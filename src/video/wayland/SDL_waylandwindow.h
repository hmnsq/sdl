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

#నిర్వచితం_కాకపోతే SDL_waylandwindow_h_
#నిర్వచించు SDL_waylandwindow_h_

#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_touch_c.h"

#అన్తర్భావ "SDL_waylandvideo.h"
#అన్తర్భావ "SDL_waylandshmbuffer.h"

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    SDL_కిటికీ *sdlwindow;
    SDL_Video_దత్తాంశం *wayland_దత్తాంశం;
    నిర్మాణం wl_surface *surface;
    నిర్మాణం wl_callback *gles_మార్పిడి_చట్రం_callback;
    నిర్మాణం wl_event_వరుస *gles_మార్పిడి_చట్రం_event_వరుస;
    నిర్మాణం wl_surface *gles_మార్పిడి_చట్రం_surface_wrapper;
    నిర్మాణం wl_callback *surface_చట్రం_callback;

    సంఘం
    {
#నిర్వచితమైతే HAVE_LIBDECOR_H
        నిర్మాణం
        {
            నిర్మాణం libdecor_చట్రం *చట్రం;
        } libdecor;
#అయితే_ముగింపు
        నిర్మాణం
        {
            నిర్మాణం xdg_surface *surface;
            సంఘం
            {
                నిర్మాణం
                {
                    నిర్మాణం xdg_toplevel *xdg_toplevel;
                } toplevel;
                నిర్మాణం
                {
                    నిర్మాణం xdg_popup *xdg_popup;
                    నిర్మాణం xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    గణన
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    గణన
    {
        WAYLAND_SHELL_SURFACE_స్థితి_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_స్థితి_నిరీక్షణ_FOR_చట్రం,
        WAYLAND_SHELL_SURFACE_స్థితి_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_స్థితి_SHOWN
    } shell_surface_స్థితి;
    గణన
    {
        WAYLAND_WM_CAPS_కిటికీ_MENU = 0x01,
        WAYLAND_WM_CAPS_MAXIMIZE = 0x02,
        WAYLAND_WM_CAPS_FULLSCREEN = 0x04,
        WAYLAND_WM_CAPS_MINIMIZE = 0x08,

        WAYLAND_WM_CAPS_ALL = WAYLAND_WM_CAPS_కిటికీ_MENU |
                              WAYLAND_WM_CAPS_MAXIMIZE |
                              WAYLAND_WM_CAPS_FULLSCREEN |
                              WAYLAND_WM_CAPS_MINIMIZE
    } wm_caps;
    గణన
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_ఎడమ = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_కుడి = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_శిఖరం = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    గణన
    {
        WAYLAND_RESIZE_అంచు_LR = 0x01,
        WAYLAND_RESIZE_అంచు_TB = 0x02,
        WAYLAND_RESIZE_అంచు_మూల = WAYLAND_RESIZE_అంచు_LR | WAYLAND_RESIZE_అంచు_TB,
    } resize_అంచు;

    నిర్మాణం wl_egl_కిటికీ *egl_కిటికీ;
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#అయితే_ముగింపు
    నిర్మాణం zxdg_toplevel_decoration_v1 *server_decoration;
    నిర్మాణం zwp_idle_inhibitor_v1 *idle_inhibitor;
    నిర్మాణం xdg_activation_token_v1 *activation_token;
    నిర్మాణం wp_viewport *viewport;
    నిర్మాణం wp_fractional_scale_v1 *fractional_scale;
    నిర్మాణం zxdg_exported_v2 *exported;
    నిర్మాణం xdg_dialog_v1 *xdg_dialog_v1;
    నిర్మాణం wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    నిర్మాణం xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    నిర్మాణం frog_color_managed_surface *frog_color_managed_surface;
    నిర్మాణం wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    నిర్మాణం xdg_toplevel_session_v1 *xdg_toplevel_session;

    నిర్మాణం Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt మార్పిడి_interval_ready;

    SDL_Display_దత్తాంశం **outputs;
    పూర్ణాంకం అంకె_outputs;

    అక్షరం *app_id;
    అక్షరం *session_id;
    ద్విగుణ scale_గుణకం_2;

    నిర్మాణం wl_బఫరు **icon_buffers;
    పూర్ణాంకం icon_బఫరు_లెక్క;

    // Keyboard, pointer, and touch focus refcount.
    పూర్ణాంకం keyboard_focus_లెక్క;
    పూర్ణాంకం సూచిక_focus_లెక్క;
    పూర్ణాంకం చురుకైన_touch_లెక్క;

    నిర్మాణం
    {
        ద్విగుణ x;
        ద్విగుణ y;
    } సూచిక_scale;

    // The in-flight window size request.
    నిర్మాణం
    {
        // The requested logical window size.
        పూర్ణాంకం logical_వెడల్పు;
        పూర్ణాంకం logical_ఎత్తు;

        // The size of the window in pixels, when using screen space scaling.
        పూర్ణాంకం pixel_వెడల్పు;
        పూర్ణాంకం pixel_ఎత్తు;
    } requested;

    // The current size of the window and drawable backing store.
    నిర్మాణం
    {
        // The size of the underlying window.
        పూర్ణాంకం logical_వెడల్పు;
        పూర్ణాంకం logical_ఎత్తు;

        // The size of the window backbuffer in pixels.
        పూర్ణాంకం pixel_వెడల్పు;
        పూర్ణాంకం pixel_ఎత్తు;

        // The dimensions of the active viewport, in logical units.
        పూర్ణాంకం viewport_వెడల్పు;
        పూర్ణాంకం viewport_ఎత్తు;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    నిర్మాణం
    {
        పూర్ణాంకం వెడల్పు;
        పూర్ణాంకం ఎత్తు;
        bool insets_apply;
    } చివరి_configure;

    // System enforced window size limits.
    నిర్మాణం
    {
        // Minimum allowed logical window size.
        పూర్ణాంకం min_వెడల్పు_2;
        పూర్ణాంకం min_ఎత్తు_2;
    } system_limits;

    నిర్మాణం
    {
        పూర్ణాంకం వెడల్పు;
        పూర్ణాంకం ఎత్తు;
    } toplevel_bounds;

    నిర్మాణం
    {
        నిర్మాణం wl_surface *surface;
        నిర్మాణం wl_subsurface *subsurface;
        నిర్మాణం wl_బఫరు *బఫరు_2;
        నిర్మాణం wp_viewport *viewport;

        పూర్ణాంకం స్థానభ్రంశం_x;
        పూర్ణాంకం స్థానభ్రంశం_y;

        bool mapped;
        bool opaque;
    } ముసుగు;

    నిర్మాణం
    {
        పూర్ణాంకం hint;
        పూర్ణాంకం purpose;
        bool చురుకైన;
    } పాఠ్యం_ఆదానం_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID చివరి_display_ID;
    పూర్ణాంకం pending_state_deadline_లెక్క;
    Uint64 చివరి_focus_event_సమయం_ns;
    Uint64 చివరి_resize_event_సమయం_ns;
    పూర్ణాంకం icc_fd;
    Uint32 icc_కొలత;
    bool floating;
    bool suspended;
    bool resizing;
    bool చురుకైన;
    bool pending_config_ack;
    bool pending_state_commit;
    bool limits_మారింది;
    bool is_fullscreen;
    bool fullscreen_exclusive;
    bool drop_fullscreen_అభ్యర్థనలు;
    bool showing_కిటికీ;
    bool fullscreen_was_positioned;
    bool show_hide_sync_required;
    bool scale_గమ్యం_display;
    bool reparenting_required;
    bool double_బఫరు;
    bool స్వీకరించు_drag_and_drop;
    bool enable_insets;

    SDL_తగిలింది_Test_ఫలితం తగిలింది_test_ఫలితం;

    నిర్మాణం wl_list external_కిటికీ_list_link;
};

బాహ్య శూన్య Wayland_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Wayland_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Wayland_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య SDL_Fullscreen_ఫలితం Wayland_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
బాహ్య శూన్య Wayland_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Wayland_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Wayland_సమితి_కిటికీ_Mouse_Rect(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Wayland_సమితి_కిటికీ_Mouse_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed);
బాహ్య bool Wayland_సమితి_కిటికీ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed);
బాహ్య శూన్య Wayland_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Wayland_సమితి_కిటికీ_Bordered(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool bordered);
బాహ్య శూన్య Wayland_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable);
బాహ్య bool Wayland_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య bool Wayland_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Wayland_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Wayland_సమితి_కిటికీ_Aspect_నిష్పత్తి(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Wayland_సమితి_కిటికీ_Minimum_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Wayland_సమితి_కిటికీ_గరిష్ఠ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Wayland_Get_కిటికీ_కొలత_లోపల_Pixels(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *w, పూర్ణాంకం *h);
బాహ్య SDL_DisplayID Wayland_Get_Display_For_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Wayland_సమితి_కిటికీ_మాతృ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ *మాతృ_కిటికీ);
బాహ్య bool Wayland_సమితి_కిటికీ_Modal(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool modal);
బాహ్య bool Wayland_సమితి_కిటికీ_Opacity(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, దశాంశం opacity);
బాహ్య శూన్య Wayland_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Wayland_Show_కిటికీ_System_Menu(SDL_కిటికీ *కిటికీ, పూర్ణాంకం x, పూర్ణాంకం y);
బాహ్య శూన్య Wayland_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
బాహ్య bool Wayland_సమితి_కిటికీ_Icon(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *icon);
బాహ్య bool Wayland_సమితి_కిటికీ_Focusable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool focusable);
బాహ్య దశాంశం Wayland_Get_కిటికీ_Content_Scale(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య *Wayland_Get_కిటికీ_ICCProfile(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, size_t *కొలత);
బాహ్య శూన్య Wayland_AcceptDragAndDrop(SDL_కిటికీ *కిటికీ, bool accept);

బాహ్య bool Wayland_సమితి_కిటికీ_తగిలింది_Test(SDL_కిటికీ *కిటికీ, bool enabled);
బాహ్య bool Wayland_Flash_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_FlashOperation operation);
బాహ్య bool Wayland_Sync_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Wayland_Reconfigure_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ_Flags flags);

బాహ్య శూన్య Wayland_Remove_Output_From_కిటికీ(SDL_కిటికీ_దత్తాంశం *కిటికీ, SDL_Display_దత్తాంశం *display_దత్తాంశం);
బాహ్య శూన్య Wayland_Update_కిటికీ_Position(SDL_కిటికీ *కిటికీ);

#అయితే_ముగింపు // SDL_waylandwindow_h_
