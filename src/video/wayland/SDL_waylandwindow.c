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

#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND

#अन्तर्भाव <sys/mman.h>

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../core/unix/SDL_appid.h"
#अन्तर्भाव "../../notification/SDL_notification_c.h"
#अन्तर्भाव "../SDL_egl_c.h"
#अन्तर्भाव "SDL_waylandevents_c.h"
#अन्तर्भाव "SDL_waylandmouse.h"
#अन्तर्भाव "SDL_waylandwindow.h"
#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "../../SDL_hints_c.h"
#अन्तर्भाव "SDL_waylandcolor.h"

#अन्तर्भाव "alpha-modifier-v1-client-protocol.h"
#अन्तर्भाव "xdg-shell-client-protocol.h"
#अन्तर्भाव "xdg-decoration-unstable-v1-client-protocol.h"
#अन्तर्भाव "idle-inhibit-unstable-v1-client-protocol.h"
#अन्तर्भाव "xdg-activation-v1-client-protocol.h"
#अन्तर्भाव "viewporter-client-protocol.h"
#अन्तर्भाव "fractional-scale-v1-client-protocol.h"
#अन्तर्भाव "xdg-foreign-unstable-v2-client-protocol.h"
#अन्तर्भाव "xdg-dialog-v1-client-protocol.h"
#अन्तर्भाव "frog-color-management-v1-client-protocol.h"
#अन्तर्भाव "xdg-toplevel-icon-v1-client-protocol.h"
#अन्तर्भाव "color-management-v1-client-protocol.h"
#अन्तर्भाव "xdg-session-management-v1-client-protocol.h"
#अन्तर्भाव "xdg-toplevel-tag-v1-client-protocol.h"

#यदि_परिभाषितम् HAVE_LIBDECOR_H
#अन्तर्भाव <libdecor.h>
#यदि_अन्तः

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
स्थिर bool Should_आवरणम्_Fullscreen()
{
    स्थिर पूर्णाङ्क आवरणम्_required = -1;

    यदि (आवरणम्_required >= 0) {
        प्रत्यागम आवरणम्_required != 0;
    }

    ध्रुव वर्ण *desktop = SDL_getenv("XDG_CURRENT_DESKTOP");
    यदि (desktop && SDL_strstr(desktop, "KDE") != रिक्त) {
        आवरणम्_required = 1;
    } अन्यथा {
        आवरणम्_required = 0;
    }

    प्रत्यागम आवरणम्_required != 0;
}

स्थिर द्विगुण Get_गवाक्षः_Scale(SDL_गवाक्षः *गवाक्षः)
{
    प्रत्यागम (गवाक्षः->flags & SDL_गवाक्षः_उच्चः_PIXEL_DENSITY) || गवाक्षः->आन्तरिकम्->scale_गन्तव्यम्_display ? गवाक्षः->आन्तरिकम्->scale_गुणकः_2 : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
स्थिर पूर्णाङ्क Point_गन्तव्यम्_Pixel(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क point)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    प्रत्यागम point ? SDL_max((पूर्णाङ्क)SDL_lround((द्विगुण)point * Get_गवाक्षः_Scale(गवाक्षः) + 1e-6), 1) : 0;
}

स्थिर पूर्णाङ्क Pixel_गन्तव्यम्_Point(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क pixel)
{
    प्रत्यागम pixel ? SDL_max((पूर्णाङ्क)SDL_lround((द्विगुण)pixel / Get_गवाक्षः_Scale(गवाक्षः)), 1) : 0;
}

गणना Wayland_बहुलकम्_Scale
{
    WAYLAND_बहुलकम्_SCALE_UNDEFINED,
    WAYLAND_बहुलकम्_SCALE_ASPECT,
    WAYLAND_बहुलकम्_SCALE_STRETCH,
    WAYLAND_बहुलकम्_SCALE_NONE
};

स्थिर गणना Wayland_बहुलकम्_Scale Get_बहुलकम्_Scale_विधानम्(शून्य)
{
    स्थिर गणना Wayland_बहुलकम्_Scale scale_बहुलकम्_2 = WAYLAND_बहुलकम्_SCALE_UNDEFINED;

    यदि (scale_बहुलकम्_2 == WAYLAND_बहुलकम्_SCALE_UNDEFINED) {
        ध्रुव वर्ण *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_बहुलकम्_SCALING);

        यदि (scale_hint) {
            यदि (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_बहुलकम्_2 = WAYLAND_बहुलकम्_SCALE_STRETCH;
            } अन्यथा यदि (!SDL_strcasecmp(scale_hint, "none")) {
                scale_बहुलकम्_2 = WAYLAND_बहुलकम्_SCALE_NONE;
            } अन्यथा {
                scale_बहुलकम्_2 = WAYLAND_बहुलकम्_SCALE_ASPECT;
            }
        } अन्यथा {
            scale_बहुलकम्_2 = WAYLAND_बहुलकम्_SCALE_ASPECT;
        }
    }

    प्रत्यागम scale_बहुलकम्_2;
}

प्रकारनिर्देश संरचना BorderInsets
{
    पूर्णाङ्क वामः;
    पूर्णाङ्क शिखरम्;
    पूर्णाङ्क दक्षिणः;
    पूर्णाङ्क bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
स्थिर शून्य GetBorderInsets(SDL_गवाक्षः *गवाक्षः, BorderInsets *insets)
{
    SDL_zerop(insets);
    यदि (!गवाक्षः->आन्तरिकम्->enable_insets) {
        प्रत्यागम;
    }
    यदि (गवाक्षः->आन्तरिकम्->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ध्रुव SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(गवाक्षः);
        insets->वामः = (पूर्णाङ्क)SDL_clamp(SDL_Get_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_WAYLAND_BORDER_INSET_वामः_सङ्ख्या, 0), 0, SDL_MAX_SINT16);
        insets->शिखरम् = (पूर्णाङ्क)SDL_clamp(SDL_Get_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_WAYLAND_BORDER_INSET_शिखरम्_सङ्ख्या, 0), 0, SDL_MAX_SINT16);
        insets->दक्षिणः = (पूर्णाङ्क)SDL_clamp(SDL_Get_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_WAYLAND_BORDER_INSET_दक्षिणः_सङ्ख्या, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (पूर्णाङ्क)SDL_clamp(SDL_Get_सङ्ख्या_Property(props, SDL_PROP_गवाक्षः_WAYLAND_BORDER_INSET_BOTTOM_सङ्ख्या, 0), 0, SDL_MAX_SINT16);
    }
}

स्थिर शून्य समुच्चयः_Min_Max_Dimensions(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;
    पूर्णाङ्क min_विस्तारः_2, min_height, max_विस्तारः_2, max_height;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    यदि (गवाक्षः->flags & (SDL_गवाक्षः_FULLSCREEN | SDL_गवाक्षः_MAXIMIZED)) {
        min_विस्तारः_2 = 0;
        min_height = 0;
        max_विस्तारः_2 = 0;
        max_height = 0;
    } अन्यथा यदि (गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE) {
        पूर्णाङ्क adj_w = SDL_max(गवाक्षः->min_w, wind->system_limits.min_विस्तारः_2);
        पूर्णाङ्क adj_h = SDL_max(गवाक्षः->min_h, wind->system_limits.min_height);
        यदि (wind->scale_गन्तव्यम्_display) {
            adj_w = Pixel_गन्तव्यम्_Point(गवाक्षः, adj_w);
            adj_h = Pixel_गन्तव्यम्_Point(गवाक्षः, adj_h);
        }
        min_विस्तारः_2 = adj_w;
        min_height = adj_h;

        adj_w = गवाक्षः->max_w ? SDL_max(गवाक्षः->max_w, wind->system_limits.min_विस्तारः_2) : 0;
        adj_h = गवाक्षः->max_h ? SDL_max(गवाक्षः->max_h, wind->system_limits.min_height) : 0;
        यदि (wind->scale_गन्तव्यम्_display) {
            adj_w = Pixel_गन्तव्यम्_Point(गवाक्षः, adj_w);
            adj_h = Pixel_गन्तव्यम्_Point(गवाक्षः, adj_h);
        }
        max_विस्तारः_2 = adj_w;
        max_height = adj_h;
    } अन्यथा {
        min_विस्तारः_2 = wind->current.logical_विस्तारः;
        min_height = wind->current.logical_height;
        max_विस्तारः_2 = wind->current.logical_विस्तारः;
        max_height = wind->current.logical_height;
    }

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (!wind->shell_surface.libdecor.frame) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }

        यदि (min_विस्तारः_2 && min_height && min_विस्तारः_2 == max_विस्तारः_2 && min_height == max_height) {
            libdecor_frame_unset_capabilities(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE);
        } अन्यथा {
            libdecor_frame_समुच्चयः_capabilities(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        यदि (libdecor_frame_has_capability(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE)) {
            libdecor_frame_समुच्चयः_min_content_आकार(wind->shell_surface.libdecor.frame,
                                                min_विस्तारः_2,
                                                min_height);
            libdecor_frame_समुच्चयः_max_content_आकार(wind->shell_surface.libdecor.frame,
                                                max_विस्तारः_2,
                                                max_height);
        }
    } अन्यथा
#यदि_अन्तः
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(गवाक्षः, &insets);
        min_विस्तारः_2 = SDL_max(min_विस्तारः_2 - (insets.वामः + insets.दक्षिणः), min_विस्तारः_2 ? 1 : 0);
        min_height = SDL_max(min_height - (insets.शिखरम् + insets.bottom), min_height ? 1 : 0);
        यदि (max_विस्तारः_2) {
            max_विस्तारः_2 = SDL_max(max_विस्तारः_2 - (insets.वामः + insets.दक्षिणः), 1);
        }
        यदि (max_height) {
            max_height = SDL_max(max_height - (insets.शिखरम् + insets.bottom), 1);
        }
        xdg_toplevel_समुच्चयः_min_आकार(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_विस्तारः_2,
                                  min_height);
        xdg_toplevel_समुच्चयः_max_आकार(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_विस्तारः_2,
                                  max_height);
    }
}

स्थिर शून्य EnsurePopupPositionIsValid(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *x, पूर्णाङ्क *y)
{
    पूर्णाङ्क adj_गणनम् = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    यदि (*x + गवाक्षः->w <= 0) {
        *x = -गवाक्षः->w;
        ++adj_गणनम्;
    }
    यदि (*y + गवाक्षः->h <= 0) {
        *y = -गवाक्षः->h;
        ++adj_गणनम्;
    }
    यदि (*x >= गवाक्षः->parent->w) {
        *x = गवाक्षः->parent->w;
        ++adj_गणनम्;
    }
    यदि (*y >= गवाक्षः->parent->h) {
        *y = गवाक्षः->parent->h;
        ++adj_गणनम्;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    यदि (adj_गणनम् > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
स्थिर शून्य Get_गवाक्षः_Geometry(SDL_गवाक्षः_दत्त *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    यदि (SDL_Rect_रिक्तानि(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_विस्तारः;
        geometry->h = wind->current.logical_height;
    }
}

स्थिर शून्य Adjust_Popup_विस्थापनम्(SDL_गवाक्षः *popup, पूर्णाङ्क *x, पूर्णाङ्क *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (popup->parent->आन्तरिकम्->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        पूर्णाङ्क adj_x, adj_y;
        libdecor_frame_translate_coordinate(popup->parent->आन्तरिकम्->shell_surface.libdecor.frame,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } अन्यथा
#यदि_अन्तः
    {
        *x -= popup->parent->आन्तरिकम्->explicit_geometry.x;
        *y -= popup->parent->आन्तरिकम्->explicit_geometry.y;
    }
}

स्थिर शून्य RepositionPopup(SDL_गवाक्षः *गवाक्षः, bool use_current_position)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_संस्करणम्(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_संस्करणम्) {
        पूर्णाङ्क x = use_current_position ? गवाक्षः->x : गवाक्षः->pending.x;
        पूर्णाङ्क y = use_current_position ? गवाक्षः->y : गवाक्षः->pending.y;

        EnsurePopupPositionIsValid(गवाक्षः, &x, &y);
        यदि (wind->scale_गन्तव्यम्_display) {
            x = Pixel_गन्तव्यम्_Point(गवाक्षः->parent, x);
            y = Pixel_गन्तव्यम्_Point(गवाक्षः->parent, y);
        }
        Adjust_Popup_विस्थापनम्(गवाक्षः, &x, &y);
        SDL_Rect parent_geometry;
        Get_गवाक्षः_Geometry(गवाक्षः->parent->आन्तरिकम्, &parent_geometry);
        xdg_positioner_समुच्चयः_anchor_rect(wind->shell_surface.xdg.popup.xdg_positioner, 0, 0, parent_geometry.w, parent_geometry.h);
        xdg_positioner_समुच्चयः_आकार(wind->shell_surface.xdg.popup.xdg_positioner, wind->current.logical_विस्तारः, wind->current.logical_height);
        xdg_positioner_समुच्चयः_विस्थापनम्(wind->shell_surface.xdg.popup.xdg_positioner, x, y);
        xdg_popup_reposition(wind->shell_surface.xdg.popup.xdg_popup,
                             wind->shell_surface.xdg.popup.xdg_positioner,
                             0);
    }
}

स्थिर शून्य समुच्चयः_Surface_Opaque_Region(संरचना wl_surface *surface, पूर्णाङ्क विस्तारः, पूर्णाङ्क height)
{
    SDL_Video_दत्त *viddata = SDL_GetVideoDevice()->आन्तरिकम्;

    यदि (विस्तारः && height) {
        संरचना wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_सङ्कलय(region, 0, 0, विस्तारः, height);
        wl_surface_समुच्चयः_opaque_region(surface, region);
        wl_region_destroy(region);
    } अन्यथा {
        wl_surface_समुच्चयः_opaque_region(surface, रिक्त);
    }
}

स्थिर शून्य Configure_गवाक्षः_Geometry(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    ध्रुव द्विगुण scale_गुणकः_2 = Get_गवाक्षः_Scale(गवाक्षः);
    ध्रुव द्विगुण पूर्व_pointer_scale_x = दत्त->pointer_scale.x;
    ध्रुव द्विगुण पूर्व_pointer_scale_y = दत्त->pointer_scale.y;
    ध्रुव पूर्णाङ्क old_pixel_विस्तारः = दत्त->current.pixel_विस्तारः;
    ध्रुव पूर्णाङ्क old_pixel_height = दत्त->current.pixel_height;
    पूर्णाङ्क गवाक्षः_विस्तारः = 0;
    पूर्णाङ्क गवाक्षः_height = 0;
    पूर्णाङ्क viewport_विस्तारः, viewport_height;
    bool गवाक्षः_आकार_परिवर्तितम्;
    bool बफर_आकार_परिवर्तितम्;
    ध्रुव bool is_opaque = !(गवाक्षः->flags & SDL_गवाक्षः_TRANSPARENT) && गवाक्षः->opacity == 1.0f;

    यदि (दत्त->is_fullscreen && गवाक्षः->fullscreen_exclusive) {
        गवाक्षः_विस्तारः = गवाक्षः->current_fullscreen_बहुलकम्.w;
        गवाक्षः_height = गवाक्षः->current_fullscreen_बहुलकम्.h;

        viewport_विस्तारः = दत्त->requested.logical_विस्तारः;
        viewport_height = दत्त->requested.logical_height;

        विकल्प (Get_बहुलकम्_Scale_विधानम्()) {
        पक्ष WAYLAND_बहुलकम्_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            यदि (गवाक्षः_विस्तारः <= viewport_विस्तारः && गवाक्षः_height <= viewport_height) {
                viewport_विस्तारः = गवाक्षः_विस्तारः;
                viewport_height = गवाक्षः_height;

                भङ्ग;
            }
            SDL_FALLTHROUGH;
        पक्ष WAYLAND_बहुलकम्_SCALE_ASPECT:
        {
            ध्रुव भिन्न output_अनुपातः = (भिन्न)viewport_विस्तारः / (भिन्न)viewport_height;
            ध्रुव भिन्न बहुलकम्_अनुपातः = (भिन्न)गवाक्षः_विस्तारः / (भिन्न)गवाक्षः_height;

            यदि (output_अनुपातः > बहुलकम्_अनुपातः) {
                viewport_विस्तारः = SDL_lroundf((भिन्न)गवाक्षः_विस्तारः * ((भिन्न)viewport_height / (भिन्न)गवाक्षः_height));
            } अन्यथा यदि (output_अनुपातः < बहुलकम्_अनुपातः) {
                viewport_height = SDL_lroundf((भिन्न)गवाक्षः_height * ((भिन्न)viewport_विस्तारः / (भिन्न)गवाक्षः_विस्तारः));
            }
        } भङ्ग;
        स्वभाव:
            भङ्ग;
        }

        गवाक्षः_आकार_परिवर्तितम् = गवाक्षः_विस्तारः != गवाक्षः->w ||
                              गवाक्षः_height != गवाक्षः->h ||
                              दत्त->current.viewport_विस्तारः != viewport_विस्तारः ||
                              दत्त->current.viewport_height != viewport_height;

        // Exclusive fullscreen window sizes are always in pixel units.
        दत्त->current.pixel_विस्तारः = गवाक्षः_विस्तारः;
        दत्त->current.pixel_height = गवाक्षः_height;
        बफर_आकार_परिवर्तितम् = दत्त->current.pixel_विस्तारः != old_pixel_विस्तारः ||
                              दत्त->current.pixel_height != old_pixel_height;

        यदि (गवाक्षः_आकार_परिवर्तितम् || बफर_आकार_परिवर्तितम्) {
            यदि (दत्त->viewport) {
                wp_viewport_समुच्चयः_destination(दत्त->viewport, viewport_विस्तारः, viewport_height);

                दत्त->current.logical_विस्तारः = दत्त->requested.logical_विस्तारः;
                दत्त->current.logical_height = दत्त->requested.logical_height;
                दत्त->current.viewport_विस्तारः = viewport_विस्तारः;
                दत्त->current.viewport_height = viewport_height;
            } अन्यथा {
                // Calculate the integer scale from the mode and output.
                ध्रुव int32_t int_scale = SDL_max(गवाक्षः->current_fullscreen_बहुलकम्.w / viewport_विस्तारः, 1);

                wl_surface_समुच्चयः_बफर_scale(दत्त->surface, int_scale);
                दत्त->current.logical_विस्तारः = गवाक्षः->current_fullscreen_बहुलकम्.w;
                दत्त->current.logical_height = गवाक्षः->current_fullscreen_बहुलकम्.h;
            }

            दत्त->pointer_scale.x = (द्विगुण)गवाक्षः_विस्तारः / (द्विगुण)viewport_विस्तारः;
            दत्त->pointer_scale.y = (द्विगुण)गवाक्षः_height / (द्विगुण)viewport_height;
        }
    } अन्यथा {
        यदि (!दत्त->scale_गन्तव्यम्_display) {
            viewport_विस्तारः = दत्त->requested.logical_विस्तारः;
            viewport_height = दत्त->requested.logical_height;
        } अन्यथा {
            viewport_विस्तारः = दत्त->requested.pixel_विस्तारः;
            viewport_height = दत्त->requested.pixel_height;
        }

        यदि (!दत्त->enable_insets &&
            दत्त->shell_surface_स्थितिः != WAYLAND_SHELL_SURFACE_स्थितिः_HIDDEN &&
            दत्त->viewport && दत्त->wayland_दत्त->subcompositor && !दत्त->floating && !दत्त->is_fullscreen) {
            पूर्णाङ्क min_विस्तारः_2, min_height, max_विस्तारः_2, max_height;
            यदि (गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE) {
                min_विस्तारः_2 = गवाक्षः->min_w;
                min_height = गवाक्षः->min_h;
                max_विस्तारः_2 = गवाक्षः->max_w;
                max_height = गवाक्षः->max_h;
            } अन्यथा {
                // Use the fixed size in the odd case where a non-resizable window somehow wound up tiled or maximized.
                min_विस्तारः_2 = गवाक्षः->floating.w;
                min_height = गवाक्षः->floating.h;
                max_विस्तारः_2 = गवाक्षः->floating.w;
                max_height = गवाक्षः->floating.h;
            }

            यदि (min_विस्तारः_2) {
                viewport_विस्तारः = SDL_max(viewport_विस्तारः, min_विस्तारः_2);
            }
            यदि (min_height) {
                viewport_height = SDL_max(viewport_height, min_height);
            }
            यदि (max_विस्तारः_2) {
                viewport_विस्तारः = SDL_min(viewport_विस्तारः, max_विस्तारः_2);
            }
            यदि (max_height) {
                viewport_height = SDL_min(viewport_height, max_height);
            }

            भिन्न aspect = (भिन्न)viewport_विस्तारः / (भिन्न)viewport_height;
            यदि (गवाक्षः->min_aspect != 0.f && aspect < गवाक्षः->min_aspect) {
                viewport_height = SDL_max(SDL_lroundf((भिन्न)viewport_विस्तारः / गवाक्षः->min_aspect), 1);
            } अन्यथा यदि (गवाक्षः->max_aspect != 0.f && aspect > गवाक्षः->max_aspect) {
                viewport_विस्तारः = SDL_max(SDL_lroundf((भिन्न)viewport_height * गवाक्षः->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            गवाक्षः_विस्तारः = viewport_विस्तारः;
            गवाक्षः_height = viewport_height;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            यदि (!दत्त->scale_गन्तव्यम्_display) {
                यदि (viewport_विस्तारः > दत्त->requested.logical_विस्तारः || viewport_height > दत्त->requested.logical_height) {
                    aspect = (भिन्न)viewport_विस्तारः / (भिन्न)viewport_height;
                    ध्रुव भिन्न गवाक्षः_अनुपातः = (भिन्न)दत्त->requested.logical_विस्तारः / (भिन्न)दत्त->requested.logical_height;
                    यदि (aspect >= गवाक्षः_अनुपातः) {
                        viewport_विस्तारः = दत्त->requested.logical_विस्तारः;
                        viewport_height = SDL_lroundf((भिन्न)viewport_विस्तारः / aspect);
                    } अन्यथा यदि (aspect < गवाक्षः_अनुपातः) {
                        viewport_height = दत्त->requested.logical_height;
                        viewport_विस्तारः = SDL_lroundf((भिन्न)viewport_height * aspect);
                    }
                }
            } अन्यथा {
                यदि (viewport_विस्तारः > दत्त->requested.pixel_विस्तारः || viewport_height > दत्त->requested.pixel_height) {
                    aspect = (भिन्न)viewport_विस्तारः / (भिन्न)viewport_height;
                    ध्रुव भिन्न गवाक्षः_अनुपातः = (भिन्न)दत्त->requested.pixel_विस्तारः / (भिन्न)दत्त->requested.pixel_height;
                    यदि (aspect >= गवाक्षः_अनुपातः) {
                        viewport_विस्तारः = दत्त->requested.pixel_विस्तारः;
                        viewport_height = SDL_lroundf((भिन्न)viewport_विस्तारः / aspect);
                    } अन्यथा यदि (aspect < गवाक्षः_अनुपातः) {
                        viewport_height = दत्त->requested.pixel_height;
                        viewport_विस्तारः = SDL_lroundf((भिन्न)viewport_height * aspect);
                    }
                }
            }

            viewport_विस्तारः = SDL_max(viewport_विस्तारः, 1);
            viewport_height = SDL_max(viewport_height, 1);
        } अन्यथा {
            गवाक्षः_विस्तारः = viewport_विस्तारः;
            गवाक्षः_height = viewport_height;
        }

        यदि (!दत्त->scale_गन्तव्यम्_display) {
            दत्त->current.pixel_विस्तारः = Point_गन्तव्यम्_Pixel(गवाक्षः, गवाक्षः_विस्तारः);
            दत्त->current.pixel_height = Point_गन्तव्यम्_Pixel(गवाक्षः, गवाक्षः_height);
        } अन्यथा {
            // The viewport size is in pixels at this point; convert it to logical units.
            दत्त->current.pixel_विस्तारः = गवाक्षः_विस्तारः;
            दत्त->current.pixel_height = गवाक्षः_height;
            viewport_विस्तारः = Pixel_गन्तव्यम्_Point(गवाक्षः, viewport_विस्तारः);
            viewport_height = Pixel_गन्तव्यम्_Point(गवाक्षः, viewport_height);
        }

        // Clamp the physical window size to the system minimum required size.
        दत्त->requested.logical_विस्तारः = SDL_max(दत्त->requested.logical_विस्तारः, दत्त->system_limits.min_विस्तारः_2);
        दत्त->requested.logical_height = SDL_max(दत्त->requested.logical_height, दत्त->system_limits.min_height);

        गवाक्षः_आकार_परिवर्तितम् = दत्त->requested.logical_विस्तारः != दत्त->current.logical_विस्तारः ||
                              दत्त->requested.logical_height != दत्त->current.logical_height ||
                              viewport_विस्तारः != दत्त->current.viewport_विस्तारः ||
                              viewport_height != दत्त->current.viewport_height;

        बफर_आकार_परिवर्तितम् = दत्त->current.pixel_विस्तारः != old_pixel_विस्तारः ||
                              दत्त->current.pixel_height != old_pixel_height;

        यदि (गवाक्षः_आकार_परिवर्तितम् || बफर_आकार_परिवर्तितम्) {
            यदि (दत्त->viewport) {
                wp_viewport_समुच्चयः_destination(दत्त->viewport, viewport_विस्तारः, viewport_height);
            } अन्यथा यदि (गवाक्षः->flags & SDL_गवाक्षः_उच्चः_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_समुच्चयः_बफर_scale(दत्त->surface, (int32_t)scale_गुणकः_2);
            }

            दत्त->current.logical_विस्तारः = दत्त->requested.logical_विस्तारः;
            दत्त->current.logical_height = दत्त->requested.logical_height;
            दत्त->current.viewport_विस्तारः = viewport_विस्तारः;
            दत्त->current.viewport_height = viewport_height;

            दत्त->pointer_scale.x = (द्विगुण)गवाक्षः_विस्तारः / (द्विगुण)viewport_विस्तारः;
            दत्त->pointer_scale.y = (द्विगुण)गवाक्षः_height / (द्विगुण)viewport_height;
        }
    }

    यदि (दत्त->egl_गवाक्षः && बफर_आकार_परिवर्तितम्) {
        WAYLAND_wl_egl_गवाक्षः_resize(दत्त->egl_गवाक्षः,
                                     दत्त->current.pixel_विस्तारः,
                                     दत्त->current.pixel_height,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    यदि (!दत्त->enable_insets && दत्त->viewport && दत्त->wayland_दत्त->subcompositor && (!दत्त->is_fullscreen || Should_आवरणम्_Fullscreen()) &&
        (viewport_विस्तारः != दत्त->current.logical_विस्तारः || viewport_height != दत्त->current.logical_height)) {
        संरचना wl_बफर *old_बफर = रिक्त;

        यदि (!दत्त->आवरणम्.surface) {
            दत्त->आवरणम्.surface = wl_compositor_create_surface(दत्त->wayland_दत्त->compositor);
            SDL_WAYLAND_पञ्जिकाकोशः_surface(दत्त->आवरणम्.surface);
            wl_surface_समुच्चयः_user_दत्त(दत्त->आवरणम्.surface, दत्त);
        }
        यदि (!दत्त->आवरणम्.subsurface) {
            दत्त->आवरणम्.subsurface = wl_subcompositor_get_subsurface(दत्त->wayland_दत्त->subcompositor, दत्त->आवरणम्.surface, दत्त->surface);
        }
        यदि (!दत्त->आवरणम्.viewport) {
            दत्त->आवरणम्.viewport = wp_viewporter_get_viewport(दत्त->wayland_दत्त->viewporter, दत्त->आवरणम्.surface);
        }
        यदि (!दत्त->आवरणम्.बफर_2 || दत्त->आवरणम्.opaque != is_opaque) {
            old_बफर = दत्त->आवरणम्.बफर_2;
            दत्त->आवरणम्.opaque = is_opaque;
            दत्त->आवरणम्.बफर_2 = Wayland_Create_Single_Pixel_बफर(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(दत्त->आवरणम्.surface, दत्त->आवरणम्.बफर_2, 0, 0);

        wl_subsurface_place_अधः(दत्त->आवरणम्.subsurface, दत्त->surface);
        wp_viewport_समुच्चयः_destination(दत्त->आवरणम्.viewport, दत्त->current.logical_विस्तारः, दत्त->current.logical_height);

        यदि (wl_surface_get_संस्करणम्(दत्त->आवरणम्.surface) >= WL_SURFACE_DAMAGE_बफर_SINCE_संस्करणम्) {
            wl_surface_damage_बफर(दत्त->आवरणम्.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } अन्यथा {
            wl_surface_damage(दत्त->आवरणम्.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        यदि (is_opaque) {
            समुच्चयः_Surface_Opaque_Region(दत्त->आवरणम्.surface, दत्त->current.logical_विस्तारः, दत्त->current.logical_height);
        } अन्यथा {
            समुच्चयः_Surface_Opaque_Region(दत्त->आवरणम्.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        यदि (दत्त->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            दत्त->आवरणम्.विस्थापनम्_x = -(दत्त->current.logical_विस्तारः - viewport_विस्तारः) / 2;
            दत्त->आवरणम्.विस्थापनम्_y = -(दत्त->current.logical_height - viewport_height) / 2;
        } अन्यथा {
            दत्त->आवरणम्.विस्थापनम्_x = 0;
            दत्त->आवरणम्.विस्थापनम्_y = 0;
        }

        wl_subsurface_समुच्चयः_position(दत्त->आवरणम्.subsurface, दत्त->आवरणम्.विस्थापनम्_x, दत्त->आवरणम्.विस्थापनम्_y);
        wl_surface_commit(दत्त->आवरणम्.surface);

        यदि (old_बफर) {
            wl_बफर_destroy(old_बफर);
        }

        दत्त->आवरणम्.mapped = true;
    } अन्यथा यदि (दत्त->आवरणम्.mapped) {
        wl_subsurface_समुच्चयः_position(दत्त->आवरणम्.subsurface, 0, 0);
        wl_surface_attach(दत्त->आवरणम्.surface, रिक्त, 0, 0);
        wl_surface_commit(दत्त->आवरणम्.surface);

        दत्त->आवरणम्.विस्थापनम्_x = 0;
        दत्त->आवरणम्.विस्थापनम्_y = 0;
        दत्त->आवरणम्.mapped = false;
    }

    यदि (दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && दत्त->shell_surface.xdg.surface &&
        (दत्त->enable_insets || !दत्त->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(गवाक्षः, &insets);
        ध्रुव bool use_insets = (insets.वामः || insets.शिखरम् || insets.दक्षिणः || insets.bottom) &&
                                !(गवाक्षः->flags & (SDL_गवाक्षः_MAXIMIZED | SDL_गवाक्षः_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, दत्त->current.logical_विस्तारः, दत्त->current.logical_height };
        यदि (use_insets) {
            geometry.x = insets.वामः;
            geometry.y = insets.शिखरम्;
            geometry.w = SDL_max(geometry.w - (insets.वामः + insets.दक्षिणः), 1);
            geometry.h = SDL_max(geometry.h - (insets.शिखरम् + insets.bottom), 1);
        }
        /* An explicitly set geometry does not track the surface, so it must be kept in sync
         * once set. Otherwise this is only done when viewports aren't supported and the size
         * has changed (XXX: a hack) to avoid a potential protocol violation if a buffer with
         * an old size is committed.
         */
        यदि ((use_insets || !SDL_Rect_रिक्तानि(&दत्त->explicit_geometry) || (!दत्त->viewport && गवाक्षः_आकार_परिवर्तितम्)) &&
            !SDL_RectsEqual(&geometry, &दत्त->explicit_geometry)) {
            xdg_surface_समुच्चयः_गवाक्षः_geometry(दत्त->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            दत्त->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    यदि (गवाक्षः_आकार_परिवर्तितम्) {
        यदि (is_opaque) {
            समुच्चयः_Surface_Opaque_Region(दत्त->surface, viewport_विस्तारः, viewport_height);
        } अन्यथा {
            समुच्चयः_Surface_Opaque_Region(दत्त->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        प्रति (SDL_गवाक्षः *child = गवाक्षः->first_child; child; child = child->अग्र_sibling) {
            RepositionPopup(child, true);
        }
    }

    // Update the scale for any focused cursors.
    यदि (पूर्व_pointer_scale_x != दत्त->pointer_scale.x || पूर्व_pointer_scale_y != दत्त->pointer_scale.y) {
        Wayland_DisplayUpdatePointerFocusedScale(दत्त);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    समुच्चयः_Min_Max_Dimensions(गवाक्षः);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    यदि (!दत्त->scale_गन्तव्यम्_display) {
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, गवाक्षः_विस्तारः, गवाक्षः_height);
    } अन्यथा {
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESIZED, दत्त->current.pixel_विस्तारः, दत्त->current.pixel_height);
    }
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_PIXEL_आकार_परिवर्तितम्, दत्त->current.pixel_विस्तारः, दत्त->current.pixel_height);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    यदि (दत्त->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN) {
        यदि ((बफर_आकार_परिवर्तितम् || गवाक्षः_आकार_परिवर्तितम्) ||
            (!दत्त->suspended && (गवाक्षः->flags & SDL_गवाक्षः_OCCLUDED))) {
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_EXPOSED, 0, 0);
        }

        यदि (दत्त->suspended) {
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_OCCLUDED, 0, 0);
        }
    }
}

स्थिर शून्य CommitLibdecorFrame(SDL_गवाक्षः *गवाक्षः)
{
#यदि_परिभाषितम् HAVE_LIBDECOR_H
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        संरचना libdecor_state *state = libdecor_state_new(wind->current.logical_विस्तारः, wind->current.logical_height);
        libdecor_frame_commit(wind->shell_surface.libdecor.frame, state, रिक्त);
        libdecor_state_free(state);
    }
#यदि_अन्तः
}

स्थिर शून्य pending_state_deadline_handler(शून्य *दत्त, संरचना wl_callback *callback, uint32_t callback_दत्त)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_गवाक्षः_ID गवाक्षः_ID = (SDL_गवाक्षः_ID)(uintptr_t)दत्त;
    SDL_गवाक्षः *गवाक्षः = SDL_Get_गवाक्षः_From_ID(गवाक्षः_ID);

    यदि (गवाक्षः && गवाक्षः->आन्तरिकम्) {
        --गवाक्षः->आन्तरिकम्->pending_state_deadline_गणनम्;
    }

    wl_callback_destroy(callback);
}

स्थिर संरचना wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

स्थिर शून्य सङ्कलय_Pending_State_Sync(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2)
{
    SDL_Video_दत्त *video_दत्त = गवाक्षः_दत्त_2->wayland_दत्त;
    शून्य *cb_दत्त = (शून्य *)(uintptr_t)गवाक्षः_दत्त_2->sdlwindow->id;

    ++गवाक्षः_दत्त_2->pending_state_deadline_गणनम्;
    संरचना wl_callback *cb = wl_display_sync(video_दत्त->display);
    wl_callback_सङ्कलय_listener(cb, &pending_state_deadline_listener, cb_दत्त);
}

स्थिर शून्य FlushPendingEvents(SDL_गवाक्षः *गवाक्षः)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ध्रुव bool चरमः_position_pending = गवाक्षः->चरमः_position_pending;
    ध्रुव bool चरमः_आकार_pending = गवाक्षः->चरमः_आकार_pending;

    यावत् (गवाक्षः->आन्तरिकम्->pending_state_deadline_गणनम्) {
        WAYLAND_wl_display_roundtrip(गवाक्षः->आन्तरिकम्->wayland_दत्त->display);
    }

    गवाक्षः->चरमः_position_pending = चरमः_position_pending;
    गवाक्षः->चरमः_आकार_pending = चरमः_आकार_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
शून्य Wayland_Update_गवाक्षः_Position(SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;
    SDL_Display_दत्त *display;

    यदि (wind->outputs && wind->अङ्कः_outputs) {
        display = wind->outputs[wind->अङ्कः_outputs - 1];
    } अन्यथा {
        // A window may not be on any displays if minimized.
        प्रत्यागम;
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
    wind->चरमः_display_ID = display->display;
    यदि (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        यदि (!wind->wayland_दत्त->scale_गन्तव्यम्_display_enabled) {
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_MOVED, display->logical.x, display->logical.y);
        } अन्यथा {
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_DISPLAY_परिवर्तितम्, wind->चरमः_display_ID, 0);
    }
}

स्थिर शून्य समुच्चयः_Fullscreen(SDL_गवाक्षः *गवाक्षः, संरचना wl_output *output, bool fullscreen)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (!wind->shell_surface.libdecor.frame) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? गवाक्षः->fullscreen_exclusive : false;
        यदि (fullscreen) {
            libdecor_frame_समुच्चयः_fullscreen(wind->shell_surface.libdecor.frame, output);
        } अन्यथा {
            libdecor_frame_unset_fullscreen(wind->shell_surface.libdecor.frame);
        }
    } अन्यथा
#यदि_अन्तः
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel == रिक्त) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? गवाक्षः->fullscreen_exclusive : false;
        यदि (fullscreen) {
            xdg_toplevel_समुच्चयः_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } अन्यथा {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    सङ्कलय_Pending_State_Sync(wind);
}

स्थिर शून्य Update_गवाक्षः_Fullscreen(SDL_गवाक्षः *गवाक्षः, bool fullscreen)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    wind->is_fullscreen = fullscreen;

    यदि (fullscreen) {
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN)) {
            SDL_copyp(&गवाक्षः->current_fullscreen_बहुलकम्, &गवाक्षः->requested_fullscreen_बहुलकम्);
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_ENTER_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            यदि (गवाक्षः->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(गवाक्षः->current_fullscreen_बहुलकम्.displayID);
                यदि (disp) {
                    wind->fullscreen_was_positioned = true;
                    समुच्चयः_Fullscreen(गवाक्षः, disp->आन्तरिकम्->output, true);
                }
            }
        }
    } अन्यथा {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        यदि ((गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) && !गवाक्षः->is_hiding && !(गवाक्षः->flags & SDL_गवाक्षः_HIDDEN)) {
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_LEAVE_FULLSCREEN, 0, 0);
            SDL_Update_Fullscreen_बहुलकम्(गवाक्षः, SDL_FULLSCREEN_OP_LEAVE, false);
            wind->fullscreen_was_positioned = false;

            /* Send a move event, in case it was deferred while the fullscreen window was moving and
             * on multiple outputs.
             */
            Wayland_Update_गवाक्षः_Position(गवाक्षः);
        }
    }
}

स्थिर ध्रुव संरचना wl_callback_listener surface_frame_listener;

स्थिर शून्य surface_frame_समाप्तम्(शून्य *दत्त, संरचना wl_callback *cb, uint32_t time)
{
    SDL_गवाक्षः_दत्त *wind = (SDL_गवाक्षः_दत्त *)दत्त;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    यदि (wl_compositor_get_संस्करणम्(wind->wayland_दत्त->compositor) >= WL_SURFACE_DAMAGE_बफर_SINCE_संस्करणम्) {
        wl_surface_damage_बफर(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } अन्यथा {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            Configure_गवाक्षः_Geometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } अन्यथा {
        wind->resizing = false;
    }

    यदि (wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_FRAME) {
        wind->shell_surface_स्थितिः = WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        प्रति (SDL_गवाक्षः *w = wind->sdlwindow->first_child; w; w = w->अग्र_sibling) {
            यदि (w->आन्तरिकम्->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_SHOW_PENDING) {
                Wayland_Show_गवाक्षः(SDL_GetVideoDevice(), w);
            } अन्यथा यदि (w->आन्तरिकम्->reparenting_required) {
                Wayland_समुच्चयः_गवाक्षः_Parent(SDL_GetVideoDevice(), w, w->parent);
                यदि (w->flags & SDL_गवाक्षः_MODAL) {
                    Wayland_समुच्चयः_गवाक्षः_Modal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        यदि (wind->suspended) {
            SDL_Send_गवाक्षः_Event(wind->sdlwindow, SDL_EVENT_गवाक्षः_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_frame_callback = wl_surface_frame(wind->surface);
    wl_callback_सङ्कलय_listener(wind->surface_frame_callback, &surface_frame_listener, दत्त);
}

स्थिर ध्रुव संरचना wl_callback_listener surface_frame_listener = {
    surface_frame_समाप्तम्
};

स्थिर ध्रुव संरचना wl_callback_listener gles_swap_frame_listener;

स्थिर शून्य gles_swap_frame_समाप्तम्(शून्य *दत्त, संरचना wl_callback *cb, uint32_t time)
{
    SDL_गवाक्षः_दत्त *wind = (SDL_गवाक्षः_दत्त *)दत्त;
    SDL_समुच्चयः_Atomic_Int(&wind->swap_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_swap_frame_callback = wl_surface_frame(wind->gles_swap_frame_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_सङ्कलय_listener(wind->gles_swap_frame_callback, &gles_swap_frame_listener, दत्त);
}

स्थिर ध्रुव संरचना wl_callback_listener gles_swap_frame_listener = {
    gles_swap_frame_समाप्तम्
};

स्थिर शून्य handle_xdg_surface_configure(शून्य *दत्त, संरचना xdg_surface *xdg, uint32_t serial)
{
    SDL_गवाक्षः_दत्त *wind = (SDL_गवाक्षः_दत्त *)दत्त;
    SDL_गवाक्षः *गवाक्षः = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    यदि (!wind->resizing) {
        wind->pending_config_ack = false;
        Configure_गवाक्षः_Geometry(गवाक्षः);
        xdg_surface_ack_configure(xdg, serial);
    } अन्यथा यदि (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_EXPOSED, 0, 0);
    }

    यदि (wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE) {
        wind->shell_surface_स्थितिः = WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_FRAME;
    }
}

स्थिर ध्रुव संरचना xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

स्थिर शून्य ApplyGeometryLimits(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क req_w, पूर्णाङ्क req_h, पूर्णाङ्क *बहिर्गमनम्_w, पूर्णाङ्क *बहिर्गमनम्_h)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    पूर्णाङ्क w = req_w;
    पूर्णाङ्क h = req_h;
    ध्रुव भिन्न aspect = (भिन्न)req_w / (भिन्न)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    यदि (!wind->resizing || (wind->resize_edge & WAYLAND_RESIZE_EDGE_CORNER) == WAYLAND_RESIZE_EDGE_CORNER) {
        यदि (गवाक्षः->min_aspect != 0.f && aspect < गवाक्षः->min_aspect) {
            h = SDL_max(SDL_lroundf((भिन्न)req_w / गवाक्षः->min_aspect), 1);

            यदि (h < गवाक्षः->min_h) {
                w = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->min_h * गवाक्षः->min_aspect), 1);
            }
            यदि (गवाक्षः->max_h && h > गवाक्षः->max_h) {
                w = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->max_h * गवाक्षः->min_aspect), 1);
            }
        } अन्यथा यदि (गवाक्षः->max_aspect != 0.f && aspect > गवाक्षः->max_aspect) {
            w = SDL_max(SDL_lroundf((भिन्न)req_h * गवाक्षः->max_aspect), 1);

            यदि (w < गवाक्षः->min_w) {
                h = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->min_w / गवाक्षः->max_aspect), 1);
            }
            यदि (गवाक्षः->max_w && w > गवाक्षः->max_w) {
                h = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->max_w / गवाक्षः->max_aspect), 1);
            }
        }
    } अन्यथा यदि (wind->resize_edge & WAYLAND_RESIZE_EDGE_LR) {
        यदि (गवाक्षः->min_aspect != 0.f && aspect < गवाक्षः->min_aspect) {
            h = SDL_max(SDL_lroundf((भिन्न)req_w / गवाक्षः->min_aspect), 1);

            यदि (h < गवाक्षः->min_h) {
                w = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->min_h * गवाक्षः->min_aspect), 1);
            }
            यदि (गवाक्षः->max_h && h > गवाक्षः->max_h) {
                w = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->max_h * गवाक्षः->min_aspect), 1);
            }
        } अन्यथा यदि (गवाक्षः->max_aspect != 0.f && aspect > गवाक्षः->max_aspect) {
            h = SDL_max(SDL_lroundf((भिन्न)req_w / गवाक्षः->max_aspect), 1);

            यदि (h < गवाक्षः->min_h) {
                w = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->min_h * गवाक्षः->max_aspect), 1);
            }
            यदि (गवाक्षः->max_h && h > गवाक्षः->max_h) {
                w = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->max_h * गवाक्षः->max_aspect), 1);
            }
        }
    } अन्यथा यदि (wind->resize_edge & WAYLAND_RESIZE_EDGE_TB) {
        यदि (गवाक्षः->min_aspect != 0.f && aspect < गवाक्षः->min_aspect) {
            w = SDL_max(SDL_lroundf((भिन्न)req_h * गवाक्षः->min_aspect), 1);

            यदि (w < गवाक्षः->min_w) {
                h = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->min_w / गवाक्षः->min_aspect), 1);
            }
            यदि (गवाक्षः->max_w && w > गवाक्षः->max_w) {
                h = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->max_w / गवाक्षः->min_aspect), 1);
            }
        } अन्यथा यदि (गवाक्षः->max_aspect != 0.f && aspect > गवाक्षः->max_aspect) {
            w = SDL_max(SDL_lroundf((भिन्न)req_h * गवाक्षः->max_aspect), 1);

            यदि (w < गवाक्षः->min_w) {
                h = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->min_w / गवाक्षः->max_aspect), 1);
            }
            यदि (गवाक्षः->max_w && w > गवाक्षः->max_w) {
                h = SDL_max(SDL_lroundf((भिन्न)गवाक्षः->max_w / गवाक्षः->max_aspect), 1);
            }
        }
    }

    यदि (गवाक्षः->max_w) {
        w = SDL_min(w, गवाक्षः->max_w);
    }
    *बहिर्गमनम्_w = SDL_max(w, गवाक्षः->min_w);

    यदि (गवाक्षः->max_h) {
        h = SDL_min(h, गवाक्षः->max_h);
    }
    *बहिर्गमनम्_h = SDL_max(h, गवाक्षः->min_h);

}

स्थिर शून्य DetermineResizeAxis(SDL_गवाक्षः_दत्त *wind, पूर्णाङ्क विस्तारः, पूर्णाङ्क height, bool resizing)
{
    /* Try to determine the axis along which the window is being resized.
     *
     * Every compositor is different, and some will start sending strange values once the resize
     * begins, so only the first change is safe to try and determine the resize edge.
     *
     * Some compositors don't send a configure event with the resize flag cleared when the resize ends,
     * so a reset timer is required.
     */
    यदि (resizing) {
        ध्रुव Uint64 now = SDL_GetTicksNS();
        यदि (now >= wind->चरमः_resize_event_time_ns + SDL_MS_गन्तव्यम्_NS(500)) {
            wind->resize_edge = 0;
        }

        wind->चरमः_resize_event_time_ns = now;

        यदि (!wind->resize_edge) {
            यदि (विस्तारः != wind->चरमः_configure.विस्तारः || !height) {
                wind->resize_edge |= WAYLAND_RESIZE_EDGE_LR;
            }
            यदि (height != wind->चरमः_configure.height || !विस्तारः) {
                wind->resize_edge |= WAYLAND_RESIZE_EDGE_TB;
            }
        }
    } अन्यथा {
        wind->resize_edge = 0;
    }

    wind->resizing = resizing;
}

स्थिर शून्य handle_xdg_toplevel_configure(शून्य *दत्त,
                                          संरचना xdg_toplevel *xdg_toplevel,
                                          int32_t विस्तारः,
                                          int32_t height,
                                          संरचना wl_array *अवस्थाः)
{
    SDL_गवाक्षः_दत्त *wind = (SDL_गवाक्षः_दत्त *)दत्त;
    SDL_गवाक्षः *गवाक्षः = wind->sdlwindow;

    गणना xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool सक्रिय = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, अवस्थाः) {
        विकल्प (*state) {
        पक्ष XDG_TOPLEVEL_STATE_FULLSCREEN:
            fullscreen = true;
            floating = false;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_MAXIMIZED:
            maximized = true;
            floating = false;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_RESIZING:
            resizing = true;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_ACTIVATED:
            सक्रिय = true;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_TILED_वामः:
        पक्ष XDG_TOPLEVEL_STATE_TILED_दक्षिणः:
        पक्ष XDG_TOPLEVEL_STATE_TILED_शिखरम्:
        पक्ष XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_CONSTRAINED_वामः:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_वामः;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_CONSTRAINED_दक्षिणः:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_दक्षिणः;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_CONSTRAINED_शिखरम्:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_शिखरम्;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_CONSTRAINED_BOTTOM:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
            भङ्ग;
        स्वभाव:
            भङ्ग;
        }
    }

    /* Configure sizes are in window geometry space; add the border insets, if any, to get
     * the surface size. Maximized and fullscreen windows must use the configured size as-is,
     * so a change in inset applicability requires re-adopting even an unchanged size, and
     * sizes adopted from the cached window size are converted back to geometry space for
     * the last_configure store.
     */
    ध्रुव bool insets_apply = wind->enable_insets && !fullscreen && !maximized;

    // When resizing, dimensions other than 0 are a maximum.
    ध्रुव bool new_configure_आकार = विस्तारः != wind->चरमः_configure.विस्तारः || height != wind->चरमः_configure.height ||
                                    insets_apply != wind->चरमः_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    यदि (insets_apply) {
        GetBorderInsets(गवाक्षः, &insets);
    }

    DetermineResizeAxis(wind, विस्तारः, height, resizing);
    Update_गवाक्षः_Fullscreen(गवाक्षः, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from xdg-shell, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    यदि (सक्रिय || !(गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED)) {
        यदि (गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESTORED, 0, 0);
        }
        SDL_Send_गवाक्षः_Event(गवाक्षः,
                            (maximized && !fullscreen) ? SDL_EVENT_गवाक्षः_MAXIMIZED : SDL_EVENT_गवाक्षः_RESTORED,
                            0, 0);
    }

    यदि (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        यदि ((गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE) || maximized) {
            यदि (!विस्तारः) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                यदि (floating) {
                    विस्तारः = गवाक्षः->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    यदि (wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE && wind->toplevel_bounds.विस्तारः) {
                        विस्तारः = SDL_min(wind->toplevel_bounds.विस्तारः, विस्तारः);
                    }
                } अन्यथा {
                    विस्तारः = गवाक्षः->windowed.w;
                }

                यदि (!wind->scale_गन्तव्यम्_display) {
                    wind->requested.logical_विस्तारः = विस्तारः;
                } अन्यथा {
                    wind->requested.pixel_विस्तारः = विस्तारः;
                    विस्तारः = wind->requested.logical_विस्तारः = Pixel_गन्तव्यम्_Point(गवाक्षः, विस्तारः);
                }
                विस्तारः = SDL_max(विस्तारः - (insets.वामः + insets.दक्षिणः), 1);
            } अन्यथा यदि (new_configure_आकार) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_विस्तारः = विस्तारः + (insets.वामः + insets.दक्षिणः);

                यदि (wind->scale_गन्तव्यम्_display) {
                    wind->requested.pixel_विस्तारः = Point_गन्तव्यम्_Pixel(गवाक्षः, wind->requested.logical_विस्तारः);
                }
            }
            यदि (!height) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                यदि (floating) {
                    height = गवाक्षः->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    यदि (wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE && wind->toplevel_bounds.height) {
                        height = SDL_min(wind->toplevel_bounds.height, height);
                    }
                } अन्यथा {
                    height = गवाक्षः->windowed.h;
                }

                यदि (!wind->scale_गन्तव्यम्_display) {
                    wind->requested.logical_height = height;
                } अन्यथा {
                    wind->requested.pixel_height = height;
                    height = wind->requested.logical_height = Pixel_गन्तव्यम्_Point(गवाक्षः, height);
                }
                height = SDL_max(height - (insets.शिखरम् + insets.bottom), 1);
            } अन्यथा यदि (new_configure_आकार) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_height = height + (insets.शिखरम् + insets.bottom);

                यदि (wind->scale_गन्तव्यम्_display) {
                    wind->requested.pixel_height = Point_गन्तव्यम्_Pixel(गवाक्षः, wind->requested.logical_height);
                }
            }
        } अन्यथा {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            यदि (!wind->scale_गन्तव्यम्_display) {
                विस्तारः = wind->requested.logical_विस्तारः = गवाक्षः->floating.w;
                height = wind->requested.logical_height = गवाक्षः->floating.h;
            } अन्यथा {
                wind->requested.pixel_विस्तारः = गवाक्षः->floating.w;
                wind->requested.pixel_height = गवाक्षः->floating.h;
                विस्तारः = wind->requested.logical_विस्तारः = Pixel_गन्तव्यम्_Point(गवाक्षः, गवाक्षः->floating.w);
                height = wind->requested.logical_height = Pixel_गन्तव्यम्_Point(गवाक्षः, गवाक्षः->floating.h);
            }
            विस्तारः = SDL_max(विस्तारः - (insets.वामः + insets.दक्षिणः), 1);
            height = SDL_max(height - (insets.शिखरम् + insets.bottom), 1);
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
        यदि (floating) {
            यदि (!wind->scale_गन्तव्यम्_display) {
                ApplyGeometryLimits(गवाक्षः, wind->requested.logical_विस्तारः, wind->requested.logical_height, &wind->requested.logical_विस्तारः, &wind->requested.logical_height);
            } अन्यथा {
                ApplyGeometryLimits(गवाक्षः, wind->requested.pixel_विस्तारः, wind->requested.pixel_height, &wind->requested.pixel_विस्तारः, &wind->requested.pixel_height);

                wind->requested.logical_विस्तारः = Pixel_गन्तव्यम्_Point(गवाक्षः, wind->requested.pixel_विस्तारः);
                wind->requested.logical_height = Pixel_गन्तव्यम्_Point(गवाक्षः, wind->requested.pixel_height);
            }
        }
    } अन्यथा {
        // Fullscreen windows know their exact size.
        यदि (विस्तारः == 0 || height == 0) {
            विस्तारः = wind->requested.logical_विस्तारः;
            height = wind->requested.logical_height;
        } अन्यथा {
            wind->requested.logical_विस्तारः = विस्तारः;
            wind->requested.logical_height = height;
        }

        यदि (wind->scale_गन्तव्यम्_display) {
            wind->requested.pixel_विस्तारः = Point_गन्तव्यम्_Pixel(गवाक्षः, विस्तारः);
            wind->requested.pixel_height = Point_गन्तव्यम्_Pixel(गवाक्षः, height);
        }
    }

    wind->चरमः_configure.विस्तारः = विस्तारः;
    wind->चरमः_configure.height = height;
    wind->चरमः_configure.insets_apply = insets_apply;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->सक्रिय = सक्रिय;
    गवाक्षः->tiled = tiled;
}

स्थिर शून्य handle_xdg_toplevel_close(शून्य *दत्त, संरचना xdg_toplevel *xdg_toplevel)
{
    SDL_गवाक्षः_दत्त *गवाक्षः = (SDL_गवाक्षः_दत्त *)दत्त;
    SDL_Send_गवाक्षः_Event(गवाक्षः->sdlwindow, SDL_EVENT_गवाक्षः_CLOSE_REQUESTED, 0, 0);
}

स्थिर शून्य handle_xdg_toplevel_configure_bounds(शून्य *दत्त,
                                                 संरचना xdg_toplevel *xdg_toplevel,
                                                 int32_t विस्तारः, int32_t height)
{
    SDL_गवाक्षः_दत्त *गवाक्षः = (SDL_गवाक्षः_दत्त *)दत्त;
    गवाक्षः->toplevel_bounds.विस्तारः = विस्तारः;
    गवाक्षः->toplevel_bounds.height = height;
}

स्थिर शून्य handle_xdg_toplevel_wm_capabilities(शून्य *दत्त,
                                                संरचना xdg_toplevel *xdg_toplevel,
                                                संरचना wl_array *capabilities)
{
    SDL_गवाक्षः_दत्त *wind = (SDL_गवाक्षः_दत्त *)दत्त;
    गणना xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        विकल्प (*wm_cap) {
        पक्ष XDG_TOPLEVEL_WM_CAPABILITIES_गवाक्षः_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_गवाक्षः_MENU;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_WM_CAPABILITIES_MAXIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MAXIMIZE;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_WM_CAPABILITIES_FULLSCREEN:
            wind->wm_caps |= WAYLAND_WM_CAPS_FULLSCREEN;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_WM_CAPABILITIES_MINIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MINIMIZE;
            भङ्ग;
        स्वभाव:
            भङ्ग;
        }
    }
}

स्थिर ध्रुव संरचना xdg_toplevel_listener toplevel_listener_xdg = {
    handle_xdg_toplevel_configure,
    handle_xdg_toplevel_close,
    handle_xdg_toplevel_configure_bounds, // Version 4
    handle_xdg_toplevel_wm_capabilities   // Version 5
};

स्थिर शून्य handle_xdg_popup_configure(शून्य *दत्त,
                                       संरचना xdg_popup *xdg_popup,
                                       int32_t x,
                                       int32_t y,
                                       int32_t विस्तारः,
                                       int32_t height)
{
    SDL_गवाक्षः_दत्त *wind = (SDL_गवाक्षः_दत्त *)दत्त;
    पूर्णाङ्क विस्थापनम्_x = 0, विस्थापनम्_y = 0;

    // Adjust the position if it was offset for libdecor
    Adjust_Popup_विस्थापनम्(wind->sdlwindow, &विस्थापनम्_x, &विस्थापनम्_y);
    x -= विस्थापनम्_x;
    y -= विस्थापनम्_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    यदि (विस्तारः == 0 || height == 0) {
        विस्तारः = wind->sdlwindow->floating.w;
        height = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    यदि (विस्तारः != wind->चरमः_configure.विस्तारः || height != wind->चरमः_configure.height) {
        wind->requested.logical_विस्तारः = विस्तारः;
        wind->requested.logical_height = height;

        यदि (wind->scale_गन्तव्यम्_display) {
            wind->requested.pixel_विस्तारः = Point_गन्तव्यम्_Pixel(wind->sdlwindow, विस्तारः);
            wind->requested.pixel_height = Point_गन्तव्यम्_Pixel(wind->sdlwindow, height);
        }
    }

    यदि (wind->scale_गन्तव्यम्_display) {
        x = Point_गन्तव्यम्_Pixel(wind->sdlwindow->parent, x);
        y = Point_गन्तव्यम्_Pixel(wind->sdlwindow->parent, y);
    }

    SDL_Send_गवाक्षः_Event(wind->sdlwindow, SDL_EVENT_गवाक्षः_MOVED, x, y);

    wind->चरमः_configure.विस्तारः = विस्तारः;
    wind->चरमः_configure.height = height;

    यदि (wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE) {
        wind->shell_surface_स्थितिः = WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_FRAME;
    }
}

स्थिर शून्य handle_xdg_popup_समाप्तम्(शून्य *दत्त, संरचना xdg_popup *xdg_popup)
{
    SDL_गवाक्षः_दत्त *गवाक्षः = (SDL_गवाक्षः_दत्त *)दत्त;
    SDL_Send_गवाक्षः_Event(गवाक्षः->sdlwindow, SDL_EVENT_गवाक्षः_CLOSE_REQUESTED, 0, 0);
}

स्थिर शून्य handle_xdg_popup_repositioned(शून्य *दत्त,
                                          संरचना xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

स्थिर ध्रुव संरचना xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_समाप्तम्,
    handle_xdg_popup_repositioned
};

स्थिर शून्य handle_xdg_toplevel_decoration_configure(शून्य *दत्त,
                                                     संरचना zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
                                                     uint32_t बहुलकम्)
{
    SDL_गवाक्षः *गवाक्षः = (SDL_गवाक्षः *)दत्त;
    SDL_गवाक्षः_दत्त *आन्तरिकम् = गवाक्षः->आन्तरिकम्;
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    /* If the compositor tries to force CSD anyway, bail on direct XDG support
     * and fall back to libdecor, it will handle these events from then on.
     *
     * To do this we have to fully unmap, then map with libdecor loaded.
     */
    यदि (बहुलकम् == ZXDG_TOPLEVEL_DECORATION_V1_बहुलकम्_CLIENT_SIDE) {
        यदि (गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            प्रत्यागम;
        }
        यदि (!Wayland_आरोपय_Libdecor(आन्तरिकम्->wayland_दत्त, true)) {
            // libdecor isn't available, so no borders for you... oh well
            प्रत्यागम;
        }
        WAYLAND_wl_display_roundtrip(आन्तरिकम्->wayland_दत्त->display);

        Wayland_Hide_गवाक्षः(device, गवाक्षः);
        आन्तरिकम्->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_Show_गवाक्षः(device, गवाक्षः);
    }
}

स्थिर ध्रुव संरचना zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
    handle_xdg_toplevel_decoration_configure
};

#यदि_परिभाषितम् HAVE_LIBDECOR_H
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
स्थिर शून्य OverrideLibdecorLimits(SDL_गवाक्षः *गवाक्षः)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    यदि (!libdecor_frame_get_min_content_आकार) {
        libdecor_frame_समुच्चयः_min_content_आकार(गवाक्षः->आन्तरिकम्->shell_surface.libdecor.frame, गवाक्षः->min_w, गवाक्षः->min_h);
    }
#नोचेद्यदि !SDL_LIBDECOR_CHECK_संस्करणम्(0, 2, 0)
    libdecor_frame_समुच्चयः_min_content_आकार(गवाक्षः->आन्तरिकम्->shell_surface.libdecor.frame, गवाक्षः->min_w, गवाक्षः->min_h);
#यदि_अन्तः
}

/*
 * NOTE: Retrieves the minimum content size limits, if the function for doing so is available.
 *       On versions of libdecor that lack the minimum content size retrieval function, this
 *       function is a no-op.
 *
 *       Can be replaced with a direct call if the minimum required version of libdecor is raised
 *       to 0.1.2 or higher.
 */
स्थिर शून्य Libdecor_Get_Min_Content_आकार(संरचना libdecor_frame *frame, पूर्णाङ्क *min_w, पूर्णाङ्क *min_h)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    यदि (libdecor_frame_get_min_content_आकार != रिक्त) {
        libdecor_frame_get_min_content_आकार(frame, min_w, min_h);
    }
#नोचेद्यदि SDL_LIBDECOR_CHECK_संस्करणम्(0, 2, 0)
    libdecor_frame_get_min_content_आकार(frame, min_w, min_h);
#यदि_अन्तः
}

स्थिर शून्य decoration_frame_configure(संरचना libdecor_frame *frame,
                                       संरचना libdecor_configuration *configuration,
                                       शून्य *user_दत्त_2)
{
    SDL_गवाक्षः_दत्त *wind = (SDL_गवाक्षः_दत्त *)user_दत्त_2;
    SDL_गवाक्षः *गवाक्षः = wind->sdlwindow;

    गणना libdecor_गवाक्षः_state गवाक्षः_state;
    पूर्णाङ्क विस्तारः, height;

    bool सक्रिय = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    स्थिर ध्रुव गणना libdecor_गवाक्षः_state tiled_अवस्थाः = (LIBDECOR_गवाक्षः_STATE_TILED_वामः | LIBDECOR_गवाक्षः_STATE_TILED_दक्षिणः |
                                                            LIBDECOR_गवाक्षः_STATE_TILED_शिखरम् | LIBDECOR_गवाक्षः_STATE_TILED_BOTTOM);

    यदि (wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE) {
        Libdecor_Get_Min_Content_आकार(frame, &wind->system_limits.min_विस्तारः_2, &wind->system_limits.min_height);
    }

    // Window State
    यदि (libdecor_configuration_get_गवाक्षः_state(configuration, &गवाक्षः_state)) {
        fullscreen = (गवाक्षः_state & LIBDECOR_गवाक्षः_STATE_FULLSCREEN) != 0;
        maximized = (गवाक्षः_state & LIBDECOR_गवाक्षः_STATE_MAXIMIZED) != 0;
        सक्रिय = (गवाक्षः_state & LIBDECOR_गवाक्षः_STATE_सक्रिय) != 0;
        tiled = (गवाक्षः_state & tiled_अवस्थाः) != 0;
#यदि SDL_LIBDECOR_CHECK_संस्करणम्(0, 2, 0)
        suspended = (गवाक्षः_state & LIBDECOR_गवाक्षः_STATE_SUSPENDED) != 0;
#यदि_अन्तः
#यदि SDL_LIBDECOR_CHECK_संस्करणम्(0, 3, 0)
        resizing = (गवाक्षः_state & LIBDECOR_गवाक्षः_STATE_RESIZING) != 0;

        यदि (गवाक्षः_state & LIBDECOR_गवाक्षः_STATE_CONSTRAINED_वामः) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_वामः;
        }
        यदि (गवाक्षः_state & LIBDECOR_गवाक्षः_STATE_CONSTRAINED_दक्षिणः) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_दक्षिणः;
        }
        यदि (गवाक्षः_state & LIBDECOR_गवाक्षः_STATE_CONSTRAINED_शिखरम्) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_शिखरम्;
        }
        यदि (गवाक्षः_state & LIBDECOR_गवाक्षः_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#यदि_अन्तः
    }
    ध्रुव bool floating = !(fullscreen || maximized || tiled);

    Update_गवाक्षः_Fullscreen(गवाक्षः, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from libdecor, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    यदि (सक्रिय || !(गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED)) {
        यदि (गवाक्षः->flags & SDL_गवाक्षः_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_RESTORED, 0, 0);
        }
        SDL_Send_गवाक्षः_Event(गवाक्षः,
                            (maximized && !fullscreen) ? SDL_EVENT_गवाक्षः_MAXIMIZED : SDL_EVENT_गवाक्षः_RESTORED,
                            0, 0);
    }

    /* For fullscreen or fixed-size windows we know our size.
     * Always assume the configure is wrong.
     */
    यदि (fullscreen) {
        यदि (!libdecor_configuration_get_content_आकार(configuration, frame, &विस्तारः, &height)) {
            विस्तारः = wind->requested.logical_विस्तारः;
            height = wind->requested.logical_height;
        } अन्यथा {
            // Fullscreen windows know their exact size.
            wind->requested.logical_विस्तारः = विस्तारः;
            wind->requested.logical_height = height;

            यदि (wind->scale_गन्तव्यम्_display) {
                wind->requested.pixel_विस्तारः = Point_गन्तव्यम्_Pixel(गवाक्षः, विस्तारः);
                wind->requested.pixel_height = Point_गन्तव्यम्_Pixel(गवाक्षः, height);
            }
        }
    } अन्यथा {
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            यदि (!wind->scale_गन्तव्यम्_display) {
                विस्तारः = wind->requested.logical_विस्तारः = गवाक्षः->floating.w;
                height = wind->requested.logical_height = गवाक्षः->floating.h;
            } अन्यथा {
                wind->requested.pixel_विस्तारः = गवाक्षः->floating.w;
                wind->requested.pixel_height = गवाक्षः->floating.h;
                विस्तारः = wind->requested.logical_विस्तारः = Pixel_गन्तव्यम्_Point(गवाक्षः, गवाक्षः->floating.w);
                height = wind->requested.logical_height = Pixel_गन्तव्यम्_Point(गवाक्षः, गवाक्षः->floating.h);
            }

            OverrideLibdecorLimits(गवाक्षः);
        } अन्यथा {
            /* XXX: The libdecor cairo plugin sends bogus content sizes that add the
             *      height of the title bar when transitioning from a fixed-size to
             *      floating state. Ignore the sent window dimensions in this case,
             *      in favor of the cached value to avoid the window increasing in
             *      size after every state transition.
             *
             *      https://gitlab.freedesktop.org/libdecor/libdecor/-/issues/34
             */
            यदि ((floating && (!wind->floating && !(गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS))) ||
                !libdecor_configuration_get_content_आकार(configuration, frame, &विस्तारः, &height)) {
                विस्तारः = 0;
                height = 0;
            }

            ध्रुव bool new_configure_आकार = विस्तारः != wind->चरमः_configure.विस्तारः || height != wind->चरमः_configure.height;
            DetermineResizeAxis(wind, विस्तारः, height, resizing);

            यदि (!विस्तारः) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                यदि (floating) {
                    विस्तारः = गवाक्षः->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    यदि (wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE && wind->toplevel_bounds.विस्तारः) {
                        विस्तारः = SDL_min(wind->toplevel_bounds.विस्तारः, विस्तारः);
                    }
                } अन्यथा {
                    विस्तारः = गवाक्षः->windowed.w;
                }

                यदि (!wind->scale_गन्तव्यम्_display) {
                    wind->requested.logical_विस्तारः = विस्तारः;
                } अन्यथा {
                    wind->requested.pixel_विस्तारः = विस्तारः;
                    विस्तारः = wind->requested.logical_विस्तारः = Pixel_गन्तव्यम्_Point(गवाक्षः, विस्तारः);
                }
            } अन्यथा {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                यदि (new_configure_आकार &&
                    !(wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_FRAME && wind->suspended != suspended)) {
                    wind->requested.logical_विस्तारः = विस्तारः;

                    यदि (wind->scale_गन्तव्यम्_display) {
                        wind->requested.pixel_विस्तारः = Point_गन्तव्यम्_Pixel(गवाक्षः, विस्तारः);
                    }
                }
            }

            यदि (!height) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                यदि (floating) {
                    height = गवाक्षः->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    यदि (wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE && wind->toplevel_bounds.height) {
                        height = SDL_min(wind->toplevel_bounds.height, height);
                    }
                } अन्यथा {
                    height = गवाक्षः->windowed.h;
                }

                यदि (!wind->scale_गन्तव्यम्_display) {
                    wind->requested.logical_height = height;
                } अन्यथा {
                    wind->requested.pixel_height = height;
                    height = wind->requested.logical_height = Pixel_गन्तव्यम्_Point(गवाक्षः, height);
                }
            } अन्यथा {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                यदि (new_configure_आकार &&
                    !(wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_FRAME && wind->suspended != suspended)) {
                    wind->requested.logical_height = height;

                    यदि (wind->scale_गन्तव्यम्_display) {
                        wind->requested.pixel_height = Point_गन्तव्यम्_Pixel(गवाक्षः, height);
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
        यदि (floating) {
            यदि (!wind->scale_गन्तव्यम्_display) {
                ApplyGeometryLimits(गवाक्षः, wind->requested.logical_विस्तारः, wind->requested.logical_height, &wind->requested.logical_विस्तारः, &wind->requested.logical_height);
            } अन्यथा {
                ApplyGeometryLimits(गवाक्षः, wind->requested.pixel_विस्तारः, wind->requested.pixel_height, &wind->requested.pixel_विस्तारः, &wind->requested.pixel_height);

                wind->requested.logical_विस्तारः = Pixel_गन्तव्यम्_Point(गवाक्षः, wind->requested.pixel_विस्तारः);
                wind->requested.logical_height = Pixel_गन्तव्यम्_Point(गवाक्षः, wind->requested.pixel_height);
            }
        }
    }

    // Store the new state.
    ध्रुव bool started_resize = !wind->resizing && resizing;
    wind->चरमः_configure.विस्तारः = विस्तारः;
    wind->चरमः_configure.height = height;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->सक्रिय = सक्रिय;
    गवाक्षः->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#यदि SDL_LIBDECOR_CHECK_संस्करणम्(0, 3, 0)
    गणना libdecor_wm_capabilities caps;
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    यदि (libdecor_frame_get_wm_capabilities) {
        caps = libdecor_frame_get_wm_capabilities(wind->shell_surface.libdecor.frame);
#अन्यथा
    caps = libdecor_frame_get_wm_capabilities(wind->shell_surface.libdecor.frame);
    {
#यदि_अन्तः
        wind->wm_caps = 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_गवाक्षः_MENU ? WAYLAND_WM_CAPS_गवाक्षः_MENU : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MAXIMIZE ? WAYLAND_WM_CAPS_MAXIMIZE : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_FULLSCREEN ? WAYLAND_WM_CAPS_FULLSCREEN : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MINIMIZE ? WAYLAND_WM_CAPS_MINIMIZE : 0;
    }
#यदि_अन्तः

    यदि (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        Configure_गवाक्षः_Geometry(गवाक्षः);
        संरचना libdecor_state *state = libdecor_state_new(wind->current.logical_विस्तारः, wind->current.logical_height);
        libdecor_frame_commit(frame, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        यदि (started_resize) {
            SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_EXPOSED, 0, 0);
        }
    }

    यदि (wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE) {
        wind->shell_surface_स्थितिः = WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_FRAME;
    }
}

स्थिर शून्य decoration_frame_close(संरचना libdecor_frame *frame, शून्य *user_दत्त_2)
{
    SDL_Send_गवाक्षः_Event(((SDL_गवाक्षः_दत्त *)user_दत्त_2)->sdlwindow, SDL_EVENT_गवाक्षः_CLOSE_REQUESTED, 0, 0);
}

स्थिर शून्य decoration_frame_commit(संरचना libdecor_frame *frame, शून्य *user_दत्त_2)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_गवाक्षः_दत्त *wind = (SDL_गवाक्षः_दत्त *)user_दत्त_2;
    यदि (!wind->suspended && wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN) {
        SDL_Send_गवाक्षः_Event(wind->sdlwindow, SDL_EVENT_गवाक्षः_EXPOSED, 0, 0);
    }
}

स्थिर शून्य decoration_dismiss_popup(संरचना libdecor_frame *frame, ध्रुव वर्ण *seat_name, शून्य *user_दत्त_2)
{
    // NOP
}

#यदि SDL_LIBDECOR_CHECK_संस्करणम्(0, 3, 0)
स्थिर शून्य decoration_frame_bounds(संरचना libdecor_frame *frame, पूर्णाङ्क विस्तारः, पूर्णाङ्क height, शून्य *user_दत्त_2)
{
    SDL_गवाक्षः_दत्त *गवाक्षः = (SDL_गवाक्षः_दत्त *)user_दत्त_2;
    गवाक्षः->toplevel_bounds.विस्तारः = विस्तारः;
    गवाक्षः->toplevel_bounds.height = height;
}
#यदि_अन्तः

स्थिर संरचना libdecor_frame_interface libdecor_frame_interface = {
    decoration_frame_configure,
    decoration_frame_close,
    decoration_frame_commit,
    decoration_dismiss_popup,
#यदि SDL_LIBDECOR_CHECK_संस्करणम्(0, 3, 0)
    decoration_frame_bounds
#यदि_अन्तः
};
#यदि_अन्तः

स्थिर शून्य Wayland_Handle_Preferred_Scale_परिवर्तितम्(SDL_गवाक्षः_दत्त *गवाक्षः_दत्त_2, द्विगुण गुणकः)
{
    ध्रुव द्विगुण old_गुणकः = गवाक्षः_दत्त_2->scale_गुणकः_2;

    // Round the scale factor if viewports aren't available.
    यदि (!गवाक्षः_दत्त_2->viewport) {
        गुणकः = SDL_ceil(गुणकः);
    }

    यदि (गुणकः != old_गुणकः) {
        गवाक्षः_दत्त_2->scale_गुणकः_2 = गुणकः;

        यदि (गवाक्षः_दत्त_2->scale_गन्तव्यम्_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            यदि (गवाक्षः_दत्त_2->floating) {
                /* Some compositors will send a configure event immediately after a scale event, however,
                 * this event can contain the old logical size, and should be ignored, or the window can
                 * incorrectly change size when moved between displays with differing scale factors.
                 *
                 * Store the last requested logical size as the last configure size, so a configure event
                 * with the old size will be ignored. Configure sizes are in window geometry space,
                 * so subtract any border insets.
                 */
                BorderInsets insets;
                GetBorderInsets(गवाक्षः_दत्त_2->sdlwindow, &insets);
                गवाक्षः_दत्त_2->चरमः_configure.विस्तारः = SDL_max(गवाक्षः_दत्त_2->requested.logical_विस्तारः - (insets.वामः + insets.दक्षिणः), 1);
                गवाक्षः_दत्त_2->चरमः_configure.height = SDL_max(गवाक्षः_दत्त_2->requested.logical_height - (insets.शिखरम् + insets.bottom), 1);

                गवाक्षः_दत्त_2->requested.logical_विस्तारः = Pixel_गन्तव्यम्_Point(गवाक्षः_दत्त_2->sdlwindow, गवाक्षः_दत्त_2->requested.pixel_विस्तारः);
                गवाक्षः_दत्त_2->requested.logical_height = Pixel_गन्तव्यम्_Point(गवाक्षः_दत्त_2->sdlwindow, गवाक्षः_दत्त_2->requested.pixel_height);
            } अन्यथा {
                गवाक्षः_दत्त_2->requested.pixel_विस्तारः = Point_गन्तव्यम्_Pixel(गवाक्षः_दत्त_2->sdlwindow, गवाक्षः_दत्त_2->requested.logical_विस्तारः);
                गवाक्षः_दत्त_2->requested.pixel_height = Point_गन्तव्यम्_Pixel(गवाक्षः_दत्त_2->sdlwindow, गवाक्षः_दत्त_2->requested.logical_height);
            }
        }

        यदि (गवाक्षः_दत्त_2->sdlwindow->flags & SDL_गवाक्षः_उच्चः_PIXEL_DENSITY || गवाक्षः_दत्त_2->scale_गन्तव्यम्_display) {
            Configure_गवाक्षः_Geometry(गवाक्षः_दत्त_2->sdlwindow);
            CommitLibdecorFrame(गवाक्षः_दत्त_2->sdlwindow);
        }
    }
}

स्थिर शून्य Wayland_Maybe_Update_Scale_गुणकः(SDL_गवाक्षः_दत्त *गवाक्षः)
{
    द्विगुण गुणकः;
    पूर्णाङ्क i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    यदि (गवाक्षः->fractional_scale || wl_surface_get_संस्करणम्(गवाक्षः->surface) >= WL_SURFACE_PREFERRED_बफर_SCALE_SINCE_संस्करणम्) {
        प्रत्यागम;
    }

    यदि (गवाक्षः->अङ्कः_outputs != 0) {
        // Check every display's factor, use the highest
        गुणकः = 0.0;
        प्रति (i = 0; i < गवाक्षः->अङ्कः_outputs; i++) {
            SDL_Display_दत्त *आन्तरिकम् = गवाक्षः->outputs[i];
            गुणकः = SDL_max(गुणकः, आन्तरिकम्->scale_गुणकः_2);
        }
    } अन्यथा {
        // All outputs removed, just fall back.
        गुणकः = गवाक्षः->scale_गुणकः_2;
    }

    Wayland_Handle_Preferred_Scale_परिवर्तितम्(गवाक्षः, गुणकः);
}

शून्य Wayland_Remove_Output_From_गवाक्षः(SDL_गवाक्षः_दत्त *गवाक्षः, SDL_Display_दत्त *display_दत्त)
{
    प्रति (पूर्णाङ्क i = 0; i < गवाक्षः->अङ्कः_outputs; i++) {
        यदि (गवाक्षः->outputs[i] == display_दत्त) { // remove this one
            यदि (i == (गवाक्षः->अङ्कः_outputs - 1)) {
                गवाक्षः->outputs[i] = रिक्त;
            } अन्यथा {
                SDL_memmove(&गवाक्षः->outputs[i],
                            &गवाक्षः->outputs[i + 1],
                            परिमाण(SDL_Display_दत्त *) * ((गवाक्षः->अङ्कः_outputs - i) - 1));
            }
            गवाक्षः->अङ्कः_outputs--;
            i--;
        }
    }

    यदि (गवाक्षः->अङ्कः_outputs == 0) {
        SDL_free(गवाक्षः->outputs);
        गवाक्षः->outputs = रिक्त;
    } अन्यथा यदि (!गवाक्षः->is_fullscreen || गवाक्षः->अङ्कः_outputs == 1) {
        Wayland_Update_गवाक्षः_Position(गवाक्षः->sdlwindow);
        Wayland_Maybe_Update_Scale_गुणकः(गवाक्षः);
    }
}

स्थिर शून्य handle_surface_enter(शून्य *दत्त, संरचना wl_surface *surface, संरचना wl_output *output)
{
    SDL_गवाक्षः_दत्त *गवाक्षः = दत्त;
    SDL_Display_दत्त *आन्तरिकम् = wl_output_get_user_दत्त(output);
    SDL_Display_दत्त **new_outputs;

    यदि (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        प्रत्यागम;
    }

    new_outputs = SDL_realloc(गवाक्षः->outputs,
                              परिमाण(SDL_Display_दत्त *) * (गवाक्षः->अङ्कः_outputs + 1));
    यदि (!new_outputs) {
        प्रत्यागम;
    }
    गवाक्षः->outputs = new_outputs;
    गवाक्षः->outputs[गवाक्षः->अङ्कः_outputs++] = आन्तरिकम्;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    यदि (!गवाक्षः->is_fullscreen || गवाक्षः->अङ्कः_outputs == 1) {
        Wayland_Update_गवाक्षः_Position(गवाक्षः->sdlwindow);
        Wayland_Maybe_Update_Scale_गुणकः(गवाक्षः);
    }
}

स्थिर शून्य handle_surface_leave(शून्य *दत्त, संरचना wl_surface *surface, संरचना wl_output *output)
{
    SDL_गवाक्षः_दत्त *गवाक्षः = (SDL_गवाक्षः_दत्त *)दत्त;

    यदि (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        प्रत्यागम;
    }

    Wayland_Remove_Output_From_गवाक्षः(गवाक्षः, (SDL_Display_दत्त *)wl_output_get_user_दत्त(output));
}

स्थिर शून्य handle_surface_preferred_बफर_scale(शून्य *दत्त, संरचना wl_surface *wl_surface, int32_t गुणकः)
{
    SDL_गवाक्षः_दत्त *wind = दत्त;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    यदि (!wind->fractional_scale) {
        Wayland_Handle_Preferred_Scale_परिवर्तितम्(दत्त, (द्विगुण)गुणकः);
    }
}

स्थिर शून्य handle_surface_preferred_बफर_transform(शून्य *दत्त, संरचना wl_surface *wl_surface, uint32_t transform)
{
    // Nothing to do here.
}

स्थिर ध्रुव संरचना wl_surface_listener surface_listener = {
    handle_surface_enter,
    handle_surface_leave,
    handle_surface_preferred_बफर_scale,
    handle_surface_preferred_बफर_transform
};

स्थिर शून्य handle_fractional_scale_preferred(शून्य *दत्त, संरचना wp_fractional_scale_v1 *wp_fractional_scale_v1, uint32_t scale)
{
    ध्रुव द्विगुण गुणकः = (द्विगुण)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_Handle_Preferred_Scale_परिवर्तितम्(दत्त, गुणकः);
}

स्थिर ध्रुव संरचना wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

स्थिर शून्य frog_preferred_metadata_handler(शून्य *दत्त, संरचना frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
                                            uint32_t output_display_primary_red_x, uint32_t output_display_primary_red_y,
                                            uint32_t output_display_primary_green_x, uint32_t output_display_primary_green_y,
                                            uint32_t output_display_primary_blue_x, uint32_t output_display_primary_blue_y,
                                            uint32_t output_white_point_x, uint32_t output_white_point_y,
                                            uint32_t max_luminance, uint32_t min_luminance,
                                            uint32_t max_पूर्णम्_frame_luminance)
{
    SDL_गवाक्षः_दत्त *wind = (SDL_गवाक्षः_दत्त *)दत्त;
    SDL_HDROutputProperties HDR;

    SDL_zero(HDR);

    विकल्प (transfer_function) {
    पक्ष FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_ST2084_PQ:
        /* ITU-R BT.2408-7 (Sept 2023) has the reference PQ white level at 203 nits,
         * while older Dolby documentation claims a reference level of 100 nits.
         *
         * Use 203 nits for now.
         */
        HDR.HDR_headroom = max_luminance / 203.0f;
        भङ्ग;
    पक्ष FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SCRGB_रैखिकम्:
        HDR.HDR_headroom = max_luminance / 80.0f;
        भङ्ग;
    पक्ष FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_UNDEFINED:
    पक्ष FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SRGB:
    पक्ष FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_GAMMA_22:
    स्वभाव:
        HDR.HDR_headroom = 1.0f;
        भङ्ग;
    }

    HDR.SDR_white_level = 1.0f;
    SDL_समुच्चयः_गवाक्षः_HDRProperties(wind->sdlwindow, &HDR, true);
}

स्थिर ध्रुव संरचना frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


स्थिर शून्य handle_surface_feedback_preferred_changed2(शून्य *दत्त,
                                                       संरचना wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t तटस्थः_hi, uint32_t तटस्थः_lo)
{
    SDL_गवाक्षः_दत्त *wind = (SDL_गवाक्षः_दत्त *)दत्त;
    Wayland_Get_Color_Info_For_गवाक्षः(wind, false);
}

स्थिर शून्य handle_surface_feedback_preferred_परिवर्तितम्(शून्य *दत्त,
                                                      संरचना wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t तटस्थः)
{
    handle_surface_feedback_preferred_changed2(दत्त, wp_color_management_surface_feedback_v1, 0, तटस्थः);
}

स्थिर ध्रुव संरचना wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_परिवर्तितम्,
    handle_surface_feedback_preferred_changed2
};

स्थिर शून्य Wayland_समुच्चयः_Keyboard_Focus(SDL_गवाक्षः *गवाक्षः, bool समुच्चयः_focus)
{
    SDL_गवाक्षः *toplevel = गवाक्षः;

    // Find the toplevel parent
    यावत् (SDL_गवाक्षः_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = गवाक्षः;

    यदि (समुच्चयः_focus && !गवाक्षः->is_hiding && !गवाक्षः->is_destroying) {
        SDL_समुच्चयः_Keyboard_Focus(गवाक्षः);
    }
}

bool Wayland_समुच्चयः_गवाक्षः_लब्धम्_Test(SDL_गवाक्षः *गवाक्षः, bool enabled)
{
    प्रत्यागम true; // just succeed, the real work is done elsewhere.
}

स्थिर संरचना xdg_toplevel *Get_Toplevel_For_गवाक्षः(SDL_गवाक्षः_दत्त *wind)
{
    यदि (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#यदि_परिभाषितम् HAVE_LIBDECOR_H
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
            प्रत्यागम libdecor_frame_get_xdg_toplevel(wind->shell_surface.libdecor.frame);
        } अन्यथा
#यदि_अन्तः
            यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                प्रत्यागम wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    प्रत्यागम रिक्त;
}

bool Wayland_समुच्चयः_गवाक्षः_Parent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः *parent_गवाक्षः)
{
    SDL_गवाक्षः_दत्त *child_दत्त = गवाक्षः->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *parent_दत्त = parent_गवाक्षः ? parent_गवाक्षः->आन्तरिकम् : रिक्त;

    child_दत्त->reparenting_required = false;

    यदि (parent_दत्त && parent_दत्त->shell_surface_स्थितिः != WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        child_दत्त->reparenting_required = true;
        प्रत्यागम true;
    }

    संरचना xdg_toplevel *child_toplevel = Get_Toplevel_For_गवाक्षः(child_दत्त);
    संरचना xdg_toplevel *parent_toplevel = Get_Toplevel_For_गवाक्षः(parent_दत्त);

    यदि (child_toplevel) {
        xdg_toplevel_समुच्चयः_parent(child_toplevel, parent_toplevel);
    }

    प्रत्यागम true;
}

bool Wayland_समुच्चयः_गवाक्षः_Modal(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool modal)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *parent_दत्त = गवाक्षः->parent->आन्तरिकम्;

    यदि (parent_दत्त->shell_surface_स्थितिः != WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        दत्त->reparenting_required = true;
        प्रत्यागम true;
    } अन्यथा {
        दत्त->reparenting_required = false;
    }

    संरचना xdg_toplevel *toplevel = Get_Toplevel_For_गवाक्षः(दत्त);

    यदि (toplevel) {
        यदि (viddata->xdg_wm_dialog_v1) {
            यदि (modal) {
                यदि (!दत्त->xdg_dialog_v1) {
                    दत्त->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_समुच्चयः_modal(दत्त->xdg_dialog_v1);
            } अन्यथा यदि (दत्त->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(दत्त->xdg_dialog_v1);
            }
        }
    }

    प्रत्यागम true;
}

स्थिर शून्य Wayland_पञ्जिकाकोशः_Toplevel_For_Session(SDL_गवाक्षः_दत्त *दत्त)
{
    संरचना xdg_toplevel *toplevel = Get_Toplevel_For_गवाक्षः(दत्त);
    यदि (!toplevel) {
        प्रत्यागम;
    }

    ध्रुव वर्ण *id = SDL_GetStringProperty(दत्त->sdlwindow->props, SDL_PROP_गवाक्षः_WAYLAND_गवाक्षः_ID_STRING, रिक्त);
    यदि (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_Video_दत्त *viddata = viddev->आन्तरिकम्;

        यदि (viddata->xdg_toplevel_चिह्नकम्_manager) {
            xdg_toplevel_चिह्नकम्_manager_v1_समुच्चयः_toplevel_चिह्नकम्(viddata->xdg_toplevel_चिह्नकम्_manager, toplevel, id);
        }

        यदि (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            यदि (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    प्रति (SDL_गवाक्षः *w = viddev->windows; w; w = w->अग्र) {
                        SDL_गवाक्षः_दत्त *d = w->आन्तरिकम्;
                        यदि (d->session_id && SDL_strcmp(d->session_id, id) == 0) {
                            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Duplicate window ID string %s found; window will not be added to session", id);
                            प्रत्यागम;
                        }
                    }
                }

                दत्त->xdg_toplevel_session = xdg_session_v1_restore_toplevel(viddata->xdg_session, toplevel, id);
                दत्त->session_id = SDL_strdup(id);
            }
        }
    }
}

स्थिर शून्य Wayland_DestroyToplevelSession(SDL_गवाक्षः_दत्त *दत्त)
{
    SDL_Video_दत्त *viddata = दत्त->wayland_दत्त;

    यदि (दत्त->xdg_toplevel_session) {
        ध्रुव वर्ण *id = SDL_GetStringProperty(दत्त->sdlwindow->props, SDL_PROP_गवाक्षः_WAYLAND_गवाक्षः_ID_STRING, रिक्त);

        // If the ID string was cleared, remove the window from the session.
        यदि (!id || *id == '\0') {
            xdg_session_v1_remove_toplevel(viddata->xdg_session, दत्त->session_id);
        }

        xdg_toplevel_session_v1_destroy(दत्त->xdg_toplevel_session);
        दत्त->xdg_toplevel_session = रिक्त;

        SDL_free(दत्त->session_id);
        दत्त->session_id = रिक्त;
    }
}

स्थिर शून्य show_hide_sync_handler(शून्य *दत्त, संरचना wl_callback *callback, uint32_t callback_दत्त)
{
    // Get the window from the ID as it may have been destroyed
    SDL_गवाक्षः_ID गवाक्षः_ID = (SDL_गवाक्षः_ID)((uintptr_t)दत्त);
    SDL_गवाक्षः *गवाक्षः = SDL_Get_गवाक्षः_From_ID(गवाक्षः_ID);

    यदि (गवाक्षः && गवाक्षः->आन्तरिकम्) {
        SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

स्थिर संरचना wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

स्थिर शून्य exported_handle_handler(शून्य *दत्त, संरचना zxdg_exported_v2 *zxdg_exported_v2, ध्रुव वर्ण *handle)
{
    SDL_गवाक्षः_दत्त *wind = (SDL_गवाक्षः_दत्त *)दत्त;
    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(wind->sdlwindow);

    SDL_समुच्चयः_String_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

स्थिर संरचना zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

शून्य Wayland_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *c = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(गवाक्षः);

    // Custom surfaces don't get toplevels and are always considered 'shown'; nothing to do here.
    यदि (दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        प्रत्यागम;
    }

    /* If this is a child window, the parent *must* be in the final shown state,
     * meaning that it has received a configure event, followed by a frame callback.
     * If not, a race condition can result, with effects ranging from the child
     * window to spuriously closing to protocol errors.
     *
     * If waiting on the parent window, set the pending status and the window will
     * be shown when the parent is in the shown state.
     */
    यदि (गवाक्षः->parent) {
        यदि (गवाक्षः->parent->आन्तरिकम्->shell_surface_स्थितिः != WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN) {
            दत्त->shell_surface_स्थितिः = WAYLAND_SHELL_SURFACE_स्थितिः_SHOW_PENDING;
            प्रत्यागम;
        }
    }

    // Always roundtrip to ensure there are no pending buffer attachments.
    कुरु {
        WAYLAND_wl_display_roundtrip(c->display);
    } यावत् (दत्त->show_hide_sync_required);

    दत्त->shell_surface_स्थितिः = WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE;

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
    wl_surface_attach(दत्त->surface, रिक्त, 0, 0);
    wl_surface_commit(दत्त->surface);

    // Create the shell surface and map the toplevel/popup
#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        दत्त->shell_surface.libdecor.frame = libdecor_decorate(c->shell.libdecor,
                                                               दत्त->surface,
                                                               &libdecor_frame_interface,
                                                               दत्त);
        यदि (!दत्त->shell_surface.libdecor.frame) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } अन्यथा {
            libdecor_frame_समुच्चयः_app_id(दत्त->shell_surface.libdecor.frame, दत्त->app_id);
            libdecor_frame_map(दत्त->shell_surface.libdecor.frame);
            यदि (गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_frame_समुच्चयः_visibility(दत्त->shell_surface.libdecor.frame, false);
            }

            यदि (c->zxdg_exporter_v2) {
                दत्त->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, दत्त->surface);
                zxdg_exported_v2_सङ्कलय_listener(दत्त->exported, &exported_v2_listener, दत्त);
            }

            यदि (c->xdg_toplevel_icon_manager_v1 && दत्त->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_समुच्चयः_icon(_this->आन्तरिकम्->xdg_toplevel_icon_manager_v1,
                                                      libdecor_frame_get_xdg_toplevel(दत्त->shell_surface.libdecor.frame),
                                                      दत्त->xdg_toplevel_icon_v1);
            }

            SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_SURFACE_POINTER, libdecor_frame_get_xdg_surface(दत्त->shell_surface.libdecor.frame));
            SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_TOPLEVEL_POINTER, libdecor_frame_get_xdg_toplevel(दत्त->shell_surface.libdecor.frame));
        }
    } अन्यथा
#यदि_अन्तः
    यदि (दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        दत्त->shell_surface.xdg.surface = xdg_wm_आधारः_get_xdg_surface(c->shell.xdg, दत्त->surface);
        xdg_surface_समुच्चयः_user_दत्त(दत्त->shell_surface.xdg.surface, दत्त);
        xdg_surface_सङ्कलय_listener(दत्त->shell_surface.xdg.surface, &_xdg_surface_listener, दत्त);
        SDL_समुच्चयः_Pointer_Property(SDL_Get_गवाक्षः_Properties(गवाक्षः), SDL_PROP_गवाक्षः_WAYLAND_XDG_SURFACE_POINTER, दत्त->shell_surface.xdg.surface);

        यदि (दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_गवाक्षः *parent = गवाक्षः->parent;
            SDL_गवाक्षः_दत्त *parent_दत्त = parent->आन्तरिकम्;
            संरचना xdg_surface *parent_xdg_surface = रिक्त;
            पूर्णाङ्क position_x = 0, position_y = 0;

            // Configure the popup parameters
#यदि_परिभाषितम् HAVE_LIBDECOR_H
            यदि (parent_दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                parent_xdg_surface = libdecor_frame_get_xdg_surface(parent_दत्त->shell_surface.libdecor.frame);
            } अन्यथा
#यदि_अन्तः
            यदि (parent_दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    parent_दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                parent_xdg_surface = parent_दत्त->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            दत्त->shell_surface.xdg.popup.xdg_positioner = xdg_wm_आधारः_create_positioner(c->shell.xdg);
            xdg_positioner_समुच्चयः_anchor(दत्त->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_शिखरम्_वामः);
            SDL_Rect parent_geometry;
            Get_गवाक्षः_Geometry(parent->आन्तरिकम्, &parent_geometry);
            xdg_positioner_समुच्चयः_anchor_rect(दत्त->shell_surface.xdg.popup.xdg_positioner, 0, 0, parent_geometry.w, parent_geometry.h);

            ध्रुव Uint32 constraint = गवाक्षः->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_समुच्चयः_constraint_adjustment(दत्त->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_समुच्चयः_gravity(दत्त->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_दक्षिणः);
            xdg_positioner_समुच्चयः_आकार(दत्त->shell_surface.xdg.popup.xdg_positioner, दत्त->current.logical_विस्तारः, दत्त->current.logical_height);

            // Set the popup initial position
            position_x = गवाक्षः->चरमः_position_pending ? गवाक्षः->pending.x : गवाक्षः->x;
            position_y = गवाक्षः->चरमः_position_pending ? गवाक्षः->pending.y : गवाक्षः->y;
            EnsurePopupPositionIsValid(गवाक्षः, &position_x, &position_y);
            यदि (दत्त->scale_गन्तव्यम्_display) {
                position_x = Pixel_गन्तव्यम्_Point(गवाक्षः->parent, position_x);
                position_y = Pixel_गन्तव्यम्_Point(गवाक्षः->parent, position_y);
            }
            Adjust_Popup_विस्थापनम्(गवाक्षः, &position_x, &position_y);
            xdg_positioner_समुच्चयः_विस्थापनम्(दत्त->shell_surface.xdg.popup.xdg_positioner, position_x, position_y);

            // Assign the popup role
            दत्त->shell_surface.xdg.popup.xdg_popup = xdg_surface_get_popup(दत्त->shell_surface.xdg.surface,
                                                                                parent_xdg_surface,
                                                                                दत्त->shell_surface.xdg.popup.xdg_positioner);
            xdg_popup_सङ्कलय_listener(दत्त->shell_surface.xdg.popup.xdg_popup, &_xdg_popup_listener, दत्त);

            यदि (गवाक्षः->flags & SDL_गवाक्षः_TOOLTIP) {
                संरचना wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_सङ्कलय(region, 0, 0, 0, 0);
                wl_surface_समुच्चयः_निवेशः_region(दत्त->surface, region);
                wl_region_destroy(region);
            } अन्यथा यदि ((गवाक्षः->flags & SDL_गवाक्षः_POPUP_MENU) && !(गवाक्षः->flags & SDL_गवाक्षः_NOT_FOCUSABLE)) {
                Wayland_समुच्चयः_Keyboard_Focus(गवाक्षः, true);
            }

            SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_POPUP_POINTER, दत्त->shell_surface.xdg.popup.xdg_popup);
            SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_POSITIONER_POINTER, दत्त->shell_surface.xdg.popup.xdg_positioner);
        } अन्यथा {
            दत्त->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(दत्त->shell_surface.xdg.surface);
            xdg_toplevel_समुच्चयः_app_id(दत्त->shell_surface.xdg.toplevel.xdg_toplevel, दत्त->app_id);
            xdg_toplevel_सङ्कलय_listener(दत्त->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, दत्त);

            // Create the window decorations
            यदि (c->decoration_manager) {
                दत्त->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, दत्त->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_सङ्कलय_listener(दत्त->server_decoration, &xdg_toplevel_decoration_listener, गवाक्षः);
                ध्रुव गणना zxdg_toplevel_decoration_v1_बहुलकम् बहुलकम् = !(गवाक्षः->flags & SDL_गवाक्षः_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_बहुलकम्_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_बहुलकम्_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_समुच्चयः_बहुलकम्(दत्त->server_decoration, बहुलकम्);
            }

            यदि (c->zxdg_exporter_v2) {
                दत्त->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, दत्त->surface);
                zxdg_exported_v2_सङ्कलय_listener(दत्त->exported, &exported_v2_listener, दत्त);
            }

            यदि (c->xdg_toplevel_icon_manager_v1 && दत्त->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_समुच्चयः_icon(_this->आन्तरिकम्->xdg_toplevel_icon_manager_v1,
                                                      दत्त->shell_surface.xdg.toplevel.xdg_toplevel,
                                                      दत्त->xdg_toplevel_icon_v1);
            }

            SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_TOPLEVEL_POINTER, दत्त->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    // Restore state that was set prior to this call
    Wayland_पञ्जिकाकोशः_Toplevel_For_Session(दत्त);
    Wayland_समुच्चयः_गवाक्षः_Parent(_this, गवाक्षः, गवाक्षः->parent);

    यदि (गवाक्षः->flags & SDL_गवाक्षः_MODAL) {
        Wayland_समुच्चयः_गवाक्षः_Modal(_this, गवाक्षः, true);
    }

    Wayland_समुच्चयः_गवाक्षः_Title(_this, गवाक्षः);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (दत्त->shell_surface.libdecor.frame) {
            यावत् (दत्त->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE) {
                यदि (libdecor_dispatch(c->shell.libdecor, -1) < 0) {
                    यदि (!Wayland_HandleDisplayDisconnected(_this)) {
                        प्रत्यागम;
                    }
                }
                यदि (WAYLAND_wl_display_dispatch_pending(c->display) < 0) {
                    यदि (!Wayland_HandleDisplayDisconnected(_this)) {
                        प्रत्यागम;
                    }
                }
            }
        }
    } अन्यथा
#यदि_अन्तः
        यदि (दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP || दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Unlike libdecor we need to call this explicitly to prevent a deadlock.
         * libdecor will call this as part of their configure event!
         * -flibit
         */
        wl_surface_commit(दत्त->surface);
        यदि (दत्त->shell_surface.xdg.surface) {
            यावत् (दत्त->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE) {
                यदि (WAYLAND_wl_display_dispatch(c->display) < 0) {
                    यदि (!Wayland_HandleDisplayDisconnected(_this)) {
                        प्रत्यागम;
                    }
                }
            }
        }
    } अन्यथा {
        // Nothing to see here, just commit.
        wl_surface_commit(दत्त->surface);
    }

    // Make sure the window can't be resized to 0, or it can be spuriously closed by the window manager.
    दत्त->system_limits.min_विस्तारः_2 = SDL_max(दत्त->system_limits.min_विस्तारः_2, 1);
    दत्त->system_limits.min_height = SDL_max(दत्त->system_limits.min_height, 1);

    /* Unlike the rest of window state we have to set this _after_ flushing the
     * display, because we need to create the decorations before possibly hiding
     * them immediately afterward.
     */
#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        यदि (गवाक्षः->windowed.w < दत्त->system_limits.min_विस्तारः_2 ||
            गवाक्षः->windowed.h < दत्त->system_limits.min_height) {

            // Warn if the window frame will be larger than the content surface.
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "Window dimensions (%i, %i) are smaller than the system enforced minimum (%i, %i); window borders will be larger than the content surface.",
                        गवाक्षः->windowed.w, गवाक्षः->windowed.h, दत्त->system_limits.min_विस्तारः_2, दत्त->system_limits.min_height);

            दत्त->current.logical_विस्तारः = SDL_max(गवाक्षः->windowed.w, दत्त->system_limits.min_विस्तारः_2);
            दत्त->current.logical_height = SDL_max(गवाक्षः->windowed.h, दत्त->system_limits.min_height);
            CommitLibdecorFrame(गवाक्षः);
        }
    }
#यदि_अन्तः
    Wayland_समुच्चयः_गवाक्षः_Resizable(_this, गवाक्षः, !!(गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE));

    // We're finally done putting the window together, raise if possible
    यदि (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_गवाक्षः_ACTIVATE_WHEN_SHOWN, true)) {
        /* if the process was passed an activation token, use it when showing
         * the initial window.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ध्रुव वर्ण *activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
        यदि (activation_token) {
            xdg_activation_v1_activate(c->activation_manager,
                                       activation_token,
                                       दत्त->surface);

            // Clear this variable, per the protocol's request
            SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
        } अन्यथा {
            // Try to generate an activation token for this window.
            Wayland_Raise_गवाक्षः(_this, गवाक्षः);
        }
    } अन्यथा {
        // Clear the ignored activation token, as it won't be used.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    }

    // No frame callback on an external surface, as it may already have one attached.
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        दत्त->surface_frame_callback = wl_surface_frame(दत्त->surface);
        wl_callback_सङ्कलय_listener(दत्त->surface_frame_callback, &surface_frame_listener, दत्त);
    }

    दत्त->show_hide_sync_required = true;
    संरचना wl_callback *cb = wl_display_sync(_this->आन्तरिकम्->display);
    wl_callback_सङ्कलय_listener(cb, &show_hide_sync_listener, (शून्य *)((uintptr_t)गवाक्षः->id));

    दत्त->showing_गवाक्षः = true;
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_SHOWN, 0, 0);
    दत्त->showing_गवाक्षः = false;

    // Send an exposure event to signal that the client should draw.
    SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_EXPOSED, 0, 0);
}

स्थिर शून्य Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_गवाक्षः *popup)
{
    SDL_गवाक्षः_दत्त *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    यदि (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_गवाक्षः)) {
        प्रत्यागम;
    }
    popupdata = popup->आन्तरिकम्;
    यदि (!popupdata) {
        प्रत्यागम;
    }

    // This may already be freed by a parent popup!
    यदि (popupdata->shell_surface.xdg.popup.xdg_popup == रिक्त) {
        प्रत्यागम;
    }

    यदि ((popup->flags & SDL_गवाक्षः_POPUP_MENU) && !(popup->flags & SDL_गवाक्षः_NOT_FOCUSABLE)) {
        SDL_गवाक्षः *new_focus;
        ध्रुव bool समुच्चयः_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_समुच्चयः_Keyboard_Focus(new_focus, समुच्चयः_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = रिक्त;
    popupdata->shell_surface.xdg.popup.xdg_positioner = रिक्त;

    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(popup);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_POPUP_POINTER, रिक्त);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_POSITIONER_POINTER, रिक्त);
}

शून्य Wayland_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;
    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(गवाक्षः);

    // Custom surfaces have nothing to destroy and are always considered to be 'shown'; nothing to do here.
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        प्रत्यागम;
    }

    /* The window was shown, but the sync point hasn't yet been reached.
     * Pump events to avoid a possible protocol violation.
     */
    यदि (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(दत्त->display);
    }

    wind->shell_surface_स्थितिः = WAYLAND_SHELL_SURFACE_स्थितिः_HIDDEN;

    यदि (wind->surface_frame_callback) {
        wl_callback_destroy(wind->surface_frame_callback);
        wind->surface_frame_callback = रिक्त;
    }

    यदि (wind->server_decoration) {
        zxdg_toplevel_decoration_v1_destroy(wind->server_decoration);
        wind->server_decoration = रिक्त;
    }

    // Clean up the export handle.
    यदि (wind->exported) {
        zxdg_exported_v2_destroy(wind->exported);
        wind->exported = रिक्त;

        SDL_समुच्चयः_String_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, रिक्त);
    }

    यदि (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = रिक्त;
    }

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (wind->shell_surface.libdecor.frame) {
            libdecor_frame_unref(wind->shell_surface.libdecor.frame);

            SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_SURFACE_POINTER, रिक्त);
            SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_TOPLEVEL_POINTER, रिक्त);
        }
    } अन्यथा
#यदि_अन्तः
    {
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, गवाक्षः);
        } अन्यथा यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_TOPLEVEL_POINTER, रिक्त);
        }

        यदि (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_XDG_SURFACE_POINTER, रिक्त);
        }
    }

    // Attach a null buffer to unmap the surface.
    यदि (wind->आवरणम्.surface) {
        wl_surface_attach(wind->आवरणम्.surface, रिक्त, 0, 0);
        wl_surface_commit(wind->आवरणम्.surface);
    }
    wl_surface_attach(wind->surface, रिक्त, 0, 0);
    wl_surface_commit(wind->surface);

    // Need to destroy the session object after unmapping the window, or the state may not be saved.
    Wayland_DestroyToplevelSession(wind);

    SDL_zero(wind->shell_surface);
    SDL_zero(wind->explicit_geometry);
    wind->show_hide_sync_required = true;
    संरचना wl_callback *cb = wl_display_sync(_this->आन्तरिकम्->display);
    wl_callback_सङ्कलय_listener(cb, &show_hide_sync_listener, (शून्य *)((uintptr_t)गवाक्षः->id));
}

स्थिर शून्य handle_xdg_activation_समाप्तम्(शून्य *दत्त,
                                       संरचना xdg_activation_token_v1 *xdg_activation_token_v1,
                                       ध्रुव वर्ण *token)
{
    SDL_गवाक्षः_दत्त *गवाक्षः = दत्त;
    यदि (xdg_activation_token_v1 == गवाक्षः->activation_token) {
        xdg_activation_v1_activate(गवाक्षः->wayland_दत्त->activation_manager,
                                   token,
                                   गवाक्षः->surface);
        xdg_activation_token_v1_destroy(गवाक्षः->activation_token);
        गवाक्षः->activation_token = रिक्त;
    }
}

स्थिर ध्रुव संरचना xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_समाप्तम्
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
स्थिर शून्य Wayland_activate_गवाक्षः(SDL_Video_दत्त *दत्त, SDL_गवाक्षः_दत्त *target_wind, bool समुच्चयः_serial)
{
    SDL_WaylandSeat *seat = दत्त->चरमः_implicit_grab_seat;
    SDL_गवाक्षः_दत्त *focus = रिक्त;

    यदि (seat) {
        focus = seat->keyboard.focus;
        यदि (!focus) {
            focus = seat->pointer.focus;
        }
    }

    संरचना wl_surface *requesting_surface = focus ? focus->surface : रिक्त;

    यदि (दत्त->activation_manager) {
        यदि (target_wind->activation_token) {
            // We're about to overwrite this with a new request
            xdg_activation_token_v1_destroy(target_wind->activation_token);
        }

        target_wind->activation_token = xdg_activation_v1_get_activation_token(दत्त->activation_manager);
        xdg_activation_token_v1_सङ्कलय_listener(target_wind->activation_token,
                                             &xdg_activation_listener,
                                             target_wind);

        /* Note that we are not setting the app_id here.
         *
         * Hypothetically we could set the app_id from data->classname, but
         * that part of the API is for _external_ programs, not ourselves.
         *
         * -flibit
         */
        यदि (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_समुच्चयः_surface(target_wind->activation_token, requesting_surface);
        }
        यदि (समुच्चयः_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_समुच्चयः_serial(target_wind->activation_token, seat->चरमः_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(target_wind->activation_token);
    }
}

शून्य Wayland_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    यदि (viddata->activation_manager) {
        /* Check for an activation token, in case the window is being
         * raised in response to a system notification.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ध्रुव वर्ण *activation_token = SDL_GetNotificationActivationToken();
        यदि (activation_token) {
            xdg_activation_v1_activate(viddata->activation_manager,
                                       activation_token,
                                       wind->surface);
            प्रत्यागम;
        }
    }

    // No token? Try to activate the window via an event serial.
    Wayland_activate_गवाक्षः(_this->आन्तरिकम्, गवाक्षः->आन्तरिकम्, true);
}

bool Wayland_Flash_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_FlashOperation operation)
{
    /* Not setting the serial will specify 'urgency' without switching focus as per
     * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
     */
    Wayland_activate_गवाक्षः(_this->आन्तरिकम्, गवाक्षः->आन्तरिकम्, false);
    प्रत्यागम true;
}

SDL_Fullscreen_परिणाम Wayland_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;
    संरचना wl_output *output = display->आन्तरिकम्->output;

    // Custom surfaces have no toplevel to make fullscreen.
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        प्रत्यागम SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    यदि (wind->showing_गवाक्षः && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
    }

    यदि (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->आन्तरिकम्->display);
    }

    // Flushing old events pending a new one, ignore this request.
    यदि (wind->drop_fullscreen_अनुरोधाः) {
        प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_अनुरोधाः = true;
    FlushPendingEvents(गवाक्षः);
    wind->drop_fullscreen_अनुरोधाः = false;

    // Nothing to do if the window is not fullscreen, and this isn't an explicit enter request.
    यदि (!wind->is_fullscreen) {
        यदि (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
            // Request was out of date; signal the video core not to update any state.
            प्रत्यागम SDL_FULLSCREEN_PENDING;
        } अन्यथा यदि (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
            // Already not fullscreen; nothing to do.
            प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    // Don't send redundant fullscreen set/unset events.
    यदि (!!fullscreen != wind->is_fullscreen) {
        wind->fullscreen_was_positioned = !!fullscreen;

        /* Only use the specified output if an exclusive mode is being used, or a position was explicitly requested
         * before entering fullscreen desktop. Otherwise, let the compositor handle placement, as it has more
         * information about where the window is and where it should go, particularly if fullscreen is being requested
         * before the window is mapped, or the window spans multiple outputs.
         */
        यदि (!गवाक्षः->fullscreen_exclusive) {
            यदि (गवाक्षः->undefined_x || गवाक्षः->undefined_y ||
                (wind->अङ्कः_outputs && !गवाक्षः->चरमः_position_pending)) {
                output = रिक्त;
            }
        }

        // Commit to set any pending size or limit data.
        यदि (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        समुच्चयः_Fullscreen(गवाक्षः, output, !!fullscreen);
    } अन्यथा यदि (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        यदि (wind->चरमः_display_ID != display->id) {
            wind->fullscreen_was_positioned = true;
            समुच्चयः_Fullscreen(गवाक्षः, output, true);
        } अन्यथा {
            Configure_गवाक्षः_Geometry(गवाक्षः);
            CommitLibdecorFrame(गवाक्षः);

            प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    प्रत्यागम SDL_FULLSCREEN_PENDING;
}

शून्य Wayland_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    // Drop restore requests when showing the window.
    यदि (wind->showing_गवाक्षः) {
        प्रत्यागम;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    यदि (!(गवाक्षः->flags & (SDL_गवाक्षः_FULLSCREEN | SDL_गवाक्षः_MAXIMIZED)) &&
        !wind->pending_state_deadline_गणनम्) {
        प्रत्यागम;
    }

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (!wind->shell_surface.libdecor.frame) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_frame_unset_maximized(wind->shell_surface.libdecor.frame);
        सङ्कलय_Pending_State_Sync(wind);
    } अन्यथा
#यदि_अन्तः
        // Note that xdg-shell does NOT provide a way to unset minimize!
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel == रिक्त) {
                प्रत्यागम; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            सङ्कलय_Pending_State_Sync(wind);
        }
}

शून्य Wayland_समुच्चयः_गवाक्षः_Bordered(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool bordered)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;
    ध्रुव SDL_Video_दत्त *viddata = (ध्रुव SDL_Video_दत्त *)_this->आन्तरिकम्;

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (wind->shell_surface.libdecor.frame) {
            libdecor_frame_समुच्चयः_visibility(wind->shell_surface.libdecor.frame, bordered);
        }
    } अन्यथा
#यदि_अन्तः
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि ((viddata->decoration_manager) && (wind->server_decoration)) {
            ध्रुव गणना zxdg_toplevel_decoration_v1_बहुलकम् बहुलकम् = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_बहुलकम्_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_बहुलकम्_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_समुच्चयः_बहुलकम्(wind->server_decoration, बहुलकम्);
        }
    }
}

शून्य Wayland_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool resizable)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    समुच्चयः_Min_Max_Dimensions(गवाक्षः);
    CommitLibdecorFrame(गवाक्षः);

    यदि (wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN) {
        wind->pending_state_commit = true;
    }
}

शून्य Wayland_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    यदि (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->आन्तरिकम्->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    यदि (!(गवाक्षः->flags & SDL_गवाक्षः_FULLSCREEN) && (गवाक्षः->flags & SDL_गवाक्षः_MAXIMIZED) &&
        !wind->pending_state_deadline_गणनम्) {
        प्रत्यागम;
    }

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (!wind->shell_surface.libdecor.frame) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        यदि (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_frame_समुच्चयः_maximized(wind->shell_surface.libdecor.frame);
        सङ्कलय_Pending_State_Sync(wind);
    } अन्यथा
#यदि_अन्तः
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel == रिक्त) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        यदि (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_समुच्चयः_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        सङ्कलय_Pending_State_Sync(wind);
    }
}

शून्य Wayland_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    यदि (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        प्रत्यागम;
    }

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (!wind->shell_surface.libdecor.frame) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_frame_समुच्चयः_minimized(wind->shell_surface.libdecor.frame);
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_MINIMIZED, 0, 0);
    } अन्यथा
#यदि_अन्तः
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel == रिक्त) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }
        xdg_toplevel_समुच्चयः_minimized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        SDL_Send_गवाक्षः_Event(गवाक्षः, SDL_EVENT_गवाक्षः_MINIMIZED, 0, 0);
    }
}

bool Wayland_समुच्चयः_गवाक्षः_Mouse_Rect(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    /* This may look suspiciously like SetWindowGrab, despite SetMouseRect not
     * implicitly doing a grab. And you're right! Wayland doesn't let us mess
     * around with mouse focus whatsoever, so it just happens to be that the
     * work that we can do in these two functions ends up being the same.
     *
     * Just know that this call lets you confine with a rect, SetWindowGrab
     * lets you confine without a rect.
     */
    यदि (!दत्त->pointer_constraints) {
        प्रत्यागम SDL_समुच्चयः_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_DisplayUpdatePointerGrabs(दत्त, गवाक्षः->आन्तरिकम्);
    प्रत्यागम true;
}

bool Wayland_समुच्चयः_गवाक्षः_Mouse_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    यदि (!दत्त->pointer_constraints) {
        प्रत्यागम SDL_समुच्चयः_Error("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_DisplayUpdatePointerGrabs(दत्त, गवाक्षः->आन्तरिकम्);
    प्रत्यागम true;
}

bool Wayland_समुच्चयः_गवाक्षः_Keyboard_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    यदि (!दत्त->कुञ्चिका_inhibitor_manager) {
        प्रत्यागम SDL_समुच्चयः_Error("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(दत्त, गवाक्षः->आन्तरिकम्);
    प्रत्यागम true;
}

bool Wayland_Reconfigure_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः_Flags flags)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    // Don't try to reconfigure mapped windows, unless they are custom or external.
    यदि (दत्त->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN &&
        दत्त->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        // Window is already mapped; abort.
        प्रत्यागम false;
    }

    /* The caller guarantees that only one of the GL or Vulkan flags will be set.
     * Note that Vulkan doesn't require any specific configuration, so only EGL
     * objects are added and removed as required.
     */
    यदि (flags & SDL_गवाक्षः_OPENGL) {
        यदि (!दत्त->egl_गवाक्षः) {
            दत्त->egl_गवाक्षः = WAYLAND_wl_egl_गवाक्षः_create(दत्त->surface, दत्त->current.pixel_विस्तारः, दत्त->current.pixel_height);
        }

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
        दत्त->egl_surface = SDL_EGL_CreateSurface(_this, गवाक्षः, (Native_गवाक्षः_Type)दत्त->egl_गवाक्षः);

        यदि (दत्त->egl_surface == EGL_NO_SURFACE) {
            प्रत्यागम false; // SDL_EGL_CreateSurface should have set the error.
        }
#यदि_अन्तः

        यदि (!दत्त->gles_swap_frame_event_queue) {
            दत्त->gles_swap_frame_event_queue = WAYLAND_wl_display_create_queue(दत्त->wayland_दत्त->display);
            दत्त->gles_swap_frame_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(दत्त->surface);
            WAYLAND_wl_proxy_समुच्चयः_queue((संरचना wl_proxy *)दत्त->gles_swap_frame_surface_wrapper, दत्त->gles_swap_frame_event_queue);
            दत्त->gles_swap_frame_callback = wl_surface_frame(दत्त->gles_swap_frame_surface_wrapper);
            wl_callback_सङ्कलय_listener(दत्त->gles_swap_frame_callback, &gles_swap_frame_listener, दत्त);
        }
    } अन्यथा {
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
        यदि (दत्त->egl_surface) {
            SDL_EGL_DestroySurface(_this, दत्त->egl_surface);
            दत्त->egl_surface = EGL_NO_SURFACE;
        }
#यदि_अन्तः

        यदि (दत्त->egl_गवाक्षः) {
            WAYLAND_wl_egl_गवाक्षः_destroy(दत्त->egl_गवाक्षः);
            दत्त->egl_गवाक्षः = रिक्त;
        }

        यदि (दत्त->gles_swap_frame_callback) {
            wl_callback_destroy(दत्त->gles_swap_frame_callback);
            दत्त->gles_swap_frame_callback = रिक्त;
        }

        यदि (दत्त->gles_swap_frame_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(दत्त->gles_swap_frame_surface_wrapper);
            दत्त->gles_swap_frame_surface_wrapper = रिक्त;
        }

        यदि (दत्त->gles_swap_frame_event_queue) {
            WAYLAND_wl_event_queue_destroy(दत्त->gles_swap_frame_event_queue);
            दत्त->gles_swap_frame_event_queue = रिक्त;
        }
    }

    प्रत्यागम true;
}

bool Wayland_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props)
{
    SDL_गवाक्षः_दत्त *दत्त;
    SDL_Video_दत्त *c = _this->आन्तरिकम्;
    संरचना wl_surface *external_surface = (संरचना wl_surface *)SDL_GetPointerProperty(create_props, SDL_PROP_गवाक्षः_CREATE_WAYLAND_WL_SURFACE_POINTER,
                                                                               (संरचना wl_surface *)SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", रिक्त));
    ध्रुव bool custom_surface_role = (external_surface != रिक्त) || SDL_GetBooleanProperty(create_props, SDL_PROP_गवाक्षः_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    ध्रुव bool create_egl_गवाक्षः = !!(गवाक्षः->flags & SDL_गवाक्षः_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_गवाक्षः_CREATE_WAYLAND_CREATE_EGL_गवाक्षः_BOOLEAN, false);

    दत्त = SDL_calloc(1, परिमाण(*दत्त));
    यदि (!दत्त) {
        प्रत्यागम false;
    }

    गवाक्षः->आन्तरिकम् = दत्त;
    दत्त->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_गवाक्षः_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    यदि (गवाक्षः->x == SDL_WINDOWPOS_UNDEFINED) {
        गवाक्षः->x = 0;
    }
    यदि (गवाक्षः->y == SDL_WINDOWPOS_UNDEFINED) {
        गवाक्षः->y = 0;
    }

    दत्त->wayland_दत्त = c;
    दत्त->sdlwindow = गवाक्षः;

    // Default to all capabilities
    दत्त->wm_caps = WAYLAND_WM_CAPS_ALL;

    दत्त->scale_गुणकः_2 = 1.0;

    यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
        दत्त->scale_गन्तव्यम्_display = गवाक्षः->parent->आन्तरिकम्->scale_गन्तव्यम्_display;
        दत्त->scale_गुणकः_2 = गवाक्षः->parent->आन्तरिकम्->scale_गुणकः_2;
        EnsurePopupPositionIsValid(गवाक्षः, &गवाक्षः->x, &गवाक्षः->y);
    } अन्यथा {
        प्रति (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; i++) {
            दत्त->scale_गुणकः_2 = SDL_max(दत्त->scale_गुणकः_2, _this->displays[i]->आन्तरिकम्->scale_गुणकः_2);
        }
    }

    दत्त->outputs = रिक्त;
    दत्त->अङ्कः_outputs = 0;
    दत्त->scale_गन्तव्यम्_display = c->scale_गन्तव्यम्_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    दत्त->app_id = SDL_strdup(SDL_GetAppID());

    यदि (!दत्त->scale_गन्तव्यम्_display) {
        दत्त->requested.logical_विस्तारः = गवाक्षः->floating.w;
        दत्त->requested.logical_height = गवाक्षः->floating.h;
    } अन्यथा {
        दत्त->requested.logical_विस्तारः = Pixel_गन्तव्यम्_Point(गवाक्षः, गवाक्षः->floating.w);
        दत्त->requested.logical_height = Pixel_गन्तव्यम्_Point(गवाक्षः, गवाक्षः->floating.h);
        दत्त->requested.pixel_विस्तारः = गवाक्षः->floating.w;
        दत्त->requested.pixel_height = गवाक्षः->floating.h;
    }

    यदि (!external_surface) {
        दत्त->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_सङ्कलय_listener(दत्त->surface, &surface_listener, दत्त);
        wl_surface_समुच्चयः_user_दत्त(दत्त->surface, दत्त);
        SDL_WAYLAND_पञ्जिकाकोशः_surface(दत्त->surface);
    } अन्यथा {
        गवाक्षः->flags |= SDL_गवाक्षः_EXTERNAL;
        दत्त->surface = external_surface;

        /* External surfaces are registered by being put in a list, as changing tags or userdata
         * can cause problems with external toolkits.
         */
        Wayland_सङ्कलय_गवाक्षः_दत्त_गन्तव्यम्_External_List(दत्त);
    }

    /* Always attach a viewport and fractional scale manager if available and the surface is not custom/external,
     * or the custom/external surface was explicitly flagged as high pixel density aware, which signals that the
     * application wants SDL to handle scaling.
     */
    यदि (!custom_surface_role || (गवाक्षः->flags & SDL_गवाक्षः_उच्चः_PIXEL_DENSITY)) {
        यदि (c->viewporter) {
            दत्त->viewport = wp_viewporter_get_viewport(c->viewporter, दत्त->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_समुच्चयः_source(दत्त->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        यदि (c->fractional_scale_manager) {
            दत्त->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, दत्त->surface);
            wp_fractional_scale_v1_सङ्कलय_listener(दत्त->fractional_scale, &fractional_scale_listener, दत्त);
        }
    }

    यदि (!custom_surface_role) {
        यदि (c->wp_color_manager_v1) {
            दत्त->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, दत्त->surface);
            wp_color_management_surface_feedback_v1_सङ्कलय_listener(दत्त->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, दत्त);
            Wayland_Get_Color_Info_For_गवाक्षः(दत्त, true);
        } अन्यथा यदि (c->frog_color_management_factory_v1) {
            दत्त->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, दत्त->surface);
            frog_color_managed_surface_सङ्कलय_listener(दत्त->frog_color_managed_surface, &frog_surface_listener, दत्त);
        }

        यदि (c->wp_alpha_modifier_v1) {
            दत्त->wp_alpha_modifier_surface_v1 = wp_alpha_modifier_v1_get_surface(c->wp_alpha_modifier_v1, दत्त->surface);
            wp_alpha_modifier_surface_v1_समुच्चयः_multiplier(दत्त->wp_alpha_modifier_surface_v1, SDL_MAX_UINT32);
        }
    }

    // Must be called before EGL configuration to set the drawable backbuffer size.
    Configure_गवाक्षः_Geometry(गवाक्षः);

    /* Fire a callback when the compositor wants a new frame rendered.
     * Right now this only matters for OpenGL; we use this callback to add a
     * wait timeout that avoids getting deadlocked by the compositor when the
     * window isn't visible.
     */
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        दत्त->gles_swap_frame_event_queue = WAYLAND_wl_display_create_queue(दत्त->wayland_दत्त->display);
        दत्त->gles_swap_frame_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(दत्त->surface);
        WAYLAND_wl_proxy_समुच्चयः_queue((संरचना wl_proxy *)दत्त->gles_swap_frame_surface_wrapper, दत्त->gles_swap_frame_event_queue);
        दत्त->gles_swap_frame_callback = wl_surface_frame(दत्त->gles_swap_frame_surface_wrapper);
        wl_callback_सङ्कलय_listener(दत्त->gles_swap_frame_callback, &gles_swap_frame_listener, दत्त);
    }

    यदि (गवाक्षः->flags & SDL_गवाक्षः_TRANSPARENT) {
        यदि (_this->gl_config.alpha_आकार == 0) {
            _this->gl_config.alpha_आकार = 8;
        }
    }

    यदि (create_egl_गवाक्षः) {
        दत्त->egl_गवाक्षः = WAYLAND_wl_egl_गवाक्षः_create(दत्त->surface, दत्त->current.pixel_विस्तारः, दत्त->current.pixel_height);
    }

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    यदि (गवाक्षः->flags & SDL_गवाक्षः_OPENGL) {
        // Create the GLES window surface
        दत्त->egl_surface = SDL_EGL_CreateSurface(_this, गवाक्षः, (Native_गवाक्षः_Type)दत्त->egl_गवाक्षः);

        यदि (दत्त->egl_surface == EGL_NO_SURFACE) {
            प्रत्यागम false; // SDL_EGL_CreateSurface should have set error
        }
    }
#यदि_अन्तः

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    यदि (!custom_surface_role) {
#यदि_परिभाषितम् HAVE_LIBDECOR_H
        यदि (c->shell.libdecor && !SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
            दत्त->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } अन्यथा
#यदि_अन्तः
            यदि (c->shell.xdg) {
            यदि (SDL_गवाक्षः_IS_POPUP(गवाक्षः)) {
                दत्त->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP;
            } अन्यथा {
                दत्त->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL;
            }
        } // All other cases will be WAYLAND_SURFACE_UNKNOWN
    } अन्यथा {
        // Roleless and external surfaces are always considered to be in the shown state by the backend.
        दत्त->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_CUSTOM;
        दत्त->shell_surface_स्थितिः = WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN;

        // External windows are presumed to be shown.
        यदि (गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL) {
            गवाक्षः->flags &= ~SDL_गवाक्षः_HIDDEN;
        }
    }

    यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_बफर, false)) {
        दत्त->double_बफर = true;
    }

    SDL_PropertiesID props = SDL_Get_गवाक्षः_Properties(गवाक्षः);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_DISPLAY_POINTER, दत्त->wayland_दत्त->display);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_SURFACE_POINTER, दत्त->surface);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_VIEWPORT_POINTER, दत्त->viewport);
    SDL_समुच्चयः_Pointer_Property(props, SDL_PROP_गवाक्षः_WAYLAND_EGL_गवाक्षः_POINTER, दत्त->egl_गवाक्षः);
    यदि (दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || दत्त->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ध्रुव वर्ण *गवाक्षः_id = SDL_GetStringProperty(create_props, SDL_PROP_गवाक्षः_CREATE_WAYLAND_गवाक्षः_ID_STRING, रिक्त);
        यदि (गवाक्षः_id && *गवाक्षः_id != '\0') {
            SDL_समुच्चयः_String_Property(props, SDL_PROP_गवाक्षः_WAYLAND_गवाक्षः_ID_STRING, गवाक्षः_id);
        }
    }

    दत्त->लब्धम्_test_परिणाम = SDL_HITTEST_प्रसामान्यम्;

    प्रत्यागम true;
}

शून्य Wayland_समुच्चयः_गवाक्षः_Minimum_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    गवाक्षः->आन्तरिकम्->limits_परिवर्तितम् = true;
}

शून्य Wayland_समुच्चयः_गवाक्षः_अधिकतमम्_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    गवाक्षः->आन्तरिकम्->limits_परिवर्तितम् = true;
}

शून्य Wayland_समुच्चयः_गवाक्षः_Aspect_अनुपातः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    गवाक्षः->आन्तरिकम्->limits_परिवर्तितम् = true;
}

bool Wayland_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    // Only popup windows can be positioned relative to the parent.
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        यदि (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_संस्करणम्(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_संस्करणम्) {
            प्रत्यागम SDL_Unsupported();
        }

        RepositionPopup(गवाक्षः, false);
        प्रत्यागम true;
    } अन्यथा यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(गवाक्षः);

        यदि (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_Get_Video_Display_For_Fullscreen_गवाक्षः(गवाक्षः);
            यदि (display && wind->चरमः_display_ID != display->id) {
                संरचना wl_output *output = display->आन्तरिकम्->output;
                समुच्चयः_Fullscreen(गवाक्षः, output, true);

                प्रत्यागम true;
            }
        }
    }
    प्रत्यागम SDL_समुच्चयः_Error("wayland cannot position non-popup windows");
}

शून्य Wayland_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    /* Flush any pending state operations, as fullscreen windows do not get
     * explicitly resized, not strictly obeying the size of a maximized window
     * is a protocol violation, and pending restore events might result in a
     * configure event overwriting the requested size.
     *
     * Calling this on a custom surface is informative, so the size must
     * always be passed through.
     */
    FlushPendingEvents(गवाक्षः);

    ध्रुव bool maximized = (गवाक्षः->flags & SDL_गवाक्षः_MAXIMIZED) != 0;
    ध्रुव bool resizable_state = !(गवाक्षः->flags & (SDL_गवाक्षः_MAXIMIZED | SDL_गवाक्षः_FULLSCREEN));

    /* Maximized and fullscreen windows don't get resized, and the new size is ignored
     * if this is just to recalculate the min/max or aspect limits on a tiled window.
     *
     * Some compositors will mark tiled windows as maximized. In these cases, the content
     * size is recalculated, but window size itself is left alone, as the spec states that
     * the configure size of a maximized window must be obeyed.
     */
    यदि (resizable_state || (गवाक्षः->tiled && !wind->limits_परिवर्तितम्) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        यदि (!maximized) {
            यदि (!wind->scale_गन्तव्यम्_display) {
                wind->requested.logical_विस्तारः = गवाक्षः->pending.w;
                wind->requested.logical_height = गवाक्षः->pending.h;
            } अन्यथा {
                wind->requested.logical_विस्तारः = Pixel_गन्तव्यम्_Point(गवाक्षः, गवाक्षः->pending.w);
                wind->requested.logical_height = Pixel_गन्तव्यम्_Point(गवाक्षः, गवाक्षः->pending.h);
                wind->requested.pixel_विस्तारः = गवाक्षः->pending.w;
                wind->requested.pixel_height = गवाक्षः->pending.h;
            }
        }

        /* If a non-resizable window somehow wound up in the tiled state, store the new
         * size in the floating parameters so the size will be preserved for future
         * configure events.
         *
         * This shouldn't happen, but apparently it can on at least one compositor...
         */
        यदि (गवाक्षः->tiled && !(गवाक्षः->flags & SDL_गवाक्षः_RESIZABLE)) {
            गवाक्षः->floating.w = गवाक्षः->pending.w;
            गवाक्षः->floating.h = गवाक्षः->pending.h;
        }
    } अन्यथा {
        // Can't resize the window.
        गवाक्षः->चरमः_आकार_pending = false;
    }

    wind->limits_परिवर्तितम् = false;
    यदि (wind->shell_surface_स्थितिः == WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    Configure_गवाक्षः_Geometry(गवाक्षः);
    CommitLibdecorFrame(गवाक्षः);
}

शून्य Wayland_Get_गवाक्षः_आकार_अन्तर्_Pixels(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    *w = दत्त->current.pixel_विस्तारः;
    *h = दत्त->current.pixel_height;
}

भिन्न Wayland_Get_गवाक्षः_Content_Scale(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    यदि (गवाक्षः->flags & SDL_गवाक्षः_उच्चः_PIXEL_DENSITY || wind->scale_गन्तव्यम्_display || wind->fullscreen_exclusive) {
        प्रत्यागम (भिन्न)wind->scale_गुणकः_2;
    }

    प्रत्यागम 1.0f;
}

SDL_DisplayID Wayland_Get_Display_For_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    यदि (wind) {
        प्रत्यागम wind->चरमः_display_ID;
    }

    प्रत्यागम 0;
}

bool Wayland_समुच्चयः_गवाक्षः_Opacity(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, भिन्न opacity)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    यदि (wind->wp_alpha_modifier_surface_v1) {
        ध्रुव bool is_opaque = !(गवाक्षः->flags & SDL_गवाक्षः_TRANSPARENT) && opacity == 1.0f;

        यदि (wind->आवरणम्.mapped && wind->आवरणम्.opaque != is_opaque) {
            संरचना wl_बफर *old_बफर = wind->आवरणम्.बफर_2;
            wind->आवरणम्.opaque = is_opaque;
            wind->आवरणम्.बफर_2 = Wayland_Create_Single_Pixel_बफर(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->आवरणम्.surface, wind->आवरणम्.बफर_2, 0, 0);
            यदि (wl_surface_get_संस्करणम्(wind->आवरणम्.surface) >= WL_SURFACE_DAMAGE_बफर_SINCE_संस्करणम्) {
                wl_surface_damage_बफर(wind->आवरणम्.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } अन्यथा {
                wl_surface_damage(wind->आवरणम्.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            यदि (is_opaque) {
                समुच्चयः_Surface_Opaque_Region(wind->आवरणम्.surface, wind->current.logical_विस्तारः, wind->current.logical_height);
            } अन्यथा {
                समुच्चयः_Surface_Opaque_Region(wind->आवरणम्.surface, 0, 0);
            }

            wl_surface_commit(wind->आवरणम्.surface);

            यदि (old_बफर) {
                wl_बफर_destroy(old_बफर);
            }
        }

        यदि (is_opaque) {
            समुच्चयः_Surface_Opaque_Region(wind->surface, wind->current.viewport_विस्तारः, wind->current.viewport_height);
        } अन्यथा {
            समुच्चयः_Surface_Opaque_Region(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_समुच्चयः_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((द्विगुण)SDL_MAX_UINT32 * (द्विगुण)opacity));

        प्रत्यागम true;
    }

    प्रत्यागम SDL_समुच्चयः_Error("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

शून्य Wayland_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;
    ध्रुव वर्ण *title = गवाक्षः->title ? गवाक्षः->title : "";

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        libdecor_frame_समुच्चयः_title(wind->shell_surface.libdecor.frame, title);
    } अन्यथा
#यदि_अन्तः
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_समुच्चयः_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

स्थिर पूर्णाङ्क icon_क्रमय_callback(ध्रुव शून्य *a, ध्रुव शून्य *b)
{
    ध्रुव SDL_Surface *s1 = *(ध्रुव SDL_Surface **)a;
    ध्रुव SDL_Surface *s2 = *(ध्रुव SDL_Surface **)b;

    प्रत्यागम (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_समुच्चयः_गवाक्षः_Icon(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *icon)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;
    Wayland_SHMPool *shm_pool = रिक्त;
    संरचना xdg_toplevel *toplevel = रिक्त;

    यदि (!_this->आन्तरिकम्->xdg_toplevel_icon_manager_v1) {
        प्रत्यागम SDL_समुच्चयः_Error("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    पूर्णाङ्क image_गणनम्_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_गणनम्_2);
    यदि (!images || !image_गणनम्_2) {
        प्रत्यागम false;
    }

    // Release the old icon resources.
    यदि (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = रिक्त;
    }

    प्रति (पूर्णाङ्क i = 0; i < wind->icon_बफर_गणनम्; ++i) {
        wl_बफर_destroy(wind->icon_buffers[i]);
    }
    wind->icon_बफर_गणनम् = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->आन्तरिकम्->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_गणनम्_2 * परिमाण(संरचना wl_बफर *));
    यदि (!wind->icon_buffers) {
        गच्छ failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    size_t pool_आकार = 0;
    प्रति (पूर्णाङ्क i = 0; i < image_गणनम्_2; ++i) {
        // Images must be square. Non-square images will be centered.
        ध्रुव पूर्णाङ्क आकार = SDL_max(images[i]->w, images[i]->h);
        pool_आकार += आकार * आकार * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_गणनम्_2, परिमाण(SDL_Surface *), icon_क्रमय_callback);

    shm_pool = Wayland_AllocSHMPool(pool_आकार);
    यदि (!shm_pool) {
        SDL_समुच्चयः_Error("wayland: failed to allocate an SHM pool for the icon");
        गच्छ failure_cleanup;
    }

    ध्रुव द्विगुण आधारः_आकार = (द्विगुण)SDL_max(icon->w, icon->h);
    प्रति (पूर्णाङ्क i = 0; i < image_गणनम्_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        ध्रुव पूर्णाङ्क level_आकार = SDL_max(surface->w, surface->h);
        ध्रुव पूर्णाङ्क scale = (पूर्णाङ्क)SDL_floor((द्विगुण)level_आकार / आधारः_आकार);
        यदि (!scale) {
            अनुवर्त;
        }

        यदि (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            यदि (!surface) {
                SDL_समुच्चयः_Error("wayland: failed to convert the icon image to ARGB8888 format");
                गच्छ failure_cleanup;
            }
        }

        शून्य *बफर_mem;
        संरचना wl_बफर *बफर_2 = Wayland_Alloc_बफर_From_Pool(shm_pool, level_आकार, level_आकार, &बफर_mem);
        यदि (!बफर_2) {
            // Clean up the temporary conversion surface.
            यदि (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_समुच्चयः_Error("wayland: failed to allocate a wl_buffer for the icon");
            गच्छ failure_cleanup;
        }

        wind->icon_buffers[wind->icon_बफर_गणनम्++] = बफर_2;

        // Center non-square images.
        यदि (surface->w < level_आकार) {
            SDL_memset(बफर_mem, 0, level_आकार * level_आकार * 4);
            बफर_mem = (Uint8 *)बफर_mem + (((level_आकार - surface->w) / 2) * 4);
        } अन्यथा यदि (surface->h < level_आकार) {
            SDL_memset(बफर_mem, 0, level_आकार * level_आकार * 4);
            बफर_mem = (Uint8 *)बफर_mem + (((level_आकार - surface->h) / 2) * (level_आकार * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, बफर_mem, level_आकार * 4, true);

        xdg_toplevel_icon_v1_सङ्कलय_बफर(wind->xdg_toplevel_icon_v1, बफर_2, scale);

        // Clean up the temporary scaled or conversion surface.
        यदि (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        toplevel = libdecor_frame_get_xdg_toplevel(wind->shell_surface.libdecor.frame);
    } अन्यथा
#यदि_अन्तः
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    यदि (toplevel) {
        xdg_toplevel_icon_manager_v1_समुच्चयः_icon(_this->आन्तरिकम्->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
    }

    Wayland_ReleaseSHMPool(shm_pool);
    SDL_free(images);

    प्रत्यागम true;

failure_cleanup:

    SDL_free(images);

    यदि (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = रिक्त;
    }

    Wayland_ReleaseSHMPool(shm_pool);

    प्रति (पूर्णाङ्क i = 0; i < wind->icon_बफर_गणनम्; ++i) {
        wl_बफर_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = रिक्त;
    wind->icon_बफर_गणनम् = 0;

    प्रत्यागम false;
}

शून्य *Wayland_Get_गवाक्षः_ICCProfile(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, size_t *आकार)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;
    शून्य *ret = रिक्त;

    यदि (wind->icc_आकार > 0) {
        शून्य *icc_map = mmap(रिक्त, wind->icc_आकार, PROT_READ, MAP_PRIVATE, wind->icc_fd, 0);
        यदि (icc_map != MAP_FAILED) {
            ret = SDL_malloc(wind->icc_आकार);
            यदि (ret) {
                *आकार = wind->icc_आकार;
                SDL_memcpy(ret, icc_map, *आकार);
            }
            munmap(icc_map, wind->icc_आकार);
        }
    }

    प्रत्यागम ret;
}

bool Wayland_Sync_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    कुरु {
        WAYLAND_wl_display_roundtrip(_this->आन्तरिकम्->display);
    } यावत् (wind->pending_state_deadline_गणनम्);

    प्रत्यागम true;
}

शून्य Wayland_AcceptDragAndDrop(SDL_गवाक्षः *गवाक्षः, bool accept)
{
    गवाक्षः->आन्तरिकम्->accepts_drag_and_drop = accept;
}

bool Wayland_समुच्चयः_गवाक्षः_Focusable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool focusable)
{
    यदि (गवाक्षः->flags & SDL_गवाक्षः_POPUP_MENU) {
        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_HIDDEN)) {
            यदि (!focusable && (गवाक्षः->flags & SDL_गवाक्षः_निवेशः_FOCUS)) {
                SDL_गवाक्षः *new_focus;
                ध्रुव bool समुच्चयः_focus = SDL_ShouldRelinquishPopupFocus(गवाक्षः, &new_focus);
                Wayland_समुच्चयः_Keyboard_Focus(new_focus, समुच्चयः_focus);
            } अन्यथा यदि (focusable) {
                यदि (SDL_ShouldFocusPopup(गवाक्षः)) {
                    Wayland_समुच्चयः_Keyboard_Focus(गवाक्षः, true);
                }
            }
        }

        प्रत्यागम true;
    }

    प्रत्यागम SDL_समुच्चयः_Error("wayland: focus can only be toggled on popup menu windows");
}

शून्य Wayland_Show_गवाक्षः_System_Menu(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क x, पूर्णाङ्क y)
{
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;
    SDL_WaylandSeat *seat = wind->wayland_दत्त->चरमः_implicit_grab_seat;

    यदि (!seat) {
        प्रत्यागम;
    }

    यदि (wind->scale_गन्तव्यम्_display) {
        x = Pixel_गन्तव्यम्_Point(गवाक्षः, x);
        y = Pixel_गन्तव्यम्_Point(गवाक्षः, y);
    }

#यदि_परिभाषितम् HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (wind->shell_surface.libdecor.frame) {
            libdecor_frame_show_गवाक्षः_menu(wind->shell_surface.libdecor.frame, seat->wl_seat, seat->चरमः_implicit_grab_serial, x, y);
        }
    } अन्यथा
#यदि_अन्तः
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_गवाक्षः_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->चरमः_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

#यदि_परिभाषितम् SDL_USE_LIBDBUS
    यदि (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        प्रत्यागम true;
    }
#यदि_अन्तः

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    यदि (दत्त->idle_inhibit_manager) {
        SDL_गवाक्षः *गवाक्षः = _this->windows;
        यावत् (गवाक्षः) {
            SDL_गवाक्षः_दत्त *win_दत्त = गवाक्षः->आन्तरिकम्;

            यदि (_this->suspend_screensaver && !win_दत्त->idle_inhibitor) {
                win_दत्त->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(दत्त->idle_inhibit_manager,
                                                                 win_दत्त->surface);
            } अन्यथा यदि (!_this->suspend_screensaver && win_दत्त->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_दत्त->idle_inhibitor);
                win_दत्त->idle_inhibitor = रिक्त;
            }

            गवाक्षः = गवाक्षः->अग्र;
        }
    }

    प्रत्यागम true;
}

शून्य Wayland_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    SDL_गवाक्षः_दत्त *wind = गवाक्षः->आन्तरिकम्;

    यदि (दत्त && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        यदि (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            गवाक्षः->लब्धम्_test = रिक्त;
            WAYLAND_wl_display_roundtrip(दत्त->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_Display_Remove_गवाक्षः_References_From_Seats(दत्त, wind);

        यदि (wind->आवरणम्.viewport) {
            wp_viewport_destroy(wind->आवरणम्.viewport);
        }
        यदि (wind->आवरणम्.बफर_2) {
            wl_बफर_destroy(wind->आवरणम्.बफर_2);
        }
        यदि (wind->आवरणम्.subsurface) {
            wl_subsurface_destroy(wind->आवरणम्.subsurface);
        }
        यदि (wind->आवरणम्.surface) {
            wl_surface_destroy(wind->आवरणम्.surface);
        }
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
        यदि (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#यदि_अन्तः
        यदि (wind->egl_गवाक्षः) {
            WAYLAND_wl_egl_गवाक्षः_destroy(wind->egl_गवाक्षः);
        }

        यदि (wind->idle_inhibitor) {
            zwp_idle_inhibitor_v1_destroy(wind->idle_inhibitor);
        }

        यदि (wind->activation_token) {
            xdg_activation_token_v1_destroy(wind->activation_token);
        }

        यदि (wind->viewport) {
            wp_viewport_destroy(wind->viewport);
        }

        यदि (wind->fractional_scale) {
            wp_fractional_scale_v1_destroy(wind->fractional_scale);
        }

        यदि (wind->wp_alpha_modifier_surface_v1) {
            wp_alpha_modifier_surface_v1_destroy(wind->wp_alpha_modifier_surface_v1);
        }

        यदि (wind->frog_color_managed_surface) {
            frog_color_managed_surface_destroy(wind->frog_color_managed_surface);
        }

        यदि (wind->wp_color_management_surface_feedback) {
            Wayland_FreeColorInfoState(wind->color_info_state);
            wp_color_management_surface_feedback_v1_destroy(wind->wp_color_management_surface_feedback);
        }

        SDL_free(wind->outputs);
        SDL_free(wind->app_id);

        यदि (wind->gles_swap_frame_callback) {
            wl_callback_destroy(wind->gles_swap_frame_callback);
            WAYLAND_wl_proxy_wrapper_destroy(wind->gles_swap_frame_surface_wrapper);
            WAYLAND_wl_event_queue_destroy(wind->gles_swap_frame_event_queue);
        }

        यदि (!(गवाक्षः->flags & SDL_गवाक्षः_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } अन्यथा {
            Wayland_Remove_गवाक्षः_दत्त_From_External_List(wind);
        }

        यदि (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        प्रति (पूर्णाङ्क i = 0; i < wind->icon_बफर_गणनम्; ++i) {
            wl_बफर_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_बफर_गणनम् = 0;

        SDL_free(wind);
    }
    गवाक्षः->आन्तरिकम् = रिक्त;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND
