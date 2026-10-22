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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

#ضمن "../../SDL_list.h"
#ضمن "SDL_x11video.h"
#اگر_تعریف_شده SDL_USE_LIBDBUS
#ضمن "../../core/linux/SDL_system_theme.h"
#پایان_اگر
#اگر_تعریف_شده HAVE_FRIBIDI_H
#ضمن "../../core/unix/SDL_fribidi.h"
#پایان_اگر
#ضمن "SDL_x11dyn.h"
#ضمن "SDL_x11toolkit.h"
#ضمن "SDL_x11settings.h"
#ضمن "SDL_x11modes.h"
#ضمن "xsettings-client.h"
#ضمن <X11/keysym.h>
#ضمن <locale.h>

#تعریف_کن SDL_مجموعه_LOCALE 1
#تعریف_کن SDL_GRAB 1

تعريفنوع تعداد SDL_Toolkit_متن_Type_X11
{
    SDL_TOOLKIT_متن_TYPE_X11_GENERIC,
    SDL_TOOLKIT_متن_TYPE_X11_THAI
} SDL_Toolkit_متن_Type_X11;

#اگر_تعریف_شده HAVE_LIBTHAI_H
تعريفنوع بنية SDL_ToolkitThaiOverlayX11
{
    bool بالاترین;
    حرف *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#پایان_اگر

تعريفنوع بنية SDL_Toolkit_متن_Element_X11
{
    SDL_Toolkit_متن_Type_X11 type;
    حرف *str;
    size_t sz;
    SDL_Rect rect;
    صحيح font_h;
    فراغ (*str_free)(فراغ *);
#اگر_تعریف_شده HAVE_LIBTHAI_H
    SDL_List_گره *thai_overlays;
#پایان_اگر
} SDL_Toolkit_متن_Element_X11;

تعريفنوع بنية SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 والد;

    /* Icon type */
    SDL_پیام_Box_Flags flags;
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

    /*داده*/
    ثابت SDL_پیام_Box_Button_داده *داده;

    /*متن*/
    SDL_List_گره *متن;
    SDL_Rect متن_rect;
    
    /* Callback */
    فراغ *cb_داده;
    فراغ (*cb)(بنية SDL_ToolkitControlX11 *, فراغ *);
} SDL_ToolkitButtonControlX11;

تعريفنوع بنية SDL_Toolkit_Label_Control_سطر_X11
{
    SDL_List_گره *متن;
    SDL_Rect rect;
#اگر_تعریف_شده HAVE_FRIBIDI_H
    FriBidiParType par;
#پایان_اگر
} SDL_Toolkit_Label_Control_سطر_X11;

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
    SDL_Toolkit_Label_Control_سطر_X11 *سطرها;
    size_t sz;
} SDL_ToolkitLabelControlX11;

تعريفنوع بنية SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 والد;

    SDL_List_گره *menu_اقلام;
} SDL_ToolkitMenuBarControlX11;

تعريفنوع بنية SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 والد;

    SDL_List_گره *menu_اقلام;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
ساكن ثابت حرف *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#تعریف_کن G_ICONFONT_اندازه 22

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
#تعریف_کن G_TOOLKITFONT_اندازه 140

ساكن ثابت SDL_پیام_Box_Color g_default_colors[SDL_MESSAGEBOX_COLOR_شمار] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#اگر_تعریف_شده SDL_USE_LIBDBUS
ساكن ثابت SDL_پیام_Box_Color g_default_colors_dark[SDL_MESSAGEBOX_COLOR_شمار] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#إذا 0
ساكن ثابت SDL_پیام_Box_Color g_default_colors_dark_بالا_contrast[SDL_MESSAGEBOX_COLOR_شمار] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

ساكن ثابت SDL_پیام_Box_Color g_default_colors_light_بالا_contrast[SDL_MESSAGEBOX_COLOR_شمار] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#پایان_اگر

#پایان_اگر

ساكن صحيح g_shm_error;
ساكن صحيح (*g_old_error_handler)(Display *, XErrorEvent *) = عدم;

ساكن صحيح X11_Toolkit_Shared_حافظه_Error_Handler(Display *d, XErrorEvent *e)
{
    إذا (e->error_کد == BadAccess || e->error_کد == BadRequest) {
        g_shm_error = True;
        أرجع 0;
    }
    أرجع g_old_error_handler(d, e);
}

ساكن فراغ X11_Toolkit_Init_پنجره_Pixmap(SDL_Toolkit_پنجره_X11 *داده) {
    إذا (داده->pixmap) {
#اگر_تعریف_نشده NO_SHARED_حافظه
        إذا (!داده->shm_pixmap) {
            داده->drawable = X11_XCreatePixmap(داده->display, داده->پنجره, داده->pixmap_عرض, داده->pixmap_ارتفاع, داده->عمق_2);
        }
#وإلا
        داده->drawable = X11_XCreatePixmap(داده->display, داده->پنجره, داده->pixmap_عرض, داده->pixmap_ارتفاع, داده->عمق_2);
#پایان_اگر
#اگر_تعریف_نشده NO_SHARED_حافظه
        إذا (داده->shm) {
            داده->image = X11_XShmCreateImage(داده->display, داده->visual, داده->عمق_2, ZPixmap, عدم, &داده->shm_info, داده->pixmap_عرض, داده->pixmap_ارتفاع);
            إذا (داده->image) {
                داده->shm_بایتها_در_هر_سطر = داده->image->بایتها_در_هر_سطر;

                داده->shm_info.shmid = shmget(IPC_خصوصی, داده->image->بایتها_در_هر_سطر * داده->image->ارتفاع, IPC_CREAT | 0777);
                إذا (داده->shm_info.shmid < 0) {
                    XDestroyImage(داده->image);
                    داده->image = عدم;
                    داده->shm = false;
                    أرجع;
                }

                داده->shm_info.readOnly = False;
                داده->shm_info.shmaddr = داده->image->داده = (حرف *)shmat(داده->shm_info.shmid, عدم, 0);
                إذا (((علامتدار حرف *)داده->shm_info.shmaddr) == (علامتدار حرف *)-1) {
                    XDestroyImage(داده->image);
                    داده->shm = false;
                    داده->image = عدم;
                    أرجع;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11_Toolkit_Shared_حافظه_Error_Handler);
                X11_XShmAttach(داده->display, &داده->shm_info);
                X11_XSync(داده->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                إذا (g_shm_error) {
                    XDestroyImage(داده->image);
                    shmdt(داده->shm_info.shmaddr);
                    shmctl(داده->shm_info.shmid, IPC_RMID, عدم);
                    داده->image = عدم;
                    داده->shm = false;
                    أرجع;
                }

                إذا (داده->shm_pixmap) {
                    داده->drawable = X11_XShmCreatePixmap(داده->display, داده->پنجره, داده->shm_info.shmaddr, &داده->shm_info, داده->pixmap_عرض, داده->pixmap_ارتفاع, داده->عمق_2);
                    إذا (داده->drawable == None) {
                        داده->shm_pixmap = False;
                    } وإلا {
                        XDestroyImage(داده->image);
                        داده->image = عدم;
                    }
                }

                shmctl(داده->shm_info.shmid, IPC_RMID, عدم);
            } وإلا {
                داده->shm = false;
            }
        }
#پایان_اگر
    }
}

ساكن فراغ X11_Toolkit_Init_پنجره_Fonts(SDL_Toolkit_پنجره_X11 *پنجره)
{    
    پنجره->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    پنجره->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#اگر_تعریف_شده X_HAVE_UTF8_STRING
    پنجره->utf8 = true;
    پنجره->font_مجموعه = عدم;
    إذا (SDL_X11_HAVE_UTF8) {
        حرف **missing = عدم;
        صحيح رقم_missing = 0;
        صحيح i_font;
        پنجره->font_struct = عدم;
        لكل (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            حرف *font;

            إذا (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_بارگیری_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_اندازه * پنجره->iscale);
                پنجره->font_مجموعه = X11_XCreate_Font_مجموعه(پنجره->display, font, &missing, &رقم_missing, عدم);
                SDL_free(font);

                إذا (!پنجره->font_مجموعه) {
                    إذا (پنجره->scale != 0 && پنجره->iscale > 0) {
                        پنجره->iscale = (صحيح)SDL_ceilf(پنجره->scale);
                        پنجره->scale = 0;
                    } وإلا {
                        پنجره->iscale--;
                    }
                    اذهب try_بارگیری_font;
                }
            } وإلا {
                پنجره->font_مجموعه = X11_XCreate_Font_مجموعه(پنجره->display, g_ToolkitFont[i_font], &missing, &رقم_missing, عدم);
            }

            إذا (missing) {
                X11_XFreeStringList(missing);
            }

            إذا (پنجره->font_مجموعه) {
                اكسر;
            }
        }

        إذا (!پنجره->font_مجموعه) {
            اذهب بارگیری_font_traditional;
        } وإلا {
            XFontStruct **font_structs;
            حرف **font_نامها;
            صحيح font_sz;
            صحيح i;
            
#اگر_تعریف_شده HAVE_FRIBIDI_H
            پنجره->do_shaping = !X11_XContextDependentDrawing(پنجره->font_مجموعه);
#پایان_اگر
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFonts_از_Font_مجموعه(پنجره->font_مجموعه, &font_structs, &font_نامها);
            لكل (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                إذا (SDL_strstr(font_نامها[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } وإلا إذا (SDL_strstr(font_نامها[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } وإلا إذا (SDL_strstr(font_نامها[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } وإلا إذا (SDL_strstr(font_نامها[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } وإلا إذا (SDL_strstr(font_نامها[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                إذا (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(پنجره->display, font_نامها[i]);
                    إذا (font_struct) {
                        إذا (font_struct->در_هر_char) {
                            صحيح glyphs_sz;
                            صحيح j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            لكل (j = 0; j < glyphs_sz; j++) {
                                إذا (font_struct->در_هر_char[j].lbearing < 0) {
                                    پنجره->thai_font = SDL_TOOLKIT_THAI_FONT_X11_جابه_جایی;
                                }
                            }
                        }
                        X11_XFreeFont(پنجره->display, font_struct);
                    }
                }
                
                پنجره->thai_encoding = thai_encoding;
            } 
        }
    } وإلا
#پایان_اگر
    {
        حرف *font;

        بارگیری_font_traditional:
        پنجره->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_اندازه * پنجره->iscale);
        پنجره->font_struct = X11_XLoadQueryFont(پنجره->display, font);
        SDL_free(font);
        إذا (!پنجره->font_struct) {
            إذا (پنجره->iscale > 0) {
                إذا (پنجره->scale != 0) {
                    پنجره->iscale = (صحيح)SDL_ceilf(پنجره->scale);
                    پنجره->scale = 0;
                } وإلا {
                    پنجره->iscale--;
                }
                اذهب بارگیری_font_traditional;
            } وإلا {
                پنجره->font_struct = X11_XLoadQueryFont(پنجره->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

ساكن فراغ X11Toolkit_SettingsNotify(ثابت حرف *name, XSettingsAction action, XSettingsSetting *setting, فراغ *داده)
{
    SDL_Toolkit_پنجره_X11 *پنجره;
    صحيح i;

    پنجره = داده;

    إذا (پنجره->xsettings_اولی_زمان) {
        أرجع;
    }

    إذا (SDL_strcmp(name, SDL_XSETTINGS_GDK_پنجره_SCALING_ضریب) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_راهاندازی = false;
        bool pixmap_already_راهاندازی = false;

        إذا (پنجره->pixmap) {
            pixmap_already_راهاندازی = true;
        } وإلا {
            dbe_already_راهاندازی = true;
        }

        /* set scale vars */
        پنجره->scale = X11_GetGlobalContentScale(پنجره->display, پنجره->xsettings);
        پنجره->iscale = (صحيح)SDL_ceilf(پنجره->scale);
        إذا (پنجره->scale < 1) {
            پنجره->scale = 1;
        }
        إذا (SDL_roundf(پنجره->scale) == پنجره->scale) {
            پنجره->scale = 0;
        }

        /* setup fonts */
#اگر_تعریف_شده X_HAVE_UTF8_STRING
        إذا (پنجره->font_مجموعه) {
            X11_XFree_Font_مجموعه(پنجره->display, پنجره->font_مجموعه);
        }
#پایان_اگر
        إذا (پنجره->font_struct) {
            X11_XFreeFont(پنجره->display, پنجره->font_struct);
        }

        X11_Toolkit_Init_پنجره_Fonts(پنجره);

        /* set up window */
        إذا (پنجره->scale != 0) {
            پنجره->پنجره_عرض = SDL_lroundf((پنجره->پنجره_عرض/پنجره->iscale) * پنجره->scale);
            پنجره->پنجره_ارتفاع = SDL_lroundf((پنجره->پنجره_ارتفاع/پنجره->iscale) * پنجره->scale);
            پنجره->pixmap_عرض = پنجره->پنجره_عرض;
            پنجره->pixmap_ارتفاع = پنجره->پنجره_ارتفاع;
            پنجره->pixmap = true;
        } وإلا {
            پنجره->pixmap = false;
        }

        إذا (پنجره->pixmap) {
            إذا (!pixmap_already_راهاندازی) {
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XDBE
                إذا (SDL_X11_HAVE_XDBE && پنجره->xdbe) {
                    X11_Xdbe_Deallocate_پشت_میانگیر_Name(پنجره->display, پنجره->buf);
                }
#پایان_اگر
            }
            X11_XFreePixmap(پنجره->display, پنجره->drawable);
            X11_Toolkit_Init_پنجره_Pixmap(پنجره);
        } وإلا {
            إذا (!dbe_already_راهاندازی) {
                X11_XFreePixmap(پنجره->display, پنجره->drawable);
#اگر_تعریف_نشده NO_SHARED_حافظه
                إذا (پنجره->image) {
                    XDestroyImage(پنجره->image);
                    پنجره->image = عدم;
                }
#پایان_اگر
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XDBE
                إذا (SDL_X11_HAVE_XDBE && پنجره->xdbe) {
                    پنجره->buf = X11_Xdbe_Allocate_پشت_میانگیر_Name(پنجره->display, پنجره->پنجره, XdbeUndefined);
                    پنجره->drawable = پنجره->buf;
                }
#پایان_اگر
            }
        }

        /* notify controls */
        لكل (i = 0; i < پنجره->controls_sz; i++) {
            پنجره->controls[i]->do_اندازه = true;

            إذا (پنجره->controls[i]->func_on_scale_change) {
                پنجره->controls[i]->func_on_scale_change(پنجره->controls[i]);
            }

            إذا (پنجره->controls[i]->func_calc_اندازه) {
                پنجره->controls[i]->func_calc_اندازه(پنجره->controls[i]);
            }

            پنجره->controls[i]->do_اندازه = false;
        }

        /* notify cb */
        إذا (پنجره->cb_on_scale_change) {
            پنجره->cb_on_scale_change(پنجره, پنجره->cb_داده);
        }

        /* update ev scales */
        إذا (!پنجره->pixmap) {
            پنجره->ev_scale = پنجره->ev_iscale = 1;
        } وإلا {
            پنجره->ev_scale = پنجره->scale;
            پنجره->ev_iscale = پنجره->iscale;
        }
    }
}

ساكن فراغ X11_Toolkit_Get_متن_عرض_ارتفاع_For_Font(XFontStruct *font, ثابت حرف *str, صحيح nbytes, صحيح *pwidth, صحيح *pheight, صحيح *ascent, صحيح *font_ارتفاع)
{
    XCharStruct متن_structure;
    صحيح font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &متن_structure);
    *pwidth = متن_structure.عرض;
    *pheight = متن_structure.ascent + متن_structure.descent;
    *ascent = متن_structure.ascent;
    إذا (font_ارتفاع) {
       *font_ارتفاع = font_ascent + font_descent;
    }
}

ساكن فراغ X11_Toolkit_Get_متن_عرض_ارتفاع(SDL_Toolkit_پنجره_X11 *داده, ثابت حرف *str, صحيح nbytes, صحيح *pwidth, صحيح *pheight, صحيح *ascent, صحيح *descent, صحيح *font_ارتفاع)
{
#اگر_تعریف_شده X_HAVE_UTF8_STRING
    إذا (داده->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8_متن_Extents(داده->font_مجموعه, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.عرض;
        *pheight = overall_logical.ارتفاع;
        *ascent = -overall_logical.y;
        *descent = overall_logical.ارتفاع - *ascent;

        إذا (font_ارتفاع) {
            XFont_مجموعه_Extents *extents;

            extents = X11_XExtents_از_Font_مجموعه(داده->font_مجموعه);
            *font_ارتفاع = extents->max_logical_extent.ارتفاع;
        }
    } وإلا
#پایان_اگر
    {
        XCharStruct متن_structure;
        صحيح font_direction, font_ascent, font_descent;
        X11_XTextExtents(داده->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &متن_structure);
        *pwidth = متن_structure.عرض;
        *pheight = متن_structure.ascent + متن_structure.descent;
        *ascent = متن_structure.ascent;
        *descent = متن_structure.descent;

        إذا (font_ارتفاع) {
            *font_ارتفاع = font_ascent + font_descent;
        }
    }
}

#اگر_تعریف_شده HAVE_FRIBIDI_H
SDL_List_گره *X11_Toolkit_Make_متن_Elements(SDL_Toolkit_پنجره_X11 *داده, حرف *txt, size_t sz, FriBidiParType *par)
#وإلا
SDL_List_گره *X11_Toolkit_Make_متن_Elements(SDL_Toolkit_پنجره_X11 *داده, حرف *txt, size_t sz)
#پایان_اگر
{
    SDL_List_گره *list;
    حرف *str;
    حرف *میانگیر_2;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = عدم;
    thai = 0;
    str = txt;
    میانگیر_2 = SDL_malloc(1);
    میانگیر_2[0] = 0;
    
#اگر_تعریف_شده HAVE_FRIBIDI_H
    إذا (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    إذا (داده->fribidi) {
        حرف *fstr;
                
        fstr = SDL_FriBidi_Process(داده->fribidi, str, sz, داده->do_shaping, par);
        إذا (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#پایان_اگر        

    طالما (1) {
        حرف *new;
        حرف utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_گام_UTF8((ثابت حرف **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        إذا (cp == 0 || cond == (thai ? false : true)) {
            SDL_Toolkit_متن_Element_X11 *element;
            
            element = SDL_malloc(حجم(SDL_Toolkit_متن_Element_X11));
            إذا (thai) {
                element->type = SDL_TOOLKIT_متن_TYPE_X11_THAI;
            } وإلا {
                element->type = SDL_TOOLKIT_متن_TYPE_X11_GENERIC;
            }
            element->str = SDL_strdup(میانگیر_2);
            element->sz = SDL_strlen(میانگیر_2);
            element->str_free = SDL_free;
            
            SDL_List_جمع_کن(&list, element);
            
            SDL_free(میانگیر_2);
            میانگیر_2 = SDL_malloc(1);
            میانگیر_2[0] = 0;
            thai = thai ? false : true;
        }

        إذا (!cp) {
            اكسر;
        }
        
        SDL_UCS4_مقصد_UTF8(cp, utf8);
        csz = SDL_strlen(میانگیر_2) + SDL_strlen(utf8) + 1;
        new = SDL_malloc(csz);
        SDL_strlcpy(new, میانگیر_2, csz);
        SDL_strlcat(new, utf8, csz);
        SDL_free(میانگیر_2);
        میانگیر_2 = new;
    }

    SDL_free(میانگیر_2);
    إذا (free_txt) {
        SDL_free(txt);
    }
    أرجع list;
}

فراغ X11_Toolkit_Shape_متن_Elements(SDL_Toolkit_پنجره_X11 *داده, SDL_List_گره *list)
{
    SDL_List_گره *cursor;
    SDL_Toolkit_متن_Element_X11 *prev;
    صحيح موقت;
    
    /* Shape and calculate bounding box */
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->مدخل;
#اگر_تعریف_شده HAVE_LIBTHAI_H
        element->thai_overlays = عدم;
#پایان_اگر
        إذا (element->type == SDL_TOOLKIT_متن_TYPE_X11_THAI) {
            إذا (داده->thai_font == SDL_TOOLKIT_THAI_FONT_X11_جابه_جایی) {
                X11_Toolkit_Get_متن_عرض_ارتفاع(داده, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &موقت, عدم);
            } وإلا {
#اگر_تعریف_شده HAVE_LIBTHAI_H
                إذا (داده->th) {
                    بنية thcell_t *cells;
                    حرف *tis_str;
                    حرف *پایه_tis_str;
                    size_t cells_sz;
                    size_t پایه_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, حجم(بنية thcell_t));
                    داده->th->make_cells((ثابت thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    پایه_tis_str_sz = cells_sz;
                    پایه_tis_str = SDL_malloc(پایه_tis_str_sz + 1);
                    لكل (موقت = 0; موقت < cells_sz; موقت++) {
                        پایه_tis_str[موقت] = cells[موقت].پایه;
                        
                        إذا (cells[موقت].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            حرف *pre;
                            صحيح temp2;
                            
                            overlay = SDL_malloc(حجم(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", پایه_tis_str, موقت);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت حرف *)&cells[موقت].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->بالاترین = false;
                            X11_Toolkit_Get_متن_عرض_ارتفاع(داده, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, عدم);
                            X11_Toolkit_Get_متن_عرض_ارتفاع(داده, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, عدم);
                            SDL_List_جمع_کن(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        إذا (cells[موقت].بالاترین) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            حرف *pre;
                            صحيح temp2;
                            
                            overlay = SDL_malloc(حجم(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", پایه_tis_str, موقت);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت حرف *)&cells[موقت].بالاترین, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->بالاترین = true;
                            X11_Toolkit_Get_متن_عرض_ارتفاع(داده, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, عدم);
                            X11_Toolkit_Get_متن_عرض_ارتفاع(داده, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, عدم);
                            SDL_List_جمع_کن(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    پایه_tis_str[پایه_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", پایه_tis_str, پایه_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11_Toolkit_Get_متن_عرض_ارتفاع(داده, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &موقت, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(پایه_tis_str);
                }
#وإلا
                X11_Toolkit_Get_متن_عرض_ارتفاع(داده, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &موقت, &element->font_h);
#پایان_اگر            
            }
        } وإلا {
            X11_Toolkit_Get_متن_عرض_ارتفاع(داده, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &موقت, &element->font_h);
        }
        
        cursor = cursor->بعدی;
    }
    
    /* Add offsets */
    prev = عدم;
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->مدخل;        
        إذا (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } وإلا {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->بعدی;
    }
}


فراغ X11_Toolkit_Draw_متن_Elements(SDL_Toolkit_پنجره_X11 *داده, SDL_List_گره *list, صحيح x, صحيح y)
{
    SDL_List_گره *cursor;
    
    cursor = list;
    
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->مدخل;
        إذا (element->type == SDL_TOOLKIT_متن_TYPE_X11_THAI) {
            إذا (داده->thai_font == SDL_TOOLKIT_THAI_FONT_X11_جابه_جایی) {
#اگر_تعریف_شده X_HAVE_UTF8_STRING
                إذا (داده->utf8) {
                    X11_Xutf8DrawString(داده->display, داده->drawable, داده->font_مجموعه, داده->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } وإلا
#پایان_اگر
                {
                    X11_XDrawString(داده->display, داده->drawable, داده->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } وإلا {    
#اگر_تعریف_شده HAVE_LIBTHAI_H
                SDL_List_گره *overlay_cursor;
                    
                /* Draw the base string */
#اگر_تعریف_شده X_HAVE_UTF8_STRING
                إذا (داده->utf8) {
                    X11_Xutf8DrawString(داده->display, داده->drawable, داده->font_مجموعه, داده->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } وإلا
#پایان_اگر
                {
                    X11_XDrawString(داده->display, داده->drawable, داده->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                طالما (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->مدخل;
#اگر_تعریف_شده X_HAVE_UTF8_STRING
                    إذا (داده->utf8) {
                        X11_Xutf8DrawString(داده->display, داده->drawable, داده->font_مجموعه, داده->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } وإلا
#پایان_اگر
                    {
                        X11_XDrawString(داده->display, داده->drawable, داده->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->بعدی;
                }
#پایان_اگر                
            }
        } وإلا {
#اگر_تعریف_شده X_HAVE_UTF8_STRING
            إذا (داده->utf8) {
                X11_Xutf8DrawString(داده->display, داده->drawable, داده->font_مجموعه, داده->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } وإلا
#پایان_اگر
            {
                X11_XDrawString(داده->display, داده->drawable, داده->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->بعدی;
    }
}

صحيح X11_Toolkit_Get_متن_Elements_Rect(SDL_List_گره *list, SDL_Rect *بیرون)
{
    SDL_List_گره *cursor;
    صحيح ret;
    
    ret = 0;
    بیرون->x = بیرون->y = 0;
    بیرون->w = بیرون->h = 0;
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
        
        element = cursor->مدخل;
        
        بیرون->w += element->rect.w;
        بیرون->h = SDL_max(بیرون->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->بعدی;
    }
    
    أرجع ret;
}

فراغ X11_Toolkit_Free_متن_Elements_List_Contents(SDL_List_گره *list)
{
    SDL_List_گره *cursor;
    
    cursor = list;
    طالما (cursor) {
        SDL_Toolkit_متن_Element_X11 *element;
#اگر_تعریف_شده HAVE_LIBTHAI_H
        SDL_List_گره *overlay_cursor;
#پایان_اگر

        element = cursor->مدخل;
        
        إذا (element->str_free) {
            element->str_free(element->str);
        }
        
#اگر_تعریف_شده HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        طالما (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->مدخل;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->بعدی;
        }
        SDL_ListClear(&element->thai_overlays);
#پایان_اگر
        
        SDL_free(element);
        
        cursor = cursor->بعدی;
    }
}

#تعریف_کن X11_Toolkit_Free_متن_Elements(x) X11_Toolkit_Free_متن_Elements_List_Contents(x); SDL_ListClear(&x)
 
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

SDL_Toolkit_پنجره_X11 *X11_Toolkit_Create_پنجره_Struct(SDL_پنجره *والد, SDL_Toolkit_پنجره_X11 *tkparent, SDL_Toolkit_پنجره_نما_X11 نما, ثابت SDL_پیام_Box_Color *colorhints, bool create_new_display)
{
    SDL_Toolkit_پنجره_X11 *پنجره;
    صحيح i;
#اگر_تعریف_شده SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#پایان_اگر
    #تعریف_کن ErrorFreeRetNull(x, y) SDL_مجموعه_Error(x); SDL_free(y); أرجع عدم
    #تعریف_کن ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_مجموعه_Error(x, y); SDL_free(z); أرجع عدم

    إذا (!SDL_X11_بارگیری_Symbols()) {
        أرجع عدم;
    }

    // This code could get called from multiple threads maybe?
    X11_XInit_نخها();

    پنجره = (SDL_Toolkit_پنجره_X11 *)SDL_malloc(حجم(SDL_Toolkit_پنجره_X11));
    إذا (!پنجره) {
        SDL_مجموعه_Error("Unable to allocate toolkit window structure");
        أرجع عدم;
    }

    پنجره->نما = نما;
    پنجره->tk_والد = tkparent;

#إذا SDL_مجموعه_LOCALE
    إذا (نما == SDL_TOOLKIT_پنجره_نما_X11_DIALOG) {
        پنجره->origlocale = setlocale(LC_ALL, عدم);
        إذا (پنجره->origlocale) {
            پنجره->origlocale = SDL_strdup(پنجره->origlocale);
            إذا (!پنجره->origlocale) {
                SDL_free(پنجره);
                أرجع عدم;
            }
            (فراغ)setlocale(LC_ALL, "");
        }
    }
#پایان_اگر

    پنجره->والد_device = عدم;
    إذا (create_new_display) {
        پنجره->display = X11_XOpenDisplay(عدم);
        پنجره->display_close = true;
        إذا (!پنجره->display) {
            ErrorFreeRetNull("Couldn't open X11 display", پنجره);
        }
    } وإلا {
        إذا (والد) {
            پنجره->والد_device = SDL_GetVideoDevice();
            پنجره->display = پنجره->والد_device->داخلی->display;
            پنجره->display_close = false;
        } وإلا إذا (tkparent) {
            پنجره->display = tkparent->display;
            پنجره->display_close = false;
        } وإلا {
            پنجره->display = X11_XOpenDisplay(عدم);
            پنجره->display_close = true;
            إذا (!پنجره->display) {
                ErrorFreeRetNull("Couldn't open X11 display", پنجره);
            }
        }
    }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
    صحيح xrandr_event_پایه, xrandr_error_پایه;
    پنجره->xrandr = X11_XRRQueryExtension(پنجره->display, &xrandr_event_پایه, &xrandr_error_پایه);
#پایان_اگر

#اگر_تعریف_نشده NO_SHARED_حافظه
    پنجره->shm_pixmap = False;
    پنجره->shm = X11_XShmQueryExtension(پنجره->display) ? SDL_X11_HAVE_SHM : false;
    إذا (پنجره->shm) {
        صحيح major;
        صحيح minor;

        X11_XShm_Query_نسخه(پنجره->display, &major, &minor, &پنجره->shm_pixmap);
        إذا (پنجره->shm_pixmap) {
            إذا (X11_XShmPixmapFormat(پنجره->display) != ZPixmap) {
                پنجره->shm_pixmap = False;
            }
        }
    }
#پایان_اگر

    /* Scale/Xsettings */
    پنجره->pixmap = false;
    پنجره->xsettings_اولی_زمان = true;
    پنجره->xsettings = xsettings_client_new(پنجره->display, DefaultScreen(پنجره->display), X11Toolkit_SettingsNotify, عدم, پنجره);
    پنجره->xsettings_اولی_زمان = false;
    پنجره->scale = X11_GetGlobalContentScale(پنجره->display, پنجره->xsettings);
    إذا (پنجره->scale < 1) {
        پنجره->scale = 1;
    }
    پنجره->iscale = (صحيح)SDL_ceilf(پنجره->scale);
    إذا (SDL_roundf(پنجره->scale) == پنجره->scale) {
        پنجره->scale = 0;
    }

    /* Fonts */
    X11_Toolkit_Init_پنجره_Fonts(پنجره);

    /* Color hints */
#اگر_تعریف_شده SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    إذا (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#پایان_اگر

    إذا (!colorhints) {
#اگر_تعریف_شده SDL_USE_LIBDBUS
        بدل (theme) {
            حالة SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                اكسر;
#إذا 0
            حالة SDL_SYSTEM_THEME_LIGHT_بالا_CONTRAST:
                colorhints = g_default_colors_light_بالا_contrast;
                اكسر;
            حالة SDL_SYSTEM_THEME_DARK_بالا_CONTRAST:
                colorhints = g_default_colors_dark_بالا_contrast;
                اكسر;
#پایان_اگر
            افتراضي:
                colorhints = g_default_colors;
        }
#وإلا
        colorhints = g_default_colors;
#پایان_اگر
    }
    پنجره->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    لكل (i = 0; i < SDL_MESSAGEBOX_COLOR_شمار; i++) {
        پنجره->xcolor[i].flags = DoRed|DoGreen|DoBlue;
        پنجره->xcolor[i].red = colorhints[i].r * 257;
        پنجره->xcolor[i].green = colorhints[i].g * 257;
        پنجره->xcolor[i].blue = colorhints[i].b * 257;
    }

    /* Generate bevel and pressed colors */
    پنجره->xcolor_bevel_l1.flags = DoRed|DoGreen|DoBlue;
    پنجره->xcolor_bevel_l1.red = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 12500, 0, 65535);
    پنجره->xcolor_bevel_l1.green = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 12500, 0, 65535);
    پنجره->xcolor_bevel_l1.blue = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 12500, 0, 65535);

    پنجره->xcolor_bevel_l2.flags = DoRed|DoGreen|DoBlue;
    پنجره->xcolor_bevel_l2.red = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 32500, 0, 65535);
    پنجره->xcolor_bevel_l2.green = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 32500, 0, 65535);
    پنجره->xcolor_bevel_l2.blue = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 32500, 0, 65535);

    پنجره->xcolor_bevel_d.flags = DoRed|DoGreen|DoBlue;
    پنجره->xcolor_bevel_d.red = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red - 22500, 0, 65535);
    پنجره->xcolor_bevel_d.green = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green - 22500, 0, 65535);
    پنجره->xcolor_bevel_d.blue = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue - 22500, 0, 65535);

    پنجره->xcolor_pressed.flags = DoRed|DoGreen|DoBlue;
    پنجره->xcolor_pressed.red = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].red - 12500, 0, 65535);
    پنجره->xcolor_pressed.green = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].green - 12500, 0, 65535);
    پنجره->xcolor_pressed.blue = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].blue - 12500, 0, 65535);

    پنجره->xcolor_disabled_متن.flags = DoRed|DoGreen|DoBlue;
    پنجره->xcolor_disabled_متن.red = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_متن].red + 19500, 0, 65535);
    پنجره->xcolor_disabled_متن.green = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_متن].green + 19500, 0, 65535);
    پنجره->xcolor_disabled_متن.blue = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_متن].blue + 19500, 0, 65535);

    /* Screen */
    پنجره->والد = والد;
    إذا (والد) {
        SDL_Display_داده *displaydata = SDL_Get_Display_Driver_داده_For_پنجره(والد);
        پنجره->screen = displaydata->screen;
    } وإلا {
        پنجره->screen = DefaultScreen(پنجره->display);
    }

    /* Visuals */
    إذا (نما == SDL_TOOLKIT_پنجره_نما_X11_فرزند) {
        پنجره->visual = والد->داخلی->visual;
        پنجره->cmap = والد->داخلی->colormap;
        X11_GetVisualInfoFromVisual(پنجره->display, پنجره->visual, &پنجره->vi);
        پنجره->عمق_2 = پنجره->vi.عمق_2;
    } وإلا {
        پنجره->visual = DefaultVisual(پنجره->display, پنجره->screen);
        پنجره->cmap = DefaultColormap(پنجره->display, پنجره->screen);
        پنجره->عمق_2 = Default_عمق(پنجره->display, پنجره->screen);
        X11_GetVisualInfoFromVisual(پنجره->display, پنجره->visual, &پنجره->vi);
    }

    /* Allocate colors */
    لكل (i = 0; i < SDL_MESSAGEBOX_COLOR_شمار; i++) {
        X11_XAllocColor(پنجره->display, پنجره->cmap, &پنجره->xcolor[i]);
    }
    X11_XAllocColor(پنجره->display, پنجره->cmap, &پنجره->xcolor_bevel_l1);
    X11_XAllocColor(پنجره->display, پنجره->cmap, &پنجره->xcolor_bevel_l2);
    X11_XAllocColor(پنجره->display, پنجره->cmap, &پنجره->xcolor_bevel_d);
    X11_XAllocColor(پنجره->display, پنجره->cmap, &پنجره->xcolor_pressed);
    X11_XAllocColor(پنجره->display, پنجره->cmap, &پنجره->xcolor_disabled_متن);

    /* Control list */
    پنجره->has_focus = false;
    پنجره->controls = عدم;
    پنجره->controls_sz = 0;
    پنجره->dyn_controls_sz = 0;
    پنجره->fiddled_control = عدم;
    پنجره->dyn_controls = عدم;

    /* Menu windows */
    پنجره->popup_windows = عدم;

    /* BIDI engine */
#اگر_تعریف_شده HAVE_FRIBIDI_H
    پنجره->fribidi = SDL_FriBidi_Create();
#پایان_اگر

#اگر_تعریف_شده HAVE_LIBTHAI_H
    پنجره->th = SDL_LibThai_Create();
#پایان_اگر
    
    /* Interface direction */
    پنجره->flip_interface = X11Toolkit_ShouldFlipUI();
    
    أرجع پنجره;
}

ساكن فراغ X11_Toolkit_جمع_کن_Control_مقصد_پنجره(SDL_Toolkit_پنجره_X11 *پنجره, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    پنجره->controls_sz++;
    إذا (پنجره->controls_sz == 1) {
        پنجره->controls = (بنية SDL_ToolkitControlX11 **)SDL_malloc(حجم(بنية SDL_ToolkitControlX11 *));
    } وإلا {
        پنجره->controls = (بنية SDL_ToolkitControlX11 **)SDL_realloc(پنجره->controls, حجم(بنية SDL_ToolkitControlX11 *) * پنجره->controls_sz);
    }
    پنجره->controls[پنجره->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    إذا (control->dynamic) {
        پنجره->dyn_controls_sz++;
        إذا (پنجره->dyn_controls_sz == 1) {
            پنجره->dyn_controls = (بنية SDL_ToolkitControlX11 **)SDL_malloc(حجم(بنية SDL_ToolkitControlX11 *));
        } وإلا {
            پنجره->dyn_controls = (بنية SDL_ToolkitControlX11 **)SDL_realloc(پنجره->dyn_controls, حجم(بنية SDL_ToolkitControlX11 *) * پنجره->dyn_controls_sz);
        }
        پنجره->dyn_controls[پنجره->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    إذا (control->selected) {
        پنجره->focused_control = control;
    }
}

bool X11_Toolkit_Create_پنجره_Res(SDL_Toolkit_پنجره_X11 *داده, صحيح w, صحيح h, صحيح cx, صحيح cy, حرف *title)
{
    صحيح x, y;
    XSizeHints *sizehints;
    XSet_پنجره_صفات wnd_attr;
    Atom NET_WM_پنجره_TYPE, NET_WM_پنجره_TYPE_DIALOG, NET_WM_پنجره_TYPE_DROPDOWN_MENU, NET_WM_پنجره_TYPE_TOOLTIP;
    SDL_پنجره_داده *windowdata = عدم;
    Display *display = داده->display;
    XGCValues ctx_vals;
    پنجره_2 ریشه_win;
    پنجره_2 والد_win;
    بیعلامت دراز gcflags = GCForeground | GCBackground;
    بیعلامت دراز valuemask;
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
#اگر_تعریف_شده XRANDR_DISABLED_BY_DEFAULT
    ثابت bool use_xrandr_by_default = false;
#وإلا
    ثابت bool use_xrandr_by_default = true;
#پایان_اگر
#پایان_اگر

    إذا (داده->scale == 0) {
        داده->پنجره_عرض = w;
        داده->پنجره_ارتفاع = h;
    } وإلا {
        داده->پنجره_عرض = SDL_lroundf((w/داده->iscale) * داده->scale);
        داده->پنجره_ارتفاع = SDL_lroundf((h/داده->iscale) * داده->scale);
        داده->pixmap_عرض = w;
        داده->pixmap_ارتفاع = h;
        داده->pixmap = true;
    }

    إذا (داده->والد) {
        windowdata = داده->والد->داخلی;
    }

    valuemask = CWEvent_ماسک | CWColormap;
    داده->event_ماسک = Exposure_ماسک |
                       Button_Press_ماسک | Button_Release_ماسک | کلید_Press_ماسک | کلید_Release_ماسک |
                       Structure_Notify_ماسک | Focus_Change_ماسک | اشاره_گر_Motion_ماسک;
    wnd_attr.event_ماسک = داده->event_ماسک;
    wnd_attr.colormap = داده->cmap;
    إذا (داده->نما == SDL_TOOLKIT_پنجره_نما_X11_MENU || داده->نما== SDL_TOOLKIT_پنجره_نما_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    ریشه_win = ریشه_پنجره(display, داده->screen);
    إذا (داده->نما == SDL_TOOLKIT_پنجره_نما_X11_فرزند) {
        والد_win = windowdata->xwindow;
    } وإلا {
        والد_win = ریشه_win;
    }

    داده->پنجره = X11_XCreate_پنجره(
        display, والد_win,
        0, 0,
        داده->پنجره_عرض, داده->پنجره_ارتفاع,
        0, داده->عمق_2, درون_داد_Output, داده->visual,
        valuemask, &wnd_attr);
    إذا (داده->پنجره == None) {
        أرجع SDL_مجموعه_Error("Couldn't create X window");
    }

    إذا (windowdata && داده->نما == SDL_TOOLKIT_پنجره_نما_X11_DIALOG) {
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
        X11_XChangeProperty(display, داده->پنجره, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_نما_Replace, (بیعلامت حرف *)stateatoms, statecount);
    }

    إذا (windowdata && داده->نما != SDL_TOOLKIT_پنجره_نما_X11_فرزند) {
        X11_XSetTransientForHint(display, داده->پنجره, windowdata->xwindow);
    }

    إذا (داده->tk_والد) {
        X11_XSetTransientForHint(display, داده->پنجره, داده->tk_والد->پنجره);
    }

    SDL_X11_مجموعه_پنجره_Title(display, داده->پنجره, title);

    // Let the window manager the type of the window
    إذا (داده->نما == SDL_TOOLKIT_پنجره_نما_X11_DIALOG) {
        NET_WM_پنجره_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_پنجره_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, داده->پنجره, NET_WM_پنجره_TYPE, XA_ATOM, 32,
                            Prop_نما_Replace,
                            (بیعلامت حرف *)&NET_WM_پنجره_TYPE_DIALOG, 1);
    } وإلا إذا (داده->نما == SDL_TOOLKIT_پنجره_نما_X11_MENU) {
        NET_WM_پنجره_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_پنجره_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, داده->پنجره, NET_WM_پنجره_TYPE, XA_ATOM, 32,
                            Prop_نما_Replace,
                            (بیعلامت حرف *)&NET_WM_پنجره_TYPE_DROPDOWN_MENU, 1);
    } وإلا إذا (داده->نما == SDL_TOOLKIT_پنجره_نما_X11_TOOLTIP) {
        NET_WM_پنجره_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_پنجره_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, داده->پنجره, NET_WM_پنجره_TYPE, XA_ATOM, 32,
                            Prop_نما_Replace,
                            (بیعلامت حرف *)&NET_WM_پنجره_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    داده->wm_delete_پیام = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, داده->پنجره, &داده->wm_delete_پیام, 1);
    داده->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    إذا (داده->نما == SDL_TOOLKIT_پنجره_نما_X11_MENU || داده->نما== SDL_TOOLKIT_پنجره_نما_X11_TOOLTIP) {
        x = cx;
        y = cy;
        اذهب MOVEWINDOW;
    }
    إذا (windowdata) {
        XWindow_صفات attrib;
        پنجره_2 dummy;

        X11_XGet_پنجره_صفات(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.عرض - داده->پنجره_عرض) / 2;
        y = attrib.y + (attrib.ارتفاع - داده->پنجره_ارتفاع) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, ریشه_پنجره(display, داده->screen), x, y, &x, &y, &dummy);
    } وإلا {
        ثابت SDL_VideoDevice *dev = SDL_GetVideoDevice();
        إذا (dev && dev->displays && dev->رقم_displays > 0) {
            ثابت SDL_VideoDisplay *dpy = dev->displays[0];
            ثابت SDL_Display_داده *dpydata = dpy->داخلی;
            x = dpydata->x + ((dpy->current_نما->w - داده->پنجره_عرض) / 2);
            y = dpydata->y + ((dpy->current_نما->h - داده->پنجره_ارتفاع) / 3);
        }
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
        وإلا إذا (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && داده->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_بیرون;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, ریشه_win);
            إذا (!screen_res) {
                اذهب NOXRANDR;
            }

            default_بیرون = X11_XRRGetOutputPrimary(display, ریشه_win);
            إذا (default_بیرون != None) {
                XRROutputInfo *بیرون_info;

                بیرون_info = X11_XRRGetOutputInfo(display, screen_res, default_بیرون);
                إذا (بیرون_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(بیرون_info);
                    اذهب FIRSTOUTPUTXRANDR;
                }

                إذا (بیرون_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, بیرون_info->crtc);
                } وإلا إذا (بیرون_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, بیرون_info->crtcs[0]);
                } وإلا {
                    crtc_info = عدم;
                }
                
                إذا (crtc_info) {
                    x = (crtc_info->عرض - داده->پنجره_عرض) / 2;
                    y = (crtc_info->ارتفاع - داده->پنجره_ارتفاع) / 3;
                    X11_XRRFreeOutputInfo(بیرون_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } وإلا {
                    X11_XRRFreeOutputInfo(بیرون_info);
                    اذهب NOXRANDR;
                }
            } وإلا {
                    FIRSTOUTPUTXRANDR:
                    إذا (screen_res->noutput > 0) {
                        XRROutputInfo *بیرون_info;

                        بیرون_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        إذا (!بیرون_info) {
                            اذهب FIRSTCRTCXRANDR;
                        }

                        إذا (بیرون_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, بیرون_info->crtc);
                        } وإلا إذا (بیرون_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, بیرون_info->crtcs[0]);
                        } وإلا {
                            crtc_info = عدم;
                        }

                        إذا (!crtc_info) {
                            X11_XRRFreeOutputInfo(بیرون_info);
                            اذهب FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->عرض - داده->پنجره_عرض) / 2;
                        y = (crtc_info->ارتفاع - داده->پنجره_ارتفاع) / 3;
                        X11_XRRFreeOutputInfo(بیرون_info);
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
                        x = (crtc_info->عرض - داده->پنجره_عرض) / 2;
                        y = (crtc_info->ارتفاع - داده->پنجره_ارتفاع) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } وإلا {
                        X11_XRRFreeScreenResources(screen_res);
                        اذهب NOXRANDR;
                    }
            }
        }
#پایان_اگر
        وإلا {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (Display_عرض(display, داده->screen) - داده->پنجره_عرض) / 2;
            y = (Display_ارتفاع(display, داده->screen) - داده->پنجره_ارتفاع) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMove_پنجره(display, داده->پنجره, x, y);
    داده->پنجره_x = x;
    داده->پنجره_y = y;

    sizehints = X11_XAlloc_اندازه_Hints();
    إذا (sizehints) {
        sizehints->flags = USPosition | USSize | PMax_اندازه | PMin_اندازه;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->عرض = داده->پنجره_عرض;
        sizehints->ارتفاع = داده->پنجره_ارتفاع;

        sizehints->min_عرض_2 = sizehints->max_عرض_2 = داده->پنجره_عرض;
        sizehints->min_ارتفاع_2 = sizehints->max_ارتفاع_2 = داده->پنجره_ارتفاع;

        X11_XSetWMNormalHints(display, داده->پنجره, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, داده->پنجره);

    داده->drawable = داده->پنجره;
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    إذا (SDL_X11_HAVE_XDBE && !داده->pixmap) {
        صحيح xdbe_major, xdbe_minor;
        إذا (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            داده->xdbe = true;
            داده->buf = X11_Xdbe_Allocate_پشت_میانگیر_Name(display, داده->پنجره, XdbeUndefined);
            داده->drawable = داده->buf;
        } وإلا {
            داده->xdbe = false;
        }
    }
#پایان_اگر

    X11_Toolkit_Init_پنجره_Pixmap(داده);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = داده->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = داده->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    إذا (!داده->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = داده->font_struct->fid;
    }
    داده->ctx = X11_XCreateGC(داده->display, داده->drawable, gcflags, &ctx_vals);
    إذا (داده->ctx == None) {
        أرجع SDL_مجموعه_Error("Couldn't create graphics context");
    }

    داده->close = false;
    داده->کلید_control_esc = داده->کلید_control_enter = عدم;
    إذا (!داده->pixmap) {
        داده->ev_scale = داده->ev_iscale = 1;
    } وإلا {
        داده->ev_scale = داده->scale;
        داده->ev_iscale = داده->iscale;
    }

#إذا SDL_GRAB
    إذا (داده->نما == SDL_TOOLKIT_پنجره_نما_X11_MENU || داده->نما== SDL_TOOLKIT_پنجره_نما_X11_TOOLTIP) {
        X11_XGrab_اشاره_گر(display, داده->پنجره, False, Button_Press_ماسک | Button_Release_ماسک | اشاره_گر_Motion_ماسک, Grab_نما_Async, Grab_نما_Async, None, None, Current_زمان);
        X11_XGrabKeyboard(display, داده->پنجره, False, Grab_نما_Async, Grab_نما_Async, Current_زمان);
    }
#پایان_اگر

    أرجع true;
}

ساكن فراغ X11_Toolkit_Draw_پنجره(SDL_Toolkit_پنجره_X11 *داده) {
    SDL_Rect rect;
    صحيح i;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && داده->xdbe && !داده->pixmap) {
        X11_XdbeBeginIdiom(داده->display);
    }
#پایان_اگر

    X11_XSetForeground(داده->display, داده->ctx, داده->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    إذا (داده->pixmap) {
        X11_XFillRectangle(داده->display, داده->drawable, داده->ctx, 0, 0, داده->pixmap_عرض, داده->pixmap_ارتفاع);
    } وإلا {
        X11_XFillRectangle(داده->display, داده->drawable, داده->ctx, 0, 0, داده->پنجره_عرض, داده->پنجره_ارتفاع);
    }

    لكل (i = 0; i < داده->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = داده->controls[i];
        إذا (control) {
            إذا (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && داده->xdbe && !داده->pixmap) {
        Xdbe_جابجا_Info جابجا_info;
        جابجا_info.جابجا_پنجره = داده->پنجره;
        جابجا_info.جابجا_action = XdbeUndefined;
        X11_Xdbe_جابجا_Buffers(داده->display, &جابجا_info, 1);
        X11_Xdbe_انتها_Idiom(داده->display);
    }
#پایان_اگر

    إذا (داده->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = داده->پنجره_عرض;
        rect.h = داده->پنجره_ارتفاع;
#اگر_تعریف_نشده NO_SHARED_حافظه
        إذا (داده->shm) {
            إذا (داده->shm_pixmap) {
                X11_XFlush(داده->display);
                X11_XSync(داده->display, false);
                scale_surface = SDL_CreateSurfaceFrom(داده->pixmap_عرض, داده->pixmap_ارتفاع, X11_GetPixelFormatFromVisualInfo(داده->display, &داده->vi), داده->shm_info.shmaddr, داده->shm_بایتها_در_هر_سطر);
                SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_خطی);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(داده->display, داده->drawable, داده->پنجره, داده->ctx, 0, 0, داده->پنجره_عرض, داده->پنجره_ارتفاع, 0, 0);
            } وإلا {
                X11_XShmGetImage(داده->display, داده->drawable, داده->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(داده->pixmap_عرض, داده->pixmap_ارتفاع, X11_GetPixelFormatFromVisualInfo(داده->display, &داده->vi), داده->image->داده, داده->image->بایتها_در_هر_سطر);
                SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_خطی);
                X11_XShmPutImage(داده->display, داده->پنجره, داده->ctx, داده->image, 0, 0, 0, 0, داده->پنجره_عرض, داده->پنجره_ارتفاع, False);
            }
        } وإلا
#پایان_اگر
        {
            XImage *image;

            image = X11_XGetImage(داده->display, داده->drawable, 0, 0 , داده->pixmap_عرض, داده->pixmap_ارتفاع, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(داده->pixmap_عرض, داده->pixmap_ارتفاع, X11_GetPixelFormatFromVisualInfo(داده->display, &داده->vi), image->داده, image->بایتها_در_هر_سطر);
            SDL_BlitSurfaceScaled(scale_surface, عدم, scale_surface, &rect, SDL_SCALEMODE_خطی);
            X11_XPutImage(داده->display, داده->پنجره, داده->ctx, image, 0, 0, 0, 0, داده->پنجره_عرض, داده->پنجره_ارتفاع);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(داده->display);
}

ساكن SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_Toolkit_پنجره_X11 *داده, صحيح x, صحيح y)
{
    صحيح i;

    لكل (i = 0; i < داده->controls_sz; i++) {
        SDL_Rect *rect = &داده->controls[i]->rect;
        إذا ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            أرجع داده->controls[i];
        }
    }

    أرجع عدم;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
ساكن Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_Toolkit_پنجره_X11 *داده = (SDL_Toolkit_پنجره_X11 *)arg;

    إذا (event->xany.display != داده->display) {
        أرجع False;
    }

    إذا (event->xany.پنجره == داده->پنجره) {
        أرجع True;
    }

    أرجع False;
}

فراغ X11_Toolkit_Process_پنجره_Events(SDL_Toolkit_پنجره_X11 *داده, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    إذا ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        أرجع;
    }

    داده->draw = false;
    داده->e = e;

    بدل (e->type) {
        حالة Expose:
            داده->draw = true;
            اكسر;
        حالة Client_پیام:
            إذا (e->xclient.پیام_type == داده->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.داده.l[0] == داده->wm_delete_پیام) {
                داده->close = true;
            }
            اكسر;
        حالة Focus_درون:
            داده->has_focus = true;
            اكسر;
        حالة Focus_بیرون:
            داده->has_focus = false;
            إذا (داده->fiddled_control) {
                داده->fiddled_control->selected = false;
            }
            داده->fiddled_control = عدم;
            لكل (داده->ev_i = 0; داده->ev_i < داده->controls_sz; داده->ev_i++) {
                داده->controls[داده->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_نرمال;
            }
            اكسر;
        حالة MotionNotify:
            إذا (داده->has_focus) {
                داده->قبلی_control = داده->fiddled_control;
                داده->fiddled_control = X11Toolkit_GetControlMouseIsOn(داده, SDL_lroundf((e->xbutton.x/ داده->ev_scale)* داده->ev_iscale), SDL_lroundf((e->xbutton.y/ داده->ev_scale)* داده->ev_iscale));
                إذا (داده->قبلی_control) {
                    داده->قبلی_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نرمال;
                    إذا (داده->قبلی_control->func_on_state_change) {
                        داده->قبلی_control->func_on_state_change(داده->قبلی_control);
                    }
                    داده->draw = true;
                }
                إذا (داده->fiddled_control) {
                    إذا (داده->fiddled_control->dynamic) {
                        داده->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        إذا (داده->fiddled_control->func_on_state_change) {
                            داده->fiddled_control->func_on_state_change(داده->fiddled_control);
                        }
                        داده->draw = true;
                    } وإلا {
                        داده->fiddled_control = عدم;
                    }
                }
            }
            اكسر;
        حالة ButtonPress:
            داده->قبلی_control = داده->fiddled_control;
            إذا (داده->قبلی_control) {
                داده->قبلی_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نرمال;
                إذا (داده->قبلی_control->func_on_state_change) {
                    داده->قبلی_control->func_on_state_change(داده->قبلی_control);
                }
                داده->draw = true;
            }
            إذا (e->xbutton.button == Button1) {
                داده->fiddled_control = X11Toolkit_GetControlMouseIsOn(داده, SDL_lroundf((e->xbutton.x/ داده->ev_scale)* داده->ev_iscale), SDL_lroundf((e->xbutton.y/ داده->ev_scale)* داده->ev_iscale));
                إذا (داده->fiddled_control) {
                    داده->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    إذا (داده->fiddled_control->func_on_state_change) {
                        داده->fiddled_control->func_on_state_change(داده->fiddled_control);
                    }
                    داده->draw = true;
                }
            }
            اكسر;
        حالة ButtonRelease:
            إذا (داده->نما == SDL_TOOLKIT_پنجره_نما_X11_MENU || داده->نما== SDL_TOOLKIT_پنجره_نما_X11_TOOLTIP) {
                صحيح cx;
                صحيح cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                إذا (cy < 0 || cx < 0) {
                    داده->close = true;
                }

                إذا (cy > داده->پنجره_ارتفاع || cx > داده->پنجره_عرض) {
                    داده->close = true;
                }
            }

            إذا ((e->xbutton.button == Button1) && (داده->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(داده, SDL_lroundf((e->xbutton.x/ داده->ev_scale)* داده->ev_iscale), SDL_lroundf((e->xbutton.y/ داده->ev_scale)* داده->ev_iscale));
                إذا (داده->fiddled_control == control) {
                    داده->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    إذا (داده->fiddled_control->func_on_state_change) {
                        داده->fiddled_control->func_on_state_change(داده->fiddled_control);
                    }
                    داده->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نرمال;
                    داده->draw = true;
                }
            }
            اكسر;
        حالة کلید_Press:
            داده->آخرین_کلید_pressed = X11_XLookupKeysym(&e->xkey, 0);

            إذا (داده->آخرین_کلید_pressed == XK_Escape) {
                لكل (داده->ev_i = 0; داده->ev_i < داده->controls_sz; داده->ev_i++) {
                    إذا(داده->controls[داده->ev_i]->is_default_esc) {
                        داده->controls[داده->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        داده->draw = true;
                        داده->کلید_control_esc = داده->controls[داده->ev_i];
                    }
                }
            } وإلا إذا ((داده->آخرین_کلید_pressed == XK_Return) || (داده->آخرین_کلید_pressed == XK_KP_Enter)) {
                لكل (داده->ev_i = 0; داده->ev_i < داده->controls_sz; داده->ev_i++) {
                    إذا(داده->controls[داده->ev_i]->selected) {
                        داده->controls[داده->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        داده->draw = true;
                        داده->کلید_control_enter = داده->controls[داده->ev_i];
                    }
                }
            }
            اكسر;
        حالة کلید_Release:
        {
            کلید_Sym کلید = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            إذا (کلید != داده->آخرین_کلید_pressed) {
                اكسر;
            }

            إذا (کلید == XK_Escape) {
                إذا (داده->کلید_control_esc) {
                    إذا (داده->کلید_control_esc->func_on_state_change) {
                        داده->کلید_control_esc->func_on_state_change(داده->کلید_control_esc);
                    }
                }
            } وإلا إذا ((کلید == XK_Return) || (کلید == XK_KP_Enter)) {
                إذا (داده->کلید_control_enter) {
                    إذا (داده->کلید_control_enter->func_on_state_change) {
                        داده->کلید_control_enter->func_on_state_change(داده->کلید_control_enter);
                    }
                }
            } وإلا إذا (کلید == XK_Tab || کلید == XK_چپ || کلید == XK_راست) {
                إذا (داده->focused_control) {
                    داده->focused_control->selected = false;
                }
                داده->draw = true;
                لكل (داده->ev_i = 0; داده->ev_i < داده->dyn_controls_sz; داده->ev_i++) {
                    إذا (داده->dyn_controls[داده->ev_i] == داده->focused_control) {
                        صحيح بعدی_شاخص;

                        إذا (کلید == XK_چپ) {
                            بعدی_شاخص = داده->ev_i - 1;
                        } وإلا {
                            بعدی_شاخص = داده->ev_i + 1;
                        }
                        إذا ((بعدی_شاخص >= داده->dyn_controls_sz) || (بعدی_شاخص < 0)) {
                            إذا (کلید == XK_راست || کلید == XK_چپ) {
                                بعدی_شاخص = داده->ev_i;
                            } وإلا {
                                بعدی_شاخص = 0;
                            }
                        }
                        داده->focused_control = داده->dyn_controls[بعدی_شاخص];
                        داده->focused_control->selected = true;
                        اكسر;
                    }
                }
            }
            اكسر;
        }
    }

    إذا (داده->draw) {
        X11_Toolkit_Draw_پنجره(داده);
    }
}

فراغ X11_Toolkit_Do_پنجره_Event_Loop(SDL_Toolkit_پنجره_X11 *داده) {
   طالما (!داده->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(داده->display, &e);
        إذا (داده->xsettings) {
            xsettings_client_process_event(داده->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(داده->display, &e, X11Toolkit_EventTest, (XPointer)داده);
        X11_Toolkit_Process_پنجره_Events(داده, &e);
    }
}


فراغ X11_Toolkit_Resize_پنجره(SDL_Toolkit_پنجره_X11 *داده, صحيح w, صحيح h) {
    إذا (!داده->pixmap) {
        داده->پنجره_عرض = w;
        داده->پنجره_ارتفاع = h;
    } وإلا {
        داده->پنجره_عرض = SDL_lroundf((w/داده->iscale) * داده->scale);
        داده->پنجره_ارتفاع = SDL_lroundf((h/داده->iscale) * داده->scale);
        داده->pixmap_عرض = w;
        داده->pixmap_ارتفاع = h;
        X11_XFreePixmap(داده->display, داده->drawable);
        X11_Toolkit_Init_پنجره_Pixmap(داده);
    }

    X11_XResize_پنجره(داده->display, داده->پنجره, داده->پنجره_عرض, داده->پنجره_ارتفاع);
}

ساكن فراغ X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->پنجره->display, icon_control->icon_char_font);
    SDL_free(control);
}

ساكن فراغ X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->پنجره->iscale;
    control->rect.h -= 2 * control->پنجره->iscale;
    X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx, control->rect.x + (2 * control->پنجره->iscale), control->rect.y + (2* control->پنجره->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    بدل (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        حالة SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx, control->rect.x+(1* control->پنجره->iscale), control->rect.y+(1* control->پنجره->iscale), control->rect.w-(2* control->پنجره->iscale), control->rect.h-(2* control->پنجره->iscale), 0, 360 * 64);
                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, icon_control->xcolor_white.pixel);
                اكسر;
        حالة SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx, control->rect.x+(1* control->پنجره->iscale), control->rect.y+(1* control->پنجره->iscale), control->rect.w-(2* control->پنجره->iscale), control->rect.h-(2* control->پنجره->iscale), 0, 360 * 64);
                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, icon_control->xcolor_black.pixel);
                اكسر;
        حالة SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx, control->rect.x+(1* control->پنجره->iscale), control->rect.y+(1* control->پنجره->iscale), control->rect.w-(2* control->پنجره->iscale), control->rect.h-(2* control->پنجره->iscale), 0, 360 * 64);
                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, icon_control->xcolor_white.pixel);
                اكسر;
    }
    X11_XSetFont(control->پنجره->display, control->پنجره->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    إذا (!control->پنجره->utf8) {
        X11_XSetFont(control->پنجره->display, control->پنجره->ctx, control->پنجره->font_struct->fid);
    }

    control->rect.w += 2 * control->پنجره->iscale;
    control->rect.h += 2 * control->پنجره->iscale;
}

ساكن فراغ X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *پایه_control) {
    SDL_ToolkitIconControlX11 *control;
    صحيح icon_char_w;
    صحيح icon_wh;

    control = (SDL_ToolkitIconControlX11 *)پایه_control;
    X11_Toolkit_Get_متن_عرض_ارتفاع_For_Font(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, عدم);
    پایه_control->rect.w = icon_char_w;
    پایه_control->rect.h = control->icon_char_h;
    icon_wh = SDL_max(icon_char_w, control->icon_char_h) + SDL_TOOLKIT_X11_ELEMENT_PADDING * 2 * پایه_control->پنجره->iscale;
    پایه_control->rect.w = icon_wh;
    پایه_control->rect.h = icon_wh;
    پایه_control->rect.y = 0;
    پایه_control->rect.x = 0;
    control->icon_char_y = control->icon_char_a + (پایه_control->rect.h - control->icon_char_h)/2;
    control->icon_char_x = (پایه_control->rect.w - icon_char_w)/2;
    پایه_control->rect.w += 2 * پایه_control->پنجره->iscale;
    پایه_control->rect.h += 2 * پایه_control->پنجره->iscale;
}

ساكن فراغ X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *پایه_control) {
    SDL_ToolkitIconControlX11 *control;
    حرف *font;

    control = (SDL_ToolkitIconControlX11 *)پایه_control;
    X11_XFreeFont(پایه_control->پنجره->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_اندازه * پایه_control->پنجره->iscale);
    control->icon_char_font = X11_XLoadQueryFont(پایه_control->پنجره->display, font);
    SDL_free(font);
    إذا (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_اندازه * پایه_control->پنجره->iscale);
        control->icon_char_font = X11_XLoadQueryFont(پایه_control->پنجره->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_پنجره_X11 *پنجره, SDL_پیام_Box_Flags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *پایه_control;
    حرف *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(حجم(SDL_ToolkitIconControlX11));
    پایه_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_مجموعه_Error("Unable to allocate icon control structure");
        أرجع عدم;
    }

    /* Fill out struct */
    پایه_control->پنجره = پنجره;
    پایه_control->func_draw = X11Toolkit_DrawIconControl;
    پایه_control->func_free = X11Toolkit_DestroyIconControl;
    پایه_control->func_on_state_change = عدم;
    پایه_control->func_calc_اندازه = X11Toolkit_CalculateIconControl;
    پایه_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    پایه_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نرمال;
    پایه_control->selected = false;
    پایه_control->dynamic = false;
    پایه_control->is_default_enter = false;
    پایه_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_اندازه * پنجره->iscale);
    control->icon_char_font = X11_XLoadQueryFont(پنجره->display, font);
    SDL_free(font);
    إذا (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_اندازه * پنجره->iscale);
        control->icon_char_font = X11_XLoadQueryFont(پنجره->display, font);
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
        X11_XAllocColor(پنجره->display, پنجره->cmap, &control->xcolor_white);
        X11_XAllocColor(پنجره->display, پنجره->cmap, &control->xcolor_red);
        X11_XAllocColor(پنجره->display, پنجره->cmap, &control->xcolor_red_darker);
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
        X11_XAllocColor(پنجره->display, پنجره->cmap, &control->xcolor_black);
        X11_XAllocColor(پنجره->display, پنجره->cmap, &control->xcolor_yellow);
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
        X11_XAllocColor(پنجره->display, پنجره->cmap, &control->xcolor_white);
        X11_XAllocColor(پنجره->display, پنجره->cmap, &control->xcolor_blue);
        اكسر;
    افتراضي:
        X11_XFreeFont(پنجره->display, control->icon_char_font);
        SDL_free(control);
        أرجع عدم;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    إذا (پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } وإلا إذا (پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.red = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    إذا (پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } وإلا إذا (پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.green = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    إذا (پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } وإلا إذا (پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } وإلا {
        control->xcolor_bg_shadow.blue = SDL_clamp(پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(پنجره->display, پنجره->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(پایه_control);

    X11_Toolkit_جمع_کن_Control_مقصد_پنجره(پنجره, پایه_control);
    أرجع پایه_control;
}

bool X11_Toolkit_Notify_Control_از_اندازه_Change(SDL_ToolkitControlX11 *control) {
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
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->پنجره->iscale + button_control->متن_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->پنجره->iscale + button_control->متن_rect.h;
    }
    button_control->متن_rect.x = (control->rect.w - button_control->متن_rect.w)/2;
    button_control->متن_rect.y = (control->rect.h - button_control->متن_rect.h)/2;
}


ساكن فراغ X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    /* Draw bevel */
    إذا (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
            X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor_bevel_d.pixel);
            X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

            X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor_bevel_l2.pixel);
            X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - (1* control->پنجره->iscale), control->rect.h - (1* control->پنجره->iscale));

            X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor_bevel_l1.pixel);
            X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x + 1 * control->پنجره->iscale, control->rect.y + 1 * control->پنجره->iscale,
                                   control->rect.w - 3 * control->پنجره->iscale, control->rect.h - 2 * control->پنجره->iscale);

            X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
            X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                               control->rect.x + 1 * control->پنجره->iscale, control->rect.y + 1 * control->پنجره->iscale,
                               control->rect.w - 3 * control->پنجره->iscale, control->rect.h - 3 * control->پنجره->iscale);

            X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor_pressed.pixel);
            X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                               control->rect.x + 2 * control->پنجره->iscale, control->rect.y + 2 * control->پنجره->iscale,
                               control->rect.w - 4 * control->پنجره->iscale, control->rect.h - 4 * control->پنجره->iscale);
        } وإلا {
            إذا (control->selected) {
                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x + 1 * control->پنجره->iscale, control->rect.y + 1 * control->پنجره->iscale,
                                   control->rect.w - 3 * control->پنجره->iscale, control->rect.h - 3 * control->پنجره->iscale);

                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x + 2 * control->پنجره->iscale, control->rect.y + 2 * control->پنجره->iscale,
                                   control->rect.w - 4 * control->پنجره->iscale, control->rect.h - 4 * control->پنجره->iscale);

                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x + 2 * control->پنجره->iscale, control->rect.y + 2 * control->پنجره->iscale,
                                   control->rect.w - 5 * control->پنجره->iscale, control->rect.h - 5 * control->پنجره->iscale);

                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x + 3 * control->پنجره->iscale, control->rect.y + 3 * control->پنجره->iscale,
                                   control->rect.w - 6 * control->پنجره->iscale, control->rect.h - 6 * control->پنجره->iscale);
            } وإلا {
                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - 1 * control->پنجره->iscale, control->rect.h - 1 * control->پنجره->iscale);

                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x + 1 * control->پنجره->iscale, control->rect.y + 1 * control->پنجره->iscale,
                                   control->rect.w - 2 * control->پنجره->iscale, control->rect.h - 2 * control->پنجره->iscale);

                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x + 1 * control->پنجره->iscale, control->rect.y + 1 * control->پنجره->iscale,
                                   control->rect.w - 3 * control->پنجره->iscale, control->rect.h - 3 * control->پنجره->iscale);

                X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->پنجره->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->پنجره->display, control->پنجره->drawable, control->پنجره->ctx,
                                   control->rect.x + 2 * control->پنجره->iscale, control->rect.y + 2 * control->پنجره->iscale,
                                   control->rect.w - 4 * control->پنجره->iscale, control->rect.h - 4 * control->پنجره->iscale);
            }
        }

    X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    X11_Toolkit_Draw_متن_Elements(control->پنجره, button_control->متن, control->rect.x + button_control->متن_rect.x, control->rect.y + button_control->متن_rect.y);
}

ساكن فراغ X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    إذا (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_داده);
    }
}

ساكن فراغ X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_Toolkit_Free_متن_Elements(button_control->متن);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_پنجره_X11 *پنجره, ثابت SDL_پیام_Box_Button_داده *داده) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *پایه_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(حجم(SDL_ToolkitButtonControlX11));
    پایه_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_مجموعه_Error("Unable to allocate button control structure");
        أرجع عدم;
    }
    پایه_control->پنجره = پنجره;
    پایه_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نرمال;
    پایه_control->func_calc_اندازه = X11Toolkit_CalculateButtonControl;
    پایه_control->func_draw = X11Toolkit_DrawButtonControl;
    پایه_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    پایه_control->func_free = X11Toolkit_DestroyButtonControl;
    پایه_control->func_on_scale_change = عدم;
    پایه_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نرمال;
    پایه_control->selected = false;
    پایه_control->dynamic = true;
    پایه_control->is_default_enter = false;
    پایه_control->is_default_esc = false;
    إذا (داده->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        پایه_control->is_default_esc = true;
    }
    إذا (داده->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        پایه_control->is_default_enter = true;
        پایه_control->selected = true;
    }
    control->cb = عدم;
    control->داده = داده;
#اگر_تعریف_شده HAVE_FRIBIDI_H
    control->متن = X11_Toolkit_Make_متن_Elements(پایه_control->پنجره, (حرف *)control->داده->متن, SDL_strlen(control->داده->متن), عدم);
#وإلا 
    control->متن = X11_Toolkit_Make_متن_Elements(پایه_control->پنجره, (حرف *)control->داده->متن, SDL_strlen(control->داده->متن));
#پایان_اگر
    X11_Toolkit_Shape_متن_Elements(پایه_control->پنجره, control->متن);
    
    پایه_control->do_اندازه = true;
    X11Toolkit_CalculateButtonControl(پایه_control);
    پایه_control->do_اندازه = false;

    X11_Toolkit_جمع_کن_Control_مقصد_پنجره(پنجره, پایه_control);
    أرجع پایه_control;
}

فراغ X11_Toolkit_ثبات_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, فراغ *داده, فراغ (*cb)(بنية SDL_ToolkitControlX11 *, فراغ *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_داده = داده;
    button_control->cb = cb;
}

ثابت SDL_پیام_Box_Button_داده *X11_Toolkit_Get_Button_Control_داده(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    أرجع button_control->داده;
}

فراغ X11_Toolkit_Destroy_پنجره(SDL_Toolkit_پنجره_X11 *داده) {
    صحيح i;

    إذا (!داده) {
        أرجع;
    }

#إذا SDL_GRAB
    إذا (داده->نما == SDL_TOOLKIT_پنجره_نما_X11_MENU || داده->نما== SDL_TOOLKIT_پنجره_نما_X11_TOOLTIP) {
        X11_XUngrab_اشاره_گر(داده->display, Current_زمان);
        X11_XUngrabKeyboard(داده->display, Current_زمان);
    }
#پایان_اگر

    لكل (i = 0; i < داده->controls_sz; i++) {
        إذا (داده->controls[i]->func_free) {
            داده->controls[i]->func_free(داده->controls[i]);
        }
    }
    SDL_free(داده->controls);
    SDL_free(داده->dyn_controls);

    إذا (داده->popup_windows) {
        SDL_ListClear(&داده->popup_windows);
    }

    إذا (داده->pixmap) {
        X11_XFreePixmap(داده->display, داده->drawable);
    }

#اگر_تعریف_نشده NO_SHARED_حافظه
    إذا (داده->pixmap && داده->shm) {
        X11_XShmDetach(داده->display, &داده->shm_info);
        إذا (!داده->shm_pixmap) {
            XDestroyImage(داده->image);
        }
        shmdt(داده->shm_info.shmaddr);
    }
#پایان_اگر

#اگر_تعریف_شده X_HAVE_UTF8_STRING
    إذا (داده->font_مجموعه) {
        X11_XFree_Font_مجموعه(داده->display, داده->font_مجموعه);
        داده->font_مجموعه = عدم;
    }
#پایان_اگر

    إذا (داده->font_struct) {
        X11_XFreeFont(داده->display, داده->font_struct);
        داده->font_struct = عدم;
    }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XDBE
    إذا (SDL_X11_HAVE_XDBE && داده->xdbe && !داده->pixmap) {
        X11_Xdbe_Deallocate_پشت_میانگیر_Name(داده->display, داده->buf);
    }
#پایان_اگر

    إذا (داده->xsettings) {
        xsettings_client_destroy(داده->xsettings);
    }

    X11_XFreeGC(داده->display, داده->ctx);

    إذا (داده->display) {
        إذا (داده->پنجره != None) {
            X11_XWithdraw_پنجره(داده->display, داده->پنجره, داده->screen);
            X11_XDestroy_پنجره(داده->display, داده->پنجره);
            داده->پنجره = None;
        }

        إذا (داده->display_close) {
            X11_XCloseDisplay(داده->display);
        }
        داده->display = عدم;
    }

#إذا SDL_مجموعه_LOCALE
    إذا (داده->origlocale && (داده->نما == SDL_TOOLKIT_پنجره_نما_X11_DIALOG)) {
        (فراغ)setlocale(LC_ALL, داده->origlocale);
        SDL_free(داده->origlocale);
    }
#پایان_اگر

#اگر_تعریف_شده HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(داده->fribidi);
#پایان_اگر

#اگر_تعریف_شده HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(داده->th);
#پایان_اگر

    SDL_free(داده);
}

ساكن صحيح X11_Toolkit_شمار_سطرها_از_متن(ثابت حرف *متن)
{
    صحيح نتیجه = 0;
    طالما (متن && *متن) {
        ثابت حرف *lf = SDL_strchr(متن, '\n');
        نتیجه++; // even without an endline, this counts as a line.
        متن = lf ? lf + 1 : عدم;
    }
    أرجع نتیجه;
}

ساكن فراغ X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحيح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->پنجره->display, control->پنجره->ctx, control->پنجره->xcolor[SDL_MESSAGEBOX_COLOR_متن].pixel);
    لكل (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Draw_متن_Elements(control->پنجره, label_control->سطرها[i].متن, control->rect.x + label_control->سطرها[i].rect.x, control->rect.y + label_control->سطرها[i].rect.y);
    }
}

ساكن فراغ X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحيح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    لكل (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Free_متن_Elements(label_control->سطرها[i].متن);
    }
    SDL_free(label_control->سطرها);
    SDL_free(label_control);
}

ساكن فراغ X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *پایه_control) {
    SDL_ToolkitLabelControlX11 *control;
    صحيح i;

    control = (SDL_ToolkitLabelControlX11 *)پایه_control;
    
    إذا (پایه_control->do_اندازه) {
        پایه_control->rect.w = 0;
        پایه_control->rect.h = 0;
    }
    
    لكل (i = 0; i < control->sz; i++) {
        صحيح font_h;
        
        font_h = X11_Toolkit_Get_متن_Elements_Rect(control->سطرها[i].متن, &control->سطرها[i].rect);
        
        إذا (پایه_control->do_اندازه) {
            پایه_control->rect.w = SDL_max(پایه_control->rect.w, control->سطرها[i].rect.w);
        }
        
        إذا (i > 0) {
            control->سطرها[i].rect.y = font_h + control->سطرها[i - 1].rect.y;
        } وإلا {
            control->سطرها[i].rect.y = 0;
        }
    }

#اگر_تعریف_شده HAVE_FRIBIDI_H
    إذا (پایه_control->پنجره->fribidi) {
        FriBidiParType اولی_ndn_dir;
        صحيح آخرین_ndn;
    
        اولی_ndn_dir = FRIBIDI_PAR_LTR;
        لكل (i = 0; i < control->sz; i++) {
            إذا (control->سطرها[i].par != FRIBIDI_PAR_ON) {
                اولی_ndn_dir = control->سطرها[i].par;
            }
        }

        آخرین_ndn = -1;
        لكل (i = 0; i < control->sz; i++) {
            بدل (control->سطرها[i].par) {
                حالة FRIBIDI_PAR_LTR:
                    control->سطرها[i].rect.x = 0;
                    آخرین_ndn = i;
                    اكسر;
                حالة FRIBIDI_PAR_RTL:
                    control->سطرها[i].rect.x = پایه_control->rect.w - control->سطرها[i].rect.w;
                    آخرین_ndn = i;
                    اكسر;
                افتراضي:
                    إذا (آخرین_ndn != -1) {
                        إذا (control->سطرها[آخرین_ndn].par == FRIBIDI_PAR_RTL) {
                            control->سطرها[i].rect.x = پایه_control->rect.w - control->سطرها[i].rect.w;
                        } وإلا {
                            control->سطرها[i].rect.x = 0;
                        }
                    } وإلا {
                        إذا (اولی_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->سطرها[i].rect.x = پایه_control->rect.w - control->سطرها[i].rect.w;
                        } وإلا {
                            control->سطرها[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#پایان_اگر
    
    إذا (پایه_control->do_اندازه && control->sz) {
        پایه_control->rect.h = control->سطرها[control->sz - 1].rect.y + control->سطرها[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_پنجره_X11 *پنجره, حرف *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *پایه_control;
    صحيح i;
    
    إذا (!utf8) {
        أرجع عدم;
    }
 
    إذا (!SDL_strcmp(utf8, "")) {
        أرجع عدم;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(حجم(SDL_ToolkitLabelControlX11));
    پایه_control = (SDL_ToolkitControlX11 *)control;
    إذا (!control) {
        SDL_مجموعه_Error("Unable to allocate label control structure");
        أرجع عدم;
    }
    پایه_control->پنجره = پنجره;
    پایه_control->func_draw = X11Toolkit_DrawLabelControl;
    پایه_control->func_on_state_change = عدم;
    پایه_control->func_calc_اندازه = X11Toolkit_CalculateLabelControl;
    پایه_control->func_free  = X11Toolkit_DestroyLabelControl;
    پایه_control->func_on_scale_change = عدم;
    پایه_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_نرمال;
    پایه_control->selected = false;
    پایه_control->dynamic = false;
    پایه_control->rect.w = 0;
    پایه_control->rect.h = 0;
    پایه_control->is_default_enter = false;
    پایه_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_شمار_سطرها_از_متن(utf8);
    control->سطرها = SDL_calloc(control->sz, حجم(SDL_Toolkit_Label_Control_سطر_X11));
    لكل (i = 0; i < control->sz; i++) {
        ثابت حرف *lf = SDL_strchr(utf8, '\n');
        ثابت صحيح درازی = lf ? (lf - utf8) : SDL_strlen(utf8);
        صحيح sz;
        
        sz = درازی;
        إذا (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#اگر_تعریف_شده HAVE_FRIBIDI_H
        control->سطرها[i].متن = X11_Toolkit_Make_متن_Elements(پایه_control->پنجره, (حرف *)utf8, sz, &control->سطرها[i].par);
#وإلا 
        control->سطرها[i].متن = X11_Toolkit_Make_متن_Elements(پایه_control->پنجره, (حرف *)utf8, sz);
#پایان_اگر
        X11_Toolkit_Shape_متن_Elements(پایه_control->پنجره, control->سطرها[i].متن);

        utf8 += درازی + 1;
        إذا (!lf) {
            اكسر;
        }
    }

    پایه_control->do_اندازه = true;
    X11Toolkit_CalculateLabelControl(پایه_control);
    پایه_control->do_اندازه = false;
    X11_Toolkit_جمع_کن_Control_مقصد_پنجره(پنجره, پایه_control);

    أرجع پایه_control;
}

صحيح X11_Toolkit_Get_Label_Control_اولی_سطر_ارتفاع(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    أرجع label_control->سطرها[0].rect.h;
}

فراغ X11_Toolkit_Signal_پنجره_Close(SDL_Toolkit_پنجره_X11 *داده) {
    داده->close = true;
}

#پایان_اگر // SDL_VIDEO_DRIVER_X11
