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
#अन्तर्भाव "SDL_internal.h"

#ifndef SDL_windowswindow_h_
#define SDL_windowswindow_h_

#ifdef SDL_VIDEO_OPENGL_EGL
#अन्तर्भाव "../SDL_egl_c.h"
#अन्यथा
#अन्तर्भाव "../SDL_sysvideo.h"
#endif

// Set up for C function definitions, even when using C++
#ifdef __cplusplus
बाह्य "C" {
#endif

प्रकारनिर्देश गणना SDL_WindowRect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_WindowRect;

प्रकारनिर्देश गणना SDL_WindowEraseBackgroundMode
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_WindowEraseBackgroundMode;

प्रकारनिर्देश संरचना
{
    शून्य **lpVtbl;
    पूर्णाङ्क refcount;
    SDL_Window *window;
    HWND hwnd;
    UINT format_text;
    UINT format_file;
} SDLDropTarget;

संरचना SDL_WindowData
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
    WCHAR ऊपरी_surrogate;
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
    पूर्णाङ्क in_modal_loop;
    पूर्णाङ्क last_modal_width;
    पूर्णाङ्क last_modal_height;
    RECT initial_size_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_parent_with_window;
    WCHAR *ICMFileName;
    SDL_WindowEraseBackgroundMode hint_erase_background_mode;
    bool taskbar_button_created;
    संरचना SDL_VideoData *videodata;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDropTarget *drop_target;
};

बाह्य bool WIN_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य शून्य WIN_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
बाह्य bool WIN_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य WIN_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *शीर्ष, पूर्णाङ्क *बायाँ, पूर्णाङ्क *bottom, पूर्णाङ्क *दायाँ);
बाह्य शून्य WIN_GetWindowSizeInPixels(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क *width, पूर्णाङ्क *height);
बाह्य bool WIN_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, भिन्न opacity);
बाह्य शून्य WIN_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य WIN_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य WIN_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य WIN_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य WIN_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य WIN_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य WIN_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
बाह्य शून्य WIN_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
बाह्य शून्य WIN_Set_Window_Always_On_शीर्ष(SDL_VideoDevice *_this, SDL_Window *window, bool on_शीर्ष);
बाह्य SDL_FullscreenResult WIN_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य शून्य WIN_UpdateWindowICCProfile(SDL_Window *window, bool send_event);
बाह्य शून्य *WIN_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, माप_प्रकार *size);
बाह्य bool WIN_SetWindowMouseRect(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य bool WIN_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य शून्य WIN_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य WIN_OnWindowEnter(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य शून्य WIN_UpdateClipCursor(SDL_Window *window);
बाह्य शून्य WIN_UnclipCursorForWindow(SDL_Window *window);
बाह्य bool WIN_SetWindowHitTest(SDL_Window *window, bool enabled);
बाह्य शून्य WIN_AcceptDragAndDrop(SDL_Window *window, bool accept);
बाह्य bool WIN_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
बाह्य bool WIN_ApplyWindowProgress(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool WIN_SetWindowPositionInternal(SDL_Window *window, UINT flags, SDL_WindowRect rect_type);
बाह्य शून्य WIN_ShowWindowSystemMenu(SDL_Window *window, पूर्णाङ्क x, पूर्णाङ्क y);
बाह्य bool WIN_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);
बाह्य bool WIN_AdjustWindowRect(SDL_Window *window, पूर्णाङ्क *x, पूर्णाङ्क *y, पूर्णाङ्क *width, पूर्णाङ्क *height, SDL_WindowRect rect_type);
बाह्य bool WIN_AdjustWindowRectForHWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi);
बाह्य bool WIN_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
बाह्य bool WIN_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);

// Ends C function definitions when using C++
#ifdef __cplusplus
}
#endif

#endif // SDL_windowswindow_h_
