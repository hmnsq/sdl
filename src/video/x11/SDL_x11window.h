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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_x11window_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_x11window_h_

/* We need to queue the focus in/out changes because they may occur during
   video mode changes and we can respond to them by triggering more mode
   changes.
*/
#ವ್ಯಾಖ್ಯಾನಿಸು PENDING_FOCUS_ಸಮಯ 200

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
#ಅನ್ತರ್ಭಾವ <EGL/egl.h>
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    PENDING_FOCUS_NONE,
    PENDING_FOCUS_ಒಳ,
    PENDING_FOCUS_ಹೊರಹೋಗು
} PendingFocusEnum;

ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    ಕಿಟಕಿ_2 xwindow;
    Visual *visual;
    Colormap colormap;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
    // MIT shared memory extension information
    bool use_mitshm;
    XShmSegmentInfo shminfo;
#ಆದರೆ_ಅಂತ್ಯ
    XImage *ximage;
    GC gc;
    XIC ic;
    bool created;
    ಪೂರ್ಣಾಂಕ border_ಎಡ;
    ಪೂರ್ಣಾಂಕ border_ಬಲ;
    ಪೂರ್ಣಾಂಕ border_ತುದಿ;
    ಪೂರ್ಣಾಂಕ border_bottom;
    bool xinput2_mouse_enabled;
    bool xinput2_keyboard_enabled;
    bool mouse_grabbed;
    Uint64 ಕೊನೆಯ_focus_event_ಸಮಯ;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ignore_button_press_serial;
    PendingFocusEnum pending_focus;
    Uint64 pending_focus_ಸಮಯ;
    bool pending_move;
    SDL_ಬಿಂದು pending_move_ಬಿಂದು;
    XConfigureEvent ಕೊನೆಯ_xconfigure;
    XConfigureEvent pending_xconfigure;
    ರಚನೆ SDL_Video_ದತ್ತಾಂಶ *videodata;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ user_ಸಮಯ;
    Atom xdnd_req;
    ಕಿಟಕಿ_2 xdnd_ಮೂಲ;
    bool flashing_ಕಿಟಕಿ;
    Uint64 flash_cancel_ಸಮಯ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
    bool ಸೂಚಕ_barrier_ಸಕ್ರಿಯ;
    ಸೂಚಕ_Barrier barrier[4];
    SDL_Rect barrier_rect;
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XFIXES
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
    XSyncCounter resize_counter;
    XSync_ಮೌಲ್ಯ resize_id;
    bool resize_ಒಳ_ಪ್ರಗತಿ;
#ಆದರೆ_ಅಂತ್ಯ /* SDL_VIDEO_DRIVER_X11_XSYNC */

    SDL_Rect expected;
    SDL_Display_ಬಹುಲಕ requested_fullscreen_ಬಹುಲಕ;

    ಎಣಿಕೆ
    {
        X11_PENDING_OP_NONE = 0x00,
        X11_PENDING_OP_RESTORE = 0x01,
        X11_PENDING_OP_MINIMIZE = 0x02,
        X11_PENDING_OP_MAXIMIZE = 0x04,
        X11_PENDING_OP_FULLSCREEN = 0x08,
        X11_PENDING_OP_MOVE = 0x10,
        X11_PENDING_OP_RESIZE = 0x20
    } pending_operation;

    ಎಣಿಕೆ
    {
        X11_ಗಾತ್ರ_MOVE_EVENTS_DISABLE = 0x01, // Events are completely disabled.
        X11_ಗಾತ್ರ_MOVE_EVENTS_WAIT_FOR_BORDERS = 0x02, // Events are disabled until a _NET_FRAME_EXTENTS event arrives.
    } ಗಾತ್ರ_move_event_flags;

    bool pending_ಗಾತ್ರ;
    bool pending_position;
    bool fs_repositioned;
    bool ಕಿಟಕಿ_was_maximized;
    bool ಹಿಂದಿನ_borders_nonzero;
    bool toggle_borders;
    bool fullscreen_borders_forced_on;
    bool was_shown;
    bool emit_ಗಾತ್ರ_move_after_property_notify;
    SDL_ದೊರಕಿತು_Test_ಫಲಿತಾಂಶ ದೊರಕಿತು_test_ಫಲಿತಾಂಶ;
    bool pending_grab;

    XPoint xim_spot;
    ಅಕ್ಷರ *preedit_ಪಠ್ಯ;
    XIMFeedback *preedit_feedback;
    ಪೂರ್ಣಾಂಕ preedit_ಉದ್ದಳತೆ;
    ಪೂರ್ಣಾಂಕ preedit_cursor;
    bool ime_needs_clear_composition;
};

ಬಾಹ್ಯ ಶೂನ್ಯ X11_ಗಣ_Net_WMState(SDL_VideoDevice *_this, ಕಿಟಕಿ_2 xwindow, SDL_ಕಿಟಕಿ_Flags flags);
ಬಾಹ್ಯ SDL_ಕಿಟಕಿ_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಕಿಟಕಿ_2 xwindow);

ಬಾಹ್ಯ bool X11_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಬಾಹ್ಯ ಅಕ್ಷರ *X11_Get_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, ಕಿಟಕಿ_2 xwindow);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool X11_ಗಣ_ಕಿಟಕಿ_Icon(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *icon);
ಬಾಹ್ಯ bool X11_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Minimum_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_ಗರಿಷ್ಠ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Aspect_ಅನುಪಾತ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool X11_Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *ತುದಿ, ಪೂರ್ಣಾಂಕ *ಎಡ, ಪೂರ್ಣಾಂಕ *bottom, ಪೂರ್ಣಾಂಕ *ಬಲ);
ಬಾಹ್ಯ bool X11_ಗಣ_ಕಿಟಕಿ_Opacity(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ opacity);
ಬಾಹ್ಯ bool X11_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ);
ಬಾಹ್ಯ bool X11_ಗಣ_ಕಿಟಕಿ_Modal(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool modal);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Bordered(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool bordered);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool on_ತುದಿ);
ಬಾಹ್ಯ SDL_Fullscreen_ಫಲಿತಾಂಶ X11_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ಬಾಹ್ಯ ಶೂನ್ಯ *X11_Get_ಕಿಟಕಿ_ICCProfile(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, size_t *ಗಾತ್ರ_2);
ಬಾಹ್ಯ bool X11_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed);
ಬಾಹ್ಯ bool X11_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool X11_ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool enabled);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_AcceptDragAndDrop(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool accept);
ಬಾಹ್ಯ bool X11_Flash_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_FlashOperation operation);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Show_ಕಿಟಕಿ_System_Menu(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y);
ಬಾಹ್ಯ bool X11_Sync_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool X11_ಗಣ_ಕಿಟಕಿ_Focusable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool focusable);

ಬಾಹ್ಯ bool SDL_X11_ಗಣ_ಕಿಟಕಿ_Title(Display *display, ಕಿಟಕಿ_2 xwindow, ಅಕ್ಷರ *title);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Update_ಕಿಟಕಿ_Position(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool use_current_position);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_ಗಣ_ಕಿಟಕಿ_Min_Max(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool use_current);

#ಆದರೆ_ಅಂತ್ಯ // SDL_x11window_h_
