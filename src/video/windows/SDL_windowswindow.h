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

#यदि_अपरिभाषितम् SDL_windowswindow_h_
#परिभाषय SDL_windowswindow_h_

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
#अन्तर्भाव "../SDL_egl_c.h"
#अन्यथा
#अन्तर्भाव "../SDL_sysvideo.h"
#यदि_अन्तः

// Set up for C function definitions, even when using C++
#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

प्रकारनिर्देश गणना SDL_गवाक्षः_Rect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_गवाक्षः_Rect;

प्रकारनिर्देश गणना SDL_गवाक्षः_Erase_Background_बहुलकम्
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_गवाक्षः_Erase_Background_बहुलकम्;

प्रकारनिर्देश संरचना
{
    शून्य **lpVtbl;
    पूर्णाङ्क refcount;
    SDL_गवाक्षः *गवाक्षः;
    HWND hwnd;
    UINT format_text;
    UINT format_file;
} SDLDropTarget;

संरचना SDL_गवाक्षः_दत्त
{
    SDL_गवाक्षः *गवाक्षः;
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
    LPARAM चरमः_pointer_update;
    WCHAR उच्चः_surrogate;
    bool initializing;
    bool expected_resize;
    bool अन्तर्_border_change;
    bool अन्तर्_title_click;
    Uint8 focus_click_pending;
    bool postpone_clipcursor;
    bool clipcursor_queued;
    bool windowed_बहुलकम्_was_maximized;
    bool अन्तर्_गवाक्षः_deactivation;
    bool force_ws_maximizebox;
    bool disable_move_आकार_events;
    bool showing_गवाक्षः;
    पूर्णाङ्क अन्तर्_modal_loop;
    पूर्णाङ्क चरमः_modal_विस्तारः;
    पूर्णाङ्क चरमः_modal_height;
    RECT initial_आकार_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_parent_with_गवाक्षः;
    WCHAR *ICMFileName;
    SDL_गवाक्षः_Erase_Background_बहुलकम् hint_erase_background_बहुलकम्;
    bool taskbar_button_created;
    संरचना SDL_Video_दत्त *videodata;
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#यदि_अन्तः

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDropTarget *drop_target;
};

बाह्य bool WIN_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
बाह्य शून्य WIN_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool WIN_समुच्चयः_गवाक्षः_Icon(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *icon);
बाह्य bool WIN_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य WIN_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool WIN_Get_गवाक्षः_Borders_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *शिखरम्, पूर्णाङ्क *वामः, पूर्णाङ्क *bottom, पूर्णाङ्क *दक्षिणः);
बाह्य शून्य WIN_Get_गवाक्षः_आकार_अन्तर्_Pixels(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *विस्तारः, पूर्णाङ्क *height);
बाह्य bool WIN_समुच्चयः_गवाक्षः_Opacity(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, भिन्न opacity);
बाह्य शून्य WIN_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य WIN_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य WIN_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य WIN_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य WIN_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य WIN_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य WIN_समुच्चयः_गवाक्षः_Bordered(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool bordered);
बाह्य शून्य WIN_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool resizable);
बाह्य शून्य WIN_समुच्चयः_गवाक्षः_Always_On_शिखरम्(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool on_शिखरम्);
बाह्य SDL_Fullscreen_परिणाम WIN_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य शून्य WIN_Update_गवाक्षः_ICCProfile(SDL_गवाक्षः *गवाक्षः, bool send_event);
बाह्य शून्य *WIN_Get_गवाक्षः_ICCProfile(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, size_t *आकार);
बाह्य bool WIN_समुच्चयः_गवाक्षः_Mouse_Rect(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool WIN_समुच्चयः_गवाक्षः_Mouse_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed);
बाह्य bool WIN_समुच्चयः_गवाक्षः_Keyboard_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed);
बाह्य शून्य WIN_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य WIN_On_गवाक्षः_Enter(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य WIN_UpdateClipCursor(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य WIN_Unclip_Cursor_For_गवाक्षः(SDL_गवाक्षः *गवाक्षः);
बाह्य bool WIN_समुच्चयः_गवाक्षः_लब्धम्_Test(SDL_गवाक्षः *गवाक्षः, bool enabled);
बाह्य शून्य WIN_AcceptDragAndDrop(SDL_गवाक्षः *गवाक्षः, bool accept);
बाह्य bool WIN_Flash_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_FlashOperation operation);
बाह्य bool WIN_Apply_गवाक्षः_प्रगतिः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool WIN_समुच्चयः_गवाक्षः_Position_आन्तरिकम्(SDL_गवाक्षः *गवाक्षः, UINT flags, SDL_गवाक्षः_Rect rect_type);
बाह्य शून्य WIN_Show_गवाक्षः_System_Menu(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क x, पूर्णाङ्क y);
बाह्य bool WIN_समुच्चयः_गवाक्षः_Focusable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool focusable);
बाह्य bool WIN_Adjust_गवाक्षः_Rect(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *x, पूर्णाङ्क *y, पूर्णाङ्क *विस्तारः, पूर्णाङ्क *height, SDL_गवाक्षः_Rect rect_type);
बाह्य bool WIN_Adjust_गवाक्षः_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT frame_dpi);
बाह्य bool WIN_समुच्चयः_गवाक्षः_Parent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः *parent);
बाह्य bool WIN_समुच्चयः_गवाक्षः_Modal(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool modal);

// Ends C function definitions when using C++
#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः // SDL_windowswindow_h_
