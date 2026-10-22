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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_waylandvideo_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_waylandvideo_h_

#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/egl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "wayland-util.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_dbus.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_ime.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandeventthread.h"

ਬਣਤਰ xkb_context;
ਬਣਤਰ SDL_WaylandSeat;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਬਣਤਰ wl_cursor_theme *theme;
    ਪੂਰਨ ਮਾਪ;
} SDL_WaylandCursorTheme;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਬਣਤਰ wl_list link;
    ਅੱਖਰ wl_output_name[];
} SDL_WaylandConnectorName;

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ
{
    ਬਣਤਰ wl_display *display;
    ਬਣਤਰ wl_registry *registry;
    ਬਣਤਰ wl_compositor *compositor;
    ਬਣਤਰ wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    ਪੂਰਨ ਅੰਕ_cursor_themes;
    ਬਣਤਰ
    {
        ਬਣਤਰ xdg_wm_ਅਧਾਰ *xdg;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
        ਬਣਤਰ libdecor *libdecor;
#ਜੇ_ਅੰਤ
    } shell;
    ਬਣਤਰ wl_subcompositor *subcompositor;
    ਬਣਤਰ zwp_relative_ਸੂਚਕ_manager_v1 *relative_ਸੂਚਕ_manager;
    ਬਣਤਰ zwp_ਸੂਚਕ_constraints_v1 *ਸੂਚਕ_constraints;
    ਬਣਤਰ wp_ਸੂਚਕ_warp_v1 *wp_ਸੂਚਕ_warp_v1;
    ਬਣਤਰ wp_cursor_shape_manager_v1 *cursor_shape_manager;
    ਬਣਤਰ wl_ਅੰਕੜੇ_device_manager *ਅੰਕੜੇ_device_manager;
    ਬਣਤਰ zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    ਬਣਤਰ zxdg_decoration_manager_v1 *decoration_manager;
    ਬਣਤਰ zwp_keyboard_shortcuts_inhibit_manager_v1 *ਕੁੰਜੀ_inhibitor_manager;
    ਬਣਤਰ zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    ਬਣਤਰ xdg_activation_v1 *activation_manager;
    ਬਣਤਰ zwp_ਪਾਠ_ਨਿਵੇਸ਼_manager_v3 *ਪਾਠ_ਨਿਵੇਸ਼_manager;
    ਬਣਤਰ zxdg_output_manager_v1 *xdg_output_manager;
    ਬਣਤਰ wp_viewporter *viewporter;
    ਬਣਤਰ wp_fractional_scale_manager_v1 *fractional_scale_manager;
    ਬਣਤਰ zwp_ਨਿਵੇਸ਼_timestamps_manager_v1 *ਨਿਵੇਸ਼_timestamps_manager;
    ਬਣਤਰ zxdg_exporter_v2 *zxdg_exporter_v2;
    ਬਣਤਰ xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    ਬਣਤਰ wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    ਬਣਤਰ xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    ਬਣਤਰ frog_color_management_factory_v1 *frog_color_management_factory_v1;
    ਬਣਤਰ wp_color_manager_v1 *wp_color_manager_v1;
    ਬਣਤਰ zwp_tablet_manager_v2 *tablet_manager;
    ਬਣਤਰ wl_fixes *wl_fixes;
    ਬਣਤਰ zwp_ਸੂਚਕ_gestures_v1 *zwp_ਸੂਚਕ_gestures;
    ਬਣਤਰ wp_single_pixel_ਬਫਰ_manager_v1 *single_pixel_ਬਫਰ_manager;
    ਬਣਤਰ xdg_session_manager_v1 *xdg_session_manager;
    ਬਣਤਰ xdg_toplevel_ਟੈਗ_manager_v1 *xdg_toplevel_ਟੈਗ_manager;

    ਬਣਤਰ xdg_session_v1 *xdg_session;
    ਬਣਤਰ xkb_context *xkb_context;

    ਬਣਤਰ wl_list seat_list;
    ਬਣਤਰ SDL_WaylandSeat *ਆਖਰੀ_implicit_grab_seat;
    ਬਣਤਰ SDL_WaylandSeat *current_ਅੰਕੜੇ_offer_seat;
    ਬਣਤਰ SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_ਕੰਮ_Thread_Context *ਕੰਮ_thread_context;

    SDL_Display_ਅੰਕੜੇ **output_list;
    ਪੂਰਨ output_ਗਿਣਤੀ;
    ਪੂਰਨ output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_ਮੰਜ਼ਿਲ_display_enabled;
};

ਬਣਤਰ SDL_Display_ਅੰਕੜੇ
{
    SDL_Video_ਅੰਕੜੇ *videodata;
    ਬਣਤਰ wl_output *output;
    ਬਣਤਰ zxdg_output_v1 *xdg_output;
    ਬਣਤਰ wp_color_management_output_v1 *wp_color_management_output;
    ਬਣਤਰ Wayland_ColorInfoState *color_info_state;
    ਅੱਖਰ *wl_output_name;
    ਦੁੱਗਣਾ scale_ਗੁਣਕ_2;
    ਪੂਰਨ integer_scale_ਗੁਣਕ; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    ਬਣਤਰ
    {
        ਪੂਰਨ x;
        ਪੂਰਨ y;
        ਪੂਰਨ ਚੌੜਾਈ;
        ਪੂਰਨ ਉਚਾਈ;
    } logical;

    ਬਣਤਰ
    {
        ਪੂਰਨ x;
        ਪੂਰਨ y;
        ਪੂਰਨ ਚੌੜਾਈ;
        ਪੂਰਨ ਉਚਾਈ;
    } pixel;

    ਬਣਤਰ
    {
        ਪੂਰਨ ਚੌੜਾਈ_mm;  // Physical width in millimeters.
        ਪੂਰਨ ਉਚਾਈ_mm; // Physical height in millimeters.
    } physical;

    ਪੂਰਨ refresh;   // Refresh in mHz
    ਪੂਰਨ transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    ਪੂਰਨ wl_output_ਪੂਰਾ_ਗਿਣਤੀ;
    bool has_logical_position;
    bool has_logical_ਮਾਪ;
    bool geometry_ਬਦਲਿਆ;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylanddyn.h"

ਬਾਹਰੀ ਖਾਲੀ SDL_WAYLAND_ਰਜਿਸਟਰ_surface(ਬਣਤਰ wl_surface *surface);
ਬਾਹਰੀ ਖਾਲੀ SDL_WAYLAND_ਰਜਿਸਟਰ_output(ਬਣਤਰ wl_output *output);
ਬਾਹਰੀ bool SDL_WAYLAND_own_surface(ਬਣਤਰ wl_surface *surface);
ਬਾਹਰੀ bool SDL_WAYLAND_own_output(ਬਣਤਰ wl_output *output);

ਬਾਹਰੀ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *Wayland_Get_ਖਿੜਕੀ_ਅੰਕੜੇ_For_Owned_Surface(ਬਣਤਰ wl_surface *surface);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਜੋੜੋ_ਖਿੜਕੀ_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ_External_List(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Remove_ਖਿੜਕੀ_ਅੰਕੜੇ_From_External_List(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਬਾਹਰੀ ਬਣਤਰ wl_event_ਕਤਾਰ *Wayland_Display_Create_ਕਤਾਰ(ਬਣਤਰ wl_display *display, ਅਚਲ ਅੱਖਰ *name);
ਬਾਹਰੀ ਖਾਲੀ Wayland_CreateSession(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ);

ਬਾਹਰੀ bool Wayland_ਲੱਦੋ_Libdecor(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ, bool ignore_xdg);

ਬਾਹਰੀ bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#ਜੇ_ਅੰਤ // SDL_waylandvideo_h_
