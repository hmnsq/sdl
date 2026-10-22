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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_waylandwindow_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_waylandwindow_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_touch_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandshmbuffer.h"

ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
    SDL_ਖਿੜਕੀ *sdlwindow;
    SDL_Video_ਅੰਕੜੇ *wayland_ਅੰਕੜੇ;
    ਬਣਤਰ wl_surface *surface;
    ਬਣਤਰ wl_callback *gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_callback;
    ਬਣਤਰ wl_event_ਕਤਾਰ *gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_event_ਕਤਾਰ;
    ਬਣਤਰ wl_surface *gles_ਅਦਲਾ_ਬਦਲੀ_ਚੌਖਟਾ_surface_wrapper;
    ਬਣਤਰ wl_callback *surface_ਚੌਖਟਾ_callback;

    ਸੰਘ
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBDECOR_H
        ਬਣਤਰ
        {
            ਬਣਤਰ libdecor_ਚੌਖਟਾ *ਚੌਖਟਾ;
        } libdecor;
#ਜੇ_ਅੰਤ
        ਬਣਤਰ
        {
            ਬਣਤਰ xdg_surface *surface;
            ਸੰਘ
            {
                ਬਣਤਰ
                {
                    ਬਣਤਰ xdg_toplevel *xdg_toplevel;
                } toplevel;
                ਬਣਤਰ
                {
                    ਬਣਤਰ xdg_popup *xdg_popup;
                    ਬਣਤਰ xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    ਗਿਣਤੀ
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    ਗਿਣਤੀ
    {
        WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_ਉਡੀਕ_FOR_ਚੌਖਟਾ,
        WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_ਸਥਿਤੀ_SHOWN
    } shell_surface_ਸਥਿਤੀ;
    ਗਿਣਤੀ
    {
        WAYLAND_WM_CAPS_ਖਿੜਕੀ_MENU = 0x01,
        WAYLAND_WM_CAPS_MAXIMIZE = 0x02,
        WAYLAND_WM_CAPS_FULLSCREEN = 0x04,
        WAYLAND_WM_CAPS_MINIMIZE = 0x08,

        WAYLAND_WM_CAPS_ALL = WAYLAND_WM_CAPS_ਖਿੜਕੀ_MENU |
                              WAYLAND_WM_CAPS_MAXIMIZE |
                              WAYLAND_WM_CAPS_FULLSCREEN |
                              WAYLAND_WM_CAPS_MINIMIZE
    } wm_caps;
    ਗਿਣਤੀ
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_ਖੱਬਾ = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_ਸੱਜਾ = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_ਸਿਖਰ = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    ਗਿਣਤੀ
    {
        WAYLAND_RESIZE_ਕਿਨਾਰਾ_LR = 0x01,
        WAYLAND_RESIZE_ਕਿਨਾਰਾ_TB = 0x02,
        WAYLAND_RESIZE_ਕਿਨਾਰਾ_ਕੋਨਾ = WAYLAND_RESIZE_ਕਿਨਾਰਾ_LR | WAYLAND_RESIZE_ਕਿਨਾਰਾ_TB,
    } resize_ਕਿਨਾਰਾ;

    ਬਣਤਰ wl_egl_ਖਿੜਕੀ *egl_ਖਿੜਕੀ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#ਜੇ_ਅੰਤ
    ਬਣਤਰ zxdg_toplevel_decoration_v1 *server_decoration;
    ਬਣਤਰ zwp_idle_inhibitor_v1 *idle_inhibitor;
    ਬਣਤਰ xdg_activation_token_v1 *activation_token;
    ਬਣਤਰ wp_viewport *viewport;
    ਬਣਤਰ wp_fractional_scale_v1 *fractional_scale;
    ਬਣਤਰ zxdg_exported_v2 *exported;
    ਬਣਤਰ xdg_dialog_v1 *xdg_dialog_v1;
    ਬਣਤਰ wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    ਬਣਤਰ xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    ਬਣਤਰ frog_color_managed_surface *frog_color_managed_surface;
    ਬਣਤਰ wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    ਬਣਤਰ xdg_toplevel_session_v1 *xdg_toplevel_session;

    ਬਣਤਰ Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt ਅਦਲਾ_ਬਦਲੀ_interval_ready;

    SDL_Display_ਅੰਕੜੇ **outputs;
    ਪੂਰਨ ਅੰਕ_outputs;

    ਅੱਖਰ *app_id;
    ਅੱਖਰ *session_id;
    ਦੁੱਗਣਾ scale_ਗੁਣਕ_2;

    ਬਣਤਰ wl_ਬਫਰ **icon_buffers;
    ਪੂਰਨ icon_ਬਫਰ_ਗਿਣਤੀ;

    // Keyboard, pointer, and touch focus refcount.
    ਪੂਰਨ keyboard_focus_ਗਿਣਤੀ;
    ਪੂਰਨ ਸੂਚਕ_focus_ਗਿਣਤੀ;
    ਪੂਰਨ ਸਰਗਰਮ_touch_ਗਿਣਤੀ;

    ਬਣਤਰ
    {
        ਦੁੱਗਣਾ x;
        ਦੁੱਗਣਾ y;
    } ਸੂਚਕ_scale;

    // The in-flight window size request.
    ਬਣਤਰ
    {
        // The requested logical window size.
        ਪੂਰਨ logical_ਚੌੜਾਈ;
        ਪੂਰਨ logical_ਉਚਾਈ;

        // The size of the window in pixels, when using screen space scaling.
        ਪੂਰਨ pixel_ਚੌੜਾਈ;
        ਪੂਰਨ pixel_ਉਚਾਈ;
    } requested;

    // The current size of the window and drawable backing store.
    ਬਣਤਰ
    {
        // The size of the underlying window.
        ਪੂਰਨ logical_ਚੌੜਾਈ;
        ਪੂਰਨ logical_ਉਚਾਈ;

        // The size of the window backbuffer in pixels.
        ਪੂਰਨ pixel_ਚੌੜਾਈ;
        ਪੂਰਨ pixel_ਉਚਾਈ;

        // The dimensions of the active viewport, in logical units.
        ਪੂਰਨ viewport_ਚੌੜਾਈ;
        ਪੂਰਨ viewport_ਉਚਾਈ;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    ਬਣਤਰ
    {
        ਪੂਰਨ ਚੌੜਾਈ;
        ਪੂਰਨ ਉਚਾਈ;
        bool insets_apply;
    } ਆਖਰੀ_configure;

    // System enforced window size limits.
    ਬਣਤਰ
    {
        // Minimum allowed logical window size.
        ਪੂਰਨ min_ਚੌੜਾਈ_2;
        ਪੂਰਨ min_ਉਚਾਈ_2;
    } system_limits;

    ਬਣਤਰ
    {
        ਪੂਰਨ ਚੌੜਾਈ;
        ਪੂਰਨ ਉਚਾਈ;
    } toplevel_bounds;

    ਬਣਤਰ
    {
        ਬਣਤਰ wl_surface *surface;
        ਬਣਤਰ wl_subsurface *subsurface;
        ਬਣਤਰ wl_ਬਫਰ *ਬਫਰ_2;
        ਬਣਤਰ wp_viewport *viewport;

        ਪੂਰਨ ਵਿੱਥ_x;
        ਪੂਰਨ ਵਿੱਥ_y;

        bool mapped;
        bool opaque;
    } ਨਕਾਬ;

    ਬਣਤਰ
    {
        ਪੂਰਨ hint;
        ਪੂਰਨ purpose;
        bool ਸਰਗਰਮ;
    } ਪਾਠ_ਨਿਵੇਸ਼_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID ਆਖਰੀ_display_ID;
    ਪੂਰਨ pending_state_deadline_ਗਿਣਤੀ;
    Uint64 ਆਖਰੀ_focus_event_ਸਮਾਂ_ns;
    Uint64 ਆਖਰੀ_resize_event_ਸਮਾਂ_ns;
    ਪੂਰਨ icc_fd;
    Uint32 icc_ਮਾਪ;
    bool floating;
    bool suspended;
    bool resizing;
    bool ਸਰਗਰਮ;
    bool pending_config_ack;
    bool pending_state_commit;
    bool limits_ਬਦਲਿਆ;
    bool is_fullscreen;
    bool fullscreen_exclusive;
    bool drop_fullscreen_ਬੇਨਤੀਆਂ;
    bool showing_ਖਿੜਕੀ;
    bool fullscreen_was_positioned;
    bool show_hide_sync_required;
    bool scale_ਮੰਜ਼ਿਲ_display;
    bool reparenting_required;
    bool double_ਬਫਰ;
    bool ਮੰਨਦਾ_drag_and_drop;
    bool enable_insets;

    SDL_ਪ੍ਰਾਪਤੀ_Test_ਨਤੀਜਾ ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ;

    ਬਣਤਰ wl_list external_ਖਿੜਕੀ_list_link;
};

ਬਾਹਰੀ ਖਾਲੀ Wayland_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ SDL_Fullscreen_ਨਤੀਜਾ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed);
ਬਾਹਰੀ bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Bordered(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool bordered);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable);
ਬਾਹਰੀ bool Wayland_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਬਾਹਰੀ bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *w, ਪੂਰਨ *h);
ਬਾਹਰੀ SDL_DisplayID Wayland_Get_Display_For_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ *ਮਾਪਾ_ਖਿੜਕੀ);
ਬਾਹਰੀ bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Modal(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool modal);
ਬਾਹਰੀ bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Opacity(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ opacity);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Show_ਖਿੜਕੀ_System_Menu(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ x, ਪੂਰਨ y);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
ਬਾਹਰੀ bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Icon(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *icon);
ਬਾਹਰੀ bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_Focusable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool focusable);
ਬਾਹਰੀ ਦਸ਼ਮਲਵ Wayland_Get_ਖਿੜਕੀ_Content_Scale(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ *Wayland_Get_ਖਿੜਕੀ_ICCProfile(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, size_t *ਮਾਪ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_AcceptDragAndDrop(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool accept);

ਬਾਹਰੀ bool Wayland_ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool enabled);
ਬਾਹਰੀ bool Wayland_Flash_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_FlashOperation operation);
ਬਾਹਰੀ bool Wayland_Sync_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Wayland_Reconfigure_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ_Flags flags);

ਬਾਹਰੀ ਖਾਲੀ Wayland_Remove_Output_From_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ, SDL_Display_ਅੰਕੜੇ *display_ਅੰਕੜੇ);
ਬਾਹਰੀ ਖਾਲੀ Wayland_Update_ਖਿੜਕੀ_Position(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);

#ਜੇ_ਅੰਤ // SDL_waylandwindow_h_
