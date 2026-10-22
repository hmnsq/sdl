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

#اگر_تعریف_نشده SDL_windowswindow_h_
#تعریف_کن SDL_windowswindow_h_

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
#ضمن "../SDL_egl_c.h"
#وإلا
#ضمن "../SDL_sysvideo.h"
#پایان_اگر

// Set up for C function definitions, even when using C++
#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

تعريفنوع تعداد SDL_پنجره_Rect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_پنجره_Rect;

تعريفنوع تعداد SDL_پنجره_Erase_Background_نما
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_پنجره_Erase_Background_نما;

تعريفنوع بنية
{
    فراغ **lpVtbl;
    صحيح refcount;
    SDL_پنجره *پنجره;
    HWND hwnd;
    UINT format_متن;
    UINT format_file;
} SDLDrop_هدف;

بنية SDL_پنجره_داده
{
    SDL_پنجره *پنجره;
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
    LPARAM آخرین_اشاره_گر_update;
    WCHAR بالا_surrogate;
    bool initializing;
    bool expected_resize;
    bool درون_border_change;
    bool درون_title_click;
    Uint8 focus_click_pending;
    bool postpone_clipcursor;
    bool clipcursor_queued;
    bool windowed_نما_was_maximized;
    bool درون_پنجره_deactivation;
    bool force_ws_maximizebox;
    bool disable_move_اندازه_events;
    bool showing_پنجره;
    صحيح درون_modal_loop;
    صحيح آخرین_modal_عرض;
    صحيح آخرین_modal_ارتفاع;
    RECT initial_اندازه_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_والد_with_پنجره;
    WCHAR *ICMFileName;
    SDL_پنجره_Erase_Background_نما hint_erase_background_نما;
    bool taskbar_button_created;
    بنية SDL_Video_داده *videodata;
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#پایان_اگر

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDrop_هدف *drop_هدف;
};

خارجي bool WIN_Create_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PropertiesID create_props);
خارجي فراغ WIN_مجموعه_پنجره_Title(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool WIN_مجموعه_پنجره_Icon(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_Surface *icon);
خارجي bool WIN_مجموعه_پنجره_Position(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ WIN_مجموعه_پنجره_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool WIN_Get_پنجره_Borders_اندازه(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *بالاترین, صحيح *چپ, صحيح *bottom, صحيح *راست);
خارجي فراغ WIN_Get_پنجره_اندازه_درون_Pixels(SDL_VideoDevice *_this, SDL_پنجره *پنجره, صحيح *عرض, صحيح *ارتفاع);
خارجي bool WIN_مجموعه_پنجره_Opacity(SDL_VideoDevice *_this, SDL_پنجره *پنجره, عائم opacity);
خارجي فراغ WIN_Show_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ WIN_Hide_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ WIN_Raise_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ WIN_Maximize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ WIN_Minimize_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ WIN_Restore_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ WIN_مجموعه_پنجره_Bordered(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool bordered);
خارجي فراغ WIN_مجموعه_پنجره_Resizable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool resizable);
خارجي فراغ WIN_مجموعه_پنجره_Always_On_بالاترین(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool on_بالاترین);
خارجي SDL_Fullscreen_نتیجه WIN_مجموعه_پنجره_Fullscreen(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ WIN_Update_پنجره_ICCProfile(SDL_پنجره *پنجره, bool send_event);
خارجي فراغ *WIN_Get_پنجره_ICCProfile(SDL_VideoDevice *_this, SDL_پنجره *پنجره, size_t *اندازه);
خارجي bool WIN_مجموعه_پنجره_Mouse_Rect(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool WIN_مجموعه_پنجره_Mouse_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed);
خارجي bool WIN_مجموعه_پنجره_Keyboard_Grab(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool grabbed);
خارجي فراغ WIN_Destroy_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ WIN_On_پنجره_Enter(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي فراغ WIN_UpdateClipCursor(SDL_پنجره *پنجره);
خارجي فراغ WIN_Unclip_Cursor_For_پنجره(SDL_پنجره *پنجره);
خارجي bool WIN_مجموعه_پنجره_اصابت_Test(SDL_پنجره *پنجره, bool enabled);
خارجي فراغ WIN_AcceptDragAndDrop(SDL_پنجره *پنجره, bool accept);
خارجي bool WIN_Flash_پنجره(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_FlashOperation operation);
خارجي bool WIN_Apply_پنجره_پیشرفت(SDL_VideoDevice *_this, SDL_پنجره *پنجره);
خارجي bool WIN_مجموعه_پنجره_Position_داخلی(SDL_پنجره *پنجره, UINT flags, SDL_پنجره_Rect rect_type);
خارجي فراغ WIN_Show_پنجره_System_Menu(SDL_پنجره *پنجره, صحيح x, صحيح y);
خارجي bool WIN_مجموعه_پنجره_Focusable(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool focusable);
خارجي bool WIN_Adjust_پنجره_Rect(SDL_پنجره *پنجره, صحيح *x, صحيح *y, صحيح *عرض, صحيح *ارتفاع, SDL_پنجره_Rect rect_type);
خارجي bool WIN_Adjust_پنجره_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT قاب_dpi);
خارجي bool WIN_مجموعه_پنجره_والد(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_پنجره *والد);
خارجي bool WIN_مجموعه_پنجره_Modal(SDL_VideoDevice *_this, SDL_پنجره *پنجره, bool modal);

// Ends C function definitions when using C++
#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر // SDL_windowswindow_h_
