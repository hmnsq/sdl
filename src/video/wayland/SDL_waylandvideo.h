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

#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_waylandvideo_h_
#define SDL_waylandvideo_h_

#അന്തര്ഭാവ <EGL/egl.h>
#അന്തര്ഭാവ "wayland-util.h"

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../../core/linux/SDL_dbus.h"
#അന്തര്ഭാവ "../../core/linux/SDL_ime.h"
#അന്തര്ഭാവ "SDL_waylandeventthread.h"

ഘടന xkb_context;
ഘടന SDL_WaylandSeat;

തരനിർവചനം ഘടന
{
    ഘടന wl_cursor_theme *theme;
    പൂർണ്ണസംഖ്യ size;
} SDL_WaylandCursorTheme;

തരനിർവചനം ഘടന
{
    ഘടന wl_list link;
    അക്ഷരം wl_output_name[];
} SDL_WaylandConnectorName;

ഘടന SDL_VideoData
{
    ഘടന wl_display *display;
    ഘടന wl_registry *registry;
    ഘടന wl_compositor *compositor;
    ഘടന wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    പൂർണ്ണസംഖ്യ അക്കം_cursor_themes;
    ഘടന
    {
        ഘടന xdg_wm_base *xdg;
#ifdef HAVE_LIBDECOR_H
        ഘടന libdecor *libdecor;
#endif
    } shell;
    ഘടന wl_subcompositor *subcompositor;
    ഘടന zwp_relative_pointer_manager_v1 *relative_pointer_manager;
    ഘടന zwp_pointer_constraints_v1 *pointer_constraints;
    ഘടന wp_pointer_warp_v1 *wp_pointer_warp_v1;
    ഘടന wp_cursor_shape_manager_v1 *cursor_shape_manager;
    ഘടന wl_data_device_manager *data_device_manager;
    ഘടന zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    ഘടന zxdg_decoration_manager_v1 *decoration_manager;
    ഘടന zwp_keyboard_shortcuts_inhibit_manager_v1 *താക്കോൽ_inhibitor_manager;
    ഘടന zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    ഘടന xdg_activation_v1 *activation_manager;
    ഘടന zwp_text_നിവേശം_manager_v3 *text_നിവേശം_manager;
    ഘടന zxdg_output_manager_v1 *xdg_output_manager;
    ഘടന wp_viewporter *viewporter;
    ഘടന wp_fractional_scale_manager_v1 *fractional_scale_manager;
    ഘടന zwp_നിവേശം_timestamps_manager_v1 *നിവേശം_timestamps_manager;
    ഘടന zxdg_exporter_v2 *zxdg_exporter_v2;
    ഘടന xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    ഘടന wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    ഘടന xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    ഘടന frog_color_management_factory_v1 *frog_color_management_factory_v1;
    ഘടന wp_color_manager_v1 *wp_color_manager_v1;
    ഘടന zwp_tablet_manager_v2 *tablet_manager;
    ഘടന wl_fixes *wl_fixes;
    ഘടന zwp_pointer_gestures_v1 *zwp_pointer_gestures;
    ഘടന wp_single_pixel_buffer_manager_v1 *single_pixel_buffer_manager;
    ഘടന xdg_session_manager_v1 *xdg_session_manager;
    ഘടന xdg_toplevel_tag_manager_v1 *xdg_toplevel_tag_manager;

    ഘടന xdg_session_v1 *xdg_session;
    ഘടന xkb_context *xkb_context;

    ഘടന wl_list seat_list;
    ഘടന SDL_WaylandSeat *last_implicit_grab_seat;
    ഘടന SDL_WaylandSeat *current_data_offer_seat;
    ഘടന SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_JobThreadContext *job_thread_context;

    SDL_DisplayData **output_list;
    പൂർണ്ണസംഖ്യ output_എണ്ണം;
    പൂർണ്ണസംഖ്യ output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_to_display_enabled;
};

ഘടന SDL_DisplayData
{
    SDL_VideoData *videodata;
    ഘടന wl_output *output;
    ഘടന zxdg_output_v1 *xdg_output;
    ഘടന wp_color_management_output_v1 *wp_color_management_output;
    ഘടന Wayland_ColorInfoState *color_info_state;
    അക്ഷരം *wl_output_name;
    ഇരട്ട scale_factor;
    പൂർണ്ണസംഖ്യ integer_scale_factor; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    ഘടന
    {
        പൂർണ്ണസംഖ്യ x;
        പൂർണ്ണസംഖ്യ y;
        പൂർണ്ണസംഖ്യ width;
        പൂർണ്ണസംഖ്യ height;
    } logical;

    ഘടന
    {
        പൂർണ്ണസംഖ്യ x;
        പൂർണ്ണസംഖ്യ y;
        പൂർണ്ണസംഖ്യ width;
        പൂർണ്ണസംഖ്യ height;
    } pixel;

    ഘടന
    {
        പൂർണ്ണസംഖ്യ width_mm;  // Physical width in millimeters.
        പൂർണ്ണസംഖ്യ height_mm; // Physical height in millimeters.
    } physical;

    പൂർണ്ണസംഖ്യ refresh;   // Refresh in mHz
    പൂർണ്ണസംഖ്യ transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    പൂർണ്ണസംഖ്യ wl_output_done_എണ്ണം;
    bool has_logical_position;
    bool has_logical_size;
    bool geometry_changed;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#അന്തര്ഭാവ "SDL_waylanddyn.h"

ബാഹ്യ ശൂന്യം SDL_WAYLAND_register_surface(ഘടന wl_surface *surface);
ബാഹ്യ ശൂന്യം SDL_WAYLAND_register_output(ഘടന wl_output *output);
ബാഹ്യ bool SDL_WAYLAND_own_surface(ഘടന wl_surface *surface);
ബാഹ്യ bool SDL_WAYLAND_own_output(ഘടന wl_output *output);

ബാഹ്യ SDL_WindowData *Wayland_GetWindowDataForOwnedSurface(ഘടന wl_surface *surface);
ബാഹ്യ ശൂന്യം Wayland_AddWindowDataToExternalList(SDL_WindowData *data);
ബാഹ്യ ശൂന്യം Wayland_RemoveWindowDataFromExternalList(SDL_WindowData *data);
ബാഹ്യ ഘടന wl_event_queue *Wayland_DisplayCreateQueue(ഘടന wl_display *display, സ്ഥിരം അക്ഷരം *name);
ബാഹ്യ ശൂന്യം Wayland_CreateSession(SDL_VideoData *data);

ബാഹ്യ bool Wayland_LoadLibdecor(SDL_VideoData *data, bool ignore_xdg);

ബാഹ്യ bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#endif // SDL_waylandvideo_h_
