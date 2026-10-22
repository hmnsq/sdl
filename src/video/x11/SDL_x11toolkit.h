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

#اگر_تعریف_نشده SDL_x11toolkit_h_
#تعریف_کن SDL_x11toolkit_h_

#ضمن "../../SDL_list.h"
#ضمن "SDL_x11video.h"
#ضمن "SDL_x11dyn.h"
#ضمن "SDL_x11settings.h"
#ضمن "SDL_x11toolkit.h"
#ضمن "xsettings-client.h"
#اگر_تعریف_شده HAVE_FRIBIDI_H
#ضمن "../../core/unix/SDL_fribidi.h"
#پایان_اگر
#اگر_تعریف_شده HAVE_LIBTHAI_H
#ضمن "../../core/unix/SDL_libthai.h"
#پایان_اگر

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

/* Various predefined paddings */
#تعریف_کن SDL_TOOLKIT_X11_ELEMENT_PADDING 4
#تعریف_کن SDL_TOOLKIT_X11_ELEMENT_PADDING_2 12
#تعریف_کن SDL_TOOLKIT_X11_ELEMENT_PADDING_3 8
#تعریف_کن SDL_TOOLKIT_X11_ELEMENT_PADDING_4 16
#تعریف_کن SDL_TOOLKIT_X11_ELEMENT_PADDING_5 3

تعريفنوع تعداد SDL_Toolkit_فرزند_نما_X11
{
    SDL_TOOLKIT_پنجره_نما_X11_DIALOG,
    SDL_TOOLKIT_پنجره_نما_X11_فرزند, /* For embedding into a normal SDL_Window */
    SDL_TOOLKIT_پنجره_نما_X11_MENU,
    SDL_TOOLKIT_پنجره_نما_X11_TOOLTIP
} SDL_Toolkit_پنجره_نما_X11;

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
    SDL_TOOLKIT_THAI_FONT_X11_جابه_جایی,
    SDL_TOOLKIT_THAI_FONT_X11_CELL
} SDL_ToolkitThaiFontX11;

تعريفنوع بنية SDL_Toolkit_پنجره_X11
{
    /* Locale */
    حرف *origlocale;

    /*نما*/
    SDL_Toolkit_پنجره_نما_X11 نما;

    /* Display */
    Display *display;
    صحيح screen;
    bool display_close;

    /*والد*/
    SDL_VideoDevice *والد_device;
    SDL_پنجره *والد;
    بنية SDL_Toolkit_پنجره_X11 *tk_والد;

    /*پنجره*/
    پنجره_2 پنجره;
    Drawable drawable;
#اگر_تعریف_نشده NO_SHARED_حافظه
    XImage *image;
    XShmSegmentInfo shm_info;
    صحيح shm_بایتها_در_هر_سطر;
#پایان_اگر

    /* Visuals and drawing */
    Visual *visual;
    XVisualInfo vi;
    Colormap cmap;
    GC ctx;
    صحيح عمق_2;
    bool pixmap;

    /* X11 extensions */
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XDBE
    Xdbe_پشت_میانگیر buf;
    bool xdbe; // Whether Xdbe is present or not
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
    bool xrandr; // Whether Xrandr is present or not
#پایان_اگر
#اگر_تعریف_نشده NO_SHARED_حافظه
    bool shm;
    Bool shm_pixmap;
#پایان_اگر
    bool utf8;
    /* Atoms */
    Atom wm_protocols;
    Atom wm_delete_پیام;

    /* Window and pixmap sizes */
    صحيح پنجره_عرض;  // Window width.
    صحيح پنجره_ارتفاع; // Window height.
    صحيح pixmap_عرض;
    صحيح pixmap_ارتفاع;
    صحيح پنجره_x;
    صحيح پنجره_y;

    /* XSettings and scaling */
    XSettingsClient *xsettings;
    bool xsettings_اولی_زمان;
    صحيح iscale;
    عائم scale;

    /* Font */
    XFont_مجموعه font_مجموعه;        // for UTF-8 systems
    XFontStruct *font_struct; // Latin1 (ASCII) fallback.
    SDL_ToolkitThaiEncodingX11 thai_encoding;
    SDL_ToolkitThaiFontX11 thai_font;
    
    /* Control colors */
    ثابت SDL_پیام_Box_Color *color_hints;
    XColor xcolor[SDL_MESSAGEBOX_COLOR_شمار];
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
    فراغ *cb_داده;
    فراغ (*cb_on_scale_change)(بنية SDL_Toolkit_پنجره_X11 *, فراغ *);

    /* Popup windows */
    SDL_List_گره *popup_windows;

    /* Event loop */
    XEvent *e;
    بنية SDL_ToolkitControlX11 *قبلی_control;
    بنية SDL_ToolkitControlX11 *کلید_control_esc;
    بنية SDL_ToolkitControlX11 *کلید_control_enter;
    کلید_Sym آخرین_کلید_pressed;
    صحيح ev_i;
    عائم ev_scale;
    عائم ev_iscale;
    bool draw;
    bool close;
    دراز event_ماسک;

#اگر_تعریف_شده HAVE_FRIBIDI_H
    /* BIDI engine */
    SDL_FriBidi *fribidi;
    bool do_shaping;
#پایان_اگر

#اگر_تعریف_شده HAVE_LIBTHAI_H
    SDL_LibThai *th;
#پایان_اگر

    bool flip_interface;
} SDL_Toolkit_پنجره_X11;

تعريفنوع تعداد SDL_ToolkitControlStateX11
{
    SDL_TOOLKIT_CONTROL_STATE_X11_نرمال,
    SDL_TOOLKIT_CONTROL_STATE_X11_HOVER,
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED, /* Key/Button Up */
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD, /* Key/Button Down */
    SDL_TOOLKIT_CONTROL_STATE_X11_DISABLED
} SDL_ToolkitControlStateX11;

تعريفنوع بنية SDL_ToolkitControlX11
{
    SDL_Toolkit_پنجره_X11 *پنجره;
    SDL_ToolkitControlStateX11 state;
    SDL_Rect rect;
    bool selected;
    bool dynamic;
    bool is_default_enter;
    bool is_default_esc;
    bool do_اندازه;

    /* User data */
    فراغ *داده;

    /* Virtual functions */
    فراغ (*func_draw)(بنية SDL_ToolkitControlX11 *);
    فراغ (*func_calc_اندازه)(بنية SDL_ToolkitControlX11 *);
    فراغ (*func_on_scale_change)(بنية SDL_ToolkitControlX11 *);
    فراغ (*func_on_state_change)(بنية SDL_ToolkitControlX11 *);
    فراغ (*func_free)(بنية SDL_ToolkitControlX11 *);
} SDL_ToolkitControlX11;

تعريفنوع بنية SDL_Toolkit_Menu_قلم_X11
{
    ثابت حرف *utf8;
    bool checkbox;
    bool checked;
    bool disabled;
    فراغ *cb_داده;
    فراغ (*cb)(بنية SDL_Toolkit_Menu_قلم_X11 *, فراغ *);
    SDL_List_گره *sub_menu;

    /* Internal use */
    SDL_Rect utf8_rect;
    SDL_Rect hover_rect;
    SDL_Rect check_rect;
    SDL_ToolkitControlStateX11 state;
    صحيح arrow_x;
    صحيح arrow_y;
    bool معکوس_arrows;
} SDL_Toolkit_Menu_قلم_X11;

/* WINDOW FUNCTIONS */
خارجي SDL_Toolkit_پنجره_X11 *X11_Toolkit_Create_پنجره_Struct(SDL_پنجره *والد, SDL_Toolkit_پنجره_X11 *tkparent, SDL_Toolkit_پنجره_نما_X11 نما, ثابت SDL_پیام_Box_Color *colorhints, bool create_new_display);
خارجي bool X11_Toolkit_Create_پنجره_Res(SDL_Toolkit_پنجره_X11 *داده, صحيح w, صحيح h, صحيح cx, صحيح cy, حرف *title);
خارجي فراغ X11_Toolkit_Do_پنجره_Event_Loop(SDL_Toolkit_پنجره_X11 *داده);
خارجي فراغ X11_Toolkit_Resize_پنجره(SDL_Toolkit_پنجره_X11 *داده, صحيح w, صحيح h);
خارجي فراغ X11_Toolkit_Destroy_پنجره(SDL_Toolkit_پنجره_X11 *داده);
خارجي فراغ X11_Toolkit_Signal_پنجره_Close(SDL_Toolkit_پنجره_X11 *داده);

/* GENERIC CONTROL FUNCTIONS */
خارجي bool X11_Toolkit_Notify_Control_از_اندازه_Change(SDL_ToolkitControlX11 *control);

/* ICON CONTROL FUNCTIONS */
خارجي SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_پنجره_X11 *پنجره, SDL_پیام_Box_Flags flags);

/* LABEL CONTROL FUNCTIONS */
خارجي SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_پنجره_X11 *پنجره, حرف *utf8);
خارجي صحيح X11_Toolkit_Get_Label_Control_اولی_سطر_ارتفاع(SDL_ToolkitControlX11 *control);

/* BUTTON CONTROL FUNCTIONS */
خارجي SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_پنجره_X11 *پنجره, ثابت SDL_پیام_Box_Button_داده *داده);
خارجي فراغ X11_Toolkit_ثبات_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, فراغ *داده, فراغ (*cb)(بنية SDL_ToolkitControlX11 *, فراغ *));
خارجي ثابت SDL_پیام_Box_Button_داده *X11_Toolkit_Get_Button_Control_داده(SDL_ToolkitControlX11 *control);

#پایان_اگر // SDL_VIDEO_DRIVER_X11

#پایان_اگر // SDL_x11toolkit_h_
