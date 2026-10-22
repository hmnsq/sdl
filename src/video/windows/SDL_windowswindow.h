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

#ifndef SDL_windowswindow_h_
#define SDL_windowswindow_h_

#ifdef SDL_VIDEO_OPENGL_EGL
#ضمن "../SDL_egl_c.h"
#وإلا
#ضمن "../SDL_sysvideo.h"
#endif

// Set up for C function definitions, even when using C++
#ifdef __cplusplus
خارجي "C" {
#endif

تعريفنوع تعداد SDL_WindowRect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_WindowRect;

تعريفنوع تعداد SDL_WindowEraseBackgroundMode
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_WindowEraseBackgroundMode;

تعريفنوع بنية
{
    فراغ **lpVtbl;
    صحيح refcount;
    SDL_Window *window;
    HWND hwnd;
    UINT format_text;
    UINT format_file;
} SDLDropTarget;

بنية SDL_WindowData
{
    SDL_Window *window;
    HWND hwnd;
    HWND parent;
    HDC hdc;
    HDC mdc;
    HINSTANCE hinstance;
    HBITMAP hbm;
    HICON hicon;
    WNDPROC wndproc;
    HHOOK keyboard_hook;
    WPARAM mouse_button_flags;
    LPARAM last_pointer_update;
    WCHAR يۇقىرى_surrogate;
    bool initializing;
    bool expected_resize;
    bool in_border_change;
    bool in_title_click;
    Uint8 focus_click_pending;
    bool postpone_clipcursor;
    bool clipcursor_queued;
    bool windowed_mode_was_maximized;
    bool in_window_deactivation;
    bool force_ws_maximizebox;
    bool disable_move_size_events;
    bool showing_window;
    صحيح in_modal_loop;
    صحيح last_modal_width;
    صحيح last_modal_height;
    RECT initial_size_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_parent_with_window;
    WCHAR *ICMFileName;
    SDL_WindowEraseBackgroundMode hint_erase_background_mode;
    bool taskbar_button_created;
    بنية SDL_VideoData *videodata;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDropTarget *drop_target;
};

خارجي bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
خارجي فراغ WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
خارجي bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, صحيح *چوققا, صحيح *سول, صحيح *bottom, صحيح *ئوڭ);
خارجي فراغ WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, صحيح *width, صحيح *height);
خارجي bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, عائم opacity);
خارجي فراغ WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
خارجي فراغ WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
خارجي فراغ WIN_Set_Window_Always_On_چوققا(SDL_VideoDevice *_this, SDL_Window *window, bool on_چوققا);
خارجي SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
خارجي فراغ WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event);
خارجي فراغ *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
خارجي bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
خارجي bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
خارجي فراغ WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window);
خارجي فراغ WIN_UpdateClipCursor(SDL_Window *window);
خارجي فراغ WIN_UnclipCursorForWindow(SDL_Window *window);
خارجي bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled);
خارجي فراغ WIN_AcceptDragAndDrop(SDL_Window *window, bool accept);
خارجي bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
خارجي bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type);
خارجي فراغ WIN_ShowWindowSystemMenu(SDL_Window *window, صحيح x, صحيح y);
خارجي bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
خارجي bool WIN_AdjustWindowRect(SDL_Window *window, صحيح *x, صحيح *y, صحيح *width, صحيح *height, SDL_WindowRect rect_type);
خارجي bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi);
خارجي bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
خارجي bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);

// Ends C function definitions when using C++
#ifdef __cplusplus
}
#endif

#endif // SDL_windowswindow_h_
