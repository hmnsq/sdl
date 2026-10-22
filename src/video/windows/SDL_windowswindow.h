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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_windowswindow_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_windowswindow_h_

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_egl_c.h"
#ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਜੇ_ਅੰਤ

// Set up for C function definitions, even when using C++
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ SDL_ਖਿੜਕੀ_Rect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_ਖਿੜਕੀ_Rect;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ SDL_ਖਿੜਕੀ_Erase_Background_ਬਹੁਲਕ
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_ਖਿੜਕੀ_Erase_Background_ਬਹੁਲਕ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਖਾਲੀ **lpVtbl;
    ਪੂਰਨ refcount;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    HWND hwnd;
    UINT format_ਪਾਠ;
    UINT format_file;
} SDLDrop_ਨਿਸ਼ਾਨਾ;

ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    HWND hwnd;
    HWND ਮਾਪਾ;
    HDC hdc;
    HDC mdc;
    HINSTANCE hinstance;
    HBITMAP hbm;
    HICON hicon;
    WNDPROC wndproc;
    HHOOK keyboard_hook;
    WPARAM mouse_button_flags;
    LPARAM ਆਖਰੀ_ਸੂਚਕ_update;
    WCHAR ਉੱਚਾ_surrogate;
    bool initializing;
    bool expected_resize;
    bool ਵਿੱਚ_border_change;
    bool ਵਿੱਚ_title_click;
    Uint8 focus_click_pending;
    bool postpone_clipcursor;
    bool clipcursor_queued;
    bool windowed_ਬਹੁਲਕ_was_maximized;
    bool ਵਿੱਚ_ਖਿੜਕੀ_deactivation;
    bool force_ws_maximizebox;
    bool disable_move_ਮਾਪ_events;
    bool showing_ਖਿੜਕੀ;
    ਪੂਰਨ ਵਿੱਚ_modal_loop;
    ਪੂਰਨ ਆਖਰੀ_modal_ਚੌੜਾਈ;
    ਪੂਰਨ ਆਖਰੀ_modal_ਉਚਾਈ;
    RECT initial_ਮਾਪ_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_ਮਾਪਾ_with_ਖਿੜਕੀ;
    WCHAR *ICMFileName;
    SDL_ਖਿੜਕੀ_Erase_Background_ਬਹੁਲਕ hint_erase_background_ਬਹੁਲਕ;
    bool taskbar_button_created;
    ਬਣਤਰ SDL_Video_ਅੰਕੜੇ *videodata;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#ਜੇ_ਅੰਤ

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDrop_ਨਿਸ਼ਾਨਾ *drop_ਨਿਸ਼ਾਨਾ;
};

ਬਾਹਰੀ bool WIN_Create_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PropertiesID create_props);
ਬਾਹਰੀ ਖਾਲੀ WIN_ਸੈੱਟ_ਖਿੜਕੀ_Title(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Icon(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_Surface *icon);
ਬਾਹਰੀ bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ WIN_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool WIN_Get_ਖਿੜਕੀ_Borders_ਮਾਪ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *ਸਿਖਰ, ਪੂਰਨ *ਖੱਬਾ, ਪੂਰਨ *bottom, ਪੂਰਨ *ਸੱਜਾ);
ਬਾਹਰੀ ਖਾਲੀ WIN_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *ਚੌੜਾਈ, ਪੂਰਨ *ਉਚਾਈ);
ਬਾਹਰੀ bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Opacity(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ opacity);
ਬਾਹਰੀ ਖਾਲੀ WIN_Show_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ WIN_Hide_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ WIN_Raise_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ WIN_Maximize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ WIN_Minimize_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ WIN_Restore_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ WIN_ਸੈੱਟ_ਖਿੜਕੀ_Bordered(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool bordered);
ਬਾਹਰੀ ਖਾਲੀ WIN_ਸੈੱਟ_ਖਿੜਕੀ_Resizable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool resizable);
ਬਾਹਰੀ ਖਾਲੀ WIN_ਸੈੱਟ_ਖਿੜਕੀ_Always_On_ਸਿਖਰ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool on_ਸਿਖਰ);
ਬਾਹਰੀ SDL_Fullscreen_ਨਤੀਜਾ WIN_ਸੈੱਟ_ਖਿੜਕੀ_Fullscreen(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ਬਾਹਰੀ ਖਾਲੀ WIN_Update_ਖਿੜਕੀ_ICCProfile(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool send_event);
ਬਾਹਰੀ ਖਾਲੀ *WIN_Get_ਖਿੜਕੀ_ICCProfile(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, size_t *ਮਾਪ);
ਬਾਹਰੀ bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed);
ਬਾਹਰੀ bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool grabbed);
ਬਾਹਰੀ ਖਾਲੀ WIN_Destroy_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ WIN_On_ਖਿੜਕੀ_Enter(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ WIN_UpdateClipCursor(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ ਖਾਲੀ WIN_Unclip_Cursor_For_ਖਿੜਕੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_ਪ੍ਰਾਪਤੀ_Test(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool enabled);
ਬਾਹਰੀ ਖਾਲੀ WIN_AcceptDragAndDrop(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool accept);
ਬਾਹਰੀ bool WIN_Flash_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_FlashOperation operation);
ਬਾਹਰੀ bool WIN_Apply_ਖਿੜਕੀ_ਤਰੱਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Position_ਅੰਦਰੂਨੀ(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, UINT flags, SDL_ਖਿੜਕੀ_Rect rect_type);
ਬਾਹਰੀ ਖਾਲੀ WIN_Show_ਖਿੜਕੀ_System_Menu(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ x, ਪੂਰਨ y);
ਬਾਹਰੀ bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Focusable(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool focusable);
ਬਾਹਰੀ bool WIN_Adjust_ਖਿੜਕੀ_Rect(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ *x, ਪੂਰਨ *y, ਪੂਰਨ *ਚੌੜਾਈ, ਪੂਰਨ *ਉਚਾਈ, SDL_ਖਿੜਕੀ_Rect rect_type);
ਬਾਹਰੀ bool WIN_Adjust_ਖਿੜਕੀ_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT ਚੌਖਟਾ_dpi);
ਬਾਹਰੀ bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_ਮਾਪਾ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_ਖਿੜਕੀ *ਮਾਪਾ);
ਬਾਹਰੀ bool WIN_ਸੈੱਟ_ਖਿੜਕੀ_Modal(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, bool modal);

// Ends C function definitions when using C++
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_windowswindow_h_
