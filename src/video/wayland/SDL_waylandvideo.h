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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_waylandvideo_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_waylandvideo_h_

#ಅನ್ತರ್ಭಾವ <EGL/egl.h>
#ಅನ್ತರ್ಭಾವ "wayland-util.h"

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_dbus.h"
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_ime.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandeventthread.h"

ರಚನೆ xkb_context;
ರಚನೆ SDL_WaylandSeat;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ರಚನೆ wl_cursor_theme *theme;
    ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2;
} SDL_WaylandCursorTheme;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ರಚನೆ wl_list link;
    ಅಕ್ಷರ wl_output_name[];
} SDL_WaylandConnectorName;

ರಚನೆ SDL_Video_ದತ್ತಾಂಶ
{
    ರಚನೆ wl_display *display;
    ರಚನೆ wl_registry *registry;
    ರಚನೆ wl_compositor *compositor;
    ರಚನೆ wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_cursor_themes;
    ರಚನೆ
    {
        ರಚನೆ xdg_wm_ತಳ *xdg;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
        ರಚನೆ libdecor *libdecor;
#ಆದರೆ_ಅಂತ್ಯ
    } shell;
    ರಚನೆ wl_subcompositor *subcompositor;
    ರಚನೆ zwp_relative_ಸೂಚಕ_manager_v1 *relative_ಸೂಚಕ_manager;
    ರಚನೆ zwp_ಸೂಚಕ_constraints_v1 *ಸೂಚಕ_constraints;
    ರಚನೆ wp_ಸೂಚಕ_warp_v1 *wp_ಸೂಚಕ_warp_v1;
    ರಚನೆ wp_cursor_shape_manager_v1 *cursor_shape_manager;
    ರಚನೆ wl_ದತ್ತಾಂಶ_device_manager *ದತ್ತಾಂಶ_device_manager;
    ರಚನೆ zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    ರಚನೆ zxdg_decoration_manager_v1 *decoration_manager;
    ರಚನೆ zwp_keyboard_shortcuts_inhibit_manager_v1 *ಕೀಲಿ_inhibitor_manager;
    ರಚನೆ zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    ರಚನೆ xdg_activation_v1 *activation_manager;
    ರಚನೆ zwp_ಪಠ್ಯ_ಒಳಹರಿವು_manager_v3 *ಪಠ್ಯ_ಒಳಹರಿವು_manager;
    ರಚನೆ zxdg_output_manager_v1 *xdg_output_manager;
    ರಚನೆ wp_viewporter *viewporter;
    ರಚನೆ wp_fractional_scale_manager_v1 *fractional_scale_manager;
    ರಚನೆ zwp_ಒಳಹರಿವು_timestamps_manager_v1 *ಒಳಹರಿವು_timestamps_manager;
    ರಚನೆ zxdg_exporter_v2 *zxdg_exporter_v2;
    ರಚನೆ xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    ರಚನೆ wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    ರಚನೆ xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    ರಚನೆ frog_color_management_factory_v1 *frog_color_management_factory_v1;
    ರಚನೆ wp_color_manager_v1 *wp_color_manager_v1;
    ರಚನೆ zwp_tablet_manager_v2 *tablet_manager;
    ರಚನೆ wl_fixes *wl_fixes;
    ರಚನೆ zwp_ಸೂಚಕ_gestures_v1 *zwp_ಸೂಚಕ_gestures;
    ರಚನೆ wp_single_pixel_ಬಫರ್_manager_v1 *single_pixel_ಬಫರ್_manager;
    ರಚನೆ xdg_session_manager_v1 *xdg_session_manager;
    ರಚನೆ xdg_toplevel_ಟ್ಯಾಗ್_manager_v1 *xdg_toplevel_ಟ್ಯಾಗ್_manager;

    ರಚನೆ xdg_session_v1 *xdg_session;
    ರಚನೆ xkb_context *xkb_context;

    ರಚನೆ wl_list seat_list;
    ರಚನೆ SDL_WaylandSeat *ಕೊನೆಯ_implicit_grab_seat;
    ರಚನೆ SDL_WaylandSeat *current_ದತ್ತಾಂಶ_offer_seat;
    ರಚನೆ SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_ಕೆಲಸ_Thread_Context *ಕೆಲಸ_thread_context;

    SDL_Display_ದತ್ತಾಂಶ **output_list;
    ಪೂರ್ಣಾಂಕ output_ಎಣಿಕೆ;
    ಪೂರ್ಣಾಂಕ output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_ಗಮ್ಯ_display_enabled;
};

ರಚನೆ SDL_Display_ದತ್ತಾಂಶ
{
    SDL_Video_ದತ್ತಾಂಶ *videodata;
    ರಚನೆ wl_output *output;
    ರಚನೆ zxdg_output_v1 *xdg_output;
    ರಚನೆ wp_color_management_output_v1 *wp_color_management_output;
    ರಚನೆ Wayland_ColorInfoState *color_info_state;
    ಅಕ್ಷರ *wl_output_name;
    ದ್ವಿಗುಣ scale_ಗುಣಕ_2;
    ಪೂರ್ಣಾಂಕ integer_scale_ಗುಣಕ; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    ರಚನೆ
    {
        ಪೂರ್ಣಾಂಕ x;
        ಪೂರ್ಣಾಂಕ y;
        ಪೂರ್ಣಾಂಕ ಅಗಲ;
        ಪೂರ್ಣಾಂಕ ಎತ್ತರ;
    } logical;

    ರಚನೆ
    {
        ಪೂರ್ಣಾಂಕ x;
        ಪೂರ್ಣಾಂಕ y;
        ಪೂರ್ಣಾಂಕ ಅಗಲ;
        ಪೂರ್ಣಾಂಕ ಎತ್ತರ;
    } pixel;

    ರಚನೆ
    {
        ಪೂರ್ಣಾಂಕ ಅಗಲ_mm;  // Physical width in millimeters.
        ಪೂರ್ಣಾಂಕ ಎತ್ತರ_mm; // Physical height in millimeters.
    } physical;

    ಪೂರ್ಣಾಂಕ refresh;   // Refresh in mHz
    ಪೂರ್ಣಾಂಕ transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    ಪೂರ್ಣಾಂಕ wl_output_ಮುಗಿದ_ಎಣಿಕೆ;
    bool has_logical_position;
    bool has_logical_ಗಾತ್ರ;
    bool geometry_ಬದಲಾಯಿತು;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#ಅನ್ತರ್ಭಾವ "SDL_waylanddyn.h"

ಬಾಹ್ಯ ಶೂನ್ಯ SDL_WAYLAND_ರಿಜಿಸ್ಟರ್_surface(ರಚನೆ wl_surface *surface);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_WAYLAND_ರಿಜಿಸ್ಟರ್_output(ರಚನೆ wl_output *output);
ಬಾಹ್ಯ bool SDL_WAYLAND_own_surface(ರಚನೆ wl_surface *surface);
ಬಾಹ್ಯ bool SDL_WAYLAND_own_output(ರಚನೆ wl_output *output);

ಬಾಹ್ಯ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *Wayland_Get_ಕಿಟಕಿ_ದತ್ತಾಂಶ_For_Owned_Surface(ರಚನೆ wl_surface *surface);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ಕೂಡಿಸು_ಕಿಟಕಿ_ದತ್ತಾಂಶ_ಗಮ್ಯ_External_List(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Remove_ಕಿಟಕಿ_ದತ್ತಾಂಶ_From_External_List(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ);
ಬಾಹ್ಯ ರಚನೆ wl_event_ಸರತಿ *Wayland_Display_Create_ಸರತಿ(ರಚನೆ wl_display *display, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_CreateSession(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ);

ಬಾಹ್ಯ bool Wayland_ತುಂಬು_Libdecor(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, bool ignore_xdg);

ಬಾಹ್ಯ bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#ಆದರೆ_ಅಂತ್ಯ // SDL_waylandvideo_h_
