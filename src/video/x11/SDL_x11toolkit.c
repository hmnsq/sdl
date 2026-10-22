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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#ضمن "../../SDL_list.h"
#ضمن "SDL_x11video.h"
#جے_تعریف_شدہ SDL_USE_LIBDBUS
#ضمن "../../core/linux/SDL_system_theme.h"
#جے_انت
#جے_تعریف_شدہ HAVE_FRIBIDI_H
#ضمن "../../core/unix/SDL_fribidi.h"
#جے_انت
#ضمن "SDL_x11dyn.h"
#ضمن "SDL_x11toolkit.h"
#ضمن "SDL_x11settings.h"
#ضمن "SDL_x11modes.h"
#ضمن "xsettings-client.h"
#ضمن <X11/keysym.h>
#ضمن <locale.h>

#تعریف_کرو SDL_سیٹ_LOCALE 1
#تعریف_کرو SDL_GRAB 1

تعريفنوع تعداد SDL_Toolkit_متن_Type_X11
{
    SDL_TOOLKIT_متن_TYPE_X11_GENERIC,
    SDL_TOOLKIT_متن_TYPE_X11_THAI
} SDL_Toolkit_متن_Type_X11;

#جے_تعریف_شدہ HAVE_LIBTHAI_H
تعريفنوع بنية SDL_ToolkitThaiOverlayX11
{
    bool چوٹی;
    حرف *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#جے_انت

تعريفنوع بنية SDL_Toolkit_متن_Element_X11
{
    SDL_Toolkit_متن_Type_X11 type;
    حرف *str;
    size_t sz;
    SDL_Rect rect;
    صحيح font_h;
    فراغ (*str_free)(فراغ *);
#جے_تعریف_شدہ HAVE_LIBTHAI_H
    SDL_List_گرہ *thai_overlays;
#جے_انت
} SDL_Toolkit_متن_Element_X11;

تعريفنوع بنية SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 ماپا;

    /* Icon type */
    SDL_سنیہا_Box_Flags flags;
    حرف icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    صحيح icon_char_x;
    صحيح icon_char_y;
    صحيح icon_char_a;
    صحيح icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

تعريفنوع بنية SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 ماپا;

    /*انکڑے*/
    ثابت SDL_سنیہا_Box_Button_انکڑے *انکڑے;

    /*متن*/
    SDL_List_گرہ *متن;
    SDL_Rect متن_rect;
    
    /* Callback */
    فراغ *cb_انکڑے;
    فراغ (*cb)(بنية SDL_ToolkitControlX11 *, فراغ *);
} SDL_ToolkitButtonControlX11;

تعريفنوع بنية SDL_Toolkit_Label_Control_سطر_X11
{
    SDL_List_گرہ *متن;
    SDL_Rect rect;
#جے_تعریف_شدہ HAVE_FRIBIDI_H
    FriBidiParType par;
#جے_انت
} SDL_Toolkit_Label_Control_سطر_X11;

تعريفنوع بنية SDL_ToolkitLabelControlX11
{
    SDL_ToolkitControlX11 ماپا;

 /*   char **lines;
    int *y;
    size_t *szs;
    size_t sz;
#ifdef HAVE_FRIBIDI_H
    int *x;
    int *w;
    bool *free_lines;
    FriBidiParType *par_types;
#endif*/
    SDL_Toolkit_Label_Control_سطر_X11 *سطریں;
    size_t sz;
} SDL_ToolkitLabelControlX11;

تعريفنوع بنية SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 ماپا;

    SDL_List_گرہ *menu_اشیاء;
} SDL_ToolkitMenuBarControlX11;

تعريفنوع بنية SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 ماپا;

    SDL_List_گرہ *menu_اشیاء;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
ساكن ثابت حرف *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#تعریف_کرو G_ICONFONT_ناپ 22

/* General UI font */
ساكن ثابت حرف g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
ساكن ثابت حرف g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

ساكن ثابت حرف *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    عدم
};
#تعریف_کرو G_TOOLKITFONT_ناپ 140

ساكن ثابت SDL_سنیہا_Box_Color g_default_colors[SDL_MESSAGEBOX_COLOR_گنتی] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#جے_تعریف_شدہ SDL_USE_LIBDBUS
ساكن ثابت SDL_سنیہا_Box_Color g_default_colors_dark[SDL_MESSAGEBOX_COLOR_گنتی] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#إذا 0
ساكن ثابت SDL_سنیہا_Box_Color g_default_colors_dark_بلند_contrast[SDL_MESSAGEBOX_COLOR_گنتی] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

ساكن ثابت SDL_سنیہا_Box_Color g_default_colors_light_بلند_contrast[SDL_MESSAGEBOX_COLOR_گنتی] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#جے_انت

#جے_انت

ساكن صحيح g_shm_error;
ساكن صحيح (*g_old_error_handler)(Display *, XErrorEvent *) = عدم;

ساكن صحيح X11_Toolkit_Shared_حافظہ_Error_Handler(Display *d, XErrorEvent *e)
{
    إذا (e->error_کوڈ == BadAccess || e->error_کوڈ == BadRequest) {
        g_shm_error = True;
        أرجع 0;
    }
    أرجع g_old_error_handler(d, e);
}

ساكن فراغ X11_Toolkit_Init_کھڑکی_Pixmap(SDL_Toolkit_کھڑکی_X11 *انکڑے) {
    إذا (انکڑے->pixmap) {
#جے_بنا_تعریف NO_SHARED_حافظہ
        إذا (!انکڑے->shm_pixmap) {
            انکڑے->drawable = X11_XCreatePixmap(انکڑے->display, انکڑے->کھڑکی, انکڑے->pixmap_چوڑائی, انکڑے->pixmap_اچائی, انکڑے->ڈونگھائی_2);
        }
#وإلا
        انکڑے->drawable = X11_XCreatePixmap(انکڑے->display, انکڑے->کھڑکی, انکڑے->pixmap_چوڑائی, انکڑے->pixmap_اچائی, انکڑے->ڈونگھائی_2);
#جے_انت
#جے_بنا_تعریف NO_SHARED_حافظہ
        إذا (انکڑے->shm) {
            انکڑے->image = X11_XShmCreateImage(انکڑے->display, انکڑے->visual, انکڑے->ڈونگھائی_2, ZPixmap, عدم, &انکڑے->shm_info, انکڑے->pixmap_چوڑائی, انکڑے->pixmap_اچائی);
            إذا (انکڑے->image) {
                انکڑے->shm_بائٹاں_فی_سطر = انکڑے->image->بائٹاں_فی_سطر;

                انکڑے->shm_info.shmid = shmget(IPC_نجی, انکڑے->image->بائٹاں_فی_سطر * انکڑے->image->اچائی, IPC_CREAT | 0777);
                إذا (انکڑے->shm_info.shmid < 0) {
                    XDestroyImage(انکڑے->image);
                    انکڑے->image = عدم;
                    انکڑے->shm = false;
                    أرجع;
                }

                انکڑے->shm_info.readOnly = False;
                انکڑے->shm_info.shmaddr = انکڑے->image->انکڑے = (حرف *)shmat(انکڑے->shm_info.shmid, عدم, 0);
                إذا (((نشانیوالا حرف *)انکڑے->shm_info.shmaddr) == (نشانیوالا حرف *)-1) {
                    XDestroyImage(انکڑے->image);
                    انکڑے->shm = false;
                    انکڑے->image = عدم;
                    أرجع;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11_Toolkit_Shared_حافظہ_Error_Handler);
                X11_XShmAttach(انکڑے->display, &انکڑے->shm_info);
                X11_XSync(انکڑے->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                إذا (g_shm_error) {
                    XDestroyImage(انکڑے->image);
                    shmdt(انکڑے->shm_info.shmaddr);
                    shmctl(انکڑے->shm_info.shmid, IPC_RMID, عدم);
                    انکڑے->image = عدم;
                    انکڑے->shm = false;
                    أرجع;
                }

                إذا (انکڑے->shm_pixmap) {
                    انکڑے->drawable = X11_XShmCreatePixmap(انکڑے->display, انکڑے->کھڑکی, انکڑے->shm_info.shmaddr, &انکڑے->shm_info, انکڑے->pixmap_چوڑائی, انکڑے->pixmap_اچائی, انکڑے->ڈونگھائی_2);
                    إذا (انکڑے->drawable == None) {
                        انکڑے->shm_pixmap = False;
                    } وإلا {
                        XDestroyImage(انکڑے->image);
                        انکڑے->image = عدم;
                    }
                }

                shmctl(انکڑے->shm_info.shmid, IPC_RMID, عدم);
            } وإلا {
                انکڑے->shm = false;
            }
        }
#جے_انت
    }
}

ساكن فراغ X11_Toolkit_Init_کھڑکی_Fonts(SDL_Toolkit_کھڑکی_X11 *کھڑکی)
{    
    کھڑکی->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    کھڑکی->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    کھڑکی->utf8 = true;
    کھڑکی->font_سیٹ = عدم;
    إذا (SDL_X11_HAVE_UTF8) {
        حرف **missing = عدم;
        صحيح عدد_missing = 0;
        صحيح i_font;
        کھڑکی->font_struct = عدم;
        لكل (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            حرف *font;

            إذا (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_لدو_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_ناپ * کھڑکی->iscale);
                کھڑکی->font_سیٹ = X11_XCreate_Font_سیٹ(کھڑکی->display, font, &missing, &عدد_missing, عدم);
                SDL_free(font);

                إذا (!کھڑکی->font_سیٹ) {
                    إذا (کھڑکی->scale != 0 && کھڑکی->iscale > 0) {
                        کھڑکی->iscale = (صحيح)SDL_ceilf(کھڑکی->scale);
                        کھڑکی->scale = 0;
                    } وإلا {
                        کھڑکی->iscale--;
                    }
                    اذهب try_لدو_font;
                }
            } وإلا {
                کھڑکی->font_سیٹ = X11_XCreate_Font_سیٹ(کھڑکی->display, g_ToolkitFont[i_font], &missing, &عدد_missing, عدم);
            }

            إذا (missing) {
                X11_XFreeStringList(missing);
            }

            إذا (کھڑکی->font_سیٹ) {
                اكسر;
            }
        }

        إذا (!کھڑکی->font_سیٹ) {
            اذهب لدو_font_traditional;
        } وإلا {
            XFontStruct **font_structs;
            حرف **font_ناں;
            صحيح font_sz;
            صحيح i;
            
#جے_تعریف_شدہ HAVE_FRIBIDI_H
            کھڑکی->do_shaping = !X11_XContextDependentDrawing(کھڑکی->font_سیٹ);
#جے_انت
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFonts_دا_Font_سیٹ(کھڑکی->font_سیٹ, &font_structs, &font_ناں);
            لكل (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                إذا (SDL_strstr(font_ناں[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } وإلا إذا (SDL_strstr(font_ناں[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } وإلا إذا (SDL_strstr(font_ناں[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } وإلا إذا (SDL_strstr(font_ناں[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } وإلا إذا (SDL_strstr(font_ناں[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                إذا (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(کھڑکی->display, font_ناں[i]);
                    إذا (font_struct) {
                        إذا (font_struct->فی_char) {
                            صحيح glyphs_sz;
                            صحيح j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            لكل (j = 0; j < glyphs_sz; j++) {
                                إذا (font_struct->فی_char[j].lbearing < 0) {
                                    کھڑکی->thai_font = SDL_TOOLKIT_THAI_FONT_X11_وتھ;
                                }
                            }
                        }
                        X11_XFreeFont(کھڑکی->display, font_struct);
                    }
                }
                
                کھڑکی->thai_encoding = thai_encoding;
            } 
        }
    } وإلا
#جے_انت
    {
        حرف *font;

        لدو_font_traditional:
        کھڑکی->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_ناپ * کھڑکی->iscale);
        کھڑکی->font_struct = X11_XLoadQueryFont(کھڑکی->display, font);
        SDL_free(font);
        إذا (!کھڑکی->font_struct) {
            إذا (کھڑکی->iscale > 0) {
                إذا (کھڑکی->scale != 0) {
                    کھڑکی->iscale = (صحيح)SDL_ceilf(کھڑکی->scale);
                    کھڑکی->scale = 0;
                } وإلا {
                    کھڑکی->iscale--;
                }
                اذهب لدو_font_traditional;
            } وإلا {
                کھڑکی->font_struct = X11_XLoadQueryFont(کھڑکی->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

ساكن فراغ X11Toolkit_SettingsNotify(ثابت حرف *name, XSettingsAction action, XSettingsSetting *setting, فراغ *انکڑے)
{
    SDL_Toolkit_کھڑکی_X11 *کھڑکی;
    صحيح i;

    کھڑکی = انکڑے;

    إذا (کھڑکی->xsettings_پہلا_ویلا) {
        أرجع;
    }

    إذا (SDL_strcmp(name, SDL_XSETTINGS_GDK_کھڑکی_SCALING_ضارب) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_تیاری = false;
        bool pixmap_already_تیاری = false;

        إذا (کھڑکی->pixmap) {
            pixmap_already_تیاری = true;
        } وإلا {
            dbe_already_تیاری = true;
        }

        /* set scale vars */
        کھڑکی->scale = X11_GetGlobalContentScale(کھڑکی->display, کھڑکی->xsettings);
        کھڑکی->iscale = (صحيح)SDL_ceilf(کھڑکی->scale);
        إذا (کھڑکی->scale < 1) {
            کھڑکی->scale = 1;
        }
        إذا (SDL_roundf(کھڑکی->scale) == کھڑکی->scale) {
            کھڑکی->scale = 0;
        }

        /* setup fonts */
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
        إذا (کھڑکی->font_سیٹ) {
            X11_XFree_Font_سیٹ(کھڑکی->display, کھڑکی->font_سیٹ);
        }
#جے_انت
        إذا (کھڑکی->font_struct) {
            X11_XFreeFont(کھڑکی->display, کھڑکی->font_struct);
        }

        X11_Toolkit_Init_کھڑکی_Fonts(کھڑکی);

        /* set up window */
        إذا (کھڑکی->scale != 0) {
            کھڑکی->کھڑکی_چوڑائی = SDL_lroundf((کھڑکی->کھڑکی_چوڑائی/کھڑکی->iscale) * کھڑکی->scale);
            کھڑکی->کھڑکی_اچائی = SDL_lroundf((کھڑکی->کھڑکی_اچائی/کھڑکی->iscale) * کھڑکی->scale);
            کھڑکی->pixmap_چوڑائی = کھڑکی->کھڑکی_چوڑائی;
            کھڑکی->pixmap_اچائی = کھڑکی->کھڑکی_اچائی;
            کھڑکی->pixmap = true;
        } وإلا {
            کھڑکی->pixmap = false;
        }

        إذا (کھڑکی->pixmap) {
            إذا (!pixmap_already_تیاری) {
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
                إذا (SDL_X11_HAVE_XDBE && کھڑکی->xdbe) {
                    X11_Xdbe_Deallocate_پٹھ_بفر_Name(کھڑکی->display, کھڑکی->buf);
                }
#جے_انت
            }
            X11_XFreePixmap(کھڑکی->display, کھڑکی->drawable);
            X11_Toolkit_Init_کھڑکی_Pixmap(کھڑکی);
        } وإلا {
            إذا (!dbe_already_تیاری) {
                X11_XFreePixmap(کھڑکی->display, کھڑکی->drawable);
#جے_بنا_تعریف NO_SHARED_حافظہ
                إذا (کھڑکی->image) {
                    XDestroyImage(کھڑکی->image);
                    کھڑکی->image = عدم;
                }
#جے_انت
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
                إذا (SDL_X11_HAVE_XDBE && کھڑکی->xdbe) {
                    کھڑکی->buf = X11_Xdbe_Allocate_پٹھ_بفر_Name(کھڑکی->display, کھڑکی->کھڑکی, XdbeUndefined);
                    کھڑکی->drawable = کھڑکی->buf;
                }
#جے_انت
            }
        }

        /* notify controls */
        لكل (i = 0; i < کھڑکی->controls_sz; i++) {
            کھڑکی->controls[i]->do_ناپ = true;

            إذا (کھڑکی->controls[i]->func_on_scale_change) {
                کھڑکی->controls[i]->func_on_scale_change(کھڑکی->controls[i]);
            }

            إذا (کھڑکی->controls[i]->func_calc_ناپ) {
                کھڑکی->controls[i]->func_calc_ناپ(کھڑکی->controls[i]);
            }

            کھڑکی->controls[i]->do_ناپ = false;
        }

        /* notify cb */
        إذا (کھڑکی->cb_on_scale_change) {
            کھڑکی->cb_on_scale_change(کھڑکی, کھڑکی->cb_انکڑے);
        }

        /* update ev scales */
        إذا (!کھڑکی->pixmap) {
            کھڑکی->ev_scale = کھڑکی->ev_iscale = 1;
        } وإلا {
            کھڑکی->ev_scale = کھڑکی->scale;
            کھڑکی->ev_iscale = کھڑکی->iscale;
        }
    }
}

ساكن فراغ X11_Toolkit_Get_متن_چوڑائی_اچائی_For_Font(XFontStruct *font, ثابت حرف *str, صحيح nbytes, صحيح *pwidth, صحيح *pheight, صحيح *ascent, صحيح *font_اچائی)
{
    XCharStruct متن_structure;
    صحيح font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &متن_structure);
    *pwidth = متن_structure.چوڑائی;
    *pheight = متن_structure.ascent + متن_structure.descent;
    *ascent = متن_structure.ascent;
    إذا (font_اچائی) {
       *font_اچائی = font_ascent + font_descent;
    }
}

ساكن فراغ X11_Toolkit_Get_متن_چوڑائی_اچائی(SDL_Toolkit_کھڑکی_X11 *انکڑے, ثابت حرف *str, صحيح nbytes, صحيح *pwidth, صحيح *pheight, صحيح *ascent, صحيح *descent, صحيح *font_اچائی)
{
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    إذا (انکڑے->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8_متن_Extents(انکڑے->font_سیٹ, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.چوڑائی;
        *pheight = overall_logical.اچائی;
        *ascent = -overall_logical.y;
        *descent = overall_logical.اچائی - *ascent;

        إذا (font_اچائی) {
            XFont_سیٹ_Extents *extents;

            extents = X11_XExtents_دا_Font_سیٹ(انکڑے->font_سیٹ);
            *font_اچائی = extents->max_logical_extent.اچائی;
        }
    } وإلا
#جے_انت
    {
        XCharStruct متن_structure;
        صحيح font_direction, font_ascent, font_descent;
        X11_XTextExtents(انکڑے->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &متن_structure);
        *pwidth = متن_structure.چوڑائی;
        *pheight = متن_structure.ascent + متن_structure.descent;
        *ascent = متن_structure.ascent;
        *descent = متن_structure.descent;

        إذا (font_اچائی) {
            *font_اچائی = font_ascent + font_descent;
        }
    }
}

#جے_تعریف_شدہ HAVE_FRIBIDI_H
SDL_List_گرہ *X11_Toolkit_Make_متن_Elements(SDL_Toolkit_کھڑکی_X11 *انکڑے, حرف *txt, size_t sz, FriBidiParType *par)
#وإلا
SDL_List_گرہ *X11_Toolkit_Make_متن_Elements(SDL_Toolkit_کھڑکی_X11 *انکڑے, حرف *txt, size_t sz)
#جے_انت
{
    SDL_List_گرہ *list;
    حرف *str;
    حرف *بفر_2;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = عدم;
    thai = 0;
    str = txt;
    بفر_2 = SDL_malloc(1);
    بفر_2[0] = 0;
    
#جے_تعریف_شدہ HAVE_FRIBIDI_H
    إذا (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    إذا (انکڑے->fribidi) {
        حرف *fstr;
                
        fstr = SDL_FriBidi_Process(انکڑے->fribidi, str, sz, انکڑے->do_shaping, par);
        إذا (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#جے_انت        

    طالما (1) {
        حرف *new;
        حرف utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_قدم_UTF8((ثابت حرف **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        إذا (cp == 0 || cond == (thai ? false : true)) {
            SDL_Toolkit_متن_Element_X11 *element;
            
            element = SDL_malloc(حجم(SDL_Toolkit_متن_Element_X11));
            إذا (thai) {
                element->type = SDL_TOOLKIT_متن_TYPE_X11_THAI;
            } وإلا {
                element->type = SDL_TOOLKIT_متن_TYPE_X11_GENERIC;
            }
            element->str = SDL_strdup(بفر_2);
            element->sz = SDL_strlen(بفر_2);
            element->str_free = SDL_free;
            
            SDL_List_جوڑو(&list, element);
            
            SDL_free(بفر_2);
            بفر_2 = SDL_malloc(1);
            بفر_2[0] = 0;
            thai = thai ? false : true;
        }

        إذا (!cp) {
            اكسر;
        }
        
        SDL_UCS4_منزل_UTF8(cp, utf8);
        csz = SDL_strlen(بفر_2) + SDL_strlen(utf8) + 1;
        new = SDL_malloc(csz);
        SDL_strlcpy(new, بفر_2, csz);
        SDL_strlcat(new, utf8, csz);
        SDL_free(بفر_2);
        بفر_2 = new;
    }

    SDL_free(بفر_2);
    إذا (free_txt) {
        SDL_free(txt);
    }
    أرجع list;
}

فراغ X11_Toolkit_Shape_متن_Elements(SDL_Toolkit_کھڑکی_X11 *انکڑے, SDL_List_گرہ *list)
{
    SDL_List_گرہ *cursor;
    SDL_Toolkit_متن_Element_X11 *prev;
    صحيح عارضی;
    
    /* Shape and calculate bounding box */
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->اندراج;
#جے_تعریف_شدہ HAVE_LIBTHAI_H
        element->thai_overlays = عدم;
#جے_انت
        إذا (element->type == SDL_TOOLKIT_متن_TYPE_X11_THAI) {
            إذا (انکڑے->thai_font == SDL_TOOLKIT_THAI_FONT_X11_وتھ) {
                X11_Toolkit_Get_متن_چوڑائی_اچائی(انکڑے, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضی, عدم);
            } وإلا {
#جے_تعریف_شدہ HAVE_LIBTHAI_H
                إذا (انکڑے->th) {
                    بنية thcell_t *cells;
                    حرف *tis_str;
                    حرف *ادھار_tis_str;
                    size_t cells_sz;
                    size_t ادھار_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, حجم(بنية thcell_t));
                    انکڑے->th->make_cells((ثابت thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    ادھار_tis_str_sz = cells_sz;
                    ادھار_tis_str = SDL_malloc(ادھار_tis_str_sz + 1);
                    لكل (عارضی = 0; عارضی < cells_sz; عارضی++) {
                        ادھار_tis_str[عارضی] = cells[عارضی].ادھار;
                        
                        إذا (cells[عارضی].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            حرف *pre;
                            صحيح temp2;
                            
                            overlay = SDL_malloc(حجم(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", ادھار_tis_str, عارضی);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت حرف *)&cells[عارضی].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->چوٹی = false;
                            X11_Toolkit_Get_متن_چوڑائی_اچائی(انکڑے, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, عدم);
                            X11_Toolkit_Get_متن_چوڑائی_اچائی(انکڑے, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, عدم);
                            SDL_List_جوڑو(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        إذا (cells[عارضی].چوٹی) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            حرف *pre;
                            صحيح temp2;
                            
                            overlay = SDL_malloc(حجم(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", ادھار_tis_str, عارضی);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت حرف *)&cells[عارضی].چوٹی, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->چوٹی = true;
                            X11_Toolkit_Get_متن_چوڑائی_اچائی(انکڑے, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, عدم);
                            X11_Toolkit_Get_متن_چوڑائی_اچائی(انکڑے, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, عدم);
                            SDL_List_جوڑو(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    ادھار_tis_str[ادھار_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", ادھار_tis_str, ادھار_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11_Toolkit_Get_متن_چوڑائی_اچائی(انکڑے, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضی, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(ادھار_tis_str);
                }
#وإلا
                X11_Toolkit_Get_متن_چوڑائی_اچائی(انکڑے, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضی, &element->font_h);
#جے_انت            
            }
        } وإلا {
            X11_Toolkit_Get_متن_چوڑائی_اچائی(انکڑے, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضی, &element->font_h);
        }
        
        cursor = cursor->اگلا;
    }
    
    /* Add offsets */
    prev = عدم;
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->اندراج;        
        إذا (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } وإلا {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->اگلا;
    }
}


فراغ X11_Toolkit_Draw_متن_Elements(SDL_Toolkit_کھڑکی_X11 *انکڑے, SDL_List_گرہ *list, صحيح x, صحيح y)
{
    SDL_List_گرہ *cursor;
    
    cursor = list;
    
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->اندراج;
        إذا (element->type == SDL_TOOLKIT_متن_TYPE_X11_THAI) {
            إذا (انکڑے->thai_font == SDL_TOOLKIT_THAI_FONT_X11_وتھ) {
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
                إذا (انکڑے->utf8) {
                    X11_Xutf8DrawString(انکڑے->display, انکڑے->drawable, انکڑے->font_سیٹ, انکڑے->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } وإلا
#جے_انت
                {
                    X11_XDrawString(انکڑے->display, انکڑے->drawable, انکڑے->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } وإلا {    
#جے_تعریف_شدہ HAVE_LIBTHAI_H
                SDL_List_گرہ *overlay_cursor;
                    
                /* Draw the base string */
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
                إذا (انکڑے->utf8) {
                    X11_Xutf8DrawString(انکڑے->display, انکڑے->drawable, انکڑے->font_سیٹ, انکڑے->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } وإلا
#جے_انت
                {
                    X11_XDrawString(انکڑے->display, انکڑے->drawable, انکڑے->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                طالما (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->اندراج;
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
                    إذا (انکڑے->utf8) {
                        X11_Xutf8DrawString(انکڑے->display, انکڑے->drawable, انکڑے->font_سیٹ, انکڑے->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } وإلا
#جے_انت
                    {
                        X11_XDrawString(انکڑے->display, انکڑے->drawable, انکڑے->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->اگلا;
                }
#جے_انت                
            }
        } وإلا {
#جے_تعریف_شدہ X_HAVE_UTF8_STRING
            إذا (انکڑے->utf8) {
                X11_Xutf8DrawString(انکڑے->display, انکڑے->drawable, انکڑے->font_سیٹ, انکڑے->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } وإلا
#جے_انت
            {
                X11_XDrawString(انکڑے->display, انکڑے->drawable, انکڑے->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->اگلا;
    }
}

صحيح X11_Toolkit_Get_متن_Elements_Rect(SDL_List_گرہ *list, SDL_Rect *باہرلا)
{
    SDL_List_گرہ *cursor;
    صحيح ret;
    
    ret = 0;
    باہرلا->x = باہرلا->y = 0;
    باہرلا->w = باہرلا->h = 0;
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->اندراج;
        
        باہرلا->w += element->rect.w;
        باہرلا->h = SDL_max(باہرلا->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->اگلا;
    }
    
    أرجع ret;
}

فراغ X11_Toolkit_Free_متن_Elements_List_Contents(SDL_List_گرہ *list)
{
    SDL_List_گرہ *cursor;
    
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
#جے_تعریف_شدہ HAVE_LIBTHAI_H
        SDL_List_گرہ *overlay_cursor;
#جے_انت

        element = cursor->اندراج;
        
        إذا (element->str_free) {
            element->str_free(element->str);
        }
        
#جے_تعریف_شدہ HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        طالما (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->اندراج;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->اگلا;
        }
        SDL_ListClear(&element->thai_overlays);
#جے_انت
        
        SDL_free(element);
        
        cursor = cursor->اگلا;
    }
}

#تعریف_کرو X11_Toolkit_Free_متن_Elements(x) X11_Toolkit_Free_متن_Elements_List_Contents(x); SDL_ListClear(&x)
 
ساكن bool X11Toolkit_ShouldFlipUI(فراغ) 
{
    SDL_Locale **current_locales;
    ساكن ثابت SDL_Locale rtl_locales[] = {
        { "ar", عدم, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", عدم, },
        { "iw", عدم, },
        { "yi", عدم, },
        { "ur", عدم, },
        { "ug", عدم, },
        { "kd", عدم, },
        { "pk", "PK", },
        { "ps", عدم, }
    }; 
    صحيح current_locales_sz;
    صحيح i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    إذا (current_locales_sz <= 0) {
        أرجع false;        
    }
    لكل (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        إذا (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            إذا (!rtl_locales[i].country) {
                أرجع true;
            } وإلا {
                أرجع SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    أرجع false;
}

SDL_Toolkit_کھڑکی_X11 *X11_Toolkit_Create_کھڑکی_Struct(SDL_کھڑکی *ماپا, SDL_Toolkit_کھڑکی_X11 *tkparent, SDL_Toolkit_کھڑکی_منوال_X11 منوال, ثابت SDL_سنیہا_Box_Color *colorhints, bool create_new_display)
{
    SDL_Toolkit_کھڑکی_X11 *کھڑکی;
    صحيح i;
#جے_تعریف_شدہ SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#جے_انت
    #تعریف_کرو ErrorFreeRetNull(x, y) SDL_سیٹ_Error(x); SDL_free(y); أرجع عدم
    #تعریف_کرو ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_سیٹ_Error(x, y); SDL_free(z); أرجع عدم

    إذا (!SDL_X11_لدو_Symbols()) {
        أرجع عدم;
    }

    // This code could get called from multiple threads maybe?
    X11_XInit_دھاگے();

    کھڑکی = (SDL_Toolkit_کھڑکی_X11 *)SDL_malloc(حجم(SDL_Toolkit_کھڑکی_X11));
    إذا (!کھڑکی) {
        SDL_سیٹ_Error("Unable to allocate toolkit window structure");
        أرجع عدم;
    }

    کھڑکی->منوال = منوال;
    کھڑکی->tk_ماپا = tkparent;

#إذا SDL_سیٹ_LOCALE
    إذا (منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG) {
        کھڑکی->origlocale = setlocale(LC_ALL, عدم);
        إذا (کھڑکی->origlocale) {
            کھڑکی->origlocale = SDL_strdup(کھڑکی->origlocale);
            إذا (!کھڑکی->origlocale) {
                SDL_free(کھڑکی);
                أرجع عدم;
            }
            (فراغ)setlocale(LC_ALL, "");
        }
    }
#جے_انت

    کھڑکی->ماپا_device = عدم;
    إذا (create_new_display) {
        کھڑکی->display = X11_XOpenDisplay(عدم);
        کھڑکی->display_close = true;
        إذا (!کھڑکی->display) {
            ErrorFreeRetNull("Couldn't open X11 display", کھڑکی);
        }
    } وإلا {
        إذا (ماپا) {
            کھڑکی->ماپا_device = SDL_GetVideoDevice();
            کھڑکی->display = کھڑکی->ماپا_device->اندرونی->display;
            کھڑکی->display_close = false;
        } وإلا إذا (tkparent) {
            کھڑکی->display = tkparent->display;
            کھڑکی->display_close = false;
        } وإلا {
            کھڑکی->display = X11_XOpenDisplay(عدم);
            کھڑکی->display_close = true;
            إذا (!کھڑکی->display) {
                ErrorFreeRetNull("Couldn't open X11 display", کھڑکی);
            }
        }
    }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
    صحيح xrandr_event_ادھار, xrandr_error_ادھار;
    کھڑکی->xrandr = X11_XRRQueryExtension(کھڑکی->display, &xrandr_event_ادھار, &xrandr_error_ادھار);
#جے_انت

#جے_بنا_تعریف NO_SHARED_حافظہ
    کھڑکی->shm_pixmap = False;
    کھڑکی->shm = X11_XShmQueryExtension(کھڑکی->display) ? SDL_X11_HAVE_SHM : false;
    إذا (کھڑکی->shm) {
        صحيح major;
        صحيح minor;

        X11_XShm_Query_نسخہ(کھڑکی->display, &major, &minor, &کھڑکی->shm_pixmap);
        إذا (کھڑکی->shm_pixmap) {
            إذا (X11_XShmPixmapFormat(کھڑکی->display) != ZPixmap) {
                کھڑکی->shm_pixmap = False;
            }
        }
    }
#جے_انت

    /* Scale/Xsettings */
    کھڑکی->pixmap = false;
    کھڑکی->xsettings_پہلا_ویلا = true;
    کھڑکی->xsettings = xsettings_client_new(کھڑکی->display, DefaultScreen(کھڑکی->display), X11Toolkit_SettingsNotify, عدم, کھڑکی);
    کھڑکی->xsettings_پہلا_ویلا = false;
    کھڑکی->scale = X11_GetGlobalContentScale(کھڑکی->display, کھڑکی->xsettings);
    إذا (کھڑکی->scale < 1) {
        کھڑکی->scale = 1;
    }
    کھڑکی->iscale = (صحيح)SDL_ceilf(کھڑکی->scale);
    إذا (SDL_roundf(کھڑکی->scale) == کھڑکی->scale) {
        کھڑکی->scale = 0;
    }

    /* Fonts */
    X11_Toolkit_Init_کھڑکی_Fonts(کھڑکی);

    /* Color hints */
#جے_تعریف_شدہ SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    إذا (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#جے_انت

    إذا (!colorhints) {
#جے_تعریف_شدہ SDL_USE_LIBDBUS
        بدل (theme) {
            حالة SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                اكسر;
#إذا 0
            حالة SDL_SYSTEM_THEME_LIGHT_بلند_CONTRAST:
                colorhints = g_default_colors_light_بلند_contrast;
                اكسر;
            حالة SDL_SYSTEM_THEME_DARK_بلند_CONTRAST:
                colorhints = g_default_colors_dark_بلند_contrast;
                اكسر;
#جے_انت
            افتراضي:
                colorhints = g_default_colors;
        }
#وإلا
        colorhints = g_default_colors;
#جے_انت
    }
    کھڑکی->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    لكل (i = 0; i < SDL_MESSAGEBOX_COLOR_گنتی; i++) {
        کھڑکی->xcolor[i].flags = DoRed|DoGreen|DoBlue;
        کھڑکی->xcolor[i].red = colorhints[i].r * 257;
        کھڑکی->xcolor[i].green = colorhints[i].g * 257;
        کھڑکی->xcolor[i].blue = colorhints[i].b * 257;
    }

    /* Generate bevel and pressed colors */
    کھڑکی->xcolor_bevel_l1.flags = DoRed|DoGreen|DoBlue;
    کھڑکی->xcolor_bevel_l1.red = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 12500, 0, 65535);
    کھڑکی->xcolor_bevel_l1.green = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 12500, 0, 65535);
    کھڑکی->xcolor_bevel_l1.blue = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 12500, 0, 65535);

    کھڑکی->xcolor_bevel_l2.flags = DoRed|DoGreen|DoBlue;
    کھڑکی->xcolor_bevel_l2.red = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 32500, 0, 65535);
    کھڑکی->xcolor_bevel_l2.green = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 32500, 0, 65535);
    کھڑکی->xcolor_bevel_l2.blue = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 32500, 0, 65535);

    کھڑکی->xcolor_bevel_d.flags = DoRed|DoGreen|DoBlue;
    کھڑکی->xcolor_bevel_d.red = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red - 22500, 0, 65535);
    کھڑکی->xcolor_bevel_d.green = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green - 22500, 0, 65535);
    کھڑکی->xcolor_bevel_d.blue = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue - 22500, 0, 65535);

    کھڑکی->xcolor_pressed.flags = DoRed|DoGreen|DoBlue;
    کھڑکی->xcolor_pressed.red = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].red - 12500, 0, 65535);
    کھڑکی->xcolor_pressed.green = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].green - 12500, 0, 65535);
    کھڑکی->xcolor_pressed.blue = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].blue - 12500, 0, 65535);

    کھڑکی->xcolor_disabled_متن.flags = DoRed|DoGreen|DoBlue;
    کھڑکی->xcolor_disabled_متن.red = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_متن].red + 19500, 0, 65535);
    کھڑکی->xcolor_disabled_متن.green = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_متن].green + 19500, 0, 65535);
    کھڑکی->xcolor_disabled_متن.blue = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_متن].blue + 19500, 0, 65535);

    /* Screen */
    کھڑکی->ماپا = ماپا;
    إذا (ماپا) {
        SDL_Display_انکڑے *displaydata = SDL_Get_Display_Driver_انکڑے_For_کھڑکی(ماپا);
        کھڑکی->screen = displaydata->screen;
    } وإلا {
        کھڑکی->screen = DefaultScreen(کھڑکی->display);
    }

    /* Visuals */
    إذا (منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_بچہ) {
        کھڑکی->visual = ماپا->اندرونی->visual;
        کھڑکی->cmap = ماپا->اندرونی->colormap;
        X11_GetVisualInfoFromVisual(کھڑکی->display, کھڑکی->visual, &کھڑکی->vi);
        کھڑکی->ڈونگھائی_2 = کھڑکی->vi.ڈونگھائی_2;
    } وإلا {
        کھڑکی->visual = DefaultVisual(کھڑکی->display, کھڑکی->screen);
        کھڑکی->cmap = DefaultColormap(کھڑکی->display, کھڑکی->screen);
        کھڑکی->ڈونگھائی_2 = Default_ڈونگھائی(کھڑکی->display, کھڑکی->screen);
        X11_GetVisualInfoFromVisual(کھڑکی->display, کھڑکی->visual, &کھڑکی->vi);
    }

    /* Allocate colors */
    لكل (i = 0; i < SDL_MESSAGEBOX_COLOR_گنتی; i++) {
        X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor[i]);
    }
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor_bevel_l1);
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor_bevel_l2);
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor_bevel_d);
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor_pressed);
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor_disabled_متن);

    /* Control list */
    کھڑکی->has_focus = false;
    کھڑکی->controls = عدم;
    کھڑکی->controls_sz = 0;
    کھڑکی->dyn_controls_sz = 0;
    کھڑکی->fiddled_control = عدم;
    کھڑکی->dyn_controls = عدم;

    /* Menu windows */
    کھڑکی->popup_windows = عدم;

    /* BIDI engine */
#جے_تعریف_شدہ HAVE_FRIBIDI_H
    کھڑکی->fribidi = SDL_FriBidi_Create();
#جے_انت

#جے_تعریف_شدہ HAVE_LIBTHAI_H
    کھڑکی->th = SDL_LibThai_Create();
#جے_انت
    
    /* Interface direction */
    کھڑکی->flip_interface = X11Toolkit_ShouldFlipUI();
    
    أرجع کھڑکی;
}

ساكن فراغ X11_Toolkit_جوڑو_Control_منزل_کھڑکی(SDL_Toolkit_کھڑکی_X11 *کھڑکی, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    کھڑکی->controls_sz++;
    إذا (کھڑکی->controls_sz == 1) {
        کھڑکی->controls = (بنية SDL_ToolkitControlX11 **)SDL_malloc(حجم(بنية SDL_ToolkitControlX11 *));
    } وإلا {
        کھڑکی->controls = (بنية SDL_ToolkitControlX11 **)SDL_realloc(کھڑکی->controls, حجم(بنية SDL_ToolkitControlX11 *) * کھڑکی->controls_sz);
    }
    کھڑکی->controls[کھڑکی->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    إذا (control->dynamic) {
        کھڑکی->dyn_controls_sz++;
        إذا (کھڑکی->dyn_controls_sz == 1) {
            کھڑکی->dyn_controls = (بنية SDL_ToolkitControlX11 **)SDL_malloc(حجم(بنية SDL_ToolkitControlX11 *));
        } وإلا {
            کھڑکی->dyn_controls = (بنية SDL_ToolkitControlX11 **)SDL_realloc(کھڑکی->dyn_controls, حجم(بنية SDL_ToolkitControlX11 *) * کھڑکی->dyn_controls_sz);
        }
        کھڑکی->dyn_controls[کھڑکی->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    إذا (control->selected) {
        کھڑکی->focused_control = control;
    }
}

bool X11_Toolkit_Create_کھڑکی_Res(SDL_Toolkit_کھڑکی_X11 *انکڑے, صحيح w, صحيح h, صحيح cx, صحيح cy, حرف *title)
{
    صحيح x, y;
    XSizeHints *sizehints;
    XSet_کھڑکی_گن wnd_attr;
    Atom NET_WM_کھڑکی_TYPE, NET_WM_کھڑکی_TYPE_DIALOG, NET_WM_کھڑکی_TYPE_DROPDOWN_MENU, NET_WM_کھڑکی_TYPE_TOOLTIP;
    SDL_کھڑکی_انکڑے *windowdata = عدم;
    Display *display = انکڑے->display;
    XGCValues ctx_vals;
    کھڑکی_2 جڑ_win;
    کھڑکی_2 ماپا_win;
    بنانشانی لما gcflags = GCForeground | GCBackground;
    بنانشانی لما valuemask;
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
#جے_تعریف_شدہ XRANDR_DISABLED_BY_DEFAULT
    ثابت bool use_xrandr_by_default = false;
#وإلا
    ثابت bool use_xrandr_by_default = true;
#جے_انت
#جے_انت

    إذا (انکڑے->scale == 0) {
        انکڑے->کھڑکی_چوڑائی = w;
        انکڑے->کھڑکی_اچائی = h;
    } وإلا {
        انکڑے->کھڑکی_چوڑائی = SDL_lroundf((w/انکڑے->iscale) * انکڑے->scale);
        انکڑے->کھڑکی_اچائی = SDL_lroundf((h/انکڑے->iscale) * انکڑے->scale);
        انکڑے->pixmap_چوڑائی = w;
        انکڑے->pixmap_اچائی = h;
        انکڑے->pixmap = true;
    }

    إذا (انکڑے->ماپا) {
        windowdata = انکڑے->ماپا->اندرونی;
    }

    valuemask = CWEvent_نقاب | CWColormap;
    انکڑے->event_نقاب = Exposure_نقاب |
                       Button_Press_نقاب | Button_Release_نقاب | کلید_Press_نقاب | کلید_Release_نقاب |
                       Structure_Notify_نقاب | Focus_Change_نقاب | اشارہ_گر_Motion_نقاب;
    wnd_attr.event_نقاب = انکڑے->event_نقاب;
    wnd_attr.colormap = انکڑے->cmap;
    إذا (انکڑے->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU || انکڑے->منوال== SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    جڑ_win = جڑ_کھڑکی(display, انکڑے->screen);
    إذا (انکڑے->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_بچہ) {
        ماپا_win = windowdata->xwindow;
    } وإلا {
        ماپا_win = جڑ_win;
    }

    انکڑے->کھڑکی = X11_XCreate_کھڑکی(
        display, ماپا_win,
        0, 0,
        انکڑے->کھڑکی_چوڑائی, انکڑے->کھڑکی_اچائی,
        0, انکڑے->ڈونگھائی_2, داخلہ_Output, انکڑے->visual,
        valuemask, &wnd_attr);
    إذا (انکڑے->کھڑکی == None) {
        أرجع SDL_سیٹ_Error("Couldn't create X window");
    }

    إذا (windowdata && انکڑے->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG) {
        Atom _NET_WM_STATE = X11_XInternAtom(display, "_NET_WM_STATE", False);
        Atom stateatoms[16];
        size_t statecount = 0;
        // Set some message-boxy window states when attached to a parent window...
        // we skip the taskbar since this will pop to the front when the parent window is clicked in the taskbar, etc
        stateatoms[statecount++] = X11_XInternAtom(display, "_NET_WM_STATE_SKIP_TASKBAR", False);
        stateatoms[statecount++] = X11_XInternAtom(display, "_NET_WM_STATE_SKIP_PAGER", False);
        stateatoms[statecount++] = X11_XInternAtom(display, "_NET_WM_STATE_FOCUSED", False);
        stateatoms[statecount++] = X11_XInternAtom(display, "_NET_WM_STATE_MODAL", False);
        SDL_assert(statecount <= SDL_arraysize(stateatoms));
        X11_XChangeProperty(display, انکڑے->کھڑکی, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_منوال_Replace, (بنانشانی حرف *)stateatoms, statecount);
    }

    إذا (windowdata && انکڑے->منوال != SDL_TOOLKIT_کھڑکی_منوال_X11_بچہ) {
        X11_XSetTransientForHint(display, انکڑے->کھڑکی, windowdata->xwindow);
    }

    إذا (انکڑے->tk_ماپا) {
        X11_XSetTransientForHint(display, انکڑے->کھڑکی, انکڑے->tk_ماپا->کھڑکی);
    }

    SDL_X11_سیٹ_کھڑکی_Title(display, انکڑے->کھڑکی, title);

    // Let the window manager the type of the window
    إذا (انکڑے->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG) {
        NET_WM_کھڑکی_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_کھڑکی_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, انکڑے->کھڑکی, NET_WM_کھڑکی_TYPE, XA_ATOM, 32,
                            Prop_منوال_Replace,
                            (بنانشانی حرف *)&NET_WM_کھڑکی_TYPE_DIALOG, 1);
    } وإلا إذا (انکڑے->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU) {
        NET_WM_کھڑکی_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_کھڑکی_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, انکڑے->کھڑکی, NET_WM_کھڑکی_TYPE, XA_ATOM, 32,
                            Prop_منوال_Replace,
                            (بنانشانی حرف *)&NET_WM_کھڑکی_TYPE_DROPDOWN_MENU, 1);
    } وإلا إذا (انکڑے->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
        NET_WM_کھڑکی_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_کھڑکی_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, انکڑے->کھڑکی, NET_WM_کھڑکی_TYPE, XA_ATOM, 32,
                            Prop_منوال_Replace,
                            (بنانشانی حرف *)&NET_WM_کھڑکی_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    انکڑے->wm_delete_سنیہا = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, انکڑے->کھڑکی, &انکڑے->wm_delete_سنیہا, 1);
    انکڑے->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    إذا (انکڑے->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU || انکڑے->منوال== SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
        x = cx;
        y = cy;
        اذهب MOVEWINDOW;
    }
    إذا (windowdata) {
        XWindow_گن attrib;
        کھڑکی_2 dummy;

        X11_XGet_کھڑکی_گن(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.چوڑائی - انکڑے->کھڑکی_چوڑائی) / 2;
        y = attrib.y + (attrib.اچائی - انکڑے->کھڑکی_اچائی) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, جڑ_کھڑکی(display, انکڑے->screen), x, y, &x, &y, &dummy);
    } وإلا {
        ثابت SDL_VideoDevice *dev = SDL_GetVideoDevice();
        إذا (dev && dev->displays && dev->عدد_displays > 0) {
            ثابت SDL_VideoDisplay *dpy = dev->displays[0];
            ثابت SDL_Display_انکڑے *dpydata = dpy->اندرونی;
            x = dpydata->x + ((dpy->current_منوال->w - انکڑے->کھڑکی_چوڑائی) / 2);
            y = dpydata->y + ((dpy->current_منوال->h - انکڑے->کھڑکی_اچائی) / 3);
        }
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
        وإلا إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && انکڑے->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_باہرلا;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, جڑ_win);
            إذا (!screen_res) {
                اذهب NOXRANDR;
            }

            default_باہرلا = X11_XRRGetOutputPrimary(display, جڑ_win);
            إذا (default_باہرلا != None) {
                XRROutputInfo *باہرلا_info;

                باہرلا_info = X11_XRRGetOutputInfo(display, screen_res, default_باہرلا);
                إذا (باہرلا_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(باہرلا_info);
                    اذهب FIRSTOUTPUTXRANDR;
                }

                إذا (باہرلا_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, باہرلا_info->crtc);
                } وإلا إذا (باہرلا_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, باہرلا_info->crtcs[0]);
                } وإلا {
                    crtc_info = عدم;
                }
                
                إذا (crtc_info) {
                    x = (crtc_info->چوڑائی - انکڑے->کھڑکی_چوڑائی) / 2;
                    y = (crtc_info->اچائی - انکڑے->کھڑکی_اچائی) / 3;
                    X11_XRRFreeOutputInfo(باہرلا_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } وإلا {
                    X11_XRRFreeOutputInfo(باہرلا_info);
                    اذهب NOXRANDR;
                }
            } وإلا {
                    FIRSTOUTPUTXRANDR:
                    إذا (screen_res->noutput > 0) {
                        XRROutputInfo *باہرلا_info;

                        باہرلا_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        إذا (!باہرلا_info) {
                            اذهب FIRSTCRTCXRANDR;
                        }

                        إذا (باہرلا_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, باہرلا_info->crtc);
                        } وإلا إذا (باہرلا_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, باہرلا_info->crtcs[0]);
                        } وإلا {
                            crtc_info = عدم;
                        }

                        إذا (!crtc_info) {
                            X11_XRRFreeOutputInfo(باہرلا_info);
                            اذهب FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->چوڑائی - انکڑے->کھڑکی_چوڑائی) / 2;
                        y = (crtc_info->اچائی - انکڑے->کھڑکی_اچائی) / 3;
                        X11_XRRFreeOutputInfo(باہرلا_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        اذهب MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    إذا (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        اذهب NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    إذا (crtc_info) {
                        x = (crtc_info->چوڑائی - انکڑے->کھڑکی_چوڑائی) / 2;
                        y = (crtc_info->اچائی - انکڑے->کھڑکی_اچائی) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } وإلا {
                        X11_XRRFreeScreenResources(screen_res);
                        اذهب NOXRANDR;
                    }
            }
        }
#جے_انت
        وإلا {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (Display_چوڑائی(display, انکڑے->screen) - انکڑے->کھڑکی_چوڑائی) / 2;
            y = (Display_اچائی(display, انکڑے->screen) - انکڑے->کھڑکی_اچائی) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMove_کھڑکی(display, انکڑے->کھڑکی, x, y);
    انکڑے->کھڑکی_x = x;
    انکڑے->کھڑکی_y = y;

    sizehints = X11_XAlloc_ناپ_Hints();
    إذا (sizehints) {
        sizehints->flags = USPosition | USSize | PMax_ناپ | PMin_ناپ;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->چوڑائی = انکڑے->کھڑکی_چوڑائی;
        sizehints->اچائی = انکڑے->کھڑکی_اچائی;

        sizehints->min_چوڑائی_2 = sizehints->max_چوڑائی_2 = انکڑے->کھڑکی_چوڑائی;
        sizehints->min_اچائی_2 = sizehints->max_اچائی_2 = انکڑے->کھڑکی_اچائی;

        X11_XSetWMNormalHints(display, انکڑے->کھڑکی, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, انکڑے->کھڑکی);

    انکڑے->drawable = انکڑے->کھڑکی;
#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    إذا (SDL_X11_HAVE_XDBE && !انکڑے->pixmap) {
        صحيح xdbe_major, xdbe_minor;
        إذا (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            انکڑے->xdbe = true;
            انکڑے->buf = X11_Xdbe_Allocate_پٹھ_بفر_Name(display, انکڑے->کھڑکی, XdbeUndefined);
            انکڑے->drawable = انکڑے->buf;
        } وإلا {
            انکڑے->xdbe = false;
        }
    }
#جے_انت

    X11_Toolkit_Init_کھڑکی_Pixmap(انکڑے);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = انکڑے->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = انکڑے->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    إذا (!انکڑے->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = انکڑے->font_struct->fid;
    }
    انکڑے->ctx = X11_XCreateGC(انکڑے->display, انکڑے->drawable, gcflags, &ctx_vals);
    إذا (انکڑے->ctx == None) {
        أرجع SDL_سیٹ_Error("Couldn't create graphics context");
    }

    انکڑے->close = false;
    انکڑے->کلید_control_esc = انکڑے->کلید_control_enter = عدم;
    إذا (!انکڑے->pixmap) {
        انکڑے->ev_scale = انکڑے->ev_iscale = 1;
    } وإلا {
        انکڑے->ev_scale = انکڑے->scale;
        انکڑے->ev_iscale = انکڑے->iscale;
    }

#إذا SDL_GRAB
    إذا (انکڑے->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU || انکڑے->منوال== SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
        X11_XGrab_اشارہ_گر(display, انکڑے->کھڑکی, False, Button_Press_نقاب | Button_Release_نقاب | اشارہ_گر_Motion_نقاب, Grab_منوال_Async, Grab_منوال_Async, None, None, Current_ویلا);
        X11_XGrabKeyboard(display, انکڑے->کھڑکی, False, Grab_منوال_Async, Grab_منوال_Async, Current_ویلا);
    }
#جے_انت

    أرجع true;
}

ساكن فراغ X11_Toolkit_Draw_کھڑکی(SDL_Toolkit_کھڑکی_X11 *انکڑے) {
    SDL_Rect rect;
    صحيح i;

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && انکڑے->xdbe && !انکڑے->pixmap) {
        X11_XdbeBeginIdiom(انکڑے->display);
    }
#جے_انت

    X11_XSetForeground(انکڑے->display, انکڑے->ctx, انکڑے->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    إذا (انکڑے->pixmap) {
        X11_XFillRectangle(انکڑے->display, انکڑے->drawable, انکڑے->ctx, 0, 0, انکڑے->pixmap_چوڑائی, انکڑے->pixmap_اچائی);
    } وإلا {
        X11_XFillRectangle(انکڑے->display, انکڑے->drawable, انکڑے->ctx, 0, 0, انکڑے->کھڑکی_چوڑائی, انکڑے->کھڑکی_اچائی);
    }

    لكل (i = 0; i < انکڑے->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = انکڑے->controls[i];
        إذا (control) {
            إذا (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && انکڑے->xdbe && !انکڑے->pixmap) {
        Xdbe_وٹاندرا_Info وٹاندرا_info;
        وٹاندرا_info.وٹاندرا_کھڑکی = انکڑے->کھڑکی;
        وٹاندرا_info.وٹاندرا_action = XdbeUndefined;
        X11_Xdbe_وٹاندرا_Buffers(انکڑے->display, &وٹاندرا_info, 1);
        X11_Xdbe_سرا_Idiom(انکڑے->display);
    }
#جے_انت

    إذا (انکڑے->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = انکڑے->کھڑکی_چوڑائی;
        rect.h = انکڑے->کھڑکی_اچائی;
#جے_بنا_تعریف NO_SHARED_حافظہ
        إذا (انکڑے->shm) {
            إذا (انکڑے->shm_pixmap) {
                X11_XFlush(انکڑے->display);
                X11_XSync(انکڑے->display, false);
                scale_surface = SDL_CreateSurfaceFrom(انکڑے->pixmap_چوڑائی, انکڑے->pixmap_اچائی, X11_GetPixelFormatFromVisualInfo(انکڑے->display, &انکڑے->vi), انکڑے->shm_info.shmaddr, انکڑے->shm_بائٹاں_فی_سطر);
                SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_خطی);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(انکڑے->display, انکڑے->drawable, انکڑے->کھڑکی, انکڑے->ctx, 0, 0, انکڑے->کھڑکی_چوڑائی, انکڑے->کھڑکی_اچائی, 0, 0);
            } وإلا {
                X11_XShmGetImage(انکڑے->display, انکڑے->drawable, انکڑے->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(انکڑے->pixmap_چوڑائی, انکڑے->pixmap_اچائی, X11_GetPixelFormatFromVisualInfo(انکڑے->display, &انکڑے->vi), انکڑے->image->انکڑے, انکڑے->image->بائٹاں_فی_سطر);
                SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_خطی);
                X11_XShmPutImage(انکڑے->display, انکڑے->کھڑکی, انکڑے->ctx, انکڑے->image, 0, 0, 0, 0, انکڑے->کھڑکی_چوڑائی, انکڑے->کھڑکی_اچائی, False);
            }
        } وإلا
#جے_انت
        {
            XImage *image;

            image = X11_XGetImage(انکڑے->display, انکڑے->drawable, 0, 0 , انکڑے->pixmap_چوڑائی, انکڑے->pixmap_اچائی, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(انکڑے->pixmap_چوڑائی, انکڑے->pixmap_اچائی, X11_GetPixelFormatFromVisualInfo(انکڑے->display, &انکڑے->vi), image->انکڑے, image->بائٹاں_فی_سطر);
            SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_خطی);
            X11_XPutImage(انکڑے->display, انکڑے->کھڑکی, انکڑے->ctx, image, 0, 0, 0, 0, انکڑے->کھڑکی_چوڑائی, انکڑے->کھڑکی_اچائی);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(انکڑے->display);
}

ساكن SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_Toolkit_کھڑکی_X11 *انکڑے, صحيح x, صحيح y)
{
    صحيح i;

    لكل (i = 0; i < انکڑے->controls_sz; i++) {
        SDL_Rect *rect = &انکڑے->controls[i]->rect;
        إذا ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            أرجع انکڑے->controls[i];
        }
    }

    أرجع عدم;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
ساكن Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_Toolkit_کھڑکی_X11 *انکڑے = (SDL_Toolkit_کھڑکی_X11 *)arg;

    إذا (event->xany.display != انکڑے->display) {
        أرجع False;
    }

    إذا (event->xany.کھڑکی == انکڑے->کھڑکی) {
        أرجع True;
    }

    أرجع False;
}

فراغ X11_Toolkit_Process_کھڑکی_Events(SDL_Toolkit_کھڑکی_X11 *انکڑے, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    إذا ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        أرجع;
    }

    انکڑے->draw = false;
    انکڑے->e = e;

    بدل (e->type) {
        حالة Expose:
            انکڑے->draw = true;
            اكسر;
        حالة Client_سنیہا:
            إذا (e->xclient.سنیہا_type == انکڑے->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.انکڑے.l[0] == انکڑے->wm_delete_سنیہا) {
                انکڑے->close = true;
            }
            اكسر;
        حالة Focus_وچ:
            انکڑے->has_focus = true;
            اكسر;
        حالة Focus_باہرلا:
            انکڑے->has_focus = false;
            إذا (انکڑے->fiddled_control) {
                انکڑے->fiddled_control->selected = false;
            }
            انکڑے->fiddled_control = عدم;
            لكل (انکڑے->ev_i = 0; انکڑے->ev_i < انکڑے->controls_sz; انکڑے->ev_i++) {
                انکڑے->controls[انکڑے->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
            }
            اكسر;
        حالة MotionNotify:
            إذا (انکڑے->has_focus) {
                انکڑے->پچھلا_control = انکڑے->fiddled_control;
                انکڑے->fiddled_control = X11Toolkit_GetControlMouseIsOn(انکڑے, SDL_lroundf((e->xbutton.x/ انکڑے->ev_scale)* انکڑے->ev_iscale), SDL_lroundf((e->xbutton.y/ انکڑے->ev_scale)* انکڑے->ev_iscale));
                إذا (انکڑے->پچھلا_control) {
                    انکڑے->پچھلا_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
                    إذا (انکڑے->پچھلا_control->func_on_state_change) {
                        انکڑے->پچھلا_control->func_on_state_change(انکڑے->پچھلا_control);
                    }
                    انکڑے->draw = true;
                }
                إذا (انکڑے->fiddled_control) {
                    إذا (انکڑے->fiddled_control->dynamic) {
                        انکڑے->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        إذا (انکڑے->fiddled_control->func_on_state_change) {
                            انکڑے->fiddled_control->func_on_state_change(انکڑے->fiddled_control);
                        }
                        انکڑے->draw = true;
                    } وإلا {
                        انکڑے->fiddled_control = عدم;
                    }
                }
            }
            اكسر;
        حالة ButtonPress:
            انکڑے->پچھلا_control = انکڑے->fiddled_control;
            إذا (انکڑے->پچھلا_control) {
                انکڑے->پچھلا_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
                إذا (انکڑے->پچھلا_control->func_on_state_change) {
                    انکڑے->پچھلا_control->func_on_state_change(انکڑے->پچھلا_control);
                }
                انکڑے->draw = true;
            }
            إذا (e->xbutton.button == Button1) {
                انکڑے->fiddled_control = X11Toolkit_GetControlMouseIsOn(انکڑے, SDL_lroundf((e->xbutton.x/ انکڑے->ev_scale)* انکڑے->ev_iscale), SDL_lroundf((e->xbutton.y/ انکڑے->ev_scale)* انکڑے->ev_iscale));
                إذا (انکڑے->fiddled_control) {
                    انکڑے->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    إذا (انکڑے->fiddled_control->func_on_state_change) {
                        انکڑے->fiddled_control->func_on_state_change(انکڑے->fiddled_control);
                    }
                    انکڑے->draw = true;
                }
            }
            اكسر;
        حالة ButtonRelease:
            إذا (انکڑے->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU || انکڑے->منوال== SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
                صحيح cx;
                صحيح cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                إذا (cy < 0 || cx < 0) {
                    انکڑے->close = true;
                }

                إذا (cy > انکڑے->کھڑکی_اچائی || cx > انکڑے->کھڑکی_چوڑائی) {
                    انکڑے->close = true;
                }
            }

            إذا ((e->xbutton.button == Button1) && (انکڑے->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(انکڑے, SDL_lroundf((e->xbutton.x/ انکڑے->ev_scale)* انکڑے->ev_iscale), SDL_lroundf((e->xbutton.y/ انکڑے->ev_scale)* انکڑے->ev_iscale));
                إذا (انکڑے->fiddled_control == control) {
                    انکڑے->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    إذا (انکڑے->fiddled_control->func_on_state_change) {
                        انکڑے->fiddled_control->func_on_state_change(انکڑے->fiddled_control);
                    }
                    انکڑے->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
                    انکڑے->draw = true;
                }
            }
            اكسر;
        حالة کلید_Press:
            انکڑے->آخری_کلید_pressed = X11_XLookupKeysym(&e->xkey, 0);

            إذا (انکڑے->آخری_کلید_pressed == XK_Escape) {
                لكل (انکڑے->ev_i = 0; انکڑے->ev_i < انکڑے->controls_sz; انکڑے->ev_i++) {
                    إذا(انکڑے->controls[انکڑے->ev_i]->is_default_esc) {
                        انکڑے->controls[انکڑے->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        انکڑے->draw = true;
                        انکڑے->کلید_control_esc = انکڑے->controls[انکڑے->ev_i];
                    }
                }
            } وإلا إذا ((انکڑے->آخری_کلید_pressed == XK_Return) || (انکڑے->آخری_کلید_pressed == XK_KP_Enter)) {
                لكل (انکڑے->ev_i = 0; انکڑے->ev_i < انکڑے->controls_sz; انکڑے->ev_i++) {
                    إذا(انکڑے->controls[انکڑے->ev_i]->selected) {
                        انکڑے->controls[انکڑے->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        انکڑے->draw = true;
                        انکڑے->کلید_control_enter = انکڑے->controls[انکڑے->ev_i];
                    }
                }
            }
            اكسر;
        حالة کلید_Release:
        {
            کلید_Sym کلید = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            إذا (کلید != انکڑے->آخری_کلید_pressed) {
                اكسر;
            }

            إذا (کلید == XK_Escape) {
                إذا (انکڑے->کلید_control_esc) {
                    إذا (انکڑے->کلید_control_esc->func_on_state_change) {
                        انکڑے->کلید_control_esc->func_on_state_change(انکڑے->کلید_control_esc);
                    }
                }
            } وإلا إذا ((کلید == XK_Return) || (کلید == XK_KP_Enter)) {
                إذا (انکڑے->کلید_control_enter) {
                    إذا (انکڑے->کلید_control_enter->func_on_state_change) {
                        انکڑے->کلید_control_enter->func_on_state_change(انکڑے->کلید_control_enter);
                    }
                }
            } وإلا إذا (کلید == XK_Tab || کلید == XK_بایاں || کلید == XK_دایاں) {
                إذا (انکڑے->focused_control) {
                    انکڑے->focused_control->selected = false;
                }
                انکڑے->draw = true;
                لكل (انکڑے->ev_i = 0; انکڑے->ev_i < انکڑے->dyn_controls_sz; انکڑے->ev_i++) {
                    إذا (انکڑے->dyn_controls[انکڑے->ev_i] == انکڑے->focused_control) {
                        صحيح اگلا_اشاریہ;

                        إذا (کلید == XK_بایاں) {
                            اگلا_اشاریہ = انکڑے->ev_i - 1;
                        } وإلا {
                            اگلا_اشاریہ = انکڑے->ev_i + 1;
                        }
                        إذا ((اگلا_اشاریہ >= انکڑے->dyn_controls_sz) || (اگلا_اشاریہ < 0)) {
                            إذا (کلید == XK_دایاں || کلید == XK_بایاں) {
                                اگلا_اشاریہ = انکڑے->ev_i;
                            } وإلا {
                                اگلا_اشاریہ = 0;
                            }
                        }
                        انکڑے->focused_control = انکڑے->dyn_controls[اگلا_اشاریہ];
                        انکڑے->focused_control->selected = true;
                        اكسر;
                    }
                }
            }
            اكسر;
        }
    }

    إذا (انکڑے->draw) {
        X11_Toolkit_Draw_کھڑکی(انکڑے);
    }
}

فراغ X11_Toolkit_Do_کھڑکی_Event_Loop(SDL_Toolkit_کھڑکی_X11 *انکڑے) {
   طالما (!انکڑے->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(انکڑے->display, &e);
        إذا (انکڑے->xsettings) {
            xsettings_client_process_event(انکڑے->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(انکڑے->display, &e, X11Toolkit_EventTest, (XPointer)انکڑے);
        X11_Toolkit_Process_کھڑکی_Events(انکڑے, &e);
    }
}


فراغ X11_Toolkit_Resize_کھڑکی(SDL_Toolkit_کھڑکی_X11 *انکڑے, صحيح w, صحيح h) {
    إذا (!انکڑے->pixmap) {
        انکڑے->کھڑکی_چوڑائی = w;
        انکڑے->کھڑکی_اچائی = h;
    } وإلا {
        انکڑے->کھڑکی_چوڑائی = SDL_lroundf((w/انکڑے->iscale) * انکڑے->scale);
        انکڑے->کھڑکی_اچائی = SDL_lroundf((h/انکڑے->iscale) * انکڑے->scale);
        انکڑے->pixmap_چوڑائی = w;
        انکڑے->pixmap_اچائی = h;
        X11_XFreePixmap(انکڑے->display, انکڑے->drawable);
        X11_Toolkit_Init_کھڑکی_Pixmap(انکڑے);
    }

    X11_XResize_کھڑکی(انکڑے->display, انکڑے->کھڑکی, انکڑے->کھڑکی_چوڑائی, انکڑے->کھڑکی_اچائی);
}

ساكن فراغ X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->کھڑکی->display, icon_control->icon_char_font);
    SDL_free(control);
}

ساكن فراغ X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->کھڑکی->iscale;
    control->rect.h -= 2 * control->کھڑکی->iscale;
    X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x + (2 * control->کھڑکی->iscale), control->rect.y + (2* control->کھڑکی->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    بدل (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        حالة SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x+(1* control->کھڑکی->iscale), control->rect.y+(1* control->کھڑکی->iscale), control->rect.w-(2* control->کھڑکی->iscale), control->rect.h-(2* control->کھڑکی->iscale), 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_white.pixel);
                اكسر;
        حالة SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x+(1* control->کھڑکی->iscale), control->rect.y+(1* control->کھڑکی->iscale), control->rect.w-(2* control->کھڑکی->iscale), control->rect.h-(2* control->کھڑکی->iscale), 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_black.pixel);
                اكسر;
        حالة SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x+(1* control->کھڑکی->iscale), control->rect.y+(1* control->کھڑکی->iscale), control->rect.w-(2* control->کھڑکی->iscale), control->rect.h-(2* control->کھڑکی->iscale), 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_white.pixel);
                اكسر;
    }
    X11_XSetFont(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    إذا (!control->کھڑکی->utf8) {
        X11_XSetFont(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->font_struct->fid);
    }

    control->rect.w += 2 * control->کھڑکی->iscale;
    control->rect.h += 2 * control->کھڑکی->iscale;
}

ساكن فراغ X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *ادھار_control) {
    SDL_ToolkitIconControlX11 *control;
    صحيح icon_char_w;
    صحيح icon_wh;

    control = (SDL_ToolkitIconControlX11 *)ادھار_control;
    X11_Toolkit_Get_متن_چوڑائی_اچائی_For_Font(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, عدم);
    ادھار_control->rect.w = icon_char_w;
    ادھار_control->rect.h = control->icon_char_h;
    icon_wh = SDL_max(icon_char_w, control->icon_char_h) + SDL_TOOLKIT_X11_ELEMENT_PADDING * 2 * ادھار_control->کھڑکی->iscale;
    ادھار_control->rect.w = icon_wh;
    ادھار_control->rect.h = icon_wh;
    ادھار_control->rect.y = 0;
    ادھار_control->rect.x = 0;
    control->icon_char_y = control->icon_char_a + (ادھار_control->rect.h - control->icon_char_h)/2;
    control->icon_char_x = (ادھار_control->rect.w - icon_char_w)/2;
    ادھار_control->rect.w += 2 * ادھار_control->کھڑکی->iscale;
    ادھار_control->rect.h += 2 * ادھار_control->کھڑکی->iscale;
}

ساكن فراغ X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *ادھار_control) {
    SDL_ToolkitIconControlX11 *control;
    حرف *font;

    control = (SDL_ToolkitIconControlX11 *)ادھار_control;
    X11_XFreeFont(ادھار_control->کھڑکی->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_ناپ * ادھار_control->کھڑکی->iscale);
    control->icon_char_font = X11_XLoadQueryFont(ادھار_control->کھڑکی->display, font);
    SDL_free(font);
    إذا (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_ناپ * ادھار_control->کھڑکی->iscale);
        control->icon_char_font = X11_XLoadQueryFont(ادھار_control->کھڑکی->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, SDL_سنیہا_Box_Flags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *ادھار_control;
    حرف *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(حجم(SDL_ToolkitIconControlX11));
    ادھار_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_سیٹ_Error("Unable to allocate icon control structure");
        أرجع عدم;
    }

    /* Fill out struct */
    ادھار_control->کھڑکی = کھڑکی;
    ادھار_control->func_draw = X11Toolkit_DrawIconControl;
    ادھار_control->func_free = X11Toolkit_DestroyIconControl;
    ادھار_control->func_on_state_change = عدم;
    ادھار_control->func_calc_ناپ = X11Toolkit_CalculateIconControl;
    ادھار_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    ادھار_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
    ادھار_control->selected = false;
    ادھار_control->dynamic = false;
    ادھار_control->is_default_enter = false;
    ادھار_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_ناپ * کھڑکی->iscale);
    control->icon_char_font = X11_XLoadQueryFont(کھڑکی->display, font);
    SDL_free(font);
    إذا (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_ناپ * کھڑکی->iscale);
        control->icon_char_font = X11_XLoadQueryFont(کھڑکی->display, font);
        SDL_free(font);
        إذا (!control->icon_char_font) {
            SDL_free(control);
            أرجع عدم;
        }
    }

    /* Set colors */
    بدل (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    حالة SDL_MESSAGEBOX_ERROR:
        control->icon_char = 'X';
        control->xcolor_white.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_white.red = 65535;
        control->xcolor_white.green = 65535;
        control->xcolor_white.blue = 65535;
        control->xcolor_red.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_red.red = 65535;
        control->xcolor_red.green = 0;
        control->xcolor_red.blue = 0;
        control->xcolor_red_darker.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_red_darker.red = 40535;
        control->xcolor_red_darker.green = 0;
        control->xcolor_red_darker.blue = 0;
        X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &control->xcolor_white);
        X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &control->xcolor_red);
        X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &control->xcolor_red_darker);
        اكسر;
    حالة SDL_MESSAGEBOX_WARNING:
        control->icon_char = '!';
        control->xcolor_black.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_black.red = 0;
        control->xcolor_black.green = 0;
        control->xcolor_black.blue = 0;
        control->xcolor_yellow.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_yellow.red = 65535;
        control->xcolor_yellow.green = 65535;
        control->xcolor_yellow.blue = 0;
        X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &control->xcolor_black);
        X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &control->xcolor_yellow);
        اكسر;
    حالة SDL_MESSAGEBOX_INFORMATION:
        control->icon_char = 'i';
        control->xcolor_white.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_white.red = 65535;
        control->xcolor_white.green = 65535;
        control->xcolor_white.blue = 65535;
        control->xcolor_blue.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_blue.red = 0;
        control->xcolor_blue.green = 0;
        control->xcolor_blue.blue = 65535;
        X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &control->xcolor_white);
        X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &control->xcolor_blue);
        اكسر;
    افتراضي:
        X11_XFreeFont(کھڑکی->display, control->icon_char_font);
        SDL_free(control);
        أرجع عدم;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    إذا (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } وإلا إذا (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.red = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    إذا (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } وإلا إذا (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.green = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    إذا (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } وإلا إذا (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.blue = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(ادھار_control);

    X11_Toolkit_جوڑو_Control_منزل_کھڑکی(کھڑکی, ادھار_control);
    أرجع ادھار_control;
}

bool X11_Toolkit_Notify_Control_دا_ناپ_Change(SDL_ToolkitControlX11 *control) {
    إذا (control->func_calc_ناپ) {
        control->func_calc_ناپ(control);
        أرجع true;
    } وإلا {
        أرجع false;
    }
}

ساكن فراغ X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11_Toolkit_Get_متن_Elements_Rect(button_control->متن, &button_control->متن_rect);
    إذا (control->do_ناپ) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->کھڑکی->iscale + button_control->متن_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->کھڑکی->iscale + button_control->متن_rect.h;
    }
    button_control->متن_rect.x = (control->rect.w - button_control->متن_rect.w)/2;
    button_control->متن_rect.y = (control->rect.h - button_control->متن_rect.h)/2;
}


ساكن فراغ X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    /* Draw bevel */
    إذا (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
            X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor_bevel_d.pixel);
            X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

            X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor_bevel_l2.pixel);
            X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - (1* control->کھڑکی->iscale), control->rect.h - (1* control->کھڑکی->iscale));

            X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor_bevel_l1.pixel);
            X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x + 1 * control->کھڑکی->iscale, control->rect.y + 1 * control->کھڑکی->iscale,
                                   control->rect.w - 3 * control->کھڑکی->iscale, control->rect.h - 2 * control->کھڑکی->iscale);

            X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
            X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                               control->rect.x + 1 * control->کھڑکی->iscale, control->rect.y + 1 * control->کھڑکی->iscale,
                               control->rect.w - 3 * control->کھڑکی->iscale, control->rect.h - 3 * control->کھڑکی->iscale);

            X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor_pressed.pixel);
            X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                               control->rect.x + 2 * control->کھڑکی->iscale, control->rect.y + 2 * control->کھڑکی->iscale,
                               control->rect.w - 4 * control->کھڑکی->iscale, control->rect.h - 4 * control->کھڑکی->iscale);
        } وإلا {
            إذا (control->selected) {
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x + 1 * control->کھڑکی->iscale, control->rect.y + 1 * control->کھڑکی->iscale,
                                   control->rect.w - 3 * control->کھڑکی->iscale, control->rect.h - 3 * control->کھڑکی->iscale);

                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x + 2 * control->کھڑکی->iscale, control->rect.y + 2 * control->کھڑکی->iscale,
                                   control->rect.w - 4 * control->کھڑکی->iscale, control->rect.h - 4 * control->کھڑکی->iscale);

                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x + 2 * control->کھڑکی->iscale, control->rect.y + 2 * control->کھڑکی->iscale,
                                   control->rect.w - 5 * control->کھڑکی->iscale, control->rect.h - 5 * control->کھڑکی->iscale);

                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x + 3 * control->کھڑکی->iscale, control->rect.y + 3 * control->کھڑکی->iscale,
                                   control->rect.w - 6 * control->کھڑکی->iscale, control->rect.h - 6 * control->کھڑکی->iscale);
            } وإلا {
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - 1 * control->کھڑکی->iscale, control->rect.h - 1 * control->کھڑکی->iscale);

                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x + 1 * control->کھڑکی->iscale, control->rect.y + 1 * control->کھڑکی->iscale,
                                   control->rect.w - 2 * control->کھڑکی->iscale, control->rect.h - 2 * control->کھڑکی->iscale);

                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x + 1 * control->کھڑکی->iscale, control->rect.y + 1 * control->کھڑکی->iscale,
                                   control->rect.w - 3 * control->کھڑکی->iscale, control->rect.h - 3 * control->کھڑکی->iscale);

                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx,
                                   control->rect.x + 2 * control->کھڑکی->iscale, control->rect.y + 2 * control->کھڑکی->iscale,
                                   control->rect.w - 4 * control->کھڑکی->iscale, control->rect.h - 4 * control->کھڑکی->iscale);
            }
        }

    X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    X11_Toolkit_Draw_متن_Elements(control->کھڑکی, button_control->متن, control->rect.x + button_control->متن_rect.x, control->rect.y + button_control->متن_rect.y);
}

ساكن فراغ X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    إذا (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_انکڑے);
    }
}

ساكن فراغ X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_Toolkit_Free_متن_Elements(button_control->متن);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, ثابت SDL_سنیہا_Box_Button_انکڑے *انکڑے) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *ادھار_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(حجم(SDL_ToolkitButtonControlX11));
    ادھار_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_سیٹ_Error("Unable to allocate button control structure");
        أرجع عدم;
    }
    ادھار_control->کھڑکی = کھڑکی;
    ادھار_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
    ادھار_control->func_calc_ناپ = X11Toolkit_CalculateButtonControl;
    ادھار_control->func_draw = X11Toolkit_DrawButtonControl;
    ادھار_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    ادھار_control->func_free = X11Toolkit_DestroyButtonControl;
    ادھار_control->func_on_scale_change = عدم;
    ادھار_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
    ادھار_control->selected = false;
    ادھار_control->dynamic = true;
    ادھار_control->is_default_enter = false;
    ادھار_control->is_default_esc = false;
    إذا (انکڑے->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        ادھار_control->is_default_esc = true;
    }
    إذا (انکڑے->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        ادھار_control->is_default_enter = true;
        ادھار_control->selected = true;
    }
    control->cb = عدم;
    control->انکڑے = انکڑے;
#جے_تعریف_شدہ HAVE_FRIBIDI_H
    control->متن = X11_Toolkit_Make_متن_Elements(ادھار_control->کھڑکی, (حرف *)control->انکڑے->متن, SDL_strlen(control->انکڑے->متن), عدم);
#وإلا 
    control->متن = X11_Toolkit_Make_متن_Elements(ادھار_control->کھڑکی, (حرف *)control->انکڑے->متن, SDL_strlen(control->انکڑے->متن));
#جے_انت
    X11_Toolkit_Shape_متن_Elements(ادھار_control->کھڑکی, control->متن);
    
    ادھار_control->do_ناپ = true;
    X11Toolkit_CalculateButtonControl(ادھار_control);
    ادھار_control->do_ناپ = false;

    X11_Toolkit_جوڑو_Control_منزل_کھڑکی(کھڑکی, ادھار_control);
    أرجع ادھار_control;
}

فراغ X11_Toolkit_رجسٹر_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, فراغ *انکڑے, فراغ (*cb)(بنية SDL_ToolkitControlX11 *, فراغ *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_انکڑے = انکڑے;
    button_control->cb = cb;
}

ثابت SDL_سنیہا_Box_Button_انکڑے *X11_Toolkit_Get_Button_Control_انکڑے(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    أرجع button_control->انکڑے;
}

فراغ X11_Toolkit_Destroy_کھڑکی(SDL_Toolkit_کھڑکی_X11 *انکڑے) {
    صحيح i;

    إذا (!انکڑے) {
        أرجع;
    }

#إذا SDL_GRAB
    إذا (انکڑے->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU || انکڑے->منوال== SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
        X11_XUngrab_اشارہ_گر(انکڑے->display, Current_ویلا);
        X11_XUngrabKeyboard(انکڑے->display, Current_ویلا);
    }
#جے_انت

    لكل (i = 0; i < انکڑے->controls_sz; i++) {
        إذا (انکڑے->controls[i]->func_free) {
            انکڑے->controls[i]->func_free(انکڑے->controls[i]);
        }
    }
    SDL_free(انکڑے->controls);
    SDL_free(انکڑے->dyn_controls);

    إذا (انکڑے->popup_windows) {
        SDL_ListClear(&انکڑے->popup_windows);
    }

    إذا (انکڑے->pixmap) {
        X11_XFreePixmap(انکڑے->display, انکڑے->drawable);
    }

#جے_بنا_تعریف NO_SHARED_حافظہ
    إذا (انکڑے->pixmap && انکڑے->shm) {
        X11_XShmDetach(انکڑے->display, &انکڑے->shm_info);
        إذا (!انکڑے->shm_pixmap) {
            XDestroyImage(انکڑے->image);
        }
        shmdt(انکڑے->shm_info.shmaddr);
    }
#جے_انت

#جے_تعریف_شدہ X_HAVE_UTF8_STRING
    إذا (انکڑے->font_سیٹ) {
        X11_XFree_Font_سیٹ(انکڑے->display, انکڑے->font_سیٹ);
        انکڑے->font_سیٹ = عدم;
    }
#جے_انت

    إذا (انکڑے->font_struct) {
        X11_XFreeFont(انکڑے->display, انکڑے->font_struct);
        انکڑے->font_struct = عدم;
    }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && انکڑے->xdbe && !انکڑے->pixmap) {
        X11_Xdbe_Deallocate_پٹھ_بفر_Name(انکڑے->display, انکڑے->buf);
    }
#جے_انت

    إذا (انکڑے->xsettings) {
        xsettings_client_destroy(انکڑے->xsettings);
    }

    X11_XFreeGC(انکڑے->display, انکڑے->ctx);

    إذا (انکڑے->display) {
        إذا (انکڑے->کھڑکی != None) {
            X11_XWithdraw_کھڑکی(انکڑے->display, انکڑے->کھڑکی, انکڑے->screen);
            X11_XDestroy_کھڑکی(انکڑے->display, انکڑے->کھڑکی);
            انکڑے->کھڑکی = None;
        }

        إذا (انکڑے->display_close) {
            X11_XCloseDisplay(انکڑے->display);
        }
        انکڑے->display = عدم;
    }

#إذا SDL_سیٹ_LOCALE
    إذا (انکڑے->origlocale && (انکڑے->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG)) {
        (فراغ)setlocale(LC_ALL, انکڑے->origlocale);
        SDL_free(انکڑے->origlocale);
    }
#جے_انت

#جے_تعریف_شدہ HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(انکڑے->fribidi);
#جے_انت

#جے_تعریف_شدہ HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(انکڑے->th);
#جے_انت

    SDL_free(انکڑے);
}

ساكن صحيح X11_Toolkit_گنتی_سطریں_دا_متن(ثابت حرف *متن)
{
    صحيح نتیجہ = 0;
    طالما (متن && *متن) {
        ثابت حرف *lf = SDL_strchr(متن, '\n');
        نتیجہ++; // even without an endline, this counts as a line.
        متن = lf ? lf + 1 : عدم;
    }
    أرجع نتیجہ;
}

ساكن فراغ X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحيح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    لكل (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Draw_متن_Elements(control->کھڑکی, label_control->سطریں[i].متن, control->rect.x + label_control->سطریں[i].rect.x, control->rect.y + label_control->سطریں[i].rect.y);
    }
}

ساكن فراغ X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحيح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    لكل (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Free_متن_Elements(label_control->سطریں[i].متن);
    }
    SDL_free(label_control->سطریں);
    SDL_free(label_control);
}

ساكن فراغ X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *ادھار_control) {
    SDL_ToolkitLabelControlX11 *control;
    صحيح i;

    control = (SDL_ToolkitLabelControlX11 *)ادھار_control;
    
    إذا (ادھار_control->do_ناپ) {
        ادھار_control->rect.w = 0;
        ادھار_control->rect.h = 0;
    }
    
    لكل (i = 0; i < control->sz; i++) {
        صحيح font_h;
        
        font_h = X11_Toolkit_Get_متن_Elements_Rect(control->سطریں[i].متن, &control->سطریں[i].rect);
        
        إذا (ادھار_control->do_ناپ) {
            ادھار_control->rect.w = SDL_max(ادھار_control->rect.w, control->سطریں[i].rect.w);
        }
        
        إذا (i > 0) {
            control->سطریں[i].rect.y = font_h + control->سطریں[i - 1].rect.y;
        } وإلا {
            control->سطریں[i].rect.y = 0;
        }
    }

#جے_تعریف_شدہ HAVE_FRIBIDI_H
    إذا (ادھار_control->کھڑکی->fribidi) {
        FriBidiParType پہلا_ndn_dir;
        صحيح آخری_ndn;
    
        پہلا_ndn_dir = FRIBIDI_PAR_LTR;
        لكل (i = 0; i < control->sz; i++) {
            إذا (control->سطریں[i].par != FRIBIDI_PAR_ON) {
                پہلا_ndn_dir = control->سطریں[i].par;
            }
        }

        آخری_ndn = -1;
        لكل (i = 0; i < control->sz; i++) {
            بدل (control->سطریں[i].par) {
                حالة FRIBIDI_PAR_LTR:
                    control->سطریں[i].rect.x = 0;
                    آخری_ndn = i;
                    اكسر;
                حالة FRIBIDI_PAR_RTL:
                    control->سطریں[i].rect.x = ادھار_control->rect.w - control->سطریں[i].rect.w;
                    آخری_ndn = i;
                    اكسر;
                افتراضي:
                    إذا (آخری_ndn != -1) {
                        إذا (control->سطریں[آخری_ndn].par == FRIBIDI_PAR_RTL) {
                            control->سطریں[i].rect.x = ادھار_control->rect.w - control->سطریں[i].rect.w;
                        } وإلا {
                            control->سطریں[i].rect.x = 0;
                        }
                    } وإلا {
                        إذا (پہلا_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->سطریں[i].rect.x = ادھار_control->rect.w - control->سطریں[i].rect.w;
                        } وإلا {
                            control->سطریں[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#جے_انت
    
    إذا (ادھار_control->do_ناپ && control->sz) {
        ادھار_control->rect.h = control->سطریں[control->sz - 1].rect.y + control->سطریں[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, حرف *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *ادھار_control;
    صحيح i;
    
    إذا (!utf8) {
        أرجع عدم;
    }
 
    إذا (!SDL_strcmp(utf8, "")) {
        أرجع عدم;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(حجم(SDL_ToolkitLabelControlX11));
    ادھار_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_سیٹ_Error("Unable to allocate label control structure");
        أرجع عدم;
    }
    ادھار_control->کھڑکی = کھڑکی;
    ادھار_control->func_draw = X11Toolkit_DrawLabelControl;
    ادھار_control->func_on_state_change = عدم;
    ادھار_control->func_calc_ناپ = X11Toolkit_CalculateLabelControl;
    ادھار_control->func_free  = X11Toolkit_DestroyLabelControl;
    ادھار_control->func_on_scale_change = عدم;
    ادھار_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
    ادھار_control->selected = false;
    ادھار_control->dynamic = false;
    ادھار_control->rect.w = 0;
    ادھار_control->rect.h = 0;
    ادھار_control->is_default_enter = false;
    ادھار_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_گنتی_سطریں_دا_متن(utf8);
    control->سطریں = SDL_calloc(control->sz, حجم(SDL_Toolkit_Label_Control_سطر_X11));
    لكل (i = 0; i < control->sz; i++) {
        ثابت حرف *lf = SDL_strchr(utf8, '\n');
        ثابت صحيح لمائی = lf ? (lf - utf8) : SDL_strlen(utf8);
        صحيح sz;
        
        sz = لمائی;
        إذا (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#جے_تعریف_شدہ HAVE_FRIBIDI_H
        control->سطریں[i].متن = X11_Toolkit_Make_متن_Elements(ادھار_control->کھڑکی, (حرف *)utf8, sz, &control->سطریں[i].par);
#وإلا 
        control->سطریں[i].متن = X11_Toolkit_Make_متن_Elements(ادھار_control->کھڑکی, (حرف *)utf8, sz);
#جے_انت
        X11_Toolkit_Shape_متن_Elements(ادھار_control->کھڑکی, control->سطریں[i].متن);

        utf8 += لمائی + 1;
        إذا (!lf) {
            اكسر;
        }
    }

    ادھار_control->do_ناپ = true;
    X11Toolkit_CalculateLabelControl(ادھار_control);
    ادھار_control->do_ناپ = false;
    X11_Toolkit_جوڑو_Control_منزل_کھڑکی(کھڑکی, ادھار_control);

    أرجع ادھار_control;
}

صحيح X11_Toolkit_Get_Label_Control_پہلا_سطر_اچائی(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    أرجع label_control->سطریں[0].rect.h;
}

فراغ X11_Toolkit_Signal_کھڑکی_Close(SDL_Toolkit_کھڑکی_X11 *انکڑے) {
    انکڑے->close = true;
}

#جے_انت // SDL_VIDEO_DRIVER_X11
