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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_waylandvideo_h_
#define SDL_waylandvideo_h_

#ಅನ್ತರ್ಭಾವ <EGL/egl.h>
#ಅನ್ತರ್ಭಾವ "wayland-util.h"

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_dbus.h"
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_ime.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandeventthread.h"

ಸಂರಚನಾ xkb_context;
ಸಂರಚನಾ SDL_WaylandSeat;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಸಂರಚನಾ wl_cursor_theme *theme;
    ಪೂರ್ಣಾಙ್ಕ size;
} SDL_WaylandCursorTheme;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    ಸಂರಚನಾ wl_list link;
    ವರ್ಣ wl_output_name[];
} SDL_WaylandConnectorName;

ಸಂರಚನಾ SDL_VideoData
{
    ಸಂರಚನಾ wl_display *display;
    ಸಂರಚನಾ wl_registry *registry;
    ಸಂರಚನಾ wl_compositor *compositor;
    ಸಂರಚನಾ wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_cursor_themes;
    ಸಂರಚನಾ
    {
        ಸಂರಚನಾ xdg_wm_base *xdg;
#ifdef HAVE_LIBDECOR_H
        ಸಂರಚನಾ libdecor *libdecor;
#endif
    } shell;
    ಸಂರಚನಾ wl_subcompositor *subcompositor;
    ಸಂರಚನಾ zwp_relative_pointer_manager_v1 *relative_pointer_manager;
    ಸಂರಚನಾ zwp_pointer_constraints_v1 *pointer_constraints;
    ಸಂರಚನಾ wp_pointer_warp_v1 *wp_pointer_warp_v1;
    ಸಂರಚನಾ wp_cursor_shape_manager_v1 *cursor_shape_manager;
    ಸಂರಚನಾ wl_data_device_manager *data_device_manager;
    ಸಂರಚನಾ zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    ಸಂರಚನಾ zxdg_decoration_manager_v1 *decoration_manager;
    ಸಂರಚನಾ zwp_keyboard_shortcuts_inhibit_manager_v1 *ಕೀಲಿ_inhibitor_manager;
    ಸಂರಚನಾ zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    ಸಂರಚನಾ xdg_activation_v1 *activation_manager;
    ಸಂರಚನಾ zwp_text_ಒಳಹರಿವು_manager_v3 *text_ಒಳಹರಿವು_manager;
    ಸಂರಚನಾ zxdg_output_manager_v1 *xdg_output_manager;
    ಸಂರಚನಾ wp_viewporter *viewporter;
    ಸಂರಚನಾ wp_fractional_scale_manager_v1 *fractional_scale_manager;
    ಸಂರಚನಾ zwp_ಒಳಹರಿವು_timestamps_manager_v1 *ಒಳಹರಿವು_timestamps_manager;
    ಸಂರಚನಾ zxdg_exporter_v2 *zxdg_exporter_v2;
    ಸಂರಚನಾ xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    ಸಂರಚನಾ wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    ಸಂರಚನಾ xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    ಸಂರಚನಾ frog_color_management_factory_v1 *frog_color_management_factory_v1;
    ಸಂರಚನಾ wp_color_manager_v1 *wp_color_manager_v1;
    ಸಂರಚನಾ zwp_tablet_manager_v2 *tablet_manager;
    ಸಂರಚನಾ wl_fixes *wl_fixes;
    ಸಂರಚನಾ zwp_pointer_gestures_v1 *zwp_pointer_gestures;
    ಸಂರಚನಾ wp_single_pixel_buffer_manager_v1 *single_pixel_buffer_manager;
    ಸಂರಚನಾ xdg_session_manager_v1 *xdg_session_manager;
    ಸಂರಚನಾ xdg_toplevel_tag_manager_v1 *xdg_toplevel_tag_manager;

    ಸಂರಚನಾ xdg_session_v1 *xdg_session;
    ಸಂರಚನಾ xkb_context *xkb_context;

    ಸಂರಚನಾ wl_list seat_list;
    ಸಂರಚನಾ SDL_WaylandSeat *last_implicit_grab_seat;
    ಸಂರಚನಾ SDL_WaylandSeat *current_data_offer_seat;
    ಸಂರಚನಾ SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_JobThreadContext *job_thread_context;

    SDL_DisplayData **output_list;
    ಪೂರ್ಣಾಙ್ಕ output_ಎಣಿಕೆ;
    ಪೂರ್ಣಾಙ್ಕ output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_to_display_enabled;
};

ಸಂರಚನಾ SDL_DisplayData
{
    SDL_VideoData *videodata;
    ಸಂರಚನಾ wl_output *output;
    ಸಂರಚನಾ zxdg_output_v1 *xdg_output;
    ಸಂರಚನಾ wp_color_management_output_v1 *wp_color_management_output;
    ಸಂರಚನಾ Wayland_ColorInfoState *color_info_state;
    ವರ್ಣ *wl_output_name;
    ದ್ವಿಗುಣ scale_factor;
    ಪೂರ್ಣಾಙ್ಕ integer_scale_factor; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    ಸಂರಚನಾ
    {
        ಪೂರ್ಣಾಙ್ಕ x;
        ಪೂರ್ಣಾಙ್ಕ y;
        ಪೂರ್ಣಾಙ್ಕ width;
        ಪೂರ್ಣಾಙ್ಕ height;
    } logical;

    ಸಂರಚನಾ
    {
        ಪೂರ್ಣಾಙ್ಕ x;
        ಪೂರ್ಣಾಙ್ಕ y;
        ಪೂರ್ಣಾಙ್ಕ width;
        ಪೂರ್ಣಾಙ್ಕ height;
    } pixel;

    ಸಂರಚನಾ
    {
        ಪೂರ್ಣಾಙ್ಕ width_mm;  // Physical width in millimeters.
        ಪೂರ್ಣಾಙ್ಕ height_mm; // Physical height in millimeters.
    } physical;

    ಪೂರ್ಣಾಙ್ಕ refresh;   // Refresh in mHz
    ಪೂರ್ಣಾಙ್ಕ transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    ಪೂರ್ಣಾಙ್ಕ wl_output_done_ಎಣಿಕೆ;
    bool has_logical_position;
    bool has_logical_size;
    bool geometry_changed;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#ಅನ್ತರ್ಭಾವ "SDL_waylanddyn.h"

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_WAYLAND_register_surface(ಸಂರಚನಾ wl_surface *surface);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_WAYLAND_register_output(ಸಂರಚನಾ wl_output *output);
ಬಾಹ್ಯ bool SDL_WAYLAND_own_surface(ಸಂರಚನಾ wl_surface *surface);
ಬಾಹ್ಯ bool SDL_WAYLAND_own_output(ಸಂರಚನಾ wl_output *output);

ಬಾಹ್ಯ SDL_WindowData *Wayland_GetWindowDataForOwnedSurface(ಸಂರಚನಾ wl_surface *surface);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_AddWindowDataToExternalList(SDL_WindowData *data);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_RemoveWindowDataFromExternalList(SDL_WindowData *data);
ಬಾಹ್ಯ ಸಂರಚನಾ wl_event_queue *Wayland_DisplayCreateQueue(ಸಂರಚನಾ wl_display *display, ಧ್ರುವ ವರ್ಣ *name);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_CreateSession(SDL_VideoData *data);

ಬಾಹ್ಯ bool Wayland_LoadLibdecor(SDL_VideoData *data, bool ignore_xdg);

ಬಾಹ್ಯ bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#endif // SDL_waylandvideo_h_
