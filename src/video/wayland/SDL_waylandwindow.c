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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#অন্তর্ভাব <sys/mman.h>

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../../core/unix/SDL_appid.h"
#অন্তর্ভাব "../../notification/SDL_notification_c.h"
#অন্তর্ভাব "../SDL_egl_c.h"
#অন্তর্ভাব "SDL_waylandevents_c.h"
#অন্তর্ভাব "SDL_waylandmouse.h"
#অন্তর্ভাব "SDL_waylandwindow.h"
#অন্তর্ভাব "SDL_waylandvideo.h"
#অন্তর্ভাব "../../SDL_hints_c.h"
#অন্তর্ভাব "SDL_waylandcolor.h"

#অন্তর্ভাব "alpha-modifier-v1-client-protocol.h"
#অন্তর্ভাব "xdg-shell-client-protocol.h"
#অন্তর্ভাব "xdg-decoration-unstable-v1-client-protocol.h"
#অন্তর্ভাব "idle-inhibit-unstable-v1-client-protocol.h"
#অন্তর্ভাব "xdg-activation-v1-client-protocol.h"
#অন্তর্ভাব "viewporter-client-protocol.h"
#অন্তর্ভাব "fractional-scale-v1-client-protocol.h"
#অন্তর্ভাব "xdg-foreign-unstable-v2-client-protocol.h"
#অন্তর্ভাব "xdg-dialog-v1-client-protocol.h"
#অন্তর্ভাব "frog-color-management-v1-client-protocol.h"
#অন্তর্ভাব "xdg-toplevel-icon-v1-client-protocol.h"
#অন্তর্ভাব "color-management-v1-client-protocol.h"
#অন্তর্ভাব "xdg-session-management-v1-client-protocol.h"
#অন্তর্ভাব "xdg-toplevel-tag-v1-client-protocol.h"

#ifdef HAVE_LIBDECOR_H
#অন্তর্ভাব <libdecor.h>
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
স্থির bool ShouldMaskFullscreen()
{
    স্থির পূর্ণাঙ্ক mask_required = -1;

    যদি (mask_required >= 0) {
        প্রত্যাগম mask_required != 0;
    }

    ধ্রুব বর্ণ *desktop = SDL_getenv("XDG_CURRENT_DESKTOP");
    যদি (desktop && SDL_strstr(desktop, "KDE") != রিক্ত) {
        mask_required = 1;
    } অন্যথা {
        mask_required = 0;
    }

    প্রত্যাগম mask_required != 0;
}

স্থির দ্বিগুণ GetWindowScale(SDL_Window *window)
{
    প্রত্যাগম (window->flags & SDL_WINDOW_উপরের_PIXEL_DENSITY) || window->internal->scale_to_display ? window->internal->scale_factor : 1.0;
}

// These are point->pixel->point round trip safe; the inverse is not round trip safe due to rounding.
স্থির পূর্ণাঙ্ক PointToPixel(SDL_Window *window, পূর্ণাঙ্ক point)
{
    /* Rounds halfway away from zero as per the Wayland fractional scaling protocol spec.
     * Wayland scale units are in units of 1/120, so the offset is required to correct for
     * rounding errors when using certain scale values.
     */
    প্রত্যাগম point ? SDL_max((পূর্ণাঙ্ক)SDL_lround((দ্বিগুণ)point * GetWindowScale(window) + 1e-6), 1) : 0;
}

স্থির পূর্ণাঙ্ক PixelToPoint(SDL_Window *window, পূর্ণাঙ্ক pixel)
{
    প্রত্যাগম pixel ? SDL_max((পূর্ণাঙ্ক)SDL_lround((দ্বিগুণ)pixel / GetWindowScale(window)), 1) : 0;
}

গণনা WaylandModeScale
{
    WAYLAND_MODE_SCALE_UNDEFINED,
    WAYLAND_MODE_SCALE_ASPECT,
    WAYLAND_MODE_SCALE_STRETCH,
    WAYLAND_MODE_SCALE_NONE
};

স্থির গণনা WaylandModeScale GetModeScaleMethod(শূন্য)
{
    স্থির গণনা WaylandModeScale scale_mode = WAYLAND_MODE_SCALE_UNDEFINED;

    যদি (scale_mode == WAYLAND_MODE_SCALE_UNDEFINED) {
        ধ্রুব বর্ণ *scale_hint = SDL_GetHint(SDL_HINT_VIDEO_WAYLAND_MODE_SCALING);

        যদি (scale_hint) {
            যদি (!SDL_strcasecmp(scale_hint, "stretch")) {
                scale_mode = WAYLAND_MODE_SCALE_STRETCH;
            } অন্যথা যদি (!SDL_strcasecmp(scale_hint, "none")) {
                scale_mode = WAYLAND_MODE_SCALE_NONE;
            } অন্যথা {
                scale_mode = WAYLAND_MODE_SCALE_ASPECT;
            }
        } অন্যথা {
            scale_mode = WAYLAND_MODE_SCALE_ASPECT;
        }
    }

    প্রত্যাগম scale_mode;
}

প্রকারনির্দেশ সংরচনা BorderInsets
{
    পূর্ণাঙ্ক বাম;
    পূর্ণাঙ্ক শীর্ষ;
    পূর্ণাঙ্ক ডান;
    পূর্ণাঙ্ক bottom;
} BorderInsets;

// The border insets from the window properties; they only apply to xdg-toplevel windows.
স্থির শূন্য GetBorderInsets(SDL_Window *window, BorderInsets *insets)
{
    SDL_zerop(insets);
    যদি (!window->internal->enable_insets) {
        প্রত্যাগম;
    }
    যদি (window->internal->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        ধ্রুব SDL_PropertiesID props = SDL_GetWindowProperties(window);
        insets->বাম = (পূর্ণাঙ্ক)SDL_clamp(SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_বাম_সংখ্যা, 0), 0, SDL_MAX_SINT16);
        insets->শীর্ষ = (পূর্ণাঙ্ক)SDL_clamp(SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_শীর্ষ_সংখ্যা, 0), 0, SDL_MAX_SINT16);
        insets->ডান = (পূর্ণাঙ্ক)SDL_clamp(SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_ডান_সংখ্যা, 0), 0, SDL_MAX_SINT16);
        insets->bottom = (পূর্ণাঙ্ক)SDL_clamp(SDL_Get_সংখ্যা_Property(props, SDL_PROP_WINDOW_WAYLAND_BORDER_INSET_BOTTOM_সংখ্যা, 0), 0, SDL_MAX_SINT16);
    }
}

স্থির শূন্য SetMinMaxDimensions(SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;
    পূর্ণাঙ্ক min_width, min_height, max_width, max_height;

    /* Keep the limits off while the window is in a fixed-size state, or the controls
     * to exit that state may be disabled.
     */
    যদি (window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) {
        min_width = 0;
        min_height = 0;
        max_width = 0;
        max_height = 0;
    } অন্যথা যদি (window->flags & SDL_WINDOW_RESIZABLE) {
        পূর্ণাঙ্ক adj_w = SDL_max(window->min_w, wind->system_limits.min_width);
        পূর্ণাঙ্ক adj_h = SDL_max(window->min_h, wind->system_limits.min_height);
        যদি (wind->scale_to_display) {
            adj_w = PixelToPoint(window, adj_w);
            adj_h = PixelToPoint(window, adj_h);
        }
        min_width = adj_w;
        min_height = adj_h;

        adj_w = window->max_w ? SDL_max(window->max_w, wind->system_limits.min_width) : 0;
        adj_h = window->max_h ? SDL_max(window->max_h, wind->system_limits.min_height) : 0;
        যদি (wind->scale_to_display) {
            adj_w = PixelToPoint(window, adj_w);
            adj_h = PixelToPoint(window, adj_h);
        }
        max_width = adj_w;
        max_height = adj_h;
    } অন্যথা {
        min_width = wind->current.logical_width;
        min_height = wind->current.logical_height;
        max_width = wind->current.logical_width;
        max_height = wind->current.logical_height;
    }

#ifdef HAVE_LIBDECOR_H
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        যদি (!wind->shell_surface.libdecor.frame) {
            প্রত্যাগম; // Can't do anything yet, wait for ShowWindow
        }

        যদি (min_width && min_height && min_width == max_width && min_height == max_height) {
            libdecor_frame_unset_capabilities(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE);
        } অন্যথা {
            libdecor_frame_set_capabilities(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE);
        }

        /* No need to change these values if the window is non-resizable,
         * as libdecor will just overwrite them internally.
         */
        যদি (libdecor_frame_has_capability(wind->shell_surface.libdecor.frame, LIBDECOR_ACTION_RESIZE)) {
            libdecor_frame_set_min_content_size(wind->shell_surface.libdecor.frame,
                                                min_width,
                                                min_height);
            libdecor_frame_set_max_content_size(wind->shell_surface.libdecor.frame,
                                                max_width,
                                                max_height);
        }
    } অন্যথা
#endif
        যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        যদি (!wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            প্রত্যাগম; // Can't do anything yet, wait for ShowWindow
        }
        /* The limits are in window geometry space; keep an existing minimum at 1 or more,
         * or the window can be spuriously closed.
         */
        BorderInsets insets;
        GetBorderInsets(window, &insets);
        min_width = SDL_max(min_width - (insets.বাম + insets.ডান), min_width ? 1 : 0);
        min_height = SDL_max(min_height - (insets.শীর্ষ + insets.bottom), min_height ? 1 : 0);
        যদি (max_width) {
            max_width = SDL_max(max_width - (insets.বাম + insets.ডান), 1);
        }
        যদি (max_height) {
            max_height = SDL_max(max_height - (insets.শীর্ষ + insets.bottom), 1);
        }
        xdg_toplevel_set_min_size(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  min_width,
                                  min_height);
        xdg_toplevel_set_max_size(wind->shell_surface.xdg.toplevel.xdg_toplevel,
                                  max_width,
                                  max_height);
    }
}

স্থির শূন্য EnsurePopupPositionIsValid(SDL_Window *window, পূর্ণাঙ্ক *x, পূর্ণাঙ্ক *y)
{
    পূর্ণাঙ্ক adj_গুনতি = 0;

    /* Per the xdg-positioner spec, child popup windows must intersect or at
     * least be partially adjoining the parent window.
     *
     * Failure to ensure this on a compositor that enforces this restriction
     * can result in behavior ranging from the window being spuriously closed
     * to a protocol violation.
     */
    যদি (*x + window->w <= 0) {
        *x = -window->w;
        ++adj_গুনতি;
    }
    যদি (*y + window->h <= 0) {
        *y = -window->h;
        ++adj_গুনতি;
    }
    যদি (*x >= window->parent->w) {
        *x = window->parent->w;
        ++adj_গুনতি;
    }
    যদি (*y >= window->parent->h) {
        *y = window->parent->h;
        ++adj_গুনতি;
    }

    /* If adjustment was required on the x and y axes, the popup is aligned with
     * the parent corner-to-corner and is neither overlapping nor adjoining, so it
     * must be nudged by 1 to be considered adjoining.
     */
    যদি (adj_গুনতি > 1) {
        *x += *x < 0 ? 1 : -1;
    }
}

// The window geometry: the explicitly set one, or the full surface if SDL has never set it.
স্থির শূন্য GetWindowGeometry(SDL_WindowData *wind, SDL_Rect *geometry)
{
    *geometry = wind->explicit_geometry;
    যদি (SDL_RectEmpty(geometry)) {
        geometry->x = 0;
        geometry->y = 0;
        geometry->w = wind->current.logical_width;
        geometry->h = wind->current.logical_height;
    }
}

স্থির শূন্য AdjustPopupOffset(SDL_Window *popup, পূর্ণাঙ্ক *x, পূর্ণাঙ্ক *y)
{
    // Positioner offsets are relative to the origin of the parent's window geometry.
#ifdef HAVE_LIBDECOR_H
    যদি (popup->parent->internal->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        পূর্ণাঙ্ক adj_x, adj_y;
        libdecor_frame_translate_coordinate(popup->parent->internal->shell_surface.libdecor.frame,
                                            *x, *y, &adj_x, &adj_y);
        *x = adj_x;
        *y = adj_y;
    } অন্যথা
#endif
    {
        *x -= popup->parent->internal->explicit_geometry.x;
        *y -= popup->parent->internal->explicit_geometry.y;
    }
}

স্থির শূন্য RepositionPopup(SDL_Window *window, bool use_current_position)
{
    SDL_WindowData *wind = window->internal;

    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP &&
        wind->shell_surface.xdg.popup.xdg_positioner &&
        xdg_popup_get_version(wind->shell_surface.xdg.popup.xdg_popup) >= XDG_POPUP_REPOSITION_SINCE_VERSION) {
        পূর্ণাঙ্ক x = use_current_position ? window->x : window->pending.x;
        পূর্ণাঙ্ক y = use_current_position ? window->y : window->pending.y;

        EnsurePopupPositionIsValid(window, &x, &y);
        যদি (wind->scale_to_display) {
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

স্থির শূন্য SetSurfaceOpaqueRegion(সংরচনা wl_surface *surface, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height)
{
    SDL_VideoData *viddata = SDL_GetVideoDevice()->internal;

    যদি (width && height) {
        সংরচনা wl_region *region = wl_compositor_create_region(viddata->compositor);
        wl_region_add(region, 0, 0, width, height);
        wl_surface_set_opaque_region(surface, region);
        wl_region_destroy(region);
    } অন্যথা {
        wl_surface_set_opaque_region(surface, রিক্ত);
    }
}

স্থির শূন্য ConfigureWindowGeometry(SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    ধ্রুব দ্বিগুণ scale_factor = GetWindowScale(window);
    ধ্রুব দ্বিগুণ prev_pointer_scale_x = data->pointer_scale.x;
    ধ্রুব দ্বিগুণ prev_pointer_scale_y = data->pointer_scale.y;
    ধ্রুব পূর্ণাঙ্ক old_pixel_width = data->current.pixel_width;
    ধ্রুব পূর্ণাঙ্ক old_pixel_height = data->current.pixel_height;
    পূর্ণাঙ্ক window_width = 0;
    পূর্ণাঙ্ক window_height = 0;
    পূর্ণাঙ্ক viewport_width, viewport_height;
    bool window_size_changed;
    bool buffer_size_changed;
    ধ্রুব bool is_opaque = !(window->flags & SDL_WINDOW_TRANSPARENT) && window->opacity == 1.0f;

    যদি (data->is_fullscreen && window->fullscreen_exclusive) {
        window_width = window->current_fullscreen_mode.w;
        window_height = window->current_fullscreen_mode.h;

        viewport_width = data->requested.logical_width;
        viewport_height = data->requested.logical_height;

        বিকল্প (GetModeScaleMethod()) {
        পক্ষ WAYLAND_MODE_SCALE_NONE:
            /* The Wayland spec states that the advertised fullscreen dimensions are a maximum.
             * Windows can request a smaller size, but exceeding these dimensions is a protocol violation,
             * thus, modes that exceed the output size still need to be scaled with a viewport.
             */
            যদি (window_width <= viewport_width && window_height <= viewport_height) {
                viewport_width = window_width;
                viewport_height = window_height;

                ভঙ্গ;
            }
            SDL_FALLTHROUGH;
        পক্ষ WAYLAND_MODE_SCALE_ASPECT:
        {
            ধ্রুব ভিন্ন output_ratio = (ভিন্ন)viewport_width / (ভিন্ন)viewport_height;
            ধ্রুব ভিন্ন mode_ratio = (ভিন্ন)window_width / (ভিন্ন)window_height;

            যদি (output_ratio > mode_ratio) {
                viewport_width = SDL_lroundf((ভিন্ন)window_width * ((ভিন্ন)viewport_height / (ভিন্ন)window_height));
            } অন্যথা যদি (output_ratio < mode_ratio) {
                viewport_height = SDL_lroundf((ভিন্ন)window_height * ((ভিন্ন)viewport_width / (ভিন্ন)window_width));
            }
        } ভঙ্গ;
        স্বভাব:
            ভঙ্গ;
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

        যদি (window_size_changed || buffer_size_changed) {
            যদি (data->viewport) {
                wp_viewport_set_destination(data->viewport, viewport_width, viewport_height);

                data->current.logical_width = data->requested.logical_width;
                data->current.logical_height = data->requested.logical_height;
                data->current.viewport_width = viewport_width;
                data->current.viewport_height = viewport_height;
            } অন্যথা {
                // Calculate the integer scale from the mode and output.
                ধ্রুব int32_t int_scale = SDL_max(window->current_fullscreen_mode.w / viewport_width, 1);

                wl_surface_set_buffer_scale(data->surface, int_scale);
                data->current.logical_width = window->current_fullscreen_mode.w;
                data->current.logical_height = window->current_fullscreen_mode.h;
            }

            data->pointer_scale.x = (দ্বিগুণ)window_width / (দ্বিগুণ)viewport_width;
            data->pointer_scale.y = (দ্বিগুণ)window_height / (দ্বিগুণ)viewport_height;
        }
    } অন্যথা {
        যদি (!data->scale_to_display) {
            viewport_width = data->requested.logical_width;
            viewport_height = data->requested.logical_height;
        } অন্যথা {
            viewport_width = data->requested.pixel_width;
            viewport_height = data->requested.pixel_height;
        }

        যদি (!data->enable_insets &&
            data->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_HIDDEN &&
            data->viewport && data->waylandData->subcompositor && !data->floating && !data->is_fullscreen) {
            পূর্ণাঙ্ক min_width, min_height, max_width, max_height;
            যদি (window->flags & SDL_WINDOW_RESIZABLE) {
                min_width = window->min_w;
                min_height = window->min_h;
                max_width = window->max_w;
                max_height = window->max_h;
            } অন্যথা {
                // Use the fixed size in the odd case where a non-resizable window somehow wound up tiled or maximized.
                min_width = window->floating.w;
                min_height = window->floating.h;
                max_width = window->floating.w;
                max_height = window->floating.h;
            }

            যদি (min_width) {
                viewport_width = SDL_max(viewport_width, min_width);
            }
            যদি (min_height) {
                viewport_height = SDL_max(viewport_height, min_height);
            }
            যদি (max_width) {
                viewport_width = SDL_min(viewport_width, max_width);
            }
            যদি (max_height) {
                viewport_height = SDL_min(viewport_height, max_height);
            }

            ভিন্ন aspect = (ভিন্ন)viewport_width / (ভিন্ন)viewport_height;
            যদি (window->min_aspect != 0.f && aspect < window->min_aspect) {
                viewport_height = SDL_max(SDL_lroundf((ভিন্ন)viewport_width / window->min_aspect), 1);
            } অন্যথা যদি (window->max_aspect != 0.f && aspect > window->max_aspect) {
                viewport_width = SDL_max(SDL_lroundf((ভিন্ন)viewport_height * window->max_aspect), 1);
            }

            // At this point, the viewport matches the virtual window dimensions, but the viewport might be clamped to the output window dimensions beyond here.
            window_width = viewport_width;
            window_height = viewport_height;

            // If the viewport bounds exceed the window size, scale them while maintaining the aspect ratio.
            যদি (!data->scale_to_display) {
                যদি (viewport_width > data->requested.logical_width || viewport_height > data->requested.logical_height) {
                    aspect = (ভিন্ন)viewport_width / (ভিন্ন)viewport_height;
                    ধ্রুব ভিন্ন window_ratio = (ভিন্ন)data->requested.logical_width / (ভিন্ন)data->requested.logical_height;
                    যদি (aspect >= window_ratio) {
                        viewport_width = data->requested.logical_width;
                        viewport_height = SDL_lroundf((ভিন্ন)viewport_width / aspect);
                    } অন্যথা যদি (aspect < window_ratio) {
                        viewport_height = data->requested.logical_height;
                        viewport_width = SDL_lroundf((ভিন্ন)viewport_height * aspect);
                    }
                }
            } অন্যথা {
                যদি (viewport_width > data->requested.pixel_width || viewport_height > data->requested.pixel_height) {
                    aspect = (ভিন্ন)viewport_width / (ভিন্ন)viewport_height;
                    ধ্রুব ভিন্ন window_ratio = (ভিন্ন)data->requested.pixel_width / (ভিন্ন)data->requested.pixel_height;
                    যদি (aspect >= window_ratio) {
                        viewport_width = data->requested.pixel_width;
                        viewport_height = SDL_lroundf((ভিন্ন)viewport_width / aspect);
                    } অন্যথা যদি (aspect < window_ratio) {
                        viewport_height = data->requested.pixel_height;
                        viewport_width = SDL_lroundf((ভিন্ন)viewport_height * aspect);
                    }
                }
            }

            viewport_width = SDL_max(viewport_width, 1);
            viewport_height = SDL_max(viewport_height, 1);
        } অন্যথা {
            window_width = viewport_width;
            window_height = viewport_height;
        }

        যদি (!data->scale_to_display) {
            data->current.pixel_width = PointToPixel(window, window_width);
            data->current.pixel_height = PointToPixel(window, window_height);
        } অন্যথা {
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

        যদি (window_size_changed || buffer_size_changed) {
            যদি (data->viewport) {
                wp_viewport_set_destination(data->viewport, viewport_width, viewport_height);
            } অন্যথা যদি (window->flags & SDL_WINDOW_উপরের_PIXEL_DENSITY) {
                // Don't change this if the DPI awareness flag is unset, as an application may have set this manually on a custom or external surface.
                wl_surface_set_buffer_scale(data->surface, (int32_t)scale_factor);
            }

            data->current.logical_width = data->requested.logical_width;
            data->current.logical_height = data->requested.logical_height;
            data->current.viewport_width = viewport_width;
            data->current.viewport_height = viewport_height;

            data->pointer_scale.x = (দ্বিগুণ)window_width / (দ্বিগুণ)viewport_width;
            data->pointer_scale.y = (দ্বিগুণ)window_height / (দ্বিগুণ)viewport_height;
        }
    }

    যদি (data->egl_window && buffer_size_changed) {
        WAYLAND_wl_egl_window_resize(data->egl_window,
                                     data->current.pixel_width,
                                     data->current.pixel_height,
                                     0, 0);
    }

    /* Calculate the mask size and offset.
     * Fullscreen windows are centered and masked automatically by the compositor, unless it lacks the capability.
     */
    যদি (!data->enable_insets && data->viewport && data->waylandData->subcompositor && (!data->is_fullscreen || ShouldMaskFullscreen()) &&
        (viewport_width != data->current.logical_width || viewport_height != data->current.logical_height)) {
        সংরচনা wl_buffer *old_buffer = রিক্ত;

        যদি (!data->mask.surface) {
            data->mask.surface = wl_compositor_create_surface(data->waylandData->compositor);
            SDL_WAYLAND_register_surface(data->mask.surface);
            wl_surface_set_user_data(data->mask.surface, data);
        }
        যদি (!data->mask.subsurface) {
            data->mask.subsurface = wl_subcompositor_get_subsurface(data->waylandData->subcompositor, data->mask.surface, data->surface);
        }
        যদি (!data->mask.viewport) {
            data->mask.viewport = wp_viewporter_get_viewport(data->waylandData->viewporter, data->mask.surface);
        }
        যদি (!data->mask.buffer || data->mask.opaque != is_opaque) {
            old_buffer = data->mask.buffer;
            data->mask.opaque = is_opaque;
            data->mask.buffer = Wayland_CreateSinglePixelBuffer(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);
        }

        wl_surface_attach(data->mask.surface, data->mask.buffer, 0, 0);

        wl_subsurface_place_below(data->mask.subsurface, data->surface);
        wp_viewport_set_destination(data->mask.viewport, data->current.logical_width, data->current.logical_height);

        যদি (wl_surface_get_version(data->mask.surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
            wl_surface_damage_buffer(data->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        } অন্যথা {
            wl_surface_damage(data->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
        }

        যদি (is_opaque) {
            SetSurfaceOpaqueRegion(data->mask.surface, data->current.logical_width, data->current.logical_height);
        } অন্যথা {
            SetSurfaceOpaqueRegion(data->mask.surface, 0, 0);
        }

        // Can't use an offset subsurface with libdecor (yet), or the decorations won't line up properly.
        যদি (data->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
            data->mask.offset_x = -(data->current.logical_width - viewport_width) / 2;
            data->mask.offset_y = -(data->current.logical_height - viewport_height) / 2;
        } অন্যথা {
            data->mask.offset_x = 0;
            data->mask.offset_y = 0;
        }

        wl_subsurface_set_position(data->mask.subsurface, data->mask.offset_x, data->mask.offset_y);
        wl_surface_commit(data->mask.surface);

        যদি (old_buffer) {
            wl_buffer_destroy(old_buffer);
        }

        data->mask.mapped = true;
    } অন্যথা যদি (data->mask.mapped) {
        wl_subsurface_set_position(data->mask.subsurface, 0, 0);
        wl_surface_attach(data->mask.surface, রিক্ত, 0, 0);
        wl_surface_commit(data->mask.surface);

        data->mask.offset_x = 0;
        data->mask.offset_y = 0;
        data->mask.mapped = false;
    }

    যদি (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && data->shell_surface.xdg.surface &&
        (data->enable_insets || !data->viewport)) {
        /* The window geometry is the surface minus the declared border insets. They don't apply
         * when an exact size is required (maximized/fullscreen).
         */
        BorderInsets insets;
        GetBorderInsets(window, &insets);
        ধ্রুব bool use_insets = (insets.বাম || insets.শীর্ষ || insets.ডান || insets.bottom) &&
                                !(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN));
        SDL_Rect geometry = { 0, 0, data->current.logical_width, data->current.logical_height };
        যদি (use_insets) {
            geometry.x = insets.বাম;
            geometry.y = insets.শীর্ষ;
            geometry.w = SDL_max(geometry.w - (insets.বাম + insets.ডান), 1);
            geometry.h = SDL_max(geometry.h - (insets.শীর্ষ + insets.bottom), 1);
        }
        /* An explicitly set geometry does not track the surface, so it must be kept in sync
         * once set. Otherwise this is only done when viewports aren't supported and the size
         * has changed (XXX: a hack) to avoid a potential protocol violation if a buffer with
         * an old size is committed.
         */
        যদি ((use_insets || !SDL_RectEmpty(&data->explicit_geometry) || (!data->viewport && window_size_changed)) &&
            !SDL_RectsEqual(&geometry, &data->explicit_geometry)) {
            xdg_surface_set_window_geometry(data->shell_surface.xdg.surface, geometry.x, geometry.y, geometry.w, geometry.h);
            data->explicit_geometry = geometry;
        }
    }

    /* The opaque region and pointer confinement region only need to be
     * recalculated if the output size has changed.
     */
    যদি (window_size_changed) {
        যদি (is_opaque) {
            SetSurfaceOpaqueRegion(data->surface, viewport_width, viewport_height);
        } অন্যথা {
            SetSurfaceOpaqueRegion(data->surface, 0, 0);
        }

        // Ensure that child popup windows are still in bounds.
        প্রতি (SDL_Window *child = window->first_child; child; child = child->next_sibling) {
            RepositionPopup(child, true);
        }
    }

    // Update the scale for any focused cursors.
    যদি (prev_pointer_scale_x != data->pointer_scale.x || prev_pointer_scale_y != data->pointer_scale.y) {
        Wayland_DisplayUpdatePointerFocusedScale(data);
    }

    /* Update the min/max dimensions, primarily if the state was changed, and for non-resizable
     * xdg-toplevel windows where the limits should match the window size.
     */
    SetMinMaxDimensions(window);

    // Unconditionally send the window and drawable size, the video core will deduplicate when required.
    যদি (!data->scale_to_display) {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, window_width, window_height);
    } অন্যথা {
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESIZED, data->current.pixel_width, data->current.pixel_height);
    }
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, data->current.pixel_width, data->current.pixel_height);

    /* Send an exposure event if the window is in the shown state and the size has changed,
     * even if the window is occluded, as the client needs to commit a new frame for the
     * changes to take effect.
     *
     * The occlusion state is immediately set again afterward, if necessary.
     */
    যদি (data->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        যদি ((buffer_size_changed || window_size_changed) ||
            (!data->suspended && (window->flags & SDL_WINDOW_OCCLUDED))) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }

        যদি (data->suspended) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
        }
    }
}

স্থির শূন্য CommitLibdecorFrame(SDL_Window *window)
{
#ifdef HAVE_LIBDECOR_H
    SDL_WindowData *wind = window->internal;

    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        সংরচনা libdecor_state *state = libdecor_state_new(wind->current.logical_width, wind->current.logical_height);
        libdecor_frame_commit(wind->shell_surface.libdecor.frame, state, রিক্ত);
        libdecor_state_free(state);
    }
#endif
}

স্থির শূন্য pending_state_deadline_handler(শূন্য *data, সংরচনা wl_callback *callback, uint32_t callback_data)
{
    // Get the window from the ID, as it may have been destroyed.
    SDL_WindowID windowID = (SDL_WindowID)(uintptr_t)data;
    SDL_Window *window = SDL_GetWindowFromID(windowID);

    যদি (window && window->internal) {
        --window->internal->pending_state_deadline_গুনতি;
    }

    wl_callback_destroy(callback);
}

স্থির সংরচনা wl_callback_listener pending_state_deadline_listener = {
    pending_state_deadline_handler
};

স্থির শূন্য AddPendingStateSync(SDL_WindowData *window_data)
{
    SDL_VideoData *video_data = window_data->waylandData;
    শূন্য *cb_data = (শূন্য *)(uintptr_t)window_data->sdlwindow->id;

    ++window_data->pending_state_deadline_গুনতি;
    সংরচনা wl_callback *cb = wl_display_sync(video_data->display);
    wl_callback_add_listener(cb, &pending_state_deadline_listener, cb_data);
}

স্থির শূন্য FlushPendingEvents(SDL_Window *window)
{
    // Serialize and restore the pending flags, as they may be overwritten while flushing.
    ধ্রুব bool last_position_pending = window->last_position_pending;
    ধ্রুব bool last_size_pending = window->last_size_pending;

    যাবত্ (window->internal->pending_state_deadline_গুনতি) {
        WAYLAND_wl_display_roundtrip(window->internal->waylandData->display);
    }

    window->last_position_pending = last_position_pending;
    window->last_size_pending = last_size_pending;
}

/* While we can't get window position from the compositor, we do at least know
 * what monitor we're on, so let's send move events that put the window at the
 * center of the whatever display the wl_surface_listener events give us.
 */
শূন্য Wayland_UpdateWindowPosition(SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;
    SDL_DisplayData *display;

    যদি (wind->outputs && wind->অঙ্ক_outputs) {
        display = wind->outputs[wind->অঙ্ক_outputs - 1];
    } অন্যথা {
        // A window may not be on any displays if minimized.
        প্রত্যাগম;
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
    যদি (wind->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        যদি (!wind->waylandData->scale_to_display_enabled) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, display->logical.x, display->logical.y);
        } অন্যথা {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MOVED, display->pixel.x, display->pixel.y);
        }
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_DISPLAY_CHANGED, wind->last_displayID, 0);
    }
}

স্থির শূন্য SetFullscreen(SDL_Window *window, সংরচনা wl_output *output, bool fullscreen)
{
    SDL_WindowData *wind = window->internal;

#ifdef HAVE_LIBDECOR_H
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        যদি (!wind->shell_surface.libdecor.frame) {
            প্রত্যাগম; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? window->fullscreen_exclusive : false;
        যদি (fullscreen) {
            libdecor_frame_set_fullscreen(wind->shell_surface.libdecor.frame, output);
        } অন্যথা {
            libdecor_frame_unset_fullscreen(wind->shell_surface.libdecor.frame);
        }
    } অন্যথা
#endif
        যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        যদি (wind->shell_surface.xdg.toplevel.xdg_toplevel == রিক্ত) {
            প্রত্যাগম; // Can't do anything yet, wait for ShowWindow
        }

        wind->fullscreen_exclusive = output ? window->fullscreen_exclusive : false;
        যদি (fullscreen) {
            xdg_toplevel_set_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel, output);
        } অন্যথা {
            xdg_toplevel_unset_fullscreen(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        }
    }

    AddPendingStateSync(wind);
}

স্থির শূন্য UpdateWindowFullscreen(SDL_Window *window, bool fullscreen)
{
    SDL_WindowData *wind = window->internal;

    wind->is_fullscreen = fullscreen;

    যদি (fullscreen) {
        যদি (!(window->flags & SDL_WINDOW_FULLSCREEN)) {
            SDL_copyp(&window->current_fullscreen_mode, &window->requested_fullscreen_mode);
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
            SDL_UpdateFullscreenMode(window, SDL_FULLSCREEN_OP_ENTER, false);

            /* Set the output for exclusive fullscreen windows when entering fullscreen from a
             * compositor event, or if the fullscreen parameters were changed between the initial
             * fullscreen request and now, to ensure that the window is on the correct output,
             * as requested by the client.
             */
            যদি (window->fullscreen_exclusive && (!wind->fullscreen_exclusive || !wind->fullscreen_was_positioned)) {
                SDL_VideoDisplay *disp = SDL_GetVideoDisplay(window->current_fullscreen_mode.displayID);
                যদি (disp) {
                    wind->fullscreen_was_positioned = true;
                    SetFullscreen(window, disp->internal->output, true);
                }
            }
        }
    } অন্যথা {
        // Don't change the fullscreen flags if the window is hidden or being hidden.
        যদি ((window->flags & SDL_WINDOW_FULLSCREEN) && !window->is_hiding && !(window->flags & SDL_WINDOW_HIDDEN)) {
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

স্থির ধ্রুব সংরচনা wl_callback_listener surface_frame_listener;

স্থির শূন্য surface_frame_done(শূন্য *data, সংরচনা wl_callback *cb, uint32_t time)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;

    /* XXX: This is needed to work around an Nvidia egl-wayland bug due to buffer coordinates
     *      being used with wl_surface_damage, which causes part of the output to not be
     *      updated when using a viewport with an output region larger than the source region.
     */
    যদি (wl_compositor_get_version(wind->waylandData->compositor) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
        wl_surface_damage_buffer(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    } অন্যথা {
        wl_surface_damage(wind->surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
    }

    wind->pending_state_commit = false;

    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        যদি (wind->pending_config_ack) {
            wind->pending_config_ack = false;
            ConfigureWindowGeometry(wind->sdlwindow);
            xdg_surface_ack_configure(wind->shell_surface.xdg.surface, wind->shell_surface.xdg.serial);
        }
    } অন্যথা {
        wind->resizing = false;
    }

    যদি (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_SHOWN;

        // If any child windows are waiting on this window to be shown, show them now
        প্রতি (SDL_Window *w = wind->sdlwindow->first_child; w; w = w->next_sibling) {
            যদি (w->internal->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING) {
                Wayland_ShowWindow(SDL_GetVideoDevice(), w);
            } অন্যথা যদি (w->internal->reparenting_required) {
                Wayland_SetWindowParent(SDL_GetVideoDevice(), w, w->parent);
                যদি (w->flags & SDL_WINDOW_MODAL) {
                    Wayland_SetWindowModal(SDL_GetVideoDevice(), w, true);
                }
            }
        }

        /* If the window was initially set to the suspended state, send the occluded event now,
         * as we don't want to mark the window as occluded until at least one frame has been submitted.
         */
        যদি (wind->suspended) {
            SDL_SendWindowEvent(wind->sdlwindow, SDL_EVENT_WINDOW_OCCLUDED, 0, 0);
        }
    }

    wl_callback_destroy(cb);
    wind->surface_frame_callback = wl_surface_frame(wind->surface);
    wl_callback_add_listener(wind->surface_frame_callback, &surface_frame_listener, data);
}

স্থির ধ্রুব সংরচনা wl_callback_listener surface_frame_listener = {
    surface_frame_done
};

স্থির ধ্রুব সংরচনা wl_callback_listener gles_swap_frame_listener;

স্থির শূন্য gles_swap_frame_done(শূন্য *data, সংরচনা wl_callback *cb, uint32_t time)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    SDL_SetAtomicInt(&wind->swap_interval_ready, 1); // mark window as ready to present again.

    // reset this callback to fire again once a new frame was presented and compositor wants the next one.
    wind->gles_swap_frame_callback = wl_surface_frame(wind->gles_swap_frame_surface_wrapper);
    wl_callback_destroy(cb);
    wl_callback_add_listener(wind->gles_swap_frame_callback, &gles_swap_frame_listener, data);
}

স্থির ধ্রুব সংরচনা wl_callback_listener gles_swap_frame_listener = {
    gles_swap_frame_done
};

স্থির শূন্য handle_xdg_surface_configure(শূন্য *data, সংরচনা xdg_surface *xdg, uint32_t serial)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    SDL_Window *window = wind->sdlwindow;

    /* Interactive resizes are throttled by acking and committing only the most recent configuration at
     * the next frame callback, or certain combinations of clients and compositors can exhibit severe lag
     * when resizing.
     */
    wind->shell_surface.xdg.serial = serial;
    যদি (!wind->resizing) {
        wind->pending_config_ack = false;
        ConfigureWindowGeometry(window);
        xdg_surface_ack_configure(xdg, serial);
    } অন্যথা যদি (!wind->pending_config_ack) {
        wind->pending_config_ack = true;

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }

    যদি (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME;
    }
}

স্থির ধ্রুব সংরচনা xdg_surface_listener _xdg_surface_listener = {
    handle_xdg_surface_configure
};

স্থির শূন্য ApplyGeometryLimits(SDL_Window *window, পূর্ণাঙ্ক req_w, পূর্ণাঙ্ক req_h, পূর্ণাঙ্ক *out_w, পূর্ণাঙ্ক *out_h)
{
    SDL_WindowData *wind = window->internal;

    পূর্ণাঙ্ক w = req_w;
    পূর্ণাঙ্ক h = req_h;
    ধ্রুব ভিন্ন aspect = (ভিন্ন)req_w / (ভিন্ন)req_h;

    /* If adjusting for aspect causes the adjusted dimension to exceed the min/max limit, clamp to the limit
     * and attempt to adjust the opposite dimension to compensate.
     */
    যদি (!wind->resizing || (wind->resize_edge & WAYLAND_RESIZE_EDGE_CORNER) == WAYLAND_RESIZE_EDGE_CORNER) {
        যদি (window->min_aspect != 0.f && aspect < window->min_aspect) {
            h = SDL_max(SDL_lroundf((ভিন্ন)req_w / window->min_aspect), 1);

            যদি (h < window->min_h) {
                w = SDL_max(SDL_lroundf((ভিন্ন)window->min_h * window->min_aspect), 1);
            }
            যদি (window->max_h && h > window->max_h) {
                w = SDL_max(SDL_lroundf((ভিন্ন)window->max_h * window->min_aspect), 1);
            }
        } অন্যথা যদি (window->max_aspect != 0.f && aspect > window->max_aspect) {
            w = SDL_max(SDL_lroundf((ভিন্ন)req_h * window->max_aspect), 1);

            যদি (w < window->min_w) {
                h = SDL_max(SDL_lroundf((ভিন্ন)window->min_w / window->max_aspect), 1);
            }
            যদি (window->max_w && w > window->max_w) {
                h = SDL_max(SDL_lroundf((ভিন্ন)window->max_w / window->max_aspect), 1);
            }
        }
    } অন্যথা যদি (wind->resize_edge & WAYLAND_RESIZE_EDGE_LR) {
        যদি (window->min_aspect != 0.f && aspect < window->min_aspect) {
            h = SDL_max(SDL_lroundf((ভিন্ন)req_w / window->min_aspect), 1);

            যদি (h < window->min_h) {
                w = SDL_max(SDL_lroundf((ভিন্ন)window->min_h * window->min_aspect), 1);
            }
            যদি (window->max_h && h > window->max_h) {
                w = SDL_max(SDL_lroundf((ভিন্ন)window->max_h * window->min_aspect), 1);
            }
        } অন্যথা যদি (window->max_aspect != 0.f && aspect > window->max_aspect) {
            h = SDL_max(SDL_lroundf((ভিন্ন)req_w / window->max_aspect), 1);

            যদি (h < window->min_h) {
                w = SDL_max(SDL_lroundf((ভিন্ন)window->min_h * window->max_aspect), 1);
            }
            যদি (window->max_h && h > window->max_h) {
                w = SDL_max(SDL_lroundf((ভিন্ন)window->max_h * window->max_aspect), 1);
            }
        }
    } অন্যথা যদি (wind->resize_edge & WAYLAND_RESIZE_EDGE_TB) {
        যদি (window->min_aspect != 0.f && aspect < window->min_aspect) {
            w = SDL_max(SDL_lroundf((ভিন্ন)req_h * window->min_aspect), 1);

            যদি (w < window->min_w) {
                h = SDL_max(SDL_lroundf((ভিন্ন)window->min_w / window->min_aspect), 1);
            }
            যদি (window->max_w && w > window->max_w) {
                h = SDL_max(SDL_lroundf((ভিন্ন)window->max_w / window->min_aspect), 1);
            }
        } অন্যথা যদি (window->max_aspect != 0.f && aspect > window->max_aspect) {
            w = SDL_max(SDL_lroundf((ভিন্ন)req_h * window->max_aspect), 1);

            যদি (w < window->min_w) {
                h = SDL_max(SDL_lroundf((ভিন্ন)window->min_w / window->max_aspect), 1);
            }
            যদি (window->max_w && w > window->max_w) {
                h = SDL_max(SDL_lroundf((ভিন্ন)window->max_w / window->max_aspect), 1);
            }
        }
    }

    যদি (window->max_w) {
        w = SDL_min(w, window->max_w);
    }
    *out_w = SDL_max(w, window->min_w);

    যদি (window->max_h) {
        h = SDL_min(h, window->max_h);
    }
    *out_h = SDL_max(h, window->min_h);

}

স্থির শূন্য DetermineResizeAxis(SDL_WindowData *wind, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height, bool resizing)
{
    /* Try to determine the axis along which the window is being resized.
     *
     * Every compositor is different, and some will start sending strange values once the resize
     * begins, so only the first change is safe to try and determine the resize edge.
     *
     * Some compositors don't send a configure event with the resize flag cleared when the resize ends,
     * so a reset timer is required.
     */
    যদি (resizing) {
        ধ্রুব Uint64 now = SDL_GetTicksNS();
        যদি (now >= wind->last_resize_event_time_ns + SDL_MS_TO_NS(500)) {
            wind->resize_edge = 0;
        }

        wind->last_resize_event_time_ns = now;

        যদি (!wind->resize_edge) {
            যদি (width != wind->last_configure.width || !height) {
                wind->resize_edge |= WAYLAND_RESIZE_EDGE_LR;
            }
            যদি (height != wind->last_configure.height || !width) {
                wind->resize_edge |= WAYLAND_RESIZE_EDGE_TB;
            }
        }
    } অন্যথা {
        wind->resize_edge = 0;
    }

    wind->resizing = resizing;
}

স্থির শূন্য handle_xdg_toplevel_configure(শূন্য *data,
                                          সংরচনা xdg_toplevel *xdg_toplevel,
                                          int32_t width,
                                          int32_t height,
                                          সংরচনা wl_array *states)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    SDL_Window *window = wind->sdlwindow;

    গণনা xdg_toplevel_state *state;
    bool fullscreen = false;
    bool maximized = false;
    bool floating = true;
    bool tiled = false;
    bool active = false;
    bool resizing = false;
    bool suspended = false;
    wind->toplevel_constraints = 0;
    wl_array_for_each (state, states) {
        বিকল্প (*state) {
        পক্ষ XDG_TOPLEVEL_STATE_FULLSCREEN:
            fullscreen = true;
            floating = false;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_STATE_MAXIMIZED:
            maximized = true;
            floating = false;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_STATE_RESIZING:
            resizing = true;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_STATE_ACTIVATED:
            active = true;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_STATE_TILED_বাম:
        পক্ষ XDG_TOPLEVEL_STATE_TILED_ডান:
        পক্ষ XDG_TOPLEVEL_STATE_TILED_শীর্ষ:
        পক্ষ XDG_TOPLEVEL_STATE_TILED_BOTTOM:
            tiled = true;
            floating = false;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_STATE_SUSPENDED:
            suspended = true;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_STATE_CONSTRAINED_বাম:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_বাম;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_STATE_CONSTRAINED_ডান:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ডান;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_STATE_CONSTRAINED_শীর্ষ:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_শীর্ষ;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_STATE_CONSTRAINED_BOTTOM:
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
            ভঙ্গ;
        স্বভাব:
            ভঙ্গ;
        }
    }

    /* Configure sizes are in window geometry space; add the border insets, if any, to get
     * the surface size. Maximized and fullscreen windows must use the configured size as-is,
     * so a change in inset applicability requires re-adopting even an unchanged size, and
     * sizes adopted from the cached window size are converted back to geometry space for
     * the last_configure store.
     */
    ধ্রুব bool insets_apply = wind->enable_insets && !fullscreen && !maximized;

    // When resizing, dimensions other than 0 are a maximum.
    ধ্রুব bool new_configure_size = width != wind->last_configure.width || height != wind->last_configure.height ||
                                    insets_apply != wind->last_configure.insets_apply;

    BorderInsets insets = { 0, 0, 0, 0 };
    যদি (insets_apply) {
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
    যদি (active || !(window->flags & SDL_WINDOW_MINIMIZED)) {
        যদি (window->flags & SDL_WINDOW_MINIMIZED) {
            // If we were minimized, send a restored event before possibly sending maximized.
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_RESTORED, 0, 0);
        }
        SDL_SendWindowEvent(window,
                            (maximized && !fullscreen) ? SDL_EVENT_WINDOW_MAXIMIZED : SDL_EVENT_WINDOW_RESTORED,
                            0, 0);
    }

    যদি (!fullscreen) {
        /* xdg_toplevel spec states that this is a suggestion.
         * Ignore if less than or greater than max/min size.
         */
        যদি ((window->flags & SDL_WINDOW_RESIZABLE) || maximized) {
            যদি (!width) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                যদি (floating) {
                    width = window->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    যদি (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.width) {
                        width = SDL_min(wind->toplevel_bounds.width, width);
                    }
                } অন্যথা {
                    width = window->windowed.w;
                }

                যদি (!wind->scale_to_display) {
                    wind->requested.logical_width = width;
                } অন্যথা {
                    wind->requested.pixel_width = width;
                    width = wind->requested.logical_width = PixelToPoint(window, width);
                }
                width = SDL_max(width - (insets.বাম + insets.ডান), 1);
            } অন্যথা যদি (new_configure_size) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */

                wind->requested.logical_width = width + (insets.বাম + insets.ডান);

                যদি (wind->scale_to_display) {
                    wind->requested.pixel_width = PointToPixel(window, wind->requested.logical_width);
                }
            }
            যদি (!height) {
                /* This happens when the compositor indicates that the size is
                 * up to the client, so use the cached window size here.
                 */
                যদি (floating) {
                    height = window->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    যদি (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.height) {
                        height = SDL_min(wind->toplevel_bounds.height, height);
                    }
                } অন্যথা {
                    height = window->windowed.h;
                }

                যদি (!wind->scale_to_display) {
                    wind->requested.logical_height = height;
                } অন্যথা {
                    wind->requested.pixel_height = height;
                    height = wind->requested.logical_height = PixelToPoint(window, height);
                }
                height = SDL_max(height - (insets.শীর্ষ + insets.bottom), 1);
            } অন্যথা যদি (new_configure_size) {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 */
                wind->requested.logical_height = height + (insets.শীর্ষ + insets.bottom);

                যদি (wind->scale_to_display) {
                    wind->requested.pixel_height = PointToPixel(window, wind->requested.logical_height);
                }
            }
        } অন্যথা {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            যদি (!wind->scale_to_display) {
                width = wind->requested.logical_width = window->floating.w;
                height = wind->requested.logical_height = window->floating.h;
            } অন্যথা {
                wind->requested.pixel_width = window->floating.w;
                wind->requested.pixel_height = window->floating.h;
                width = wind->requested.logical_width = PixelToPoint(window, window->floating.w);
                height = wind->requested.logical_height = PixelToPoint(window, window->floating.h);
            }
            width = SDL_max(width - (insets.বাম + insets.ডান), 1);
            height = SDL_max(height - (insets.শীর্ষ + insets.bottom), 1);
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
        যদি (floating) {
            যদি (!wind->scale_to_display) {
                ApplyGeometryLimits(window, wind->requested.logical_width, wind->requested.logical_height, &wind->requested.logical_width, &wind->requested.logical_height);
            } অন্যথা {
                ApplyGeometryLimits(window, wind->requested.pixel_width, wind->requested.pixel_height, &wind->requested.pixel_width, &wind->requested.pixel_height);

                wind->requested.logical_width = PixelToPoint(window, wind->requested.pixel_width);
                wind->requested.logical_height = PixelToPoint(window, wind->requested.pixel_height);
            }
        }
    } অন্যথা {
        // Fullscreen windows know their exact size.
        যদি (width == 0 || height == 0) {
            width = wind->requested.logical_width;
            height = wind->requested.logical_height;
        } অন্যথা {
            wind->requested.logical_width = width;
            wind->requested.logical_height = height;
        }

        যদি (wind->scale_to_display) {
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

স্থির শূন্য handle_xdg_toplevel_close(শূন্য *data, সংরচনা xdg_toplevel *xdg_toplevel)
{
    SDL_WindowData *window = (SDL_WindowData *)data;
    SDL_SendWindowEvent(window->sdlwindow, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
}

স্থির শূন্য handle_xdg_toplevel_configure_bounds(শূন্য *data,
                                                 সংরচনা xdg_toplevel *xdg_toplevel,
                                                 int32_t width, int32_t height)
{
    SDL_WindowData *window = (SDL_WindowData *)data;
    window->toplevel_bounds.width = width;
    window->toplevel_bounds.height = height;
}

স্থির শূন্য handle_xdg_toplevel_wm_capabilities(শূন্য *data,
                                                সংরচনা xdg_toplevel *xdg_toplevel,
                                                সংরচনা wl_array *capabilities)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    গণনা xdg_toplevel_wm_capabilities *wm_cap;

    wind->wm_caps = 0;

    wl_array_for_each (wm_cap, capabilities) {
        বিকল্প (*wm_cap) {
        পক্ষ XDG_TOPLEVEL_WM_CAPABILITIES_WINDOW_MENU:
            wind->wm_caps |= WAYLAND_WM_CAPS_WINDOW_MENU;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_WM_CAPABILITIES_MAXIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MAXIMIZE;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_WM_CAPABILITIES_FULLSCREEN:
            wind->wm_caps |= WAYLAND_WM_CAPS_FULLSCREEN;
            ভঙ্গ;
        পক্ষ XDG_TOPLEVEL_WM_CAPABILITIES_MINIMIZE:
            wind->wm_caps |= WAYLAND_WM_CAPS_MINIMIZE;
            ভঙ্গ;
        স্বভাব:
            ভঙ্গ;
        }
    }
}

স্থির ধ্রুব সংরচনা xdg_toplevel_listener toplevel_listener_xdg = {
    handle_xdg_toplevel_configure,
    handle_xdg_toplevel_close,
    handle_xdg_toplevel_configure_bounds, // Version 4
    handle_xdg_toplevel_wm_capabilities   // Version 5
};

স্থির শূন্য handle_xdg_popup_configure(শূন্য *data,
                                       সংরচনা xdg_popup *xdg_popup,
                                       int32_t x,
                                       int32_t y,
                                       int32_t width,
                                       int32_t height)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    পূর্ণাঙ্ক offset_x = 0, offset_y = 0;

    // Adjust the position if it was offset for libdecor
    AdjustPopupOffset(wind->sdlwindow, &offset_x, &offset_y);
    x -= offset_x;
    y -= offset_y;

    /* This happens when the compositor indicates that the size is
     * up to the client, so use the cached window size here.
     */
    যদি (width == 0 || height == 0) {
        width = wind->sdlwindow->floating.w;
        height = wind->sdlwindow->floating.h;
    }

    /* Don't apply the supplied dimensions if they haven't changed from the last configuration
     * event, or a newer size set programmatically can be overwritten by old data.
     */
    যদি (width != wind->last_configure.width || height != wind->last_configure.height) {
        wind->requested.logical_width = width;
        wind->requested.logical_height = height;

        যদি (wind->scale_to_display) {
            wind->requested.pixel_width = PointToPixel(wind->sdlwindow, width);
            wind->requested.pixel_height = PointToPixel(wind->sdlwindow, height);
        }
    }

    যদি (wind->scale_to_display) {
        x = PointToPixel(wind->sdlwindow->parent, x);
        y = PointToPixel(wind->sdlwindow->parent, y);
    }

    SDL_SendWindowEvent(wind->sdlwindow, SDL_EVENT_WINDOW_MOVED, x, y);

    wind->last_configure.width = width;
    wind->last_configure.height = height;

    যদি (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME;
    }
}

স্থির শূন্য handle_xdg_popup_done(শূন্য *data, সংরচনা xdg_popup *xdg_popup)
{
    SDL_WindowData *window = (SDL_WindowData *)data;
    SDL_SendWindowEvent(window->sdlwindow, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
}

স্থির শূন্য handle_xdg_popup_repositioned(শূন্য *data,
                                          সংরচনা xdg_popup *xdg_popup,
                                          uint32_t token)
{
    // No-op, configure does all the work we care about
}

স্থির ধ্রুব সংরচনা xdg_popup_listener _xdg_popup_listener = {
    handle_xdg_popup_configure,
    handle_xdg_popup_done,
    handle_xdg_popup_repositioned
};

স্থির শূন্য handle_xdg_toplevel_decoration_configure(শূন্য *data,
                                                     সংরচনা zxdg_toplevel_decoration_v1 *zxdg_toplevel_decoration_v1,
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
    যদি (mode == ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE) {
        যদি (window->flags & SDL_WINDOW_BORDERLESS) {
            // borderless windows do request CSD, so we got what we wanted
            প্রত্যাগম;
        }
        যদি (!Wayland_LoadLibdecor(internal->waylandData, true)) {
            // libdecor isn't available, so no borders for you... oh well
            প্রত্যাগম;
        }
        WAYLAND_wl_display_roundtrip(internal->waylandData->display);

        Wayland_HideWindow(device, window);
        internal->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        Wayland_ShowWindow(device, window);
    }
}

স্থির ধ্রুব সংরচনা zxdg_toplevel_decoration_v1_listener xdg_toplevel_decoration_listener = {
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
স্থির শূন্য OverrideLibdecorLimits(SDL_Window *window)
{
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    যদি (!libdecor_frame_get_min_content_size) {
        libdecor_frame_set_min_content_size(window->internal->shell_surface.libdecor.frame, window->min_w, window->min_h);
    }
#নোচেদ্যদি !SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
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
স্থির শূন্য LibdecorGetMinContentSize(সংরচনা libdecor_frame *frame, পূর্ণাঙ্ক *min_w, পূর্ণাঙ্ক *min_h)
{
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    যদি (libdecor_frame_get_min_content_size != রিক্ত) {
        libdecor_frame_get_min_content_size(frame, min_w, min_h);
    }
#নোচেদ্যদি SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
    libdecor_frame_get_min_content_size(frame, min_w, min_h);
#endif
}

স্থির শূন্য decoration_frame_configure(সংরচনা libdecor_frame *frame,
                                       সংরচনা libdecor_configuration *configuration,
                                       শূন্য *user_data)
{
    SDL_WindowData *wind = (SDL_WindowData *)user_data;
    SDL_Window *window = wind->sdlwindow;

    গণনা libdecor_window_state window_state;
    পূর্ণাঙ্ক width, height;

    bool active = false;
    bool fullscreen = false;
    bool maximized = false;
    bool tiled = false;
    bool suspended = false;
    bool resizing = false;
    wind->toplevel_constraints = 0;

    স্থির ধ্রুব গণনা libdecor_window_state tiled_states = (LIBDECOR_WINDOW_STATE_TILED_বাম | LIBDECOR_WINDOW_STATE_TILED_ডান |
                                                            LIBDECOR_WINDOW_STATE_TILED_শীর্ষ | LIBDECOR_WINDOW_STATE_TILED_BOTTOM);

    যদি (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        LibdecorGetMinContentSize(frame, &wind->system_limits.min_width, &wind->system_limits.min_height);
    }

    // Window State
    যদি (libdecor_configuration_get_window_state(configuration, &window_state)) {
        fullscreen = (window_state & LIBDECOR_WINDOW_STATE_FULLSCREEN) != 0;
        maximized = (window_state & LIBDECOR_WINDOW_STATE_MAXIMIZED) != 0;
        active = (window_state & LIBDECOR_WINDOW_STATE_ACTIVE) != 0;
        tiled = (window_state & tiled_states) != 0;
#যদি SDL_LIBDECOR_CHECK_VERSION(0, 2, 0)
        suspended = (window_state & LIBDECOR_WINDOW_STATE_SUSPENDED) != 0;
#endif
#যদি SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
        resizing = (window_state & LIBDECOR_WINDOW_STATE_RESIZING) != 0;

        যদি (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_বাম) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_বাম;
        }
        যদি (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_ডান) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_ডান;
        }
        যদি (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_শীর্ষ) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_শীর্ষ;
        }
        যদি (window_state & LIBDECOR_WINDOW_STATE_CONSTRAINED_BOTTOM) {
            wind->toplevel_constraints |= WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM;
        }
#endif
    }
    ধ্রুব bool floating = !(fullscreen || maximized || tiled);

    UpdateWindowFullscreen(window, fullscreen);

    /* Always send a maximized/restore event; if the event is redundant it will
     * automatically be discarded (see src/events/SDL_windowevents.c)
     *
     * No, we do not get minimize events from libdecor, however, the minimized
     * state can be programmatically set. The meaning of 'minimized' is compositor
     * dependent, but in general, we can assume that the flag should remain set until
     * the next focused configure event occurs.
     */
    যদি (active || !(window->flags & SDL_WINDOW_MINIMIZED)) {
        যদি (window->flags & SDL_WINDOW_MINIMIZED) {
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
    যদি (fullscreen) {
        যদি (!libdecor_configuration_get_content_size(configuration, frame, &width, &height)) {
            width = wind->requested.logical_width;
            height = wind->requested.logical_height;
        } অন্যথা {
            // Fullscreen windows know their exact size.
            wind->requested.logical_width = width;
            wind->requested.logical_height = height;

            যদি (wind->scale_to_display) {
                wind->requested.pixel_width = PointToPixel(window, width);
                wind->requested.pixel_height = PointToPixel(window, height);
            }
        }
    } অন্যথা {
        যদি (!(window->flags & SDL_WINDOW_RESIZABLE) && !maximized) {
            /* If we're a fixed-size, non-maximized window, we know our size for sure.
             * Always assume the configure is wrong.
             */
            যদি (!wind->scale_to_display) {
                width = wind->requested.logical_width = window->floating.w;
                height = wind->requested.logical_height = window->floating.h;
            } অন্যথা {
                wind->requested.pixel_width = window->floating.w;
                wind->requested.pixel_height = window->floating.h;
                width = wind->requested.logical_width = PixelToPoint(window, window->floating.w);
                height = wind->requested.logical_height = PixelToPoint(window, window->floating.h);
            }

            OverrideLibdecorLimits(window);
        } অন্যথা {
            /* XXX: The libdecor cairo plugin sends bogus content sizes that add the
             *      height of the title bar when transitioning from a fixed-size to
             *      floating state. Ignore the sent window dimensions in this case,
             *      in favor of the cached value to avoid the window increasing in
             *      size after every state transition.
             *
             *      https://gitlab.freedesktop.org/libdecor/libdecor/-/issues/34
             */
            যদি ((floating && (!wind->floating && !(window->flags & SDL_WINDOW_BORDERLESS))) ||
                !libdecor_configuration_get_content_size(configuration, frame, &width, &height)) {
                width = 0;
                height = 0;
            }

            ধ্রুব bool new_configure_size = width != wind->last_configure.width || height != wind->last_configure.height;
            DetermineResizeAxis(wind, width, height, resizing);

            যদি (!width) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                যদি (floating) {
                    width = window->floating.w;

                    // Clamp the window to the toplevel bounds, if any are set.
                    যদি (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.width) {
                        width = SDL_min(wind->toplevel_bounds.width, width);
                    }
                } অন্যথা {
                    width = window->windowed.w;
                }

                যদি (!wind->scale_to_display) {
                    wind->requested.logical_width = width;
                } অন্যথা {
                    wind->requested.pixel_width = width;
                    width = wind->requested.logical_width = PixelToPoint(window, width);
                }
            } অন্যথা {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                যদি (new_configure_size &&
                    !(wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME && wind->suspended != suspended)) {
                    wind->requested.logical_width = width;

                    যদি (wind->scale_to_display) {
                        wind->requested.pixel_width = PointToPixel(window, width);
                    }
                }
            }

            যদি (!height) {
                /* This happens when we're being restored from a non-floating state,
                 * or the compositor indicates that the size is up to the client, so
                 * used the cached window size here.
                 */
                যদি (floating) {
                    height = window->floating.h;

                    // Clamp the window to the toplevel bounds, if any are set.
                    যদি (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE && wind->toplevel_bounds.height) {
                        height = SDL_min(wind->toplevel_bounds.height, height);
                    }
                } অন্যথা {
                    height = window->windowed.h;
                }

                যদি (!wind->scale_to_display) {
                    wind->requested.logical_height = height;
                } অন্যথা {
                    wind->requested.pixel_height = height;
                    height = wind->requested.logical_height = PixelToPoint(window, height);
                }
            } অন্যথা {
                /* Don't apply the supplied dimensions if they haven't changed from the last configuration
                 * event, or a newer size set programmatically can be overwritten by old data.
                 *
                 * If a client takes a long time to present the first frame after creating the window, a
                 * configure event to set the suspended state may arrive with the content size increased
                 * by the decoration dimensions, which should also be ignored.
                 */
                যদি (new_configure_size &&
                    !(wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME && wind->suspended != suspended)) {
                    wind->requested.logical_height = height;

                    যদি (wind->scale_to_display) {
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
        যদি (floating) {
            যদি (!wind->scale_to_display) {
                ApplyGeometryLimits(window, wind->requested.logical_width, wind->requested.logical_height, &wind->requested.logical_width, &wind->requested.logical_height);
            } অন্যথা {
                ApplyGeometryLimits(window, wind->requested.pixel_width, wind->requested.pixel_height, &wind->requested.pixel_width, &wind->requested.pixel_height);

                wind->requested.logical_width = PixelToPoint(window, wind->requested.pixel_width);
                wind->requested.logical_height = PixelToPoint(window, wind->requested.pixel_height);
            }
        }
    }

    // Store the new state.
    ধ্রুব bool started_resize = !wind->resizing && resizing;
    wind->last_configure.width = width;
    wind->last_configure.height = height;
    wind->floating = floating;
    wind->suspended = suspended;
    wind->active = active;
    window->tiled = tiled;
    wind->resizing = resizing;

    // Update the window manager capabilities.
#যদি SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
    গণনা libdecor_wm_capabilities caps;
#ifdef SDL_VIDEO_DRIVER_WAYLAND_DYNAMIC_LIBDECOR
    যদি (libdecor_frame_get_wm_capabilities) {
        caps = libdecor_frame_get_wm_capabilities(wind->shell_surface.libdecor.frame);
#অন্যথা
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

    যদি (!wind->resizing || started_resize) {
        /* Calculate the new window geometry and commit the changes on the libdecor side.
         *
         * XXX: This will potentially leave un-acked configurations, but libdecor invalidates the
         *      configuration upon returning from the frame event, so there is nothing that can be
         *      done, unless libdecor adds the ability to copy or refcount the configuration state
         *      to apply later.
         */
        ConfigureWindowGeometry(window);
        সংরচনা libdecor_state *state = libdecor_state_new(wind->current.logical_width, wind->current.logical_height);
        libdecor_frame_commit(frame, state, configuration);
        libdecor_state_free(state);

        // Always send an exposure event during a new frame to ensure forward progress if the frame callback already occurred.
        যদি (started_resize) {
            SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
        }
    }

    যদি (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
        wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME;
    }
}

স্থির শূন্য decoration_frame_close(সংরচনা libdecor_frame *frame, শূন্য *user_data)
{
    SDL_SendWindowEvent(((SDL_WindowData *)user_data)->sdlwindow, SDL_EVENT_WINDOW_CLOSE_REQUESTED, 0, 0);
}

স্থির শূন্য decoration_frame_commit(সংরচনা libdecor_frame *frame, শূন্য *user_data)
{
    /* libdecor decoration subsurfaces are synchronous, so the client needs to
     * commit a frame to trigger an update of the decoration surfaces.
     */
    SDL_WindowData *wind = (SDL_WindowData *)user_data;
    যদি (!wind->suspended && wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        SDL_SendWindowEvent(wind->sdlwindow, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
    }
}

স্থির শূন্য decoration_dismiss_popup(সংরচনা libdecor_frame *frame, ধ্রুব বর্ণ *seat_name, শূন্য *user_data)
{
    // NOP
}

#যদি SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
স্থির শূন্য decoration_frame_bounds(সংরচনা libdecor_frame *frame, পূর্ণাঙ্ক width, পূর্ণাঙ্ক height, শূন্য *user_data)
{
    SDL_WindowData *window = (SDL_WindowData *)user_data;
    window->toplevel_bounds.width = width;
    window->toplevel_bounds.height = height;
}
#endif

স্থির সংরচনা libdecor_frame_interface libdecor_frame_interface = {
    decoration_frame_configure,
    decoration_frame_close,
    decoration_frame_commit,
    decoration_dismiss_popup,
#যদি SDL_LIBDECOR_CHECK_VERSION(0, 3, 0)
    decoration_frame_bounds
#endif
};
#endif

স্থির শূন্য Wayland_HandlePreferredScaleChanged(SDL_WindowData *window_data, দ্বিগুণ factor)
{
    ধ্রুব দ্বিগুণ old_factor = window_data->scale_factor;

    // Round the scale factor if viewports aren't available.
    যদি (!window_data->viewport) {
        factor = SDL_ceil(factor);
    }

    যদি (factor != old_factor) {
        window_data->scale_factor = factor;

        যদি (window_data->scale_to_display) {
            /* If the window is in the floating state with a user/application specified size, calculate the new
             * logical size from the backbuffer size. Otherwise, use the fixed underlying logical size to calculate
             * the new backbuffer dimensions.
             */
            যদি (window_data->floating) {
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
                window_data->last_configure.width = SDL_max(window_data->requested.logical_width - (insets.বাম + insets.ডান), 1);
                window_data->last_configure.height = SDL_max(window_data->requested.logical_height - (insets.শীর্ষ + insets.bottom), 1);

                window_data->requested.logical_width = PixelToPoint(window_data->sdlwindow, window_data->requested.pixel_width);
                window_data->requested.logical_height = PixelToPoint(window_data->sdlwindow, window_data->requested.pixel_height);
            } অন্যথা {
                window_data->requested.pixel_width = PointToPixel(window_data->sdlwindow, window_data->requested.logical_width);
                window_data->requested.pixel_height = PointToPixel(window_data->sdlwindow, window_data->requested.logical_height);
            }
        }

        যদি (window_data->sdlwindow->flags & SDL_WINDOW_উপরের_PIXEL_DENSITY || window_data->scale_to_display) {
            ConfigureWindowGeometry(window_data->sdlwindow);
            CommitLibdecorFrame(window_data->sdlwindow);
        }
    }
}

স্থির শূন্য Wayland_MaybeUpdateScaleFactor(SDL_WindowData *window)
{
    দ্বিগুণ factor;
    পূর্ণাঙ্ক i;

    /* If the fractional scale protocol is present or the core protocol supports the
     * preferred buffer scale event, the compositor will explicitly tell the application
     * what scale it wants via these events, so don't try to determine the scale factor
     * from which displays the surface has entered.
     */
    যদি (window->fractional_scale || wl_surface_get_version(window->surface) >= WL_SURFACE_PREFERRED_BUFFER_SCALE_SINCE_VERSION) {
        প্রত্যাগম;
    }

    যদি (window->অঙ্ক_outputs != 0) {
        // Check every display's factor, use the highest
        factor = 0.0;
        প্রতি (i = 0; i < window->অঙ্ক_outputs; i++) {
            SDL_DisplayData *internal = window->outputs[i];
            factor = SDL_max(factor, internal->scale_factor);
        }
    } অন্যথা {
        // All outputs removed, just fall back.
        factor = window->scale_factor;
    }

    Wayland_HandlePreferredScaleChanged(window, factor);
}

শূন্য Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < window->অঙ্ক_outputs; i++) {
        যদি (window->outputs[i] == display_data) { // remove this one
            যদি (i == (window->অঙ্ক_outputs - 1)) {
                window->outputs[i] = রিক্ত;
            } অন্যথা {
                SDL_memmove(&window->outputs[i],
                            &window->outputs[i + 1],
                            পরিমাণ(SDL_DisplayData *) * ((window->অঙ্ক_outputs - i) - 1));
            }
            window->অঙ্ক_outputs--;
            i--;
        }
    }

    যদি (window->অঙ্ক_outputs == 0) {
        SDL_free(window->outputs);
        window->outputs = রিক্ত;
    } অন্যথা যদি (!window->is_fullscreen || window->অঙ্ক_outputs == 1) {
        Wayland_UpdateWindowPosition(window->sdlwindow);
        Wayland_MaybeUpdateScaleFactor(window);
    }
}

স্থির শূন্য handle_surface_enter(শূন্য *data, সংরচনা wl_surface *surface, সংরচনা wl_output *output)
{
    SDL_WindowData *window = data;
    SDL_DisplayData *internal = wl_output_get_user_data(output);
    SDL_DisplayData **new_outputs;

    যদি (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        প্রত্যাগম;
    }

    new_outputs = SDL_realloc(window->outputs,
                              পরিমাণ(SDL_DisplayData *) * (window->অঙ্ক_outputs + 1));
    যদি (!new_outputs) {
        প্রত্যাগম;
    }
    window->outputs = new_outputs;
    window->outputs[window->অঙ্ক_outputs++] = internal;

    // Update the scale factor after the move so that fullscreen outputs are updated.
    যদি (!window->is_fullscreen || window->অঙ্ক_outputs == 1) {
        Wayland_UpdateWindowPosition(window->sdlwindow);
        Wayland_MaybeUpdateScaleFactor(window);
    }
}

স্থির শূন্য handle_surface_leave(শূন্য *data, সংরচনা wl_surface *surface, সংরচনা wl_output *output)
{
    SDL_WindowData *window = (SDL_WindowData *)data;

    যদি (!SDL_WAYLAND_own_output(output) || !SDL_WAYLAND_own_surface(surface)) {
        প্রত্যাগম;
    }

    Wayland_RemoveOutputFromWindow(window, (SDL_DisplayData *)wl_output_get_user_data(output));
}

স্থির শূন্য handle_surface_preferred_buffer_scale(শূন্য *data, সংরচনা wl_surface *wl_surface, int32_t factor)
{
    SDL_WindowData *wind = data;

    /* The spec is unclear on how this interacts with the fractional scaling protocol,
     * so, for now, assume that the fractional scaling protocol takes priority and
     * only listen to this event if the fractional scaling protocol is not present.
     */
    যদি (!wind->fractional_scale) {
        Wayland_HandlePreferredScaleChanged(data, (দ্বিগুণ)factor);
    }
}

স্থির শূন্য handle_surface_preferred_buffer_transform(শূন্য *data, সংরচনা wl_surface *wl_surface, uint32_t transform)
{
    // Nothing to do here.
}

স্থির ধ্রুব সংরচনা wl_surface_listener surface_listener = {
    handle_surface_enter,
    handle_surface_leave,
    handle_surface_preferred_buffer_scale,
    handle_surface_preferred_buffer_transform
};

স্থির শূন্য handle_fractional_scale_preferred(শূন্য *data, সংরচনা wp_fractional_scale_v1 *wp_fractional_scale_v1, uint32_t scale)
{
    ধ্রুব দ্বিগুণ factor = (দ্বিগুণ)scale / 120.; // 120 is a magic number defined in the spec as a common denominator
    Wayland_HandlePreferredScaleChanged(data, factor);
}

স্থির ধ্রুব সংরচনা wp_fractional_scale_v1_listener fractional_scale_listener = {
    handle_fractional_scale_preferred
};

স্থির শূন্য frog_preferred_metadata_handler(শূন্য *data, সংরচনা frog_color_managed_surface *frog_color_managed_surface, uint32_t transfer_function,
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

    বিকল্প (transfer_function) {
    পক্ষ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_ST2084_PQ:
        /* ITU-R BT.2408-7 (Sept 2023) has the reference PQ white level at 203 nits,
         * while older Dolby documentation claims a reference level of 100 nits.
         *
         * Use 203 nits for now.
         */
        HDR.HDR_headroom = max_luminance / 203.0f;
        ভঙ্গ;
    পক্ষ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SCRGB_LINEAR:
        HDR.HDR_headroom = max_luminance / 80.0f;
        ভঙ্গ;
    পক্ষ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_UNDEFINED:
    পক্ষ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_SRGB:
    পক্ষ FROG_COLOR_MANAGED_SURFACE_TRANSFER_FUNCTION_GAMMA_22:
    স্বভাব:
        HDR.HDR_headroom = 1.0f;
        ভঙ্গ;
    }

    HDR.SDR_white_level = 1.0f;
    SDL_SetWindowHDRProperties(wind->sdlwindow, &HDR, true);
}

স্থির ধ্রুব সংরচনা frog_color_managed_surface_listener frog_surface_listener = {
    frog_preferred_metadata_handler
};


স্থির শূন্য handle_surface_feedback_preferred_changed2(শূন্য *data,
                                                       সংরচনা wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                       uint32_t identity_hi, uint32_t identity_lo)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    Wayland_GetColorInfoForWindow(wind, false);
}

স্থির শূন্য handle_surface_feedback_preferred_changed(শূন্য *data,
                                                      সংরচনা wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback_v1,
                                                      uint32_t identity)
{
    handle_surface_feedback_preferred_changed2(data, wp_color_management_surface_feedback_v1, 0, identity);
}

স্থির ধ্রুব সংরচনা wp_color_management_surface_feedback_v1_listener color_management_surface_feedback_listener = {
    handle_surface_feedback_preferred_changed,
    handle_surface_feedback_preferred_changed2
};

স্থির শূন্য Wayland_SetKeyboardFocus(SDL_Window *window, bool set_focus)
{
    SDL_Window *toplevel = window;

    // Find the toplevel parent
    যাবত্ (SDL_WINDOW_IS_POPUP(toplevel)) {
        toplevel = toplevel->parent;
    }

    toplevel->keyboard_focus = window;

    যদি (set_focus && !window->is_hiding && !window->is_destroying) {
        SDL_SetKeyboardFocus(window);
    }
}

bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled)
{
    প্রত্যাগম true; // just succeed, the real work is done elsewhere.
}

স্থির সংরচনা xdg_toplevel *GetToplevelForWindow(SDL_WindowData *wind)
{
    যদি (wind) {
        /* Libdecor crashes on attempts to unset the parent by passing null, which is allowed by the
         * toplevel spec, so just use the raw xdg-toplevel instead (that's what libdecor does
         * internally anyways).
         */
#ifdef HAVE_LIBDECOR_H
        যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
            প্রত্যাগম libdecor_frame_get_xdg_toplevel(wind->shell_surface.libdecor.frame);
        } অন্যথা
#endif
            যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
                প্রত্যাগম wind->shell_surface.xdg.toplevel.xdg_toplevel;
            }
    }

    প্রত্যাগম রিক্ত;
}

bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window)
{
    SDL_WindowData *child_data = window->internal;
    SDL_WindowData *parent_data = parent_window ? parent_window->internal : রিক্ত;

    child_data->reparenting_required = false;

    যদি (parent_data && parent_data->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        // Need to wait for the parent to become mapped, or it's the same as setting a null parent.
        child_data->reparenting_required = true;
        প্রত্যাগম true;
    }

    সংরচনা xdg_toplevel *child_toplevel = GetToplevelForWindow(child_data);
    সংরচনা xdg_toplevel *parent_toplevel = GetToplevelForWindow(parent_data);

    যদি (child_toplevel) {
        xdg_toplevel_set_parent(child_toplevel, parent_toplevel);
    }

    প্রত্যাগম true;
}

bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_WindowData *data = window->internal;
    SDL_WindowData *parent_data = window->parent->internal;

    যদি (parent_data->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        // Need to wait for the parent to become mapped before changing modal status.
        data->reparenting_required = true;
        প্রত্যাগম true;
    } অন্যথা {
        data->reparenting_required = false;
    }

    সংরচনা xdg_toplevel *toplevel = GetToplevelForWindow(data);

    যদি (toplevel) {
        যদি (viddata->xdg_wm_dialog_v1) {
            যদি (modal) {
                যদি (!data->xdg_dialog_v1) {
                    data->xdg_dialog_v1 = xdg_wm_dialog_v1_get_xdg_dialog(viddata->xdg_wm_dialog_v1, toplevel);
                }

                xdg_dialog_v1_set_modal(data->xdg_dialog_v1);
            } অন্যথা যদি (data->xdg_dialog_v1) {
                xdg_dialog_v1_unset_modal(data->xdg_dialog_v1);
            }
        }
    }

    প্রত্যাগম true;
}

স্থির শূন্য Wayland_RegisterToplevelForSession(SDL_WindowData *data)
{
    সংরচনা xdg_toplevel *toplevel = GetToplevelForWindow(data);
    যদি (!toplevel) {
        প্রত্যাগম;
    }

    ধ্রুব বর্ণ *id = SDL_GetStringProperty(data->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_WINDOW_ID_STRING, রিক্ত);
    যদি (id && *id != '\0') {
        SDL_VideoDevice *viddev = SDL_GetVideoDevice();
        SDL_VideoData *viddata = viddev->internal;

        যদি (viddata->xdg_toplevel_tag_manager) {
            xdg_toplevel_tag_manager_v1_set_toplevel_tag(viddata->xdg_toplevel_tag_manager, toplevel, id);
        }

        যদি (viddata->xdg_session_manager) {
            Wayland_CreateSession(viddata);

            যদি (viddata->xdg_session) {
                CHECK_PARAM (true) {
                    // Windows added to a session must not have a duplicate ID string, or a protocol error will result.
                    প্রতি (SDL_Window *w = viddev->windows; w; w = w->next) {
                        SDL_WindowData *d = w->internal;
                        যদি (d->session_id && SDL_strcmp(d->session_id, id) == 0) {
                            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Duplicate window ID string %s found; window will not be added to session", id);
                            প্রত্যাগম;
                        }
                    }
                }

                data->xdg_toplevel_session = xdg_session_v1_restore_toplevel(viddata->xdg_session, toplevel, id);
                data->session_id = SDL_strdup(id);
            }
        }
    }
}

স্থির শূন্য Wayland_DestroyToplevelSession(SDL_WindowData *data)
{
    SDL_VideoData *viddata = data->waylandData;

    যদি (data->xdg_toplevel_session) {
        ধ্রুব বর্ণ *id = SDL_GetStringProperty(data->sdlwindow->props, SDL_PROP_WINDOW_WAYLAND_WINDOW_ID_STRING, রিক্ত);

        // If the ID string was cleared, remove the window from the session.
        যদি (!id || *id == '\0') {
            xdg_session_v1_remove_toplevel(viddata->xdg_session, data->session_id);
        }

        xdg_toplevel_session_v1_destroy(data->xdg_toplevel_session);
        data->xdg_toplevel_session = রিক্ত;

        SDL_free(data->session_id);
        data->session_id = রিক্ত;
    }
}

স্থির শূন্য show_hide_sync_handler(শূন্য *data, সংরচনা wl_callback *callback, uint32_t callback_data)
{
    // Get the window from the ID as it may have been destroyed
    SDL_WindowID windowID = (SDL_WindowID)((uintptr_t)data);
    SDL_Window *window = SDL_GetWindowFromID(windowID);

    যদি (window && window->internal) {
        SDL_WindowData *wind = window->internal;
        wind->show_hide_sync_required = false;
    }

    wl_callback_destroy(callback);
}

স্থির সংরচনা wl_callback_listener show_hide_sync_listener = {
    show_hide_sync_handler
};

স্থির শূন্য exported_handle_handler(শূন্য *data, সংরচনা zxdg_exported_v2 *zxdg_exported_v2, ধ্রুব বর্ণ *handle)
{
    SDL_WindowData *wind = (SDL_WindowData *)data;
    SDL_PropertiesID props = SDL_GetWindowProperties(wind->sdlwindow);

    SDL_SetStringProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, handle);
}

স্থির সংরচনা zxdg_exported_v2_listener exported_v2_listener = {
    exported_handle_handler
};

শূন্য Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *c = _this->internal;
    SDL_WindowData *data = window->internal;
    SDL_PropertiesID props = SDL_GetWindowProperties(window);

    // Custom surfaces don't get toplevels and are always considered 'shown'; nothing to do here.
    যদি (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        প্রত্যাগম;
    }

    /* If this is a child window, the parent *must* be in the final shown state,
     * meaning that it has received a configure event, followed by a frame callback.
     * If not, a race condition can result, with effects ranging from the child
     * window to spuriously closing to protocol errors.
     *
     * If waiting on the parent window, set the pending status and the window will
     * be shown when the parent is in the shown state.
     */
    যদি (window->parent) {
        যদি (window->parent->internal->shell_surface_status != WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
            data->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING;
            প্রত্যাগম;
        }
    }

    // Always roundtrip to ensure there are no pending buffer attachments.
    কুরু {
        WAYLAND_wl_display_roundtrip(c->display);
    } যাবত্ (data->show_hide_sync_required);

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
    wl_surface_attach(data->surface, রিক্ত, 0, 0);
    wl_surface_commit(data->surface);

    // Create the shell surface and map the toplevel/popup
#ifdef HAVE_LIBDECOR_H
    যদি (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        data->shell_surface.libdecor.frame = libdecor_decorate(c->shell.libdecor,
                                                               data->surface,
                                                               &libdecor_frame_interface,
                                                               data);
        যদি (!data->shell_surface.libdecor.frame) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Failed to create libdecor frame!");
        } অন্যথা {
            libdecor_frame_set_app_id(data->shell_surface.libdecor.frame, data->app_id);
            libdecor_frame_map(data->shell_surface.libdecor.frame);
            যদি (window->flags & SDL_WINDOW_BORDERLESS) {
                // Note: Calling this with 'true' immediately after mapping will cause the libdecor Cairo plugin to crash.
                libdecor_frame_set_visibility(data->shell_surface.libdecor.frame, false);
            }

            যদি (c->zxdg_exporter_v2) {
                data->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, data->surface);
                zxdg_exported_v2_add_listener(data->exported, &exported_v2_listener, data);
            }

            যদি (c->xdg_toplevel_icon_manager_v1 && data->xdg_toplevel_icon_v1) {
                xdg_toplevel_icon_manager_v1_set_icon(_this->internal->xdg_toplevel_icon_manager_v1,
                                                      libdecor_frame_get_xdg_toplevel(data->shell_surface.libdecor.frame),
                                                      data->xdg_toplevel_icon_v1);
            }

            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, libdecor_frame_get_xdg_surface(data->shell_surface.libdecor.frame));
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_POINTER, libdecor_frame_get_xdg_toplevel(data->shell_surface.libdecor.frame));
        }
    } অন্যথা
#endif
    যদি (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        data->shell_surface.xdg.surface = xdg_wm_base_get_xdg_surface(c->shell.xdg, data->surface);
        xdg_surface_set_user_data(data->shell_surface.xdg.surface, data);
        xdg_surface_add_listener(data->shell_surface.xdg.surface, &_xdg_surface_listener, data);
        SDL_SetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, data->shell_surface.xdg.surface);

        যদি (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            SDL_Window *parent = window->parent;
            SDL_WindowData *parent_data = parent->internal;
            সংরচনা xdg_surface *parent_xdg_surface = রিক্ত;
            পূর্ণাঙ্ক position_x = 0, position_y = 0;

            // Configure the popup parameters
#ifdef HAVE_LIBDECOR_H
            যদি (parent_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
                parent_xdg_surface = libdecor_frame_get_xdg_surface(parent_data->shell_surface.libdecor.frame);
            } অন্যথা
#endif
            যদি (parent_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL ||
                    parent_data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
                parent_xdg_surface = parent_data->shell_surface.xdg.surface;
            }

            // Set up the positioner for the popup and configure the constraints
            data->shell_surface.xdg.popup.xdg_positioner = xdg_wm_base_create_positioner(c->shell.xdg);
            xdg_positioner_set_anchor(data->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_ANCHOR_শীর্ষ_বাম);
            SDL_Rect parent_geometry;
            GetWindowGeometry(parent->internal, &parent_geometry);
            xdg_positioner_set_anchor_rect(data->shell_surface.xdg.popup.xdg_positioner, 0, 0, parent_geometry.w, parent_geometry.h);

            ধ্রুব Uint32 constraint = window->constrain_popup ? (XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_X | XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_SLIDE_Y) : XDG_POSITIONER_CONSTRAINT_ADJUSTMENT_NONE;
            xdg_positioner_set_constraint_adjustment(data->shell_surface.xdg.popup.xdg_positioner, constraint);
            xdg_positioner_set_gravity(data->shell_surface.xdg.popup.xdg_positioner, XDG_POSITIONER_GRAVITY_BOTTOM_ডান);
            xdg_positioner_set_size(data->shell_surface.xdg.popup.xdg_positioner, data->current.logical_width, data->current.logical_height);

            // Set the popup initial position
            position_x = window->last_position_pending ? window->pending.x : window->x;
            position_y = window->last_position_pending ? window->pending.y : window->y;
            EnsurePopupPositionIsValid(window, &position_x, &position_y);
            যদি (data->scale_to_display) {
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

            যদি (window->flags & SDL_WINDOW_TOOLTIP) {
                সংরচনা wl_region *region;

                // Tooltips can't be interacted with, so turn off the input region to avoid blocking anything behind them
                region = wl_compositor_create_region(c->compositor);
                wl_region_add(region, 0, 0, 0, 0);
                wl_surface_set_প্রবেশ_region(data->surface, region);
                wl_region_destroy(region);
            } অন্যথা যদি ((window->flags & SDL_WINDOW_POPUP_MENU) && !(window->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
                Wayland_SetKeyboardFocus(window, true);
            }

            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POPUP_POINTER, data->shell_surface.xdg.popup.xdg_popup);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POSITIONER_POINTER, data->shell_surface.xdg.popup.xdg_positioner);
        } অন্যথা {
            data->shell_surface.xdg.toplevel.xdg_toplevel = xdg_surface_get_toplevel(data->shell_surface.xdg.surface);
            xdg_toplevel_set_app_id(data->shell_surface.xdg.toplevel.xdg_toplevel, data->app_id);
            xdg_toplevel_add_listener(data->shell_surface.xdg.toplevel.xdg_toplevel, &toplevel_listener_xdg, data);

            // Create the window decorations
            যদি (c->decoration_manager) {
                data->server_decoration = zxdg_decoration_manager_v1_get_toplevel_decoration(c->decoration_manager, data->shell_surface.xdg.toplevel.xdg_toplevel);
                zxdg_toplevel_decoration_v1_add_listener(data->server_decoration, &xdg_toplevel_decoration_listener, window);
                ধ্রুব গণনা zxdg_toplevel_decoration_v1_mode mode = !(window->flags & SDL_WINDOW_BORDERLESS) ? ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE;
                zxdg_toplevel_decoration_v1_set_mode(data->server_decoration, mode);
            }

            যদি (c->zxdg_exporter_v2) {
                data->exported = zxdg_exporter_v2_export_toplevel(c->zxdg_exporter_v2, data->surface);
                zxdg_exported_v2_add_listener(data->exported, &exported_v2_listener, data);
            }

            যদি (c->xdg_toplevel_icon_manager_v1 && data->xdg_toplevel_icon_v1) {
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

    যদি (window->flags & SDL_WINDOW_MODAL) {
        Wayland_SetWindowModal(_this, window, true);
    }

    Wayland_SetWindowTitle(_this, window);

    /* We have to wait until the surface gets a "configure" event, or use of
     * this surface will fail. This is a new rule for xdg_shell.
     */
#ifdef HAVE_LIBDECOR_H
    যদি (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        যদি (data->shell_surface.libdecor.frame) {
            যাবত্ (data->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
                যদি (libdecor_dispatch(c->shell.libdecor, -1) < 0) {
                    যদি (!Wayland_HandleDisplayDisconnected(_this)) {
                        প্রত্যাগম;
                    }
                }
                যদি (WAYLAND_wl_display_dispatch_pending(c->display) < 0) {
                    যদি (!Wayland_HandleDisplayDisconnected(_this)) {
                        প্রত্যাগম;
                    }
                }
            }
        }
    } অন্যথা
#endif
        যদি (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP || data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Unlike libdecor we need to call this explicitly to prevent a deadlock.
         * libdecor will call this as part of their configure event!
         * -flibit
         */
        wl_surface_commit(data->surface);
        যদি (data->shell_surface.xdg.surface) {
            যাবত্ (data->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE) {
                যদি (WAYLAND_wl_display_dispatch(c->display) < 0) {
                    যদি (!Wayland_HandleDisplayDisconnected(_this)) {
                        প্রত্যাগম;
                    }
                }
            }
        }
    } অন্যথা {
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
    যদি (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        // Libdecor plugins can enforce minimum window sizes, so adjust if the initial window size is too small.
        যদি (window->windowed.w < data->system_limits.min_width ||
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
    যদি (c->activation_manager && SDL_GetHintBoolean(SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN, true)) {
        /* if the process was passed an activation token, use it when showing
         * the initial window.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ধ্রুব বর্ণ *activation_token = SDL_getenv("XDG_ACTIVATION_TOKEN");
        যদি (activation_token) {
            xdg_activation_v1_activate(c->activation_manager,
                                       activation_token,
                                       data->surface);

            // Clear this variable, per the protocol's request
            SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
        } অন্যথা {
            // Try to generate an activation token for this window.
            Wayland_RaiseWindow(_this, window);
        }
    } অন্যথা {
        // Clear the ignored activation token, as it won't be used.
        SDL_unsetenv_unsafe("XDG_ACTIVATION_TOKEN");
    }

    // No frame callback on an external surface, as it may already have one attached.
    যদি (!(window->flags & SDL_WINDOW_EXTERNAL)) {
        // Fire a callback when the compositor wants a new frame.
        data->surface_frame_callback = wl_surface_frame(data->surface);
        wl_callback_add_listener(data->surface_frame_callback, &surface_frame_listener, data);
    }

    data->show_hide_sync_required = true;
    সংরচনা wl_callback *cb = wl_display_sync(_this->internal->display);
    wl_callback_add_listener(cb, &show_hide_sync_listener, (শূন্য *)((uintptr_t)window->id));

    data->showing_window = true;
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_SHOWN, 0, 0);
    data->showing_window = false;

    // Send an exposure event to signal that the client should draw.
    SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_EXPOSED, 0, 0);
}

স্থির শূন্য Wayland_ReleasePopup(SDL_VideoDevice *_this, SDL_Window *popup)
{
    SDL_WindowData *popupdata;

    // Basic sanity checks to weed out the weird popup closures
    যদি (!SDL_ObjectValid(popup, SDL_OBJECT_TYPE_WINDOW)) {
        প্রত্যাগম;
    }
    popupdata = popup->internal;
    যদি (!popupdata) {
        প্রত্যাগম;
    }

    // This may already be freed by a parent popup!
    যদি (popupdata->shell_surface.xdg.popup.xdg_popup == রিক্ত) {
        প্রত্যাগম;
    }

    যদি ((popup->flags & SDL_WINDOW_POPUP_MENU) && !(popup->flags & SDL_WINDOW_NOT_FOCUSABLE)) {
        SDL_Window *new_focus;
        ধ্রুব bool set_focus = SDL_ShouldRelinquishPopupFocus(popup, &new_focus);
        Wayland_SetKeyboardFocus(new_focus, set_focus);
    }

    xdg_popup_destroy(popupdata->shell_surface.xdg.popup.xdg_popup);
    xdg_positioner_destroy(popupdata->shell_surface.xdg.popup.xdg_positioner);
    popupdata->shell_surface.xdg.popup.xdg_popup = রিক্ত;
    popupdata->shell_surface.xdg.popup.xdg_positioner = রিক্ত;

    SDL_PropertiesID props = SDL_GetWindowProperties(popup);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POPUP_POINTER, রিক্ত);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_POSITIONER_POINTER, রিক্ত);
}

শূন্য Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *wind = window->internal;
    SDL_PropertiesID props = SDL_GetWindowProperties(window);

    // Custom surfaces have nothing to destroy and are always considered to be 'shown'; nothing to do here.
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        প্রত্যাগম;
    }

    /* The window was shown, but the sync point hasn't yet been reached.
     * Pump events to avoid a possible protocol violation.
     */
    যদি (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(data->display);
    }

    wind->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_HIDDEN;

    যদি (wind->surface_frame_callback) {
        wl_callback_destroy(wind->surface_frame_callback);
        wind->surface_frame_callback = রিক্ত;
    }

    যদি (wind->server_decoration) {
        zxdg_toplevel_decoration_v1_destroy(wind->server_decoration);
        wind->server_decoration = রিক্ত;
    }

    // Clean up the export handle.
    যদি (wind->exported) {
        zxdg_exported_v2_destroy(wind->exported);
        wind->exported = রিক্ত;

        SDL_SetStringProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_EXPORT_HANDLE_STRING, রিক্ত);
    }

    যদি (wind->xdg_dialog_v1) {
        xdg_dialog_v1_destroy(wind->xdg_dialog_v1);
        wind->xdg_dialog_v1 = রিক্ত;
    }

#ifdef HAVE_LIBDECOR_H
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        যদি (wind->shell_surface.libdecor.frame) {
            libdecor_frame_unref(wind->shell_surface.libdecor.frame);

            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, রিক্ত);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_POINTER, রিক্ত);
        }
    } অন্যথা
#endif
    {
        যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
            Wayland_ReleasePopup(_this, window);
        } অন্যথা যদি (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_destroy(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_TOPLEVEL_POINTER, রিক্ত);
        }

        যদি (wind->shell_surface.xdg.surface) {
            xdg_surface_destroy(wind->shell_surface.xdg.surface);
            SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_XDG_SURFACE_POINTER, রিক্ত);
        }
    }

    // Attach a null buffer to unmap the surface.
    যদি (wind->mask.surface) {
        wl_surface_attach(wind->mask.surface, রিক্ত, 0, 0);
        wl_surface_commit(wind->mask.surface);
    }
    wl_surface_attach(wind->surface, রিক্ত, 0, 0);
    wl_surface_commit(wind->surface);

    // Need to destroy the session object after unmapping the window, or the state may not be saved.
    Wayland_DestroyToplevelSession(wind);

    SDL_zero(wind->shell_surface);
    SDL_zero(wind->explicit_geometry);
    wind->show_hide_sync_required = true;
    সংরচনা wl_callback *cb = wl_display_sync(_this->internal->display);
    wl_callback_add_listener(cb, &show_hide_sync_listener, (শূন্য *)((uintptr_t)window->id));
}

স্থির শূন্য handle_xdg_activation_done(শূন্য *data,
                                       সংরচনা xdg_activation_token_v1 *xdg_activation_token_v1,
                                       ধ্রুব বর্ণ *token)
{
    SDL_WindowData *window = data;
    যদি (xdg_activation_token_v1 == window->activation_token) {
        xdg_activation_v1_activate(window->waylandData->activation_manager,
                                   token,
                                   window->surface);
        xdg_activation_token_v1_destroy(window->activation_token);
        window->activation_token = রিক্ত;
    }
}

স্থির ধ্রুব সংরচনা xdg_activation_token_v1_listener xdg_activation_listener = {
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
স্থির শূন্য Wayland_activate_window(SDL_VideoData *data, SDL_WindowData *target_wind, bool set_serial)
{
    SDL_WaylandSeat *seat = data->last_implicit_grab_seat;
    SDL_WindowData *focus = রিক্ত;

    যদি (seat) {
        focus = seat->keyboard.focus;
        যদি (!focus) {
            focus = seat->pointer.focus;
        }
    }

    সংরচনা wl_surface *requesting_surface = focus ? focus->surface : রিক্ত;

    যদি (data->activation_manager) {
        যদি (target_wind->activation_token) {
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
        যদি (requesting_surface) {
            // This specifies the surface from which the activation request is originating, not the activation target surface.
            xdg_activation_token_v1_set_surface(target_wind->activation_token, requesting_surface);
        }
        যদি (set_serial && seat && seat->wl_seat) {
            xdg_activation_token_v1_set_serial(target_wind->activation_token, seat->last_implicit_grab_serial, seat->wl_seat);
        }
        xdg_activation_token_v1_commit(target_wind->activation_token);
    }
}

শূন্য Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_WindowData *wind = window->internal;

    যদি (viddata->activation_manager) {
        /* Check for an activation token, in case the window is being
         * raised in response to a system notification.
         *
         * Note that we don't check for empty strings, as that is still
         * considered a valid activation token!
         */
        ধ্রুব বর্ণ *activation_token = SDL_GetNotificationActivationToken();
        যদি (activation_token) {
            xdg_activation_v1_activate(viddata->activation_manager,
                                       activation_token,
                                       wind->surface);
            প্রত্যাগম;
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
    প্রত্যাগম true;
}

SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window,
                                 SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen)
{
    SDL_WindowData *wind = window->internal;
    সংরচনা wl_output *output = display->internal->output;

    // Custom surfaces have no toplevel to make fullscreen.
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        প্রত্যাগম SDL_FULLSCREEN_FAILED;
    }

    // Drop fullscreen leave requests when showing the window.
    যদি (wind->showing_window && fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
        প্রত্যাগম SDL_FULLSCREEN_SUCCEEDED;
    }

    যদি (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->internal->display);
    }

    // Flushing old events pending a new one, ignore this request.
    যদি (wind->drop_fullscreen_requests) {
        প্রত্যাগম SDL_FULLSCREEN_SUCCEEDED;
    }

    wind->drop_fullscreen_requests = true;
    FlushPendingEvents(window);
    wind->drop_fullscreen_requests = false;

    // Nothing to do if the window is not fullscreen, and this isn't an explicit enter request.
    যদি (!wind->is_fullscreen) {
        যদি (fullscreen == SDL_FULLSCREEN_OP_UPDATE) {
            // Request was out of date; signal the video core not to update any state.
            প্রত্যাগম SDL_FULLSCREEN_PENDING;
        } অন্যথা যদি (fullscreen == SDL_FULLSCREEN_OP_LEAVE) {
            // Already not fullscreen; nothing to do.
            প্রত্যাগম SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    // Don't send redundant fullscreen set/unset events.
    যদি (!!fullscreen != wind->is_fullscreen) {
        wind->fullscreen_was_positioned = !!fullscreen;

        /* Only use the specified output if an exclusive mode is being used, or a position was explicitly requested
         * before entering fullscreen desktop. Otherwise, let the compositor handle placement, as it has more
         * information about where the window is and where it should go, particularly if fullscreen is being requested
         * before the window is mapped, or the window spans multiple outputs.
         */
        যদি (!window->fullscreen_exclusive) {
            যদি (window->undefined_x || window->undefined_y ||
                (wind->অঙ্ক_outputs && !window->last_position_pending)) {
                output = রিক্ত;
            }
        }

        // Commit to set any pending size or limit data.
        যদি (fullscreen && wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        SetFullscreen(window, output, !!fullscreen);
    } অন্যথা যদি (wind->is_fullscreen) {
        /*
         * If the window is already fullscreen, this is likely a request to switch between
         * fullscreen and fullscreen desktop, change outputs, or change the video mode.
         *
         * If the window is already positioned on the target output, just update the
         * window geometry.
         */
        যদি (wind->last_displayID != display->id) {
            wind->fullscreen_was_positioned = true;
            SetFullscreen(window, output, true);
        } অন্যথা {
            ConfigureWindowGeometry(window);
            CommitLibdecorFrame(window);

            প্রত্যাগম SDL_FULLSCREEN_SUCCEEDED;
        }
    }

    প্রত্যাগম SDL_FULLSCREEN_PENDING;
}

শূন্য Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    // Drop restore requests when showing the window.
    যদি (wind->showing_window) {
        প্রত্যাগম;
    }

    // Not currently fullscreen or maximized, and no state pending; nothing to do.
    যদি (!(window->flags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) &&
        !wind->pending_state_deadline_গুনতি) {
        প্রত্যাগম;
    }

#ifdef HAVE_LIBDECOR_H
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        যদি (!wind->shell_surface.libdecor.frame) {
            প্রত্যাগম; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_frame_unset_maximized(wind->shell_surface.libdecor.frame);
        AddPendingStateSync(wind);
    } অন্যথা
#endif
        // Note that xdg-shell does NOT provide a way to unset minimize!
        যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
            যদি (wind->shell_surface.xdg.toplevel.xdg_toplevel == রিক্ত) {
                প্রত্যাগম; // Can't do anything yet, wait for ShowWindow
            }
            xdg_toplevel_unset_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
            AddPendingStateSync(wind);
        }
}

শূন্য Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered)
{
    SDL_WindowData *wind = window->internal;
    ধ্রুব SDL_VideoData *viddata = (ধ্রুব SDL_VideoData *)_this->internal;

#ifdef HAVE_LIBDECOR_H
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        যদি (wind->shell_surface.libdecor.frame) {
            libdecor_frame_set_visibility(wind->shell_surface.libdecor.frame, bordered);
        }
    } অন্যথা
#endif
        যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        যদি ((viddata->decoration_manager) && (wind->server_decoration)) {
            ধ্রুব গণনা zxdg_toplevel_decoration_v1_mode mode = bordered ? ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE : ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE;
            zxdg_toplevel_decoration_v1_set_mode(wind->server_decoration, mode);
        }
    }
}

শূন্য Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable)
{
    SDL_WindowData *wind = window->internal;

    /* When changing the resize capability on libdecor windows, the limits must always
     * be reapplied, as when libdecor changes states, it overwrites the values internally.
     */
    SetMinMaxDimensions(window);
    CommitLibdecorFrame(window);

    যদি (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        wind->pending_state_commit = true;
    }
}

শূন্য Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    যদি (wind->show_hide_sync_required) {
        WAYLAND_wl_display_roundtrip(_this->internal->display);
    }

    // Not fullscreen, already maximized, and no state pending; nothing to do.
    যদি (!(window->flags & SDL_WINDOW_FULLSCREEN) && (window->flags & SDL_WINDOW_MAXIMIZED) &&
        !wind->pending_state_deadline_গুনতি) {
        প্রত্যাগম;
    }

#ifdef HAVE_LIBDECOR_H
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        যদি (!wind->shell_surface.libdecor.frame) {
            প্রত্যাগম; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        যদি (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        libdecor_frame_set_maximized(wind->shell_surface.libdecor.frame);
        AddPendingStateSync(wind);
    } অন্যথা
#endif
        যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        যদি (wind->shell_surface.xdg.toplevel.xdg_toplevel == রিক্ত) {
            প্রত্যাগম; // Can't do anything yet, wait for ShowWindow
        }

        // Commit to set any pending size or limit data.
        যদি (wind->pending_state_commit) {
            wl_surface_commit(wind->surface);
        }
        xdg_toplevel_set_maximized(wind->shell_surface.xdg.toplevel.xdg_toplevel);
        AddPendingStateSync(wind);
    }
}

শূন্য Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    যদি (!(wind->wm_caps & WAYLAND_WM_CAPS_MINIMIZE)) {
        প্রত্যাগম;
    }

#ifdef HAVE_LIBDECOR_H
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        যদি (!wind->shell_surface.libdecor.frame) {
            প্রত্যাগম; // Can't do anything yet, wait for ShowWindow
        }
        libdecor_frame_set_minimized(wind->shell_surface.libdecor.frame);
        SDL_SendWindowEvent(window, SDL_EVENT_WINDOW_MINIMIZED, 0, 0);
    } অন্যথা
#endif
        যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        যদি (wind->shell_surface.xdg.toplevel.xdg_toplevel == রিক্ত) {
            প্রত্যাগম; // Can't do anything yet, wait for ShowWindow
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
    যদি (!data->pointer_constraints) {
        প্রত্যাগম SDL_SetError("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_DisplayUpdatePointerGrabs(data, window->internal);
    প্রত্যাগম true;
}

bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_VideoData *data = _this->internal;
    যদি (!data->pointer_constraints) {
        প্রত্যাগম SDL_SetError("Failed to grab mouse: compositor lacks support for the required zwp_pointer_constraints_v1 protocol");
    }
    Wayland_DisplayUpdatePointerGrabs(data, window->internal);
    প্রত্যাগম true;
}

bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed)
{
    SDL_VideoData *data = _this->internal;
    যদি (!data->চাবি_inhibitor_manager) {
        প্রত্যাগম SDL_SetError("Failed to grab keyboard: compositor lacks support for the required zwp_keyboard_shortcuts_inhibit_manager_v1 protocol");
    }
    Wayland_DisplayUpdateKeyboardGrabs(data, window->internal);
    প্রত্যাগম true;
}

bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags)
{
    SDL_WindowData *data = window->internal;

    // Don't try to reconfigure mapped windows, unless they are custom or external.
    যদি (data->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN &&
        data->shell_surface_type != WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {
        // Window is already mapped; abort.
        প্রত্যাগম false;
    }

    /* The caller guarantees that only one of the GL or Vulkan flags will be set.
     * Note that Vulkan doesn't require any specific configuration, so only EGL
     * objects are added and removed as required.
     */
    যদি (flags & SDL_WINDOW_OPENGL) {
        যদি (!data->egl_window) {
            data->egl_window = WAYLAND_wl_egl_window_create(data->surface, data->current.pixel_width, data->current.pixel_height);
        }

#ifdef SDL_VIDEO_OPENGL_EGL
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)data->egl_window);

        যদি (data->egl_surface == EGL_NO_SURFACE) {
            প্রত্যাগম false; // SDL_EGL_CreateSurface should have set the error.
        }
#endif

        যদি (!data->gles_swap_frame_event_queue) {
            data->gles_swap_frame_event_queue = WAYLAND_wl_display_create_queue(data->waylandData->display);
            data->gles_swap_frame_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(data->surface);
            WAYLAND_wl_proxy_set_queue((সংরচনা wl_proxy *)data->gles_swap_frame_surface_wrapper, data->gles_swap_frame_event_queue);
            data->gles_swap_frame_callback = wl_surface_frame(data->gles_swap_frame_surface_wrapper);
            wl_callback_add_listener(data->gles_swap_frame_callback, &gles_swap_frame_listener, data);
        }
    } অন্যথা {
#ifdef SDL_VIDEO_OPENGL_EGL
        যদি (data->egl_surface) {
            SDL_EGL_DestroySurface(_this, data->egl_surface);
            data->egl_surface = EGL_NO_SURFACE;
        }
#endif

        যদি (data->egl_window) {
            WAYLAND_wl_egl_window_destroy(data->egl_window);
            data->egl_window = রিক্ত;
        }

        যদি (data->gles_swap_frame_callback) {
            wl_callback_destroy(data->gles_swap_frame_callback);
            data->gles_swap_frame_callback = রিক্ত;
        }

        যদি (data->gles_swap_frame_surface_wrapper) {
            WAYLAND_wl_proxy_wrapper_destroy(data->gles_swap_frame_surface_wrapper);
            data->gles_swap_frame_surface_wrapper = রিক্ত;
        }

        যদি (data->gles_swap_frame_event_queue) {
            WAYLAND_wl_event_queue_destroy(data->gles_swap_frame_event_queue);
            data->gles_swap_frame_event_queue = রিক্ত;
        }
    }

    প্রত্যাগম true;
}

bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props)
{
    SDL_WindowData *data;
    SDL_VideoData *c = _this->internal;
    সংরচনা wl_surface *external_surface = (সংরচনা wl_surface *)SDL_GetPointerProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_WL_SURFACE_POINTER,
                                                                               (সংরচনা wl_surface *)SDL_GetPointerProperty(create_props, "sdl2-compat.external_window", রিক্ত));
    ধ্রুব bool custom_surface_role = (external_surface != রিক্ত) || SDL_GetBooleanProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_SURFACE_ROLE_CUSTOM_BOOLEAN, false);
    ধ্রুব bool create_egl_window = !!(window->flags & SDL_WINDOW_OPENGL) ||
                                       SDL_GetBooleanProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_CREATE_EGL_WINDOW_BOOLEAN, false);

    data = SDL_calloc(1, পরিমাণ(*data));
    যদি (!data) {
        প্রত্যাগম false;
    }

    window->internal = data;
    data->enable_insets = SDL_GetBooleanProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_ENABLE_INSETS_BOOLEAN, false);

    যদি (window->x == SDL_WINDOWPOS_UNDEFINED) {
        window->x = 0;
    }
    যদি (window->y == SDL_WINDOWPOS_UNDEFINED) {
        window->y = 0;
    }

    data->waylandData = c;
    data->sdlwindow = window;

    // Default to all capabilities
    data->wm_caps = WAYLAND_WM_CAPS_ALL;

    data->scale_factor = 1.0;

    যদি (SDL_WINDOW_IS_POPUP(window)) {
        data->scale_to_display = window->parent->internal->scale_to_display;
        data->scale_factor = window->parent->internal->scale_factor;
        EnsurePopupPositionIsValid(window, &window->x, &window->y);
    } অন্যথা {
        প্রতি (পূর্ণাঙ্ক i = 0; i < _this->অঙ্ক_displays; i++) {
            data->scale_factor = SDL_max(data->scale_factor, _this->displays[i]->internal->scale_factor);
        }
    }

    data->outputs = রিক্ত;
    data->অঙ্ক_outputs = 0;
    data->scale_to_display = c->scale_to_display_enabled;

    // Cache the app_id at creation time, as it may change before the window is mapped.
    data->app_id = SDL_strdup(SDL_GetAppID());

    যদি (!data->scale_to_display) {
        data->requested.logical_width = window->floating.w;
        data->requested.logical_height = window->floating.h;
    } অন্যথা {
        data->requested.logical_width = PixelToPoint(window, window->floating.w);
        data->requested.logical_height = PixelToPoint(window, window->floating.h);
        data->requested.pixel_width = window->floating.w;
        data->requested.pixel_height = window->floating.h;
    }

    যদি (!external_surface) {
        data->surface = wl_compositor_create_surface(c->compositor);
        wl_surface_add_listener(data->surface, &surface_listener, data);
        wl_surface_set_user_data(data->surface, data);
        SDL_WAYLAND_register_surface(data->surface);
    } অন্যথা {
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
    যদি (!custom_surface_role || (window->flags & SDL_WINDOW_উপরের_PIXEL_DENSITY)) {
        যদি (c->viewporter) {
            data->viewport = wp_viewporter_get_viewport(c->viewporter, data->surface);

            // The viewport always uses the entire buffer.
            wp_viewport_set_source(data->viewport,
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1),
                                   wl_fixed_from_int(-1), wl_fixed_from_int(-1));
        }
        যদি (c->fractional_scale_manager) {
            data->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(c->fractional_scale_manager, data->surface);
            wp_fractional_scale_v1_add_listener(data->fractional_scale, &fractional_scale_listener, data);
        }
    }

    যদি (!custom_surface_role) {
        যদি (c->wp_color_manager_v1) {
            data->wp_color_management_surface_feedback = wp_color_manager_v1_get_surface_feedback(c->wp_color_manager_v1, data->surface);
            wp_color_management_surface_feedback_v1_add_listener(data->wp_color_management_surface_feedback, &color_management_surface_feedback_listener, data);
            Wayland_GetColorInfoForWindow(data, true);
        } অন্যথা যদি (c->frog_color_management_factory_v1) {
            data->frog_color_managed_surface = frog_color_management_factory_v1_get_color_managed_surface(c->frog_color_management_factory_v1, data->surface);
            frog_color_managed_surface_add_listener(data->frog_color_managed_surface, &frog_surface_listener, data);
        }

        যদি (c->wp_alpha_modifier_v1) {
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
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        data->gles_swap_frame_event_queue = WAYLAND_wl_display_create_queue(data->waylandData->display);
        data->gles_swap_frame_surface_wrapper = WAYLAND_wl_proxy_create_wrapper(data->surface);
        WAYLAND_wl_proxy_set_queue((সংরচনা wl_proxy *)data->gles_swap_frame_surface_wrapper, data->gles_swap_frame_event_queue);
        data->gles_swap_frame_callback = wl_surface_frame(data->gles_swap_frame_surface_wrapper);
        wl_callback_add_listener(data->gles_swap_frame_callback, &gles_swap_frame_listener, data);
    }

    যদি (window->flags & SDL_WINDOW_TRANSPARENT) {
        যদি (_this->gl_config.alpha_size == 0) {
            _this->gl_config.alpha_size = 8;
        }
    }

    যদি (create_egl_window) {
        data->egl_window = WAYLAND_wl_egl_window_create(data->surface, data->current.pixel_width, data->current.pixel_height);
    }

#ifdef SDL_VIDEO_OPENGL_EGL
    যদি (window->flags & SDL_WINDOW_OPENGL) {
        // Create the GLES window surface
        data->egl_surface = SDL_EGL_CreateSurface(_this, window, (NativeWindowType)data->egl_window);

        যদি (data->egl_surface == EGL_NO_SURFACE) {
            প্রত্যাগম false; // SDL_EGL_CreateSurface should have set error
        }
    }
#endif

    // We may need to create an idle inhibitor for this new window
    Wayland_SuspendScreenSaver(_this);

    যদি (!custom_surface_role) {
#ifdef HAVE_LIBDECOR_H
        যদি (c->shell.libdecor && !SDL_WINDOW_IS_POPUP(window)) {
            data->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR;
        } অন্যথা
#endif
            যদি (c->shell.xdg) {
            যদি (SDL_WINDOW_IS_POPUP(window)) {
                data->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP;
            } অন্যথা {
                data->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL;
            }
        } // All other cases will be WAYLAND_SURFACE_UNKNOWN
    } অন্যথা {
        // Roleless and external surfaces are always considered to be in the shown state by the backend.
        data->shell_surface_type = WAYLAND_SHELL_SURFACE_TYPE_CUSTOM;
        data->shell_surface_status = WAYLAND_SHELL_SURFACE_STATUS_SHOWN;

        // External windows are presumed to be shown.
        যদি (window->flags & SDL_WINDOW_EXTERNAL) {
            window->flags &= ~SDL_WINDOW_HIDDEN;
        }
    }

    যদি (SDL_GetHintBoolean(SDL_HINT_VIDEO_DOUBLE_BUFFER, false)) {
        data->double_buffer = true;
    }

    SDL_PropertiesID props = SDL_GetWindowProperties(window);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, data->waylandData->display);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, data->surface);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_VIEWPORT_POINTER, data->viewport);
    SDL_SetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_EGL_WINDOW_POINTER, data->egl_window);
    যদি (data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL || data->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        ধ্রুব বর্ণ *window_id = SDL_GetStringProperty(create_props, SDL_PROP_WINDOW_CREATE_WAYLAND_WINDOW_ID_STRING, রিক্ত);
        যদি (window_id && *window_id != '\0') {
            SDL_SetStringProperty(props, SDL_PROP_WINDOW_WAYLAND_WINDOW_ID_STRING, window_id);
        }
    }

    data->hit_test_result = SDL_HITTEST_NORMAL;

    প্রত্যাগম true;
}

শূন্য Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    window->internal->limits_changed = true;
}

শূন্য Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    window->internal->limits_changed = true;
}

শূন্য Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window)
{
    // Will be committed when Wayland_SetWindowSize() is called by the video core.
    window->internal->limits_changed = true;
}

bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    // Only popup windows can be positioned relative to the parent.
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP) {
        যদি (wind->shell_surface.xdg.popup.xdg_popup &&
            xdg_popup_get_version(wind->shell_surface.xdg.popup.xdg_popup) < XDG_POPUP_REPOSITION_SINCE_VERSION) {
            প্রত্যাগম SDL_Unsupported();
        }

        RepositionPopup(window, false);
        প্রত্যাগম true;
    } অন্যথা যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR || wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        /* Catch up on any pending state before attempting to change the fullscreen window
         * display via a set fullscreen call to make sure the window doesn't have a pending
         * leave fullscreen event that it might override.
         */
        FlushPendingEvents(window);

        যদি (wind->is_fullscreen) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplayForFullscreenWindow(window);
            যদি (display && wind->last_displayID != display->id) {
                সংরচনা wl_output *output = display->internal->output;
                SetFullscreen(window, output, true);

                প্রত্যাগম true;
            }
        }
    }
    প্রত্যাগম SDL_SetError("wayland cannot position non-popup windows");
}

শূন্য Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window)
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

    ধ্রুব bool maximized = (window->flags & SDL_WINDOW_MAXIMIZED) != 0;
    ধ্রুব bool resizable_state = !(window->flags & (SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN));

    /* Maximized and fullscreen windows don't get resized, and the new size is ignored
     * if this is just to recalculate the min/max or aspect limits on a tiled window.
     *
     * Some compositors will mark tiled windows as maximized. In these cases, the content
     * size is recalculated, but window size itself is left alone, as the spec states that
     * the configure size of a maximized window must be obeyed.
     */
    যদি (resizable_state || (window->tiled && !wind->limits_changed) ||
        wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_CUSTOM) {

        // Don't change the window size if maximized and tiled.
        যদি (!maximized) {
            যদি (!wind->scale_to_display) {
                wind->requested.logical_width = window->pending.w;
                wind->requested.logical_height = window->pending.h;
            } অন্যথা {
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
        যদি (window->tiled && !(window->flags & SDL_WINDOW_RESIZABLE)) {
            window->floating.w = window->pending.w;
            window->floating.h = window->pending.h;
        }
    } অন্যথা {
        // Can't resize the window.
        window->last_size_pending = false;
    }

    wind->limits_changed = false;
    যদি (wind->shell_surface_status == WAYLAND_SHELL_SURFACE_STATUS_SHOWN) {
        wind->pending_state_commit = true;
    }

    // Always recalculate the geometry, as this may be in response to a min/max limit change.
    ConfigureWindowGeometry(window);
    CommitLibdecorFrame(window);
}

শূন্য Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক *w, পূর্ণাঙ্ক *h)
{
    SDL_WindowData *data = window->internal;

    *w = data->current.pixel_width;
    *h = data->current.pixel_height;
}

ভিন্ন Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    যদি (window->flags & SDL_WINDOW_উপরের_PIXEL_DENSITY || wind->scale_to_display || wind->fullscreen_exclusive) {
        প্রত্যাগম (ভিন্ন)wind->scale_factor;
    }

    প্রত্যাগম 1.0f;
}

SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    যদি (wind) {
        প্রত্যাগম wind->last_displayID;
    }

    প্রত্যাগম 0;
}

bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ভিন্ন opacity)
{
    SDL_WindowData *wind = window->internal;

    যদি (wind->wp_alpha_modifier_surface_v1) {
        ধ্রুব bool is_opaque = !(window->flags & SDL_WINDOW_TRANSPARENT) && opacity == 1.0f;

        যদি (wind->mask.mapped && wind->mask.opaque != is_opaque) {
            সংরচনা wl_buffer *old_buffer = wind->mask.buffer;
            wind->mask.opaque = is_opaque;
            wind->mask.buffer = Wayland_CreateSinglePixelBuffer(0, 0, 0, is_opaque ? SDL_MAX_UINT32 : 0);

            wl_surface_attach(wind->mask.surface, wind->mask.buffer, 0, 0);
            যদি (wl_surface_get_version(wind->mask.surface) >= WL_SURFACE_DAMAGE_BUFFER_SINCE_VERSION) {
                wl_surface_damage_buffer(wind->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            } অন্যথা {
                wl_surface_damage(wind->mask.surface, 0, 0, SDL_MAX_SINT32, SDL_MAX_SINT32);
            }

            যদি (is_opaque) {
                SetSurfaceOpaqueRegion(wind->mask.surface, wind->current.logical_width, wind->current.logical_height);
            } অন্যথা {
                SetSurfaceOpaqueRegion(wind->mask.surface, 0, 0);
            }

            wl_surface_commit(wind->mask.surface);

            যদি (old_buffer) {
                wl_buffer_destroy(old_buffer);
            }
        }

        যদি (is_opaque) {
            SetSurfaceOpaqueRegion(wind->surface, wind->current.viewport_width, wind->current.viewport_height);
        } অন্যথা {
            SetSurfaceOpaqueRegion(wind->surface, 0, 0);
        }

        wp_alpha_modifier_surface_v1_set_multiplier(wind->wp_alpha_modifier_surface_v1, (Uint32)((দ্বিগুণ)SDL_MAX_UINT32 * (দ্বিগুণ)opacity));

        প্রত্যাগম true;
    }

    প্রত্যাগম SDL_SetError("wayland: set window opacity failed; compositor lacks support for the required wp_alpha_modifier_v1 protocol");
}

শূন্য Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;
    ধ্রুব বর্ণ *title = window->title ? window->title : "";

#ifdef HAVE_LIBDECOR_H
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        libdecor_frame_set_title(wind->shell_surface.libdecor.frame, title);
    } অন্যথা
#endif
        যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        xdg_toplevel_set_title(wind->shell_surface.xdg.toplevel.xdg_toplevel, title);
    }
}

স্থির পূর্ণাঙ্ক icon_sort_callback(ধ্রুব শূন্য *a, ধ্রুব শূন্য *b)
{
    ধ্রুব SDL_Surface *s1 = *(ধ্রুব SDL_Surface **)a;
    ধ্রুব SDL_Surface *s2 = *(ধ্রুব SDL_Surface **)b;

    প্রত্যাগম (s1->w * s1->h) <= (s2->w * s2->h) ? -1 : 1;
}

bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon)
{
    SDL_WindowData *wind = window->internal;
    Wayland_SHMPool *shm_pool = রিক্ত;
    সংরচনা xdg_toplevel *toplevel = রিক্ত;

    যদি (!_this->internal->xdg_toplevel_icon_manager_v1) {
        প্রত্যাগম SDL_SetError("wayland: cannot set icon; required xdg_toplevel_icon_v1 protocol not supported");
    }

    পূর্ণাঙ্ক image_গুনতি_2 = 0;
    SDL_Surface **images = SDL_GetSurfaceImages(icon, &image_গুনতি_2);
    যদি (!images || !image_গুনতি_2) {
        প্রত্যাগম false;
    }

    // Release the old icon resources.
    যদি (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = রিক্ত;
    }

    প্রতি (পূর্ণাঙ্ক i = 0; i < wind->icon_buffer_গুনতি; ++i) {
        wl_buffer_destroy(wind->icon_buffers[i]);
    }
    wind->icon_buffer_গুনতি = 0;

    wind->xdg_toplevel_icon_v1 = xdg_toplevel_icon_manager_v1_create_icon(_this->internal->xdg_toplevel_icon_manager_v1);
    wind->icon_buffers = SDL_realloc(wind->icon_buffers, image_গুনতি_2 * পরিমাণ(সংরচনা wl_buffer *));
    যদি (!wind->icon_buffers) {
        গচ্ছ failure_cleanup;
    }

    // Calculate the size of the buffer pool.
    size_t pool_size = 0;
    প্রতি (পূর্ণাঙ্ক i = 0; i < image_গুনতি_2; ++i) {
        // Images must be square. Non-square images will be centered.
        ধ্রুব পূর্ণাঙ্ক size = SDL_max(images[i]->w, images[i]->h);
        pool_size += size * size * 4;
    }

    // Sort the images in ascending order by size.
    SDL_qsort(images, image_গুনতি_2, পরিমাণ(SDL_Surface *), icon_sort_callback);

    shm_pool = Wayland_AllocSHMPool(pool_size);
    যদি (!shm_pool) {
        SDL_SetError("wayland: failed to allocate an SHM pool for the icon");
        গচ্ছ failure_cleanup;
    }

    ধ্রুব দ্বিগুণ base_size = (দ্বিগুণ)SDL_max(icon->w, icon->h);
    প্রতি (পূর্ণাঙ্ক i = 0; i < image_গুনতি_2; ++i) {
        SDL_Surface *surface = images[i];

        // Choose the largest image for each integer scale, ignoring any below the base size.
        ধ্রুব পূর্ণাঙ্ক level_size = SDL_max(surface->w, surface->h);
        ধ্রুব পূর্ণাঙ্ক scale = (পূর্ণাঙ্ক)SDL_floor((দ্বিগুণ)level_size / base_size);
        যদি (!scale) {
            অনুবর্ত;
        }

        যদি (surface->format != SDL_PIXELFORMAT_ARGB8888) {
            surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
            যদি (!surface) {
                SDL_SetError("wayland: failed to convert the icon image to ARGB8888 format");
                গচ্ছ failure_cleanup;
            }
        }

        শূন্য *buffer_mem;
        সংরচনা wl_buffer *buffer = Wayland_AllocBufferFromPool(shm_pool, level_size, level_size, &buffer_mem);
        যদি (!buffer) {
            // Clean up the temporary conversion surface.
            যদি (surface != images[i]) {
                SDL_DestroySurface(surface);
            }
            SDL_SetError("wayland: failed to allocate a wl_buffer for the icon");
            গচ্ছ failure_cleanup;
        }

        wind->icon_buffers[wind->icon_buffer_গুনতি++] = buffer;

        // Center non-square images.
        যদি (surface->w < level_size) {
            SDL_memset(buffer_mem, 0, level_size * level_size * 4);
            buffer_mem = (Uint8 *)buffer_mem + (((level_size - surface->w) / 2) * 4);
        } অন্যথা যদি (surface->h < level_size) {
            SDL_memset(buffer_mem, 0, level_size * level_size * 4);
            buffer_mem = (Uint8 *)buffer_mem + (((level_size - surface->h) / 2) * (level_size * 4));
        }

        SDL_PremultiplyAlpha(surface->w, surface->h, surface->format, surface->pixels, surface->pitch,
                             SDL_PIXELFORMAT_ARGB8888, buffer_mem, level_size * 4, true);

        xdg_toplevel_icon_v1_add_buffer(wind->xdg_toplevel_icon_v1, buffer, scale);

        // Clean up the temporary scaled or conversion surface.
        যদি (surface != images[i]) {
            SDL_DestroySurface(surface);
        }
    }

#ifdef HAVE_LIBDECOR_H
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR && wind->shell_surface.libdecor.frame) {
        toplevel = libdecor_frame_get_xdg_toplevel(wind->shell_surface.libdecor.frame);
    } অন্যথা
#endif
        যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL && wind->shell_surface.xdg.toplevel.xdg_toplevel) {
        toplevel = wind->shell_surface.xdg.toplevel.xdg_toplevel;
    }

    যদি (toplevel) {
        xdg_toplevel_icon_manager_v1_set_icon(_this->internal->xdg_toplevel_icon_manager_v1, toplevel, wind->xdg_toplevel_icon_v1);
    }

    Wayland_ReleaseSHMPool(shm_pool);
    SDL_free(images);

    প্রত্যাগম true;

failure_cleanup:

    SDL_free(images);

    যদি (wind->xdg_toplevel_icon_v1) {
        xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        wind->xdg_toplevel_icon_v1 = রিক্ত;
    }

    Wayland_ReleaseSHMPool(shm_pool);

    প্রতি (পূর্ণাঙ্ক i = 0; i < wind->icon_buffer_গুনতি; ++i) {
        wl_buffer_destroy(wind->icon_buffers[i]);
    }
    SDL_free(wind->icon_buffers);
    wind->icon_buffers = রিক্ত;
    wind->icon_buffer_গুনতি = 0;

    প্রত্যাগম false;
}

শূন্য *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size)
{
    SDL_WindowData *wind = window->internal;
    শূন্য *ret = রিক্ত;

    যদি (wind->icc_size > 0) {
        শূন্য *icc_map = mmap(রিক্ত, wind->icc_size, PROT_READ, MAP_PRIVATE, wind->icc_fd, 0);
        যদি (icc_map != MAP_FAILED) {
            ret = SDL_malloc(wind->icc_size);
            যদি (ret) {
                *size = wind->icc_size;
                SDL_memcpy(ret, icc_map, *size);
            }
            munmap(icc_map, wind->icc_size);
        }
    }

    প্রত্যাগম ret;
}

bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *wind = window->internal;

    কুরু {
        WAYLAND_wl_display_roundtrip(_this->internal->display);
    } যাবত্ (wind->pending_state_deadline_গুনতি);

    প্রত্যাগম true;
}

শূন্য Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept)
{
    window->internal->accepts_drag_and_drop = accept;
}

bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable)
{
    যদি (window->flags & SDL_WINDOW_POPUP_MENU) {
        যদি (!(window->flags & SDL_WINDOW_HIDDEN)) {
            যদি (!focusable && (window->flags & SDL_WINDOW_প্রবেশ_FOCUS)) {
                SDL_Window *new_focus;
                ধ্রুব bool set_focus = SDL_ShouldRelinquishPopupFocus(window, &new_focus);
                Wayland_SetKeyboardFocus(new_focus, set_focus);
            } অন্যথা যদি (focusable) {
                যদি (SDL_ShouldFocusPopup(window)) {
                    Wayland_SetKeyboardFocus(window, true);
                }
            }
        }

        প্রত্যাগম true;
    }

    প্রত্যাগম SDL_SetError("wayland: focus can only be toggled on popup menu windows");
}

শূন্য Wayland_ShowWindowSystemMenu(SDL_Window *window, পূর্ণাঙ্ক x, পূর্ণাঙ্ক y)
{
    SDL_WindowData *wind = window->internal;
    SDL_WaylandSeat *seat = wind->waylandData->last_implicit_grab_seat;

    যদি (!seat) {
        প্রত্যাগম;
    }

    যদি (wind->scale_to_display) {
        x = PixelToPoint(window, x);
        y = PixelToPoint(window, y);
    }

#ifdef HAVE_LIBDECOR_H
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR) {
        যদি (wind->shell_surface.libdecor.frame) {
            libdecor_frame_show_window_menu(wind->shell_surface.libdecor.frame, seat->wl_seat, seat->last_implicit_grab_serial, x, y);
        }
    } অন্যথা
#endif
    যদি (wind->shell_surface_type == WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL) {
        যদি (wind->shell_surface.xdg.toplevel.xdg_toplevel) {
            xdg_toplevel_show_window_menu(wind->shell_surface.xdg.toplevel.xdg_toplevel, seat->wl_seat, seat->last_implicit_grab_serial, x, y);
        }
    }
}

bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;

#ifdef SDL_USE_LIBDBUS
    যদি (SDL_DBus_ScreensaverInhibit(_this->suspend_screensaver)) {
        প্রত্যাগম true;
    }
#endif

    /* The idle_inhibit_unstable_v1 protocol suspends the screensaver
       on a per wl_surface basis, but SDL assumes that suspending
       the screensaver can be done independently of any window.

       To reconcile these differences, we propagate the idle inhibit
       state to each window. If there is no window active, we will
       be able to inhibit idle once the first window is created.
    */
    যদি (data->idle_inhibit_manager) {
        SDL_Window *window = _this->windows;
        যাবত্ (window) {
            SDL_WindowData *win_data = window->internal;

            যদি (_this->suspend_screensaver && !win_data->idle_inhibitor) {
                win_data->idle_inhibitor =
                    zwp_idle_inhibit_manager_v1_create_inhibitor(data->idle_inhibit_manager,
                                                                 win_data->surface);
            } অন্যথা যদি (!_this->suspend_screensaver && win_data->idle_inhibitor) {
                zwp_idle_inhibitor_v1_destroy(win_data->idle_inhibitor);
                win_data->idle_inhibitor = রিক্ত;
            }

            window = window->next;
        }
    }

    প্রত্যাগম true;
}

শূন্য Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_VideoData *data = _this->internal;
    SDL_WindowData *wind = window->internal;

    যদি (data && wind) {
        /* Roundtrip before destroying the window to make sure that it has received input leave events, so that
         * no internal structures are left pointing to the destroyed window.
         */
        যদি (wind->show_hide_sync_required) {
            /* Make sure hit test isn't executed during roundtrip */
            window->hit_test = রিক্ত;
            WAYLAND_wl_display_roundtrip(data->display);
        }

        /* The compositor should have relinquished keyboard, pointer, touch, and tablet tool focus when the toplevel
         * window was destroyed upon being hidden, but there is no guarantee of this, so ensure that all references
         * to the window held by seats are released before destroying the underlying surface and struct.
         */
        Wayland_DisplayRemoveWindowReferencesFromSeats(data, wind);

        যদি (wind->mask.viewport) {
            wp_viewport_destroy(wind->mask.viewport);
        }
        যদি (wind->mask.buffer) {
            wl_buffer_destroy(wind->mask.buffer);
        }
        যদি (wind->mask.subsurface) {
            wl_subsurface_destroy(wind->mask.subsurface);
        }
        যদি (wind->mask.surface) {
            wl_surface_destroy(wind->mask.surface);
        }
#ifdef SDL_VIDEO_OPENGL_EGL
        যদি (wind->egl_surface) {
            SDL_EGL_DestroySurface(_this, wind->egl_surface);
        }
#endif
        যদি (wind->egl_window) {
            WAYLAND_wl_egl_window_destroy(wind->egl_window);
        }

        যদি (wind->idle_inhibitor) {
            zwp_idle_inhibitor_v1_destroy(wind->idle_inhibitor);
        }

        যদি (wind->activation_token) {
            xdg_activation_token_v1_destroy(wind->activation_token);
        }

        যদি (wind->viewport) {
            wp_viewport_destroy(wind->viewport);
        }

        যদি (wind->fractional_scale) {
            wp_fractional_scale_v1_destroy(wind->fractional_scale);
        }

        যদি (wind->wp_alpha_modifier_surface_v1) {
            wp_alpha_modifier_surface_v1_destroy(wind->wp_alpha_modifier_surface_v1);
        }

        যদি (wind->frog_color_managed_surface) {
            frog_color_managed_surface_destroy(wind->frog_color_managed_surface);
        }

        যদি (wind->wp_color_management_surface_feedback) {
            Wayland_FreeColorInfoState(wind->color_info_state);
            wp_color_management_surface_feedback_v1_destroy(wind->wp_color_management_surface_feedback);
        }

        SDL_free(wind->outputs);
        SDL_free(wind->app_id);

        যদি (wind->gles_swap_frame_callback) {
            wl_callback_destroy(wind->gles_swap_frame_callback);
            WAYLAND_wl_proxy_wrapper_destroy(wind->gles_swap_frame_surface_wrapper);
            WAYLAND_wl_event_queue_destroy(wind->gles_swap_frame_event_queue);
        }

        যদি (!(window->flags & SDL_WINDOW_EXTERNAL)) {
            wl_surface_destroy(wind->surface);
        } অন্যথা {
            Wayland_RemoveWindowDataFromExternalList(wind);
        }

        যদি (wind->xdg_toplevel_icon_v1) {
            xdg_toplevel_icon_v1_destroy(wind->xdg_toplevel_icon_v1);
        }

        প্রতি (পূর্ণাঙ্ক i = 0; i < wind->icon_buffer_গুনতি; ++i) {
            wl_buffer_destroy(wind->icon_buffers[i]);
        }
        SDL_free(wind->icon_buffers);
        wind->icon_buffer_গুনতি = 0;

        SDL_free(wind);
    }
    window->internal = রিক্ত;
}

#endif // SDL_VIDEO_DRIVER_WAYLAND
