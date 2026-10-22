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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

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

#ifdef HAVE_LIBDECOR_H
#अन्तर्भाव <libdecor.h>
#endif

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
स्थिर bool ShouldMaskFullscreen()
{
    स्थिर पूर्णाङ्क mask_required = -1;

    यदि (mask_required >= 0) {
        प्रत्यागम mask_required != 0;
    }

    ध्रुव वर्ण *desktop = SDL_getenv("XDG_CURRENT_DESKTOP");
    यदि (desktop && SDL_strstr(desktop, "KDE") != रिक्त) {
        mask_required = 1;
    } अन्यथा {
        mask_required = 0;
    }

    प्रत्यागम mask_required != 0;
}

स्थिर द्विगुण GetWindowScale(SDL_Window *window)
{
    प्रत्यागम (window->flags & SDL_WINDOW_वरचा_PIXEL_DENSITY) || window->internal->scale_to_display ? window->internal->scale_factor : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
स्थिर पूर्णाङ्क PointToPixel(SDL_Window *window, पूर्णाङ्क point)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    प्रत्यागम point ? SDL_max((पूर्णाङ्क)SDL_lround((द्विगुण)point * GetWindowScale(window) + 1e-6), 1) : 0;
}

स्थिर पूर्णाङ्क PixelToPoint(SDL_Window *window, पूर्णाङ्क pixel)
{
    प्रत्यागम pixel ? SDL_max((पूर्णाङ्क)SDL_lround((द्विगुण)pixel / GetWindowScale(window)), 1) : 0;
}

गणना WaylandModeScale
{
    WAYLAND_MODE_SCALE_UNDEFINED,
    WAYLAND_MODE_SCALE_ASPECT,
    WAYLAND_MODE_SCALE_STRETCH,
    WAYLAND_MODE_SCALE_NONE
};

स्थिर गणना WaylandModeScale GetModeScaleMethod(शून्य)
{
    स्थिर गणना WaylandModeScale scale_mode = WAYLAND_MODE_SCALE_UNDEFINED;

    यदि (scale_mode == WAYLAND_MODE_SCALE_UNDEFINED) {
        ध्रुव वर्ण *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_MODE_SCALING);

        यदि (scale_hint) {
            यदि (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_mode = WAYLAND_MODE_SCALE_STRETCH;
            } अन्यथा यदि (!SDL_strcasecmp(scale_hint, "none")) {
                scale_mode = WAYLAND_MODE_SCALE_NONE;
            } अन्यथा {
                scale_mode = WAYLAND_MODE_SCALE_ASPECT;
            }
        } अन्यथा {
            scale_mode = WAYLAND_MODE_SCALE_ASPECT;
        }
    }

    प्रत्यागम scale_mode;
}

प्रकारनिर्देश संरचना BorderInsets
{
    पूर्णाङ्क डावा;
    पूर्णाङ्क शीर्ष;
    पूर्णाङ्क उजवा;
    पूर्णाङ्क bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
स्थिर शून्य GetBorderInsets(SDL_Window *window, BorderInsets *insets)
{
    SDL_zerop(insets);
    यदि (!window->internal->enable_insets) {
        प्रत्यागम;
    }
    यदि (window->internal->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ध्रुव SDL_PropertiesID props = SDL_GetWindowProperties(window);
        insets->डावा = (पूर्णाङ्क)SDL_clamp(SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_डावा_संख्या, 0), 0, SDL_MAX_SINT16);
        insets->शीर्ष = (पूर्णाङ्क)SDL_clamp(SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_शीर्ष_संख्या, 0), 0, SDL_MAX_SINT16);
        insets->उजवा = (पूर्णाङ्क)SDL_clamp(SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_उजवा_संख्या, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (पूर्णाङ्क)SDL_clamp(SDL_Get_संख्या_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_BOTTOM_संख्या, 0), 0, SDL_MAX_SINT16);
    }
}

स्थिर शून्य SetMinMaxDimensions(SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;
    पूर्णाङ्क min_width, min_height, max_width, max_height;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    यदि (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) {
        min_width = 0;
        min_height = 0;
        max_width = 0;
        max_height = 0;
    } अन्यथा यदि (window->flags & SDL_WINDOW_RESIZABLE) {
        पूर्णाङ्क adj_w = SDL_max(window->min_w, wind->system_limits.min_width);
        पूर्णाङ्क adj_h = SDL_max(window->min_h, wind->system_limits.min_height);
        यदि (wind->scale_to_display) {
            adj_w = PixelToPoint(window, adj_w);
            adj_h = PixelToPoint(window, adj_h);
        }
        min_width = adj_w;
        min_height = adj_h;

        adj_w = window->max_w ? SDL_max(window->max_w, wind->system_limits.min_width) : 0;
        adj_h = window->max_h ? SDL_max(window->max_h, wind->system_limits.min_height) : 0;
        यदि (wind->scale_to_display) {
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

#ifdef HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (!wind->shell_surface.libdecor.frame) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }

        यदि (min_width && min_height && min_width == max_width && min_height == max_height) {
            libdecor_frame_unset_capabilities(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE);
        } अन्यथा {
            libdecor_frame_set_capabilities(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        यदि (libdecor_frame_has_capability(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE)) {
            libdecor_frame_set_min_content_size(wind->shell_surface.libdecor.frame,
                                                min_width,
                                                min_height);
            libdecor_frame_set_max_content_size(wind->shell_surface.libdecor.frame,
                                                max_width,
                                                max_height);
        }
    } अन्यथा
#endif
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(window, &insets);
        min_width = SDL_max(min_width - (insets.डावा + insets.उजवा), min_width ? 1 : 0);
        min_height = SDL_max(min_height - (insets.शीर्ष + insets.bottom), min_height ? 1 : 0);
        यदि (max_width) {
            max_width = SDL_max(max_width - (insets.डावा + insets.उजवा), 1);
        }
        यदि (max_height) {
            max_height = SDL_max(max_height - (insets.शीर्ष + insets.bottom), 1);
        }
        xdg_toplevel_set_min_size(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_width,
                                  min_height);
        xdg_toplevel_set_max_size(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_width,
                                  max_height);
    }
}

स्थिर शून्य EnsurePopupPositionIsValid(SDL_Window *window, पूर्णाङ्क *x, पूर्णाङ्क *y)
{
    पूर्णाङ्क adj_मोजणी = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    यदि (*x + window->w <= 0) {
        *x = -window->w;
        ++adj_मोजणी;
    }
    यदि (*y + window->h <= 0) {
        *y = -window->h;
        ++adj_मोजणी;
    }
    यदि (*x >= window->parent->w) {
        *x = window->parent->w;
        ++adj_मोजणी;
    }
    यदि (*y >= window->parent->h) {
        *y = window->parent->h;
        ++adj_मोजणी;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    यदि (adj_मोजणी > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
स्थिर शून्य GetWindowGeometry(SDL_WindowData *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    यदि (SDL_RectEmpty(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_width;
        geometry->h = wind->current.logical_height;
    }
}

स्थिर शून्य AdjustPopupOffset(SDL_Window *popup, पूर्णाङ्क *x, पूर्णाङ्क *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#ifdef HAVE_LIBDECOR_H
    यदि (popup->parent->internal->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        पूर्णाङ्क adj_x, adj_y;
        libdecor_frame_translate_coordinate(popup->parent->internal->shell_surface.libdecor.frame,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } अन्यथा
#endif
    {
        *x -= popup->parent->internal->explicit_geometry.x;
        *y -= popup->parent->internal->explicit_geometry.y;
    }
}

स्थिर शून्य RepositionPopup(SDL_Window *window, bool use_current_position)
{
    SDL_WindowData *wind = window->internal;

    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_version(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_VERSION) {
        पूर्णाङ्क x = use_current_position ? window->x : window->pending.x;
        पूर्णाङ्क y = use_current_position ? window->y : window->pending.y;

        EnsurePopupPositionIsValid(window, &x, &y);
        यदि (wind->scale_to_display) {
            x = PixelToPoint(window->parent, x);
            y = PixelToPoint(window->parent, y);
        }
        AdjustPopupOffset(window, &x, &y);
        SDL_Rect parent_geometry;
        GetWindowGeometry(window->parent->internal, &parent_geometry);
        xdg_positioner_set_anchor_rect(wind->shell_surface.xdg.popup.xdg_positioner, 0, 0, parent_geometry.w, parent_geometry.h);
        xdg_positioner_set_size(wind->shell_surface.xdg.popup.xdg_positioner, wind->current.logical_width, wind->current.logical_height);
        xdg_positioner_set_offset(wind->shell_surface.xdg.popup.xdg_positioner, x, y);
        xdg_popup_reposition(wind->shell_surface.xdg.popup.xdg_popup,
                             wind->shell_surface.xdg.popup.xdg_positioner,
                             0);
    }
}

स्थिर शून्य SetSurfaceOpaqueRegion(संरचना wl_surface *surface, पूर्णाङ्क width, पूर्णाङ्क height)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    यदि (width && height) {
        संरचना wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_add(region, 0, 0, width, height);
        wl_surface_set_opaque_region(surface, region);
        wl_region_destroy(region);
    } अन्यथा {
        wl_surface_set_opaque_region(surface, रिक्त);
    }
}

स्थिर शून्य ConfigureWindowGeometry(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    ध्रुव द्विगुण scale_factor = GetWindowScale(window);
    ध्रुव द्विगुण prev_pointer_scale_x = data->pointer_scale.x;
    ध्रुव द्विगुण prev_pointer_scale_y = data->pointer_scale.y;
    ध्रुव पूर्णाङ्क old_pixel_width = data->current.pixel_width;
    ध्रुव पूर्णाङ्क old_pixel_height = data->current.pixel_height;
    पूर्णाङ्क window_width = 0;
    पूर्णाङ्क window_height = 0;
    पूर्णाङ्क viewport_width, viewport_height;
    bool window_size_changed;
    bool buffer_size_changed;
    ध्रुव bool is_opaque = !(window->flags & SDL_WINDOW_TRANSPARENT) && window->opacity == 1.0f;

    यदि (data->is_fullscreen && window->fullscreen_exclusive) {
        window_width = window->current_fullscreen_mode.w;
        window_height = window->current_fullscreen_mode.h;

        viewport_width = data->requested.logical_width;
        viewport_height = data->requested.logical_height;

        विकल्प (GetModeScaleMethod()) {
        पक्ष WAYLAND_MODE_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            यदि (window_width <= viewport_width && window_height <= viewport_height) {
                viewport_width = window_width;
                viewport_height = window_height;

                भङ्ग;
            }
            SDL_FALLTHROUGH;
        पक्ष WAYLAND_MODE_SCALE_ASPECT:
        {
            ध्रुव भिन्न output_ratio = (भिन्न)viewport_width / (भिन्न)viewport_height;
            ध्रुव भिन्न mode_ratio = (भिन्न)window_width / (भिन्न)window_height;

            यदि (output_ratio > mode_ratio) {
                viewport_width = SDL_lroundf((भिन्न)window_width * ((भिन्न)viewport_height / (भिन्न)window_height));
            } अन्यथा यदि (output_ratio < mode_ratio) {
                viewport_height = SDL_lroundf((भिन्न)window_height * ((भिन्न)viewport_width / (भिन्न)window_width));
            }
        } भङ्ग;
        स्वभाव:
            भङ्ग;
        }

        window_size_changed = window_width != window->w ||
                              window_height != window->h ||
                              data->current.viewport_width != viewport_width ||
                              data->current.viewport_height != viewport_height;

        // Exclusive fullscreen window sizes are always in pixel units.
        data->current.pixel_width = window_width;
        data->current.pixel_height = window_height;
        buffer_size_changed = data->current.pixel_width != old_pixel_width ||
                              data->current.pixel_height != old_pixel_height;

        यदि (window_size_changed || buffer_size_changed) {
            यदि (data->viewport) {
                wp_viewport_set_destination(data->viewport, viewport_width, viewport_height);

                data->current.logical_width = data->requested.logical_width;
                data->current.logical_height = data->requested.logical_height;
                data->current.viewport_width = viewport_width;
                data->current.viewport_height = viewport_height;
            } अन्यथा {
                // Calculate the integer scale from the mode and output.
                ध्रुव int32_t int_scale = SDL_max(window->current_fullscreen_mode.w / viewport_width, 1);

                wl_surface_set_buffer_scale(data->surface, int_scale);
                data->current.logical_width = window->current_fullscreen_mode.w;
                data->current.logical_height = window->current_fullscreen_mode.h;
            }

            data->pointer_scale.x = (द्विगुण)window_width / (द्विगुण)viewport_width;
            data->pointer_scale.y = (द्विगुण)window_height / (द्विगुण)viewport_height;
        }
    } अन्यथा {
        यदि (!data->scale_to_display) {
            viewport_width = data->requested.logical_width;
            viewport_height = data->requested.logical_height;
        } अन्यथा {
            viewport_width = data->requested.pixel_width;
            viewport_height = data->requested.pixel_height;
        }

        यदि (!data->enable_insets &&
            data->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_HIDDEN &&
            data->viewport && data->waylandData->subcompositor && !data->floating && !data->is_fullscreen) {
            पूर्णाङ्क min_width, min_height, max_width, max_height;
            यदि (window->flags & SDL_WINDOW_RESIZABLE) {
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

            यदि (min_width) {
                viewport_width = SDL_max(viewport_width, min_width);
            }
            यदि (min_height) {
                viewport_height = SDL_max(viewport_height, min_height);
            }
            यदि (max_width) {
                viewport_width = SDL_min(viewport_width, max_width);
            }
            यदि (max_height) {
                viewport_height = SDL_min(viewport_height, max_height);
            }

            भिन्न aspect = (भिन्न)viewport_width / (भिन्न)viewport_height;
            यदि (window->min_aspect != 0.f && aspect < window->min_aspect) {
                viewport_height = SDL_max(SDL_lroundf((भिन्न)viewport_width / window->min_aspect), 1);
            } अन्यथा यदि (window->max_aspect != 0.f && aspect > window->max_aspect) {
                viewport_width = SDL_max(SDL_lroundf((भिन्न)viewport_height * window->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            window_width = viewport_width;
            window_height = viewport_height;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            यदि (!data->scale_to_display) {
                यदि (viewport_width > data->requested.logical_width || viewport_height > data->requested.logical_height) {
                    aspect = (भिन्न)viewport_width / (भिन्न)viewport_height;
                    ध्रुव भिन्न window_ratio = (भिन्न)data->requested.logical_width / (भिन्न)data->requested.logical_height;
                    यदि (aspect >= window_ratio) {
                        viewport_width = data->requested.logical_width;
                        viewport_height = SDL_lroundf((भिन्न)viewport_width / aspect);
                    } अन्यथा यदि (aspect < window_ratio) {
                        viewport_height = data->requested.logical_height;
                        viewport_width = SDL_lroundf((भिन्न)viewport_height * aspect);
                    }
                }
            } अन्यथा {
                यदि (viewport_width > data->requested.pixel_width || viewport_height > data->requested.pixel_height) {
                    aspect = (भिन्न)viewport_width / (भिन्न)viewport_height;
                    ध्रुव भिन्न window_ratio = (भिन्न)data->requested.pixel_width / (भिन्न)data->requested.pixel_height;
                    यदि (aspect >= window_ratio) {
                        viewport_width = data->requested.pixel_width;
                        viewport_height = SDL_lroundf((भिन्न)viewport_width / aspect);
                    } अन्यथा यदि (aspect < window_ratio) {
                        viewport_height = data->requested.pixel_height;
                        viewport_width = SDL_lroundf((भिन्न)viewport_height * aspect);
                    }
                }
            }

            viewport_width = SDL_max(viewport_width, 1);
            viewport_height = SDL_max(viewport_height, 1);
        } अन्यथा {
            window_width = viewport_width;
            window_height = viewport_height;
        }

        यदि (!data->scale_to_display) {
            data->current.pixel_width = PointToPixel(window, window_width);
            data->current.pixel_height = PointToPixel(window, window_height);
        } अन्यथा {
            // The viewport size is in pixels at this point; convert it to logical units.
            data->current.pixel_width = window_width;
            data->current.pixel_height = window_height;
            viewport_width = PixelToPoint(window, viewport_width);
            viewport_height = PixelToPoint(window, viewport_height);
        }

        // Clamp the physical window size to the system minimum required size.
        data->requested.logical_width = SDL_max(data->requested.logical_width, data->system_limits.min_width);
        data->requested.logical_height = SDL_max(data->requested.logical_height, data->system_limits.min_height);

        window_size_changed = data->requested.logical_width != data->current.logical_width ||
                              data->requested.logical_height != data->current.logical_height ||
                              viewport_width != data->current.viewport_width ||
                              viewport_height != data->current.viewport_height;

        buffer_size_changed = data->current.pixel_width != old_pixel_width ||
                              data->current.pixel_height != old_pixel_height;

        यदि (window_size_changed || buffer_size_changed) {
            यदि (data->viewport) {
                wp_viewport_set_destination(data->viewport, viewport_width, viewport_height);
            } अन्यथा यदि (window->flags & SDL_WINDOW_वरचा_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_set_buffer_scale(data->surface, (int32_t)scale_factor);
            }

            data->current.logical_width = data->requested.logical_width;
            data->current.logical_height = data->requested.logical_height;
            data->current.viewport_width = viewport_width;
            data->current.viewport_height = viewport_height;

            data->pointer_scale.x = (द्विगुण)window_width / (द्विगुण)viewport_width;
            data->pointer_scale.y = (द्विगुण)window_height / (द्विगुण)viewport_height;
        }
    }

    यदि (data->egl_window && buffer_size_changed) {
        WAYLAND_wl_egl_window_resize(data->egl_window,
                                     data->current.pixel_width,
                                     data->current.pixel_height,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    यदि (!data->enable_insets && data->viewport && data->waylandData->subcompositor && (!data->is_fullscreen || ShouldMaskFullscreen()) &&
        (viewport_width != data->current.logical_width || viewport_height != data->current.logical_height)) {
        संरचना wl_buffer *old_buffer = रिक्त;

        यदि (!data->mask.surface) {
            data->mask.surface = wl_compositor_create_surface(data->waylandData->compositor);
            SDL_WAYLAND_register_surface(data->mask.surface);
            wl_surface_set_user_data(data->mask.surface, data);
        }
        यदि (!data->mask.subsurface) {
            data->mask.subsurface = wl_subcompositor_get_subsurface(data->waylandData->subcompositor, data->mask.surface, data->surface);
        }
        यदि (!data->mask.viewport) {
            data->mask.viewport = wp_viewporter_get_viewport(data->waylandData->viewporter, data->mask.surface);
        }
        यदि (!data->mask.buffer || data->mask.opaque != is_opaque) {
            old_buffer = data->mask.buffer;
            data->mask.opaque = is_opaque;
            data->mask.buffer = Wayland_CreateSinglePixelBuffer(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(data->mask.surface, data->mask.buffer, 0, 0);

        wl_subsurface_place_below(data->mask.subsurface, data->surface);
        wp_viewport_set_destination(data->mask.viewport, data->current.logical_width, data->current.logical_height);

        यदि (wl_surface_get_version(data->mask.surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
            wl_surface_damage_buffer(data->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } अन्यथा {
            wl_surface_damage(data->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        यदि (is_opaque) {
            SetSurfaceOpaqueRegion(data->mask.surface, data->current.logical_width, data->current.logical_height);
        } अन्यथा {
            SetSurfaceOpaqueRegion(data->mask.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        यदि (data->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            data->mask.offset_x = -(data->current.logical_width - viewport_width) / 2;
            data->mask.offset_y = -(data->current.logical_height - viewport_height) / 2;
        } अन्यथा {
            data->mask.offset_x = 0;
            data->mask.offset_y = 0;
        }

        wl_subsurface_set_position(data->mask.subsurface, data->mask.offset_x, data->mask.offset_y);
        wl_surface_commit(data->mask.surface);

        यदि (old_buffer) {
            wl_buffer_destroy(old_buffer);
        }

        data->mask.mapped = true;
    } अन्यथा यदि (data->mask.mapped) {
        wl_subsurface_set_position(data->mask.subsurface, 0, 0);
        wl_surface_attach(data->mask.surface, रिक्त, 0, 0);
        wl_surface_commit(data->mask.surface);

        data->mask.offset_x = 0;
        data->mask.offset_y = 0;
        data->mask.mapped = false;
    }

    यदि (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && data->shell_surface.xdg.surface &&
        (data->enable_insets || !data->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(window, &insets);
        ध्रुव bool use_insets = (insets.डावा || insets.शीर्ष || insets.उजवा || insets.bottom) &&
                                !(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, data->current.logical_width, data->current.logical_height };
        यदि (use_insets) {
            geometry.x = insets.डावा;
            geometry.y = insets.शीर्ष;
            geometry.w = SDL_max(geometry.w - (insets.डावा + insets.उजवा), 1);
            geometry.h = SDL_max(geometry.h - (insets.शीर्ष + insets.bottom), 1);
        }
        /* An explicitly set geometry does not track the surface, so it must be kept in sync
         * once set. Otherwise this is only done when viewports aren't supported and the size
         * has changed (XXX: a hack) to avoid a potential protocol violation if a buffer with
         * an old size is committed.
         */
        यदि ((use_insets || !SDL_RectEmpty(&data->explicit_geometry) || (!data->viewport && window_size_changed)) &&
            !SDL_RectsEqual(&geometry, &data->explicit_geometry)) {
            xdg_surface_set_window_geometry(data->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            data->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    यदि (window_size_changed) {
        यदि (is_opaque) {
            SetSurfaceOpaqueRegion(data->surface, viewport_width, viewport_height);
        } अन्यथा {
            SetSurfaceOpaqueRegion(data->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        प्रति (SDL_Window *child = window->first_child; child; child = child->next_sibling) {
            RepositionPopup(child, true);
        }
    }

    // Update the scale for any focused cursors.
    यदि (prev_pointer_scale_x != data->pointer_scale.x || prev_pointer_scale_y != data->pointer_scale.y) {
        Wayland_DisplayUpdatePointerFocusedScale(data);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    SetMinMaxDimensions(window);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    यदि (!data->scale_to_display) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window_width, window_height);
    } अन्यथा {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, data->current.pixel_width, data->current.pixel_height);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, data->current.pixel_width, data->current.pixel_height);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    यदि (data->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        यदि ((buffer_size_changed || window_size_changed) ||
            (!data->suspended && (window->flags & SDL_WINDOW_OCCLUDED))) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }

        यदि (data->suspended) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
        }
    }
}

स्थिर शून्य CommitLibdecorFrame(SDL_Window *window)
{
#ifdef HAVE_LIBDECOR_H
    SDL_WindowData *wind = window->internal;

    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        संरचना libdecor_state *state = libdecor_state_new(wind->current.logical_width, wind->current.logical_height);
        libdecor_frame_commit(wind->shell_surface.libdecor.frame, state, रिक्त);
        libdecor_state_free(state);
    }
#endif
}

स्थिर शून्य pending_state_deadline_handler(शून्य *data, संरचना wl_callback *callback, uint32_t callback_data)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_WindowID windowID = (SDL_WindowID)(uintptr_t)data;
    SDL_Window *window = SDL_GetWindowFromID(windowID);

    यदि (window && window->internal) {
        --window->internal->pending_state_deadline_मोजणी;
    }

    wl_callback_destroy(callback);
}

स्थिर संरचना wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

स्थिर शून्य AddPendingStateSync(SDL_WindowData *window_data)
{
    SDL_VideoData *video_data = window_data->waylandData;
    शून्य *cb_data = (शून्य *)(uintptr_t)window_data->sdlwindow->id;

    ++window_data->pending_state_deadline_मोजणी;
    संरचना wl_callback *cb = wl_display_sync(video_data->display);
    wl_callback_add_listener(cb, &pending_state_deadline_listener, cb_data);
}

स्थिर शून्य FlushPendingEvents(SDL_Window *window)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ध्रुव bool last_position_pending = window->last_position_pending;
    ध्रुव bool last_size_pending = window->last_size_pending;

    यावत् (window->internal->pending_state_deadline_मोजणी) {
        WAYLAND_wl_display_roundtrip(window->internal->waylandData->display);
    }

    window->last_position_pending = last_position_pending;
    window->last_size_pending = last_size_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
शून्य Wayland_UpdateWindowPosition(SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;
    SDL_DisplayData *display;

    यदि (wind->outputs && wind->अंक_outputs) {
        display = wind->outputs[wind->अंक_outputs - 1];
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
    wind->last_displayID = display->display;
    यदि (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        यदि (!wind->waylandData->scale_to_display_enabled) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, display->logical.x, display->logical.y);
        } अन्यथा {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, wind->last_displayID, 0);
    }
}

स्थिर शून्य SetFullscreen(SDL_Window *window, संरचना wl_output *output, bool fullscreen)
{
    SDL_WindowData *wind = window->internal;

#ifdef HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (!wind->shell_surface.libdecor.frame) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? window->fullscreen_exclusive : false;
        यदि (fullscreen) {
            libdecor_frame_set_fullscreen(wind->shell_surface.libdecor.frame, output);
        } अन्यथा {
            libdecor_frame_unset_fullscreen(wind->shell_surface.libdecor.frame);
        }
    } अन्यथा
#endif
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel == रिक्त) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? window->fullscreen_exclusive : false;
        यदि (fullscreen) {
            xdg_toplevel_set_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } अन्यथा {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    AddPendingStateSync(wind);
}

स्थिर शून्य UpdateWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    SDL_WindowData *wind = window->internal;

    wind->is_fullscreen = fullscreen;

    यदि (fullscreen) {
        यदि (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            यदि (window->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(window->current_fullscreen_mode.displayID);
                यदि (disp) {
                    wind->fullscreen_was_positioned = true;
                    SetFullscreen(window, disp->internal->output, true);
                }
            }
        }
    } अन्यथा {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        यदि ((window->flags & SDL_WINDOW_FULLSCREEN) && !window->is_hiding && !(window->flags & SDL_WINDOW_HIDDEN)) {
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

स्थिर ध्रुव संरचना wl_callback_listener surface_frame_listener;

स्थिर शून्य surface_frame_done(शून्य *data, संरचना wl_callback *cb, uint32_t time)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    यदि (wl_compositor_get_version(wind->waylandData->compositor) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
        wl_surface_damage_buffer(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } अन्यथा {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            ConfigureWindowGeometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } अन्यथा {
        wind->resizing = false;
    }

    यदि (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        प्रति (SDL_Window *w = wind->sdlwindow->first_child; w; w = w->next_sibling) {
            यदि (w->internal->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING) {
                Wayland_ShowWindow(SDL_GetVideoDevice(), w);
            } अन्यथा यदि (w->internal->reparenting_required) {
                Wayland_SetWindowParent(SDL_GetVideoDevice(), w, w->parent);
                यदि (w->flags & SDL_WINDOW_MODAL) {
                    Wayland_SetWindowModal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        यदि (wind->suspended) {
            SDL_SendWindowEvent(wind->sdlwindow, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_frame_callback = wl_surface_frame(wind->surface);
    wl_callback_add_listener(wind->surface_frame_callback, &surface_frame_listener, data);
}

स्थिर ध्रुव संरचना wl_callback_listener surface_frame_listener = {
    surface_frame_done
};

स्थिर ध्रुव संरचना wl_callback_listener gles_swap_frame_listener;

स्थिर शून्य gles_swap_frame_done(शून्य *data, संरचना wl_callback *cb, uint32_t time)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    SDL_SetAtomicInt(&wind->swap_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_swap_frame_callback = wl_surface_frame(wind->gles_swap_frame_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_add_listener(wind->gles_swap_frame_callback, &gles_swap_frame_listener, data);
}

स्थिर ध्रुव संरचना wl_callback_listener gles_swap_frame_listener = {
    gles_swap_frame_done
};

स्थिर शून्य handle_xdg_surface_configure(शून्य *data, संरचना xdg_surface *xdg, uint32_t serial)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    SDL_Window *window = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    यदि (!wind->resizing) {
        wind->pending_config_ack = false;
        ConfigureWindowGeometry(window);
        xdg_surface_ack_configure(xdg, serial);
    } अन्यथा यदि (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }

    यदि (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME;
    }
}

स्थिर ध्रुव संरचना xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

स्थिर शून्य ApplyGeometryLimits(SDL_Window *window, पूर्णाङ्क req_w, पूर्णाङ्क req_h, पूर्णाङ्क *out_w, पूर्णाङ्क *out_h)
{
    SDL_WindowData *wind = window->internal;

    पूर्णाङ्क w = req_w;
    पूर्णाङ्क h = req_h;
    ध्रुव भिन्न aspect = (भिन्न)req_w / (भिन्न)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    यदि (!wind->resizing || (wind->resize_edge & WAYLAND_RESIZE_EDGE_CORNER) == WAYLAND_RESIZE_EDGE_CORNER) {
        यदि (window->min_aspect != 0.f && aspect < window->min_aspect) {
            h = SDL_max(SDL_lroundf((भिन्न)req_w / window->min_aspect), 1);

            यदि (h < window->min_h) {
                w = SDL_max(SDL_lroundf((भिन्न)window->min_h * window->min_aspect), 1);
            }
            यदि (window->max_h && h > window->max_h) {
                w = SDL_max(SDL_lroundf((भिन्न)window->max_h * window->min_aspect), 1);
            }
        } अन्यथा यदि (window->max_aspect != 0.f && aspect > window->max_aspect) {
            w = SDL_max(SDL_lroundf((भिन्न)req_h * window->max_aspect), 1);

            यदि (w < window->min_w) {
                h = SDL_max(SDL_lroundf((भिन्न)window->min_w / window->max_aspect), 1);
            }
            यदि (window->max_w && w > window->max_w) {
                h = SDL_max(SDL_lroundf((भिन्न)window->max_w / window->max_aspect), 1);
            }
        }
    } अन्यथा यदि (wind->resize_edge & WAYLAND_RESIZE_EDGE_LR) {
        यदि (window->min_aspect != 0.f && aspect < window->min_aspect) {
            h = SDL_max(SDL_lroundf((भिन्न)req_w / window->min_aspect), 1);

            यदि (h < window->min_h) {
                w = SDL_max(SDL_lroundf((भिन्न)window->min_h * window->min_aspect), 1);
            }
            यदि (window->max_h && h > window->max_h) {
                w = SDL_max(SDL_lroundf((भिन्न)window->max_h * window->min_aspect), 1);
            }
        } अन्यथा यदि (window->max_aspect != 0.f && aspect > window->max_aspect) {
            h = SDL_max(SDL_lroundf((भिन्न)req_w / window->max_aspect), 1);

            यदि (h < window->min_h) {
                w = SDL_max(SDL_lroundf((भिन्न)window->min_h * window->max_aspect), 1);
            }
            यदि (window->max_h && h > window->max_h) {
                w = SDL_max(SDL_lroundf((भिन्न)window->max_h * window->max_aspect), 1);
            }
        }
    } अन्यथा यदि (wind->resize_edge & WAYLAND_RESIZE_EDGE_TB) {
        यदि (window->min_aspect != 0.f && aspect < window->min_aspect) {
            w = SDL_max(SDL_lroundf((भिन्न)req_h * window->min_aspect), 1);

            यदि (w < window->min_w) {
                h = SDL_max(SDL_lroundf((भिन्न)window->min_w / window->min_aspect), 1);
            }
            यदि (window->max_w && w > window->max_w) {
                h = SDL_max(SDL_lroundf((भिन्न)window->max_w / window->min_aspect), 1);
            }
        } अन्यथा यदि (window->max_aspect != 0.f && aspect > window->max_aspect) {
            w = SDL_max(SDL_lroundf((भिन्न)req_h * window->max_aspect), 1);

            यदि (w < window->min_w) {
                h = SDL_max(SDL_lroundf((भिन्न)window->min_w / window->max_aspect), 1);
            }
            यदि (window->max_w && w > window->max_w) {
                h = SDL_max(SDL_lroundf((भिन्न)window->max_w / window->max_aspect), 1);
            }
        }
    }

    यदि (window->max_w) {
        w = SDL_min(w, window->max_w);
    }
    *out_w = SDL_max(w, window->min_w);

    यदि (window->max_h) {
        h = SDL_min(h, window->max_h);
    }
    *out_h = SDL_max(h, window->min_h);

}

स्थिर शून्य DetermineResizeAxis(SDL_WindowData *wind, पूर्णाङ्क width, पूर्णाङ्क height, bool resizing)
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
        यदि (now >= wind->last_resize_event_time_ns + SDL_MS_TO_NS(500)) {
            wind->resize_edge = 0;
        }

        wind->last_resize_event_time_ns = now;

        यदि (!wind->resize_edge) {
            यदि (width != wind->last_configure.width || !height) {
                wind->resize_edge |= WAYLAND_RESIZE_EDGE_LR;
            }
            यदि (height != wind->last_configure.height || !width) {
                wind->resize_edge |= WAYLAND_RESIZE_EDGE_TB;
            }
        }
    } अन्यथा {
        wind->resize_edge = 0;
    }

    wind->resizing = resizing;
}

स्थिर शून्य handle_xdg_toplevel_configure(शून्य *data,
                                          संरचना xdg_toplevel *xdg_toplevel,
                                          int32_t width,
                                          int32_t height,
                                          संरचना wl_array *states)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    SDL_Window *window = wind->sdlwindow;

    गणना xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool active = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, states) {
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
            active = true;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_TILED_डावा:
        पक्ष XDG_TOPLEVEL_STATE_TILED_उजवा:
        पक्ष XDG_TOPLEVEL_STATE_TILED_शीर्ष:
        पक्ष XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_CONSTRAINED_डावा:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_डावा;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_CONSTRAINED_उजवा:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_उजवा;
            भङ्ग;
        पक्ष XDG_TOPLEVEL_STATE_CONSTRAINED_शीर्ष:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष;
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
    ध्रुव bool new_configure_size = width != wind->last_configure.width || height != wind->last_configure.height ||
                                    insets_apply != wind->last_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    यदि (insets_apply) {
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
    यदि (active || !(window->flags & SDL_WINDOW_MINIMIZED)) {
        यदि (window->flags & SDL_WINDOW_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
        SDL_SendWindowEvent(window,
                            (maximized && !fullscreen) ? SDL_EVENT_WINDOW_MAXIMIZED : SDL_EVENT_WINDOW_RESTORED,
                            0, 0);
    }

    यदि (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        यदि ((window->flags & SDL_WINDOW_RESIZABLE) || maximized) {
            यदि (!width) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                यदि (floating) {
                    width = window->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    यदि (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.width) {
                        width = SDL_min(wind->toplevel_bounds.width, width);
                    }
                } अन्यथा {
                    width = window->windowed.w;
                }

                यदि (!wind->scale_to_display) {
                    wind->requested.logical_width = width;
                } अन्यथा {
                    wind->requested.pixel_width = width;
                    width = wind->requested.logical_width = PixelToPoint(window, width);
                }
                width = SDL_max(width - (insets.डावा + insets.उजवा), 1);
            } अन्यथा यदि (new_configure_size) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_width = width + (insets.डावा + insets.उजवा);

                यदि (wind->scale_to_display) {
                    wind->requested.pixel_width = PointToPixel(window, wind->requested.logical_width);
                }
            }
            यदि (!height) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                यदि (floating) {
                    height = window->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    यदि (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.height) {
                        height = SDL_min(wind->toplevel_bounds.height, height);
                    }
                } अन्यथा {
                    height = window->windowed.h;
                }

                यदि (!wind->scale_to_display) {
                    wind->requested.logical_height = height;
                } अन्यथा {
                    wind->requested.pixel_height = height;
                    height = wind->requested.logical_height = PixelToPoint(window, height);
                }
                height = SDL_max(height - (insets.शीर्ष + insets.bottom), 1);
            } अन्यथा यदि (new_configure_size) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_height = height + (insets.शीर्ष + insets.bottom);

                यदि (wind->scale_to_display) {
                    wind->requested.pixel_height = PointToPixel(window, wind->requested.logical_height);
                }
            }
        } अन्यथा {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            यदि (!wind->scale_to_display) {
                width = wind->requested.logical_width = window->floating.w;
                height = wind->requested.logical_height = window->floating.h;
            } अन्यथा {
                wind->requested.pixel_width = window->floating.w;
                wind->requested.pixel_height = window->floating.h;
                width = wind->requested.logical_width = PixelToPoint(window, window->floating.w);
                height = wind->requested.logical_height = PixelToPoint(window, window->floating.h);
            }
            width = SDL_max(width - (insets.डावा + insets.उजवा), 1);
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
        यदि (floating) {
            यदि (!wind->scale_to_display) {
                ApplyGeometryLimits(window, wind->requested.logical_width, wind->requested.logical_height, &wind->requested.logical_width, &wind->requested.logical_height);
            } अन्यथा {
                ApplyGeometryLimits(window, wind->requested.pixel_width, wind->requested.pixel_height, &wind->requested.pixel_width, &wind->requested.pixel_height);

                wind->requested.logical_width = PixelToPoint(window, wind->requested.pixel_width);
                wind->requested.logical_height = PixelToPoint(window, wind->requested.pixel_height);
            }
        }
    } अन्यथा {
        // Fullscreen windows know their exact size.
        यदि (width == 0 || height == 0) {
            width = wind->requested.logical_width;
            height = wind->requested.logical_height;
        } अन्यथा {
            wind->requested.logical_width = width;
            wind->requested.logical_height = height;
        }

        यदि (wind->scale_to_display) {
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

स्थिर शून्य handle_xdg_toplevel_close(शून्य *data, संरचना xdg_toplevel *xdg_toplevel)
{
    SDL_WindowData *window = (SDL_WindowData *)data;
    SDL_SendWindowEvent(window->sdlwindow, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
}

स्थिर शून्य handle_xdg_toplevel_configure_bounds(शून्य *data,
                                                 संरचना xdg_toplevel *xdg_toplevel,
                                                 int32_t width, int32_t height)
{
    SDL_WindowData *window = (SDL_WindowData *)data;
    window->toplevel_bounds.width = width;
    window->toplevel_bounds.height = height;
}

स्थिर शून्य handle_xdg_toplevel_wm_capabilities(शून्य *data,
                                                संरचना xdg_toplevel *xdg_toplevel,
                                                संरचना wl_array *capabilities)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    गणना xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        विकल्प (*wm_cap) {
        पक्ष XDG_TOPLEVEL_WM_CAPABILITIES_WINDOW_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_WINDOW_MENU;
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

स्थिर शून्य handle_xdg_popup_configure(शून्य *data,
                                       संरचना xdg_popup *xdg_popup,
                                       int32_t x,
                                       int32_t y,
                                       int32_t width,
                                       int32_t height)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    पूर्णाङ्क offset_x = 0, offset_y = 0;

    // Adjust the position if it was offset for libdecor
    AdjustPopupOffset(wind->sdlwindow, &offset_x, &offset_y);
    x -= offset_x;
    y -= offset_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    यदि (width == 0 || height == 0) {
        width = wind->sdlwindow->floating.w;
        height = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    यदि (width != wind->last_configure.width || height != wind->last_configure.height) {
        wind->requested.logical_width = width;
        wind->requested.logical_height = height;

        यदि (wind->scale_to_display) {
            wind->requested.pixel_width = PointToPixel(wind->sdlwindow, width);
            wind->requested.pixel_height = PointToPixel(wind->sdlwindow, height);
        }
    }

    यदि (wind->scale_to_display) {
        x = PointToPixel(wind->sdlwindow->parent, x);
        y = PointToPixel(wind->sdlwindow->parent, y);
    }

    SDL_SendWindowEvent(wind->sdlwindow, SDL_EVENT_WINDOW_MOVED, x, y);

    wind->last_configure.width = width;
    wind->last_configure.height = height;

    यदि (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME;
    }
}

स्थिर शून्य handle_xdg_popup_done(शून्य *data, संरचना xdg_popup *xdg_popup)
{
    SDL_WindowData *window = (SDL_WindowData *)data;
    SDL_SendWindowEvent(window->sdlwindow, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
}

स्थिर शून्य handle_xdg_popup_repositioned(शून्य *data,
                                          संरचना xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

स्थिर ध्रुव संरचना xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_done,
    handle_xdg_popup_repositioned
};

स्थिर शून्य handle_xdg_toplevel_decoration_configure(शून्य *data,
                                                     संरचना zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
                                                     uint32_t mode)
{
    SDL_Window *window = (SDL_Window *)data;
    SDL_WindowData *internal = window->internal;
    SDL_VideoDevice *device = SDL_GetVideoDevice();

    /* If the compositor tries to force CSD anyway, bail on direct XDG support
     * and fall back to libdecor, it will handle these events from then on.
     *
     * To do this we have to fully unmap, then map with libdecor loaded.
     */
    यदि (mode == ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE) {
        यदि (window->flags & SDL_WINDOW_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            प्रत्यागम;
        }
        यदि (!Wayland_LoadLibdecor(internal->waylandData, true)) {
            // libdecor isn't available, so no borders for you... oh well
            प्रत्यागम;
        }
        WAYLAND_wl_display_roundtrip(internal->waylandData->display);

        Wayland_HideWindow(device, window);
        internal->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_ShowWindow(device, window);
    }
}

स्थिर ध्रुव संरचना zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
    handle_xdg_toplevel_decoration_configure
};

#ifdef HAVE_LIBDECOR_H
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
स्थिर शून्य OverrideLibdecorLimits(SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    यदि (!libdecor_frame_get_min_content_size) {
        libdecor_frame_set_min_content_size(window->internal->shell_surface.libdecor.frame, window->min_w, window->min_h);
    }
#नोचेद्यदि !SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
    libdecor_frame_set_min_content_size(window->internal->shell_surface.libdecor.frame, window->min_w, window->min_h);
#endif
}

/*
 * NOTE: Retrieves the minimum content size limits, if the function for doing so is available.
 *       On versions of libdecor that lack the minimum content size retrieval function, this
 *       function is a no-op.
 *
 *       Can be replaced with a direct call if the minimum required version of libdecor is raised
 *       to 0.1.2 or higher.
 */
स्थिर शून्य LibdecorGetMinContentSize(संरचना libdecor_frame *frame, पूर्णाङ्क *min_w, पूर्णाङ्क *min_h)
{
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    यदि (libdecor_frame_get_min_content_size != रिक्त) {
        libdecor_frame_get_min_content_size(frame, min_w, min_h);
    }
#नोचेद्यदि SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
    libdecor_frame_get_min_content_size(frame, min_w, min_h);
#endif
}

स्थिर शून्य decoration_frame_configure(संरचना libdecor_frame *frame,
                                       संरचना libdecor_configuration *configuration,
                                       शून्य *user_data)
{
    SDL_WindowData *wind = (SDL_WindowData *)user_data;
    SDL_Window *window = wind->sdlwindow;

    गणना libdecor_window_state window_state;
    पूर्णाङ्क width, height;

    bool active = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    स्थिर ध्रुव गणना libdecor_window_state tiled_states = (LIBDECOR_WINDOW_STATE_TILED_डावा | LIBDECOR_WINDOW_STATE_TILED_उजवा |
                                                            LIBDECOR_WINDOW_STATE_TILED_शीर्ष | LIBDECOR_WINDOW_STATE_TILED_BOTTOM);

    यदि (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        LibdecorGetMinContentSize(frame, &wind->system_limits.min_width, &wind->system_limits.min_height);
    }

    // Window State
    यदि (libdecor_configuration_get_window_state(configuration, &window_state)) {
        fullscreen = (window_state & LIBDECOR_WINDOW_STATE_FULLSCREEN) != 0;
        maximized = (window_state & LIBDECOR_WINDOW_STATE_MAXIMIZED) != 0;
        active = (window_state & LIBDECOR_WINDOW_STATE_ACTIVE) != 0;
        tiled = (window_state & tiled_states) != 0;
#यदि SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
        suspended = (window_state & LIBDECOR_WINDOW_STATE_SUSPENDED) != 0;
#endif
#यदि SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
        resizing = (window_state & LIBDECOR_WINDOW_STATE_RESIZING) != 0;

        यदि (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_डावा) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_डावा;
        }
        यदि (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_उजवा) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_उजवा;
        }
        यदि (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_शीर्ष) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष;
        }
        यदि (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#endif
    }
    ध्रुव bool floating = !(fullscreen || maximized || tiled);

    UpdateWindowFullscreen(window, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from libdecor, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    यदि (active || !(window->flags & SDL_WINDOW_MINIMIZED)) {
        यदि (window->flags & SDL_WINDOW_MINIMIZED) {
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
    यदि (fullscreen) {
        यदि (!libdecor_configuration_get_content_size(configuration, frame, &width, &height)) {
            width = wind->requested.logical_width;
            height = wind->requested.logical_height;
        } अन्यथा {
            // Fullscreen windows know their exact size.
            wind->requested.logical_width = width;
            wind->requested.logical_height = height;

            यदि (wind->scale_to_display) {
                wind->requested.pixel_width = PointToPixel(window, width);
                wind->requested.pixel_height = PointToPixel(window, height);
            }
        }
    } अन्यथा {
        यदि (!(window->flags & SDL_WINDOW_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            यदि (!wind->scale_to_display) {
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
            यदि ((floating && (!wind->floating && !(window->flags & SDL_WINDOW_BORDERLESS))) ||
                !libdecor_configuration_get_content_size(configuration, frame, &width, &height)) {
                width = 0;
                height = 0;
            }

            ध्रुव bool new_configure_size = width != wind->last_configure.width || height != wind->last_configure.height;
            DetermineResizeAxis(wind, width, height, resizing);

            यदि (!width) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                यदि (floating) {
                    width = window->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    यदि (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.width) {
                        width = SDL_min(wind->toplevel_bounds.width, width);
                    }
                } अन्यथा {
                    width = window->windowed.w;
                }

                यदि (!wind->scale_to_display) {
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
                यदि (new_configure_size &&
                    !(wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME && wind->suspended != suspended)) {
                    wind->requested.logical_width = width;

                    यदि (wind->scale_to_display) {
                        wind->requested.pixel_width = PointToPixel(window, width);
                    }
                }
            }

            यदि (!height) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                यदि (floating) {
                    height = window->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    यदि (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.height) {
                        height = SDL_min(wind->toplevel_bounds.height, height);
                    }
                } अन्यथा {
                    height = window->windowed.h;
                }

                यदि (!wind->scale_to_display) {
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
                यदि (new_configure_size &&
                    !(wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME && wind->suspended != suspended)) {
                    wind->requested.logical_height = height;

                    यदि (wind->scale_to_display) {
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
        यदि (floating) {
            यदि (!wind->scale_to_display) {
                ApplyGeometryLimits(window, wind->requested.logical_width, wind->requested.logical_height, &wind->requested.logical_width, &wind->requested.logical_height);
            } अन्यथा {
                ApplyGeometryLimits(window, wind->requested.pixel_width, wind->requested.pixel_height, &wind->requested.pixel_width, &wind->requested.pixel_height);

                wind->requested.logical_width = PixelToPoint(window, wind->requested.pixel_width);
                wind->requested.logical_height = PixelToPoint(window, wind->requested.pixel_height);
            }
        }
    }

    // Store the new state.
    ध्रुव bool started_resize = !wind->resizing && resizing;
    wind->last_configure.width = width;
    wind->last_configure.height = height;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->active = active;
    window->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#यदि SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
    गणना libdecor_wm_capabilities caps;
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    यदि (libdecor_frame_get_wm_capabilities) {
        caps = libdecor_frame_get_wm_capabilities(wind->shell_surface.libdecor.frame);
#अन्यथा
    caps = libdecor_frame_get_wm_capabilities(wind->shell_surface.libdecor.frame);
    {
#endif
        wind->wm_caps = 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_WINDOW_MENU ? WAYLAND_WM_CAPS_WINDOW_MENU : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MAXIMIZE ? WAYLAND_WM_CAPS_MAXIMIZE : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_FULLSCREEN ? WAYLAND_WM_CAPS_FULLSCREEN : 0;
        wind->wm_caps |= caps & LIBDECOR_WM_CAPABILITIES_MINIMIZE ? WAYLAND_WM_CAPS_MINIMIZE : 0;
    }
#endif

    यदि (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        ConfigureWindowGeometry(window);
        संरचना libdecor_state *state = libdecor_state_new(wind->current.logical_width, wind->current.logical_height);
        libdecor_frame_commit(frame, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        यदि (started_resize) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }

    यदि (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME;
    }
}

स्थिर शून्य decoration_frame_close(संरचना libdecor_frame *frame, शून्य *user_data)
{
    SDL_SendWindowEvent(((SDL_WindowData *)user_data)->sdlwindow, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
}

स्थिर शून्य decoration_frame_commit(संरचना libdecor_frame *frame, शून्य *user_data)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_WindowData *wind = (SDL_WindowData *)user_data;
    यदि (!wind->suspended && wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        SDL_SendWindowEvent(wind->sdlwindow, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }
}

स्थिर शून्य decoration_dismiss_popup(संरचना libdecor_frame *frame, ध्रुव वर्ण *seat_name, शून्य *user_data)
{
    // NOP
}

#यदि SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
स्थिर शून्य decoration_frame_bounds(संरचना libdecor_frame *frame, पूर्णाङ्क width, पूर्णाङ्क height, शून्य *user_data)
{
    SDL_WindowData *window = (SDL_WindowData *)user_data;
    window->toplevel_bounds.width = width;
    window->toplevel_bounds.height = height;
}
#endif

स्थिर संरचना libdecor_frame_interface libdecor_frame_interface = {
    decoration_frame_configure,
    decoration_frame_close,
    decoration_frame_commit,
    decoration_dismiss_popup,
#यदि SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
    decoration_frame_bounds
#endif
};
#endif

स्थिर शून्य Wayland_HandlePreferredScaleChanged(SDL_WindowData *window_data, द्विगुण factor)
{
    ध्रुव द्विगुण old_factor = window_data->scale_factor;

    // Round the scale factor if viewports aren't available.
    यदि (!window_data->viewport) {
        factor = SDL_ceil(factor);
    }

    यदि (factor != old_factor) {
        window_data->scale_factor = factor;

        यदि (window_data->scale_to_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            यदि (window_data->floating) {
                /* Some compositors will send a configure event immediately after a scale event, however,
                 * this event can contain the old logical size, and should be ignored, or the window can
                 * incorrectly change size when moved between displays with differing scale factors.
                 *
                 * Store the last requested logical size as the last configure size, so a configure event
                 * with the old size will be ignored. Configure sizes are in window geometry space,
                 * so subtract any border insets.
                 */
                BorderInsets insets;
                GetBorderInsets(window_data->sdlwindow, &insets);
                window_data->last_configure.width = SDL_max(window_data->requested.logical_width - (insets.डावा + insets.उजवा), 1);
                window_data->last_configure.height = SDL_max(window_data->requested.logical_height - (insets.शीर्ष + insets.bottom), 1);

                window_data->requested.logical_width = PixelToPoint(window_data->sdlwindow, window_data->requested.pixel_width);
                window_data->requested.logical_height = PixelToPoint(window_data->sdlwindow, window_data->requested.pixel_height);
            } अन्यथा {
                window_data->requested.pixel_width = PointToPixel(window_data->sdlwindow, window_data->requested.logical_width);
                window_data->requested.pixel_height = PointToPixel(window_data->sdlwindow, window_data->requested.logical_height);
            }
        }

        यदि (window_data->sdlwindow->flags & SDL_WINDOW_वरचा_PIXEL_DENSITY || window_data->scale_to_display) {
            ConfigureWindowGeometry(window_data->sdlwindow);
            CommitLibdecorFrame(window_data->sdlwindow);
        }
    }
}

स्थिर शून्य Wayland_MaybeUpdateScaleFactor(SDL_WindowData *window)
{
    द्विगुण factor;
    पूर्णाङ्क i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    यदि (window->fractional_scale || wl_surface_get_version(window->surface) >= WL_SURFACE_PREFERRED_BUFFER_SCALE_SINCE_VERSION) {
        प्रत्यागम;
    }

    यदि (window->अंक_outputs != 0) {
        // Check every display's factor, use the highest
        factor = 0.0;
        प्रति (i = 0; i < window->अंक_outputs; i++) {
            SDL_DisplayData *internal = window->outputs[i];
            factor = SDL_max(factor, internal->scale_factor);
        }
    } अन्यथा {
        // All outputs removed, just fall back.
        factor = window->scale_factor;
    }

    Wayland_HandlePreferredScaleChanged(window, factor);
}

शून्य Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data)
{
    प्रति (पूर्णाङ्क i = 0; i < window->अंक_outputs; i++) {
        यदि (window->outputs[i] == display_data) { // remove this one
            यदि (i == (window->अंक_outputs - 1)) {
                window->outputs[i] = रिक्त;
            } अन्यथा {
                SDL_memmove(&window->outputs[i],
                            &window->outputs[i + 1],
                            परिमाण(SDL_DisplayData *) * ((window->अंक_outputs - i) - 1));
            }
            window->अंक_outputs--;
            i--;
        }
    }

    यदि (window->अंक_outputs == 0) {
        SDL_free(window->outputs);
        window->outputs = रिक्त;
    } अन्यथा यदि (!window->is_fullscreen || window->अंक_outputs == 1) {
        Wayland_UpdateWindowPosition(window->sdlwindow);
        Wayland_MaybeUpdateScaleFactor(window);
    }
}

स्थिर शून्य handle_surface_enter(शून्य *data, संरचना wl_surface *surface, संरचना wl_output *output)
{
    SDL_WindowData *window = data;
    SDL_DisplayData *internal = wl_output_get_user_data(output);
    SDL_DisplayData **new_outputs;

    यदि (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        प्रत्यागम;
    }

    new_outputs = SDL_realloc(window->outputs,
                              परिमाण(SDL_DisplayData *) * (window->अंक_outputs + 1));
    यदि (!new_outputs) {
        प्रत्यागम;
    }
    window->outputs = new_outputs;
    window->outputs[window->अंक_outputs++] = internal;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    यदि (!window->is_fullscreen || window->अंक_outputs == 1) {
        Wayland_UpdateWindowPosition(window->sdlwindow);
        Wayland_MaybeUpdateScaleFactor(window);
    }
}

स्थिर शून्य handle_surface_leave(शून्य *data, संरचना wl_surface *surface, संरचना wl_output *output)
{
    SDL_WindowData *window = (SDL_WindowData *)data;

    यदि (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        प्रत्यागम;
    }

    Wayland_RemoveOutputFromWindow(window, (SDL_DisplayData *)wl_output_get_user_data(output));
}

स्थिर शून्य handle_surface_preferred_buffer_scale(शून्य *data, संरचना wl_surface *wl_surface, int32_t factor)
{
    SDL_WindowData *wind = data;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    यदि (!wind->fractional_scale) {
        Wayland_HandlePreferredScaleChanged(data, (द्विगुण)factor);
    }
}

स्थिर शून्य handle_surface_preferred_buffer_transform(शून्य *data, संरचना wl_surface *wl_surface, uint32_t transform)
{
    // Nothing to do here.
}

स्थिर ध्रुव संरचना wl_surface_listener surface_listener = {
    handle_surface_enter,
    handle_surface_leave,
    handle_surface_preferred_buffer_scale,
    handle_surface_preferred_buffer_transform
};

स्थिर शून्य handle_fractional_scale_preferred(शून्य *data, संरचना wp_fractional_scale_v1 *wp_fractional_scale_v1, uint32_t scale)
{
    ध्रुव द्विगुण factor = (द्विगुण)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_HandlePreferredScaleChanged(data, factor);
}

स्थिर ध्रुव संरचना wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

स्थिर शून्य frog_preferred_metadata_handler(शून्य *data, संरचना frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
                                            uint32_t output_display_primary_red_x, uint32_t output_display_primary_red_y,
                                            uint32_t output_display_primary_green_x, uint32_t output_display_primary_green_y,
                                            uint32_t output_display_primary_blue_x, uint32_t output_display_primary_blue_y,
                                            uint32_t output_white_point_x, uint32_t output_white_point_y,
                                            uint32_t max_luminance, uint32_t min_luminance,
                                            uint32_t max_full_frame_luminance)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
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
    पक्ष FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SCRGB_LINEAR:
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
    SDL_SetWindowHDRProperties(wind->sdlwindow, &HDR, true);
}

स्थिर ध्रुव संरचना frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


स्थिर शून्य handle_surface_feedback_preferred_changed2(शून्य *data,
                                                       संरचना wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t identity_hi, uint32_t identity_lo)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    Wayland_GetColorInfoForWindow(wind, false);
}

स्थिर शून्य handle_surface_feedback_preferred_changed(शून्य *data,
                                                      संरचना wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t identity)
{
    handle_surface_feedback_preferred_changed2(data, wp_color_management_surface_feedback_v1, 0, identity);
}

स्थिर ध्रुव संरचना wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_changed,
    handle_surface_feedback_preferred_changed2
};

स्थिर शून्य Wayland_SetKeyboardFocus(SDL_Window *window, bool set_focus)
{
    SDL_Window *toplevel = window;

    // Find the toplevel parent
    यावत् (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    यदि (set_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    प्रत्यागम true; // just succeed, the real work is done elsewhere.
}

स्थिर संरचना xdg_toplevel *GetToplevelForWindow(SDL_WindowData *wind)
{
    यदि (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#ifdef HAVE_LIBDECOR_H
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
            प्रत्यागम libdecor_frame_get_xdg_toplevel(wind->shell_surface.libdecor.frame);
        } अन्यथा
#endif
            यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                प्रत्यागम wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    प्रत्यागम रिक्त;
}

bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window)
{
    SDL_WindowData *child_data = window->internal;
    SDL_WindowData *parent_data = parent_window ? parent_window->internal : रिक्त;

    child_data->reparenting_required = false;

    यदि (parent_data && parent_data->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        child_data->reparenting_required = true;
        प्रत्यागम true;
    }

    संरचना xdg_toplevel *child_toplevel = GetToplevelForWindow(child_data);
    संरचना xdg_toplevel *parent_toplevel = GetToplevelForWindow(parent_data);

    यदि (child_toplevel) {
        xdg_toplevel_set_parent(child_toplevel, parent_toplevel);
    }

    प्रत्यागम true;
}

bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_WindowData *data = window->internal;
    SDL_WindowData *parent_data = window->parent->internal;

    यदि (parent_data->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        data->reparenting_required = true;
        प्रत्यागम true;
    } अन्यथा {
        data->reparenting_required = false;
    }

    संरचना xdg_toplevel *toplevel = GetToplevelForWindow(data);

    यदि (toplevel) {
        यदि (viddata->xdg_wm_dialog_v1) {
            यदि (modal) {
                यदि (!data->xdg_dialog_v1) {
                    data->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_set_modal(data->xdg_dialog_v1);
            } अन्यथा यदि (data->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(data->xdg_dialog_v1);
            }
        }
    }

    प्रत्यागम true;
}

स्थिर शून्य Wayland_RegisterToplevelForSession(SDL_WindowData *data)
{
    संरचना xdg_toplevel *toplevel = GetToplevelForWindow(data);
    यदि (!toplevel) {
        प्रत्यागम;
    }

    ध्रुव वर्ण *id = SDL_GetStringProperty(data->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_WINDOW_ID_STRING, रिक्त);
    यदि (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_VideoData *viddata = viddev->internal;

        यदि (viddata->xdg_toplevel_tag_manager) {
            xdg_toplevel_tag_manager_v1_set_toplevel_tag(viddata->xdg_toplevel_tag_manager, toplevel, id);
        }

        यदि (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            यदि (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    प्रति (SDL_Window *w = viddev->windows; w; w = w->next) {
                        SDL_WindowData *d = w->internal;
                        यदि (d->session_id && SDL_strcmp(d->session_id, id) == 0) {
                            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Duplicate window ID string %s found; window will not be added to session", id);
                            प्रत्यागम;
                        }
                    }
                }

                data->xdg_toplevel_session = xdg_session_v1_restore_toplevel(viddata->xdg_session, toplevel, id);
                data->session_id = SDL_strdup(id);
            }
        }
    }
}

स्थिर शून्य Wayland_DestroyToplevelSession(SDL_WindowData *data)
{
    SDL_VideoData *viddata = data->waylandData;

    यदि (data->xdg_toplevel_session) {
        ध्रुव वर्ण *id = SDL_GetStringProperty(data->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_WINDOW_ID_STRING, रिक्त);

        // If the ID string was cleared, remove the window from the session.
        यदि (!id || *id == '\0') {
            xdg_session_v1_remove_toplevel(viddata->xdg_session, data->session_id);
        }

        xdg_toplevel_session_v1_destroy(data->xdg_toplevel_session);
        data->xdg_toplevel_session = रिक्त;

        SDL_free(data->session_id);
        data->session_id = रिक्त;
    }
}

स्थिर शून्य show_hide_sync_handler(शून्य *data, संरचना wl_callback *callback, uint32_t callback_data)
{
    // Get the window from the ID as it may have been destroyed
    SDL_WindowID windowID = (SDL_WindowID)((uintptr_t)data);
    SDL_Window *window = SDL_GetWindowFromID(windowID);

    यदि (window && window->internal) {
        SDL_WindowData *wind = window->internal;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

स्थिर संरचना wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

स्थिर शून्य exported_handle_handler(शून्य *data, संरचना zxdg_exported_v2 *zxdg_exported_v2, ध्रुव वर्ण *handle)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    SDL_PropertiesID props = SDL_GetWindowProperties(wind->sdlwindow);

    SDL_SetStringProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

स्थिर संरचना zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

शून्य Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *c = _this->internal;
    SDL_WindowData *data = window->internal;
    SDL_PropertiesID props = SDL_GetWindowProperties(window);

    // Custom surfaces don't get toplevels and are always considered 'shown'; nothing to do here.
    यदि (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
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
    यदि (window->parent) {
        यदि (window->parent->internal->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
            data->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING;
            प्रत्यागम;
        }
    }

    // Always roundtrip to ensure there are no pending buffer attachments.
    कुरु {
        WAYLAND_wl_display_roundtrip(c->display);
    } यावत् (data->show_hide_sync_required);

    data->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE;

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
    wl_surface_attach(data->surface, रिक्त, 0, 0);
    wl_surface_commit(data->surface);

    // Create the shell surface and map the toplevel/popup
#ifdef HAVE_LIBDECOR_H
    यदि (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        data->shell_surface.libdecor.frame = libdecor_decorate(c->shell.libdecor,
                                                               data->surface,
                                                               &libdecor_frame_interface,
                                                               data);
        यदि (!data->shell_surface.libdecor.frame) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } अन्यथा {
            libdecor_frame_set_app_id(data->shell_surface.libdecor.frame, data->app_id);
            libdecor_frame_map(data->shell_surface.libdecor.frame);
            यदि (window->flags & SDL_WINDOW_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_frame_set_visibility(data->shell_surface.libdecor.frame, false);
            }

            यदि (c->zxdg_exporter_v2) {
                data->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, data->surface);
                zxdg_exported_v2_add_listener(data->exported, &exported_v2_listener, data);
            }

            यदि (c->xdg_toplevel_icon_manager_v1 && data->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_set_icon(_this->internal->xdg_toplevel_icon_manager_v1,
                                                      libdecor_frame_get_xdg_toplevel(data->shell_surface.libdecor.frame),
                                                      data->xdg_toplevel_icon_v1);
            }

            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, libdecor_frame_get_xdg_surface(data->shell_surface.libdecor.frame));
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_POINTER, libdecor_frame_get_xdg_toplevel(data->shell_surface.libdecor.frame));
        }
    } अन्यथा
#endif
    यदि (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        data->shell_surface.xdg.surface = xdg_wm_base_get_xdg_surface(c->shell.xdg, data->surface);
        xdg_surface_set_user_data(data->shell_surface.xdg.surface, data);
        xdg_surface_add_listener(data->shell_surface.xdg.surface, &_xdg_surface_listener, data);
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, data->shell_surface.xdg.surface);

        यदि (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_Window *parent = window->parent;
            SDL_WindowData *parent_data = parent->internal;
            संरचना xdg_surface *parent_xdg_surface = रिक्त;
            पूर्णाङ्क position_x = 0, position_y = 0;

            // Configure the popup parameters
#ifdef HAVE_LIBDECOR_H
            यदि (parent_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                parent_xdg_surface = libdecor_frame_get_xdg_surface(parent_data->shell_surface.libdecor.frame);
            } अन्यथा
#endif
            यदि (parent_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    parent_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                parent_xdg_surface = parent_data->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            data->shell_surface.xdg.popup.xdg_positioner = xdg_wm_base_create_positioner(c->shell.xdg);
            xdg_positioner_set_anchor(data->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_शीर्ष_डावा);
            SDL_Rect parent_geometry;
            GetWindowGeometry(parent->internal, &parent_geometry);
            xdg_positioner_set_anchor_rect(data->shell_surface.xdg.popup.xdg_positioner, 0, 0, parent_geometry.w, parent_geometry.h);

            ध्रुव Uint32 constraint = window->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_set_constraint_adjustment(data->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_set_gravity(data->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_उजवा);
            xdg_positioner_set_size(data->shell_surface.xdg.popup.xdg_positioner, data->current.logical_width, data->current.logical_height);

            // Set the popup initial position
            position_x = window->last_position_pending ? window->pending.x : window->x;
            position_y = window->last_position_pending ? window->pending.y : window->y;
            EnsurePopupPositionIsValid(window, &position_x, &position_y);
            यदि (data->scale_to_display) {
                position_x = PixelToPoint(window->parent, position_x);
                position_y = PixelToPoint(window->parent, position_y);
            }
            AdjustPopupOffset(window, &position_x, &position_y);
            xdg_positioner_set_offset(data->shell_surface.xdg.popup.xdg_positioner, position_x, position_y);

            // Assign the popup role
            data->shell_surface.xdg.popup.xdg_popup = xdg_surface_get_popup(data->shell_surface.xdg.surface,
                                                                                parent_xdg_surface,
                                                                                data->shell_surface.xdg.popup.xdg_positioner);
            xdg_popup_add_listener(data->shell_surface.xdg.popup.xdg_popup, &_xdg_popup_listener, data);

            यदि (window->flags & SDL_WINDOW_TOOLTIP) {
                संरचना wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_add(region, 0, 0, 0, 0);
                wl_surface_set_आदान_region(data->surface, region);
                wl_region_destroy(region);
            } अन्यथा यदि ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
                Wayland_SetKeyboardFocus(window, true);
            }

            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POPUP_POINTER, data->shell_surface.xdg.popup.xdg_popup);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POSITIONER_POINTER, data->shell_surface.xdg.popup.xdg_positioner);
        } अन्यथा {
            data->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(data->shell_surface.xdg.surface);
            xdg_toplevel_set_app_id(data->shell_surface.xdg.toplevel.xdg_toplevel, data->app_id);
            xdg_toplevel_add_listener(data->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, data);

            // Create the window decorations
            यदि (c->decoration_manager) {
                data->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, data->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_add_listener(data->server_decoration, &xdg_toplevel_decoration_listener, window);
                ध्रुव गणना zxdg_toplevel_decoration_v1_mode mode = !(window->flags & SDL_WINDOW_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_set_mode(data->server_decoration, mode);
            }

            यदि (c->zxdg_exporter_v2) {
                data->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, data->surface);
                zxdg_exported_v2_add_listener(data->exported, &exported_v2_listener, data);
            }

            यदि (c->xdg_toplevel_icon_manager_v1 && data->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_set_icon(_this->internal->xdg_toplevel_icon_manager_v1,
                                                      data->shell_surface.xdg.toplevel.xdg_toplevel,
                                                      data->xdg_toplevel_icon_v1);
            }

            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_POINTER, data->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    // Restore state that was set prior to this call
    Wayland_RegisterToplevelForSession(data);
    Wayland_SetWindowParent(_this, window, window->parent);

    यदि (window->flags & SDL_WINDOW_MODAL) {
        Wayland_SetWindowModal(_this, window, true);
    }

    Wayland_SetWindowTitle(_this, window);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#ifdef HAVE_LIBDECOR_H
    यदि (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (data->shell_surface.libdecor.frame) {
            यावत् (data->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
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
#endif
        यदि (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP || data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Unlike libdecor we need to call this explicitly to prevent a deadlock.
         * libdecor will call this as part of their configure event!
         * -flibit
         */
        wl_surface_commit(data->surface);
        यदि (data->shell_surface.xdg.surface) {
            यावत् (data->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
                यदि (WAYLAND_wl_display_dispatch(c->display) < 0) {
                    यदि (!Wayland_HandleDisplayDisconnected(_this)) {
                        प्रत्यागम;
                    }
                }
            }
        }
    } अन्यथा {
        // Nothing to see here, just commit.
        wl_surface_commit(data->surface);
    }

    // Make sure the window can't be resized to 0, or it can be spuriously closed by the window manager.
    data->system_limits.min_width = SDL_max(data->system_limits.min_width, 1);
    data->system_limits.min_height = SDL_max(data->system_limits.min_height, 1);

    /* Unlike the rest of window state we have to set this _after_ flushing the
     * display, because we need to create the decorations before possibly hiding
     * them immediately afterward.
     */
#ifdef HAVE_LIBDECOR_H
    यदि (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        यदि (window->windowed.w < data->system_limits.min_width ||
            window->windowed.h < data->system_limits.min_height) {

            // Warn if the window frame will be larger than the content surface.
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "Window dimensions (%i, %i) are smaller than the system enforced minimum (%i, %i); window borders will be larger than the content surface.",
                        window->windowed.w, window->windowed.h, data->system_limits.min_width, data->system_limits.min_height);

            data->current.logical_width = SDL_max(window->windowed.w, data->system_limits.min_width);
            data->current.logical_height = SDL_max(window->windowed.h, data->system_limits.min_height);
            CommitLibdecorFrame(window);
        }
    }
#endif
    Wayland_SetWindowResizable(_this, window, !!(window->flags & SDL_WINDOW_RESIZABLE));

    // We're finally done putting the window together, raise if possible
    यदि (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true)) {
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
                                       data->surface);

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
    यदि (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        data->surface_frame_callback = wl_surface_frame(data->surface);
        wl_callback_add_listener(data->surface_frame_callback, &surface_frame_listener, data);
    }

    data->show_hide_sync_required = true;
    संरचना wl_callback *cb = wl_display_sync(_this->internal->display);
    wl_callback_add_listener(cb, &show_hide_sync_listener, (शून्य *)((uintptr_t)window->id));

    data->showing_window = true;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    data->showing_window = false;

    // Send an exposure event to signal that the client should draw.
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
}

स्थिर शून्य Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_Window *popup)
{
    SDL_WindowData *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    यदि (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_WINDOW)) {
        प्रत्यागम;
    }
    popupdata = popup->internal;
    यदि (!popupdata) {
        प्रत्यागम;
    }

    // This may already be freed by a parent popup!
    यदि (popupdata->shell_surface.xdg.popup.xdg_popup == रिक्त) {
        प्रत्यागम;
    }

    यदि ((popup->flags & SDL_WINDOW_POPUP_MENU) && !(popup->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        ध्रुव bool set_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_SetKeyboardFocus(new_focus, set_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = रिक्त;
    popupdata->shell_surface.xdg.popup.xdg_positioner = रिक्त;

    SDL_PropertiesID props = SDL_GetWindowProperties(popup);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POPUP_POINTER, रिक्त);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POSITIONER_POINTER, रिक्त);
}

शून्य Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *wind = window->internal;
    SDL_PropertiesID props = SDL_GetWindowProperties(window);

    // Custom surfaces have nothing to destroy and are always considered to be 'shown'; nothing to do here.
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        प्रत्यागम;
    }

    /* The window was shown, but the sync point hasn't yet been reached.
     * Pump events to avoid a possible protocol violation.
     */
    यदि (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(data->display);
    }

    wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_HIDDEN;

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

        SDL_SetStringProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, रिक्त);
    }

    यदि (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = रिक्त;
    }

#ifdef HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (wind->shell_surface.libdecor.frame) {
            libdecor_frame_unref(wind->shell_surface.libdecor.frame);

            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, रिक्त);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_POINTER, रिक्त);
        }
    } अन्यथा
#endif
    {
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, window);
        } अन्यथा यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_POINTER, रिक्त);
        }

        यदि (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, रिक्त);
        }
    }

    // Attach a null buffer to unmap the surface.
    यदि (wind->mask.surface) {
        wl_surface_attach(wind->mask.surface, रिक्त, 0, 0);
        wl_surface_commit(wind->mask.surface);
    }
    wl_surface_attach(wind->surface, रिक्त, 0, 0);
    wl_surface_commit(wind->surface);

    // Need to destroy the session object after unmapping the window, or the state may not be saved.
    Wayland_DestroyToplevelSession(wind);

    SDL_zero(wind->shell_surface);
    SDL_zero(wind->explicit_geometry);
    wind->show_hide_sync_required = true;
    संरचना wl_callback *cb = wl_display_sync(_this->internal->display);
    wl_callback_add_listener(cb, &show_hide_sync_listener, (शून्य *)((uintptr_t)window->id));
}

स्थिर शून्य handle_xdg_activation_done(शून्य *data,
                                       संरचना xdg_activation_token_v1 *xdg_activation_token_v1,
                                       ध्रुव वर्ण *token)
{
    SDL_WindowData *window = data;
    यदि (xdg_activation_token_v1 == window->activation_token) {
        xdg_activation_v1_activate(window->waylandData->activation_manager,
                                   token,
                                   window->surface);
        xdg_activation_token_v1_destroy(window->activation_token);
        window->activation_token = रिक्त;
    }
}

स्थिर ध्रुव संरचना xdg_activation_token_v1_listener xdg_activation_listener = {
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
स्थिर शून्य Wayland_activate_window(SDL_VideoData *data, SDL_WindowData *target_wind, bool set_serial)
{
    SDL_WaylandSeat *seat = data->last_implicit_grab_seat;
    SDL_WindowData *focus = रिक्त;

    यदि (seat) {
        focus = seat->keyboard.focus;
        यदि (!focus) {
            focus = seat->pointer.focus;
        }
    }

    संरचना wl_surface *requesting_surface = focus ? focus->surface : रिक्त;

    यदि (data->activation_manager) {
        यदि (target_wind->activation_token) {
            // We're about to overwrite this with a new request
            xdg_activation_token_v1_destroy(target_wind->activation_token);
        }

        target_wind->activation_token = xdg_activation_v1_get_activation_token(data->activation_manager);
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
        यदि (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_set_surface(target_wind->activation_token, requesting_surface);
        }
        यदि (set_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_set_serial(target_wind->activation_token, seat->last_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(target_wind->activation_token);
    }
}

शून्य Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_WindowData *wind = window->internal;

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
    Wayland_activate_window(_this->internal, window->internal, true);
}

bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation)
{
    /* Not setting the serial will specify 'urgency' without switching focus as per
     * https://gitlab.freedesktop.org/wayland/wayland-protocols/-/merge_requests/9#note_854977
     */
    Wayland_activate_window(_this->internal, window->internal, false);
    प्रत्यागम true;
}

SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *wind = window->internal;
    संरचना wl_output *output = display->internal->output;

    // Custom surfaces have no toplevel to make fullscreen.
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        प्रत्यागम SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    यदि (wind->showing_window && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
    }

    यदि (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->internal->display);
    }

    // Flushing old events pending a new one, ignore this request.
    यदि (wind->drop_fullscreen_requests) {
        प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_requests = true;
    FlushPendingEvents(window);
    wind->drop_fullscreen_requests = false;

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
        यदि (!window->fullscreen_exclusive) {
            यदि (window->undefined_x || window->undefined_y ||
                (wind->अंक_outputs && !window->last_position_pending)) {
                output = रिक्त;
            }
        }

        // Commit to set any pending size or limit data.
        यदि (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        SetFullscreen(window, output, !!fullscreen);
    } अन्यथा यदि (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        यदि (wind->last_displayID != display->id) {
            wind->fullscreen_was_positioned = true;
            SetFullscreen(window, output, true);
        } अन्यथा {
            ConfigureWindowGeometry(window);
            CommitLibdecorFrame(window);

            प्रत्यागम SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    प्रत्यागम SDL_FULLSCREEN_PENDING;
}

शून्य Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    // Drop restore requests when showing the window.
    यदि (wind->showing_window) {
        प्रत्यागम;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    यदि (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) &&
        !wind->pending_state_deadline_मोजणी) {
        प्रत्यागम;
    }

#ifdef HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (!wind->shell_surface.libdecor.frame) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_frame_unset_maximized(wind->shell_surface.libdecor.frame);
        AddPendingStateSync(wind);
    } अन्यथा
#endif
        // Note that xdg-shell does NOT provide a way to unset minimize!
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel == रिक्त) {
                प्रत्यागम; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            AddPendingStateSync(wind);
        }
}

शून्य Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
{
    SDL_WindowData *wind = window->internal;
    ध्रुव SDL_VideoData *viddata = (ध्रुव SDL_VideoData *)_this->internal;

#ifdef HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (wind->shell_surface.libdecor.frame) {
            libdecor_frame_set_visibility(wind->shell_surface.libdecor.frame, bordered);
        }
    } अन्यथा
#endif
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि ((viddata->decoration_manager) && (wind->server_decoration)) {
            ध्रुव गणना zxdg_toplevel_decoration_v1_mode mode = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_set_mode(wind->server_decoration, mode);
        }
    }
}

शून्य Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *wind = window->internal;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    SetMinMaxDimensions(window);
    CommitLibdecorFrame(window);

    यदि (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        wind->pending_state_commit = true;
    }
}

शून्य Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    यदि (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->internal->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    यदि (!(window->flags & SDL_WINDOW_FULLSCREEN) && (window->flags & SDL_WINDOW_MAXIMIZED) &&
        !wind->pending_state_deadline_मोजणी) {
        प्रत्यागम;
    }

#ifdef HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (!wind->shell_surface.libdecor.frame) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        यदि (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_frame_set_maximized(wind->shell_surface.libdecor.frame);
        AddPendingStateSync(wind);
    } अन्यथा
#endif
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel == रिक्त) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        यदि (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_set_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        AddPendingStateSync(wind);
    }
}

शून्य Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    यदि (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        प्रत्यागम;
    }

#ifdef HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (!wind->shell_surface.libdecor.frame) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_frame_set_minimized(wind->shell_surface.libdecor.frame);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
    } अन्यथा
#endif
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel == रिक्त) {
            प्रत्यागम; // Can't do anything yet, wait for ShowWindow
        }
        xdg_toplevel_set_minimized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
    }
}

bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = _this->internal;

    /* This may look suspiciously like SetWindowGrab, despite SetMouseRect not
     * implicitly doing a grab. And you're right! Wayland doesn't let us mess
     * around with mouse focus whatsoever, so it just happens to be that the
     * work that we can do in these two functions ends up being the same.
     *
     * Just know that this call lets you confine with a rect, SetWindowGrab
     * lets you confine without a rect.
     */
    यदि (!data->pointer_constraints) {
        प्रत्यागम SDL_SetError("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_DisplayUpdatePointerGrabs(data, window->internal);
    प्रत्यागम true;
}

bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_VideoData *data = _this->internal;
    यदि (!data->pointer_constraints) {
        प्रत्यागम SDL_SetError("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_DisplayUpdatePointerGrabs(data, window->internal);
    प्रत्यागम true;
}

bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_VideoData *data = _this->internal;
    यदि (!data->किल्ली_inhibitor_manager) {
        प्रत्यागम SDL_SetError("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(data, window->internal);
    प्रत्यागम true;
}

bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags)
{
    SDL_WindowData *data = window->internal;

    // Don't try to reconfigure mapped windows, unless they are custom or external.
    यदि (data->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN &&
        data->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        // Window is already mapped; abort.
        प्रत्यागम false;
    }

    /* The caller guarantees that only one of the GL or Vulkan flags will be set.
     * Note that Vulkan doesn't require any specific configuration, so only EGL
     * objects are added and removed as required.
     */
    यदि (flags & SDL_WINDOW_OPENGL) {
        यदि (!data->egl_window) {
            data->egl_window = WAYLAND_wl_egl_window_create(data->surface, data->current.pixel_width, data->current.pixel_height);
        }

#ifdef SDL_VIDEO_OPENGL_EGL
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)data->egl_window);

        यदि (data->egl_surface == EGL_NO_SURFACE) {
            प्रत्यागम false; // SDL_EGL_CreateSurface should have set the error.
        }
#endif

        यदि (!data->gles_swap_frame_event_queue) {
            data->gles_swap_frame_event_queue = WAYLAND_wl_display_create_queue(data->waylandData->display);
            data->gles_swap_frame_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(data->surface);
            WAYLAND_wl_proxy_set_queue((संरचना wl_proxy *)data->gles_swap_frame_surface_wrapper, data->gles_swap_frame_event_queue);
            data->gles_swap_frame_callback = wl_surface_frame(data->gles_swap_frame_surface_wrapper);
            wl_callback_add_listener(data->gles_swap_frame_callback, &gles_swap_frame_listener, data);
        }
    } अन्यथा {
#ifdef SDL_VIDEO_OPENGL_EGL
        यदि (data->egl_surface) {
            SDL_EGL_DestroySurface(_this, data->egl_surface);
            data->egl_surface = EGL_NO_SURFACE;
        }
#endif

        यदि (data->egl_window) {
            WAYLAND_wl_egl_window_destroy(data->egl_window);
            data->egl_window = रिक्त;
        }

        यदि (data->gles_swap_frame_callback) {
            wl_callback_destroy(data->gles_swap_frame_callback);
            data->gles_swap_frame_callback = रिक्त;
        }

        यदि (data->gles_swap_frame_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(data->gles_swap_frame_surface_wrapper);
            data->gles_swap_frame_surface_wrapper = रिक्त;
        }

        यदि (data->gles_swap_frame_event_queue) {
            WAYLAND_wl_event_queue_destroy(data->gles_swap_frame_event_queue);
            data->gles_swap_frame_event_queue = रिक्त;
        }
    }

    प्रत्यागम true;
}

bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *data;
    SDL_VideoData *c = _this->internal;
    संरचना wl_surface *external_surface = (संरचना wl_surface *)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_WL_SURFACE_POINTER,
                                                                               (संरचना wl_surface *)SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", रिक्त));
    ध्रुव bool custom_surface_role = (external_surface != रिक्त) || SDL_GetBooleanProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    ध्रुव bool create_egl_window = !!(window->flags & SDL_WINDOW_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_CREATE_EGL_WINDOW_BOOLEAN, false);

    data = SDL_calloc(1, परिमाण(*data));
    यदि (!data) {
        प्रत्यागम false;
    }

    window->internal = data;
    data->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    यदि (window->x == SDL_WINDOWPOS_UNDEFINED) {
        window->x = 0;
    }
    यदि (window->y == SDL_WINDOWPOS_UNDEFINED) {
        window->y = 0;
    }

    data->waylandData = c;
    data->sdlwindow = window;

    // Default to all capabilities
    data->wm_caps = WAYLAND_WM_CAPS_ALL;

    data->scale_factor = 1.0;

    यदि (SDL_WINDOW_IS_POPUP(window)) {
        data->scale_to_display = window->parent->internal->scale_to_display;
        data->scale_factor = window->parent->internal->scale_factor;
        EnsurePopupPositionIsValid(window, &window->x, &window->y);
    } अन्यथा {
        प्रति (पूर्णाङ्क i = 0; i < _this->अंक_displays; i++) {
            data->scale_factor = SDL_max(data->scale_factor, _this->displays[i]->internal->scale_factor);
        }
    }

    data->outputs = रिक्त;
    data->अंक_outputs = 0;
    data->scale_to_display = c->scale_to_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    data->app_id = SDL_strdup(SDL_GetAppID());

    यदि (!data->scale_to_display) {
        data->requested.logical_width = window->floating.w;
        data->requested.logical_height = window->floating.h;
    } अन्यथा {
        data->requested.logical_width = PixelToPoint(window, window->floating.w);
        data->requested.logical_height = PixelToPoint(window, window->floating.h);
        data->requested.pixel_width = window->floating.w;
        data->requested.pixel_height = window->floating.h;
    }

    यदि (!external_surface) {
        data->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_add_listener(data->surface, &surface_listener, data);
        wl_surface_set_user_data(data->surface, data);
        SDL_WAYLAND_register_surface(data->surface);
    } अन्यथा {
        window->flags |= SDL_WINDOW_EXTERNAL;
        data->surface = external_surface;

        /* External surfaces are registered by being put in a list, as changing tags or userdata
         * can cause problems with external toolkits.
         */
        Wayland_AddWindowDataToExternalList(data);
    }

    /* Always attach a viewport and fractional scale manager if available and the surface is not custom/external,
     * or the custom/external surface was explicitly flagged as high pixel density aware, which signals that the
     * application wants SDL to handle scaling.
     */
    यदि (!custom_surface_role || (window->flags & SDL_WINDOW_वरचा_PIXEL_DENSITY)) {
        यदि (c->viewporter) {
            data->viewport = wp_viewporter_get_viewport(c->viewporter, data->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_set_source(data->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        यदि (c->fractional_scale_manager) {
            data->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, data->surface);
            wp_fractional_scale_v1_add_listener(data->fractional_scale, &fractional_scale_listener, data);
        }
    }

    यदि (!custom_surface_role) {
        यदि (c->wp_color_manager_v1) {
            data->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, data->surface);
            wp_color_management_surface_feedback_v1_add_listener(data->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, data);
            Wayland_GetColorInfoForWindow(data, true);
        } अन्यथा यदि (c->frog_color_management_factory_v1) {
            data->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, data->surface);
            frog_color_managed_surface_add_listener(data->frog_color_managed_surface, &frog_surface_listener, data);
        }

        यदि (c->wp_alpha_modifier_v1) {
            data->wp_alpha_modifier_surface_v1 = wp_alpha_modifier_v1_get_surface(c->wp_alpha_modifier_v1, data->surface);
            wp_alpha_modifier_surface_v1_set_multiplier(data->wp_alpha_modifier_surface_v1, SDL_MAX_UINT32);
        }
    }

    // Must be called before EGL configuration to set the drawable backbuffer size.
    ConfigureWindowGeometry(window);

    /* Fire a callback when the compositor wants a new frame rendered.
     * Right now this only matters for OpenGL; we use this callback to add a
     * wait timeout that avoids getting deadlocked by the compositor when the
     * window isn't visible.
     */
    यदि (window->flags & SDL_WINDOW_OPENGL) {
        data->gles_swap_frame_event_queue = WAYLAND_wl_display_create_queue(data->waylandData->display);
        data->gles_swap_frame_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(data->surface);
        WAYLAND_wl_proxy_set_queue((संरचना wl_proxy *)data->gles_swap_frame_surface_wrapper, data->gles_swap_frame_event_queue);
        data->gles_swap_frame_callback = wl_surface_frame(data->gles_swap_frame_surface_wrapper);
        wl_callback_add_listener(data->gles_swap_frame_callback, &gles_swap_frame_listener, data);
    }

    यदि (window->flags & SDL_WINDOW_TRANSPARENT) {
        यदि (_this->gl_config.alpha_size == 0) {
            _this->gl_config.alpha_size = 8;
        }
    }

    यदि (create_egl_window) {
        data->egl_window = WAYLAND_wl_egl_window_create(data->surface, data->current.pixel_width, data->current.pixel_height);
    }

#ifdef SDL_VIDEO_OPENGL_EGL
    यदि (window->flags & SDL_WINDOW_OPENGL) {
        // Create the GLES window surface
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)data->egl_window);

        यदि (data->egl_surface == EGL_NO_SURFACE) {
            प्रत्यागम false; // SDL_EGL_CreateSurface should have set error
        }
    }
#endif

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    यदि (!custom_surface_role) {
#ifdef HAVE_LIBDECOR_H
        यदि (c->shell.libdecor && !SDL_WINDOW_IS_POPUP(window)) {
            data->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } अन्यथा
#endif
            यदि (c->shell.xdg) {
            यदि (SDL_WINDOW_IS_POPUP(window)) {
                data->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP;
            } अन्यथा {
                data->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL;
            }
        } // All other cases will be WAYLAND_SURFACE_UNKNOWN
    } अन्यथा {
        // Roleless and external surfaces are always considered to be in the shown state by the backend.
        data->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_CUSTOM;
        data->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_SHOWN;

        // External windows are presumed to be shown.
        यदि (window->flags & SDL_WINDOW_EXTERNAL) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        }
    }

    यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_BUFFER, false)) {
        data->double_buffer = true;
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, data->waylandData->display);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, data->surface);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_VIEWPORT_POINTER, data->viewport);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_EGL_WINDOW_POINTER, data->egl_window);
    यदि (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ध्रुव वर्ण *window_id = SDL_GetStringProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_WINDOW_ID_STRING, रिक्त);
        यदि (window_id && *window_id != '\0') {
            SDL_SetStringProperty(props, SDL_PROP_WINDOW_WAYLAND_WINDOW_ID_STRING, window_id);
        }
    }

    data->hit_test_result = SDL_HITTEST_NORMAL;

    प्रत्यागम true;
}

शून्य Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    window->internal->limits_changed = true;
}

शून्य Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    window->internal->limits_changed = true;
}

शून्य Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    window->internal->limits_changed = true;
}

bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    // Only popup windows can be positioned relative to the parent.
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        यदि (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_version(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_VERSION) {
            प्रत्यागम SDL_Unsupported();
        }

        RepositionPopup(window, false);
        प्रत्यागम true;
    } अन्यथा यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(window);

        यदि (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplayForFullscreenWindow(window);
            यदि (display && wind->last_displayID != display->id) {
                संरचना wl_output *output = display->internal->output;
                SetFullscreen(window, output, true);

                प्रत्यागम true;
            }
        }
    }
    प्रत्यागम SDL_SetError("wayland cannot position non-popup windows");
}

शून्य Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    /* Flush any pending state operations, as fullscreen windows do not get
     * explicitly resized, not strictly obeying the size of a maximized window
     * is a protocol violation, and pending restore events might result in a
     * configure event overwriting the requested size.
     *
     * Calling this on a custom surface is informative, so the size must
     * always be passed through.
     */
    FlushPendingEvents(window);

    ध्रुव bool maximized = (window->flags & SDL_WINDOW_MAXIMIZED) != 0;
    ध्रुव bool resizable_state = !(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN));

    /* Maximized and fullscreen windows don't get resized, and the new size is ignored
     * if this is just to recalculate the min/max or aspect limits on a tiled window.
     *
     * Some compositors will mark tiled windows as maximized. In these cases, the content
     * size is recalculated, but window size itself is left alone, as the spec states that
     * the configure size of a maximized window must be obeyed.
     */
    यदि (resizable_state || (window->tiled && !wind->limits_changed) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        यदि (!maximized) {
            यदि (!wind->scale_to_display) {
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
        यदि (window->tiled && !(window->flags & SDL_WINDOW_RESIZABLE)) {
            window->floating.w = window->pending.w;
            window->floating.h = window->pending.h;
        }
    } अन्यथा {
        // Can't resize the window.
        window->last_size_pending = false;
    }

    wind->limits_changed = false;
    यदि (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    ConfigureWindowGeometry(window);
    CommitLibdecorFrame(window);
}

शून्य Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *w, पूर्णाङ्क *h)
{
    SDL_WindowData *data = window->internal;

    *w = data->current.pixel_width;
    *h = data->current.pixel_height;
}

भिन्न Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    यदि (window->flags & SDL_WINDOW_वरचा_PIXEL_DENSITY || wind->scale_to_display || wind->fullscreen_exclusive) {
        प्रत्यागम (भिन्न)wind->scale_factor;
    }

    प्रत्यागम 1.0f;
}

SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    यदि (wind) {
        प्रत्यागम wind->last_displayID;
    }

    प्रत्यागम 0;
}

bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, भिन्न opacity)
{
    SDL_WindowData *wind = window->internal;

    यदि (wind->wp_alpha_modifier_surface_v1) {
        ध्रुव bool is_opaque = !(window->flags & SDL_WINDOW_TRANSPARENT) && opacity == 1.0f;

        यदि (wind->mask.mapped && wind->mask.opaque != is_opaque) {
            संरचना wl_buffer *old_buffer = wind->mask.buffer;
            wind->mask.opaque = is_opaque;
            wind->mask.buffer = Wayland_CreateSinglePixelBuffer(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->mask.surface, wind->mask.buffer, 0, 0);
            यदि (wl_surface_get_version(wind->mask.surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
                wl_surface_damage_buffer(wind->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } अन्यथा {
                wl_surface_damage(wind->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            यदि (is_opaque) {
                SetSurfaceOpaqueRegion(wind->mask.surface, wind->current.logical_width, wind->current.logical_height);
            } अन्यथा {
                SetSurfaceOpaqueRegion(wind->mask.surface, 0, 0);
            }

            wl_surface_commit(wind->mask.surface);

            यदि (old_buffer) {
                wl_buffer_destroy(old_buffer);
            }
        }

        यदि (is_opaque) {
            SetSurfaceOpaqueRegion(wind->surface, wind->current.viewport_width, wind->current.viewport_height);
        } अन्यथा {
            SetSurfaceOpaqueRegion(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_set_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((द्विगुण)SDL_MAX_UINT32 * (द्विगुण)opacity));

        प्रत्यागम true;
    }

    प्रत्यागम SDL_SetError("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

शून्य Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;
    ध्रुव वर्ण *title = window->title ? window->title : "";

#ifdef HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        libdecor_frame_set_title(wind->shell_surface.libdecor.frame, title);
    } अन्यथा
#endif
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_set_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

स्थिर पूर्णाङ्क icon_sort_callback(ध्रुव शून्य *a, ध्रुव शून्य *b)
{
    ध्रुव SDL_Surface *s1 = *(ध्रुव SDL_Surface **)a;
    ध्रुव SDL_Surface *s2 = *(ध्रुव SDL_Surface **)b;

    प्रत्यागम (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
    SDL_WindowData *wind = window->internal;
    Wayland_SHMPool *shm_pool = रिक्त;
    संरचना xdg_toplevel *toplevel = रिक्त;

    यदि (!_this->internal->xdg_toplevel_icon_manager_v1) {
        प्रत्यागम SDL_SetError("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    पूर्णाङ्क image_मोजणी_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_मोजणी_2);
    यदि (!images || !image_मोजणी_2) {
        प्रत्यागम false;
    }

    // Release the old icon resources.
    यदि (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = रिक्त;
    }

    प्रति (पूर्णाङ्क i = 0; i < wind->icon_buffer_मोजणी; ++i) {
        wl_buffer_destroy(wind->icon_buffers[i]);
    }
    wind->icon_buffer_मोजणी = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->internal->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_मोजणी_2 * परिमाण(संरचना wl_buffer *));
    यदि (!wind->icon_buffers) {
        गच्छ failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    size_t pool_size = 0;
    प्रति (पूर्णाङ्क i = 0; i < image_मोजणी_2; ++i) {
        // Images must be square. Non-square images will be centered.
        ध्रुव पूर्णाङ्क size = SDL_max(images[i]->w, images[i]->h);
        pool_size += size * size * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_मोजणी_2, परिमाण(SDL_Surface *), icon_sort_callback);

    shm_pool = Wayland_AllocSHMPool(pool_size);
    यदि (!shm_pool) {
        SDL_SetError("wayland: failed to allocate an SHM pool for the icon");
        गच्छ failure_cleanup;
    }

    ध्रुव द्विगुण base_size = (द्विगुण)SDL_max(icon->w, icon->h);
    प्रति (पूर्णाङ्क i = 0; i < image_मोजणी_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        ध्रुव पूर्णाङ्क level_size = SDL_max(surface->w, surface->h);
        ध्रुव पूर्णाङ्क scale = (पूर्णाङ्क)SDL_floor((द्विगुण)level_size / base_size);
        यदि (!scale) {
            अनुवर्त;
        }

        यदि (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            यदि (!surface) {
                SDL_SetError("wayland: failed to convert the icon image to ARGB8888 format");
                गच्छ failure_cleanup;
            }
        }

        शून्य *buffer_mem;
        संरचना wl_buffer *buffer = Wayland_AllocBufferFromPool(shm_pool, level_size, level_size, &buffer_mem);
        यदि (!buffer) {
            // Clean up the temporary conversion surface.
            यदि (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_SetError("wayland: failed to allocate a wl_buffer for the icon");
            गच्छ failure_cleanup;
        }

        wind->icon_buffers[wind->icon_buffer_मोजणी++] = buffer;

        // Center non-square images.
        यदि (surface->w < level_size) {
            SDL_memset(buffer_mem, 0, level_size * level_size * 4);
            buffer_mem = (Uint8 *)buffer_mem + (((level_size - surface->w) / 2) * 4);
        } अन्यथा यदि (surface->h < level_size) {
            SDL_memset(buffer_mem, 0, level_size * level_size * 4);
            buffer_mem = (Uint8 *)buffer_mem + (((level_size - surface->h) / 2) * (level_size * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, buffer_mem, level_size * 4, true);

        xdg_toplevel_icon_v1_add_buffer(wind->xdg_toplevel_icon_v1, buffer, scale);

        // Clean up the temporary scaled or conversion surface.
        यदि (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#ifdef HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        toplevel = libdecor_frame_get_xdg_toplevel(wind->shell_surface.libdecor.frame);
    } अन्यथा
#endif
        यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    यदि (toplevel) {
        xdg_toplevel_icon_manager_v1_set_icon(_this->internal->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
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

    प्रति (पूर्णाङ्क i = 0; i < wind->icon_buffer_मोजणी; ++i) {
        wl_buffer_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = रिक्त;
    wind->icon_buffer_मोजणी = 0;

    प्रत्यागम false;
}

शून्य *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *wind = window->internal;
    शून्य *ret = रिक्त;

    यदि (wind->icc_size > 0) {
        शून्य *icc_map = mmap(रिक्त, wind->icc_size, PROT_READ, MAP_PRIVATE, wind->icc_fd, 0);
        यदि (icc_map != MAP_FAILED) {
            ret = SDL_malloc(wind->icc_size);
            यदि (ret) {
                *size = wind->icc_size;
                SDL_memcpy(ret, icc_map, *size);
            }
            munmap(icc_map, wind->icc_size);
        }
    }

    प्रत्यागम ret;
}

bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    कुरु {
        WAYLAND_wl_display_roundtrip(_this->internal->display);
    } यावत् (wind->pending_state_deadline_मोजणी);

    प्रत्यागम true;
}

शून्य Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    window->internal->accepts_drag_and_drop = accept;
}

bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    यदि (window->flags & SDL_WINDOW_POPUP_MENU) {
        यदि (!(window->flags & SDL_WINDOW_HIDDEN)) {
            यदि (!focusable && (window->flags & SDL_WINDOW_आदान_FOCUS)) {
                SDL_Window *new_focus;
                ध्रुव bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                Wayland_SetKeyboardFocus(new_focus, set_focus);
            } अन्यथा यदि (focusable) {
                यदि (SDL_ShouldFocusPopup(window)) {
                    Wayland_SetKeyboardFocus(window, true);
                }
            }
        }

        प्रत्यागम true;
    }

    प्रत्यागम SDL_SetError("wayland: focus can only be toggled on popup menu windows");
}

शून्य Wayland_ShowWindowSystemMenu(SDL_Window *window, पूर्णाङ्क x, पूर्णाङ्क y)
{
    SDL_WindowData *wind = window->internal;
    SDL_WaylandSeat *seat = wind->waylandData->last_implicit_grab_seat;

    यदि (!seat) {
        प्रत्यागम;
    }

    यदि (wind->scale_to_display) {
        x = PixelToPoint(window, x);
        y = PixelToPoint(window, y);
    }

#ifdef HAVE_LIBDECOR_H
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        यदि (wind->shell_surface.libdecor.frame) {
            libdecor_frame_show_window_menu(wind->shell_surface.libdecor.frame, seat->wl_seat, seat->last_implicit_grab_serial, x, y);
        }
    } अन्यथा
#endif
    यदि (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        यदि (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_window_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->last_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_USE_LIBDBUS
    यदि (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        प्रत्यागम true;
    }
#endif

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    यदि (data->idle_inhibit_manager) {
        SDL_Window *window = _this->windows;
        यावत् (window) {
            SDL_WindowData *win_data = window->internal;

            यदि (_this->suspend_screensaver && !win_data->idle_inhibitor) {
                win_data->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(data->idle_inhibit_manager,
                                                                 win_data->surface);
            } अन्यथा यदि (!_this->suspend_screensaver && win_data->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_data->idle_inhibitor);
                win_data->idle_inhibitor = रिक्त;
            }

            window = window->next;
        }
    }

    प्रत्यागम true;
}

शून्य Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *wind = window->internal;

    यदि (data && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        यदि (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            window->hit_test = रिक्त;
            WAYLAND_wl_display_roundtrip(data->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_DisplayRemoveWindowReferencesFromSeats(data, wind);

        यदि (wind->mask.viewport) {
            wp_viewport_destroy(wind->mask.viewport);
        }
        यदि (wind->mask.buffer) {
            wl_buffer_destroy(wind->mask.buffer);
        }
        यदि (wind->mask.subsurface) {
            wl_subsurface_destroy(wind->mask.subsurface);
        }
        यदि (wind->mask.surface) {
            wl_surface_destroy(wind->mask.surface);
        }
#ifdef SDL_VIDEO_OPENGL_EGL
        यदि (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#endif
        यदि (wind->egl_window) {
            WAYLAND_wl_egl_window_destroy(wind->egl_window);
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

        यदि (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } अन्यथा {
            Wayland_RemoveWindowDataFromExternalList(wind);
        }

        यदि (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        प्रति (पूर्णाङ्क i = 0; i < wind->icon_buffer_मोजणी; ++i) {
            wl_buffer_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_buffer_मोजणी = 0;

        SDL_free(wind);
    }
    window->internal = रिक्त;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
