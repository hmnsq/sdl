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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "../../SDL_list.h"
#अन्तर्भाव "SDL_x11video.h"
#यदि_परिभाषितम् SDL_USE_LIBDBUS
#अन्तर्भाव "../../core/linux/SDL_system_theme.h"
#यदि_अन्तः
#यदि_परिभाषितम् HAVE_FRIBIDI_H
#अन्तर्भाव "../../core/unix/SDL_fribidi.h"
#यदि_अन्तः
#अन्तर्भाव "SDL_x11dyn.h"
#अन्तर्भाव "SDL_x11toolkit.h"
#अन्तर्भाव "SDL_x11settings.h"
#अन्तर्भाव "SDL_x11modes.h"
#अन्तर्भाव "xsettings-client.h"
#अन्तर्भाव <X11/keysym.h>
#अन्तर्भाव <locale.h>

#परिभाषय SDL_समुच्चयः_LOCALE 1
#परिभाषय SDL_GRAB 1

प्रकारनिर्देश गणना SDL_ToolkitTextTypeX11
{
    SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC,
    SDL_TOOLKIT_TEXT_TYPE_X11_THAI
} SDL_ToolkitTextTypeX11;

#यदि_परिभाषितम् HAVE_LIBTHAI_H
प्रकारनिर्देश संरचना SDL_ToolkitThaiOverlayX11
{
    bool शिखरम्;
    वर्ण *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#यदि_अन्तः

प्रकारनिर्देश संरचना SDL_ToolkitTextElementX11
{
    SDL_ToolkitTextTypeX11 type;
    वर्ण *str;
    size_t sz;
    SDL_Rect rect;
    पूर्णाङ्क font_h;
    शून्य (*str_free)(शून्य *);
#यदि_परिभाषितम् HAVE_LIBTHAI_H
    SDL_List_ग्रन्थिः *thai_overlays;
#यदि_अन्तः
} SDL_ToolkitTextElementX11;

प्रकारनिर्देश संरचना SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 parent;

    /* Icon type */
    SDL_सन्देशः_Box_Flags flags;
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

    /*दत्त*/
    ध्रुव SDL_सन्देशः_Box_Button_दत्त *दत्त;

    /* Text */
    SDL_List_ग्रन्थिः *text;
    SDL_Rect text_rect;
    
    /* Callback */
    शून्य *cb_दत्त;
    शून्य (*cb)(संरचना SDL_ToolkitControlX11 *, शून्य *);
} SDL_ToolkitButtonControlX11;

प्रकारनिर्देश संरचना SDL_Toolkit_Label_Control_पङ्क्तिः_X11
{
    SDL_List_ग्रन्थिः *text;
    SDL_Rect rect;
#यदि_परिभाषितम् HAVE_FRIBIDI_H
    FriBidiParType par;
#यदि_अन्तः
} SDL_Toolkit_Label_Control_पङ्क्तिः_X11;

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
    SDL_Toolkit_Label_Control_पङ्क्तिः_X11 *पङ्क्तयः;
    size_t sz;
} SDL_ToolkitLabelControlX11;

प्रकारनिर्देश संरचना SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_ग्रन्थिः *menu_वस्तूनि;
} SDL_ToolkitMenuBarControlX11;

प्रकारनिर्देश संरचना SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 parent;

    SDL_List_ग्रन्थिः *menu_वस्तूनि;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
स्थिर ध्रुव वर्ण *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#परिभाषय G_ICONFONT_आकार 22

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
#परिभाषय G_TOOLKITFONT_आकार 140

स्थिर ध्रुव SDL_सन्देशः_Box_Color g_default_colors[SDL_MESSAGEBOX_COLOR_गणनम्] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#यदि_परिभाषितम् SDL_USE_LIBDBUS
स्थिर ध्रुव SDL_सन्देशः_Box_Color g_default_colors_dark[SDL_MESSAGEBOX_COLOR_गणनम्] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#यदि 0
स्थिर ध्रुव SDL_सन्देशः_Box_Color g_default_colors_dark_उच्चः_contrast[SDL_MESSAGEBOX_COLOR_गणनम्] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

स्थिर ध्रुव SDL_सन्देशः_Box_Color g_default_colors_light_उच्चः_contrast[SDL_MESSAGEBOX_COLOR_गणनम्] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#यदि_अन्तः

#यदि_अन्तः

स्थिर पूर्णाङ्क g_shm_error;
स्थिर पूर्णाङ्क (*g_old_error_handler)(Display *, XErrorEvent *) = रिक्त;

स्थिर पूर्णाङ्क X11_Toolkit_Shared_स्मृतिः_Error_Handler(Display *d, XErrorEvent *e)
{
    यदि (e->error_संहिता == BadAccess || e->error_संहिता == BadRequest) {
        g_shm_error = True;
        प्रत्यागम 0;
    }
    प्रत्यागम g_old_error_handler(d, e);
}

स्थिर शून्य X11_Toolkit_Init_गवाक्षः_Pixmap(SDL_Toolkit_गवाक्षः_X11 *दत्त) {
    यदि (दत्त->pixmap) {
#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
        यदि (!दत्त->shm_pixmap) {
            दत्त->drawable = X11_XCreatePixmap(दत्त->display, दत्त->गवाक्षः, दत्त->pixmap_विस्तारः, दत्त->pixmap_height, दत्त->गभीरता_2);
        }
#अन्यथा
        दत्त->drawable = X11_XCreatePixmap(दत्त->display, दत्त->गवाक्षः, दत्त->pixmap_विस्तारः, दत्त->pixmap_height, दत्त->गभीरता_2);
#यदि_अन्तः
#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
        यदि (दत्त->shm) {
            दत्त->image = X11_XShmCreateImage(दत्त->display, दत्त->visual, दत्त->गभीरता_2, ZPixmap, रिक्त, &दत्त->shm_info, दत्त->pixmap_विस्तारः, दत्त->pixmap_height);
            यदि (दत्त->image) {
                दत्त->shm_अष्टकानि_प्रत्येकम्_पङ्क्तिः = दत्त->image->अष्टकानि_प्रत्येकम्_पङ्क्तिः;

                दत्त->shm_info.shmid = shmget(IPC_वैयक्तिकम्, दत्त->image->अष्टकानि_प्रत्येकम्_पङ्क्तिः * दत्त->image->height, IPC_CREAT | 0777);
                यदि (दत्त->shm_info.shmid < 0) {
                    XDestroyImage(दत्त->image);
                    दत्त->image = रिक्त;
                    दत्त->shm = false;
                    प्रत्यागम;
                }

                दत्त->shm_info.readOnly = False;
                दत्त->shm_info.shmaddr = दत्त->image->दत्त = (वर्ण *)shmat(दत्त->shm_info.shmid, रिक्त, 0);
                यदि (((चिह्नित वर्ण *)दत्त->shm_info.shmaddr) == (चिह्नित वर्ण *)-1) {
                    XDestroyImage(दत्त->image);
                    दत्त->shm = false;
                    दत्त->image = रिक्त;
                    प्रत्यागम;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11_Toolkit_Shared_स्मृतिः_Error_Handler);
                X11_XShmAttach(दत्त->display, &दत्त->shm_info);
                X11_XSync(दत्त->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                यदि (g_shm_error) {
                    XDestroyImage(दत्त->image);
                    shmdt(दत्त->shm_info.shmaddr);
                    shmctl(दत्त->shm_info.shmid, IPC_RMID, रिक्त);
                    दत्त->image = रिक्त;
                    दत्त->shm = false;
                    प्रत्यागम;
                }

                यदि (दत्त->shm_pixmap) {
                    दत्त->drawable = X11_XShmCreatePixmap(दत्त->display, दत्त->गवाक्षः, दत्त->shm_info.shmaddr, &दत्त->shm_info, दत्त->pixmap_विस्तारः, दत्त->pixmap_height, दत्त->गभीरता_2);
                    यदि (दत्त->drawable == None) {
                        दत्त->shm_pixmap = False;
                    } अन्यथा {
                        XDestroyImage(दत्त->image);
                        दत्त->image = रिक्त;
                    }
                }

                shmctl(दत्त->shm_info.shmid, IPC_RMID, रिक्त);
            } अन्यथा {
                दत्त->shm = false;
            }
        }
#यदि_अन्तः
    }
}

स्थिर शून्य X11_Toolkit_Init_गवाक्षः_Fonts(SDL_Toolkit_गवाक्षः_X11 *गवाक्षः)
{    
    गवाक्षः->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    गवाक्षः->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    गवाक्षः->utf8 = true;
    गवाक्षः->font_समुच्चयः = रिक्त;
    यदि (SDL_X11_HAVE_UTF8) {
        वर्ण **missing = रिक्त;
        पूर्णाङ्क अङ्कः_missing = 0;
        पूर्णाङ्क i_font;
        गवाक्षः->font_struct = रिक्त;
        प्रति (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            वर्ण *font;

            यदि (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_आरोपय_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_आकार * गवाक्षः->iscale);
                गवाक्षः->font_समुच्चयः = X11_XCreate_Font_समुच्चयः(गवाक्षः->display, font, &missing, &अङ्कः_missing, रिक्त);
                SDL_free(font);

                यदि (!गवाक्षः->font_समुच्चयः) {
                    यदि (गवाक्षः->scale != 0 && गवाक्षः->iscale > 0) {
                        गवाक्षः->iscale = (पूर्णाङ्क)SDL_ceilf(गवाक्षः->scale);
                        गवाक्षः->scale = 0;
                    } अन्यथा {
                        गवाक्षः->iscale--;
                    }
                    गच्छ try_आरोपय_font;
                }
            } अन्यथा {
                गवाक्षः->font_समुच्चयः = X11_XCreate_Font_समुच्चयः(गवाक्षः->display, g_ToolkitFont[i_font], &missing, &अङ्कः_missing, रिक्त);
            }

            यदि (missing) {
                X11_XFreeStringList(missing);
            }

            यदि (गवाक्षः->font_समुच्चयः) {
                भङ्ग;
            }
        }

        यदि (!गवाक्षः->font_समुच्चयः) {
            गच्छ आरोपय_font_traditional;
        } अन्यथा {
            XFontStruct **font_structs;
            वर्ण **font_नामानि;
            पूर्णाङ्क font_sz;
            पूर्णाङ्क i;
            
#यदि_परिभाषितम् HAVE_FRIBIDI_H
            गवाक्षः->do_shaping = !X11_XContextDependentDrawing(गवाक्षः->font_समुच्चयः);
#यदि_अन्तः
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFonts_सम्बन्धि_Font_समुच्चयः(गवाक्षः->font_समुच्चयः, &font_structs, &font_नामानि);
            प्रति (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                यदि (SDL_strstr(font_नामानि[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } अन्यथा यदि (SDL_strstr(font_नामानि[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } अन्यथा यदि (SDL_strstr(font_नामानि[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } अन्यथा यदि (SDL_strstr(font_नामानि[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } अन्यथा यदि (SDL_strstr(font_नामानि[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                यदि (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(गवाक्षः->display, font_नामानि[i]);
                    यदि (font_struct) {
                        यदि (font_struct->प्रत्येकम्_char) {
                            पूर्णाङ्क glyphs_sz;
                            पूर्णाङ्क j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            प्रति (j = 0; j < glyphs_sz; j++) {
                                यदि (font_struct->प्रत्येकम्_char[j].lbearing < 0) {
                                    गवाक्षः->thai_font = SDL_TOOLKIT_THAI_FONT_X11_विस्थापनम्;
                                }
                            }
                        }
                        X11_XFreeFont(गवाक्षः->display, font_struct);
                    }
                }
                
                गवाक्षः->thai_encoding = thai_encoding;
            } 
        }
    } अन्यथा
#यदि_अन्तः
    {
        वर्ण *font;

        आरोपय_font_traditional:
        गवाक्षः->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_आकार * गवाक्षः->iscale);
        गवाक्षः->font_struct = X11_XLoadQueryFont(गवाक्षः->display, font);
        SDL_free(font);
        यदि (!गवाक्षः->font_struct) {
            यदि (गवाक्षः->iscale > 0) {
                यदि (गवाक्षः->scale != 0) {
                    गवाक्षः->iscale = (पूर्णाङ्क)SDL_ceilf(गवाक्षः->scale);
                    गवाक्षः->scale = 0;
                } अन्यथा {
                    गवाक्षः->iscale--;
                }
                गच्छ आरोपय_font_traditional;
            } अन्यथा {
                गवाक्षः->font_struct = X11_XLoadQueryFont(गवाक्षः->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

स्थिर शून्य X11Toolkit_SettingsNotify(ध्रुव वर्ण *name, XSettingsAction action, XSettingsSetting *setting, शून्य *दत्त)
{
    SDL_Toolkit_गवाक्षः_X11 *गवाक्षः;
    पूर्णाङ्क i;

    गवाक्षः = दत्त;

    यदि (गवाक्षः->xsettings_first_time) {
        प्रत्यागम;
    }

    यदि (SDL_strcmp(name, SDL_XSETTINGS_GDK_गवाक्षः_SCALING_गुणकः) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_सज्जता = false;
        bool pixmap_already_सज्जता = false;

        यदि (गवाक्षः->pixmap) {
            pixmap_already_सज्जता = true;
        } अन्यथा {
            dbe_already_सज्जता = true;
        }

        /* set scale vars */
        गवाक्षः->scale = X11_GetGlobalContentScale(गवाक्षः->display, गवाक्षः->xsettings);
        गवाक्षः->iscale = (पूर्णाङ्क)SDL_ceilf(गवाक्षः->scale);
        यदि (गवाक्षः->scale < 1) {
            गवाक्षः->scale = 1;
        }
        यदि (SDL_roundf(गवाक्षः->scale) == गवाक्षः->scale) {
            गवाक्षः->scale = 0;
        }

        /* setup fonts */
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
        यदि (गवाक्षः->font_समुच्चयः) {
            X11_XFree_Font_समुच्चयः(गवाक्षः->display, गवाक्षः->font_समुच्चयः);
        }
#यदि_अन्तः
        यदि (गवाक्षः->font_struct) {
            X11_XFreeFont(गवाक्षः->display, गवाक्षः->font_struct);
        }

        X11_Toolkit_Init_गवाक्षः_Fonts(गवाक्षः);

        /* set up window */
        यदि (गवाक्षः->scale != 0) {
            गवाक्षः->गवाक्षः_विस्तारः = SDL_lroundf((गवाक्षः->गवाक्षः_विस्तारः/गवाक्षः->iscale) * गवाक्षः->scale);
            गवाक्षः->गवाक्षः_height = SDL_lroundf((गवाक्षः->गवाक्षः_height/गवाक्षः->iscale) * गवाक्षः->scale);
            गवाक्षः->pixmap_विस्तारः = गवाक्षः->गवाक्षः_विस्तारः;
            गवाक्षः->pixmap_height = गवाक्षः->गवाक्षः_height;
            गवाक्षः->pixmap = true;
        } अन्यथा {
            गवाक्षः->pixmap = false;
        }

        यदि (गवाक्षः->pixmap) {
            यदि (!pixmap_already_सज्जता) {
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XDBE
                यदि (SDL_X11_HAVE_XDBE && गवाक्षः->xdbe) {
                    X11_Xdbe_Deallocate_पृष्ठभागः_बफर_Name(गवाक्षः->display, गवाक्षः->buf);
                }
#यदि_अन्तः
            }
            X11_XFreePixmap(गवाक्षः->display, गवाक्षः->drawable);
            X11_Toolkit_Init_गवाक्षः_Pixmap(गवाक्षः);
        } अन्यथा {
            यदि (!dbe_already_सज्जता) {
                X11_XFreePixmap(गवाक्षः->display, गवाक्षः->drawable);
#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
                यदि (गवाक्षः->image) {
                    XDestroyImage(गवाक्षः->image);
                    गवाक्षः->image = रिक्त;
                }
#यदि_अन्तः
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XDBE
                यदि (SDL_X11_HAVE_XDBE && गवाक्षः->xdbe) {
                    गवाक्षः->buf = X11_Xdbe_Allocate_पृष्ठभागः_बफर_Name(गवाक्षः->display, गवाक्षः->गवाक्षः, XdbeUndefined);
                    गवाक्षः->drawable = गवाक्षः->buf;
                }
#यदि_अन्तः
            }
        }

        /* notify controls */
        प्रति (i = 0; i < गवाक्षः->controls_sz; i++) {
            गवाक्षः->controls[i]->do_आकार = true;

            यदि (गवाक्षः->controls[i]->func_on_scale_change) {
                गवाक्षः->controls[i]->func_on_scale_change(गवाक्षः->controls[i]);
            }

            यदि (गवाक्षः->controls[i]->func_calc_आकार) {
                गवाक्षः->controls[i]->func_calc_आकार(गवाक्षः->controls[i]);
            }

            गवाक्षः->controls[i]->do_आकार = false;
        }

        /* notify cb */
        यदि (गवाक्षः->cb_on_scale_change) {
            गवाक्षः->cb_on_scale_change(गवाक्षः, गवाक्षः->cb_दत्त);
        }

        /* update ev scales */
        यदि (!गवाक्षः->pixmap) {
            गवाक्षः->ev_scale = गवाक्षः->ev_iscale = 1;
        } अन्यथा {
            गवाक्षः->ev_scale = गवाक्षः->scale;
            गवाक्षः->ev_iscale = गवाक्षः->iscale;
        }
    }
}

स्थिर शून्य X11_Toolkit_Get_Text_विस्तारः_Height_For_Font(XFontStruct *font, ध्रुव वर्ण *str, पूर्णाङ्क nbytes, पूर्णाङ्क *pwidth, पूर्णाङ्क *pheight, पूर्णाङ्क *ascent, पूर्णाङ्क *font_height)
{
    XCharStruct text_structure;
    पूर्णाङ्क font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &text_structure);
    *pwidth = text_structure.विस्तारः;
    *pheight = text_structure.ascent + text_structure.descent;
    *ascent = text_structure.ascent;
    यदि (font_height) {
       *font_height = font_ascent + font_descent;
    }
}

स्थिर शून्य X11_Toolkit_Get_Text_विस्तारः_Height(SDL_Toolkit_गवाक्षः_X11 *दत्त, ध्रुव वर्ण *str, पूर्णाङ्क nbytes, पूर्णाङ्क *pwidth, पूर्णाङ्क *pheight, पूर्णाङ्क *ascent, पूर्णाङ्क *descent, पूर्णाङ्क *font_height)
{
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    यदि (दत्त->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8TextExtents(दत्त->font_समुच्चयः, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.विस्तारः;
        *pheight = overall_logical.height;
        *ascent = -overall_logical.y;
        *descent = overall_logical.height - *ascent;

        यदि (font_height) {
            XFont_समुच्चयः_Extents *extents;

            extents = X11_XExtents_सम्बन्धि_Font_समुच्चयः(दत्त->font_समुच्चयः);
            *font_height = extents->max_logical_extent.height;
        }
    } अन्यथा
#यदि_अन्तः
    {
        XCharStruct text_structure;
        पूर्णाङ्क font_direction, font_ascent, font_descent;
        X11_XTextExtents(दत्त->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &text_structure);
        *pwidth = text_structure.विस्तारः;
        *pheight = text_structure.ascent + text_structure.descent;
        *ascent = text_structure.ascent;
        *descent = text_structure.descent;

        यदि (font_height) {
            *font_height = font_ascent + font_descent;
        }
    }
}

#यदि_परिभाषितम् HAVE_FRIBIDI_H
SDL_List_ग्रन्थिः *X11Toolkit_MakeTextElements(SDL_Toolkit_गवाक्षः_X11 *दत्त, वर्ण *txt, size_t sz, FriBidiParType *par)
#अन्यथा
SDL_List_ग्रन्थिः *X11Toolkit_MakeTextElements(SDL_Toolkit_गवाक्षः_X11 *दत्त, वर्ण *txt, size_t sz)
#यदि_अन्तः
{
    SDL_List_ग्रन्थिः *list;
    वर्ण *str;
    वर्ण *बफर_2;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = रिक्त;
    thai = 0;
    str = txt;
    बफर_2 = SDL_malloc(1);
    बफर_2[0] = 0;
    
#यदि_परिभाषितम् HAVE_FRIBIDI_H
    यदि (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    यदि (दत्त->fribidi) {
        वर्ण *fstr;
                
        fstr = SDL_FriBidi_Process(दत्त->fribidi, str, sz, दत्त->do_shaping, par);
        यदि (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#यदि_अन्तः        

    यावत् (1) {
        वर्ण *new;
        वर्ण utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_चरणः_UTF8((ध्रुव वर्ण **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        यदि (cp == 0 || cond == (thai ? false : true)) {
            SDL_ToolkitTextElementX11 *element;
            
            element = SDL_malloc(परिमाण(SDL_ToolkitTextElementX11));
            यदि (thai) {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_THAI;
            } अन्यथा {
                element->type = SDL_TOOLKIT_TEXT_TYPE_X11_GENERIC;
            }
            element->str = SDL_strdup(बफर_2);
            element->sz = SDL_strlen(बफर_2);
            element->str_free = SDL_free;
            
            SDL_List_सङ्कलय(&list, element);
            
            SDL_free(बफर_2);
            बफर_2 = SDL_malloc(1);
            बफर_2[0] = 0;
            thai = thai ? false : true;
        }

        यदि (!cp) {
            भङ्ग;
        }
        
        SDL_UCS4_गन्तव्यम्_UTF8(cp, utf8);
        csz = SDL_strlen(बफर_2) + SDL_strlen(utf8) + 1;
        new = SDL_malloc(csz);
        SDL_strlcpy(new, बफर_2, csz);
        SDL_strlcat(new, utf8, csz);
        SDL_free(बफर_2);
        बफर_2 = new;
    }

    SDL_free(बफर_2);
    यदि (free_txt) {
        SDL_free(txt);
    }
    प्रत्यागम list;
}

शून्य X11Toolkit_ShapeTextElements(SDL_Toolkit_गवाक्षः_X11 *दत्त, SDL_List_ग्रन्थिः *list)
{
    SDL_List_ग्रन्थिः *cursor;
    SDL_ToolkitTextElementX11 *पूर्व;
    पूर्णाङ्क अस्थायी;
    
    /* Shape and calculate bounding box */
    cursor = list;
    यावत् (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->प्रविष्टिः;
#यदि_परिभाषितम् HAVE_LIBTHAI_H
        element->thai_overlays = रिक्त;
#यदि_अन्तः
        यदि (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            यदि (दत्त->thai_font == SDL_TOOLKIT_THAI_FONT_X11_विस्थापनम्) {
                X11_Toolkit_Get_Text_विस्तारः_Height(दत्त, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &अस्थायी, रिक्त);
            } अन्यथा {
#यदि_परिभाषितम् HAVE_LIBTHAI_H
                यदि (दत्त->th) {
                    संरचना thcell_t *cells;
                    वर्ण *tis_str;
                    वर्ण *आधारः_tis_str;
                    size_t cells_sz;
                    size_t आधारः_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, परिमाण(संरचना thcell_t));
                    दत्त->th->make_cells((ध्रुव thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    आधारः_tis_str_sz = cells_sz;
                    आधारः_tis_str = SDL_malloc(आधारः_tis_str_sz + 1);
                    प्रति (अस्थायी = 0; अस्थायी < cells_sz; अस्थायी++) {
                        आधारः_tis_str[अस्थायी] = cells[अस्थायी].आधारः;
                        
                        यदि (cells[अस्थायी].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            वर्ण *pre;
                            पूर्णाङ्क temp2;
                            
                            overlay = SDL_malloc(परिमाण(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", आधारः_tis_str, अस्थायी);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ध्रुव वर्ण *)&cells[अस्थायी].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->शिखरम् = false;
                            X11_Toolkit_Get_Text_विस्तारः_Height(दत्त, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, रिक्त);
                            X11_Toolkit_Get_Text_विस्तारः_Height(दत्त, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, रिक्त);
                            SDL_List_सङ्कलय(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        यदि (cells[अस्थायी].शिखरम्) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            वर्ण *pre;
                            पूर्णाङ्क temp2;
                            
                            overlay = SDL_malloc(परिमाण(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", आधारः_tis_str, अस्थायी);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ध्रुव वर्ण *)&cells[अस्थायी].शिखरम्, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->शिखरम् = true;
                            X11_Toolkit_Get_Text_विस्तारः_Height(दत्त, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, रिक्त);
                            X11_Toolkit_Get_Text_विस्तारः_Height(दत्त, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, रिक्त);
                            SDL_List_सङ्कलय(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    आधारः_tis_str[आधारः_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", आधारः_tis_str, आधारः_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11_Toolkit_Get_Text_विस्तारः_Height(दत्त, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &अस्थायी, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(आधारः_tis_str);
                }
#अन्यथा
                X11_Toolkit_Get_Text_विस्तारः_Height(दत्त, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &अस्थायी, &element->font_h);
#यदि_अन्तः            
            }
        } अन्यथा {
            X11_Toolkit_Get_Text_विस्तारः_Height(दत्त, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &अस्थायी, &element->font_h);
        }
        
        cursor = cursor->अग्र;
    }
    
    /* Add offsets */
    पूर्व = रिक्त;
    cursor = list;
    यावत् (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->प्रविष्टिः;        
        यदि (पूर्व) {
            element->rect.x = पूर्व->rect.x + पूर्व->rect.w;
        } अन्यथा {
            element->rect.x = 0;
        }
        
        पूर्व = element;
        cursor = cursor->अग्र;
    }
}


शून्य X11Toolkit_DrawTextElements(SDL_Toolkit_गवाक्षः_X11 *दत्त, SDL_List_ग्रन्थिः *list, पूर्णाङ्क x, पूर्णाङ्क y)
{
    SDL_List_ग्रन्थिः *cursor;
    
    cursor = list;
    
    यावत् (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->प्रविष्टिः;
        यदि (element->type == SDL_TOOLKIT_TEXT_TYPE_X11_THAI) {
            यदि (दत्त->thai_font == SDL_TOOLKIT_THAI_FONT_X11_विस्थापनम्) {
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
                यदि (दत्त->utf8) {
                    X11_Xutf8DrawString(दत्त->display, दत्त->drawable, दत्त->font_समुच्चयः, दत्त->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } अन्यथा
#यदि_अन्तः
                {
                    X11_XDrawString(दत्त->display, दत्त->drawable, दत्त->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } अन्यथा {    
#यदि_परिभाषितम् HAVE_LIBTHAI_H
                SDL_List_ग्रन्थिः *overlay_cursor;
                    
                /* Draw the base string */
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
                यदि (दत्त->utf8) {
                    X11_Xutf8DrawString(दत्त->display, दत्त->drawable, दत्त->font_समुच्चयः, दत्त->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } अन्यथा
#यदि_अन्तः
                {
                    X11_XDrawString(दत्त->display, दत्त->drawable, दत्त->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                यावत् (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->प्रविष्टिः;
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
                    यदि (दत्त->utf8) {
                        X11_Xutf8DrawString(दत्त->display, दत्त->drawable, दत्त->font_समुच्चयः, दत्त->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } अन्यथा
#यदि_अन्तः
                    {
                        X11_XDrawString(दत्त->display, दत्त->drawable, दत्त->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->अग्र;
                }
#यदि_अन्तः                
            }
        } अन्यथा {
#यदि_परिभाषितम् X_HAVE_UTF8_STRING
            यदि (दत्त->utf8) {
                X11_Xutf8DrawString(दत्त->display, दत्त->drawable, दत्त->font_समुच्चयः, दत्त->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } अन्यथा
#यदि_अन्तः
            {
                X11_XDrawString(दत्त->display, दत्त->drawable, दत्त->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->अग्र;
    }
}

पूर्णाङ्क X11Toolkit_GetTextElementsRect(SDL_List_ग्रन्थिः *list, SDL_Rect *बहिर्गमनम्)
{
    SDL_List_ग्रन्थिः *cursor;
    पूर्णाङ्क ret;
    
    ret = 0;
    बहिर्गमनम्->x = बहिर्गमनम्->y = 0;
    बहिर्गमनम्->w = बहिर्गमनम्->h = 0;
    cursor = list;
    यावत् (cursor) {
        SDL_ToolkitTextElementX11 *element;
        
        element = cursor->प्रविष्टिः;
        
        बहिर्गमनम्->w += element->rect.w;
        बहिर्गमनम्->h = SDL_max(बहिर्गमनम्->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->अग्र;
    }
    
    प्रत्यागम ret;
}

शून्य X11Toolkit_FreeTextElementsListContents(SDL_List_ग्रन्थिः *list)
{
    SDL_List_ग्रन्थिः *cursor;
    
    cursor = list;
    यावत् (cursor) {
        SDL_ToolkitTextElementX11 *element;
#यदि_परिभाषितम् HAVE_LIBTHAI_H
        SDL_List_ग्रन्थिः *overlay_cursor;
#यदि_अन्तः

        element = cursor->प्रविष्टिः;
        
        यदि (element->str_free) {
            element->str_free(element->str);
        }
        
#यदि_परिभाषितम् HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        यावत् (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->प्रविष्टिः;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->अग्र;
        }
        SDL_ListClear(&element->thai_overlays);
#यदि_अन्तः
        
        SDL_free(element);
        
        cursor = cursor->अग्र;
    }
}

#परिभाषय X11Toolkit_FreeTextElements(x) X11Toolkit_FreeTextElementsListContents(x); SDL_ListClear(&x)
 
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

SDL_Toolkit_गवाक्षः_X11 *X11_Toolkit_Create_गवाक्षः_Struct(SDL_गवाक्षः *parent, SDL_Toolkit_गवाक्षः_X11 *tkparent, SDL_Toolkit_गवाक्षः_बहुलकम्_X11 बहुलकम्, ध्रुव SDL_सन्देशः_Box_Color *colorhints, bool create_new_display)
{
    SDL_Toolkit_गवाक्षः_X11 *गवाक्षः;
    पूर्णाङ्क i;
#यदि_परिभाषितम् SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#यदि_अन्तः
    #परिभाषय ErrorFreeRetNull(x, y) SDL_समुच्चयः_Error(x); SDL_free(y); प्रत्यागम रिक्त
    #परिभाषय ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_समुच्चयः_Error(x, y); SDL_free(z); प्रत्यागम रिक्त

    यदि (!SDL_X11_आरोपय_Symbols()) {
        प्रत्यागम रिक्त;
    }

    // This code could get called from multiple threads maybe?
    X11_XInit_तन्तवः();

    गवाक्षः = (SDL_Toolkit_गवाक्षः_X11 *)SDL_malloc(परिमाण(SDL_Toolkit_गवाक्षः_X11));
    यदि (!गवाक्षः) {
        SDL_समुच्चयः_Error("Unable to allocate toolkit window structure");
        प्रत्यागम रिक्त;
    }

    गवाक्षः->बहुलकम् = बहुलकम्;
    गवाक्षः->tk_parent = tkparent;

#यदि SDL_समुच्चयः_LOCALE
    यदि (बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_DIALOG) {
        गवाक्षः->origlocale = setlocale(LC_ALL, रिक्त);
        यदि (गवाक्षः->origlocale) {
            गवाक्षः->origlocale = SDL_strdup(गवाक्षः->origlocale);
            यदि (!गवाक्षः->origlocale) {
                SDL_free(गवाक्षः);
                प्रत्यागम रिक्त;
            }
            (शून्य)setlocale(LC_ALL, "");
        }
    }
#यदि_अन्तः

    गवाक्षः->parent_device = रिक्त;
    यदि (create_new_display) {
        गवाक्षः->display = X11_XOpenDisplay(रिक्त);
        गवाक्षः->display_close = true;
        यदि (!गवाक्षः->display) {
            ErrorFreeRetNull("Couldn't open X11 display", गवाक्षः);
        }
    } अन्यथा {
        यदि (parent) {
            गवाक्षः->parent_device = SDL_GetVideoDevice();
            गवाक्षः->display = गवाक्षः->parent_device->आन्तरिकम्->display;
            गवाक्षः->display_close = false;
        } अन्यथा यदि (tkparent) {
            गवाक्षः->display = tkparent->display;
            गवाक्षः->display_close = false;
        } अन्यथा {
            गवाक्षः->display = X11_XOpenDisplay(रिक्त);
            गवाक्षः->display_close = true;
            यदि (!गवाक्षः->display) {
                ErrorFreeRetNull("Couldn't open X11 display", गवाक्षः);
            }
        }
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
    पूर्णाङ्क xrandr_event_आधारः, xrandr_error_आधारः;
    गवाक्षः->xrandr = X11_XRRQueryExtension(गवाक्षः->display, &xrandr_event_आधारः, &xrandr_error_आधारः);
#यदि_अन्तः

#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
    गवाक्षः->shm_pixmap = False;
    गवाक्षः->shm = X11_XShmQueryExtension(गवाक्षः->display) ? SDL_X11_HAVE_SHM : false;
    यदि (गवाक्षः->shm) {
        पूर्णाङ्क major;
        पूर्णाङ्क minor;

        X11_XShm_Query_संस्करणम्(गवाक्षः->display, &major, &minor, &गवाक्षः->shm_pixmap);
        यदि (गवाक्षः->shm_pixmap) {
            यदि (X11_XShmPixmapFormat(गवाक्षः->display) != ZPixmap) {
                गवाक्षः->shm_pixmap = False;
            }
        }
    }
#यदि_अन्तः

    /* Scale/Xsettings */
    गवाक्षः->pixmap = false;
    गवाक्षः->xsettings_first_time = true;
    गवाक्षः->xsettings = xsettings_client_new(गवाक्षः->display, DefaultScreen(गवाक्षः->display), X11Toolkit_SettingsNotify, रिक्त, गवाक्षः);
    गवाक्षः->xsettings_first_time = false;
    गवाक्षः->scale = X11_GetGlobalContentScale(गवाक्षः->display, गवाक्षः->xsettings);
    यदि (गवाक्षः->scale < 1) {
        गवाक्षः->scale = 1;
    }
    गवाक्षः->iscale = (पूर्णाङ्क)SDL_ceilf(गवाक्षः->scale);
    यदि (SDL_roundf(गवाक्षः->scale) == गवाक्षः->scale) {
        गवाक्षः->scale = 0;
    }

    /* Fonts */
    X11_Toolkit_Init_गवाक्षः_Fonts(गवाक्षः);

    /* Color hints */
#यदि_परिभाषितम् SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    यदि (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#यदि_अन्तः

    यदि (!colorhints) {
#यदि_परिभाषितम् SDL_USE_LIBDBUS
        विकल्प (theme) {
            पक्ष SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                भङ्ग;
#यदि 0
            पक्ष SDL_SYSTEM_THEME_LIGHT_उच्चः_CONTRAST:
                colorhints = g_default_colors_light_उच्चः_contrast;
                भङ्ग;
            पक्ष SDL_SYSTEM_THEME_DARK_उच्चः_CONTRAST:
                colorhints = g_default_colors_dark_उच्चः_contrast;
                भङ्ग;
#यदि_अन्तः
            स्वभाव:
                colorhints = g_default_colors;
        }
#अन्यथा
        colorhints = g_default_colors;
#यदि_अन्तः
    }
    गवाक्षः->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    प्रति (i = 0; i < SDL_MESSAGEBOX_COLOR_गणनम्; i++) {
        गवाक्षः->xcolor[i].flags = DoRed|DoGreen|DoBlue;
        गवाक्षः->xcolor[i].red = colorhints[i].r * 257;
        गवाक्षः->xcolor[i].green = colorhints[i].g * 257;
        गवाक्षः->xcolor[i].blue = colorhints[i].b * 257;
    }

    /* Generate bevel and pressed colors */
    गवाक्षः->xcolor_bevel_l1.flags = DoRed|DoGreen|DoBlue;
    गवाक्षः->xcolor_bevel_l1.red = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 12500, 0, 65535);
    गवाक्षः->xcolor_bevel_l1.green = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 12500, 0, 65535);
    गवाक्षः->xcolor_bevel_l1.blue = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 12500, 0, 65535);

    गवाक्षः->xcolor_bevel_l2.flags = DoRed|DoGreen|DoBlue;
    गवाक्षः->xcolor_bevel_l2.red = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 32500, 0, 65535);
    गवाक्षः->xcolor_bevel_l2.green = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 32500, 0, 65535);
    गवाक्षः->xcolor_bevel_l2.blue = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 32500, 0, 65535);

    गवाक्षः->xcolor_bevel_d.flags = DoRed|DoGreen|DoBlue;
    गवाक्षः->xcolor_bevel_d.red = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red - 22500, 0, 65535);
    गवाक्षः->xcolor_bevel_d.green = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green - 22500, 0, 65535);
    गवाक्षः->xcolor_bevel_d.blue = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue - 22500, 0, 65535);

    गवाक्षः->xcolor_pressed.flags = DoRed|DoGreen|DoBlue;
    गवाक्षः->xcolor_pressed.red = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].red - 12500, 0, 65535);
    गवाक्षः->xcolor_pressed.green = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].green - 12500, 0, 65535);
    गवाक्षः->xcolor_pressed.blue = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].blue - 12500, 0, 65535);

    गवाक्षः->xcolor_disabled_text.flags = DoRed|DoGreen|DoBlue;
    गवाक्षः->xcolor_disabled_text.red = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].red + 19500, 0, 65535);
    गवाक्षः->xcolor_disabled_text.green = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].green + 19500, 0, 65535);
    गवाक्षः->xcolor_disabled_text.blue = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].blue + 19500, 0, 65535);

    /* Screen */
    गवाक्षः->parent = parent;
    यदि (parent) {
        SDL_Display_दत्त *displaydata = SDL_Get_Display_Driver_दत्त_For_गवाक्षः(parent);
        गवाक्षः->screen = displaydata->screen;
    } अन्यथा {
        गवाक्षः->screen = DefaultScreen(गवाक्षः->display);
    }

    /* Visuals */
    यदि (बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_CHILD) {
        गवाक्षः->visual = parent->आन्तरिकम्->visual;
        गवाक्षः->cmap = parent->आन्तरिकम्->colormap;
        X11_GetVisualInfoFromVisual(गवाक्षः->display, गवाक्षः->visual, &गवाक्षः->vi);
        गवाक्षः->गभीरता_2 = गवाक्षः->vi.गभीरता_2;
    } अन्यथा {
        गवाक्षः->visual = DefaultVisual(गवाक्षः->display, गवाक्षः->screen);
        गवाक्षः->cmap = DefaultColormap(गवाक्षः->display, गवाक्षः->screen);
        गवाक्षः->गभीरता_2 = Default_गभीरता(गवाक्षः->display, गवाक्षः->screen);
        X11_GetVisualInfoFromVisual(गवाक्षः->display, गवाक्षः->visual, &गवाक्षः->vi);
    }

    /* Allocate colors */
    प्रति (i = 0; i < SDL_MESSAGEBOX_COLOR_गणनम्; i++) {
        X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &गवाक्षः->xcolor[i]);
    }
    X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &गवाक्षः->xcolor_bevel_l1);
    X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &गवाक्षः->xcolor_bevel_l2);
    X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &गवाक्षः->xcolor_bevel_d);
    X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &गवाक्षः->xcolor_pressed);
    X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &गवाक्षः->xcolor_disabled_text);

    /* Control list */
    गवाक्षः->has_focus = false;
    गवाक्षः->controls = रिक्त;
    गवाक्षः->controls_sz = 0;
    गवाक्षः->dyn_controls_sz = 0;
    गवाक्षः->fiddled_control = रिक्त;
    गवाक्षः->dyn_controls = रिक्त;

    /* Menu windows */
    गवाक्षः->popup_windows = रिक्त;

    /* BIDI engine */
#यदि_परिभाषितम् HAVE_FRIBIDI_H
    गवाक्षः->fribidi = SDL_FriBidi_Create();
#यदि_अन्तः

#यदि_परिभाषितम् HAVE_LIBTHAI_H
    गवाक्षः->th = SDL_LibThai_Create();
#यदि_अन्तः
    
    /* Interface direction */
    गवाक्षः->flip_interface = X11Toolkit_ShouldFlipUI();
    
    प्रत्यागम गवाक्षः;
}

स्थिर शून्य X11_Toolkit_सङ्कलय_Control_गन्तव्यम्_गवाक्षः(SDL_Toolkit_गवाक्षः_X11 *गवाक्षः, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    गवाक्षः->controls_sz++;
    यदि (गवाक्षः->controls_sz == 1) {
        गवाक्षः->controls = (संरचना SDL_ToolkitControlX11 **)SDL_malloc(परिमाण(संरचना SDL_ToolkitControlX11 *));
    } अन्यथा {
        गवाक्षः->controls = (संरचना SDL_ToolkitControlX11 **)SDL_realloc(गवाक्षः->controls, परिमाण(संरचना SDL_ToolkitControlX11 *) * गवाक्षः->controls_sz);
    }
    गवाक्षः->controls[गवाक्षः->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    यदि (control->dynamic) {
        गवाक्षः->dyn_controls_sz++;
        यदि (गवाक्षः->dyn_controls_sz == 1) {
            गवाक्षः->dyn_controls = (संरचना SDL_ToolkitControlX11 **)SDL_malloc(परिमाण(संरचना SDL_ToolkitControlX11 *));
        } अन्यथा {
            गवाक्षः->dyn_controls = (संरचना SDL_ToolkitControlX11 **)SDL_realloc(गवाक्षः->dyn_controls, परिमाण(संरचना SDL_ToolkitControlX11 *) * गवाक्षः->dyn_controls_sz);
        }
        गवाक्षः->dyn_controls[गवाक्षः->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    यदि (control->selected) {
        गवाक्षः->focused_control = control;
    }
}

bool X11_Toolkit_Create_गवाक्षः_Res(SDL_Toolkit_गवाक्षः_X11 *दत्त, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क cx, पूर्णाङ्क cy, वर्ण *title)
{
    पूर्णाङ्क x, y;
    XSizeHints *sizehints;
    XSet_गवाक्षः_गुणाः wnd_attr;
    Atom NET_WM_गवाक्षः_TYPE, NET_WM_गवाक्षः_TYPE_DIALOG, NET_WM_गवाक्षः_TYPE_DROPDOWN_MENU, NET_WM_गवाक्षः_TYPE_TOOLTIP;
    SDL_गवाक्षः_दत्त *windowdata = रिक्त;
    Display *display = दत्त->display;
    XGCValues ctx_vals;
    गवाक्षः_2 मूलम्_win;
    गवाक्षः_2 parent_win;
    अचिह्नित दीर्घ gcflags = GCForeground | GCBackground;
    अचिह्नित दीर्घ valuemask;
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
#यदि_परिभाषितम् XRANDR_DISABLED_BY_DEFAULT
    ध्रुव bool use_xrandr_by_default = false;
#अन्यथा
    ध्रुव bool use_xrandr_by_default = true;
#यदि_अन्तः
#यदि_अन्तः

    यदि (दत्त->scale == 0) {
        दत्त->गवाक्षः_विस्तारः = w;
        दत्त->गवाक्षः_height = h;
    } अन्यथा {
        दत्त->गवाक्षः_विस्तारः = SDL_lroundf((w/दत्त->iscale) * दत्त->scale);
        दत्त->गवाक्षः_height = SDL_lroundf((h/दत्त->iscale) * दत्त->scale);
        दत्त->pixmap_विस्तारः = w;
        दत्त->pixmap_height = h;
        दत्त->pixmap = true;
    }

    यदि (दत्त->parent) {
        windowdata = दत्त->parent->आन्तरिकम्;
    }

    valuemask = CWEvent_आवरणम् | CWColormap;
    दत्त->event_आवरणम् = Exposure_आवरणम् |
                       Button_Press_आवरणम् | Button_Release_आवरणम् | कुञ्चिका_Press_आवरणम् | कुञ्चिका_Release_आवरणम् |
                       Structure_Notify_आवरणम् | Focus_Change_आवरणम् | Pointer_Motion_आवरणम्;
    wnd_attr.event_आवरणम् = दत्त->event_आवरणम्;
    wnd_attr.colormap = दत्त->cmap;
    यदि (दत्त->बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_MENU || दत्त->बहुलकम्== SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    मूलम्_win = मूलम्_गवाक्षः(display, दत्त->screen);
    यदि (दत्त->बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_CHILD) {
        parent_win = windowdata->xwindow;
    } अन्यथा {
        parent_win = मूलम्_win;
    }

    दत्त->गवाक्षः = X11_XCreate_गवाक्षः(
        display, parent_win,
        0, 0,
        दत्त->गवाक्षः_विस्तारः, दत्त->गवाक्षः_height,
        0, दत्त->गभीरता_2, निवेशः_Output, दत्त->visual,
        valuemask, &wnd_attr);
    यदि (दत्त->गवाक्षः == None) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't create X window");
    }

    यदि (windowdata && दत्त->बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_DIALOG) {
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
        X11_XChangeProperty(display, दत्त->गवाक्षः, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_बहुलकम्_Replace, (अचिह्नित वर्ण *)stateatoms, statecount);
    }

    यदि (windowdata && दत्त->बहुलकम् != SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_CHILD) {
        X11_XSetTransientForHint(display, दत्त->गवाक्षः, windowdata->xwindow);
    }

    यदि (दत्त->tk_parent) {
        X11_XSetTransientForHint(display, दत्त->गवाक्षः, दत्त->tk_parent->गवाक्षः);
    }

    SDL_X11_समुच्चयः_गवाक्षः_Title(display, दत्त->गवाक्षः, title);

    // Let the window manager the type of the window
    यदि (दत्त->बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_DIALOG) {
        NET_WM_गवाक्षः_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_गवाक्षः_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, दत्त->गवाक्षः, NET_WM_गवाक्षः_TYPE, XA_ATOM, 32,
                            Prop_बहुलकम्_Replace,
                            (अचिह्नित वर्ण *)&NET_WM_गवाक्षः_TYPE_DIALOG, 1);
    } अन्यथा यदि (दत्त->बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_MENU) {
        NET_WM_गवाक्षः_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_गवाक्षः_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, दत्त->गवाक्षः, NET_WM_गवाक्षः_TYPE, XA_ATOM, 32,
                            Prop_बहुलकम्_Replace,
                            (अचिह्नित वर्ण *)&NET_WM_गवाक्षः_TYPE_DROPDOWN_MENU, 1);
    } अन्यथा यदि (दत्त->बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_TOOLTIP) {
        NET_WM_गवाक्षः_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_गवाक्षः_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, दत्त->गवाक्षः, NET_WM_गवाक्षः_TYPE, XA_ATOM, 32,
                            Prop_बहुलकम्_Replace,
                            (अचिह्नित वर्ण *)&NET_WM_गवाक्षः_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    दत्त->wm_delete_सन्देशः = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, दत्त->गवाक्षः, &दत्त->wm_delete_सन्देशः, 1);
    दत्त->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    यदि (दत्त->बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_MENU || दत्त->बहुलकम्== SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_TOOLTIP) {
        x = cx;
        y = cy;
        गच्छ MOVEWINDOW;
    }
    यदि (windowdata) {
        XWindow_गुणाः attrib;
        गवाक्षः_2 dummy;

        X11_XGet_गवाक्षः_गुणाः(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.विस्तारः - दत्त->गवाक्षः_विस्तारः) / 2;
        y = attrib.y + (attrib.height - दत्त->गवाक्षः_height) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, मूलम्_गवाक्षः(display, दत्त->screen), x, y, &x, &y, &dummy);
    } अन्यथा {
        ध्रुव SDL_VideoDevice *dev = SDL_GetVideoDevice();
        यदि (dev && dev->displays && dev->अङ्कः_displays > 0) {
            ध्रुव SDL_VideoDisplay *dpy = dev->displays[0];
            ध्रुव SDL_Display_दत्त *dpydata = dpy->आन्तरिकम्;
            x = dpydata->x + ((dpy->current_बहुलकम्->w - दत्त->गवाक्षः_विस्तारः) / 2);
            y = dpydata->y + ((dpy->current_बहुलकम्->h - दत्त->गवाक्षः_height) / 3);
        }
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
        अन्यथा यदि (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && दत्त->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_बहिर्गमनम्;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, मूलम्_win);
            यदि (!screen_res) {
                गच्छ NOXRANDR;
            }

            default_बहिर्गमनम् = X11_XRRGetOutputPrimary(display, मूलम्_win);
            यदि (default_बहिर्गमनम् != None) {
                XRROutputInfo *बहिर्गमनम्_info;

                बहिर्गमनम्_info = X11_XRRGetOutputInfo(display, screen_res, default_बहिर्गमनम्);
                यदि (बहिर्गमनम्_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(बहिर्गमनम्_info);
                    गच्छ FIRSTOUTPUTXRANDR;
                }

                यदि (बहिर्गमनम्_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, बहिर्गमनम्_info->crtc);
                } अन्यथा यदि (बहिर्गमनम्_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, बहिर्गमनम्_info->crtcs[0]);
                } अन्यथा {
                    crtc_info = रिक्त;
                }
                
                यदि (crtc_info) {
                    x = (crtc_info->विस्तारः - दत्त->गवाक्षः_विस्तारः) / 2;
                    y = (crtc_info->height - दत्त->गवाक्षः_height) / 3;
                    X11_XRRFreeOutputInfo(बहिर्गमनम्_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } अन्यथा {
                    X11_XRRFreeOutputInfo(बहिर्गमनम्_info);
                    गच्छ NOXRANDR;
                }
            } अन्यथा {
                    FIRSTOUTPUTXRANDR:
                    यदि (screen_res->noutput > 0) {
                        XRROutputInfo *बहिर्गमनम्_info;

                        बहिर्गमनम्_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        यदि (!बहिर्गमनम्_info) {
                            गच्छ FIRSTCRTCXRANDR;
                        }

                        यदि (बहिर्गमनम्_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, बहिर्गमनम्_info->crtc);
                        } अन्यथा यदि (बहिर्गमनम्_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, बहिर्गमनम्_info->crtcs[0]);
                        } अन्यथा {
                            crtc_info = रिक्त;
                        }

                        यदि (!crtc_info) {
                            X11_XRRFreeOutputInfo(बहिर्गमनम्_info);
                            गच्छ FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->विस्तारः - दत्त->गवाक्षः_विस्तारः) / 2;
                        y = (crtc_info->height - दत्त->गवाक्षः_height) / 3;
                        X11_XRRFreeOutputInfo(बहिर्गमनम्_info);
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
                        x = (crtc_info->विस्तारः - दत्त->गवाक्षः_विस्तारः) / 2;
                        y = (crtc_info->height - दत्त->गवाक्षः_height) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } अन्यथा {
                        X11_XRRFreeScreenResources(screen_res);
                        गच्छ NOXRANDR;
                    }
            }
        }
#यदि_अन्तः
        अन्यथा {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (Display_विस्तारः(display, दत्त->screen) - दत्त->गवाक्षः_विस्तारः) / 2;
            y = (DisplayHeight(display, दत्त->screen) - दत्त->गवाक्षः_height) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMove_गवाक्षः(display, दत्त->गवाक्षः, x, y);
    दत्त->गवाक्षः_x = x;
    दत्त->गवाक्षः_y = y;

    sizehints = X11_XAlloc_आकार_Hints();
    यदि (sizehints) {
        sizehints->flags = USPosition | USSize | PMax_आकार | PMin_आकार;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->विस्तारः = दत्त->गवाक्षः_विस्तारः;
        sizehints->height = दत्त->गवाक्षः_height;

        sizehints->min_विस्तारः_2 = sizehints->max_विस्तारः_2 = दत्त->गवाक्षः_विस्तारः;
        sizehints->min_height = sizehints->max_height = दत्त->गवाक्षः_height;

        X11_XSetWMNormalHints(display, दत्त->गवाक्षः, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, दत्त->गवाक्षः);

    दत्त->drawable = दत्त->गवाक्षः;
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    यदि (SDL_X11_HAVE_XDBE && !दत्त->pixmap) {
        पूर्णाङ्क xdbe_major, xdbe_minor;
        यदि (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            दत्त->xdbe = true;
            दत्त->buf = X11_Xdbe_Allocate_पृष्ठभागः_बफर_Name(display, दत्त->गवाक्षः, XdbeUndefined);
            दत्त->drawable = दत्त->buf;
        } अन्यथा {
            दत्त->xdbe = false;
        }
    }
#यदि_अन्तः

    X11_Toolkit_Init_गवाक्षः_Pixmap(दत्त);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = दत्त->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = दत्त->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    यदि (!दत्त->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = दत्त->font_struct->fid;
    }
    दत्त->ctx = X11_XCreateGC(दत्त->display, दत्त->drawable, gcflags, &ctx_vals);
    यदि (दत्त->ctx == None) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't create graphics context");
    }

    दत्त->close = false;
    दत्त->कुञ्चिका_control_esc = दत्त->कुञ्चिका_control_enter = रिक्त;
    यदि (!दत्त->pixmap) {
        दत्त->ev_scale = दत्त->ev_iscale = 1;
    } अन्यथा {
        दत्त->ev_scale = दत्त->scale;
        दत्त->ev_iscale = दत्त->iscale;
    }

#यदि SDL_GRAB
    यदि (दत्त->बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_MENU || दत्त->बहुलकम्== SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_TOOLTIP) {
        X11_XGrabPointer(display, दत्त->गवाक्षः, False, Button_Press_आवरणम् | Button_Release_आवरणम् | Pointer_Motion_आवरणम्, Grab_बहुलकम्_Async, Grab_बहुलकम्_Async, None, None, CurrentTime);
        X11_XGrabKeyboard(display, दत्त->गवाक्षः, False, Grab_बहुलकम्_Async, Grab_बहुलकम्_Async, CurrentTime);
    }
#यदि_अन्तः

    प्रत्यागम true;
}

स्थिर शून्य X11_Toolkit_Draw_गवाक्षः(SDL_Toolkit_गवाक्षः_X11 *दत्त) {
    SDL_Rect rect;
    पूर्णाङ्क i;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XDBE
    यदि (SDL_X11_HAVE_XDBE && दत्त->xdbe && !दत्त->pixmap) {
        X11_XdbeBeginIdiom(दत्त->display);
    }
#यदि_अन्तः

    X11_XSetForeground(दत्त->display, दत्त->ctx, दत्त->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    यदि (दत्त->pixmap) {
        X11_XFillRectangle(दत्त->display, दत्त->drawable, दत्त->ctx, 0, 0, दत्त->pixmap_विस्तारः, दत्त->pixmap_height);
    } अन्यथा {
        X11_XFillRectangle(दत्त->display, दत्त->drawable, दत्त->ctx, 0, 0, दत्त->गवाक्षः_विस्तारः, दत्त->गवाक्षः_height);
    }

    प्रति (i = 0; i < दत्त->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = दत्त->controls[i];
        यदि (control) {
            यदि (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XDBE
    यदि (SDL_X11_HAVE_XDBE && दत्त->xdbe && !दत्त->pixmap) {
        XdbeSwapInfo swap_info;
        swap_info.swap_गवाक्षः = दत्त->गवाक्षः;
        swap_info.swap_action = XdbeUndefined;
        X11_XdbeSwapBuffers(दत्त->display, &swap_info, 1);
        X11_Xdbe_अन्तः_Idiom(दत्त->display);
    }
#यदि_अन्तः

    यदि (दत्त->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = दत्त->गवाक्षः_विस्तारः;
        rect.h = दत्त->गवाक्षः_height;
#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
        यदि (दत्त->shm) {
            यदि (दत्त->shm_pixmap) {
                X11_XFlush(दत्त->display);
                X11_XSync(दत्त->display, false);
                scale_surface = SDL_CreateSurfaceFrom(दत्त->pixmap_विस्तारः, दत्त->pixmap_height, X11_GetPixelFormatFromVisualInfo(दत्त->display, &दत्त->vi), दत्त->shm_info.shmaddr, दत्त->shm_अष्टकानि_प्रत्येकम्_पङ्क्तिः);
                SDL_BlitSurfaceScaled(scale_surface, रिक्त, scale_surface, &rect, SDL_SCALEMODE_रैखिकम्);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(दत्त->display, दत्त->drawable, दत्त->गवाक्षः, दत्त->ctx, 0, 0, दत्त->गवाक्षः_विस्तारः, दत्त->गवाक्षः_height, 0, 0);
            } अन्यथा {
                X11_XShmGetImage(दत्त->display, दत्त->drawable, दत्त->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(दत्त->pixmap_विस्तारः, दत्त->pixmap_height, X11_GetPixelFormatFromVisualInfo(दत्त->display, &दत्त->vi), दत्त->image->दत्त, दत्त->image->अष्टकानि_प्रत्येकम्_पङ्क्तिः);
                SDL_BlitSurfaceScaled(scale_surface, रिक्त, scale_surface, &rect, SDL_SCALEMODE_रैखिकम्);
                X11_XShmPutImage(दत्त->display, दत्त->गवाक्षः, दत्त->ctx, दत्त->image, 0, 0, 0, 0, दत्त->गवाक्षः_विस्तारः, दत्त->गवाक्षः_height, False);
            }
        } अन्यथा
#यदि_अन्तः
        {
            XImage *image;

            image = X11_XGetImage(दत्त->display, दत्त->drawable, 0, 0 , दत्त->pixmap_विस्तारः, दत्त->pixmap_height, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(दत्त->pixmap_विस्तारः, दत्त->pixmap_height, X11_GetPixelFormatFromVisualInfo(दत्त->display, &दत्त->vi), image->दत्त, image->अष्टकानि_प्रत्येकम्_पङ्क्तिः);
            SDL_BlitSurfaceScaled(scale_surface, रिक्त, scale_surface, &rect, SDL_SCALEMODE_रैखिकम्);
            X11_XPutImage(दत्त->display, दत्त->गवाक्षः, दत्त->ctx, image, 0, 0, 0, 0, दत्त->गवाक्षः_विस्तारः, दत्त->गवाक्षः_height);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(दत्त->display);
}

स्थिर SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_Toolkit_गवाक्षः_X11 *दत्त, पूर्णाङ्क x, पूर्णाङ्क y)
{
    पूर्णाङ्क i;

    प्रति (i = 0; i < दत्त->controls_sz; i++) {
        SDL_Rect *rect = &दत्त->controls[i]->rect;
        यदि ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            प्रत्यागम दत्त->controls[i];
        }
    }

    प्रत्यागम रिक्त;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
स्थिर Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_Toolkit_गवाक्षः_X11 *दत्त = (SDL_Toolkit_गवाक्षः_X11 *)arg;

    यदि (event->xany.display != दत्त->display) {
        प्रत्यागम False;
    }

    यदि (event->xany.गवाक्षः == दत्त->गवाक्षः) {
        प्रत्यागम True;
    }

    प्रत्यागम False;
}

शून्य X11_Toolkit_Process_गवाक्षः_Events(SDL_Toolkit_गवाक्षः_X11 *दत्त, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    यदि ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        प्रत्यागम;
    }

    दत्त->draw = false;
    दत्त->e = e;

    विकल्प (e->type) {
        पक्ष Expose:
            दत्त->draw = true;
            भङ्ग;
        पक्ष Client_सन्देशः:
            यदि (e->xclient.सन्देशः_type == दत्त->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.दत्त.l[0] == दत्त->wm_delete_सन्देशः) {
                दत्त->close = true;
            }
            भङ्ग;
        पक्ष Focus_अन्तर्:
            दत्त->has_focus = true;
            भङ्ग;
        पक्ष Focus_बहिर्गमनम्:
            दत्त->has_focus = false;
            यदि (दत्त->fiddled_control) {
                दत्त->fiddled_control->selected = false;
            }
            दत्त->fiddled_control = रिक्त;
            प्रति (दत्त->ev_i = 0; दत्त->ev_i < दत्त->controls_sz; दत्त->ev_i++) {
                दत्त->controls[दत्त->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_प्रसामान्यम्;
            }
            भङ्ग;
        पक्ष MotionNotify:
            यदि (दत्त->has_focus) {
                दत्त->previous_control = दत्त->fiddled_control;
                दत्त->fiddled_control = X11Toolkit_GetControlMouseIsOn(दत्त, SDL_lroundf((e->xbutton.x/ दत्त->ev_scale)* दत्त->ev_iscale), SDL_lroundf((e->xbutton.y/ दत्त->ev_scale)* दत्त->ev_iscale));
                यदि (दत्त->previous_control) {
                    दत्त->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_प्रसामान्यम्;
                    यदि (दत्त->previous_control->func_on_state_change) {
                        दत्त->previous_control->func_on_state_change(दत्त->previous_control);
                    }
                    दत्त->draw = true;
                }
                यदि (दत्त->fiddled_control) {
                    यदि (दत्त->fiddled_control->dynamic) {
                        दत्त->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        यदि (दत्त->fiddled_control->func_on_state_change) {
                            दत्त->fiddled_control->func_on_state_change(दत्त->fiddled_control);
                        }
                        दत्त->draw = true;
                    } अन्यथा {
                        दत्त->fiddled_control = रिक्त;
                    }
                }
            }
            भङ्ग;
        पक्ष ButtonPress:
            दत्त->previous_control = दत्त->fiddled_control;
            यदि (दत्त->previous_control) {
                दत्त->previous_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_प्रसामान्यम्;
                यदि (दत्त->previous_control->func_on_state_change) {
                    दत्त->previous_control->func_on_state_change(दत्त->previous_control);
                }
                दत्त->draw = true;
            }
            यदि (e->xbutton.button == Button1) {
                दत्त->fiddled_control = X11Toolkit_GetControlMouseIsOn(दत्त, SDL_lroundf((e->xbutton.x/ दत्त->ev_scale)* दत्त->ev_iscale), SDL_lroundf((e->xbutton.y/ दत्त->ev_scale)* दत्त->ev_iscale));
                यदि (दत्त->fiddled_control) {
                    दत्त->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    यदि (दत्त->fiddled_control->func_on_state_change) {
                        दत्त->fiddled_control->func_on_state_change(दत्त->fiddled_control);
                    }
                    दत्त->draw = true;
                }
            }
            भङ्ग;
        पक्ष ButtonRelease:
            यदि (दत्त->बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_MENU || दत्त->बहुलकम्== SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_TOOLTIP) {
                पूर्णाङ्क cx;
                पूर्णाङ्क cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                यदि (cy < 0 || cx < 0) {
                    दत्त->close = true;
                }

                यदि (cy > दत्त->गवाक्षः_height || cx > दत्त->गवाक्षः_विस्तारः) {
                    दत्त->close = true;
                }
            }

            यदि ((e->xbutton.button == Button1) && (दत्त->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(दत्त, SDL_lroundf((e->xbutton.x/ दत्त->ev_scale)* दत्त->ev_iscale), SDL_lroundf((e->xbutton.y/ दत्त->ev_scale)* दत्त->ev_iscale));
                यदि (दत्त->fiddled_control == control) {
                    दत्त->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    यदि (दत्त->fiddled_control->func_on_state_change) {
                        दत्त->fiddled_control->func_on_state_change(दत्त->fiddled_control);
                    }
                    दत्त->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_प्रसामान्यम्;
                    दत्त->draw = true;
                }
            }
            भङ्ग;
        पक्ष कुञ्चिका_Press:
            दत्त->चरमः_कुञ्चिका_pressed = X11_XLookupKeysym(&e->xkey, 0);

            यदि (दत्त->चरमः_कुञ्चिका_pressed == XK_Escape) {
                प्रति (दत्त->ev_i = 0; दत्त->ev_i < दत्त->controls_sz; दत्त->ev_i++) {
                    यदि(दत्त->controls[दत्त->ev_i]->is_default_esc) {
                        दत्त->controls[दत्त->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        दत्त->draw = true;
                        दत्त->कुञ्चिका_control_esc = दत्त->controls[दत्त->ev_i];
                    }
                }
            } अन्यथा यदि ((दत्त->चरमः_कुञ्चिका_pressed == XK_Return) || (दत्त->चरमः_कुञ्चिका_pressed == XK_KP_Enter)) {
                प्रति (दत्त->ev_i = 0; दत्त->ev_i < दत्त->controls_sz; दत्त->ev_i++) {
                    यदि(दत्त->controls[दत्त->ev_i]->selected) {
                        दत्त->controls[दत्त->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        दत्त->draw = true;
                        दत्त->कुञ्चिका_control_enter = दत्त->controls[दत्त->ev_i];
                    }
                }
            }
            भङ्ग;
        पक्ष कुञ्चिका_Release:
        {
            कुञ्चिका_Sym कुञ्चिका = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            यदि (कुञ्चिका != दत्त->चरमः_कुञ्चिका_pressed) {
                भङ्ग;
            }

            यदि (कुञ्चिका == XK_Escape) {
                यदि (दत्त->कुञ्चिका_control_esc) {
                    यदि (दत्त->कुञ्चिका_control_esc->func_on_state_change) {
                        दत्त->कुञ्चिका_control_esc->func_on_state_change(दत्त->कुञ्चिका_control_esc);
                    }
                }
            } अन्यथा यदि ((कुञ्चिका == XK_Return) || (कुञ्चिका == XK_KP_Enter)) {
                यदि (दत्त->कुञ्चिका_control_enter) {
                    यदि (दत्त->कुञ्चिका_control_enter->func_on_state_change) {
                        दत्त->कुञ्चिका_control_enter->func_on_state_change(दत्त->कुञ्चिका_control_enter);
                    }
                }
            } अन्यथा यदि (कुञ्चिका == XK_Tab || कुञ्चिका == XK_वामः || कुञ्चिका == XK_दक्षिणः) {
                यदि (दत्त->focused_control) {
                    दत्त->focused_control->selected = false;
                }
                दत्त->draw = true;
                प्रति (दत्त->ev_i = 0; दत्त->ev_i < दत्त->dyn_controls_sz; दत्त->ev_i++) {
                    यदि (दत्त->dyn_controls[दत्त->ev_i] == दत्त->focused_control) {
                        पूर्णाङ्क अग्र_सूचकांक;

                        यदि (कुञ्चिका == XK_वामः) {
                            अग्र_सूचकांक = दत्त->ev_i - 1;
                        } अन्यथा {
                            अग्र_सूचकांक = दत्त->ev_i + 1;
                        }
                        यदि ((अग्र_सूचकांक >= दत्त->dyn_controls_sz) || (अग्र_सूचकांक < 0)) {
                            यदि (कुञ्चिका == XK_दक्षिणः || कुञ्चिका == XK_वामः) {
                                अग्र_सूचकांक = दत्त->ev_i;
                            } अन्यथा {
                                अग्र_सूचकांक = 0;
                            }
                        }
                        दत्त->focused_control = दत्त->dyn_controls[अग्र_सूचकांक];
                        दत्त->focused_control->selected = true;
                        भङ्ग;
                    }
                }
            }
            भङ्ग;
        }
    }

    यदि (दत्त->draw) {
        X11_Toolkit_Draw_गवाक्षः(दत्त);
    }
}

शून्य X11_Toolkit_Do_गवाक्षः_Event_Loop(SDL_Toolkit_गवाक्षः_X11 *दत्त) {
   यावत् (!दत्त->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(दत्त->display, &e);
        यदि (दत्त->xsettings) {
            xsettings_client_process_event(दत्त->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(दत्त->display, &e, X11Toolkit_EventTest, (XPointer)दत्त);
        X11_Toolkit_Process_गवाक्षः_Events(दत्त, &e);
    }
}


शून्य X11_Toolkit_Resize_गवाक्षः(SDL_Toolkit_गवाक्षः_X11 *दत्त, पूर्णाङ्क w, पूर्णाङ्क h) {
    यदि (!दत्त->pixmap) {
        दत्त->गवाक्षः_विस्तारः = w;
        दत्त->गवाक्षः_height = h;
    } अन्यथा {
        दत्त->गवाक्षः_विस्तारः = SDL_lroundf((w/दत्त->iscale) * दत्त->scale);
        दत्त->गवाक्षः_height = SDL_lroundf((h/दत्त->iscale) * दत्त->scale);
        दत्त->pixmap_विस्तारः = w;
        दत्त->pixmap_height = h;
        X11_XFreePixmap(दत्त->display, दत्त->drawable);
        X11_Toolkit_Init_गवाक्षः_Pixmap(दत्त);
    }

    X11_XResize_गवाक्षः(दत्त->display, दत्त->गवाक्षः, दत्त->गवाक्षः_विस्तारः, दत्त->गवाक्षः_height);
}

स्थिर शून्य X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->गवाक्षः->display, icon_control->icon_char_font);
    SDL_free(control);
}

स्थिर शून्य X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->गवाक्षः->iscale;
    control->rect.h -= 2 * control->गवाक्षः->iscale;
    X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx, control->rect.x + (2 * control->गवाक्षः->iscale), control->rect.y + (2* control->गवाक्षः->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    विकल्प (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        पक्ष SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx, control->rect.x+(1* control->गवाक्षः->iscale), control->rect.y+(1* control->गवाक्षः->iscale), control->rect.w-(2* control->गवाक्षः->iscale), control->rect.h-(2* control->गवाक्षः->iscale), 0, 360 * 64);
                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, icon_control->xcolor_white.pixel);
                भङ्ग;
        पक्ष SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx, control->rect.x+(1* control->गवाक्षः->iscale), control->rect.y+(1* control->गवाक्षः->iscale), control->rect.w-(2* control->गवाक्षः->iscale), control->rect.h-(2* control->गवाक्षः->iscale), 0, 360 * 64);
                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, icon_control->xcolor_black.pixel);
                भङ्ग;
        पक्ष SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx, control->rect.x+(1* control->गवाक्षः->iscale), control->rect.y+(1* control->गवाक्षः->iscale), control->rect.w-(2* control->गवाक्षः->iscale), control->rect.h-(2* control->गवाक्षः->iscale), 0, 360 * 64);
                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, icon_control->xcolor_white.pixel);
                भङ्ग;
    }
    X11_XSetFont(control->गवाक्षः->display, control->गवाक्षः->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    यदि (!control->गवाक्षः->utf8) {
        X11_XSetFont(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->font_struct->fid);
    }

    control->rect.w += 2 * control->गवाक्षः->iscale;
    control->rect.h += 2 * control->गवाक्षः->iscale;
}

स्थिर शून्य X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *आधारः_control) {
    SDL_ToolkitIconControlX11 *control;
    पूर्णाङ्क icon_char_w;
    पूर्णाङ्क icon_wh;

    control = (SDL_ToolkitIconControlX11 *)आधारः_control;
    X11_Toolkit_Get_Text_विस्तारः_Height_For_Font(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, रिक्त);
    आधारः_control->rect.w = icon_char_w;
    आधारः_control->rect.h = control->icon_char_h;
    icon_wh = SDL_max(icon_char_w, control->icon_char_h) + SDL_TOOLKIT_X11_ELEMENT_PADDING * 2 * आधारः_control->गवाक्षः->iscale;
    आधारः_control->rect.w = icon_wh;
    आधारः_control->rect.h = icon_wh;
    आधारः_control->rect.y = 0;
    आधारः_control->rect.x = 0;
    control->icon_char_y = control->icon_char_a + (आधारः_control->rect.h - control->icon_char_h)/2;
    control->icon_char_x = (आधारः_control->rect.w - icon_char_w)/2;
    आधारः_control->rect.w += 2 * आधारः_control->गवाक्षः->iscale;
    आधारः_control->rect.h += 2 * आधारः_control->गवाक्षः->iscale;
}

स्थिर शून्य X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *आधारः_control) {
    SDL_ToolkitIconControlX11 *control;
    वर्ण *font;

    control = (SDL_ToolkitIconControlX11 *)आधारः_control;
    X11_XFreeFont(आधारः_control->गवाक्षः->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_आकार * आधारः_control->गवाक्षः->iscale);
    control->icon_char_font = X11_XLoadQueryFont(आधारः_control->गवाक्षः->display, font);
    SDL_free(font);
    यदि (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_आकार * आधारः_control->गवाक्षः->iscale);
        control->icon_char_font = X11_XLoadQueryFont(आधारः_control->गवाक्षः->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_गवाक्षः_X11 *गवाक्षः, SDL_सन्देशः_Box_Flags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *आधारः_control;
    वर्ण *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(परिमाण(SDL_ToolkitIconControlX11));
    आधारः_control = (SDL_ToolkitControlX11 *)control;
    यदि (!control) {
        SDL_समुच्चयः_Error("Unable to allocate icon control structure");
        प्रत्यागम रिक्त;
    }

    /* Fill out struct */
    आधारः_control->गवाक्षः = गवाक्षः;
    आधारः_control->func_draw = X11Toolkit_DrawIconControl;
    आधारः_control->func_free = X11Toolkit_DestroyIconControl;
    आधारः_control->func_on_state_change = रिक्त;
    आधारः_control->func_calc_आकार = X11Toolkit_CalculateIconControl;
    आधारः_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    आधारः_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_प्रसामान्यम्;
    आधारः_control->selected = false;
    आधारः_control->dynamic = false;
    आधारः_control->is_default_enter = false;
    आधारः_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_आकार * गवाक्षः->iscale);
    control->icon_char_font = X11_XLoadQueryFont(गवाक्षः->display, font);
    SDL_free(font);
    यदि (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_आकार * गवाक्षः->iscale);
        control->icon_char_font = X11_XLoadQueryFont(गवाक्षः->display, font);
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
        X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &control->xcolor_white);
        X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &control->xcolor_red);
        X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &control->xcolor_red_darker);
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
        X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &control->xcolor_black);
        X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &control->xcolor_yellow);
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
        X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &control->xcolor_white);
        X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &control->xcolor_blue);
        भङ्ग;
    स्वभाव:
        X11_XFreeFont(गवाक्षः->display, control->icon_char_font);
        SDL_free(control);
        प्रत्यागम रिक्त;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    यदि (गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } अन्यथा यदि (गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } अन्यथा {
        control->xcolor_bg_shadow.red = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    यदि (गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } अन्यथा यदि (गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } अन्यथा {
        control->xcolor_bg_shadow.green = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    यदि (गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } अन्यथा यदि (गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } अन्यथा {
        control->xcolor_bg_shadow.blue = SDL_clamp(गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(गवाक्षः->display, गवाक्षः->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(आधारः_control);

    X11_Toolkit_सङ्कलय_Control_गन्तव्यम्_गवाक्षः(गवाक्षः, आधारः_control);
    प्रत्यागम आधारः_control;
}

bool X11_Toolkit_Notify_Control_सम्बन्धि_आकार_Change(SDL_ToolkitControlX11 *control) {
    यदि (control->func_calc_आकार) {
        control->func_calc_आकार(control);
        प्रत्यागम true;
    } अन्यथा {
        प्रत्यागम false;
    }
}

स्थिर शून्य X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11Toolkit_GetTextElementsRect(button_control->text, &button_control->text_rect);
    यदि (control->do_आकार) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->गवाक्षः->iscale + button_control->text_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->गवाक्षः->iscale + button_control->text_rect.h;
    }
    button_control->text_rect.x = (control->rect.w - button_control->text_rect.w)/2;
    button_control->text_rect.y = (control->rect.h - button_control->text_rect.h)/2;
}


स्थिर शून्य X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    /* Draw bevel */
    यदि (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
            X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor_bevel_d.pixel);
            X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

            X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor_bevel_l2.pixel);
            X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - (1* control->गवाक्षः->iscale), control->rect.h - (1* control->गवाक्षः->iscale));

            X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor_bevel_l1.pixel);
            X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x + 1 * control->गवाक्षः->iscale, control->rect.y + 1 * control->गवाक्षः->iscale,
                                   control->rect.w - 3 * control->गवाक्षः->iscale, control->rect.h - 2 * control->गवाक्षः->iscale);

            X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
            X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                               control->rect.x + 1 * control->गवाक्षः->iscale, control->rect.y + 1 * control->गवाक्षः->iscale,
                               control->rect.w - 3 * control->गवाक्षः->iscale, control->rect.h - 3 * control->गवाक्षः->iscale);

            X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor_pressed.pixel);
            X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                               control->rect.x + 2 * control->गवाक्षः->iscale, control->rect.y + 2 * control->गवाक्षः->iscale,
                               control->rect.w - 4 * control->गवाक्षः->iscale, control->rect.h - 4 * control->गवाक्षः->iscale);
        } अन्यथा {
            यदि (control->selected) {
                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x + 1 * control->गवाक्षः->iscale, control->rect.y + 1 * control->गवाक्षः->iscale,
                                   control->rect.w - 3 * control->गवाक्षः->iscale, control->rect.h - 3 * control->गवाक्षः->iscale);

                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x + 2 * control->गवाक्षः->iscale, control->rect.y + 2 * control->गवाक्षः->iscale,
                                   control->rect.w - 4 * control->गवाक्षः->iscale, control->rect.h - 4 * control->गवाक्षः->iscale);

                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x + 2 * control->गवाक्षः->iscale, control->rect.y + 2 * control->गवाक्षः->iscale,
                                   control->rect.w - 5 * control->गवाक्षः->iscale, control->rect.h - 5 * control->गवाक्षः->iscale);

                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x + 3 * control->गवाक्षः->iscale, control->rect.y + 3 * control->गवाक्षः->iscale,
                                   control->rect.w - 6 * control->गवाक्षः->iscale, control->rect.h - 6 * control->गवाक्षः->iscale);
            } अन्यथा {
                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - 1 * control->गवाक्षः->iscale, control->rect.h - 1 * control->गवाक्षः->iscale);

                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x + 1 * control->गवाक्षः->iscale, control->rect.y + 1 * control->गवाक्षः->iscale,
                                   control->rect.w - 2 * control->गवाक्षः->iscale, control->rect.h - 2 * control->गवाक्षः->iscale);

                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x + 1 * control->गवाक्षः->iscale, control->rect.y + 1 * control->गवाक्षः->iscale,
                                   control->rect.w - 3 * control->गवाक्षः->iscale, control->rect.h - 3 * control->गवाक्षः->iscale);

                X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->गवाक्षः->display, control->गवाक्षः->drawable, control->गवाक्षः->ctx,
                                   control->rect.x + 2 * control->गवाक्षः->iscale, control->rect.y + 2 * control->गवाक्षः->iscale,
                                   control->rect.w - 4 * control->गवाक्षः->iscale, control->rect.h - 4 * control->गवाक्षः->iscale);
            }
        }

    X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    X11Toolkit_DrawTextElements(control->गवाक्षः, button_control->text, control->rect.x + button_control->text_rect.x, control->rect.y + button_control->text_rect.y);
}

स्थिर शून्य X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    यदि (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_दत्त);
    }
}

स्थिर शून्य X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11Toolkit_FreeTextElements(button_control->text);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_गवाक्षः_X11 *गवाक्षः, ध्रुव SDL_सन्देशः_Box_Button_दत्त *दत्त) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *आधारः_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(परिमाण(SDL_ToolkitButtonControlX11));
    आधारः_control = (SDL_ToolkitControlX11 *)control;
    यदि (!control) {
        SDL_समुच्चयः_Error("Unable to allocate button control structure");
        प्रत्यागम रिक्त;
    }
    आधारः_control->गवाक्षः = गवाक्षः;
    आधारः_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_प्रसामान्यम्;
    आधारः_control->func_calc_आकार = X11Toolkit_CalculateButtonControl;
    आधारः_control->func_draw = X11Toolkit_DrawButtonControl;
    आधारः_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    आधारः_control->func_free = X11Toolkit_DestroyButtonControl;
    आधारः_control->func_on_scale_change = रिक्त;
    आधारः_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_प्रसामान्यम्;
    आधारः_control->selected = false;
    आधारः_control->dynamic = true;
    आधारः_control->is_default_enter = false;
    आधारः_control->is_default_esc = false;
    यदि (दत्त->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        आधारः_control->is_default_esc = true;
    }
    यदि (दत्त->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        आधारः_control->is_default_enter = true;
        आधारः_control->selected = true;
    }
    control->cb = रिक्त;
    control->दत्त = दत्त;
#यदि_परिभाषितम् HAVE_FRIBIDI_H
    control->text = X11Toolkit_MakeTextElements(आधारः_control->गवाक्षः, (वर्ण *)control->दत्त->text, SDL_strlen(control->दत्त->text), रिक्त);
#अन्यथा 
    control->text = X11Toolkit_MakeTextElements(आधारः_control->गवाक्षः, (वर्ण *)control->दत्त->text, SDL_strlen(control->दत्त->text));
#यदि_अन्तः
    X11Toolkit_ShapeTextElements(आधारः_control->गवाक्षः, control->text);
    
    आधारः_control->do_आकार = true;
    X11Toolkit_CalculateButtonControl(आधारः_control);
    आधारः_control->do_आकार = false;

    X11_Toolkit_सङ्कलय_Control_गन्तव्यम्_गवाक्षः(गवाक्षः, आधारः_control);
    प्रत्यागम आधारः_control;
}

शून्य X11_Toolkit_पञ्जिकाकोशः_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, शून्य *दत्त, शून्य (*cb)(संरचना SDL_ToolkitControlX11 *, शून्य *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_दत्त = दत्त;
    button_control->cb = cb;
}

ध्रुव SDL_सन्देशः_Box_Button_दत्त *X11_Toolkit_Get_Button_Control_दत्त(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    प्रत्यागम button_control->दत्त;
}

शून्य X11_Toolkit_Destroy_गवाक्षः(SDL_Toolkit_गवाक्षः_X11 *दत्त) {
    पूर्णाङ्क i;

    यदि (!दत्त) {
        प्रत्यागम;
    }

#यदि SDL_GRAB
    यदि (दत्त->बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_MENU || दत्त->बहुलकम्== SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_TOOLTIP) {
        X11_XUngrabPointer(दत्त->display, CurrentTime);
        X11_XUngrabKeyboard(दत्त->display, CurrentTime);
    }
#यदि_अन्तः

    प्रति (i = 0; i < दत्त->controls_sz; i++) {
        यदि (दत्त->controls[i]->func_free) {
            दत्त->controls[i]->func_free(दत्त->controls[i]);
        }
    }
    SDL_free(दत्त->controls);
    SDL_free(दत्त->dyn_controls);

    यदि (दत्त->popup_windows) {
        SDL_ListClear(&दत्त->popup_windows);
    }

    यदि (दत्त->pixmap) {
        X11_XFreePixmap(दत्त->display, दत्त->drawable);
    }

#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
    यदि (दत्त->pixmap && दत्त->shm) {
        X11_XShmDetach(दत्त->display, &दत्त->shm_info);
        यदि (!दत्त->shm_pixmap) {
            XDestroyImage(दत्त->image);
        }
        shmdt(दत्त->shm_info.shmaddr);
    }
#यदि_अन्तः

#यदि_परिभाषितम् X_HAVE_UTF8_STRING
    यदि (दत्त->font_समुच्चयः) {
        X11_XFree_Font_समुच्चयः(दत्त->display, दत्त->font_समुच्चयः);
        दत्त->font_समुच्चयः = रिक्त;
    }
#यदि_अन्तः

    यदि (दत्त->font_struct) {
        X11_XFreeFont(दत्त->display, दत्त->font_struct);
        दत्त->font_struct = रिक्त;
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XDBE
    यदि (SDL_X11_HAVE_XDBE && दत्त->xdbe && !दत्त->pixmap) {
        X11_Xdbe_Deallocate_पृष्ठभागः_बफर_Name(दत्त->display, दत्त->buf);
    }
#यदि_अन्तः

    यदि (दत्त->xsettings) {
        xsettings_client_destroy(दत्त->xsettings);
    }

    X11_XFreeGC(दत्त->display, दत्त->ctx);

    यदि (दत्त->display) {
        यदि (दत्त->गवाक्षः != None) {
            X11_XWithdraw_गवाक्षः(दत्त->display, दत्त->गवाक्षः, दत्त->screen);
            X11_XDestroy_गवाक्षः(दत्त->display, दत्त->गवाक्षः);
            दत्त->गवाक्षः = None;
        }

        यदि (दत्त->display_close) {
            X11_XCloseDisplay(दत्त->display);
        }
        दत्त->display = रिक्त;
    }

#यदि SDL_समुच्चयः_LOCALE
    यदि (दत्त->origlocale && (दत्त->बहुलकम् == SDL_TOOLKIT_गवाक्षः_बहुलकम्_X11_DIALOG)) {
        (शून्य)setlocale(LC_ALL, दत्त->origlocale);
        SDL_free(दत्त->origlocale);
    }
#यदि_अन्तः

#यदि_परिभाषितम् HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(दत्त->fribidi);
#यदि_अन्तः

#यदि_परिभाषितम् HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(दत्त->th);
#यदि_अन्तः

    SDL_free(दत्त);
}

स्थिर पूर्णाङ्क X11_Toolkit_गणनम्_पङ्क्तयः_सम्बन्धि_Text(ध्रुव वर्ण *text)
{
    पूर्णाङ्क परिणाम = 0;
    यावत् (text && *text) {
        ध्रुव वर्ण *lf = SDL_strchr(text, '\n');
        परिणाम++; // even without an endline, this counts as a line.
        text = lf ? lf + 1 : रिक्त;
    }
    प्रत्यागम परिणाम;
}

स्थिर शून्य X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    पूर्णाङ्क i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->गवाक्षः->display, control->गवाक्षः->ctx, control->गवाक्षः->xcolor[SDL_MESSAGEBOX_COLOR_TEXT].pixel);
    प्रति (i = 0; i < label_control->sz; i++) {
        X11Toolkit_DrawTextElements(control->गवाक्षः, label_control->पङ्क्तयः[i].text, control->rect.x + label_control->पङ्क्तयः[i].rect.x, control->rect.y + label_control->पङ्क्तयः[i].rect.y);
    }
}

स्थिर शून्य X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    पूर्णाङ्क i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    प्रति (i = 0; i < label_control->sz; i++) {
        X11Toolkit_FreeTextElements(label_control->पङ्क्तयः[i].text);
    }
    SDL_free(label_control->पङ्क्तयः);
    SDL_free(label_control);
}

स्थिर शून्य X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *आधारः_control) {
    SDL_ToolkitLabelControlX11 *control;
    पूर्णाङ्क i;

    control = (SDL_ToolkitLabelControlX11 *)आधारः_control;
    
    यदि (आधारः_control->do_आकार) {
        आधारः_control->rect.w = 0;
        आधारः_control->rect.h = 0;
    }
    
    प्रति (i = 0; i < control->sz; i++) {
        पूर्णाङ्क font_h;
        
        font_h = X11Toolkit_GetTextElementsRect(control->पङ्क्तयः[i].text, &control->पङ्क्तयः[i].rect);
        
        यदि (आधारः_control->do_आकार) {
            आधारः_control->rect.w = SDL_max(आधारः_control->rect.w, control->पङ्क्तयः[i].rect.w);
        }
        
        यदि (i > 0) {
            control->पङ्क्तयः[i].rect.y = font_h + control->पङ्क्तयः[i - 1].rect.y;
        } अन्यथा {
            control->पङ्क्तयः[i].rect.y = 0;
        }
    }

#यदि_परिभाषितम् HAVE_FRIBIDI_H
    यदि (आधारः_control->गवाक्षः->fribidi) {
        FriBidiParType first_ndn_dir;
        पूर्णाङ्क चरमः_ndn;
    
        first_ndn_dir = FRIBIDI_PAR_LTR;
        प्रति (i = 0; i < control->sz; i++) {
            यदि (control->पङ्क्तयः[i].par != FRIBIDI_PAR_ON) {
                first_ndn_dir = control->पङ्क्तयः[i].par;
            }
        }

        चरमः_ndn = -1;
        प्रति (i = 0; i < control->sz; i++) {
            विकल्प (control->पङ्क्तयः[i].par) {
                पक्ष FRIBIDI_PAR_LTR:
                    control->पङ्क्तयः[i].rect.x = 0;
                    चरमः_ndn = i;
                    भङ्ग;
                पक्ष FRIBIDI_PAR_RTL:
                    control->पङ्क्तयः[i].rect.x = आधारः_control->rect.w - control->पङ्क्तयः[i].rect.w;
                    चरमः_ndn = i;
                    भङ्ग;
                स्वभाव:
                    यदि (चरमः_ndn != -1) {
                        यदि (control->पङ्क्तयः[चरमः_ndn].par == FRIBIDI_PAR_RTL) {
                            control->पङ्क्तयः[i].rect.x = आधारः_control->rect.w - control->पङ्क्तयः[i].rect.w;
                        } अन्यथा {
                            control->पङ्क्तयः[i].rect.x = 0;
                        }
                    } अन्यथा {
                        यदि (first_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->पङ्क्तयः[i].rect.x = आधारः_control->rect.w - control->पङ्क्तयः[i].rect.w;
                        } अन्यथा {
                            control->पङ्क्तयः[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#यदि_अन्तः
    
    यदि (आधारः_control->do_आकार && control->sz) {
        आधारः_control->rect.h = control->पङ्क्तयः[control->sz - 1].rect.y + control->पङ्क्तयः[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_गवाक्षः_X11 *गवाक्षः, वर्ण *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *आधारः_control;
    पूर्णाङ्क i;
    
    यदि (!utf8) {
        प्रत्यागम रिक्त;
    }
 
    यदि (!SDL_strcmp(utf8, "")) {
        प्रत्यागम रिक्त;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(परिमाण(SDL_ToolkitLabelControlX11));
    आधारः_control = (SDL_ToolkitControlX11 *)control;
    यदि (!control) {
        SDL_समुच्चयः_Error("Unable to allocate label control structure");
        प्रत्यागम रिक्त;
    }
    आधारः_control->गवाक्षः = गवाक्षः;
    आधारः_control->func_draw = X11Toolkit_DrawLabelControl;
    आधारः_control->func_on_state_change = रिक्त;
    आधारः_control->func_calc_आकार = X11Toolkit_CalculateLabelControl;
    आधारः_control->func_free  = X11Toolkit_DestroyLabelControl;
    आधारः_control->func_on_scale_change = रिक्त;
    आधारः_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_प्रसामान्यम्;
    आधारः_control->selected = false;
    आधारः_control->dynamic = false;
    आधारः_control->rect.w = 0;
    आधारः_control->rect.h = 0;
    आधारः_control->is_default_enter = false;
    आधारः_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_गणनम्_पङ्क्तयः_सम्बन्धि_Text(utf8);
    control->पङ्क्तयः = SDL_calloc(control->sz, परिमाण(SDL_Toolkit_Label_Control_पङ्क्तिः_X11));
    प्रति (i = 0; i < control->sz; i++) {
        ध्रुव वर्ण *lf = SDL_strchr(utf8, '\n');
        ध्रुव पूर्णाङ्क दीर्घता = lf ? (lf - utf8) : SDL_strlen(utf8);
        पूर्णाङ्क sz;
        
        sz = दीर्घता;
        यदि (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#यदि_परिभाषितम् HAVE_FRIBIDI_H
        control->पङ्क्तयः[i].text = X11Toolkit_MakeTextElements(आधारः_control->गवाक्षः, (वर्ण *)utf8, sz, &control->पङ्क्तयः[i].par);
#अन्यथा 
        control->पङ्क्तयः[i].text = X11Toolkit_MakeTextElements(आधारः_control->गवाक्षः, (वर्ण *)utf8, sz);
#यदि_अन्तः
        X11Toolkit_ShapeTextElements(आधारः_control->गवाक्षः, control->पङ्क्तयः[i].text);

        utf8 += दीर्घता + 1;
        यदि (!lf) {
            भङ्ग;
        }
    }

    आधारः_control->do_आकार = true;
    X11Toolkit_CalculateLabelControl(आधारः_control);
    आधारः_control->do_आकार = false;
    X11_Toolkit_सङ्कलय_Control_गन्तव्यम्_गवाक्षः(गवाक्षः, आधारः_control);

    प्रत्यागम आधारः_control;
}

पूर्णाङ्क X11_Toolkit_Get_Label_Control_First_पङ्क्तिः_Height(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    प्रत्यागम label_control->पङ्क्तयः[0].rect.h;
}

शून्य X11_Toolkit_Signal_गवाक्षः_Close(SDL_Toolkit_गवाक्षः_X11 *दत्त) {
    दत्त->close = true;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
