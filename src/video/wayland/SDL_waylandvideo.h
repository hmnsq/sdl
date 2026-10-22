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

#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_waylandvideo_h_
#घोषणा SDL_waylandvideo_h_

#समावेश <EGL/egl.h>
#समावेश "wayland-util.h"

#समावेश "../SDL_sysvideo.h"
#समावेश "../../core/linux/SDL_dbus.h"
#समावेश "../../core/linux/SDL_ime.h"
#समावेश "SDL_waylandeventthread.h"

काष्ठा xkb_context;
काष्ठा SDL_WaylandSeat;

प्रकार काष्ठा
{
    काष्ठा wl_cursor_theme *theme;
    पूर्णांक आकार;
} SDL_WaylandCursorTheme;

प्रकार काष्ठा
{
    काष्ठा wl_list link;
    अक्षर wl_output_name[];
} SDL_WaylandConnectorName;

काष्ठा SDL_Video_तथ्य
{
    काष्ठा wl_display *display;
    काष्ठा wl_registry *registry;
    काष्ठा wl_compositor *compositor;
    काष्ठा wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    पूर्णांक अंक_cursor_themes;
    काष्ठा
    {
        काष्ठा xdg_wm_base *xdg;
#अगर_घोषित HAVE_LIBDECOR_H
        काष्ठा libdecor *libdecor;
#पूर्ण_अगर
    } shell;
    काष्ठा wl_subcompositor *subcompositor;
    काष्ठा zwp_relative_pointer_manager_v1 *relative_pointer_manager;
    काष्ठा zwp_pointer_constraints_v1 *pointer_constraints;
    काष्ठा wp_pointer_warp_v1 *wp_pointer_warp_v1;
    काष्ठा wp_cursor_shape_manager_v1 *cursor_shape_manager;
    काष्ठा wl_तथ्य_device_manager *तथ्य_device_manager;
    काष्ठा zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    काष्ठा zxdg_decoration_manager_v1 *decoration_manager;
    काष्ठा zwp_keyboard_shortcuts_inhibit_manager_v1 *कुंजी_inhibitor_manager;
    काष्ठा zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    काष्ठा xdg_activation_v1 *activation_manager;
    काष्ठा zwp_text_निवेश_manager_v3 *text_निवेश_manager;
    काष्ठा zxdg_output_manager_v1 *xdg_output_manager;
    काष्ठा wp_viewporter *viewporter;
    काष्ठा wp_fractional_scale_manager_v1 *fractional_scale_manager;
    काष्ठा zwp_निवेश_timestamps_manager_v1 *निवेश_timestamps_manager;
    काष्ठा zxdg_exporter_v2 *zxdg_exporter_v2;
    काष्ठा xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    काष्ठा wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    काष्ठा xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    काष्ठा frog_color_management_factory_v1 *frog_color_management_factory_v1;
    काष्ठा wp_color_manager_v1 *wp_color_manager_v1;
    काष्ठा zwp_tablet_manager_v2 *tablet_manager;
    काष्ठा wl_fixes *wl_fixes;
    काष्ठा zwp_pointer_gestures_v1 *zwp_pointer_gestures;
    काष्ठा wp_single_pixel_बफर_manager_v1 *single_pixel_बफर_manager;
    काष्ठा xdg_session_manager_v1 *xdg_session_manager;
    काष्ठा xdg_toplevel_tag_manager_v1 *xdg_toplevel_tag_manager;

    काष्ठा xdg_session_v1 *xdg_session;
    काष्ठा xkb_context *xkb_context;

    काष्ठा wl_list seat_list;
    काष्ठा SDL_WaylandSeat *last_implicit_grab_seat;
    काष्ठा SDL_WaylandSeat *current_तथ्य_offer_seat;
    काष्ठा SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_JobThreadContext *job_thread_context;

    SDL_Display_तथ्य **output_list;
    पूर्णांक output_गिनती;
    पूर्णांक output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_to_display_enabled;
};

काष्ठा SDL_Display_तथ्य
{
    SDL_Video_तथ्य *videodata;
    काष्ठा wl_output *output;
    काष्ठा zxdg_output_v1 *xdg_output;
    काष्ठा wp_color_management_output_v1 *wp_color_management_output;
    काष्ठा Wayland_ColorInfoState *color_info_state;
    अक्षर *wl_output_name;
    द्विगुन scale_factor;
    पूर्णांक integer_scale_factor; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    काष्ठा
    {
        पूर्णांक x;
        पूर्णांक y;
        पूर्णांक width;
        पूर्णांक height;
    } logical;

    काष्ठा
    {
        पूर्णांक x;
        पूर्णांक y;
        पूर्णांक width;
        पूर्णांक height;
    } pixel;

    काष्ठा
    {
        पूर्णांक width_mm;  // Physical width in millimeters.
        पूर्णांक height_mm; // Physical height in millimeters.
    } physical;

    पूर्णांक refresh;   // Refresh in mHz
    पूर्णांक transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    पूर्णांक wl_output_done_गिनती;
    bool has_logical_position;
    bool has_logical_आकार;
    bool geometry_changed;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#समावेश "SDL_waylanddyn.h"

बाह्य व्योम SDL_WAYLAND_register_surface(काष्ठा wl_surface *surface);
बाह्य व्योम SDL_WAYLAND_register_output(काष्ठा wl_output *output);
बाह्य bool SDL_WAYLAND_own_surface(काष्ठा wl_surface *surface);
बाह्य bool SDL_WAYLAND_own_output(काष्ठा wl_output *output);

बाह्य SDL_Window_तथ्य *Wayland_Get_Window_तथ्य_For_Owned_Surface(काष्ठा wl_surface *surface);
बाह्य व्योम Wayland_Add_Window_तथ्य_To_External_List(SDL_Window_तथ्य *तथ्य);
बाह्य व्योम Wayland_Remove_Window_तथ्य_From_External_List(SDL_Window_तथ्य *तथ्य);
बाह्य काष्ठा wl_event_queue *Wayland_DisplayCreateQueue(काष्ठा wl_display *display, स्थिर अक्षर *name);
बाह्य व्योम Wayland_CreateSession(SDL_Video_तथ्य *तथ्य);

बाह्य bool Wayland_LoadLibdecor(SDL_Video_तथ्य *तथ्य, bool ignore_xdg);

बाह्य bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#पूर्ण_अगर // SDL_waylandvideo_h_
