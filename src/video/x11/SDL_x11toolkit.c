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

#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাৱ "../../SDL_list.h"
#অন্তর্ভাৱ "SDL_x11video.h"
#ifdef SDL_USE_LIBDBUS
#অন্তর্ভাৱ "../../core/linux/SDL_system_theme.h"
#endif
#ifdef HAVE_FRIBIDI_H
#অন্তর্ভাৱ "../../core/unix/SDL_fribidi.h"
#endif
#অন্তর্ভাৱ "SDL_x11dyn.h"
#অন্তর্ভাৱ "SDL_x11toolkit.h"
#অন্তর্ভাৱ "SDL_x11settings.h"
#অন্তর্ভাৱ "SDL_x11modes.h"
#অন্তর্ভাৱ "xsettings-client.h"
#অন্তর্ভাৱ <X11/keysym.h>
#অন্তর্ভাৱ <locale.h>

#define SDL_SET_LOCALE 1
#define SDL_GRAB 1

প্রকারনির্দেশ গণনা SDL_ToolkitTextTypeX11
{
    SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC,
    SDL_TOOLKIT_TEXT_TYPE_X11_THAI
} SDL_ToolkitTextTypeX11;

#ifdef HAVE_LIBTHAI_H
প্রকারনির্দেশ সংরচনা SDL_ToolkitThaiOverlayX11
{
    bool শীৰ্ষ;
    ৱর্ণ *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#endif

প্রকারনির্দেশ সংরচনা SDL_ToolkitTextElementX11
{
    SDL_ToolkitTextTypeX11 type;
    ৱর্ণ *str;
    size_t sz;
    SDL_Rect rect;
    পূর্ণাঙ্ক font_h;
    শূন্য (*str_free)(শূন্য *);
#ifdef HAVE_LIBTHAI_H
    SDL_List_গ্ৰন্থি *thai_overlays;
#endif
} SDL_ToolkitTextElementX11;

প্রকারনির্দেশ সংরচনা SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Icon type */
    SDL_MessageBoxFlags flags;
    ৱর্ণ icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    পূর্ণাঙ্ক icon_char_x;
    পূর্ণাঙ্ক icon_char_y;
    পূর্ণাঙ্ক icon_char_a;
    পূর্ণাঙ্ক icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

প্রকারনির্দেশ সংরচনা SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Data */
    ধ্রুৱ SDL_MessageBoxButtonData *data;

    /* Text */
    SDL_List_গ্ৰন্থি *text;
    SDL_Rect text_rect;
    
    /* Callback */
    শূন্য *cb_data;
    শূন্য (*cb)(সংরচনা SDL_ToolkitControlX11 *, শূন্য *);
} SDL_ToolkitButtonControlX11;

প্রকারনির্দেশ সংরচনা SDL_Toolkit_Label_Control_সাৰি_X11
{
    SDL_List_গ্ৰন্থি *text;
    SDL_Rect rect;
#ifdef HAVE_FRIBIDI_H
    FriBidiParType par;
#endif
} SDL_Toolkit_Label_Control_সাৰি_X11;

প্রকারনির্দেশ সংরচনা SDL_ToolkitLabelControlX11
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
    SDL_Toolkit_Label_Control_সাৰি_X11 *সাৰিগুলি;
    size_t sz;
} SDL_ToolkitLabelControlX11;

প্রকারনির্দেশ সংরচনা SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_গ্ৰন্থি *menu_বস্তুসমূহ;
} SDL_ToolkitMenuBarControlX11;

প্রকারনির্দেশ সংরচনা SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_গ্ৰন্থি *menu_বস্তুসমূহ;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
স্থির ধ্রুৱ ৱর্ণ *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#define G_ICONFONT_SIZE 22

/* General UI font */
স্থির ধ্রুৱ ৱর্ণ g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
স্থির ধ্রুৱ ৱর্ণ g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

স্থির ধ্রুৱ ৱর্ণ *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    রিক্ত
};
#define G_TOOLKITFONT_SIZE 140

স্থির ধ্রুৱ SDL_MessageBoxColor g_default_colors[SDL_MESSAGEBOX_COLOR_গুনতি] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ifdef SDL_USE_LIBDBUS
স্থির ধ্রুৱ SDL_MessageBoxColor g_default_colors_dark[SDL_MESSAGEBOX_COLOR_গুনতি] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#যদি 0
স্থির ধ্রুৱ SDL_MessageBoxColor g_default_colors_dark_উপৰেৰ_contrast[SDL_MESSAGEBOX_COLOR_গুনতি] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

স্থির ধ্রুৱ SDL_MessageBoxColor g_default_colors_light_উপৰেৰ_contrast[SDL_MESSAGEBOX_COLOR_গুনতি] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#endif

#endif

স্থির পূর্ণাঙ্ক g_shm_error;
স্থির পূর্ণাঙ্ক (*g_old_error_handler)(Display *, XErrorEvent *) = রিক্ত;

স্থির পূর্ণাঙ্ক X11Toolkit_SharedMemoryErrorHandler(Display *d, XErrorEvent *e)
{
    যদি (e->error_code == BadAccess || e->error_code == BadRequest) {
        g_shm_error = True;
        ঘূৰাই 0;
    }
    ঘূৰাই g_old_error_handler(d, e);
}

স্থির শূন্য X11Toolkit_InitWindowPixmap(SDL_ToolkitWindowX11 *data) {
    যদি (data->pixmap) {
#ifndef NO_SHARED_MEMORY
        যদি (!data->shm_pixmap) {
            data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
        }
#অন্যথা
        data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
#endif
#ifndef NO_SHARED_MEMORY
        যদি (data->shm) {
            data->image = X11_XShmCreateImage(data->display, data->visual, data->depth, ZPixmap, রিক্ত, &data->shm_info, data->pixmap_width, data->pixmap_height);
            যদি (data->image) {
                data->shm_bytes_per_সাৰি = data->image->bytes_per_সাৰি;

                data->shm_info.shmid = shmget(IPC_PRIVATE, data->image->bytes_per_সাৰি * data->image->height, IPC_CREAT | 0777);
                যদি (data->shm_info.shmid < 0) {
                    XDestroyImage(data->image);
                    data->image = রিক্ত;
                    data->shm = false;
                    ঘূৰাই;
                }

                data->shm_info.readOnly = False;
                data->shm_info.shmaddr = data->image->data = (ৱর্ণ *)shmat(data->shm_info.shmid, রিক্ত, 0);
                যদি (((signed ৱর্ণ *)data->shm_info.shmaddr) == (signed ৱর্ণ *)-1) {
                    XDestroyImage(data->image);
                    data->shm = false;
                    data->image = রিক্ত;
                    ঘূৰাই;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11Toolkit_SharedMemoryErrorHandler);
                X11_XShmAttach(data->display, &data->shm_info);
                X11_XSync(data->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                যদি (g_shm_error) {
                    XDestroyImage(data->image);
                    shmdt(data->shm_info.shmaddr);
                    shmctl(data->shm_info.shmid, IPC_RMID, রিক্ত);
                    data->image = রিক্ত;
                    data->shm = false;
                    ঘূৰাই;
                }

                যদি (data->shm_pixmap) {
                    data->drawable = X11_XShmCreatePixmap(data->display, data->window, data->shm_info.shmaddr, &data->shm_info, data->pixmap_width, data->pixmap_height, data->depth);
                    যদি (data->drawable == None) {
                        data->shm_pixmap = False;
                    } অন্যথা {
                        XDestroyImage(data->image);
                        data->image = রিক্ত;
                    }
                }

                shmctl(data->shm_info.shmid, IPC_RMID, রিক্ত);
            } অন্যথা {
                data->shm = false;
            }
        }
#endif
    }
}

স্থির শূন্য X11Toolkit_InitWindowFonts(SDL_ToolkitWindowX11 *window)
{    
    window->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    window->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#ifdef X_HAVE_UTF8_STRING
    window->utf8 = true;
    window->font_set = রিক্ত;
    যদি (SDL_X11_HAVE_UTF8) {
        ৱর্ণ **missing = রিক্ত;
        পূর্ণাঙ্ক অঙ্ক_missing = 0;
        পূর্ণাঙ্ক i_font;
        window->font_struct = রিক্ত;
        বাবে (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            ৱর্ণ *font;

            যদি (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_load_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_SIZE * window->iscale);
                window->font_set = X11_XCreateFontSet(window->display, font, &missing, &অঙ্ক_missing, রিক্ত);
                SDL_free(font);

                যদি (!window->font_set) {
                    যদি (window->scale != 0 && window->iscale > 0) {
                        window->iscale = (পূর্ণাঙ্ক)SDL_ceilf(window->scale);
                        window->scale = 0;
                    } অন্যথা {
                        window->iscale--;
                    }
                    গচ্ছ try_load_font;
                }
            } অন্যথা {
                window->font_set = X11_XCreateFontSet(window->display, g_ToolkitFont[i_font], &missing, &অঙ্ক_missing, রিক্ত);
            }

            যদি (missing) {
                X11_XFreeStringList(missing);
            }

            যদি (window->font_set) {
                ভঙ্গ;
            }
        }

        যদি (!window->font_set) {
            গচ্ছ load_font_traditional;
        } অন্যথা {
            XFontStruct **font_structs;
            ৱর্ণ **font_names;
            পূর্ণাঙ্ক font_sz;
            পূর্ণাঙ্ক i;
            
#ifdef HAVE_FRIBIDI_H
            window->do_shaping = !X11_XContextDependentDrawing(window->font_set);
#endif
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFontsOfFontSet(window->font_set, &font_structs, &font_names);
            বাবে (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                যদি (SDL_strstr(font_names[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } অন্যথা যদি (SDL_strstr(font_names[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } অন্যথা যদি (SDL_strstr(font_names[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } অন্যথা যদি (SDL_strstr(font_names[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } অন্যথা যদি (SDL_strstr(font_names[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                যদি (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(window->display, font_names[i]);
                    যদি (font_struct) {
                        যদি (font_struct->per_char) {
                            পূর্ণাঙ্ক glyphs_sz;
                            পূর্ণাঙ্ক j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            বাবে (j = 0; j < glyphs_sz; j++) {
                                যদি (font_struct->per_char[j].lbearing < 0) {
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
    } অন্যথা
#endif
    {
        ৱর্ণ *font;

        load_font_traditional:
        window->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        window->font_struct = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        যদি (!window->font_struct) {
            যদি (window->iscale > 0) {
                যদি (window->scale != 0) {
                    window->iscale = (পূর্ণাঙ্ক)SDL_ceilf(window->scale);
                    window->scale = 0;
                } অন্যথা {
                    window->iscale--;
                }
                গচ্ছ load_font_traditional;
            } অন্যথা {
                window->font_struct = X11_XLoadQueryFont(window->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

স্থির শূন্য X11Toolkit_SettingsNotify(ধ্রুৱ ৱর্ণ *name, XSettingsAction action, XSettingsSetting *setting, শূন্য *data)
{
    SDL_ToolkitWindowX11 *window;
    পূর্ণাঙ্ক i;

    window = data;

    যদি (window->xsettings_first_time) {
        ঘূৰাই;
    }

    যদি (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_setup = false;
        bool pixmap_already_setup = false;

        যদি (window->pixmap) {
            pixmap_already_setup = true;
        } অন্যথা {
            dbe_already_setup = true;
        }

        /* set scale vars */
        window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
        window->iscale = (পূর্ণাঙ্ক)SDL_ceilf(window->scale);
        যদি (window->scale < 1) {
            window->scale = 1;
        }
        যদি (SDL_roundf(window->scale) == window->scale) {
            window->scale = 0;
        }

        /* setup fonts */
#ifdef X_HAVE_UTF8_STRING
        যদি (window->font_set) {
            X11_XFreeFontSet(window->display, window->font_set);
        }
#endif
        যদি (window->font_struct) {
            X11_XFreeFont(window->display, window->font_struct);
        }

        X11Toolkit_InitWindowFonts(window);

        /* set up window */
        যদি (window->scale != 0) {
            window->window_width = SDL_lroundf((window->window_width/window->iscale) * window->scale);
            window->window_height = SDL_lroundf((window->window_height/window->iscale) * window->scale);
            window->pixmap_width = window->window_width;
            window->pixmap_height = window->window_height;
            window->pixmap = true;
        } অন্যথা {
            window->pixmap = false;
        }

        যদি (window->pixmap) {
            যদি (!pixmap_already_setup) {
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                যদি (SDL_X11_HAVE_XDBE && window->xdbe) {
                    X11_XdbeDeallocateBackBufferName(window->display, window->buf);
                }
#endif
            }
            X11_XFreePixmap(window->display, window->drawable);
            X11Toolkit_InitWindowPixmap(window);
        } অন্যথা {
            যদি (!dbe_already_setup) {
                X11_XFreePixmap(window->display, window->drawable);
#ifndef NO_SHARED_MEMORY
                যদি (window->image) {
                    XDestroyImage(window->image);
                    window->image = রিক্ত;
                }
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                যদি (SDL_X11_HAVE_XDBE && window->xdbe) {
                    window->buf = X11_XdbeAllocateBackBufferName(window->display, window->window, XdbeUndefined);
                    window->drawable = window->buf;
                }
#endif
            }
        }

        /* notify controls */
        বাবে (i = 0; i < window->controls_sz; i++) {
            window->controls[i]->do_size = true;

            যদি (window->controls[i]->func_on_scale_change) {
                window->controls[i]->func_on_scale_change(window->controls[i]);
            }

            যদি (window->controls[i]->func_calc_size) {
                window->controls[i]->func_calc_size(window->controls[i]);
            }

            window->controls[i]->do_size = false;
        }

        /* notify cb */
        যদি (window->cb_on_scale_change) {
            window->cb_on_scale_change(window, window->cb_data);
        }

        /* update ev scales */
        যদি (!window->pixmap) {
            window->ev_scale = window->ev_iscale = 1;
        } অন্যথা {
            window->ev_scale = window->scale;
            window->ev_iscale = window->iscale;
        }
    }
}

স্থির শূন্য X11Toolkit_GetTextWidthHeightForFont(XFontStruct *font, ধ্রুৱ ৱর্ণ *str, পূর্ণাঙ্ক nbytes, পূর্ণাঙ্ক *pwidth, পূর্ণাঙ্ক *pheight, পূর্ণাঙ্ক *ascent, পূর্ণাঙ্ক *font_height)
{
    XCharStruct text_structure;
    পূর্ণাঙ্ক font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &text_structure);
    *pwidth = text_structure.width;
    *pheight = text_structure.ascent + text_structure.descent;
    *ascent = text_structure.ascent;
    যদি (font_height) {
       *font_height = font_ascent + font_descent;
    }
}

স্থির শূন্য X11Toolkit_GetTextWidthHeight(SDL_ToolkitWindowX11 *data, ধ্রুৱ ৱর্ণ *str, পূর্ণাঙ্ক nbytes, পূর্ণাঙ্ক *pwidth, পূর্ণাঙ্ক *pheight, পূর্ণাঙ্ক *ascent, পূর্ণাঙ্ক *descent, পূর্ণাঙ্ক *font_height)
{
#ifdef X_HAVE_UTF8_STRING
    যদি (data->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8TextExtents(data->font_set, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.width;
        *pheight = overall_logical.height;
        *ascent = -overall_logical.y;
        *descent = overall_logical.height - *ascent;

        যদি (font_height) {
            XFontSetExtents *extents;

            extents = X11_XExtentsOfFontSet(data->font_set);
            *font_height = extents->max_logical_extent.height;
        }
    } অন্যথা
#endif
    {
        XCharStruct text_structure;
        পূর্ণাঙ্ক font_direction, font_ascent, font_descent;
        X11_XTextExtents(data->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &text_structure);
        *pwidth = text_structure.width;
        *pheight = text_structure.ascent + text_structure.descent;
        *ascent = text_structure.ascent;
        *descent = text_structure.descent;

        যদি (font_height) {
            *font_height = font_ascent + font_descent;
        }
    }
}

#ifdef HAVE_FRIBIDI_H
SDL_List_গ্ৰন্থি *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, ৱর্ণ *txt, size_t sz, FriBidiParType *par)
#অন্যথা
SDL_List_গ্ৰন্থি *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, ৱর্ণ *txt, size_t sz)
#endif
{
    SDL_List_গ্ৰন্থি *list;
    ৱর্ণ *str;
    ৱর্ণ *buffer;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = রিক্ত;
    thai = 0;
    str = txt;
    buffer = SDL_malloc(1);
    buffer[0] = 0;
    
#ifdef HAVE_FRIBIDI_H
    যদি (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    যদি (data->fribidi) {
        ৱর্ণ *fstr;
                
        fstr = SDL_FriBidi_Process(data->fribidi, str, sz, data->do_shaping, par);
        যদি (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#endif        

    যেতিয়ালৈ (1) {
        ৱর্ণ *new;
        ৱর্ণ utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_StepUTF8((ধ্রুৱ ৱর্ণ **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        যদি (cp == 0 || cond == (thai ? false : true)) {
            SDL_ToolkitTextElementX11 *element;
            
            element = SDL_malloc(পরিমাণ(SDL_ToolkitTextElementX11));
            যদি (thai) {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_THAI;
            } অন্যথা {
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

        যদি (!cp) {
            ভঙ্গ;
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
    যদি (free_txt) {
        SDL_free(txt);
    }
    ঘূৰাই list;
}

শূন্য X11Toolkit_ShapeTextElements(SDL_ToolkitWindowX11 *data, SDL_List_গ্ৰন্থি *list)
{
    SDL_List_গ্ৰন্থি *cursor;
    SDL_ToolkitTextElementX11 *prev;
    পূর্ণাঙ্ক temp;
    
    /* Shape and calculate bounding box */
    cursor = list;
    যেতিয়ালৈ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
#ifdef HAVE_LIBTHAI_H
        element->thai_overlays = রিক্ত;
#endif
        যদি (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            যদি (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, রিক্ত);
            } অন্যথা {
#ifdef HAVE_LIBTHAI_H
                যদি (data->th) {
                    সংরচনা thcell_t *cells;
                    ৱর্ণ *tis_str;
                    ৱর্ণ *base_tis_str;
                    size_t cells_sz;
                    size_t base_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, পরিমাণ(সংরচনা thcell_t));
                    data->th->make_cells((ধ্রুৱ thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    base_tis_str_sz = cells_sz;
                    base_tis_str = SDL_malloc(base_tis_str_sz + 1);
                    বাবে (temp = 0; temp < cells_sz; temp++) {
                        base_tis_str[temp] = cells[temp].base;
                        
                        যদি (cells[temp].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            ৱর্ণ *pre;
                            পূর্ণাঙ্ক temp2;
                            
                            overlay = SDL_malloc(পরিমাণ(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ধ্রুৱ ৱর্ণ *)&cells[temp].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->শীৰ্ষ = false;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, রিক্ত);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, রিক্ত);
                            SDL_ListAdd(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        যদি (cells[temp].শীৰ্ষ) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            ৱর্ণ *pre;
                            পূর্ণাঙ্ক temp2;
                            
                            overlay = SDL_malloc(পরিমাণ(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ধ্রুৱ ৱর্ণ *)&cells[temp].শীৰ্ষ, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->শীৰ্ষ = true;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, রিক্ত);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, রিক্ত);
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
#অন্যথা
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
#endif            
            }
        } অন্যথা {
            X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
        }
        
        cursor = cursor->next;
    }
    
    /* Add offsets */
    prev = রিক্ত;
    cursor = list;
    যেতিয়ালৈ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;        
        যদি (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } অন্যথা {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->next;
    }
}


শূন্য X11Toolkit_DrawTextElements(SDL_ToolkitWindowX11 *data, SDL_List_গ্ৰন্থি *list, পূর্ণাঙ্ক x, পূর্ণাঙ্ক y)
{
    SDL_List_গ্ৰন্থি *cursor;
    
    cursor = list;
    
    যেতিয়ালৈ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        যদি (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            যদি (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
#ifdef X_HAVE_UTF8_STRING
                যদি (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } অন্যথা
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } অন্যথা {    
#ifdef HAVE_LIBTHAI_H
                SDL_List_গ্ৰন্থি *overlay_cursor;
                    
                /* Draw the base string */
#ifdef X_HAVE_UTF8_STRING
                যদি (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } অন্যথা
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                যেতিয়ালৈ (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->entry;
#ifdef X_HAVE_UTF8_STRING
                    যদি (data->utf8) {
                        X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } অন্যথা
#endif
                    {
                        X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->next;
                }
#endif                
            }
        } অন্যথা {
#ifdef X_HAVE_UTF8_STRING
            যদি (data->utf8) {
                X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } অন্যথা
#endif
            {
                X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->next;
    }
}

পূর্ণাঙ্ক X11Toolkit_GetTextElementsRect(SDL_List_গ্ৰন্থি *list, SDL_Rect *out)
{
    SDL_List_গ্ৰন্থি *cursor;
    পূর্ণাঙ্ক ret;
    
    ret = 0;
    out->x = out->y = 0;
    out->w = out->h = 0;
    cursor = list;
    যেতিয়ালৈ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        
        out->w += element->rect.w;
        out->h = SDL_max(out->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->next;
    }
    
    ঘূৰাই ret;
}

শূন্য X11Toolkit_FreeTextElementsListContents(SDL_List_গ্ৰন্থি *list)
{
    SDL_List_গ্ৰন্থি *cursor;
    
    cursor = list;
    যেতিয়ালৈ (cursor) {
        SDL_ToolkitTextElementX11 *element;
#ifdef HAVE_LIBTHAI_H
        SDL_List_গ্ৰন্থি *overlay_cursor;
#endif

        element = cursor->entry;
        
        যদি (element->str_free) {
            element->str_free(element->str);
        }
        
#ifdef HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        যেতিয়ালৈ (overlay_cursor) {
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
 
স্থির bool X11Toolkit_ShouldFlipUI(শূন্য) 
{
    SDL_Locale **current_locales;
    স্থির ধ্রুৱ SDL_Locale rtl_locales[] = {
        { "ar", রিক্ত, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", রিক্ত, },
        { "iw", রিক্ত, },
        { "yi", রিক্ত, },
        { "ur", রিক্ত, },
        { "ug", রিক্ত, },
        { "kd", রিক্ত, },
        { "pk", "PK", },
        { "ps", রিক্ত, }
    }; 
    পূর্ণাঙ্ক current_locales_sz;
    পূর্ণাঙ্ক i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    যদি (current_locales_sz <= 0) {
        ঘূৰাই false;        
    }
    বাবে (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        যদি (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            যদি (!rtl_locales[i].country) {
                ঘূৰাই true;
            } অন্যথা {
                ঘূৰাই SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    ঘূৰাই false;
}

SDL_ToolkitWindowX11 *X11Toolkit_CreateWindowStruct(SDL_Window *parent, SDL_ToolkitWindowX11 *tkparent, SDL_ToolkitWindowModeX11 mode, ধ্রুৱ SDL_MessageBoxColor *colorhints, bool create_new_display)
{
    SDL_ToolkitWindowX11 *window;
    পূর্ণাঙ্ক i;
#ifdef SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#endif
    #define ErrorFreeRetNull(x, y) SDL_SetError(x); SDL_free(y); ঘূৰাই রিক্ত
    #define ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_SetError(x, y); SDL_free(z); ঘূৰাই রিক্ত

    যদি (!SDL_X11_LoadSymbols()) {
        ঘূৰাই রিক্ত;
    }

    // This code could get called from multiple threads maybe?
    X11_XInitThreads();

    window = (SDL_ToolkitWindowX11 *)SDL_malloc(পরিমাণ(SDL_ToolkitWindowX11));
    যদি (!window) {
        SDL_SetError("Unable to allocate toolkit window structure");
        ঘূৰাই রিক্ত;
    }

    window->mode = mode;
    window->tk_parent = tkparent;

#যদি SDL_SET_LOCALE
    যদি (mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        window->origlocale = setlocale(LC_ALL, রিক্ত);
        যদি (window->origlocale) {
            window->origlocale = SDL_strdup(window->origlocale);
            যদি (!window->origlocale) {
                SDL_free(window);
                ঘূৰাই রিক্ত;
            }
            (শূন্য)setlocale(LC_ALL, "");
        }
    }
#endif

    window->parent_device = রিক্ত;
    যদি (create_new_display) {
        window->display = X11_XOpenDisplay(রিক্ত);
        window->display_close = true;
        যদি (!window->display) {
            ErrorFreeRetNull("Couldn't open X11 display", window);
        }
    } অন্যথা {
        যদি (parent) {
            window->parent_device = SDL_GetVideoDevice();
            window->display = window->parent_device->internal->display;
            window->display_close = false;
        } অন্যথা যদি (tkparent) {
            window->display = tkparent->display;
            window->display_close = false;
        } অন্যথা {
            window->display = X11_XOpenDisplay(রিক্ত);
            window->display_close = true;
            যদি (!window->display) {
                ErrorFreeRetNull("Couldn't open X11 display", window);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    পূর্ণাঙ্ক xrandr_event_base, xrandr_error_base;
    window->xrandr = X11_XRRQueryExtension(window->display, &xrandr_event_base, &xrandr_error_base);
#endif

#ifndef NO_SHARED_MEMORY
    window->shm_pixmap = False;
    window->shm = X11_XShmQueryExtension(window->display) ? SDL_X11_HAVE_SHM : false;
    যদি (window->shm) {
        পূর্ণাঙ্ক major;
        পূর্ণাঙ্ক minor;

        X11_XShmQueryVersion(window->display, &major, &minor, &window->shm_pixmap);
        যদি (window->shm_pixmap) {
            যদি (X11_XShmPixmapFormat(window->display) != ZPixmap) {
                window->shm_pixmap = False;
            }
        }
    }
#endif

    /* Scale/Xsettings */
    window->pixmap = false;
    window->xsettings_first_time = true;
    window->xsettings = xsettings_client_new(window->display, DefaultScreen(window->display), X11Toolkit_SettingsNotify, রিক্ত, window);
    window->xsettings_first_time = false;
    window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
    যদি (window->scale < 1) {
        window->scale = 1;
    }
    window->iscale = (পূর্ণাঙ্ক)SDL_ceilf(window->scale);
    যদি (SDL_roundf(window->scale) == window->scale) {
        window->scale = 0;
    }

    /* Fonts */
    X11Toolkit_InitWindowFonts(window);

    /* Color hints */
#ifdef SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    যদি (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#endif

    যদি (!colorhints) {
#ifdef SDL_USE_LIBDBUS
        ৱিকল্প (theme) {
            পক্ষ SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                ভঙ্গ;
#যদি 0
            পক্ষ SDL_SYSTEM_THEME_LIGHT_উপৰেৰ_CONTRAST:
                colorhints = g_default_colors_light_উপৰেৰ_contrast;
                ভঙ্গ;
            পক্ষ SDL_SYSTEM_THEME_DARK_উপৰেৰ_CONTRAST:
                colorhints = g_default_colors_dark_উপৰেৰ_contrast;
                ভঙ্গ;
#endif
            স্ৱভাৱ:
                colorhints = g_default_colors;
        }
#অন্যথা
        colorhints = g_default_colors;
#endif
    }
    window->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    বাবে (i = 0; i < SDL_MESSAGEBOX_COLOR_গুনতি; i++) {
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
    যদি (parent) {
        SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(parent);
        window->screen = displaydata->screen;
    } অন্যথা {
        window->screen = DefaultScreen(window->display);
    }

    /* Visuals */
    যদি (mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        window->visual = parent->internal->visual;
        window->cmap = parent->internal->colormap;
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
        window->depth = window->vi.depth;
    } অন্যথা {
        window->visual = DefaultVisual(window->display, window->screen);
        window->cmap = DefaultColormap(window->display, window->screen);
        window->depth = DefaultDepth(window->display, window->screen);
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
    }

    /* Allocate colors */
    বাবে (i = 0; i < SDL_MESSAGEBOX_COLOR_গুনতি; i++) {
        X11_XAllocColor(window->display, window->cmap, &window->xcolor[i]);
    }
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l1);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l2);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_d);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_pressed);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_disabled_text);

    /* Control list */
    window->has_focus = false;
    window->controls = রিক্ত;
    window->controls_sz = 0;
    window->dyn_controls_sz = 0;
    window->fiddled_control = রিক্ত;
    window->dyn_controls = রিক্ত;

    /* Menu windows */
    window->popup_windows = রিক্ত;

    /* BIDI engine */
#ifdef HAVE_FRIBIDI_H
    window->fribidi = SDL_FriBidi_Create();
#endif

#ifdef HAVE_LIBTHAI_H
    window->th = SDL_LibThai_Create();
#endif
    
    /* Interface direction */
    window->flip_interface = X11Toolkit_ShouldFlipUI();
    
    ঘূৰাই window;
}

স্থির শূন্য X11Toolkit_AddControlToWindow(SDL_ToolkitWindowX11 *window, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    window->controls_sz++;
    যদি (window->controls_sz == 1) {
        window->controls = (সংরচনা SDL_ToolkitControlX11 **)SDL_malloc(পরিমাণ(সংরচনা SDL_ToolkitControlX11 *));
    } অন্যথা {
        window->controls = (সংরচনা SDL_ToolkitControlX11 **)SDL_realloc(window->controls, পরিমাণ(সংরচনা SDL_ToolkitControlX11 *) * window->controls_sz);
    }
    window->controls[window->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    যদি (control->dynamic) {
        window->dyn_controls_sz++;
        যদি (window->dyn_controls_sz == 1) {
            window->dyn_controls = (সংরচনা SDL_ToolkitControlX11 **)SDL_malloc(পরিমাণ(সংরচনা SDL_ToolkitControlX11 *));
        } অন্যথা {
            window->dyn_controls = (সংরচনা SDL_ToolkitControlX11 **)SDL_realloc(window->dyn_controls, পরিমাণ(সংরচনা SDL_ToolkitControlX11 *) * window->dyn_controls_sz);
        }
        window->dyn_controls[window->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    যদি (control->selected) {
        window->focused_control = control;
    }
}

bool X11Toolkit_CreateWindowRes(SDL_ToolkitWindowX11 *data, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h, পূর্ণাঙ্ক cx, পূর্ণাঙ্ক cy, ৱর্ণ *title)
{
    পূর্ণাঙ্ক x, y;
    XSizeHints *sizehints;
    XSetWindowAttributes wnd_attr;
    Atom _NET_WM_WINDOW_TYPE, _NET_WM_WINDOW_TYPE_DIALOG, _NET_WM_WINDOW_TYPE_DROPDOWN_MENU, _NET_WM_WINDOW_TYPE_TOOLTIP;
    SDL_WindowData *windowdata = রিক্ত;
    Display *display = data->display;
    XGCValues ctx_vals;
    Window মূল_win;
    Window parent_win;
    unsigned long gcflags = GCForeground | GCBackground;
    unsigned long valuemask;
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
#ifdef XRANDR_DISABLED_BY_DEFAULT
    ধ্রুৱ bool use_xrandr_by_default = false;
#অন্যথা
    ধ্রুৱ bool use_xrandr_by_default = true;
#endif
#endif

    যদি (data->scale == 0) {
        data->window_width = w;
        data->window_height = h;
    } অন্যথা {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        data->pixmap = true;
    }

    যদি (data->parent) {
        windowdata = data->parent->internal;
    }

    valuemask = CWEventMask | CWColormap;
    data->event_mask = ExposureMask |
                       ButtonPressMask | ButtonReleaseMask | চাবি_Press_Mask | চাবি_Release_Mask |
                       StructureNotifyMask | FocusChangeMask | PointerMotionMask;
    wnd_attr.event_mask = data->event_mask;
    wnd_attr.colormap = data->cmap;
    যদি (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    মূল_win = মূল_Window(display, data->screen);
    যদি (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        parent_win = windowdata->xwindow;
    } অন্যথা {
        parent_win = মূল_win;
    }

    data->window = X11_XCreateWindow(
        display, parent_win,
        0, 0,
        data->window_width, data->window_height,
        0, data->depth, প্ৰবেশ_Output, data->visual,
        valuemask, &wnd_attr);
    যদি (data->window == None) {
        ঘূৰাই SDL_SetError("Couldn't create X window");
    }

    যদি (windowdata && data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
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
                            PropModeReplace, (unsigned ৱর্ণ *)stateatoms, statecount);
    }

    যদি (windowdata && data->mode != SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        X11_XSetTransientForHint(display, data->window, windowdata->xwindow);
    }

    যদি (data->tk_parent) {
        X11_XSetTransientForHint(display, data->window, data->tk_parent->window);
    }

    SDL_X11_SetWindowTitle(display, data->window, title);

    // Let the window manager the type of the window
    যদি (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned ৱর্ণ *)&_NET_WM_WINDOW_TYPE_DIALOG, 1);
    } অন্যথা যদি (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned ৱর্ণ *)&_NET_WM_WINDOW_TYPE_DROPDOWN_MENU, 1);
    } অন্যথা যদি (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned ৱর্ণ *)&_NET_WM_WINDOW_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    data->wm_delete_message = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, data->window, &data->wm_delete_message, 1);
    data->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    যদি (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        x = cx;
        y = cy;
        গচ্ছ MOVEWINDOW;
    }
    যদি (windowdata) {
        XWindowAttributes attrib;
        Window dummy;

        X11_XGetWindowAttributes(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.width - data->window_width) / 2;
        y = attrib.y + (attrib.height - data->window_height) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, মূল_Window(display, data->screen), x, y, &x, &y, &dummy);
    } অন্যথা {
        ধ্রুৱ SDL_VideoDevice *dev = SDL_GetVideoDevice();
        যদি (dev && dev->displays && dev->অঙ্ক_displays > 0) {
            ধ্রুৱ SDL_VideoDisplay *dpy = dev->displays[0];
            ধ্রুৱ SDL_DisplayData *dpydata = dpy->internal;
            x = dpydata->x + ((dpy->current_mode->w - data->window_width) / 2);
            y = dpydata->y + ((dpy->current_mode->h - data->window_height) / 3);
        }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
        অন্যথা যদি (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && data->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_out;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, মূল_win);
            যদি (!screen_res) {
                গচ্ছ NOXRANDR;
            }

            default_out = X11_XRRGetOutputPrimary(display, মূল_win);
            যদি (default_out != None) {
                XRROutputInfo *out_info;

                out_info = X11_XRRGetOutputInfo(display, screen_res, default_out);
                যদি (out_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(out_info);
                    গচ্ছ FIRSTOUTPUTXRANDR;
                }

                যদি (out_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                } অন্যথা যদি (out_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                } অন্যথা {
                    crtc_info = রিক্ত;
                }
                
                যদি (crtc_info) {
                    x = (crtc_info->width - data->window_width) / 2;
                    y = (crtc_info->height - data->window_height) / 3;
                    X11_XRRFreeOutputInfo(out_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } অন্যথা {
                    X11_XRRFreeOutputInfo(out_info);
                    গচ্ছ NOXRANDR;
                }
            } অন্যথা {
                    FIRSTOUTPUTXRANDR:
                    যদি (screen_res->noutput > 0) {
                        XRROutputInfo *out_info;

                        out_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        যদি (!out_info) {
                            গচ্ছ FIRSTCRTCXRANDR;
                        }

                        যদি (out_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                        } অন্যথা যদি (out_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                        } অন্যথা {
                            crtc_info = রিক্ত;
                        }

                        যদি (!crtc_info) {
                            X11_XRRFreeOutputInfo(out_info);
                            গচ্ছ FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeOutputInfo(out_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        গচ্ছ MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    যদি (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        গচ্ছ NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    যদি (crtc_info) {
                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } অন্যথা {
                        X11_XRRFreeScreenResources(screen_res);
                        গচ্ছ NOXRANDR;
                    }
            }
        }
#endif
        অন্যথা {
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
    যদি (sizehints) {
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
    যদি (SDL_X11_HAVE_XDBE && !data->pixmap) {
        পূর্ণাঙ্ক xdbe_major, xdbe_minor;
        যদি (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            data->xdbe = true;
            data->buf = X11_XdbeAllocateBackBufferName(display, data->window, XdbeUndefined);
            data->drawable = data->buf;
        } অন্যথা {
            data->xdbe = false;
        }
    }
#endif

    X11Toolkit_InitWindowPixmap(data);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    যদি (!data->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = data->font_struct->fid;
    }
    data->ctx = X11_XCreateGC(data->display, data->drawable, gcflags, &ctx_vals);
    যদি (data->ctx == None) {
        ঘূৰাই SDL_SetError("Couldn't create graphics context");
    }

    data->close = false;
    data->চাবি_control_esc = data->চাবি_control_enter = রিক্ত;
    যদি (!data->pixmap) {
        data->ev_scale = data->ev_iscale = 1;
    } অন্যথা {
        data->ev_scale = data->scale;
        data->ev_iscale = data->iscale;
    }

#যদি SDL_GRAB
    যদি (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XGrabPointer(display, data->window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
        X11_XGrabKeyboard(display, data->window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
#endif

    ঘূৰাই true;
}

স্থির শূন্য X11Toolkit_DrawWindow(SDL_ToolkitWindowX11 *data) {
    SDL_Rect rect;
    পূর্ণাঙ্ক i;

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    যদি (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeBeginIdiom(data->display);
    }
#endif

    X11_XSetForeground(data->display, data->ctx, data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    যদি (data->pixmap) {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->pixmap_width, data->pixmap_height);
    } অন্যথা {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->window_width, data->window_height);
    }

    বাবে (i = 0; i < data->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = data->controls[i];
        যদি (control) {
            যদি (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    যদি (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        XdbeSwapInfo swap_info;
        swap_info.swap_window = data->window;
        swap_info.swap_action = XdbeUndefined;
        X11_XdbeSwapBuffers(data->display, &swap_info, 1);
        X11_XdbeEndIdiom(data->display);
    }
#endif

    যদি (data->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = data->window_width;
        rect.h = data->window_height;
#ifndef NO_SHARED_MEMORY
        যদি (data->shm) {
            যদি (data->shm_pixmap) {
                X11_XFlush(data->display);
                X11_XSync(data->display, false);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->shm_info.shmaddr, data->shm_bytes_per_সাৰি);
                SDL_BlitSurfaceScaled(scale_surface, রিক্ত, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(data->display, data->drawable, data->window, data->ctx, 0, 0, data->window_width, data->window_height, 0, 0);
            } অন্যথা {
                X11_XShmGetImage(data->display, data->drawable, data->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->image->data, data->image->bytes_per_সাৰি);
                SDL_BlitSurfaceScaled(scale_surface, রিক্ত, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                X11_XShmPutImage(data->display, data->window, data->ctx, data->image, 0, 0, 0, 0, data->window_width, data->window_height, False);
            }
        } অন্যথা
#endif
        {
            XImage *image;

            image = X11_XGetImage(data->display, data->drawable, 0, 0 , data->pixmap_width, data->pixmap_height, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), image->data, image->bytes_per_সাৰি);
            SDL_BlitSurfaceScaled(scale_surface, রিক্ত, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
            X11_XPutImage(data->display, data->window, data->ctx, image, 0, 0, 0, 0, data->window_width, data->window_height);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(data->display);
}

স্থির SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_ToolkitWindowX11 *data, পূর্ণাঙ্ক x, পূর্ণাঙ্ক y)
{
    পূর্ণাঙ্ক i;

    বাবে (i = 0; i < data->controls_sz; i++) {
        SDL_Rect *rect = &data->controls[i]->rect;
        যদি ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            ঘূৰাই data->controls[i];
        }
    }

    ঘূৰাই রিক্ত;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
স্থির Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_ToolkitWindowX11 *data = (SDL_ToolkitWindowX11 *)arg;

    যদি (event->xany.display != data->display) {
        ঘূৰাই False;
    }

    যদি (event->xany.window == data->window) {
        ঘূৰাই True;
    }

    ঘূৰাই False;
}

শূন্য X11Toolkit_ProcessWindowEvents(SDL_ToolkitWindowX11 *data, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    যদি ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        ঘূৰাই;
    }

    data->draw = false;
    data->e = e;

    ৱিকল্প (e->type) {
        পক্ষ Expose:
            data->draw = true;
            ভঙ্গ;
        পক্ষ ClientMessage:
            যদি (e->xclient.message_type == data->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.data.l[0] == data->wm_delete_message) {
                data->close = true;
            }
            ভঙ্গ;
        পক্ষ FocusIn:
            data->has_focus = true;
            ভঙ্গ;
        পক্ষ FocusOut:
            data->has_focus = false;
            যদি (data->fiddled_control) {
                data->fiddled_control->selected = false;
            }
            data->fiddled_control = রিক্ত;
            বাবে (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
            }
            ভঙ্গ;
        পক্ষ MotionNotify:
            যদি (data->has_focus) {
                data->previous_control = data->fiddled_control;
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                যদি (data->previous_control) {
                    data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    যদি (data->previous_control->func_on_state_change) {
                        data->previous_control->func_on_state_change(data->previous_control);
                    }
                    data->draw = true;
                }
                যদি (data->fiddled_control) {
                    যদি (data->fiddled_control->dynamic) {
                        data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        যদি (data->fiddled_control->func_on_state_change) {
                            data->fiddled_control->func_on_state_change(data->fiddled_control);
                        }
                        data->draw = true;
                    } অন্যথা {
                        data->fiddled_control = রিক্ত;
                    }
                }
            }
            ভঙ্গ;
        পক্ষ ButtonPress:
            data->previous_control = data->fiddled_control;
            যদি (data->previous_control) {
                data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                যদি (data->previous_control->func_on_state_change) {
                    data->previous_control->func_on_state_change(data->previous_control);
                }
                data->draw = true;
            }
            যদি (e->xbutton.button == Button1) {
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                যদি (data->fiddled_control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    যদি (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->draw = true;
                }
            }
            ভঙ্গ;
        পক্ষ ButtonRelease:
            যদি (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
                পূর্ণাঙ্ক cx;
                পূর্ণাঙ্ক cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                যদি (cy < 0 || cx < 0) {
                    data->close = true;
                }

                যদি (cy > data->window_height || cx > data->window_width) {
                    data->close = true;
                }
            }

            যদি ((e->xbutton.button == Button1) && (data->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                যদি (data->fiddled_control == control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    যদি (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    data->draw = true;
                }
            }
            ভঙ্গ;
        পক্ষ চাবি_Press:
            data->last_চাবি_pressed = X11_XLookupKeysym(&e->xkey, 0);

            যদি (data->last_চাবি_pressed == XK_Escape) {
                বাবে (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    যদি(data->controls[data->ev_i]->is_default_esc) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->চাবি_control_esc = data->controls[data->ev_i];
                    }
                }
            } অন্যথা যদি ((data->last_চাবি_pressed == XK_Return) || (data->last_চাবি_pressed == XK_KP_Enter)) {
                বাবে (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    যদি(data->controls[data->ev_i]->selected) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->চাবি_control_enter = data->controls[data->ev_i];
                    }
                }
            }
            ভঙ্গ;
        পক্ষ চাবি_Release:
        {
            চাবি_Sym চাবি = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            যদি (চাবি != data->last_চাবি_pressed) {
                ভঙ্গ;
            }

            যদি (চাবি == XK_Escape) {
                যদি (data->চাবি_control_esc) {
                    যদি (data->চাবি_control_esc->func_on_state_change) {
                        data->চাবি_control_esc->func_on_state_change(data->চাবি_control_esc);
                    }
                }
            } অন্যথা যদি ((চাবি == XK_Return) || (চাবি == XK_KP_Enter)) {
                যদি (data->চাবি_control_enter) {
                    যদি (data->চাবি_control_enter->func_on_state_change) {
                        data->চাবি_control_enter->func_on_state_change(data->চাবি_control_enter);
                    }
                }
            } অন্যথা যদি (চাবি == XK_Tab || চাবি == XK_বাম || চাবি == XK_ডান) {
                যদি (data->focused_control) {
                    data->focused_control->selected = false;
                }
                data->draw = true;
                বাবে (data->ev_i = 0; data->ev_i < data->dyn_controls_sz; data->ev_i++) {
                    যদি (data->dyn_controls[data->ev_i] == data->focused_control) {
                        পূর্ণাঙ্ক next_index;

                        যদি (চাবি == XK_বাম) {
                            next_index = data->ev_i - 1;
                        } অন্যথা {
                            next_index = data->ev_i + 1;
                        }
                        যদি ((next_index >= data->dyn_controls_sz) || (next_index < 0)) {
                            যদি (চাবি == XK_ডান || চাবি == XK_বাম) {
                                next_index = data->ev_i;
                            } অন্যথা {
                                next_index = 0;
                            }
                        }
                        data->focused_control = data->dyn_controls[next_index];
                        data->focused_control->selected = true;
                        ভঙ্গ;
                    }
                }
            }
            ভঙ্গ;
        }
    }

    যদি (data->draw) {
        X11Toolkit_DrawWindow(data);
    }
}

শূন্য X11Toolkit_DoWindowEventLoop(SDL_ToolkitWindowX11 *data) {
   যেতিয়ালৈ (!data->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(data->display, &e);
        যদি (data->xsettings) {
            xsettings_client_process_event(data->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(data->display, &e, X11Toolkit_EventTest, (XPointer)data);
        X11Toolkit_ProcessWindowEvents(data, &e);
    }
}


শূন্য X11Toolkit_ResizeWindow(SDL_ToolkitWindowX11 *data, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h) {
    যদি (!data->pixmap) {
        data->window_width = w;
        data->window_height = h;
    } অন্যথা {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        X11_XFreePixmap(data->display, data->drawable);
        X11Toolkit_InitWindowPixmap(data);
    }

    X11_XResizeWindow(data->display, data->window, data->window_width, data->window_height);
}

স্থির শূন্য X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->window->display, icon_control->icon_char_font);
    SDL_free(control);
}

স্থির শূন্য X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->window->iscale;
    control->rect.h -= 2 * control->window->iscale;
    X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + (2 * control->window->iscale), control->rect.y + (2* control->window->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    ৱিকল্প (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        পক্ষ SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                ভঙ্গ;
        পক্ষ SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                ভঙ্গ;
        পক্ষ SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                ভঙ্গ;
    }
    X11_XSetFont(control->window->display, control->window->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    যদি (!control->window->utf8) {
        X11_XSetFont(control->window->display, control->window->ctx, control->window->font_struct->fid);
    }

    control->rect.w += 2 * control->window->iscale;
    control->rect.h += 2 * control->window->iscale;
}

স্থির শূন্য X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    পূর্ণাঙ্ক icon_char_w;
    পূর্ণাঙ্ক icon_wh;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11Toolkit_GetTextWidthHeightForFont(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, রিক্ত);
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

স্থির শূন্য X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    ৱর্ণ *font;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11_XFreeFont(base_control->window->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_SIZE * base_control->window->iscale);
    control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
    SDL_free(font);
    যদি (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * base_control->window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_ToolkitWindowX11 *window, SDL_MessageBoxFlags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    ৱর্ণ *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(পরিমাণ(SDL_ToolkitIconControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    যদি (!control) {
        SDL_SetError("Unable to allocate icon control structure");
        ঘূৰাই রিক্ত;
    }

    /* Fill out struct */
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawIconControl;
    base_control->func_free = X11Toolkit_DestroyIconControl;
    base_control->func_on_state_change = রিক্ত;
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
    যদি (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        যদি (!control->icon_char_font) {
            SDL_free(control);
            ঘূৰাই রিক্ত;
        }
    }

    /* Set colors */
    ৱিকল্প (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    পক্ষ SDL_MESSAGEBOX_ERROR:
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
        ভঙ্গ;
    পক্ষ SDL_MESSAGEBOX_WARNING:
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
        ভঙ্গ;
    পক্ষ SDL_MESSAGEBOX_INFORMATION:
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
        ভঙ্গ;
    স্ৱভাৱ:
        X11_XFreeFont(window->display, control->icon_char_font);
        SDL_free(control);
        ঘূৰাই রিক্ত;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    যদি (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } অন্যথা যদি (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } অন্যথা {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    যদি (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } অন্যথা যদি (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } অন্যথা {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    যদি (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } অন্যথা যদি (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } অন্যথা {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(window->display, window->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(base_control);

    X11Toolkit_AddControlToWindow(window, base_control);
    ঘূৰাই base_control;
}

bool X11Toolkit_NotifyControlOfSizeChange(SDL_ToolkitControlX11 *control) {
    যদি (control->func_calc_size) {
        control->func_calc_size(control);
        ঘূৰাই true;
    } অন্যথা {
        ঘূৰাই false;
    }
}

স্থির শূন্য X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11Toolkit_GetTextElementsRect(button_control->text, &button_control->text_rect);
    যদি (control->do_size) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.h;
    }
    button_control->text_rect.x = (control->rect.w - button_control->text_rect.w)/2;
    button_control->text_rect.y = (control->rect.h - button_control->text_rect.h)/2;
}


স্থির শূন্য X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    /* Draw bevel */
    যদি (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
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
        } অন্যথা {
            যদি (control->selected) {
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
            } অন্যথা {
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

স্থির শূন্য X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    যদি (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_data);
    }
}

স্থির শূন্য X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11Toolkit_FreeTextElements(button_control->text);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_ToolkitWindowX11 *window, ধ্রুৱ SDL_MessageBoxButtonData *data) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *base_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(পরিমাণ(SDL_ToolkitButtonControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    যদি (!control) {
        SDL_SetError("Unable to allocate button control structure");
        ঘূৰাই রিক্ত;
    }
    base_control->window = window;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->func_calc_size = X11Toolkit_CalculateButtonControl;
    base_control->func_draw = X11Toolkit_DrawButtonControl;
    base_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    base_control->func_free = X11Toolkit_DestroyButtonControl;
    base_control->func_on_scale_change = রিক্ত;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = true;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    যদি (data->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        base_control->is_default_esc = true;
    }
    যদি (data->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        base_control->is_default_enter = true;
        base_control->selected = true;
    }
    control->cb = রিক্ত;
    control->data = data;
#ifdef HAVE_FRIBIDI_H
    control->text = X11Toolkit_MakeTextElements(base_control->window, (ৱর্ণ *)control->data->text, SDL_strlen(control->data->text), রিক্ত);
#অন্যথা 
    control->text = X11Toolkit_MakeTextElements(base_control->window, (ৱর্ণ *)control->data->text, SDL_strlen(control->data->text));
#endif
    X11Toolkit_ShapeTextElements(base_control->window, control->text);
    
    base_control->do_size = true;
    X11Toolkit_CalculateButtonControl(base_control);
    base_control->do_size = false;

    X11Toolkit_AddControlToWindow(window, base_control);
    ঘূৰাই base_control;
}

শূন্য X11Toolkit_RegisterCallbackForButtonControl(SDL_ToolkitControlX11 *control, শূন্য *data, শূন্য (*cb)(সংরচনা SDL_ToolkitControlX11 *, শূন্য *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_data = data;
    button_control->cb = cb;
}

ধ্রুৱ SDL_MessageBoxButtonData *X11Toolkit_GetButtonControlData(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    ঘূৰাই button_control->data;
}

শূন্য X11Toolkit_DestroyWindow(SDL_ToolkitWindowX11 *data) {
    পূর্ণাঙ্ক i;

    যদি (!data) {
        ঘূৰাই;
    }

#যদি SDL_GRAB
    যদি (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XUngrabPointer(data->display, CurrentTime);
        X11_XUngrabKeyboard(data->display, CurrentTime);
    }
#endif

    বাবে (i = 0; i < data->controls_sz; i++) {
        যদি (data->controls[i]->func_free) {
            data->controls[i]->func_free(data->controls[i]);
        }
    }
    SDL_free(data->controls);
    SDL_free(data->dyn_controls);

    যদি (data->popup_windows) {
        SDL_ListClear(&data->popup_windows);
    }

    যদি (data->pixmap) {
        X11_XFreePixmap(data->display, data->drawable);
    }

#ifndef NO_SHARED_MEMORY
    যদি (data->pixmap && data->shm) {
        X11_XShmDetach(data->display, &data->shm_info);
        যদি (!data->shm_pixmap) {
            XDestroyImage(data->image);
        }
        shmdt(data->shm_info.shmaddr);
    }
#endif

#ifdef X_HAVE_UTF8_STRING
    যদি (data->font_set) {
        X11_XFreeFontSet(data->display, data->font_set);
        data->font_set = রিক্ত;
    }
#endif

    যদি (data->font_struct) {
        X11_XFreeFont(data->display, data->font_struct);
        data->font_struct = রিক্ত;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    যদি (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeDeallocateBackBufferName(data->display, data->buf);
    }
#endif

    যদি (data->xsettings) {
        xsettings_client_destroy(data->xsettings);
    }

    X11_XFreeGC(data->display, data->ctx);

    যদি (data->display) {
        যদি (data->window != None) {
            X11_XWithdrawWindow(data->display, data->window, data->screen);
            X11_XDestroyWindow(data->display, data->window);
            data->window = None;
        }

        যদি (data->display_close) {
            X11_XCloseDisplay(data->display);
        }
        data->display = রিক্ত;
    }

#যদি SDL_SET_LOCALE
    যদি (data->origlocale && (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG)) {
        (শূন্য)setlocale(LC_ALL, data->origlocale);
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

স্থির পূর্ণাঙ্ক X11_Toolkit_গুনতি_সাৰিগুলি_Of_Text(ধ্রুৱ ৱর্ণ *text)
{
    পূর্ণাঙ্ক result = 0;
    যেতিয়ালৈ (text && *text) {
        ধ্রুৱ ৱর্ণ *lf = SDL_strchr(text, '\n');
        result++; // even without an endline, this counts as a line.
        text = lf ? lf + 1 : রিক্ত;
    }
    ঘূৰাই result;
}

স্থির শূন্য X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    পূর্ণাঙ্ক i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    বাবে (i = 0; i < label_control->sz; i++) {
        X11Toolkit_DrawTextElements(control->window, label_control->সাৰিগুলি[i].text, control->rect.x + label_control->সাৰিগুলি[i].rect.x, control->rect.y + label_control->সাৰিগুলি[i].rect.y);
    }
}

স্থির শূন্য X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    পূর্ণাঙ্ক i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    বাবে (i = 0; i < label_control->sz; i++) {
        X11Toolkit_FreeTextElements(label_control->সাৰিগুলি[i].text);
    }
    SDL_free(label_control->সাৰিগুলি);
    SDL_free(label_control);
}

স্থির শূন্য X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitLabelControlX11 *control;
    পূর্ণাঙ্ক i;

    control = (SDL_ToolkitLabelControlX11 *)base_control;
    
    যদি (base_control->do_size) {
        base_control->rect.w = 0;
        base_control->rect.h = 0;
    }
    
    বাবে (i = 0; i < control->sz; i++) {
        পূর্ণাঙ্ক font_h;
        
        font_h = X11Toolkit_GetTextElementsRect(control->সাৰিগুলি[i].text, &control->সাৰিগুলি[i].rect);
        
        যদি (base_control->do_size) {
            base_control->rect.w = SDL_max(base_control->rect.w, control->সাৰিগুলি[i].rect.w);
        }
        
        যদি (i > 0) {
            control->সাৰিগুলি[i].rect.y = font_h + control->সাৰিগুলি[i - 1].rect.y;
        } অন্যথা {
            control->সাৰিগুলি[i].rect.y = 0;
        }
    }

#ifdef HAVE_FRIBIDI_H
    যদি (base_control->window->fribidi) {
        FriBidiParType first_ndn_dir;
        পূর্ণাঙ্ক last_ndn;
    
        first_ndn_dir = FRIBIDI_PAR_LTR;
        বাবে (i = 0; i < control->sz; i++) {
            যদি (control->সাৰিগুলি[i].par != FRIBIDI_PAR_ON) {
                first_ndn_dir = control->সাৰিগুলি[i].par;
            }
        }

        last_ndn = -1;
        বাবে (i = 0; i < control->sz; i++) {
            ৱিকল্প (control->সাৰিগুলি[i].par) {
                পক্ষ FRIBIDI_PAR_LTR:
                    control->সাৰিগুলি[i].rect.x = 0;
                    last_ndn = i;
                    ভঙ্গ;
                পক্ষ FRIBIDI_PAR_RTL:
                    control->সাৰিগুলি[i].rect.x = base_control->rect.w - control->সাৰিগুলি[i].rect.w;
                    last_ndn = i;
                    ভঙ্গ;
                স্ৱভাৱ:
                    যদি (last_ndn != -1) {
                        যদি (control->সাৰিগুলি[last_ndn].par == FRIBIDI_PAR_RTL) {
                            control->সাৰিগুলি[i].rect.x = base_control->rect.w - control->সাৰিগুলি[i].rect.w;
                        } অন্যথা {
                            control->সাৰিগুলি[i].rect.x = 0;
                        }
                    } অন্যথা {
                        যদি (first_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->সাৰিগুলি[i].rect.x = base_control->rect.w - control->সাৰিগুলি[i].rect.w;
                        } অন্যথা {
                            control->সাৰিগুলি[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#endif
    
    যদি (base_control->do_size && control->sz) {
        base_control->rect.h = control->সাৰিগুলি[control->sz - 1].rect.y + control->সাৰিগুলি[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_ToolkitWindowX11 *window, ৱর্ণ *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    পূর্ণাঙ্ক i;
    
    যদি (!utf8) {
        ঘূৰাই রিক্ত;
    }
 
    যদি (!SDL_strcmp(utf8, "")) {
        ঘূৰাই রিক্ত;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(পরিমাণ(SDL_ToolkitLabelControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    যদি (!control) {
        SDL_SetError("Unable to allocate label control structure");
        ঘূৰাই রিক্ত;
    }
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawLabelControl;
    base_control->func_on_state_change = রিক্ত;
    base_control->func_calc_size = X11Toolkit_CalculateLabelControl;
    base_control->func_free  = X11Toolkit_DestroyLabelControl;
    base_control->func_on_scale_change = রিক্ত;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = false;
    base_control->rect.w = 0;
    base_control->rect.h = 0;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_গুনতি_সাৰিগুলি_Of_Text(utf8);
    control->সাৰিগুলি = SDL_calloc(control->sz, পরিমাণ(SDL_Toolkit_Label_Control_সাৰি_X11));
    বাবে (i = 0; i < control->sz; i++) {
        ধ্রুৱ ৱর্ণ *lf = SDL_strchr(utf8, '\n');
        ধ্রুৱ পূর্ণাঙ্ক length = lf ? (lf - utf8) : SDL_strlen(utf8);
        পূর্ণাঙ্ক sz;
        
        sz = length;
        যদি (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#ifdef HAVE_FRIBIDI_H
        control->সাৰিগুলি[i].text = X11Toolkit_MakeTextElements(base_control->window, (ৱর্ণ *)utf8, sz, &control->সাৰিগুলি[i].par);
#অন্যথা 
        control->সাৰিগুলি[i].text = X11Toolkit_MakeTextElements(base_control->window, (ৱর্ণ *)utf8, sz);
#endif
        X11Toolkit_ShapeTextElements(base_control->window, control->সাৰিগুলি[i].text);

        utf8 += length + 1;
        যদি (!lf) {
            ভঙ্গ;
        }
    }

    base_control->do_size = true;
    X11Toolkit_CalculateLabelControl(base_control);
    base_control->do_size = false;
    X11Toolkit_AddControlToWindow(window, base_control);

    ঘূৰাই base_control;
}

পূর্ণাঙ্ক X11_Toolkit_Get_Label_Control_First_সাৰি_Height(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    ঘূৰাই label_control->সাৰিগুলি[0].rect.h;
}

শূন্য X11Toolkit_SignalWindowClose(SDL_ToolkitWindowX11 *data) {
    data->close = true;
}

#endif // SDL_VIDEO_DRIVER_X11
