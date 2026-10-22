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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ <sys/mman.h>

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_appid.h"
#ಅನ್ತರ್ಭಾವ "../../notification/SDL_notification_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandevents_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandmouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandwindow.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "../../SDL_hints_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandcolor.h"

#ಅನ್ತರ್ಭಾವ "alpha-modifier-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-shell-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-decoration-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "idle-inhibit-unstable-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-activation-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "viewporter-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "fractional-scale-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-foreign-unstable-v2-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-dialog-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "frog-color-management-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-toplevel-icon-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "color-management-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-session-management-v1-client-protocol.h"
#ಅನ್ತರ್ಭಾವ "xdg-toplevel-tag-v1-client-protocol.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
#ಅನ್ತರ್ಭಾವ <libdecor.h>
#ಆದರೆ_ಅಂತ್ಯ

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
ಸ್ಥಿರ bool Should_ಮುಖವಾಡ_Fullscreen()
{
    ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ_required = -1;

    ಆದರೆ (ಮುಖವಾಡ_required >= 0) {
        ಹಿಂತಿರುಗಿ ಮುಖವಾಡ_required != 0;
    }

    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *desktop = SDL_getenv("XDG_CURRENT_DESKTOP");
    ಆದರೆ (desktop && SDL_strstr(desktop, "KDE") != ಖಾಲಿ) {
        ಮುಖವಾಡ_required = 1;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಮುಖವಾಡ_required = 0;
    }

    ಹಿಂತಿರುಗಿ ಮುಖವಾಡ_required != 0;
}

ಸ್ಥಿರ ದ್ವಿಗುಣ Get_ಕಿಟಕಿ_Scale(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಮೇಲಿನ_PIXEL_DENSITY) || ಕಿಟಕಿ->ಆಂತರಿಕ->scale_ಗಮ್ಯ_display ? ಕಿಟಕಿ->ಆಂತರಿಕ->scale_ಗುಣಕ_2 : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಬಿಂದು_ಗಮ್ಯ_Pixel(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ ಬಿಂದು)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    ಹಿಂತಿರುಗಿ ಬಿಂದು ? SDL_max((ಪೂರ್ಣಾಂಕ)SDL_lround((ದ್ವಿಗುಣ)ಬಿಂದು * Get_ಕಿಟಕಿ_Scale(ಕಿಟಕಿ) + 1e-6), 1) : 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Pixel_ಗಮ್ಯ_ಬಿಂದು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ pixel)
{
    ಹಿಂತಿರುಗಿ pixel ? SDL_max((ಪೂರ್ಣಾಂಕ)SDL_lround((ದ್ವಿಗುಣ)pixel / Get_ಕಿಟಕಿ_Scale(ಕಿಟಕಿ)), 1) : 0;
}

ಎಣಿಕೆ Wayland_ಬಹುಲಕ_Scale
{
    WAYLAND_ಬಹುಲಕ_SCALE_UNDEFINED,
    WAYLAND_ಬಹುಲಕ_SCALE_ASPECT,
    WAYLAND_ಬಹುಲಕ_SCALE_STRETCH,
    WAYLAND_ಬಹುಲಕ_SCALE_NONE
};

ಸ್ಥಿರ ಎಣಿಕೆ Wayland_ಬಹುಲಕ_Scale Get_ಬಹುಲಕ_Scale_ವಿಧಾನ(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ ಎಣಿಕೆ Wayland_ಬಹುಲಕ_Scale scale_ಬಹುಲಕ_2 = WAYLAND_ಬಹುಲಕ_SCALE_UNDEFINED;

    ಆದರೆ (scale_ಬಹುಲಕ_2 == WAYLAND_ಬಹುಲಕ_SCALE_UNDEFINED) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_ಬಹುಲಕ_SCALING);

        ಆದರೆ (scale_hint) {
            ಆದರೆ (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_ಬಹುಲಕ_2 = WAYLAND_ಬಹುಲಕ_SCALE_STRETCH;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!SDL_strcasecmp(scale_hint, "none")) {
                scale_ಬಹುಲಕ_2 = WAYLAND_ಬಹುಲಕ_SCALE_NONE;
            } ಇಲ್ಲದಿದ್ದರೆ {
                scale_ಬಹುಲಕ_2 = WAYLAND_ಬಹುಲಕ_SCALE_ASPECT;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            scale_ಬಹುಲಕ_2 = WAYLAND_ಬಹುಲಕ_SCALE_ASPECT;
        }
    }

    ಹಿಂತಿರುಗಿ scale_ಬಹುಲಕ_2;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ BorderInsets
{
    ಪೂರ್ಣಾಂಕ ಎಡ;
    ಪೂರ್ಣಾಂಕ ತುದಿ;
    ಪೂರ್ಣಾಂಕ ಬಲ;
    ಪೂರ್ಣಾಂಕ bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
ಸ್ಥಿರ ಶೂನ್ಯ GetBorderInsets(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, BorderInsets *insets)
{
    SDL_zerop(insets);
    ಆದರೆ (!ಕಿಟಕಿ->ಆಂತರಿಕ->enable_insets) {
        ಹಿಂತಿರುಗಿ;
    }
    ಆದರೆ (ಕಿಟಕಿ->ಆಂತರಿಕ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ಸ್ಥಿರಾಂಕ SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
        insets->ಎಡ = (ಪೂರ್ಣಾಂಕ)SDL_clamp(SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_BORDER_INSET_ಎಡ_ಸಂಖ್ಯೆ, 0), 0, SDL_MAX_SINT16);
        insets->ತುದಿ = (ಪೂರ್ಣಾಂಕ)SDL_clamp(SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_BORDER_INSET_ತುದಿ_ಸಂಖ್ಯೆ, 0), 0, SDL_MAX_SINT16);
        insets->ಬಲ = (ಪೂರ್ಣಾಂಕ)SDL_clamp(SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_BORDER_INSET_ಬಲ_ಸಂಖ್ಯೆ, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (ಪೂರ್ಣಾಂಕ)SDL_clamp(SDL_Get_ಸಂಖ್ಯೆ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_BORDER_INSET_BOTTOM_ಸಂಖ್ಯೆ, 0), 0, SDL_MAX_SINT16);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಗಣ_Min_Max_Dimensions(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ min_ಅಗಲ_2, min_ಎತ್ತರ_2, max_ಅಗಲ_2, max_ಎತ್ತರ_2;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    ಆದರೆ (ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_FULLSCREEN | SDL_ಕಿಟಕಿ_MAXIMIZED)) {
        min_ಅಗಲ_2 = 0;
        min_ಎತ್ತರ_2 = 0;
        max_ಅಗಲ_2 = 0;
        max_ಎತ್ತರ_2 = 0;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE) {
        ಪೂರ್ಣಾಂಕ adj_w = SDL_max(ಕಿಟಕಿ->min_w, wind->system_limits.min_ಅಗಲ_2);
        ಪೂರ್ಣಾಂಕ adj_h = SDL_max(ಕಿಟಕಿ->min_h, wind->system_limits.min_ಎತ್ತರ_2);
        ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
            adj_w = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, adj_w);
            adj_h = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, adj_h);
        }
        min_ಅಗಲ_2 = adj_w;
        min_ಎತ್ತರ_2 = adj_h;

        adj_w = ಕಿಟಕಿ->max_w ? SDL_max(ಕಿಟಕಿ->max_w, wind->system_limits.min_ಅಗಲ_2) : 0;
        adj_h = ಕಿಟಕಿ->max_h ? SDL_max(ಕಿಟಕಿ->max_h, wind->system_limits.min_ಎತ್ತರ_2) : 0;
        ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
            adj_w = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, adj_w);
            adj_h = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, adj_h);
        }
        max_ಅಗಲ_2 = adj_w;
        max_ಎತ್ತರ_2 = adj_h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        min_ಅಗಲ_2 = wind->current.logical_ಅಗಲ;
        min_ಎತ್ತರ_2 = wind->current.logical_ಎತ್ತರ;
        max_ಅಗಲ_2 = wind->current.logical_ಅಗಲ;
        max_ಎತ್ತರ_2 = wind->current.logical_ಎತ್ತರ;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ಆದರೆ (!wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
            ಹಿಂತಿರುಗಿ; // Can't do anything yet, wait for ShowWindow
        }

        ಆದರೆ (min_ಅಗಲ_2 && min_ಎತ್ತರ_2 && min_ಅಗಲ_2 == max_ಅಗಲ_2 && min_ಎತ್ತರ_2 == max_ಎತ್ತರ_2) {
            libdecor_ಚೌಕಟ್ಟು_unset_capabilities(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು, LIBDECOR_ACTION_RESIZE);
        } ಇಲ್ಲದಿದ್ದರೆ {
            libdecor_ಚೌಕಟ್ಟು_ಗಣ_capabilities(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        ಆದರೆ (libdecor_ಚೌಕಟ್ಟು_has_capability(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು, LIBDECOR_ACTION_RESIZE)) {
            libdecor_ಚೌಕಟ್ಟು_ಗಣ_min_content_ಗಾತ್ರ(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು,
                                                min_ಅಗಲ_2,
                                                min_ಎತ್ತರ_2);
            libdecor_ಚೌಕಟ್ಟು_ಗಣ_max_content_ಗಾತ್ರ(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು,
                                                max_ಅಗಲ_2,
                                                max_ಎತ್ತರ_2);
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ಆದರೆ (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            ಹಿಂತಿರುಗಿ; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(ಕಿಟಕಿ, &insets);
        min_ಅಗಲ_2 = SDL_max(min_ಅಗಲ_2 - (insets.ಎಡ + insets.ಬಲ), min_ಅಗಲ_2 ? 1 : 0);
        min_ಎತ್ತರ_2 = SDL_max(min_ಎತ್ತರ_2 - (insets.ತುದಿ + insets.bottom), min_ಎತ್ತರ_2 ? 1 : 0);
        ಆದರೆ (max_ಅಗಲ_2) {
            max_ಅಗಲ_2 = SDL_max(max_ಅಗಲ_2 - (insets.ಎಡ + insets.ಬಲ), 1);
        }
        ಆದರೆ (max_ಎತ್ತರ_2) {
            max_ಎತ್ತರ_2 = SDL_max(max_ಎತ್ತರ_2 - (insets.ತುದಿ + insets.bottom), 1);
        }
        xdg_toplevel_ಗಣ_min_ಗಾತ್ರ(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_ಅಗಲ_2,
                                  min_ಎತ್ತರ_2);
        xdg_toplevel_ಗಣ_max_ಗಾತ್ರ(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_ಅಗಲ_2,
                                  max_ಎತ್ತರ_2);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ EnsurePopupPositionIsValid(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *x, ಪೂರ್ಣಾಂಕ *y)
{
    ಪೂರ್ಣಾಂಕ adj_ಎಣಿಕೆ = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    ಆದರೆ (*x + ಕಿಟಕಿ->w <= 0) {
        *x = -ಕಿಟಕಿ->w;
        ++adj_ಎಣಿಕೆ;
    }
    ಆದರೆ (*y + ಕಿಟಕಿ->h <= 0) {
        *y = -ಕಿಟಕಿ->h;
        ++adj_ಎಣಿಕೆ;
    }
    ಆದರೆ (*x >= ಕಿಟಕಿ->ಪೋಷಕ->w) {
        *x = ಕಿಟಕಿ->ಪೋಷಕ->w;
        ++adj_ಎಣಿಕೆ;
    }
    ಆದರೆ (*y >= ಕಿಟಕಿ->ಪೋಷಕ->h) {
        *y = ಕಿಟಕಿ->ಪೋಷಕ->h;
        ++adj_ಎಣಿಕೆ;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    ಆದರೆ (adj_ಎಣಿಕೆ > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
ಸ್ಥಿರ ಶೂನ್ಯ Get_ಕಿಟಕಿ_Geometry(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    ಆದರೆ (SDL_Rect_ಖಾಲಿಗಳು(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_ಅಗಲ;
        geometry->h = wind->current.logical_ಎತ್ತರ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Adjust_Popup_ಸ್ಥಾನಾಂತರ(SDL_ಕಿಟಕಿ *popup, ಪೂರ್ಣಾಂಕ *x, ಪೂರ್ಣಾಂಕ *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (popup->ಪೋಷಕ->ಆಂತರಿಕ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ಪೂರ್ಣಾಂಕ adj_x, adj_y;
        libdecor_ಚೌಕಟ್ಟು_translate_coordinate(popup->ಪೋಷಕ->ಆಂತರಿಕ->shell_surface.libdecor.ಚೌಕಟ್ಟು,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        *x -= popup->ಪೋಷಕ->ಆಂತರಿಕ->explicit_geometry.x;
        *y -= popup->ಪೋಷಕ->ಆಂತರಿಕ->explicit_geometry.y;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ RepositionPopup(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool use_current_position)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_ಆವೃತ್ತಿ(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_ಆವೃತ್ತಿ) {
        ಪೂರ್ಣಾಂಕ x = use_current_position ? ಕಿಟಕಿ->x : ಕಿಟಕಿ->pending.x;
        ಪೂರ್ಣಾಂಕ y = use_current_position ? ಕಿಟಕಿ->y : ಕಿಟಕಿ->pending.y;

        EnsurePopupPositionIsValid(ಕಿಟಕಿ, &x, &y);
        ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
            x = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ->ಪೋಷಕ, x);
            y = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ->ಪೋಷಕ, y);
        }
        Adjust_Popup_ಸ್ಥಾನಾಂತರ(ಕಿಟಕಿ, &x, &y);
        SDL_Rect ಪೋಷಕ_geometry;
        Get_ಕಿಟಕಿ_Geometry(ಕಿಟಕಿ->ಪೋಷಕ->ಆಂತರಿಕ, &ಪೋಷಕ_geometry);
        xdg_positioner_ಗಣ_anchor_rect(wind->shell_surface.xdg.popup.xdg_positioner, 0, 0, ಪೋಷಕ_geometry.w, ಪೋಷಕ_geometry.h);
        xdg_positioner_ಗಣ_ಗಾತ್ರ(wind->shell_surface.xdg.popup.xdg_positioner, wind->current.logical_ಅಗಲ, wind->current.logical_ಎತ್ತರ);
        xdg_positioner_ಗಣ_ಸ್ಥಾನಾಂತರ(wind->shell_surface.xdg.popup.xdg_positioner, x, y);
        xdg_popup_reposition(wind->shell_surface.xdg.popup.xdg_popup,
                             wind->shell_surface.xdg.popup.xdg_positioner,
                             0);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಗಣ_Surface_Opaque_Region(ರಚನೆ wl_surface *surface, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = SDL_GetVideoDevice()->ಆಂತರಿಕ;

    ಆದರೆ (ಅಗಲ && ಎತ್ತರ) {
        ರಚನೆ wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_ಕೂಡಿಸು(region, 0, 0, ಅಗಲ, ಎತ್ತರ);
        wl_surface_ಗಣ_opaque_region(surface, region);
        wl_region_destroy(region);
    } ಇಲ್ಲದಿದ್ದರೆ {
        wl_surface_ಗಣ_opaque_region(surface, ಖಾಲಿ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Configure_ಕಿಟಕಿ_Geometry(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ scale_ಗುಣಕ_2 = Get_ಕಿಟಕಿ_Scale(ಕಿಟಕಿ);
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ prev_ಸೂಚಕ_scale_x = ದತ್ತಾಂಶ->ಸೂಚಕ_scale.x;
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ prev_ಸೂಚಕ_scale_y = ದತ್ತಾಂಶ->ಸೂಚಕ_scale.y;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ old_pixel_ಅಗಲ = ದತ್ತಾಂಶ->current.pixel_ಅಗಲ;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ old_pixel_ಎತ್ತರ = ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಅಗಲ = 0;
    ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಎತ್ತರ = 0;
    ಪೂರ್ಣಾಂಕ viewport_ಅಗಲ, viewport_ಎತ್ತರ;
    bool ಕಿಟಕಿ_ಗಾತ್ರ_ಬದಲಾಯಿತು;
    bool ಬಫರ್_ಗಾತ್ರ_ಬದಲಾಯಿತು;
    ಸ್ಥಿರಾಂಕ bool is_opaque = !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT) && ಕಿಟಕಿ->opacity == 1.0f;

    ಆದರೆ (ದತ್ತಾಂಶ->is_fullscreen && ಕಿಟಕಿ->fullscreen_exclusive) {
        ಕಿಟಕಿ_ಅಗಲ = ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.w;
        ಕಿಟಕಿ_ಎತ್ತರ = ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.h;

        viewport_ಅಗಲ = ದತ್ತಾಂಶ->requested.logical_ಅಗಲ;
        viewport_ಎತ್ತರ = ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ;

        ಆಯ್ಕೆ (Get_ಬಹುಲಕ_Scale_ವಿಧಾನ()) {
        ಸ್ಥಿತಿ WAYLAND_ಬಹುಲಕ_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            ಆದರೆ (ಕಿಟಕಿ_ಅಗಲ <= viewport_ಅಗಲ && ಕಿಟಕಿ_ಎತ್ತರ <= viewport_ಎತ್ತರ) {
                viewport_ಅಗಲ = ಕಿಟಕಿ_ಅಗಲ;
                viewport_ಎತ್ತರ = ಕಿಟಕಿ_ಎತ್ತರ;

                ನಿಲ್ಲಿಸು;
            }
            SDL_FALLTHROUGH;
        ಸ್ಥಿತಿ WAYLAND_ಬಹುಲಕ_SCALE_ASPECT:
        {
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ output_ಅನುಪಾತ = (ದಶಮಾಂಶ)viewport_ಅಗಲ / (ದಶಮಾಂಶ)viewport_ಎತ್ತರ;
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ ಬಹುಲಕ_ಅನುಪಾತ = (ದಶಮಾಂಶ)ಕಿಟಕಿ_ಅಗಲ / (ದಶಮಾಂಶ)ಕಿಟಕಿ_ಎತ್ತರ;

            ಆದರೆ (output_ಅನುಪಾತ > ಬಹುಲಕ_ಅನುಪಾತ) {
                viewport_ಅಗಲ = SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ_ಅಗಲ * ((ದಶಮಾಂಶ)viewport_ಎತ್ತರ / (ದಶಮಾಂಶ)ಕಿಟಕಿ_ಎತ್ತರ));
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (output_ಅನುಪಾತ < ಬಹುಲಕ_ಅನುಪಾತ) {
                viewport_ಎತ್ತರ = SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ_ಎತ್ತರ * ((ದಶಮಾಂಶ)viewport_ಅಗಲ / (ದಶಮಾಂಶ)ಕಿಟಕಿ_ಅಗಲ));
            }
        } ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }

        ಕಿಟಕಿ_ಗಾತ್ರ_ಬದಲಾಯಿತು = ಕಿಟಕಿ_ಅಗಲ != ಕಿಟಕಿ->w ||
                              ಕಿಟಕಿ_ಎತ್ತರ != ಕಿಟಕಿ->h ||
                              ದತ್ತಾಂಶ->current.viewport_ಅಗಲ != viewport_ಅಗಲ ||
                              ದತ್ತಾಂಶ->current.viewport_ಎತ್ತರ != viewport_ಎತ್ತರ;

        // Exclusive fullscreen window sizes are always in pixel units.
        ದತ್ತಾಂಶ->current.pixel_ಅಗಲ = ಕಿಟಕಿ_ಅಗಲ;
        ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ = ಕಿಟಕಿ_ಎತ್ತರ;
        ಬಫರ್_ಗಾತ್ರ_ಬದಲಾಯಿತು = ದತ್ತಾಂಶ->current.pixel_ಅಗಲ != old_pixel_ಅಗಲ ||
                              ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ != old_pixel_ಎತ್ತರ;

        ಆದರೆ (ಕಿಟಕಿ_ಗಾತ್ರ_ಬದಲಾಯಿತು || ಬಫರ್_ಗಾತ್ರ_ಬದಲಾಯಿತು) {
            ಆದರೆ (ದತ್ತಾಂಶ->viewport) {
                wp_viewport_ಗಣ_destination(ದತ್ತಾಂಶ->viewport, viewport_ಅಗಲ, viewport_ಎತ್ತರ);

                ದತ್ತಾಂಶ->current.logical_ಅಗಲ = ದತ್ತಾಂಶ->requested.logical_ಅಗಲ;
                ದತ್ತಾಂಶ->current.logical_ಎತ್ತರ = ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ;
                ದತ್ತಾಂಶ->current.viewport_ಅಗಲ = viewport_ಅಗಲ;
                ದತ್ತಾಂಶ->current.viewport_ಎತ್ತರ = viewport_ಎತ್ತರ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                // Calculate the integer scale from the mode and output.
                ಸ್ಥಿರಾಂಕ int32_t int_scale = SDL_max(ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.w / viewport_ಅಗಲ, 1);

                wl_surface_ಗಣ_ಬಫರ್_scale(ದತ್ತಾಂಶ->surface, int_scale);
                ದತ್ತಾಂಶ->current.logical_ಅಗಲ = ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.w;
                ದತ್ತಾಂಶ->current.logical_ಎತ್ತರ = ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.h;
            }

            ದತ್ತಾಂಶ->ಸೂಚಕ_scale.x = (ದ್ವಿಗುಣ)ಕಿಟಕಿ_ಅಗಲ / (ದ್ವಿಗುಣ)viewport_ಅಗಲ;
            ದತ್ತಾಂಶ->ಸೂಚಕ_scale.y = (ದ್ವಿಗುಣ)ಕಿಟಕಿ_ಎತ್ತರ / (ದ್ವಿಗುಣ)viewport_ಎತ್ತರ;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display) {
            viewport_ಅಗಲ = ದತ್ತಾಂಶ->requested.logical_ಅಗಲ;
            viewport_ಎತ್ತರ = ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            viewport_ಅಗಲ = ದತ್ತಾಂಶ->requested.pixel_ಅಗಲ;
            viewport_ಎತ್ತರ = ದತ್ತಾಂಶ->requested.pixel_ಎತ್ತರ;
        }

        ಆದರೆ (!ದತ್ತಾಂಶ->enable_insets &&
            ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ != WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_HIDDEN &&
            ದತ್ತಾಂಶ->viewport && ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ->subcompositor && !ದತ್ತಾಂಶ->floating && !ದತ್ತಾಂಶ->is_fullscreen) {
            ಪೂರ್ಣಾಂಕ min_ಅಗಲ_2, min_ಎತ್ತರ_2, max_ಅಗಲ_2, max_ಎತ್ತರ_2;
            ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE) {
                min_ಅಗಲ_2 = ಕಿಟಕಿ->min_w;
                min_ಎತ್ತರ_2 = ಕಿಟಕಿ->min_h;
                max_ಅಗಲ_2 = ಕಿಟಕಿ->max_w;
                max_ಎತ್ತರ_2 = ಕಿಟಕಿ->max_h;
            } ಇಲ್ಲದಿದ್ದರೆ {
                // Use the fixed size in the odd case where a non-resizable window somehow wound up tiled or maximized.
                min_ಅಗಲ_2 = ಕಿಟಕಿ->floating.w;
                min_ಎತ್ತರ_2 = ಕಿಟಕಿ->floating.h;
                max_ಅಗಲ_2 = ಕಿಟಕಿ->floating.w;
                max_ಎತ್ತರ_2 = ಕಿಟಕಿ->floating.h;
            }

            ಆದರೆ (min_ಅಗಲ_2) {
                viewport_ಅಗಲ = SDL_max(viewport_ಅಗಲ, min_ಅಗಲ_2);
            }
            ಆದರೆ (min_ಎತ್ತರ_2) {
                viewport_ಎತ್ತರ = SDL_max(viewport_ಎತ್ತರ, min_ಎತ್ತರ_2);
            }
            ಆದರೆ (max_ಅಗಲ_2) {
                viewport_ಅಗಲ = SDL_min(viewport_ಅಗಲ, max_ಅಗಲ_2);
            }
            ಆದರೆ (max_ಎತ್ತರ_2) {
                viewport_ಎತ್ತರ = SDL_min(viewport_ಎತ್ತರ, max_ಎತ್ತರ_2);
            }

            ದಶಮಾಂಶ aspect = (ದಶಮಾಂಶ)viewport_ಅಗಲ / (ದಶಮಾಂಶ)viewport_ಎತ್ತರ;
            ಆದರೆ (ಕಿಟಕಿ->min_aspect != 0.f && aspect < ಕಿಟಕಿ->min_aspect) {
                viewport_ಎತ್ತರ = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)viewport_ಅಗಲ / ಕಿಟಕಿ->min_aspect), 1);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->max_aspect != 0.f && aspect > ಕಿಟಕಿ->max_aspect) {
                viewport_ಅಗಲ = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)viewport_ಎತ್ತರ * ಕಿಟಕಿ->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            ಕಿಟಕಿ_ಅಗಲ = viewport_ಅಗಲ;
            ಕಿಟಕಿ_ಎತ್ತರ = viewport_ಎತ್ತರ;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            ಆದರೆ (!ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display) {
                ಆದರೆ (viewport_ಅಗಲ > ದತ್ತಾಂಶ->requested.logical_ಅಗಲ || viewport_ಎತ್ತರ > ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ) {
                    aspect = (ದಶಮಾಂಶ)viewport_ಅಗಲ / (ದಶಮಾಂಶ)viewport_ಎತ್ತರ;
                    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ ಕಿಟಕಿ_ಅನುಪಾತ = (ದಶಮಾಂಶ)ದತ್ತಾಂಶ->requested.logical_ಅಗಲ / (ದಶಮಾಂಶ)ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ;
                    ಆದರೆ (aspect >= ಕಿಟಕಿ_ಅನುಪಾತ) {
                        viewport_ಅಗಲ = ದತ್ತಾಂಶ->requested.logical_ಅಗಲ;
                        viewport_ಎತ್ತರ = SDL_lroundf((ದಶಮಾಂಶ)viewport_ಅಗಲ / aspect);
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (aspect < ಕಿಟಕಿ_ಅನುಪಾತ) {
                        viewport_ಎತ್ತರ = ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ;
                        viewport_ಅಗಲ = SDL_lroundf((ದಶಮಾಂಶ)viewport_ಎತ್ತರ * aspect);
                    }
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಆದರೆ (viewport_ಅಗಲ > ದತ್ತಾಂಶ->requested.pixel_ಅಗಲ || viewport_ಎತ್ತರ > ದತ್ತಾಂಶ->requested.pixel_ಎತ್ತರ) {
                    aspect = (ದಶಮಾಂಶ)viewport_ಅಗಲ / (ದಶಮಾಂಶ)viewport_ಎತ್ತರ;
                    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ ಕಿಟಕಿ_ಅನುಪಾತ = (ದಶಮಾಂಶ)ದತ್ತಾಂಶ->requested.pixel_ಅಗಲ / (ದಶಮಾಂಶ)ದತ್ತಾಂಶ->requested.pixel_ಎತ್ತರ;
                    ಆದರೆ (aspect >= ಕಿಟಕಿ_ಅನುಪಾತ) {
                        viewport_ಅಗಲ = ದತ್ತಾಂಶ->requested.pixel_ಅಗಲ;
                        viewport_ಎತ್ತರ = SDL_lroundf((ದಶಮಾಂಶ)viewport_ಅಗಲ / aspect);
                    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (aspect < ಕಿಟಕಿ_ಅನುಪಾತ) {
                        viewport_ಎತ್ತರ = ದತ್ತಾಂಶ->requested.pixel_ಎತ್ತರ;
                        viewport_ಅಗಲ = SDL_lroundf((ದಶಮಾಂಶ)viewport_ಎತ್ತರ * aspect);
                    }
                }
            }

            viewport_ಅಗಲ = SDL_max(viewport_ಅಗಲ, 1);
            viewport_ಎತ್ತರ = SDL_max(viewport_ಎತ್ತರ, 1);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ_ಅಗಲ = viewport_ಅಗಲ;
            ಕಿಟಕಿ_ಎತ್ತರ = viewport_ಎತ್ತರ;
        }

        ಆದರೆ (!ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display) {
            ದತ್ತಾಂಶ->current.pixel_ಅಗಲ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ, ಕಿಟಕಿ_ಅಗಲ);
            ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ, ಕಿಟಕಿ_ಎತ್ತರ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            // The viewport size is in pixels at this point; convert it to logical units.
            ದತ್ತಾಂಶ->current.pixel_ಅಗಲ = ಕಿಟಕಿ_ಅಗಲ;
            ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ = ಕಿಟಕಿ_ಎತ್ತರ;
            viewport_ಅಗಲ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, viewport_ಅಗಲ);
            viewport_ಎತ್ತರ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, viewport_ಎತ್ತರ);
        }

        // Clamp the physical window size to the system minimum required size.
        ದತ್ತಾಂಶ->requested.logical_ಅಗಲ = SDL_max(ದತ್ತಾಂಶ->requested.logical_ಅಗಲ, ದತ್ತಾಂಶ->system_limits.min_ಅಗಲ_2);
        ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ = SDL_max(ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ, ದತ್ತಾಂಶ->system_limits.min_ಎತ್ತರ_2);

        ಕಿಟಕಿ_ಗಾತ್ರ_ಬದಲಾಯಿತು = ದತ್ತಾಂಶ->requested.logical_ಅಗಲ != ದತ್ತಾಂಶ->current.logical_ಅಗಲ ||
                              ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ != ದತ್ತಾಂಶ->current.logical_ಎತ್ತರ ||
                              viewport_ಅಗಲ != ದತ್ತಾಂಶ->current.viewport_ಅಗಲ ||
                              viewport_ಎತ್ತರ != ದತ್ತಾಂಶ->current.viewport_ಎತ್ತರ;

        ಬಫರ್_ಗಾತ್ರ_ಬದಲಾಯಿತು = ದತ್ತಾಂಶ->current.pixel_ಅಗಲ != old_pixel_ಅಗಲ ||
                              ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ != old_pixel_ಎತ್ತರ;

        ಆದರೆ (ಕಿಟಕಿ_ಗಾತ್ರ_ಬದಲಾಯಿತು || ಬಫರ್_ಗಾತ್ರ_ಬದಲಾಯಿತು) {
            ಆದರೆ (ದತ್ತಾಂಶ->viewport) {
                wp_viewport_ಗಣ_destination(ದತ್ತಾಂಶ->viewport, viewport_ಅಗಲ, viewport_ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಮೇಲಿನ_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_ಗಣ_ಬಫರ್_scale(ದತ್ತಾಂಶ->surface, (int32_t)scale_ಗುಣಕ_2);
            }

            ದತ್ತಾಂಶ->current.logical_ಅಗಲ = ದತ್ತಾಂಶ->requested.logical_ಅಗಲ;
            ದತ್ತಾಂಶ->current.logical_ಎತ್ತರ = ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ;
            ದತ್ತಾಂಶ->current.viewport_ಅಗಲ = viewport_ಅಗಲ;
            ದತ್ತಾಂಶ->current.viewport_ಎತ್ತರ = viewport_ಎತ್ತರ;

            ದತ್ತಾಂಶ->ಸೂಚಕ_scale.x = (ದ್ವಿಗುಣ)ಕಿಟಕಿ_ಅಗಲ / (ದ್ವಿಗುಣ)viewport_ಅಗಲ;
            ದತ್ತಾಂಶ->ಸೂಚಕ_scale.y = (ದ್ವಿಗುಣ)ಕಿಟಕಿ_ಎತ್ತರ / (ದ್ವಿಗುಣ)viewport_ಎತ್ತರ;
        }
    }

    ಆದರೆ (ದತ್ತಾಂಶ->egl_ಕಿಟಕಿ && ಬಫರ್_ಗಾತ್ರ_ಬದಲಾಯಿತು) {
        WAYLAND_wl_egl_ಕಿಟಕಿ_resize(ದತ್ತಾಂಶ->egl_ಕಿಟಕಿ,
                                     ದತ್ತಾಂಶ->current.pixel_ಅಗಲ,
                                     ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    ಆದರೆ (!ದತ್ತಾಂಶ->enable_insets && ದತ್ತಾಂಶ->viewport && ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ->subcompositor && (!ದತ್ತಾಂಶ->is_fullscreen || Should_ಮುಖವಾಡ_Fullscreen()) &&
        (viewport_ಅಗಲ != ದತ್ತಾಂಶ->current.logical_ಅಗಲ || viewport_ಎತ್ತರ != ದತ್ತಾಂಶ->current.logical_ಎತ್ತರ)) {
        ರಚನೆ wl_ಬಫರ್ *old_ಬಫರ್ = ಖಾಲಿ;

        ಆದರೆ (!ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface) {
            ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface = wl_compositor_create_surface(ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ->compositor);
            SDL_WAYLAND_ರಿಜಿಸ್ಟರ್_surface(ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface);
            wl_surface_ಗಣ_user_ದತ್ತಾಂಶ(ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface, ದತ್ತಾಂಶ);
        }
        ಆದರೆ (!ದತ್ತಾಂಶ->ಮುಖವಾಡ.subsurface) {
            ದತ್ತಾಂಶ->ಮುಖವಾಡ.subsurface = wl_subcompositor_get_subsurface(ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ->subcompositor, ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface, ದತ್ತಾಂಶ->surface);
        }
        ಆದರೆ (!ದತ್ತಾಂಶ->ಮುಖವಾಡ.viewport) {
            ದತ್ತಾಂಶ->ಮುಖವಾಡ.viewport = wp_viewporter_get_viewport(ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ->viewporter, ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface);
        }
        ಆದರೆ (!ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಬಫರ್_2 || ದತ್ತಾಂಶ->ಮುಖವಾಡ.opaque != is_opaque) {
            old_ಬಫರ್ = ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಬಫರ್_2;
            ದತ್ತಾಂಶ->ಮುಖವಾಡ.opaque = is_opaque;
            ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಬಫರ್_2 = Wayland_Create_Single_Pixel_ಬಫರ್(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface, ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಬಫರ್_2, 0, 0);

        wl_subsurface_ಇರಿಸು_ಕೆಳಗೆ(ದತ್ತಾಂಶ->ಮುಖವಾಡ.subsurface, ದತ್ತಾಂಶ->surface);
        wp_viewport_ಗಣ_destination(ದತ್ತಾಂಶ->ಮುಖವಾಡ.viewport, ದತ್ತಾಂಶ->current.logical_ಅಗಲ, ದತ್ತಾಂಶ->current.logical_ಎತ್ತರ);

        ಆದರೆ (wl_surface_get_ಆವೃತ್ತಿ(ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface) >= WL_SURFACE_DAMAGE_ಬಫರ್_SINCE_ಆವೃತ್ತಿ) {
            wl_surface_damage_ಬಫರ್(ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } ಇಲ್ಲದಿದ್ದರೆ {
            wl_surface_damage(ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        ಆದರೆ (is_opaque) {
            ಗಣ_Surface_Opaque_Region(ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface, ದತ್ತಾಂಶ->current.logical_ಅಗಲ, ದತ್ತಾಂಶ->current.logical_ಎತ್ತರ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಗಣ_Surface_Opaque_Region(ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_x = -(ದತ್ತಾಂಶ->current.logical_ಅಗಲ - viewport_ಅಗಲ) / 2;
            ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_y = -(ದತ್ತಾಂಶ->current.logical_ಎತ್ತರ - viewport_ಎತ್ತರ) / 2;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_x = 0;
            ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_y = 0;
        }

        wl_subsurface_ಗಣ_position(ದತ್ತಾಂಶ->ಮುಖವಾಡ.subsurface, ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_x, ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_y);
        wl_surface_commit(ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface);

        ಆದರೆ (old_ಬಫರ್) {
            wl_ಬಫರ್_destroy(old_ಬಫರ್);
        }

        ದತ್ತಾಂಶ->ಮುಖವಾಡ.mapped = true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಮುಖವಾಡ.mapped) {
        wl_subsurface_ಗಣ_position(ದತ್ತಾಂಶ->ಮುಖವಾಡ.subsurface, 0, 0);
        wl_surface_attach(ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface, ಖಾಲಿ, 0, 0);
        wl_surface_commit(ದತ್ತಾಂಶ->ಮುಖವಾಡ.surface);

        ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_x = 0;
        ದತ್ತಾಂಶ->ಮುಖವಾಡ.ಸ್ಥಾನಾಂತರ_y = 0;
        ದತ್ತಾಂಶ->ಮುಖವಾಡ.mapped = false;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && ದತ್ತಾಂಶ->shell_surface.xdg.surface &&
        (ದತ್ತಾಂಶ->enable_insets || !ದತ್ತಾಂಶ->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(ಕಿಟಕಿ, &insets);
        ಸ್ಥಿರಾಂಕ bool use_insets = (insets.ಎಡ || insets.ತುದಿ || insets.ಬಲ || insets.bottom) &&
                                !(ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_MAXIMIZED | SDL_ಕಿಟಕಿ_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, ದತ್ತಾಂಶ->current.logical_ಅಗಲ, ದತ್ತಾಂಶ->current.logical_ಎತ್ತರ };
        ಆದರೆ (use_insets) {
            geometry.x = insets.ಎಡ;
            geometry.y = insets.ತುದಿ;
            geometry.w = SDL_max(geometry.w - (insets.ಎಡ + insets.ಬಲ), 1);
            geometry.h = SDL_max(geometry.h - (insets.ತುದಿ + insets.bottom), 1);
        }
        /* An explicitly set geometry does not track the surface, so it must be kept in sync
         * once set. Otherwise this is only done when viewports aren't supported and the size
         * has changed (XXX: a hack) to avoid a potential protocol violation if a buffer with
         * an old size is committed.
         */
        ಆದರೆ ((use_insets || !SDL_Rect_ಖಾಲಿಗಳು(&ದತ್ತಾಂಶ->explicit_geometry) || (!ದತ್ತಾಂಶ->viewport && ಕಿಟಕಿ_ಗಾತ್ರ_ಬದಲಾಯಿತು)) &&
            !SDL_RectsEqual(&geometry, &ದತ್ತಾಂಶ->explicit_geometry)) {
            xdg_surface_ಗಣ_ಕಿಟಕಿ_geometry(ದತ್ತಾಂಶ->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            ದತ್ತಾಂಶ->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    ಆದರೆ (ಕಿಟಕಿ_ಗಾತ್ರ_ಬದಲಾಯಿತು) {
        ಆದರೆ (is_opaque) {
            ಗಣ_Surface_Opaque_Region(ದತ್ತಾಂಶ->surface, viewport_ಅಗಲ, viewport_ಎತ್ತರ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಗಣ_Surface_Opaque_Region(ದತ್ತಾಂಶ->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        ಗಾಗಿ (SDL_ಕಿಟಕಿ *ಮಗು = ಕಿಟಕಿ->ಮೊದಲ_ಮಗು; ಮಗು; ಮಗು = ಮಗು->ಮುಂದಿನ_sibling) {
            RepositionPopup(ಮಗು, true);
        }
    }

    // Update the scale for any focused cursors.
    ಆದರೆ (prev_ಸೂಚಕ_scale_x != ದತ್ತಾಂಶ->ಸೂಚಕ_scale.x || prev_ಸೂಚಕ_scale_y != ದತ್ತಾಂಶ->ಸೂಚಕ_scale.y) {
        Wayland_Display_Update_ಸೂಚಕ_Focused_Scale(ದತ್ತಾಂಶ);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    ಗಣ_Min_Max_Dimensions(ಕಿಟಕಿ);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    ಆದರೆ (!ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display) {
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, ಕಿಟಕಿ_ಅಗಲ, ಕಿಟಕಿ_ಎತ್ತರ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESIZED, ದತ್ತಾಂಶ->current.pixel_ಅಗಲ, ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ);
    }
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_PIXEL_ಗಾತ್ರ_ಬದಲಾಯಿತು, ದತ್ತಾಂಶ->current.pixel_ಅಗಲ, ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN) {
        ಆದರೆ ((ಬಫರ್_ಗಾತ್ರ_ಬದಲಾಯಿತು || ಕಿಟಕಿ_ಗಾತ್ರ_ಬದಲಾಯಿತು) ||
            (!ದತ್ತಾಂಶ->suspended && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OCCLUDED))) {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_EXPOSED, 0, 0);
        }

        ಆದರೆ (ದತ್ತಾಂಶ->suspended) {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_OCCLUDED, 0, 0);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Commit_Libdecor_ಚೌಕಟ್ಟು(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
        ರಚನೆ libdecor_state *state = libdecor_state_new(wind->current.logical_ಅಗಲ, wind->current.logical_ಎತ್ತರ);
        libdecor_ಚೌಕಟ್ಟು_commit(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು, state, ಖಾಲಿ);
        libdecor_state_free(state);
    }
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಶೂನ್ಯ pending_state_deadline_handler(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_callback *callback, uint32_t callback_ದತ್ತಾಂಶ)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_ಕಿಟಕಿ_ID ಕಿಟಕಿ_ID = (SDL_ಕಿಟಕಿ_ID)(uintptr_t)ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = SDL_Get_ಕಿಟಕಿ_From_ID(ಕಿಟಕಿ_ID);

    ಆದರೆ (ಕಿಟಕಿ && ಕಿಟಕಿ->ಆಂತರಿಕ) {
        --ಕಿಟಕಿ->ಆಂತರಿಕ->pending_state_deadline_ಎಣಿಕೆ;
    }

    wl_callback_destroy(callback);
}

ಸ್ಥಿರ ರಚನೆ wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

ಸ್ಥಿರ ಶೂನ್ಯ ಕೂಡಿಸು_Pending_State_Sync(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2)
{
    SDL_Video_ದತ್ತಾಂಶ *video_ದತ್ತಾಂಶ = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->wayland_ದತ್ತಾಂಶ;
    ಶೂನ್ಯ *cb_ದತ್ತಾಂಶ = (ಶೂನ್ಯ *)(uintptr_t)ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow->id;

    ++ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->pending_state_deadline_ಎಣಿಕೆ;
    ರಚನೆ wl_callback *cb = wl_display_sync(video_ದತ್ತಾಂಶ->display);
    wl_callback_ಕೂಡಿಸು_listener(cb, &pending_state_deadline_listener, cb_ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ ಶೂನ್ಯ FlushPendingEvents(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ಸ್ಥಿರಾಂಕ bool ಕೊನೆಯ_position_pending = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending;
    ಸ್ಥಿರಾಂಕ bool ಕೊನೆಯ_ಗಾತ್ರ_pending = ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending;

    ಆಗ (ಕಿಟಕಿ->ಆಂತರಿಕ->pending_state_deadline_ಎಣಿಕೆ) {
        WAYLAND_wl_display_roundtrip(ಕಿಟಕಿ->ಆಂತರಿಕ->wayland_ದತ್ತಾಂಶ->display);
    }

    ಕಿಟಕಿ->ಕೊನೆಯ_position_pending = ಕೊನೆಯ_position_pending;
    ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending = ಕೊನೆಯ_ಗಾತ್ರ_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
ಶೂನ್ಯ Wayland_Update_ಕಿಟಕಿ_Position(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *display;

    ಆದರೆ (wind->outputs && wind->ಅಂಕೆ_outputs) {
        display = wind->outputs[wind->ಅಂಕೆ_outputs - 1];
    } ಇಲ್ಲದಿದ್ದರೆ {
        // A window may not be on any displays if minimized.
        ಹಿಂತಿರುಗಿ;
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
    wind->ಕೊನೆಯ_display_ID = display->display;
    ಆದರೆ (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        ಆದರೆ (!wind->wayland_ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display_enabled) {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MOVED, display->logical.x, display->logical.y);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_DISPLAY_ಬದಲಾಯಿತು, wind->ಕೊನೆಯ_display_ID, 0);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಗಣ_Fullscreen(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ರಚನೆ wl_output *output, bool fullscreen)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ಆದರೆ (!wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
            ಹಿಂತಿರುಗಿ; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? ಕಿಟಕಿ->fullscreen_exclusive : false;
        ಆದರೆ (fullscreen) {
            libdecor_ಚೌಕಟ್ಟು_ಗಣ_fullscreen(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು, output);
        } ಇಲ್ಲದಿದ್ದರೆ {
            libdecor_ಚೌಕಟ್ಟು_unset_fullscreen(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು);
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ಆದರೆ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ಖಾಲಿ) {
            ಹಿಂತಿರುಗಿ; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? ಕಿಟಕಿ->fullscreen_exclusive : false;
        ಆದರೆ (fullscreen) {
            xdg_toplevel_ಗಣ_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } ಇಲ್ಲದಿದ್ದರೆ {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    ಕೂಡಿಸು_Pending_State_Sync(wind);
}

ಸ್ಥಿರ ಶೂನ್ಯ Update_ಕಿಟಕಿ_Fullscreen(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool fullscreen)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    wind->is_fullscreen = fullscreen;

    ಆದರೆ (fullscreen) {
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN)) {
            SDL_copyp(&ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ, &ಕಿಟಕಿ->requested_fullscreen_ಬಹುಲಕ);
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_ENTER_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            ಆದರೆ (ಕಿಟಕಿ->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(ಕಿಟಕಿ->current_fullscreen_ಬಹುಲಕ.displayID);
                ಆದರೆ (disp) {
                    wind->fullscreen_was_positioned = true;
                    ಗಣ_Fullscreen(ಕಿಟಕಿ, disp->ಆಂತರಿಕ->output, true);
                }
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) && !ಕಿಟಕಿ->is_hiding && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_LEAVE_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_ಬಹುಲಕ(ಕಿಟಕಿ, SDL_FULLSCREEN_OP_LEAVE, false);
            wind->fullscreen_was_positioned = false;

            /* Send a move event, in case it was deferred while the fullscreen window was moving and
             * on multiple outputs.
             */
            Wayland_Update_ಕಿಟಕಿ_Position(ಕಿಟಕಿ);
        }
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_callback_listener surface_ಚೌಕಟ್ಟು_listener;

ಸ್ಥಿರ ಶೂನ್ಯ surface_ಚೌಕಟ್ಟು_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_callback *cb, uint32_t ಸಮಯ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    ಆದರೆ (wl_compositor_get_ಆವೃತ್ತಿ(wind->wayland_ದತ್ತಾಂಶ->compositor) >= WL_SURFACE_DAMAGE_ಬಫರ್_SINCE_ಆವೃತ್ತಿ) {
        wl_surface_damage_ಬಫರ್(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } ಇಲ್ಲದಿದ್ದರೆ {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ಆದರೆ (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            Configure_ಕಿಟಕಿ_Geometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        wind->resizing = false;
    }

    ಆದರೆ (wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_ಚೌಕಟ್ಟು) {
        wind->shell_surface_ಸ್ಥಿತಿ = WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        ಗಾಗಿ (SDL_ಕಿಟಕಿ *w = wind->sdlwindow->ಮೊದಲ_ಮಗು; w; w = w->ಮುಂದಿನ_sibling) {
            ಆದರೆ (w->ಆಂತರಿಕ->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOW_PENDING) {
                Wayland_Show_ಕಿಟಕಿ(SDL_GetVideoDevice(), w);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (w->ಆಂತರಿಕ->reparenting_required) {
                Wayland_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(SDL_GetVideoDevice(), w, w->ಪೋಷಕ);
                ಆದರೆ (w->flags & SDL_ಕಿಟಕಿ_MODAL) {
                    Wayland_ಗಣ_ಕಿಟಕಿ_Modal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        ಆದರೆ (wind->suspended) {
            SDL_Send_ಕಿಟಕಿ_Event(wind->sdlwindow, SDL_EVENT_ಕಿಟಕಿ_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_ಚೌಕಟ್ಟು_callback = wl_surface_ಚೌಕಟ್ಟು(wind->surface);
    wl_callback_ಕೂಡಿಸು_listener(wind->surface_ಚೌಕಟ್ಟು_callback, &surface_ಚೌಕಟ್ಟು_listener, ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_callback_listener surface_ಚೌಕಟ್ಟು_listener = {
    surface_ಚೌಕಟ್ಟು_ಮುಗಿದ
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_callback_listener gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_listener;

ಸ್ಥಿರ ಶೂನ್ಯ gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_callback *cb, uint32_t ಸಮಯ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    SDL_ಗಣ_Atomic_Int(&wind->ಅದಲುಬದಲು_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback = wl_surface_ಚೌಕಟ್ಟು(wind->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_ಕೂಡಿಸು_listener(wind->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback, &gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_listener, ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_callback_listener gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_listener = {
    gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_ಮುಗಿದ
};

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_surface_configure(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ xdg_surface *xdg, uint32_t serial)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    ಆದರೆ (!wind->resizing) {
        wind->pending_config_ack = false;
        Configure_ಕಿಟಕಿ_Geometry(ಕಿಟಕಿ);
        xdg_surface_ack_configure(xdg, serial);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_EXPOSED, 0, 0);
    }

    ಆದರೆ (wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE) {
        wind->shell_surface_ಸ್ಥಿತಿ = WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_ಚೌಕಟ್ಟು;
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

ಸ್ಥಿರ ಶೂನ್ಯ ApplyGeometryLimits(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ req_w, ಪೂರ್ಣಾಂಕ req_h, ಪೂರ್ಣಾಂಕ *ಹೊರಹೋಗು_w, ಪೂರ್ಣಾಂಕ *ಹೊರಹೋಗು_h)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಪೂರ್ಣಾಂಕ w = req_w;
    ಪೂರ್ಣಾಂಕ h = req_h;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ aspect = (ದಶಮಾಂಶ)req_w / (ದಶಮಾಂಶ)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    ಆದರೆ (!wind->resizing || (wind->resize_ಅಂಚು & WAYLAND_RESIZE_ಅಂಚು_ಮೂಲೆ) == WAYLAND_RESIZE_ಅಂಚು_ಮೂಲೆ) {
        ಆದರೆ (ಕಿಟಕಿ->min_aspect != 0.f && aspect < ಕಿಟಕಿ->min_aspect) {
            h = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)req_w / ಕಿಟಕಿ->min_aspect), 1);

            ಆದರೆ (h < ಕಿಟಕಿ->min_h) {
                w = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->min_h * ಕಿಟಕಿ->min_aspect), 1);
            }
            ಆದರೆ (ಕಿಟಕಿ->max_h && h > ಕಿಟಕಿ->max_h) {
                w = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->max_h * ಕಿಟಕಿ->min_aspect), 1);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->max_aspect != 0.f && aspect > ಕಿಟಕಿ->max_aspect) {
            w = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)req_h * ಕಿಟಕಿ->max_aspect), 1);

            ಆದರೆ (w < ಕಿಟಕಿ->min_w) {
                h = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->min_w / ಕಿಟಕಿ->max_aspect), 1);
            }
            ಆದರೆ (ಕಿಟಕಿ->max_w && w > ಕಿಟಕಿ->max_w) {
                h = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->max_w / ಕಿಟಕಿ->max_aspect), 1);
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (wind->resize_ಅಂಚು & WAYLAND_RESIZE_ಅಂಚು_LR) {
        ಆದರೆ (ಕಿಟಕಿ->min_aspect != 0.f && aspect < ಕಿಟಕಿ->min_aspect) {
            h = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)req_w / ಕಿಟಕಿ->min_aspect), 1);

            ಆದರೆ (h < ಕಿಟಕಿ->min_h) {
                w = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->min_h * ಕಿಟಕಿ->min_aspect), 1);
            }
            ಆದರೆ (ಕಿಟಕಿ->max_h && h > ಕಿಟಕಿ->max_h) {
                w = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->max_h * ಕಿಟಕಿ->min_aspect), 1);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->max_aspect != 0.f && aspect > ಕಿಟಕಿ->max_aspect) {
            h = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)req_w / ಕಿಟಕಿ->max_aspect), 1);

            ಆದರೆ (h < ಕಿಟಕಿ->min_h) {
                w = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->min_h * ಕಿಟಕಿ->max_aspect), 1);
            }
            ಆದರೆ (ಕಿಟಕಿ->max_h && h > ಕಿಟಕಿ->max_h) {
                w = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->max_h * ಕಿಟಕಿ->max_aspect), 1);
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (wind->resize_ಅಂಚು & WAYLAND_RESIZE_ಅಂಚು_TB) {
        ಆದರೆ (ಕಿಟಕಿ->min_aspect != 0.f && aspect < ಕಿಟಕಿ->min_aspect) {
            w = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)req_h * ಕಿಟಕಿ->min_aspect), 1);

            ಆದರೆ (w < ಕಿಟಕಿ->min_w) {
                h = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->min_w / ಕಿಟಕಿ->min_aspect), 1);
            }
            ಆದರೆ (ಕಿಟಕಿ->max_w && w > ಕಿಟಕಿ->max_w) {
                h = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->max_w / ಕಿಟಕಿ->min_aspect), 1);
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->max_aspect != 0.f && aspect > ಕಿಟಕಿ->max_aspect) {
            w = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)req_h * ಕಿಟಕಿ->max_aspect), 1);

            ಆದರೆ (w < ಕಿಟಕಿ->min_w) {
                h = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->min_w / ಕಿಟಕಿ->max_aspect), 1);
            }
            ಆದರೆ (ಕಿಟಕಿ->max_w && w > ಕಿಟಕಿ->max_w) {
                h = SDL_max(SDL_lroundf((ದಶಮಾಂಶ)ಕಿಟಕಿ->max_w / ಕಿಟಕಿ->max_aspect), 1);
            }
        }
    }

    ಆದರೆ (ಕಿಟಕಿ->max_w) {
        w = SDL_min(w, ಕಿಟಕಿ->max_w);
    }
    *ಹೊರಹೋಗು_w = SDL_max(w, ಕಿಟಕಿ->min_w);

    ಆದರೆ (ಕಿಟಕಿ->max_h) {
        h = SDL_min(h, ಕಿಟಕಿ->max_h);
    }
    *ಹೊರಹೋಗು_h = SDL_max(h, ಕಿಟಕಿ->min_h);

}

ಸ್ಥಿರ ಶೂನ್ಯ DetermineResizeAxis(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, bool resizing)
{
    /* Try to determine the axis along which the window is being resized.
     *
     * Every compositor is different, and some will start sending strange values once the resize
     * begins, so only the first change is safe to try and determine the resize edge.
     *
     * Some compositors don't send a configure event with the resize flag cleared when the resize ends,
     * so a reset timer is required.
     */
    ಆದರೆ (resizing) {
        ಸ್ಥಿರಾಂಕ Uint64 now = SDL_GetTicksNS();
        ಆದರೆ (now >= wind->ಕೊನೆಯ_resize_event_ಸಮಯ_ns + SDL_MS_ಗಮ್ಯ_NS(500)) {
            wind->resize_ಅಂಚು = 0;
        }

        wind->ಕೊನೆಯ_resize_event_ಸಮಯ_ns = now;

        ಆದರೆ (!wind->resize_ಅಂಚು) {
            ಆದರೆ (ಅಗಲ != wind->ಕೊನೆಯ_configure.ಅಗಲ || !ಎತ್ತರ) {
                wind->resize_ಅಂಚು |= WAYLAND_RESIZE_ಅಂಚು_LR;
            }
            ಆದರೆ (ಎತ್ತರ != wind->ಕೊನೆಯ_configure.ಎತ್ತರ || !ಅಗಲ) {
                wind->resize_ಅಂಚು |= WAYLAND_RESIZE_ಅಂಚು_TB;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        wind->resize_ಅಂಚು = 0;
    }

    wind->resizing = resizing;
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_toplevel_configure(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                          ರಚನೆ xdg_toplevel *xdg_toplevel,
                                          int32_t ಅಗಲ,
                                          int32_t ಎತ್ತರ,
                                          ರಚನೆ wl_array *ಸ್ಥಿತಿಗಳು)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = wind->sdlwindow;

    ಎಣಿಕೆ xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool ಸಕ್ರಿಯ = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, ಸ್ಥಿತಿಗಳು) {
        ಆಯ್ಕೆ (*state) {
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_FULLSCREEN:
            fullscreen = true;
            floating = false;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_MAXIMIZED:
            maximized = true;
            floating = false;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_RESIZING:
            resizing = true;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_ACTIVATED:
            ಸಕ್ರಿಯ = true;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_TILED_ಎಡ:
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_TILED_ಬಲ:
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_TILED_ತುದಿ:
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_CONSTRAINED_ಎಡ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_CONSTRAINED_ಬಲ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_CONSTRAINED_ತುದಿ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_STATE_CONSTRAINED_BOTTOM:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }

    /* Configure sizes are in window geometry space; add the border insets, if any, to get
     * the surface size. Maximized and fullscreen windows must use the configured size as-is,
     * so a change in inset applicability requires re-adopting even an unchanged size, and
     * sizes adopted from the cached window size are converted back to geometry space for
     * the last_configure store.
     */
    ಸ್ಥಿರಾಂಕ bool insets_apply = wind->enable_insets && !fullscreen && !maximized;

    // When resizing, dimensions other than 0 are a maximum.
    ಸ್ಥಿರಾಂಕ bool new_configure_ಗಾತ್ರ = ಅಗಲ != wind->ಕೊನೆಯ_configure.ಅಗಲ || ಎತ್ತರ != wind->ಕೊನೆಯ_configure.ಎತ್ತರ ||
                                    insets_apply != wind->ಕೊನೆಯ_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    ಆದರೆ (insets_apply) {
        GetBorderInsets(ಕಿಟಕಿ, &insets);
    }

    DetermineResizeAxis(wind, ಅಗಲ, ಎತ್ತರ, resizing);
    Update_ಕಿಟಕಿ_Fullscreen(ಕಿಟಕಿ, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from xdg-shell, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    ಆದರೆ (ಸಕ್ರಿಯ || !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED)) {
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESTORED, 0, 0);
        }
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ,
                            (maximized && !fullscreen) ? SDL_EVENT_ಕಿಟಕಿ_MAXIMIZED : SDL_EVENT_ಕಿಟಕಿ_RESTORED,
                            0, 0);
    }

    ಆದರೆ (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE) || maximized) {
            ಆದರೆ (!ಅಗಲ) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                ಆದರೆ (floating) {
                    ಅಗಲ = ಕಿಟಕಿ->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ಆದರೆ (wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE && wind->toplevel_bounds.ಅಗಲ) {
                        ಅಗಲ = SDL_min(wind->toplevel_bounds.ಅಗಲ, ಅಗಲ);
                    }
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಅಗಲ = ಕಿಟಕಿ->windowed.w;
                }

                ಆದರೆ (!wind->scale_ಗಮ್ಯ_display) {
                    wind->requested.logical_ಅಗಲ = ಅಗಲ;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    wind->requested.pixel_ಅಗಲ = ಅಗಲ;
                    ಅಗಲ = wind->requested.logical_ಅಗಲ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಅಗಲ);
                }
                ಅಗಲ = SDL_max(ಅಗಲ - (insets.ಎಡ + insets.ಬಲ), 1);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (new_configure_ಗಾತ್ರ) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_ಅಗಲ = ಅಗಲ + (insets.ಎಡ + insets.ಬಲ);

                ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
                    wind->requested.pixel_ಅಗಲ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ, wind->requested.logical_ಅಗಲ);
                }
            }
            ಆದರೆ (!ಎತ್ತರ) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                ಆದರೆ (floating) {
                    ಎತ್ತರ = ಕಿಟಕಿ->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ಆದರೆ (wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE && wind->toplevel_bounds.ಎತ್ತರ) {
                        ಎತ್ತರ = SDL_min(wind->toplevel_bounds.ಎತ್ತರ, ಎತ್ತರ);
                    }
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಎತ್ತರ = ಕಿಟಕಿ->windowed.h;
                }

                ಆದರೆ (!wind->scale_ಗಮ್ಯ_display) {
                    wind->requested.logical_ಎತ್ತರ = ಎತ್ತರ;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    wind->requested.pixel_ಎತ್ತರ = ಎತ್ತರ;
                    ಎತ್ತರ = wind->requested.logical_ಎತ್ತರ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಎತ್ತರ);
                }
                ಎತ್ತರ = SDL_max(ಎತ್ತರ - (insets.ತುದಿ + insets.bottom), 1);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (new_configure_ಗಾತ್ರ) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_ಎತ್ತರ = ಎತ್ತರ + (insets.ತುದಿ + insets.bottom);

                ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
                    wind->requested.pixel_ಎತ್ತರ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ, wind->requested.logical_ಎತ್ತರ);
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            ಆದರೆ (!wind->scale_ಗಮ್ಯ_display) {
                ಅಗಲ = wind->requested.logical_ಅಗಲ = ಕಿಟಕಿ->floating.w;
                ಎತ್ತರ = wind->requested.logical_ಎತ್ತರ = ಕಿಟಕಿ->floating.h;
            } ಇಲ್ಲದಿದ್ದರೆ {
                wind->requested.pixel_ಅಗಲ = ಕಿಟಕಿ->floating.w;
                wind->requested.pixel_ಎತ್ತರ = ಕಿಟಕಿ->floating.h;
                ಅಗಲ = wind->requested.logical_ಅಗಲ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಕಿಟಕಿ->floating.w);
                ಎತ್ತರ = wind->requested.logical_ಎತ್ತರ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಕಿಟಕಿ->floating.h);
            }
            ಅಗಲ = SDL_max(ಅಗಲ - (insets.ಎಡ + insets.ಬಲ), 1);
            ಎತ್ತರ = SDL_max(ಎತ್ತರ - (insets.ತುದಿ + insets.bottom), 1);
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
        ಆದರೆ (floating) {
            ಆದರೆ (!wind->scale_ಗಮ್ಯ_display) {
                ApplyGeometryLimits(ಕಿಟಕಿ, wind->requested.logical_ಅಗಲ, wind->requested.logical_ಎತ್ತರ, &wind->requested.logical_ಅಗಲ, &wind->requested.logical_ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ApplyGeometryLimits(ಕಿಟಕಿ, wind->requested.pixel_ಅಗಲ, wind->requested.pixel_ಎತ್ತರ, &wind->requested.pixel_ಅಗಲ, &wind->requested.pixel_ಎತ್ತರ);

                wind->requested.logical_ಅಗಲ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, wind->requested.pixel_ಅಗಲ);
                wind->requested.logical_ಎತ್ತರ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, wind->requested.pixel_ಎತ್ತರ);
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Fullscreen windows know their exact size.
        ಆದರೆ (ಅಗಲ == 0 || ಎತ್ತರ == 0) {
            ಅಗಲ = wind->requested.logical_ಅಗಲ;
            ಎತ್ತರ = wind->requested.logical_ಎತ್ತರ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            wind->requested.logical_ಅಗಲ = ಅಗಲ;
            wind->requested.logical_ಎತ್ತರ = ಎತ್ತರ;
        }

        ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
            wind->requested.pixel_ಅಗಲ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ, ಅಗಲ);
            wind->requested.pixel_ಎತ್ತರ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ, ಎತ್ತರ);
        }
    }

    wind->ಕೊನೆಯ_configure.ಅಗಲ = ಅಗಲ;
    wind->ಕೊನೆಯ_configure.ಎತ್ತರ = ಎತ್ತರ;
    wind->ಕೊನೆಯ_configure.insets_apply = insets_apply;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->ಸಕ್ರಿಯ = ಸಕ್ರಿಯ;
    ಕಿಟಕಿ->tiled = tiled;
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_toplevel_close(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ xdg_toplevel *xdg_toplevel)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ->sdlwindow, SDL_EVENT_ಕಿಟಕಿ_CLOSE_REQUESTED, 0, 0);
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_toplevel_configure_bounds(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                 ರಚನೆ xdg_toplevel *xdg_toplevel,
                                                 int32_t ಅಗಲ, int32_t ಎತ್ತರ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    ಕಿಟಕಿ->toplevel_bounds.ಅಗಲ = ಅಗಲ;
    ಕಿಟಕಿ->toplevel_bounds.ಎತ್ತರ = ಎತ್ತರ;
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_toplevel_wm_capabilities(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                ರಚನೆ xdg_toplevel *xdg_toplevel,
                                                ರಚನೆ wl_array *capabilities)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    ಎಣಿಕೆ xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        ಆಯ್ಕೆ (*wm_cap) {
        ಸ್ಥಿತಿ XDG_TOPLEVEL_WM_CAPABILITIES_ಕಿಟಕಿ_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_ಕಿಟಕಿ_MENU;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_WM_CAPABILITIES_MAXIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MAXIMIZE;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_WM_CAPABILITIES_FULLSCREEN:
            wind->wm_caps |= WAYLAND_WM_CAPS_FULLSCREEN;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ XDG_TOPLEVEL_WM_CAPABILITIES_MINIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MINIMIZE;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ xdg_toplevel_listener toplevel_listener_xdg = {
    handle_xdg_toplevel_configure,
    handle_xdg_toplevel_close,
    handle_xdg_toplevel_configure_bounds, // Version 4
    handle_xdg_toplevel_wm_capabilities   // Version 5
};

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_popup_configure(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                       ರಚನೆ xdg_popup *xdg_popup,
                                       int32_t x,
                                       int32_t y,
                                       int32_t ಅಗಲ,
                                       int32_t ಎತ್ತರ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_x = 0, ಸ್ಥಾನಾಂತರ_y = 0;

    // Adjust the position if it was offset for libdecor
    Adjust_Popup_ಸ್ಥಾನಾಂತರ(wind->sdlwindow, &ಸ್ಥಾನಾಂತರ_x, &ಸ್ಥಾನಾಂತರ_y);
    x -= ಸ್ಥಾನಾಂತರ_x;
    y -= ಸ್ಥಾನಾಂತರ_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    ಆದರೆ (ಅಗಲ == 0 || ಎತ್ತರ == 0) {
        ಅಗಲ = wind->sdlwindow->floating.w;
        ಎತ್ತರ = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    ಆದರೆ (ಅಗಲ != wind->ಕೊನೆಯ_configure.ಅಗಲ || ಎತ್ತರ != wind->ಕೊನೆಯ_configure.ಎತ್ತರ) {
        wind->requested.logical_ಅಗಲ = ಅಗಲ;
        wind->requested.logical_ಎತ್ತರ = ಎತ್ತರ;

        ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
            wind->requested.pixel_ಅಗಲ = ಬಿಂದು_ಗಮ್ಯ_Pixel(wind->sdlwindow, ಅಗಲ);
            wind->requested.pixel_ಎತ್ತರ = ಬಿಂದು_ಗಮ್ಯ_Pixel(wind->sdlwindow, ಎತ್ತರ);
        }
    }

    ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
        x = ಬಿಂದು_ಗಮ್ಯ_Pixel(wind->sdlwindow->ಪೋಷಕ, x);
        y = ಬಿಂದು_ಗಮ್ಯ_Pixel(wind->sdlwindow->ಪೋಷಕ, y);
    }

    SDL_Send_ಕಿಟಕಿ_Event(wind->sdlwindow, SDL_EVENT_ಕಿಟಕಿ_MOVED, x, y);

    wind->ಕೊನೆಯ_configure.ಅಗಲ = ಅಗಲ;
    wind->ಕೊನೆಯ_configure.ಎತ್ತರ = ಎತ್ತರ;

    ಆದರೆ (wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE) {
        wind->shell_surface_ಸ್ಥಿತಿ = WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_ಚೌಕಟ್ಟು;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_popup_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ xdg_popup *xdg_popup)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ->sdlwindow, SDL_EVENT_ಕಿಟಕಿ_CLOSE_REQUESTED, 0, 0);
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_popup_repositioned(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                          ರಚನೆ xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_ಮುಗಿದ,
    handle_xdg_popup_repositioned
};

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_toplevel_decoration_configure(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                     ರಚನೆ zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
                                                     uint32_t ಬಹುಲಕ)
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = (SDL_ಕಿಟಕಿ *)ದತ್ತಾಂಶ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಆಂತರಿಕ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    /* If the compositor tries to force CSD anyway, bail on direct XDG support
     * and fall back to libdecor, it will handle these events from then on.
     *
     * To do this we have to fully unmap, then map with libdecor loaded.
     */
    ಆದರೆ (ಬಹುಲಕ == ZXDG_TOPLEVEL_DECORATION_V1_ಬಹುಲಕ_CLIENT_SIDE) {
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            ಹಿಂತಿರುಗಿ;
        }
        ಆದರೆ (!Wayland_ತುಂಬು_Libdecor(ಆಂತರಿಕ->wayland_ದತ್ತಾಂಶ, true)) {
            // libdecor isn't available, so no borders for you... oh well
            ಹಿಂತಿರುಗಿ;
        }
        WAYLAND_wl_display_roundtrip(ಆಂತರಿಕ->wayland_ದತ್ತಾಂಶ->display);

        Wayland_Hide_ಕಿಟಕಿ(device, ಕಿಟಕಿ);
        ಆಂತರಿಕ->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_Show_ಕಿಟಕಿ(device, ಕಿಟಕಿ);
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
    handle_xdg_toplevel_decoration_configure
};

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
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
ಸ್ಥಿರ ಶೂನ್ಯ OverrideLibdecorLimits(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    ಆದರೆ (!libdecor_ಚೌಕಟ್ಟು_get_min_content_ಗಾತ್ರ) {
        libdecor_ಚೌಕಟ್ಟು_ಗಣ_min_content_ಗಾತ್ರ(ಕಿಟಕಿ->ಆಂತರಿಕ->shell_surface.libdecor.ಚೌಕಟ್ಟು, ಕಿಟಕಿ->min_w, ಕಿಟಕಿ->min_h);
    }
#ಅಥವಾಆದರೆ !SDL_LIBDECOR_CHECK_ಆವೃತ್ತಿ(0, 2, 0)
    libdecor_ಚೌಕಟ್ಟು_ಗಣ_min_content_ಗಾತ್ರ(ಕಿಟಕಿ->ಆಂತರಿಕ->shell_surface.libdecor.ಚೌಕಟ್ಟು, ಕಿಟಕಿ->min_w, ಕಿಟಕಿ->min_h);
#ಆದರೆ_ಅಂತ್ಯ
}

/*
 * NOTE: Retrieves the minimum content size limits, if the function for doing so is available.
 *       On versions of libdecor that lack the minimum content size retrieval function, this
 *       function is a no-op.
 *
 *       Can be replaced with a direct call if the minimum required version of libdecor is raised
 *       to 0.1.2 or higher.
 */
ಸ್ಥಿರ ಶೂನ್ಯ Libdecor_Get_Min_Content_ಗಾತ್ರ(ರಚನೆ libdecor_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು, ಪೂರ್ಣಾಂಕ *min_w, ಪೂರ್ಣಾಂಕ *min_h)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    ಆದರೆ (libdecor_ಚೌಕಟ್ಟು_get_min_content_ಗಾತ್ರ != ಖಾಲಿ) {
        libdecor_ಚೌಕಟ್ಟು_get_min_content_ಗಾತ್ರ(ಚೌಕಟ್ಟು, min_w, min_h);
    }
#ಅಥವಾಆದರೆ SDL_LIBDECOR_CHECK_ಆವೃತ್ತಿ(0, 2, 0)
    libdecor_ಚೌಕಟ್ಟು_get_min_content_ಗಾತ್ರ(ಚೌಕಟ್ಟು, min_w, min_h);
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಶೂನ್ಯ decoration_ಚೌಕಟ್ಟು_configure(ರಚನೆ libdecor_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು,
                                       ರಚನೆ libdecor_configuration *configuration,
                                       ಶೂನ್ಯ *user_ದತ್ತಾಂಶ_2)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)user_ದತ್ತಾಂಶ_2;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = wind->sdlwindow;

    ಎಣಿಕೆ libdecor_ಕಿಟಕಿ_state ಕಿಟಕಿ_state;
    ಪೂರ್ಣಾಂಕ ಅಗಲ, ಎತ್ತರ;

    bool ಸಕ್ರಿಯ = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ libdecor_ಕಿಟಕಿ_state tiled_ಸ್ಥಿತಿಗಳು = (LIBDECOR_ಕಿಟಕಿ_STATE_TILED_ಎಡ | LIBDECOR_ಕಿಟಕಿ_STATE_TILED_ಬಲ |
                                                            LIBDECOR_ಕಿಟಕಿ_STATE_TILED_ತುದಿ | LIBDECOR_ಕಿಟಕಿ_STATE_TILED_BOTTOM);

    ಆದರೆ (wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE) {
        Libdecor_Get_Min_Content_ಗಾತ್ರ(ಚೌಕಟ್ಟು, &wind->system_limits.min_ಅಗಲ_2, &wind->system_limits.min_ಎತ್ತರ_2);
    }

    // Window State
    ಆದರೆ (libdecor_configuration_get_ಕಿಟಕಿ_state(configuration, &ಕಿಟಕಿ_state)) {
        fullscreen = (ಕಿಟಕಿ_state & LIBDECOR_ಕಿಟಕಿ_STATE_FULLSCREEN) != 0;
        maximized = (ಕಿಟಕಿ_state & LIBDECOR_ಕಿಟಕಿ_STATE_MAXIMIZED) != 0;
        ಸಕ್ರಿಯ = (ಕಿಟಕಿ_state & LIBDECOR_ಕಿಟಕಿ_STATE_ಸಕ್ರಿಯ) != 0;
        tiled = (ಕಿಟಕಿ_state & tiled_ಸ್ಥಿತಿಗಳು) != 0;
#ಆದರೆ SDL_LIBDECOR_CHECK_ಆವೃತ್ತಿ(0, 2, 0)
        suspended = (ಕಿಟಕಿ_state & LIBDECOR_ಕಿಟಕಿ_STATE_SUSPENDED) != 0;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ SDL_LIBDECOR_CHECK_ಆವೃತ್ತಿ(0, 3, 0)
        resizing = (ಕಿಟಕಿ_state & LIBDECOR_ಕಿಟಕಿ_STATE_RESIZING) != 0;

        ಆದರೆ (ಕಿಟಕಿ_state & LIBDECOR_ಕಿಟಕಿ_STATE_CONSTRAINED_ಎಡ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ;
        }
        ಆದರೆ (ಕಿಟಕಿ_state & LIBDECOR_ಕಿಟಕಿ_STATE_CONSTRAINED_ಬಲ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ;
        }
        ಆದರೆ (ಕಿಟಕಿ_state & LIBDECOR_ಕಿಟಕಿ_STATE_CONSTRAINED_ತುದಿ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ;
        }
        ಆದರೆ (ಕಿಟಕಿ_state & LIBDECOR_ಕಿಟಕಿ_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#ಆದರೆ_ಅಂತ್ಯ
    }
    ಸ್ಥಿರಾಂಕ bool floating = !(fullscreen || maximized || tiled);

    Update_ಕಿಟಕಿ_Fullscreen(ಕಿಟಕಿ, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from libdecor, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    ಆದರೆ (ಸಕ್ರಿಯ || !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED)) {
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_RESTORED, 0, 0);
        }
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ,
                            (maximized && !fullscreen) ? SDL_EVENT_ಕಿಟಕಿ_MAXIMIZED : SDL_EVENT_ಕಿಟಕಿ_RESTORED,
                            0, 0);
    }

    /* For fullscreen or fixed-size windows we know our size.
     * Always assume the configure is wrong.
     */
    ಆದರೆ (fullscreen) {
        ಆದರೆ (!libdecor_configuration_get_content_ಗಾತ್ರ(configuration, ಚೌಕಟ್ಟು, &ಅಗಲ, &ಎತ್ತರ)) {
            ಅಗಲ = wind->requested.logical_ಅಗಲ;
            ಎತ್ತರ = wind->requested.logical_ಎತ್ತರ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Fullscreen windows know their exact size.
            wind->requested.logical_ಅಗಲ = ಅಗಲ;
            wind->requested.logical_ಎತ್ತರ = ಎತ್ತರ;

            ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
                wind->requested.pixel_ಅಗಲ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ, ಅಗಲ);
                wind->requested.pixel_ಎತ್ತರ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ, ಎತ್ತರ);
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            ಆದರೆ (!wind->scale_ಗಮ್ಯ_display) {
                ಅಗಲ = wind->requested.logical_ಅಗಲ = ಕಿಟಕಿ->floating.w;
                ಎತ್ತರ = wind->requested.logical_ಎತ್ತರ = ಕಿಟಕಿ->floating.h;
            } ಇಲ್ಲದಿದ್ದರೆ {
                wind->requested.pixel_ಅಗಲ = ಕಿಟಕಿ->floating.w;
                wind->requested.pixel_ಎತ್ತರ = ಕಿಟಕಿ->floating.h;
                ಅಗಲ = wind->requested.logical_ಅಗಲ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಕಿಟಕಿ->floating.w);
                ಎತ್ತರ = wind->requested.logical_ಎತ್ತರ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಕಿಟಕಿ->floating.h);
            }

            OverrideLibdecorLimits(ಕಿಟಕಿ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            /* XXX: The libdecor cairo plugin sends bogus content sizes that add the
             *      height of the title bar when transitioning from a fixed-size to
             *      floating state. Ignore the sent window dimensions in this case,
             *      in favor of the cached value to avoid the window increasing in
             *      size after every state transition.
             *
             *      https://gitlab.freedesktop.org/libdecor/libdecor/-/issues/34
             */
            ಆದರೆ ((floating && (!wind->floating && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS))) ||
                !libdecor_configuration_get_content_ಗಾತ್ರ(configuration, ಚೌಕಟ್ಟು, &ಅಗಲ, &ಎತ್ತರ)) {
                ಅಗಲ = 0;
                ಎತ್ತರ = 0;
            }

            ಸ್ಥಿರಾಂಕ bool new_configure_ಗಾತ್ರ = ಅಗಲ != wind->ಕೊನೆಯ_configure.ಅಗಲ || ಎತ್ತರ != wind->ಕೊನೆಯ_configure.ಎತ್ತರ;
            DetermineResizeAxis(wind, ಅಗಲ, ಎತ್ತರ, resizing);

            ಆದರೆ (!ಅಗಲ) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                ಆದರೆ (floating) {
                    ಅಗಲ = ಕಿಟಕಿ->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ಆದರೆ (wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE && wind->toplevel_bounds.ಅಗಲ) {
                        ಅಗಲ = SDL_min(wind->toplevel_bounds.ಅಗಲ, ಅಗಲ);
                    }
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಅಗಲ = ಕಿಟಕಿ->windowed.w;
                }

                ಆದರೆ (!wind->scale_ಗಮ್ಯ_display) {
                    wind->requested.logical_ಅಗಲ = ಅಗಲ;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    wind->requested.pixel_ಅಗಲ = ಅಗಲ;
                    ಅಗಲ = wind->requested.logical_ಅಗಲ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಅಗಲ);
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                ಆದರೆ (new_configure_ಗಾತ್ರ &&
                    !(wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_ಚೌಕಟ್ಟು && wind->suspended != suspended)) {
                    wind->requested.logical_ಅಗಲ = ಅಗಲ;

                    ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
                        wind->requested.pixel_ಅಗಲ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ, ಅಗಲ);
                    }
                }
            }

            ಆದರೆ (!ಎತ್ತರ) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                ಆದರೆ (floating) {
                    ಎತ್ತರ = ಕಿಟಕಿ->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ಆದರೆ (wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE && wind->toplevel_bounds.ಎತ್ತರ) {
                        ಎತ್ತರ = SDL_min(wind->toplevel_bounds.ಎತ್ತರ, ಎತ್ತರ);
                    }
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಎತ್ತರ = ಕಿಟಕಿ->windowed.h;
                }

                ಆದರೆ (!wind->scale_ಗಮ್ಯ_display) {
                    wind->requested.logical_ಎತ್ತರ = ಎತ್ತರ;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    wind->requested.pixel_ಎತ್ತರ = ಎತ್ತರ;
                    ಎತ್ತರ = wind->requested.logical_ಎತ್ತರ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಎತ್ತರ);
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                ಆದರೆ (new_configure_ಗಾತ್ರ &&
                    !(wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_ಚೌಕಟ್ಟು && wind->suspended != suspended)) {
                    wind->requested.logical_ಎತ್ತರ = ಎತ್ತರ;

                    ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
                        wind->requested.pixel_ಎತ್ತರ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ, ಎತ್ತರ);
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
        ಆದರೆ (floating) {
            ಆದರೆ (!wind->scale_ಗಮ್ಯ_display) {
                ApplyGeometryLimits(ಕಿಟಕಿ, wind->requested.logical_ಅಗಲ, wind->requested.logical_ಎತ್ತರ, &wind->requested.logical_ಅಗಲ, &wind->requested.logical_ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ApplyGeometryLimits(ಕಿಟಕಿ, wind->requested.pixel_ಅಗಲ, wind->requested.pixel_ಎತ್ತರ, &wind->requested.pixel_ಅಗಲ, &wind->requested.pixel_ಎತ್ತರ);

                wind->requested.logical_ಅಗಲ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, wind->requested.pixel_ಅಗಲ);
                wind->requested.logical_ಎತ್ತರ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, wind->requested.pixel_ಎತ್ತರ);
            }
        }
    }

    // Store the new state.
    ಸ್ಥಿರಾಂಕ bool started_resize = !wind->resizing && resizing;
    wind->ಕೊನೆಯ_configure.ಅಗಲ = ಅಗಲ;
    wind->ಕೊನೆಯ_configure.ಎತ್ತರ = ಎತ್ತರ;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->ಸಕ್ರಿಯ = ಸಕ್ರಿಯ;
    ಕಿಟಕಿ->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#ಆದರೆ SDL_LIBDECOR_CHECK_ಆವೃತ್ತಿ(0, 3, 0)
    ಎಣಿಕೆ libdecor_wm_capabilities caps;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    ಆದರೆ (libdecor_ಚೌಕಟ್ಟು_get_wm_capabilities) {
        caps = libdecor_ಚೌಕಟ್ಟು_get_wm_capabilities(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು);
#ಇಲ್ಲದಿದ್ದರೆ
    caps = libdecor_ಚೌಕಟ್ಟು_get_wm_capabilities(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು);
    {
#ಆದರೆ_ಅಂತ್ಯ
        wind->wm_caps = 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_ಕಿಟಕಿ_MENU ? WAYLAND_WM_CAPS_ಕಿಟಕಿ_MENU : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MAXIMIZE ? WAYLAND_WM_CAPS_MAXIMIZE : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_FULLSCREEN ? WAYLAND_WM_CAPS_FULLSCREEN : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MINIMIZE ? WAYLAND_WM_CAPS_MINIMIZE : 0;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        Configure_ಕಿಟಕಿ_Geometry(ಕಿಟಕಿ);
        ರಚನೆ libdecor_state *state = libdecor_state_new(wind->current.logical_ಅಗಲ, wind->current.logical_ಎತ್ತರ);
        libdecor_ಚೌಕಟ್ಟು_commit(ಚೌಕಟ್ಟು, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        ಆದರೆ (started_resize) {
            SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_EXPOSED, 0, 0);
        }
    }

    ಆದರೆ (wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE) {
        wind->shell_surface_ಸ್ಥಿತಿ = WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_ಚೌಕಟ್ಟು;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ decoration_ಚೌಕಟ್ಟು_close(ರಚನೆ libdecor_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ_2)
{
    SDL_Send_ಕಿಟಕಿ_Event(((SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)user_ದತ್ತಾಂಶ_2)->sdlwindow, SDL_EVENT_ಕಿಟಕಿ_CLOSE_REQUESTED, 0, 0);
}

ಸ್ಥಿರ ಶೂನ್ಯ decoration_ಚೌಕಟ್ಟು_commit(ರಚನೆ libdecor_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ_2)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)user_ದತ್ತಾಂಶ_2;
    ಆದರೆ (!wind->suspended && wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN) {
        SDL_Send_ಕಿಟಕಿ_Event(wind->sdlwindow, SDL_EVENT_ಕಿಟಕಿ_EXPOSED, 0, 0);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ decoration_dismiss_popup(ರಚನೆ libdecor_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *seat_name, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ_2)
{
    // NOP
}

#ಆದರೆ SDL_LIBDECOR_CHECK_ಆವೃತ್ತಿ(0, 3, 0)
ಸ್ಥಿರ ಶೂನ್ಯ decoration_ಚೌಕಟ್ಟು_bounds(ರಚನೆ libdecor_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು, ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, ಶೂನ್ಯ *user_ದತ್ತಾಂಶ_2)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)user_ದತ್ತಾಂಶ_2;
    ಕಿಟಕಿ->toplevel_bounds.ಅಗಲ = ಅಗಲ;
    ಕಿಟಕಿ->toplevel_bounds.ಎತ್ತರ = ಎತ್ತರ;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ರಚನೆ libdecor_ಚೌಕಟ್ಟು_interface libdecor_ಚೌಕಟ್ಟು_interface = {
    decoration_ಚೌಕಟ್ಟು_configure,
    decoration_ಚೌಕಟ್ಟು_close,
    decoration_ಚೌಕಟ್ಟು_commit,
    decoration_dismiss_popup,
#ಆದರೆ SDL_LIBDECOR_CHECK_ಆವೃತ್ತಿ(0, 3, 0)
    decoration_ಚೌಕಟ್ಟು_bounds
#ಆದರೆ_ಅಂತ್ಯ
};
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Handle_Preferred_Scale_ಬದಲಾಯಿತು(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ_ದತ್ತಾಂಶ_2, ದ್ವಿಗುಣ ಗುಣಕ)
{
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ old_ಗುಣಕ = ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->scale_ಗುಣಕ_2;

    // Round the scale factor if viewports aren't available.
    ಆದರೆ (!ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->viewport) {
        ಗುಣಕ = SDL_ceil(ಗುಣಕ);
    }

    ಆದರೆ (ಗುಣಕ != old_ಗುಣಕ) {
        ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->scale_ಗುಣಕ_2 = ಗುಣಕ;

        ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->scale_ಗಮ್ಯ_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->floating) {
                /* Some compositors will send a configure event immediately after a scale event, however,
                 * this event can contain the old logical size, and should be ignored, or the window can
                 * incorrectly change size when moved between displays with differing scale factors.
                 *
                 * Store the last requested logical size as the last configure size, so a configure event
                 * with the old size will be ignored. Configure sizes are in window geometry space,
                 * so subtract any border insets.
                 */
                BorderInsets insets;
                GetBorderInsets(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, &insets);
                ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕೊನೆಯ_configure.ಅಗಲ = SDL_max(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->requested.logical_ಅಗಲ - (insets.ಎಡ + insets.ಬಲ), 1);
                ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->ಕೊನೆಯ_configure.ಎತ್ತರ = SDL_max(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->requested.logical_ಎತ್ತರ - (insets.ತುದಿ + insets.bottom), 1);

                ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->requested.logical_ಅಗಲ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->requested.pixel_ಅಗಲ);
                ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->requested.logical_ಎತ್ತರ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->requested.pixel_ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->requested.pixel_ಅಗಲ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->requested.logical_ಅಗಲ);
                ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->requested.pixel_ಎತ್ತರ = ಬಿಂದು_ಗಮ್ಯ_Pixel(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow, ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->requested.logical_ಎತ್ತರ);
            }
        }

        ಆದರೆ (ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow->flags & SDL_ಕಿಟಕಿ_ಮೇಲಿನ_PIXEL_DENSITY || ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->scale_ಗಮ್ಯ_display) {
            Configure_ಕಿಟಕಿ_Geometry(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow);
            Commit_Libdecor_ಚೌಕಟ್ಟು(ಕಿಟಕಿ_ದತ್ತಾಂಶ_2->sdlwindow);
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_Maybe_Update_Scale_ಗುಣಕ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ)
{
    ದ್ವಿಗುಣ ಗುಣಕ;
    ಪೂರ್ಣಾಂಕ i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    ಆದರೆ (ಕಿಟಕಿ->fractional_scale || wl_surface_get_ಆವೃತ್ತಿ(ಕಿಟಕಿ->surface) >= WL_SURFACE_PREFERRED_ಬಫರ್_SCALE_SINCE_ಆವೃತ್ತಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (ಕಿಟಕಿ->ಅಂಕೆ_outputs != 0) {
        // Check every display's factor, use the highest
        ಗುಣಕ = 0.0;
        ಗಾಗಿ (i = 0; i < ಕಿಟಕಿ->ಅಂಕೆ_outputs; i++) {
            SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = ಕಿಟಕಿ->outputs[i];
            ಗುಣಕ = SDL_max(ಗುಣಕ, ಆಂತರಿಕ->scale_ಗುಣಕ_2);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // All outputs removed, just fall back.
        ಗುಣಕ = ಕಿಟಕಿ->scale_ಗುಣಕ_2;
    }

    Wayland_Handle_Preferred_Scale_ಬದಲಾಯಿತು(ಕಿಟಕಿ, ಗುಣಕ);
}

ಶೂನ್ಯ Wayland_Remove_Output_From_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ, SDL_Display_ದತ್ತಾಂಶ *display_ದತ್ತಾಂಶ)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಕಿಟಕಿ->ಅಂಕೆ_outputs; i++) {
        ಆದರೆ (ಕಿಟಕಿ->outputs[i] == display_ದತ್ತಾಂಶ) { // remove this one
            ಆದರೆ (i == (ಕಿಟಕಿ->ಅಂಕೆ_outputs - 1)) {
                ಕಿಟಕಿ->outputs[i] = ಖಾಲಿ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                SDL_memmove(&ಕಿಟಕಿ->outputs[i],
                            &ಕಿಟಕಿ->outputs[i + 1],
                            ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ *) * ((ಕಿಟಕಿ->ಅಂಕೆ_outputs - i) - 1));
            }
            ಕಿಟಕಿ->ಅಂಕೆ_outputs--;
            i--;
        }
    }

    ಆದರೆ (ಕಿಟಕಿ->ಅಂಕೆ_outputs == 0) {
        SDL_free(ಕಿಟಕಿ->outputs);
        ಕಿಟಕಿ->outputs = ಖಾಲಿ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ಕಿಟಕಿ->is_fullscreen || ಕಿಟಕಿ->ಅಂಕೆ_outputs == 1) {
        Wayland_Update_ಕಿಟಕಿ_Position(ಕಿಟಕಿ->sdlwindow);
        Wayland_Maybe_Update_Scale_ಗುಣಕ(ಕಿಟಕಿ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_surface_enter(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_surface *surface, ರಚನೆ wl_output *output)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = ದತ್ತಾಂಶ;
    SDL_Display_ದತ್ತಾಂಶ *ಆಂತರಿಕ = wl_output_get_user_ದತ್ತಾಂಶ(output);
    SDL_Display_ದತ್ತಾಂಶ **new_outputs;

    ಆದರೆ (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        ಹಿಂತಿರುಗಿ;
    }

    new_outputs = SDL_realloc(ಕಿಟಕಿ->outputs,
                              ಗಾತ್ರ(SDL_Display_ದತ್ತಾಂಶ *) * (ಕಿಟಕಿ->ಅಂಕೆ_outputs + 1));
    ಆದರೆ (!new_outputs) {
        ಹಿಂತಿರುಗಿ;
    }
    ಕಿಟಕಿ->outputs = new_outputs;
    ಕಿಟಕಿ->outputs[ಕಿಟಕಿ->ಅಂಕೆ_outputs++] = ಆಂತರಿಕ;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    ಆದರೆ (!ಕಿಟಕಿ->is_fullscreen || ಕಿಟಕಿ->ಅಂಕೆ_outputs == 1) {
        Wayland_Update_ಕಿಟಕಿ_Position(ಕಿಟಕಿ->sdlwindow);
        Wayland_Maybe_Update_Scale_ಗುಣಕ(ಕಿಟಕಿ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_surface_leave(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_surface *surface, ರಚನೆ wl_output *output)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;

    ಆದರೆ (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        ಹಿಂತಿರುಗಿ;
    }

    Wayland_Remove_Output_From_ಕಿಟಕಿ(ಕಿಟಕಿ, (SDL_Display_ದತ್ತಾಂಶ *)wl_output_get_user_ದತ್ತಾಂಶ(output));
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_surface_preferred_ಬಫರ್_scale(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_surface *wl_surface, int32_t ಗುಣಕ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ದತ್ತಾಂಶ;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    ಆದರೆ (!wind->fractional_scale) {
        Wayland_Handle_Preferred_Scale_ಬದಲಾಯಿತು(ದತ್ತಾಂಶ, (ದ್ವಿಗುಣ)ಗುಣಕ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_surface_preferred_ಬಫರ್_transform(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_surface *wl_surface, uint32_t transform)
{
    // Nothing to do here.
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_surface_listener surface_listener = {
    handle_surface_enter,
    handle_surface_leave,
    handle_surface_preferred_ಬಫರ್_scale,
    handle_surface_preferred_ಬಫರ್_transform
};

ಸ್ಥಿರ ಶೂನ್ಯ handle_fractional_scale_preferred(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wp_fractional_scale_v1 *wp_fractional_scale_v1, uint32_t scale)
{
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ ಗುಣಕ = (ದ್ವಿಗುಣ)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_Handle_Preferred_Scale_ಬದಲಾಯಿತು(ದತ್ತಾಂಶ, ಗುಣಕ);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

ಸ್ಥಿರ ಶೂನ್ಯ frog_preferred_metadata_handler(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
                                            uint32_t output_display_primary_red_x, uint32_t output_display_primary_red_y,
                                            uint32_t output_display_primary_green_x, uint32_t output_display_primary_green_y,
                                            uint32_t output_display_primary_blue_x, uint32_t output_display_primary_blue_y,
                                            uint32_t output_white_ಬಿಂದು_x, uint32_t output_white_ಬಿಂದು_y,
                                            uint32_t max_luminance, uint32_t min_luminance,
                                            uint32_t max_ತುಂಬಿದ_ಚೌಕಟ್ಟು_luminance)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    SDL_HDROutputProperties HDR;

    SDL_zero(HDR);

    ಆಯ್ಕೆ (transfer_function) {
    ಸ್ಥಿತಿ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_ST2084_PQ:
        /* ITU-R BT.2408-7 (Sept 2023) has the reference PQ white level at 203 nits,
         * while older Dolby documentation claims a reference level of 100 nits.
         *
         * Use 203 nits for now.
         */
        HDR.HDR_headroom = max_luminance / 203.0f;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SCRGB_ರೇಖೀಯ:
        HDR.HDR_headroom = max_luminance / 80.0f;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_UNDEFINED:
    ಸ್ಥಿತಿ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SRGB:
    ಸ್ಥಿತಿ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_GAMMA_22:
    ಪೂರ್ವನಿಯೋಜಿತ:
        HDR.HDR_headroom = 1.0f;
        ನಿಲ್ಲಿಸು;
    }

    HDR.SDR_white_level = 1.0f;
    SDL_ಗಣ_ಕಿಟಕಿ_HDRProperties(wind->sdlwindow, &HDR, true);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


ಸ್ಥಿರ ಶೂನ್ಯ handle_surface_feedback_preferred_changed2(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                       ರಚನೆ wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t ತಟಸ್ಥ_hi, uint32_t ತಟಸ್ಥ_lo)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    Wayland_Get_Color_Info_For_ಕಿಟಕಿ(wind, false);
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_surface_feedback_preferred_ಬದಲಾಯಿತು(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                                      ರಚನೆ wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t ತಟಸ್ಥ)
{
    handle_surface_feedback_preferred_changed2(ದತ್ತಾಂಶ, wp_color_management_surface_feedback_v1, 0, ತಟಸ್ಥ);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_ಬದಲಾಯಿತು,
    handle_surface_feedback_preferred_changed2
};

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_ಗಣ_Keyboard_Focus(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool ಗಣ_focus)
{
    SDL_ಕಿಟಕಿ *toplevel = ಕಿಟಕಿ;

    // Find the toplevel parent
    ಆಗ (SDL_ಕಿಟಕಿ_IS_POPUP(toplevel)) {
        toplevel = toplevel->ಪೋಷಕ;
    }

    toplevel->keyboard_focus = ಕಿಟಕಿ;

    ಆದರೆ (ಗಣ_focus && !ಕಿಟಕಿ->is_hiding && !ಕಿಟಕಿ->is_destroying) {
        SDL_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ);
    }
}

bool Wayland_ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool enabled)
{
    ಹಿಂತಿರುಗಿ true; // just succeed, the real work is done elsewhere.
}

ಸ್ಥಿರ ರಚನೆ xdg_toplevel *Get_Toplevel_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind)
{
    ಆದರೆ (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
        ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
            ಹಿಂತಿರುಗಿ libdecor_ಚೌಕಟ್ಟು_get_xdg_toplevel(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು);
        } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
            ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                ಹಿಂತಿರುಗಿ wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

bool Wayland_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ_ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಮಗು_ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಪೋಷಕ_ದತ್ತಾಂಶ = ಪೋಷಕ_ಕಿಟಕಿ ? ಪೋಷಕ_ಕಿಟಕಿ->ಆಂತರಿಕ : ಖಾಲಿ;

    ಮಗು_ದತ್ತಾಂಶ->reparenting_required = false;

    ಆದರೆ (ಪೋಷಕ_ದತ್ತಾಂಶ && ಪೋಷಕ_ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ != WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        ಮಗು_ದತ್ತಾಂಶ->reparenting_required = true;
        ಹಿಂತಿರುಗಿ true;
    }

    ರಚನೆ xdg_toplevel *ಮಗು_toplevel = Get_Toplevel_For_ಕಿಟಕಿ(ಮಗು_ದತ್ತಾಂಶ);
    ರಚನೆ xdg_toplevel *ಪೋಷಕ_toplevel = Get_Toplevel_For_ಕಿಟಕಿ(ಪೋಷಕ_ದತ್ತಾಂಶ);

    ಆದರೆ (ಮಗು_toplevel) {
        xdg_toplevel_ಗಣ_ಪೋಷಕ(ಮಗು_toplevel, ಪೋಷಕ_toplevel);
    }

    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_ಗಣ_ಕಿಟಕಿ_Modal(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool modal)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಪೋಷಕ_ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಪೋಷಕ->ಆಂತರಿಕ;

    ಆದರೆ (ಪೋಷಕ_ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ != WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        ದತ್ತಾಂಶ->reparenting_required = true;
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->reparenting_required = false;
    }

    ರಚನೆ xdg_toplevel *toplevel = Get_Toplevel_For_ಕಿಟಕಿ(ದತ್ತಾಂಶ);

    ಆದರೆ (toplevel) {
        ಆದರೆ (viddata->xdg_wm_dialog_v1) {
            ಆದರೆ (modal) {
                ಆದರೆ (!ದತ್ತಾಂಶ->xdg_dialog_v1) {
                    ದತ್ತಾಂಶ->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_ಗಣ_modal(ದತ್ತಾಂಶ->xdg_dialog_v1);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(ದತ್ತಾಂಶ->xdg_dialog_v1);
            }
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_ರಿಜಿಸ್ಟರ್_Toplevel_For_Session(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    ರಚನೆ xdg_toplevel *toplevel = Get_Toplevel_For_ಕಿಟಕಿ(ದತ್ತಾಂಶ);
    ಆದರೆ (!toplevel) {
        ಹಿಂತಿರುಗಿ;
    }

    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *id = SDL_GetStringProperty(ದತ್ತಾಂಶ->sdlwindow->props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_ಕಿಟಕಿ_ID_STRING, ಖಾಲಿ);
    ಆದರೆ (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_Video_ದತ್ತಾಂಶ *viddata = viddev->ಆಂತರಿಕ;

        ಆದರೆ (viddata->xdg_toplevel_ಟ್ಯಾಗ್_manager) {
            xdg_toplevel_ಟ್ಯಾಗ್_manager_v1_ಗಣ_toplevel_ಟ್ಯಾಗ್(viddata->xdg_toplevel_ಟ್ಯಾಗ್_manager, toplevel, id);
        }

        ಆದರೆ (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            ಆದರೆ (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    ಗಾಗಿ (SDL_ಕಿಟಕಿ *w = viddev->windows; w; w = w->ಮುಂದಿನ) {
                        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *d = w->ಆಂತರಿಕ;
                        ಆದರೆ (d->session_id && SDL_strcmp(d->session_id, id) == 0) {
                            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Duplicate window ID string %s found; window will not be added to session", id);
                            ಹಿಂತಿರುಗಿ;
                        }
                    }
                }

                ದತ್ತಾಂಶ->xdg_toplevel_session = xdg_session_v1_restore_toplevel(viddata->xdg_session, toplevel, id);
                ದತ್ತಾಂಶ->session_id = SDL_strdup(id);
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_DestroyToplevelSession(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ;

    ಆದರೆ (ದತ್ತಾಂಶ->xdg_toplevel_session) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *id = SDL_GetStringProperty(ದತ್ತಾಂಶ->sdlwindow->props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_ಕಿಟಕಿ_ID_STRING, ಖಾಲಿ);

        // If the ID string was cleared, remove the window from the session.
        ಆದರೆ (!id || *id == '\0') {
            xdg_session_v1_remove_toplevel(viddata->xdg_session, ದತ್ತಾಂಶ->session_id);
        }

        xdg_toplevel_session_v1_destroy(ದತ್ತಾಂಶ->xdg_toplevel_session);
        ದತ್ತಾಂಶ->xdg_toplevel_session = ಖಾಲಿ;

        SDL_free(ದತ್ತಾಂಶ->session_id);
        ದತ್ತಾಂಶ->session_id = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ show_hide_sync_handler(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_callback *callback, uint32_t callback_ದತ್ತಾಂಶ)
{
    // Get the window from the ID as it may have been destroyed
    SDL_ಕಿಟಕಿ_ID ಕಿಟಕಿ_ID = (SDL_ಕಿಟಕಿ_ID)((uintptr_t)ದತ್ತಾಂಶ);
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = SDL_Get_ಕಿಟಕಿ_From_ID(ಕಿಟಕಿ_ID);

    ಆದರೆ (ಕಿಟಕಿ && ಕಿಟಕಿ->ಆಂತರಿಕ) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

ಸ್ಥಿರ ರಚನೆ wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

ಸ್ಥಿರ ಶೂನ್ಯ exported_handle_handler(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ zxdg_exported_v2 *zxdg_exported_v2, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *handle)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = (SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *)ದತ್ತಾಂಶ;
    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(wind->sdlwindow);

    SDL_ಗಣ_String_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

ಸ್ಥಿರ ರಚನೆ zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

ಶೂನ್ಯ Wayland_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *c = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);

    // Custom surfaces don't get toplevels and are always considered 'shown'; nothing to do here.
    ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        ಹಿಂತಿರುಗಿ;
    }

    /* If this is a child window, the parent *must* be in the final shown state,
     * meaning that it has received a configure event, followed by a frame callback.
     * If not, a race condition can result, with effects ranging from the child
     * window to spuriously closing to protocol errors.
     *
     * If waiting on the parent window, set the pending status and the window will
     * be shown when the parent is in the shown state.
     */
    ಆದರೆ (ಕಿಟಕಿ->ಪೋಷಕ) {
        ಆದರೆ (ಕಿಟಕಿ->ಪೋಷಕ->ಆಂತರಿಕ->shell_surface_ಸ್ಥಿತಿ != WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN) {
            ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ = WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOW_PENDING;
            ಹಿಂತಿರುಗಿ;
        }
    }

    // Always roundtrip to ensure there are no pending buffer attachments.
    ಮಾಡು {
        WAYLAND_wl_display_roundtrip(c->display);
    } ಆಗ (ದತ್ತಾಂಶ->show_hide_sync_required);

    ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ = WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE;

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
    wl_surface_attach(ದತ್ತಾಂಶ->surface, ಖಾಲಿ, 0, 0);
    wl_surface_commit(ದತ್ತಾಂಶ->surface);

    // Create the shell surface and map the toplevel/popup
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ದತ್ತಾಂಶ->shell_surface.libdecor.ಚೌಕಟ್ಟು = libdecor_decorate(c->shell.libdecor,
                                                               ದತ್ತಾಂಶ->surface,
                                                               &libdecor_ಚೌಕಟ್ಟು_interface,
                                                               ದತ್ತಾಂಶ);
        ಆದರೆ (!ದತ್ತಾಂಶ->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } ಇಲ್ಲದಿದ್ದರೆ {
            libdecor_ಚೌಕಟ್ಟು_ಗಣ_app_id(ದತ್ತಾಂಶ->shell_surface.libdecor.ಚೌಕಟ್ಟು, ದತ್ತಾಂಶ->app_id);
            libdecor_ಚೌಕಟ್ಟು_map(ದತ್ತಾಂಶ->shell_surface.libdecor.ಚೌಕಟ್ಟು);
            ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_ಚೌಕಟ್ಟು_ಗಣ_visibility(ದತ್ತಾಂಶ->shell_surface.libdecor.ಚೌಕಟ್ಟು, false);
            }

            ಆದರೆ (c->zxdg_exporter_v2) {
                ದತ್ತಾಂಶ->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, ದತ್ತಾಂಶ->surface);
                zxdg_exported_v2_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->exported, &exported_v2_listener, ದತ್ತಾಂಶ);
            }

            ಆದರೆ (c->xdg_toplevel_icon_manager_v1 && ದತ್ತಾಂಶ->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_ಗಣ_icon(_this->ಆಂತರಿಕ->xdg_toplevel_icon_manager_v1,
                                                      libdecor_ಚೌಕಟ್ಟು_get_xdg_toplevel(ದತ್ತಾಂಶ->shell_surface.libdecor.ಚೌಕಟ್ಟು),
                                                      ದತ್ತಾಂಶ->xdg_toplevel_icon_v1);
            }

            SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_SURFACE_ಸೂಚಕ, libdecor_ಚೌಕಟ್ಟು_get_xdg_surface(ದತ್ತಾಂಶ->shell_surface.libdecor.ಚೌಕಟ್ಟು));
            SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_TOPLEVEL_ಸೂಚಕ, libdecor_ಚೌಕಟ್ಟು_get_xdg_toplevel(ದತ್ತಾಂಶ->shell_surface.libdecor.ಚೌಕಟ್ಟು));
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        ದತ್ತಾಂಶ->shell_surface.xdg.surface = xdg_wm_ತಳ_get_xdg_surface(c->shell.xdg, ದತ್ತಾಂಶ->surface);
        xdg_surface_ಗಣ_user_ದತ್ತಾಂಶ(ದತ್ತಾಂಶ->shell_surface.xdg.surface, ದತ್ತಾಂಶ);
        xdg_surface_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->shell_surface.xdg.surface, &_xdg_surface_listener, ದತ್ತಾಂಶ);
        SDL_ಗಣ_ಸೂಚಕ_Property(SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ), SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_SURFACE_ಸೂಚಕ, ದತ್ತಾಂಶ->shell_surface.xdg.surface);

        ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_ಕಿಟಕಿ *ಪೋಷಕ = ಕಿಟಕಿ->ಪೋಷಕ;
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಪೋಷಕ_ದತ್ತಾಂಶ = ಪೋಷಕ->ಆಂತರಿಕ;
            ರಚನೆ xdg_surface *ಪೋಷಕ_xdg_surface = ಖಾಲಿ;
            ಪೂರ್ಣಾಂಕ position_x = 0, position_y = 0;

            // Configure the popup parameters
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
            ಆದರೆ (ಪೋಷಕ_ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                ಪೋಷಕ_xdg_surface = libdecor_ಚೌಕಟ್ಟು_get_xdg_surface(ಪೋಷಕ_ದತ್ತಾಂಶ->shell_surface.libdecor.ಚೌಕಟ್ಟು);
            } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
            ಆದರೆ (ಪೋಷಕ_ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    ಪೋಷಕ_ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                ಪೋಷಕ_xdg_surface = ಪೋಷಕ_ದತ್ತಾಂಶ->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_positioner = xdg_wm_ತಳ_create_positioner(c->shell.xdg);
            xdg_positioner_ಗಣ_anchor(ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_ತುದಿ_ಎಡ);
            SDL_Rect ಪೋಷಕ_geometry;
            Get_ಕಿಟಕಿ_Geometry(ಪೋಷಕ->ಆಂತರಿಕ, &ಪೋಷಕ_geometry);
            xdg_positioner_ಗಣ_anchor_rect(ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_positioner, 0, 0, ಪೋಷಕ_geometry.w, ಪೋಷಕ_geometry.h);

            ಸ್ಥಿರಾಂಕ Uint32 constraint = ಕಿಟಕಿ->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_ಗಣ_constraint_adjustment(ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_ಗಣ_gravity(ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_ಬಲ);
            xdg_positioner_ಗಣ_ಗಾತ್ರ(ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_positioner, ದತ್ತಾಂಶ->current.logical_ಅಗಲ, ದತ್ತಾಂಶ->current.logical_ಎತ್ತರ);

            // Set the popup initial position
            position_x = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending ? ಕಿಟಕಿ->pending.x : ಕಿಟಕಿ->x;
            position_y = ಕಿಟಕಿ->ಕೊನೆಯ_position_pending ? ಕಿಟಕಿ->pending.y : ಕಿಟಕಿ->y;
            EnsurePopupPositionIsValid(ಕಿಟಕಿ, &position_x, &position_y);
            ಆದರೆ (ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display) {
                position_x = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ->ಪೋಷಕ, position_x);
                position_y = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ->ಪೋಷಕ, position_y);
            }
            Adjust_Popup_ಸ್ಥಾನಾಂತರ(ಕಿಟಕಿ, &position_x, &position_y);
            xdg_positioner_ಗಣ_ಸ್ಥಾನಾಂತರ(ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_positioner, position_x, position_y);

            // Assign the popup role
            ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_popup = xdg_surface_get_popup(ದತ್ತಾಂಶ->shell_surface.xdg.surface,
                                                                                ಪೋಷಕ_xdg_surface,
                                                                                ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_positioner);
            xdg_popup_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_popup, &_xdg_popup_listener, ದತ್ತಾಂಶ);

            ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TOOLTIP) {
                ರಚನೆ wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_ಕೂಡಿಸು(region, 0, 0, 0, 0);
                wl_surface_ಗಣ_ಒಳಹರಿವು_region(ದತ್ತಾಂಶ->surface, region);
                wl_region_destroy(region);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE)) {
                Wayland_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ, true);
            }

            SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_POPUP_ಸೂಚಕ, ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_popup);
            SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_POSITIONER_ಸೂಚಕ, ದತ್ತಾಂಶ->shell_surface.xdg.popup.xdg_positioner);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ದತ್ತಾಂಶ->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(ದತ್ತಾಂಶ->shell_surface.xdg.surface);
            xdg_toplevel_ಗಣ_app_id(ದತ್ತಾಂಶ->shell_surface.xdg.toplevel.xdg_toplevel, ದತ್ತಾಂಶ->app_id);
            xdg_toplevel_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, ದತ್ತಾಂಶ);

            // Create the window decorations
            ಆದರೆ (c->decoration_manager) {
                ದತ್ತಾಂಶ->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, ದತ್ತಾಂಶ->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->server_decoration, &xdg_toplevel_decoration_listener, ಕಿಟಕಿ);
                ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ zxdg_toplevel_decoration_v1_ಬಹುಲಕ ಬಹುಲಕ = !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_ಬಹುಲಕ_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_ಬಹುಲಕ_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_ಗಣ_ಬಹುಲಕ(ದತ್ತಾಂಶ->server_decoration, ಬಹುಲಕ);
            }

            ಆದರೆ (c->zxdg_exporter_v2) {
                ದತ್ತಾಂಶ->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, ದತ್ತಾಂಶ->surface);
                zxdg_exported_v2_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->exported, &exported_v2_listener, ದತ್ತಾಂಶ);
            }

            ಆದರೆ (c->xdg_toplevel_icon_manager_v1 && ದತ್ತಾಂಶ->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_ಗಣ_icon(_this->ಆಂತರಿಕ->xdg_toplevel_icon_manager_v1,
                                                      ದತ್ತಾಂಶ->shell_surface.xdg.toplevel.xdg_toplevel,
                                                      ದತ್ತಾಂಶ->xdg_toplevel_icon_v1);
            }

            SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_TOPLEVEL_ಸೂಚಕ, ದತ್ತಾಂಶ->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    // Restore state that was set prior to this call
    Wayland_ರಿಜಿಸ್ಟರ್_Toplevel_For_Session(ದತ್ತಾಂಶ);
    Wayland_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(_this, ಕಿಟಕಿ, ಕಿಟಕಿ->ಪೋಷಕ);

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MODAL) {
        Wayland_ಗಣ_ಕಿಟಕಿ_Modal(_this, ಕಿಟಕಿ, true);
    }

    Wayland_ಗಣ_ಕಿಟಕಿ_Title(_this, ಕಿಟಕಿ);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ಆದರೆ (ದತ್ತಾಂಶ->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
            ಆಗ (ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE) {
                ಆದರೆ (libdecor_dispatch(c->shell.libdecor, -1) < 0) {
                    ಆದರೆ (!Wayland_HandleDisplayDisconnected(_this)) {
                        ಹಿಂತಿರುಗಿ;
                    }
                }
                ಆದರೆ (WAYLAND_wl_display_dispatch_pending(c->display) < 0) {
                    ಆದರೆ (!Wayland_HandleDisplayDisconnected(_this)) {
                        ಹಿಂತಿರುಗಿ;
                    }
                }
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP || ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Unlike libdecor we need to call this explicitly to prevent a deadlock.
         * libdecor will call this as part of their configure event!
         * -flibit
         */
        wl_surface_commit(ದತ್ತಾಂಶ->surface);
        ಆದರೆ (ದತ್ತಾಂಶ->shell_surface.xdg.surface) {
            ಆಗ (ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE) {
                ಆದರೆ (WAYLAND_wl_display_dispatch(c->display) < 0) {
                    ಆದರೆ (!Wayland_HandleDisplayDisconnected(_this)) {
                        ಹಿಂತಿರುಗಿ;
                    }
                }
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Nothing to see here, just commit.
        wl_surface_commit(ದತ್ತಾಂಶ->surface);
    }

    // Make sure the window can't be resized to 0, or it can be spuriously closed by the window manager.
    ದತ್ತಾಂಶ->system_limits.min_ಅಗಲ_2 = SDL_max(ದತ್ತಾಂಶ->system_limits.min_ಅಗಲ_2, 1);
    ದತ್ತಾಂಶ->system_limits.min_ಎತ್ತರ_2 = SDL_max(ದತ್ತಾಂಶ->system_limits.min_ಎತ್ತರ_2, 1);

    /* Unlike the rest of window state we have to set this _after_ flushing the
     * display, because we need to create the decorations before possibly hiding
     * them immediately afterward.
     */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        ಆದರೆ (ಕಿಟಕಿ->windowed.w < ದತ್ತಾಂಶ->system_limits.min_ಅಗಲ_2 ||
            ಕಿಟಕಿ->windowed.h < ದತ್ತಾಂಶ->system_limits.min_ಎತ್ತರ_2) {

            // Warn if the window frame will be larger than the content surface.
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "Window dimensions (%i, %i) are smaller than the system enforced minimum (%i, %i); window borders will be larger than the content surface.",
                        ಕಿಟಕಿ->windowed.w, ಕಿಟಕಿ->windowed.h, ದತ್ತಾಂಶ->system_limits.min_ಅಗಲ_2, ದತ್ತಾಂಶ->system_limits.min_ಎತ್ತರ_2);

            ದತ್ತಾಂಶ->current.logical_ಅಗಲ = SDL_max(ಕಿಟಕಿ->windowed.w, ದತ್ತಾಂಶ->system_limits.min_ಅಗಲ_2);
            ದತ್ತಾಂಶ->current.logical_ಎತ್ತರ = SDL_max(ಕಿಟಕಿ->windowed.h, ದತ್ತಾಂಶ->system_limits.min_ಎತ್ತರ_2);
            Commit_Libdecor_ಚೌಕಟ್ಟು(ಕಿಟಕಿ);
        }
    }
#ಆದರೆ_ಅಂತ್ಯ
    Wayland_ಗಣ_ಕಿಟಕಿ_Resizable(_this, ಕಿಟಕಿ, !!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE));

    // We're finally done putting the window together, raise if possible
    ಆದರೆ (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_ಕಿಟಕಿ_ACTIVATE_WHEN_SHOWN, true)) {
        /* if the process was passed an activation token, use it when showing
         * the initial window.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
        ಆದರೆ (activation_token) {
            xdg_activation_v1_activate(c->activation_manager,
                                       activation_token,
                                       ದತ್ತಾಂಶ->surface);

            // Clear this variable, per the protocol's request
            SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Try to generate an activation token for this window.
            Wayland_Raise_ಕಿಟಕಿ(_this, ಕಿಟಕಿ);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Clear the ignored activation token, as it won't be used.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    }

    // No frame callback on an external surface, as it may already have one attached.
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        ದತ್ತಾಂಶ->surface_ಚೌಕಟ್ಟು_callback = wl_surface_ಚೌಕಟ್ಟು(ದತ್ತಾಂಶ->surface);
        wl_callback_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->surface_ಚೌಕಟ್ಟು_callback, &surface_ಚೌಕಟ್ಟು_listener, ದತ್ತಾಂಶ);
    }

    ದತ್ತಾಂಶ->show_hide_sync_required = true;
    ರಚನೆ wl_callback *cb = wl_display_sync(_this->ಆಂತರಿಕ->display);
    wl_callback_ಕೂಡಿಸು_listener(cb, &show_hide_sync_listener, (ಶೂನ್ಯ *)((uintptr_t)ಕಿಟಕಿ->id));

    ದತ್ತಾಂಶ->showing_ಕಿಟಕಿ = true;
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_SHOWN, 0, 0);
    ದತ್ತಾಂಶ->showing_ಕಿಟಕಿ = false;

    // Send an exposure event to signal that the client should draw.
    SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_EXPOSED, 0, 0);
}

ಸ್ಥಿರ ಶೂನ್ಯ Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *popup)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    ಆದರೆ (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_ಕಿಟಕಿ)) {
        ಹಿಂತಿರುಗಿ;
    }
    popupdata = popup->ಆಂತರಿಕ;
    ಆದರೆ (!popupdata) {
        ಹಿಂತಿರುಗಿ;
    }

    // This may already be freed by a parent popup!
    ಆದರೆ (popupdata->shell_surface.xdg.popup.xdg_popup == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ ((popup->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) && !(popup->flags & SDL_ಕಿಟಕಿ_NOT_FOCUSABLE)) {
        SDL_ಕಿಟಕಿ *new_focus;
        ಸ್ಥಿರಾಂಕ bool ಗಣ_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_ಗಣ_Keyboard_Focus(new_focus, ಗಣ_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = ಖಾಲಿ;
    popupdata->shell_surface.xdg.popup.xdg_positioner = ಖಾಲಿ;

    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(popup);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_POPUP_ಸೂಚಕ, ಖಾಲಿ);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_POSITIONER_ಸೂಚಕ, ಖಾಲಿ);
}

ಶೂನ್ಯ Wayland_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);

    // Custom surfaces have nothing to destroy and are always considered to be 'shown'; nothing to do here.
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        ಹಿಂತಿರುಗಿ;
    }

    /* The window was shown, but the sync point hasn't yet been reached.
     * Pump events to avoid a possible protocol violation.
     */
    ಆದರೆ (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(ದತ್ತಾಂಶ->display);
    }

    wind->shell_surface_ಸ್ಥಿತಿ = WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_HIDDEN;

    ಆದರೆ (wind->surface_ಚೌಕಟ್ಟು_callback) {
        wl_callback_destroy(wind->surface_ಚೌಕಟ್ಟು_callback);
        wind->surface_ಚೌಕಟ್ಟು_callback = ಖಾಲಿ;
    }

    ಆದರೆ (wind->server_decoration) {
        zxdg_toplevel_decoration_v1_destroy(wind->server_decoration);
        wind->server_decoration = ಖಾಲಿ;
    }

    // Clean up the export handle.
    ಆದರೆ (wind->exported) {
        zxdg_exported_v2_destroy(wind->exported);
        wind->exported = ಖಾಲಿ;

        SDL_ಗಣ_String_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, ಖಾಲಿ);
    }

    ಆದರೆ (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = ಖಾಲಿ;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ಆದರೆ (wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
            libdecor_ಚೌಕಟ್ಟು_unref(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು);

            SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_SURFACE_ಸೂಚಕ, ಖಾಲಿ);
            SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_TOPLEVEL_ಸೂಚಕ, ಖಾಲಿ);
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, ಕಿಟಕಿ);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_TOPLEVEL_ಸೂಚಕ, ಖಾಲಿ);
        }

        ಆದರೆ (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_XDG_SURFACE_ಸೂಚಕ, ಖಾಲಿ);
        }
    }

    // Attach a null buffer to unmap the surface.
    ಆದರೆ (wind->ಮುಖವಾಡ.surface) {
        wl_surface_attach(wind->ಮುಖವಾಡ.surface, ಖಾಲಿ, 0, 0);
        wl_surface_commit(wind->ಮುಖವಾಡ.surface);
    }
    wl_surface_attach(wind->surface, ಖಾಲಿ, 0, 0);
    wl_surface_commit(wind->surface);

    // Need to destroy the session object after unmapping the window, or the state may not be saved.
    Wayland_DestroyToplevelSession(wind);

    SDL_zero(wind->shell_surface);
    SDL_zero(wind->explicit_geometry);
    wind->show_hide_sync_required = true;
    ರಚನೆ wl_callback *cb = wl_display_sync(_this->ಆಂತರಿಕ->display);
    wl_callback_ಕೂಡಿಸು_listener(cb, &show_hide_sync_listener, (ಶೂನ್ಯ *)((uintptr_t)ಕಿಟಕಿ->id));
}

ಸ್ಥಿರ ಶೂನ್ಯ handle_xdg_activation_ಮುಗಿದ(ಶೂನ್ಯ *ದತ್ತಾಂಶ,
                                       ರಚನೆ xdg_activation_token_v1 *xdg_activation_token_v1,
                                       ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *token)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ = ದತ್ತಾಂಶ;
    ಆದರೆ (xdg_activation_token_v1 == ಕಿಟಕಿ->activation_token) {
        xdg_activation_v1_activate(ಕಿಟಕಿ->wayland_ದತ್ತಾಂಶ->activation_manager,
                                   token,
                                   ಕಿಟಕಿ->surface);
        xdg_activation_token_v1_destroy(ಕಿಟಕಿ->activation_token);
        ಕಿಟಕಿ->activation_token = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_ಮುಗಿದ
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
ಸ್ಥಿರ ಶೂನ್ಯ Wayland_activate_ಕಿಟಕಿ(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಗುರಿ_wind, bool ಗಣ_serial)
{
    SDL_WaylandSeat *seat = ದತ್ತಾಂಶ->ಕೊನೆಯ_implicit_grab_seat;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *focus = ಖಾಲಿ;

    ಆದರೆ (seat) {
        focus = seat->keyboard.focus;
        ಆದರೆ (!focus) {
            focus = seat->ಸೂಚಕ_2.focus;
        }
    }

    ರಚನೆ wl_surface *requesting_surface = focus ? focus->surface : ಖಾಲಿ;

    ಆದರೆ (ದತ್ತಾಂಶ->activation_manager) {
        ಆದರೆ (ಗುರಿ_wind->activation_token) {
            // We're about to overwrite this with a new request
            xdg_activation_token_v1_destroy(ಗುರಿ_wind->activation_token);
        }

        ಗುರಿ_wind->activation_token = xdg_activation_v1_get_activation_token(ದತ್ತಾಂಶ->activation_manager);
        xdg_activation_token_v1_ಕೂಡಿಸು_listener(ಗುರಿ_wind->activation_token,
                                             &xdg_activation_listener,
                                             ಗುರಿ_wind);

        /* Note that we are not setting the app_id here.
         *
         * Hypothetically we could set the app_id from data->classname, but
         * that part of the API is for _external_ programs, not ourselves.
         *
         * -flibit
         */
        ಆದರೆ (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_ಗಣ_surface(ಗುರಿ_wind->activation_token, requesting_surface);
        }
        ಆದರೆ (ಗಣ_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_ಗಣ_serial(ಗುರಿ_wind->activation_token, seat->ಕೊನೆಯ_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(ಗುರಿ_wind->activation_token);
    }
}

ಶೂನ್ಯ Wayland_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (viddata->activation_manager) {
        /* Check for an activation token, in case the window is being
         * raised in response to a system notification.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *activation_token = SDL_GetNotificationActivationToken();
        ಆದರೆ (activation_token) {
            xdg_activation_v1_activate(viddata->activation_manager,
                                       activation_token,
                                       wind->surface);
            ಹಿಂತಿರುಗಿ;
        }
    }

    // No token? Try to activate the window via an event serial.
    Wayland_activate_ಕಿಟಕಿ(_this->ಆಂತರಿಕ, ಕಿಟಕಿ->ಆಂತರಿಕ, true);
}

bool Wayland_Flash_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_FlashOperation operation)
{
    /* Not setting the serial will specify 'urgency' without switching focus as per
     * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
     */
    Wayland_activate_ಕಿಟಕಿ(_this->ಆಂತರಿಕ, ಕಿಟಕಿ->ಆಂತರಿಕ, false);
    ಹಿಂತಿರುಗಿ true;
}

SDL_Fullscreen_ಫಲಿತಾಂಶ Wayland_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ರಚನೆ wl_output *output = display->ಆಂತರಿಕ->output;

    // Custom surfaces have no toplevel to make fullscreen.
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    ಆದರೆ (wind->showing_ಕಿಟಕಿ && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
    }

    ಆದರೆ (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->ಆಂತರಿಕ->display);
    }

    // Flushing old events pending a new one, ignore this request.
    ಆದರೆ (wind->drop_fullscreen_ವಿನಂತಿಗಳು) {
        ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_ವಿನಂತಿಗಳು = true;
    FlushPendingEvents(ಕಿಟಕಿ);
    wind->drop_fullscreen_ವಿನಂತಿಗಳು = false;

    // Nothing to do if the window is not fullscreen, and this isn't an explicit enter request.
    ಆದರೆ (!wind->is_fullscreen) {
        ಆದರೆ (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
            // Request was out of date; signal the video core not to update any state.
            ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_PENDING;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
            // Already not fullscreen; nothing to do.
            ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    // Don't send redundant fullscreen set/unset events.
    ಆದರೆ (!!fullscreen != wind->is_fullscreen) {
        wind->fullscreen_was_positioned = !!fullscreen;

        /* Only use the specified output if an exclusive mode is being used, or a position was explicitly requested
         * before entering fullscreen desktop. Otherwise, let the compositor handle placement, as it has more
         * information about where the window is and where it should go, particularly if fullscreen is being requested
         * before the window is mapped, or the window spans multiple outputs.
         */
        ಆದರೆ (!ಕಿಟಕಿ->fullscreen_exclusive) {
            ಆದರೆ (ಕಿಟಕಿ->undefined_x || ಕಿಟಕಿ->undefined_y ||
                (wind->ಅಂಕೆ_outputs && !ಕಿಟಕಿ->ಕೊನೆಯ_position_pending)) {
                output = ಖಾಲಿ;
            }
        }

        // Commit to set any pending size or limit data.
        ಆದರೆ (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        ಗಣ_Fullscreen(ಕಿಟಕಿ, output, !!fullscreen);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        ಆದರೆ (wind->ಕೊನೆಯ_display_ID != display->id) {
            wind->fullscreen_was_positioned = true;
            ಗಣ_Fullscreen(ಕಿಟಕಿ, output, true);
        } ಇಲ್ಲದಿದ್ದರೆ {
            Configure_ಕಿಟಕಿ_Geometry(ಕಿಟಕಿ);
            Commit_Libdecor_ಚೌಕಟ್ಟು(ಕಿಟಕಿ);

            ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    ಹಿಂತಿರುಗಿ SDL_FULLSCREEN_PENDING;
}

ಶೂನ್ಯ Wayland_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    // Drop restore requests when showing the window.
    ಆದರೆ (wind->showing_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    ಆದರೆ (!(ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_FULLSCREEN | SDL_ಕಿಟಕಿ_MAXIMIZED)) &&
        !wind->pending_state_deadline_ಎಣಿಕೆ) {
        ಹಿಂತಿರುಗಿ;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ಆದರೆ (!wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
            ಹಿಂತಿರುಗಿ; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_ಚೌಕಟ್ಟು_unset_maximized(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು);
        ಕೂಡಿಸು_Pending_State_Sync(wind);
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        // Note that xdg-shell does NOT provide a way to unset minimize!
        ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            ಆದರೆ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ಖಾಲಿ) {
                ಹಿಂತಿರುಗಿ; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            ಕೂಡಿಸು_Pending_State_Sync(wind);
        }
}

ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_Bordered(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool bordered)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *viddata = (ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *)_this->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ಆದರೆ (wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
            libdecor_ಚೌಕಟ್ಟು_ಗಣ_visibility(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು, bordered);
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ಆದರೆ ((viddata->decoration_manager) && (wind->server_decoration)) {
            ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ zxdg_toplevel_decoration_v1_ಬಹುಲಕ ಬಹುಲಕ = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_ಬಹುಲಕ_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_ಬಹುಲಕ_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_ಗಣ_ಬಹುಲಕ(wind->server_decoration, ಬಹುಲಕ);
        }
    }
}

ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    ಗಣ_Min_Max_Dimensions(ಕಿಟಕಿ);
    Commit_Libdecor_ಚೌಕಟ್ಟು(ಕಿಟಕಿ);

    ಆದರೆ (wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN) {
        wind->pending_state_commit = true;
    }
}

ಶೂನ್ಯ Wayland_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->ಆಂತರಿಕ->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_FULLSCREEN) && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MAXIMIZED) &&
        !wind->pending_state_deadline_ಎಣಿಕೆ) {
        ಹಿಂತಿರುಗಿ;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ಆದರೆ (!wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
            ಹಿಂತಿರುಗಿ; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        ಆದರೆ (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_ಚೌಕಟ್ಟು_ಗಣ_maximized(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು);
        ಕೂಡಿಸು_Pending_State_Sync(wind);
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ಆದರೆ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ಖಾಲಿ) {
            ಹಿಂತಿರುಗಿ; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        ಆದರೆ (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_ಗಣ_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        ಕೂಡಿಸು_Pending_State_Sync(wind);
    }
}

ಶೂನ್ಯ Wayland_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        ಹಿಂತಿರುಗಿ;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ಆದರೆ (!wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
            ಹಿಂತಿರುಗಿ; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_ಚೌಕಟ್ಟು_ಗಣ_minimized(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು);
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MINIMIZED, 0, 0);
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ಆದರೆ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ಖಾಲಿ) {
            ಹಿಂತಿರುಗಿ; // Can't do anything yet, wait for ShowWindow
        }
        xdg_toplevel_ಗಣ_minimized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        SDL_Send_ಕಿಟಕಿ_Event(ಕಿಟಕಿ, SDL_EVENT_ಕಿಟಕಿ_MINIMIZED, 0, 0);
    }
}

bool Wayland_ಗಣ_ಕಿಟಕಿ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    /* This may look suspiciously like SetWindowGrab, despite SetMouseRect not
     * implicitly doing a grab. And you're right! Wayland doesn't let us mess
     * around with mouse focus whatsoever, so it just happens to be that the
     * work that we can do in these two functions ends up being the same.
     *
     * Just know that this call lets you confine with a rect, SetWindowGrab
     * lets you confine without a rect.
     */
    ಆದರೆ (!ದತ್ತಾಂಶ->ಸೂಚಕ_constraints) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_ಸೂಚಕ_Grabs(ದತ್ತಾಂಶ, ಕಿಟಕಿ->ಆಂತರಿಕ);
    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    ಆದರೆ (!ದತ್ತಾಂಶ->ಸೂಚಕ_constraints) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_ಸೂಚಕ_Grabs(ದತ್ತಾಂಶ, ಕಿಟಕಿ->ಆಂತರಿಕ);
    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    ಆದರೆ (!ದತ್ತಾಂಶ->ಕೀಲಿ_inhibitor_manager) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(ದತ್ತಾಂಶ, ಕಿಟಕಿ->ಆಂತರಿಕ);
    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_Reconfigure_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ_Flags flags)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    // Don't try to reconfigure mapped windows, unless they are custom or external.
    ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN &&
        ದತ್ತಾಂಶ->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        // Window is already mapped; abort.
        ಹಿಂತಿರುಗಿ false;
    }

    /* The caller guarantees that only one of the GL or Vulkan flags will be set.
     * Note that Vulkan doesn't require any specific configuration, so only EGL
     * objects are added and removed as required.
     */
    ಆದರೆ (flags & SDL_ಕಿಟಕಿ_OPENGL) {
        ಆದರೆ (!ದತ್ತಾಂಶ->egl_ಕಿಟಕಿ) {
            ದತ್ತಾಂಶ->egl_ಕಿಟಕಿ = WAYLAND_wl_egl_ಕಿಟಕಿ_create(ದತ್ತಾಂಶ->surface, ದತ್ತಾಂಶ->current.pixel_ಅಗಲ, ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ);
        }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
        ದತ್ತಾಂಶ->egl_surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, (Native_ಕಿಟಕಿ_Type)ದತ್ತಾಂಶ->egl_ಕಿಟಕಿ);

        ಆದರೆ (ದತ್ತಾಂಶ->egl_surface == EGL_NO_SURFACE) {
            ಹಿಂತಿರುಗಿ false; // SDL_EGL_CreateSurface should have set the error.
        }
#ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ (!ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ) {
            ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ = WAYLAND_wl_display_create_ಸರತಿ(ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ->display);
            ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(ದತ್ತಾಂಶ->surface);
            WAYLAND_wl_proxy_ಗಣ_ಸರತಿ((ರಚನೆ wl_proxy *)ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper, ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ);
            ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback = wl_surface_ಚೌಕಟ್ಟು(ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper);
            wl_callback_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback, &gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_listener, ದತ್ತಾಂಶ);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
        ಆದರೆ (ದತ್ತಾಂಶ->egl_surface) {
            SDL_EGL_DestroySurface(_this, ದತ್ತಾಂಶ->egl_surface);
            ದತ್ತಾಂಶ->egl_surface = EGL_NO_SURFACE;
        }
#ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ (ದತ್ತಾಂಶ->egl_ಕಿಟಕಿ) {
            WAYLAND_wl_egl_ಕಿಟಕಿ_destroy(ದತ್ತಾಂಶ->egl_ಕಿಟಕಿ);
            ದತ್ತಾಂಶ->egl_ಕಿಟಕಿ = ಖಾಲಿ;
        }

        ಆದರೆ (ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback) {
            wl_callback_destroy(ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback);
            ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback = ಖಾಲಿ;
        }

        ಆದರೆ (ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper);
            ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper = ಖಾಲಿ;
        }

        ಆದರೆ (ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ) {
            WAYLAND_wl_event_ಸರತಿ_destroy(ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ);
            ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ = ಖಾಲಿ;
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

bool Wayland_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    SDL_Video_ದತ್ತಾಂಶ *c = _this->ಆಂತರಿಕ;
    ರಚನೆ wl_surface *external_surface = (ರಚನೆ wl_surface *)SDL_Get_ಸೂಚಕ_Property(create_props, SDL_PROP_ಕಿಟಕಿ_CREATE_WAYLAND_WL_SURFACE_ಸೂಚಕ,
                                                                               (ರಚನೆ wl_surface *)SDL_Get_ಸೂಚಕ_Property(create_props, "sdl2-compat.external_window", ಖಾಲಿ));
    ಸ್ಥಿರಾಂಕ bool custom_surface_role = (external_surface != ಖಾಲಿ) || SDL_GetBooleanProperty(create_props, SDL_PROP_ಕಿಟಕಿ_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    ಸ್ಥಿರಾಂಕ bool create_egl_ಕಿಟಕಿ = !!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_ಕಿಟಕಿ_CREATE_WAYLAND_CREATE_EGL_ಕಿಟಕಿ_BOOLEAN, false);

    ದತ್ತಾಂಶ = SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಕಿಟಕಿ->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    ದತ್ತಾಂಶ->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_ಕಿಟಕಿ_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    ಆದರೆ (ಕಿಟಕಿ->x == SDL_WINDOWPOS_UNDEFINED) {
        ಕಿಟಕಿ->x = 0;
    }
    ಆದರೆ (ಕಿಟಕಿ->y == SDL_WINDOWPOS_UNDEFINED) {
        ಕಿಟಕಿ->y = 0;
    }

    ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ = c;
    ದತ್ತಾಂಶ->sdlwindow = ಕಿಟಕಿ;

    // Default to all capabilities
    ದತ್ತಾಂಶ->wm_caps = WAYLAND_WM_CAPS_ALL;

    ದತ್ತಾಂಶ->scale_ಗುಣಕ_2 = 1.0;

    ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
        ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display = ಕಿಟಕಿ->ಪೋಷಕ->ಆಂತರಿಕ->scale_ಗಮ್ಯ_display;
        ದತ್ತಾಂಶ->scale_ಗುಣಕ_2 = ಕಿಟಕಿ->ಪೋಷಕ->ಆಂತರಿಕ->scale_ಗುಣಕ_2;
        EnsurePopupPositionIsValid(ಕಿಟಕಿ, &ಕಿಟಕಿ->x, &ಕಿಟಕಿ->y);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < _this->ಅಂಕೆ_displays; i++) {
            ದತ್ತಾಂಶ->scale_ಗುಣಕ_2 = SDL_max(ದತ್ತಾಂಶ->scale_ಗುಣಕ_2, _this->displays[i]->ಆಂತರಿಕ->scale_ಗುಣಕ_2);
        }
    }

    ದತ್ತಾಂಶ->outputs = ಖಾಲಿ;
    ದತ್ತಾಂಶ->ಅಂಕೆ_outputs = 0;
    ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display = c->scale_ಗಮ್ಯ_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    ದತ್ತಾಂಶ->app_id = SDL_strdup(SDL_GetAppID());

    ಆದರೆ (!ದತ್ತಾಂಶ->scale_ಗಮ್ಯ_display) {
        ದತ್ತಾಂಶ->requested.logical_ಅಗಲ = ಕಿಟಕಿ->floating.w;
        ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ = ಕಿಟಕಿ->floating.h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->requested.logical_ಅಗಲ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಕಿಟಕಿ->floating.w);
        ದತ್ತಾಂಶ->requested.logical_ಎತ್ತರ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಕಿಟಕಿ->floating.h);
        ದತ್ತಾಂಶ->requested.pixel_ಅಗಲ = ಕಿಟಕಿ->floating.w;
        ದತ್ತಾಂಶ->requested.pixel_ಎತ್ತರ = ಕಿಟಕಿ->floating.h;
    }

    ಆದರೆ (!external_surface) {
        ದತ್ತಾಂಶ->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->surface, &surface_listener, ದತ್ತಾಂಶ);
        wl_surface_ಗಣ_user_ದತ್ತಾಂಶ(ದತ್ತಾಂಶ->surface, ದತ್ತಾಂಶ);
        SDL_WAYLAND_ರಿಜಿಸ್ಟರ್_surface(ದತ್ತಾಂಶ->surface);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಕಿಟಕಿ->flags |= SDL_ಕಿಟಕಿ_EXTERNAL;
        ದತ್ತಾಂಶ->surface = external_surface;

        /* External surfaces are registered by being put in a list, as changing tags or userdata
         * can cause problems with external toolkits.
         */
        Wayland_ಕೂಡಿಸು_ಕಿಟಕಿ_ದತ್ತಾಂಶ_ಗಮ್ಯ_External_List(ದತ್ತಾಂಶ);
    }

    /* Always attach a viewport and fractional scale manager if available and the surface is not custom/external,
     * or the custom/external surface was explicitly flagged as high pixel density aware, which signals that the
     * application wants SDL to handle scaling.
     */
    ಆದರೆ (!custom_surface_role || (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಮೇಲಿನ_PIXEL_DENSITY)) {
        ಆದರೆ (c->viewporter) {
            ದತ್ತಾಂಶ->viewport = wp_viewporter_get_viewport(c->viewporter, ದತ್ತಾಂಶ->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_ಗಣ_ಮೂಲ(ದತ್ತಾಂಶ->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        ಆದರೆ (c->fractional_scale_manager) {
            ದತ್ತಾಂಶ->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, ದತ್ತಾಂಶ->surface);
            wp_fractional_scale_v1_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->fractional_scale, &fractional_scale_listener, ದತ್ತಾಂಶ);
        }
    }

    ಆದರೆ (!custom_surface_role) {
        ಆದರೆ (c->wp_color_manager_v1) {
            ದತ್ತಾಂಶ->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, ದತ್ತಾಂಶ->surface);
            wp_color_management_surface_feedback_v1_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, ದತ್ತಾಂಶ);
            Wayland_Get_Color_Info_For_ಕಿಟಕಿ(ದತ್ತಾಂಶ, true);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c->frog_color_management_factory_v1) {
            ದತ್ತಾಂಶ->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, ದತ್ತಾಂಶ->surface);
            frog_color_managed_surface_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->frog_color_managed_surface, &frog_surface_listener, ದತ್ತಾಂಶ);
        }

        ಆದರೆ (c->wp_alpha_modifier_v1) {
            ದತ್ತಾಂಶ->wp_alpha_modifier_surface_v1 = wp_alpha_modifier_v1_get_surface(c->wp_alpha_modifier_v1, ದತ್ತಾಂಶ->surface);
            wp_alpha_modifier_surface_v1_ಗಣ_multiplier(ದತ್ತಾಂಶ->wp_alpha_modifier_surface_v1, SDL_MAX_UINT32);
        }
    }

    // Must be called before EGL configuration to set the drawable backbuffer size.
    Configure_ಕಿಟಕಿ_Geometry(ಕಿಟಕಿ);

    /* Fire a callback when the compositor wants a new frame rendered.
     * Right now this only matters for OpenGL; we use this callback to add a
     * wait timeout that avoids getting deadlocked by the compositor when the
     * window isn't visible.
     */
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ = WAYLAND_wl_display_create_ಸರತಿ(ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ->display);
        ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(ದತ್ತಾಂಶ->surface);
        WAYLAND_wl_proxy_ಗಣ_ಸರತಿ((ರಚನೆ wl_proxy *)ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper, ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ);
        ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback = wl_surface_ಚೌಕಟ್ಟು(ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper);
        wl_callback_ಕೂಡಿಸು_listener(ದತ್ತಾಂಶ->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback, &gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_listener, ದತ್ತಾಂಶ);
    }

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT) {
        ಆದರೆ (_this->gl_config.alpha_ಗಾತ್ರ == 0) {
            _this->gl_config.alpha_ಗಾತ್ರ = 8;
        }
    }

    ಆದರೆ (create_egl_ಕಿಟಕಿ) {
        ದತ್ತಾಂಶ->egl_ಕಿಟಕಿ = WAYLAND_wl_egl_ಕಿಟಕಿ_create(ದತ್ತಾಂಶ->surface, ದತ್ತಾಂಶ->current.pixel_ಅಗಲ, ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL) {
        // Create the GLES window surface
        ದತ್ತಾಂಶ->egl_surface = SDL_EGL_CreateSurface(_this, ಕಿಟಕಿ, (Native_ಕಿಟಕಿ_Type)ದತ್ತಾಂಶ->egl_ಕಿಟಕಿ);

        ಆದರೆ (ದತ್ತಾಂಶ->egl_surface == EGL_NO_SURFACE) {
            ಹಿಂತಿರುಗಿ false; // SDL_EGL_CreateSurface should have set error
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    ಆದರೆ (!custom_surface_role) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
        ಆದರೆ (c->shell.libdecor && !SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
            ದತ್ತಾಂಶ->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
            ಆದರೆ (c->shell.xdg) {
            ಆದರೆ (SDL_ಕಿಟಕಿ_IS_POPUP(ಕಿಟಕಿ)) {
                ದತ್ತಾಂಶ->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ದತ್ತಾಂಶ->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL;
            }
        } // All other cases will be WAYLAND_SURFACE_UNKNOWN
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Roleless and external surfaces are always considered to be in the shown state by the backend.
        ದತ್ತಾಂಶ->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_CUSTOM;
        ದತ್ತಾಂಶ->shell_surface_ಸ್ಥಿತಿ = WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN;

        // External windows are presumed to be shown.
        ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL) {
            ಕಿಟಕಿ->flags &= ~SDL_ಕಿಟಕಿ_HIDDEN;
        }
    }

    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_ಬಫರ್, false)) {
        ದತ್ತಾಂಶ->double_ಬಫರ್ = true;
    }

    SDL_PropertiesID props = SDL_Get_ಕಿಟಕಿ_Properties(ಕಿಟಕಿ);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_DISPLAY_ಸೂಚಕ, ದತ್ತಾಂಶ->wayland_ದತ್ತಾಂಶ->display);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_SURFACE_ಸೂಚಕ, ದತ್ತಾಂಶ->surface);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_VIEWPORT_ಸೂಚಕ, ದತ್ತಾಂಶ->viewport);
    SDL_ಗಣ_ಸೂಚಕ_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_EGL_ಕಿಟಕಿ_ಸೂಚಕ, ದತ್ತಾಂಶ->egl_ಕಿಟಕಿ);
    ಆದರೆ (ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || ದತ್ತಾಂಶ->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕಿಟಕಿ_id = SDL_GetStringProperty(create_props, SDL_PROP_ಕಿಟಕಿ_CREATE_WAYLAND_ಕಿಟಕಿ_ID_STRING, ಖಾಲಿ);
        ಆದರೆ (ಕಿಟಕಿ_id && *ಕಿಟಕಿ_id != '\0') {
            SDL_ಗಣ_String_Property(props, SDL_PROP_ಕಿಟಕಿ_WAYLAND_ಕಿಟಕಿ_ID_STRING, ಕಿಟಕಿ_id);
        }
    }

    ದತ್ತಾಂಶ->ದೊರಕಿತು_test_ಫಲಿತಾಂಶ = SDL_HITTEST_ಸಾಮಾನ್ಯ;

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    ಕಿಟಕಿ->ಆಂತರಿಕ->limits_ಬದಲಾಯಿತು = true;
}

ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    ಕಿಟಕಿ->ಆಂತರಿಕ->limits_ಬದಲಾಯಿತು = true;
}

ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    ಕಿಟಕಿ->ಆಂತರಿಕ->limits_ಬದಲಾಯಿತು = true;
}

bool Wayland_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    // Only popup windows can be positioned relative to the parent.
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        ಆದರೆ (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_ಆವೃತ್ತಿ(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_ಆವೃತ್ತಿ) {
            ಹಿಂತಿರುಗಿ SDL_Unsupported();
        }

        RepositionPopup(ಕಿಟಕಿ, false);
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(ಕಿಟಕಿ);

        ಆದರೆ (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_Get_Video_Display_For_Fullscreen_ಕಿಟಕಿ(ಕಿಟಕಿ);
            ಆದರೆ (display && wind->ಕೊನೆಯ_display_ID != display->id) {
                ರಚನೆ wl_output *output = display->ಆಂತರಿಕ->output;
                ಗಣ_Fullscreen(ಕಿಟಕಿ, output, true);

                ಹಿಂತಿರುಗಿ true;
            }
        }
    }
    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("wayland cannot position non-popup windows");
}

ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    /* Flush any pending state operations, as fullscreen windows do not get
     * explicitly resized, not strictly obeying the size of a maximized window
     * is a protocol violation, and pending restore events might result in a
     * configure event overwriting the requested size.
     *
     * Calling this on a custom surface is informative, so the size must
     * always be passed through.
     */
    FlushPendingEvents(ಕಿಟಕಿ);

    ಸ್ಥಿರಾಂಕ bool maximized = (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_MAXIMIZED) != 0;
    ಸ್ಥಿರಾಂಕ bool resizable_state = !(ಕಿಟಕಿ->flags & (SDL_ಕಿಟಕಿ_MAXIMIZED | SDL_ಕಿಟಕಿ_FULLSCREEN));

    /* Maximized and fullscreen windows don't get resized, and the new size is ignored
     * if this is just to recalculate the min/max or aspect limits on a tiled window.
     *
     * Some compositors will mark tiled windows as maximized. In these cases, the content
     * size is recalculated, but window size itself is left alone, as the spec states that
     * the configure size of a maximized window must be obeyed.
     */
    ಆದರೆ (resizable_state || (ಕಿಟಕಿ->tiled && !wind->limits_ಬದಲಾಯಿತು) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        ಆದರೆ (!maximized) {
            ಆದರೆ (!wind->scale_ಗಮ್ಯ_display) {
                wind->requested.logical_ಅಗಲ = ಕಿಟಕಿ->pending.w;
                wind->requested.logical_ಎತ್ತರ = ಕಿಟಕಿ->pending.h;
            } ಇಲ್ಲದಿದ್ದರೆ {
                wind->requested.logical_ಅಗಲ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಕಿಟಕಿ->pending.w);
                wind->requested.logical_ಎತ್ತರ = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, ಕಿಟಕಿ->pending.h);
                wind->requested.pixel_ಅಗಲ = ಕಿಟಕಿ->pending.w;
                wind->requested.pixel_ಎತ್ತರ = ಕಿಟಕಿ->pending.h;
            }
        }

        /* If a non-resizable window somehow wound up in the tiled state, store the new
         * size in the floating parameters so the size will be preserved for future
         * configure events.
         *
         * This shouldn't happen, but apparently it can on at least one compositor...
         */
        ಆದರೆ (ಕಿಟಕಿ->tiled && !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_RESIZABLE)) {
            ಕಿಟಕಿ->floating.w = ಕಿಟಕಿ->pending.w;
            ಕಿಟಕಿ->floating.h = ಕಿಟಕಿ->pending.h;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Can't resize the window.
        ಕಿಟಕಿ->ಕೊನೆಯ_ಗಾತ್ರ_pending = false;
    }

    wind->limits_ಬದಲಾಯಿತು = false;
    ಆದರೆ (wind->shell_surface_ಸ್ಥಿತಿ == WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    Configure_ಕಿಟಕಿ_Geometry(ಕಿಟಕಿ);
    Commit_Libdecor_ಚೌಕಟ್ಟು(ಕಿಟಕಿ);
}

ಶೂನ್ಯ Wayland_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *w, ಪೂರ್ಣಾಂಕ *h)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    *w = ದತ್ತಾಂಶ->current.pixel_ಅಗಲ;
    *h = ದತ್ತಾಂಶ->current.pixel_ಎತ್ತರ;
}

ದಶಮಾಂಶ Wayland_Get_ಕಿಟಕಿ_Content_Scale(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಮೇಲಿನ_PIXEL_DENSITY || wind->scale_ಗಮ್ಯ_display || wind->fullscreen_exclusive) {
        ಹಿಂತಿರುಗಿ (ದಶಮಾಂಶ)wind->scale_ಗುಣಕ_2;
    }

    ಹಿಂತಿರುಗಿ 1.0f;
}

SDL_DisplayID Wayland_Get_Display_For_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (wind) {
        ಹಿಂತಿರುಗಿ wind->ಕೊನೆಯ_display_ID;
    }

    ಹಿಂತಿರುಗಿ 0;
}

bool Wayland_ಗಣ_ಕಿಟಕಿ_Opacity(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ opacity)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (wind->wp_alpha_modifier_surface_v1) {
        ಸ್ಥಿರಾಂಕ bool is_opaque = !(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_TRANSPARENT) && opacity == 1.0f;

        ಆದರೆ (wind->ಮುಖವಾಡ.mapped && wind->ಮುಖವಾಡ.opaque != is_opaque) {
            ರಚನೆ wl_ಬಫರ್ *old_ಬಫರ್ = wind->ಮುಖವಾಡ.ಬಫರ್_2;
            wind->ಮುಖವಾಡ.opaque = is_opaque;
            wind->ಮುಖವಾಡ.ಬಫರ್_2 = Wayland_Create_Single_Pixel_ಬಫರ್(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->ಮುಖವಾಡ.surface, wind->ಮುಖವಾಡ.ಬಫರ್_2, 0, 0);
            ಆದರೆ (wl_surface_get_ಆವೃತ್ತಿ(wind->ಮುಖವಾಡ.surface) >= WL_SURFACE_DAMAGE_ಬಫರ್_SINCE_ಆವೃತ್ತಿ) {
                wl_surface_damage_ಬಫರ್(wind->ಮುಖವಾಡ.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } ಇಲ್ಲದಿದ್ದರೆ {
                wl_surface_damage(wind->ಮುಖವಾಡ.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            ಆದರೆ (is_opaque) {
                ಗಣ_Surface_Opaque_Region(wind->ಮುಖವಾಡ.surface, wind->current.logical_ಅಗಲ, wind->current.logical_ಎತ್ತರ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಗಣ_Surface_Opaque_Region(wind->ಮುಖವಾಡ.surface, 0, 0);
            }

            wl_surface_commit(wind->ಮುಖವಾಡ.surface);

            ಆದರೆ (old_ಬಫರ್) {
                wl_ಬಫರ್_destroy(old_ಬಫರ್);
            }
        }

        ಆದರೆ (is_opaque) {
            ಗಣ_Surface_Opaque_Region(wind->surface, wind->current.viewport_ಅಗಲ, wind->current.viewport_ಎತ್ತರ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಗಣ_Surface_Opaque_Region(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_ಗಣ_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((ದ್ವಿಗುಣ)SDL_MAX_UINT32 * (ದ್ವಿಗುಣ)opacity));

        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *title = ಕಿಟಕಿ->title ? ಕಿಟಕಿ->title : "";

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
        libdecor_ಚೌಕಟ್ಟು_ಗಣ_title(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು, title);
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_ಗಣ_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ icon_ವಿಂಗಡಿಸು_callback(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *a, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *b)
{
    ಸ್ಥಿರಾಂಕ SDL_Surface *s1 = *(ಸ್ಥಿರಾಂಕ SDL_Surface **)a;
    ಸ್ಥಿರಾಂಕ SDL_Surface *s2 = *(ಸ್ಥಿರಾಂಕ SDL_Surface **)b;

    ಹಿಂತಿರುಗಿ (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_ಗಣ_ಕಿಟಕಿ_Icon(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *icon)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Wayland_SHMPool *shm_pool = ಖಾಲಿ;
    ರಚನೆ xdg_toplevel *toplevel = ಖಾಲಿ;

    ಆದರೆ (!_this->ಆಂತರಿಕ->xdg_toplevel_icon_manager_v1) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    ಪೂರ್ಣಾಂಕ image_ಎಣಿಕೆ_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_ಎಣಿಕೆ_2);
    ಆದರೆ (!images || !image_ಎಣಿಕೆ_2) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Release the old icon resources.
    ಆದರೆ (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = ಖಾಲಿ;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < wind->icon_ಬಫರ್_ಎಣಿಕೆ; ++i) {
        wl_ಬಫರ್_destroy(wind->icon_buffers[i]);
    }
    wind->icon_ಬಫರ್_ಎಣಿಕೆ = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->ಆಂತರಿಕ->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_ಎಣಿಕೆ_2 * ಗಾತ್ರ(ರಚನೆ wl_ಬಫರ್ *));
    ಆದರೆ (!wind->icon_buffers) {
        ಹೋಗು failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    size_t pool_ಗಾತ್ರ = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < image_ಎಣಿಕೆ_2; ++i) {
        // Images must be square. Non-square images will be centered.
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 = SDL_max(images[i]->w, images[i]->h);
        pool_ಗಾತ್ರ += ಗಾತ್ರ_2 * ಗಾತ್ರ_2 * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_ಎಣಿಕೆ_2, ಗಾತ್ರ(SDL_Surface *), icon_ವಿಂಗಡಿಸು_callback);

    shm_pool = Wayland_AllocSHMPool(pool_ಗಾತ್ರ);
    ಆದರೆ (!shm_pool) {
        SDL_ಗಣ_Error("wayland: failed to allocate an SHM pool for the icon");
        ಹೋಗು failure_cleanup;
    }

    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ ತಳ_ಗಾತ್ರ = (ದ್ವಿಗುಣ)SDL_max(icon->w, icon->h);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < image_ಎಣಿಕೆ_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ level_ಗಾತ್ರ = SDL_max(surface->w, surface->h);
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ scale = (ಪೂರ್ಣಾಂಕ)SDL_floor((ದ್ವಿಗುಣ)level_ಗಾತ್ರ / ತಳ_ಗಾತ್ರ);
        ಆದರೆ (!scale) {
            ಮುಂದುವರಿ;
        }

        ಆದರೆ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            ಆದರೆ (!surface) {
                SDL_ಗಣ_Error("wayland: failed to convert the icon image to ARGB8888 format");
                ಹೋಗು failure_cleanup;
            }
        }

        ಶೂನ್ಯ *ಬಫರ್_mem;
        ರಚನೆ wl_ಬಫರ್ *ಬಫರ್_2 = Wayland_Alloc_ಬಫರ್_From_Pool(shm_pool, level_ಗಾತ್ರ, level_ಗಾತ್ರ, &ಬಫರ್_mem);
        ಆದರೆ (!ಬಫರ್_2) {
            // Clean up the temporary conversion surface.
            ಆದರೆ (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_ಗಣ_Error("wayland: failed to allocate a wl_buffer for the icon");
            ಹೋಗು failure_cleanup;
        }

        wind->icon_buffers[wind->icon_ಬಫರ್_ಎಣಿಕೆ++] = ಬಫರ್_2;

        // Center non-square images.
        ಆದರೆ (surface->w < level_ಗಾತ್ರ) {
            SDL_memset(ಬಫರ್_mem, 0, level_ಗಾತ್ರ * level_ಗಾತ್ರ * 4);
            ಬಫರ್_mem = (Uint8 *)ಬಫರ್_mem + (((level_ಗಾತ್ರ - surface->w) / 2) * 4);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (surface->h < level_ಗಾತ್ರ) {
            SDL_memset(ಬಫರ್_mem, 0, level_ಗಾತ್ರ * level_ಗಾತ್ರ * 4);
            ಬಫರ್_mem = (Uint8 *)ಬಫರ್_mem + (((level_ಗಾತ್ರ - surface->h) / 2) * (level_ಗಾತ್ರ * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, ಬಫರ್_mem, level_ಗಾತ್ರ * 4, true);

        xdg_toplevel_icon_v1_ಕೂಡಿಸು_ಬಫರ್(wind->xdg_toplevel_icon_v1, ಬಫರ್_2, scale);

        // Clean up the temporary scaled or conversion surface.
        ಆದರೆ (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
        toplevel = libdecor_ಚೌಕಟ್ಟು_get_xdg_toplevel(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು);
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    ಆದರೆ (toplevel) {
        xdg_toplevel_icon_manager_v1_ಗಣ_icon(_this->ಆಂತರಿಕ->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
    }

    Wayland_ReleaseSHMPool(shm_pool);
    SDL_free(images);

    ಹಿಂತಿರುಗಿ true;

failure_cleanup:

    SDL_free(images);

    ಆದರೆ (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = ಖಾಲಿ;
    }

    Wayland_ReleaseSHMPool(shm_pool);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < wind->icon_ಬಫರ್_ಎಣಿಕೆ; ++i) {
        wl_ಬಫರ್_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = ಖಾಲಿ;
    wind->icon_ಬಫರ್_ಎಣಿಕೆ = 0;

    ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ *Wayland_Get_ಕಿಟಕಿ_ICCProfile(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, size_t *ಗಾತ್ರ_2)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
    ಶೂನ್ಯ *ret = ಖಾಲಿ;

    ಆದರೆ (wind->icc_ಗಾತ್ರ > 0) {
        ಶೂನ್ಯ *icc_map = mmap(ಖಾಲಿ, wind->icc_ಗಾತ್ರ, PROT_READ, MAP_PRIVATE, wind->icc_fd, 0);
        ಆದರೆ (icc_map != MAP_FAILED) {
            ret = SDL_malloc(wind->icc_ಗಾತ್ರ);
            ಆದರೆ (ret) {
                *ಗಾತ್ರ_2 = wind->icc_ಗಾತ್ರ;
                SDL_memcpy(ret, icc_map, *ಗಾತ್ರ_2);
            }
            munmap(icc_map, wind->icc_ಗಾತ್ರ);
        }
    }

    ಹಿಂತಿರುಗಿ ret;
}

bool Wayland_Sync_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಮಾಡು {
        WAYLAND_wl_display_roundtrip(_this->ಆಂತರಿಕ->display);
    } ಆಗ (wind->pending_state_deadline_ಎಣಿಕೆ);

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Wayland_AcceptDragAndDrop(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool accept)
{
    ಕಿಟಕಿ->ಆಂತರಿಕ->ಸ್ವೀಕರಿಸು_drag_and_drop = accept;
}

bool Wayland_ಗಣ_ಕಿಟಕಿ_Focusable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool focusable)
{
    ಆದರೆ (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_POPUP_MENU) {
        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_HIDDEN)) {
            ಆದರೆ (!focusable && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_ಒಳಹರಿವು_FOCUS)) {
                SDL_ಕಿಟಕಿ *new_focus;
                ಸ್ಥಿರಾಂಕ bool ಗಣ_focus = SDL_ShouldRelinquishPopupFocus(ಕಿಟಕಿ, &new_focus);
                Wayland_ಗಣ_Keyboard_Focus(new_focus, ಗಣ_focus);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (focusable) {
                ಆದರೆ (SDL_ShouldFocusPopup(ಕಿಟಕಿ)) {
                    Wayland_ಗಣ_Keyboard_Focus(ಕಿಟಕಿ, true);
                }
            }
        }

        ಹಿಂತಿರುಗಿ true;
    }

    ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("wayland: focus can only be toggled on popup menu windows");
}

ಶೂನ್ಯ Wayland_Show_ಕಿಟಕಿ_System_Menu(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;
    SDL_WaylandSeat *seat = wind->wayland_ದತ್ತಾಂಶ->ಕೊನೆಯ_implicit_grab_seat;

    ಆದರೆ (!seat) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (wind->scale_ಗಮ್ಯ_display) {
        x = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, x);
        y = Pixel_ಗಮ್ಯ_ಬಿಂದು(ಕಿಟಕಿ, y);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ಆದರೆ (wind->shell_surface.libdecor.ಚೌಕಟ್ಟು) {
            libdecor_ಚೌಕಟ್ಟು_show_ಕಿಟಕಿ_menu(wind->shell_surface.libdecor.ಚೌಕಟ್ಟು, seat->wl_seat, seat->ಕೊನೆಯ_implicit_grab_serial, x, y);
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ಆದರೆ (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_ಕಿಟಕಿ_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->ಕೊನೆಯ_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    ಆದರೆ (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        ಹಿಂತಿರುಗಿ true;
    }
#ಆದರೆ_ಅಂತ್ಯ

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    ಆದರೆ (ದತ್ತಾಂಶ->idle_inhibit_manager) {
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ = _this->windows;
        ಆಗ (ಕಿಟಕಿ) {
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *win_ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

            ಆದರೆ (_this->suspend_screensaver && !win_ದತ್ತಾಂಶ->idle_inhibitor) {
                win_ದತ್ತಾಂಶ->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(ದತ್ತಾಂಶ->idle_inhibit_manager,
                                                                 win_ದತ್ತಾಂಶ->surface);
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!_this->suspend_screensaver && win_ದತ್ತಾಂಶ->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_ದತ್ತಾಂಶ->idle_inhibitor);
                win_ದತ್ತಾಂಶ->idle_inhibitor = ಖಾಲಿ;
            }

            ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ;
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Wayland_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *wind = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        ಆದರೆ (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            ಕಿಟಕಿ->ದೊರಕಿತು_test = ಖಾಲಿ;
            WAYLAND_wl_display_roundtrip(ದತ್ತಾಂಶ->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_Display_Remove_ಕಿಟಕಿ_References_From_Seats(ದತ್ತಾಂಶ, wind);

        ಆದರೆ (wind->ಮುಖವಾಡ.viewport) {
            wp_viewport_destroy(wind->ಮುಖವಾಡ.viewport);
        }
        ಆದರೆ (wind->ಮುಖವಾಡ.ಬಫರ್_2) {
            wl_ಬಫರ್_destroy(wind->ಮುಖವಾಡ.ಬಫರ್_2);
        }
        ಆದರೆ (wind->ಮುಖವಾಡ.subsurface) {
            wl_subsurface_destroy(wind->ಮುಖವಾಡ.subsurface);
        }
        ಆದರೆ (wind->ಮುಖವಾಡ.surface) {
            wl_surface_destroy(wind->ಮುಖವಾಡ.surface);
        }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
        ಆದರೆ (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (wind->egl_ಕಿಟಕಿ) {
            WAYLAND_wl_egl_ಕಿಟಕಿ_destroy(wind->egl_ಕಿಟಕಿ);
        }

        ಆದರೆ (wind->idle_inhibitor) {
            zwp_idle_inhibitor_v1_destroy(wind->idle_inhibitor);
        }

        ಆದರೆ (wind->activation_token) {
            xdg_activation_token_v1_destroy(wind->activation_token);
        }

        ಆದರೆ (wind->viewport) {
            wp_viewport_destroy(wind->viewport);
        }

        ಆದರೆ (wind->fractional_scale) {
            wp_fractional_scale_v1_destroy(wind->fractional_scale);
        }

        ಆದರೆ (wind->wp_alpha_modifier_surface_v1) {
            wp_alpha_modifier_surface_v1_destroy(wind->wp_alpha_modifier_surface_v1);
        }

        ಆದರೆ (wind->frog_color_managed_surface) {
            frog_color_managed_surface_destroy(wind->frog_color_managed_surface);
        }

        ಆದರೆ (wind->wp_color_management_surface_feedback) {
            Wayland_FreeColorInfoState(wind->color_info_state);
            wp_color_management_surface_feedback_v1_destroy(wind->wp_color_management_surface_feedback);
        }

        SDL_free(wind->outputs);
        SDL_free(wind->app_id);

        ಆದರೆ (wind->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback) {
            wl_callback_destroy(wind->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback);
            WAYLAND_wl_proxy_wrapper_destroy(wind->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper);
            WAYLAND_wl_event_ಸರತಿ_destroy(wind->gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ);
        }

        ಆದರೆ (!(ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } ಇಲ್ಲದಿದ್ದರೆ {
            Wayland_Remove_ಕಿಟಕಿ_ದತ್ತಾಂಶ_From_External_List(wind);
        }

        ಆದರೆ (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < wind->icon_ಬಫರ್_ಎಣಿಕೆ; ++i) {
            wl_ಬಫರ್_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_ಬಫರ್_ಎಣಿಕೆ = 0;

        SDL_free(wind);
    }
    ಕಿಟಕಿ->ಆಂತರಿಕ = ಖಾಲಿ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND
