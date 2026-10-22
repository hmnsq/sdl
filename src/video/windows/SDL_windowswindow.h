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
#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_windowswindow_h_
#define SDL_windowswindow_h_

#ifdef SDL_VIDEO_OPENGL_EGL
#অন্তর্ভাব "../SDL_egl_c.h"
#অন্যথা
#অন্তর্ভাব "../SDL_sysvideo.h"
#endif

// Set up for C function definitions, even when using C++
#ifdef __cplusplus
বাহ্যিক "C" {
#endif

প্রকারলেখ গণনা SDL_WindowRect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_WindowRect;

প্রকারলেখ গণনা SDL_WindowEraseBackgroundMode
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_WindowEraseBackgroundMode;

প্রকারলেখ কাঠামো
{
    শূন্য **lpVtbl;
    পূর্ণসংখ্যা refcount;
    SDL_Window *window;
    HWND hwnd;
    UINT format_text;
    UINT format_file;
} SDLDropTarget;

কাঠামো SDL_Window_তথ্য
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
    WCHAR উপরের_surrogate;
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
    bool disable_move_আকার_events;
    bool showing_window;
    পূর্ণসংখ্যা in_modal_loop;
    পূর্ণসংখ্যা last_modal_width;
    পূর্ণসংখ্যা last_modal_height;
    RECT initial_আকার_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_parent_with_window;
    WCHAR *ICMFileName;
    SDL_WindowEraseBackgroundMode hint_erase_background_mode;
    bool taskbar_button_created;
    কাঠামো SDL_Video_তথ্য *videodata;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDropTarget *drop_target;
};

বাহ্যিক bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
বাহ্যিক শূন্য WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
বাহ্যিক bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য WIN_Set_Window_আকার(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool WIN_Get_Window_Borders_আকার(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণসংখ্যা *শীর্ষ, পূর্ণসংখ্যা *বাম, পূর্ণসংখ্যা *bottom, পূর্ণসংখ্যা *ডান);
বাহ্যিক শূন্য WIN_Get_Window_আকার_In_Pixels(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণসংখ্যা *width, পূর্ণসংখ্যা *height);
বাহ্যিক bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, দশমিক opacity);
বাহ্যিক শূন্য WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
বাহ্যিক শূন্য WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
বাহ্যিক শূন্য WIN_Set_Window_Always_On_শীর্ষ(SDL_VideoDevice *_this, SDL_Window *window, bool on_শীর্ষ);
বাহ্যিক SDL_Fullscreen_ফলাফল WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
বাহ্যিক শূন্য WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event);
বাহ্যিক শূন্য *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *আকার_2);
বাহ্যিক bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
বাহ্যিক bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
বাহ্যিক শূন্য WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক শূন্য WIN_UpdateClipCursor(SDL_Window *window);
বাহ্যিক শূন্য WIN_UnclipCursorForWindow(SDL_Window *window);
বাহ্যিক bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled);
বাহ্যিক শূন্য WIN_AcceptDragAndDrop(SDL_Window *window, bool accept);
বাহ্যিক bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
বাহ্যিক bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window);
বাহ্যিক bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type);
বাহ্যিক শূন্য WIN_ShowWindowSystemMenu(SDL_Window *window, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y);
বাহ্যিক bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
বাহ্যিক bool WIN_AdjustWindowRect(SDL_Window *window, পূর্ণসংখ্যা *x, পূর্ণসংখ্যা *y, পূর্ণসংখ্যা *width, পূর্ণসংখ্যা *height, SDL_WindowRect rect_type);
বাহ্যিক bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi);
বাহ্যিক bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
বাহ্যিক bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);

// Ends C function definitions when using C++
#ifdef __cplusplus
}
#endif

#endif // SDL_windowswindow_h_
