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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_x11toolkit_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_x11toolkit_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_list.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11dyn.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11settings.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11toolkit.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xsettings-client.h"
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/unix/SDL_fribidi.h"
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBTHAI_H
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/unix/SDL_libthai.h"
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

/* Various predefined paddings */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_TOOLKIT_X11_ELEMENT_PADDING 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_TOOLKIT_X11_ELEMENT_PADDING_2 12
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_TOOLKIT_X11_ELEMENT_PADDING_3 8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_TOOLKIT_X11_ELEMENT_PADDING_4 16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_TOOLKIT_X11_ELEMENT_PADDING_5 3

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ SDL_Toolkit_ਬੱਚਾ_ਬਹੁਲਕ_X11
{
    SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_DIALOG,
    SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_ਬੱਚਾ, /* For embedding into a normal SDL_Window */
    SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_MENU,
    SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_TOOLTIP
} SDL_Toolkit_ਖਿੜਕੀ_ਬਹੁਲਕ_X11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ SDL_ToolkitThaiEncodingX11
{
    SDL_TOOLKIT_THAI_ENCODING_X11_NONE,
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS, /* -0 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN, /* -2 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC, /* -1 */
    SDL_TOOLKIT_THAI_ENCODING_X11_8859,
    SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE
} SDL_ToolkitThaiEncodingX11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ SDL_ToolkitThaiFontX11
{
    SDL_TOOLKIT_THAI_FONT_X11_ਵਿੱਥ,
    SDL_TOOLKIT_THAI_FONT_X11_CELL
} SDL_ToolkitThaiFontX11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_Toolkit_ਖਿੜਕੀ_X11
{
    /* Locale */
    ਅੱਖਰ *origlocale;

    /*ਬਹੁਲਕ*/
    SDL_Toolkit_ਖਿੜਕੀ_ਬਹੁਲਕ_X11 ਬਹੁਲਕ;

    /* Display */
    Display *display;
    ਪੂਰਨ screen;
    bool display_close;

    /*ਮਾਪਾ*/
    SDL_VideoDevice *ਮਾਪਾ_device;
    SDL_ਖਿੜਕੀ *ਮਾਪਾ;
    ਬਣਤਰ SDL_Toolkit_ਖਿੜਕੀ_X11 *tk_ਮਾਪਾ;

    /*ਖਿੜਕੀ*/
    ਖਿੜਕੀ_2 ਖਿੜਕੀ;
    Drawable drawable;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
    XImage *image;
    XShmSegmentInfo shm_info;
    ਪੂਰਨ shm_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਸਤਰ;
#ਜੇ_ਅੰਤ

    /* Visuals and drawing */
    Visual *visual;
    XVisualInfo vi;
    Colormap cmap;
    GC ctx;
    ਪੂਰਨ ਡੂੰਘਾਈ_2;
    bool pixmap;

    /* X11 extensions */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XDBE
    Xdbe_ਪਿੱਠ_ਬਫਰ buf;
    bool xdbe; // Whether Xdbe is present or not
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
    bool xrandr; // Whether Xrandr is present or not
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
    bool shm;
    Bool shm_pixmap;
#ਜੇ_ਅੰਤ
    bool utf8;
    /* Atoms */
    Atom wm_protocols;
    Atom wm_delete_ਸੁਨੇਹਾ;

    /* Window and pixmap sizes */
    ਪੂਰਨ ਖਿੜਕੀ_ਚੌੜਾਈ;  // Window width.
    ਪੂਰਨ ਖਿੜਕੀ_ਉਚਾਈ; // Window height.
    ਪੂਰਨ pixmap_ਚੌੜਾਈ;
    ਪੂਰਨ pixmap_ਉਚਾਈ;
    ਪੂਰਨ ਖਿੜਕੀ_x;
    ਪੂਰਨ ਖਿੜਕੀ_y;

    /* XSettings and scaling */
    XSettingsClient *xsettings;
    bool xsettings_ਪਹਿਲਾ_ਸਮਾਂ;
    ਪੂਰਨ iscale;
    ਦਸ਼ਮਲਵ scale;

    /* Font */
    XFont_ਸੈੱਟ font_ਸੈੱਟ;        // for UTF-8 systems
    XFontStruct *font_struct; // Latin1 (ASCII) fallback.
    SDL_ToolkitThaiEncodingX11 thai_encoding;
    SDL_ToolkitThaiFontX11 thai_font;
    
    /* Control colors */
    ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color *color_hints;
    XColor xcolor[SDL_MESSAGEBOX_COLOR_ਗਿਣਤੀ];
    XColor xcolor_bevel_l1;
    XColor xcolor_bevel_l2;
    XColor xcolor_bevel_d;
    XColor xcolor_pressed;
    XColor xcolor_disabled_ਪਾਠ;

    /* Control list */
    bool has_focus;
    ਬਣਤਰ SDL_ToolkitControlX11 *focused_control;
    ਬਣਤਰ SDL_ToolkitControlX11 *fiddled_control;
    ਬਣਤਰ SDL_ToolkitControlX11 **controls;
    size_t controls_sz;
    ਬਣਤਰ SDL_ToolkitControlX11 **dyn_controls;
    size_t dyn_controls_sz;

    /* User callbacks */
    ਖਾਲੀ *cb_ਅੰਕੜੇ;
    ਖਾਲੀ (*cb_on_scale_change)(ਬਣਤਰ SDL_Toolkit_ਖਿੜਕੀ_X11 *, ਖਾਲੀ *);

    /* Popup windows */
    SDL_List_ਗੰਢ *popup_windows;

    /* Event loop */
    XEvent *e;
    ਬਣਤਰ SDL_ToolkitControlX11 *ਪਿਛਲਾ_control;
    ਬਣਤਰ SDL_ToolkitControlX11 *ਕੁੰਜੀ_control_esc;
    ਬਣਤਰ SDL_ToolkitControlX11 *ਕੁੰਜੀ_control_enter;
    ਕੁੰਜੀ_Sym ਆਖਰੀ_ਕੁੰਜੀ_pressed;
    ਪੂਰਨ ev_i;
    ਦਸ਼ਮਲਵ ev_scale;
    ਦਸ਼ਮਲਵ ev_iscale;
    bool draw;
    bool close;
    ਲੰਮਾ event_ਨਕਾਬ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
    /* BIDI engine */
    SDL_FriBidi *fribidi;
    bool do_shaping;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBTHAI_H
    SDL_LibThai *th;
#ਜੇ_ਅੰਤ

    bool flip_interface;
} SDL_Toolkit_ਖਿੜਕੀ_X11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ SDL_ToolkitControlStateX11
{
    SDL_TOOLKIT_CONTROL_STATE_X11_ਸਾਧਾਰਨ,
    SDL_TOOLKIT_CONTROL_STATE_X11_HOVER,
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED, /* Key/Button Up */
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD, /* Key/Button Down */
    SDL_TOOLKIT_CONTROL_STATE_X11_DISABLED
} SDL_ToolkitControlStateX11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_ToolkitControlX11
{
    SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ;
    SDL_ToolkitControlStateX11 state;
    SDL_Rect rect;
    bool selected;
    bool dynamic;
    bool is_default_enter;
    bool is_default_esc;
    bool do_ਮਾਪ;

    /* User data */
    ਖਾਲੀ *ਅੰਕੜੇ;

    /* Virtual functions */
    ਖਾਲੀ (*func_draw)(ਬਣਤਰ SDL_ToolkitControlX11 *);
    ਖਾਲੀ (*func_calc_ਮਾਪ)(ਬਣਤਰ SDL_ToolkitControlX11 *);
    ਖਾਲੀ (*func_on_scale_change)(ਬਣਤਰ SDL_ToolkitControlX11 *);
    ਖਾਲੀ (*func_on_state_change)(ਬਣਤਰ SDL_ToolkitControlX11 *);
    ਖਾਲੀ (*func_free)(ਬਣਤਰ SDL_ToolkitControlX11 *);
} SDL_ToolkitControlX11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_Toolkit_Menu_ਵਸਤੂ_X11
{
    ਅਚਲ ਅੱਖਰ *utf8;
    bool checkbox;
    bool checked;
    bool disabled;
    ਖਾਲੀ *cb_ਅੰਕੜੇ;
    ਖਾਲੀ (*cb)(ਬਣਤਰ SDL_Toolkit_Menu_ਵਸਤੂ_X11 *, ਖਾਲੀ *);
    SDL_List_ਗੰਢ *sub_menu;

    /* Internal use */
    SDL_Rect utf8_rect;
    SDL_Rect hover_rect;
    SDL_Rect check_rect;
    SDL_ToolkitControlStateX11 state;
    ਪੂਰਨ arrow_x;
    ਪੂਰਨ arrow_y;
    bool ਉਲਟ_arrows;
} SDL_Toolkit_Menu_ਵਸਤੂ_X11;

/* WINDOW FUNCTIONS */
ਬਾਹਰੀ SDL_Toolkit_ਖਿੜਕੀ_X11 *X11_Toolkit_Create_ਖਿੜਕੀ_Struct(SDL_ਖਿੜਕੀ *ਮਾਪਾ, SDL_Toolkit_ਖਿੜਕੀ_X11 *tkparent, SDL_Toolkit_ਖਿੜਕੀ_ਬਹੁਲਕ_X11 ਬਹੁਲਕ, ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color *colorhints, bool create_new_display);
ਬਾਹਰੀ bool X11_Toolkit_Create_ਖਿੜਕੀ_Res(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ, ਪੂਰਨ w, ਪੂਰਨ h, ਪੂਰਨ cx, ਪੂਰਨ cy, ਅੱਖਰ *title);
ਬਾਹਰੀ ਖਾਲੀ X11_Toolkit_Do_ਖਿੜਕੀ_Event_Loop(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ);
ਬਾਹਰੀ ਖਾਲੀ X11_Toolkit_Resize_ਖਿੜਕੀ(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ, ਪੂਰਨ w, ਪੂਰਨ h);
ਬਾਹਰੀ ਖਾਲੀ X11_Toolkit_Destroy_ਖਿੜਕੀ(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ);
ਬਾਹਰੀ ਖਾਲੀ X11_Toolkit_Signal_ਖਿੜਕੀ_Close(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ);

/* GENERIC CONTROL FUNCTIONS */
ਬਾਹਰੀ bool X11_Toolkit_Notify_Control_ਦਾ_ਮਾਪ_Change(SDL_ToolkitControlX11 *control);

/* ICON CONTROL FUNCTIONS */
ਬਾਹਰੀ SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ, SDL_ਸੁਨੇਹਾ_Box_Flags flags);

/* LABEL CONTROL FUNCTIONS */
ਬਾਹਰੀ SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ, ਅੱਖਰ *utf8);
ਬਾਹਰੀ ਪੂਰਨ X11_Toolkit_Get_Label_Control_ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ(SDL_ToolkitControlX11 *control);

/* BUTTON CONTROL FUNCTIONS */
ਬਾਹਰੀ SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ, ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ *ਅੰਕੜੇ);
ਬਾਹਰੀ ਖਾਲੀ X11_Toolkit_ਰਜਿਸਟਰ_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, ਖਾਲੀ *ਅੰਕੜੇ, ਖਾਲੀ (*cb)(ਬਣਤਰ SDL_ToolkitControlX11 *, ਖਾਲੀ *));
ਬਾਹਰੀ ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ *X11_Toolkit_Get_Button_Control_ਅੰਕੜੇ(SDL_ToolkitControlX11 *control);

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11

#ਜੇ_ਅੰਤ // SDL_x11toolkit_h_
