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

কাঠামো xkb_context;
কাঠামো SDL_WaylandSeat;

প্রকারলেখ কাঠামো
{
    কাঠামো wl_cursor_theme *theme;
    পূর্ণসংখ্যা আকার_2;
} SDL_WaylandCursorTheme;

প্রকারলেখ কাঠামো
{
    কাঠামো wl_list link;
    অক্ষর wl_output_name[];
} SDL_WaylandConnectorName;

কাঠামো SDL_Video_তথ্য
{
    কাঠামো wl_display *display;
    কাঠামো wl_registry *registry;
    কাঠামো wl_compositor *compositor;
    কাঠামো wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    পূর্ণসংখ্যা অঙ্ক_cursor_themes;
    কাঠামো
    {
        কাঠামো xdg_wm_base *xdg;
#ifdef HAVE_LIBDECOR_H
        কাঠামো libdecor *libdecor;
#endif
    } shell;
    কাঠামো wl_subcompositor *subcompositor;
    কাঠামো zwp_relative_pointer_manager_v1 *relative_pointer_manager;
    কাঠামো zwp_pointer_constraints_v1 *pointer_constraints;
    কাঠামো wp_pointer_warp_v1 *wp_pointer_warp_v1;
    কাঠামো wp_cursor_shape_manager_v1 *cursor_shape_manager;
    কাঠামো wl_তথ্য_device_manager *তথ্য_device_manager;
    কাঠামো zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    কাঠামো zxdg_decoration_manager_v1 *decoration_manager;
    কাঠামো zwp_keyboard_shortcuts_inhibit_manager_v1 *চাবি_inhibitor_manager;
    কাঠামো zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    কাঠামো xdg_activation_v1 *activation_manager;
    কাঠামো zwp_text_প্রবেশ_manager_v3 *text_প্রবেশ_manager;
    কাঠামো zxdg_output_manager_v1 *xdg_output_manager;
    কাঠামো wp_viewporter *viewporter;
    কাঠামো wp_fractional_scale_manager_v1 *fractional_scale_manager;
    কাঠামো zwp_প্রবেশ_timestamps_manager_v1 *প্রবেশ_timestamps_manager;
    কাঠামো zxdg_exporter_v2 *zxdg_exporter_v2;
    কাঠামো xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    কাঠামো wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    কাঠামো xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    কাঠামো frog_color_management_factory_v1 *frog_color_management_factory_v1;
    কাঠামো wp_color_manager_v1 *wp_color_manager_v1;
    কাঠামো zwp_tablet_manager_v2 *tablet_manager;
    কাঠামো wl_fixes *wl_fixes;
    কাঠামো zwp_pointer_gestures_v1 *zwp_pointer_gestures;
    কাঠামো wp_single_pixel_বাফার_manager_v1 *single_pixel_বাফার_manager;
    কাঠামো xdg_session_manager_v1 *xdg_session_manager;
    কাঠামো xdg_toplevel_tag_manager_v1 *xdg_toplevel_tag_manager;

    কাঠামো xdg_session_v1 *xdg_session;
    কাঠামো xkb_context *xkb_context;

    কাঠামো wl_list seat_list;
    কাঠামো SDL_WaylandSeat *last_implicit_grab_seat;
    কাঠামো SDL_WaylandSeat *current_তথ্য_offer_seat;
    কাঠামো SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_JobThreadContext *job_thread_context;

    SDL_Display_তথ্য **output_list;
    পূর্ণসংখ্যা output_গুনতি;
    পূর্ণসংখ্যা output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_to_display_enabled;
};

কাঠামো SDL_Display_তথ্য
{
    SDL_Video_তথ্য *videodata;
    কাঠামো wl_output *output;
    কাঠামো zxdg_output_v1 *xdg_output;
    কাঠামো wp_color_management_output_v1 *wp_color_management_output;
    কাঠামো Wayland_ColorInfoState *color_info_state;
    অক্ষর *wl_output_name;
    দ্বিগুণ scale_factor;
    পূর্ণসংখ্যা integer_scale_factor; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    কাঠামো
    {
        পূর্ণসংখ্যা x;
        পূর্ণসংখ্যা y;
        পূর্ণসংখ্যা width;
        পূর্ণসংখ্যা height;
    } logical;

    কাঠামো
    {
        পূর্ণসংখ্যা x;
        পূর্ণসংখ্যা y;
        পূর্ণসংখ্যা width;
        পূর্ণসংখ্যা height;
    } pixel;

    কাঠামো
    {
        পূর্ণসংখ্যা width_mm;  // Physical width in millimeters.
        পূর্ণসংখ্যা height_mm; // Physical height in millimeters.
    } physical;

    পূর্ণসংখ্যা refresh;   // Refresh in mHz
    পূর্ণসংখ্যা transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    পূর্ণসংখ্যা wl_output_done_গুনতি;
    bool has_logical_position;
    bool has_logical_আকার;
    bool geometry_changed;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#অন্তর্ভাব "SDL_waylanddyn.h"

বাহ্যিক শূন্য SDL_WAYLAND_register_surface(কাঠামো wl_surface *surface);
বাহ্যিক শূন্য SDL_WAYLAND_register_output(কাঠামো wl_output *output);
বাহ্যিক bool SDL_WAYLAND_own_surface(কাঠামো wl_surface *surface);
বাহ্যিক bool SDL_WAYLAND_own_output(কাঠামো wl_output *output);

বাহ্যিক SDL_Window_তথ্য *Wayland_Get_Window_তথ্য_For_Owned_Surface(কাঠামো wl_surface *surface);
বাহ্যিক শূন্য Wayland_Add_Window_তথ্য_To_External_List(SDL_Window_তথ্য *তথ্য);
বাহ্যিক শূন্য Wayland_Remove_Window_তথ্য_From_External_List(SDL_Window_তথ্য *তথ্য);
বাহ্যিক কাঠামো wl_event_queue *Wayland_DisplayCreateQueue(কাঠামো wl_display *display, ধ্রুবক অক্ষর *name);
বাহ্যিক শূন্য Wayland_CreateSession(SDL_Video_তথ্য *তথ্য);

বাহ্যিক bool Wayland_LoadLibdecor(SDL_Video_তথ্য *তথ্য, bool ignore_xdg);

বাহ্যিক bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#endif // SDL_waylandvideo_h_
