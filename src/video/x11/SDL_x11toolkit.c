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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश "../../SDL_list.h"
#समावेश "SDL_x11video.h"
#अगर_घोषित SDL_USE_LIBDBUS
#समावेश "../../core/linux/SDL_system_theme.h"
#पूर्ण_अगर
#अगर_घोषित HAVE_FRIBIDI_H
#समावेश "../../core/unix/SDL_fribidi.h"
#पूर्ण_अगर
#समावेश "SDL_x11dyn.h"
#समावेश "SDL_x11toolkit.h"
#समावेश "SDL_x11settings.h"
#समावेश "SDL_x11modes.h"
#समावेश "xsettings-client.h"
#समावेश <X11/keysym.h>
#समावेश <locale.h>

#घोषणा SDL_SET_LOCALE 1
#घोषणा SDL_GRAB 1

प्रकार क्रमागत SDL_ToolkitTextTypeX11
{
    SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC,
    SDL_TOOLKIT_TEXT_TYPE_X11_THAI
} SDL_ToolkitTextTypeX11;

#अगर_घोषित HAVE_LIBTHAI_H
प्रकार काष्ठा SDL_ToolkitThaiOverlayX11
{
    bool शीर्ष;
    अक्षर *str;
    माप_प्रकार sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#पूर्ण_अगर

प्रकार काष्ठा SDL_ToolkitTextElementX11
{
    SDL_ToolkitTextTypeX11 type;
    अक्षर *str;
    माप_प्रकार sz;
    SDL_Rect rect;
    पूर्णांक font_h;
    व्योम (*str_free)(व्योम *);
#अगर_घोषित HAVE_LIBTHAI_H
    SDL_List_गाँठ *thai_overlays;
#पूर्ण_अगर
} SDL_ToolkitTextElementX11;

प्रकार काष्ठा SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Icon type */
    SDL_MessageBoxFlags flags;
    अक्षर icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    पूर्णांक icon_char_x;
    पूर्णांक icon_char_y;
    पूर्णांक icon_char_a;
    पूर्णांक icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

प्रकार काष्ठा SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 parent;

    /*तथ्य*/
    स्थिर SDL_Message_Box_Button_तथ्य *तथ्य;

    /* Text */
    SDL_List_गाँठ *text;
    SDL_Rect text_rect;
    
    /* Callback */
    व्योम *cb_तथ्य;
    व्योम (*cb)(काष्ठा SDL_ToolkitControlX11 *, व्योम *);
} SDL_ToolkitButtonControlX11;

प्रकार काष्ठा SDL_Toolkit_Label_Control_पंक्ति_X11
{
    SDL_List_गाँठ *text;
    SDL_Rect rect;
#अगर_घोषित HAVE_FRIBIDI_H
    FriBidiParType par;
#पूर्ण_अगर
} SDL_Toolkit_Label_Control_पंक्ति_X11;

प्रकार काष्ठा SDL_ToolkitLabelControlX11
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

प्रकार काष्ठा SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_गाँठ *menu_वस्तुएँ;
} SDL_ToolkitMenuBarControlX11;

प्रकार काष्ठा SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_गाँठ *menu_वस्तुएँ;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
अटल स्थिर अक्षर *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#घोषणा G_ICONFONT_आकार 22

/* General UI font */
अटल स्थिर अक्षर g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
अटल स्थिर अक्षर g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

अटल स्थिर अक्षर *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    शून्य
};
#घोषणा G_TOOLKITFONT_आकार 140

अटल स्थिर SDL_MessageBoxColor g_default_colors[SDL_MESSAGEBOX_COLOR_गिनती] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#अगर_घोषित SDL_USE_LIBDBUS
अटल स्थिर SDL_MessageBoxColor g_default_colors_dark[SDL_MESSAGEBOX_COLOR_गिनती] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#अगर 0
अटल स्थिर SDL_MessageBoxColor g_default_colors_dark_ऊपरी_contrast[SDL_MESSAGEBOX_COLOR_गिनती] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

अटल स्थिर SDL_MessageBoxColor g_default_colors_light_ऊपरी_contrast[SDL_MESSAGEBOX_COLOR_गिनती] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#पूर्ण_अगर

#पूर्ण_अगर

अटल पूर्णांक g_shm_error;
अटल पूर्णांक (*g_old_error_handler)(Display *, XErrorEvent *) = शून्य;

अटल पूर्णांक X11Toolkit_SharedMemoryErrorHandler(Display *d, XErrorEvent *e)
{
    अगर (e->error_code == BadAccess || e->error_code == BadRequest) {
        g_shm_error = True;
        वापस 0;
    }
    वापस g_old_error_handler(d, e);
}

अटल व्योम X11Toolkit_InitWindowPixmap(SDL_ToolkitWindowX11 *तथ्य) {
    अगर (तथ्य->pixmap) {
#अगर_अघोषित NO_SHARED_MEMORY
        अगर (!तथ्य->shm_pixmap) {
            तथ्य->drawable = X11_XCreatePixmap(तथ्य->display, तथ्य->window, तथ्य->pixmap_width, तथ्य->pixmap_height, तथ्य->depth);
        }
#अन्यथा
        तथ्य->drawable = X11_XCreatePixmap(तथ्य->display, तथ्य->window, तथ्य->pixmap_width, तथ्य->pixmap_height, तथ्य->depth);
#पूर्ण_अगर
#अगर_अघोषित NO_SHARED_MEMORY
        अगर (तथ्य->shm) {
            तथ्य->image = X11_XShmCreateImage(तथ्य->display, तथ्य->visual, तथ्य->depth, ZPixmap, शून्य, &तथ्य->shm_info, तथ्य->pixmap_width, तथ्य->pixmap_height);
            अगर (तथ्य->image) {
                तथ्य->shm_bytes_per_पंक्ति = तथ्य->image->bytes_per_पंक्ति;

                तथ्य->shm_info.shmid = shmget(IPC_PRIVATE, तथ्य->image->bytes_per_पंक्ति * तथ्य->image->height, IPC_CREAT | 0777);
                अगर (तथ्य->shm_info.shmid < 0) {
                    XDestroyImage(तथ्य->image);
                    तथ्य->image = शून्य;
                    तथ्य->shm = false;
                    वापस;
                }

                तथ्य->shm_info.readOnly = False;
                तथ्य->shm_info.shmaddr = तथ्य->image->तथ्य = (अक्षर *)shmat(तथ्य->shm_info.shmid, शून्य, 0);
                अगर (((चिन्हित अक्षर *)तथ्य->shm_info.shmaddr) == (चिन्हित अक्षर *)-1) {
                    XDestroyImage(तथ्य->image);
                    तथ्य->shm = false;
                    तथ्य->image = शून्य;
                    वापस;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11Toolkit_SharedMemoryErrorHandler);
                X11_XShmAttach(तथ्य->display, &तथ्य->shm_info);
                X11_XSync(तथ्य->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                अगर (g_shm_error) {
                    XDestroyImage(तथ्य->image);
                    shmdt(तथ्य->shm_info.shmaddr);
                    shmctl(तथ्य->shm_info.shmid, IPC_RMID, शून्य);
                    तथ्य->image = शून्य;
                    तथ्य->shm = false;
                    वापस;
                }

                अगर (तथ्य->shm_pixmap) {
                    तथ्य->drawable = X11_XShmCreatePixmap(तथ्य->display, तथ्य->window, तथ्य->shm_info.shmaddr, &तथ्य->shm_info, तथ्य->pixmap_width, तथ्य->pixmap_height, तथ्य->depth);
                    अगर (तथ्य->drawable == None) {
                        तथ्य->shm_pixmap = False;
                    } अन्यथा {
                        XDestroyImage(तथ्य->image);
                        तथ्य->image = शून्य;
                    }
                }

                shmctl(तथ्य->shm_info.shmid, IPC_RMID, शून्य);
            } अन्यथा {
                तथ्य->shm = false;
            }
        }
#पूर्ण_अगर
    }
}

अटल व्योम X11Toolkit_InitWindowFonts(SDL_ToolkitWindowX11 *window)
{    
    window->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    window->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#अगर_घोषित X_HAVE_UTF8_STRING
    window->utf8 = true;
    window->font_set = शून्य;
    अगर (SDL_X11_HAVE_UTF8) {
        अक्षर **missing = शून्य;
        पूर्णांक अंक_missing = 0;
        पूर्णांक i_font;
        window->font_struct = शून्य;
        क्रम (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            अक्षर *font;

            अगर (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_load_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_आकार * window->iscale);
                window->font_set = X11_XCreateFontSet(window->display, font, &missing, &अंक_missing, शून्य);
                SDL_free(font);

                अगर (!window->font_set) {
                    अगर (window->scale != 0 && window->iscale > 0) {
                        window->iscale = (पूर्णांक)SDL_ceilf(window->scale);
                        window->scale = 0;
                    } अन्यथा {
                        window->iscale--;
                    }
                    जाओ try_load_font;
                }
            } अन्यथा {
                window->font_set = X11_XCreateFontSet(window->display, g_ToolkitFont[i_font], &missing, &अंक_missing, शून्य);
            }

            अगर (missing) {
                X11_XFreeStringList(missing);
            }

            अगर (window->font_set) {
                अवरोध;
            }
        }

        अगर (!window->font_set) {
            जाओ load_font_traditional;
        } अन्यथा {
            XFontStruct **font_structs;
            अक्षर **font_names;
            पूर्णांक font_sz;
            पूर्णांक i;
            
#अगर_घोषित HAVE_FRIBIDI_H
            window->do_shaping = !X11_XContextDependentDrawing(window->font_set);
#पूर्ण_अगर
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFontsOfFontSet(window->font_set, &font_structs, &font_names);
            क्रम (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                अगर (SDL_strstr(font_names[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } अन्यथा अगर (SDL_strstr(font_names[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } अन्यथा अगर (SDL_strstr(font_names[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } अन्यथा अगर (SDL_strstr(font_names[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } अन्यथा अगर (SDL_strstr(font_names[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                अगर (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(window->display, font_names[i]);
                    अगर (font_struct) {
                        अगर (font_struct->per_char) {
                            पूर्णांक glyphs_sz;
                            पूर्णांक j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            क्रम (j = 0; j < glyphs_sz; j++) {
                                अगर (font_struct->per_char[j].lbearing < 0) {
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
#पूर्ण_अगर
    {
        अक्षर *font;

        load_font_traditional:
        window->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_आकार * window->iscale);
        window->font_struct = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        अगर (!window->font_struct) {
            अगर (window->iscale > 0) {
                अगर (window->scale != 0) {
                    window->iscale = (पूर्णांक)SDL_ceilf(window->scale);
                    window->scale = 0;
                } अन्यथा {
                    window->iscale--;
                }
                जाओ load_font_traditional;
            } अन्यथा {
                window->font_struct = X11_XLoadQueryFont(window->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

अटल व्योम X11Toolkit_SettingsNotify(स्थिर अक्षर *name, XSettingsAction action, XSettingsSetting *setting, व्योम *तथ्य)
{
    SDL_ToolkitWindowX11 *window;
    पूर्णांक i;

    window = तथ्य;

    अगर (window->xsettings_first_time) {
        वापस;
    }

    अगर (SDL_strcmp(name, SDL_XSETTINGS_GDK_WINDOW_SCALING_FACTOR) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_setup = false;
        bool pixmap_already_setup = false;

        अगर (window->pixmap) {
            pixmap_already_setup = true;
        } अन्यथा {
            dbe_already_setup = true;
        }

        /* set scale vars */
        window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
        window->iscale = (पूर्णांक)SDL_ceilf(window->scale);
        अगर (window->scale < 1) {
            window->scale = 1;
        }
        अगर (SDL_roundf(window->scale) == window->scale) {
            window->scale = 0;
        }

        /* setup fonts */
#अगर_घोषित X_HAVE_UTF8_STRING
        अगर (window->font_set) {
            X11_XFreeFontSet(window->display, window->font_set);
        }
#पूर्ण_अगर
        अगर (window->font_struct) {
            X11_XFreeFont(window->display, window->font_struct);
        }

        X11Toolkit_InitWindowFonts(window);

        /* set up window */
        अगर (window->scale != 0) {
            window->window_width = SDL_lroundf((window->window_width/window->iscale) * window->scale);
            window->window_height = SDL_lroundf((window->window_height/window->iscale) * window->scale);
            window->pixmap_width = window->window_width;
            window->pixmap_height = window->window_height;
            window->pixmap = true;
        } अन्यथा {
            window->pixmap = false;
        }

        अगर (window->pixmap) {
            अगर (!pixmap_already_setup) {
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XDBE
                अगर (SDL_X11_HAVE_XDBE && window->xdbe) {
                    X11_Xdbe_Deallocate_Back_बफर_Name(window->display, window->buf);
                }
#पूर्ण_अगर
            }
            X11_XFreePixmap(window->display, window->drawable);
            X11Toolkit_InitWindowPixmap(window);
        } अन्यथा {
            अगर (!dbe_already_setup) {
                X11_XFreePixmap(window->display, window->drawable);
#अगर_अघोषित NO_SHARED_MEMORY
                अगर (window->image) {
                    XDestroyImage(window->image);
                    window->image = शून्य;
                }
#पूर्ण_अगर
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XDBE
                अगर (SDL_X11_HAVE_XDBE && window->xdbe) {
                    window->buf = X11_Xdbe_Allocate_Back_बफर_Name(window->display, window->window, XdbeUndefined);
                    window->drawable = window->buf;
                }
#पूर्ण_अगर
            }
        }

        /* notify controls */
        क्रम (i = 0; i < window->controls_sz; i++) {
            window->controls[i]->do_आकार = true;

            अगर (window->controls[i]->func_on_scale_change) {
                window->controls[i]->func_on_scale_change(window->controls[i]);
            }

            अगर (window->controls[i]->func_calc_आकार) {
                window->controls[i]->func_calc_आकार(window->controls[i]);
            }

            window->controls[i]->do_आकार = false;
        }

        /* notify cb */
        अगर (window->cb_on_scale_change) {
            window->cb_on_scale_change(window, window->cb_तथ्य);
        }

        /* update ev scales */
        अगर (!window->pixmap) {
            window->ev_scale = window->ev_iscale = 1;
        } अन्यथा {
            window->ev_scale = window->scale;
            window->ev_iscale = window->iscale;
        }
    }
}

अटल व्योम X11Toolkit_GetTextWidthHeightForFont(XFontStruct *font, स्थिर अक्षर *str, पूर्णांक nbytes, पूर्णांक *pwidth, पूर्णांक *pheight, पूर्णांक *ascent, पूर्णांक *font_height)
{
    XCharStruct text_structure;
    पूर्णांक font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &text_structure);
    *pwidth = text_structure.width;
    *pheight = text_structure.ascent + text_structure.descent;
    *ascent = text_structure.ascent;
    अगर (font_height) {
       *font_height = font_ascent + font_descent;
    }
}

अटल व्योम X11Toolkit_GetTextWidthHeight(SDL_ToolkitWindowX11 *तथ्य, स्थिर अक्षर *str, पूर्णांक nbytes, पूर्णांक *pwidth, पूर्णांक *pheight, पूर्णांक *ascent, पूर्णांक *descent, पूर्णांक *font_height)
{
#अगर_घोषित X_HAVE_UTF8_STRING
    अगर (तथ्य->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8TextExtents(तथ्य->font_set, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.width;
        *pheight = overall_logical.height;
        *ascent = -overall_logical.y;
        *descent = overall_logical.height - *ascent;

        अगर (font_height) {
            XFontSetExtents *extents;

            extents = X11_XExtentsOfFontSet(तथ्य->font_set);
            *font_height = extents->max_logical_extent.height;
        }
    } अन्यथा
#पूर्ण_अगर
    {
        XCharStruct text_structure;
        पूर्णांक font_direction, font_ascent, font_descent;
        X11_XTextExtents(तथ्य->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &text_structure);
        *pwidth = text_structure.width;
        *pheight = text_structure.ascent + text_structure.descent;
        *ascent = text_structure.ascent;
        *descent = text_structure.descent;

        अगर (font_height) {
            *font_height = font_ascent + font_descent;
        }
    }
}

#अगर_घोषित HAVE_FRIBIDI_H
SDL_List_गाँठ *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *तथ्य, अक्षर *txt, माप_प्रकार sz, FriBidiParType *par)
#अन्यथा
SDL_List_गाँठ *X11Toolkit_MakeTextElements(SDL_ToolkitWindowX11 *तथ्य, अक्षर *txt, माप_प्रकार sz)
#पूर्ण_अगर
{
    SDL_List_गाँठ *list;
    अक्षर *str;
    अक्षर *बफर_2;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = शून्य;
    thai = 0;
    str = txt;
    बफर_2 = SDL_malloc(1);
    बफर_2[0] = 0;
    
#अगर_घोषित HAVE_FRIBIDI_H
    अगर (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    अगर (तथ्य->fribidi) {
        अक्षर *fstr;
                
        fstr = SDL_FriBidi_Process(तथ्य->fribidi, str, sz, तथ्य->do_shaping, par);
        अगर (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#पूर्ण_अगर        

    जबतक (1) {
        अक्षर *new;
        अक्षर utf8[5];
        माप_प्रकार csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_StepUTF8((स्थिर अक्षर **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        अगर (cp == 0 || cond == (thai ? false : true)) {
            SDL_ToolkitTextElementX11 *element;
            
            element = SDL_malloc(माप(SDL_ToolkitTextElementX11));
            अगर (thai) {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_THAI;
            } अन्यथा {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC;
            }
            element->str = SDL_strdup(बफर_2);
            element->sz = SDL_strlen(बफर_2);
            element->str_free = SDL_free;
            
            SDL_ListAdd(&list, element);
            
            SDL_free(बफर_2);
            बफर_2 = SDL_malloc(1);
            बफर_2[0] = 0;
            thai = thai ? false : true;
        }

        अगर (!cp) {
            अवरोध;
        }
        
        SDL_UCS4ToUTF8(cp, utf8);
        csz = SDL_strlen(बफर_2) + SDL_strlen(utf8) + 1;
        new = SDL_malloc(csz);
        SDL_strlcpy(new, बफर_2, csz);
        SDL_strlcat(new, utf8, csz);
        SDL_free(बफर_2);
        बफर_2 = new;
    }

    SDL_free(बफर_2);
    अगर (free_txt) {
        SDL_free(txt);
    }
    वापस list;
}

व्योम X11Toolkit_ShapeTextElements(SDL_ToolkitWindowX11 *तथ्य, SDL_List_गाँठ *list)
{
    SDL_List_गाँठ *cursor;
    SDL_ToolkitTextElementX11 *पूर्व;
    पूर्णांक अस्थायी;
    
    /* Shape and calculate bounding box */
    cursor = list;
    जबतक (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
#अगर_घोषित HAVE_LIBTHAI_H
        element->thai_overlays = शून्य;
#पूर्ण_अगर
        अगर (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            अगर (तथ्य->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
                X11Toolkit_GetTextWidthHeight(तथ्य, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &अस्थायी, शून्य);
            } अन्यथा {
#अगर_घोषित HAVE_LIBTHAI_H
                अगर (तथ्य->th) {
                    काष्ठा thcell_t *cells;
                    अक्षर *tis_str;
                    अक्षर *base_tis_str;
                    माप_प्रकार cells_sz;
                    माप_प्रकार base_tis_str_sz;
                    माप_प्रकार tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, माप(काष्ठा thcell_t));
                    तथ्य->th->make_cells((स्थिर thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    base_tis_str_sz = cells_sz;
                    base_tis_str = SDL_malloc(base_tis_str_sz + 1);
                    क्रम (अस्थायी = 0; अस्थायी < cells_sz; अस्थायी++) {
                        base_tis_str[अस्थायी] = cells[अस्थायी].base;
                        
                        अगर (cells[अस्थायी].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            अक्षर *pre;
                            पूर्णांक temp2;
                            
                            overlay = SDL_malloc(माप(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, अस्थायी);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (स्थिर अक्षर *)&cells[अस्थायी].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->शीर्ष = false;
                            X11Toolkit_GetTextWidthHeight(तथ्य, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, शून्य);
                            X11Toolkit_GetTextWidthHeight(तथ्य, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, शून्य);
                            SDL_ListAdd(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        अगर (cells[अस्थायी].शीर्ष) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            अक्षर *pre;
                            पूर्णांक temp2;
                            
                            overlay = SDL_malloc(माप(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, अस्थायी);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (स्थिर अक्षर *)&cells[अस्थायी].शीर्ष, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->शीर्ष = true;
                            X11Toolkit_GetTextWidthHeight(तथ्य, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, शून्य);
                            X11Toolkit_GetTextWidthHeight(तथ्य, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, शून्य);
                            SDL_ListAdd(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    base_tis_str[base_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", base_tis_str, base_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11Toolkit_GetTextWidthHeight(तथ्य, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &अस्थायी, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(base_tis_str);
                }
#अन्यथा
                X11Toolkit_GetTextWidthHeight(तथ्य, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &अस्थायी, &element->font_h);
#पूर्ण_अगर            
            }
        } अन्यथा {
            X11Toolkit_GetTextWidthHeight(तथ्य, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &अस्थायी, &element->font_h);
        }
        
        cursor = cursor->अग्र;
    }
    
    /* Add offsets */
    पूर्व = शून्य;
    cursor = list;
    जबतक (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;        
        अगर (पूर्व) {
            element->rect.x = पूर्व->rect.x + पूर्व->rect.w;
        } अन्यथा {
            element->rect.x = 0;
        }
        
        पूर्व = element;
        cursor = cursor->अग्र;
    }
}


व्योम X11Toolkit_DrawTextElements(SDL_ToolkitWindowX11 *तथ्य, SDL_List_गाँठ *list, पूर्णांक x, पूर्णांक y)
{
    SDL_List_गाँठ *cursor;
    
    cursor = list;
    
    जबतक (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        अगर (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            अगर (तथ्य->thai_font == SDL_TOOLKIT_THAI_FONT_X11_OFFSET) {
#अगर_घोषित X_HAVE_UTF8_STRING
                अगर (तथ्य->utf8) {
                    X11_Xutf8DrawString(तथ्य->display, तथ्य->drawable, तथ्य->font_set, तथ्य->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } अन्यथा
#पूर्ण_अगर
                {
                    X11_XDrawString(तथ्य->display, तथ्य->drawable, तथ्य->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } अन्यथा {    
#अगर_घोषित HAVE_LIBTHAI_H
                SDL_List_गाँठ *overlay_cursor;
                    
                /* Draw the base string */
#अगर_घोषित X_HAVE_UTF8_STRING
                अगर (तथ्य->utf8) {
                    X11_Xutf8DrawString(तथ्य->display, तथ्य->drawable, तथ्य->font_set, तथ्य->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } अन्यथा
#पूर्ण_अगर
                {
                    X11_XDrawString(तथ्य->display, तथ्य->drawable, तथ्य->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                जबतक (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->entry;
#अगर_घोषित X_HAVE_UTF8_STRING
                    अगर (तथ्य->utf8) {
                        X11_Xutf8DrawString(तथ्य->display, तथ्य->drawable, तथ्य->font_set, तथ्य->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } अन्यथा
#पूर्ण_अगर
                    {
                        X11_XDrawString(तथ्य->display, तथ्य->drawable, तथ्य->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->अग्र;
                }
#पूर्ण_अगर                
            }
        } अन्यथा {
#अगर_घोषित X_HAVE_UTF8_STRING
            अगर (तथ्य->utf8) {
                X11_Xutf8DrawString(तथ्य->display, तथ्य->drawable, तथ्य->font_set, तथ्य->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } अन्यथा
#पूर्ण_अगर
            {
                X11_XDrawString(तथ्य->display, तथ्य->drawable, तथ्य->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->अग्र;
    }
}

पूर्णांक X11Toolkit_GetTextElementsRect(SDL_List_गाँठ *list, SDL_Rect *out)
{
    SDL_List_गाँठ *cursor;
    पूर्णांक ret;
    
    ret = 0;
    out->x = out->y = 0;
    out->w = out->h = 0;
    cursor = list;
    जबतक (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->entry;
        
        out->w += element->rect.w;
        out->h = SDL_max(out->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->अग्र;
    }
    
    वापस ret;
}

व्योम X11Toolkit_FreeTextElementsListContents(SDL_List_गाँठ *list)
{
    SDL_List_गाँठ *cursor;
    
    cursor = list;
    जबतक (cursor) {
        SDL_ToolkitTextElementX11 *element;
#अगर_घोषित HAVE_LIBTHAI_H
        SDL_List_गाँठ *overlay_cursor;
#पूर्ण_अगर

        element = cursor->entry;
        
        अगर (element->str_free) {
            element->str_free(element->str);
        }
        
#अगर_घोषित HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        जबतक (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->entry;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->अग्र;
        }
        SDL_ListClear(&element->thai_overlays);
#पूर्ण_अगर
        
        SDL_free(element);
        
        cursor = cursor->अग्र;
    }
}

#घोषणा X11Toolkit_FreeTextElements(x) X11Toolkit_FreeTextElementsListContents(x); SDL_ListClear(&x)
 
अटल bool X11Toolkit_ShouldFlipUI(व्योम) 
{
    SDL_Locale **current_locales;
    अटल स्थिर SDL_Locale rtl_locales[] = {
        { "ar", शून्य, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", शून्य, },
        { "iw", शून्य, },
        { "yi", शून्य, },
        { "ur", शून्य, },
        { "ug", शून्य, },
        { "kd", शून्य, },
        { "pk", "PK", },
        { "ps", शून्य, }
    }; 
    पूर्णांक current_locales_sz;
    पूर्णांक i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    अगर (current_locales_sz <= 0) {
        वापस false;        
    }
    क्रम (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        अगर (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            अगर (!rtl_locales[i].country) {
                वापस true;
            } अन्यथा {
                वापस SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    वापस false;
}

SDL_ToolkitWindowX11 *X11Toolkit_CreateWindowStruct(SDL_Window *parent, SDL_ToolkitWindowX11 *tkparent, SDL_ToolkitWindowModeX11 mode, स्थिर SDL_MessageBoxColor *colorhints, bool create_new_display)
{
    SDL_ToolkitWindowX11 *window;
    पूर्णांक i;
#अगर_घोषित SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#पूर्ण_अगर
    #घोषणा ErrorFreeRetNull(x, y) SDL_SetError(x); SDL_free(y); वापस शून्य
    #घोषणा ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_SetError(x, y); SDL_free(z); वापस शून्य

    अगर (!SDL_X11_LoadSymbols()) {
        वापस शून्य;
    }

    // This code could get called from multiple threads maybe?
    X11_XInitThreads();

    window = (SDL_ToolkitWindowX11 *)SDL_malloc(माप(SDL_ToolkitWindowX11));
    अगर (!window) {
        SDL_SetError("Unable to allocate toolkit window structure");
        वापस शून्य;
    }

    window->mode = mode;
    window->tk_parent = tkparent;

#अगर SDL_SET_LOCALE
    अगर (mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        window->origlocale = रखो_क्षेत्र(LC_ALL, शून्य);
        अगर (window->origlocale) {
            window->origlocale = SDL_strdup(window->origlocale);
            अगर (!window->origlocale) {
                SDL_free(window);
                वापस शून्य;
            }
            (व्योम)रखो_क्षेत्र(LC_ALL, "");
        }
    }
#पूर्ण_अगर

    window->parent_device = शून्य;
    अगर (create_new_display) {
        window->display = X11_XOpenDisplay(शून्य);
        window->display_close = true;
        अगर (!window->display) {
            ErrorFreeRetNull("Couldn't open X11 display", window);
        }
    } अन्यथा {
        अगर (parent) {
            window->parent_device = SDL_GetVideoDevice();
            window->display = window->parent_device->internal->display;
            window->display_close = false;
        } अन्यथा अगर (tkparent) {
            window->display = tkparent->display;
            window->display_close = false;
        } अन्यथा {
            window->display = X11_XOpenDisplay(शून्य);
            window->display_close = true;
            अगर (!window->display) {
                ErrorFreeRetNull("Couldn't open X11 display", window);
            }
        }
    }

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
    पूर्णांक xrandr_event_base, xrandr_error_base;
    window->xrandr = X11_XRRQueryExtension(window->display, &xrandr_event_base, &xrandr_error_base);
#पूर्ण_अगर

#अगर_अघोषित NO_SHARED_MEMORY
    window->shm_pixmap = False;
    window->shm = X11_XShmQueryExtension(window->display) ? SDL_X11_HAVE_SHM : false;
    अगर (window->shm) {
        पूर्णांक major;
        पूर्णांक minor;

        X11_XShmQueryVersion(window->display, &major, &minor, &window->shm_pixmap);
        अगर (window->shm_pixmap) {
            अगर (X11_XShmPixmapFormat(window->display) != ZPixmap) {
                window->shm_pixmap = False;
            }
        }
    }
#पूर्ण_अगर

    /* Scale/Xsettings */
    window->pixmap = false;
    window->xsettings_first_time = true;
    window->xsettings = xsettings_client_new(window->display, DefaultScreen(window->display), X11Toolkit_SettingsNotify, शून्य, window);
    window->xsettings_first_time = false;
    window->scale = X11_GetGlobalContentScale(window->display, window->xsettings);
    अगर (window->scale < 1) {
        window->scale = 1;
    }
    window->iscale = (पूर्णांक)SDL_ceilf(window->scale);
    अगर (SDL_roundf(window->scale) == window->scale) {
        window->scale = 0;
    }

    /* Fonts */
    X11Toolkit_InitWindowFonts(window);

    /* Color hints */
#अगर_घोषित SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    अगर (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#पूर्ण_अगर

    अगर (!colorhints) {
#अगर_घोषित SDL_USE_LIBDBUS
        चयन (theme) {
            हाल SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                अवरोध;
#अगर 0
            हाल SDL_SYSTEM_THEME_LIGHT_ऊपरी_CONTRAST:
                colorhints = g_default_colors_light_ऊपरी_contrast;
                अवरोध;
            हाल SDL_SYSTEM_THEME_DARK_ऊपरी_CONTRAST:
                colorhints = g_default_colors_dark_ऊपरी_contrast;
                अवरोध;
#पूर्ण_अगर
            शेष:
                colorhints = g_default_colors;
        }
#अन्यथा
        colorhints = g_default_colors;
#पूर्ण_अगर
    }
    window->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    क्रम (i = 0; i < SDL_MESSAGEBOX_COLOR_गिनती; i++) {
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
    अगर (parent) {
        SDL_Display_तथ्य *displaydata = SDL_Get_Display_Driver_तथ्य_For_Window(parent);
        window->screen = displaydata->screen;
    } अन्यथा {
        window->screen = DefaultScreen(window->display);
    }

    /* Visuals */
    अगर (mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
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
    क्रम (i = 0; i < SDL_MESSAGEBOX_COLOR_गिनती; i++) {
        X11_XAllocColor(window->display, window->cmap, &window->xcolor[i]);
    }
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l1);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_l2);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_bevel_d);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_pressed);
    X11_XAllocColor(window->display, window->cmap, &window->xcolor_disabled_text);

    /* Control list */
    window->has_focus = false;
    window->controls = शून्य;
    window->controls_sz = 0;
    window->dyn_controls_sz = 0;
    window->fiddled_control = शून्य;
    window->dyn_controls = शून्य;

    /* Menu windows */
    window->popup_windows = शून्य;

    /* BIDI engine */
#अगर_घोषित HAVE_FRIBIDI_H
    window->fribidi = SDL_FriBidi_Create();
#पूर्ण_अगर

#अगर_घोषित HAVE_LIBTHAI_H
    window->th = SDL_LibThai_Create();
#पूर्ण_अगर
    
    /* Interface direction */
    window->flip_interface = X11Toolkit_ShouldFlipUI();
    
    वापस window;
}

अटल व्योम X11Toolkit_AddControlToWindow(SDL_ToolkitWindowX11 *window, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    window->controls_sz++;
    अगर (window->controls_sz == 1) {
        window->controls = (काष्ठा SDL_ToolkitControlX11 **)SDL_malloc(माप(काष्ठा SDL_ToolkitControlX11 *));
    } अन्यथा {
        window->controls = (काष्ठा SDL_ToolkitControlX11 **)SDL_realloc(window->controls, माप(काष्ठा SDL_ToolkitControlX11 *) * window->controls_sz);
    }
    window->controls[window->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    अगर (control->dynamic) {
        window->dyn_controls_sz++;
        अगर (window->dyn_controls_sz == 1) {
            window->dyn_controls = (काष्ठा SDL_ToolkitControlX11 **)SDL_malloc(माप(काष्ठा SDL_ToolkitControlX11 *));
        } अन्यथा {
            window->dyn_controls = (काष्ठा SDL_ToolkitControlX11 **)SDL_realloc(window->dyn_controls, माप(काष्ठा SDL_ToolkitControlX11 *) * window->dyn_controls_sz);
        }
        window->dyn_controls[window->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    अगर (control->selected) {
        window->focused_control = control;
    }
}

bool X11Toolkit_CreateWindowRes(SDL_ToolkitWindowX11 *तथ्य, पूर्णांक w, पूर्णांक h, पूर्णांक cx, पूर्णांक cy, अक्षर *title)
{
    पूर्णांक x, y;
    XSizeHints *sizehints;
    XSetWindowAttributes wnd_attr;
    Atom _NET_WM_WINDOW_TYPE, _NET_WM_WINDOW_TYPE_DIALOG, _NET_WM_WINDOW_TYPE_DROPDOWN_MENU, _NET_WM_WINDOW_TYPE_TOOLTIP;
    SDL_Window_तथ्य *windowdata = शून्य;
    Display *display = तथ्य->display;
    XGCValues ctx_vals;
    Window मूल_win;
    Window parent_win;
    अचिन्हित दीर्घ gcflags = GCForeground | GCBackground;
    अचिन्हित दीर्घ valuemask;
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
#अगर_घोषित XRANDR_DISABLED_BY_DEFAULT
    स्थिर bool use_xrandr_by_default = false;
#अन्यथा
    स्थिर bool use_xrandr_by_default = true;
#पूर्ण_अगर
#पूर्ण_अगर

    अगर (तथ्य->scale == 0) {
        तथ्य->window_width = w;
        तथ्य->window_height = h;
    } अन्यथा {
        तथ्य->window_width = SDL_lroundf((w/तथ्य->iscale) * तथ्य->scale);
        तथ्य->window_height = SDL_lroundf((h/तथ्य->iscale) * तथ्य->scale);
        तथ्य->pixmap_width = w;
        तथ्य->pixmap_height = h;
        तथ्य->pixmap = true;
    }

    अगर (तथ्य->parent) {
        windowdata = तथ्य->parent->internal;
    }

    valuemask = CWEventMask | CWColormap;
    तथ्य->event_mask = ExposureMask |
                       ButtonPressMask | ButtonReleaseMask | कुंजी_Press_Mask | कुंजी_Release_Mask |
                       StructureNotifyMask | FocusChangeMask | PointerMotionMask;
    wnd_attr.event_mask = तथ्य->event_mask;
    wnd_attr.colormap = तथ्य->cmap;
    अगर (तथ्य->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || तथ्य->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    मूल_win = मूल_Window(display, तथ्य->screen);
    अगर (तथ्य->mode == SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        parent_win = windowdata->xwindow;
    } अन्यथा {
        parent_win = मूल_win;
    }

    तथ्य->window = X11_XCreateWindow(
        display, parent_win,
        0, 0,
        तथ्य->window_width, तथ्य->window_height,
        0, तथ्य->depth, निवेश_Output, तथ्य->visual,
        valuemask, &wnd_attr);
    अगर (तथ्य->window == None) {
        वापस SDL_SetError("Couldn't create X window");
    }

    अगर (windowdata && तथ्य->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
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
        X11_XChangeProperty(display, तथ्य->window, _NET_WM_STATE, XA_ATOM, 32,
                            PropModeReplace, (अचिन्हित अक्षर *)stateatoms, statecount);
    }

    अगर (windowdata && तथ्य->mode != SDL_TOOLKIT_WINDOW_MODE_X11_CHILD) {
        X11_XSetTransientForHint(display, तथ्य->window, windowdata->xwindow);
    }

    अगर (तथ्य->tk_parent) {
        X11_XSetTransientForHint(display, तथ्य->window, तथ्य->tk_parent->window);
    }

    SDL_X11_SetWindowTitle(display, तथ्य->window, title);

    // Let the window manager the type of the window
    अगर (तथ्य->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, तथ्य->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (अचिन्हित अक्षर *)&_NET_WM_WINDOW_TYPE_DIALOG, 1);
    } अन्यथा अगर (तथ्य->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, तथ्य->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (अचिन्हित अक्षर *)&_NET_WM_WINDOW_TYPE_DROPDOWN_MENU, 1);
    } अन्यथा अगर (तथ्य->mode == SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        _NET_WM_WINDOW_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        _NET_WM_WINDOW_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, तथ्य->window, _NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                            PropModeReplace,
                            (अचिन्हित अक्षर *)&_NET_WM_WINDOW_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    तथ्य->wm_delete_message = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, तथ्य->window, &तथ्य->wm_delete_message, 1);
    तथ्य->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    अगर (तथ्य->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || तथ्य->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        x = cx;
        y = cy;
        जाओ MOVEWINDOW;
    }
    अगर (windowdata) {
        XWindowAttributes attrib;
        Window dummy;

        X11_XGetWindowAttributes(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.width - तथ्य->window_width) / 2;
        y = attrib.y + (attrib.height - तथ्य->window_height) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, मूल_Window(display, तथ्य->screen), x, y, &x, &y, &dummy);
    } अन्यथा {
        स्थिर SDL_VideoDevice *dev = SDL_GetVideoDevice();
        अगर (dev && dev->displays && dev->अंक_displays > 0) {
            स्थिर SDL_VideoDisplay *dpy = dev->displays[0];
            स्थिर SDL_Display_तथ्य *dpydata = dpy->internal;
            x = dpydata->x + ((dpy->current_mode->w - तथ्य->window_width) / 2);
            y = dpydata->y + ((dpy->current_mode->h - तथ्य->window_height) / 3);
        }
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
        अन्यथा अगर (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && तथ्य->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_out;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, मूल_win);
            अगर (!screen_res) {
                जाओ NOXRANDR;
            }

            default_out = X11_XRRGetOutputPrimary(display, मूल_win);
            अगर (default_out != None) {
                XRROutputInfo *out_info;

                out_info = X11_XRRGetOutputInfo(display, screen_res, default_out);
                अगर (out_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(out_info);
                    जाओ FIRSTOUTPUTXRANDR;
                }

                अगर (out_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                } अन्यथा अगर (out_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                } अन्यथा {
                    crtc_info = शून्य;
                }
                
                अगर (crtc_info) {
                    x = (crtc_info->width - तथ्य->window_width) / 2;
                    y = (crtc_info->height - तथ्य->window_height) / 3;
                    X11_XRRFreeOutputInfo(out_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } अन्यथा {
                    X11_XRRFreeOutputInfo(out_info);
                    जाओ NOXRANDR;
                }
            } अन्यथा {
                    FIRSTOUTPUTXRANDR:
                    अगर (screen_res->noutput > 0) {
                        XRROutputInfo *out_info;

                        out_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        अगर (!out_info) {
                            जाओ FIRSTCRTCXRANDR;
                        }

                        अगर (out_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtc);
                        } अन्यथा अगर (out_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, out_info->crtcs[0]);
                        } अन्यथा {
                            crtc_info = शून्य;
                        }

                        अगर (!crtc_info) {
                            X11_XRRFreeOutputInfo(out_info);
                            जाओ FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->width - तथ्य->window_width) / 2;
                        y = (crtc_info->height - तथ्य->window_height) / 3;
                        X11_XRRFreeOutputInfo(out_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        जाओ MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    अगर (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        जाओ NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    अगर (crtc_info) {
                        x = (crtc_info->width - तथ्य->window_width) / 2;
                        y = (crtc_info->height - तथ्य->window_height) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } अन्यथा {
                        X11_XRRFreeScreenResources(screen_res);
                        जाओ NOXRANDR;
                    }
            }
        }
#पूर्ण_अगर
        अन्यथा {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (DisplayWidth(display, तथ्य->screen) - तथ्य->window_width) / 2;
            y = (DisplayHeight(display, तथ्य->screen) - तथ्य->window_height) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMoveWindow(display, तथ्य->window, x, y);
    तथ्य->window_x = x;
    तथ्य->window_y = y;

    sizehints = X11_XAlloc_आकार_Hints();
    अगर (sizehints) {
        sizehints->flags = USPosition | USSize | PMax_आकार | PMin_आकार;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->width = तथ्य->window_width;
        sizehints->height = तथ्य->window_height;

        sizehints->min_width = sizehints->max_width = तथ्य->window_width;
        sizehints->min_height = sizehints->max_height = तथ्य->window_height;

        X11_XSetWMNormalHints(display, तथ्य->window, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, तथ्य->window);

    तथ्य->drawable = तथ्य->window;
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    अगर (SDL_X11_HAVE_XDBE && !तथ्य->pixmap) {
        पूर्णांक xdbe_major, xdbe_minor;
        अगर (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            तथ्य->xdbe = true;
            तथ्य->buf = X11_Xdbe_Allocate_Back_बफर_Name(display, तथ्य->window, XdbeUndefined);
            तथ्य->drawable = तथ्य->buf;
        } अन्यथा {
            तथ्य->xdbe = false;
        }
    }
#पूर्ण_अगर

    X11Toolkit_InitWindowPixmap(तथ्य);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = तथ्य->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = तथ्य->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    अगर (!तथ्य->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = तथ्य->font_struct->fid;
    }
    तथ्य->ctx = X11_XCreateGC(तथ्य->display, तथ्य->drawable, gcflags, &ctx_vals);
    अगर (तथ्य->ctx == None) {
        वापस SDL_SetError("Couldn't create graphics context");
    }

    तथ्य->बंद = false;
    तथ्य->कुंजी_control_esc = तथ्य->कुंजी_control_enter = शून्य;
    अगर (!तथ्य->pixmap) {
        तथ्य->ev_scale = तथ्य->ev_iscale = 1;
    } अन्यथा {
        तथ्य->ev_scale = तथ्य->scale;
        तथ्य->ev_iscale = तथ्य->iscale;
    }

#अगर SDL_GRAB
    अगर (तथ्य->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || तथ्य->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XGrabPointer(display, तथ्य->window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
        X11_XGrabKeyboard(display, तथ्य->window, False, GrabModeAsync, GrabModeAsync, CurrentTime);
    }
#पूर्ण_अगर

    वापस true;
}

अटल व्योम X11Toolkit_DrawWindow(SDL_ToolkitWindowX11 *तथ्य) {
    SDL_Rect rect;
    पूर्णांक i;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XDBE
    अगर (SDL_X11_HAVE_XDBE && तथ्य->xdbe && !तथ्य->pixmap) {
        X11_XdbeBeginIdiom(तथ्य->display);
    }
#पूर्ण_अगर

    X11_XSetForeground(तथ्य->display, तथ्य->ctx, तथ्य->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    अगर (तथ्य->pixmap) {
        X11_XFillRectangle(तथ्य->display, तथ्य->drawable, तथ्य->ctx, 0, 0, तथ्य->pixmap_width, तथ्य->pixmap_height);
    } अन्यथा {
        X11_XFillRectangle(तथ्य->display, तथ्य->drawable, तथ्य->ctx, 0, 0, तथ्य->window_width, तथ्य->window_height);
    }

    क्रम (i = 0; i < तथ्य->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = तथ्य->controls[i];
        अगर (control) {
            अगर (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XDBE
    अगर (SDL_X11_HAVE_XDBE && तथ्य->xdbe && !तथ्य->pixmap) {
        XdbeSwapInfo swap_info;
        swap_info.swap_window = तथ्य->window;
        swap_info.swap_action = XdbeUndefined;
        X11_XdbeSwapBuffers(तथ्य->display, &swap_info, 1);
        X11_XdbeEndIdiom(तथ्य->display);
    }
#पूर्ण_अगर

    अगर (तथ्य->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = तथ्य->window_width;
        rect.h = तथ्य->window_height;
#अगर_अघोषित NO_SHARED_MEMORY
        अगर (तथ्य->shm) {
            अगर (तथ्य->shm_pixmap) {
                X11_XFlush(तथ्य->display);
                X11_XSync(तथ्य->display, false);
                scale_surface = SDL_CreateSurfaceFrom(तथ्य->pixmap_width, तथ्य->pixmap_height, X11_GetPixelFormatFromVisualInfo(तथ्य->display, &तथ्य->vi), तथ्य->shm_info.shmaddr, तथ्य->shm_bytes_per_पंक्ति);
                SDL_BlitSurfaceScaled(scale_surface, शून्य, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(तथ्य->display, तथ्य->drawable, तथ्य->window, तथ्य->ctx, 0, 0, तथ्य->window_width, तथ्य->window_height, 0, 0);
            } अन्यथा {
                X11_XShmGetImage(तथ्य->display, तथ्य->drawable, तथ्य->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(तथ्य->pixmap_width, तथ्य->pixmap_height, X11_GetPixelFormatFromVisualInfo(तथ्य->display, &तथ्य->vi), तथ्य->image->तथ्य, तथ्य->image->bytes_per_पंक्ति);
                SDL_BlitSurfaceScaled(scale_surface, शून्य, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
                X11_XShmPutImage(तथ्य->display, तथ्य->window, तथ्य->ctx, तथ्य->image, 0, 0, 0, 0, तथ्य->window_width, तथ्य->window_height, False);
            }
        } अन्यथा
#पूर्ण_अगर
        {
            XImage *image;

            image = X11_XGetImage(तथ्य->display, तथ्य->drawable, 0, 0 , तथ्य->pixmap_width, तथ्य->pixmap_height, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(तथ्य->pixmap_width, तथ्य->pixmap_height, X11_GetPixelFormatFromVisualInfo(तथ्य->display, &तथ्य->vi), image->तथ्य, image->bytes_per_पंक्ति);
            SDL_BlitSurfaceScaled(scale_surface, शून्य, scale_surface, &rect, SDL_SCALEMODE_LINEAR);
            X11_XPutImage(तथ्य->display, तथ्य->window, तथ्य->ctx, image, 0, 0, 0, 0, तथ्य->window_width, तथ्य->window_height);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(तथ्य->display);
}

अटल SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_ToolkitWindowX11 *तथ्य, पूर्णांक x, पूर्णांक y)
{
    पूर्णांक i;

    क्रम (i = 0; i < तथ्य->controls_sz; i++) {
        SDL_Rect *rect = &तथ्य->controls[i]->rect;
        अगर ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            वापस तथ्य->controls[i];
        }
    }

    वापस शून्य;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
अटल Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_ToolkitWindowX11 *तथ्य = (SDL_ToolkitWindowX11 *)arg;

    अगर (event->xany.display != तथ्य->display) {
        वापस False;
    }

    अगर (event->xany.window == तथ्य->window) {
        वापस True;
    }

    वापस False;
}

व्योम X11Toolkit_ProcessWindowEvents(SDL_ToolkitWindowX11 *तथ्य, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    अगर ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        वापस;
    }

    तथ्य->draw = false;
    तथ्य->e = e;

    चयन (e->type) {
        हाल Expose:
            तथ्य->draw = true;
            अवरोध;
        हाल ClientMessage:
            अगर (e->xclient.message_type == तथ्य->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.तथ्य.l[0] == तथ्य->wm_delete_message) {
                तथ्य->बंद = true;
            }
            अवरोध;
        हाल FocusIn:
            तथ्य->has_focus = true;
            अवरोध;
        हाल FocusOut:
            तथ्य->has_focus = false;
            अगर (तथ्य->fiddled_control) {
                तथ्य->fiddled_control->selected = false;
            }
            तथ्य->fiddled_control = शून्य;
            क्रम (तथ्य->ev_i = 0; तथ्य->ev_i < तथ्य->controls_sz; तथ्य->ev_i++) {
                तथ्य->controls[तथ्य->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
            }
            अवरोध;
        हाल MotionNotify:
            अगर (तथ्य->has_focus) {
                तथ्य->previous_control = तथ्य->fiddled_control;
                तथ्य->fiddled_control = X11Toolkit_GetControlMouseIsOn(तथ्य, SDL_lroundf((e->xbutton.x/ तथ्य->ev_scale)* तथ्य->ev_iscale), SDL_lroundf((e->xbutton.y/ तथ्य->ev_scale)* तथ्य->ev_iscale));
                अगर (तथ्य->previous_control) {
                    तथ्य->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    अगर (तथ्य->previous_control->func_on_state_change) {
                        तथ्य->previous_control->func_on_state_change(तथ्य->previous_control);
                    }
                    तथ्य->draw = true;
                }
                अगर (तथ्य->fiddled_control) {
                    अगर (तथ्य->fiddled_control->dynamic) {
                        तथ्य->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        अगर (तथ्य->fiddled_control->func_on_state_change) {
                            तथ्य->fiddled_control->func_on_state_change(तथ्य->fiddled_control);
                        }
                        तथ्य->draw = true;
                    } अन्यथा {
                        तथ्य->fiddled_control = शून्य;
                    }
                }
            }
            अवरोध;
        हाल ButtonPress:
            तथ्य->previous_control = तथ्य->fiddled_control;
            अगर (तथ्य->previous_control) {
                तथ्य->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                अगर (तथ्य->previous_control->func_on_state_change) {
                    तथ्य->previous_control->func_on_state_change(तथ्य->previous_control);
                }
                तथ्य->draw = true;
            }
            अगर (e->xbutton.button == Button1) {
                तथ्य->fiddled_control = X11Toolkit_GetControlMouseIsOn(तथ्य, SDL_lroundf((e->xbutton.x/ तथ्य->ev_scale)* तथ्य->ev_iscale), SDL_lroundf((e->xbutton.y/ तथ्य->ev_scale)* तथ्य->ev_iscale));
                अगर (तथ्य->fiddled_control) {
                    तथ्य->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    अगर (तथ्य->fiddled_control->func_on_state_change) {
                        तथ्य->fiddled_control->func_on_state_change(तथ्य->fiddled_control);
                    }
                    तथ्य->draw = true;
                }
            }
            अवरोध;
        हाल ButtonRelease:
            अगर (तथ्य->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || तथ्य->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
                पूर्णांक cx;
                पूर्णांक cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                अगर (cy < 0 || cx < 0) {
                    तथ्य->बंद = true;
                }

                अगर (cy > तथ्य->window_height || cx > तथ्य->window_width) {
                    तथ्य->बंद = true;
                }
            }

            अगर ((e->xbutton.button == Button1) && (तथ्य->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(तथ्य, SDL_lroundf((e->xbutton.x/ तथ्य->ev_scale)* तथ्य->ev_iscale), SDL_lroundf((e->xbutton.y/ तथ्य->ev_scale)* तथ्य->ev_iscale));
                अगर (तथ्य->fiddled_control == control) {
                    तथ्य->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    अगर (तथ्य->fiddled_control->func_on_state_change) {
                        तथ्य->fiddled_control->func_on_state_change(तथ्य->fiddled_control);
                    }
                    तथ्य->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
                    तथ्य->draw = true;
                }
            }
            अवरोध;
        हाल कुंजी_Press:
            तथ्य->last_कुंजी_pressed = X11_XLookupKeysym(&e->xkey, 0);

            अगर (तथ्य->last_कुंजी_pressed == XK_Escape) {
                क्रम (तथ्य->ev_i = 0; तथ्य->ev_i < तथ्य->controls_sz; तथ्य->ev_i++) {
                    अगर(तथ्य->controls[तथ्य->ev_i]->is_default_esc) {
                        तथ्य->controls[तथ्य->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        तथ्य->draw = true;
                        तथ्य->कुंजी_control_esc = तथ्य->controls[तथ्य->ev_i];
                    }
                }
            } अन्यथा अगर ((तथ्य->last_कुंजी_pressed == XK_Return) || (तथ्य->last_कुंजी_pressed == XK_KP_Enter)) {
                क्रम (तथ्य->ev_i = 0; तथ्य->ev_i < तथ्य->controls_sz; तथ्य->ev_i++) {
                    अगर(तथ्य->controls[तथ्य->ev_i]->selected) {
                        तथ्य->controls[तथ्य->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        तथ्य->draw = true;
                        तथ्य->कुंजी_control_enter = तथ्य->controls[तथ्य->ev_i];
                    }
                }
            }
            अवरोध;
        हाल कुंजी_Release:
        {
            कुंजी_Sym कुंजी = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            अगर (कुंजी != तथ्य->last_कुंजी_pressed) {
                अवरोध;
            }

            अगर (कुंजी == XK_Escape) {
                अगर (तथ्य->कुंजी_control_esc) {
                    अगर (तथ्य->कुंजी_control_esc->func_on_state_change) {
                        तथ्य->कुंजी_control_esc->func_on_state_change(तथ्य->कुंजी_control_esc);
                    }
                }
            } अन्यथा अगर ((कुंजी == XK_Return) || (कुंजी == XK_KP_Enter)) {
                अगर (तथ्य->कुंजी_control_enter) {
                    अगर (तथ्य->कुंजी_control_enter->func_on_state_change) {
                        तथ्य->कुंजी_control_enter->func_on_state_change(तथ्य->कुंजी_control_enter);
                    }
                }
            } अन्यथा अगर (कुंजी == XK_Tab || कुंजी == XK_बायाँ || कुंजी == XK_दायाँ) {
                अगर (तथ्य->focused_control) {
                    तथ्य->focused_control->selected = false;
                }
                तथ्य->draw = true;
                क्रम (तथ्य->ev_i = 0; तथ्य->ev_i < तथ्य->dyn_controls_sz; तथ्य->ev_i++) {
                    अगर (तथ्य->dyn_controls[तथ्य->ev_i] == तथ्य->focused_control) {
                        पूर्णांक अग्र_सूचकांक;

                        अगर (कुंजी == XK_बायाँ) {
                            अग्र_सूचकांक = तथ्य->ev_i - 1;
                        } अन्यथा {
                            अग्र_सूचकांक = तथ्य->ev_i + 1;
                        }
                        अगर ((अग्र_सूचकांक >= तथ्य->dyn_controls_sz) || (अग्र_सूचकांक < 0)) {
                            अगर (कुंजी == XK_दायाँ || कुंजी == XK_बायाँ) {
                                अग्र_सूचकांक = तथ्य->ev_i;
                            } अन्यथा {
                                अग्र_सूचकांक = 0;
                            }
                        }
                        तथ्य->focused_control = तथ्य->dyn_controls[अग्र_सूचकांक];
                        तथ्य->focused_control->selected = true;
                        अवरोध;
                    }
                }
            }
            अवरोध;
        }
    }

    अगर (तथ्य->draw) {
        X11Toolkit_DrawWindow(तथ्य);
    }
}

व्योम X11Toolkit_DoWindowEventLoop(SDL_ToolkitWindowX11 *तथ्य) {
   जबतक (!तथ्य->बंद) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(तथ्य->display, &e);
        अगर (तथ्य->xsettings) {
            xsettings_client_process_event(तथ्य->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(तथ्य->display, &e, X11Toolkit_EventTest, (XPointer)तथ्य);
        X11Toolkit_ProcessWindowEvents(तथ्य, &e);
    }
}


व्योम X11Toolkit_ResizeWindow(SDL_ToolkitWindowX11 *तथ्य, पूर्णांक w, पूर्णांक h) {
    अगर (!तथ्य->pixmap) {
        तथ्य->window_width = w;
        तथ्य->window_height = h;
    } अन्यथा {
        तथ्य->window_width = SDL_lroundf((w/तथ्य->iscale) * तथ्य->scale);
        तथ्य->window_height = SDL_lroundf((h/तथ्य->iscale) * तथ्य->scale);
        तथ्य->pixmap_width = w;
        तथ्य->pixmap_height = h;
        X11_XFreePixmap(तथ्य->display, तथ्य->drawable);
        X11Toolkit_InitWindowPixmap(तथ्य);
    }

    X11_XResizeWindow(तथ्य->display, तथ्य->window, तथ्य->window_width, तथ्य->window_height);
}

अटल व्योम X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->window->display, icon_control->icon_char_font);
    SDL_free(control);
}

अटल व्योम X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->window->iscale;
    control->rect.h -= 2 * control->window->iscale;
    X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + (2 * control->window->iscale), control->rect.y + (2* control->window->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    चयन (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        हाल SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                अवरोध;
        हाल SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_black.pixel);
                अवरोध;
        हाल SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->window->display, control->window->drawable, control->window->ctx, control->rect.x+(1* control->window->iscale), control->rect.y+(1* control->window->iscale), control->rect.w-(2* control->window->iscale), control->rect.h-(2* control->window->iscale), 0, 360 * 64);
                X11_XSetForeground(control->window->display, control->window->ctx, icon_control->xcolor_white.pixel);
                अवरोध;
    }
    X11_XSetFont(control->window->display, control->window->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->window->display, control->window->drawable, control->window->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    अगर (!control->window->utf8) {
        X11_XSetFont(control->window->display, control->window->ctx, control->window->font_struct->fid);
    }

    control->rect.w += 2 * control->window->iscale;
    control->rect.h += 2 * control->window->iscale;
}

अटल व्योम X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    पूर्णांक icon_char_w;
    पूर्णांक icon_wh;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11Toolkit_GetTextWidthHeightForFont(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, शून्य);
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

अटल व्योम X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitIconControlX11 *control;
    अक्षर *font;

    control = (SDL_ToolkitIconControlX11 *)base_control;
    X11_XFreeFont(base_control->window->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_आकार * base_control->window->iscale);
    control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
    SDL_free(font);
    अगर (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_आकार * base_control->window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(base_control->window->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_ToolkitWindowX11 *window, SDL_MessageBoxFlags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    अक्षर *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(माप(SDL_ToolkitIconControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    अगर (!control) {
        SDL_SetError("Unable to allocate icon control structure");
        वापस शून्य;
    }

    /* Fill out struct */
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawIconControl;
    base_control->func_free = X11Toolkit_DestroyIconControl;
    base_control->func_on_state_change = शून्य;
    base_control->func_calc_आकार = X11Toolkit_CalculateIconControl;
    base_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = false;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_आकार * window->iscale);
    control->icon_char_font = X11_XLoadQueryFont(window->display, font);
    SDL_free(font);
    अगर (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_आकार * window->iscale);
        control->icon_char_font = X11_XLoadQueryFont(window->display, font);
        SDL_free(font);
        अगर (!control->icon_char_font) {
            SDL_free(control);
            वापस शून्य;
        }
    }

    /* Set colors */
    चयन (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    हाल SDL_MESSAGEBOX_ERROR:
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
        अवरोध;
    हाल SDL_MESSAGEBOX_WARNING:
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
        अवरोध;
    हाल SDL_MESSAGEBOX_INFORMATION:
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
        अवरोध;
    शेष:
        X11_XFreeFont(window->display, control->icon_char_font);
        SDL_free(control);
        वापस शून्य;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    अगर (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } अन्यथा अगर (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } अन्यथा {
        control->xcolor_bg_shadow.red = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    अगर (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } अन्यथा अगर (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } अन्यथा {
        control->xcolor_bg_shadow.green = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    अगर (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } अन्यथा अगर (window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } अन्यथा {
        control->xcolor_bg_shadow.blue = SDL_clamp(window->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(window->display, window->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(base_control);

    X11Toolkit_AddControlToWindow(window, base_control);
    वापस base_control;
}

bool X11_Toolkit_Notify_Control_Of_आकार_Change(SDL_ToolkitControlX11 *control) {
    अगर (control->func_calc_आकार) {
        control->func_calc_आकार(control);
        वापस true;
    } अन्यथा {
        वापस false;
    }
}

अटल व्योम X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11Toolkit_GetTextElementsRect(button_control->text, &button_control->text_rect);
    अगर (control->do_आकार) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->window->iscale + button_control->text_rect.h;
    }
    button_control->text_rect.x = (control->rect.w - button_control->text_rect.w)/2;
    button_control->text_rect.y = (control->rect.h - button_control->text_rect.h)/2;
}


अटल व्योम X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    /* Draw bevel */
    अगर (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
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
            अगर (control->selected) {
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

अटल व्योम X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    अगर (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_तथ्य);
    }
}

अटल व्योम X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11Toolkit_FreeTextElements(button_control->text);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_ToolkitWindowX11 *window, स्थिर SDL_Message_Box_Button_तथ्य *तथ्य) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *base_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(माप(SDL_ToolkitButtonControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    अगर (!control) {
        SDL_SetError("Unable to allocate button control structure");
        वापस शून्य;
    }
    base_control->window = window;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->func_calc_आकार = X11Toolkit_CalculateButtonControl;
    base_control->func_draw = X11Toolkit_DrawButtonControl;
    base_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    base_control->func_free = X11Toolkit_DestroyButtonControl;
    base_control->func_on_scale_change = शून्य;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = true;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    अगर (तथ्य->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        base_control->is_default_esc = true;
    }
    अगर (तथ्य->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        base_control->is_default_enter = true;
        base_control->selected = true;
    }
    control->cb = शून्य;
    control->तथ्य = तथ्य;
#अगर_घोषित HAVE_FRIBIDI_H
    control->text = X11Toolkit_MakeTextElements(base_control->window, (अक्षर *)control->तथ्य->text, SDL_strlen(control->तथ्य->text), शून्य);
#अन्यथा 
    control->text = X11Toolkit_MakeTextElements(base_control->window, (अक्षर *)control->तथ्य->text, SDL_strlen(control->तथ्य->text));
#पूर्ण_अगर
    X11Toolkit_ShapeTextElements(base_control->window, control->text);
    
    base_control->do_आकार = true;
    X11Toolkit_CalculateButtonControl(base_control);
    base_control->do_आकार = false;

    X11Toolkit_AddControlToWindow(window, base_control);
    वापस base_control;
}

व्योम X11Toolkit_RegisterCallbackForButtonControl(SDL_ToolkitControlX11 *control, व्योम *तथ्य, व्योम (*cb)(काष्ठा SDL_ToolkitControlX11 *, व्योम *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_तथ्य = तथ्य;
    button_control->cb = cb;
}

स्थिर SDL_Message_Box_Button_तथ्य *X11_Toolkit_Get_Button_Control_तथ्य(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    वापस button_control->तथ्य;
}

व्योम X11Toolkit_DestroyWindow(SDL_ToolkitWindowX11 *तथ्य) {
    पूर्णांक i;

    अगर (!तथ्य) {
        वापस;
    }

#अगर SDL_GRAB
    अगर (तथ्य->mode == SDL_TOOLKIT_WINDOW_MODE_X11_MENU || तथ्य->mode== SDL_TOOLKIT_WINDOW_MODE_X11_TOOLTIP) {
        X11_XUngrabPointer(तथ्य->display, CurrentTime);
        X11_XUngrabKeyboard(तथ्य->display, CurrentTime);
    }
#पूर्ण_अगर

    क्रम (i = 0; i < तथ्य->controls_sz; i++) {
        अगर (तथ्य->controls[i]->func_free) {
            तथ्य->controls[i]->func_free(तथ्य->controls[i]);
        }
    }
    SDL_free(तथ्य->controls);
    SDL_free(तथ्य->dyn_controls);

    अगर (तथ्य->popup_windows) {
        SDL_ListClear(&तथ्य->popup_windows);
    }

    अगर (तथ्य->pixmap) {
        X11_XFreePixmap(तथ्य->display, तथ्य->drawable);
    }

#अगर_अघोषित NO_SHARED_MEMORY
    अगर (तथ्य->pixmap && तथ्य->shm) {
        X11_XShmDetach(तथ्य->display, &तथ्य->shm_info);
        अगर (!तथ्य->shm_pixmap) {
            XDestroyImage(तथ्य->image);
        }
        shmdt(तथ्य->shm_info.shmaddr);
    }
#पूर्ण_अगर

#अगर_घोषित X_HAVE_UTF8_STRING
    अगर (तथ्य->font_set) {
        X11_XFreeFontSet(तथ्य->display, तथ्य->font_set);
        तथ्य->font_set = शून्य;
    }
#पूर्ण_अगर

    अगर (तथ्य->font_struct) {
        X11_XFreeFont(तथ्य->display, तथ्य->font_struct);
        तथ्य->font_struct = शून्य;
    }

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XDBE
    अगर (SDL_X11_HAVE_XDBE && तथ्य->xdbe && !तथ्य->pixmap) {
        X11_Xdbe_Deallocate_Back_बफर_Name(तथ्य->display, तथ्य->buf);
    }
#पूर्ण_अगर

    अगर (तथ्य->xsettings) {
        xsettings_client_destroy(तथ्य->xsettings);
    }

    X11_XFreeGC(तथ्य->display, तथ्य->ctx);

    अगर (तथ्य->display) {
        अगर (तथ्य->window != None) {
            X11_XWithdrawWindow(तथ्य->display, तथ्य->window, तथ्य->screen);
            X11_XDestroyWindow(तथ्य->display, तथ्य->window);
            तथ्य->window = None;
        }

        अगर (तथ्य->display_close) {
            X11_XCloseDisplay(तथ्य->display);
        }
        तथ्य->display = शून्य;
    }

#अगर SDL_SET_LOCALE
    अगर (तथ्य->origlocale && (तथ्य->mode == SDL_TOOLKIT_WINDOW_MODE_X11_DIALOG)) {
        (व्योम)रखो_क्षेत्र(LC_ALL, तथ्य->origlocale);
        SDL_free(तथ्य->origlocale);
    }
#पूर्ण_अगर

#अगर_घोषित HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(तथ्य->fribidi);
#पूर्ण_अगर

#अगर_घोषित HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(तथ्य->th);
#पूर्ण_अगर

    SDL_free(तथ्य);
}

अटल पूर्णांक X11_Toolkit_गिनती_पंक्तियाँ_Of_Text(स्थिर अक्षर *text)
{
    पूर्णांक परिणाम = 0;
    जबतक (text && *text) {
        स्थिर अक्षर *lf = SDL_strchr(text, '\n');
        परिणाम++; // even without an endline, this counts as a line.
        text = lf ? lf + 1 : शून्य;
    }
    वापस परिणाम;
}

अटल व्योम X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    पूर्णांक i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->window->display, control->window->ctx, control->window->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    क्रम (i = 0; i < label_control->sz; i++) {
        X11Toolkit_DrawTextElements(control->window, label_control->पंक्तियाँ[i].text, control->rect.x + label_control->पंक्तियाँ[i].rect.x, control->rect.y + label_control->पंक्तियाँ[i].rect.y);
    }
}

अटल व्योम X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    पूर्णांक i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    क्रम (i = 0; i < label_control->sz; i++) {
        X11Toolkit_FreeTextElements(label_control->पंक्तियाँ[i].text);
    }
    SDL_free(label_control->पंक्तियाँ);
    SDL_free(label_control);
}

अटल व्योम X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *base_control) {
    SDL_ToolkitLabelControlX11 *control;
    पूर्णांक i;

    control = (SDL_ToolkitLabelControlX11 *)base_control;
    
    अगर (base_control->do_आकार) {
        base_control->rect.w = 0;
        base_control->rect.h = 0;
    }
    
    क्रम (i = 0; i < control->sz; i++) {
        पूर्णांक font_h;
        
        font_h = X11Toolkit_GetTextElementsRect(control->पंक्तियाँ[i].text, &control->पंक्तियाँ[i].rect);
        
        अगर (base_control->do_आकार) {
            base_control->rect.w = SDL_max(base_control->rect.w, control->पंक्तियाँ[i].rect.w);
        }
        
        अगर (i > 0) {
            control->पंक्तियाँ[i].rect.y = font_h + control->पंक्तियाँ[i - 1].rect.y;
        } अन्यथा {
            control->पंक्तियाँ[i].rect.y = 0;
        }
    }

#अगर_घोषित HAVE_FRIBIDI_H
    अगर (base_control->window->fribidi) {
        FriBidiParType first_ndn_dir;
        पूर्णांक last_ndn;
    
        first_ndn_dir = FRIBIDI_PAR_LTR;
        क्रम (i = 0; i < control->sz; i++) {
            अगर (control->पंक्तियाँ[i].par != FRIBIDI_PAR_ON) {
                first_ndn_dir = control->पंक्तियाँ[i].par;
            }
        }

        last_ndn = -1;
        क्रम (i = 0; i < control->sz; i++) {
            चयन (control->पंक्तियाँ[i].par) {
                हाल FRIBIDI_PAR_LTR:
                    control->पंक्तियाँ[i].rect.x = 0;
                    last_ndn = i;
                    अवरोध;
                हाल FRIBIDI_PAR_RTL:
                    control->पंक्तियाँ[i].rect.x = base_control->rect.w - control->पंक्तियाँ[i].rect.w;
                    last_ndn = i;
                    अवरोध;
                शेष:
                    अगर (last_ndn != -1) {
                        अगर (control->पंक्तियाँ[last_ndn].par == FRIBIDI_PAR_RTL) {
                            control->पंक्तियाँ[i].rect.x = base_control->rect.w - control->पंक्तियाँ[i].rect.w;
                        } अन्यथा {
                            control->पंक्तियाँ[i].rect.x = 0;
                        }
                    } अन्यथा {
                        अगर (first_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->पंक्तियाँ[i].rect.x = base_control->rect.w - control->पंक्तियाँ[i].rect.w;
                        } अन्यथा {
                            control->पंक्तियाँ[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#पूर्ण_अगर
    
    अगर (base_control->do_आकार && control->sz) {
        base_control->rect.h = control->पंक्तियाँ[control->sz - 1].rect.y + control->पंक्तियाँ[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_ToolkitWindowX11 *window, अक्षर *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *base_control;
    पूर्णांक i;
    
    अगर (!utf8) {
        वापस शून्य;
    }
 
    अगर (!SDL_strcmp(utf8, "")) {
        वापस शून्य;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(माप(SDL_ToolkitLabelControlX11));
    base_control = (SDL_ToolkitControlX11 *)control;
    अगर (!control) {
        SDL_SetError("Unable to allocate label control structure");
        वापस शून्य;
    }
    base_control->window = window;
    base_control->func_draw = X11Toolkit_DrawLabelControl;
    base_control->func_on_state_change = शून्य;
    base_control->func_calc_आकार = X11Toolkit_CalculateLabelControl;
    base_control->func_free  = X11Toolkit_DestroyLabelControl;
    base_control->func_on_scale_change = शून्य;
    base_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_NORMAL;
    base_control->selected = false;
    base_control->dynamic = false;
    base_control->rect.w = 0;
    base_control->rect.h = 0;
    base_control->is_default_enter = false;
    base_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_गिनती_पंक्तियाँ_Of_Text(utf8);
    control->पंक्तियाँ = SDL_calloc(control->sz, माप(SDL_Toolkit_Label_Control_पंक्ति_X11));
    क्रम (i = 0; i < control->sz; i++) {
        स्थिर अक्षर *lf = SDL_strchr(utf8, '\n');
        स्थिर पूर्णांक लंबाई = lf ? (lf - utf8) : SDL_strlen(utf8);
        पूर्णांक sz;
        
        sz = लंबाई;
        अगर (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#अगर_घोषित HAVE_FRIBIDI_H
        control->पंक्तियाँ[i].text = X11Toolkit_MakeTextElements(base_control->window, (अक्षर *)utf8, sz, &control->पंक्तियाँ[i].par);
#अन्यथा 
        control->पंक्तियाँ[i].text = X11Toolkit_MakeTextElements(base_control->window, (अक्षर *)utf8, sz);
#पूर्ण_अगर
        X11Toolkit_ShapeTextElements(base_control->window, control->पंक्तियाँ[i].text);

        utf8 += लंबाई + 1;
        अगर (!lf) {
            अवरोध;
        }
    }

    base_control->do_आकार = true;
    X11Toolkit_CalculateLabelControl(base_control);
    base_control->do_आकार = false;
    X11Toolkit_AddControlToWindow(window, base_control);

    वापस base_control;
}

पूर्णांक X11_Toolkit_Get_Label_Control_First_पंक्ति_Height(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    वापस label_control->पंक्तियाँ[0].rect.h;
}

व्योम X11Toolkit_SignalWindowClose(SDL_ToolkitWindowX11 *तथ्य) {
    तथ्य->बंद = true;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
