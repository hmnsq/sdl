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

#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_waylandwindow_h_
#define SDL_waylandwindow_h_

#অন্তর্ভাব "../SDL_sysvideo.h"
#অন্তর্ভাব "../../events/SDL_touch_c.h"

#অন্তর্ভাব "SDL_waylandvideo.h"
#অন্তর্ভাব "SDL_waylandshmbuffer.h"

সংরচনা SDL_WindowData
{
    SDL_Window *sdlwindow;
    SDL_VideoData *waylandData;
    সংরচনা wl_surface *surface;
    সংরচনা wl_callback *gles_swap_frame_callback;
    সংরচনা wl_event_queue *gles_swap_frame_event_queue;
    সংরচনা wl_surface *gles_swap_frame_surface_wrapper;
    সংরচনা wl_callback *surface_frame_callback;

    সঙ্ঘ
    {
#ifdef HAVE_LIBDECOR_H
        সংরচনা
        {
            সংরচনা libdecor_frame *frame;
        } libdecor;
#endif
        সংরচনা
        {
            সংরচনা xdg_surface *surface;
            সঙ্ঘ
            {
                সংরচনা
                {
                    সংরচনা xdg_toplevel *xdg_toplevel;
                } toplevel;
                সংরচনা
                {
                    সংরচনা xdg_popup *xdg_popup;
                    সংরচনা xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    গণনা
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    গণনা
    {
        WAYLAND_SHELL_SURFACE_STATUS_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_STATUS_SHOWN
    } shell_surface_status;
    গণনা
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
    গণনা
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_বাম = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_ডান = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_শীর্ষ = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    গণনা
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    সংরচনা wl_egl_window *egl_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
    সংরচনা zxdg_toplevel_decoration_v1 *server_decoration;
    সংরচনা zwp_idle_inhibitor_v1 *idle_inhibitor;
    সংরচনা xdg_activation_token_v1 *activation_token;
    সংরচনা wp_viewport *viewport;
    সংরচনা wp_fractional_scale_v1 *fractional_scale;
    সংরচনা zxdg_exported_v2 *exported;
    সংরচনা xdg_dialog_v1 *xdg_dialog_v1;
    সংরচনা wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    সংরচনা xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    সংরচনা frog_color_managed_surface *frog_color_managed_surface;
    সংরচনা wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    সংরচনা xdg_toplevel_session_v1 *xdg_toplevel_session;

    সংরচনা Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_DisplayData **outputs;
    পূর্ণাঙ্ক অঙ্ক_outputs;

    বর্ণ *app_id;
    বর্ণ *session_id;
    দ্বিগুণ scale_factor;

    সংরচনা wl_buffer **icon_buffers;
    পূর্ণাঙ্ক icon_buffer_গুনতি;

    // Keyboard, pointer, and touch focus refcount.
    পূর্ণাঙ্ক keyboard_focus_গুনতি;
    পূর্ণাঙ্ক pointer_focus_গুনতি;
    পূর্ণাঙ্ক active_touch_গুনতি;

    সংরচনা
    {
        দ্বিগুণ x;
        দ্বিগুণ y;
    } pointer_scale;

    // The in-flight window size request.
    সংরচনা
    {
        // The requested logical window size.
        পূর্ণাঙ্ক logical_width;
        পূর্ণাঙ্ক logical_height;

        // The size of the window in pixels, when using screen space scaling.
        পূর্ণাঙ্ক pixel_width;
        পূর্ণাঙ্ক pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    সংরচনা
    {
        // The size of the underlying window.
        পূর্ণাঙ্ক logical_width;
        পূর্ণাঙ্ক logical_height;

        // The size of the window backbuffer in pixels.
        পূর্ণাঙ্ক pixel_width;
        পূর্ণাঙ্ক pixel_height;

        // The dimensions of the active viewport, in logical units.
        পূর্ণাঙ্ক viewport_width;
        পূর্ণাঙ্ক viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    সংরচনা
    {
        পূর্ণাঙ্ক width;
        পূর্ণাঙ্ক height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    সংরচনা
    {
        // Minimum allowed logical window size.
        পূর্ণাঙ্ক min_width;
        পূর্ণাঙ্ক min_height;
    } system_limits;

    সংরচনা
    {
        পূর্ণাঙ্ক width;
        পূর্ণাঙ্ক height;
    } toplevel_bounds;

    সংরচনা
    {
        সংরচনা wl_surface *surface;
        সংরচনা wl_subsurface *subsurface;
        সংরচনা wl_buffer *buffer;
        সংরচনা wp_viewport *viewport;

        পূর্ণাঙ্ক offset_x;
        পূর্ণাঙ্ক offset_y;

        bool mapped;
        bool opaque;
    } mask;

    সংরচনা
    {
        পূর্ণাঙ্ক hint;
        পূর্ণাঙ্ক purpose;
        bool active;
    } text_প্রবেশ_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    পূর্ণাঙ্ক pending_state_deadline_গুনতি;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    পূর্ণাঙ্ক icc_fd;
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

    সংরচনা wl_list external_window_list_link;
};

বাহ্য শূন্য Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
বাহ্য শূন্য Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
বাহ্য bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
বাহ্য শূন্য Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
বাহ্য শূন্য Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
বাহ্য bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
বাহ্য bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক *w, পূর্ণাঙ্ক *h);
বাহ্য SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
বাহ্য bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
বাহ্য bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ভিন্ন opacity);
বাহ্য শূন্য Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য Wayland_ShowWindowSystemMenu(SDL_Window *window, পূর্ণাঙ্ক x, পূর্ণাঙ্ক y);
বাহ্য শূন্য Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
বাহ্য bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
বাহ্য bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
বাহ্য ভিন্ন Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য শূন্য *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
বাহ্য শূন্য Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

বাহ্য bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
বাহ্য bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
বাহ্য bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্য bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

বাহ্য শূন্য Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data);
বাহ্য শূন্য Wayland_UpdateWindowPosition(SDL_Window *window);

#endif // SDL_waylandwindow_h_
