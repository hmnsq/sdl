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
#அந்தர்பாவ "SDL_internal.h"

#ifndef SDL_x11window_h_
#define SDL_x11window_h_

/* We need to queue the focus in/out changes because they may occur during
   video mode changes and we can respond to them by triggering more mode
   changes.
*/
#define PENDING_FOCUS_TIME 200

#ifdef SDL_VIDEO_OPENGL_EGL
#அந்தர்பாவ <EGL/egl.h>
#endif

வகைவரை எண்ணிக்கை
{
    PENDING_FOCUS_NONE,
    PENDING_FOCUS_IN,
    PENDING_FOCUS_OUT
} PendingFocusEnum;

கட்டமைப்பு SDL_WindowData
{
    SDL_Window *window;
    Window xwindow;
    Visual *visual;
    Colormap colormap;
#ifndef NO_SHARED_MEMORY
    // MIT shared memory extension information
    bool use_mitshm;
    XShmSegmentInfo shminfo;
#endif
    XImage *ximage;
    GC gc;
    XIC ic;
    bool created;
    முழு border_இடது;
    முழு border_வலது;
    முழு border_உச்சி;
    முழு border_bottom;
    bool xinput2_mouse_enabled;
    bool xinput2_keyboard_enabled;
    bool mouse_grabbed;
    Uint64 last_focus_event_time;
    unsigned long ignore_button_press_serial;
    PendingFocusEnum pending_focus;
    Uint64 pending_focus_time;
    bool pending_move;
    SDL_Point pending_move_point;
    XConfigureEvent last_xconfigure;
    XConfigureEvent pending_xconfigure;
    கட்டமைப்பு SDL_VideoData *videodata;
    unsigned long user_time;
    Atom xdnd_req;
    Window xdnd_source;
    bool flashing_window;
    Uint64 flash_cancel_time;
#ifdef SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    bool pointer_barrier_active;
    PointerBarrier barrier[4];
    SDL_Rect barrier_rect;
#endif // SDL_VIDEO_DRIVER_X11_XFIXES
#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
    XSyncCounter resize_counter;
    XSync_மதிப்பு resize_id;
    bool resize_in_progress;
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

    SDL_Rect expected;
    SDL_DisplayMode requested_fullscreen_mode;

    எண்ணிக்கை
    {
        X11_PENDING_OP_NONE = 0x00,
        X11_PENDING_OP_RESTORE = 0x01,
        X11_PENDING_OP_MINIMIZE = 0x02,
        X11_PENDING_OP_MAXIMIZE = 0x04,
        X11_PENDING_OP_FULLSCREEN = 0x08,
        X11_PENDING_OP_MOVE = 0x10,
        X11_PENDING_OP_RESIZE = 0x20
    } pending_operation;

    எண்ணிக்கை
    {
        X11_SIZE_MOVE_EVENTS_DISABLE = 0x01, // Events are completely disabled.
        X11_SIZE_MOVE_EVENTS_WAIT_FOR_BORDERS = 0x02, // Events are disabled until a _NET_FRAME_EXTENTS event arrives.
    } size_move_event_flags;

    bool pending_size;
    bool pending_position;
    bool fs_repositioned;
    bool window_was_maximized;
    bool previous_borders_nonzero;
    bool toggle_borders;
    bool fullscreen_borders_forced_on;
    bool was_shown;
    bool emit_size_move_after_property_notify;
    SDL_HitTestResult hit_test_result;
    bool pending_grab;

    XPoint xim_spot;
    எழுத்து *preedit_text;
    XIMFeedback *preedit_feedback;
    முழு preedit_length;
    முழு preedit_cursor;
    bool ime_needs_clear_composition;
};

வெளி வெறுமை X11_SetNetWMState(SDL_VideoDevice *_this, Window xwindow, SDL_WindowFlags flags);
வெளி SDL_WindowFlags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_Window *window, Window xwindow);

வெளி bool X11_CreateWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_PropertiesID create_props);
வெளி எழுத்து *X11_GetWindowTitle(SDL_VideoDevice *_this, Window xwindow);
வெளி வெறுமை X11_SetWindowTitle(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool X11_SetWindowIcon(SDL_VideoDevice *_this, SDL_Window *window, SDL_Surface *icon);
வெளி bool X11_SetWindowPosition(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை X11_SetWindowMinimumSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை X11_SetWindowMaximumSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை X11_SetWindowAspectRatio(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool X11_GetWindowBordersSize(SDL_VideoDevice *_this, SDL_Window *window, முழு *உச்சி, முழு *இடது, முழு *bottom, முழு *வலது);
வெளி bool X11_SetWindowOpacity(SDL_VideoDevice *_this, SDL_Window *window, தசம opacity);
வெளி bool X11_SetWindowParent(SDL_VideoDevice *_this, SDL_Window *window, SDL_Window *parent);
வெளி bool X11_SetWindowModal(SDL_VideoDevice *_this, SDL_Window *window, bool modal);
வெளி வெறுமை X11_SetWindowSize(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை X11_ShowWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை X11_HideWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை X11_RaiseWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை X11_MaximizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை X11_MinimizeWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை X11_RestoreWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி வெறுமை X11_SetWindowBordered(SDL_VideoDevice *_this, SDL_Window *window, bool bordered);
வெளி வெறுமை X11_SetWindowResizable(SDL_VideoDevice *_this, SDL_Window *window, bool resizable);
வெளி வெறுமை X11_Set_Window_Always_On_உச்சி(SDL_VideoDevice *_this, SDL_Window *window, bool on_உச்சி);
வெளி SDL_FullscreenResult X11_SetWindowFullscreen(SDL_VideoDevice *_this, SDL_Window *window, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
வெளி வெறுமை *X11_GetWindowICCProfile(SDL_VideoDevice *_this, SDL_Window *window, size_t *size);
வெளி bool X11_SetWindowMouseGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
வெளி bool X11_SetWindowKeyboardGrab(SDL_VideoDevice *_this, SDL_Window *window, bool grabbed);
வெளி வெறுமை X11_DestroyWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool X11_SetWindowHitTest(SDL_Window *window, bool enabled);
வெளி வெறுமை X11_AcceptDragAndDrop(SDL_Window *window, bool accept);
வெளி bool X11_FlashWindow(SDL_VideoDevice *_this, SDL_Window *window, SDL_FlashOperation operation);
வெளி வெறுமை X11_ShowWindowSystemMenu(SDL_Window *window, முழு x, முழு y);
வெளி bool X11_SyncWindow(SDL_VideoDevice *_this, SDL_Window *window);
வெளி bool X11_SetWindowFocusable(SDL_VideoDevice *_this, SDL_Window *window, bool focusable);

வெளி bool SDL_X11_SetWindowTitle(Display *display, Window xwindow, எழுத்து *title);
வெளி வெறுமை X11_UpdateWindowPosition(SDL_Window *window, bool use_current_position);
வெளி வெறுமை X11_SetWindowMinMax(SDL_Window *window, bool use_current);

#endif // SDL_x11window_h_
