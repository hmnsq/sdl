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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_waylandvideo_h_
#define SDL_waylandvideo_h_

#ଅନ୍ତର୍ଭାଵ <EGL/egl.h>
#ଅନ୍ତର୍ଭାଵ "wayland-util.h"

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../../core/linux/SDL_dbus.h"
#ଅନ୍ତର୍ଭାଵ "../../core/linux/SDL_ime.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandeventthread.h"

ସଂରଚନା xkb_context;
ସଂରଚନା SDL_WaylandSeat;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ସଂରଚନା wl_cursor_theme *theme;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା size;
} SDL_WaylandCursorTheme;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ସଂରଚନା wl_list link;
    ଅକ୍ଷର wl_output_name[];
} SDL_WaylandConnectorName;

ସଂରଚନା SDL_VideoData
{
    ସଂରଚନା wl_display *display;
    ସଂରଚନା wl_registry *registry;
    ସଂରଚନା wl_compositor *compositor;
    ସଂରଚନା wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_cursor_themes;
    ସଂରଚନା
    {
        ସଂରଚନା xdg_wm_base *xdg;
#ifdef HAVE_LIBDECOR_H
        ସଂରଚନା libdecor *libdecor;
#endif
    } shell;
    ସଂରଚନା wl_subcompositor *subcompositor;
    ସଂରଚନା zwp_relative_pointer_manager_v1 *relative_pointer_manager;
    ସଂରଚନା zwp_pointer_constraints_v1 *pointer_constraints;
    ସଂରଚନା wp_pointer_warp_v1 *wp_pointer_warp_v1;
    ସଂରଚନା wp_cursor_shape_manager_v1 *cursor_shape_manager;
    ସଂରଚନା wl_data_device_manager *data_device_manager;
    ସଂରଚନା zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    ସଂରଚନା zxdg_decoration_manager_v1 *decoration_manager;
    ସଂରଚନା zwp_keyboard_shortcuts_inhibit_manager_v1 *ଚାବି_inhibitor_manager;
    ସଂରଚନା zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    ସଂରଚନା xdg_activation_v1 *activation_manager;
    ସଂରଚନା zwp_text_ନିବେଶ_manager_v3 *text_ନିବେଶ_manager;
    ସଂରଚନା zxdg_output_manager_v1 *xdg_output_manager;
    ସଂରଚନା wp_viewporter *viewporter;
    ସଂରଚନା wp_fractional_scale_manager_v1 *fractional_scale_manager;
    ସଂରଚନା zwp_ନିବେଶ_timestamps_manager_v1 *ନିବେଶ_timestamps_manager;
    ସଂରଚନା zxdg_exporter_v2 *zxdg_exporter_v2;
    ସଂରଚନା xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    ସଂରଚନା wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    ସଂରଚନା xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    ସଂରଚନା frog_color_management_factory_v1 *frog_color_management_factory_v1;
    ସଂରଚନା wp_color_manager_v1 *wp_color_manager_v1;
    ସଂରଚନା zwp_tablet_manager_v2 *tablet_manager;
    ସଂରଚନା wl_fixes *wl_fixes;
    ସଂରଚନା zwp_pointer_gestures_v1 *zwp_pointer_gestures;
    ସଂରଚନା wp_single_pixel_buffer_manager_v1 *single_pixel_buffer_manager;
    ସଂରଚନା xdg_session_manager_v1 *xdg_session_manager;
    ସଂରଚନା xdg_toplevel_tag_manager_v1 *xdg_toplevel_tag_manager;

    ସଂରଚନା xdg_session_v1 *xdg_session;
    ସଂରଚନା xkb_context *xkb_context;

    ସଂରଚନା wl_list seat_list;
    ସଂରଚନା SDL_WaylandSeat *last_implicit_grab_seat;
    ସଂରଚନା SDL_WaylandSeat *current_data_offer_seat;
    ସଂରଚନା SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_JobThreadContext *job_thread_context;

    SDL_DisplayData **output_list;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା output_ଗଣନା;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_to_display_enabled;
};

ସଂରଚନା SDL_DisplayData
{
    SDL_VideoData *videodata;
    ସଂରଚନା wl_output *output;
    ସଂରଚନା zxdg_output_v1 *xdg_output;
    ସଂରଚନା wp_color_management_output_v1 *wp_color_management_output;
    ସଂରଚନା Wayland_ColorInfoState *color_info_state;
    ଅକ୍ଷର *wl_output_name;
    ଦ୍ୱିଗୁଣ scale_factor;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା integer_scale_factor; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    ସଂରଚନା
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା x;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା y;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା width;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା height;
    } logical;

    ସଂରଚନା
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା x;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା y;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା width;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା height;
    } pixel;

    ସଂରଚନା
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା width_mm;  // Physical width in millimeters.
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା height_mm; // Physical height in millimeters.
    } physical;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା refresh;   // Refresh in mHz
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା wl_output_done_ଗଣନା;
    bool has_logical_position;
    bool has_logical_size;
    bool geometry_changed;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#ଅନ୍ତର୍ଭାଵ "SDL_waylanddyn.h"

ବାହ୍ୟ ଶୂନ୍ୟ SDL_WAYLAND_register_surface(ସଂରଚନା wl_surface *surface);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_WAYLAND_register_output(ସଂରଚନା wl_output *output);
ବାହ୍ୟ bool SDL_WAYLAND_own_surface(ସଂରଚନା wl_surface *surface);
ବାହ୍ୟ bool SDL_WAYLAND_own_output(ସଂରଚନା wl_output *output);

ବାହ୍ୟ SDL_WindowData *Wayland_GetWindowDataForOwnedSurface(ସଂରଚନା wl_surface *surface);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_AddWindowDataToExternalList(SDL_WindowData *data);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_RemoveWindowDataFromExternalList(SDL_WindowData *data);
ବାହ୍ୟ ସଂରଚନା wl_event_queue *Wayland_DisplayCreateQueue(ସଂରଚନା wl_display *display, ଅଚଳ ଅକ୍ଷର *name);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_CreateSession(SDL_VideoData *data);

ବାହ୍ୟ bool Wayland_LoadLibdecor(SDL_VideoData *data, bool ignore_xdg);

ବାହ୍ୟ bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#endif // SDL_waylandvideo_h_
