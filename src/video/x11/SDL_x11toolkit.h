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

#ifndef SDL_x11toolkit_h_
#define SDL_x11toolkit_h_

#अन्तर्भाव "../../SDL_list.h"
#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11dyn.h"
#अन्तर्भाव "SDL_x11settings.h"
#अन्तर्भाव "SDL_x11toolkit.h"
#अन्तर्भाव "xsettings-client.h"
#ifdef HAVE_FRIBIDI_H
#अन्तर्भाव "../../core/unix/SDL_fribidi.h"
#endif
#ifdef HAVE_LIBTHAI_H
#अन्तर्भाव "../../core/unix/SDL_libthai.h"
#endif

#ifdef SDL_VIDEO_DRIVER_X11

/* Various predefined paddings */
#define SDL_TOOLKIT_X11_ELEMENT_PADDING 4
#define SDL_TOOLKIT_X11_ELEMENT_PADDING_2 12
#define SDL_TOOLKIT_X11_ELEMENT_PADDING_3 8
#define SDL_TOOLKIT_X11_ELEMENT_PADDING_4 16
#define SDL_TOOLKIT_X11_ELEMENT_PADDING_5 3

प्रकारनिर्देश गणना SDL_ToolkitChildModeX11
{
    SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG,
    SDL_TOOLKIT_WINDOW_MODE_X11_CHILD, /* For embedding into a normal SDL_Window */
    SDL_TOOLKIT_WINDOW_MODE_X11_MENU,
    SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP
} SDL_ToolkitWindowModeX11;

प्रकारनिर्देश गणना SDL_ToolkitThaiEncodingX11
{
    SDL_TOOLKIT_THAI_ENCODING_X11_NONE,
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS, /* -0 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN, /* -2 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC, /* -1 */
    SDL_TOOLKIT_THAI_ENCODING_X11_8859,
    SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE
} SDL_ToolkitThaiEncodingX11;

प्रकारनिर्देश गणना SDL_ToolkitThaiFontX11
{
    SDL_TOOLKIT_THAI_FONT_X11_OFFSET,
    SDL_TOOLKIT_THAI_FONT_X11_CELL
} SDL_ToolkitThaiFontX11;

प्रकारनिर्देश संरचना SDL_ToolkitWindowX11
{
    /* Locale */
    वर्ण *origlocale;

    /* Mode */
    SDL_ToolkitWindowModeX11 mode;

    /* Display */
    Display *display;
    पूर्णाङ्क screen;
    bool display_close;

    /* Parent */
    SDL_VideoDevice *parent_device;
    SDL_Window *parent;
    संरचना SDL_ToolkitWindowX11 *tk_parent;

    /* Window */
    Window window;
    Drawable drawable;
#ifndef NO_SHARED_MEMORY
    XImage *image;
    XShmSegmentInfo shm_info;
    पूर्णाङ्क shm_bytes_per_ओळ;
#endif

    /* Visuals and drawing */
    Visual *visual;
    XVisualInfo vi;
    Colormap cmap;
    GC ctx;
    पूर्णाङ्क depth;
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
    पूर्णाङ्क window_width;  // Window width.
    पूर्णाङ्क window_height; // Window height.
    पूर्णाङ्क pixmap_width;
    पूर्णाङ्क pixmap_height;
    पूर्णाङ्क window_x;
    पूर्णाङ्क window_y;

    /* XSettings and scaling */
    XSettingsClient *xsettings;
    bool xsettings_first_time;
    पूर्णाङ्क iscale;
    भिन्न scale;

    /* Font */
    XFontSet font_set;        // for UTF-8 systems
    XFontStruct *font_struct; // Latin1 (ASCII) fallback.
    SDL_ToolkitThaiEncodingX11 thai_encoding;
    SDL_ToolkitThaiFontX11 thai_font;
    
    /* Control colors */
    ध्रुव SDL_MessageBoxColor *color_hints;
    XColor xcolor[SDL_MESSAGEBOX_COLOR_मोजणी];
    XColor xcolor_bevel_l1;
    XColor xcolor_bevel_l2;
    XColor xcolor_bevel_d;
    XColor xcolor_pressed;
    XColor xcolor_disabled_text;

    /* Control list */
    bool has_focus;
    संरचना SDL_ToolkitControlX11 *focused_control;
    संरचना SDL_ToolkitControlX11 *fiddled_control;
    संरचना SDL_ToolkitControlX11 **controls;
    size_t controls_sz;
    संरचना SDL_ToolkitControlX11 **dyn_controls;
    size_t dyn_controls_sz;

    /* User callbacks */
    शून्य *cb_data;
    शून्य (*cb_on_scale_change)(संरचना SDL_ToolkitWindowX11 *, शून्य *);

    /* Popup windows */
    SDL_List_गाठ *popup_windows;

    /* Event loop */
    XEvent *e;
    संरचना SDL_ToolkitControlX11 *previous_control;
    संरचना SDL_ToolkitControlX11 *किल्ली_control_esc;
    संरचना SDL_ToolkitControlX11 *किल्ली_control_enter;
    किल्ली_Sym last_किल्ली_pressed;
    पूर्णाङ्क ev_i;
    भिन्न ev_scale;
    भिन्न ev_iscale;
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

प्रकारनिर्देश गणना SDL_ToolkitControlStateX11
{
    SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL,
    SDL_TOOLKIT_CONTROL_STATE_X11_HOVER,
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED, /* Key/Button Up */
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD, /* Key/Button Down */
    SDL_TOOLKIT_CONTROL_STATE_X11_DISABLED
} SDL_ToolkitControlStateX11;

प्रकारनिर्देश संरचना SDL_ToolkitControlX11
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
    शून्य *data;

    /* Virtual functions */
    शून्य (*func_draw)(संरचना SDL_ToolkitControlX11 *);
    शून्य (*func_calc_size)(संरचना SDL_ToolkitControlX11 *);
    शून्य (*func_on_scale_change)(संरचना SDL_ToolkitControlX11 *);
    शून्य (*func_on_state_change)(संरचना SDL_ToolkitControlX11 *);
    शून्य (*func_free)(संरचना SDL_ToolkitControlX11 *);
} SDL_ToolkitControlX11;

प्रकारनिर्देश संरचना SDL_ToolkitMenuItemX11
{
    ध्रुव वर्ण *utf8;
    bool checkbox;
    bool checked;
    bool disabled;
    शून्य *cb_data;
    शून्य (*cb)(संरचना SDL_ToolkitMenuItemX11 *, शून्य *);
    SDL_List_गाठ *sub_menu;

    /* Internal use */
    SDL_Rect utf8_rect;
    SDL_Rect hover_rect;
    SDL_Rect check_rect;
    SDL_ToolkitControlStateX11 state;
    पूर्णाङ्क arrow_x;
    पूर्णाङ्क arrow_y;
    bool reverse_arrows;
} SDL_ToolkitMenuItemX11;

/* WINDOW FUNCTIONS */
बाह्य SDL_ToolkitWindowX11 *X11Toolkit_CreateWindowStruct(SDL_Window *parent, SDL_ToolkitWindowX11 *tkparent, SDL_ToolkitWindowModeX11 mode, ध्रुव SDL_MessageBoxColor *colorhints, bool create_new_display);
बाह्य bool X11Toolkit_CreateWindowRes(SDL_ToolkitWindowX11 *data, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क cx, पूर्णाङ्क cy, वर्ण *title);
बाह्य शून्य X11Toolkit_DoWindowEventLoop(SDL_ToolkitWindowX11 *data);
बाह्य शून्य X11Toolkit_ResizeWindow(SDL_ToolkitWindowX11 *data, पूर्णाङ्क w, पूर्णाङ्क h);
बाह्य शून्य X11Toolkit_DestroyWindow(SDL_ToolkitWindowX11 *data);
बाह्य शून्य X11Toolkit_SignalWindowClose(SDL_ToolkitWindowX11 *data);

/* GENERIC CONTROL FUNCTIONS */
बाह्य bool X11Toolkit_NotifyControlOfSizeChange(SDL_ToolkitControlX11 *control);

/* ICON CONTROL FUNCTIONS */
बाह्य SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_ToolkitWindowX11 *window, SDL_MessageBoxFlags flags);

/* LABEL CONTROL FUNCTIONS */
बाह्य SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_ToolkitWindowX11 *window, वर्ण *utf8);
बाह्य पूर्णाङ्क X11_Toolkit_Get_Label_Control_First_ओळ_Height(SDL_ToolkitControlX11 *control);

/* BUTTON CONTROL FUNCTIONS */
बाह्य SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_ToolkitWindowX11 *window, ध्रुव SDL_MessageBoxButtonData *data);
बाह्य शून्य X11Toolkit_RegisterCallbackForButtonControl(SDL_ToolkitControlX11 *control, शून्य *data, शून्य (*cb)(संरचना SDL_ToolkitControlX11 *, शून्य *));
बाह्य ध्रुव SDL_MessageBoxButtonData *X11Toolkit_GetButtonControlData(SDL_ToolkitControlX11 *control);

#endif // SDL_VIDEO_DRIVER_X11

#endif // SDL_x11toolkit_h_
