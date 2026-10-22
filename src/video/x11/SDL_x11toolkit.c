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

#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#અન્તર્ભાવ "../../SDL_list.h"
#અન્તર્ભાવ "SDL_x11video.h"
#ifdef SDL_USE_LIBDBUS
#અન્તર્ભાવ "../../core/linux/SDL_system_theme.h"
#endif
#ifdef HAVE_FRIBIDI_H
#અન્તર્ભાવ "../../core/unix/SDL_fribidi.h"
#endif
#અન્તર્ભાવ "SDL_x11dyn.h"
#અન્તર્ભાવ "SDL_x11toolkit.h"
#અન્તર્ભાવ "SDL_x11settings.h"
#અન્તર્ભાવ "SDL_x11modes.h"
#અન્તર્ભાવ "xsettings-client.h"
#અન્તર્ભાવ <X11/keysym.h>
#અન્તર્ભાવ <locale.h>

#define SDL_SET_LOCALE 1
#define SDL_GRAB 1

પ્રકારવ્યાખ્યા ગણના SDL_ToolkitTextTypeX11
{
    SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC,
    SDL_TOOLKIT_TEXT_TYPE_X11_THAI
} SDL_ToolkitTextTypeX11;

#ifdef HAVE_LIBTHAI_H
પ્રકારવ્યાખ્યા સંરચના SDL_ToolkitThaiOverlayX11
{
    bool ટોચ;
    અક્ષર *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#endif

પ્રકારવ્યાખ્યા સંરચના SDL_ToolkitTextElementX11
{
    SDL_ToolkitTextTypeX11 type;
    અક્ષર *str;
    size_t sz;
    SDL_Rect rect;
    પૂર્ણાંક font_h;
    શૂન્ય (*str_free)(શૂન્ય *);
#ifdef HAVE_LIBTHAI_H
    SDL_List_ગાંઠ *thai_overlays;
#endif
} SDL_ToolkitTextElementX11;

પ્રકારવ્યાખ્યા સંરચના SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Icon type */
    SDL_MessageBoxFlags flags;
    અક્ષર icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    પૂર્ણાંક icon_char_x;
    પૂર્ણાંક icon_char_y;
    પૂર્ણાંક icon_char_a;
    પૂર્ણાંક icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

પ્રકારવ્યાખ્યા સંરચના SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Data */
    અચલ SDL_MessageBoxButtonData *data;

    /* Text */
    SDL_List_ગાંઠ *text;
    SDL_Rect text_rect;
    
    /* Callback */
    શૂન્ય *cb_data;
    શૂન્ય (*cb)(સંરચના SDL_ToolkitControlX11 *, શૂન્ય *);
} SDL_ToolkitButtonControlX11;

પ્રકારવ્યાખ્યા સંરચના SDL_Toolkit_Label_Control_લીટી_X11
{
    SDL_List_ગાંઠ *text;
    SDL_Rect rect;
#ifdef HAVE_FRIBIDI_H
    FriBidiParType par;
#endif
} SDL_Toolkit_Label_Control_લીટી_X11;

પ્રકારવ્યાખ્યા સંરચના SDL_ToolkitLabelControlX11
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
    SDL_Toolkit_Label_Control_લીટી_X11 *લીટીઓ;
    size_t sz;
} SDL_ToolkitLabelControlX11;

પ્રકારવ્યાખ્યા સંરચના SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_ગાંઠ *menu_વસ્તુઓ;
} SDL_ToolkitMenuBarControlX11;

પ્રકારવ્યાખ્યા સંરચના SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_ગાંઠ *menu_વસ્તુઓ;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
સ્થિર અચલ અક્ષર *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#define G_ICONFONT_SIZE 22

/* General UI font */
સ્થિર અચલ અક્ષર g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
સ્થિર અચલ અક્ષર g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

સ્થિર અચલ અક્ષર *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    ખાલી
};
#define G_TOOLKITFONT_SIZE 140

સ્થિર અચલ SDL_MessageBoxColor g_default_colors[SDL_MESSAGEBOX_COLOR_ગણતરી] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ifdef SDL_USE_LIBDBUS
સ્થિર અચલ SDL_MessageBoxColor g_default_colors_dark[SDL_MESSAGEBOX_COLOR_ગણતરી] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#જો 0
સ્થિર અચલ SDL_MessageBoxColor g_default_colors_dark_ઉપલું_contrast[SDL_MESSAGEBOX_COLOR_ગણતરી] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

સ્થિર અચલ SDL_MessageBoxColor g_default_colors_light_ઉપલું_contrast[SDL_MESSAGEBOX_COLOR_ગણતરી] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#endif

#endif

સ્થિર પૂર્ણાંક g_shm_error;
સ્થિર પૂર્ણાંક (*g_old_error_handler)(Display *, XErrorEvent *) = ખાલી;

સ્થિર પૂર્ણાંક X11Toolkit_SharedMemoryErrorHandler(Display *d, XErrorEvent *e)
{
    જો (e->error_code == BadAccess || e->error_code == BadRequest) {
        g_shm_error = True;
        પાછા 0;
    }
    પાછા g_old_error_handler(d, e);
}

સ્થિર શૂન્ય X11Toolkit_InitWindowPixmap(SDL_ToolkitWindowX11 *data) {
    જો (data->pixmap) {
#ifndef NO_SHARED_MEMORY
        જો (!data->shm_pixmap) {
            data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
        }
#નહીંતર
        data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
#endif
#ifndef NO_SHARED_MEMORY
        જો (data->shm) {
            data->image = X11_XShmCreateImage(data->display, data->visual, data->depth, ZPixmap, ખાલી, &data->shm_info, data->pixmap_width, data->pixmap_height);
            જો (data->image) {
                data->shm_bytes_per_લીટી = data->image->bytes_per_લીટી;

                data->shm_info.shmid = shmget(IPC_PRIVATE, data->image->bytes_per_લીટી * data->image->height, IPC_CREAT | 0777);
                જો (data->shm_info.shmid < 0) {
                    XDestroyImage(data->image);
                    data->image = ખાલી;
                    data->shm = false;
                    પાછા;
                }

                data->shm_info.readOnly = False;
                data->shm_info.shmaddr = data->image->data = (અક્ષર *)shmat(data->shm_info.shmid, ખાલી, 0);
                જો (((signed અક્ષર *)data->shm_info.shmaddr) == (signed અક્ષર *)-1) {
                    XDestroyImage(data->image);
                    data->shm = false;
                    data->image = ખાલી;
                    પાછા;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11Toolkit_SharedMemoryErrorHandler);
                X11_XShmAttach(data->display, &data->shm_info);
                X11_XSync(data->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                જો (g_shm_error) {
                    XDestroyImage(data->image);
                    shmdt(data->shm_info.shmaddr);
                    shmctl(data->shm_info.shmid, IPC_RMID, ખાલી);
                    data->image = ખાલી;
                    data->shm = false;
                    પાછા;
                }

                જો (data->shm_pixmap) {
                    data->drawable = X11_XShmCreatePixmap(data->display, data->window, data->shm_info.shmaddr, &data->shm_info, data->pixmap_width, data->pixmap_height, data->depth);
                    જો (data->drawable == None) {
                        data->shm_pixmap = False;
                    } નહીંતર {
                        XDestroyImage(data->image);
                        data->image = ખાલી;
                    }
                }

                shmctl(data->shm_info.shmid, IPC_RMID, ખાલી);
            } નહીંતર {
                data->shm = false;
            }
        }
#endif
    }
}

સ્થિર શૂન્ય X11Toolkit_InitWindowFonts(SDL_ToolkitWindowX11 *window)
{    
    window->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    window->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#ifdef X_HAVE_UTF8_STRING
    window->utf8 = true;
    window->font_set = ખાલી;
    જો (SDL_X11_HAVE_UTF8) {
        અક્ષર **missing = ખાલી;
        પૂર્ણાંક અંક_missing = 0;
        પૂર્ણાંક i_font;
        window->font_struct = ખાલી;
        માટે (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            અક્ષર *font;

            જો (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_load_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_SIZE * window->iscale);
                window->font_set = X11_XCreateFontSet(window->display, font, &missing, &અંક_missing, ખાલી);
                SDL_free(font);

                જો (!window->font_set) {
                    જો (window->scale != 0 && window->iscale > 0) {
                        window->iscale = (પૂર્ણાંક)SDL_ceilf(window->scale);
                        window->scale = 0;
                    } નહીંતર {
                        window->iscale--;
                    }
                    જાઓ try_load_font;
                }
            } નહીંતર {
                window->font_set = X11_XCreateFontSet(window->display, g_ToolkitFont[i_font], &missing, &અંક_missing, ખાલી);
            }

            જો (missing) {
                X11_XFreeStringList(missing);
            }

            જો (window->font_set) {
                તોડો;
            }
        }

        જો (!window->font_set) {
            જાઓ load_font_traditional;
        } નહીંતર {
            XFontStruct **font_structs;
            અક્ષર **font_names;
            પૂર્ણાંક font_sz;
            પૂર્ણાંક i;
            
#ifdef HAVE_FRIBIDI_H
            window->do_shaping = !X11_XContextDependentDrawing(window->font_set);
#endif
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFontsOfFontSet(window->font_set, &font_structs, &font_names);
            માટે (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                જો (SDL_strstr(font_names[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } નહીંતર જો (SDL_strstr(font_names[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } નહીંતર જો (SDL_strstr(font_names[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } નહીંતર જો (SDL_strstr(font_names[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } નહીંતર જો (SDL_strstr(font_names[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                જો (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(window->display, font_names[i]);
                    જો (font_struct) {
                        જો (font_struct->per_char) {
                            પૂર્ણાંક glyphs_sz;
                            પૂર્ણાંક j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            માટે (j = 0; j < glyphs_sz; j++) {
                                જો (font_struct->per_char[j].lbearing < 0) {
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
    } નહીંતર
#endif
    {
        અક્ષર *font;

        load_font_traditional:
        window->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        window->font_struct = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        જો (!window->font_struct) {
            જો (window->iscale > 0) {
                જો (window->scale != 0) {
                    window->iscale = (પૂર્ણાંક)SDL_ceilf(window->scale);
                    window->scale = 0;
                } નહીંતર {
                    window->iscale--;
                }
                જાઓ load_font_traditional;
            } નહીંતર {
                window->font_struct = X11_XLoadQueryFont(window->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

સ્થિર શૂન્ય X11Toolkit_SettingsNotify(અચલ અક્ષર *name, XSettingsAction action, XSettingsSetting *setting, શૂન્ય *data)
{
    SDL_ToolkitWindowX11 *window;
    પૂર્ણાંક i;

    window = data;

    જો (window->xsettings_first_time) {
        પાછા;
    }

    જો (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_setup = false;
        bool pixmap_already_setup = false;

        જો (window->pixmap) {
            pixmap_already_setup = true;
        } નહીંતર {
            dbe_already_setup = true;
        }

        /* set scale vars */
        window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
        window->iscale = (પૂર્ણાંક)SDL_ceilf(window->scale);
        જો (window->scale < 1) {
            window->scale = 1;
        }
        જો (SDL_roundf(window->scale) == window->scale) {
            window->scale = 0;
        }

        /* setup fonts */
#ifdef X_HAVE_UTF8_STRING
        જો (window->font_set) {
            X11_XFreeFontSet(window->display, window->font_set);
        }
#endif
        જો (window->font_struct) {
            X11_XFreeFont(window->display, window->font_struct);
        }

        X11Toolkit_InitWindowFonts(window);

        /* set up window */
        જો (window->scale != 0) {
            window->window_width = SDL_lroundf((window->window_width/window->iscale) * window->scale);
            window->window_height = SDL_lroundf((window->window_height/window->iscale) * window->scale);
            window->pixmap_width = window->window_width;
            window->pixmap_height = window->window_height;
            window->pixmap = true;
        } નહીંતર {
            window->pixmap = false;
        }

        જો (window->pixmap) {
            જો (!pixmap_already_setup) {
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                જો (SDL_X11_HAVE_XDBE && window->xdbe) {
                    X11_XdbeDeallocateBackBufferName(window->display, window->buf);
                }
#endif
            }
            X11_XFreePixmap(window->display, window->drawable);
            X11Toolkit_InitWindowPixmap(window);
        } નહીંતર {
            જો (!dbe_already_setup) {
                X11_XFreePixmap(window->display, window->drawable);
#ifndef NO_SHARED_MEMORY
                જો (window->image) {
                    XDestroyImage(window->image);
                    window->image = ખાલી;
                }
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                જો (SDL_X11_HAVE_XDBE && window->xdbe) {
                    window->buf = X11_XdbeAllocateBackBufferName(window->display, window->window, XdbeUndefined);
                    window->drawable = window->buf;
                }
#endif
            }
        }

        /* notify controls */
        માટે (i = 0; i < window->controls_sz; i++) {
            window->controls[i]->do_size = true;

            જો (window->controls[i]->func_on_scale_change) {
                window->controls[i]->func_on_scale_change(window->controls[i]);
            }

            જો (window->controls[i]->func_calc_size) {
                window->controls[i]->func_calc_size(window->controls[i]);
            }

            window->controls[i]->do_size = false;
        }

        /* notify cb */
        જો (window->cb_on_scale_change) {
            window->cb_on_scale_change(window, window->cb_data);
        }

        /* update ev scales */
        જો (!window->pixmap) {
            window->ev_scale = window->ev_iscale = 1;
        } નહીંતર {
            window->ev_scale = window->scale;
            window->ev_iscale = window->iscale;
        }
    }
}

સ્થિર શૂન્ય X11Toolkit_GetTextWidthHeightForFont(XFontStruct *font, અચલ અક્ષર *str, પૂર્ણાંક nbytes, પૂર્ણાંક *pwidth, પૂર્ણાંક *pheight, પૂર્ણાંક *ascent, પૂર્ણાંક *font_height)
{
    XCharStruct text_structure;
    પૂર્ણાંક font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &text_structure);
    *pwidth = text_structure.width;
    *pheight = text_structure.ascent + text_structure.descent;
    *ascent = text_structure.ascent;
    જો (font_height) {
       *font_height = font_ascent + font_descent;
    }
}

સ્થિર શૂન્ય X11Toolkit_GetTextWidthHeight(SDL_ToolkitWindowX11 *data, અચલ અક્ષર *str, પૂર્ણાંક nbytes, પૂર્ણાંક *pwidth, પૂર્ણાંક *pheight, પૂર્ણાંક *ascent, પૂર્ણાંક *descent, પૂર્ણાંક *font_height)
{
#ifdef X_HAVE_UTF8_STRING
    જો (data->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8TextExtents(data->font_set, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.width;
        *pheight = overall_logical.height;
        *ascent = -overall_logical.y;
        *descent = overall_logical.height - *ascent;

        જો (font_height) {
            XFontSetExtents *extents;

            extents = X11_XExtentsOfFontSet(data->font_set);
            *font_height = extents->max_logical_extent.height;
        }
    } નહીંતર
#endif
    {
        XCharStruct text_structure;
        પૂર્ણાંક font_direction, font_ascent, font_descent;
        X11_XTextExtents(data->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &text_structure);
        *pwidth = text_structure.width;
        *pheight = text_structure.ascent + text_structure.descent;
        *ascent = text_structure.ascent;
        *descent = text_structure.descent;

        જો (font_height) {
            *font_height = font_ascent + font_descent;
        }
    }
}

#ifdef HAVE_FRIBIDI_H
SDL_List_ગાંઠ *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, અક્ષર *txt, size_t sz, FriBidiParType *par)
#નહીંતર
SDL_List_ગાંઠ *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, અક્ષર *txt, size_t sz)
#endif
{
    SDL_List_ગાંઠ *list;
    અક્ષર *str;
    અક્ષર *buffer;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = ખાલી;
    thai = 0;
    str = txt;
    buffer = SDL_malloc(1);
    buffer[0] = 0;
    
#ifdef HAVE_FRIBIDI_H
    જો (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    જો (data->fribidi) {
        અક્ષર *fstr;
                
        fstr = SDL_FriBidi_Process(data->fribidi, str, sz, data->do_shaping, par);
        જો (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#endif        

    જ્યારે (1) {
        અક્ષર *new;
        અક્ષર utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_StepUTF8((અચલ અક્ષર **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        જો (cp == 0 || cond == (thai ? false : true)) {
            SDL_ToolkitTextElementX11 *element;
            
            element = SDL_malloc(કદ(SDL_ToolkitTextElementX11));
            જો (thai) {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_THAI;
            } નહીંતર {
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

        જો (!cp) {
            તોડો;
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
    જો (free_txt) {
        SDL_free(txt);
    }
    પાછા list;
}

શૂન્ય X11Toolkit_ShapeTextElements(SDL_ToolkitWindowX11 *data, SDL_List_ગાંઠ *list)
{
    SDL_List_ગાંઠ *cursor;
    SDL_ToolkitTextElementX11 *prev;
    પૂર્ણાંક temp;
    
    /* Shape and calculate bounding box */
    cursor = list;
    જ્યારે (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
#ifdef HAVE_LIBTHAI_H
        element->thai_overlays = ખાલી;
#endif
        જો (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            જો (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, ખાલી);
            } નહીંતર {
#ifdef HAVE_LIBTHAI_H
                જો (data->th) {
                    સંરચના thcell_t *cells;
                    અક્ષર *tis_str;
                    અક્ષર *base_tis_str;
                    size_t cells_sz;
                    size_t base_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, કદ(સંરચના thcell_t));
                    data->th->make_cells((અચલ thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    base_tis_str_sz = cells_sz;
                    base_tis_str = SDL_malloc(base_tis_str_sz + 1);
                    માટે (temp = 0; temp < cells_sz; temp++) {
                        base_tis_str[temp] = cells[temp].base;
                        
                        જો (cells[temp].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            અક્ષર *pre;
                            પૂર્ણાંક temp2;
                            
                            overlay = SDL_malloc(કદ(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (અચલ અક્ષર *)&cells[temp].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->ટોચ = false;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ખાલી);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ખાલી);
                            SDL_ListAdd(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        જો (cells[temp].ટોચ) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            અક્ષર *pre;
                            પૂર્ણાંક temp2;
                            
                            overlay = SDL_malloc(કદ(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (અચલ અક્ષર *)&cells[temp].ટોચ, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->ટોચ = true;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ખાલી);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ખાલી);
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
#નહીંતર
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
#endif            
            }
        } નહીંતર {
            X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
        }
        
        cursor = cursor->next;
    }
    
    /* Add offsets */
    prev = ખાલી;
    cursor = list;
    જ્યારે (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;        
        જો (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } નહીંતર {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->next;
    }
}


શૂન્ય X11Toolkit_DrawTextElements(SDL_ToolkitWindowX11 *data, SDL_List_ગાંઠ *list, પૂર્ણાંક x, પૂર્ણાંક y)
{
    SDL_List_ગાંઠ *cursor;
    
    cursor = list;
    
    જ્યારે (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        જો (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            જો (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
#ifdef X_HAVE_UTF8_STRING
                જો (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } નહીંતર
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } નહીંતર {    
#ifdef HAVE_LIBTHAI_H
                SDL_List_ગાંઠ *overlay_cursor;
                    
                /* Draw the base string */
#ifdef X_HAVE_UTF8_STRING
                જો (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } નહીંતર
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                જ્યારે (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->entry;
#ifdef X_HAVE_UTF8_STRING
                    જો (data->utf8) {
                        X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } નહીંતર
#endif
                    {
                        X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->next;
                }
#endif                
            }
        } નહીંતર {
#ifdef X_HAVE_UTF8_STRING
            જો (data->utf8) {
                X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } નહીંતર
#endif
            {
                X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->next;
    }
}

પૂર્ણાંક X11Toolkit_GetTextElementsRect(SDL_List_ગાંઠ *list, SDL_Rect *out)
{
    SDL_List_ગાંઠ *cursor;
    પૂર્ણાંક ret;
    
    ret = 0;
    out->x = out->y = 0;
    out->w = out->h = 0;
    cursor = list;
    જ્યારે (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        
        out->w += element->rect.w;
        out->h = SDL_max(out->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->next;
    }
    
    પાછા ret;
}

શૂન્ય X11Toolkit_FreeTextElementsListContents(SDL_List_ગાંઠ *list)
{
    SDL_List_ગાંઠ *cursor;
    
    cursor = list;
    જ્યારે (cursor) {
        SDL_ToolkitTextElementX11 *element;
#ifdef HAVE_LIBTHAI_H
        SDL_List_ગાંઠ *overlay_cursor;
#endif

        element = cursor->entry;
        
        જો (element->str_free) {
            element->str_free(element->str);
        }
        
#ifdef HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        જ્યારે (overlay_cursor) {
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
 
સ્થિર bool X11Toolkit_ShouldFlipUI(શૂન્ય) 
{
    SDL_Locale **current_locales;
    સ્થિર અચલ SDL_Locale rtl_locales[] = {
        { "ar", ખાલી, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", ખાલી, },
        { "iw", ખાલી, },
        { "yi", ખાલી, },
        { "ur", ખાલી, },
        { "ug", ખાલી, },
        { "kd", ખાલી, },
        { "pk", "PK", },
        { "ps", ખાલી, }
    }; 
    પૂર્ણાંક current_locales_sz;
    પૂર્ણાંક i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    જો (current_locales_sz <= 0) {
        પાછા false;        
    }
    માટે (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        જો (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            જો (!rtl_locales[i].country) {
                પાછા true;
            } નહીંતર {
                પાછા SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    પાછા false;
}

SDL_ToolkitWindowX11 *X11Toolkit_CreateWindowStruct(SDL_Window *parent, SDL_ToolkitWindowX11 *tkparent, SDL_ToolkitWindowModeX11 mode, અચલ SDL_MessageBoxColor *colorhints, bool create_new_display)
{
    SDL_ToolkitWindowX11 *window;
    પૂર્ણાંક i;
#ifdef SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#endif
    #define ErrorFreeRetNull(x, y) SDL_SetError(x); SDL_free(y); પાછા ખાલી
    #define ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_SetError(x, y); SDL_free(z); પાછા ખાલી

    જો (!SDL_X11_LoadSymbols()) {
        પાછા ખાલી;
    }

    // This code could get called from multiple threads maybe?
    X11_XInitThreads();

    window = (SDL_ToolkitWindowX11 *)SDL_malloc(કદ(SDL_ToolkitWindowX11));
    જો (!window) {
        SDL_SetError("Unable to allocate toolkit window structure");
        પાછા ખાલી;
    }

    window->mode = mode;
    window->tk_parent = tkparent;

#જો SDL_SET_LOCALE
    જો (mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        window->origlocale = setlocale(LC_ALL, ખાલી);
        જો (window->origlocale) {
            window->origlocale = SDL_strdup(window->origlocale);
            જો (!window->origlocale) {
                SDL_free(window);
                પાછા ખાલી;
            }
            (શૂન્ય)setlocale(LC_ALL, "");
        }
    }
#endif

    window->parent_device = ખાલી;
    જો (create_new_display) {
        window->display = X11_XOpenDisplay(ખાલી);
        window->display_close = true;
        જો (!window->display) {
            ErrorFreeRetNull("Couldn't open X11 display", window);
        }
    } નહીંતર {
        જો (parent) {
            window->parent_device = SDL_GetVideoDevice();
            window->display = window->parent_device->internal->display;
            window->display_close = false;
        } નહીંતર જો (tkparent) {
            window->display = tkparent->display;
            window->display_close = false;
        } નહીંતર {
            window->display = X11_XOpenDisplay(ખાલી);
            window->display_close = true;
            જો (!window->display) {
                ErrorFreeRetNull("Couldn't open X11 display", window);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    પૂર્ણાંક xrandr_event_base, xrandr_error_base;
    window->xrandr = X11_XRRQueryExtension(window->display, &xrandr_event_base, &xrandr_error_base);
#endif

#ifndef NO_SHARED_MEMORY
    window->shm_pixmap = False;
    window->shm = X11_XShmQueryExtension(window->display) ? SDL_X11_HAVE_SHM : false;
    જો (window->shm) {
        પૂર્ણાંક major;
        પૂર્ણાંક minor;

        X11_XShmQueryVersion(window->display, &major, &minor, &window->shm_pixmap);
        જો (window->shm_pixmap) {
            જો (X11_XShmPixmapFormat(window->display) != ZPixmap) {
                window->shm_pixmap = False;
            }
        }
    }
#endif

    /* Scale/Xsettings */
    window->pixmap = false;
    window->xsettings_first_time = true;
    window->xsettings = xsettings_client_new(window->display, DefaultScreen(window->display), X11Toolkit_SettingsNotify, ખાલી, window);
    window->xsettings_first_time = false;
    window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
    જો (window->scale < 1) {
        window->scale = 1;
    }
    window->iscale = (પૂર્ણાંક)SDL_ceilf(window->scale);
    જો (SDL_roundf(window->scale) == window->scale) {
        window->scale = 0;
    }

    /* Fonts */
    X11Toolkit_InitWindowFonts(window);

    /* Color hints */
#ifdef SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    જો (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#endif

    જો (!colorhints) {
#ifdef SDL_USE_LIBDBUS
        પસંદગી (theme) {
            સ્થિતિ SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                તોડો;
#જો 0
            સ્થિતિ SDL_SYSTEM_THEME_LIGHT_ઉપલું_CONTRAST:
                colorhints = g_default_colors_light_ઉપલું_contrast;
                તોડો;
            સ્થિતિ SDL_SYSTEM_THEME_DARK_ઉપલું_CONTRAST:
                colorhints = g_default_colors_dark_ઉપલું_contrast;
                તોડો;
#endif
            મૂળભૂત:
                colorhints = g_default_colors;
        }
#નહીંતર
        colorhints = g_default_colors;
#endif
    }
    window->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    માટે (i = 0; i < SDL_MESSAGEBOX_COLOR_ગણતરી; i++) {
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
    જો (parent) {
        SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(parent);
        window->screen = displaydata->screen;
    } નહીંતર {
        window->screen = DefaultScreen(window->display);
    }

    /* Visuals */
    જો (mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        window->visual = parent->internal->visual;
        window->cmap = parent->internal->colormap;
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
        window->depth = window->vi.depth;
    } નહીંતર {
        window->visual = DefaultVisual(window->display, window->screen);
        window->cmap = DefaultColormap(window->display, window->screen);
        window->depth = DefaultDepth(window->display, window->screen);
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
    }

    /* Allocate colors */
    માટે (i = 0; i < SDL_MESSAGEBOX_COLOR_ગણતરી; i++) {
        X11_XAllocColor(window->display, window->cmap, &window->xcolor[i]);
    }
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l1);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l2);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_d);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_pressed);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_disabled_text);

    /* Control list */
    window->has_focus = false;
    window->controls = ખાલી;
    window->controls_sz = 0;
    window->dyn_controls_sz = 0;
    window->fiddled_control = ખાલી;
    window->dyn_controls = ખાલી;

    /* Menu windows */
    window->popup_windows = ખાલી;

    /* BIDI engine */
#ifdef HAVE_FRIBIDI_H
    window->fribidi = SDL_FriBidi_Create();
#endif

#ifdef HAVE_LIBTHAI_H
    window->th = SDL_LibThai_Create();
#endif
    
    /* Interface direction */
    window->flip_interface = X11Toolkit_ShouldFlipUI();
    
    પાછા window;
}

સ્થિર શૂન્ય X11Toolkit_AddControlToWindow(SDL_ToolkitWindowX11 *window, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    window->controls_sz++;
    જો (window->controls_sz == 1) {
        window->controls = (સંરચના SDL_ToolkitControlX11 **)SDL_malloc(કદ(સંરચના SDL_ToolkitControlX11 *));
    } નહીંતર {
        window->controls = (સંરચના SDL_ToolkitControlX11 **)SDL_realloc(window->controls, કદ(સંરચના SDL_ToolkitControlX11 *) * window->controls_sz);
    }
    window->controls[window->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    જો (control->dynamic) {
        window->dyn_controls_sz++;
        જો (window->dyn_controls_sz == 1) {
            window->dyn_controls = (સંરચના SDL_ToolkitControlX11 **)SDL_malloc(કદ(સંરચના SDL_ToolkitControlX11 *));
        } નહીંતર {
            window->dyn_controls = (સંરચના SDL_ToolkitControlX11 **)SDL_realloc(window->dyn_controls, કદ(સંરચના SDL_ToolkitControlX11 *) * window->dyn_controls_sz);
        }
        window->dyn_controls[window->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    જો (control->selected) {
        window->focused_control = control;
    }
}

bool X11Toolkit_CreateWindowRes(SDL_ToolkitWindowX11 *data, પૂર્ણાંક w, પૂર્ણાંક h, પૂર્ણાંક cx, પૂર્ણાંક cy, અક્ષર *title)
{
    પૂર્ણાંક x, y;
    XSizeHints *sizehints;
    XSetWindowAttributes wnd_attr;
    Atom _NET_WM_WINDOW_TYPE, _NET_WM_WINDOW_TYPE_DIALOG, _NET_WM_WINDOW_TYPE_DROPDOWN_MENU, _NET_WM_WINDOW_TYPE_TOOLTIP;
    SDL_WindowData *windowdata = ખાલી;
    Display *display = data->display;
    XGCValues ctx_vals;
    Window મૂળ_win;
    Window parent_win;
    unsigned long gcflags = GCForeground | GCBackground;
    unsigned long valuemask;
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
#ifdef XRANDR_DISABLED_BY_DEFAULT
    અચલ bool use_xrandr_by_default = false;
#નહીંતર
    અચલ bool use_xrandr_by_default = true;
#endif
#endif

    જો (data->scale == 0) {
        data->window_width = w;
        data->window_height = h;
    } નહીંતર {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        data->pixmap = true;
    }

    જો (data->parent) {
        windowdata = data->parent->internal;
    }

    valuemask = CWEventMask | CWColormap;
    data->event_mask = ExposureMask |
                       ButtonPressMask | ButtonReleaseMask | ચાવી_Press_Mask | ચાવી_Release_Mask |
                       StructureNotifyMask | FocusChangeMask | PointerMotionMask;
    wnd_attr.event_mask = data->event_mask;
    wnd_attr.colormap = data->cmap;
    જો (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    મૂળ_win = મૂળ_Window(display, data->screen);
    જો (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        parent_win = windowdata->xwindow;
    } નહીંતર {
        parent_win = મૂળ_win;
    }

    data->window = X11_XCreateWindow(
        display, parent_win,
        0, 0,
        data->window_width, data->window_height,
        0, data->depth, આગત_Output, data->visual,
        valuemask, &wnd_attr);
    જો (data->window == None) {
        પાછા SDL_SetError("Couldn't create X window");
    }

    જો (windowdata && data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
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
                            PropModeReplace, (unsigned અક્ષર *)stateatoms, statecount);
    }

    જો (windowdata && data->mode != SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        X11_XSetTransientForHint(display, data->window, windowdata->xwindow);
    }

    જો (data->tk_parent) {
        X11_XSetTransientForHint(display, data->window, data->tk_parent->window);
    }

    SDL_X11_SetWindowTitle(display, data->window, title);

    // Let the window manager the type of the window
    જો (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned અક્ષર *)&_NET_WM_WINDOW_TYPE_DIALOG, 1);
    } નહીંતર જો (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned અક્ષર *)&_NET_WM_WINDOW_TYPE_DROPDOWN_MENU, 1);
    } નહીંતર જો (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned અક્ષર *)&_NET_WM_WINDOW_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    data->wm_delete_message = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, data->window, &data->wm_delete_message, 1);
    data->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    જો (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        x = cx;
        y = cy;
        જાઓ MOVEWINDOW;
    }
    જો (windowdata) {
        XWindowAttributes attrib;
        Window dummy;

        X11_XGetWindowAttributes(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.width - data->window_width) / 2;
        y = attrib.y + (attrib.height - data->window_height) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, મૂળ_Window(display, data->screen), x, y, &x, &y, &dummy);
    } નહીંતર {
        અચલ SDL_VideoDevice *dev = SDL_GetVideoDevice();
        જો (dev && dev->displays && dev->અંક_displays > 0) {
            અચલ SDL_VideoDisplay *dpy = dev->displays[0];
            અચલ SDL_DisplayData *dpydata = dpy->internal;
            x = dpydata->x + ((dpy->current_mode->w - data->window_width) / 2);
            y = dpydata->y + ((dpy->current_mode->h - data->window_height) / 3);
        }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
        નહીંતર જો (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && data->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_out;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, મૂળ_win);
            જો (!screen_res) {
                જાઓ NOXRANDR;
            }

            default_out = X11_XRRGetOutputPrimary(display, મૂળ_win);
            જો (default_out != None) {
                XRROutputInfo *out_info;

                out_info = X11_XRRGetOutputInfo(display, screen_res, default_out);
                જો (out_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(out_info);
                    જાઓ FIRSTOUTPUTXRANDR;
                }

                જો (out_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                } નહીંતર જો (out_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                } નહીંતર {
                    crtc_info = ખાલી;
                }
                
                જો (crtc_info) {
                    x = (crtc_info->width - data->window_width) / 2;
                    y = (crtc_info->height - data->window_height) / 3;
                    X11_XRRFreeOutputInfo(out_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } નહીંતર {
                    X11_XRRFreeOutputInfo(out_info);
                    જાઓ NOXRANDR;
                }
            } નહીંતર {
                    FIRSTOUTPUTXRANDR:
                    જો (screen_res->noutput > 0) {
                        XRROutputInfo *out_info;

                        out_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        જો (!out_info) {
                            જાઓ FIRSTCRTCXRANDR;
                        }

                        જો (out_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                        } નહીંતર જો (out_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                        } નહીંતર {
                            crtc_info = ખાલી;
                        }

                        જો (!crtc_info) {
                            X11_XRRFreeOutputInfo(out_info);
                            જાઓ FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeOutputInfo(out_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        જાઓ MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    જો (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        જાઓ NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    જો (crtc_info) {
                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } નહીંતર {
                        X11_XRRFreeScreenResources(screen_res);
                        જાઓ NOXRANDR;
                    }
            }
        }
#endif
        નહીંતર {
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
    જો (sizehints) {
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
    જો (SDL_X11_HAVE_XDBE && !data->pixmap) {
        પૂર્ણાંક xdbe_major, xdbe_minor;
        જો (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            data->xdbe = true;
            data->buf = X11_XdbeAllocateBackBufferName(display, data->window, XdbeUndefined);
            data->drawable = data->buf;
        } નહીંતર {
            data->xdbe = false;
        }
    }
#endif

    X11Toolkit_InitWindowPixmap(data);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    જો (!data->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = data->font_struct->fid;
    }
    data->ctx = X11_XCreateGC(data->display, data->drawable, gcflags, &ctx_vals);
    જો (data->ctx == None) {
        પાછા SDL_SetError("Couldn't create graphics context");
    }

    data->close = false;
    data->ચાવી_control_esc = data->ચાવી_control_enter = ખાલી;
    જો (!data->pixmap) {
        data->ev_scale = data->ev_iscale = 1;
    } નહીંતર {
        data->ev_scale = data->scale;
        data->ev_iscale = data->iscale;
    }

#જો SDL_GRAB
    જો (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XGrabPointer(display, data->window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
        X11_XGrabKeyboard(display, data->window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
#endif

    પાછા true;
}

સ્થિર શૂન્ય X11Toolkit_DrawWindow(SDL_ToolkitWindowX11 *data) {
    SDL_Rect rect;
    પૂર્ણાંક i;

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    જો (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeBeginIdiom(data->display);
    }
#endif

    X11_XSetForeground(data->display, data->ctx, data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    જો (data->pixmap) {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->pixmap_width, data->pixmap_height);
    } નહીંતર {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->window_width, data->window_height);
    }

    માટે (i = 0; i < data->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = data->controls[i];
        જો (control) {
            જો (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    જો (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        XdbeSwapInfo swap_info;
        swap_info.swap_window = data->window;
        swap_info.swap_action = XdbeUndefined;
        X11_XdbeSwapBuffers(data->display, &swap_info, 1);
        X11_XdbeEndIdiom(data->display);
    }
#endif

    જો (data->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = data->window_width;
        rect.h = data->window_height;
#ifndef NO_SHARED_MEMORY
        જો (data->shm) {
            જો (data->shm_pixmap) {
                X11_XFlush(data->display);
                X11_XSync(data->display, false);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->shm_info.shmaddr, data->shm_bytes_per_લીટી);
                SDL_BlitSurfaceScaled(scale_surface, ખાલી, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(data->display, data->drawable, data->window, data->ctx, 0, 0, data->window_width, data->window_height, 0, 0);
            } નહીંતર {
                X11_XShmGetImage(data->display, data->drawable, data->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->image->data, data->image->bytes_per_લીટી);
                SDL_BlitSurfaceScaled(scale_surface, ખાલી, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                X11_XShmPutImage(data->display, data->window, data->ctx, data->image, 0, 0, 0, 0, data->window_width, data->window_height, False);
            }
        } નહીંતર
#endif
        {
            XImage *image;

            image = X11_XGetImage(data->display, data->drawable, 0, 0 , data->pixmap_width, data->pixmap_height, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), image->data, image->bytes_per_લીટી);
            SDL_BlitSurfaceScaled(scale_surface, ખાલી, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
            X11_XPutImage(data->display, data->window, data->ctx, image, 0, 0, 0, 0, data->window_width, data->window_height);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(data->display);
}

સ્થિર SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_ToolkitWindowX11 *data, પૂર્ણાંક x, પૂર્ણાંક y)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < data->controls_sz; i++) {
        SDL_Rect *rect = &data->controls[i]->rect;
        જો ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            પાછા data->controls[i];
        }
    }

    પાછા ખાલી;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
સ્થિર Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_ToolkitWindowX11 *data = (SDL_ToolkitWindowX11 *)arg;

    જો (event->xany.display != data->display) {
        પાછા False;
    }

    જો (event->xany.window == data->window) {
        પાછા True;
    }

    પાછા False;
}

શૂન્ય X11Toolkit_ProcessWindowEvents(SDL_ToolkitWindowX11 *data, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    જો ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        પાછા;
    }

    data->draw = false;
    data->e = e;

    પસંદગી (e->type) {
        સ્થિતિ Expose:
            data->draw = true;
            તોડો;
        સ્થિતિ ClientMessage:
            જો (e->xclient.message_type == data->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.data.l[0] == data->wm_delete_message) {
                data->close = true;
            }
            તોડો;
        સ્થિતિ FocusIn:
            data->has_focus = true;
            તોડો;
        સ્થિતિ FocusOut:
            data->has_focus = false;
            જો (data->fiddled_control) {
                data->fiddled_control->selected = false;
            }
            data->fiddled_control = ખાલી;
            માટે (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
            }
            તોડો;
        સ્થિતિ MotionNotify:
            જો (data->has_focus) {
                data->previous_control = data->fiddled_control;
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                જો (data->previous_control) {
                    data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    જો (data->previous_control->func_on_state_change) {
                        data->previous_control->func_on_state_change(data->previous_control);
                    }
                    data->draw = true;
                }
                જો (data->fiddled_control) {
                    જો (data->fiddled_control->dynamic) {
                        data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        જો (data->fiddled_control->func_on_state_change) {
                            data->fiddled_control->func_on_state_change(data->fiddled_control);
                        }
                        data->draw = true;
                    } નહીંતર {
                        data->fiddled_control = ખાલી;
                    }
                }
            }
            તોડો;
        સ્થિતિ ButtonPress:
            data->previous_control = data->fiddled_control;
            જો (data->previous_control) {
                data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                જો (data->previous_control->func_on_state_change) {
                    data->previous_control->func_on_state_change(data->previous_control);
                }
                data->draw = true;
            }
            જો (e->xbutton.button == Button1) {
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                જો (data->fiddled_control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    જો (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->draw = true;
                }
            }
            તોડો;
        સ્થિતિ ButtonRelease:
            જો (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
                પૂર્ણાંક cx;
                પૂર્ણાંક cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                જો (cy < 0 || cx < 0) {
                    data->close = true;
                }

                જો (cy > data->window_height || cx > data->window_width) {
                    data->close = true;
                }
            }

            જો ((e->xbutton.button == Button1) && (data->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                જો (data->fiddled_control == control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    જો (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    data->draw = true;
                }
            }
            તોડો;
        સ્થિતિ ચાવી_Press:
            data->last_ચાવી_pressed = X11_XLookupKeysym(&e->xkey, 0);

            જો (data->last_ચાવી_pressed == XK_Escape) {
                માટે (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    જો(data->controls[data->ev_i]->is_default_esc) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->ચાવી_control_esc = data->controls[data->ev_i];
                    }
                }
            } નહીંતર જો ((data->last_ચાવી_pressed == XK_Return) || (data->last_ચાવી_pressed == XK_KP_Enter)) {
                માટે (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    જો(data->controls[data->ev_i]->selected) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->ચાવી_control_enter = data->controls[data->ev_i];
                    }
                }
            }
            તોડો;
        સ્થિતિ ચાવી_Release:
        {
            ચાવી_Sym ચાવી = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            જો (ચાવી != data->last_ચાવી_pressed) {
                તોડો;
            }

            જો (ચાવી == XK_Escape) {
                જો (data->ચાવી_control_esc) {
                    જો (data->ચાવી_control_esc->func_on_state_change) {
                        data->ચાવી_control_esc->func_on_state_change(data->ચાવી_control_esc);
                    }
                }
            } નહીંતર જો ((ચાવી == XK_Return) || (ચાવી == XK_KP_Enter)) {
                જો (data->ચાવી_control_enter) {
                    જો (data->ચાવી_control_enter->func_on_state_change) {
                        data->ચાવી_control_enter->func_on_state_change(data->ચાવી_control_enter);
                    }
                }
            } નહીંતર જો (ચાવી == XK_Tab || ચાવી == XK_ડાબું || ચાવી == XK_જમણું) {
                જો (data->focused_control) {
                    data->focused_control->selected = false;
                }
                data->draw = true;
                માટે (data->ev_i = 0; data->ev_i < data->dyn_controls_sz; data->ev_i++) {
                    જો (data->dyn_controls[data->ev_i] == data->focused_control) {
                        પૂર્ણાંક next_index;

                        જો (ચાવી == XK_ડાબું) {
                            next_index = data->ev_i - 1;
                        } નહીંતર {
                            next_index = data->ev_i + 1;
                        }
                        જો ((next_index >= data->dyn_controls_sz) || (next_index < 0)) {
                            જો (ચાવી == XK_જમણું || ચાવી == XK_ડાબું) {
                                next_index = data->ev_i;
                            } નહીંતર {
                                next_index = 0;
                            }
                        }
                        data->focused_control = data->dyn_controls[next_index];
                        data->focused_control->selected = true;
                        તોડો;
                    }
                }
            }
            તોડો;
        }
    }

    જો (data->draw) {
        X11Toolkit_DrawWindow(data);
    }
}

શૂન્ય X11Toolkit_DoWindowEventLoop(SDL_ToolkitWindowX11 *data) {
   જ્યારે (!data->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(data->display, &e);
        જો (data->xsettings) {
            xsettings_client_process_event(data->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(data->display, &e, X11Toolkit_EventTest, (XPointer)data);
        X11Toolkit_ProcessWindowEvents(data, &e);
    }
}


શૂન્ય X11Toolkit_ResizeWindow(SDL_ToolkitWindowX11 *data, પૂર્ણાંક w, પૂર્ણાંક h) {
    જો (!data->pixmap) {
        data->window_width = w;
        data->window_height = h;
    } નહીંતર {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        X11_XFreePixmap(data->display, data->drawable);
        X11Toolkit_InitWindowPixmap(data);
    }

    X11_XResizeWindow(data->display, data->window, data->window_width, data->window_height);
}

સ્થિર શૂન્ય X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->window->display, icon_control->icon_char_font);
    SDL_free(control);
}

સ્થિર શૂન્ય X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->window->iscale;
    control->rect.h -= 2 * control->window->iscale;
    X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + (2 * control->window->iscale), control->rect.y + (2* control->window->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    પસંદગી (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        સ્થિતિ SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                તોડો;
        સ્થિતિ SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                તોડો;
        સ્થિતિ SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                તોડો;
    }
    X11_XSetFont(control->window->display, control->window->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    જો (!control->window->utf8) {
        X11_XSetFont(control->window->display, control->window->ctx, control->window->font_struct->fid);
    }

    control->rect.w += 2 * control->window->iscale;
    control->rect.h += 2 * control->window->iscale;
}

સ્થિર શૂન્ય X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    પૂર્ણાંક icon_char_w;
    પૂર્ણાંક icon_wh;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11Toolkit_GetTextWidthHeightForFont(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, ખાલી);
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

સ્થિર શૂન્ય X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    અક્ષર *font;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11_XFreeFont(base_control->window->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_SIZE * base_control->window->iscale);
    control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
    SDL_free(font);
    જો (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * base_control->window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_ToolkitWindowX11 *window, SDL_MessageBoxFlags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    અક્ષર *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(કદ(SDL_ToolkitIconControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    જો (!control) {
        SDL_SetError("Unable to allocate icon control structure");
        પાછા ખાલી;
    }

    /* Fill out struct */
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawIconControl;
    base_control->func_free = X11Toolkit_DestroyIconControl;
    base_control->func_on_state_change = ખાલી;
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
    જો (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        જો (!control->icon_char_font) {
            SDL_free(control);
            પાછા ખાલી;
        }
    }

    /* Set colors */
    પસંદગી (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    સ્થિતિ SDL_MESSAGEBOX_ERROR:
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
        તોડો;
    સ્થિતિ SDL_MESSAGEBOX_WARNING:
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
        તોડો;
    સ્થિતિ SDL_MESSAGEBOX_INFORMATION:
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
        તોડો;
    મૂળભૂત:
        X11_XFreeFont(window->display, control->icon_char_font);
        SDL_free(control);
        પાછા ખાલી;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    જો (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } નહીંતર જો (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } નહીંતર {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    જો (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } નહીંતર જો (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } નહીંતર {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    જો (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } નહીંતર જો (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } નહીંતર {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(window->display, window->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(base_control);

    X11Toolkit_AddControlToWindow(window, base_control);
    પાછા base_control;
}

bool X11Toolkit_NotifyControlOfSizeChange(SDL_ToolkitControlX11 *control) {
    જો (control->func_calc_size) {
        control->func_calc_size(control);
        પાછા true;
    } નહીંતર {
        પાછા false;
    }
}

સ્થિર શૂન્ય X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11Toolkit_GetTextElementsRect(button_control->text, &button_control->text_rect);
    જો (control->do_size) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.h;
    }
    button_control->text_rect.x = (control->rect.w - button_control->text_rect.w)/2;
    button_control->text_rect.y = (control->rect.h - button_control->text_rect.h)/2;
}


સ્થિર શૂન્ય X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    /* Draw bevel */
    જો (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
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
        } નહીંતર {
            જો (control->selected) {
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
            } નહીંતર {
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

સ્થિર શૂન્ય X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    જો (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_data);
    }
}

સ્થિર શૂન્ય X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11Toolkit_FreeTextElements(button_control->text);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_ToolkitWindowX11 *window, અચલ SDL_MessageBoxButtonData *data) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *base_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(કદ(SDL_ToolkitButtonControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    જો (!control) {
        SDL_SetError("Unable to allocate button control structure");
        પાછા ખાલી;
    }
    base_control->window = window;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->func_calc_size = X11Toolkit_CalculateButtonControl;
    base_control->func_draw = X11Toolkit_DrawButtonControl;
    base_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    base_control->func_free = X11Toolkit_DestroyButtonControl;
    base_control->func_on_scale_change = ખાલી;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = true;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    જો (data->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        base_control->is_default_esc = true;
    }
    જો (data->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        base_control->is_default_enter = true;
        base_control->selected = true;
    }
    control->cb = ખાલી;
    control->data = data;
#ifdef HAVE_FRIBIDI_H
    control->text = X11Toolkit_MakeTextElements(base_control->window, (અક્ષર *)control->data->text, SDL_strlen(control->data->text), ખાલી);
#નહીંતર 
    control->text = X11Toolkit_MakeTextElements(base_control->window, (અક્ષર *)control->data->text, SDL_strlen(control->data->text));
#endif
    X11Toolkit_ShapeTextElements(base_control->window, control->text);
    
    base_control->do_size = true;
    X11Toolkit_CalculateButtonControl(base_control);
    base_control->do_size = false;

    X11Toolkit_AddControlToWindow(window, base_control);
    પાછા base_control;
}

શૂન્ય X11Toolkit_RegisterCallbackForButtonControl(SDL_ToolkitControlX11 *control, શૂન્ય *data, શૂન્ય (*cb)(સંરચના SDL_ToolkitControlX11 *, શૂન્ય *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_data = data;
    button_control->cb = cb;
}

અચલ SDL_MessageBoxButtonData *X11Toolkit_GetButtonControlData(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    પાછા button_control->data;
}

શૂન્ય X11Toolkit_DestroyWindow(SDL_ToolkitWindowX11 *data) {
    પૂર્ણાંક i;

    જો (!data) {
        પાછા;
    }

#જો SDL_GRAB
    જો (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XUngrabPointer(data->display, CurrentTime);
        X11_XUngrabKeyboard(data->display, CurrentTime);
    }
#endif

    માટે (i = 0; i < data->controls_sz; i++) {
        જો (data->controls[i]->func_free) {
            data->controls[i]->func_free(data->controls[i]);
        }
    }
    SDL_free(data->controls);
    SDL_free(data->dyn_controls);

    જો (data->popup_windows) {
        SDL_ListClear(&data->popup_windows);
    }

    જો (data->pixmap) {
        X11_XFreePixmap(data->display, data->drawable);
    }

#ifndef NO_SHARED_MEMORY
    જો (data->pixmap && data->shm) {
        X11_XShmDetach(data->display, &data->shm_info);
        જો (!data->shm_pixmap) {
            XDestroyImage(data->image);
        }
        shmdt(data->shm_info.shmaddr);
    }
#endif

#ifdef X_HAVE_UTF8_STRING
    જો (data->font_set) {
        X11_XFreeFontSet(data->display, data->font_set);
        data->font_set = ખાલી;
    }
#endif

    જો (data->font_struct) {
        X11_XFreeFont(data->display, data->font_struct);
        data->font_struct = ખાલી;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    જો (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeDeallocateBackBufferName(data->display, data->buf);
    }
#endif

    જો (data->xsettings) {
        xsettings_client_destroy(data->xsettings);
    }

    X11_XFreeGC(data->display, data->ctx);

    જો (data->display) {
        જો (data->window != None) {
            X11_XWithdrawWindow(data->display, data->window, data->screen);
            X11_XDestroyWindow(data->display, data->window);
            data->window = None;
        }

        જો (data->display_close) {
            X11_XCloseDisplay(data->display);
        }
        data->display = ખાલી;
    }

#જો SDL_SET_LOCALE
    જો (data->origlocale && (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG)) {
        (શૂન્ય)setlocale(LC_ALL, data->origlocale);
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

સ્થિર પૂર્ણાંક X11_Toolkit_ગણતરી_લીટીઓ_Of_Text(અચલ અક્ષર *text)
{
    પૂર્ણાંક result = 0;
    જ્યારે (text && *text) {
        અચલ અક્ષર *lf = SDL_strchr(text, '\n');
        result++; // even without an endline, this counts as a line.
        text = lf ? lf + 1 : ખાલી;
    }
    પાછા result;
}

સ્થિર શૂન્ય X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    પૂર્ણાંક i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    માટે (i = 0; i < label_control->sz; i++) {
        X11Toolkit_DrawTextElements(control->window, label_control->લીટીઓ[i].text, control->rect.x + label_control->લીટીઓ[i].rect.x, control->rect.y + label_control->લીટીઓ[i].rect.y);
    }
}

સ્થિર શૂન્ય X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    પૂર્ણાંક i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    માટે (i = 0; i < label_control->sz; i++) {
        X11Toolkit_FreeTextElements(label_control->લીટીઓ[i].text);
    }
    SDL_free(label_control->લીટીઓ);
    SDL_free(label_control);
}

સ્થિર શૂન્ય X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitLabelControlX11 *control;
    પૂર્ણાંક i;

    control = (SDL_ToolkitLabelControlX11 *)base_control;
    
    જો (base_control->do_size) {
        base_control->rect.w = 0;
        base_control->rect.h = 0;
    }
    
    માટે (i = 0; i < control->sz; i++) {
        પૂર્ણાંક font_h;
        
        font_h = X11Toolkit_GetTextElementsRect(control->લીટીઓ[i].text, &control->લીટીઓ[i].rect);
        
        જો (base_control->do_size) {
            base_control->rect.w = SDL_max(base_control->rect.w, control->લીટીઓ[i].rect.w);
        }
        
        જો (i > 0) {
            control->લીટીઓ[i].rect.y = font_h + control->લીટીઓ[i - 1].rect.y;
        } નહીંતર {
            control->લીટીઓ[i].rect.y = 0;
        }
    }

#ifdef HAVE_FRIBIDI_H
    જો (base_control->window->fribidi) {
        FriBidiParType first_ndn_dir;
        પૂર્ણાંક last_ndn;
    
        first_ndn_dir = FRIBIDI_PAR_LTR;
        માટે (i = 0; i < control->sz; i++) {
            જો (control->લીટીઓ[i].par != FRIBIDI_PAR_ON) {
                first_ndn_dir = control->લીટીઓ[i].par;
            }
        }

        last_ndn = -1;
        માટે (i = 0; i < control->sz; i++) {
            પસંદગી (control->લીટીઓ[i].par) {
                સ્થિતિ FRIBIDI_PAR_LTR:
                    control->લીટીઓ[i].rect.x = 0;
                    last_ndn = i;
                    તોડો;
                સ્થિતિ FRIBIDI_PAR_RTL:
                    control->લીટીઓ[i].rect.x = base_control->rect.w - control->લીટીઓ[i].rect.w;
                    last_ndn = i;
                    તોડો;
                મૂળભૂત:
                    જો (last_ndn != -1) {
                        જો (control->લીટીઓ[last_ndn].par == FRIBIDI_PAR_RTL) {
                            control->લીટીઓ[i].rect.x = base_control->rect.w - control->લીટીઓ[i].rect.w;
                        } નહીંતર {
                            control->લીટીઓ[i].rect.x = 0;
                        }
                    } નહીંતર {
                        જો (first_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->લીટીઓ[i].rect.x = base_control->rect.w - control->લીટીઓ[i].rect.w;
                        } નહીંતર {
                            control->લીટીઓ[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#endif
    
    જો (base_control->do_size && control->sz) {
        base_control->rect.h = control->લીટીઓ[control->sz - 1].rect.y + control->લીટીઓ[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_ToolkitWindowX11 *window, અક્ષર *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    પૂર્ણાંક i;
    
    જો (!utf8) {
        પાછા ખાલી;
    }
 
    જો (!SDL_strcmp(utf8, "")) {
        પાછા ખાલી;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(કદ(SDL_ToolkitLabelControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    જો (!control) {
        SDL_SetError("Unable to allocate label control structure");
        પાછા ખાલી;
    }
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawLabelControl;
    base_control->func_on_state_change = ખાલી;
    base_control->func_calc_size = X11Toolkit_CalculateLabelControl;
    base_control->func_free  = X11Toolkit_DestroyLabelControl;
    base_control->func_on_scale_change = ખાલી;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = false;
    base_control->rect.w = 0;
    base_control->rect.h = 0;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_ગણતરી_લીટીઓ_Of_Text(utf8);
    control->લીટીઓ = SDL_calloc(control->sz, કદ(SDL_Toolkit_Label_Control_લીટી_X11));
    માટે (i = 0; i < control->sz; i++) {
        અચલ અક્ષર *lf = SDL_strchr(utf8, '\n');
        અચલ પૂર્ણાંક length = lf ? (lf - utf8) : SDL_strlen(utf8);
        પૂર્ણાંક sz;
        
        sz = length;
        જો (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#ifdef HAVE_FRIBIDI_H
        control->લીટીઓ[i].text = X11Toolkit_MakeTextElements(base_control->window, (અક્ષર *)utf8, sz, &control->લીટીઓ[i].par);
#નહીંતર 
        control->લીટીઓ[i].text = X11Toolkit_MakeTextElements(base_control->window, (અક્ષર *)utf8, sz);
#endif
        X11Toolkit_ShapeTextElements(base_control->window, control->લીટીઓ[i].text);

        utf8 += length + 1;
        જો (!lf) {
            તોડો;
        }
    }

    base_control->do_size = true;
    X11Toolkit_CalculateLabelControl(base_control);
    base_control->do_size = false;
    X11Toolkit_AddControlToWindow(window, base_control);

    પાછા base_control;
}

પૂર્ણાંક X11_Toolkit_Get_Label_Control_First_લીટી_Height(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    પાછા label_control->લીટીઓ[0].rect.h;
}

શૂન્ય X11Toolkit_SignalWindowClose(SDL_ToolkitWindowX11 *data) {
    data->close = true;
}

#endif // SDL_VIDEO_DRIVER_X11
