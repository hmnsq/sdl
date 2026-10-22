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

#اگر_غیر_تعریف_شدہ SDL_x11window_h_
#تعریف_کرو SDL_x11window_h_

/* We need to queue the focus in/out changes because they may occur during
   video mode changes and we can respond to them by triggering more mode
   changes.
*/
#تعریف_کرو PENDING_FOCUS_وقت 200

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#شامل <EGL/egl.h>
#اگر_ختم

قسمتعریف شمار
{
    PENDING_FOCUS_NONE,
    PENDING_FOCUS_اندر,
    PENDING_FOCUS_برآمد
} PendingFocusEnum;

ساخت SDL_کھڑکی_ڈیٹا
{
    SDL_کھڑکی *کھڑکی;
    کھڑکی_2 xwindow;
    Visual *visual;
    Colormap colormap;
#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
    // MIT shared memory extension information
    bool use_mitshm;
    XShmSegmentInfo shminfo;
#اگر_ختم
    XImage *ximage;
    GC gc;
    XIC ic;
    bool created;
    صحیح border_بایاں;
    صحیح border_دایاں;
    صحیح border_چوٹی;
    صحیح border_bottom;
    bool xinput2_mouse_enabled;
    bool xinput2_keyboard_enabled;
    bool mouse_grabbed;
    Uint64 آخری_focus_event_وقت;
    غیرعلامتی طویل ignore_button_press_serial;
    PendingFocusEnum pending_focus;
    Uint64 pending_focus_وقت;
    bool pending_move;
    SDL_نقطہ pending_move_نقطہ;
    XConfigureEvent آخری_xconfigure;
    XConfigureEvent pending_xconfigure;
    ساخت SDL_Video_ڈیٹا *videodata;
    غیرعلامتی طویل user_وقت;
    Atom xdnd_req;
    کھڑکی_2 xdnd_ماخذ;
    bool flashing_کھڑکی;
    Uint64 flash_cancel_وقت;
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    bool اشارہ_گر_barrier_فعال;
    اشارہ_گر_Barrier barrier[4];
    SDL_Rect barrier_rect;
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XFIXES
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
    XSync_شمار resize_شمار;
    XSync_قدر resize_id;
    bool resize_اندر_پیش_رفت;
#اگر_ختم /* SDL_VIDEO_DRIVER_X11_XSYNC */

    SDL_Rect expected;
    SDL_Display_منوال requested_fullscreen_منوال;

    شمار
    {
        X11_PENDING_OP_NONE = 0x00,
        X11_PENDING_OP_RESTORE = 0x01,
        X11_PENDING_OP_MINIMIZE = 0x02,
        X11_PENDING_OP_MAXIMIZE = 0x04,
        X11_PENDING_OP_FULLSCREEN = 0x08,
        X11_PENDING_OP_MOVE = 0x10,
        X11_PENDING_OP_RESIZE = 0x20
    } pending_operation;

    شمار
    {
        X11_سائز_MOVE_EVENTS_DISABLE = 0x01, // Events are completely disabled.
        X11_سائز_MOVE_EVENTS_WAIT_FOR_BORDERS = 0x02, // Events are disabled until a _NET_FRAME_EXTENTS event arrives.
    } سائز_move_event_flags;

    bool pending_سائز;
    bool pending_position;
    bool fs_repositioned;
    bool کھڑکی_was_maximized;
    bool پچھلا_borders_nonzero;
    bool toggle_borders;
    bool fullscreen_borders_forced_on;
    bool was_shown;
    bool emit_سائز_move_after_property_notify;
    SDL_کامیابی_Test_نتیجہ کامیابی_test_نتیجہ;
    bool pending_grab;

    XPoint xim_spot;
    حرف *preedit_متن;
    XIMFeedback *preedit_feedback;
    صحیح preedit_لمبائی;
    صحیح preedit_cursor;
    bool ime_needs_clear_composition;
};

خارجی خالی X11_سیٹ_Net_WMState(SDL_VideoDevice *_this, کھڑکی_2 xwindow, SDL_کھڑکی_Flags flags);
خارجی SDL_کھڑکی_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, کھڑکی_2 xwindow);

خارجی bool X11_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجی حرف *X11_Get_کھڑکی_Title(SDL_VideoDevice *_this, کھڑکی_2 xwindow);
خارجی خالی X11_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool X11_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
خارجی bool X11_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_سیٹ_کھڑکی_Minimum_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_سیٹ_کھڑکی_زیادہ_سے_زیادہ_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_سیٹ_کھڑکی_Aspect_تناسب(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool X11_Get_کھڑکی_Borders_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *چوٹی, صحیح *بایاں, صحیح *bottom, صحیح *دایاں);
خارجی bool X11_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, اعشاری opacity);
خارجی bool X11_سیٹ_کھڑکی_والد(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *والد);
خارجی bool X11_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal);
خارجی خالی X11_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی X11_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered);
خارجی خالی X11_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);
خارجی خالی X11_سیٹ_کھڑکی_Always_On_چوٹی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی);
خارجی SDL_Fullscreen_نتیجہ X11_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجی خالی *X11_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *سائز);
خارجی bool X11_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجی bool X11_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجی خالی X11_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool X11_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled);
خارجی خالی X11_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept);
خارجی bool X11_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation);
خارجی خالی X11_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحیح x, صحیح y);
خارجی bool X11_Sync_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool X11_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);

خارجی bool SDL_X11_سیٹ_کھڑکی_Title(Display *display, کھڑکی_2 xwindow, حرف *title);
خارجی خالی X11_Update_کھڑکی_Position(SDL_کھڑکی *کھڑکی, bool use_current_position);
خارجی خالی X11_سیٹ_کھڑکی_Min_Max(SDL_کھڑکی *کھڑکی, bool use_current);

#اگر_ختم // SDL_x11window_h_
