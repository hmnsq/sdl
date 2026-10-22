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

#నిర్వచితం_కాకపోతే SDL_x11toolkit_h_
#నిర్వచించు SDL_x11toolkit_h_

#అన్తర్భావ "../../SDL_list.h"
#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11dyn.h"
#అన్తర్భావ "SDL_x11settings.h"
#అన్తర్భావ "SDL_x11toolkit.h"
#అన్తర్భావ "xsettings-client.h"
#నిర్వచితమైతే HAVE_FRIBIDI_H
#అన్తర్భావ "../../core/unix/SDL_fribidi.h"
#అయితే_ముగింపు
#నిర్వచితమైతే HAVE_LIBTHAI_H
#అన్తర్భావ "../../core/unix/SDL_libthai.h"
#అయితే_ముగింపు

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

/* Various predefined paddings */
#నిర్వచించు SDL_TOOLKIT_X11_ELEMENT_PADDING 4
#నిర్వచించు SDL_TOOLKIT_X11_ELEMENT_PADDING_2 12
#నిర్వచించు SDL_TOOLKIT_X11_ELEMENT_PADDING_3 8
#నిర్వచించు SDL_TOOLKIT_X11_ELEMENT_PADDING_4 16
#నిర్వచించు SDL_TOOLKIT_X11_ELEMENT_PADDING_5 3

రకనిర్వచనం గణన SDL_Toolkit_బిడ్డ_బహుళకం_X11
{
    SDL_TOOLKIT_కిటికీ_బహుళకం_X11_DIALOG,
    SDL_TOOLKIT_కిటికీ_బహుళకం_X11_బిడ్డ, /* For embedding into a normal SDL_Window */
    SDL_TOOLKIT_కిటికీ_బహుళకం_X11_MENU,
    SDL_TOOLKIT_కిటికీ_బహుళకం_X11_TOOLTIP
} SDL_Toolkit_కిటికీ_బహుళకం_X11;

రకనిర్వచనం గణన SDL_ToolkitThaiEncodingX11
{
    SDL_TOOLKIT_THAI_ENCODING_X11_NONE,
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS, /* -0 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN, /* -2 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC, /* -1 */
    SDL_TOOLKIT_THAI_ENCODING_X11_8859,
    SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE
} SDL_ToolkitThaiEncodingX11;

రకనిర్వచనం గణన SDL_ToolkitThaiFontX11
{
    SDL_TOOLKIT_THAI_FONT_X11_స్థానభ్రంశం,
    SDL_TOOLKIT_THAI_FONT_X11_CELL
} SDL_ToolkitThaiFontX11;

రకనిర్వచనం నిర్మాణం SDL_Toolkit_కిటికీ_X11
{
    /* Locale */
    అక్షరం *origlocale;

    /*బహుళకం*/
    SDL_Toolkit_కిటికీ_బహుళకం_X11 బహుళకం;

    /* Display */
    Display *display;
    పూర్ణాంకం screen;
    bool display_close;

    /*మాతృ*/
    SDL_VideoDevice *మాతృ_device;
    SDL_కిటికీ *మాతృ;
    నిర్మాణం SDL_Toolkit_కిటికీ_X11 *tk_మాతృ;

    /*కిటికీ*/
    కిటికీ_2 కిటికీ;
    Drawable drawable;
#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
    XImage *image;
    XShmSegmentInfo shm_info;
    పూర్ణాంకం shm_బైట్లు_చొప్పున_పంక్తి;
#అయితే_ముగింపు

    /* Visuals and drawing */
    Visual *visual;
    XVisualInfo vi;
    Colormap cmap;
    GC ctx;
    పూర్ణాంకం లోతు_2;
    bool pixmap;

    /* X11 extensions */
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XDBE
    Xdbe_వెనుక_బఫరు buf;
    bool xdbe; // Whether Xdbe is present or not
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
    bool xrandr; // Whether Xrandr is present or not
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
    bool shm;
    Bool shm_pixmap;
#అయితే_ముగింపు
    bool utf8;
    /* Atoms */
    Atom wm_protocols;
    Atom wm_delete_సందేశం;

    /* Window and pixmap sizes */
    పూర్ణాంకం కిటికీ_వెడల్పు;  // Window width.
    పూర్ణాంకం కిటికీ_ఎత్తు; // Window height.
    పూర్ణాంకం pixmap_వెడల్పు;
    పూర్ణాంకం pixmap_ఎత్తు;
    పూర్ణాంకం కిటికీ_x;
    పూర్ణాంకం కిటికీ_y;

    /* XSettings and scaling */
    XSettingsClient *xsettings;
    bool xsettings_మొదటి_సమయం;
    పూర్ణాంకం iscale;
    దశాంశం scale;

    /* Font */
    XFont_సమితి font_సమితి;        // for UTF-8 systems
    XFontStruct *font_struct; // Latin1 (ASCII) fallback.
    SDL_ToolkitThaiEncodingX11 thai_encoding;
    SDL_ToolkitThaiFontX11 thai_font;
    
    /* Control colors */
    స్థిరరాశి SDL_సందేశం_Box_Color *color_hints;
    XColor xcolor[SDL_MESSAGEBOX_COLOR_లెక్క];
    XColor xcolor_bevel_l1;
    XColor xcolor_bevel_l2;
    XColor xcolor_bevel_d;
    XColor xcolor_pressed;
    XColor xcolor_disabled_పాఠ్యం;

    /* Control list */
    bool has_focus;
    నిర్మాణం SDL_ToolkitControlX11 *focused_control;
    నిర్మాణం SDL_ToolkitControlX11 *fiddled_control;
    నిర్మాణం SDL_ToolkitControlX11 **controls;
    size_t controls_sz;
    నిర్మాణం SDL_ToolkitControlX11 **dyn_controls;
    size_t dyn_controls_sz;

    /* User callbacks */
    శూన్య *cb_దత్తాంశం;
    శూన్య (*cb_on_scale_change)(నిర్మాణం SDL_Toolkit_కిటికీ_X11 *, శూన్య *);

    /* Popup windows */
    SDL_List_కణుపు *popup_windows;

    /* Event loop */
    XEvent *e;
    నిర్మాణం SDL_ToolkitControlX11 *మునుపటి_control;
    నిర్మాణం SDL_ToolkitControlX11 *కీలకం_control_esc;
    నిర్మాణం SDL_ToolkitControlX11 *కీలకం_control_enter;
    కీలకం_Sym చివరి_కీలకం_pressed;
    పూర్ణాంకం ev_i;
    దశాంశం ev_scale;
    దశాంశం ev_iscale;
    bool draw;
    bool close;
    దీర్ఘ event_ముసుగు;

#నిర్వచితమైతే HAVE_FRIBIDI_H
    /* BIDI engine */
    SDL_FriBidi *fribidi;
    bool do_shaping;
#అయితే_ముగింపు

#నిర్వచితమైతే HAVE_LIBTHAI_H
    SDL_LibThai *th;
#అయితే_ముగింపు

    bool flip_interface;
} SDL_Toolkit_కిటికీ_X11;

రకనిర్వచనం గణన SDL_ToolkitControlStateX11
{
    SDL_TOOLKIT_CONTROL_STATE_X11_సాధారణ,
    SDL_TOOLKIT_CONTROL_STATE_X11_HOVER,
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED, /* Key/Button Up */
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD, /* Key/Button Down */
    SDL_TOOLKIT_CONTROL_STATE_X11_DISABLED
} SDL_ToolkitControlStateX11;

రకనిర్వచనం నిర్మాణం SDL_ToolkitControlX11
{
    SDL_Toolkit_కిటికీ_X11 *కిటికీ;
    SDL_ToolkitControlStateX11 state;
    SDL_Rect rect;
    bool selected;
    bool dynamic;
    bool is_default_enter;
    bool is_default_esc;
    bool do_కొలత;

    /* User data */
    శూన్య *దత్తాంశం;

    /* Virtual functions */
    శూన్య (*func_draw)(నిర్మాణం SDL_ToolkitControlX11 *);
    శూన్య (*func_calc_కొలత)(నిర్మాణం SDL_ToolkitControlX11 *);
    శూన్య (*func_on_scale_change)(నిర్మాణం SDL_ToolkitControlX11 *);
    శూన్య (*func_on_state_change)(నిర్మాణం SDL_ToolkitControlX11 *);
    శూన్య (*func_free)(నిర్మాణం SDL_ToolkitControlX11 *);
} SDL_ToolkitControlX11;

రకనిర్వచనం నిర్మాణం SDL_Toolkit_Menu_అంశం_X11
{
    స్థిరరాశి అక్షరం *utf8;
    bool checkbox;
    bool checked;
    bool disabled;
    శూన్య *cb_దత్తాంశం;
    శూన్య (*cb)(నిర్మాణం SDL_Toolkit_Menu_అంశం_X11 *, శూన్య *);
    SDL_List_కణుపు *sub_menu;

    /* Internal use */
    SDL_Rect utf8_rect;
    SDL_Rect hover_rect;
    SDL_Rect check_rect;
    SDL_ToolkitControlStateX11 state;
    పూర్ణాంకం arrow_x;
    పూర్ణాంకం arrow_y;
    bool తిరగేయి_arrows;
} SDL_Toolkit_Menu_అంశం_X11;

/* WINDOW FUNCTIONS */
బాహ్య SDL_Toolkit_కిటికీ_X11 *X11_Toolkit_Create_కిటికీ_Struct(SDL_కిటికీ *మాతృ, SDL_Toolkit_కిటికీ_X11 *tkparent, SDL_Toolkit_కిటికీ_బహుళకం_X11 బహుళకం, స్థిరరాశి SDL_సందేశం_Box_Color *colorhints, bool create_new_display);
బాహ్య bool X11_Toolkit_Create_కిటికీ_Res(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం, పూర్ణాంకం w, పూర్ణాంకం h, పూర్ణాంకం cx, పూర్ణాంకం cy, అక్షరం *title);
బాహ్య శూన్య X11_Toolkit_Do_కిటికీ_Event_Loop(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం);
బాహ్య శూన్య X11_Toolkit_Resize_కిటికీ(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం, పూర్ణాంకం w, పూర్ణాంకం h);
బాహ్య శూన్య X11_Toolkit_Destroy_కిటికీ(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం);
బాహ్య శూన్య X11_Toolkit_Signal_కిటికీ_Close(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం);

/* GENERIC CONTROL FUNCTIONS */
బాహ్య bool X11_Toolkit_Notify_Control_యొక్క_కొలత_Change(SDL_ToolkitControlX11 *control);

/* ICON CONTROL FUNCTIONS */
బాహ్య SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_కిటికీ_X11 *కిటికీ, SDL_సందేశం_Box_Flags flags);

/* LABEL CONTROL FUNCTIONS */
బాహ్య SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_కిటికీ_X11 *కిటికీ, అక్షరం *utf8);
బాహ్య పూర్ణాంకం X11_Toolkit_Get_Label_Control_మొదటి_పంక్తి_ఎత్తు(SDL_ToolkitControlX11 *control);

/* BUTTON CONTROL FUNCTIONS */
బాహ్య SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_కిటికీ_X11 *కిటికీ, స్థిరరాశి SDL_సందేశం_Box_Button_దత్తాంశం *దత్తాంశం);
బాహ్య శూన్య X11_Toolkit_రిజిస్టరు_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, శూన్య *దత్తాంశం, శూన్య (*cb)(నిర్మాణం SDL_ToolkitControlX11 *, శూన్య *));
బాహ్య స్థిరరాశి SDL_సందేశం_Box_Button_దత్తాంశం *X11_Toolkit_Get_Button_Control_దత్తాంశం(SDL_ToolkitControlX11 *control);

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11

#అయితే_ముగింపు // SDL_x11toolkit_h_
