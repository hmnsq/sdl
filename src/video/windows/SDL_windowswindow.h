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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_windowswindow_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_windowswindow_h_

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
#ಅನ್ತರ್ಭಾವ "../SDL_egl_c.h"
#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಆದರೆ_ಅಂತ್ಯ

// Set up for C function definitions, even when using C++
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ SDL_ಕಿಟಕಿ_Rect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_ಕಿಟಕಿ_Rect;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ SDL_ಕಿಟಕಿ_Erase_Background_ಬಹುಲಕ
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_ಕಿಟಕಿ_Erase_Background_ಬಹುಲಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಶೂನ್ಯ **lpVtbl;
    ಪೂರ್ಣಾಂಕ refcount;
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    HWND hwnd;
    UINT format_ಪಠ್ಯ;
    UINT format_file;
} SDLDrop_ಗುರಿ;

ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
    SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;
    HWND hwnd;
    HWND ಪೋಷಕ;
    HDC hdc;
    HDC mdc;
    HINSTANCE hinstance;
    HBITMAP hbm;
    HICON hicon;
    WNDPROC wndproc;
    HHOOK keyboard_hook;
    WPARAM mouse_button_flags;
    LPARAM ಕೊನೆಯ_ಸೂಚಕ_update;
    WCHAR ಮೇಲಿನ_surrogate;
    bool initializing;
    bool expected_resize;
    bool ಒಳ_border_change;
    bool ಒಳ_title_click;
    Uint8 focus_click_pending;
    bool postpone_clipcursor;
    bool clipcursor_queued;
    bool windowed_ಬಹುಲಕ_was_maximized;
    bool ಒಳ_ಕಿಟಕಿ_deactivation;
    bool force_ws_maximizebox;
    bool disable_move_ಗಾತ್ರ_events;
    bool showing_ಕಿಟಕಿ;
    ಪೂರ್ಣಾಂಕ ಒಳ_modal_loop;
    ಪೂರ್ಣಾಂಕ ಕೊನೆಯ_modal_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ ಕೊನೆಯ_modal_ಎತ್ತರ;
    RECT initial_ಗಾತ್ರ_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_ಪೋಷಕ_with_ಕಿಟಕಿ;
    WCHAR *ICMFileName;
    SDL_ಕಿಟಕಿ_Erase_Background_ಬಹುಲಕ hint_erase_background_ಬಹುಲಕ;
    bool taskbar_button_created;
    ರಚನೆ SDL_Video_ದತ್ತಾಂಶ *videodata;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#ಆದರೆ_ಅಂತ್ಯ

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDrop_ಗುರಿ *drop_ಗುರಿ;
};

ಬಾಹ್ಯ bool WIN_Create_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PropertiesID create_props);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_ಗಣ_ಕಿಟಕಿ_Title(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool WIN_ಗಣ_ಕಿಟಕಿ_Icon(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_Surface *icon);
ಬಾಹ್ಯ bool WIN_ಗಣ_ಕಿಟಕಿ_Position(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_ಗಣ_ಕಿಟಕಿ_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool WIN_Get_ಕಿಟಕಿ_Borders_ಗಾತ್ರ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *ತುದಿ, ಪೂರ್ಣಾಂಕ *ಎಡ, ಪೂರ್ಣಾಂಕ *bottom, ಪೂರ್ಣಾಂಕ *ಬಲ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *ಅಗಲ, ಪೂರ್ಣಾಂಕ *ಎತ್ತರ);
ಬಾಹ್ಯ bool WIN_ಗಣ_ಕಿಟಕಿ_Opacity(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ opacity);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Show_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Hide_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Raise_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Maximize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Minimize_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Restore_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_ಗಣ_ಕಿಟಕಿ_Bordered(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool bordered);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_ಗಣ_ಕಿಟಕಿ_Resizable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool resizable);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_ಗಣ_ಕಿಟಕಿ_Always_On_ತುದಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool on_ತುದಿ);
ಬಾಹ್ಯ SDL_Fullscreen_ಫಲಿತಾಂಶ WIN_ಗಣ_ಕಿಟಕಿ_Fullscreen(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Update_ಕಿಟಕಿ_ICCProfile(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool send_event);
ಬಾಹ್ಯ ಶೂನ್ಯ *WIN_Get_ಕಿಟಕಿ_ICCProfile(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, size_t *ಗಾತ್ರ_2);
ಬಾಹ್ಯ bool WIN_ಗಣ_ಕಿಟಕಿ_Mouse_Rect(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool WIN_ಗಣ_ಕಿಟಕಿ_Mouse_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed);
ಬಾಹ್ಯ bool WIN_ಗಣ_ಕಿಟಕಿ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool grabbed);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Destroy_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_On_ಕಿಟಕಿ_Enter(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_UpdateClipCursor(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Unclip_Cursor_For_ಕಿಟಕಿ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool WIN_ಗಣ_ಕಿಟಕಿ_ದೊರಕಿತು_Test(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool enabled);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_AcceptDragAndDrop(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool accept);
ಬಾಹ್ಯ bool WIN_Flash_ಕಿಟಕಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_FlashOperation operation);
ಬಾಹ್ಯ bool WIN_Apply_ಕಿಟಕಿ_ಪ್ರಗತಿ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ);
ಬಾಹ್ಯ bool WIN_ಗಣ_ಕಿಟಕಿ_Position_ಆಂತರಿಕ(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, UINT flags, SDL_ಕಿಟಕಿ_Rect rect_type);
ಬಾಹ್ಯ ಶೂನ್ಯ WIN_Show_ಕಿಟಕಿ_System_Menu(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y);
ಬಾಹ್ಯ bool WIN_ಗಣ_ಕಿಟಕಿ_Focusable(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool focusable);
ಬಾಹ್ಯ bool WIN_Adjust_ಕಿಟಕಿ_Rect(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ *x, ಪೂರ್ಣಾಂಕ *y, ಪೂರ್ಣಾಂಕ *ಅಗಲ, ಪೂರ್ಣಾಂಕ *ಎತ್ತರ, SDL_ಕಿಟಕಿ_Rect rect_type);
ಬಾಹ್ಯ bool WIN_Adjust_ಕಿಟಕಿ_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT ಚೌಕಟ್ಟು_dpi);
ಬಾಹ್ಯ bool WIN_ಗಣ_ಕಿಟಕಿ_ಪೋಷಕ(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_ಕಿಟಕಿ *ಪೋಷಕ);
ಬಾಹ್ಯ bool WIN_ಗಣ_ಕಿಟಕಿ_Modal(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, bool modal);

// Ends C function definitions when using C++
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_windowswindow_h_
