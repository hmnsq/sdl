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

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
#ضمن <libdecor.h>
#جيڪڏهن_پورو

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

ساكن مزدوج Get_دري_Scale(SDL_دري *دري)
{
    أرجع (دري->flags & SDL_دري_مٿاهون_PIXEL_DENSITY) || دري->اندروني->scale_منزل_display ? دري->اندروني->scale_ضرب_ڪندڙ_2 : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
ساكن صحيح نقطو_منزل_Pixel(SDL_دري *دري, صحيح نقطو)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    أرجع نقطو ? SDL_max((صحيح)SDL_lround((مزدوج)نقطو * Get_دري_Scale(دري) + 1e-6), 1) : 0;
}

ساكن صحيح Pixel_منزل_نقطو(SDL_دري *دري, صحيح pixel)
{
    أرجع pixel ? SDL_max((صحيح)SDL_lround((مزدوج)pixel / Get_دري_Scale(دري)), 1) : 0;
}

تعداد Wayland_گهڻائي_Scale
{
    WAYLAND_گهڻائي_SCALE_UNDEFINED,
    WAYLAND_گهڻائي_SCALE_ASPECT,
    WAYLAND_گهڻائي_SCALE_STRETCH,
    WAYLAND_گهڻائي_SCALE_NONE
};

ساكن تعداد Wayland_گهڻائي_Scale Get_گهڻائي_Scale_طريقو(فراغ)
{
    ساكن تعداد Wayland_گهڻائي_Scale scale_گهڻائي_2 = WAYLAND_گهڻائي_SCALE_UNDEFINED;

    إذا (scale_گهڻائي_2 == WAYLAND_گهڻائي_SCALE_UNDEFINED) {
        ثابت حرف *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_گهڻائي_SCALING);

        إذا (scale_hint) {
            إذا (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_گهڻائي_2 = WAYLAND_گهڻائي_SCALE_STRETCH;
            } وإلا إذا (!SDL_strcasecmp(scale_hint, "none")) {
                scale_گهڻائي_2 = WAYLAND_گهڻائي_SCALE_NONE;
            } وإلا {
                scale_گهڻائي_2 = WAYLAND_گهڻائي_SCALE_ASPECT;
            }
        } وإلا {
            scale_گهڻائي_2 = WAYLAND_گهڻائي_SCALE_ASPECT;
        }
    }

    أرجع scale_گهڻائي_2;
}

تعريفنوع بنية BorderInsets
{
    صحيح کاٻو;
    صحيح چوٽي;
    صحيح ساڄو;
    صحيح bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
ساكن فراغ GetBorderInsets(SDL_دري *دري, BorderInsets *insets)
{
    SDL_zerop(insets);
    إذا (!دري->اندروني->enable_insets) {
        أرجع;
    }
    إذا (دري->اندروني->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ثابت SDL_PropertiesID props = SDL_Get_دري_Properties(دري);
        insets->کاٻو = (صحيح)SDL_clamp(SDL_Get_عدد_Property(props, SDL_PROP_دري_WAYLAND_BORDER_INSET_کاٻو_عدد, 0), 0, SDL_MAX_SINT16);
        insets->چوٽي = (صحيح)SDL_clamp(SDL_Get_عدد_Property(props, SDL_PROP_دري_WAYLAND_BORDER_INSET_چوٽي_عدد, 0), 0, SDL_MAX_SINT16);
        insets->ساڄو = (صحيح)SDL_clamp(SDL_Get_عدد_Property(props, SDL_PROP_دري_WAYLAND_BORDER_INSET_ساڄو_عدد, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (صحيح)SDL_clamp(SDL_Get_عدد_Property(props, SDL_PROP_دري_WAYLAND_BORDER_INSET_BOTTOM_عدد, 0), 0, SDL_MAX_SINT16);
    }
}

ساكن فراغ سيٽ_Min_Max_Dimensions(SDL_دري *دري)
{
    SDL_دري_معلومات *wind = دري->اندروني;
    صحيح min_ويڪر_2, min_اوچائي_2, max_ويڪر_2, max_اوچائي_2;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    إذا (دري->flags & (SDL_دري_FULLSCREEN | SDL_دري_MAXIMIZED)) {
        min_ويڪر_2 = 0;
        min_اوچائي_2 = 0;
        max_ويڪر_2 = 0;
        max_اوچائي_2 = 0;
    } وإلا إذا (دري->flags & SDL_دري_RESIZABLE) {
        صحيح adj_w = SDL_max(دري->min_w, wind->system_limits.min_ويڪر_2);
        صحيح adj_h = SDL_max(دري->min_h, wind->system_limits.min_اوچائي_2);
        إذا (wind->scale_منزل_display) {
            adj_w = Pixel_منزل_نقطو(دري, adj_w);
            adj_h = Pixel_منزل_نقطو(دري, adj_h);
        }
        min_ويڪر_2 = adj_w;
        min_اوچائي_2 = adj_h;

        adj_w = دري->max_w ? SDL_max(دري->max_w, wind->system_limits.min_ويڪر_2) : 0;
        adj_h = دري->max_h ? SDL_max(دري->max_h, wind->system_limits.min_اوچائي_2) : 0;
        إذا (wind->scale_منزل_display) {
            adj_w = Pixel_منزل_نقطو(دري, adj_w);
            adj_h = Pixel_منزل_نقطو(دري, adj_h);
        }
        max_ويڪر_2 = adj_w;
        max_اوچائي_2 = adj_h;
    } وإلا {
        min_ويڪر_2 = wind->current.logical_ويڪر;
        min_اوچائي_2 = wind->current.logical_اوچائي;
        max_ويڪر_2 = wind->current.logical_ويڪر;
        max_اوچائي_2 = wind->current.logical_اوچائي;
    }

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکٺو) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        إذا (min_ويڪر_2 && min_اوچائي_2 && min_ويڪر_2 == max_ويڪر_2 && min_اوچائي_2 == max_اوچائي_2) {
            libdecor_چوکٺو_unset_capabilities(wind->shell_surface.libdecor.چوکٺو, LIBDECOR_ACTION_RESIZE);
        } وإلا {
            libdecor_چوکٺو_سيٽ_capabilities(wind->shell_surface.libdecor.چوکٺو, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        إذا (libdecor_چوکٺو_has_capability(wind->shell_surface.libdecor.چوکٺو, LIBDECOR_ACTION_RESIZE)) {
            libdecor_چوکٺو_سيٽ_min_content_سائيز(wind->shell_surface.libdecor.چوکٺو,
                                                min_ويڪر_2,
                                                min_اوچائي_2);
            libdecor_چوکٺو_سيٽ_max_content_سائيز(wind->shell_surface.libdecor.چوکٺو,
                                                max_ويڪر_2,
                                                max_اوچائي_2);
        }
    } وإلا
#جيڪڏهن_پورو
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(دري, &insets);
        min_ويڪر_2 = SDL_max(min_ويڪر_2 - (insets.کاٻو + insets.ساڄو), min_ويڪر_2 ? 1 : 0);
        min_اوچائي_2 = SDL_max(min_اوچائي_2 - (insets.چوٽي + insets.bottom), min_اوچائي_2 ? 1 : 0);
        إذا (max_ويڪر_2) {
            max_ويڪر_2 = SDL_max(max_ويڪر_2 - (insets.کاٻو + insets.ساڄو), 1);
        }
        إذا (max_اوچائي_2) {
            max_اوچائي_2 = SDL_max(max_اوچائي_2 - (insets.چوٽي + insets.bottom), 1);
        }
        xdg_toplevel_سيٽ_min_سائيز(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_ويڪر_2,
                                  min_اوچائي_2);
        xdg_toplevel_سيٽ_max_سائيز(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_ويڪر_2,
                                  max_اوچائي_2);
    }
}

ساكن فراغ EnsurePopupPositionIsValid(SDL_دري *دري, صحيح *x, صحيح *y)
{
    صحيح adj_ڳڻپ = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    إذا (*x + دري->w <= 0) {
        *x = -دري->w;
        ++adj_ڳڻپ;
    }
    إذا (*y + دري->h <= 0) {
        *y = -دري->h;
        ++adj_ڳڻپ;
    }
    إذا (*x >= دري->والد->w) {
        *x = دري->والد->w;
        ++adj_ڳڻپ;
    }
    إذا (*y >= دري->والد->h) {
        *y = دري->والد->h;
        ++adj_ڳڻپ;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    إذا (adj_ڳڻپ > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
ساكن فراغ Get_دري_Geometry(SDL_دري_معلومات *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    إذا (SDL_Rect_خالي_جايون(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_ويڪر;
        geometry->h = wind->current.logical_اوچائي;
    }
}

ساكن فراغ Adjust_Popup_وٿي(SDL_دري *popup, صحيح *x, صحيح *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (popup->والد->اندروني->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        صحيح adj_x, adj_y;
        libdecor_چوکٺو_translate_coordinate(popup->والد->اندروني->shell_surface.libdecor.چوکٺو,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } وإلا
#جيڪڏهن_پورو
    {
        *x -= popup->والد->اندروني->explicit_geometry.x;
        *y -= popup->والد->اندروني->explicit_geometry.y;
    }
}

ساكن فراغ RepositionPopup(SDL_دري *دري, bool use_current_position)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_نسخو(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_نسخو) {
        صحيح x = use_current_position ? دري->x : دري->pending.x;
        صحيح y = use_current_position ? دري->y : دري->pending.y;

        EnsurePopupPositionIsValid(دري, &x, &y);
        إذا (wind->scale_منزل_display) {
            x = Pixel_منزل_نقطو(دري->والد, x);
            y = Pixel_منزل_نقطو(دري->والد, y);
        }
        Adjust_Popup_وٿي(دري, &x, &y);
        SDL_Rect والد_geometry;
        Get_دري_Geometry(دري->والد->اندروني, &والد_geometry);
        xdg_positioner_سيٽ_anchor_rect(wind->shell_surface.xdg.popup.xdg_positioner, 0, 0, والد_geometry.w, والد_geometry.h);
        xdg_positioner_سيٽ_سائيز(wind->shell_surface.xdg.popup.xdg_positioner, wind->current.logical_ويڪر, wind->current.logical_اوچائي);
        xdg_positioner_سيٽ_وٿي(wind->shell_surface.xdg.popup.xdg_positioner, x, y);
        xdg_popup_reposition(wind->shell_surface.xdg.popup.xdg_popup,
                             wind->shell_surface.xdg.popup.xdg_positioner,
                             0);
    }
}

ساكن فراغ سيٽ_Surface_Opaque_Region(بنية wl_surface *surface, صحيح ويڪر, صحيح اوچائي)
{
    SDL_Video_معلومات *viddata = SDL_GetVideoDevice()->اندروني;

    إذا (ويڪر && اوچائي) {
        بنية wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_جوڙيو(region, 0, 0, ويڪر, اوچائي);
        wl_surface_سيٽ_opaque_region(surface, region);
        wl_region_destroy(region);
    } وإلا {
        wl_surface_سيٽ_opaque_region(surface, عدم);
    }
}

ساكن فراغ Configure_دري_Geometry(SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    ثابت مزدوج scale_ضرب_ڪندڙ_2 = Get_دري_Scale(دري);
    ثابت مزدوج prev_اشارو_scale_x = معلومات->اشارو_scale.x;
    ثابت مزدوج prev_اشارو_scale_y = معلومات->اشارو_scale.y;
    ثابت صحيح old_pixel_ويڪر = معلومات->current.pixel_ويڪر;
    ثابت صحيح old_pixel_اوچائي = معلومات->current.pixel_اوچائي;
    صحيح دري_ويڪر = 0;
    صحيح دري_اوچائي = 0;
    صحيح viewport_ويڪر, viewport_اوچائي;
    bool دري_سائيز_بدليو;
    bool بفر_سائيز_بدليو;
    ثابت bool is_opaque = !(دري->flags & SDL_دري_TRANSPARENT) && دري->opacity == 1.0f;

    إذا (معلومات->is_fullscreen && دري->fullscreen_exclusive) {
        دري_ويڪر = دري->current_fullscreen_گهڻائي.w;
        دري_اوچائي = دري->current_fullscreen_گهڻائي.h;

        viewport_ويڪر = معلومات->requested.logical_ويڪر;
        viewport_اوچائي = معلومات->requested.logical_اوچائي;

        بدل (Get_گهڻائي_Scale_طريقو()) {
        حالة WAYLAND_گهڻائي_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            إذا (دري_ويڪر <= viewport_ويڪر && دري_اوچائي <= viewport_اوچائي) {
                viewport_ويڪر = دري_ويڪر;
                viewport_اوچائي = دري_اوچائي;

                اكسر;
            }
            SDL_FALLTHROUGH;
        حالة WAYLAND_گهڻائي_SCALE_ASPECT:
        {
            ثابت عائم output_تناسب = (عائم)viewport_ويڪر / (عائم)viewport_اوچائي;
            ثابت عائم گهڻائي_تناسب = (عائم)دري_ويڪر / (عائم)دري_اوچائي;

            إذا (output_تناسب > گهڻائي_تناسب) {
                viewport_ويڪر = SDL_lroundf((عائم)دري_ويڪر * ((عائم)viewport_اوچائي / (عائم)دري_اوچائي));
            } وإلا إذا (output_تناسب < گهڻائي_تناسب) {
                viewport_اوچائي = SDL_lroundf((عائم)دري_اوچائي * ((عائم)viewport_ويڪر / (عائم)دري_ويڪر));
            }
        } اكسر;
        افتراضي:
            اكسر;
        }

        دري_سائيز_بدليو = دري_ويڪر != دري->w ||
                              دري_اوچائي != دري->h ||
                              معلومات->current.viewport_ويڪر != viewport_ويڪر ||
                              معلومات->current.viewport_اوچائي != viewport_اوچائي;

        // Exclusive fullscreen window sizes are always in pixel units.
        معلومات->current.pixel_ويڪر = دري_ويڪر;
        معلومات->current.pixel_اوچائي = دري_اوچائي;
        بفر_سائيز_بدليو = معلومات->current.pixel_ويڪر != old_pixel_ويڪر ||
                              معلومات->current.pixel_اوچائي != old_pixel_اوچائي;

        إذا (دري_سائيز_بدليو || بفر_سائيز_بدليو) {
            إذا (معلومات->viewport) {
                wp_viewport_سيٽ_destination(معلومات->viewport, viewport_ويڪر, viewport_اوچائي);

                معلومات->current.logical_ويڪر = معلومات->requested.logical_ويڪر;
                معلومات->current.logical_اوچائي = معلومات->requested.logical_اوچائي;
                معلومات->current.viewport_ويڪر = viewport_ويڪر;
                معلومات->current.viewport_اوچائي = viewport_اوچائي;
            } وإلا {
                // Calculate the integer scale from the mode and output.
                ثابت int32_t int_scale = SDL_max(دري->current_fullscreen_گهڻائي.w / viewport_ويڪر, 1);

                wl_surface_سيٽ_بفر_scale(معلومات->surface, int_scale);
                معلومات->current.logical_ويڪر = دري->current_fullscreen_گهڻائي.w;
                معلومات->current.logical_اوچائي = دري->current_fullscreen_گهڻائي.h;
            }

            معلومات->اشارو_scale.x = (مزدوج)دري_ويڪر / (مزدوج)viewport_ويڪر;
            معلومات->اشارو_scale.y = (مزدوج)دري_اوچائي / (مزدوج)viewport_اوچائي;
        }
    } وإلا {
        إذا (!معلومات->scale_منزل_display) {
            viewport_ويڪر = معلومات->requested.logical_ويڪر;
            viewport_اوچائي = معلومات->requested.logical_اوچائي;
        } وإلا {
            viewport_ويڪر = معلومات->requested.pixel_ويڪر;
            viewport_اوچائي = معلومات->requested.pixel_اوچائي;
        }

        إذا (!معلومات->enable_insets &&
            معلومات->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_HIDDEN &&
            معلومات->viewport && معلومات->wayland_معلومات->subcompositor && !معلومات->floating && !معلومات->is_fullscreen) {
            صحيح min_ويڪر_2, min_اوچائي_2, max_ويڪر_2, max_اوچائي_2;
            إذا (دري->flags & SDL_دري_RESIZABLE) {
                min_ويڪر_2 = دري->min_w;
                min_اوچائي_2 = دري->min_h;
                max_ويڪر_2 = دري->max_w;
                max_اوچائي_2 = دري->max_h;
            } وإلا {
                // Use the fixed size in the odd case where a non-resizable window somehow wound up tiled or maximized.
                min_ويڪر_2 = دري->floating.w;
                min_اوچائي_2 = دري->floating.h;
                max_ويڪر_2 = دري->floating.w;
                max_اوچائي_2 = دري->floating.h;
            }

            إذا (min_ويڪر_2) {
                viewport_ويڪر = SDL_max(viewport_ويڪر, min_ويڪر_2);
            }
            إذا (min_اوچائي_2) {
                viewport_اوچائي = SDL_max(viewport_اوچائي, min_اوچائي_2);
            }
            إذا (max_ويڪر_2) {
                viewport_ويڪر = SDL_min(viewport_ويڪر, max_ويڪر_2);
            }
            إذا (max_اوچائي_2) {
                viewport_اوچائي = SDL_min(viewport_اوچائي, max_اوچائي_2);
            }

            عائم aspect = (عائم)viewport_ويڪر / (عائم)viewport_اوچائي;
            إذا (دري->min_aspect != 0.f && aspect < دري->min_aspect) {
                viewport_اوچائي = SDL_max(SDL_lroundf((عائم)viewport_ويڪر / دري->min_aspect), 1);
            } وإلا إذا (دري->max_aspect != 0.f && aspect > دري->max_aspect) {
                viewport_ويڪر = SDL_max(SDL_lroundf((عائم)viewport_اوچائي * دري->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            دري_ويڪر = viewport_ويڪر;
            دري_اوچائي = viewport_اوچائي;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            إذا (!معلومات->scale_منزل_display) {
                إذا (viewport_ويڪر > معلومات->requested.logical_ويڪر || viewport_اوچائي > معلومات->requested.logical_اوچائي) {
                    aspect = (عائم)viewport_ويڪر / (عائم)viewport_اوچائي;
                    ثابت عائم دري_تناسب = (عائم)معلومات->requested.logical_ويڪر / (عائم)معلومات->requested.logical_اوچائي;
                    إذا (aspect >= دري_تناسب) {
                        viewport_ويڪر = معلومات->requested.logical_ويڪر;
                        viewport_اوچائي = SDL_lroundf((عائم)viewport_ويڪر / aspect);
                    } وإلا إذا (aspect < دري_تناسب) {
                        viewport_اوچائي = معلومات->requested.logical_اوچائي;
                        viewport_ويڪر = SDL_lroundf((عائم)viewport_اوچائي * aspect);
                    }
                }
            } وإلا {
                إذا (viewport_ويڪر > معلومات->requested.pixel_ويڪر || viewport_اوچائي > معلومات->requested.pixel_اوچائي) {
                    aspect = (عائم)viewport_ويڪر / (عائم)viewport_اوچائي;
                    ثابت عائم دري_تناسب = (عائم)معلومات->requested.pixel_ويڪر / (عائم)معلومات->requested.pixel_اوچائي;
                    إذا (aspect >= دري_تناسب) {
                        viewport_ويڪر = معلومات->requested.pixel_ويڪر;
                        viewport_اوچائي = SDL_lroundf((عائم)viewport_ويڪر / aspect);
                    } وإلا إذا (aspect < دري_تناسب) {
                        viewport_اوچائي = معلومات->requested.pixel_اوچائي;
                        viewport_ويڪر = SDL_lroundf((عائم)viewport_اوچائي * aspect);
                    }
                }
            }

            viewport_ويڪر = SDL_max(viewport_ويڪر, 1);
            viewport_اوچائي = SDL_max(viewport_اوچائي, 1);
        } وإلا {
            دري_ويڪر = viewport_ويڪر;
            دري_اوچائي = viewport_اوچائي;
        }

        إذا (!معلومات->scale_منزل_display) {
            معلومات->current.pixel_ويڪر = نقطو_منزل_Pixel(دري, دري_ويڪر);
            معلومات->current.pixel_اوچائي = نقطو_منزل_Pixel(دري, دري_اوچائي);
        } وإلا {
            // The viewport size is in pixels at this point; convert it to logical units.
            معلومات->current.pixel_ويڪر = دري_ويڪر;
            معلومات->current.pixel_اوچائي = دري_اوچائي;
            viewport_ويڪر = Pixel_منزل_نقطو(دري, viewport_ويڪر);
            viewport_اوچائي = Pixel_منزل_نقطو(دري, viewport_اوچائي);
        }

        // Clamp the physical window size to the system minimum required size.
        معلومات->requested.logical_ويڪر = SDL_max(معلومات->requested.logical_ويڪر, معلومات->system_limits.min_ويڪر_2);
        معلومات->requested.logical_اوچائي = SDL_max(معلومات->requested.logical_اوچائي, معلومات->system_limits.min_اوچائي_2);

        دري_سائيز_بدليو = معلومات->requested.logical_ويڪر != معلومات->current.logical_ويڪر ||
                              معلومات->requested.logical_اوچائي != معلومات->current.logical_اوچائي ||
                              viewport_ويڪر != معلومات->current.viewport_ويڪر ||
                              viewport_اوچائي != معلومات->current.viewport_اوچائي;

        بفر_سائيز_بدليو = معلومات->current.pixel_ويڪر != old_pixel_ويڪر ||
                              معلومات->current.pixel_اوچائي != old_pixel_اوچائي;

        إذا (دري_سائيز_بدليو || بفر_سائيز_بدليو) {
            إذا (معلومات->viewport) {
                wp_viewport_سيٽ_destination(معلومات->viewport, viewport_ويڪر, viewport_اوچائي);
            } وإلا إذا (دري->flags & SDL_دري_مٿاهون_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_سيٽ_بفر_scale(معلومات->surface, (int32_t)scale_ضرب_ڪندڙ_2);
            }

            معلومات->current.logical_ويڪر = معلومات->requested.logical_ويڪر;
            معلومات->current.logical_اوچائي = معلومات->requested.logical_اوچائي;
            معلومات->current.viewport_ويڪر = viewport_ويڪر;
            معلومات->current.viewport_اوچائي = viewport_اوچائي;

            معلومات->اشارو_scale.x = (مزدوج)دري_ويڪر / (مزدوج)viewport_ويڪر;
            معلومات->اشارو_scale.y = (مزدوج)دري_اوچائي / (مزدوج)viewport_اوچائي;
        }
    }

    إذا (معلومات->egl_دري && بفر_سائيز_بدليو) {
        WAYLAND_wl_egl_دري_resize(معلومات->egl_دري,
                                     معلومات->current.pixel_ويڪر,
                                     معلومات->current.pixel_اوچائي,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    إذا (!معلومات->enable_insets && معلومات->viewport && معلومات->wayland_معلومات->subcompositor && (!معلومات->is_fullscreen || Should_نقاب_Fullscreen()) &&
        (viewport_ويڪر != معلومات->current.logical_ويڪر || viewport_اوچائي != معلومات->current.logical_اوچائي)) {
        بنية wl_بفر *old_بفر = عدم;

        إذا (!معلومات->نقاب.surface) {
            معلومات->نقاب.surface = wl_compositor_create_surface(معلومات->wayland_معلومات->compositor);
            SDL_WAYLAND_رجسٽر_surface(معلومات->نقاب.surface);
            wl_surface_سيٽ_user_معلومات(معلومات->نقاب.surface, معلومات);
        }
        إذا (!معلومات->نقاب.subsurface) {
            معلومات->نقاب.subsurface = wl_subcompositor_get_subsurface(معلومات->wayland_معلومات->subcompositor, معلومات->نقاب.surface, معلومات->surface);
        }
        إذا (!معلومات->نقاب.viewport) {
            معلومات->نقاب.viewport = wp_viewporter_get_viewport(معلومات->wayland_معلومات->viewporter, معلومات->نقاب.surface);
        }
        إذا (!معلومات->نقاب.بفر_2 || معلومات->نقاب.opaque != is_opaque) {
            old_بفر = معلومات->نقاب.بفر_2;
            معلومات->نقاب.opaque = is_opaque;
            معلومات->نقاب.بفر_2 = Wayland_Create_Single_Pixel_بفر(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(معلومات->نقاب.surface, معلومات->نقاب.بفر_2, 0, 0);

        wl_subsurface_رکو_هيٺ(معلومات->نقاب.subsurface, معلومات->surface);
        wp_viewport_سيٽ_destination(معلومات->نقاب.viewport, معلومات->current.logical_ويڪر, معلومات->current.logical_اوچائي);

        إذا (wl_surface_get_نسخو(معلومات->نقاب.surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخو) {
            wl_surface_damage_بفر(معلومات->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } وإلا {
            wl_surface_damage(معلومات->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        إذا (is_opaque) {
            سيٽ_Surface_Opaque_Region(معلومات->نقاب.surface, معلومات->current.logical_ويڪر, معلومات->current.logical_اوچائي);
        } وإلا {
            سيٽ_Surface_Opaque_Region(معلومات->نقاب.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        إذا (معلومات->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            معلومات->نقاب.وٿي_x = -(معلومات->current.logical_ويڪر - viewport_ويڪر) / 2;
            معلومات->نقاب.وٿي_y = -(معلومات->current.logical_اوچائي - viewport_اوچائي) / 2;
        } وإلا {
            معلومات->نقاب.وٿي_x = 0;
            معلومات->نقاب.وٿي_y = 0;
        }

        wl_subsurface_سيٽ_position(معلومات->نقاب.subsurface, معلومات->نقاب.وٿي_x, معلومات->نقاب.وٿي_y);
        wl_surface_commit(معلومات->نقاب.surface);

        إذا (old_بفر) {
            wl_بفر_destroy(old_بفر);
        }

        معلومات->نقاب.mapped = true;
    } وإلا إذا (معلومات->نقاب.mapped) {
        wl_subsurface_سيٽ_position(معلومات->نقاب.subsurface, 0, 0);
        wl_surface_attach(معلومات->نقاب.surface, عدم, 0, 0);
        wl_surface_commit(معلومات->نقاب.surface);

        معلومات->نقاب.وٿي_x = 0;
        معلومات->نقاب.وٿي_y = 0;
        معلومات->نقاب.mapped = false;
    }

    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && معلومات->shell_surface.xdg.surface &&
        (معلومات->enable_insets || !معلومات->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(دري, &insets);
        ثابت bool use_insets = (insets.کاٻو || insets.چوٽي || insets.ساڄو || insets.bottom) &&
                                !(دري->flags & (SDL_دري_MAXIMIZED | SDL_دري_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, معلومات->current.logical_ويڪر, معلومات->current.logical_اوچائي };
        إذا (use_insets) {
            geometry.x = insets.کاٻو;
            geometry.y = insets.چوٽي;
            geometry.w = SDL_max(geometry.w - (insets.کاٻو + insets.ساڄو), 1);
            geometry.h = SDL_max(geometry.h - (insets.چوٽي + insets.bottom), 1);
        }
        /* An explicitly set geometry does not track the surface, so it must be kept in sync
         * once set. Otherwise this is only done when viewports aren't supported and the size
         * has changed (XXX: a hack) to avoid a potential protocol violation if a buffer with
         * an old size is committed.
         */
        إذا ((use_insets || !SDL_Rect_خالي_جايون(&معلومات->explicit_geometry) || (!معلومات->viewport && دري_سائيز_بدليو)) &&
            !SDL_RectsEqual(&geometry, &معلومات->explicit_geometry)) {
            xdg_surface_سيٽ_دري_geometry(معلومات->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            معلومات->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    إذا (دري_سائيز_بدليو) {
        إذا (is_opaque) {
            سيٽ_Surface_Opaque_Region(معلومات->surface, viewport_ويڪر, viewport_اوچائي);
        } وإلا {
            سيٽ_Surface_Opaque_Region(معلومات->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        لكل (SDL_دري *ٻار = دري->پهريون_ٻار; ٻار; ٻار = ٻار->ايندڙ_sibling) {
            RepositionPopup(ٻار, true);
        }
    }

    // Update the scale for any focused cursors.
    إذا (prev_اشارو_scale_x != معلومات->اشارو_scale.x || prev_اشارو_scale_y != معلومات->اشارو_scale.y) {
        Wayland_Display_Update_اشارو_Focused_Scale(معلومات);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    سيٽ_Min_Max_Dimensions(دري);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    إذا (!معلومات->scale_منزل_display) {
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, دري_ويڪر, دري_اوچائي);
    } وإلا {
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESIZED, معلومات->current.pixel_ويڪر, معلومات->current.pixel_اوچائي);
    }
    SDL_Send_دري_Event(دري, SDL_EVENT_دري_PIXEL_سائيز_بدليو, معلومات->current.pixel_ويڪر, معلومات->current.pixel_اوچائي);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    إذا (معلومات->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        إذا ((بفر_سائيز_بدليو || دري_سائيز_بدليو) ||
            (!معلومات->suspended && (دري->flags & SDL_دري_OCCLUDED))) {
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_EXPOSED, 0, 0);
        }

        إذا (معلومات->suspended) {
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_OCCLUDED, 0, 0);
        }
    }
}

ساكن فراغ Commit_Libdecor_چوکٺو(SDL_دري *دري)
{
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    SDL_دري_معلومات *wind = دري->اندروني;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکٺو) {
        بنية libdecor_state *state = libdecor_state_new(wind->current.logical_ويڪر, wind->current.logical_اوچائي);
        libdecor_چوکٺو_commit(wind->shell_surface.libdecor.چوکٺو, state, عدم);
        libdecor_state_free(state);
    }
#جيڪڏهن_پورو
}

ساكن فراغ pending_state_deadline_handler(فراغ *معلومات, بنية wl_callback *callback, uint32_t callback_معلومات)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_دري_ID دري_ID = (SDL_دري_ID)(uintptr_t)معلومات;
    SDL_دري *دري = SDL_Get_دري_From_ID(دري_ID);

    إذا (دري && دري->اندروني) {
        --دري->اندروني->pending_state_deadline_ڳڻپ;
    }

    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

ساكن فراغ جوڙيو_Pending_State_Sync(SDL_دري_معلومات *دري_معلومات_2)
{
    SDL_Video_معلومات *video_معلومات = دري_معلومات_2->wayland_معلومات;
    فراغ *cb_معلومات = (فراغ *)(uintptr_t)دري_معلومات_2->sdlwindow->id;

    ++دري_معلومات_2->pending_state_deadline_ڳڻپ;
    بنية wl_callback *cb = wl_display_sync(video_معلومات->display);
    wl_callback_جوڙيو_listener(cb, &pending_state_deadline_listener, cb_معلومات);
}

ساكن فراغ FlushPendingEvents(SDL_دري *دري)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ثابت bool آخري_position_pending = دري->آخري_position_pending;
    ثابت bool آخري_سائيز_pending = دري->آخري_سائيز_pending;

    طالما (دري->اندروني->pending_state_deadline_ڳڻپ) {
        WAYLAND_wl_display_roundtrip(دري->اندروني->wayland_معلومات->display);
    }

    دري->آخري_position_pending = آخري_position_pending;
    دري->آخري_سائيز_pending = آخري_سائيز_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
فراغ Wayland_Update_دري_Position(SDL_دري *دري)
{
    SDL_دري_معلومات *wind = دري->اندروني;
    SDL_Display_معلومات *display;

    إذا (wind->outputs && wind->انگ_outputs) {
        display = wind->outputs[wind->انگ_outputs - 1];
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
    wind->آخري_display_ID = display->display;
    إذا (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        إذا (!wind->wayland_معلومات->scale_منزل_display_enabled) {
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_MOVED, display->logical.x, display->logical.y);
        } وإلا {
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_DISPLAY_بدليو, wind->آخري_display_ID, 0);
    }
}

ساكن فراغ سيٽ_Fullscreen(SDL_دري *دري, بنية wl_output *output, bool fullscreen)
{
    SDL_دري_معلومات *wind = دري->اندروني;

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکٺو) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? دري->fullscreen_exclusive : false;
        إذا (fullscreen) {
            libdecor_چوکٺو_سيٽ_fullscreen(wind->shell_surface.libdecor.چوکٺو, output);
        } وإلا {
            libdecor_چوکٺو_unset_fullscreen(wind->shell_surface.libdecor.چوکٺو);
        }
    } وإلا
#جيڪڏهن_پورو
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? دري->fullscreen_exclusive : false;
        إذا (fullscreen) {
            xdg_toplevel_سيٽ_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } وإلا {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    جوڙيو_Pending_State_Sync(wind);
}

ساكن فراغ Update_دري_Fullscreen(SDL_دري *دري, bool fullscreen)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    wind->is_fullscreen = fullscreen;

    إذا (fullscreen) {
        إذا (!(دري->flags & SDL_دري_FULLSCREEN)) {
            SDL_copyp(&دري->current_fullscreen_گهڻائي, &دري->requested_fullscreen_گهڻائي);
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_ENTER_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_گهڻائي(دري, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            إذا (دري->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(دري->current_fullscreen_گهڻائي.displayID);
                إذا (disp) {
                    wind->fullscreen_was_positioned = true;
                    سيٽ_Fullscreen(دري, disp->اندروني->output, true);
                }
            }
        }
    } وإلا {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        إذا ((دري->flags & SDL_دري_FULLSCREEN) && !دري->is_hiding && !(دري->flags & SDL_دري_HIDDEN)) {
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_LEAVE_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_گهڻائي(دري, SDL_FULLSCREEN_OP_LEAVE, false);
            wind->fullscreen_was_positioned = false;

            /* Send a move event, in case it was deferred while the fullscreen window was moving and
             * on multiple outputs.
             */
            Wayland_Update_دري_Position(دري);
        }
    }
}

ساكن ثابت بنية wl_callback_listener surface_چوکٺو_listener;

ساكن فراغ surface_چوکٺو_پورو(فراغ *معلومات, بنية wl_callback *cb, uint32_t وقت)
{
    SDL_دري_معلومات *wind = (SDL_دري_معلومات *)معلومات;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    إذا (wl_compositor_get_نسخو(wind->wayland_معلومات->compositor) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخو) {
        wl_surface_damage_بفر(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } وإلا {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            Configure_دري_Geometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } وإلا {
        wind->resizing = false;
    }

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکٺو) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        لكل (SDL_دري *w = wind->sdlwindow->پهريون_ٻار; w; w = w->ايندڙ_sibling) {
            إذا (w->اندروني->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOW_PENDING) {
                Wayland_Show_دري(SDL_GetVideoDevice(), w);
            } وإلا إذا (w->اندروني->reparenting_required) {
                Wayland_سيٽ_دري_والد(SDL_GetVideoDevice(), w, w->والد);
                إذا (w->flags & SDL_دري_MODAL) {
                    Wayland_سيٽ_دري_Modal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        إذا (wind->suspended) {
            SDL_Send_دري_Event(wind->sdlwindow, SDL_EVENT_دري_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_چوکٺو_callback = wl_surface_چوکٺو(wind->surface);
    wl_callback_جوڙيو_listener(wind->surface_چوکٺو_callback, &surface_چوکٺو_listener, معلومات);
}

ساكن ثابت بنية wl_callback_listener surface_چوکٺو_listener = {
    surface_چوکٺو_پورو
};

ساكن ثابت بنية wl_callback_listener gles_مٽا_سٽا_چوکٺو_listener;

ساكن فراغ gles_مٽا_سٽا_چوکٺو_پورو(فراغ *معلومات, بنية wl_callback *cb, uint32_t وقت)
{
    SDL_دري_معلومات *wind = (SDL_دري_معلومات *)معلومات;
    SDL_سيٽ_Atomic_Int(&wind->مٽا_سٽا_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_مٽا_سٽا_چوکٺو_callback = wl_surface_چوکٺو(wind->gles_مٽا_سٽا_چوکٺو_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_جوڙيو_listener(wind->gles_مٽا_سٽا_چوکٺو_callback, &gles_مٽا_سٽا_چوکٺو_listener, معلومات);
}

ساكن ثابت بنية wl_callback_listener gles_مٽا_سٽا_چوکٺو_listener = {
    gles_مٽا_سٽا_چوکٺو_پورو
};

ساكن فراغ handle_xdg_surface_configure(فراغ *معلومات, بنية xdg_surface *xdg, uint32_t serial)
{
    SDL_دري_معلومات *wind = (SDL_دري_معلومات *)معلومات;
    SDL_دري *دري = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    إذا (!wind->resizing) {
        wind->pending_config_ack = false;
        Configure_دري_Geometry(دري);
        xdg_surface_ack_configure(xdg, serial);
    } وإلا إذا (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_EXPOSED, 0, 0);
    }

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکٺو;
    }
}

ساكن ثابت بنية xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

ساكن فراغ ApplyGeometryLimits(SDL_دري *دري, صحيح req_w, صحيح req_h, صحيح *ٻاهريون_w, صحيح *ٻاهريون_h)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    صحيح w = req_w;
    صحيح h = req_h;
    ثابت عائم aspect = (عائم)req_w / (عائم)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    إذا (!wind->resizing || (wind->resize_ڪنارو & WAYLAND_RESIZE_ڪنارو_ڪنڊ) == WAYLAND_RESIZE_ڪنارو_ڪنڊ) {
        إذا (دري->min_aspect != 0.f && aspect < دري->min_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / دري->min_aspect), 1);

            إذا (h < دري->min_h) {
                w = SDL_max(SDL_lroundf((عائم)دري->min_h * دري->min_aspect), 1);
            }
            إذا (دري->max_h && h > دري->max_h) {
                w = SDL_max(SDL_lroundf((عائم)دري->max_h * دري->min_aspect), 1);
            }
        } وإلا إذا (دري->max_aspect != 0.f && aspect > دري->max_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * دري->max_aspect), 1);

            إذا (w < دري->min_w) {
                h = SDL_max(SDL_lroundf((عائم)دري->min_w / دري->max_aspect), 1);
            }
            إذا (دري->max_w && w > دري->max_w) {
                h = SDL_max(SDL_lroundf((عائم)دري->max_w / دري->max_aspect), 1);
            }
        }
    } وإلا إذا (wind->resize_ڪنارو & WAYLAND_RESIZE_ڪنارو_LR) {
        إذا (دري->min_aspect != 0.f && aspect < دري->min_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / دري->min_aspect), 1);

            إذا (h < دري->min_h) {
                w = SDL_max(SDL_lroundf((عائم)دري->min_h * دري->min_aspect), 1);
            }
            إذا (دري->max_h && h > دري->max_h) {
                w = SDL_max(SDL_lroundf((عائم)دري->max_h * دري->min_aspect), 1);
            }
        } وإلا إذا (دري->max_aspect != 0.f && aspect > دري->max_aspect) {
            h = SDL_max(SDL_lroundf((عائم)req_w / دري->max_aspect), 1);

            إذا (h < دري->min_h) {
                w = SDL_max(SDL_lroundf((عائم)دري->min_h * دري->max_aspect), 1);
            }
            إذا (دري->max_h && h > دري->max_h) {
                w = SDL_max(SDL_lroundf((عائم)دري->max_h * دري->max_aspect), 1);
            }
        }
    } وإلا إذا (wind->resize_ڪنارو & WAYLAND_RESIZE_ڪنارو_TB) {
        إذا (دري->min_aspect != 0.f && aspect < دري->min_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * دري->min_aspect), 1);

            إذا (w < دري->min_w) {
                h = SDL_max(SDL_lroundf((عائم)دري->min_w / دري->min_aspect), 1);
            }
            إذا (دري->max_w && w > دري->max_w) {
                h = SDL_max(SDL_lroundf((عائم)دري->max_w / دري->min_aspect), 1);
            }
        } وإلا إذا (دري->max_aspect != 0.f && aspect > دري->max_aspect) {
            w = SDL_max(SDL_lroundf((عائم)req_h * دري->max_aspect), 1);

            إذا (w < دري->min_w) {
                h = SDL_max(SDL_lroundf((عائم)دري->min_w / دري->max_aspect), 1);
            }
            إذا (دري->max_w && w > دري->max_w) {
                h = SDL_max(SDL_lroundf((عائم)دري->max_w / دري->max_aspect), 1);
            }
        }
    }

    إذا (دري->max_w) {
        w = SDL_min(w, دري->max_w);
    }
    *ٻاهريون_w = SDL_max(w, دري->min_w);

    إذا (دري->max_h) {
        h = SDL_min(h, دري->max_h);
    }
    *ٻاهريون_h = SDL_max(h, دري->min_h);

}

ساكن فراغ DetermineResizeAxis(SDL_دري_معلومات *wind, صحيح ويڪر, صحيح اوچائي, bool resizing)
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
        إذا (now >= wind->آخري_resize_event_وقت_ns + SDL_MS_منزل_NS(500)) {
            wind->resize_ڪنارو = 0;
        }

        wind->آخري_resize_event_وقت_ns = now;

        إذا (!wind->resize_ڪنارو) {
            إذا (ويڪر != wind->آخري_configure.ويڪر || !اوچائي) {
                wind->resize_ڪنارو |= WAYLAND_RESIZE_ڪنارو_LR;
            }
            إذا (اوچائي != wind->آخري_configure.اوچائي || !ويڪر) {
                wind->resize_ڪنارو |= WAYLAND_RESIZE_ڪنارو_TB;
            }
        }
    } وإلا {
        wind->resize_ڪنارو = 0;
    }

    wind->resizing = resizing;
}

ساكن فراغ handle_xdg_toplevel_configure(فراغ *معلومات,
                                          بنية xdg_toplevel *xdg_toplevel,
                                          int32_t ويڪر,
                                          int32_t اوچائي,
                                          بنية wl_array *حالتون)
{
    SDL_دري_معلومات *wind = (SDL_دري_معلومات *)معلومات;
    SDL_دري *دري = wind->sdlwindow;

    تعداد xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool سرگرم = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, حالتون) {
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
        حالة XDG_TOPLEVEL_STATE_TILED_کاٻو:
        حالة XDG_TOPLEVEL_STATE_TILED_ساڄو:
        حالة XDG_TOPLEVEL_STATE_TILED_چوٽي:
        حالة XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_کاٻو:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_کاٻو;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_ساڄو:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ساڄو;
            اكسر;
        حالة XDG_TOPLEVEL_STATE_CONSTRAINED_چوٽي:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_چوٽي;
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
    ثابت bool new_configure_سائيز = ويڪر != wind->آخري_configure.ويڪر || اوچائي != wind->آخري_configure.اوچائي ||
                                    insets_apply != wind->آخري_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    إذا (insets_apply) {
        GetBorderInsets(دري, &insets);
    }

    DetermineResizeAxis(wind, ويڪر, اوچائي, resizing);
    Update_دري_Fullscreen(دري, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from xdg-shell, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    إذا (سرگرم || !(دري->flags & SDL_دري_MINIMIZED)) {
        إذا (دري->flags & SDL_دري_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESTORED, 0, 0);
        }
        SDL_Send_دري_Event(دري,
                            (maximized && !fullscreen) ? SDL_EVENT_دري_MAXIMIZED : SDL_EVENT_دري_RESTORED,
                            0, 0);
    }

    إذا (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        إذا ((دري->flags & SDL_دري_RESIZABLE) || maximized) {
            إذا (!ويڪر) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                إذا (floating) {
                    ويڪر = دري->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.ويڪر) {
                        ويڪر = SDL_min(wind->toplevel_bounds.ويڪر, ويڪر);
                    }
                } وإلا {
                    ويڪر = دري->windowed.w;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_ويڪر = ويڪر;
                } وإلا {
                    wind->requested.pixel_ويڪر = ويڪر;
                    ويڪر = wind->requested.logical_ويڪر = Pixel_منزل_نقطو(دري, ويڪر);
                }
                ويڪر = SDL_max(ويڪر - (insets.کاٻو + insets.ساڄو), 1);
            } وإلا إذا (new_configure_سائيز) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_ويڪر = ويڪر + (insets.کاٻو + insets.ساڄو);

                إذا (wind->scale_منزل_display) {
                    wind->requested.pixel_ويڪر = نقطو_منزل_Pixel(دري, wind->requested.logical_ويڪر);
                }
            }
            إذا (!اوچائي) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                إذا (floating) {
                    اوچائي = دري->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.اوچائي) {
                        اوچائي = SDL_min(wind->toplevel_bounds.اوچائي, اوچائي);
                    }
                } وإلا {
                    اوچائي = دري->windowed.h;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_اوچائي = اوچائي;
                } وإلا {
                    wind->requested.pixel_اوچائي = اوچائي;
                    اوچائي = wind->requested.logical_اوچائي = Pixel_منزل_نقطو(دري, اوچائي);
                }
                اوچائي = SDL_max(اوچائي - (insets.چوٽي + insets.bottom), 1);
            } وإلا إذا (new_configure_سائيز) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_اوچائي = اوچائي + (insets.چوٽي + insets.bottom);

                إذا (wind->scale_منزل_display) {
                    wind->requested.pixel_اوچائي = نقطو_منزل_Pixel(دري, wind->requested.logical_اوچائي);
                }
            }
        } وإلا {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            إذا (!wind->scale_منزل_display) {
                ويڪر = wind->requested.logical_ويڪر = دري->floating.w;
                اوچائي = wind->requested.logical_اوچائي = دري->floating.h;
            } وإلا {
                wind->requested.pixel_ويڪر = دري->floating.w;
                wind->requested.pixel_اوچائي = دري->floating.h;
                ويڪر = wind->requested.logical_ويڪر = Pixel_منزل_نقطو(دري, دري->floating.w);
                اوچائي = wind->requested.logical_اوچائي = Pixel_منزل_نقطو(دري, دري->floating.h);
            }
            ويڪر = SDL_max(ويڪر - (insets.کاٻو + insets.ساڄو), 1);
            اوچائي = SDL_max(اوچائي - (insets.چوٽي + insets.bottom), 1);
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
                ApplyGeometryLimits(دري, wind->requested.logical_ويڪر, wind->requested.logical_اوچائي, &wind->requested.logical_ويڪر, &wind->requested.logical_اوچائي);
            } وإلا {
                ApplyGeometryLimits(دري, wind->requested.pixel_ويڪر, wind->requested.pixel_اوچائي, &wind->requested.pixel_ويڪر, &wind->requested.pixel_اوچائي);

                wind->requested.logical_ويڪر = Pixel_منزل_نقطو(دري, wind->requested.pixel_ويڪر);
                wind->requested.logical_اوچائي = Pixel_منزل_نقطو(دري, wind->requested.pixel_اوچائي);
            }
        }
    } وإلا {
        // Fullscreen windows know their exact size.
        إذا (ويڪر == 0 || اوچائي == 0) {
            ويڪر = wind->requested.logical_ويڪر;
            اوچائي = wind->requested.logical_اوچائي;
        } وإلا {
            wind->requested.logical_ويڪر = ويڪر;
            wind->requested.logical_اوچائي = اوچائي;
        }

        إذا (wind->scale_منزل_display) {
            wind->requested.pixel_ويڪر = نقطو_منزل_Pixel(دري, ويڪر);
            wind->requested.pixel_اوچائي = نقطو_منزل_Pixel(دري, اوچائي);
        }
    }

    wind->آخري_configure.ويڪر = ويڪر;
    wind->آخري_configure.اوچائي = اوچائي;
    wind->آخري_configure.insets_apply = insets_apply;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->سرگرم = سرگرم;
    دري->tiled = tiled;
}

ساكن فراغ handle_xdg_toplevel_close(فراغ *معلومات, بنية xdg_toplevel *xdg_toplevel)
{
    SDL_دري_معلومات *دري = (SDL_دري_معلومات *)معلومات;
    SDL_Send_دري_Event(دري->sdlwindow, SDL_EVENT_دري_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ handle_xdg_toplevel_configure_bounds(فراغ *معلومات,
                                                 بنية xdg_toplevel *xdg_toplevel,
                                                 int32_t ويڪر, int32_t اوچائي)
{
    SDL_دري_معلومات *دري = (SDL_دري_معلومات *)معلومات;
    دري->toplevel_bounds.ويڪر = ويڪر;
    دري->toplevel_bounds.اوچائي = اوچائي;
}

ساكن فراغ handle_xdg_toplevel_wm_capabilities(فراغ *معلومات,
                                                بنية xdg_toplevel *xdg_toplevel,
                                                بنية wl_array *capabilities)
{
    SDL_دري_معلومات *wind = (SDL_دري_معلومات *)معلومات;
    تعداد xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        بدل (*wm_cap) {
        حالة XDG_TOPLEVEL_WM_CAPABILITIES_دري_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_دري_MENU;
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
                                       int32_t ويڪر,
                                       int32_t اوچائي)
{
    SDL_دري_معلومات *wind = (SDL_دري_معلومات *)معلومات;
    صحيح وٿي_x = 0, وٿي_y = 0;

    // Adjust the position if it was offset for libdecor
    Adjust_Popup_وٿي(wind->sdlwindow, &وٿي_x, &وٿي_y);
    x -= وٿي_x;
    y -= وٿي_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    إذا (ويڪر == 0 || اوچائي == 0) {
        ويڪر = wind->sdlwindow->floating.w;
        اوچائي = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    إذا (ويڪر != wind->آخري_configure.ويڪر || اوچائي != wind->آخري_configure.اوچائي) {
        wind->requested.logical_ويڪر = ويڪر;
        wind->requested.logical_اوچائي = اوچائي;

        إذا (wind->scale_منزل_display) {
            wind->requested.pixel_ويڪر = نقطو_منزل_Pixel(wind->sdlwindow, ويڪر);
            wind->requested.pixel_اوچائي = نقطو_منزل_Pixel(wind->sdlwindow, اوچائي);
        }
    }

    إذا (wind->scale_منزل_display) {
        x = نقطو_منزل_Pixel(wind->sdlwindow->والد, x);
        y = نقطو_منزل_Pixel(wind->sdlwindow->والد, y);
    }

    SDL_Send_دري_Event(wind->sdlwindow, SDL_EVENT_دري_MOVED, x, y);

    wind->آخري_configure.ويڪر = ويڪر;
    wind->آخري_configure.اوچائي = اوچائي;

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکٺو;
    }
}

ساكن فراغ handle_xdg_popup_پورو(فراغ *معلومات, بنية xdg_popup *xdg_popup)
{
    SDL_دري_معلومات *دري = (SDL_دري_معلومات *)معلومات;
    SDL_Send_دري_Event(دري->sdlwindow, SDL_EVENT_دري_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ handle_xdg_popup_repositioned(فراغ *معلومات,
                                          بنية xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

ساكن ثابت بنية xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_پورو,
    handle_xdg_popup_repositioned
};

ساكن فراغ handle_xdg_toplevel_decoration_configure(فراغ *معلومات,
                                                     بنية zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
                                                     uint32_t گهڻائي)
{
    SDL_دري *دري = (SDL_دري *)معلومات;
    SDL_دري_معلومات *اندروني = دري->اندروني;
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    /* If the compositor tries to force CSD anyway, bail on direct XDG support
     * and fall back to libdecor, it will handle these events from then on.
     *
     * To do this we have to fully unmap, then map with libdecor loaded.
     */
    إذا (گهڻائي == ZXDG_TOPLEVEL_DECORATION_V1_گهڻائي_CLIENT_SIDE) {
        إذا (دري->flags & SDL_دري_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            أرجع;
        }
        إذا (!Wayland_ڀريو_Libdecor(اندروني->wayland_معلومات, true)) {
            // libdecor isn't available, so no borders for you... oh well
            أرجع;
        }
        WAYLAND_wl_display_roundtrip(اندروني->wayland_معلومات->display);

        Wayland_Hide_دري(device, دري);
        اندروني->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_Show_دري(device, دري);
    }
}

ساكن ثابت بنية zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
    handle_xdg_toplevel_decoration_configure
};

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
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
ساكن فراغ OverrideLibdecorLimits(SDL_دري *دري)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (!libdecor_چوکٺو_get_min_content_سائيز) {
        libdecor_چوکٺو_سيٽ_min_content_سائيز(دري->اندروني->shell_surface.libdecor.چوکٺو, دري->min_w, دري->min_h);
    }
#وإلاإذا !SDL_LIBDECOR_CHECK_نسخو(0, 2, 0)
    libdecor_چوکٺو_سيٽ_min_content_سائيز(دري->اندروني->shell_surface.libdecor.چوکٺو, دري->min_w, دري->min_h);
#جيڪڏهن_پورو
}

/*
 * NOTE: Retrieves the minimum content size limits, if the function for doing so is available.
 *       On versions of libdecor that lack the minimum content size retrieval function, this
 *       function is a no-op.
 *
 *       Can be replaced with a direct call if the minimum required version of libdecor is raised
 *       to 0.1.2 or higher.
 */
ساكن فراغ Libdecor_Get_Min_Content_سائيز(بنية libdecor_چوکٺو *چوکٺو, صحيح *min_w, صحيح *min_h)
{
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (libdecor_چوکٺو_get_min_content_سائيز != عدم) {
        libdecor_چوکٺو_get_min_content_سائيز(چوکٺو, min_w, min_h);
    }
#وإلاإذا SDL_LIBDECOR_CHECK_نسخو(0, 2, 0)
    libdecor_چوکٺو_get_min_content_سائيز(چوکٺو, min_w, min_h);
#جيڪڏهن_پورو
}

ساكن فراغ decoration_چوکٺو_configure(بنية libdecor_چوکٺو *چوکٺو,
                                       بنية libdecor_configuration *configuration,
                                       فراغ *user_معلومات_2)
{
    SDL_دري_معلومات *wind = (SDL_دري_معلومات *)user_معلومات_2;
    SDL_دري *دري = wind->sdlwindow;

    تعداد libdecor_دري_state دري_state;
    صحيح ويڪر, اوچائي;

    bool سرگرم = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    ساكن ثابت تعداد libdecor_دري_state tiled_حالتون = (LIBDECOR_دري_STATE_TILED_کاٻو | LIBDECOR_دري_STATE_TILED_ساڄو |
                                                            LIBDECOR_دري_STATE_TILED_چوٽي | LIBDECOR_دري_STATE_TILED_BOTTOM);

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        Libdecor_Get_Min_Content_سائيز(چوکٺو, &wind->system_limits.min_ويڪر_2, &wind->system_limits.min_اوچائي_2);
    }

    // Window State
    إذا (libdecor_configuration_get_دري_state(configuration, &دري_state)) {
        fullscreen = (دري_state & LIBDECOR_دري_STATE_FULLSCREEN) != 0;
        maximized = (دري_state & LIBDECOR_دري_STATE_MAXIMIZED) != 0;
        سرگرم = (دري_state & LIBDECOR_دري_STATE_سرگرم) != 0;
        tiled = (دري_state & tiled_حالتون) != 0;
#إذا SDL_LIBDECOR_CHECK_نسخو(0, 2, 0)
        suspended = (دري_state & LIBDECOR_دري_STATE_SUSPENDED) != 0;
#جيڪڏهن_پورو
#إذا SDL_LIBDECOR_CHECK_نسخو(0, 3, 0)
        resizing = (دري_state & LIBDECOR_دري_STATE_RESIZING) != 0;

        إذا (دري_state & LIBDECOR_دري_STATE_CONSTRAINED_کاٻو) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_کاٻو;
        }
        إذا (دري_state & LIBDECOR_دري_STATE_CONSTRAINED_ساڄو) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ساڄو;
        }
        إذا (دري_state & LIBDECOR_دري_STATE_CONSTRAINED_چوٽي) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_چوٽي;
        }
        إذا (دري_state & LIBDECOR_دري_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#جيڪڏهن_پورو
    }
    ثابت bool floating = !(fullscreen || maximized || tiled);

    Update_دري_Fullscreen(دري, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from libdecor, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    إذا (سرگرم || !(دري->flags & SDL_دري_MINIMIZED)) {
        إذا (دري->flags & SDL_دري_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_RESTORED, 0, 0);
        }
        SDL_Send_دري_Event(دري,
                            (maximized && !fullscreen) ? SDL_EVENT_دري_MAXIMIZED : SDL_EVENT_دري_RESTORED,
                            0, 0);
    }

    /* For fullscreen or fixed-size windows we know our size.
     * Always assume the configure is wrong.
     */
    إذا (fullscreen) {
        إذا (!libdecor_configuration_get_content_سائيز(configuration, چوکٺو, &ويڪر, &اوچائي)) {
            ويڪر = wind->requested.logical_ويڪر;
            اوچائي = wind->requested.logical_اوچائي;
        } وإلا {
            // Fullscreen windows know their exact size.
            wind->requested.logical_ويڪر = ويڪر;
            wind->requested.logical_اوچائي = اوچائي;

            إذا (wind->scale_منزل_display) {
                wind->requested.pixel_ويڪر = نقطو_منزل_Pixel(دري, ويڪر);
                wind->requested.pixel_اوچائي = نقطو_منزل_Pixel(دري, اوچائي);
            }
        }
    } وإلا {
        إذا (!(دري->flags & SDL_دري_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            إذا (!wind->scale_منزل_display) {
                ويڪر = wind->requested.logical_ويڪر = دري->floating.w;
                اوچائي = wind->requested.logical_اوچائي = دري->floating.h;
            } وإلا {
                wind->requested.pixel_ويڪر = دري->floating.w;
                wind->requested.pixel_اوچائي = دري->floating.h;
                ويڪر = wind->requested.logical_ويڪر = Pixel_منزل_نقطو(دري, دري->floating.w);
                اوچائي = wind->requested.logical_اوچائي = Pixel_منزل_نقطو(دري, دري->floating.h);
            }

            OverrideLibdecorLimits(دري);
        } وإلا {
            /* XXX: The libdecor cairo plugin sends bogus content sizes that add the
             *      height of the title bar when transitioning from a fixed-size to
             *      floating state. Ignore the sent window dimensions in this case,
             *      in favor of the cached value to avoid the window increasing in
             *      size after every state transition.
             *
             *      https://gitlab.freedesktop.org/libdecor/libdecor/-/issues/34
             */
            إذا ((floating && (!wind->floating && !(دري->flags & SDL_دري_BORDERLESS))) ||
                !libdecor_configuration_get_content_سائيز(configuration, چوکٺو, &ويڪر, &اوچائي)) {
                ويڪر = 0;
                اوچائي = 0;
            }

            ثابت bool new_configure_سائيز = ويڪر != wind->آخري_configure.ويڪر || اوچائي != wind->آخري_configure.اوچائي;
            DetermineResizeAxis(wind, ويڪر, اوچائي, resizing);

            إذا (!ويڪر) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                إذا (floating) {
                    ويڪر = دري->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.ويڪر) {
                        ويڪر = SDL_min(wind->toplevel_bounds.ويڪر, ويڪر);
                    }
                } وإلا {
                    ويڪر = دري->windowed.w;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_ويڪر = ويڪر;
                } وإلا {
                    wind->requested.pixel_ويڪر = ويڪر;
                    ويڪر = wind->requested.logical_ويڪر = Pixel_منزل_نقطو(دري, ويڪر);
                }
            } وإلا {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                إذا (new_configure_سائيز &&
                    !(wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکٺو && wind->suspended != suspended)) {
                    wind->requested.logical_ويڪر = ويڪر;

                    إذا (wind->scale_منزل_display) {
                        wind->requested.pixel_ويڪر = نقطو_منزل_Pixel(دري, ويڪر);
                    }
                }
            }

            إذا (!اوچائي) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                إذا (floating) {
                    اوچائي = دري->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE && wind->toplevel_bounds.اوچائي) {
                        اوچائي = SDL_min(wind->toplevel_bounds.اوچائي, اوچائي);
                    }
                } وإلا {
                    اوچائي = دري->windowed.h;
                }

                إذا (!wind->scale_منزل_display) {
                    wind->requested.logical_اوچائي = اوچائي;
                } وإلا {
                    wind->requested.pixel_اوچائي = اوچائي;
                    اوچائي = wind->requested.logical_اوچائي = Pixel_منزل_نقطو(دري, اوچائي);
                }
            } وإلا {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                إذا (new_configure_سائيز &&
                    !(wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکٺو && wind->suspended != suspended)) {
                    wind->requested.logical_اوچائي = اوچائي;

                    إذا (wind->scale_منزل_display) {
                        wind->requested.pixel_اوچائي = نقطو_منزل_Pixel(دري, اوچائي);
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
                ApplyGeometryLimits(دري, wind->requested.logical_ويڪر, wind->requested.logical_اوچائي, &wind->requested.logical_ويڪر, &wind->requested.logical_اوچائي);
            } وإلا {
                ApplyGeometryLimits(دري, wind->requested.pixel_ويڪر, wind->requested.pixel_اوچائي, &wind->requested.pixel_ويڪر, &wind->requested.pixel_اوچائي);

                wind->requested.logical_ويڪر = Pixel_منزل_نقطو(دري, wind->requested.pixel_ويڪر);
                wind->requested.logical_اوچائي = Pixel_منزل_نقطو(دري, wind->requested.pixel_اوچائي);
            }
        }
    }

    // Store the new state.
    ثابت bool started_resize = !wind->resizing && resizing;
    wind->آخري_configure.ويڪر = ويڪر;
    wind->آخري_configure.اوچائي = اوچائي;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->سرگرم = سرگرم;
    دري->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#إذا SDL_LIBDECOR_CHECK_نسخو(0, 3, 0)
    تعداد libdecor_wm_capabilities caps;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    إذا (libdecor_چوکٺو_get_wm_capabilities) {
        caps = libdecor_چوکٺو_get_wm_capabilities(wind->shell_surface.libdecor.چوکٺو);
#وإلا
    caps = libdecor_چوکٺو_get_wm_capabilities(wind->shell_surface.libdecor.چوکٺو);
    {
#جيڪڏهن_پورو
        wind->wm_caps = 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_دري_MENU ? WAYLAND_WM_CAPS_دري_MENU : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MAXIMIZE ? WAYLAND_WM_CAPS_MAXIMIZE : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_FULLSCREEN ? WAYLAND_WM_CAPS_FULLSCREEN : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MINIMIZE ? WAYLAND_WM_CAPS_MINIMIZE : 0;
    }
#جيڪڏهن_پورو

    إذا (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        Configure_دري_Geometry(دري);
        بنية libdecor_state *state = libdecor_state_new(wind->current.logical_ويڪر, wind->current.logical_اوچائي);
        libdecor_چوکٺو_commit(چوکٺو, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        إذا (started_resize) {
            SDL_Send_دري_Event(دري, SDL_EVENT_دري_EXPOSED, 0, 0);
        }
    }

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE) {
        wind->shell_surface_حالت = WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکٺو;
    }
}

ساكن فراغ decoration_چوکٺو_close(بنية libdecor_چوکٺو *چوکٺو, فراغ *user_معلومات_2)
{
    SDL_Send_دري_Event(((SDL_دري_معلومات *)user_معلومات_2)->sdlwindow, SDL_EVENT_دري_CLOSE_REQUESTED, 0, 0);
}

ساكن فراغ decoration_چوکٺو_commit(بنية libdecor_چوکٺو *چوکٺو, فراغ *user_معلومات_2)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_دري_معلومات *wind = (SDL_دري_معلومات *)user_معلومات_2;
    إذا (!wind->suspended && wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        SDL_Send_دري_Event(wind->sdlwindow, SDL_EVENT_دري_EXPOSED, 0, 0);
    }
}

ساكن فراغ decoration_dismiss_popup(بنية libdecor_چوکٺو *چوکٺو, ثابت حرف *seat_name, فراغ *user_معلومات_2)
{
    // NOP
}

#إذا SDL_LIBDECOR_CHECK_نسخو(0, 3, 0)
ساكن فراغ decoration_چوکٺو_bounds(بنية libdecor_چوکٺو *چوکٺو, صحيح ويڪر, صحيح اوچائي, فراغ *user_معلومات_2)
{
    SDL_دري_معلومات *دري = (SDL_دري_معلومات *)user_معلومات_2;
    دري->toplevel_bounds.ويڪر = ويڪر;
    دري->toplevel_bounds.اوچائي = اوچائي;
}
#جيڪڏهن_پورو

ساكن بنية libdecor_چوکٺو_interface libdecor_چوکٺو_interface = {
    decoration_چوکٺو_configure,
    decoration_چوکٺو_close,
    decoration_چوکٺو_commit,
    decoration_dismiss_popup,
#إذا SDL_LIBDECOR_CHECK_نسخو(0, 3, 0)
    decoration_چوکٺو_bounds
#جيڪڏهن_پورو
};
#جيڪڏهن_پورو

ساكن فراغ Wayland_Handle_Preferred_Scale_بدليو(SDL_دري_معلومات *دري_معلومات_2, مزدوج ضرب_ڪندڙ)
{
    ثابت مزدوج old_ضرب_ڪندڙ = دري_معلومات_2->scale_ضرب_ڪندڙ_2;

    // Round the scale factor if viewports aren't available.
    إذا (!دري_معلومات_2->viewport) {
        ضرب_ڪندڙ = SDL_ceil(ضرب_ڪندڙ);
    }

    إذا (ضرب_ڪندڙ != old_ضرب_ڪندڙ) {
        دري_معلومات_2->scale_ضرب_ڪندڙ_2 = ضرب_ڪندڙ;

        إذا (دري_معلومات_2->scale_منزل_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            إذا (دري_معلومات_2->floating) {
                /* Some compositors will send a configure event immediately after a scale event, however,
                 * this event can contain the old logical size, and should be ignored, or the window can
                 * incorrectly change size when moved between displays with differing scale factors.
                 *
                 * Store the last requested logical size as the last configure size, so a configure event
                 * with the old size will be ignored. Configure sizes are in window geometry space,
                 * so subtract any border insets.
                 */
                BorderInsets insets;
                GetBorderInsets(دري_معلومات_2->sdlwindow, &insets);
                دري_معلومات_2->آخري_configure.ويڪر = SDL_max(دري_معلومات_2->requested.logical_ويڪر - (insets.کاٻو + insets.ساڄو), 1);
                دري_معلومات_2->آخري_configure.اوچائي = SDL_max(دري_معلومات_2->requested.logical_اوچائي - (insets.چوٽي + insets.bottom), 1);

                دري_معلومات_2->requested.logical_ويڪر = Pixel_منزل_نقطو(دري_معلومات_2->sdlwindow, دري_معلومات_2->requested.pixel_ويڪر);
                دري_معلومات_2->requested.logical_اوچائي = Pixel_منزل_نقطو(دري_معلومات_2->sdlwindow, دري_معلومات_2->requested.pixel_اوچائي);
            } وإلا {
                دري_معلومات_2->requested.pixel_ويڪر = نقطو_منزل_Pixel(دري_معلومات_2->sdlwindow, دري_معلومات_2->requested.logical_ويڪر);
                دري_معلومات_2->requested.pixel_اوچائي = نقطو_منزل_Pixel(دري_معلومات_2->sdlwindow, دري_معلومات_2->requested.logical_اوچائي);
            }
        }

        إذا (دري_معلومات_2->sdlwindow->flags & SDL_دري_مٿاهون_PIXEL_DENSITY || دري_معلومات_2->scale_منزل_display) {
            Configure_دري_Geometry(دري_معلومات_2->sdlwindow);
            Commit_Libdecor_چوکٺو(دري_معلومات_2->sdlwindow);
        }
    }
}

ساكن فراغ Wayland_Maybe_Update_Scale_ضرب_ڪندڙ(SDL_دري_معلومات *دري)
{
    مزدوج ضرب_ڪندڙ;
    صحيح i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    إذا (دري->fractional_scale || wl_surface_get_نسخو(دري->surface) >= WL_SURFACE_PREFERRED_بفر_SCALE_SINCE_نسخو) {
        أرجع;
    }

    إذا (دري->انگ_outputs != 0) {
        // Check every display's factor, use the highest
        ضرب_ڪندڙ = 0.0;
        لكل (i = 0; i < دري->انگ_outputs; i++) {
            SDL_Display_معلومات *اندروني = دري->outputs[i];
            ضرب_ڪندڙ = SDL_max(ضرب_ڪندڙ, اندروني->scale_ضرب_ڪندڙ_2);
        }
    } وإلا {
        // All outputs removed, just fall back.
        ضرب_ڪندڙ = دري->scale_ضرب_ڪندڙ_2;
    }

    Wayland_Handle_Preferred_Scale_بدليو(دري, ضرب_ڪندڙ);
}

فراغ Wayland_Remove_Output_From_دري(SDL_دري_معلومات *دري, SDL_Display_معلومات *display_معلومات)
{
    لكل (صحيح i = 0; i < دري->انگ_outputs; i++) {
        إذا (دري->outputs[i] == display_معلومات) { // remove this one
            إذا (i == (دري->انگ_outputs - 1)) {
                دري->outputs[i] = عدم;
            } وإلا {
                SDL_memmove(&دري->outputs[i],
                            &دري->outputs[i + 1],
                            حجم(SDL_Display_معلومات *) * ((دري->انگ_outputs - i) - 1));
            }
            دري->انگ_outputs--;
            i--;
        }
    }

    إذا (دري->انگ_outputs == 0) {
        SDL_free(دري->outputs);
        دري->outputs = عدم;
    } وإلا إذا (!دري->is_fullscreen || دري->انگ_outputs == 1) {
        Wayland_Update_دري_Position(دري->sdlwindow);
        Wayland_Maybe_Update_Scale_ضرب_ڪندڙ(دري);
    }
}

ساكن فراغ handle_surface_enter(فراغ *معلومات, بنية wl_surface *surface, بنية wl_output *output)
{
    SDL_دري_معلومات *دري = معلومات;
    SDL_Display_معلومات *اندروني = wl_output_get_user_معلومات(output);
    SDL_Display_معلومات **new_outputs;

    إذا (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        أرجع;
    }

    new_outputs = SDL_realloc(دري->outputs,
                              حجم(SDL_Display_معلومات *) * (دري->انگ_outputs + 1));
    إذا (!new_outputs) {
        أرجع;
    }
    دري->outputs = new_outputs;
    دري->outputs[دري->انگ_outputs++] = اندروني;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    إذا (!دري->is_fullscreen || دري->انگ_outputs == 1) {
        Wayland_Update_دري_Position(دري->sdlwindow);
        Wayland_Maybe_Update_Scale_ضرب_ڪندڙ(دري);
    }
}

ساكن فراغ handle_surface_leave(فراغ *معلومات, بنية wl_surface *surface, بنية wl_output *output)
{
    SDL_دري_معلومات *دري = (SDL_دري_معلومات *)معلومات;

    إذا (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        أرجع;
    }

    Wayland_Remove_Output_From_دري(دري, (SDL_Display_معلومات *)wl_output_get_user_معلومات(output));
}

ساكن فراغ handle_surface_preferred_بفر_scale(فراغ *معلومات, بنية wl_surface *wl_surface, int32_t ضرب_ڪندڙ)
{
    SDL_دري_معلومات *wind = معلومات;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    إذا (!wind->fractional_scale) {
        Wayland_Handle_Preferred_Scale_بدليو(معلومات, (مزدوج)ضرب_ڪندڙ);
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
    ثابت مزدوج ضرب_ڪندڙ = (مزدوج)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_Handle_Preferred_Scale_بدليو(معلومات, ضرب_ڪندڙ);
}

ساكن ثابت بنية wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

ساكن فراغ frog_preferred_metadata_handler(فراغ *معلومات, بنية frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
                                            uint32_t output_display_primary_red_x, uint32_t output_display_primary_red_y,
                                            uint32_t output_display_primary_green_x, uint32_t output_display_primary_green_y,
                                            uint32_t output_display_primary_blue_x, uint32_t output_display_primary_blue_y,
                                            uint32_t output_white_نقطو_x, uint32_t output_white_نقطو_y,
                                            uint32_t max_luminance, uint32_t min_luminance,
                                            uint32_t max_ڀريل_چوکٺو_luminance)
{
    SDL_دري_معلومات *wind = (SDL_دري_معلومات *)معلومات;
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
    حالة FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SCRGB_لڪيري:
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
    SDL_سيٽ_دري_HDRProperties(wind->sdlwindow, &HDR, true);
}

ساكن ثابت بنية frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


ساكن فراغ handle_surface_feedback_preferred_changed2(فراغ *معلومات,
                                                       بنية wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t سڃاڻپ_عنصر_hi, uint32_t سڃاڻپ_عنصر_lo)
{
    SDL_دري_معلومات *wind = (SDL_دري_معلومات *)معلومات;
    Wayland_Get_Color_Info_For_دري(wind, false);
}

ساكن فراغ handle_surface_feedback_preferred_بدليو(فراغ *معلومات,
                                                      بنية wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t سڃاڻپ_عنصر)
{
    handle_surface_feedback_preferred_changed2(معلومات, wp_color_management_surface_feedback_v1, 0, سڃاڻپ_عنصر);
}

ساكن ثابت بنية wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_بدليو,
    handle_surface_feedback_preferred_changed2
};

ساكن فراغ Wayland_سيٽ_Keyboard_Focus(SDL_دري *دري, bool سيٽ_focus)
{
    SDL_دري *toplevel = دري;

    // Find the toplevel parent
    طالما (SDL_دري_IS_POPUP(toplevel)) {
        toplevel = toplevel->والد;
    }

    toplevel->keyboard_focus = دري;

    إذا (سيٽ_focus && !دري->is_hiding && !دري->is_destroying) {
        SDL_سيٽ_Keyboard_Focus(دري);
    }
}

bool Wayland_سيٽ_دري_ڪاميابي_Test(SDL_دري *دري, bool enabled)
{
    أرجع true; // just succeed, the real work is done elsewhere.
}

ساكن بنية xdg_toplevel *Get_Toplevel_For_دري(SDL_دري_معلومات *wind)
{
    إذا (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکٺو) {
            أرجع libdecor_چوکٺو_get_xdg_toplevel(wind->shell_surface.libdecor.چوکٺو);
        } وإلا
#جيڪڏهن_پورو
            إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                أرجع wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    أرجع عدم;
}

bool Wayland_سيٽ_دري_والد(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري *والد_دري)
{
    SDL_دري_معلومات *ٻار_معلومات = دري->اندروني;
    SDL_دري_معلومات *والد_معلومات = والد_دري ? والد_دري->اندروني : عدم;

    ٻار_معلومات->reparenting_required = false;

    إذا (والد_معلومات && والد_معلومات->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        ٻار_معلومات->reparenting_required = true;
        أرجع true;
    }

    بنية xdg_toplevel *ٻار_toplevel = Get_Toplevel_For_دري(ٻار_معلومات);
    بنية xdg_toplevel *والد_toplevel = Get_Toplevel_For_دري(والد_معلومات);

    إذا (ٻار_toplevel) {
        xdg_toplevel_سيٽ_والد(ٻار_toplevel, والد_toplevel);
    }

    أرجع true;
}

bool Wayland_سيٽ_دري_Modal(SDL_VideoDevice *_this, SDL_دري *دري, bool modal)
{
    SDL_Video_معلومات *viddata = _this->اندروني;
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_دري_معلومات *والد_معلومات = دري->والد->اندروني;

    إذا (والد_معلومات->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        معلومات->reparenting_required = true;
        أرجع true;
    } وإلا {
        معلومات->reparenting_required = false;
    }

    بنية xdg_toplevel *toplevel = Get_Toplevel_For_دري(معلومات);

    إذا (toplevel) {
        إذا (viddata->xdg_wm_dialog_v1) {
            إذا (modal) {
                إذا (!معلومات->xdg_dialog_v1) {
                    معلومات->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_سيٽ_modal(معلومات->xdg_dialog_v1);
            } وإلا إذا (معلومات->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(معلومات->xdg_dialog_v1);
            }
        }
    }

    أرجع true;
}

ساكن فراغ Wayland_رجسٽر_Toplevel_For_Session(SDL_دري_معلومات *معلومات)
{
    بنية xdg_toplevel *toplevel = Get_Toplevel_For_دري(معلومات);
    إذا (!toplevel) {
        أرجع;
    }

    ثابت حرف *id = SDL_GetStringProperty(معلومات->sdlwindow->props, SDL_PROP_دري_WAYLAND_دري_ID_STRING, عدم);
    إذا (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_Video_معلومات *viddata = viddev->اندروني;

        إذا (viddata->xdg_toplevel_ٽيگ_manager) {
            xdg_toplevel_ٽيگ_manager_v1_سيٽ_toplevel_ٽيگ(viddata->xdg_toplevel_ٽيگ_manager, toplevel, id);
        }

        إذا (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            إذا (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    لكل (SDL_دري *w = viddev->windows; w; w = w->ايندڙ) {
                        SDL_دري_معلومات *d = w->اندروني;
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

ساكن فراغ Wayland_DestroyToplevelSession(SDL_دري_معلومات *معلومات)
{
    SDL_Video_معلومات *viddata = معلومات->wayland_معلومات;

    إذا (معلومات->xdg_toplevel_session) {
        ثابت حرف *id = SDL_GetStringProperty(معلومات->sdlwindow->props, SDL_PROP_دري_WAYLAND_دري_ID_STRING, عدم);

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
    SDL_دري_ID دري_ID = (SDL_دري_ID)((uintptr_t)معلومات);
    SDL_دري *دري = SDL_Get_دري_From_ID(دري_ID);

    إذا (دري && دري->اندروني) {
        SDL_دري_معلومات *wind = دري->اندروني;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

ساكن بنية wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

ساكن فراغ exported_handle_handler(فراغ *معلومات, بنية zxdg_exported_v2 *zxdg_exported_v2, ثابت حرف *handle)
{
    SDL_دري_معلومات *wind = (SDL_دري_معلومات *)معلومات;
    SDL_PropertiesID props = SDL_Get_دري_Properties(wind->sdlwindow);

    SDL_سيٽ_String_Property(props, SDL_PROP_دري_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

ساكن بنية zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

فراغ Wayland_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *c = _this->اندروني;
    SDL_دري_معلومات *معلومات = دري->اندروني;
    SDL_PropertiesID props = SDL_Get_دري_Properties(دري);

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
    إذا (دري->والد) {
        إذا (دري->والد->اندروني->shell_surface_حالت != WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
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
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        معلومات->shell_surface.libdecor.چوکٺو = libdecor_decorate(c->shell.libdecor,
                                                               معلومات->surface,
                                                               &libdecor_چوکٺو_interface,
                                                               معلومات);
        إذا (!معلومات->shell_surface.libdecor.چوکٺو) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } وإلا {
            libdecor_چوکٺو_سيٽ_app_id(معلومات->shell_surface.libdecor.چوکٺو, معلومات->app_id);
            libdecor_چوکٺو_map(معلومات->shell_surface.libdecor.چوکٺو);
            إذا (دري->flags & SDL_دري_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_چوکٺو_سيٽ_visibility(معلومات->shell_surface.libdecor.چوکٺو, false);
            }

            إذا (c->zxdg_exporter_v2) {
                معلومات->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, معلومات->surface);
                zxdg_exported_v2_جوڙيو_listener(معلومات->exported, &exported_v2_listener, معلومات);
            }

            إذا (c->xdg_toplevel_icon_manager_v1 && معلومات->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_سيٽ_icon(_this->اندروني->xdg_toplevel_icon_manager_v1,
                                                      libdecor_چوکٺو_get_xdg_toplevel(معلومات->shell_surface.libdecor.چوکٺو),
                                                      معلومات->xdg_toplevel_icon_v1);
            }

            SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_XDG_SURFACE_اشارو, libdecor_چوکٺو_get_xdg_surface(معلومات->shell_surface.libdecor.چوکٺو));
            SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_XDG_TOPLEVEL_اشارو, libdecor_چوکٺو_get_xdg_toplevel(معلومات->shell_surface.libdecor.چوکٺو));
        }
    } وإلا
#جيڪڏهن_پورو
    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        معلومات->shell_surface.xdg.surface = xdg_wm_بنياد_get_xdg_surface(c->shell.xdg, معلومات->surface);
        xdg_surface_سيٽ_user_معلومات(معلومات->shell_surface.xdg.surface, معلومات);
        xdg_surface_جوڙيو_listener(معلومات->shell_surface.xdg.surface, &_xdg_surface_listener, معلومات);
        SDL_سيٽ_اشارو_Property(SDL_Get_دري_Properties(دري), SDL_PROP_دري_WAYLAND_XDG_SURFACE_اشارو, معلومات->shell_surface.xdg.surface);

        إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_دري *والد = دري->والد;
            SDL_دري_معلومات *والد_معلومات = والد->اندروني;
            بنية xdg_surface *والد_xdg_surface = عدم;
            صحيح position_x = 0, position_y = 0;

            // Configure the popup parameters
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
            إذا (والد_معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                والد_xdg_surface = libdecor_چوکٺو_get_xdg_surface(والد_معلومات->shell_surface.libdecor.چوکٺو);
            } وإلا
#جيڪڏهن_پورو
            إذا (والد_معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    والد_معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                والد_xdg_surface = والد_معلومات->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            معلومات->shell_surface.xdg.popup.xdg_positioner = xdg_wm_بنياد_create_positioner(c->shell.xdg);
            xdg_positioner_سيٽ_anchor(معلومات->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_چوٽي_کاٻو);
            SDL_Rect والد_geometry;
            Get_دري_Geometry(والد->اندروني, &والد_geometry);
            xdg_positioner_سيٽ_anchor_rect(معلومات->shell_surface.xdg.popup.xdg_positioner, 0, 0, والد_geometry.w, والد_geometry.h);

            ثابت Uint32 constraint = دري->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_سيٽ_constraint_adjustment(معلومات->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_سيٽ_gravity(معلومات->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_ساڄو);
            xdg_positioner_سيٽ_سائيز(معلومات->shell_surface.xdg.popup.xdg_positioner, معلومات->current.logical_ويڪر, معلومات->current.logical_اوچائي);

            // Set the popup initial position
            position_x = دري->آخري_position_pending ? دري->pending.x : دري->x;
            position_y = دري->آخري_position_pending ? دري->pending.y : دري->y;
            EnsurePopupPositionIsValid(دري, &position_x, &position_y);
            إذا (معلومات->scale_منزل_display) {
                position_x = Pixel_منزل_نقطو(دري->والد, position_x);
                position_y = Pixel_منزل_نقطو(دري->والد, position_y);
            }
            Adjust_Popup_وٿي(دري, &position_x, &position_y);
            xdg_positioner_سيٽ_وٿي(معلومات->shell_surface.xdg.popup.xdg_positioner, position_x, position_y);

            // Assign the popup role
            معلومات->shell_surface.xdg.popup.xdg_popup = xdg_surface_get_popup(معلومات->shell_surface.xdg.surface,
                                                                                والد_xdg_surface,
                                                                                معلومات->shell_surface.xdg.popup.xdg_positioner);
            xdg_popup_جوڙيو_listener(معلومات->shell_surface.xdg.popup.xdg_popup, &_xdg_popup_listener, معلومات);

            إذا (دري->flags & SDL_دري_TOOLTIP) {
                بنية wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_جوڙيو(region, 0, 0, 0, 0);
                wl_surface_سيٽ_داخلا_region(معلومات->surface, region);
                wl_region_destroy(region);
            } وإلا إذا ((دري->flags & SDL_دري_POPUP_MENU) && !(دري->flags & SDL_دري_NOT_FOCUSABLE)) {
                Wayland_سيٽ_Keyboard_Focus(دري, true);
            }

            SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_XDG_POPUP_اشارو, معلومات->shell_surface.xdg.popup.xdg_popup);
            SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_XDG_POSITIONER_اشارو, معلومات->shell_surface.xdg.popup.xdg_positioner);
        } وإلا {
            معلومات->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(معلومات->shell_surface.xdg.surface);
            xdg_toplevel_سيٽ_app_id(معلومات->shell_surface.xdg.toplevel.xdg_toplevel, معلومات->app_id);
            xdg_toplevel_جوڙيو_listener(معلومات->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, معلومات);

            // Create the window decorations
            إذا (c->decoration_manager) {
                معلومات->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, معلومات->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_جوڙيو_listener(معلومات->server_decoration, &xdg_toplevel_decoration_listener, دري);
                ثابت تعداد zxdg_toplevel_decoration_v1_گهڻائي گهڻائي = !(دري->flags & SDL_دري_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_گهڻائي_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_گهڻائي_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_سيٽ_گهڻائي(معلومات->server_decoration, گهڻائي);
            }

            إذا (c->zxdg_exporter_v2) {
                معلومات->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, معلومات->surface);
                zxdg_exported_v2_جوڙيو_listener(معلومات->exported, &exported_v2_listener, معلومات);
            }

            إذا (c->xdg_toplevel_icon_manager_v1 && معلومات->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_سيٽ_icon(_this->اندروني->xdg_toplevel_icon_manager_v1,
                                                      معلومات->shell_surface.xdg.toplevel.xdg_toplevel,
                                                      معلومات->xdg_toplevel_icon_v1);
            }

            SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_XDG_TOPLEVEL_اشارو, معلومات->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    // Restore state that was set prior to this call
    Wayland_رجسٽر_Toplevel_For_Session(معلومات);
    Wayland_سيٽ_دري_والد(_this, دري, دري->والد);

    إذا (دري->flags & SDL_دري_MODAL) {
        Wayland_سيٽ_دري_Modal(_this, دري, true);
    }

    Wayland_سيٽ_دري_Title(_this, دري);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (معلومات->shell_surface.libdecor.چوکٺو) {
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
#جيڪڏهن_پورو
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
    معلومات->system_limits.min_ويڪر_2 = SDL_max(معلومات->system_limits.min_ويڪر_2, 1);
    معلومات->system_limits.min_اوچائي_2 = SDL_max(معلومات->system_limits.min_اوچائي_2, 1);

    /* Unlike the rest of window state we have to set this _after_ flushing the
     * display, because we need to create the decorations before possibly hiding
     * them immediately afterward.
     */
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        إذا (دري->windowed.w < معلومات->system_limits.min_ويڪر_2 ||
            دري->windowed.h < معلومات->system_limits.min_اوچائي_2) {

            // Warn if the window frame will be larger than the content surface.
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "Window dimensions (%i, %i) are smaller than the system enforced minimum (%i, %i); window borders will be larger than the content surface.",
                        دري->windowed.w, دري->windowed.h, معلومات->system_limits.min_ويڪر_2, معلومات->system_limits.min_اوچائي_2);

            معلومات->current.logical_ويڪر = SDL_max(دري->windowed.w, معلومات->system_limits.min_ويڪر_2);
            معلومات->current.logical_اوچائي = SDL_max(دري->windowed.h, معلومات->system_limits.min_اوچائي_2);
            Commit_Libdecor_چوکٺو(دري);
        }
    }
#جيڪڏهن_پورو
    Wayland_سيٽ_دري_Resizable(_this, دري, !!(دري->flags & SDL_دري_RESIZABLE));

    // We're finally done putting the window together, raise if possible
    إذا (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_دري_ACTIVATE_WHEN_SHOWN, true)) {
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
            Wayland_Raise_دري(_this, دري);
        }
    } وإلا {
        // Clear the ignored activation token, as it won't be used.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    }

    // No frame callback on an external surface, as it may already have one attached.
    إذا (!(دري->flags & SDL_دري_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        معلومات->surface_چوکٺو_callback = wl_surface_چوکٺو(معلومات->surface);
        wl_callback_جوڙيو_listener(معلومات->surface_چوکٺو_callback, &surface_چوکٺو_listener, معلومات);
    }

    معلومات->show_hide_sync_required = true;
    بنية wl_callback *cb = wl_display_sync(_this->اندروني->display);
    wl_callback_جوڙيو_listener(cb, &show_hide_sync_listener, (فراغ *)((uintptr_t)دري->id));

    معلومات->showing_دري = true;
    SDL_Send_دري_Event(دري, SDL_EVENT_دري_SHOWN, 0, 0);
    معلومات->showing_دري = false;

    // Send an exposure event to signal that the client should draw.
    SDL_Send_دري_Event(دري, SDL_EVENT_دري_EXPOSED, 0, 0);
}

ساكن فراغ Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_دري *popup)
{
    SDL_دري_معلومات *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    إذا (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_دري)) {
        أرجع;
    }
    popupdata = popup->اندروني;
    إذا (!popupdata) {
        أرجع;
    }

    // This may already be freed by a parent popup!
    إذا (popupdata->shell_surface.xdg.popup.xdg_popup == عدم) {
        أرجع;
    }

    إذا ((popup->flags & SDL_دري_POPUP_MENU) && !(popup->flags & SDL_دري_NOT_FOCUSABLE)) {
        SDL_دري *new_focus;
        ثابت bool سيٽ_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_سيٽ_Keyboard_Focus(new_focus, سيٽ_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = عدم;
    popupdata->shell_surface.xdg.popup.xdg_positioner = عدم;

    SDL_PropertiesID props = SDL_Get_دري_Properties(popup);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_XDG_POPUP_اشارو, عدم);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_XDG_POSITIONER_اشارو, عدم);
}

فراغ Wayland_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    SDL_دري_معلومات *wind = دري->اندروني;
    SDL_PropertiesID props = SDL_Get_دري_Properties(دري);

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

    إذا (wind->surface_چوکٺو_callback) {
        wl_callback_destroy(wind->surface_چوکٺو_callback);
        wind->surface_چوکٺو_callback = عدم;
    }

    إذا (wind->server_decoration) {
        zxdg_toplevel_decoration_v1_destroy(wind->server_decoration);
        wind->server_decoration = عدم;
    }

    // Clean up the export handle.
    إذا (wind->exported) {
        zxdg_exported_v2_destroy(wind->exported);
        wind->exported = عدم;

        SDL_سيٽ_String_Property(props, SDL_PROP_دري_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, عدم);
    }

    إذا (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = عدم;
    }

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.چوکٺو) {
            libdecor_چوکٺو_unref(wind->shell_surface.libdecor.چوکٺو);

            SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_XDG_SURFACE_اشارو, عدم);
            SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_XDG_TOPLEVEL_اشارو, عدم);
        }
    } وإلا
#جيڪڏهن_پورو
    {
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, دري);
        } وإلا إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_XDG_TOPLEVEL_اشارو, عدم);
        }

        إذا (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_XDG_SURFACE_اشارو, عدم);
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
    بنية wl_callback *cb = wl_display_sync(_this->اندروني->display);
    wl_callback_جوڙيو_listener(cb, &show_hide_sync_listener, (فراغ *)((uintptr_t)دري->id));
}

ساكن فراغ handle_xdg_activation_پورو(فراغ *معلومات,
                                       بنية xdg_activation_token_v1 *xdg_activation_token_v1,
                                       ثابت حرف *token)
{
    SDL_دري_معلومات *دري = معلومات;
    إذا (xdg_activation_token_v1 == دري->activation_token) {
        xdg_activation_v1_activate(دري->wayland_معلومات->activation_manager,
                                   token,
                                   دري->surface);
        xdg_activation_token_v1_destroy(دري->activation_token);
        دري->activation_token = عدم;
    }
}

ساكن ثابت بنية xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_پورو
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
ساكن فراغ Wayland_activate_دري(SDL_Video_معلومات *معلومات, SDL_دري_معلومات *هدف_wind, bool سيٽ_serial)
{
    SDL_WaylandSeat *seat = معلومات->آخري_implicit_grab_seat;
    SDL_دري_معلومات *focus = عدم;

    إذا (seat) {
        focus = seat->keyboard.focus;
        إذا (!focus) {
            focus = seat->اشارو_2.focus;
        }
    }

    بنية wl_surface *requesting_surface = focus ? focus->surface : عدم;

    إذا (معلومات->activation_manager) {
        إذا (هدف_wind->activation_token) {
            // We're about to overwrite this with a new request
            xdg_activation_token_v1_destroy(هدف_wind->activation_token);
        }

        هدف_wind->activation_token = xdg_activation_v1_get_activation_token(معلومات->activation_manager);
        xdg_activation_token_v1_جوڙيو_listener(هدف_wind->activation_token,
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
            xdg_activation_token_v1_سيٽ_surface(هدف_wind->activation_token, requesting_surface);
        }
        إذا (سيٽ_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_سيٽ_serial(هدف_wind->activation_token, seat->آخري_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(هدف_wind->activation_token);
    }
}

فراغ Wayland_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *viddata = _this->اندروني;
    SDL_دري_معلومات *wind = دري->اندروني;

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
    Wayland_activate_دري(_this->اندروني, دري->اندروني, true);
}

bool Wayland_Flash_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_FlashOperation operation)
{
    /* Not setting the serial will specify 'urgency' without switching focus as per
     * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
     */
    Wayland_activate_دري(_this->اندروني, دري->اندروني, false);
    أرجع true;
}

SDL_Fullscreen_نتيجو Wayland_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_دري_معلومات *wind = دري->اندروني;
    بنية wl_output *output = display->اندروني->output;

    // Custom surfaces have no toplevel to make fullscreen.
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        أرجع SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    إذا (wind->showing_دري && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    إذا (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->اندروني->display);
    }

    // Flushing old events pending a new one, ignore this request.
    إذا (wind->drop_fullscreen_درخواستون) {
        أرجع SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_درخواستون = true;
    FlushPendingEvents(دري);
    wind->drop_fullscreen_درخواستون = false;

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
        إذا (!دري->fullscreen_exclusive) {
            إذا (دري->undefined_x || دري->undefined_y ||
                (wind->انگ_outputs && !دري->آخري_position_pending)) {
                output = عدم;
            }
        }

        // Commit to set any pending size or limit data.
        إذا (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        سيٽ_Fullscreen(دري, output, !!fullscreen);
    } وإلا إذا (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        إذا (wind->آخري_display_ID != display->id) {
            wind->fullscreen_was_positioned = true;
            سيٽ_Fullscreen(دري, output, true);
        } وإلا {
            Configure_دري_Geometry(دري);
            Commit_Libdecor_چوکٺو(دري);

            أرجع SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    أرجع SDL_FULLSCREEN_PENDING;
}

فراغ Wayland_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    // Drop restore requests when showing the window.
    إذا (wind->showing_دري) {
        أرجع;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    إذا (!(دري->flags & (SDL_دري_FULLSCREEN | SDL_دري_MAXIMIZED)) &&
        !wind->pending_state_deadline_ڳڻپ) {
        أرجع;
    }

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکٺو) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_چوکٺو_unset_maximized(wind->shell_surface.libdecor.چوکٺو);
        جوڙيو_Pending_State_Sync(wind);
    } وإلا
#جيڪڏهن_پورو
        // Note that xdg-shell does NOT provide a way to unset minimize!
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
                أرجع; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            جوڙيو_Pending_State_Sync(wind);
        }
}

فراغ Wayland_سيٽ_دري_Bordered(SDL_VideoDevice *_this, SDL_دري *دري, bool bordered)
{
    SDL_دري_معلومات *wind = دري->اندروني;
    ثابت SDL_Video_معلومات *viddata = (ثابت SDL_Video_معلومات *)_this->اندروني;

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.چوکٺو) {
            libdecor_چوکٺو_سيٽ_visibility(wind->shell_surface.libdecor.چوکٺو, bordered);
        }
    } وإلا
#جيڪڏهن_پورو
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا ((viddata->decoration_manager) && (wind->server_decoration)) {
            ثابت تعداد zxdg_toplevel_decoration_v1_گهڻائي گهڻائي = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_گهڻائي_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_گهڻائي_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_سيٽ_گهڻائي(wind->server_decoration, گهڻائي);
        }
    }
}

فراغ Wayland_سيٽ_دري_Resizable(SDL_VideoDevice *_this, SDL_دري *دري, bool resizable)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    سيٽ_Min_Max_Dimensions(دري);
    Commit_Libdecor_چوکٺو(دري);

    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        wind->pending_state_commit = true;
    }
}

فراغ Wayland_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    إذا (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->اندروني->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    إذا (!(دري->flags & SDL_دري_FULLSCREEN) && (دري->flags & SDL_دري_MAXIMIZED) &&
        !wind->pending_state_deadline_ڳڻپ) {
        أرجع;
    }

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکٺو) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        إذا (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_چوکٺو_سيٽ_maximized(wind->shell_surface.libdecor.چوکٺو);
        جوڙيو_Pending_State_Sync(wind);
    } وإلا
#جيڪڏهن_پورو
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        إذا (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_سيٽ_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        جوڙيو_Pending_State_Sync(wind);
    }
}

فراغ Wayland_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    إذا (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        أرجع;
    }

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (!wind->shell_surface.libdecor.چوکٺو) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_چوکٺو_سيٽ_minimized(wind->shell_surface.libdecor.چوکٺو);
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_MINIMIZED, 0, 0);
    } وإلا
#جيڪڏهن_پورو
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel == عدم) {
            أرجع; // Can't do anything yet, wait for ShowWindow
        }
        xdg_toplevel_سيٽ_minimized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        SDL_Send_دري_Event(دري, SDL_EVENT_دري_MINIMIZED, 0, 0);
    }
}

bool Wayland_سيٽ_دري_Mouse_Rect(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    /* This may look suspiciously like SetWindowGrab, despite SetMouseRect not
     * implicitly doing a grab. And you're right! Wayland doesn't let us mess
     * around with mouse focus whatsoever, so it just happens to be that the
     * work that we can do in these two functions ends up being the same.
     *
     * Just know that this call lets you confine with a rect, SetWindowGrab
     * lets you confine without a rect.
     */
    إذا (!معلومات->اشارو_constraints) {
        أرجع SDL_سيٽ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_اشارو_Grabs(معلومات, دري->اندروني);
    أرجع true;
}

bool Wayland_سيٽ_دري_Mouse_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    إذا (!معلومات->اشارو_constraints) {
        أرجع SDL_سيٽ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_اشارو_Grabs(معلومات, دري->اندروني);
    أرجع true;
}

bool Wayland_سيٽ_دري_Keyboard_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    إذا (!معلومات->ڪنجي_inhibitor_manager) {
        أرجع SDL_سيٽ_Error("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(معلومات, دري->اندروني);
    أرجع true;
}

bool Wayland_Reconfigure_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري_Flags flags)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

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
    إذا (flags & SDL_دري_OPENGL) {
        إذا (!معلومات->egl_دري) {
            معلومات->egl_دري = WAYLAND_wl_egl_دري_create(معلومات->surface, معلومات->current.pixel_ويڪر, معلومات->current.pixel_اوچائي);
        }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, دري, (Native_دري_Type)معلومات->egl_دري);

        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            أرجع false; // SDL_EGL_CreateSurface should have set the error.
        }
#جيڪڏهن_پورو

        إذا (!معلومات->gles_مٽا_سٽا_چوکٺو_event_قطار) {
            معلومات->gles_مٽا_سٽا_چوکٺو_event_قطار = WAYLAND_wl_display_create_قطار(معلومات->wayland_معلومات->display);
            معلومات->gles_مٽا_سٽا_چوکٺو_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(معلومات->surface);
            WAYLAND_wl_proxy_سيٽ_قطار((بنية wl_proxy *)معلومات->gles_مٽا_سٽا_چوکٺو_surface_wrapper, معلومات->gles_مٽا_سٽا_چوکٺو_event_قطار);
            معلومات->gles_مٽا_سٽا_چوکٺو_callback = wl_surface_چوکٺو(معلومات->gles_مٽا_سٽا_چوکٺو_surface_wrapper);
            wl_callback_جوڙيو_listener(معلومات->gles_مٽا_سٽا_چوکٺو_callback, &gles_مٽا_سٽا_چوکٺو_listener, معلومات);
        }
    } وإلا {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
        إذا (معلومات->egl_surface) {
            SDL_EGL_DestroySurface(_this, معلومات->egl_surface);
            معلومات->egl_surface = EGL_NO_SURFACE;
        }
#جيڪڏهن_پورو

        إذا (معلومات->egl_دري) {
            WAYLAND_wl_egl_دري_destroy(معلومات->egl_دري);
            معلومات->egl_دري = عدم;
        }

        إذا (معلومات->gles_مٽا_سٽا_چوکٺو_callback) {
            wl_callback_destroy(معلومات->gles_مٽا_سٽا_چوکٺو_callback);
            معلومات->gles_مٽا_سٽا_چوکٺو_callback = عدم;
        }

        إذا (معلومات->gles_مٽا_سٽا_چوکٺو_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(معلومات->gles_مٽا_سٽا_چوکٺو_surface_wrapper);
            معلومات->gles_مٽا_سٽا_چوکٺو_surface_wrapper = عدم;
        }

        إذا (معلومات->gles_مٽا_سٽا_چوکٺو_event_قطار) {
            WAYLAND_wl_event_قطار_destroy(معلومات->gles_مٽا_سٽا_چوکٺو_event_قطار);
            معلومات->gles_مٽا_سٽا_چوکٺو_event_قطار = عدم;
        }
    }

    أرجع true;
}

bool Wayland_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props)
{
    SDL_دري_معلومات *معلومات;
    SDL_Video_معلومات *c = _this->اندروني;
    بنية wl_surface *external_surface = (بنية wl_surface *)SDL_Get_اشارو_Property(create_props, SDL_PROP_دري_CREATE_WAYLAND_WL_SURFACE_اشارو,
                                                                               (بنية wl_surface *)SDL_Get_اشارو_Property(create_props, "sdl2-compat.external_window", عدم));
    ثابت bool custom_surface_role = (external_surface != عدم) || SDL_GetBooleanProperty(create_props, SDL_PROP_دري_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    ثابت bool create_egl_دري = !!(دري->flags & SDL_دري_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_دري_CREATE_WAYLAND_CREATE_EGL_دري_BOOLEAN, false);

    معلومات = SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        أرجع false;
    }

    دري->اندروني = معلومات;
    معلومات->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_دري_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    إذا (دري->x == SDL_WINDOWPOS_UNDEFINED) {
        دري->x = 0;
    }
    إذا (دري->y == SDL_WINDOWPOS_UNDEFINED) {
        دري->y = 0;
    }

    معلومات->wayland_معلومات = c;
    معلومات->sdlwindow = دري;

    // Default to all capabilities
    معلومات->wm_caps = WAYLAND_WM_CAPS_ALL;

    معلومات->scale_ضرب_ڪندڙ_2 = 1.0;

    إذا (SDL_دري_IS_POPUP(دري)) {
        معلومات->scale_منزل_display = دري->والد->اندروني->scale_منزل_display;
        معلومات->scale_ضرب_ڪندڙ_2 = دري->والد->اندروني->scale_ضرب_ڪندڙ_2;
        EnsurePopupPositionIsValid(دري, &دري->x, &دري->y);
    } وإلا {
        لكل (صحيح i = 0; i < _this->انگ_displays; i++) {
            معلومات->scale_ضرب_ڪندڙ_2 = SDL_max(معلومات->scale_ضرب_ڪندڙ_2, _this->displays[i]->اندروني->scale_ضرب_ڪندڙ_2);
        }
    }

    معلومات->outputs = عدم;
    معلومات->انگ_outputs = 0;
    معلومات->scale_منزل_display = c->scale_منزل_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    معلومات->app_id = SDL_strdup(SDL_GetAppID());

    إذا (!معلومات->scale_منزل_display) {
        معلومات->requested.logical_ويڪر = دري->floating.w;
        معلومات->requested.logical_اوچائي = دري->floating.h;
    } وإلا {
        معلومات->requested.logical_ويڪر = Pixel_منزل_نقطو(دري, دري->floating.w);
        معلومات->requested.logical_اوچائي = Pixel_منزل_نقطو(دري, دري->floating.h);
        معلومات->requested.pixel_ويڪر = دري->floating.w;
        معلومات->requested.pixel_اوچائي = دري->floating.h;
    }

    إذا (!external_surface) {
        معلومات->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_جوڙيو_listener(معلومات->surface, &surface_listener, معلومات);
        wl_surface_سيٽ_user_معلومات(معلومات->surface, معلومات);
        SDL_WAYLAND_رجسٽر_surface(معلومات->surface);
    } وإلا {
        دري->flags |= SDL_دري_EXTERNAL;
        معلومات->surface = external_surface;

        /* External surfaces are registered by being put in a list, as changing tags or userdata
         * can cause problems with external toolkits.
         */
        Wayland_جوڙيو_دري_معلومات_منزل_External_List(معلومات);
    }

    /* Always attach a viewport and fractional scale manager if available and the surface is not custom/external,
     * or the custom/external surface was explicitly flagged as high pixel density aware, which signals that the
     * application wants SDL to handle scaling.
     */
    إذا (!custom_surface_role || (دري->flags & SDL_دري_مٿاهون_PIXEL_DENSITY)) {
        إذا (c->viewporter) {
            معلومات->viewport = wp_viewporter_get_viewport(c->viewporter, معلومات->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_سيٽ_ذريعو(معلومات->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        إذا (c->fractional_scale_manager) {
            معلومات->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, معلومات->surface);
            wp_fractional_scale_v1_جوڙيو_listener(معلومات->fractional_scale, &fractional_scale_listener, معلومات);
        }
    }

    إذا (!custom_surface_role) {
        إذا (c->wp_color_manager_v1) {
            معلومات->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, معلومات->surface);
            wp_color_management_surface_feedback_v1_جوڙيو_listener(معلومات->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, معلومات);
            Wayland_Get_Color_Info_For_دري(معلومات, true);
        } وإلا إذا (c->frog_color_management_factory_v1) {
            معلومات->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, معلومات->surface);
            frog_color_managed_surface_جوڙيو_listener(معلومات->frog_color_managed_surface, &frog_surface_listener, معلومات);
        }

        إذا (c->wp_alpha_modifier_v1) {
            معلومات->wp_alpha_modifier_surface_v1 = wp_alpha_modifier_v1_get_surface(c->wp_alpha_modifier_v1, معلومات->surface);
            wp_alpha_modifier_surface_v1_سيٽ_multiplier(معلومات->wp_alpha_modifier_surface_v1, SDL_MAX_UINT32);
        }
    }

    // Must be called before EGL configuration to set the drawable backbuffer size.
    Configure_دري_Geometry(دري);

    /* Fire a callback when the compositor wants a new frame rendered.
     * Right now this only matters for OpenGL; we use this callback to add a
     * wait timeout that avoids getting deadlocked by the compositor when the
     * window isn't visible.
     */
    إذا (دري->flags & SDL_دري_OPENGL) {
        معلومات->gles_مٽا_سٽا_چوکٺو_event_قطار = WAYLAND_wl_display_create_قطار(معلومات->wayland_معلومات->display);
        معلومات->gles_مٽا_سٽا_چوکٺو_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(معلومات->surface);
        WAYLAND_wl_proxy_سيٽ_قطار((بنية wl_proxy *)معلومات->gles_مٽا_سٽا_چوکٺو_surface_wrapper, معلومات->gles_مٽا_سٽا_چوکٺو_event_قطار);
        معلومات->gles_مٽا_سٽا_چوکٺو_callback = wl_surface_چوکٺو(معلومات->gles_مٽا_سٽا_چوکٺو_surface_wrapper);
        wl_callback_جوڙيو_listener(معلومات->gles_مٽا_سٽا_چوکٺو_callback, &gles_مٽا_سٽا_چوکٺو_listener, معلومات);
    }

    إذا (دري->flags & SDL_دري_TRANSPARENT) {
        إذا (_this->gl_config.alpha_سائيز == 0) {
            _this->gl_config.alpha_سائيز = 8;
        }
    }

    إذا (create_egl_دري) {
        معلومات->egl_دري = WAYLAND_wl_egl_دري_create(معلومات->surface, معلومات->current.pixel_ويڪر, معلومات->current.pixel_اوچائي);
    }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    إذا (دري->flags & SDL_دري_OPENGL) {
        // Create the GLES window surface
        معلومات->egl_surface = SDL_EGL_CreateSurface(_this, دري, (Native_دري_Type)معلومات->egl_دري);

        إذا (معلومات->egl_surface == EGL_NO_SURFACE) {
            أرجع false; // SDL_EGL_CreateSurface should have set error
        }
    }
#جيڪڏهن_پورو

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    إذا (!custom_surface_role) {
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
        إذا (c->shell.libdecor && !SDL_دري_IS_POPUP(دري)) {
            معلومات->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } وإلا
#جيڪڏهن_پورو
            إذا (c->shell.xdg) {
            إذا (SDL_دري_IS_POPUP(دري)) {
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
        إذا (دري->flags & SDL_دري_EXTERNAL) {
            دري->flags &= ~SDL_دري_HIDDEN;
        }
    }

    إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_بفر, false)) {
        معلومات->double_بفر = true;
    }

    SDL_PropertiesID props = SDL_Get_دري_Properties(دري);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_DISPLAY_اشارو, معلومات->wayland_معلومات->display);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_SURFACE_اشارو, معلومات->surface);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_VIEWPORT_اشارو, معلومات->viewport);
    SDL_سيٽ_اشارو_Property(props, SDL_PROP_دري_WAYLAND_EGL_دري_اشارو, معلومات->egl_دري);
    إذا (معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || معلومات->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ثابت حرف *دري_id = SDL_GetStringProperty(create_props, SDL_PROP_دري_CREATE_WAYLAND_دري_ID_STRING, عدم);
        إذا (دري_id && *دري_id != '\0') {
            SDL_سيٽ_String_Property(props, SDL_PROP_دري_WAYLAND_دري_ID_STRING, دري_id);
        }
    }

    معلومات->ڪاميابي_test_نتيجو = SDL_HITTEST_عام;

    أرجع true;
}

فراغ Wayland_سيٽ_دري_Minimum_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    دري->اندروني->limits_بدليو = true;
}

فراغ Wayland_سيٽ_دري_وڌ_کان_وڌ_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    دري->اندروني->limits_بدليو = true;
}

فراغ Wayland_سيٽ_دري_Aspect_تناسب(SDL_VideoDevice *_this, SDL_دري *دري)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    دري->اندروني->limits_بدليو = true;
}

bool Wayland_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    // Only popup windows can be positioned relative to the parent.
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        إذا (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_نسخو(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_نسخو) {
            أرجع SDL_Unsupported();
        }

        RepositionPopup(دري, false);
        أرجع true;
    } وإلا إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(دري);

        إذا (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_Get_Video_Display_For_Fullscreen_دري(دري);
            إذا (display && wind->آخري_display_ID != display->id) {
                بنية wl_output *output = display->اندروني->output;
                سيٽ_Fullscreen(دري, output, true);

                أرجع true;
            }
        }
    }
    أرجع SDL_سيٽ_Error("wayland cannot position non-popup windows");
}

فراغ Wayland_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    /* Flush any pending state operations, as fullscreen windows do not get
     * explicitly resized, not strictly obeying the size of a maximized window
     * is a protocol violation, and pending restore events might result in a
     * configure event overwriting the requested size.
     *
     * Calling this on a custom surface is informative, so the size must
     * always be passed through.
     */
    FlushPendingEvents(دري);

    ثابت bool maximized = (دري->flags & SDL_دري_MAXIMIZED) != 0;
    ثابت bool resizable_state = !(دري->flags & (SDL_دري_MAXIMIZED | SDL_دري_FULLSCREEN));

    /* Maximized and fullscreen windows don't get resized, and the new size is ignored
     * if this is just to recalculate the min/max or aspect limits on a tiled window.
     *
     * Some compositors will mark tiled windows as maximized. In these cases, the content
     * size is recalculated, but window size itself is left alone, as the spec states that
     * the configure size of a maximized window must be obeyed.
     */
    إذا (resizable_state || (دري->tiled && !wind->limits_بدليو) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        إذا (!maximized) {
            إذا (!wind->scale_منزل_display) {
                wind->requested.logical_ويڪر = دري->pending.w;
                wind->requested.logical_اوچائي = دري->pending.h;
            } وإلا {
                wind->requested.logical_ويڪر = Pixel_منزل_نقطو(دري, دري->pending.w);
                wind->requested.logical_اوچائي = Pixel_منزل_نقطو(دري, دري->pending.h);
                wind->requested.pixel_ويڪر = دري->pending.w;
                wind->requested.pixel_اوچائي = دري->pending.h;
            }
        }

        /* If a non-resizable window somehow wound up in the tiled state, store the new
         * size in the floating parameters so the size will be preserved for future
         * configure events.
         *
         * This shouldn't happen, but apparently it can on at least one compositor...
         */
        إذا (دري->tiled && !(دري->flags & SDL_دري_RESIZABLE)) {
            دري->floating.w = دري->pending.w;
            دري->floating.h = دري->pending.h;
        }
    } وإلا {
        // Can't resize the window.
        دري->آخري_سائيز_pending = false;
    }

    wind->limits_بدليو = false;
    إذا (wind->shell_surface_حالت == WAYLAND_SHELL_SURFACE_حالت_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    Configure_دري_Geometry(دري);
    Commit_Libdecor_چوکٺو(دري);
}

فراغ Wayland_Get_دري_سائيز_اندريون_Pixels(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *w, صحيح *h)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    *w = معلومات->current.pixel_ويڪر;
    *h = معلومات->current.pixel_اوچائي;
}

عائم Wayland_Get_دري_Content_Scale(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    إذا (دري->flags & SDL_دري_مٿاهون_PIXEL_DENSITY || wind->scale_منزل_display || wind->fullscreen_exclusive) {
        أرجع (عائم)wind->scale_ضرب_ڪندڙ_2;
    }

    أرجع 1.0f;
}

SDL_DisplayID Wayland_Get_Display_For_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    إذا (wind) {
        أرجع wind->آخري_display_ID;
    }

    أرجع 0;
}

bool Wayland_سيٽ_دري_Opacity(SDL_VideoDevice *_this, SDL_دري *دري, عائم opacity)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    إذا (wind->wp_alpha_modifier_surface_v1) {
        ثابت bool is_opaque = !(دري->flags & SDL_دري_TRANSPARENT) && opacity == 1.0f;

        إذا (wind->نقاب.mapped && wind->نقاب.opaque != is_opaque) {
            بنية wl_بفر *old_بفر = wind->نقاب.بفر_2;
            wind->نقاب.opaque = is_opaque;
            wind->نقاب.بفر_2 = Wayland_Create_Single_Pixel_بفر(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->نقاب.surface, wind->نقاب.بفر_2, 0, 0);
            إذا (wl_surface_get_نسخو(wind->نقاب.surface) >= WL_SURFACE_DAMAGE_بفر_SINCE_نسخو) {
                wl_surface_damage_بفر(wind->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } وإلا {
                wl_surface_damage(wind->نقاب.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            إذا (is_opaque) {
                سيٽ_Surface_Opaque_Region(wind->نقاب.surface, wind->current.logical_ويڪر, wind->current.logical_اوچائي);
            } وإلا {
                سيٽ_Surface_Opaque_Region(wind->نقاب.surface, 0, 0);
            }

            wl_surface_commit(wind->نقاب.surface);

            إذا (old_بفر) {
                wl_بفر_destroy(old_بفر);
            }
        }

        إذا (is_opaque) {
            سيٽ_Surface_Opaque_Region(wind->surface, wind->current.viewport_ويڪر, wind->current.viewport_اوچائي);
        } وإلا {
            سيٽ_Surface_Opaque_Region(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_سيٽ_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((مزدوج)SDL_MAX_UINT32 * (مزدوج)opacity));

        أرجع true;
    }

    أرجع SDL_سيٽ_Error("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

فراغ Wayland_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *wind = دري->اندروني;
    ثابت حرف *title = دري->title ? دري->title : "";

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکٺو) {
        libdecor_چوکٺو_سيٽ_title(wind->shell_surface.libdecor.چوکٺو, title);
    } وإلا
#جيڪڏهن_پورو
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_سيٽ_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

ساكن صحيح icon_ترتيب_ڏيو_callback(ثابت فراغ *a, ثابت فراغ *b)
{
    ثابت SDL_Surface *s1 = *(ثابت SDL_Surface **)a;
    ثابت SDL_Surface *s2 = *(ثابت SDL_Surface **)b;

    أرجع (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_سيٽ_دري_Icon(SDL_VideoDevice *_this, SDL_دري *دري, SDL_Surface *icon)
{
    SDL_دري_معلومات *wind = دري->اندروني;
    Wayland_SHMPool *shm_pool = عدم;
    بنية xdg_toplevel *toplevel = عدم;

    إذا (!_this->اندروني->xdg_toplevel_icon_manager_v1) {
        أرجع SDL_سيٽ_Error("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    صحيح image_ڳڻپ_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_ڳڻپ_2);
    إذا (!images || !image_ڳڻپ_2) {
        أرجع false;
    }

    // Release the old icon resources.
    إذا (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = عدم;
    }

    لكل (صحيح i = 0; i < wind->icon_بفر_ڳڻپ; ++i) {
        wl_بفر_destroy(wind->icon_buffers[i]);
    }
    wind->icon_بفر_ڳڻپ = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->اندروني->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_ڳڻپ_2 * حجم(بنية wl_بفر *));
    إذا (!wind->icon_buffers) {
        اذهب failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    size_t pool_سائيز = 0;
    لكل (صحيح i = 0; i < image_ڳڻپ_2; ++i) {
        // Images must be square. Non-square images will be centered.
        ثابت صحيح سائيز = SDL_max(images[i]->w, images[i]->h);
        pool_سائيز += سائيز * سائيز * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_ڳڻپ_2, حجم(SDL_Surface *), icon_ترتيب_ڏيو_callback);

    shm_pool = Wayland_AllocSHMPool(pool_سائيز);
    إذا (!shm_pool) {
        SDL_سيٽ_Error("wayland: failed to allocate an SHM pool for the icon");
        اذهب failure_cleanup;
    }

    ثابت مزدوج بنياد_سائيز = (مزدوج)SDL_max(icon->w, icon->h);
    لكل (صحيح i = 0; i < image_ڳڻپ_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        ثابت صحيح level_سائيز = SDL_max(surface->w, surface->h);
        ثابت صحيح scale = (صحيح)SDL_floor((مزدوج)level_سائيز / بنياد_سائيز);
        إذا (!scale) {
            استمر;
        }

        إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            إذا (!surface) {
                SDL_سيٽ_Error("wayland: failed to convert the icon image to ARGB8888 format");
                اذهب failure_cleanup;
            }
        }

        فراغ *بفر_mem;
        بنية wl_بفر *بفر_2 = Wayland_Alloc_بفر_From_Pool(shm_pool, level_سائيز, level_سائيز, &بفر_mem);
        إذا (!بفر_2) {
            // Clean up the temporary conversion surface.
            إذا (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_سيٽ_Error("wayland: failed to allocate a wl_buffer for the icon");
            اذهب failure_cleanup;
        }

        wind->icon_buffers[wind->icon_بفر_ڳڻپ++] = بفر_2;

        // Center non-square images.
        إذا (surface->w < level_سائيز) {
            SDL_memset(بفر_mem, 0, level_سائيز * level_سائيز * 4);
            بفر_mem = (Uint8 *)بفر_mem + (((level_سائيز - surface->w) / 2) * 4);
        } وإلا إذا (surface->h < level_سائيز) {
            SDL_memset(بفر_mem, 0, level_سائيز * level_سائيز * 4);
            بفر_mem = (Uint8 *)بفر_mem + (((level_سائيز - surface->h) / 2) * (level_سائيز * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, بفر_mem, level_سائيز * 4, true);

        xdg_toplevel_icon_v1_جوڙيو_بفر(wind->xdg_toplevel_icon_v1, بفر_2, scale);

        // Clean up the temporary scaled or conversion surface.
        إذا (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.چوکٺو) {
        toplevel = libdecor_چوکٺو_get_xdg_toplevel(wind->shell_surface.libdecor.چوکٺو);
    } وإلا
#جيڪڏهن_پورو
        إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    إذا (toplevel) {
        xdg_toplevel_icon_manager_v1_سيٽ_icon(_this->اندروني->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
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

    لكل (صحيح i = 0; i < wind->icon_بفر_ڳڻپ; ++i) {
        wl_بفر_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = عدم;
    wind->icon_بفر_ڳڻپ = 0;

    أرجع false;
}

فراغ *Wayland_Get_دري_ICCProfile(SDL_VideoDevice *_this, SDL_دري *دري, size_t *سائيز)
{
    SDL_دري_معلومات *wind = دري->اندروني;
    فراغ *ret = عدم;

    إذا (wind->icc_سائيز > 0) {
        فراغ *icc_map = mmap(عدم, wind->icc_سائيز, PROT_READ, MAP_PRIVATE, wind->icc_fd, 0);
        إذا (icc_map != MAP_FAILED) {
            ret = SDL_malloc(wind->icc_سائيز);
            إذا (ret) {
                *سائيز = wind->icc_سائيز;
                SDL_memcpy(ret, icc_map, *سائيز);
            }
            munmap(icc_map, wind->icc_سائيز);
        }
    }

    أرجع ret;
}

bool Wayland_Sync_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *wind = دري->اندروني;

    افعل {
        WAYLAND_wl_display_roundtrip(_this->اندروني->display);
    } طالما (wind->pending_state_deadline_ڳڻپ);

    أرجع true;
}

فراغ Wayland_AcceptDragAndDrop(SDL_دري *دري, bool accept)
{
    دري->اندروني->قبولي_drag_and_drop = accept;
}

bool Wayland_سيٽ_دري_Focusable(SDL_VideoDevice *_this, SDL_دري *دري, bool focusable)
{
    إذا (دري->flags & SDL_دري_POPUP_MENU) {
        إذا (!(دري->flags & SDL_دري_HIDDEN)) {
            إذا (!focusable && (دري->flags & SDL_دري_داخلا_FOCUS)) {
                SDL_دري *new_focus;
                ثابت bool سيٽ_focus = SDL_ShouldRelinquishPopupFocus(دري, &new_focus);
                Wayland_سيٽ_Keyboard_Focus(new_focus, سيٽ_focus);
            } وإلا إذا (focusable) {
                إذا (SDL_ShouldFocusPopup(دري)) {
                    Wayland_سيٽ_Keyboard_Focus(دري, true);
                }
            }
        }

        أرجع true;
    }

    أرجع SDL_سيٽ_Error("wayland: focus can only be toggled on popup menu windows");
}

فراغ Wayland_Show_دري_System_Menu(SDL_دري *دري, صحيح x, صحيح y)
{
    SDL_دري_معلومات *wind = دري->اندروني;
    SDL_WaylandSeat *seat = wind->wayland_معلومات->آخري_implicit_grab_seat;

    إذا (!seat) {
        أرجع;
    }

    إذا (wind->scale_منزل_display) {
        x = Pixel_منزل_نقطو(دري, x);
        y = Pixel_منزل_نقطو(دري, y);
    }

#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        إذا (wind->shell_surface.libdecor.چوکٺو) {
            libdecor_چوکٺو_show_دري_menu(wind->shell_surface.libdecor.چوکٺو, seat->wl_seat, seat->آخري_implicit_grab_serial, x, y);
        }
    } وإلا
#جيڪڏهن_پورو
    إذا (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        إذا (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_دري_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->آخري_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
    إذا (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        أرجع true;
    }
#جيڪڏهن_پورو

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    إذا (معلومات->idle_inhibit_manager) {
        SDL_دري *دري = _this->windows;
        طالما (دري) {
            SDL_دري_معلومات *win_معلومات = دري->اندروني;

            إذا (_this->suspend_screensaver && !win_معلومات->idle_inhibitor) {
                win_معلومات->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(معلومات->idle_inhibit_manager,
                                                                 win_معلومات->surface);
            } وإلا إذا (!_this->suspend_screensaver && win_معلومات->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_معلومات->idle_inhibitor);
                win_معلومات->idle_inhibitor = عدم;
            }

            دري = دري->ايندڙ;
        }
    }

    أرجع true;
}

فراغ Wayland_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    SDL_دري_معلومات *wind = دري->اندروني;

    إذا (معلومات && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        إذا (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            دري->ڪاميابي_test = عدم;
            WAYLAND_wl_display_roundtrip(معلومات->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_Display_Remove_دري_References_From_Seats(معلومات, wind);

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
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
        إذا (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#جيڪڏهن_پورو
        إذا (wind->egl_دري) {
            WAYLAND_wl_egl_دري_destroy(wind->egl_دري);
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

        إذا (wind->gles_مٽا_سٽا_چوکٺو_callback) {
            wl_callback_destroy(wind->gles_مٽا_سٽا_چوکٺو_callback);
            WAYLAND_wl_proxy_wrapper_destroy(wind->gles_مٽا_سٽا_چوکٺو_surface_wrapper);
            WAYLAND_wl_event_قطار_destroy(wind->gles_مٽا_سٽا_چوکٺو_event_قطار);
        }

        إذا (!(دري->flags & SDL_دري_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } وإلا {
            Wayland_Remove_دري_معلومات_From_External_List(wind);
        }

        إذا (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        لكل (صحيح i = 0; i < wind->icon_بفر_ڳڻپ; ++i) {
            wl_بفر_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_بفر_ڳڻپ = 0;

        SDL_free(wind);
    }
    دري->اندروني = عدم;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WAYLAND
