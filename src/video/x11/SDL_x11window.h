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

#که_نه_تعریف_شوی SDL_x11window_h_
#تعریف_کړه SDL_x11window_h_

/* We need to queue the focus in/out changes because they may occur during
   video mode changes and we can respond to them by triggering more mode
   changes.
*/
#تعریف_کړه PENDING_FOCUS_وخت 200

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
#ضمن <EGL/egl.h>
#د_که_پای

تعريفنوع تعداد
{
    PENDING_FOCUS_NONE,
    PENDING_FOCUS_دننه,
    PENDING_FOCUS_بهر
} PendingFocusEnum;

بنية SDL_کړکۍ_معلومات
{
    SDL_کړکۍ *کړکۍ;
    کړکۍ_2 xwindow;
    Visual *visual;
    Colormap colormap;
#که_نه_تعریف_شوی NO_SHARED_حافظه
    // MIT shared memory extension information
    bool use_mitshm;
    XShmSegmentInfo shminfo;
#د_که_پای
    XImage *ximage;
    GC gc;
    XIC ic;
    bool created;
    صحيح border_کیڼ;
    صحيح border_ښی;
    صحيح border_سر;
    صحيح border_bottom;
    bool xinput2_mouse_enabled;
    bool xinput2_keyboard_enabled;
    bool mouse_grabbed;
    Uint64 وروستی_focus_event_وخت;
    بینښه اوږد ignore_button_press_serial;
    PendingFocusEnum pending_focus;
    Uint64 pending_focus_وخت;
    bool pending_move;
    SDL_ټکی pending_move_ټکی;
    XConfigureEvent وروستی_xconfigure;
    XConfigureEvent pending_xconfigure;
    بنية SDL_Video_معلومات *videodata;
    بینښه اوږد user_وخت;
    Atom xdnd_req;
    کړکۍ_2 xdnd_سرچینه;
    bool flashing_کړکۍ;
    Uint64 flash_cancel_وخت;
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XFIXES
    bool اشاره_ګر_barrier_فعال;
    اشاره_ګر_Barrier barrier[4];
    SDL_Rect barrier_rect;
#د_که_پای // SDL_VIDEO_DRIVER_X11_XFIXES
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSYNC
    XSyncCounter resize_counter;
    XSync_ارزښت resize_id;
    bool resize_دننه_پرمختګ;
#د_که_پای /* SDL_VIDEO_DRIVER_X11_XSYNC */

    SDL_Rect expected;
    SDL_Display_ډېرپېښ requested_fullscreen_ډېرپېښ;

    تعداد
    {
        X11_PENDING_OP_NONE = 0x00,
        X11_PENDING_OP_RESTORE = 0x01,
        X11_PENDING_OP_MINIMIZE = 0x02,
        X11_PENDING_OP_MAXIMIZE = 0x04,
        X11_PENDING_OP_FULLSCREEN = 0x08,
        X11_PENDING_OP_MOVE = 0x10,
        X11_PENDING_OP_RESIZE = 0x20
    } pending_operation;

    تعداد
    {
        X11_اندازه_MOVE_EVENTS_DISABLE = 0x01, // Events are completely disabled.
        X11_اندازه_MOVE_EVENTS_WAIT_FOR_BORDERS = 0x02, // Events are disabled until a _NET_FRAME_EXTENTS event arrives.
    } اندازه_move_event_flags;

    bool pending_اندازه;
    bool pending_position;
    bool fs_repositioned;
    bool کړکۍ_was_maximized;
    bool پخوانی_borders_nonzero;
    bool toggle_borders;
    bool fullscreen_borders_forced_on;
    bool was_shown;
    bool emit_اندازه_move_after_property_notify;
    SDL_موندنه_Test_پایله موندنه_test_پایله;
    bool pending_grab;

    XPoint xim_spot;
    حرف *preedit_متن;
    XIMFeedback *preedit_feedback;
    صحيح preedit_اوږدتیا;
    صحيح preedit_cursor;
    bool ime_needs_clear_composition;
};

خارجي فراغ X11_سېټ_Net_WMState(SDL_VideoDevice *_this, کړکۍ_2 xwindow, SDL_کړکۍ_Flags flags);
خارجي SDL_کړکۍ_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, کړکۍ_2 xwindow);

خارجي bool X11_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props);
خارجي حرف *X11_Get_کړکۍ_Title(SDL_VideoDevice *_this, کړکۍ_2 xwindow);
خارجي فراغ X11_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool X11_سېټ_کړکۍ_Icon(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *icon);
خارجي bool X11_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ X11_سېټ_کړکۍ_Minimum_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ X11_سېټ_کړکۍ_اعظمي_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ X11_سېټ_کړکۍ_Aspect_نسبت(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool X11_Get_کړکۍ_Borders_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *سر, صحيح *کیڼ, صحيح *bottom, صحيح *ښی);
خارجي bool X11_سېټ_کړکۍ_Opacity(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, عائم opacity);
خارجي bool X11_سېټ_کړکۍ_پلار(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_کړکۍ *پلار);
خارجي bool X11_سېټ_کړکۍ_Modal(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool modal);
خارجي فراغ X11_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ X11_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ X11_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ X11_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ X11_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ X11_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ X11_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ X11_سېټ_کړکۍ_Bordered(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool bordered);
خارجي فراغ X11_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool resizable);
خارجي فراغ X11_سېټ_کړکۍ_Always_On_سر(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool on_سر);
خارجي SDL_Fullscreen_پایله X11_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ *X11_Get_کړکۍ_ICCProfile(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, size_t *اندازه);
خارجي bool X11_سېټ_کړکۍ_Mouse_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed);
خارجي bool X11_سېټ_کړکۍ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed);
خارجي فراغ X11_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool X11_سېټ_کړکۍ_موندنه_Test(SDL_کړکۍ *کړکۍ, bool enabled);
خارجي فراغ X11_AcceptDragAndDrop(SDL_کړکۍ *کړکۍ, bool accept);
خارجي bool X11_Flash_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_FlashOperation operation);
خارجي فراغ X11_Show_کړکۍ_System_Menu(SDL_کړکۍ *کړکۍ, صحيح x, صحيح y);
خارجي bool X11_Sync_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool X11_سېټ_کړکۍ_Focusable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool focusable);

خارجي bool SDL_X11_سېټ_کړکۍ_Title(Display *display, کړکۍ_2 xwindow, حرف *title);
خارجي فراغ X11_Update_کړکۍ_Position(SDL_کړکۍ *کړکۍ, bool use_current_position);
خارجي فراغ X11_سېټ_کړکۍ_Min_Max(SDL_کړکۍ *کړکۍ, bool use_current);

#د_که_پای // SDL_x11window_h_
