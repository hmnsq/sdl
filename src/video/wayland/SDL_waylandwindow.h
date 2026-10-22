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

#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_waylandwindow_h_
#تعریف_کرو SDL_waylandwindow_h_

#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_touch_c.h"

#شامل "SDL_waylandvideo.h"
#شامل "SDL_waylandshmbuffer.h"

ساخت SDL_کھڑکی_ڈیٹا
{
    SDL_کھڑکی *sdlwindow;
    SDL_Video_ڈیٹا *wayland_ڈیٹا;
    ساخت wl_surface *surface;
    ساخت wl_callback *gles_تبادلہ_چوکھٹا_callback;
    ساخت wl_event_قطار *gles_تبادلہ_چوکھٹا_event_قطار;
    ساخت wl_surface *gles_تبادلہ_چوکھٹا_surface_wrapper;
    ساخت wl_callback *surface_چوکھٹا_callback;

    اتحاد
    {
#اگر_تعریف_شدہ HAVE_LIBDECOR_H
        ساخت
        {
            ساخت libdecor_چوکھٹا *چوکھٹا;
        } libdecor;
#اگر_ختم
        ساخت
        {
            ساخت xdg_surface *surface;
            اتحاد
            {
                ساخت
                {
                    ساخت xdg_toplevel *xdg_toplevel;
                } toplevel;
                ساخت
                {
                    ساخت xdg_popup *xdg_popup;
                    ساخت xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    شمار
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    شمار
    {
        WAYLAND_SHELL_SURFACE_حالت_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکھٹا,
        WAYLAND_SHELL_SURFACE_حالت_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_حالت_SHOWN
    } shell_surface_حالت;
    شمار
    {
        WAYLAND_WM_CAPS_کھڑکی_MENU = 0x01,
        WAYLAND_WM_CAPS_MAXIMIZE = 0x02,
        WAYLAND_WM_CAPS_FULLSCREEN = 0x04,
        WAYLAND_WM_CAPS_MINIMIZE = 0x08,

        WAYLAND_WM_CAPS_ALL = WAYLAND_WM_CAPS_کھڑکی_MENU |
                              WAYLAND_WM_CAPS_MAXIMIZE |
                              WAYLAND_WM_CAPS_FULLSCREEN |
                              WAYLAND_WM_CAPS_MINIMIZE
    } wm_caps;
    شمار
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_بایاں = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_دایاں = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    شمار
    {
        WAYLAND_RESIZE_کنارہ_LR = 0x01,
        WAYLAND_RESIZE_کنارہ_TB = 0x02,
        WAYLAND_RESIZE_کنارہ_کونا = WAYLAND_RESIZE_کنارہ_LR | WAYLAND_RESIZE_کنارہ_TB,
    } resize_کنارہ;

    ساخت wl_egl_کھڑکی *egl_کھڑکی;
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#اگر_ختم
    ساخت zxdg_toplevel_decoration_v1 *server_decoration;
    ساخت zwp_idle_inhibitor_v1 *idle_inhibitor;
    ساخت xdg_activation_token_v1 *activation_token;
    ساخت wp_viewport *viewport;
    ساخت wp_fractional_scale_v1 *fractional_scale;
    ساخت zxdg_exported_v2 *exported;
    ساخت xdg_dialog_v1 *xdg_dialog_v1;
    ساخت wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    ساخت xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    ساخت frog_color_managed_surface *frog_color_managed_surface;
    ساخت wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    ساخت xdg_toplevel_session_v1 *xdg_toplevel_session;

    ساخت Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt تبادلہ_interval_ready;

    SDL_Display_ڈیٹا **outputs;
    صحیح عدد_outputs;

    حرف *app_id;
    حرف *session_id;
    دوہرا scale_ضربی_عدد_2;

    ساخت wl_بفر **icon_buffers;
    صحیح icon_بفر_گنتی;

    // Keyboard, pointer, and touch focus refcount.
    صحیح keyboard_focus_گنتی;
    صحیح اشارہ_گر_focus_گنتی;
    صحیح فعال_touch_گنتی;

    ساخت
    {
        دوہرا x;
        دوہرا y;
    } اشارہ_گر_scale;

    // The in-flight window size request.
    ساخت
    {
        // The requested logical window size.
        صحیح logical_چوڑائی;
        صحیح logical_اونچائی;

        // The size of the window in pixels, when using screen space scaling.
        صحیح pixel_چوڑائی;
        صحیح pixel_اونچائی;
    } requested;

    // The current size of the window and drawable backing store.
    ساخت
    {
        // The size of the underlying window.
        صحیح logical_چوڑائی;
        صحیح logical_اونچائی;

        // The size of the window backbuffer in pixels.
        صحیح pixel_چوڑائی;
        صحیح pixel_اونچائی;

        // The dimensions of the active viewport, in logical units.
        صحیح viewport_چوڑائی;
        صحیح viewport_اونچائی;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    ساخت
    {
        صحیح چوڑائی;
        صحیح اونچائی;
        bool insets_apply;
    } آخری_configure;

    // System enforced window size limits.
    ساخت
    {
        // Minimum allowed logical window size.
        صحیح min_چوڑائی_2;
        صحیح min_اونچائی_2;
    } system_limits;

    ساخت
    {
        صحیح چوڑائی;
        صحیح اونچائی;
    } toplevel_bounds;

    ساخت
    {
        ساخت wl_surface *surface;
        ساخت wl_subsurface *subsurface;
        ساخت wl_بفر *بفر_2;
        ساخت wp_viewport *viewport;

        صحیح انحراف_x;
        صحیح انحراف_y;

        bool mapped;
        bool opaque;
    } نقاب;

    ساخت
    {
        صحیح hint;
        صحیح purpose;
        bool فعال;
    } متن_داخلہ_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID آخری_display_ID;
    صحیح pending_state_deadline_گنتی;
    Uint64 آخری_focus_event_وقت_ns;
    Uint64 آخری_resize_event_وقت_ns;
    صحیح icc_fd;
    Uint32 icc_سائز;
    bool floating;
    bool suspended;
    bool resizing;
    bool فعال;
    bool pending_config_ack;
    bool pending_state_commit;
    bool limits_بدلا;
    bool is_fullscreen;
    bool fullscreen_exclusive;
    bool drop_fullscreen_درخواستیں;
    bool showing_کھڑکی;
    bool fullscreen_was_positioned;
    bool show_hide_sync_required;
    bool scale_مقصد_display;
    bool reparenting_required;
    bool double_بفر;
    bool قبول_کرتا_drag_and_drop;
    bool enable_insets;

    SDL_کامیابی_Test_نتیجہ کامیابی_test_نتیجہ;

    ساخت wl_list external_کھڑکی_list_link;
};

خارجی خالی Wayland_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Wayland_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Wayland_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی SDL_Fullscreen_نتیجہ Wayland_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
خارجی خالی Wayland_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Wayland_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Wayland_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Wayland_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجی bool Wayland_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجی خالی Wayland_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Wayland_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered);
خارجی خالی Wayland_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);
خارجی bool Wayland_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجی bool Wayland_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Wayland_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Wayland_سیٹ_کھڑکی_Aspect_تناسب(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Wayland_سیٹ_کھڑکی_Minimum_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Wayland_سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Wayland_Get_کھڑکی_سائز_اندر_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *w, صحیح *h);
خارجی SDL_DisplayID Wayland_Get_Display_For_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Wayland_سیٹ_کھڑکی_والد(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *والد_کھڑکی);
خارجی bool Wayland_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal);
خارجی bool Wayland_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, اعشاری opacity);
خارجی خالی Wayland_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی Wayland_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحیح x, صحیح y);
خارجی خالی Wayland_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
خارجی bool Wayland_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
خارجی bool Wayland_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);
خارجی اعشاری Wayland_Get_کھڑکی_Content_Scale(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی *Wayland_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *سائز);
خارجی خالی Wayland_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept);

خارجی bool Wayland_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled);
خارجی bool Wayland_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation);
خارجی bool Wayland_Sync_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool Wayland_Reconfigure_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags);

خارجی خالی Wayland_Remove_Output_From_کھڑکی(SDL_کھڑکی_ڈیٹا *کھڑکی, SDL_Display_ڈیٹا *display_ڈیٹا);
خارجی خالی Wayland_Update_کھڑکی_Position(SDL_کھڑکی *کھڑکی);

#اگر_ختم // SDL_waylandwindow_h_
