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

#شامل "SDL_internal.h"

#ifndef SDL_waylandvideo_h_
#define SDL_waylandvideo_h_

#شامل <EGL/egl.h>
#شامل "wayland-util.h"

#شامل "../SDL_sysvideo.h"
#شامل "../../core/linux/SDL_dbus.h"
#شامل "../../core/linux/SDL_ime.h"
#شامل "SDL_waylandeventthread.h"

ساختار xkb_context;
ساختار SDL_WaylandSeat;

تعریفنوع ساختار
{
    ساختار wl_cursor_theme *theme;
    صحیح size;
} SDL_WaylandCursorTheme;

تعریفنوع ساختار
{
    ساختار wl_list link;
    نویسه wl_output_name[];
} SDL_WaylandConnectorName;

ساختار SDL_VideoData
{
    ساختار wl_display *display;
    ساختار wl_registry *registry;
    ساختار wl_compositor *compositor;
    ساختار wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    صحیح رقم_cursor_themes;
    ساختار
    {
        ساختار xdg_wm_base *xdg;
#ifdef HAVE_LIBDECOR_H
        ساختار libdecor *libdecor;
#endif
    } shell;
    ساختار wl_subcompositor *subcompositor;
    ساختار zwp_relative_pointer_manager_v1 *relative_pointer_manager;
    ساختار zwp_pointer_constraints_v1 *pointer_constraints;
    ساختار wp_pointer_warp_v1 *wp_pointer_warp_v1;
    ساختار wp_cursor_shape_manager_v1 *cursor_shape_manager;
    ساختار wl_data_device_manager *data_device_manager;
    ساختار zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    ساختار zxdg_decoration_manager_v1 *decoration_manager;
    ساختار zwp_keyboard_shortcuts_inhibit_manager_v1 *کلید_inhibitor_manager;
    ساختار zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    ساختار xdg_activation_v1 *activation_manager;
    ساختار zwp_text_درون_داد_manager_v3 *text_درون_داد_manager;
    ساختار zxdg_output_manager_v1 *xdg_output_manager;
    ساختار wp_viewporter *viewporter;
    ساختار wp_fractional_scale_manager_v1 *fractional_scale_manager;
    ساختار zwp_درون_داد_timestamps_manager_v1 *درون_داد_timestamps_manager;
    ساختار zxdg_exporter_v2 *zxdg_exporter_v2;
    ساختار xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    ساختار wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    ساختار xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    ساختار frog_color_management_factory_v1 *frog_color_management_factory_v1;
    ساختار wp_color_manager_v1 *wp_color_manager_v1;
    ساختار zwp_tablet_manager_v2 *tablet_manager;
    ساختار wl_fixes *wl_fixes;
    ساختار zwp_pointer_gestures_v1 *zwp_pointer_gestures;
    ساختار wp_single_pixel_buffer_manager_v1 *single_pixel_buffer_manager;
    ساختار xdg_session_manager_v1 *xdg_session_manager;
    ساختار xdg_toplevel_tag_manager_v1 *xdg_toplevel_tag_manager;

    ساختار xdg_session_v1 *xdg_session;
    ساختار xkb_context *xkb_context;

    ساختار wl_list seat_list;
    ساختار SDL_WaylandSeat *last_implicit_grab_seat;
    ساختار SDL_WaylandSeat *current_data_offer_seat;
    ساختار SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_JobThreadContext *job_thread_context;

    SDL_DisplayData **output_list;
    صحیح output_شمار;
    صحیح output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_to_display_enabled;
};

ساختار SDL_DisplayData
{
    SDL_VideoData *videodata;
    ساختار wl_output *output;
    ساختار zxdg_output_v1 *xdg_output;
    ساختار wp_color_management_output_v1 *wp_color_management_output;
    ساختار Wayland_ColorInfoState *color_info_state;
    نویسه *wl_output_name;
    دوگانه scale_factor;
    صحیح integer_scale_factor; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    ساختار
    {
        صحیح x;
        صحیح y;
        صحیح width;
        صحیح height;
    } logical;

    ساختار
    {
        صحیح x;
        صحیح y;
        صحیح width;
        صحیح height;
    } pixel;

    ساختار
    {
        صحیح width_mm;  // Physical width in millimeters.
        صحیح height_mm; // Physical height in millimeters.
    } physical;

    صحیح refresh;   // Refresh in mHz
    صحیح transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    صحیح wl_output_done_شمار;
    bool has_logical_position;
    bool has_logical_size;
    bool geometry_changed;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#شامل "SDL_waylanddyn.h"

بیرونی تهی SDL_WAYLAND_register_surface(ساختار wl_surface *surface);
بیرونی تهی SDL_WAYLAND_register_output(ساختار wl_output *output);
بیرونی bool SDL_WAYLAND_own_surface(ساختار wl_surface *surface);
بیرونی bool SDL_WAYLAND_own_output(ساختار wl_output *output);

بیرونی SDL_WindowData *Wayland_GetWindowDataForOwnedSurface(ساختار wl_surface *surface);
بیرونی تهی Wayland_AddWindowDataToExternalList(SDL_WindowData *data);
بیرونی تهی Wayland_RemoveWindowDataFromExternalList(SDL_WindowData *data);
بیرونی ساختار wl_event_queue *Wayland_DisplayCreateQueue(ساختار wl_display *display, ثابت نویسه *name);
بیرونی تهی Wayland_CreateSession(SDL_VideoData *data);

بیرونی bool Wayland_LoadLibdecor(SDL_VideoData *data, bool ignore_xdg);

بیرونی bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#endif // SDL_waylandvideo_h_
