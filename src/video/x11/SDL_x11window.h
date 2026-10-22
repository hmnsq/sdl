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

#جيڪڏهن_وصف_نه_ٿيل SDL_x11window_h_
#وصف_ڪريو SDL_x11window_h_

/* We need to queue the focus in/out changes because they may occur during
   video mode changes and we can respond to them by triggering more mode
   changes.
*/
#وصف_ڪريو PENDING_FOCUS_وقت 200

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
#ضمن <EGL/egl.h>
#جيڪڏهن_پورو

تعريفنوع تعداد
{
    PENDING_FOCUS_NONE,
    PENDING_FOCUS_اندريون,
    PENDING_FOCUS_ٻاهريون
} PendingFocusEnum;

بنية SDL_دري_معلومات
{
    SDL_دري *دري;
    دري_2 xwindow;
    Visual *visual;
    Colormap colormap;
#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري
    // MIT shared memory extension information
    bool use_mitshm;
    XShmSegmentInfo shminfo;
#جيڪڏهن_پورو
    XImage *ximage;
    GC gc;
    XIC ic;
    bool created;
    صحيح border_کاٻو;
    صحيح border_ساڄو;
    صحيح border_چوٽي;
    صحيح border_bottom;
    bool xinput2_mouse_enabled;
    bool xinput2_keyboard_enabled;
    bool mouse_grabbed;
    Uint64 آخري_focus_event_وقت;
    بنانشان ڊگهو ignore_button_press_serial;
    PendingFocusEnum pending_focus;
    Uint64 pending_focus_وقت;
    bool pending_move;
    SDL_نقطو pending_move_نقطو;
    XConfigureEvent آخري_xconfigure;
    XConfigureEvent pending_xconfigure;
    بنية SDL_Video_معلومات *videodata;
    بنانشان ڊگهو user_وقت;
    Atom xdnd_req;
    دري_2 xdnd_ذريعو;
    bool flashing_دري;
    Uint64 flash_cancel_وقت;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
    bool اشارو_barrier_سرگرم;
    اشارو_Barrier barrier[4];
    SDL_Rect barrier_rect;
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_XFIXES
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSYNC
    XSyncCounter resize_counter;
    XSync_قدر resize_id;
    bool resize_اندريون_ترقي;
#جيڪڏهن_پورو /* SDL_VIDEO_DRIVER_X11_XSYNC */

    SDL_Rect expected;
    SDL_Display_گهڻائي requested_fullscreen_گهڻائي;

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
        X11_سائيز_MOVE_EVENTS_DISABLE = 0x01, // Events are completely disabled.
        X11_سائيز_MOVE_EVENTS_WAIT_FOR_BORDERS = 0x02, // Events are disabled until a _NET_FRAME_EXTENTS event arrives.
    } سائيز_move_event_flags;

    bool pending_سائيز;
    bool pending_position;
    bool fs_repositioned;
    bool دري_was_maximized;
    bool اڳيون_borders_nonzero;
    bool toggle_borders;
    bool fullscreen_borders_forced_on;
    bool was_shown;
    bool emit_سائيز_move_after_property_notify;
    SDL_ڪاميابي_Test_نتيجو ڪاميابي_test_نتيجو;
    bool pending_grab;

    XPoint xim_spot;
    حرف *preedit_متن;
    XIMFeedback *preedit_feedback;
    صحيح preedit_ڊيگهائي;
    صحيح preedit_cursor;
    bool ime_needs_clear_composition;
};

خارجي فراغ X11_سيٽ_Net_WMState(SDL_VideoDevice *_this, دري_2 xwindow, SDL_دري_Flags flags);
خارجي SDL_دري_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_دري *دري, دري_2 xwindow);

خارجي bool X11_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props);
خارجي حرف *X11_Get_دري_Title(SDL_VideoDevice *_this, دري_2 xwindow);
خارجي فراغ X11_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool X11_سيٽ_دري_Icon(SDL_VideoDevice *_this, SDL_دري *دري, SDL_Surface *icon);
خارجي bool X11_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_سيٽ_دري_Minimum_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_سيٽ_دري_وڌ_کان_وڌ_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_سيٽ_دري_Aspect_تناسب(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool X11_Get_دري_Borders_سائيز(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *چوٽي, صحيح *کاٻو, صحيح *bottom, صحيح *ساڄو);
خارجي bool X11_سيٽ_دري_Opacity(SDL_VideoDevice *_this, SDL_دري *دري, عائم opacity);
خارجي bool X11_سيٽ_دري_والد(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري *والد);
خارجي bool X11_سيٽ_دري_Modal(SDL_VideoDevice *_this, SDL_دري *دري, bool modal);
خارجي فراغ X11_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ X11_سيٽ_دري_Bordered(SDL_VideoDevice *_this, SDL_دري *دري, bool bordered);
خارجي فراغ X11_سيٽ_دري_Resizable(SDL_VideoDevice *_this, SDL_دري *دري, bool resizable);
خارجي فراغ X11_سيٽ_دري_Always_On_چوٽي(SDL_VideoDevice *_this, SDL_دري *دري, bool on_چوٽي);
خارجي SDL_Fullscreen_نتيجو X11_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ *X11_Get_دري_ICCProfile(SDL_VideoDevice *_this, SDL_دري *دري, size_t *سائيز);
خارجي bool X11_سيٽ_دري_Mouse_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed);
خارجي bool X11_سيٽ_دري_Keyboard_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed);
خارجي فراغ X11_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool X11_سيٽ_دري_ڪاميابي_Test(SDL_دري *دري, bool enabled);
خارجي فراغ X11_AcceptDragAndDrop(SDL_دري *دري, bool accept);
خارجي bool X11_Flash_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_FlashOperation operation);
خارجي فراغ X11_Show_دري_System_Menu(SDL_دري *دري, صحيح x, صحيح y);
خارجي bool X11_Sync_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool X11_سيٽ_دري_Focusable(SDL_VideoDevice *_this, SDL_دري *دري, bool focusable);

خارجي bool SDL_X11_سيٽ_دري_Title(Display *display, دري_2 xwindow, حرف *title);
خارجي فراغ X11_Update_دري_Position(SDL_دري *دري, bool use_current_position);
خارجي فراغ X11_سيٽ_دري_Min_Max(SDL_دري *دري, bool use_current);

#جيڪڏهن_پورو // SDL_x11window_h_
