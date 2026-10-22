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

#ضمن "SDL_internal.h"

#که_نه_تعریف_شوی SDL_waylandwindow_h_
#تعریف_کړه SDL_waylandwindow_h_

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_touch_c.h"

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandshmbuffer.h"

بنية SDL_کړکۍ_معلومات
{
    SDL_کړکۍ *sdlwindow;
    SDL_Video_معلومات *wayland_معلومات;
    بنية wl_surface *surface;
    بنية wl_callback *gles_بدلون_چوکاټ_callback;
    بنية wl_event_کتار *gles_بدلون_چوکاټ_event_کتار;
    بنية wl_surface *gles_بدلون_چوکاټ_surface_wrapper;
    بنية wl_callback *surface_چوکاټ_callback;

    اتحاد
    {
#که_تعریف_شوی HAVE_LIBDECOR_H
        بنية
        {
            بنية libdecor_چوکاټ *چوکاټ;
        } libdecor;
#د_که_پای
        بنية
        {
            بنية xdg_surface *surface;
            اتحاد
            {
                بنية
                {
                    بنية xdg_toplevel *xdg_toplevel;
                } toplevel;
                بنية
                {
                    بنية xdg_popup *xdg_popup;
                    بنية xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    تعداد
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    تعداد
    {
        WAYLAND_SHELL_SURFACE_حالت_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکاټ,
        WAYLAND_SHELL_SURFACE_حالت_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_حالت_SHOWN
    } shell_surface_حالت;
    تعداد
    {
        WAYLAND_WM_CAPS_کړکۍ_MENU = 0x01,
        WAYLAND_WM_CAPS_MAXIMIZE = 0x02,
        WAYLAND_WM_CAPS_FULLSCREEN = 0x04,
        WAYLAND_WM_CAPS_MINIMIZE = 0x08,

        WAYLAND_WM_CAPS_ALL = WAYLAND_WM_CAPS_کړکۍ_MENU |
                              WAYLAND_WM_CAPS_MAXIMIZE |
                              WAYLAND_WM_CAPS_FULLSCREEN |
                              WAYLAND_WM_CAPS_MINIMIZE
    } wm_caps;
    تعداد
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_کیڼ = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_ښی = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_سر = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    تعداد
    {
        WAYLAND_RESIZE_څنډه_LR = 0x01,
        WAYLAND_RESIZE_څنډه_TB = 0x02,
        WAYLAND_RESIZE_څنډه_کونج = WAYLAND_RESIZE_څنډه_LR | WAYLAND_RESIZE_څنډه_TB,
    } resize_څنډه;

    بنية wl_egl_کړکۍ *egl_کړکۍ;
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#د_که_پای
    بنية zxdg_toplevel_decoration_v1 *server_decoration;
    بنية zwp_idle_inhibitor_v1 *idle_inhibitor;
    بنية xdg_activation_token_v1 *activation_token;
    بنية wp_viewport *viewport;
    بنية wp_fractional_scale_v1 *fractional_scale;
    بنية zxdg_exported_v2 *exported;
    بنية xdg_dialog_v1 *xdg_dialog_v1;
    بنية wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    بنية xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    بنية frog_color_managed_surface *frog_color_managed_surface;
    بنية wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    بنية xdg_toplevel_session_v1 *xdg_toplevel_session;

    بنية Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt بدلون_interval_ready;

    SDL_Display_معلومات **outputs;
    صحيح عدد_outputs;

    حرف *app_id;
    حرف *session_id;
    مزدوج scale_ضریب_2;

    بنية wl_بفر **icon_buffers;
    صحيح icon_بفر_شمېر;

    // Keyboard, pointer, and touch focus refcount.
    صحيح keyboard_focus_شمېر;
    صحيح اشاره_ګر_focus_شمېر;
    صحيح فعال_touch_شمېر;

    بنية
    {
        مزدوج x;
        مزدوج y;
    } اشاره_ګر_scale;

    // The in-flight window size request.
    بنية
    {
        // The requested logical window size.
        صحيح logical_پلنوالی;
        صحيح logical_لوړوالی;

        // The size of the window in pixels, when using screen space scaling.
        صحيح pixel_پلنوالی;
        صحيح pixel_لوړوالی;
    } requested;

    // The current size of the window and drawable backing store.
    بنية
    {
        // The size of the underlying window.
        صحيح logical_پلنوالی;
        صحيح logical_لوړوالی;

        // The size of the window backbuffer in pixels.
        صحيح pixel_پلنوالی;
        صحيح pixel_لوړوالی;

        // The dimensions of the active viewport, in logical units.
        صحيح viewport_پلنوالی;
        صحيح viewport_لوړوالی;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    بنية
    {
        صحيح پلنوالی;
        صحيح لوړوالی;
        bool insets_apply;
    } وروستی_configure;

    // System enforced window size limits.
    بنية
    {
        // Minimum allowed logical window size.
        صحيح min_پلنوالی_2;
        صحيح min_لوړوالی_2;
    } system_limits;

    بنية
    {
        صحيح پلنوالی;
        صحيح لوړوالی;
    } toplevel_bounds;

    بنية
    {
        بنية wl_surface *surface;
        بنية wl_subsurface *subsurface;
        بنية wl_بفر *بفر_2;
        بنية wp_viewport *viewport;

        صحيح دننه_واټن_x;
        صحيح دننه_واټن_y;

        bool mapped;
        bool opaque;
    } ماسک;

    بنية
    {
        صحيح hint;
        صحيح purpose;
        bool فعال;
    } متن_ننوت_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID وروستی_display_ID;
    صحيح pending_state_deadline_شمېر;
    Uint64 وروستی_focus_event_وخت_ns;
    Uint64 وروستی_resize_event_وخت_ns;
    صحيح icc_fd;
    Uint32 icc_اندازه;
    bool floating;
    bool suspended;
    bool resizing;
    bool فعال;
    bool pending_config_ack;
    bool pending_state_commit;
    bool limits_بدل_شوی;
    bool is_fullscreen;
    bool fullscreen_exclusive;
    bool drop_fullscreen_غوښتنې;
    bool showing_کړکۍ;
    bool fullscreen_was_positioned;
    bool show_hide_sync_required;
    bool scale_منزل_display;
    bool reparenting_required;
    bool double_بفر;
    bool مني_drag_and_drop;
    bool enable_insets;

    SDL_موندنه_Test_پایله موندنه_test_پایله;

    بنية wl_list external_کړکۍ_list_link;
};

خارجي فراغ Wayland_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Wayland_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Wayland_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي SDL_Fullscreen_پایله Wayland_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
خارجي فراغ Wayland_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Wayland_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Wayland_سېټ_کړکۍ_Mouse_Rect(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Wayland_سېټ_کړکۍ_Mouse_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed);
خارجي bool Wayland_سېټ_کړکۍ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed);
خارجي فراغ Wayland_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Wayland_سېټ_کړکۍ_Bordered(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool bordered);
خارجي فراغ Wayland_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool resizable);
خارجي bool Wayland_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props);
خارجي bool Wayland_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Wayland_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Wayland_سېټ_کړکۍ_Aspect_نسبت(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Wayland_سېټ_کړکۍ_Minimum_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Wayland_سېټ_کړکۍ_اعظمي_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Wayland_Get_کړکۍ_اندازه_دننه_Pixels(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *w, صحيح *h);
خارجي SDL_DisplayID Wayland_Get_Display_For_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Wayland_سېټ_کړکۍ_پلار(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_کړکۍ *پلار_کړکۍ);
خارجي bool Wayland_سېټ_کړکۍ_Modal(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool modal);
خارجي bool Wayland_سېټ_کړکۍ_Opacity(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, عائم opacity);
خارجي فراغ Wayland_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ Wayland_Show_کړکۍ_System_Menu(SDL_کړکۍ *کړکۍ, صحيح x, صحيح y);
خارجي فراغ Wayland_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
خارجي bool Wayland_سېټ_کړکۍ_Icon(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *icon);
خارجي bool Wayland_سېټ_کړکۍ_Focusable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool focusable);
خارجي عائم Wayland_Get_کړکۍ_Content_Scale(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ *Wayland_Get_کړکۍ_ICCProfile(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, size_t *اندازه);
خارجي فراغ Wayland_AcceptDragAndDrop(SDL_کړکۍ *کړکۍ, bool accept);

خارجي bool Wayland_سېټ_کړکۍ_موندنه_Test(SDL_کړکۍ *کړکۍ, bool enabled);
خارجي bool Wayland_Flash_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_FlashOperation operation);
خارجي bool Wayland_Sync_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool Wayland_Reconfigure_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_کړکۍ_Flags flags);

خارجي فراغ Wayland_Remove_Output_From_کړکۍ(SDL_کړکۍ_معلومات *کړکۍ, SDL_Display_معلومات *display_معلومات);
خارجي فراغ Wayland_Update_کړکۍ_Position(SDL_کړکۍ *کړکۍ);

#د_که_پای // SDL_waylandwindow_h_
