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

#جيڪڏهن_وصف_نه_ٿيل SDL_windowswindow_h_
#وصف_ڪريو SDL_windowswindow_h_

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
#ضمن "../SDL_egl_c.h"
#وإلا
#ضمن "../SDL_sysvideo.h"
#جيڪڏهن_پورو

// Set up for C function definitions, even when using C++
#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

تعريفنوع تعداد SDL_دري_Rect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_دري_Rect;

تعريفنوع تعداد SDL_دري_Erase_Background_گهڻائي
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_دري_Erase_Background_گهڻائي;

تعريفنوع بنية
{
    فراغ **lpVtbl;
    صحيح refcount;
    SDL_دري *دري;
    HWND hwnd;
    UINT format_متن;
    UINT format_file;
} SDLDrop_هدف;

بنية SDL_دري_معلومات
{
    SDL_دري *دري;
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
    LPARAM آخري_اشارو_update;
    WCHAR مٿاهون_surrogate;
    bool initializing;
    bool expected_resize;
    bool اندريون_border_change;
    bool اندريون_title_click;
    Uint8 focus_click_pending;
    bool postpone_clipcursor;
    bool clipcursor_queued;
    bool windowed_گهڻائي_was_maximized;
    bool اندريون_دري_deactivation;
    bool force_ws_maximizebox;
    bool disable_move_سائيز_events;
    bool showing_دري;
    صحيح اندريون_modal_loop;
    صحيح آخري_modal_ويڪر;
    صحيح آخري_modal_اوچائي;
    RECT initial_سائيز_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_والد_with_دري;
    WCHAR *ICMFileName;
    SDL_دري_Erase_Background_گهڻائي hint_erase_background_گهڻائي;
    bool taskbar_button_created;
    بنية SDL_Video_معلومات *videodata;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#جيڪڏهن_پورو

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDrop_هدف *drop_هدف;
};

خارجي bool WIN_Create_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PropertiesID create_props);
خارجي فراغ WIN_سيٽ_دري_Title(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool WIN_سيٽ_دري_Icon(SDL_VideoDevice *_this, SDL_دري *دري, SDL_Surface *icon);
خارجي bool WIN_سيٽ_دري_Position(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ WIN_سيٽ_دري_سائيز(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool WIN_Get_دري_Borders_سائيز(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *چوٽي, صحيح *کاٻو, صحيح *bottom, صحيح *ساڄو);
خارجي فراغ WIN_Get_دري_سائيز_اندريون_Pixels(SDL_VideoDevice *_this, SDL_دري *دري, صحيح *ويڪر, صحيح *اوچائي);
خارجي bool WIN_سيٽ_دري_Opacity(SDL_VideoDevice *_this, SDL_دري *دري, عائم opacity);
خارجي فراغ WIN_Show_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ WIN_Hide_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ WIN_Raise_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ WIN_Maximize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ WIN_Minimize_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ WIN_Restore_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ WIN_سيٽ_دري_Bordered(SDL_VideoDevice *_this, SDL_دري *دري, bool bordered);
خارجي فراغ WIN_سيٽ_دري_Resizable(SDL_VideoDevice *_this, SDL_دري *دري, bool resizable);
خارجي فراغ WIN_سيٽ_دري_Always_On_چوٽي(SDL_VideoDevice *_this, SDL_دري *دري, bool on_چوٽي);
خارجي SDL_Fullscreen_نتيجو WIN_سيٽ_دري_Fullscreen(SDL_VideoDevice *_this, SDL_دري *دري, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ WIN_Update_دري_ICCProfile(SDL_دري *دري, bool send_event);
خارجي فراغ *WIN_Get_دري_ICCProfile(SDL_VideoDevice *_this, SDL_دري *دري, size_t *سائيز);
خارجي bool WIN_سيٽ_دري_Mouse_Rect(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool WIN_سيٽ_دري_Mouse_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed);
خارجي bool WIN_سيٽ_دري_Keyboard_Grab(SDL_VideoDevice *_this, SDL_دري *دري, bool grabbed);
خارجي فراغ WIN_Destroy_دري(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ WIN_On_دري_Enter(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي فراغ WIN_UpdateClipCursor(SDL_دري *دري);
خارجي فراغ WIN_Unclip_Cursor_For_دري(SDL_دري *دري);
خارجي bool WIN_سيٽ_دري_ڪاميابي_Test(SDL_دري *دري, bool enabled);
خارجي فراغ WIN_AcceptDragAndDrop(SDL_دري *دري, bool accept);
خارجي bool WIN_Flash_دري(SDL_VideoDevice *_this, SDL_دري *دري, SDL_FlashOperation operation);
خارجي bool WIN_Apply_دري_ترقي(SDL_VideoDevice *_this, SDL_دري *دري);
خارجي bool WIN_سيٽ_دري_Position_اندروني(SDL_دري *دري, UINT flags, SDL_دري_Rect rect_type);
خارجي فراغ WIN_Show_دري_System_Menu(SDL_دري *دري, صحيح x, صحيح y);
خارجي bool WIN_سيٽ_دري_Focusable(SDL_VideoDevice *_this, SDL_دري *دري, bool focusable);
خارجي bool WIN_Adjust_دري_Rect(SDL_دري *دري, صحيح *x, صحيح *y, صحيح *ويڪر, صحيح *اوچائي, SDL_دري_Rect rect_type);
خارجي bool WIN_Adjust_دري_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT چوکٺو_dpi);
خارجي bool WIN_سيٽ_دري_والد(SDL_VideoDevice *_this, SDL_دري *دري, SDL_دري *والد);
خارجي bool WIN_سيٽ_دري_Modal(SDL_VideoDevice *_this, SDL_دري *دري, bool modal);

// Ends C function definitions when using C++
#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو // SDL_windowswindow_h_
