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

#ضمن "SDL_internal.h"

#جے_بنا_تعریف SDL_waylandvideo_h_
#تعریف_کرو SDL_waylandvideo_h_

#ضمن <EGL/egl.h>
#ضمن "wayland-util.h"

#ضمن "../SDL_sysvideo.h"
#ضمن "../../core/linux/SDL_dbus.h"
#ضمن "../../core/linux/SDL_ime.h"
#ضمن "SDL_waylandeventthread.h"

بنية xkb_context;
بنية SDL_WaylandSeat;

تعريفنوع بنية
{
    بنية wl_cursor_theme *theme;
    صحيح ناپ;
} SDL_WaylandCursorTheme;

تعريفنوع بنية
{
    بنية wl_list link;
    حرف wl_output_name[];
} SDL_WaylandConnectorName;

بنية SDL_Video_انکڑے
{
    بنية wl_display *display;
    بنية wl_registry *registry;
    بنية wl_compositor *compositor;
    بنية wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    صحيح عدد_cursor_themes;
    بنية
    {
        بنية xdg_wm_ادھار *xdg;
#جے_تعریف_شدہ HAVE_LIBDECOR_H
        بنية libdecor *libdecor;
#جے_انت
    } shell;
    بنية wl_subcompositor *subcompositor;
    بنية zwp_relative_اشارہ_گر_manager_v1 *relative_اشارہ_گر_manager;
    بنية zwp_اشارہ_گر_constraints_v1 *اشارہ_گر_constraints;
    بنية wp_اشارہ_گر_warp_v1 *wp_اشارہ_گر_warp_v1;
    بنية wp_cursor_shape_manager_v1 *cursor_shape_manager;
    بنية wl_انکڑے_device_manager *انکڑے_device_manager;
    بنية zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    بنية zxdg_decoration_manager_v1 *decoration_manager;
    بنية zwp_keyboard_shortcuts_inhibit_manager_v1 *کلید_inhibitor_manager;
    بنية zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    بنية xdg_activation_v1 *activation_manager;
    بنية zwp_متن_داخلہ_manager_v3 *متن_داخلہ_manager;
    بنية zxdg_output_manager_v1 *xdg_output_manager;
    بنية wp_viewporter *viewporter;
    بنية wp_fractional_scale_manager_v1 *fractional_scale_manager;
    بنية zwp_داخلہ_timestamps_manager_v1 *داخلہ_timestamps_manager;
    بنية zxdg_exporter_v2 *zxdg_exporter_v2;
    بنية xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    بنية wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    بنية xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    بنية frog_color_management_factory_v1 *frog_color_management_factory_v1;
    بنية wp_color_manager_v1 *wp_color_manager_v1;
    بنية zwp_tablet_manager_v2 *tablet_manager;
    بنية wl_fixes *wl_fixes;
    بنية zwp_اشارہ_گر_gestures_v1 *zwp_اشارہ_گر_gestures;
    بنية wp_single_pixel_بفر_manager_v1 *single_pixel_بفر_manager;
    بنية xdg_session_manager_v1 *xdg_session_manager;
    بنية xdg_toplevel_ٹیگ_manager_v1 *xdg_toplevel_ٹیگ_manager;

    بنية xdg_session_v1 *xdg_session;
    بنية xkb_context *xkb_context;

    بنية wl_list seat_list;
    بنية SDL_WaylandSeat *آخری_implicit_grab_seat;
    بنية SDL_WaylandSeat *current_انکڑے_offer_seat;
    بنية SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_کم_Thread_Context *کم_thread_context;

    SDL_Display_انکڑے **output_list;
    صحيح output_گنتی;
    صحيح output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_منزل_display_enabled;
};

بنية SDL_Display_انکڑے
{
    SDL_Video_انکڑے *videodata;
    بنية wl_output *output;
    بنية zxdg_output_v1 *xdg_output;
    بنية wp_color_management_output_v1 *wp_color_management_output;
    بنية Wayland_ColorInfoState *color_info_state;
    حرف *wl_output_name;
    مزدوج scale_ضارب_2;
    صحيح integer_scale_ضارب; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    بنية
    {
        صحيح x;
        صحيح y;
        صحيح چوڑائی;
        صحيح اچائی;
    } logical;

    بنية
    {
        صحيح x;
        صحيح y;
        صحيح چوڑائی;
        صحيح اچائی;
    } pixel;

    بنية
    {
        صحيح چوڑائی_mm;  // Physical width in millimeters.
        صحيح اچائی_mm; // Physical height in millimeters.
    } physical;

    صحيح refresh;   // Refresh in mHz
    صحيح transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    صحيح wl_output_پورا_گنتی;
    bool has_logical_position;
    bool has_logical_ناپ;
    bool geometry_بدلیا;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#ضمن "SDL_waylanddyn.h"

خارجي فراغ SDL_WAYLAND_رجسٹر_surface(بنية wl_surface *surface);
خارجي فراغ SDL_WAYLAND_رجسٹر_output(بنية wl_output *output);
خارجي bool SDL_WAYLAND_own_surface(بنية wl_surface *surface);
خارجي bool SDL_WAYLAND_own_output(بنية wl_output *output);

خارجي SDL_کھڑکی_انکڑے *Wayland_Get_کھڑکی_انکڑے_For_Owned_Surface(بنية wl_surface *surface);
خارجي فراغ Wayland_جوڑو_کھڑکی_انکڑے_منزل_External_List(SDL_کھڑکی_انکڑے *انکڑے);
خارجي فراغ Wayland_Remove_کھڑکی_انکڑے_From_External_List(SDL_کھڑکی_انکڑے *انکڑے);
خارجي بنية wl_event_قطار *Wayland_Display_Create_قطار(بنية wl_display *display, ثابت حرف *name);
خارجي فراغ Wayland_CreateSession(SDL_Video_انکڑے *انکڑے);

خارجي bool Wayland_لدو_Libdecor(SDL_Video_انکڑے *انکڑے, bool ignore_xdg);

خارجي bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#جے_انت // SDL_waylandvideo_h_
