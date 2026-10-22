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

#నిర్వచితం_కాకపోతే SDL_x11window_h_
#నిర్వచించు SDL_x11window_h_

/* We need to queue the focus in/out changes because they may occur during
   video mode changes and we can respond to them by triggering more mode
   changes.
*/
#నిర్వచించు PENDING_FOCUS_సమయం 200

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
#అన్తర్భావ <EGL/egl.h>
#అయితే_ముగింపు

రకనిర్వచనం గణన
{
    PENDING_FOCUS_NONE,
    PENDING_FOCUS_లోపల,
    PENDING_FOCUS_బహిర్గతం
} PendingFocusEnum;

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    SDL_కిటికీ *కిటికీ;
    కిటికీ_2 xwindow;
    Visual *visual;
    Colormap colormap;
#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
    // MIT shared memory extension information
    bool use_mitshm;
    XShmSegmentInfo shminfo;
#అయితే_ముగింపు
    XImage *ximage;
    GC gc;
    XIC ic;
    bool created;
    పూర్ణాంకం border_ఎడమ;
    పూర్ణాంకం border_కుడి;
    పూర్ణాంకం border_శిఖరం;
    పూర్ణాంకం border_bottom;
    bool xinput2_mouse_enabled;
    bool xinput2_keyboard_enabled;
    bool mouse_grabbed;
    Uint64 చివరి_focus_event_సమయం;
    గుర్తులేని దీర్ఘ ignore_button_press_serial;
    PendingFocusEnum pending_focus;
    Uint64 pending_focus_సమయం;
    bool pending_move;
    SDL_బిందువు pending_move_బిందువు;
    XConfigureEvent చివరి_xconfigure;
    XConfigureEvent pending_xconfigure;
    నిర్మాణం SDL_Video_దత్తాంశం *videodata;
    గుర్తులేని దీర్ఘ user_సమయం;
    Atom xdnd_req;
    కిటికీ_2 xdnd_ఆధారం;
    bool flashing_కిటికీ;
    Uint64 flash_cancel_సమయం;
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    EGLSurface egl_surface;
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
    bool సూచిక_barrier_చురుకైన;
    సూచిక_Barrier barrier[4];
    SDL_Rect barrier_rect;
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XFIXES
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
    XSyncCounter resize_counter;
    XSync_విలువ resize_id;
    bool resize_లోపల_పురోగతి;
#అయితే_ముగింపు /* SDL_VIDEO_DRIVER_X11_XSYNC */

    SDL_Rect expected;
    SDL_Display_బహుళకం requested_fullscreen_బహుళకం;

    గణన
    {
        X11_PENDING_OP_NONE = 0x00,
        X11_PENDING_OP_RESTORE = 0x01,
        X11_PENDING_OP_MINIMIZE = 0x02,
        X11_PENDING_OP_MAXIMIZE = 0x04,
        X11_PENDING_OP_FULLSCREEN = 0x08,
        X11_PENDING_OP_MOVE = 0x10,
        X11_PENDING_OP_RESIZE = 0x20
    } pending_operation;

    గణన
    {
        X11_కొలత_MOVE_EVENTS_DISABLE = 0x01, // Events are completely disabled.
        X11_కొలత_MOVE_EVENTS_WAIT_FOR_BORDERS = 0x02, // Events are disabled until a _NET_FRAME_EXTENTS event arrives.
    } కొలత_move_event_flags;

    bool pending_కొలత;
    bool pending_position;
    bool fs_repositioned;
    bool కిటికీ_was_maximized;
    bool మునుపటి_borders_nonzero;
    bool toggle_borders;
    bool fullscreen_borders_forced_on;
    bool was_shown;
    bool emit_కొలత_move_after_property_notify;
    SDL_తగిలింది_Test_ఫలితం తగిలింది_test_ఫలితం;
    bool pending_grab;

    XPoint xim_spot;
    అక్షరం *preedit_పాఠ్యం;
    XIMFeedback *preedit_feedback;
    పూర్ణాంకం preedit_నిడివి;
    పూర్ణాంకం preedit_cursor;
    bool ime_needs_clear_composition;
};

బాహ్య శూన్య X11_సమితి_Net_WMState(SDL_VideoDevice *_this, కిటికీ_2 xwindow, SDL_కిటికీ_Flags flags);
బాహ్య SDL_కిటికీ_Flags X11_GetNetWMState(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, కిటికీ_2 xwindow);

బాహ్య bool X11_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య అక్షరం *X11_Get_కిటికీ_Title(SDL_VideoDevice *_this, కిటికీ_2 xwindow);
బాహ్య శూన్య X11_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool X11_సమితి_కిటికీ_Icon(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_Surface *icon);
బాహ్య bool X11_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య X11_సమితి_కిటికీ_Minimum_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య X11_సమితి_కిటికీ_గరిష్ఠ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య X11_సమితి_కిటికీ_Aspect_నిష్పత్తి(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool X11_Get_కిటికీ_Borders_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం *శిఖరం, పూర్ణాంకం *ఎడమ, పూర్ణాంకం *bottom, పూర్ణాంకం *కుడి);
బాహ్య bool X11_సమితి_కిటికీ_Opacity(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, దశాంశం opacity);
బాహ్య bool X11_సమితి_కిటికీ_మాతృ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ *మాతృ);
బాహ్య bool X11_సమితి_కిటికీ_Modal(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool modal);
బాహ్య శూన్య X11_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య X11_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య X11_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య X11_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య X11_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య X11_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య X11_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య X11_సమితి_కిటికీ_Bordered(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool bordered);
బాహ్య శూన్య X11_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable);
బాహ్య శూన్య X11_సమితి_కిటికీ_Always_On_శిఖరం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool on_శిఖరం);
బాహ్య SDL_Fullscreen_ఫలితం X11_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
బాహ్య శూన్య *X11_Get_కిటికీ_ICCProfile(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, size_t *కొలత);
బాహ్య bool X11_సమితి_కిటికీ_Mouse_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed);
బాహ్య bool X11_సమితి_కిటికీ_Keyboard_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed);
బాహ్య శూన్య X11_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool X11_సమితి_కిటికీ_తగిలింది_Test(SDL_కిటికీ *కిటికీ, bool enabled);
బాహ్య శూన్య X11_AcceptDragAndDrop(SDL_కిటికీ *కిటికీ, bool accept);
బాహ్య bool X11_Flash_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_FlashOperation operation);
బాహ్య శూన్య X11_Show_కిటికీ_System_Menu(SDL_కిటికీ *కిటికీ, పూర్ణాంకం x, పూర్ణాంకం y);
బాహ్య bool X11_Sync_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool X11_సమితి_కిటికీ_Focusable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool focusable);

బాహ్య bool SDL_X11_సమితి_కిటికీ_Title(Display *display, కిటికీ_2 xwindow, అక్షరం *title);
బాహ్య శూన్య X11_Update_కిటికీ_Position(SDL_కిటికీ *కిటికీ, bool use_current_position);
బాహ్య శూన్య X11_సమితి_కిటికీ_Min_Max(SDL_కిటికీ *కిటికీ, bool use_current);

#అయితే_ముగింపు // SDL_x11window_h_
