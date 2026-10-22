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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_windowswindow_h_
#define SDL_windowswindow_h_

#ifdef SDL_VIDEO_OPENGL_EGL
#ଅନ୍ତର୍ଭାଵ "../SDL_egl_c.h"
#ଅନ୍ୟଥା
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#endif

// Set up for C function definitions, even when using C++
#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା SDL_WindowRect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_WindowRect;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା SDL_WindowEraseBackgroundMode
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_WindowEraseBackgroundMode;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    ଶୂନ୍ୟ **lpVtbl;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା refcount;
    SDL_Window *window;
    HWND hwnd;
    UINT format_text;
    UINT format_file;
} SDLDropTarget;

ସଂରଚନା SDL_WindowData
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
    WCHAR ଉପର_surrogate;
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
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_modal_loop;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା last_modal_width;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା last_modal_height;
    RECT initial_size_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_parent_with_window;
    WCHAR *ICMFileName;
    SDL_WindowEraseBackgroundMode hint_erase_background_mode;
    bool taskbar_button_created;
    ସଂରଚନା SDL_VideoData *videodata;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDropTarget *drop_target;
};

ବାହ୍ୟ bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
ବାହ୍ୟ bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଶୀର୍ଷ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ବାମ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *bottom, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ଡାହାଣ);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *height);
ବାହ୍ୟ bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, ଦଶମିକ opacity);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_Set_Window_Always_On_ଶୀର୍ଷ(SDL_VideoDevice *_this, SDL_Window *window, bool on_ଶୀର୍ଷ);
ବାହ୍ୟ SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event);
ବାହ୍ୟ ଶୂନ୍ୟ *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
ବାହ୍ୟ bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ବାହ୍ୟ bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_UpdateClipCursor(SDL_Window *window);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_UnclipCursorForWindow(SDL_Window *window);
ବାହ୍ୟ bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_AcceptDragAndDrop(SDL_Window *window, bool accept);
ବାହ୍ୟ bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
ବାହ୍ୟ bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window);
ବାହ୍ୟ bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type);
ବାହ୍ୟ ଶୂନ୍ୟ WIN_ShowWindowSystemMenu(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y);
ବାହ୍ୟ bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
ବାହ୍ୟ bool WIN_AdjustWindowRect(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *height, SDL_WindowRect rect_type);
ବାହ୍ୟ bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi);
ବାହ୍ୟ bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
ବାହ୍ୟ bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);

// Ends C function definitions when using C++
#ifdef __cplusplus
}
#endif

#endif // SDL_windowswindow_h_
