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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ "../../SDL_list.h"
#అన్తర్భావ "SDL_x11video.h"
#నిర్వచితమైతే SDL_USE_LIBDBUS
#అన్తర్భావ "../../core/linux/SDL_system_theme.h"
#అయితే_ముగింపు
#నిర్వచితమైతే HAVE_FRIBIDI_H
#అన్తర్భావ "../../core/unix/SDL_fribidi.h"
#అయితే_ముగింపు
#అన్తర్భావ "SDL_x11dyn.h"
#అన్తర్భావ "SDL_x11toolkit.h"
#అన్తర్భావ "SDL_x11settings.h"
#అన్తర్భావ "SDL_x11modes.h"
#అన్తర్భావ "xsettings-client.h"
#అన్తర్భావ <X11/keysym.h>
#అన్తర్భావ <locale.h>

#నిర్వచించు SDL_సమితి_LOCALE 1
#నిర్వచించు SDL_GRAB 1

రకనిర్వచనం గణన SDL_Toolkit_పాఠ్యం_Type_X11
{
    SDL_TOOLKIT_పాఠ్యం_TYPE_X11_GENERIC,
    SDL_TOOLKIT_పాఠ్యం_TYPE_X11_THAI
} SDL_Toolkit_పాఠ్యం_Type_X11;

#నిర్వచితమైతే HAVE_LIBTHAI_H
రకనిర్వచనం నిర్మాణం SDL_ToolkitThaiOverlayX11
{
    bool శిఖరం;
    అక్షరం *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం SDL_Toolkit_పాఠ్యం_Element_X11
{
    SDL_Toolkit_పాఠ్యం_Type_X11 type;
    అక్షరం *str;
    size_t sz;
    SDL_Rect rect;
    పూర్ణాంకం font_h;
    శూన్య (*str_free)(శూన్య *);
#నిర్వచితమైతే HAVE_LIBTHAI_H
    SDL_List_కణుపు *thai_overlays;
#అయితే_ముగింపు
} SDL_Toolkit_పాఠ్యం_Element_X11;

రకనిర్వచనం నిర్మాణం SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 మాతృ;

    /* Icon type */
    SDL_సందేశం_Box_Flags flags;
    అక్షరం icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    పూర్ణాంకం icon_char_x;
    పూర్ణాంకం icon_char_y;
    పూర్ణాంకం icon_char_a;
    పూర్ణాంకం icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

రకనిర్వచనం నిర్మాణం SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 మాతృ;

    /*దత్తాంశం*/
    స్థిరరాశి SDL_సందేశం_Box_Button_దత్తాంశం *దత్తాంశం;

    /*పాఠ్యం*/
    SDL_List_కణుపు *పాఠ్యం;
    SDL_Rect పాఠ్యం_rect;
    
    /* Callback */
    శూన్య *cb_దత్తాంశం;
    శూన్య (*cb)(నిర్మాణం SDL_ToolkitControlX11 *, శూన్య *);
} SDL_ToolkitButtonControlX11;

రకనిర్వచనం నిర్మాణం SDL_Toolkit_Label_Control_పంక్తి_X11
{
    SDL_List_కణుపు *పాఠ్యం;
    SDL_Rect rect;
#నిర్వచితమైతే HAVE_FRIBIDI_H
    FriBidiParType par;
#అయితే_ముగింపు
} SDL_Toolkit_Label_Control_పంక్తి_X11;

రకనిర్వచనం నిర్మాణం SDL_ToolkitLabelControlX11
{
    SDL_ToolkitControlX11 మాతృ;

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
    SDL_Toolkit_Label_Control_పంక్తి_X11 *పంక్తులు;
    size_t sz;
} SDL_ToolkitLabelControlX11;

రకనిర్వచనం నిర్మాణం SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 మాతృ;

    SDL_List_కణుపు *menu_వస్తువులు;
} SDL_ToolkitMenuBarControlX11;

రకనిర్వచనం నిర్మాణం SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 మాతృ;

    SDL_List_కణుపు *menu_వస్తువులు;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
స్థిర స్థిరరాశి అక్షరం *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#నిర్వచించు G_ICONFONT_కొలత 22

/* General UI font */
స్థిర స్థిరరాశి అక్షరం g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
స్థిర స్థిరరాశి అక్షరం g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

స్థిర స్థిరరాశి అక్షరం *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    ఖాళీ
};
#నిర్వచించు G_TOOLKITFONT_కొలత 140

స్థిర స్థిరరాశి SDL_సందేశం_Box_Color g_default_colors[SDL_MESSAGEBOX_COLOR_లెక్క] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#నిర్వచితమైతే SDL_USE_LIBDBUS
స్థిర స్థిరరాశి SDL_సందేశం_Box_Color g_default_colors_dark[SDL_MESSAGEBOX_COLOR_లెక్క] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ఒకవేళ 0
స్థిర స్థిరరాశి SDL_సందేశం_Box_Color g_default_colors_dark_ఎగువ_contrast[SDL_MESSAGEBOX_COLOR_లెక్క] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

స్థిర స్థిరరాశి SDL_సందేశం_Box_Color g_default_colors_light_ఎగువ_contrast[SDL_MESSAGEBOX_COLOR_లెక్క] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#అయితే_ముగింపు

#అయితే_ముగింపు

స్థిర పూర్ణాంకం g_shm_error;
స్థిర పూర్ణాంకం (*g_old_error_handler)(Display *, XErrorEvent *) = ఖాళీ;

స్థిర పూర్ణాంకం X11_Toolkit_Shared_జ్ఞాపకం_Error_Handler(Display *d, XErrorEvent *e)
{
    ఒకవేళ (e->error_సంకేతం == BadAccess || e->error_సంకేతం == BadRequest) {
        g_shm_error = True;
        తిరిగి 0;
    }
    తిరిగి g_old_error_handler(d, e);
}

స్థిర శూన్య X11_Toolkit_Init_కిటికీ_Pixmap(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం) {
    ఒకవేళ (దత్తాంశం->pixmap) {
#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
        ఒకవేళ (!దత్తాంశం->shm_pixmap) {
            దత్తాంశం->drawable = X11_XCreatePixmap(దత్తాంశం->display, దత్తాంశం->కిటికీ, దత్తాంశం->pixmap_వెడల్పు, దత్తాంశం->pixmap_ఎత్తు, దత్తాంశం->లోతు_2);
        }
#లేకపోతే
        దత్తాంశం->drawable = X11_XCreatePixmap(దత్తాంశం->display, దత్తాంశం->కిటికీ, దత్తాంశం->pixmap_వెడల్పు, దత్తాంశం->pixmap_ఎత్తు, దత్తాంశం->లోతు_2);
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
        ఒకవేళ (దత్తాంశం->shm) {
            దత్తాంశం->image = X11_XShmCreateImage(దత్తాంశం->display, దత్తాంశం->visual, దత్తాంశం->లోతు_2, ZPixmap, ఖాళీ, &దత్తాంశం->shm_info, దత్తాంశం->pixmap_వెడల్పు, దత్తాంశం->pixmap_ఎత్తు);
            ఒకవేళ (దత్తాంశం->image) {
                దత్తాంశం->shm_బైట్లు_చొప్పున_పంక్తి = దత్తాంశం->image->బైట్లు_చొప్పున_పంక్తి;

                దత్తాంశం->shm_info.shmid = shmget(IPC_వ్యక్తిగత, దత్తాంశం->image->బైట్లు_చొప్పున_పంక్తి * దత్తాంశం->image->ఎత్తు, IPC_CREAT | 0777);
                ఒకవేళ (దత్తాంశం->shm_info.shmid < 0) {
                    XDestroyImage(దత్తాంశం->image);
                    దత్తాంశం->image = ఖాళీ;
                    దత్తాంశం->shm = false;
                    తిరిగి;
                }

                దత్తాంశం->shm_info.readOnly = False;
                దత్తాంశం->shm_info.shmaddr = దత్తాంశం->image->దత్తాంశం = (అక్షరం *)shmat(దత్తాంశం->shm_info.shmid, ఖాళీ, 0);
                ఒకవేళ (((గుర్తుగల అక్షరం *)దత్తాంశం->shm_info.shmaddr) == (గుర్తుగల అక్షరం *)-1) {
                    XDestroyImage(దత్తాంశం->image);
                    దత్తాంశం->shm = false;
                    దత్తాంశం->image = ఖాళీ;
                    తిరిగి;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11_Toolkit_Shared_జ్ఞాపకం_Error_Handler);
                X11_XShmAttach(దత్తాంశం->display, &దత్తాంశం->shm_info);
                X11_XSync(దత్తాంశం->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                ఒకవేళ (g_shm_error) {
                    XDestroyImage(దత్తాంశం->image);
                    shmdt(దత్తాంశం->shm_info.shmaddr);
                    shmctl(దత్తాంశం->shm_info.shmid, IPC_RMID, ఖాళీ);
                    దత్తాంశం->image = ఖాళీ;
                    దత్తాంశం->shm = false;
                    తిరిగి;
                }

                ఒకవేళ (దత్తాంశం->shm_pixmap) {
                    దత్తాంశం->drawable = X11_XShmCreatePixmap(దత్తాంశం->display, దత్తాంశం->కిటికీ, దత్తాంశం->shm_info.shmaddr, &దత్తాంశం->shm_info, దత్తాంశం->pixmap_వెడల్పు, దత్తాంశం->pixmap_ఎత్తు, దత్తాంశం->లోతు_2);
                    ఒకవేళ (దత్తాంశం->drawable == None) {
                        దత్తాంశం->shm_pixmap = False;
                    } లేకపోతే {
                        XDestroyImage(దత్తాంశం->image);
                        దత్తాంశం->image = ఖాళీ;
                    }
                }

                shmctl(దత్తాంశం->shm_info.shmid, IPC_RMID, ఖాళీ);
            } లేకపోతే {
                దత్తాంశం->shm = false;
            }
        }
#అయితే_ముగింపు
    }
}

స్థిర శూన్య X11_Toolkit_Init_కిటికీ_Fonts(SDL_Toolkit_కిటికీ_X11 *కిటికీ)
{    
    కిటికీ->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    కిటికీ->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#నిర్వచితమైతే X_HAVE_UTF8_STRING
    కిటికీ->utf8 = true;
    కిటికీ->font_సమితి = ఖాళీ;
    ఒకవేళ (SDL_X11_HAVE_UTF8) {
        అక్షరం **missing = ఖాళీ;
        పూర్ణాంకం అంకె_missing = 0;
        పూర్ణాంకం i_font;
        కిటికీ->font_struct = ఖాళీ;
        కొరకు (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            అక్షరం *font;

            ఒకవేళ (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_ఎక్కించు_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_కొలత * కిటికీ->iscale);
                కిటికీ->font_సమితి = X11_XCreate_Font_సమితి(కిటికీ->display, font, &missing, &అంకె_missing, ఖాళీ);
                SDL_free(font);

                ఒకవేళ (!కిటికీ->font_సమితి) {
                    ఒకవేళ (కిటికీ->scale != 0 && కిటికీ->iscale > 0) {
                        కిటికీ->iscale = (పూర్ణాంకం)SDL_ceilf(కిటికీ->scale);
                        కిటికీ->scale = 0;
                    } లేకపోతే {
                        కిటికీ->iscale--;
                    }
                    వెళ్ళు try_ఎక్కించు_font;
                }
            } లేకపోతే {
                కిటికీ->font_సమితి = X11_XCreate_Font_సమితి(కిటికీ->display, g_ToolkitFont[i_font], &missing, &అంకె_missing, ఖాళీ);
            }

            ఒకవేళ (missing) {
                X11_XFreeStringList(missing);
            }

            ఒకవేళ (కిటికీ->font_సమితి) {
                ఆపు;
            }
        }

        ఒకవేళ (!కిటికీ->font_సమితి) {
            వెళ్ళు ఎక్కించు_font_traditional;
        } లేకపోతే {
            XFontStruct **font_structs;
            అక్షరం **font_పేర్లు;
            పూర్ణాంకం font_sz;
            పూర్ణాంకం i;
            
#నిర్వచితమైతే HAVE_FRIBIDI_H
            కిటికీ->do_shaping = !X11_XContextDependentDrawing(కిటికీ->font_సమితి);
#అయితే_ముగింపు
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFonts_యొక్క_Font_సమితి(కిటికీ->font_సమితి, &font_structs, &font_పేర్లు);
            కొరకు (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                ఒకవేళ (SDL_strstr(font_పేర్లు[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } లేకపోతే ఒకవేళ (SDL_strstr(font_పేర్లు[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } లేకపోతే ఒకవేళ (SDL_strstr(font_పేర్లు[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } లేకపోతే ఒకవేళ (SDL_strstr(font_పేర్లు[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } లేకపోతే ఒకవేళ (SDL_strstr(font_పేర్లు[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                ఒకవేళ (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(కిటికీ->display, font_పేర్లు[i]);
                    ఒకవేళ (font_struct) {
                        ఒకవేళ (font_struct->చొప్పున_char) {
                            పూర్ణాంకం glyphs_sz;
                            పూర్ణాంకం j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            కొరకు (j = 0; j < glyphs_sz; j++) {
                                ఒకవేళ (font_struct->చొప్పున_char[j].lbearing < 0) {
                                    కిటికీ->thai_font = SDL_TOOLKIT_THAI_FONT_X11_స్థానభ్రంశం;
                                }
                            }
                        }
                        X11_XFreeFont(కిటికీ->display, font_struct);
                    }
                }
                
                కిటికీ->thai_encoding = thai_encoding;
            } 
        }
    } లేకపోతే
#అయితే_ముగింపు
    {
        అక్షరం *font;

        ఎక్కించు_font_traditional:
        కిటికీ->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_కొలత * కిటికీ->iscale);
        కిటికీ->font_struct = X11_XLoadQueryFont(కిటికీ->display, font);
        SDL_free(font);
        ఒకవేళ (!కిటికీ->font_struct) {
            ఒకవేళ (కిటికీ->iscale > 0) {
                ఒకవేళ (కిటికీ->scale != 0) {
                    కిటికీ->iscale = (పూర్ణాంకం)SDL_ceilf(కిటికీ->scale);
                    కిటికీ->scale = 0;
                } లేకపోతే {
                    కిటికీ->iscale--;
                }
                వెళ్ళు ఎక్కించు_font_traditional;
            } లేకపోతే {
                కిటికీ->font_struct = X11_XLoadQueryFont(కిటికీ->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

స్థిర శూన్య X11Toolkit_SettingsNotify(స్థిరరాశి అక్షరం *name, XSettingsAction action, XSettingsSetting *setting, శూన్య *దత్తాంశం)
{
    SDL_Toolkit_కిటికీ_X11 *కిటికీ;
    పూర్ణాంకం i;

    కిటికీ = దత్తాంశం;

    ఒకవేళ (కిటికీ->xsettings_మొదటి_సమయం) {
        తిరిగి;
    }

    ఒకవేళ (SDL_strcmp(name, SDL_XSETTINGS_GDK_కిటికీ_SCALING_గుణకం) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_అమరిక = false;
        bool pixmap_already_అమరిక = false;

        ఒకవేళ (కిటికీ->pixmap) {
            pixmap_already_అమరిక = true;
        } లేకపోతే {
            dbe_already_అమరిక = true;
        }

        /* set scale vars */
        కిటికీ->scale = X11_GetGlobalContentScale(కిటికీ->display, కిటికీ->xsettings);
        కిటికీ->iscale = (పూర్ణాంకం)SDL_ceilf(కిటికీ->scale);
        ఒకవేళ (కిటికీ->scale < 1) {
            కిటికీ->scale = 1;
        }
        ఒకవేళ (SDL_roundf(కిటికీ->scale) == కిటికీ->scale) {
            కిటికీ->scale = 0;
        }

        /* setup fonts */
#నిర్వచితమైతే X_HAVE_UTF8_STRING
        ఒకవేళ (కిటికీ->font_సమితి) {
            X11_XFree_Font_సమితి(కిటికీ->display, కిటికీ->font_సమితి);
        }
#అయితే_ముగింపు
        ఒకవేళ (కిటికీ->font_struct) {
            X11_XFreeFont(కిటికీ->display, కిటికీ->font_struct);
        }

        X11_Toolkit_Init_కిటికీ_Fonts(కిటికీ);

        /* set up window */
        ఒకవేళ (కిటికీ->scale != 0) {
            కిటికీ->కిటికీ_వెడల్పు = SDL_lroundf((కిటికీ->కిటికీ_వెడల్పు/కిటికీ->iscale) * కిటికీ->scale);
            కిటికీ->కిటికీ_ఎత్తు = SDL_lroundf((కిటికీ->కిటికీ_ఎత్తు/కిటికీ->iscale) * కిటికీ->scale);
            కిటికీ->pixmap_వెడల్పు = కిటికీ->కిటికీ_వెడల్పు;
            కిటికీ->pixmap_ఎత్తు = కిటికీ->కిటికీ_ఎత్తు;
            కిటికీ->pixmap = true;
        } లేకపోతే {
            కిటికీ->pixmap = false;
        }

        ఒకవేళ (కిటికీ->pixmap) {
            ఒకవేళ (!pixmap_already_అమరిక) {
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XDBE
                ఒకవేళ (SDL_X11_HAVE_XDBE && కిటికీ->xdbe) {
                    X11_Xdbe_Deallocate_వెనుక_బఫరు_Name(కిటికీ->display, కిటికీ->buf);
                }
#అయితే_ముగింపు
            }
            X11_XFreePixmap(కిటికీ->display, కిటికీ->drawable);
            X11_Toolkit_Init_కిటికీ_Pixmap(కిటికీ);
        } లేకపోతే {
            ఒకవేళ (!dbe_already_అమరిక) {
                X11_XFreePixmap(కిటికీ->display, కిటికీ->drawable);
#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
                ఒకవేళ (కిటికీ->image) {
                    XDestroyImage(కిటికీ->image);
                    కిటికీ->image = ఖాళీ;
                }
#అయితే_ముగింపు
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XDBE
                ఒకవేళ (SDL_X11_HAVE_XDBE && కిటికీ->xdbe) {
                    కిటికీ->buf = X11_Xdbe_Allocate_వెనుక_బఫరు_Name(కిటికీ->display, కిటికీ->కిటికీ, XdbeUndefined);
                    కిటికీ->drawable = కిటికీ->buf;
                }
#అయితే_ముగింపు
            }
        }

        /* notify controls */
        కొరకు (i = 0; i < కిటికీ->controls_sz; i++) {
            కిటికీ->controls[i]->do_కొలత = true;

            ఒకవేళ (కిటికీ->controls[i]->func_on_scale_change) {
                కిటికీ->controls[i]->func_on_scale_change(కిటికీ->controls[i]);
            }

            ఒకవేళ (కిటికీ->controls[i]->func_calc_కొలత) {
                కిటికీ->controls[i]->func_calc_కొలత(కిటికీ->controls[i]);
            }

            కిటికీ->controls[i]->do_కొలత = false;
        }

        /* notify cb */
        ఒకవేళ (కిటికీ->cb_on_scale_change) {
            కిటికీ->cb_on_scale_change(కిటికీ, కిటికీ->cb_దత్తాంశం);
        }

        /* update ev scales */
        ఒకవేళ (!కిటికీ->pixmap) {
            కిటికీ->ev_scale = కిటికీ->ev_iscale = 1;
        } లేకపోతే {
            కిటికీ->ev_scale = కిటికీ->scale;
            కిటికీ->ev_iscale = కిటికీ->iscale;
        }
    }
}

స్థిర శూన్య X11_Toolkit_Get_పాఠ్యం_వెడల్పు_ఎత్తు_For_Font(XFontStruct *font, స్థిరరాశి అక్షరం *str, పూర్ణాంకం nbytes, పూర్ణాంకం *pwidth, పూర్ణాంకం *pheight, పూర్ణాంకం *ascent, పూర్ణాంకం *font_ఎత్తు)
{
    XCharStruct పాఠ్యం_structure;
    పూర్ణాంకం font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &పాఠ్యం_structure);
    *pwidth = పాఠ్యం_structure.వెడల్పు;
    *pheight = పాఠ్యం_structure.ascent + పాఠ్యం_structure.descent;
    *ascent = పాఠ్యం_structure.ascent;
    ఒకవేళ (font_ఎత్తు) {
       *font_ఎత్తు = font_ascent + font_descent;
    }
}

స్థిర శూన్య X11_Toolkit_Get_పాఠ్యం_వెడల్పు_ఎత్తు(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం, స్థిరరాశి అక్షరం *str, పూర్ణాంకం nbytes, పూర్ణాంకం *pwidth, పూర్ణాంకం *pheight, పూర్ణాంకం *ascent, పూర్ణాంకం *descent, పూర్ణాంకం *font_ఎత్తు)
{
#నిర్వచితమైతే X_HAVE_UTF8_STRING
    ఒకవేళ (దత్తాంశం->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8_పాఠ్యం_Extents(దత్తాంశం->font_సమితి, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.వెడల్పు;
        *pheight = overall_logical.ఎత్తు;
        *ascent = -overall_logical.y;
        *descent = overall_logical.ఎత్తు - *ascent;

        ఒకవేళ (font_ఎత్తు) {
            XFont_సమితి_Extents *extents;

            extents = X11_XExtents_యొక్క_Font_సమితి(దత్తాంశం->font_సమితి);
            *font_ఎత్తు = extents->max_logical_extent.ఎత్తు;
        }
    } లేకపోతే
#అయితే_ముగింపు
    {
        XCharStruct పాఠ్యం_structure;
        పూర్ణాంకం font_direction, font_ascent, font_descent;
        X11_XTextExtents(దత్తాంశం->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &పాఠ్యం_structure);
        *pwidth = పాఠ్యం_structure.వెడల్పు;
        *pheight = పాఠ్యం_structure.ascent + పాఠ్యం_structure.descent;
        *ascent = పాఠ్యం_structure.ascent;
        *descent = పాఠ్యం_structure.descent;

        ఒకవేళ (font_ఎత్తు) {
            *font_ఎత్తు = font_ascent + font_descent;
        }
    }
}

#నిర్వచితమైతే HAVE_FRIBIDI_H
SDL_List_కణుపు *X11_Toolkit_Make_పాఠ్యం_Elements(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం, అక్షరం *txt, size_t sz, FriBidiParType *par)
#లేకపోతే
SDL_List_కణుపు *X11_Toolkit_Make_పాఠ్యం_Elements(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం, అక్షరం *txt, size_t sz)
#అయితే_ముగింపు
{
    SDL_List_కణుపు *list;
    అక్షరం *str;
    అక్షరం *బఫరు_2;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = ఖాళీ;
    thai = 0;
    str = txt;
    బఫరు_2 = SDL_malloc(1);
    బఫరు_2[0] = 0;
    
#నిర్వచితమైతే HAVE_FRIBIDI_H
    ఒకవేళ (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    ఒకవేళ (దత్తాంశం->fribidi) {
        అక్షరం *fstr;
                
        fstr = SDL_FriBidi_Process(దత్తాంశం->fribidi, str, sz, దత్తాంశం->do_shaping, par);
        ఒకవేళ (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#అయితే_ముగింపు        

    అయితే (1) {
        అక్షరం *new;
        అక్షరం utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_అడుగు_UTF8((స్థిరరాశి అక్షరం **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        ఒకవేళ (cp == 0 || cond == (thai ? false : true)) {
            SDL_Toolkit_పాఠ్యం_Element_X11 *element;
            
            element = SDL_malloc(పరిమాణం(SDL_Toolkit_పాఠ్యం_Element_X11));
            ఒకవేళ (thai) {
                element->type = SDL_TOOLKIT_పాఠ్యం_TYPE_X11_THAI;
            } లేకపోతే {
                element->type = SDL_TOOLKIT_పాఠ్యం_TYPE_X11_GENERIC;
            }
            element->str = SDL_strdup(బఫరు_2);
            element->sz = SDL_strlen(బఫరు_2);
            element->str_free = SDL_free;
            
            SDL_List_కూడు(&list, element);
            
            SDL_free(బఫరు_2);
            బఫరు_2 = SDL_malloc(1);
            బఫరు_2[0] = 0;
            thai = thai ? false : true;
        }

        ఒకవేళ (!cp) {
            ఆపు;
        }
        
        SDL_UCS4_గమ్యం_UTF8(cp, utf8);
        csz = SDL_strlen(బఫరు_2) + SDL_strlen(utf8) + 1;
        new = SDL_malloc(csz);
        SDL_strlcpy(new, బఫరు_2, csz);
        SDL_strlcat(new, utf8, csz);
        SDL_free(బఫరు_2);
        బఫరు_2 = new;
    }

    SDL_free(బఫరు_2);
    ఒకవేళ (free_txt) {
        SDL_free(txt);
    }
    తిరిగి list;
}

శూన్య X11_Toolkit_Shape_పాఠ్యం_Elements(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం, SDL_List_కణుపు *list)
{
    SDL_List_కణుపు *cursor;
    SDL_Toolkit_పాఠ్యం_Element_X11 *prev;
    పూర్ణాంకం తాత్కాలిక;
    
    /* Shape and calculate bounding box */
    cursor = list;
    అయితే (cursor) {
        SDL_Toolkit_పాఠ్యం_Element_X11 *element;
        
        element = cursor->నమోదు_2;
#నిర్వచితమైతే HAVE_LIBTHAI_H
        element->thai_overlays = ఖాళీ;
#అయితే_ముగింపు
        ఒకవేళ (element->type == SDL_TOOLKIT_పాఠ్యం_TYPE_X11_THAI) {
            ఒకవేళ (దత్తాంశం->thai_font == SDL_TOOLKIT_THAI_FONT_X11_స్థానభ్రంశం) {
                X11_Toolkit_Get_పాఠ్యం_వెడల్పు_ఎత్తు(దత్తాంశం, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &తాత్కాలిక, ఖాళీ);
            } లేకపోతే {
#నిర్వచితమైతే HAVE_LIBTHAI_H
                ఒకవేళ (దత్తాంశం->th) {
                    నిర్మాణం thcell_t *cells;
                    అక్షరం *tis_str;
                    అక్షరం *పునాది_tis_str;
                    size_t cells_sz;
                    size_t పునాది_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, పరిమాణం(నిర్మాణం thcell_t));
                    దత్తాంశం->th->make_cells((స్థిరరాశి thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    పునాది_tis_str_sz = cells_sz;
                    పునాది_tis_str = SDL_malloc(పునాది_tis_str_sz + 1);
                    కొరకు (తాత్కాలిక = 0; తాత్కాలిక < cells_sz; తాత్కాలిక++) {
                        పునాది_tis_str[తాత్కాలిక] = cells[తాత్కాలిక].పునాది;
                        
                        ఒకవేళ (cells[తాత్కాలిక].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            అక్షరం *pre;
                            పూర్ణాంకం temp2;
                            
                            overlay = SDL_malloc(పరిమాణం(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", పునాది_tis_str, తాత్కాలిక);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (స్థిరరాశి అక్షరం *)&cells[తాత్కాలిక].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->శిఖరం = false;
                            X11_Toolkit_Get_పాఠ్యం_వెడల్పు_ఎత్తు(దత్తాంశం, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ఖాళీ);
                            X11_Toolkit_Get_పాఠ్యం_వెడల్పు_ఎత్తు(దత్తాంశం, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ఖాళీ);
                            SDL_List_కూడు(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        ఒకవేళ (cells[తాత్కాలిక].శిఖరం) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            అక్షరం *pre;
                            పూర్ణాంకం temp2;
                            
                            overlay = SDL_malloc(పరిమాణం(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", పునాది_tis_str, తాత్కాలిక);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (స్థిరరాశి అక్షరం *)&cells[తాత్కాలిక].శిఖరం, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->శిఖరం = true;
                            X11_Toolkit_Get_పాఠ్యం_వెడల్పు_ఎత్తు(దత్తాంశం, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ఖాళీ);
                            X11_Toolkit_Get_పాఠ్యం_వెడల్పు_ఎత్తు(దత్తాంశం, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ఖాళీ);
                            SDL_List_కూడు(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    పునాది_tis_str[పునాది_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", పునాది_tis_str, పునాది_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11_Toolkit_Get_పాఠ్యం_వెడల్పు_ఎత్తు(దత్తాంశం, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &తాత్కాలిక, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(పునాది_tis_str);
                }
#లేకపోతే
                X11_Toolkit_Get_పాఠ్యం_వెడల్పు_ఎత్తు(దత్తాంశం, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &తాత్కాలిక, &element->font_h);
#అయితే_ముగింపు            
            }
        } లేకపోతే {
            X11_Toolkit_Get_పాఠ్యం_వెడల్పు_ఎత్తు(దత్తాంశం, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &తాత్కాలిక, &element->font_h);
        }
        
        cursor = cursor->తదుపరి;
    }
    
    /* Add offsets */
    prev = ఖాళీ;
    cursor = list;
    అయితే (cursor) {
        SDL_Toolkit_పాఠ్యం_Element_X11 *element;
        
        element = cursor->నమోదు_2;        
        ఒకవేళ (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } లేకపోతే {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->తదుపరి;
    }
}


శూన్య X11_Toolkit_Draw_పాఠ్యం_Elements(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం, SDL_List_కణుపు *list, పూర్ణాంకం x, పూర్ణాంకం y)
{
    SDL_List_కణుపు *cursor;
    
    cursor = list;
    
    అయితే (cursor) {
        SDL_Toolkit_పాఠ్యం_Element_X11 *element;
        
        element = cursor->నమోదు_2;
        ఒకవేళ (element->type == SDL_TOOLKIT_పాఠ్యం_TYPE_X11_THAI) {
            ఒకవేళ (దత్తాంశం->thai_font == SDL_TOOLKIT_THAI_FONT_X11_స్థానభ్రంశం) {
#నిర్వచితమైతే X_HAVE_UTF8_STRING
                ఒకవేళ (దత్తాంశం->utf8) {
                    X11_Xutf8DrawString(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->font_సమితి, దత్తాంశం->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } లేకపోతే
#అయితే_ముగింపు
                {
                    X11_XDrawString(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } లేకపోతే {    
#నిర్వచితమైతే HAVE_LIBTHAI_H
                SDL_List_కణుపు *overlay_cursor;
                    
                /* Draw the base string */
#నిర్వచితమైతే X_HAVE_UTF8_STRING
                ఒకవేళ (దత్తాంశం->utf8) {
                    X11_Xutf8DrawString(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->font_సమితి, దత్తాంశం->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } లేకపోతే
#అయితే_ముగింపు
                {
                    X11_XDrawString(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                అయితే (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->నమోదు_2;
#నిర్వచితమైతే X_HAVE_UTF8_STRING
                    ఒకవేళ (దత్తాంశం->utf8) {
                        X11_Xutf8DrawString(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->font_సమితి, దత్తాంశం->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } లేకపోతే
#అయితే_ముగింపు
                    {
                        X11_XDrawString(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->తదుపరి;
                }
#అయితే_ముగింపు                
            }
        } లేకపోతే {
#నిర్వచితమైతే X_HAVE_UTF8_STRING
            ఒకవేళ (దత్తాంశం->utf8) {
                X11_Xutf8DrawString(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->font_సమితి, దత్తాంశం->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } లేకపోతే
#అయితే_ముగింపు
            {
                X11_XDrawString(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->తదుపరి;
    }
}

పూర్ణాంకం X11_Toolkit_Get_పాఠ్యం_Elements_Rect(SDL_List_కణుపు *list, SDL_Rect *బహిర్గతం)
{
    SDL_List_కణుపు *cursor;
    పూర్ణాంకం ret;
    
    ret = 0;
    బహిర్గతం->x = బహిర్గతం->y = 0;
    బహిర్గతం->w = బహిర్గతం->h = 0;
    cursor = list;
    అయితే (cursor) {
        SDL_Toolkit_పాఠ్యం_Element_X11 *element;
        
        element = cursor->నమోదు_2;
        
        బహిర్గతం->w += element->rect.w;
        బహిర్గతం->h = SDL_max(బహిర్గతం->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->తదుపరి;
    }
    
    తిరిగి ret;
}

శూన్య X11_Toolkit_Free_పాఠ్యం_Elements_List_Contents(SDL_List_కణుపు *list)
{
    SDL_List_కణుపు *cursor;
    
    cursor = list;
    అయితే (cursor) {
        SDL_Toolkit_పాఠ్యం_Element_X11 *element;
#నిర్వచితమైతే HAVE_LIBTHAI_H
        SDL_List_కణుపు *overlay_cursor;
#అయితే_ముగింపు

        element = cursor->నమోదు_2;
        
        ఒకవేళ (element->str_free) {
            element->str_free(element->str);
        }
        
#నిర్వచితమైతే HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        అయితే (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->నమోదు_2;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->తదుపరి;
        }
        SDL_ListClear(&element->thai_overlays);
#అయితే_ముగింపు
        
        SDL_free(element);
        
        cursor = cursor->తదుపరి;
    }
}

#నిర్వచించు X11_Toolkit_Free_పాఠ్యం_Elements(x) X11_Toolkit_Free_పాఠ్యం_Elements_List_Contents(x); SDL_ListClear(&x)
 
స్థిర bool X11Toolkit_ShouldFlipUI(శూన్య) 
{
    SDL_Locale **current_locales;
    స్థిర స్థిరరాశి SDL_Locale rtl_locales[] = {
        { "ar", ఖాళీ, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", ఖాళీ, },
        { "iw", ఖాళీ, },
        { "yi", ఖాళీ, },
        { "ur", ఖాళీ, },
        { "ug", ఖాళీ, },
        { "kd", ఖాళీ, },
        { "pk", "PK", },
        { "ps", ఖాళీ, }
    }; 
    పూర్ణాంకం current_locales_sz;
    పూర్ణాంకం i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    ఒకవేళ (current_locales_sz <= 0) {
        తిరిగి false;        
    }
    కొరకు (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        ఒకవేళ (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            ఒకవేళ (!rtl_locales[i].country) {
                తిరిగి true;
            } లేకపోతే {
                తిరిగి SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    తిరిగి false;
}

SDL_Toolkit_కిటికీ_X11 *X11_Toolkit_Create_కిటికీ_Struct(SDL_కిటికీ *మాతృ, SDL_Toolkit_కిటికీ_X11 *tkparent, SDL_Toolkit_కిటికీ_బహుళకం_X11 బహుళకం, స్థిరరాశి SDL_సందేశం_Box_Color *colorhints, bool create_new_display)
{
    SDL_Toolkit_కిటికీ_X11 *కిటికీ;
    పూర్ణాంకం i;
#నిర్వచితమైతే SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#అయితే_ముగింపు
    #నిర్వచించు ErrorFreeRetNull(x, y) SDL_సమితి_Error(x); SDL_free(y); తిరిగి ఖాళీ
    #నిర్వచించు ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_సమితి_Error(x, y); SDL_free(z); తిరిగి ఖాళీ

    ఒకవేళ (!SDL_X11_ఎక్కించు_Symbols()) {
        తిరిగి ఖాళీ;
    }

    // This code could get called from multiple threads maybe?
    X11_XInit_దారాలు();

    కిటికీ = (SDL_Toolkit_కిటికీ_X11 *)SDL_malloc(పరిమాణం(SDL_Toolkit_కిటికీ_X11));
    ఒకవేళ (!కిటికీ) {
        SDL_సమితి_Error("Unable to allocate toolkit window structure");
        తిరిగి ఖాళీ;
    }

    కిటికీ->బహుళకం = బహుళకం;
    కిటికీ->tk_మాతృ = tkparent;

#ఒకవేళ SDL_సమితి_LOCALE
    ఒకవేళ (బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_DIALOG) {
        కిటికీ->origlocale = setlocale(LC_ALL, ఖాళీ);
        ఒకవేళ (కిటికీ->origlocale) {
            కిటికీ->origlocale = SDL_strdup(కిటికీ->origlocale);
            ఒకవేళ (!కిటికీ->origlocale) {
                SDL_free(కిటికీ);
                తిరిగి ఖాళీ;
            }
            (శూన్య)setlocale(LC_ALL, "");
        }
    }
#అయితే_ముగింపు

    కిటికీ->మాతృ_device = ఖాళీ;
    ఒకవేళ (create_new_display) {
        కిటికీ->display = X11_XOpenDisplay(ఖాళీ);
        కిటికీ->display_close = true;
        ఒకవేళ (!కిటికీ->display) {
            ErrorFreeRetNull("Couldn't open X11 display", కిటికీ);
        }
    } లేకపోతే {
        ఒకవేళ (మాతృ) {
            కిటికీ->మాతృ_device = SDL_GetVideoDevice();
            కిటికీ->display = కిటికీ->మాతృ_device->అంతర్గత->display;
            కిటికీ->display_close = false;
        } లేకపోతే ఒకవేళ (tkparent) {
            కిటికీ->display = tkparent->display;
            కిటికీ->display_close = false;
        } లేకపోతే {
            కిటికీ->display = X11_XOpenDisplay(ఖాళీ);
            కిటికీ->display_close = true;
            ఒకవేళ (!కిటికీ->display) {
                ErrorFreeRetNull("Couldn't open X11 display", కిటికీ);
            }
        }
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
    పూర్ణాంకం xrandr_event_పునాది, xrandr_error_పునాది;
    కిటికీ->xrandr = X11_XRRQueryExtension(కిటికీ->display, &xrandr_event_పునాది, &xrandr_error_పునాది);
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
    కిటికీ->shm_pixmap = False;
    కిటికీ->shm = X11_XShmQueryExtension(కిటికీ->display) ? SDL_X11_HAVE_SHM : false;
    ఒకవేళ (కిటికీ->shm) {
        పూర్ణాంకం major;
        పూర్ణాంకం minor;

        X11_XShm_Query_సంస్కరణ(కిటికీ->display, &major, &minor, &కిటికీ->shm_pixmap);
        ఒకవేళ (కిటికీ->shm_pixmap) {
            ఒకవేళ (X11_XShmPixmapFormat(కిటికీ->display) != ZPixmap) {
                కిటికీ->shm_pixmap = False;
            }
        }
    }
#అయితే_ముగింపు

    /* Scale/Xsettings */
    కిటికీ->pixmap = false;
    కిటికీ->xsettings_మొదటి_సమయం = true;
    కిటికీ->xsettings = xsettings_client_new(కిటికీ->display, DefaultScreen(కిటికీ->display), X11Toolkit_SettingsNotify, ఖాళీ, కిటికీ);
    కిటికీ->xsettings_మొదటి_సమయం = false;
    కిటికీ->scale = X11_GetGlobalContentScale(కిటికీ->display, కిటికీ->xsettings);
    ఒకవేళ (కిటికీ->scale < 1) {
        కిటికీ->scale = 1;
    }
    కిటికీ->iscale = (పూర్ణాంకం)SDL_ceilf(కిటికీ->scale);
    ఒకవేళ (SDL_roundf(కిటికీ->scale) == కిటికీ->scale) {
        కిటికీ->scale = 0;
    }

    /* Fonts */
    X11_Toolkit_Init_కిటికీ_Fonts(కిటికీ);

    /* Color hints */
#నిర్వచితమైతే SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    ఒకవేళ (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#అయితే_ముగింపు

    ఒకవేళ (!colorhints) {
#నిర్వచితమైతే SDL_USE_LIBDBUS
        ఎంపిక (theme) {
            స్థితి SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                ఆపు;
#ఒకవేళ 0
            స్థితి SDL_SYSTEM_THEME_LIGHT_ఎగువ_CONTRAST:
                colorhints = g_default_colors_light_ఎగువ_contrast;
                ఆపు;
            స్థితి SDL_SYSTEM_THEME_DARK_ఎగువ_CONTRAST:
                colorhints = g_default_colors_dark_ఎగువ_contrast;
                ఆపు;
#అయితే_ముగింపు
            అప్రమేయ:
                colorhints = g_default_colors;
        }
#లేకపోతే
        colorhints = g_default_colors;
#అయితే_ముగింపు
    }
    కిటికీ->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    కొరకు (i = 0; i < SDL_MESSAGEBOX_COLOR_లెక్క; i++) {
        కిటికీ->xcolor[i].flags = DoRed|DoGreen|DoBlue;
        కిటికీ->xcolor[i].red = colorhints[i].r * 257;
        కిటికీ->xcolor[i].green = colorhints[i].g * 257;
        కిటికీ->xcolor[i].blue = colorhints[i].b * 257;
    }

    /* Generate bevel and pressed colors */
    కిటికీ->xcolor_bevel_l1.flags = DoRed|DoGreen|DoBlue;
    కిటికీ->xcolor_bevel_l1.red = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 12500, 0, 65535);
    కిటికీ->xcolor_bevel_l1.green = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 12500, 0, 65535);
    కిటికీ->xcolor_bevel_l1.blue = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 12500, 0, 65535);

    కిటికీ->xcolor_bevel_l2.flags = DoRed|DoGreen|DoBlue;
    కిటికీ->xcolor_bevel_l2.red = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 32500, 0, 65535);
    కిటికీ->xcolor_bevel_l2.green = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 32500, 0, 65535);
    కిటికీ->xcolor_bevel_l2.blue = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 32500, 0, 65535);

    కిటికీ->xcolor_bevel_d.flags = DoRed|DoGreen|DoBlue;
    కిటికీ->xcolor_bevel_d.red = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red - 22500, 0, 65535);
    కిటికీ->xcolor_bevel_d.green = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green - 22500, 0, 65535);
    కిటికీ->xcolor_bevel_d.blue = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue - 22500, 0, 65535);

    కిటికీ->xcolor_pressed.flags = DoRed|DoGreen|DoBlue;
    కిటికీ->xcolor_pressed.red = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].red - 12500, 0, 65535);
    కిటికీ->xcolor_pressed.green = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].green - 12500, 0, 65535);
    కిటికీ->xcolor_pressed.blue = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].blue - 12500, 0, 65535);

    కిటికీ->xcolor_disabled_పాఠ్యం.flags = DoRed|DoGreen|DoBlue;
    కిటికీ->xcolor_disabled_పాఠ్యం.red = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_పాఠ్యం].red + 19500, 0, 65535);
    కిటికీ->xcolor_disabled_పాఠ్యం.green = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_పాఠ్యం].green + 19500, 0, 65535);
    కిటికీ->xcolor_disabled_పాఠ్యం.blue = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_పాఠ్యం].blue + 19500, 0, 65535);

    /* Screen */
    కిటికీ->మాతృ = మాతృ;
    ఒకవేళ (మాతృ) {
        SDL_Display_దత్తాంశం *displaydata = SDL_Get_Display_Driver_దత్తాంశం_For_కిటికీ(మాతృ);
        కిటికీ->screen = displaydata->screen;
    } లేకపోతే {
        కిటికీ->screen = DefaultScreen(కిటికీ->display);
    }

    /* Visuals */
    ఒకవేళ (బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_బిడ్డ) {
        కిటికీ->visual = మాతృ->అంతర్గత->visual;
        కిటికీ->cmap = మాతృ->అంతర్గత->colormap;
        X11_GetVisualInfoFromVisual(కిటికీ->display, కిటికీ->visual, &కిటికీ->vi);
        కిటికీ->లోతు_2 = కిటికీ->vi.లోతు_2;
    } లేకపోతే {
        కిటికీ->visual = DefaultVisual(కిటికీ->display, కిటికీ->screen);
        కిటికీ->cmap = DefaultColormap(కిటికీ->display, కిటికీ->screen);
        కిటికీ->లోతు_2 = Default_లోతు(కిటికీ->display, కిటికీ->screen);
        X11_GetVisualInfoFromVisual(కిటికీ->display, కిటికీ->visual, &కిటికీ->vi);
    }

    /* Allocate colors */
    కొరకు (i = 0; i < SDL_MESSAGEBOX_COLOR_లెక్క; i++) {
        X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &కిటికీ->xcolor[i]);
    }
    X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &కిటికీ->xcolor_bevel_l1);
    X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &కిటికీ->xcolor_bevel_l2);
    X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &కిటికీ->xcolor_bevel_d);
    X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &కిటికీ->xcolor_pressed);
    X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &కిటికీ->xcolor_disabled_పాఠ్యం);

    /* Control list */
    కిటికీ->has_focus = false;
    కిటికీ->controls = ఖాళీ;
    కిటికీ->controls_sz = 0;
    కిటికీ->dyn_controls_sz = 0;
    కిటికీ->fiddled_control = ఖాళీ;
    కిటికీ->dyn_controls = ఖాళీ;

    /* Menu windows */
    కిటికీ->popup_windows = ఖాళీ;

    /* BIDI engine */
#నిర్వచితమైతే HAVE_FRIBIDI_H
    కిటికీ->fribidi = SDL_FriBidi_Create();
#అయితే_ముగింపు

#నిర్వచితమైతే HAVE_LIBTHAI_H
    కిటికీ->th = SDL_LibThai_Create();
#అయితే_ముగింపు
    
    /* Interface direction */
    కిటికీ->flip_interface = X11Toolkit_ShouldFlipUI();
    
    తిరిగి కిటికీ;
}

స్థిర శూన్య X11_Toolkit_కూడు_Control_గమ్యం_కిటికీ(SDL_Toolkit_కిటికీ_X11 *కిటికీ, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    కిటికీ->controls_sz++;
    ఒకవేళ (కిటికీ->controls_sz == 1) {
        కిటికీ->controls = (నిర్మాణం SDL_ToolkitControlX11 **)SDL_malloc(పరిమాణం(నిర్మాణం SDL_ToolkitControlX11 *));
    } లేకపోతే {
        కిటికీ->controls = (నిర్మాణం SDL_ToolkitControlX11 **)SDL_realloc(కిటికీ->controls, పరిమాణం(నిర్మాణం SDL_ToolkitControlX11 *) * కిటికీ->controls_sz);
    }
    కిటికీ->controls[కిటికీ->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    ఒకవేళ (control->dynamic) {
        కిటికీ->dyn_controls_sz++;
        ఒకవేళ (కిటికీ->dyn_controls_sz == 1) {
            కిటికీ->dyn_controls = (నిర్మాణం SDL_ToolkitControlX11 **)SDL_malloc(పరిమాణం(నిర్మాణం SDL_ToolkitControlX11 *));
        } లేకపోతే {
            కిటికీ->dyn_controls = (నిర్మాణం SDL_ToolkitControlX11 **)SDL_realloc(కిటికీ->dyn_controls, పరిమాణం(నిర్మాణం SDL_ToolkitControlX11 *) * కిటికీ->dyn_controls_sz);
        }
        కిటికీ->dyn_controls[కిటికీ->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    ఒకవేళ (control->selected) {
        కిటికీ->focused_control = control;
    }
}

bool X11_Toolkit_Create_కిటికీ_Res(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం, పూర్ణాంకం w, పూర్ణాంకం h, పూర్ణాంకం cx, పూర్ణాంకం cy, అక్షరం *title)
{
    పూర్ణాంకం x, y;
    XSizeHints *sizehints;
    XSet_కిటికీ_లక్షణాలు wnd_attr;
    Atom NET_WM_కిటికీ_TYPE, NET_WM_కిటికీ_TYPE_DIALOG, NET_WM_కిటికీ_TYPE_DROPDOWN_MENU, NET_WM_కిటికీ_TYPE_TOOLTIP;
    SDL_కిటికీ_దత్తాంశం *windowdata = ఖాళీ;
    Display *display = దత్తాంశం->display;
    XGCValues ctx_vals;
    కిటికీ_2 మూలం_win;
    కిటికీ_2 మాతృ_win;
    గుర్తులేని దీర్ఘ gcflags = GCForeground | GCBackground;
    గుర్తులేని దీర్ఘ valuemask;
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
#నిర్వచితమైతే XRANDR_DISABLED_BY_DEFAULT
    స్థిరరాశి bool use_xrandr_by_default = false;
#లేకపోతే
    స్థిరరాశి bool use_xrandr_by_default = true;
#అయితే_ముగింపు
#అయితే_ముగింపు

    ఒకవేళ (దత్తాంశం->scale == 0) {
        దత్తాంశం->కిటికీ_వెడల్పు = w;
        దత్తాంశం->కిటికీ_ఎత్తు = h;
    } లేకపోతే {
        దత్తాంశం->కిటికీ_వెడల్పు = SDL_lroundf((w/దత్తాంశం->iscale) * దత్తాంశం->scale);
        దత్తాంశం->కిటికీ_ఎత్తు = SDL_lroundf((h/దత్తాంశం->iscale) * దత్తాంశం->scale);
        దత్తాంశం->pixmap_వెడల్పు = w;
        దత్తాంశం->pixmap_ఎత్తు = h;
        దత్తాంశం->pixmap = true;
    }

    ఒకవేళ (దత్తాంశం->మాతృ) {
        windowdata = దత్తాంశం->మాతృ->అంతర్గత;
    }

    valuemask = CWEvent_ముసుగు | CWColormap;
    దత్తాంశం->event_ముసుగు = Exposure_ముసుగు |
                       Button_Press_ముసుగు | Button_Release_ముసుగు | కీలకం_Press_ముసుగు | కీలకం_Release_ముసుగు |
                       Structure_Notify_ముసుగు | Focus_Change_ముసుగు | సూచిక_Motion_ముసుగు;
    wnd_attr.event_ముసుగు = దత్తాంశం->event_ముసుగు;
    wnd_attr.colormap = దత్తాంశం->cmap;
    ఒకవేళ (దత్తాంశం->బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_MENU || దత్తాంశం->బహుళకం== SDL_TOOLKIT_కిటికీ_బహుళకం_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    మూలం_win = మూలం_కిటికీ(display, దత్తాంశం->screen);
    ఒకవేళ (దత్తాంశం->బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_బిడ్డ) {
        మాతృ_win = windowdata->xwindow;
    } లేకపోతే {
        మాతృ_win = మూలం_win;
    }

    దత్తాంశం->కిటికీ = X11_XCreate_కిటికీ(
        display, మాతృ_win,
        0, 0,
        దత్తాంశం->కిటికీ_వెడల్పు, దత్తాంశం->కిటికీ_ఎత్తు,
        0, దత్తాంశం->లోతు_2, ఆదానం_Output, దత్తాంశం->visual,
        valuemask, &wnd_attr);
    ఒకవేళ (దత్తాంశం->కిటికీ == None) {
        తిరిగి SDL_సమితి_Error("Couldn't create X window");
    }

    ఒకవేళ (windowdata && దత్తాంశం->బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_DIALOG) {
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
        X11_XChangeProperty(display, దత్తాంశం->కిటికీ, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_బహుళకం_Replace, (గుర్తులేని అక్షరం *)stateatoms, statecount);
    }

    ఒకవేళ (windowdata && దత్తాంశం->బహుళకం != SDL_TOOLKIT_కిటికీ_బహుళకం_X11_బిడ్డ) {
        X11_XSetTransientForHint(display, దత్తాంశం->కిటికీ, windowdata->xwindow);
    }

    ఒకవేళ (దత్తాంశం->tk_మాతృ) {
        X11_XSetTransientForHint(display, దత్తాంశం->కిటికీ, దత్తాంశం->tk_మాతృ->కిటికీ);
    }

    SDL_X11_సమితి_కిటికీ_Title(display, దత్తాంశం->కిటికీ, title);

    // Let the window manager the type of the window
    ఒకవేళ (దత్తాంశం->బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_DIALOG) {
        NET_WM_కిటికీ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_కిటికీ_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, దత్తాంశం->కిటికీ, NET_WM_కిటికీ_TYPE, XA_ATOM, 32,
                            Prop_బహుళకం_Replace,
                            (గుర్తులేని అక్షరం *)&NET_WM_కిటికీ_TYPE_DIALOG, 1);
    } లేకపోతే ఒకవేళ (దత్తాంశం->బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_MENU) {
        NET_WM_కిటికీ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_కిటికీ_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, దత్తాంశం->కిటికీ, NET_WM_కిటికీ_TYPE, XA_ATOM, 32,
                            Prop_బహుళకం_Replace,
                            (గుర్తులేని అక్షరం *)&NET_WM_కిటికీ_TYPE_DROPDOWN_MENU, 1);
    } లేకపోతే ఒకవేళ (దత్తాంశం->బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_TOOLTIP) {
        NET_WM_కిటికీ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_కిటికీ_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, దత్తాంశం->కిటికీ, NET_WM_కిటికీ_TYPE, XA_ATOM, 32,
                            Prop_బహుళకం_Replace,
                            (గుర్తులేని అక్షరం *)&NET_WM_కిటికీ_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    దత్తాంశం->wm_delete_సందేశం = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, దత్తాంశం->కిటికీ, &దత్తాంశం->wm_delete_సందేశం, 1);
    దత్తాంశం->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    ఒకవేళ (దత్తాంశం->బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_MENU || దత్తాంశం->బహుళకం== SDL_TOOLKIT_కిటికీ_బహుళకం_X11_TOOLTIP) {
        x = cx;
        y = cy;
        వెళ్ళు MOVEWINDOW;
    }
    ఒకవేళ (windowdata) {
        XWindow_లక్షణాలు attrib;
        కిటికీ_2 dummy;

        X11_XGet_కిటికీ_లక్షణాలు(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.వెడల్పు - దత్తాంశం->కిటికీ_వెడల్పు) / 2;
        y = attrib.y + (attrib.ఎత్తు - దత్తాంశం->కిటికీ_ఎత్తు) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, మూలం_కిటికీ(display, దత్తాంశం->screen), x, y, &x, &y, &dummy);
    } లేకపోతే {
        స్థిరరాశి SDL_VideoDevice *dev = SDL_GetVideoDevice();
        ఒకవేళ (dev && dev->displays && dev->అంకె_displays > 0) {
            స్థిరరాశి SDL_VideoDisplay *dpy = dev->displays[0];
            స్థిరరాశి SDL_Display_దత్తాంశం *dpydata = dpy->అంతర్గత;
            x = dpydata->x + ((dpy->current_బహుళకం->w - దత్తాంశం->కిటికీ_వెడల్పు) / 2);
            y = dpydata->y + ((dpy->current_బహుళకం->h - దత్తాంశం->కిటికీ_ఎత్తు) / 3);
        }
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
        లేకపోతే ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && దత్తాంశం->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_బహిర్గతం;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, మూలం_win);
            ఒకవేళ (!screen_res) {
                వెళ్ళు NOXRANDR;
            }

            default_బహిర్గతం = X11_XRRGetOutputPrimary(display, మూలం_win);
            ఒకవేళ (default_బహిర్గతం != None) {
                XRROutputInfo *బహిర్గతం_info;

                బహిర్గతం_info = X11_XRRGetOutputInfo(display, screen_res, default_బహిర్గతం);
                ఒకవేళ (బహిర్గతం_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(బహిర్గతం_info);
                    వెళ్ళు FIRSTOUTPUTXRANDR;
                }

                ఒకవేళ (బహిర్గతం_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, బహిర్గతం_info->crtc);
                } లేకపోతే ఒకవేళ (బహిర్గతం_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, బహిర్గతం_info->crtcs[0]);
                } లేకపోతే {
                    crtc_info = ఖాళీ;
                }
                
                ఒకవేళ (crtc_info) {
                    x = (crtc_info->వెడల్పు - దత్తాంశం->కిటికీ_వెడల్పు) / 2;
                    y = (crtc_info->ఎత్తు - దత్తాంశం->కిటికీ_ఎత్తు) / 3;
                    X11_XRRFreeOutputInfo(బహిర్గతం_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } లేకపోతే {
                    X11_XRRFreeOutputInfo(బహిర్గతం_info);
                    వెళ్ళు NOXRANDR;
                }
            } లేకపోతే {
                    FIRSTOUTPUTXRANDR:
                    ఒకవేళ (screen_res->noutput > 0) {
                        XRROutputInfo *బహిర్గతం_info;

                        బహిర్గతం_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        ఒకవేళ (!బహిర్గతం_info) {
                            వెళ్ళు FIRSTCRTCXRANDR;
                        }

                        ఒకవేళ (బహిర్గతం_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, బహిర్గతం_info->crtc);
                        } లేకపోతే ఒకవేళ (బహిర్గతం_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, బహిర్గతం_info->crtcs[0]);
                        } లేకపోతే {
                            crtc_info = ఖాళీ;
                        }

                        ఒకవేళ (!crtc_info) {
                            X11_XRRFreeOutputInfo(బహిర్గతం_info);
                            వెళ్ళు FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->వెడల్పు - దత్తాంశం->కిటికీ_వెడల్పు) / 2;
                        y = (crtc_info->ఎత్తు - దత్తాంశం->కిటికీ_ఎత్తు) / 3;
                        X11_XRRFreeOutputInfo(బహిర్గతం_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        వెళ్ళు MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    ఒకవేళ (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        వెళ్ళు NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    ఒకవేళ (crtc_info) {
                        x = (crtc_info->వెడల్పు - దత్తాంశం->కిటికీ_వెడల్పు) / 2;
                        y = (crtc_info->ఎత్తు - దత్తాంశం->కిటికీ_ఎత్తు) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } లేకపోతే {
                        X11_XRRFreeScreenResources(screen_res);
                        వెళ్ళు NOXRANDR;
                    }
            }
        }
#అయితే_ముగింపు
        లేకపోతే {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (Display_వెడల్పు(display, దత్తాంశం->screen) - దత్తాంశం->కిటికీ_వెడల్పు) / 2;
            y = (Display_ఎత్తు(display, దత్తాంశం->screen) - దత్తాంశం->కిటికీ_ఎత్తు) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMove_కిటికీ(display, దత్తాంశం->కిటికీ, x, y);
    దత్తాంశం->కిటికీ_x = x;
    దత్తాంశం->కిటికీ_y = y;

    sizehints = X11_XAlloc_కొలత_Hints();
    ఒకవేళ (sizehints) {
        sizehints->flags = USPosition | USSize | PMax_కొలత | PMin_కొలత;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->వెడల్పు = దత్తాంశం->కిటికీ_వెడల్పు;
        sizehints->ఎత్తు = దత్తాంశం->కిటికీ_ఎత్తు;

        sizehints->min_వెడల్పు_2 = sizehints->max_వెడల్పు_2 = దత్తాంశం->కిటికీ_వెడల్పు;
        sizehints->min_ఎత్తు_2 = sizehints->max_ఎత్తు_2 = దత్తాంశం->కిటికీ_ఎత్తు;

        X11_XSetWMNormalHints(display, దత్తాంశం->కిటికీ, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, దత్తాంశం->కిటికీ);

    దత్తాంశం->drawable = దత్తాంశం->కిటికీ;
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    ఒకవేళ (SDL_X11_HAVE_XDBE && !దత్తాంశం->pixmap) {
        పూర్ణాంకం xdbe_major, xdbe_minor;
        ఒకవేళ (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            దత్తాంశం->xdbe = true;
            దత్తాంశం->buf = X11_Xdbe_Allocate_వెనుక_బఫరు_Name(display, దత్తాంశం->కిటికీ, XdbeUndefined);
            దత్తాంశం->drawable = దత్తాంశం->buf;
        } లేకపోతే {
            దత్తాంశం->xdbe = false;
        }
    }
#అయితే_ముగింపు

    X11_Toolkit_Init_కిటికీ_Pixmap(దత్తాంశం);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = దత్తాంశం->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = దత్తాంశం->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ఒకవేళ (!దత్తాంశం->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = దత్తాంశం->font_struct->fid;
    }
    దత్తాంశం->ctx = X11_XCreateGC(దత్తాంశం->display, దత్తాంశం->drawable, gcflags, &ctx_vals);
    ఒకవేళ (దత్తాంశం->ctx == None) {
        తిరిగి SDL_సమితి_Error("Couldn't create graphics context");
    }

    దత్తాంశం->close = false;
    దత్తాంశం->కీలకం_control_esc = దత్తాంశం->కీలకం_control_enter = ఖాళీ;
    ఒకవేళ (!దత్తాంశం->pixmap) {
        దత్తాంశం->ev_scale = దత్తాంశం->ev_iscale = 1;
    } లేకపోతే {
        దత్తాంశం->ev_scale = దత్తాంశం->scale;
        దత్తాంశం->ev_iscale = దత్తాంశం->iscale;
    }

#ఒకవేళ SDL_GRAB
    ఒకవేళ (దత్తాంశం->బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_MENU || దత్తాంశం->బహుళకం== SDL_TOOLKIT_కిటికీ_బహుళకం_X11_TOOLTIP) {
        X11_XGrab_సూచిక(display, దత్తాంశం->కిటికీ, False, Button_Press_ముసుగు | Button_Release_ముసుగు | సూచిక_Motion_ముసుగు, Grab_బహుళకం_Async, Grab_బహుళకం_Async, None, None, Current_సమయం);
        X11_XGrabKeyboard(display, దత్తాంశం->కిటికీ, False, Grab_బహుళకం_Async, Grab_బహుళకం_Async, Current_సమయం);
    }
#అయితే_ముగింపు

    తిరిగి true;
}

స్థిర శూన్య X11_Toolkit_Draw_కిటికీ(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం) {
    SDL_Rect rect;
    పూర్ణాంకం i;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XDBE
    ఒకవేళ (SDL_X11_HAVE_XDBE && దత్తాంశం->xdbe && !దత్తాంశం->pixmap) {
        X11_XdbeBeginIdiom(దత్తాంశం->display);
    }
#అయితే_ముగింపు

    X11_XSetForeground(దత్తాంశం->display, దత్తాంశం->ctx, దత్తాంశం->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    ఒకవేళ (దత్తాంశం->pixmap) {
        X11_XFillRectangle(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->ctx, 0, 0, దత్తాంశం->pixmap_వెడల్పు, దత్తాంశం->pixmap_ఎత్తు);
    } లేకపోతే {
        X11_XFillRectangle(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->ctx, 0, 0, దత్తాంశం->కిటికీ_వెడల్పు, దత్తాంశం->కిటికీ_ఎత్తు);
    }

    కొరకు (i = 0; i < దత్తాంశం->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = దత్తాంశం->controls[i];
        ఒకవేళ (control) {
            ఒకవేళ (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XDBE
    ఒకవేళ (SDL_X11_HAVE_XDBE && దత్తాంశం->xdbe && !దత్తాంశం->pixmap) {
        Xdbe_మార్పిడి_Info మార్పిడి_info;
        మార్పిడి_info.మార్పిడి_కిటికీ = దత్తాంశం->కిటికీ;
        మార్పిడి_info.మార్పిడి_action = XdbeUndefined;
        X11_Xdbe_మార్పిడి_Buffers(దత్తాంశం->display, &మార్పిడి_info, 1);
        X11_Xdbe_చివర_Idiom(దత్తాంశం->display);
    }
#అయితే_ముగింపు

    ఒకవేళ (దత్తాంశం->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = దత్తాంశం->కిటికీ_వెడల్పు;
        rect.h = దత్తాంశం->కిటికీ_ఎత్తు;
#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
        ఒకవేళ (దత్తాంశం->shm) {
            ఒకవేళ (దత్తాంశం->shm_pixmap) {
                X11_XFlush(దత్తాంశం->display);
                X11_XSync(దత్తాంశం->display, false);
                scale_surface = SDL_CreateSurfaceFrom(దత్తాంశం->pixmap_వెడల్పు, దత్తాంశం->pixmap_ఎత్తు, X11_GetPixelFormatFromVisualInfo(దత్తాంశం->display, &దత్తాంశం->vi), దత్తాంశం->shm_info.shmaddr, దత్తాంశం->shm_బైట్లు_చొప్పున_పంక్తి);
                SDL_BlitSurfaceScaled(scale_surface, ఖాళీ, scale_surface, &rect, SDL_SCALEMODE_రేఖీయ);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->కిటికీ, దత్తాంశం->ctx, 0, 0, దత్తాంశం->కిటికీ_వెడల్పు, దత్తాంశం->కిటికీ_ఎత్తు, 0, 0);
            } లేకపోతే {
                X11_XShmGetImage(దత్తాంశం->display, దత్తాంశం->drawable, దత్తాంశం->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(దత్తాంశం->pixmap_వెడల్పు, దత్తాంశం->pixmap_ఎత్తు, X11_GetPixelFormatFromVisualInfo(దత్తాంశం->display, &దత్తాంశం->vi), దత్తాంశం->image->దత్తాంశం, దత్తాంశం->image->బైట్లు_చొప్పున_పంక్తి);
                SDL_BlitSurfaceScaled(scale_surface, ఖాళీ, scale_surface, &rect, SDL_SCALEMODE_రేఖీయ);
                X11_XShmPutImage(దత్తాంశం->display, దత్తాంశం->కిటికీ, దత్తాంశం->ctx, దత్తాంశం->image, 0, 0, 0, 0, దత్తాంశం->కిటికీ_వెడల్పు, దత్తాంశం->కిటికీ_ఎత్తు, False);
            }
        } లేకపోతే
#అయితే_ముగింపు
        {
            XImage *image;

            image = X11_XGetImage(దత్తాంశం->display, దత్తాంశం->drawable, 0, 0 , దత్తాంశం->pixmap_వెడల్పు, దత్తాంశం->pixmap_ఎత్తు, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(దత్తాంశం->pixmap_వెడల్పు, దత్తాంశం->pixmap_ఎత్తు, X11_GetPixelFormatFromVisualInfo(దత్తాంశం->display, &దత్తాంశం->vi), image->దత్తాంశం, image->బైట్లు_చొప్పున_పంక్తి);
            SDL_BlitSurfaceScaled(scale_surface, ఖాళీ, scale_surface, &rect, SDL_SCALEMODE_రేఖీయ);
            X11_XPutImage(దత్తాంశం->display, దత్తాంశం->కిటికీ, దత్తాంశం->ctx, image, 0, 0, 0, 0, దత్తాంశం->కిటికీ_వెడల్పు, దత్తాంశం->కిటికీ_ఎత్తు);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(దత్తాంశం->display);
}

స్థిర SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం, పూర్ణాంకం x, పూర్ణాంకం y)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < దత్తాంశం->controls_sz; i++) {
        SDL_Rect *rect = &దత్తాంశం->controls[i]->rect;
        ఒకవేళ ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            తిరిగి దత్తాంశం->controls[i];
        }
    }

    తిరిగి ఖాళీ;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
స్థిర Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_Toolkit_కిటికీ_X11 *దత్తాంశం = (SDL_Toolkit_కిటికీ_X11 *)arg;

    ఒకవేళ (event->xany.display != దత్తాంశం->display) {
        తిరిగి False;
    }

    ఒకవేళ (event->xany.కిటికీ == దత్తాంశం->కిటికీ) {
        తిరిగి True;
    }

    తిరిగి False;
}

శూన్య X11_Toolkit_Process_కిటికీ_Events(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    ఒకవేళ ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        తిరిగి;
    }

    దత్తాంశం->draw = false;
    దత్తాంశం->e = e;

    ఎంపిక (e->type) {
        స్థితి Expose:
            దత్తాంశం->draw = true;
            ఆపు;
        స్థితి Client_సందేశం:
            ఒకవేళ (e->xclient.సందేశం_type == దత్తాంశం->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.దత్తాంశం.l[0] == దత్తాంశం->wm_delete_సందేశం) {
                దత్తాంశం->close = true;
            }
            ఆపు;
        స్థితి Focus_లోపల:
            దత్తాంశం->has_focus = true;
            ఆపు;
        స్థితి Focus_బహిర్గతం:
            దత్తాంశం->has_focus = false;
            ఒకవేళ (దత్తాంశం->fiddled_control) {
                దత్తాంశం->fiddled_control->selected = false;
            }
            దత్తాంశం->fiddled_control = ఖాళీ;
            కొరకు (దత్తాంశం->ev_i = 0; దత్తాంశం->ev_i < దత్తాంశం->controls_sz; దత్తాంశం->ev_i++) {
                దత్తాంశం->controls[దత్తాంశం->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_సాధారణ;
            }
            ఆపు;
        స్థితి MotionNotify:
            ఒకవేళ (దత్తాంశం->has_focus) {
                దత్తాంశం->మునుపటి_control = దత్తాంశం->fiddled_control;
                దత్తాంశం->fiddled_control = X11Toolkit_GetControlMouseIsOn(దత్తాంశం, SDL_lroundf((e->xbutton.x/ దత్తాంశం->ev_scale)* దత్తాంశం->ev_iscale), SDL_lroundf((e->xbutton.y/ దత్తాంశం->ev_scale)* దత్తాంశం->ev_iscale));
                ఒకవేళ (దత్తాంశం->మునుపటి_control) {
                    దత్తాంశం->మునుపటి_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_సాధారణ;
                    ఒకవేళ (దత్తాంశం->మునుపటి_control->func_on_state_change) {
                        దత్తాంశం->మునుపటి_control->func_on_state_change(దత్తాంశం->మునుపటి_control);
                    }
                    దత్తాంశం->draw = true;
                }
                ఒకవేళ (దత్తాంశం->fiddled_control) {
                    ఒకవేళ (దత్తాంశం->fiddled_control->dynamic) {
                        దత్తాంశం->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        ఒకవేళ (దత్తాంశం->fiddled_control->func_on_state_change) {
                            దత్తాంశం->fiddled_control->func_on_state_change(దత్తాంశం->fiddled_control);
                        }
                        దత్తాంశం->draw = true;
                    } లేకపోతే {
                        దత్తాంశం->fiddled_control = ఖాళీ;
                    }
                }
            }
            ఆపు;
        స్థితి ButtonPress:
            దత్తాంశం->మునుపటి_control = దత్తాంశం->fiddled_control;
            ఒకవేళ (దత్తాంశం->మునుపటి_control) {
                దత్తాంశం->మునుపటి_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_సాధారణ;
                ఒకవేళ (దత్తాంశం->మునుపటి_control->func_on_state_change) {
                    దత్తాంశం->మునుపటి_control->func_on_state_change(దత్తాంశం->మునుపటి_control);
                }
                దత్తాంశం->draw = true;
            }
            ఒకవేళ (e->xbutton.button == Button1) {
                దత్తాంశం->fiddled_control = X11Toolkit_GetControlMouseIsOn(దత్తాంశం, SDL_lroundf((e->xbutton.x/ దత్తాంశం->ev_scale)* దత్తాంశం->ev_iscale), SDL_lroundf((e->xbutton.y/ దత్తాంశం->ev_scale)* దత్తాంశం->ev_iscale));
                ఒకవేళ (దత్తాంశం->fiddled_control) {
                    దత్తాంశం->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    ఒకవేళ (దత్తాంశం->fiddled_control->func_on_state_change) {
                        దత్తాంశం->fiddled_control->func_on_state_change(దత్తాంశం->fiddled_control);
                    }
                    దత్తాంశం->draw = true;
                }
            }
            ఆపు;
        స్థితి ButtonRelease:
            ఒకవేళ (దత్తాంశం->బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_MENU || దత్తాంశం->బహుళకం== SDL_TOOLKIT_కిటికీ_బహుళకం_X11_TOOLTIP) {
                పూర్ణాంకం cx;
                పూర్ణాంకం cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                ఒకవేళ (cy < 0 || cx < 0) {
                    దత్తాంశం->close = true;
                }

                ఒకవేళ (cy > దత్తాంశం->కిటికీ_ఎత్తు || cx > దత్తాంశం->కిటికీ_వెడల్పు) {
                    దత్తాంశం->close = true;
                }
            }

            ఒకవేళ ((e->xbutton.button == Button1) && (దత్తాంశం->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(దత్తాంశం, SDL_lroundf((e->xbutton.x/ దత్తాంశం->ev_scale)* దత్తాంశం->ev_iscale), SDL_lroundf((e->xbutton.y/ దత్తాంశం->ev_scale)* దత్తాంశం->ev_iscale));
                ఒకవేళ (దత్తాంశం->fiddled_control == control) {
                    దత్తాంశం->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    ఒకవేళ (దత్తాంశం->fiddled_control->func_on_state_change) {
                        దత్తాంశం->fiddled_control->func_on_state_change(దత్తాంశం->fiddled_control);
                    }
                    దత్తాంశం->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_సాధారణ;
                    దత్తాంశం->draw = true;
                }
            }
            ఆపు;
        స్థితి కీలకం_Press:
            దత్తాంశం->చివరి_కీలకం_pressed = X11_XLookupKeysym(&e->xkey, 0);

            ఒకవేళ (దత్తాంశం->చివరి_కీలకం_pressed == XK_Escape) {
                కొరకు (దత్తాంశం->ev_i = 0; దత్తాంశం->ev_i < దత్తాంశం->controls_sz; దత్తాంశం->ev_i++) {
                    ఒకవేళ(దత్తాంశం->controls[దత్తాంశం->ev_i]->is_default_esc) {
                        దత్తాంశం->controls[దత్తాంశం->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        దత్తాంశం->draw = true;
                        దత్తాంశం->కీలకం_control_esc = దత్తాంశం->controls[దత్తాంశం->ev_i];
                    }
                }
            } లేకపోతే ఒకవేళ ((దత్తాంశం->చివరి_కీలకం_pressed == XK_Return) || (దత్తాంశం->చివరి_కీలకం_pressed == XK_KP_Enter)) {
                కొరకు (దత్తాంశం->ev_i = 0; దత్తాంశం->ev_i < దత్తాంశం->controls_sz; దత్తాంశం->ev_i++) {
                    ఒకవేళ(దత్తాంశం->controls[దత్తాంశం->ev_i]->selected) {
                        దత్తాంశం->controls[దత్తాంశం->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        దత్తాంశం->draw = true;
                        దత్తాంశం->కీలకం_control_enter = దత్తాంశం->controls[దత్తాంశం->ev_i];
                    }
                }
            }
            ఆపు;
        స్థితి కీలకం_Release:
        {
            కీలకం_Sym కీలకం = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            ఒకవేళ (కీలకం != దత్తాంశం->చివరి_కీలకం_pressed) {
                ఆపు;
            }

            ఒకవేళ (కీలకం == XK_Escape) {
                ఒకవేళ (దత్తాంశం->కీలకం_control_esc) {
                    ఒకవేళ (దత్తాంశం->కీలకం_control_esc->func_on_state_change) {
                        దత్తాంశం->కీలకం_control_esc->func_on_state_change(దత్తాంశం->కీలకం_control_esc);
                    }
                }
            } లేకపోతే ఒకవేళ ((కీలకం == XK_Return) || (కీలకం == XK_KP_Enter)) {
                ఒకవేళ (దత్తాంశం->కీలకం_control_enter) {
                    ఒకవేళ (దత్తాంశం->కీలకం_control_enter->func_on_state_change) {
                        దత్తాంశం->కీలకం_control_enter->func_on_state_change(దత్తాంశం->కీలకం_control_enter);
                    }
                }
            } లేకపోతే ఒకవేళ (కీలకం == XK_Tab || కీలకం == XK_ఎడమ || కీలకం == XK_కుడి) {
                ఒకవేళ (దత్తాంశం->focused_control) {
                    దత్తాంశం->focused_control->selected = false;
                }
                దత్తాంశం->draw = true;
                కొరకు (దత్తాంశం->ev_i = 0; దత్తాంశం->ev_i < దత్తాంశం->dyn_controls_sz; దత్తాంశం->ev_i++) {
                    ఒకవేళ (దత్తాంశం->dyn_controls[దత్తాంశం->ev_i] == దత్తాంశం->focused_control) {
                        పూర్ణాంకం తదుపరి_సూచీ;

                        ఒకవేళ (కీలకం == XK_ఎడమ) {
                            తదుపరి_సూచీ = దత్తాంశం->ev_i - 1;
                        } లేకపోతే {
                            తదుపరి_సూచీ = దత్తాంశం->ev_i + 1;
                        }
                        ఒకవేళ ((తదుపరి_సూచీ >= దత్తాంశం->dyn_controls_sz) || (తదుపరి_సూచీ < 0)) {
                            ఒకవేళ (కీలకం == XK_కుడి || కీలకం == XK_ఎడమ) {
                                తదుపరి_సూచీ = దత్తాంశం->ev_i;
                            } లేకపోతే {
                                తదుపరి_సూచీ = 0;
                            }
                        }
                        దత్తాంశం->focused_control = దత్తాంశం->dyn_controls[తదుపరి_సూచీ];
                        దత్తాంశం->focused_control->selected = true;
                        ఆపు;
                    }
                }
            }
            ఆపు;
        }
    }

    ఒకవేళ (దత్తాంశం->draw) {
        X11_Toolkit_Draw_కిటికీ(దత్తాంశం);
    }
}

శూన్య X11_Toolkit_Do_కిటికీ_Event_Loop(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం) {
   అయితే (!దత్తాంశం->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(దత్తాంశం->display, &e);
        ఒకవేళ (దత్తాంశం->xsettings) {
            xsettings_client_process_event(దత్తాంశం->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(దత్తాంశం->display, &e, X11Toolkit_EventTest, (XPointer)దత్తాంశం);
        X11_Toolkit_Process_కిటికీ_Events(దత్తాంశం, &e);
    }
}


శూన్య X11_Toolkit_Resize_కిటికీ(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం, పూర్ణాంకం w, పూర్ణాంకం h) {
    ఒకవేళ (!దత్తాంశం->pixmap) {
        దత్తాంశం->కిటికీ_వెడల్పు = w;
        దత్తాంశం->కిటికీ_ఎత్తు = h;
    } లేకపోతే {
        దత్తాంశం->కిటికీ_వెడల్పు = SDL_lroundf((w/దత్తాంశం->iscale) * దత్తాంశం->scale);
        దత్తాంశం->కిటికీ_ఎత్తు = SDL_lroundf((h/దత్తాంశం->iscale) * దత్తాంశం->scale);
        దత్తాంశం->pixmap_వెడల్పు = w;
        దత్తాంశం->pixmap_ఎత్తు = h;
        X11_XFreePixmap(దత్తాంశం->display, దత్తాంశం->drawable);
        X11_Toolkit_Init_కిటికీ_Pixmap(దత్తాంశం);
    }

    X11_XResize_కిటికీ(దత్తాంశం->display, దత్తాంశం->కిటికీ, దత్తాంశం->కిటికీ_వెడల్పు, దత్తాంశం->కిటికీ_ఎత్తు);
}

స్థిర శూన్య X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->కిటికీ->display, icon_control->icon_char_font);
    SDL_free(control);
}

స్థిర శూన్య X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->కిటికీ->iscale;
    control->rect.h -= 2 * control->కిటికీ->iscale;
    X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx, control->rect.x + (2 * control->కిటికీ->iscale), control->rect.y + (2* control->కిటికీ->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    ఎంపిక (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        స్థితి SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx, control->rect.x+(1* control->కిటికీ->iscale), control->rect.y+(1* control->కిటికీ->iscale), control->rect.w-(2* control->కిటికీ->iscale), control->rect.h-(2* control->కిటికీ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, icon_control->xcolor_white.pixel);
                ఆపు;
        స్థితి SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx, control->rect.x+(1* control->కిటికీ->iscale), control->rect.y+(1* control->కిటికీ->iscale), control->rect.w-(2* control->కిటికీ->iscale), control->rect.h-(2* control->కిటికీ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, icon_control->xcolor_black.pixel);
                ఆపు;
        స్థితి SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx, control->rect.x+(1* control->కిటికీ->iscale), control->rect.y+(1* control->కిటికీ->iscale), control->rect.w-(2* control->కిటికీ->iscale), control->rect.h-(2* control->కిటికీ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, icon_control->xcolor_white.pixel);
                ఆపు;
    }
    X11_XSetFont(control->కిటికీ->display, control->కిటికీ->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    ఒకవేళ (!control->కిటికీ->utf8) {
        X11_XSetFont(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->font_struct->fid);
    }

    control->rect.w += 2 * control->కిటికీ->iscale;
    control->rect.h += 2 * control->కిటికీ->iscale;
}

స్థిర శూన్య X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *పునాది_control) {
    SDL_ToolkitIconControlX11 *control;
    పూర్ణాంకం icon_char_w;
    పూర్ణాంకం icon_wh;

    control = (SDL_ToolkitIconControlX11 *)పునాది_control;
    X11_Toolkit_Get_పాఠ్యం_వెడల్పు_ఎత్తు_For_Font(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, ఖాళీ);
    పునాది_control->rect.w = icon_char_w;
    పునాది_control->rect.h = control->icon_char_h;
    icon_wh = SDL_max(icon_char_w, control->icon_char_h) + SDL_TOOLKIT_X11_ELEMENT_PADDING * 2 * పునాది_control->కిటికీ->iscale;
    పునాది_control->rect.w = icon_wh;
    పునాది_control->rect.h = icon_wh;
    పునాది_control->rect.y = 0;
    పునాది_control->rect.x = 0;
    control->icon_char_y = control->icon_char_a + (పునాది_control->rect.h - control->icon_char_h)/2;
    control->icon_char_x = (పునాది_control->rect.w - icon_char_w)/2;
    పునాది_control->rect.w += 2 * పునాది_control->కిటికీ->iscale;
    పునాది_control->rect.h += 2 * పునాది_control->కిటికీ->iscale;
}

స్థిర శూన్య X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *పునాది_control) {
    SDL_ToolkitIconControlX11 *control;
    అక్షరం *font;

    control = (SDL_ToolkitIconControlX11 *)పునాది_control;
    X11_XFreeFont(పునాది_control->కిటికీ->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_కొలత * పునాది_control->కిటికీ->iscale);
    control->icon_char_font = X11_XLoadQueryFont(పునాది_control->కిటికీ->display, font);
    SDL_free(font);
    ఒకవేళ (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_కొలత * పునాది_control->కిటికీ->iscale);
        control->icon_char_font = X11_XLoadQueryFont(పునాది_control->కిటికీ->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_కిటికీ_X11 *కిటికీ, SDL_సందేశం_Box_Flags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *పునాది_control;
    అక్షరం *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(పరిమాణం(SDL_ToolkitIconControlX11));
    పునాది_control = (SDL_ToolkitControlX11 *)control;
    ఒకవేళ (!control) {
        SDL_సమితి_Error("Unable to allocate icon control structure");
        తిరిగి ఖాళీ;
    }

    /* Fill out struct */
    పునాది_control->కిటికీ = కిటికీ;
    పునాది_control->func_draw = X11Toolkit_DrawIconControl;
    పునాది_control->func_free = X11Toolkit_DestroyIconControl;
    పునాది_control->func_on_state_change = ఖాళీ;
    పునాది_control->func_calc_కొలత = X11Toolkit_CalculateIconControl;
    పునాది_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    పునాది_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_సాధారణ;
    పునాది_control->selected = false;
    పునాది_control->dynamic = false;
    పునాది_control->is_default_enter = false;
    పునాది_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_కొలత * కిటికీ->iscale);
    control->icon_char_font = X11_XLoadQueryFont(కిటికీ->display, font);
    SDL_free(font);
    ఒకవేళ (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_కొలత * కిటికీ->iscale);
        control->icon_char_font = X11_XLoadQueryFont(కిటికీ->display, font);
        SDL_free(font);
        ఒకవేళ (!control->icon_char_font) {
            SDL_free(control);
            తిరిగి ఖాళీ;
        }
    }

    /* Set colors */
    ఎంపిక (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    స్థితి SDL_MESSAGEBOX_ERROR:
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
        X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &control->xcolor_white);
        X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &control->xcolor_red);
        X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &control->xcolor_red_darker);
        ఆపు;
    స్థితి SDL_MESSAGEBOX_WARNING:
        control->icon_char = '!';
        control->xcolor_black.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_black.red = 0;
        control->xcolor_black.green = 0;
        control->xcolor_black.blue = 0;
        control->xcolor_yellow.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_yellow.red = 65535;
        control->xcolor_yellow.green = 65535;
        control->xcolor_yellow.blue = 0;
        X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &control->xcolor_black);
        X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &control->xcolor_yellow);
        ఆపు;
    స్థితి SDL_MESSAGEBOX_INFORMATION:
        control->icon_char = 'i';
        control->xcolor_white.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_white.red = 65535;
        control->xcolor_white.green = 65535;
        control->xcolor_white.blue = 65535;
        control->xcolor_blue.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_blue.red = 0;
        control->xcolor_blue.green = 0;
        control->xcolor_blue.blue = 65535;
        X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &control->xcolor_white);
        X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &control->xcolor_blue);
        ఆపు;
    అప్రమేయ:
        X11_XFreeFont(కిటికీ->display, control->icon_char_font);
        SDL_free(control);
        తిరిగి ఖాళీ;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    ఒకవేళ (కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } లేకపోతే ఒకవేళ (కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } లేకపోతే {
        control->xcolor_bg_shadow.red = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    ఒకవేళ (కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } లేకపోతే ఒకవేళ (కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } లేకపోతే {
        control->xcolor_bg_shadow.green = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    ఒకవేళ (కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } లేకపోతే ఒకవేళ (కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } లేకపోతే {
        control->xcolor_bg_shadow.blue = SDL_clamp(కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(కిటికీ->display, కిటికీ->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(పునాది_control);

    X11_Toolkit_కూడు_Control_గమ్యం_కిటికీ(కిటికీ, పునాది_control);
    తిరిగి పునాది_control;
}

bool X11_Toolkit_Notify_Control_యొక్క_కొలత_Change(SDL_ToolkitControlX11 *control) {
    ఒకవేళ (control->func_calc_కొలత) {
        control->func_calc_కొలత(control);
        తిరిగి true;
    } లేకపోతే {
        తిరిగి false;
    }
}

స్థిర శూన్య X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11_Toolkit_Get_పాఠ్యం_Elements_Rect(button_control->పాఠ్యం, &button_control->పాఠ్యం_rect);
    ఒకవేళ (control->do_కొలత) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->కిటికీ->iscale + button_control->పాఠ్యం_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->కిటికీ->iscale + button_control->పాఠ్యం_rect.h;
    }
    button_control->పాఠ్యం_rect.x = (control->rect.w - button_control->పాఠ్యం_rect.w)/2;
    button_control->పాఠ్యం_rect.y = (control->rect.h - button_control->పాఠ్యం_rect.h)/2;
}


స్థిర శూన్య X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_పాఠ్యం].pixel);
    /* Draw bevel */
    ఒకవేళ (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
            X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor_bevel_d.pixel);
            X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

            X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor_bevel_l2.pixel);
            X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - (1* control->కిటికీ->iscale), control->rect.h - (1* control->కిటికీ->iscale));

            X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor_bevel_l1.pixel);
            X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x + 1 * control->కిటికీ->iscale, control->rect.y + 1 * control->కిటికీ->iscale,
                                   control->rect.w - 3 * control->కిటికీ->iscale, control->rect.h - 2 * control->కిటికీ->iscale);

            X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
            X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                               control->rect.x + 1 * control->కిటికీ->iscale, control->rect.y + 1 * control->కిటికీ->iscale,
                               control->rect.w - 3 * control->కిటికీ->iscale, control->rect.h - 3 * control->కిటికీ->iscale);

            X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor_pressed.pixel);
            X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                               control->rect.x + 2 * control->కిటికీ->iscale, control->rect.y + 2 * control->కిటికీ->iscale,
                               control->rect.w - 4 * control->కిటికీ->iscale, control->rect.h - 4 * control->కిటికీ->iscale);
        } లేకపోతే {
            ఒకవేళ (control->selected) {
                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x + 1 * control->కిటికీ->iscale, control->rect.y + 1 * control->కిటికీ->iscale,
                                   control->rect.w - 3 * control->కిటికీ->iscale, control->rect.h - 3 * control->కిటికీ->iscale);

                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x + 2 * control->కిటికీ->iscale, control->rect.y + 2 * control->కిటికీ->iscale,
                                   control->rect.w - 4 * control->కిటికీ->iscale, control->rect.h - 4 * control->కిటికీ->iscale);

                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x + 2 * control->కిటికీ->iscale, control->rect.y + 2 * control->కిటికీ->iscale,
                                   control->rect.w - 5 * control->కిటికీ->iscale, control->rect.h - 5 * control->కిటికీ->iscale);

                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x + 3 * control->కిటికీ->iscale, control->rect.y + 3 * control->కిటికీ->iscale,
                                   control->rect.w - 6 * control->కిటికీ->iscale, control->rect.h - 6 * control->కిటికీ->iscale);
            } లేకపోతే {
                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - 1 * control->కిటికీ->iscale, control->rect.h - 1 * control->కిటికీ->iscale);

                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x + 1 * control->కిటికీ->iscale, control->rect.y + 1 * control->కిటికీ->iscale,
                                   control->rect.w - 2 * control->కిటికీ->iscale, control->rect.h - 2 * control->కిటికీ->iscale);

                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x + 1 * control->కిటికీ->iscale, control->rect.y + 1 * control->కిటికీ->iscale,
                                   control->rect.w - 3 * control->కిటికీ->iscale, control->rect.h - 3 * control->కిటికీ->iscale);

                X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->కిటికీ->display, control->కిటికీ->drawable, control->కిటికీ->ctx,
                                   control->rect.x + 2 * control->కిటికీ->iscale, control->rect.y + 2 * control->కిటికీ->iscale,
                                   control->rect.w - 4 * control->కిటికీ->iscale, control->rect.h - 4 * control->కిటికీ->iscale);
            }
        }

    X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_పాఠ్యం].pixel);
    X11_Toolkit_Draw_పాఠ్యం_Elements(control->కిటికీ, button_control->పాఠ్యం, control->rect.x + button_control->పాఠ్యం_rect.x, control->rect.y + button_control->పాఠ్యం_rect.y);
}

స్థిర శూన్య X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    ఒకవేళ (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_దత్తాంశం);
    }
}

స్థిర శూన్య X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_Toolkit_Free_పాఠ్యం_Elements(button_control->పాఠ్యం);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_కిటికీ_X11 *కిటికీ, స్థిరరాశి SDL_సందేశం_Box_Button_దత్తాంశం *దత్తాంశం) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *పునాది_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(పరిమాణం(SDL_ToolkitButtonControlX11));
    పునాది_control = (SDL_ToolkitControlX11 *)control;
    ఒకవేళ (!control) {
        SDL_సమితి_Error("Unable to allocate button control structure");
        తిరిగి ఖాళీ;
    }
    పునాది_control->కిటికీ = కిటికీ;
    పునాది_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_సాధారణ;
    పునాది_control->func_calc_కొలత = X11Toolkit_CalculateButtonControl;
    పునాది_control->func_draw = X11Toolkit_DrawButtonControl;
    పునాది_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    పునాది_control->func_free = X11Toolkit_DestroyButtonControl;
    పునాది_control->func_on_scale_change = ఖాళీ;
    పునాది_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_సాధారణ;
    పునాది_control->selected = false;
    పునాది_control->dynamic = true;
    పునాది_control->is_default_enter = false;
    పునాది_control->is_default_esc = false;
    ఒకవేళ (దత్తాంశం->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        పునాది_control->is_default_esc = true;
    }
    ఒకవేళ (దత్తాంశం->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        పునాది_control->is_default_enter = true;
        పునాది_control->selected = true;
    }
    control->cb = ఖాళీ;
    control->దత్తాంశం = దత్తాంశం;
#నిర్వచితమైతే HAVE_FRIBIDI_H
    control->పాఠ్యం = X11_Toolkit_Make_పాఠ్యం_Elements(పునాది_control->కిటికీ, (అక్షరం *)control->దత్తాంశం->పాఠ్యం, SDL_strlen(control->దత్తాంశం->పాఠ్యం), ఖాళీ);
#లేకపోతే 
    control->పాఠ్యం = X11_Toolkit_Make_పాఠ్యం_Elements(పునాది_control->కిటికీ, (అక్షరం *)control->దత్తాంశం->పాఠ్యం, SDL_strlen(control->దత్తాంశం->పాఠ్యం));
#అయితే_ముగింపు
    X11_Toolkit_Shape_పాఠ్యం_Elements(పునాది_control->కిటికీ, control->పాఠ్యం);
    
    పునాది_control->do_కొలత = true;
    X11Toolkit_CalculateButtonControl(పునాది_control);
    పునాది_control->do_కొలత = false;

    X11_Toolkit_కూడు_Control_గమ్యం_కిటికీ(కిటికీ, పునాది_control);
    తిరిగి పునాది_control;
}

శూన్య X11_Toolkit_రిజిస్టరు_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, శూన్య *దత్తాంశం, శూన్య (*cb)(నిర్మాణం SDL_ToolkitControlX11 *, శూన్య *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_దత్తాంశం = దత్తాంశం;
    button_control->cb = cb;
}

స్థిరరాశి SDL_సందేశం_Box_Button_దత్తాంశం *X11_Toolkit_Get_Button_Control_దత్తాంశం(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    తిరిగి button_control->దత్తాంశం;
}

శూన్య X11_Toolkit_Destroy_కిటికీ(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం) {
    పూర్ణాంకం i;

    ఒకవేళ (!దత్తాంశం) {
        తిరిగి;
    }

#ఒకవేళ SDL_GRAB
    ఒకవేళ (దత్తాంశం->బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_MENU || దత్తాంశం->బహుళకం== SDL_TOOLKIT_కిటికీ_బహుళకం_X11_TOOLTIP) {
        X11_XUngrab_సూచిక(దత్తాంశం->display, Current_సమయం);
        X11_XUngrabKeyboard(దత్తాంశం->display, Current_సమయం);
    }
#అయితే_ముగింపు

    కొరకు (i = 0; i < దత్తాంశం->controls_sz; i++) {
        ఒకవేళ (దత్తాంశం->controls[i]->func_free) {
            దత్తాంశం->controls[i]->func_free(దత్తాంశం->controls[i]);
        }
    }
    SDL_free(దత్తాంశం->controls);
    SDL_free(దత్తాంశం->dyn_controls);

    ఒకవేళ (దత్తాంశం->popup_windows) {
        SDL_ListClear(&దత్తాంశం->popup_windows);
    }

    ఒకవేళ (దత్తాంశం->pixmap) {
        X11_XFreePixmap(దత్తాంశం->display, దత్తాంశం->drawable);
    }

#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
    ఒకవేళ (దత్తాంశం->pixmap && దత్తాంశం->shm) {
        X11_XShmDetach(దత్తాంశం->display, &దత్తాంశం->shm_info);
        ఒకవేళ (!దత్తాంశం->shm_pixmap) {
            XDestroyImage(దత్తాంశం->image);
        }
        shmdt(దత్తాంశం->shm_info.shmaddr);
    }
#అయితే_ముగింపు

#నిర్వచితమైతే X_HAVE_UTF8_STRING
    ఒకవేళ (దత్తాంశం->font_సమితి) {
        X11_XFree_Font_సమితి(దత్తాంశం->display, దత్తాంశం->font_సమితి);
        దత్తాంశం->font_సమితి = ఖాళీ;
    }
#అయితే_ముగింపు

    ఒకవేళ (దత్తాంశం->font_struct) {
        X11_XFreeFont(దత్తాంశం->display, దత్తాంశం->font_struct);
        దత్తాంశం->font_struct = ఖాళీ;
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XDBE
    ఒకవేళ (SDL_X11_HAVE_XDBE && దత్తాంశం->xdbe && !దత్తాంశం->pixmap) {
        X11_Xdbe_Deallocate_వెనుక_బఫరు_Name(దత్తాంశం->display, దత్తాంశం->buf);
    }
#అయితే_ముగింపు

    ఒకవేళ (దత్తాంశం->xsettings) {
        xsettings_client_destroy(దత్తాంశం->xsettings);
    }

    X11_XFreeGC(దత్తాంశం->display, దత్తాంశం->ctx);

    ఒకవేళ (దత్తాంశం->display) {
        ఒకవేళ (దత్తాంశం->కిటికీ != None) {
            X11_XWithdraw_కిటికీ(దత్తాంశం->display, దత్తాంశం->కిటికీ, దత్తాంశం->screen);
            X11_XDestroy_కిటికీ(దత్తాంశం->display, దత్తాంశం->కిటికీ);
            దత్తాంశం->కిటికీ = None;
        }

        ఒకవేళ (దత్తాంశం->display_close) {
            X11_XCloseDisplay(దత్తాంశం->display);
        }
        దత్తాంశం->display = ఖాళీ;
    }

#ఒకవేళ SDL_సమితి_LOCALE
    ఒకవేళ (దత్తాంశం->origlocale && (దత్తాంశం->బహుళకం == SDL_TOOLKIT_కిటికీ_బహుళకం_X11_DIALOG)) {
        (శూన్య)setlocale(LC_ALL, దత్తాంశం->origlocale);
        SDL_free(దత్తాంశం->origlocale);
    }
#అయితే_ముగింపు

#నిర్వచితమైతే HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(దత్తాంశం->fribidi);
#అయితే_ముగింపు

#నిర్వచితమైతే HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(దత్తాంశం->th);
#అయితే_ముగింపు

    SDL_free(దత్తాంశం);
}

స్థిర పూర్ణాంకం X11_Toolkit_లెక్క_పంక్తులు_యొక్క_పాఠ్యం(స్థిరరాశి అక్షరం *పాఠ్యం)
{
    పూర్ణాంకం ఫలితం = 0;
    అయితే (పాఠ్యం && *పాఠ్యం) {
        స్థిరరాశి అక్షరం *lf = SDL_strchr(పాఠ్యం, '\n');
        ఫలితం++; // even without an endline, this counts as a line.
        పాఠ్యం = lf ? lf + 1 : ఖాళీ;
    }
    తిరిగి ఫలితం;
}

స్థిర శూన్య X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    పూర్ణాంకం i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->కిటికీ->display, control->కిటికీ->ctx, control->కిటికీ->xcolor[SDL_MESSAGEBOX_COLOR_పాఠ్యం].pixel);
    కొరకు (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Draw_పాఠ్యం_Elements(control->కిటికీ, label_control->పంక్తులు[i].పాఠ్యం, control->rect.x + label_control->పంక్తులు[i].rect.x, control->rect.y + label_control->పంక్తులు[i].rect.y);
    }
}

స్థిర శూన్య X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    పూర్ణాంకం i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    కొరకు (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Free_పాఠ్యం_Elements(label_control->పంక్తులు[i].పాఠ్యం);
    }
    SDL_free(label_control->పంక్తులు);
    SDL_free(label_control);
}

స్థిర శూన్య X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *పునాది_control) {
    SDL_ToolkitLabelControlX11 *control;
    పూర్ణాంకం i;

    control = (SDL_ToolkitLabelControlX11 *)పునాది_control;
    
    ఒకవేళ (పునాది_control->do_కొలత) {
        పునాది_control->rect.w = 0;
        పునాది_control->rect.h = 0;
    }
    
    కొరకు (i = 0; i < control->sz; i++) {
        పూర్ణాంకం font_h;
        
        font_h = X11_Toolkit_Get_పాఠ్యం_Elements_Rect(control->పంక్తులు[i].పాఠ్యం, &control->పంక్తులు[i].rect);
        
        ఒకవేళ (పునాది_control->do_కొలత) {
            పునాది_control->rect.w = SDL_max(పునాది_control->rect.w, control->పంక్తులు[i].rect.w);
        }
        
        ఒకవేళ (i > 0) {
            control->పంక్తులు[i].rect.y = font_h + control->పంక్తులు[i - 1].rect.y;
        } లేకపోతే {
            control->పంక్తులు[i].rect.y = 0;
        }
    }

#నిర్వచితమైతే HAVE_FRIBIDI_H
    ఒకవేళ (పునాది_control->కిటికీ->fribidi) {
        FriBidiParType మొదటి_ndn_dir;
        పూర్ణాంకం చివరి_ndn;
    
        మొదటి_ndn_dir = FRIBIDI_PAR_LTR;
        కొరకు (i = 0; i < control->sz; i++) {
            ఒకవేళ (control->పంక్తులు[i].par != FRIBIDI_PAR_ON) {
                మొదటి_ndn_dir = control->పంక్తులు[i].par;
            }
        }

        చివరి_ndn = -1;
        కొరకు (i = 0; i < control->sz; i++) {
            ఎంపిక (control->పంక్తులు[i].par) {
                స్థితి FRIBIDI_PAR_LTR:
                    control->పంక్తులు[i].rect.x = 0;
                    చివరి_ndn = i;
                    ఆపు;
                స్థితి FRIBIDI_PAR_RTL:
                    control->పంక్తులు[i].rect.x = పునాది_control->rect.w - control->పంక్తులు[i].rect.w;
                    చివరి_ndn = i;
                    ఆపు;
                అప్రమేయ:
                    ఒకవేళ (చివరి_ndn != -1) {
                        ఒకవేళ (control->పంక్తులు[చివరి_ndn].par == FRIBIDI_PAR_RTL) {
                            control->పంక్తులు[i].rect.x = పునాది_control->rect.w - control->పంక్తులు[i].rect.w;
                        } లేకపోతే {
                            control->పంక్తులు[i].rect.x = 0;
                        }
                    } లేకపోతే {
                        ఒకవేళ (మొదటి_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->పంక్తులు[i].rect.x = పునాది_control->rect.w - control->పంక్తులు[i].rect.w;
                        } లేకపోతే {
                            control->పంక్తులు[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#అయితే_ముగింపు
    
    ఒకవేళ (పునాది_control->do_కొలత && control->sz) {
        పునాది_control->rect.h = control->పంక్తులు[control->sz - 1].rect.y + control->పంక్తులు[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_కిటికీ_X11 *కిటికీ, అక్షరం *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *పునాది_control;
    పూర్ణాంకం i;
    
    ఒకవేళ (!utf8) {
        తిరిగి ఖాళీ;
    }
 
    ఒకవేళ (!SDL_strcmp(utf8, "")) {
        తిరిగి ఖాళీ;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(పరిమాణం(SDL_ToolkitLabelControlX11));
    పునాది_control = (SDL_ToolkitControlX11 *)control;
    ఒకవేళ (!control) {
        SDL_సమితి_Error("Unable to allocate label control structure");
        తిరిగి ఖాళీ;
    }
    పునాది_control->కిటికీ = కిటికీ;
    పునాది_control->func_draw = X11Toolkit_DrawLabelControl;
    పునాది_control->func_on_state_change = ఖాళీ;
    పునాది_control->func_calc_కొలత = X11Toolkit_CalculateLabelControl;
    పునాది_control->func_free  = X11Toolkit_DestroyLabelControl;
    పునాది_control->func_on_scale_change = ఖాళీ;
    పునాది_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_సాధారణ;
    పునాది_control->selected = false;
    పునాది_control->dynamic = false;
    పునాది_control->rect.w = 0;
    పునాది_control->rect.h = 0;
    పునాది_control->is_default_enter = false;
    పునాది_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_లెక్క_పంక్తులు_యొక్క_పాఠ్యం(utf8);
    control->పంక్తులు = SDL_calloc(control->sz, పరిమాణం(SDL_Toolkit_Label_Control_పంక్తి_X11));
    కొరకు (i = 0; i < control->sz; i++) {
        స్థిరరాశి అక్షరం *lf = SDL_strchr(utf8, '\n');
        స్థిరరాశి పూర్ణాంకం నిడివి = lf ? (lf - utf8) : SDL_strlen(utf8);
        పూర్ణాంకం sz;
        
        sz = నిడివి;
        ఒకవేళ (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#నిర్వచితమైతే HAVE_FRIBIDI_H
        control->పంక్తులు[i].పాఠ్యం = X11_Toolkit_Make_పాఠ్యం_Elements(పునాది_control->కిటికీ, (అక్షరం *)utf8, sz, &control->పంక్తులు[i].par);
#లేకపోతే 
        control->పంక్తులు[i].పాఠ్యం = X11_Toolkit_Make_పాఠ్యం_Elements(పునాది_control->కిటికీ, (అక్షరం *)utf8, sz);
#అయితే_ముగింపు
        X11_Toolkit_Shape_పాఠ్యం_Elements(పునాది_control->కిటికీ, control->పంక్తులు[i].పాఠ్యం);

        utf8 += నిడివి + 1;
        ఒకవేళ (!lf) {
            ఆపు;
        }
    }

    పునాది_control->do_కొలత = true;
    X11Toolkit_CalculateLabelControl(పునాది_control);
    పునాది_control->do_కొలత = false;
    X11_Toolkit_కూడు_Control_గమ్యం_కిటికీ(కిటికీ, పునాది_control);

    తిరిగి పునాది_control;
}

పూర్ణాంకం X11_Toolkit_Get_Label_Control_మొదటి_పంక్తి_ఎత్తు(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    తిరిగి label_control->పంక్తులు[0].rect.h;
}

శూన్య X11_Toolkit_Signal_కిటికీ_Close(SDL_Toolkit_కిటికీ_X11 *దత్తాంశం) {
    దత్తాంశం->close = true;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
