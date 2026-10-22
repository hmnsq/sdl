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

#که_نه_تعریف_شوی SDL_waylandvideo_h_
#تعریف_کړه SDL_waylandvideo_h_

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
    صحيح اندازه;
} SDL_WaylandCursorTheme;

تعريفنوع بنية
{
    بنية wl_list link;
    حرف wl_output_name[];
} SDL_WaylandConnectorName;

بنية SDL_Video_معلومات
{
    بنية wl_display *display;
    بنية wl_registry *registry;
    بنية wl_compositor *compositor;
    بنية wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    صحيح عدد_cursor_themes;
    بنية
    {
        بنية xdg_wm_بنسټ *xdg;
#که_تعریف_شوی HAVE_LIBDECOR_H
        بنية libdecor *libdecor;
#د_که_پای
    } shell;
    بنية wl_subcompositor *subcompositor;
    بنية zwp_relative_اشاره_ګر_manager_v1 *relative_اشاره_ګر_manager;
    بنية zwp_اشاره_ګر_constraints_v1 *اشاره_ګر_constraints;
    بنية wp_اشاره_ګر_warp_v1 *wp_اشاره_ګر_warp_v1;
    بنية wp_cursor_shape_manager_v1 *cursor_shape_manager;
    بنية wl_معلومات_device_manager *معلومات_device_manager;
    بنية zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    بنية zxdg_decoration_manager_v1 *decoration_manager;
    بنية zwp_keyboard_shortcuts_inhibit_manager_v1 *کلی_inhibitor_manager;
    بنية zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    بنية xdg_activation_v1 *activation_manager;
    بنية zwp_متن_ننوت_manager_v3 *متن_ننوت_manager;
    بنية zxdg_output_manager_v1 *xdg_output_manager;
    بنية wp_viewporter *viewporter;
    بنية wp_fractional_scale_manager_v1 *fractional_scale_manager;
    بنية zwp_ننوت_timestamps_manager_v1 *ننوت_timestamps_manager;
    بنية zxdg_exporter_v2 *zxdg_exporter_v2;
    بنية xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    بنية wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    بنية xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    بنية frog_color_management_factory_v1 *frog_color_management_factory_v1;
    بنية wp_color_manager_v1 *wp_color_manager_v1;
    بنية zwp_tablet_manager_v2 *tablet_manager;
    بنية wl_fixes *wl_fixes;
    بنية zwp_اشاره_ګر_gestures_v1 *zwp_اشاره_ګر_gestures;
    بنية wp_single_pixel_بفر_manager_v1 *single_pixel_بفر_manager;
    بنية xdg_session_manager_v1 *xdg_session_manager;
    بنية xdg_toplevel_نښان_manager_v1 *xdg_toplevel_نښان_manager;

    بنية xdg_session_v1 *xdg_session;
    بنية xkb_context *xkb_context;

    بنية wl_list seat_list;
    بنية SDL_WaylandSeat *وروستی_implicit_grab_seat;
    بنية SDL_WaylandSeat *current_معلومات_offer_seat;
    بنية SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_دنده_Thread_Context *دنده_thread_context;

    SDL_Display_معلومات **output_list;
    صحيح output_شمېر;
    صحيح output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_منزل_display_enabled;
};

بنية SDL_Display_معلومات
{
    SDL_Video_معلومات *videodata;
    بنية wl_output *output;
    بنية zxdg_output_v1 *xdg_output;
    بنية wp_color_management_output_v1 *wp_color_management_output;
    بنية Wayland_ColorInfoState *color_info_state;
    حرف *wl_output_name;
    مزدوج scale_ضریب_2;
    صحيح integer_scale_ضریب; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    بنية
    {
        صحيح x;
        صحيح y;
        صحيح پلنوالی;
        صحيح لوړوالی;
    } logical;

    بنية
    {
        صحيح x;
        صحيح y;
        صحيح پلنوالی;
        صحيح لوړوالی;
    } pixel;

    بنية
    {
        صحيح پلنوالی_mm;  // Physical width in millimeters.
        صحيح لوړوالی_mm; // Physical height in millimeters.
    } physical;

    صحيح refresh;   // Refresh in mHz
    صحيح transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    صحيح wl_output_بشپړ_شمېر;
    bool has_logical_position;
    bool has_logical_اندازه;
    bool geometry_بدل_شوی;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#ضمن "SDL_waylanddyn.h"

خارجي فراغ SDL_WAYLAND_ثبتوونکی_surface(بنية wl_surface *surface);
خارجي فراغ SDL_WAYLAND_ثبتوونکی_output(بنية wl_output *output);
خارجي bool SDL_WAYLAND_own_surface(بنية wl_surface *surface);
خارجي bool SDL_WAYLAND_own_output(بنية wl_output *output);

خارجي SDL_کړکۍ_معلومات *Wayland_Get_کړکۍ_معلومات_For_Owned_Surface(بنية wl_surface *surface);
خارجي فراغ Wayland_جمع_کړه_کړکۍ_معلومات_منزل_External_List(SDL_کړکۍ_معلومات *معلومات);
خارجي فراغ Wayland_Remove_کړکۍ_معلومات_From_External_List(SDL_کړکۍ_معلومات *معلومات);
خارجي بنية wl_event_کتار *Wayland_Display_Create_کتار(بنية wl_display *display, ثابت حرف *name);
خارجي فراغ Wayland_CreateSession(SDL_Video_معلومات *معلومات);

خارجي bool Wayland_بارول_Libdecor(SDL_Video_معلومات *معلومات, bool ignore_xdg);

خارجي bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#د_که_پای // SDL_waylandvideo_h_
