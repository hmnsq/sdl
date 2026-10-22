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

#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_waylandwindow_h_
#define SDL_waylandwindow_h_

#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "../../events/SDL_touch_c.h"

#அந்தர்பாவ "SDL_waylandvideo.h"
#அந்தர்பாவ "SDL_waylandshmbuffer.h"

கட்டமைப்பு SDL_WindowData
{
    SDL_Window *sdlwindow;
    SDL_VideoData *waylandData;
    கட்டமைப்பு wl_surface *surface;
    கட்டமைப்பு wl_callback *gles_swap_frame_callback;
    கட்டமைப்பு wl_event_queue *gles_swap_frame_event_queue;
    கட்டமைப்பு wl_surface *gles_swap_frame_surface_wrapper;
    கட்டமைப்பு wl_callback *surface_frame_callback;

    ஒன்றிப்பு
    {
#ifdef HAVE_LIBDECOR_H
        கட்டமைப்பு
        {
            கட்டமைப்பு libdecor_frame *frame;
        } libdecor;
#endif
        கட்டமைப்பு
        {
            கட்டமைப்பு xdg_surface *surface;
            ஒன்றிப்பு
            {
                கட்டமைப்பு
                {
                    கட்டமைப்பு xdg_toplevel *xdg_toplevel;
                } toplevel;
                கட்டமைப்பு
                {
                    கட்டமைப்பு xdg_popup *xdg_popup;
                    கட்டமைப்பு xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    எண்ணிக்கை
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    எண்ணிக்கை
    {
        WAYLAND_SHELL_SURFACE_STATUS_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_STATUS_SHOWN
    } shell_surface_status;
    எண்ணிக்கை
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
    எண்ணிக்கை
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_இடது = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_வலது = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_உச்சி = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    எண்ணிக்கை
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    கட்டமைப்பு wl_egl_window *egl_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
    கட்டமைப்பு zxdg_toplevel_decoration_v1 *server_decoration;
    கட்டமைப்பு zwp_idle_inhibitor_v1 *idle_inhibitor;
    கட்டமைப்பு xdg_activation_token_v1 *activation_token;
    கட்டமைப்பு wp_viewport *viewport;
    கட்டமைப்பு wp_fractional_scale_v1 *fractional_scale;
    கட்டமைப்பு zxdg_exported_v2 *exported;
    கட்டமைப்பு xdg_dialog_v1 *xdg_dialog_v1;
    கட்டமைப்பு wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    கட்டமைப்பு xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    கட்டமைப்பு frog_color_managed_surface *frog_color_managed_surface;
    கட்டமைப்பு wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    கட்டமைப்பு xdg_toplevel_session_v1 *xdg_toplevel_session;

    கட்டமைப்பு Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_DisplayData **outputs;
    முழு இலக்கம்_outputs;

    எழுத்து *app_id;
    எழுத்து *session_id;
    இரட்டை scale_factor;

    கட்டமைப்பு wl_buffer **icon_buffers;
    முழு icon_buffer_மொத்தம்;

    // Keyboard, pointer, and touch focus refcount.
    முழு keyboard_focus_மொத்தம்;
    முழு pointer_focus_மொத்தம்;
    முழு active_touch_மொத்தம்;

    கட்டமைப்பு
    {
        இரட்டை x;
        இரட்டை y;
    } pointer_scale;

    // The in-flight window size request.
    கட்டமைப்பு
    {
        // The requested logical window size.
        முழு logical_width;
        முழு logical_height;

        // The size of the window in pixels, when using screen space scaling.
        முழு pixel_width;
        முழு pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    கட்டமைப்பு
    {
        // The size of the underlying window.
        முழு logical_width;
        முழு logical_height;

        // The size of the window backbuffer in pixels.
        முழு pixel_width;
        முழு pixel_height;

        // The dimensions of the active viewport, in logical units.
        முழு viewport_width;
        முழு viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    கட்டமைப்பு
    {
        முழு width;
        முழு height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    கட்டமைப்பு
    {
        // Minimum allowed logical window size.
        முழு min_width;
        முழு min_height;
    } system_limits;

    கட்டமைப்பு
    {
        முழு width;
        முழு height;
    } toplevel_bounds;

    கட்டமைப்பு
    {
        கட்டமைப்பு wl_surface *surface;
        கட்டமைப்பு wl_subsurface *subsurface;
        கட்டமைப்பு wl_buffer *buffer;
        கட்டமைப்பு wp_viewport *viewport;

        முழு offset_x;
        முழு offset_y;

        bool mapped;
        bool opaque;
    } mask;

    கட்டமைப்பு
    {
        முழு hint;
        முழு purpose;
        bool active;
    } text_உள்ளீடு_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    முழு pending_state_deadline_மொத்தம்;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    முழு icc_fd;
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

    கட்டமைப்பு wl_list external_window_list_link;
};

வெளி வெறுமை Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
வெளி வெறுமை Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
வெளி bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
வெளி வெறுமை Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
வெளி வெறுமை Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
வெளி bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
வெளி bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, முழு *w, முழு *h);
வெளி SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
வெளி bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
வெளி bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, தசம opacity);
வெளி வெறுமை Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை Wayland_ShowWindowSystemMenu(SDL_Window *window, முழு x, முழு y);
வெளி வெறுமை Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
வெளி bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
வெளி bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
வெளி தசம Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
வெளி வெறுமை Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

வெளி bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
வெளி bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
வெளி bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

வெளி வெறுமை Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data);
வெளி வெறுமை Wayland_UpdateWindowPosition(SDL_Window *window);

#endif // SDL_waylandwindow_h_
