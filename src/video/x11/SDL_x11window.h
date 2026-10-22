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

#यदि_अपरिभाषितम् SDL_x11window_h_
#परिभाषय SDL_x11window_h_

/* We need to queue the focus in/out changes because they may occur during
   video mode changes and we can respond to them by triggering more mode
   changes.
*/
#परिभाषय PENDING_FOCUS_TIME 200

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
#अन्तर्भाव <EGL/egl.h>
#यदि_अन्तः

प्रकारनिर्देश गणना
{
    PENDING_FOCUS_NONE,
    PENDING_FOCUS_अन्तर्,
    PENDING_FOCUS_बहिर्गमनम्
} PendingFocusEnum;

संरचना SDL_गवाक्षः_दत्त
{
    SDL_गवाक्षः *गवाक्षः;
    गवाक्षः_2 xwindow;
    Visual *visual;
    Colormap colormap;
#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
    // MIT shared memory extension information
    bool use_mitshm;
    XShmSegmentInfo shminfo;
#यदि_अन्तः
    XImage *ximage;
    GC gc;
    XIC ic;
    bool created;
    पूर्णाङ्क border_वामः;
    पूर्णाङ्क border_दक्षिणः;
    पूर्णाङ्क border_शिखरम्;
    पूर्णाङ्क border_bottom;
    bool xinput2_mouse_enabled;
    bool xinput2_keyboard_enabled;
    bool mouse_grabbed;
    Uint64 चरमः_focus_event_time;
    अचिह्नित दीर्घ ignore_button_press_serial;
    PendingFocusEnum pending_focus;
    Uint64 pending_focus_time;
    bool pending_move;
    SDL_Point pending_move_point;
    XConfigureEvent चरमः_xconfigure;
    XConfigureEvent pending_xconfigure;
    संरचना SDL_Video_दत्त *videodata;
    अचिह्नित दीर्घ user_time;
    Atom xdnd_req;
    गवाक्षः_2 xdnd_source;
    bool flashing_गवाक्षः;
    Uint64 flash_cancel_time;
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
    bool pointer_barrier_सक्रिय;
    PointerBarrier barrier[4];
    SDL_Rect barrier_rect;
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XFIXES
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
    XSync_गणक resize_गणक;
    XSync_मानम् resize_id;
    bool resize_अन्तर्_प्रगतिः;
#यदि_अन्तः /* SDL_VIDEO_DRIVER_X11_XSYNC */

    SDL_Rect expected;
    SDL_Display_बहुलकम् requested_fullscreen_बहुलकम्;

    गणना
    {
        X11_PENDING_OP_NONE = 0x00,
        X11_PENDING_OP_RESTORE = 0x01,
        X11_PENDING_OP_MINIMIZE = 0x02,
        X11_PENDING_OP_MAXIMIZE = 0x04,
        X11_PENDING_OP_FULLSCREEN = 0x08,
        X11_PENDING_OP_MOVE = 0x10,
        X11_PENDING_OP_RESIZE = 0x20
    } pending_operation;

    गणना
    {
        X11_आकार_MOVE_EVENTS_DISABLE = 0x01, // Events are completely disabled.
        X11_आकार_MOVE_EVENTS_WAIT_FOR_BORDERS = 0x02, // Events are disabled until a _NET_FRAME_EXTENTS event arrives.
    } आकार_move_event_flags;

    bool pending_आकार;
    bool pending_position;
    bool fs_repositioned;
    bool गवाक्षः_was_maximized;
    bool previous_borders_nonzero;
    bool toggle_borders;
    bool fullscreen_borders_forced_on;
    bool was_shown;
    bool emit_आकार_move_after_property_notify;
    SDL_लब्धम्_Test_परिणाम लब्धम्_test_परिणाम;
    bool pending_grab;

    XPoint xim_spot;
    वर्ण *preedit_text;
    XIMFeedback *preedit_feedback;
    पूर्णाङ्क preedit_दीर्घता;
    पूर्णाङ्क preedit_cursor;
    bool ime_needs_clear_composition;
};

बाह्य शून्य X11_समुच्चयः_Net_WMState(SDL_VideoDevice *_this, गवाक्षः_2 xwindow, SDL_गवाक्षः_Flags flags);
बाह्य SDL_गवाक्षः_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, गवाक्षः_2 xwindow);

बाह्य bool X11_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
बाह्य वर्ण *X11_Get_गवाक्षः_Title(SDL_VideoDevice *_this, गवाक्षः_2 xwindow);
बाह्य शून्य X11_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool X11_समुच्चयः_गवाक्षः_Icon(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_Surface *icon);
बाह्य bool X11_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_समुच्चयः_गवाक्षः_Minimum_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_समुच्चयः_गवाक्षः_अधिकतमम्_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_समुच्चयः_गवाक्षः_Aspect_अनुपातः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool X11_Get_गवाक्षः_Borders_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क *शिखरम्, पूर्णाङ्क *वामः, पूर्णाङ्क *bottom, पूर्णाङ्क *दक्षिणः);
बाह्य bool X11_समुच्चयः_गवाक्षः_Opacity(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, भिन्न opacity);
बाह्य bool X11_समुच्चयः_गवाक्षः_Parent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः *parent);
बाह्य bool X11_समुच्चयः_गवाक्षः_Modal(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool modal);
बाह्य शून्य X11_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य X11_समुच्चयः_गवाक्षः_Bordered(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool bordered);
बाह्य शून्य X11_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool resizable);
बाह्य शून्य X11_समुच्चयः_गवाक्षः_Always_On_शिखरम्(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool on_शिखरम्);
बाह्य SDL_Fullscreen_परिणाम X11_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य शून्य *X11_Get_गवाक्षः_ICCProfile(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, size_t *आकार);
बाह्य bool X11_समुच्चयः_गवाक्षः_Mouse_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed);
बाह्य bool X11_समुच्चयः_गवाक्षः_Keyboard_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed);
बाह्य शून्य X11_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool X11_समुच्चयः_गवाक्षः_लब्धम्_Test(SDL_गवाक्षः *गवाक्षः, bool enabled);
बाह्य शून्य X11_AcceptDragAndDrop(SDL_गवाक्षः *गवाक्षः, bool accept);
बाह्य bool X11_Flash_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_FlashOperation operation);
बाह्य शून्य X11_Show_गवाक्षः_System_Menu(SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क x, पूर्णाङ्क y);
बाह्य bool X11_Sync_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool X11_समुच्चयः_गवाक्षः_Focusable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool focusable);

बाह्य bool SDL_X11_समुच्चयः_गवाक्षः_Title(Display *display, गवाक्षः_2 xwindow, वर्ण *title);
बाह्य शून्य X11_Update_गवाक्षः_Position(SDL_गवाक्षः *गवाक्षः, bool use_current_position);
बाह्य शून्य X11_समुच्चयः_गवाक्षः_Min_Max(SDL_गवाक्षः *गवाक्षः, bool use_current);

#यदि_अन्तः // SDL_x11window_h_
