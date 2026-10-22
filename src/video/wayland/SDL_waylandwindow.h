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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_waylandwindow_h_
#define SDL_waylandwindow_h_

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_touch_c.h"

#ଅନ୍ତର୍ଭାଵ "SDL_waylandvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandshmbuffer.h"

ସଂରଚନା SDL_WindowData
{
    SDL_Window *sdlwindow;
    SDL_VideoData *waylandData;
    ସଂରଚନା wl_surface *surface;
    ସଂରଚନା wl_callback *gles_swap_frame_callback;
    ସଂରଚନା wl_event_queue *gles_swap_frame_event_queue;
    ସଂରଚନା wl_surface *gles_swap_frame_surface_wrapper;
    ସଂରଚନା wl_callback *surface_frame_callback;

    ସଂଘ
    {
#ifdef HAVE_LIBDECOR_H
        ସଂରଚନା
        {
            ସଂରଚନା libdecor_frame *frame;
        } libdecor;
#endif
        ସଂରଚନା
        {
            ସଂରଚନା xdg_surface *surface;
            ସଂଘ
            {
                ସଂରଚନା
                {
                    ସଂରଚନା xdg_toplevel *xdg_toplevel;
                } toplevel;
                ସଂରଚନା
                {
                    ସଂରଚନା xdg_popup *xdg_popup;
                    ସଂରଚନା xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    ଗଣନା
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    ଗଣନା
    {
        WAYLAND_SHELL_SURFACE_STATUS_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_STATUS_SHOWN
    } shell_surface_status;
    ଗଣନା
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
    ଗଣନା
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_ବାମ = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_ଡାହାଣ = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_ଶୀର୍ଷ = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    ଗଣନା
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    ସଂରଚନା wl_egl_window *egl_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
    ସଂରଚନା zxdg_toplevel_decoration_v1 *server_decoration;
    ସଂରଚନା zwp_idle_inhibitor_v1 *idle_inhibitor;
    ସଂରଚନା xdg_activation_token_v1 *activation_token;
    ସଂରଚନା wp_viewport *viewport;
    ସଂରଚନା wp_fractional_scale_v1 *fractional_scale;
    ସଂରଚନା zxdg_exported_v2 *exported;
    ସଂରଚନା xdg_dialog_v1 *xdg_dialog_v1;
    ସଂରଚନା wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    ସଂରଚନା xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    ସଂରଚନା frog_color_managed_surface *frog_color_managed_surface;
    ସଂରଚନା wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    ସଂରଚନା xdg_toplevel_session_v1 *xdg_toplevel_session;

    ସଂରଚନା Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_DisplayData **outputs;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_outputs;

    ଅକ୍ଷର *app_id;
    ଅକ୍ଷର *session_id;
    ଦ୍ୱିଗୁଣ scale_factor;

    ସଂରଚନା wl_buffer **icon_buffers;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା icon_buffer_ଗଣନା;

    // Keyboard, pointer, and touch focus refcount.
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା keyboard_focus_ଗଣନା;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pointer_focus_ଗଣନା;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା active_touch_ଗଣନା;

    ସଂରଚନା
    {
        ଦ୍ୱିଗୁଣ x;
        ଦ୍ୱିଗୁଣ y;
    } pointer_scale;

    // The in-flight window size request.
    ସଂରଚନା
    {
        // The requested logical window size.
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା logical_width;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା logical_height;

        // The size of the window in pixels, when using screen space scaling.
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା pixel_width;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    ସଂରଚନା
    {
        // The size of the underlying window.
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା logical_width;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା logical_height;

        // The size of the window backbuffer in pixels.
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା pixel_width;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା pixel_height;

        // The dimensions of the active viewport, in logical units.
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା viewport_width;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    ସଂରଚନା
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା width;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    ସଂରଚନା
    {
        // Minimum allowed logical window size.
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା min_width;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା min_height;
    } system_limits;

    ସଂରଚନା
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା width;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା height;
    } toplevel_bounds;

    ସଂରଚନା
    {
        ସଂରଚନା wl_surface *surface;
        ସଂରଚନା wl_subsurface *subsurface;
        ସଂରଚନା wl_buffer *buffer;
        ସଂରଚନା wp_viewport *viewport;

        ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset_x;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset_y;

        bool mapped;
        bool opaque;
    } mask;

    ସଂରଚନା
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା hint;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା purpose;
        bool active;
    } text_ନିବେଶ_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pending_state_deadline_ଗଣନା;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା icc_fd;
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

    ସଂରଚନା wl_list external_window_list_link;
};

ବାହ୍ୟ ଶୂନ୍ୟ Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ବାହ୍ୟ bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
ବାହ୍ୟ bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ବାହ୍ୟ bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *h);
ବାହ୍ୟ SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
ବାହ୍ୟ bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
ବାହ୍ୟ bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ଦଶମିକ opacity);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_ShowWindowSystemMenu(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
ବାହ୍ୟ bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
ବାହ୍ୟ bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
ବାହ୍ୟ ଦଶମିକ Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

ବାହ୍ୟ bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
ବାହ୍ୟ bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
ବାହ୍ୟ bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

ବାହ୍ୟ ଶୂନ୍ୟ Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_UpdateWindowPosition(SDL_Window *window);

#endif // SDL_waylandwindow_h_
