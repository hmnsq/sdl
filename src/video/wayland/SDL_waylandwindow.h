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

#यदि_अपरिभाषितम् SDL_waylandwindow_h_
#परिभाषय SDL_waylandwindow_h_

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"

#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "SDL_waylandshmbuffer.h"

संरचना SDL_गवाक्षः_दत्त
{
    SDL_गवाक्षः *sdlwindow;
    SDL_Video_दत्त *wayland_दत्त;
    संरचना wl_surface *surface;
    संरचना wl_callback *gles_swap_frame_callback;
    संरचना wl_event_queue *gles_swap_frame_event_queue;
    संरचना wl_surface *gles_swap_frame_surface_wrapper;
    संरचना wl_callback *surface_frame_callback;

    सङ्घ
    {
#यदि_परिभाषितम् HAVE_LIBDECOR_H
        संरचना
        {
            संरचना libdecor_frame *frame;
        } libdecor;
#यदि_अन्तः
        संरचना
        {
            संरचना xdg_surface *surface;
            सङ्घ
            {
                संरचना
                {
                    संरचना xdg_toplevel *xdg_toplevel;
                } toplevel;
                संरचना
                {
                    संरचना xdg_popup *xdg_popup;
                    संरचना xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    गणना
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    गणना
    {
        WAYLAND_SHELL_SURFACE_स्थितिः_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_स्थितिः_प्रतीक्षा_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_स्थितिः_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_स्थितिः_SHOWN
    } shell_surface_स्थितिः;
    गणना
    {
        WAYLAND_WM_CAPS_गवाक्षः_MENU = 0x01,
        WAYLAND_WM_CAPS_MAXIMIZE = 0x02,
        WAYLAND_WM_CAPS_FULLSCREEN = 0x04,
        WAYLAND_WM_CAPS_MINIMIZE = 0x08,

        WAYLAND_WM_CAPS_ALL = WAYLAND_WM_CAPS_गवाक्षः_MENU |
                              WAYLAND_WM_CAPS_MAXIMIZE |
                              WAYLAND_WM_CAPS_FULLSCREEN |
                              WAYLAND_WM_CAPS_MINIMIZE
    } wm_caps;
    गणना
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_वामः = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_दक्षिणः = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_शिखरम् = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    गणना
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    संरचना wl_egl_गवाक्षः *egl_गवाक्षः;
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#यदि_अन्तः
    संरचना zxdg_toplevel_decoration_v1 *server_decoration;
    संरचना zwp_idle_inhibitor_v1 *idle_inhibitor;
    संरचना xdg_activation_token_v1 *activation_token;
    संरचना wp_viewport *viewport;
    संरचना wp_fractional_scale_v1 *fractional_scale;
    संरचना zxdg_exported_v2 *exported;
    संरचना xdg_dialog_v1 *xdg_dialog_v1;
    संरचना wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    संरचना xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    संरचना frog_color_managed_surface *frog_color_managed_surface;
    संरचना wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    संरचना xdg_toplevel_session_v1 *xdg_toplevel_session;

    संरचना Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_Display_दत्त **outputs;
    पूर्णाङ्क अङ्कः_outputs;

    वर्ण *app_id;
    वर्ण *session_id;
    द्विगुण scale_गुणकः_2;

    संरचना wl_बफर **icon_buffers;
    पूर्णाङ्क icon_बफर_गणनम्;

    // Keyboard, pointer, and touch focus refcount.
    पूर्णाङ्क keyboard_focus_गणनम्;
    पूर्णाङ्क pointer_focus_गणनम्;
    पूर्णाङ्क सक्रिय_touch_गणनम्;

    संरचना
    {
        द्विगुण x;
        द्विगुण y;
    } pointer_scale;

    // The in-flight window size request.
    संरचना
    {
        // The requested logical window size.
        पूर्णाङ्क logical_विस्तारः;
        पूर्णाङ्क logical_height;

        // The size of the window in pixels, when using screen space scaling.
        पूर्णाङ्क pixel_विस्तारः;
        पूर्णाङ्क pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    संरचना
    {
        // The size of the underlying window.
        पूर्णाङ्क logical_विस्तारः;
        पूर्णाङ्क logical_height;

        // The size of the window backbuffer in pixels.
        पूर्णाङ्क pixel_विस्तारः;
        पूर्णाङ्क pixel_height;

        // The dimensions of the active viewport, in logical units.
        पूर्णाङ्क viewport_विस्तारः;
        पूर्णाङ्क viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    संरचना
    {
        पूर्णाङ्क विस्तारः;
        पूर्णाङ्क height;
        bool insets_apply;
    } चरमः_configure;

    // System enforced window size limits.
    संरचना
    {
        // Minimum allowed logical window size.
        पूर्णाङ्क min_विस्तारः_2;
        पूर्णाङ्क min_height;
    } system_limits;

    संरचना
    {
        पूर्णाङ्क विस्तारः;
        पूर्णाङ्क height;
    } toplevel_bounds;

    संरचना
    {
        संरचना wl_surface *surface;
        संरचना wl_subsurface *subsurface;
        संरचना wl_बफर *बफर_2;
        संरचना wp_viewport *viewport;

        पूर्णाङ्क विस्थापनम्_x;
        पूर्णाङ्क विस्थापनम्_y;

        bool mapped;
        bool opaque;
    } आवरणम्;

    संरचना
    {
        पूर्णाङ्क hint;
        पूर्णाङ्क purpose;
        bool सक्रिय;
    } text_निवेशः_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID चरमः_display_ID;
    पूर्णाङ्क pending_state_deadline_गणनम्;
    Uint64 चरमः_focus_event_time_ns;
    Uint64 चरमः_resize_event_time_ns;
    पूर्णाङ्क icc_fd;
    Uint32 icc_आकार;
    bool floating;
    bool suspended;
    bool resizing;
    bool सक्रिय;
    bool pending_config_ack;
    bool pending_state_commit;
    bool limits_परिवर्तितम्;
    bool is_fullscreen;
    bool fullscreen_exclusive;
    bool drop_fullscreen_अनुरोधाः;
    bool showing_गवाक्षः;
    bool fullscreen_was_positioned;
    bool show_hide_sync_required;
    bool scale_गन्तव्यम्_display;
    bool reparenting_required;
    bool double_बफर;
    bool accepts_drag_and_drop;
    bool enable_insets;

    SDL_लब्धम्_Test_परिणाम लब्धम्_test_परिणाम;

    संरचना wl_list external_गवाक्षः_list_link;
};

बाह्य शून्य Wayland_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Wayland_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Wayland_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य SDL_Fullscreen_परिणाम Wayland_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
बाह्य शून्य Wayland_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Wayland_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Wayland_समुच्चयः_गवाक्षः_Mouse_Rect(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Wayland_समुच्चयः_गवाक्षः_Mouse_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed);
बाह्य bool Wayland_समुच्चयः_गवाक्षः_Keyboard_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed);
बाह्य शून्य Wayland_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Wayland_समुच्चयः_गवाक्षः_Bordered(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool bordered);
बाह्य शून्य Wayland_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool resizable);
बाह्य bool Wayland_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
बाह्य bool Wayland_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Wayland_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Wayland_समुच्चयः_गवाक्षः_Aspect_अनुपातः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Wayland_समुच्चयः_गवाक्षः_Minimum_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Wayland_समुच्चयः_गवाक्षः_अधिकतमम्_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Wayland_Get_गवाक्षः_आकार_अन्तर्_Pixels(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *w, पूर्णाङ्क *h);
बाह्य SDL_DisplayID Wayland_Get_Display_For_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Wayland_समुच्चयः_गवाक्षः_Parent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः *parent_गवाक्षः);
बाह्य bool Wayland_समुच्चयः_गवाक्षः_Modal(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool modal);
बाह्य bool Wayland_समुच्चयः_गवाक्षः_Opacity(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, भिन्न opacity);
बाह्य शून्य Wayland_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Wayland_Show_गवाक्षः_System_Menu(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क x, पूर्णाङ्क y);
बाह्य शून्य Wayland_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
बाह्य bool Wayland_समुच्चयः_गवाक्षः_Icon(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *icon);
बाह्य bool Wayland_समुच्चयः_गवाक्षः_Focusable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool focusable);
बाह्य भिन्न Wayland_Get_गवाक्षः_Content_Scale(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य *Wayland_Get_गवाक्षः_ICCProfile(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, size_t *आकार);
बाह्य शून्य Wayland_AcceptDragAndDrop(SDL_गवाक्षः *गवाक्षः, bool accept);

बाह्य bool Wayland_समुच्चयः_गवाक्षः_लब्धम्_Test(SDL_गवाक्षः *गवाक्षः, bool enabled);
बाह्य bool Wayland_Flash_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_FlashOperation operation);
बाह्य bool Wayland_Sync_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Wayland_Reconfigure_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः_Flags flags);

बाह्य शून्य Wayland_Remove_Output_From_गवाक्षः(SDL_गवाक्षः_दत्त *गवाक्षः, SDL_Display_दत्त *display_दत्त);
बाह्य शून्य Wayland_Update_गवाक्षः_Position(SDL_गवाक्षः *गवाक्षः);

#यदि_अन्तः // SDL_waylandwindow_h_
