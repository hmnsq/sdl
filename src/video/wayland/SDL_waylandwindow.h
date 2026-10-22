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

#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_waylandwindow_h_
#घोषणा SDL_waylandwindow_h_

#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_touch_c.h"

#समावेश "SDL_waylandvideo.h"
#समावेश "SDL_waylandshmbuffer.h"

काष्ठा SDL_Window_तथ्य
{
    SDL_Window *sdlwindow;
    SDL_Video_तथ्य *wayland_तथ्य;
    काष्ठा wl_surface *surface;
    काष्ठा wl_callback *gles_swap_frame_callback;
    काष्ठा wl_event_queue *gles_swap_frame_event_queue;
    काष्ठा wl_surface *gles_swap_frame_surface_wrapper;
    काष्ठा wl_callback *surface_frame_callback;

    जोड़
    {
#अगर_घोषित HAVE_LIBDECOR_H
        काष्ठा
        {
            काष्ठा libdecor_frame *frame;
        } libdecor;
#पूर्ण_अगर
        काष्ठा
        {
            काष्ठा xdg_surface *surface;
            जोड़
            {
                काष्ठा
                {
                    काष्ठा xdg_toplevel *xdg_toplevel;
                } toplevel;
                काष्ठा
                {
                    काष्ठा xdg_popup *xdg_popup;
                    काष्ठा xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    क्रमागत
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    क्रमागत
    {
        WAYLAND_SHELL_SURFACE_STATUS_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_STATUS_WAITING_FOR_FRAME,
        WAYLAND_SHELL_SURFACE_STATUS_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_STATUS_SHOWN
    } shell_surface_status;
    क्रमागत
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
    क्रमागत
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_बायाँ = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_दायाँ = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_शीर्ष = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    क्रमागत
    {
        WAYLAND_RESIZE_EDGE_LR = 0x01,
        WAYLAND_RESIZE_EDGE_TB = 0x02,
        WAYLAND_RESIZE_EDGE_CORNER = WAYLAND_RESIZE_EDGE_LR | WAYLAND_RESIZE_EDGE_TB,
    } resize_edge;

    काष्ठा wl_egl_window *egl_window;
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#पूर्ण_अगर
    काष्ठा zxdg_toplevel_decoration_v1 *server_decoration;
    काष्ठा zwp_idle_inhibitor_v1 *idle_inhibitor;
    काष्ठा xdg_activation_token_v1 *activation_token;
    काष्ठा wp_viewport *viewport;
    काष्ठा wp_fractional_scale_v1 *fractional_scale;
    काष्ठा zxdg_exported_v2 *exported;
    काष्ठा xdg_dialog_v1 *xdg_dialog_v1;
    काष्ठा wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    काष्ठा xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    काष्ठा frog_color_managed_surface *frog_color_managed_surface;
    काष्ठा wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    काष्ठा xdg_toplevel_session_v1 *xdg_toplevel_session;

    काष्ठा Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt swap_interval_ready;

    SDL_Display_तथ्य **outputs;
    पूर्णांक अंक_outputs;

    अक्षर *app_id;
    अक्षर *session_id;
    द्विगुन scale_factor;

    काष्ठा wl_बफर **icon_buffers;
    पूर्णांक icon_बफर_गिनती;

    // Keyboard, pointer, and touch focus refcount.
    पूर्णांक keyboard_focus_गिनती;
    पूर्णांक pointer_focus_गिनती;
    पूर्णांक active_touch_गिनती;

    काष्ठा
    {
        द्विगुन x;
        द्विगुन y;
    } pointer_scale;

    // The in-flight window size request.
    काष्ठा
    {
        // The requested logical window size.
        पूर्णांक logical_width;
        पूर्णांक logical_height;

        // The size of the window in pixels, when using screen space scaling.
        पूर्णांक pixel_width;
        पूर्णांक pixel_height;
    } requested;

    // The current size of the window and drawable backing store.
    काष्ठा
    {
        // The size of the underlying window.
        पूर्णांक logical_width;
        पूर्णांक logical_height;

        // The size of the window backbuffer in pixels.
        पूर्णांक pixel_width;
        पूर्णांक pixel_height;

        // The dimensions of the active viewport, in logical units.
        पूर्णांक viewport_width;
        पूर्णांक viewport_height;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    काष्ठा
    {
        पूर्णांक width;
        पूर्णांक height;
        bool insets_apply;
    } last_configure;

    // System enforced window size limits.
    काष्ठा
    {
        // Minimum allowed logical window size.
        पूर्णांक min_width;
        पूर्णांक min_height;
    } system_limits;

    काष्ठा
    {
        पूर्णांक width;
        पूर्णांक height;
    } toplevel_bounds;

    काष्ठा
    {
        काष्ठा wl_surface *surface;
        काष्ठा wl_subsurface *subsurface;
        काष्ठा wl_बफर *बफर_2;
        काष्ठा wp_viewport *viewport;

        पूर्णांक offset_x;
        पूर्णांक offset_y;

        bool mapped;
        bool opaque;
    } mask;

    काष्ठा
    {
        पूर्णांक hint;
        पूर्णांक purpose;
        bool active;
    } text_निवेश_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID last_displayID;
    पूर्णांक pending_state_deadline_गिनती;
    Uint64 last_focus_event_time_ns;
    Uint64 last_resize_event_time_ns;
    पूर्णांक icc_fd;
    Uint32 icc_आकार;
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
    bool double_बफर;
    bool accepts_drag_and_drop;
    bool enable_insets;

    SDL_Hit_Test_परिणाम hit_test_परिणाम;

    काष्ठा wl_list external_window_list_link;
};

बाह्य व्योम Wayland_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Wayland_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Wayland_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य SDL_Fullscreen_परिणाम Wayland_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
बाह्य व्योम Wayland_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Wayland_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Wayland_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Wayland_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य bool Wayland_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य व्योम Wayland_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Wayland_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
बाह्य व्योम Wayland_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
बाह्य bool Wayland_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य bool Wayland_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Wayland_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Wayland_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Wayland_Set_Window_Minimum_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Wayland_Set_Window_Maximum_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Wayland_Get_Window_आकार_In_Pixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *w, पूर्णांक *h);
बाह्य SDL_DisplayID Wayland_GetDisplayForWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Wayland_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent_window);
बाह्य bool Wayland_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
बाह्य bool Wayland_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, भग्न opacity);
बाह्य व्योम Wayland_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम Wayland_ShowWindowSystemMenu(SDL_Window *window, पूर्णांक x, पूर्णांक y);
बाह्य व्योम Wayland_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
बाह्य bool Wayland_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
बाह्य bool Wayland_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
बाह्य भग्न Wayland_GetWindowContentScale(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम *Wayland_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, माप_प्रकार *आकार);
बाह्य व्योम Wayland_AcceptDragAndDrop(SDL_Window *window, bool accept);

बाह्य bool Wayland_SetWindowHitTest(SDL_Window *window, bool enabled);
बाह्य bool Wayland_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
बाह्य bool Wayland_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Wayland_ReconfigureWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_WindowFlags flags);

बाह्य व्योम Wayland_RemoveOutputFromWindow(SDL_Window_तथ्य *window, SDL_Display_तथ्य *display_तथ्य);
बाह्य व्योम Wayland_UpdateWindowPosition(SDL_Window *window);

#पूर्ण_अगर // SDL_waylandwindow_h_
