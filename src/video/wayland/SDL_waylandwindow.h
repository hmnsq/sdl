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

#جے_بنا_تعریف SDL_waylandwindow_h_
#تعریف_کرو SDL_waylandwindow_h_

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_touch_c.h"

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandshmbuffer.h"

بنية SDL_کھڑکی_انکڑے
{
    SDL_کھڑکی *sdlwindow;
    SDL_Video_انکڑے *wayland_انکڑے;
    بنية wl_surface *surface;
    بنية wl_callback *gles_وٹاندرا_چوکھٹا_callback;
    بنية wl_event_قطار *gles_وٹاندرا_چوکھٹا_event_قطار;
    بنية wl_surface *gles_وٹاندرا_چوکھٹا_surface_wrapper;
    بنية wl_callback *surface_چوکھٹا_callback;

    اتحاد
    {
#جے_تعریف_شدہ HAVE_LIBDECOR_H
        بنية
        {
            بنية libdecor_چوکھٹا *چوکھٹا;
        } libdecor;
#جے_انت
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
        WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_حالت_اڈیک_FOR_چوکھٹا,
        WAYLAND_SHELL_SURFACE_حالت_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_حالت_SHOWN
    } shell_surface_حالت;
    تعداد
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
    تعداد
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_بایاں = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_دایاں = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_چوٹی = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    تعداد
    {
        WAYLAND_RESIZE_کنارا_LR = 0x01,
        WAYLAND_RESIZE_کنارا_TB = 0x02,
        WAYLAND_RESIZE_کنارا_کونا = WAYLAND_RESIZE_کنارا_LR | WAYLAND_RESIZE_کنارا_TB,
    } resize_کنارا;

    بنية wl_egl_کھڑکی *egl_کھڑکی;
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#جے_انت
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

    SDL_AtomicInt وٹاندرا_interval_ready;

    SDL_Display_انکڑے **outputs;
    صحيح عدد_outputs;

    حرف *app_id;
    حرف *session_id;
    مزدوج scale_ضارب_2;

    بنية wl_بفر **icon_buffers;
    صحيح icon_بفر_گنتی;

    // Keyboard, pointer, and touch focus refcount.
    صحيح keyboard_focus_گنتی;
    صحيح اشارہ_گر_focus_گنتی;
    صحيح سرگرم_touch_گنتی;

    بنية
    {
        مزدوج x;
        مزدوج y;
    } اشارہ_گر_scale;

    // The in-flight window size request.
    بنية
    {
        // The requested logical window size.
        صحيح logical_چوڑائی;
        صحيح logical_اچائی;

        // The size of the window in pixels, when using screen space scaling.
        صحيح pixel_چوڑائی;
        صحيح pixel_اچائی;
    } requested;

    // The current size of the window and drawable backing store.
    بنية
    {
        // The size of the underlying window.
        صحيح logical_چوڑائی;
        صحيح logical_اچائی;

        // The size of the window backbuffer in pixels.
        صحيح pixel_چوڑائی;
        صحيح pixel_اچائی;

        // The dimensions of the active viewport, in logical units.
        صحيح viewport_چوڑائی;
        صحيح viewport_اچائی;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    بنية
    {
        صحيح چوڑائی;
        صحيح اچائی;
        bool insets_apply;
    } آخری_configure;

    // System enforced window size limits.
    بنية
    {
        // Minimum allowed logical window size.
        صحيح min_چوڑائی_2;
        صحيح min_اچائی_2;
    } system_limits;

    بنية
    {
        صحيح چوڑائی;
        صحيح اچائی;
    } toplevel_bounds;

    بنية
    {
        بنية wl_surface *surface;
        بنية wl_subsurface *subsurface;
        بنية wl_بفر *بفر_2;
        بنية wp_viewport *viewport;

        صحيح وتھ_x;
        صحيح وتھ_y;

        bool mapped;
        bool opaque;
    } نقاب;

    بنية
    {
        صحيح hint;
        صحيح purpose;
        bool سرگرم;
    } متن_داخلہ_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID آخری_display_ID;
    صحيح pending_state_deadline_گنتی;
    Uint64 آخری_focus_event_ویلا_ns;
    Uint64 آخری_resize_event_ویلا_ns;
    صحيح icc_fd;
    Uint32 icc_ناپ;
    bool floating;
    bool suspended;
    bool resizing;
    bool سرگرم;
    bool pending_config_ack;
    bool pending_state_commit;
    bool limits_بدلیا;
    bool is_fullscreen;
    bool fullscreen_exclusive;
    bool drop_fullscreen_بینتیاں;
    bool showing_کھڑکی;
    bool fullscreen_was_positioned;
    bool show_hide_sync_required;
    bool scale_منزل_display;
    bool reparenting_required;
    bool double_بفر;
    bool مندا_drag_and_drop;
    bool enable_insets;

    SDL_کامیابی_Test_نتیجہ کامیابی_test_نتیجہ;

    بنية wl_list external_کھڑکی_list_link;
};

خارجي فراغ Wayland_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Wayland_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Wayland_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي SDL_Fullscreen_نتیجہ Wayland_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
خارجي فراغ Wayland_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Wayland_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Wayland_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Wayland_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجي bool Wayland_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجي فراغ Wayland_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Wayland_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered);
خارجي فراغ Wayland_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);
خارجي bool Wayland_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجي bool Wayland_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Wayland_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Wayland_سیٹ_کھڑکی_Aspect_تناسب(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Wayland_سیٹ_کھڑکی_Minimum_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Wayland_سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Wayland_Get_کھڑکی_ناپ_وچ_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *w, صحيح *h);
خارجي SDL_DisplayID Wayland_Get_Display_For_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Wayland_سیٹ_کھڑکی_ماپا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *ماپا_کھڑکی);
خارجي bool Wayland_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal);
خارجي bool Wayland_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, عائم opacity);
خارجي فراغ Wayland_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ Wayland_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحيح x, صحيح y);
خارجي فراغ Wayland_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
خارجي bool Wayland_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
خارجي bool Wayland_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);
خارجي عائم Wayland_Get_کھڑکی_Content_Scale(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ *Wayland_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *ناپ);
خارجي فراغ Wayland_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept);

خارجي bool Wayland_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled);
خارجي bool Wayland_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation);
خارجي bool Wayland_Sync_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool Wayland_Reconfigure_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی_Flags flags);

خارجي فراغ Wayland_Remove_Output_From_کھڑکی(SDL_کھڑکی_انکڑے *کھڑکی, SDL_Display_انکڑے *display_انکڑے);
خارجي فراغ Wayland_Update_کھڑکی_Position(SDL_کھڑکی *کھڑکی);

#جے_انت // SDL_waylandwindow_h_
