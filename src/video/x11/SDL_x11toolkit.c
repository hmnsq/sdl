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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#അന്തര്ഭാവ "../../SDL_list.h"
#അന്തര്ഭാവ "SDL_x11video.h"
#ifdef SDL_USE_LIBDBUS
#അന്തര്ഭാവ "../../core/linux/SDL_system_theme.h"
#endif
#ifdef HAVE_FRIBIDI_H
#അന്തര്ഭാവ "../../core/unix/SDL_fribidi.h"
#endif
#അന്തര്ഭാവ "SDL_x11dyn.h"
#അന്തര്ഭാവ "SDL_x11toolkit.h"
#അന്തര്ഭാവ "SDL_x11settings.h"
#അന്തര്ഭാവ "SDL_x11modes.h"
#അന്തര്ഭാവ "xsettings-client.h"
#അന്തര്ഭാവ <X11/keysym.h>
#അന്തര്ഭാവ <locale.h>

#define SDL_SET_LOCALE 1
#define SDL_GRAB 1

തരനിർവചനം എണ്ണൽ SDL_ToolkitTextTypeX11
{
    SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC,
    SDL_TOOLKIT_TEXT_TYPE_X11_THAI
} SDL_ToolkitTextTypeX11;

#ifdef HAVE_LIBTHAI_H
തരനിർവചനം ഘടന SDL_ToolkitThaiOverlayX11
{
    bool മുകൾ;
    അക്ഷരം *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#endif

തരനിർവചനം ഘടന SDL_ToolkitTextElementX11
{
    SDL_ToolkitTextTypeX11 type;
    അക്ഷരം *str;
    size_t sz;
    SDL_Rect rect;
    പൂർണ്ണസംഖ്യ font_h;
    ശൂന്യം (*str_free)(ശൂന്യം *);
#ifdef HAVE_LIBTHAI_H
    SDL_List_കണ്ണി *thai_overlays;
#endif
} SDL_ToolkitTextElementX11;

തരനിർവചനം ഘടന SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Icon type */
    SDL_MessageBoxFlags flags;
    അക്ഷരം icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    പൂർണ്ണസംഖ്യ icon_char_x;
    പൂർണ്ണസംഖ്യ icon_char_y;
    പൂർണ്ണസംഖ്യ icon_char_a;
    പൂർണ്ണസംഖ്യ icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

തരനിർവചനം ഘടന SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Data */
    സ്ഥിരം SDL_MessageBoxButtonData *data;

    /* Text */
    SDL_List_കണ്ണി *text;
    SDL_Rect text_rect;
    
    /* Callback */
    ശൂന്യം *cb_data;
    ശൂന്യം (*cb)(ഘടന SDL_ToolkitControlX11 *, ശൂന്യം *);
} SDL_ToolkitButtonControlX11;

തരനിർവചനം ഘടന SDL_Toolkit_Label_Control_വരി_X11
{
    SDL_List_കണ്ണി *text;
    SDL_Rect rect;
#ifdef HAVE_FRIBIDI_H
    FriBidiParType par;
#endif
} SDL_Toolkit_Label_Control_വരി_X11;

തരനിർവചനം ഘടന SDL_ToolkitLabelControlX11
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
    SDL_Toolkit_Label_Control_വരി_X11 *വരികൾ;
    size_t sz;
} SDL_ToolkitLabelControlX11;

തരനിർവചനം ഘടന SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_കണ്ണി *menu_ഇനങ്ങൾ;
} SDL_ToolkitMenuBarControlX11;

തരനിർവചനം ഘടന SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_കണ്ണി *menu_ഇനങ്ങൾ;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
സ്ഥിതം സ്ഥിരം അക്ഷരം *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#define G_ICONFONT_SIZE 22

/* General UI font */
സ്ഥിതം സ്ഥിരം അക്ഷരം g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
സ്ഥിതം സ്ഥിരം അക്ഷരം g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

സ്ഥിതം സ്ഥിരം അക്ഷരം *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    ശൂന്യ
};
#define G_TOOLKITFONT_SIZE 140

സ്ഥിതം സ്ഥിരം SDL_MessageBoxColor g_default_colors[SDL_MESSAGEBOX_COLOR_എണ്ണം] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ifdef SDL_USE_LIBDBUS
സ്ഥിതം സ്ഥിരം SDL_MessageBoxColor g_default_colors_dark[SDL_MESSAGEBOX_COLOR_എണ്ണം] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#എങ്കിൽ 0
സ്ഥിതം സ്ഥിരം SDL_MessageBoxColor g_default_colors_dark_മുകളിലെ_contrast[SDL_MESSAGEBOX_COLOR_എണ്ണം] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

സ്ഥിതം സ്ഥിരം SDL_MessageBoxColor g_default_colors_light_മുകളിലെ_contrast[SDL_MESSAGEBOX_COLOR_എണ്ണം] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#endif

#endif

സ്ഥിതം പൂർണ്ണസംഖ്യ g_shm_error;
സ്ഥിതം പൂർണ്ണസംഖ്യ (*g_old_error_handler)(Display *, XErrorEvent *) = ശൂന്യ;

സ്ഥിതം പൂർണ്ണസംഖ്യ X11Toolkit_SharedMemoryErrorHandler(Display *d, XErrorEvent *e)
{
    എങ്കിൽ (e->error_code == BadAccess || e->error_code == BadRequest) {
        g_shm_error = True;
        തിരികെ 0;
    }
    തിരികെ g_old_error_handler(d, e);
}

സ്ഥിതം ശൂന്യം X11Toolkit_InitWindowPixmap(SDL_ToolkitWindowX11 *data) {
    എങ്കിൽ (data->pixmap) {
#ifndef NO_SHARED_MEMORY
        എങ്കിൽ (!data->shm_pixmap) {
            data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
        }
#അല്ലെങ്കിൽ
        data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
#endif
#ifndef NO_SHARED_MEMORY
        എങ്കിൽ (data->shm) {
            data->image = X11_XShmCreateImage(data->display, data->visual, data->depth, ZPixmap, ശൂന്യ, &data->shm_info, data->pixmap_width, data->pixmap_height);
            എങ്കിൽ (data->image) {
                data->shm_bytes_per_വരി = data->image->bytes_per_വരി;

                data->shm_info.shmid = shmget(IPC_PRIVATE, data->image->bytes_per_വരി * data->image->height, IPC_CREAT | 0777);
                എങ്കിൽ (data->shm_info.shmid < 0) {
                    XDestroyImage(data->image);
                    data->image = ശൂന്യ;
                    data->shm = false;
                    തിരികെ;
                }

                data->shm_info.readOnly = False;
                data->shm_info.shmaddr = data->image->data = (അക്ഷരം *)shmat(data->shm_info.shmid, ശൂന്യ, 0);
                എങ്കിൽ (((signed അക്ഷരം *)data->shm_info.shmaddr) == (signed അക്ഷരം *)-1) {
                    XDestroyImage(data->image);
                    data->shm = false;
                    data->image = ശൂന്യ;
                    തിരികെ;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11Toolkit_SharedMemoryErrorHandler);
                X11_XShmAttach(data->display, &data->shm_info);
                X11_XSync(data->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                എങ്കിൽ (g_shm_error) {
                    XDestroyImage(data->image);
                    shmdt(data->shm_info.shmaddr);
                    shmctl(data->shm_info.shmid, IPC_RMID, ശൂന്യ);
                    data->image = ശൂന്യ;
                    data->shm = false;
                    തിരികെ;
                }

                എങ്കിൽ (data->shm_pixmap) {
                    data->drawable = X11_XShmCreatePixmap(data->display, data->window, data->shm_info.shmaddr, &data->shm_info, data->pixmap_width, data->pixmap_height, data->depth);
                    എങ്കിൽ (data->drawable == None) {
                        data->shm_pixmap = False;
                    } അല്ലെങ്കിൽ {
                        XDestroyImage(data->image);
                        data->image = ശൂന്യ;
                    }
                }

                shmctl(data->shm_info.shmid, IPC_RMID, ശൂന്യ);
            } അല്ലെങ്കിൽ {
                data->shm = false;
            }
        }
#endif
    }
}

സ്ഥിതം ശൂന്യം X11Toolkit_InitWindowFonts(SDL_ToolkitWindowX11 *window)
{    
    window->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    window->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#ifdef X_HAVE_UTF8_STRING
    window->utf8 = true;
    window->font_set = ശൂന്യ;
    എങ്കിൽ (SDL_X11_HAVE_UTF8) {
        അക്ഷരം **missing = ശൂന്യ;
        പൂർണ്ണസംഖ്യ അക്കം_missing = 0;
        പൂർണ്ണസംഖ്യ i_font;
        window->font_struct = ശൂന്യ;
        വേണ്ടി (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            അക്ഷരം *font;

            എങ്കിൽ (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_load_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_SIZE * window->iscale);
                window->font_set = X11_XCreateFontSet(window->display, font, &missing, &അക്കം_missing, ശൂന്യ);
                SDL_free(font);

                എങ്കിൽ (!window->font_set) {
                    എങ്കിൽ (window->scale != 0 && window->iscale > 0) {
                        window->iscale = (പൂർണ്ണസംഖ്യ)SDL_ceilf(window->scale);
                        window->scale = 0;
                    } അല്ലെങ്കിൽ {
                        window->iscale--;
                    }
                    പോകുക try_load_font;
                }
            } അല്ലെങ്കിൽ {
                window->font_set = X11_XCreateFontSet(window->display, g_ToolkitFont[i_font], &missing, &അക്കം_missing, ശൂന്യ);
            }

            എങ്കിൽ (missing) {
                X11_XFreeStringList(missing);
            }

            എങ്കിൽ (window->font_set) {
                നിർത്തുക;
            }
        }

        എങ്കിൽ (!window->font_set) {
            പോകുക load_font_traditional;
        } അല്ലെങ്കിൽ {
            XFontStruct **font_structs;
            അക്ഷരം **font_names;
            പൂർണ്ണസംഖ്യ font_sz;
            പൂർണ്ണസംഖ്യ i;
            
#ifdef HAVE_FRIBIDI_H
            window->do_shaping = !X11_XContextDependentDrawing(window->font_set);
#endif
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFontsOfFontSet(window->font_set, &font_structs, &font_names);
            വേണ്ടി (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                എങ്കിൽ (SDL_strstr(font_names[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strstr(font_names[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strstr(font_names[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strstr(font_names[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } അല്ലെങ്കിൽ എങ്കിൽ (SDL_strstr(font_names[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                എങ്കിൽ (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(window->display, font_names[i]);
                    എങ്കിൽ (font_struct) {
                        എങ്കിൽ (font_struct->per_char) {
                            പൂർണ്ണസംഖ്യ glyphs_sz;
                            പൂർണ്ണസംഖ്യ j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            വേണ്ടി (j = 0; j < glyphs_sz; j++) {
                                എങ്കിൽ (font_struct->per_char[j].lbearing < 0) {
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
    } അല്ലെങ്കിൽ
#endif
    {
        അക്ഷരം *font;

        load_font_traditional:
        window->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        window->font_struct = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        എങ്കിൽ (!window->font_struct) {
            എങ്കിൽ (window->iscale > 0) {
                എങ്കിൽ (window->scale != 0) {
                    window->iscale = (പൂർണ്ണസംഖ്യ)SDL_ceilf(window->scale);
                    window->scale = 0;
                } അല്ലെങ്കിൽ {
                    window->iscale--;
                }
                പോകുക load_font_traditional;
            } അല്ലെങ്കിൽ {
                window->font_struct = X11_XLoadQueryFont(window->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

സ്ഥിതം ശൂന്യം X11Toolkit_SettingsNotify(സ്ഥിരം അക്ഷരം *name, XSettingsAction action, XSettingsSetting *setting, ശൂന്യം *data)
{
    SDL_ToolkitWindowX11 *window;
    പൂർണ്ണസംഖ്യ i;

    window = data;

    എങ്കിൽ (window->xsettings_first_time) {
        തിരികെ;
    }

    എങ്കിൽ (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_setup = false;
        bool pixmap_already_setup = false;

        എങ്കിൽ (window->pixmap) {
            pixmap_already_setup = true;
        } അല്ലെങ്കിൽ {
            dbe_already_setup = true;
        }

        /* set scale vars */
        window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
        window->iscale = (പൂർണ്ണസംഖ്യ)SDL_ceilf(window->scale);
        എങ്കിൽ (window->scale < 1) {
            window->scale = 1;
        }
        എങ്കിൽ (SDL_roundf(window->scale) == window->scale) {
            window->scale = 0;
        }

        /* setup fonts */
#ifdef X_HAVE_UTF8_STRING
        എങ്കിൽ (window->font_set) {
            X11_XFreeFontSet(window->display, window->font_set);
        }
#endif
        എങ്കിൽ (window->font_struct) {
            X11_XFreeFont(window->display, window->font_struct);
        }

        X11Toolkit_InitWindowFonts(window);

        /* set up window */
        എങ്കിൽ (window->scale != 0) {
            window->window_width = SDL_lroundf((window->window_width/window->iscale) * window->scale);
            window->window_height = SDL_lroundf((window->window_height/window->iscale) * window->scale);
            window->pixmap_width = window->window_width;
            window->pixmap_height = window->window_height;
            window->pixmap = true;
        } അല്ലെങ്കിൽ {
            window->pixmap = false;
        }

        എങ്കിൽ (window->pixmap) {
            എങ്കിൽ (!pixmap_already_setup) {
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                എങ്കിൽ (SDL_X11_HAVE_XDBE && window->xdbe) {
                    X11_XdbeDeallocateBackBufferName(window->display, window->buf);
                }
#endif
            }
            X11_XFreePixmap(window->display, window->drawable);
            X11Toolkit_InitWindowPixmap(window);
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (!dbe_already_setup) {
                X11_XFreePixmap(window->display, window->drawable);
#ifndef NO_SHARED_MEMORY
                എങ്കിൽ (window->image) {
                    XDestroyImage(window->image);
                    window->image = ശൂന്യ;
                }
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                എങ്കിൽ (SDL_X11_HAVE_XDBE && window->xdbe) {
                    window->buf = X11_XdbeAllocateBackBufferName(window->display, window->window, XdbeUndefined);
                    window->drawable = window->buf;
                }
#endif
            }
        }

        /* notify controls */
        വേണ്ടി (i = 0; i < window->controls_sz; i++) {
            window->controls[i]->do_size = true;

            എങ്കിൽ (window->controls[i]->func_on_scale_change) {
                window->controls[i]->func_on_scale_change(window->controls[i]);
            }

            എങ്കിൽ (window->controls[i]->func_calc_size) {
                window->controls[i]->func_calc_size(window->controls[i]);
            }

            window->controls[i]->do_size = false;
        }

        /* notify cb */
        എങ്കിൽ (window->cb_on_scale_change) {
            window->cb_on_scale_change(window, window->cb_data);
        }

        /* update ev scales */
        എങ്കിൽ (!window->pixmap) {
            window->ev_scale = window->ev_iscale = 1;
        } അല്ലെങ്കിൽ {
            window->ev_scale = window->scale;
            window->ev_iscale = window->iscale;
        }
    }
}

സ്ഥിതം ശൂന്യം X11Toolkit_GetTextWidthHeightForFont(XFontStruct *font, സ്ഥിരം അക്ഷരം *str, പൂർണ്ണസംഖ്യ nbytes, പൂർണ്ണസംഖ്യ *pwidth, പൂർണ്ണസംഖ്യ *pheight, പൂർണ്ണസംഖ്യ *ascent, പൂർണ്ണസംഖ്യ *font_height)
{
    XCharStruct text_structure;
    പൂർണ്ണസംഖ്യ font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &text_structure);
    *pwidth = text_structure.width;
    *pheight = text_structure.ascent + text_structure.descent;
    *ascent = text_structure.ascent;
    എങ്കിൽ (font_height) {
       *font_height = font_ascent + font_descent;
    }
}

സ്ഥിതം ശൂന്യം X11Toolkit_GetTextWidthHeight(SDL_ToolkitWindowX11 *data, സ്ഥിരം അക്ഷരം *str, പൂർണ്ണസംഖ്യ nbytes, പൂർണ്ണസംഖ്യ *pwidth, പൂർണ്ണസംഖ്യ *pheight, പൂർണ്ണസംഖ്യ *ascent, പൂർണ്ണസംഖ്യ *descent, പൂർണ്ണസംഖ്യ *font_height)
{
#ifdef X_HAVE_UTF8_STRING
    എങ്കിൽ (data->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8TextExtents(data->font_set, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.width;
        *pheight = overall_logical.height;
        *ascent = -overall_logical.y;
        *descent = overall_logical.height - *ascent;

        എങ്കിൽ (font_height) {
            XFontSetExtents *extents;

            extents = X11_XExtentsOfFontSet(data->font_set);
            *font_height = extents->max_logical_extent.height;
        }
    } അല്ലെങ്കിൽ
#endif
    {
        XCharStruct text_structure;
        പൂർണ്ണസംഖ്യ font_direction, font_ascent, font_descent;
        X11_XTextExtents(data->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &text_structure);
        *pwidth = text_structure.width;
        *pheight = text_structure.ascent + text_structure.descent;
        *ascent = text_structure.ascent;
        *descent = text_structure.descent;

        എങ്കിൽ (font_height) {
            *font_height = font_ascent + font_descent;
        }
    }
}

#ifdef HAVE_FRIBIDI_H
SDL_List_കണ്ണി *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, അക്ഷരം *txt, size_t sz, FriBidiParType *par)
#അല്ലെങ്കിൽ
SDL_List_കണ്ണി *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, അക്ഷരം *txt, size_t sz)
#endif
{
    SDL_List_കണ്ണി *list;
    അക്ഷരം *str;
    അക്ഷരം *buffer;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = ശൂന്യ;
    thai = 0;
    str = txt;
    buffer = SDL_malloc(1);
    buffer[0] = 0;
    
#ifdef HAVE_FRIBIDI_H
    എങ്കിൽ (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    എങ്കിൽ (data->fribidi) {
        അക്ഷരം *fstr;
                
        fstr = SDL_FriBidi_Process(data->fribidi, str, sz, data->do_shaping, par);
        എങ്കിൽ (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#endif        

    ആകുമ്പോൾ (1) {
        അക്ഷരം *new;
        അക്ഷരം utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_StepUTF8((സ്ഥിരം അക്ഷരം **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        എങ്കിൽ (cp == 0 || cond == (thai ? false : true)) {
            SDL_ToolkitTextElementX11 *element;
            
            element = SDL_malloc(വലുപ്പം(SDL_ToolkitTextElementX11));
            എങ്കിൽ (thai) {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_THAI;
            } അല്ലെങ്കിൽ {
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

        എങ്കിൽ (!cp) {
            നിർത്തുക;
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
    എങ്കിൽ (free_txt) {
        SDL_free(txt);
    }
    തിരികെ list;
}

ശൂന്യം X11Toolkit_ShapeTextElements(SDL_ToolkitWindowX11 *data, SDL_List_കണ്ണി *list)
{
    SDL_List_കണ്ണി *cursor;
    SDL_ToolkitTextElementX11 *prev;
    പൂർണ്ണസംഖ്യ temp;
    
    /* Shape and calculate bounding box */
    cursor = list;
    ആകുമ്പോൾ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
#ifdef HAVE_LIBTHAI_H
        element->thai_overlays = ശൂന്യ;
#endif
        എങ്കിൽ (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            എങ്കിൽ (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, ശൂന്യ);
            } അല്ലെങ്കിൽ {
#ifdef HAVE_LIBTHAI_H
                എങ്കിൽ (data->th) {
                    ഘടന thcell_t *cells;
                    അക്ഷരം *tis_str;
                    അക്ഷരം *base_tis_str;
                    size_t cells_sz;
                    size_t base_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, വലുപ്പം(ഘടന thcell_t));
                    data->th->make_cells((സ്ഥിരം thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    base_tis_str_sz = cells_sz;
                    base_tis_str = SDL_malloc(base_tis_str_sz + 1);
                    വേണ്ടി (temp = 0; temp < cells_sz; temp++) {
                        base_tis_str[temp] = cells[temp].base;
                        
                        എങ്കിൽ (cells[temp].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            അക്ഷരം *pre;
                            പൂർണ്ണസംഖ്യ temp2;
                            
                            overlay = SDL_malloc(വലുപ്പം(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (സ്ഥിരം അക്ഷരം *)&cells[temp].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->മുകൾ = false;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ശൂന്യ);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ശൂന്യ);
                            SDL_ListAdd(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        എങ്കിൽ (cells[temp].മുകൾ) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            അക്ഷരം *pre;
                            പൂർണ്ണസംഖ്യ temp2;
                            
                            overlay = SDL_malloc(വലുപ്പം(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (സ്ഥിരം അക്ഷരം *)&cells[temp].മുകൾ, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->മുകൾ = true;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ശൂന്യ);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ശൂന്യ);
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
#അല്ലെങ്കിൽ
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
#endif            
            }
        } അല്ലെങ്കിൽ {
            X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
        }
        
        cursor = cursor->next;
    }
    
    /* Add offsets */
    prev = ശൂന്യ;
    cursor = list;
    ആകുമ്പോൾ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;        
        എങ്കിൽ (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } അല്ലെങ്കിൽ {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->next;
    }
}


ശൂന്യം X11Toolkit_DrawTextElements(SDL_ToolkitWindowX11 *data, SDL_List_കണ്ണി *list, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y)
{
    SDL_List_കണ്ണി *cursor;
    
    cursor = list;
    
    ആകുമ്പോൾ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        എങ്കിൽ (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            എങ്കിൽ (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
#ifdef X_HAVE_UTF8_STRING
                എങ്കിൽ (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } അല്ലെങ്കിൽ
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } അല്ലെങ്കിൽ {    
#ifdef HAVE_LIBTHAI_H
                SDL_List_കണ്ണി *overlay_cursor;
                    
                /* Draw the base string */
#ifdef X_HAVE_UTF8_STRING
                എങ്കിൽ (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } അല്ലെങ്കിൽ
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                ആകുമ്പോൾ (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->entry;
#ifdef X_HAVE_UTF8_STRING
                    എങ്കിൽ (data->utf8) {
                        X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } അല്ലെങ്കിൽ
#endif
                    {
                        X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->next;
                }
#endif                
            }
        } അല്ലെങ്കിൽ {
#ifdef X_HAVE_UTF8_STRING
            എങ്കിൽ (data->utf8) {
                X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } അല്ലെങ്കിൽ
#endif
            {
                X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->next;
    }
}

പൂർണ്ണസംഖ്യ X11Toolkit_GetTextElementsRect(SDL_List_കണ്ണി *list, SDL_Rect *out)
{
    SDL_List_കണ്ണി *cursor;
    പൂർണ്ണസംഖ്യ ret;
    
    ret = 0;
    out->x = out->y = 0;
    out->w = out->h = 0;
    cursor = list;
    ആകുമ്പോൾ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        
        out->w += element->rect.w;
        out->h = SDL_max(out->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->next;
    }
    
    തിരികെ ret;
}

ശൂന്യം X11Toolkit_FreeTextElementsListContents(SDL_List_കണ്ണി *list)
{
    SDL_List_കണ്ണി *cursor;
    
    cursor = list;
    ആകുമ്പോൾ (cursor) {
        SDL_ToolkitTextElementX11 *element;
#ifdef HAVE_LIBTHAI_H
        SDL_List_കണ്ണി *overlay_cursor;
#endif

        element = cursor->entry;
        
        എങ്കിൽ (element->str_free) {
            element->str_free(element->str);
        }
        
#ifdef HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        ആകുമ്പോൾ (overlay_cursor) {
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
 
സ്ഥിതം bool X11Toolkit_ShouldFlipUI(ശൂന്യം) 
{
    SDL_Locale **current_locales;
    സ്ഥിതം സ്ഥിരം SDL_Locale rtl_locales[] = {
        { "ar", ശൂന്യ, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", ശൂന്യ, },
        { "iw", ശൂന്യ, },
        { "yi", ശൂന്യ, },
        { "ur", ശൂന്യ, },
        { "ug", ശൂന്യ, },
        { "kd", ശൂന്യ, },
        { "pk", "PK", },
        { "ps", ശൂന്യ, }
    }; 
    പൂർണ്ണസംഖ്യ current_locales_sz;
    പൂർണ്ണസംഖ്യ i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    എങ്കിൽ (current_locales_sz <= 0) {
        തിരികെ false;        
    }
    വേണ്ടി (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        എങ്കിൽ (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            എങ്കിൽ (!rtl_locales[i].country) {
                തിരികെ true;
            } അല്ലെങ്കിൽ {
                തിരികെ SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    തിരികെ false;
}

SDL_ToolkitWindowX11 *X11Toolkit_CreateWindowStruct(SDL_Window *parent, SDL_ToolkitWindowX11 *tkparent, SDL_ToolkitWindowModeX11 mode, സ്ഥിരം SDL_MessageBoxColor *colorhints, bool create_new_display)
{
    SDL_ToolkitWindowX11 *window;
    പൂർണ്ണസംഖ്യ i;
#ifdef SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#endif
    #define ErrorFreeRetNull(x, y) SDL_SetError(x); SDL_free(y); തിരികെ ശൂന്യ
    #define ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_SetError(x, y); SDL_free(z); തിരികെ ശൂന്യ

    എങ്കിൽ (!SDL_X11_LoadSymbols()) {
        തിരികെ ശൂന്യ;
    }

    // This code could get called from multiple threads maybe?
    X11_XInitThreads();

    window = (SDL_ToolkitWindowX11 *)SDL_malloc(വലുപ്പം(SDL_ToolkitWindowX11));
    എങ്കിൽ (!window) {
        SDL_SetError("Unable to allocate toolkit window structure");
        തിരികെ ശൂന്യ;
    }

    window->mode = mode;
    window->tk_parent = tkparent;

#എങ്കിൽ SDL_SET_LOCALE
    എങ്കിൽ (mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        window->origlocale = setlocale(LC_ALL, ശൂന്യ);
        എങ്കിൽ (window->origlocale) {
            window->origlocale = SDL_strdup(window->origlocale);
            എങ്കിൽ (!window->origlocale) {
                SDL_free(window);
                തിരികെ ശൂന്യ;
            }
            (ശൂന്യം)setlocale(LC_ALL, "");
        }
    }
#endif

    window->parent_device = ശൂന്യ;
    എങ്കിൽ (create_new_display) {
        window->display = X11_XOpenDisplay(ശൂന്യ);
        window->display_close = true;
        എങ്കിൽ (!window->display) {
            ErrorFreeRetNull("Couldn't open X11 display", window);
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (parent) {
            window->parent_device = SDL_GetVideoDevice();
            window->display = window->parent_device->internal->display;
            window->display_close = false;
        } അല്ലെങ്കിൽ എങ്കിൽ (tkparent) {
            window->display = tkparent->display;
            window->display_close = false;
        } അല്ലെങ്കിൽ {
            window->display = X11_XOpenDisplay(ശൂന്യ);
            window->display_close = true;
            എങ്കിൽ (!window->display) {
                ErrorFreeRetNull("Couldn't open X11 display", window);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    പൂർണ്ണസംഖ്യ xrandr_event_base, xrandr_error_base;
    window->xrandr = X11_XRRQueryExtension(window->display, &xrandr_event_base, &xrandr_error_base);
#endif

#ifndef NO_SHARED_MEMORY
    window->shm_pixmap = False;
    window->shm = X11_XShmQueryExtension(window->display) ? SDL_X11_HAVE_SHM : false;
    എങ്കിൽ (window->shm) {
        പൂർണ്ണസംഖ്യ major;
        പൂർണ്ണസംഖ്യ minor;

        X11_XShmQueryVersion(window->display, &major, &minor, &window->shm_pixmap);
        എങ്കിൽ (window->shm_pixmap) {
            എങ്കിൽ (X11_XShmPixmapFormat(window->display) != ZPixmap) {
                window->shm_pixmap = False;
            }
        }
    }
#endif

    /* Scale/Xsettings */
    window->pixmap = false;
    window->xsettings_first_time = true;
    window->xsettings = xsettings_client_new(window->display, DefaultScreen(window->display), X11Toolkit_SettingsNotify, ശൂന്യ, window);
    window->xsettings_first_time = false;
    window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
    എങ്കിൽ (window->scale < 1) {
        window->scale = 1;
    }
    window->iscale = (പൂർണ്ണസംഖ്യ)SDL_ceilf(window->scale);
    എങ്കിൽ (SDL_roundf(window->scale) == window->scale) {
        window->scale = 0;
    }

    /* Fonts */
    X11Toolkit_InitWindowFonts(window);

    /* Color hints */
#ifdef SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    എങ്കിൽ (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#endif

    എങ്കിൽ (!colorhints) {
#ifdef SDL_USE_LIBDBUS
        തിരഞ്ഞെടുപ്പ് (theme) {
            അവസ്ഥ SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                നിർത്തുക;
#എങ്കിൽ 0
            അവസ്ഥ SDL_SYSTEM_THEME_LIGHT_മുകളിലെ_CONTRAST:
                colorhints = g_default_colors_light_മുകളിലെ_contrast;
                നിർത്തുക;
            അവസ്ഥ SDL_SYSTEM_THEME_DARK_മുകളിലെ_CONTRAST:
                colorhints = g_default_colors_dark_മുകളിലെ_contrast;
                നിർത്തുക;
#endif
            സ്ഥിരസ്ഥിതി:
                colorhints = g_default_colors;
        }
#അല്ലെങ്കിൽ
        colorhints = g_default_colors;
#endif
    }
    window->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    വേണ്ടി (i = 0; i < SDL_MESSAGEBOX_COLOR_എണ്ണം; i++) {
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
    എങ്കിൽ (parent) {
        SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(parent);
        window->screen = displaydata->screen;
    } അല്ലെങ്കിൽ {
        window->screen = DefaultScreen(window->display);
    }

    /* Visuals */
    എങ്കിൽ (mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        window->visual = parent->internal->visual;
        window->cmap = parent->internal->colormap;
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
        window->depth = window->vi.depth;
    } അല്ലെങ്കിൽ {
        window->visual = DefaultVisual(window->display, window->screen);
        window->cmap = DefaultColormap(window->display, window->screen);
        window->depth = DefaultDepth(window->display, window->screen);
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
    }

    /* Allocate colors */
    വേണ്ടി (i = 0; i < SDL_MESSAGEBOX_COLOR_എണ്ണം; i++) {
        X11_XAllocColor(window->display, window->cmap, &window->xcolor[i]);
    }
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l1);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l2);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_d);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_pressed);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_disabled_text);

    /* Control list */
    window->has_focus = false;
    window->controls = ശൂന്യ;
    window->controls_sz = 0;
    window->dyn_controls_sz = 0;
    window->fiddled_control = ശൂന്യ;
    window->dyn_controls = ശൂന്യ;

    /* Menu windows */
    window->popup_windows = ശൂന്യ;

    /* BIDI engine */
#ifdef HAVE_FRIBIDI_H
    window->fribidi = SDL_FriBidi_Create();
#endif

#ifdef HAVE_LIBTHAI_H
    window->th = SDL_LibThai_Create();
#endif
    
    /* Interface direction */
    window->flip_interface = X11Toolkit_ShouldFlipUI();
    
    തിരികെ window;
}

സ്ഥിതം ശൂന്യം X11Toolkit_AddControlToWindow(SDL_ToolkitWindowX11 *window, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    window->controls_sz++;
    എങ്കിൽ (window->controls_sz == 1) {
        window->controls = (ഘടന SDL_ToolkitControlX11 **)SDL_malloc(വലുപ്പം(ഘടന SDL_ToolkitControlX11 *));
    } അല്ലെങ്കിൽ {
        window->controls = (ഘടന SDL_ToolkitControlX11 **)SDL_realloc(window->controls, വലുപ്പം(ഘടന SDL_ToolkitControlX11 *) * window->controls_sz);
    }
    window->controls[window->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    എങ്കിൽ (control->dynamic) {
        window->dyn_controls_sz++;
        എങ്കിൽ (window->dyn_controls_sz == 1) {
            window->dyn_controls = (ഘടന SDL_ToolkitControlX11 **)SDL_malloc(വലുപ്പം(ഘടന SDL_ToolkitControlX11 *));
        } അല്ലെങ്കിൽ {
            window->dyn_controls = (ഘടന SDL_ToolkitControlX11 **)SDL_realloc(window->dyn_controls, വലുപ്പം(ഘടന SDL_ToolkitControlX11 *) * window->dyn_controls_sz);
        }
        window->dyn_controls[window->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    എങ്കിൽ (control->selected) {
        window->focused_control = control;
    }
}

bool X11Toolkit_CreateWindowRes(SDL_ToolkitWindowX11 *data, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h, പൂർണ്ണസംഖ്യ cx, പൂർണ്ണസംഖ്യ cy, അക്ഷരം *title)
{
    പൂർണ്ണസംഖ്യ x, y;
    XSizeHints *sizehints;
    XSetWindowAttributes wnd_attr;
    Atom _NET_WM_WINDOW_TYPE, _NET_WM_WINDOW_TYPE_DIALOG, _NET_WM_WINDOW_TYPE_DROPDOWN_MENU, _NET_WM_WINDOW_TYPE_TOOLTIP;
    SDL_WindowData *windowdata = ശൂന്യ;
    Display *display = data->display;
    XGCValues ctx_vals;
    Window വേര്_win;
    Window parent_win;
    unsigned long gcflags = GCForeground | GCBackground;
    unsigned long valuemask;
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
#ifdef XRANDR_DISABLED_BY_DEFAULT
    സ്ഥിരം bool use_xrandr_by_default = false;
#അല്ലെങ്കിൽ
    സ്ഥിരം bool use_xrandr_by_default = true;
#endif
#endif

    എങ്കിൽ (data->scale == 0) {
        data->window_width = w;
        data->window_height = h;
    } അല്ലെങ്കിൽ {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        data->pixmap = true;
    }

    എങ്കിൽ (data->parent) {
        windowdata = data->parent->internal;
    }

    valuemask = CWEventMask | CWColormap;
    data->event_mask = ExposureMask |
                       ButtonPressMask | ButtonReleaseMask | താക്കോൽ_Press_Mask | താക്കോൽ_Release_Mask |
                       StructureNotifyMask | FocusChangeMask | PointerMotionMask;
    wnd_attr.event_mask = data->event_mask;
    wnd_attr.colormap = data->cmap;
    എങ്കിൽ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    വേര്_win = വേര്_Window(display, data->screen);
    എങ്കിൽ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        parent_win = windowdata->xwindow;
    } അല്ലെങ്കിൽ {
        parent_win = വേര്_win;
    }

    data->window = X11_XCreateWindow(
        display, parent_win,
        0, 0,
        data->window_width, data->window_height,
        0, data->depth, നിവേശം_Output, data->visual,
        valuemask, &wnd_attr);
    എങ്കിൽ (data->window == None) {
        തിരികെ SDL_SetError("Couldn't create X window");
    }

    എങ്കിൽ (windowdata && data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
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
                            PropModeReplace, (unsigned അക്ഷരം *)stateatoms, statecount);
    }

    എങ്കിൽ (windowdata && data->mode != SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        X11_XSetTransientForHint(display, data->window, windowdata->xwindow);
    }

    എങ്കിൽ (data->tk_parent) {
        X11_XSetTransientForHint(display, data->window, data->tk_parent->window);
    }

    SDL_X11_SetWindowTitle(display, data->window, title);

    // Let the window manager the type of the window
    എങ്കിൽ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned അക്ഷരം *)&_NET_WM_WINDOW_TYPE_DIALOG, 1);
    } അല്ലെങ്കിൽ എങ്കിൽ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned അക്ഷരം *)&_NET_WM_WINDOW_TYPE_DROPDOWN_MENU, 1);
    } അല്ലെങ്കിൽ എങ്കിൽ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned അക്ഷരം *)&_NET_WM_WINDOW_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    data->wm_delete_message = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, data->window, &data->wm_delete_message, 1);
    data->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    എങ്കിൽ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        x = cx;
        y = cy;
        പോകുക MOVEWINDOW;
    }
    എങ്കിൽ (windowdata) {
        XWindowAttributes attrib;
        Window dummy;

        X11_XGetWindowAttributes(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.width - data->window_width) / 2;
        y = attrib.y + (attrib.height - data->window_height) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, വേര്_Window(display, data->screen), x, y, &x, &y, &dummy);
    } അല്ലെങ്കിൽ {
        സ്ഥിരം SDL_VideoDevice *dev = SDL_GetVideoDevice();
        എങ്കിൽ (dev && dev->displays && dev->അക്കം_displays > 0) {
            സ്ഥിരം SDL_VideoDisplay *dpy = dev->displays[0];
            സ്ഥിരം SDL_DisplayData *dpydata = dpy->internal;
            x = dpydata->x + ((dpy->current_mode->w - data->window_width) / 2);
            y = dpydata->y + ((dpy->current_mode->h - data->window_height) / 3);
        }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
        അല്ലെങ്കിൽ എങ്കിൽ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && data->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_out;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, വേര്_win);
            എങ്കിൽ (!screen_res) {
                പോകുക NOXRANDR;
            }

            default_out = X11_XRRGetOutputPrimary(display, വേര്_win);
            എങ്കിൽ (default_out != None) {
                XRROutputInfo *out_info;

                out_info = X11_XRRGetOutputInfo(display, screen_res, default_out);
                എങ്കിൽ (out_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(out_info);
                    പോകുക FIRSTOUTPUTXRANDR;
                }

                എങ്കിൽ (out_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                } അല്ലെങ്കിൽ എങ്കിൽ (out_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                } അല്ലെങ്കിൽ {
                    crtc_info = ശൂന്യ;
                }
                
                എങ്കിൽ (crtc_info) {
                    x = (crtc_info->width - data->window_width) / 2;
                    y = (crtc_info->height - data->window_height) / 3;
                    X11_XRRFreeOutputInfo(out_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } അല്ലെങ്കിൽ {
                    X11_XRRFreeOutputInfo(out_info);
                    പോകുക NOXRANDR;
                }
            } അല്ലെങ്കിൽ {
                    FIRSTOUTPUTXRANDR:
                    എങ്കിൽ (screen_res->noutput > 0) {
                        XRROutputInfo *out_info;

                        out_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        എങ്കിൽ (!out_info) {
                            പോകുക FIRSTCRTCXRANDR;
                        }

                        എങ്കിൽ (out_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                        } അല്ലെങ്കിൽ എങ്കിൽ (out_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                        } അല്ലെങ്കിൽ {
                            crtc_info = ശൂന്യ;
                        }

                        എങ്കിൽ (!crtc_info) {
                            X11_XRRFreeOutputInfo(out_info);
                            പോകുക FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeOutputInfo(out_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        പോകുക MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    എങ്കിൽ (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        പോകുക NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    എങ്കിൽ (crtc_info) {
                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } അല്ലെങ്കിൽ {
                        X11_XRRFreeScreenResources(screen_res);
                        പോകുക NOXRANDR;
                    }
            }
        }
#endif
        അല്ലെങ്കിൽ {
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
    എങ്കിൽ (sizehints) {
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
    എങ്കിൽ (SDL_X11_HAVE_XDBE && !data->pixmap) {
        പൂർണ്ണസംഖ്യ xdbe_major, xdbe_minor;
        എങ്കിൽ (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            data->xdbe = true;
            data->buf = X11_XdbeAllocateBackBufferName(display, data->window, XdbeUndefined);
            data->drawable = data->buf;
        } അല്ലെങ്കിൽ {
            data->xdbe = false;
        }
    }
#endif

    X11Toolkit_InitWindowPixmap(data);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    എങ്കിൽ (!data->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = data->font_struct->fid;
    }
    data->ctx = X11_XCreateGC(data->display, data->drawable, gcflags, &ctx_vals);
    എങ്കിൽ (data->ctx == None) {
        തിരികെ SDL_SetError("Couldn't create graphics context");
    }

    data->close = false;
    data->താക്കോൽ_control_esc = data->താക്കോൽ_control_enter = ശൂന്യ;
    എങ്കിൽ (!data->pixmap) {
        data->ev_scale = data->ev_iscale = 1;
    } അല്ലെങ്കിൽ {
        data->ev_scale = data->scale;
        data->ev_iscale = data->iscale;
    }

#എങ്കിൽ SDL_GRAB
    എങ്കിൽ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XGrabPointer(display, data->window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
        X11_XGrabKeyboard(display, data->window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
#endif

    തിരികെ true;
}

സ്ഥിതം ശൂന്യം X11Toolkit_DrawWindow(SDL_ToolkitWindowX11 *data) {
    SDL_Rect rect;
    പൂർണ്ണസംഖ്യ i;

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    എങ്കിൽ (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeBeginIdiom(data->display);
    }
#endif

    X11_XSetForeground(data->display, data->ctx, data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    എങ്കിൽ (data->pixmap) {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->pixmap_width, data->pixmap_height);
    } അല്ലെങ്കിൽ {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->window_width, data->window_height);
    }

    വേണ്ടി (i = 0; i < data->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = data->controls[i];
        എങ്കിൽ (control) {
            എങ്കിൽ (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    എങ്കിൽ (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        XdbeSwapInfo swap_info;
        swap_info.swap_window = data->window;
        swap_info.swap_action = XdbeUndefined;
        X11_XdbeSwapBuffers(data->display, &swap_info, 1);
        X11_XdbeEndIdiom(data->display);
    }
#endif

    എങ്കിൽ (data->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = data->window_width;
        rect.h = data->window_height;
#ifndef NO_SHARED_MEMORY
        എങ്കിൽ (data->shm) {
            എങ്കിൽ (data->shm_pixmap) {
                X11_XFlush(data->display);
                X11_XSync(data->display, false);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->shm_info.shmaddr, data->shm_bytes_per_വരി);
                SDL_BlitSurfaceScaled(scale_surface, ശൂന്യ, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(data->display, data->drawable, data->window, data->ctx, 0, 0, data->window_width, data->window_height, 0, 0);
            } അല്ലെങ്കിൽ {
                X11_XShmGetImage(data->display, data->drawable, data->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->image->data, data->image->bytes_per_വരി);
                SDL_BlitSurfaceScaled(scale_surface, ശൂന്യ, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                X11_XShmPutImage(data->display, data->window, data->ctx, data->image, 0, 0, 0, 0, data->window_width, data->window_height, False);
            }
        } അല്ലെങ്കിൽ
#endif
        {
            XImage *image;

            image = X11_XGetImage(data->display, data->drawable, 0, 0 , data->pixmap_width, data->pixmap_height, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), image->data, image->bytes_per_വരി);
            SDL_BlitSurfaceScaled(scale_surface, ശൂന്യ, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
            X11_XPutImage(data->display, data->window, data->ctx, image, 0, 0, 0, 0, data->window_width, data->window_height);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(data->display);
}

സ്ഥിതം SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_ToolkitWindowX11 *data, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < data->controls_sz; i++) {
        SDL_Rect *rect = &data->controls[i]->rect;
        എങ്കിൽ ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            തിരികെ data->controls[i];
        }
    }

    തിരികെ ശൂന്യ;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
സ്ഥിതം Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_ToolkitWindowX11 *data = (SDL_ToolkitWindowX11 *)arg;

    എങ്കിൽ (event->xany.display != data->display) {
        തിരികെ False;
    }

    എങ്കിൽ (event->xany.window == data->window) {
        തിരികെ True;
    }

    തിരികെ False;
}

ശൂന്യം X11Toolkit_ProcessWindowEvents(SDL_ToolkitWindowX11 *data, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    എങ്കിൽ ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        തിരികെ;
    }

    data->draw = false;
    data->e = e;

    തിരഞ്ഞെടുപ്പ് (e->type) {
        അവസ്ഥ Expose:
            data->draw = true;
            നിർത്തുക;
        അവസ്ഥ ClientMessage:
            എങ്കിൽ (e->xclient.message_type == data->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.data.l[0] == data->wm_delete_message) {
                data->close = true;
            }
            നിർത്തുക;
        അവസ്ഥ FocusIn:
            data->has_focus = true;
            നിർത്തുക;
        അവസ്ഥ FocusOut:
            data->has_focus = false;
            എങ്കിൽ (data->fiddled_control) {
                data->fiddled_control->selected = false;
            }
            data->fiddled_control = ശൂന്യ;
            വേണ്ടി (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
            }
            നിർത്തുക;
        അവസ്ഥ MotionNotify:
            എങ്കിൽ (data->has_focus) {
                data->previous_control = data->fiddled_control;
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                എങ്കിൽ (data->previous_control) {
                    data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    എങ്കിൽ (data->previous_control->func_on_state_change) {
                        data->previous_control->func_on_state_change(data->previous_control);
                    }
                    data->draw = true;
                }
                എങ്കിൽ (data->fiddled_control) {
                    എങ്കിൽ (data->fiddled_control->dynamic) {
                        data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        എങ്കിൽ (data->fiddled_control->func_on_state_change) {
                            data->fiddled_control->func_on_state_change(data->fiddled_control);
                        }
                        data->draw = true;
                    } അല്ലെങ്കിൽ {
                        data->fiddled_control = ശൂന്യ;
                    }
                }
            }
            നിർത്തുക;
        അവസ്ഥ ButtonPress:
            data->previous_control = data->fiddled_control;
            എങ്കിൽ (data->previous_control) {
                data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                എങ്കിൽ (data->previous_control->func_on_state_change) {
                    data->previous_control->func_on_state_change(data->previous_control);
                }
                data->draw = true;
            }
            എങ്കിൽ (e->xbutton.button == Button1) {
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                എങ്കിൽ (data->fiddled_control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    എങ്കിൽ (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->draw = true;
                }
            }
            നിർത്തുക;
        അവസ്ഥ ButtonRelease:
            എങ്കിൽ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
                പൂർണ്ണസംഖ്യ cx;
                പൂർണ്ണസംഖ്യ cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                എങ്കിൽ (cy < 0 || cx < 0) {
                    data->close = true;
                }

                എങ്കിൽ (cy > data->window_height || cx > data->window_width) {
                    data->close = true;
                }
            }

            എങ്കിൽ ((e->xbutton.button == Button1) && (data->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                എങ്കിൽ (data->fiddled_control == control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    എങ്കിൽ (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    data->draw = true;
                }
            }
            നിർത്തുക;
        അവസ്ഥ താക്കോൽ_Press:
            data->last_താക്കോൽ_pressed = X11_XLookupKeysym(&e->xkey, 0);

            എങ്കിൽ (data->last_താക്കോൽ_pressed == XK_Escape) {
                വേണ്ടി (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    എങ്കിൽ(data->controls[data->ev_i]->is_default_esc) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->താക്കോൽ_control_esc = data->controls[data->ev_i];
                    }
                }
            } അല്ലെങ്കിൽ എങ്കിൽ ((data->last_താക്കോൽ_pressed == XK_Return) || (data->last_താക്കോൽ_pressed == XK_KP_Enter)) {
                വേണ്ടി (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    എങ്കിൽ(data->controls[data->ev_i]->selected) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->താക്കോൽ_control_enter = data->controls[data->ev_i];
                    }
                }
            }
            നിർത്തുക;
        അവസ്ഥ താക്കോൽ_Release:
        {
            താക്കോൽ_Sym താക്കോൽ = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            എങ്കിൽ (താക്കോൽ != data->last_താക്കോൽ_pressed) {
                നിർത്തുക;
            }

            എങ്കിൽ (താക്കോൽ == XK_Escape) {
                എങ്കിൽ (data->താക്കോൽ_control_esc) {
                    എങ്കിൽ (data->താക്കോൽ_control_esc->func_on_state_change) {
                        data->താക്കോൽ_control_esc->func_on_state_change(data->താക്കോൽ_control_esc);
                    }
                }
            } അല്ലെങ്കിൽ എങ്കിൽ ((താക്കോൽ == XK_Return) || (താക്കോൽ == XK_KP_Enter)) {
                എങ്കിൽ (data->താക്കോൽ_control_enter) {
                    എങ്കിൽ (data->താക്കോൽ_control_enter->func_on_state_change) {
                        data->താക്കോൽ_control_enter->func_on_state_change(data->താക്കോൽ_control_enter);
                    }
                }
            } അല്ലെങ്കിൽ എങ്കിൽ (താക്കോൽ == XK_Tab || താക്കോൽ == XK_ഇടത് || താക്കോൽ == XK_വലത്) {
                എങ്കിൽ (data->focused_control) {
                    data->focused_control->selected = false;
                }
                data->draw = true;
                വേണ്ടി (data->ev_i = 0; data->ev_i < data->dyn_controls_sz; data->ev_i++) {
                    എങ്കിൽ (data->dyn_controls[data->ev_i] == data->focused_control) {
                        പൂർണ്ണസംഖ്യ next_index;

                        എങ്കിൽ (താക്കോൽ == XK_ഇടത്) {
                            next_index = data->ev_i - 1;
                        } അല്ലെങ്കിൽ {
                            next_index = data->ev_i + 1;
                        }
                        എങ്കിൽ ((next_index >= data->dyn_controls_sz) || (next_index < 0)) {
                            എങ്കിൽ (താക്കോൽ == XK_വലത് || താക്കോൽ == XK_ഇടത്) {
                                next_index = data->ev_i;
                            } അല്ലെങ്കിൽ {
                                next_index = 0;
                            }
                        }
                        data->focused_control = data->dyn_controls[next_index];
                        data->focused_control->selected = true;
                        നിർത്തുക;
                    }
                }
            }
            നിർത്തുക;
        }
    }

    എങ്കിൽ (data->draw) {
        X11Toolkit_DrawWindow(data);
    }
}

ശൂന്യം X11Toolkit_DoWindowEventLoop(SDL_ToolkitWindowX11 *data) {
   ആകുമ്പോൾ (!data->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(data->display, &e);
        എങ്കിൽ (data->xsettings) {
            xsettings_client_process_event(data->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(data->display, &e, X11Toolkit_EventTest, (XPointer)data);
        X11Toolkit_ProcessWindowEvents(data, &e);
    }
}


ശൂന്യം X11Toolkit_ResizeWindow(SDL_ToolkitWindowX11 *data, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h) {
    എങ്കിൽ (!data->pixmap) {
        data->window_width = w;
        data->window_height = h;
    } അല്ലെങ്കിൽ {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        X11_XFreePixmap(data->display, data->drawable);
        X11Toolkit_InitWindowPixmap(data);
    }

    X11_XResizeWindow(data->display, data->window, data->window_width, data->window_height);
}

സ്ഥിതം ശൂന്യം X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->window->display, icon_control->icon_char_font);
    SDL_free(control);
}

സ്ഥിതം ശൂന്യം X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->window->iscale;
    control->rect.h -= 2 * control->window->iscale;
    X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + (2 * control->window->iscale), control->rect.y + (2* control->window->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    തിരഞ്ഞെടുപ്പ് (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        അവസ്ഥ SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                നിർത്തുക;
        അവസ്ഥ SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                നിർത്തുക;
        അവസ്ഥ SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                നിർത്തുക;
    }
    X11_XSetFont(control->window->display, control->window->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    എങ്കിൽ (!control->window->utf8) {
        X11_XSetFont(control->window->display, control->window->ctx, control->window->font_struct->fid);
    }

    control->rect.w += 2 * control->window->iscale;
    control->rect.h += 2 * control->window->iscale;
}

സ്ഥിതം ശൂന്യം X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    പൂർണ്ണസംഖ്യ icon_char_w;
    പൂർണ്ണസംഖ്യ icon_wh;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11Toolkit_GetTextWidthHeightForFont(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, ശൂന്യ);
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

സ്ഥിതം ശൂന്യം X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    അക്ഷരം *font;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11_XFreeFont(base_control->window->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_SIZE * base_control->window->iscale);
    control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
    SDL_free(font);
    എങ്കിൽ (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * base_control->window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_ToolkitWindowX11 *window, SDL_MessageBoxFlags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    അക്ഷരം *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(വലുപ്പം(SDL_ToolkitIconControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    എങ്കിൽ (!control) {
        SDL_SetError("Unable to allocate icon control structure");
        തിരികെ ശൂന്യ;
    }

    /* Fill out struct */
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawIconControl;
    base_control->func_free = X11Toolkit_DestroyIconControl;
    base_control->func_on_state_change = ശൂന്യ;
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
    എങ്കിൽ (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        എങ്കിൽ (!control->icon_char_font) {
            SDL_free(control);
            തിരികെ ശൂന്യ;
        }
    }

    /* Set colors */
    തിരഞ്ഞെടുപ്പ് (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    അവസ്ഥ SDL_MESSAGEBOX_ERROR:
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
        നിർത്തുക;
    അവസ്ഥ SDL_MESSAGEBOX_WARNING:
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
        നിർത്തുക;
    അവസ്ഥ SDL_MESSAGEBOX_INFORMATION:
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
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        X11_XFreeFont(window->display, control->icon_char_font);
        SDL_free(control);
        തിരികെ ശൂന്യ;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    എങ്കിൽ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } അല്ലെങ്കിൽ എങ്കിൽ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } അല്ലെങ്കിൽ {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    എങ്കിൽ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } അല്ലെങ്കിൽ എങ്കിൽ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } അല്ലെങ്കിൽ {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    എങ്കിൽ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } അല്ലെങ്കിൽ എങ്കിൽ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } അല്ലെങ്കിൽ {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(window->display, window->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(base_control);

    X11Toolkit_AddControlToWindow(window, base_control);
    തിരികെ base_control;
}

bool X11Toolkit_NotifyControlOfSizeChange(SDL_ToolkitControlX11 *control) {
    എങ്കിൽ (control->func_calc_size) {
        control->func_calc_size(control);
        തിരികെ true;
    } അല്ലെങ്കിൽ {
        തിരികെ false;
    }
}

സ്ഥിതം ശൂന്യം X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11Toolkit_GetTextElementsRect(button_control->text, &button_control->text_rect);
    എങ്കിൽ (control->do_size) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.h;
    }
    button_control->text_rect.x = (control->rect.w - button_control->text_rect.w)/2;
    button_control->text_rect.y = (control->rect.h - button_control->text_rect.h)/2;
}


സ്ഥിതം ശൂന്യം X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    /* Draw bevel */
    എങ്കിൽ (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
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
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (control->selected) {
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
            } അല്ലെങ്കിൽ {
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

സ്ഥിതം ശൂന്യം X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    എങ്കിൽ (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_data);
    }
}

സ്ഥിതം ശൂന്യം X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11Toolkit_FreeTextElements(button_control->text);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_ToolkitWindowX11 *window, സ്ഥിരം SDL_MessageBoxButtonData *data) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *base_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(വലുപ്പം(SDL_ToolkitButtonControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    എങ്കിൽ (!control) {
        SDL_SetError("Unable to allocate button control structure");
        തിരികെ ശൂന്യ;
    }
    base_control->window = window;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->func_calc_size = X11Toolkit_CalculateButtonControl;
    base_control->func_draw = X11Toolkit_DrawButtonControl;
    base_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    base_control->func_free = X11Toolkit_DestroyButtonControl;
    base_control->func_on_scale_change = ശൂന്യ;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = true;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    എങ്കിൽ (data->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        base_control->is_default_esc = true;
    }
    എങ്കിൽ (data->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        base_control->is_default_enter = true;
        base_control->selected = true;
    }
    control->cb = ശൂന്യ;
    control->data = data;
#ifdef HAVE_FRIBIDI_H
    control->text = X11Toolkit_MakeTextElements(base_control->window, (അക്ഷരം *)control->data->text, SDL_strlen(control->data->text), ശൂന്യ);
#അല്ലെങ്കിൽ 
    control->text = X11Toolkit_MakeTextElements(base_control->window, (അക്ഷരം *)control->data->text, SDL_strlen(control->data->text));
#endif
    X11Toolkit_ShapeTextElements(base_control->window, control->text);
    
    base_control->do_size = true;
    X11Toolkit_CalculateButtonControl(base_control);
    base_control->do_size = false;

    X11Toolkit_AddControlToWindow(window, base_control);
    തിരികെ base_control;
}

ശൂന്യം X11Toolkit_RegisterCallbackForButtonControl(SDL_ToolkitControlX11 *control, ശൂന്യം *data, ശൂന്യം (*cb)(ഘടന SDL_ToolkitControlX11 *, ശൂന്യം *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_data = data;
    button_control->cb = cb;
}

സ്ഥിരം SDL_MessageBoxButtonData *X11Toolkit_GetButtonControlData(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    തിരികെ button_control->data;
}

ശൂന്യം X11Toolkit_DestroyWindow(SDL_ToolkitWindowX11 *data) {
    പൂർണ്ണസംഖ്യ i;

    എങ്കിൽ (!data) {
        തിരികെ;
    }

#എങ്കിൽ SDL_GRAB
    എങ്കിൽ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XUngrabPointer(data->display, CurrentTime);
        X11_XUngrabKeyboard(data->display, CurrentTime);
    }
#endif

    വേണ്ടി (i = 0; i < data->controls_sz; i++) {
        എങ്കിൽ (data->controls[i]->func_free) {
            data->controls[i]->func_free(data->controls[i]);
        }
    }
    SDL_free(data->controls);
    SDL_free(data->dyn_controls);

    എങ്കിൽ (data->popup_windows) {
        SDL_ListClear(&data->popup_windows);
    }

    എങ്കിൽ (data->pixmap) {
        X11_XFreePixmap(data->display, data->drawable);
    }

#ifndef NO_SHARED_MEMORY
    എങ്കിൽ (data->pixmap && data->shm) {
        X11_XShmDetach(data->display, &data->shm_info);
        എങ്കിൽ (!data->shm_pixmap) {
            XDestroyImage(data->image);
        }
        shmdt(data->shm_info.shmaddr);
    }
#endif

#ifdef X_HAVE_UTF8_STRING
    എങ്കിൽ (data->font_set) {
        X11_XFreeFontSet(data->display, data->font_set);
        data->font_set = ശൂന്യ;
    }
#endif

    എങ്കിൽ (data->font_struct) {
        X11_XFreeFont(data->display, data->font_struct);
        data->font_struct = ശൂന്യ;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    എങ്കിൽ (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeDeallocateBackBufferName(data->display, data->buf);
    }
#endif

    എങ്കിൽ (data->xsettings) {
        xsettings_client_destroy(data->xsettings);
    }

    X11_XFreeGC(data->display, data->ctx);

    എങ്കിൽ (data->display) {
        എങ്കിൽ (data->window != None) {
            X11_XWithdrawWindow(data->display, data->window, data->screen);
            X11_XDestroyWindow(data->display, data->window);
            data->window = None;
        }

        എങ്കിൽ (data->display_close) {
            X11_XCloseDisplay(data->display);
        }
        data->display = ശൂന്യ;
    }

#എങ്കിൽ SDL_SET_LOCALE
    എങ്കിൽ (data->origlocale && (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG)) {
        (ശൂന്യം)setlocale(LC_ALL, data->origlocale);
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

സ്ഥിതം പൂർണ്ണസംഖ്യ X11_Toolkit_എണ്ണം_വരികൾ_Of_Text(സ്ഥിരം അക്ഷരം *text)
{
    പൂർണ്ണസംഖ്യ result = 0;
    ആകുമ്പോൾ (text && *text) {
        സ്ഥിരം അക്ഷരം *lf = SDL_strchr(text, '\n');
        result++; // even without an endline, this counts as a line.
        text = lf ? lf + 1 : ശൂന്യ;
    }
    തിരികെ result;
}

സ്ഥിതം ശൂന്യം X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    പൂർണ്ണസംഖ്യ i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    വേണ്ടി (i = 0; i < label_control->sz; i++) {
        X11Toolkit_DrawTextElements(control->window, label_control->വരികൾ[i].text, control->rect.x + label_control->വരികൾ[i].rect.x, control->rect.y + label_control->വരികൾ[i].rect.y);
    }
}

സ്ഥിതം ശൂന്യം X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    പൂർണ്ണസംഖ്യ i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    വേണ്ടി (i = 0; i < label_control->sz; i++) {
        X11Toolkit_FreeTextElements(label_control->വരികൾ[i].text);
    }
    SDL_free(label_control->വരികൾ);
    SDL_free(label_control);
}

സ്ഥിതം ശൂന്യം X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitLabelControlX11 *control;
    പൂർണ്ണസംഖ്യ i;

    control = (SDL_ToolkitLabelControlX11 *)base_control;
    
    എങ്കിൽ (base_control->do_size) {
        base_control->rect.w = 0;
        base_control->rect.h = 0;
    }
    
    വേണ്ടി (i = 0; i < control->sz; i++) {
        പൂർണ്ണസംഖ്യ font_h;
        
        font_h = X11Toolkit_GetTextElementsRect(control->വരികൾ[i].text, &control->വരികൾ[i].rect);
        
        എങ്കിൽ (base_control->do_size) {
            base_control->rect.w = SDL_max(base_control->rect.w, control->വരികൾ[i].rect.w);
        }
        
        എങ്കിൽ (i > 0) {
            control->വരികൾ[i].rect.y = font_h + control->വരികൾ[i - 1].rect.y;
        } അല്ലെങ്കിൽ {
            control->വരികൾ[i].rect.y = 0;
        }
    }

#ifdef HAVE_FRIBIDI_H
    എങ്കിൽ (base_control->window->fribidi) {
        FriBidiParType first_ndn_dir;
        പൂർണ്ണസംഖ്യ last_ndn;
    
        first_ndn_dir = FRIBIDI_PAR_LTR;
        വേണ്ടി (i = 0; i < control->sz; i++) {
            എങ്കിൽ (control->വരികൾ[i].par != FRIBIDI_PAR_ON) {
                first_ndn_dir = control->വരികൾ[i].par;
            }
        }

        last_ndn = -1;
        വേണ്ടി (i = 0; i < control->sz; i++) {
            തിരഞ്ഞെടുപ്പ് (control->വരികൾ[i].par) {
                അവസ്ഥ FRIBIDI_PAR_LTR:
                    control->വരികൾ[i].rect.x = 0;
                    last_ndn = i;
                    നിർത്തുക;
                അവസ്ഥ FRIBIDI_PAR_RTL:
                    control->വരികൾ[i].rect.x = base_control->rect.w - control->വരികൾ[i].rect.w;
                    last_ndn = i;
                    നിർത്തുക;
                സ്ഥിരസ്ഥിതി:
                    എങ്കിൽ (last_ndn != -1) {
                        എങ്കിൽ (control->വരികൾ[last_ndn].par == FRIBIDI_PAR_RTL) {
                            control->വരികൾ[i].rect.x = base_control->rect.w - control->വരികൾ[i].rect.w;
                        } അല്ലെങ്കിൽ {
                            control->വരികൾ[i].rect.x = 0;
                        }
                    } അല്ലെങ്കിൽ {
                        എങ്കിൽ (first_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->വരികൾ[i].rect.x = base_control->rect.w - control->വരികൾ[i].rect.w;
                        } അല്ലെങ്കിൽ {
                            control->വരികൾ[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#endif
    
    എങ്കിൽ (base_control->do_size && control->sz) {
        base_control->rect.h = control->വരികൾ[control->sz - 1].rect.y + control->വരികൾ[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_ToolkitWindowX11 *window, അക്ഷരം *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    പൂർണ്ണസംഖ്യ i;
    
    എങ്കിൽ (!utf8) {
        തിരികെ ശൂന്യ;
    }
 
    എങ്കിൽ (!SDL_strcmp(utf8, "")) {
        തിരികെ ശൂന്യ;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(വലുപ്പം(SDL_ToolkitLabelControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    എങ്കിൽ (!control) {
        SDL_SetError("Unable to allocate label control structure");
        തിരികെ ശൂന്യ;
    }
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawLabelControl;
    base_control->func_on_state_change = ശൂന്യ;
    base_control->func_calc_size = X11Toolkit_CalculateLabelControl;
    base_control->func_free  = X11Toolkit_DestroyLabelControl;
    base_control->func_on_scale_change = ശൂന്യ;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = false;
    base_control->rect.w = 0;
    base_control->rect.h = 0;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_എണ്ണം_വരികൾ_Of_Text(utf8);
    control->വരികൾ = SDL_calloc(control->sz, വലുപ്പം(SDL_Toolkit_Label_Control_വരി_X11));
    വേണ്ടി (i = 0; i < control->sz; i++) {
        സ്ഥിരം അക്ഷരം *lf = SDL_strchr(utf8, '\n');
        സ്ഥിരം പൂർണ്ണസംഖ്യ length = lf ? (lf - utf8) : SDL_strlen(utf8);
        പൂർണ്ണസംഖ്യ sz;
        
        sz = length;
        എങ്കിൽ (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#ifdef HAVE_FRIBIDI_H
        control->വരികൾ[i].text = X11Toolkit_MakeTextElements(base_control->window, (അക്ഷരം *)utf8, sz, &control->വരികൾ[i].par);
#അല്ലെങ്കിൽ 
        control->വരികൾ[i].text = X11Toolkit_MakeTextElements(base_control->window, (അക്ഷരം *)utf8, sz);
#endif
        X11Toolkit_ShapeTextElements(base_control->window, control->വരികൾ[i].text);

        utf8 += length + 1;
        എങ്കിൽ (!lf) {
            നിർത്തുക;
        }
    }

    base_control->do_size = true;
    X11Toolkit_CalculateLabelControl(base_control);
    base_control->do_size = false;
    X11Toolkit_AddControlToWindow(window, base_control);

    തിരികെ base_control;
}

പൂർണ്ണസംഖ്യ X11_Toolkit_Get_Label_Control_First_വരി_Height(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    തിരികെ label_control->വരികൾ[0].rect.h;
}

ശൂന്യം X11Toolkit_SignalWindowClose(SDL_ToolkitWindowX11 *data) {
    data->close = true;
}

#endif // SDL_VIDEO_DRIVER_X11
