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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11

#ضمن "../../SDL_list.h"
#ضمن "SDL_x11video.h"
#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
#ضمن "../../core/linux/SDL_system_theme.h"
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل HAVE_FRIBIDI_H
#ضمن "../../core/unix/SDL_fribidi.h"
#جيڪڏهن_پورو
#ضمن "SDL_x11dyn.h"
#ضمن "SDL_x11toolkit.h"
#ضمن "SDL_x11settings.h"
#ضمن "SDL_x11modes.h"
#ضمن "xsettings-client.h"
#ضمن <X11/keysym.h>
#ضمن <locale.h>

#وصف_ڪريو SDL_سيٽ_LOCALE 1
#وصف_ڪريو SDL_GRAB 1

تعريفنوع تعداد SDL_Toolkit_متن_Type_X11
{
    SDL_TOOLKIT_متن_TYPE_X11_GENERIC,
    SDL_TOOLKIT_متن_TYPE_X11_THAI
} SDL_Toolkit_متن_Type_X11;

#جيڪڏهن_وصف_ٿيل HAVE_LIBTHAI_H
تعريفنوع بنية SDL_ToolkitThaiOverlayX11
{
    bool چوٽي;
    حرف *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#جيڪڏهن_پورو

تعريفنوع بنية SDL_Toolkit_متن_Element_X11
{
    SDL_Toolkit_متن_Type_X11 type;
    حرف *str;
    size_t sz;
    SDL_Rect rect;
    صحيح font_h;
    فراغ (*str_free)(فراغ *);
#جيڪڏهن_وصف_ٿيل HAVE_LIBTHAI_H
    SDL_List_ڳنڍ *thai_overlays;
#جيڪڏهن_پورو
} SDL_Toolkit_متن_Element_X11;

تعريفنوع بنية SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 والد;

    /* Icon type */
    SDL_پيغام_Box_Flags flags;
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
    SDL_ToolkitControlX11 والد;

    /*معلومات*/
    ثابت SDL_پيغام_Box_Button_معلومات *معلومات;

    /*متن*/
    SDL_List_ڳنڍ *متن;
    SDL_Rect متن_rect;
    
    /* Callback */
    فراغ *cb_معلومات;
    فراغ (*cb)(بنية SDL_ToolkitControlX11 *, فراغ *);
} SDL_ToolkitButtonControlX11;

تعريفنوع بنية SDL_Toolkit_Label_Control_سٽ_X11
{
    SDL_List_ڳنڍ *متن;
    SDL_Rect rect;
#جيڪڏهن_وصف_ٿيل HAVE_FRIBIDI_H
    FriBidiParType par;
#جيڪڏهن_پورو
} SDL_Toolkit_Label_Control_سٽ_X11;

تعريفنوع بنية SDL_ToolkitLabelControlX11
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
    SDL_Toolkit_Label_Control_سٽ_X11 *سٽون;
    size_t sz;
} SDL_ToolkitLabelControlX11;

تعريفنوع بنية SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 والد;

    SDL_List_ڳنڍ *menu_شيون;
} SDL_ToolkitMenuBarControlX11;

تعريفنوع بنية SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 والد;

    SDL_List_ڳنڍ *menu_شيون;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
ساكن ثابت حرف *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#وصف_ڪريو G_ICONFONT_سائيز 22

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
#وصف_ڪريو G_TOOLKITFONT_سائيز 140

ساكن ثابت SDL_پيغام_Box_Color g_default_colors[SDL_MESSAGEBOX_COLOR_ڳڻپ] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
ساكن ثابت SDL_پيغام_Box_Color g_default_colors_dark[SDL_MESSAGEBOX_COLOR_ڳڻپ] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#إذا 0
ساكن ثابت SDL_پيغام_Box_Color g_default_colors_dark_مٿاهون_contrast[SDL_MESSAGEBOX_COLOR_ڳڻپ] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

ساكن ثابت SDL_پيغام_Box_Color g_default_colors_light_مٿاهون_contrast[SDL_MESSAGEBOX_COLOR_ڳڻپ] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#جيڪڏهن_پورو

#جيڪڏهن_پورو

ساكن صحيح g_shm_error;
ساكن صحيح (*g_old_error_handler)(Display *, XErrorEvent *) = عدم;

ساكن صحيح X11_Toolkit_Shared_يادگيري_Error_Handler(Display *d, XErrorEvent *e)
{
    إذا (e->error_ڪوڊ == BadAccess || e->error_ڪوڊ == BadRequest) {
        g_shm_error = True;
        أرجع 0;
    }
    أرجع g_old_error_handler(d, e);
}

ساكن فراغ X11_Toolkit_Init_دري_Pixmap(SDL_Toolkit_دري_X11 *معلومات) {
    إذا (معلومات->pixmap) {
#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري
        إذا (!معلومات->shm_pixmap) {
            معلومات->drawable = X11_XCreatePixmap(معلومات->display, معلومات->دري, معلومات->pixmap_ويڪر, معلومات->pixmap_اوچائي, معلومات->اونهائي_2);
        }
#وإلا
        معلومات->drawable = X11_XCreatePixmap(معلومات->display, معلومات->دري, معلومات->pixmap_ويڪر, معلومات->pixmap_اوچائي, معلومات->اونهائي_2);
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري
        إذا (معلومات->shm) {
            معلومات->image = X11_XShmCreateImage(معلومات->display, معلومات->visual, معلومات->اونهائي_2, ZPixmap, عدم, &معلومات->shm_info, معلومات->pixmap_ويڪر, معلومات->pixmap_اوچائي);
            إذا (معلومات->image) {
                معلومات->shm_بائيٽون_في_سٽ = معلومات->image->بائيٽون_في_سٽ;

                معلومات->shm_info.shmid = shmget(IPC_ذاتي, معلومات->image->بائيٽون_في_سٽ * معلومات->image->اوچائي, IPC_CREAT | 0777);
                إذا (معلومات->shm_info.shmid < 0) {
                    XDestroyImage(معلومات->image);
                    معلومات->image = عدم;
                    معلومات->shm = false;
                    أرجع;
                }

                معلومات->shm_info.readOnly = False;
                معلومات->shm_info.shmaddr = معلومات->image->معلومات = (حرف *)shmat(معلومات->shm_info.shmid, عدم, 0);
                إذا (((نشانوارو حرف *)معلومات->shm_info.shmaddr) == (نشانوارو حرف *)-1) {
                    XDestroyImage(معلومات->image);
                    معلومات->shm = false;
                    معلومات->image = عدم;
                    أرجع;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11_Toolkit_Shared_يادگيري_Error_Handler);
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
                    معلومات->drawable = X11_XShmCreatePixmap(معلومات->display, معلومات->دري, معلومات->shm_info.shmaddr, &معلومات->shm_info, معلومات->pixmap_ويڪر, معلومات->pixmap_اوچائي, معلومات->اونهائي_2);
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
#جيڪڏهن_پورو
    }
}

ساكن فراغ X11_Toolkit_Init_دري_Fonts(SDL_Toolkit_دري_X11 *دري)
{    
    دري->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    دري->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    دري->utf8 = true;
    دري->font_سيٽ = عدم;
    إذا (SDL_X11_HAVE_UTF8) {
        حرف **missing = عدم;
        صحيح انگ_missing = 0;
        صحيح i_font;
        دري->font_struct = عدم;
        لكل (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            حرف *font;

            إذا (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_ڀريو_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_سائيز * دري->iscale);
                دري->font_سيٽ = X11_XCreate_Font_سيٽ(دري->display, font, &missing, &انگ_missing, عدم);
                SDL_free(font);

                إذا (!دري->font_سيٽ) {
                    إذا (دري->scale != 0 && دري->iscale > 0) {
                        دري->iscale = (صحيح)SDL_ceilf(دري->scale);
                        دري->scale = 0;
                    } وإلا {
                        دري->iscale--;
                    }
                    اذهب try_ڀريو_font;
                }
            } وإلا {
                دري->font_سيٽ = X11_XCreate_Font_سيٽ(دري->display, g_ToolkitFont[i_font], &missing, &انگ_missing, عدم);
            }

            إذا (missing) {
                X11_XFreeStringList(missing);
            }

            إذا (دري->font_سيٽ) {
                اكسر;
            }
        }

        إذا (!دري->font_سيٽ) {
            اذهب ڀريو_font_traditional;
        } وإلا {
            XFontStruct **font_structs;
            حرف **font_نالا;
            صحيح font_sz;
            صحيح i;
            
#جيڪڏهن_وصف_ٿيل HAVE_FRIBIDI_H
            دري->do_shaping = !X11_XContextDependentDrawing(دري->font_سيٽ);
#جيڪڏهن_پورو
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFonts_جو_Font_سيٽ(دري->font_سيٽ, &font_structs, &font_نالا);
            لكل (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                إذا (SDL_strstr(font_نالا[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } وإلا إذا (SDL_strstr(font_نالا[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } وإلا إذا (SDL_strstr(font_نالا[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } وإلا إذا (SDL_strstr(font_نالا[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } وإلا إذا (SDL_strstr(font_نالا[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                إذا (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(دري->display, font_نالا[i]);
                    إذا (font_struct) {
                        إذا (font_struct->في_char) {
                            صحيح glyphs_sz;
                            صحيح j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            لكل (j = 0; j < glyphs_sz; j++) {
                                إذا (font_struct->في_char[j].lbearing < 0) {
                                    دري->thai_font = SDL_TOOLKIT_THAI_FONT_X11_وٿي;
                                }
                            }
                        }
                        X11_XFreeFont(دري->display, font_struct);
                    }
                }
                
                دري->thai_encoding = thai_encoding;
            } 
        }
    } وإلا
#جيڪڏهن_پورو
    {
        حرف *font;

        ڀريو_font_traditional:
        دري->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_سائيز * دري->iscale);
        دري->font_struct = X11_XLoadQueryFont(دري->display, font);
        SDL_free(font);
        إذا (!دري->font_struct) {
            إذا (دري->iscale > 0) {
                إذا (دري->scale != 0) {
                    دري->iscale = (صحيح)SDL_ceilf(دري->scale);
                    دري->scale = 0;
                } وإلا {
                    دري->iscale--;
                }
                اذهب ڀريو_font_traditional;
            } وإلا {
                دري->font_struct = X11_XLoadQueryFont(دري->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

ساكن فراغ X11Toolkit_SettingsNotify(ثابت حرف *name, XSettingsAction action, XSettingsSetting *setting, فراغ *معلومات)
{
    SDL_Toolkit_دري_X11 *دري;
    صحيح i;

    دري = معلومات;

    إذا (دري->xsettings_پهريون_وقت) {
        أرجع;
    }

    إذا (SDL_strcmp(name, SDL_XSETTINGS_GDK_دري_SCALING_ضرب_ڪندڙ) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_تياري = false;
        bool pixmap_already_تياري = false;

        إذا (دري->pixmap) {
            pixmap_already_تياري = true;
        } وإلا {
            dbe_already_تياري = true;
        }

        /* set scale vars */
        دري->scale = X11_GetGlobalContentScale(دري->display, دري->xsettings);
        دري->iscale = (صحيح)SDL_ceilf(دري->scale);
        إذا (دري->scale < 1) {
            دري->scale = 1;
        }
        إذا (SDL_roundf(دري->scale) == دري->scale) {
            دري->scale = 0;
        }

        /* setup fonts */
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
        إذا (دري->font_سيٽ) {
            X11_XFree_Font_سيٽ(دري->display, دري->font_سيٽ);
        }
#جيڪڏهن_پورو
        إذا (دري->font_struct) {
            X11_XFreeFont(دري->display, دري->font_struct);
        }

        X11_Toolkit_Init_دري_Fonts(دري);

        /* set up window */
        إذا (دري->scale != 0) {
            دري->دري_ويڪر = SDL_lroundf((دري->دري_ويڪر/دري->iscale) * دري->scale);
            دري->دري_اوچائي = SDL_lroundf((دري->دري_اوچائي/دري->iscale) * دري->scale);
            دري->pixmap_ويڪر = دري->دري_ويڪر;
            دري->pixmap_اوچائي = دري->دري_اوچائي;
            دري->pixmap = true;
        } وإلا {
            دري->pixmap = false;
        }

        إذا (دري->pixmap) {
            إذا (!pixmap_already_تياري) {
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XDBE
                إذا (SDL_X11_HAVE_XDBE && دري->xdbe) {
                    X11_Xdbe_Deallocate_پٺ_بفر_Name(دري->display, دري->buf);
                }
#جيڪڏهن_پورو
            }
            X11_XFreePixmap(دري->display, دري->drawable);
            X11_Toolkit_Init_دري_Pixmap(دري);
        } وإلا {
            إذا (!dbe_already_تياري) {
                X11_XFreePixmap(دري->display, دري->drawable);
#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري
                إذا (دري->image) {
                    XDestroyImage(دري->image);
                    دري->image = عدم;
                }
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XDBE
                إذا (SDL_X11_HAVE_XDBE && دري->xdbe) {
                    دري->buf = X11_Xdbe_Allocate_پٺ_بفر_Name(دري->display, دري->دري, XdbeUndefined);
                    دري->drawable = دري->buf;
                }
#جيڪڏهن_پورو
            }
        }

        /* notify controls */
        لكل (i = 0; i < دري->controls_sz; i++) {
            دري->controls[i]->do_سائيز = true;

            إذا (دري->controls[i]->func_on_scale_change) {
                دري->controls[i]->func_on_scale_change(دري->controls[i]);
            }

            إذا (دري->controls[i]->func_calc_سائيز) {
                دري->controls[i]->func_calc_سائيز(دري->controls[i]);
            }

            دري->controls[i]->do_سائيز = false;
        }

        /* notify cb */
        إذا (دري->cb_on_scale_change) {
            دري->cb_on_scale_change(دري, دري->cb_معلومات);
        }

        /* update ev scales */
        إذا (!دري->pixmap) {
            دري->ev_scale = دري->ev_iscale = 1;
        } وإلا {
            دري->ev_scale = دري->scale;
            دري->ev_iscale = دري->iscale;
        }
    }
}

ساكن فراغ X11_Toolkit_Get_متن_ويڪر_اوچائي_For_Font(XFontStruct *font, ثابت حرف *str, صحيح nbytes, صحيح *pwidth, صحيح *pheight, صحيح *ascent, صحيح *font_اوچائي)
{
    XCharStruct متن_structure;
    صحيح font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &متن_structure);
    *pwidth = متن_structure.ويڪر;
    *pheight = متن_structure.ascent + متن_structure.descent;
    *ascent = متن_structure.ascent;
    إذا (font_اوچائي) {
       *font_اوچائي = font_ascent + font_descent;
    }
}

ساكن فراغ X11_Toolkit_Get_متن_ويڪر_اوچائي(SDL_Toolkit_دري_X11 *معلومات, ثابت حرف *str, صحيح nbytes, صحيح *pwidth, صحيح *pheight, صحيح *ascent, صحيح *descent, صحيح *font_اوچائي)
{
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    إذا (معلومات->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8_متن_Extents(معلومات->font_سيٽ, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.ويڪر;
        *pheight = overall_logical.اوچائي;
        *ascent = -overall_logical.y;
        *descent = overall_logical.اوچائي - *ascent;

        إذا (font_اوچائي) {
            XFont_سيٽ_Extents *extents;

            extents = X11_XExtents_جو_Font_سيٽ(معلومات->font_سيٽ);
            *font_اوچائي = extents->max_logical_extent.اوچائي;
        }
    } وإلا
#جيڪڏهن_پورو
    {
        XCharStruct متن_structure;
        صحيح font_direction, font_ascent, font_descent;
        X11_XTextExtents(معلومات->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &متن_structure);
        *pwidth = متن_structure.ويڪر;
        *pheight = متن_structure.ascent + متن_structure.descent;
        *ascent = متن_structure.ascent;
        *descent = متن_structure.descent;

        إذا (font_اوچائي) {
            *font_اوچائي = font_ascent + font_descent;
        }
    }
}

#جيڪڏهن_وصف_ٿيل HAVE_FRIBIDI_H
SDL_List_ڳنڍ *X11_Toolkit_Make_متن_Elements(SDL_Toolkit_دري_X11 *معلومات, حرف *txt, size_t sz, FriBidiParType *par)
#وإلا
SDL_List_ڳنڍ *X11_Toolkit_Make_متن_Elements(SDL_Toolkit_دري_X11 *معلومات, حرف *txt, size_t sz)
#جيڪڏهن_پورو
{
    SDL_List_ڳنڍ *list;
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
    
#جيڪڏهن_وصف_ٿيل HAVE_FRIBIDI_H
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
#جيڪڏهن_پورو        

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
            
            SDL_List_جوڙيو(&list, element);
            
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

فراغ X11_Toolkit_Shape_متن_Elements(SDL_Toolkit_دري_X11 *معلومات, SDL_List_ڳنڍ *list)
{
    SDL_List_ڳنڍ *cursor;
    SDL_Toolkit_متن_Element_X11 *prev;
    صحيح عارضي;
    
    /* Shape and calculate bounding box */
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->داخلا;
#جيڪڏهن_وصف_ٿيل HAVE_LIBTHAI_H
        element->thai_overlays = عدم;
#جيڪڏهن_پورو
        إذا (element->type == SDL_TOOLKIT_متن_TYPE_X11_THAI) {
            إذا (معلومات->thai_font == SDL_TOOLKIT_THAI_FONT_X11_وٿي) {
                X11_Toolkit_Get_متن_ويڪر_اوچائي(معلومات, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضي, عدم);
            } وإلا {
#جيڪڏهن_وصف_ٿيل HAVE_LIBTHAI_H
                إذا (معلومات->th) {
                    بنية thcell_t *cells;
                    حرف *tis_str;
                    حرف *بنياد_tis_str;
                    size_t cells_sz;
                    size_t بنياد_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, حجم(بنية thcell_t));
                    معلومات->th->make_cells((ثابت thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    بنياد_tis_str_sz = cells_sz;
                    بنياد_tis_str = SDL_malloc(بنياد_tis_str_sz + 1);
                    لكل (عارضي = 0; عارضي < cells_sz; عارضي++) {
                        بنياد_tis_str[عارضي] = cells[عارضي].بنياد;
                        
                        إذا (cells[عارضي].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            حرف *pre;
                            صحيح temp2;
                            
                            overlay = SDL_malloc(حجم(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", بنياد_tis_str, عارضي);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت حرف *)&cells[عارضي].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->چوٽي = false;
                            X11_Toolkit_Get_متن_ويڪر_اوچائي(معلومات, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, عدم);
                            X11_Toolkit_Get_متن_ويڪر_اوچائي(معلومات, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, عدم);
                            SDL_List_جوڙيو(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        إذا (cells[عارضي].چوٽي) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            حرف *pre;
                            صحيح temp2;
                            
                            overlay = SDL_malloc(حجم(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", بنياد_tis_str, عارضي);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت حرف *)&cells[عارضي].چوٽي, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->چوٽي = true;
                            X11_Toolkit_Get_متن_ويڪر_اوچائي(معلومات, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, عدم);
                            X11_Toolkit_Get_متن_ويڪر_اوچائي(معلومات, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, عدم);
                            SDL_List_جوڙيو(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    بنياد_tis_str[بنياد_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", بنياد_tis_str, بنياد_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11_Toolkit_Get_متن_ويڪر_اوچائي(معلومات, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضي, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(بنياد_tis_str);
                }
#وإلا
                X11_Toolkit_Get_متن_ويڪر_اوچائي(معلومات, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضي, &element->font_h);
#جيڪڏهن_پورو            
            }
        } وإلا {
            X11_Toolkit_Get_متن_ويڪر_اوچائي(معلومات, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &عارضي, &element->font_h);
        }
        
        cursor = cursor->ايندڙ;
    }
    
    /* Add offsets */
    prev = عدم;
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->داخلا;        
        إذا (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } وإلا {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->ايندڙ;
    }
}


فراغ X11_Toolkit_Draw_متن_Elements(SDL_Toolkit_دري_X11 *معلومات, SDL_List_ڳنڍ *list, صحيح x, صحيح y)
{
    SDL_List_ڳنڍ *cursor;
    
    cursor = list;
    
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->داخلا;
        إذا (element->type == SDL_TOOLKIT_متن_TYPE_X11_THAI) {
            إذا (معلومات->thai_font == SDL_TOOLKIT_THAI_FONT_X11_وٿي) {
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
                إذا (معلومات->utf8) {
                    X11_Xutf8DrawString(معلومات->display, معلومات->drawable, معلومات->font_سيٽ, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } وإلا
#جيڪڏهن_پورو
                {
                    X11_XDrawString(معلومات->display, معلومات->drawable, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } وإلا {    
#جيڪڏهن_وصف_ٿيل HAVE_LIBTHAI_H
                SDL_List_ڳنڍ *overlay_cursor;
                    
                /* Draw the base string */
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
                إذا (معلومات->utf8) {
                    X11_Xutf8DrawString(معلومات->display, معلومات->drawable, معلومات->font_سيٽ, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } وإلا
#جيڪڏهن_پورو
                {
                    X11_XDrawString(معلومات->display, معلومات->drawable, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                طالما (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->داخلا;
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
                    إذا (معلومات->utf8) {
                        X11_Xutf8DrawString(معلومات->display, معلومات->drawable, معلومات->font_سيٽ, معلومات->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } وإلا
#جيڪڏهن_پورو
                    {
                        X11_XDrawString(معلومات->display, معلومات->drawable, معلومات->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->ايندڙ;
                }
#جيڪڏهن_پورو                
            }
        } وإلا {
#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
            إذا (معلومات->utf8) {
                X11_Xutf8DrawString(معلومات->display, معلومات->drawable, معلومات->font_سيٽ, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } وإلا
#جيڪڏهن_پورو
            {
                X11_XDrawString(معلومات->display, معلومات->drawable, معلومات->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->ايندڙ;
    }
}

صحيح X11_Toolkit_Get_متن_Elements_Rect(SDL_List_ڳنڍ *list, SDL_Rect *ٻاهريون)
{
    SDL_List_ڳنڍ *cursor;
    صحيح ret;
    
    ret = 0;
    ٻاهريون->x = ٻاهريون->y = 0;
    ٻاهريون->w = ٻاهريون->h = 0;
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->داخلا;
        
        ٻاهريون->w += element->rect.w;
        ٻاهريون->h = SDL_max(ٻاهريون->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->ايندڙ;
    }
    
    أرجع ret;
}

فراغ X11_Toolkit_Free_متن_Elements_List_Contents(SDL_List_ڳنڍ *list)
{
    SDL_List_ڳنڍ *cursor;
    
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
#جيڪڏهن_وصف_ٿيل HAVE_LIBTHAI_H
        SDL_List_ڳنڍ *overlay_cursor;
#جيڪڏهن_پورو

        element = cursor->داخلا;
        
        إذا (element->str_free) {
            element->str_free(element->str);
        }
        
#جيڪڏهن_وصف_ٿيل HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        طالما (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->داخلا;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->ايندڙ;
        }
        SDL_ListClear(&element->thai_overlays);
#جيڪڏهن_پورو
        
        SDL_free(element);
        
        cursor = cursor->ايندڙ;
    }
}

#وصف_ڪريو X11_Toolkit_Free_متن_Elements(x) X11_Toolkit_Free_متن_Elements_List_Contents(x); SDL_ListClear(&x)
 
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

SDL_Toolkit_دري_X11 *X11_Toolkit_Create_دري_Struct(SDL_دري *والد, SDL_Toolkit_دري_X11 *tkparent, SDL_Toolkit_دري_گهڻائي_X11 گهڻائي, ثابت SDL_پيغام_Box_Color *colorhints, bool create_new_display)
{
    SDL_Toolkit_دري_X11 *دري;
    صحيح i;
#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#جيڪڏهن_پورو
    #وصف_ڪريو ErrorFreeRetNull(x, y) SDL_سيٽ_Error(x); SDL_free(y); أرجع عدم
    #وصف_ڪريو ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_سيٽ_Error(x, y); SDL_free(z); أرجع عدم

    إذا (!SDL_X11_ڀريو_Symbols()) {
        أرجع عدم;
    }

    // This code could get called from multiple threads maybe?
    X11_XInit_ڌاڳا();

    دري = (SDL_Toolkit_دري_X11 *)SDL_malloc(حجم(SDL_Toolkit_دري_X11));
    إذا (!دري) {
        SDL_سيٽ_Error("Unable to allocate toolkit window structure");
        أرجع عدم;
    }

    دري->گهڻائي = گهڻائي;
    دري->tk_والد = tkparent;

#إذا SDL_سيٽ_LOCALE
    إذا (گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_DIALOG) {
        دري->origlocale = setlocale(LC_ALL, عدم);
        إذا (دري->origlocale) {
            دري->origlocale = SDL_strdup(دري->origlocale);
            إذا (!دري->origlocale) {
                SDL_free(دري);
                أرجع عدم;
            }
            (فراغ)setlocale(LC_ALL, "");
        }
    }
#جيڪڏهن_پورو

    دري->والد_device = عدم;
    إذا (create_new_display) {
        دري->display = X11_XOpenDisplay(عدم);
        دري->display_close = true;
        إذا (!دري->display) {
            ErrorFreeRetNull("Couldn't open X11 display", دري);
        }
    } وإلا {
        إذا (والد) {
            دري->والد_device = SDL_GetVideoDevice();
            دري->display = دري->والد_device->اندروني->display;
            دري->display_close = false;
        } وإلا إذا (tkparent) {
            دري->display = tkparent->display;
            دري->display_close = false;
        } وإلا {
            دري->display = X11_XOpenDisplay(عدم);
            دري->display_close = true;
            إذا (!دري->display) {
                ErrorFreeRetNull("Couldn't open X11 display", دري);
            }
        }
    }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XRANDR
    صحيح xrandr_event_بنياد, xrandr_error_بنياد;
    دري->xrandr = X11_XRRQueryExtension(دري->display, &xrandr_event_بنياد, &xrandr_error_بنياد);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري
    دري->shm_pixmap = False;
    دري->shm = X11_XShmQueryExtension(دري->display) ? SDL_X11_HAVE_SHM : false;
    إذا (دري->shm) {
        صحيح major;
        صحيح minor;

        X11_XShm_Query_نسخو(دري->display, &major, &minor, &دري->shm_pixmap);
        إذا (دري->shm_pixmap) {
            إذا (X11_XShmPixmapFormat(دري->display) != ZPixmap) {
                دري->shm_pixmap = False;
            }
        }
    }
#جيڪڏهن_پورو

    /* Scale/Xsettings */
    دري->pixmap = false;
    دري->xsettings_پهريون_وقت = true;
    دري->xsettings = xsettings_client_new(دري->display, DefaultScreen(دري->display), X11Toolkit_SettingsNotify, عدم, دري);
    دري->xsettings_پهريون_وقت = false;
    دري->scale = X11_GetGlobalContentScale(دري->display, دري->xsettings);
    إذا (دري->scale < 1) {
        دري->scale = 1;
    }
    دري->iscale = (صحيح)SDL_ceilf(دري->scale);
    إذا (SDL_roundf(دري->scale) == دري->scale) {
        دري->scale = 0;
    }

    /* Fonts */
    X11_Toolkit_Init_دري_Fonts(دري);

    /* Color hints */
#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    إذا (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#جيڪڏهن_پورو

    إذا (!colorhints) {
#جيڪڏهن_وصف_ٿيل SDL_USE_LIBDBUS
        بدل (theme) {
            حالة SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                اكسر;
#إذا 0
            حالة SDL_SYSTEM_THEME_LIGHT_مٿاهون_CONTRAST:
                colorhints = g_default_colors_light_مٿاهون_contrast;
                اكسر;
            حالة SDL_SYSTEM_THEME_DARK_مٿاهون_CONTRAST:
                colorhints = g_default_colors_dark_مٿاهون_contrast;
                اكسر;
#جيڪڏهن_پورو
            افتراضي:
                colorhints = g_default_colors;
        }
#وإلا
        colorhints = g_default_colors;
#جيڪڏهن_پورو
    }
    دري->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    لكل (i = 0; i < SDL_MESSAGEBOX_COLOR_ڳڻپ; i++) {
        دري->xcolor[i].flags = DoRed|DoGreen|DoBlue;
        دري->xcolor[i].red = colorhints[i].r * 257;
        دري->xcolor[i].green = colorhints[i].g * 257;
        دري->xcolor[i].blue = colorhints[i].b * 257;
    }

    /* Generate bevel and pressed colors */
    دري->xcolor_bevel_l1.flags = DoRed|DoGreen|DoBlue;
    دري->xcolor_bevel_l1.red = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 12500, 0, 65535);
    دري->xcolor_bevel_l1.green = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 12500, 0, 65535);
    دري->xcolor_bevel_l1.blue = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 12500, 0, 65535);

    دري->xcolor_bevel_l2.flags = DoRed|DoGreen|DoBlue;
    دري->xcolor_bevel_l2.red = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 32500, 0, 65535);
    دري->xcolor_bevel_l2.green = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 32500, 0, 65535);
    دري->xcolor_bevel_l2.blue = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 32500, 0, 65535);

    دري->xcolor_bevel_d.flags = DoRed|DoGreen|DoBlue;
    دري->xcolor_bevel_d.red = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red - 22500, 0, 65535);
    دري->xcolor_bevel_d.green = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green - 22500, 0, 65535);
    دري->xcolor_bevel_d.blue = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue - 22500, 0, 65535);

    دري->xcolor_pressed.flags = DoRed|DoGreen|DoBlue;
    دري->xcolor_pressed.red = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].red - 12500, 0, 65535);
    دري->xcolor_pressed.green = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].green - 12500, 0, 65535);
    دري->xcolor_pressed.blue = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].blue - 12500, 0, 65535);

    دري->xcolor_disabled_متن.flags = DoRed|DoGreen|DoBlue;
    دري->xcolor_disabled_متن.red = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_متن].red + 19500, 0, 65535);
    دري->xcolor_disabled_متن.green = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_متن].green + 19500, 0, 65535);
    دري->xcolor_disabled_متن.blue = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_متن].blue + 19500, 0, 65535);

    /* Screen */
    دري->والد = والد;
    إذا (والد) {
        SDL_Display_معلومات *displaydata = SDL_Get_Display_Driver_معلومات_For_دري(والد);
        دري->screen = displaydata->screen;
    } وإلا {
        دري->screen = DefaultScreen(دري->display);
    }

    /* Visuals */
    إذا (گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_ٻار) {
        دري->visual = والد->اندروني->visual;
        دري->cmap = والد->اندروني->colormap;
        X11_GetVisualInfoFromVisual(دري->display, دري->visual, &دري->vi);
        دري->اونهائي_2 = دري->vi.اونهائي_2;
    } وإلا {
        دري->visual = DefaultVisual(دري->display, دري->screen);
        دري->cmap = DefaultColormap(دري->display, دري->screen);
        دري->اونهائي_2 = Default_اونهائي(دري->display, دري->screen);
        X11_GetVisualInfoFromVisual(دري->display, دري->visual, &دري->vi);
    }

    /* Allocate colors */
    لكل (i = 0; i < SDL_MESSAGEBOX_COLOR_ڳڻپ; i++) {
        X11_XAllocColor(دري->display, دري->cmap, &دري->xcolor[i]);
    }
    X11_XAllocColor(دري->display, دري->cmap, &دري->xcolor_bevel_l1);
    X11_XAllocColor(دري->display, دري->cmap, &دري->xcolor_bevel_l2);
    X11_XAllocColor(دري->display, دري->cmap, &دري->xcolor_bevel_d);
    X11_XAllocColor(دري->display, دري->cmap, &دري->xcolor_pressed);
    X11_XAllocColor(دري->display, دري->cmap, &دري->xcolor_disabled_متن);

    /* Control list */
    دري->has_focus = false;
    دري->controls = عدم;
    دري->controls_sz = 0;
    دري->dyn_controls_sz = 0;
    دري->fiddled_control = عدم;
    دري->dyn_controls = عدم;

    /* Menu windows */
    دري->popup_windows = عدم;

    /* BIDI engine */
#جيڪڏهن_وصف_ٿيل HAVE_FRIBIDI_H
    دري->fribidi = SDL_FriBidi_Create();
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل HAVE_LIBTHAI_H
    دري->th = SDL_LibThai_Create();
#جيڪڏهن_پورو
    
    /* Interface direction */
    دري->flip_interface = X11Toolkit_ShouldFlipUI();
    
    أرجع دري;
}

ساكن فراغ X11_Toolkit_جوڙيو_Control_منزل_دري(SDL_Toolkit_دري_X11 *دري, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    دري->controls_sz++;
    إذا (دري->controls_sz == 1) {
        دري->controls = (بنية SDL_ToolkitControlX11 **)SDL_malloc(حجم(بنية SDL_ToolkitControlX11 *));
    } وإلا {
        دري->controls = (بنية SDL_ToolkitControlX11 **)SDL_realloc(دري->controls, حجم(بنية SDL_ToolkitControlX11 *) * دري->controls_sz);
    }
    دري->controls[دري->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    إذا (control->dynamic) {
        دري->dyn_controls_sz++;
        إذا (دري->dyn_controls_sz == 1) {
            دري->dyn_controls = (بنية SDL_ToolkitControlX11 **)SDL_malloc(حجم(بنية SDL_ToolkitControlX11 *));
        } وإلا {
            دري->dyn_controls = (بنية SDL_ToolkitControlX11 **)SDL_realloc(دري->dyn_controls, حجم(بنية SDL_ToolkitControlX11 *) * دري->dyn_controls_sz);
        }
        دري->dyn_controls[دري->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    إذا (control->selected) {
        دري->focused_control = control;
    }
}

bool X11_Toolkit_Create_دري_Res(SDL_Toolkit_دري_X11 *معلومات, صحيح w, صحيح h, صحيح cx, صحيح cy, حرف *title)
{
    صحيح x, y;
    XSizeHints *sizehints;
    XSet_دري_خاصيتون wnd_attr;
    Atom NET_WM_دري_TYPE, NET_WM_دري_TYPE_DIALOG, NET_WM_دري_TYPE_DROPDOWN_MENU, NET_WM_دري_TYPE_TOOLTIP;
    SDL_دري_معلومات *windowdata = عدم;
    Display *display = معلومات->display;
    XGCValues ctx_vals;
    دري_2 پاڙ_win;
    دري_2 والد_win;
    بنانشان ڊگهو gcflags = GCForeground | GCBackground;
    بنانشان ڊگهو valuemask;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XRANDR
#جيڪڏهن_وصف_ٿيل XRANDR_DISABLED_BY_DEFAULT
    ثابت bool use_xrandr_by_default = false;
#وإلا
    ثابت bool use_xrandr_by_default = true;
#جيڪڏهن_پورو
#جيڪڏهن_پورو

    إذا (معلومات->scale == 0) {
        معلومات->دري_ويڪر = w;
        معلومات->دري_اوچائي = h;
    } وإلا {
        معلومات->دري_ويڪر = SDL_lroundf((w/معلومات->iscale) * معلومات->scale);
        معلومات->دري_اوچائي = SDL_lroundf((h/معلومات->iscale) * معلومات->scale);
        معلومات->pixmap_ويڪر = w;
        معلومات->pixmap_اوچائي = h;
        معلومات->pixmap = true;
    }

    إذا (معلومات->والد) {
        windowdata = معلومات->والد->اندروني;
    }

    valuemask = CWEvent_نقاب | CWColormap;
    معلومات->event_نقاب = Exposure_نقاب |
                       Button_Press_نقاب | Button_Release_نقاب | ڪنجي_Press_نقاب | ڪنجي_Release_نقاب |
                       Structure_Notify_نقاب | Focus_Change_نقاب | اشارو_Motion_نقاب;
    wnd_attr.event_نقاب = معلومات->event_نقاب;
    wnd_attr.colormap = معلومات->cmap;
    إذا (معلومات->گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_MENU || معلومات->گهڻائي== SDL_TOOLKIT_دري_گهڻائي_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    پاڙ_win = پاڙ_دري(display, معلومات->screen);
    إذا (معلومات->گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_ٻار) {
        والد_win = windowdata->xwindow;
    } وإلا {
        والد_win = پاڙ_win;
    }

    معلومات->دري = X11_XCreate_دري(
        display, والد_win,
        0, 0,
        معلومات->دري_ويڪر, معلومات->دري_اوچائي,
        0, معلومات->اونهائي_2, داخلا_Output, معلومات->visual,
        valuemask, &wnd_attr);
    إذا (معلومات->دري == None) {
        أرجع SDL_سيٽ_Error("Couldn't create X window");
    }

    إذا (windowdata && معلومات->گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_DIALOG) {
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
        X11_XChangeProperty(display, معلومات->دري, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_گهڻائي_Replace, (بنانشان حرف *)stateatoms, statecount);
    }

    إذا (windowdata && معلومات->گهڻائي != SDL_TOOLKIT_دري_گهڻائي_X11_ٻار) {
        X11_XSetTransientForHint(display, معلومات->دري, windowdata->xwindow);
    }

    إذا (معلومات->tk_والد) {
        X11_XSetTransientForHint(display, معلومات->دري, معلومات->tk_والد->دري);
    }

    SDL_X11_سيٽ_دري_Title(display, معلومات->دري, title);

    // Let the window manager the type of the window
    إذا (معلومات->گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_DIALOG) {
        NET_WM_دري_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_دري_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, معلومات->دري, NET_WM_دري_TYPE, XA_ATOM, 32,
                            Prop_گهڻائي_Replace,
                            (بنانشان حرف *)&NET_WM_دري_TYPE_DIALOG, 1);
    } وإلا إذا (معلومات->گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_MENU) {
        NET_WM_دري_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_دري_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, معلومات->دري, NET_WM_دري_TYPE, XA_ATOM, 32,
                            Prop_گهڻائي_Replace,
                            (بنانشان حرف *)&NET_WM_دري_TYPE_DROPDOWN_MENU, 1);
    } وإلا إذا (معلومات->گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_TOOLTIP) {
        NET_WM_دري_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_دري_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, معلومات->دري, NET_WM_دري_TYPE, XA_ATOM, 32,
                            Prop_گهڻائي_Replace,
                            (بنانشان حرف *)&NET_WM_دري_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    معلومات->wm_delete_پيغام = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, معلومات->دري, &معلومات->wm_delete_پيغام, 1);
    معلومات->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    إذا (معلومات->گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_MENU || معلومات->گهڻائي== SDL_TOOLKIT_دري_گهڻائي_X11_TOOLTIP) {
        x = cx;
        y = cy;
        اذهب MOVEWINDOW;
    }
    إذا (windowdata) {
        XWindow_خاصيتون attrib;
        دري_2 dummy;

        X11_XGet_دري_خاصيتون(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.ويڪر - معلومات->دري_ويڪر) / 2;
        y = attrib.y + (attrib.اوچائي - معلومات->دري_اوچائي) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, پاڙ_دري(display, معلومات->screen), x, y, &x, &y, &dummy);
    } وإلا {
        ثابت SDL_VideoDevice *dev = SDL_GetVideoDevice();
        إذا (dev && dev->displays && dev->انگ_displays > 0) {
            ثابت SDL_VideoDisplay *dpy = dev->displays[0];
            ثابت SDL_Display_معلومات *dpydata = dpy->اندروني;
            x = dpydata->x + ((dpy->current_گهڻائي->w - معلومات->دري_ويڪر) / 2);
            y = dpydata->y + ((dpy->current_گهڻائي->h - معلومات->دري_اوچائي) / 3);
        }
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XRANDR
        وإلا إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && معلومات->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_ٻاهريون;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, پاڙ_win);
            إذا (!screen_res) {
                اذهب NOXRANDR;
            }

            default_ٻاهريون = X11_XRRGetOutputPrimary(display, پاڙ_win);
            إذا (default_ٻاهريون != None) {
                XRROutputInfo *ٻاهريون_info;

                ٻاهريون_info = X11_XRRGetOutputInfo(display, screen_res, default_ٻاهريون);
                إذا (ٻاهريون_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(ٻاهريون_info);
                    اذهب FIRSTOUTPUTXRANDR;
                }

                إذا (ٻاهريون_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ٻاهريون_info->crtc);
                } وإلا إذا (ٻاهريون_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ٻاهريون_info->crtcs[0]);
                } وإلا {
                    crtc_info = عدم;
                }
                
                إذا (crtc_info) {
                    x = (crtc_info->ويڪر - معلومات->دري_ويڪر) / 2;
                    y = (crtc_info->اوچائي - معلومات->دري_اوچائي) / 3;
                    X11_XRRFreeOutputInfo(ٻاهريون_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } وإلا {
                    X11_XRRFreeOutputInfo(ٻاهريون_info);
                    اذهب NOXRANDR;
                }
            } وإلا {
                    FIRSTOUTPUTXRANDR:
                    إذا (screen_res->noutput > 0) {
                        XRROutputInfo *ٻاهريون_info;

                        ٻاهريون_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        إذا (!ٻاهريون_info) {
                            اذهب FIRSTCRTCXRANDR;
                        }

                        إذا (ٻاهريون_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ٻاهريون_info->crtc);
                        } وإلا إذا (ٻاهريون_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ٻاهريون_info->crtcs[0]);
                        } وإلا {
                            crtc_info = عدم;
                        }

                        إذا (!crtc_info) {
                            X11_XRRFreeOutputInfo(ٻاهريون_info);
                            اذهب FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->ويڪر - معلومات->دري_ويڪر) / 2;
                        y = (crtc_info->اوچائي - معلومات->دري_اوچائي) / 3;
                        X11_XRRFreeOutputInfo(ٻاهريون_info);
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
                        x = (crtc_info->ويڪر - معلومات->دري_ويڪر) / 2;
                        y = (crtc_info->اوچائي - معلومات->دري_اوچائي) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } وإلا {
                        X11_XRRFreeScreenResources(screen_res);
                        اذهب NOXRANDR;
                    }
            }
        }
#جيڪڏهن_پورو
        وإلا {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (Display_ويڪر(display, معلومات->screen) - معلومات->دري_ويڪر) / 2;
            y = (Display_اوچائي(display, معلومات->screen) - معلومات->دري_اوچائي) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMove_دري(display, معلومات->دري, x, y);
    معلومات->دري_x = x;
    معلومات->دري_y = y;

    sizehints = X11_XAlloc_سائيز_Hints();
    إذا (sizehints) {
        sizehints->flags = USPosition | USSize | PMax_سائيز | PMin_سائيز;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->ويڪر = معلومات->دري_ويڪر;
        sizehints->اوچائي = معلومات->دري_اوچائي;

        sizehints->min_ويڪر_2 = sizehints->max_ويڪر_2 = معلومات->دري_ويڪر;
        sizehints->min_اوچائي_2 = sizehints->max_اوچائي_2 = معلومات->دري_اوچائي;

        X11_XSetWMNormalHints(display, معلومات->دري, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, معلومات->دري);

    معلومات->drawable = معلومات->دري;
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    إذا (SDL_X11_HAVE_XDBE && !معلومات->pixmap) {
        صحيح xdbe_major, xdbe_minor;
        إذا (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            معلومات->xdbe = true;
            معلومات->buf = X11_Xdbe_Allocate_پٺ_بفر_Name(display, معلومات->دري, XdbeUndefined);
            معلومات->drawable = معلومات->buf;
        } وإلا {
            معلومات->xdbe = false;
        }
    }
#جيڪڏهن_پورو

    X11_Toolkit_Init_دري_Pixmap(معلومات);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = معلومات->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = معلومات->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    إذا (!معلومات->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = معلومات->font_struct->fid;
    }
    معلومات->ctx = X11_XCreateGC(معلومات->display, معلومات->drawable, gcflags, &ctx_vals);
    إذا (معلومات->ctx == None) {
        أرجع SDL_سيٽ_Error("Couldn't create graphics context");
    }

    معلومات->close = false;
    معلومات->ڪنجي_control_esc = معلومات->ڪنجي_control_enter = عدم;
    إذا (!معلومات->pixmap) {
        معلومات->ev_scale = معلومات->ev_iscale = 1;
    } وإلا {
        معلومات->ev_scale = معلومات->scale;
        معلومات->ev_iscale = معلومات->iscale;
    }

#إذا SDL_GRAB
    إذا (معلومات->گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_MENU || معلومات->گهڻائي== SDL_TOOLKIT_دري_گهڻائي_X11_TOOLTIP) {
        X11_XGrab_اشارو(display, معلومات->دري, False, Button_Press_نقاب | Button_Release_نقاب | اشارو_Motion_نقاب, Grab_گهڻائي_Async, Grab_گهڻائي_Async, None, None, Current_وقت);
        X11_XGrabKeyboard(display, معلومات->دري, False, Grab_گهڻائي_Async, Grab_گهڻائي_Async, Current_وقت);
    }
#جيڪڏهن_پورو

    أرجع true;
}

ساكن فراغ X11_Toolkit_Draw_دري(SDL_Toolkit_دري_X11 *معلومات) {
    SDL_Rect rect;
    صحيح i;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && معلومات->xdbe && !معلومات->pixmap) {
        X11_XdbeBeginIdiom(معلومات->display);
    }
#جيڪڏهن_پورو

    X11_XSetForeground(معلومات->display, معلومات->ctx, معلومات->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    إذا (معلومات->pixmap) {
        X11_XFillRectangle(معلومات->display, معلومات->drawable, معلومات->ctx, 0, 0, معلومات->pixmap_ويڪر, معلومات->pixmap_اوچائي);
    } وإلا {
        X11_XFillRectangle(معلومات->display, معلومات->drawable, معلومات->ctx, 0, 0, معلومات->دري_ويڪر, معلومات->دري_اوچائي);
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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && معلومات->xdbe && !معلومات->pixmap) {
        Xdbe_مٽا_سٽا_Info مٽا_سٽا_info;
        مٽا_سٽا_info.مٽا_سٽا_دري = معلومات->دري;
        مٽا_سٽا_info.مٽا_سٽا_action = XdbeUndefined;
        X11_Xdbe_مٽا_سٽا_Buffers(معلومات->display, &مٽا_سٽا_info, 1);
        X11_Xdbe_پڇاڙي_Idiom(معلومات->display);
    }
#جيڪڏهن_پورو

    إذا (معلومات->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = معلومات->دري_ويڪر;
        rect.h = معلومات->دري_اوچائي;
#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري
        إذا (معلومات->shm) {
            إذا (معلومات->shm_pixmap) {
                X11_XFlush(معلومات->display);
                X11_XSync(معلومات->display, false);
                scale_surface = SDL_CreateSurfaceFrom(معلومات->pixmap_ويڪر, معلومات->pixmap_اوچائي, X11_GetPixelFormatFromVisualInfo(معلومات->display, &معلومات->vi), معلومات->shm_info.shmaddr, معلومات->shm_بائيٽون_في_سٽ);
                SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_لڪيري);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(معلومات->display, معلومات->drawable, معلومات->دري, معلومات->ctx, 0, 0, معلومات->دري_ويڪر, معلومات->دري_اوچائي, 0, 0);
            } وإلا {
                X11_XShmGetImage(معلومات->display, معلومات->drawable, معلومات->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(معلومات->pixmap_ويڪر, معلومات->pixmap_اوچائي, X11_GetPixelFormatFromVisualInfo(معلومات->display, &معلومات->vi), معلومات->image->معلومات, معلومات->image->بائيٽون_في_سٽ);
                SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_لڪيري);
                X11_XShmPutImage(معلومات->display, معلومات->دري, معلومات->ctx, معلومات->image, 0, 0, 0, 0, معلومات->دري_ويڪر, معلومات->دري_اوچائي, False);
            }
        } وإلا
#جيڪڏهن_پورو
        {
            XImage *image;

            image = X11_XGetImage(معلومات->display, معلومات->drawable, 0, 0 , معلومات->pixmap_ويڪر, معلومات->pixmap_اوچائي, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(معلومات->pixmap_ويڪر, معلومات->pixmap_اوچائي, X11_GetPixelFormatFromVisualInfo(معلومات->display, &معلومات->vi), image->معلومات, image->بائيٽون_في_سٽ);
            SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_لڪيري);
            X11_XPutImage(معلومات->display, معلومات->دري, معلومات->ctx, image, 0, 0, 0, 0, معلومات->دري_ويڪر, معلومات->دري_اوچائي);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(معلومات->display);
}

ساكن SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_Toolkit_دري_X11 *معلومات, صحيح x, صحيح y)
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
    SDL_Toolkit_دري_X11 *معلومات = (SDL_Toolkit_دري_X11 *)arg;

    إذا (event->xany.display != معلومات->display) {
        أرجع False;
    }

    إذا (event->xany.دري == معلومات->دري) {
        أرجع True;
    }

    أرجع False;
}

فراغ X11_Toolkit_Process_دري_Events(SDL_Toolkit_دري_X11 *معلومات, XEvent *e) {
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
        حالة Client_پيغام:
            إذا (e->xclient.پيغام_type == معلومات->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.معلومات.l[0] == معلومات->wm_delete_پيغام) {
                معلومات->close = true;
            }
            اكسر;
        حالة Focus_اندريون:
            معلومات->has_focus = true;
            اكسر;
        حالة Focus_ٻاهريون:
            معلومات->has_focus = false;
            إذا (معلومات->fiddled_control) {
                معلومات->fiddled_control->selected = false;
            }
            معلومات->fiddled_control = عدم;
            لكل (معلومات->ev_i = 0; معلومات->ev_i < معلومات->controls_sz; معلومات->ev_i++) {
                معلومات->controls[معلومات->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
            }
            اكسر;
        حالة MotionNotify:
            إذا (معلومات->has_focus) {
                معلومات->اڳيون_control = معلومات->fiddled_control;
                معلومات->fiddled_control = X11Toolkit_GetControlMouseIsOn(معلومات, SDL_lroundf((e->xbutton.x/ معلومات->ev_scale)* معلومات->ev_iscale), SDL_lroundf((e->xbutton.y/ معلومات->ev_scale)* معلومات->ev_iscale));
                إذا (معلومات->اڳيون_control) {
                    معلومات->اڳيون_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
                    إذا (معلومات->اڳيون_control->func_on_state_change) {
                        معلومات->اڳيون_control->func_on_state_change(معلومات->اڳيون_control);
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
            معلومات->اڳيون_control = معلومات->fiddled_control;
            إذا (معلومات->اڳيون_control) {
                معلومات->اڳيون_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
                إذا (معلومات->اڳيون_control->func_on_state_change) {
                    معلومات->اڳيون_control->func_on_state_change(معلومات->اڳيون_control);
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
            إذا (معلومات->گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_MENU || معلومات->گهڻائي== SDL_TOOLKIT_دري_گهڻائي_X11_TOOLTIP) {
                صحيح cx;
                صحيح cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                إذا (cy < 0 || cx < 0) {
                    معلومات->close = true;
                }

                إذا (cy > معلومات->دري_اوچائي || cx > معلومات->دري_ويڪر) {
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
                    معلومات->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
                    معلومات->draw = true;
                }
            }
            اكسر;
        حالة ڪنجي_Press:
            معلومات->آخري_ڪنجي_pressed = X11_XLookupKeysym(&e->xkey, 0);

            إذا (معلومات->آخري_ڪنجي_pressed == XK_Escape) {
                لكل (معلومات->ev_i = 0; معلومات->ev_i < معلومات->controls_sz; معلومات->ev_i++) {
                    إذا(معلومات->controls[معلومات->ev_i]->is_default_esc) {
                        معلومات->controls[معلومات->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        معلومات->draw = true;
                        معلومات->ڪنجي_control_esc = معلومات->controls[معلومات->ev_i];
                    }
                }
            } وإلا إذا ((معلومات->آخري_ڪنجي_pressed == XK_Return) || (معلومات->آخري_ڪنجي_pressed == XK_KP_Enter)) {
                لكل (معلومات->ev_i = 0; معلومات->ev_i < معلومات->controls_sz; معلومات->ev_i++) {
                    إذا(معلومات->controls[معلومات->ev_i]->selected) {
                        معلومات->controls[معلومات->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        معلومات->draw = true;
                        معلومات->ڪنجي_control_enter = معلومات->controls[معلومات->ev_i];
                    }
                }
            }
            اكسر;
        حالة ڪنجي_Release:
        {
            ڪنجي_Sym ڪنجي = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            إذا (ڪنجي != معلومات->آخري_ڪنجي_pressed) {
                اكسر;
            }

            إذا (ڪنجي == XK_Escape) {
                إذا (معلومات->ڪنجي_control_esc) {
                    إذا (معلومات->ڪنجي_control_esc->func_on_state_change) {
                        معلومات->ڪنجي_control_esc->func_on_state_change(معلومات->ڪنجي_control_esc);
                    }
                }
            } وإلا إذا ((ڪنجي == XK_Return) || (ڪنجي == XK_KP_Enter)) {
                إذا (معلومات->ڪنجي_control_enter) {
                    إذا (معلومات->ڪنجي_control_enter->func_on_state_change) {
                        معلومات->ڪنجي_control_enter->func_on_state_change(معلومات->ڪنجي_control_enter);
                    }
                }
            } وإلا إذا (ڪنجي == XK_Tab || ڪنجي == XK_کاٻو || ڪنجي == XK_ساڄو) {
                إذا (معلومات->focused_control) {
                    معلومات->focused_control->selected = false;
                }
                معلومات->draw = true;
                لكل (معلومات->ev_i = 0; معلومات->ev_i < معلومات->dyn_controls_sz; معلومات->ev_i++) {
                    إذا (معلومات->dyn_controls[معلومات->ev_i] == معلومات->focused_control) {
                        صحيح ايندڙ_اشاريو;

                        إذا (ڪنجي == XK_کاٻو) {
                            ايندڙ_اشاريو = معلومات->ev_i - 1;
                        } وإلا {
                            ايندڙ_اشاريو = معلومات->ev_i + 1;
                        }
                        إذا ((ايندڙ_اشاريو >= معلومات->dyn_controls_sz) || (ايندڙ_اشاريو < 0)) {
                            إذا (ڪنجي == XK_ساڄو || ڪنجي == XK_کاٻو) {
                                ايندڙ_اشاريو = معلومات->ev_i;
                            } وإلا {
                                ايندڙ_اشاريو = 0;
                            }
                        }
                        معلومات->focused_control = معلومات->dyn_controls[ايندڙ_اشاريو];
                        معلومات->focused_control->selected = true;
                        اكسر;
                    }
                }
            }
            اكسر;
        }
    }

    إذا (معلومات->draw) {
        X11_Toolkit_Draw_دري(معلومات);
    }
}

فراغ X11_Toolkit_Do_دري_Event_Loop(SDL_Toolkit_دري_X11 *معلومات) {
   طالما (!معلومات->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(معلومات->display, &e);
        إذا (معلومات->xsettings) {
            xsettings_client_process_event(معلومات->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(معلومات->display, &e, X11Toolkit_EventTest, (XPointer)معلومات);
        X11_Toolkit_Process_دري_Events(معلومات, &e);
    }
}


فراغ X11_Toolkit_Resize_دري(SDL_Toolkit_دري_X11 *معلومات, صحيح w, صحيح h) {
    إذا (!معلومات->pixmap) {
        معلومات->دري_ويڪر = w;
        معلومات->دري_اوچائي = h;
    } وإلا {
        معلومات->دري_ويڪر = SDL_lroundf((w/معلومات->iscale) * معلومات->scale);
        معلومات->دري_اوچائي = SDL_lroundf((h/معلومات->iscale) * معلومات->scale);
        معلومات->pixmap_ويڪر = w;
        معلومات->pixmap_اوچائي = h;
        X11_XFreePixmap(معلومات->display, معلومات->drawable);
        X11_Toolkit_Init_دري_Pixmap(معلومات);
    }

    X11_XResize_دري(معلومات->display, معلومات->دري, معلومات->دري_ويڪر, معلومات->دري_اوچائي);
}

ساكن فراغ X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->دري->display, icon_control->icon_char_font);
    SDL_free(control);
}

ساكن فراغ X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->دري->iscale;
    control->rect.h -= 2 * control->دري->iscale;
    X11_XSetForeground(control->دري->display, control->دري->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->دري->display, control->دري->drawable, control->دري->ctx, control->rect.x + (2 * control->دري->iscale), control->rect.y + (2* control->دري->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    بدل (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        حالة SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->دري->display, control->دري->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->دري->display, control->دري->drawable, control->دري->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->دري->display, control->دري->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->دري->display, control->دري->drawable, control->دري->ctx, control->rect.x+(1* control->دري->iscale), control->rect.y+(1* control->دري->iscale), control->rect.w-(2* control->دري->iscale), control->rect.h-(2* control->دري->iscale), 0, 360 * 64);
                X11_XSetForeground(control->دري->display, control->دري->ctx, icon_control->xcolor_white.pixel);
                اكسر;
        حالة SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->دري->display, control->دري->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->دري->display, control->دري->drawable, control->دري->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->دري->display, control->دري->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->دري->display, control->دري->drawable, control->دري->ctx, control->rect.x+(1* control->دري->iscale), control->rect.y+(1* control->دري->iscale), control->rect.w-(2* control->دري->iscale), control->rect.h-(2* control->دري->iscale), 0, 360 * 64);
                X11_XSetForeground(control->دري->display, control->دري->ctx, icon_control->xcolor_black.pixel);
                اكسر;
        حالة SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->دري->display, control->دري->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->دري->display, control->دري->drawable, control->دري->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->دري->display, control->دري->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->دري->display, control->دري->drawable, control->دري->ctx, control->rect.x+(1* control->دري->iscale), control->rect.y+(1* control->دري->iscale), control->rect.w-(2* control->دري->iscale), control->rect.h-(2* control->دري->iscale), 0, 360 * 64);
                X11_XSetForeground(control->دري->display, control->دري->ctx, icon_control->xcolor_white.pixel);
                اكسر;
    }
    X11_XSetFont(control->دري->display, control->دري->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->دري->display, control->دري->drawable, control->دري->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    إذا (!control->دري->utf8) {
        X11_XSetFont(control->دري->display, control->دري->ctx, control->دري->font_struct->fid);
    }

    control->rect.w += 2 * control->دري->iscale;
    control->rect.h += 2 * control->دري->iscale;
}

ساكن فراغ X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *بنياد_control) {
    SDL_ToolkitIconControlX11 *control;
    صحيح icon_char_w;
    صحيح icon_wh;

    control = (SDL_ToolkitIconControlX11 *)بنياد_control;
    X11_Toolkit_Get_متن_ويڪر_اوچائي_For_Font(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, عدم);
    بنياد_control->rect.w = icon_char_w;
    بنياد_control->rect.h = control->icon_char_h;
    icon_wh = SDL_max(icon_char_w, control->icon_char_h) + SDL_TOOLKIT_X11_ELEMENT_PADDING * 2 * بنياد_control->دري->iscale;
    بنياد_control->rect.w = icon_wh;
    بنياد_control->rect.h = icon_wh;
    بنياد_control->rect.y = 0;
    بنياد_control->rect.x = 0;
    control->icon_char_y = control->icon_char_a + (بنياد_control->rect.h - control->icon_char_h)/2;
    control->icon_char_x = (بنياد_control->rect.w - icon_char_w)/2;
    بنياد_control->rect.w += 2 * بنياد_control->دري->iscale;
    بنياد_control->rect.h += 2 * بنياد_control->دري->iscale;
}

ساكن فراغ X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *بنياد_control) {
    SDL_ToolkitIconControlX11 *control;
    حرف *font;

    control = (SDL_ToolkitIconControlX11 *)بنياد_control;
    X11_XFreeFont(بنياد_control->دري->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_سائيز * بنياد_control->دري->iscale);
    control->icon_char_font = X11_XLoadQueryFont(بنياد_control->دري->display, font);
    SDL_free(font);
    إذا (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_سائيز * بنياد_control->دري->iscale);
        control->icon_char_font = X11_XLoadQueryFont(بنياد_control->دري->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_دري_X11 *دري, SDL_پيغام_Box_Flags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *بنياد_control;
    حرف *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(حجم(SDL_ToolkitIconControlX11));
    بنياد_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_سيٽ_Error("Unable to allocate icon control structure");
        أرجع عدم;
    }

    /* Fill out struct */
    بنياد_control->دري = دري;
    بنياد_control->func_draw = X11Toolkit_DrawIconControl;
    بنياد_control->func_free = X11Toolkit_DestroyIconControl;
    بنياد_control->func_on_state_change = عدم;
    بنياد_control->func_calc_سائيز = X11Toolkit_CalculateIconControl;
    بنياد_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    بنياد_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
    بنياد_control->selected = false;
    بنياد_control->dynamic = false;
    بنياد_control->is_default_enter = false;
    بنياد_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_سائيز * دري->iscale);
    control->icon_char_font = X11_XLoadQueryFont(دري->display, font);
    SDL_free(font);
    إذا (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_سائيز * دري->iscale);
        control->icon_char_font = X11_XLoadQueryFont(دري->display, font);
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
        X11_XAllocColor(دري->display, دري->cmap, &control->xcolor_white);
        X11_XAllocColor(دري->display, دري->cmap, &control->xcolor_red);
        X11_XAllocColor(دري->display, دري->cmap, &control->xcolor_red_darker);
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
        X11_XAllocColor(دري->display, دري->cmap, &control->xcolor_black);
        X11_XAllocColor(دري->display, دري->cmap, &control->xcolor_yellow);
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
        X11_XAllocColor(دري->display, دري->cmap, &control->xcolor_white);
        X11_XAllocColor(دري->display, دري->cmap, &control->xcolor_blue);
        اكسر;
    افتراضي:
        X11_XFreeFont(دري->display, control->icon_char_font);
        SDL_free(control);
        أرجع عدم;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    إذا (دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } وإلا إذا (دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.red = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    إذا (دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } وإلا إذا (دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.green = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    إذا (دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } وإلا إذا (دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.blue = SDL_clamp(دري->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(دري->display, دري->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(بنياد_control);

    X11_Toolkit_جوڙيو_Control_منزل_دري(دري, بنياد_control);
    أرجع بنياد_control;
}

bool X11_Toolkit_Notify_Control_جو_سائيز_Change(SDL_ToolkitControlX11 *control) {
    إذا (control->func_calc_سائيز) {
        control->func_calc_سائيز(control);
        أرجع true;
    } وإلا {
        أرجع false;
    }
}

ساكن فراغ X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11_Toolkit_Get_متن_Elements_Rect(button_control->متن, &button_control->متن_rect);
    إذا (control->do_سائيز) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->دري->iscale + button_control->متن_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->دري->iscale + button_control->متن_rect.h;
    }
    button_control->متن_rect.x = (control->rect.w - button_control->متن_rect.w)/2;
    button_control->متن_rect.y = (control->rect.h - button_control->متن_rect.h)/2;
}


ساكن فراغ X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    /* Draw bevel */
    إذا (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
            X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor_bevel_d.pixel);
            X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

            X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor_bevel_l2.pixel);
            X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - (1* control->دري->iscale), control->rect.h - (1* control->دري->iscale));

            X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor_bevel_l1.pixel);
            X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x + 1 * control->دري->iscale, control->rect.y + 1 * control->دري->iscale,
                                   control->rect.w - 3 * control->دري->iscale, control->rect.h - 2 * control->دري->iscale);

            X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
            X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                               control->rect.x + 1 * control->دري->iscale, control->rect.y + 1 * control->دري->iscale,
                               control->rect.w - 3 * control->دري->iscale, control->rect.h - 3 * control->دري->iscale);

            X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor_pressed.pixel);
            X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                               control->rect.x + 2 * control->دري->iscale, control->rect.y + 2 * control->دري->iscale,
                               control->rect.w - 4 * control->دري->iscale, control->rect.h - 4 * control->دري->iscale);
        } وإلا {
            إذا (control->selected) {
                X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x + 1 * control->دري->iscale, control->rect.y + 1 * control->دري->iscale,
                                   control->rect.w - 3 * control->دري->iscale, control->rect.h - 3 * control->دري->iscale);

                X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x + 2 * control->دري->iscale, control->rect.y + 2 * control->دري->iscale,
                                   control->rect.w - 4 * control->دري->iscale, control->rect.h - 4 * control->دري->iscale);

                X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x + 2 * control->دري->iscale, control->rect.y + 2 * control->دري->iscale,
                                   control->rect.w - 5 * control->دري->iscale, control->rect.h - 5 * control->دري->iscale);

                X11_XSetForeground(control->دري->display, control->دري->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x + 3 * control->دري->iscale, control->rect.y + 3 * control->دري->iscale,
                                   control->rect.w - 6 * control->دري->iscale, control->rect.h - 6 * control->دري->iscale);
            } وإلا {
                X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - 1 * control->دري->iscale, control->rect.h - 1 * control->دري->iscale);

                X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x + 1 * control->دري->iscale, control->rect.y + 1 * control->دري->iscale,
                                   control->rect.w - 2 * control->دري->iscale, control->rect.h - 2 * control->دري->iscale);

                X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x + 1 * control->دري->iscale, control->rect.y + 1 * control->دري->iscale,
                                   control->rect.w - 3 * control->دري->iscale, control->rect.h - 3 * control->دري->iscale);

                X11_XSetForeground(control->دري->display, control->دري->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->دري->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->دري->display, control->دري->drawable, control->دري->ctx,
                                   control->rect.x + 2 * control->دري->iscale, control->rect.y + 2 * control->دري->iscale,
                                   control->rect.w - 4 * control->دري->iscale, control->rect.h - 4 * control->دري->iscale);
            }
        }

    X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    X11_Toolkit_Draw_متن_Elements(control->دري, button_control->متن, control->rect.x + button_control->متن_rect.x, control->rect.y + button_control->متن_rect.y);
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

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_دري_X11 *دري, ثابت SDL_پيغام_Box_Button_معلومات *معلومات) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *بنياد_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(حجم(SDL_ToolkitButtonControlX11));
    بنياد_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_سيٽ_Error("Unable to allocate button control structure");
        أرجع عدم;
    }
    بنياد_control->دري = دري;
    بنياد_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
    بنياد_control->func_calc_سائيز = X11Toolkit_CalculateButtonControl;
    بنياد_control->func_draw = X11Toolkit_DrawButtonControl;
    بنياد_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    بنياد_control->func_free = X11Toolkit_DestroyButtonControl;
    بنياد_control->func_on_scale_change = عدم;
    بنياد_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
    بنياد_control->selected = false;
    بنياد_control->dynamic = true;
    بنياد_control->is_default_enter = false;
    بنياد_control->is_default_esc = false;
    إذا (معلومات->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        بنياد_control->is_default_esc = true;
    }
    إذا (معلومات->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        بنياد_control->is_default_enter = true;
        بنياد_control->selected = true;
    }
    control->cb = عدم;
    control->معلومات = معلومات;
#جيڪڏهن_وصف_ٿيل HAVE_FRIBIDI_H
    control->متن = X11_Toolkit_Make_متن_Elements(بنياد_control->دري, (حرف *)control->معلومات->متن, SDL_strlen(control->معلومات->متن), عدم);
#وإلا 
    control->متن = X11_Toolkit_Make_متن_Elements(بنياد_control->دري, (حرف *)control->معلومات->متن, SDL_strlen(control->معلومات->متن));
#جيڪڏهن_پورو
    X11_Toolkit_Shape_متن_Elements(بنياد_control->دري, control->متن);
    
    بنياد_control->do_سائيز = true;
    X11Toolkit_CalculateButtonControl(بنياد_control);
    بنياد_control->do_سائيز = false;

    X11_Toolkit_جوڙيو_Control_منزل_دري(دري, بنياد_control);
    أرجع بنياد_control;
}

فراغ X11_Toolkit_رجسٽر_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, فراغ *معلومات, فراغ (*cb)(بنية SDL_ToolkitControlX11 *, فراغ *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_معلومات = معلومات;
    button_control->cb = cb;
}

ثابت SDL_پيغام_Box_Button_معلومات *X11_Toolkit_Get_Button_Control_معلومات(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    أرجع button_control->معلومات;
}

فراغ X11_Toolkit_Destroy_دري(SDL_Toolkit_دري_X11 *معلومات) {
    صحيح i;

    إذا (!معلومات) {
        أرجع;
    }

#إذا SDL_GRAB
    إذا (معلومات->گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_MENU || معلومات->گهڻائي== SDL_TOOLKIT_دري_گهڻائي_X11_TOOLTIP) {
        X11_XUngrab_اشارو(معلومات->display, Current_وقت);
        X11_XUngrabKeyboard(معلومات->display, Current_وقت);
    }
#جيڪڏهن_پورو

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

#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري
    إذا (معلومات->pixmap && معلومات->shm) {
        X11_XShmDetach(معلومات->display, &معلومات->shm_info);
        إذا (!معلومات->shm_pixmap) {
            XDestroyImage(معلومات->image);
        }
        shmdt(معلومات->shm_info.shmaddr);
    }
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
    إذا (معلومات->font_سيٽ) {
        X11_XFree_Font_سيٽ(معلومات->display, معلومات->font_سيٽ);
        معلومات->font_سيٽ = عدم;
    }
#جيڪڏهن_پورو

    إذا (معلومات->font_struct) {
        X11_XFreeFont(معلومات->display, معلومات->font_struct);
        معلومات->font_struct = عدم;
    }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && معلومات->xdbe && !معلومات->pixmap) {
        X11_Xdbe_Deallocate_پٺ_بفر_Name(معلومات->display, معلومات->buf);
    }
#جيڪڏهن_پورو

    إذا (معلومات->xsettings) {
        xsettings_client_destroy(معلومات->xsettings);
    }

    X11_XFreeGC(معلومات->display, معلومات->ctx);

    إذا (معلومات->display) {
        إذا (معلومات->دري != None) {
            X11_XWithdraw_دري(معلومات->display, معلومات->دري, معلومات->screen);
            X11_XDestroy_دري(معلومات->display, معلومات->دري);
            معلومات->دري = None;
        }

        إذا (معلومات->display_close) {
            X11_XCloseDisplay(معلومات->display);
        }
        معلومات->display = عدم;
    }

#إذا SDL_سيٽ_LOCALE
    إذا (معلومات->origlocale && (معلومات->گهڻائي == SDL_TOOLKIT_دري_گهڻائي_X11_DIALOG)) {
        (فراغ)setlocale(LC_ALL, معلومات->origlocale);
        SDL_free(معلومات->origlocale);
    }
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(معلومات->fribidi);
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(معلومات->th);
#جيڪڏهن_پورو

    SDL_free(معلومات);
}

ساكن صحيح X11_Toolkit_ڳڻپ_سٽون_جو_متن(ثابت حرف *متن)
{
    صحيح نتيجو = 0;
    طالما (متن && *متن) {
        ثابت حرف *lf = SDL_strchr(متن, '\n');
        نتيجو++; // even without an endline, this counts as a line.
        متن = lf ? lf + 1 : عدم;
    }
    أرجع نتيجو;
}

ساكن فراغ X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحيح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->دري->display, control->دري->ctx, control->دري->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    لكل (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Draw_متن_Elements(control->دري, label_control->سٽون[i].متن, control->rect.x + label_control->سٽون[i].rect.x, control->rect.y + label_control->سٽون[i].rect.y);
    }
}

ساكن فراغ X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحيح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    لكل (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Free_متن_Elements(label_control->سٽون[i].متن);
    }
    SDL_free(label_control->سٽون);
    SDL_free(label_control);
}

ساكن فراغ X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *بنياد_control) {
    SDL_ToolkitLabelControlX11 *control;
    صحيح i;

    control = (SDL_ToolkitLabelControlX11 *)بنياد_control;
    
    إذا (بنياد_control->do_سائيز) {
        بنياد_control->rect.w = 0;
        بنياد_control->rect.h = 0;
    }
    
    لكل (i = 0; i < control->sz; i++) {
        صحيح font_h;
        
        font_h = X11_Toolkit_Get_متن_Elements_Rect(control->سٽون[i].متن, &control->سٽون[i].rect);
        
        إذا (بنياد_control->do_سائيز) {
            بنياد_control->rect.w = SDL_max(بنياد_control->rect.w, control->سٽون[i].rect.w);
        }
        
        إذا (i > 0) {
            control->سٽون[i].rect.y = font_h + control->سٽون[i - 1].rect.y;
        } وإلا {
            control->سٽون[i].rect.y = 0;
        }
    }

#جيڪڏهن_وصف_ٿيل HAVE_FRIBIDI_H
    إذا (بنياد_control->دري->fribidi) {
        FriBidiParType پهريون_ndn_dir;
        صحيح آخري_ndn;
    
        پهريون_ndn_dir = FRIBIDI_PAR_LTR;
        لكل (i = 0; i < control->sz; i++) {
            إذا (control->سٽون[i].par != FRIBIDI_PAR_ON) {
                پهريون_ndn_dir = control->سٽون[i].par;
            }
        }

        آخري_ndn = -1;
        لكل (i = 0; i < control->sz; i++) {
            بدل (control->سٽون[i].par) {
                حالة FRIBIDI_PAR_LTR:
                    control->سٽون[i].rect.x = 0;
                    آخري_ndn = i;
                    اكسر;
                حالة FRIBIDI_PAR_RTL:
                    control->سٽون[i].rect.x = بنياد_control->rect.w - control->سٽون[i].rect.w;
                    آخري_ndn = i;
                    اكسر;
                افتراضي:
                    إذا (آخري_ndn != -1) {
                        إذا (control->سٽون[آخري_ndn].par == FRIBIDI_PAR_RTL) {
                            control->سٽون[i].rect.x = بنياد_control->rect.w - control->سٽون[i].rect.w;
                        } وإلا {
                            control->سٽون[i].rect.x = 0;
                        }
                    } وإلا {
                        إذا (پهريون_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->سٽون[i].rect.x = بنياد_control->rect.w - control->سٽون[i].rect.w;
                        } وإلا {
                            control->سٽون[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#جيڪڏهن_پورو
    
    إذا (بنياد_control->do_سائيز && control->sz) {
        بنياد_control->rect.h = control->سٽون[control->sz - 1].rect.y + control->سٽون[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_دري_X11 *دري, حرف *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *بنياد_control;
    صحيح i;
    
    إذا (!utf8) {
        أرجع عدم;
    }
 
    إذا (!SDL_strcmp(utf8, "")) {
        أرجع عدم;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(حجم(SDL_ToolkitLabelControlX11));
    بنياد_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_سيٽ_Error("Unable to allocate label control structure");
        أرجع عدم;
    }
    بنياد_control->دري = دري;
    بنياد_control->func_draw = X11Toolkit_DrawLabelControl;
    بنياد_control->func_on_state_change = عدم;
    بنياد_control->func_calc_سائيز = X11Toolkit_CalculateLabelControl;
    بنياد_control->func_free  = X11Toolkit_DestroyLabelControl;
    بنياد_control->func_on_scale_change = عدم;
    بنياد_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_عام;
    بنياد_control->selected = false;
    بنياد_control->dynamic = false;
    بنياد_control->rect.w = 0;
    بنياد_control->rect.h = 0;
    بنياد_control->is_default_enter = false;
    بنياد_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_ڳڻپ_سٽون_جو_متن(utf8);
    control->سٽون = SDL_calloc(control->sz, حجم(SDL_Toolkit_Label_Control_سٽ_X11));
    لكل (i = 0; i < control->sz; i++) {
        ثابت حرف *lf = SDL_strchr(utf8, '\n');
        ثابت صحيح ڊيگهائي = lf ? (lf - utf8) : SDL_strlen(utf8);
        صحيح sz;
        
        sz = ڊيگهائي;
        إذا (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#جيڪڏهن_وصف_ٿيل HAVE_FRIBIDI_H
        control->سٽون[i].متن = X11_Toolkit_Make_متن_Elements(بنياد_control->دري, (حرف *)utf8, sz, &control->سٽون[i].par);
#وإلا 
        control->سٽون[i].متن = X11_Toolkit_Make_متن_Elements(بنياد_control->دري, (حرف *)utf8, sz);
#جيڪڏهن_پورو
        X11_Toolkit_Shape_متن_Elements(بنياد_control->دري, control->سٽون[i].متن);

        utf8 += ڊيگهائي + 1;
        إذا (!lf) {
            اكسر;
        }
    }

    بنياد_control->do_سائيز = true;
    X11Toolkit_CalculateLabelControl(بنياد_control);
    بنياد_control->do_سائيز = false;
    X11_Toolkit_جوڙيو_Control_منزل_دري(دري, بنياد_control);

    أرجع بنياد_control;
}

صحيح X11_Toolkit_Get_Label_Control_پهريون_سٽ_اوچائي(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    أرجع label_control->سٽون[0].rect.h;
}

فراغ X11_Toolkit_Signal_دري_Close(SDL_Toolkit_دري_X11 *معلومات) {
    معلومات->close = true;
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11
