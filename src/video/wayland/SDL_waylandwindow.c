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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND

#అన్తర్భావ <sys/mman.h>

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../core/unix/SDL_appid.h"
#అన్తర్భావ "../../notification/SDL_notification_c.h"
#అన్తర్భావ "../SDL_egl_c.h"
#అన్తర్భావ "SDL_waylandevents_c.h"
#అన్తర్భావ "SDL_waylandmouse.h"
#అన్తర్భావ "SDL_waylandwindow.h"
#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "../../SDL_hints_c.h"
#అన్తర్భావ "SDL_waylandcolor.h"

#అన్తర్భావ "alpha-modifier-v1-client-protocol.h"
#అన్తర్భావ "xdg-shell-client-protocol.h"
#అన్తర్భావ "xdg-decoration-unstable-v1-client-protocol.h"
#అన్తర్భావ "idle-inhibit-unstable-v1-client-protocol.h"
#అన్తర్భావ "xdg-activation-v1-client-protocol.h"
#అన్తర్భావ "viewporter-client-protocol.h"
#అన్తర్భావ "fractional-scale-v1-client-protocol.h"
#అన్తర్భావ "xdg-foreign-unstable-v2-client-protocol.h"
#అన్తర్భావ "xdg-dialog-v1-client-protocol.h"
#అన్తర్భావ "frog-color-management-v1-client-protocol.h"
#అన్తర్భావ "xdg-toplevel-icon-v1-client-protocol.h"
#అన్తర్భావ "color-management-v1-client-protocol.h"
#అన్తర్భావ "xdg-session-management-v1-client-protocol.h"
#అన్తర్భావ "xdg-toplevel-tag-v1-client-protocol.h"

#నిర్వచితమైతే HAVE_LIBDECOR_H
#అన్తర్భావ <libdecor.h>
#అయితే_ముగింపు

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
స్థిర bool Should_ముసుగు_Fullscreen()
{
    స్థిర పూర్ణాంకం ముసుగు_required = -1;

    ఒకవేళ (ముసుగు_required >= 0) {
        తిరిగి ముసుగు_required != 0;
    }

    స్థిరరాశి అక్షరం *desktop = SDL_getenv("XDG_CURRENT_DESKTOP");
    ఒకవేళ (desktop && SDL_strstr(desktop, "KDE") != ఖాళీ) {
        ముసుగు_required = 1;
    } లేకపోతే {
        ముసుగు_required = 0;
    }

    తిరిగి ముసుగు_required != 0;
}

స్థిర ద్విగుణ Get_కిటికీ_Scale(SDL_కిటికీ *కిటికీ)
{
    తిరిగి (కిటికీ->flags & SDL_కిటికీ_ఎగువ_PIXEL_DENSITY) || కిటికీ->అంతర్గత->scale_గమ్యం_display ? కిటికీ->అంతర్గత->scale_గుణకం_2 : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
స్థిర పూర్ణాంకం బిందువు_గమ్యం_Pixel(SDL_కిటికీ *కిటికీ, పూర్ణాంకం బిందువు)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    తిరిగి బిందువు ? SDL_max((పూర్ణాంకం)SDL_lround((ద్విగుణ)బిందువు * Get_కిటికీ_Scale(కిటికీ) + 1e-6), 1) : 0;
}

స్థిర పూర్ణాంకం Pixel_గమ్యం_బిందువు(SDL_కిటికీ *కిటికీ, పూర్ణాంకం pixel)
{
    తిరిగి pixel ? SDL_max((పూర్ణాంకం)SDL_lround((ద్విగుణ)pixel / Get_కిటికీ_Scale(కిటికీ)), 1) : 0;
}

గణన Wayland_బహుళకం_Scale
{
    WAYLAND_బహుళకం_SCALE_UNDEFINED,
    WAYLAND_బహుళకం_SCALE_ASPECT,
    WAYLAND_బహుళకం_SCALE_STRETCH,
    WAYLAND_బహుళకం_SCALE_NONE
};

స్థిర గణన Wayland_బహుళకం_Scale Get_బహుళకం_Scale_పద్ధతి(శూన్య)
{
    స్థిర గణన Wayland_బహుళకం_Scale scale_బహుళకం_2 = WAYLAND_బహుళకం_SCALE_UNDEFINED;

    ఒకవేళ (scale_బహుళకం_2 == WAYLAND_బహుళకం_SCALE_UNDEFINED) {
        స్థిరరాశి అక్షరం *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_బహుళకం_SCALING);

        ఒకవేళ (scale_hint) {
            ఒకవేళ (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_బహుళకం_2 = WAYLAND_బహుళకం_SCALE_STRETCH;
            } లేకపోతే ఒకవేళ (!SDL_strcasecmp(scale_hint, "none")) {
                scale_బహుళకం_2 = WAYLAND_బహుళకం_SCALE_NONE;
            } లేకపోతే {
                scale_బహుళకం_2 = WAYLAND_బహుళకం_SCALE_ASPECT;
            }
        } లేకపోతే {
            scale_బహుళకం_2 = WAYLAND_బహుళకం_SCALE_ASPECT;
        }
    }

    తిరిగి scale_బహుళకం_2;
}

రకనిర్వచనం నిర్మాణం BorderInsets
{
    పూర్ణాంకం ఎడమ;
    పూర్ణాంకం శిఖరం;
    పూర్ణాంకం కుడి;
    పూర్ణాంకం bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
స్థిర శూన్య GetBorderInsets(SDL_కిటికీ *కిటికీ, BorderInsets *insets)
{
    SDL_zerop(insets);
    ఒకవేళ (!కిటికీ->అంతర్గత->enable_insets) {
        తిరిగి;
    }
    ఒకవేళ (కిటికీ->అంతర్గత->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        స్థిరరాశి SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);
        insets->ఎడమ = (పూర్ణాంకం)SDL_clamp(SDL_Get_సంఖ్య_Property(props, SDL_PROP_కిటికీ_WAYLAND_BORDER_INSET_ఎడమ_సంఖ్య, 0), 0, SDL_MAX_SINT16);
        insets->శిఖరం = (పూర్ణాంకం)SDL_clamp(SDL_Get_సంఖ్య_Property(props, SDL_PROP_కిటికీ_WAYLAND_BORDER_INSET_శిఖరం_సంఖ్య, 0), 0, SDL_MAX_SINT16);
        insets->కుడి = (పూర్ణాంకం)SDL_clamp(SDL_Get_సంఖ్య_Property(props, SDL_PROP_కిటికీ_WAYLAND_BORDER_INSET_కుడి_సంఖ్య, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (పూర్ణాంకం)SDL_clamp(SDL_Get_సంఖ్య_Property(props, SDL_PROP_కిటికీ_WAYLAND_BORDER_INSET_BOTTOM_సంఖ్య, 0), 0, SDL_MAX_SINT16);
    }
}

స్థిర శూన్య సమితి_Min_Max_Dimensions(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
    పూర్ణాంకం min_వెడల్పు_2, min_ఎత్తు_2, max_వెడల్పు_2, max_ఎత్తు_2;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    ఒకవేళ (కిటికీ->flags & (SDL_కిటికీ_FULLSCREEN | SDL_కిటికీ_MAXIMIZED)) {
        min_వెడల్పు_2 = 0;
        min_ఎత్తు_2 = 0;
        max_వెడల్పు_2 = 0;
        max_ఎత్తు_2 = 0;
    } లేకపోతే ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_RESIZABLE) {
        పూర్ణాంకం adj_w = SDL_max(కిటికీ->min_w, wind->system_limits.min_వెడల్పు_2);
        పూర్ణాంకం adj_h = SDL_max(కిటికీ->min_h, wind->system_limits.min_ఎత్తు_2);
        ఒకవేళ (wind->scale_గమ్యం_display) {
            adj_w = Pixel_గమ్యం_బిందువు(కిటికీ, adj_w);
            adj_h = Pixel_గమ్యం_బిందువు(కిటికీ, adj_h);
        }
        min_వెడల్పు_2 = adj_w;
        min_ఎత్తు_2 = adj_h;

        adj_w = కిటికీ->max_w ? SDL_max(కిటికీ->max_w, wind->system_limits.min_వెడల్పు_2) : 0;
        adj_h = కిటికీ->max_h ? SDL_max(కిటికీ->max_h, wind->system_limits.min_ఎత్తు_2) : 0;
        ఒకవేళ (wind->scale_గమ్యం_display) {
            adj_w = Pixel_గమ్యం_బిందువు(కిటికీ, adj_w);
            adj_h = Pixel_గమ్యం_బిందువు(కిటికీ, adj_h);
        }
        max_వెడల్పు_2 = adj_w;
        max_ఎత్తు_2 = adj_h;
    } లేకపోతే {
        min_వెడల్పు_2 = wind->current.logical_వెడల్పు;
        min_ఎత్తు_2 = wind->current.logical_ఎత్తు;
        max_వెడల్పు_2 = wind->current.logical_వెడల్పు;
        max_ఎత్తు_2 = wind->current.logical_ఎత్తు;
    }

#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ఒకవేళ (!wind->shell_surface.libdecor.చట్రం) {
            తిరిగి; // Can't do anything yet, wait for ShowWindow
        }

        ఒకవేళ (min_వెడల్పు_2 && min_ఎత్తు_2 && min_వెడల్పు_2 == max_వెడల్పు_2 && min_ఎత్తు_2 == max_ఎత్తు_2) {
            libdecor_చట్రం_unset_capabilities(wind->shell_surface.libdecor.చట్రం, LIBDECOR_ACTION_RESIZE);
        } లేకపోతే {
            libdecor_చట్రం_సమితి_capabilities(wind->shell_surface.libdecor.చట్రం, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        ఒకవేళ (libdecor_చట్రం_has_capability(wind->shell_surface.libdecor.చట్రం, LIBDECOR_ACTION_RESIZE)) {
            libdecor_చట్రం_సమితి_min_content_కొలత(wind->shell_surface.libdecor.చట్రం,
                                                min_వెడల్పు_2,
                                                min_ఎత్తు_2);
            libdecor_చట్రం_సమితి_max_content_కొలత(wind->shell_surface.libdecor.చట్రం,
                                                max_వెడల్పు_2,
                                                max_ఎత్తు_2);
        }
    } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ఒకవేళ (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            తిరిగి; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(కిటికీ, &insets);
        min_వెడల్పు_2 = SDL_max(min_వెడల్పు_2 - (insets.ఎడమ + insets.కుడి), min_వెడల్పు_2 ? 1 : 0);
        min_ఎత్తు_2 = SDL_max(min_ఎత్తు_2 - (insets.శిఖరం + insets.bottom), min_ఎత్తు_2 ? 1 : 0);
        ఒకవేళ (max_వెడల్పు_2) {
            max_వెడల్పు_2 = SDL_max(max_వెడల్పు_2 - (insets.ఎడమ + insets.కుడి), 1);
        }
        ఒకవేళ (max_ఎత్తు_2) {
            max_ఎత్తు_2 = SDL_max(max_ఎత్తు_2 - (insets.శిఖరం + insets.bottom), 1);
        }
        xdg_toplevel_సమితి_min_కొలత(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_వెడల్పు_2,
                                  min_ఎత్తు_2);
        xdg_toplevel_సమితి_max_కొలత(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_వెడల్పు_2,
                                  max_ఎత్తు_2);
    }
}

స్థిర శూన్య EnsurePopupPositionIsValid(SDL_కిటికీ *కిటికీ, పూర్ణాంకం *x, పూర్ణాంకం *y)
{
    పూర్ణాంకం adj_లెక్క = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    ఒకవేళ (*x + కిటికీ->w <= 0) {
        *x = -కిటికీ->w;
        ++adj_లెక్క;
    }
    ఒకవేళ (*y + కిటికీ->h <= 0) {
        *y = -కిటికీ->h;
        ++adj_లెక్క;
    }
    ఒకవేళ (*x >= కిటికీ->మాతృ->w) {
        *x = కిటికీ->మాతృ->w;
        ++adj_లెక్క;
    }
    ఒకవేళ (*y >= కిటికీ->మాతృ->h) {
        *y = కిటికీ->మాతృ->h;
        ++adj_లెక్క;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    ఒకవేళ (adj_లెక్క > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
స్థిర శూన్య Get_కిటికీ_Geometry(SDL_కిటికీ_దత్తాంశం *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    ఒకవేళ (SDL_Rect_ఖాళీలు(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_వెడల్పు;
        geometry->h = wind->current.logical_ఎత్తు;
    }
}

స్థిర శూన్య Adjust_Popup_స్థానభ్రంశం(SDL_కిటికీ *popup, పూర్ణాంకం *x, పూర్ణాంకం *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (popup->మాతృ->అంతర్గత->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        పూర్ణాంకం adj_x, adj_y;
        libdecor_చట్రం_translate_coordinate(popup->మాతృ->అంతర్గత->shell_surface.libdecor.చట్రం,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } లేకపోతే
#అయితే_ముగింపు
    {
        *x -= popup->మాతృ->అంతర్గత->explicit_geometry.x;
        *y -= popup->మాతృ->అంతర్గత->explicit_geometry.y;
    }
}

స్థిర శూన్య RepositionPopup(SDL_కిటికీ *కిటికీ, bool use_current_position)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_సంస్కరణ(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_సంస్కరణ) {
        పూర్ణాంకం x = use_current_position ? కిటికీ->x : కిటికీ->pending.x;
        పూర్ణాంకం y = use_current_position ? కిటికీ->y : కిటికీ->pending.y;

        EnsurePopupPositionIsValid(కిటికీ, &x, &y);
        ఒకవేళ (wind->scale_గమ్యం_display) {
            x = Pixel_గమ్యం_బిందువు(కిటికీ->మాతృ, x);
            y = Pixel_గమ్యం_బిందువు(కిటికీ->మాతృ, y);
        }
        Adjust_Popup_స్థానభ్రంశం(కిటికీ, &x, &y);
        SDL_Rect మాతృ_geometry;
        Get_కిటికీ_Geometry(కిటికీ->మాతృ->అంతర్గత, &మాతృ_geometry);
        xdg_positioner_సమితి_anchor_rect(wind->shell_surface.xdg.popup.xdg_positioner, 0, 0, మాతృ_geometry.w, మాతృ_geometry.h);
        xdg_positioner_సమితి_కొలత(wind->shell_surface.xdg.popup.xdg_positioner, wind->current.logical_వెడల్పు, wind->current.logical_ఎత్తు);
        xdg_positioner_సమితి_స్థానభ్రంశం(wind->shell_surface.xdg.popup.xdg_positioner, x, y);
        xdg_popup_reposition(wind->shell_surface.xdg.popup.xdg_popup,
                             wind->shell_surface.xdg.popup.xdg_positioner,
                             0);
    }
}

స్థిర శూన్య సమితి_Surface_Opaque_Region(నిర్మాణం wl_surface *surface, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు)
{
    SDL_Video_దత్తాంశం *viddata = SDL_GetVideoDevice()->అంతర్గత;

    ఒకవేళ (వెడల్పు && ఎత్తు) {
        నిర్మాణం wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_కూడు(region, 0, 0, వెడల్పు, ఎత్తు);
        wl_surface_సమితి_opaque_region(surface, region);
        wl_region_destroy(region);
    } లేకపోతే {
        wl_surface_సమితి_opaque_region(surface, ఖాళీ);
    }
}

స్థిర శూన్య Configure_కిటికీ_Geometry(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    స్థిరరాశి ద్విగుణ scale_గుణకం_2 = Get_కిటికీ_Scale(కిటికీ);
    స్థిరరాశి ద్విగుణ prev_సూచిక_scale_x = దత్తాంశం->సూచిక_scale.x;
    స్థిరరాశి ద్విగుణ prev_సూచిక_scale_y = దత్తాంశం->సూచిక_scale.y;
    స్థిరరాశి పూర్ణాంకం old_pixel_వెడల్పు = దత్తాంశం->current.pixel_వెడల్పు;
    స్థిరరాశి పూర్ణాంకం old_pixel_ఎత్తు = దత్తాంశం->current.pixel_ఎత్తు;
    పూర్ణాంకం కిటికీ_వెడల్పు = 0;
    పూర్ణాంకం కిటికీ_ఎత్తు = 0;
    పూర్ణాంకం viewport_వెడల్పు, viewport_ఎత్తు;
    bool కిటికీ_కొలత_మారింది;
    bool బఫరు_కొలత_మారింది;
    స్థిరరాశి bool is_opaque = !(కిటికీ->flags & SDL_కిటికీ_TRANSPARENT) && కిటికీ->opacity == 1.0f;

    ఒకవేళ (దత్తాంశం->is_fullscreen && కిటికీ->fullscreen_exclusive) {
        కిటికీ_వెడల్పు = కిటికీ->current_fullscreen_బహుళకం.w;
        కిటికీ_ఎత్తు = కిటికీ->current_fullscreen_బహుళకం.h;

        viewport_వెడల్పు = దత్తాంశం->requested.logical_వెడల్పు;
        viewport_ఎత్తు = దత్తాంశం->requested.logical_ఎత్తు;

        ఎంపిక (Get_బహుళకం_Scale_పద్ధతి()) {
        స్థితి WAYLAND_బహుళకం_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            ఒకవేళ (కిటికీ_వెడల్పు <= viewport_వెడల్పు && కిటికీ_ఎత్తు <= viewport_ఎత్తు) {
                viewport_వెడల్పు = కిటికీ_వెడల్పు;
                viewport_ఎత్తు = కిటికీ_ఎత్తు;

                ఆపు;
            }
            SDL_FALLTHROUGH;
        స్థితి WAYLAND_బహుళకం_SCALE_ASPECT:
        {
            స్థిరరాశి దశాంశం output_నిష్పత్తి = (దశాంశం)viewport_వెడల్పు / (దశాంశం)viewport_ఎత్తు;
            స్థిరరాశి దశాంశం బహుళకం_నిష్పత్తి = (దశాంశం)కిటికీ_వెడల్పు / (దశాంశం)కిటికీ_ఎత్తు;

            ఒకవేళ (output_నిష్పత్తి > బహుళకం_నిష్పత్తి) {
                viewport_వెడల్పు = SDL_lroundf((దశాంశం)కిటికీ_వెడల్పు * ((దశాంశం)viewport_ఎత్తు / (దశాంశం)కిటికీ_ఎత్తు));
            } లేకపోతే ఒకవేళ (output_నిష్పత్తి < బహుళకం_నిష్పత్తి) {
                viewport_ఎత్తు = SDL_lroundf((దశాంశం)కిటికీ_ఎత్తు * ((దశాంశం)viewport_వెడల్పు / (దశాంశం)కిటికీ_వెడల్పు));
            }
        } ఆపు;
        అప్రమేయ:
            ఆపు;
        }

        కిటికీ_కొలత_మారింది = కిటికీ_వెడల్పు != కిటికీ->w ||
                              కిటికీ_ఎత్తు != కిటికీ->h ||
                              దత్తాంశం->current.viewport_వెడల్పు != viewport_వెడల్పు ||
                              దత్తాంశం->current.viewport_ఎత్తు != viewport_ఎత్తు;

        // Exclusive fullscreen window sizes are always in pixel units.
        దత్తాంశం->current.pixel_వెడల్పు = కిటికీ_వెడల్పు;
        దత్తాంశం->current.pixel_ఎత్తు = కిటికీ_ఎత్తు;
        బఫరు_కొలత_మారింది = దత్తాంశం->current.pixel_వెడల్పు != old_pixel_వెడల్పు ||
                              దత్తాంశం->current.pixel_ఎత్తు != old_pixel_ఎత్తు;

        ఒకవేళ (కిటికీ_కొలత_మారింది || బఫరు_కొలత_మారింది) {
            ఒకవేళ (దత్తాంశం->viewport) {
                wp_viewport_సమితి_destination(దత్తాంశం->viewport, viewport_వెడల్పు, viewport_ఎత్తు);

                దత్తాంశం->current.logical_వెడల్పు = దత్తాంశం->requested.logical_వెడల్పు;
                దత్తాంశం->current.logical_ఎత్తు = దత్తాంశం->requested.logical_ఎత్తు;
                దత్తాంశం->current.viewport_వెడల్పు = viewport_వెడల్పు;
                దత్తాంశం->current.viewport_ఎత్తు = viewport_ఎత్తు;
            } లేకపోతే {
                // Calculate the integer scale from the mode and output.
                స్థిరరాశి int32_t int_scale = SDL_max(కిటికీ->current_fullscreen_బహుళకం.w / viewport_వెడల్పు, 1);

                wl_surface_సమితి_బఫరు_scale(దత్తాంశం->surface, int_scale);
                దత్తాంశం->current.logical_వెడల్పు = కిటికీ->current_fullscreen_బహుళకం.w;
                దత్తాంశం->current.logical_ఎత్తు = కిటికీ->current_fullscreen_బహుళకం.h;
            }

            దత్తాంశం->సూచిక_scale.x = (ద్విగుణ)కిటికీ_వెడల్పు / (ద్విగుణ)viewport_వెడల్పు;
            దత్తాంశం->సూచిక_scale.y = (ద్విగుణ)కిటికీ_ఎత్తు / (ద్విగుణ)viewport_ఎత్తు;
        }
    } లేకపోతే {
        ఒకవేళ (!దత్తాంశం->scale_గమ్యం_display) {
            viewport_వెడల్పు = దత్తాంశం->requested.logical_వెడల్పు;
            viewport_ఎత్తు = దత్తాంశం->requested.logical_ఎత్తు;
        } లేకపోతే {
            viewport_వెడల్పు = దత్తాంశం->requested.pixel_వెడల్పు;
            viewport_ఎత్తు = దత్తాంశం->requested.pixel_ఎత్తు;
        }

        ఒకవేళ (!దత్తాంశం->enable_insets &&
            దత్తాంశం->shell_surface_స్థితి != WAYLAND_SHELL_SURFACE_స్థితి_HIDDEN &&
            దత్తాంశం->viewport && దత్తాంశం->wayland_దత్తాంశం->subcompositor && !దత్తాంశం->floating && !దత్తాంశం->is_fullscreen) {
            పూర్ణాంకం min_వెడల్పు_2, min_ఎత్తు_2, max_వెడల్పు_2, max_ఎత్తు_2;
            ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_RESIZABLE) {
                min_వెడల్పు_2 = కిటికీ->min_w;
                min_ఎత్తు_2 = కిటికీ->min_h;
                max_వెడల్పు_2 = కిటికీ->max_w;
                max_ఎత్తు_2 = కిటికీ->max_h;
            } లేకపోతే {
                // Use the fixed size in the odd case where a non-resizable window somehow wound up tiled or maximized.
                min_వెడల్పు_2 = కిటికీ->floating.w;
                min_ఎత్తు_2 = కిటికీ->floating.h;
                max_వెడల్పు_2 = కిటికీ->floating.w;
                max_ఎత్తు_2 = కిటికీ->floating.h;
            }

            ఒకవేళ (min_వెడల్పు_2) {
                viewport_వెడల్పు = SDL_max(viewport_వెడల్పు, min_వెడల్పు_2);
            }
            ఒకవేళ (min_ఎత్తు_2) {
                viewport_ఎత్తు = SDL_max(viewport_ఎత్తు, min_ఎత్తు_2);
            }
            ఒకవేళ (max_వెడల్పు_2) {
                viewport_వెడల్పు = SDL_min(viewport_వెడల్పు, max_వెడల్పు_2);
            }
            ఒకవేళ (max_ఎత్తు_2) {
                viewport_ఎత్తు = SDL_min(viewport_ఎత్తు, max_ఎత్తు_2);
            }

            దశాంశం aspect = (దశాంశం)viewport_వెడల్పు / (దశాంశం)viewport_ఎత్తు;
            ఒకవేళ (కిటికీ->min_aspect != 0.f && aspect < కిటికీ->min_aspect) {
                viewport_ఎత్తు = SDL_max(SDL_lroundf((దశాంశం)viewport_వెడల్పు / కిటికీ->min_aspect), 1);
            } లేకపోతే ఒకవేళ (కిటికీ->max_aspect != 0.f && aspect > కిటికీ->max_aspect) {
                viewport_వెడల్పు = SDL_max(SDL_lroundf((దశాంశం)viewport_ఎత్తు * కిటికీ->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            కిటికీ_వెడల్పు = viewport_వెడల్పు;
            కిటికీ_ఎత్తు = viewport_ఎత్తు;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            ఒకవేళ (!దత్తాంశం->scale_గమ్యం_display) {
                ఒకవేళ (viewport_వెడల్పు > దత్తాంశం->requested.logical_వెడల్పు || viewport_ఎత్తు > దత్తాంశం->requested.logical_ఎత్తు) {
                    aspect = (దశాంశం)viewport_వెడల్పు / (దశాంశం)viewport_ఎత్తు;
                    స్థిరరాశి దశాంశం కిటికీ_నిష్పత్తి = (దశాంశం)దత్తాంశం->requested.logical_వెడల్పు / (దశాంశం)దత్తాంశం->requested.logical_ఎత్తు;
                    ఒకవేళ (aspect >= కిటికీ_నిష్పత్తి) {
                        viewport_వెడల్పు = దత్తాంశం->requested.logical_వెడల్పు;
                        viewport_ఎత్తు = SDL_lroundf((దశాంశం)viewport_వెడల్పు / aspect);
                    } లేకపోతే ఒకవేళ (aspect < కిటికీ_నిష్పత్తి) {
                        viewport_ఎత్తు = దత్తాంశం->requested.logical_ఎత్తు;
                        viewport_వెడల్పు = SDL_lroundf((దశాంశం)viewport_ఎత్తు * aspect);
                    }
                }
            } లేకపోతే {
                ఒకవేళ (viewport_వెడల్పు > దత్తాంశం->requested.pixel_వెడల్పు || viewport_ఎత్తు > దత్తాంశం->requested.pixel_ఎత్తు) {
                    aspect = (దశాంశం)viewport_వెడల్పు / (దశాంశం)viewport_ఎత్తు;
                    స్థిరరాశి దశాంశం కిటికీ_నిష్పత్తి = (దశాంశం)దత్తాంశం->requested.pixel_వెడల్పు / (దశాంశం)దత్తాంశం->requested.pixel_ఎత్తు;
                    ఒకవేళ (aspect >= కిటికీ_నిష్పత్తి) {
                        viewport_వెడల్పు = దత్తాంశం->requested.pixel_వెడల్పు;
                        viewport_ఎత్తు = SDL_lroundf((దశాంశం)viewport_వెడల్పు / aspect);
                    } లేకపోతే ఒకవేళ (aspect < కిటికీ_నిష్పత్తి) {
                        viewport_ఎత్తు = దత్తాంశం->requested.pixel_ఎత్తు;
                        viewport_వెడల్పు = SDL_lroundf((దశాంశం)viewport_ఎత్తు * aspect);
                    }
                }
            }

            viewport_వెడల్పు = SDL_max(viewport_వెడల్పు, 1);
            viewport_ఎత్తు = SDL_max(viewport_ఎత్తు, 1);
        } లేకపోతే {
            కిటికీ_వెడల్పు = viewport_వెడల్పు;
            కిటికీ_ఎత్తు = viewport_ఎత్తు;
        }

        ఒకవేళ (!దత్తాంశం->scale_గమ్యం_display) {
            దత్తాంశం->current.pixel_వెడల్పు = బిందువు_గమ్యం_Pixel(కిటికీ, కిటికీ_వెడల్పు);
            దత్తాంశం->current.pixel_ఎత్తు = బిందువు_గమ్యం_Pixel(కిటికీ, కిటికీ_ఎత్తు);
        } లేకపోతే {
            // The viewport size is in pixels at this point; convert it to logical units.
            దత్తాంశం->current.pixel_వెడల్పు = కిటికీ_వెడల్పు;
            దత్తాంశం->current.pixel_ఎత్తు = కిటికీ_ఎత్తు;
            viewport_వెడల్పు = Pixel_గమ్యం_బిందువు(కిటికీ, viewport_వెడల్పు);
            viewport_ఎత్తు = Pixel_గమ్యం_బిందువు(కిటికీ, viewport_ఎత్తు);
        }

        // Clamp the physical window size to the system minimum required size.
        దత్తాంశం->requested.logical_వెడల్పు = SDL_max(దత్తాంశం->requested.logical_వెడల్పు, దత్తాంశం->system_limits.min_వెడల్పు_2);
        దత్తాంశం->requested.logical_ఎత్తు = SDL_max(దత్తాంశం->requested.logical_ఎత్తు, దత్తాంశం->system_limits.min_ఎత్తు_2);

        కిటికీ_కొలత_మారింది = దత్తాంశం->requested.logical_వెడల్పు != దత్తాంశం->current.logical_వెడల్పు ||
                              దత్తాంశం->requested.logical_ఎత్తు != దత్తాంశం->current.logical_ఎత్తు ||
                              viewport_వెడల్పు != దత్తాంశం->current.viewport_వెడల్పు ||
                              viewport_ఎత్తు != దత్తాంశం->current.viewport_ఎత్తు;

        బఫరు_కొలత_మారింది = దత్తాంశం->current.pixel_వెడల్పు != old_pixel_వెడల్పు ||
                              దత్తాంశం->current.pixel_ఎత్తు != old_pixel_ఎత్తు;

        ఒకవేళ (కిటికీ_కొలత_మారింది || బఫరు_కొలత_మారింది) {
            ఒకవేళ (దత్తాంశం->viewport) {
                wp_viewport_సమితి_destination(దత్తాంశం->viewport, viewport_వెడల్పు, viewport_ఎత్తు);
            } లేకపోతే ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ఎగువ_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_సమితి_బఫరు_scale(దత్తాంశం->surface, (int32_t)scale_గుణకం_2);
            }

            దత్తాంశం->current.logical_వెడల్పు = దత్తాంశం->requested.logical_వెడల్పు;
            దత్తాంశం->current.logical_ఎత్తు = దత్తాంశం->requested.logical_ఎత్తు;
            దత్తాంశం->current.viewport_వెడల్పు = viewport_వెడల్పు;
            దత్తాంశం->current.viewport_ఎత్తు = viewport_ఎత్తు;

            దత్తాంశం->సూచిక_scale.x = (ద్విగుణ)కిటికీ_వెడల్పు / (ద్విగుణ)viewport_వెడల్పు;
            దత్తాంశం->సూచిక_scale.y = (ద్విగుణ)కిటికీ_ఎత్తు / (ద్విగుణ)viewport_ఎత్తు;
        }
    }

    ఒకవేళ (దత్తాంశం->egl_కిటికీ && బఫరు_కొలత_మారింది) {
        WAYLAND_wl_egl_కిటికీ_resize(దత్తాంశం->egl_కిటికీ,
                                     దత్తాంశం->current.pixel_వెడల్పు,
                                     దత్తాంశం->current.pixel_ఎత్తు,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    ఒకవేళ (!దత్తాంశం->enable_insets && దత్తాంశం->viewport && దత్తాంశం->wayland_దత్తాంశం->subcompositor && (!దత్తాంశం->is_fullscreen || Should_ముసుగు_Fullscreen()) &&
        (viewport_వెడల్పు != దత్తాంశం->current.logical_వెడల్పు || viewport_ఎత్తు != దత్తాంశం->current.logical_ఎత్తు)) {
        నిర్మాణం wl_బఫరు *old_బఫరు = ఖాళీ;

        ఒకవేళ (!దత్తాంశం->ముసుగు.surface) {
            దత్తాంశం->ముసుగు.surface = wl_compositor_create_surface(దత్తాంశం->wayland_దత్తాంశం->compositor);
            SDL_WAYLAND_రిజిస్టరు_surface(దత్తాంశం->ముసుగు.surface);
            wl_surface_సమితి_user_దత్తాంశం(దత్తాంశం->ముసుగు.surface, దత్తాంశం);
        }
        ఒకవేళ (!దత్తాంశం->ముసుగు.subsurface) {
            దత్తాంశం->ముసుగు.subsurface = wl_subcompositor_get_subsurface(దత్తాంశం->wayland_దత్తాంశం->subcompositor, దత్తాంశం->ముసుగు.surface, దత్తాంశం->surface);
        }
        ఒకవేళ (!దత్తాంశం->ముసుగు.viewport) {
            దత్తాంశం->ముసుగు.viewport = wp_viewporter_get_viewport(దత్తాంశం->wayland_దత్తాంశం->viewporter, దత్తాంశం->ముసుగు.surface);
        }
        ఒకవేళ (!దత్తాంశం->ముసుగు.బఫరు_2 || దత్తాంశం->ముసుగు.opaque != is_opaque) {
            old_బఫరు = దత్తాంశం->ముసుగు.బఫరు_2;
            దత్తాంశం->ముసుగు.opaque = is_opaque;
            దత్తాంశం->ముసుగు.బఫరు_2 = Wayland_Create_Single_Pixel_బఫరు(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(దత్తాంశం->ముసుగు.surface, దత్తాంశం->ముసుగు.బఫరు_2, 0, 0);

        wl_subsurface_ఉంచు_క్రింద(దత్తాంశం->ముసుగు.subsurface, దత్తాంశం->surface);
        wp_viewport_సమితి_destination(దత్తాంశం->ముసుగు.viewport, దత్తాంశం->current.logical_వెడల్పు, దత్తాంశం->current.logical_ఎత్తు);

        ఒకవేళ (wl_surface_get_సంస్కరణ(దత్తాంశం->ముసుగు.surface) >= WL_SURFACE_DAMAGE_బఫరు_SINCE_సంస్కరణ) {
            wl_surface_damage_బఫరు(దత్తాంశం->ముసుగు.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } లేకపోతే {
            wl_surface_damage(దత్తాంశం->ముసుగు.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        ఒకవేళ (is_opaque) {
            సమితి_Surface_Opaque_Region(దత్తాంశం->ముసుగు.surface, దత్తాంశం->current.logical_వెడల్పు, దత్తాంశం->current.logical_ఎత్తు);
        } లేకపోతే {
            సమితి_Surface_Opaque_Region(దత్తాంశం->ముసుగు.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        ఒకవేళ (దత్తాంశం->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            దత్తాంశం->ముసుగు.స్థానభ్రంశం_x = -(దత్తాంశం->current.logical_వెడల్పు - viewport_వెడల్పు) / 2;
            దత్తాంశం->ముసుగు.స్థానభ్రంశం_y = -(దత్తాంశం->current.logical_ఎత్తు - viewport_ఎత్తు) / 2;
        } లేకపోతే {
            దత్తాంశం->ముసుగు.స్థానభ్రంశం_x = 0;
            దత్తాంశం->ముసుగు.స్థానభ్రంశం_y = 0;
        }

        wl_subsurface_సమితి_position(దత్తాంశం->ముసుగు.subsurface, దత్తాంశం->ముసుగు.స్థానభ్రంశం_x, దత్తాంశం->ముసుగు.స్థానభ్రంశం_y);
        wl_surface_commit(దత్తాంశం->ముసుగు.surface);

        ఒకవేళ (old_బఫరు) {
            wl_బఫరు_destroy(old_బఫరు);
        }

        దత్తాంశం->ముసుగు.mapped = true;
    } లేకపోతే ఒకవేళ (దత్తాంశం->ముసుగు.mapped) {
        wl_subsurface_సమితి_position(దత్తాంశం->ముసుగు.subsurface, 0, 0);
        wl_surface_attach(దత్తాంశం->ముసుగు.surface, ఖాళీ, 0, 0);
        wl_surface_commit(దత్తాంశం->ముసుగు.surface);

        దత్తాంశం->ముసుగు.స్థానభ్రంశం_x = 0;
        దత్తాంశం->ముసుగు.స్థానభ్రంశం_y = 0;
        దత్తాంశం->ముసుగు.mapped = false;
    }

    ఒకవేళ (దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && దత్తాంశం->shell_surface.xdg.surface &&
        (దత్తాంశం->enable_insets || !దత్తాంశం->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(కిటికీ, &insets);
        స్థిరరాశి bool use_insets = (insets.ఎడమ || insets.శిఖరం || insets.కుడి || insets.bottom) &&
                                !(కిటికీ->flags & (SDL_కిటికీ_MAXIMIZED | SDL_కిటికీ_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, దత్తాంశం->current.logical_వెడల్పు, దత్తాంశం->current.logical_ఎత్తు };
        ఒకవేళ (use_insets) {
            geometry.x = insets.ఎడమ;
            geometry.y = insets.శిఖరం;
            geometry.w = SDL_max(geometry.w - (insets.ఎడమ + insets.కుడి), 1);
            geometry.h = SDL_max(geometry.h - (insets.శిఖరం + insets.bottom), 1);
        }
        /* An explicitly set geometry does not track the surface, so it must be kept in sync
         * once set. Otherwise this is only done when viewports aren't supported and the size
         * has changed (XXX: a hack) to avoid a potential protocol violation if a buffer with
         * an old size is committed.
         */
        ఒకవేళ ((use_insets || !SDL_Rect_ఖాళీలు(&దత్తాంశం->explicit_geometry) || (!దత్తాంశం->viewport && కిటికీ_కొలత_మారింది)) &&
            !SDL_RectsEqual(&geometry, &దత్తాంశం->explicit_geometry)) {
            xdg_surface_సమితి_కిటికీ_geometry(దత్తాంశం->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            దత్తాంశం->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    ఒకవేళ (కిటికీ_కొలత_మారింది) {
        ఒకవేళ (is_opaque) {
            సమితి_Surface_Opaque_Region(దత్తాంశం->surface, viewport_వెడల్పు, viewport_ఎత్తు);
        } లేకపోతే {
            సమితి_Surface_Opaque_Region(దత్తాంశం->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        కొరకు (SDL_కిటికీ *బిడ్డ = కిటికీ->మొదటి_బిడ్డ; బిడ్డ; బిడ్డ = బిడ్డ->తదుపరి_sibling) {
            RepositionPopup(బిడ్డ, true);
        }
    }

    // Update the scale for any focused cursors.
    ఒకవేళ (prev_సూచిక_scale_x != దత్తాంశం->సూచిక_scale.x || prev_సూచిక_scale_y != దత్తాంశం->సూచిక_scale.y) {
        Wayland_Display_Update_సూచిక_Focused_Scale(దత్తాంశం);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    సమితి_Min_Max_Dimensions(కిటికీ);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    ఒకవేళ (!దత్తాంశం->scale_గమ్యం_display) {
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, కిటికీ_వెడల్పు, కిటికీ_ఎత్తు);
    } లేకపోతే {
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESIZED, దత్తాంశం->current.pixel_వెడల్పు, దత్తాంశం->current.pixel_ఎత్తు);
    }
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_PIXEL_కొలత_మారింది, దత్తాంశం->current.pixel_వెడల్పు, దత్తాంశం->current.pixel_ఎత్తు);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    ఒకవేళ (దత్తాంశం->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_SHOWN) {
        ఒకవేళ ((బఫరు_కొలత_మారింది || కిటికీ_కొలత_మారింది) ||
            (!దత్తాంశం->suspended && (కిటికీ->flags & SDL_కిటికీ_OCCLUDED))) {
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_EXPOSED, 0, 0);
        }

        ఒకవేళ (దత్తాంశం->suspended) {
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_OCCLUDED, 0, 0);
        }
    }
}

స్థిర శూన్య Commit_Libdecor_చట్రం(SDL_కిటికీ *కిటికీ)
{
#నిర్వచితమైతే HAVE_LIBDECOR_H
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.చట్రం) {
        నిర్మాణం libdecor_state *state = libdecor_state_new(wind->current.logical_వెడల్పు, wind->current.logical_ఎత్తు);
        libdecor_చట్రం_commit(wind->shell_surface.libdecor.చట్రం, state, ఖాళీ);
        libdecor_state_free(state);
    }
#అయితే_ముగింపు
}

స్థిర శూన్య pending_state_deadline_handler(శూన్య *దత్తాంశం, నిర్మాణం wl_callback *callback, uint32_t callback_దత్తాంశం)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_కిటికీ_ID కిటికీ_ID = (SDL_కిటికీ_ID)(uintptr_t)దత్తాంశం;
    SDL_కిటికీ *కిటికీ = SDL_Get_కిటికీ_From_ID(కిటికీ_ID);

    ఒకవేళ (కిటికీ && కిటికీ->అంతర్గత) {
        --కిటికీ->అంతర్గత->pending_state_deadline_లెక్క;
    }

    wl_callback_destroy(callback);
}

స్థిర నిర్మాణం wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

స్థిర శూన్య కూడు_Pending_State_Sync(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2)
{
    SDL_Video_దత్తాంశం *video_దత్తాంశం = కిటికీ_దత్తాంశం_2->wayland_దత్తాంశం;
    శూన్య *cb_దత్తాంశం = (శూన్య *)(uintptr_t)కిటికీ_దత్తాంశం_2->sdlwindow->id;

    ++కిటికీ_దత్తాంశం_2->pending_state_deadline_లెక్క;
    నిర్మాణం wl_callback *cb = wl_display_sync(video_దత్తాంశం->display);
    wl_callback_కూడు_listener(cb, &pending_state_deadline_listener, cb_దత్తాంశం);
}

స్థిర శూన్య FlushPendingEvents(SDL_కిటికీ *కిటికీ)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    స్థిరరాశి bool చివరి_position_pending = కిటికీ->చివరి_position_pending;
    స్థిరరాశి bool చివరి_కొలత_pending = కిటికీ->చివరి_కొలత_pending;

    అయితే (కిటికీ->అంతర్గత->pending_state_deadline_లెక్క) {
        WAYLAND_wl_display_roundtrip(కిటికీ->అంతర్గత->wayland_దత్తాంశం->display);
    }

    కిటికీ->చివరి_position_pending = చివరి_position_pending;
    కిటికీ->చివరి_కొలత_pending = చివరి_కొలత_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
శూన్య Wayland_Update_కిటికీ_Position(SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
    SDL_Display_దత్తాంశం *display;

    ఒకవేళ (wind->outputs && wind->అంకె_outputs) {
        display = wind->outputs[wind->అంకె_outputs - 1];
    } లేకపోతే {
        // A window may not be on any displays if minimized.
        తిరిగి;
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
    wind->చివరి_display_ID = display->display;
    ఒకవేళ (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        ఒకవేళ (!wind->wayland_దత్తాంశం->scale_గమ్యం_display_enabled) {
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_MOVED, display->logical.x, display->logical.y);
        } లేకపోతే {
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_DISPLAY_మారింది, wind->చివరి_display_ID, 0);
    }
}

స్థిర శూన్య సమితి_Fullscreen(SDL_కిటికీ *కిటికీ, నిర్మాణం wl_output *output, bool fullscreen)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ఒకవేళ (!wind->shell_surface.libdecor.చట్రం) {
            తిరిగి; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? కిటికీ->fullscreen_exclusive : false;
        ఒకవేళ (fullscreen) {
            libdecor_చట్రం_సమితి_fullscreen(wind->shell_surface.libdecor.చట్రం, output);
        } లేకపోతే {
            libdecor_చట్రం_unset_fullscreen(wind->shell_surface.libdecor.చట్రం);
        }
    } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ఒకవేళ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ఖాళీ) {
            తిరిగి; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? కిటికీ->fullscreen_exclusive : false;
        ఒకవేళ (fullscreen) {
            xdg_toplevel_సమితి_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } లేకపోతే {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    కూడు_Pending_State_Sync(wind);
}

స్థిర శూన్య Update_కిటికీ_Fullscreen(SDL_కిటికీ *కిటికీ, bool fullscreen)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    wind->is_fullscreen = fullscreen;

    ఒకవేళ (fullscreen) {
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN)) {
            SDL_copyp(&కిటికీ->current_fullscreen_బహుళకం, &కిటికీ->requested_fullscreen_బహుళకం);
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_ENTER_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_బహుళకం(కిటికీ, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            ఒకవేళ (కిటికీ->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(కిటికీ->current_fullscreen_బహుళకం.displayID);
                ఒకవేళ (disp) {
                    wind->fullscreen_was_positioned = true;
                    సమితి_Fullscreen(కిటికీ, disp->అంతర్గత->output, true);
                }
            }
        }
    } లేకపోతే {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) && !కిటికీ->is_hiding && !(కిటికీ->flags & SDL_కిటికీ_HIDDEN)) {
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_LEAVE_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_బహుళకం(కిటికీ, SDL_FULLSCREEN_OP_LEAVE, false);
            wind->fullscreen_was_positioned = false;

            /* Send a move event, in case it was deferred while the fullscreen window was moving and
             * on multiple outputs.
             */
            Wayland_Update_కిటికీ_Position(కిటికీ);
        }
    }
}

స్థిర స్థిరరాశి నిర్మాణం wl_callback_listener surface_చట్రం_listener;

స్థిర శూన్య surface_చట్రం_పూర్తి(శూన్య *దత్తాంశం, నిర్మాణం wl_callback *cb, uint32_t సమయం)
{
    SDL_కిటికీ_దత్తాంశం *wind = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    ఒకవేళ (wl_compositor_get_సంస్కరణ(wind->wayland_దత్తాంశం->compositor) >= WL_SURFACE_DAMAGE_బఫరు_SINCE_సంస్కరణ) {
        wl_surface_damage_బఫరు(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } లేకపోతే {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ఒకవేళ (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            Configure_కిటికీ_Geometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } లేకపోతే {
        wind->resizing = false;
    }

    ఒకవేళ (wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_చట్రం) {
        wind->shell_surface_స్థితి = WAYLAND_SHELL_SURFACE_స్థితి_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        కొరకు (SDL_కిటికీ *w = wind->sdlwindow->మొదటి_బిడ్డ; w; w = w->తదుపరి_sibling) {
            ఒకవేళ (w->అంతర్గత->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_SHOW_PENDING) {
                Wayland_Show_కిటికీ(SDL_GetVideoDevice(), w);
            } లేకపోతే ఒకవేళ (w->అంతర్గత->reparenting_required) {
                Wayland_సమితి_కిటికీ_మాతృ(SDL_GetVideoDevice(), w, w->మాతృ);
                ఒకవేళ (w->flags & SDL_కిటికీ_MODAL) {
                    Wayland_సమితి_కిటికీ_Modal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        ఒకవేళ (wind->suspended) {
            SDL_Send_కిటికీ_Event(wind->sdlwindow, SDL_EVENT_కిటికీ_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_చట్రం_callback = wl_surface_చట్రం(wind->surface);
    wl_callback_కూడు_listener(wind->surface_చట్రం_callback, &surface_చట్రం_listener, దత్తాంశం);
}

స్థిర స్థిరరాశి నిర్మాణం wl_callback_listener surface_చట్రం_listener = {
    surface_చట్రం_పూర్తి
};

స్థిర స్థిరరాశి నిర్మాణం wl_callback_listener gles_మార్పిడి_చట్రం_listener;

స్థిర శూన్య gles_మార్పిడి_చట్రం_పూర్తి(శూన్య *దత్తాంశం, నిర్మాణం wl_callback *cb, uint32_t సమయం)
{
    SDL_కిటికీ_దత్తాంశం *wind = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;
    SDL_సమితి_Atomic_Int(&wind->మార్పిడి_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_మార్పిడి_చట్రం_callback = wl_surface_చట్రం(wind->gles_మార్పిడి_చట్రం_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_కూడు_listener(wind->gles_మార్పిడి_చట్రం_callback, &gles_మార్పిడి_చట్రం_listener, దత్తాంశం);
}

స్థిర స్థిరరాశి నిర్మాణం wl_callback_listener gles_మార్పిడి_చట్రం_listener = {
    gles_మార్పిడి_చట్రం_పూర్తి
};

స్థిర శూన్య handle_xdg_surface_configure(శూన్య *దత్తాంశం, నిర్మాణం xdg_surface *xdg, uint32_t serial)
{
    SDL_కిటికీ_దత్తాంశం *wind = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;
    SDL_కిటికీ *కిటికీ = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    ఒకవేళ (!wind->resizing) {
        wind->pending_config_ack = false;
        Configure_కిటికీ_Geometry(కిటికీ);
        xdg_surface_ack_configure(xdg, serial);
    } లేకపోతే ఒకవేళ (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_EXPOSED, 0, 0);
    }

    ఒకవేళ (wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE) {
        wind->shell_surface_స్థితి = WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_చట్రం;
    }
}

స్థిర స్థిరరాశి నిర్మాణం xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

స్థిర శూన్య ApplyGeometryLimits(SDL_కిటికీ *కిటికీ, పూర్ణాంకం req_w, పూర్ణాంకం req_h, పూర్ణాంకం *బహిర్గతం_w, పూర్ణాంకం *బహిర్గతం_h)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    పూర్ణాంకం w = req_w;
    పూర్ణాంకం h = req_h;
    స్థిరరాశి దశాంశం aspect = (దశాంశం)req_w / (దశాంశం)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    ఒకవేళ (!wind->resizing || (wind->resize_అంచు & WAYLAND_RESIZE_అంచు_మూల) == WAYLAND_RESIZE_అంచు_మూల) {
        ఒకవేళ (కిటికీ->min_aspect != 0.f && aspect < కిటికీ->min_aspect) {
            h = SDL_max(SDL_lroundf((దశాంశం)req_w / కిటికీ->min_aspect), 1);

            ఒకవేళ (h < కిటికీ->min_h) {
                w = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->min_h * కిటికీ->min_aspect), 1);
            }
            ఒకవేళ (కిటికీ->max_h && h > కిటికీ->max_h) {
                w = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->max_h * కిటికీ->min_aspect), 1);
            }
        } లేకపోతే ఒకవేళ (కిటికీ->max_aspect != 0.f && aspect > కిటికీ->max_aspect) {
            w = SDL_max(SDL_lroundf((దశాంశం)req_h * కిటికీ->max_aspect), 1);

            ఒకవేళ (w < కిటికీ->min_w) {
                h = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->min_w / కిటికీ->max_aspect), 1);
            }
            ఒకవేళ (కిటికీ->max_w && w > కిటికీ->max_w) {
                h = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->max_w / కిటికీ->max_aspect), 1);
            }
        }
    } లేకపోతే ఒకవేళ (wind->resize_అంచు & WAYLAND_RESIZE_అంచు_LR) {
        ఒకవేళ (కిటికీ->min_aspect != 0.f && aspect < కిటికీ->min_aspect) {
            h = SDL_max(SDL_lroundf((దశాంశం)req_w / కిటికీ->min_aspect), 1);

            ఒకవేళ (h < కిటికీ->min_h) {
                w = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->min_h * కిటికీ->min_aspect), 1);
            }
            ఒకవేళ (కిటికీ->max_h && h > కిటికీ->max_h) {
                w = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->max_h * కిటికీ->min_aspect), 1);
            }
        } లేకపోతే ఒకవేళ (కిటికీ->max_aspect != 0.f && aspect > కిటికీ->max_aspect) {
            h = SDL_max(SDL_lroundf((దశాంశం)req_w / కిటికీ->max_aspect), 1);

            ఒకవేళ (h < కిటికీ->min_h) {
                w = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->min_h * కిటికీ->max_aspect), 1);
            }
            ఒకవేళ (కిటికీ->max_h && h > కిటికీ->max_h) {
                w = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->max_h * కిటికీ->max_aspect), 1);
            }
        }
    } లేకపోతే ఒకవేళ (wind->resize_అంచు & WAYLAND_RESIZE_అంచు_TB) {
        ఒకవేళ (కిటికీ->min_aspect != 0.f && aspect < కిటికీ->min_aspect) {
            w = SDL_max(SDL_lroundf((దశాంశం)req_h * కిటికీ->min_aspect), 1);

            ఒకవేళ (w < కిటికీ->min_w) {
                h = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->min_w / కిటికీ->min_aspect), 1);
            }
            ఒకవేళ (కిటికీ->max_w && w > కిటికీ->max_w) {
                h = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->max_w / కిటికీ->min_aspect), 1);
            }
        } లేకపోతే ఒకవేళ (కిటికీ->max_aspect != 0.f && aspect > కిటికీ->max_aspect) {
            w = SDL_max(SDL_lroundf((దశాంశం)req_h * కిటికీ->max_aspect), 1);

            ఒకవేళ (w < కిటికీ->min_w) {
                h = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->min_w / కిటికీ->max_aspect), 1);
            }
            ఒకవేళ (కిటికీ->max_w && w > కిటికీ->max_w) {
                h = SDL_max(SDL_lroundf((దశాంశం)కిటికీ->max_w / కిటికీ->max_aspect), 1);
            }
        }
    }

    ఒకవేళ (కిటికీ->max_w) {
        w = SDL_min(w, కిటికీ->max_w);
    }
    *బహిర్గతం_w = SDL_max(w, కిటికీ->min_w);

    ఒకవేళ (కిటికీ->max_h) {
        h = SDL_min(h, కిటికీ->max_h);
    }
    *బహిర్గతం_h = SDL_max(h, కిటికీ->min_h);

}

స్థిర శూన్య DetermineResizeAxis(SDL_కిటికీ_దత్తాంశం *wind, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, bool resizing)
{
    /* Try to determine the axis along which the window is being resized.
     *
     * Every compositor is different, and some will start sending strange values once the resize
     * begins, so only the first change is safe to try and determine the resize edge.
     *
     * Some compositors don't send a configure event with the resize flag cleared when the resize ends,
     * so a reset timer is required.
     */
    ఒకవేళ (resizing) {
        స్థిరరాశి Uint64 now = SDL_GetTicksNS();
        ఒకవేళ (now >= wind->చివరి_resize_event_సమయం_ns + SDL_MS_గమ్యం_NS(500)) {
            wind->resize_అంచు = 0;
        }

        wind->చివరి_resize_event_సమయం_ns = now;

        ఒకవేళ (!wind->resize_అంచు) {
            ఒకవేళ (వెడల్పు != wind->చివరి_configure.వెడల్పు || !ఎత్తు) {
                wind->resize_అంచు |= WAYLAND_RESIZE_అంచు_LR;
            }
            ఒకవేళ (ఎత్తు != wind->చివరి_configure.ఎత్తు || !వెడల్పు) {
                wind->resize_అంచు |= WAYLAND_RESIZE_అంచు_TB;
            }
        }
    } లేకపోతే {
        wind->resize_అంచు = 0;
    }

    wind->resizing = resizing;
}

స్థిర శూన్య handle_xdg_toplevel_configure(శూన్య *దత్తాంశం,
                                          నిర్మాణం xdg_toplevel *xdg_toplevel,
                                          int32_t వెడల్పు,
                                          int32_t ఎత్తు,
                                          నిర్మాణం wl_array *స్థితులు)
{
    SDL_కిటికీ_దత్తాంశం *wind = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;
    SDL_కిటికీ *కిటికీ = wind->sdlwindow;

    గణన xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool చురుకైన = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, స్థితులు) {
        ఎంపిక (*state) {
        స్థితి XDG_TOPLEVEL_STATE_FULLSCREEN:
            fullscreen = true;
            floating = false;
            ఆపు;
        స్థితి XDG_TOPLEVEL_STATE_MAXIMIZED:
            maximized = true;
            floating = false;
            ఆపు;
        స్థితి XDG_TOPLEVEL_STATE_RESIZING:
            resizing = true;
            ఆపు;
        స్థితి XDG_TOPLEVEL_STATE_ACTIVATED:
            చురుకైన = true;
            ఆపు;
        స్థితి XDG_TOPLEVEL_STATE_TILED_ఎడమ:
        స్థితి XDG_TOPLEVEL_STATE_TILED_కుడి:
        స్థితి XDG_TOPLEVEL_STATE_TILED_శిఖరం:
        స్థితి XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            ఆపు;
        స్థితి XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            ఆపు;
        స్థితి XDG_TOPLEVEL_STATE_CONSTRAINED_ఎడమ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ఎడమ;
            ఆపు;
        స్థితి XDG_TOPLEVEL_STATE_CONSTRAINED_కుడి:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_కుడి;
            ఆపు;
        స్థితి XDG_TOPLEVEL_STATE_CONSTRAINED_శిఖరం:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_శిఖరం;
            ఆపు;
        స్థితి XDG_TOPLEVEL_STATE_CONSTRAINED_BOTTOM:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
            ఆపు;
        అప్రమేయ:
            ఆపు;
        }
    }

    /* Configure sizes are in window geometry space; add the border insets, if any, to get
     * the surface size. Maximized and fullscreen windows must use the configured size as-is,
     * so a change in inset applicability requires re-adopting even an unchanged size, and
     * sizes adopted from the cached window size are converted back to geometry space for
     * the last_configure store.
     */
    స్థిరరాశి bool insets_apply = wind->enable_insets && !fullscreen && !maximized;

    // When resizing, dimensions other than 0 are a maximum.
    స్థిరరాశి bool new_configure_కొలత = వెడల్పు != wind->చివరి_configure.వెడల్పు || ఎత్తు != wind->చివరి_configure.ఎత్తు ||
                                    insets_apply != wind->చివరి_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    ఒకవేళ (insets_apply) {
        GetBorderInsets(కిటికీ, &insets);
    }

    DetermineResizeAxis(wind, వెడల్పు, ఎత్తు, resizing);
    Update_కిటికీ_Fullscreen(కిటికీ, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from xdg-shell, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    ఒకవేళ (చురుకైన || !(కిటికీ->flags & SDL_కిటికీ_MINIMIZED)) {
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESTORED, 0, 0);
        }
        SDL_Send_కిటికీ_Event(కిటికీ,
                            (maximized && !fullscreen) ? SDL_EVENT_కిటికీ_MAXIMIZED : SDL_EVENT_కిటికీ_RESTORED,
                            0, 0);
    }

    ఒకవేళ (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_RESIZABLE) || maximized) {
            ఒకవేళ (!వెడల్పు) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                ఒకవేళ (floating) {
                    వెడల్పు = కిటికీ->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ఒకవేళ (wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE && wind->toplevel_bounds.వెడల్పు) {
                        వెడల్పు = SDL_min(wind->toplevel_bounds.వెడల్పు, వెడల్పు);
                    }
                } లేకపోతే {
                    వెడల్పు = కిటికీ->windowed.w;
                }

                ఒకవేళ (!wind->scale_గమ్యం_display) {
                    wind->requested.logical_వెడల్పు = వెడల్పు;
                } లేకపోతే {
                    wind->requested.pixel_వెడల్పు = వెడల్పు;
                    వెడల్పు = wind->requested.logical_వెడల్పు = Pixel_గమ్యం_బిందువు(కిటికీ, వెడల్పు);
                }
                వెడల్పు = SDL_max(వెడల్పు - (insets.ఎడమ + insets.కుడి), 1);
            } లేకపోతే ఒకవేళ (new_configure_కొలత) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_వెడల్పు = వెడల్పు + (insets.ఎడమ + insets.కుడి);

                ఒకవేళ (wind->scale_గమ్యం_display) {
                    wind->requested.pixel_వెడల్పు = బిందువు_గమ్యం_Pixel(కిటికీ, wind->requested.logical_వెడల్పు);
                }
            }
            ఒకవేళ (!ఎత్తు) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                ఒకవేళ (floating) {
                    ఎత్తు = కిటికీ->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ఒకవేళ (wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE && wind->toplevel_bounds.ఎత్తు) {
                        ఎత్తు = SDL_min(wind->toplevel_bounds.ఎత్తు, ఎత్తు);
                    }
                } లేకపోతే {
                    ఎత్తు = కిటికీ->windowed.h;
                }

                ఒకవేళ (!wind->scale_గమ్యం_display) {
                    wind->requested.logical_ఎత్తు = ఎత్తు;
                } లేకపోతే {
                    wind->requested.pixel_ఎత్తు = ఎత్తు;
                    ఎత్తు = wind->requested.logical_ఎత్తు = Pixel_గమ్యం_బిందువు(కిటికీ, ఎత్తు);
                }
                ఎత్తు = SDL_max(ఎత్తు - (insets.శిఖరం + insets.bottom), 1);
            } లేకపోతే ఒకవేళ (new_configure_కొలత) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_ఎత్తు = ఎత్తు + (insets.శిఖరం + insets.bottom);

                ఒకవేళ (wind->scale_గమ్యం_display) {
                    wind->requested.pixel_ఎత్తు = బిందువు_గమ్యం_Pixel(కిటికీ, wind->requested.logical_ఎత్తు);
                }
            }
        } లేకపోతే {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            ఒకవేళ (!wind->scale_గమ్యం_display) {
                వెడల్పు = wind->requested.logical_వెడల్పు = కిటికీ->floating.w;
                ఎత్తు = wind->requested.logical_ఎత్తు = కిటికీ->floating.h;
            } లేకపోతే {
                wind->requested.pixel_వెడల్పు = కిటికీ->floating.w;
                wind->requested.pixel_ఎత్తు = కిటికీ->floating.h;
                వెడల్పు = wind->requested.logical_వెడల్పు = Pixel_గమ్యం_బిందువు(కిటికీ, కిటికీ->floating.w);
                ఎత్తు = wind->requested.logical_ఎత్తు = Pixel_గమ్యం_బిందువు(కిటికీ, కిటికీ->floating.h);
            }
            వెడల్పు = SDL_max(వెడల్పు - (insets.ఎడమ + insets.కుడి), 1);
            ఎత్తు = SDL_max(ఎత్తు - (insets.శిఖరం + insets.bottom), 1);
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
        ఒకవేళ (floating) {
            ఒకవేళ (!wind->scale_గమ్యం_display) {
                ApplyGeometryLimits(కిటికీ, wind->requested.logical_వెడల్పు, wind->requested.logical_ఎత్తు, &wind->requested.logical_వెడల్పు, &wind->requested.logical_ఎత్తు);
            } లేకపోతే {
                ApplyGeometryLimits(కిటికీ, wind->requested.pixel_వెడల్పు, wind->requested.pixel_ఎత్తు, &wind->requested.pixel_వెడల్పు, &wind->requested.pixel_ఎత్తు);

                wind->requested.logical_వెడల్పు = Pixel_గమ్యం_బిందువు(కిటికీ, wind->requested.pixel_వెడల్పు);
                wind->requested.logical_ఎత్తు = Pixel_గమ్యం_బిందువు(కిటికీ, wind->requested.pixel_ఎత్తు);
            }
        }
    } లేకపోతే {
        // Fullscreen windows know their exact size.
        ఒకవేళ (వెడల్పు == 0 || ఎత్తు == 0) {
            వెడల్పు = wind->requested.logical_వెడల్పు;
            ఎత్తు = wind->requested.logical_ఎత్తు;
        } లేకపోతే {
            wind->requested.logical_వెడల్పు = వెడల్పు;
            wind->requested.logical_ఎత్తు = ఎత్తు;
        }

        ఒకవేళ (wind->scale_గమ్యం_display) {
            wind->requested.pixel_వెడల్పు = బిందువు_గమ్యం_Pixel(కిటికీ, వెడల్పు);
            wind->requested.pixel_ఎత్తు = బిందువు_గమ్యం_Pixel(కిటికీ, ఎత్తు);
        }
    }

    wind->చివరి_configure.వెడల్పు = వెడల్పు;
    wind->చివరి_configure.ఎత్తు = ఎత్తు;
    wind->చివరి_configure.insets_apply = insets_apply;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->చురుకైన = చురుకైన;
    కిటికీ->tiled = tiled;
}

స్థిర శూన్య handle_xdg_toplevel_close(శూన్య *దత్తాంశం, నిర్మాణం xdg_toplevel *xdg_toplevel)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;
    SDL_Send_కిటికీ_Event(కిటికీ->sdlwindow, SDL_EVENT_కిటికీ_CLOSE_REQUESTED, 0, 0);
}

స్థిర శూన్య handle_xdg_toplevel_configure_bounds(శూన్య *దత్తాంశం,
                                                 నిర్మాణం xdg_toplevel *xdg_toplevel,
                                                 int32_t వెడల్పు, int32_t ఎత్తు)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;
    కిటికీ->toplevel_bounds.వెడల్పు = వెడల్పు;
    కిటికీ->toplevel_bounds.ఎత్తు = ఎత్తు;
}

స్థిర శూన్య handle_xdg_toplevel_wm_capabilities(శూన్య *దత్తాంశం,
                                                నిర్మాణం xdg_toplevel *xdg_toplevel,
                                                నిర్మాణం wl_array *capabilities)
{
    SDL_కిటికీ_దత్తాంశం *wind = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;
    గణన xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        ఎంపిక (*wm_cap) {
        స్థితి XDG_TOPLEVEL_WM_CAPABILITIES_కిటికీ_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_కిటికీ_MENU;
            ఆపు;
        స్థితి XDG_TOPLEVEL_WM_CAPABILITIES_MAXIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MAXIMIZE;
            ఆపు;
        స్థితి XDG_TOPLEVEL_WM_CAPABILITIES_FULLSCREEN:
            wind->wm_caps |= WAYLAND_WM_CAPS_FULLSCREEN;
            ఆపు;
        స్థితి XDG_TOPLEVEL_WM_CAPABILITIES_MINIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MINIMIZE;
            ఆపు;
        అప్రమేయ:
            ఆపు;
        }
    }
}

స్థిర స్థిరరాశి నిర్మాణం xdg_toplevel_listener toplevel_listener_xdg = {
    handle_xdg_toplevel_configure,
    handle_xdg_toplevel_close,
    handle_xdg_toplevel_configure_bounds, // Version 4
    handle_xdg_toplevel_wm_capabilities   // Version 5
};

స్థిర శూన్య handle_xdg_popup_configure(శూన్య *దత్తాంశం,
                                       నిర్మాణం xdg_popup *xdg_popup,
                                       int32_t x,
                                       int32_t y,
                                       int32_t వెడల్పు,
                                       int32_t ఎత్తు)
{
    SDL_కిటికీ_దత్తాంశం *wind = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;
    పూర్ణాంకం స్థానభ్రంశం_x = 0, స్థానభ్రంశం_y = 0;

    // Adjust the position if it was offset for libdecor
    Adjust_Popup_స్థానభ్రంశం(wind->sdlwindow, &స్థానభ్రంశం_x, &స్థానభ్రంశం_y);
    x -= స్థానభ్రంశం_x;
    y -= స్థానభ్రంశం_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    ఒకవేళ (వెడల్పు == 0 || ఎత్తు == 0) {
        వెడల్పు = wind->sdlwindow->floating.w;
        ఎత్తు = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    ఒకవేళ (వెడల్పు != wind->చివరి_configure.వెడల్పు || ఎత్తు != wind->చివరి_configure.ఎత్తు) {
        wind->requested.logical_వెడల్పు = వెడల్పు;
        wind->requested.logical_ఎత్తు = ఎత్తు;

        ఒకవేళ (wind->scale_గమ్యం_display) {
            wind->requested.pixel_వెడల్పు = బిందువు_గమ్యం_Pixel(wind->sdlwindow, వెడల్పు);
            wind->requested.pixel_ఎత్తు = బిందువు_గమ్యం_Pixel(wind->sdlwindow, ఎత్తు);
        }
    }

    ఒకవేళ (wind->scale_గమ్యం_display) {
        x = బిందువు_గమ్యం_Pixel(wind->sdlwindow->మాతృ, x);
        y = బిందువు_గమ్యం_Pixel(wind->sdlwindow->మాతృ, y);
    }

    SDL_Send_కిటికీ_Event(wind->sdlwindow, SDL_EVENT_కిటికీ_MOVED, x, y);

    wind->చివరి_configure.వెడల్పు = వెడల్పు;
    wind->చివరి_configure.ఎత్తు = ఎత్తు;

    ఒకవేళ (wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE) {
        wind->shell_surface_స్థితి = WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_చట్రం;
    }
}

స్థిర శూన్య handle_xdg_popup_పూర్తి(శూన్య *దత్తాంశం, నిర్మాణం xdg_popup *xdg_popup)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;
    SDL_Send_కిటికీ_Event(కిటికీ->sdlwindow, SDL_EVENT_కిటికీ_CLOSE_REQUESTED, 0, 0);
}

స్థిర శూన్య handle_xdg_popup_repositioned(శూన్య *దత్తాంశం,
                                          నిర్మాణం xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

స్థిర స్థిరరాశి నిర్మాణం xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_పూర్తి,
    handle_xdg_popup_repositioned
};

స్థిర శూన్య handle_xdg_toplevel_decoration_configure(శూన్య *దత్తాంశం,
                                                     నిర్మాణం zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
                                                     uint32_t బహుళకం)
{
    SDL_కిటికీ *కిటికీ = (SDL_కిటికీ *)దత్తాంశం;
    SDL_కిటికీ_దత్తాంశం *అంతర్గత = కిటికీ->అంతర్గత;
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    /* If the compositor tries to force CSD anyway, bail on direct XDG support
     * and fall back to libdecor, it will handle these events from then on.
     *
     * To do this we have to fully unmap, then map with libdecor loaded.
     */
    ఒకవేళ (బహుళకం == ZXDG_TOPLEVEL_DECORATION_V1_బహుళకం_CLIENT_SIDE) {
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            తిరిగి;
        }
        ఒకవేళ (!Wayland_ఎక్కించు_Libdecor(అంతర్గత->wayland_దత్తాంశం, true)) {
            // libdecor isn't available, so no borders for you... oh well
            తిరిగి;
        }
        WAYLAND_wl_display_roundtrip(అంతర్గత->wayland_దత్తాంశం->display);

        Wayland_Hide_కిటికీ(device, కిటికీ);
        అంతర్గత->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_Show_కిటికీ(device, కిటికీ);
    }
}

స్థిర స్థిరరాశి నిర్మాణం zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
    handle_xdg_toplevel_decoration_configure
};

#నిర్వచితమైతే HAVE_LIBDECOR_H
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
స్థిర శూన్య OverrideLibdecorLimits(SDL_కిటికీ *కిటికీ)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    ఒకవేళ (!libdecor_చట్రం_get_min_content_కొలత) {
        libdecor_చట్రం_సమితి_min_content_కొలత(కిటికీ->అంతర్గత->shell_surface.libdecor.చట్రం, కిటికీ->min_w, కిటికీ->min_h);
    }
#లేదావేళ !SDL_LIBDECOR_CHECK_సంస్కరణ(0, 2, 0)
    libdecor_చట్రం_సమితి_min_content_కొలత(కిటికీ->అంతర్గత->shell_surface.libdecor.చట్రం, కిటికీ->min_w, కిటికీ->min_h);
#అయితే_ముగింపు
}

/*
 * NOTE: Retrieves the minimum content size limits, if the function for doing so is available.
 *       On versions of libdecor that lack the minimum content size retrieval function, this
 *       function is a no-op.
 *
 *       Can be replaced with a direct call if the minimum required version of libdecor is raised
 *       to 0.1.2 or higher.
 */
స్థిర శూన్య Libdecor_Get_Min_Content_కొలత(నిర్మాణం libdecor_చట్రం *చట్రం, పూర్ణాంకం *min_w, పూర్ణాంకం *min_h)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    ఒకవేళ (libdecor_చట్రం_get_min_content_కొలత != ఖాళీ) {
        libdecor_చట్రం_get_min_content_కొలత(చట్రం, min_w, min_h);
    }
#లేదావేళ SDL_LIBDECOR_CHECK_సంస్కరణ(0, 2, 0)
    libdecor_చట్రం_get_min_content_కొలత(చట్రం, min_w, min_h);
#అయితే_ముగింపు
}

స్థిర శూన్య decoration_చట్రం_configure(నిర్మాణం libdecor_చట్రం *చట్రం,
                                       నిర్మాణం libdecor_configuration *configuration,
                                       శూన్య *user_దత్తాంశం_2)
{
    SDL_కిటికీ_దత్తాంశం *wind = (SDL_కిటికీ_దత్తాంశం *)user_దత్తాంశం_2;
    SDL_కిటికీ *కిటికీ = wind->sdlwindow;

    గణన libdecor_కిటికీ_state కిటికీ_state;
    పూర్ణాంకం వెడల్పు, ఎత్తు;

    bool చురుకైన = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    స్థిర స్థిరరాశి గణన libdecor_కిటికీ_state tiled_స్థితులు = (LIBDECOR_కిటికీ_STATE_TILED_ఎడమ | LIBDECOR_కిటికీ_STATE_TILED_కుడి |
                                                            LIBDECOR_కిటికీ_STATE_TILED_శిఖరం | LIBDECOR_కిటికీ_STATE_TILED_BOTTOM);

    ఒకవేళ (wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE) {
        Libdecor_Get_Min_Content_కొలత(చట్రం, &wind->system_limits.min_వెడల్పు_2, &wind->system_limits.min_ఎత్తు_2);
    }

    // Window State
    ఒకవేళ (libdecor_configuration_get_కిటికీ_state(configuration, &కిటికీ_state)) {
        fullscreen = (కిటికీ_state & LIBDECOR_కిటికీ_STATE_FULLSCREEN) != 0;
        maximized = (కిటికీ_state & LIBDECOR_కిటికీ_STATE_MAXIMIZED) != 0;
        చురుకైన = (కిటికీ_state & LIBDECOR_కిటికీ_STATE_చురుకైన) != 0;
        tiled = (కిటికీ_state & tiled_స్థితులు) != 0;
#ఒకవేళ SDL_LIBDECOR_CHECK_సంస్కరణ(0, 2, 0)
        suspended = (కిటికీ_state & LIBDECOR_కిటికీ_STATE_SUSPENDED) != 0;
#అయితే_ముగింపు
#ఒకవేళ SDL_LIBDECOR_CHECK_సంస్కరణ(0, 3, 0)
        resizing = (కిటికీ_state & LIBDECOR_కిటికీ_STATE_RESIZING) != 0;

        ఒకవేళ (కిటికీ_state & LIBDECOR_కిటికీ_STATE_CONSTRAINED_ఎడమ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ఎడమ;
        }
        ఒకవేళ (కిటికీ_state & LIBDECOR_కిటికీ_STATE_CONSTRAINED_కుడి) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_కుడి;
        }
        ఒకవేళ (కిటికీ_state & LIBDECOR_కిటికీ_STATE_CONSTRAINED_శిఖరం) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_శిఖరం;
        }
        ఒకవేళ (కిటికీ_state & LIBDECOR_కిటికీ_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#అయితే_ముగింపు
    }
    స్థిరరాశి bool floating = !(fullscreen || maximized || tiled);

    Update_కిటికీ_Fullscreen(కిటికీ, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from libdecor, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    ఒకవేళ (చురుకైన || !(కిటికీ->flags & SDL_కిటికీ_MINIMIZED)) {
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_RESTORED, 0, 0);
        }
        SDL_Send_కిటికీ_Event(కిటికీ,
                            (maximized && !fullscreen) ? SDL_EVENT_కిటికీ_MAXIMIZED : SDL_EVENT_కిటికీ_RESTORED,
                            0, 0);
    }

    /* For fullscreen or fixed-size windows we know our size.
     * Always assume the configure is wrong.
     */
    ఒకవేళ (fullscreen) {
        ఒకవేళ (!libdecor_configuration_get_content_కొలత(configuration, చట్రం, &వెడల్పు, &ఎత్తు)) {
            వెడల్పు = wind->requested.logical_వెడల్పు;
            ఎత్తు = wind->requested.logical_ఎత్తు;
        } లేకపోతే {
            // Fullscreen windows know their exact size.
            wind->requested.logical_వెడల్పు = వెడల్పు;
            wind->requested.logical_ఎత్తు = ఎత్తు;

            ఒకవేళ (wind->scale_గమ్యం_display) {
                wind->requested.pixel_వెడల్పు = బిందువు_గమ్యం_Pixel(కిటికీ, వెడల్పు);
                wind->requested.pixel_ఎత్తు = బిందువు_గమ్యం_Pixel(కిటికీ, ఎత్తు);
            }
        }
    } లేకపోతే {
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            ఒకవేళ (!wind->scale_గమ్యం_display) {
                వెడల్పు = wind->requested.logical_వెడల్పు = కిటికీ->floating.w;
                ఎత్తు = wind->requested.logical_ఎత్తు = కిటికీ->floating.h;
            } లేకపోతే {
                wind->requested.pixel_వెడల్పు = కిటికీ->floating.w;
                wind->requested.pixel_ఎత్తు = కిటికీ->floating.h;
                వెడల్పు = wind->requested.logical_వెడల్పు = Pixel_గమ్యం_బిందువు(కిటికీ, కిటికీ->floating.w);
                ఎత్తు = wind->requested.logical_ఎత్తు = Pixel_గమ్యం_బిందువు(కిటికీ, కిటికీ->floating.h);
            }

            OverrideLibdecorLimits(కిటికీ);
        } లేకపోతే {
            /* XXX: The libdecor cairo plugin sends bogus content sizes that add the
             *      height of the title bar when transitioning from a fixed-size to
             *      floating state. Ignore the sent window dimensions in this case,
             *      in favor of the cached value to avoid the window increasing in
             *      size after every state transition.
             *
             *      https://gitlab.freedesktop.org/libdecor/libdecor/-/issues/34
             */
            ఒకవేళ ((floating && (!wind->floating && !(కిటికీ->flags & SDL_కిటికీ_BORDERLESS))) ||
                !libdecor_configuration_get_content_కొలత(configuration, చట్రం, &వెడల్పు, &ఎత్తు)) {
                వెడల్పు = 0;
                ఎత్తు = 0;
            }

            స్థిరరాశి bool new_configure_కొలత = వెడల్పు != wind->చివరి_configure.వెడల్పు || ఎత్తు != wind->చివరి_configure.ఎత్తు;
            DetermineResizeAxis(wind, వెడల్పు, ఎత్తు, resizing);

            ఒకవేళ (!వెడల్పు) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                ఒకవేళ (floating) {
                    వెడల్పు = కిటికీ->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ఒకవేళ (wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE && wind->toplevel_bounds.వెడల్పు) {
                        వెడల్పు = SDL_min(wind->toplevel_bounds.వెడల్పు, వెడల్పు);
                    }
                } లేకపోతే {
                    వెడల్పు = కిటికీ->windowed.w;
                }

                ఒకవేళ (!wind->scale_గమ్యం_display) {
                    wind->requested.logical_వెడల్పు = వెడల్పు;
                } లేకపోతే {
                    wind->requested.pixel_వెడల్పు = వెడల్పు;
                    వెడల్పు = wind->requested.logical_వెడల్పు = Pixel_గమ్యం_బిందువు(కిటికీ, వెడల్పు);
                }
            } లేకపోతే {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                ఒకవేళ (new_configure_కొలత &&
                    !(wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_చట్రం && wind->suspended != suspended)) {
                    wind->requested.logical_వెడల్పు = వెడల్పు;

                    ఒకవేళ (wind->scale_గమ్యం_display) {
                        wind->requested.pixel_వెడల్పు = బిందువు_గమ్యం_Pixel(కిటికీ, వెడల్పు);
                    }
                }
            }

            ఒకవేళ (!ఎత్తు) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                ఒకవేళ (floating) {
                    ఎత్తు = కిటికీ->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    ఒకవేళ (wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE && wind->toplevel_bounds.ఎత్తు) {
                        ఎత్తు = SDL_min(wind->toplevel_bounds.ఎత్తు, ఎత్తు);
                    }
                } లేకపోతే {
                    ఎత్తు = కిటికీ->windowed.h;
                }

                ఒకవేళ (!wind->scale_గమ్యం_display) {
                    wind->requested.logical_ఎత్తు = ఎత్తు;
                } లేకపోతే {
                    wind->requested.pixel_ఎత్తు = ఎత్తు;
                    ఎత్తు = wind->requested.logical_ఎత్తు = Pixel_గమ్యం_బిందువు(కిటికీ, ఎత్తు);
                }
            } లేకపోతే {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                ఒకవేళ (new_configure_కొలత &&
                    !(wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_చట్రం && wind->suspended != suspended)) {
                    wind->requested.logical_ఎత్తు = ఎత్తు;

                    ఒకవేళ (wind->scale_గమ్యం_display) {
                        wind->requested.pixel_ఎత్తు = బిందువు_గమ్యం_Pixel(కిటికీ, ఎత్తు);
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
        ఒకవేళ (floating) {
            ఒకవేళ (!wind->scale_గమ్యం_display) {
                ApplyGeometryLimits(కిటికీ, wind->requested.logical_వెడల్పు, wind->requested.logical_ఎత్తు, &wind->requested.logical_వెడల్పు, &wind->requested.logical_ఎత్తు);
            } లేకపోతే {
                ApplyGeometryLimits(కిటికీ, wind->requested.pixel_వెడల్పు, wind->requested.pixel_ఎత్తు, &wind->requested.pixel_వెడల్పు, &wind->requested.pixel_ఎత్తు);

                wind->requested.logical_వెడల్పు = Pixel_గమ్యం_బిందువు(కిటికీ, wind->requested.pixel_వెడల్పు);
                wind->requested.logical_ఎత్తు = Pixel_గమ్యం_బిందువు(కిటికీ, wind->requested.pixel_ఎత్తు);
            }
        }
    }

    // Store the new state.
    స్థిరరాశి bool started_resize = !wind->resizing && resizing;
    wind->చివరి_configure.వెడల్పు = వెడల్పు;
    wind->చివరి_configure.ఎత్తు = ఎత్తు;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->చురుకైన = చురుకైన;
    కిటికీ->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#ఒకవేళ SDL_LIBDECOR_CHECK_సంస్కరణ(0, 3, 0)
    గణన libdecor_wm_capabilities caps;
#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    ఒకవేళ (libdecor_చట్రం_get_wm_capabilities) {
        caps = libdecor_చట్రం_get_wm_capabilities(wind->shell_surface.libdecor.చట్రం);
#లేకపోతే
    caps = libdecor_చట్రం_get_wm_capabilities(wind->shell_surface.libdecor.చట్రం);
    {
#అయితే_ముగింపు
        wind->wm_caps = 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_కిటికీ_MENU ? WAYLAND_WM_CAPS_కిటికీ_MENU : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MAXIMIZE ? WAYLAND_WM_CAPS_MAXIMIZE : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_FULLSCREEN ? WAYLAND_WM_CAPS_FULLSCREEN : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MINIMIZE ? WAYLAND_WM_CAPS_MINIMIZE : 0;
    }
#అయితే_ముగింపు

    ఒకవేళ (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        Configure_కిటికీ_Geometry(కిటికీ);
        నిర్మాణం libdecor_state *state = libdecor_state_new(wind->current.logical_వెడల్పు, wind->current.logical_ఎత్తు);
        libdecor_చట్రం_commit(చట్రం, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        ఒకవేళ (started_resize) {
            SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_EXPOSED, 0, 0);
        }
    }

    ఒకవేళ (wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE) {
        wind->shell_surface_స్థితి = WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_చట్రం;
    }
}

స్థిర శూన్య decoration_చట్రం_close(నిర్మాణం libdecor_చట్రం *చట్రం, శూన్య *user_దత్తాంశం_2)
{
    SDL_Send_కిటికీ_Event(((SDL_కిటికీ_దత్తాంశం *)user_దత్తాంశం_2)->sdlwindow, SDL_EVENT_కిటికీ_CLOSE_REQUESTED, 0, 0);
}

స్థిర శూన్య decoration_చట్రం_commit(నిర్మాణం libdecor_చట్రం *చట్రం, శూన్య *user_దత్తాంశం_2)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_కిటికీ_దత్తాంశం *wind = (SDL_కిటికీ_దత్తాంశం *)user_దత్తాంశం_2;
    ఒకవేళ (!wind->suspended && wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_SHOWN) {
        SDL_Send_కిటికీ_Event(wind->sdlwindow, SDL_EVENT_కిటికీ_EXPOSED, 0, 0);
    }
}

స్థిర శూన్య decoration_dismiss_popup(నిర్మాణం libdecor_చట్రం *చట్రం, స్థిరరాశి అక్షరం *seat_name, శూన్య *user_దత్తాంశం_2)
{
    // NOP
}

#ఒకవేళ SDL_LIBDECOR_CHECK_సంస్కరణ(0, 3, 0)
స్థిర శూన్య decoration_చట్రం_bounds(నిర్మాణం libdecor_చట్రం *చట్రం, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, శూన్య *user_దత్తాంశం_2)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = (SDL_కిటికీ_దత్తాంశం *)user_దత్తాంశం_2;
    కిటికీ->toplevel_bounds.వెడల్పు = వెడల్పు;
    కిటికీ->toplevel_bounds.ఎత్తు = ఎత్తు;
}
#అయితే_ముగింపు

స్థిర నిర్మాణం libdecor_చట్రం_interface libdecor_చట్రం_interface = {
    decoration_చట్రం_configure,
    decoration_చట్రం_close,
    decoration_చట్రం_commit,
    decoration_dismiss_popup,
#ఒకవేళ SDL_LIBDECOR_CHECK_సంస్కరణ(0, 3, 0)
    decoration_చట్రం_bounds
#అయితే_ముగింపు
};
#అయితే_ముగింపు

స్థిర శూన్య Wayland_Handle_Preferred_Scale_మారింది(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, ద్విగుణ గుణకం)
{
    స్థిరరాశి ద్విగుణ old_గుణకం = కిటికీ_దత్తాంశం_2->scale_గుణకం_2;

    // Round the scale factor if viewports aren't available.
    ఒకవేళ (!కిటికీ_దత్తాంశం_2->viewport) {
        గుణకం = SDL_ceil(గుణకం);
    }

    ఒకవేళ (గుణకం != old_గుణకం) {
        కిటికీ_దత్తాంశం_2->scale_గుణకం_2 = గుణకం;

        ఒకవేళ (కిటికీ_దత్తాంశం_2->scale_గమ్యం_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            ఒకవేళ (కిటికీ_దత్తాంశం_2->floating) {
                /* Some compositors will send a configure event immediately after a scale event, however,
                 * this event can contain the old logical size, and should be ignored, or the window can
                 * incorrectly change size when moved between displays with differing scale factors.
                 *
                 * Store the last requested logical size as the last configure size, so a configure event
                 * with the old size will be ignored. Configure sizes are in window geometry space,
                 * so subtract any border insets.
                 */
                BorderInsets insets;
                GetBorderInsets(కిటికీ_దత్తాంశం_2->sdlwindow, &insets);
                కిటికీ_దత్తాంశం_2->చివరి_configure.వెడల్పు = SDL_max(కిటికీ_దత్తాంశం_2->requested.logical_వెడల్పు - (insets.ఎడమ + insets.కుడి), 1);
                కిటికీ_దత్తాంశం_2->చివరి_configure.ఎత్తు = SDL_max(కిటికీ_దత్తాంశం_2->requested.logical_ఎత్తు - (insets.శిఖరం + insets.bottom), 1);

                కిటికీ_దత్తాంశం_2->requested.logical_వెడల్పు = Pixel_గమ్యం_బిందువు(కిటికీ_దత్తాంశం_2->sdlwindow, కిటికీ_దత్తాంశం_2->requested.pixel_వెడల్పు);
                కిటికీ_దత్తాంశం_2->requested.logical_ఎత్తు = Pixel_గమ్యం_బిందువు(కిటికీ_దత్తాంశం_2->sdlwindow, కిటికీ_దత్తాంశం_2->requested.pixel_ఎత్తు);
            } లేకపోతే {
                కిటికీ_దత్తాంశం_2->requested.pixel_వెడల్పు = బిందువు_గమ్యం_Pixel(కిటికీ_దత్తాంశం_2->sdlwindow, కిటికీ_దత్తాంశం_2->requested.logical_వెడల్పు);
                కిటికీ_దత్తాంశం_2->requested.pixel_ఎత్తు = బిందువు_గమ్యం_Pixel(కిటికీ_దత్తాంశం_2->sdlwindow, కిటికీ_దత్తాంశం_2->requested.logical_ఎత్తు);
            }
        }

        ఒకవేళ (కిటికీ_దత్తాంశం_2->sdlwindow->flags & SDL_కిటికీ_ఎగువ_PIXEL_DENSITY || కిటికీ_దత్తాంశం_2->scale_గమ్యం_display) {
            Configure_కిటికీ_Geometry(కిటికీ_దత్తాంశం_2->sdlwindow);
            Commit_Libdecor_చట్రం(కిటికీ_దత్తాంశం_2->sdlwindow);
        }
    }
}

స్థిర శూన్య Wayland_Maybe_Update_Scale_గుణకం(SDL_కిటికీ_దత్తాంశం *కిటికీ)
{
    ద్విగుణ గుణకం;
    పూర్ణాంకం i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    ఒకవేళ (కిటికీ->fractional_scale || wl_surface_get_సంస్కరణ(కిటికీ->surface) >= WL_SURFACE_PREFERRED_బఫరు_SCALE_SINCE_సంస్కరణ) {
        తిరిగి;
    }

    ఒకవేళ (కిటికీ->అంకె_outputs != 0) {
        // Check every display's factor, use the highest
        గుణకం = 0.0;
        కొరకు (i = 0; i < కిటికీ->అంకె_outputs; i++) {
            SDL_Display_దత్తాంశం *అంతర్గత = కిటికీ->outputs[i];
            గుణకం = SDL_max(గుణకం, అంతర్గత->scale_గుణకం_2);
        }
    } లేకపోతే {
        // All outputs removed, just fall back.
        గుణకం = కిటికీ->scale_గుణకం_2;
    }

    Wayland_Handle_Preferred_Scale_మారింది(కిటికీ, గుణకం);
}

శూన్య Wayland_Remove_Output_From_కిటికీ(SDL_కిటికీ_దత్తాంశం *కిటికీ, SDL_Display_దత్తాంశం *display_దత్తాంశం)
{
    కొరకు (పూర్ణాంకం i = 0; i < కిటికీ->అంకె_outputs; i++) {
        ఒకవేళ (కిటికీ->outputs[i] == display_దత్తాంశం) { // remove this one
            ఒకవేళ (i == (కిటికీ->అంకె_outputs - 1)) {
                కిటికీ->outputs[i] = ఖాళీ;
            } లేకపోతే {
                SDL_memmove(&కిటికీ->outputs[i],
                            &కిటికీ->outputs[i + 1],
                            పరిమాణం(SDL_Display_దత్తాంశం *) * ((కిటికీ->అంకె_outputs - i) - 1));
            }
            కిటికీ->అంకె_outputs--;
            i--;
        }
    }

    ఒకవేళ (కిటికీ->అంకె_outputs == 0) {
        SDL_free(కిటికీ->outputs);
        కిటికీ->outputs = ఖాళీ;
    } లేకపోతే ఒకవేళ (!కిటికీ->is_fullscreen || కిటికీ->అంకె_outputs == 1) {
        Wayland_Update_కిటికీ_Position(కిటికీ->sdlwindow);
        Wayland_Maybe_Update_Scale_గుణకం(కిటికీ);
    }
}

స్థిర శూన్య handle_surface_enter(శూన్య *దత్తాంశం, నిర్మాణం wl_surface *surface, నిర్మాణం wl_output *output)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = దత్తాంశం;
    SDL_Display_దత్తాంశం *అంతర్గత = wl_output_get_user_దత్తాంశం(output);
    SDL_Display_దత్తాంశం **new_outputs;

    ఒకవేళ (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        తిరిగి;
    }

    new_outputs = SDL_realloc(కిటికీ->outputs,
                              పరిమాణం(SDL_Display_దత్తాంశం *) * (కిటికీ->అంకె_outputs + 1));
    ఒకవేళ (!new_outputs) {
        తిరిగి;
    }
    కిటికీ->outputs = new_outputs;
    కిటికీ->outputs[కిటికీ->అంకె_outputs++] = అంతర్గత;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    ఒకవేళ (!కిటికీ->is_fullscreen || కిటికీ->అంకె_outputs == 1) {
        Wayland_Update_కిటికీ_Position(కిటికీ->sdlwindow);
        Wayland_Maybe_Update_Scale_గుణకం(కిటికీ);
    }
}

స్థిర శూన్య handle_surface_leave(శూన్య *దత్తాంశం, నిర్మాణం wl_surface *surface, నిర్మాణం wl_output *output)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;

    ఒకవేళ (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        తిరిగి;
    }

    Wayland_Remove_Output_From_కిటికీ(కిటికీ, (SDL_Display_దత్తాంశం *)wl_output_get_user_దత్తాంశం(output));
}

స్థిర శూన్య handle_surface_preferred_బఫరు_scale(శూన్య *దత్తాంశం, నిర్మాణం wl_surface *wl_surface, int32_t గుణకం)
{
    SDL_కిటికీ_దత్తాంశం *wind = దత్తాంశం;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    ఒకవేళ (!wind->fractional_scale) {
        Wayland_Handle_Preferred_Scale_మారింది(దత్తాంశం, (ద్విగుణ)గుణకం);
    }
}

స్థిర శూన్య handle_surface_preferred_బఫరు_transform(శూన్య *దత్తాంశం, నిర్మాణం wl_surface *wl_surface, uint32_t transform)
{
    // Nothing to do here.
}

స్థిర స్థిరరాశి నిర్మాణం wl_surface_listener surface_listener = {
    handle_surface_enter,
    handle_surface_leave,
    handle_surface_preferred_బఫరు_scale,
    handle_surface_preferred_బఫరు_transform
};

స్థిర శూన్య handle_fractional_scale_preferred(శూన్య *దత్తాంశం, నిర్మాణం wp_fractional_scale_v1 *wp_fractional_scale_v1, uint32_t scale)
{
    స్థిరరాశి ద్విగుణ గుణకం = (ద్విగుణ)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_Handle_Preferred_Scale_మారింది(దత్తాంశం, గుణకం);
}

స్థిర స్థిరరాశి నిర్మాణం wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

స్థిర శూన్య frog_preferred_metadata_handler(శూన్య *దత్తాంశం, నిర్మాణం frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
                                            uint32_t output_display_primary_red_x, uint32_t output_display_primary_red_y,
                                            uint32_t output_display_primary_green_x, uint32_t output_display_primary_green_y,
                                            uint32_t output_display_primary_blue_x, uint32_t output_display_primary_blue_y,
                                            uint32_t output_white_బిందువు_x, uint32_t output_white_బిందువు_y,
                                            uint32_t max_luminance, uint32_t min_luminance,
                                            uint32_t max_నిండిన_చట్రం_luminance)
{
    SDL_కిటికీ_దత్తాంశం *wind = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;
    SDL_HDROutputProperties HDR;

    SDL_zero(HDR);

    ఎంపిక (transfer_function) {
    స్థితి FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_ST2084_PQ:
        /* ITU-R BT.2408-7 (Sept 2023) has the reference PQ white level at 203 nits,
         * while older Dolby documentation claims a reference level of 100 nits.
         *
         * Use 203 nits for now.
         */
        HDR.HDR_headroom = max_luminance / 203.0f;
        ఆపు;
    స్థితి FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SCRGB_రేఖీయ:
        HDR.HDR_headroom = max_luminance / 80.0f;
        ఆపు;
    స్థితి FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_UNDEFINED:
    స్థితి FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SRGB:
    స్థితి FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_GAMMA_22:
    అప్రమేయ:
        HDR.HDR_headroom = 1.0f;
        ఆపు;
    }

    HDR.SDR_white_level = 1.0f;
    SDL_సమితి_కిటికీ_HDRProperties(wind->sdlwindow, &HDR, true);
}

స్థిర స్థిరరాశి నిర్మాణం frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


స్థిర శూన్య handle_surface_feedback_preferred_changed2(శూన్య *దత్తాంశం,
                                                       నిర్మాణం wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t తటస్థం_hi, uint32_t తటస్థం_lo)
{
    SDL_కిటికీ_దత్తాంశం *wind = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;
    Wayland_Get_Color_Info_For_కిటికీ(wind, false);
}

స్థిర శూన్య handle_surface_feedback_preferred_మారింది(శూన్య *దత్తాంశం,
                                                      నిర్మాణం wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t తటస్థం)
{
    handle_surface_feedback_preferred_changed2(దత్తాంశం, wp_color_management_surface_feedback_v1, 0, తటస్థం);
}

స్థిర స్థిరరాశి నిర్మాణం wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_మారింది,
    handle_surface_feedback_preferred_changed2
};

స్థిర శూన్య Wayland_సమితి_Keyboard_Focus(SDL_కిటికీ *కిటికీ, bool సమితి_focus)
{
    SDL_కిటికీ *toplevel = కిటికీ;

    // Find the toplevel parent
    అయితే (SDL_కిటికీ_IS_POPUP(toplevel)) {
        toplevel = toplevel->మాతృ;
    }

    toplevel->keyboard_focus = కిటికీ;

    ఒకవేళ (సమితి_focus && !కిటికీ->is_hiding && !కిటికీ->is_destroying) {
        SDL_సమితి_Keyboard_Focus(కిటికీ);
    }
}

bool Wayland_సమితి_కిటికీ_తగిలింది_Test(SDL_కిటికీ *కిటికీ, bool enabled)
{
    తిరిగి true; // just succeed, the real work is done elsewhere.
}

స్థిర నిర్మాణం xdg_toplevel *Get_Toplevel_For_కిటికీ(SDL_కిటికీ_దత్తాంశం *wind)
{
    ఒకవేళ (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#నిర్వచితమైతే HAVE_LIBDECOR_H
        ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.చట్రం) {
            తిరిగి libdecor_చట్రం_get_xdg_toplevel(wind->shell_surface.libdecor.చట్రం);
        } లేకపోతే
#అయితే_ముగింపు
            ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                తిరిగి wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    తిరిగి ఖాళీ;
}

bool Wayland_సమితి_కిటికీ_మాతృ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ *మాతృ_కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *బిడ్డ_దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *మాతృ_దత్తాంశం = మాతృ_కిటికీ ? మాతృ_కిటికీ->అంతర్గత : ఖాళీ;

    బిడ్డ_దత్తాంశం->reparenting_required = false;

    ఒకవేళ (మాతృ_దత్తాంశం && మాతృ_దత్తాంశం->shell_surface_స్థితి != WAYLAND_SHELL_SURFACE_స్థితి_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        బిడ్డ_దత్తాంశం->reparenting_required = true;
        తిరిగి true;
    }

    నిర్మాణం xdg_toplevel *బిడ్డ_toplevel = Get_Toplevel_For_కిటికీ(బిడ్డ_దత్తాంశం);
    నిర్మాణం xdg_toplevel *మాతృ_toplevel = Get_Toplevel_For_కిటికీ(మాతృ_దత్తాంశం);

    ఒకవేళ (బిడ్డ_toplevel) {
        xdg_toplevel_సమితి_మాతృ(బిడ్డ_toplevel, మాతృ_toplevel);
    }

    తిరిగి true;
}

bool Wayland_సమితి_కిటికీ_Modal(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool modal)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *మాతృ_దత్తాంశం = కిటికీ->మాతృ->అంతర్గత;

    ఒకవేళ (మాతృ_దత్తాంశం->shell_surface_స్థితి != WAYLAND_SHELL_SURFACE_స్థితి_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        దత్తాంశం->reparenting_required = true;
        తిరిగి true;
    } లేకపోతే {
        దత్తాంశం->reparenting_required = false;
    }

    నిర్మాణం xdg_toplevel *toplevel = Get_Toplevel_For_కిటికీ(దత్తాంశం);

    ఒకవేళ (toplevel) {
        ఒకవేళ (viddata->xdg_wm_dialog_v1) {
            ఒకవేళ (modal) {
                ఒకవేళ (!దత్తాంశం->xdg_dialog_v1) {
                    దత్తాంశం->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_సమితి_modal(దత్తాంశం->xdg_dialog_v1);
            } లేకపోతే ఒకవేళ (దత్తాంశం->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(దత్తాంశం->xdg_dialog_v1);
            }
        }
    }

    తిరిగి true;
}

స్థిర శూన్య Wayland_రిజిస్టరు_Toplevel_For_Session(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    నిర్మాణం xdg_toplevel *toplevel = Get_Toplevel_For_కిటికీ(దత్తాంశం);
    ఒకవేళ (!toplevel) {
        తిరిగి;
    }

    స్థిరరాశి అక్షరం *id = SDL_GetStringProperty(దత్తాంశం->sdlwindow->props, SDL_PROP_కిటికీ_WAYLAND_కిటికీ_ID_STRING, ఖాళీ);
    ఒకవేళ (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_Video_దత్తాంశం *viddata = viddev->అంతర్గత;

        ఒకవేళ (viddata->xdg_toplevel_ట్యాగ్_manager) {
            xdg_toplevel_ట్యాగ్_manager_v1_సమితి_toplevel_ట్యాగ్(viddata->xdg_toplevel_ట్యాగ్_manager, toplevel, id);
        }

        ఒకవేళ (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            ఒకవేళ (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    కొరకు (SDL_కిటికీ *w = viddev->windows; w; w = w->తదుపరి) {
                        SDL_కిటికీ_దత్తాంశం *d = w->అంతర్గత;
                        ఒకవేళ (d->session_id && SDL_strcmp(d->session_id, id) == 0) {
                            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Duplicate window ID string %s found; window will not be added to session", id);
                            తిరిగి;
                        }
                    }
                }

                దత్తాంశం->xdg_toplevel_session = xdg_session_v1_restore_toplevel(viddata->xdg_session, toplevel, id);
                దత్తాంశం->session_id = SDL_strdup(id);
            }
        }
    }
}

స్థిర శూన్య Wayland_DestroyToplevelSession(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    SDL_Video_దత్తాంశం *viddata = దత్తాంశం->wayland_దత్తాంశం;

    ఒకవేళ (దత్తాంశం->xdg_toplevel_session) {
        స్థిరరాశి అక్షరం *id = SDL_GetStringProperty(దత్తాంశం->sdlwindow->props, SDL_PROP_కిటికీ_WAYLAND_కిటికీ_ID_STRING, ఖాళీ);

        // If the ID string was cleared, remove the window from the session.
        ఒకవేళ (!id || *id == '\0') {
            xdg_session_v1_remove_toplevel(viddata->xdg_session, దత్తాంశం->session_id);
        }

        xdg_toplevel_session_v1_destroy(దత్తాంశం->xdg_toplevel_session);
        దత్తాంశం->xdg_toplevel_session = ఖాళీ;

        SDL_free(దత్తాంశం->session_id);
        దత్తాంశం->session_id = ఖాళీ;
    }
}

స్థిర శూన్య show_hide_sync_handler(శూన్య *దత్తాంశం, నిర్మాణం wl_callback *callback, uint32_t callback_దత్తాంశం)
{
    // Get the window from the ID as it may have been destroyed
    SDL_కిటికీ_ID కిటికీ_ID = (SDL_కిటికీ_ID)((uintptr_t)దత్తాంశం);
    SDL_కిటికీ *కిటికీ = SDL_Get_కిటికీ_From_ID(కిటికీ_ID);

    ఒకవేళ (కిటికీ && కిటికీ->అంతర్గత) {
        SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

స్థిర నిర్మాణం wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

స్థిర శూన్య exported_handle_handler(శూన్య *దత్తాంశం, నిర్మాణం zxdg_exported_v2 *zxdg_exported_v2, స్థిరరాశి అక్షరం *handle)
{
    SDL_కిటికీ_దత్తాంశం *wind = (SDL_కిటికీ_దత్తాంశం *)దత్తాంశం;
    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(wind->sdlwindow);

    SDL_సమితి_String_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

స్థిర నిర్మాణం zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

శూన్య Wayland_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *c = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);

    // Custom surfaces don't get toplevels and are always considered 'shown'; nothing to do here.
    ఒకవేళ (దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        తిరిగి;
    }

    /* If this is a child window, the parent *must* be in the final shown state,
     * meaning that it has received a configure event, followed by a frame callback.
     * If not, a race condition can result, with effects ranging from the child
     * window to spuriously closing to protocol errors.
     *
     * If waiting on the parent window, set the pending status and the window will
     * be shown when the parent is in the shown state.
     */
    ఒకవేళ (కిటికీ->మాతృ) {
        ఒకవేళ (కిటికీ->మాతృ->అంతర్గత->shell_surface_స్థితి != WAYLAND_SHELL_SURFACE_స్థితి_SHOWN) {
            దత్తాంశం->shell_surface_స్థితి = WAYLAND_SHELL_SURFACE_స్థితి_SHOW_PENDING;
            తిరిగి;
        }
    }

    // Always roundtrip to ensure there are no pending buffer attachments.
    చేయి {
        WAYLAND_wl_display_roundtrip(c->display);
    } అయితే (దత్తాంశం->show_hide_sync_required);

    దత్తాంశం->shell_surface_స్థితి = WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE;

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
    wl_surface_attach(దత్తాంశం->surface, ఖాళీ, 0, 0);
    wl_surface_commit(దత్తాంశం->surface);

    // Create the shell surface and map the toplevel/popup
#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        దత్తాంశం->shell_surface.libdecor.చట్రం = libdecor_decorate(c->shell.libdecor,
                                                               దత్తాంశం->surface,
                                                               &libdecor_చట్రం_interface,
                                                               దత్తాంశం);
        ఒకవేళ (!దత్తాంశం->shell_surface.libdecor.చట్రం) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } లేకపోతే {
            libdecor_చట్రం_సమితి_app_id(దత్తాంశం->shell_surface.libdecor.చట్రం, దత్తాంశం->app_id);
            libdecor_చట్రం_map(దత్తాంశం->shell_surface.libdecor.చట్రం);
            ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_చట్రం_సమితి_visibility(దత్తాంశం->shell_surface.libdecor.చట్రం, false);
            }

            ఒకవేళ (c->zxdg_exporter_v2) {
                దత్తాంశం->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, దత్తాంశం->surface);
                zxdg_exported_v2_కూడు_listener(దత్తాంశం->exported, &exported_v2_listener, దత్తాంశం);
            }

            ఒకవేళ (c->xdg_toplevel_icon_manager_v1 && దత్తాంశం->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_సమితి_icon(_this->అంతర్గత->xdg_toplevel_icon_manager_v1,
                                                      libdecor_చట్రం_get_xdg_toplevel(దత్తాంశం->shell_surface.libdecor.చట్రం),
                                                      దత్తాంశం->xdg_toplevel_icon_v1);
            }

            SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_SURFACE_సూచిక, libdecor_చట్రం_get_xdg_surface(దత్తాంశం->shell_surface.libdecor.చట్రం));
            SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_TOPLEVEL_సూచిక, libdecor_చట్రం_get_xdg_toplevel(దత్తాంశం->shell_surface.libdecor.చట్రం));
        }
    } లేకపోతే
#అయితే_ముగింపు
    ఒకవేళ (దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        దత్తాంశం->shell_surface.xdg.surface = xdg_wm_పునాది_get_xdg_surface(c->shell.xdg, దత్తాంశం->surface);
        xdg_surface_సమితి_user_దత్తాంశం(దత్తాంశం->shell_surface.xdg.surface, దత్తాంశం);
        xdg_surface_కూడు_listener(దత్తాంశం->shell_surface.xdg.surface, &_xdg_surface_listener, దత్తాంశం);
        SDL_సమితి_సూచిక_Property(SDL_Get_కిటికీ_Properties(కిటికీ), SDL_PROP_కిటికీ_WAYLAND_XDG_SURFACE_సూచిక, దత్తాంశం->shell_surface.xdg.surface);

        ఒకవేళ (దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_కిటికీ *మాతృ = కిటికీ->మాతృ;
            SDL_కిటికీ_దత్తాంశం *మాతృ_దత్తాంశం = మాతృ->అంతర్గత;
            నిర్మాణం xdg_surface *మాతృ_xdg_surface = ఖాళీ;
            పూర్ణాంకం position_x = 0, position_y = 0;

            // Configure the popup parameters
#నిర్వచితమైతే HAVE_LIBDECOR_H
            ఒకవేళ (మాతృ_దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                మాతృ_xdg_surface = libdecor_చట్రం_get_xdg_surface(మాతృ_దత్తాంశం->shell_surface.libdecor.చట్రం);
            } లేకపోతే
#అయితే_ముగింపు
            ఒకవేళ (మాతృ_దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    మాతృ_దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                మాతృ_xdg_surface = మాతృ_దత్తాంశం->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            దత్తాంశం->shell_surface.xdg.popup.xdg_positioner = xdg_wm_పునాది_create_positioner(c->shell.xdg);
            xdg_positioner_సమితి_anchor(దత్తాంశం->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_శిఖరం_ఎడమ);
            SDL_Rect మాతృ_geometry;
            Get_కిటికీ_Geometry(మాతృ->అంతర్గత, &మాతృ_geometry);
            xdg_positioner_సమితి_anchor_rect(దత్తాంశం->shell_surface.xdg.popup.xdg_positioner, 0, 0, మాతృ_geometry.w, మాతృ_geometry.h);

            స్థిరరాశి Uint32 constraint = కిటికీ->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_సమితి_constraint_adjustment(దత్తాంశం->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_సమితి_gravity(దత్తాంశం->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_కుడి);
            xdg_positioner_సమితి_కొలత(దత్తాంశం->shell_surface.xdg.popup.xdg_positioner, దత్తాంశం->current.logical_వెడల్పు, దత్తాంశం->current.logical_ఎత్తు);

            // Set the popup initial position
            position_x = కిటికీ->చివరి_position_pending ? కిటికీ->pending.x : కిటికీ->x;
            position_y = కిటికీ->చివరి_position_pending ? కిటికీ->pending.y : కిటికీ->y;
            EnsurePopupPositionIsValid(కిటికీ, &position_x, &position_y);
            ఒకవేళ (దత్తాంశం->scale_గమ్యం_display) {
                position_x = Pixel_గమ్యం_బిందువు(కిటికీ->మాతృ, position_x);
                position_y = Pixel_గమ్యం_బిందువు(కిటికీ->మాతృ, position_y);
            }
            Adjust_Popup_స్థానభ్రంశం(కిటికీ, &position_x, &position_y);
            xdg_positioner_సమితి_స్థానభ్రంశం(దత్తాంశం->shell_surface.xdg.popup.xdg_positioner, position_x, position_y);

            // Assign the popup role
            దత్తాంశం->shell_surface.xdg.popup.xdg_popup = xdg_surface_get_popup(దత్తాంశం->shell_surface.xdg.surface,
                                                                                మాతృ_xdg_surface,
                                                                                దత్తాంశం->shell_surface.xdg.popup.xdg_positioner);
            xdg_popup_కూడు_listener(దత్తాంశం->shell_surface.xdg.popup.xdg_popup, &_xdg_popup_listener, దత్తాంశం);

            ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_TOOLTIP) {
                నిర్మాణం wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_కూడు(region, 0, 0, 0, 0);
                wl_surface_సమితి_ఆదానం_region(దత్తాంశం->surface, region);
                wl_region_destroy(region);
            } లేకపోతే ఒకవేళ ((కిటికీ->flags & SDL_కిటికీ_POPUP_MENU) && !(కిటికీ->flags & SDL_కిటికీ_NOT_FOCUSABLE)) {
                Wayland_సమితి_Keyboard_Focus(కిటికీ, true);
            }

            SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_POPUP_సూచిక, దత్తాంశం->shell_surface.xdg.popup.xdg_popup);
            SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_POSITIONER_సూచిక, దత్తాంశం->shell_surface.xdg.popup.xdg_positioner);
        } లేకపోతే {
            దత్తాంశం->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(దత్తాంశం->shell_surface.xdg.surface);
            xdg_toplevel_సమితి_app_id(దత్తాంశం->shell_surface.xdg.toplevel.xdg_toplevel, దత్తాంశం->app_id);
            xdg_toplevel_కూడు_listener(దత్తాంశం->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, దత్తాంశం);

            // Create the window decorations
            ఒకవేళ (c->decoration_manager) {
                దత్తాంశం->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, దత్తాంశం->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_కూడు_listener(దత్తాంశం->server_decoration, &xdg_toplevel_decoration_listener, కిటికీ);
                స్థిరరాశి గణన zxdg_toplevel_decoration_v1_బహుళకం బహుళకం = !(కిటికీ->flags & SDL_కిటికీ_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_బహుళకం_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_బహుళకం_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_సమితి_బహుళకం(దత్తాంశం->server_decoration, బహుళకం);
            }

            ఒకవేళ (c->zxdg_exporter_v2) {
                దత్తాంశం->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, దత్తాంశం->surface);
                zxdg_exported_v2_కూడు_listener(దత్తాంశం->exported, &exported_v2_listener, దత్తాంశం);
            }

            ఒకవేళ (c->xdg_toplevel_icon_manager_v1 && దత్తాంశం->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_సమితి_icon(_this->అంతర్గత->xdg_toplevel_icon_manager_v1,
                                                      దత్తాంశం->shell_surface.xdg.toplevel.xdg_toplevel,
                                                      దత్తాంశం->xdg_toplevel_icon_v1);
            }

            SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_TOPLEVEL_సూచిక, దత్తాంశం->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    // Restore state that was set prior to this call
    Wayland_రిజిస్టరు_Toplevel_For_Session(దత్తాంశం);
    Wayland_సమితి_కిటికీ_మాతృ(_this, కిటికీ, కిటికీ->మాతృ);

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_MODAL) {
        Wayland_సమితి_కిటికీ_Modal(_this, కిటికీ, true);
    }

    Wayland_సమితి_కిటికీ_Title(_this, కిటికీ);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ఒకవేళ (దత్తాంశం->shell_surface.libdecor.చట్రం) {
            అయితే (దత్తాంశం->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE) {
                ఒకవేళ (libdecor_dispatch(c->shell.libdecor, -1) < 0) {
                    ఒకవేళ (!Wayland_HandleDisplayDisconnected(_this)) {
                        తిరిగి;
                    }
                }
                ఒకవేళ (WAYLAND_wl_display_dispatch_pending(c->display) < 0) {
                    ఒకవేళ (!Wayland_HandleDisplayDisconnected(_this)) {
                        తిరిగి;
                    }
                }
            }
        }
    } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP || దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Unlike libdecor we need to call this explicitly to prevent a deadlock.
         * libdecor will call this as part of their configure event!
         * -flibit
         */
        wl_surface_commit(దత్తాంశం->surface);
        ఒకవేళ (దత్తాంశం->shell_surface.xdg.surface) {
            అయితే (దత్తాంశం->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE) {
                ఒకవేళ (WAYLAND_wl_display_dispatch(c->display) < 0) {
                    ఒకవేళ (!Wayland_HandleDisplayDisconnected(_this)) {
                        తిరిగి;
                    }
                }
            }
        }
    } లేకపోతే {
        // Nothing to see here, just commit.
        wl_surface_commit(దత్తాంశం->surface);
    }

    // Make sure the window can't be resized to 0, or it can be spuriously closed by the window manager.
    దత్తాంశం->system_limits.min_వెడల్పు_2 = SDL_max(దత్తాంశం->system_limits.min_వెడల్పు_2, 1);
    దత్తాంశం->system_limits.min_ఎత్తు_2 = SDL_max(దత్తాంశం->system_limits.min_ఎత్తు_2, 1);

    /* Unlike the rest of window state we have to set this _after_ flushing the
     * display, because we need to create the decorations before possibly hiding
     * them immediately afterward.
     */
#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        ఒకవేళ (కిటికీ->windowed.w < దత్తాంశం->system_limits.min_వెడల్పు_2 ||
            కిటికీ->windowed.h < దత్తాంశం->system_limits.min_ఎత్తు_2) {

            // Warn if the window frame will be larger than the content surface.
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "Window dimensions (%i, %i) are smaller than the system enforced minimum (%i, %i); window borders will be larger than the content surface.",
                        కిటికీ->windowed.w, కిటికీ->windowed.h, దత్తాంశం->system_limits.min_వెడల్పు_2, దత్తాంశం->system_limits.min_ఎత్తు_2);

            దత్తాంశం->current.logical_వెడల్పు = SDL_max(కిటికీ->windowed.w, దత్తాంశం->system_limits.min_వెడల్పు_2);
            దత్తాంశం->current.logical_ఎత్తు = SDL_max(కిటికీ->windowed.h, దత్తాంశం->system_limits.min_ఎత్తు_2);
            Commit_Libdecor_చట్రం(కిటికీ);
        }
    }
#అయితే_ముగింపు
    Wayland_సమితి_కిటికీ_Resizable(_this, కిటికీ, !!(కిటికీ->flags & SDL_కిటికీ_RESIZABLE));

    // We're finally done putting the window together, raise if possible
    ఒకవేళ (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_కిటికీ_ACTIVATE_WHEN_SHOWN, true)) {
        /* if the process was passed an activation token, use it when showing
         * the initial window.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        స్థిరరాశి అక్షరం *activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
        ఒకవేళ (activation_token) {
            xdg_activation_v1_activate(c->activation_manager,
                                       activation_token,
                                       దత్తాంశం->surface);

            // Clear this variable, per the protocol's request
            SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
        } లేకపోతే {
            // Try to generate an activation token for this window.
            Wayland_Raise_కిటికీ(_this, కిటికీ);
        }
    } లేకపోతే {
        // Clear the ignored activation token, as it won't be used.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    }

    // No frame callback on an external surface, as it may already have one attached.
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        దత్తాంశం->surface_చట్రం_callback = wl_surface_చట్రం(దత్తాంశం->surface);
        wl_callback_కూడు_listener(దత్తాంశం->surface_చట్రం_callback, &surface_చట్రం_listener, దత్తాంశం);
    }

    దత్తాంశం->show_hide_sync_required = true;
    నిర్మాణం wl_callback *cb = wl_display_sync(_this->అంతర్గత->display);
    wl_callback_కూడు_listener(cb, &show_hide_sync_listener, (శూన్య *)((uintptr_t)కిటికీ->id));

    దత్తాంశం->showing_కిటికీ = true;
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_SHOWN, 0, 0);
    దత్తాంశం->showing_కిటికీ = false;

    // Send an exposure event to signal that the client should draw.
    SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_EXPOSED, 0, 0);
}

స్థిర శూన్య Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_కిటికీ *popup)
{
    SDL_కిటికీ_దత్తాంశం *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    ఒకవేళ (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_కిటికీ)) {
        తిరిగి;
    }
    popupdata = popup->అంతర్గత;
    ఒకవేళ (!popupdata) {
        తిరిగి;
    }

    // This may already be freed by a parent popup!
    ఒకవేళ (popupdata->shell_surface.xdg.popup.xdg_popup == ఖాళీ) {
        తిరిగి;
    }

    ఒకవేళ ((popup->flags & SDL_కిటికీ_POPUP_MENU) && !(popup->flags & SDL_కిటికీ_NOT_FOCUSABLE)) {
        SDL_కిటికీ *new_focus;
        స్థిరరాశి bool సమితి_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_సమితి_Keyboard_Focus(new_focus, సమితి_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = ఖాళీ;
    popupdata->shell_surface.xdg.popup.xdg_positioner = ఖాళీ;

    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(popup);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_POPUP_సూచిక, ఖాళీ);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_POSITIONER_సూచిక, ఖాళీ);
}

శూన్య Wayland_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);

    // Custom surfaces have nothing to destroy and are always considered to be 'shown'; nothing to do here.
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        తిరిగి;
    }

    /* The window was shown, but the sync point hasn't yet been reached.
     * Pump events to avoid a possible protocol violation.
     */
    ఒకవేళ (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(దత్తాంశం->display);
    }

    wind->shell_surface_స్థితి = WAYLAND_SHELL_SURFACE_స్థితి_HIDDEN;

    ఒకవేళ (wind->surface_చట్రం_callback) {
        wl_callback_destroy(wind->surface_చట్రం_callback);
        wind->surface_చట్రం_callback = ఖాళీ;
    }

    ఒకవేళ (wind->server_decoration) {
        zxdg_toplevel_decoration_v1_destroy(wind->server_decoration);
        wind->server_decoration = ఖాళీ;
    }

    // Clean up the export handle.
    ఒకవేళ (wind->exported) {
        zxdg_exported_v2_destroy(wind->exported);
        wind->exported = ఖాళీ;

        SDL_సమితి_String_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, ఖాళీ);
    }

    ఒకవేళ (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = ఖాళీ;
    }

#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ఒకవేళ (wind->shell_surface.libdecor.చట్రం) {
            libdecor_చట్రం_unref(wind->shell_surface.libdecor.చట్రం);

            SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_SURFACE_సూచిక, ఖాళీ);
            SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_TOPLEVEL_సూచిక, ఖాళీ);
        }
    } లేకపోతే
#అయితే_ముగింపు
    {
        ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, కిటికీ);
        } లేకపోతే ఒకవేళ (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_TOPLEVEL_సూచిక, ఖాళీ);
        }

        ఒకవేళ (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_XDG_SURFACE_సూచిక, ఖాళీ);
        }
    }

    // Attach a null buffer to unmap the surface.
    ఒకవేళ (wind->ముసుగు.surface) {
        wl_surface_attach(wind->ముసుగు.surface, ఖాళీ, 0, 0);
        wl_surface_commit(wind->ముసుగు.surface);
    }
    wl_surface_attach(wind->surface, ఖాళీ, 0, 0);
    wl_surface_commit(wind->surface);

    // Need to destroy the session object after unmapping the window, or the state may not be saved.
    Wayland_DestroyToplevelSession(wind);

    SDL_zero(wind->shell_surface);
    SDL_zero(wind->explicit_geometry);
    wind->show_hide_sync_required = true;
    నిర్మాణం wl_callback *cb = wl_display_sync(_this->అంతర్గత->display);
    wl_callback_కూడు_listener(cb, &show_hide_sync_listener, (శూన్య *)((uintptr_t)కిటికీ->id));
}

స్థిర శూన్య handle_xdg_activation_పూర్తి(శూన్య *దత్తాంశం,
                                       నిర్మాణం xdg_activation_token_v1 *xdg_activation_token_v1,
                                       స్థిరరాశి అక్షరం *token)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ = దత్తాంశం;
    ఒకవేళ (xdg_activation_token_v1 == కిటికీ->activation_token) {
        xdg_activation_v1_activate(కిటికీ->wayland_దత్తాంశం->activation_manager,
                                   token,
                                   కిటికీ->surface);
        xdg_activation_token_v1_destroy(కిటికీ->activation_token);
        కిటికీ->activation_token = ఖాళీ;
    }
}

స్థిర స్థిరరాశి నిర్మాణం xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_పూర్తి
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
స్థిర శూన్య Wayland_activate_కిటికీ(SDL_Video_దత్తాంశం *దత్తాంశం, SDL_కిటికీ_దత్తాంశం *లక్ష్యం_wind, bool సమితి_serial)
{
    SDL_WaylandSeat *seat = దత్తాంశం->చివరి_implicit_grab_seat;
    SDL_కిటికీ_దత్తాంశం *focus = ఖాళీ;

    ఒకవేళ (seat) {
        focus = seat->keyboard.focus;
        ఒకవేళ (!focus) {
            focus = seat->సూచిక_2.focus;
        }
    }

    నిర్మాణం wl_surface *requesting_surface = focus ? focus->surface : ఖాళీ;

    ఒకవేళ (దత్తాంశం->activation_manager) {
        ఒకవేళ (లక్ష్యం_wind->activation_token) {
            // We're about to overwrite this with a new request
            xdg_activation_token_v1_destroy(లక్ష్యం_wind->activation_token);
        }

        లక్ష్యం_wind->activation_token = xdg_activation_v1_get_activation_token(దత్తాంశం->activation_manager);
        xdg_activation_token_v1_కూడు_listener(లక్ష్యం_wind->activation_token,
                                             &xdg_activation_listener,
                                             లక్ష్యం_wind);

        /* Note that we are not setting the app_id here.
         *
         * Hypothetically we could set the app_id from data->classname, but
         * that part of the API is for _external_ programs, not ourselves.
         *
         * -flibit
         */
        ఒకవేళ (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_సమితి_surface(లక్ష్యం_wind->activation_token, requesting_surface);
        }
        ఒకవేళ (సమితి_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_సమితి_serial(లక్ష్యం_wind->activation_token, seat->చివరి_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(లక్ష్యం_wind->activation_token);
    }
}

శూన్య Wayland_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    ఒకవేళ (viddata->activation_manager) {
        /* Check for an activation token, in case the window is being
         * raised in response to a system notification.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        స్థిరరాశి అక్షరం *activation_token = SDL_GetNotificationActivationToken();
        ఒకవేళ (activation_token) {
            xdg_activation_v1_activate(viddata->activation_manager,
                                       activation_token,
                                       wind->surface);
            తిరిగి;
        }
    }

    // No token? Try to activate the window via an event serial.
    Wayland_activate_కిటికీ(_this->అంతర్గత, కిటికీ->అంతర్గత, true);
}

bool Wayland_Flash_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_FlashOperation operation)
{
    /* Not setting the serial will specify 'urgency' without switching focus as per
     * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
     */
    Wayland_activate_కిటికీ(_this->అంతర్గత, కిటికీ->అంతర్గత, false);
    తిరిగి true;
}

SDL_Fullscreen_ఫలితం Wayland_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
    నిర్మాణం wl_output *output = display->అంతర్గత->output;

    // Custom surfaces have no toplevel to make fullscreen.
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        తిరిగి SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    ఒకవేళ (wind->showing_కిటికీ && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        తిరిగి SDL_FULLSCREEN_SUCCEEDED;
    }

    ఒకవేళ (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->అంతర్గత->display);
    }

    // Flushing old events pending a new one, ignore this request.
    ఒకవేళ (wind->drop_fullscreen_అభ్యర్థనలు) {
        తిరిగి SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_అభ్యర్థనలు = true;
    FlushPendingEvents(కిటికీ);
    wind->drop_fullscreen_అభ్యర్థనలు = false;

    // Nothing to do if the window is not fullscreen, and this isn't an explicit enter request.
    ఒకవేళ (!wind->is_fullscreen) {
        ఒకవేళ (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
            // Request was out of date; signal the video core not to update any state.
            తిరిగి SDL_FULLSCREEN_PENDING;
        } లేకపోతే ఒకవేళ (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
            // Already not fullscreen; nothing to do.
            తిరిగి SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    // Don't send redundant fullscreen set/unset events.
    ఒకవేళ (!!fullscreen != wind->is_fullscreen) {
        wind->fullscreen_was_positioned = !!fullscreen;

        /* Only use the specified output if an exclusive mode is being used, or a position was explicitly requested
         * before entering fullscreen desktop. Otherwise, let the compositor handle placement, as it has more
         * information about where the window is and where it should go, particularly if fullscreen is being requested
         * before the window is mapped, or the window spans multiple outputs.
         */
        ఒకవేళ (!కిటికీ->fullscreen_exclusive) {
            ఒకవేళ (కిటికీ->undefined_x || కిటికీ->undefined_y ||
                (wind->అంకె_outputs && !కిటికీ->చివరి_position_pending)) {
                output = ఖాళీ;
            }
        }

        // Commit to set any pending size or limit data.
        ఒకవేళ (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        సమితి_Fullscreen(కిటికీ, output, !!fullscreen);
    } లేకపోతే ఒకవేళ (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        ఒకవేళ (wind->చివరి_display_ID != display->id) {
            wind->fullscreen_was_positioned = true;
            సమితి_Fullscreen(కిటికీ, output, true);
        } లేకపోతే {
            Configure_కిటికీ_Geometry(కిటికీ);
            Commit_Libdecor_చట్రం(కిటికీ);

            తిరిగి SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    తిరిగి SDL_FULLSCREEN_PENDING;
}

శూన్య Wayland_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    // Drop restore requests when showing the window.
    ఒకవేళ (wind->showing_కిటికీ) {
        తిరిగి;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    ఒకవేళ (!(కిటికీ->flags & (SDL_కిటికీ_FULLSCREEN | SDL_కిటికీ_MAXIMIZED)) &&
        !wind->pending_state_deadline_లెక్క) {
        తిరిగి;
    }

#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ఒకవేళ (!wind->shell_surface.libdecor.చట్రం) {
            తిరిగి; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_చట్రం_unset_maximized(wind->shell_surface.libdecor.చట్రం);
        కూడు_Pending_State_Sync(wind);
    } లేకపోతే
#అయితే_ముగింపు
        // Note that xdg-shell does NOT provide a way to unset minimize!
        ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            ఒకవేళ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ఖాళీ) {
                తిరిగి; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            కూడు_Pending_State_Sync(wind);
        }
}

శూన్య Wayland_సమితి_కిటికీ_Bordered(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool bordered)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
    స్థిరరాశి SDL_Video_దత్తాంశం *viddata = (స్థిరరాశి SDL_Video_దత్తాంశం *)_this->అంతర్గత;

#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ఒకవేళ (wind->shell_surface.libdecor.చట్రం) {
            libdecor_చట్రం_సమితి_visibility(wind->shell_surface.libdecor.చట్రం, bordered);
        }
    } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ఒకవేళ ((viddata->decoration_manager) && (wind->server_decoration)) {
            స్థిరరాశి గణన zxdg_toplevel_decoration_v1_బహుళకం బహుళకం = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_బహుళకం_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_బహుళకం_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_సమితి_బహుళకం(wind->server_decoration, బహుళకం);
        }
    }
}

శూన్య Wayland_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    సమితి_Min_Max_Dimensions(కిటికీ);
    Commit_Libdecor_చట్రం(కిటికీ);

    ఒకవేళ (wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_SHOWN) {
        wind->pending_state_commit = true;
    }
}

శూన్య Wayland_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    ఒకవేళ (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->అంతర్గత->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) && (కిటికీ->flags & SDL_కిటికీ_MAXIMIZED) &&
        !wind->pending_state_deadline_లెక్క) {
        తిరిగి;
    }

#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ఒకవేళ (!wind->shell_surface.libdecor.చట్రం) {
            తిరిగి; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        ఒకవేళ (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_చట్రం_సమితి_maximized(wind->shell_surface.libdecor.చట్రం);
        కూడు_Pending_State_Sync(wind);
    } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ఒకవేళ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ఖాళీ) {
            తిరిగి; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        ఒకవేళ (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_సమితి_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        కూడు_Pending_State_Sync(wind);
    }
}

శూన్య Wayland_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    ఒకవేళ (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        తిరిగి;
    }

#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ఒకవేళ (!wind->shell_surface.libdecor.చట్రం) {
            తిరిగి; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_చట్రం_సమితి_minimized(wind->shell_surface.libdecor.చట్రం);
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_MINIMIZED, 0, 0);
    } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ఒకవేళ (wind->shell_surface.xdg.toplevel.xdg_toplevel == ఖాళీ) {
            తిరిగి; // Can't do anything yet, wait for ShowWindow
        }
        xdg_toplevel_సమితి_minimized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        SDL_Send_కిటికీ_Event(కిటికీ, SDL_EVENT_కిటికీ_MINIMIZED, 0, 0);
    }
}

bool Wayland_సమితి_కిటికీ_Mouse_Rect(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    /* This may look suspiciously like SetWindowGrab, despite SetMouseRect not
     * implicitly doing a grab. And you're right! Wayland doesn't let us mess
     * around with mouse focus whatsoever, so it just happens to be that the
     * work that we can do in these two functions ends up being the same.
     *
     * Just know that this call lets you confine with a rect, SetWindowGrab
     * lets you confine without a rect.
     */
    ఒకవేళ (!దత్తాంశం->సూచిక_constraints) {
        తిరిగి SDL_సమితి_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_సూచిక_Grabs(దత్తాంశం, కిటికీ->అంతర్గత);
    తిరిగి true;
}

bool Wayland_సమితి_కిటికీ_Mouse_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    ఒకవేళ (!దత్తాంశం->సూచిక_constraints) {
        తిరిగి SDL_సమితి_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_Display_Update_సూచిక_Grabs(దత్తాంశం, కిటికీ->అంతర్గత);
    తిరిగి true;
}

bool Wayland_సమితి_కిటికీ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    ఒకవేళ (!దత్తాంశం->కీలకం_inhibitor_manager) {
        తిరిగి SDL_సమితి_Error("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(దత్తాంశం, కిటికీ->అంతర్గత);
    తిరిగి true;
}

bool Wayland_Reconfigure_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ_Flags flags)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    // Don't try to reconfigure mapped windows, unless they are custom or external.
    ఒకవేళ (దత్తాంశం->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_SHOWN &&
        దత్తాంశం->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        // Window is already mapped; abort.
        తిరిగి false;
    }

    /* The caller guarantees that only one of the GL or Vulkan flags will be set.
     * Note that Vulkan doesn't require any specific configuration, so only EGL
     * objects are added and removed as required.
     */
    ఒకవేళ (flags & SDL_కిటికీ_OPENGL) {
        ఒకవేళ (!దత్తాంశం->egl_కిటికీ) {
            దత్తాంశం->egl_కిటికీ = WAYLAND_wl_egl_కిటికీ_create(దత్తాంశం->surface, దత్తాంశం->current.pixel_వెడల్పు, దత్తాంశం->current.pixel_ఎత్తు);
        }

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
        దత్తాంశం->egl_surface = SDL_EGL_CreateSurface(_this, కిటికీ, (Native_కిటికీ_Type)దత్తాంశం->egl_కిటికీ);

        ఒకవేళ (దత్తాంశం->egl_surface == EGL_NO_SURFACE) {
            తిరిగి false; // SDL_EGL_CreateSurface should have set the error.
        }
#అయితే_ముగింపు

        ఒకవేళ (!దత్తాంశం->gles_మార్పిడి_చట్రం_event_వరుస) {
            దత్తాంశం->gles_మార్పిడి_చట్రం_event_వరుస = WAYLAND_wl_display_create_వరుస(దత్తాంశం->wayland_దత్తాంశం->display);
            దత్తాంశం->gles_మార్పిడి_చట్రం_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(దత్తాంశం->surface);
            WAYLAND_wl_proxy_సమితి_వరుస((నిర్మాణం wl_proxy *)దత్తాంశం->gles_మార్పిడి_చట్రం_surface_wrapper, దత్తాంశం->gles_మార్పిడి_చట్రం_event_వరుస);
            దత్తాంశం->gles_మార్పిడి_చట్రం_callback = wl_surface_చట్రం(దత్తాంశం->gles_మార్పిడి_చట్రం_surface_wrapper);
            wl_callback_కూడు_listener(దత్తాంశం->gles_మార్పిడి_చట్రం_callback, &gles_మార్పిడి_చట్రం_listener, దత్తాంశం);
        }
    } లేకపోతే {
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
        ఒకవేళ (దత్తాంశం->egl_surface) {
            SDL_EGL_DestroySurface(_this, దత్తాంశం->egl_surface);
            దత్తాంశం->egl_surface = EGL_NO_SURFACE;
        }
#అయితే_ముగింపు

        ఒకవేళ (దత్తాంశం->egl_కిటికీ) {
            WAYLAND_wl_egl_కిటికీ_destroy(దత్తాంశం->egl_కిటికీ);
            దత్తాంశం->egl_కిటికీ = ఖాళీ;
        }

        ఒకవేళ (దత్తాంశం->gles_మార్పిడి_చట్రం_callback) {
            wl_callback_destroy(దత్తాంశం->gles_మార్పిడి_చట్రం_callback);
            దత్తాంశం->gles_మార్పిడి_చట్రం_callback = ఖాళీ;
        }

        ఒకవేళ (దత్తాంశం->gles_మార్పిడి_చట్రం_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(దత్తాంశం->gles_మార్పిడి_చట్రం_surface_wrapper);
            దత్తాంశం->gles_మార్పిడి_చట్రం_surface_wrapper = ఖాళీ;
        }

        ఒకవేళ (దత్తాంశం->gles_మార్పిడి_చట్రం_event_వరుస) {
            WAYLAND_wl_event_వరుస_destroy(దత్తాంశం->gles_మార్పిడి_చట్రం_event_వరుస);
            దత్తాంశం->gles_మార్పిడి_చట్రం_event_వరుస = ఖాళీ;
        }
    }

    తిరిగి true;
}

bool Wayland_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం;
    SDL_Video_దత్తాంశం *c = _this->అంతర్గత;
    నిర్మాణం wl_surface *external_surface = (నిర్మాణం wl_surface *)SDL_Get_సూచిక_Property(create_props, SDL_PROP_కిటికీ_CREATE_WAYLAND_WL_SURFACE_సూచిక,
                                                                               (నిర్మాణం wl_surface *)SDL_Get_సూచిక_Property(create_props, "sdl2-compat.external_window", ఖాళీ));
    స్థిరరాశి bool custom_surface_role = (external_surface != ఖాళీ) || SDL_GetBooleanProperty(create_props, SDL_PROP_కిటికీ_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    స్థిరరాశి bool create_egl_కిటికీ = !!(కిటికీ->flags & SDL_కిటికీ_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_కిటికీ_CREATE_WAYLAND_CREATE_EGL_కిటికీ_BOOLEAN, false);

    దత్తాంశం = SDL_calloc(1, పరిమాణం(*దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        తిరిగి false;
    }

    కిటికీ->అంతర్గత = దత్తాంశం;
    దత్తాంశం->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_కిటికీ_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    ఒకవేళ (కిటికీ->x == SDL_WINDOWPOS_UNDEFINED) {
        కిటికీ->x = 0;
    }
    ఒకవేళ (కిటికీ->y == SDL_WINDOWPOS_UNDEFINED) {
        కిటికీ->y = 0;
    }

    దత్తాంశం->wayland_దత్తాంశం = c;
    దత్తాంశం->sdlwindow = కిటికీ;

    // Default to all capabilities
    దత్తాంశం->wm_caps = WAYLAND_WM_CAPS_ALL;

    దత్తాంశం->scale_గుణకం_2 = 1.0;

    ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ)) {
        దత్తాంశం->scale_గమ్యం_display = కిటికీ->మాతృ->అంతర్గత->scale_గమ్యం_display;
        దత్తాంశం->scale_గుణకం_2 = కిటికీ->మాతృ->అంతర్గత->scale_గుణకం_2;
        EnsurePopupPositionIsValid(కిటికీ, &కిటికీ->x, &కిటికీ->y);
    } లేకపోతే {
        కొరకు (పూర్ణాంకం i = 0; i < _this->అంకె_displays; i++) {
            దత్తాంశం->scale_గుణకం_2 = SDL_max(దత్తాంశం->scale_గుణకం_2, _this->displays[i]->అంతర్గత->scale_గుణకం_2);
        }
    }

    దత్తాంశం->outputs = ఖాళీ;
    దత్తాంశం->అంకె_outputs = 0;
    దత్తాంశం->scale_గమ్యం_display = c->scale_గమ్యం_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    దత్తాంశం->app_id = SDL_strdup(SDL_GetAppID());

    ఒకవేళ (!దత్తాంశం->scale_గమ్యం_display) {
        దత్తాంశం->requested.logical_వెడల్పు = కిటికీ->floating.w;
        దత్తాంశం->requested.logical_ఎత్తు = కిటికీ->floating.h;
    } లేకపోతే {
        దత్తాంశం->requested.logical_వెడల్పు = Pixel_గమ్యం_బిందువు(కిటికీ, కిటికీ->floating.w);
        దత్తాంశం->requested.logical_ఎత్తు = Pixel_గమ్యం_బిందువు(కిటికీ, కిటికీ->floating.h);
        దత్తాంశం->requested.pixel_వెడల్పు = కిటికీ->floating.w;
        దత్తాంశం->requested.pixel_ఎత్తు = కిటికీ->floating.h;
    }

    ఒకవేళ (!external_surface) {
        దత్తాంశం->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_కూడు_listener(దత్తాంశం->surface, &surface_listener, దత్తాంశం);
        wl_surface_సమితి_user_దత్తాంశం(దత్తాంశం->surface, దత్తాంశం);
        SDL_WAYLAND_రిజిస్టరు_surface(దత్తాంశం->surface);
    } లేకపోతే {
        కిటికీ->flags |= SDL_కిటికీ_EXTERNAL;
        దత్తాంశం->surface = external_surface;

        /* External surfaces are registered by being put in a list, as changing tags or userdata
         * can cause problems with external toolkits.
         */
        Wayland_కూడు_కిటికీ_దత్తాంశం_గమ్యం_External_List(దత్తాంశం);
    }

    /* Always attach a viewport and fractional scale manager if available and the surface is not custom/external,
     * or the custom/external surface was explicitly flagged as high pixel density aware, which signals that the
     * application wants SDL to handle scaling.
     */
    ఒకవేళ (!custom_surface_role || (కిటికీ->flags & SDL_కిటికీ_ఎగువ_PIXEL_DENSITY)) {
        ఒకవేళ (c->viewporter) {
            దత్తాంశం->viewport = wp_viewporter_get_viewport(c->viewporter, దత్తాంశం->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_సమితి_ఆధారం(దత్తాంశం->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        ఒకవేళ (c->fractional_scale_manager) {
            దత్తాంశం->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, దత్తాంశం->surface);
            wp_fractional_scale_v1_కూడు_listener(దత్తాంశం->fractional_scale, &fractional_scale_listener, దత్తాంశం);
        }
    }

    ఒకవేళ (!custom_surface_role) {
        ఒకవేళ (c->wp_color_manager_v1) {
            దత్తాంశం->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, దత్తాంశం->surface);
            wp_color_management_surface_feedback_v1_కూడు_listener(దత్తాంశం->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, దత్తాంశం);
            Wayland_Get_Color_Info_For_కిటికీ(దత్తాంశం, true);
        } లేకపోతే ఒకవేళ (c->frog_color_management_factory_v1) {
            దత్తాంశం->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, దత్తాంశం->surface);
            frog_color_managed_surface_కూడు_listener(దత్తాంశం->frog_color_managed_surface, &frog_surface_listener, దత్తాంశం);
        }

        ఒకవేళ (c->wp_alpha_modifier_v1) {
            దత్తాంశం->wp_alpha_modifier_surface_v1 = wp_alpha_modifier_v1_get_surface(c->wp_alpha_modifier_v1, దత్తాంశం->surface);
            wp_alpha_modifier_surface_v1_సమితి_multiplier(దత్తాంశం->wp_alpha_modifier_surface_v1, SDL_MAX_UINT32);
        }
    }

    // Must be called before EGL configuration to set the drawable backbuffer size.
    Configure_కిటికీ_Geometry(కిటికీ);

    /* Fire a callback when the compositor wants a new frame rendered.
     * Right now this only matters for OpenGL; we use this callback to add a
     * wait timeout that avoids getting deadlocked by the compositor when the
     * window isn't visible.
     */
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        దత్తాంశం->gles_మార్పిడి_చట్రం_event_వరుస = WAYLAND_wl_display_create_వరుస(దత్తాంశం->wayland_దత్తాంశం->display);
        దత్తాంశం->gles_మార్పిడి_చట్రం_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(దత్తాంశం->surface);
        WAYLAND_wl_proxy_సమితి_వరుస((నిర్మాణం wl_proxy *)దత్తాంశం->gles_మార్పిడి_చట్రం_surface_wrapper, దత్తాంశం->gles_మార్పిడి_చట్రం_event_వరుస);
        దత్తాంశం->gles_మార్పిడి_చట్రం_callback = wl_surface_చట్రం(దత్తాంశం->gles_మార్పిడి_చట్రం_surface_wrapper);
        wl_callback_కూడు_listener(దత్తాంశం->gles_మార్పిడి_చట్రం_callback, &gles_మార్పిడి_చట్రం_listener, దత్తాంశం);
    }

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_TRANSPARENT) {
        ఒకవేళ (_this->gl_config.alpha_కొలత == 0) {
            _this->gl_config.alpha_కొలత = 8;
        }
    }

    ఒకవేళ (create_egl_కిటికీ) {
        దత్తాంశం->egl_కిటికీ = WAYLAND_wl_egl_కిటికీ_create(దత్తాంశం->surface, దత్తాంశం->current.pixel_వెడల్పు, దత్తాంశం->current.pixel_ఎత్తు);
    }

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_OPENGL) {
        // Create the GLES window surface
        దత్తాంశం->egl_surface = SDL_EGL_CreateSurface(_this, కిటికీ, (Native_కిటికీ_Type)దత్తాంశం->egl_కిటికీ);

        ఒకవేళ (దత్తాంశం->egl_surface == EGL_NO_SURFACE) {
            తిరిగి false; // SDL_EGL_CreateSurface should have set error
        }
    }
#అయితే_ముగింపు

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    ఒకవేళ (!custom_surface_role) {
#నిర్వచితమైతే HAVE_LIBDECOR_H
        ఒకవేళ (c->shell.libdecor && !SDL_కిటికీ_IS_POPUP(కిటికీ)) {
            దత్తాంశం->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } లేకపోతే
#అయితే_ముగింపు
            ఒకవేళ (c->shell.xdg) {
            ఒకవేళ (SDL_కిటికీ_IS_POPUP(కిటికీ)) {
                దత్తాంశం->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP;
            } లేకపోతే {
                దత్తాంశం->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL;
            }
        } // All other cases will be WAYLAND_SURFACE_UNKNOWN
    } లేకపోతే {
        // Roleless and external surfaces are always considered to be in the shown state by the backend.
        దత్తాంశం->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_CUSTOM;
        దత్తాంశం->shell_surface_స్థితి = WAYLAND_SHELL_SURFACE_స్థితి_SHOWN;

        // External windows are presumed to be shown.
        ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_EXTERNAL) {
            కిటికీ->flags &= ~SDL_కిటికీ_HIDDEN;
        }
    }

    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_బఫరు, false)) {
        దత్తాంశం->double_బఫరు = true;
    }

    SDL_PropertiesID props = SDL_Get_కిటికీ_Properties(కిటికీ);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_DISPLAY_సూచిక, దత్తాంశం->wayland_దత్తాంశం->display);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_SURFACE_సూచిక, దత్తాంశం->surface);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_VIEWPORT_సూచిక, దత్తాంశం->viewport);
    SDL_సమితి_సూచిక_Property(props, SDL_PROP_కిటికీ_WAYLAND_EGL_కిటికీ_సూచిక, దత్తాంశం->egl_కిటికీ);
    ఒకవేళ (దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || దత్తాంశం->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        స్థిరరాశి అక్షరం *కిటికీ_id = SDL_GetStringProperty(create_props, SDL_PROP_కిటికీ_CREATE_WAYLAND_కిటికీ_ID_STRING, ఖాళీ);
        ఒకవేళ (కిటికీ_id && *కిటికీ_id != '\0') {
            SDL_సమితి_String_Property(props, SDL_PROP_కిటికీ_WAYLAND_కిటికీ_ID_STRING, కిటికీ_id);
        }
    }

    దత్తాంశం->తగిలింది_test_ఫలితం = SDL_HITTEST_సాధారణ;

    తిరిగి true;
}

శూన్య Wayland_సమితి_కిటికీ_Minimum_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    కిటికీ->అంతర్గత->limits_మారింది = true;
}

శూన్య Wayland_సమితి_కిటికీ_గరిష్ఠ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    కిటికీ->అంతర్గత->limits_మారింది = true;
}

శూన్య Wayland_సమితి_కిటికీ_Aspect_నిష్పత్తి(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    కిటికీ->అంతర్గత->limits_మారింది = true;
}

bool Wayland_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    // Only popup windows can be positioned relative to the parent.
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        ఒకవేళ (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_సంస్కరణ(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_సంస్కరణ) {
            తిరిగి SDL_Unsupported();
        }

        RepositionPopup(కిటికీ, false);
        తిరిగి true;
    } లేకపోతే ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(కిటికీ);

        ఒకవేళ (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_Get_Video_Display_For_Fullscreen_కిటికీ(కిటికీ);
            ఒకవేళ (display && wind->చివరి_display_ID != display->id) {
                నిర్మాణం wl_output *output = display->అంతర్గత->output;
                సమితి_Fullscreen(కిటికీ, output, true);

                తిరిగి true;
            }
        }
    }
    తిరిగి SDL_సమితి_Error("wayland cannot position non-popup windows");
}

శూన్య Wayland_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    /* Flush any pending state operations, as fullscreen windows do not get
     * explicitly resized, not strictly obeying the size of a maximized window
     * is a protocol violation, and pending restore events might result in a
     * configure event overwriting the requested size.
     *
     * Calling this on a custom surface is informative, so the size must
     * always be passed through.
     */
    FlushPendingEvents(కిటికీ);

    స్థిరరాశి bool maximized = (కిటికీ->flags & SDL_కిటికీ_MAXIMIZED) != 0;
    స్థిరరాశి bool resizable_state = !(కిటికీ->flags & (SDL_కిటికీ_MAXIMIZED | SDL_కిటికీ_FULLSCREEN));

    /* Maximized and fullscreen windows don't get resized, and the new size is ignored
     * if this is just to recalculate the min/max or aspect limits on a tiled window.
     *
     * Some compositors will mark tiled windows as maximized. In these cases, the content
     * size is recalculated, but window size itself is left alone, as the spec states that
     * the configure size of a maximized window must be obeyed.
     */
    ఒకవేళ (resizable_state || (కిటికీ->tiled && !wind->limits_మారింది) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        ఒకవేళ (!maximized) {
            ఒకవేళ (!wind->scale_గమ్యం_display) {
                wind->requested.logical_వెడల్పు = కిటికీ->pending.w;
                wind->requested.logical_ఎత్తు = కిటికీ->pending.h;
            } లేకపోతే {
                wind->requested.logical_వెడల్పు = Pixel_గమ్యం_బిందువు(కిటికీ, కిటికీ->pending.w);
                wind->requested.logical_ఎత్తు = Pixel_గమ్యం_బిందువు(కిటికీ, కిటికీ->pending.h);
                wind->requested.pixel_వెడల్పు = కిటికీ->pending.w;
                wind->requested.pixel_ఎత్తు = కిటికీ->pending.h;
            }
        }

        /* If a non-resizable window somehow wound up in the tiled state, store the new
         * size in the floating parameters so the size will be preserved for future
         * configure events.
         *
         * This shouldn't happen, but apparently it can on at least one compositor...
         */
        ఒకవేళ (కిటికీ->tiled && !(కిటికీ->flags & SDL_కిటికీ_RESIZABLE)) {
            కిటికీ->floating.w = కిటికీ->pending.w;
            కిటికీ->floating.h = కిటికీ->pending.h;
        }
    } లేకపోతే {
        // Can't resize the window.
        కిటికీ->చివరి_కొలత_pending = false;
    }

    wind->limits_మారింది = false;
    ఒకవేళ (wind->shell_surface_స్థితి == WAYLAND_SHELL_SURFACE_స్థితి_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    Configure_కిటికీ_Geometry(కిటికీ);
    Commit_Libdecor_చట్రం(కిటికీ);
}

శూన్య Wayland_Get_కిటికీ_కొలత_లోపల_Pixels(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    *w = దత్తాంశం->current.pixel_వెడల్పు;
    *h = దత్తాంశం->current.pixel_ఎత్తు;
}

దశాంశం Wayland_Get_కిటికీ_Content_Scale(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_ఎగువ_PIXEL_DENSITY || wind->scale_గమ్యం_display || wind->fullscreen_exclusive) {
        తిరిగి (దశాంశం)wind->scale_గుణకం_2;
    }

    తిరిగి 1.0f;
}

SDL_DisplayID Wayland_Get_Display_For_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    ఒకవేళ (wind) {
        తిరిగి wind->చివరి_display_ID;
    }

    తిరిగి 0;
}

bool Wayland_సమితి_కిటికీ_Opacity(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, దశాంశం opacity)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    ఒకవేళ (wind->wp_alpha_modifier_surface_v1) {
        స్థిరరాశి bool is_opaque = !(కిటికీ->flags & SDL_కిటికీ_TRANSPARENT) && opacity == 1.0f;

        ఒకవేళ (wind->ముసుగు.mapped && wind->ముసుగు.opaque != is_opaque) {
            నిర్మాణం wl_బఫరు *old_బఫరు = wind->ముసుగు.బఫరు_2;
            wind->ముసుగు.opaque = is_opaque;
            wind->ముసుగు.బఫరు_2 = Wayland_Create_Single_Pixel_బఫరు(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->ముసుగు.surface, wind->ముసుగు.బఫరు_2, 0, 0);
            ఒకవేళ (wl_surface_get_సంస్కరణ(wind->ముసుగు.surface) >= WL_SURFACE_DAMAGE_బఫరు_SINCE_సంస్కరణ) {
                wl_surface_damage_బఫరు(wind->ముసుగు.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } లేకపోతే {
                wl_surface_damage(wind->ముసుగు.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            ఒకవేళ (is_opaque) {
                సమితి_Surface_Opaque_Region(wind->ముసుగు.surface, wind->current.logical_వెడల్పు, wind->current.logical_ఎత్తు);
            } లేకపోతే {
                సమితి_Surface_Opaque_Region(wind->ముసుగు.surface, 0, 0);
            }

            wl_surface_commit(wind->ముసుగు.surface);

            ఒకవేళ (old_బఫరు) {
                wl_బఫరు_destroy(old_బఫరు);
            }
        }

        ఒకవేళ (is_opaque) {
            సమితి_Surface_Opaque_Region(wind->surface, wind->current.viewport_వెడల్పు, wind->current.viewport_ఎత్తు);
        } లేకపోతే {
            సమితి_Surface_Opaque_Region(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_సమితి_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((ద్విగుణ)SDL_MAX_UINT32 * (ద్విగుణ)opacity));

        తిరిగి true;
    }

    తిరిగి SDL_సమితి_Error("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

శూన్య Wayland_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
    స్థిరరాశి అక్షరం *title = కిటికీ->title ? కిటికీ->title : "";

#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.చట్రం) {
        libdecor_చట్రం_సమితి_title(wind->shell_surface.libdecor.చట్రం, title);
    } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_సమితి_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

స్థిర పూర్ణాంకం icon_క్రమీకరించు_callback(స్థిరరాశి శూన్య *a, స్థిరరాశి శూన్య *b)
{
    స్థిరరాశి SDL_Surface *s1 = *(స్థిరరాశి SDL_Surface **)a;
    స్థిరరాశి SDL_Surface *s2 = *(స్థిరరాశి SDL_Surface **)b;

    తిరిగి (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_సమితి_కిటికీ_Icon(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *icon)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
    Wayland_SHMPool *shm_pool = ఖాళీ;
    నిర్మాణం xdg_toplevel *toplevel = ఖాళీ;

    ఒకవేళ (!_this->అంతర్గత->xdg_toplevel_icon_manager_v1) {
        తిరిగి SDL_సమితి_Error("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    పూర్ణాంకం image_లెక్క_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_లెక్క_2);
    ఒకవేళ (!images || !image_లెక్క_2) {
        తిరిగి false;
    }

    // Release the old icon resources.
    ఒకవేళ (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = ఖాళీ;
    }

    కొరకు (పూర్ణాంకం i = 0; i < wind->icon_బఫరు_లెక్క; ++i) {
        wl_బఫరు_destroy(wind->icon_buffers[i]);
    }
    wind->icon_బఫరు_లెక్క = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->అంతర్గత->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_లెక్క_2 * పరిమాణం(నిర్మాణం wl_బఫరు *));
    ఒకవేళ (!wind->icon_buffers) {
        వెళ్ళు failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    size_t pool_కొలత = 0;
    కొరకు (పూర్ణాంకం i = 0; i < image_లెక్క_2; ++i) {
        // Images must be square. Non-square images will be centered.
        స్థిరరాశి పూర్ణాంకం కొలత = SDL_max(images[i]->w, images[i]->h);
        pool_కొలత += కొలత * కొలత * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_లెక్క_2, పరిమాణం(SDL_Surface *), icon_క్రమీకరించు_callback);

    shm_pool = Wayland_AllocSHMPool(pool_కొలత);
    ఒకవేళ (!shm_pool) {
        SDL_సమితి_Error("wayland: failed to allocate an SHM pool for the icon");
        వెళ్ళు failure_cleanup;
    }

    స్థిరరాశి ద్విగుణ పునాది_కొలత = (ద్విగుణ)SDL_max(icon->w, icon->h);
    కొరకు (పూర్ణాంకం i = 0; i < image_లెక్క_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        స్థిరరాశి పూర్ణాంకం level_కొలత = SDL_max(surface->w, surface->h);
        స్థిరరాశి పూర్ణాంకం scale = (పూర్ణాంకం)SDL_floor((ద్విగుణ)level_కొలత / పునాది_కొలత);
        ఒకవేళ (!scale) {
            కొనసాగు;
        }

        ఒకవేళ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            ఒకవేళ (!surface) {
                SDL_సమితి_Error("wayland: failed to convert the icon image to ARGB8888 format");
                వెళ్ళు failure_cleanup;
            }
        }

        శూన్య *బఫరు_mem;
        నిర్మాణం wl_బఫరు *బఫరు_2 = Wayland_Alloc_బఫరు_From_Pool(shm_pool, level_కొలత, level_కొలత, &బఫరు_mem);
        ఒకవేళ (!బఫరు_2) {
            // Clean up the temporary conversion surface.
            ఒకవేళ (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_సమితి_Error("wayland: failed to allocate a wl_buffer for the icon");
            వెళ్ళు failure_cleanup;
        }

        wind->icon_buffers[wind->icon_బఫరు_లెక్క++] = బఫరు_2;

        // Center non-square images.
        ఒకవేళ (surface->w < level_కొలత) {
            SDL_memset(బఫరు_mem, 0, level_కొలత * level_కొలత * 4);
            బఫరు_mem = (Uint8 *)బఫరు_mem + (((level_కొలత - surface->w) / 2) * 4);
        } లేకపోతే ఒకవేళ (surface->h < level_కొలత) {
            SDL_memset(బఫరు_mem, 0, level_కొలత * level_కొలత * 4);
            బఫరు_mem = (Uint8 *)బఫరు_mem + (((level_కొలత - surface->h) / 2) * (level_కొలత * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, బఫరు_mem, level_కొలత * 4, true);

        xdg_toplevel_icon_v1_కూడు_బఫరు(wind->xdg_toplevel_icon_v1, బఫరు_2, scale);

        // Clean up the temporary scaled or conversion surface.
        ఒకవేళ (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.చట్రం) {
        toplevel = libdecor_చట్రం_get_xdg_toplevel(wind->shell_surface.libdecor.చట్రం);
    } లేకపోతే
#అయితే_ముగింపు
        ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    ఒకవేళ (toplevel) {
        xdg_toplevel_icon_manager_v1_సమితి_icon(_this->అంతర్గత->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
    }

    Wayland_ReleaseSHMPool(shm_pool);
    SDL_free(images);

    తిరిగి true;

failure_cleanup:

    SDL_free(images);

    ఒకవేళ (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = ఖాళీ;
    }

    Wayland_ReleaseSHMPool(shm_pool);

    కొరకు (పూర్ణాంకం i = 0; i < wind->icon_బఫరు_లెక్క; ++i) {
        wl_బఫరు_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = ఖాళీ;
    wind->icon_బఫరు_లెక్క = 0;

    తిరిగి false;
}

శూన్య *Wayland_Get_కిటికీ_ICCProfile(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, size_t *కొలత)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
    శూన్య *ret = ఖాళీ;

    ఒకవేళ (wind->icc_కొలత > 0) {
        శూన్య *icc_map = mmap(ఖాళీ, wind->icc_కొలత, PROT_READ, MAP_PRIVATE, wind->icc_fd, 0);
        ఒకవేళ (icc_map != MAP_FAILED) {
            ret = SDL_malloc(wind->icc_కొలత);
            ఒకవేళ (ret) {
                *కొలత = wind->icc_కొలత;
                SDL_memcpy(ret, icc_map, *కొలత);
            }
            munmap(icc_map, wind->icc_కొలత);
        }
    }

    తిరిగి ret;
}

bool Wayland_Sync_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    చేయి {
        WAYLAND_wl_display_roundtrip(_this->అంతర్గత->display);
    } అయితే (wind->pending_state_deadline_లెక్క);

    తిరిగి true;
}

శూన్య Wayland_AcceptDragAndDrop(SDL_కిటికీ *కిటికీ, bool accept)
{
    కిటికీ->అంతర్గత->స్వీకరించు_drag_and_drop = accept;
}

bool Wayland_సమితి_కిటికీ_Focusable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool focusable)
{
    ఒకవేళ (కిటికీ->flags & SDL_కిటికీ_POPUP_MENU) {
        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_HIDDEN)) {
            ఒకవేళ (!focusable && (కిటికీ->flags & SDL_కిటికీ_ఆదానం_FOCUS)) {
                SDL_కిటికీ *new_focus;
                స్థిరరాశి bool సమితి_focus = SDL_ShouldRelinquishPopupFocus(కిటికీ, &new_focus);
                Wayland_సమితి_Keyboard_Focus(new_focus, సమితి_focus);
            } లేకపోతే ఒకవేళ (focusable) {
                ఒకవేళ (SDL_ShouldFocusPopup(కిటికీ)) {
                    Wayland_సమితి_Keyboard_Focus(కిటికీ, true);
                }
            }
        }

        తిరిగి true;
    }

    తిరిగి SDL_సమితి_Error("wayland: focus can only be toggled on popup menu windows");
}

శూన్య Wayland_Show_కిటికీ_System_Menu(SDL_కిటికీ *కిటికీ, పూర్ణాంకం x, పూర్ణాంకం y)
{
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;
    SDL_WaylandSeat *seat = wind->wayland_దత్తాంశం->చివరి_implicit_grab_seat;

    ఒకవేళ (!seat) {
        తిరిగి;
    }

    ఒకవేళ (wind->scale_గమ్యం_display) {
        x = Pixel_గమ్యం_బిందువు(కిటికీ, x);
        y = Pixel_గమ్యం_బిందువు(కిటికీ, y);
    }

#నిర్వచితమైతే HAVE_LIBDECOR_H
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ఒకవేళ (wind->shell_surface.libdecor.చట్రం) {
            libdecor_చట్రం_show_కిటికీ_menu(wind->shell_surface.libdecor.చట్రం, seat->wl_seat, seat->చివరి_implicit_grab_serial, x, y);
        }
    } లేకపోతే
#అయితే_ముగింపు
    ఒకవేళ (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ఒకవేళ (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_కిటికీ_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->చివరి_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

#నిర్వచితమైతే SDL_USE_LIBDBUS
    ఒకవేళ (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        తిరిగి true;
    }
#అయితే_ముగింపు

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    ఒకవేళ (దత్తాంశం->idle_inhibit_manager) {
        SDL_కిటికీ *కిటికీ = _this->windows;
        అయితే (కిటికీ) {
            SDL_కిటికీ_దత్తాంశం *win_దత్తాంశం = కిటికీ->అంతర్గత;

            ఒకవేళ (_this->suspend_screensaver && !win_దత్తాంశం->idle_inhibitor) {
                win_దత్తాంశం->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(దత్తాంశం->idle_inhibit_manager,
                                                                 win_దత్తాంశం->surface);
            } లేకపోతే ఒకవేళ (!_this->suspend_screensaver && win_దత్తాంశం->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_దత్తాంశం->idle_inhibitor);
                win_దత్తాంశం->idle_inhibitor = ఖాళీ;
            }

            కిటికీ = కిటికీ->తదుపరి;
        }
    }

    తిరిగి true;
}

శూన్య Wayland_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    SDL_కిటికీ_దత్తాంశం *wind = కిటికీ->అంతర్గత;

    ఒకవేళ (దత్తాంశం && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        ఒకవేళ (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            కిటికీ->తగిలింది_test = ఖాళీ;
            WAYLAND_wl_display_roundtrip(దత్తాంశం->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_Display_Remove_కిటికీ_References_From_Seats(దత్తాంశం, wind);

        ఒకవేళ (wind->ముసుగు.viewport) {
            wp_viewport_destroy(wind->ముసుగు.viewport);
        }
        ఒకవేళ (wind->ముసుగు.బఫరు_2) {
            wl_బఫరు_destroy(wind->ముసుగు.బఫరు_2);
        }
        ఒకవేళ (wind->ముసుగు.subsurface) {
            wl_subsurface_destroy(wind->ముసుగు.subsurface);
        }
        ఒకవేళ (wind->ముసుగు.surface) {
            wl_surface_destroy(wind->ముసుగు.surface);
        }
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
        ఒకవేళ (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#అయితే_ముగింపు
        ఒకవేళ (wind->egl_కిటికీ) {
            WAYLAND_wl_egl_కిటికీ_destroy(wind->egl_కిటికీ);
        }

        ఒకవేళ (wind->idle_inhibitor) {
            zwp_idle_inhibitor_v1_destroy(wind->idle_inhibitor);
        }

        ఒకవేళ (wind->activation_token) {
            xdg_activation_token_v1_destroy(wind->activation_token);
        }

        ఒకవేళ (wind->viewport) {
            wp_viewport_destroy(wind->viewport);
        }

        ఒకవేళ (wind->fractional_scale) {
            wp_fractional_scale_v1_destroy(wind->fractional_scale);
        }

        ఒకవేళ (wind->wp_alpha_modifier_surface_v1) {
            wp_alpha_modifier_surface_v1_destroy(wind->wp_alpha_modifier_surface_v1);
        }

        ఒకవేళ (wind->frog_color_managed_surface) {
            frog_color_managed_surface_destroy(wind->frog_color_managed_surface);
        }

        ఒకవేళ (wind->wp_color_management_surface_feedback) {
            Wayland_FreeColorInfoState(wind->color_info_state);
            wp_color_management_surface_feedback_v1_destroy(wind->wp_color_management_surface_feedback);
        }

        SDL_free(wind->outputs);
        SDL_free(wind->app_id);

        ఒకవేళ (wind->gles_మార్పిడి_చట్రం_callback) {
            wl_callback_destroy(wind->gles_మార్పిడి_చట్రం_callback);
            WAYLAND_wl_proxy_wrapper_destroy(wind->gles_మార్పిడి_చట్రం_surface_wrapper);
            WAYLAND_wl_event_వరుస_destroy(wind->gles_మార్పిడి_చట్రం_event_వరుస);
        }

        ఒకవేళ (!(కిటికీ->flags & SDL_కిటికీ_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } లేకపోతే {
            Wayland_Remove_కిటికీ_దత్తాంశం_From_External_List(wind);
        }

        ఒకవేళ (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        కొరకు (పూర్ణాంకం i = 0; i < wind->icon_బఫరు_లెక్క; ++i) {
            wl_బఫరు_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_బఫరు_లెక్క = 0;

        SDL_free(wind);
    }
    కిటికీ->అంతర్గత = ఖాళీ;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND
