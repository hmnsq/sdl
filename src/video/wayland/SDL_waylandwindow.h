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

#include "SDL_internal.h"

#ifndef SDL_waylandwindow_h_
#define SDL_waylandwindow_h_

#include "../SDL_sysvideo.h"
#include "../../events/SDL_touch_c.h"

#include "SDL_waylandvideo.h"
#include "SDL_waylandshmbuffer.h"

sa_nracanaa SDL_WindowData
{
    SDL_Window *sdlwindow;
    SDL_VideoData *waylandData;
    sa_nracanaa wl_surface *surface;
    sa_nracanaa wl_callback *gles_swap_frame_callback;
    sa_nracanaa wl_event_queue *gles_swap_frame_event_queue;
    sa_nracanaa wl_surface *gles_swap_frame_surface_wrapper;
    sa_nracanaa wl_callback *surface_frame_callback;

    sa_ngha
    {
#ifdef HAVE_LIBDECOR_H
        sa_nracanaa
        {
            sa_nracanaa libdecor_frame *frame;
        } libdecor;
#endif
        sa_nracanaa
        {
            sa_nracanaa xdg_surface *surface;
            sa_ngha
            {
                sa_nracanaa
                {
                    sa_nracanaa xdg_toplevel *xdg_toplevel;
                } toplevel;
                sa_nracanaa
                {
                    sa_nracanaa xdg_popup *xdg_popup;
                    sa_nracanaa xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    ga_nanaa
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    ga_nanaa
    {
        WAYLAND_SHELL_SURFACE_STATUS_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_STATUS_SHOWN
    } shell_surface_status;
    ga_nanaa
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
    ga_nanaa
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_LEFT = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_RIGHT = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_TOP = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    ga_nanaa
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    sa_nracanaa wl_egl_window *egl_window;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
    sa_nracanaa zxdg_toplevel_decoration_v1 *server_decoration;
    sa_nracanaa zwp_idle_inhibitor_v1 *idle_inhibitor;
    sa_nracanaa xdg_activation_token_v1 *activation_token;
    sa_nracanaa wp_viewport *viewport;
    sa_nracanaa wp_fractional_scale_v1 *fractional_scale;
    sa_nracanaa zxdg_exported_v2 *exported;
    sa_nracanaa xdg_dialog_v1 *xdg_dialog_v1;
    sa_nracanaa wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    sa_nracanaa xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    sa_nracanaa frog_color_managed_surface *frog_color_managed_surface;
    sa_nracanaa wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    sa_nracanaa xdg_toplevel_session_v1 *xdg_toplevel_session;

    sa_nracanaa Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_DisplayData **outputs;
    පූර්ණ_සංඛ්‍යා num_outputs;

    var_na *app_id;
    var_na *session_id;
    dviguu_na scale_factor;

    sa_nracanaa wl_buffer **icon_buffers;
    පූර්ණ_සංඛ්‍යා icon_buffer_count;

    // Keyboard, pointer, and touch focus refcount.
    පූර්ණ_සංඛ්‍යා keyboard_focus_count;
    පූර්ණ_සංඛ්‍යා pointer_focus_count;
    පූර්ණ_සංඛ්‍යා active_touch_count;

    sa_nracanaa
    {
        dviguu_na x;
        dviguu_na y;
    } pointer_scale;

    // The in-flight window size request.
    sa_nracanaa
    {
        // The requested logical window size.
        පූර්ණ_සංඛ්‍යා logical_width;
        පූර්ණ_සංඛ්‍යා logical_height;

        // The size of the window in pixels, when using screen space scaling.
        පූර්ණ_සංඛ්‍යා pixel_width;
        පූර්ණ_සංඛ්‍යා pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    sa_nracanaa
    {
        // The size of the underlying window.
        පූර්ණ_සංඛ්‍යා logical_width;
        පූර්ණ_සංඛ්‍යා logical_height;

        // The size of the window backbuffer in pixels.
        පූර්ණ_සංඛ්‍යා pixel_width;
        පූර්ණ_සංඛ්‍යා pixel_height;

        // The dimensions of the active viewport, in logical units.
        පූර්ණ_සංඛ්‍යා viewport_width;
        පූර්ණ_සංඛ්‍යා viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    sa_nracanaa
    {
        පූර්ණ_සංඛ්‍යා width;
        පූර්ණ_සංඛ්‍යා height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    sa_nracanaa
    {
        // Minimum allowed logical window size.
        පූර්ණ_සංඛ්‍යා min_width;
        පූර්ණ_සංඛ්‍යා min_height;
    } system_limits;

    sa_nracanaa
    {
        පූර්ණ_සංඛ්‍යා width;
        පූර්ණ_සංඛ්‍යා height;
    } toplevel_bounds;

    sa_nracanaa
    {
        sa_nracanaa wl_surface *surface;
        sa_nracanaa wl_subsurface *subsurface;
        sa_nracanaa wl_buffer *buffer;
        sa_nracanaa wp_viewport *viewport;

        පූර්ණ_සංඛ්‍යා offset_x;
        පූර්ණ_සංඛ්‍යා offset_y;

        bool mapped;
        bool opaque;
    } mask;

    sa_nracanaa
    {
        පූර්ණ_සංඛ්‍යා hint;
        පූර්ණ_සංඛ්‍යා purpose;
        bool active;
    } text_input_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    පූර්ණ_සංඛ්‍යා pending_state_deadline_count;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    පූර්ණ_සංඛ්‍යා icc_fd;
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

    sa_nracanaa wl_list external_window_list_link;
};

extern void Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
extern void Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
extern void Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
extern SDL_FullscreenResult Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
extern void Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
extern void Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
extern bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
extern bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
extern bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
extern void Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
extern void Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
extern void Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
extern bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
extern bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
extern void Wayland_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
extern void Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
extern void Wayland_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
extern void Wayland_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
extern void Wayland_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, පූර්ණ_සංඛ්‍යා *w, පූර්ණ_සංඛ්‍යා *h);
extern SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
extern bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
extern bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
extern bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, float opacity);
extern void Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
extern void Wayland_ShowWindowSystemMenu(SDL_Window *window, පූර්ණ_සංඛ්‍යා x, පූර්ණ_සංඛ්‍යා y);
extern void Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
extern bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
extern bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
extern bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
extern float Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
extern void *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
extern void Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

extern bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
extern bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
extern bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
extern bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

extern void Wayland_RemoveOutputFromWindow(SDL_WindowData *window, SDL_DisplayData *display_data);
extern void Wayland_UpdateWindowPosition(SDL_Window *window);

#endif // SDL_waylandwindow_h_
