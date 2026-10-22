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

#अन्तर्भाव "SDL_internal.h"

#यदि_अपरिभाषितम् SDL_waylandvideo_h_
#परिभाषय SDL_waylandvideo_h_

#अन्तर्भाव <EGL/egl.h>
#अन्तर्भाव "wayland-util.h"

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../core/linux/SDL_dbus.h"
#अन्तर्भाव "../../core/linux/SDL_ime.h"
#अन्तर्भाव "SDL_waylandeventthread.h"

संरचना xkb_context;
संरचना SDL_WaylandSeat;

प्रकारनिर्देश संरचना
{
    संरचना wl_cursor_theme *theme;
    पूर्णाङ्क आकार;
} SDL_WaylandCursorTheme;

प्रकारनिर्देश संरचना
{
    संरचना wl_list link;
    वर्ण wl_output_name[];
} SDL_WaylandConnectorName;

संरचना SDL_Video_दत्त
{
    संरचना wl_display *display;
    संरचना wl_registry *registry;
    संरचना wl_compositor *compositor;
    संरचना wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    पूर्णाङ्क अङ्कः_cursor_themes;
    संरचना
    {
        संरचना xdg_wm_आधारः *xdg;
#यदि_परिभाषितम् HAVE_LIBDECOR_H
        संरचना libdecor *libdecor;
#यदि_अन्तः
    } shell;
    संरचना wl_subcompositor *subcompositor;
    संरचना zwp_relative_pointer_manager_v1 *relative_pointer_manager;
    संरचना zwp_pointer_constraints_v1 *pointer_constraints;
    संरचना wp_pointer_warp_v1 *wp_pointer_warp_v1;
    संरचना wp_cursor_shape_manager_v1 *cursor_shape_manager;
    संरचना wl_दत्त_device_manager *दत्त_device_manager;
    संरचना zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    संरचना zxdg_decoration_manager_v1 *decoration_manager;
    संरचना zwp_keyboard_shortcuts_inhibit_manager_v1 *कुञ्चिका_inhibitor_manager;
    संरचना zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    संरचना xdg_activation_v1 *activation_manager;
    संरचना zwp_text_निवेशः_manager_v3 *text_निवेशः_manager;
    संरचना zxdg_output_manager_v1 *xdg_output_manager;
    संरचना wp_viewporter *viewporter;
    संरचना wp_fractional_scale_manager_v1 *fractional_scale_manager;
    संरचना zwp_निवेशः_timestamps_manager_v1 *निवेशः_timestamps_manager;
    संरचना zxdg_exporter_v2 *zxdg_exporter_v2;
    संरचना xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    संरचना wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    संरचना xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    संरचना frog_color_management_factory_v1 *frog_color_management_factory_v1;
    संरचना wp_color_manager_v1 *wp_color_manager_v1;
    संरचना zwp_tablet_manager_v2 *tablet_manager;
    संरचना wl_fixes *wl_fixes;
    संरचना zwp_pointer_gestures_v1 *zwp_pointer_gestures;
    संरचना wp_single_pixel_बफर_manager_v1 *single_pixel_बफर_manager;
    संरचना xdg_session_manager_v1 *xdg_session_manager;
    संरचना xdg_toplevel_चिह्नकम्_manager_v1 *xdg_toplevel_चिह्नकम्_manager;

    संरचना xdg_session_v1 *xdg_session;
    संरचना xkb_context *xkb_context;

    संरचना wl_list seat_list;
    संरचना SDL_WaylandSeat *चरमः_implicit_grab_seat;
    संरचना SDL_WaylandSeat *current_दत्त_offer_seat;
    संरचना SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_JobThreadContext *job_thread_context;

    SDL_Display_दत्त **output_list;
    पूर्णाङ्क output_गणनम्;
    पूर्णाङ्क output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_गन्तव्यम्_display_enabled;
};

संरचना SDL_Display_दत्त
{
    SDL_Video_दत्त *videodata;
    संरचना wl_output *output;
    संरचना zxdg_output_v1 *xdg_output;
    संरचना wp_color_management_output_v1 *wp_color_management_output;
    संरचना Wayland_ColorInfoState *color_info_state;
    वर्ण *wl_output_name;
    द्विगुण scale_गुणकः_2;
    पूर्णाङ्क integer_scale_गुणकः; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    संरचना
    {
        पूर्णाङ्क x;
        पूर्णाङ्क y;
        पूर्णाङ्क विस्तारः;
        पूर्णाङ्क height;
    } logical;

    संरचना
    {
        पूर्णाङ्क x;
        पूर्णाङ्क y;
        पूर्णाङ्क विस्तारः;
        पूर्णाङ्क height;
    } pixel;

    संरचना
    {
        पूर्णाङ्क विस्तारः_mm;  // Physical width in millimeters.
        पूर्णाङ्क height_mm; // Physical height in millimeters.
    } physical;

    पूर्णाङ्क refresh;   // Refresh in mHz
    पूर्णाङ्क transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    पूर्णाङ्क wl_output_समाप्तम्_गणनम्;
    bool has_logical_position;
    bool has_logical_आकार;
    bool geometry_परिवर्तितम्;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#अन्तर्भाव "SDL_waylanddyn.h"

बाह्य शून्य SDL_WAYLAND_पञ्जिकाकोशः_surface(संरचना wl_surface *surface);
बाह्य शून्य SDL_WAYLAND_पञ्जिकाकोशः_output(संरचना wl_output *output);
बाह्य bool SDL_WAYLAND_own_surface(संरचना wl_surface *surface);
बाह्य bool SDL_WAYLAND_own_output(संरचना wl_output *output);

बाह्य SDL_गवाक्षः_दत्त *Wayland_Get_गवाक्षः_दत्त_For_Owned_Surface(संरचना wl_surface *surface);
बाह्य शून्य Wayland_सङ्कलय_गवाक्षः_दत्त_गन्तव्यम्_External_List(SDL_गवाक्षः_दत्त *दत्त);
बाह्य शून्य Wayland_Remove_गवाक्षः_दत्त_From_External_List(SDL_गवाक्षः_दत्त *दत्त);
बाह्य संरचना wl_event_queue *Wayland_DisplayCreateQueue(संरचना wl_display *display, ध्रुव वर्ण *name);
बाह्य शून्य Wayland_CreateSession(SDL_Video_दत्त *दत्त);

बाह्य bool Wayland_आरोपय_Libdecor(SDL_Video_दत्त *दत्त, bool ignore_xdg);

बाह्य bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#यदि_अन्तः // SDL_waylandvideo_h_
