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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "../../SDL_list.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
#ಅನ್ತರ್ಭಾವ "../../core/linux/SDL_system_theme.h"
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_fribidi.h"
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "SDL_x11dyn.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11toolkit.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11settings.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11modes.h"
#ಅನ್ತರ್ಭಾವ "xsettings-client.h"
#ಅನ್ತರ್ಭಾವ <X11/keysym.h>
#ಅನ್ತರ್ಭಾವ <locale.h>

#ವ್ಯಾಖ್ಯಾನಿಸು SDL_ಗಣ_LOCALE 1
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_GRAB 1

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ SDL_Toolkit_ಪಠ್ಯ_Type_X11
{
    SDL_TOOLKIT_ಪಠ್ಯ_TYPE_X11_GENERIC,
    SDL_TOOLKIT_ಪಠ್ಯ_TYPE_X11_THAI
} SDL_Toolkit_ಪಠ್ಯ_Type_X11;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBTHAI_H
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_ToolkitThaiOverlayX11
{
    bool ತುದಿ;
    ಅಕ್ಷರ *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_Toolkit_ಪಠ್ಯ_Element_X11
{
    SDL_Toolkit_ಪಠ್ಯ_Type_X11 type;
    ಅಕ್ಷರ *str;
    size_t sz;
    SDL_Rect rect;
    ಪೂರ್ಣಾಂಕ font_h;
    ಶೂನ್ಯ (*str_free)(ಶೂನ್ಯ *);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBTHAI_H
    SDL_List_ಗಂಟು *thai_overlays;
#ಆದರೆ_ಅಂತ್ಯ
} SDL_Toolkit_ಪಠ್ಯ_Element_X11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 ಪೋಷಕ;

    /* Icon type */
    SDL_ಸಂದೇಶ_Box_Flags flags;
    ಅಕ್ಷರ icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    ಪೂರ್ಣಾಂಕ icon_char_x;
    ಪೂರ್ಣಾಂಕ icon_char_y;
    ಪೂರ್ಣಾಂಕ icon_char_a;
    ಪೂರ್ಣಾಂಕ icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 ಪೋಷಕ;

    /*ದತ್ತಾಂಶ*/
    ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;

    /*ಪಠ್ಯ*/
    SDL_List_ಗಂಟು *ಪಠ್ಯ;
    SDL_Rect ಪಠ್ಯ_rect;
    
    /* Callback */
    ಶೂನ್ಯ *cb_ದತ್ತಾಂಶ;
    ಶೂನ್ಯ (*cb)(ರಚನೆ SDL_ToolkitControlX11 *, ಶೂನ್ಯ *);
} SDL_ToolkitButtonControlX11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_Toolkit_Label_Control_ಸಾಲು_X11
{
    SDL_List_ಗಂಟು *ಪಠ್ಯ;
    SDL_Rect rect;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
    FriBidiParType par;
#ಆದರೆ_ಅಂತ್ಯ
} SDL_Toolkit_Label_Control_ಸಾಲು_X11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_ToolkitLabelControlX11
{
    SDL_ToolkitControlX11 ಪೋಷಕ;

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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 ಪೋಷಕ;

    SDL_List_ಗಂಟು *menu_ವಸ್ತುಗಳು;
} SDL_ToolkitMenuBarControlX11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 ಪೋಷಕ;

    SDL_List_ಗಂಟು *menu_ವಸ್ತುಗಳು;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#ವ್ಯಾಖ್ಯಾನಿಸು G_ICONFONT_ಗಾತ್ರ 22

/* General UI font */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    ಖಾಲಿ
};
#ವ್ಯಾಖ್ಯಾನಿಸು G_TOOLKITFONT_ಗಾತ್ರ 140

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color g_default_colors[SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color g_default_colors_dark[SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ಆದರೆ 0
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color g_default_colors_dark_ಮೇಲಿನ_contrast[SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color g_default_colors_light_ಮೇಲಿನ_contrast[SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ g_shm_error;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ (*g_old_error_handler)(Display *, XErrorEvent *) = ಖಾಲಿ;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ X11_Toolkit_Shared_ಸ್ಮರಣೆ_Error_Handler(Display *d, XErrorEvent *e)
{
    ಆದರೆ (e->error_ಸಂಕೇತ == BadAccess || e->error_ಸಂಕೇತ == BadRequest) {
        g_shm_error = True;
        ಹಿಂತಿರುಗಿ 0;
    }
    ಹಿಂತಿರುಗಿ g_old_error_handler(d, e);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Toolkit_Init_ಕಿಟಕಿ_Pixmap(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ) {
    ಆದರೆ (ದತ್ತಾಂಶ->pixmap) {
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
        ಆದರೆ (!ದತ್ತಾಂಶ->shm_pixmap) {
            ದತ್ತಾಂಶ->drawable = X11_XCreatePixmap(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, ದತ್ತಾಂಶ->pixmap_ಅಗಲ, ದತ್ತಾಂಶ->pixmap_ಎತ್ತರ, ದತ್ತಾಂಶ->ಆಳ_2);
        }
#ಇಲ್ಲದಿದ್ದರೆ
        ದತ್ತಾಂಶ->drawable = X11_XCreatePixmap(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, ದತ್ತಾಂಶ->pixmap_ಅಗಲ, ದತ್ತಾಂಶ->pixmap_ಎತ್ತರ, ದತ್ತಾಂಶ->ಆಳ_2);
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
        ಆದರೆ (ದತ್ತಾಂಶ->shm) {
            ದತ್ತಾಂಶ->image = X11_XShmCreateImage(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->visual, ದತ್ತಾಂಶ->ಆಳ_2, ZPixmap, ಖಾಲಿ, &ದತ್ತಾಂಶ->shm_info, ದತ್ತಾಂಶ->pixmap_ಅಗಲ, ದತ್ತಾಂಶ->pixmap_ಎತ್ತರ);
            ಆದರೆ (ದತ್ತಾಂಶ->image) {
                ದತ್ತಾಂಶ->shm_ಬೈಟುಗಳು_ಪ್ರತಿ_ಸಾಲು = ದತ್ತಾಂಶ->image->ಬೈಟುಗಳು_ಪ್ರತಿ_ಸಾಲು;

                ದತ್ತಾಂಶ->shm_info.shmid = shmget(IPC_ಖಾಸಗಿ, ದತ್ತಾಂಶ->image->ಬೈಟುಗಳು_ಪ್ರತಿ_ಸಾಲು * ದತ್ತಾಂಶ->image->ಎತ್ತರ, IPC_CREAT | 0777);
                ಆದರೆ (ದತ್ತಾಂಶ->shm_info.shmid < 0) {
                    XDestroyImage(ದತ್ತಾಂಶ->image);
                    ದತ್ತಾಂಶ->image = ಖಾಲಿ;
                    ದತ್ತಾಂಶ->shm = false;
                    ಹಿಂತಿರುಗಿ;
                }

                ದತ್ತಾಂಶ->shm_info.readOnly = False;
                ದತ್ತಾಂಶ->shm_info.shmaddr = ದತ್ತಾಂಶ->image->ದತ್ತಾಂಶ = (ಅಕ್ಷರ *)shmat(ದತ್ತಾಂಶ->shm_info.shmid, ಖಾಲಿ, 0);
                ಆದರೆ (((ಚಿಹ್ನೆಯುಳ್ಳ ಅಕ್ಷರ *)ದತ್ತಾಂಶ->shm_info.shmaddr) == (ಚಿಹ್ನೆಯುಳ್ಳ ಅಕ್ಷರ *)-1) {
                    XDestroyImage(ದತ್ತಾಂಶ->image);
                    ದತ್ತಾಂಶ->shm = false;
                    ದತ್ತಾಂಶ->image = ಖಾಲಿ;
                    ಹಿಂತಿರುಗಿ;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11_Toolkit_Shared_ಸ್ಮರಣೆ_Error_Handler);
                X11_XShmAttach(ದತ್ತಾಂಶ->display, &ದತ್ತಾಂಶ->shm_info);
                X11_XSync(ದತ್ತಾಂಶ->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                ಆದರೆ (g_shm_error) {
                    XDestroyImage(ದತ್ತಾಂಶ->image);
                    shmdt(ದತ್ತಾಂಶ->shm_info.shmaddr);
                    shmctl(ದತ್ತಾಂಶ->shm_info.shmid, IPC_RMID, ಖಾಲಿ);
                    ದತ್ತಾಂಶ->image = ಖಾಲಿ;
                    ದತ್ತಾಂಶ->shm = false;
                    ಹಿಂತಿರುಗಿ;
                }

                ಆದರೆ (ದತ್ತಾಂಶ->shm_pixmap) {
                    ದತ್ತಾಂಶ->drawable = X11_XShmCreatePixmap(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, ದತ್ತಾಂಶ->shm_info.shmaddr, &ದತ್ತಾಂಶ->shm_info, ದತ್ತಾಂಶ->pixmap_ಅಗಲ, ದತ್ತಾಂಶ->pixmap_ಎತ್ತರ, ದತ್ತಾಂಶ->ಆಳ_2);
                    ಆದರೆ (ದತ್ತಾಂಶ->drawable == None) {
                        ದತ್ತಾಂಶ->shm_pixmap = False;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        XDestroyImage(ದತ್ತಾಂಶ->image);
                        ದತ್ತಾಂಶ->image = ಖಾಲಿ;
                    }
                }

                shmctl(ದತ್ತಾಂಶ->shm_info.shmid, IPC_RMID, ಖಾಲಿ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ದತ್ತಾಂಶ->shm = false;
            }
        }
#ಆದರೆ_ಅಂತ್ಯ
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Toolkit_Init_ಕಿಟಕಿ_Fonts(SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ)
{    
    ಕಿಟಕಿ->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    ಕಿಟಕಿ->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    ಕಿಟಕಿ->utf8 = true;
    ಕಿಟಕಿ->font_ಗಣ = ಖಾಲಿ;
    ಆದರೆ (SDL_X11_HAVE_UTF8) {
        ಅಕ್ಷರ **missing = ಖಾಲಿ;
        ಪೂರ್ಣಾಂಕ ಅಂಕೆ_missing = 0;
        ಪೂರ್ಣಾಂಕ i_font;
        ಕಿಟಕಿ->font_struct = ಖಾಲಿ;
        ಗಾಗಿ (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            ಅಕ್ಷರ *font;

            ಆದರೆ (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_ತುಂಬು_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_ಗಾತ್ರ * ಕಿಟಕಿ->iscale);
                ಕಿಟಕಿ->font_ಗಣ = X11_XCreate_Font_ಗಣ(ಕಿಟಕಿ->display, font, &missing, &ಅಂಕೆ_missing, ಖಾಲಿ);
                SDL_free(font);

                ಆದರೆ (!ಕಿಟಕಿ->font_ಗಣ) {
                    ಆದರೆ (ಕಿಟಕಿ->scale != 0 && ಕಿಟಕಿ->iscale > 0) {
                        ಕಿಟಕಿ->iscale = (ಪೂರ್ಣಾಂಕ)SDL_ceilf(ಕಿಟಕಿ->scale);
                        ಕಿಟಕಿ->scale = 0;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        ಕಿಟಕಿ->iscale--;
                    }
                    ಹೋಗು try_ತುಂಬು_font;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಕಿಟಕಿ->font_ಗಣ = X11_XCreate_Font_ಗಣ(ಕಿಟಕಿ->display, g_ToolkitFont[i_font], &missing, &ಅಂಕೆ_missing, ಖಾಲಿ);
            }

            ಆದರೆ (missing) {
                X11_XFreeStringList(missing);
            }

            ಆದರೆ (ಕಿಟಕಿ->font_ಗಣ) {
                ನಿಲ್ಲಿಸು;
            }
        }

        ಆದರೆ (!ಕಿಟಕಿ->font_ಗಣ) {
            ಹೋಗು ತುಂಬು_font_traditional;
        } ಇಲ್ಲದಿದ್ದರೆ {
            XFontStruct **font_structs;
            ಅಕ್ಷರ **font_ಹೆಸರುಗಳು;
            ಪೂರ್ಣಾಂಕ font_sz;
            ಪೂರ್ಣಾಂಕ i;
            
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
            ಕಿಟಕಿ->do_shaping = !X11_XContextDependentDrawing(ಕಿಟಕಿ->font_ಗಣ);
#ಆದರೆ_ಅಂತ್ಯ
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFonts_ದ_Font_ಗಣ(ಕಿಟಕಿ->font_ಗಣ, &font_structs, &font_ಹೆಸರುಗಳು);
            ಗಾಗಿ (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                ಆದರೆ (SDL_strstr(font_ಹೆಸರುಗಳು[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strstr(font_ಹೆಸರುಗಳು[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strstr(font_ಹೆಸರುಗಳು[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strstr(font_ಹೆಸರುಗಳು[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_strstr(font_ಹೆಸರುಗಳು[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                ಆದರೆ (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(ಕಿಟಕಿ->display, font_ಹೆಸರುಗಳು[i]);
                    ಆದರೆ (font_struct) {
                        ಆದರೆ (font_struct->ಪ್ರತಿ_char) {
                            ಪೂರ್ಣಾಂಕ glyphs_sz;
                            ಪೂರ್ಣಾಂಕ j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            ಗಾಗಿ (j = 0; j < glyphs_sz; j++) {
                                ಆದರೆ (font_struct->ಪ್ರತಿ_char[j].lbearing < 0) {
                                    ಕಿಟಕಿ->thai_font = SDL_TOOLKIT_THAI_FONT_X11_ಸ್ಥಾನಾಂತರ;
                                }
                            }
                        }
                        X11_XFreeFont(ಕಿಟಕಿ->display, font_struct);
                    }
                }
                
                ಕಿಟಕಿ->thai_encoding = thai_encoding;
            } 
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        ಅಕ್ಷರ *font;

        ತುಂಬು_font_traditional:
        ಕಿಟಕಿ->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_ಗಾತ್ರ * ಕಿಟಕಿ->iscale);
        ಕಿಟಕಿ->font_struct = X11_XLoadQueryFont(ಕಿಟಕಿ->display, font);
        SDL_free(font);
        ಆದರೆ (!ಕಿಟಕಿ->font_struct) {
            ಆದರೆ (ಕಿಟಕಿ->iscale > 0) {
                ಆದರೆ (ಕಿಟಕಿ->scale != 0) {
                    ಕಿಟಕಿ->iscale = (ಪೂರ್ಣಾಂಕ)SDL_ceilf(ಕಿಟಕಿ->scale);
                    ಕಿಟಕಿ->scale = 0;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಕಿಟಕಿ->iscale--;
                }
                ಹೋಗು ತುಂಬು_font_traditional;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಕಿಟಕಿ->font_struct = X11_XLoadQueryFont(ಕಿಟಕಿ->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_SettingsNotify(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, XSettingsAction action, XSettingsSetting *setting, ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ;
    ಪೂರ್ಣಾಂಕ i;

    ಕಿಟಕಿ = ದತ್ತಾಂಶ;

    ಆದರೆ (ಕಿಟಕಿ->xsettings_ಮೊದಲ_ಸಮಯ) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (SDL_strcmp(name, SDL_XSETTINGS_GDK_ಕಿಟಕಿ_SCALING_ಗುಣಕ) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_ಸಿದ್ಧತೆ = false;
        bool pixmap_already_ಸಿದ್ಧತೆ = false;

        ಆದರೆ (ಕಿಟಕಿ->pixmap) {
            pixmap_already_ಸಿದ್ಧತೆ = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dbe_already_ಸಿದ್ಧತೆ = true;
        }

        /* set scale vars */
        ಕಿಟಕಿ->scale = X11_GetGlobalContentScale(ಕಿಟಕಿ->display, ಕಿಟಕಿ->xsettings);
        ಕಿಟಕಿ->iscale = (ಪೂರ್ಣಾಂಕ)SDL_ceilf(ಕಿಟಕಿ->scale);
        ಆದರೆ (ಕಿಟಕಿ->scale < 1) {
            ಕಿಟಕಿ->scale = 1;
        }
        ಆದರೆ (SDL_roundf(ಕಿಟಕಿ->scale) == ಕಿಟಕಿ->scale) {
            ಕಿಟಕಿ->scale = 0;
        }

        /* setup fonts */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
        ಆದರೆ (ಕಿಟಕಿ->font_ಗಣ) {
            X11_XFree_Font_ಗಣ(ಕಿಟಕಿ->display, ಕಿಟಕಿ->font_ಗಣ);
        }
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (ಕಿಟಕಿ->font_struct) {
            X11_XFreeFont(ಕಿಟಕಿ->display, ಕಿಟಕಿ->font_struct);
        }

        X11_Toolkit_Init_ಕಿಟಕಿ_Fonts(ಕಿಟಕಿ);

        /* set up window */
        ಆದರೆ (ಕಿಟಕಿ->scale != 0) {
            ಕಿಟಕಿ->ಕಿಟಕಿ_ಅಗಲ = SDL_lroundf((ಕಿಟಕಿ->ಕಿಟಕಿ_ಅಗಲ/ಕಿಟಕಿ->iscale) * ಕಿಟಕಿ->scale);
            ಕಿಟಕಿ->ಕಿಟಕಿ_ಎತ್ತರ = SDL_lroundf((ಕಿಟಕಿ->ಕಿಟಕಿ_ಎತ್ತರ/ಕಿಟಕಿ->iscale) * ಕಿಟಕಿ->scale);
            ಕಿಟಕಿ->pixmap_ಅಗಲ = ಕಿಟಕಿ->ಕಿಟಕಿ_ಅಗಲ;
            ಕಿಟಕಿ->pixmap_ಎತ್ತರ = ಕಿಟಕಿ->ಕಿಟಕಿ_ಎತ್ತರ;
            ಕಿಟಕಿ->pixmap = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->pixmap = false;
        }

        ಆದರೆ (ಕಿಟಕಿ->pixmap) {
            ಆದರೆ (!pixmap_already_ಸಿದ್ಧತೆ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XDBE
                ಆದರೆ (SDL_X11_HAVE_XDBE && ಕಿಟಕಿ->xdbe) {
                    X11_Xdbe_Deallocate_ಹಿಂಭಾಗ_ಬಫರ್_Name(ಕಿಟಕಿ->display, ಕಿಟಕಿ->buf);
                }
#ಆದರೆ_ಅಂತ್ಯ
            }
            X11_XFreePixmap(ಕಿಟಕಿ->display, ಕಿಟಕಿ->drawable);
            X11_Toolkit_Init_ಕಿಟಕಿ_Pixmap(ಕಿಟಕಿ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (!dbe_already_ಸಿದ್ಧತೆ) {
                X11_XFreePixmap(ಕಿಟಕಿ->display, ಕಿಟಕಿ->drawable);
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
                ಆದರೆ (ಕಿಟಕಿ->image) {
                    XDestroyImage(ಕಿಟಕಿ->image);
                    ಕಿಟಕಿ->image = ಖಾಲಿ;
                }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XDBE
                ಆದರೆ (SDL_X11_HAVE_XDBE && ಕಿಟಕಿ->xdbe) {
                    ಕಿಟಕಿ->buf = X11_Xdbe_Allocate_ಹಿಂಭಾಗ_ಬಫರ್_Name(ಕಿಟಕಿ->display, ಕಿಟಕಿ->ಕಿಟಕಿ, XdbeUndefined);
                    ಕಿಟಕಿ->drawable = ಕಿಟಕಿ->buf;
                }
#ಆದರೆ_ಅಂತ್ಯ
            }
        }

        /* notify controls */
        ಗಾಗಿ (i = 0; i < ಕಿಟಕಿ->controls_sz; i++) {
            ಕಿಟಕಿ->controls[i]->do_ಗಾತ್ರ = true;

            ಆದರೆ (ಕಿಟಕಿ->controls[i]->func_on_scale_change) {
                ಕಿಟಕಿ->controls[i]->func_on_scale_change(ಕಿಟಕಿ->controls[i]);
            }

            ಆದರೆ (ಕಿಟಕಿ->controls[i]->func_calc_ಗಾತ್ರ) {
                ಕಿಟಕಿ->controls[i]->func_calc_ಗಾತ್ರ(ಕಿಟಕಿ->controls[i]);
            }

            ಕಿಟಕಿ->controls[i]->do_ಗಾತ್ರ = false;
        }

        /* notify cb */
        ಆದರೆ (ಕಿಟಕಿ->cb_on_scale_change) {
            ಕಿಟಕಿ->cb_on_scale_change(ಕಿಟಕಿ, ಕಿಟಕಿ->cb_ದತ್ತಾಂಶ);
        }

        /* update ev scales */
        ಆದರೆ (!ಕಿಟಕಿ->pixmap) {
            ಕಿಟಕಿ->ev_scale = ಕಿಟಕಿ->ev_iscale = 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->ev_scale = ಕಿಟಕಿ->scale;
            ಕಿಟಕಿ->ev_iscale = ಕಿಟಕಿ->iscale;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Toolkit_Get_ಪಠ್ಯ_ಅಗಲ_ಎತ್ತರ_For_Font(XFontStruct *font, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಪೂರ್ಣಾಂಕ nbytes, ಪೂರ್ಣಾಂಕ *pwidth, ಪೂರ್ಣಾಂಕ *pheight, ಪೂರ್ಣಾಂಕ *ascent, ಪೂರ್ಣಾಂಕ *font_ಎತ್ತರ)
{
    XCharStruct ಪಠ್ಯ_structure;
    ಪೂರ್ಣಾಂಕ font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &ಪಠ್ಯ_structure);
    *pwidth = ಪಠ್ಯ_structure.ಅಗಲ;
    *pheight = ಪಠ್ಯ_structure.ascent + ಪಠ್ಯ_structure.descent;
    *ascent = ಪಠ್ಯ_structure.ascent;
    ಆದರೆ (font_ಎತ್ತರ) {
       *font_ಎತ್ತರ = font_ascent + font_descent;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Toolkit_Get_ಪಠ್ಯ_ಅಗಲ_ಎತ್ತರ(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಪೂರ್ಣಾಂಕ nbytes, ಪೂರ್ಣಾಂಕ *pwidth, ಪೂರ್ಣಾಂಕ *pheight, ಪೂರ್ಣಾಂಕ *ascent, ಪೂರ್ಣಾಂಕ *descent, ಪೂರ್ಣಾಂಕ *font_ಎತ್ತರ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    ಆದರೆ (ದತ್ತಾಂಶ->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8_ಪಠ್ಯ_Extents(ದತ್ತಾಂಶ->font_ಗಣ, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.ಅಗಲ;
        *pheight = overall_logical.ಎತ್ತರ;
        *ascent = -overall_logical.y;
        *descent = overall_logical.ಎತ್ತರ - *ascent;

        ಆದರೆ (font_ಎತ್ತರ) {
            XFont_ಗಣ_Extents *extents;

            extents = X11_XExtents_ದ_Font_ಗಣ(ದತ್ತಾಂಶ->font_ಗಣ);
            *font_ಎತ್ತರ = extents->max_logical_extent.ಎತ್ತರ;
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        XCharStruct ಪಠ್ಯ_structure;
        ಪೂರ್ಣಾಂಕ font_direction, font_ascent, font_descent;
        X11_XTextExtents(ದತ್ತಾಂಶ->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &ಪಠ್ಯ_structure);
        *pwidth = ಪಠ್ಯ_structure.ಅಗಲ;
        *pheight = ಪಠ್ಯ_structure.ascent + ಪಠ್ಯ_structure.descent;
        *ascent = ಪಠ್ಯ_structure.ascent;
        *descent = ಪಠ್ಯ_structure.descent;

        ಆದರೆ (font_ಎತ್ತರ) {
            *font_ಎತ್ತರ = font_ascent + font_descent;
        }
    }
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
SDL_List_ಗಂಟು *X11_Toolkit_Make_ಪಠ್ಯ_Elements(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ, ಅಕ್ಷರ *txt, size_t sz, FriBidiParType *par)
#ಇಲ್ಲದಿದ್ದರೆ
SDL_List_ಗಂಟು *X11_Toolkit_Make_ಪಠ್ಯ_Elements(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ, ಅಕ್ಷರ *txt, size_t sz)
#ಆದರೆ_ಅಂತ್ಯ
{
    SDL_List_ಗಂಟು *list;
    ಅಕ್ಷರ *str;
    ಅಕ್ಷರ *ಬಫರ್_2;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = ಖಾಲಿ;
    thai = 0;
    str = txt;
    ಬಫರ್_2 = SDL_malloc(1);
    ಬಫರ್_2[0] = 0;
    
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
    ಆದರೆ (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    ಆದರೆ (ದತ್ತಾಂಶ->fribidi) {
        ಅಕ್ಷರ *fstr;
                
        fstr = SDL_FriBidi_Process(ದತ್ತಾಂಶ->fribidi, str, sz, ದತ್ತಾಂಶ->do_shaping, par);
        ಆದರೆ (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#ಆದರೆ_ಅಂತ್ಯ        

    ಆಗ (1) {
        ಅಕ್ಷರ *new;
        ಅಕ್ಷರ utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_ಹೆಜ್ಜೆ_UTF8((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        ಆದರೆ (cp == 0 || cond == (thai ? false : true)) {
            SDL_Toolkit_ಪಠ್ಯ_Element_X11 *element;
            
            element = SDL_malloc(ಗಾತ್ರ(SDL_Toolkit_ಪಠ್ಯ_Element_X11));
            ಆದರೆ (thai) {
                element->type = SDL_TOOLKIT_ಪಠ್ಯ_TYPE_X11_THAI;
            } ಇಲ್ಲದಿದ್ದರೆ {
                element->type = SDL_TOOLKIT_ಪಠ್ಯ_TYPE_X11_GENERIC;
            }
            element->str = SDL_strdup(ಬಫರ್_2);
            element->sz = SDL_strlen(ಬಫರ್_2);
            element->str_free = SDL_free;
            
            SDL_List_ಕೂಡಿಸು(&list, element);
            
            SDL_free(ಬಫರ್_2);
            ಬಫರ್_2 = SDL_malloc(1);
            ಬಫರ್_2[0] = 0;
            thai = thai ? false : true;
        }

        ಆದರೆ (!cp) {
            ನಿಲ್ಲಿಸು;
        }
        
        SDL_UCS4_ಗಮ್ಯ_UTF8(cp, utf8);
        csz = SDL_strlen(ಬಫರ್_2) + SDL_strlen(utf8) + 1;
        new = SDL_malloc(csz);
        SDL_strlcpy(new, ಬಫರ್_2, csz);
        SDL_strlcat(new, utf8, csz);
        SDL_free(ಬಫರ್_2);
        ಬಫರ್_2 = new;
    }

    SDL_free(ಬಫರ್_2);
    ಆದರೆ (free_txt) {
        SDL_free(txt);
    }
    ಹಿಂತಿರುಗಿ list;
}

ಶೂನ್ಯ X11_Toolkit_Shape_ಪಠ್ಯ_Elements(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ, SDL_List_ಗಂಟು *list)
{
    SDL_List_ಗಂಟು *cursor;
    SDL_Toolkit_ಪಠ್ಯ_Element_X11 *prev;
    ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ;
    
    /* Shape and calculate bounding box */
    cursor = list;
    ಆಗ (cursor) {
        SDL_Toolkit_ಪಠ್ಯ_Element_X11 *element;
        
        element = cursor->ನಮೂದು;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBTHAI_H
        element->thai_overlays = ಖಾಲಿ;
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (element->type == SDL_TOOLKIT_ಪಠ್ಯ_TYPE_X11_THAI) {
            ಆದರೆ (ದತ್ತಾಂಶ->thai_font == SDL_TOOLKIT_THAI_FONT_X11_ಸ್ಥಾನಾಂತರ) {
                X11_Toolkit_Get_ಪಠ್ಯ_ಅಗಲ_ಎತ್ತರ(ದತ್ತಾಂಶ, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &ತಾತ್ಕಾಲಿಕ, ಖಾಲಿ);
            } ಇಲ್ಲದಿದ್ದರೆ {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBTHAI_H
                ಆದರೆ (ದತ್ತಾಂಶ->th) {
                    ರಚನೆ thcell_t *cells;
                    ಅಕ್ಷರ *tis_str;
                    ಅಕ್ಷರ *ತಳ_tis_str;
                    size_t cells_sz;
                    size_t ತಳ_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, ಗಾತ್ರ(ರಚನೆ thcell_t));
                    ದತ್ತಾಂಶ->th->make_cells((ಸ್ಥಿರಾಂಕ thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    ತಳ_tis_str_sz = cells_sz;
                    ತಳ_tis_str = SDL_malloc(ತಳ_tis_str_sz + 1);
                    ಗಾಗಿ (ತಾತ್ಕಾಲಿಕ = 0; ತಾತ್ಕಾಲಿಕ < cells_sz; ತಾತ್ಕಾಲಿಕ++) {
                        ತಳ_tis_str[ತಾತ್ಕಾಲಿಕ] = cells[ತಾತ್ಕಾಲಿಕ].ತಳ;
                        
                        ಆದರೆ (cells[ತಾತ್ಕಾಲಿಕ].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            ಅಕ್ಷರ *pre;
                            ಪೂರ್ಣಾಂಕ temp2;
                            
                            overlay = SDL_malloc(ಗಾತ್ರ(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", ತಳ_tis_str, ತಾತ್ಕಾಲಿಕ);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)&cells[ತಾತ್ಕಾಲಿಕ].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->ತುದಿ = false;
                            X11_Toolkit_Get_ಪಠ್ಯ_ಅಗಲ_ಎತ್ತರ(ದತ್ತಾಂಶ, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ಖಾಲಿ);
                            X11_Toolkit_Get_ಪಠ್ಯ_ಅಗಲ_ಎತ್ತರ(ದತ್ತಾಂಶ, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ಖಾಲಿ);
                            SDL_List_ಕೂಡಿಸು(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        ಆದರೆ (cells[ತಾತ್ಕಾಲಿಕ].ತುದಿ) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            ಅಕ್ಷರ *pre;
                            ಪೂರ್ಣಾಂಕ temp2;
                            
                            overlay = SDL_malloc(ಗಾತ್ರ(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", ತಳ_tis_str, ತಾತ್ಕಾಲಿಕ);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)&cells[ತಾತ್ಕಾಲಿಕ].ತುದಿ, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->ತುದಿ = true;
                            X11_Toolkit_Get_ಪಠ್ಯ_ಅಗಲ_ಎತ್ತರ(ದತ್ತಾಂಶ, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ಖಾಲಿ);
                            X11_Toolkit_Get_ಪಠ್ಯ_ಅಗಲ_ಎತ್ತರ(ದತ್ತಾಂಶ, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ಖಾಲಿ);
                            SDL_List_ಕೂಡಿಸು(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    ತಳ_tis_str[ತಳ_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", ತಳ_tis_str, ತಳ_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11_Toolkit_Get_ಪಠ್ಯ_ಅಗಲ_ಎತ್ತರ(ದತ್ತಾಂಶ, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &ತಾತ್ಕಾಲಿಕ, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(ತಳ_tis_str);
                }
#ಇಲ್ಲದಿದ್ದರೆ
                X11_Toolkit_Get_ಪಠ್ಯ_ಅಗಲ_ಎತ್ತರ(ದತ್ತಾಂಶ, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &ತಾತ್ಕಾಲಿಕ, &element->font_h);
#ಆದರೆ_ಅಂತ್ಯ            
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            X11_Toolkit_Get_ಪಠ್ಯ_ಅಗಲ_ಎತ್ತರ(ದತ್ತಾಂಶ, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &ತಾತ್ಕಾಲಿಕ, &element->font_h);
        }
        
        cursor = cursor->ಮುಂದಿನ;
    }
    
    /* Add offsets */
    prev = ಖಾಲಿ;
    cursor = list;
    ಆಗ (cursor) {
        SDL_Toolkit_ಪಠ್ಯ_Element_X11 *element;
        
        element = cursor->ನಮೂದು;        
        ಆದರೆ (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } ಇಲ್ಲದಿದ್ದರೆ {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->ಮುಂದಿನ;
    }
}


ಶೂನ್ಯ X11_Toolkit_Draw_ಪಠ್ಯ_Elements(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ, SDL_List_ಗಂಟು *list, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y)
{
    SDL_List_ಗಂಟು *cursor;
    
    cursor = list;
    
    ಆಗ (cursor) {
        SDL_Toolkit_ಪಠ್ಯ_Element_X11 *element;
        
        element = cursor->ನಮೂದು;
        ಆದರೆ (element->type == SDL_TOOLKIT_ಪಠ್ಯ_TYPE_X11_THAI) {
            ಆದರೆ (ದತ್ತಾಂಶ->thai_font == SDL_TOOLKIT_THAI_FONT_X11_ಸ್ಥಾನಾಂತರ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
                ಆದರೆ (ದತ್ತಾಂಶ->utf8) {
                    X11_Xutf8DrawString(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->font_ಗಣ, ದತ್ತಾಂಶ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
                {
                    X11_XDrawString(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } ಇಲ್ಲದಿದ್ದರೆ {    
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBTHAI_H
                SDL_List_ಗಂಟು *overlay_cursor;
                    
                /* Draw the base string */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
                ಆದರೆ (ದತ್ತಾಂಶ->utf8) {
                    X11_Xutf8DrawString(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->font_ಗಣ, ದತ್ತಾಂಶ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
                {
                    X11_XDrawString(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                ಆಗ (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->ನಮೂದು;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
                    ಆದರೆ (ದತ್ತಾಂಶ->utf8) {
                        X11_Xutf8DrawString(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->font_ಗಣ, ದತ್ತಾಂಶ->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
                    {
                        X11_XDrawString(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->ಮುಂದಿನ;
                }
#ಆದರೆ_ಅಂತ್ಯ                
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
            ಆದರೆ (ದತ್ತಾಂಶ->utf8) {
                X11_Xutf8DrawString(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->font_ಗಣ, ದತ್ತಾಂಶ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
            {
                X11_XDrawString(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->ಮುಂದಿನ;
    }
}

ಪೂರ್ಣಾಂಕ X11_Toolkit_Get_ಪಠ್ಯ_Elements_Rect(SDL_List_ಗಂಟು *list, SDL_Rect *ಹೊರಹೋಗು)
{
    SDL_List_ಗಂಟು *cursor;
    ಪೂರ್ಣಾಂಕ ret;
    
    ret = 0;
    ಹೊರಹೋಗು->x = ಹೊರಹೋಗು->y = 0;
    ಹೊರಹೋಗು->w = ಹೊರಹೋಗು->h = 0;
    cursor = list;
    ಆಗ (cursor) {
        SDL_Toolkit_ಪಠ್ಯ_Element_X11 *element;
        
        element = cursor->ನಮೂದು;
        
        ಹೊರಹೋಗು->w += element->rect.w;
        ಹೊರಹೋಗು->h = SDL_max(ಹೊರಹೋಗು->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->ಮುಂದಿನ;
    }
    
    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ X11_Toolkit_Free_ಪಠ್ಯ_Elements_List_Contents(SDL_List_ಗಂಟು *list)
{
    SDL_List_ಗಂಟು *cursor;
    
    cursor = list;
    ಆಗ (cursor) {
        SDL_Toolkit_ಪಠ್ಯ_Element_X11 *element;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBTHAI_H
        SDL_List_ಗಂಟು *overlay_cursor;
#ಆದರೆ_ಅಂತ್ಯ

        element = cursor->ನಮೂದು;
        
        ಆದರೆ (element->str_free) {
            element->str_free(element->str);
        }
        
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        ಆಗ (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->ನಮೂದು;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->ಮುಂದಿನ;
        }
        SDL_ListClear(&element->thai_overlays);
#ಆದರೆ_ಅಂತ್ಯ
        
        SDL_free(element);
        
        cursor = cursor->ಮುಂದಿನ;
    }
}

#ವ್ಯಾಖ್ಯಾನಿಸು X11_Toolkit_Free_ಪಠ್ಯ_Elements(x) X11_Toolkit_Free_ಪಠ್ಯ_Elements_List_Contents(x); SDL_ListClear(&x)
 
ಸ್ಥಿರ bool X11Toolkit_ShouldFlipUI(ಶೂನ್ಯ) 
{
    SDL_Locale **current_locales;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SDL_Locale rtl_locales[] = {
        { "ar", ಖಾಲಿ, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", ಖಾಲಿ, },
        { "iw", ಖಾಲಿ, },
        { "yi", ಖಾಲಿ, },
        { "ur", ಖಾಲಿ, },
        { "ug", ಖಾಲಿ, },
        { "kd", ಖಾಲಿ, },
        { "pk", "PK", },
        { "ps", ಖಾಲಿ, }
    }; 
    ಪೂರ್ಣಾಂಕ current_locales_sz;
    ಪೂರ್ಣಾಂಕ i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    ಆದರೆ (current_locales_sz <= 0) {
        ಹಿಂತಿರುಗಿ false;        
    }
    ಗಾಗಿ (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        ಆದರೆ (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            ಆದರೆ (!rtl_locales[i].country) {
                ಹಿಂತಿರುಗಿ true;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಹಿಂತಿರುಗಿ SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    ಹಿಂತಿರುಗಿ false;
}

SDL_Toolkit_ಕಿಟಕಿ_X11 *X11_Toolkit_Create_ಕಿಟಕಿ_Struct(SDL_ಕಿಟಕಿ *ಪೋಷಕ, SDL_Toolkit_ಕಿಟಕಿ_X11 *tkparent, SDL_Toolkit_ಕಿಟಕಿ_ಬಹುಲಕ_X11 ಬಹುಲಕ, ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Color *colorhints, bool create_new_display)
{
    SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ;
    ಪೂರ್ಣಾಂಕ i;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#ಆದರೆ_ಅಂತ್ಯ
    #ವ್ಯಾಖ್ಯಾನಿಸು ErrorFreeRetNull(x, y) SDL_ಗಣ_Error(x); SDL_free(y); ಹಿಂತಿರುಗಿ ಖಾಲಿ
    #ವ್ಯಾಖ್ಯಾನಿಸು ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_ಗಣ_Error(x, y); SDL_free(z); ಹಿಂತಿರುಗಿ ಖಾಲಿ

    ಆದರೆ (!SDL_X11_ತುಂಬು_Symbols()) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // This code could get called from multiple threads maybe?
    X11_XInit_ಎಳೆಗಳು();

    ಕಿಟಕಿ = (SDL_Toolkit_ಕಿಟಕಿ_X11 *)SDL_malloc(ಗಾತ್ರ(SDL_Toolkit_ಕಿಟಕಿ_X11));
    ಆದರೆ (!ಕಿಟಕಿ) {
        SDL_ಗಣ_Error("Unable to allocate toolkit window structure");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಕಿಟಕಿ->ಬಹುಲಕ = ಬಹುಲಕ;
    ಕಿಟಕಿ->tk_ಪೋಷಕ = tkparent;

#ಆದರೆ SDL_ಗಣ_LOCALE
    ಆದರೆ (ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_DIALOG) {
        ಕಿಟಕಿ->origlocale = setlocale(LC_ALL, ಖಾಲಿ);
        ಆದರೆ (ಕಿಟಕಿ->origlocale) {
            ಕಿಟಕಿ->origlocale = SDL_strdup(ಕಿಟಕಿ->origlocale);
            ಆದರೆ (!ಕಿಟಕಿ->origlocale) {
                SDL_free(ಕಿಟಕಿ);
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            }
            (ಶೂನ್ಯ)setlocale(LC_ALL, "");
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಕಿಟಕಿ->ಪೋಷಕ_device = ಖಾಲಿ;
    ಆದರೆ (create_new_display) {
        ಕಿಟಕಿ->display = X11_XOpenDisplay(ಖಾಲಿ);
        ಕಿಟಕಿ->display_close = true;
        ಆದರೆ (!ಕಿಟಕಿ->display) {
            ErrorFreeRetNull("Couldn't open X11 display", ಕಿಟಕಿ);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (ಪೋಷಕ) {
            ಕಿಟಕಿ->ಪೋಷಕ_device = SDL_GetVideoDevice();
            ಕಿಟಕಿ->display = ಕಿಟಕಿ->ಪೋಷಕ_device->ಆಂತರಿಕ->display;
            ಕಿಟಕಿ->display_close = false;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (tkparent) {
            ಕಿಟಕಿ->display = tkparent->display;
            ಕಿಟಕಿ->display_close = false;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->display = X11_XOpenDisplay(ಖಾಲಿ);
            ಕಿಟಕಿ->display_close = true;
            ಆದರೆ (!ಕಿಟಕಿ->display) {
                ErrorFreeRetNull("Couldn't open X11 display", ಕಿಟಕಿ);
            }
        }
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
    ಪೂರ್ಣಾಂಕ xrandr_event_ತಳ, xrandr_error_ತಳ;
    ಕಿಟಕಿ->xrandr = X11_XRRQueryExtension(ಕಿಟಕಿ->display, &xrandr_event_ತಳ, &xrandr_error_ತಳ);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
    ಕಿಟಕಿ->shm_pixmap = False;
    ಕಿಟಕಿ->shm = X11_XShmQueryExtension(ಕಿಟಕಿ->display) ? SDL_X11_HAVE_SHM : false;
    ಆದರೆ (ಕಿಟಕಿ->shm) {
        ಪೂರ್ಣಾಂಕ major;
        ಪೂರ್ಣಾಂಕ minor;

        X11_XShm_Query_ಆವೃತ್ತಿ(ಕಿಟಕಿ->display, &major, &minor, &ಕಿಟಕಿ->shm_pixmap);
        ಆದರೆ (ಕಿಟಕಿ->shm_pixmap) {
            ಆದರೆ (X11_XShmPixmapFormat(ಕಿಟಕಿ->display) != ZPixmap) {
                ಕಿಟಕಿ->shm_pixmap = False;
            }
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    /* Scale/Xsettings */
    ಕಿಟಕಿ->pixmap = false;
    ಕಿಟಕಿ->xsettings_ಮೊದಲ_ಸಮಯ = true;
    ಕಿಟಕಿ->xsettings = xsettings_client_new(ಕಿಟಕಿ->display, DefaultScreen(ಕಿಟಕಿ->display), X11Toolkit_SettingsNotify, ಖಾಲಿ, ಕಿಟಕಿ);
    ಕಿಟಕಿ->xsettings_ಮೊದಲ_ಸಮಯ = false;
    ಕಿಟಕಿ->scale = X11_GetGlobalContentScale(ಕಿಟಕಿ->display, ಕಿಟಕಿ->xsettings);
    ಆದರೆ (ಕಿಟಕಿ->scale < 1) {
        ಕಿಟಕಿ->scale = 1;
    }
    ಕಿಟಕಿ->iscale = (ಪೂರ್ಣಾಂಕ)SDL_ceilf(ಕಿಟಕಿ->scale);
    ಆದರೆ (SDL_roundf(ಕಿಟಕಿ->scale) == ಕಿಟಕಿ->scale) {
        ಕಿಟಕಿ->scale = 0;
    }

    /* Fonts */
    X11_Toolkit_Init_ಕಿಟಕಿ_Fonts(ಕಿಟಕಿ);

    /* Color hints */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    ಆದರೆ (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!colorhints) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_USE_LIBDBUS
        ಆಯ್ಕೆ (theme) {
            ಸ್ಥಿತಿ SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                ನಿಲ್ಲಿಸು;
#ಆದರೆ 0
            ಸ್ಥಿತಿ SDL_SYSTEM_THEME_LIGHT_ಮೇಲಿನ_CONTRAST:
                colorhints = g_default_colors_light_ಮೇಲಿನ_contrast;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ SDL_SYSTEM_THEME_DARK_ಮೇಲಿನ_CONTRAST:
                colorhints = g_default_colors_dark_ಮೇಲಿನ_contrast;
                ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
            ಪೂರ್ವನಿಯೋಜಿತ:
                colorhints = g_default_colors;
        }
#ಇಲ್ಲದಿದ್ದರೆ
        colorhints = g_default_colors;
#ಆದರೆ_ಅಂತ್ಯ
    }
    ಕಿಟಕಿ->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    ಗಾಗಿ (i = 0; i < SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ; i++) {
        ಕಿಟಕಿ->xcolor[i].flags = DoRed|DoGreen|DoBlue;
        ಕಿಟಕಿ->xcolor[i].red = colorhints[i].r * 257;
        ಕಿಟಕಿ->xcolor[i].green = colorhints[i].g * 257;
        ಕಿಟಕಿ->xcolor[i].blue = colorhints[i].b * 257;
    }

    /* Generate bevel and pressed colors */
    ಕಿಟಕಿ->xcolor_bevel_l1.flags = DoRed|DoGreen|DoBlue;
    ಕಿಟಕಿ->xcolor_bevel_l1.red = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 12500, 0, 65535);
    ಕಿಟಕಿ->xcolor_bevel_l1.green = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 12500, 0, 65535);
    ಕಿಟಕಿ->xcolor_bevel_l1.blue = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 12500, 0, 65535);

    ಕಿಟಕಿ->xcolor_bevel_l2.flags = DoRed|DoGreen|DoBlue;
    ಕಿಟಕಿ->xcolor_bevel_l2.red = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 32500, 0, 65535);
    ಕಿಟಕಿ->xcolor_bevel_l2.green = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 32500, 0, 65535);
    ಕಿಟಕಿ->xcolor_bevel_l2.blue = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 32500, 0, 65535);

    ಕಿಟಕಿ->xcolor_bevel_d.flags = DoRed|DoGreen|DoBlue;
    ಕಿಟಕಿ->xcolor_bevel_d.red = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red - 22500, 0, 65535);
    ಕಿಟಕಿ->xcolor_bevel_d.green = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green - 22500, 0, 65535);
    ಕಿಟಕಿ->xcolor_bevel_d.blue = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue - 22500, 0, 65535);

    ಕಿಟಕಿ->xcolor_pressed.flags = DoRed|DoGreen|DoBlue;
    ಕಿಟಕಿ->xcolor_pressed.red = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].red - 12500, 0, 65535);
    ಕಿಟಕಿ->xcolor_pressed.green = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].green - 12500, 0, 65535);
    ಕಿಟಕಿ->xcolor_pressed.blue = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].blue - 12500, 0, 65535);

    ಕಿಟಕಿ->xcolor_disabled_ಪಠ್ಯ.flags = DoRed|DoGreen|DoBlue;
    ಕಿಟಕಿ->xcolor_disabled_ಪಠ್ಯ.red = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_ಪಠ್ಯ].red + 19500, 0, 65535);
    ಕಿಟಕಿ->xcolor_disabled_ಪಠ್ಯ.green = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_ಪಠ್ಯ].green + 19500, 0, 65535);
    ಕಿಟಕಿ->xcolor_disabled_ಪಠ್ಯ.blue = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_ಪಠ್ಯ].blue + 19500, 0, 65535);

    /* Screen */
    ಕಿಟಕಿ->ಪೋಷಕ = ಪೋಷಕ;
    ಆದರೆ (ಪೋಷಕ) {
        SDL_Display_ದತ್ತಾಂಶ *displaydata = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(ಪೋಷಕ);
        ಕಿಟಕಿ->screen = displaydata->screen;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಕಿಟಕಿ->screen = DefaultScreen(ಕಿಟಕಿ->display);
    }

    /* Visuals */
    ಆದರೆ (ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_ಮಗು) {
        ಕಿಟಕಿ->visual = ಪೋಷಕ->ಆಂತರಿಕ->visual;
        ಕಿಟಕಿ->cmap = ಪೋಷಕ->ಆಂತರಿಕ->colormap;
        X11_GetVisualInfoFromVisual(ಕಿಟಕಿ->display, ಕಿಟಕಿ->visual, &ಕಿಟಕಿ->vi);
        ಕಿಟಕಿ->ಆಳ_2 = ಕಿಟಕಿ->vi.ಆಳ_2;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಕಿಟಕಿ->visual = DefaultVisual(ಕಿಟಕಿ->display, ಕಿಟಕಿ->screen);
        ಕಿಟಕಿ->cmap = DefaultColormap(ಕಿಟಕಿ->display, ಕಿಟಕಿ->screen);
        ಕಿಟಕಿ->ಆಳ_2 = Default_ಆಳ(ಕಿಟಕಿ->display, ಕಿಟಕಿ->screen);
        X11_GetVisualInfoFromVisual(ಕಿಟಕಿ->display, ಕಿಟಕಿ->visual, &ಕಿಟಕಿ->vi);
    }

    /* Allocate colors */
    ಗಾಗಿ (i = 0; i < SDL_MESSAGEBOX_COLOR_ಎಣಿಕೆ; i++) {
        X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &ಕಿಟಕಿ->xcolor[i]);
    }
    X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &ಕಿಟಕಿ->xcolor_bevel_l1);
    X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &ಕಿಟಕಿ->xcolor_bevel_l2);
    X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &ಕಿಟಕಿ->xcolor_bevel_d);
    X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &ಕಿಟಕಿ->xcolor_pressed);
    X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &ಕಿಟಕಿ->xcolor_disabled_ಪಠ್ಯ);

    /* Control list */
    ಕಿಟಕಿ->has_focus = false;
    ಕಿಟಕಿ->controls = ಖಾಲಿ;
    ಕಿಟಕಿ->controls_sz = 0;
    ಕಿಟಕಿ->dyn_controls_sz = 0;
    ಕಿಟಕಿ->fiddled_control = ಖಾಲಿ;
    ಕಿಟಕಿ->dyn_controls = ಖಾಲಿ;

    /* Menu windows */
    ಕಿಟಕಿ->popup_windows = ಖಾಲಿ;

    /* BIDI engine */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
    ಕಿಟಕಿ->fribidi = SDL_FriBidi_Create();
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBTHAI_H
    ಕಿಟಕಿ->th = SDL_LibThai_Create();
#ಆದರೆ_ಅಂತ್ಯ
    
    /* Interface direction */
    ಕಿಟಕಿ->flip_interface = X11Toolkit_ShouldFlipUI();
    
    ಹಿಂತಿರುಗಿ ಕಿಟಕಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Toolkit_ಕೂಡಿಸು_Control_ಗಮ್ಯ_ಕಿಟಕಿ(SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    ಕಿಟಕಿ->controls_sz++;
    ಆದರೆ (ಕಿಟಕಿ->controls_sz == 1) {
        ಕಿಟಕಿ->controls = (ರಚನೆ SDL_ToolkitControlX11 **)SDL_malloc(ಗಾತ್ರ(ರಚನೆ SDL_ToolkitControlX11 *));
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಕಿಟಕಿ->controls = (ರಚನೆ SDL_ToolkitControlX11 **)SDL_realloc(ಕಿಟಕಿ->controls, ಗಾತ್ರ(ರಚನೆ SDL_ToolkitControlX11 *) * ಕಿಟಕಿ->controls_sz);
    }
    ಕಿಟಕಿ->controls[ಕಿಟಕಿ->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    ಆದರೆ (control->dynamic) {
        ಕಿಟಕಿ->dyn_controls_sz++;
        ಆದರೆ (ಕಿಟಕಿ->dyn_controls_sz == 1) {
            ಕಿಟಕಿ->dyn_controls = (ರಚನೆ SDL_ToolkitControlX11 **)SDL_malloc(ಗಾತ್ರ(ರಚನೆ SDL_ToolkitControlX11 *));
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕಿಟಕಿ->dyn_controls = (ರಚನೆ SDL_ToolkitControlX11 **)SDL_realloc(ಕಿಟಕಿ->dyn_controls, ಗಾತ್ರ(ರಚನೆ SDL_ToolkitControlX11 *) * ಕಿಟಕಿ->dyn_controls_sz);
        }
        ಕಿಟಕಿ->dyn_controls[ಕಿಟಕಿ->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    ಆದರೆ (control->selected) {
        ಕಿಟಕಿ->focused_control = control;
    }
}

bool X11_Toolkit_Create_ಕಿಟಕಿ_Res(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ cx, ಪೂರ್ಣಾಂಕ cy, ಅಕ್ಷರ *title)
{
    ಪೂರ್ಣಾಂಕ x, y;
    XSizeHints *sizehints;
    XSet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು wnd_attr;
    Atom NET_WM_ಕಿಟಕಿ_TYPE, NET_WM_ಕಿಟಕಿ_TYPE_DIALOG, NET_WM_ಕಿಟಕಿ_TYPE_DROPDOWN_MENU, NET_WM_ಕಿಟಕಿ_TYPE_TOOLTIP;
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *windowdata = ಖಾಲಿ;
    Display *display = ದತ್ತಾಂಶ->display;
    XGCValues ctx_vals;
    ಕಿಟಕಿ_2 ಬೇರು_win;
    ಕಿಟಕಿ_2 ಪೋಷಕ_win;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ gcflags = GCForeground | GCBackground;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ valuemask;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XRANDR_DISABLED_BY_DEFAULT
    ಸ್ಥಿರಾಂಕ bool use_xrandr_by_default = false;
#ಇಲ್ಲದಿದ್ದರೆ
    ಸ್ಥಿರಾಂಕ bool use_xrandr_by_default = true;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ದತ್ತಾಂಶ->scale == 0) {
        ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ = w;
        ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ = h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ = SDL_lroundf((w/ದತ್ತಾಂಶ->iscale) * ದತ್ತಾಂಶ->scale);
        ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ = SDL_lroundf((h/ದತ್ತಾಂಶ->iscale) * ದತ್ತಾಂಶ->scale);
        ದತ್ತಾಂಶ->pixmap_ಅಗಲ = w;
        ದತ್ತಾಂಶ->pixmap_ಎತ್ತರ = h;
        ದತ್ತಾಂಶ->pixmap = true;
    }

    ಆದರೆ (ದತ್ತಾಂಶ->ಪೋಷಕ) {
        windowdata = ದತ್ತಾಂಶ->ಪೋಷಕ->ಆಂತರಿಕ;
    }

    valuemask = CWEvent_ಮುಖವಾಡ | CWColormap;
    ದತ್ತಾಂಶ->event_ಮುಖವಾಡ = Exposure_ಮುಖವಾಡ |
                       Button_Press_ಮುಖವಾಡ | Button_Release_ಮುಖವಾಡ | ಕೀಲಿ_Press_ಮುಖವಾಡ | ಕೀಲಿ_Release_ಮುಖವಾಡ |
                       Structure_Notify_ಮುಖವಾಡ | Focus_Change_ಮುಖವಾಡ | ಸೂಚಕ_Motion_ಮುಖವಾಡ;
    wnd_attr.event_ಮುಖವಾಡ = ದತ್ತಾಂಶ->event_ಮುಖವಾಡ;
    wnd_attr.colormap = ದತ್ತಾಂಶ->cmap;
    ಆದರೆ (ದತ್ತಾಂಶ->ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_MENU || ದತ್ತಾಂಶ->ಬಹುಲಕ== SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    ಬೇರು_win = ಬೇರು_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->screen);
    ಆದರೆ (ದತ್ತಾಂಶ->ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_ಮಗು) {
        ಪೋಷಕ_win = windowdata->xwindow;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಪೋಷಕ_win = ಬೇರು_win;
    }

    ದತ್ತಾಂಶ->ಕಿಟಕಿ = X11_XCreate_ಕಿಟಕಿ(
        display, ಪೋಷಕ_win,
        0, 0,
        ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ, ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ,
        0, ದತ್ತಾಂಶ->ಆಳ_2, ಒಳಹರಿವು_Output, ದತ್ತಾಂಶ->visual,
        valuemask, &wnd_attr);
    ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ == None) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't create X window");
    }

    ಆದರೆ (windowdata && ದತ್ತಾಂಶ->ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_DIALOG) {
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
        X11_XChangeProperty(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_ಬಹುಲಕ_Replace, (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)stateatoms, statecount);
    }

    ಆದರೆ (windowdata && ದತ್ತಾಂಶ->ಬಹುಲಕ != SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_ಮಗು) {
        X11_XSetTransientForHint(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, windowdata->xwindow);
    }

    ಆದರೆ (ದತ್ತಾಂಶ->tk_ಪೋಷಕ) {
        X11_XSetTransientForHint(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, ದತ್ತಾಂಶ->tk_ಪೋಷಕ->ಕಿಟಕಿ);
    }

    SDL_X11_ಗಣ_ಕಿಟಕಿ_Title(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, title);

    // Let the window manager the type of the window
    ಆದರೆ (ದತ್ತಾಂಶ->ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_DIALOG) {
        NET_WM_ಕಿಟಕಿ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_ಕಿಟಕಿ_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, NET_WM_ಕಿಟಕಿ_TYPE, XA_ATOM, 32,
                            Prop_ಬಹುಲಕ_Replace,
                            (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)&NET_WM_ಕಿಟಕಿ_TYPE_DIALOG, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_MENU) {
        NET_WM_ಕಿಟಕಿ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_ಕಿಟಕಿ_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, NET_WM_ಕಿಟಕಿ_TYPE, XA_ATOM, 32,
                            Prop_ಬಹುಲಕ_Replace,
                            (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)&NET_WM_ಕಿಟಕಿ_TYPE_DROPDOWN_MENU, 1);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ದತ್ತಾಂಶ->ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_TOOLTIP) {
        NET_WM_ಕಿಟಕಿ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_ಕಿಟಕಿ_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, NET_WM_ಕಿಟಕಿ_TYPE, XA_ATOM, 32,
                            Prop_ಬಹುಲಕ_Replace,
                            (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)&NET_WM_ಕಿಟಕಿ_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    ದತ್ತಾಂಶ->wm_delete_ಸಂದೇಶ = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, &ದತ್ತಾಂಶ->wm_delete_ಸಂದೇಶ, 1);
    ದತ್ತಾಂಶ->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    ಆದರೆ (ದತ್ತಾಂಶ->ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_MENU || ದತ್ತಾಂಶ->ಬಹುಲಕ== SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_TOOLTIP) {
        x = cx;
        y = cy;
        ಹೋಗು MOVEWINDOW;
    }
    ಆದರೆ (windowdata) {
        XWindow_ಗುಣಲಕ್ಷಣಗಳು attrib;
        ಕಿಟಕಿ_2 dummy;

        X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.ಅಗಲ - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ) / 2;
        y = attrib.y + (attrib.ಎತ್ತರ - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, ಬೇರು_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->screen), x, y, &x, &y, &dummy);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ SDL_VideoDevice *dev = SDL_GetVideoDevice();
        ಆದರೆ (dev && dev->displays && dev->ಅಂಕೆ_displays > 0) {
            ಸ್ಥಿರಾಂಕ SDL_VideoDisplay *dpy = dev->displays[0];
            ಸ್ಥಿರಾಂಕ SDL_Display_ದತ್ತಾಂಶ *dpydata = dpy->ಆಂತರಿಕ;
            x = dpydata->x + ((dpy->current_ಬಹುಲಕ->w - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ) / 2);
            y = dpydata->y + ((dpy->current_ಬಹುಲಕ->h - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ) / 3);
        }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && ದತ್ತಾಂಶ->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_ಹೊರಹೋಗು;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, ಬೇರು_win);
            ಆದರೆ (!screen_res) {
                ಹೋಗು NOXRANDR;
            }

            default_ಹೊರಹೋಗು = X11_XRRGetOutputPrimary(display, ಬೇರು_win);
            ಆದರೆ (default_ಹೊರಹೋಗು != None) {
                XRROutputInfo *ಹೊರಹೋಗು_info;

                ಹೊರಹೋಗು_info = X11_XRRGetOutputInfo(display, screen_res, default_ಹೊರಹೋಗು);
                ಆದರೆ (ಹೊರಹೋಗು_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(ಹೊರಹೋಗು_info);
                    ಹೋಗು FIRSTOUTPUTXRANDR;
                }

                ಆದರೆ (ಹೊರಹೋಗು_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ಹೊರಹೋಗು_info->crtc);
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಹೊರಹೋಗು_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ಹೊರಹೋಗು_info->crtcs[0]);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    crtc_info = ಖಾಲಿ;
                }
                
                ಆದರೆ (crtc_info) {
                    x = (crtc_info->ಅಗಲ - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ) / 2;
                    y = (crtc_info->ಎತ್ತರ - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ) / 3;
                    X11_XRRFreeOutputInfo(ಹೊರಹೋಗು_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    X11_XRRFreeOutputInfo(ಹೊರಹೋಗು_info);
                    ಹೋಗು NOXRANDR;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                    FIRSTOUTPUTXRANDR:
                    ಆದರೆ (screen_res->noutput > 0) {
                        XRROutputInfo *ಹೊರಹೋಗು_info;

                        ಹೊರಹೋಗು_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        ಆದರೆ (!ಹೊರಹೋಗು_info) {
                            ಹೋಗು FIRSTCRTCXRANDR;
                        }

                        ಆದರೆ (ಹೊರಹೋಗು_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ಹೊರಹೋಗು_info->crtc);
                        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಹೊರಹೋಗು_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ಹೊರಹೋಗು_info->crtcs[0]);
                        } ಇಲ್ಲದಿದ್ದರೆ {
                            crtc_info = ಖಾಲಿ;
                        }

                        ಆದರೆ (!crtc_info) {
                            X11_XRRFreeOutputInfo(ಹೊರಹೋಗು_info);
                            ಹೋಗು FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->ಅಗಲ - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ) / 2;
                        y = (crtc_info->ಎತ್ತರ - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ) / 3;
                        X11_XRRFreeOutputInfo(ಹೊರಹೋಗು_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        ಹೋಗು MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    ಆದರೆ (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        ಹೋಗು NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    ಆದರೆ (crtc_info) {
                        x = (crtc_info->ಅಗಲ - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ) / 2;
                        y = (crtc_info->ಎತ್ತರ - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        X11_XRRFreeScreenResources(screen_res);
                        ಹೋಗು NOXRANDR;
                    }
            }
        }
#ಆದರೆ_ಅಂತ್ಯ
        ಇಲ್ಲದಿದ್ದರೆ {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (Display_ಅಗಲ(display, ದತ್ತಾಂಶ->screen) - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ) / 2;
            y = (Display_ಎತ್ತರ(display, ದತ್ತಾಂಶ->screen) - ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMove_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, x, y);
    ದತ್ತಾಂಶ->ಕಿಟಕಿ_x = x;
    ದತ್ತಾಂಶ->ಕಿಟಕಿ_y = y;

    sizehints = X11_XAlloc_ಗಾತ್ರ_Hints();
    ಆದರೆ (sizehints) {
        sizehints->flags = USPosition | USSize | PMax_ಗಾತ್ರ | PMin_ಗಾತ್ರ;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->ಅಗಲ = ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ;
        sizehints->ಎತ್ತರ = ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ;

        sizehints->min_ಅಗಲ_2 = sizehints->max_ಅಗಲ_2 = ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ;
        sizehints->min_ಎತ್ತರ_2 = sizehints->max_ಎತ್ತರ_2 = ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ;

        X11_XSetWMNormalHints(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ);

    ದತ್ತಾಂಶ->drawable = ದತ್ತಾಂಶ->ಕಿಟಕಿ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    ಆದರೆ (SDL_X11_HAVE_XDBE && !ದತ್ತಾಂಶ->pixmap) {
        ಪೂರ್ಣಾಂಕ xdbe_major, xdbe_minor;
        ಆದರೆ (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            ದತ್ತಾಂಶ->xdbe = true;
            ದತ್ತಾಂಶ->buf = X11_Xdbe_Allocate_ಹಿಂಭಾಗ_ಬಫರ್_Name(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, XdbeUndefined);
            ದತ್ತಾಂಶ->drawable = ದತ್ತಾಂಶ->buf;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ದತ್ತಾಂಶ->xdbe = false;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ

    X11_Toolkit_Init_ಕಿಟಕಿ_Pixmap(ದತ್ತಾಂಶ);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = ದತ್ತಾಂಶ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = ದತ್ತಾಂಶ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ಆದರೆ (!ದತ್ತಾಂಶ->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = ದತ್ತಾಂಶ->font_struct->fid;
    }
    ದತ್ತಾಂಶ->ctx = X11_XCreateGC(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, gcflags, &ctx_vals);
    ಆದರೆ (ದತ್ತಾಂಶ->ctx == None) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't create graphics context");
    }

    ದತ್ತಾಂಶ->close = false;
    ದತ್ತಾಂಶ->ಕೀಲಿ_control_esc = ದತ್ತಾಂಶ->ಕೀಲಿ_control_enter = ಖಾಲಿ;
    ಆದರೆ (!ದತ್ತಾಂಶ->pixmap) {
        ದತ್ತಾಂಶ->ev_scale = ದತ್ತಾಂಶ->ev_iscale = 1;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->ev_scale = ದತ್ತಾಂಶ->scale;
        ದತ್ತಾಂಶ->ev_iscale = ದತ್ತಾಂಶ->iscale;
    }

#ಆದರೆ SDL_GRAB
    ಆದರೆ (ದತ್ತಾಂಶ->ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_MENU || ದತ್ತಾಂಶ->ಬಹುಲಕ== SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_TOOLTIP) {
        X11_XGrab_ಸೂಚಕ(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, False, Button_Press_ಮುಖವಾಡ | Button_Release_ಮುಖವಾಡ | ಸೂಚಕ_Motion_ಮುಖವಾಡ, Grab_ಬಹುಲಕ_Async, Grab_ಬಹುಲಕ_Async, None, None, Current_ಸಮಯ);
        X11_XGrabKeyboard(display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, False, Grab_ಬಹುಲಕ_Async, Grab_ಬಹುಲಕ_Async, Current_ಸಮಯ);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Toolkit_Draw_ಕಿಟಕಿ(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ) {
    SDL_Rect rect;
    ಪೂರ್ಣಾಂಕ i;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XDBE
    ಆದರೆ (SDL_X11_HAVE_XDBE && ದತ್ತಾಂಶ->xdbe && !ದತ್ತಾಂಶ->pixmap) {
        X11_XdbeBeginIdiom(ದತ್ತಾಂಶ->display);
    }
#ಆದರೆ_ಅಂತ್ಯ

    X11_XSetForeground(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->ctx, ದತ್ತಾಂಶ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    ಆದರೆ (ದತ್ತಾಂಶ->pixmap) {
        X11_XFillRectangle(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->ctx, 0, 0, ದತ್ತಾಂಶ->pixmap_ಅಗಲ, ದತ್ತಾಂಶ->pixmap_ಎತ್ತರ);
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_XFillRectangle(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->ctx, 0, 0, ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ, ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ);
    }

    ಗಾಗಿ (i = 0; i < ದತ್ತಾಂಶ->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = ದತ್ತಾಂಶ->controls[i];
        ಆದರೆ (control) {
            ಆದರೆ (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XDBE
    ಆದರೆ (SDL_X11_HAVE_XDBE && ದತ್ತಾಂಶ->xdbe && !ದತ್ತಾಂಶ->pixmap) {
        Xdbe_ಅದಲುಬದಲು_Info ಅದಲುಬದಲು_info;
        ಅದಲುಬದಲು_info.ಅದಲುಬದಲು_ಕಿಟಕಿ = ದತ್ತಾಂಶ->ಕಿಟಕಿ;
        ಅದಲುಬದಲು_info.ಅದಲುಬದಲು_action = XdbeUndefined;
        X11_Xdbe_ಅದಲುಬದಲು_Buffers(ದತ್ತಾಂಶ->display, &ಅದಲುಬದಲು_info, 1);
        X11_Xdbe_ಕೊನೆ_Idiom(ದತ್ತಾಂಶ->display);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ದತ್ತಾಂಶ->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ;
        rect.h = ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
        ಆದರೆ (ದತ್ತಾಂಶ->shm) {
            ಆದರೆ (ದತ್ತಾಂಶ->shm_pixmap) {
                X11_XFlush(ದತ್ತಾಂಶ->display);
                X11_XSync(ದತ್ತಾಂಶ->display, false);
                scale_surface = SDL_CreateSurfaceFrom(ದತ್ತಾಂಶ->pixmap_ಅಗಲ, ದತ್ತಾಂಶ->pixmap_ಎತ್ತರ, X11_GetPixelFormatFromVisualInfo(ದತ್ತಾಂಶ->display, &ದತ್ತಾಂಶ->vi), ದತ್ತಾಂಶ->shm_info.shmaddr, ದತ್ತಾಂಶ->shm_ಬೈಟುಗಳು_ಪ್ರತಿ_ಸಾಲು);
                SDL_BlitSurfaceScaled(scale_surface, ಖಾಲಿ, scale_surface, &rect, SDL_SCALEMODE_ರೇಖೀಯ);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->ಕಿಟಕಿ, ದತ್ತಾಂಶ->ctx, 0, 0, ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ, ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ, 0, 0);
            } ಇಲ್ಲದಿದ್ದರೆ {
                X11_XShmGetImage(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, ದತ್ತಾಂಶ->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(ದತ್ತಾಂಶ->pixmap_ಅಗಲ, ದತ್ತಾಂಶ->pixmap_ಎತ್ತರ, X11_GetPixelFormatFromVisualInfo(ದತ್ತಾಂಶ->display, &ದತ್ತಾಂಶ->vi), ದತ್ತಾಂಶ->image->ದತ್ತಾಂಶ, ದತ್ತಾಂಶ->image->ಬೈಟುಗಳು_ಪ್ರತಿ_ಸಾಲು);
                SDL_BlitSurfaceScaled(scale_surface, ಖಾಲಿ, scale_surface, &rect, SDL_SCALEMODE_ರೇಖೀಯ);
                X11_XShmPutImage(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, ದತ್ತಾಂಶ->ctx, ದತ್ತಾಂಶ->image, 0, 0, 0, 0, ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ, ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ, False);
            }
        } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
        {
            XImage *image;

            image = X11_XGetImage(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable, 0, 0 , ದತ್ತಾಂಶ->pixmap_ಅಗಲ, ದತ್ತಾಂಶ->pixmap_ಎತ್ತರ, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(ದತ್ತಾಂಶ->pixmap_ಅಗಲ, ದತ್ತಾಂಶ->pixmap_ಎತ್ತರ, X11_GetPixelFormatFromVisualInfo(ದತ್ತಾಂಶ->display, &ದತ್ತಾಂಶ->vi), image->ದತ್ತಾಂಶ, image->ಬೈಟುಗಳು_ಪ್ರತಿ_ಸಾಲು);
            SDL_BlitSurfaceScaled(scale_surface, ಖಾಲಿ, scale_surface, &rect, SDL_SCALEMODE_ರೇಖೀಯ);
            X11_XPutImage(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, ದತ್ತಾಂಶ->ctx, image, 0, 0, 0, 0, ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ, ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(ದತ್ತಾಂಶ->display);
}

ಸ್ಥಿರ SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < ದತ್ತಾಂಶ->controls_sz; i++) {
        SDL_Rect *rect = &ದತ್ತಾಂಶ->controls[i]->rect;
        ಆದರೆ ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            ಹಿಂತಿರುಗಿ ದತ್ತಾಂಶ->controls[i];
        }
    }

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
ಸ್ಥಿರ Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ = (SDL_Toolkit_ಕಿಟಕಿ_X11 *)arg;

    ಆದರೆ (event->xany.display != ದತ್ತಾಂಶ->display) {
        ಹಿಂತಿರುಗಿ False;
    }

    ಆದರೆ (event->xany.ಕಿಟಕಿ == ದತ್ತಾಂಶ->ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ True;
    }

    ಹಿಂತಿರುಗಿ False;
}

ಶೂನ್ಯ X11_Toolkit_Process_ಕಿಟಕಿ_Events(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    ಆದರೆ ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        ಹಿಂತಿರುಗಿ;
    }

    ದತ್ತಾಂಶ->draw = false;
    ದತ್ತಾಂಶ->e = e;

    ಆಯ್ಕೆ (e->type) {
        ಸ್ಥಿತಿ Expose:
            ದತ್ತಾಂಶ->draw = true;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ Client_ಸಂದೇಶ:
            ಆದರೆ (e->xclient.ಸಂದೇಶ_type == ದತ್ತಾಂಶ->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.ದತ್ತಾಂಶ.l[0] == ದತ್ತಾಂಶ->wm_delete_ಸಂದೇಶ) {
                ದತ್ತಾಂಶ->close = true;
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ Focus_ಒಳ:
            ದತ್ತಾಂಶ->has_focus = true;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ Focus_ಹೊರಹೋಗು:
            ದತ್ತಾಂಶ->has_focus = false;
            ಆದರೆ (ದತ್ತಾಂಶ->fiddled_control) {
                ದತ್ತಾಂಶ->fiddled_control->selected = false;
            }
            ದತ್ತಾಂಶ->fiddled_control = ಖಾಲಿ;
            ಗಾಗಿ (ದತ್ತಾಂಶ->ev_i = 0; ದತ್ತಾಂಶ->ev_i < ದತ್ತಾಂಶ->controls_sz; ದತ್ತಾಂಶ->ev_i++) {
                ದತ್ತಾಂಶ->controls[ದತ್ತಾಂಶ->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_ಸಾಮಾನ್ಯ;
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ MotionNotify:
            ಆದರೆ (ದತ್ತಾಂಶ->has_focus) {
                ದತ್ತಾಂಶ->ಹಿಂದಿನ_control = ದತ್ತಾಂಶ->fiddled_control;
                ದತ್ತಾಂಶ->fiddled_control = X11Toolkit_GetControlMouseIsOn(ದತ್ತಾಂಶ, SDL_lroundf((e->xbutton.x/ ದತ್ತಾಂಶ->ev_scale)* ದತ್ತಾಂಶ->ev_iscale), SDL_lroundf((e->xbutton.y/ ದತ್ತಾಂಶ->ev_scale)* ದತ್ತಾಂಶ->ev_iscale));
                ಆದರೆ (ದತ್ತಾಂಶ->ಹಿಂದಿನ_control) {
                    ದತ್ತಾಂಶ->ಹಿಂದಿನ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ಸಾಮಾನ್ಯ;
                    ಆದರೆ (ದತ್ತಾಂಶ->ಹಿಂದಿನ_control->func_on_state_change) {
                        ದತ್ತಾಂಶ->ಹಿಂದಿನ_control->func_on_state_change(ದತ್ತಾಂಶ->ಹಿಂದಿನ_control);
                    }
                    ದತ್ತಾಂಶ->draw = true;
                }
                ಆದರೆ (ದತ್ತಾಂಶ->fiddled_control) {
                    ಆದರೆ (ದತ್ತಾಂಶ->fiddled_control->dynamic) {
                        ದತ್ತಾಂಶ->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        ಆದರೆ (ದತ್ತಾಂಶ->fiddled_control->func_on_state_change) {
                            ದತ್ತಾಂಶ->fiddled_control->func_on_state_change(ದತ್ತಾಂಶ->fiddled_control);
                        }
                        ದತ್ತಾಂಶ->draw = true;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        ದತ್ತಾಂಶ->fiddled_control = ಖಾಲಿ;
                    }
                }
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ ButtonPress:
            ದತ್ತಾಂಶ->ಹಿಂದಿನ_control = ದತ್ತಾಂಶ->fiddled_control;
            ಆದರೆ (ದತ್ತಾಂಶ->ಹಿಂದಿನ_control) {
                ದತ್ತಾಂಶ->ಹಿಂದಿನ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ಸಾಮಾನ್ಯ;
                ಆದರೆ (ದತ್ತಾಂಶ->ಹಿಂದಿನ_control->func_on_state_change) {
                    ದತ್ತಾಂಶ->ಹಿಂದಿನ_control->func_on_state_change(ದತ್ತಾಂಶ->ಹಿಂದಿನ_control);
                }
                ದತ್ತಾಂಶ->draw = true;
            }
            ಆದರೆ (e->xbutton.button == Button1) {
                ದತ್ತಾಂಶ->fiddled_control = X11Toolkit_GetControlMouseIsOn(ದತ್ತಾಂಶ, SDL_lroundf((e->xbutton.x/ ದತ್ತಾಂಶ->ev_scale)* ದತ್ತಾಂಶ->ev_iscale), SDL_lroundf((e->xbutton.y/ ದತ್ತಾಂಶ->ev_scale)* ದತ್ತಾಂಶ->ev_iscale));
                ಆದರೆ (ದತ್ತಾಂಶ->fiddled_control) {
                    ದತ್ತಾಂಶ->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    ಆದರೆ (ದತ್ತಾಂಶ->fiddled_control->func_on_state_change) {
                        ದತ್ತಾಂಶ->fiddled_control->func_on_state_change(ದತ್ತಾಂಶ->fiddled_control);
                    }
                    ದತ್ತಾಂಶ->draw = true;
                }
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ ButtonRelease:
            ಆದರೆ (ದತ್ತಾಂಶ->ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_MENU || ದತ್ತಾಂಶ->ಬಹುಲಕ== SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_TOOLTIP) {
                ಪೂರ್ಣಾಂಕ cx;
                ಪೂರ್ಣಾಂಕ cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                ಆದರೆ (cy < 0 || cx < 0) {
                    ದತ್ತಾಂಶ->close = true;
                }

                ಆದರೆ (cy > ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ || cx > ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ) {
                    ದತ್ತಾಂಶ->close = true;
                }
            }

            ಆದರೆ ((e->xbutton.button == Button1) && (ದತ್ತಾಂಶ->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(ದತ್ತಾಂಶ, SDL_lroundf((e->xbutton.x/ ದತ್ತಾಂಶ->ev_scale)* ದತ್ತಾಂಶ->ev_iscale), SDL_lroundf((e->xbutton.y/ ದತ್ತಾಂಶ->ev_scale)* ದತ್ತಾಂಶ->ev_iscale));
                ಆದರೆ (ದತ್ತಾಂಶ->fiddled_control == control) {
                    ದತ್ತಾಂಶ->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    ಆದರೆ (ದತ್ತಾಂಶ->fiddled_control->func_on_state_change) {
                        ದತ್ತಾಂಶ->fiddled_control->func_on_state_change(ದತ್ತಾಂಶ->fiddled_control);
                    }
                    ದತ್ತಾಂಶ->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ಸಾಮಾನ್ಯ;
                    ದತ್ತಾಂಶ->draw = true;
                }
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ ಕೀಲಿ_Press:
            ದತ್ತಾಂಶ->ಕೊನೆಯ_ಕೀಲಿ_pressed = X11_XLookupKeysym(&e->xkey, 0);

            ಆದರೆ (ದತ್ತಾಂಶ->ಕೊನೆಯ_ಕೀಲಿ_pressed == XK_Escape) {
                ಗಾಗಿ (ದತ್ತಾಂಶ->ev_i = 0; ದತ್ತಾಂಶ->ev_i < ದತ್ತಾಂಶ->controls_sz; ದತ್ತಾಂಶ->ev_i++) {
                    ಆದರೆ(ದತ್ತಾಂಶ->controls[ದತ್ತಾಂಶ->ev_i]->is_default_esc) {
                        ದತ್ತಾಂಶ->controls[ದತ್ತಾಂಶ->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        ದತ್ತಾಂಶ->draw = true;
                        ದತ್ತಾಂಶ->ಕೀಲಿ_control_esc = ದತ್ತಾಂಶ->controls[ದತ್ತಾಂಶ->ev_i];
                    }
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ದತ್ತಾಂಶ->ಕೊನೆಯ_ಕೀಲಿ_pressed == XK_Return) || (ದತ್ತಾಂಶ->ಕೊನೆಯ_ಕೀಲಿ_pressed == XK_KP_Enter)) {
                ಗಾಗಿ (ದತ್ತಾಂಶ->ev_i = 0; ದತ್ತಾಂಶ->ev_i < ದತ್ತಾಂಶ->controls_sz; ದತ್ತಾಂಶ->ev_i++) {
                    ಆದರೆ(ದತ್ತಾಂಶ->controls[ದತ್ತಾಂಶ->ev_i]->selected) {
                        ದತ್ತಾಂಶ->controls[ದತ್ತಾಂಶ->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        ದತ್ತಾಂಶ->draw = true;
                        ದತ್ತಾಂಶ->ಕೀಲಿ_control_enter = ದತ್ತಾಂಶ->controls[ದತ್ತಾಂಶ->ev_i];
                    }
                }
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ ಕೀಲಿ_Release:
        {
            ಕೀಲಿ_Sym ಕೀಲಿ = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            ಆದರೆ (ಕೀಲಿ != ದತ್ತಾಂಶ->ಕೊನೆಯ_ಕೀಲಿ_pressed) {
                ನಿಲ್ಲಿಸು;
            }

            ಆದರೆ (ಕೀಲಿ == XK_Escape) {
                ಆದರೆ (ದತ್ತಾಂಶ->ಕೀಲಿ_control_esc) {
                    ಆದರೆ (ದತ್ತಾಂಶ->ಕೀಲಿ_control_esc->func_on_state_change) {
                        ದತ್ತಾಂಶ->ಕೀಲಿ_control_esc->func_on_state_change(ದತ್ತಾಂಶ->ಕೀಲಿ_control_esc);
                    }
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಕೀಲಿ == XK_Return) || (ಕೀಲಿ == XK_KP_Enter)) {
                ಆದರೆ (ದತ್ತಾಂಶ->ಕೀಲಿ_control_enter) {
                    ಆದರೆ (ದತ್ತಾಂಶ->ಕೀಲಿ_control_enter->func_on_state_change) {
                        ದತ್ತಾಂಶ->ಕೀಲಿ_control_enter->func_on_state_change(ದತ್ತಾಂಶ->ಕೀಲಿ_control_enter);
                    }
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕೀಲಿ == XK_Tab || ಕೀಲಿ == XK_ಎಡ || ಕೀಲಿ == XK_ಬಲ) {
                ಆದರೆ (ದತ್ತಾಂಶ->focused_control) {
                    ದತ್ತಾಂಶ->focused_control->selected = false;
                }
                ದತ್ತಾಂಶ->draw = true;
                ಗಾಗಿ (ದತ್ತಾಂಶ->ev_i = 0; ದತ್ತಾಂಶ->ev_i < ದತ್ತಾಂಶ->dyn_controls_sz; ದತ್ತಾಂಶ->ev_i++) {
                    ಆದರೆ (ದತ್ತಾಂಶ->dyn_controls[ದತ್ತಾಂಶ->ev_i] == ದತ್ತಾಂಶ->focused_control) {
                        ಪೂರ್ಣಾಂಕ ಮುಂದಿನ_ಸೂಚ್ಯಂಕ;

                        ಆದರೆ (ಕೀಲಿ == XK_ಎಡ) {
                            ಮುಂದಿನ_ಸೂಚ್ಯಂಕ = ದತ್ತಾಂಶ->ev_i - 1;
                        } ಇಲ್ಲದಿದ್ದರೆ {
                            ಮುಂದಿನ_ಸೂಚ್ಯಂಕ = ದತ್ತಾಂಶ->ev_i + 1;
                        }
                        ಆದರೆ ((ಮುಂದಿನ_ಸೂಚ್ಯಂಕ >= ದತ್ತಾಂಶ->dyn_controls_sz) || (ಮುಂದಿನ_ಸೂಚ್ಯಂಕ < 0)) {
                            ಆದರೆ (ಕೀಲಿ == XK_ಬಲ || ಕೀಲಿ == XK_ಎಡ) {
                                ಮುಂದಿನ_ಸೂಚ್ಯಂಕ = ದತ್ತಾಂಶ->ev_i;
                            } ಇಲ್ಲದಿದ್ದರೆ {
                                ಮುಂದಿನ_ಸೂಚ್ಯಂಕ = 0;
                            }
                        }
                        ದತ್ತಾಂಶ->focused_control = ದತ್ತಾಂಶ->dyn_controls[ಮುಂದಿನ_ಸೂಚ್ಯಂಕ];
                        ದತ್ತಾಂಶ->focused_control->selected = true;
                        ನಿಲ್ಲಿಸು;
                    }
                }
            }
            ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (ದತ್ತಾಂಶ->draw) {
        X11_Toolkit_Draw_ಕಿಟಕಿ(ದತ್ತಾಂಶ);
    }
}

ಶೂನ್ಯ X11_Toolkit_Do_ಕಿಟಕಿ_Event_Loop(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ) {
   ಆಗ (!ದತ್ತಾಂಶ->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(ದತ್ತಾಂಶ->display, &e);
        ಆದರೆ (ದತ್ತಾಂಶ->xsettings) {
            xsettings_client_process_event(ದತ್ತಾಂಶ->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(ದತ್ತಾಂಶ->display, &e, X11Toolkit_EventTest, (XPointer)ದತ್ತಾಂಶ);
        X11_Toolkit_Process_ಕಿಟಕಿ_Events(ದತ್ತಾಂಶ, &e);
    }
}


ಶೂನ್ಯ X11_Toolkit_Resize_ಕಿಟಕಿ(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h) {
    ಆದರೆ (!ದತ್ತಾಂಶ->pixmap) {
        ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ = w;
        ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ = h;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ = SDL_lroundf((w/ದತ್ತಾಂಶ->iscale) * ದತ್ತಾಂಶ->scale);
        ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ = SDL_lroundf((h/ದತ್ತಾಂಶ->iscale) * ದತ್ತಾಂಶ->scale);
        ದತ್ತಾಂಶ->pixmap_ಅಗಲ = w;
        ದತ್ತಾಂಶ->pixmap_ಎತ್ತರ = h;
        X11_XFreePixmap(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable);
        X11_Toolkit_Init_ಕಿಟಕಿ_Pixmap(ದತ್ತಾಂಶ);
    }

    X11_XResize_ಕಿಟಕಿ(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಅಗಲ, ದತ್ತಾಂಶ->ಕಿಟಕಿ_ಎತ್ತರ);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->ಕಿಟಕಿ->display, icon_control->icon_char_font);
    SDL_free(control);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->ಕಿಟಕಿ->iscale;
    control->rect.h -= 2 * control->ಕಿಟಕಿ->iscale;
    X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx, control->rect.x + (2 * control->ಕಿಟಕಿ->iscale), control->rect.y + (2* control->ಕಿಟಕಿ->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    ಆಯ್ಕೆ (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        ಸ್ಥಿತಿ SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx, control->rect.x+(1* control->ಕಿಟಕಿ->iscale), control->rect.y+(1* control->ಕಿಟಕಿ->iscale), control->rect.w-(2* control->ಕಿಟಕಿ->iscale), control->rect.h-(2* control->ಕಿಟಕಿ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, icon_control->xcolor_white.pixel);
                ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx, control->rect.x+(1* control->ಕಿಟಕಿ->iscale), control->rect.y+(1* control->ಕಿಟಕಿ->iscale), control->rect.w-(2* control->ಕಿಟಕಿ->iscale), control->rect.h-(2* control->ಕಿಟಕಿ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, icon_control->xcolor_black.pixel);
                ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx, control->rect.x+(1* control->ಕಿಟಕಿ->iscale), control->rect.y+(1* control->ಕಿಟಕಿ->iscale), control->rect.w-(2* control->ಕಿಟಕಿ->iscale), control->rect.h-(2* control->ಕಿಟಕಿ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, icon_control->xcolor_white.pixel);
                ನಿಲ್ಲಿಸು;
    }
    X11_XSetFont(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    ಆದರೆ (!control->ಕಿಟಕಿ->utf8) {
        X11_XSetFont(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->font_struct->fid);
    }

    control->rect.w += 2 * control->ಕಿಟಕಿ->iscale;
    control->rect.h += 2 * control->ಕಿಟಕಿ->iscale;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *ತಳ_control) {
    SDL_ToolkitIconControlX11 *control;
    ಪೂರ್ಣಾಂಕ icon_char_w;
    ಪೂರ್ಣಾಂಕ icon_wh;

    control = (SDL_ToolkitIconControlX11 *)ತಳ_control;
    X11_Toolkit_Get_ಪಠ್ಯ_ಅಗಲ_ಎತ್ತರ_For_Font(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, ಖಾಲಿ);
    ತಳ_control->rect.w = icon_char_w;
    ತಳ_control->rect.h = control->icon_char_h;
    icon_wh = SDL_max(icon_char_w, control->icon_char_h) + SDL_TOOLKIT_X11_ELEMENT_PADDING * 2 * ತಳ_control->ಕಿಟಕಿ->iscale;
    ತಳ_control->rect.w = icon_wh;
    ತಳ_control->rect.h = icon_wh;
    ತಳ_control->rect.y = 0;
    ತಳ_control->rect.x = 0;
    control->icon_char_y = control->icon_char_a + (ತಳ_control->rect.h - control->icon_char_h)/2;
    control->icon_char_x = (ತಳ_control->rect.w - icon_char_w)/2;
    ತಳ_control->rect.w += 2 * ತಳ_control->ಕಿಟಕಿ->iscale;
    ತಳ_control->rect.h += 2 * ತಳ_control->ಕಿಟಕಿ->iscale;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *ತಳ_control) {
    SDL_ToolkitIconControlX11 *control;
    ಅಕ್ಷರ *font;

    control = (SDL_ToolkitIconControlX11 *)ತಳ_control;
    X11_XFreeFont(ತಳ_control->ಕಿಟಕಿ->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_ಗಾತ್ರ * ತಳ_control->ಕಿಟಕಿ->iscale);
    control->icon_char_font = X11_XLoadQueryFont(ತಳ_control->ಕಿಟಕಿ->display, font);
    SDL_free(font);
    ಆದರೆ (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_ಗಾತ್ರ * ತಳ_control->ಕಿಟಕಿ->iscale);
        control->icon_char_font = X11_XLoadQueryFont(ತಳ_control->ಕಿಟಕಿ->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ, SDL_ಸಂದೇಶ_Box_Flags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *ತಳ_control;
    ಅಕ್ಷರ *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(ಗಾತ್ರ(SDL_ToolkitIconControlX11));
    ತಳ_control = (SDL_ToolkitControlX11 *)control;
    ಆದರೆ (!control) {
        SDL_ಗಣ_Error("Unable to allocate icon control structure");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    /* Fill out struct */
    ತಳ_control->ಕಿಟಕಿ = ಕಿಟಕಿ;
    ತಳ_control->func_draw = X11Toolkit_DrawIconControl;
    ತಳ_control->func_free = X11Toolkit_DestroyIconControl;
    ತಳ_control->func_on_state_change = ಖಾಲಿ;
    ತಳ_control->func_calc_ಗಾತ್ರ = X11Toolkit_CalculateIconControl;
    ತಳ_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    ತಳ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ಸಾಮಾನ್ಯ;
    ತಳ_control->selected = false;
    ತಳ_control->dynamic = false;
    ತಳ_control->is_default_enter = false;
    ತಳ_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_ಗಾತ್ರ * ಕಿಟಕಿ->iscale);
    control->icon_char_font = X11_XLoadQueryFont(ಕಿಟಕಿ->display, font);
    SDL_free(font);
    ಆದರೆ (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_ಗಾತ್ರ * ಕಿಟಕಿ->iscale);
        control->icon_char_font = X11_XLoadQueryFont(ಕಿಟಕಿ->display, font);
        SDL_free(font);
        ಆದರೆ (!control->icon_char_font) {
            SDL_free(control);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
    }

    /* Set colors */
    ಆಯ್ಕೆ (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    ಸ್ಥಿತಿ SDL_MESSAGEBOX_ERROR:
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
        X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &control->xcolor_white);
        X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &control->xcolor_red);
        X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &control->xcolor_red_darker);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_MESSAGEBOX_WARNING:
        control->icon_char = '!';
        control->xcolor_black.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_black.red = 0;
        control->xcolor_black.green = 0;
        control->xcolor_black.blue = 0;
        control->xcolor_yellow.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_yellow.red = 65535;
        control->xcolor_yellow.green = 65535;
        control->xcolor_yellow.blue = 0;
        X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &control->xcolor_black);
        X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &control->xcolor_yellow);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_MESSAGEBOX_INFORMATION:
        control->icon_char = 'i';
        control->xcolor_white.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_white.red = 65535;
        control->xcolor_white.green = 65535;
        control->xcolor_white.blue = 65535;
        control->xcolor_blue.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_blue.red = 0;
        control->xcolor_blue.green = 0;
        control->xcolor_blue.blue = 65535;
        X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &control->xcolor_white);
        X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &control->xcolor_blue);
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        X11_XFreeFont(ಕಿಟಕಿ->display, control->icon_char_font);
        SDL_free(control);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    ಆದರೆ (ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } ಇಲ್ಲದಿದ್ದರೆ {
        control->xcolor_bg_shadow.red = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    ಆದರೆ (ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } ಇಲ್ಲದಿದ್ದರೆ {
        control->xcolor_bg_shadow.green = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    ಆದರೆ (ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } ಇಲ್ಲದಿದ್ದರೆ {
        control->xcolor_bg_shadow.blue = SDL_clamp(ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(ಕಿಟಕಿ->display, ಕಿಟಕಿ->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(ತಳ_control);

    X11_Toolkit_ಕೂಡಿಸು_Control_ಗಮ್ಯ_ಕಿಟಕಿ(ಕಿಟಕಿ, ತಳ_control);
    ಹಿಂತಿರುಗಿ ತಳ_control;
}

bool X11_Toolkit_Notify_Control_ದ_ಗಾತ್ರ_Change(SDL_ToolkitControlX11 *control) {
    ಆದರೆ (control->func_calc_ಗಾತ್ರ) {
        control->func_calc_ಗಾತ್ರ(control);
        ಹಿಂತಿರುಗಿ true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ false;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11_Toolkit_Get_ಪಠ್ಯ_Elements_Rect(button_control->ಪಠ್ಯ, &button_control->ಪಠ್ಯ_rect);
    ಆದರೆ (control->do_ಗಾತ್ರ) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->ಕಿಟಕಿ->iscale + button_control->ಪಠ್ಯ_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->ಕಿಟಕಿ->iscale + button_control->ಪಠ್ಯ_rect.h;
    }
    button_control->ಪಠ್ಯ_rect.x = (control->rect.w - button_control->ಪಠ್ಯ_rect.w)/2;
    button_control->ಪಠ್ಯ_rect.y = (control->rect.h - button_control->ಪಠ್ಯ_rect.h)/2;
}


ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_ಪಠ್ಯ].pixel);
    /* Draw bevel */
    ಆದರೆ (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
            X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor_bevel_d.pixel);
            X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

            X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor_bevel_l2.pixel);
            X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - (1* control->ಕಿಟಕಿ->iscale), control->rect.h - (1* control->ಕಿಟಕಿ->iscale));

            X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor_bevel_l1.pixel);
            X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x + 1 * control->ಕಿಟಕಿ->iscale, control->rect.y + 1 * control->ಕಿಟಕಿ->iscale,
                                   control->rect.w - 3 * control->ಕಿಟಕಿ->iscale, control->rect.h - 2 * control->ಕಿಟಕಿ->iscale);

            X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
            X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                               control->rect.x + 1 * control->ಕಿಟಕಿ->iscale, control->rect.y + 1 * control->ಕಿಟಕಿ->iscale,
                               control->rect.w - 3 * control->ಕಿಟಕಿ->iscale, control->rect.h - 3 * control->ಕಿಟಕಿ->iscale);

            X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor_pressed.pixel);
            X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                               control->rect.x + 2 * control->ಕಿಟಕಿ->iscale, control->rect.y + 2 * control->ಕಿಟಕಿ->iscale,
                               control->rect.w - 4 * control->ಕಿಟಕಿ->iscale, control->rect.h - 4 * control->ಕಿಟಕಿ->iscale);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ (control->selected) {
                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x + 1 * control->ಕಿಟಕಿ->iscale, control->rect.y + 1 * control->ಕಿಟಕಿ->iscale,
                                   control->rect.w - 3 * control->ಕಿಟಕಿ->iscale, control->rect.h - 3 * control->ಕಿಟಕಿ->iscale);

                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x + 2 * control->ಕಿಟಕಿ->iscale, control->rect.y + 2 * control->ಕಿಟಕಿ->iscale,
                                   control->rect.w - 4 * control->ಕಿಟಕಿ->iscale, control->rect.h - 4 * control->ಕಿಟಕಿ->iscale);

                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x + 2 * control->ಕಿಟಕಿ->iscale, control->rect.y + 2 * control->ಕಿಟಕಿ->iscale,
                                   control->rect.w - 5 * control->ಕಿಟಕಿ->iscale, control->rect.h - 5 * control->ಕಿಟಕಿ->iscale);

                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x + 3 * control->ಕಿಟಕಿ->iscale, control->rect.y + 3 * control->ಕಿಟಕಿ->iscale,
                                   control->rect.w - 6 * control->ಕಿಟಕಿ->iscale, control->rect.h - 6 * control->ಕಿಟಕಿ->iscale);
            } ಇಲ್ಲದಿದ್ದರೆ {
                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - 1 * control->ಕಿಟಕಿ->iscale, control->rect.h - 1 * control->ಕಿಟಕಿ->iscale);

                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x + 1 * control->ಕಿಟಕಿ->iscale, control->rect.y + 1 * control->ಕಿಟಕಿ->iscale,
                                   control->rect.w - 2 * control->ಕಿಟಕಿ->iscale, control->rect.h - 2 * control->ಕಿಟಕಿ->iscale);

                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x + 1 * control->ಕಿಟಕಿ->iscale, control->rect.y + 1 * control->ಕಿಟಕಿ->iscale,
                                   control->rect.w - 3 * control->ಕಿಟಕಿ->iscale, control->rect.h - 3 * control->ಕಿಟಕಿ->iscale);

                X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->drawable, control->ಕಿಟಕಿ->ctx,
                                   control->rect.x + 2 * control->ಕಿಟಕಿ->iscale, control->rect.y + 2 * control->ಕಿಟಕಿ->iscale,
                                   control->rect.w - 4 * control->ಕಿಟಕಿ->iscale, control->rect.h - 4 * control->ಕಿಟಕಿ->iscale);
            }
        }

    X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_ಪಠ್ಯ].pixel);
    X11_Toolkit_Draw_ಪಠ್ಯ_Elements(control->ಕಿಟಕಿ, button_control->ಪಠ್ಯ, control->rect.x + button_control->ಪಠ್ಯ_rect.x, control->rect.y + button_control->ಪಠ್ಯ_rect.y);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    ಆದರೆ (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_ದತ್ತಾಂಶ);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_Toolkit_Free_ಪಠ್ಯ_Elements(button_control->ಪಠ್ಯ);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *ತಳ_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(ಗಾತ್ರ(SDL_ToolkitButtonControlX11));
    ತಳ_control = (SDL_ToolkitControlX11 *)control;
    ಆದರೆ (!control) {
        SDL_ಗಣ_Error("Unable to allocate button control structure");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ತಳ_control->ಕಿಟಕಿ = ಕಿಟಕಿ;
    ತಳ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ಸಾಮಾನ್ಯ;
    ತಳ_control->func_calc_ಗಾತ್ರ = X11Toolkit_CalculateButtonControl;
    ತಳ_control->func_draw = X11Toolkit_DrawButtonControl;
    ತಳ_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    ತಳ_control->func_free = X11Toolkit_DestroyButtonControl;
    ತಳ_control->func_on_scale_change = ಖಾಲಿ;
    ತಳ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ಸಾಮಾನ್ಯ;
    ತಳ_control->selected = false;
    ತಳ_control->dynamic = true;
    ತಳ_control->is_default_enter = false;
    ತಳ_control->is_default_esc = false;
    ಆದರೆ (ದತ್ತಾಂಶ->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        ತಳ_control->is_default_esc = true;
    }
    ಆದರೆ (ದತ್ತಾಂಶ->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        ತಳ_control->is_default_enter = true;
        ತಳ_control->selected = true;
    }
    control->cb = ಖಾಲಿ;
    control->ದತ್ತಾಂಶ = ದತ್ತಾಂಶ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
    control->ಪಠ್ಯ = X11_Toolkit_Make_ಪಠ್ಯ_Elements(ತಳ_control->ಕಿಟಕಿ, (ಅಕ್ಷರ *)control->ದತ್ತಾಂಶ->ಪಠ್ಯ, SDL_strlen(control->ದತ್ತಾಂಶ->ಪಠ್ಯ), ಖಾಲಿ);
#ಇಲ್ಲದಿದ್ದರೆ 
    control->ಪಠ್ಯ = X11_Toolkit_Make_ಪಠ್ಯ_Elements(ತಳ_control->ಕಿಟಕಿ, (ಅಕ್ಷರ *)control->ದತ್ತಾಂಶ->ಪಠ್ಯ, SDL_strlen(control->ದತ್ತಾಂಶ->ಪಠ್ಯ));
#ಆದರೆ_ಅಂತ್ಯ
    X11_Toolkit_Shape_ಪಠ್ಯ_Elements(ತಳ_control->ಕಿಟಕಿ, control->ಪಠ್ಯ);
    
    ತಳ_control->do_ಗಾತ್ರ = true;
    X11Toolkit_CalculateButtonControl(ತಳ_control);
    ತಳ_control->do_ಗಾತ್ರ = false;

    X11_Toolkit_ಕೂಡಿಸು_Control_ಗಮ್ಯ_ಕಿಟಕಿ(ಕಿಟಕಿ, ತಳ_control);
    ಹಿಂತಿರುಗಿ ತಳ_control;
}

ಶೂನ್ಯ X11_Toolkit_ರಿಜಿಸ್ಟರ್_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, ಶೂನ್ಯ *ದತ್ತಾಂಶ, ಶೂನ್ಯ (*cb)(ರಚನೆ SDL_ToolkitControlX11 *, ಶೂನ್ಯ *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_ದತ್ತಾಂಶ = ದತ್ತಾಂಶ;
    button_control->cb = cb;
}

ಸ್ಥಿರಾಂಕ SDL_ಸಂದೇಶ_Box_Button_ದತ್ತಾಂಶ *X11_Toolkit_Get_Button_Control_ದತ್ತಾಂಶ(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    ಹಿಂತಿರುಗಿ button_control->ದತ್ತಾಂಶ;
}

ಶೂನ್ಯ X11_Toolkit_Destroy_ಕಿಟಕಿ(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ) {
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ;
    }

#ಆದರೆ SDL_GRAB
    ಆದರೆ (ದತ್ತಾಂಶ->ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_MENU || ದತ್ತಾಂಶ->ಬಹುಲಕ== SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_TOOLTIP) {
        X11_XUngrab_ಸೂಚಕ(ದತ್ತಾಂಶ->display, Current_ಸಮಯ);
        X11_XUngrabKeyboard(ದತ್ತಾಂಶ->display, Current_ಸಮಯ);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಗಾಗಿ (i = 0; i < ದತ್ತಾಂಶ->controls_sz; i++) {
        ಆದರೆ (ದತ್ತಾಂಶ->controls[i]->func_free) {
            ದತ್ತಾಂಶ->controls[i]->func_free(ದತ್ತಾಂಶ->controls[i]);
        }
    }
    SDL_free(ದತ್ತಾಂಶ->controls);
    SDL_free(ದತ್ತಾಂಶ->dyn_controls);

    ಆದರೆ (ದತ್ತಾಂಶ->popup_windows) {
        SDL_ListClear(&ದತ್ತಾಂಶ->popup_windows);
    }

    ಆದರೆ (ದತ್ತಾಂಶ->pixmap) {
        X11_XFreePixmap(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->drawable);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
    ಆದರೆ (ದತ್ತಾಂಶ->pixmap && ದತ್ತಾಂಶ->shm) {
        X11_XShmDetach(ದತ್ತಾಂಶ->display, &ದತ್ತಾಂಶ->shm_info);
        ಆದರೆ (!ದತ್ತಾಂಶ->shm_pixmap) {
            XDestroyImage(ದತ್ತಾಂಶ->image);
        }
        shmdt(ದತ್ತಾಂಶ->shm_info.shmaddr);
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X_HAVE_UTF8_STRING
    ಆದರೆ (ದತ್ತಾಂಶ->font_ಗಣ) {
        X11_XFree_Font_ಗಣ(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->font_ಗಣ);
        ದತ್ತಾಂಶ->font_ಗಣ = ಖಾಲಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ದತ್ತಾಂಶ->font_struct) {
        X11_XFreeFont(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->font_struct);
        ದತ್ತಾಂಶ->font_struct = ಖಾಲಿ;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XDBE
    ಆದರೆ (SDL_X11_HAVE_XDBE && ದತ್ತಾಂಶ->xdbe && !ದತ್ತಾಂಶ->pixmap) {
        X11_Xdbe_Deallocate_ಹಿಂಭಾಗ_ಬಫರ್_Name(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->buf);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (ದತ್ತಾಂಶ->xsettings) {
        xsettings_client_destroy(ದತ್ತಾಂಶ->xsettings);
    }

    X11_XFreeGC(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->ctx);

    ಆದರೆ (ದತ್ತಾಂಶ->display) {
        ಆದರೆ (ದತ್ತಾಂಶ->ಕಿಟಕಿ != None) {
            X11_XWithdraw_ಕಿಟಕಿ(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->ಕಿಟಕಿ, ದತ್ತಾಂಶ->screen);
            X11_XDestroy_ಕಿಟಕಿ(ದತ್ತಾಂಶ->display, ದತ್ತಾಂಶ->ಕಿಟಕಿ);
            ದತ್ತಾಂಶ->ಕಿಟಕಿ = None;
        }

        ಆದರೆ (ದತ್ತಾಂಶ->display_close) {
            X11_XCloseDisplay(ದತ್ತಾಂಶ->display);
        }
        ದತ್ತಾಂಶ->display = ಖಾಲಿ;
    }

#ಆದರೆ SDL_ಗಣ_LOCALE
    ಆದರೆ (ದತ್ತಾಂಶ->origlocale && (ದತ್ತಾಂಶ->ಬಹುಲಕ == SDL_TOOLKIT_ಕಿಟಕಿ_ಬಹುಲಕ_X11_DIALOG)) {
        (ಶೂನ್ಯ)setlocale(LC_ALL, ದತ್ತಾಂಶ->origlocale);
        SDL_free(ದತ್ತಾಂಶ->origlocale);
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(ದತ್ತಾಂಶ->fribidi);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(ದತ್ತಾಂಶ->th);
#ಆದರೆ_ಅಂತ್ಯ

    SDL_free(ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ X11_Toolkit_ಎಣಿಕೆ_ಸಾಲುಗಳು_ದ_ಪಠ್ಯ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪಠ್ಯ)
{
    ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;
    ಆಗ (ಪಠ್ಯ && *ಪಠ್ಯ) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *lf = SDL_strchr(ಪಠ್ಯ, '\n');
        ಫಲಿತಾಂಶ++; // even without an endline, this counts as a line.
        ಪಠ್ಯ = lf ? lf + 1 : ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    ಪೂರ್ಣಾಂಕ i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->ಕಿಟಕಿ->display, control->ಕಿಟಕಿ->ctx, control->ಕಿಟಕಿ->xcolor[SDL_MESSAGEBOX_COLOR_ಪಠ್ಯ].pixel);
    ಗಾಗಿ (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Draw_ಪಠ್ಯ_Elements(control->ಕಿಟಕಿ, label_control->ಸಾಲುಗಳು[i].ಪಠ್ಯ, control->rect.x + label_control->ಸಾಲುಗಳು[i].rect.x, control->rect.y + label_control->ಸಾಲುಗಳು[i].rect.y);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    ಪೂರ್ಣಾಂಕ i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    ಗಾಗಿ (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Free_ಪಠ್ಯ_Elements(label_control->ಸಾಲುಗಳು[i].ಪಠ್ಯ);
    }
    SDL_free(label_control->ಸಾಲುಗಳು);
    SDL_free(label_control);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *ತಳ_control) {
    SDL_ToolkitLabelControlX11 *control;
    ಪೂರ್ಣಾಂಕ i;

    control = (SDL_ToolkitLabelControlX11 *)ತಳ_control;
    
    ಆದರೆ (ತಳ_control->do_ಗಾತ್ರ) {
        ತಳ_control->rect.w = 0;
        ತಳ_control->rect.h = 0;
    }
    
    ಗಾಗಿ (i = 0; i < control->sz; i++) {
        ಪೂರ್ಣಾಂಕ font_h;
        
        font_h = X11_Toolkit_Get_ಪಠ್ಯ_Elements_Rect(control->ಸಾಲುಗಳು[i].ಪಠ್ಯ, &control->ಸಾಲುಗಳು[i].rect);
        
        ಆದರೆ (ತಳ_control->do_ಗಾತ್ರ) {
            ತಳ_control->rect.w = SDL_max(ತಳ_control->rect.w, control->ಸಾಲುಗಳು[i].rect.w);
        }
        
        ಆದರೆ (i > 0) {
            control->ಸಾಲುಗಳು[i].rect.y = font_h + control->ಸಾಲುಗಳು[i - 1].rect.y;
        } ಇಲ್ಲದಿದ್ದರೆ {
            control->ಸಾಲುಗಳು[i].rect.y = 0;
        }
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
    ಆದರೆ (ತಳ_control->ಕಿಟಕಿ->fribidi) {
        FriBidiParType ಮೊದಲ_ndn_dir;
        ಪೂರ್ಣಾಂಕ ಕೊನೆಯ_ndn;
    
        ಮೊದಲ_ndn_dir = FRIBIDI_PAR_LTR;
        ಗಾಗಿ (i = 0; i < control->sz; i++) {
            ಆದರೆ (control->ಸಾಲುಗಳು[i].par != FRIBIDI_PAR_ON) {
                ಮೊದಲ_ndn_dir = control->ಸಾಲುಗಳು[i].par;
            }
        }

        ಕೊನೆಯ_ndn = -1;
        ಗಾಗಿ (i = 0; i < control->sz; i++) {
            ಆಯ್ಕೆ (control->ಸಾಲುಗಳು[i].par) {
                ಸ್ಥಿತಿ FRIBIDI_PAR_LTR:
                    control->ಸಾಲುಗಳು[i].rect.x = 0;
                    ಕೊನೆಯ_ndn = i;
                    ನಿಲ್ಲಿಸು;
                ಸ್ಥಿತಿ FRIBIDI_PAR_RTL:
                    control->ಸಾಲುಗಳು[i].rect.x = ತಳ_control->rect.w - control->ಸಾಲುಗಳು[i].rect.w;
                    ಕೊನೆಯ_ndn = i;
                    ನಿಲ್ಲಿಸು;
                ಪೂರ್ವನಿಯೋಜಿತ:
                    ಆದರೆ (ಕೊನೆಯ_ndn != -1) {
                        ಆದರೆ (control->ಸಾಲುಗಳು[ಕೊನೆಯ_ndn].par == FRIBIDI_PAR_RTL) {
                            control->ಸಾಲುಗಳು[i].rect.x = ತಳ_control->rect.w - control->ಸಾಲುಗಳು[i].rect.w;
                        } ಇಲ್ಲದಿದ್ದರೆ {
                            control->ಸಾಲುಗಳು[i].rect.x = 0;
                        }
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        ಆದರೆ (ಮೊದಲ_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->ಸಾಲುಗಳು[i].rect.x = ತಳ_control->rect.w - control->ಸಾಲುಗಳು[i].rect.w;
                        } ಇಲ್ಲದಿದ್ದರೆ {
                            control->ಸಾಲುಗಳು[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#ಆದರೆ_ಅಂತ್ಯ
    
    ಆದರೆ (ತಳ_control->do_ಗಾತ್ರ && control->sz) {
        ತಳ_control->rect.h = control->ಸಾಲುಗಳು[control->sz - 1].rect.y + control->ಸಾಲುಗಳು[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_ಕಿಟಕಿ_X11 *ಕಿಟಕಿ, ಅಕ್ಷರ *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *ತಳ_control;
    ಪೂರ್ಣಾಂಕ i;
    
    ಆದರೆ (!utf8) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
 
    ಆದರೆ (!SDL_strcmp(utf8, "")) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(ಗಾತ್ರ(SDL_ToolkitLabelControlX11));
    ತಳ_control = (SDL_ToolkitControlX11 *)control;
    ಆದರೆ (!control) {
        SDL_ಗಣ_Error("Unable to allocate label control structure");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ತಳ_control->ಕಿಟಕಿ = ಕಿಟಕಿ;
    ತಳ_control->func_draw = X11Toolkit_DrawLabelControl;
    ತಳ_control->func_on_state_change = ಖಾಲಿ;
    ತಳ_control->func_calc_ಗಾತ್ರ = X11Toolkit_CalculateLabelControl;
    ತಳ_control->func_free  = X11Toolkit_DestroyLabelControl;
    ತಳ_control->func_on_scale_change = ಖಾಲಿ;
    ತಳ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ಸಾಮಾನ್ಯ;
    ತಳ_control->selected = false;
    ತಳ_control->dynamic = false;
    ತಳ_control->rect.w = 0;
    ತಳ_control->rect.h = 0;
    ತಳ_control->is_default_enter = false;
    ತಳ_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_ಎಣಿಕೆ_ಸಾಲುಗಳು_ದ_ಪಠ್ಯ(utf8);
    control->ಸಾಲುಗಳು = SDL_calloc(control->sz, ಗಾತ್ರ(SDL_Toolkit_Label_Control_ಸಾಲು_X11));
    ಗಾಗಿ (i = 0; i < control->sz; i++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *lf = SDL_strchr(utf8, '\n');
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ = lf ? (lf - utf8) : SDL_strlen(utf8);
        ಪೂರ್ಣಾಂಕ sz;
        
        sz = ಉದ್ದಳತೆ;
        ಆದರೆ (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_FRIBIDI_H
        control->ಸಾಲುಗಳು[i].ಪಠ್ಯ = X11_Toolkit_Make_ಪಠ್ಯ_Elements(ತಳ_control->ಕಿಟಕಿ, (ಅಕ್ಷರ *)utf8, sz, &control->ಸಾಲುಗಳು[i].par);
#ಇಲ್ಲದಿದ್ದರೆ 
        control->ಸಾಲುಗಳು[i].ಪಠ್ಯ = X11_Toolkit_Make_ಪಠ್ಯ_Elements(ತಳ_control->ಕಿಟಕಿ, (ಅಕ್ಷರ *)utf8, sz);
#ಆದರೆ_ಅಂತ್ಯ
        X11_Toolkit_Shape_ಪಠ್ಯ_Elements(ತಳ_control->ಕಿಟಕಿ, control->ಸಾಲುಗಳು[i].ಪಠ್ಯ);

        utf8 += ಉದ್ದಳತೆ + 1;
        ಆದರೆ (!lf) {
            ನಿಲ್ಲಿಸು;
        }
    }

    ತಳ_control->do_ಗಾತ್ರ = true;
    X11Toolkit_CalculateLabelControl(ತಳ_control);
    ತಳ_control->do_ಗಾತ್ರ = false;
    X11_Toolkit_ಕೂಡಿಸು_Control_ಗಮ್ಯ_ಕಿಟಕಿ(ಕಿಟಕಿ, ತಳ_control);

    ಹಿಂತಿರುಗಿ ತಳ_control;
}

ಪೂರ್ಣಾಂಕ X11_Toolkit_Get_Label_Control_ಮೊದಲ_ಸಾಲು_ಎತ್ತರ(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    ಹಿಂತಿರುಗಿ label_control->ಸಾಲುಗಳು[0].rect.h;
}

ಶೂನ್ಯ X11_Toolkit_Signal_ಕಿಟಕಿ_Close(SDL_Toolkit_ಕಿಟಕಿ_X11 *ದತ್ತಾಂಶ) {
    ದತ್ತಾಂಶ->close = true;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
