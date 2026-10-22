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

#که_نه_تعریف_شوی SDL_windowswindow_h_
#تعریف_کړه SDL_windowswindow_h_

#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
#ضمن "../SDL_egl_c.h"
#وإلا
#ضمن "../SDL_sysvideo.h"
#د_که_پای

// Set up for C function definitions, even when using C++
#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

تعريفنوع تعداد SDL_کړکۍ_Rect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_کړکۍ_Rect;

تعريفنوع تعداد SDL_کړکۍ_Erase_Background_ډېرپېښ
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_کړکۍ_Erase_Background_ډېرپېښ;

تعريفنوع بنية
{
    فراغ **lpVtbl;
    صحيح refcount;
    SDL_کړکۍ *کړکۍ;
    HWND hwnd;
    UINT format_متن;
    UINT format_file;
} SDLDrop_موخه;

بنية SDL_کړکۍ_معلومات
{
    SDL_کړکۍ *کړکۍ;
    HWND hwnd;
    HWND پلار;
    HDC hdc;
    HDC mdc;
    HINSTANCE hinstance;
    HBITMAP hbm;
    HICON hicon;
    WNDPROC wndproc;
    HHOOK keyboard_hook;
    WPARAM mouse_button_flags;
    LPARAM وروستی_اشاره_ګر_update;
    WCHAR لوړ_surrogate;
    bool initializing;
    bool expected_resize;
    bool دننه_border_change;
    bool دننه_title_click;
    Uint8 focus_click_pending;
    bool postpone_clipcursor;
    bool clipcursor_queued;
    bool windowed_ډېرپېښ_was_maximized;
    bool دننه_کړکۍ_deactivation;
    bool force_ws_maximizebox;
    bool disable_move_اندازه_events;
    bool showing_کړکۍ;
    صحيح دننه_modal_loop;
    صحيح وروستی_modal_پلنوالی;
    صحيح وروستی_modal_لوړوالی;
    RECT initial_اندازه_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_پلار_with_کړکۍ;
    WCHAR *ICMFileName;
    SDL_کړکۍ_Erase_Background_ډېرپېښ hint_erase_background_ډېرپېښ;
    bool taskbar_button_created;
    بنية SDL_Video_معلومات *videodata;
#که_تعریف_شوی SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#د_که_پای

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDrop_موخه *drop_موخه;
};

خارجي bool WIN_Create_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PropertiesID create_props);
خارجي فراغ WIN_سېټ_کړکۍ_Title(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool WIN_سېټ_کړکۍ_Icon(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_Surface *icon);
خارجي bool WIN_سېټ_کړکۍ_Position(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ WIN_سېټ_کړکۍ_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool WIN_Get_کړکۍ_Borders_اندازه(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *سر, صحيح *کیڼ, صحيح *bottom, صحيح *ښی);
خارجي فراغ WIN_Get_کړکۍ_اندازه_دننه_Pixels(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, صحيح *پلنوالی, صحيح *لوړوالی);
خارجي bool WIN_سېټ_کړکۍ_Opacity(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, عائم opacity);
خارجي فراغ WIN_Show_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ WIN_Hide_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ WIN_Raise_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ WIN_Maximize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ WIN_Minimize_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ WIN_Restore_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ WIN_سېټ_کړکۍ_Bordered(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool bordered);
خارجي فراغ WIN_سېټ_کړکۍ_Resizable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool resizable);
خارجي فراغ WIN_سېټ_کړکۍ_Always_On_سر(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool on_سر);
خارجي SDL_Fullscreen_پایله WIN_سېټ_کړکۍ_Fullscreen(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ WIN_Update_کړکۍ_ICCProfile(SDL_کړکۍ *کړکۍ, bool send_event);
خارجي فراغ *WIN_Get_کړکۍ_ICCProfile(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, size_t *اندازه);
خارجي bool WIN_سېټ_کړکۍ_Mouse_Rect(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool WIN_سېټ_کړکۍ_Mouse_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed);
خارجي bool WIN_سېټ_کړکۍ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool grabbed);
خارجي فراغ WIN_Destroy_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ WIN_On_کړکۍ_Enter(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي فراغ WIN_UpdateClipCursor(SDL_کړکۍ *کړکۍ);
خارجي فراغ WIN_Unclip_Cursor_For_کړکۍ(SDL_کړکۍ *کړکۍ);
خارجي bool WIN_سېټ_کړکۍ_موندنه_Test(SDL_کړکۍ *کړکۍ, bool enabled);
خارجي فراغ WIN_AcceptDragAndDrop(SDL_کړکۍ *کړکۍ, bool accept);
خارجي bool WIN_Flash_کړکۍ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_FlashOperation operation);
خارجي bool WIN_Apply_کړکۍ_پرمختګ(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ);
خارجي bool WIN_سېټ_کړکۍ_Position_دننی(SDL_کړکۍ *کړکۍ, UINT flags, SDL_کړکۍ_Rect rect_type);
خارجي فراغ WIN_Show_کړکۍ_System_Menu(SDL_کړکۍ *کړکۍ, صحيح x, صحيح y);
خارجي bool WIN_سېټ_کړکۍ_Focusable(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool focusable);
خارجي bool WIN_Adjust_کړکۍ_Rect(SDL_کړکۍ *کړکۍ, صحيح *x, صحيح *y, صحيح *پلنوالی, صحيح *لوړوالی, SDL_کړکۍ_Rect rect_type);
خارجي bool WIN_Adjust_کړکۍ_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT چوکاټ_dpi);
خارجي bool WIN_سېټ_کړکۍ_پلار(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_کړکۍ *پلار);
خارجي bool WIN_سېټ_کړکۍ_Modal(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, bool modal);

// Ends C function definitions when using C++
#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای // SDL_windowswindow_h_
