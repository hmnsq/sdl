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

#جے_بنا_تعریف SDL_x11window_h_
#تعریف_کرو SDL_x11window_h_

/* We need to queue the focus in/out changes because they may occur during
   video mode changes and we can respond to them by triggering more mode
   changes.
*/
#تعریف_کرو PENDING_FOCUS_ویلا 200

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#ضمن <EGL/egl.h>
#جے_انت

تعريفنوع تعداد
{
    PENDING_FOCUS_NONE,
    PENDING_FOCUS_وچ,
    PENDING_FOCUS_باہرلا
} PendingFocusEnum;

بنية SDL_کھڑکی_انکڑے
{
    SDL_کھڑکی *کھڑکی;
    کھڑکی_2 xwindow;
    Visual *visual;
    Colormap colormap;
#جے_بنا_تعریف NO_SHARED_حافظہ
    // MIT shared memory extension information
    bool use_mitshm;
    XShmSegmentInfo shminfo;
#جے_انت
    XImage *ximage;
    GC gc;
    XIC ic;
    bool created;
    صحيح border_بایاں;
    صحيح border_دایاں;
    صحيح border_چوٹی;
    صحيح border_bottom;
    bool xinput2_mouse_enabled;
    bool xinput2_keyboard_enabled;
    bool mouse_grabbed;
    Uint64 آخری_focus_event_ویلا;
    بنانشانی لما ignore_button_press_serial;
    PendingFocusEnum pending_focus;
    Uint64 pending_focus_ویلا;
    bool pending_move;
    SDL_نقطہ pending_move_نقطہ;
    XConfigureEvent آخری_xconfigure;
    XConfigureEvent pending_xconfigure;
    بنية SDL_Video_انکڑے *videodata;
    بنانشانی لما user_ویلا;
    Atom xdnd_req;
    کھڑکی_2 xdnd_سروت;
    bool flashing_کھڑکی;
    Uint64 flash_cancel_ویلا;
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    bool اشارہ_گر_barrier_سرگرم;
    اشارہ_گر_Barrier barrier[4];
    SDL_Rect barrier_rect;
#جے_انت // SDL_VIDEO_DRIVER_X11_XFIXES
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
    XSyncCounter resize_counter;
    XSync_قدر resize_id;
    bool resize_وچ_ترقی;
#جے_انت /* SDL_VIDEO_DRIVER_X11_XSYNC */

    SDL_Rect expected;
    SDL_Display_منوال requested_fullscreen_منوال;

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
        X11_ناپ_MOVE_EVENTS_DISABLE = 0x01, // Events are completely disabled.
        X11_ناپ_MOVE_EVENTS_WAIT_FOR_BORDERS = 0x02, // Events are disabled until a _NET_FRAME_EXTENTS event arrives.
    } ناپ_move_event_flags;

    bool pending_ناپ;
    bool pending_position;
    bool fs_repositioned;
    bool کھڑکی_was_maximized;
    bool پچھلا_borders_nonzero;
    bool toggle_borders;
    bool fullscreen_borders_forced_on;
    bool was_shown;
    bool emit_ناپ_move_after_property_notify;
    SDL_کامیابی_Test_نتیجہ کامیابی_test_نتیجہ;
    bool pending_grab;

    XPoint xim_spot;
    حرف *preedit_متن;
    XIMFeedback *preedit_feedback;
    صحيح preedit_لمائی;
    صحيح preedit_cursor;
    bool ime_needs_clear_composition;
};

خارجي فراغ X11_سیٹ_Net_WMState(SDL_VideoDevice *_this, کھڑکی_2 xwindow, SDL_کھڑکی_Flags flags);
خارجي SDL_کھڑکی_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, کھڑکی_2 xwindow);

خارجي bool X11_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجي حرف *X11_Get_کھڑکی_Title(SDL_VideoDevice *_this, کھڑکی_2 xwindow);
خارجي فراغ X11_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool X11_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
خارجي bool X11_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ X11_سیٹ_کھڑکی_Minimum_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ X11_سیٹ_کھڑکی_ودھ_توں_ودھ_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ X11_سیٹ_کھڑکی_Aspect_تناسب(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool X11_Get_کھڑکی_Borders_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *چوٹی, صحيح *بایاں, صحيح *bottom, صحيح *دایاں);
خارجي bool X11_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, عائم opacity);
خارجي bool X11_سیٹ_کھڑکی_ماپا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *ماپا);
خارجي bool X11_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal);
خارجي فراغ X11_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ X11_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ X11_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ X11_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ X11_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ X11_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ X11_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ X11_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered);
خارجي فراغ X11_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);
خارجي فراغ X11_سیٹ_کھڑکی_Always_On_چوٹی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی);
خارجي SDL_Fullscreen_نتیجہ X11_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ *X11_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *ناپ);
خارجي bool X11_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجي bool X11_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجي فراغ X11_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool X11_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled);
خارجي فراغ X11_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept);
خارجي bool X11_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation);
خارجي فراغ X11_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحيح x, صحيح y);
خارجي bool X11_Sync_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool X11_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);

خارجي bool SDL_X11_سیٹ_کھڑکی_Title(Display *display, کھڑکی_2 xwindow, حرف *title);
خارجي فراغ X11_Update_کھڑکی_Position(SDL_کھڑکی *کھڑکی, bool use_current_position);
خارجي فراغ X11_سیٹ_کھڑکی_Min_Max(SDL_کھڑکی *کھڑکی, bool use_current);

#جے_انت // SDL_x11window_h_
