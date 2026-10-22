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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_waylandvideo_h_
#నిర్వచించు SDL_waylandvideo_h_

#అన్తర్భావ <EGL/egl.h>
#అన్తర్భావ "wayland-util.h"

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../core/linux/SDL_dbus.h"
#అన్తర్భావ "../../core/linux/SDL_ime.h"
#అన్తర్భావ "SDL_waylandeventthread.h"

నిర్మాణం xkb_context;
నిర్మాణం SDL_WaylandSeat;

రకనిర్వచనం నిర్మాణం
{
    నిర్మాణం wl_cursor_theme *theme;
    పూర్ణాంకం కొలత;
} SDL_WaylandCursorTheme;

రకనిర్వచనం నిర్మాణం
{
    నిర్మాణం wl_list link;
    అక్షరం wl_output_name[];
} SDL_WaylandConnectorName;

నిర్మాణం SDL_Video_దత్తాంశం
{
    నిర్మాణం wl_display *display;
    నిర్మాణం wl_registry *registry;
    నిర్మాణం wl_compositor *compositor;
    నిర్మాణం wl_shm *shm;
    SDL_WaylandCursorTheme *cursor_themes;
    పూర్ణాంకం అంకె_cursor_themes;
    నిర్మాణం
    {
        నిర్మాణం xdg_wm_పునాది *xdg;
#నిర్వచితమైతే HAVE_LIBDECOR_H
        నిర్మాణం libdecor *libdecor;
#అయితే_ముగింపు
    } shell;
    నిర్మాణం wl_subcompositor *subcompositor;
    నిర్మాణం zwp_relative_సూచిక_manager_v1 *relative_సూచిక_manager;
    నిర్మాణం zwp_సూచిక_constraints_v1 *సూచిక_constraints;
    నిర్మాణం wp_సూచిక_warp_v1 *wp_సూచిక_warp_v1;
    నిర్మాణం wp_cursor_shape_manager_v1 *cursor_shape_manager;
    నిర్మాణం wl_దత్తాంశం_device_manager *దత్తాంశం_device_manager;
    నిర్మాణం zwp_primary_selection_device_manager_v1 *primary_selection_device_manager;
    నిర్మాణం zxdg_decoration_manager_v1 *decoration_manager;
    నిర్మాణం zwp_keyboard_shortcuts_inhibit_manager_v1 *కీలకం_inhibitor_manager;
    నిర్మాణం zwp_idle_inhibit_manager_v1 *idle_inhibit_manager;
    నిర్మాణం xdg_activation_v1 *activation_manager;
    నిర్మాణం zwp_పాఠ్యం_ఆదానం_manager_v3 *పాఠ్యం_ఆదానం_manager;
    నిర్మాణం zxdg_output_manager_v1 *xdg_output_manager;
    నిర్మాణం wp_viewporter *viewporter;
    నిర్మాణం wp_fractional_scale_manager_v1 *fractional_scale_manager;
    నిర్మాణం zwp_ఆదానం_timestamps_manager_v1 *ఆదానం_timestamps_manager;
    నిర్మాణం zxdg_exporter_v2 *zxdg_exporter_v2;
    నిర్మాణం xdg_wm_dialog_v1 *xdg_wm_dialog_v1;
    నిర్మాణం wp_alpha_modifier_v1 *wp_alpha_modifier_v1;
    నిర్మాణం xdg_toplevel_icon_manager_v1 *xdg_toplevel_icon_manager_v1;
    నిర్మాణం frog_color_management_factory_v1 *frog_color_management_factory_v1;
    నిర్మాణం wp_color_manager_v1 *wp_color_manager_v1;
    నిర్మాణం zwp_tablet_manager_v2 *tablet_manager;
    నిర్మాణం wl_fixes *wl_fixes;
    నిర్మాణం zwp_సూచిక_gestures_v1 *zwp_సూచిక_gestures;
    నిర్మాణం wp_single_pixel_బఫరు_manager_v1 *single_pixel_బఫరు_manager;
    నిర్మాణం xdg_session_manager_v1 *xdg_session_manager;
    నిర్మాణం xdg_toplevel_ట్యాగ్_manager_v1 *xdg_toplevel_ట్యాగ్_manager;

    నిర్మాణం xdg_session_v1 *xdg_session;
    నిర్మాణం xkb_context *xkb_context;

    నిర్మాణం wl_list seat_list;
    నిర్మాణం SDL_WaylandSeat *చివరి_implicit_grab_seat;
    నిర్మాణం SDL_WaylandSeat *current_దత్తాంశం_offer_seat;
    నిర్మాణం SDL_WaylandSeat *current_primary_selection_seat;
    Wayland_EventThreadContext *event_thread_context;
    Wayland_పని_Thread_Context *పని_thread_context;

    SDL_Display_దత్తాంశం **output_list;
    పూర్ణాంకం output_లెక్క;
    పూర్ణాంకం output_max;

    bool initializing;
    bool display_disconnected;
    bool display_externally_owned;
    bool scale_గమ్యం_display_enabled;
};

నిర్మాణం SDL_Display_దత్తాంశం
{
    SDL_Video_దత్తాంశం *videodata;
    నిర్మాణం wl_output *output;
    నిర్మాణం zxdg_output_v1 *xdg_output;
    నిర్మాణం wp_color_management_output_v1 *wp_color_management_output;
    నిర్మాణం Wayland_ColorInfoState *color_info_state;
    అక్షరం *wl_output_name;
    ద్విగుణ scale_గుణకం_2;
    పూర్ణాంకం integer_scale_గుణకం; // The integer scale factor set by wl_output.
    Uint32 registry_id;

    నిర్మాణం
    {
        పూర్ణాంకం x;
        పూర్ణాంకం y;
        పూర్ణాంకం వెడల్పు;
        పూర్ణాంకం ఎత్తు;
    } logical;

    నిర్మాణం
    {
        పూర్ణాంకం x;
        పూర్ణాంకం y;
        పూర్ణాంకం వెడల్పు;
        పూర్ణాంకం ఎత్తు;
    } pixel;

    నిర్మాణం
    {
        పూర్ణాంకం వెడల్పు_mm;  // Physical width in millimeters.
        పూర్ణాంకం ఎత్తు_mm; // Physical height in millimeters.
    } physical;

    పూర్ణాంకం refresh;   // Refresh in mHz
    పూర్ణాంకం transform; // wl_output_transform enum
    SDL_DisplayOrientation orientation;

    SDL_HDROutputProperties HDR;

    SDL_DisplayID display;
    SDL_VideoDisplay placeholder;

    పూర్ణాంకం wl_output_పూర్తి_లెక్క;
    bool has_logical_position;
    bool has_logical_కొలత;
    bool geometry_మారింది;
};

// Needed here to get wl_surface declaration, fixes GitHub#4594
#అన్తర్భావ "SDL_waylanddyn.h"

బాహ్య శూన్య SDL_WAYLAND_రిజిస్టరు_surface(నిర్మాణం wl_surface *surface);
బాహ్య శూన్య SDL_WAYLAND_రిజిస్టరు_output(నిర్మాణం wl_output *output);
బాహ్య bool SDL_WAYLAND_own_surface(నిర్మాణం wl_surface *surface);
బాహ్య bool SDL_WAYLAND_own_output(నిర్మాణం wl_output *output);

బాహ్య SDL_కిటికీ_దత్తాంశం *Wayland_Get_కిటికీ_దత్తాంశం_For_Owned_Surface(నిర్మాణం wl_surface *surface);
బాహ్య శూన్య Wayland_కూడు_కిటికీ_దత్తాంశం_గమ్యం_External_List(SDL_కిటికీ_దత్తాంశం *దత్తాంశం);
బాహ్య శూన్య Wayland_Remove_కిటికీ_దత్తాంశం_From_External_List(SDL_కిటికీ_దత్తాంశం *దత్తాంశం);
బాహ్య నిర్మాణం wl_event_వరుస *Wayland_Display_Create_వరుస(నిర్మాణం wl_display *display, స్థిరరాశి అక్షరం *name);
బాహ్య శూన్య Wayland_CreateSession(SDL_Video_దత్తాంశం *దత్తాంశం);

బాహ్య bool Wayland_ఎక్కించు_Libdecor(SDL_Video_దత్తాంశం *దత్తాంశం, bool ignore_xdg);

బాహ్య bool Wayland_HandleDisplayDisconnected(SDL_VideoDevice *_this);

#అయితే_ముగింపు // SDL_waylandvideo_h_
