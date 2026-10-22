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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_windowswindow_h_
#నిర్వచించు SDL_windowswindow_h_

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
#అన్తర్భావ "../SDL_egl_c.h"
#లేకపోతే
#అన్తర్భావ "../SDL_sysvideo.h"
#అయితే_ముగింపు

// Set up for C function definitions, even when using C++
#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

రకనిర్వచనం గణన SDL_కిటికీ_Rect
{
    SDL_WINDOWRECT_CURRENT,
    SDL_WINDOWRECT_WINDOWED,
    SDL_WINDOWRECT_FLOATING,
    SDL_WINDOWRECT_PENDING
} SDL_కిటికీ_Rect;

రకనిర్వచనం గణన SDL_కిటికీ_Erase_Background_బహుళకం
{
    SDL_ERASEBACKGROUNDMODE_NEVER,
    SDL_ERASEBACKGROUNDMODE_INITIAL,
    SDL_ERASEBACKGROUNDMODE_ALWAYS,
} SDL_కిటికీ_Erase_Background_బహుళకం;

రకనిర్వచనం నిర్మాణం
{
    శూన్య **lpVtbl;
    పూర్ణాంకం refcount;
    SDL_కిటికీ *కిటికీ;
    HWND hwnd;
    UINT format_పాఠ్యం;
    UINT format_file;
} SDLDrop_లక్ష్యం;

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    SDL_కిటికీ *కిటికీ;
    HWND hwnd;
    HWND మాతృ;
    HDC hdc;
    HDC mdc;
    HINSTANCE hinstance;
    HBITMAP hbm;
    HICON hicon;
    WNDPROC wndproc;
    HHOOK keyboard_hook;
    WPARAM mouse_button_flags;
    LPARAM చివరి_సూచిక_update;
    WCHAR ఎగువ_surrogate;
    bool initializing;
    bool expected_resize;
    bool లోపల_border_change;
    bool లోపల_title_click;
    Uint8 focus_click_pending;
    bool postpone_clipcursor;
    bool clipcursor_queued;
    bool windowed_బహుళకం_was_maximized;
    bool లోపల_కిటికీ_deactivation;
    bool force_ws_maximizebox;
    bool disable_move_కొలత_events;
    bool showing_కిటికీ;
    పూర్ణాంకం లోపల_modal_loop;
    పూర్ణాంకం చివరి_modal_వెడల్పు;
    పూర్ణాంకం చివరి_modal_ఎత్తు;
    RECT initial_కొలత_rect;
    RECT cursor_clipped_rect; // last successfully committed clipping rect for this window
    RECT cursor_ctrlock_rect; // this is Windows-specific, but probably does not need to be per-window
    bool mouse_tracked;
    bool destroy_మాతృ_with_కిటికీ;
    WCHAR *ICMFileName;
    SDL_కిటికీ_Erase_Background_బహుళకం hint_erase_background_బహుళకం;
    bool taskbar_button_created;
    నిర్మాణం SDL_Video_దత్తాంశం *videodata;
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#అయితే_ముగింపు

    // Whether we retain the content of the window when changing state
    UINT copybits_flag;
    SDLDrop_లక్ష్యం *drop_లక్ష్యం;
};

బాహ్య bool WIN_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య శూన్య WIN_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool WIN_సమితి_కిటికీ_Icon(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *icon);
బాహ్య bool WIN_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య WIN_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool WIN_Get_కిటికీ_Borders_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *శిఖరం, పూర్ణాంకం *ఎడమ, పూర్ణాంకం *bottom, పూర్ణాంకం *కుడి);
బాహ్య శూన్య WIN_Get_కిటికీ_కొలత_లోపల_Pixels(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *వెడల్పు, పూర్ణాంకం *ఎత్తు);
బాహ్య bool WIN_సమితి_కిటికీ_Opacity(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, దశాంశం opacity);
బాహ్య శూన్య WIN_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య WIN_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య WIN_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య WIN_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య WIN_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య WIN_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య WIN_సమితి_కిటికీ_Bordered(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool bordered);
బాహ్య శూన్య WIN_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable);
బాహ్య శూన్య WIN_సమితి_కిటికీ_Always_On_శిఖరం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool on_శిఖరం);
బాహ్య SDL_Fullscreen_ఫలితం WIN_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
బాహ్య శూన్య WIN_Update_కిటికీ_ICCProfile(SDL_కిటికీ *కిటికీ, bool send_event);
బాహ్య శూన్య *WIN_Get_కిటికీ_ICCProfile(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, size_t *కొలత);
బాహ్య bool WIN_సమితి_కిటికీ_Mouse_Rect(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool WIN_సమితి_కిటికీ_Mouse_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed);
బాహ్య bool WIN_సమితి_కిటికీ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed);
బాహ్య శూన్య WIN_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య WIN_On_కిటికీ_Enter(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య WIN_UpdateClipCursor(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య WIN_Unclip_Cursor_For_కిటికీ(SDL_కిటికీ *కిటికీ);
బాహ్య bool WIN_సమితి_కిటికీ_తగిలింది_Test(SDL_కిటికీ *కిటికీ, bool enabled);
బాహ్య శూన్య WIN_AcceptDragAndDrop(SDL_కిటికీ *కిటికీ, bool accept);
బాహ్య bool WIN_Flash_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_FlashOperation operation);
బాహ్య bool WIN_Apply_కిటికీ_పురోగతి(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool WIN_సమితి_కిటికీ_Position_అంతర్గత(SDL_కిటికీ *కిటికీ, UINT flags, SDL_కిటికీ_Rect rect_type);
బాహ్య శూన్య WIN_Show_కిటికీ_System_Menu(SDL_కిటికీ *కిటికీ, పూర్ణాంకం x, పూర్ణాంకం y);
బాహ్య bool WIN_సమితి_కిటికీ_Focusable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool focusable);
బాహ్య bool WIN_Adjust_కిటికీ_Rect(SDL_కిటికీ *కిటికీ, పూర్ణాంకం *x, పూర్ణాంకం *y, పూర్ణాంకం *వెడల్పు, పూర్ణాంకం *ఎత్తు, SDL_కిటికీ_Rect rect_type);
బాహ్య bool WIN_Adjust_కిటికీ_Rect_For_HWND(HWND hwnd, LPRECT lpRect, UINT చట్రం_dpi);
బాహ్య bool WIN_సమితి_కిటికీ_మాతృ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ *మాతృ);
బాహ్య bool WIN_సమితి_కిటికీ_Modal(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool modal);

// Ends C function definitions when using C++
#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_windowswindow_h_
