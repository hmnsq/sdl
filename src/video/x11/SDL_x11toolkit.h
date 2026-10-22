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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_x11toolkit_h_
#تعریف_کرو SDL_x11toolkit_h_

#شامل "../../SDL_list.h"
#شامل "SDL_x11video.h"
#شامل "SDL_x11dyn.h"
#شامل "SDL_x11settings.h"
#شامل "SDL_x11toolkit.h"
#شامل "xsettings-client.h"
#اگر_تعریف_شدہ HAVE_FRIBIDI_H
#شامل "../../core/unix/SDL_fribidi.h"
#اگر_ختم
#اگر_تعریف_شدہ HAVE_LIBTHAI_H
#شامل "../../core/unix/SDL_libthai.h"
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

/* Various predefined paddings */
#تعریف_کرو SDL_TOOLKIT_X11_ELEMENT_PADDING 4
#تعریف_کرو SDL_TOOLKIT_X11_ELEMENT_PADDING_2 12
#تعریف_کرو SDL_TOOLKIT_X11_ELEMENT_PADDING_3 8
#تعریف_کرو SDL_TOOLKIT_X11_ELEMENT_PADDING_4 16
#تعریف_کرو SDL_TOOLKIT_X11_ELEMENT_PADDING_5 3

قسمتعریف شمار SDL_Toolkit_بچہ_منوال_X11
{
    SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG,
    SDL_TOOLKIT_کھڑکی_منوال_X11_بچہ, /* For embedding into a normal SDL_Window */
    SDL_TOOLKIT_کھڑکی_منوال_X11_MENU,
    SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP
} SDL_Toolkit_کھڑکی_منوال_X11;

قسمتعریف شمار SDL_ToolkitThaiEncodingX11
{
    SDL_TOOLKIT_THAI_ENCODING_X11_NONE,
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS, /* -0 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN, /* -2 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC, /* -1 */
    SDL_TOOLKIT_THAI_ENCODING_X11_8859,
    SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE
} SDL_ToolkitThaiEncodingX11;

قسمتعریف شمار SDL_ToolkitThaiFontX11
{
    SDL_TOOLKIT_THAI_FONT_X11_انحراف,
    SDL_TOOLKIT_THAI_FONT_X11_CELL
} SDL_ToolkitThaiFontX11;

قسمتعریف ساخت SDL_Toolkit_کھڑکی_X11
{
    /* Locale */
    حرف *origlocale;

    /*منوال*/
    SDL_Toolkit_کھڑکی_منوال_X11 منوال;

    /* Display */
    Display *display;
    صحیح screen;
    bool display_close;

    /*والد*/
    SDL_VideoDevice *والد_device;
    SDL_کھڑکی *والد;
    ساخت SDL_Toolkit_کھڑکی_X11 *tk_والد;

    /*کھڑکی*/
    کھڑکی_2 کھڑکی;
    Drawable drawable;
#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
    XImage *image;
    XShmSegmentInfo shm_info;
    صحیح shm_بائٹیں_فی_سطر;
#اگر_ختم

    /* Visuals and drawing */
    Visual *visual;
    XVisualInfo vi;
    Colormap cmap;
    GC ctx;
    صحیح گہرائی_2;
    bool pixmap;

    /* X11 extensions */
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
    Xdbe_عقب_بفر buf;
    bool xdbe; // Whether Xdbe is present or not
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
    bool xrandr; // Whether Xrandr is present or not
#اگر_ختم
#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
    bool shm;
    Bool shm_pixmap;
#اگر_ختم
    bool utf8;
    /* Atoms */
    Atom wm_protocols;
    Atom wm_delete_پیغام;

    /* Window and pixmap sizes */
    صحیح کھڑکی_چوڑائی;  // Window width.
    صحیح کھڑکی_اونچائی; // Window height.
    صحیح pixmap_چوڑائی;
    صحیح pixmap_اونچائی;
    صحیح کھڑکی_x;
    صحیح کھڑکی_y;

    /* XSettings and scaling */
    XSettingsClient *xsettings;
    bool xsettings_پہلا_وقت;
    صحیح iscale;
    اعشاری scale;

    /* Font */
    XFont_سیٹ font_سیٹ;        // for UTF-8 systems
    XFontStruct *font_struct; // Latin1 (ASCII) fallback.
    SDL_ToolkitThaiEncodingX11 thai_encoding;
    SDL_ToolkitThaiFontX11 thai_font;
    
    /* Control colors */
    ثابت SDL_پیغام_Box_Color *color_hints;
    XColor xcolor[SDL_MESSAGEBOX_COLOR_گنتی];
    XColor xcolor_bevel_l1;
    XColor xcolor_bevel_l2;
    XColor xcolor_bevel_d;
    XColor xcolor_pressed;
    XColor xcolor_disabled_متن;

    /* Control list */
    bool has_focus;
    ساخت SDL_ToolkitControlX11 *focused_control;
    ساخت SDL_ToolkitControlX11 *fiddled_control;
    ساخت SDL_ToolkitControlX11 **controls;
    size_t controls_sz;
    ساخت SDL_ToolkitControlX11 **dyn_controls;
    size_t dyn_controls_sz;

    /* User callbacks */
    خالی *cb_ڈیٹا;
    خالی (*cb_on_scale_change)(ساخت SDL_Toolkit_کھڑکی_X11 *, خالی *);

    /* Popup windows */
    SDL_List_گرہ *popup_windows;

    /* Event loop */
    XEvent *e;
    ساخت SDL_ToolkitControlX11 *پچھلا_control;
    ساخت SDL_ToolkitControlX11 *کلید_control_esc;
    ساخت SDL_ToolkitControlX11 *کلید_control_enter;
    کلید_Sym آخری_کلید_pressed;
    صحیح ev_i;
    اعشاری ev_scale;
    اعشاری ev_iscale;
    bool draw;
    bool close;
    طویل event_نقاب;

#اگر_تعریف_شدہ HAVE_FRIBIDI_H
    /* BIDI engine */
    SDL_FriBidi *fribidi;
    bool do_shaping;
#اگر_ختم

#اگر_تعریف_شدہ HAVE_LIBTHAI_H
    SDL_LibThai *th;
#اگر_ختم

    bool flip_interface;
} SDL_Toolkit_کھڑکی_X11;

قسمتعریف شمار SDL_ToolkitControlStateX11
{
    SDL_TOOLKIT_CONTROL_STATE_X11_معمول,
    SDL_TOOLKIT_CONTROL_STATE_X11_HOVER,
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED, /* Key/Button Up */
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD, /* Key/Button Down */
    SDL_TOOLKIT_CONTROL_STATE_X11_DISABLED
} SDL_ToolkitControlStateX11;

قسمتعریف ساخت SDL_ToolkitControlX11
{
    SDL_Toolkit_کھڑکی_X11 *کھڑکی;
    SDL_ToolkitControlStateX11 state;
    SDL_Rect rect;
    bool selected;
    bool dynamic;
    bool is_default_enter;
    bool is_default_esc;
    bool do_سائز;

    /* User data */
    خالی *ڈیٹا;

    /* Virtual functions */
    خالی (*func_draw)(ساخت SDL_ToolkitControlX11 *);
    خالی (*func_calc_سائز)(ساخت SDL_ToolkitControlX11 *);
    خالی (*func_on_scale_change)(ساخت SDL_ToolkitControlX11 *);
    خالی (*func_on_state_change)(ساخت SDL_ToolkitControlX11 *);
    خالی (*func_free)(ساخت SDL_ToolkitControlX11 *);
} SDL_ToolkitControlX11;

قسمتعریف ساخت SDL_Toolkit_Menu_شے_X11
{
    ثابت حرف *utf8;
    bool checkbox;
    bool checked;
    bool disabled;
    خالی *cb_ڈیٹا;
    خالی (*cb)(ساخت SDL_Toolkit_Menu_شے_X11 *, خالی *);
    SDL_List_گرہ *sub_menu;

    /* Internal use */
    SDL_Rect utf8_rect;
    SDL_Rect hover_rect;
    SDL_Rect check_rect;
    SDL_ToolkitControlStateX11 state;
    صحیح arrow_x;
    صحیح arrow_y;
    bool الٹ_arrows;
} SDL_Toolkit_Menu_شے_X11;

/* WINDOW FUNCTIONS */
خارجی SDL_Toolkit_کھڑکی_X11 *X11_Toolkit_Create_کھڑکی_Struct(SDL_کھڑکی *والد, SDL_Toolkit_کھڑکی_X11 *tkparent, SDL_Toolkit_کھڑکی_منوال_X11 منوال, ثابت SDL_پیغام_Box_Color *colorhints, bool create_new_display);
خارجی bool X11_Toolkit_Create_کھڑکی_Res(SDL_Toolkit_کھڑکی_X11 *ڈیٹا, صحیح w, صحیح h, صحیح cx, صحیح cy, حرف *title);
خارجی خالی X11_Toolkit_Do_کھڑکی_Event_Loop(SDL_Toolkit_کھڑکی_X11 *ڈیٹا);
خارجی خالی X11_Toolkit_Resize_کھڑکی(SDL_Toolkit_کھڑکی_X11 *ڈیٹا, صحیح w, صحیح h);
خارجی خالی X11_Toolkit_Destroy_کھڑکی(SDL_Toolkit_کھڑکی_X11 *ڈیٹا);
خارجی خالی X11_Toolkit_Signal_کھڑکی_Close(SDL_Toolkit_کھڑکی_X11 *ڈیٹا);

/* GENERIC CONTROL FUNCTIONS */
خارجی bool X11_Toolkit_Notify_Control_کا_سائز_Change(SDL_ToolkitControlX11 *control);

/* ICON CONTROL FUNCTIONS */
خارجی SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, SDL_پیغام_Box_Flags flags);

/* LABEL CONTROL FUNCTIONS */
خارجی SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, حرف *utf8);
خارجی صحیح X11_Toolkit_Get_Label_Control_پہلا_سطر_اونچائی(SDL_ToolkitControlX11 *control);

/* BUTTON CONTROL FUNCTIONS */
خارجی SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, ثابت SDL_پیغام_Box_Button_ڈیٹا *ڈیٹا);
خارجی خالی X11_Toolkit_رجسٹر_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, خالی *ڈیٹا, خالی (*cb)(ساخت SDL_ToolkitControlX11 *, خالی *));
خارجی ثابت SDL_پیغام_Box_Button_ڈیٹا *X11_Toolkit_Get_Button_Control_ڈیٹا(SDL_ToolkitControlX11 *control);

#اگر_ختم // SDL_VIDEO_DRIVER_X11

#اگر_ختم // SDL_x11toolkit_h_
