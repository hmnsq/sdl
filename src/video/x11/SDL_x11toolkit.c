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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাব "../../SDL_list.h"
#অন্তর্ভাব "SDL_x11video.h"
#ifdef SDL_USE_LIBDBUS
#অন্তর্ভাব "../../core/linux/SDL_system_theme.h"
#endif
#ifdef HAVE_FRIBIDI_H
#অন্তর্ভাব "../../core/unix/SDL_fribidi.h"
#endif
#অন্তর্ভাব "SDL_x11dyn.h"
#অন্তর্ভাব "SDL_x11toolkit.h"
#অন্তর্ভাব "SDL_x11settings.h"
#অন্তর্ভাব "SDL_x11modes.h"
#অন্তর্ভাব "xsettings-client.h"
#অন্তর্ভাব <X11/keysym.h>
#অন্তর্ভাব <locale.h>

#define SDL_SET_LOCALE 1
#define SDL_GRAB 1

প্রকারলেখ গণনা SDL_ToolkitTextTypeX11
{
    SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC,
    SDL_TOOLKIT_TEXT_TYPE_X11_THAI
} SDL_ToolkitTextTypeX11;

#ifdef HAVE_LIBTHAI_H
প্রকারলেখ কাঠামো SDL_ToolkitThaiOverlayX11
{
    bool শীর্ষ;
    অক্ষর *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#endif

প্রকারলেখ কাঠামো SDL_ToolkitTextElementX11
{
    SDL_ToolkitTextTypeX11 type;
    অক্ষর *str;
    size_t sz;
    SDL_Rect rect;
    পূর্ণসংখ্যা font_h;
    শূন্য (*str_free)(শূন্য *);
#ifdef HAVE_LIBTHAI_H
    SDL_List_গ্রন্থি *thai_overlays;
#endif
} SDL_ToolkitTextElementX11;

প্রকারলেখ কাঠামো SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Icon type */
    SDL_MessageBoxFlags flags;
    অক্ষর icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    পূর্ণসংখ্যা icon_char_x;
    পূর্ণসংখ্যা icon_char_y;
    পূর্ণসংখ্যা icon_char_a;
    পূর্ণসংখ্যা icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

প্রকারলেখ কাঠামো SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 parent;

    /*তথ্য*/
    ধ্রুবক SDL_Message_Box_Button_তথ্য *তথ্য;

    /* Text */
    SDL_List_গ্রন্থি *text;
    SDL_Rect text_rect;
    
    /* Callback */
    শূন্য *cb_তথ্য;
    শূন্য (*cb)(কাঠামো SDL_ToolkitControlX11 *, শূন্য *);
} SDL_ToolkitButtonControlX11;

প্রকারলেখ কাঠামো SDL_Toolkit_Label_Control_সারি_X11
{
    SDL_List_গ্রন্থি *text;
    SDL_Rect rect;
#ifdef HAVE_FRIBIDI_H
    FriBidiParType par;
#endif
} SDL_Toolkit_Label_Control_সারি_X11;

প্রকারলেখ কাঠামো SDL_ToolkitLabelControlX11
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
    SDL_Toolkit_Label_Control_সারি_X11 *সারিগুলি;
    size_t sz;
} SDL_ToolkitLabelControlX11;

প্রকারলেখ কাঠামো SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_গ্রন্থি *menu_বস্তুসমূহ;
} SDL_ToolkitMenuBarControlX11;

প্রকারলেখ কাঠামো SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_গ্রন্থি *menu_বস্তুসমূহ;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
স্থির ধ্রুবক অক্ষর *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#define G_ICONFONT_আকার 22

/* General UI font */
স্থির ধ্রুবক অক্ষর g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
স্থির ধ্রুবক অক্ষর g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

স্থির ধ্রুবক অক্ষর *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    ফাঁকা
};
#define G_TOOLKITFONT_আকার 140

স্থির ধ্রুবক SDL_MessageBoxColor g_default_colors[SDL_MESSAGEBOX_COLOR_গুনতি] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ifdef SDL_USE_LIBDBUS
স্থির ধ্রুবক SDL_MessageBoxColor g_default_colors_dark[SDL_MESSAGEBOX_COLOR_গুনতি] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#যদি 0
স্থির ধ্রুবক SDL_MessageBoxColor g_default_colors_dark_উপরের_contrast[SDL_MESSAGEBOX_COLOR_গুনতি] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

স্থির ধ্রুবক SDL_MessageBoxColor g_default_colors_light_উপরের_contrast[SDL_MESSAGEBOX_COLOR_গুনতি] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#endif

#endif

স্থির পূর্ণসংখ্যা g_shm_error;
স্থির পূর্ণসংখ্যা (*g_old_error_handler)(Display *, XErrorEvent *) = ফাঁকা;

স্থির পূর্ণসংখ্যা X11Toolkit_SharedMemoryErrorHandler(Display *d, XErrorEvent *e)
{
    যদি (e->error_code == BadAccess || e->error_code == BadRequest) {
        g_shm_error = True;
        ফেরত 0;
    }
    ফেরত g_old_error_handler(d, e);
}

স্থির শূন্য X11Toolkit_InitWindowPixmap(SDL_ToolkitWindowX11 *তথ্য) {
    যদি (তথ্য->pixmap) {
#ifndef NO_SHARED_MEMORY
        যদি (!তথ্য->shm_pixmap) {
            তথ্য->drawable = X11_XCreatePixmap(তথ্য->display, তথ্য->window, তথ্য->pixmap_width, তথ্য->pixmap_height, তথ্য->depth);
        }
#অন্যথা
        তথ্য->drawable = X11_XCreatePixmap(তথ্য->display, তথ্য->window, তথ্য->pixmap_width, তথ্য->pixmap_height, তথ্য->depth);
#endif
#ifndef NO_SHARED_MEMORY
        যদি (তথ্য->shm) {
            তথ্য->image = X11_XShmCreateImage(তথ্য->display, তথ্য->visual, তথ্য->depth, ZPixmap, ফাঁকা, &তথ্য->shm_info, তথ্য->pixmap_width, তথ্য->pixmap_height);
            যদি (তথ্য->image) {
                তথ্য->shm_bytes_per_সারি = তথ্য->image->bytes_per_সারি;

                তথ্য->shm_info.shmid = shmget(IPC_PRIVATE, তথ্য->image->bytes_per_সারি * তথ্য->image->height, IPC_CREAT | 0777);
                যদি (তথ্য->shm_info.shmid < 0) {
                    XDestroyImage(তথ্য->image);
                    তথ্য->image = ফাঁকা;
                    তথ্য->shm = false;
                    ফেরত;
                }

                তথ্য->shm_info.readOnly = False;
                তথ্য->shm_info.shmaddr = তথ্য->image->তথ্য = (অক্ষর *)shmat(তথ্য->shm_info.shmid, ফাঁকা, 0);
                যদি (((signed অক্ষর *)তথ্য->shm_info.shmaddr) == (signed অক্ষর *)-1) {
                    XDestroyImage(তথ্য->image);
                    তথ্য->shm = false;
                    তথ্য->image = ফাঁকা;
                    ফেরত;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11Toolkit_SharedMemoryErrorHandler);
                X11_XShmAttach(তথ্য->display, &তথ্য->shm_info);
                X11_XSync(তথ্য->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                যদি (g_shm_error) {
                    XDestroyImage(তথ্য->image);
                    shmdt(তথ্য->shm_info.shmaddr);
                    shmctl(তথ্য->shm_info.shmid, IPC_RMID, ফাঁকা);
                    তথ্য->image = ফাঁকা;
                    তথ্য->shm = false;
                    ফেরত;
                }

                যদি (তথ্য->shm_pixmap) {
                    তথ্য->drawable = X11_XShmCreatePixmap(তথ্য->display, তথ্য->window, তথ্য->shm_info.shmaddr, &তথ্য->shm_info, তথ্য->pixmap_width, তথ্য->pixmap_height, তথ্য->depth);
                    যদি (তথ্য->drawable == None) {
                        তথ্য->shm_pixmap = False;
                    } অন্যথা {
                        XDestroyImage(তথ্য->image);
                        তথ্য->image = ফাঁকা;
                    }
                }

                shmctl(তথ্য->shm_info.shmid, IPC_RMID, ফাঁকা);
            } অন্যথা {
                তথ্য->shm = false;
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
    window->font_set = ফাঁকা;
    যদি (SDL_X11_HAVE_UTF8) {
        অক্ষর **missing = ফাঁকা;
        পূর্ণসংখ্যা অঙ্ক_missing = 0;
        পূর্ণসংখ্যা i_font;
        window->font_struct = ফাঁকা;
        জন্য (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            অক্ষর *font;

            যদি (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_load_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_আকার * window->iscale);
                window->font_set = X11_XCreateFontSet(window->display, font, &missing, &অঙ্ক_missing, ফাঁকা);
                SDL_free(font);

                যদি (!window->font_set) {
                    যদি (window->scale != 0 && window->iscale > 0) {
                        window->iscale = (পূর্ণসংখ্যা)SDL_ceilf(window->scale);
                        window->scale = 0;
                    } অন্যথা {
                        window->iscale--;
                    }
                    যাও try_load_font;
                }
            } অন্যথা {
                window->font_set = X11_XCreateFontSet(window->display, g_ToolkitFont[i_font], &missing, &অঙ্ক_missing, ফাঁকা);
            }

            যদি (missing) {
                X11_XFreeStringList(missing);
            }

            যদি (window->font_set) {
                বিরতি;
            }
        }

        যদি (!window->font_set) {
            যাও load_font_traditional;
        } অন্যথা {
            XFontStruct **font_structs;
            অক্ষর **font_names;
            পূর্ণসংখ্যা font_sz;
            পূর্ণসংখ্যা i;
            
#ifdef HAVE_FRIBIDI_H
            window->do_shaping = !X11_XContextDependentDrawing(window->font_set);
#endif
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFontsOfFontSet(window->font_set, &font_structs, &font_names);
            জন্য (i = 0; i < font_sz; i++) {
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
                            পূর্ণসংখ্যা glyphs_sz;
                            পূর্ণসংখ্যা j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            জন্য (j = 0; j < glyphs_sz; j++) {
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
        অক্ষর *font;

        load_font_traditional:
        window->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_আকার * window->iscale);
        window->font_struct = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        যদি (!window->font_struct) {
            যদি (window->iscale > 0) {
                যদি (window->scale != 0) {
                    window->iscale = (পূর্ণসংখ্যা)SDL_ceilf(window->scale);
                    window->scale = 0;
                } অন্যথা {
                    window->iscale--;
                }
                যাও load_font_traditional;
            } অন্যথা {
                window->font_struct = X11_XLoadQueryFont(window->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

স্থির শূন্য X11Toolkit_SettingsNotify(ধ্রুবক অক্ষর *name, XSettingsAction action, XSettingsSetting *setting, শূন্য *তথ্য)
{
    SDL_ToolkitWindowX11 *window;
    পূর্ণসংখ্যা i;

    window = তথ্য;

    যদি (window->xsettings_first_time) {
        ফেরত;
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
        window->iscale = (পূর্ণসংখ্যা)SDL_ceilf(window->scale);
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
                    X11_Xdbe_Deallocate_Back_বাফার_Name(window->display, window->buf);
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
                    window->image = ফাঁকা;
                }
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                যদি (SDL_X11_HAVE_XDBE && window->xdbe) {
                    window->buf = X11_Xdbe_Allocate_Back_বাফার_Name(window->display, window->window, XdbeUndefined);
                    window->drawable = window->buf;
                }
#endif
            }
        }

        /* notify controls */
        জন্য (i = 0; i < window->controls_sz; i++) {
            window->controls[i]->do_আকার = true;

            যদি (window->controls[i]->func_on_scale_change) {
                window->controls[i]->func_on_scale_change(window->controls[i]);
            }

            যদি (window->controls[i]->func_calc_আকার) {
                window->controls[i]->func_calc_আকার(window->controls[i]);
            }

            window->controls[i]->do_আকার = false;
        }

        /* notify cb */
        যদি (window->cb_on_scale_change) {
            window->cb_on_scale_change(window, window->cb_তথ্য);
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

স্থির শূন্য X11Toolkit_GetTextWidthHeightForFont(XFontStruct *font, ধ্রুবক অক্ষর *str, পূর্ণসংখ্যা nbytes, পূর্ণসংখ্যা *pwidth, পূর্ণসংখ্যা *pheight, পূর্ণসংখ্যা *ascent, পূর্ণসংখ্যা *font_height)
{
    XCharStruct text_structure;
    পূর্ণসংখ্যা font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &text_structure);
    *pwidth = text_structure.width;
    *pheight = text_structure.ascent + text_structure.descent;
    *ascent = text_structure.ascent;
    যদি (font_height) {
       *font_height = font_ascent + font_descent;
    }
}

স্থির শূন্য X11Toolkit_GetTextWidthHeight(SDL_ToolkitWindowX11 *তথ্য, ধ্রুবক অক্ষর *str, পূর্ণসংখ্যা nbytes, পূর্ণসংখ্যা *pwidth, পূর্ণসংখ্যা *pheight, পূর্ণসংখ্যা *ascent, পূর্ণসংখ্যা *descent, পূর্ণসংখ্যা *font_height)
{
#ifdef X_HAVE_UTF8_STRING
    যদি (তথ্য->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8TextExtents(তথ্য->font_set, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.width;
        *pheight = overall_logical.height;
        *ascent = -overall_logical.y;
        *descent = overall_logical.height - *ascent;

        যদি (font_height) {
            XFontSetExtents *extents;

            extents = X11_XExtentsOfFontSet(তথ্য->font_set);
            *font_height = extents->max_logical_extent.height;
        }
    } অন্যথা
#endif
    {
        XCharStruct text_structure;
        পূর্ণসংখ্যা font_direction, font_ascent, font_descent;
        X11_XTextExtents(তথ্য->font_struct, str, nbytes,
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
SDL_List_গ্রন্থি *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *তথ্য, অক্ষর *txt, size_t sz, FriBidiParType *par)
#অন্যথা
SDL_List_গ্রন্থি *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *তথ্য, অক্ষর *txt, size_t sz)
#endif
{
    SDL_List_গ্রন্থি *list;
    অক্ষর *str;
    অক্ষর *বাফার_2;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = ফাঁকা;
    thai = 0;
    str = txt;
    বাফার_2 = SDL_malloc(1);
    বাফার_2[0] = 0;
    
#ifdef HAVE_FRIBIDI_H
    যদি (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    যদি (তথ্য->fribidi) {
        অক্ষর *fstr;
                
        fstr = SDL_FriBidi_Process(তথ্য->fribidi, str, sz, তথ্য->do_shaping, par);
        যদি (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#endif        

    যখন (1) {
        অক্ষর *new;
        অক্ষর utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_StepUTF8((ধ্রুবক অক্ষর **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        যদি (cp == 0 || cond == (thai ? false : true)) {
            SDL_ToolkitTextElementX11 *element;
            
            element = SDL_malloc(আকার(SDL_ToolkitTextElementX11));
            যদি (thai) {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_THAI;
            } অন্যথা {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC;
            }
            element->str = SDL_strdup(বাফার_2);
            element->sz = SDL_strlen(বাফার_2);
            element->str_free = SDL_free;
            
            SDL_ListAdd(&list, element);
            
            SDL_free(বাফার_2);
            বাফার_2 = SDL_malloc(1);
            বাফার_2[0] = 0;
            thai = thai ? false : true;
        }

        যদি (!cp) {
            বিরতি;
        }
        
        SDL_UCS4ToUTF8(cp, utf8);
        csz = SDL_strlen(বাফার_2) + SDL_strlen(utf8) + 1;
        new = SDL_malloc(csz);
        SDL_strlcpy(new, বাফার_2, csz);
        SDL_strlcat(new, utf8, csz);
        SDL_free(বাফার_2);
        বাফার_2 = new;
    }

    SDL_free(বাফার_2);
    যদি (free_txt) {
        SDL_free(txt);
    }
    ফেরত list;
}

শূন্য X11Toolkit_ShapeTextElements(SDL_ToolkitWindowX11 *তথ্য, SDL_List_গ্রন্থি *list)
{
    SDL_List_গ্রন্থি *cursor;
    SDL_ToolkitTextElementX11 *পূর্ব;
    পূর্ণসংখ্যা অস্থায়ী;
    
    /* Shape and calculate bounding box */
    cursor = list;
    যখন (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
#ifdef HAVE_LIBTHAI_H
        element->thai_overlays = ফাঁকা;
#endif
        যদি (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            যদি (তথ্য->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
                X11Toolkit_GetTextWidthHeight(তথ্য, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &অস্থায়ী, ফাঁকা);
            } অন্যথা {
#ifdef HAVE_LIBTHAI_H
                যদি (তথ্য->th) {
                    কাঠামো thcell_t *cells;
                    অক্ষর *tis_str;
                    অক্ষর *base_tis_str;
                    size_t cells_sz;
                    size_t base_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, আকার(কাঠামো thcell_t));
                    তথ্য->th->make_cells((ধ্রুবক thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    base_tis_str_sz = cells_sz;
                    base_tis_str = SDL_malloc(base_tis_str_sz + 1);
                    জন্য (অস্থায়ী = 0; অস্থায়ী < cells_sz; অস্থায়ী++) {
                        base_tis_str[অস্থায়ী] = cells[অস্থায়ী].base;
                        
                        যদি (cells[অস্থায়ী].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            অক্ষর *pre;
                            পূর্ণসংখ্যা temp2;
                            
                            overlay = SDL_malloc(আকার(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, অস্থায়ী);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ধ্রুবক অক্ষর *)&cells[অস্থায়ী].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->শীর্ষ = false;
                            X11Toolkit_GetTextWidthHeight(তথ্য, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ফাঁকা);
                            X11Toolkit_GetTextWidthHeight(তথ্য, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ফাঁকা);
                            SDL_ListAdd(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        যদি (cells[অস্থায়ী].শীর্ষ) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            অক্ষর *pre;
                            পূর্ণসংখ্যা temp2;
                            
                            overlay = SDL_malloc(আকার(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, অস্থায়ী);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ধ্রুবক অক্ষর *)&cells[অস্থায়ী].শীর্ষ, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->শীর্ষ = true;
                            X11Toolkit_GetTextWidthHeight(তথ্য, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ফাঁকা);
                            X11Toolkit_GetTextWidthHeight(তথ্য, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ফাঁকা);
                            SDL_ListAdd(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    base_tis_str[base_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, base_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11Toolkit_GetTextWidthHeight(তথ্য, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &অস্থায়ী, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(base_tis_str);
                }
#অন্যথা
                X11Toolkit_GetTextWidthHeight(তথ্য, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &অস্থায়ী, &element->font_h);
#endif            
            }
        } অন্যথা {
            X11Toolkit_GetTextWidthHeight(তথ্য, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &অস্থায়ী, &element->font_h);
        }
        
        cursor = cursor->পরবর্তী;
    }
    
    /* Add offsets */
    পূর্ব = ফাঁকা;
    cursor = list;
    যখন (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;        
        যদি (পূর্ব) {
            element->rect.x = পূর্ব->rect.x + পূর্ব->rect.w;
        } অন্যথা {
            element->rect.x = 0;
        }
        
        পূর্ব = element;
        cursor = cursor->পরবর্তী;
    }
}


শূন্য X11Toolkit_DrawTextElements(SDL_ToolkitWindowX11 *তথ্য, SDL_List_গ্রন্থি *list, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y)
{
    SDL_List_গ্রন্থি *cursor;
    
    cursor = list;
    
    যখন (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        যদি (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            যদি (তথ্য->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
#ifdef X_HAVE_UTF8_STRING
                যদি (তথ্য->utf8) {
                    X11_Xutf8DrawString(তথ্য->display, তথ্য->drawable, তথ্য->font_set, তথ্য->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } অন্যথা
#endif
                {
                    X11_XDrawString(তথ্য->display, তথ্য->drawable, তথ্য->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } অন্যথা {    
#ifdef HAVE_LIBTHAI_H
                SDL_List_গ্রন্থি *overlay_cursor;
                    
                /* Draw the base string */
#ifdef X_HAVE_UTF8_STRING
                যদি (তথ্য->utf8) {
                    X11_Xutf8DrawString(তথ্য->display, তথ্য->drawable, তথ্য->font_set, তথ্য->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } অন্যথা
#endif
                {
                    X11_XDrawString(তথ্য->display, তথ্য->drawable, তথ্য->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                যখন (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->entry;
#ifdef X_HAVE_UTF8_STRING
                    যদি (তথ্য->utf8) {
                        X11_Xutf8DrawString(তথ্য->display, তথ্য->drawable, তথ্য->font_set, তথ্য->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } অন্যথা
#endif
                    {
                        X11_XDrawString(তথ্য->display, তথ্য->drawable, তথ্য->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->পরবর্তী;
                }
#endif                
            }
        } অন্যথা {
#ifdef X_HAVE_UTF8_STRING
            যদি (তথ্য->utf8) {
                X11_Xutf8DrawString(তথ্য->display, তথ্য->drawable, তথ্য->font_set, তথ্য->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } অন্যথা
#endif
            {
                X11_XDrawString(তথ্য->display, তথ্য->drawable, তথ্য->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->পরবর্তী;
    }
}

পূর্ণসংখ্যা X11Toolkit_GetTextElementsRect(SDL_List_গ্রন্থি *list, SDL_Rect *out)
{
    SDL_List_গ্রন্থি *cursor;
    পূর্ণসংখ্যা ret;
    
    ret = 0;
    out->x = out->y = 0;
    out->w = out->h = 0;
    cursor = list;
    যখন (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        
        out->w += element->rect.w;
        out->h = SDL_max(out->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->পরবর্তী;
    }
    
    ফেরত ret;
}

শূন্য X11Toolkit_FreeTextElementsListContents(SDL_List_গ্রন্থি *list)
{
    SDL_List_গ্রন্থি *cursor;
    
    cursor = list;
    যখন (cursor) {
        SDL_ToolkitTextElementX11 *element;
#ifdef HAVE_LIBTHAI_H
        SDL_List_গ্রন্থি *overlay_cursor;
#endif

        element = cursor->entry;
        
        যদি (element->str_free) {
            element->str_free(element->str);
        }
        
#ifdef HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        যখন (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->entry;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->পরবর্তী;
        }
        SDL_ListClear(&element->thai_overlays);
#endif
        
        SDL_free(element);
        
        cursor = cursor->পরবর্তী;
    }
}

#define X11Toolkit_FreeTextElements(x) X11Toolkit_FreeTextElementsListContents(x); SDL_ListClear(&x)
 
স্থির bool X11Toolkit_ShouldFlipUI(শূন্য) 
{
    SDL_Locale **current_locales;
    স্থির ধ্রুবক SDL_Locale rtl_locales[] = {
        { "ar", ফাঁকা, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", ফাঁকা, },
        { "iw", ফাঁকা, },
        { "yi", ফাঁকা, },
        { "ur", ফাঁকা, },
        { "ug", ফাঁকা, },
        { "kd", ফাঁকা, },
        { "pk", "PK", },
        { "ps", ফাঁকা, }
    }; 
    পূর্ণসংখ্যা current_locales_sz;
    পূর্ণসংখ্যা i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    যদি (current_locales_sz <= 0) {
        ফেরত false;        
    }
    জন্য (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        যদি (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            যদি (!rtl_locales[i].country) {
                ফেরত true;
            } অন্যথা {
                ফেরত SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    ফেরত false;
}

SDL_ToolkitWindowX11 *X11Toolkit_CreateWindowStruct(SDL_Window *parent, SDL_ToolkitWindowX11 *tkparent, SDL_ToolkitWindowModeX11 mode, ধ্রুবক SDL_MessageBoxColor *colorhints, bool create_new_display)
{
    SDL_ToolkitWindowX11 *window;
    পূর্ণসংখ্যা i;
#ifdef SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#endif
    #define ErrorFreeRetNull(x, y) SDL_SetError(x); SDL_free(y); ফেরত ফাঁকা
    #define ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_SetError(x, y); SDL_free(z); ফেরত ফাঁকা

    যদি (!SDL_X11_LoadSymbols()) {
        ফেরত ফাঁকা;
    }

    // This code could get called from multiple threads maybe?
    X11_XInitThreads();

    window = (SDL_ToolkitWindowX11 *)SDL_malloc(আকার(SDL_ToolkitWindowX11));
    যদি (!window) {
        SDL_SetError("Unable to allocate toolkit window structure");
        ফেরত ফাঁকা;
    }

    window->mode = mode;
    window->tk_parent = tkparent;

#যদি SDL_SET_LOCALE
    যদি (mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        window->origlocale = setlocale(LC_ALL, ফাঁকা);
        যদি (window->origlocale) {
            window->origlocale = SDL_strdup(window->origlocale);
            যদি (!window->origlocale) {
                SDL_free(window);
                ফেরত ফাঁকা;
            }
            (শূন্য)setlocale(LC_ALL, "");
        }
    }
#endif

    window->parent_device = ফাঁকা;
    যদি (create_new_display) {
        window->display = X11_XOpenDisplay(ফাঁকা);
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
            window->display = X11_XOpenDisplay(ফাঁকা);
            window->display_close = true;
            যদি (!window->display) {
                ErrorFreeRetNull("Couldn't open X11 display", window);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    পূর্ণসংখ্যা xrandr_event_base, xrandr_error_base;
    window->xrandr = X11_XRRQueryExtension(window->display, &xrandr_event_base, &xrandr_error_base);
#endif

#ifndef NO_SHARED_MEMORY
    window->shm_pixmap = False;
    window->shm = X11_XShmQueryExtension(window->display) ? SDL_X11_HAVE_SHM : false;
    যদি (window->shm) {
        পূর্ণসংখ্যা major;
        পূর্ণসংখ্যা minor;

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
    window->xsettings = xsettings_client_new(window->display, DefaultScreen(window->display), X11Toolkit_SettingsNotify, ফাঁকা, window);
    window->xsettings_first_time = false;
    window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
    যদি (window->scale < 1) {
        window->scale = 1;
    }
    window->iscale = (পূর্ণসংখ্যা)SDL_ceilf(window->scale);
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
        নির্বাচন (theme) {
            ক্ষেত্র SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                বিরতি;
#যদি 0
            ক্ষেত্র SDL_SYSTEM_THEME_LIGHT_উপরের_CONTRAST:
                colorhints = g_default_colors_light_উপরের_contrast;
                বিরতি;
            ক্ষেত্র SDL_SYSTEM_THEME_DARK_উপরের_CONTRAST:
                colorhints = g_default_colors_dark_উপরের_contrast;
                বিরতি;
#endif
            পূর্বনির্ধারিত:
                colorhints = g_default_colors;
        }
#অন্যথা
        colorhints = g_default_colors;
#endif
    }
    window->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    জন্য (i = 0; i < SDL_MESSAGEBOX_COLOR_গুনতি; i++) {
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
        SDL_Display_তথ্য *displaydata = SDL_Get_Display_Driver_তথ্য_For_Window(parent);
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
    জন্য (i = 0; i < SDL_MESSAGEBOX_COLOR_গুনতি; i++) {
        X11_XAllocColor(window->display, window->cmap, &window->xcolor[i]);
    }
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l1);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l2);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_d);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_pressed);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_disabled_text);

    /* Control list */
    window->has_focus = false;
    window->controls = ফাঁকা;
    window->controls_sz = 0;
    window->dyn_controls_sz = 0;
    window->fiddled_control = ফাঁকা;
    window->dyn_controls = ফাঁকা;

    /* Menu windows */
    window->popup_windows = ফাঁকা;

    /* BIDI engine */
#ifdef HAVE_FRIBIDI_H
    window->fribidi = SDL_FriBidi_Create();
#endif

#ifdef HAVE_LIBTHAI_H
    window->th = SDL_LibThai_Create();
#endif
    
    /* Interface direction */
    window->flip_interface = X11Toolkit_ShouldFlipUI();
    
    ফেরত window;
}

স্থির শূন্য X11Toolkit_AddControlToWindow(SDL_ToolkitWindowX11 *window, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    window->controls_sz++;
    যদি (window->controls_sz == 1) {
        window->controls = (কাঠামো SDL_ToolkitControlX11 **)SDL_malloc(আকার(কাঠামো SDL_ToolkitControlX11 *));
    } অন্যথা {
        window->controls = (কাঠামো SDL_ToolkitControlX11 **)SDL_realloc(window->controls, আকার(কাঠামো SDL_ToolkitControlX11 *) * window->controls_sz);
    }
    window->controls[window->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    যদি (control->dynamic) {
        window->dyn_controls_sz++;
        যদি (window->dyn_controls_sz == 1) {
            window->dyn_controls = (কাঠামো SDL_ToolkitControlX11 **)SDL_malloc(আকার(কাঠামো SDL_ToolkitControlX11 *));
        } অন্যথা {
            window->dyn_controls = (কাঠামো SDL_ToolkitControlX11 **)SDL_realloc(window->dyn_controls, আকার(কাঠামো SDL_ToolkitControlX11 *) * window->dyn_controls_sz);
        }
        window->dyn_controls[window->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    যদি (control->selected) {
        window->focused_control = control;
    }
}

bool X11Toolkit_CreateWindowRes(SDL_ToolkitWindowX11 *তথ্য, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, পূর্ণসংখ্যা cx, পূর্ণসংখ্যা cy, অক্ষর *title)
{
    পূর্ণসংখ্যা x, y;
    XSizeHints *sizehints;
    XSetWindowAttributes wnd_attr;
    Atom _NET_WM_WINDOW_TYPE, _NET_WM_WINDOW_TYPE_DIALOG, _NET_WM_WINDOW_TYPE_DROPDOWN_MENU, _NET_WM_WINDOW_TYPE_TOOLTIP;
    SDL_Window_তথ্য *windowdata = ফাঁকা;
    Display *display = তথ্য->display;
    XGCValues ctx_vals;
    Window মূল_win;
    Window parent_win;
    unsigned long gcflags = GCForeground | GCBackground;
    unsigned long valuemask;
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
#ifdef XRANDR_DISABLED_BY_DEFAULT
    ধ্রুবক bool use_xrandr_by_default = false;
#অন্যথা
    ধ্রুবক bool use_xrandr_by_default = true;
#endif
#endif

    যদি (তথ্য->scale == 0) {
        তথ্য->window_width = w;
        তথ্য->window_height = h;
    } অন্যথা {
        তথ্য->window_width = SDL_lroundf((w/তথ্য->iscale) * তথ্য->scale);
        তথ্য->window_height = SDL_lroundf((h/তথ্য->iscale) * তথ্য->scale);
        তথ্য->pixmap_width = w;
        তথ্য->pixmap_height = h;
        তথ্য->pixmap = true;
    }

    যদি (তথ্য->parent) {
        windowdata = তথ্য->parent->internal;
    }

    valuemask = CWEventMask | CWColormap;
    তথ্য->event_mask = ExposureMask |
                       ButtonPressMask | ButtonReleaseMask | চাবি_Press_Mask | চাবি_Release_Mask |
                       StructureNotifyMask | FocusChangeMask | PointerMotionMask;
    wnd_attr.event_mask = তথ্য->event_mask;
    wnd_attr.colormap = তথ্য->cmap;
    যদি (তথ্য->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || তথ্য->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    মূল_win = মূল_Window(display, তথ্য->screen);
    যদি (তথ্য->mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        parent_win = windowdata->xwindow;
    } অন্যথা {
        parent_win = মূল_win;
    }

    তথ্য->window = X11_XCreateWindow(
        display, parent_win,
        0, 0,
        তথ্য->window_width, তথ্য->window_height,
        0, তথ্য->depth, প্রবেশ_Output, তথ্য->visual,
        valuemask, &wnd_attr);
    যদি (তথ্য->window == None) {
        ফেরত SDL_SetError("Couldn't create X window");
    }

    যদি (windowdata && তথ্য->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
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
        X11_XChangeProperty(display, তথ্য->window, _NET_WM_STATE, XA_ATOM, 32,
                            PropModeReplace, (unsigned অক্ষর *)stateatoms, statecount);
    }

    যদি (windowdata && তথ্য->mode != SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        X11_XSetTransientForHint(display, তথ্য->window, windowdata->xwindow);
    }

    যদি (তথ্য->tk_parent) {
        X11_XSetTransientForHint(display, তথ্য->window, তথ্য->tk_parent->window);
    }

    SDL_X11_SetWindowTitle(display, তথ্য->window, title);

    // Let the window manager the type of the window
    যদি (তথ্য->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, তথ্য->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned অক্ষর *)&_NET_WM_WINDOW_TYPE_DIALOG, 1);
    } অন্যথা যদি (তথ্য->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, তথ্য->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned অক্ষর *)&_NET_WM_WINDOW_TYPE_DROPDOWN_MENU, 1);
    } অন্যথা যদি (তথ্য->mode == SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, তথ্য->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned অক্ষর *)&_NET_WM_WINDOW_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    তথ্য->wm_delete_message = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, তথ্য->window, &তথ্য->wm_delete_message, 1);
    তথ্য->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    যদি (তথ্য->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || তথ্য->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        x = cx;
        y = cy;
        যাও MOVEWINDOW;
    }
    যদি (windowdata) {
        XWindowAttributes attrib;
        Window dummy;

        X11_XGetWindowAttributes(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.width - তথ্য->window_width) / 2;
        y = attrib.y + (attrib.height - তথ্য->window_height) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, মূল_Window(display, তথ্য->screen), x, y, &x, &y, &dummy);
    } অন্যথা {
        ধ্রুবক SDL_VideoDevice *dev = SDL_GetVideoDevice();
        যদি (dev && dev->displays && dev->অঙ্ক_displays > 0) {
            ধ্রুবক SDL_VideoDisplay *dpy = dev->displays[0];
            ধ্রুবক SDL_Display_তথ্য *dpydata = dpy->internal;
            x = dpydata->x + ((dpy->current_mode->w - তথ্য->window_width) / 2);
            y = dpydata->y + ((dpy->current_mode->h - তথ্য->window_height) / 3);
        }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
        অন্যথা যদি (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && তথ্য->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_out;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, মূল_win);
            যদি (!screen_res) {
                যাও NOXRANDR;
            }

            default_out = X11_XRRGetOutputPrimary(display, মূল_win);
            যদি (default_out != None) {
                XRROutputInfo *out_info;

                out_info = X11_XRRGetOutputInfo(display, screen_res, default_out);
                যদি (out_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(out_info);
                    যাও FIRSTOUTPUTXRANDR;
                }

                যদি (out_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                } অন্যথা যদি (out_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                } অন্যথা {
                    crtc_info = ফাঁকা;
                }
                
                যদি (crtc_info) {
                    x = (crtc_info->width - তথ্য->window_width) / 2;
                    y = (crtc_info->height - তথ্য->window_height) / 3;
                    X11_XRRFreeOutputInfo(out_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } অন্যথা {
                    X11_XRRFreeOutputInfo(out_info);
                    যাও NOXRANDR;
                }
            } অন্যথা {
                    FIRSTOUTPUTXRANDR:
                    যদি (screen_res->noutput > 0) {
                        XRROutputInfo *out_info;

                        out_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        যদি (!out_info) {
                            যাও FIRSTCRTCXRANDR;
                        }

                        যদি (out_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                        } অন্যথা যদি (out_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                        } অন্যথা {
                            crtc_info = ফাঁকা;
                        }

                        যদি (!crtc_info) {
                            X11_XRRFreeOutputInfo(out_info);
                            যাও FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->width - তথ্য->window_width) / 2;
                        y = (crtc_info->height - তথ্য->window_height) / 3;
                        X11_XRRFreeOutputInfo(out_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        যাও MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    যদি (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        যাও NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    যদি (crtc_info) {
                        x = (crtc_info->width - তথ্য->window_width) / 2;
                        y = (crtc_info->height - তথ্য->window_height) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } অন্যথা {
                        X11_XRRFreeScreenResources(screen_res);
                        যাও NOXRANDR;
                    }
            }
        }
#endif
        অন্যথা {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (DisplayWidth(display, তথ্য->screen) - তথ্য->window_width) / 2;
            y = (DisplayHeight(display, তথ্য->screen) - তথ্য->window_height) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMoveWindow(display, তথ্য->window, x, y);
    তথ্য->window_x = x;
    তথ্য->window_y = y;

    sizehints = X11_XAlloc_আকার_Hints();
    যদি (sizehints) {
        sizehints->flags = USPosition | USSize | PMax_আকার | PMin_আকার;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->width = তথ্য->window_width;
        sizehints->height = তথ্য->window_height;

        sizehints->min_width = sizehints->max_width = তথ্য->window_width;
        sizehints->min_height = sizehints->max_height = তথ্য->window_height;

        X11_XSetWMNormalHints(display, তথ্য->window, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, তথ্য->window);

    তথ্য->drawable = তথ্য->window;
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    যদি (SDL_X11_HAVE_XDBE && !তথ্য->pixmap) {
        পূর্ণসংখ্যা xdbe_major, xdbe_minor;
        যদি (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            তথ্য->xdbe = true;
            তথ্য->buf = X11_Xdbe_Allocate_Back_বাফার_Name(display, তথ্য->window, XdbeUndefined);
            তথ্য->drawable = তথ্য->buf;
        } অন্যথা {
            তথ্য->xdbe = false;
        }
    }
#endif

    X11Toolkit_InitWindowPixmap(তথ্য);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = তথ্য->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = তথ্য->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    যদি (!তথ্য->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = তথ্য->font_struct->fid;
    }
    তথ্য->ctx = X11_XCreateGC(তথ্য->display, তথ্য->drawable, gcflags, &ctx_vals);
    যদি (তথ্য->ctx == None) {
        ফেরত SDL_SetError("Couldn't create graphics context");
    }

    তথ্য->close = false;
    তথ্য->চাবি_control_esc = তথ্য->চাবি_control_enter = ফাঁকা;
    যদি (!তথ্য->pixmap) {
        তথ্য->ev_scale = তথ্য->ev_iscale = 1;
    } অন্যথা {
        তথ্য->ev_scale = তথ্য->scale;
        তথ্য->ev_iscale = তথ্য->iscale;
    }

#যদি SDL_GRAB
    যদি (তথ্য->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || তথ্য->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XGrabPointer(display, তথ্য->window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
        X11_XGrabKeyboard(display, তথ্য->window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
#endif

    ফেরত true;
}

স্থির শূন্য X11Toolkit_DrawWindow(SDL_ToolkitWindowX11 *তথ্য) {
    SDL_Rect rect;
    পূর্ণসংখ্যা i;

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    যদি (SDL_X11_HAVE_XDBE && তথ্য->xdbe && !তথ্য->pixmap) {
        X11_XdbeBeginIdiom(তথ্য->display);
    }
#endif

    X11_XSetForeground(তথ্য->display, তথ্য->ctx, তথ্য->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    যদি (তথ্য->pixmap) {
        X11_XFillRectangle(তথ্য->display, তথ্য->drawable, তথ্য->ctx, 0, 0, তথ্য->pixmap_width, তথ্য->pixmap_height);
    } অন্যথা {
        X11_XFillRectangle(তথ্য->display, তথ্য->drawable, তথ্য->ctx, 0, 0, তথ্য->window_width, তথ্য->window_height);
    }

    জন্য (i = 0; i < তথ্য->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = তথ্য->controls[i];
        যদি (control) {
            যদি (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    যদি (SDL_X11_HAVE_XDBE && তথ্য->xdbe && !তথ্য->pixmap) {
        XdbeSwapInfo swap_info;
        swap_info.swap_window = তথ্য->window;
        swap_info.swap_action = XdbeUndefined;
        X11_XdbeSwapBuffers(তথ্য->display, &swap_info, 1);
        X11_XdbeEndIdiom(তথ্য->display);
    }
#endif

    যদি (তথ্য->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = তথ্য->window_width;
        rect.h = তথ্য->window_height;
#ifndef NO_SHARED_MEMORY
        যদি (তথ্য->shm) {
            যদি (তথ্য->shm_pixmap) {
                X11_XFlush(তথ্য->display);
                X11_XSync(তথ্য->display, false);
                scale_surface = SDL_CreateSurfaceFrom(তথ্য->pixmap_width, তথ্য->pixmap_height, X11_GetPixelFormatFromVisualInfo(তথ্য->display, &তথ্য->vi), তথ্য->shm_info.shmaddr, তথ্য->shm_bytes_per_সারি);
                SDL_BlitSurfaceScaled(scale_surface, ফাঁকা, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(তথ্য->display, তথ্য->drawable, তথ্য->window, তথ্য->ctx, 0, 0, তথ্য->window_width, তথ্য->window_height, 0, 0);
            } অন্যথা {
                X11_XShmGetImage(তথ্য->display, তথ্য->drawable, তথ্য->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(তথ্য->pixmap_width, তথ্য->pixmap_height, X11_GetPixelFormatFromVisualInfo(তথ্য->display, &তথ্য->vi), তথ্য->image->তথ্য, তথ্য->image->bytes_per_সারি);
                SDL_BlitSurfaceScaled(scale_surface, ফাঁকা, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                X11_XShmPutImage(তথ্য->display, তথ্য->window, তথ্য->ctx, তথ্য->image, 0, 0, 0, 0, তথ্য->window_width, তথ্য->window_height, False);
            }
        } অন্যথা
#endif
        {
            XImage *image;

            image = X11_XGetImage(তথ্য->display, তথ্য->drawable, 0, 0 , তথ্য->pixmap_width, তথ্য->pixmap_height, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(তথ্য->pixmap_width, তথ্য->pixmap_height, X11_GetPixelFormatFromVisualInfo(তথ্য->display, &তথ্য->vi), image->তথ্য, image->bytes_per_সারি);
            SDL_BlitSurfaceScaled(scale_surface, ফাঁকা, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
            X11_XPutImage(তথ্য->display, তথ্য->window, তথ্য->ctx, image, 0, 0, 0, 0, তথ্য->window_width, তথ্য->window_height);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(তথ্য->display);
}

স্থির SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_ToolkitWindowX11 *তথ্য, পূর্ণসংখ্যা x, পূর্ণসংখ্যা y)
{
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < তথ্য->controls_sz; i++) {
        SDL_Rect *rect = &তথ্য->controls[i]->rect;
        যদি ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            ফেরত তথ্য->controls[i];
        }
    }

    ফেরত ফাঁকা;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
স্থির Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_ToolkitWindowX11 *তথ্য = (SDL_ToolkitWindowX11 *)arg;

    যদি (event->xany.display != তথ্য->display) {
        ফেরত False;
    }

    যদি (event->xany.window == তথ্য->window) {
        ফেরত True;
    }

    ফেরত False;
}

শূন্য X11Toolkit_ProcessWindowEvents(SDL_ToolkitWindowX11 *তথ্য, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    যদি ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        ফেরত;
    }

    তথ্য->draw = false;
    তথ্য->e = e;

    নির্বাচন (e->type) {
        ক্ষেত্র Expose:
            তথ্য->draw = true;
            বিরতি;
        ক্ষেত্র ClientMessage:
            যদি (e->xclient.message_type == তথ্য->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.তথ্য.l[0] == তথ্য->wm_delete_message) {
                তথ্য->close = true;
            }
            বিরতি;
        ক্ষেত্র FocusIn:
            তথ্য->has_focus = true;
            বিরতি;
        ক্ষেত্র FocusOut:
            তথ্য->has_focus = false;
            যদি (তথ্য->fiddled_control) {
                তথ্য->fiddled_control->selected = false;
            }
            তথ্য->fiddled_control = ফাঁকা;
            জন্য (তথ্য->ev_i = 0; তথ্য->ev_i < তথ্য->controls_sz; তথ্য->ev_i++) {
                তথ্য->controls[তথ্য->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
            }
            বিরতি;
        ক্ষেত্র MotionNotify:
            যদি (তথ্য->has_focus) {
                তথ্য->previous_control = তথ্য->fiddled_control;
                তথ্য->fiddled_control = X11Toolkit_GetControlMouseIsOn(তথ্য, SDL_lroundf((e->xbutton.x/ তথ্য->ev_scale)* তথ্য->ev_iscale), SDL_lroundf((e->xbutton.y/ তথ্য->ev_scale)* তথ্য->ev_iscale));
                যদি (তথ্য->previous_control) {
                    তথ্য->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    যদি (তথ্য->previous_control->func_on_state_change) {
                        তথ্য->previous_control->func_on_state_change(তথ্য->previous_control);
                    }
                    তথ্য->draw = true;
                }
                যদি (তথ্য->fiddled_control) {
                    যদি (তথ্য->fiddled_control->dynamic) {
                        তথ্য->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        যদি (তথ্য->fiddled_control->func_on_state_change) {
                            তথ্য->fiddled_control->func_on_state_change(তথ্য->fiddled_control);
                        }
                        তথ্য->draw = true;
                    } অন্যথা {
                        তথ্য->fiddled_control = ফাঁকা;
                    }
                }
            }
            বিরতি;
        ক্ষেত্র ButtonPress:
            তথ্য->previous_control = তথ্য->fiddled_control;
            যদি (তথ্য->previous_control) {
                তথ্য->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                যদি (তথ্য->previous_control->func_on_state_change) {
                    তথ্য->previous_control->func_on_state_change(তথ্য->previous_control);
                }
                তথ্য->draw = true;
            }
            যদি (e->xbutton.button == Button1) {
                তথ্য->fiddled_control = X11Toolkit_GetControlMouseIsOn(তথ্য, SDL_lroundf((e->xbutton.x/ তথ্য->ev_scale)* তথ্য->ev_iscale), SDL_lroundf((e->xbutton.y/ তথ্য->ev_scale)* তথ্য->ev_iscale));
                যদি (তথ্য->fiddled_control) {
                    তথ্য->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    যদি (তথ্য->fiddled_control->func_on_state_change) {
                        তথ্য->fiddled_control->func_on_state_change(তথ্য->fiddled_control);
                    }
                    তথ্য->draw = true;
                }
            }
            বিরতি;
        ক্ষেত্র ButtonRelease:
            যদি (তথ্য->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || তথ্য->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
                পূর্ণসংখ্যা cx;
                পূর্ণসংখ্যা cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                যদি (cy < 0 || cx < 0) {
                    তথ্য->close = true;
                }

                যদি (cy > তথ্য->window_height || cx > তথ্য->window_width) {
                    তথ্য->close = true;
                }
            }

            যদি ((e->xbutton.button == Button1) && (তথ্য->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(তথ্য, SDL_lroundf((e->xbutton.x/ তথ্য->ev_scale)* তথ্য->ev_iscale), SDL_lroundf((e->xbutton.y/ তথ্য->ev_scale)* তথ্য->ev_iscale));
                যদি (তথ্য->fiddled_control == control) {
                    তথ্য->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    যদি (তথ্য->fiddled_control->func_on_state_change) {
                        তথ্য->fiddled_control->func_on_state_change(তথ্য->fiddled_control);
                    }
                    তথ্য->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    তথ্য->draw = true;
                }
            }
            বিরতি;
        ক্ষেত্র চাবি_Press:
            তথ্য->last_চাবি_pressed = X11_XLookupKeysym(&e->xkey, 0);

            যদি (তথ্য->last_চাবি_pressed == XK_Escape) {
                জন্য (তথ্য->ev_i = 0; তথ্য->ev_i < তথ্য->controls_sz; তথ্য->ev_i++) {
                    যদি(তথ্য->controls[তথ্য->ev_i]->is_default_esc) {
                        তথ্য->controls[তথ্য->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        তথ্য->draw = true;
                        তথ্য->চাবি_control_esc = তথ্য->controls[তথ্য->ev_i];
                    }
                }
            } অন্যথা যদি ((তথ্য->last_চাবি_pressed == XK_Return) || (তথ্য->last_চাবি_pressed == XK_KP_Enter)) {
                জন্য (তথ্য->ev_i = 0; তথ্য->ev_i < তথ্য->controls_sz; তথ্য->ev_i++) {
                    যদি(তথ্য->controls[তথ্য->ev_i]->selected) {
                        তথ্য->controls[তথ্য->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        তথ্য->draw = true;
                        তথ্য->চাবি_control_enter = তথ্য->controls[তথ্য->ev_i];
                    }
                }
            }
            বিরতি;
        ক্ষেত্র চাবি_Release:
        {
            চাবি_Sym চাবি = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            যদি (চাবি != তথ্য->last_চাবি_pressed) {
                বিরতি;
            }

            যদি (চাবি == XK_Escape) {
                যদি (তথ্য->চাবি_control_esc) {
                    যদি (তথ্য->চাবি_control_esc->func_on_state_change) {
                        তথ্য->চাবি_control_esc->func_on_state_change(তথ্য->চাবি_control_esc);
                    }
                }
            } অন্যথা যদি ((চাবি == XK_Return) || (চাবি == XK_KP_Enter)) {
                যদি (তথ্য->চাবি_control_enter) {
                    যদি (তথ্য->চাবি_control_enter->func_on_state_change) {
                        তথ্য->চাবি_control_enter->func_on_state_change(তথ্য->চাবি_control_enter);
                    }
                }
            } অন্যথা যদি (চাবি == XK_Tab || চাবি == XK_বাম || চাবি == XK_ডান) {
                যদি (তথ্য->focused_control) {
                    তথ্য->focused_control->selected = false;
                }
                তথ্য->draw = true;
                জন্য (তথ্য->ev_i = 0; তথ্য->ev_i < তথ্য->dyn_controls_sz; তথ্য->ev_i++) {
                    যদি (তথ্য->dyn_controls[তথ্য->ev_i] == তথ্য->focused_control) {
                        পূর্ণসংখ্যা পরবর্তী_সূচক;

                        যদি (চাবি == XK_বাম) {
                            পরবর্তী_সূচক = তথ্য->ev_i - 1;
                        } অন্যথা {
                            পরবর্তী_সূচক = তথ্য->ev_i + 1;
                        }
                        যদি ((পরবর্তী_সূচক >= তথ্য->dyn_controls_sz) || (পরবর্তী_সূচক < 0)) {
                            যদি (চাবি == XK_ডান || চাবি == XK_বাম) {
                                পরবর্তী_সূচক = তথ্য->ev_i;
                            } অন্যথা {
                                পরবর্তী_সূচক = 0;
                            }
                        }
                        তথ্য->focused_control = তথ্য->dyn_controls[পরবর্তী_সূচক];
                        তথ্য->focused_control->selected = true;
                        বিরতি;
                    }
                }
            }
            বিরতি;
        }
    }

    যদি (তথ্য->draw) {
        X11Toolkit_DrawWindow(তথ্য);
    }
}

শূন্য X11Toolkit_DoWindowEventLoop(SDL_ToolkitWindowX11 *তথ্য) {
   যখন (!তথ্য->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(তথ্য->display, &e);
        যদি (তথ্য->xsettings) {
            xsettings_client_process_event(তথ্য->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(তথ্য->display, &e, X11Toolkit_EventTest, (XPointer)তথ্য);
        X11Toolkit_ProcessWindowEvents(তথ্য, &e);
    }
}


শূন্য X11Toolkit_ResizeWindow(SDL_ToolkitWindowX11 *তথ্য, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h) {
    যদি (!তথ্য->pixmap) {
        তথ্য->window_width = w;
        তথ্য->window_height = h;
    } অন্যথা {
        তথ্য->window_width = SDL_lroundf((w/তথ্য->iscale) * তথ্য->scale);
        তথ্য->window_height = SDL_lroundf((h/তথ্য->iscale) * তথ্য->scale);
        তথ্য->pixmap_width = w;
        তথ্য->pixmap_height = h;
        X11_XFreePixmap(তথ্য->display, তথ্য->drawable);
        X11Toolkit_InitWindowPixmap(তথ্য);
    }

    X11_XResizeWindow(তথ্য->display, তথ্য->window, তথ্য->window_width, তথ্য->window_height);
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

    নির্বাচন (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        ক্ষেত্র SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                বিরতি;
        ক্ষেত্র SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                বিরতি;
        ক্ষেত্র SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                বিরতি;
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
    পূর্ণসংখ্যা icon_char_w;
    পূর্ণসংখ্যা icon_wh;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11Toolkit_GetTextWidthHeightForFont(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, ফাঁকা);
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
    অক্ষর *font;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11_XFreeFont(base_control->window->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_আকার * base_control->window->iscale);
    control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
    SDL_free(font);
    যদি (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_আকার * base_control->window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_ToolkitWindowX11 *window, SDL_MessageBoxFlags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    অক্ষর *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(আকার(SDL_ToolkitIconControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    যদি (!control) {
        SDL_SetError("Unable to allocate icon control structure");
        ফেরত ফাঁকা;
    }

    /* Fill out struct */
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawIconControl;
    base_control->func_free = X11Toolkit_DestroyIconControl;
    base_control->func_on_state_change = ফাঁকা;
    base_control->func_calc_আকার = X11Toolkit_CalculateIconControl;
    base_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = false;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_আকার * window->iscale);
    control->icon_char_font = X11_XLoadQueryFont(window->display, font);
    SDL_free(font);
    যদি (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_আকার * window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        যদি (!control->icon_char_font) {
            SDL_free(control);
            ফেরত ফাঁকা;
        }
    }

    /* Set colors */
    নির্বাচন (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    ক্ষেত্র SDL_MESSAGEBOX_ERROR:
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
        বিরতি;
    ক্ষেত্র SDL_MESSAGEBOX_WARNING:
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
        বিরতি;
    ক্ষেত্র SDL_MESSAGEBOX_INFORMATION:
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
        বিরতি;
    পূর্বনির্ধারিত:
        X11_XFreeFont(window->display, control->icon_char_font);
        SDL_free(control);
        ফেরত ফাঁকা;
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
    ফেরত base_control;
}

bool X11_Toolkit_Notify_Control_Of_আকার_Change(SDL_ToolkitControlX11 *control) {
    যদি (control->func_calc_আকার) {
        control->func_calc_আকার(control);
        ফেরত true;
    } অন্যথা {
        ফেরত false;
    }
}

স্থির শূন্য X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11Toolkit_GetTextElementsRect(button_control->text, &button_control->text_rect);
    যদি (control->do_আকার) {
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
        button_control->cb(control, button_control->cb_তথ্য);
    }
}

স্থির শূন্য X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11Toolkit_FreeTextElements(button_control->text);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_ToolkitWindowX11 *window, ধ্রুবক SDL_Message_Box_Button_তথ্য *তথ্য) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *base_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(আকার(SDL_ToolkitButtonControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    যদি (!control) {
        SDL_SetError("Unable to allocate button control structure");
        ফেরত ফাঁকা;
    }
    base_control->window = window;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->func_calc_আকার = X11Toolkit_CalculateButtonControl;
    base_control->func_draw = X11Toolkit_DrawButtonControl;
    base_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    base_control->func_free = X11Toolkit_DestroyButtonControl;
    base_control->func_on_scale_change = ফাঁকা;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = true;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    যদি (তথ্য->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        base_control->is_default_esc = true;
    }
    যদি (তথ্য->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        base_control->is_default_enter = true;
        base_control->selected = true;
    }
    control->cb = ফাঁকা;
    control->তথ্য = তথ্য;
#ifdef HAVE_FRIBIDI_H
    control->text = X11Toolkit_MakeTextElements(base_control->window, (অক্ষর *)control->তথ্য->text, SDL_strlen(control->তথ্য->text), ফাঁকা);
#অন্যথা 
    control->text = X11Toolkit_MakeTextElements(base_control->window, (অক্ষর *)control->তথ্য->text, SDL_strlen(control->তথ্য->text));
#endif
    X11Toolkit_ShapeTextElements(base_control->window, control->text);
    
    base_control->do_আকার = true;
    X11Toolkit_CalculateButtonControl(base_control);
    base_control->do_আকার = false;

    X11Toolkit_AddControlToWindow(window, base_control);
    ফেরত base_control;
}

শূন্য X11Toolkit_RegisterCallbackForButtonControl(SDL_ToolkitControlX11 *control, শূন্য *তথ্য, শূন্য (*cb)(কাঠামো SDL_ToolkitControlX11 *, শূন্য *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_তথ্য = তথ্য;
    button_control->cb = cb;
}

ধ্রুবক SDL_Message_Box_Button_তথ্য *X11_Toolkit_Get_Button_Control_তথ্য(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    ফেরত button_control->তথ্য;
}

শূন্য X11Toolkit_DestroyWindow(SDL_ToolkitWindowX11 *তথ্য) {
    পূর্ণসংখ্যা i;

    যদি (!তথ্য) {
        ফেরত;
    }

#যদি SDL_GRAB
    যদি (তথ্য->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || তথ্য->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XUngrabPointer(তথ্য->display, CurrentTime);
        X11_XUngrabKeyboard(তথ্য->display, CurrentTime);
    }
#endif

    জন্য (i = 0; i < তথ্য->controls_sz; i++) {
        যদি (তথ্য->controls[i]->func_free) {
            তথ্য->controls[i]->func_free(তথ্য->controls[i]);
        }
    }
    SDL_free(তথ্য->controls);
    SDL_free(তথ্য->dyn_controls);

    যদি (তথ্য->popup_windows) {
        SDL_ListClear(&তথ্য->popup_windows);
    }

    যদি (তথ্য->pixmap) {
        X11_XFreePixmap(তথ্য->display, তথ্য->drawable);
    }

#ifndef NO_SHARED_MEMORY
    যদি (তথ্য->pixmap && তথ্য->shm) {
        X11_XShmDetach(তথ্য->display, &তথ্য->shm_info);
        যদি (!তথ্য->shm_pixmap) {
            XDestroyImage(তথ্য->image);
        }
        shmdt(তথ্য->shm_info.shmaddr);
    }
#endif

#ifdef X_HAVE_UTF8_STRING
    যদি (তথ্য->font_set) {
        X11_XFreeFontSet(তথ্য->display, তথ্য->font_set);
        তথ্য->font_set = ফাঁকা;
    }
#endif

    যদি (তথ্য->font_struct) {
        X11_XFreeFont(তথ্য->display, তথ্য->font_struct);
        তথ্য->font_struct = ফাঁকা;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    যদি (SDL_X11_HAVE_XDBE && তথ্য->xdbe && !তথ্য->pixmap) {
        X11_Xdbe_Deallocate_Back_বাফার_Name(তথ্য->display, তথ্য->buf);
    }
#endif

    যদি (তথ্য->xsettings) {
        xsettings_client_destroy(তথ্য->xsettings);
    }

    X11_XFreeGC(তথ্য->display, তথ্য->ctx);

    যদি (তথ্য->display) {
        যদি (তথ্য->window != None) {
            X11_XWithdrawWindow(তথ্য->display, তথ্য->window, তথ্য->screen);
            X11_XDestroyWindow(তথ্য->display, তথ্য->window);
            তথ্য->window = None;
        }

        যদি (তথ্য->display_close) {
            X11_XCloseDisplay(তথ্য->display);
        }
        তথ্য->display = ফাঁকা;
    }

#যদি SDL_SET_LOCALE
    যদি (তথ্য->origlocale && (তথ্য->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG)) {
        (শূন্য)setlocale(LC_ALL, তথ্য->origlocale);
        SDL_free(তথ্য->origlocale);
    }
#endif

#ifdef HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(তথ্য->fribidi);
#endif

#ifdef HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(তথ্য->th);
#endif

    SDL_free(তথ্য);
}

স্থির পূর্ণসংখ্যা X11_Toolkit_গুনতি_সারিগুলি_Of_Text(ধ্রুবক অক্ষর *text)
{
    পূর্ণসংখ্যা ফলাফল = 0;
    যখন (text && *text) {
        ধ্রুবক অক্ষর *lf = SDL_strchr(text, '\n');
        ফলাফল++; // even without an endline, this counts as a line.
        text = lf ? lf + 1 : ফাঁকা;
    }
    ফেরত ফলাফল;
}

স্থির শূন্য X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    পূর্ণসংখ্যা i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    জন্য (i = 0; i < label_control->sz; i++) {
        X11Toolkit_DrawTextElements(control->window, label_control->সারিগুলি[i].text, control->rect.x + label_control->সারিগুলি[i].rect.x, control->rect.y + label_control->সারিগুলি[i].rect.y);
    }
}

স্থির শূন্য X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    পূর্ণসংখ্যা i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    জন্য (i = 0; i < label_control->sz; i++) {
        X11Toolkit_FreeTextElements(label_control->সারিগুলি[i].text);
    }
    SDL_free(label_control->সারিগুলি);
    SDL_free(label_control);
}

স্থির শূন্য X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitLabelControlX11 *control;
    পূর্ণসংখ্যা i;

    control = (SDL_ToolkitLabelControlX11 *)base_control;
    
    যদি (base_control->do_আকার) {
        base_control->rect.w = 0;
        base_control->rect.h = 0;
    }
    
    জন্য (i = 0; i < control->sz; i++) {
        পূর্ণসংখ্যা font_h;
        
        font_h = X11Toolkit_GetTextElementsRect(control->সারিগুলি[i].text, &control->সারিগুলি[i].rect);
        
        যদি (base_control->do_আকার) {
            base_control->rect.w = SDL_max(base_control->rect.w, control->সারিগুলি[i].rect.w);
        }
        
        যদি (i > 0) {
            control->সারিগুলি[i].rect.y = font_h + control->সারিগুলি[i - 1].rect.y;
        } অন্যথা {
            control->সারিগুলি[i].rect.y = 0;
        }
    }

#ifdef HAVE_FRIBIDI_H
    যদি (base_control->window->fribidi) {
        FriBidiParType first_ndn_dir;
        পূর্ণসংখ্যা last_ndn;
    
        first_ndn_dir = FRIBIDI_PAR_LTR;
        জন্য (i = 0; i < control->sz; i++) {
            যদি (control->সারিগুলি[i].par != FRIBIDI_PAR_ON) {
                first_ndn_dir = control->সারিগুলি[i].par;
            }
        }

        last_ndn = -1;
        জন্য (i = 0; i < control->sz; i++) {
            নির্বাচন (control->সারিগুলি[i].par) {
                ক্ষেত্র FRIBIDI_PAR_LTR:
                    control->সারিগুলি[i].rect.x = 0;
                    last_ndn = i;
                    বিরতি;
                ক্ষেত্র FRIBIDI_PAR_RTL:
                    control->সারিগুলি[i].rect.x = base_control->rect.w - control->সারিগুলি[i].rect.w;
                    last_ndn = i;
                    বিরতি;
                পূর্বনির্ধারিত:
                    যদি (last_ndn != -1) {
                        যদি (control->সারিগুলি[last_ndn].par == FRIBIDI_PAR_RTL) {
                            control->সারিগুলি[i].rect.x = base_control->rect.w - control->সারিগুলি[i].rect.w;
                        } অন্যথা {
                            control->সারিগুলি[i].rect.x = 0;
                        }
                    } অন্যথা {
                        যদি (first_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->সারিগুলি[i].rect.x = base_control->rect.w - control->সারিগুলি[i].rect.w;
                        } অন্যথা {
                            control->সারিগুলি[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#endif
    
    যদি (base_control->do_আকার && control->sz) {
        base_control->rect.h = control->সারিগুলি[control->sz - 1].rect.y + control->সারিগুলি[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_ToolkitWindowX11 *window, অক্ষর *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    পূর্ণসংখ্যা i;
    
    যদি (!utf8) {
        ফেরত ফাঁকা;
    }
 
    যদি (!SDL_strcmp(utf8, "")) {
        ফেরত ফাঁকা;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(আকার(SDL_ToolkitLabelControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    যদি (!control) {
        SDL_SetError("Unable to allocate label control structure");
        ফেরত ফাঁকা;
    }
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawLabelControl;
    base_control->func_on_state_change = ফাঁকা;
    base_control->func_calc_আকার = X11Toolkit_CalculateLabelControl;
    base_control->func_free  = X11Toolkit_DestroyLabelControl;
    base_control->func_on_scale_change = ফাঁকা;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = false;
    base_control->rect.w = 0;
    base_control->rect.h = 0;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_গুনতি_সারিগুলি_Of_Text(utf8);
    control->সারিগুলি = SDL_calloc(control->sz, আকার(SDL_Toolkit_Label_Control_সারি_X11));
    জন্য (i = 0; i < control->sz; i++) {
        ধ্রুবক অক্ষর *lf = SDL_strchr(utf8, '\n');
        ধ্রুবক পূর্ণসংখ্যা দৈর্ঘ্য = lf ? (lf - utf8) : SDL_strlen(utf8);
        পূর্ণসংখ্যা sz;
        
        sz = দৈর্ঘ্য;
        যদি (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#ifdef HAVE_FRIBIDI_H
        control->সারিগুলি[i].text = X11Toolkit_MakeTextElements(base_control->window, (অক্ষর *)utf8, sz, &control->সারিগুলি[i].par);
#অন্যথা 
        control->সারিগুলি[i].text = X11Toolkit_MakeTextElements(base_control->window, (অক্ষর *)utf8, sz);
#endif
        X11Toolkit_ShapeTextElements(base_control->window, control->সারিগুলি[i].text);

        utf8 += দৈর্ঘ্য + 1;
        যদি (!lf) {
            বিরতি;
        }
    }

    base_control->do_আকার = true;
    X11Toolkit_CalculateLabelControl(base_control);
    base_control->do_আকার = false;
    X11Toolkit_AddControlToWindow(window, base_control);

    ফেরত base_control;
}

পূর্ণসংখ্যা X11_Toolkit_Get_Label_Control_First_সারি_Height(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    ফেরত label_control->সারিগুলি[0].rect.h;
}

শূন্য X11Toolkit_SignalWindowClose(SDL_ToolkitWindowX11 *তথ্য) {
    তথ্য->close = true;
}

#endif // SDL_VIDEO_DRIVER_X11
