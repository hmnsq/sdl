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

#ifndef SDL_waylandwindow_h_
#define SDL_waylandwindow_h_

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_touch_c.h"

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandshmbuffer.h"

بنية SDL_WindowData
{
    SDL_Window *sdlwindow;
    SDL_VideoData *waylandData;
    بنية wl_surface *surface;
    بنية wl_callback *gles_swap_frame_callback;
    بنية wl_event_queue *gles_swap_frame_event_queue;
    بنية wl_surface *gles_swap_frame_surface_wrapper;
    بنية wl_callback *surface_frame_callback;

    اتحاد
    {
#ifdef HAVE_LIBDECOR_H
        بنية
        {
            بنية libdecor_frame *frame;
        } libdecor;
#endif
        بنية
        {
            بنية xdg_surface *surface;
            اتحاد
            {
                بنية
                {
                    بنية xdg_toplevel *xdg_toplevel;
                } toplevel;
                بنية
                {
                    بنية xdg_popup *xdg_popup;
                    بنية xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    تعداد
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    تعداد
    {
        WAYLAND_SHELL_SURFACE_STATUS_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_STATUS_SHOWN
    } shell_surface_status;
    تعداد
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
    تعداد
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_LEFT = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_RIGHT = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_TOP = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    تعداد
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    بنية wl_egl_window *egl_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
    بنية zxdg_toplevel_decoration_v1 *server_decoration;
    بنية zwp_idle_inhibitor_v1 *idle_inhibitor;
    بنية xdg_activation_token_v1 *activation_token;
    بنية wp_viewport *viewport;
    بنية wp_fractional_scale_v1 *fractional_scale;
    بنية zxdg_exported_v2 *exported;
    بنية xdg_dialog_v1 *xdg_dialog_v1;
    بنية wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    بنية xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    بنية frog_color_managed_surface *frog_color_managed_surface;
    بنية wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    بنية xdg_toplevel_session_v1 *xdg_toplevel_session;

    بنية Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_DisplayData **outputs;
    صحيح num_outputs;

    حرف *app_id;
    حرف *session_id;
    مزدوج scale_factor;

    بنية wl_buffer **icon_buffers;
    صحيح icon_buffer_count;

    // Keyboard, pointer, and touch focus refcount.
    صحيح keyboard_focus_count;
    صحيح pointer_focus_count;
    صحيح active_touch_count;

    بنية
    {
        مزدوج x;
        مزدوج y;
    } pointer_scale;

    // The in-flight window size request.
    بنية
    {
        // The requested logical window size.
        صحيح logical_width;
        صحيح logical_height;

        // The size of the window in pixels, when using screen space scaling.
        صحيح pixel_width;
        صحيح pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    بنية
    {
        // The size of the underlying window.
        صحيح logical_width;
        صحيح logical_height;

        // The size of the window backbuffer in pixels.
        صحيح pixel_width;
        صحيح pixel_height;

        // The dimensions of the active viewport, in logical units.
        صحيح viewport_width;
        صحيح viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    بنية
    {
        صحيح width;
        صحيح height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    بنية
    {
        // Minimum allowed logical window size.
        صحيح min_width;
        صحيح min_height;
    } system_limits;

    بنية
    {
        صحيح width;
        صحيح height;
    } toplevel_bounds;

    بنية
    {
        بنية wl_surface *surface;
        بنية wl_subsurface *subsurface;
        بنية wl_buffer *buffer;
        بنية wp_viewport *viewport;

        صحيح offset_x;
        صحيح offset_y;

        bool mapped;
        bool opaque;
    } mask;

    بنية
    {
        صحيح hint;
        صحيح purpose;
        bool active;
    } text_input_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    صحيح pending_state_deadline_count;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    صحيح icc_fd;
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

    بنية wl_list external_window_list_link;
};

خارجي فراغ Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
خارجي فراغ Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
خارجي bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
خارجي فراغ Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
خارجي فراغ Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
خارجي bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
خارجي bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, صحيح *w, صحيح *h);
خارجي SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
خارجي bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
خارجي bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, عائم opacity);
خارجي فراغ Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ Wayland_ShowWindowSystemMenu(SDL_Window *window, صحيح x, صحيح y);
خارجي فراغ Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
خارجي bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
خارجي bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
خارجي عائم Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
خارجي فراغ Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

خارجي bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
خارجي bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
خارجي bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

خارجي فراغ Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data);
خارجي فراغ Wayland_UpdateWindowPosition(SDL_Window *window);

#endif // SDL_waylandwindow_h_
