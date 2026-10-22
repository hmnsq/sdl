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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND

#ਅਨ੍ਤਰ੍ਭਾਵ <sys/mman.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/unix/SDL_appid.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../notification/SDL_notification_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandwindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_hints_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandcolor.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "alpha-modifier-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-shell-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-decoration-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "idle-inhibit-unstable-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-activation-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "viewporter-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "fractional-scale-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-foreign-unstable-v2-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-dialog-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frog-color-management-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-toplevel-icon-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "color-management-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-session-management-v1-client-protocol.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xdg-toplevel-tag-v1-client-protocol.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
#ਅਨ੍ਤਰ੍ਭਾਵ <libdecor.h>
#ਜੇ_ਅੰਤ

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
ਸਥਿਰ bool Should_ਨਕਾਬ_Fullscreen()
{
    ਸਥਿਰ ਪੂਰਨ ਨਕਾਬ_required = -1;

    ਜੇ (ਨਕਾਬ_required >= 0) {
        ਵਾਪਸ ਨਕਾਬ_required != 0;
    }

    ਅਚਲ ਅੱਖਰ *desktop = SDL_getenv("XDG_CURRENT_DESKTOP");
    ਜੇ (desktop && SDL_strstr(desktop, "KDE") != ਨਿਰਾ) {
        ਨਕਾਬ_required = 1;
    } ਨਹੀਂਤਾਂ {
        ਨਕਾਬ_required = 0;
    }

    ਵਾਪਸ ਨਕਾਬ_required != 0;
}

ਸਥਿਰ ਦੁੱਗਣਾ Get_ਖਿੜਕੀ_Scale(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਉੱਚਾ_PIXEL_DENSITY) || ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->scale_ਮੰਜ਼ਿਲ_display ? ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2 : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
ਸਥਿਰ ਪੂਰਨ ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ ਬਿੰਦੂ)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    ਵਾਪਸ ਬਿੰਦੂ ? SDL_max((ਪੂਰਨ)SDL_lround((ਦੁੱਗਣਾ)ਬਿੰਦੂ * Get_ਖਿੜਕੀ_Scale(ਖਿੜਕੀ) + 1e-6), 1) : 0;
}

ਸਥਿਰ ਪੂਰਨ Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ pixel)
{
    ਵਾਪਸ pixel ? SDL_max((ਪੂਰਨ)SDL_lround((ਦੁੱਗਣਾ)pixel / Get_ਖਿੜਕੀ_Scale(ਖਿੜਕੀ)), 1) : 0;
}

ਗਿਣਤੀ Wayland_ਬਹੁਲਕ_Scale
{
    WAYLAND_ਬਹੁਲਕ_SCALE_UNDEFINED,
    WAYLAND_ਬਹੁਲਕ_SCALE_ASPECT,
    WAYLAND_ਬਹੁਲਕ_SCALE_STRETCH,
    WAYLAND_ਬਹੁਲਕ_SCALE_NONE
};

ਸਥਿਰ ਗਿਣਤੀ Wayland_ਬਹੁਲਕ_Scale Get_ਬਹੁਲਕ_Scale_ਵਿਧੀ(ਖਾਲੀ)
{
    ਸਥਿਰ ਗਿਣਤੀ Wayland_ਬਹੁਲਕ_Scale scale_ਬਹੁਲਕ_2 = WAYLAND_ਬਹੁਲਕ_SCALE_UNDEFINED;

    ਜੇ (scale_ਬਹੁਲਕ_2 == WAYLAND_ਬਹੁਲਕ_SCALE_UNDEFINED) {
        ਅਚਲ ਅੱਖਰ *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_ਬਹੁਲਕ_SCALING);

        ਜੇ (scale_hint) {
            ਜੇ (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_ਬਹੁਲਕ_2 = WAYLAND_ਬਹੁਲਕ_SCALE_STRETCH;
            } ਨਹੀਂਤਾਂ ਜੇ (!SDL_strcasecmp(scale_hint, "none")) {
                scale_ਬਹੁਲਕ_2 = WAYLAND_ਬਹੁਲਕ_SCALE_NONE;
            } ਨਹੀਂਤਾਂ {
                scale_ਬਹੁਲਕ_2 = WAYLAND_ਬਹੁਲਕ_SCALE_ASPECT;
            }
        } ਨਹੀਂਤਾਂ {
            scale_ਬਹੁਲਕ_2 = WAYLAND_ਬਹੁਲਕ_SCALE_ASPECT;
        }
    }

    ਵਾਪਸ scale_ਬਹੁਲਕ_2;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ BorderInsets
{
    ਪੂਰਨ ਖੱਬਾ;
    ਪੂਰਨ ਸਿਖਰ;
    ਪੂਰਨ ਸੱਜਾ;
    ਪੂਰਨ bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
ਸਥਿਰ ਖਾਲੀ GetBorderInsets(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, BorderInsets *insets)
{
    SDL_zerop(insets);
    ਜੇ (!ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->enable_insets) {
        ਵਾਪਸ;
    }
    ਜੇ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ਅਚਲ SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
        insets->ਖੱਬਾ = (ਪੂਰਨ)SDL_clamp(SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_BORDER_INSET_ਖੱਬਾ_ਸੰਖਿਆ, 0), 0, SDL_MAX_SINT16);
        insets->ਸਿਖਰ = (ਪੂਰਨ)SDL_clamp(SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_BORDER_INSET_ਸਿਖਰ_ਸੰਖਿਆ, 0), 0, SDL_MAX_SINT16);
        insets->ਸੱਜਾ = (ਪੂਰਨ)SDL_clamp(SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_BORDER_INSET_ਸੱਜਾ_ਸੰਖਿਆ, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (ਪੂਰਨ)SDL_clamp(SDL_Get_ਸੰਖਿਆ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_BORDER_INSET_BOTTOM_ਸੰਖਿਆ, 0), 0, SDL_MAX_SINT16);
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੈੱਟ_Min_Max_Dimensions(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਪੂਰਨ min_ਚੌੜਾਈ_2, min_ਉਚਾਈ_2, max_ਚੌੜਾਈ_2, max_ਉਚਾਈ_2;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    ਜੇ (ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_FULLSCREEN | SDL_ਖਿੜਕੀ_MAXIMIZED)) {
        min_ਚੌੜਾਈ_2 = 0;
        min_ਉਚਾਈ_2 = 0;
        max_ਚੌੜਾਈ_2 = 0;
        max_ਉਚਾਈ_2 = 0;
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE) {
        ਪੂਰਨ adj_w = SDL_max(ਖਿੜਕੀ->min_w, wind->system_limits.min_ਚੌੜਾਈ_2);
        ਪੂਰਨ adj_h = SDL_max(ਖਿੜਕੀ->min_h, wind->system_limits.min_ਉਚਾਈ_2);
        ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
            adj_w = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, adj_w);
            adj_h = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, adj_h);
        }
        min_ਚੌੜਾਈ_2 = adj_w;
        min_ਉਚਾਈ_2 = adj_h;

        adj_w = ਖਿੜਕੀ->max_w ? SDL_max(ਖਿੜਕੀ->max_w, wind->system_limits.min_ਚੌੜਾਈ_2) : 0;
        adj_h = ਖਿੜਕੀ->max_h ? SDL_max(ਖਿੜਕੀ->max_h, wind->system_limits.min_ਉਚਾਈ_2) : 0;
        ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
            adj_w = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, adj_w);
            adj_h = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, adj_h);
        }
        max_ਚੌੜਾਈ_2 = adj_w;
        max_ਉਚਾਈ_2 = adj_h;
    } ਨਹੀਂਤਾਂ {
        min_ਚੌੜਾਈ_2 = wind->current.logical_ਚੌੜਾਈ;
        min_ਉਚਾਈ_2 = wind->current.logical_ਉਚਾਈ;
        max_ਚੌੜਾਈ_2 = wind->current.logical_ਚੌੜਾਈ;
        max_ਉਚਾਈ_2 = wind->current.logical_ਉਚਾਈ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਜੇ (!wind->shell_surface.libdecor.ਚੌਖਟਾ) {
            ਵਾਪਸ; // Can't do anything yet, wait for ShowWindow
        }

        ਜੇ (min_ਚੌੜਾਈ_2 && min_ਉਚਾਈ_2 && min_ਚੌੜਾਈ_2 == max_ਚੌੜਾਈ_2 && min_ਉਚਾਈ_2 == max_ਉਚਾਈ_2) {
            libdecor_ਚੌਖਟਾ_unset_capabilities(wind->shell_surface.libdecor.ਚੌਖਟਾ, LIBDECOR_ACTION_RESIZE);
        } ਨਹੀਂਤਾਂ {
            libdecor_ਚੌਖਟਾ_ਸੈੱਟ_capabilities(wind->shell_surface.libdecor.ਚੌਖਟਾ, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        ਜੇ (libdecor_ਚੌਖਟਾ_has_capability(wind->shell_surface.libdecor.ਚੌਖਟਾ, LIBDECOR_ACTION_RESIZE)) {
            libdecor_ਚੌਖਟਾ_ਸੈੱਟ_min_content_ਮਾਪ(wind->shell_surface.libdecor.ਚੌਖਟਾ,
                                                min_ਚੌੜਾਈ_2,
                                                min_ਉਚਾਈ_2);
            libdecor_ਚੌਖਟਾ_ਸੈੱਟ_max_content_ਮਾਪ(wind->shell_surface.libdecor.ਚੌਖਟਾ,
                                                max_ਚੌੜਾਈ_2,
                                                max_ਉਚਾਈ_2);
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ਜੇ (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            ਵਾਪਸ; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(ਖਿੜਕੀ, &insets);
        min_ਚੌੜਾਈ_2 = SDL_max(min_ਚੌੜਾਈ_2 - (insets.ਖੱਬਾ + insets.ਸੱਜਾ), min_ਚੌੜਾਈ_2 ? 1 : 0);
        min_ਉਚਾਈ_2 = SDL_max(min_ਉਚਾਈ_2 - (insets.ਸਿਖਰ + insets.bottom), min_ਉਚਾਈ_2 ? 1 : 0);
        ਜੇ (max_ਚੌੜਾਈ_2) {
            max_ਚੌੜਾਈ_2 = SDL_max(max_ਚੌੜਾਈ_2 - (insets.ਖੱਬਾ + insets.ਸੱਜਾ), 1);
        }
        ਜੇ (max_ਉਚਾਈ_2) {
            max_ਉਚਾਈ_2 = SDL_max(max_ਉਚਾਈ_2 - (insets.ਸਿਖਰ + insets.bottom), 1);
        }
        xdg_toplevel_ਸੈੱਟ_min_ਮਾਪ(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_ਚੌੜਾਈ_2,
                                  min_ਉਚਾਈ_2);
        xdg_toplevel_ਸੈੱਟ_max_ਮਾਪ(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_ਚੌੜਾਈ_2,
                                  max_ਉਚਾਈ_2);
    }
}

ਸਥਿਰ ਖਾਲੀ EnsurePopupPositionIsValid(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *x, ਪੂਰਨ *y)
{
    ਪੂਰਨ adj_ਗਿਣਤੀ = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    ਜੇ (*x + ਖਿੜਕੀ->w <= 0) {
        *x = -ਖਿੜਕੀ->w;
        ++adj_ਗਿਣਤੀ;
    }
    ਜੇ (*y + ਖਿੜਕੀ->h <= 0) {
        *y = -ਖਿੜਕੀ->h;
        ++adj_ਗਿਣਤੀ;
    }
    ਜੇ (*x >= ਖਿੜਕੀ->ਮਾਪਾ->w) {
        *x = ਖਿੜਕੀ->ਮਾਪਾ->w;
        ++adj_ਗਿਣਤੀ;
    }
    ਜੇ (*y >= ਖਿੜਕੀ->ਮਾਪਾ->h) {
        *y = ਖਿੜਕੀ->ਮਾਪਾ->h;
        ++adj_ਗਿਣਤੀ;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    ਜੇ (adj_ਗਿਣਤੀ > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
ਸਥਿਰ ਖਾਲੀ Get_ਖਿੜਕੀ_Geometry(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    ਜੇ (SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_ਚੌੜਾਈ;
        geometry->h = wind->current.logical_ਉਚਾਈ;
    }
}

ਸਥਿਰ ਖਾਲੀ Adjust_Popup_ਵਿੱਥ(SDL_ਖਿੜਕੀ *popup, ਪੂਰਨ *x, ਪੂਰਨ *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (popup->ਮਾਪਾ->ਅੰਦਰੂਨੀ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਪੂਰਨ adj_x, adj_y;
        libdecor_ਚੌਖਟਾ_translate_coordinate(popup->ਮਾਪਾ->ਅੰਦਰੂਨੀ->shell_surface.libdecor.ਚੌਖਟਾ,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        *x -= popup->ਮਾਪਾ->ਅੰਦਰੂਨੀ->explicit_geometry.x;
        *y -= popup->ਮਾਪਾ->ਅੰਦਰੂਨੀ->explicit_geometry.y;
    }
}

ਸਥਿਰ ਖਾਲੀ RepositionPopup(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool use_current_position)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_ਸੰਸਕਰਣ(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_ਸੰਸਕਰਣ) {
        ਪੂਰਨ x = use_current_position ? ਖਿੜਕੀ->x : ਖਿੜਕੀ->pending.x;
        ਪੂਰਨ y = use_current_position ? ਖਿੜਕੀ->y : ਖਿੜਕੀ->pending.y;

        EnsurePopupPositionIsValid(ਖਿੜਕੀ, &x, &y);
        ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
            x = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ->ਮਾਪਾ, x);
            y = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ->ਮਾਪਾ, y);
        }
        Adjust_Popup_ਵਿੱਥ(ਖਿੜਕੀ, &x, &y);
        SDL_Rect ਮਾਪਾ_geometry;
        Get_ਖਿੜਕੀ_Geometry(ਖਿੜਕੀ->ਮਾਪਾ->ਅੰਦਰੂਨੀ, &ਮਾਪਾ_geometry);
        xdg_positioner_ਸੈੱਟ_anchor_rect(wind->shell_surface.xdg.popup.xdg_positioner, 0, 0, ਮਾਪਾ_geometry.w, ਮਾਪਾ_geometry.h);
        xdg_positioner_ਸੈੱਟ_ਮਾਪ(wind->shell_surface.xdg.popup.xdg_positioner, wind->current.logical_ਚੌੜਾਈ, wind->current.logical_ਉਚਾਈ);
        xdg_positioner_ਸੈੱਟ_ਵਿੱਥ(wind->shell_surface.xdg.popup.xdg_positioner, x, y);
        xdg_popup_reposition(wind->shell_surface.xdg.popup.xdg_popup,
                             wind->shell_surface.xdg.popup.xdg_positioner,
                             0);
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੈੱਟ_Surface_Opaque_Region(ਬਣਤਰ wl_surface *surface, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ)
{
    SDL_Video_ਅੰਕੜੇ *viddata = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;

    ਜੇ (ਚੌੜਾਈ && ਉਚਾਈ) {
        ਬਣਤਰ wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_ਜੋੜੋ(region, 0, 0, ਚੌੜਾਈ, ਉਚਾਈ);
        wl_surface_ਸੈੱਟ_opaque_region(surface, region);
        wl_region_destroy(region);
    } ਨਹੀਂਤਾਂ {
        wl_surface_ਸੈੱਟ_opaque_region(surface, ਨਿਰਾ);
    }
}

ਸਥਿਰ ਖਾਲੀ Configure_ਖਿੜਕੀ_Geometry(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਅਚਲ ਦੁੱਗਣਾ scale_ਗੁਣਕ_2 = Get_ਖਿੜਕੀ_Scale(ਖਿੜਕੀ);
    ਅਚਲ ਦੁੱਗਣਾ prev_ਸੂਚਕ_scale_x = ਅੰਕੜੇ->ਸੂਚਕ_scale.x;
    ਅਚਲ ਦੁੱਗਣਾ prev_ਸੂਚਕ_scale_y = ਅੰਕੜੇ->ਸੂਚਕ_scale.y;
    ਅਚਲ ਪੂਰਨ old_pixel_ਚੌੜਾਈ = ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ;
    ਅਚਲ ਪੂਰਨ old_pixel_ਉਚਾਈ = ਅੰਕੜੇ->current.pixel_ਉਚਾਈ;
    ਪੂਰਨ ਖਿੜਕੀ_ਚੌੜਾਈ = 0;
    ਪੂਰਨ ਖਿੜਕੀ_ਉਚਾਈ = 0;
    ਪੂਰਨ viewport_ਚੌੜਾਈ, viewport_ਉਚਾਈ;
    bool ਖਿੜਕੀ_ਮਾਪ_ਬਦਲਿਆ;
    bool ਬਫਰ_ਮਾਪ_ਬਦਲਿਆ;
    ਅਚਲ bool is_opaque = !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT) && ਖਿੜਕੀ->opacity == 1.0f;

    ਜੇ (ਅੰਕੜੇ->is_fullscreen && ਖਿੜਕੀ->fullscreen_exclusive) {
        ਖਿੜਕੀ_ਚੌੜਾਈ = ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.w;
        ਖਿੜਕੀ_ਉਚਾਈ = ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.h;

        viewport_ਚੌੜਾਈ = ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ;
        viewport_ਉਚਾਈ = ਅੰਕੜੇ->requested.logical_ਉਚਾਈ;

        ਚੋਣ (Get_ਬਹੁਲਕ_Scale_ਵਿਧੀ()) {
        ਹਾਲਤ WAYLAND_ਬਹੁਲਕ_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            ਜੇ (ਖਿੜਕੀ_ਚੌੜਾਈ <= viewport_ਚੌੜਾਈ && ਖਿੜਕੀ_ਉਚਾਈ <= viewport_ਉਚਾਈ) {
                viewport_ਚੌੜਾਈ = ਖਿੜਕੀ_ਚੌੜਾਈ;
                viewport_ਉਚਾਈ = ਖਿੜਕੀ_ਉਚਾਈ;

                ਰੋਕੋ;
            }
            SDL_FALLTHROUGH;
        ਹਾਲਤ WAYLAND_ਬਹੁਲਕ_SCALE_ASPECT:
        {
            ਅਚਲ ਦਸ਼ਮਲਵ output_ਅਨੁਪਾਤ = (ਦਸ਼ਮਲਵ)viewport_ਚੌੜਾਈ / (ਦਸ਼ਮਲਵ)viewport_ਉਚਾਈ;
            ਅਚਲ ਦਸ਼ਮਲਵ ਬਹੁਲਕ_ਅਨੁਪਾਤ = (ਦਸ਼ਮਲਵ)ਖਿੜਕੀ_ਚੌੜਾਈ / (ਦਸ਼ਮਲਵ)ਖਿੜਕੀ_ਉਚਾਈ;

            ਜੇ (output_ਅਨੁਪਾਤ > ਬਹੁਲਕ_ਅਨੁਪਾਤ) {
                viewport_ਚੌੜਾਈ = SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ_ਚੌੜਾਈ * ((ਦਸ਼ਮਲਵ)viewport_ਉਚਾਈ / (ਦਸ਼ਮਲਵ)ਖਿੜਕੀ_ਉਚਾਈ));
            } ਨਹੀਂਤਾਂ ਜੇ (output_ਅਨੁਪਾਤ < ਬਹੁਲਕ_ਅਨੁਪਾਤ) {
                viewport_ਉਚਾਈ = SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ_ਉਚਾਈ * ((ਦਸ਼ਮਲਵ)viewport_ਚੌੜਾਈ / (ਦਸ਼ਮਲਵ)ਖਿੜਕੀ_ਚੌੜਾਈ));
            }
        } ਰੋਕੋ;
        ਮੂਲ:
            ਰੋਕੋ;
        }

        ਖਿੜਕੀ_ਮਾਪ_ਬਦਲਿਆ = ਖਿੜਕੀ_ਚੌੜਾਈ != ਖਿੜਕੀ->w ||
                              ਖਿੜਕੀ_ਉਚਾਈ != ਖਿੜਕੀ->h ||
                              ਅੰਕੜੇ->current.viewport_ਚੌੜਾਈ != viewport_ਚੌੜਾਈ ||
                              ਅੰਕੜੇ->current.viewport_ਉਚਾਈ != viewport_ਉਚਾਈ;

        // Exclusive fullscreen window sizes are always in pixel units.
        ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ = ਖਿੜਕੀ_ਚੌੜਾਈ;
        ਅੰਕੜੇ->current.pixel_ਉਚਾਈ = ਖਿੜਕੀ_ਉਚਾਈ;
        ਬਫਰ_ਮਾਪ_ਬਦਲਿਆ = ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ != old_pixel_ਚੌੜਾਈ ||
                              ਅੰਕੜੇ->current.pixel_ਉਚਾਈ != old_pixel_ਉਚਾਈ;

        ਜੇ (ਖਿੜਕੀ_ਮਾਪ_ਬਦਲਿਆ || ਬਫਰ_ਮਾਪ_ਬਦਲਿਆ) {
            ਜੇ (ਅੰਕੜੇ->viewport) {
                wp_viewport_ਸੈੱਟ_destination(ਅੰਕੜੇ->viewport, viewport_ਚੌੜਾਈ, viewport_ਉਚਾਈ);

                ਅੰਕੜੇ->current.logical_ਚੌੜਾਈ = ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ;
                ਅੰਕੜੇ->current.logical_ਉਚਾਈ = ਅੰਕੜੇ->requested.logical_ਉਚਾਈ;
                ਅੰਕੜੇ->current.viewport_ਚੌੜਾਈ = viewport_ਚੌੜਾਈ;
                ਅੰਕੜੇ->current.viewport_ਉਚਾਈ = viewport_ਉਚਾਈ;
            } ਨਹੀਂਤਾਂ {
                // Calculate the integer scale from the mode and output.
                ਅਚਲ int32_t int_scale = SDL_max(ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.w / viewport_ਚੌੜਾਈ, 1);

                wl_surface_ਸੈੱਟ_ਬਫਰ_scale(ਅੰਕੜੇ->surface, int_scale);
                ਅੰਕੜੇ->current.logical_ਚੌੜਾਈ = ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.w;
                ਅੰਕੜੇ->current.logical_ਉਚਾਈ = ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.h;
            }

            ਅੰਕੜੇ->ਸੂਚਕ_scale.x = (ਦੁੱਗਣਾ)ਖਿੜਕੀ_ਚੌੜਾਈ / (ਦੁੱਗਣਾ)viewport_ਚੌੜਾਈ;
            ਅੰਕੜੇ->ਸੂਚਕ_scale.y = (ਦੁੱਗਣਾ)ਖਿੜਕੀ_ਉਚਾਈ / (ਦੁੱਗਣਾ)viewport_ਉਚਾਈ;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display) {
            viewport_ਚੌੜਾਈ = ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ;
            viewport_ਉਚਾਈ = ਅੰਕੜੇ->requested.logical_ਉਚਾਈ;
        } ਨਹੀਂਤਾਂ {
            viewport_ਚੌੜਾਈ = ਅੰਕੜੇ->requested.pixel_ਚੌੜਾਈ;
            viewport_ਉਚਾਈ = ਅੰਕੜੇ->requested.pixel_ਉਚਾਈ;
        }

        ਜੇ (!ਅੰਕੜੇ->enable_insets &&
            ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ != WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_HIDDEN &&
            ਅੰਕੜੇ->viewport && ਅੰਕੜੇ->wayland_ਅੰਕੜੇ->subcompositor && !ਅੰਕੜੇ->floating && !ਅੰਕੜੇ->is_fullscreen) {
            ਪੂਰਨ min_ਚੌੜਾਈ_2, min_ਉਚਾਈ_2, max_ਚੌੜਾਈ_2, max_ਉਚਾਈ_2;
            ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE) {
                min_ਚੌੜਾਈ_2 = ਖਿੜਕੀ->min_w;
                min_ਉਚਾਈ_2 = ਖਿੜਕੀ->min_h;
                max_ਚੌੜਾਈ_2 = ਖਿੜਕੀ->max_w;
                max_ਉਚਾਈ_2 = ਖਿੜਕੀ->max_h;
            } ਨਹੀਂਤਾਂ {
                // Use the fixed size in the odd case where a non-resizable window somehow wound up tiled or maximized.
                min_ਚੌੜਾਈ_2 = ਖਿੜਕੀ->floating.w;
                min_ਉਚਾਈ_2 = ਖਿੜਕੀ->floating.h;
                max_ਚੌੜਾਈ_2 = ਖਿੜਕੀ->floating.w;
                max_ਉਚਾਈ_2 = ਖਿੜਕੀ->floating.h;
            }

            ਜੇ (min_ਚੌੜਾਈ_2) {
                viewport_ਚੌੜਾਈ = SDL_max(viewport_ਚੌੜਾਈ, min_ਚੌੜਾਈ_2);
            }
            ਜੇ (min_ਉਚਾਈ_2) {
                viewport_ਉਚਾਈ = SDL_max(viewport_ਉਚਾਈ, min_ਉਚਾਈ_2);
            }
            ਜੇ (max_ਚੌੜਾਈ_2) {
                viewport_ਚੌੜਾਈ = SDL_min(viewport_ਚੌੜਾਈ, max_ਚੌੜਾਈ_2);
            }
            ਜੇ (max_ਉਚਾਈ_2) {
                viewport_ਉਚਾਈ = SDL_min(viewport_ਉਚਾਈ, max_ਉਚਾਈ_2);
            }

            ਦਸ਼ਮਲਵ aspect = (ਦਸ਼ਮਲਵ)viewport_ਚੌੜਾਈ / (ਦਸ਼ਮਲਵ)viewport_ਉਚਾਈ;
            ਜੇ (ਖਿੜਕੀ->min_aspect != 0.f && aspect < ਖਿੜਕੀ->min_aspect) {
                viewport_ਉਚਾਈ = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)viewport_ਚੌੜਾਈ / ਖਿੜਕੀ->min_aspect), 1);
            } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->max_aspect != 0.f && aspect > ਖਿੜਕੀ->max_aspect) {
                viewport_ਚੌੜਾਈ = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)viewport_ਉਚਾਈ * ਖਿੜਕੀ->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            ਖਿੜਕੀ_ਚੌੜਾਈ = viewport_ਚੌੜਾਈ;
            ਖਿੜਕੀ_ਉਚਾਈ = viewport_ਉਚਾਈ;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            ਜੇ (!ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display) {
                ਜੇ (viewport_ਚੌੜਾਈ > ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ || viewport_ਉਚਾਈ > ਅੰਕੜੇ->requested.logical_ਉਚਾਈ) {
                    aspect = (ਦਸ਼ਮਲਵ)viewport_ਚੌੜਾਈ / (ਦਸ਼ਮਲਵ)viewport_ਉਚਾਈ;
                    ਅਚਲ ਦਸ਼ਮਲਵ ਖਿੜਕੀ_ਅਨੁਪਾਤ = (ਦਸ਼ਮਲਵ)ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ / (ਦਸ਼ਮਲਵ)ਅੰਕੜੇ->requested.logical_ਉਚਾਈ;
                    ਜੇ (aspect >= ਖਿੜਕੀ_ਅਨੁਪਾਤ) {
                        viewport_ਚੌੜਾਈ = ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ;
                        viewport_ਉਚਾਈ = SDL_lroundf((ਦਸ਼ਮਲਵ)viewport_ਚੌੜਾਈ / aspect);
                    } ਨਹੀਂਤਾਂ ਜੇ (aspect < ਖਿੜਕੀ_ਅਨੁਪਾਤ) {
                        viewport_ਉਚਾਈ = ਅੰਕੜੇ->requested.logical_ਉਚਾਈ;
                        viewport_ਚੌੜਾਈ = SDL_lroundf((ਦਸ਼ਮਲਵ)viewport_ਉਚਾਈ * aspect);
                    }
                }
            } ਨਹੀਂਤਾਂ {
                ਜੇ (viewport_ਚੌੜਾਈ > ਅੰਕੜੇ->requested.pixel_ਚੌੜਾਈ || viewport_ਉਚਾਈ > ਅੰਕੜੇ->requested.pixel_ਉਚਾਈ) {
                    aspect = (ਦਸ਼ਮਲਵ)viewport_ਚੌੜਾਈ / (ਦਸ਼ਮਲਵ)viewport_ਉਚਾਈ;
                    ਅਚਲ ਦਸ਼ਮਲਵ ਖਿੜਕੀ_ਅਨੁਪਾਤ = (ਦਸ਼ਮਲਵ)ਅੰਕੜੇ->requested.pixel_ਚੌੜਾਈ / (ਦਸ਼ਮਲਵ)ਅੰਕੜੇ->requested.pixel_ਉਚਾਈ;
                    ਜੇ (aspect >= ਖਿੜਕੀ_ਅਨੁਪਾਤ) {
                        viewport_ਚੌੜਾਈ = ਅੰਕੜੇ->requested.pixel_ਚੌੜਾਈ;
                        viewport_ਉਚਾਈ = SDL_lroundf((ਦਸ਼ਮਲਵ)viewport_ਚੌੜਾਈ / aspect);
                    } ਨਹੀਂਤਾਂ ਜੇ (aspect < ਖਿੜਕੀ_ਅਨੁਪਾਤ) {
                        viewport_ਉਚਾਈ = ਅੰਕੜੇ->requested.pixel_ਉਚਾਈ;
                        viewport_ਚੌੜਾਈ = SDL_lroundf((ਦਸ਼ਮਲਵ)viewport_ਉਚਾਈ * aspect);
                    }
                }
            }

            viewport_ਚੌੜਾਈ = SDL_max(viewport_ਚੌੜਾਈ, 1);
            viewport_ਉਚਾਈ = SDL_max(viewport_ਉਚਾਈ, 1);
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ_ਚੌੜਾਈ = viewport_ਚੌੜਾਈ;
            ਖਿੜਕੀ_ਉਚਾਈ = viewport_ਉਚਾਈ;
        }

        ਜੇ (!ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display) {
            ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ, ਖਿੜਕੀ_ਚੌੜਾਈ);
            ਅੰਕੜੇ->current.pixel_ਉਚਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ, ਖਿੜਕੀ_ਉਚਾਈ);
        } ਨਹੀਂਤਾਂ {
            // The viewport size is in pixels at this point; convert it to logical units.
            ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ = ਖਿੜਕੀ_ਚੌੜਾਈ;
            ਅੰਕੜੇ->current.pixel_ਉਚਾਈ = ਖਿੜਕੀ_ਉਚਾਈ;
            viewport_ਚੌੜਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, viewport_ਚੌੜਾਈ);
            viewport_ਉਚਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, viewport_ਉਚਾਈ);
        }

        // Clamp the physical window size to the system minimum required size.
        ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ = SDL_max(ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ, ਅੰਕੜੇ->system_limits.min_ਚੌੜਾਈ_2);
        ਅੰਕੜੇ->requested.logical_ਉਚਾਈ = SDL_max(ਅੰਕੜੇ->requested.logical_ਉਚਾਈ, ਅੰਕੜੇ->system_limits.min_ਉਚਾਈ_2);

        ਖਿੜਕੀ_ਮਾਪ_ਬਦਲਿਆ = ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ != ਅੰਕੜੇ->current.logical_ਚੌੜਾਈ ||
                              ਅੰਕੜੇ->requested.logical_ਉਚਾਈ != ਅੰਕੜੇ->current.logical_ਉਚਾਈ ||
                              viewport_ਚੌੜਾਈ != ਅੰਕੜੇ->current.viewport_ਚੌੜਾਈ ||
                              viewport_ਉਚਾਈ != ਅੰਕੜੇ->current.viewport_ਉਚਾਈ;

        ਬਫਰ_ਮਾਪ_ਬਦਲਿਆ = ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ != old_pixel_ਚੌੜਾਈ ||
                              ਅੰਕੜੇ->current.pixel_ਉਚਾਈ != old_pixel_ਉਚਾਈ;

        ਜੇ (ਖਿੜਕੀ_ਮਾਪ_ਬਦਲਿਆ || ਬਫਰ_ਮਾਪ_ਬਦਲਿਆ) {
            ਜੇ (ਅੰਕੜੇ->viewport) {
                wp_viewport_ਸੈੱਟ_destination(ਅੰਕੜੇ->viewport, viewport_ਚੌੜਾਈ, viewport_ਉਚਾਈ);
            } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਉੱਚਾ_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_ਸੈੱਟ_ਬਫਰ_scale(ਅੰਕੜੇ->surface, (int32_t)scale_ਗੁਣਕ_2);
            }

            ਅੰਕੜੇ->current.logical_ਚੌੜਾਈ = ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ;
            ਅੰਕੜੇ->current.logical_ਉਚਾਈ = ਅੰਕੜੇ->requested.logical_ਉਚਾਈ;
            ਅੰਕੜੇ->current.viewport_ਚੌੜਾਈ = viewport_ਚੌੜਾਈ;
            ਅੰਕੜੇ->current.viewport_ਉਚਾਈ = viewport_ਉਚਾਈ;

            ਅੰਕੜੇ->ਸੂਚਕ_scale.x = (ਦੁੱਗਣਾ)ਖਿੜਕੀ_ਚੌੜਾਈ / (ਦੁੱਗਣਾ)viewport_ਚੌੜਾਈ;
            ਅੰਕੜੇ->ਸੂਚਕ_scale.y = (ਦੁੱਗਣਾ)ਖਿੜਕੀ_ਉਚਾਈ / (ਦੁੱਗਣਾ)viewport_ਉਚਾਈ;
        }
    }

    ਜੇ (ਅੰਕੜੇ->egl_ਖਿੜਕੀ && ਬਫਰ_ਮਾਪ_ਬਦਲਿਆ) {
        WAYLAND_wl_egl_ਖਿੜਕੀ_resize(ਅੰਕੜੇ->egl_ਖਿੜਕੀ,
                                     ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ,
                                     ਅੰਕੜੇ->current.pixel_ਉਚਾਈ,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    ਜੇ (!ਅੰਕੜੇ->enable_insets && ਅੰਕੜੇ->viewport && ਅੰਕੜੇ->wayland_ਅੰਕੜੇ->subcompositor && (!ਅੰਕੜੇ->is_fullscreen || Should_ਨਕਾਬ_Fullscreen()) &&
        (viewport_ਚੌੜਾਈ != ਅੰਕੜੇ->current.logical_ਚੌੜਾਈ || viewport_ਉਚਾਈ != ਅੰਕੜੇ->current.logical_ਉਚਾਈ)) {
        ਬਣਤਰ wl_ਬਫਰ *old_ਬਫਰ = ਨਿਰਾ;

        ਜੇ (!ਅੰਕੜੇ->ਨਕਾਬ.surface) {
            ਅੰਕੜੇ->ਨਕਾਬ.surface = wl_compositor_create_surface(ਅੰਕੜੇ->wayland_ਅੰਕੜੇ->compositor);
            SDL_WAYLAND_ਰਜਿਸਟਰ_surface(ਅੰਕੜੇ->ਨਕਾਬ.surface);
            wl_surface_ਸੈੱਟ_user_ਅੰਕੜੇ(ਅੰਕੜੇ->ਨਕਾਬ.surface, ਅੰਕੜੇ);
        }
        ਜੇ (!ਅੰਕੜੇ->ਨਕਾਬ.subsurface) {
            ਅੰਕੜੇ->ਨਕਾਬ.subsurface = wl_subcompositor_get_subsurface(ਅੰਕੜੇ->wayland_ਅੰਕੜੇ->subcompositor, ਅੰਕੜੇ->ਨਕਾਬ.surface, ਅੰਕੜੇ->surface);
        }
        ਜੇ (!ਅੰਕੜੇ->ਨਕਾਬ.viewport) {
            ਅੰਕੜੇ->ਨਕਾਬ.viewport = wp_viewporter_get_viewport(ਅੰਕੜੇ->wayland_ਅੰਕੜੇ->viewporter, ਅੰਕੜੇ->ਨਕਾਬ.surface);
        }
        ਜੇ (!ਅੰਕੜੇ->ਨਕਾਬ.ਬਫਰ_2 || ਅੰਕੜੇ->ਨਕਾਬ.opaque != is_opaque) {
            old_ਬਫਰ = ਅੰਕੜੇ->ਨਕਾਬ.ਬਫਰ_2;
            ਅੰਕੜੇ->ਨਕਾਬ.opaque = is_opaque;
            ਅੰਕੜੇ->ਨਕਾਬ.ਬਫਰ_2 = Wayland_Create_Single_Pixel_ਬਫਰ(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(ਅੰਕੜੇ->ਨਕਾਬ.surface, ਅੰਕੜੇ->ਨਕਾਬ.ਬਫਰ_2, 0, 0);

        wl_subsurface_ਰੱਖੋ_ਹੇਠਾਂ(ਅੰਕੜੇ->ਨਕਾਬ.subsurface, ਅੰਕੜੇ->surface);
        wp_viewport_ਸੈੱਟ_destination(ਅੰਕੜੇ->ਨਕਾਬ.viewport, ਅੰਕੜੇ->current.logical_ਚੌੜਾਈ, ਅੰਕੜੇ->current.logical_ਉਚਾਈ);

        ਜੇ (wl_surface_get_ਸੰਸਕਰਣ(ਅੰਕੜੇ->ਨਕਾਬ.surface) >= WL_SURFACE_DAMAGE_ਬਫਰ_SINCE_ਸੰਸਕਰਣ) {
            wl_surface_damage_ਬਫਰ(ਅੰਕੜੇ->ਨਕਾਬ.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } ਨਹੀਂਤਾਂ {
            wl_surface_damage(ਅੰਕੜੇ->ਨਕਾਬ.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        ਜੇ (is_opaque) {
            ਸੈੱਟ_Surface_Opaque_Region(ਅੰਕੜੇ->ਨਕਾਬ.surface, ਅੰਕੜੇ->current.logical_ਚੌੜਾਈ, ਅੰਕੜੇ->current.logical_ਉਚਾਈ);
        } ਨਹੀਂਤਾਂ {
            ਸੈੱਟ_Surface_Opaque_Region(ਅੰਕੜੇ->ਨਕਾਬ.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        ਜੇ (ਅੰਕੜੇ->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            ਅੰਕੜੇ->ਨਕਾਬ.ਵਿੱਥ_x = -(ਅੰਕੜੇ->current.logical_ਚੌੜਾਈ - viewport_ਚੌੜਾਈ) / 2;
            ਅੰਕੜੇ->ਨਕਾਬ.ਵਿੱਥ_y = -(ਅੰਕੜੇ->current.logical_ਉਚਾਈ - viewport_ਉਚਾਈ) / 2;
        } ਨਹੀਂਤਾਂ {
            ਅੰਕੜੇ->ਨਕਾਬ.ਵਿੱਥ_x = 0;
            ਅੰਕੜੇ->ਨਕਾਬ.ਵਿੱਥ_y = 0;
        }

        wl_subsurface_ਸੈੱਟ_position(ਅੰਕੜੇ->ਨਕਾਬ.subsurface, ਅੰਕੜੇ->ਨਕਾਬ.ਵਿੱਥ_x, ਅੰਕੜੇ->ਨਕਾਬ.ਵਿੱਥ_y);
        wl_surface_commit(ਅੰਕੜੇ->ਨਕਾਬ.surface);

        ਜੇ (old_ਬਫਰ) {
            wl_ਬਫਰ_destroy(old_ਬਫਰ);
        }

        ਅੰਕੜੇ->ਨਕਾਬ.mapped = true;
    } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਨਕਾਬ.mapped) {
        wl_subsurface_ਸੈੱਟ_position(ਅੰਕੜੇ->ਨਕਾਬ.subsurface, 0, 0);
        wl_surface_attach(ਅੰਕੜੇ->ਨਕਾਬ.surface, ਨਿਰਾ, 0, 0);
        wl_surface_commit(ਅੰਕੜੇ->ਨਕਾਬ.surface);

        ਅੰਕੜੇ->ਨਕਾਬ.ਵਿੱਥ_x = 0;
        ਅੰਕੜੇ->ਨਕਾਬ.ਵਿੱਥ_y = 0;
        ਅੰਕੜੇ->ਨਕਾਬ.mapped = false;
    }

    ਜੇ (ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && ਅੰਕੜੇ->shell_surface.xdg.surface &&
        (ਅੰਕੜੇ->enable_insets || !ਅੰਕੜੇ->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(ਖਿੜਕੀ, &insets);
        ਅਚਲ bool use_insets = (insets.ਖੱਬਾ || insets.ਸਿਖਰ || insets.ਸੱਜਾ || insets.bottom) &&
                                !(ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_MAXIMIZED | SDL_ਖਿੜਕੀ_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, ਅੰਕੜੇ->current.logical_ਚੌੜਾਈ, ਅੰਕੜੇ->current.logical_ਉਚਾਈ };
        ਜੇ (use_insets) {
            geometry.x = insets.ਖੱਬਾ;
            geometry.y = insets.ਸਿਖਰ;
            geometry.w = SDL_max(geometry.w - (insets.ਖੱਬਾ + insets.ਸੱਜਾ), 1);
            geometry.h = SDL_max(geometry.h - (insets.ਸਿਖਰ + insets.bottom), 1);
        }
        /* An explicitly set geometry does not track the surface, so it must be kept in sync
         * once set. Otherwise this is only done when viewports aren't supported and the size
         * has changed (XXX: a hack) to avoid a potential protocol violation if a buffer with
         * an old size is committed.
         */
        ਜੇ ((use_insets || !SDL_Rect_ਖਾਲੀ_ਥਾਵਾਂ(&ਅੰਕੜੇ->explicit_geometry) || (!ਅੰਕੜੇ->viewport && ਖਿੜਕੀ_ਮਾਪ_ਬਦਲਿਆ)) &&
            !SDL_RectsEqual(&geometry, &ਅੰਕੜੇ->explicit_geometry)) {
            xdg_surface_ਸੈੱਟ_ਖਿੜਕੀ_geometry(ਅੰਕੜੇ->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            ਅੰਕੜੇ->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    ਜੇ (ਖਿੜਕੀ_ਮਾਪ_ਬਦਲਿਆ) {
        ਜੇ (is_opaque) {
            ਸੈੱਟ_Surface_Opaque_Region(ਅੰਕੜੇ->surface, viewport_ਚੌੜਾਈ, viewport_ਉਚਾਈ);
        } ਨਹੀਂਤਾਂ {
            ਸੈੱਟ_Surface_Opaque_Region(ਅੰਕੜੇ->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        ਲਈ (SDL_ਖਿੜਕੀ *ਬੱਚਾ = ਖਿੜਕੀ->ਪਹਿਲਾ_ਬੱਚਾ; ਬੱਚਾ; ਬੱਚਾ = ਬੱਚਾ->ਅਗਲਾ_sibling) {
            RepositionPopup(ਬੱਚਾ, true);
        }
    }

    // Update the scale for any focused cursors.
    ਜੇ (prev_ਸੂਚਕ_scale_x != ਅੰਕੜੇ->ਸੂਚਕ_scale.x || prev_ਸੂਚਕ_scale_y != ਅੰਕੜੇ->ਸੂਚਕ_scale.y) {
        Wayland_Display_Update_ਸੂਚਕ_Focused_Scale(ਅੰਕੜੇ);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    ਸੈੱਟ_Min_Max_Dimensions(ਖਿੜਕੀ);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    ਜੇ (!ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display) {
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, ਖਿੜਕੀ_ਚੌੜਾਈ, ਖਿੜਕੀ_ਉਚਾਈ);
    } ਨਹੀਂਤਾਂ {
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ, ਅੰਕੜੇ->current.pixel_ਉਚਾਈ);
    }
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_PIXEL_ਮਾਪ_ਬਦਲਿਆ, ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ, ਅੰਕੜੇ->current.pixel_ਉਚਾਈ);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    ਜੇ (ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN) {
        ਜੇ ((ਬਫਰ_ਮਾਪ_ਬਦਲਿਆ || ਖਿੜਕੀ_ਮਾਪ_ਬਦਲਿਆ) ||
            (!ਅੰਕੜੇ->suspended && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OCCLUDED))) {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_EXPOSED, 0, 0);
        }

        ਜੇ (ਅੰਕੜੇ->suspended) {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_OCCLUDED, 0, 0);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Commit_Libdecor_ਚੌਖਟਾ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.ਚੌਖਟਾ) {
        ਬਣਤਰ libdecor_state *state = libdecor_state_new(wind->current.logical_ਚੌੜਾਈ, wind->current.logical_ਉਚਾਈ);
        libdecor_ਚੌਖਟਾ_commit(wind->shell_surface.libdecor.ਚੌਖਟਾ, state, ਨਿਰਾ);
        libdecor_state_free(state);
    }
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਖਾਲੀ pending_state_deadline_handler(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_callback *callback, uint32_t callback_ਅੰਕੜੇ)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_ਖਿੜਕੀ_ID ਖਿੜਕੀ_ID = (SDL_ਖਿੜਕੀ_ID)(uintptr_t)ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = SDL_Get_ਖਿੜਕੀ_From_ID(ਖਿੜਕੀ_ID);

    ਜੇ (ਖਿੜਕੀ && ਖਿੜਕੀ->ਅੰਦਰੂਨੀ) {
        --ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_state_deadline_ਗਿਣਤੀ;
    }

    wl_callback_destroy(callback);
}

ਸਥਿਰ ਬਣਤਰ wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

ਸਥਿਰ ਖਾਲੀ ਜੋੜੋ_Pending_State_Sync(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2)
{
    SDL_Video_ਅੰਕੜੇ *video_ਅੰਕੜੇ = ਖਿੜਕੀ_ਅੰਕੜੇ_2->wayland_ਅੰਕੜੇ;
    ਖਾਲੀ *cb_ਅੰਕੜੇ = (ਖਾਲੀ *)(uintptr_t)ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow->id;

    ++ਖਿੜਕੀ_ਅੰਕੜੇ_2->pending_state_deadline_ਗਿਣਤੀ;
    ਬਣਤਰ wl_callback *cb = wl_display_sync(video_ਅੰਕੜੇ->display);
    wl_callback_ਜੋੜੋ_listener(cb, &pending_state_deadline_listener, cb_ਅੰਕੜੇ);
}

ਸਥਿਰ ਖਾਲੀ FlushPendingEvents(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ਅਚਲ bool ਆਖਰੀ_position_pending = ਖਿੜਕੀ->ਆਖਰੀ_position_pending;
    ਅਚਲ bool ਆਖਰੀ_ਮਾਪ_pending = ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending;

    ਜਦੋਂ (ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->pending_state_deadline_ਗਿਣਤੀ) {
        WAYLAND_wl_display_roundtrip(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->wayland_ਅੰਕੜੇ->display);
    }

    ਖਿੜਕੀ->ਆਖਰੀ_position_pending = ਆਖਰੀ_position_pending;
    ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending = ਆਖਰੀ_ਮਾਪ_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
ਖਾਲੀ Wayland_Update_ਖਿੜਕੀ_Position(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *display;

    ਜੇ (wind->outputs && wind->ਅੰਕ_outputs) {
        display = wind->outputs[wind->ਅੰਕ_outputs - 1];
    } ਨਹੀਂਤਾਂ {
        // A window may not be on any displays if minimized.
        ਵਾਪਸ;
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
    wind->ਆਖਰੀ_display_ID = display->display;
    ਜੇ (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        ਜੇ (!wind->wayland_ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display_enabled) {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MOVED, display->logical.x, display->logical.y);
        } ਨਹੀਂਤਾਂ {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_DISPLAY_ਬਦਲਿਆ, wind->ਆਖਰੀ_display_ID, 0);
    }
}

ਸਥਿਰ ਖਾਲੀ ਸੈੱਟ_Fullscreen(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਬਣਤਰ wl_output *output, bool fullscreen)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਜੇ (!wind->shell_surface.libdecor.ਚੌਖਟਾ) {
            ਵਾਪਸ; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? ਖਿੜਕੀ->fullscreen_exclusive : false;
        ਜੇ (fullscreen) {
            libdecor_ਚੌਖਟਾ_ਸੈੱਟ_fullscreen(wind->shell_surface.libdecor.ਚੌਖਟਾ, output);
        } ਨਹੀਂਤਾਂ {
            libdecor_ਚੌਖਟਾ_unset_fullscreen(wind->shell_surface.libdecor.ਚੌਖਟਾ);
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ਜੇ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ਨਿਰਾ) {
            ਵਾਪਸ; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? ਖਿੜਕੀ->fullscreen_exclusive : false;
        ਜੇ (fullscreen) {
            xdg_toplevel_ਸੈੱਟ_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } ਨਹੀਂਤਾਂ {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    ਜੋੜੋ_Pending_State_Sync(wind);
}

ਸਥਿਰ ਖਾਲੀ Update_ਖਿੜਕੀ_Fullscreen(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool fullscreen)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    wind->is_fullscreen = fullscreen;

    ਜੇ (fullscreen) {
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN)) {
            SDL_copyp(&ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ, &ਖਿੜਕੀ->requested_fullscreen_ਬਹੁਲਕ);
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_ENTER_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            ਜੇ (ਖਿੜਕੀ->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(ਖਿੜਕੀ->current_fullscreen_ਬਹੁਲਕ.displayID);
                ਜੇ (disp) {
                    wind->fullscreen_was_positioned = true;
                    ਸੈੱਟ_Fullscreen(ਖਿੜਕੀ, disp->ਅੰਦਰੂਨੀ->output, true);
                }
            }
        }
    } ਨਹੀਂਤਾਂ {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) && !ਖਿੜਕੀ->is_hiding && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_LEAVE_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ, SDL_FULLSCREEN_OP_LEAVE, false);
            wind->fullscreen_was_positioned = false;

            /* Send a move event, in case it was deferred while the fullscreen window was moving and
             * on multiple outputs.
             */
            Wayland_Update_ਖਿੜਕੀ_Position(ਖਿੜਕੀ);
        }
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_callback_listener surface_ਚੌਖਟਾ_listener;

ਸਥਿਰ ਖਾਲੀ surface_ਚੌਖਟਾ_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_callback *cb, uint32_t ਸਮਾਂ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    ਜੇ (wl_compositor_get_ਸੰਸਕਰਣ(wind->wayland_ਅੰਕੜੇ->compositor) >= WL_SURFACE_DAMAGE_ਬਫਰ_SINCE_ਸੰਸਕਰਣ) {
        wl_surface_damage_ਬਫਰ(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } ਨਹੀਂਤਾਂ {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ਜੇ (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            Configure_ਖਿੜਕੀ_Geometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } ਨਹੀਂਤਾਂ {
        wind->resizing = false;
    }

    ਜੇ (wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_ਚੌਖਟਾ) {
        wind->shell_surface_ਸਥਿਤੀ = WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        ਲਈ (SDL_ਖਿੜਕੀ *w = wind->sdlwindow->ਪਹਿਲਾ_ਬੱਚਾ; w; w = w->ਅਗਲਾ_sibling) {
            ਜੇ (w->ਅੰਦਰੂਨੀ->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOW_PENDING) {
                Wayland_Show_ਖਿੜਕੀ(SDL_GetVideoDevice(), w);
            } ਨਹੀਂਤਾਂ ਜੇ (w->ਅੰਦਰੂਨੀ->reparenting_required) {
                Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(SDL_GetVideoDevice(), w, w->ਮਾਪਾ);
                ਜੇ (w->flags & SDL_ਖਿੜਕੀ_MODAL) {
                    Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Modal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        ਜੇ (wind->suspended) {
            SDL_Send_ਖਿੜਕੀ_Event(wind->sdlwindow, SDL_EVENT_ਖਿੜਕੀ_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_ਚੌਖਟਾ_callback = wl_surface_ਚੌਖਟਾ(wind->surface);
    wl_callback_ਜੋੜੋ_listener(wind->surface_ਚੌਖਟਾ_callback, &surface_ਚੌਖਟਾ_listener, ਅੰਕੜੇ);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_callback_listener surface_ਚੌਖਟਾ_listener = {
    surface_ਚੌਖਟਾ_ਪੂਰਾ
};

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_callback_listener gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_listener;

ਸਥਿਰ ਖਾਲੀ gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_callback *cb, uint32_t ਸਮਾਂ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    SDL_ਸੈੱਟ_Atomic_Int(&wind->ਅਦਲਾ_ਬਦਲੀ_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback = wl_surface_ਚੌਖਟਾ(wind->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_ਜੋੜੋ_listener(wind->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback, &gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_listener, ਅੰਕੜੇ);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_callback_listener gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_listener = {
    gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_ਪੂਰਾ
};

ਸਥਿਰ ਖਾਲੀ handle_xdg_surface_configure(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ xdg_surface *xdg, uint32_t serial)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    ਜੇ (!wind->resizing) {
        wind->pending_config_ack = false;
        Configure_ਖਿੜਕੀ_Geometry(ਖਿੜਕੀ);
        xdg_surface_ack_configure(xdg, serial);
    } ਨਹੀਂਤਾਂ ਜੇ (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_EXPOSED, 0, 0);
    }

    ਜੇ (wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE) {
        wind->shell_surface_ਸਥਿਤੀ = WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_ਚੌਖਟਾ;
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

ਸਥਿਰ ਖਾਲੀ ApplyGeometryLimits(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ req_w, ਪੂਰਨ req_h, ਪੂਰਨ *ਬਾਹਰਲਾ_w, ਪੂਰਨ *ਬਾਹਰਲਾ_h)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਪੂਰਨ w = req_w;
    ਪੂਰਨ h = req_h;
    ਅਚਲ ਦਸ਼ਮਲਵ aspect = (ਦਸ਼ਮਲਵ)req_w / (ਦਸ਼ਮਲਵ)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    ਜੇ (!wind->resizing || (wind->resize_ਕਿਨਾਰਾ & WAYLAND_RESIZE_ਕਿਨਾਰਾ_ਕੋਨਾ) == WAYLAND_RESIZE_ਕਿਨਾਰਾ_ਕੋਨਾ) {
        ਜੇ (ਖਿੜਕੀ->min_aspect != 0.f && aspect < ਖਿੜਕੀ->min_aspect) {
            h = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)req_w / ਖਿੜਕੀ->min_aspect), 1);

            ਜੇ (h < ਖਿੜਕੀ->min_h) {
                w = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->min_h * ਖਿੜਕੀ->min_aspect), 1);
            }
            ਜੇ (ਖਿੜਕੀ->max_h && h > ਖਿੜਕੀ->max_h) {
                w = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->max_h * ਖਿੜਕੀ->min_aspect), 1);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->max_aspect != 0.f && aspect > ਖਿੜਕੀ->max_aspect) {
            w = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)req_h * ਖਿੜਕੀ->max_aspect), 1);

            ਜੇ (w < ਖਿੜਕੀ->min_w) {
                h = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->min_w / ਖਿੜਕੀ->max_aspect), 1);
            }
            ਜੇ (ਖਿੜਕੀ->max_w && w > ਖਿੜਕੀ->max_w) {
                h = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->max_w / ਖਿੜਕੀ->max_aspect), 1);
            }
        }
    } ਨਹੀਂਤਾਂ ਜੇ (wind->resize_ਕਿਨਾਰਾ & WAYLAND_RESIZE_ਕਿਨਾਰਾ_LR) {
        ਜੇ (ਖਿੜਕੀ->min_aspect != 0.f && aspect < ਖਿੜਕੀ->min_aspect) {
            h = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)req_w / ਖਿੜਕੀ->min_aspect), 1);

            ਜੇ (h < ਖਿੜਕੀ->min_h) {
                w = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->min_h * ਖਿੜਕੀ->min_aspect), 1);
            }
            ਜੇ (ਖਿੜਕੀ->max_h && h > ਖਿੜਕੀ->max_h) {
                w = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->max_h * ਖਿੜਕੀ->min_aspect), 1);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->max_aspect != 0.f && aspect > ਖਿੜਕੀ->max_aspect) {
            h = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)req_w / ਖਿੜਕੀ->max_aspect), 1);

            ਜੇ (h < ਖਿੜਕੀ->min_h) {
                w = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->min_h * ਖਿੜਕੀ->max_aspect), 1);
            }
            ਜੇ (ਖਿੜਕੀ->max_h && h > ਖਿੜਕੀ->max_h) {
                w = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->max_h * ਖਿੜਕੀ->max_aspect), 1);
            }
        }
    } ਨਹੀਂਤਾਂ ਜੇ (wind->resize_ਕਿਨਾਰਾ & WAYLAND_RESIZE_ਕਿਨਾਰਾ_TB) {
        ਜੇ (ਖਿੜਕੀ->min_aspect != 0.f && aspect < ਖਿੜਕੀ->min_aspect) {
            w = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)req_h * ਖਿੜਕੀ->min_aspect), 1);

            ਜੇ (w < ਖਿੜਕੀ->min_w) {
                h = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->min_w / ਖਿੜਕੀ->min_aspect), 1);
            }
            ਜੇ (ਖਿੜਕੀ->max_w && w > ਖਿੜਕੀ->max_w) {
                h = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->max_w / ਖਿੜਕੀ->min_aspect), 1);
            }
        } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->max_aspect != 0.f && aspect > ਖਿੜਕੀ->max_aspect) {
            w = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)req_h * ਖਿੜਕੀ->max_aspect), 1);

            ਜੇ (w < ਖਿੜਕੀ->min_w) {
                h = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->min_w / ਖਿੜਕੀ->max_aspect), 1);
            }
            ਜੇ (ਖਿੜਕੀ->max_w && w > ਖਿੜਕੀ->max_w) {
                h = SDL_max(SDL_lroundf((ਦਸ਼ਮਲਵ)ਖਿੜਕੀ->max_w / ਖਿੜਕੀ->max_aspect), 1);
            }
        }
    }

    ਜੇ (ਖਿੜਕੀ->max_w) {
        w = SDL_min(w, ਖਿੜਕੀ->max_w);
    }
    *ਬਾਹਰਲਾ_w = SDL_max(w, ਖਿੜਕੀ->min_w);

    ਜੇ (ਖਿੜਕੀ->max_h) {
        h = SDL_min(h, ਖਿੜਕੀ->max_h);
    }
    *ਬਾਹਰਲਾ_h = SDL_max(h, ਖਿੜਕੀ->min_h);

}

ਸਥਿਰ ਖਾਲੀ DetermineResizeAxis(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, bool resizing)
{
    /* Try to determine the axis along which the window is being resized.
     *
     * Every compositor is different, and some will start sending strange values once the resize
     * begins, so only the first change is safe to try and determine the resize edge.
     *
     * Some compositors don't send a configure event with the resize flag cleared when the resize ends,
     * so a reset timer is required.
     */
    ਜੇ (resizing) {
        ਅਚਲ Uint64 now = SDL_GetTicksNS();
        ਜੇ (now >= wind->ਆਖਰੀ_resize_event_ਸਮਾਂ_ns + SDL_MS_ਮੰਜ਼ਿਲ_NS(500)) {
            wind->resize_ਕਿਨਾਰਾ = 0;
        }

        wind->ਆਖਰੀ_resize_event_ਸਮਾਂ_ns = now;

        ਜੇ (!wind->resize_ਕਿਨਾਰਾ) {
            ਜੇ (ਚੌੜਾਈ != wind->ਆਖਰੀ_configure.ਚੌੜਾਈ || !ਉਚਾਈ) {
                wind->resize_ਕਿਨਾਰਾ |= WAYLAND_RESIZE_ਕਿਨਾਰਾ_LR;
            }
            ਜੇ (ਉਚਾਈ != wind->ਆਖਰੀ_configure.ਉਚਾਈ || !ਚੌੜਾਈ) {
                wind->resize_ਕਿਨਾਰਾ |= WAYLAND_RESIZE_ਕਿਨਾਰਾ_TB;
            }
        }
    } ਨਹੀਂਤਾਂ {
        wind->resize_ਕਿਨਾਰਾ = 0;
    }

    wind->resizing = resizing;
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_toplevel_configure(ਖਾਲੀ *ਅੰਕੜੇ,
                                          ਬਣਤਰ xdg_toplevel *xdg_toplevel,
                                          int32_t ਚੌੜਾਈ,
                                          int32_t ਉਚਾਈ,
                                          ਬਣਤਰ wl_array *ਹਾਲਤਾਂ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = wind->sdlwindow;

    ਗਿਣਤੀ xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool ਸਰਗਰਮ = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, ਹਾਲਤਾਂ) {
        ਚੋਣ (*state) {
        ਹਾਲਤ XDG_TOPLEVEL_STATE_FULLSCREEN:
            fullscreen = true;
            floating = false;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_STATE_MAXIMIZED:
            maximized = true;
            floating = false;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_STATE_RESIZING:
            resizing = true;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_STATE_ACTIVATED:
            ਸਰਗਰਮ = true;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_STATE_TILED_ਖੱਬਾ:
        ਹਾਲਤ XDG_TOPLEVEL_STATE_TILED_ਸੱਜਾ:
        ਹਾਲਤ XDG_TOPLEVEL_STATE_TILED_ਸਿਖਰ:
        ਹਾਲਤ XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_STATE_CONSTRAINED_ਖੱਬਾ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ਖੱਬਾ;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_STATE_CONSTRAINED_ਸੱਜਾ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ਸੱਜਾ;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_STATE_CONSTRAINED_ਸਿਖਰ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ਸਿਖਰ;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_STATE_CONSTRAINED_BOTTOM:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
            ਰੋਕੋ;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }

    /* Configure sizes are in window geometry space; add the border insets, if any, to get
     * the surface size. Maximized and fullscreen windows must use the configured size as-is,
     * so a change in inset applicability requires re-adopting even an unchanged size, and
     * sizes adopted from the cached window size are converted back to geometry space for
     * the last_configure store.
     */
    ਅਚਲ bool insets_apply = wind->enable_insets && !fullscreen && !maximized;

    // When resizing, dimensions other than 0 are a maximum.
    ਅਚਲ bool new_configure_ਮਾਪ = ਚੌੜਾਈ != wind->ਆਖਰੀ_configure.ਚੌੜਾਈ || ਉਚਾਈ != wind->ਆਖਰੀ_configure.ਉਚਾਈ ||
                                    insets_apply != wind->ਆਖਰੀ_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    ਜੇ (insets_apply) {
        GetBorderInsets(ਖਿੜਕੀ, &insets);
    }

    DetermineResizeAxis(wind, ਚੌੜਾਈ, ਉਚਾਈ, resizing);
    Update_ਖਿੜਕੀ_Fullscreen(ਖਿੜਕੀ, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from xdg-shell, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    ਜੇ (ਸਰਗਰਮ || !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED)) {
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESTORED, 0, 0);
        }
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ,
                            (maximized && !fullscreen) ? SDL_EVENT_ਖਿੜਕੀ_MAXIMIZED : SDL_EVENT_ਖਿੜਕੀ_RESTORED,
                            0, 0);
    }

    ਜੇ (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE) || maximized) {
            ਜੇ (!ਚੌੜਾਈ) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                ਜੇ (floating) {
                    ਚੌੜਾਈ = ਖਿੜਕੀ->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ਜੇ (wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE && wind->toplevel_bounds.ਚੌੜਾਈ) {
                        ਚੌੜਾਈ = SDL_min(wind->toplevel_bounds.ਚੌੜਾਈ, ਚੌੜਾਈ);
                    }
                } ਨਹੀਂਤਾਂ {
                    ਚੌੜਾਈ = ਖਿੜਕੀ->windowed.w;
                }

                ਜੇ (!wind->scale_ਮੰਜ਼ਿਲ_display) {
                    wind->requested.logical_ਚੌੜਾਈ = ਚੌੜਾਈ;
                } ਨਹੀਂਤਾਂ {
                    wind->requested.pixel_ਚੌੜਾਈ = ਚੌੜਾਈ;
                    ਚੌੜਾਈ = wind->requested.logical_ਚੌੜਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਚੌੜਾਈ);
                }
                ਚੌੜਾਈ = SDL_max(ਚੌੜਾਈ - (insets.ਖੱਬਾ + insets.ਸੱਜਾ), 1);
            } ਨਹੀਂਤਾਂ ਜੇ (new_configure_ਮਾਪ) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_ਚੌੜਾਈ = ਚੌੜਾਈ + (insets.ਖੱਬਾ + insets.ਸੱਜਾ);

                ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
                    wind->requested.pixel_ਚੌੜਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ, wind->requested.logical_ਚੌੜਾਈ);
                }
            }
            ਜੇ (!ਉਚਾਈ) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                ਜੇ (floating) {
                    ਉਚਾਈ = ਖਿੜਕੀ->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ਜੇ (wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE && wind->toplevel_bounds.ਉਚਾਈ) {
                        ਉਚਾਈ = SDL_min(wind->toplevel_bounds.ਉਚਾਈ, ਉਚਾਈ);
                    }
                } ਨਹੀਂਤਾਂ {
                    ਉਚਾਈ = ਖਿੜਕੀ->windowed.h;
                }

                ਜੇ (!wind->scale_ਮੰਜ਼ਿਲ_display) {
                    wind->requested.logical_ਉਚਾਈ = ਉਚਾਈ;
                } ਨਹੀਂਤਾਂ {
                    wind->requested.pixel_ਉਚਾਈ = ਉਚਾਈ;
                    ਉਚਾਈ = wind->requested.logical_ਉਚਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਉਚਾਈ);
                }
                ਉਚਾਈ = SDL_max(ਉਚਾਈ - (insets.ਸਿਖਰ + insets.bottom), 1);
            } ਨਹੀਂਤਾਂ ਜੇ (new_configure_ਮਾਪ) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_ਉਚਾਈ = ਉਚਾਈ + (insets.ਸਿਖਰ + insets.bottom);

                ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
                    wind->requested.pixel_ਉਚਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ, wind->requested.logical_ਉਚਾਈ);
                }
            }
        } ਨਹੀਂਤਾਂ {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            ਜੇ (!wind->scale_ਮੰਜ਼ਿਲ_display) {
                ਚੌੜਾਈ = wind->requested.logical_ਚੌੜਾਈ = ਖਿੜਕੀ->floating.w;
                ਉਚਾਈ = wind->requested.logical_ਉਚਾਈ = ਖਿੜਕੀ->floating.h;
            } ਨਹੀਂਤਾਂ {
                wind->requested.pixel_ਚੌੜਾਈ = ਖਿੜਕੀ->floating.w;
                wind->requested.pixel_ਉਚਾਈ = ਖਿੜਕੀ->floating.h;
                ਚੌੜਾਈ = wind->requested.logical_ਚੌੜਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਖਿੜਕੀ->floating.w);
                ਉਚਾਈ = wind->requested.logical_ਉਚਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਖਿੜਕੀ->floating.h);
            }
            ਚੌੜਾਈ = SDL_max(ਚੌੜਾਈ - (insets.ਖੱਬਾ + insets.ਸੱਜਾ), 1);
            ਉਚਾਈ = SDL_max(ਉਚਾਈ - (insets.ਸਿਖਰ + insets.bottom), 1);
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
        ਜੇ (floating) {
            ਜੇ (!wind->scale_ਮੰਜ਼ਿਲ_display) {
                ApplyGeometryLimits(ਖਿੜਕੀ, wind->requested.logical_ਚੌੜਾਈ, wind->requested.logical_ਉਚਾਈ, &wind->requested.logical_ਚੌੜਾਈ, &wind->requested.logical_ਉਚਾਈ);
            } ਨਹੀਂਤਾਂ {
                ApplyGeometryLimits(ਖਿੜਕੀ, wind->requested.pixel_ਚੌੜਾਈ, wind->requested.pixel_ਉਚਾਈ, &wind->requested.pixel_ਚੌੜਾਈ, &wind->requested.pixel_ਉਚਾਈ);

                wind->requested.logical_ਚੌੜਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, wind->requested.pixel_ਚੌੜਾਈ);
                wind->requested.logical_ਉਚਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, wind->requested.pixel_ਉਚਾਈ);
            }
        }
    } ਨਹੀਂਤਾਂ {
        // Fullscreen windows know their exact size.
        ਜੇ (ਚੌੜਾਈ == 0 || ਉਚਾਈ == 0) {
            ਚੌੜਾਈ = wind->requested.logical_ਚੌੜਾਈ;
            ਉਚਾਈ = wind->requested.logical_ਉਚਾਈ;
        } ਨਹੀਂਤਾਂ {
            wind->requested.logical_ਚੌੜਾਈ = ਚੌੜਾਈ;
            wind->requested.logical_ਉਚਾਈ = ਉਚਾਈ;
        }

        ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
            wind->requested.pixel_ਚੌੜਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ, ਚੌੜਾਈ);
            wind->requested.pixel_ਉਚਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ, ਉਚਾਈ);
        }
    }

    wind->ਆਖਰੀ_configure.ਚੌੜਾਈ = ਚੌੜਾਈ;
    wind->ਆਖਰੀ_configure.ਉਚਾਈ = ਉਚਾਈ;
    wind->ਆਖਰੀ_configure.insets_apply = insets_apply;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->ਸਰਗਰਮ = ਸਰਗਰਮ;
    ਖਿੜਕੀ->tiled = tiled;
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_toplevel_close(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ xdg_toplevel *xdg_toplevel)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ->sdlwindow, SDL_EVENT_ਖਿੜਕੀ_CLOSE_REQUESTED, 0, 0);
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_toplevel_configure_bounds(ਖਾਲੀ *ਅੰਕੜੇ,
                                                 ਬਣਤਰ xdg_toplevel *xdg_toplevel,
                                                 int32_t ਚੌੜਾਈ, int32_t ਉਚਾਈ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    ਖਿੜਕੀ->toplevel_bounds.ਚੌੜਾਈ = ਚੌੜਾਈ;
    ਖਿੜਕੀ->toplevel_bounds.ਉਚਾਈ = ਉਚਾਈ;
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_toplevel_wm_capabilities(ਖਾਲੀ *ਅੰਕੜੇ,
                                                ਬਣਤਰ xdg_toplevel *xdg_toplevel,
                                                ਬਣਤਰ wl_array *capabilities)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    ਗਿਣਤੀ xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        ਚੋਣ (*wm_cap) {
        ਹਾਲਤ XDG_TOPLEVEL_WM_CAPABILITIES_ਖਿੜਕੀ_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_ਖਿੜਕੀ_MENU;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_WM_CAPABILITIES_MAXIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MAXIMIZE;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_WM_CAPABILITIES_FULLSCREEN:
            wind->wm_caps |= WAYLAND_WM_CAPS_FULLSCREEN;
            ਰੋਕੋ;
        ਹਾਲਤ XDG_TOPLEVEL_WM_CAPABILITIES_MINIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MINIMIZE;
            ਰੋਕੋ;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ xdg_toplevel_listener toplevel_listener_xdg = {
    handle_xdg_toplevel_configure,
    handle_xdg_toplevel_close,
    handle_xdg_toplevel_configure_bounds, // Version 4
    handle_xdg_toplevel_wm_capabilities   // Version 5
};

ਸਥਿਰ ਖਾਲੀ handle_xdg_popup_configure(ਖਾਲੀ *ਅੰਕੜੇ,
                                       ਬਣਤਰ xdg_popup *xdg_popup,
                                       int32_t x,
                                       int32_t y,
                                       int32_t ਚੌੜਾਈ,
                                       int32_t ਉਚਾਈ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    ਪੂਰਨ ਵਿੱਥ_x = 0, ਵਿੱਥ_y = 0;

    // Adjust the position if it was offset for libdecor
    Adjust_Popup_ਵਿੱਥ(wind->sdlwindow, &ਵਿੱਥ_x, &ਵਿੱਥ_y);
    x -= ਵਿੱਥ_x;
    y -= ਵਿੱਥ_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    ਜੇ (ਚੌੜਾਈ == 0 || ਉਚਾਈ == 0) {
        ਚੌੜਾਈ = wind->sdlwindow->floating.w;
        ਉਚਾਈ = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    ਜੇ (ਚੌੜਾਈ != wind->ਆਖਰੀ_configure.ਚੌੜਾਈ || ਉਚਾਈ != wind->ਆਖਰੀ_configure.ਉਚਾਈ) {
        wind->requested.logical_ਚੌੜਾਈ = ਚੌੜਾਈ;
        wind->requested.logical_ਉਚਾਈ = ਉਚਾਈ;

        ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
            wind->requested.pixel_ਚੌੜਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(wind->sdlwindow, ਚੌੜਾਈ);
            wind->requested.pixel_ਉਚਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(wind->sdlwindow, ਉਚਾਈ);
        }
    }

    ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
        x = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(wind->sdlwindow->ਮਾਪਾ, x);
        y = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(wind->sdlwindow->ਮਾਪਾ, y);
    }

    SDL_Send_ਖਿੜਕੀ_Event(wind->sdlwindow, SDL_EVENT_ਖਿੜਕੀ_MOVED, x, y);

    wind->ਆਖਰੀ_configure.ਚੌੜਾਈ = ਚੌੜਾਈ;
    wind->ਆਖਰੀ_configure.ਉਚਾਈ = ਉਚਾਈ;

    ਜੇ (wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE) {
        wind->shell_surface_ਸਥਿਤੀ = WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_ਚੌਖਟਾ;
    }
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_popup_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ xdg_popup *xdg_popup)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ->sdlwindow, SDL_EVENT_ਖਿੜਕੀ_CLOSE_REQUESTED, 0, 0);
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_popup_repositioned(ਖਾਲੀ *ਅੰਕੜੇ,
                                          ਬਣਤਰ xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_ਪੂਰਾ,
    handle_xdg_popup_repositioned
};

ਸਥਿਰ ਖਾਲੀ handle_xdg_toplevel_decoration_configure(ਖਾਲੀ *ਅੰਕੜੇ,
                                                     ਬਣਤਰ zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
                                                     uint32_t ਬਹੁਲਕ)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = (SDL_ਖਿੜਕੀ *)ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    /* If the compositor tries to force CSD anyway, bail on direct XDG support
     * and fall back to libdecor, it will handle these events from then on.
     *
     * To do this we have to fully unmap, then map with libdecor loaded.
     */
    ਜੇ (ਬਹੁਲਕ == ZXDG_TOPLEVEL_DECORATION_V1_ਬਹੁਲਕ_CLIENT_SIDE) {
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            ਵਾਪਸ;
        }
        ਜੇ (!Wayland_ਲੱਦੋ_Libdecor(ਅੰਦਰੂਨੀ->wayland_ਅੰਕੜੇ, true)) {
            // libdecor isn't available, so no borders for you... oh well
            ਵਾਪਸ;
        }
        WAYLAND_wl_display_roundtrip(ਅੰਦਰੂਨੀ->wayland_ਅੰਕੜੇ->display);

        Wayland_Hide_ਖਿੜਕੀ(device, ਖਿੜਕੀ);
        ਅੰਦਰੂਨੀ->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_Show_ਖਿੜਕੀ(device, ਖਿੜਕੀ);
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
    handle_xdg_toplevel_decoration_configure
};

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
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
ਸਥਿਰ ਖਾਲੀ OverrideLibdecorLimits(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    ਜੇ (!libdecor_ਚੌਖਟਾ_get_min_content_ਮਾਪ) {
        libdecor_ਚੌਖਟਾ_ਸੈੱਟ_min_content_ਮਾਪ(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->shell_surface.libdecor.ਚੌਖਟਾ, ਖਿੜਕੀ->min_w, ਖਿੜਕੀ->min_h);
    }
#ਜਾਂਜੇ !SDL_LIBDECOR_CHECK_ਸੰਸਕਰਣ(0, 2, 0)
    libdecor_ਚੌਖਟਾ_ਸੈੱਟ_min_content_ਮਾਪ(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->shell_surface.libdecor.ਚੌਖਟਾ, ਖਿੜਕੀ->min_w, ਖਿੜਕੀ->min_h);
#ਜੇ_ਅੰਤ
}

/*
 * NOTE: Retrieves the minimum content size limits, if the function for doing so is available.
 *       On versions of libdecor that lack the minimum content size retrieval function, this
 *       function is a no-op.
 *
 *       Can be replaced with a direct call if the minimum required version of libdecor is raised
 *       to 0.1.2 or higher.
 */
ਸਥਿਰ ਖਾਲੀ Libdecor_Get_Min_Content_ਮਾਪ(ਬਣਤਰ libdecor_ਚੌਖਟਾ *ਚੌਖਟਾ, ਪੂਰਨ *min_w, ਪੂਰਨ *min_h)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    ਜੇ (libdecor_ਚੌਖਟਾ_get_min_content_ਮਾਪ != ਨਿਰਾ) {
        libdecor_ਚੌਖਟਾ_get_min_content_ਮਾਪ(ਚੌਖਟਾ, min_w, min_h);
    }
#ਜਾਂਜੇ SDL_LIBDECOR_CHECK_ਸੰਸਕਰਣ(0, 2, 0)
    libdecor_ਚੌਖਟਾ_get_min_content_ਮਾਪ(ਚੌਖਟਾ, min_w, min_h);
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਖਾਲੀ decoration_ਚੌਖਟਾ_configure(ਬਣਤਰ libdecor_ਚੌਖਟਾ *ਚੌਖਟਾ,
                                       ਬਣਤਰ libdecor_configuration *configuration,
                                       ਖਾਲੀ *user_ਅੰਕੜੇ_2)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)user_ਅੰਕੜੇ_2;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = wind->sdlwindow;

    ਗਿਣਤੀ libdecor_ਖਿੜਕੀ_state ਖਿੜਕੀ_state;
    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;

    bool ਸਰਗਰਮ = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    ਸਥਿਰ ਅਚਲ ਗਿਣਤੀ libdecor_ਖਿੜਕੀ_state tiled_ਹਾਲਤਾਂ = (LIBDECOR_ਖਿੜਕੀ_STATE_TILED_ਖੱਬਾ | LIBDECOR_ਖਿੜਕੀ_STATE_TILED_ਸੱਜਾ |
                                                            LIBDECOR_ਖਿੜਕੀ_STATE_TILED_ਸਿਖਰ | LIBDECOR_ਖਿੜਕੀ_STATE_TILED_BOTTOM);

    ਜੇ (wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE) {
        Libdecor_Get_Min_Content_ਮਾਪ(ਚੌਖਟਾ, &wind->system_limits.min_ਚੌੜਾਈ_2, &wind->system_limits.min_ਉਚਾਈ_2);
    }

    // Window State
    ਜੇ (libdecor_configuration_get_ਖਿੜਕੀ_state(configuration, &ਖਿੜਕੀ_state)) {
        fullscreen = (ਖਿੜਕੀ_state & LIBDECOR_ਖਿੜਕੀ_STATE_FULLSCREEN) != 0;
        maximized = (ਖਿੜਕੀ_state & LIBDECOR_ਖਿੜਕੀ_STATE_MAXIMIZED) != 0;
        ਸਰਗਰਮ = (ਖਿੜਕੀ_state & LIBDECOR_ਖਿੜਕੀ_STATE_ਸਰਗਰਮ) != 0;
        tiled = (ਖਿੜਕੀ_state & tiled_ਹਾਲਤਾਂ) != 0;
#ਜੇ SDL_LIBDECOR_CHECK_ਸੰਸਕਰਣ(0, 2, 0)
        suspended = (ਖਿੜਕੀ_state & LIBDECOR_ਖਿੜਕੀ_STATE_SUSPENDED) != 0;
#ਜੇ_ਅੰਤ
#ਜੇ SDL_LIBDECOR_CHECK_ਸੰਸਕਰਣ(0, 3, 0)
        resizing = (ਖਿੜਕੀ_state & LIBDECOR_ਖਿੜਕੀ_STATE_RESIZING) != 0;

        ਜੇ (ਖਿੜਕੀ_state & LIBDECOR_ਖਿੜਕੀ_STATE_CONSTRAINED_ਖੱਬਾ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ਖੱਬਾ;
        }
        ਜੇ (ਖਿੜਕੀ_state & LIBDECOR_ਖਿੜਕੀ_STATE_CONSTRAINED_ਸੱਜਾ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ਸੱਜਾ;
        }
        ਜੇ (ਖਿੜਕੀ_state & LIBDECOR_ਖਿੜਕੀ_STATE_CONSTRAINED_ਸਿਖਰ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ਸਿਖਰ;
        }
        ਜੇ (ਖਿੜਕੀ_state & LIBDECOR_ਖਿੜਕੀ_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#ਜੇ_ਅੰਤ
    }
    ਅਚਲ bool floating = !(fullscreen || maximized || tiled);

    Update_ਖਿੜਕੀ_Fullscreen(ਖਿੜਕੀ, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from libdecor, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    ਜੇ (ਸਰਗਰਮ || !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED)) {
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESTORED, 0, 0);
        }
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ,
                            (maximized && !fullscreen) ? SDL_EVENT_ਖਿੜਕੀ_MAXIMIZED : SDL_EVENT_ਖਿੜਕੀ_RESTORED,
                            0, 0);
    }

    /* For fullscreen or fixed-size windows we know our size.
     * Always assume the configure is wrong.
     */
    ਜੇ (fullscreen) {
        ਜੇ (!libdecor_configuration_get_content_ਮਾਪ(configuration, ਚੌਖਟਾ, &ਚੌੜਾਈ, &ਉਚਾਈ)) {
            ਚੌੜਾਈ = wind->requested.logical_ਚੌੜਾਈ;
            ਉਚਾਈ = wind->requested.logical_ਉਚਾਈ;
        } ਨਹੀਂਤਾਂ {
            // Fullscreen windows know their exact size.
            wind->requested.logical_ਚੌੜਾਈ = ਚੌੜਾਈ;
            wind->requested.logical_ਉਚਾਈ = ਉਚਾਈ;

            ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
                wind->requested.pixel_ਚੌੜਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ, ਚੌੜਾਈ);
                wind->requested.pixel_ਉਚਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ, ਉਚਾਈ);
            }
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            ਜੇ (!wind->scale_ਮੰਜ਼ਿਲ_display) {
                ਚੌੜਾਈ = wind->requested.logical_ਚੌੜਾਈ = ਖਿੜਕੀ->floating.w;
                ਉਚਾਈ = wind->requested.logical_ਉਚਾਈ = ਖਿੜਕੀ->floating.h;
            } ਨਹੀਂਤਾਂ {
                wind->requested.pixel_ਚੌੜਾਈ = ਖਿੜਕੀ->floating.w;
                wind->requested.pixel_ਉਚਾਈ = ਖਿੜਕੀ->floating.h;
                ਚੌੜਾਈ = wind->requested.logical_ਚੌੜਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਖਿੜਕੀ->floating.w);
                ਉਚਾਈ = wind->requested.logical_ਉਚਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਖਿੜਕੀ->floating.h);
            }

            OverrideLibdecorLimits(ਖਿੜਕੀ);
        } ਨਹੀਂਤਾਂ {
            /* XXX: The libdecor cairo plugin sends bogus content sizes that add the
             *      height of the title bar when transitioning from a fixed-size to
             *      floating state. Ignore the sent window dimensions in this case,
             *      in favor of the cached value to avoid the window increasing in
             *      size after every state transition.
             *
             *      https://gitlab.freedesktop.org/libdecor/libdecor/-/issues/34
             */
            ਜੇ ((floating && (!wind->floating && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS))) ||
                !libdecor_configuration_get_content_ਮਾਪ(configuration, ਚੌਖਟਾ, &ਚੌੜਾਈ, &ਉਚਾਈ)) {
                ਚੌੜਾਈ = 0;
                ਉਚਾਈ = 0;
            }

            ਅਚਲ bool new_configure_ਮਾਪ = ਚੌੜਾਈ != wind->ਆਖਰੀ_configure.ਚੌੜਾਈ || ਉਚਾਈ != wind->ਆਖਰੀ_configure.ਉਚਾਈ;
            DetermineResizeAxis(wind, ਚੌੜਾਈ, ਉਚਾਈ, resizing);

            ਜੇ (!ਚੌੜਾਈ) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                ਜੇ (floating) {
                    ਚੌੜਾਈ = ਖਿੜਕੀ->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ਜੇ (wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE && wind->toplevel_bounds.ਚੌੜਾਈ) {
                        ਚੌੜਾਈ = SDL_min(wind->toplevel_bounds.ਚੌੜਾਈ, ਚੌੜਾਈ);
                    }
                } ਨਹੀਂਤਾਂ {
                    ਚੌੜਾਈ = ਖਿੜਕੀ->windowed.w;
                }

                ਜੇ (!wind->scale_ਮੰਜ਼ਿਲ_display) {
                    wind->requested.logical_ਚੌੜਾਈ = ਚੌੜਾਈ;
                } ਨਹੀਂਤਾਂ {
                    wind->requested.pixel_ਚੌੜਾਈ = ਚੌੜਾਈ;
                    ਚੌੜਾਈ = wind->requested.logical_ਚੌੜਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਚੌੜਾਈ);
                }
            } ਨਹੀਂਤਾਂ {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                ਜੇ (new_configure_ਮਾਪ &&
                    !(wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_ਚੌਖਟਾ && wind->suspended != suspended)) {
                    wind->requested.logical_ਚੌੜਾਈ = ਚੌੜਾਈ;

                    ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
                        wind->requested.pixel_ਚੌੜਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ, ਚੌੜਾਈ);
                    }
                }
            }

            ਜੇ (!ਉਚਾਈ) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                ਜੇ (floating) {
                    ਉਚਾਈ = ਖਿੜਕੀ->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ਜੇ (wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE && wind->toplevel_bounds.ਉਚਾਈ) {
                        ਉਚਾਈ = SDL_min(wind->toplevel_bounds.ਉਚਾਈ, ਉਚਾਈ);
                    }
                } ਨਹੀਂਤਾਂ {
                    ਉਚਾਈ = ਖਿੜਕੀ->windowed.h;
                }

                ਜੇ (!wind->scale_ਮੰਜ਼ਿਲ_display) {
                    wind->requested.logical_ਉਚਾਈ = ਉਚਾਈ;
                } ਨਹੀਂਤਾਂ {
                    wind->requested.pixel_ਉਚਾਈ = ਉਚਾਈ;
                    ਉਚਾਈ = wind->requested.logical_ਉਚਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਉਚਾਈ);
                }
            } ਨਹੀਂਤਾਂ {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                ਜੇ (new_configure_ਮਾਪ &&
                    !(wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_ਚੌਖਟਾ && wind->suspended != suspended)) {
                    wind->requested.logical_ਉਚਾਈ = ਉਚਾਈ;

                    ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
                        wind->requested.pixel_ਉਚਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ, ਉਚਾਈ);
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
        ਜੇ (floating) {
            ਜੇ (!wind->scale_ਮੰਜ਼ਿਲ_display) {
                ApplyGeometryLimits(ਖਿੜਕੀ, wind->requested.logical_ਚੌੜਾਈ, wind->requested.logical_ਉਚਾਈ, &wind->requested.logical_ਚੌੜਾਈ, &wind->requested.logical_ਉਚਾਈ);
            } ਨਹੀਂਤਾਂ {
                ApplyGeometryLimits(ਖਿੜਕੀ, wind->requested.pixel_ਚੌੜਾਈ, wind->requested.pixel_ਉਚਾਈ, &wind->requested.pixel_ਚੌੜਾਈ, &wind->requested.pixel_ਉਚਾਈ);

                wind->requested.logical_ਚੌੜਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, wind->requested.pixel_ਚੌੜਾਈ);
                wind->requested.logical_ਉਚਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, wind->requested.pixel_ਉਚਾਈ);
            }
        }
    }

    // Store the new state.
    ਅਚਲ bool started_resize = !wind->resizing && resizing;
    wind->ਆਖਰੀ_configure.ਚੌੜਾਈ = ਚੌੜਾਈ;
    wind->ਆਖਰੀ_configure.ਉਚਾਈ = ਉਚਾਈ;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->ਸਰਗਰਮ = ਸਰਗਰਮ;
    ਖਿੜਕੀ->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#ਜੇ SDL_LIBDECOR_CHECK_ਸੰਸਕਰਣ(0, 3, 0)
    ਗਿਣਤੀ libdecor_wm_capabilities caps;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    ਜੇ (libdecor_ਚੌਖਟਾ_get_wm_capabilities) {
        caps = libdecor_ਚੌਖਟਾ_get_wm_capabilities(wind->shell_surface.libdecor.ਚੌਖਟਾ);
#ਨਹੀਂਤਾਂ
    caps = libdecor_ਚੌਖਟਾ_get_wm_capabilities(wind->shell_surface.libdecor.ਚੌਖਟਾ);
    {
#ਜੇ_ਅੰਤ
        wind->wm_caps = 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_ਖਿੜਕੀ_MENU ? WAYLAND_WM_CAPS_ਖਿੜਕੀ_MENU : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MAXIMIZE ? WAYLAND_WM_CAPS_MAXIMIZE : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_FULLSCREEN ? WAYLAND_WM_CAPS_FULLSCREEN : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MINIMIZE ? WAYLAND_WM_CAPS_MINIMIZE : 0;
    }
#ਜੇ_ਅੰਤ

    ਜੇ (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        Configure_ਖਿੜਕੀ_Geometry(ਖਿੜਕੀ);
        ਬਣਤਰ libdecor_state *state = libdecor_state_new(wind->current.logical_ਚੌੜਾਈ, wind->current.logical_ਉਚਾਈ);
        libdecor_ਚੌਖਟਾ_commit(ਚੌਖਟਾ, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        ਜੇ (started_resize) {
            SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_EXPOSED, 0, 0);
        }
    }

    ਜੇ (wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE) {
        wind->shell_surface_ਸਥਿਤੀ = WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_ਚੌਖਟਾ;
    }
}

ਸਥਿਰ ਖਾਲੀ decoration_ਚੌਖਟਾ_close(ਬਣਤਰ libdecor_ਚੌਖਟਾ *ਚੌਖਟਾ, ਖਾਲੀ *user_ਅੰਕੜੇ_2)
{
    SDL_Send_ਖਿੜਕੀ_Event(((SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)user_ਅੰਕੜੇ_2)->sdlwindow, SDL_EVENT_ਖਿੜਕੀ_CLOSE_REQUESTED, 0, 0);
}

ਸਥਿਰ ਖਾਲੀ decoration_ਚੌਖਟਾ_commit(ਬਣਤਰ libdecor_ਚੌਖਟਾ *ਚੌਖਟਾ, ਖਾਲੀ *user_ਅੰਕੜੇ_2)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)user_ਅੰਕੜੇ_2;
    ਜੇ (!wind->suspended && wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN) {
        SDL_Send_ਖਿੜਕੀ_Event(wind->sdlwindow, SDL_EVENT_ਖਿੜਕੀ_EXPOSED, 0, 0);
    }
}

ਸਥਿਰ ਖਾਲੀ decoration_dismiss_popup(ਬਣਤਰ libdecor_ਚੌਖਟਾ *ਚੌਖਟਾ, ਅਚਲ ਅੱਖਰ *seat_name, ਖਾਲੀ *user_ਅੰਕੜੇ_2)
{
    // NOP
}

#ਜੇ SDL_LIBDECOR_CHECK_ਸੰਸਕਰਣ(0, 3, 0)
ਸਥਿਰ ਖਾਲੀ decoration_ਚੌਖਟਾ_bounds(ਬਣਤਰ libdecor_ਚੌਖਟਾ *ਚੌਖਟਾ, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਖਾਲੀ *user_ਅੰਕੜੇ_2)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)user_ਅੰਕੜੇ_2;
    ਖਿੜਕੀ->toplevel_bounds.ਚੌੜਾਈ = ਚੌੜਾਈ;
    ਖਿੜਕੀ->toplevel_bounds.ਉਚਾਈ = ਉਚਾਈ;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਬਣਤਰ libdecor_ਚੌਖਟਾ_interface libdecor_ਚੌਖਟਾ_interface = {
    decoration_ਚੌਖਟਾ_configure,
    decoration_ਚੌਖਟਾ_close,
    decoration_ਚੌਖਟਾ_commit,
    decoration_dismiss_popup,
#ਜੇ SDL_LIBDECOR_CHECK_ਸੰਸਕਰਣ(0, 3, 0)
    decoration_ਚੌਖਟਾ_bounds
#ਜੇ_ਅੰਤ
};
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਖਾਲੀ Wayland_Handle_Preferred_Scale_ਬਦਲਿਆ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਦੁੱਗਣਾ ਗੁਣਕ)
{
    ਅਚਲ ਦੁੱਗਣਾ old_ਗੁਣਕ = ਖਿੜਕੀ_ਅੰਕੜੇ_2->scale_ਗੁਣਕ_2;

    // Round the scale factor if viewports aren't available.
    ਜੇ (!ਖਿੜਕੀ_ਅੰਕੜੇ_2->viewport) {
        ਗੁਣਕ = SDL_ceil(ਗੁਣਕ);
    }

    ਜੇ (ਗੁਣਕ != old_ਗੁਣਕ) {
        ਖਿੜਕੀ_ਅੰਕੜੇ_2->scale_ਗੁਣਕ_2 = ਗੁਣਕ;

        ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->scale_ਮੰਜ਼ਿਲ_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->floating) {
                /* Some compositors will send a configure event immediately after a scale event, however,
                 * this event can contain the old logical size, and should be ignored, or the window can
                 * incorrectly change size when moved between displays with differing scale factors.
                 *
                 * Store the last requested logical size as the last configure size, so a configure event
                 * with the old size will be ignored. Configure sizes are in window geometry space,
                 * so subtract any border insets.
                 */
                BorderInsets insets;
                GetBorderInsets(ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, &insets);
                ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਆਖਰੀ_configure.ਚੌੜਾਈ = SDL_max(ਖਿੜਕੀ_ਅੰਕੜੇ_2->requested.logical_ਚੌੜਾਈ - (insets.ਖੱਬਾ + insets.ਸੱਜਾ), 1);
                ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਆਖਰੀ_configure.ਉਚਾਈ = SDL_max(ਖਿੜਕੀ_ਅੰਕੜੇ_2->requested.logical_ਉਚਾਈ - (insets.ਸਿਖਰ + insets.bottom), 1);

                ਖਿੜਕੀ_ਅੰਕੜੇ_2->requested.logical_ਚੌੜਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, ਖਿੜਕੀ_ਅੰਕੜੇ_2->requested.pixel_ਚੌੜਾਈ);
                ਖਿੜਕੀ_ਅੰਕੜੇ_2->requested.logical_ਉਚਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, ਖਿੜਕੀ_ਅੰਕੜੇ_2->requested.pixel_ਉਚਾਈ);
            } ਨਹੀਂਤਾਂ {
                ਖਿੜਕੀ_ਅੰਕੜੇ_2->requested.pixel_ਚੌੜਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, ਖਿੜਕੀ_ਅੰਕੜੇ_2->requested.logical_ਚੌੜਾਈ);
                ਖਿੜਕੀ_ਅੰਕੜੇ_2->requested.pixel_ਉਚਾਈ = ਬਿੰਦੂ_ਮੰਜ਼ਿਲ_Pixel(ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow, ਖਿੜਕੀ_ਅੰਕੜੇ_2->requested.logical_ਉਚਾਈ);
            }
        }

        ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow->flags & SDL_ਖਿੜਕੀ_ਉੱਚਾ_PIXEL_DENSITY || ਖਿੜਕੀ_ਅੰਕੜੇ_2->scale_ਮੰਜ਼ਿਲ_display) {
            Configure_ਖਿੜਕੀ_Geometry(ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow);
            Commit_Libdecor_ਚੌਖਟਾ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->sdlwindow);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_Maybe_Update_Scale_ਗੁਣਕ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ)
{
    ਦੁੱਗਣਾ ਗੁਣਕ;
    ਪੂਰਨ i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    ਜੇ (ਖਿੜਕੀ->fractional_scale || wl_surface_get_ਸੰਸਕਰਣ(ਖਿੜਕੀ->surface) >= WL_SURFACE_PREFERRED_ਬਫਰ_SCALE_SINCE_ਸੰਸਕਰਣ) {
        ਵਾਪਸ;
    }

    ਜੇ (ਖਿੜਕੀ->ਅੰਕ_outputs != 0) {
        // Check every display's factor, use the highest
        ਗੁਣਕ = 0.0;
        ਲਈ (i = 0; i < ਖਿੜਕੀ->ਅੰਕ_outputs; i++) {
            SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = ਖਿੜਕੀ->outputs[i];
            ਗੁਣਕ = SDL_max(ਗੁਣਕ, ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2);
        }
    } ਨਹੀਂਤਾਂ {
        // All outputs removed, just fall back.
        ਗੁਣਕ = ਖਿੜਕੀ->scale_ਗੁਣਕ_2;
    }

    Wayland_Handle_Preferred_Scale_ਬਦਲਿਆ(ਖਿੜਕੀ, ਗੁਣਕ);
}

ਖਾਲੀ Wayland_Remove_Output_From_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ, SDL_Display_ਅੰਕੜੇ *display_ਅੰਕੜੇ)
{
    ਲਈ (ਪੂਰਨ i = 0; i < ਖਿੜਕੀ->ਅੰਕ_outputs; i++) {
        ਜੇ (ਖਿੜਕੀ->outputs[i] == display_ਅੰਕੜੇ) { // remove this one
            ਜੇ (i == (ਖਿੜਕੀ->ਅੰਕ_outputs - 1)) {
                ਖਿੜਕੀ->outputs[i] = ਨਿਰਾ;
            } ਨਹੀਂਤਾਂ {
                SDL_memmove(&ਖਿੜਕੀ->outputs[i],
                            &ਖਿੜਕੀ->outputs[i + 1],
                            ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ *) * ((ਖਿੜਕੀ->ਅੰਕ_outputs - i) - 1));
            }
            ਖਿੜਕੀ->ਅੰਕ_outputs--;
            i--;
        }
    }

    ਜੇ (ਖਿੜਕੀ->ਅੰਕ_outputs == 0) {
        SDL_free(ਖਿੜਕੀ->outputs);
        ਖਿੜਕੀ->outputs = ਨਿਰਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (!ਖਿੜਕੀ->is_fullscreen || ਖਿੜਕੀ->ਅੰਕ_outputs == 1) {
        Wayland_Update_ਖਿੜਕੀ_Position(ਖਿੜਕੀ->sdlwindow);
        Wayland_Maybe_Update_Scale_ਗੁਣਕ(ਖਿੜਕੀ);
    }
}

ਸਥਿਰ ਖਾਲੀ handle_surface_enter(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_surface *surface, ਬਣਤਰ wl_output *output)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = ਅੰਕੜੇ;
    SDL_Display_ਅੰਕੜੇ *ਅੰਦਰੂਨੀ = wl_output_get_user_ਅੰਕੜੇ(output);
    SDL_Display_ਅੰਕੜੇ **new_outputs;

    ਜੇ (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        ਵਾਪਸ;
    }

    new_outputs = SDL_realloc(ਖਿੜਕੀ->outputs,
                              ਆਕਾਰ(SDL_Display_ਅੰਕੜੇ *) * (ਖਿੜਕੀ->ਅੰਕ_outputs + 1));
    ਜੇ (!new_outputs) {
        ਵਾਪਸ;
    }
    ਖਿੜਕੀ->outputs = new_outputs;
    ਖਿੜਕੀ->outputs[ਖਿੜਕੀ->ਅੰਕ_outputs++] = ਅੰਦਰੂਨੀ;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    ਜੇ (!ਖਿੜਕੀ->is_fullscreen || ਖਿੜਕੀ->ਅੰਕ_outputs == 1) {
        Wayland_Update_ਖਿੜਕੀ_Position(ਖਿੜਕੀ->sdlwindow);
        Wayland_Maybe_Update_Scale_ਗੁਣਕ(ਖਿੜਕੀ);
    }
}

ਸਥਿਰ ਖਾਲੀ handle_surface_leave(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_surface *surface, ਬਣਤਰ wl_output *output)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;

    ਜੇ (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        ਵਾਪਸ;
    }

    Wayland_Remove_Output_From_ਖਿੜਕੀ(ਖਿੜਕੀ, (SDL_Display_ਅੰਕੜੇ *)wl_output_get_user_ਅੰਕੜੇ(output));
}

ਸਥਿਰ ਖਾਲੀ handle_surface_preferred_ਬਫਰ_scale(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_surface *wl_surface, int32_t ਗੁਣਕ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਅੰਕੜੇ;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    ਜੇ (!wind->fractional_scale) {
        Wayland_Handle_Preferred_Scale_ਬਦਲਿਆ(ਅੰਕੜੇ, (ਦੁੱਗਣਾ)ਗੁਣਕ);
    }
}

ਸਥਿਰ ਖਾਲੀ handle_surface_preferred_ਬਫਰ_transform(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_surface *wl_surface, uint32_t transform)
{
    // Nothing to do here.
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_surface_listener surface_listener = {
    handle_surface_enter,
    handle_surface_leave,
    handle_surface_preferred_ਬਫਰ_scale,
    handle_surface_preferred_ਬਫਰ_transform
};

ਸਥਿਰ ਖਾਲੀ handle_fractional_scale_preferred(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wp_fractional_scale_v1 *wp_fractional_scale_v1, uint32_t scale)
{
    ਅਚਲ ਦੁੱਗਣਾ ਗੁਣਕ = (ਦੁੱਗਣਾ)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_Handle_Preferred_Scale_ਬਦਲਿਆ(ਅੰਕੜੇ, ਗੁਣਕ);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

ਸਥਿਰ ਖਾਲੀ frog_preferred_metadata_handler(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
                                            uint32_t output_display_primary_red_x, uint32_t output_display_primary_red_y,
                                            uint32_t output_display_primary_green_x, uint32_t output_display_primary_green_y,
                                            uint32_t output_display_primary_blue_x, uint32_t output_display_primary_blue_y,
                                            uint32_t output_white_ਬਿੰਦੂ_x, uint32_t output_white_ਬਿੰਦੂ_y,
                                            uint32_t max_luminance, uint32_t min_luminance,
                                            uint32_t max_ਭਰਿਆ_ਚੌਖਟਾ_luminance)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    SDL_HDROutputProperties HDR;

    SDL_zero(HDR);

    ਚੋਣ (transfer_function) {
    ਹਾਲਤ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_ST2084_PQ:
        /* ITU-R BT.2408-7 (Sept 2023) has the reference PQ white level at 203 nits,
         * while older Dolby documentation claims a reference level of 100 nits.
         *
         * Use 203 nits for now.
         */
        HDR.HDR_headroom = max_luminance / 203.0f;
        ਰੋਕੋ;
    ਹਾਲਤ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SCRGB_ਰੇਖਿਕ:
        HDR.HDR_headroom = max_luminance / 80.0f;
        ਰੋਕੋ;
    ਹਾਲਤ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_UNDEFINED:
    ਹਾਲਤ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SRGB:
    ਹਾਲਤ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_GAMMA_22:
    ਮੂਲ:
        HDR.HDR_headroom = 1.0f;
        ਰੋਕੋ;
    }

    HDR.SDR_white_level = 1.0f;
    SDL_ਸੈੱਟ_ਖਿੜਕੀ_HDRProperties(wind->sdlwindow, &HDR, true);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


ਸਥਿਰ ਖਾਲੀ handle_surface_feedback_preferred_changed2(ਖਾਲੀ *ਅੰਕੜੇ,
                                                       ਬਣਤਰ wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t ਪਛਾਣ_ਤੱਤ_hi, uint32_t ਪਛਾਣ_ਤੱਤ_lo)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    Wayland_Get_Color_Info_For_ਖਿੜਕੀ(wind, false);
}

ਸਥਿਰ ਖਾਲੀ handle_surface_feedback_preferred_ਬਦਲਿਆ(ਖਾਲੀ *ਅੰਕੜੇ,
                                                      ਬਣਤਰ wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t ਪਛਾਣ_ਤੱਤ)
{
    handle_surface_feedback_preferred_changed2(ਅੰਕੜੇ, wp_color_management_surface_feedback_v1, 0, ਪਛਾਣ_ਤੱਤ);
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_ਬਦਲਿਆ,
    handle_surface_feedback_preferred_changed2
};

ਸਥਿਰ ਖਾਲੀ Wayland_ਸੈੱਟ_Keyboard_Focus(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool ਸੈੱਟ_focus)
{
    SDL_ਖਿੜਕੀ *toplevel = ਖਿੜਕੀ;

    // Find the toplevel parent
    ਜਦੋਂ (SDL_ਖਿੜਕੀ_IS_POPUP(toplevel)) {
        toplevel = toplevel->ਮਾਪਾ;
    }

    toplevel->keyboard_focus = ਖਿੜਕੀ;

    ਜੇ (ਸੈੱਟ_focus && !ਖਿੜਕੀ->is_hiding && !ਖਿੜਕੀ->is_destroying) {
        SDL_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ);
    }
}

bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool enabled)
{
    ਵਾਪਸ true; // just succeed, the real work is done elsewhere.
}

ਸਥਿਰ ਬਣਤਰ xdg_toplevel *Get_Toplevel_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind)
{
    ਜੇ (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
        ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.ਚੌਖਟਾ) {
            ਵਾਪਸ libdecor_ਚੌਖਟਾ_get_xdg_toplevel(wind->shell_surface.libdecor.ਚੌਖਟਾ);
        } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
            ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                ਵਾਪਸ wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    ਵਾਪਸ ਨਿਰਾ;
}

bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ *ਮਾਪਾ_ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਬੱਚਾ_ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਮਾਪਾ_ਅੰਕੜੇ = ਮਾਪਾ_ਖਿੜਕੀ ? ਮਾਪਾ_ਖਿੜਕੀ->ਅੰਦਰੂਨੀ : ਨਿਰਾ;

    ਬੱਚਾ_ਅੰਕੜੇ->reparenting_required = false;

    ਜੇ (ਮਾਪਾ_ਅੰਕੜੇ && ਮਾਪਾ_ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ != WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        ਬੱਚਾ_ਅੰਕੜੇ->reparenting_required = true;
        ਵਾਪਸ true;
    }

    ਬਣਤਰ xdg_toplevel *ਬੱਚਾ_toplevel = Get_Toplevel_For_ਖਿੜਕੀ(ਬੱਚਾ_ਅੰਕੜੇ);
    ਬਣਤਰ xdg_toplevel *ਮਾਪਾ_toplevel = Get_Toplevel_For_ਖਿੜਕੀ(ਮਾਪਾ_ਅੰਕੜੇ);

    ਜੇ (ਬੱਚਾ_toplevel) {
        xdg_toplevel_ਸੈੱਟ_ਮਾਪਾ(ਬੱਚਾ_toplevel, ਮਾਪਾ_toplevel);
    }

    ਵਾਪਸ true;
}

bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Modal(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool modal)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਮਾਪਾ_ਅੰਕੜੇ = ਖਿੜਕੀ->ਮਾਪਾ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਮਾਪਾ_ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ != WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        ਅੰਕੜੇ->reparenting_required = true;
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->reparenting_required = false;
    }

    ਬਣਤਰ xdg_toplevel *toplevel = Get_Toplevel_For_ਖਿੜਕੀ(ਅੰਕੜੇ);

    ਜੇ (toplevel) {
        ਜੇ (viddata->xdg_wm_dialog_v1) {
            ਜੇ (modal) {
                ਜੇ (!ਅੰਕੜੇ->xdg_dialog_v1) {
                    ਅੰਕੜੇ->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_ਸੈੱਟ_modal(ਅੰਕੜੇ->xdg_dialog_v1);
            } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(ਅੰਕੜੇ->xdg_dialog_v1);
            }
        }
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ Wayland_ਰਜਿਸਟਰ_Toplevel_For_Session(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    ਬਣਤਰ xdg_toplevel *toplevel = Get_Toplevel_For_ਖਿੜਕੀ(ਅੰਕੜੇ);
    ਜੇ (!toplevel) {
        ਵਾਪਸ;
    }

    ਅਚਲ ਅੱਖਰ *id = SDL_GetStringProperty(ਅੰਕੜੇ->sdlwindow->props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_ਖਿੜਕੀ_ID_STRING, ਨਿਰਾ);
    ਜੇ (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_Video_ਅੰਕੜੇ *viddata = viddev->ਅੰਦਰੂਨੀ;

        ਜੇ (viddata->xdg_toplevel_ਟੈਗ_manager) {
            xdg_toplevel_ਟੈਗ_manager_v1_ਸੈੱਟ_toplevel_ਟੈਗ(viddata->xdg_toplevel_ਟੈਗ_manager, toplevel, id);
        }

        ਜੇ (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            ਜੇ (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    ਲਈ (SDL_ਖਿੜਕੀ *w = viddev->windows; w; w = w->ਅਗਲਾ) {
                        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *d = w->ਅੰਦਰੂਨੀ;
                        ਜੇ (d->session_id && SDL_strcmp(d->session_id, id) == 0) {
                            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Duplicate window ID string %s found; window will not be added to session", id);
                            ਵਾਪਸ;
                        }
                    }
                }

                ਅੰਕੜੇ->xdg_toplevel_session = xdg_session_v1_restore_toplevel(viddata->xdg_session, toplevel, id);
                ਅੰਕੜੇ->session_id = SDL_strdup(id);
            }
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Wayland_DestroyToplevelSession(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    SDL_Video_ਅੰਕੜੇ *viddata = ਅੰਕੜੇ->wayland_ਅੰਕੜੇ;

    ਜੇ (ਅੰਕੜੇ->xdg_toplevel_session) {
        ਅਚਲ ਅੱਖਰ *id = SDL_GetStringProperty(ਅੰਕੜੇ->sdlwindow->props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_ਖਿੜਕੀ_ID_STRING, ਨਿਰਾ);

        // If the ID string was cleared, remove the window from the session.
        ਜੇ (!id || *id == '\0') {
            xdg_session_v1_remove_toplevel(viddata->xdg_session, ਅੰਕੜੇ->session_id);
        }

        xdg_toplevel_session_v1_destroy(ਅੰਕੜੇ->xdg_toplevel_session);
        ਅੰਕੜੇ->xdg_toplevel_session = ਨਿਰਾ;

        SDL_free(ਅੰਕੜੇ->session_id);
        ਅੰਕੜੇ->session_id = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਖਾਲੀ show_hide_sync_handler(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_callback *callback, uint32_t callback_ਅੰਕੜੇ)
{
    // Get the window from the ID as it may have been destroyed
    SDL_ਖਿੜਕੀ_ID ਖਿੜਕੀ_ID = (SDL_ਖਿੜਕੀ_ID)((uintptr_t)ਅੰਕੜੇ);
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = SDL_Get_ਖਿੜਕੀ_From_ID(ਖਿੜਕੀ_ID);

    ਜੇ (ਖਿੜਕੀ && ਖਿੜਕੀ->ਅੰਦਰੂਨੀ) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

ਸਥਿਰ ਬਣਤਰ wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

ਸਥਿਰ ਖਾਲੀ exported_handle_handler(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ zxdg_exported_v2 *zxdg_exported_v2, ਅਚਲ ਅੱਖਰ *handle)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)ਅੰਕੜੇ;
    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(wind->sdlwindow);

    SDL_ਸੈੱਟ_String_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

ਸਥਿਰ ਬਣਤਰ zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

ਖਾਲੀ Wayland_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *c = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);

    // Custom surfaces don't get toplevels and are always considered 'shown'; nothing to do here.
    ਜੇ (ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        ਵਾਪਸ;
    }

    /* If this is a child window, the parent *must* be in the final shown state,
     * meaning that it has received a configure event, followed by a frame callback.
     * If not, a race condition can result, with effects ranging from the child
     * window to spuriously closing to protocol errors.
     *
     * If waiting on the parent window, set the pending status and the window will
     * be shown when the parent is in the shown state.
     */
    ਜੇ (ਖਿੜਕੀ->ਮਾਪਾ) {
        ਜੇ (ਖਿੜਕੀ->ਮਾਪਾ->ਅੰਦਰੂਨੀ->shell_surface_ਸਥਿਤੀ != WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN) {
            ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ = WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOW_PENDING;
            ਵਾਪਸ;
        }
    }

    // Always roundtrip to ensure there are no pending buffer attachments.
    ਕਰੋ {
        WAYLAND_wl_display_roundtrip(c->display);
    } ਜਦੋਂ (ਅੰਕੜੇ->show_hide_sync_required);

    ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ = WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE;

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
    wl_surface_attach(ਅੰਕੜੇ->surface, ਨਿਰਾ, 0, 0);
    wl_surface_commit(ਅੰਕੜੇ->surface);

    // Create the shell surface and map the toplevel/popup
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਅੰਕੜੇ->shell_surface.libdecor.ਚੌਖਟਾ = libdecor_decorate(c->shell.libdecor,
                                                               ਅੰਕੜੇ->surface,
                                                               &libdecor_ਚੌਖਟਾ_interface,
                                                               ਅੰਕੜੇ);
        ਜੇ (!ਅੰਕੜੇ->shell_surface.libdecor.ਚੌਖਟਾ) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } ਨਹੀਂਤਾਂ {
            libdecor_ਚੌਖਟਾ_ਸੈੱਟ_app_id(ਅੰਕੜੇ->shell_surface.libdecor.ਚੌਖਟਾ, ਅੰਕੜੇ->app_id);
            libdecor_ਚੌਖਟਾ_map(ਅੰਕੜੇ->shell_surface.libdecor.ਚੌਖਟਾ);
            ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_ਚੌਖਟਾ_ਸੈੱਟ_visibility(ਅੰਕੜੇ->shell_surface.libdecor.ਚੌਖਟਾ, false);
            }

            ਜੇ (c->zxdg_exporter_v2) {
                ਅੰਕੜੇ->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, ਅੰਕੜੇ->surface);
                zxdg_exported_v2_ਜੋੜੋ_listener(ਅੰਕੜੇ->exported, &exported_v2_listener, ਅੰਕੜੇ);
            }

            ਜੇ (c->xdg_toplevel_icon_manager_v1 && ਅੰਕੜੇ->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_ਸੈੱਟ_icon(_this->ਅੰਦਰੂਨੀ->xdg_toplevel_icon_manager_v1,
                                                      libdecor_ਚੌਖਟਾ_get_xdg_toplevel(ਅੰਕੜੇ->shell_surface.libdecor.ਚੌਖਟਾ),
                                                      ਅੰਕੜੇ->xdg_toplevel_icon_v1);
            }

            SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_SURFACE_ਸੂਚਕ, libdecor_ਚੌਖਟਾ_get_xdg_surface(ਅੰਕੜੇ->shell_surface.libdecor.ਚੌਖਟਾ));
            SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_TOPLEVEL_ਸੂਚਕ, libdecor_ਚੌਖਟਾ_get_xdg_toplevel(ਅੰਕੜੇ->shell_surface.libdecor.ਚੌਖਟਾ));
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    ਜੇ (ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        ਅੰਕੜੇ->shell_surface.xdg.surface = xdg_wm_ਅਧਾਰ_get_xdg_surface(c->shell.xdg, ਅੰਕੜੇ->surface);
        xdg_surface_ਸੈੱਟ_user_ਅੰਕੜੇ(ਅੰਕੜੇ->shell_surface.xdg.surface, ਅੰਕੜੇ);
        xdg_surface_ਜੋੜੋ_listener(ਅੰਕੜੇ->shell_surface.xdg.surface, &_xdg_surface_listener, ਅੰਕੜੇ);
        SDL_ਸੈੱਟ_ਸੂਚਕ_Property(SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ), SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_SURFACE_ਸੂਚਕ, ਅੰਕੜੇ->shell_surface.xdg.surface);

        ਜੇ (ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_ਖਿੜਕੀ *ਮਾਪਾ = ਖਿੜਕੀ->ਮਾਪਾ;
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਮਾਪਾ_ਅੰਕੜੇ = ਮਾਪਾ->ਅੰਦਰੂਨੀ;
            ਬਣਤਰ xdg_surface *ਮਾਪਾ_xdg_surface = ਨਿਰਾ;
            ਪੂਰਨ position_x = 0, position_y = 0;

            // Configure the popup parameters
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
            ਜੇ (ਮਾਪਾ_ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ਮਾਪਾ_xdg_surface = libdecor_ਚੌਖਟਾ_get_xdg_surface(ਮਾਪਾ_ਅੰਕੜੇ->shell_surface.libdecor.ਚੌਖਟਾ);
            } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
            ਜੇ (ਮਾਪਾ_ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    ਮਾਪਾ_ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                ਮਾਪਾ_xdg_surface = ਮਾਪਾ_ਅੰਕੜੇ->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_positioner = xdg_wm_ਅਧਾਰ_create_positioner(c->shell.xdg);
            xdg_positioner_ਸੈੱਟ_anchor(ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_ਸਿਖਰ_ਖੱਬਾ);
            SDL_Rect ਮਾਪਾ_geometry;
            Get_ਖਿੜਕੀ_Geometry(ਮਾਪਾ->ਅੰਦਰੂਨੀ, &ਮਾਪਾ_geometry);
            xdg_positioner_ਸੈੱਟ_anchor_rect(ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_positioner, 0, 0, ਮਾਪਾ_geometry.w, ਮਾਪਾ_geometry.h);

            ਅਚਲ Uint32 constraint = ਖਿੜਕੀ->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_ਸੈੱਟ_constraint_adjustment(ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_ਸੈੱਟ_gravity(ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_ਸੱਜਾ);
            xdg_positioner_ਸੈੱਟ_ਮਾਪ(ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_positioner, ਅੰਕੜੇ->current.logical_ਚੌੜਾਈ, ਅੰਕੜੇ->current.logical_ਉਚਾਈ);

            // Set the popup initial position
            position_x = ਖਿੜਕੀ->ਆਖਰੀ_position_pending ? ਖਿੜਕੀ->pending.x : ਖਿੜਕੀ->x;
            position_y = ਖਿੜਕੀ->ਆਖਰੀ_position_pending ? ਖਿੜਕੀ->pending.y : ਖਿੜਕੀ->y;
            EnsurePopupPositionIsValid(ਖਿੜਕੀ, &position_x, &position_y);
            ਜੇ (ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display) {
                position_x = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ->ਮਾਪਾ, position_x);
                position_y = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ->ਮਾਪਾ, position_y);
            }
            Adjust_Popup_ਵਿੱਥ(ਖਿੜਕੀ, &position_x, &position_y);
            xdg_positioner_ਸੈੱਟ_ਵਿੱਥ(ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_positioner, position_x, position_y);

            // Assign the popup role
            ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_popup = xdg_surface_get_popup(ਅੰਕੜੇ->shell_surface.xdg.surface,
                                                                                ਮਾਪਾ_xdg_surface,
                                                                                ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_positioner);
            xdg_popup_ਜੋੜੋ_listener(ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_popup, &_xdg_popup_listener, ਅੰਕੜੇ);

            ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TOOLTIP) {
                ਬਣਤਰ wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_ਜੋੜੋ(region, 0, 0, 0, 0);
                wl_surface_ਸੈੱਟ_ਨਿਵੇਸ਼_region(ਅੰਕੜੇ->surface, region);
                wl_region_destroy(region);
            } ਨਹੀਂਤਾਂ ਜੇ ((ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE)) {
                Wayland_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ, true);
            }

            SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_POPUP_ਸੂਚਕ, ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_popup);
            SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_POSITIONER_ਸੂਚਕ, ਅੰਕੜੇ->shell_surface.xdg.popup.xdg_positioner);
        } ਨਹੀਂਤਾਂ {
            ਅੰਕੜੇ->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(ਅੰਕੜੇ->shell_surface.xdg.surface);
            xdg_toplevel_ਸੈੱਟ_app_id(ਅੰਕੜੇ->shell_surface.xdg.toplevel.xdg_toplevel, ਅੰਕੜੇ->app_id);
            xdg_toplevel_ਜੋੜੋ_listener(ਅੰਕੜੇ->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, ਅੰਕੜੇ);

            // Create the window decorations
            ਜੇ (c->decoration_manager) {
                ਅੰਕੜੇ->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, ਅੰਕੜੇ->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_ਜੋੜੋ_listener(ਅੰਕੜੇ->server_decoration, &xdg_toplevel_decoration_listener, ਖਿੜਕੀ);
                ਅਚਲ ਗਿਣਤੀ zxdg_toplevel_decoration_v1_ਬਹੁਲਕ ਬਹੁਲਕ = !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_ਬਹੁਲਕ_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_ਬਹੁਲਕ_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_ਸੈੱਟ_ਬਹੁਲਕ(ਅੰਕੜੇ->server_decoration, ਬਹੁਲਕ);
            }

            ਜੇ (c->zxdg_exporter_v2) {
                ਅੰਕੜੇ->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, ਅੰਕੜੇ->surface);
                zxdg_exported_v2_ਜੋੜੋ_listener(ਅੰਕੜੇ->exported, &exported_v2_listener, ਅੰਕੜੇ);
            }

            ਜੇ (c->xdg_toplevel_icon_manager_v1 && ਅੰਕੜੇ->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_ਸੈੱਟ_icon(_this->ਅੰਦਰੂਨੀ->xdg_toplevel_icon_manager_v1,
                                                      ਅੰਕੜੇ->shell_surface.xdg.toplevel.xdg_toplevel,
                                                      ਅੰਕੜੇ->xdg_toplevel_icon_v1);
            }

            SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_TOPLEVEL_ਸੂਚਕ, ਅੰਕੜੇ->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    // Restore state that was set prior to this call
    Wayland_ਰਜਿਸਟਰ_Toplevel_For_Session(ਅੰਕੜੇ);
    Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(_this, ਖਿੜਕੀ, ਖਿੜਕੀ->ਮਾਪਾ);

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MODAL) {
        Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Modal(_this, ਖਿੜਕੀ, true);
    }

    Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Title(_this, ਖਿੜਕੀ);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਜੇ (ਅੰਕੜੇ->shell_surface.libdecor.ਚੌਖਟਾ) {
            ਜਦੋਂ (ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE) {
                ਜੇ (libdecor_dispatch(c->shell.libdecor, -1) < 0) {
                    ਜੇ (!Wayland_HandleDisplayDisconnected(_this)) {
                        ਵਾਪਸ;
                    }
                }
                ਜੇ (WAYLAND_wl_display_dispatch_pending(c->display) < 0) {
                    ਜੇ (!Wayland_HandleDisplayDisconnected(_this)) {
                        ਵਾਪਸ;
                    }
                }
            }
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP || ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Unlike libdecor we need to call this explicitly to prevent a deadlock.
         * libdecor will call this as part of their configure event!
         * -flibit
         */
        wl_surface_commit(ਅੰਕੜੇ->surface);
        ਜੇ (ਅੰਕੜੇ->shell_surface.xdg.surface) {
            ਜਦੋਂ (ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE) {
                ਜੇ (WAYLAND_wl_display_dispatch(c->display) < 0) {
                    ਜੇ (!Wayland_HandleDisplayDisconnected(_this)) {
                        ਵਾਪਸ;
                    }
                }
            }
        }
    } ਨਹੀਂਤਾਂ {
        // Nothing to see here, just commit.
        wl_surface_commit(ਅੰਕੜੇ->surface);
    }

    // Make sure the window can't be resized to 0, or it can be spuriously closed by the window manager.
    ਅੰਕੜੇ->system_limits.min_ਚੌੜਾਈ_2 = SDL_max(ਅੰਕੜੇ->system_limits.min_ਚੌੜਾਈ_2, 1);
    ਅੰਕੜੇ->system_limits.min_ਉਚਾਈ_2 = SDL_max(ਅੰਕੜੇ->system_limits.min_ਉਚਾਈ_2, 1);

    /* Unlike the rest of window state we have to set this _after_ flushing the
     * display, because we need to create the decorations before possibly hiding
     * them immediately afterward.
     */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        ਜੇ (ਖਿੜਕੀ->windowed.w < ਅੰਕੜੇ->system_limits.min_ਚੌੜਾਈ_2 ||
            ਖਿੜਕੀ->windowed.h < ਅੰਕੜੇ->system_limits.min_ਉਚਾਈ_2) {

            // Warn if the window frame will be larger than the content surface.
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "Window dimensions (%i, %i) are smaller than the system enforced minimum (%i, %i); window borders will be larger than the content surface.",
                        ਖਿੜਕੀ->windowed.w, ਖਿੜਕੀ->windowed.h, ਅੰਕੜੇ->system_limits.min_ਚੌੜਾਈ_2, ਅੰਕੜੇ->system_limits.min_ਉਚਾਈ_2);

            ਅੰਕੜੇ->current.logical_ਚੌੜਾਈ = SDL_max(ਖਿੜਕੀ->windowed.w, ਅੰਕੜੇ->system_limits.min_ਚੌੜਾਈ_2);
            ਅੰਕੜੇ->current.logical_ਉਚਾਈ = SDL_max(ਖਿੜਕੀ->windowed.h, ਅੰਕੜੇ->system_limits.min_ਉਚਾਈ_2);
            Commit_Libdecor_ਚੌਖਟਾ(ਖਿੜਕੀ);
        }
    }
#ਜੇ_ਅੰਤ
    Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(_this, ਖਿੜਕੀ, !!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE));

    // We're finally done putting the window together, raise if possible
    ਜੇ (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_ਖਿੜਕੀ_ACTIVATE_WHEN_SHOWN, true)) {
        /* if the process was passed an activation token, use it when showing
         * the initial window.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ਅਚਲ ਅੱਖਰ *activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
        ਜੇ (activation_token) {
            xdg_activation_v1_activate(c->activation_manager,
                                       activation_token,
                                       ਅੰਕੜੇ->surface);

            // Clear this variable, per the protocol's request
            SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
        } ਨਹੀਂਤਾਂ {
            // Try to generate an activation token for this window.
            Wayland_Raise_ਖਿੜਕੀ(_this, ਖਿੜਕੀ);
        }
    } ਨਹੀਂਤਾਂ {
        // Clear the ignored activation token, as it won't be used.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    }

    // No frame callback on an external surface, as it may already have one attached.
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        ਅੰਕੜੇ->surface_ਚੌਖਟਾ_callback = wl_surface_ਚੌਖਟਾ(ਅੰਕੜੇ->surface);
        wl_callback_ਜੋੜੋ_listener(ਅੰਕੜੇ->surface_ਚੌਖਟਾ_callback, &surface_ਚੌਖਟਾ_listener, ਅੰਕੜੇ);
    }

    ਅੰਕੜੇ->show_hide_sync_required = true;
    ਬਣਤਰ wl_callback *cb = wl_display_sync(_this->ਅੰਦਰੂਨੀ->display);
    wl_callback_ਜੋੜੋ_listener(cb, &show_hide_sync_listener, (ਖਾਲੀ *)((uintptr_t)ਖਿੜਕੀ->id));

    ਅੰਕੜੇ->showing_ਖਿੜਕੀ = true;
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_SHOWN, 0, 0);
    ਅੰਕੜੇ->showing_ਖਿੜਕੀ = false;

    // Send an exposure event to signal that the client should draw.
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_EXPOSED, 0, 0);
}

ਸਥਿਰ ਖਾਲੀ Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *popup)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    ਜੇ (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_ਖਿੜਕੀ)) {
        ਵਾਪਸ;
    }
    popupdata = popup->ਅੰਦਰੂਨੀ;
    ਜੇ (!popupdata) {
        ਵਾਪਸ;
    }

    // This may already be freed by a parent popup!
    ਜੇ (popupdata->shell_surface.xdg.popup.xdg_popup == ਨਿਰਾ) {
        ਵਾਪਸ;
    }

    ਜੇ ((popup->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) && !(popup->flags & SDL_ਖਿੜਕੀ_NOT_FOCUSABLE)) {
        SDL_ਖਿੜਕੀ *new_focus;
        ਅਚਲ bool ਸੈੱਟ_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_ਸੈੱਟ_Keyboard_Focus(new_focus, ਸੈੱਟ_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = ਨਿਰਾ;
    popupdata->shell_surface.xdg.popup.xdg_positioner = ਨਿਰਾ;

    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(popup);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_POPUP_ਸੂਚਕ, ਨਿਰਾ);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_POSITIONER_ਸੂਚਕ, ਨਿਰਾ);
}

ਖਾਲੀ Wayland_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);

    // Custom surfaces have nothing to destroy and are always considered to be 'shown'; nothing to do here.
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        ਵਾਪਸ;
    }

    /* The window was shown, but the sync point hasn't yet been reached.
     * Pump events to avoid a possible protocol violation.
     */
    ਜੇ (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(ਅੰਕੜੇ->display);
    }

    wind->shell_surface_ਸਥਿਤੀ = WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_HIDDEN;

    ਜੇ (wind->surface_ਚੌਖਟਾ_callback) {
        wl_callback_destroy(wind->surface_ਚੌਖਟਾ_callback);
        wind->surface_ਚੌਖਟਾ_callback = ਨਿਰਾ;
    }

    ਜੇ (wind->server_decoration) {
        zxdg_toplevel_decoration_v1_destroy(wind->server_decoration);
        wind->server_decoration = ਨਿਰਾ;
    }

    // Clean up the export handle.
    ਜੇ (wind->exported) {
        zxdg_exported_v2_destroy(wind->exported);
        wind->exported = ਨਿਰਾ;

        SDL_ਸੈੱਟ_String_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, ਨਿਰਾ);
    }

    ਜੇ (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = ਨਿਰਾ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਜੇ (wind->shell_surface.libdecor.ਚੌਖਟਾ) {
            libdecor_ਚੌਖਟਾ_unref(wind->shell_surface.libdecor.ਚੌਖਟਾ);

            SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_SURFACE_ਸੂਚਕ, ਨਿਰਾ);
            SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_TOPLEVEL_ਸੂਚਕ, ਨਿਰਾ);
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, ਖਿੜਕੀ);
        } ਨਹੀਂਤਾਂ ਜੇ (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_TOPLEVEL_ਸੂਚਕ, ਨਿਰਾ);
        }

        ਜੇ (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_XDG_SURFACE_ਸੂਚਕ, ਨਿਰਾ);
        }
    }

    // Attach a null buffer to unmap the surface.
    ਜੇ (wind->ਨਕਾਬ.surface) {
        wl_surface_attach(wind->ਨਕਾਬ.surface, ਨਿਰਾ, 0, 0);
        wl_surface_commit(wind->ਨਕਾਬ.surface);
    }
    wl_surface_attach(wind->surface, ਨਿਰਾ, 0, 0);
    wl_surface_commit(wind->surface);

    // Need to destroy the session object after unmapping the window, or the state may not be saved.
    Wayland_DestroyToplevelSession(wind);

    SDL_zero(wind->shell_surface);
    SDL_zero(wind->explicit_geometry);
    wind->show_hide_sync_required = true;
    ਬਣਤਰ wl_callback *cb = wl_display_sync(_this->ਅੰਦਰੂਨੀ->display);
    wl_callback_ਜੋੜੋ_listener(cb, &show_hide_sync_listener, (ਖਾਲੀ *)((uintptr_t)ਖਿੜਕੀ->id));
}

ਸਥਿਰ ਖਾਲੀ handle_xdg_activation_ਪੂਰਾ(ਖਾਲੀ *ਅੰਕੜੇ,
                                       ਬਣਤਰ xdg_activation_token_v1 *xdg_activation_token_v1,
                                       ਅਚਲ ਅੱਖਰ *token)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ = ਅੰਕੜੇ;
    ਜੇ (xdg_activation_token_v1 == ਖਿੜਕੀ->activation_token) {
        xdg_activation_v1_activate(ਖਿੜਕੀ->wayland_ਅੰਕੜੇ->activation_manager,
                                   token,
                                   ਖਿੜਕੀ->surface);
        xdg_activation_token_v1_destroy(ਖਿੜਕੀ->activation_token);
        ਖਿੜਕੀ->activation_token = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_ਪੂਰਾ
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
ਸਥਿਰ ਖਾਲੀ Wayland_activate_ਖਿੜਕੀ(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ, SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਨਿਸ਼ਾਨਾ_wind, bool ਸੈੱਟ_serial)
{
    SDL_WaylandSeat *seat = ਅੰਕੜੇ->ਆਖਰੀ_implicit_grab_seat;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *focus = ਨਿਰਾ;

    ਜੇ (seat) {
        focus = seat->keyboard.focus;
        ਜੇ (!focus) {
            focus = seat->ਸੂਚਕ_2.focus;
        }
    }

    ਬਣਤਰ wl_surface *requesting_surface = focus ? focus->surface : ਨਿਰਾ;

    ਜੇ (ਅੰਕੜੇ->activation_manager) {
        ਜੇ (ਨਿਸ਼ਾਨਾ_wind->activation_token) {
            // We're about to overwrite this with a new request
            xdg_activation_token_v1_destroy(ਨਿਸ਼ਾਨਾ_wind->activation_token);
        }

        ਨਿਸ਼ਾਨਾ_wind->activation_token = xdg_activation_v1_get_activation_token(ਅੰਕੜੇ->activation_manager);
        xdg_activation_token_v1_ਜੋੜੋ_listener(ਨਿਸ਼ਾਨਾ_wind->activation_token,
                                             &xdg_activation_listener,
                                             ਨਿਸ਼ਾਨਾ_wind);

        /* Note that we are not setting the app_id here.
         *
         * Hypothetically we could set the app_id from data->classname, but
         * that part of the API is for _external_ programs, not ourselves.
         *
         * -flibit
         */
        ਜੇ (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_ਸੈੱਟ_surface(ਨਿਸ਼ਾਨਾ_wind->activation_token, requesting_surface);
        }
        ਜੇ (ਸੈੱਟ_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_ਸੈੱਟ_serial(ਨਿਸ਼ਾਨਾ_wind->activation_token, seat->ਆਖਰੀ_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(ਨਿਸ਼ਾਨਾ_wind->activation_token);
    }
}

ਖਾਲੀ Wayland_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (viddata->activation_manager) {
        /* Check for an activation token, in case the window is being
         * raised in response to a system notification.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ਅਚਲ ਅੱਖਰ *activation_token = SDL_GetNotificationActivationToken();
        ਜੇ (activation_token) {
            xdg_activation_v1_activate(viddata->activation_manager,
                                       activation_token,
                                       wind->surface);
            ਵਾਪਸ;
        }
    }

    // No token? Try to activate the window via an event serial.
    Wayland_activate_ਖਿੜਕੀ(_this->ਅੰਦਰੂਨੀ, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ, true);
}

bool Wayland_Flash_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_FlashOperation operation)
{
    /* Not setting the serial will specify 'urgency' without switching focus as per
     * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
     */
    Wayland_activate_ਖਿੜਕੀ(_this->ਅੰਦਰੂਨੀ, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ, false);
    ਵਾਪਸ true;
}

SDL_Fullscreen_ਨਤੀਜਾ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਬਣਤਰ wl_output *output = display->ਅੰਦਰੂਨੀ->output;

    // Custom surfaces have no toplevel to make fullscreen.
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        ਵਾਪਸ SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    ਜੇ (wind->showing_ਖਿੜਕੀ && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
    }

    ਜੇ (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->ਅੰਦਰੂਨੀ->display);
    }

    // Flushing old events pending a new one, ignore this request.
    ਜੇ (wind->drop_fullscreen_ਬੇਨਤੀਆਂ) {
        ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_ਬੇਨਤੀਆਂ = true;
    FlushPendingEvents(ਖਿੜਕੀ);
    wind->drop_fullscreen_ਬੇਨਤੀਆਂ = false;

    // Nothing to do if the window is not fullscreen, and this isn't an explicit enter request.
    ਜੇ (!wind->is_fullscreen) {
        ਜੇ (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
            // Request was out of date; signal the video core not to update any state.
            ਵਾਪਸ SDL_FULLSCREEN_PENDING;
        } ਨਹੀਂਤਾਂ ਜੇ (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
            // Already not fullscreen; nothing to do.
            ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    // Don't send redundant fullscreen set/unset events.
    ਜੇ (!!fullscreen != wind->is_fullscreen) {
        wind->fullscreen_was_positioned = !!fullscreen;

        /* Only use the specified output if an exclusive mode is being used, or a position was explicitly requested
         * before entering fullscreen desktop. Otherwise, let the compositor handle placement, as it has more
         * information about where the window is and where it should go, particularly if fullscreen is being requested
         * before the window is mapped, or the window spans multiple outputs.
         */
        ਜੇ (!ਖਿੜਕੀ->fullscreen_exclusive) {
            ਜੇ (ਖਿੜਕੀ->undefined_x || ਖਿੜਕੀ->undefined_y ||
                (wind->ਅੰਕ_outputs && !ਖਿੜਕੀ->ਆਖਰੀ_position_pending)) {
                output = ਨਿਰਾ;
            }
        }

        // Commit to set any pending size or limit data.
        ਜੇ (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        ਸੈੱਟ_Fullscreen(ਖਿੜਕੀ, output, !!fullscreen);
    } ਨਹੀਂਤਾਂ ਜੇ (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        ਜੇ (wind->ਆਖਰੀ_display_ID != display->id) {
            wind->fullscreen_was_positioned = true;
            ਸੈੱਟ_Fullscreen(ਖਿੜਕੀ, output, true);
        } ਨਹੀਂਤਾਂ {
            Configure_ਖਿੜਕੀ_Geometry(ਖਿੜਕੀ);
            Commit_Libdecor_ਚੌਖਟਾ(ਖਿੜਕੀ);

            ਵਾਪਸ SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    ਵਾਪਸ SDL_FULLSCREEN_PENDING;
}

ਖਾਲੀ Wayland_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    // Drop restore requests when showing the window.
    ਜੇ (wind->showing_ਖਿੜਕੀ) {
        ਵਾਪਸ;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    ਜੇ (!(ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_FULLSCREEN | SDL_ਖਿੜਕੀ_MAXIMIZED)) &&
        !wind->pending_state_deadline_ਗਿਣਤੀ) {
        ਵਾਪਸ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਜੇ (!wind->shell_surface.libdecor.ਚੌਖਟਾ) {
            ਵਾਪਸ; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_ਚੌਖਟਾ_unset_maximized(wind->shell_surface.libdecor.ਚੌਖਟਾ);
        ਜੋੜੋ_Pending_State_Sync(wind);
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        // Note that xdg-shell does NOT provide a way to unset minimize!
        ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            ਜੇ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ਨਿਰਾ) {
                ਵਾਪਸ; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            ਜੋੜੋ_Pending_State_Sync(wind);
        }
}

ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Bordered(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool bordered)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਅਚਲ SDL_Video_ਅੰਕੜੇ *viddata = (ਅਚਲ SDL_Video_ਅੰਕੜੇ *)_this->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਜੇ (wind->shell_surface.libdecor.ਚੌਖਟਾ) {
            libdecor_ਚੌਖਟਾ_ਸੈੱਟ_visibility(wind->shell_surface.libdecor.ਚੌਖਟਾ, bordered);
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ਜੇ ((viddata->decoration_manager) && (wind->server_decoration)) {
            ਅਚਲ ਗਿਣਤੀ zxdg_toplevel_decoration_v1_ਬਹੁਲਕ ਬਹੁਲਕ = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_ਬਹੁਲਕ_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_ਬਹੁਲਕ_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_ਸੈੱਟ_ਬਹੁਲਕ(wind->server_decoration, ਬਹੁਲਕ);
        }
    }
}

ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    ਸੈੱਟ_Min_Max_Dimensions(ਖਿੜਕੀ);
    Commit_Libdecor_ਚੌਖਟਾ(ਖਿੜਕੀ);

    ਜੇ (wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN) {
        wind->pending_state_commit = true;
    }
}

ਖਾਲੀ Wayland_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->ਅੰਦਰੂਨੀ->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MAXIMIZED) &&
        !wind->pending_state_deadline_ਗਿਣਤੀ) {
        ਵਾਪਸ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਜੇ (!wind->shell_surface.libdecor.ਚੌਖਟਾ) {
            ਵਾਪਸ; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        ਜੇ (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_ਚੌਖਟਾ_ਸੈੱਟ_maximized(wind->shell_surface.libdecor.ਚੌਖਟਾ);
        ਜੋੜੋ_Pending_State_Sync(wind);
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ਜੇ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ਨਿਰਾ) {
            ਵਾਪਸ; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        ਜੇ (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_ਸੈੱਟ_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        ਜੋੜੋ_Pending_State_Sync(wind);
    }
}

ਖਾਲੀ Wayland_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        ਵਾਪਸ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਜੇ (!wind->shell_surface.libdecor.ਚੌਖਟਾ) {
            ਵਾਪਸ; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_ਚੌਖਟਾ_ਸੈੱਟ_minimized(wind->shell_surface.libdecor.ਚੌਖਟਾ);
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MINIMIZED, 0, 0);
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ਜੇ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ਨਿਰਾ) {
            ਵਾਪਸ; // Can't do anything yet, wait for ShowWindow
        }
        xdg_toplevel_ਸੈੱਟ_minimized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_MINIMIZED, 0, 0);
    }
}

bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    /* This may look suspiciously like SetWindowGrab, despite SetMouseRect not
     * implicitly doing a grab. And you're right! Wayland doesn't let us mess
     * around with mouse focus whatsoever, so it just happens to be that the
     * work that we can do in these two functions ends up being the same.
     *
     * Just know that this call lets you confine with a rect, SetWindowGrab
     * lets you confine without a rect.
     */
    ਜੇ (!ਅੰਕੜੇ->ਸੂਚਕ_constraints) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_ਸੂਚਕ_Grabs(ਅੰਕੜੇ, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
    ਵਾਪਸ true;
}

bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (!ਅੰਕੜੇ->ਸੂਚਕ_constraints) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_ਸੂਚਕ_Grabs(ਅੰਕੜੇ, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
    ਵਾਪਸ true;
}

bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਜੇ (!ਅੰਕੜੇ->ਕੁੰਜੀ_inhibitor_manager) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(ਅੰਕੜੇ, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
    ਵਾਪਸ true;
}

bool Wayland_Reconfigure_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ_Flags flags)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    // Don't try to reconfigure mapped windows, unless they are custom or external.
    ਜੇ (ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN &&
        ਅੰਕੜੇ->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        // Window is already mapped; abort.
        ਵਾਪਸ false;
    }

    /* The caller guarantees that only one of the GL or Vulkan flags will be set.
     * Note that Vulkan doesn't require any specific configuration, so only EGL
     * objects are added and removed as required.
     */
    ਜੇ (flags & SDL_ਖਿੜਕੀ_OPENGL) {
        ਜੇ (!ਅੰਕੜੇ->egl_ਖਿੜਕੀ) {
            ਅੰਕੜੇ->egl_ਖਿੜਕੀ = WAYLAND_wl_egl_ਖਿੜਕੀ_create(ਅੰਕੜੇ->surface, ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ, ਅੰਕੜੇ->current.pixel_ਉਚਾਈ);
        }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
        ਅੰਕੜੇ->egl_surface = SDL_EGL_CreateSurface(_this, ਖਿੜਕੀ, (Native_ਖਿੜਕੀ_Type)ਅੰਕੜੇ->egl_ਖਿੜਕੀ);

        ਜੇ (ਅੰਕੜੇ->egl_surface == EGL_NO_SURFACE) {
            ਵਾਪਸ false; // SDL_EGL_CreateSurface should have set the error.
        }
#ਜੇ_ਅੰਤ

        ਜੇ (!ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ) {
            ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ = WAYLAND_wl_display_create_ਕਤਾਰ(ਅੰਕੜੇ->wayland_ਅੰਕੜੇ->display);
            ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(ਅੰਕੜੇ->surface);
            WAYLAND_wl_proxy_ਸੈੱਟ_ਕਤਾਰ((ਬਣਤਰ wl_proxy *)ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper, ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ);
            ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback = wl_surface_ਚੌਖਟਾ(ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper);
            wl_callback_ਜੋੜੋ_listener(ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback, &gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_listener, ਅੰਕੜੇ);
        }
    } ਨਹੀਂਤਾਂ {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
        ਜੇ (ਅੰਕੜੇ->egl_surface) {
            SDL_EGL_DestroySurface(_this, ਅੰਕੜੇ->egl_surface);
            ਅੰਕੜੇ->egl_surface = EGL_NO_SURFACE;
        }
#ਜੇ_ਅੰਤ

        ਜੇ (ਅੰਕੜੇ->egl_ਖਿੜਕੀ) {
            WAYLAND_wl_egl_ਖਿੜਕੀ_destroy(ਅੰਕੜੇ->egl_ਖਿੜਕੀ);
            ਅੰਕੜੇ->egl_ਖਿੜਕੀ = ਨਿਰਾ;
        }

        ਜੇ (ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback) {
            wl_callback_destroy(ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback);
            ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback = ਨਿਰਾ;
        }

        ਜੇ (ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper);
            ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper = ਨਿਰਾ;
        }

        ਜੇ (ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ) {
            WAYLAND_wl_event_ਕਤਾਰ_destroy(ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ);
            ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ = ਨਿਰਾ;
        }
    }

    ਵਾਪਸ true;
}

bool Wayland_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ;
    SDL_Video_ਅੰਕੜੇ *c = _this->ਅੰਦਰੂਨੀ;
    ਬਣਤਰ wl_surface *external_surface = (ਬਣਤਰ wl_surface *)SDL_Get_ਸੂਚਕ_Property(create_props, SDL_PROP_ਖਿੜਕੀ_CREATE_WAYLAND_WL_SURFACE_ਸੂਚਕ,
                                                                               (ਬਣਤਰ wl_surface *)SDL_Get_ਸੂਚਕ_Property(create_props, "sdl2-compat.external_window", ਨਿਰਾ));
    ਅਚਲ bool custom_surface_role = (external_surface != ਨਿਰਾ) || SDL_GetBooleanProperty(create_props, SDL_PROP_ਖਿੜਕੀ_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    ਅਚਲ bool create_egl_ਖਿੜਕੀ = !!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_ਖਿੜਕੀ_CREATE_WAYLAND_CREATE_EGL_ਖਿੜਕੀ_BOOLEAN, false);

    ਅੰਕੜੇ = SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ false;
    }

    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    ਅੰਕੜੇ->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_ਖਿੜਕੀ_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    ਜੇ (ਖਿੜਕੀ->x == SDL_WINDOWPOS_UNDEFINED) {
        ਖਿੜਕੀ->x = 0;
    }
    ਜੇ (ਖਿੜਕੀ->y == SDL_WINDOWPOS_UNDEFINED) {
        ਖਿੜਕੀ->y = 0;
    }

    ਅੰਕੜੇ->wayland_ਅੰਕੜੇ = c;
    ਅੰਕੜੇ->sdlwindow = ਖਿੜਕੀ;

    // Default to all capabilities
    ਅੰਕੜੇ->wm_caps = WAYLAND_WM_CAPS_ALL;

    ਅੰਕੜੇ->scale_ਗੁਣਕ_2 = 1.0;

    ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
        ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display = ਖਿੜਕੀ->ਮਾਪਾ->ਅੰਦਰੂਨੀ->scale_ਮੰਜ਼ਿਲ_display;
        ਅੰਕੜੇ->scale_ਗੁਣਕ_2 = ਖਿੜਕੀ->ਮਾਪਾ->ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2;
        EnsurePopupPositionIsValid(ਖਿੜਕੀ, &ਖਿੜਕੀ->x, &ਖਿੜਕੀ->y);
    } ਨਹੀਂਤਾਂ {
        ਲਈ (ਪੂਰਨ i = 0; i < _this->ਅੰਕ_displays; i++) {
            ਅੰਕੜੇ->scale_ਗੁਣਕ_2 = SDL_max(ਅੰਕੜੇ->scale_ਗੁਣਕ_2, _this->displays[i]->ਅੰਦਰੂਨੀ->scale_ਗੁਣਕ_2);
        }
    }

    ਅੰਕੜੇ->outputs = ਨਿਰਾ;
    ਅੰਕੜੇ->ਅੰਕ_outputs = 0;
    ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display = c->scale_ਮੰਜ਼ਿਲ_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    ਅੰਕੜੇ->app_id = SDL_strdup(SDL_GetAppID());

    ਜੇ (!ਅੰਕੜੇ->scale_ਮੰਜ਼ਿਲ_display) {
        ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ = ਖਿੜਕੀ->floating.w;
        ਅੰਕੜੇ->requested.logical_ਉਚਾਈ = ਖਿੜਕੀ->floating.h;
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->requested.logical_ਚੌੜਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਖਿੜਕੀ->floating.w);
        ਅੰਕੜੇ->requested.logical_ਉਚਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਖਿੜਕੀ->floating.h);
        ਅੰਕੜੇ->requested.pixel_ਚੌੜਾਈ = ਖਿੜਕੀ->floating.w;
        ਅੰਕੜੇ->requested.pixel_ਉਚਾਈ = ਖਿੜਕੀ->floating.h;
    }

    ਜੇ (!external_surface) {
        ਅੰਕੜੇ->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_ਜੋੜੋ_listener(ਅੰਕੜੇ->surface, &surface_listener, ਅੰਕੜੇ);
        wl_surface_ਸੈੱਟ_user_ਅੰਕੜੇ(ਅੰਕੜੇ->surface, ਅੰਕੜੇ);
        SDL_WAYLAND_ਰਜਿਸਟਰ_surface(ਅੰਕੜੇ->surface);
    } ਨਹੀਂਤਾਂ {
        ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_EXTERNAL;
        ਅੰਕੜੇ->surface = external_surface;

        /* External surfaces are registered by being put in a list, as changing tags or userdata
         * can cause problems with external toolkits.
         */
        Wayland_ਜੋੜੋ_ਖਿੜਕੀ_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ_External_List(ਅੰਕੜੇ);
    }

    /* Always attach a viewport and fractional scale manager if available and the surface is not custom/external,
     * or the custom/external surface was explicitly flagged as high pixel density aware, which signals that the
     * application wants SDL to handle scaling.
     */
    ਜੇ (!custom_surface_role || (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਉੱਚਾ_PIXEL_DENSITY)) {
        ਜੇ (c->viewporter) {
            ਅੰਕੜੇ->viewport = wp_viewporter_get_viewport(c->viewporter, ਅੰਕੜੇ->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_ਸੈੱਟ_ਸਰੋਤ(ਅੰਕੜੇ->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        ਜੇ (c->fractional_scale_manager) {
            ਅੰਕੜੇ->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, ਅੰਕੜੇ->surface);
            wp_fractional_scale_v1_ਜੋੜੋ_listener(ਅੰਕੜੇ->fractional_scale, &fractional_scale_listener, ਅੰਕੜੇ);
        }
    }

    ਜੇ (!custom_surface_role) {
        ਜੇ (c->wp_color_manager_v1) {
            ਅੰਕੜੇ->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, ਅੰਕੜੇ->surface);
            wp_color_management_surface_feedback_v1_ਜੋੜੋ_listener(ਅੰਕੜੇ->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, ਅੰਕੜੇ);
            Wayland_Get_Color_Info_For_ਖਿੜਕੀ(ਅੰਕੜੇ, true);
        } ਨਹੀਂਤਾਂ ਜੇ (c->frog_color_management_factory_v1) {
            ਅੰਕੜੇ->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, ਅੰਕੜੇ->surface);
            frog_color_managed_surface_ਜੋੜੋ_listener(ਅੰਕੜੇ->frog_color_managed_surface, &frog_surface_listener, ਅੰਕੜੇ);
        }

        ਜੇ (c->wp_alpha_modifier_v1) {
            ਅੰਕੜੇ->wp_alpha_modifier_surface_v1 = wp_alpha_modifier_v1_get_surface(c->wp_alpha_modifier_v1, ਅੰਕੜੇ->surface);
            wp_alpha_modifier_surface_v1_ਸੈੱਟ_multiplier(ਅੰਕੜੇ->wp_alpha_modifier_surface_v1, SDL_MAX_UINT32);
        }
    }

    // Must be called before EGL configuration to set the drawable backbuffer size.
    Configure_ਖਿੜਕੀ_Geometry(ਖਿੜਕੀ);

    /* Fire a callback when the compositor wants a new frame rendered.
     * Right now this only matters for OpenGL; we use this callback to add a
     * wait timeout that avoids getting deadlocked by the compositor when the
     * window isn't visible.
     */
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ = WAYLAND_wl_display_create_ਕਤਾਰ(ਅੰਕੜੇ->wayland_ਅੰਕੜੇ->display);
        ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(ਅੰਕੜੇ->surface);
        WAYLAND_wl_proxy_ਸੈੱਟ_ਕਤਾਰ((ਬਣਤਰ wl_proxy *)ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper, ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ);
        ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback = wl_surface_ਚੌਖਟਾ(ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper);
        wl_callback_ਜੋੜੋ_listener(ਅੰਕੜੇ->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback, &gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_listener, ਅੰਕੜੇ);
    }

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT) {
        ਜੇ (_this->gl_config.alpha_ਮਾਪ == 0) {
            _this->gl_config.alpha_ਮਾਪ = 8;
        }
    }

    ਜੇ (create_egl_ਖਿੜਕੀ) {
        ਅੰਕੜੇ->egl_ਖਿੜਕੀ = WAYLAND_wl_egl_ਖਿੜਕੀ_create(ਅੰਕੜੇ->surface, ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ, ਅੰਕੜੇ->current.pixel_ਉਚਾਈ);
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL) {
        // Create the GLES window surface
        ਅੰਕੜੇ->egl_surface = SDL_EGL_CreateSurface(_this, ਖਿੜਕੀ, (Native_ਖਿੜਕੀ_Type)ਅੰਕੜੇ->egl_ਖਿੜਕੀ);

        ਜੇ (ਅੰਕੜੇ->egl_surface == EGL_NO_SURFACE) {
            ਵਾਪਸ false; // SDL_EGL_CreateSurface should have set error
        }
    }
#ਜੇ_ਅੰਤ

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    ਜੇ (!custom_surface_role) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
        ਜੇ (c->shell.libdecor && !SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
            ਅੰਕੜੇ->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
            ਜੇ (c->shell.xdg) {
            ਜੇ (SDL_ਖਿੜਕੀ_IS_POPUP(ਖਿੜਕੀ)) {
                ਅੰਕੜੇ->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP;
            } ਨਹੀਂਤਾਂ {
                ਅੰਕੜੇ->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL;
            }
        } // All other cases will be WAYLAND_SURFACE_UNKNOWN
    } ਨਹੀਂਤਾਂ {
        // Roleless and external surfaces are always considered to be in the shown state by the backend.
        ਅੰਕੜੇ->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_CUSTOM;
        ਅੰਕੜੇ->shell_surface_ਸਥਿਤੀ = WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN;

        // External windows are presumed to be shown.
        ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL) {
            ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_HIDDEN;
        }
    }

    ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_ਬਫਰ, false)) {
        ਅੰਕੜੇ->double_ਬਫਰ = true;
    }

    SDL_PropertiesID props = SDL_Get_ਖਿੜਕੀ_Properties(ਖਿੜਕੀ);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_DISPLAY_ਸੂਚਕ, ਅੰਕੜੇ->wayland_ਅੰਕੜੇ->display);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_SURFACE_ਸੂਚਕ, ਅੰਕੜੇ->surface);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_VIEWPORT_ਸੂਚਕ, ਅੰਕੜੇ->viewport);
    SDL_ਸੈੱਟ_ਸੂਚਕ_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_EGL_ਖਿੜਕੀ_ਸੂਚਕ, ਅੰਕੜੇ->egl_ਖਿੜਕੀ);
    ਜੇ (ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || ਅੰਕੜੇ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਅਚਲ ਅੱਖਰ *ਖਿੜਕੀ_id = SDL_GetStringProperty(create_props, SDL_PROP_ਖਿੜਕੀ_CREATE_WAYLAND_ਖਿੜਕੀ_ID_STRING, ਨਿਰਾ);
        ਜੇ (ਖਿੜਕੀ_id && *ਖਿੜਕੀ_id != '\0') {
            SDL_ਸੈੱਟ_String_Property(props, SDL_PROP_ਖਿੜਕੀ_WAYLAND_ਖਿੜਕੀ_ID_STRING, ਖਿੜਕੀ_id);
        }
    }

    ਅੰਕੜੇ->ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ = SDL_HITTEST_ਸਾਧਾਰਨ;

    ਵਾਪਸ true;
}

ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->limits_ਬਦਲਿਆ = true;
}

ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->limits_ਬਦਲਿਆ = true;
}

ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->limits_ਬਦਲਿਆ = true;
}

bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    // Only popup windows can be positioned relative to the parent.
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        ਜੇ (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_ਸੰਸਕਰਣ(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_ਸੰਸਕਰਣ) {
            ਵਾਪਸ SDL_Unsupported();
        }

        RepositionPopup(ਖਿੜਕੀ, false);
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(ਖਿੜਕੀ);

        ਜੇ (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_Get_Video_Display_For_Fullscreen_ਖਿੜਕੀ(ਖਿੜਕੀ);
            ਜੇ (display && wind->ਆਖਰੀ_display_ID != display->id) {
                ਬਣਤਰ wl_output *output = display->ਅੰਦਰੂਨੀ->output;
                ਸੈੱਟ_Fullscreen(ਖਿੜਕੀ, output, true);

                ਵਾਪਸ true;
            }
        }
    }
    ਵਾਪਸ SDL_ਸੈੱਟ_Error("wayland cannot position non-popup windows");
}

ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    /* Flush any pending state operations, as fullscreen windows do not get
     * explicitly resized, not strictly obeying the size of a maximized window
     * is a protocol violation, and pending restore events might result in a
     * configure event overwriting the requested size.
     *
     * Calling this on a custom surface is informative, so the size must
     * always be passed through.
     */
    FlushPendingEvents(ਖਿੜਕੀ);

    ਅਚਲ bool maximized = (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MAXIMIZED) != 0;
    ਅਚਲ bool resizable_state = !(ਖਿੜਕੀ->flags & (SDL_ਖਿੜਕੀ_MAXIMIZED | SDL_ਖਿੜਕੀ_FULLSCREEN));

    /* Maximized and fullscreen windows don't get resized, and the new size is ignored
     * if this is just to recalculate the min/max or aspect limits on a tiled window.
     *
     * Some compositors will mark tiled windows as maximized. In these cases, the content
     * size is recalculated, but window size itself is left alone, as the spec states that
     * the configure size of a maximized window must be obeyed.
     */
    ਜੇ (resizable_state || (ਖਿੜਕੀ->tiled && !wind->limits_ਬਦਲਿਆ) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        ਜੇ (!maximized) {
            ਜੇ (!wind->scale_ਮੰਜ਼ਿਲ_display) {
                wind->requested.logical_ਚੌੜਾਈ = ਖਿੜਕੀ->pending.w;
                wind->requested.logical_ਉਚਾਈ = ਖਿੜਕੀ->pending.h;
            } ਨਹੀਂਤਾਂ {
                wind->requested.logical_ਚੌੜਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਖਿੜਕੀ->pending.w);
                wind->requested.logical_ਉਚਾਈ = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, ਖਿੜਕੀ->pending.h);
                wind->requested.pixel_ਚੌੜਾਈ = ਖਿੜਕੀ->pending.w;
                wind->requested.pixel_ਉਚਾਈ = ਖਿੜਕੀ->pending.h;
            }
        }

        /* If a non-resizable window somehow wound up in the tiled state, store the new
         * size in the floating parameters so the size will be preserved for future
         * configure events.
         *
         * This shouldn't happen, but apparently it can on at least one compositor...
         */
        ਜੇ (ਖਿੜਕੀ->tiled && !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE)) {
            ਖਿੜਕੀ->floating.w = ਖਿੜਕੀ->pending.w;
            ਖਿੜਕੀ->floating.h = ਖਿੜਕੀ->pending.h;
        }
    } ਨਹੀਂਤਾਂ {
        // Can't resize the window.
        ਖਿੜਕੀ->ਆਖਰੀ_ਮਾਪ_pending = false;
    }

    wind->limits_ਬਦਲਿਆ = false;
    ਜੇ (wind->shell_surface_ਸਥਿਤੀ == WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    Configure_ਖਿੜਕੀ_Geometry(ਖਿੜਕੀ);
    Commit_Libdecor_ਚੌਖਟਾ(ਖਿੜਕੀ);
}

ਖਾਲੀ Wayland_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *w, ਪੂਰਨ *h)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    *w = ਅੰਕੜੇ->current.pixel_ਚੌੜਾਈ;
    *h = ਅੰਕੜੇ->current.pixel_ਉਚਾਈ;
}

ਦਸ਼ਮਲਵ Wayland_Get_ਖਿੜਕੀ_Content_Scale(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਉੱਚਾ_PIXEL_DENSITY || wind->scale_ਮੰਜ਼ਿਲ_display || wind->fullscreen_exclusive) {
        ਵਾਪਸ (ਦਸ਼ਮਲਵ)wind->scale_ਗੁਣਕ_2;
    }

    ਵਾਪਸ 1.0f;
}

SDL_DisplayID Wayland_Get_Display_For_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (wind) {
        ਵਾਪਸ wind->ਆਖਰੀ_display_ID;
    }

    ਵਾਪਸ 0;
}

bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Opacity(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ opacity)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (wind->wp_alpha_modifier_surface_v1) {
        ਅਚਲ bool is_opaque = !(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_TRANSPARENT) && opacity == 1.0f;

        ਜੇ (wind->ਨਕਾਬ.mapped && wind->ਨਕਾਬ.opaque != is_opaque) {
            ਬਣਤਰ wl_ਬਫਰ *old_ਬਫਰ = wind->ਨਕਾਬ.ਬਫਰ_2;
            wind->ਨਕਾਬ.opaque = is_opaque;
            wind->ਨਕਾਬ.ਬਫਰ_2 = Wayland_Create_Single_Pixel_ਬਫਰ(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->ਨਕਾਬ.surface, wind->ਨਕਾਬ.ਬਫਰ_2, 0, 0);
            ਜੇ (wl_surface_get_ਸੰਸਕਰਣ(wind->ਨਕਾਬ.surface) >= WL_SURFACE_DAMAGE_ਬਫਰ_SINCE_ਸੰਸਕਰਣ) {
                wl_surface_damage_ਬਫਰ(wind->ਨਕਾਬ.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } ਨਹੀਂਤਾਂ {
                wl_surface_damage(wind->ਨਕਾਬ.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            ਜੇ (is_opaque) {
                ਸੈੱਟ_Surface_Opaque_Region(wind->ਨਕਾਬ.surface, wind->current.logical_ਚੌੜਾਈ, wind->current.logical_ਉਚਾਈ);
            } ਨਹੀਂਤਾਂ {
                ਸੈੱਟ_Surface_Opaque_Region(wind->ਨਕਾਬ.surface, 0, 0);
            }

            wl_surface_commit(wind->ਨਕਾਬ.surface);

            ਜੇ (old_ਬਫਰ) {
                wl_ਬਫਰ_destroy(old_ਬਫਰ);
            }
        }

        ਜੇ (is_opaque) {
            ਸੈੱਟ_Surface_Opaque_Region(wind->surface, wind->current.viewport_ਚੌੜਾਈ, wind->current.viewport_ਉਚਾਈ);
        } ਨਹੀਂਤਾਂ {
            ਸੈੱਟ_Surface_Opaque_Region(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_ਸੈੱਟ_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((ਦੁੱਗਣਾ)SDL_MAX_UINT32 * (ਦੁੱਗਣਾ)opacity));

        ਵਾਪਸ true;
    }

    ਵਾਪਸ SDL_ਸੈੱਟ_Error("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਅਚਲ ਅੱਖਰ *title = ਖਿੜਕੀ->title ? ਖਿੜਕੀ->title : "";

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.ਚੌਖਟਾ) {
        libdecor_ਚੌਖਟਾ_ਸੈੱਟ_title(wind->shell_surface.libdecor.ਚੌਖਟਾ, title);
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_ਸੈੱਟ_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

ਸਥਿਰ ਪੂਰਨ icon_ਛਾਂਟੋ_callback(ਅਚਲ ਖਾਲੀ *a, ਅਚਲ ਖਾਲੀ *b)
{
    ਅਚਲ SDL_Surface *s1 = *(ਅਚਲ SDL_Surface **)a;
    ਅਚਲ SDL_Surface *s2 = *(ਅਚਲ SDL_Surface **)b;

    ਵਾਪਸ (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Icon(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *icon)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Wayland_SHMPool *shm_pool = ਨਿਰਾ;
    ਬਣਤਰ xdg_toplevel *toplevel = ਨਿਰਾ;

    ਜੇ (!_this->ਅੰਦਰੂਨੀ->xdg_toplevel_icon_manager_v1) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    ਪੂਰਨ image_ਗਿਣਤੀ_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_ਗਿਣਤੀ_2);
    ਜੇ (!images || !image_ਗਿਣਤੀ_2) {
        ਵਾਪਸ false;
    }

    // Release the old icon resources.
    ਜੇ (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = ਨਿਰਾ;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < wind->icon_ਬਫਰ_ਗਿਣਤੀ; ++i) {
        wl_ਬਫਰ_destroy(wind->icon_buffers[i]);
    }
    wind->icon_ਬਫਰ_ਗਿਣਤੀ = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->ਅੰਦਰੂਨੀ->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_ਗਿਣਤੀ_2 * ਆਕਾਰ(ਬਣਤਰ wl_ਬਫਰ *));
    ਜੇ (!wind->icon_buffers) {
        ਜਾਓ failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    size_t pool_ਮਾਪ = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < image_ਗਿਣਤੀ_2; ++i) {
        // Images must be square. Non-square images will be centered.
        ਅਚਲ ਪੂਰਨ ਮਾਪ = SDL_max(images[i]->w, images[i]->h);
        pool_ਮਾਪ += ਮਾਪ * ਮਾਪ * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_ਗਿਣਤੀ_2, ਆਕਾਰ(SDL_Surface *), icon_ਛਾਂਟੋ_callback);

    shm_pool = Wayland_AllocSHMPool(pool_ਮਾਪ);
    ਜੇ (!shm_pool) {
        SDL_ਸੈੱਟ_Error("wayland: failed to allocate an SHM pool for the icon");
        ਜਾਓ failure_cleanup;
    }

    ਅਚਲ ਦੁੱਗਣਾ ਅਧਾਰ_ਮਾਪ = (ਦੁੱਗਣਾ)SDL_max(icon->w, icon->h);
    ਲਈ (ਪੂਰਨ i = 0; i < image_ਗਿਣਤੀ_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        ਅਚਲ ਪੂਰਨ level_ਮਾਪ = SDL_max(surface->w, surface->h);
        ਅਚਲ ਪੂਰਨ scale = (ਪੂਰਨ)SDL_floor((ਦੁੱਗਣਾ)level_ਮਾਪ / ਅਧਾਰ_ਮਾਪ);
        ਜੇ (!scale) {
            ਜਾਰੀ;
        }

        ਜੇ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            ਜੇ (!surface) {
                SDL_ਸੈੱਟ_Error("wayland: failed to convert the icon image to ARGB8888 format");
                ਜਾਓ failure_cleanup;
            }
        }

        ਖਾਲੀ *ਬਫਰ_mem;
        ਬਣਤਰ wl_ਬਫਰ *ਬਫਰ_2 = Wayland_Alloc_ਬਫਰ_From_Pool(shm_pool, level_ਮਾਪ, level_ਮਾਪ, &ਬਫਰ_mem);
        ਜੇ (!ਬਫਰ_2) {
            // Clean up the temporary conversion surface.
            ਜੇ (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_ਸੈੱਟ_Error("wayland: failed to allocate a wl_buffer for the icon");
            ਜਾਓ failure_cleanup;
        }

        wind->icon_buffers[wind->icon_ਬਫਰ_ਗਿਣਤੀ++] = ਬਫਰ_2;

        // Center non-square images.
        ਜੇ (surface->w < level_ਮਾਪ) {
            SDL_memset(ਬਫਰ_mem, 0, level_ਮਾਪ * level_ਮਾਪ * 4);
            ਬਫਰ_mem = (Uint8 *)ਬਫਰ_mem + (((level_ਮਾਪ - surface->w) / 2) * 4);
        } ਨਹੀਂਤਾਂ ਜੇ (surface->h < level_ਮਾਪ) {
            SDL_memset(ਬਫਰ_mem, 0, level_ਮਾਪ * level_ਮਾਪ * 4);
            ਬਫਰ_mem = (Uint8 *)ਬਫਰ_mem + (((level_ਮਾਪ - surface->h) / 2) * (level_ਮਾਪ * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, ਬਫਰ_mem, level_ਮਾਪ * 4, true);

        xdg_toplevel_icon_v1_ਜੋੜੋ_ਬਫਰ(wind->xdg_toplevel_icon_v1, ਬਫਰ_2, scale);

        // Clean up the temporary scaled or conversion surface.
        ਜੇ (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.ਚੌਖਟਾ) {
        toplevel = libdecor_ਚੌਖਟਾ_get_xdg_toplevel(wind->shell_surface.libdecor.ਚੌਖਟਾ);
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    ਜੇ (toplevel) {
        xdg_toplevel_icon_manager_v1_ਸੈੱਟ_icon(_this->ਅੰਦਰੂਨੀ->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
    }

    Wayland_ReleaseSHMPool(shm_pool);
    SDL_free(images);

    ਵਾਪਸ true;

failure_cleanup:

    SDL_free(images);

    ਜੇ (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = ਨਿਰਾ;
    }

    Wayland_ReleaseSHMPool(shm_pool);

    ਲਈ (ਪੂਰਨ i = 0; i < wind->icon_ਬਫਰ_ਗਿਣਤੀ; ++i) {
        wl_ਬਫਰ_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = ਨਿਰਾ;
    wind->icon_ਬਫਰ_ਗਿਣਤੀ = 0;

    ਵਾਪਸ false;
}

ਖਾਲੀ *Wayland_Get_ਖਿੜਕੀ_ICCProfile(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, size_t *ਮਾਪ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    ਖਾਲੀ *ret = ਨਿਰਾ;

    ਜੇ (wind->icc_ਮਾਪ > 0) {
        ਖਾਲੀ *icc_map = mmap(ਨਿਰਾ, wind->icc_ਮਾਪ, PROT_READ, MAP_PRIVATE, wind->icc_fd, 0);
        ਜੇ (icc_map != MAP_FAILED) {
            ret = SDL_malloc(wind->icc_ਮਾਪ);
            ਜੇ (ret) {
                *ਮਾਪ = wind->icc_ਮਾਪ;
                SDL_memcpy(ret, icc_map, *ਮਾਪ);
            }
            munmap(icc_map, wind->icc_ਮਾਪ);
        }
    }

    ਵਾਪਸ ret;
}

bool Wayland_Sync_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਕਰੋ {
        WAYLAND_wl_display_roundtrip(_this->ਅੰਦਰੂਨੀ->display);
    } ਜਦੋਂ (wind->pending_state_deadline_ਗਿਣਤੀ);

    ਵਾਪਸ true;
}

ਖਾਲੀ Wayland_AcceptDragAndDrop(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool accept)
{
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->ਮੰਨਦਾ_drag_and_drop = accept;
}

bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Focusable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool focusable)
{
    ਜੇ (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_POPUP_MENU) {
        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN)) {
            ਜੇ (!focusable && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਨਿਵੇਸ਼_FOCUS)) {
                SDL_ਖਿੜਕੀ *new_focus;
                ਅਚਲ bool ਸੈੱਟ_focus = SDL_ShouldRelinquishPopupFocus(ਖਿੜਕੀ, &new_focus);
                Wayland_ਸੈੱਟ_Keyboard_Focus(new_focus, ਸੈੱਟ_focus);
            } ਨਹੀਂਤਾਂ ਜੇ (focusable) {
                ਜੇ (SDL_ShouldFocusPopup(ਖਿੜਕੀ)) {
                    Wayland_ਸੈੱਟ_Keyboard_Focus(ਖਿੜਕੀ, true);
                }
            }
        }

        ਵਾਪਸ true;
    }

    ਵਾਪਸ SDL_ਸੈੱਟ_Error("wayland: focus can only be toggled on popup menu windows");
}

ਖਾਲੀ Wayland_Show_ਖਿੜਕੀ_System_Menu(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ x, ਪੂਰਨ y)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    SDL_WaylandSeat *seat = wind->wayland_ਅੰਕੜੇ->ਆਖਰੀ_implicit_grab_seat;

    ਜੇ (!seat) {
        ਵਾਪਸ;
    }

    ਜੇ (wind->scale_ਮੰਜ਼ਿਲ_display) {
        x = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, x);
        y = Pixel_ਮੰਜ਼ਿਲ_ਬਿੰਦੂ(ਖਿੜਕੀ, y);
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ਜੇ (wind->shell_surface.libdecor.ਚੌਖਟਾ) {
            libdecor_ਚੌਖਟਾ_show_ਖਿੜਕੀ_menu(wind->shell_surface.libdecor.ਚੌਖਟਾ, seat->wl_seat, seat->ਆਖਰੀ_implicit_grab_serial, x, y);
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    ਜੇ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ਜੇ (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_ਖਿੜਕੀ_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->ਆਖਰੀ_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    ਜੇ (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        ਵਾਪਸ true;
    }
#ਜੇ_ਅੰਤ

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    ਜੇ (ਅੰਕੜੇ->idle_inhibit_manager) {
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = _this->windows;
        ਜਦੋਂ (ਖਿੜਕੀ) {
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *win_ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

            ਜੇ (_this->suspend_screensaver && !win_ਅੰਕੜੇ->idle_inhibitor) {
                win_ਅੰਕੜੇ->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(ਅੰਕੜੇ->idle_inhibit_manager,
                                                                 win_ਅੰਕੜੇ->surface);
            } ਨਹੀਂਤਾਂ ਜੇ (!_this->suspend_screensaver && win_ਅੰਕੜੇ->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_ਅੰਕੜੇ->idle_inhibitor);
                win_ਅੰਕੜੇ->idle_inhibitor = ਨਿਰਾ;
            }

            ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ;
        }
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ Wayland_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wind = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        ਜੇ (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            ਖਿੜਕੀ->ਪ੍ਰਾਪਤੀ_test = ਨਿਰਾ;
            WAYLAND_wl_display_roundtrip(ਅੰਕੜੇ->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_Display_Remove_ਖਿੜਕੀ_References_From_Seats(ਅੰਕੜੇ, wind);

        ਜੇ (wind->ਨਕਾਬ.viewport) {
            wp_viewport_destroy(wind->ਨਕਾਬ.viewport);
        }
        ਜੇ (wind->ਨਕਾਬ.ਬਫਰ_2) {
            wl_ਬਫਰ_destroy(wind->ਨਕਾਬ.ਬਫਰ_2);
        }
        ਜੇ (wind->ਨਕਾਬ.subsurface) {
            wl_subsurface_destroy(wind->ਨਕਾਬ.subsurface);
        }
        ਜੇ (wind->ਨਕਾਬ.surface) {
            wl_surface_destroy(wind->ਨਕਾਬ.surface);
        }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
        ਜੇ (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#ਜੇ_ਅੰਤ
        ਜੇ (wind->egl_ਖਿੜਕੀ) {
            WAYLAND_wl_egl_ਖਿੜਕੀ_destroy(wind->egl_ਖਿੜਕੀ);
        }

        ਜੇ (wind->idle_inhibitor) {
            zwp_idle_inhibitor_v1_destroy(wind->idle_inhibitor);
        }

        ਜੇ (wind->activation_token) {
            xdg_activation_token_v1_destroy(wind->activation_token);
        }

        ਜੇ (wind->viewport) {
            wp_viewport_destroy(wind->viewport);
        }

        ਜੇ (wind->fractional_scale) {
            wp_fractional_scale_v1_destroy(wind->fractional_scale);
        }

        ਜੇ (wind->wp_alpha_modifier_surface_v1) {
            wp_alpha_modifier_surface_v1_destroy(wind->wp_alpha_modifier_surface_v1);
        }

        ਜੇ (wind->frog_color_managed_surface) {
            frog_color_managed_surface_destroy(wind->frog_color_managed_surface);
        }

        ਜੇ (wind->wp_color_management_surface_feedback) {
            Wayland_FreeColorInfoState(wind->color_info_state);
            wp_color_management_surface_feedback_v1_destroy(wind->wp_color_management_surface_feedback);
        }

        SDL_free(wind->outputs);
        SDL_free(wind->app_id);

        ਜੇ (wind->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback) {
            wl_callback_destroy(wind->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback);
            WAYLAND_wl_proxy_wrapper_destroy(wind->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper);
            WAYLAND_wl_event_ਕਤਾਰ_destroy(wind->gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ);
        }

        ਜੇ (!(ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } ਨਹੀਂਤਾਂ {
            Wayland_Remove_ਖਿੜਕੀ_ਅੰਕੜੇ_From_External_List(wind);
        }

        ਜੇ (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        ਲਈ (ਪੂਰਨ i = 0; i < wind->icon_ਬਫਰ_ਗਿਣਤੀ; ++i) {
            wl_ਬਫਰ_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_ਬਫਰ_ਗਿਣਤੀ = 0;

        SDL_free(wind);
    }
    ਖਿੜਕੀ->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND
