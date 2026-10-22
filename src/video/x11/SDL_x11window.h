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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_x11window_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_x11window_h_

/* We need to queue the focus in/out changes because they may occur during
   video mode changes and we can respond to them by triggering more mode
   changes.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PENDING_FOCUS_ਸਮਾਂ 200

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
#ਅਨ੍ਤਰ੍ਭਾਵ <EGL/egl.h>
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    PENDING_FOCUS_NONE,
    PENDING_FOCUS_ਵਿੱਚ,
    PENDING_FOCUS_ਬਾਹਰਲਾ
} PendingFocusEnum;

ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    ਖਿੜਕੀ_2 xwindow;
    Visual *visual;
    Colormap colormap;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
    // MIT shared memory extension information
    bool use_mitshm;
    XShmSegmentInfo shminfo;
#ਜੇ_ਅੰਤ
    XImage *ximage;
    GC gc;
    XIC ic;
    bool created;
    ਪੂਰਨ border_ਖੱਬਾ;
    ਪੂਰਨ border_ਸੱਜਾ;
    ਪੂਰਨ border_ਸਿਖਰ;
    ਪੂਰਨ border_bottom;
    bool xinput2_mouse_enabled;
    bool xinput2_keyboard_enabled;
    bool mouse_grabbed;
    Uint64 ਆਖਰੀ_focus_event_ਸਮਾਂ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ignore_button_press_serial;
    PendingFocusEnum pending_focus;
    Uint64 pending_focus_ਸਮਾਂ;
    bool pending_move;
    SDL_ਬਿੰਦੂ pending_move_ਬਿੰਦੂ;
    XConfigureEvent ਆਖਰੀ_xconfigure;
    XConfigureEvent pending_xconfigure;
    ਬਣਤਰ SDL_Video_ਅੰਕੜੇ *videodata;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ user_ਸਮਾਂ;
    Atom xdnd_req;
    ਖਿੜਕੀ_2 xdnd_ਸਰੋਤ;
    bool flashing_ਖਿੜਕੀ;
    Uint64 flash_cancel_ਸਮਾਂ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
    bool ਸੂਚਕ_barrier_ਸਰਗਰਮ;
    ਸੂਚਕ_Barrier barrier[4];
    SDL_Rect barrier_rect;
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XFIXES
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
    XSyncCounter resize_counter;
    XSync_ਮੁੱਲ resize_id;
    bool resize_ਵਿੱਚ_ਤਰੱਕੀ;
#ਜੇ_ਅੰਤ /* SDL_VIDEO_DRIVER_X11_XSYNC */

    SDL_Rect expected;
    SDL_Display_ਬਹੁਲਕ requested_fullscreen_ਬਹੁਲਕ;

    ਗਿਣਤੀ
    {
        X11_PENDING_OP_NONE = 0x00,
        X11_PENDING_OP_RESTORE = 0x01,
        X11_PENDING_OP_MINIMIZE = 0x02,
        X11_PENDING_OP_MAXIMIZE = 0x04,
        X11_PENDING_OP_FULLSCREEN = 0x08,
        X11_PENDING_OP_MOVE = 0x10,
        X11_PENDING_OP_RESIZE = 0x20
    } pending_operation;

    ਗਿਣਤੀ
    {
        X11_ਮਾਪ_MOVE_EVENTS_DISABLE = 0x01, // Events are completely disabled.
        X11_ਮਾਪ_MOVE_EVENTS_WAIT_FOR_BORDERS = 0x02, // Events are disabled until a _NET_FRAME_EXTENTS event arrives.
    } ਮਾਪ_move_event_flags;

    bool pending_ਮਾਪ;
    bool pending_position;
    bool fs_repositioned;
    bool ਖਿੜਕੀ_was_maximized;
    bool ਪਿਛਲਾ_borders_nonzero;
    bool toggle_borders;
    bool fullscreen_borders_forced_on;
    bool was_shown;
    bool emit_ਮਾਪ_move_after_property_notify;
    SDL_ਪ੍ਰਾਪਤੀ_Test_ਨਤੀਜਾ ਪ੍ਰਾਪਤੀ_test_ਨਤੀਜਾ;
    bool pending_grab;

    XPoint xim_spot;
    ਅੱਖਰ *preedit_ਪਾਠ;
    XIMFeedback *preedit_feedback;
    ਪੂਰਨ preedit_ਲੰਮਾਈ;
    ਪੂਰਨ preedit_cursor;
    bool ime_needs_clear_composition;
};

ਬਾਹਰੀ ਖਾਲੀ X11_ਸੈੱਟ_Net_WMState(SDL_VideoDevice *_this, ਖਿੜਕੀ_2 xwindow, SDL_ਖਿੜਕੀ_Flags flags);
ਬਾਹਰੀ SDL_ਖਿੜਕੀ_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਖਿੜਕੀ_2 xwindow);

ਬਾਹਰੀ bool X11_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਬਾਹਰੀ ਅੱਖਰ *X11_Get_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, ਖਿੜਕੀ_2 xwindow);
ਬਾਹਰੀ ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Icon(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *icon);
ਬਾਹਰੀ bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Minimum_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_ਵੱਧ_ਤੋਂ_ਵੱਧ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Aspect_ਅਨੁਪਾਤ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool X11_Get_ਖਿੜਕੀ_Borders_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *ਸਿਖਰ, ਪੂਰਨ *ਖੱਬਾ, ਪੂਰਨ *bottom, ਪੂਰਨ *ਸੱਜਾ);
ਬਾਹਰੀ bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Opacity(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ opacity);
ਬਾਹਰੀ bool X11_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ *ਮਾਪਾ);
ਬਾਹਰੀ bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Modal(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool modal);
ਬਾਹਰੀ ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Bordered(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool bordered);
ਬਾਹਰੀ ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable);
ਬਾਹਰੀ ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool on_ਸਿਖਰ);
ਬਾਹਰੀ SDL_Fullscreen_ਨਤੀਜਾ X11_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ਬਾਹਰੀ ਖਾਲੀ *X11_Get_ਖਿੜਕੀ_ICCProfile(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, size_t *ਮਾਪ);
ਬਾਹਰੀ bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed);
ਬਾਹਰੀ bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed);
ਬਾਹਰੀ ਖਾਲੀ X11_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool X11_ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool enabled);
ਬਾਹਰੀ ਖਾਲੀ X11_AcceptDragAndDrop(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool accept);
ਬਾਹਰੀ bool X11_Flash_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_FlashOperation operation);
ਬਾਹਰੀ ਖਾਲੀ X11_Show_ਖਿੜਕੀ_System_Menu(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ x, ਪੂਰਨ y);
ਬਾਹਰੀ bool X11_Sync_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool X11_ਸੈੱਟ_ਖਿੜਕੀ_Focusable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool focusable);

ਬਾਹਰੀ bool SDL_X11_ਸੈੱਟ_ਖਿੜਕੀ_Title(Display *display, ਖਿੜਕੀ_2 xwindow, ਅੱਖਰ *title);
ਬਾਹਰੀ ਖਾਲੀ X11_Update_ਖਿੜਕੀ_Position(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool use_current_position);
ਬਾਹਰੀ ਖਾਲੀ X11_ਸੈੱਟ_ਖਿੜਕੀ_Min_Max(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool use_current);

#ਜੇ_ਅੰਤ // SDL_x11window_h_
