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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND

#समावेश <sys/mman.h>

#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../../core/unix/SDL_appid.h"
#समावेश "../../notification/SDL_notification_c.h"
#समावेश "../SDL_egl_c.h"
#समावेश "SDL_waylandevents_c.h"
#समावेश "SDL_waylandmouse.h"
#समावेश "SDL_waylandwindow.h"
#समावेश "SDL_waylandvideo.h"
#समावेश "../../SDL_hints_c.h"
#समावेश "SDL_waylandcolor.h"

#समावेश "alpha-modifier-v1-client-protocol.h"
#समावेश "xdg-shell-client-protocol.h"
#समावेश "xdg-decoration-unstable-v1-client-protocol.h"
#समावेश "idle-inhibit-unstable-v1-client-protocol.h"
#समावेश "xdg-activation-v1-client-protocol.h"
#समावेश "viewporter-client-protocol.h"
#समावेश "fractional-scale-v1-client-protocol.h"
#समावेश "xdg-foreign-unstable-v2-client-protocol.h"
#समावेश "xdg-dialog-v1-client-protocol.h"
#समावेश "frog-color-management-v1-client-protocol.h"
#समावेश "xdg-toplevel-icon-v1-client-protocol.h"
#समावेश "color-management-v1-client-protocol.h"
#समावेश "xdg-session-management-v1-client-protocol.h"
#समावेश "xdg-toplevel-tag-v1-client-protocol.h"

#अगर_घोषित HAVE_LIBDECOR_H
#समावेश <libdecor.h>
#पूर्ण_अगर

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
अटल bool ShouldMaskFullscreen()
{
    अटल पूर्णांक mask_required = -1;

    अगर (mask_required >= 0) {
        वापस mask_required != 0;
    }

    स्थिर अक्षर *desktop = SDL_getenv("XDG_CURRENT_DESKTOP");
    अगर (desktop && SDL_strstr(desktop, "KDE") != शून्य) {
        mask_required = 1;
    } अन्यथा {
        mask_required = 0;
    }

    वापस mask_required != 0;
}

अटल द्विगुन GetWindowScale(SDL_Window *window)
{
    वापस (window->flags & SDL_WINDOW_ऊपरी_PIXEL_DENSITY) || window->internal->scale_to_display ? window->internal->scale_factor : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
अटल पूर्णांक PointToPixel(SDL_Window *window, पूर्णांक point)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    वापस point ? SDL_max((पूर्णांक)SDL_lround((द्विगुन)point * GetWindowScale(window) + 1e-6), 1) : 0;
}

अटल पूर्णांक PixelToPoint(SDL_Window *window, पूर्णांक pixel)
{
    वापस pixel ? SDL_max((पूर्णांक)SDL_lround((द्विगुन)pixel / GetWindowScale(window)), 1) : 0;
}

क्रमागत WaylandModeScale
{
    WAYLAND_MODE_SCALE_UNDEFINED,
    WAYLAND_MODE_SCALE_ASPECT,
    WAYLAND_MODE_SCALE_STRETCH,
    WAYLAND_MODE_SCALE_NONE
};

अटल क्रमागत WaylandModeScale GetModeScaleMethod(व्योम)
{
    अटल क्रमागत WaylandModeScale scale_mode = WAYLAND_MODE_SCALE_UNDEFINED;

    अगर (scale_mode == WAYLAND_MODE_SCALE_UNDEFINED) {
        स्थिर अक्षर *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_MODE_SCALING);

        अगर (scale_hint) {
            अगर (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_mode = WAYLAND_MODE_SCALE_STRETCH;
            } अन्यथा अगर (!SDL_strcasecmp(scale_hint, "none")) {
                scale_mode = WAYLAND_MODE_SCALE_NONE;
            } अन्यथा {
                scale_mode = WAYLAND_MODE_SCALE_ASPECT;
            }
        } अन्यथा {
            scale_mode = WAYLAND_MODE_SCALE_ASPECT;
        }
    }

    वापस scale_mode;
}

प्रकार काष्ठा BorderInsets
{
    पूर्णांक बायाँ;
    पूर्णांक शीर्ष;
    पूर्णांक दायाँ;
    पूर्णांक bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
अटल व्योम GetBorderInsets(SDL_Window *window, BorderInsets *insets)
{
    SDL_zerop(insets);
    अगर (!window->internal->enable_insets) {
        वापस;
    }
    अगर (window->internal->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        स्थिर SDL_PropertiesID props = SDL_GetWindowProperties(window);
        insets->बायाँ = (पूर्णांक)SDL_clamp(SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_बायाँ_संख्या, 0), 0, SDL_MAX_SINT16);
        insets->शीर्ष = (पूर्णांक)SDL_clamp(SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_शीर्ष_संख्या, 0), 0, SDL_MAX_SINT16);
        insets->दायाँ = (पूर्णांक)SDL_clamp(SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_दायाँ_संख्या, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (पूर्णांक)SDL_clamp(SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_BOTTOM_संख्या, 0), 0, SDL_MAX_SINT16);
    }
}

अटल व्योम SetMinMaxDimensions(SDL_Window *window)
{
    SDL_Window_तथ्य *wind = window->internal;
    पूर्णांक min_width, min_height, max_width, max_height;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    अगर (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) {
        min_width = 0;
        min_height = 0;
        max_width = 0;
        max_height = 0;
    } अन्यथा अगर (window->flags & SDL_WINDOW_RESIZABLE) {
        पूर्णांक adj_w = SDL_max(window->min_w, wind->system_limits.min_width);
        पूर्णांक adj_h = SDL_max(window->min_h, wind->system_limits.min_height);
        अगर (wind->scale_to_display) {
            adj_w = PixelToPoint(window, adj_w);
            adj_h = PixelToPoint(window, adj_h);
        }
        min_width = adj_w;
        min_height = adj_h;

        adj_w = window->max_w ? SDL_max(window->max_w, wind->system_limits.min_width) : 0;
        adj_h = window->max_h ? SDL_max(window->max_h, wind->system_limits.min_height) : 0;
        अगर (wind->scale_to_display) {
            adj_w = PixelToPoint(window, adj_w);
            adj_h = PixelToPoint(window, adj_h);
        }
        max_width = adj_w;
        max_height = adj_h;
    } अन्यथा {
        min_width = wind->current.logical_width;
        min_height = wind->current.logical_height;
        max_width = wind->current.logical_width;
        max_height = wind->current.logical_height;
    }

#अगर_घोषित HAVE_LIBDECOR_H
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        अगर (!wind->shell_surface.libdecor.frame) {
            वापस; // Can't do anything yet, wait for ShowWindow
        }

        अगर (min_width && min_height && min_width == max_width && min_height == max_height) {
            libdecor_frame_unset_capabilities(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE);
        } अन्यथा {
            libdecor_frame_set_capabilities(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        अगर (libdecor_frame_has_capability(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE)) {
            libdecor_frame_set_min_content_आकार(wind->shell_surface.libdecor.frame,
                                                min_width,
                                                min_height);
            libdecor_frame_set_max_content_आकार(wind->shell_surface.libdecor.frame,
                                                max_width,
                                                max_height);
        }
    } अन्यथा
#पूर्ण_अगर
        अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        अगर (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            वापस; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(window, &insets);
        min_width = SDL_max(min_width - (insets.बायाँ + insets.दायाँ), min_width ? 1 : 0);
        min_height = SDL_max(min_height - (insets.शीर्ष + insets.bottom), min_height ? 1 : 0);
        अगर (max_width) {
            max_width = SDL_max(max_width - (insets.बायाँ + insets.दायाँ), 1);
        }
        अगर (max_height) {
            max_height = SDL_max(max_height - (insets.शीर्ष + insets.bottom), 1);
        }
        xdg_toplevel_set_min_आकार(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_width,
                                  min_height);
        xdg_toplevel_set_max_आकार(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_width,
                                  max_height);
    }
}

अटल व्योम EnsurePopupPositionIsValid(SDL_Window *window, पूर्णांक *x, पूर्णांक *y)
{
    पूर्णांक adj_गिनती = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    अगर (*x + window->w <= 0) {
        *x = -window->w;
        ++adj_गिनती;
    }
    अगर (*y + window->h <= 0) {
        *y = -window->h;
        ++adj_गिनती;
    }
    अगर (*x >= window->parent->w) {
        *x = window->parent->w;
        ++adj_गिनती;
    }
    अगर (*y >= window->parent->h) {
        *y = window->parent->h;
        ++adj_गिनती;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    अगर (adj_गिनती > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
अटल व्योम GetWindowGeometry(SDL_Window_तथ्य *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    अगर (SDL_RectEmpty(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_width;
        geometry->h = wind->current.logical_height;
    }
}

अटल व्योम AdjustPopupOffset(SDL_Window *popup, पूर्णांक *x, पूर्णांक *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#अगर_घोषित HAVE_LIBDECOR_H
    अगर (popup->parent->internal->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        पूर्णांक adj_x, adj_y;
        libdecor_frame_translate_coordinate(popup->parent->internal->shell_surface.libdecor.frame,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } अन्यथा
#पूर्ण_अगर
    {
        *x -= popup->parent->internal->explicit_geometry.x;
        *y -= popup->parent->internal->explicit_geometry.y;
    }
}

अटल व्योम RepositionPopup(SDL_Window *window, bool use_current_position)
{
    SDL_Window_तथ्य *wind = window->internal;

    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_version(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_VERSION) {
        पूर्णांक x = use_current_position ? window->x : window->pending.x;
        पूर्णांक y = use_current_position ? window->y : window->pending.y;

        EnsurePopupPositionIsValid(window, &x, &y);
        अगर (wind->scale_to_display) {
            x = PixelToPoint(window->parent, x);
            y = PixelToPoint(window->parent, y);
        }
        AdjustPopupOffset(window, &x, &y);
        SDL_Rect parent_geometry;
        GetWindowGeometry(window->parent->internal, &parent_geometry);
        xdg_positioner_set_anchor_rect(wind->shell_surface.xdg.popup.xdg_positioner, 0, 0, parent_geometry.w, parent_geometry.h);
        xdg_positioner_set_आकार(wind->shell_surface.xdg.popup.xdg_positioner, wind->current.logical_width, wind->current.logical_height);
        xdg_positioner_set_offset(wind->shell_surface.xdg.popup.xdg_positioner, x, y);
        xdg_popup_reposition(wind->shell_surface.xdg.popup.xdg_popup,
                             wind->shell_surface.xdg.popup.xdg_positioner,
                             0);
    }
}

अटल व्योम SetSurfaceOpaqueRegion(काष्ठा wl_surface *surface, पूर्णांक width, पूर्णांक height)
{
    SDL_Video_तथ्य *viddata = SDL_GetVideoDevice()->internal;

    अगर (width && height) {
        काष्ठा wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_add(region, 0, 0, width, height);
        wl_surface_set_opaque_region(surface, region);
        wl_region_destroy(region);
    } अन्यथा {
        wl_surface_set_opaque_region(surface, शून्य);
    }
}

अटल व्योम ConfigureWindowGeometry(SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    स्थिर द्विगुन scale_factor = GetWindowScale(window);
    स्थिर द्विगुन पूर्व_pointer_scale_x = तथ्य->pointer_scale.x;
    स्थिर द्विगुन पूर्व_pointer_scale_y = तथ्य->pointer_scale.y;
    स्थिर पूर्णांक old_pixel_width = तथ्य->current.pixel_width;
    स्थिर पूर्णांक old_pixel_height = तथ्य->current.pixel_height;
    पूर्णांक window_width = 0;
    पूर्णांक window_height = 0;
    पूर्णांक viewport_width, viewport_height;
    bool window_आकार_changed;
    bool बफर_आकार_changed;
    स्थिर bool is_opaque = !(window->flags & SDL_WINDOW_TRANSPARENT) && window->opacity == 1.0f;

    अगर (तथ्य->is_fullscreen && window->fullscreen_exclusive) {
        window_width = window->current_fullscreen_mode.w;
        window_height = window->current_fullscreen_mode.h;

        viewport_width = तथ्य->requested.logical_width;
        viewport_height = तथ्य->requested.logical_height;

        चयन (GetModeScaleMethod()) {
        हाल WAYLAND_MODE_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            अगर (window_width <= viewport_width && window_height <= viewport_height) {
                viewport_width = window_width;
                viewport_height = window_height;

                अवरोध;
            }
            SDL_FALLTHROUGH;
        हाल WAYLAND_MODE_SCALE_ASPECT:
        {
            स्थिर भग्न output_ratio = (भग्न)viewport_width / (भग्न)viewport_height;
            स्थिर भग्न mode_ratio = (भग्न)window_width / (भग्न)window_height;

            अगर (output_ratio > mode_ratio) {
                viewport_width = SDL_lroundf((भग्न)window_width * ((भग्न)viewport_height / (भग्न)window_height));
            } अन्यथा अगर (output_ratio < mode_ratio) {
                viewport_height = SDL_lroundf((भग्न)window_height * ((भग्न)viewport_width / (भग्न)window_width));
            }
        } अवरोध;
        शेष:
            अवरोध;
        }

        window_आकार_changed = window_width != window->w ||
                              window_height != window->h ||
                              तथ्य->current.viewport_width != viewport_width ||
                              तथ्य->current.viewport_height != viewport_height;

        // Exclusive fullscreen window sizes are always in pixel units.
        तथ्य->current.pixel_width = window_width;
        तथ्य->current.pixel_height = window_height;
        बफर_आकार_changed = तथ्य->current.pixel_width != old_pixel_width ||
                              तथ्य->current.pixel_height != old_pixel_height;

        अगर (window_आकार_changed || बफर_आकार_changed) {
            अगर (तथ्य->viewport) {
                wp_viewport_set_destination(तथ्य->viewport, viewport_width, viewport_height);

                तथ्य->current.logical_width = तथ्य->requested.logical_width;
                तथ्य->current.logical_height = तथ्य->requested.logical_height;
                तथ्य->current.viewport_width = viewport_width;
                तथ्य->current.viewport_height = viewport_height;
            } अन्यथा {
                // Calculate the integer scale from the mode and output.
                स्थिर int32_t int_scale = SDL_max(window->current_fullscreen_mode.w / viewport_width, 1);

                wl_surface_set_बफर_scale(तथ्य->surface, int_scale);
                तथ्य->current.logical_width = window->current_fullscreen_mode.w;
                तथ्य->current.logical_height = window->current_fullscreen_mode.h;
            }

            तथ्य->pointer_scale.x = (द्विगुन)window_width / (द्विगुन)viewport_width;
            तथ्य->pointer_scale.y = (द्विगुन)window_height / (द्विगुन)viewport_height;
        }
    } अन्यथा {
        अगर (!तथ्य->scale_to_display) {
            viewport_width = तथ्य->requested.logical_width;
            viewport_height = तथ्य->requested.logical_height;
        } अन्यथा {
            viewport_width = तथ्य->requested.pixel_width;
            viewport_height = तथ्य->requested.pixel_height;
        }

        अगर (!तथ्य->enable_insets &&
            तथ्य->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_HIDDEN &&
            तथ्य->viewport && तथ्य->wayland_तथ्य->subcompositor && !तथ्य->floating && !तथ्य->is_fullscreen) {
            पूर्णांक min_width, min_height, max_width, max_height;
            अगर (window->flags & SDL_WINDOW_RESIZABLE) {
                min_width = window->min_w;
                min_height = window->min_h;
                max_width = window->max_w;
                max_height = window->max_h;
            } अन्यथा {
                // Use the fixed size in the odd case where a non-resizable window somehow wound up tiled or maximized.
                min_width = window->floating.w;
                min_height = window->floating.h;
                max_width = window->floating.w;
                max_height = window->floating.h;
            }

            अगर (min_width) {
                viewport_width = SDL_max(viewport_width, min_width);
            }
            अगर (min_height) {
                viewport_height = SDL_max(viewport_height, min_height);
            }
            अगर (max_width) {
                viewport_width = SDL_min(viewport_width, max_width);
            }
            अगर (max_height) {
                viewport_height = SDL_min(viewport_height, max_height);
            }

            भग्न aspect = (भग्न)viewport_width / (भग्न)viewport_height;
            अगर (window->min_aspect != 0.f && aspect < window->min_aspect) {
                viewport_height = SDL_max(SDL_lroundf((भग्न)viewport_width / window->min_aspect), 1);
            } अन्यथा अगर (window->max_aspect != 0.f && aspect > window->max_aspect) {
                viewport_width = SDL_max(SDL_lroundf((भग्न)viewport_height * window->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            window_width = viewport_width;
            window_height = viewport_height;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            अगर (!तथ्य->scale_to_display) {
                अगर (viewport_width > तथ्य->requested.logical_width || viewport_height > तथ्य->requested.logical_height) {
                    aspect = (भग्न)viewport_width / (भग्न)viewport_height;
                    स्थिर भग्न window_ratio = (भग्न)तथ्य->requested.logical_width / (भग्न)तथ्य->requested.logical_height;
                    अगर (aspect >= window_ratio) {
                        viewport_width = तथ्य->requested.logical_width;
                        viewport_height = SDL_lroundf((भग्न)viewport_width / aspect);
                    } अन्यथा अगर (aspect < window_ratio) {
                        viewport_height = तथ्य->requested.logical_height;
                        viewport_width = SDL_lroundf((भग्न)viewport_height * aspect);
                    }
                }
            } अन्यथा {
                अगर (viewport_width > तथ्य->requested.pixel_width || viewport_height > तथ्य->requested.pixel_height) {
                    aspect = (भग्न)viewport_width / (भग्न)viewport_height;
                    स्थिर भग्न window_ratio = (भग्न)तथ्य->requested.pixel_width / (भग्न)तथ्य->requested.pixel_height;
                    अगर (aspect >= window_ratio) {
                        viewport_width = तथ्य->requested.pixel_width;
                        viewport_height = SDL_lroundf((भग्न)viewport_width / aspect);
                    } अन्यथा अगर (aspect < window_ratio) {
                        viewport_height = तथ्य->requested.pixel_height;
                        viewport_width = SDL_lroundf((भग्न)viewport_height * aspect);
                    }
                }
            }

            viewport_width = SDL_max(viewport_width, 1);
            viewport_height = SDL_max(viewport_height, 1);
        } अन्यथा {
            window_width = viewport_width;
            window_height = viewport_height;
        }

        अगर (!तथ्य->scale_to_display) {
            तथ्य->current.pixel_width = PointToPixel(window, window_width);
            तथ्य->current.pixel_height = PointToPixel(window, window_height);
        } अन्यथा {
            // The viewport size is in pixels at this point; convert it to logical units.
            तथ्य->current.pixel_width = window_width;
            तथ्य->current.pixel_height = window_height;
            viewport_width = PixelToPoint(window, viewport_width);
            viewport_height = PixelToPoint(window, viewport_height);
        }

        // Clamp the physical window size to the system minimum required size.
        तथ्य->requested.logical_width = SDL_max(तथ्य->requested.logical_width, तथ्य->system_limits.min_width);
        तथ्य->requested.logical_height = SDL_max(तथ्य->requested.logical_height, तथ्य->system_limits.min_height);

        window_आकार_changed = तथ्य->requested.logical_width != तथ्य->current.logical_width ||
                              तथ्य->requested.logical_height != तथ्य->current.logical_height ||
                              viewport_width != तथ्य->current.viewport_width ||
                              viewport_height != तथ्य->current.viewport_height;

        बफर_आकार_changed = तथ्य->current.pixel_width != old_pixel_width ||
                              तथ्य->current.pixel_height != old_pixel_height;

        अगर (window_आकार_changed || बफर_आकार_changed) {
            अगर (तथ्य->viewport) {
                wp_viewport_set_destination(तथ्य->viewport, viewport_width, viewport_height);
            } अन्यथा अगर (window->flags & SDL_WINDOW_ऊपरी_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_set_बफर_scale(तथ्य->surface, (int32_t)scale_factor);
            }

            तथ्य->current.logical_width = तथ्य->requested.logical_width;
            तथ्य->current.logical_height = तथ्य->requested.logical_height;
            तथ्य->current.viewport_width = viewport_width;
            तथ्य->current.viewport_height = viewport_height;

            तथ्य->pointer_scale.x = (द्विगुन)window_width / (द्विगुन)viewport_width;
            तथ्य->pointer_scale.y = (द्विगुन)window_height / (द्विगुन)viewport_height;
        }
    }

    अगर (तथ्य->egl_window && बफर_आकार_changed) {
        WAYLAND_wl_egl_window_resize(तथ्य->egl_window,
                                     तथ्य->current.pixel_width,
                                     तथ्य->current.pixel_height,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    अगर (!तथ्य->enable_insets && तथ्य->viewport && तथ्य->wayland_तथ्य->subcompositor && (!तथ्य->is_fullscreen || ShouldMaskFullscreen()) &&
        (viewport_width != तथ्य->current.logical_width || viewport_height != तथ्य->current.logical_height)) {
        काष्ठा wl_बफर *old_बफर = शून्य;

        अगर (!तथ्य->mask.surface) {
            तथ्य->mask.surface = wl_compositor_create_surface(तथ्य->wayland_तथ्य->compositor);
            SDL_WAYLAND_register_surface(तथ्य->mask.surface);
            wl_surface_set_user_तथ्य(तथ्य->mask.surface, तथ्य);
        }
        अगर (!तथ्य->mask.subsurface) {
            तथ्य->mask.subsurface = wl_subcompositor_get_subsurface(तथ्य->wayland_तथ्य->subcompositor, तथ्य->mask.surface, तथ्य->surface);
        }
        अगर (!तथ्य->mask.viewport) {
            तथ्य->mask.viewport = wp_viewporter_get_viewport(तथ्य->wayland_तथ्य->viewporter, तथ्य->mask.surface);
        }
        अगर (!तथ्य->mask.बफर_2 || तथ्य->mask.opaque != is_opaque) {
            old_बफर = तथ्य->mask.बफर_2;
            तथ्य->mask.opaque = is_opaque;
            तथ्य->mask.बफर_2 = Wayland_Create_Single_Pixel_बफर(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(तथ्य->mask.surface, तथ्य->mask.बफर_2, 0, 0);

        wl_subsurface_place_below(तथ्य->mask.subsurface, तथ्य->surface);
        wp_viewport_set_destination(तथ्य->mask.viewport, तथ्य->current.logical_width, तथ्य->current.logical_height);

        अगर (wl_surface_get_version(तथ्य->mask.surface) >= WL_SURFACE_DAMAGE_बफर_SINCE_VERSION) {
            wl_surface_damage_बफर(तथ्य->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } अन्यथा {
            wl_surface_damage(तथ्य->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        अगर (is_opaque) {
            SetSurfaceOpaqueRegion(तथ्य->mask.surface, तथ्य->current.logical_width, तथ्य->current.logical_height);
        } अन्यथा {
            SetSurfaceOpaqueRegion(तथ्य->mask.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        अगर (तथ्य->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            तथ्य->mask.offset_x = -(तथ्य->current.logical_width - viewport_width) / 2;
            तथ्य->mask.offset_y = -(तथ्य->current.logical_height - viewport_height) / 2;
        } अन्यथा {
            तथ्य->mask.offset_x = 0;
            तथ्य->mask.offset_y = 0;
        }

        wl_subsurface_set_position(तथ्य->mask.subsurface, तथ्य->mask.offset_x, तथ्य->mask.offset_y);
        wl_surface_commit(तथ्य->mask.surface);

        अगर (old_बफर) {
            wl_बफर_destroy(old_बफर);
        }

        तथ्य->mask.mapped = true;
    } अन्यथा अगर (तथ्य->mask.mapped) {
        wl_subsurface_set_position(तथ्य->mask.subsurface, 0, 0);
        wl_surface_attach(तथ्य->mask.surface, शून्य, 0, 0);
        wl_surface_commit(तथ्य->mask.surface);

        तथ्य->mask.offset_x = 0;
        तथ्य->mask.offset_y = 0;
        तथ्य->mask.mapped = false;
    }

    अगर (तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && तथ्य->shell_surface.xdg.surface &&
        (तथ्य->enable_insets || !तथ्य->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(window, &insets);
        स्थिर bool use_insets = (insets.बायाँ || insets.शीर्ष || insets.दायाँ || insets.bottom) &&
                                !(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, तथ्य->current.logical_width, तथ्य->current.logical_height };
        अगर (use_insets) {
            geometry.x = insets.बायाँ;
            geometry.y = insets.शीर्ष;
            geometry.w = SDL_max(geometry.w - (insets.बायाँ + insets.दायाँ), 1);
            geometry.h = SDL_max(geometry.h - (insets.शीर्ष + insets.bottom), 1);
        }
        /* An explicitly set geometry does not track the surface, so it must be kept in sync
         * once set. Otherwise this is only done when viewports aren't supported and the size
         * has changed (XXX: a hack) to avoid a potential protocol violation if a buffer with
         * an old size is committed.
         */
        अगर ((use_insets || !SDL_RectEmpty(&तथ्य->explicit_geometry) || (!तथ्य->viewport && window_आकार_changed)) &&
            !SDL_RectsEqual(&geometry, &तथ्य->explicit_geometry)) {
            xdg_surface_set_window_geometry(तथ्य->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            तथ्य->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    अगर (window_आकार_changed) {
        अगर (is_opaque) {
            SetSurfaceOpaqueRegion(तथ्य->surface, viewport_width, viewport_height);
        } अन्यथा {
            SetSurfaceOpaqueRegion(तथ्य->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        क्रम (SDL_Window *child = window->first_child; child; child = child->अग्र_sibling) {
            RepositionPopup(child, true);
        }
    }

    // Update the scale for any focused cursors.
    अगर (पूर्व_pointer_scale_x != तथ्य->pointer_scale.x || पूर्व_pointer_scale_y != तथ्य->pointer_scale.y) {
        Wayland_DisplayUpdatePointerFocusedScale(तथ्य);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    SetMinMaxDimensions(window);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    अगर (!तथ्य->scale_to_display) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window_width, window_height);
    } अन्यथा {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, तथ्य->current.pixel_width, तथ्य->current.pixel_height);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_आकार_CHANGED, तथ्य->current.pixel_width, तथ्य->current.pixel_height);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    अगर (तथ्य->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        अगर ((बफर_आकार_changed || window_आकार_changed) ||
            (!तथ्य->suspended && (window->flags & SDL_WINDOW_OCCLUDED))) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }

        अगर (तथ्य->suspended) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
        }
    }
}

अटल व्योम CommitLibdecorFrame(SDL_Window *window)
{
#अगर_घोषित HAVE_LIBDECOR_H
    SDL_Window_तथ्य *wind = window->internal;

    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        काष्ठा libdecor_state *state = libdecor_state_new(wind->current.logical_width, wind->current.logical_height);
        libdecor_frame_commit(wind->shell_surface.libdecor.frame, state, शून्य);
        libdecor_state_free(state);
    }
#पूर्ण_अगर
}

अटल व्योम pending_state_deadline_handler(व्योम *तथ्य, काष्ठा wl_callback *callback, uint32_t callback_तथ्य)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_WindowID windowID = (SDL_WindowID)(uintptr_t)तथ्य;
    SDL_Window *window = SDL_GetWindowFromID(windowID);

    अगर (window && window->internal) {
        --window->internal->pending_state_deadline_गिनती;
    }

    wl_callback_destroy(callback);
}

अटल काष्ठा wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

अटल व्योम AddPendingStateSync(SDL_Window_तथ्य *window_तथ्य_2)
{
    SDL_Video_तथ्य *video_तथ्य = window_तथ्य_2->wayland_तथ्य;
    व्योम *cb_तथ्य = (व्योम *)(uintptr_t)window_तथ्य_2->sdlwindow->id;

    ++window_तथ्य_2->pending_state_deadline_गिनती;
    काष्ठा wl_callback *cb = wl_display_sync(video_तथ्य->display);
    wl_callback_add_listener(cb, &pending_state_deadline_listener, cb_तथ्य);
}

अटल व्योम FlushPendingEvents(SDL_Window *window)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    स्थिर bool last_position_pending = window->last_position_pending;
    स्थिर bool last_आकार_pending = window->last_आकार_pending;

    जबतक (window->internal->pending_state_deadline_गिनती) {
        WAYLAND_wl_display_roundtrip(window->internal->wayland_तथ्य->display);
    }

    window->last_position_pending = last_position_pending;
    window->last_आकार_pending = last_आकार_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
व्योम Wayland_UpdateWindowPosition(SDL_Window *window)
{
    SDL_Window_तथ्य *wind = window->internal;
    SDL_Display_तथ्य *display;

    अगर (wind->outputs && wind->अंक_outputs) {
        display = wind->outputs[wind->अंक_outputs - 1];
    } अन्यथा {
        // A window may not be on any displays if minimized.
        वापस;
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
    wind->last_displayID = display->display;
    अगर (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        अगर (!wind->wayland_तथ्य->scale_to_display_enabled) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, display->logical.x, display->logical.y);
        } अन्यथा {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, wind->last_displayID, 0);
    }
}

अटल व्योम SetFullscreen(SDL_Window *window, काष्ठा wl_output *output, bool fullscreen)
{
    SDL_Window_तथ्य *wind = window->internal;

#अगर_घोषित HAVE_LIBDECOR_H
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        अगर (!wind->shell_surface.libdecor.frame) {
            वापस; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? window->fullscreen_exclusive : false;
        अगर (fullscreen) {
            libdecor_frame_set_fullscreen(wind->shell_surface.libdecor.frame, output);
        } अन्यथा {
            libdecor_frame_unset_fullscreen(wind->shell_surface.libdecor.frame);
        }
    } अन्यथा
#पूर्ण_अगर
        अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        अगर (wind->shell_surface.xdg.toplevel.xdg_toplevel == शून्य) {
            वापस; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? window->fullscreen_exclusive : false;
        अगर (fullscreen) {
            xdg_toplevel_set_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } अन्यथा {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    AddPendingStateSync(wind);
}

अटल व्योम UpdateWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    SDL_Window_तथ्य *wind = window->internal;

    wind->is_fullscreen = fullscreen;

    अगर (fullscreen) {
        अगर (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            अगर (window->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(window->current_fullscreen_mode.displayID);
                अगर (disp) {
                    wind->fullscreen_was_positioned = true;
                    SetFullscreen(window, disp->internal->output, true);
                }
            }
        }
    } अन्यथा {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        अगर ((window->flags & SDL_WINDOW_FULLSCREEN) && !window->is_hiding && !(window->flags & SDL_WINDOW_HIDDEN)) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_LEAVE, false);
            wind->fullscreen_was_positioned = false;

            /* Send a move event, in case it was deferred while the fullscreen window was moving and
             * on multiple outputs.
             */
            Wayland_UpdateWindowPosition(window);
        }
    }
}

अटल स्थिर काष्ठा wl_callback_listener surface_frame_listener;

अटल व्योम surface_frame_done(व्योम *तथ्य, काष्ठा wl_callback *cb, uint32_t समय)
{
    SDL_Window_तथ्य *wind = (SDL_Window_तथ्य *)तथ्य;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    अगर (wl_compositor_get_version(wind->wayland_तथ्य->compositor) >= WL_SURFACE_DAMAGE_बफर_SINCE_VERSION) {
        wl_surface_damage_बफर(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } अन्यथा {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        अगर (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            ConfigureWindowGeometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } अन्यथा {
        wind->resizing = false;
    }

    अगर (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        क्रम (SDL_Window *w = wind->sdlwindow->first_child; w; w = w->अग्र_sibling) {
            अगर (w->internal->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING) {
                Wayland_ShowWindow(SDL_GetVideoDevice(), w);
            } अन्यथा अगर (w->internal->reparenting_required) {
                Wayland_SetWindowParent(SDL_GetVideoDevice(), w, w->parent);
                अगर (w->flags & SDL_WINDOW_MODAL) {
                    Wayland_SetWindowModal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        अगर (wind->suspended) {
            SDL_SendWindowEvent(wind->sdlwindow, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_frame_callback = wl_surface_frame(wind->surface);
    wl_callback_add_listener(wind->surface_frame_callback, &surface_frame_listener, तथ्य);
}

अटल स्थिर काष्ठा wl_callback_listener surface_frame_listener = {
    surface_frame_done
};

अटल स्थिर काष्ठा wl_callback_listener gles_swap_frame_listener;

अटल व्योम gles_swap_frame_done(व्योम *तथ्य, काष्ठा wl_callback *cb, uint32_t समय)
{
    SDL_Window_तथ्य *wind = (SDL_Window_तथ्य *)तथ्य;
    SDL_SetAtomicInt(&wind->swap_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_swap_frame_callback = wl_surface_frame(wind->gles_swap_frame_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_add_listener(wind->gles_swap_frame_callback, &gles_swap_frame_listener, तथ्य);
}

अटल स्थिर काष्ठा wl_callback_listener gles_swap_frame_listener = {
    gles_swap_frame_done
};

अटल व्योम handle_xdg_surface_configure(व्योम *तथ्य, काष्ठा xdg_surface *xdg, uint32_t serial)
{
    SDL_Window_तथ्य *wind = (SDL_Window_तथ्य *)तथ्य;
    SDL_Window *window = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    अगर (!wind->resizing) {
        wind->pending_config_ack = false;
        ConfigureWindowGeometry(window);
        xdg_surface_ack_configure(xdg, serial);
    } अन्यथा अगर (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }

    अगर (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME;
    }
}

अटल स्थिर काष्ठा xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

अटल व्योम ApplyGeometryLimits(SDL_Window *window, पूर्णांक req_w, पूर्णांक req_h, पूर्णांक *out_w, पूर्णांक *out_h)
{
    SDL_Window_तथ्य *wind = window->internal;

    पूर्णांक w = req_w;
    पूर्णांक h = req_h;
    स्थिर भग्न aspect = (भग्न)req_w / (भग्न)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    अगर (!wind->resizing || (wind->resize_edge & WAYLAND_RESIZE_EDGE_CORNER) == WAYLAND_RESIZE_EDGE_CORNER) {
        अगर (window->min_aspect != 0.f && aspect < window->min_aspect) {
            h = SDL_max(SDL_lroundf((भग्न)req_w / window->min_aspect), 1);

            अगर (h < window->min_h) {
                w = SDL_max(SDL_lroundf((भग्न)window->min_h * window->min_aspect), 1);
            }
            अगर (window->max_h && h > window->max_h) {
                w = SDL_max(SDL_lroundf((भग्न)window->max_h * window->min_aspect), 1);
            }
        } अन्यथा अगर (window->max_aspect != 0.f && aspect > window->max_aspect) {
            w = SDL_max(SDL_lroundf((भग्न)req_h * window->max_aspect), 1);

            अगर (w < window->min_w) {
                h = SDL_max(SDL_lroundf((भग्न)window->min_w / window->max_aspect), 1);
            }
            अगर (window->max_w && w > window->max_w) {
                h = SDL_max(SDL_lroundf((भग्न)window->max_w / window->max_aspect), 1);
            }
        }
    } अन्यथा अगर (wind->resize_edge & WAYLAND_RESIZE_EDGE_LR) {
        अगर (window->min_aspect != 0.f && aspect < window->min_aspect) {
            h = SDL_max(SDL_lroundf((भग्न)req_w / window->min_aspect), 1);

            अगर (h < window->min_h) {
                w = SDL_max(SDL_lroundf((भग्न)window->min_h * window->min_aspect), 1);
            }
            अगर (window->max_h && h > window->max_h) {
                w = SDL_max(SDL_lroundf((भग्न)window->max_h * window->min_aspect), 1);
            }
        } अन्यथा अगर (window->max_aspect != 0.f && aspect > window->max_aspect) {
            h = SDL_max(SDL_lroundf((भग्न)req_w / window->max_aspect), 1);

            अगर (h < window->min_h) {
                w = SDL_max(SDL_lroundf((भग्न)window->min_h * window->max_aspect), 1);
            }
            अगर (window->max_h && h > window->max_h) {
                w = SDL_max(SDL_lroundf((भग्न)window->max_h * window->max_aspect), 1);
            }
        }
    } अन्यथा अगर (wind->resize_edge & WAYLAND_RESIZE_EDGE_TB) {
        अगर (window->min_aspect != 0.f && aspect < window->min_aspect) {
            w = SDL_max(SDL_lroundf((भग्न)req_h * window->min_aspect), 1);

            अगर (w < window->min_w) {
                h = SDL_max(SDL_lroundf((भग्न)window->min_w / window->min_aspect), 1);
            }
            अगर (window->max_w && w > window->max_w) {
                h = SDL_max(SDL_lroundf((भग्न)window->max_w / window->min_aspect), 1);
            }
        } अन्यथा अगर (window->max_aspect != 0.f && aspect > window->max_aspect) {
            w = SDL_max(SDL_lroundf((भग्न)req_h * window->max_aspect), 1);

            अगर (w < window->min_w) {
                h = SDL_max(SDL_lroundf((भग्न)window->min_w / window->max_aspect), 1);
            }
            अगर (window->max_w && w > window->max_w) {
                h = SDL_max(SDL_lroundf((भग्न)window->max_w / window->max_aspect), 1);
            }
        }
    }

    अगर (window->max_w) {
        w = SDL_min(w, window->max_w);
    }
    *out_w = SDL_max(w, window->min_w);

    अगर (window->max_h) {
        h = SDL_min(h, window->max_h);
    }
    *out_h = SDL_max(h, window->min_h);

}

अटल व्योम DetermineResizeAxis(SDL_Window_तथ्य *wind, पूर्णांक width, पूर्णांक height, bool resizing)
{
    /* Try to determine the axis along which the window is being resized.
     *
     * Every compositor is different, and some will start sending strange values once the resize
     * begins, so only the first change is safe to try and determine the resize edge.
     *
     * Some compositors don't send a configure event with the resize flag cleared when the resize ends,
     * so a reset timer is required.
     */
    अगर (resizing) {
        स्थिर Uint64 now = SDL_GetTicksNS();
        अगर (now >= wind->last_resize_event_time_ns + SDL_MS_TO_NS(500)) {
            wind->resize_edge = 0;
        }

        wind->last_resize_event_time_ns = now;

        अगर (!wind->resize_edge) {
            अगर (width != wind->last_configure.width || !height) {
                wind->resize_edge |= WAYLAND_RESIZE_EDGE_LR;
            }
            अगर (height != wind->last_configure.height || !width) {
                wind->resize_edge |= WAYLAND_RESIZE_EDGE_TB;
            }
        }
    } अन्यथा {
        wind->resize_edge = 0;
    }

    wind->resizing = resizing;
}

अटल व्योम handle_xdg_toplevel_configure(व्योम *तथ्य,
                                          काष्ठा xdg_toplevel *xdg_toplevel,
                                          int32_t width,
                                          int32_t height,
                                          काष्ठा wl_array *states)
{
    SDL_Window_तथ्य *wind = (SDL_Window_तथ्य *)तथ्य;
    SDL_Window *window = wind->sdlwindow;

    क्रमागत xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool active = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, states) {
        चयन (*state) {
        हाल XDG_TOPLEVEL_STATE_FULLSCREEN:
            fullscreen = true;
            floating = false;
            अवरोध;
        हाल XDG_TOPLEVEL_STATE_MAXIMIZED:
            maximized = true;
            floating = false;
            अवरोध;
        हाल XDG_TOPLEVEL_STATE_RESIZING:
            resizing = true;
            अवरोध;
        हाल XDG_TOPLEVEL_STATE_ACTIVATED:
            active = true;
            अवरोध;
        हाल XDG_TOPLEVEL_STATE_TILED_बायाँ:
        हाल XDG_TOPLEVEL_STATE_TILED_दायाँ:
        हाल XDG_TOPLEVEL_STATE_TILED_शीर्ष:
        हाल XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            अवरोध;
        हाल XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            अवरोध;
        हाल XDG_TOPLEVEL_STATE_CONSTRAINED_बायाँ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ;
            अवरोध;
        हाल XDG_TOPLEVEL_STATE_CONSTRAINED_दायाँ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ;
            अवरोध;
        हाल XDG_TOPLEVEL_STATE_CONSTRAINED_शीर्ष:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष;
            अवरोध;
        हाल XDG_TOPLEVEL_STATE_CONSTRAINED_BOTTOM:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
            अवरोध;
        शेष:
            अवरोध;
        }
    }

    /* Configure sizes are in window geometry space; add the border insets, if any, to get
     * the surface size. Maximized and fullscreen windows must use the configured size as-is,
     * so a change in inset applicability requires re-adopting even an unchanged size, and
     * sizes adopted from the cached window size are converted back to geometry space for
     * the last_configure store.
     */
    स्थिर bool insets_apply = wind->enable_insets && !fullscreen && !maximized;

    // When resizing, dimensions other than 0 are a maximum.
    स्थिर bool new_configure_आकार = width != wind->last_configure.width || height != wind->last_configure.height ||
                                    insets_apply != wind->last_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    अगर (insets_apply) {
        GetBorderInsets(window, &insets);
    }

    DetermineResizeAxis(wind, width, height, resizing);
    UpdateWindowFullscreen(window, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from xdg-shell, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    अगर (active || !(window->flags & SDL_WINDOW_MINIMIZED)) {
        अगर (window->flags & SDL_WINDOW_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
        SDL_SendWindowEvent(window,
                            (maximized && !fullscreen) ? SDL_EVENT_WINDOW_MAXIMIZED : SDL_EVENT_WINDOW_RESTORED,
                            0, 0);
    }

    अगर (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        अगर ((window->flags & SDL_WINDOW_RESIZABLE) || maximized) {
            अगर (!width) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                अगर (floating) {
                    width = window->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    अगर (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.width) {
                        width = SDL_min(wind->toplevel_bounds.width, width);
                    }
                } अन्यथा {
                    width = window->windowed.w;
                }

                अगर (!wind->scale_to_display) {
                    wind->requested.logical_width = width;
                } अन्यथा {
                    wind->requested.pixel_width = width;
                    width = wind->requested.logical_width = PixelToPoint(window, width);
                }
                width = SDL_max(width - (insets.बायाँ + insets.दायाँ), 1);
            } अन्यथा अगर (new_configure_आकार) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_width = width + (insets.बायाँ + insets.दायाँ);

                अगर (wind->scale_to_display) {
                    wind->requested.pixel_width = PointToPixel(window, wind->requested.logical_width);
                }
            }
            अगर (!height) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                अगर (floating) {
                    height = window->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    अगर (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.height) {
                        height = SDL_min(wind->toplevel_bounds.height, height);
                    }
                } अन्यथा {
                    height = window->windowed.h;
                }

                अगर (!wind->scale_to_display) {
                    wind->requested.logical_height = height;
                } अन्यथा {
                    wind->requested.pixel_height = height;
                    height = wind->requested.logical_height = PixelToPoint(window, height);
                }
                height = SDL_max(height - (insets.शीर्ष + insets.bottom), 1);
            } अन्यथा अगर (new_configure_आकार) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_height = height + (insets.शीर्ष + insets.bottom);

                अगर (wind->scale_to_display) {
                    wind->requested.pixel_height = PointToPixel(window, wind->requested.logical_height);
                }
            }
        } अन्यथा {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            अगर (!wind->scale_to_display) {
                width = wind->requested.logical_width = window->floating.w;
                height = wind->requested.logical_height = window->floating.h;
            } अन्यथा {
                wind->requested.pixel_width = window->floating.w;
                wind->requested.pixel_height = window->floating.h;
                width = wind->requested.logical_width = PixelToPoint(window, window->floating.w);
                height = wind->requested.logical_height = PixelToPoint(window, window->floating.h);
            }
            width = SDL_max(width - (insets.बायाँ + insets.दायाँ), 1);
            height = SDL_max(height - (insets.शीर्ष + insets.bottom), 1);
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
        अगर (floating) {
            अगर (!wind->scale_to_display) {
                ApplyGeometryLimits(window, wind->requested.logical_width, wind->requested.logical_height, &wind->requested.logical_width, &wind->requested.logical_height);
            } अन्यथा {
                ApplyGeometryLimits(window, wind->requested.pixel_width, wind->requested.pixel_height, &wind->requested.pixel_width, &wind->requested.pixel_height);

                wind->requested.logical_width = PixelToPoint(window, wind->requested.pixel_width);
                wind->requested.logical_height = PixelToPoint(window, wind->requested.pixel_height);
            }
        }
    } अन्यथा {
        // Fullscreen windows know their exact size.
        अगर (width == 0 || height == 0) {
            width = wind->requested.logical_width;
            height = wind->requested.logical_height;
        } अन्यथा {
            wind->requested.logical_width = width;
            wind->requested.logical_height = height;
        }

        अगर (wind->scale_to_display) {
            wind->requested.pixel_width = PointToPixel(window, width);
            wind->requested.pixel_height = PointToPixel(window, height);
        }
    }

    wind->last_configure.width = width;
    wind->last_configure.height = height;
    wind->last_configure.insets_apply = insets_apply;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->active = active;
    window->tiled = tiled;
}

अटल व्योम handle_xdg_toplevel_close(व्योम *तथ्य, काष्ठा xdg_toplevel *xdg_toplevel)
{
    SDL_Window_तथ्य *window = (SDL_Window_तथ्य *)तथ्य;
    SDL_SendWindowEvent(window->sdlwindow, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
}

अटल व्योम handle_xdg_toplevel_configure_bounds(व्योम *तथ्य,
                                                 काष्ठा xdg_toplevel *xdg_toplevel,
                                                 int32_t width, int32_t height)
{
    SDL_Window_तथ्य *window = (SDL_Window_तथ्य *)तथ्य;
    window->toplevel_bounds.width = width;
    window->toplevel_bounds.height = height;
}

अटल व्योम handle_xdg_toplevel_wm_capabilities(व्योम *तथ्य,
                                                काष्ठा xdg_toplevel *xdg_toplevel,
                                                काष्ठा wl_array *capabilities)
{
    SDL_Window_तथ्य *wind = (SDL_Window_तथ्य *)तथ्य;
    क्रमागत xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        चयन (*wm_cap) {
        हाल XDG_TOPLEVEL_WM_CAPABILITIES_WINDOW_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_WINDOW_MENU;
            अवरोध;
        हाल XDG_TOPLEVEL_WM_CAPABILITIES_MAXIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MAXIMIZE;
            अवरोध;
        हाल XDG_TOPLEVEL_WM_CAPABILITIES_FULLSCREEN:
            wind->wm_caps |= WAYLAND_WM_CAPS_FULLSCREEN;
            अवरोध;
        हाल XDG_TOPLEVEL_WM_CAPABILITIES_MINIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MINIMIZE;
            अवरोध;
        शेष:
            अवरोध;
        }
    }
}

अटल स्थिर काष्ठा xdg_toplevel_listener toplevel_listener_xdg = {
    handle_xdg_toplevel_configure,
    handle_xdg_toplevel_close,
    handle_xdg_toplevel_configure_bounds, // Version 4
    handle_xdg_toplevel_wm_capabilities   // Version 5
};

अटल व्योम handle_xdg_popup_configure(व्योम *तथ्य,
                                       काष्ठा xdg_popup *xdg_popup,
                                       int32_t x,
                                       int32_t y,
                                       int32_t width,
                                       int32_t height)
{
    SDL_Window_तथ्य *wind = (SDL_Window_तथ्य *)तथ्य;
    पूर्णांक offset_x = 0, offset_y = 0;

    // Adjust the position if it was offset for libdecor
    AdjustPopupOffset(wind->sdlwindow, &offset_x, &offset_y);
    x -= offset_x;
    y -= offset_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    अगर (width == 0 || height == 0) {
        width = wind->sdlwindow->floating.w;
        height = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    अगर (width != wind->last_configure.width || height != wind->last_configure.height) {
        wind->requested.logical_width = width;
        wind->requested.logical_height = height;

        अगर (wind->scale_to_display) {
            wind->requested.pixel_width = PointToPixel(wind->sdlwindow, width);
            wind->requested.pixel_height = PointToPixel(wind->sdlwindow, height);
        }
    }

    अगर (wind->scale_to_display) {
        x = PointToPixel(wind->sdlwindow->parent, x);
        y = PointToPixel(wind->sdlwindow->parent, y);
    }

    SDL_SendWindowEvent(wind->sdlwindow, SDL_EVENT_WINDOW_MOVED, x, y);

    wind->last_configure.width = width;
    wind->last_configure.height = height;

    अगर (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME;
    }
}

अटल व्योम handle_xdg_popup_done(व्योम *तथ्य, काष्ठा xdg_popup *xdg_popup)
{
    SDL_Window_तथ्य *window = (SDL_Window_तथ्य *)तथ्य;
    SDL_SendWindowEvent(window->sdlwindow, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
}

अटल व्योम handle_xdg_popup_repositioned(व्योम *तथ्य,
                                          काष्ठा xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

अटल स्थिर काष्ठा xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_done,
    handle_xdg_popup_repositioned
};

अटल व्योम handle_xdg_toplevel_decoration_configure(व्योम *तथ्य,
                                                     काष्ठा zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
                                                     uint32_t mode)
{
    SDL_Window *window = (SDL_Window *)तथ्य;
    SDL_Window_तथ्य *internal = window->internal;
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    /* If the compositor tries to force CSD anyway, bail on direct XDG support
     * and fall back to libdecor, it will handle these events from then on.
     *
     * To do this we have to fully unmap, then map with libdecor loaded.
     */
    अगर (mode == ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE) {
        अगर (window->flags & SDL_WINDOW_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            वापस;
        }
        अगर (!Wayland_LoadLibdecor(internal->wayland_तथ्य, true)) {
            // libdecor isn't available, so no borders for you... oh well
            वापस;
        }
        WAYLAND_wl_display_roundtrip(internal->wayland_तथ्य->display);

        Wayland_HideWindow(device, window);
        internal->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_ShowWindow(device, window);
    }
}

अटल स्थिर काष्ठा zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
    handle_xdg_toplevel_decoration_configure
};

#अगर_घोषित HAVE_LIBDECOR_H
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
अटल व्योम OverrideLibdecorLimits(SDL_Window *window)
{
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    अगर (!libdecor_frame_get_min_content_आकार) {
        libdecor_frame_set_min_content_आकार(window->internal->shell_surface.libdecor.frame, window->min_w, window->min_h);
    }
#या_अगर !SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
    libdecor_frame_set_min_content_आकार(window->internal->shell_surface.libdecor.frame, window->min_w, window->min_h);
#पूर्ण_अगर
}

/*
 * NOTE: Retrieves the minimum content size limits, if the function for doing so is available.
 *       On versions of libdecor that lack the minimum content size retrieval function, this
 *       function is a no-op.
 *
 *       Can be replaced with a direct call if the minimum required version of libdecor is raised
 *       to 0.1.2 or higher.
 */
अटल व्योम Libdecor_Get_Min_Content_आकार(काष्ठा libdecor_frame *frame, पूर्णांक *min_w, पूर्णांक *min_h)
{
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    अगर (libdecor_frame_get_min_content_आकार != शून्य) {
        libdecor_frame_get_min_content_आकार(frame, min_w, min_h);
    }
#या_अगर SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
    libdecor_frame_get_min_content_आकार(frame, min_w, min_h);
#पूर्ण_अगर
}

अटल व्योम decoration_frame_configure(काष्ठा libdecor_frame *frame,
                                       काष्ठा libdecor_configuration *configuration,
                                       व्योम *user_तथ्य_2)
{
    SDL_Window_तथ्य *wind = (SDL_Window_तथ्य *)user_तथ्य_2;
    SDL_Window *window = wind->sdlwindow;

    क्रमागत libdecor_window_state window_state;
    पूर्णांक width, height;

    bool active = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    अटल स्थिर क्रमागत libdecor_window_state tiled_states = (LIBDECOR_WINDOW_STATE_TILED_बायाँ | LIBDECOR_WINDOW_STATE_TILED_दायाँ |
                                                            LIBDECOR_WINDOW_STATE_TILED_शीर्ष | LIBDECOR_WINDOW_STATE_TILED_BOTTOM);

    अगर (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        Libdecor_Get_Min_Content_आकार(frame, &wind->system_limits.min_width, &wind->system_limits.min_height);
    }

    // Window State
    अगर (libdecor_configuration_get_window_state(configuration, &window_state)) {
        fullscreen = (window_state & LIBDECOR_WINDOW_STATE_FULLSCREEN) != 0;
        maximized = (window_state & LIBDECOR_WINDOW_STATE_MAXIMIZED) != 0;
        active = (window_state & LIBDECOR_WINDOW_STATE_ACTIVE) != 0;
        tiled = (window_state & tiled_states) != 0;
#अगर SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
        suspended = (window_state & LIBDECOR_WINDOW_STATE_SUSPENDED) != 0;
#पूर्ण_अगर
#अगर SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
        resizing = (window_state & LIBDECOR_WINDOW_STATE_RESIZING) != 0;

        अगर (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_बायाँ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ;
        }
        अगर (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_दायाँ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ;
        }
        अगर (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_शीर्ष) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष;
        }
        अगर (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#पूर्ण_अगर
    }
    स्थिर bool floating = !(fullscreen || maximized || tiled);

    UpdateWindowFullscreen(window, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from libdecor, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    अगर (active || !(window->flags & SDL_WINDOW_MINIMIZED)) {
        अगर (window->flags & SDL_WINDOW_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
        SDL_SendWindowEvent(window,
                            (maximized && !fullscreen) ? SDL_EVENT_WINDOW_MAXIMIZED : SDL_EVENT_WINDOW_RESTORED,
                            0, 0);
    }

    /* For fullscreen or fixed-size windows we know our size.
     * Always assume the configure is wrong.
     */
    अगर (fullscreen) {
        अगर (!libdecor_configuration_get_content_आकार(configuration, frame, &width, &height)) {
            width = wind->requested.logical_width;
            height = wind->requested.logical_height;
        } अन्यथा {
            // Fullscreen windows know their exact size.
            wind->requested.logical_width = width;
            wind->requested.logical_height = height;

            अगर (wind->scale_to_display) {
                wind->requested.pixel_width = PointToPixel(window, width);
                wind->requested.pixel_height = PointToPixel(window, height);
            }
        }
    } अन्यथा {
        अगर (!(window->flags & SDL_WINDOW_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            अगर (!wind->scale_to_display) {
                width = wind->requested.logical_width = window->floating.w;
                height = wind->requested.logical_height = window->floating.h;
            } अन्यथा {
                wind->requested.pixel_width = window->floating.w;
                wind->requested.pixel_height = window->floating.h;
                width = wind->requested.logical_width = PixelToPoint(window, window->floating.w);
                height = wind->requested.logical_height = PixelToPoint(window, window->floating.h);
            }

            OverrideLibdecorLimits(window);
        } अन्यथा {
            /* XXX: The libdecor cairo plugin sends bogus content sizes that add the
             *      height of the title bar when transitioning from a fixed-size to
             *      floating state. Ignore the sent window dimensions in this case,
             *      in favor of the cached value to avoid the window increasing in
             *      size after every state transition.
             *
             *      https://gitlab.freedesktop.org/libdecor/libdecor/-/issues/34
             */
            अगर ((floating && (!wind->floating && !(window->flags & SDL_WINDOW_BORDERLESS))) ||
                !libdecor_configuration_get_content_आकार(configuration, frame, &width, &height)) {
                width = 0;
                height = 0;
            }

            स्थिर bool new_configure_आकार = width != wind->last_configure.width || height != wind->last_configure.height;
            DetermineResizeAxis(wind, width, height, resizing);

            अगर (!width) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                अगर (floating) {
                    width = window->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    अगर (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.width) {
                        width = SDL_min(wind->toplevel_bounds.width, width);
                    }
                } अन्यथा {
                    width = window->windowed.w;
                }

                अगर (!wind->scale_to_display) {
                    wind->requested.logical_width = width;
                } अन्यथा {
                    wind->requested.pixel_width = width;
                    width = wind->requested.logical_width = PixelToPoint(window, width);
                }
            } अन्यथा {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                अगर (new_configure_आकार &&
                    !(wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME && wind->suspended != suspended)) {
                    wind->requested.logical_width = width;

                    अगर (wind->scale_to_display) {
                        wind->requested.pixel_width = PointToPixel(window, width);
                    }
                }
            }

            अगर (!height) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                अगर (floating) {
                    height = window->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    अगर (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.height) {
                        height = SDL_min(wind->toplevel_bounds.height, height);
                    }
                } अन्यथा {
                    height = window->windowed.h;
                }

                अगर (!wind->scale_to_display) {
                    wind->requested.logical_height = height;
                } अन्यथा {
                    wind->requested.pixel_height = height;
                    height = wind->requested.logical_height = PixelToPoint(window, height);
                }
            } अन्यथा {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                अगर (new_configure_आकार &&
                    !(wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME && wind->suspended != suspended)) {
                    wind->requested.logical_height = height;

                    अगर (wind->scale_to_display) {
                        wind->requested.pixel_height = PointToPixel(window, height);
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
        अगर (floating) {
            अगर (!wind->scale_to_display) {
                ApplyGeometryLimits(window, wind->requested.logical_width, wind->requested.logical_height, &wind->requested.logical_width, &wind->requested.logical_height);
            } अन्यथा {
                ApplyGeometryLimits(window, wind->requested.pixel_width, wind->requested.pixel_height, &wind->requested.pixel_width, &wind->requested.pixel_height);

                wind->requested.logical_width = PixelToPoint(window, wind->requested.pixel_width);
                wind->requested.logical_height = PixelToPoint(window, wind->requested.pixel_height);
            }
        }
    }

    // Store the new state.
    स्थिर bool started_resize = !wind->resizing && resizing;
    wind->last_configure.width = width;
    wind->last_configure.height = height;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->active = active;
    window->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#अगर SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
    क्रमागत libdecor_wm_capabilities caps;
#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    अगर (libdecor_frame_get_wm_capabilities) {
        caps = libdecor_frame_get_wm_capabilities(wind->shell_surface.libdecor.frame);
#अन्यथा
    caps = libdecor_frame_get_wm_capabilities(wind->shell_surface.libdecor.frame);
    {
#पूर्ण_अगर
        wind->wm_caps = 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_WINDOW_MENU ? WAYLAND_WM_CAPS_WINDOW_MENU : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MAXIMIZE ? WAYLAND_WM_CAPS_MAXIMIZE : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_FULLSCREEN ? WAYLAND_WM_CAPS_FULLSCREEN : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MINIMIZE ? WAYLAND_WM_CAPS_MINIMIZE : 0;
    }
#पूर्ण_अगर

    अगर (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        ConfigureWindowGeometry(window);
        काष्ठा libdecor_state *state = libdecor_state_new(wind->current.logical_width, wind->current.logical_height);
        libdecor_frame_commit(frame, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        अगर (started_resize) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }

    अगर (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME;
    }
}

अटल व्योम decoration_frame_close(काष्ठा libdecor_frame *frame, व्योम *user_तथ्य_2)
{
    SDL_SendWindowEvent(((SDL_Window_तथ्य *)user_तथ्य_2)->sdlwindow, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
}

अटल व्योम decoration_frame_commit(काष्ठा libdecor_frame *frame, व्योम *user_तथ्य_2)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_Window_तथ्य *wind = (SDL_Window_तथ्य *)user_तथ्य_2;
    अगर (!wind->suspended && wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        SDL_SendWindowEvent(wind->sdlwindow, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }
}

अटल व्योम decoration_dismiss_popup(काष्ठा libdecor_frame *frame, स्थिर अक्षर *seat_name, व्योम *user_तथ्य_2)
{
    // NOP
}

#अगर SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
अटल व्योम decoration_frame_bounds(काष्ठा libdecor_frame *frame, पूर्णांक width, पूर्णांक height, व्योम *user_तथ्य_2)
{
    SDL_Window_तथ्य *window = (SDL_Window_तथ्य *)user_तथ्य_2;
    window->toplevel_bounds.width = width;
    window->toplevel_bounds.height = height;
}
#पूर्ण_अगर

अटल काष्ठा libdecor_frame_interface libdecor_frame_interface = {
    decoration_frame_configure,
    decoration_frame_close,
    decoration_frame_commit,
    decoration_dismiss_popup,
#अगर SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
    decoration_frame_bounds
#पूर्ण_अगर
};
#पूर्ण_अगर

अटल व्योम Wayland_HandlePreferredScaleChanged(SDL_Window_तथ्य *window_तथ्य_2, द्विगुन factor)
{
    स्थिर द्विगुन old_factor = window_तथ्य_2->scale_factor;

    // Round the scale factor if viewports aren't available.
    अगर (!window_तथ्य_2->viewport) {
        factor = SDL_ceil(factor);
    }

    अगर (factor != old_factor) {
        window_तथ्य_2->scale_factor = factor;

        अगर (window_तथ्य_2->scale_to_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            अगर (window_तथ्य_2->floating) {
                /* Some compositors will send a configure event immediately after a scale event, however,
                 * this event can contain the old logical size, and should be ignored, or the window can
                 * incorrectly change size when moved between displays with differing scale factors.
                 *
                 * Store the last requested logical size as the last configure size, so a configure event
                 * with the old size will be ignored. Configure sizes are in window geometry space,
                 * so subtract any border insets.
                 */
                BorderInsets insets;
                GetBorderInsets(window_तथ्य_2->sdlwindow, &insets);
                window_तथ्य_2->last_configure.width = SDL_max(window_तथ्य_2->requested.logical_width - (insets.बायाँ + insets.दायाँ), 1);
                window_तथ्य_2->last_configure.height = SDL_max(window_तथ्य_2->requested.logical_height - (insets.शीर्ष + insets.bottom), 1);

                window_तथ्य_2->requested.logical_width = PixelToPoint(window_तथ्य_2->sdlwindow, window_तथ्य_2->requested.pixel_width);
                window_तथ्य_2->requested.logical_height = PixelToPoint(window_तथ्य_2->sdlwindow, window_तथ्य_2->requested.pixel_height);
            } अन्यथा {
                window_तथ्य_2->requested.pixel_width = PointToPixel(window_तथ्य_2->sdlwindow, window_तथ्य_2->requested.logical_width);
                window_तथ्य_2->requested.pixel_height = PointToPixel(window_तथ्य_2->sdlwindow, window_तथ्य_2->requested.logical_height);
            }
        }

        अगर (window_तथ्य_2->sdlwindow->flags & SDL_WINDOW_ऊपरी_PIXEL_DENSITY || window_तथ्य_2->scale_to_display) {
            ConfigureWindowGeometry(window_तथ्य_2->sdlwindow);
            CommitLibdecorFrame(window_तथ्य_2->sdlwindow);
        }
    }
}

अटल व्योम Wayland_MaybeUpdateScaleFactor(SDL_Window_तथ्य *window)
{
    द्विगुन factor;
    पूर्णांक i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    अगर (window->fractional_scale || wl_surface_get_version(window->surface) >= WL_SURFACE_PREFERRED_बफर_SCALE_SINCE_VERSION) {
        वापस;
    }

    अगर (window->अंक_outputs != 0) {
        // Check every display's factor, use the highest
        factor = 0.0;
        क्रम (i = 0; i < window->अंक_outputs; i++) {
            SDL_Display_तथ्य *internal = window->outputs[i];
            factor = SDL_max(factor, internal->scale_factor);
        }
    } अन्यथा {
        // All outputs removed, just fall back.
        factor = window->scale_factor;
    }

    Wayland_HandlePreferredScaleChanged(window, factor);
}

व्योम Wayland_RemoveOutputFromWindow(SDL_Window_तथ्य *window, SDL_Display_तथ्य *display_तथ्य)
{
    क्रम (पूर्णांक i = 0; i < window->अंक_outputs; i++) {
        अगर (window->outputs[i] == display_तथ्य) { // remove this one
            अगर (i == (window->अंक_outputs - 1)) {
                window->outputs[i] = शून्य;
            } अन्यथा {
                SDL_memmove(&window->outputs[i],
                            &window->outputs[i + 1],
                            माप(SDL_Display_तथ्य *) * ((window->अंक_outputs - i) - 1));
            }
            window->अंक_outputs--;
            i--;
        }
    }

    अगर (window->अंक_outputs == 0) {
        SDL_free(window->outputs);
        window->outputs = शून्य;
    } अन्यथा अगर (!window->is_fullscreen || window->अंक_outputs == 1) {
        Wayland_UpdateWindowPosition(window->sdlwindow);
        Wayland_MaybeUpdateScaleFactor(window);
    }
}

अटल व्योम handle_surface_enter(व्योम *तथ्य, काष्ठा wl_surface *surface, काष्ठा wl_output *output)
{
    SDL_Window_तथ्य *window = तथ्य;
    SDL_Display_तथ्य *internal = wl_output_get_user_तथ्य(output);
    SDL_Display_तथ्य **new_outputs;

    अगर (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        वापस;
    }

    new_outputs = SDL_realloc(window->outputs,
                              माप(SDL_Display_तथ्य *) * (window->अंक_outputs + 1));
    अगर (!new_outputs) {
        वापस;
    }
    window->outputs = new_outputs;
    window->outputs[window->अंक_outputs++] = internal;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    अगर (!window->is_fullscreen || window->अंक_outputs == 1) {
        Wayland_UpdateWindowPosition(window->sdlwindow);
        Wayland_MaybeUpdateScaleFactor(window);
    }
}

अटल व्योम handle_surface_leave(व्योम *तथ्य, काष्ठा wl_surface *surface, काष्ठा wl_output *output)
{
    SDL_Window_तथ्य *window = (SDL_Window_तथ्य *)तथ्य;

    अगर (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        वापस;
    }

    Wayland_RemoveOutputFromWindow(window, (SDL_Display_तथ्य *)wl_output_get_user_तथ्य(output));
}

अटल व्योम handle_surface_preferred_बफर_scale(व्योम *तथ्य, काष्ठा wl_surface *wl_surface, int32_t factor)
{
    SDL_Window_तथ्य *wind = तथ्य;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    अगर (!wind->fractional_scale) {
        Wayland_HandlePreferredScaleChanged(तथ्य, (द्विगुन)factor);
    }
}

अटल व्योम handle_surface_preferred_बफर_transform(व्योम *तथ्य, काष्ठा wl_surface *wl_surface, uint32_t transform)
{
    // Nothing to do here.
}

अटल स्थिर काष्ठा wl_surface_listener surface_listener = {
    handle_surface_enter,
    handle_surface_leave,
    handle_surface_preferred_बफर_scale,
    handle_surface_preferred_बफर_transform
};

अटल व्योम handle_fractional_scale_preferred(व्योम *तथ्य, काष्ठा wp_fractional_scale_v1 *wp_fractional_scale_v1, uint32_t scale)
{
    स्थिर द्विगुन factor = (द्विगुन)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_HandlePreferredScaleChanged(तथ्य, factor);
}

अटल स्थिर काष्ठा wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

अटल व्योम frog_preferred_metadata_handler(व्योम *तथ्य, काष्ठा frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
                                            uint32_t output_display_primary_red_x, uint32_t output_display_primary_red_y,
                                            uint32_t output_display_primary_green_x, uint32_t output_display_primary_green_y,
                                            uint32_t output_display_primary_blue_x, uint32_t output_display_primary_blue_y,
                                            uint32_t output_white_point_x, uint32_t output_white_point_y,
                                            uint32_t max_luminance, uint32_t min_luminance,
                                            uint32_t max_full_frame_luminance)
{
    SDL_Window_तथ्य *wind = (SDL_Window_तथ्य *)तथ्य;
    SDL_HDROutputProperties HDR;

    SDL_zero(HDR);

    चयन (transfer_function) {
    हाल FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_ST2084_PQ:
        /* ITU-R BT.2408-7 (Sept 2023) has the reference PQ white level at 203 nits,
         * while older Dolby documentation claims a reference level of 100 nits.
         *
         * Use 203 nits for now.
         */
        HDR.HDR_headroom = max_luminance / 203.0f;
        अवरोध;
    हाल FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SCRGB_LINEAR:
        HDR.HDR_headroom = max_luminance / 80.0f;
        अवरोध;
    हाल FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_UNDEFINED:
    हाल FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SRGB:
    हाल FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_GAMMA_22:
    शेष:
        HDR.HDR_headroom = 1.0f;
        अवरोध;
    }

    HDR.SDR_white_level = 1.0f;
    SDL_SetWindowHDRProperties(wind->sdlwindow, &HDR, true);
}

अटल स्थिर काष्ठा frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


अटल व्योम handle_surface_feedback_preferred_changed2(व्योम *तथ्य,
                                                       काष्ठा wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t identity_hi, uint32_t identity_lo)
{
    SDL_Window_तथ्य *wind = (SDL_Window_तथ्य *)तथ्य;
    Wayland_GetColorInfoForWindow(wind, false);
}

अटल व्योम handle_surface_feedback_preferred_changed(व्योम *तथ्य,
                                                      काष्ठा wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t identity)
{
    handle_surface_feedback_preferred_changed2(तथ्य, wp_color_management_surface_feedback_v1, 0, identity);
}

अटल स्थिर काष्ठा wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_changed,
    handle_surface_feedback_preferred_changed2
};

अटल व्योम Wayland_SetKeyboardFocus(SDL_Window *window, bool set_focus)
{
    SDL_Window *toplevel = window;

    // Find the toplevel parent
    जबतक (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    अगर (set_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    वापस true; // just succeed, the real work is done elsewhere.
}

अटल काष्ठा xdg_toplevel *GetToplevelForWindow(SDL_Window_तथ्य *wind)
{
    अगर (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#अगर_घोषित HAVE_LIBDECOR_H
        अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
            वापस libdecor_frame_get_xdg_toplevel(wind->shell_surface.libdecor.frame);
        } अन्यथा
#पूर्ण_अगर
            अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                वापस wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    वापस शून्य;
}

bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window)
{
    SDL_Window_तथ्य *child_तथ्य = window->internal;
    SDL_Window_तथ्य *parent_तथ्य = parent_window ? parent_window->internal : शून्य;

    child_तथ्य->reparenting_required = false;

    अगर (parent_तथ्य && parent_तथ्य->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        child_तथ्य->reparenting_required = true;
        वापस true;
    }

    काष्ठा xdg_toplevel *child_toplevel = GetToplevelForWindow(child_तथ्य);
    काष्ठा xdg_toplevel *parent_toplevel = GetToplevelForWindow(parent_तथ्य);

    अगर (child_toplevel) {
        xdg_toplevel_set_parent(child_toplevel, parent_toplevel);
    }

    वापस true;
}

bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
    SDL_Video_तथ्य *viddata = _this->internal;
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_Window_तथ्य *parent_तथ्य = window->parent->internal;

    अगर (parent_तथ्य->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        तथ्य->reparenting_required = true;
        वापस true;
    } अन्यथा {
        तथ्य->reparenting_required = false;
    }

    काष्ठा xdg_toplevel *toplevel = GetToplevelForWindow(तथ्य);

    अगर (toplevel) {
        अगर (viddata->xdg_wm_dialog_v1) {
            अगर (modal) {
                अगर (!तथ्य->xdg_dialog_v1) {
                    तथ्य->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_set_modal(तथ्य->xdg_dialog_v1);
            } अन्यथा अगर (तथ्य->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(तथ्य->xdg_dialog_v1);
            }
        }
    }

    वापस true;
}

अटल व्योम Wayland_RegisterToplevelForSession(SDL_Window_तथ्य *तथ्य)
{
    काष्ठा xdg_toplevel *toplevel = GetToplevelForWindow(तथ्य);
    अगर (!toplevel) {
        वापस;
    }

    स्थिर अक्षर *id = SDL_GetStringProperty(तथ्य->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_WINDOW_ID_STRING, शून्य);
    अगर (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_Video_तथ्य *viddata = viddev->internal;

        अगर (viddata->xdg_toplevel_tag_manager) {
            xdg_toplevel_tag_manager_v1_set_toplevel_tag(viddata->xdg_toplevel_tag_manager, toplevel, id);
        }

        अगर (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            अगर (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    क्रम (SDL_Window *w = viddev->windows; w; w = w->अग्र) {
                        SDL_Window_तथ्य *d = w->internal;
                        अगर (d->session_id && SDL_strcmp(d->session_id, id) == 0) {
                            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Duplicate window ID string %s found; window will not be added to session", id);
                            वापस;
                        }
                    }
                }

                तथ्य->xdg_toplevel_session = xdg_session_v1_restore_toplevel(viddata->xdg_session, toplevel, id);
                तथ्य->session_id = SDL_strdup(id);
            }
        }
    }
}

अटल व्योम Wayland_DestroyToplevelSession(SDL_Window_तथ्य *तथ्य)
{
    SDL_Video_तथ्य *viddata = तथ्य->wayland_तथ्य;

    अगर (तथ्य->xdg_toplevel_session) {
        स्थिर अक्षर *id = SDL_GetStringProperty(तथ्य->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_WINDOW_ID_STRING, शून्य);

        // If the ID string was cleared, remove the window from the session.
        अगर (!id || *id == '\0') {
            xdg_session_v1_remove_toplevel(viddata->xdg_session, तथ्य->session_id);
        }

        xdg_toplevel_session_v1_destroy(तथ्य->xdg_toplevel_session);
        तथ्य->xdg_toplevel_session = शून्य;

        SDL_free(तथ्य->session_id);
        तथ्य->session_id = शून्य;
    }
}

अटल व्योम show_hide_sync_handler(व्योम *तथ्य, काष्ठा wl_callback *callback, uint32_t callback_तथ्य)
{
    // Get the window from the ID as it may have been destroyed
    SDL_WindowID windowID = (SDL_WindowID)((uintptr_t)तथ्य);
    SDL_Window *window = SDL_GetWindowFromID(windowID);

    अगर (window && window->internal) {
        SDL_Window_तथ्य *wind = window->internal;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

अटल काष्ठा wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

अटल व्योम exported_handle_handler(व्योम *तथ्य, काष्ठा zxdg_exported_v2 *zxdg_exported_v2, स्थिर अक्षर *handle)
{
    SDL_Window_तथ्य *wind = (SDL_Window_तथ्य *)तथ्य;
    SDL_PropertiesID props = SDL_GetWindowProperties(wind->sdlwindow);

    SDL_SetStringProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

अटल काष्ठा zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

व्योम Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *c = _this->internal;
    SDL_Window_तथ्य *तथ्य = window->internal;
    SDL_PropertiesID props = SDL_GetWindowProperties(window);

    // Custom surfaces don't get toplevels and are always considered 'shown'; nothing to do here.
    अगर (तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        वापस;
    }

    /* If this is a child window, the parent *must* be in the final shown state,
     * meaning that it has received a configure event, followed by a frame callback.
     * If not, a race condition can result, with effects ranging from the child
     * window to spuriously closing to protocol errors.
     *
     * If waiting on the parent window, set the pending status and the window will
     * be shown when the parent is in the shown state.
     */
    अगर (window->parent) {
        अगर (window->parent->internal->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
            तथ्य->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING;
            वापस;
        }
    }

    // Always roundtrip to ensure there are no pending buffer attachments.
    करो {
        WAYLAND_wl_display_roundtrip(c->display);
    } जबतक (तथ्य->show_hide_sync_required);

    तथ्य->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE;

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
    wl_surface_attach(तथ्य->surface, शून्य, 0, 0);
    wl_surface_commit(तथ्य->surface);

    // Create the shell surface and map the toplevel/popup
#अगर_घोषित HAVE_LIBDECOR_H
    अगर (तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        तथ्य->shell_surface.libdecor.frame = libdecor_decorate(c->shell.libdecor,
                                                               तथ्य->surface,
                                                               &libdecor_frame_interface,
                                                               तथ्य);
        अगर (!तथ्य->shell_surface.libdecor.frame) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } अन्यथा {
            libdecor_frame_set_app_id(तथ्य->shell_surface.libdecor.frame, तथ्य->app_id);
            libdecor_frame_map(तथ्य->shell_surface.libdecor.frame);
            अगर (window->flags & SDL_WINDOW_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_frame_set_visibility(तथ्य->shell_surface.libdecor.frame, false);
            }

            अगर (c->zxdg_exporter_v2) {
                तथ्य->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, तथ्य->surface);
                zxdg_exported_v2_add_listener(तथ्य->exported, &exported_v2_listener, तथ्य);
            }

            अगर (c->xdg_toplevel_icon_manager_v1 && तथ्य->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_set_icon(_this->internal->xdg_toplevel_icon_manager_v1,
                                                      libdecor_frame_get_xdg_toplevel(तथ्य->shell_surface.libdecor.frame),
                                                      तथ्य->xdg_toplevel_icon_v1);
            }

            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, libdecor_frame_get_xdg_surface(तथ्य->shell_surface.libdecor.frame));
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_POINTER, libdecor_frame_get_xdg_toplevel(तथ्य->shell_surface.libdecor.frame));
        }
    } अन्यथा
#पूर्ण_अगर
    अगर (तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        तथ्य->shell_surface.xdg.surface = xdg_wm_base_get_xdg_surface(c->shell.xdg, तथ्य->surface);
        xdg_surface_set_user_तथ्य(तथ्य->shell_surface.xdg.surface, तथ्य);
        xdg_surface_add_listener(तथ्य->shell_surface.xdg.surface, &_xdg_surface_listener, तथ्य);
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, तथ्य->shell_surface.xdg.surface);

        अगर (तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_Window *parent = window->parent;
            SDL_Window_तथ्य *parent_तथ्य = parent->internal;
            काष्ठा xdg_surface *parent_xdg_surface = शून्य;
            पूर्णांक position_x = 0, position_y = 0;

            // Configure the popup parameters
#अगर_घोषित HAVE_LIBDECOR_H
            अगर (parent_तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                parent_xdg_surface = libdecor_frame_get_xdg_surface(parent_तथ्य->shell_surface.libdecor.frame);
            } अन्यथा
#पूर्ण_अगर
            अगर (parent_तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    parent_तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                parent_xdg_surface = parent_तथ्य->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            तथ्य->shell_surface.xdg.popup.xdg_positioner = xdg_wm_base_create_positioner(c->shell.xdg);
            xdg_positioner_set_anchor(तथ्य->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_शीर्ष_बायाँ);
            SDL_Rect parent_geometry;
            GetWindowGeometry(parent->internal, &parent_geometry);
            xdg_positioner_set_anchor_rect(तथ्य->shell_surface.xdg.popup.xdg_positioner, 0, 0, parent_geometry.w, parent_geometry.h);

            स्थिर Uint32 constraint = window->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_set_constraint_adjustment(तथ्य->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_set_gravity(तथ्य->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_दायाँ);
            xdg_positioner_set_आकार(तथ्य->shell_surface.xdg.popup.xdg_positioner, तथ्य->current.logical_width, तथ्य->current.logical_height);

            // Set the popup initial position
            position_x = window->last_position_pending ? window->pending.x : window->x;
            position_y = window->last_position_pending ? window->pending.y : window->y;
            EnsurePopupPositionIsValid(window, &position_x, &position_y);
            अगर (तथ्य->scale_to_display) {
                position_x = PixelToPoint(window->parent, position_x);
                position_y = PixelToPoint(window->parent, position_y);
            }
            AdjustPopupOffset(window, &position_x, &position_y);
            xdg_positioner_set_offset(तथ्य->shell_surface.xdg.popup.xdg_positioner, position_x, position_y);

            // Assign the popup role
            तथ्य->shell_surface.xdg.popup.xdg_popup = xdg_surface_get_popup(तथ्य->shell_surface.xdg.surface,
                                                                                parent_xdg_surface,
                                                                                तथ्य->shell_surface.xdg.popup.xdg_positioner);
            xdg_popup_add_listener(तथ्य->shell_surface.xdg.popup.xdg_popup, &_xdg_popup_listener, तथ्य);

            अगर (window->flags & SDL_WINDOW_TOOLTIP) {
                काष्ठा wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_add(region, 0, 0, 0, 0);
                wl_surface_set_निवेश_region(तथ्य->surface, region);
                wl_region_destroy(region);
            } अन्यथा अगर ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
                Wayland_SetKeyboardFocus(window, true);
            }

            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POPUP_POINTER, तथ्य->shell_surface.xdg.popup.xdg_popup);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POSITIONER_POINTER, तथ्य->shell_surface.xdg.popup.xdg_positioner);
        } अन्यथा {
            तथ्य->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(तथ्य->shell_surface.xdg.surface);
            xdg_toplevel_set_app_id(तथ्य->shell_surface.xdg.toplevel.xdg_toplevel, तथ्य->app_id);
            xdg_toplevel_add_listener(तथ्य->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, तथ्य);

            // Create the window decorations
            अगर (c->decoration_manager) {
                तथ्य->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, तथ्य->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_add_listener(तथ्य->server_decoration, &xdg_toplevel_decoration_listener, window);
                स्थिर क्रमागत zxdg_toplevel_decoration_v1_mode mode = !(window->flags & SDL_WINDOW_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_set_mode(तथ्य->server_decoration, mode);
            }

            अगर (c->zxdg_exporter_v2) {
                तथ्य->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, तथ्य->surface);
                zxdg_exported_v2_add_listener(तथ्य->exported, &exported_v2_listener, तथ्य);
            }

            अगर (c->xdg_toplevel_icon_manager_v1 && तथ्य->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_set_icon(_this->internal->xdg_toplevel_icon_manager_v1,
                                                      तथ्य->shell_surface.xdg.toplevel.xdg_toplevel,
                                                      तथ्य->xdg_toplevel_icon_v1);
            }

            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_POINTER, तथ्य->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    // Restore state that was set prior to this call
    Wayland_RegisterToplevelForSession(तथ्य);
    Wayland_SetWindowParent(_this, window, window->parent);

    अगर (window->flags & SDL_WINDOW_MODAL) {
        Wayland_SetWindowModal(_this, window, true);
    }

    Wayland_SetWindowTitle(_this, window);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#अगर_घोषित HAVE_LIBDECOR_H
    अगर (तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        अगर (तथ्य->shell_surface.libdecor.frame) {
            जबतक (तथ्य->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
                अगर (libdecor_dispatch(c->shell.libdecor, -1) < 0) {
                    अगर (!Wayland_HandleDisplayDisconnected(_this)) {
                        वापस;
                    }
                }
                अगर (WAYLAND_wl_display_dispatch_pending(c->display) < 0) {
                    अगर (!Wayland_HandleDisplayDisconnected(_this)) {
                        वापस;
                    }
                }
            }
        }
    } अन्यथा
#पूर्ण_अगर
        अगर (तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP || तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Unlike libdecor we need to call this explicitly to prevent a deadlock.
         * libdecor will call this as part of their configure event!
         * -flibit
         */
        wl_surface_commit(तथ्य->surface);
        अगर (तथ्य->shell_surface.xdg.surface) {
            जबतक (तथ्य->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
                अगर (WAYLAND_wl_display_dispatch(c->display) < 0) {
                    अगर (!Wayland_HandleDisplayDisconnected(_this)) {
                        वापस;
                    }
                }
            }
        }
    } अन्यथा {
        // Nothing to see here, just commit.
        wl_surface_commit(तथ्य->surface);
    }

    // Make sure the window can't be resized to 0, or it can be spuriously closed by the window manager.
    तथ्य->system_limits.min_width = SDL_max(तथ्य->system_limits.min_width, 1);
    तथ्य->system_limits.min_height = SDL_max(तथ्य->system_limits.min_height, 1);

    /* Unlike the rest of window state we have to set this _after_ flushing the
     * display, because we need to create the decorations before possibly hiding
     * them immediately afterward.
     */
#अगर_घोषित HAVE_LIBDECOR_H
    अगर (तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        अगर (window->windowed.w < तथ्य->system_limits.min_width ||
            window->windowed.h < तथ्य->system_limits.min_height) {

            // Warn if the window frame will be larger than the content surface.
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "Window dimensions (%i, %i) are smaller than the system enforced minimum (%i, %i); window borders will be larger than the content surface.",
                        window->windowed.w, window->windowed.h, तथ्य->system_limits.min_width, तथ्य->system_limits.min_height);

            तथ्य->current.logical_width = SDL_max(window->windowed.w, तथ्य->system_limits.min_width);
            तथ्य->current.logical_height = SDL_max(window->windowed.h, तथ्य->system_limits.min_height);
            CommitLibdecorFrame(window);
        }
    }
#पूर्ण_अगर
    Wayland_SetWindowResizable(_this, window, !!(window->flags & SDL_WINDOW_RESIZABLE));

    // We're finally done putting the window together, raise if possible
    अगर (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true)) {
        /* if the process was passed an activation token, use it when showing
         * the initial window.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        स्थिर अक्षर *activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
        अगर (activation_token) {
            xdg_activation_v1_activate(c->activation_manager,
                                       activation_token,
                                       तथ्य->surface);

            // Clear this variable, per the protocol's request
            SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
        } अन्यथा {
            // Try to generate an activation token for this window.
            Wayland_RaiseWindow(_this, window);
        }
    } अन्यथा {
        // Clear the ignored activation token, as it won't be used.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    }

    // No frame callback on an external surface, as it may already have one attached.
    अगर (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        तथ्य->surface_frame_callback = wl_surface_frame(तथ्य->surface);
        wl_callback_add_listener(तथ्य->surface_frame_callback, &surface_frame_listener, तथ्य);
    }

    तथ्य->show_hide_sync_required = true;
    काष्ठा wl_callback *cb = wl_display_sync(_this->internal->display);
    wl_callback_add_listener(cb, &show_hide_sync_listener, (व्योम *)((uintptr_t)window->id));

    तथ्य->showing_window = true;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    तथ्य->showing_window = false;

    // Send an exposure event to signal that the client should draw.
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
}

अटल व्योम Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_Window *popup)
{
    SDL_Window_तथ्य *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    अगर (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_WINDOW)) {
        वापस;
    }
    popupdata = popup->internal;
    अगर (!popupdata) {
        वापस;
    }

    // This may already be freed by a parent popup!
    अगर (popupdata->shell_surface.xdg.popup.xdg_popup == शून्य) {
        वापस;
    }

    अगर ((popup->flags & SDL_WINDOW_POPUP_MENU) && !(popup->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        स्थिर bool set_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_SetKeyboardFocus(new_focus, set_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = शून्य;
    popupdata->shell_surface.xdg.popup.xdg_positioner = शून्य;

    SDL_PropertiesID props = SDL_GetWindowProperties(popup);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POPUP_POINTER, शून्य);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POSITIONER_POINTER, शून्य);
}

व्योम Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    SDL_Window_तथ्य *wind = window->internal;
    SDL_PropertiesID props = SDL_GetWindowProperties(window);

    // Custom surfaces have nothing to destroy and are always considered to be 'shown'; nothing to do here.
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        वापस;
    }

    /* The window was shown, but the sync point hasn't yet been reached.
     * Pump events to avoid a possible protocol violation.
     */
    अगर (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(तथ्य->display);
    }

    wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_HIDDEN;

    अगर (wind->surface_frame_callback) {
        wl_callback_destroy(wind->surface_frame_callback);
        wind->surface_frame_callback = शून्य;
    }

    अगर (wind->server_decoration) {
        zxdg_toplevel_decoration_v1_destroy(wind->server_decoration);
        wind->server_decoration = शून्य;
    }

    // Clean up the export handle.
    अगर (wind->exported) {
        zxdg_exported_v2_destroy(wind->exported);
        wind->exported = शून्य;

        SDL_SetStringProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, शून्य);
    }

    अगर (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = शून्य;
    }

#अगर_घोषित HAVE_LIBDECOR_H
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        अगर (wind->shell_surface.libdecor.frame) {
            libdecor_frame_unref(wind->shell_surface.libdecor.frame);

            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, शून्य);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_POINTER, शून्य);
        }
    } अन्यथा
#पूर्ण_अगर
    {
        अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, window);
        } अन्यथा अगर (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_POINTER, शून्य);
        }

        अगर (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, शून्य);
        }
    }

    // Attach a null buffer to unmap the surface.
    अगर (wind->mask.surface) {
        wl_surface_attach(wind->mask.surface, शून्य, 0, 0);
        wl_surface_commit(wind->mask.surface);
    }
    wl_surface_attach(wind->surface, शून्य, 0, 0);
    wl_surface_commit(wind->surface);

    // Need to destroy the session object after unmapping the window, or the state may not be saved.
    Wayland_DestroyToplevelSession(wind);

    SDL_zero(wind->shell_surface);
    SDL_zero(wind->explicit_geometry);
    wind->show_hide_sync_required = true;
    काष्ठा wl_callback *cb = wl_display_sync(_this->internal->display);
    wl_callback_add_listener(cb, &show_hide_sync_listener, (व्योम *)((uintptr_t)window->id));
}

अटल व्योम handle_xdg_activation_done(व्योम *तथ्य,
                                       काष्ठा xdg_activation_token_v1 *xdg_activation_token_v1,
                                       स्थिर अक्षर *token)
{
    SDL_Window_तथ्य *window = तथ्य;
    अगर (xdg_activation_token_v1 == window->activation_token) {
        xdg_activation_v1_activate(window->wayland_तथ्य->activation_manager,
                                   token,
                                   window->surface);
        xdg_activation_token_v1_destroy(window->activation_token);
        window->activation_token = शून्य;
    }
}

अटल स्थिर काष्ठा xdg_activation_token_v1_listener xdg_activation_listener = {
    handle_xdg_activation_done
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
अटल व्योम Wayland_activate_window(SDL_Video_तथ्य *तथ्य, SDL_Window_तथ्य *target_wind, bool set_serial)
{
    SDL_WaylandSeat *seat = तथ्य->last_implicit_grab_seat;
    SDL_Window_तथ्य *focus = शून्य;

    अगर (seat) {
        focus = seat->keyboard.focus;
        अगर (!focus) {
            focus = seat->pointer.focus;
        }
    }

    काष्ठा wl_surface *requesting_surface = focus ? focus->surface : शून्य;

    अगर (तथ्य->activation_manager) {
        अगर (target_wind->activation_token) {
            // We're about to overwrite this with a new request
            xdg_activation_token_v1_destroy(target_wind->activation_token);
        }

        target_wind->activation_token = xdg_activation_v1_get_activation_token(तथ्य->activation_manager);
        xdg_activation_token_v1_add_listener(target_wind->activation_token,
                                             &xdg_activation_listener,
                                             target_wind);

        /* Note that we are not setting the app_id here.
         *
         * Hypothetically we could set the app_id from data->classname, but
         * that part of the API is for _external_ programs, not ourselves.
         *
         * -flibit
         */
        अगर (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_set_surface(target_wind->activation_token, requesting_surface);
        }
        अगर (set_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_set_serial(target_wind->activation_token, seat->last_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(target_wind->activation_token);
    }
}

व्योम Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *viddata = _this->internal;
    SDL_Window_तथ्य *wind = window->internal;

    अगर (viddata->activation_manager) {
        /* Check for an activation token, in case the window is being
         * raised in response to a system notification.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        स्थिर अक्षर *activation_token = SDL_GetNotificationActivationToken();
        अगर (activation_token) {
            xdg_activation_v1_activate(viddata->activation_manager,
                                       activation_token,
                                       wind->surface);
            वापस;
        }
    }

    // No token? Try to activate the window via an event serial.
    Wayland_activate_window(_this->internal, window->internal, true);
}

bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    /* Not setting the serial will specify 'urgency' without switching focus as per
     * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
     */
    Wayland_activate_window(_this->internal, window->internal, false);
    वापस true;
}

SDL_Fullscreen_परिणाम Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_Window_तथ्य *wind = window->internal;
    काष्ठा wl_output *output = display->internal->output;

    // Custom surfaces have no toplevel to make fullscreen.
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        वापस SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    अगर (wind->showing_window && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        वापस SDL_FULLSCREEN_SUCCEEDED;
    }

    अगर (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->internal->display);
    }

    // Flushing old events pending a new one, ignore this request.
    अगर (wind->drop_fullscreen_requests) {
        वापस SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_requests = true;
    FlushPendingEvents(window);
    wind->drop_fullscreen_requests = false;

    // Nothing to do if the window is not fullscreen, and this isn't an explicit enter request.
    अगर (!wind->is_fullscreen) {
        अगर (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
            // Request was out of date; signal the video core not to update any state.
            वापस SDL_FULLSCREEN_PENDING;
        } अन्यथा अगर (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
            // Already not fullscreen; nothing to do.
            वापस SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    // Don't send redundant fullscreen set/unset events.
    अगर (!!fullscreen != wind->is_fullscreen) {
        wind->fullscreen_was_positioned = !!fullscreen;

        /* Only use the specified output if an exclusive mode is being used, or a position was explicitly requested
         * before entering fullscreen desktop. Otherwise, let the compositor handle placement, as it has more
         * information about where the window is and where it should go, particularly if fullscreen is being requested
         * before the window is mapped, or the window spans multiple outputs.
         */
        अगर (!window->fullscreen_exclusive) {
            अगर (window->undefined_x || window->undefined_y ||
                (wind->अंक_outputs && !window->last_position_pending)) {
                output = शून्य;
            }
        }

        // Commit to set any pending size or limit data.
        अगर (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        SetFullscreen(window, output, !!fullscreen);
    } अन्यथा अगर (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        अगर (wind->last_displayID != display->id) {
            wind->fullscreen_was_positioned = true;
            SetFullscreen(window, output, true);
        } अन्यथा {
            ConfigureWindowGeometry(window);
            CommitLibdecorFrame(window);

            वापस SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    वापस SDL_FULLSCREEN_PENDING;
}

व्योम Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *wind = window->internal;

    // Drop restore requests when showing the window.
    अगर (wind->showing_window) {
        वापस;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    अगर (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) &&
        !wind->pending_state_deadline_गिनती) {
        वापस;
    }

#अगर_घोषित HAVE_LIBDECOR_H
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        अगर (!wind->shell_surface.libdecor.frame) {
            वापस; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_frame_unset_maximized(wind->shell_surface.libdecor.frame);
        AddPendingStateSync(wind);
    } अन्यथा
#पूर्ण_अगर
        // Note that xdg-shell does NOT provide a way to unset minimize!
        अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            अगर (wind->shell_surface.xdg.toplevel.xdg_toplevel == शून्य) {
                वापस; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            AddPendingStateSync(wind);
        }
}

व्योम Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
{
    SDL_Window_तथ्य *wind = window->internal;
    स्थिर SDL_Video_तथ्य *viddata = (स्थिर SDL_Video_तथ्य *)_this->internal;

#अगर_घोषित HAVE_LIBDECOR_H
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        अगर (wind->shell_surface.libdecor.frame) {
            libdecor_frame_set_visibility(wind->shell_surface.libdecor.frame, bordered);
        }
    } अन्यथा
#पूर्ण_अगर
        अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        अगर ((viddata->decoration_manager) && (wind->server_decoration)) {
            स्थिर क्रमागत zxdg_toplevel_decoration_v1_mode mode = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_set_mode(wind->server_decoration, mode);
        }
    }
}

व्योम Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_Window_तथ्य *wind = window->internal;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    SetMinMaxDimensions(window);
    CommitLibdecorFrame(window);

    अगर (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        wind->pending_state_commit = true;
    }
}

व्योम Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *wind = window->internal;

    अगर (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->internal->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    अगर (!(window->flags & SDL_WINDOW_FULLSCREEN) && (window->flags & SDL_WINDOW_MAXIMIZED) &&
        !wind->pending_state_deadline_गिनती) {
        वापस;
    }

#अगर_घोषित HAVE_LIBDECOR_H
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        अगर (!wind->shell_surface.libdecor.frame) {
            वापस; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        अगर (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_frame_set_maximized(wind->shell_surface.libdecor.frame);
        AddPendingStateSync(wind);
    } अन्यथा
#पूर्ण_अगर
        अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        अगर (wind->shell_surface.xdg.toplevel.xdg_toplevel == शून्य) {
            वापस; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        अगर (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_set_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        AddPendingStateSync(wind);
    }
}

व्योम Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *wind = window->internal;

    अगर (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        वापस;
    }

#अगर_घोषित HAVE_LIBDECOR_H
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        अगर (!wind->shell_surface.libdecor.frame) {
            वापस; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_frame_set_minimized(wind->shell_surface.libdecor.frame);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
    } अन्यथा
#पूर्ण_अगर
        अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        अगर (wind->shell_surface.xdg.toplevel.xdg_toplevel == शून्य) {
            वापस; // Can't do anything yet, wait for ShowWindow
        }
        xdg_toplevel_set_minimized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
    }
}

bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

    /* This may look suspiciously like SetWindowGrab, despite SetMouseRect not
     * implicitly doing a grab. And you're right! Wayland doesn't let us mess
     * around with mouse focus whatsoever, so it just happens to be that the
     * work that we can do in these two functions ends up being the same.
     *
     * Just know that this call lets you confine with a rect, SetWindowGrab
     * lets you confine without a rect.
     */
    अगर (!तथ्य->pointer_constraints) {
        वापस SDL_SetError("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_DisplayUpdatePointerGrabs(तथ्य, window->internal);
    वापस true;
}

bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    अगर (!तथ्य->pointer_constraints) {
        वापस SDL_SetError("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_DisplayUpdatePointerGrabs(तथ्य, window->internal);
    वापस true;
}

bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    अगर (!तथ्य->कुंजी_inhibitor_manager) {
        वापस SDL_SetError("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(तथ्य, window->internal);
    वापस true;
}

bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    // Don't try to reconfigure mapped windows, unless they are custom or external.
    अगर (तथ्य->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN &&
        तथ्य->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        // Window is already mapped; abort.
        वापस false;
    }

    /* The caller guarantees that only one of the GL or Vulkan flags will be set.
     * Note that Vulkan doesn't require any specific configuration, so only EGL
     * objects are added and removed as required.
     */
    अगर (flags & SDL_WINDOW_OPENGL) {
        अगर (!तथ्य->egl_window) {
            तथ्य->egl_window = WAYLAND_wl_egl_window_create(तथ्य->surface, तथ्य->current.pixel_width, तथ्य->current.pixel_height);
        }

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
        तथ्य->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)तथ्य->egl_window);

        अगर (तथ्य->egl_surface == EGL_NO_SURFACE) {
            वापस false; // SDL_EGL_CreateSurface should have set the error.
        }
#पूर्ण_अगर

        अगर (!तथ्य->gles_swap_frame_event_queue) {
            तथ्य->gles_swap_frame_event_queue = WAYLAND_wl_display_create_queue(तथ्य->wayland_तथ्य->display);
            तथ्य->gles_swap_frame_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(तथ्य->surface);
            WAYLAND_wl_proxy_set_queue((काष्ठा wl_proxy *)तथ्य->gles_swap_frame_surface_wrapper, तथ्य->gles_swap_frame_event_queue);
            तथ्य->gles_swap_frame_callback = wl_surface_frame(तथ्य->gles_swap_frame_surface_wrapper);
            wl_callback_add_listener(तथ्य->gles_swap_frame_callback, &gles_swap_frame_listener, तथ्य);
        }
    } अन्यथा {
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
        अगर (तथ्य->egl_surface) {
            SDL_EGL_DestroySurface(_this, तथ्य->egl_surface);
            तथ्य->egl_surface = EGL_NO_SURFACE;
        }
#पूर्ण_अगर

        अगर (तथ्य->egl_window) {
            WAYLAND_wl_egl_window_destroy(तथ्य->egl_window);
            तथ्य->egl_window = शून्य;
        }

        अगर (तथ्य->gles_swap_frame_callback) {
            wl_callback_destroy(तथ्य->gles_swap_frame_callback);
            तथ्य->gles_swap_frame_callback = शून्य;
        }

        अगर (तथ्य->gles_swap_frame_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(तथ्य->gles_swap_frame_surface_wrapper);
            तथ्य->gles_swap_frame_surface_wrapper = शून्य;
        }

        अगर (तथ्य->gles_swap_frame_event_queue) {
            WAYLAND_wl_event_queue_destroy(तथ्य->gles_swap_frame_event_queue);
            तथ्य->gles_swap_frame_event_queue = शून्य;
        }
    }

    वापस true;
}

bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_Window_तथ्य *तथ्य;
    SDL_Video_तथ्य *c = _this->internal;
    काष्ठा wl_surface *external_surface = (काष्ठा wl_surface *)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_WL_SURFACE_POINTER,
                                                                               (काष्ठा wl_surface *)SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", शून्य));
    स्थिर bool custom_surface_role = (external_surface != शून्य) || SDL_GetBooleanProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    स्थिर bool create_egl_window = !!(window->flags & SDL_WINDOW_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_CREATE_EGL_WINDOW_BOOLEAN, false);

    तथ्य = SDL_calloc(1, माप(*तथ्य));
    अगर (!तथ्य) {
        वापस false;
    }

    window->internal = तथ्य;
    तथ्य->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    अगर (window->x == SDL_WINDOWPOS_UNDEFINED) {
        window->x = 0;
    }
    अगर (window->y == SDL_WINDOWPOS_UNDEFINED) {
        window->y = 0;
    }

    तथ्य->wayland_तथ्य = c;
    तथ्य->sdlwindow = window;

    // Default to all capabilities
    तथ्य->wm_caps = WAYLAND_WM_CAPS_ALL;

    तथ्य->scale_factor = 1.0;

    अगर (SDL_WINDOW_IS_POPUP(window)) {
        तथ्य->scale_to_display = window->parent->internal->scale_to_display;
        तथ्य->scale_factor = window->parent->internal->scale_factor;
        EnsurePopupPositionIsValid(window, &window->x, &window->y);
    } अन्यथा {
        क्रम (पूर्णांक i = 0; i < _this->अंक_displays; i++) {
            तथ्य->scale_factor = SDL_max(तथ्य->scale_factor, _this->displays[i]->internal->scale_factor);
        }
    }

    तथ्य->outputs = शून्य;
    तथ्य->अंक_outputs = 0;
    तथ्य->scale_to_display = c->scale_to_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    तथ्य->app_id = SDL_strdup(SDL_GetAppID());

    अगर (!तथ्य->scale_to_display) {
        तथ्य->requested.logical_width = window->floating.w;
        तथ्य->requested.logical_height = window->floating.h;
    } अन्यथा {
        तथ्य->requested.logical_width = PixelToPoint(window, window->floating.w);
        तथ्य->requested.logical_height = PixelToPoint(window, window->floating.h);
        तथ्य->requested.pixel_width = window->floating.w;
        तथ्य->requested.pixel_height = window->floating.h;
    }

    अगर (!external_surface) {
        तथ्य->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_add_listener(तथ्य->surface, &surface_listener, तथ्य);
        wl_surface_set_user_तथ्य(तथ्य->surface, तथ्य);
        SDL_WAYLAND_register_surface(तथ्य->surface);
    } अन्यथा {
        window->flags |= SDL_WINDOW_EXTERNAL;
        तथ्य->surface = external_surface;

        /* External surfaces are registered by being put in a list, as changing tags or userdata
         * can cause problems with external toolkits.
         */
        Wayland_Add_Window_तथ्य_To_External_List(तथ्य);
    }

    /* Always attach a viewport and fractional scale manager if available and the surface is not custom/external,
     * or the custom/external surface was explicitly flagged as high pixel density aware, which signals that the
     * application wants SDL to handle scaling.
     */
    अगर (!custom_surface_role || (window->flags & SDL_WINDOW_ऊपरी_PIXEL_DENSITY)) {
        अगर (c->viewporter) {
            तथ्य->viewport = wp_viewporter_get_viewport(c->viewporter, तथ्य->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_set_source(तथ्य->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        अगर (c->fractional_scale_manager) {
            तथ्य->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, तथ्य->surface);
            wp_fractional_scale_v1_add_listener(तथ्य->fractional_scale, &fractional_scale_listener, तथ्य);
        }
    }

    अगर (!custom_surface_role) {
        अगर (c->wp_color_manager_v1) {
            तथ्य->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, तथ्य->surface);
            wp_color_management_surface_feedback_v1_add_listener(तथ्य->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, तथ्य);
            Wayland_GetColorInfoForWindow(तथ्य, true);
        } अन्यथा अगर (c->frog_color_management_factory_v1) {
            तथ्य->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, तथ्य->surface);
            frog_color_managed_surface_add_listener(तथ्य->frog_color_managed_surface, &frog_surface_listener, तथ्य);
        }

        अगर (c->wp_alpha_modifier_v1) {
            तथ्य->wp_alpha_modifier_surface_v1 = wp_alpha_modifier_v1_get_surface(c->wp_alpha_modifier_v1, तथ्य->surface);
            wp_alpha_modifier_surface_v1_set_multiplier(तथ्य->wp_alpha_modifier_surface_v1, SDL_MAX_UINT32);
        }
    }

    // Must be called before EGL configuration to set the drawable backbuffer size.
    ConfigureWindowGeometry(window);

    /* Fire a callback when the compositor wants a new frame rendered.
     * Right now this only matters for OpenGL; we use this callback to add a
     * wait timeout that avoids getting deadlocked by the compositor when the
     * window isn't visible.
     */
    अगर (window->flags & SDL_WINDOW_OPENGL) {
        तथ्य->gles_swap_frame_event_queue = WAYLAND_wl_display_create_queue(तथ्य->wayland_तथ्य->display);
        तथ्य->gles_swap_frame_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(तथ्य->surface);
        WAYLAND_wl_proxy_set_queue((काष्ठा wl_proxy *)तथ्य->gles_swap_frame_surface_wrapper, तथ्य->gles_swap_frame_event_queue);
        तथ्य->gles_swap_frame_callback = wl_surface_frame(तथ्य->gles_swap_frame_surface_wrapper);
        wl_callback_add_listener(तथ्य->gles_swap_frame_callback, &gles_swap_frame_listener, तथ्य);
    }

    अगर (window->flags & SDL_WINDOW_TRANSPARENT) {
        अगर (_this->gl_config.alpha_आकार == 0) {
            _this->gl_config.alpha_आकार = 8;
        }
    }

    अगर (create_egl_window) {
        तथ्य->egl_window = WAYLAND_wl_egl_window_create(तथ्य->surface, तथ्य->current.pixel_width, तथ्य->current.pixel_height);
    }

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    अगर (window->flags & SDL_WINDOW_OPENGL) {
        // Create the GLES window surface
        तथ्य->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)तथ्य->egl_window);

        अगर (तथ्य->egl_surface == EGL_NO_SURFACE) {
            वापस false; // SDL_EGL_CreateSurface should have set error
        }
    }
#पूर्ण_अगर

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    अगर (!custom_surface_role) {
#अगर_घोषित HAVE_LIBDECOR_H
        अगर (c->shell.libdecor && !SDL_WINDOW_IS_POPUP(window)) {
            तथ्य->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } अन्यथा
#पूर्ण_अगर
            अगर (c->shell.xdg) {
            अगर (SDL_WINDOW_IS_POPUP(window)) {
                तथ्य->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP;
            } अन्यथा {
                तथ्य->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL;
            }
        } // All other cases will be WAYLAND_SURFACE_UNKNOWN
    } अन्यथा {
        // Roleless and external surfaces are always considered to be in the shown state by the backend.
        तथ्य->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_CUSTOM;
        तथ्य->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_SHOWN;

        // External windows are presumed to be shown.
        अगर (window->flags & SDL_WINDOW_EXTERNAL) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        }
    }

    अगर (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_बफर, false)) {
        तथ्य->double_बफर = true;
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, तथ्य->wayland_तथ्य->display);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, तथ्य->surface);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_VIEWPORT_POINTER, तथ्य->viewport);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_EGL_WINDOW_POINTER, तथ्य->egl_window);
    अगर (तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || तथ्य->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        स्थिर अक्षर *window_id = SDL_GetStringProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_WINDOW_ID_STRING, शून्य);
        अगर (window_id && *window_id != '\0') {
            SDL_SetStringProperty(props, SDL_PROP_WINDOW_WAYLAND_WINDOW_ID_STRING, window_id);
        }
    }

    तथ्य->hit_test_परिणाम = SDL_HITTEST_NORMAL;

    वापस true;
}

व्योम Wayland_Set_Window_Minimum_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    window->internal->limits_changed = true;
}

व्योम Wayland_Set_Window_Maximum_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    window->internal->limits_changed = true;
}

व्योम Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    window->internal->limits_changed = true;
}

bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *wind = window->internal;

    // Only popup windows can be positioned relative to the parent.
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        अगर (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_version(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_VERSION) {
            वापस SDL_Unsupported();
        }

        RepositionPopup(window, false);
        वापस true;
    } अन्यथा अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(window);

        अगर (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplayForFullscreenWindow(window);
            अगर (display && wind->last_displayID != display->id) {
                काष्ठा wl_output *output = display->internal->output;
                SetFullscreen(window, output, true);

                वापस true;
            }
        }
    }
    वापस SDL_SetError("wayland cannot position non-popup windows");
}

व्योम Wayland_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *wind = window->internal;

    /* Flush any pending state operations, as fullscreen windows do not get
     * explicitly resized, not strictly obeying the size of a maximized window
     * is a protocol violation, and pending restore events might result in a
     * configure event overwriting the requested size.
     *
     * Calling this on a custom surface is informative, so the size must
     * always be passed through.
     */
    FlushPendingEvents(window);

    स्थिर bool maximized = (window->flags & SDL_WINDOW_MAXIMIZED) != 0;
    स्थिर bool resizable_state = !(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN));

    /* Maximized and fullscreen windows don't get resized, and the new size is ignored
     * if this is just to recalculate the min/max or aspect limits on a tiled window.
     *
     * Some compositors will mark tiled windows as maximized. In these cases, the content
     * size is recalculated, but window size itself is left alone, as the spec states that
     * the configure size of a maximized window must be obeyed.
     */
    अगर (resizable_state || (window->tiled && !wind->limits_changed) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        अगर (!maximized) {
            अगर (!wind->scale_to_display) {
                wind->requested.logical_width = window->pending.w;
                wind->requested.logical_height = window->pending.h;
            } अन्यथा {
                wind->requested.logical_width = PixelToPoint(window, window->pending.w);
                wind->requested.logical_height = PixelToPoint(window, window->pending.h);
                wind->requested.pixel_width = window->pending.w;
                wind->requested.pixel_height = window->pending.h;
            }
        }

        /* If a non-resizable window somehow wound up in the tiled state, store the new
         * size in the floating parameters so the size will be preserved for future
         * configure events.
         *
         * This shouldn't happen, but apparently it can on at least one compositor...
         */
        अगर (window->tiled && !(window->flags & SDL_WINDOW_RESIZABLE)) {
            window->floating.w = window->pending.w;
            window->floating.h = window->pending.h;
        }
    } अन्यथा {
        // Can't resize the window.
        window->last_आकार_pending = false;
    }

    wind->limits_changed = false;
    अगर (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    ConfigureWindowGeometry(window);
    CommitLibdecorFrame(window);
}

व्योम Wayland_Get_Window_आकार_In_Pixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *w, पूर्णांक *h)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    *w = तथ्य->current.pixel_width;
    *h = तथ्य->current.pixel_height;
}

भग्न Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *wind = window->internal;

    अगर (window->flags & SDL_WINDOW_ऊपरी_PIXEL_DENSITY || wind->scale_to_display || wind->fullscreen_exclusive) {
        वापस (भग्न)wind->scale_factor;
    }

    वापस 1.0f;
}

SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *wind = window->internal;

    अगर (wind) {
        वापस wind->last_displayID;
    }

    वापस 0;
}

bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, भग्न opacity)
{
    SDL_Window_तथ्य *wind = window->internal;

    अगर (wind->wp_alpha_modifier_surface_v1) {
        स्थिर bool is_opaque = !(window->flags & SDL_WINDOW_TRANSPARENT) && opacity == 1.0f;

        अगर (wind->mask.mapped && wind->mask.opaque != is_opaque) {
            काष्ठा wl_बफर *old_बफर = wind->mask.बफर_2;
            wind->mask.opaque = is_opaque;
            wind->mask.बफर_2 = Wayland_Create_Single_Pixel_बफर(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->mask.surface, wind->mask.बफर_2, 0, 0);
            अगर (wl_surface_get_version(wind->mask.surface) >= WL_SURFACE_DAMAGE_बफर_SINCE_VERSION) {
                wl_surface_damage_बफर(wind->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } अन्यथा {
                wl_surface_damage(wind->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            अगर (is_opaque) {
                SetSurfaceOpaqueRegion(wind->mask.surface, wind->current.logical_width, wind->current.logical_height);
            } अन्यथा {
                SetSurfaceOpaqueRegion(wind->mask.surface, 0, 0);
            }

            wl_surface_commit(wind->mask.surface);

            अगर (old_बफर) {
                wl_बफर_destroy(old_बफर);
            }
        }

        अगर (is_opaque) {
            SetSurfaceOpaqueRegion(wind->surface, wind->current.viewport_width, wind->current.viewport_height);
        } अन्यथा {
            SetSurfaceOpaqueRegion(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_set_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((द्विगुन)SDL_MAX_UINT32 * (द्विगुन)opacity));

        वापस true;
    }

    वापस SDL_SetError("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

व्योम Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *wind = window->internal;
    स्थिर अक्षर *title = window->title ? window->title : "";

#अगर_घोषित HAVE_LIBDECOR_H
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        libdecor_frame_set_title(wind->shell_surface.libdecor.frame, title);
    } अन्यथा
#पूर्ण_अगर
        अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_set_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

अटल पूर्णांक icon_sort_callback(स्थिर व्योम *a, स्थिर व्योम *b)
{
    स्थिर SDL_Surface *s1 = *(स्थिर SDL_Surface **)a;
    स्थिर SDL_Surface *s2 = *(स्थिर SDL_Surface **)b;

    वापस (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
    SDL_Window_तथ्य *wind = window->internal;
    Wayland_SHMPool *shm_pool = शून्य;
    काष्ठा xdg_toplevel *toplevel = शून्य;

    अगर (!_this->internal->xdg_toplevel_icon_manager_v1) {
        वापस SDL_SetError("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    पूर्णांक image_गिनती_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_गिनती_2);
    अगर (!images || !image_गिनती_2) {
        वापस false;
    }

    // Release the old icon resources.
    अगर (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = शून्य;
    }

    क्रम (पूर्णांक i = 0; i < wind->icon_बफर_गिनती; ++i) {
        wl_बफर_destroy(wind->icon_buffers[i]);
    }
    wind->icon_बफर_गिनती = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->internal->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_गिनती_2 * माप(काष्ठा wl_बफर *));
    अगर (!wind->icon_buffers) {
        जाओ failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    माप_प्रकार pool_आकार = 0;
    क्रम (पूर्णांक i = 0; i < image_गिनती_2; ++i) {
        // Images must be square. Non-square images will be centered.
        स्थिर पूर्णांक आकार = SDL_max(images[i]->w, images[i]->h);
        pool_आकार += आकार * आकार * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_गिनती_2, माप(SDL_Surface *), icon_sort_callback);

    shm_pool = Wayland_AllocSHMPool(pool_आकार);
    अगर (!shm_pool) {
        SDL_SetError("wayland: failed to allocate an SHM pool for the icon");
        जाओ failure_cleanup;
    }

    स्थिर द्विगुन base_आकार = (द्विगुन)SDL_max(icon->w, icon->h);
    क्रम (पूर्णांक i = 0; i < image_गिनती_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        स्थिर पूर्णांक level_आकार = SDL_max(surface->w, surface->h);
        स्थिर पूर्णांक scale = (पूर्णांक)SDL_floor((द्विगुन)level_आकार / base_आकार);
        अगर (!scale) {
            जारी;
        }

        अगर (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            अगर (!surface) {
                SDL_SetError("wayland: failed to convert the icon image to ARGB8888 format");
                जाओ failure_cleanup;
            }
        }

        व्योम *बफर_mem;
        काष्ठा wl_बफर *बफर_2 = Wayland_Alloc_बफर_From_Pool(shm_pool, level_आकार, level_आकार, &बफर_mem);
        अगर (!बफर_2) {
            // Clean up the temporary conversion surface.
            अगर (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_SetError("wayland: failed to allocate a wl_buffer for the icon");
            जाओ failure_cleanup;
        }

        wind->icon_buffers[wind->icon_बफर_गिनती++] = बफर_2;

        // Center non-square images.
        अगर (surface->w < level_आकार) {
            SDL_memset(बफर_mem, 0, level_आकार * level_आकार * 4);
            बफर_mem = (Uint8 *)बफर_mem + (((level_आकार - surface->w) / 2) * 4);
        } अन्यथा अगर (surface->h < level_आकार) {
            SDL_memset(बफर_mem, 0, level_आकार * level_आकार * 4);
            बफर_mem = (Uint8 *)बफर_mem + (((level_आकार - surface->h) / 2) * (level_आकार * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, बफर_mem, level_आकार * 4, true);

        xdg_toplevel_icon_v1_add_बफर(wind->xdg_toplevel_icon_v1, बफर_2, scale);

        // Clean up the temporary scaled or conversion surface.
        अगर (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#अगर_घोषित HAVE_LIBDECOR_H
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        toplevel = libdecor_frame_get_xdg_toplevel(wind->shell_surface.libdecor.frame);
    } अन्यथा
#पूर्ण_अगर
        अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    अगर (toplevel) {
        xdg_toplevel_icon_manager_v1_set_icon(_this->internal->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
    }

    Wayland_ReleaseSHMPool(shm_pool);
    SDL_free(images);

    वापस true;

failure_cleanup:

    SDL_free(images);

    अगर (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = शून्य;
    }

    Wayland_ReleaseSHMPool(shm_pool);

    क्रम (पूर्णांक i = 0; i < wind->icon_बफर_गिनती; ++i) {
        wl_बफर_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = शून्य;
    wind->icon_बफर_गिनती = 0;

    वापस false;
}

व्योम *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, माप_प्रकार *आकार)
{
    SDL_Window_तथ्य *wind = window->internal;
    व्योम *ret = शून्य;

    अगर (wind->icc_आकार > 0) {
        व्योम *icc_map = mmap(शून्य, wind->icc_आकार, PROT_READ, MAP_PRIVATE, wind->icc_fd, 0);
        अगर (icc_map != MAP_FAILED) {
            ret = SDL_malloc(wind->icc_आकार);
            अगर (ret) {
                *आकार = wind->icc_आकार;
                SDL_memcpy(ret, icc_map, *आकार);
            }
            munmap(icc_map, wind->icc_आकार);
        }
    }

    वापस ret;
}

bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *wind = window->internal;

    करो {
        WAYLAND_wl_display_roundtrip(_this->internal->display);
    } जबतक (wind->pending_state_deadline_गिनती);

    वापस true;
}

व्योम Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    window->internal->accepts_drag_and_drop = accept;
}

bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    अगर (window->flags & SDL_WINDOW_POPUP_MENU) {
        अगर (!(window->flags & SDL_WINDOW_HIDDEN)) {
            अगर (!focusable && (window->flags & SDL_WINDOW_निवेश_FOCUS)) {
                SDL_Window *new_focus;
                स्थिर bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                Wayland_SetKeyboardFocus(new_focus, set_focus);
            } अन्यथा अगर (focusable) {
                अगर (SDL_ShouldFocusPopup(window)) {
                    Wayland_SetKeyboardFocus(window, true);
                }
            }
        }

        वापस true;
    }

    वापस SDL_SetError("wayland: focus can only be toggled on popup menu windows");
}

व्योम Wayland_ShowWindowSystemMenu(SDL_Window *window, पूर्णांक x, पूर्णांक y)
{
    SDL_Window_तथ्य *wind = window->internal;
    SDL_WaylandSeat *seat = wind->wayland_तथ्य->last_implicit_grab_seat;

    अगर (!seat) {
        वापस;
    }

    अगर (wind->scale_to_display) {
        x = PixelToPoint(window, x);
        y = PixelToPoint(window, y);
    }

#अगर_घोषित HAVE_LIBDECOR_H
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        अगर (wind->shell_surface.libdecor.frame) {
            libdecor_frame_show_window_menu(wind->shell_surface.libdecor.frame, seat->wl_seat, seat->last_implicit_grab_serial, x, y);
        }
    } अन्यथा
#पूर्ण_अगर
    अगर (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        अगर (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_window_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->last_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

#अगर_घोषित SDL_USE_LIBDBUS
    अगर (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        वापस true;
    }
#पूर्ण_अगर

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    अगर (तथ्य->idle_inhibit_manager) {
        SDL_Window *window = _this->windows;
        जबतक (window) {
            SDL_Window_तथ्य *win_तथ्य = window->internal;

            अगर (_this->suspend_screensaver && !win_तथ्य->idle_inhibitor) {
                win_तथ्य->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(तथ्य->idle_inhibit_manager,
                                                                 win_तथ्य->surface);
            } अन्यथा अगर (!_this->suspend_screensaver && win_तथ्य->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_तथ्य->idle_inhibitor);
                win_तथ्य->idle_inhibitor = शून्य;
            }

            window = window->अग्र;
        }
    }

    वापस true;
}

व्योम Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    SDL_Window_तथ्य *wind = window->internal;

    अगर (तथ्य && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        अगर (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            window->hit_test = शून्य;
            WAYLAND_wl_display_roundtrip(तथ्य->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_DisplayRemoveWindowReferencesFromSeats(तथ्य, wind);

        अगर (wind->mask.viewport) {
            wp_viewport_destroy(wind->mask.viewport);
        }
        अगर (wind->mask.बफर_2) {
            wl_बफर_destroy(wind->mask.बफर_2);
        }
        अगर (wind->mask.subsurface) {
            wl_subsurface_destroy(wind->mask.subsurface);
        }
        अगर (wind->mask.surface) {
            wl_surface_destroy(wind->mask.surface);
        }
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
        अगर (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#पूर्ण_अगर
        अगर (wind->egl_window) {
            WAYLAND_wl_egl_window_destroy(wind->egl_window);
        }

        अगर (wind->idle_inhibitor) {
            zwp_idle_inhibitor_v1_destroy(wind->idle_inhibitor);
        }

        अगर (wind->activation_token) {
            xdg_activation_token_v1_destroy(wind->activation_token);
        }

        अगर (wind->viewport) {
            wp_viewport_destroy(wind->viewport);
        }

        अगर (wind->fractional_scale) {
            wp_fractional_scale_v1_destroy(wind->fractional_scale);
        }

        अगर (wind->wp_alpha_modifier_surface_v1) {
            wp_alpha_modifier_surface_v1_destroy(wind->wp_alpha_modifier_surface_v1);
        }

        अगर (wind->frog_color_managed_surface) {
            frog_color_managed_surface_destroy(wind->frog_color_managed_surface);
        }

        अगर (wind->wp_color_management_surface_feedback) {
            Wayland_FreeColorInfoState(wind->color_info_state);
            wp_color_management_surface_feedback_v1_destroy(wind->wp_color_management_surface_feedback);
        }

        SDL_free(wind->outputs);
        SDL_free(wind->app_id);

        अगर (wind->gles_swap_frame_callback) {
            wl_callback_destroy(wind->gles_swap_frame_callback);
            WAYLAND_wl_proxy_wrapper_destroy(wind->gles_swap_frame_surface_wrapper);
            WAYLAND_wl_event_queue_destroy(wind->gles_swap_frame_event_queue);
        }

        अगर (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } अन्यथा {
            Wayland_Remove_Window_तथ्य_From_External_List(wind);
        }

        अगर (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        क्रम (पूर्णांक i = 0; i < wind->icon_बफर_गिनती; ++i) {
            wl_बफर_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_बफर_गिनती = 0;

        SDL_free(wind);
    }
    window->internal = शून्य;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND
