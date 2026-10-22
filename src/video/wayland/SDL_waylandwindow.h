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

#شامل "SDL_internal.h"

#ifndef SDL_waylandwindow_h_
#define SDL_waylandwindow_h_

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_touch_c.h"

#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandshmbuffer.h"

ساختار SDL_WindowData
{
    SDL_Window *sdlwindow;
    SDL_VideoData *waylandData;
    ساختار wl_surface *surface;
    ساختار wl_callback *gles_swap_frame_callback;
    ساختار wl_event_queue *gles_swap_frame_event_queue;
    ساختار wl_surface *gles_swap_frame_surface_wrapper;
    ساختار wl_callback *surface_frame_callback;

    اجتماع
    {
#ifdef HAVE_LIBDECOR_H
        ساختار
        {
            ساختار libdecor_frame *frame;
        } libdecor;
#endif
        ساختار
        {
            ساختار xdg_surface *surface;
            اجتماع
            {
                ساختار
                {
                    ساختار xdg_toplevel *xdg_toplevel;
                } toplevel;
                ساختار
                {
                    ساختار xdg_popup *xdg_popup;
                    ساختار xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    شمارش
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    شمارش
    {
        WAYLAND_SHELL_SURFACE_STATUS_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_STATUS_SHOWN
    } shell_surface_status;
    شمارش
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
    شمارش
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_چپ = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_راست = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    شمارش
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    ساختار wl_egl_window *egl_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
    ساختار zxdg_toplevel_decoration_v1 *server_decoration;
    ساختار zwp_idle_inhibitor_v1 *idle_inhibitor;
    ساختار xdg_activation_token_v1 *activation_token;
    ساختار wp_viewport *viewport;
    ساختار wp_fractional_scale_v1 *fractional_scale;
    ساختار zxdg_exported_v2 *exported;
    ساختار xdg_dialog_v1 *xdg_dialog_v1;
    ساختار wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    ساختار xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    ساختار frog_color_managed_surface *frog_color_managed_surface;
    ساختار wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    ساختار xdg_toplevel_session_v1 *xdg_toplevel_session;

    ساختار Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_DisplayData **outputs;
    صحیح رقم_outputs;

    نویسه *app_id;
    نویسه *session_id;
    دوگانه scale_factor;

    ساختار wl_buffer **icon_buffers;
    صحیح icon_buffer_شمار;

    // Keyboard, pointer, and touch focus refcount.
    صحیح keyboard_focus_شمار;
    صحیح pointer_focus_شمار;
    صحیح active_touch_شمار;

    ساختار
    {
        دوگانه x;
        دوگانه y;
    } pointer_scale;

    // The in-flight window size request.
    ساختار
    {
        // The requested logical window size.
        صحیح logical_width;
        صحیح logical_height;

        // The size of the window in pixels, when using screen space scaling.
        صحیح pixel_width;
        صحیح pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    ساختار
    {
        // The size of the underlying window.
        صحیح logical_width;
        صحیح logical_height;

        // The size of the window backbuffer in pixels.
        صحیح pixel_width;
        صحیح pixel_height;

        // The dimensions of the active viewport, in logical units.
        صحیح viewport_width;
        صحیح viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    ساختار
    {
        صحیح width;
        صحیح height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    ساختار
    {
        // Minimum allowed logical window size.
        صحیح min_width;
        صحیح min_height;
    } system_limits;

    ساختار
    {
        صحیح width;
        صحیح height;
    } toplevel_bounds;

    ساختار
    {
        ساختار wl_surface *surface;
        ساختار wl_subsurface *subsurface;
        ساختار wl_buffer *buffer;
        ساختار wp_viewport *viewport;

        صحیح offset_x;
        صحیح offset_y;

        bool mapped;
        bool opaque;
    } mask;

    ساختار
    {
        صحیح hint;
        صحیح purpose;
        bool active;
    } text_درون_داد_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    صحیح pending_state_deadline_شمار;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    صحیح icc_fd;
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

    ساختار wl_list external_window_list_link;
};

بیرونی تهی Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
بیرونی تهی Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
بیرونی bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
بیرونی تهی Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
بیرونی تهی Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
بیرونی bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
بیرونی bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, صحیح *w, صحیح *h);
بیرونی SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
بیرونی bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
بیرونی bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, اعشاری opacity);
بیرونی تهی Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی Wayland_ShowWindowSystemMenu(SDL_Window *window, صحیح x, صحیح y);
بیرونی تهی Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
بیرونی bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
بیرونی bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
بیرونی اعشاری Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی تهی *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
بیرونی تهی Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

بیرونی bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
بیرونی bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
بیرونی bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
بیرونی bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

بیرونی تهی Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data);
بیرونی تهی Wayland_UpdateWindowPosition(SDL_Window *window);

#endif // SDL_waylandwindow_h_
