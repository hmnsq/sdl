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

#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "../../SDL_list.h"
#अन्तर्भाव "SDL_x11video.h"
#ifdef SDL_USE_LIBDBUS
#अन्तर्भाव "../../core/linux/SDL_system_theme.h"
#endif
#ifdef HAVE_FRIBIDI_H
#अन्तर्भाव "../../core/unix/SDL_fribidi.h"
#endif
#अन्तर्भाव "SDL_x11dyn.h"
#अन्तर्भाव "SDL_x11toolkit.h"
#अन्तर्भाव "SDL_x11settings.h"
#अन्तर्भाव "SDL_x11modes.h"
#अन्तर्भाव "xsettings-client.h"
#अन्तर्भाव <X11/keysym.h>
#अन्तर्भाव <locale.h>

#define SDL_SET_LOCALE 1
#define SDL_GRAB 1

प्रकारनिर्देश गणना SDL_ToolkitTextTypeX11
{
    SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC,
    SDL_TOOLKIT_TEXT_TYPE_X11_THAI
} SDL_ToolkitTextTypeX11;

#ifdef HAVE_LIBTHAI_H
प्रकारनिर्देश संरचना SDL_ToolkitThaiOverlayX11
{
    bool शीर्ष;
    वर्ण *str;
    माप_प्रकार sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#endif

प्रकारनिर्देश संरचना SDL_ToolkitTextElementX11
{
    SDL_ToolkitTextTypeX11 type;
    वर्ण *str;
    माप_प्रकार sz;
    SDL_Rect rect;
    पूर्णाङ्क font_h;
    शून्य (*str_free)(शून्य *);
#ifdef HAVE_LIBTHAI_H
    SDL_List_गाँठ *thai_overlays;
#endif
} SDL_ToolkitTextElementX11;

प्रकारनिर्देश संरचना SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Icon type */
    SDL_MessageBoxFlags flags;
    वर्ण icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    पूर्णाङ्क icon_char_x;
    पूर्णाङ्क icon_char_y;
    पूर्णाङ्क icon_char_a;
    पूर्णाङ्क icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

प्रकारनिर्देश संरचना SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Data */
    ध्रुव SDL_MessageBoxButtonData *data;

    /* Text */
    SDL_List_गाँठ *text;
    SDL_Rect text_rect;
    
    /* Callback */
    शून्य *cb_data;
    शून्य (*cb)(संरचना SDL_ToolkitControlX11 *, शून्य *);
} SDL_ToolkitButtonControlX11;

प्रकारनिर्देश संरचना SDL_Toolkit_Label_Control_पंक्ति_X11
{
    SDL_List_गाँठ *text;
    SDL_Rect rect;
#ifdef HAVE_FRIBIDI_H
    FriBidiParType par;
#endif
} SDL_Toolkit_Label_Control_पंक्ति_X11;

प्रकारनिर्देश संरचना SDL_ToolkitLabelControlX11
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
    SDL_Toolkit_Label_Control_पंक्ति_X11 *पंक्तियाँ;
    माप_प्रकार sz;
} SDL_ToolkitLabelControlX11;

प्रकारनिर्देश संरचना SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_गाँठ *menu_वस्तुएँ;
} SDL_ToolkitMenuBarControlX11;

प्रकारनिर्देश संरचना SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_गाँठ *menu_वस्तुएँ;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
स्थिर ध्रुव वर्ण *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#define G_ICONFONT_SIZE 22

/* General UI font */
स्थिर ध्रुव वर्ण g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
स्थिर ध्रुव वर्ण g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

स्थिर ध्रुव वर्ण *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    रिक्त
};
#define G_TOOLKITFONT_SIZE 140

स्थिर ध्रुव SDL_MessageBoxColor g_default_colors[SDL_MESSAGEBOX_COLOR_गिनती] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ifdef SDL_USE_LIBDBUS
स्थिर ध्रुव SDL_MessageBoxColor g_default_colors_dark[SDL_MESSAGEBOX_COLOR_गिनती] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#यदि 0
स्थिर ध्रुव SDL_MessageBoxColor g_default_colors_dark_ऊपरी_contrast[SDL_MESSAGEBOX_COLOR_गिनती] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

स्थिर ध्रुव SDL_MessageBoxColor g_default_colors_light_ऊपरी_contrast[SDL_MESSAGEBOX_COLOR_गिनती] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#endif

#endif

स्थिर पूर्णाङ्क g_shm_error;
स्थिर पूर्णाङ्क (*g_old_error_handler)(Display *, XErrorEvent *) = रिक्त;

स्थिर पूर्णाङ्क X11Toolkit_SharedMemoryErrorHandler(Display *d, XErrorEvent *e)
{
    यदि (e->error_code == BadAccess || e->error_code == BadRequest) {
        g_shm_error = True;
        प्रत्यागम 0;
    }
    प्रत्यागम g_old_error_handler(d, e);
}

स्थिर शून्य X11Toolkit_InitWindowPixmap(SDL_ToolkitWindowX11 *data) {
    यदि (data->pixmap) {
#ifndef NO_SHARED_MEMORY
        यदि (!data->shm_pixmap) {
            data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
        }
#अन्यथा
        data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
#endif
#ifndef NO_SHARED_MEMORY
        यदि (data->shm) {
            data->image = X11_XShmCreateImage(data->display, data->visual, data->depth, ZPixmap, रिक्त, &data->shm_info, data->pixmap_width, data->pixmap_height);
            यदि (data->image) {
                data->shm_bytes_per_पंक्ति = data->image->bytes_per_पंक्ति;

                data->shm_info.shmid = shmget(IPC_PRIVATE, data->image->bytes_per_पंक्ति * data->image->height, IPC_CREAT | 0777);
                यदि (data->shm_info.shmid < 0) {
                    XDestroyImage(data->image);
                    data->image = रिक्त;
                    data->shm = false;
                    प्रत्यागम;
                }

                data->shm_info.readOnly = False;
                data->shm_info.shmaddr = data->image->data = (वर्ण *)shmat(data->shm_info.shmid, रिक्त, 0);
                यदि (((चिन्हित वर्ण *)data->shm_info.shmaddr) == (चिन्हित वर्ण *)-1) {
                    XDestroyImage(data->image);
                    data->shm = false;
                    data->image = रिक्त;
                    प्रत्यागम;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11Toolkit_SharedMemoryErrorHandler);
                X11_XShmAttach(data->display, &data->shm_info);
                X11_XSync(data->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                यदि (g_shm_error) {
                    XDestroyImage(data->image);
                    shmdt(data->shm_info.shmaddr);
                    shmctl(data->shm_info.shmid, IPC_RMID, रिक्त);
                    data->image = रिक्त;
                    data->shm = false;
                    प्रत्यागम;
                }

                यदि (data->shm_pixmap) {
                    data->drawable = X11_XShmCreatePixmap(data->display, data->window, data->shm_info.shmaddr, &data->shm_info, data->pixmap_width, data->pixmap_height, data->depth);
                    यदि (data->drawable == None) {
                        data->shm_pixmap = False;
                    } अन्यथा {
                        XDestroyImage(data->image);
                        data->image = रिक्त;
                    }
                }

                shmctl(data->shm_info.shmid, IPC_RMID, रिक्त);
            } अन्यथा {
                data->shm = false;
            }
        }
#endif
    }
}

स्थिर शून्य X11Toolkit_InitWindowFonts(SDL_ToolkitWindowX11 *window)
{    
    window->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    window->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#ifdef X_HAVE_UTF8_STRING
    window->utf8 = true;
    window->font_set = रिक्त;
    यदि (SDL_X11_HAVE_UTF8) {
        वर्ण **missing = रिक्त;
        पूर्णाङ्क अंक_missing = 0;
        पूर्णाङ्क i_font;
        window->font_struct = रिक्त;
        प्रति (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            वर्ण *font;

            यदि (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_load_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_SIZE * window->iscale);
                window->font_set = X11_XCreateFontSet(window->display, font, &missing, &अंक_missing, रिक्त);
                SDL_free(font);

                यदि (!window->font_set) {
                    यदि (window->scale != 0 && window->iscale > 0) {
                        window->iscale = (पूर्णाङ्क)SDL_ceilf(window->scale);
                        window->scale = 0;
                    } अन्यथा {
                        window->iscale--;
                    }
                    गच्छ try_load_font;
                }
            } अन्यथा {
                window->font_set = X11_XCreateFontSet(window->display, g_ToolkitFont[i_font], &missing, &अंक_missing, रिक्त);
            }

            यदि (missing) {
                X11_XFreeStringList(missing);
            }

            यदि (window->font_set) {
                भङ्ग;
            }
        }

        यदि (!window->font_set) {
            गच्छ load_font_traditional;
        } अन्यथा {
            XFontStruct **font_structs;
            वर्ण **font_names;
            पूर्णाङ्क font_sz;
            पूर्णाङ्क i;
            
#ifdef HAVE_FRIBIDI_H
            window->do_shaping = !X11_XContextDependentDrawing(window->font_set);
#endif
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFontsOfFontSet(window->font_set, &font_structs, &font_names);
            प्रति (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                यदि (SDL_strstr(font_names[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } अन्यथा यदि (SDL_strstr(font_names[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } अन्यथा यदि (SDL_strstr(font_names[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } अन्यथा यदि (SDL_strstr(font_names[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } अन्यथा यदि (SDL_strstr(font_names[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                यदि (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(window->display, font_names[i]);
                    यदि (font_struct) {
                        यदि (font_struct->per_char) {
                            पूर्णाङ्क glyphs_sz;
                            पूर्णाङ्क j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            प्रति (j = 0; j < glyphs_sz; j++) {
                                यदि (font_struct->per_char[j].lbearing < 0) {
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
    } अन्यथा
#endif
    {
        वर्ण *font;

        load_font_traditional:
        window->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        window->font_struct = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        यदि (!window->font_struct) {
            यदि (window->iscale > 0) {
                यदि (window->scale != 0) {
                    window->iscale = (पूर्णाङ्क)SDL_ceilf(window->scale);
                    window->scale = 0;
                } अन्यथा {
                    window->iscale--;
                }
                गच्छ load_font_traditional;
            } अन्यथा {
                window->font_struct = X11_XLoadQueryFont(window->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

स्थिर शून्य X11Toolkit_SettingsNotify(ध्रुव वर्ण *name, XSettingsAction action, XSettingsSetting *setting, शून्य *data)
{
    SDL_ToolkitWindowX11 *window;
    पूर्णाङ्क i;

    window = data;

    यदि (window->xsettings_first_time) {
        प्रत्यागम;
    }

    यदि (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_setup = false;
        bool pixmap_already_setup = false;

        यदि (window->pixmap) {
            pixmap_already_setup = true;
        } अन्यथा {
            dbe_already_setup = true;
        }

        /* set scale vars */
        window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
        window->iscale = (पूर्णाङ्क)SDL_ceilf(window->scale);
        यदि (window->scale < 1) {
            window->scale = 1;
        }
        यदि (SDL_roundf(window->scale) == window->scale) {
            window->scale = 0;
        }

        /* setup fonts */
#ifdef X_HAVE_UTF8_STRING
        यदि (window->font_set) {
            X11_XFreeFontSet(window->display, window->font_set);
        }
#endif
        यदि (window->font_struct) {
            X11_XFreeFont(window->display, window->font_struct);
        }

        X11Toolkit_InitWindowFonts(window);

        /* set up window */
        यदि (window->scale != 0) {
            window->window_width = SDL_lroundf((window->window_width/window->iscale) * window->scale);
            window->window_height = SDL_lroundf((window->window_height/window->iscale) * window->scale);
            window->pixmap_width = window->window_width;
            window->pixmap_height = window->window_height;
            window->pixmap = true;
        } अन्यथा {
            window->pixmap = false;
        }

        यदि (window->pixmap) {
            यदि (!pixmap_already_setup) {
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                यदि (SDL_X11_HAVE_XDBE && window->xdbe) {
                    X11_XdbeDeallocateBackBufferName(window->display, window->buf);
                }
#endif
            }
            X11_XFreePixmap(window->display, window->drawable);
            X11Toolkit_InitWindowPixmap(window);
        } अन्यथा {
            यदि (!dbe_already_setup) {
                X11_XFreePixmap(window->display, window->drawable);
#ifndef NO_SHARED_MEMORY
                यदि (window->image) {
                    XDestroyImage(window->image);
                    window->image = रिक्त;
                }
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                यदि (SDL_X11_HAVE_XDBE && window->xdbe) {
                    window->buf = X11_XdbeAllocateBackBufferName(window->display, window->window, XdbeUndefined);
                    window->drawable = window->buf;
                }
#endif
            }
        }

        /* notify controls */
        प्रति (i = 0; i < window->controls_sz; i++) {
            window->controls[i]->do_size = true;

            यदि (window->controls[i]->func_on_scale_change) {
                window->controls[i]->func_on_scale_change(window->controls[i]);
            }

            यदि (window->controls[i]->func_calc_size) {
                window->controls[i]->func_calc_size(window->controls[i]);
            }

            window->controls[i]->do_size = false;
        }

        /* notify cb */
        यदि (window->cb_on_scale_change) {
            window->cb_on_scale_change(window, window->cb_data);
        }

        /* update ev scales */
        यदि (!window->pixmap) {
            window->ev_scale = window->ev_iscale = 1;
        } अन्यथा {
            window->ev_scale = window->scale;
            window->ev_iscale = window->iscale;
        }
    }
}

स्थिर शून्य X11Toolkit_GetTextWidthHeightForFont(XFontStruct *font, ध्रुव वर्ण *str, पूर्णाङ्क nbytes, पूर्णाङ्क *pwidth, पूर्णाङ्क *pheight, पूर्णाङ्क *ascent, पूर्णाङ्क *font_height)
{
    XCharStruct text_structure;
    पूर्णाङ्क font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &text_structure);
    *pwidth = text_structure.width;
    *pheight = text_structure.ascent + text_structure.descent;
    *ascent = text_structure.ascent;
    यदि (font_height) {
       *font_height = font_ascent + font_descent;
    }
}

स्थिर शून्य X11Toolkit_GetTextWidthHeight(SDL_ToolkitWindowX11 *data, ध्रुव वर्ण *str, पूर्णाङ्क nbytes, पूर्णाङ्क *pwidth, पूर्णाङ्क *pheight, पूर्णाङ्क *ascent, पूर्णाङ्क *descent, पूर्णाङ्क *font_height)
{
#ifdef X_HAVE_UTF8_STRING
    यदि (data->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8TextExtents(data->font_set, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.width;
        *pheight = overall_logical.height;
        *ascent = -overall_logical.y;
        *descent = overall_logical.height - *ascent;

        यदि (font_height) {
            XFontSetExtents *extents;

            extents = X11_XExtentsOfFontSet(data->font_set);
            *font_height = extents->max_logical_extent.height;
        }
    } अन्यथा
#endif
    {
        XCharStruct text_structure;
        पूर्णाङ्क font_direction, font_ascent, font_descent;
        X11_XTextExtents(data->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &text_structure);
        *pwidth = text_structure.width;
        *pheight = text_structure.ascent + text_structure.descent;
        *ascent = text_structure.ascent;
        *descent = text_structure.descent;

        यदि (font_height) {
            *font_height = font_ascent + font_descent;
        }
    }
}

#ifdef HAVE_FRIBIDI_H
SDL_List_गाँठ *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, वर्ण *txt, माप_प्रकार sz, FriBidiParType *par)
#अन्यथा
SDL_List_गाँठ *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, वर्ण *txt, माप_प्रकार sz)
#endif
{
    SDL_List_गाँठ *list;
    वर्ण *str;
    वर्ण *buffer;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = रिक्त;
    thai = 0;
    str = txt;
    buffer = SDL_malloc(1);
    buffer[0] = 0;
    
#ifdef HAVE_FRIBIDI_H
    यदि (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    यदि (data->fribidi) {
        वर्ण *fstr;
                
        fstr = SDL_FriBidi_Process(data->fribidi, str, sz, data->do_shaping, par);
        यदि (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#endif        

    यावत् (1) {
        वर्ण *new;
        वर्ण utf8[5];
        माप_प्रकार csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_StepUTF8((ध्रुव वर्ण **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        यदि (cp == 0 || cond == (thai ? false : true)) {
            SDL_ToolkitTextElementX11 *element;
            
            element = SDL_malloc(परिमाण(SDL_ToolkitTextElementX11));
            यदि (thai) {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_THAI;
            } अन्यथा {
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

        यदि (!cp) {
            भङ्ग;
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
    यदि (free_txt) {
        SDL_free(txt);
    }
    प्रत्यागम list;
}

शून्य X11Toolkit_ShapeTextElements(SDL_ToolkitWindowX11 *data, SDL_List_गाँठ *list)
{
    SDL_List_गाँठ *cursor;
    SDL_ToolkitTextElementX11 *prev;
    पूर्णाङ्क temp;
    
    /* Shape and calculate bounding box */
    cursor = list;
    यावत् (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
#ifdef HAVE_LIBTHAI_H
        element->thai_overlays = रिक्त;
#endif
        यदि (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            यदि (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, रिक्त);
            } अन्यथा {
#ifdef HAVE_LIBTHAI_H
                यदि (data->th) {
                    संरचना thcell_t *cells;
                    वर्ण *tis_str;
                    वर्ण *base_tis_str;
                    माप_प्रकार cells_sz;
                    माप_प्रकार base_tis_str_sz;
                    माप_प्रकार tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, परिमाण(संरचना thcell_t));
                    data->th->make_cells((ध्रुव thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    base_tis_str_sz = cells_sz;
                    base_tis_str = SDL_malloc(base_tis_str_sz + 1);
                    प्रति (temp = 0; temp < cells_sz; temp++) {
                        base_tis_str[temp] = cells[temp].base;
                        
                        यदि (cells[temp].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            वर्ण *pre;
                            पूर्णाङ्क temp2;
                            
                            overlay = SDL_malloc(परिमाण(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ध्रुव वर्ण *)&cells[temp].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->शीर्ष = false;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, रिक्त);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, रिक्त);
                            SDL_ListAdd(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        यदि (cells[temp].शीर्ष) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            वर्ण *pre;
                            पूर्णाङ्क temp2;
                            
                            overlay = SDL_malloc(परिमाण(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ध्रुव वर्ण *)&cells[temp].शीर्ष, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->शीर्ष = true;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, रिक्त);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, रिक्त);
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
#अन्यथा
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
#endif            
            }
        } अन्यथा {
            X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
        }
        
        cursor = cursor->next;
    }
    
    /* Add offsets */
    prev = रिक्त;
    cursor = list;
    यावत् (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;        
        यदि (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } अन्यथा {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->next;
    }
}


शून्य X11Toolkit_DrawTextElements(SDL_ToolkitWindowX11 *data, SDL_List_गाँठ *list, पूर्णाङ्क x, पूर्णाङ्क y)
{
    SDL_List_गाँठ *cursor;
    
    cursor = list;
    
    यावत् (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        यदि (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            यदि (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
#ifdef X_HAVE_UTF8_STRING
                यदि (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } अन्यथा
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } अन्यथा {    
#ifdef HAVE_LIBTHAI_H
                SDL_List_गाँठ *overlay_cursor;
                    
                /* Draw the base string */
#ifdef X_HAVE_UTF8_STRING
                यदि (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } अन्यथा
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                यावत् (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->entry;
#ifdef X_HAVE_UTF8_STRING
                    यदि (data->utf8) {
                        X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } अन्यथा
#endif
                    {
                        X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->next;
                }
#endif                
            }
        } अन्यथा {
#ifdef X_HAVE_UTF8_STRING
            यदि (data->utf8) {
                X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } अन्यथा
#endif
            {
                X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->next;
    }
}

पूर्णाङ्क X11Toolkit_GetTextElementsRect(SDL_List_गाँठ *list, SDL_Rect *out)
{
    SDL_List_गाँठ *cursor;
    पूर्णाङ्क ret;
    
    ret = 0;
    out->x = out->y = 0;
    out->w = out->h = 0;
    cursor = list;
    यावत् (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        
        out->w += element->rect.w;
        out->h = SDL_max(out->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->next;
    }
    
    प्रत्यागम ret;
}

शून्य X11Toolkit_FreeTextElementsListContents(SDL_List_गाँठ *list)
{
    SDL_List_गाँठ *cursor;
    
    cursor = list;
    यावत् (cursor) {
        SDL_ToolkitTextElementX11 *element;
#ifdef HAVE_LIBTHAI_H
        SDL_List_गाँठ *overlay_cursor;
#endif

        element = cursor->entry;
        
        यदि (element->str_free) {
            element->str_free(element->str);
        }
        
#ifdef HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        यावत् (overlay_cursor) {
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
 
स्थिर bool X11Toolkit_ShouldFlipUI(शून्य) 
{
    SDL_Locale **current_locales;
    स्थिर ध्रुव SDL_Locale rtl_locales[] = {
        { "ar", रिक्त, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", रिक्त, },
        { "iw", रिक्त, },
        { "yi", रिक्त, },
        { "ur", रिक्त, },
        { "ug", रिक्त, },
        { "kd", रिक्त, },
        { "pk", "PK", },
        { "ps", रिक्त, }
    }; 
    पूर्णाङ्क current_locales_sz;
    पूर्णाङ्क i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    यदि (current_locales_sz <= 0) {
        प्रत्यागम false;        
    }
    प्रति (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        यदि (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            यदि (!rtl_locales[i].country) {
                प्रत्यागम true;
            } अन्यथा {
                प्रत्यागम SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    प्रत्यागम false;
}

SDL_ToolkitWindowX11 *X11Toolkit_CreateWindowStruct(SDL_Window *parent, SDL_ToolkitWindowX11 *tkparent, SDL_ToolkitWindowModeX11 mode, ध्रुव SDL_MessageBoxColor *colorhints, bool create_new_display)
{
    SDL_ToolkitWindowX11 *window;
    पूर्णाङ्क i;
#ifdef SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#endif
    #define ErrorFreeRetNull(x, y) SDL_SetError(x); SDL_free(y); प्रत्यागम रिक्त
    #define ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_SetError(x, y); SDL_free(z); प्रत्यागम रिक्त

    यदि (!SDL_X11_LoadSymbols()) {
        प्रत्यागम रिक्त;
    }

    // This code could get called from multiple threads maybe?
    X11_XInitThreads();

    window = (SDL_ToolkitWindowX11 *)SDL_malloc(परिमाण(SDL_ToolkitWindowX11));
    यदि (!window) {
        SDL_SetError("Unable to allocate toolkit window structure");
        प्रत्यागम रिक्त;
    }

    window->mode = mode;
    window->tk_parent = tkparent;

#यदि SDL_SET_LOCALE
    यदि (mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        window->origlocale = रखो_क्षेत्र(LC_ALL, रिक्त);
        यदि (window->origlocale) {
            window->origlocale = SDL_strdup(window->origlocale);
            यदि (!window->origlocale) {
                SDL_free(window);
                प्रत्यागम रिक्त;
            }
            (शून्य)रखो_क्षेत्र(LC_ALL, "");
        }
    }
#endif

    window->parent_device = रिक्त;
    यदि (create_new_display) {
        window->display = X11_XOpenDisplay(रिक्त);
        window->display_close = true;
        यदि (!window->display) {
            ErrorFreeRetNull("Couldn't open X11 display", window);
        }
    } अन्यथा {
        यदि (parent) {
            window->parent_device = SDL_GetVideoDevice();
            window->display = window->parent_device->internal->display;
            window->display_close = false;
        } अन्यथा यदि (tkparent) {
            window->display = tkparent->display;
            window->display_close = false;
        } अन्यथा {
            window->display = X11_XOpenDisplay(रिक्त);
            window->display_close = true;
            यदि (!window->display) {
                ErrorFreeRetNull("Couldn't open X11 display", window);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    पूर्णाङ्क xrandr_event_base, xrandr_error_base;
    window->xrandr = X11_XRRQueryExtension(window->display, &xrandr_event_base, &xrandr_error_base);
#endif

#ifndef NO_SHARED_MEMORY
    window->shm_pixmap = False;
    window->shm = X11_XShmQueryExtension(window->display) ? SDL_X11_HAVE_SHM : false;
    यदि (window->shm) {
        पूर्णाङ्क major;
        पूर्णाङ्क minor;

        X11_XShmQueryVersion(window->display, &major, &minor, &window->shm_pixmap);
        यदि (window->shm_pixmap) {
            यदि (X11_XShmPixmapFormat(window->display) != ZPixmap) {
                window->shm_pixmap = False;
            }
        }
    }
#endif

    /* Scale/Xsettings */
    window->pixmap = false;
    window->xsettings_first_time = true;
    window->xsettings = xsettings_client_new(window->display, DefaultScreen(window->display), X11Toolkit_SettingsNotify, रिक्त, window);
    window->xsettings_first_time = false;
    window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
    यदि (window->scale < 1) {
        window->scale = 1;
    }
    window->iscale = (पूर्णाङ्क)SDL_ceilf(window->scale);
    यदि (SDL_roundf(window->scale) == window->scale) {
        window->scale = 0;
    }

    /* Fonts */
    X11Toolkit_InitWindowFonts(window);

    /* Color hints */
#ifdef SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    यदि (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#endif

    यदि (!colorhints) {
#ifdef SDL_USE_LIBDBUS
        विकल्प (theme) {
            पक्ष SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                भङ्ग;
#यदि 0
            पक्ष SDL_SYSTEM_THEME_LIGHT_ऊपरी_CONTRAST:
                colorhints = g_default_colors_light_ऊपरी_contrast;
                भङ्ग;
            पक्ष SDL_SYSTEM_THEME_DARK_ऊपरी_CONTRAST:
                colorhints = g_default_colors_dark_ऊपरी_contrast;
                भङ्ग;
#endif
            स्वभाव:
                colorhints = g_default_colors;
        }
#अन्यथा
        colorhints = g_default_colors;
#endif
    }
    window->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    प्रति (i = 0; i < SDL_MESSAGEBOX_COLOR_गिनती; i++) {
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
    यदि (parent) {
        SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(parent);
        window->screen = displaydata->screen;
    } अन्यथा {
        window->screen = DefaultScreen(window->display);
    }

    /* Visuals */
    यदि (mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        window->visual = parent->internal->visual;
        window->cmap = parent->internal->colormap;
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
        window->depth = window->vi.depth;
    } अन्यथा {
        window->visual = DefaultVisual(window->display, window->screen);
        window->cmap = DefaultColormap(window->display, window->screen);
        window->depth = DefaultDepth(window->display, window->screen);
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
    }

    /* Allocate colors */
    प्रति (i = 0; i < SDL_MESSAGEBOX_COLOR_गिनती; i++) {
        X11_XAllocColor(window->display, window->cmap, &window->xcolor[i]);
    }
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l1);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l2);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_d);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_pressed);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_disabled_text);

    /* Control list */
    window->has_focus = false;
    window->controls = रिक्त;
    window->controls_sz = 0;
    window->dyn_controls_sz = 0;
    window->fiddled_control = रिक्त;
    window->dyn_controls = रिक्त;

    /* Menu windows */
    window->popup_windows = रिक्त;

    /* BIDI engine */
#ifdef HAVE_FRIBIDI_H
    window->fribidi = SDL_FriBidi_Create();
#endif

#ifdef HAVE_LIBTHAI_H
    window->th = SDL_LibThai_Create();
#endif
    
    /* Interface direction */
    window->flip_interface = X11Toolkit_ShouldFlipUI();
    
    प्रत्यागम window;
}

स्थिर शून्य X11Toolkit_AddControlToWindow(SDL_ToolkitWindowX11 *window, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    window->controls_sz++;
    यदि (window->controls_sz == 1) {
        window->controls = (संरचना SDL_ToolkitControlX11 **)SDL_malloc(परिमाण(संरचना SDL_ToolkitControlX11 *));
    } अन्यथा {
        window->controls = (संरचना SDL_ToolkitControlX11 **)SDL_realloc(window->controls, परिमाण(संरचना SDL_ToolkitControlX11 *) * window->controls_sz);
    }
    window->controls[window->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    यदि (control->dynamic) {
        window->dyn_controls_sz++;
        यदि (window->dyn_controls_sz == 1) {
            window->dyn_controls = (संरचना SDL_ToolkitControlX11 **)SDL_malloc(परिमाण(संरचना SDL_ToolkitControlX11 *));
        } अन्यथा {
            window->dyn_controls = (संरचना SDL_ToolkitControlX11 **)SDL_realloc(window->dyn_controls, परिमाण(संरचना SDL_ToolkitControlX11 *) * window->dyn_controls_sz);
        }
        window->dyn_controls[window->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    यदि (control->selected) {
        window->focused_control = control;
    }
}

bool X11Toolkit_CreateWindowRes(SDL_ToolkitWindowX11 *data, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क cx, पूर्णाङ्क cy, वर्ण *title)
{
    पूर्णाङ्क x, y;
    XSizeHints *sizehints;
    XSetWindowAttributes wnd_attr;
    Atom _NET_WM_WINDOW_TYPE, _NET_WM_WINDOW_TYPE_DIALOG, _NET_WM_WINDOW_TYPE_DROPDOWN_MENU, _NET_WM_WINDOW_TYPE_TOOLTIP;
    SDL_WindowData *windowdata = रिक्त;
    Display *display = data->display;
    XGCValues ctx_vals;
    Window मूल_win;
    Window parent_win;
    अचिन्हित दीर्घ gcflags = GCForeground | GCBackground;
    अचिन्हित दीर्घ valuemask;
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
#ifdef XRANDR_DISABLED_BY_DEFAULT
    ध्रुव bool use_xrandr_by_default = false;
#अन्यथा
    ध्रुव bool use_xrandr_by_default = true;
#endif
#endif

    यदि (data->scale == 0) {
        data->window_width = w;
        data->window_height = h;
    } अन्यथा {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        data->pixmap = true;
    }

    यदि (data->parent) {
        windowdata = data->parent->internal;
    }

    valuemask = CWEventMask | CWColormap;
    data->event_mask = ExposureMask |
                       ButtonPressMask | ButtonReleaseMask | कुंजी_Press_Mask | कुंजी_Release_Mask |
                       StructureNotifyMask | FocusChangeMask | PointerMotionMask;
    wnd_attr.event_mask = data->event_mask;
    wnd_attr.colormap = data->cmap;
    यदि (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    मूल_win = मूल_Window(display, data->screen);
    यदि (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        parent_win = windowdata->xwindow;
    } अन्यथा {
        parent_win = मूल_win;
    }

    data->window = X11_XCreateWindow(
        display, parent_win,
        0, 0,
        data->window_width, data->window_height,
        0, data->depth, निवेश_Output, data->visual,
        valuemask, &wnd_attr);
    यदि (data->window == None) {
        प्रत्यागम SDL_SetError("Couldn't create X window");
    }

    यदि (windowdata && data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        Atom _NET_WM_STATE = X11_XInternAtom(display, "_NET_WM_STATE", False);
        Atom stateatoms[16];
        माप_प्रकार statecount = 0;
        // Set some message-boxy window states when attached to a parent window...
        // we skip the taskbar since this will pop to the front when the parent window is clicked in the taskbar, etc
        stateatoms[statecount++] = X11_XInternAtom(display, "_NET_WM_STATE_SKIP_TASKBAR", False);
        stateatoms[statecount++] = X11_XInternAtom(display, "_NET_WM_STATE_SKIP_PAGER", False);
        stateatoms[statecount++] = X11_XInternAtom(display, "_NET_WM_STATE_FOCUSED", False);
        stateatoms[statecount++] = X11_XInternAtom(display, "_NET_WM_STATE_MODAL", False);
        SDL_assert(statecount <= SDL_arraysize(stateatoms));
        X11_XChangeProperty(display, data->window, _NET_WM_STATE, XA_ATOM, 32,
                            PropModeReplace, (अचिन्हित वर्ण *)stateatoms, statecount);
    }

    यदि (windowdata && data->mode != SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        X11_XSetTransientForHint(display, data->window, windowdata->xwindow);
    }

    यदि (data->tk_parent) {
        X11_XSetTransientForHint(display, data->window, data->tk_parent->window);
    }

    SDL_X11_SetWindowTitle(display, data->window, title);

    // Let the window manager the type of the window
    यदि (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (अचिन्हित वर्ण *)&_NET_WM_WINDOW_TYPE_DIALOG, 1);
    } अन्यथा यदि (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (अचिन्हित वर्ण *)&_NET_WM_WINDOW_TYPE_DROPDOWN_MENU, 1);
    } अन्यथा यदि (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (अचिन्हित वर्ण *)&_NET_WM_WINDOW_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    data->wm_delete_message = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, data->window, &data->wm_delete_message, 1);
    data->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    यदि (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        x = cx;
        y = cy;
        गच्छ MOVEWINDOW;
    }
    यदि (windowdata) {
        XWindowAttributes attrib;
        Window dummy;

        X11_XGetWindowAttributes(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.width - data->window_width) / 2;
        y = attrib.y + (attrib.height - data->window_height) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, मूल_Window(display, data->screen), x, y, &x, &y, &dummy);
    } अन्यथा {
        ध्रुव SDL_VideoDevice *dev = SDL_GetVideoDevice();
        यदि (dev && dev->displays && dev->अंक_displays > 0) {
            ध्रुव SDL_VideoDisplay *dpy = dev->displays[0];
            ध्रुव SDL_DisplayData *dpydata = dpy->internal;
            x = dpydata->x + ((dpy->current_mode->w - data->window_width) / 2);
            y = dpydata->y + ((dpy->current_mode->h - data->window_height) / 3);
        }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
        अन्यथा यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && data->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_out;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, मूल_win);
            यदि (!screen_res) {
                गच्छ NOXRANDR;
            }

            default_out = X11_XRRGetOutputPrimary(display, मूल_win);
            यदि (default_out != None) {
                XRROutputInfo *out_info;

                out_info = X11_XRRGetOutputInfo(display, screen_res, default_out);
                यदि (out_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(out_info);
                    गच्छ FIRSTOUTPUTXRANDR;
                }

                यदि (out_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                } अन्यथा यदि (out_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                } अन्यथा {
                    crtc_info = रिक्त;
                }
                
                यदि (crtc_info) {
                    x = (crtc_info->width - data->window_width) / 2;
                    y = (crtc_info->height - data->window_height) / 3;
                    X11_XRRFreeOutputInfo(out_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } अन्यथा {
                    X11_XRRFreeOutputInfo(out_info);
                    गच्छ NOXRANDR;
                }
            } अन्यथा {
                    FIRSTOUTPUTXRANDR:
                    यदि (screen_res->noutput > 0) {
                        XRROutputInfo *out_info;

                        out_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        यदि (!out_info) {
                            गच्छ FIRSTCRTCXRANDR;
                        }

                        यदि (out_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                        } अन्यथा यदि (out_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                        } अन्यथा {
                            crtc_info = रिक्त;
                        }

                        यदि (!crtc_info) {
                            X11_XRRFreeOutputInfo(out_info);
                            गच्छ FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeOutputInfo(out_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        गच्छ MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    यदि (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        गच्छ NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    यदि (crtc_info) {
                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } अन्यथा {
                        X11_XRRFreeScreenResources(screen_res);
                        गच्छ NOXRANDR;
                    }
            }
        }
#endif
        अन्यथा {
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
    यदि (sizehints) {
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
    यदि (SDL_X11_HAVE_XDBE && !data->pixmap) {
        पूर्णाङ्क xdbe_major, xdbe_minor;
        यदि (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            data->xdbe = true;
            data->buf = X11_XdbeAllocateBackBufferName(display, data->window, XdbeUndefined);
            data->drawable = data->buf;
        } अन्यथा {
            data->xdbe = false;
        }
    }
#endif

    X11Toolkit_InitWindowPixmap(data);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    यदि (!data->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = data->font_struct->fid;
    }
    data->ctx = X11_XCreateGC(data->display, data->drawable, gcflags, &ctx_vals);
    यदि (data->ctx == None) {
        प्रत्यागम SDL_SetError("Couldn't create graphics context");
    }

    data->बंद = false;
    data->कुंजी_control_esc = data->कुंजी_control_enter = रिक्त;
    यदि (!data->pixmap) {
        data->ev_scale = data->ev_iscale = 1;
    } अन्यथा {
        data->ev_scale = data->scale;
        data->ev_iscale = data->iscale;
    }

#यदि SDL_GRAB
    यदि (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XGrabPointer(display, data->window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
        X11_XGrabKeyboard(display, data->window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
#endif

    प्रत्यागम true;
}

स्थिर शून्य X11Toolkit_DrawWindow(SDL_ToolkitWindowX11 *data) {
    SDL_Rect rect;
    पूर्णाङ्क i;

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    यदि (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeBeginIdiom(data->display);
    }
#endif

    X11_XSetForeground(data->display, data->ctx, data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    यदि (data->pixmap) {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->pixmap_width, data->pixmap_height);
    } अन्यथा {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->window_width, data->window_height);
    }

    प्रति (i = 0; i < data->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = data->controls[i];
        यदि (control) {
            यदि (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    यदि (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        XdbeSwapInfo swap_info;
        swap_info.swap_window = data->window;
        swap_info.swap_action = XdbeUndefined;
        X11_XdbeSwapBuffers(data->display, &swap_info, 1);
        X11_XdbeEndIdiom(data->display);
    }
#endif

    यदि (data->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = data->window_width;
        rect.h = data->window_height;
#ifndef NO_SHARED_MEMORY
        यदि (data->shm) {
            यदि (data->shm_pixmap) {
                X11_XFlush(data->display);
                X11_XSync(data->display, false);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->shm_info.shmaddr, data->shm_bytes_per_पंक्ति);
                SDL_BlitSurfaceScaled(scale_surface, रिक्त, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(data->display, data->drawable, data->window, data->ctx, 0, 0, data->window_width, data->window_height, 0, 0);
            } अन्यथा {
                X11_XShmGetImage(data->display, data->drawable, data->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->image->data, data->image->bytes_per_पंक्ति);
                SDL_BlitSurfaceScaled(scale_surface, रिक्त, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                X11_XShmPutImage(data->display, data->window, data->ctx, data->image, 0, 0, 0, 0, data->window_width, data->window_height, False);
            }
        } अन्यथा
#endif
        {
            XImage *image;

            image = X11_XGetImage(data->display, data->drawable, 0, 0 , data->pixmap_width, data->pixmap_height, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), image->data, image->bytes_per_पंक्ति);
            SDL_BlitSurfaceScaled(scale_surface, रिक्त, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
            X11_XPutImage(data->display, data->window, data->ctx, image, 0, 0, 0, 0, data->window_width, data->window_height);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(data->display);
}

स्थिर SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_ToolkitWindowX11 *data, पूर्णाङ्क x, पूर्णाङ्क y)
{
    पूर्णाङ्क i;

    प्रति (i = 0; i < data->controls_sz; i++) {
        SDL_Rect *rect = &data->controls[i]->rect;
        यदि ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            प्रत्यागम data->controls[i];
        }
    }

    प्रत्यागम रिक्त;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
स्थिर Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_ToolkitWindowX11 *data = (SDL_ToolkitWindowX11 *)arg;

    यदि (event->xany.display != data->display) {
        प्रत्यागम False;
    }

    यदि (event->xany.window == data->window) {
        प्रत्यागम True;
    }

    प्रत्यागम False;
}

शून्य X11Toolkit_ProcessWindowEvents(SDL_ToolkitWindowX11 *data, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    यदि ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        प्रत्यागम;
    }

    data->draw = false;
    data->e = e;

    विकल्प (e->type) {
        पक्ष Expose:
            data->draw = true;
            भङ्ग;
        पक्ष ClientMessage:
            यदि (e->xclient.message_type == data->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.data.l[0] == data->wm_delete_message) {
                data->बंद = true;
            }
            भङ्ग;
        पक्ष FocusIn:
            data->has_focus = true;
            भङ्ग;
        पक्ष FocusOut:
            data->has_focus = false;
            यदि (data->fiddled_control) {
                data->fiddled_control->selected = false;
            }
            data->fiddled_control = रिक्त;
            प्रति (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
            }
            भङ्ग;
        पक्ष MotionNotify:
            यदि (data->has_focus) {
                data->previous_control = data->fiddled_control;
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                यदि (data->previous_control) {
                    data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    यदि (data->previous_control->func_on_state_change) {
                        data->previous_control->func_on_state_change(data->previous_control);
                    }
                    data->draw = true;
                }
                यदि (data->fiddled_control) {
                    यदि (data->fiddled_control->dynamic) {
                        data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        यदि (data->fiddled_control->func_on_state_change) {
                            data->fiddled_control->func_on_state_change(data->fiddled_control);
                        }
                        data->draw = true;
                    } अन्यथा {
                        data->fiddled_control = रिक्त;
                    }
                }
            }
            भङ्ग;
        पक्ष ButtonPress:
            data->previous_control = data->fiddled_control;
            यदि (data->previous_control) {
                data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                यदि (data->previous_control->func_on_state_change) {
                    data->previous_control->func_on_state_change(data->previous_control);
                }
                data->draw = true;
            }
            यदि (e->xbutton.button == Button1) {
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                यदि (data->fiddled_control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    यदि (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->draw = true;
                }
            }
            भङ्ग;
        पक्ष ButtonRelease:
            यदि (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
                पूर्णाङ्क cx;
                पूर्णाङ्क cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                यदि (cy < 0 || cx < 0) {
                    data->बंद = true;
                }

                यदि (cy > data->window_height || cx > data->window_width) {
                    data->बंद = true;
                }
            }

            यदि ((e->xbutton.button == Button1) && (data->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                यदि (data->fiddled_control == control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    यदि (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    data->draw = true;
                }
            }
            भङ्ग;
        पक्ष कुंजी_Press:
            data->last_कुंजी_pressed = X11_XLookupKeysym(&e->xkey, 0);

            यदि (data->last_कुंजी_pressed == XK_Escape) {
                प्रति (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    यदि(data->controls[data->ev_i]->is_default_esc) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->कुंजी_control_esc = data->controls[data->ev_i];
                    }
                }
            } अन्यथा यदि ((data->last_कुंजी_pressed == XK_Return) || (data->last_कुंजी_pressed == XK_KP_Enter)) {
                प्रति (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    यदि(data->controls[data->ev_i]->selected) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->कुंजी_control_enter = data->controls[data->ev_i];
                    }
                }
            }
            भङ्ग;
        पक्ष कुंजी_Release:
        {
            कुंजी_Sym कुंजी = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            यदि (कुंजी != data->last_कुंजी_pressed) {
                भङ्ग;
            }

            यदि (कुंजी == XK_Escape) {
                यदि (data->कुंजी_control_esc) {
                    यदि (data->कुंजी_control_esc->func_on_state_change) {
                        data->कुंजी_control_esc->func_on_state_change(data->कुंजी_control_esc);
                    }
                }
            } अन्यथा यदि ((कुंजी == XK_Return) || (कुंजी == XK_KP_Enter)) {
                यदि (data->कुंजी_control_enter) {
                    यदि (data->कुंजी_control_enter->func_on_state_change) {
                        data->कुंजी_control_enter->func_on_state_change(data->कुंजी_control_enter);
                    }
                }
            } अन्यथा यदि (कुंजी == XK_Tab || कुंजी == XK_बायाँ || कुंजी == XK_दायाँ) {
                यदि (data->focused_control) {
                    data->focused_control->selected = false;
                }
                data->draw = true;
                प्रति (data->ev_i = 0; data->ev_i < data->dyn_controls_sz; data->ev_i++) {
                    यदि (data->dyn_controls[data->ev_i] == data->focused_control) {
                        पूर्णाङ्क next_index;

                        यदि (कुंजी == XK_बायाँ) {
                            next_index = data->ev_i - 1;
                        } अन्यथा {
                            next_index = data->ev_i + 1;
                        }
                        यदि ((next_index >= data->dyn_controls_sz) || (next_index < 0)) {
                            यदि (कुंजी == XK_दायाँ || कुंजी == XK_बायाँ) {
                                next_index = data->ev_i;
                            } अन्यथा {
                                next_index = 0;
                            }
                        }
                        data->focused_control = data->dyn_controls[next_index];
                        data->focused_control->selected = true;
                        भङ्ग;
                    }
                }
            }
            भङ्ग;
        }
    }

    यदि (data->draw) {
        X11Toolkit_DrawWindow(data);
    }
}

शून्य X11Toolkit_DoWindowEventLoop(SDL_ToolkitWindowX11 *data) {
   यावत् (!data->बंद) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(data->display, &e);
        यदि (data->xsettings) {
            xsettings_client_process_event(data->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(data->display, &e, X11Toolkit_EventTest, (XPointer)data);
        X11Toolkit_ProcessWindowEvents(data, &e);
    }
}


शून्य X11Toolkit_ResizeWindow(SDL_ToolkitWindowX11 *data, पूर्णाङ्क w, पूर्णाङ्क h) {
    यदि (!data->pixmap) {
        data->window_width = w;
        data->window_height = h;
    } अन्यथा {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        X11_XFreePixmap(data->display, data->drawable);
        X11Toolkit_InitWindowPixmap(data);
    }

    X11_XResizeWindow(data->display, data->window, data->window_width, data->window_height);
}

स्थिर शून्य X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->window->display, icon_control->icon_char_font);
    SDL_free(control);
}

स्थिर शून्य X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->window->iscale;
    control->rect.h -= 2 * control->window->iscale;
    X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + (2 * control->window->iscale), control->rect.y + (2* control->window->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    विकल्प (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        पक्ष SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                भङ्ग;
        पक्ष SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                भङ्ग;
        पक्ष SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                भङ्ग;
    }
    X11_XSetFont(control->window->display, control->window->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    यदि (!control->window->utf8) {
        X11_XSetFont(control->window->display, control->window->ctx, control->window->font_struct->fid);
    }

    control->rect.w += 2 * control->window->iscale;
    control->rect.h += 2 * control->window->iscale;
}

स्थिर शून्य X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    पूर्णाङ्क icon_char_w;
    पूर्णाङ्क icon_wh;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11Toolkit_GetTextWidthHeightForFont(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, रिक्त);
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

स्थिर शून्य X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    वर्ण *font;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11_XFreeFont(base_control->window->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_SIZE * base_control->window->iscale);
    control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
    SDL_free(font);
    यदि (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * base_control->window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_ToolkitWindowX11 *window, SDL_MessageBoxFlags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    वर्ण *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(परिमाण(SDL_ToolkitIconControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    यदि (!control) {
        SDL_SetError("Unable to allocate icon control structure");
        प्रत्यागम रिक्त;
    }

    /* Fill out struct */
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawIconControl;
    base_control->func_free = X11Toolkit_DestroyIconControl;
    base_control->func_on_state_change = रिक्त;
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
    यदि (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        यदि (!control->icon_char_font) {
            SDL_free(control);
            प्रत्यागम रिक्त;
        }
    }

    /* Set colors */
    विकल्प (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    पक्ष SDL_MESSAGEBOX_ERROR:
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
        भङ्ग;
    पक्ष SDL_MESSAGEBOX_WARNING:
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
        भङ्ग;
    पक्ष SDL_MESSAGEBOX_INFORMATION:
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
        भङ्ग;
    स्वभाव:
        X11_XFreeFont(window->display, control->icon_char_font);
        SDL_free(control);
        प्रत्यागम रिक्त;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    यदि (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } अन्यथा यदि (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } अन्यथा {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    यदि (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } अन्यथा यदि (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } अन्यथा {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    यदि (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } अन्यथा यदि (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } अन्यथा {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(window->display, window->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(base_control);

    X11Toolkit_AddControlToWindow(window, base_control);
    प्रत्यागम base_control;
}

bool X11Toolkit_NotifyControlOfSizeChange(SDL_ToolkitControlX11 *control) {
    यदि (control->func_calc_size) {
        control->func_calc_size(control);
        प्रत्यागम true;
    } अन्यथा {
        प्रत्यागम false;
    }
}

स्थिर शून्य X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11Toolkit_GetTextElementsRect(button_control->text, &button_control->text_rect);
    यदि (control->do_size) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.h;
    }
    button_control->text_rect.x = (control->rect.w - button_control->text_rect.w)/2;
    button_control->text_rect.y = (control->rect.h - button_control->text_rect.h)/2;
}


स्थिर शून्य X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    /* Draw bevel */
    यदि (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
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
        } अन्यथा {
            यदि (control->selected) {
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
            } अन्यथा {
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

स्थिर शून्य X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    यदि (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_data);
    }
}

स्थिर शून्य X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11Toolkit_FreeTextElements(button_control->text);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_ToolkitWindowX11 *window, ध्रुव SDL_MessageBoxButtonData *data) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *base_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(परिमाण(SDL_ToolkitButtonControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    यदि (!control) {
        SDL_SetError("Unable to allocate button control structure");
        प्रत्यागम रिक्त;
    }
    base_control->window = window;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->func_calc_size = X11Toolkit_CalculateButtonControl;
    base_control->func_draw = X11Toolkit_DrawButtonControl;
    base_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    base_control->func_free = X11Toolkit_DestroyButtonControl;
    base_control->func_on_scale_change = रिक्त;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = true;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    यदि (data->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        base_control->is_default_esc = true;
    }
    यदि (data->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        base_control->is_default_enter = true;
        base_control->selected = true;
    }
    control->cb = रिक्त;
    control->data = data;
#ifdef HAVE_FRIBIDI_H
    control->text = X11Toolkit_MakeTextElements(base_control->window, (वर्ण *)control->data->text, SDL_strlen(control->data->text), रिक्त);
#अन्यथा 
    control->text = X11Toolkit_MakeTextElements(base_control->window, (वर्ण *)control->data->text, SDL_strlen(control->data->text));
#endif
    X11Toolkit_ShapeTextElements(base_control->window, control->text);
    
    base_control->do_size = true;
    X11Toolkit_CalculateButtonControl(base_control);
    base_control->do_size = false;

    X11Toolkit_AddControlToWindow(window, base_control);
    प्रत्यागम base_control;
}

शून्य X11Toolkit_RegisterCallbackForButtonControl(SDL_ToolkitControlX11 *control, शून्य *data, शून्य (*cb)(संरचना SDL_ToolkitControlX11 *, शून्य *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_data = data;
    button_control->cb = cb;
}

ध्रुव SDL_MessageBoxButtonData *X11Toolkit_GetButtonControlData(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    प्रत्यागम button_control->data;
}

शून्य X11Toolkit_DestroyWindow(SDL_ToolkitWindowX11 *data) {
    पूर्णाङ्क i;

    यदि (!data) {
        प्रत्यागम;
    }

#यदि SDL_GRAB
    यदि (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XUngrabPointer(data->display, CurrentTime);
        X11_XUngrabKeyboard(data->display, CurrentTime);
    }
#endif

    प्रति (i = 0; i < data->controls_sz; i++) {
        यदि (data->controls[i]->func_free) {
            data->controls[i]->func_free(data->controls[i]);
        }
    }
    SDL_free(data->controls);
    SDL_free(data->dyn_controls);

    यदि (data->popup_windows) {
        SDL_ListClear(&data->popup_windows);
    }

    यदि (data->pixmap) {
        X11_XFreePixmap(data->display, data->drawable);
    }

#ifndef NO_SHARED_MEMORY
    यदि (data->pixmap && data->shm) {
        X11_XShmDetach(data->display, &data->shm_info);
        यदि (!data->shm_pixmap) {
            XDestroyImage(data->image);
        }
        shmdt(data->shm_info.shmaddr);
    }
#endif

#ifdef X_HAVE_UTF8_STRING
    यदि (data->font_set) {
        X11_XFreeFontSet(data->display, data->font_set);
        data->font_set = रिक्त;
    }
#endif

    यदि (data->font_struct) {
        X11_XFreeFont(data->display, data->font_struct);
        data->font_struct = रिक्त;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    यदि (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeDeallocateBackBufferName(data->display, data->buf);
    }
#endif

    यदि (data->xsettings) {
        xsettings_client_destroy(data->xsettings);
    }

    X11_XFreeGC(data->display, data->ctx);

    यदि (data->display) {
        यदि (data->window != None) {
            X11_XWithdrawWindow(data->display, data->window, data->screen);
            X11_XDestroyWindow(data->display, data->window);
            data->window = None;
        }

        यदि (data->display_close) {
            X11_XCloseDisplay(data->display);
        }
        data->display = रिक्त;
    }

#यदि SDL_SET_LOCALE
    यदि (data->origlocale && (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG)) {
        (शून्य)रखो_क्षेत्र(LC_ALL, data->origlocale);
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

स्थिर पूर्णाङ्क X11_Toolkit_गिनती_पंक्तियाँ_Of_Text(ध्रुव वर्ण *text)
{
    पूर्णाङ्क result = 0;
    यावत् (text && *text) {
        ध्रुव वर्ण *lf = SDL_strchr(text, '\n');
        result++; // even without an endline, this counts as a line.
        text = lf ? lf + 1 : रिक्त;
    }
    प्रत्यागम result;
}

स्थिर शून्य X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    पूर्णाङ्क i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    प्रति (i = 0; i < label_control->sz; i++) {
        X11Toolkit_DrawTextElements(control->window, label_control->पंक्तियाँ[i].text, control->rect.x + label_control->पंक्तियाँ[i].rect.x, control->rect.y + label_control->पंक्तियाँ[i].rect.y);
    }
}

स्थिर शून्य X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    पूर्णाङ्क i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    प्रति (i = 0; i < label_control->sz; i++) {
        X11Toolkit_FreeTextElements(label_control->पंक्तियाँ[i].text);
    }
    SDL_free(label_control->पंक्तियाँ);
    SDL_free(label_control);
}

स्थिर शून्य X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitLabelControlX11 *control;
    पूर्णाङ्क i;

    control = (SDL_ToolkitLabelControlX11 *)base_control;
    
    यदि (base_control->do_size) {
        base_control->rect.w = 0;
        base_control->rect.h = 0;
    }
    
    प्रति (i = 0; i < control->sz; i++) {
        पूर्णाङ्क font_h;
        
        font_h = X11Toolkit_GetTextElementsRect(control->पंक्तियाँ[i].text, &control->पंक्तियाँ[i].rect);
        
        यदि (base_control->do_size) {
            base_control->rect.w = SDL_max(base_control->rect.w, control->पंक्तियाँ[i].rect.w);
        }
        
        यदि (i > 0) {
            control->पंक्तियाँ[i].rect.y = font_h + control->पंक्तियाँ[i - 1].rect.y;
        } अन्यथा {
            control->पंक्तियाँ[i].rect.y = 0;
        }
    }

#ifdef HAVE_FRIBIDI_H
    यदि (base_control->window->fribidi) {
        FriBidiParType first_ndn_dir;
        पूर्णाङ्क last_ndn;
    
        first_ndn_dir = FRIBIDI_PAR_LTR;
        प्रति (i = 0; i < control->sz; i++) {
            यदि (control->पंक्तियाँ[i].par != FRIBIDI_PAR_ON) {
                first_ndn_dir = control->पंक्तियाँ[i].par;
            }
        }

        last_ndn = -1;
        प्रति (i = 0; i < control->sz; i++) {
            विकल्प (control->पंक्तियाँ[i].par) {
                पक्ष FRIBIDI_PAR_LTR:
                    control->पंक्तियाँ[i].rect.x = 0;
                    last_ndn = i;
                    भङ्ग;
                पक्ष FRIBIDI_PAR_RTL:
                    control->पंक्तियाँ[i].rect.x = base_control->rect.w - control->पंक्तियाँ[i].rect.w;
                    last_ndn = i;
                    भङ्ग;
                स्वभाव:
                    यदि (last_ndn != -1) {
                        यदि (control->पंक्तियाँ[last_ndn].par == FRIBIDI_PAR_RTL) {
                            control->पंक्तियाँ[i].rect.x = base_control->rect.w - control->पंक्तियाँ[i].rect.w;
                        } अन्यथा {
                            control->पंक्तियाँ[i].rect.x = 0;
                        }
                    } अन्यथा {
                        यदि (first_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->पंक्तियाँ[i].rect.x = base_control->rect.w - control->पंक्तियाँ[i].rect.w;
                        } अन्यथा {
                            control->पंक्तियाँ[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#endif
    
    यदि (base_control->do_size && control->sz) {
        base_control->rect.h = control->पंक्तियाँ[control->sz - 1].rect.y + control->पंक्तियाँ[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_ToolkitWindowX11 *window, वर्ण *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    पूर्णाङ्क i;
    
    यदि (!utf8) {
        प्रत्यागम रिक्त;
    }
 
    यदि (!SDL_strcmp(utf8, "")) {
        प्रत्यागम रिक्त;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(परिमाण(SDL_ToolkitLabelControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    यदि (!control) {
        SDL_SetError("Unable to allocate label control structure");
        प्रत्यागम रिक्त;
    }
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawLabelControl;
    base_control->func_on_state_change = रिक्त;
    base_control->func_calc_size = X11Toolkit_CalculateLabelControl;
    base_control->func_free  = X11Toolkit_DestroyLabelControl;
    base_control->func_on_scale_change = रिक्त;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = false;
    base_control->rect.w = 0;
    base_control->rect.h = 0;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_गिनती_पंक्तियाँ_Of_Text(utf8);
    control->पंक्तियाँ = SDL_calloc(control->sz, परिमाण(SDL_Toolkit_Label_Control_पंक्ति_X11));
    प्रति (i = 0; i < control->sz; i++) {
        ध्रुव वर्ण *lf = SDL_strchr(utf8, '\n');
        ध्रुव पूर्णाङ्क length = lf ? (lf - utf8) : SDL_strlen(utf8);
        पूर्णाङ्क sz;
        
        sz = length;
        यदि (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#ifdef HAVE_FRIBIDI_H
        control->पंक्तियाँ[i].text = X11Toolkit_MakeTextElements(base_control->window, (वर्ण *)utf8, sz, &control->पंक्तियाँ[i].par);
#अन्यथा 
        control->पंक्तियाँ[i].text = X11Toolkit_MakeTextElements(base_control->window, (वर्ण *)utf8, sz);
#endif
        X11Toolkit_ShapeTextElements(base_control->window, control->पंक्तियाँ[i].text);

        utf8 += length + 1;
        यदि (!lf) {
            भङ्ग;
        }
    }

    base_control->do_size = true;
    X11Toolkit_CalculateLabelControl(base_control);
    base_control->do_size = false;
    X11Toolkit_AddControlToWindow(window, base_control);

    प्रत्यागम base_control;
}

पूर्णाङ्क X11_Toolkit_Get_Label_Control_First_पंक्ति_Height(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    प्रत्यागम label_control->पंक्तियाँ[0].rect.h;
}

शून्य X11Toolkit_SignalWindowClose(SDL_ToolkitWindowX11 *data) {
    data->बंद = true;
}

#endif // SDL_VIDEO_DRIVER_X11
