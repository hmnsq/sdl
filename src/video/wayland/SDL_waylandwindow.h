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

#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_waylandwindow_h_
#define SDL_waylandwindow_h_

#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../../events/SDL_touch_c.h"

#അന്തര്ഭാവ "SDL_waylandvideo.h"
#അന്തര്ഭാവ "SDL_waylandshmbuffer.h"

ഘടന SDL_WindowData
{
    SDL_Window *sdlwindow;
    SDL_VideoData *waylandData;
    ഘടന wl_surface *surface;
    ഘടന wl_callback *gles_swap_frame_callback;
    ഘടന wl_event_queue *gles_swap_frame_event_queue;
    ഘടന wl_surface *gles_swap_frame_surface_wrapper;
    ഘടന wl_callback *surface_frame_callback;

    സംഘം
    {
#ifdef HAVE_LIBDECOR_H
        ഘടന
        {
            ഘടന libdecor_frame *frame;
        } libdecor;
#endif
        ഘടന
        {
            ഘടന xdg_surface *surface;
            സംഘം
            {
                ഘടന
                {
                    ഘടന xdg_toplevel *xdg_toplevel;
                } toplevel;
                ഘടന
                {
                    ഘടന xdg_popup *xdg_popup;
                    ഘടന xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    എണ്ണൽ
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    എണ്ണൽ
    {
        WAYLAND_SHELL_SURFACE_STATUS_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_STATUS_SHOWN
    } shell_surface_status;
    എണ്ണൽ
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
    എണ്ണൽ
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_ഇടത് = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_വലത് = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_മുകൾ = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    എണ്ണൽ
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    ഘടന wl_egl_window *egl_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
    ഘടന zxdg_toplevel_decoration_v1 *server_decoration;
    ഘടന zwp_idle_inhibitor_v1 *idle_inhibitor;
    ഘടന xdg_activation_token_v1 *activation_token;
    ഘടന wp_viewport *viewport;
    ഘടന wp_fractional_scale_v1 *fractional_scale;
    ഘടന zxdg_exported_v2 *exported;
    ഘടന xdg_dialog_v1 *xdg_dialog_v1;
    ഘടന wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    ഘടന xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    ഘടന frog_color_managed_surface *frog_color_managed_surface;
    ഘടന wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    ഘടന xdg_toplevel_session_v1 *xdg_toplevel_session;

    ഘടന Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_DisplayData **outputs;
    പൂർണ്ണസംഖ്യ അക്കം_outputs;

    അക്ഷരം *app_id;
    അക്ഷരം *session_id;
    ഇരട്ട scale_factor;

    ഘടന wl_buffer **icon_buffers;
    പൂർണ്ണസംഖ്യ icon_buffer_എണ്ണം;

    // Keyboard, pointer, and touch focus refcount.
    പൂർണ്ണസംഖ്യ keyboard_focus_എണ്ണം;
    പൂർണ്ണസംഖ്യ pointer_focus_എണ്ണം;
    പൂർണ്ണസംഖ്യ active_touch_എണ്ണം;

    ഘടന
    {
        ഇരട്ട x;
        ഇരട്ട y;
    } pointer_scale;

    // The in-flight window size request.
    ഘടന
    {
        // The requested logical window size.
        പൂർണ്ണസംഖ്യ logical_width;
        പൂർണ്ണസംഖ്യ logical_height;

        // The size of the window in pixels, when using screen space scaling.
        പൂർണ്ണസംഖ്യ pixel_width;
        പൂർണ്ണസംഖ്യ pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    ഘടന
    {
        // The size of the underlying window.
        പൂർണ്ണസംഖ്യ logical_width;
        പൂർണ്ണസംഖ്യ logical_height;

        // The size of the window backbuffer in pixels.
        പൂർണ്ണസംഖ്യ pixel_width;
        പൂർണ്ണസംഖ്യ pixel_height;

        // The dimensions of the active viewport, in logical units.
        പൂർണ്ണസംഖ്യ viewport_width;
        പൂർണ്ണസംഖ്യ viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    ഘടന
    {
        പൂർണ്ണസംഖ്യ width;
        പൂർണ്ണസംഖ്യ height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    ഘടന
    {
        // Minimum allowed logical window size.
        പൂർണ്ണസംഖ്യ min_width;
        പൂർണ്ണസംഖ്യ min_height;
    } system_limits;

    ഘടന
    {
        പൂർണ്ണസംഖ്യ width;
        പൂർണ്ണസംഖ്യ height;
    } toplevel_bounds;

    ഘടന
    {
        ഘടന wl_surface *surface;
        ഘടന wl_subsurface *subsurface;
        ഘടന wl_buffer *buffer;
        ഘടന wp_viewport *viewport;

        പൂർണ്ണസംഖ്യ offset_x;
        പൂർണ്ണസംഖ്യ offset_y;

        bool mapped;
        bool opaque;
    } mask;

    ഘടന
    {
        പൂർണ്ണസംഖ്യ hint;
        പൂർണ്ണസംഖ്യ purpose;
        bool active;
    } text_നിവേശം_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    പൂർണ്ണസംഖ്യ pending_state_deadline_എണ്ണം;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    പൂർണ്ണസംഖ്യ icc_fd;
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

    ഘടന wl_list external_window_list_link;
};

ബാഹ്യ ശൂന്യം Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
ബാഹ്യ ശൂന്യം Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ബാഹ്യ bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ബാഹ്യ ശൂന്യം Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
ബാഹ്യ ശൂന്യം Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
ബാഹ്യ bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ബാഹ്യ bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ *w, പൂർണ്ണസംഖ്യ *h);
ബാഹ്യ SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
ബാഹ്യ bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
ബാഹ്യ bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ദശാംശം opacity);
ബാഹ്യ ശൂന്യം Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം Wayland_ShowWindowSystemMenu(SDL_Window *window, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y);
ബാഹ്യ ശൂന്യം Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
ബാഹ്യ bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
ബാഹ്യ bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
ബാഹ്യ ദശാംശം Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ ശൂന്യം *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
ബാഹ്യ ശൂന്യം Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

ബാഹ്യ bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
ബാഹ്യ bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
ബാഹ്യ bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
ബാഹ്യ bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

ബാഹ്യ ശൂന്യം Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data);
ബാഹ്യ ശൂന്യം Wayland_UpdateWindowPosition(SDL_Window *window);

#endif // SDL_waylandwindow_h_
