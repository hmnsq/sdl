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

#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_waylandwindow_h_
#define SDL_waylandwindow_h_

#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "../../events/SDL_touch_c.h"

#અન્તર્ભાવ "SDL_waylandvideo.h"
#અન્તર્ભાવ "SDL_waylandshmbuffer.h"

સંરચના SDL_WindowData
{
    SDL_Window *sdlwindow;
    SDL_VideoData *waylandData;
    સંરચના wl_surface *surface;
    સંરચના wl_callback *gles_swap_frame_callback;
    સંરચના wl_event_queue *gles_swap_frame_event_queue;
    સંરચના wl_surface *gles_swap_frame_surface_wrapper;
    સંરચના wl_callback *surface_frame_callback;

    સંઘ
    {
#ifdef HAVE_LIBDECOR_H
        સંરચના
        {
            સંરચના libdecor_frame *frame;
        } libdecor;
#endif
        સંરચના
        {
            સંરચના xdg_surface *surface;
            સંઘ
            {
                સંરચના
                {
                    સંરચના xdg_toplevel *xdg_toplevel;
                } toplevel;
                સંરચના
                {
                    સંરચના xdg_popup *xdg_popup;
                    સંરચના xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    ગણના
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    ગણના
    {
        WAYLAND_SHELL_SURFACE_STATUS_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_STATUS_SHOWN
    } shell_surface_status;
    ગણના
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
    ગણના
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_ડાબું = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_જમણું = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_ટોચ = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    ગણના
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    સંરચના wl_egl_window *egl_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
    સંરચના zxdg_toplevel_decoration_v1 *server_decoration;
    સંરચના zwp_idle_inhibitor_v1 *idle_inhibitor;
    સંરચના xdg_activation_token_v1 *activation_token;
    સંરચના wp_viewport *viewport;
    સંરચના wp_fractional_scale_v1 *fractional_scale;
    સંરચના zxdg_exported_v2 *exported;
    સંરચના xdg_dialog_v1 *xdg_dialog_v1;
    સંરચના wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    સંરચના xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    સંરચના frog_color_managed_surface *frog_color_managed_surface;
    સંરચના wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    સંરચના xdg_toplevel_session_v1 *xdg_toplevel_session;

    સંરચના Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_DisplayData **outputs;
    પૂર્ણાંક અંક_outputs;

    અક્ષર *app_id;
    અક્ષર *session_id;
    દ્વિગુણ scale_factor;

    સંરચના wl_buffer **icon_buffers;
    પૂર્ણાંક icon_buffer_ગણતરી;

    // Keyboard, pointer, and touch focus refcount.
    પૂર્ણાંક keyboard_focus_ગણતરી;
    પૂર્ણાંક pointer_focus_ગણતરી;
    પૂર્ણાંક active_touch_ગણતરી;

    સંરચના
    {
        દ્વિગુણ x;
        દ્વિગુણ y;
    } pointer_scale;

    // The in-flight window size request.
    સંરચના
    {
        // The requested logical window size.
        પૂર્ણાંક logical_width;
        પૂર્ણાંક logical_height;

        // The size of the window in pixels, when using screen space scaling.
        પૂર્ણાંક pixel_width;
        પૂર્ણાંક pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    સંરચના
    {
        // The size of the underlying window.
        પૂર્ણાંક logical_width;
        પૂર્ણાંક logical_height;

        // The size of the window backbuffer in pixels.
        પૂર્ણાંક pixel_width;
        પૂર્ણાંક pixel_height;

        // The dimensions of the active viewport, in logical units.
        પૂર્ણાંક viewport_width;
        પૂર્ણાંક viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    સંરચના
    {
        પૂર્ણાંક width;
        પૂર્ણાંક height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    સંરચના
    {
        // Minimum allowed logical window size.
        પૂર્ણાંક min_width;
        પૂર્ણાંક min_height;
    } system_limits;

    સંરચના
    {
        પૂર્ણાંક width;
        પૂર્ણાંક height;
    } toplevel_bounds;

    સંરચના
    {
        સંરચના wl_surface *surface;
        સંરચના wl_subsurface *subsurface;
        સંરચના wl_buffer *buffer;
        સંરચના wp_viewport *viewport;

        પૂર્ણાંક offset_x;
        પૂર્ણાંક offset_y;

        bool mapped;
        bool opaque;
    } mask;

    સંરચના
    {
        પૂર્ણાંક hint;
        પૂર્ણાંક purpose;
        bool active;
    } text_આગત_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    પૂર્ણાંક pending_state_deadline_ગણતરી;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    પૂર્ણાંક icc_fd;
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

    સંરચના wl_list external_window_list_link;
};

બાહ્ય શૂન્ય Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
બાહ્ય શૂન્ય Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
બાહ્ય bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
બાહ્ય શૂન્ય Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
બાહ્ય શૂન્ય Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
બાહ્ય bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
બાહ્ય bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, પૂર્ણાંક *w, પૂર્ણાંક *h);
બાહ્ય SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
બાહ્ય bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
બાહ્ય bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, દશાંશ opacity);
બાહ્ય શૂન્ય Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય Wayland_ShowWindowSystemMenu(SDL_Window *window, પૂર્ણાંક x, પૂર્ણાંક y);
બાહ્ય શૂન્ય Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
બાહ્ય bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
બાહ્ય bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
બાહ્ય દશાંશ Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય શૂન્ય *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
બાહ્ય શૂન્ય Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

બાહ્ય bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
બાહ્ય bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
બાહ્ય bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
બાહ્ય bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

બાહ્ય શૂન્ય Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data);
બાહ્ય શૂન્ય Wayland_UpdateWindowPosition(SDL_Window *window);

#endif // SDL_waylandwindow_h_
