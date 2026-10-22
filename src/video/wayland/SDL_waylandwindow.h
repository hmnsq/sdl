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

#ifndef SDL_waylandwindow_h_
#define SDL_waylandwindow_h_

#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_touch_c.h"

#अन्तर्भाव "SDL_waylandvideo.h"
#अन्तर्भाव "SDL_waylandshmbuffer.h"

संरचना SDL_WindowData
{
    SDL_Window *sdlwindow;
    SDL_VideoData *waylandData;
    संरचना wl_surface *surface;
    संरचना wl_callback *gles_swap_frame_callback;
    संरचना wl_event_queue *gles_swap_frame_event_queue;
    संरचना wl_surface *gles_swap_frame_surface_wrapper;
    संरचना wl_callback *surface_frame_callback;

    सङ्घ
    {
#ifdef HAVE_LIBDECOR_H
        संरचना
        {
            संरचना libdecor_frame *frame;
        } libdecor;
#endif
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
        WAYLAND_SHELL_SURFACE_STATUS_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_STATUS_SHOWN
    } shell_surface_status;
    गणना
    {
        WAYLAND_WM_CAPS_WINDOW_MENU = 0x01,
        WAYLAND_WM_CAPS_MAXIMIZE = 0x02,
        WAYLAND_WM_CAPS_FULLSCREEN = 0x04,
        WAYLAND_WM_CAPS_MINIMIZE = 0x08,

        WAYLAND_WM_CAPS_ALL = WAYLAND_WM_CAPS_WINDOW_MENU |
                              WAYLAND_WM_CAPS_MAXIMIZE |
                              WAYLAND_WM_CAPS_FULLSCREEN |
                              WAYLAND_WM_CAPS_MINIMIZE
    } wm_caps;
    गणना
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    गणना
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    संरचना wl_egl_window *egl_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
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

    SDL_DisplayData **outputs;
    पूर्णाङ्क अंक_outputs;

    वर्ण *app_id;
    वर्ण *session_id;
    द्विगुण scale_factor;

    संरचना wl_buffer **icon_buffers;
    पूर्णाङ्क icon_buffer_गिनती;

    // Keyboard, pointer, and touch focus refcount.
    पूर्णाङ्क keyboard_focus_गिनती;
    पूर्णाङ्क pointer_focus_गिनती;
    पूर्णाङ्क active_touch_गिनती;

    संरचना
    {
        द्विगुण x;
        द्विगुण y;
    } pointer_scale;

    // The in-flight window size request.
    संरचना
    {
        // The requested logical window size.
        पूर्णाङ्क logical_width;
        पूर्णाङ्क logical_height;

        // The size of the window in pixels, when using screen space scaling.
        पूर्णाङ्क pixel_width;
        पूर्णाङ्क pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    संरचना
    {
        // The size of the underlying window.
        पूर्णाङ्क logical_width;
        पूर्णाङ्क logical_height;

        // The size of the window backbuffer in pixels.
        पूर्णाङ्क pixel_width;
        पूर्णाङ्क pixel_height;

        // The dimensions of the active viewport, in logical units.
        पूर्णाङ्क viewport_width;
        पूर्णाङ्क viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    संरचना
    {
        पूर्णाङ्क width;
        पूर्णाङ्क height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    संरचना
    {
        // Minimum allowed logical window size.
        पूर्णाङ्क min_width;
        पूर्णाङ्क min_height;
    } system_limits;

    संरचना
    {
        पूर्णाङ्क width;
        पूर्णाङ्क height;
    } toplevel_bounds;

    संरचना
    {
        संरचना wl_surface *surface;
        संरचना wl_subsurface *subsurface;
        संरचना wl_buffer *buffer;
        संरचना wp_viewport *viewport;

        पूर्णाङ्क offset_x;
        पूर्णाङ्क offset_y;

        bool mapped;
        bool opaque;
    } mask;

    संरचना
    {
        पूर्णाङ्क hint;
        पूर्णाङ्क purpose;
        bool active;
    } text_निवेश_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    पूर्णाङ्क pending_state_deadline_गिनती;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    पूर्णाङ्क icc_fd;
    Uint32 icc_size;
    bool floating;
    bool suspended;
    bool resizing;
    bool active;
    bool pending_config_ack;
    bool pending_state_commit;
    bool limits_changed;
    bool is_fullscreen;
    bool fullscreen_exclusive;
    bool drop_fullscreen_requests;
    bool showing_window;
    bool fullscreen_was_positioned;
    bool show_hide_sync_required;
    bool scale_to_display;
    bool reparenting_required;
    bool double_buffer;
    bool accepts_drag_and_drop;
    bool enable_insets;

    SDL_HitTestResult hit_test_result;

    संरचना wl_list external_window_list_link;
};

बाह्य शून्य Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
बाह्य शून्य Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य शून्य Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
बाह्य शून्य Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
बाह्य bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *w, पूर्णाङ्क *h);
बाह्य SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
बाह्य bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
बाह्य bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, भिन्न opacity);
बाह्य शून्य Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य Wayland_ShowWindowSystemMenu(SDL_Window *window, पूर्णाङ्क x, पूर्णाङ्क y);
बाह्य शून्य Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
बाह्य bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
बाह्य bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
बाह्य भिन्न Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, माप_प्रकार *size);
बाह्य शून्य Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

बाह्य bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
बाह्य bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
बाह्य bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

बाह्य शून्य Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data);
बाह्य शून्य Wayland_UpdateWindowPosition(SDL_Window *window);

#endif // SDL_waylandwindow_h_
