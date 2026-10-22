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

কাঠামো SDL_Window_তথ্য
{
    SDL_Window *sdlwindow;
    SDL_Video_তথ্য *wayland_তথ্য;
    কাঠামো wl_surface *surface;
    কাঠামো wl_callback *gles_swap_frame_callback;
    কাঠামো wl_event_queue *gles_swap_frame_event_queue;
    কাঠামো wl_surface *gles_swap_frame_surface_wrapper;
    কাঠামো wl_callback *surface_frame_callback;

    সংঘ
    {
#ifdef HAVE_LIBDECOR_H
        কাঠামো
        {
            কাঠামো libdecor_frame *frame;
        } libdecor;
#endif
        কাঠামো
        {
            কাঠামো xdg_surface *surface;
            সংঘ
            {
                কাঠামো
                {
                    কাঠামো xdg_toplevel *xdg_toplevel;
                } toplevel;
                কাঠামো
                {
                    কাঠামো xdg_popup *xdg_popup;
                    কাঠামো xdg_positioner *xdg_positioner;
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

    কাঠামো wl_egl_window *egl_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
    কাঠামো zxdg_toplevel_decoration_v1 *server_decoration;
    কাঠামো zwp_idle_inhibitor_v1 *idle_inhibitor;
    কাঠামো xdg_activation_token_v1 *activation_token;
    কাঠামো wp_viewport *viewport;
    কাঠামো wp_fractional_scale_v1 *fractional_scale;
    কাঠামো zxdg_exported_v2 *exported;
    কাঠামো xdg_dialog_v1 *xdg_dialog_v1;
    কাঠামো wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    কাঠামো xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    কাঠামো frog_color_managed_surface *frog_color_managed_surface;
    কাঠামো wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    কাঠামো xdg_toplevel_session_v1 *xdg_toplevel_session;

    কাঠামো Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_Display_তথ্য **outputs;
    পূর্ণসংখ্যা অঙ্ক_outputs;

    অক্ষর *app_id;
    অক্ষর *session_id;
    দ্বিগুণ scale_factor;

    কাঠামো wl_বাফার **icon_buffers;
    পূর্ণসংখ্যা icon_বাফার_গুনতি;

    // Keyboard, pointer, and touch focus refcount.
    পূর্ণসংখ্যা keyboard_focus_গুনতি;
    পূর্ণসংখ্যা pointer_focus_গুনতি;
    পূর্ণসংখ্যা active_touch_গুনতি;

    কাঠামো
    {
        দ্বিগুণ x;
        দ্বিগুণ y;
    } pointer_scale;

    // The in-flight window size request.
    কাঠামো
    {
        // The requested logical window size.
        পূর্ণসংখ্যা logical_width;
        পূর্ণসংখ্যা logical_height;

        // The size of the window in pixels, when using screen space scaling.
        পূর্ণসংখ্যা pixel_width;
        পূর্ণসংখ্যা pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    কাঠামো
    {
        // The size of the underlying window.
        পূর্ণসংখ্যা logical_width;
        পূর্ণসংখ্যা logical_height;

        // The size of the window backbuffer in pixels.
        পূর্ণসংখ্যা pixel_width;
        পূর্ণসংখ্যা pixel_height;

        // The dimensions of the active viewport, in logical units.
        পূর্ণসংখ্যা viewport_width;
        পূর্ণসংখ্যা viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    কাঠামো
    {
        পূর্ণসংখ্যা width;
        পূর্ণসংখ্যা height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    কাঠামো
    {
        // Minimum allowed logical window size.
        পূর্ণসংখ্যা min_width;
        পূর্ণসংখ্যা min_height;
    } system_limits;

    কাঠামো
    {
        পূর্ণসংখ্যা width;
        পূর্ণসংখ্যা height;
    } toplevel_bounds;

    কাঠামো
    {
        কাঠামো wl_surface *surface;
        কাঠামো wl_subsurface *subsurface;
        কাঠামো wl_বাফার *বাফার_2;
        কাঠামো wp_viewport *viewport;

        পূর্ণসংখ্যা offset_x;
        পূর্ণসংখ্যা offset_y;

        bool mapped;
        bool opaque;
    } mask;

    কাঠামো
    {
        পূর্ণসংখ্যা hint;
        পূর্ণসংখ্যা purpose;
        bool active;
    } text_প্রবেশ_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    পূর্ণসংখ্যা pending_state_deadline_গুনতি;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    পূর্ণসংখ্যা icc_fd;
    Uint32 icc_আকার;
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
    bool double_বাফার;
    bool accepts_drag_and_drop;
    bool enable_insets;

    SDL_Hit_Test_ফলাফল hit_test_ফলাফল;

    কাঠামো wl_list external_window_list_link;
};

বাহ্যিক শূন্য Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক SDL_Fullscreen_ফলাফল Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
বাহ্যিক শূন্য Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
বাহ্যিক bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
বাহ্যিক শূন্য Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
বাহ্যিক শূন্য Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
বাহ্যিক bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
বাহ্যিক bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য Wayland_Set_Window_আকার(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য Wayland_Set_Window_Minimum_আকার(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য Wayland_Set_Window_Maximum_আকার(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য Wayland_Get_Window_আকার_In_Pixels(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণসংখ্যা *w, পূর্ণসংখ্যা *h);
বাহ্যিক SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
বাহ্যিক bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
বাহ্যিক bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, দশমিক opacity);
বাহ্যিক শূন্য Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য Wayland_ShowWindowSystemMenu(SDL_Window *window, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y);
বাহ্যিক শূন্য Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
বাহ্যিক bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
বাহ্যিক bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
বাহ্যিক দশমিক Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *আকার_2);
বাহ্যিক শূন্য Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

বাহ্যিক bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
বাহ্যিক bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
বাহ্যিক bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

বাহ্যিক শূন্য Wayland_RemoveOutputFromWindow(SDL_Window_তথ্য *window, SDL_Display_তথ্য *display_তথ্য);
বাহ্যিক শূন্য Wayland_UpdateWindowPosition(SDL_Window *window);

#endif // SDL_waylandwindow_h_
