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

#यदि_अपरिभाषितम् SDL_x11toolkit_h_
#परिभाषय SDL_x11toolkit_h_

#अन्तर्भाव "../../SDL_list.h"
#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11dyn.h"
#अन्तर्भाव "SDL_x11settings.h"
#अन्तर्भाव "SDL_x11toolkit.h"
#अन्तर्भाव "xsettings-client.h"
#यदि_परिभाषितम् HAVE_FRIBIDI_H
#अन्तर्भाव "../../core/unix/SDL_fribidi.h"
#यदि_अन्तः
#यदि_परिभाषितम् HAVE_LIBTHAI_H
#अन्तर्भाव "../../core/unix/SDL_libthai.h"
#यदि_अन्तः

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

/* Various predefined paddings */
#परिभाषय SDL_TOOLKIT_X11_ELEMENT_PADDING 4
#परिभाषय SDL_TOOLKIT_X11_ELEMENT_PADDING_2 12
#परिभाषय SDL_TOOLKIT_X11_ELEMENT_PADDING_3 8
#परिभाषय SDL_TOOLKIT_X11_ELEMENT_PADDING_4 16
#परिभाषय SDL_TOOLKIT_X11_ELEMENT_PADDING_5 3

प्रकारनिर्देश गणना SDL_Toolkit_Child_बहुलकम्_X11
{
    SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_DIALOG,
    SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_CHILD, /* For embedding into a normal SDL_Window */
    SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_MENU,
    SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_TOOLTIP
} SDL_Toolkit_गवाक्षः_बहुलकम्_X11;

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
    SDL_TOOLKIT_THAI_FONT_X11_विस्थापनम्,
    SDL_TOOLKIT_THAI_FONT_X11_CELL
} SDL_ToolkitThaiFontX11;

प्रकारनिर्देश संरचना SDL_Toolkit_गवाक्षः_X11
{
    /* Locale */
    वर्ण *origlocale;

    /*बहुलकम्*/
    SDL_Toolkit_गवाक्षः_बहुलकम्_X11 बहुलकम्;

    /* Display */
    Display *display;
    पूर्णाङ्क screen;
    bool display_close;

    /* Parent */
    SDL_VideoDevice *parent_device;
    SDL_गवाक्षः *parent;
    संरचना SDL_Toolkit_गवाक्षः_X11 *tk_parent;

    /*गवाक्षः*/
    गवाक्षः_2 गवाक्षः;
    Drawable drawable;
#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
    XImage *image;
    XShmSegmentInfo shm_info;
    पूर्णाङ्क shm_अष्टकानि_प्रत्येकम्_पङ्क्तिः;
#यदि_अन्तः

    /* Visuals and drawing */
    Visual *visual;
    XVisualInfo vi;
    Colormap cmap;
    GC ctx;
    पूर्णाङ्क गभीरता_2;
    bool pixmap;

    /* X11 extensions */
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XDBE
    Xdbe_पृष्ठभागः_बफर buf;
    bool xdbe; // Whether Xdbe is present or not
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
    bool xrandr; // Whether Xrandr is present or not
#यदि_अन्तः
#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
    bool shm;
    Bool shm_pixmap;
#यदि_अन्तः
    bool utf8;
    /* Atoms */
    Atom wm_protocols;
    Atom wm_delete_सन्देशः;

    /* Window and pixmap sizes */
    पूर्णाङ्क गवाक्षः_विस्तारः;  // Window width.
    पूर्णाङ्क गवाक्षः_height; // Window height.
    पूर्णाङ्क pixmap_विस्तारः;
    पूर्णाङ्क pixmap_height;
    पूर्णाङ्क गवाक्षः_x;
    पूर्णाङ्क गवाक्षः_y;

    /* XSettings and scaling */
    XSettingsClient *xsettings;
    bool xsettings_first_time;
    पूर्णाङ्क iscale;
    भिन्न scale;

    /* Font */
    XFont_समुच्चयः font_समुच्चयः;        // for UTF-8 systems
    XFontStruct *font_struct; // Latin1 (ASCII) fallback.
    SDL_ToolkitThaiEncodingX11 thai_encoding;
    SDL_ToolkitThaiFontX11 thai_font;
    
    /* Control colors */
    ध्रुव SDL_सन्देशः_Box_Color *color_hints;
    XColor xcolor[SDL_MESSAGEBOX_COLOR_गणनम्];
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
    शून्य *cb_दत्त;
    शून्य (*cb_on_scale_change)(संरचना SDL_Toolkit_गवाक्षः_X11 *, शून्य *);

    /* Popup windows */
    SDL_List_ग्रन्थिः *popup_windows;

    /* Event loop */
    XEvent *e;
    संरचना SDL_ToolkitControlX11 *previous_control;
    संरचना SDL_ToolkitControlX11 *कुञ्चिका_control_esc;
    संरचना SDL_ToolkitControlX11 *कुञ्चिका_control_enter;
    कुञ्चिका_Sym चरमः_कुञ्चिका_pressed;
    पूर्णाङ्क ev_i;
    भिन्न ev_scale;
    भिन्न ev_iscale;
    bool draw;
    bool close;
    दीर्घ event_आवरणम्;

#यदि_परिभाषितम् HAVE_FRIBIDI_H
    /* BIDI engine */
    SDL_FriBidi *fribidi;
    bool do_shaping;
#यदि_अन्तः

#यदि_परिभाषितम् HAVE_LIBTHAI_H
    SDL_LibThai *th;
#यदि_अन्तः

    bool flip_interface;
} SDL_Toolkit_गवाक्षः_X11;

प्रकारनिर्देश गणना SDL_ToolkitControlStateX11
{
    SDL_TOOLKIT_CONTROL_STATE_X11_प्रसामान्यम्,
    SDL_TOOLKIT_CONTROL_STATE_X11_HOVER,
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED, /* Key/Button Up */
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD, /* Key/Button Down */
    SDL_TOOLKIT_CONTROL_STATE_X11_DISABLED
} SDL_ToolkitControlStateX11;

प्रकारनिर्देश संरचना SDL_ToolkitControlX11
{
    SDL_Toolkit_गवाक्षः_X11 *गवाक्षः;
    SDL_ToolkitControlStateX11 state;
    SDL_Rect rect;
    bool selected;
    bool dynamic;
    bool is_default_enter;
    bool is_default_esc;
    bool do_आकार;

    /* User data */
    शून्य *दत्त;

    /* Virtual functions */
    शून्य (*func_draw)(संरचना SDL_ToolkitControlX11 *);
    शून्य (*func_calc_आकार)(संरचना SDL_ToolkitControlX11 *);
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
    शून्य *cb_दत्त;
    शून्य (*cb)(संरचना SDL_ToolkitMenuItemX11 *, शून्य *);
    SDL_List_ग्रन्थिः *sub_menu;

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
बाह्य SDL_Toolkit_गवाक्षः_X11 *X11_Toolkit_Create_गवाक्षः_Struct(SDL_गवाक्षः *parent, SDL_Toolkit_गवाक्षः_X11 *tkparent, SDL_Toolkit_गवाक्षः_बहुलकम्_X11 बहुलकम्, ध्रुव SDL_सन्देशः_Box_Color *colorhints, bool create_new_display);
बाह्य bool X11_Toolkit_Create_गवाक्षः_Res(SDL_Toolkit_गवाक्षः_X11 *दत्त, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क cx, पूर्णाङ्क cy, वर्ण *title);
बाह्य शून्य X11_Toolkit_Do_गवाक्षः_Event_Loop(SDL_Toolkit_गवाक्षः_X11 *दत्त);
बाह्य शून्य X11_Toolkit_Resize_गवाक्षः(SDL_Toolkit_गवाक्षः_X11 *दत्त, पूर्णाङ्क w, पूर्णाङ्क h);
बाह्य शून्य X11_Toolkit_Destroy_गवाक्षः(SDL_Toolkit_गवाक्षः_X11 *दत्त);
बाह्य शून्य X11_Toolkit_Signal_गवाक्षः_Close(SDL_Toolkit_गवाक्षः_X11 *दत्त);

/* GENERIC CONTROL FUNCTIONS */
बाह्य bool X11_Toolkit_Notify_Control_सम्बन्धि_आकार_Change(SDL_ToolkitControlX11 *control);

/* ICON CONTROL FUNCTIONS */
बाह्य SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_गवाक्षः_X11 *गवाक्षः, SDL_सन्देशः_Box_Flags flags);

/* LABEL CONTROL FUNCTIONS */
बाह्य SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_गवाक्षः_X11 *गवाक्षः, वर्ण *utf8);
बाह्य पूर्णाङ्क X11_Toolkit_Get_Label_Control_First_पङ्क्तिः_Height(SDL_ToolkitControlX11 *control);

/* BUTTON CONTROL FUNCTIONS */
बाह्य SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_गवाक्षः_X11 *गवाक्षः, ध्रुव SDL_सन्देशः_Box_Button_दत्त *दत्त);
बाह्य शून्य X11_Toolkit_पञ्जिकाकोशः_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, शून्य *दत्त, शून्य (*cb)(संरचना SDL_ToolkitControlX11 *, शून्य *));
बाह्य ध्रुव SDL_सन्देशः_Box_Button_दत्त *X11_Toolkit_Get_Button_Control_दत्त(SDL_ToolkitControlX11 *control);

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11

#यदि_अन्तः // SDL_x11toolkit_h_
