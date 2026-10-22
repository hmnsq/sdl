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

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11

#ضمن "../../SDL_list.h"
#ضمن "SDL_x11video.h"
#که_تعریف_شوی SDL_USE_LIBDBUS
#ضمن "../../core/linux/SDL_system_theme.h"
#د_که_پای
#که_تعریف_شوی HAVE_FRIBIDI_H
#ضمن "../../core/unix/SDL_fribidi.h"
#د_که_پای
#ضمن "SDL_x11dyn.h"
#ضمن "SDL_x11toolkit.h"
#ضمن "SDL_x11settings.h"
#ضمن "SDL_x11modes.h"
#ضمن "xsettings-client.h"
#ضمن <X11/keysym.h>
#ضمن <locale.h>

#تعریف_کړه SDL_سېټ_LOCALE 1
#تعریف_کړه SDL_GRAB 1

تعريفنوع تعداد SDL_Toolkit_متن_Type_X11
{
    SDL_TOOLKIT_متن_TYPE_X11_GENERIC,
    SDL_TOOLKIT_متن_TYPE_X11_THAI
} SDL_Toolkit_متن_Type_X11;

#که_تعریف_شوی HAVE_LIBTHAI_H
تعريفنوع بنية SDL_ToolkitThaiOverlayX11
{
    bool سر;
    حرف *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#د_که_پای

تعريفنوع بنية SDL_Toolkit_متن_Element_X11
{
    SDL_Toolkit_متن_Type_X11 type;
    حرف *str;
    size_t sz;
    SDL_Rect rect;
    صحيح font_h;
    فراغ (*str_free)(فراغ *);
#که_تعریف_شوی HAVE_LIBTHAI_H
    SDL_List_غوټه *thai_overlays;
#د_که_پای
} SDL_Toolkit_متن_Element_X11;

تعريفنوع بنية SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 پلار;

    /* Icon type */
    SDL_پیغام_Box_Flags flags;
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
    SDL_ToolkitControlX11 پلار;

    /*معلومات*/
    ثابت SDL_پیغام_Box_Button_معلومات *معلومات;

    /*متن*/
    SDL_List_غوټه *متن;
    SDL_Rect متن_rect;
    
    /* Callback */
    فراغ *cb_معلومات;
    فراغ (*cb)(بنية SDL_ToolkitControlX11 *, فراغ *);
} SDL_ToolkitButtonControlX11;

تعريفنوع بنية SDL_Toolkit_Label_Control_کرښه_X11
{
    SDL_List_غوټه *متن;
    SDL_Rect rect;
#که_تعریف_شوی HAVE_FRIBIDI_H
    FriBidiParType par;
#د_که_پای
} SDL_Toolkit_Label_Control_کرښه_X11;

تعريفنوع بنية SDL_ToolkitLabelControlX11
{
    SDL_ToolkitControlX11 پلار;

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
    SDL_Toolkit_Label_Control_کرښه_X11 *کرښې;
    size_t sz;
} SDL_ToolkitLabelControlX11;

تعريفنوع بنية SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 پلار;

    SDL_List_غوټه *menu_توکي;
} SDL_ToolkitMenuBarControlX11;

تعريفنوع بنية SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 پلار;

    SDL_List_غوټه *menu_توکي;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
ساكن ثابت حرف *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#تعریف_کړه G_ICONFONT_اندازه 22

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
#تعریف_کړه G_TOOLKITFONT_اندازه 140

ساكن ثابت SDL_پیغام_Box_Color g_default_colors[SDL_MESSAGEBOX_COLOR_شمېر] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#که_تعریف_شوی SDL_USE_LIBDBUS
ساكن ثابت SDL_پیغام_Box_Color g_default_colors_dark[SDL_MESSAGEBOX_COLOR_شمېر] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#إذا 0
ساكن ثابت SDL_پیغام_Box_Color g_default_colors_dark_لوړ_contrast[SDL_MESSAGEBOX_COLOR_شمېر] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

ساكن ثابت SDL_پیغام_Box_Color g_default_colors_light_لوړ_contrast[SDL_MESSAGEBOX_COLOR_شمېر] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#د_که_پای

#د_که_پای

ساكن صحيح g_shm_error;
ساكن صحيح (*g_old_error_handler)(Display *, XErrorEvent *) = عدم;

ساكن صحيح X11_Toolkit_Shared_حافظه_Error_Handler(Display *d, XErrorEvent *e)
{
    إذا (e->error_کوډ == BadAccess || e->error_کوډ == BadRequest) {
        g_shm_error = True;
        أرجع 0;
    }
    أرجع g_old_error_handler(d, e);
}

ساكن فراغ X11_Toolkit_Init_کړکۍ_Pixmap(SDL_Toolkit_کړکۍ_X11 *معلومات) {
    إذا (معلومات->pixmap) {
#که_نه_تعریف_شوی NO_SHARED_حافظه
        إذا (!معلومات->shm_pixmap) {
            معلومات->drawable = X11_XCreatePixmap(معلومات->display, معلومات->کړکۍ, معلومات->pixmap_پلنوالی, معلومات->pixmap_لوړوالی, معلومات->ژوروالی_2);
        }
#وإلا
        معلومات->drawable = X11_XCreatePixmap(معلومات->display, معلومات->کړکۍ, معلومات->pixmap_پلنوالی, معلومات->pixmap_لوړوالی, معلومات->ژوروالی_2);
#د_که_پای
#که_نه_تعریف_شوی NO_SHARED_حافظه
        إذا (معلومات->shm) {
            معلومات->image = X11_XShmCreateImage(معلومات->display, معلومات->visual, معلومات->ژوروالی_2, ZPixmap, عدم, &معلومات->shm_info, معلومات->pixmap_پلنوالی, معلومات->pixmap_لوړوالی);
            إذا (معلومات->image) {
                معلومات->shm_بایټونه_فی_کرښه = معلومات->image->بایټونه_فی_کرښه;

                معلومات->shm_info.shmid = shmget(IPC_شخصي, معلومات->image->بایټونه_فی_کرښه * معلومات->image->لوړوالی, IPC_CREAT | 0777);
                إذا (معلومات->shm_info.shmid < 0) {
                    XDestroyImage(معلومات->image);
                    معلومات->image = عدم;
                    معلومات->shm = false;
                    أرجع;
                }

                معلومات->shm_info.readOnly = False;
                معلومات->shm_info.shmaddr = معلومات->image->معلومات = (حرف *)shmat(معلومات->shm_info.shmid, عدم, 0);
                إذا (((نښهدار حرف *)معلومات->shm_info.shmaddr) == (نښهدار حرف *)-1) {
                    XDestroyImage(معلومات->image);
                    معلومات->shm = false;
                    معلومات->image = عدم;
                    أرجع;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11_Toolkit_Shared_حافظه_Error_Handler);
                X11_XShmAttach(معلومات->display, &معلومات->shm_info);
                X11_XSync(معلومات->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                إذا (g_shm_error) {
                    XDestroyImage(معلومات->image);
                    shmdt(معلومات->shm_info.shmaddr);
                    shmctl(معلومات->shm_info.shmid, IPC_RMID, عدم);
                    معلومات->image = عدم;
                    معلومات->shm = false;
                    أرجع;
                }

                إذا (معلومات->shm_pixmap) {
                    معلومات->drawable = X11_XShmCreatePixmap(معلومات->display, معلومات->کړکۍ, معلومات->shm_info.shmaddr, &معلومات->shm_info, معلومات->pixmap_پلنوالی, معلومات->pixmap_لوړوالی, معلومات->ژوروالی_2);
                    إذا (معلومات->drawable == None) {
                        معلومات->shm_pixmap = False;
                    } وإلا {
                        XDestroyImage(معلومات->image);
                        معلومات->image = عدم;
                    }
                }

                shmctl(معلومات->shm_info.shmid, IPC_RMID, عدم);
            } وإلا {
                معلومات->shm = false;
            }
        }
#د_که_پای
    }
}

ساكن فراغ X11_Toolkit_Init_کړکۍ_Fonts(SDL_Toolkit_کړکۍ_X11 *کړکۍ)
{    
    کړکۍ->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    کړکۍ->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#که_تعریف_شوی X_HAVE_UTF8_STRING
    کړکۍ->utf8 = true;
    کړکۍ->font_سېټ = عدم;
    إذا (SDL_X11_HAVE_UTF8) {
        حرف **missing = عدم;
        صحيح عدد_missing = 0;
        صحيح i_font;
        کړکۍ->font_struct = عدم;
        لكل (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            حرف *font;

            إذا (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_بارول_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_اندازه * کړکۍ->iscale);
                کړکۍ->font_سېټ = X11_XCreate_Font_سېټ(کړکۍ->display, font, &missing, &عدد_missing, عدم);
                SDL_free(font);

                إذا (!کړکۍ->font_سېټ) {
                    إذا (کړکۍ->scale != 0 && کړکۍ->iscale > 0) {
                        کړکۍ->iscale = (صحيح)SDL_ceilf(کړکۍ->scale);
                        کړکۍ->scale = 0;
                    } وإلا {
                        کړکۍ->iscale--;
                    }
                    اذهب try_بارول_font;
                }
            } وإلا {
                کړکۍ->font_سېټ = X11_XCreate_Font_سېټ(کړکۍ->display, g_ToolkitFont[i_font], &missing, &عدد_missing, عدم);
            }

            إذا (missing) {
                X11_XFreeStringList(missing);
            }

            إذا (کړکۍ->font_سېټ) {
                اكسر;
            }
        }

        إذا (!کړکۍ->font_سېټ) {
            اذهب بارول_font_traditional;
        } وإلا {
            XFontStruct **font_structs;
            حرف **font_نومونه;
            صحيح font_sz;
            صحيح i;
            
#که_تعریف_شوی HAVE_FRIBIDI_H
            کړکۍ->do_shaping = !X11_XContextDependentDrawing(کړکۍ->font_سېټ);
#د_که_پای
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFonts_د_Font_سېټ(کړکۍ->font_سېټ, &font_structs, &font_نومونه);
            لكل (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                إذا (SDL_strstr(font_نومونه[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } وإلا إذا (SDL_strstr(font_نومونه[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } وإلا إذا (SDL_strstr(font_نومونه[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } وإلا إذا (SDL_strstr(font_نومونه[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } وإلا إذا (SDL_strstr(font_نومونه[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                إذا (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(کړکۍ->display, font_نومونه[i]);
                    إذا (font_struct) {
                        إذا (font_struct->فی_char) {
                            صحيح glyphs_sz;
                            صحيح j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            لكل (j = 0; j < glyphs_sz; j++) {
                                إذا (font_struct->فی_char[j].lbearing < 0) {
                                    کړکۍ->thai_font = SDL_TOOLKIT_THAI_FONT_X11_دننه_واټن;
                                }
                            }
                        }
                        X11_XFreeFont(کړکۍ->display, font_struct);
                    }
                }
                
                کړکۍ->thai_encoding = thai_encoding;
            } 
        }
    } وإلا
#د_که_پای
    {
        حرف *font;

        بارول_font_traditional:
        کړکۍ->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_اندازه * کړکۍ->iscale);
        کړکۍ->font_struct = X11_XLoadQueryFont(کړکۍ->display, font);
        SDL_free(font);
        إذا (!کړکۍ->font_struct) {
            إذا (کړکۍ->iscale > 0) {
                إذا (کړکۍ->scale != 0) {
                    کړکۍ->iscale = (صحيح)SDL_ceilf(کړکۍ->scale);
                    کړکۍ->scale = 0;
                } وإلا {
                    کړکۍ->iscale--;
                }
                اذهب بارول_font_traditional;
            } وإلا {
                کړکۍ->font_struct = X11_XLoadQueryFont(کړکۍ->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

ساكن فراغ X11Toolkit_SettingsNotify(ثابت حرف *name, XSettingsAction action, XSettingsSetting *setting, فراغ *معلومات)
{
    SDL_Toolkit_کړکۍ_X11 *کړکۍ;
    صحيح i;

    کړکۍ = معلومات;

    إذا (کړکۍ->xsettings_لومړی_وخت) {
        أرجع;
    }

    إذا (SDL_strcmp(name, SDL_XSETTINGS_GDK_کړکۍ_SCALING_ضریب) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_تیاری = false;
        bool pixmap_already_تیاری = false;

        إذا (کړکۍ->pixmap) {
            pixmap_already_تیاری = true;
        } وإلا {
            dbe_already_تیاری = true;
        }

        /* set scale vars */
        کړکۍ->scale = X11_GetGlobalContentScale(کړکۍ->display, کړکۍ->xsettings);
        کړکۍ->iscale = (صحيح)SDL_ceilf(کړکۍ->scale);
        إذا (کړکۍ->scale < 1) {
            کړکۍ->scale = 1;
        }
        إذا (SDL_roundf(کړکۍ->scale) == کړکۍ->scale) {
            کړکۍ->scale = 0;
        }

        /* setup fonts */
#که_تعریف_شوی X_HAVE_UTF8_STRING
        إذا (کړکۍ->font_سېټ) {
            X11_XFree_Font_سېټ(کړکۍ->display, کړکۍ->font_سېټ);
        }
#د_که_پای
        إذا (کړکۍ->font_struct) {
            X11_XFreeFont(کړکۍ->display, کړکۍ->font_struct);
        }

        X11_Toolkit_Init_کړکۍ_Fonts(کړکۍ);

        /* set up window */
        إذا (کړکۍ->scale != 0) {
            کړکۍ->کړکۍ_پلنوالی = SDL_lroundf((کړکۍ->کړکۍ_پلنوالی/کړکۍ->iscale) * کړکۍ->scale);
            کړکۍ->کړکۍ_لوړوالی = SDL_lroundf((کړکۍ->کړکۍ_لوړوالی/کړکۍ->iscale) * کړکۍ->scale);
            کړکۍ->pixmap_پلنوالی = کړکۍ->کړکۍ_پلنوالی;
            کړکۍ->pixmap_لوړوالی = کړکۍ->کړکۍ_لوړوالی;
            کړکۍ->pixmap = true;
        } وإلا {
            کړکۍ->pixmap = false;
        }

        إذا (کړکۍ->pixmap) {
            إذا (!pixmap_already_تیاری) {
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XDBE
                إذا (SDL_X11_HAVE_XDBE && کړکۍ->xdbe) {
                    X11_Xdbe_Deallocate_شا_بفر_Name(کړکۍ->display, کړکۍ->buf);
                }
#د_که_پای
            }
            X11_XFreePixmap(کړکۍ->display, کړکۍ->drawable);
            X11_Toolkit_Init_کړکۍ_Pixmap(کړکۍ);
        } وإلا {
            إذا (!dbe_already_تیاری) {
                X11_XFreePixmap(کړکۍ->display, کړکۍ->drawable);
#که_نه_تعریف_شوی NO_SHARED_حافظه
                إذا (کړکۍ->image) {
                    XDestroyImage(کړکۍ->image);
                    کړکۍ->image = عدم;
                }
#د_که_پای
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XDBE
                إذا (SDL_X11_HAVE_XDBE && کړکۍ->xdbe) {
                    کړکۍ->buf = X11_Xdbe_Allocate_شا_بفر_Name(کړکۍ->display, کړکۍ->کړکۍ, XdbeUndefined);
                    کړکۍ->drawable = کړکۍ->buf;
                }
#د_که_پای
            }
        }

        /* notify controls */
        لكل (i = 0; i < کړکۍ->controls_sz; i++) {
            کړکۍ->controls[i]->do_اندازه = true;

            إذا (کړکۍ->controls[i]->func_on_scale_change) {
                کړکۍ->controls[i]->func_on_scale_change(کړکۍ->controls[i]);
            }

            إذا (کړکۍ->controls[i]->func_calc_اندازه) {
                کړکۍ->controls[i]->func_calc_اندازه(کړکۍ->controls[i]);
            }

            کړکۍ->controls[i]->do_اندازه = false;
        }

        /* notify cb */
        إذا (کړکۍ->cb_on_scale_change) {
            کړکۍ->cb_on_scale_change(کړکۍ, کړکۍ->cb_معلومات);
        }

        /* update ev scales */
        إذا (!کړکۍ->pixmap) {
            کړکۍ->ev_scale = کړکۍ->ev_iscale = 1;
        } وإلا {
            کړکۍ->ev_scale = کړکۍ->scale;
            کړکۍ->ev_iscale = کړکۍ->iscale;
        }
    }
}

ساكن فراغ X11_Toolkit_Get_متن_پلنوالی_لوړوالی_For_Font(XFontStruct *font, ثابت حرف *str, صحيح nbytes, صحيح *pwidth, صحيح *pheight, صحيح *ascent, صحيح *font_لوړوالی)
{
    XCharStruct متن_structure;
    صحيح font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &متن_structure);
    *pwidth = متن_structure.پلنوالی;
    *pheight = متن_structure.ascent + متن_structure.descent;
    *ascent = متن_structure.ascent;
    إذا (font_لوړوالی) {
       *font_لوړوالی = font_ascent + font_descent;
    }
}

ساكن فراغ X11_Toolkit_Get_متن_پلنوالی_لوړوالی(SDL_Toolkit_کړکۍ_X11 *معلومات, ثابت حرف *str, صحيح nbytes, صحيح *pwidth, صحيح *pheight, صحيح *ascent, صحيح *descent, صحيح *font_لوړوالی)
{
#که_تعریف_شوی X_HAVE_UTF8_STRING
    إذا (معلومات->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8_متن_Extents(معلومات->font_سېټ, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.پلنوالی;
        *pheight = overall_logical.لوړوالی;
        *ascent = -overall_logical.y;
        *descent = overall_logical.لوړوالی - *ascent;

        إذا (font_لوړوالی) {
            XFont_سېټ_Extents *extents;

            extents = X11_XExtents_د_Font_سېټ(معلومات->font_سېټ);
            *font_لوړوالی = extents->max_logical_extent.لوړوالی;
        }
    } وإلا
#د_که_پای
    {
        XCharStruct متن_structure;
        صحيح font_direction, font_ascent, font_descent;
        X11_XTextExtents(معلومات->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &متن_structure);
        *pwidth = متن_structure.پلنوالی;
        *pheight = متن_structure.ascent + متن_structure.descent;
        *ascent = متن_structure.ascent;
        *descent = متن_structure.descent;

        إذا (font_لوړوالی) {
            *font_لوړوالی = font_ascent + font_descent;
        }
    }
}

#که_تعریف_شوی HAVE_FRIBIDI_H
SDL_List_غوټه *X11_Toolkit_Make_متن_Elements(SDL_Toolkit_کړکۍ_X11 *معلومات, حرف *txt, size_t sz, FriBidiParType *par)
#وإلا
SDL_List_غوټه *X11_Toolkit_Make_متن_Elements(SDL_Toolkit_کړکۍ_X11 *معلومات, حرف *txt, size_t sz)
#د_که_پای
{
    SDL_List_غوټه *list;
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
    
#که_تعریف_شوی HAVE_FRIBIDI_H
    إذا (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    إذا (معلومات->fribidi) {
        حرف *fstr;
                
        fstr = SDL_FriBidi_Process(معلومات->fribidi, str, sz, معلومات->do_shaping, par);
        إذا (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#د_که_پای        

    طالما (1) {
        حرف *new;
        حرف utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_ګام_UTF8((ثابت حرف **)&str, &sz);
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
            
            SDL_List_جمع_کړه(&list, element);
            
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

فراغ X11_Toolkit_Shape_متن_Elements(SDL_Toolkit_کړکۍ_X11 *معلومات, SDL_List_غوټه *list)
{
    SDL_List_غوټه *cursor;
    SDL_Toolkit_متن_Element_X11 *prev;
    صحيح لنډمهاله;
    
    /* Shape and calculate bounding box */
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->ثبت;
#که_تعریف_شوی HAVE_LIBTHAI_H
        element->thai_overlays = عدم;
#د_که_پای
        إذا (element->type == SDL_TOOLKIT_متن_TYPE_X11_THAI) {
            إذا (معلومات->thai_font == SDL_TOOLKIT_THAI_FONT_X11_دننه_واټن) {
                X11_Toolkit_Get_متن_پلنوالی_لوړوالی(معلومات, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &لنډمهاله, عدم);
            } وإلا {
#که_تعریف_شوی HAVE_LIBTHAI_H
                إذا (معلومات->th) {
                    بنية thcell_t *cells;
                    حرف *tis_str;
                    حرف *بنسټ_tis_str;
                    size_t cells_sz;
                    size_t بنسټ_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, حجم(بنية thcell_t));
                    معلومات->th->make_cells((ثابت thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    بنسټ_tis_str_sz = cells_sz;
                    بنسټ_tis_str = SDL_malloc(بنسټ_tis_str_sz + 1);
                    لكل (لنډمهاله = 0; لنډمهاله < cells_sz; لنډمهاله++) {
                        بنسټ_tis_str[لنډمهاله] = cells[لنډمهاله].بنسټ;
                        
                        إذا (cells[لنډمهاله].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            حرف *pre;
                            صحيح temp2;
                            
                            overlay = SDL_malloc(حجم(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", بنسټ_tis_str, لنډمهاله);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت حرف *)&cells[لنډمهاله].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->سر = false;
                            X11_Toolkit_Get_متن_پلنوالی_لوړوالی(معلومات, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, عدم);
                            X11_Toolkit_Get_متن_پلنوالی_لوړوالی(معلومات, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, عدم);
                            SDL_List_جمع_کړه(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        إذا (cells[لنډمهاله].سر) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            حرف *pre;
                            صحيح temp2;
                            
                            overlay = SDL_malloc(حجم(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", بنسټ_tis_str, لنډمهاله);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت حرف *)&cells[لنډمهاله].سر, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->سر = true;
                            X11_Toolkit_Get_متن_پلنوالی_لوړوالی(معلومات, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, عدم);
                            X11_Toolkit_Get_متن_پلنوالی_لوړوالی(معلومات, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, عدم);
                            SDL_List_جمع_کړه(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    بنسټ_tis_str[بنسټ_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", بنسټ_tis_str, بنسټ_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11_Toolkit_Get_متن_پلنوالی_لوړوالی(معلومات, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &لنډمهاله, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(بنسټ_tis_str);
                }
#وإلا
                X11_Toolkit_Get_متن_پلنوالی_لوړوالی(معلومات, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &لنډمهاله, &element->font_h);
#د_که_پای            
            }
        } وإلا {
            X11_Toolkit_Get_متن_پلنوالی_لوړوالی(معلومات, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &لنډمهاله, &element->font_h);
        }
        
        cursor = cursor->بل;
    }
    
    /* Add offsets */
    prev = عدم;
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->ثبت;        
        إذا (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } وإلا {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->بل;
    }
}


فراغ X11_Toolkit_Draw_متن_Elements(SDL_Toolkit_کړکۍ_X11 *معلومات, SDL_List_غوټه *list, صحيح x, صحيح y)
{
    SDL_List_غوټه *cursor;
    
    cursor = list;
    
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->ثبت;
        إذا (element->type == SDL_TOOLKIT_متن_TYPE_X11_THAI) {
            إذا (معلومات->thai_font == SDL_TOOLKIT_THAI_FONT_X11_دننه_واټن) {
#که_تعریف_شوی X_HAVE_UTF8_STRING
                إذا (معلومات->utf8) {
                    X11_Xutf8DrawString(معلومات->display, معلومات->drawable, معلومات->font_سېټ, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } وإلا
#د_که_پای
                {
                    X11_XDrawString(معلومات->display, معلومات->drawable, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } وإلا {    
#که_تعریف_شوی HAVE_LIBTHAI_H
                SDL_List_غوټه *overlay_cursor;
                    
                /* Draw the base string */
#که_تعریف_شوی X_HAVE_UTF8_STRING
                إذا (معلومات->utf8) {
                    X11_Xutf8DrawString(معلومات->display, معلومات->drawable, معلومات->font_سېټ, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } وإلا
#د_که_پای
                {
                    X11_XDrawString(معلومات->display, معلومات->drawable, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                طالما (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->ثبت;
#که_تعریف_شوی X_HAVE_UTF8_STRING
                    إذا (معلومات->utf8) {
                        X11_Xutf8DrawString(معلومات->display, معلومات->drawable, معلومات->font_سېټ, معلومات->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } وإلا
#د_که_پای
                    {
                        X11_XDrawString(معلومات->display, معلومات->drawable, معلومات->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->بل;
                }
#د_که_پای                
            }
        } وإلا {
#که_تعریف_شوی X_HAVE_UTF8_STRING
            إذا (معلومات->utf8) {
                X11_Xutf8DrawString(معلومات->display, معلومات->drawable, معلومات->font_سېټ, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } وإلا
#د_که_پای
            {
                X11_XDrawString(معلومات->display, معلومات->drawable, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->بل;
    }
}

صحيح X11_Toolkit_Get_متن_Elements_Rect(SDL_List_غوټه *list, SDL_Rect *بهر)
{
    SDL_List_غوټه *cursor;
    صحيح ret;
    
    ret = 0;
    بهر->x = بهر->y = 0;
    بهر->w = بهر->h = 0;
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->ثبت;
        
        بهر->w += element->rect.w;
        بهر->h = SDL_max(بهر->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->بل;
    }
    
    أرجع ret;
}

فراغ X11_Toolkit_Free_متن_Elements_List_Contents(SDL_List_غوټه *list)
{
    SDL_List_غوټه *cursor;
    
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
#که_تعریف_شوی HAVE_LIBTHAI_H
        SDL_List_غوټه *overlay_cursor;
#د_که_پای

        element = cursor->ثبت;
        
        إذا (element->str_free) {
            element->str_free(element->str);
        }
        
#که_تعریف_شوی HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        طالما (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->ثبت;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->بل;
        }
        SDL_ListClear(&element->thai_overlays);
#د_که_پای
        
        SDL_free(element);
        
        cursor = cursor->بل;
    }
}

#تعریف_کړه X11_Toolkit_Free_متن_Elements(x) X11_Toolkit_Free_متن_Elements_List_Contents(x); SDL_ListClear(&x)
 
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

SDL_Toolkit_کړکۍ_X11 *X11_Toolkit_Create_کړکۍ_Struct(SDL_کړکۍ *پلار, SDL_Toolkit_کړکۍ_X11 *tkparent, SDL_Toolkit_کړکۍ_ډېرپېښ_X11 ډېرپېښ, ثابت SDL_پیغام_Box_Color *colorhints, bool create_new_display)
{
    SDL_Toolkit_کړکۍ_X11 *کړکۍ;
    صحيح i;
#که_تعریف_شوی SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#د_که_پای
    #تعریف_کړه ErrorFreeRetNull(x, y) SDL_سېټ_Error(x); SDL_free(y); أرجع عدم
    #تعریف_کړه ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_سېټ_Error(x, y); SDL_free(z); أرجع عدم

    إذا (!SDL_X11_بارول_Symbols()) {
        أرجع عدم;
    }

    // This code could get called from multiple threads maybe?
    X11_XInit_تارونه();

    کړکۍ = (SDL_Toolkit_کړکۍ_X11 *)SDL_malloc(حجم(SDL_Toolkit_کړکۍ_X11));
    إذا (!کړکۍ) {
        SDL_سېټ_Error("Unable to allocate toolkit window structure");
        أرجع عدم;
    }

    کړکۍ->ډېرپېښ = ډېرپېښ;
    کړکۍ->tk_پلار = tkparent;

#إذا SDL_سېټ_LOCALE
    إذا (ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_DIALOG) {
        کړکۍ->origlocale = setlocale(LC_ALL, عدم);
        إذا (کړکۍ->origlocale) {
            کړکۍ->origlocale = SDL_strdup(کړکۍ->origlocale);
            إذا (!کړکۍ->origlocale) {
                SDL_free(کړکۍ);
                أرجع عدم;
            }
            (فراغ)setlocale(LC_ALL, "");
        }
    }
#د_که_پای

    کړکۍ->پلار_device = عدم;
    إذا (create_new_display) {
        کړکۍ->display = X11_XOpenDisplay(عدم);
        کړکۍ->display_close = true;
        إذا (!کړکۍ->display) {
            ErrorFreeRetNull("Couldn't open X11 display", کړکۍ);
        }
    } وإلا {
        إذا (پلار) {
            کړکۍ->پلار_device = SDL_GetVideoDevice();
            کړکۍ->display = کړکۍ->پلار_device->دننی->display;
            کړکۍ->display_close = false;
        } وإلا إذا (tkparent) {
            کړکۍ->display = tkparent->display;
            کړکۍ->display_close = false;
        } وإلا {
            کړکۍ->display = X11_XOpenDisplay(عدم);
            کړکۍ->display_close = true;
            إذا (!کړکۍ->display) {
                ErrorFreeRetNull("Couldn't open X11 display", کړکۍ);
            }
        }
    }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XRANDR
    صحيح xrandr_event_بنسټ, xrandr_error_بنسټ;
    کړکۍ->xrandr = X11_XRRQueryExtension(کړکۍ->display, &xrandr_event_بنسټ, &xrandr_error_بنسټ);
#د_که_پای

#که_نه_تعریف_شوی NO_SHARED_حافظه
    کړکۍ->shm_pixmap = False;
    کړکۍ->shm = X11_XShmQueryExtension(کړکۍ->display) ? SDL_X11_HAVE_SHM : false;
    إذا (کړکۍ->shm) {
        صحيح major;
        صحيح minor;

        X11_XShm_Query_نسخه(کړکۍ->display, &major, &minor, &کړکۍ->shm_pixmap);
        إذا (کړکۍ->shm_pixmap) {
            إذا (X11_XShmPixmapFormat(کړکۍ->display) != ZPixmap) {
                کړکۍ->shm_pixmap = False;
            }
        }
    }
#د_که_پای

    /* Scale/Xsettings */
    کړکۍ->pixmap = false;
    کړکۍ->xsettings_لومړی_وخت = true;
    کړکۍ->xsettings = xsettings_client_new(کړکۍ->display, DefaultScreen(کړکۍ->display), X11Toolkit_SettingsNotify, عدم, کړکۍ);
    کړکۍ->xsettings_لومړی_وخت = false;
    کړکۍ->scale = X11_GetGlobalContentScale(کړکۍ->display, کړکۍ->xsettings);
    إذا (کړکۍ->scale < 1) {
        کړکۍ->scale = 1;
    }
    کړکۍ->iscale = (صحيح)SDL_ceilf(کړکۍ->scale);
    إذا (SDL_roundf(کړکۍ->scale) == کړکۍ->scale) {
        کړکۍ->scale = 0;
    }

    /* Fonts */
    X11_Toolkit_Init_کړکۍ_Fonts(کړکۍ);

    /* Color hints */
#که_تعریف_شوی SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    إذا (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#د_که_پای

    إذا (!colorhints) {
#که_تعریف_شوی SDL_USE_LIBDBUS
        بدل (theme) {
            حالة SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                اكسر;
#إذا 0
            حالة SDL_SYSTEM_THEME_LIGHT_لوړ_CONTRAST:
                colorhints = g_default_colors_light_لوړ_contrast;
                اكسر;
            حالة SDL_SYSTEM_THEME_DARK_لوړ_CONTRAST:
                colorhints = g_default_colors_dark_لوړ_contrast;
                اكسر;
#د_که_پای
            افتراضي:
                colorhints = g_default_colors;
        }
#وإلا
        colorhints = g_default_colors;
#د_که_پای
    }
    کړکۍ->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    لكل (i = 0; i < SDL_MESSAGEBOX_COLOR_شمېر; i++) {
        کړکۍ->xcolor[i].flags = DoRed|DoGreen|DoBlue;
        کړکۍ->xcolor[i].red = colorhints[i].r * 257;
        کړکۍ->xcolor[i].green = colorhints[i].g * 257;
        کړکۍ->xcolor[i].blue = colorhints[i].b * 257;
    }

    /* Generate bevel and pressed colors */
    کړکۍ->xcolor_bevel_l1.flags = DoRed|DoGreen|DoBlue;
    کړکۍ->xcolor_bevel_l1.red = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 12500, 0, 65535);
    کړکۍ->xcolor_bevel_l1.green = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 12500, 0, 65535);
    کړکۍ->xcolor_bevel_l1.blue = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 12500, 0, 65535);

    کړکۍ->xcolor_bevel_l2.flags = DoRed|DoGreen|DoBlue;
    کړکۍ->xcolor_bevel_l2.red = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 32500, 0, 65535);
    کړکۍ->xcolor_bevel_l2.green = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 32500, 0, 65535);
    کړکۍ->xcolor_bevel_l2.blue = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 32500, 0, 65535);

    کړکۍ->xcolor_bevel_d.flags = DoRed|DoGreen|DoBlue;
    کړکۍ->xcolor_bevel_d.red = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red - 22500, 0, 65535);
    کړکۍ->xcolor_bevel_d.green = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green - 22500, 0, 65535);
    کړکۍ->xcolor_bevel_d.blue = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue - 22500, 0, 65535);

    کړکۍ->xcolor_pressed.flags = DoRed|DoGreen|DoBlue;
    کړکۍ->xcolor_pressed.red = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].red - 12500, 0, 65535);
    کړکۍ->xcolor_pressed.green = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].green - 12500, 0, 65535);
    کړکۍ->xcolor_pressed.blue = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].blue - 12500, 0, 65535);

    کړکۍ->xcolor_disabled_متن.flags = DoRed|DoGreen|DoBlue;
    کړکۍ->xcolor_disabled_متن.red = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_متن].red + 19500, 0, 65535);
    کړکۍ->xcolor_disabled_متن.green = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_متن].green + 19500, 0, 65535);
    کړکۍ->xcolor_disabled_متن.blue = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_متن].blue + 19500, 0, 65535);

    /* Screen */
    کړکۍ->پلار = پلار;
    إذا (پلار) {
        SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_کړکۍ(پلار);
        کړکۍ->screen = displaydata->screen;
    } وإلا {
        کړکۍ->screen = DefaultScreen(کړکۍ->display);
    }

    /* Visuals */
    إذا (ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_ماشوم) {
        کړکۍ->visual = پلار->دننی->visual;
        کړکۍ->cmap = پلار->دننی->colormap;
        X11_GetVisualInfoFromVisual(کړکۍ->display, کړکۍ->visual, &کړکۍ->vi);
        کړکۍ->ژوروالی_2 = کړکۍ->vi.ژوروالی_2;
    } وإلا {
        کړکۍ->visual = DefaultVisual(کړکۍ->display, کړکۍ->screen);
        کړکۍ->cmap = DefaultColormap(کړکۍ->display, کړکۍ->screen);
        کړکۍ->ژوروالی_2 = Default_ژوروالی(کړکۍ->display, کړکۍ->screen);
        X11_GetVisualInfoFromVisual(کړکۍ->display, کړکۍ->visual, &کړکۍ->vi);
    }

    /* Allocate colors */
    لكل (i = 0; i < SDL_MESSAGEBOX_COLOR_شمېر; i++) {
        X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &کړکۍ->xcolor[i]);
    }
    X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &کړکۍ->xcolor_bevel_l1);
    X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &کړکۍ->xcolor_bevel_l2);
    X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &کړکۍ->xcolor_bevel_d);
    X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &کړکۍ->xcolor_pressed);
    X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &کړکۍ->xcolor_disabled_متن);

    /* Control list */
    کړکۍ->has_focus = false;
    کړکۍ->controls = عدم;
    کړکۍ->controls_sz = 0;
    کړکۍ->dyn_controls_sz = 0;
    کړکۍ->fiddled_control = عدم;
    کړکۍ->dyn_controls = عدم;

    /* Menu windows */
    کړکۍ->popup_windows = عدم;

    /* BIDI engine */
#که_تعریف_شوی HAVE_FRIBIDI_H
    کړکۍ->fribidi = SDL_FriBidi_Create();
#د_که_پای

#که_تعریف_شوی HAVE_LIBTHAI_H
    کړکۍ->th = SDL_LibThai_Create();
#د_که_پای
    
    /* Interface direction */
    کړکۍ->flip_interface = X11Toolkit_ShouldFlipUI();
    
    أرجع کړکۍ;
}

ساكن فراغ X11_Toolkit_جمع_کړه_Control_منزل_کړکۍ(SDL_Toolkit_کړکۍ_X11 *کړکۍ, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    کړکۍ->controls_sz++;
    إذا (کړکۍ->controls_sz == 1) {
        کړکۍ->controls = (بنية SDL_ToolkitControlX11 **)SDL_malloc(حجم(بنية SDL_ToolkitControlX11 *));
    } وإلا {
        کړکۍ->controls = (بنية SDL_ToolkitControlX11 **)SDL_realloc(کړکۍ->controls, حجم(بنية SDL_ToolkitControlX11 *) * کړکۍ->controls_sz);
    }
    کړکۍ->controls[کړکۍ->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    إذا (control->dynamic) {
        کړکۍ->dyn_controls_sz++;
        إذا (کړکۍ->dyn_controls_sz == 1) {
            کړکۍ->dyn_controls = (بنية SDL_ToolkitControlX11 **)SDL_malloc(حجم(بنية SDL_ToolkitControlX11 *));
        } وإلا {
            کړکۍ->dyn_controls = (بنية SDL_ToolkitControlX11 **)SDL_realloc(کړکۍ->dyn_controls, حجم(بنية SDL_ToolkitControlX11 *) * کړکۍ->dyn_controls_sz);
        }
        کړکۍ->dyn_controls[کړکۍ->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    إذا (control->selected) {
        کړکۍ->focused_control = control;
    }
}

bool X11_Toolkit_Create_کړکۍ_Res(SDL_Toolkit_کړکۍ_X11 *معلومات, صحيح w, صحيح h, صحيح cx, صحيح cy, حرف *title)
{
    صحيح x, y;
    XSizeHints *sizehints;
    XSet_کړکۍ_ځانګړتیاوې wnd_attr;
    Atom NET_WM_کړکۍ_TYPE, NET_WM_کړکۍ_TYPE_DIALOG, NET_WM_کړکۍ_TYPE_DROPDOWN_MENU, NET_WM_کړکۍ_TYPE_TOOLTIP;
    SDL_کړکۍ_معلومات *windowdata = عدم;
    Display *display = معلومات->display;
    XGCValues ctx_vals;
    کړکۍ_2 ریښه_win;
    کړکۍ_2 پلار_win;
    بینښه اوږد gcflags = GCForeground | GCBackground;
    بینښه اوږد valuemask;
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XRANDR
#که_تعریف_شوی XRANDR_DISABLED_BY_DEFAULT
    ثابت bool use_xrandr_by_default = false;
#وإلا
    ثابت bool use_xrandr_by_default = true;
#د_که_پای
#د_که_پای

    إذا (معلومات->scale == 0) {
        معلومات->کړکۍ_پلنوالی = w;
        معلومات->کړکۍ_لوړوالی = h;
    } وإلا {
        معلومات->کړکۍ_پلنوالی = SDL_lroundf((w/معلومات->iscale) * معلومات->scale);
        معلومات->کړکۍ_لوړوالی = SDL_lroundf((h/معلومات->iscale) * معلومات->scale);
        معلومات->pixmap_پلنوالی = w;
        معلومات->pixmap_لوړوالی = h;
        معلومات->pixmap = true;
    }

    إذا (معلومات->پلار) {
        windowdata = معلومات->پلار->دننی;
    }

    valuemask = CWEvent_ماسک | CWColormap;
    معلومات->event_ماسک = Exposure_ماسک |
                       Button_Press_ماسک | Button_Release_ماسک | کلی_Press_ماسک | کلی_Release_ماسک |
                       Structure_Notify_ماسک | Focus_Change_ماسک | اشاره_ګر_Motion_ماسک;
    wnd_attr.event_ماسک = معلومات->event_ماسک;
    wnd_attr.colormap = معلومات->cmap;
    إذا (معلومات->ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_MENU || معلومات->ډېرپېښ== SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    ریښه_win = ریښه_کړکۍ(display, معلومات->screen);
    إذا (معلومات->ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_ماشوم) {
        پلار_win = windowdata->xwindow;
    } وإلا {
        پلار_win = ریښه_win;
    }

    معلومات->کړکۍ = X11_XCreate_کړکۍ(
        display, پلار_win,
        0, 0,
        معلومات->کړکۍ_پلنوالی, معلومات->کړکۍ_لوړوالی,
        0, معلومات->ژوروالی_2, ننوت_Output, معلومات->visual,
        valuemask, &wnd_attr);
    إذا (معلومات->کړکۍ == None) {
        أرجع SDL_سېټ_Error("Couldn't create X window");
    }

    إذا (windowdata && معلومات->ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_DIALOG) {
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
        X11_XChangeProperty(display, معلومات->کړکۍ, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_ډېرپېښ_Replace, (بینښه حرف *)stateatoms, statecount);
    }

    إذا (windowdata && معلومات->ډېرپېښ != SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_ماشوم) {
        X11_XSetTransientForHint(display, معلومات->کړکۍ, windowdata->xwindow);
    }

    إذا (معلومات->tk_پلار) {
        X11_XSetTransientForHint(display, معلومات->کړکۍ, معلومات->tk_پلار->کړکۍ);
    }

    SDL_X11_سېټ_کړکۍ_Title(display, معلومات->کړکۍ, title);

    // Let the window manager the type of the window
    إذا (معلومات->ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_DIALOG) {
        NET_WM_کړکۍ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_کړکۍ_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, معلومات->کړکۍ, NET_WM_کړکۍ_TYPE, XA_ATOM, 32,
                            Prop_ډېرپېښ_Replace,
                            (بینښه حرف *)&NET_WM_کړکۍ_TYPE_DIALOG, 1);
    } وإلا إذا (معلومات->ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_MENU) {
        NET_WM_کړکۍ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_کړکۍ_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, معلومات->کړکۍ, NET_WM_کړکۍ_TYPE, XA_ATOM, 32,
                            Prop_ډېرپېښ_Replace,
                            (بینښه حرف *)&NET_WM_کړکۍ_TYPE_DROPDOWN_MENU, 1);
    } وإلا إذا (معلومات->ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_TOOLTIP) {
        NET_WM_کړکۍ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_کړکۍ_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, معلومات->کړکۍ, NET_WM_کړکۍ_TYPE, XA_ATOM, 32,
                            Prop_ډېرپېښ_Replace,
                            (بینښه حرف *)&NET_WM_کړکۍ_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    معلومات->wm_delete_پیغام = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, معلومات->کړکۍ, &معلومات->wm_delete_پیغام, 1);
    معلومات->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    إذا (معلومات->ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_MENU || معلومات->ډېرپېښ== SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_TOOLTIP) {
        x = cx;
        y = cy;
        اذهب MOVEWINDOW;
    }
    إذا (windowdata) {
        XWindow_ځانګړتیاوې attrib;
        کړکۍ_2 dummy;

        X11_XGet_کړکۍ_ځانګړتیاوې(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.پلنوالی - معلومات->کړکۍ_پلنوالی) / 2;
        y = attrib.y + (attrib.لوړوالی - معلومات->کړکۍ_لوړوالی) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, ریښه_کړکۍ(display, معلومات->screen), x, y, &x, &y, &dummy);
    } وإلا {
        ثابت SDL_VideoDevice *dev = SDL_GetVideoDevice();
        إذا (dev && dev->displays && dev->عدد_displays > 0) {
            ثابت SDL_VideoDisplay *dpy = dev->displays[0];
            ثابت SDL_Display_معلومات *dpydata = dpy->دننی;
            x = dpydata->x + ((dpy->current_ډېرپېښ->w - معلومات->کړکۍ_پلنوالی) / 2);
            y = dpydata->y + ((dpy->current_ډېرپېښ->h - معلومات->کړکۍ_لوړوالی) / 3);
        }
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XRANDR
        وإلا إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && معلومات->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_بهر;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, ریښه_win);
            إذا (!screen_res) {
                اذهب NOXRANDR;
            }

            default_بهر = X11_XRRGetOutputPrimary(display, ریښه_win);
            إذا (default_بهر != None) {
                XRROutputInfo *بهر_info;

                بهر_info = X11_XRRGetOutputInfo(display, screen_res, default_بهر);
                إذا (بهر_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(بهر_info);
                    اذهب FIRSTOUTPUTXRANDR;
                }

                إذا (بهر_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, بهر_info->crtc);
                } وإلا إذا (بهر_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, بهر_info->crtcs[0]);
                } وإلا {
                    crtc_info = عدم;
                }
                
                إذا (crtc_info) {
                    x = (crtc_info->پلنوالی - معلومات->کړکۍ_پلنوالی) / 2;
                    y = (crtc_info->لوړوالی - معلومات->کړکۍ_لوړوالی) / 3;
                    X11_XRRFreeOutputInfo(بهر_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } وإلا {
                    X11_XRRFreeOutputInfo(بهر_info);
                    اذهب NOXRANDR;
                }
            } وإلا {
                    FIRSTOUTPUTXRANDR:
                    إذا (screen_res->noutput > 0) {
                        XRROutputInfo *بهر_info;

                        بهر_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        إذا (!بهر_info) {
                            اذهب FIRSTCRTCXRANDR;
                        }

                        إذا (بهر_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, بهر_info->crtc);
                        } وإلا إذا (بهر_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, بهر_info->crtcs[0]);
                        } وإلا {
                            crtc_info = عدم;
                        }

                        إذا (!crtc_info) {
                            X11_XRRFreeOutputInfo(بهر_info);
                            اذهب FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->پلنوالی - معلومات->کړکۍ_پلنوالی) / 2;
                        y = (crtc_info->لوړوالی - معلومات->کړکۍ_لوړوالی) / 3;
                        X11_XRRFreeOutputInfo(بهر_info);
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
                        x = (crtc_info->پلنوالی - معلومات->کړکۍ_پلنوالی) / 2;
                        y = (crtc_info->لوړوالی - معلومات->کړکۍ_لوړوالی) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } وإلا {
                        X11_XRRFreeScreenResources(screen_res);
                        اذهب NOXRANDR;
                    }
            }
        }
#د_که_پای
        وإلا {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (Display_پلنوالی(display, معلومات->screen) - معلومات->کړکۍ_پلنوالی) / 2;
            y = (Display_لوړوالی(display, معلومات->screen) - معلومات->کړکۍ_لوړوالی) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMove_کړکۍ(display, معلومات->کړکۍ, x, y);
    معلومات->کړکۍ_x = x;
    معلومات->کړکۍ_y = y;

    sizehints = X11_XAlloc_اندازه_Hints();
    إذا (sizehints) {
        sizehints->flags = USPosition | USSize | PMax_اندازه | PMin_اندازه;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->پلنوالی = معلومات->کړکۍ_پلنوالی;
        sizehints->لوړوالی = معلومات->کړکۍ_لوړوالی;

        sizehints->min_پلنوالی_2 = sizehints->max_پلنوالی_2 = معلومات->کړکۍ_پلنوالی;
        sizehints->min_لوړوالی_2 = sizehints->max_لوړوالی_2 = معلومات->کړکۍ_لوړوالی;

        X11_XSetWMNormalHints(display, معلومات->کړکۍ, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, معلومات->کړکۍ);

    معلومات->drawable = معلومات->کړکۍ;
#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    إذا (SDL_X11_HAVE_XDBE && !معلومات->pixmap) {
        صحيح xdbe_major, xdbe_minor;
        إذا (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            معلومات->xdbe = true;
            معلومات->buf = X11_Xdbe_Allocate_شا_بفر_Name(display, معلومات->کړکۍ, XdbeUndefined);
            معلومات->drawable = معلومات->buf;
        } وإلا {
            معلومات->xdbe = false;
        }
    }
#د_که_پای

    X11_Toolkit_Init_کړکۍ_Pixmap(معلومات);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = معلومات->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = معلومات->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    إذا (!معلومات->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = معلومات->font_struct->fid;
    }
    معلومات->ctx = X11_XCreateGC(معلومات->display, معلومات->drawable, gcflags, &ctx_vals);
    إذا (معلومات->ctx == None) {
        أرجع SDL_سېټ_Error("Couldn't create graphics context");
    }

    معلومات->close = false;
    معلومات->کلی_control_esc = معلومات->کلی_control_enter = عدم;
    إذا (!معلومات->pixmap) {
        معلومات->ev_scale = معلومات->ev_iscale = 1;
    } وإلا {
        معلومات->ev_scale = معلومات->scale;
        معلومات->ev_iscale = معلومات->iscale;
    }

#إذا SDL_GRAB
    إذا (معلومات->ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_MENU || معلومات->ډېرپېښ== SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_TOOLTIP) {
        X11_XGrab_اشاره_ګر(display, معلومات->کړکۍ, False, Button_Press_ماسک | Button_Release_ماسک | اشاره_ګر_Motion_ماسک, Grab_ډېرپېښ_Async, Grab_ډېرپېښ_Async, None, None, Current_وخت);
        X11_XGrabKeyboard(display, معلومات->کړکۍ, False, Grab_ډېرپېښ_Async, Grab_ډېرپېښ_Async, Current_وخت);
    }
#د_که_پای

    أرجع true;
}

ساكن فراغ X11_Toolkit_Draw_کړکۍ(SDL_Toolkit_کړکۍ_X11 *معلومات) {
    SDL_Rect rect;
    صحيح i;

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && معلومات->xdbe && !معلومات->pixmap) {
        X11_XdbeBeginIdiom(معلومات->display);
    }
#د_که_پای

    X11_XSetForeground(معلومات->display, معلومات->ctx, معلومات->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    إذا (معلومات->pixmap) {
        X11_XFillRectangle(معلومات->display, معلومات->drawable, معلومات->ctx, 0, 0, معلومات->pixmap_پلنوالی, معلومات->pixmap_لوړوالی);
    } وإلا {
        X11_XFillRectangle(معلومات->display, معلومات->drawable, معلومات->ctx, 0, 0, معلومات->کړکۍ_پلنوالی, معلومات->کړکۍ_لوړوالی);
    }

    لكل (i = 0; i < معلومات->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = معلومات->controls[i];
        إذا (control) {
            إذا (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && معلومات->xdbe && !معلومات->pixmap) {
        Xdbe_بدلون_Info بدلون_info;
        بدلون_info.بدلون_کړکۍ = معلومات->کړکۍ;
        بدلون_info.بدلون_action = XdbeUndefined;
        X11_Xdbe_بدلون_Buffers(معلومات->display, &بدلون_info, 1);
        X11_Xdbe_پای_ټکی_Idiom(معلومات->display);
    }
#د_که_پای

    إذا (معلومات->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = معلومات->کړکۍ_پلنوالی;
        rect.h = معلومات->کړکۍ_لوړوالی;
#که_نه_تعریف_شوی NO_SHARED_حافظه
        إذا (معلومات->shm) {
            إذا (معلومات->shm_pixmap) {
                X11_XFlush(معلومات->display);
                X11_XSync(معلومات->display, false);
                scale_surface = SDL_CreateSurfaceFrom(معلومات->pixmap_پلنوالی, معلومات->pixmap_لوړوالی, X11_GetPixelFormatFromVisualInfo(معلومات->display, &معلومات->vi), معلومات->shm_info.shmaddr, معلومات->shm_بایټونه_فی_کرښه);
                SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_خطي);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(معلومات->display, معلومات->drawable, معلومات->کړکۍ, معلومات->ctx, 0, 0, معلومات->کړکۍ_پلنوالی, معلومات->کړکۍ_لوړوالی, 0, 0);
            } وإلا {
                X11_XShmGetImage(معلومات->display, معلومات->drawable, معلومات->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(معلومات->pixmap_پلنوالی, معلومات->pixmap_لوړوالی, X11_GetPixelFormatFromVisualInfo(معلومات->display, &معلومات->vi), معلومات->image->معلومات, معلومات->image->بایټونه_فی_کرښه);
                SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_خطي);
                X11_XShmPutImage(معلومات->display, معلومات->کړکۍ, معلومات->ctx, معلومات->image, 0, 0, 0, 0, معلومات->کړکۍ_پلنوالی, معلومات->کړکۍ_لوړوالی, False);
            }
        } وإلا
#د_که_پای
        {
            XImage *image;

            image = X11_XGetImage(معلومات->display, معلومات->drawable, 0, 0 , معلومات->pixmap_پلنوالی, معلومات->pixmap_لوړوالی, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(معلومات->pixmap_پلنوالی, معلومات->pixmap_لوړوالی, X11_GetPixelFormatFromVisualInfo(معلومات->display, &معلومات->vi), image->معلومات, image->بایټونه_فی_کرښه);
            SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_خطي);
            X11_XPutImage(معلومات->display, معلومات->کړکۍ, معلومات->ctx, image, 0, 0, 0, 0, معلومات->کړکۍ_پلنوالی, معلومات->کړکۍ_لوړوالی);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(معلومات->display);
}

ساكن SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_Toolkit_کړکۍ_X11 *معلومات, صحيح x, صحيح y)
{
    صحيح i;

    لكل (i = 0; i < معلومات->controls_sz; i++) {
        SDL_Rect *rect = &معلومات->controls[i]->rect;
        إذا ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            أرجع معلومات->controls[i];
        }
    }

    أرجع عدم;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
ساكن Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_Toolkit_کړکۍ_X11 *معلومات = (SDL_Toolkit_کړکۍ_X11 *)arg;

    إذا (event->xany.display != معلومات->display) {
        أرجع False;
    }

    إذا (event->xany.کړکۍ == معلومات->کړکۍ) {
        أرجع True;
    }

    أرجع False;
}

فراغ X11_Toolkit_Process_کړکۍ_Events(SDL_Toolkit_کړکۍ_X11 *معلومات, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    إذا ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        أرجع;
    }

    معلومات->draw = false;
    معلومات->e = e;

    بدل (e->type) {
        حالة Expose:
            معلومات->draw = true;
            اكسر;
        حالة Client_پیغام:
            إذا (e->xclient.پیغام_type == معلومات->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.معلومات.l[0] == معلومات->wm_delete_پیغام) {
                معلومات->close = true;
            }
            اكسر;
        حالة Focus_دننه:
            معلومات->has_focus = true;
            اكسر;
        حالة Focus_بهر:
            معلومات->has_focus = false;
            إذا (معلومات->fiddled_control) {
                معلومات->fiddled_control->selected = false;
            }
            معلومات->fiddled_control = عدم;
            لكل (معلومات->ev_i = 0; معلومات->ev_i < معلومات->controls_sz; معلومات->ev_i++) {
                معلومات->controls[معلومات->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_نورمال;
            }
            اكسر;
        حالة MotionNotify:
            إذا (معلومات->has_focus) {
                معلومات->پخوانی_control = معلومات->fiddled_control;
                معلومات->fiddled_control = X11Toolkit_GetControlMouseIsOn(معلومات, SDL_lroundf((e->xbutton.x/ معلومات->ev_scale)* معلومات->ev_iscale), SDL_lroundf((e->xbutton.y/ معلومات->ev_scale)* معلومات->ev_iscale));
                إذا (معلومات->پخوانی_control) {
                    معلومات->پخوانی_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نورمال;
                    إذا (معلومات->پخوانی_control->func_on_state_change) {
                        معلومات->پخوانی_control->func_on_state_change(معلومات->پخوانی_control);
                    }
                    معلومات->draw = true;
                }
                إذا (معلومات->fiddled_control) {
                    إذا (معلومات->fiddled_control->dynamic) {
                        معلومات->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        إذا (معلومات->fiddled_control->func_on_state_change) {
                            معلومات->fiddled_control->func_on_state_change(معلومات->fiddled_control);
                        }
                        معلومات->draw = true;
                    } وإلا {
                        معلومات->fiddled_control = عدم;
                    }
                }
            }
            اكسر;
        حالة ButtonPress:
            معلومات->پخوانی_control = معلومات->fiddled_control;
            إذا (معلومات->پخوانی_control) {
                معلومات->پخوانی_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نورمال;
                إذا (معلومات->پخوانی_control->func_on_state_change) {
                    معلومات->پخوانی_control->func_on_state_change(معلومات->پخوانی_control);
                }
                معلومات->draw = true;
            }
            إذا (e->xbutton.button == Button1) {
                معلومات->fiddled_control = X11Toolkit_GetControlMouseIsOn(معلومات, SDL_lroundf((e->xbutton.x/ معلومات->ev_scale)* معلومات->ev_iscale), SDL_lroundf((e->xbutton.y/ معلومات->ev_scale)* معلومات->ev_iscale));
                إذا (معلومات->fiddled_control) {
                    معلومات->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    إذا (معلومات->fiddled_control->func_on_state_change) {
                        معلومات->fiddled_control->func_on_state_change(معلومات->fiddled_control);
                    }
                    معلومات->draw = true;
                }
            }
            اكسر;
        حالة ButtonRelease:
            إذا (معلومات->ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_MENU || معلومات->ډېرپېښ== SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_TOOLTIP) {
                صحيح cx;
                صحيح cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                إذا (cy < 0 || cx < 0) {
                    معلومات->close = true;
                }

                إذا (cy > معلومات->کړکۍ_لوړوالی || cx > معلومات->کړکۍ_پلنوالی) {
                    معلومات->close = true;
                }
            }

            إذا ((e->xbutton.button == Button1) && (معلومات->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(معلومات, SDL_lroundf((e->xbutton.x/ معلومات->ev_scale)* معلومات->ev_iscale), SDL_lroundf((e->xbutton.y/ معلومات->ev_scale)* معلومات->ev_iscale));
                إذا (معلومات->fiddled_control == control) {
                    معلومات->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    إذا (معلومات->fiddled_control->func_on_state_change) {
                        معلومات->fiddled_control->func_on_state_change(معلومات->fiddled_control);
                    }
                    معلومات->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نورمال;
                    معلومات->draw = true;
                }
            }
            اكسر;
        حالة کلی_Press:
            معلومات->وروستی_کلی_pressed = X11_XLookupKeysym(&e->xkey, 0);

            إذا (معلومات->وروستی_کلی_pressed == XK_Escape) {
                لكل (معلومات->ev_i = 0; معلومات->ev_i < معلومات->controls_sz; معلومات->ev_i++) {
                    إذا(معلومات->controls[معلومات->ev_i]->is_default_esc) {
                        معلومات->controls[معلومات->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        معلومات->draw = true;
                        معلومات->کلی_control_esc = معلومات->controls[معلومات->ev_i];
                    }
                }
            } وإلا إذا ((معلومات->وروستی_کلی_pressed == XK_Return) || (معلومات->وروستی_کلی_pressed == XK_KP_Enter)) {
                لكل (معلومات->ev_i = 0; معلومات->ev_i < معلومات->controls_sz; معلومات->ev_i++) {
                    إذا(معلومات->controls[معلومات->ev_i]->selected) {
                        معلومات->controls[معلومات->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        معلومات->draw = true;
                        معلومات->کلی_control_enter = معلومات->controls[معلومات->ev_i];
                    }
                }
            }
            اكسر;
        حالة کلی_Release:
        {
            کلی_Sym کلی = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            إذا (کلی != معلومات->وروستی_کلی_pressed) {
                اكسر;
            }

            إذا (کلی == XK_Escape) {
                إذا (معلومات->کلی_control_esc) {
                    إذا (معلومات->کلی_control_esc->func_on_state_change) {
                        معلومات->کلی_control_esc->func_on_state_change(معلومات->کلی_control_esc);
                    }
                }
            } وإلا إذا ((کلی == XK_Return) || (کلی == XK_KP_Enter)) {
                إذا (معلومات->کلی_control_enter) {
                    إذا (معلومات->کلی_control_enter->func_on_state_change) {
                        معلومات->کلی_control_enter->func_on_state_change(معلومات->کلی_control_enter);
                    }
                }
            } وإلا إذا (کلی == XK_Tab || کلی == XK_کیڼ || کلی == XK_ښی) {
                إذا (معلومات->focused_control) {
                    معلومات->focused_control->selected = false;
                }
                معلومات->draw = true;
                لكل (معلومات->ev_i = 0; معلومات->ev_i < معلومات->dyn_controls_sz; معلومات->ev_i++) {
                    إذا (معلومات->dyn_controls[معلومات->ev_i] == معلومات->focused_control) {
                        صحيح بل_شاخص;

                        إذا (کلی == XK_کیڼ) {
                            بل_شاخص = معلومات->ev_i - 1;
                        } وإلا {
                            بل_شاخص = معلومات->ev_i + 1;
                        }
                        إذا ((بل_شاخص >= معلومات->dyn_controls_sz) || (بل_شاخص < 0)) {
                            إذا (کلی == XK_ښی || کلی == XK_کیڼ) {
                                بل_شاخص = معلومات->ev_i;
                            } وإلا {
                                بل_شاخص = 0;
                            }
                        }
                        معلومات->focused_control = معلومات->dyn_controls[بل_شاخص];
                        معلومات->focused_control->selected = true;
                        اكسر;
                    }
                }
            }
            اكسر;
        }
    }

    إذا (معلومات->draw) {
        X11_Toolkit_Draw_کړکۍ(معلومات);
    }
}

فراغ X11_Toolkit_Do_کړکۍ_Event_Loop(SDL_Toolkit_کړکۍ_X11 *معلومات) {
   طالما (!معلومات->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(معلومات->display, &e);
        إذا (معلومات->xsettings) {
            xsettings_client_process_event(معلومات->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(معلومات->display, &e, X11Toolkit_EventTest, (XPointer)معلومات);
        X11_Toolkit_Process_کړکۍ_Events(معلومات, &e);
    }
}


فراغ X11_Toolkit_Resize_کړکۍ(SDL_Toolkit_کړکۍ_X11 *معلومات, صحيح w, صحيح h) {
    إذا (!معلومات->pixmap) {
        معلومات->کړکۍ_پلنوالی = w;
        معلومات->کړکۍ_لوړوالی = h;
    } وإلا {
        معلومات->کړکۍ_پلنوالی = SDL_lroundf((w/معلومات->iscale) * معلومات->scale);
        معلومات->کړکۍ_لوړوالی = SDL_lroundf((h/معلومات->iscale) * معلومات->scale);
        معلومات->pixmap_پلنوالی = w;
        معلومات->pixmap_لوړوالی = h;
        X11_XFreePixmap(معلومات->display, معلومات->drawable);
        X11_Toolkit_Init_کړکۍ_Pixmap(معلومات);
    }

    X11_XResize_کړکۍ(معلومات->display, معلومات->کړکۍ, معلومات->کړکۍ_پلنوالی, معلومات->کړکۍ_لوړوالی);
}

ساكن فراغ X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->کړکۍ->display, icon_control->icon_char_font);
    SDL_free(control);
}

ساكن فراغ X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->کړکۍ->iscale;
    control->rect.h -= 2 * control->کړکۍ->iscale;
    X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx, control->rect.x + (2 * control->کړکۍ->iscale), control->rect.y + (2* control->کړکۍ->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    بدل (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        حالة SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx, control->rect.x+(1* control->کړکۍ->iscale), control->rect.y+(1* control->کړکۍ->iscale), control->rect.w-(2* control->کړکۍ->iscale), control->rect.h-(2* control->کړکۍ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, icon_control->xcolor_white.pixel);
                اكسر;
        حالة SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx, control->rect.x+(1* control->کړکۍ->iscale), control->rect.y+(1* control->کړکۍ->iscale), control->rect.w-(2* control->کړکۍ->iscale), control->rect.h-(2* control->کړکۍ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, icon_control->xcolor_black.pixel);
                اكسر;
        حالة SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx, control->rect.x+(1* control->کړکۍ->iscale), control->rect.y+(1* control->کړکۍ->iscale), control->rect.w-(2* control->کړکۍ->iscale), control->rect.h-(2* control->کړکۍ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, icon_control->xcolor_white.pixel);
                اكسر;
    }
    X11_XSetFont(control->کړکۍ->display, control->کړکۍ->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    إذا (!control->کړکۍ->utf8) {
        X11_XSetFont(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->font_struct->fid);
    }

    control->rect.w += 2 * control->کړکۍ->iscale;
    control->rect.h += 2 * control->کړکۍ->iscale;
}

ساكن فراغ X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *بنسټ_control) {
    SDL_ToolkitIconControlX11 *control;
    صحيح icon_char_w;
    صحيح icon_wh;

    control = (SDL_ToolkitIconControlX11 *)بنسټ_control;
    X11_Toolkit_Get_متن_پلنوالی_لوړوالی_For_Font(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, عدم);
    بنسټ_control->rect.w = icon_char_w;
    بنسټ_control->rect.h = control->icon_char_h;
    icon_wh = SDL_max(icon_char_w, control->icon_char_h) + SDL_TOOLKIT_X11_ELEMENT_PADDING * 2 * بنسټ_control->کړکۍ->iscale;
    بنسټ_control->rect.w = icon_wh;
    بنسټ_control->rect.h = icon_wh;
    بنسټ_control->rect.y = 0;
    بنسټ_control->rect.x = 0;
    control->icon_char_y = control->icon_char_a + (بنسټ_control->rect.h - control->icon_char_h)/2;
    control->icon_char_x = (بنسټ_control->rect.w - icon_char_w)/2;
    بنسټ_control->rect.w += 2 * بنسټ_control->کړکۍ->iscale;
    بنسټ_control->rect.h += 2 * بنسټ_control->کړکۍ->iscale;
}

ساكن فراغ X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *بنسټ_control) {
    SDL_ToolkitIconControlX11 *control;
    حرف *font;

    control = (SDL_ToolkitIconControlX11 *)بنسټ_control;
    X11_XFreeFont(بنسټ_control->کړکۍ->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_اندازه * بنسټ_control->کړکۍ->iscale);
    control->icon_char_font = X11_XLoadQueryFont(بنسټ_control->کړکۍ->display, font);
    SDL_free(font);
    إذا (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_اندازه * بنسټ_control->کړکۍ->iscale);
        control->icon_char_font = X11_XLoadQueryFont(بنسټ_control->کړکۍ->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_کړکۍ_X11 *کړکۍ, SDL_پیغام_Box_Flags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *بنسټ_control;
    حرف *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(حجم(SDL_ToolkitIconControlX11));
    بنسټ_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_سېټ_Error("Unable to allocate icon control structure");
        أرجع عدم;
    }

    /* Fill out struct */
    بنسټ_control->کړکۍ = کړکۍ;
    بنسټ_control->func_draw = X11Toolkit_DrawIconControl;
    بنسټ_control->func_free = X11Toolkit_DestroyIconControl;
    بنسټ_control->func_on_state_change = عدم;
    بنسټ_control->func_calc_اندازه = X11Toolkit_CalculateIconControl;
    بنسټ_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    بنسټ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نورمال;
    بنسټ_control->selected = false;
    بنسټ_control->dynamic = false;
    بنسټ_control->is_default_enter = false;
    بنسټ_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_اندازه * کړکۍ->iscale);
    control->icon_char_font = X11_XLoadQueryFont(کړکۍ->display, font);
    SDL_free(font);
    إذا (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_اندازه * کړکۍ->iscale);
        control->icon_char_font = X11_XLoadQueryFont(کړکۍ->display, font);
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
        X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &control->xcolor_white);
        X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &control->xcolor_red);
        X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &control->xcolor_red_darker);
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
        X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &control->xcolor_black);
        X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &control->xcolor_yellow);
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
        X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &control->xcolor_white);
        X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &control->xcolor_blue);
        اكسر;
    افتراضي:
        X11_XFreeFont(کړکۍ->display, control->icon_char_font);
        SDL_free(control);
        أرجع عدم;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    إذا (کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } وإلا إذا (کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.red = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    إذا (کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } وإلا إذا (کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.green = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    إذا (کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } وإلا إذا (کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.blue = SDL_clamp(کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(کړکۍ->display, کړکۍ->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(بنسټ_control);

    X11_Toolkit_جمع_کړه_Control_منزل_کړکۍ(کړکۍ, بنسټ_control);
    أرجع بنسټ_control;
}

bool X11_Toolkit_Notify_Control_د_اندازه_Change(SDL_ToolkitControlX11 *control) {
    إذا (control->func_calc_اندازه) {
        control->func_calc_اندازه(control);
        أرجع true;
    } وإلا {
        أرجع false;
    }
}

ساكن فراغ X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11_Toolkit_Get_متن_Elements_Rect(button_control->متن, &button_control->متن_rect);
    إذا (control->do_اندازه) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->کړکۍ->iscale + button_control->متن_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->کړکۍ->iscale + button_control->متن_rect.h;
    }
    button_control->متن_rect.x = (control->rect.w - button_control->متن_rect.w)/2;
    button_control->متن_rect.y = (control->rect.h - button_control->متن_rect.h)/2;
}


ساكن فراغ X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    /* Draw bevel */
    إذا (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
            X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor_bevel_d.pixel);
            X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

            X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor_bevel_l2.pixel);
            X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - (1* control->کړکۍ->iscale), control->rect.h - (1* control->کړکۍ->iscale));

            X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor_bevel_l1.pixel);
            X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x + 1 * control->کړکۍ->iscale, control->rect.y + 1 * control->کړکۍ->iscale,
                                   control->rect.w - 3 * control->کړکۍ->iscale, control->rect.h - 2 * control->کړکۍ->iscale);

            X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
            X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                               control->rect.x + 1 * control->کړکۍ->iscale, control->rect.y + 1 * control->کړکۍ->iscale,
                               control->rect.w - 3 * control->کړکۍ->iscale, control->rect.h - 3 * control->کړکۍ->iscale);

            X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor_pressed.pixel);
            X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                               control->rect.x + 2 * control->کړکۍ->iscale, control->rect.y + 2 * control->کړکۍ->iscale,
                               control->rect.w - 4 * control->کړکۍ->iscale, control->rect.h - 4 * control->کړکۍ->iscale);
        } وإلا {
            إذا (control->selected) {
                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x + 1 * control->کړکۍ->iscale, control->rect.y + 1 * control->کړکۍ->iscale,
                                   control->rect.w - 3 * control->کړکۍ->iscale, control->rect.h - 3 * control->کړکۍ->iscale);

                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x + 2 * control->کړکۍ->iscale, control->rect.y + 2 * control->کړکۍ->iscale,
                                   control->rect.w - 4 * control->کړکۍ->iscale, control->rect.h - 4 * control->کړکۍ->iscale);

                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x + 2 * control->کړکۍ->iscale, control->rect.y + 2 * control->کړکۍ->iscale,
                                   control->rect.w - 5 * control->کړکۍ->iscale, control->rect.h - 5 * control->کړکۍ->iscale);

                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x + 3 * control->کړکۍ->iscale, control->rect.y + 3 * control->کړکۍ->iscale,
                                   control->rect.w - 6 * control->کړکۍ->iscale, control->rect.h - 6 * control->کړکۍ->iscale);
            } وإلا {
                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - 1 * control->کړکۍ->iscale, control->rect.h - 1 * control->کړکۍ->iscale);

                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x + 1 * control->کړکۍ->iscale, control->rect.y + 1 * control->کړکۍ->iscale,
                                   control->rect.w - 2 * control->کړکۍ->iscale, control->rect.h - 2 * control->کړکۍ->iscale);

                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x + 1 * control->کړکۍ->iscale, control->rect.y + 1 * control->کړکۍ->iscale,
                                   control->rect.w - 3 * control->کړکۍ->iscale, control->rect.h - 3 * control->کړکۍ->iscale);

                X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->کړکۍ->display, control->کړکۍ->drawable, control->کړکۍ->ctx,
                                   control->rect.x + 2 * control->کړکۍ->iscale, control->rect.y + 2 * control->کړکۍ->iscale,
                                   control->rect.w - 4 * control->کړکۍ->iscale, control->rect.h - 4 * control->کړکۍ->iscale);
            }
        }

    X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    X11_Toolkit_Draw_متن_Elements(control->کړکۍ, button_control->متن, control->rect.x + button_control->متن_rect.x, control->rect.y + button_control->متن_rect.y);
}

ساكن فراغ X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    إذا (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_معلومات);
    }
}

ساكن فراغ X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_Toolkit_Free_متن_Elements(button_control->متن);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_کړکۍ_X11 *کړکۍ, ثابت SDL_پیغام_Box_Button_معلومات *معلومات) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *بنسټ_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(حجم(SDL_ToolkitButtonControlX11));
    بنسټ_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_سېټ_Error("Unable to allocate button control structure");
        أرجع عدم;
    }
    بنسټ_control->کړکۍ = کړکۍ;
    بنسټ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نورمال;
    بنسټ_control->func_calc_اندازه = X11Toolkit_CalculateButtonControl;
    بنسټ_control->func_draw = X11Toolkit_DrawButtonControl;
    بنسټ_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    بنسټ_control->func_free = X11Toolkit_DestroyButtonControl;
    بنسټ_control->func_on_scale_change = عدم;
    بنسټ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نورمال;
    بنسټ_control->selected = false;
    بنسټ_control->dynamic = true;
    بنسټ_control->is_default_enter = false;
    بنسټ_control->is_default_esc = false;
    إذا (معلومات->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        بنسټ_control->is_default_esc = true;
    }
    إذا (معلومات->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        بنسټ_control->is_default_enter = true;
        بنسټ_control->selected = true;
    }
    control->cb = عدم;
    control->معلومات = معلومات;
#که_تعریف_شوی HAVE_FRIBIDI_H
    control->متن = X11_Toolkit_Make_متن_Elements(بنسټ_control->کړکۍ, (حرف *)control->معلومات->متن, SDL_strlen(control->معلومات->متن), عدم);
#وإلا 
    control->متن = X11_Toolkit_Make_متن_Elements(بنسټ_control->کړکۍ, (حرف *)control->معلومات->متن, SDL_strlen(control->معلومات->متن));
#د_که_پای
    X11_Toolkit_Shape_متن_Elements(بنسټ_control->کړکۍ, control->متن);
    
    بنسټ_control->do_اندازه = true;
    X11Toolkit_CalculateButtonControl(بنسټ_control);
    بنسټ_control->do_اندازه = false;

    X11_Toolkit_جمع_کړه_Control_منزل_کړکۍ(کړکۍ, بنسټ_control);
    أرجع بنسټ_control;
}

فراغ X11_Toolkit_ثبتوونکی_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, فراغ *معلومات, فراغ (*cb)(بنية SDL_ToolkitControlX11 *, فراغ *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_معلومات = معلومات;
    button_control->cb = cb;
}

ثابت SDL_پیغام_Box_Button_معلومات *X11_Toolkit_Get_Button_Control_معلومات(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    أرجع button_control->معلومات;
}

فراغ X11_Toolkit_Destroy_کړکۍ(SDL_Toolkit_کړکۍ_X11 *معلومات) {
    صحيح i;

    إذا (!معلومات) {
        أرجع;
    }

#إذا SDL_GRAB
    إذا (معلومات->ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_MENU || معلومات->ډېرپېښ== SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_TOOLTIP) {
        X11_XUngrab_اشاره_ګر(معلومات->display, Current_وخت);
        X11_XUngrabKeyboard(معلومات->display, Current_وخت);
    }
#د_که_پای

    لكل (i = 0; i < معلومات->controls_sz; i++) {
        إذا (معلومات->controls[i]->func_free) {
            معلومات->controls[i]->func_free(معلومات->controls[i]);
        }
    }
    SDL_free(معلومات->controls);
    SDL_free(معلومات->dyn_controls);

    إذا (معلومات->popup_windows) {
        SDL_ListClear(&معلومات->popup_windows);
    }

    إذا (معلومات->pixmap) {
        X11_XFreePixmap(معلومات->display, معلومات->drawable);
    }

#که_نه_تعریف_شوی NO_SHARED_حافظه
    إذا (معلومات->pixmap && معلومات->shm) {
        X11_XShmDetach(معلومات->display, &معلومات->shm_info);
        إذا (!معلومات->shm_pixmap) {
            XDestroyImage(معلومات->image);
        }
        shmdt(معلومات->shm_info.shmaddr);
    }
#د_که_پای

#که_تعریف_شوی X_HAVE_UTF8_STRING
    إذا (معلومات->font_سېټ) {
        X11_XFree_Font_سېټ(معلومات->display, معلومات->font_سېټ);
        معلومات->font_سېټ = عدم;
    }
#د_که_پای

    إذا (معلومات->font_struct) {
        X11_XFreeFont(معلومات->display, معلومات->font_struct);
        معلومات->font_struct = عدم;
    }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && معلومات->xdbe && !معلومات->pixmap) {
        X11_Xdbe_Deallocate_شا_بفر_Name(معلومات->display, معلومات->buf);
    }
#د_که_پای

    إذا (معلومات->xsettings) {
        xsettings_client_destroy(معلومات->xsettings);
    }

    X11_XFreeGC(معلومات->display, معلومات->ctx);

    إذا (معلومات->display) {
        إذا (معلومات->کړکۍ != None) {
            X11_XWithdraw_کړکۍ(معلومات->display, معلومات->کړکۍ, معلومات->screen);
            X11_XDestroy_کړکۍ(معلومات->display, معلومات->کړکۍ);
            معلومات->کړکۍ = None;
        }

        إذا (معلومات->display_close) {
            X11_XCloseDisplay(معلومات->display);
        }
        معلومات->display = عدم;
    }

#إذا SDL_سېټ_LOCALE
    إذا (معلومات->origlocale && (معلومات->ډېرپېښ == SDL_TOOLKIT_کړکۍ_ډېرپېښ_X11_DIALOG)) {
        (فراغ)setlocale(LC_ALL, معلومات->origlocale);
        SDL_free(معلومات->origlocale);
    }
#د_که_پای

#که_تعریف_شوی HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(معلومات->fribidi);
#د_که_پای

#که_تعریف_شوی HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(معلومات->th);
#د_که_پای

    SDL_free(معلومات);
}

ساكن صحيح X11_Toolkit_شمېر_کرښې_د_متن(ثابت حرف *متن)
{
    صحيح پایله = 0;
    طالما (متن && *متن) {
        ثابت حرف *lf = SDL_strchr(متن, '\n');
        پایله++; // even without an endline, this counts as a line.
        متن = lf ? lf + 1 : عدم;
    }
    أرجع پایله;
}

ساكن فراغ X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحيح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->کړکۍ->display, control->کړکۍ->ctx, control->کړکۍ->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    لكل (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Draw_متن_Elements(control->کړکۍ, label_control->کرښې[i].متن, control->rect.x + label_control->کرښې[i].rect.x, control->rect.y + label_control->کرښې[i].rect.y);
    }
}

ساكن فراغ X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحيح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    لكل (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Free_متن_Elements(label_control->کرښې[i].متن);
    }
    SDL_free(label_control->کرښې);
    SDL_free(label_control);
}

ساكن فراغ X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *بنسټ_control) {
    SDL_ToolkitLabelControlX11 *control;
    صحيح i;

    control = (SDL_ToolkitLabelControlX11 *)بنسټ_control;
    
    إذا (بنسټ_control->do_اندازه) {
        بنسټ_control->rect.w = 0;
        بنسټ_control->rect.h = 0;
    }
    
    لكل (i = 0; i < control->sz; i++) {
        صحيح font_h;
        
        font_h = X11_Toolkit_Get_متن_Elements_Rect(control->کرښې[i].متن, &control->کرښې[i].rect);
        
        إذا (بنسټ_control->do_اندازه) {
            بنسټ_control->rect.w = SDL_max(بنسټ_control->rect.w, control->کرښې[i].rect.w);
        }
        
        إذا (i > 0) {
            control->کرښې[i].rect.y = font_h + control->کرښې[i - 1].rect.y;
        } وإلا {
            control->کرښې[i].rect.y = 0;
        }
    }

#که_تعریف_شوی HAVE_FRIBIDI_H
    إذا (بنسټ_control->کړکۍ->fribidi) {
        FriBidiParType لومړی_ndn_dir;
        صحيح وروستی_ndn;
    
        لومړی_ndn_dir = FRIBIDI_PAR_LTR;
        لكل (i = 0; i < control->sz; i++) {
            إذا (control->کرښې[i].par != FRIBIDI_PAR_ON) {
                لومړی_ndn_dir = control->کرښې[i].par;
            }
        }

        وروستی_ndn = -1;
        لكل (i = 0; i < control->sz; i++) {
            بدل (control->کرښې[i].par) {
                حالة FRIBIDI_PAR_LTR:
                    control->کرښې[i].rect.x = 0;
                    وروستی_ndn = i;
                    اكسر;
                حالة FRIBIDI_PAR_RTL:
                    control->کرښې[i].rect.x = بنسټ_control->rect.w - control->کرښې[i].rect.w;
                    وروستی_ndn = i;
                    اكسر;
                افتراضي:
                    إذا (وروستی_ndn != -1) {
                        إذا (control->کرښې[وروستی_ndn].par == FRIBIDI_PAR_RTL) {
                            control->کرښې[i].rect.x = بنسټ_control->rect.w - control->کرښې[i].rect.w;
                        } وإلا {
                            control->کرښې[i].rect.x = 0;
                        }
                    } وإلا {
                        إذا (لومړی_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->کرښې[i].rect.x = بنسټ_control->rect.w - control->کرښې[i].rect.w;
                        } وإلا {
                            control->کرښې[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#د_که_پای
    
    إذا (بنسټ_control->do_اندازه && control->sz) {
        بنسټ_control->rect.h = control->کرښې[control->sz - 1].rect.y + control->کرښې[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_کړکۍ_X11 *کړکۍ, حرف *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *بنسټ_control;
    صحيح i;
    
    إذا (!utf8) {
        أرجع عدم;
    }
 
    إذا (!SDL_strcmp(utf8, "")) {
        أرجع عدم;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(حجم(SDL_ToolkitLabelControlX11));
    بنسټ_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_سېټ_Error("Unable to allocate label control structure");
        أرجع عدم;
    }
    بنسټ_control->کړکۍ = کړکۍ;
    بنسټ_control->func_draw = X11Toolkit_DrawLabelControl;
    بنسټ_control->func_on_state_change = عدم;
    بنسټ_control->func_calc_اندازه = X11Toolkit_CalculateLabelControl;
    بنسټ_control->func_free  = X11Toolkit_DestroyLabelControl;
    بنسټ_control->func_on_scale_change = عدم;
    بنسټ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نورمال;
    بنسټ_control->selected = false;
    بنسټ_control->dynamic = false;
    بنسټ_control->rect.w = 0;
    بنسټ_control->rect.h = 0;
    بنسټ_control->is_default_enter = false;
    بنسټ_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_شمېر_کرښې_د_متن(utf8);
    control->کرښې = SDL_calloc(control->sz, حجم(SDL_Toolkit_Label_Control_کرښه_X11));
    لكل (i = 0; i < control->sz; i++) {
        ثابت حرف *lf = SDL_strchr(utf8, '\n');
        ثابت صحيح اوږدتیا = lf ? (lf - utf8) : SDL_strlen(utf8);
        صحيح sz;
        
        sz = اوږدتیا;
        إذا (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#که_تعریف_شوی HAVE_FRIBIDI_H
        control->کرښې[i].متن = X11_Toolkit_Make_متن_Elements(بنسټ_control->کړکۍ, (حرف *)utf8, sz, &control->کرښې[i].par);
#وإلا 
        control->کرښې[i].متن = X11_Toolkit_Make_متن_Elements(بنسټ_control->کړکۍ, (حرف *)utf8, sz);
#د_که_پای
        X11_Toolkit_Shape_متن_Elements(بنسټ_control->کړکۍ, control->کرښې[i].متن);

        utf8 += اوږدتیا + 1;
        إذا (!lf) {
            اكسر;
        }
    }

    بنسټ_control->do_اندازه = true;
    X11Toolkit_CalculateLabelControl(بنسټ_control);
    بنسټ_control->do_اندازه = false;
    X11_Toolkit_جمع_کړه_Control_منزل_کړکۍ(کړکۍ, بنسټ_control);

    أرجع بنسټ_control;
}

صحيح X11_Toolkit_Get_Label_Control_لومړی_کرښه_لوړوالی(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    أرجع label_control->کرښې[0].rect.h;
}

فراغ X11_Toolkit_Signal_کړکۍ_Close(SDL_Toolkit_کړکۍ_X11 *معلومات) {
    معلومات->close = true;
}

#د_که_پای // SDL_VIDEO_DRIVER_X11
