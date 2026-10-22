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

#اگر_تعریف_نشده SDL_waylandwindow_h_
#تعریف_کن SDL_waylandwindow_h_

#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_touch_c.h"

#ضمن "SDL_waylandvideo.h"
#ضمن "SDL_waylandshmbuffer.h"

بنية SDL_پنجره_داده
{
    SDL_پنجره *sdlwindow;
    SDL_Video_داده *wayland_داده;
    بنية wl_surface *surface;
    بنية wl_callback *gles_جابجا_قاب_callback;
    بنية wl_event_صف *gles_جابجا_قاب_event_صف;
    بنية wl_surface *gles_جابجا_قاب_surface_wrapper;
    بنية wl_callback *surface_قاب_callback;

    اتحاد
    {
#اگر_تعریف_شده HAVE_LIBDECOR_H
        بنية
        {
            بنية libdecor_قاب *قاب;
        } libdecor;
#پایان_اگر
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
        WAYLAND_SHELL_SURFACE_وضعیت_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_وضعیت_انتظار_FOR_قاب,
        WAYLAND_SHELL_SURFACE_وضعیت_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_وضعیت_SHOWN
    } shell_surface_وضعیت;
    تعداد
    {
        WAYLAND_WM_CAPS_پنجره_MENU = 0x01,
        WAYLAND_WM_CAPS_MAXIMIZE = 0x02,
        WAYLAND_WM_CAPS_FULLSCREEN = 0x04,
        WAYLAND_WM_CAPS_MINIMIZE = 0x08,

        WAYLAND_WM_CAPS_ALL = WAYLAND_WM_CAPS_پنجره_MENU |
                              WAYLAND_WM_CAPS_MAXIMIZE |
                              WAYLAND_WM_CAPS_FULLSCREEN |
                              WAYLAND_WM_CAPS_MINIMIZE
    } wm_caps;
    تعداد
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_چپ = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_راست = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_بالاترین = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    تعداد
    {
        WAYLAND_RESIZE_یال_LR = 0x01,
        WAYLAND_RESIZE_یال_TB = 0x02,
        WAYLAND_RESIZE_یال_گوشه = WAYLAND_RESIZE_یال_LR | WAYLAND_RESIZE_یال_TB,
    } resize_یال;

    بنية wl_egl_پنجره *egl_پنجره;
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#پایان_اگر
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

    SDL_AtomicInt جابجا_interval_ready;

    SDL_Display_داده **outputs;
    صحيح رقم_outputs;

    حرف *app_id;
    حرف *session_id;
    مزدوج scale_ضریب_2;

    بنية wl_میانگیر **icon_buffers;
    صحيح icon_میانگیر_شمار;

    // Keyboard, pointer, and touch focus refcount.
    صحيح keyboard_focus_شمار;
    صحيح اشاره_گر_focus_شمار;
    صحيح فعال_touch_شمار;

    بنية
    {
        مزدوج x;
        مزدوج y;
    } اشاره_گر_scale;

    // The in-flight window size request.
    بنية
    {
        // The requested logical window size.
        صحيح logical_عرض;
        صحيح logical_ارتفاع;

        // The size of the window in pixels, when using screen space scaling.
        صحيح pixel_عرض;
        صحيح pixel_ارتفاع;
    } requested;

    // The current size of the window and drawable backing store.
    بنية
    {
        // The size of the underlying window.
        صحيح logical_عرض;
        صحيح logical_ارتفاع;

        // The size of the window backbuffer in pixels.
        صحيح pixel_عرض;
        صحيح pixel_ارتفاع;

        // The dimensions of the active viewport, in logical units.
        صحيح viewport_عرض;
        صحيح viewport_ارتفاع;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    بنية
    {
        صحيح عرض;
        صحيح ارتفاع;
        bool insets_apply;
    } آخرین_configure;

    // System enforced window size limits.
    بنية
    {
        // Minimum allowed logical window size.
        صحيح min_عرض_2;
        صحيح min_ارتفاع_2;
    } system_limits;

    بنية
    {
        صحيح عرض;
        صحيح ارتفاع;
    } toplevel_bounds;

    بنية
    {
        بنية wl_surface *surface;
        بنية wl_subsurface *subsurface;
        بنية wl_میانگیر *میانگیر_2;
        بنية wp_viewport *viewport;

        صحيح جابه_جایی_x;
        صحيح جابه_جایی_y;

        bool mapped;
        bool opaque;
    } ماسک;

    بنية
    {
        صحيح hint;
        صحيح purpose;
        bool فعال;
    } متن_درون_داد_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID آخرین_display_ID;
    صحيح pending_state_deadline_شمار;
    Uint64 آخرین_focus_event_زمان_ns;
    Uint64 آخرین_resize_event_زمان_ns;
    صحيح icc_fd;
    Uint32 icc_اندازه;
    bool floating;
    bool suspended;
    bool resizing;
    bool فعال;
    bool pending_config_ack;
    bool pending_state_commit;
    bool limits_تغییریافته;
    bool is_fullscreen;
    bool fullscreen_exclusive;
    bool drop_fullscreen_درخواستها;
    bool showing_پنجره;
    bool fullscreen_was_positioned;
    bool show_hide_sync_required;
    bool scale_مقصد_display;
    bool reparenting_required;
    bool double_میانگیر;
    bool میپذیرد_drag_and_drop;
    bool enable_insets;

    SDL_اصابت_Test_نتیجه اصابت_test_نتیجه;

    بنية wl_list external_پنجره_list_link;
};

خارجي فراغ Wayland_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Wayland_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Wayland_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي SDL_Fullscreen_نتیجه Wayland_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
خارجي فراغ Wayland_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Wayland_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Wayland_مجموعه_پنجره_Mouse_Rect(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Wayland_مجموعه_پنجره_Mouse_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed);
خارجي bool Wayland_مجموعه_پنجره_Keyboard_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed);
خارجي فراغ Wayland_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Wayland_مجموعه_پنجره_Bordered(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool bordered);
خارجي فراغ Wayland_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool resizable);
خارجي bool Wayland_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props);
خارجي bool Wayland_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Wayland_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Wayland_مجموعه_پنجره_Aspect_نسبت(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Wayland_مجموعه_پنجره_Minimum_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Wayland_مجموعه_پنجره_بیشینه_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Wayland_Get_پنجره_اندازه_درون_Pixels(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *w, صحيح *h);
خارجي SDL_DisplayID Wayland_Get_Display_For_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Wayland_مجموعه_پنجره_والد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_پنجره *والد_پنجره);
خارجي bool Wayland_مجموعه_پنجره_Modal(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool modal);
خارجي bool Wayland_مجموعه_پنجره_Opacity(SDL_VideoDevice *_this, SDL_پنجره *پنجره, عائم opacity);
خارجي فراغ Wayland_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ Wayland_Show_پنجره_System_Menu(SDL_پنجره *پنجره, صحيح x, صحيح y);
خارجي فراغ Wayland_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
خارجي bool Wayland_مجموعه_پنجره_Icon(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *icon);
خارجي bool Wayland_مجموعه_پنجره_Focusable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool focusable);
خارجي عائم Wayland_Get_پنجره_Content_Scale(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ *Wayland_Get_پنجره_ICCProfile(SDL_VideoDevice *_this, SDL_پنجره *پنجره, size_t *اندازه);
خارجي فراغ Wayland_AcceptDragAndDrop(SDL_پنجره *پنجره, bool accept);

خارجي bool Wayland_مجموعه_پنجره_اصابت_Test(SDL_پنجره *پنجره, bool enabled);
خارجي bool Wayland_Flash_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_FlashOperation operation);
خارجي bool Wayland_Sync_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool Wayland_Reconfigure_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_پنجره_Flags flags);

خارجي فراغ Wayland_Remove_Output_From_پنجره(SDL_پنجره_داده *پنجره, SDL_Display_داده *display_داده);
خارجي فراغ Wayland_Update_پنجره_Position(SDL_پنجره *پنجره);

#پایان_اگر // SDL_waylandwindow_h_
