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
#ضمن "SDL_internal.h"

#جے_بنا_تعریف SDL_x11toolkit_h_
#تعریف_کرو SDL_x11toolkit_h_

#ضمن "../../SDL_list.h"
#ضمن "SDL_x11video.h"
#ضمن "SDL_x11dyn.h"
#ضمن "SDL_x11settings.h"
#ضمن "SDL_x11toolkit.h"
#ضمن "xsettings-client.h"
#جے_تعریف_شدہ HAVE_FRIBIDI_H
#ضمن "../../core/unix/SDL_fribidi.h"
#جے_انت
#جے_تعریف_شدہ HAVE_LIBTHAI_H
#ضمن "../../core/unix/SDL_libthai.h"
#جے_انت

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

/* Various predefined paddings */
#تعریف_کرو SDL_TOOLKIT_X11_ELEMENT_PADDING 4
#تعریف_کرو SDL_TOOLKIT_X11_ELEMENT_PADDING_2 12
#تعریف_کرو SDL_TOOLKIT_X11_ELEMENT_PADDING_3 8
#تعریف_کرو SDL_TOOLKIT_X11_ELEMENT_PADDING_4 16
#تعریف_کرو SDL_TOOLKIT_X11_ELEMENT_PADDING_5 3

تعريفنوع تعداد SDL_Toolkit_بچہ_منوال_X11
{
    SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG,
    SDL_TOOLKIT_کھڑکی_منوال_X11_بچہ, /* For embedding into a normal SDL_Window */
    SDL_TOOLKIT_کھڑکی_منوال_X11_MENU,
    SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP
} SDL_Toolkit_کھڑکی_منوال_X11;

تعريفنوع تعداد SDL_ToolkitThaiEncodingX11
{
    SDL_TOOLKIT_THAI_ENCODING_X11_NONE,
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS, /* -0 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN, /* -2 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC, /* -1 */
    SDL_TOOLKIT_THAI_ENCODING_X11_8859,
    SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE
} SDL_ToolkitThaiEncodingX11;

تعريفنوع تعداد SDL_ToolkitThaiFontX11
{
    SDL_TOOLKIT_THAI_FONT_X11_وتھ,
    SDL_TOOLKIT_THAI_FONT_X11_CELL
} SDL_ToolkitThaiFontX11;

تعريفنوع بنية SDL_Toolkit_کھڑکی_X11
{
    /* Locale */
    حرف *origlocale;

    /*منوال*/
    SDL_Toolkit_کھڑکی_منوال_X11 منوال;

    /* Display */
    Display *display;
    صحيح screen;
    bool display_close;

    /*ماپا*/
    SDL_VideoDevice *ماپا_device;
    SDL_کھڑکی *ماپا;
    بنية SDL_Toolkit_کھڑکی_X11 *tk_ماپا;

    /*کھڑکی*/
    کھڑکی_2 کھڑکی;
    Drawable drawable;
#جے_بنا_تعریف NO_SHARED_حافظہ
    XImage *image;
    XShmSegmentInfo shm_info;
    صحيح shm_بائٹاں_فی_سطر;
#جے_انت

    /* Visuals and drawing */
    Visual *visual;
    XVisualInfo vi;
    Colormap cmap;
    GC ctx;
    صحيح ڈونگھائی_2;
    bool pixmap;

    /* X11 extensions */
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
    Xdbe_پٹھ_بفر buf;
    bool xdbe; // Whether Xdbe is present or not
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
    bool xrandr; // Whether Xrandr is present or not
#جے_انت
#جے_بنا_تعریف NO_SHARED_حافظہ
    bool shm;
    Bool shm_pixmap;
#جے_انت
    bool utf8;
    /* Atoms */
    Atom wm_protocols;
    Atom wm_delete_سنیہا;

    /* Window and pixmap sizes */
    صحيح کھڑکی_چوڑائی;  // Window width.
    صحيح کھڑکی_اچائی; // Window height.
    صحيح pixmap_چوڑائی;
    صحيح pixmap_اچائی;
    صحيح کھڑکی_x;
    صحيح کھڑکی_y;

    /* XSettings and scaling */
    XSettingsClient *xsettings;
    bool xsettings_پہلا_ویلا;
    صحيح iscale;
    عائم scale;

    /* Font */
    XFont_سیٹ font_سیٹ;        // for UTF-8 systems
    XFontStruct *font_struct; // Latin1 (ASCII) fallback.
    SDL_ToolkitThaiEncodingX11 thai_encoding;
    SDL_ToolkitThaiFontX11 thai_font;
    
    /* Control colors */
    ثابت SDL_سنیہا_Box_Color *color_hints;
    XColor xcolor[SDL_MESSAGEBOX_COLOR_گنتی];
    XColor xcolor_bevel_l1;
    XColor xcolor_bevel_l2;
    XColor xcolor_bevel_d;
    XColor xcolor_pressed;
    XColor xcolor_disabled_متن;

    /* Control list */
    bool has_focus;
    بنية SDL_ToolkitControlX11 *focused_control;
    بنية SDL_ToolkitControlX11 *fiddled_control;
    بنية SDL_ToolkitControlX11 **controls;
    size_t controls_sz;
    بنية SDL_ToolkitControlX11 **dyn_controls;
    size_t dyn_controls_sz;

    /* User callbacks */
    فراغ *cb_انکڑے;
    فراغ (*cb_on_scale_change)(بنية SDL_Toolkit_کھڑکی_X11 *, فراغ *);

    /* Popup windows */
    SDL_List_گرہ *popup_windows;

    /* Event loop */
    XEvent *e;
    بنية SDL_ToolkitControlX11 *پچھلا_control;
    بنية SDL_ToolkitControlX11 *کلید_control_esc;
    بنية SDL_ToolkitControlX11 *کلید_control_enter;
    کلید_Sym آخری_کلید_pressed;
    صحيح ev_i;
    عائم ev_scale;
    عائم ev_iscale;
    bool draw;
    bool close;
    لما event_نقاب;

#جے_تعریف_شدہ HAVE_FRIBIDI_H
    /* BIDI engine */
    SDL_FriBidi *fribidi;
    bool do_shaping;
#جے_انت

#جے_تعریف_شدہ HAVE_LIBTHAI_H
    SDL_LibThai *th;
#جے_انت

    bool flip_interface;
} SDL_Toolkit_کھڑکی_X11;

تعريفنوع تعداد SDL_ToolkitControlStateX11
{
    SDL_TOOLKIT_CONTROL_STATE_X11_عام,
    SDL_TOOLKIT_CONTROL_STATE_X11_HOVER,
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED, /* Key/Button Up */
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD, /* Key/Button Down */
    SDL_TOOLKIT_CONTROL_STATE_X11_DISABLED
} SDL_ToolkitControlStateX11;

تعريفنوع بنية SDL_ToolkitControlX11
{
    SDL_Toolkit_کھڑکی_X11 *کھڑکی;
    SDL_ToolkitControlStateX11 state;
    SDL_Rect rect;
    bool selected;
    bool dynamic;
    bool is_default_enter;
    bool is_default_esc;
    bool do_ناپ;

    /* User data */
    فراغ *انکڑے;

    /* Virtual functions */
    فراغ (*func_draw)(بنية SDL_ToolkitControlX11 *);
    فراغ (*func_calc_ناپ)(بنية SDL_ToolkitControlX11 *);
    فراغ (*func_on_scale_change)(بنية SDL_ToolkitControlX11 *);
    فراغ (*func_on_state_change)(بنية SDL_ToolkitControlX11 *);
    فراغ (*func_free)(بنية SDL_ToolkitControlX11 *);
} SDL_ToolkitControlX11;

تعريفنوع بنية SDL_Toolkit_Menu_شے_X11
{
    ثابت حرف *utf8;
    bool checkbox;
    bool checked;
    bool disabled;
    فراغ *cb_انکڑے;
    فراغ (*cb)(بنية SDL_Toolkit_Menu_شے_X11 *, فراغ *);
    SDL_List_گرہ *sub_menu;

    /* Internal use */
    SDL_Rect utf8_rect;
    SDL_Rect hover_rect;
    SDL_Rect check_rect;
    SDL_ToolkitControlStateX11 state;
    صحيح arrow_x;
    صحيح arrow_y;
    bool الٹ_arrows;
} SDL_Toolkit_Menu_شے_X11;

/* WINDOW FUNCTIONS */
خارجي SDL_Toolkit_کھڑکی_X11 *X11_Toolkit_Create_کھڑکی_Struct(SDL_کھڑکی *ماپا, SDL_Toolkit_کھڑکی_X11 *tkparent, SDL_Toolkit_کھڑکی_منوال_X11 منوال, ثابت SDL_سنیہا_Box_Color *colorhints, bool create_new_display);
خارجي bool X11_Toolkit_Create_کھڑکی_Res(SDL_Toolkit_کھڑکی_X11 *انکڑے, صحيح w, صحيح h, صحيح cx, صحيح cy, حرف *title);
خارجي فراغ X11_Toolkit_Do_کھڑکی_Event_Loop(SDL_Toolkit_کھڑکی_X11 *انکڑے);
خارجي فراغ X11_Toolkit_Resize_کھڑکی(SDL_Toolkit_کھڑکی_X11 *انکڑے, صحيح w, صحيح h);
خارجي فراغ X11_Toolkit_Destroy_کھڑکی(SDL_Toolkit_کھڑکی_X11 *انکڑے);
خارجي فراغ X11_Toolkit_Signal_کھڑکی_Close(SDL_Toolkit_کھڑکی_X11 *انکڑے);

/* GENERIC CONTROL FUNCTIONS */
خارجي bool X11_Toolkit_Notify_Control_دا_ناپ_Change(SDL_ToolkitControlX11 *control);

/* ICON CONTROL FUNCTIONS */
خارجي SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, SDL_سنیہا_Box_Flags flags);

/* LABEL CONTROL FUNCTIONS */
خارجي SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, حرف *utf8);
خارجي صحيح X11_Toolkit_Get_Label_Control_پہلا_سطر_اچائی(SDL_ToolkitControlX11 *control);

/* BUTTON CONTROL FUNCTIONS */
خارجي SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, ثابت SDL_سنیہا_Box_Button_انکڑے *انکڑے);
خارجي فراغ X11_Toolkit_رجسٹر_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, فراغ *انکڑے, فراغ (*cb)(بنية SDL_ToolkitControlX11 *, فراغ *));
خارجي ثابت SDL_سنیہا_Box_Button_انکڑے *X11_Toolkit_Get_Button_Control_انکڑے(SDL_ToolkitControlX11 *control);

#جے_انت // SDL_VIDEO_DRIVER_X11

#جے_انت // SDL_x11toolkit_h_
