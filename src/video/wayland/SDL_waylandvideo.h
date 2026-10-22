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

#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_waylandvideo_h_
#define SDL_waylandvideo_h_

#અન્તર્ભાવ <EGL/egl.h>
#અન્તર્ભાવ "wayland-util.h"

#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "../../core/linux/SDL_dbus.h"
#અન્તર્ભાવ "../../core/linux/SDL_ime.h"
#અન્તર્ભાવ "SDL_waylandeventthread.h"

સંરચના xkb_context;
સંરચના SDL_WaylandSeat;

પ્રકારવ્યાખ્યા સંરચના
{
    સંરચના wl_cursor_theme *theme;
    પૂર્ણાંક size;
} SDL_WaylandCursorTheme;

પ્રકારવ્યાખ્યા સંરચના
{
    સંરચના wl_list link;
    અક્ષર wl_output_name[];
} SDL_WaylandConnectorName;

સંરચના SDL_VideoData
{
    સંરચના wl_display *display;
    સંરચના wl_registry *registry;
    સંરચના wl_compositor *compositor;
    સંરચના wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    પૂર્ણાંક અંક_cursor_themes;
    સંરચના
    {
        સંરચના xdg_wm_base *xdg;
#ifdef HAVE_LIBDECOR_H
        સંરચના libdecor *libdecor;
#endif
    } shell;
    સંરચના wl_subcompositor *subcompositor;
    સંરચના zwp_relative_pointer_manager_v1 *relative_pointer_manager;
    સંરચના zwp_pointer_constraints_v1 *pointer_constraints;
    સંરચના wp_pointer_warp_v1 *wp_pointer_warp_v1;
    સંરચના wp_cursor_shape_manager_v1 *cursor_shape_manager;
    સંરચના wl_data_device_manager *data_device_manager;
    સંરચના zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    સંરચના zxdg_decoration_manager_v1 *decoration_manager;
    સંરચના zwp_keyboard_shortcuts_inhibit_manager_v1 *ચાવી_inhibitor_manager;
    સંરચના zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    સંરચના xdg_activation_v1 *activation_manager;
    સંરચના zwp_text_આગત_manager_v3 *text_આગત_manager;
    સંરચના zxdg_output_manager_v1 *xdg_output_manager;
    સંરચના wp_viewporter *viewporter;
    સંરચના wp_fractional_scale_manager_v1 *fractional_scale_manager;
    સંરચના zwp_આગત_timestamps_manager_v1 *આગત_timestamps_manager;
    સંરચના zxdg_exporter_v2 *zxdg_exporter_v2;
    સંરચના xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    સંરચના wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    સંરચના xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    સંરચના frog_color_management_factory_v1 *frog_color_management_factory_v1;
    સંરચના wp_color_manager_v1 *wp_color_manager_v1;
    સંરચના zwp_tablet_manager_v2 *tablet_manager;
    સંરચના wl_fixes *wl_fixes;
    સંરચના zwp_pointer_gestures_v1 *zwp_pointer_gestures;
    સંરચના wp_single_pixel_buffer_manager_v1 *single_pixel_buffer_manager;
    સંરચના xdg_session_manager_v1 *xdg_session_manager;
    સંરચના xdg_toplevel_tag_manager_v1 *xdg_toplevel_tag_manager;

    સંરચના xdg_session_v1 *xdg_session;
    સંરચના xkb_context *xkb_context;

    સંરચના wl_list seat_list;
    સંરચના SDL_WaylandSeat *last_implicit_grab_seat;
    સંરચના SDL_WaylandSeat *current_data_offer_seat;
    સંરચના SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_JobThreadContext *job_thread_context;

    SDL_DisplayData **output_list;
    પૂર્ણાંક output_ગણતરી;
    પૂર્ણાંક output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_to_display_enabled;
};

સંરચના SDL_DisplayData
{
    SDL_VideoData *videodata;
    સંરચના wl_output *output;
    સંરચના zxdg_output_v1 *xdg_output;
    સંરચના wp_color_management_output_v1 *wp_color_management_output;
    સંરચના Wayland_ColorInfoState *color_info_state;
    અક્ષર *wl_output_name;
    દ્વિગુણ scale_factor;
    પૂર્ણાંક integer_scale_factor; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    સંરચના
    {
        પૂર્ણાંક x;
        પૂર્ણાંક y;
        પૂર્ણાંક width;
        પૂર્ણાંક height;
    } logical;

    સંરચના
    {
        પૂર્ણાંક x;
        પૂર્ણાંક y;
        પૂર્ણાંક width;
        પૂર્ણાંક height;
    } pixel;

    સંરચના
    {
        પૂર્ણાંક width_mm;  // Physical width in millimeters.
        પૂર્ણાંક height_mm; // Physical height in millimeters.
    } physical;

    પૂર્ણાંક refresh;   // Refresh in mHz
    પૂર્ણાંક transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    પૂર્ણાંક wl_output_done_ગણતરી;
    bool has_logical_position;
    bool has_logical_size;
    bool geometry_changed;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#અન્તર્ભાવ "SDL_waylanddyn.h"

બાહ્ય શૂન્ય SDL_WAYLAND_register_surface(સંરચના wl_surface *surface);
બાહ્ય શૂન્ય SDL_WAYLAND_register_output(સંરચના wl_output *output);
બાહ્ય bool SDL_WAYLAND_own_surface(સંરચના wl_surface *surface);
બાહ્ય bool SDL_WAYLAND_own_output(સંરચના wl_output *output);

બાહ્ય SDL_WindowData *Wayland_GetWindowDataForOwnedSurface(સંરચના wl_surface *surface);
બાહ્ય શૂન્ય Wayland_AddWindowDataToExternalList(SDL_WindowData *data);
બાહ્ય શૂન્ય Wayland_RemoveWindowDataFromExternalList(SDL_WindowData *data);
બાહ્ય સંરચના wl_event_queue *Wayland_DisplayCreateQueue(સંરચના wl_display *display, અચલ અક્ષર *name);
બાહ્ય શૂન્ય Wayland_CreateSession(SDL_VideoData *data);

બાહ્ય bool Wayland_LoadLibdecor(SDL_VideoData *data, bool ignore_xdg);

બાહ્ય bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#endif // SDL_waylandvideo_h_
