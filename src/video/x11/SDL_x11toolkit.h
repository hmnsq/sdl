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

#ifndef SDL_x11toolkit_h_
#define SDL_x11toolkit_h_

#অন্তর্ভাব "../../SDL_list.h"
#অন্তর্ভাব "SDL_x11video.h"
#অন্তর্ভাব "SDL_x11dyn.h"
#অন্তর্ভাব "SDL_x11settings.h"
#অন্তর্ভাব "SDL_x11toolkit.h"
#অন্তর্ভাব "xsettings-client.h"
#ifdef HAVE_FRIBIDI_H
#অন্তর্ভাব "../../core/unix/SDL_fribidi.h"
#endif
#ifdef HAVE_LIBTHAI_H
#অন্তর্ভাব "../../core/unix/SDL_libthai.h"
#endif

#ifdef SDL_VIDEO_DRIVER_X11

/* Various predefined paddings */
#define SDL_TOOLKIT_X11_ELEMENT_PADDING 4
#define SDL_TOOLKIT_X11_ELEMENT_PADDING_2 12
#define SDL_TOOLKIT_X11_ELEMENT_PADDING_3 8
#define SDL_TOOLKIT_X11_ELEMENT_PADDING_4 16
#define SDL_TOOLKIT_X11_ELEMENT_PADDING_5 3

প্রকারনির্দেশ গণনা SDL_ToolkitChildModeX11
{
    SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG,
    SDL_TOOLKIT_WINDOW_MODE_X11_CHILD, /* For embedding into a normal SDL_Window */
    SDL_TOOLKIT_WINDOW_MODE_X11_MENU,
    SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP
} SDL_ToolkitWindowModeX11;

প্রকারনির্দেশ গণনা SDL_ToolkitThaiEncodingX11
{
    SDL_TOOLKIT_THAI_ENCODING_X11_NONE,
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS, /* -0 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN, /* -2 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC, /* -1 */
    SDL_TOOLKIT_THAI_ENCODING_X11_8859,
    SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE
} SDL_ToolkitThaiEncodingX11;

প্রকারনির্দেশ গণনা SDL_ToolkitThaiFontX11
{
    SDL_TOOLKIT_THAI_FONT_X11_OFFSET,
    SDL_TOOLKIT_THAI_FONT_X11_CELL
} SDL_ToolkitThaiFontX11;

প্রকারনির্দেশ সংরচনা SDL_ToolkitWindowX11
{
    /* Locale */
    বর্ণ *origlocale;

    /* Mode */
    SDL_ToolkitWindowModeX11 mode;

    /* Display */
    Display *display;
    পূর্ণাঙ্ক screen;
    bool display_close;

    /* Parent */
    SDL_VideoDevice *parent_device;
    SDL_Window *parent;
    সংরচনা SDL_ToolkitWindowX11 *tk_parent;

    /* Window */
    Window window;
    Drawable drawable;
#ifndef NO_SHARED_MEMORY
    XImage *image;
    XShmSegmentInfo shm_info;
    পূর্ণাঙ্ক shm_bytes_per_সারি;
#endif

    /* Visuals and drawing */
    Visual *visual;
    XVisualInfo vi;
    Colormap cmap;
    GC ctx;
    পূর্ণাঙ্ক depth;
    bool pixmap;

    /* X11 extensions */
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    XdbeBackBuffer buf;
    bool xdbe; // Whether Xdbe is present or not
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    bool xrandr; // Whether Xrandr is present or not
#endif
#ifndef NO_SHARED_MEMORY
    bool shm;
    Bool shm_pixmap;
#endif
    bool utf8;
    /* Atoms */
    Atom wm_protocols;
    Atom wm_delete_message;

    /* Window and pixmap sizes */
    পূর্ণাঙ্ক window_width;  // Window width.
    পূর্ণাঙ্ক window_height; // Window height.
    পূর্ণাঙ্ক pixmap_width;
    পূর্ণাঙ্ক pixmap_height;
    পূর্ণাঙ্ক window_x;
    পূর্ণাঙ্ক window_y;

    /* XSettings and scaling */
    XSettingsClient *xsettings;
    bool xsettings_first_time;
    পূর্ণাঙ্ক iscale;
    ভিন্ন scale;

    /* Font */
    XFontSet font_set;        // for UTF-8 systems
    XFontStruct *font_struct; // Latin1 (ASCII) fallback.
    SDL_ToolkitThaiEncodingX11 thai_encoding;
    SDL_ToolkitThaiFontX11 thai_font;
    
    /* Control colors */
    ধ্রুব SDL_MessageBoxColor *color_hints;
    XColor xcolor[SDL_MESSAGEBOX_COLOR_গুনতি];
    XColor xcolor_bevel_l1;
    XColor xcolor_bevel_l2;
    XColor xcolor_bevel_d;
    XColor xcolor_pressed;
    XColor xcolor_disabled_text;

    /* Control list */
    bool has_focus;
    সংরচনা SDL_ToolkitControlX11 *focused_control;
    সংরচনা SDL_ToolkitControlX11 *fiddled_control;
    সংরচনা SDL_ToolkitControlX11 **controls;
    size_t controls_sz;
    সংরচনা SDL_ToolkitControlX11 **dyn_controls;
    size_t dyn_controls_sz;

    /* User callbacks */
    শূন্য *cb_data;
    শূন্য (*cb_on_scale_change)(সংরচনা SDL_ToolkitWindowX11 *, শূন্য *);

    /* Popup windows */
    SDL_List_গ্রন্থি *popup_windows;

    /* Event loop */
    XEvent *e;
    সংরচনা SDL_ToolkitControlX11 *previous_control;
    সংরচনা SDL_ToolkitControlX11 *চাবি_control_esc;
    সংরচনা SDL_ToolkitControlX11 *চাবি_control_enter;
    চাবি_Sym last_চাবি_pressed;
    পূর্ণাঙ্ক ev_i;
    ভিন্ন ev_scale;
    ভিন্ন ev_iscale;
    bool draw;
    bool close;
    long event_mask;

#ifdef HAVE_FRIBIDI_H
    /* BIDI engine */
    SDL_FriBidi *fribidi;
    bool do_shaping;
#endif

#ifdef HAVE_LIBTHAI_H
    SDL_LibThai *th;
#endif

    bool flip_interface;
} SDL_ToolkitWindowX11;

প্রকারনির্দেশ গণনা SDL_ToolkitControlStateX11
{
    SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL,
    SDL_TOOLKIT_CONTROL_STATE_X11_HOVER,
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED, /* Key/Button Up */
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD, /* Key/Button Down */
    SDL_TOOLKIT_CONTROL_STATE_X11_DISABLED
} SDL_ToolkitControlStateX11;

প্রকারনির্দেশ সংরচনা SDL_ToolkitControlX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlStateX11 state;
    SDL_Rect rect;
    bool selected;
    bool dynamic;
    bool is_default_enter;
    bool is_default_esc;
    bool do_size;

    /* User data */
    শূন্য *data;

    /* Virtual functions */
    শূন্য (*func_draw)(সংরচনা SDL_ToolkitControlX11 *);
    শূন্য (*func_calc_size)(সংরচনা SDL_ToolkitControlX11 *);
    শূন্য (*func_on_scale_change)(সংরচনা SDL_ToolkitControlX11 *);
    শূন্য (*func_on_state_change)(সংরচনা SDL_ToolkitControlX11 *);
    শূন্য (*func_free)(সংরচনা SDL_ToolkitControlX11 *);
} SDL_ToolkitControlX11;

প্রকারনির্দেশ সংরচনা SDL_ToolkitMenuItemX11
{
    ধ্রুব বর্ণ *utf8;
    bool checkbox;
    bool checked;
    bool disabled;
    শূন্য *cb_data;
    শূন্য (*cb)(সংরচনা SDL_ToolkitMenuItemX11 *, শূন্য *);
    SDL_List_গ্রন্থি *sub_menu;

    /* Internal use */
    SDL_Rect utf8_rect;
    SDL_Rect hover_rect;
    SDL_Rect check_rect;
    SDL_ToolkitControlStateX11 state;
    পূর্ণাঙ্ক arrow_x;
    পূর্ণাঙ্ক arrow_y;
    bool reverse_arrows;
} SDL_ToolkitMenuItemX11;

/* WINDOW FUNCTIONS */
বাহ্য SDL_ToolkitWindowX11 *X11Toolkit_CreateWindowStruct(SDL_Window *parent, SDL_ToolkitWindowX11 *tkparent, SDL_ToolkitWindowModeX11 mode, ধ্রুব SDL_MessageBoxColor *colorhints, bool create_new_display);
বাহ্য bool X11Toolkit_CreateWindowRes(SDL_ToolkitWindowX11 *data, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h, পূর্ণাঙ্ক cx, পূর্ণাঙ্ক cy, বর্ণ *title);
বাহ্য শূন্য X11Toolkit_DoWindowEventLoop(SDL_ToolkitWindowX11 *data);
বাহ্য শূন্য X11Toolkit_ResizeWindow(SDL_ToolkitWindowX11 *data, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h);
বাহ্য শূন্য X11Toolkit_DestroyWindow(SDL_ToolkitWindowX11 *data);
বাহ্য শূন্য X11Toolkit_SignalWindowClose(SDL_ToolkitWindowX11 *data);

/* GENERIC CONTROL FUNCTIONS */
বাহ্য bool X11Toolkit_NotifyControlOfSizeChange(SDL_ToolkitControlX11 *control);

/* ICON CONTROL FUNCTIONS */
বাহ্য SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_ToolkitWindowX11 *window, SDL_MessageBoxFlags flags);

/* LABEL CONTROL FUNCTIONS */
বাহ্য SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_ToolkitWindowX11 *window, বর্ণ *utf8);
বাহ্য পূর্ণাঙ্ক X11_Toolkit_Get_Label_Control_First_সারি_Height(SDL_ToolkitControlX11 *control);

/* BUTTON CONTROL FUNCTIONS */
বাহ্য SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_ToolkitWindowX11 *window, ধ্রুব SDL_MessageBoxButtonData *data);
বাহ্য শূন্য X11Toolkit_RegisterCallbackForButtonControl(SDL_ToolkitControlX11 *control, শূন্য *data, শূন্য (*cb)(সংরচনা SDL_ToolkitControlX11 *, শূন্য *));
বাহ্য ধ্রুব SDL_MessageBoxButtonData *X11Toolkit_GetButtonControlData(SDL_ToolkitControlX11 *control);

#endif // SDL_VIDEO_DRIVER_X11

#endif // SDL_x11toolkit_h_
