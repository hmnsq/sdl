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

#ifdef SDL_VIDEO_DRIVER_X11

#شامل "../../SDL_list.h"
#شامل "SDL_x11video.h"
#ifdef SDL_USE_LIBDBUS
#شامل "../../core/linux/SDL_system_theme.h"
#endif
#ifdef HAVE_FRIBIDI_H
#شامل "../../core/unix/SDL_fribidi.h"
#endif
#شامل "SDL_x11dyn.h"
#شامل "SDL_x11toolkit.h"
#شامل "SDL_x11settings.h"
#شامل "SDL_x11modes.h"
#شامل "xsettings-client.h"
#شامل <X11/keysym.h>
#شامل <locale.h>

#define SDL_SET_LOCALE 1
#define SDL_GRAB 1

تعریفنوع شمارش SDL_ToolkitTextTypeX11
{
    SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC,
    SDL_TOOLKIT_TEXT_TYPE_X11_THAI
} SDL_ToolkitTextTypeX11;

#ifdef HAVE_LIBTHAI_H
تعریفنوع ساختار SDL_ToolkitThaiOverlayX11
{
    bool بالاترین;
    نویسه *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#endif

تعریفنوع ساختار SDL_ToolkitTextElementX11
{
    SDL_ToolkitTextTypeX11 type;
    نویسه *str;
    size_t sz;
    SDL_Rect rect;
    صحیح font_h;
    تهی (*str_free)(تهی *);
#ifdef HAVE_LIBTHAI_H
    SDL_List_گره *thai_overlays;
#endif
} SDL_ToolkitTextElementX11;

تعریفنوع ساختار SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Icon type */
    SDL_MessageBoxFlags flags;
    نویسه icon_char;

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

تعریفنوع ساختار SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Data */
    ثابت SDL_MessageBoxButtonData *data;

    /* Text */
    SDL_List_گره *text;
    SDL_Rect text_rect;
    
    /* Callback */
    تهی *cb_data;
    تهی (*cb)(ساختار SDL_ToolkitControlX11 *, تهی *);
} SDL_ToolkitButtonControlX11;

تعریفنوع ساختار SDL_Toolkit_Label_Control_سطر_X11
{
    SDL_List_گره *text;
    SDL_Rect rect;
#ifdef HAVE_FRIBIDI_H
    FriBidiParType par;
#endif
} SDL_Toolkit_Label_Control_سطر_X11;

تعریفنوع ساختار SDL_ToolkitLabelControlX11
{
    SDL_ToolkitControlX11 parent;

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

تعریفنوع ساختار SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_گره *menu_اقلام;
} SDL_ToolkitMenuBarControlX11;

تعریفنوع ساختار SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_گره *menu_اقلام;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
ایستا ثابت نویسه *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#define G_ICONFONT_SIZE 22

/* General UI font */
ایستا ثابت نویسه g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
ایستا ثابت نویسه g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

ایستا ثابت نویسه *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    پوچ
};
#define G_TOOLKITFONT_SIZE 140

ایستا ثابت SDL_MessageBoxColor g_default_colors[SDL_MESSAGEBOX_COLOR_شمار] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ifdef SDL_USE_LIBDBUS
ایستا ثابت SDL_MessageBoxColor g_default_colors_dark[SDL_MESSAGEBOX_COLOR_شمار] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#اگر 0
ایستا ثابت SDL_MessageBoxColor g_default_colors_dark_بالا_contrast[SDL_MESSAGEBOX_COLOR_شمار] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

ایستا ثابت SDL_MessageBoxColor g_default_colors_light_بالا_contrast[SDL_MESSAGEBOX_COLOR_شمار] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#endif

#endif

ایستا صحیح g_shm_error;
ایستا صحیح (*g_old_error_handler)(Display *, XErrorEvent *) = پوچ;

ایستا صحیح X11Toolkit_SharedMemoryErrorHandler(Display *d, XErrorEvent *e)
{
    اگر (e->error_code == BadAccess || e->error_code == BadRequest) {
        g_shm_error = True;
        بازگشت 0;
    }
    بازگشت g_old_error_handler(d, e);
}

ایستا تهی X11Toolkit_InitWindowPixmap(SDL_ToolkitWindowX11 *data) {
    اگر (data->pixmap) {
#ifndef NO_SHARED_MEMORY
        اگر (!data->shm_pixmap) {
            data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
        }
#وگرنه
        data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
#endif
#ifndef NO_SHARED_MEMORY
        اگر (data->shm) {
            data->image = X11_XShmCreateImage(data->display, data->visual, data->depth, ZPixmap, پوچ, &data->shm_info, data->pixmap_width, data->pixmap_height);
            اگر (data->image) {
                data->shm_bytes_per_سطر = data->image->bytes_per_سطر;

                data->shm_info.shmid = shmget(IPC_PRIVATE, data->image->bytes_per_سطر * data->image->height, IPC_CREAT | 0777);
                اگر (data->shm_info.shmid < 0) {
                    XDestroyImage(data->image);
                    data->image = پوچ;
                    data->shm = false;
                    بازگشت;
                }

                data->shm_info.readOnly = False;
                data->shm_info.shmaddr = data->image->data = (نویسه *)shmat(data->shm_info.shmid, پوچ, 0);
                اگر (((signed نویسه *)data->shm_info.shmaddr) == (signed نویسه *)-1) {
                    XDestroyImage(data->image);
                    data->shm = false;
                    data->image = پوچ;
                    بازگشت;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11Toolkit_SharedMemoryErrorHandler);
                X11_XShmAttach(data->display, &data->shm_info);
                X11_XSync(data->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                اگر (g_shm_error) {
                    XDestroyImage(data->image);
                    shmdt(data->shm_info.shmaddr);
                    shmctl(data->shm_info.shmid, IPC_RMID, پوچ);
                    data->image = پوچ;
                    data->shm = false;
                    بازگشت;
                }

                اگر (data->shm_pixmap) {
                    data->drawable = X11_XShmCreatePixmap(data->display, data->window, data->shm_info.shmaddr, &data->shm_info, data->pixmap_width, data->pixmap_height, data->depth);
                    اگر (data->drawable == None) {
                        data->shm_pixmap = False;
                    } وگرنه {
                        XDestroyImage(data->image);
                        data->image = پوچ;
                    }
                }

                shmctl(data->shm_info.shmid, IPC_RMID, پوچ);
            } وگرنه {
                data->shm = false;
            }
        }
#endif
    }
}

ایستا تهی X11Toolkit_InitWindowFonts(SDL_ToolkitWindowX11 *window)
{    
    window->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    window->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#ifdef X_HAVE_UTF8_STRING
    window->utf8 = true;
    window->font_set = پوچ;
    اگر (SDL_X11_HAVE_UTF8) {
        نویسه **missing = پوچ;
        صحیح رقم_missing = 0;
        صحیح i_font;
        window->font_struct = پوچ;
        برای (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            نویسه *font;

            اگر (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_load_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_SIZE * window->iscale);
                window->font_set = X11_XCreateFontSet(window->display, font, &missing, &رقم_missing, پوچ);
                SDL_free(font);

                اگر (!window->font_set) {
                    اگر (window->scale != 0 && window->iscale > 0) {
                        window->iscale = (صحیح)SDL_ceilf(window->scale);
                        window->scale = 0;
                    } وگرنه {
                        window->iscale--;
                    }
                    برو try_load_font;
                }
            } وگرنه {
                window->font_set = X11_XCreateFontSet(window->display, g_ToolkitFont[i_font], &missing, &رقم_missing, پوچ);
            }

            اگر (missing) {
                X11_XFreeStringList(missing);
            }

            اگر (window->font_set) {
                بشکن;
            }
        }

        اگر (!window->font_set) {
            برو load_font_traditional;
        } وگرنه {
            XFontStruct **font_structs;
            نویسه **font_names;
            صحیح font_sz;
            صحیح i;
            
#ifdef HAVE_FRIBIDI_H
            window->do_shaping = !X11_XContextDependentDrawing(window->font_set);
#endif
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFontsOfFontSet(window->font_set, &font_structs, &font_names);
            برای (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                اگر (SDL_strstr(font_names[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } وگرنه اگر (SDL_strstr(font_names[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } وگرنه اگر (SDL_strstr(font_names[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } وگرنه اگر (SDL_strstr(font_names[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } وگرنه اگر (SDL_strstr(font_names[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                اگر (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(window->display, font_names[i]);
                    اگر (font_struct) {
                        اگر (font_struct->per_char) {
                            صحیح glyphs_sz;
                            صحیح j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            برای (j = 0; j < glyphs_sz; j++) {
                                اگر (font_struct->per_char[j].lbearing < 0) {
                                    window->thai_font = SDL_TOOLKIT_THAI_FONT_X11_OFFSET;
                                }
                            }
                        }
                        X11_XFreeFont(window->display, font_struct);
                    }
                }
                
                window->thai_encoding = thai_encoding;
            } 
        }
    } وگرنه
#endif
    {
        نویسه *font;

        load_font_traditional:
        window->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        window->font_struct = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        اگر (!window->font_struct) {
            اگر (window->iscale > 0) {
                اگر (window->scale != 0) {
                    window->iscale = (صحیح)SDL_ceilf(window->scale);
                    window->scale = 0;
                } وگرنه {
                    window->iscale--;
                }
                برو load_font_traditional;
            } وگرنه {
                window->font_struct = X11_XLoadQueryFont(window->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

ایستا تهی X11Toolkit_SettingsNotify(ثابت نویسه *name, XSettingsAction action, XSettingsSetting *setting, تهی *data)
{
    SDL_ToolkitWindowX11 *window;
    صحیح i;

    window = data;

    اگر (window->xsettings_first_time) {
        بازگشت;
    }

    اگر (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_setup = false;
        bool pixmap_already_setup = false;

        اگر (window->pixmap) {
            pixmap_already_setup = true;
        } وگرنه {
            dbe_already_setup = true;
        }

        /* set scale vars */
        window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
        window->iscale = (صحیح)SDL_ceilf(window->scale);
        اگر (window->scale < 1) {
            window->scale = 1;
        }
        اگر (SDL_roundf(window->scale) == window->scale) {
            window->scale = 0;
        }

        /* setup fonts */
#ifdef X_HAVE_UTF8_STRING
        اگر (window->font_set) {
            X11_XFreeFontSet(window->display, window->font_set);
        }
#endif
        اگر (window->font_struct) {
            X11_XFreeFont(window->display, window->font_struct);
        }

        X11Toolkit_InitWindowFonts(window);

        /* set up window */
        اگر (window->scale != 0) {
            window->window_width = SDL_lroundf((window->window_width/window->iscale) * window->scale);
            window->window_height = SDL_lroundf((window->window_height/window->iscale) * window->scale);
            window->pixmap_width = window->window_width;
            window->pixmap_height = window->window_height;
            window->pixmap = true;
        } وگرنه {
            window->pixmap = false;
        }

        اگر (window->pixmap) {
            اگر (!pixmap_already_setup) {
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                اگر (SDL_X11_HAVE_XDBE && window->xdbe) {
                    X11_XdbeDeallocateBackBufferName(window->display, window->buf);
                }
#endif
            }
            X11_XFreePixmap(window->display, window->drawable);
            X11Toolkit_InitWindowPixmap(window);
        } وگرنه {
            اگر (!dbe_already_setup) {
                X11_XFreePixmap(window->display, window->drawable);
#ifndef NO_SHARED_MEMORY
                اگر (window->image) {
                    XDestroyImage(window->image);
                    window->image = پوچ;
                }
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                اگر (SDL_X11_HAVE_XDBE && window->xdbe) {
                    window->buf = X11_XdbeAllocateBackBufferName(window->display, window->window, XdbeUndefined);
                    window->drawable = window->buf;
                }
#endif
            }
        }

        /* notify controls */
        برای (i = 0; i < window->controls_sz; i++) {
            window->controls[i]->do_size = true;

            اگر (window->controls[i]->func_on_scale_change) {
                window->controls[i]->func_on_scale_change(window->controls[i]);
            }

            اگر (window->controls[i]->func_calc_size) {
                window->controls[i]->func_calc_size(window->controls[i]);
            }

            window->controls[i]->do_size = false;
        }

        /* notify cb */
        اگر (window->cb_on_scale_change) {
            window->cb_on_scale_change(window, window->cb_data);
        }

        /* update ev scales */
        اگر (!window->pixmap) {
            window->ev_scale = window->ev_iscale = 1;
        } وگرنه {
            window->ev_scale = window->scale;
            window->ev_iscale = window->iscale;
        }
    }
}

ایستا تهی X11Toolkit_GetTextWidthHeightForFont(XFontStruct *font, ثابت نویسه *str, صحیح nbytes, صحیح *pwidth, صحیح *pheight, صحیح *ascent, صحیح *font_height)
{
    XCharStruct text_structure;
    صحیح font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &text_structure);
    *pwidth = text_structure.width;
    *pheight = text_structure.ascent + text_structure.descent;
    *ascent = text_structure.ascent;
    اگر (font_height) {
       *font_height = font_ascent + font_descent;
    }
}

ایستا تهی X11Toolkit_GetTextWidthHeight(SDL_ToolkitWindowX11 *data, ثابت نویسه *str, صحیح nbytes, صحیح *pwidth, صحیح *pheight, صحیح *ascent, صحیح *descent, صحیح *font_height)
{
#ifdef X_HAVE_UTF8_STRING
    اگر (data->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8TextExtents(data->font_set, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.width;
        *pheight = overall_logical.height;
        *ascent = -overall_logical.y;
        *descent = overall_logical.height - *ascent;

        اگر (font_height) {
            XFontSetExtents *extents;

            extents = X11_XExtentsOfFontSet(data->font_set);
            *font_height = extents->max_logical_extent.height;
        }
    } وگرنه
#endif
    {
        XCharStruct text_structure;
        صحیح font_direction, font_ascent, font_descent;
        X11_XTextExtents(data->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &text_structure);
        *pwidth = text_structure.width;
        *pheight = text_structure.ascent + text_structure.descent;
        *ascent = text_structure.ascent;
        *descent = text_structure.descent;

        اگر (font_height) {
            *font_height = font_ascent + font_descent;
        }
    }
}

#ifdef HAVE_FRIBIDI_H
SDL_List_گره *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, نویسه *txt, size_t sz, FriBidiParType *par)
#وگرنه
SDL_List_گره *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, نویسه *txt, size_t sz)
#endif
{
    SDL_List_گره *list;
    نویسه *str;
    نویسه *buffer;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = پوچ;
    thai = 0;
    str = txt;
    buffer = SDL_malloc(1);
    buffer[0] = 0;
    
#ifdef HAVE_FRIBIDI_H
    اگر (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    اگر (data->fribidi) {
        نویسه *fstr;
                
        fstr = SDL_FriBidi_Process(data->fribidi, str, sz, data->do_shaping, par);
        اگر (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#endif        

    وقتی (1) {
        نویسه *new;
        نویسه utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_StepUTF8((ثابت نویسه **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        اگر (cp == 0 || cond == (thai ? false : true)) {
            SDL_ToolkitTextElementX11 *element;
            
            element = SDL_malloc(اندازه(SDL_ToolkitTextElementX11));
            اگر (thai) {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_THAI;
            } وگرنه {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC;
            }
            element->str = SDL_strdup(buffer);
            element->sz = SDL_strlen(buffer);
            element->str_free = SDL_free;
            
            SDL_ListAdd(&list, element);
            
            SDL_free(buffer);
            buffer = SDL_malloc(1);
            buffer[0] = 0;
            thai = thai ? false : true;
        }

        اگر (!cp) {
            بشکن;
        }
        
        SDL_UCS4ToUTF8(cp, utf8);
        csz = SDL_strlen(buffer) + SDL_strlen(utf8) + 1;
        new = SDL_malloc(csz);
        SDL_strlcpy(new, buffer, csz);
        SDL_strlcat(new, utf8, csz);
        SDL_free(buffer);
        buffer = new;
    }

    SDL_free(buffer);
    اگر (free_txt) {
        SDL_free(txt);
    }
    بازگشت list;
}

تهی X11Toolkit_ShapeTextElements(SDL_ToolkitWindowX11 *data, SDL_List_گره *list)
{
    SDL_List_گره *cursor;
    SDL_ToolkitTextElementX11 *prev;
    صحیح temp;
    
    /* Shape and calculate bounding box */
    cursor = list;
    وقتی (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
#ifdef HAVE_LIBTHAI_H
        element->thai_overlays = پوچ;
#endif
        اگر (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            اگر (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, پوچ);
            } وگرنه {
#ifdef HAVE_LIBTHAI_H
                اگر (data->th) {
                    ساختار thcell_t *cells;
                    نویسه *tis_str;
                    نویسه *base_tis_str;
                    size_t cells_sz;
                    size_t base_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, اندازه(ساختار thcell_t));
                    data->th->make_cells((ثابت thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    base_tis_str_sz = cells_sz;
                    base_tis_str = SDL_malloc(base_tis_str_sz + 1);
                    برای (temp = 0; temp < cells_sz; temp++) {
                        base_tis_str[temp] = cells[temp].base;
                        
                        اگر (cells[temp].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            نویسه *pre;
                            صحیح temp2;
                            
                            overlay = SDL_malloc(اندازه(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت نویسه *)&cells[temp].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->بالاترین = false;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, پوچ);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, پوچ);
                            SDL_ListAdd(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        اگر (cells[temp].بالاترین) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            نویسه *pre;
                            صحیح temp2;
                            
                            overlay = SDL_malloc(اندازه(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ثابت نویسه *)&cells[temp].بالاترین, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->بالاترین = true;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, پوچ);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, پوچ);
                            SDL_ListAdd(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    base_tis_str[base_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, base_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(base_tis_str);
                }
#وگرنه
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
#endif            
            }
        } وگرنه {
            X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
        }
        
        cursor = cursor->next;
    }
    
    /* Add offsets */
    prev = پوچ;
    cursor = list;
    وقتی (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;        
        اگر (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } وگرنه {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->next;
    }
}


تهی X11Toolkit_DrawTextElements(SDL_ToolkitWindowX11 *data, SDL_List_گره *list, صحیح x, صحیح y)
{
    SDL_List_گره *cursor;
    
    cursor = list;
    
    وقتی (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        اگر (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            اگر (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
#ifdef X_HAVE_UTF8_STRING
                اگر (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } وگرنه
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } وگرنه {    
#ifdef HAVE_LIBTHAI_H
                SDL_List_گره *overlay_cursor;
                    
                /* Draw the base string */
#ifdef X_HAVE_UTF8_STRING
                اگر (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } وگرنه
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                وقتی (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->entry;
#ifdef X_HAVE_UTF8_STRING
                    اگر (data->utf8) {
                        X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } وگرنه
#endif
                    {
                        X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->next;
                }
#endif                
            }
        } وگرنه {
#ifdef X_HAVE_UTF8_STRING
            اگر (data->utf8) {
                X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } وگرنه
#endif
            {
                X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->next;
    }
}

صحیح X11Toolkit_GetTextElementsRect(SDL_List_گره *list, SDL_Rect *out)
{
    SDL_List_گره *cursor;
    صحیح ret;
    
    ret = 0;
    out->x = out->y = 0;
    out->w = out->h = 0;
    cursor = list;
    وقتی (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        
        out->w += element->rect.w;
        out->h = SDL_max(out->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->next;
    }
    
    بازگشت ret;
}

تهی X11Toolkit_FreeTextElementsListContents(SDL_List_گره *list)
{
    SDL_List_گره *cursor;
    
    cursor = list;
    وقتی (cursor) {
        SDL_ToolkitTextElementX11 *element;
#ifdef HAVE_LIBTHAI_H
        SDL_List_گره *overlay_cursor;
#endif

        element = cursor->entry;
        
        اگر (element->str_free) {
            element->str_free(element->str);
        }
        
#ifdef HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        وقتی (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->entry;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->next;
        }
        SDL_ListClear(&element->thai_overlays);
#endif
        
        SDL_free(element);
        
        cursor = cursor->next;
    }
}

#define X11Toolkit_FreeTextElements(x) X11Toolkit_FreeTextElementsListContents(x); SDL_ListClear(&x)
 
ایستا bool X11Toolkit_ShouldFlipUI(تهی) 
{
    SDL_Locale **current_locales;
    ایستا ثابت SDL_Locale rtl_locales[] = {
        { "ar", پوچ, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", پوچ, },
        { "iw", پوچ, },
        { "yi", پوچ, },
        { "ur", پوچ, },
        { "ug", پوچ, },
        { "kd", پوچ, },
        { "pk", "PK", },
        { "ps", پوچ, }
    }; 
    صحیح current_locales_sz;
    صحیح i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    اگر (current_locales_sz <= 0) {
        بازگشت false;        
    }
    برای (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        اگر (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            اگر (!rtl_locales[i].country) {
                بازگشت true;
            } وگرنه {
                بازگشت SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    بازگشت false;
}

SDL_ToolkitWindowX11 *X11Toolkit_CreateWindowStruct(SDL_Window *parent, SDL_ToolkitWindowX11 *tkparent, SDL_ToolkitWindowModeX11 mode, ثابت SDL_MessageBoxColor *colorhints, bool create_new_display)
{
    SDL_ToolkitWindowX11 *window;
    صحیح i;
#ifdef SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#endif
    #define ErrorFreeRetNull(x, y) SDL_SetError(x); SDL_free(y); بازگشت پوچ
    #define ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_SetError(x, y); SDL_free(z); بازگشت پوچ

    اگر (!SDL_X11_LoadSymbols()) {
        بازگشت پوچ;
    }

    // This code could get called from multiple threads maybe?
    X11_XInitThreads();

    window = (SDL_ToolkitWindowX11 *)SDL_malloc(اندازه(SDL_ToolkitWindowX11));
    اگر (!window) {
        SDL_SetError("Unable to allocate toolkit window structure");
        بازگشت پوچ;
    }

    window->mode = mode;
    window->tk_parent = tkparent;

#اگر SDL_SET_LOCALE
    اگر (mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        window->origlocale = setlocale(LC_ALL, پوچ);
        اگر (window->origlocale) {
            window->origlocale = SDL_strdup(window->origlocale);
            اگر (!window->origlocale) {
                SDL_free(window);
                بازگشت پوچ;
            }
            (تهی)setlocale(LC_ALL, "");
        }
    }
#endif

    window->parent_device = پوچ;
    اگر (create_new_display) {
        window->display = X11_XOpenDisplay(پوچ);
        window->display_close = true;
        اگر (!window->display) {
            ErrorFreeRetNull("Couldn't open X11 display", window);
        }
    } وگرنه {
        اگر (parent) {
            window->parent_device = SDL_GetVideoDevice();
            window->display = window->parent_device->internal->display;
            window->display_close = false;
        } وگرنه اگر (tkparent) {
            window->display = tkparent->display;
            window->display_close = false;
        } وگرنه {
            window->display = X11_XOpenDisplay(پوچ);
            window->display_close = true;
            اگر (!window->display) {
                ErrorFreeRetNull("Couldn't open X11 display", window);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    صحیح xrandr_event_base, xrandr_error_base;
    window->xrandr = X11_XRRQueryExtension(window->display, &xrandr_event_base, &xrandr_error_base);
#endif

#ifndef NO_SHARED_MEMORY
    window->shm_pixmap = False;
    window->shm = X11_XShmQueryExtension(window->display) ? SDL_X11_HAVE_SHM : false;
    اگر (window->shm) {
        صحیح major;
        صحیح minor;

        X11_XShmQueryVersion(window->display, &major, &minor, &window->shm_pixmap);
        اگر (window->shm_pixmap) {
            اگر (X11_XShmPixmapFormat(window->display) != ZPixmap) {
                window->shm_pixmap = False;
            }
        }
    }
#endif

    /* Scale/Xsettings */
    window->pixmap = false;
    window->xsettings_first_time = true;
    window->xsettings = xsettings_client_new(window->display, DefaultScreen(window->display), X11Toolkit_SettingsNotify, پوچ, window);
    window->xsettings_first_time = false;
    window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
    اگر (window->scale < 1) {
        window->scale = 1;
    }
    window->iscale = (صحیح)SDL_ceilf(window->scale);
    اگر (SDL_roundf(window->scale) == window->scale) {
        window->scale = 0;
    }

    /* Fonts */
    X11Toolkit_InitWindowFonts(window);

    /* Color hints */
#ifdef SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    اگر (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#endif

    اگر (!colorhints) {
#ifdef SDL_USE_LIBDBUS
        انتخاب (theme) {
            حالت SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                بشکن;
#اگر 0
            حالت SDL_SYSTEM_THEME_LIGHT_بالا_CONTRAST:
                colorhints = g_default_colors_light_بالا_contrast;
                بشکن;
            حالت SDL_SYSTEM_THEME_DARK_بالا_CONTRAST:
                colorhints = g_default_colors_dark_بالا_contrast;
                بشکن;
#endif
            پیشفرض:
                colorhints = g_default_colors;
        }
#وگرنه
        colorhints = g_default_colors;
#endif
    }
    window->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    برای (i = 0; i < SDL_MESSAGEBOX_COLOR_شمار; i++) {
        window->xcolor[i].flags = DoRed|DoGreen|DoBlue;
        window->xcolor[i].red = colorhints[i].r * 257;
        window->xcolor[i].green = colorhints[i].g * 257;
        window->xcolor[i].blue = colorhints[i].b * 257;
    }

    /* Generate bevel and pressed colors */
    window->xcolor_bevel_l1.flags = DoRed|DoGreen|DoBlue;
    window->xcolor_bevel_l1.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 12500, 0, 65535);
    window->xcolor_bevel_l1.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 12500, 0, 65535);
    window->xcolor_bevel_l1.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 12500, 0, 65535);

    window->xcolor_bevel_l2.flags = DoRed|DoGreen|DoBlue;
    window->xcolor_bevel_l2.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 32500, 0, 65535);
    window->xcolor_bevel_l2.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 32500, 0, 65535);
    window->xcolor_bevel_l2.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 32500, 0, 65535);

    window->xcolor_bevel_d.flags = DoRed|DoGreen|DoBlue;
    window->xcolor_bevel_d.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red - 22500, 0, 65535);
    window->xcolor_bevel_d.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green - 22500, 0, 65535);
    window->xcolor_bevel_d.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue - 22500, 0, 65535);

    window->xcolor_pressed.flags = DoRed|DoGreen|DoBlue;
    window->xcolor_pressed.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].red - 12500, 0, 65535);
    window->xcolor_pressed.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].green - 12500, 0, 65535);
    window->xcolor_pressed.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].blue - 12500, 0, 65535);

    window->xcolor_disabled_text.flags = DoRed|DoGreen|DoBlue;
    window->xcolor_disabled_text.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].red + 19500, 0, 65535);
    window->xcolor_disabled_text.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].green + 19500, 0, 65535);
    window->xcolor_disabled_text.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].blue + 19500, 0, 65535);

    /* Screen */
    window->parent = parent;
    اگر (parent) {
        SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(parent);
        window->screen = displaydata->screen;
    } وگرنه {
        window->screen = DefaultScreen(window->display);
    }

    /* Visuals */
    اگر (mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        window->visual = parent->internal->visual;
        window->cmap = parent->internal->colormap;
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
        window->depth = window->vi.depth;
    } وگرنه {
        window->visual = DefaultVisual(window->display, window->screen);
        window->cmap = DefaultColormap(window->display, window->screen);
        window->depth = DefaultDepth(window->display, window->screen);
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
    }

    /* Allocate colors */
    برای (i = 0; i < SDL_MESSAGEBOX_COLOR_شمار; i++) {
        X11_XAllocColor(window->display, window->cmap, &window->xcolor[i]);
    }
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l1);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l2);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_d);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_pressed);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_disabled_text);

    /* Control list */
    window->has_focus = false;
    window->controls = پوچ;
    window->controls_sz = 0;
    window->dyn_controls_sz = 0;
    window->fiddled_control = پوچ;
    window->dyn_controls = پوچ;

    /* Menu windows */
    window->popup_windows = پوچ;

    /* BIDI engine */
#ifdef HAVE_FRIBIDI_H
    window->fribidi = SDL_FriBidi_Create();
#endif

#ifdef HAVE_LIBTHAI_H
    window->th = SDL_LibThai_Create();
#endif
    
    /* Interface direction */
    window->flip_interface = X11Toolkit_ShouldFlipUI();
    
    بازگشت window;
}

ایستا تهی X11Toolkit_AddControlToWindow(SDL_ToolkitWindowX11 *window, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    window->controls_sz++;
    اگر (window->controls_sz == 1) {
        window->controls = (ساختار SDL_ToolkitControlX11 **)SDL_malloc(اندازه(ساختار SDL_ToolkitControlX11 *));
    } وگرنه {
        window->controls = (ساختار SDL_ToolkitControlX11 **)SDL_realloc(window->controls, اندازه(ساختار SDL_ToolkitControlX11 *) * window->controls_sz);
    }
    window->controls[window->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    اگر (control->dynamic) {
        window->dyn_controls_sz++;
        اگر (window->dyn_controls_sz == 1) {
            window->dyn_controls = (ساختار SDL_ToolkitControlX11 **)SDL_malloc(اندازه(ساختار SDL_ToolkitControlX11 *));
        } وگرنه {
            window->dyn_controls = (ساختار SDL_ToolkitControlX11 **)SDL_realloc(window->dyn_controls, اندازه(ساختار SDL_ToolkitControlX11 *) * window->dyn_controls_sz);
        }
        window->dyn_controls[window->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    اگر (control->selected) {
        window->focused_control = control;
    }
}

bool X11Toolkit_CreateWindowRes(SDL_ToolkitWindowX11 *data, صحیح w, صحیح h, صحیح cx, صحیح cy, نویسه *title)
{
    صحیح x, y;
    XSizeHints *sizehints;
    XSetWindowAttributes wnd_attr;
    Atom _NET_WM_WINDOW_TYPE, _NET_WM_WINDOW_TYPE_DIALOG, _NET_WM_WINDOW_TYPE_DROPDOWN_MENU, _NET_WM_WINDOW_TYPE_TOOLTIP;
    SDL_WindowData *windowdata = پوچ;
    Display *display = data->display;
    XGCValues ctx_vals;
    Window ریشه_win;
    Window parent_win;
    unsigned long gcflags = GCForeground | GCBackground;
    unsigned long valuemask;
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
#ifdef XRANDR_DISABLED_BY_DEFAULT
    ثابت bool use_xrandr_by_default = false;
#وگرنه
    ثابت bool use_xrandr_by_default = true;
#endif
#endif

    اگر (data->scale == 0) {
        data->window_width = w;
        data->window_height = h;
    } وگرنه {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        data->pixmap = true;
    }

    اگر (data->parent) {
        windowdata = data->parent->internal;
    }

    valuemask = CWEventMask | CWColormap;
    data->event_mask = ExposureMask |
                       ButtonPressMask | ButtonReleaseMask | کلید_Press_Mask | کلید_Release_Mask |
                       StructureNotifyMask | FocusChangeMask | PointerMotionMask;
    wnd_attr.event_mask = data->event_mask;
    wnd_attr.colormap = data->cmap;
    اگر (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    ریشه_win = ریشه_Window(display, data->screen);
    اگر (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        parent_win = windowdata->xwindow;
    } وگرنه {
        parent_win = ریشه_win;
    }

    data->window = X11_XCreateWindow(
        display, parent_win,
        0, 0,
        data->window_width, data->window_height,
        0, data->depth, درون_داد_Output, data->visual,
        valuemask, &wnd_attr);
    اگر (data->window == None) {
        بازگشت SDL_SetError("Couldn't create X window");
    }

    اگر (windowdata && data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
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
        X11_XChangeProperty(display, data->window, _NET_WM_STATE, XA_ATOM, 32,
                            PropModeReplace, (unsigned نویسه *)stateatoms, statecount);
    }

    اگر (windowdata && data->mode != SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        X11_XSetTransientForHint(display, data->window, windowdata->xwindow);
    }

    اگر (data->tk_parent) {
        X11_XSetTransientForHint(display, data->window, data->tk_parent->window);
    }

    SDL_X11_SetWindowTitle(display, data->window, title);

    // Let the window manager the type of the window
    اگر (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned نویسه *)&_NET_WM_WINDOW_TYPE_DIALOG, 1);
    } وگرنه اگر (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned نویسه *)&_NET_WM_WINDOW_TYPE_DROPDOWN_MENU, 1);
    } وگرنه اگر (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned نویسه *)&_NET_WM_WINDOW_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    data->wm_delete_message = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, data->window, &data->wm_delete_message, 1);
    data->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    اگر (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        x = cx;
        y = cy;
        برو MOVEWINDOW;
    }
    اگر (windowdata) {
        XWindowAttributes attrib;
        Window dummy;

        X11_XGetWindowAttributes(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.width - data->window_width) / 2;
        y = attrib.y + (attrib.height - data->window_height) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, ریشه_Window(display, data->screen), x, y, &x, &y, &dummy);
    } وگرنه {
        ثابت SDL_VideoDevice *dev = SDL_GetVideoDevice();
        اگر (dev && dev->displays && dev->رقم_displays > 0) {
            ثابت SDL_VideoDisplay *dpy = dev->displays[0];
            ثابت SDL_DisplayData *dpydata = dpy->internal;
            x = dpydata->x + ((dpy->current_mode->w - data->window_width) / 2);
            y = dpydata->y + ((dpy->current_mode->h - data->window_height) / 3);
        }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
        وگرنه اگر (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && data->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_out;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, ریشه_win);
            اگر (!screen_res) {
                برو NOXRANDR;
            }

            default_out = X11_XRRGetOutputPrimary(display, ریشه_win);
            اگر (default_out != None) {
                XRROutputInfo *out_info;

                out_info = X11_XRRGetOutputInfo(display, screen_res, default_out);
                اگر (out_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(out_info);
                    برو FIRSTOUTPUTXRANDR;
                }

                اگر (out_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                } وگرنه اگر (out_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                } وگرنه {
                    crtc_info = پوچ;
                }
                
                اگر (crtc_info) {
                    x = (crtc_info->width - data->window_width) / 2;
                    y = (crtc_info->height - data->window_height) / 3;
                    X11_XRRFreeOutputInfo(out_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } وگرنه {
                    X11_XRRFreeOutputInfo(out_info);
                    برو NOXRANDR;
                }
            } وگرنه {
                    FIRSTOUTPUTXRANDR:
                    اگر (screen_res->noutput > 0) {
                        XRROutputInfo *out_info;

                        out_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        اگر (!out_info) {
                            برو FIRSTCRTCXRANDR;
                        }

                        اگر (out_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                        } وگرنه اگر (out_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                        } وگرنه {
                            crtc_info = پوچ;
                        }

                        اگر (!crtc_info) {
                            X11_XRRFreeOutputInfo(out_info);
                            برو FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeOutputInfo(out_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        برو MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    اگر (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        برو NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    اگر (crtc_info) {
                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } وگرنه {
                        X11_XRRFreeScreenResources(screen_res);
                        برو NOXRANDR;
                    }
            }
        }
#endif
        وگرنه {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (DisplayWidth(display, data->screen) - data->window_width) / 2;
            y = (DisplayHeight(display, data->screen) - data->window_height) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMoveWindow(display, data->window, x, y);
    data->window_x = x;
    data->window_y = y;

    sizehints = X11_XAllocSizeHints();
    اگر (sizehints) {
        sizehints->flags = USPosition | USSize | PMaxSize | PMinSize;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->width = data->window_width;
        sizehints->height = data->window_height;

        sizehints->min_width = sizehints->max_width = data->window_width;
        sizehints->min_height = sizehints->max_height = data->window_height;

        X11_XSetWMNormalHints(display, data->window, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, data->window);

    data->drawable = data->window;
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    اگر (SDL_X11_HAVE_XDBE && !data->pixmap) {
        صحیح xdbe_major, xdbe_minor;
        اگر (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            data->xdbe = true;
            data->buf = X11_XdbeAllocateBackBufferName(display, data->window, XdbeUndefined);
            data->drawable = data->buf;
        } وگرنه {
            data->xdbe = false;
        }
    }
#endif

    X11Toolkit_InitWindowPixmap(data);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    اگر (!data->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = data->font_struct->fid;
    }
    data->ctx = X11_XCreateGC(data->display, data->drawable, gcflags, &ctx_vals);
    اگر (data->ctx == None) {
        بازگشت SDL_SetError("Couldn't create graphics context");
    }

    data->close = false;
    data->کلید_control_esc = data->کلید_control_enter = پوچ;
    اگر (!data->pixmap) {
        data->ev_scale = data->ev_iscale = 1;
    } وگرنه {
        data->ev_scale = data->scale;
        data->ev_iscale = data->iscale;
    }

#اگر SDL_GRAB
    اگر (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XGrabPointer(display, data->window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
        X11_XGrabKeyboard(display, data->window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
#endif

    بازگشت true;
}

ایستا تهی X11Toolkit_DrawWindow(SDL_ToolkitWindowX11 *data) {
    SDL_Rect rect;
    صحیح i;

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    اگر (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeBeginIdiom(data->display);
    }
#endif

    X11_XSetForeground(data->display, data->ctx, data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    اگر (data->pixmap) {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->pixmap_width, data->pixmap_height);
    } وگرنه {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->window_width, data->window_height);
    }

    برای (i = 0; i < data->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = data->controls[i];
        اگر (control) {
            اگر (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    اگر (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        XdbeSwapInfo swap_info;
        swap_info.swap_window = data->window;
        swap_info.swap_action = XdbeUndefined;
        X11_XdbeSwapBuffers(data->display, &swap_info, 1);
        X11_XdbeEndIdiom(data->display);
    }
#endif

    اگر (data->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = data->window_width;
        rect.h = data->window_height;
#ifndef NO_SHARED_MEMORY
        اگر (data->shm) {
            اگر (data->shm_pixmap) {
                X11_XFlush(data->display);
                X11_XSync(data->display, false);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->shm_info.shmaddr, data->shm_bytes_per_سطر);
                SDL_BlitSurfaceScaled(scale_surface, پوچ, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(data->display, data->drawable, data->window, data->ctx, 0, 0, data->window_width, data->window_height, 0, 0);
            } وگرنه {
                X11_XShmGetImage(data->display, data->drawable, data->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->image->data, data->image->bytes_per_سطر);
                SDL_BlitSurfaceScaled(scale_surface, پوچ, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                X11_XShmPutImage(data->display, data->window, data->ctx, data->image, 0, 0, 0, 0, data->window_width, data->window_height, False);
            }
        } وگرنه
#endif
        {
            XImage *image;

            image = X11_XGetImage(data->display, data->drawable, 0, 0 , data->pixmap_width, data->pixmap_height, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), image->data, image->bytes_per_سطر);
            SDL_BlitSurfaceScaled(scale_surface, پوچ, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
            X11_XPutImage(data->display, data->window, data->ctx, image, 0, 0, 0, 0, data->window_width, data->window_height);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(data->display);
}

ایستا SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_ToolkitWindowX11 *data, صحیح x, صحیح y)
{
    صحیح i;

    برای (i = 0; i < data->controls_sz; i++) {
        SDL_Rect *rect = &data->controls[i]->rect;
        اگر ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            بازگشت data->controls[i];
        }
    }

    بازگشت پوچ;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
ایستا Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_ToolkitWindowX11 *data = (SDL_ToolkitWindowX11 *)arg;

    اگر (event->xany.display != data->display) {
        بازگشت False;
    }

    اگر (event->xany.window == data->window) {
        بازگشت True;
    }

    بازگشت False;
}

تهی X11Toolkit_ProcessWindowEvents(SDL_ToolkitWindowX11 *data, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    اگر ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        بازگشت;
    }

    data->draw = false;
    data->e = e;

    انتخاب (e->type) {
        حالت Expose:
            data->draw = true;
            بشکن;
        حالت ClientMessage:
            اگر (e->xclient.message_type == data->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.data.l[0] == data->wm_delete_message) {
                data->close = true;
            }
            بشکن;
        حالت FocusIn:
            data->has_focus = true;
            بشکن;
        حالت FocusOut:
            data->has_focus = false;
            اگر (data->fiddled_control) {
                data->fiddled_control->selected = false;
            }
            data->fiddled_control = پوچ;
            برای (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
            }
            بشکن;
        حالت MotionNotify:
            اگر (data->has_focus) {
                data->previous_control = data->fiddled_control;
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                اگر (data->previous_control) {
                    data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    اگر (data->previous_control->func_on_state_change) {
                        data->previous_control->func_on_state_change(data->previous_control);
                    }
                    data->draw = true;
                }
                اگر (data->fiddled_control) {
                    اگر (data->fiddled_control->dynamic) {
                        data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        اگر (data->fiddled_control->func_on_state_change) {
                            data->fiddled_control->func_on_state_change(data->fiddled_control);
                        }
                        data->draw = true;
                    } وگرنه {
                        data->fiddled_control = پوچ;
                    }
                }
            }
            بشکن;
        حالت ButtonPress:
            data->previous_control = data->fiddled_control;
            اگر (data->previous_control) {
                data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                اگر (data->previous_control->func_on_state_change) {
                    data->previous_control->func_on_state_change(data->previous_control);
                }
                data->draw = true;
            }
            اگر (e->xbutton.button == Button1) {
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                اگر (data->fiddled_control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    اگر (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->draw = true;
                }
            }
            بشکن;
        حالت ButtonRelease:
            اگر (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
                صحیح cx;
                صحیح cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                اگر (cy < 0 || cx < 0) {
                    data->close = true;
                }

                اگر (cy > data->window_height || cx > data->window_width) {
                    data->close = true;
                }
            }

            اگر ((e->xbutton.button == Button1) && (data->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                اگر (data->fiddled_control == control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    اگر (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    data->draw = true;
                }
            }
            بشکن;
        حالت کلید_Press:
            data->last_کلید_pressed = X11_XLookupKeysym(&e->xkey, 0);

            اگر (data->last_کلید_pressed == XK_Escape) {
                برای (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    اگر(data->controls[data->ev_i]->is_default_esc) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->کلید_control_esc = data->controls[data->ev_i];
                    }
                }
            } وگرنه اگر ((data->last_کلید_pressed == XK_Return) || (data->last_کلید_pressed == XK_KP_Enter)) {
                برای (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    اگر(data->controls[data->ev_i]->selected) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->کلید_control_enter = data->controls[data->ev_i];
                    }
                }
            }
            بشکن;
        حالت کلید_Release:
        {
            کلید_Sym کلید = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            اگر (کلید != data->last_کلید_pressed) {
                بشکن;
            }

            اگر (کلید == XK_Escape) {
                اگر (data->کلید_control_esc) {
                    اگر (data->کلید_control_esc->func_on_state_change) {
                        data->کلید_control_esc->func_on_state_change(data->کلید_control_esc);
                    }
                }
            } وگرنه اگر ((کلید == XK_Return) || (کلید == XK_KP_Enter)) {
                اگر (data->کلید_control_enter) {
                    اگر (data->کلید_control_enter->func_on_state_change) {
                        data->کلید_control_enter->func_on_state_change(data->کلید_control_enter);
                    }
                }
            } وگرنه اگر (کلید == XK_Tab || کلید == XK_چپ || کلید == XK_راست) {
                اگر (data->focused_control) {
                    data->focused_control->selected = false;
                }
                data->draw = true;
                برای (data->ev_i = 0; data->ev_i < data->dyn_controls_sz; data->ev_i++) {
                    اگر (data->dyn_controls[data->ev_i] == data->focused_control) {
                        صحیح next_index;

                        اگر (کلید == XK_چپ) {
                            next_index = data->ev_i - 1;
                        } وگرنه {
                            next_index = data->ev_i + 1;
                        }
                        اگر ((next_index >= data->dyn_controls_sz) || (next_index < 0)) {
                            اگر (کلید == XK_راست || کلید == XK_چپ) {
                                next_index = data->ev_i;
                            } وگرنه {
                                next_index = 0;
                            }
                        }
                        data->focused_control = data->dyn_controls[next_index];
                        data->focused_control->selected = true;
                        بشکن;
                    }
                }
            }
            بشکن;
        }
    }

    اگر (data->draw) {
        X11Toolkit_DrawWindow(data);
    }
}

تهی X11Toolkit_DoWindowEventLoop(SDL_ToolkitWindowX11 *data) {
   وقتی (!data->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(data->display, &e);
        اگر (data->xsettings) {
            xsettings_client_process_event(data->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(data->display, &e, X11Toolkit_EventTest, (XPointer)data);
        X11Toolkit_ProcessWindowEvents(data, &e);
    }
}


تهی X11Toolkit_ResizeWindow(SDL_ToolkitWindowX11 *data, صحیح w, صحیح h) {
    اگر (!data->pixmap) {
        data->window_width = w;
        data->window_height = h;
    } وگرنه {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        X11_XFreePixmap(data->display, data->drawable);
        X11Toolkit_InitWindowPixmap(data);
    }

    X11_XResizeWindow(data->display, data->window, data->window_width, data->window_height);
}

ایستا تهی X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->window->display, icon_control->icon_char_font);
    SDL_free(control);
}

ایستا تهی X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->window->iscale;
    control->rect.h -= 2 * control->window->iscale;
    X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + (2 * control->window->iscale), control->rect.y + (2* control->window->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    انتخاب (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        حالت SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                بشکن;
        حالت SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                بشکن;
        حالت SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                بشکن;
    }
    X11_XSetFont(control->window->display, control->window->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    اگر (!control->window->utf8) {
        X11_XSetFont(control->window->display, control->window->ctx, control->window->font_struct->fid);
    }

    control->rect.w += 2 * control->window->iscale;
    control->rect.h += 2 * control->window->iscale;
}

ایستا تهی X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    صحیح icon_char_w;
    صحیح icon_wh;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11Toolkit_GetTextWidthHeightForFont(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, پوچ);
    base_control->rect.w = icon_char_w;
    base_control->rect.h = control->icon_char_h;
    icon_wh = SDL_max(icon_char_w, control->icon_char_h) + SDL_TOOLKIT_X11_ELEMENT_PADDING * 2 * base_control->window->iscale;
    base_control->rect.w = icon_wh;
    base_control->rect.h = icon_wh;
    base_control->rect.y = 0;
    base_control->rect.x = 0;
    control->icon_char_y = control->icon_char_a + (base_control->rect.h - control->icon_char_h)/2;
    control->icon_char_x = (base_control->rect.w - icon_char_w)/2;
    base_control->rect.w += 2 * base_control->window->iscale;
    base_control->rect.h += 2 * base_control->window->iscale;
}

ایستا تهی X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    نویسه *font;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11_XFreeFont(base_control->window->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_SIZE * base_control->window->iscale);
    control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
    SDL_free(font);
    اگر (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * base_control->window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_ToolkitWindowX11 *window, SDL_MessageBoxFlags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    نویسه *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(اندازه(SDL_ToolkitIconControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    اگر (!control) {
        SDL_SetError("Unable to allocate icon control structure");
        بازگشت پوچ;
    }

    /* Fill out struct */
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawIconControl;
    base_control->func_free = X11Toolkit_DestroyIconControl;
    base_control->func_on_state_change = پوچ;
    base_control->func_calc_size = X11Toolkit_CalculateIconControl;
    base_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = false;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_SIZE * window->iscale);
    control->icon_char_font = X11_XLoadQueryFont(window->display, font);
    SDL_free(font);
    اگر (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        اگر (!control->icon_char_font) {
            SDL_free(control);
            بازگشت پوچ;
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
        X11_XAllocColor(window->display, window->cmap, &control->xcolor_white);
        X11_XAllocColor(window->display, window->cmap, &control->xcolor_red);
        X11_XAllocColor(window->display, window->cmap, &control->xcolor_red_darker);
        بشکن;
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
        X11_XAllocColor(window->display, window->cmap, &control->xcolor_black);
        X11_XAllocColor(window->display, window->cmap, &control->xcolor_yellow);
        بشکن;
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
        X11_XAllocColor(window->display, window->cmap, &control->xcolor_white);
        X11_XAllocColor(window->display, window->cmap, &control->xcolor_blue);
        بشکن;
    پیشفرض:
        X11_XFreeFont(window->display, control->icon_char_font);
        SDL_free(control);
        بازگشت پوچ;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    اگر (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } وگرنه اگر (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } وگرنه {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    اگر (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } وگرنه اگر (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } وگرنه {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    اگر (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } وگرنه اگر (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } وگرنه {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(window->display, window->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(base_control);

    X11Toolkit_AddControlToWindow(window, base_control);
    بازگشت base_control;
}

bool X11Toolkit_NotifyControlOfSizeChange(SDL_ToolkitControlX11 *control) {
    اگر (control->func_calc_size) {
        control->func_calc_size(control);
        بازگشت true;
    } وگرنه {
        بازگشت false;
    }
}

ایستا تهی X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11Toolkit_GetTextElementsRect(button_control->text, &button_control->text_rect);
    اگر (control->do_size) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.h;
    }
    button_control->text_rect.x = (control->rect.w - button_control->text_rect.w)/2;
    button_control->text_rect.y = (control->rect.h - button_control->text_rect.h)/2;
}


ایستا تهی X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    /* Draw bevel */
    اگر (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
            X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor_bevel_d.pixel);
            X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

            X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor_bevel_l2.pixel);
            X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - (1* control->window->iscale), control->rect.h - (1* control->window->iscale));

            X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor_bevel_l1.pixel);
            X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x + 1 * control->window->iscale, control->rect.y + 1 * control->window->iscale,
                                   control->rect.w - 3 * control->window->iscale, control->rect.h - 2 * control->window->iscale);

            X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
            X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                               control->rect.x + 1 * control->window->iscale, control->rect.y + 1 * control->window->iscale,
                               control->rect.w - 3 * control->window->iscale, control->rect.h - 3 * control->window->iscale);

            X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor_pressed.pixel);
            X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                               control->rect.x + 2 * control->window->iscale, control->rect.y + 2 * control->window->iscale,
                               control->rect.w - 4 * control->window->iscale, control->rect.h - 4 * control->window->iscale);
        } وگرنه {
            اگر (control->selected) {
                X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x + 1 * control->window->iscale, control->rect.y + 1 * control->window->iscale,
                                   control->rect.w - 3 * control->window->iscale, control->rect.h - 3 * control->window->iscale);

                X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x + 2 * control->window->iscale, control->rect.y + 2 * control->window->iscale,
                                   control->rect.w - 4 * control->window->iscale, control->rect.h - 4 * control->window->iscale);

                X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x + 2 * control->window->iscale, control->rect.y + 2 * control->window->iscale,
                                   control->rect.w - 5 * control->window->iscale, control->rect.h - 5 * control->window->iscale);

                X11_XSetForeground(control->window->display, control->window->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x + 3 * control->window->iscale, control->rect.y + 3 * control->window->iscale,
                                   control->rect.w - 6 * control->window->iscale, control->rect.h - 6 * control->window->iscale);
            } وگرنه {
                X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - 1 * control->window->iscale, control->rect.h - 1 * control->window->iscale);

                X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x + 1 * control->window->iscale, control->rect.y + 1 * control->window->iscale,
                                   control->rect.w - 2 * control->window->iscale, control->rect.h - 2 * control->window->iscale);

                X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x + 1 * control->window->iscale, control->rect.y + 1 * control->window->iscale,
                                   control->rect.w - 3 * control->window->iscale, control->rect.h - 3 * control->window->iscale);

                X11_XSetForeground(control->window->display, control->window->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->window->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->window->display, control->window->drawable, control->window->ctx,
                                   control->rect.x + 2 * control->window->iscale, control->rect.y + 2 * control->window->iscale,
                                   control->rect.w - 4 * control->window->iscale, control->rect.h - 4 * control->window->iscale);
            }
        }

    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    X11Toolkit_DrawTextElements(control->window, button_control->text, control->rect.x + button_control->text_rect.x, control->rect.y + button_control->text_rect.y);
}

ایستا تهی X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    اگر (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_data);
    }
}

ایستا تهی X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11Toolkit_FreeTextElements(button_control->text);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_ToolkitWindowX11 *window, ثابت SDL_MessageBoxButtonData *data) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *base_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(اندازه(SDL_ToolkitButtonControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    اگر (!control) {
        SDL_SetError("Unable to allocate button control structure");
        بازگشت پوچ;
    }
    base_control->window = window;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->func_calc_size = X11Toolkit_CalculateButtonControl;
    base_control->func_draw = X11Toolkit_DrawButtonControl;
    base_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    base_control->func_free = X11Toolkit_DestroyButtonControl;
    base_control->func_on_scale_change = پوچ;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = true;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    اگر (data->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        base_control->is_default_esc = true;
    }
    اگر (data->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        base_control->is_default_enter = true;
        base_control->selected = true;
    }
    control->cb = پوچ;
    control->data = data;
#ifdef HAVE_FRIBIDI_H
    control->text = X11Toolkit_MakeTextElements(base_control->window, (نویسه *)control->data->text, SDL_strlen(control->data->text), پوچ);
#وگرنه 
    control->text = X11Toolkit_MakeTextElements(base_control->window, (نویسه *)control->data->text, SDL_strlen(control->data->text));
#endif
    X11Toolkit_ShapeTextElements(base_control->window, control->text);
    
    base_control->do_size = true;
    X11Toolkit_CalculateButtonControl(base_control);
    base_control->do_size = false;

    X11Toolkit_AddControlToWindow(window, base_control);
    بازگشت base_control;
}

تهی X11Toolkit_RegisterCallbackForButtonControl(SDL_ToolkitControlX11 *control, تهی *data, تهی (*cb)(ساختار SDL_ToolkitControlX11 *, تهی *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_data = data;
    button_control->cb = cb;
}

ثابت SDL_MessageBoxButtonData *X11Toolkit_GetButtonControlData(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    بازگشت button_control->data;
}

تهی X11Toolkit_DestroyWindow(SDL_ToolkitWindowX11 *data) {
    صحیح i;

    اگر (!data) {
        بازگشت;
    }

#اگر SDL_GRAB
    اگر (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XUngrabPointer(data->display, CurrentTime);
        X11_XUngrabKeyboard(data->display, CurrentTime);
    }
#endif

    برای (i = 0; i < data->controls_sz; i++) {
        اگر (data->controls[i]->func_free) {
            data->controls[i]->func_free(data->controls[i]);
        }
    }
    SDL_free(data->controls);
    SDL_free(data->dyn_controls);

    اگر (data->popup_windows) {
        SDL_ListClear(&data->popup_windows);
    }

    اگر (data->pixmap) {
        X11_XFreePixmap(data->display, data->drawable);
    }

#ifndef NO_SHARED_MEMORY
    اگر (data->pixmap && data->shm) {
        X11_XShmDetach(data->display, &data->shm_info);
        اگر (!data->shm_pixmap) {
            XDestroyImage(data->image);
        }
        shmdt(data->shm_info.shmaddr);
    }
#endif

#ifdef X_HAVE_UTF8_STRING
    اگر (data->font_set) {
        X11_XFreeFontSet(data->display, data->font_set);
        data->font_set = پوچ;
    }
#endif

    اگر (data->font_struct) {
        X11_XFreeFont(data->display, data->font_struct);
        data->font_struct = پوچ;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    اگر (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeDeallocateBackBufferName(data->display, data->buf);
    }
#endif

    اگر (data->xsettings) {
        xsettings_client_destroy(data->xsettings);
    }

    X11_XFreeGC(data->display, data->ctx);

    اگر (data->display) {
        اگر (data->window != None) {
            X11_XWithdrawWindow(data->display, data->window, data->screen);
            X11_XDestroyWindow(data->display, data->window);
            data->window = None;
        }

        اگر (data->display_close) {
            X11_XCloseDisplay(data->display);
        }
        data->display = پوچ;
    }

#اگر SDL_SET_LOCALE
    اگر (data->origlocale && (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG)) {
        (تهی)setlocale(LC_ALL, data->origlocale);
        SDL_free(data->origlocale);
    }
#endif

#ifdef HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(data->fribidi);
#endif

#ifdef HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(data->th);
#endif

    SDL_free(data);
}

ایستا صحیح X11_Toolkit_شمار_سطرها_Of_Text(ثابت نویسه *text)
{
    صحیح result = 0;
    وقتی (text && *text) {
        ثابت نویسه *lf = SDL_strchr(text, '\n');
        result++; // even without an endline, this counts as a line.
        text = lf ? lf + 1 : پوچ;
    }
    بازگشت result;
}

ایستا تهی X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحیح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    برای (i = 0; i < label_control->sz; i++) {
        X11Toolkit_DrawTextElements(control->window, label_control->سطرها[i].text, control->rect.x + label_control->سطرها[i].rect.x, control->rect.y + label_control->سطرها[i].rect.y);
    }
}

ایستا تهی X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    صحیح i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    برای (i = 0; i < label_control->sz; i++) {
        X11Toolkit_FreeTextElements(label_control->سطرها[i].text);
    }
    SDL_free(label_control->سطرها);
    SDL_free(label_control);
}

ایستا تهی X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitLabelControlX11 *control;
    صحیح i;

    control = (SDL_ToolkitLabelControlX11 *)base_control;
    
    اگر (base_control->do_size) {
        base_control->rect.w = 0;
        base_control->rect.h = 0;
    }
    
    برای (i = 0; i < control->sz; i++) {
        صحیح font_h;
        
        font_h = X11Toolkit_GetTextElementsRect(control->سطرها[i].text, &control->سطرها[i].rect);
        
        اگر (base_control->do_size) {
            base_control->rect.w = SDL_max(base_control->rect.w, control->سطرها[i].rect.w);
        }
        
        اگر (i > 0) {
            control->سطرها[i].rect.y = font_h + control->سطرها[i - 1].rect.y;
        } وگرنه {
            control->سطرها[i].rect.y = 0;
        }
    }

#ifdef HAVE_FRIBIDI_H
    اگر (base_control->window->fribidi) {
        FriBidiParType first_ndn_dir;
        صحیح last_ndn;
    
        first_ndn_dir = FRIBIDI_PAR_LTR;
        برای (i = 0; i < control->sz; i++) {
            اگر (control->سطرها[i].par != FRIBIDI_PAR_ON) {
                first_ndn_dir = control->سطرها[i].par;
            }
        }

        last_ndn = -1;
        برای (i = 0; i < control->sz; i++) {
            انتخاب (control->سطرها[i].par) {
                حالت FRIBIDI_PAR_LTR:
                    control->سطرها[i].rect.x = 0;
                    last_ndn = i;
                    بشکن;
                حالت FRIBIDI_PAR_RTL:
                    control->سطرها[i].rect.x = base_control->rect.w - control->سطرها[i].rect.w;
                    last_ndn = i;
                    بشکن;
                پیشفرض:
                    اگر (last_ndn != -1) {
                        اگر (control->سطرها[last_ndn].par == FRIBIDI_PAR_RTL) {
                            control->سطرها[i].rect.x = base_control->rect.w - control->سطرها[i].rect.w;
                        } وگرنه {
                            control->سطرها[i].rect.x = 0;
                        }
                    } وگرنه {
                        اگر (first_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->سطرها[i].rect.x = base_control->rect.w - control->سطرها[i].rect.w;
                        } وگرنه {
                            control->سطرها[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#endif
    
    اگر (base_control->do_size && control->sz) {
        base_control->rect.h = control->سطرها[control->sz - 1].rect.y + control->سطرها[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_ToolkitWindowX11 *window, نویسه *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    صحیح i;
    
    اگر (!utf8) {
        بازگشت پوچ;
    }
 
    اگر (!SDL_strcmp(utf8, "")) {
        بازگشت پوچ;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(اندازه(SDL_ToolkitLabelControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    اگر (!control) {
        SDL_SetError("Unable to allocate label control structure");
        بازگشت پوچ;
    }
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawLabelControl;
    base_control->func_on_state_change = پوچ;
    base_control->func_calc_size = X11Toolkit_CalculateLabelControl;
    base_control->func_free  = X11Toolkit_DestroyLabelControl;
    base_control->func_on_scale_change = پوچ;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = false;
    base_control->rect.w = 0;
    base_control->rect.h = 0;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_شمار_سطرها_Of_Text(utf8);
    control->سطرها = SDL_calloc(control->sz, اندازه(SDL_Toolkit_Label_Control_سطر_X11));
    برای (i = 0; i < control->sz; i++) {
        ثابت نویسه *lf = SDL_strchr(utf8, '\n');
        ثابت صحیح length = lf ? (lf - utf8) : SDL_strlen(utf8);
        صحیح sz;
        
        sz = length;
        اگر (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#ifdef HAVE_FRIBIDI_H
        control->سطرها[i].text = X11Toolkit_MakeTextElements(base_control->window, (نویسه *)utf8, sz, &control->سطرها[i].par);
#وگرنه 
        control->سطرها[i].text = X11Toolkit_MakeTextElements(base_control->window, (نویسه *)utf8, sz);
#endif
        X11Toolkit_ShapeTextElements(base_control->window, control->سطرها[i].text);

        utf8 += length + 1;
        اگر (!lf) {
            بشکن;
        }
    }

    base_control->do_size = true;
    X11Toolkit_CalculateLabelControl(base_control);
    base_control->do_size = false;
    X11Toolkit_AddControlToWindow(window, base_control);

    بازگشت base_control;
}

صحیح X11_Toolkit_Get_Label_Control_First_سطر_Height(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    بازگشت label_control->سطرها[0].rect.h;
}

تهی X11Toolkit_SignalWindowClose(SDL_ToolkitWindowX11 *data) {
    data->close = true;
}

#endif // SDL_VIDEO_DRIVER_X11
