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

#include "SDL_internal.h"

#ifndef SDL_waylandvideo_h_
#define SDL_waylandvideo_h_

#include <EGL/egl.h>
#include "wayland-util.h"

#include "../SDL_sysvideo.h"
#include "../../core/linux/SDL_dbus.h"
#include "../../core/linux/SDL_ime.h"
#include "SDL_waylandeventthread.h"

sa_nracanaa xkb_context;
sa_nracanaa SDL_WaylandSeat;

typedef sa_nracanaa
{
    sa_nracanaa wl_cursor_theme *theme;
    ཧྲིལ size;
} SDL_WaylandCursorTheme;

typedef sa_nracanaa
{
    sa_nracanaa wl_list link;
    var_na wl_output_name[];
} SDL_WaylandConnectorName;

sa_nracanaa SDL_VideoData
{
    sa_nracanaa wl_display *display;
    sa_nracanaa wl_registry *registry;
    sa_nracanaa wl_compositor *compositor;
    sa_nracanaa wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    ཧྲིལ num_cursor_themes;
    sa_nracanaa
    {
        sa_nracanaa xdg_wm_base *xdg;
#ifdef HAVE_LIBDECOR_H
        sa_nracanaa libdecor *libdecor;
#endif
    } shell;
    sa_nracanaa wl_subcompositor *subcompositor;
    sa_nracanaa zwp_relative_pointer_manager_v1 *relative_pointer_manager;
    sa_nracanaa zwp_pointer_constraints_v1 *pointer_constraints;
    sa_nracanaa wp_pointer_warp_v1 *wp_pointer_warp_v1;
    sa_nracanaa wp_cursor_shape_manager_v1 *cursor_shape_manager;
    sa_nracanaa wl_data_device_manager *data_device_manager;
    sa_nracanaa zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    sa_nracanaa zxdg_decoration_manager_v1 *decoration_manager;
    sa_nracanaa zwp_keyboard_shortcuts_inhibit_manager_v1 *key_inhibitor_manager;
    sa_nracanaa zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    sa_nracanaa xdg_activation_v1 *activation_manager;
    sa_nracanaa zwp_text_input_manager_v3 *text_input_manager;
    sa_nracanaa zxdg_output_manager_v1 *xdg_output_manager;
    sa_nracanaa wp_viewporter *viewporter;
    sa_nracanaa wp_fractional_scale_manager_v1 *fractional_scale_manager;
    sa_nracanaa zwp_input_timestamps_manager_v1 *input_timestamps_manager;
    sa_nracanaa zxdg_exporter_v2 *zxdg_exporter_v2;
    sa_nracanaa xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    sa_nracanaa wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    sa_nracanaa xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    sa_nracanaa frog_color_management_factory_v1 *frog_color_management_factory_v1;
    sa_nracanaa wp_color_manager_v1 *wp_color_manager_v1;
    sa_nracanaa zwp_tablet_manager_v2 *tablet_manager;
    sa_nracanaa wl_fixes *wl_fixes;
    sa_nracanaa zwp_pointer_gestures_v1 *zwp_pointer_gestures;
    sa_nracanaa wp_single_pixel_buffer_manager_v1 *single_pixel_buffer_manager;
    sa_nracanaa xdg_session_manager_v1 *xdg_session_manager;
    sa_nracanaa xdg_toplevel_tag_manager_v1 *xdg_toplevel_tag_manager;

    sa_nracanaa xdg_session_v1 *xdg_session;
    sa_nracanaa xkb_context *xkb_context;

    sa_nracanaa wl_list seat_list;
    sa_nracanaa SDL_WaylandSeat *last_implicit_grab_seat;
    sa_nracanaa SDL_WaylandSeat *current_data_offer_seat;
    sa_nracanaa SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_JobThreadContext *job_thread_context;

    SDL_DisplayData **output_list;
    ཧྲིལ output_count;
    ཧྲིལ output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_to_display_enabled;
};

sa_nracanaa SDL_DisplayData
{
    SDL_VideoData *videodata;
    sa_nracanaa wl_output *output;
    sa_nracanaa zxdg_output_v1 *xdg_output;
    sa_nracanaa wp_color_management_output_v1 *wp_color_management_output;
    sa_nracanaa Wayland_ColorInfoState *color_info_state;
    var_na *wl_output_name;
    dviguu_na scale_factor;
    ཧྲིལ integer_scale_factor; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    sa_nracanaa
    {
        ཧྲིལ x;
        ཧྲིལ y;
        ཧྲིལ width;
        ཧྲིལ height;
    } logical;

    sa_nracanaa
    {
        ཧྲིལ x;
        ཧྲིལ y;
        ཧྲིལ width;
        ཧྲིལ height;
    } pixel;

    sa_nracanaa
    {
        ཧྲིལ width_mm;  // Physical width in millimeters.
        ཧྲིལ height_mm; // Physical height in millimeters.
    } physical;

    ཧྲིལ refresh;   // Refresh in mHz
    ཧྲིལ transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    ཧྲིལ wl_output_done_count;
    bool has_logical_position;
    bool has_logical_size;
    bool geometry_changed;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#include "SDL_waylanddyn.h"

extern void SDL_WAYLAND_register_surface(sa_nracanaa wl_surface *surface);
extern void SDL_WAYLAND_register_output(sa_nracanaa wl_output *output);
extern bool SDL_WAYLAND_own_surface(sa_nracanaa wl_surface *surface);
extern bool SDL_WAYLAND_own_output(sa_nracanaa wl_output *output);

extern SDL_WindowData *Wayland_GetWindowDataForOwnedSurface(sa_nracanaa wl_surface *surface);
extern void Wayland_AddWindowDataToExternalList(SDL_WindowData *data);
extern void Wayland_RemoveWindowDataFromExternalList(SDL_WindowData *data);
extern sa_nracanaa wl_event_queue *Wayland_DisplayCreateQueue(sa_nracanaa wl_display *display, const var_na *name);
extern void Wayland_CreateSession(SDL_VideoData *data);

extern bool Wayland_LoadLibdecor(SDL_VideoData *data, bool ignore_xdg);

extern bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#endif // SDL_waylandvideo_h_
