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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "../../SDL_list.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ifdef SDL_USE_LIBDBUS
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_system_theme.h"
#endif
#ifdef HAVE_FRIBIDI_H
#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_fribidi.h"
#endif
#ಅನ್ತರ್ಭಾವ "SDL_x11dyn.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11toolkit.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11settings.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11modes.h"
#ಅನ್ತರ್ಭಾವ "xsettings-client.h"
#ಅನ್ತರ್ಭಾವ <X11/keysym.h>
#ಅನ್ತರ್ಭಾವ <locale.h>

#define SDL_SET_LOCALE 1
#define SDL_GRAB 1

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ SDL_ToolkitTextTypeX11
{
    SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC,
    SDL_TOOLKIT_TEXT_TYPE_X11_THAI
} SDL_ToolkitTextTypeX11;

#ifdef HAVE_LIBTHAI_H
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_ToolkitThaiOverlayX11
{
    bool ತುದಿ;
    ವರ್ಣ *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#endif

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_ToolkitTextElementX11
{
    SDL_ToolkitTextTypeX11 type;
    ವರ್ಣ *str;
    size_t sz;
    SDL_Rect rect;
    ಪೂರ್ಣಾಙ್ಕ font_h;
    ಶೂನ್ಯ (*str_free)(ಶೂನ್ಯ *);
#ifdef HAVE_LIBTHAI_H
    SDL_List_ಗಂಟು *thai_overlays;
#endif
} SDL_ToolkitTextElementX11;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Icon type */
    SDL_MessageBoxFlags flags;
    ವರ್ಣ icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    ಪೂರ್ಣಾಙ್ಕ icon_char_x;
    ಪೂರ್ಣಾಙ್ಕ icon_char_y;
    ಪೂರ್ಣಾಙ್ಕ icon_char_a;
    ಪೂರ್ಣಾಙ್ಕ icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Data */
    ಧ್ರುವ SDL_MessageBoxButtonData *data;

    /* Text */
    SDL_List_ಗಂಟು *text;
    SDL_Rect text_rect;
    
    /* Callback */
    ಶೂನ್ಯ *cb_data;
    ಶೂನ್ಯ (*cb)(ಸಂರಚನಾ SDL_ToolkitControlX11 *, ಶೂನ್ಯ *);
} SDL_ToolkitButtonControlX11;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_Toolkit_Label_Control_ಸಾಲು_X11
{
    SDL_List_ಗಂಟು *text;
    SDL_Rect rect;
#ifdef HAVE_FRIBIDI_H
    FriBidiParType par;
#endif
} SDL_Toolkit_Label_Control_ಸಾಲು_X11;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_ToolkitLabelControlX11
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
    SDL_Toolkit_Label_Control_ಸಾಲು_X11 *ಸಾಲುಗಳು;
    size_t sz;
} SDL_ToolkitLabelControlX11;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_ಗಂಟು *menu_ವಸ್ತುಗಳು;
} SDL_ToolkitMenuBarControlX11;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_ಗಂಟು *menu_ವಸ್ತುಗಳು;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#define G_ICONFONT_SIZE 22

/* General UI font */
ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    ರಿಕ್ತ
};
#define G_TOOLKITFONT_SIZE 140

ಸ್ಥಿರ ಧ್ರುವ SDL_MessageBoxColor g_default_colors[SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ifdef SDL_USE_LIBDBUS
ಸ್ಥಿರ ಧ್ರುವ SDL_MessageBoxColor g_default_colors_dark[SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ಯದಿ 0
ಸ್ಥಿರ ಧ್ರುವ SDL_MessageBoxColor g_default_colors_dark_ಮೇಲಿನ_contrast[SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

ಸ್ಥಿರ ಧ್ರುವ SDL_MessageBoxColor g_default_colors_light_ಮೇಲಿನ_contrast[SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#endif

#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ g_shm_error;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ (*g_old_error_handler)(Display *, XErrorEvent *) = ರಿಕ್ತ;

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ X11Toolkit_SharedMemoryErrorHandler(Display *d, XErrorEvent *e)
{
    ಯದಿ (e->error_code == BadAccess || e->error_code == BadRequest) {
        g_shm_error = True;
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    ಪ್ರತ್ಯಾಗಮ g_old_error_handler(d, e);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_InitWindowPixmap(SDL_ToolkitWindowX11 *data) {
    ಯದಿ (data->pixmap) {
#ifndef NO_SHARED_MEMORY
        ಯದಿ (!data->shm_pixmap) {
            data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
        }
#ಅನ್ಯಥಾ
        data->drawable = X11_XCreatePixmap(data->display, data->window, data->pixmap_width, data->pixmap_height, data->depth);
#endif
#ifndef NO_SHARED_MEMORY
        ಯದಿ (data->shm) {
            data->image = X11_XShmCreateImage(data->display, data->visual, data->depth, ZPixmap, ರಿಕ್ತ, &data->shm_info, data->pixmap_width, data->pixmap_height);
            ಯದಿ (data->image) {
                data->shm_bytes_per_ಸಾಲು = data->image->bytes_per_ಸಾಲು;

                data->shm_info.shmid = shmget(IPC_PRIVATE, data->image->bytes_per_ಸಾಲು * data->image->height, IPC_CREAT | 0777);
                ಯದಿ (data->shm_info.shmid < 0) {
                    XDestroyImage(data->image);
                    data->image = ರಿಕ್ತ;
                    data->shm = false;
                    ಪ್ರತ್ಯಾಗಮ;
                }

                data->shm_info.readOnly = False;
                data->shm_info.shmaddr = data->image->data = (ವರ್ಣ *)shmat(data->shm_info.shmid, ರಿಕ್ತ, 0);
                ಯದಿ (((signed ವರ್ಣ *)data->shm_info.shmaddr) == (signed ವರ್ಣ *)-1) {
                    XDestroyImage(data->image);
                    data->shm = false;
                    data->image = ರಿಕ್ತ;
                    ಪ್ರತ್ಯಾಗಮ;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11Toolkit_SharedMemoryErrorHandler);
                X11_XShmAttach(data->display, &data->shm_info);
                X11_XSync(data->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                ಯದಿ (g_shm_error) {
                    XDestroyImage(data->image);
                    shmdt(data->shm_info.shmaddr);
                    shmctl(data->shm_info.shmid, IPC_RMID, ರಿಕ್ತ);
                    data->image = ರಿಕ್ತ;
                    data->shm = false;
                    ಪ್ರತ್ಯಾಗಮ;
                }

                ಯದಿ (data->shm_pixmap) {
                    data->drawable = X11_XShmCreatePixmap(data->display, data->window, data->shm_info.shmaddr, &data->shm_info, data->pixmap_width, data->pixmap_height, data->depth);
                    ಯದಿ (data->drawable == None) {
                        data->shm_pixmap = False;
                    } ಅನ್ಯಥಾ {
                        XDestroyImage(data->image);
                        data->image = ರಿಕ್ತ;
                    }
                }

                shmctl(data->shm_info.shmid, IPC_RMID, ರಿಕ್ತ);
            } ಅನ್ಯಥಾ {
                data->shm = false;
            }
        }
#endif
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_InitWindowFonts(SDL_ToolkitWindowX11 *window)
{    
    window->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    window->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#ifdef X_HAVE_UTF8_STRING
    window->utf8 = true;
    window->font_set = ರಿಕ್ತ;
    ಯದಿ (SDL_X11_HAVE_UTF8) {
        ವರ್ಣ **missing = ರಿಕ್ತ;
        ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_missing = 0;
        ಪೂರ್ಣಾಙ್ಕ i_font;
        window->font_struct = ರಿಕ್ತ;
        ಪ್ರತಿ (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            ವರ್ಣ *font;

            ಯದಿ (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_load_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_SIZE * window->iscale);
                window->font_set = X11_XCreateFontSet(window->display, font, &missing, &ಅಂಕೆ_missing, ರಿಕ್ತ);
                SDL_free(font);

                ಯದಿ (!window->font_set) {
                    ಯದಿ (window->scale != 0 && window->iscale > 0) {
                        window->iscale = (ಪೂರ್ಣಾಙ್ಕ)SDL_ceilf(window->scale);
                        window->scale = 0;
                    } ಅನ್ಯಥಾ {
                        window->iscale--;
                    }
                    ಗಚ್ಛ try_load_font;
                }
            } ಅನ್ಯಥಾ {
                window->font_set = X11_XCreateFontSet(window->display, g_ToolkitFont[i_font], &missing, &ಅಂಕೆ_missing, ರಿಕ್ತ);
            }

            ಯದಿ (missing) {
                X11_XFreeStringList(missing);
            }

            ಯದಿ (window->font_set) {
                ಭಙ್ಗ;
            }
        }

        ಯದಿ (!window->font_set) {
            ಗಚ್ಛ load_font_traditional;
        } ಅನ್ಯಥಾ {
            XFontStruct **font_structs;
            ವರ್ಣ **font_names;
            ಪೂರ್ಣಾಙ್ಕ font_sz;
            ಪೂರ್ಣಾಙ್ಕ i;
            
#ifdef HAVE_FRIBIDI_H
            window->do_shaping = !X11_XContextDependentDrawing(window->font_set);
#endif
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFontsOfFontSet(window->font_set, &font_structs, &font_names);
            ಪ್ರತಿ (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                ಯದಿ (SDL_strstr(font_names[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } ಅನ್ಯಥಾ ಯದಿ (SDL_strstr(font_names[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } ಅನ್ಯಥಾ ಯದಿ (SDL_strstr(font_names[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } ಅನ್ಯಥಾ ಯದಿ (SDL_strstr(font_names[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } ಅನ್ಯಥಾ ಯದಿ (SDL_strstr(font_names[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                ಯದಿ (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(window->display, font_names[i]);
                    ಯದಿ (font_struct) {
                        ಯದಿ (font_struct->per_char) {
                            ಪೂರ್ಣಾಙ್ಕ glyphs_sz;
                            ಪೂರ್ಣಾಙ್ಕ j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            ಪ್ರತಿ (j = 0; j < glyphs_sz; j++) {
                                ಯದಿ (font_struct->per_char[j].lbearing < 0) {
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
    } ಅನ್ಯಥಾ
#endif
    {
        ವರ್ಣ *font;

        load_font_traditional:
        window->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        window->font_struct = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        ಯದಿ (!window->font_struct) {
            ಯದಿ (window->iscale > 0) {
                ಯದಿ (window->scale != 0) {
                    window->iscale = (ಪೂರ್ಣಾಙ್ಕ)SDL_ceilf(window->scale);
                    window->scale = 0;
                } ಅನ್ಯಥಾ {
                    window->iscale--;
                }
                ಗಚ್ಛ load_font_traditional;
            } ಅನ್ಯಥಾ {
                window->font_struct = X11_XLoadQueryFont(window->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_SettingsNotify(ಧ್ರುವ ವರ್ಣ *name, XSettingsAction action, XSettingsSetting *setting, ಶೂನ್ಯ *data)
{
    SDL_ToolkitWindowX11 *window;
    ಪೂರ್ಣಾಙ್ಕ i;

    window = data;

    ಯದಿ (window->xsettings_first_time) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_setup = false;
        bool pixmap_already_setup = false;

        ಯದಿ (window->pixmap) {
            pixmap_already_setup = true;
        } ಅನ್ಯಥಾ {
            dbe_already_setup = true;
        }

        /* set scale vars */
        window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
        window->iscale = (ಪೂರ್ಣಾಙ್ಕ)SDL_ceilf(window->scale);
        ಯದಿ (window->scale < 1) {
            window->scale = 1;
        }
        ಯದಿ (SDL_roundf(window->scale) == window->scale) {
            window->scale = 0;
        }

        /* setup fonts */
#ifdef X_HAVE_UTF8_STRING
        ಯದಿ (window->font_set) {
            X11_XFreeFontSet(window->display, window->font_set);
        }
#endif
        ಯದಿ (window->font_struct) {
            X11_XFreeFont(window->display, window->font_struct);
        }

        X11Toolkit_InitWindowFonts(window);

        /* set up window */
        ಯದಿ (window->scale != 0) {
            window->window_width = SDL_lroundf((window->window_width/window->iscale) * window->scale);
            window->window_height = SDL_lroundf((window->window_height/window->iscale) * window->scale);
            window->pixmap_width = window->window_width;
            window->pixmap_height = window->window_height;
            window->pixmap = true;
        } ಅನ್ಯಥಾ {
            window->pixmap = false;
        }

        ಯದಿ (window->pixmap) {
            ಯದಿ (!pixmap_already_setup) {
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                ಯದಿ (SDL_X11_HAVE_XDBE && window->xdbe) {
                    X11_XdbeDeallocateBackBufferName(window->display, window->buf);
                }
#endif
            }
            X11_XFreePixmap(window->display, window->drawable);
            X11Toolkit_InitWindowPixmap(window);
        } ಅನ್ಯಥಾ {
            ಯದಿ (!dbe_already_setup) {
                X11_XFreePixmap(window->display, window->drawable);
#ifndef NO_SHARED_MEMORY
                ಯದಿ (window->image) {
                    XDestroyImage(window->image);
                    window->image = ರಿಕ್ತ;
                }
#endif
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
                ಯದಿ (SDL_X11_HAVE_XDBE && window->xdbe) {
                    window->buf = X11_XdbeAllocateBackBufferName(window->display, window->window, XdbeUndefined);
                    window->drawable = window->buf;
                }
#endif
            }
        }

        /* notify controls */
        ಪ್ರತಿ (i = 0; i < window->controls_sz; i++) {
            window->controls[i]->do_size = true;

            ಯದಿ (window->controls[i]->func_on_scale_change) {
                window->controls[i]->func_on_scale_change(window->controls[i]);
            }

            ಯದಿ (window->controls[i]->func_calc_size) {
                window->controls[i]->func_calc_size(window->controls[i]);
            }

            window->controls[i]->do_size = false;
        }

        /* notify cb */
        ಯದಿ (window->cb_on_scale_change) {
            window->cb_on_scale_change(window, window->cb_data);
        }

        /* update ev scales */
        ಯದಿ (!window->pixmap) {
            window->ev_scale = window->ev_iscale = 1;
        } ಅನ್ಯಥಾ {
            window->ev_scale = window->scale;
            window->ev_iscale = window->iscale;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_GetTextWidthHeightForFont(XFontStruct *font, ಧ್ರುವ ವರ್ಣ *str, ಪೂರ್ಣಾಙ್ಕ nbytes, ಪೂರ್ಣಾಙ್ಕ *pwidth, ಪೂರ್ಣಾಙ್ಕ *pheight, ಪೂರ್ಣಾಙ್ಕ *ascent, ಪೂರ್ಣಾಙ್ಕ *font_height)
{
    XCharStruct text_structure;
    ಪೂರ್ಣಾಙ್ಕ font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &text_structure);
    *pwidth = text_structure.width;
    *pheight = text_structure.ascent + text_structure.descent;
    *ascent = text_structure.ascent;
    ಯದಿ (font_height) {
       *font_height = font_ascent + font_descent;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_GetTextWidthHeight(SDL_ToolkitWindowX11 *data, ಧ್ರುವ ವರ್ಣ *str, ಪೂರ್ಣಾಙ್ಕ nbytes, ಪೂರ್ಣಾಙ್ಕ *pwidth, ಪೂರ್ಣಾಙ್ಕ *pheight, ಪೂರ್ಣಾಙ್ಕ *ascent, ಪೂರ್ಣಾಙ್ಕ *descent, ಪೂರ್ಣಾಙ್ಕ *font_height)
{
#ifdef X_HAVE_UTF8_STRING
    ಯದಿ (data->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8TextExtents(data->font_set, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.width;
        *pheight = overall_logical.height;
        *ascent = -overall_logical.y;
        *descent = overall_logical.height - *ascent;

        ಯದಿ (font_height) {
            XFontSetExtents *extents;

            extents = X11_XExtentsOfFontSet(data->font_set);
            *font_height = extents->max_logical_extent.height;
        }
    } ಅನ್ಯಥಾ
#endif
    {
        XCharStruct text_structure;
        ಪೂರ್ಣಾಙ್ಕ font_direction, font_ascent, font_descent;
        X11_XTextExtents(data->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &text_structure);
        *pwidth = text_structure.width;
        *pheight = text_structure.ascent + text_structure.descent;
        *ascent = text_structure.ascent;
        *descent = text_structure.descent;

        ಯದಿ (font_height) {
            *font_height = font_ascent + font_descent;
        }
    }
}

#ifdef HAVE_FRIBIDI_H
SDL_List_ಗಂಟು *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, ವರ್ಣ *txt, size_t sz, FriBidiParType *par)
#ಅನ್ಯಥಾ
SDL_List_ಗಂಟು *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *data, ವರ್ಣ *txt, size_t sz)
#endif
{
    SDL_List_ಗಂಟು *list;
    ವರ್ಣ *str;
    ವರ್ಣ *buffer;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = ರಿಕ್ತ;
    thai = 0;
    str = txt;
    buffer = SDL_malloc(1);
    buffer[0] = 0;
    
#ifdef HAVE_FRIBIDI_H
    ಯದಿ (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    ಯದಿ (data->fribidi) {
        ವರ್ಣ *fstr;
                
        fstr = SDL_FriBidi_Process(data->fribidi, str, sz, data->do_shaping, par);
        ಯದಿ (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#endif        

    ಯಾವತ್ (1) {
        ವರ್ಣ *new;
        ವರ್ಣ utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_StepUTF8((ಧ್ರುವ ವರ್ಣ **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        ಯದಿ (cp == 0 || cond == (thai ? false : true)) {
            SDL_ToolkitTextElementX11 *element;
            
            element = SDL_malloc(ಪರಿಮಾಣ(SDL_ToolkitTextElementX11));
            ಯದಿ (thai) {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_THAI;
            } ಅನ್ಯಥಾ {
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

        ಯದಿ (!cp) {
            ಭಙ್ಗ;
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
    ಯದಿ (free_txt) {
        SDL_free(txt);
    }
    ಪ್ರತ್ಯಾಗಮ list;
}

ಶೂನ್ಯ X11Toolkit_ShapeTextElements(SDL_ToolkitWindowX11 *data, SDL_List_ಗಂಟು *list)
{
    SDL_List_ಗಂಟು *cursor;
    SDL_ToolkitTextElementX11 *prev;
    ಪೂರ್ಣಾಙ್ಕ temp;
    
    /* Shape and calculate bounding box */
    cursor = list;
    ಯಾವತ್ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
#ifdef HAVE_LIBTHAI_H
        element->thai_overlays = ರಿಕ್ತ;
#endif
        ಯದಿ (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            ಯದಿ (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, ರಿಕ್ತ);
            } ಅನ್ಯಥಾ {
#ifdef HAVE_LIBTHAI_H
                ಯದಿ (data->th) {
                    ಸಂರಚನಾ thcell_t *cells;
                    ವರ್ಣ *tis_str;
                    ವರ್ಣ *base_tis_str;
                    size_t cells_sz;
                    size_t base_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, ಪರಿಮಾಣ(ಸಂರಚನಾ thcell_t));
                    data->th->make_cells((ಧ್ರುವ thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    base_tis_str_sz = cells_sz;
                    base_tis_str = SDL_malloc(base_tis_str_sz + 1);
                    ಪ್ರತಿ (temp = 0; temp < cells_sz; temp++) {
                        base_tis_str[temp] = cells[temp].base;
                        
                        ಯದಿ (cells[temp].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            ವರ್ಣ *pre;
                            ಪೂರ್ಣಾಙ್ಕ temp2;
                            
                            overlay = SDL_malloc(ಪರಿಮಾಣ(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ಧ್ರುವ ವರ್ಣ *)&cells[temp].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->ತುದಿ = false;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ರಿಕ್ತ);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ರಿಕ್ತ);
                            SDL_ListAdd(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        ಯದಿ (cells[temp].ತುದಿ) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            ವರ್ಣ *pre;
                            ಪೂರ್ಣಾಙ್ಕ temp2;
                            
                            overlay = SDL_malloc(ಪರಿಮಾಣ(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, temp);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ಧ್ರುವ ವರ್ಣ *)&cells[temp].ತುದಿ, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->ತುದಿ = true;
                            X11Toolkit_GetTextWidthHeight(data, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ರಿಕ್ತ);
                            X11Toolkit_GetTextWidthHeight(data, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ರಿಕ್ತ);
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
#ಅನ್ಯಥಾ
                X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
#endif            
            }
        } ಅನ್ಯಥಾ {
            X11Toolkit_GetTextWidthHeight(data, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &temp, &element->font_h);
        }
        
        cursor = cursor->next;
    }
    
    /* Add offsets */
    prev = ರಿಕ್ತ;
    cursor = list;
    ಯಾವತ್ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;        
        ಯದಿ (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } ಅನ್ಯಥಾ {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->next;
    }
}


ಶೂನ್ಯ X11Toolkit_DrawTextElements(SDL_ToolkitWindowX11 *data, SDL_List_ಗಂಟು *list, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y)
{
    SDL_List_ಗಂಟು *cursor;
    
    cursor = list;
    
    ಯಾವತ್ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        ಯದಿ (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            ಯದಿ (data->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
#ifdef X_HAVE_UTF8_STRING
                ಯದಿ (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } ಅನ್ಯಥಾ
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } ಅನ್ಯಥಾ {    
#ifdef HAVE_LIBTHAI_H
                SDL_List_ಗಂಟು *overlay_cursor;
                    
                /* Draw the base string */
#ifdef X_HAVE_UTF8_STRING
                ಯದಿ (data->utf8) {
                    X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } ಅನ್ಯಥಾ
#endif
                {
                    X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                ಯಾವತ್ (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->entry;
#ifdef X_HAVE_UTF8_STRING
                    ಯದಿ (data->utf8) {
                        X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } ಅನ್ಯಥಾ
#endif
                    {
                        X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->next;
                }
#endif                
            }
        } ಅನ್ಯಥಾ {
#ifdef X_HAVE_UTF8_STRING
            ಯದಿ (data->utf8) {
                X11_Xutf8DrawString(data->display, data->drawable, data->font_set, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } ಅನ್ಯಥಾ
#endif
            {
                X11_XDrawString(data->display, data->drawable, data->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->next;
    }
}

ಪೂರ್ಣಾಙ್ಕ X11Toolkit_GetTextElementsRect(SDL_List_ಗಂಟು *list, SDL_Rect *out)
{
    SDL_List_ಗಂಟು *cursor;
    ಪೂರ್ಣಾಙ್ಕ ret;
    
    ret = 0;
    out->x = out->y = 0;
    out->w = out->h = 0;
    cursor = list;
    ಯಾವತ್ (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        
        out->w += element->rect.w;
        out->h = SDL_max(out->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->next;
    }
    
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಶೂನ್ಯ X11Toolkit_FreeTextElementsListContents(SDL_List_ಗಂಟು *list)
{
    SDL_List_ಗಂಟು *cursor;
    
    cursor = list;
    ಯಾವತ್ (cursor) {
        SDL_ToolkitTextElementX11 *element;
#ifdef HAVE_LIBTHAI_H
        SDL_List_ಗಂಟು *overlay_cursor;
#endif

        element = cursor->entry;
        
        ಯದಿ (element->str_free) {
            element->str_free(element->str);
        }
        
#ifdef HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        ಯಾವತ್ (overlay_cursor) {
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
 
ಸ್ಥಿರ bool X11Toolkit_ShouldFlipUI(ಶೂನ್ಯ) 
{
    SDL_Locale **current_locales;
    ಸ್ಥಿರ ಧ್ರುವ SDL_Locale rtl_locales[] = {
        { "ar", ರಿಕ್ತ, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", ರಿಕ್ತ, },
        { "iw", ರಿಕ್ತ, },
        { "yi", ರಿಕ್ತ, },
        { "ur", ರಿಕ್ತ, },
        { "ug", ರಿಕ್ತ, },
        { "kd", ರಿಕ್ತ, },
        { "pk", "PK", },
        { "ps", ರಿಕ್ತ, }
    }; 
    ಪೂರ್ಣಾಙ್ಕ current_locales_sz;
    ಪೂರ್ಣಾಙ್ಕ i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    ಯದಿ (current_locales_sz <= 0) {
        ಪ್ರತ್ಯಾಗಮ false;        
    }
    ಪ್ರತಿ (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        ಯದಿ (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            ಯದಿ (!rtl_locales[i].country) {
                ಪ್ರತ್ಯಾಗಮ true;
            } ಅನ್ಯಥಾ {
                ಪ್ರತ್ಯಾಗಮ SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    ಪ್ರತ್ಯಾಗಮ false;
}

SDL_ToolkitWindowX11 *X11Toolkit_CreateWindowStruct(SDL_Window *parent, SDL_ToolkitWindowX11 *tkparent, SDL_ToolkitWindowModeX11 mode, ಧ್ರುವ SDL_MessageBoxColor *colorhints, bool create_new_display)
{
    SDL_ToolkitWindowX11 *window;
    ಪೂರ್ಣಾಙ್ಕ i;
#ifdef SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#endif
    #define ErrorFreeRetNull(x, y) SDL_SetError(x); SDL_free(y); ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ
    #define ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_SetError(x, y); SDL_free(z); ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ

    ಯದಿ (!SDL_X11_LoadSymbols()) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    // This code could get called from multiple threads maybe?
    X11_XInitThreads();

    window = (SDL_ToolkitWindowX11 *)SDL_malloc(ಪರಿಮಾಣ(SDL_ToolkitWindowX11));
    ಯದಿ (!window) {
        SDL_SetError("Unable to allocate toolkit window structure");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    window->mode = mode;
    window->tk_parent = tkparent;

#ಯದಿ SDL_SET_LOCALE
    ಯದಿ (mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        window->origlocale = setlocale(LC_ALL, ರಿಕ್ತ);
        ಯದಿ (window->origlocale) {
            window->origlocale = SDL_strdup(window->origlocale);
            ಯದಿ (!window->origlocale) {
                SDL_free(window);
                ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
            }
            (ಶೂನ್ಯ)setlocale(LC_ALL, "");
        }
    }
#endif

    window->parent_device = ರಿಕ್ತ;
    ಯದಿ (create_new_display) {
        window->display = X11_XOpenDisplay(ರಿಕ್ತ);
        window->display_close = true;
        ಯದಿ (!window->display) {
            ErrorFreeRetNull("Couldn't open X11 display", window);
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (parent) {
            window->parent_device = SDL_GetVideoDevice();
            window->display = window->parent_device->internal->display;
            window->display_close = false;
        } ಅನ್ಯಥಾ ಯದಿ (tkparent) {
            window->display = tkparent->display;
            window->display_close = false;
        } ಅನ್ಯಥಾ {
            window->display = X11_XOpenDisplay(ರಿಕ್ತ);
            window->display_close = true;
            ಯದಿ (!window->display) {
                ErrorFreeRetNull("Couldn't open X11 display", window);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    ಪೂರ್ಣಾಙ್ಕ xrandr_event_base, xrandr_error_base;
    window->xrandr = X11_XRRQueryExtension(window->display, &xrandr_event_base, &xrandr_error_base);
#endif

#ifndef NO_SHARED_MEMORY
    window->shm_pixmap = False;
    window->shm = X11_XShmQueryExtension(window->display) ? SDL_X11_HAVE_SHM : false;
    ಯದಿ (window->shm) {
        ಪೂರ್ಣಾಙ್ಕ major;
        ಪೂರ್ಣಾಙ್ಕ minor;

        X11_XShmQueryVersion(window->display, &major, &minor, &window->shm_pixmap);
        ಯದಿ (window->shm_pixmap) {
            ಯದಿ (X11_XShmPixmapFormat(window->display) != ZPixmap) {
                window->shm_pixmap = False;
            }
        }
    }
#endif

    /* Scale/Xsettings */
    window->pixmap = false;
    window->xsettings_first_time = true;
    window->xsettings = xsettings_client_new(window->display, DefaultScreen(window->display), X11Toolkit_SettingsNotify, ರಿಕ್ತ, window);
    window->xsettings_first_time = false;
    window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
    ಯದಿ (window->scale < 1) {
        window->scale = 1;
    }
    window->iscale = (ಪೂರ್ಣಾಙ್ಕ)SDL_ceilf(window->scale);
    ಯದಿ (SDL_roundf(window->scale) == window->scale) {
        window->scale = 0;
    }

    /* Fonts */
    X11Toolkit_InitWindowFonts(window);

    /* Color hints */
#ifdef SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    ಯದಿ (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#endif

    ಯದಿ (!colorhints) {
#ifdef SDL_USE_LIBDBUS
        ವಿಕಲ್ಪ (theme) {
            ಪಕ್ಷ SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                ಭಙ್ಗ;
#ಯದಿ 0
            ಪಕ್ಷ SDL_SYSTEM_THEME_LIGHT_ಮೇಲಿನ_CONTRAST:
                colorhints = g_default_colors_light_ಮೇಲಿನ_contrast;
                ಭಙ್ಗ;
            ಪಕ್ಷ SDL_SYSTEM_THEME_DARK_ಮೇಲಿನ_CONTRAST:
                colorhints = g_default_colors_dark_ಮೇಲಿನ_contrast;
                ಭಙ್ಗ;
#endif
            ಸ್ವಭಾವ:
                colorhints = g_default_colors;
        }
#ಅನ್ಯಥಾ
        colorhints = g_default_colors;
#endif
    }
    window->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    ಪ್ರತಿ (i = 0; i < SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ; i++) {
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
    ಯದಿ (parent) {
        SDL_DisplayData *displaydata = SDL_GetDisplayDriverDataForWindow(parent);
        window->screen = displaydata->screen;
    } ಅನ್ಯಥಾ {
        window->screen = DefaultScreen(window->display);
    }

    /* Visuals */
    ಯದಿ (mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        window->visual = parent->internal->visual;
        window->cmap = parent->internal->colormap;
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
        window->depth = window->vi.depth;
    } ಅನ್ಯಥಾ {
        window->visual = DefaultVisual(window->display, window->screen);
        window->cmap = DefaultColormap(window->display, window->screen);
        window->depth = DefaultDepth(window->display, window->screen);
        X11_GetVisualInfoFromVisual(window->display, window->visual, &window->vi);
    }

    /* Allocate colors */
    ಪ್ರತಿ (i = 0; i < SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ; i++) {
        X11_XAllocColor(window->display, window->cmap, &window->xcolor[i]);
    }
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l1);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l2);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_d);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_pressed);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_disabled_text);

    /* Control list */
    window->has_focus = false;
    window->controls = ರಿಕ್ತ;
    window->controls_sz = 0;
    window->dyn_controls_sz = 0;
    window->fiddled_control = ರಿಕ್ತ;
    window->dyn_controls = ರಿಕ್ತ;

    /* Menu windows */
    window->popup_windows = ರಿಕ್ತ;

    /* BIDI engine */
#ifdef HAVE_FRIBIDI_H
    window->fribidi = SDL_FriBidi_Create();
#endif

#ifdef HAVE_LIBTHAI_H
    window->th = SDL_LibThai_Create();
#endif
    
    /* Interface direction */
    window->flip_interface = X11Toolkit_ShouldFlipUI();
    
    ಪ್ರತ್ಯಾಗಮ window;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_AddControlToWindow(SDL_ToolkitWindowX11 *window, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    window->controls_sz++;
    ಯದಿ (window->controls_sz == 1) {
        window->controls = (ಸಂರಚನಾ SDL_ToolkitControlX11 **)SDL_malloc(ಪರಿಮಾಣ(ಸಂರಚನಾ SDL_ToolkitControlX11 *));
    } ಅನ್ಯಥಾ {
        window->controls = (ಸಂರಚನಾ SDL_ToolkitControlX11 **)SDL_realloc(window->controls, ಪರಿಮಾಣ(ಸಂರಚನಾ SDL_ToolkitControlX11 *) * window->controls_sz);
    }
    window->controls[window->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    ಯದಿ (control->dynamic) {
        window->dyn_controls_sz++;
        ಯದಿ (window->dyn_controls_sz == 1) {
            window->dyn_controls = (ಸಂರಚನಾ SDL_ToolkitControlX11 **)SDL_malloc(ಪರಿಮಾಣ(ಸಂರಚನಾ SDL_ToolkitControlX11 *));
        } ಅನ್ಯಥಾ {
            window->dyn_controls = (ಸಂರಚನಾ SDL_ToolkitControlX11 **)SDL_realloc(window->dyn_controls, ಪರಿಮಾಣ(ಸಂರಚನಾ SDL_ToolkitControlX11 *) * window->dyn_controls_sz);
        }
        window->dyn_controls[window->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    ಯದಿ (control->selected) {
        window->focused_control = control;
    }
}

bool X11Toolkit_CreateWindowRes(SDL_ToolkitWindowX11 *data, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, ಪೂರ್ಣಾಙ್ಕ cx, ಪೂರ್ಣಾಙ್ಕ cy, ವರ್ಣ *title)
{
    ಪೂರ್ಣಾಙ್ಕ x, y;
    XSizeHints *sizehints;
    XSetWindowAttributes wnd_attr;
    Atom _NET_WM_WINDOW_TYPE, _NET_WM_WINDOW_TYPE_DIALOG, _NET_WM_WINDOW_TYPE_DROPDOWN_MENU, _NET_WM_WINDOW_TYPE_TOOLTIP;
    SDL_WindowData *windowdata = ರಿಕ್ತ;
    Display *display = data->display;
    XGCValues ctx_vals;
    Window ಬೇರು_win;
    Window parent_win;
    unsigned long gcflags = GCForeground | GCBackground;
    unsigned long valuemask;
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
#ifdef XRANDR_DISABLED_BY_DEFAULT
    ಧ್ರುವ bool use_xrandr_by_default = false;
#ಅನ್ಯಥಾ
    ಧ್ರುವ bool use_xrandr_by_default = true;
#endif
#endif

    ಯದಿ (data->scale == 0) {
        data->window_width = w;
        data->window_height = h;
    } ಅನ್ಯಥಾ {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        data->pixmap = true;
    }

    ಯದಿ (data->parent) {
        windowdata = data->parent->internal;
    }

    valuemask = CWEventMask | CWColormap;
    data->event_mask = ExposureMask |
                       ButtonPressMask | ButtonReleaseMask | ಕೀಲಿ_Press_Mask | ಕೀಲಿ_Release_Mask |
                       StructureNotifyMask | FocusChangeMask | PointerMotionMask;
    wnd_attr.event_mask = data->event_mask;
    wnd_attr.colormap = data->cmap;
    ಯದಿ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    ಬೇರು_win = ಬೇರು_Window(display, data->screen);
    ಯದಿ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        parent_win = windowdata->xwindow;
    } ಅನ್ಯಥಾ {
        parent_win = ಬೇರು_win;
    }

    data->window = X11_XCreateWindow(
        display, parent_win,
        0, 0,
        data->window_width, data->window_height,
        0, data->depth, ಒಳಹರಿವು_Output, data->visual,
        valuemask, &wnd_attr);
    ಯದಿ (data->window == None) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't create X window");
    }

    ಯದಿ (windowdata && data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
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
                            PropModeReplace, (unsigned ವರ್ಣ *)stateatoms, statecount);
    }

    ಯದಿ (windowdata && data->mode != SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        X11_XSetTransientForHint(display, data->window, windowdata->xwindow);
    }

    ಯದಿ (data->tk_parent) {
        X11_XSetTransientForHint(display, data->window, data->tk_parent->window);
    }

    SDL_X11_SetWindowTitle(display, data->window, title);

    // Let the window manager the type of the window
    ಯದಿ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned ವರ್ಣ *)&_NET_WM_WINDOW_TYPE_DIALOG, 1);
    } ಅನ್ಯಥಾ ಯದಿ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned ವರ್ಣ *)&_NET_WM_WINDOW_TYPE_DROPDOWN_MENU, 1);
    } ಅನ್ಯಥಾ ಯದಿ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, data->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (unsigned ವರ್ಣ *)&_NET_WM_WINDOW_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    data->wm_delete_message = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, data->window, &data->wm_delete_message, 1);
    data->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    ಯದಿ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        x = cx;
        y = cy;
        ಗಚ್ಛ MOVEWINDOW;
    }
    ಯದಿ (windowdata) {
        XWindowAttributes attrib;
        Window dummy;

        X11_XGetWindowAttributes(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.width - data->window_width) / 2;
        y = attrib.y + (attrib.height - data->window_height) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, ಬೇರು_Window(display, data->screen), x, y, &x, &y, &dummy);
    } ಅನ್ಯಥಾ {
        ಧ್ರುವ SDL_VideoDevice *dev = SDL_GetVideoDevice();
        ಯದಿ (dev && dev->displays && dev->ಅಂಕೆ_displays > 0) {
            ಧ್ರುವ SDL_VideoDisplay *dpy = dev->displays[0];
            ಧ್ರುವ SDL_DisplayData *dpydata = dpy->internal;
            x = dpydata->x + ((dpy->current_mode->w - data->window_width) / 2);
            y = dpydata->y + ((dpy->current_mode->h - data->window_height) / 3);
        }
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
        ಅನ್ಯಥಾ ಯದಿ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && data->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_out;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, ಬೇರು_win);
            ಯದಿ (!screen_res) {
                ಗಚ್ಛ NOXRANDR;
            }

            default_out = X11_XRRGetOutputPrimary(display, ಬೇರು_win);
            ಯದಿ (default_out != None) {
                XRROutputInfo *out_info;

                out_info = X11_XRRGetOutputInfo(display, screen_res, default_out);
                ಯದಿ (out_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(out_info);
                    ಗಚ್ಛ FIRSTOUTPUTXRANDR;
                }

                ಯದಿ (out_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                } ಅನ್ಯಥಾ ಯದಿ (out_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                } ಅನ್ಯಥಾ {
                    crtc_info = ರಿಕ್ತ;
                }
                
                ಯದಿ (crtc_info) {
                    x = (crtc_info->width - data->window_width) / 2;
                    y = (crtc_info->height - data->window_height) / 3;
                    X11_XRRFreeOutputInfo(out_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } ಅನ್ಯಥಾ {
                    X11_XRRFreeOutputInfo(out_info);
                    ಗಚ್ಛ NOXRANDR;
                }
            } ಅನ್ಯಥಾ {
                    FIRSTOUTPUTXRANDR:
                    ಯದಿ (screen_res->noutput > 0) {
                        XRROutputInfo *out_info;

                        out_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        ಯದಿ (!out_info) {
                            ಗಚ್ಛ FIRSTCRTCXRANDR;
                        }

                        ಯದಿ (out_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                        } ಅನ್ಯಥಾ ಯದಿ (out_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                        } ಅನ್ಯಥಾ {
                            crtc_info = ರಿಕ್ತ;
                        }

                        ಯದಿ (!crtc_info) {
                            X11_XRRFreeOutputInfo(out_info);
                            ಗಚ್ಛ FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeOutputInfo(out_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        ಗಚ್ಛ MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    ಯದಿ (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        ಗಚ್ಛ NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    ಯದಿ (crtc_info) {
                        x = (crtc_info->width - data->window_width) / 2;
                        y = (crtc_info->height - data->window_height) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } ಅನ್ಯಥಾ {
                        X11_XRRFreeScreenResources(screen_res);
                        ಗಚ್ಛ NOXRANDR;
                    }
            }
        }
#endif
        ಅನ್ಯಥಾ {
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
    ಯದಿ (sizehints) {
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
    ಯದಿ (SDL_X11_HAVE_XDBE && !data->pixmap) {
        ಪೂರ್ಣಾಙ್ಕ xdbe_major, xdbe_minor;
        ಯದಿ (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            data->xdbe = true;
            data->buf = X11_XdbeAllocateBackBufferName(display, data->window, XdbeUndefined);
            data->drawable = data->buf;
        } ಅನ್ಯಥಾ {
            data->xdbe = false;
        }
    }
#endif

    X11Toolkit_InitWindowPixmap(data);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ಯದಿ (!data->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = data->font_struct->fid;
    }
    data->ctx = X11_XCreateGC(data->display, data->drawable, gcflags, &ctx_vals);
    ಯದಿ (data->ctx == None) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't create graphics context");
    }

    data->close = false;
    data->ಕೀಲಿ_control_esc = data->ಕೀಲಿ_control_enter = ರಿಕ್ತ;
    ಯದಿ (!data->pixmap) {
        data->ev_scale = data->ev_iscale = 1;
    } ಅನ್ಯಥಾ {
        data->ev_scale = data->scale;
        data->ev_iscale = data->iscale;
    }

#ಯದಿ SDL_GRAB
    ಯದಿ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XGrabPointer(display, data->window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
        X11_XGrabKeyboard(display, data->window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
#endif

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DrawWindow(SDL_ToolkitWindowX11 *data) {
    SDL_Rect rect;
    ಪೂರ್ಣಾಙ್ಕ i;

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    ಯದಿ (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeBeginIdiom(data->display);
    }
#endif

    X11_XSetForeground(data->display, data->ctx, data->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    ಯದಿ (data->pixmap) {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->pixmap_width, data->pixmap_height);
    } ಅನ್ಯಥಾ {
        X11_XFillRectangle(data->display, data->drawable, data->ctx, 0, 0, data->window_width, data->window_height);
    }

    ಪ್ರತಿ (i = 0; i < data->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = data->controls[i];
        ಯದಿ (control) {
            ಯದಿ (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    ಯದಿ (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        XdbeSwapInfo swap_info;
        swap_info.swap_window = data->window;
        swap_info.swap_action = XdbeUndefined;
        X11_XdbeSwapBuffers(data->display, &swap_info, 1);
        X11_XdbeEndIdiom(data->display);
    }
#endif

    ಯದಿ (data->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = data->window_width;
        rect.h = data->window_height;
#ifndef NO_SHARED_MEMORY
        ಯದಿ (data->shm) {
            ಯದಿ (data->shm_pixmap) {
                X11_XFlush(data->display);
                X11_XSync(data->display, false);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->shm_info.shmaddr, data->shm_bytes_per_ಸಾಲು);
                SDL_BlitSurfaceScaled(scale_surface, ರಿಕ್ತ, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(data->display, data->drawable, data->window, data->ctx, 0, 0, data->window_width, data->window_height, 0, 0);
            } ಅನ್ಯಥಾ {
                X11_XShmGetImage(data->display, data->drawable, data->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), data->image->data, data->image->bytes_per_ಸಾಲು);
                SDL_BlitSurfaceScaled(scale_surface, ರಿಕ್ತ, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                X11_XShmPutImage(data->display, data->window, data->ctx, data->image, 0, 0, 0, 0, data->window_width, data->window_height, False);
            }
        } ಅನ್ಯಥಾ
#endif
        {
            XImage *image;

            image = X11_XGetImage(data->display, data->drawable, 0, 0 , data->pixmap_width, data->pixmap_height, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(data->pixmap_width, data->pixmap_height, X11_GetPixelFormatFromVisualInfo(data->display, &data->vi), image->data, image->bytes_per_ಸಾಲು);
            SDL_BlitSurfaceScaled(scale_surface, ರಿಕ್ತ, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
            X11_XPutImage(data->display, data->window, data->ctx, image, 0, 0, 0, 0, data->window_width, data->window_height);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(data->display);
}

ಸ್ಥಿರ SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_ToolkitWindowX11 *data, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < data->controls_sz; i++) {
        SDL_Rect *rect = &data->controls[i]->rect;
        ಯದಿ ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            ಪ್ರತ್ಯಾಗಮ data->controls[i];
        }
    }

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
ಸ್ಥಿರ Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_ToolkitWindowX11 *data = (SDL_ToolkitWindowX11 *)arg;

    ಯದಿ (event->xany.display != data->display) {
        ಪ್ರತ್ಯಾಗಮ False;
    }

    ಯದಿ (event->xany.window == data->window) {
        ಪ್ರತ್ಯಾಗಮ True;
    }

    ಪ್ರತ್ಯಾಗಮ False;
}

ಶೂನ್ಯ X11Toolkit_ProcessWindowEvents(SDL_ToolkitWindowX11 *data, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    ಯದಿ ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    data->draw = false;
    data->e = e;

    ವಿಕಲ್ಪ (e->type) {
        ಪಕ್ಷ Expose:
            data->draw = true;
            ಭಙ್ಗ;
        ಪಕ್ಷ ClientMessage:
            ಯದಿ (e->xclient.message_type == data->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.data.l[0] == data->wm_delete_message) {
                data->close = true;
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ FocusIn:
            data->has_focus = true;
            ಭಙ್ಗ;
        ಪಕ್ಷ FocusOut:
            data->has_focus = false;
            ಯದಿ (data->fiddled_control) {
                data->fiddled_control->selected = false;
            }
            data->fiddled_control = ರಿಕ್ತ;
            ಪ್ರತಿ (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ MotionNotify:
            ಯದಿ (data->has_focus) {
                data->previous_control = data->fiddled_control;
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                ಯದಿ (data->previous_control) {
                    data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    ಯದಿ (data->previous_control->func_on_state_change) {
                        data->previous_control->func_on_state_change(data->previous_control);
                    }
                    data->draw = true;
                }
                ಯದಿ (data->fiddled_control) {
                    ಯದಿ (data->fiddled_control->dynamic) {
                        data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        ಯದಿ (data->fiddled_control->func_on_state_change) {
                            data->fiddled_control->func_on_state_change(data->fiddled_control);
                        }
                        data->draw = true;
                    } ಅನ್ಯಥಾ {
                        data->fiddled_control = ರಿಕ್ತ;
                    }
                }
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ ButtonPress:
            data->previous_control = data->fiddled_control;
            ಯದಿ (data->previous_control) {
                data->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                ಯದಿ (data->previous_control->func_on_state_change) {
                    data->previous_control->func_on_state_change(data->previous_control);
                }
                data->draw = true;
            }
            ಯದಿ (e->xbutton.button == Button1) {
                data->fiddled_control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                ಯದಿ (data->fiddled_control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    ಯದಿ (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->draw = true;
                }
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ ButtonRelease:
            ಯದಿ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
                ಪೂರ್ಣಾಙ್ಕ cx;
                ಪೂರ್ಣಾಙ್ಕ cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                ಯದಿ (cy < 0 || cx < 0) {
                    data->close = true;
                }

                ಯದಿ (cy > data->window_height || cx > data->window_width) {
                    data->close = true;
                }
            }

            ಯದಿ ((e->xbutton.button == Button1) && (data->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(data, SDL_lroundf((e->xbutton.x/ data->ev_scale)* data->ev_iscale), SDL_lroundf((e->xbutton.y/ data->ev_scale)* data->ev_iscale));
                ಯದಿ (data->fiddled_control == control) {
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    ಯದಿ (data->fiddled_control->func_on_state_change) {
                        data->fiddled_control->func_on_state_change(data->fiddled_control);
                    }
                    data->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    data->draw = true;
                }
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ ಕೀಲಿ_Press:
            data->last_ಕೀಲಿ_pressed = X11_XLookupKeysym(&e->xkey, 0);

            ಯದಿ (data->last_ಕೀಲಿ_pressed == XK_Escape) {
                ಪ್ರತಿ (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    ಯದಿ(data->controls[data->ev_i]->is_default_esc) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->ಕೀಲಿ_control_esc = data->controls[data->ev_i];
                    }
                }
            } ಅನ್ಯಥಾ ಯದಿ ((data->last_ಕೀಲಿ_pressed == XK_Return) || (data->last_ಕೀಲಿ_pressed == XK_KP_Enter)) {
                ಪ್ರತಿ (data->ev_i = 0; data->ev_i < data->controls_sz; data->ev_i++) {
                    ಯದಿ(data->controls[data->ev_i]->selected) {
                        data->controls[data->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        data->draw = true;
                        data->ಕೀಲಿ_control_enter = data->controls[data->ev_i];
                    }
                }
            }
            ಭಙ್ಗ;
        ಪಕ್ಷ ಕೀಲಿ_Release:
        {
            ಕೀಲಿ_Sym ಕೀಲಿ = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            ಯದಿ (ಕೀಲಿ != data->last_ಕೀಲಿ_pressed) {
                ಭಙ್ಗ;
            }

            ಯದಿ (ಕೀಲಿ == XK_Escape) {
                ಯದಿ (data->ಕೀಲಿ_control_esc) {
                    ಯದಿ (data->ಕೀಲಿ_control_esc->func_on_state_change) {
                        data->ಕೀಲಿ_control_esc->func_on_state_change(data->ಕೀಲಿ_control_esc);
                    }
                }
            } ಅನ್ಯಥಾ ಯದಿ ((ಕೀಲಿ == XK_Return) || (ಕೀಲಿ == XK_KP_Enter)) {
                ಯದಿ (data->ಕೀಲಿ_control_enter) {
                    ಯದಿ (data->ಕೀಲಿ_control_enter->func_on_state_change) {
                        data->ಕೀಲಿ_control_enter->func_on_state_change(data->ಕೀಲಿ_control_enter);
                    }
                }
            } ಅನ್ಯಥಾ ಯದಿ (ಕೀಲಿ == XK_Tab || ಕೀಲಿ == XK_ಎಡ || ಕೀಲಿ == XK_ಬಲ) {
                ಯದಿ (data->focused_control) {
                    data->focused_control->selected = false;
                }
                data->draw = true;
                ಪ್ರತಿ (data->ev_i = 0; data->ev_i < data->dyn_controls_sz; data->ev_i++) {
                    ಯದಿ (data->dyn_controls[data->ev_i] == data->focused_control) {
                        ಪೂರ್ಣಾಙ್ಕ next_index;

                        ಯದಿ (ಕೀಲಿ == XK_ಎಡ) {
                            next_index = data->ev_i - 1;
                        } ಅನ್ಯಥಾ {
                            next_index = data->ev_i + 1;
                        }
                        ಯದಿ ((next_index >= data->dyn_controls_sz) || (next_index < 0)) {
                            ಯದಿ (ಕೀಲಿ == XK_ಬಲ || ಕೀಲಿ == XK_ಎಡ) {
                                next_index = data->ev_i;
                            } ಅನ್ಯಥಾ {
                                next_index = 0;
                            }
                        }
                        data->focused_control = data->dyn_controls[next_index];
                        data->focused_control->selected = true;
                        ಭಙ್ಗ;
                    }
                }
            }
            ಭಙ್ಗ;
        }
    }

    ಯದಿ (data->draw) {
        X11Toolkit_DrawWindow(data);
    }
}

ಶೂನ್ಯ X11Toolkit_DoWindowEventLoop(SDL_ToolkitWindowX11 *data) {
   ಯಾವತ್ (!data->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(data->display, &e);
        ಯದಿ (data->xsettings) {
            xsettings_client_process_event(data->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(data->display, &e, X11Toolkit_EventTest, (XPointer)data);
        X11Toolkit_ProcessWindowEvents(data, &e);
    }
}


ಶೂನ್ಯ X11Toolkit_ResizeWindow(SDL_ToolkitWindowX11 *data, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h) {
    ಯದಿ (!data->pixmap) {
        data->window_width = w;
        data->window_height = h;
    } ಅನ್ಯಥಾ {
        data->window_width = SDL_lroundf((w/data->iscale) * data->scale);
        data->window_height = SDL_lroundf((h/data->iscale) * data->scale);
        data->pixmap_width = w;
        data->pixmap_height = h;
        X11_XFreePixmap(data->display, data->drawable);
        X11Toolkit_InitWindowPixmap(data);
    }

    X11_XResizeWindow(data->display, data->window, data->window_width, data->window_height);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->window->display, icon_control->icon_char_font);
    SDL_free(control);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->window->iscale;
    control->rect.h -= 2 * control->window->iscale;
    X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + (2 * control->window->iscale), control->rect.y + (2* control->window->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    ವಿಕಲ್ಪ (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        ಪಕ್ಷ SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                ಭಙ್ಗ;
        ಪಕ್ಷ SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                ಭಙ್ಗ;
        ಪಕ್ಷ SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                ಭಙ್ಗ;
    }
    X11_XSetFont(control->window->display, control->window->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    ಯದಿ (!control->window->utf8) {
        X11_XSetFont(control->window->display, control->window->ctx, control->window->font_struct->fid);
    }

    control->rect.w += 2 * control->window->iscale;
    control->rect.h += 2 * control->window->iscale;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    ಪೂರ್ಣಾಙ್ಕ icon_char_w;
    ಪೂರ್ಣಾಙ್ಕ icon_wh;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11Toolkit_GetTextWidthHeightForFont(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, ರಿಕ್ತ);
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

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    ವರ್ಣ *font;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11_XFreeFont(base_control->window->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_SIZE * base_control->window->iscale);
    control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
    SDL_free(font);
    ಯದಿ (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * base_control->window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_ToolkitWindowX11 *window, SDL_MessageBoxFlags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    ವರ್ಣ *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(ಪರಿಮಾಣ(SDL_ToolkitIconControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    ಯದಿ (!control) {
        SDL_SetError("Unable to allocate icon control structure");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    /* Fill out struct */
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawIconControl;
    base_control->func_free = X11Toolkit_DestroyIconControl;
    base_control->func_on_state_change = ರಿಕ್ತ;
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
    ಯದಿ (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_SIZE * window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        ಯದಿ (!control->icon_char_font) {
            SDL_free(control);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
    }

    /* Set colors */
    ವಿಕಲ್ಪ (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    ಪಕ್ಷ SDL_MESSAGEBOX_ERROR:
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
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_MESSAGEBOX_WARNING:
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
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_MESSAGEBOX_INFORMATION:
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
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        X11_XFreeFont(window->display, control->icon_char_font);
        SDL_free(control);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    ಯದಿ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } ಅನ್ಯಥಾ ಯದಿ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } ಅನ್ಯಥಾ {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    ಯದಿ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } ಅನ್ಯಥಾ ಯದಿ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } ಅನ್ಯಥಾ {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    ಯದಿ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } ಅನ್ಯಥಾ ಯದಿ (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } ಅನ್ಯಥಾ {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(window->display, window->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(base_control);

    X11Toolkit_AddControlToWindow(window, base_control);
    ಪ್ರತ್ಯಾಗಮ base_control;
}

bool X11Toolkit_NotifyControlOfSizeChange(SDL_ToolkitControlX11 *control) {
    ಯದಿ (control->func_calc_size) {
        control->func_calc_size(control);
        ಪ್ರತ್ಯಾಗಮ true;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ false;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11Toolkit_GetTextElementsRect(button_control->text, &button_control->text_rect);
    ಯದಿ (control->do_size) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.h;
    }
    button_control->text_rect.x = (control->rect.w - button_control->text_rect.w)/2;
    button_control->text_rect.y = (control->rect.h - button_control->text_rect.h)/2;
}


ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    /* Draw bevel */
    ಯದಿ (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
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
        } ಅನ್ಯಥಾ {
            ಯದಿ (control->selected) {
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
            } ಅನ್ಯಥಾ {
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

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    ಯದಿ (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_data);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11Toolkit_FreeTextElements(button_control->text);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_ToolkitWindowX11 *window, ಧ್ರುವ SDL_MessageBoxButtonData *data) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *base_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(ಪರಿಮಾಣ(SDL_ToolkitButtonControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    ಯದಿ (!control) {
        SDL_SetError("Unable to allocate button control structure");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    base_control->window = window;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->func_calc_size = X11Toolkit_CalculateButtonControl;
    base_control->func_draw = X11Toolkit_DrawButtonControl;
    base_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    base_control->func_free = X11Toolkit_DestroyButtonControl;
    base_control->func_on_scale_change = ರಿಕ್ತ;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = true;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    ಯದಿ (data->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        base_control->is_default_esc = true;
    }
    ಯದಿ (data->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        base_control->is_default_enter = true;
        base_control->selected = true;
    }
    control->cb = ರಿಕ್ತ;
    control->data = data;
#ifdef HAVE_FRIBIDI_H
    control->text = X11Toolkit_MakeTextElements(base_control->window, (ವರ್ಣ *)control->data->text, SDL_strlen(control->data->text), ರಿಕ್ತ);
#ಅನ್ಯಥಾ 
    control->text = X11Toolkit_MakeTextElements(base_control->window, (ವರ್ಣ *)control->data->text, SDL_strlen(control->data->text));
#endif
    X11Toolkit_ShapeTextElements(base_control->window, control->text);
    
    base_control->do_size = true;
    X11Toolkit_CalculateButtonControl(base_control);
    base_control->do_size = false;

    X11Toolkit_AddControlToWindow(window, base_control);
    ಪ್ರತ್ಯಾಗಮ base_control;
}

ಶೂನ್ಯ X11Toolkit_RegisterCallbackForButtonControl(SDL_ToolkitControlX11 *control, ಶೂನ್ಯ *data, ಶೂನ್ಯ (*cb)(ಸಂರಚನಾ SDL_ToolkitControlX11 *, ಶೂನ್ಯ *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_data = data;
    button_control->cb = cb;
}

ಧ್ರುವ SDL_MessageBoxButtonData *X11Toolkit_GetButtonControlData(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    ಪ್ರತ್ಯಾಗಮ button_control->data;
}

ಶೂನ್ಯ X11Toolkit_DestroyWindow(SDL_ToolkitWindowX11 *data) {
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (!data) {
        ಪ್ರತ್ಯಾಗಮ;
    }

#ಯದಿ SDL_GRAB
    ಯದಿ (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || data->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XUngrabPointer(data->display, CurrentTime);
        X11_XUngrabKeyboard(data->display, CurrentTime);
    }
#endif

    ಪ್ರತಿ (i = 0; i < data->controls_sz; i++) {
        ಯದಿ (data->controls[i]->func_free) {
            data->controls[i]->func_free(data->controls[i]);
        }
    }
    SDL_free(data->controls);
    SDL_free(data->dyn_controls);

    ಯದಿ (data->popup_windows) {
        SDL_ListClear(&data->popup_windows);
    }

    ಯದಿ (data->pixmap) {
        X11_XFreePixmap(data->display, data->drawable);
    }

#ifndef NO_SHARED_MEMORY
    ಯದಿ (data->pixmap && data->shm) {
        X11_XShmDetach(data->display, &data->shm_info);
        ಯದಿ (!data->shm_pixmap) {
            XDestroyImage(data->image);
        }
        shmdt(data->shm_info.shmaddr);
    }
#endif

#ifdef X_HAVE_UTF8_STRING
    ಯದಿ (data->font_set) {
        X11_XFreeFontSet(data->display, data->font_set);
        data->font_set = ರಿಕ್ತ;
    }
#endif

    ಯದಿ (data->font_struct) {
        X11_XFreeFont(data->display, data->font_struct);
        data->font_struct = ರಿಕ್ತ;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XDBE
    ಯದಿ (SDL_X11_HAVE_XDBE && data->xdbe && !data->pixmap) {
        X11_XdbeDeallocateBackBufferName(data->display, data->buf);
    }
#endif

    ಯದಿ (data->xsettings) {
        xsettings_client_destroy(data->xsettings);
    }

    X11_XFreeGC(data->display, data->ctx);

    ಯದಿ (data->display) {
        ಯದಿ (data->window != None) {
            X11_XWithdrawWindow(data->display, data->window, data->screen);
            X11_XDestroyWindow(data->display, data->window);
            data->window = None;
        }

        ಯದಿ (data->display_close) {
            X11_XCloseDisplay(data->display);
        }
        data->display = ರಿಕ್ತ;
    }

#ಯದಿ SDL_SET_LOCALE
    ಯದಿ (data->origlocale && (data->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG)) {
        (ಶೂನ್ಯ)setlocale(LC_ALL, data->origlocale);
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

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ X11_Toolkit_ಎಣಿಕೆ_ಸಾಲುಗಳು_Of_Text(ಧ್ರುವ ವರ್ಣ *text)
{
    ಪೂರ್ಣಾಙ್ಕ result = 0;
    ಯಾವತ್ (text && *text) {
        ಧ್ರುವ ವರ್ಣ *lf = SDL_strchr(text, '\n');
        result++; // even without an endline, this counts as a line.
        text = lf ? lf + 1 : ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    ಪೂರ್ಣಾಙ್ಕ i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    ಪ್ರತಿ (i = 0; i < label_control->sz; i++) {
        X11Toolkit_DrawTextElements(control->window, label_control->ಸಾಲುಗಳು[i].text, control->rect.x + label_control->ಸಾಲುಗಳು[i].rect.x, control->rect.y + label_control->ಸಾಲುಗಳು[i].rect.y);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    ಪೂರ್ಣಾಙ್ಕ i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    ಪ್ರತಿ (i = 0; i < label_control->sz; i++) {
        X11Toolkit_FreeTextElements(label_control->ಸಾಲುಗಳು[i].text);
    }
    SDL_free(label_control->ಸಾಲುಗಳು);
    SDL_free(label_control);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitLabelControlX11 *control;
    ಪೂರ್ಣಾಙ್ಕ i;

    control = (SDL_ToolkitLabelControlX11 *)base_control;
    
    ಯದಿ (base_control->do_size) {
        base_control->rect.w = 0;
        base_control->rect.h = 0;
    }
    
    ಪ್ರತಿ (i = 0; i < control->sz; i++) {
        ಪೂರ್ಣಾಙ್ಕ font_h;
        
        font_h = X11Toolkit_GetTextElementsRect(control->ಸಾಲುಗಳು[i].text, &control->ಸಾಲುಗಳು[i].rect);
        
        ಯದಿ (base_control->do_size) {
            base_control->rect.w = SDL_max(base_control->rect.w, control->ಸಾಲುಗಳು[i].rect.w);
        }
        
        ಯದಿ (i > 0) {
            control->ಸಾಲುಗಳು[i].rect.y = font_h + control->ಸಾಲುಗಳು[i - 1].rect.y;
        } ಅನ್ಯಥಾ {
            control->ಸಾಲುಗಳು[i].rect.y = 0;
        }
    }

#ifdef HAVE_FRIBIDI_H
    ಯದಿ (base_control->window->fribidi) {
        FriBidiParType first_ndn_dir;
        ಪೂರ್ಣಾಙ್ಕ last_ndn;
    
        first_ndn_dir = FRIBIDI_PAR_LTR;
        ಪ್ರತಿ (i = 0; i < control->sz; i++) {
            ಯದಿ (control->ಸಾಲುಗಳು[i].par != FRIBIDI_PAR_ON) {
                first_ndn_dir = control->ಸಾಲುಗಳು[i].par;
            }
        }

        last_ndn = -1;
        ಪ್ರತಿ (i = 0; i < control->sz; i++) {
            ವಿಕಲ್ಪ (control->ಸಾಲುಗಳು[i].par) {
                ಪಕ್ಷ FRIBIDI_PAR_LTR:
                    control->ಸಾಲುಗಳು[i].rect.x = 0;
                    last_ndn = i;
                    ಭಙ್ಗ;
                ಪಕ್ಷ FRIBIDI_PAR_RTL:
                    control->ಸಾಲುಗಳು[i].rect.x = base_control->rect.w - control->ಸಾಲುಗಳು[i].rect.w;
                    last_ndn = i;
                    ಭಙ್ಗ;
                ಸ್ವಭಾವ:
                    ಯದಿ (last_ndn != -1) {
                        ಯದಿ (control->ಸಾಲುಗಳು[last_ndn].par == FRIBIDI_PAR_RTL) {
                            control->ಸಾಲುಗಳು[i].rect.x = base_control->rect.w - control->ಸಾಲುಗಳು[i].rect.w;
                        } ಅನ್ಯಥಾ {
                            control->ಸಾಲುಗಳು[i].rect.x = 0;
                        }
                    } ಅನ್ಯಥಾ {
                        ಯದಿ (first_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->ಸಾಲುಗಳು[i].rect.x = base_control->rect.w - control->ಸಾಲುಗಳು[i].rect.w;
                        } ಅನ್ಯಥಾ {
                            control->ಸಾಲುಗಳು[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#endif
    
    ಯದಿ (base_control->do_size && control->sz) {
        base_control->rect.h = control->ಸಾಲುಗಳು[control->sz - 1].rect.y + control->ಸಾಲುಗಳು[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_ToolkitWindowX11 *window, ವರ್ಣ *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    ಪೂರ್ಣಾಙ್ಕ i;
    
    ಯದಿ (!utf8) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
 
    ಯದಿ (!SDL_strcmp(utf8, "")) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(ಪರಿಮಾಣ(SDL_ToolkitLabelControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    ಯದಿ (!control) {
        SDL_SetError("Unable to allocate label control structure");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawLabelControl;
    base_control->func_on_state_change = ರಿಕ್ತ;
    base_control->func_calc_size = X11Toolkit_CalculateLabelControl;
    base_control->func_free  = X11Toolkit_DestroyLabelControl;
    base_control->func_on_scale_change = ರಿಕ್ತ;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = false;
    base_control->rect.w = 0;
    base_control->rect.h = 0;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_ಎಣಿಕೆ_ಸಾಲುಗಳು_Of_Text(utf8);
    control->ಸಾಲುಗಳು = SDL_calloc(control->sz, ಪರಿಮಾಣ(SDL_Toolkit_Label_Control_ಸಾಲು_X11));
    ಪ್ರತಿ (i = 0; i < control->sz; i++) {
        ಧ್ರುವ ವರ್ಣ *lf = SDL_strchr(utf8, '\n');
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ length = lf ? (lf - utf8) : SDL_strlen(utf8);
        ಪೂರ್ಣಾಙ್ಕ sz;
        
        sz = length;
        ಯದಿ (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#ifdef HAVE_FRIBIDI_H
        control->ಸಾಲುಗಳು[i].text = X11Toolkit_MakeTextElements(base_control->window, (ವರ್ಣ *)utf8, sz, &control->ಸಾಲುಗಳು[i].par);
#ಅನ್ಯಥಾ 
        control->ಸಾಲುಗಳು[i].text = X11Toolkit_MakeTextElements(base_control->window, (ವರ್ಣ *)utf8, sz);
#endif
        X11Toolkit_ShapeTextElements(base_control->window, control->ಸಾಲುಗಳು[i].text);

        utf8 += length + 1;
        ಯದಿ (!lf) {
            ಭಙ್ಗ;
        }
    }

    base_control->do_size = true;
    X11Toolkit_CalculateLabelControl(base_control);
    base_control->do_size = false;
    X11Toolkit_AddControlToWindow(window, base_control);

    ಪ್ರತ್ಯಾಗಮ base_control;
}

ಪೂರ್ಣಾಙ್ಕ X11_Toolkit_Get_Label_Control_First_ಸಾಲು_Height(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    ಪ್ರತ್ಯಾಗಮ label_control->ಸಾಲುಗಳು[0].rect.h;
}

ಶೂನ್ಯ X11Toolkit_SignalWindowClose(SDL_ToolkitWindowX11 *data) {
    data->close = true;
}

#endif // SDL_VIDEO_DRIVER_X11
