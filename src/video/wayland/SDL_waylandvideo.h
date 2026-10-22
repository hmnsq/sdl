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

#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_waylandvideo_h_
#define SDL_waylandvideo_h_

#அந்தர்பாவ <EGL/egl.h>
#அந்தர்பாவ "wayland-util.h"

#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../../core/linux/SDL_dbus.h"
#அந்தர்பாவ "../../core/linux/SDL_ime.h"
#அந்தர்பாவ "SDL_waylandeventthread.h"

கட்டமைப்பு xkb_context;
கட்டமைப்பு SDL_WaylandSeat;

வகைவரை கட்டமைப்பு
{
    கட்டமைப்பு wl_cursor_theme *theme;
    முழு size;
} SDL_WaylandCursorTheme;

வகைவரை கட்டமைப்பு
{
    கட்டமைப்பு wl_list link;
    எழுத்து wl_output_name[];
} SDL_WaylandConnectorName;

கட்டமைப்பு SDL_VideoData
{
    கட்டமைப்பு wl_display *display;
    கட்டமைப்பு wl_registry *registry;
    கட்டமைப்பு wl_compositor *compositor;
    கட்டமைப்பு wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    முழு இலக்கம்_cursor_themes;
    கட்டமைப்பு
    {
        கட்டமைப்பு xdg_wm_base *xdg;
#ifdef HAVE_LIBDECOR_H
        கட்டமைப்பு libdecor *libdecor;
#endif
    } shell;
    கட்டமைப்பு wl_subcompositor *subcompositor;
    கட்டமைப்பு zwp_relative_pointer_manager_v1 *relative_pointer_manager;
    கட்டமைப்பு zwp_pointer_constraints_v1 *pointer_constraints;
    கட்டமைப்பு wp_pointer_warp_v1 *wp_pointer_warp_v1;
    கட்டமைப்பு wp_cursor_shape_manager_v1 *cursor_shape_manager;
    கட்டமைப்பு wl_data_device_manager *data_device_manager;
    கட்டமைப்பு zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    கட்டமைப்பு zxdg_decoration_manager_v1 *decoration_manager;
    கட்டமைப்பு zwp_keyboard_shortcuts_inhibit_manager_v1 *சாவி_inhibitor_manager;
    கட்டமைப்பு zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    கட்டமைப்பு xdg_activation_v1 *activation_manager;
    கட்டமைப்பு zwp_text_உள்ளீடு_manager_v3 *text_உள்ளீடு_manager;
    கட்டமைப்பு zxdg_output_manager_v1 *xdg_output_manager;
    கட்டமைப்பு wp_viewporter *viewporter;
    கட்டமைப்பு wp_fractional_scale_manager_v1 *fractional_scale_manager;
    கட்டமைப்பு zwp_உள்ளீடு_timestamps_manager_v1 *உள்ளீடு_timestamps_manager;
    கட்டமைப்பு zxdg_exporter_v2 *zxdg_exporter_v2;
    கட்டமைப்பு xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    கட்டமைப்பு wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    கட்டமைப்பு xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    கட்டமைப்பு frog_color_management_factory_v1 *frog_color_management_factory_v1;
    கட்டமைப்பு wp_color_manager_v1 *wp_color_manager_v1;
    கட்டமைப்பு zwp_tablet_manager_v2 *tablet_manager;
    கட்டமைப்பு wl_fixes *wl_fixes;
    கட்டமைப்பு zwp_pointer_gestures_v1 *zwp_pointer_gestures;
    கட்டமைப்பு wp_single_pixel_buffer_manager_v1 *single_pixel_buffer_manager;
    கட்டமைப்பு xdg_session_manager_v1 *xdg_session_manager;
    கட்டமைப்பு xdg_toplevel_tag_manager_v1 *xdg_toplevel_tag_manager;

    கட்டமைப்பு xdg_session_v1 *xdg_session;
    கட்டமைப்பு xkb_context *xkb_context;

    கட்டமைப்பு wl_list seat_list;
    கட்டமைப்பு SDL_WaylandSeat *last_implicit_grab_seat;
    கட்டமைப்பு SDL_WaylandSeat *current_data_offer_seat;
    கட்டமைப்பு SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_JobThreadContext *job_thread_context;

    SDL_DisplayData **output_list;
    முழு output_மொத்தம்;
    முழு output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_to_display_enabled;
};

கட்டமைப்பு SDL_DisplayData
{
    SDL_VideoData *videodata;
    கட்டமைப்பு wl_output *output;
    கட்டமைப்பு zxdg_output_v1 *xdg_output;
    கட்டமைப்பு wp_color_management_output_v1 *wp_color_management_output;
    கட்டமைப்பு Wayland_ColorInfoState *color_info_state;
    எழுத்து *wl_output_name;
    இரட்டை scale_factor;
    முழு integer_scale_factor; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    கட்டமைப்பு
    {
        முழு x;
        முழு y;
        முழு width;
        முழு height;
    } logical;

    கட்டமைப்பு
    {
        முழு x;
        முழு y;
        முழு width;
        முழு height;
    } pixel;

    கட்டமைப்பு
    {
        முழு width_mm;  // Physical width in millimeters.
        முழு height_mm; // Physical height in millimeters.
    } physical;

    முழு refresh;   // Refresh in mHz
    முழு transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    முழு wl_output_done_மொத்தம்;
    bool has_logical_position;
    bool has_logical_size;
    bool geometry_changed;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#அந்தர்பாவ "SDL_waylanddyn.h"

வெளி வெறுமை SDL_WAYLAND_register_surface(கட்டமைப்பு wl_surface *surface);
வெளி வெறுமை SDL_WAYLAND_register_output(கட்டமைப்பு wl_output *output);
வெளி bool SDL_WAYLAND_own_surface(கட்டமைப்பு wl_surface *surface);
வெளி bool SDL_WAYLAND_own_output(கட்டமைப்பு wl_output *output);

வெளி SDL_WindowData *Wayland_GetWindowDataForOwnedSurface(கட்டமைப்பு wl_surface *surface);
வெளி வெறுமை Wayland_AddWindowDataToExternalList(SDL_WindowData *data);
வெளி வெறுமை Wayland_RemoveWindowDataFromExternalList(SDL_WindowData *data);
வெளி கட்டமைப்பு wl_event_queue *Wayland_DisplayCreateQueue(கட்டமைப்பு wl_display *display, மாறிலி எழுத்து *name);
வெளி வெறுமை Wayland_CreateSession(SDL_VideoData *data);

வெளி bool Wayland_LoadLibdecor(SDL_VideoData *data, bool ignore_xdg);

வெளி bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#endif // SDL_waylandvideo_h_
