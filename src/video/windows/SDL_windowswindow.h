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

#جے_بنا_تعریف SDL_windowswindow_h_
#تعریف_کرو SDL_windowswindow_h_

#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
#ضمن "../SDL_egl_c.h"
#وإلا
#ضمن "../SDL_sysvideo.h"
#جے_انت

// Set up for C function definitions, even when using C++
#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

تعريفنوع تعداد SDL_کھڑکی_Rect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_کھڑکی_Rect;

تعريفنوع تعداد SDL_کھڑکی_Erase_Background_منوال
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_کھڑکی_Erase_Background_منوال;

تعريفنوع بنية
{
    فراغ **lpVtbl;
    صحيح refcount;
    SDL_کھڑکی *کھڑکی;
    HWND hwnd;
    UINT format_متن;
    UINT format_file;
} SDLDrop_نشانہ;

بنية SDL_کھڑکی_انکڑے
{
    SDL_کھڑکی *کھڑکی;
    HWND hwnd;
    HWND ماپا;
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
    bool وچ_border_change;
    bool وچ_title_click;
    Uint8 focus_click_pending;
    bool postpone_clipcursor;
    bool clipcursor_queued;
    bool windowed_منوال_was_maximized;
    bool وچ_کھڑکی_deactivation;
    bool force_ws_maximizebox;
    bool disable_move_ناپ_events;
    bool showing_کھڑکی;
    صحيح وچ_modal_loop;
    صحيح آخری_modal_چوڑائی;
    صحيح آخری_modal_اچائی;
    RECT initial_ناپ_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_ماپا_with_کھڑکی;
    WCHAR *ICMFileName;
    SDL_کھڑکی_Erase_Background_منوال hint_erase_background_منوال;
    bool taskbar_button_created;
    بنية SDL_Video_انکڑے *videodata;
#جے_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#جے_انت

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDrop_نشانہ *drop_نشانہ;
};

خارجي bool WIN_Create_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PropertiesID create_props);
خارجي فراغ WIN_سیٹ_کھڑکی_Title(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool WIN_سیٹ_کھڑکی_Icon(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_Surface *icon);
خارجي bool WIN_سیٹ_کھڑکی_Position(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ WIN_سیٹ_کھڑکی_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool WIN_Get_کھڑکی_Borders_ناپ(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *چوٹی, صحيح *بایاں, صحيح *bottom, صحيح *دایاں);
خارجي فراغ WIN_Get_کھڑکی_ناپ_وچ_Pixels(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحيح *چوڑائی, صحيح *اچائی);
خارجي bool WIN_سیٹ_کھڑکی_Opacity(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, عائم opacity);
خارجي فراغ WIN_Show_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ WIN_Hide_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ WIN_Raise_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ WIN_Maximize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ WIN_Minimize_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ WIN_Restore_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ WIN_سیٹ_کھڑکی_Bordered(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool bordered);
خارجي فراغ WIN_سیٹ_کھڑکی_Resizable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool resizable);
خارجي فراغ WIN_سیٹ_کھڑکی_Always_On_چوٹی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool on_چوٹی);
خارجي SDL_Fullscreen_نتیجہ WIN_سیٹ_کھڑکی_Fullscreen(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ WIN_Update_کھڑکی_ICCProfile(SDL_کھڑکی *کھڑکی, bool send_event);
خارجي فراغ *WIN_Get_کھڑکی_ICCProfile(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, size_t *ناپ);
خارجي bool WIN_سیٹ_کھڑکی_Mouse_Rect(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool WIN_سیٹ_کھڑکی_Mouse_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجي bool WIN_سیٹ_کھڑکی_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool grabbed);
خارجي فراغ WIN_Destroy_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ WIN_On_کھڑکی_Enter(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي فراغ WIN_UpdateClipCursor(SDL_کھڑکی *کھڑکی);
خارجي فراغ WIN_Unclip_Cursor_For_کھڑکی(SDL_کھڑکی *کھڑکی);
خارجي bool WIN_سیٹ_کھڑکی_کامیابی_Test(SDL_کھڑکی *کھڑکی, bool enabled);
خارجي فراغ WIN_AcceptDragAndDrop(SDL_کھڑکی *کھڑکی, bool accept);
خارجي bool WIN_Flash_کھڑکی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_FlashOperation operation);
خارجي bool WIN_Apply_کھڑکی_ترقی(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی);
خارجي bool WIN_سیٹ_کھڑکی_Position_اندرونی(SDL_کھڑکی *کھڑکی, UINT flags, SDL_کھڑکی_Rect rect_type);
خارجي فراغ WIN_Show_کھڑکی_System_Menu(SDL_کھڑکی *کھڑکی, صحيح x, صحيح y);
خارجي bool WIN_سیٹ_کھڑکی_Focusable(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool focusable);
خارجي bool WIN_Adjust_کھڑکی_Rect(SDL_کھڑکی *کھڑکی, صحيح *x, صحيح *y, صحيح *چوڑائی, صحيح *اچائی, SDL_کھڑکی_Rect rect_type);
خارجي bool WIN_Adjust_کھڑکی_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT چوکھٹا_dpi);
خارجي bool WIN_سیٹ_کھڑکی_ماپا(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_کھڑکی *ماپا);
خارجي bool WIN_سیٹ_کھڑکی_Modal(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, bool modal);

// Ends C function definitions when using C++
#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت // SDL_windowswindow_h_
