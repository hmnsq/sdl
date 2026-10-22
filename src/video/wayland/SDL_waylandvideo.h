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

#ifndef SDL_waylandvideo_h_
#define SDL_waylandvideo_h_

#অন্তর্ভাব <EGL/egl.h>
#অন্তর্ভাব "wayland-util.h"

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../../core/linux/SDL_dbus.h"
#অন্তর্ভাব "../../core/linux/SDL_ime.h"
#অন্তর্ভাব "SDL_waylandeventthread.h"

সংরচনা xkb_context;
সংরচনা SDL_WaylandSeat;

প্রকারনির্দেশ সংরচনা
{
    সংরচনা wl_cursor_theme *theme;
    পূর্ণাঙ্ক size;
} SDL_WaylandCursorTheme;

প্রকারনির্দেশ সংরচনা
{
    সংরচনা wl_list link;
    বর্ণ wl_output_name[];
} SDL_WaylandConnectorName;

সংরচনা SDL_VideoData
{
    সংরচনা wl_display *display;
    সংরচনা wl_registry *registry;
    সংরচনা wl_compositor *compositor;
    সংরচনা wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    পূর্ণাঙ্ক অঙ্ক_cursor_themes;
    সংরচনা
    {
        সংরচনা xdg_wm_base *xdg;
#ifdef HAVE_LIBDECOR_H
        সংরচনা libdecor *libdecor;
#endif
    } shell;
    সংরচনা wl_subcompositor *subcompositor;
    সংরচনা zwp_relative_pointer_manager_v1 *relative_pointer_manager;
    সংরচনা zwp_pointer_constraints_v1 *pointer_constraints;
    সংরচনা wp_pointer_warp_v1 *wp_pointer_warp_v1;
    সংরচনা wp_cursor_shape_manager_v1 *cursor_shape_manager;
    সংরচনা wl_data_device_manager *data_device_manager;
    সংরচনা zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    সংরচনা zxdg_decoration_manager_v1 *decoration_manager;
    সংরচনা zwp_keyboard_shortcuts_inhibit_manager_v1 *চাবি_inhibitor_manager;
    সংরচনা zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    সংরচনা xdg_activation_v1 *activation_manager;
    সংরচনা zwp_text_প্রবেশ_manager_v3 *text_প্রবেশ_manager;
    সংরচনা zxdg_output_manager_v1 *xdg_output_manager;
    সংরচনা wp_viewporter *viewporter;
    সংরচনা wp_fractional_scale_manager_v1 *fractional_scale_manager;
    সংরচনা zwp_প্রবেশ_timestamps_manager_v1 *প্রবেশ_timestamps_manager;
    সংরচনা zxdg_exporter_v2 *zxdg_exporter_v2;
    সংরচনা xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    সংরচনা wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    সংরচনা xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    সংরচনা frog_color_management_factory_v1 *frog_color_management_factory_v1;
    সংরচনা wp_color_manager_v1 *wp_color_manager_v1;
    সংরচনা zwp_tablet_manager_v2 *tablet_manager;
    সংরচনা wl_fixes *wl_fixes;
    সংরচনা zwp_pointer_gestures_v1 *zwp_pointer_gestures;
    সংরচনা wp_single_pixel_buffer_manager_v1 *single_pixel_buffer_manager;
    সংরচনা xdg_session_manager_v1 *xdg_session_manager;
    সংরচনা xdg_toplevel_tag_manager_v1 *xdg_toplevel_tag_manager;

    সংরচনা xdg_session_v1 *xdg_session;
    সংরচনা xkb_context *xkb_context;

    সংরচনা wl_list seat_list;
    সংরচনা SDL_WaylandSeat *last_implicit_grab_seat;
    সংরচনা SDL_WaylandSeat *current_data_offer_seat;
    সংরচনা SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_JobThreadContext *job_thread_context;

    SDL_DisplayData **output_list;
    পূর্ণাঙ্ক output_গুনতি;
    পূর্ণাঙ্ক output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_to_display_enabled;
};

সংরচনা SDL_DisplayData
{
    SDL_VideoData *videodata;
    সংরচনা wl_output *output;
    সংরচনা zxdg_output_v1 *xdg_output;
    সংরচনা wp_color_management_output_v1 *wp_color_management_output;
    সংরচনা Wayland_ColorInfoState *color_info_state;
    বর্ণ *wl_output_name;
    দ্বিগুণ scale_factor;
    পূর্ণাঙ্ক integer_scale_factor; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    সংরচনা
    {
        পূর্ণাঙ্ক x;
        পূর্ণাঙ্ক y;
        পূর্ণাঙ্ক width;
        পূর্ণাঙ্ক height;
    } logical;

    সংরচনা
    {
        পূর্ণাঙ্ক x;
        পূর্ণাঙ্ক y;
        পূর্ণাঙ্ক width;
        পূর্ণাঙ্ক height;
    } pixel;

    সংরচনা
    {
        পূর্ণাঙ্ক width_mm;  // Physical width in millimeters.
        পূর্ণাঙ্ক height_mm; // Physical height in millimeters.
    } physical;

    পূর্ণাঙ্ক refresh;   // Refresh in mHz
    পূর্ণাঙ্ক transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    পূর্ণাঙ্ক wl_output_done_গুনতি;
    bool has_logical_position;
    bool has_logical_size;
    bool geometry_changed;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#অন্তর্ভাব "SDL_waylanddyn.h"

বাহ্য শূন্য SDL_WAYLAND_register_surface(সংরচনা wl_surface *surface);
বাহ্য শূন্য SDL_WAYLAND_register_output(সংরচনা wl_output *output);
বাহ্য bool SDL_WAYLAND_own_surface(সংরচনা wl_surface *surface);
বাহ্য bool SDL_WAYLAND_own_output(সংরচনা wl_output *output);

বাহ্য SDL_WindowData *Wayland_GetWindowDataForOwnedSurface(সংরচনা wl_surface *surface);
বাহ্য শূন্য Wayland_AddWindowDataToExternalList(SDL_WindowData *data);
বাহ্য শূন্য Wayland_RemoveWindowDataFromExternalList(SDL_WindowData *data);
বাহ্য সংরচনা wl_event_queue *Wayland_DisplayCreateQueue(সংরচনা wl_display *display, ধ্রুব বর্ণ *name);
বাহ্য শূন্য Wayland_CreateSession(SDL_VideoData *data);

বাহ্য bool Wayland_LoadLibdecor(SDL_VideoData *data, bool ignore_xdg);

বাহ্য bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#endif // SDL_waylandvideo_h_
