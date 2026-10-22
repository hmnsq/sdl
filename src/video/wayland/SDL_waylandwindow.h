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

#ifndef SDL_waylandwindow_h_
#define SDL_waylandwindow_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandshmbuffer.h"

ಸಂರಚನಾ SDL_WindowData
{
    SDL_Window *sdlwindow;
    SDL_VideoData *waylandData;
    ಸಂರಚನಾ wl_surface *surface;
    ಸಂರಚನಾ wl_callback *gles_swap_frame_callback;
    ಸಂರಚನಾ wl_event_queue *gles_swap_frame_event_queue;
    ಸಂರಚನಾ wl_surface *gles_swap_frame_surface_wrapper;
    ಸಂರಚನಾ wl_callback *surface_frame_callback;

    ಸಙ್ಘ
    {
#ifdef HAVE_LIBDECOR_H
        ಸಂರಚನಾ
        {
            ಸಂರಚನಾ libdecor_frame *frame;
        } libdecor;
#endif
        ಸಂರಚನಾ
        {
            ಸಂರಚನಾ xdg_surface *surface;
            ಸಙ್ಘ
            {
                ಸಂರಚನಾ
                {
                    ಸಂರಚನಾ xdg_toplevel *xdg_toplevel;
                } toplevel;
                ಸಂರಚನಾ
                {
                    ಸಂರಚನಾ xdg_popup *xdg_popup;
                    ಸಂರಚನಾ xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    ಗಣನಾ
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    ಗಣನಾ
    {
        WAYLAND_SHELL_SURFACE_STATUS_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_STATUS_SHOWN
    } shell_surface_status;
    ಗಣನಾ
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
    ಗಣನಾ
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    ಗಣನಾ
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    ಸಂರಚನಾ wl_egl_window *egl_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
    ಸಂರಚನಾ zxdg_toplevel_decoration_v1 *server_decoration;
    ಸಂರಚನಾ zwp_idle_inhibitor_v1 *idle_inhibitor;
    ಸಂರಚನಾ xdg_activation_token_v1 *activation_token;
    ಸಂರಚನಾ wp_viewport *viewport;
    ಸಂರಚನಾ wp_fractional_scale_v1 *fractional_scale;
    ಸಂರಚನಾ zxdg_exported_v2 *exported;
    ಸಂರಚನಾ xdg_dialog_v1 *xdg_dialog_v1;
    ಸಂರಚನಾ wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    ಸಂರಚನಾ xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    ಸಂರಚನಾ frog_color_managed_surface *frog_color_managed_surface;
    ಸಂರಚನಾ wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    ಸಂರಚನಾ xdg_toplevel_session_v1 *xdg_toplevel_session;

    ಸಂರಚನಾ Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_DisplayData **outputs;
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_outputs;

    ವರ್ಣ *app_id;
    ವರ್ಣ *session_id;
    ದ್ವಿಗುಣ scale_factor;

    ಸಂರಚನಾ wl_buffer **icon_buffers;
    ಪೂರ್ಣಾಙ್ಕ icon_buffer_ಎಣಿಕೆ;

    // Keyboard, pointer, and touch focus refcount.
    ಪೂರ್ಣಾಙ್ಕ keyboard_focus_ಎಣಿಕೆ;
    ಪೂರ್ಣಾಙ್ಕ pointer_focus_ಎಣಿಕೆ;
    ಪೂರ್ಣಾಙ್ಕ active_touch_ಎಣಿಕೆ;

    ಸಂರಚನಾ
    {
        ದ್ವಿಗುಣ x;
        ದ್ವಿಗುಣ y;
    } pointer_scale;

    // The in-flight window size request.
    ಸಂರಚನಾ
    {
        // The requested logical window size.
        ಪೂರ್ಣಾಙ್ಕ logical_width;
        ಪೂರ್ಣಾಙ್ಕ logical_height;

        // The size of the window in pixels, when using screen space scaling.
        ಪೂರ್ಣಾಙ್ಕ pixel_width;
        ಪೂರ್ಣಾಙ್ಕ pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    ಸಂರಚನಾ
    {
        // The size of the underlying window.
        ಪೂರ್ಣಾಙ್ಕ logical_width;
        ಪೂರ್ಣಾಙ್ಕ logical_height;

        // The size of the window backbuffer in pixels.
        ಪೂರ್ಣಾಙ್ಕ pixel_width;
        ಪೂರ್ಣಾಙ್ಕ pixel_height;

        // The dimensions of the active viewport, in logical units.
        ಪೂರ್ಣಾಙ್ಕ viewport_width;
        ಪೂರ್ಣಾಙ್ಕ viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    ಸಂರಚನಾ
    {
        ಪೂರ್ಣಾಙ್ಕ width;
        ಪೂರ್ಣಾಙ್ಕ height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    ಸಂರಚನಾ
    {
        // Minimum allowed logical window size.
        ಪೂರ್ಣಾಙ್ಕ min_width;
        ಪೂರ್ಣಾಙ್ಕ min_height;
    } system_limits;

    ಸಂರಚನಾ
    {
        ಪೂರ್ಣಾಙ್ಕ width;
        ಪೂರ್ಣಾಙ್ಕ height;
    } toplevel_bounds;

    ಸಂರಚನಾ
    {
        ಸಂರಚನಾ wl_surface *surface;
        ಸಂರಚನಾ wl_subsurface *subsurface;
        ಸಂರಚನಾ wl_buffer *buffer;
        ಸಂರಚನಾ wp_viewport *viewport;

        ಪೂರ್ಣಾಙ್ಕ offset_x;
        ಪೂರ್ಣಾಙ್ಕ offset_y;

        bool mapped;
        bool opaque;
    } mask;

    ಸಂರಚನಾ
    {
        ಪೂರ್ಣಾಙ್ಕ hint;
        ಪೂರ್ಣಾಙ್ಕ purpose;
        bool active;
    } text_ಒಳಹರಿವು_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    ಪೂರ್ಣಾಙ್ಕ pending_state_deadline_ಎಣಿಕೆ;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    ಪೂರ್ಣಾಙ್ಕ icc_fd;
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

    ಸಂರಚನಾ wl_list external_window_list_link;
};

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ಬಾಹ್ಯ bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
ಬಾಹ್ಯ bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ಬಾಹ್ಯ bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ *w, ಪೂರ್ಣಾಙ್ಕ *h);
ಬಾಹ್ಯ SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
ಬಾಹ್ಯ bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
ಬಾಹ್ಯ bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ಭಿನ್ನ opacity);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ShowWindowSystemMenu(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
ಬಾಹ್ಯ bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
ಬಾಹ್ಯ ಭಿನ್ನ Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

ಬಾಹ್ಯ bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
ಬಾಹ್ಯ bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
ಬಾಹ್ಯ bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_UpdateWindowPosition(SDL_Window *window);

#endif // SDL_waylandwindow_h_
