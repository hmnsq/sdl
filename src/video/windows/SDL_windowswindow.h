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

#اگر_غیر_تعریف_شدہ SDL_windowswindow_h_
#تعریف_کرو SDL_windowswindow_h_

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#شامل "../SDL_egl_c.h"
#ورنہ
#شامل "../SDL_sysvideo.h"
#اگر_ختم

// Set up for C function definitions, even when using C++
#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

قسمتعریف شمار SDL_کھڑکی_Rect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_کھڑکی_Rect;

قسمتعریف شمار SDL_کھڑکی_Erase_Background_منوال
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_کھڑکی_Erase_Background_منوال;

قسمتعریف ساخت
{
    خالی **lpVtbl;
    صحیح refcount;
    SDL_کھڑکی *کھڑکی;
    HWND hwnd;
    UINT format_متن;
    UINT format_file;
} SDLDrop_ہدف;

ساخت SDL_کھڑکی_ڈیٹا
{
    SDL_کھڑکی *کھڑکی;
    HWND hwnd;
    HWND والد;
    HDC hdc;
    HDC mdc;
    HINSTANCE hinstance;
    HBITMAP hbm;
    HICON hicon;
    WNDPROC wndproc;
    HHOOK keyboard_hook;
    WPARAM mouse_button_flags;
    LPARAM آخری_اشارہ_گر_update;
    WCHAR بلند_surrogate;
    bool initializing;
    bool expected_resize;
    bool اندر_border_change;
    bool اندر_title_click;
    Uint8 focus_click_pending;
    bool postpone_clipcursor;
    bool clipcursor_queued;
    bool windowed_منوال_was_maximized;
    bool اندر_کھڑکی_deactivation;
    bool force_ws_maximizebox;
    bool disable_move_سائز_events;
    bool showing_کھڑکی;
    صحیح اندر_modal_loop;
    صحیح آخری_modal_چوڑائی;
    صحیح آخری_modal_اونچائی;
    RECT initial_سائز_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_والد_with_کھڑکی;
    WCHAR *ICMFileName;
    SDL_کھڑکی_Erase_Background_منوال hint_erase_background_منوال;
    bool taskbar_button_created;
    ساخت SDL_Video_ڈیٹا *videodata;
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#اگر_ختم

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDrop_ہدف *drop_ہدف;
};

خارجی bool WIN_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجی خالی WIN_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool WIN_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
خارجی bool WIN_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی WIN_سیٹ_کھڑکی_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool WIN_Get_کھڑکی_Borders_سائز(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *چوٹی, صحیح *بایاں, صحیح *bottom, صحیح *دایاں);
خارجی خالی WIN_Get_کھڑکی_سائز_اندر_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح *چوڑائی, صحیح *اونچائی);
خارجی bool WIN_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, اعشاری opacity);
خارجی خالی WIN_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی WIN_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی WIN_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی WIN_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی WIN_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی WIN_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی WIN_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered);
خارجی خالی WIN_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);
خارجی خالی WIN_سیٹ_کھڑکی_Always_On_چوٹی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی);
خارجی SDL_Fullscreen_نتیجہ WIN_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجی خالی WIN_Update_کھڑکی_ICCProfile(SDL_کھڑکی *کھڑکی, bool send_event);
خارجی خالی *WIN_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *سائز);
خارجی bool WIN_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool WIN_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجی bool WIN_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجی خالی WIN_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی WIN_On_کھڑکی_Enter(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی خالی WIN_UpdateClipCursor(SDL_کھڑکی *کھڑکی);
خارجی خالی WIN_Unclip_Cursor_For_کھڑکی(SDL_کھڑکی *کھڑکی);
خارجی bool WIN_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled);
خارجی خالی WIN_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept);
خارجی bool WIN_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation);
خارجی bool WIN_Apply_کھڑکی_پیش_رفت(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجی bool WIN_سیٹ_کھڑکی_Position_اندرونی(SDL_کھڑکی *کھڑکی, UINT flags, SDL_کھڑکی_Rect rect_type);
خارجی خالی WIN_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحیح x, صحیح y);
خارجی bool WIN_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);
خارجی bool WIN_Adjust_کھڑکی_Rect(SDL_کھڑکی *کھڑکی, صحیح *x, صحیح *y, صحیح *چوڑائی, صحیح *اونچائی, SDL_کھڑکی_Rect rect_type);
خارجی bool WIN_Adjust_کھڑکی_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT چوکھٹا_dpi);
خارجی bool WIN_سیٹ_کھڑکی_والد(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *والد);
خارجی bool WIN_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal);

// Ends C function definitions when using C++
#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم // SDL_windowswindow_h_
