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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_waylandwindow_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_waylandwindow_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_touch_c.h"

#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandshmbuffer.h"

ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
    SDL_ಕಿಟಕಿ *sdlwindow;
    SDL_Video_ದತ್ತಾಂಶ *wayland_ದತ್ತಾಂಶ;
    ರಚನೆ wl_surface *surface;
    ರಚನೆ wl_callback *gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_callback;
    ರಚನೆ wl_event_ಸರತಿ *gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_event_ಸರತಿ;
    ರಚನೆ wl_surface *gles_ಅದಲುಬದಲು_ಚೌಕಟ್ಟು_surface_wrapper;
    ರಚನೆ wl_callback *surface_ಚೌಕಟ್ಟು_callback;

    ಒಕ್ಕೂಟ
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBDECOR_H
        ರಚನೆ
        {
            ರಚನೆ libdecor_ಚೌಕಟ್ಟು *ಚೌಕಟ್ಟು;
        } libdecor;
#ಆದರೆ_ಅಂತ್ಯ
        ರಚನೆ
        {
            ರಚನೆ xdg_surface *surface;
            ಒಕ್ಕೂಟ
            {
                ರಚನೆ
                {
                    ರಚನೆ xdg_toplevel *xdg_toplevel;
                } toplevel;
                ರಚನೆ
                {
                    ರಚನೆ xdg_popup *xdg_popup;
                    ರಚನೆ xdg_positioner *xdg_positioner;
                } popup;
            };

            Uint32 serial;
        } xdg;
    } shell_surface;
    ಎಣಿಕೆ
    {
        WAYLAND_SHELL_SURFACE_TYPE_UNKNOWN = 0,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_TOPLEVEL,
        WAYLAND_SHELL_SURFACE_TYPE_XDG_POPUP,
        WAYLAND_SHELL_SURFACE_TYPE_LIBDECOR,
        WAYLAND_SHELL_SURFACE_TYPE_CUSTOM
    } shell_surface_type;
    ಎಣಿಕೆ
    {
        WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_HIDDEN = 0,
        WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_CONFIGURE,
        WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ_FOR_ಚೌಕಟ್ಟು,
        WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOW_PENDING,
        WAYLAND_SHELL_SURFACE_ಸ್ಥಿತಿ_SHOWN
    } shell_surface_ಸ್ಥಿತಿ;
    ಎಣಿಕೆ
    {
        WAYLAND_WM_CAPS_ಕಿಟಕಿ_MENU = 0x01,
        WAYLAND_WM_CAPS_MAXIMIZE = 0x02,
        WAYLAND_WM_CAPS_FULLSCREEN = 0x04,
        WAYLAND_WM_CAPS_MINIMIZE = 0x08,

        WAYLAND_WM_CAPS_ALL = WAYLAND_WM_CAPS_ಕಿಟಕಿ_MENU |
                              WAYLAND_WM_CAPS_MAXIMIZE |
                              WAYLAND_WM_CAPS_FULLSCREEN |
                              WAYLAND_WM_CAPS_MINIMIZE
    } wm_caps;
    ಎಣಿಕೆ
    {
        WAYLAND_TOPLEVEL_CONSTRAINED_ಎಡ = 0x01,
        WAYLAND_TOPLEVEL_CONSTRAINED_ಬಲ = 0x02,
        WAYLAND_TOPLEVEL_CONSTRAINED_ತುದಿ = 0x04,
        WAYLAND_TOPLEVEL_CONSTRAINED_BOTTOM = 0x08
    } toplevel_constraints;

    ಎಣಿಕೆ
    {
        WAYLAND_RESIZE_ಅಂಚು_LR = 0x01,
        WAYLAND_RESIZE_ಅಂಚು_TB = 0x02,
        WAYLAND_RESIZE_ಅಂಚು_ಮೂಲೆ = WAYLAND_RESIZE_ಅಂಚು_LR | WAYLAND_RESIZE_ಅಂಚು_TB,
    } resize_ಅಂಚು;

    ರಚನೆ wl_egl_ಕಿಟಕಿ *egl_ಕಿಟಕಿ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#ಆದರೆ_ಅಂತ್ಯ
    ರಚನೆ zxdg_toplevel_decoration_v1 *server_decoration;
    ರಚನೆ zwp_idle_inhibitor_v1 *idle_inhibitor;
    ರಚನೆ xdg_activation_token_v1 *activation_token;
    ರಚನೆ wp_viewport *viewport;
    ರಚನೆ wp_fractional_scale_v1 *fractional_scale;
    ರಚನೆ zxdg_exported_v2 *exported;
    ರಚನೆ xdg_dialog_v1 *xdg_dialog_v1;
    ರಚನೆ wp_alpha_modifier_surface_v1 *wp_alpha_modifier_surface_v1;
    ರಚನೆ xdg_toplevel_icon_v1 *xdg_toplevel_icon_v1;
    ರಚನೆ frog_color_managed_surface *frog_color_managed_surface;
    ರಚನೆ wp_color_management_surface_feedback_v1 *wp_color_management_surface_feedback;
    ರಚನೆ xdg_toplevel_session_v1 *xdg_toplevel_session;

    ರಚನೆ Wayland_ColorInfoState *color_info_state;

    SDL_AtomicInt ಅದಲುಬದಲು_interval_ready;

    SDL_Display_ದತ್ತಾಂಶ **outputs;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_outputs;

    ಅಕ್ಷರ *app_id;
    ಅಕ್ಷರ *session_id;
    ದ್ವಿಗುಣ scale_ಗುಣಕ_2;

    ರಚನೆ wl_ಬಫರ್ **icon_buffers;
    ಪೂರ್ಣಾಂಕ icon_ಬಫರ್_ಎಣಿಕೆ;

    // Keyboard, pointer, and touch focus refcount.
    ಪೂರ್ಣಾಂಕ keyboard_focus_ಎಣಿಕೆ;
    ಪೂರ್ಣಾಂಕ ಸೂಚಕ_focus_ಎಣಿಕೆ;
    ಪೂರ್ಣಾಂಕ ಸಕ್ರಿಯ_touch_ಎಣಿಕೆ;

    ರಚನೆ
    {
        ದ್ವಿಗುಣ x;
        ದ್ವಿಗುಣ y;
    } ಸೂಚಕ_scale;

    // The in-flight window size request.
    ರಚನೆ
    {
        // The requested logical window size.
        ಪೂರ್ಣಾಂಕ logical_ಅಗಲ;
        ಪೂರ್ಣಾಂಕ logical_ಎತ್ತರ;

        // The size of the window in pixels, when using screen space scaling.
        ಪೂರ್ಣಾಂಕ pixel_ಅಗಲ;
        ಪೂರ್ಣಾಂಕ pixel_ಎತ್ತರ;
    } requested;

    // The current size of the window and drawable backing store.
    ರಚನೆ
    {
        // The size of the underlying window.
        ಪೂರ್ಣಾಂಕ logical_ಅಗಲ;
        ಪೂರ್ಣಾಂಕ logical_ಎತ್ತರ;

        // The size of the window backbuffer in pixels.
        ಪೂರ್ಣಾಂಕ pixel_ಅಗಲ;
        ಪೂರ್ಣಾಂಕ pixel_ಎತ್ತರ;

        // The dimensions of the active viewport, in logical units.
        ಪೂರ್ಣಾಂಕ viewport_ಅಗಲ;
        ಪೂರ್ಣಾಂಕ viewport_ಎತ್ತರ;
    } current;

    // The last compositor requested parameters; used for deduplication of window geometry configuration.
    ರಚನೆ
    {
        ಪೂರ್ಣಾಂಕ ಅಗಲ;
        ಪೂರ್ಣಾಂಕ ಎತ್ತರ;
        bool insets_apply;
    } ಕೊನೆಯ_configure;

    // System enforced window size limits.
    ರಚನೆ
    {
        // Minimum allowed logical window size.
        ಪೂರ್ಣಾಂಕ min_ಅಗಲ_2;
        ಪೂರ್ಣಾಂಕ min_ಎತ್ತರ_2;
    } system_limits;

    ರಚನೆ
    {
        ಪೂರ್ಣಾಂಕ ಅಗಲ;
        ಪೂರ್ಣಾಂಕ ಎತ್ತರ;
    } toplevel_bounds;

    ರಚನೆ
    {
        ರಚನೆ wl_surface *surface;
        ರಚನೆ wl_subsurface *subsurface;
        ರಚನೆ wl_ಬಫರ್ *ಬಫರ್_2;
        ರಚನೆ wp_viewport *viewport;

        ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_x;
        ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ_y;

        bool mapped;
        bool opaque;
    } ಮುಖವಾಡ;

    ರಚನೆ
    {
        ಪೂರ್ಣಾಂಕ hint;
        ಪೂರ್ಣಾಂಕ purpose;
        bool ಸಕ್ರಿಯ;
    } ಪಠ್ಯ_ಒಳಹರಿವು_props;

    SDL_Rect explicit_geometry;
    SDL_DisplayID ಕೊನೆಯ_display_ID;
    ಪೂರ್ಣಾಂಕ pending_state_deadline_ಎಣಿಕೆ;
    Uint64 ಕೊನೆಯ_focus_event_ಸಮಯ_ns;
    Uint64 ಕೊನೆಯ_resize_event_ಸಮಯ_ns;
    ಪೂರ್ಣಾಂಕ icc_fd;
    Uint32 icc_ಗಾತ್ರ;
    bool floating;
    bool suspended;
    bool resizing;
    bool ಸಕ್ರಿಯ;
    bool pending_config_ack;
    bool pending_state_commit;
    bool limits_ಬದಲಾಯಿತು;
    bool is_fullscreen;
    bool fullscreen_exclusive;
    bool drop_fullscreen_ವಿನಂತಿಗಳು;
    bool showing_ಕಿಟಕಿ;
    bool fullscreen_was_positioned;
    bool show_hide_sync_required;
    bool scale_ಗಮ್ಯ_display;
    bool reparenting_required;
    bool double_ಬಫರ್;
    bool ಸ್ವೀಕರಿಸು_drag_and_drop;
    bool enable_insets;

    SDL_ದೊರಕಿತು_Test_ಫಲಿತಾಂಶ ದೊರಕಿತು_test_ಫಲಿತಾಂಶ;

    ರಚನೆ wl_list external_ಕಿಟಕಿ_list_link;
};

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ SDL_Fullscreen_ಫಲಿತಾಂಶ Wayland_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *_display, SDL_FullscreenOp fullscreen);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Wayland_ಗಣ_ಕಿಟಕಿ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Wayland_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed);
ಬಾಹ್ಯ bool Wayland_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_Bordered(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool bordered);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable);
ಬಾಹ್ಯ bool Wayland_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಬಾಹ್ಯ bool Wayland_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *w, ಪೂರ್ಣಾಂಕ *h);
ಬಾಹ್ಯ SDL_DisplayID Wayland_Get_Display_For_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Wayland_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ_ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Wayland_ಗಣ_ಕಿಟಕಿ_Modal(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool modal);
ಬಾಹ್ಯ bool Wayland_ಗಣ_ಕಿಟಕಿ_Opacity(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ opacity);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Show_ಕಿಟಕಿ_System_Menu(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Wayland_SuspendScreenSaver(SDL_VideoDevice *_this);
ಬಾಹ್ಯ bool Wayland_ಗಣ_ಕಿಟಕಿ_Icon(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *icon);
ಬಾಹ್ಯ bool Wayland_ಗಣ_ಕಿಟಕಿ_Focusable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool focusable);
ಬಾಹ್ಯ ದಶಮಾಂಶ Wayland_Get_ಕಿಟಕಿ_Content_Scale(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_Get_ಕಿಟಕಿ_ICCProfile(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, size_t *ಗಾತ್ರ_2);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_AcceptDragAndDrop(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool accept);

ಬಾಹ್ಯ bool Wayland_ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool enabled);
ಬಾಹ್ಯ bool Wayland_Flash_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_FlashOperation operation);
ಬಾಹ್ಯ bool Wayland_Sync_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool Wayland_Reconfigure_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ_Flags flags);

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Remove_Output_From_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ಕಿಟಕಿ, SDL_Display_ದತ್ತಾಂಶ *display_ದತ್ತಾಂಶ);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Update_ಕಿಟಕಿ_Position(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);

#ಆದರೆ_ಅಂತ್ಯ // SDL_waylandwindow_h_
