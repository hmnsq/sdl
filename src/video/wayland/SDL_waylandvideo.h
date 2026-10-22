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

#اگر_غیر_تعریف_شدہ SDL_waylandvideo_h_
#تعریف_کرو SDL_waylandvideo_h_

#شامل <EGL/egl.h>
#شامل "wayland-util.h"

#شامل "../SDL_sysvideo.h"
#شامل "../../core/linux/SDL_dbus.h"
#شامل "../../core/linux/SDL_ime.h"
#شامل "SDL_waylandeventthread.h"

ساخت xkb_context;
ساخت SDL_WaylandSeat;

قسمتعریف ساخت
{
    ساخت wl_cursor_theme *theme;
    صحیح سائز;
} SDL_WaylandCursorTheme;

قسمتعریف ساخت
{
    ساخت wl_list link;
    حرف wl_output_name[];
} SDL_WaylandConnectorName;

ساخت SDL_Video_ڈیٹا
{
    ساخت wl_display *display;
    ساخت wl_registry *registry;
    ساخت wl_compositor *compositor;
    ساخت wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    صحیح عدد_cursor_themes;
    ساخت
    {
        ساخت xdg_wm_بنیاد *xdg;
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
        ساخت libdecor *libdecor;
#اگر_ختم
    } shell;
    ساخت wl_subcompositor *subcompositor;
    ساخت zwp_relative_اشارہ_گر_manager_v1 *relative_اشارہ_گر_manager;
    ساخت zwp_اشارہ_گر_constraints_v1 *اشارہ_گر_constraints;
    ساخت wp_اشارہ_گر_warp_v1 *wp_اشارہ_گر_warp_v1;
    ساخت wp_cursor_shape_manager_v1 *cursor_shape_manager;
    ساخت wl_ڈیٹا_device_manager *ڈیٹا_device_manager;
    ساخت zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    ساخت zxdg_decoration_manager_v1 *decoration_manager;
    ساخت zwp_keyboard_shortcuts_inhibit_manager_v1 *کلید_inhibitor_manager;
    ساخت zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    ساخت xdg_activation_v1 *activation_manager;
    ساخت zwp_متن_داخلہ_manager_v3 *متن_داخلہ_manager;
    ساخت zxdg_output_manager_v1 *xdg_output_manager;
    ساخت wp_viewporter *viewporter;
    ساخت wp_fractional_scale_manager_v1 *fractional_scale_manager;
    ساخت zwp_داخلہ_timestamps_manager_v1 *داخلہ_timestamps_manager;
    ساخت zxdg_exporter_v2 *zxdg_exporter_v2;
    ساخت xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    ساخت wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    ساخت xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    ساخت frog_color_management_factory_v1 *frog_color_management_factory_v1;
    ساخت wp_color_manager_v1 *wp_color_manager_v1;
    ساخت zwp_tablet_manager_v2 *tablet_manager;
    ساخت wl_fixes *wl_fixes;
    ساخت zwp_اشارہ_گر_gestures_v1 *zwp_اشارہ_گر_gestures;
    ساخت wp_single_pixel_بفر_manager_v1 *single_pixel_بفر_manager;
    ساخت xdg_session_manager_v1 *xdg_session_manager;
    ساخت xdg_toplevel_لیبل_manager_v1 *xdg_toplevel_لیبل_manager;

    ساخت xdg_session_v1 *xdg_session;
    ساخت xkb_context *xkb_context;

    ساخت wl_list seat_list;
    ساخت SDL_WaylandSeat *آخری_implicit_grab_seat;
    ساخت SDL_WaylandSeat *current_ڈیٹا_offer_seat;
    ساخت SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_کام_Thread_Context *کام_thread_context;

    SDL_Display_ڈیٹا **output_list;
    صحیح output_گنتی;
    صحیح output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_مقصد_display_enabled;
};

ساخت SDL_Display_ڈیٹا
{
    SDL_Video_ڈیٹا *videodata;
    ساخت wl_output *output;
    ساخت zxdg_output_v1 *xdg_output;
    ساخت wp_color_management_output_v1 *wp_color_management_output;
    ساخت Wayland_ColorInfoState *color_info_state;
    حرف *wl_output_name;
    دوہرا scale_ضربی_عدد_2;
    صحیح integer_scale_ضربی_عدد; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    ساخت
    {
        صحیح x;
        صحیح y;
        صحیح چوڑائی;
        صحیح اونچائی;
    } logical;

    ساخت
    {
        صحیح x;
        صحیح y;
        صحیح چوڑائی;
        صحیح اونچائی;
    } pixel;

    ساخت
    {
        صحیح چوڑائی_mm;  // Physical width in millimeters.
        صحیح اونچائی_mm; // Physical height in millimeters.
    } physical;

    صحیح refresh;   // Refresh in mHz
    صحیح transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    صحیح wl_output_مکمل_گنتی;
    bool has_logical_position;
    bool has_logical_سائز;
    bool geometry_بدلا;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#شامل "SDL_waylanddyn.h"

خارجی خالی SDL_WAYLAND_رجسٹر_surface(ساخت wl_surface *surface);
خارجی خالی SDL_WAYLAND_رجسٹر_output(ساخت wl_output *output);
خارجی bool SDL_WAYLAND_own_surface(ساخت wl_surface *surface);
خارجی bool SDL_WAYLAND_own_output(ساخت wl_output *output);

خارجی SDL_کھڑکی_ڈیٹا *Wayland_Get_کھڑکی_ڈیٹا_For_Owned_Surface(ساخت wl_surface *surface);
خارجی خالی Wayland_جوڑو_کھڑکی_ڈیٹا_مقصد_External_List(SDL_کھڑکی_ڈیٹا *ڈیٹا);
خارجی خالی Wayland_Remove_کھڑکی_ڈیٹا_From_External_List(SDL_کھڑکی_ڈیٹا *ڈیٹا);
خارجی ساخت wl_event_قطار *Wayland_Display_Create_قطار(ساخت wl_display *display, ثابت حرف *name);
خارجی خالی Wayland_CreateSession(SDL_Video_ڈیٹا *ڈیٹا);

خارجی bool Wayland_بھرو_Libdecor(SDL_Video_ڈیٹا *ڈیٹا, bool ignore_xdg);

خارجی bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#اگر_ختم // SDL_waylandvideo_h_
