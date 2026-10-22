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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_x11toolkit_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_x11toolkit_h_

#ಅನ್ತರ್ಭಾವ "../../SDL_list.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11dyn.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11settings.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11toolkit.h"
#ಅನ್ತರ್ಭಾವ "xsettings-client.h"
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_fribidi.h"
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBTHAI_H
#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_libthai.h"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

/* Various predefined paddings */
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_TOOLKIT_X11_ELEMENT_PADDING 4
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_TOOLKIT_X11_ELEMENT_PADDING_2 12
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_TOOLKIT_X11_ELEMENT_PADDING_3 8
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_TOOLKIT_X11_ELEMENT_PADDING_4 16
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_TOOLKIT_X11_ELEMENT_PADDING_5 3

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ SDL_Toolkit_ಮಗು_ಬಹುಲಕ_X11
{
    SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_DIALOG,
    SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_ಮಗು, /* For embedding into a normal SDL_Window */
    SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_MENU,
    SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_TOOLTIP
} SDL_Toolkit_ಕಿಟಕಿ_ಬಹುಲಕ_X11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ SDL_ToolkitThaiEncodingX11
{
    SDL_TOOLKIT_THAI_ENCODING_X11_NONE,
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS, /* -0 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN, /* -2 */
    SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC, /* -1 */
    SDL_TOOLKIT_THAI_ENCODING_X11_8859,
    SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE
} SDL_ToolkitThaiEncodingX11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ SDL_ToolkitThaiFontX11
{
    SDL_TOOLKIT_THAI_FONT_X11_ಸ್ಥಾನಾಂತರ,
    SDL_TOOLKIT_THAI_FONT_X11_CELL
} SDL_ToolkitThaiFontX11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_Toolkit_ಕಿಟಕಿ_X11
{
    /* Locale */
    ಅಕ್ಷರ *origlocale;

    /*ಬಹುಲಕ*/
    SDL_Toolkit_ಕಿಟಕಿ_ಬಹುಲಕ_X11 ಬಹುಲಕ;

    /* Display */
    Display *display;
    ಪೂರ್ಣಾಂಕ screen;
    bool display_close;

    /*ಪೋಷಕ*/
    SDL_VideoDevice *ಪೋಷಕ_device;
    SDL_ಕಿಟಕಿ *ಪೋಷಕ;
    ರಚನೆ SDL_Toolkit_ಕಿಟಕಿ_X11 *tk_ಪೋಷಕ;

    /*ಕಿಟಕಿ*/
    ಕಿಟಕಿ_2 ಕಿಟಕಿ;
    Drawable drawable;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
    XImage *image;
    XShmSegmentInfo shm_info;
    ಪೂರ್ಣಾಂಕ shm_ಬೈಟುಗಳು_ಪ್ರತಿ_ಸಾಲು;
#ಆದರೆ_ಅಂತ್ಯ

    /* Visuals and drawing */
    Visual *visual;
    XVisualInfo vi;
    Colormap cmap;
    GC ctx;
    ಪೂರ್ಣಾಂಕ ಆಳ_2;
    bool pixmap;

    /* X11 extensions */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XDBE
    Xdbe_ಹಿಂಭಾಗ_ಬಫರ್ buf;
    bool xdbe; // Whether Xdbe is present or not
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
    bool xrandr; // Whether Xrandr is present or not
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
    bool shm;
    Bool shm_pixmap;
#ಆದರೆ_ಅಂತ್ಯ
    bool utf8;
    /* Atoms */
    Atom wm_protocols;
    Atom wm_delete_ಸಂದೇಶ;

    /* Window and pixmap sizes */
    ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಅಗಲ;  // Window width.
    ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಎತ್ತರ; // Window height.
    ಪೂರ್ಣಾಂಕ pixmap_ಅಗಲ;
    ಪೂರ್ಣಾಂಕ pixmap_ಎತ್ತರ;
    ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_x;
    ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_y;

    /* XSettings and scaling */
    XSettingsClient *xsettings;
    bool xsettings_ಮೊದಲ_ಸಮಯ;
    ಪೂರ್ಣಾಂಕ iscale;
    ದಶಮಾಂಶ scale;

    /* Font */
    XFont_ಗಣ font_ಗಣ;        // for UTF-8 systems
    XFontStruct *font_struct; // Latin1 (ASCII) fallback.
    SDL_ToolkitThaiEncodingX11 thai_encoding;
    SDL_ToolkitThaiFontX11 thai_font;
    
    /* Control colors */
    ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color *color_hints;
    XColor xcolor[SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ];
    XColor xcolor_bevel_l1;
    XColor xcolor_bevel_l2;
    XColor xcolor_bevel_d;
    XColor xcolor_pressed;
    XColor xcolor_disabled_ಪಠ್ಯ;

    /* Control list */
    bool has_focus;
    ರಚನೆ SDL_ToolkitControlX11 *focused_control;
    ರಚನೆ SDL_ToolkitControlX11 *fiddled_control;
    ರಚನೆ SDL_ToolkitControlX11 **controls;
    size_t controls_sz;
    ರಚನೆ SDL_ToolkitControlX11 **dyn_controls;
    size_t dyn_controls_sz;

    /* User callbacks */
    ಶೂನ್ಯ *cb_ದತ್ತಾಂಶ;
    ಶೂನ್ಯ (*cb_on_scale_change)(ರಚನೆ SDL_Toolkit_ಕಿಟಕಿ_X11 *, ಶೂನ್ಯ *);

    /* Popup windows */
    SDL_List_ಗಂಟು *popup_windows;

    /* Event loop */
    XEvent *e;
    ರಚನೆ SDL_ToolkitControlX11 *ಹಿಂದಿನ_control;
    ರಚನೆ SDL_ToolkitControlX11 *ಕೀಲಿ_control_esc;
    ರಚನೆ SDL_ToolkitControlX11 *ಕೀಲಿ_control_enter;
    ಕೀಲಿ_Sym ಕೊನೆಯ_ಕೀಲಿ_pressed;
    ಪೂರ್ಣಾಂಕ ev_i;
    ದಶಮಾಂಶ ev_scale;
    ದಶಮಾಂಶ ev_iscale;
    bool draw;
    bool close;
    ದೀರ್ಘ event_ಮುಖವಾಡ;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
    /* BIDI engine */
    SDL_FriBidi *fribidi;
    bool do_shaping;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBTHAI_H
    SDL_LibThai *th;
#ಆದರೆ_ಅಂತ್ಯ

    bool flip_interface;
} SDL_Toolkit_ಕಿಟಕಿ_X11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ SDL_ToolkitControlStateX11
{
    SDL_TOOLKIT_CONTROL_STATE_X11_ಸಾಮಾನ್ಯ,
    SDL_TOOLKIT_CONTROL_STATE_X11_HOVER,
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED, /* Key/Button Up */
    SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD, /* Key/Button Down */
    SDL_TOOLKIT_CONTROL_STATE_X11_DISABLED
} SDL_ToolkitControlStateX11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_ToolkitControlX11
{
    SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ;
    SDL_ToolkitControlStateX11 state;
    SDL_Rect rect;
    bool selected;
    bool dynamic;
    bool is_default_enter;
    bool is_default_esc;
    bool do_ಗಾತ್ರ;

    /* User data */
    ಶೂನ್ಯ *ದತ್ತಾಂಶ;

    /* Virtual functions */
    ಶೂನ್ಯ (*func_draw)(ರಚನೆ SDL_ToolkitControlX11 *);
    ಶೂನ್ಯ (*func_calc_ಗಾತ್ರ)(ರಚನೆ SDL_ToolkitControlX11 *);
    ಶೂನ್ಯ (*func_on_scale_change)(ರಚನೆ SDL_ToolkitControlX11 *);
    ಶೂನ್ಯ (*func_on_state_change)(ರಚನೆ SDL_ToolkitControlX11 *);
    ಶೂನ್ಯ (*func_free)(ರಚನೆ SDL_ToolkitControlX11 *);
} SDL_ToolkitControlX11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_Toolkit_Menu_ಅಂಶ_X11
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *utf8;
    bool checkbox;
    bool checked;
    bool disabled;
    ಶೂನ್ಯ *cb_ದತ್ತಾಂಶ;
    ಶೂನ್ಯ (*cb)(ರಚನೆ SDL_Toolkit_Menu_ಅಂಶ_X11 *, ಶೂನ್ಯ *);
    SDL_List_ಗಂಟು *sub_menu;

    /* Internal use */
    SDL_Rect utf8_rect;
    SDL_Rect hover_rect;
    SDL_Rect check_rect;
    SDL_ToolkitControlStateX11 state;
    ಪೂರ್ಣಾಂಕ arrow_x;
    ಪೂರ್ಣಾಂಕ arrow_y;
    bool ಹಿಮ್ಮುಖ_arrows;
} SDL_Toolkit_Menu_ಅಂಶ_X11;

/* WINDOW FUNCTIONS */
ಬಾಹ್ಯ SDL_Toolkit_ಕಿಟಕಿ_X11 *X11_Toolkit_Create_ಕಿಟಕಿ_Struct(SDL_ಕಿಟಕಿ *ಪೋಷಕ, SDL_Toolkit_ಕಿಟಕಿ_X11 *tkparent, SDL_Toolkit_ಕಿಟಕಿ_ಬಹುಲಕ_X11 ಬಹುಲಕ, ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color *colorhints, bool create_new_display);
ಬಾಹ್ಯ bool X11_Toolkit_Create_ಕಿಟಕಿ_Res(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ cx, ಪೂರ್ಣಾಂಕ cy, ಅಕ್ಷರ *title);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Toolkit_Do_ಕಿಟಕಿ_Event_Loop(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Toolkit_Resize_ಕಿಟಕಿ(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Toolkit_Destroy_ಕಿಟಕಿ(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Toolkit_Signal_ಕಿಟಕಿ_Close(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ);

/* GENERIC CONTROL FUNCTIONS */
ಬಾಹ್ಯ bool X11_Toolkit_Notify_Control_ದ_ಗಾತ್ರ_Change(SDL_ToolkitControlX11 *control);

/* ICON CONTROL FUNCTIONS */
ಬಾಹ್ಯ SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ, SDL_ಸಂದೇಶ_Box_Flags flags);

/* LABEL CONTROL FUNCTIONS */
ಬಾಹ್ಯ SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ, ಅಕ್ಷರ *utf8);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ X11_Toolkit_Get_Label_Control_ಮೊದಲ_ಸಾಲು_ಎತ್ತರ(SDL_ToolkitControlX11 *control);

/* BUTTON CONTROL FUNCTIONS */
ಬಾಹ್ಯ SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ);
ಬಾಹ್ಯ ಶೂನ್ಯ X11_Toolkit_ರಿಜಿಸ್ಟರ್_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, ಶೂನ್ಯ *ದತ್ತಾಂಶ, ಶೂನ್ಯ (*cb)(ರಚನೆ SDL_ToolkitControlX11 *, ಶೂನ್ಯ *));
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ *X11_Toolkit_Get_Button_Control_ದತ್ತಾಂಶ(SDL_ToolkitControlX11 *control);

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11

#ಆದರೆ_ಅಂತ್ಯ // SDL_x11toolkit_h_
