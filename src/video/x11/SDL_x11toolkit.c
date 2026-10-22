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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#شامل "../../SDL_list.h"
#شامل "SDL_x11video.h"
#اگر_تعریف_شدہ SDL_USE_LIBDBUS
#شامل "../../core/linux/SDL_system_theme.h"
#اگر_ختم
#اگر_تعریف_شدہ HAVE_FRIBIDI_H
#شامل "../../core/unix/SDL_fribidi.h"
#اگر_ختم
#شامل "SDL_x11dyn.h"
#شامل "SDL_x11toolkit.h"
#شامل "SDL_x11settings.h"
#شامل "SDL_x11modes.h"
#شامل "xsettings-client.h"
#شامل <X11/keysym.h>
#شامل <locale.h>

#تعریف_کرو SDL_سیٹ_LOCALE 1
#تعریف_کرو SDL_GRAB 1

قسمتعریف شمار SDL_Toolkit_متن_Type_X11
{
    SDL_TOOLKIT_متن_TYPE_X11_GENERIC,
    SDL_TOOLKIT_متن_TYPE_X11_THAI
} SDL_Toolkit_متن_Type_X11;

#اگر_تعریف_شدہ HAVE_LIBTHAI_H
قسمتعریف ساخت SDL_ToolkitThaiOverlayX11
{
    bool چوٹی;
    حرف *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#اگر_ختم

قسمتعریف ساخت SDL_Toolkit_متن_Element_X11
{
    SDL_Toolkit_متن_Type_X11 type;
    حرف *str;
    size_t sz;
    SDL_Rect rect;
    صحیح font_h;
    خالی (*str_free)(خالی *);
#اگر_تعریف_شدہ HAVE_LIBTHAI_H
    SDL_List_گرہ *thai_overlays;
#اگر_ختم
} SDL_Toolkit_متن_Element_X11;

قسمتعریف ساخت SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 والد;

    /* Icon type */
    SDL_پیغام_Box_Flags flags;
    حرف icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    صحیح icon_char_x;
    صحیح icon_char_y;
    صحیح icon_char_a;
    صحیح icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

قسمتعریف ساخت SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 والد;

    /*ڈیٹا*/
    ثابت SDL_پیغام_Box_Button_ڈیٹا *ڈیٹا;

    /*متن*/
    SDL_List_گرہ *متن;
    SDL_Rect متن_rect;
    
    /* Callback */
    خالی *cb_ڈیٹا;
    خالی (*cb)(ساخت SDL_ToolkitControlX11 *, خالی *);
} SDL_ToolkitButtonControlX11;

قسمتعریف ساخت SDL_Toolkit_Label_Control_سطر_X11
{
    SDL_List_گرہ *متن;
    SDL_Rect rect;
#اگر_تعریف_شدہ HAVE_FRIBIDI_H
    FriBidiParType par;
#اگر_ختم
} SDL_Toolkit_Label_Control_سطر_X11;

قسمتعریف ساخت SDL_ToolkitLabelControlX11
{
    SDL_ToolkitControlX11 والد;

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

قسمتعریف ساخت SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 والد;

    SDL_List_گرہ *menu_اشیاء;
} SDL_ToolkitMenuBarControlX11;

قسمتعریف ساخت SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 والد;

    SDL_List_گرہ *menu_اشیاء;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
ساکن ثابت حرف *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#تعریف_کرو G_ICONFONT_سائز 22

/* General UI font */
ساکن ثابت حرف g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
ساکن ثابت حرف g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

ساکن ثابت حرف *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    تہی
};
#تعریف_کرو G_TOOLKITFONT_سائز 140

ساکن ثابت SDL_پیغام_Box_Color g_default_colors[SDL_MESSAGEBOX_COLOR_گنتی] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#اگر_تعریف_شدہ SDL_USE_LIBDBUS
ساکن ثابت SDL_پیغام_Box_Color g_default_colors_dark[SDL_MESSAGEBOX_COLOR_گنتی] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#اگر 0
ساکن ثابت SDL_پیغام_Box_Color g_default_colors_dark_بلند_contrast[SDL_MESSAGEBOX_COLOR_گنتی] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

ساکن ثابت SDL_پیغام_Box_Color g_default_colors_light_بلند_contrast[SDL_MESSAGEBOX_COLOR_گنتی] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#اگر_ختم

#اگر_ختم

ساکن صحیح g_shm_error;
ساکن صحیح (*g_old_error_handler)(Display *, XErrorEvent *) = تہی;

ساکن صحیح X11_Toolkit_Shared_حافظہ_Error_Handler(Display *d, XErrorEvent *e)
{
    اگر (e->error_رمز == BadAccess || e->error_رمز == BadRequest) {
        g_shm_error = True;
        واپس 0;
    }
    واپس g_old_error_handler(d, e);
}

ساکن خالی X11_Toolkit_Init_کھڑکی_Pixmap(SDL_Toolkit_کھڑکی_X11 *ڈیٹا) {
    اگر (ڈیٹا->pixmap) {
#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
        اگر (!ڈیٹا->shm_pixmap) {
            ڈیٹا->drawable = X11_XCreatePixmap(ڈیٹا->display, ڈیٹا->کھڑکی, ڈیٹا->pixmap_چوڑائی, ڈیٹا->pixmap_اونچائی, ڈیٹا->گہرائی_2);
        }
#ورنہ
        ڈیٹا->drawable = X11_XCreatePixmap(ڈیٹا->display, ڈیٹا->کھڑکی, ڈیٹا->pixmap_چوڑائی, ڈیٹا->pixmap_اونچائی, ڈیٹا->گہرائی_2);
#اگر_ختم
#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
        اگر (ڈیٹا->shm) {
            ڈیٹا->image = X11_XShmCreateImage(ڈیٹا->display, ڈیٹا->visual, ڈیٹا->گہرائی_2, ZPixmap, تہی, &ڈیٹا->shm_info, ڈیٹا->pixmap_چوڑائی, ڈیٹا->pixmap_اونچائی);
            اگر (ڈیٹا->image) {
                ڈیٹا->shm_بائٹیں_فی_سطر = ڈیٹا->image->بائٹیں_فی_سطر;

                ڈیٹا->shm_info.shmid = shmget(IPC_نجی, ڈیٹا->image->بائٹیں_فی_سطر * ڈیٹا->image->اونچائی, IPC_CREAT | 0777);
                اگر (ڈیٹا->shm_info.shmid < 0) {
                    XDestroyImage(ڈیٹا->image);
                    ڈیٹا->image = تہی;
                    ڈیٹا->shm = false;
                    واپس;
                }

                ڈیٹا->shm_info.readOnly = False;
                ڈیٹا->shm_info.shmaddr = ڈیٹا->image->ڈیٹا = (حرف *)shmat(ڈیٹا->shm_info.shmid, تہی, 0);
                اگر (((علامتی حرف *)ڈیٹا->shm_info.shmaddr) == (علامتی حرف *)-1) {
                    XDestroyImage(ڈیٹا->image);
                    ڈیٹا->shm = false;
                    ڈیٹا->image = تہی;
                    واپس;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11_Toolkit_Shared_حافظہ_Error_Handler);
                X11_XShmAttach(ڈیٹا->display, &ڈیٹا->shm_info);
                X11_XSync(ڈیٹا->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                اگر (g_shm_error) {
                    XDestroyImage(ڈیٹا->image);
                    shmdt(ڈیٹا->shm_info.shmaddr);
                    shmctl(ڈیٹا->shm_info.shmid, IPC_RMID, تہی);
                    ڈیٹا->image = تہی;
                    ڈیٹا->shm = false;
                    واپس;
                }

                اگر (ڈیٹا->shm_pixmap) {
                    ڈیٹا->drawable = X11_XShmCreatePixmap(ڈیٹا->display, ڈیٹا->کھڑکی, ڈیٹا->shm_info.shmaddr, &ڈیٹا->shm_info, ڈیٹا->pixmap_چوڑائی, ڈیٹا->pixmap_اونچائی, ڈیٹا->گہرائی_2);
                    اگر (ڈیٹا->drawable == None) {
                        ڈیٹا->shm_pixmap = False;
                    } ورنہ {
                        XDestroyImage(ڈیٹا->image);
                        ڈیٹا->image = تہی;
                    }
                }

                shmctl(ڈیٹا->shm_info.shmid, IPC_RMID, تہی);
            } ورنہ {
                ڈیٹا->shm = false;
            }
        }
#اگر_ختم
    }
}

ساکن خالی X11_Toolkit_Init_کھڑکی_Fonts(SDL_Toolkit_کھڑکی_X11 *کھڑکی)
{    
    کھڑکی->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    کھڑکی->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    کھڑکی->utf8 = true;
    کھڑکی->font_سیٹ = تہی;
    اگر (SDL_X11_HAVE_UTF8) {
        حرف **missing = تہی;
        صحیح عدد_missing = 0;
        صحیح i_font;
        کھڑکی->font_struct = تہی;
        برائے (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            حرف *font;

            اگر (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_بھرو_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_سائز * کھڑکی->iscale);
                کھڑکی->font_سیٹ = X11_XCreate_Font_سیٹ(کھڑکی->display, font, &missing, &عدد_missing, تہی);
                SDL_free(font);

                اگر (!کھڑکی->font_سیٹ) {
                    اگر (کھڑکی->scale != 0 && کھڑکی->iscale > 0) {
                        کھڑکی->iscale = (صحیح)SDL_ceilf(کھڑکی->scale);
                        کھڑکی->scale = 0;
                    } ورنہ {
                        کھڑکی->iscale--;
                    }
                    جاؤ try_بھرو_font;
                }
            } ورنہ {
                کھڑکی->font_سیٹ = X11_XCreate_Font_سیٹ(کھڑکی->display, g_ToolkitFont[i_font], &missing, &عدد_missing, تہی);
            }

            اگر (missing) {
                X11_XFreeStringList(missing);
            }

            اگر (کھڑکی->font_سیٹ) {
                توڑو;
            }
        }

        اگر (!کھڑکی->font_سیٹ) {
            جاؤ بھرو_font_traditional;
        } ورنہ {
            XFontStruct **font_structs;
            حرف **font_نام;
            صحیح font_sz;
            صحیح i;
            
#اگر_تعریف_شدہ HAVE_FRIBIDI_H
            کھڑکی->do_shaping = !X11_XContextDependentDrawing(کھڑکی->font_سیٹ);
#اگر_ختم
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFonts_کا_Font_سیٹ(کھڑکی->font_سیٹ, &font_structs, &font_نام);
            برائے (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                اگر (SDL_strstr(font_نام[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } ورنہ اگر (SDL_strstr(font_نام[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } ورنہ اگر (SDL_strstr(font_نام[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } ورنہ اگر (SDL_strstr(font_نام[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } ورنہ اگر (SDL_strstr(font_نام[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                اگر (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(کھڑکی->display, font_نام[i]);
                    اگر (font_struct) {
                        اگر (font_struct->فی_char) {
                            صحیح glyphs_sz;
                            صحیح j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            برائے (j = 0; j < glyphs_sz; j++) {
                                اگر (font_struct->فی_char[j].lbearing < 0) {
                                    کھڑکی->thai_font = SDL_TOOLKIT_THAI_FONT_X11_انحراف;
                                }
                            }
                        }
                        X11_XFreeFont(کھڑکی->display, font_struct);
                    }
                }
                
                کھڑکی->thai_encoding = thai_encoding;
            } 
        }
    } ورنہ
#اگر_ختم
    {
        حرف *font;

        بھرو_font_traditional:
        کھڑکی->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_سائز * کھڑکی->iscale);
        کھڑکی->font_struct = X11_XLoadQueryFont(کھڑکی->display, font);
        SDL_free(font);
        اگر (!کھڑکی->font_struct) {
            اگر (کھڑکی->iscale > 0) {
                اگر (کھڑکی->scale != 0) {
                    کھڑکی->iscale = (صحیح)SDL_ceilf(کھڑکی->scale);
                    کھڑکی->scale = 0;
                } ورنہ {
                    کھڑکی->iscale--;
                }
                جاؤ بھرو_font_traditional;
            } ورنہ {
                کھڑکی->font_struct = X11_XLoadQueryFont(کھڑکی->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

ساکن خالی X11Toolkit_SettingsNotify(ثابت حرف *name, XSettingsAction action, XSettingsSetting *setting, خالی *ڈیٹا)
{
    SDL_Toolkit_کھڑکی_X11 *کھڑکی;
    صحیح i;

    کھڑکی = ڈیٹا;

    اگر (کھڑکی->xsettings_پہلا_وقت) {
        واپس;
    }

    اگر (SDL_strcmp(name, SDL_XSETTINGS_GDK_کھڑکی_SCALING_ضربی_عدد) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_تیاری = false;
        bool pixmap_already_تیاری = false;

        اگر (کھڑکی->pixmap) {
            pixmap_already_تیاری = true;
        } ورنہ {
            dbe_already_تیاری = true;
        }

        /* set scale vars */
        کھڑکی->scale = X11_GetGlobalContentScale(کھڑکی->display, کھڑکی->xsettings);
        کھڑکی->iscale = (صحیح)SDL_ceilf(کھڑکی->scale);
        اگر (کھڑکی->scale < 1) {
            کھڑکی->scale = 1;
        }
        اگر (SDL_roundf(کھڑکی->scale) == کھڑکی->scale) {
            کھڑکی->scale = 0;
        }

        /* setup fonts */
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
        اگر (کھڑکی->font_سیٹ) {
            X11_XFree_Font_سیٹ(کھڑکی->display, کھڑکی->font_سیٹ);
        }
#اگر_ختم
        اگر (کھڑکی->font_struct) {
            X11_XFreeFont(کھڑکی->display, کھڑکی->font_struct);
        }

        X11_Toolkit_Init_کھڑکی_Fonts(کھڑکی);

        /* set up window */
        اگر (کھڑکی->scale != 0) {
            کھڑکی->کھڑکی_چوڑائی = SDL_lroundf((کھڑکی->کھڑکی_چوڑائی/کھڑکی->iscale) * کھڑکی->scale);
            کھڑکی->کھڑکی_اونچائی = SDL_lroundf((کھڑکی->کھڑکی_اونچائی/کھڑکی->iscale) * کھڑکی->scale);
            کھڑکی->pixmap_چوڑائی = کھڑکی->کھڑکی_چوڑائی;
            کھڑکی->pixmap_اونچائی = کھڑکی->کھڑکی_اونچائی;
            کھڑکی->pixmap = true;
        } ورنہ {
            کھڑکی->pixmap = false;
        }

        اگر (کھڑکی->pixmap) {
            اگر (!pixmap_already_تیاری) {
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
                اگر (SDL_X11_HAVE_XDBE && کھڑکی->xdbe) {
                    X11_Xdbe_Deallocate_عقب_بفر_Name(کھڑکی->display, کھڑکی->buf);
                }
#اگر_ختم
            }
            X11_XFreePixmap(کھڑکی->display, کھڑکی->drawable);
            X11_Toolkit_Init_کھڑکی_Pixmap(کھڑکی);
        } ورنہ {
            اگر (!dbe_already_تیاری) {
                X11_XFreePixmap(کھڑکی->display, کھڑکی->drawable);
#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
                اگر (کھڑکی->image) {
                    XDestroyImage(کھڑکی->image);
                    کھڑکی->image = تہی;
                }
#اگر_ختم
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
                اگر (SDL_X11_HAVE_XDBE && کھڑکی->xdbe) {
                    کھڑکی->buf = X11_Xdbe_Allocate_عقب_بفر_Name(کھڑکی->display, کھڑکی->کھڑکی, XdbeUndefined);
                    کھڑکی->drawable = کھڑکی->buf;
                }
#اگر_ختم
            }
        }

        /* notify controls */
        برائے (i = 0; i < کھڑکی->controls_sz; i++) {
            کھڑکی->controls[i]->do_سائز = true;

            اگر (کھڑکی->controls[i]->func_on_scale_change) {
                کھڑکی->controls[i]->func_on_scale_change(کھڑکی->controls[i]);
            }

            اگر (کھڑکی->controls[i]->func_calc_سائز) {
                کھڑکی->controls[i]->func_calc_سائز(کھڑکی->controls[i]);
            }

            کھڑکی->controls[i]->do_سائز = false;
        }

        /* notify cb */
        اگر (کھڑکی->cb_on_scale_change) {
            کھڑکی->cb_on_scale_change(کھڑکی, کھڑکی->cb_ڈیٹا);
        }

        /* update ev scales */
        اگر (!کھڑکی->pixmap) {
            کھڑکی->ev_scale = کھڑکی->ev_iscale = 1;
        } ورنہ {
            کھڑکی->ev_scale = کھڑکی->scale;
            کھڑکی->ev_iscale = کھڑکی->iscale;
        }
    }
}

ساکن خالی X11_Toolkit_Get_متن_چوڑائی_اونچائی_For_Font(XFontStruct *font, ثابت حرف *str, صحیح nbytes, صحیح *pwidth, صحیح *pheight, صحیح *ascent, صحیح *font_اونچائی)
{
    XCharStruct متن_structure;
    صحیح font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &متن_structure);
    *pwidth = متن_structure.چوڑائی;
    *pheight = متن_structure.ascent + متن_structure.descent;
    *ascent = متن_structure.ascent;
    اگر (font_اونچائی) {
       *font_اونچائی = font_ascent + font_descent;
    }
}

ساکن خالی X11_Toolkit_Get_متن_چوڑائی_اونچائی(SDL_Toolkit_کھڑکی_X11 *ڈیٹا, ثابت حرف *str, صحیح nbytes, صحیح *pwidth, صحیح *pheight, صحیح *ascent, صحیح *descent, صحیح *font_اونچائی)
{
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    اگر (ڈیٹا->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8_متن_Extents(ڈیٹا->font_سیٹ, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.چوڑائی;
        *pheight = overall_logical.اونچائی;
        *ascent = -overall_logical.y;
        *descent = overall_logical.اونچائی - *ascent;

        اگر (font_اونچائی) {
            XFont_سیٹ_Extents *extents;

            extents = X11_XExtents_کا_Font_سیٹ(ڈیٹا->font_سیٹ);
            *font_اونچائی = extents->max_logical_extent.اونچائی;
        }
    } ورنہ
#اگر_ختم
    {
        XCharStruct متن_structure;
        صحیح font_direction, font_ascent, font_descent;
        X11_XTextExtents(ڈیٹا->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &متن_structure);
        *pwidth = متن_structure.چوڑائی;
        *pheight = متن_structure.ascent + متن_structure.descent;
        *ascent = متن_structure.ascent;
        *descent = متن_structure.descent;

        اگر (font_اونچائی) {
            *font_اونچائی = font_ascent + font_descent;
        }
    }
}

#اگر_تعریف_شدہ HAVE_FRIBIDI_H
SDL_List_گرہ *X11_Toolkit_Make_متن_Elements(SDL_Toolkit_کھڑکی_X11 *ڈیٹا, حرف *txt, size_t sz, FriBidiParType *par)
#ورنہ
SDL_List_گرہ *X11_Toolkit_Make_متن_Elements(SDL_Toolkit_کھڑکی_X11 *ڈیٹا, حرف *txt, size_t sz)
#اگر_ختم
{
    SDL_List_گرہ *list;
    حرف *str;
    حرف *بفر_2;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = تہی;
    thai = 0;
    str = txt;
    بفر_2 = SDL_malloc(1);
    بفر_2[0] = 0;
    
#اگر_تعریف_شدہ HAVE_FRIBIDI_H
    اگر (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    اگر (ڈیٹا->fribidi) {
        حرف *fstr;
                
        fstr = SDL_FriBidi_Process(ڈیٹا->fribidi, str, sz, ڈیٹا->do_shaping, par);
        اگر (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#اگر_ختم        

    جب (1) {
        حرف *new;
        حرف utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_قدم_UTF8((ثابت حرف **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        اگر (cp == 0 || cond == (thai ? false : true)) {
            SDL_Toolkit_متن_Element_X11 *element;
            
            element = SDL_malloc(حجم(SDL_Toolkit_متن_Element_X11));
            اگر (thai) {
                element->type = SDL_TOOLKIT_متن_TYPE_X11_THAI;
            } ورنہ {
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

        اگر (!cp) {
            توڑو;
        }
        
        SDL_UCS4_مقصد_UTF8(cp, utf8);
        csz = SDL_strlen(بفر_2) + SDL_strlen(utf8) + 1;
        new = SDL_malloc(csz);
        SDL_strlcpy(new, بفر_2, csz);
        SDL_strlcat(new, utf8, csz);
        SDL_free(بفر_2);
        بفر_2 = new;
    }

    SDL_free(بفر_2);
    اگر (free_txt) {
        SDL_free(txt);
    }
    واپس list;
}

خالی X11_Toolkit_Shape_متن_Elements(SDL_Toolkit_کھڑکی_X11 *ڈیٹا, SDL_List_گرہ *list)
{
    SDL_List_گرہ *cursor;
    SDL_Toolkit_متن_Element_X11 *پچھلا;
    صحیح عارضی;
    
    /* Shape and calculate bounding box */
    cursor = list;
    جب (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->اندراج_2;
#اگر_تعریف_شدہ HAVE_LIBTHAI_H
        element->thai_overlays = تہی;
#اگر_ختم
        اگر (element->type == SDL_TOOLKIT_متن_TYPE_X11_THAI) {
            اگر (ڈیٹا->thai_font == SDL_TOOLKIT_THAI_FONT_X11_انحراف) {
                X11_Toolkit_Get_متن_چوڑائی_اونچائی(ڈیٹا, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضی, تہی);
            } ورنہ {
#اگر_تعریف_شدہ HAVE_LIBTHAI_H
                اگر (ڈیٹا->th) {
                    ساخت thcell_t *cells;
                    حرف *tis_str;
                    حرف *بنیاد_tis_str;
                    size_t cells_sz;
                    size_t بنیاد_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, حجم(ساخت thcell_t));
                    ڈیٹا->th->make_cells((ثابت thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    بنیاد_tis_str_sz = cells_sz;
                    بنیاد_tis_str = SDL_malloc(بنیاد_tis_str_sz + 1);
                    برائے (عارضی = 0; عارضی < cells_sz; عارضی++) {
                        بنیاد_tis_str[عارضی] = cells[عارضی].بنیاد;
                        
                        اگر (cells[عارضی].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            حرف *pre;
                            صحیح temp2;
                            
                            overlay = SDL_malloc(حجم(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", بنیاد_tis_str, عارضی);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت حرف *)&cells[عارضی].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->چوٹی = false;
                            X11_Toolkit_Get_متن_چوڑائی_اونچائی(ڈیٹا, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, تہی);
                            X11_Toolkit_Get_متن_چوڑائی_اونچائی(ڈیٹا, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, تہی);
                            SDL_List_جوڑو(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        اگر (cells[عارضی].چوٹی) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            حرف *pre;
                            صحیح temp2;
                            
                            overlay = SDL_malloc(حجم(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", بنیاد_tis_str, عارضی);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت حرف *)&cells[عارضی].چوٹی, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->چوٹی = true;
                            X11_Toolkit_Get_متن_چوڑائی_اونچائی(ڈیٹا, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, تہی);
                            X11_Toolkit_Get_متن_چوڑائی_اونچائی(ڈیٹا, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, تہی);
                            SDL_List_جوڑو(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    بنیاد_tis_str[بنیاد_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", بنیاد_tis_str, بنیاد_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11_Toolkit_Get_متن_چوڑائی_اونچائی(ڈیٹا, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضی, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(بنیاد_tis_str);
                }
#ورنہ
                X11_Toolkit_Get_متن_چوڑائی_اونچائی(ڈیٹا, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضی, &element->font_h);
#اگر_ختم            
            }
        } ورنہ {
            X11_Toolkit_Get_متن_چوڑائی_اونچائی(ڈیٹا, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضی, &element->font_h);
        }
        
        cursor = cursor->اگلا;
    }
    
    /* Add offsets */
    پچھلا = تہی;
    cursor = list;
    جب (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->اندراج_2;        
        اگر (پچھلا) {
            element->rect.x = پچھلا->rect.x + پچھلا->rect.w;
        } ورنہ {
            element->rect.x = 0;
        }
        
        پچھلا = element;
        cursor = cursor->اگلا;
    }
}


خالی X11_Toolkit_Draw_متن_Elements(SDL_Toolkit_کھڑکی_X11 *ڈیٹا, SDL_List_گرہ *list, صحیح x, صحیح y)
{
    SDL_List_گرہ *cursor;
    
    cursor = list;
    
    جب (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->اندراج_2;
        اگر (element->type == SDL_TOOLKIT_متن_TYPE_X11_THAI) {
            اگر (ڈیٹا->thai_font == SDL_TOOLKIT_THAI_FONT_X11_انحراف) {
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
                اگر (ڈیٹا->utf8) {
                    X11_Xutf8DrawString(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->font_سیٹ, ڈیٹا->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } ورنہ
#اگر_ختم
                {
                    X11_XDrawString(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } ورنہ {    
#اگر_تعریف_شدہ HAVE_LIBTHAI_H
                SDL_List_گرہ *overlay_cursor;
                    
                /* Draw the base string */
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
                اگر (ڈیٹا->utf8) {
                    X11_Xutf8DrawString(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->font_سیٹ, ڈیٹا->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } ورنہ
#اگر_ختم
                {
                    X11_XDrawString(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                جب (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->اندراج_2;
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
                    اگر (ڈیٹا->utf8) {
                        X11_Xutf8DrawString(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->font_سیٹ, ڈیٹا->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } ورنہ
#اگر_ختم
                    {
                        X11_XDrawString(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->اگلا;
                }
#اگر_ختم                
            }
        } ورنہ {
#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
            اگر (ڈیٹا->utf8) {
                X11_Xutf8DrawString(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->font_سیٹ, ڈیٹا->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } ورنہ
#اگر_ختم
            {
                X11_XDrawString(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->اگلا;
    }
}

صحیح X11_Toolkit_Get_متن_Elements_Rect(SDL_List_گرہ *list, SDL_Rect *برآمد)
{
    SDL_List_گرہ *cursor;
    صحیح ret;
    
    ret = 0;
    برآمد->x = برآمد->y = 0;
    برآمد->w = برآمد->h = 0;
    cursor = list;
    جب (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->اندراج_2;
        
        برآمد->w += element->rect.w;
        برآمد->h = SDL_max(برآمد->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->اگلا;
    }
    
    واپس ret;
}

خالی X11_Toolkit_Free_متن_Elements_List_Contents(SDL_List_گرہ *list)
{
    SDL_List_گرہ *cursor;
    
    cursor = list;
    جب (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
#اگر_تعریف_شدہ HAVE_LIBTHAI_H
        SDL_List_گرہ *overlay_cursor;
#اگر_ختم

        element = cursor->اندراج_2;
        
        اگر (element->str_free) {
            element->str_free(element->str);
        }
        
#اگر_تعریف_شدہ HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        جب (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->اندراج_2;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->اگلا;
        }
        SDL_ListClear(&element->thai_overlays);
#اگر_ختم
        
        SDL_free(element);
        
        cursor = cursor->اگلا;
    }
}

#تعریف_کرو X11_Toolkit_Free_متن_Elements(x) X11_Toolkit_Free_متن_Elements_List_Contents(x); SDL_ListClear(&x)
 
ساکن bool X11Toolkit_ShouldFlipUI(خالی) 
{
    SDL_Locale **current_locales;
    ساکن ثابت SDL_Locale rtl_locales[] = {
        { "ar", تہی, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", تہی, },
        { "iw", تہی, },
        { "yi", تہی, },
        { "ur", تہی, },
        { "ug", تہی, },
        { "kd", تہی, },
        { "pk", "PK", },
        { "ps", تہی, }
    }; 
    صحیح current_locales_sz;
    صحیح i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    اگر (current_locales_sz <= 0) {
        واپس false;        
    }
    برائے (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        اگر (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            اگر (!rtl_locales[i].country) {
                واپس true;
            } ورنہ {
                واپس SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    واپس false;
}

SDL_Toolkit_کھڑکی_X11 *X11_Toolkit_Create_کھڑکی_Struct(SDL_کھڑکی *والد, SDL_Toolkit_کھڑکی_X11 *tkparent, SDL_Toolkit_کھڑکی_منوال_X11 منوال, ثابت SDL_پیغام_Box_Color *colorhints, bool create_new_display)
{
    SDL_Toolkit_کھڑکی_X11 *کھڑکی;
    صحیح i;
#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#اگر_ختم
    #تعریف_کرو ErrorFreeRetNull(x, y) SDL_سیٹ_Error(x); SDL_free(y); واپس تہی
    #تعریف_کرو ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_سیٹ_Error(x, y); SDL_free(z); واپس تہی

    اگر (!SDL_X11_بھرو_Symbols()) {
        واپس تہی;
    }

    // This code could get called from multiple threads maybe?
    X11_XInit_دھاگے();

    کھڑکی = (SDL_Toolkit_کھڑکی_X11 *)SDL_malloc(حجم(SDL_Toolkit_کھڑکی_X11));
    اگر (!کھڑکی) {
        SDL_سیٹ_Error("Unable to allocate toolkit window structure");
        واپس تہی;
    }

    کھڑکی->منوال = منوال;
    کھڑکی->tk_والد = tkparent;

#اگر SDL_سیٹ_LOCALE
    اگر (منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG) {
        کھڑکی->origlocale = setlocale(LC_ALL, تہی);
        اگر (کھڑکی->origlocale) {
            کھڑکی->origlocale = SDL_strdup(کھڑکی->origlocale);
            اگر (!کھڑکی->origlocale) {
                SDL_free(کھڑکی);
                واپس تہی;
            }
            (خالی)setlocale(LC_ALL, "");
        }
    }
#اگر_ختم

    کھڑکی->والد_device = تہی;
    اگر (create_new_display) {
        کھڑکی->display = X11_XOpenDisplay(تہی);
        کھڑکی->display_close = true;
        اگر (!کھڑکی->display) {
            ErrorFreeRetNull("Couldn't open X11 display", کھڑکی);
        }
    } ورنہ {
        اگر (والد) {
            کھڑکی->والد_device = SDL_GetVideoDevice();
            کھڑکی->display = کھڑکی->والد_device->اندرونی_2->display;
            کھڑکی->display_close = false;
        } ورنہ اگر (tkparent) {
            کھڑکی->display = tkparent->display;
            کھڑکی->display_close = false;
        } ورنہ {
            کھڑکی->display = X11_XOpenDisplay(تہی);
            کھڑکی->display_close = true;
            اگر (!کھڑکی->display) {
                ErrorFreeRetNull("Couldn't open X11 display", کھڑکی);
            }
        }
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
    صحیح xrandr_event_بنیاد, xrandr_error_بنیاد;
    کھڑکی->xrandr = X11_XRRQueryExtension(کھڑکی->display, &xrandr_event_بنیاد, &xrandr_error_بنیاد);
#اگر_ختم

#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
    کھڑکی->shm_pixmap = False;
    کھڑکی->shm = X11_XShmQueryExtension(کھڑکی->display) ? SDL_X11_HAVE_SHM : false;
    اگر (کھڑکی->shm) {
        صحیح major;
        صحیح minor;

        X11_XShm_Query_نسخہ(کھڑکی->display, &major, &minor, &کھڑکی->shm_pixmap);
        اگر (کھڑکی->shm_pixmap) {
            اگر (X11_XShmPixmapFormat(کھڑکی->display) != ZPixmap) {
                کھڑکی->shm_pixmap = False;
            }
        }
    }
#اگر_ختم

    /* Scale/Xsettings */
    کھڑکی->pixmap = false;
    کھڑکی->xsettings_پہلا_وقت = true;
    کھڑکی->xsettings = xsettings_client_new(کھڑکی->display, DefaultScreen(کھڑکی->display), X11Toolkit_SettingsNotify, تہی, کھڑکی);
    کھڑکی->xsettings_پہلا_وقت = false;
    کھڑکی->scale = X11_GetGlobalContentScale(کھڑکی->display, کھڑکی->xsettings);
    اگر (کھڑکی->scale < 1) {
        کھڑکی->scale = 1;
    }
    کھڑکی->iscale = (صحیح)SDL_ceilf(کھڑکی->scale);
    اگر (SDL_roundf(کھڑکی->scale) == کھڑکی->scale) {
        کھڑکی->scale = 0;
    }

    /* Fonts */
    X11_Toolkit_Init_کھڑکی_Fonts(کھڑکی);

    /* Color hints */
#اگر_تعریف_شدہ SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    اگر (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#اگر_ختم

    اگر (!colorhints) {
#اگر_تعریف_شدہ SDL_USE_LIBDBUS
        انتخاب (theme) {
            حالت SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                توڑو;
#اگر 0
            حالت SDL_SYSTEM_THEME_LIGHT_بلند_CONTRAST:
                colorhints = g_default_colors_light_بلند_contrast;
                توڑو;
            حالت SDL_SYSTEM_THEME_DARK_بلند_CONTRAST:
                colorhints = g_default_colors_dark_بلند_contrast;
                توڑو;
#اگر_ختم
            طےشدہ:
                colorhints = g_default_colors;
        }
#ورنہ
        colorhints = g_default_colors;
#اگر_ختم
    }
    کھڑکی->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    برائے (i = 0; i < SDL_MESSAGEBOX_COLOR_گنتی; i++) {
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
    کھڑکی->والد = والد;
    اگر (والد) {
        SDL_Display_ڈیٹا *displaydata = SDL_Get_Display_Driver_ڈیٹا_For_کھڑکی(والد);
        کھڑکی->screen = displaydata->screen;
    } ورنہ {
        کھڑکی->screen = DefaultScreen(کھڑکی->display);
    }

    /* Visuals */
    اگر (منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_بچہ) {
        کھڑکی->visual = والد->اندرونی_2->visual;
        کھڑکی->cmap = والد->اندرونی_2->colormap;
        X11_GetVisualInfoFromVisual(کھڑکی->display, کھڑکی->visual, &کھڑکی->vi);
        کھڑکی->گہرائی_2 = کھڑکی->vi.گہرائی_2;
    } ورنہ {
        کھڑکی->visual = DefaultVisual(کھڑکی->display, کھڑکی->screen);
        کھڑکی->cmap = DefaultColormap(کھڑکی->display, کھڑکی->screen);
        کھڑکی->گہرائی_2 = Default_گہرائی(کھڑکی->display, کھڑکی->screen);
        X11_GetVisualInfoFromVisual(کھڑکی->display, کھڑکی->visual, &کھڑکی->vi);
    }

    /* Allocate colors */
    برائے (i = 0; i < SDL_MESSAGEBOX_COLOR_گنتی; i++) {
        X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor[i]);
    }
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor_bevel_l1);
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor_bevel_l2);
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor_bevel_d);
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor_pressed);
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &کھڑکی->xcolor_disabled_متن);

    /* Control list */
    کھڑکی->has_focus = false;
    کھڑکی->controls = تہی;
    کھڑکی->controls_sz = 0;
    کھڑکی->dyn_controls_sz = 0;
    کھڑکی->fiddled_control = تہی;
    کھڑکی->dyn_controls = تہی;

    /* Menu windows */
    کھڑکی->popup_windows = تہی;

    /* BIDI engine */
#اگر_تعریف_شدہ HAVE_FRIBIDI_H
    کھڑکی->fribidi = SDL_FriBidi_Create();
#اگر_ختم

#اگر_تعریف_شدہ HAVE_LIBTHAI_H
    کھڑکی->th = SDL_LibThai_Create();
#اگر_ختم
    
    /* Interface direction */
    کھڑکی->flip_interface = X11Toolkit_ShouldFlipUI();
    
    واپس کھڑکی;
}

ساکن خالی X11_Toolkit_جوڑو_Control_مقصد_کھڑکی(SDL_Toolkit_کھڑکی_X11 *کھڑکی, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    کھڑکی->controls_sz++;
    اگر (کھڑکی->controls_sz == 1) {
        کھڑکی->controls = (ساخت SDL_ToolkitControlX11 **)SDL_malloc(حجم(ساخت SDL_ToolkitControlX11 *));
    } ورنہ {
        کھڑکی->controls = (ساخت SDL_ToolkitControlX11 **)SDL_realloc(کھڑکی->controls, حجم(ساخت SDL_ToolkitControlX11 *) * کھڑکی->controls_sz);
    }
    کھڑکی->controls[کھڑکی->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    اگر (control->dynamic) {
        کھڑکی->dyn_controls_sz++;
        اگر (کھڑکی->dyn_controls_sz == 1) {
            کھڑکی->dyn_controls = (ساخت SDL_ToolkitControlX11 **)SDL_malloc(حجم(ساخت SDL_ToolkitControlX11 *));
        } ورنہ {
            کھڑکی->dyn_controls = (ساخت SDL_ToolkitControlX11 **)SDL_realloc(کھڑکی->dyn_controls, حجم(ساخت SDL_ToolkitControlX11 *) * کھڑکی->dyn_controls_sz);
        }
        کھڑکی->dyn_controls[کھڑکی->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    اگر (control->selected) {
        کھڑکی->focused_control = control;
    }
}

bool X11_Toolkit_Create_کھڑکی_Res(SDL_Toolkit_کھڑکی_X11 *ڈیٹا, صحیح w, صحیح h, صحیح cx, صحیح cy, حرف *title)
{
    صحیح x, y;
    XSizeHints *sizehints;
    XSet_کھڑکی_اوصاف wnd_attr;
    Atom NET_WM_کھڑکی_TYPE, NET_WM_کھڑکی_TYPE_DIALOG, NET_WM_کھڑکی_TYPE_DROPDOWN_MENU, NET_WM_کھڑکی_TYPE_TOOLTIP;
    SDL_کھڑکی_ڈیٹا *windowdata = تہی;
    Display *display = ڈیٹا->display;
    XGCValues ctx_vals;
    کھڑکی_2 جڑ_win;
    کھڑکی_2 والد_win;
    غیرعلامتی طویل gcflags = GCForeground | GCBackground;
    غیرعلامتی طویل valuemask;
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
#اگر_تعریف_شدہ XRANDR_DISABLED_BY_DEFAULT
    ثابت bool use_xrandr_by_default = false;
#ورنہ
    ثابت bool use_xrandr_by_default = true;
#اگر_ختم
#اگر_ختم

    اگر (ڈیٹا->scale == 0) {
        ڈیٹا->کھڑکی_چوڑائی = w;
        ڈیٹا->کھڑکی_اونچائی = h;
    } ورنہ {
        ڈیٹا->کھڑکی_چوڑائی = SDL_lroundf((w/ڈیٹا->iscale) * ڈیٹا->scale);
        ڈیٹا->کھڑکی_اونچائی = SDL_lroundf((h/ڈیٹا->iscale) * ڈیٹا->scale);
        ڈیٹا->pixmap_چوڑائی = w;
        ڈیٹا->pixmap_اونچائی = h;
        ڈیٹا->pixmap = true;
    }

    اگر (ڈیٹا->والد) {
        windowdata = ڈیٹا->والد->اندرونی_2;
    }

    valuemask = CWEvent_نقاب | CWColormap;
    ڈیٹا->event_نقاب = Exposure_نقاب |
                       Button_Press_نقاب | Button_Release_نقاب | کلید_Press_نقاب | کلید_Release_نقاب |
                       Structure_Notify_نقاب | Focus_Change_نقاب | اشارہ_گر_Motion_نقاب;
    wnd_attr.event_نقاب = ڈیٹا->event_نقاب;
    wnd_attr.colormap = ڈیٹا->cmap;
    اگر (ڈیٹا->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU || ڈیٹا->منوال== SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    جڑ_win = جڑ_کھڑکی(display, ڈیٹا->screen);
    اگر (ڈیٹا->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_بچہ) {
        والد_win = windowdata->xwindow;
    } ورنہ {
        والد_win = جڑ_win;
    }

    ڈیٹا->کھڑکی = X11_XCreate_کھڑکی(
        display, والد_win,
        0, 0,
        ڈیٹا->کھڑکی_چوڑائی, ڈیٹا->کھڑکی_اونچائی,
        0, ڈیٹا->گہرائی_2, داخلہ_Output, ڈیٹا->visual,
        valuemask, &wnd_attr);
    اگر (ڈیٹا->کھڑکی == None) {
        واپس SDL_سیٹ_Error("Couldn't create X window");
    }

    اگر (windowdata && ڈیٹا->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG) {
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
        X11_XChangeProperty(display, ڈیٹا->کھڑکی, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_منوال_Replace, (غیرعلامتی حرف *)stateatoms, statecount);
    }

    اگر (windowdata && ڈیٹا->منوال != SDL_TOOLKIT_کھڑکی_منوال_X11_بچہ) {
        X11_XSetTransientForHint(display, ڈیٹا->کھڑکی, windowdata->xwindow);
    }

    اگر (ڈیٹا->tk_والد) {
        X11_XSetTransientForHint(display, ڈیٹا->کھڑکی, ڈیٹا->tk_والد->کھڑکی);
    }

    SDL_X11_سیٹ_کھڑکی_Title(display, ڈیٹا->کھڑکی, title);

    // Let the window manager the type of the window
    اگر (ڈیٹا->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG) {
        NET_WM_کھڑکی_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_کھڑکی_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, ڈیٹا->کھڑکی, NET_WM_کھڑکی_TYPE, XA_ATOM, 32,
                            Prop_منوال_Replace,
                            (غیرعلامتی حرف *)&NET_WM_کھڑکی_TYPE_DIALOG, 1);
    } ورنہ اگر (ڈیٹا->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU) {
        NET_WM_کھڑکی_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_کھڑکی_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, ڈیٹا->کھڑکی, NET_WM_کھڑکی_TYPE, XA_ATOM, 32,
                            Prop_منوال_Replace,
                            (غیرعلامتی حرف *)&NET_WM_کھڑکی_TYPE_DROPDOWN_MENU, 1);
    } ورنہ اگر (ڈیٹا->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
        NET_WM_کھڑکی_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_کھڑکی_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, ڈیٹا->کھڑکی, NET_WM_کھڑکی_TYPE, XA_ATOM, 32,
                            Prop_منوال_Replace,
                            (غیرعلامتی حرف *)&NET_WM_کھڑکی_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    ڈیٹا->wm_delete_پیغام = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, ڈیٹا->کھڑکی, &ڈیٹا->wm_delete_پیغام, 1);
    ڈیٹا->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    اگر (ڈیٹا->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU || ڈیٹا->منوال== SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
        x = cx;
        y = cy;
        جاؤ MOVEWINDOW;
    }
    اگر (windowdata) {
        XWindow_اوصاف attrib;
        کھڑکی_2 dummy;

        X11_XGet_کھڑکی_اوصاف(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.چوڑائی - ڈیٹا->کھڑکی_چوڑائی) / 2;
        y = attrib.y + (attrib.اونچائی - ڈیٹا->کھڑکی_اونچائی) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, جڑ_کھڑکی(display, ڈیٹا->screen), x, y, &x, &y, &dummy);
    } ورنہ {
        ثابت SDL_VideoDevice *dev = SDL_GetVideoDevice();
        اگر (dev && dev->displays && dev->عدد_displays > 0) {
            ثابت SDL_VideoDisplay *dpy = dev->displays[0];
            ثابت SDL_Display_ڈیٹا *dpydata = dpy->اندرونی_2;
            x = dpydata->x + ((dpy->current_منوال->w - ڈیٹا->کھڑکی_چوڑائی) / 2);
            y = dpydata->y + ((dpy->current_منوال->h - ڈیٹا->کھڑکی_اونچائی) / 3);
        }
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
        ورنہ اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && ڈیٹا->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_برآمد;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, جڑ_win);
            اگر (!screen_res) {
                جاؤ NOXRANDR;
            }

            default_برآمد = X11_XRRGetOutputPrimary(display, جڑ_win);
            اگر (default_برآمد != None) {
                XRROutputInfo *برآمد_info;

                برآمد_info = X11_XRRGetOutputInfo(display, screen_res, default_برآمد);
                اگر (برآمد_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(برآمد_info);
                    جاؤ FIRSTOUTPUTXRANDR;
                }

                اگر (برآمد_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, برآمد_info->crtc);
                } ورنہ اگر (برآمد_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, برآمد_info->crtcs[0]);
                } ورنہ {
                    crtc_info = تہی;
                }
                
                اگر (crtc_info) {
                    x = (crtc_info->چوڑائی - ڈیٹا->کھڑکی_چوڑائی) / 2;
                    y = (crtc_info->اونچائی - ڈیٹا->کھڑکی_اونچائی) / 3;
                    X11_XRRFreeOutputInfo(برآمد_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } ورنہ {
                    X11_XRRFreeOutputInfo(برآمد_info);
                    جاؤ NOXRANDR;
                }
            } ورنہ {
                    FIRSTOUTPUTXRANDR:
                    اگر (screen_res->noutput > 0) {
                        XRROutputInfo *برآمد_info;

                        برآمد_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        اگر (!برآمد_info) {
                            جاؤ FIRSTCRTCXRANDR;
                        }

                        اگر (برآمد_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, برآمد_info->crtc);
                        } ورنہ اگر (برآمد_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, برآمد_info->crtcs[0]);
                        } ورنہ {
                            crtc_info = تہی;
                        }

                        اگر (!crtc_info) {
                            X11_XRRFreeOutputInfo(برآمد_info);
                            جاؤ FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->چوڑائی - ڈیٹا->کھڑکی_چوڑائی) / 2;
                        y = (crtc_info->اونچائی - ڈیٹا->کھڑکی_اونچائی) / 3;
                        X11_XRRFreeOutputInfo(برآمد_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        جاؤ MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    اگر (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        جاؤ NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    اگر (crtc_info) {
                        x = (crtc_info->چوڑائی - ڈیٹا->کھڑکی_چوڑائی) / 2;
                        y = (crtc_info->اونچائی - ڈیٹا->کھڑکی_اونچائی) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } ورنہ {
                        X11_XRRFreeScreenResources(screen_res);
                        جاؤ NOXRANDR;
                    }
            }
        }
#اگر_ختم
        ورنہ {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (Display_چوڑائی(display, ڈیٹا->screen) - ڈیٹا->کھڑکی_چوڑائی) / 2;
            y = (Display_اونچائی(display, ڈیٹا->screen) - ڈیٹا->کھڑکی_اونچائی) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMove_کھڑکی(display, ڈیٹا->کھڑکی, x, y);
    ڈیٹا->کھڑکی_x = x;
    ڈیٹا->کھڑکی_y = y;

    sizehints = X11_XAlloc_سائز_Hints();
    اگر (sizehints) {
        sizehints->flags = USPosition | USSize | PMax_سائز | PMin_سائز;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->چوڑائی = ڈیٹا->کھڑکی_چوڑائی;
        sizehints->اونچائی = ڈیٹا->کھڑکی_اونچائی;

        sizehints->min_چوڑائی_2 = sizehints->max_چوڑائی_2 = ڈیٹا->کھڑکی_چوڑائی;
        sizehints->min_اونچائی_2 = sizehints->max_اونچائی_2 = ڈیٹا->کھڑکی_اونچائی;

        X11_XSetWMNormalHints(display, ڈیٹا->کھڑکی, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, ڈیٹا->کھڑکی);

    ڈیٹا->drawable = ڈیٹا->کھڑکی;
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    اگر (SDL_X11_HAVE_XDBE && !ڈیٹا->pixmap) {
        صحیح xdbe_major, xdbe_minor;
        اگر (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            ڈیٹا->xdbe = true;
            ڈیٹا->buf = X11_Xdbe_Allocate_عقب_بفر_Name(display, ڈیٹا->کھڑکی, XdbeUndefined);
            ڈیٹا->drawable = ڈیٹا->buf;
        } ورنہ {
            ڈیٹا->xdbe = false;
        }
    }
#اگر_ختم

    X11_Toolkit_Init_کھڑکی_Pixmap(ڈیٹا);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = ڈیٹا->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = ڈیٹا->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    اگر (!ڈیٹا->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = ڈیٹا->font_struct->fid;
    }
    ڈیٹا->ctx = X11_XCreateGC(ڈیٹا->display, ڈیٹا->drawable, gcflags, &ctx_vals);
    اگر (ڈیٹا->ctx == None) {
        واپس SDL_سیٹ_Error("Couldn't create graphics context");
    }

    ڈیٹا->close = false;
    ڈیٹا->کلید_control_esc = ڈیٹا->کلید_control_enter = تہی;
    اگر (!ڈیٹا->pixmap) {
        ڈیٹا->ev_scale = ڈیٹا->ev_iscale = 1;
    } ورنہ {
        ڈیٹا->ev_scale = ڈیٹا->scale;
        ڈیٹا->ev_iscale = ڈیٹا->iscale;
    }

#اگر SDL_GRAB
    اگر (ڈیٹا->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU || ڈیٹا->منوال== SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
        X11_XGrab_اشارہ_گر(display, ڈیٹا->کھڑکی, False, Button_Press_نقاب | Button_Release_نقاب | اشارہ_گر_Motion_نقاب, Grab_منوال_Async, Grab_منوال_Async, None, None, Current_وقت);
        X11_XGrabKeyboard(display, ڈیٹا->کھڑکی, False, Grab_منوال_Async, Grab_منوال_Async, Current_وقت);
    }
#اگر_ختم

    واپس true;
}

ساکن خالی X11_Toolkit_Draw_کھڑکی(SDL_Toolkit_کھڑکی_X11 *ڈیٹا) {
    SDL_Rect rect;
    صحیح i;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
    اگر (SDL_X11_HAVE_XDBE && ڈیٹا->xdbe && !ڈیٹا->pixmap) {
        X11_XdbeBeginIdiom(ڈیٹا->display);
    }
#اگر_ختم

    X11_XSetForeground(ڈیٹا->display, ڈیٹا->ctx, ڈیٹا->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    اگر (ڈیٹا->pixmap) {
        X11_XFillRectangle(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->ctx, 0, 0, ڈیٹا->pixmap_چوڑائی, ڈیٹا->pixmap_اونچائی);
    } ورنہ {
        X11_XFillRectangle(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->ctx, 0, 0, ڈیٹا->کھڑکی_چوڑائی, ڈیٹا->کھڑکی_اونچائی);
    }

    برائے (i = 0; i < ڈیٹا->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = ڈیٹا->controls[i];
        اگر (control) {
            اگر (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
    اگر (SDL_X11_HAVE_XDBE && ڈیٹا->xdbe && !ڈیٹا->pixmap) {
        Xdbe_تبادلہ_Info تبادلہ_info;
        تبادلہ_info.تبادلہ_کھڑکی = ڈیٹا->کھڑکی;
        تبادلہ_info.تبادلہ_action = XdbeUndefined;
        X11_Xdbe_تبادلہ_Buffers(ڈیٹا->display, &تبادلہ_info, 1);
        X11_Xdbe_انتہا_Idiom(ڈیٹا->display);
    }
#اگر_ختم

    اگر (ڈیٹا->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = ڈیٹا->کھڑکی_چوڑائی;
        rect.h = ڈیٹا->کھڑکی_اونچائی;
#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
        اگر (ڈیٹا->shm) {
            اگر (ڈیٹا->shm_pixmap) {
                X11_XFlush(ڈیٹا->display);
                X11_XSync(ڈیٹا->display, false);
                scale_surface = SDL_CreateSurfaceFrom(ڈیٹا->pixmap_چوڑائی, ڈیٹا->pixmap_اونچائی, X11_GetPixelFormatFromVisualInfo(ڈیٹا->display, &ڈیٹا->vi), ڈیٹا->shm_info.shmaddr, ڈیٹا->shm_بائٹیں_فی_سطر);
                SDL_BlitSurfaceScaled(scale_surface, تہی, scale_surface, &rect, SDL_SCALEMODE_خطی);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->کھڑکی, ڈیٹا->ctx, 0, 0, ڈیٹا->کھڑکی_چوڑائی, ڈیٹا->کھڑکی_اونچائی, 0, 0);
            } ورنہ {
                X11_XShmGetImage(ڈیٹا->display, ڈیٹا->drawable, ڈیٹا->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(ڈیٹا->pixmap_چوڑائی, ڈیٹا->pixmap_اونچائی, X11_GetPixelFormatFromVisualInfo(ڈیٹا->display, &ڈیٹا->vi), ڈیٹا->image->ڈیٹا, ڈیٹا->image->بائٹیں_فی_سطر);
                SDL_BlitSurfaceScaled(scale_surface, تہی, scale_surface, &rect, SDL_SCALEMODE_خطی);
                X11_XShmPutImage(ڈیٹا->display, ڈیٹا->کھڑکی, ڈیٹا->ctx, ڈیٹا->image, 0, 0, 0, 0, ڈیٹا->کھڑکی_چوڑائی, ڈیٹا->کھڑکی_اونچائی, False);
            }
        } ورنہ
#اگر_ختم
        {
            XImage *image;

            image = X11_XGetImage(ڈیٹا->display, ڈیٹا->drawable, 0, 0 , ڈیٹا->pixmap_چوڑائی, ڈیٹا->pixmap_اونچائی, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(ڈیٹا->pixmap_چوڑائی, ڈیٹا->pixmap_اونچائی, X11_GetPixelFormatFromVisualInfo(ڈیٹا->display, &ڈیٹا->vi), image->ڈیٹا, image->بائٹیں_فی_سطر);
            SDL_BlitSurfaceScaled(scale_surface, تہی, scale_surface, &rect, SDL_SCALEMODE_خطی);
            X11_XPutImage(ڈیٹا->display, ڈیٹا->کھڑکی, ڈیٹا->ctx, image, 0, 0, 0, 0, ڈیٹا->کھڑکی_چوڑائی, ڈیٹا->کھڑکی_اونچائی);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(ڈیٹا->display);
}

ساکن SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_Toolkit_کھڑکی_X11 *ڈیٹا, صحیح x, صحیح y)
{
    صحیح i;

    برائے (i = 0; i < ڈیٹا->controls_sz; i++) {
        SDL_Rect *rect = &ڈیٹا->controls[i]->rect;
        اگر ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            واپس ڈیٹا->controls[i];
        }
    }

    واپس تہی;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
ساکن Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_Toolkit_کھڑکی_X11 *ڈیٹا = (SDL_Toolkit_کھڑکی_X11 *)arg;

    اگر (event->xany.display != ڈیٹا->display) {
        واپس False;
    }

    اگر (event->xany.کھڑکی == ڈیٹا->کھڑکی) {
        واپس True;
    }

    واپس False;
}

خالی X11_Toolkit_Process_کھڑکی_Events(SDL_Toolkit_کھڑکی_X11 *ڈیٹا, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    اگر ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        واپس;
    }

    ڈیٹا->draw = false;
    ڈیٹا->e = e;

    انتخاب (e->type) {
        حالت Expose:
            ڈیٹا->draw = true;
            توڑو;
        حالت Client_پیغام:
            اگر (e->xclient.پیغام_type == ڈیٹا->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.ڈیٹا.l[0] == ڈیٹا->wm_delete_پیغام) {
                ڈیٹا->close = true;
            }
            توڑو;
        حالت Focus_اندر:
            ڈیٹا->has_focus = true;
            توڑو;
        حالت Focus_برآمد:
            ڈیٹا->has_focus = false;
            اگر (ڈیٹا->fiddled_control) {
                ڈیٹا->fiddled_control->selected = false;
            }
            ڈیٹا->fiddled_control = تہی;
            برائے (ڈیٹا->ev_i = 0; ڈیٹا->ev_i < ڈیٹا->controls_sz; ڈیٹا->ev_i++) {
                ڈیٹا->controls[ڈیٹا->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_معمول;
            }
            توڑو;
        حالت MotionNotify:
            اگر (ڈیٹا->has_focus) {
                ڈیٹا->پچھلا_control = ڈیٹا->fiddled_control;
                ڈیٹا->fiddled_control = X11Toolkit_GetControlMouseIsOn(ڈیٹا, SDL_lroundf((e->xbutton.x/ ڈیٹا->ev_scale)* ڈیٹا->ev_iscale), SDL_lroundf((e->xbutton.y/ ڈیٹا->ev_scale)* ڈیٹا->ev_iscale));
                اگر (ڈیٹا->پچھلا_control) {
                    ڈیٹا->پچھلا_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_معمول;
                    اگر (ڈیٹا->پچھلا_control->func_on_state_change) {
                        ڈیٹا->پچھلا_control->func_on_state_change(ڈیٹا->پچھلا_control);
                    }
                    ڈیٹا->draw = true;
                }
                اگر (ڈیٹا->fiddled_control) {
                    اگر (ڈیٹا->fiddled_control->dynamic) {
                        ڈیٹا->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        اگر (ڈیٹا->fiddled_control->func_on_state_change) {
                            ڈیٹا->fiddled_control->func_on_state_change(ڈیٹا->fiddled_control);
                        }
                        ڈیٹا->draw = true;
                    } ورنہ {
                        ڈیٹا->fiddled_control = تہی;
                    }
                }
            }
            توڑو;
        حالت ButtonPress:
            ڈیٹا->پچھلا_control = ڈیٹا->fiddled_control;
            اگر (ڈیٹا->پچھلا_control) {
                ڈیٹا->پچھلا_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_معمول;
                اگر (ڈیٹا->پچھلا_control->func_on_state_change) {
                    ڈیٹا->پچھلا_control->func_on_state_change(ڈیٹا->پچھلا_control);
                }
                ڈیٹا->draw = true;
            }
            اگر (e->xbutton.button == Button1) {
                ڈیٹا->fiddled_control = X11Toolkit_GetControlMouseIsOn(ڈیٹا, SDL_lroundf((e->xbutton.x/ ڈیٹا->ev_scale)* ڈیٹا->ev_iscale), SDL_lroundf((e->xbutton.y/ ڈیٹا->ev_scale)* ڈیٹا->ev_iscale));
                اگر (ڈیٹا->fiddled_control) {
                    ڈیٹا->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    اگر (ڈیٹا->fiddled_control->func_on_state_change) {
                        ڈیٹا->fiddled_control->func_on_state_change(ڈیٹا->fiddled_control);
                    }
                    ڈیٹا->draw = true;
                }
            }
            توڑو;
        حالت ButtonRelease:
            اگر (ڈیٹا->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU || ڈیٹا->منوال== SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
                صحیح cx;
                صحیح cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                اگر (cy < 0 || cx < 0) {
                    ڈیٹا->close = true;
                }

                اگر (cy > ڈیٹا->کھڑکی_اونچائی || cx > ڈیٹا->کھڑکی_چوڑائی) {
                    ڈیٹا->close = true;
                }
            }

            اگر ((e->xbutton.button == Button1) && (ڈیٹا->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(ڈیٹا, SDL_lroundf((e->xbutton.x/ ڈیٹا->ev_scale)* ڈیٹا->ev_iscale), SDL_lroundf((e->xbutton.y/ ڈیٹا->ev_scale)* ڈیٹا->ev_iscale));
                اگر (ڈیٹا->fiddled_control == control) {
                    ڈیٹا->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    اگر (ڈیٹا->fiddled_control->func_on_state_change) {
                        ڈیٹا->fiddled_control->func_on_state_change(ڈیٹا->fiddled_control);
                    }
                    ڈیٹا->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_معمول;
                    ڈیٹا->draw = true;
                }
            }
            توڑو;
        حالت کلید_Press:
            ڈیٹا->آخری_کلید_pressed = X11_XLookupKeysym(&e->xkey, 0);

            اگر (ڈیٹا->آخری_کلید_pressed == XK_Escape) {
                برائے (ڈیٹا->ev_i = 0; ڈیٹا->ev_i < ڈیٹا->controls_sz; ڈیٹا->ev_i++) {
                    اگر(ڈیٹا->controls[ڈیٹا->ev_i]->is_default_esc) {
                        ڈیٹا->controls[ڈیٹا->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        ڈیٹا->draw = true;
                        ڈیٹا->کلید_control_esc = ڈیٹا->controls[ڈیٹا->ev_i];
                    }
                }
            } ورنہ اگر ((ڈیٹا->آخری_کلید_pressed == XK_Return) || (ڈیٹا->آخری_کلید_pressed == XK_KP_Enter)) {
                برائے (ڈیٹا->ev_i = 0; ڈیٹا->ev_i < ڈیٹا->controls_sz; ڈیٹا->ev_i++) {
                    اگر(ڈیٹا->controls[ڈیٹا->ev_i]->selected) {
                        ڈیٹا->controls[ڈیٹا->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        ڈیٹا->draw = true;
                        ڈیٹا->کلید_control_enter = ڈیٹا->controls[ڈیٹا->ev_i];
                    }
                }
            }
            توڑو;
        حالت کلید_Release:
        {
            کلید_Sym کلید = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            اگر (کلید != ڈیٹا->آخری_کلید_pressed) {
                توڑو;
            }

            اگر (کلید == XK_Escape) {
                اگر (ڈیٹا->کلید_control_esc) {
                    اگر (ڈیٹا->کلید_control_esc->func_on_state_change) {
                        ڈیٹا->کلید_control_esc->func_on_state_change(ڈیٹا->کلید_control_esc);
                    }
                }
            } ورنہ اگر ((کلید == XK_Return) || (کلید == XK_KP_Enter)) {
                اگر (ڈیٹا->کلید_control_enter) {
                    اگر (ڈیٹا->کلید_control_enter->func_on_state_change) {
                        ڈیٹا->کلید_control_enter->func_on_state_change(ڈیٹا->کلید_control_enter);
                    }
                }
            } ورنہ اگر (کلید == XK_Tab || کلید == XK_بایاں || کلید == XK_دایاں) {
                اگر (ڈیٹا->focused_control) {
                    ڈیٹا->focused_control->selected = false;
                }
                ڈیٹا->draw = true;
                برائے (ڈیٹا->ev_i = 0; ڈیٹا->ev_i < ڈیٹا->dyn_controls_sz; ڈیٹا->ev_i++) {
                    اگر (ڈیٹا->dyn_controls[ڈیٹا->ev_i] == ڈیٹا->focused_control) {
                        صحیح اگلا_اشاریہ;

                        اگر (کلید == XK_بایاں) {
                            اگلا_اشاریہ = ڈیٹا->ev_i - 1;
                        } ورنہ {
                            اگلا_اشاریہ = ڈیٹا->ev_i + 1;
                        }
                        اگر ((اگلا_اشاریہ >= ڈیٹا->dyn_controls_sz) || (اگلا_اشاریہ < 0)) {
                            اگر (کلید == XK_دایاں || کلید == XK_بایاں) {
                                اگلا_اشاریہ = ڈیٹا->ev_i;
                            } ورنہ {
                                اگلا_اشاریہ = 0;
                            }
                        }
                        ڈیٹا->focused_control = ڈیٹا->dyn_controls[اگلا_اشاریہ];
                        ڈیٹا->focused_control->selected = true;
                        توڑو;
                    }
                }
            }
            توڑو;
        }
    }

    اگر (ڈیٹا->draw) {
        X11_Toolkit_Draw_کھڑکی(ڈیٹا);
    }
}

خالی X11_Toolkit_Do_کھڑکی_Event_Loop(SDL_Toolkit_کھڑکی_X11 *ڈیٹا) {
   جب (!ڈیٹا->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(ڈیٹا->display, &e);
        اگر (ڈیٹا->xsettings) {
            xsettings_client_process_event(ڈیٹا->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(ڈیٹا->display, &e, X11Toolkit_EventTest, (XPointer)ڈیٹا);
        X11_Toolkit_Process_کھڑکی_Events(ڈیٹا, &e);
    }
}


خالی X11_Toolkit_Resize_کھڑکی(SDL_Toolkit_کھڑکی_X11 *ڈیٹا, صحیح w, صحیح h) {
    اگر (!ڈیٹا->pixmap) {
        ڈیٹا->کھڑکی_چوڑائی = w;
        ڈیٹا->کھڑکی_اونچائی = h;
    } ورنہ {
        ڈیٹا->کھڑکی_چوڑائی = SDL_lroundf((w/ڈیٹا->iscale) * ڈیٹا->scale);
        ڈیٹا->کھڑکی_اونچائی = SDL_lroundf((h/ڈیٹا->iscale) * ڈیٹا->scale);
        ڈیٹا->pixmap_چوڑائی = w;
        ڈیٹا->pixmap_اونچائی = h;
        X11_XFreePixmap(ڈیٹا->display, ڈیٹا->drawable);
        X11_Toolkit_Init_کھڑکی_Pixmap(ڈیٹا);
    }

    X11_XResize_کھڑکی(ڈیٹا->display, ڈیٹا->کھڑکی, ڈیٹا->کھڑکی_چوڑائی, ڈیٹا->کھڑکی_اونچائی);
}

ساکن خالی X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->کھڑکی->display, icon_control->icon_char_font);
    SDL_free(control);
}

ساکن خالی X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->کھڑکی->iscale;
    control->rect.h -= 2 * control->کھڑکی->iscale;
    X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x + (2 * control->کھڑکی->iscale), control->rect.y + (2* control->کھڑکی->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    انتخاب (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        حالت SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x+(1* control->کھڑکی->iscale), control->rect.y+(1* control->کھڑکی->iscale), control->rect.w-(2* control->کھڑکی->iscale), control->rect.h-(2* control->کھڑکی->iscale), 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_white.pixel);
                توڑو;
        حالت SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x+(1* control->کھڑکی->iscale), control->rect.y+(1* control->کھڑکی->iscale), control->rect.w-(2* control->کھڑکی->iscale), control->rect.h-(2* control->کھڑکی->iscale), 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_black.pixel);
                توڑو;
        حالت SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x+(1* control->کھڑکی->iscale), control->rect.y+(1* control->کھڑکی->iscale), control->rect.w-(2* control->کھڑکی->iscale), control->rect.h-(2* control->کھڑکی->iscale), 0, 360 * 64);
                X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->xcolor_white.pixel);
                توڑو;
    }
    X11_XSetFont(control->کھڑکی->display, control->کھڑکی->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->کھڑکی->display, control->کھڑکی->drawable, control->کھڑکی->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    اگر (!control->کھڑکی->utf8) {
        X11_XSetFont(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->font_struct->fid);
    }

    control->rect.w += 2 * control->کھڑکی->iscale;
    control->rect.h += 2 * control->کھڑکی->iscale;
}

ساکن خالی X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *بنیاد_control) {
    SDL_ToolkitIconControlX11 *control;
    صحیح icon_char_w;
    صحیح icon_wh;

    control = (SDL_ToolkitIconControlX11 *)بنیاد_control;
    X11_Toolkit_Get_متن_چوڑائی_اونچائی_For_Font(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, تہی);
    بنیاد_control->rect.w = icon_char_w;
    بنیاد_control->rect.h = control->icon_char_h;
    icon_wh = SDL_max(icon_char_w, control->icon_char_h) + SDL_TOOLKIT_X11_ELEMENT_PADDING * 2 * بنیاد_control->کھڑکی->iscale;
    بنیاد_control->rect.w = icon_wh;
    بنیاد_control->rect.h = icon_wh;
    بنیاد_control->rect.y = 0;
    بنیاد_control->rect.x = 0;
    control->icon_char_y = control->icon_char_a + (بنیاد_control->rect.h - control->icon_char_h)/2;
    control->icon_char_x = (بنیاد_control->rect.w - icon_char_w)/2;
    بنیاد_control->rect.w += 2 * بنیاد_control->کھڑکی->iscale;
    بنیاد_control->rect.h += 2 * بنیاد_control->کھڑکی->iscale;
}

ساکن خالی X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *بنیاد_control) {
    SDL_ToolkitIconControlX11 *control;
    حرف *font;

    control = (SDL_ToolkitIconControlX11 *)بنیاد_control;
    X11_XFreeFont(بنیاد_control->کھڑکی->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_سائز * بنیاد_control->کھڑکی->iscale);
    control->icon_char_font = X11_XLoadQueryFont(بنیاد_control->کھڑکی->display, font);
    SDL_free(font);
    اگر (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_سائز * بنیاد_control->کھڑکی->iscale);
        control->icon_char_font = X11_XLoadQueryFont(بنیاد_control->کھڑکی->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, SDL_پیغام_Box_Flags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *بنیاد_control;
    حرف *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(حجم(SDL_ToolkitIconControlX11));
    بنیاد_control = (SDL_ToolkitControlX11 *)control;
    اگر (!control) {
        SDL_سیٹ_Error("Unable to allocate icon control structure");
        واپس تہی;
    }

    /* Fill out struct */
    بنیاد_control->کھڑکی = کھڑکی;
    بنیاد_control->func_draw = X11Toolkit_DrawIconControl;
    بنیاد_control->func_free = X11Toolkit_DestroyIconControl;
    بنیاد_control->func_on_state_change = تہی;
    بنیاد_control->func_calc_سائز = X11Toolkit_CalculateIconControl;
    بنیاد_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    بنیاد_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_معمول;
    بنیاد_control->selected = false;
    بنیاد_control->dynamic = false;
    بنیاد_control->is_default_enter = false;
    بنیاد_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_سائز * کھڑکی->iscale);
    control->icon_char_font = X11_XLoadQueryFont(کھڑکی->display, font);
    SDL_free(font);
    اگر (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_سائز * کھڑکی->iscale);
        control->icon_char_font = X11_XLoadQueryFont(کھڑکی->display, font);
        SDL_free(font);
        اگر (!control->icon_char_font) {
            SDL_free(control);
            واپس تہی;
        }
    }

    /* Set colors */
    انتخاب (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    حالت SDL_MESSAGEBOX_ERROR:
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
        توڑو;
    حالت SDL_MESSAGEBOX_WARNING:
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
        توڑو;
    حالت SDL_MESSAGEBOX_INFORMATION:
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
        توڑو;
    طےشدہ:
        X11_XFreeFont(کھڑکی->display, control->icon_char_font);
        SDL_free(control);
        واپس تہی;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    اگر (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } ورنہ اگر (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } ورنہ {
        control->xcolor_bg_shadow.red = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    اگر (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } ورنہ اگر (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } ورنہ {
        control->xcolor_bg_shadow.green = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    اگر (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } ورنہ اگر (کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } ورنہ {
        control->xcolor_bg_shadow.blue = SDL_clamp(کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(کھڑکی->display, کھڑکی->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(بنیاد_control);

    X11_Toolkit_جوڑو_Control_مقصد_کھڑکی(کھڑکی, بنیاد_control);
    واپس بنیاد_control;
}

bool X11_Toolkit_Notify_Control_کا_سائز_Change(SDL_ToolkitControlX11 *control) {
    اگر (control->func_calc_سائز) {
        control->func_calc_سائز(control);
        واپس true;
    } ورنہ {
        واپس false;
    }
}

ساکن خالی X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11_Toolkit_Get_متن_Elements_Rect(button_control->متن, &button_control->متن_rect);
    اگر (control->do_سائز) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->کھڑکی->iscale + button_control->متن_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->کھڑکی->iscale + button_control->متن_rect.h;
    }
    button_control->متن_rect.x = (control->rect.w - button_control->متن_rect.w)/2;
    button_control->متن_rect.y = (control->rect.h - button_control->متن_rect.h)/2;
}


ساکن خالی X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    /* Draw bevel */
    اگر (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
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
        } ورنہ {
            اگر (control->selected) {
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
            } ورنہ {
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

ساکن خالی X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    اگر (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_ڈیٹا);
    }
}

ساکن خالی X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_Toolkit_Free_متن_Elements(button_control->متن);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, ثابت SDL_پیغام_Box_Button_ڈیٹا *ڈیٹا) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *بنیاد_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(حجم(SDL_ToolkitButtonControlX11));
    بنیاد_control = (SDL_ToolkitControlX11 *)control;
    اگر (!control) {
        SDL_سیٹ_Error("Unable to allocate button control structure");
        واپس تہی;
    }
    بنیاد_control->کھڑکی = کھڑکی;
    بنیاد_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_معمول;
    بنیاد_control->func_calc_سائز = X11Toolkit_CalculateButtonControl;
    بنیاد_control->func_draw = X11Toolkit_DrawButtonControl;
    بنیاد_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    بنیاد_control->func_free = X11Toolkit_DestroyButtonControl;
    بنیاد_control->func_on_scale_change = تہی;
    بنیاد_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_معمول;
    بنیاد_control->selected = false;
    بنیاد_control->dynamic = true;
    بنیاد_control->is_default_enter = false;
    بنیاد_control->is_default_esc = false;
    اگر (ڈیٹا->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        بنیاد_control->is_default_esc = true;
    }
    اگر (ڈیٹا->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        بنیاد_control->is_default_enter = true;
        بنیاد_control->selected = true;
    }
    control->cb = تہی;
    control->ڈیٹا = ڈیٹا;
#اگر_تعریف_شدہ HAVE_FRIBIDI_H
    control->متن = X11_Toolkit_Make_متن_Elements(بنیاد_control->کھڑکی, (حرف *)control->ڈیٹا->متن, SDL_strlen(control->ڈیٹا->متن), تہی);
#ورنہ 
    control->متن = X11_Toolkit_Make_متن_Elements(بنیاد_control->کھڑکی, (حرف *)control->ڈیٹا->متن, SDL_strlen(control->ڈیٹا->متن));
#اگر_ختم
    X11_Toolkit_Shape_متن_Elements(بنیاد_control->کھڑکی, control->متن);
    
    بنیاد_control->do_سائز = true;
    X11Toolkit_CalculateButtonControl(بنیاد_control);
    بنیاد_control->do_سائز = false;

    X11_Toolkit_جوڑو_Control_مقصد_کھڑکی(کھڑکی, بنیاد_control);
    واپس بنیاد_control;
}

خالی X11_Toolkit_رجسٹر_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, خالی *ڈیٹا, خالی (*cb)(ساخت SDL_ToolkitControlX11 *, خالی *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_ڈیٹا = ڈیٹا;
    button_control->cb = cb;
}

ثابت SDL_پیغام_Box_Button_ڈیٹا *X11_Toolkit_Get_Button_Control_ڈیٹا(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    واپس button_control->ڈیٹا;
}

خالی X11_Toolkit_Destroy_کھڑکی(SDL_Toolkit_کھڑکی_X11 *ڈیٹا) {
    صحیح i;

    اگر (!ڈیٹا) {
        واپس;
    }

#اگر SDL_GRAB
    اگر (ڈیٹا->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_MENU || ڈیٹا->منوال== SDL_TOOLKIT_کھڑکی_منوال_X11_TOOLTIP) {
        X11_XUngrab_اشارہ_گر(ڈیٹا->display, Current_وقت);
        X11_XUngrabKeyboard(ڈیٹا->display, Current_وقت);
    }
#اگر_ختم

    برائے (i = 0; i < ڈیٹا->controls_sz; i++) {
        اگر (ڈیٹا->controls[i]->func_free) {
            ڈیٹا->controls[i]->func_free(ڈیٹا->controls[i]);
        }
    }
    SDL_free(ڈیٹا->controls);
    SDL_free(ڈیٹا->dyn_controls);

    اگر (ڈیٹا->popup_windows) {
        SDL_ListClear(&ڈیٹا->popup_windows);
    }

    اگر (ڈیٹا->pixmap) {
        X11_XFreePixmap(ڈیٹا->display, ڈیٹا->drawable);
    }

#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
    اگر (ڈیٹا->pixmap && ڈیٹا->shm) {
        X11_XShmDetach(ڈیٹا->display, &ڈیٹا->shm_info);
        اگر (!ڈیٹا->shm_pixmap) {
            XDestroyImage(ڈیٹا->image);
        }
        shmdt(ڈیٹا->shm_info.shmaddr);
    }
#اگر_ختم

#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
    اگر (ڈیٹا->font_سیٹ) {
        X11_XFree_Font_سیٹ(ڈیٹا->display, ڈیٹا->font_سیٹ);
        ڈیٹا->font_سیٹ = تہی;
    }
#اگر_ختم

    اگر (ڈیٹا->font_struct) {
        X11_XFreeFont(ڈیٹا->display, ڈیٹا->font_struct);
        ڈیٹا->font_struct = تہی;
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
    اگر (SDL_X11_HAVE_XDBE && ڈیٹا->xdbe && !ڈیٹا->pixmap) {
        X11_Xdbe_Deallocate_عقب_بفر_Name(ڈیٹا->display, ڈیٹا->buf);
    }
#اگر_ختم

    اگر (ڈیٹا->xsettings) {
        xsettings_client_destroy(ڈیٹا->xsettings);
    }

    X11_XFreeGC(ڈیٹا->display, ڈیٹا->ctx);

    اگر (ڈیٹا->display) {
        اگر (ڈیٹا->کھڑکی != None) {
            X11_XWithdraw_کھڑکی(ڈیٹا->display, ڈیٹا->کھڑکی, ڈیٹا->screen);
            X11_XDestroy_کھڑکی(ڈیٹا->display, ڈیٹا->کھڑکی);
            ڈیٹا->کھڑکی = None;
        }

        اگر (ڈیٹا->display_close) {
            X11_XCloseDisplay(ڈیٹا->display);
        }
        ڈیٹا->display = تہی;
    }

#اگر SDL_سیٹ_LOCALE
    اگر (ڈیٹا->origlocale && (ڈیٹا->منوال == SDL_TOOLKIT_کھڑکی_منوال_X11_DIALOG)) {
        (خالی)setlocale(LC_ALL, ڈیٹا->origlocale);
        SDL_free(ڈیٹا->origlocale);
    }
#اگر_ختم

#اگر_تعریف_شدہ HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(ڈیٹا->fribidi);
#اگر_ختم

#اگر_تعریف_شدہ HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(ڈیٹا->th);
#اگر_ختم

    SDL_free(ڈیٹا);
}

ساکن صحیح X11_Toolkit_گنتی_سطریں_کا_متن(ثابت حرف *متن)
{
    صحیح نتیجہ = 0;
    جب (متن && *متن) {
        ثابت حرف *lf = SDL_strchr(متن, '\n');
        نتیجہ++; // even without an endline, this counts as a line.
        متن = lf ? lf + 1 : تہی;
    }
    واپس نتیجہ;
}

ساکن خالی X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحیح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->کھڑکی->display, control->کھڑکی->ctx, control->کھڑکی->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    برائے (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Draw_متن_Elements(control->کھڑکی, label_control->سطریں[i].متن, control->rect.x + label_control->سطریں[i].rect.x, control->rect.y + label_control->سطریں[i].rect.y);
    }
}

ساکن خالی X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحیح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    برائے (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Free_متن_Elements(label_control->سطریں[i].متن);
    }
    SDL_free(label_control->سطریں);
    SDL_free(label_control);
}

ساکن خالی X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *بنیاد_control) {
    SDL_ToolkitLabelControlX11 *control;
    صحیح i;

    control = (SDL_ToolkitLabelControlX11 *)بنیاد_control;
    
    اگر (بنیاد_control->do_سائز) {
        بنیاد_control->rect.w = 0;
        بنیاد_control->rect.h = 0;
    }
    
    برائے (i = 0; i < control->sz; i++) {
        صحیح font_h;
        
        font_h = X11_Toolkit_Get_متن_Elements_Rect(control->سطریں[i].متن, &control->سطریں[i].rect);
        
        اگر (بنیاد_control->do_سائز) {
            بنیاد_control->rect.w = SDL_max(بنیاد_control->rect.w, control->سطریں[i].rect.w);
        }
        
        اگر (i > 0) {
            control->سطریں[i].rect.y = font_h + control->سطریں[i - 1].rect.y;
        } ورنہ {
            control->سطریں[i].rect.y = 0;
        }
    }

#اگر_تعریف_شدہ HAVE_FRIBIDI_H
    اگر (بنیاد_control->کھڑکی->fribidi) {
        FriBidiParType پہلا_ndn_dir;
        صحیح آخری_ndn;
    
        پہلا_ndn_dir = FRIBIDI_PAR_LTR;
        برائے (i = 0; i < control->sz; i++) {
            اگر (control->سطریں[i].par != FRIBIDI_PAR_ON) {
                پہلا_ndn_dir = control->سطریں[i].par;
            }
        }

        آخری_ndn = -1;
        برائے (i = 0; i < control->sz; i++) {
            انتخاب (control->سطریں[i].par) {
                حالت FRIBIDI_PAR_LTR:
                    control->سطریں[i].rect.x = 0;
                    آخری_ndn = i;
                    توڑو;
                حالت FRIBIDI_PAR_RTL:
                    control->سطریں[i].rect.x = بنیاد_control->rect.w - control->سطریں[i].rect.w;
                    آخری_ndn = i;
                    توڑو;
                طےشدہ:
                    اگر (آخری_ndn != -1) {
                        اگر (control->سطریں[آخری_ndn].par == FRIBIDI_PAR_RTL) {
                            control->سطریں[i].rect.x = بنیاد_control->rect.w - control->سطریں[i].rect.w;
                        } ورنہ {
                            control->سطریں[i].rect.x = 0;
                        }
                    } ورنہ {
                        اگر (پہلا_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->سطریں[i].rect.x = بنیاد_control->rect.w - control->سطریں[i].rect.w;
                        } ورنہ {
                            control->سطریں[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#اگر_ختم
    
    اگر (بنیاد_control->do_سائز && control->sz) {
        بنیاد_control->rect.h = control->سطریں[control->sz - 1].rect.y + control->سطریں[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_کھڑکی_X11 *کھڑکی, حرف *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *بنیاد_control;
    صحیح i;
    
    اگر (!utf8) {
        واپس تہی;
    }
 
    اگر (!SDL_strcmp(utf8, "")) {
        واپس تہی;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(حجم(SDL_ToolkitLabelControlX11));
    بنیاد_control = (SDL_ToolkitControlX11 *)control;
    اگر (!control) {
        SDL_سیٹ_Error("Unable to allocate label control structure");
        واپس تہی;
    }
    بنیاد_control->کھڑکی = کھڑکی;
    بنیاد_control->func_draw = X11Toolkit_DrawLabelControl;
    بنیاد_control->func_on_state_change = تہی;
    بنیاد_control->func_calc_سائز = X11Toolkit_CalculateLabelControl;
    بنیاد_control->func_free  = X11Toolkit_DestroyLabelControl;
    بنیاد_control->func_on_scale_change = تہی;
    بنیاد_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_معمول;
    بنیاد_control->selected = false;
    بنیاد_control->dynamic = false;
    بنیاد_control->rect.w = 0;
    بنیاد_control->rect.h = 0;
    بنیاد_control->is_default_enter = false;
    بنیاد_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_گنتی_سطریں_کا_متن(utf8);
    control->سطریں = SDL_calloc(control->sz, حجم(SDL_Toolkit_Label_Control_سطر_X11));
    برائے (i = 0; i < control->sz; i++) {
        ثابت حرف *lf = SDL_strchr(utf8, '\n');
        ثابت صحیح لمبائی = lf ? (lf - utf8) : SDL_strlen(utf8);
        صحیح sz;
        
        sz = لمبائی;
        اگر (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#اگر_تعریف_شدہ HAVE_FRIBIDI_H
        control->سطریں[i].متن = X11_Toolkit_Make_متن_Elements(بنیاد_control->کھڑکی, (حرف *)utf8, sz, &control->سطریں[i].par);
#ورنہ 
        control->سطریں[i].متن = X11_Toolkit_Make_متن_Elements(بنیاد_control->کھڑکی, (حرف *)utf8, sz);
#اگر_ختم
        X11_Toolkit_Shape_متن_Elements(بنیاد_control->کھڑکی, control->سطریں[i].متن);

        utf8 += لمبائی + 1;
        اگر (!lf) {
            توڑو;
        }
    }

    بنیاد_control->do_سائز = true;
    X11Toolkit_CalculateLabelControl(بنیاد_control);
    بنیاد_control->do_سائز = false;
    X11_Toolkit_جوڑو_Control_مقصد_کھڑکی(کھڑکی, بنیاد_control);

    واپس بنیاد_control;
}

صحیح X11_Toolkit_Get_Label_Control_پہلا_سطر_اونچائی(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    واپس label_control->سطریں[0].rect.h;
}

خالی X11_Toolkit_Signal_کھڑکی_Close(SDL_Toolkit_کھڑکی_X11 *ڈیٹا) {
    ڈیٹا->close = true;
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
