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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_x11window_h_
#घोषणा SDL_x11window_h_

/* We need to queue the focus in/out changes because they may occur during
   video mode changes and we can respond to them by triggering more mode
   changes.
*/
#घोषणा PENDING_FOCUS_TIME 200

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
#समावेश <EGL/egl.h>
#पूर्ण_अगर

प्रकार क्रमागत
{
    PENDING_FOCUS_NONE,
    PENDING_FOCUS_IN,
    PENDING_FOCUS_OUT
} PendingFocusEnum;

काष्ठा SDL_Window_तथ्य
{
    SDL_Window *window;
    Window xwindow;
    Visual *visual;
    Colormap colormap;
#अगर_अघोषित NO_SHARED_MEMORY
    // MIT shared memory extension information
    bool use_mitshm;
    XShmSegmentInfo shminfo;
#पूर्ण_अगर
    XImage *ximage;
    GC gc;
    XIC ic;
    bool created;
    पूर्णांक border_बायाँ;
    पूर्णांक border_दायाँ;
    पूर्णांक border_शीर्ष;
    पूर्णांक border_bottom;
    bool xinput2_mouse_enabled;
    bool xinput2_keyboard_enabled;
    bool mouse_grabbed;
    Uint64 last_focus_event_time;
    अचिन्हित दीर्घ ignore_button_press_serial;
    PendingFocusEnum pending_focus;
    Uint64 pending_focus_time;
    bool pending_move;
    SDL_Point pending_move_point;
    XConfigureEvent last_xconfigure;
    XConfigureEvent pending_xconfigure;
    काष्ठा SDL_Video_तथ्य *videodata;
    अचिन्हित दीर्घ user_time;
    Atom xdnd_req;
    Window xdnd_source;
    bool flashing_window;
    Uint64 flash_cancel_time;
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XFIXES
    bool pointer_barrier_active;
    PointerBarrier barrier[4];
    SDL_Rect barrier_rect;
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XFIXES
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSYNC
    XSync_गणक resize_गणक;
    XSync_मूल्य resize_id;
    bool resize_in_progress;
#पूर्ण_अगर /* SDL_VIDEO_DRIVER_X11_XSYNC */

    SDL_Rect expected;
    SDL_DisplayMode requested_fullscreen_mode;

    क्रमागत
    {
        X11_PENDING_OP_NONE = 0x00,
        X11_PENDING_OP_RESTORE = 0x01,
        X11_PENDING_OP_MINIMIZE = 0x02,
        X11_PENDING_OP_MAXIMIZE = 0x04,
        X11_PENDING_OP_FULLSCREEN = 0x08,
        X11_PENDING_OP_MOVE = 0x10,
        X11_PENDING_OP_RESIZE = 0x20
    } pending_operation;

    क्रमागत
    {
        X11_आकार_MOVE_EVENTS_DISABLE = 0x01, // Events are completely disabled.
        X11_आकार_MOVE_EVENTS_WAIT_FOR_BORDERS = 0x02, // Events are disabled until a _NET_FRAME_EXTENTS event arrives.
    } आकार_move_event_flags;

    bool pending_आकार;
    bool pending_position;
    bool fs_repositioned;
    bool window_was_maximized;
    bool previous_borders_nonzero;
    bool toggle_borders;
    bool fullscreen_borders_forced_on;
    bool was_shown;
    bool emit_आकार_move_after_property_notify;
    SDL_Hit_Test_परिणाम hit_test_परिणाम;
    bool pending_grab;

    XPoint xim_spot;
    अक्षर *preedit_text;
    XIMFeedback *preedit_feedback;
    पूर्णांक preedit_लंबाई;
    पूर्णांक preedit_cursor;
    bool ime_needs_clear_composition;
};

बाह्य व्योम X11_SetNetWMState(SDL_VideoDevice *_this, Window xwindow, SDL_WindowFlags flags);
बाह्य SDL_WindowFlags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_Window *window, Window xwindow);

बाह्य bool X11_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
बाह्य अक्षर *X11_GetWindowTitle(SDL_VideoDevice *_this, Window xwindow);
बाह्य व्योम X11_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool X11_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
बाह्य bool X11_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_Set_Window_Minimum_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_Set_Window_Maximum_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool X11_Get_Window_Borders_आकार(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक *शीर्ष, पूर्णांक *बायाँ, पूर्णांक *bottom, पूर्णांक *दायाँ);
बाह्य bool X11_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, भग्न opacity);
बाह्य bool X11_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
बाह्य bool X11_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
बाह्य व्योम X11_Set_Window_आकार(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य व्योम X11_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
बाह्य व्योम X11_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
बाह्य व्योम X11_Set_Window_Always_On_शीर्ष(SDL_VideoDevice *_this, SDL_Window *window, bool on_शीर्ष);
बाह्य SDL_Fullscreen_परिणाम X11_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य व्योम *X11_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, माप_प्रकार *आकार);
बाह्य bool X11_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य bool X11_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
बाह्य व्योम X11_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool X11_SetWindowHitTest(SDL_Window *window, bool enabled);
बाह्य व्योम X11_AcceptDragAndDrop(SDL_Window *window, bool accept);
बाह्य bool X11_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
बाह्य व्योम X11_ShowWindowSystemMenu(SDL_Window *window, पूर्णांक x, पूर्णांक y);
बाह्य bool X11_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool X11_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);

बाह्य bool SDL_X11_SetWindowTitle(Display *display, Window xwindow, अक्षर *title);
बाह्य व्योम X11_UpdateWindowPosition(SDL_Window *window, bool use_current_position);
बाह्य व्योम X11_SetWindowMinMax(SDL_Window *window, bool use_current);

#पूर्ण_अगर // SDL_x11window_h_
