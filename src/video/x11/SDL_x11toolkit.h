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

#अगर_अघोषित SDL_x11toolkit_h_
#घोषणा SDL_x11toolkit_h_

#समावेश "../../SDL_list.h"
#समावेश "SDL_x11video.h"
#समावेश "SDL_x11dyn.h"
#समावेश "SDL_x11settings.h"
#समावेश "SDL_x11toolkit.h"
#समावेश "xsettings-client.h"
#अगर_घोषित HAVE_FRIBIDI_H
#समावेश "../../core/unix/SDL_fribidi.h"
#पूर्ण_अगर
#अगर_घोषित HAVE_LIBTHAI_H
#समावेश "../../core/unix/SDL_libthai.h"
#पूर्ण_अगर

#अगर_घोषित SDL_VIDEO_DRIVER_X11

/* Various predefined paddings */
#घोषणा SDL_TOOLKIT_X11_ELEMENT_PADDING 4
#घोषणा SDL_TOOLKIT_X11_ELEMENT_PADDING_2 12
#घोषणा SDL_TOOLKIT_X11_ELEMENT_PADDING_3 8
#घोषणा SDL_TOOLKIT_X11_ELEMENT_PADDING_4 16
#घोषणा SDL_TOOLKIT_X11_ELEMENT_PADDING_5 3

प्रकार क्रमागत SDL_ToolkitChildModeX11
{
    SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG,
    SDL_TOOLKIT_WINDOW_MODE_X11_CHILD, /* For embedding into a normal SDL_Window */
    SDL_TOOLKIT_WINDOW_MODE_X11_MENU,
    SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP
} SDL_ToolkitWindowModeX11;

प्रकार क्रमागत SDL_ToolkitThaiEncodingX11
{
    SDL_TOOLKIT_THAI_ENCODING_X11_NONE,
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS, /* -0 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN, /* -2 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC, /* -1 */
    SDL_TOOLKIT_THAI_ENCODING_X11_8859,
    SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE
} SDL_ToolkitThaiEncodingX11;

प्रकार क्रमागत SDL_ToolkitThaiFontX11
{
    SDL_TOOLKIT_THAI_FONT_X11_OFFSET,
    SDL_TOOLKIT_THAI_FONT_X11_CELL
} SDL_ToolkitThaiFontX11;

प्रकार काष्ठा SDL_ToolkitWindowX11
{
    /* Locale */
    अक्षर *origlocale;

    /* Mode */
    SDL_ToolkitWindowModeX11 mode;

    /* Display */
    Display *display;
    पूर्णांक screen;
    bool display_close;

    /* Parent */
    SDL_VideoDevice *parent_device;
    SDL_Window *parent;
    काष्ठा SDL_ToolkitWindowX11 *tk_parent;

    /* Window */
    Window window;
    Drawable drawable;
#अगर_अघोषित NO_SHARED_MEMORY
    XImage *image;
    XShmSegmentInfo shm_info;
    पूर्णांक shm_bytes_per_पंक्ति;
#पूर्ण_अगर

    /* Visuals and drawing */
    Visual *visual;
    XVisualInfo vi;
    Colormap cmap;
    GC ctx;
    पूर्णांक depth;
    bool pixmap;

    /* X11 extensions */
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XDBE
    Xdbe_Back_बफर buf;
    bool xdbe; // Whether Xdbe is present or not
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
    bool xrandr; // Whether Xrandr is present or not
#पूर्ण_अगर
#अगर_अघोषित NO_SHARED_MEMORY
    bool shm;
    Bool shm_pixmap;
#पूर्ण_अगर
    bool utf8;
    /* Atoms */
    Atom wm_protocols;
    Atom wm_delete_message;

    /* Window and pixmap sizes */
    पूर्णांक window_width;  // Window width.
    पूर्णांक window_height; // Window height.
    पूर्णांक pixmap_width;
    पूर्णांक pixmap_height;
    पूर्णांक window_x;
    पूर्णांक window_y;

    /* XSettings and scaling */
    XSettingsClient *xsettings;
    bool xsettings_first_time;
    पूर्णांक iscale;
    भग्न scale;

    /* Font */
    XFontSet font_set;        // for UTF-8 systems
    XFontStruct *font_struct; // Latin1 (ASCII) fallback.
    SDL_ToolkitThaiEncodingX11 thai_encoding;
    SDL_ToolkitThaiFontX11 thai_font;
    
    /* Control colors */
    स्थिर SDL_MessageBoxColor *color_hints;
    XColor xcolor[SDL_MESSAGEBOX_COLOR_गिनती];
    XColor xcolor_bevel_l1;
    XColor xcolor_bevel_l2;
    XColor xcolor_bevel_d;
    XColor xcolor_pressed;
    XColor xcolor_disabled_text;

    /* Control list */
    bool has_focus;
    काष्ठा SDL_ToolkitControlX11 *focused_control;
    काष्ठा SDL_ToolkitControlX11 *fiddled_control;
    काष्ठा SDL_ToolkitControlX11 **controls;
    माप_प्रकार controls_sz;
    काष्ठा SDL_ToolkitControlX11 **dyn_controls;
    माप_प्रकार dyn_controls_sz;

    /* User callbacks */
    व्योम *cb_तथ्य;
    व्योम (*cb_on_scale_change)(काष्ठा SDL_ToolkitWindowX11 *, व्योम *);

    /* Popup windows */
    SDL_List_गाँठ *popup_windows;

    /* Event loop */
    XEvent *e;
    काष्ठा SDL_ToolkitControlX11 *previous_control;
    काष्ठा SDL_ToolkitControlX11 *कुंजी_control_esc;
    काष्ठा SDL_ToolkitControlX11 *कुंजी_control_enter;
    कुंजी_Sym last_कुंजी_pressed;
    पूर्णांक ev_i;
    भग्न ev_scale;
    भग्न ev_iscale;
    bool draw;
    bool बंद;
    दीर्घ event_mask;

#अगर_घोषित HAVE_FRIBIDI_H
    /* BIDI engine */
    SDL_FriBidi *fribidi;
    bool do_shaping;
#पूर्ण_अगर

#अगर_घोषित HAVE_LIBTHAI_H
    SDL_LibThai *th;
#पूर्ण_अगर

    bool flip_interface;
} SDL_ToolkitWindowX11;

प्रकार क्रमागत SDL_ToolkitControlStateX11
{
    SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL,
    SDL_TOOLKIT_CONTROL_STATE_X11_HOVER,
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED, /* Key/Button Up */
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD, /* Key/Button Down */
    SDL_TOOLKIT_CONTROL_STATE_X11_DISABLED
} SDL_ToolkitControlStateX11;

प्रकार काष्ठा SDL_ToolkitControlX11
{
    SDL_ToolkitWindowX11 *window;
    SDL_ToolkitControlStateX11 state;
    SDL_Rect rect;
    bool selected;
    bool dynamic;
    bool is_default_enter;
    bool is_default_esc;
    bool do_आकार;

    /* User data */
    व्योम *तथ्य;

    /* Virtual functions */
    व्योम (*func_draw)(काष्ठा SDL_ToolkitControlX11 *);
    व्योम (*func_calc_आकार)(काष्ठा SDL_ToolkitControlX11 *);
    व्योम (*func_on_scale_change)(काष्ठा SDL_ToolkitControlX11 *);
    व्योम (*func_on_state_change)(काष्ठा SDL_ToolkitControlX11 *);
    व्योम (*func_free)(काष्ठा SDL_ToolkitControlX11 *);
} SDL_ToolkitControlX11;

प्रकार काष्ठा SDL_ToolkitMenuItemX11
{
    स्थिर अक्षर *utf8;
    bool checkbox;
    bool checked;
    bool disabled;
    व्योम *cb_तथ्य;
    व्योम (*cb)(काष्ठा SDL_ToolkitMenuItemX11 *, व्योम *);
    SDL_List_गाँठ *sub_menu;

    /* Internal use */
    SDL_Rect utf8_rect;
    SDL_Rect hover_rect;
    SDL_Rect check_rect;
    SDL_ToolkitControlStateX11 state;
    पूर्णांक arrow_x;
    पूर्णांक arrow_y;
    bool reverse_arrows;
} SDL_ToolkitMenuItemX11;

/* WINDOW FUNCTIONS */
बाह्य SDL_ToolkitWindowX11 *X11Toolkit_CreateWindowStruct(SDL_Window *parent, SDL_ToolkitWindowX11 *tkparent, SDL_ToolkitWindowModeX11 mode, स्थिर SDL_MessageBoxColor *colorhints, bool create_new_display);
बाह्य bool X11Toolkit_CreateWindowRes(SDL_ToolkitWindowX11 *तथ्य, पूर्णांक w, पूर्णांक h, पूर्णांक cx, पूर्णांक cy, अक्षर *title);
बाह्य व्योम X11Toolkit_DoWindowEventLoop(SDL_ToolkitWindowX11 *तथ्य);
बाह्य व्योम X11Toolkit_ResizeWindow(SDL_ToolkitWindowX11 *तथ्य, पूर्णांक w, पूर्णांक h);
बाह्य व्योम X11Toolkit_DestroyWindow(SDL_ToolkitWindowX11 *तथ्य);
बाह्य व्योम X11Toolkit_SignalWindowClose(SDL_ToolkitWindowX11 *तथ्य);

/* GENERIC CONTROL FUNCTIONS */
बाह्य bool X11_Toolkit_Notify_Control_Of_आकार_Change(SDL_ToolkitControlX11 *control);

/* ICON CONTROL FUNCTIONS */
बाह्य SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_ToolkitWindowX11 *window, SDL_MessageBoxFlags flags);

/* LABEL CONTROL FUNCTIONS */
बाह्य SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_ToolkitWindowX11 *window, अक्षर *utf8);
बाह्य पूर्णांक X11_Toolkit_Get_Label_Control_First_पंक्ति_Height(SDL_ToolkitControlX11 *control);

/* BUTTON CONTROL FUNCTIONS */
बाह्य SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_ToolkitWindowX11 *window, स्थिर SDL_Message_Box_Button_तथ्य *तथ्य);
बाह्य व्योम X11Toolkit_RegisterCallbackForButtonControl(SDL_ToolkitControlX11 *control, व्योम *तथ्य, व्योम (*cb)(काष्ठा SDL_ToolkitControlX11 *, व्योम *));
बाह्य स्थिर SDL_Message_Box_Button_तथ्य *X11_Toolkit_Get_Button_Control_तथ्य(SDL_ToolkitControlX11 *control);

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11

#पूर्ण_अगर // SDL_x11toolkit_h_
