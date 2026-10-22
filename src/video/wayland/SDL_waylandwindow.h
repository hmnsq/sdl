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

#جيڪڏهن_وصف_نه_ٿيل SDL_waylandwindow_h_
#وصف_ڪريو SDL_waylandwindow_h_

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_touch_c.h"

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandshmbuffer.h"

بنية SDL_دري_معلومات
{
    SDL_دري *sdlwindow;
    SDL_Video_معلومات *wayland_معلومات;
    بنية wl_surface *surface;
    بنية wl_callback *gles_مٽا_سٽا_چوکٺو_callback;
    بنية wl_event_قطار *gles_مٽا_سٽا_چوکٺو_event_قطار;
    بنية wl_surface *gles_مٽا_سٽا_چوکٺو_surface_wrapper;
    بنية wl_callback *surface_چوکٺو_callback;

    اتحاد
    {
#جيڪڏهن_وصف_ٿيل HAVE_LIBDECOR_H
        بنية
        {
            بنية libdecor_چوکٺو *چوکٺو;
        } libdecor;
#جيڪڏهن_پورو
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
        WAYLAND_SHELL_SURFACE_حالت_انتظار_FOR_چوکٺو,
        WAYLAND_SHELL_SURFACE_حالت_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_حالت_SHOWN
    } shell_surface_حالت;
    تعداد
    {
        WAYLAND_WM_CAPS_دري_MENU = 0x01,
        WAYLAND_WM_CAPS_MAXIMIZE = 0x02,
        WAYLAND_WM_CAPS_FULLSCREEN = 0x04,
        WAYLAND_WM_CAPS_MINIMIZE = 0x08,

        WAYLAND_WM_CAPS_ALL = WAYLAND_WM_CAPS_دري_MENU |
                              WAYLAND_WM_CAPS_MAXIMIZE |
                              WAYLAND_WM_CAPS_FULLSCREEN |
                              WAYLAND_WM_CAPS_MINIMIZE
    } wm_caps;
    تعداد
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_کاٻو = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_ساڄو = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_چوٽي = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    تعداد
    {
        WAYLAND_RESIZE_ڪنارو_LR = 0x01,
        WAYLAND_RESIZE_ڪنارو_TB = 0x02,
        WAYLAND_RESIZE_ڪنارو_ڪنڊ = WAYLAND_RESIZE_ڪنارو_LR | WAYLAND_RESIZE_ڪنارو_TB,
    } resize_ڪنارو;

    بنية wl_egl_دري *egl_دري;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#جيڪڏهن_پورو
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

    SDL_AtomicInt مٽا_سٽا_interval_ready;

    SDL_Display_معلومات **outputs;
    صحيح انگ_outputs;

    حرف *app_id;
    حرف *session_id;
    مزدوج scale_ضرب_ڪندڙ_2;

    بنية wl_بفر **icon_buffers;
    صحيح icon_بفر_ڳڻپ;

    // Keyboard, pointer, and touch focus refcount.
    صحيح keyboard_focus_ڳڻپ;
    صحيح اشارو_focus_ڳڻپ;
    صحيح سرگرم_touch_ڳڻپ;

    بنية
    {
        مزدوج x;
        مزدوج y;
    } اشارو_scale;

    // The in-flight window size request.
    بنية
    {
        // The requested logical window size.
        صحيح logical_ويڪر;
        صحيح logical_اوچائي;

        // The size of the window in pixels, when using screen space scaling.
        صحيح pixel_ويڪر;
        صحيح pixel_اوچائي;
    } requested;

    // The current size of the window and drawable backing store.
    بنية
    {
        // The size of the underlying window.
        صحيح logical_ويڪر;
        صحيح logical_اوچائي;

        // The size of the window backbuffer in pixels.
        صحيح pixel_ويڪر;
        صحيح pixel_اوچائي;

        // The dimensions of the active viewport, in logical units.
        صحيح viewport_ويڪر;
        صحيح viewport_اوچائي;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    بنية
    {
        صحيح ويڪر;
        صحيح اوچائي;
        bool insets_apply;
    } آخري_configure;

    // System enforced window size limits.
    بنية
    {
        // Minimum allowed logical window size.
        صحيح min_ويڪر_2;
        صحيح min_اوچائي_2;
    } system_limits;

    بنية
    {
        صحيح ويڪر;
        صحيح اوچائي;
    } toplevel_bounds;

    بنية
    {
        بنية wl_surface *surface;
        بنية wl_subsurface *subsurface;
        بنية wl_بفر *بفر_2;
        بنية wp_viewport *viewport;

        صحيح وٿي_x;
        صحيح وٿي_y;

        bool mapped;
        bool opaque;
    } نقاب;

    بنية
    {
        صحيح hint;
        صحيح purpose;
        bool سرگرم;
    } متن_داخلا_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID آخري_display_ID;
    صحيح pending_state_deadline_ڳڻپ;
    Uint64 آخري_focus_event_وقت_ns;
    Uint64 آخري_resize_event_وقت_ns;
    صحيح icc_fd;
    Uint32 icc_سائيز;
    bool floating;
    bool suspended;
    bool resizing;
    bool سرگرم;
    bool pending_config_ack;
    bool pending_state_commit;
    bool limits_بدليو;
    bool is_fullscreen;
    bool fullscreen_exclusive;
    bool drop_fullscreen_درخواستون;
    bool showing_دري;
    bool fullscreen_was_positioned;
    bool show_hide_sync_required;
    bool scale_منزل_display;
    bool reparenting_required;
    bool double_بفر;
    bool قبولي_drag_and_drop;
    bool enable_insets;

    SDL_ڪاميابي_Test_نتيجو ڪاميابي_test_نتيجو;

    بنية wl_list external_دري_list_link;
};

خارجي فراغ Wayland_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Wayland_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Wayland_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي SDL_Fullscreen_نتيجو Wayland_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
خارجي فراغ Wayland_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Wayland_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Wayland_سيٽ_دري_Mouse_Rect(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Wayland_سيٽ_دري_Mouse_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed);
خارجي bool Wayland_سيٽ_دري_Keyboard_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed);
خارجي فراغ Wayland_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Wayland_سيٽ_دري_Bordered(SDL_VideoDevice *_this, SDL_دري *دري, bool bordered);
خارجي فراغ Wayland_سيٽ_دري_Resizable(SDL_VideoDevice *_this, SDL_دري *دري, bool resizable);
خارجي bool Wayland_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props);
خارجي bool Wayland_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Wayland_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Wayland_سيٽ_دري_Aspect_تناسب(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Wayland_سيٽ_دري_Minimum_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Wayland_سيٽ_دري_وڌ_کان_وڌ_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Wayland_Get_دري_سائيز_اندريون_Pixels(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *w, صحيح *h);
خارجي SDL_DisplayID Wayland_Get_Display_For_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Wayland_سيٽ_دري_والد(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري *والد_دري);
خارجي bool Wayland_سيٽ_دري_Modal(SDL_VideoDevice *_this, SDL_دري *دري, bool modal);
خارجي bool Wayland_سيٽ_دري_Opacity(SDL_VideoDevice *_this, SDL_دري *دري, عائم opacity);
خارجي فراغ Wayland_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ Wayland_Show_دري_System_Menu(SDL_دري *دري, صحيح x, صحيح y);
خارجي فراغ Wayland_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
خارجي bool Wayland_سيٽ_دري_Icon(SDL_VideoDevice *_this, SDL_دري *دري, SDL_Surface *icon);
خارجي bool Wayland_سيٽ_دري_Focusable(SDL_VideoDevice *_this, SDL_دري *دري, bool focusable);
خارجي عائم Wayland_Get_دري_Content_Scale(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ *Wayland_Get_دري_ICCProfile(SDL_VideoDevice *_this, SDL_دري *دري, size_t *سائيز);
خارجي فراغ Wayland_AcceptDragAndDrop(SDL_دري *دري, bool accept);

خارجي bool Wayland_سيٽ_دري_ڪاميابي_Test(SDL_دري *دري, bool enabled);
خارجي bool Wayland_Flash_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_FlashOperation operation);
خارجي bool Wayland_Sync_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool Wayland_Reconfigure_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري_Flags flags);

خارجي فراغ Wayland_Remove_Output_From_دري(SDL_دري_معلومات *دري, SDL_Display_معلومات *display_معلومات);
خارجي فراغ Wayland_Update_دري_Position(SDL_دري *دري);

#جيڪڏهن_پورو // SDL_waylandwindow_h_
