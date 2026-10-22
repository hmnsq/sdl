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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_list.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/linux/SDL_system_theme.h"
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/unix/SDL_fribidi.h"
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11dyn.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11toolkit.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11settings.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11modes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xsettings-client.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/keysym.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_ਸੈੱਟ_LOCALE 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_GRAB 1

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ SDL_Toolkit_ਪਾਠ_Type_X11
{
    SDL_TOOLKIT_ਪਾਠ_TYPE_X11_GENERIC,
    SDL_TOOLKIT_ਪਾਠ_TYPE_X11_THAI
} SDL_Toolkit_ਪਾਠ_Type_X11;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBTHAI_H
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_ToolkitThaiOverlayX11
{
    bool ਸਿਖਰ;
    ਅੱਖਰ *str;
    size_t sz;
    SDL_Rect rect;
} SDL_ToolkitThaiOverlayX11;
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_Toolkit_ਪਾਠ_Element_X11
{
    SDL_Toolkit_ਪਾਠ_Type_X11 type;
    ਅੱਖਰ *str;
    size_t sz;
    SDL_Rect rect;
    ਪੂਰਨ font_h;
    ਖਾਲੀ (*str_free)(ਖਾਲੀ *);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBTHAI_H
    SDL_List_ਗੰਢ *thai_overlays;
#ਜੇ_ਅੰਤ
} SDL_Toolkit_ਪਾਠ_Element_X11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_ToolkitIconControlX11
{
    SDL_ToolkitControlX11 ਮਾਪਾ;

    /* Icon type */
    SDL_ਸੁਨੇਹਾ_Box_Flags flags;
    ਅੱਖਰ icon_char;

    /* Font */
    XFontStruct *icon_char_font;
    ਪੂਰਨ icon_char_x;
    ਪੂਰਨ icon_char_y;
    ਪੂਰਨ icon_char_a;
    ਪੂਰਨ icon_char_h;

    /* Colors */
    XColor xcolor_black;
    XColor xcolor_red;
    XColor xcolor_red_darker;
    XColor xcolor_white;
    XColor xcolor_yellow;
    XColor xcolor_blue;
    XColor xcolor_bg_shadow;
} SDL_ToolkitIconControlX11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_ToolkitButtonControlX11
{
    SDL_ToolkitControlX11 ਮਾਪਾ;

    /*ਅੰਕੜੇ*/
    ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ *ਅੰਕੜੇ;

    /*ਪਾਠ*/
    SDL_List_ਗੰਢ *ਪਾਠ;
    SDL_Rect ਪਾਠ_rect;
    
    /* Callback */
    ਖਾਲੀ *cb_ਅੰਕੜੇ;
    ਖਾਲੀ (*cb)(ਬਣਤਰ SDL_ToolkitControlX11 *, ਖਾਲੀ *);
} SDL_ToolkitButtonControlX11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_Toolkit_Label_Control_ਸਤਰ_X11
{
    SDL_List_ਗੰਢ *ਪਾਠ;
    SDL_Rect rect;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
    FriBidiParType par;
#ਜੇ_ਅੰਤ
} SDL_Toolkit_Label_Control_ਸਤਰ_X11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_ToolkitLabelControlX11
{
    SDL_ToolkitControlX11 ਮਾਪਾ;

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
    SDL_Toolkit_Label_Control_ਸਤਰ_X11 *ਸਤਰਾਂ;
    size_t sz;
} SDL_ToolkitLabelControlX11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_ToolkitMenuBarControlX11
{
    SDL_ToolkitControlX11 ਮਾਪਾ;

    SDL_List_ਗੰਢ *menu_ਚੀਜ਼ਾਂ;
} SDL_ToolkitMenuBarControlX11;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SDL_ToolkitMenuControlX11
{
    SDL_ToolkitControlX11 ਮਾਪਾ;

    SDL_List_ਗੰਢ *menu_ਚੀਜ਼ਾਂ;
    XColor xcolor_check_bg;
} SDL_ToolkitMenuControlX11;

/* Font for icon control */
ਸਥਿਰ ਅਚਲ ਅੱਖਰ *g_IconFont = "-*-*-bold-r-normal-*-%d-*-*-*-*-*-iso8859-1[33 88 105]";
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ G_ICONFONT_ਮਾਪ 22

/* General UI font */
ਸਥਿਰ ਅਚਲ ਅੱਖਰ g_ToolkitFontLatin1[] =
    "-*-*-medium-r-normal--0-%d-*-*-p-0-iso8859-1";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ g_ToolkitFontLatin1Fallback[] =
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1";

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *g_ToolkitFont[] = {
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso10646-1,*",  // explicitly unicode (iso10646-1)
    "-misc-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // misc unicode (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso10646-1,*",  // just give me anything Unicode.
    "-*-*-medium-r-normal--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-*-*-medium-r-*--*-%d-*-*-*-*-iso8859-1,*",  // explicitly latin1, in case low-ASCII works out.
    "-misc-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // misc latin1 (fix for some systems)
    "-*-*-*-*-*--*-*-*-*-*-*-iso8859-1,*",  // just give me anything latin1.
    ਨਿਰਾ
};
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ G_TOOLKITFONT_ਮਾਪ 140

ਸਥਿਰ ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color g_default_colors[SDL_MESSAGEBOX_COLOR_ਗਿਣਤੀ] = {
    { 191, 184, 191 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 127, 120, 127 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 191, 184, 191 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 235, 235, 235 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
ਸਥਿਰ ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color g_default_colors_dark[SDL_MESSAGEBOX_COLOR_ਗਿਣਤੀ] = {
    { 20, 20, 20 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 192, 192, 192 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 12, 12, 12 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 20, 20, 20 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 36, 36, 36 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

#ਜੇ 0
ਸਥਿਰ ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color g_default_colors_dark_ਉੱਚਾ_contrast[SDL_MESSAGEBOX_COLOR_ਗਿਣਤੀ] = {
    { 0, 0, 0 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 255, 255, 255 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 20, 235, 255 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 0, 0, 0 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 125, 5, 125 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

ਸਥਿਰ ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color g_default_colors_light_ਉੱਚਾ_contrast[SDL_MESSAGEBOX_COLOR_ਗਿਣਤੀ] = {
    { 255, 255, 255 },    // SDL_MESSAGEBOX_COLOR_BACKGROUND,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_TEXT,
    { 0, 0, 0 }, // SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
    { 255, 255, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
    { 20, 230, 255 },  // SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ g_shm_error;
ਸਥਿਰ ਪੂਰਨ (*g_old_error_handler)(Display *, XErrorEvent *) = ਨਿਰਾ;

ਸਥਿਰ ਪੂਰਨ X11_Toolkit_Shared_ਸਮ੍ਰਿਤੀ_Error_Handler(Display *d, XErrorEvent *e)
{
    ਜੇ (e->error_ਕੋਡ == BadAccess || e->error_ਕੋਡ == BadRequest) {
        g_shm_error = True;
        ਵਾਪਸ 0;
    }
    ਵਾਪਸ g_old_error_handler(d, e);
}

ਸਥਿਰ ਖਾਲੀ X11_Toolkit_Init_ਖਿੜਕੀ_Pixmap(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ) {
    ਜੇ (ਅੰਕੜੇ->pixmap) {
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
        ਜੇ (!ਅੰਕੜੇ->shm_pixmap) {
            ਅੰਕੜੇ->drawable = X11_XCreatePixmap(ਅੰਕੜੇ->display, ਅੰਕੜੇ->ਖਿੜਕੀ, ਅੰਕੜੇ->pixmap_ਚੌੜਾਈ, ਅੰਕੜੇ->pixmap_ਉਚਾਈ, ਅੰਕੜੇ->ਡੂੰਘਾਈ_2);
        }
#ਨਹੀਂਤਾਂ
        ਅੰਕੜੇ->drawable = X11_XCreatePixmap(ਅੰਕੜੇ->display, ਅੰਕੜੇ->ਖਿੜਕੀ, ਅੰਕੜੇ->pixmap_ਚੌੜਾਈ, ਅੰਕੜੇ->pixmap_ਉਚਾਈ, ਅੰਕੜੇ->ਡੂੰਘਾਈ_2);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
        ਜੇ (ਅੰਕੜੇ->shm) {
            ਅੰਕੜੇ->image = X11_XShmCreateImage(ਅੰਕੜੇ->display, ਅੰਕੜੇ->visual, ਅੰਕੜੇ->ਡੂੰਘਾਈ_2, ZPixmap, ਨਿਰਾ, &ਅੰਕੜੇ->shm_info, ਅੰਕੜੇ->pixmap_ਚੌੜਾਈ, ਅੰਕੜੇ->pixmap_ਉਚਾਈ);
            ਜੇ (ਅੰਕੜੇ->image) {
                ਅੰਕੜੇ->shm_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਸਤਰ = ਅੰਕੜੇ->image->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਸਤਰ;

                ਅੰਕੜੇ->shm_info.shmid = shmget(IPC_ਨਿੱਜੀ, ਅੰਕੜੇ->image->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਸਤਰ * ਅੰਕੜੇ->image->ਉਚਾਈ, IPC_CREAT | 0777);
                ਜੇ (ਅੰਕੜੇ->shm_info.shmid < 0) {
                    XDestroyImage(ਅੰਕੜੇ->image);
                    ਅੰਕੜੇ->image = ਨਿਰਾ;
                    ਅੰਕੜੇ->shm = false;
                    ਵਾਪਸ;
                }

                ਅੰਕੜੇ->shm_info.readOnly = False;
                ਅੰਕੜੇ->shm_info.shmaddr = ਅੰਕੜੇ->image->ਅੰਕੜੇ = (ਅੱਖਰ *)shmat(ਅੰਕੜੇ->shm_info.shmid, ਨਿਰਾ, 0);
                ਜੇ (((ਨਿਸ਼ਾਨੀਵਾਲਾ ਅੱਖਰ *)ਅੰਕੜੇ->shm_info.shmaddr) == (ਨਿਸ਼ਾਨੀਵਾਲਾ ਅੱਖਰ *)-1) {
                    XDestroyImage(ਅੰਕੜੇ->image);
                    ਅੰਕੜੇ->shm = false;
                    ਅੰਕੜੇ->image = ਨਿਰਾ;
                    ਵਾਪਸ;
                }

                g_shm_error = False;
                g_old_error_handler = X11_XSetErrorHandler(X11_Toolkit_Shared_ਸਮ੍ਰਿਤੀ_Error_Handler);
                X11_XShmAttach(ਅੰਕੜੇ->display, &ਅੰਕੜੇ->shm_info);
                X11_XSync(ਅੰਕੜੇ->display, False);
                X11_XSetErrorHandler(g_old_error_handler);
                ਜੇ (g_shm_error) {
                    XDestroyImage(ਅੰਕੜੇ->image);
                    shmdt(ਅੰਕੜੇ->shm_info.shmaddr);
                    shmctl(ਅੰਕੜੇ->shm_info.shmid, IPC_RMID, ਨਿਰਾ);
                    ਅੰਕੜੇ->image = ਨਿਰਾ;
                    ਅੰਕੜੇ->shm = false;
                    ਵਾਪਸ;
                }

                ਜੇ (ਅੰਕੜੇ->shm_pixmap) {
                    ਅੰਕੜੇ->drawable = X11_XShmCreatePixmap(ਅੰਕੜੇ->display, ਅੰਕੜੇ->ਖਿੜਕੀ, ਅੰਕੜੇ->shm_info.shmaddr, &ਅੰਕੜੇ->shm_info, ਅੰਕੜੇ->pixmap_ਚੌੜਾਈ, ਅੰਕੜੇ->pixmap_ਉਚਾਈ, ਅੰਕੜੇ->ਡੂੰਘਾਈ_2);
                    ਜੇ (ਅੰਕੜੇ->drawable == None) {
                        ਅੰਕੜੇ->shm_pixmap = False;
                    } ਨਹੀਂਤਾਂ {
                        XDestroyImage(ਅੰਕੜੇ->image);
                        ਅੰਕੜੇ->image = ਨਿਰਾ;
                    }
                }

                shmctl(ਅੰਕੜੇ->shm_info.shmid, IPC_RMID, ਨਿਰਾ);
            } ਨਹੀਂਤਾਂ {
                ਅੰਕੜੇ->shm = false;
            }
        }
#ਜੇ_ਅੰਤ
    }
}

ਸਥਿਰ ਖਾਲੀ X11_Toolkit_Init_ਖਿੜਕੀ_Fonts(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ)
{    
    ਖਿੜਕੀ->thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
    ਖਿੜਕੀ->thai_font = SDL_TOOLKIT_THAI_FONT_X11_CELL;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    ਖਿੜਕੀ->utf8 = true;
    ਖਿੜਕੀ->font_ਸੈੱਟ = ਨਿਰਾ;
    ਜੇ (SDL_X11_HAVE_UTF8) {
        ਅੱਖਰ **missing = ਨਿਰਾ;
        ਪੂਰਨ ਅੰਕ_missing = 0;
        ਪੂਰਨ i_font;
        ਖਿੜਕੀ->font_struct = ਨਿਰਾ;
        ਲਈ (i_font = 0; g_ToolkitFont[i_font]; ++i_font) {
            ਅੱਖਰ *font;

            ਜੇ (SDL_strstr(g_ToolkitFont[i_font], "%d")) {
                try_ਲੱਦੋ_font:
                SDL_asprintf(&font, g_ToolkitFont[i_font], G_TOOLKITFONT_ਮਾਪ * ਖਿੜਕੀ->iscale);
                ਖਿੜਕੀ->font_ਸੈੱਟ = X11_XCreate_Font_ਸੈੱਟ(ਖਿੜਕੀ->display, font, &missing, &ਅੰਕ_missing, ਨਿਰਾ);
                SDL_free(font);

                ਜੇ (!ਖਿੜਕੀ->font_ਸੈੱਟ) {
                    ਜੇ (ਖਿੜਕੀ->scale != 0 && ਖਿੜਕੀ->iscale > 0) {
                        ਖਿੜਕੀ->iscale = (ਪੂਰਨ)SDL_ceilf(ਖਿੜਕੀ->scale);
                        ਖਿੜਕੀ->scale = 0;
                    } ਨਹੀਂਤਾਂ {
                        ਖਿੜਕੀ->iscale--;
                    }
                    ਜਾਓ try_ਲੱਦੋ_font;
                }
            } ਨਹੀਂਤਾਂ {
                ਖਿੜਕੀ->font_ਸੈੱਟ = X11_XCreate_Font_ਸੈੱਟ(ਖਿੜਕੀ->display, g_ToolkitFont[i_font], &missing, &ਅੰਕ_missing, ਨਿਰਾ);
            }

            ਜੇ (missing) {
                X11_XFreeStringList(missing);
            }

            ਜੇ (ਖਿੜਕੀ->font_ਸੈੱਟ) {
                ਰੋਕੋ;
            }
        }

        ਜੇ (!ਖਿੜਕੀ->font_ਸੈੱਟ) {
            ਜਾਓ ਲੱਦੋ_font_traditional;
        } ਨਹੀਂਤਾਂ {
            XFontStruct **font_structs;
            ਅੱਖਰ **font_ਨਾਂ;
            ਪੂਰਨ font_sz;
            ਪੂਰਨ i;
            
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
            ਖਿੜਕੀ->do_shaping = !X11_XContextDependentDrawing(ਖਿੜਕੀ->font_ਸੈੱਟ);
#ਜੇ_ਅੰਤ
            /* TODO: What to do the XFontSet happens to have more than one Thai font? */
            font_sz = X11_XFonts_ਦਾ_Font_ਸੈੱਟ(ਖਿੜਕੀ->font_ਸੈੱਟ, &font_structs, &font_ਨਾਂ);
            ਲਈ (i = 0; i < font_sz; i++) {
                SDL_ToolkitThaiEncodingX11 thai_encoding;
                
                thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_NONE;
                ਜੇ (SDL_strstr(font_ਨਾਂ[i], "tis620-0")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS;
                } ਨਹੀਂਤਾਂ ਜੇ (SDL_strstr(font_ਨਾਂ[i], "tis620-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_MAC;
                } ਨਹੀਂਤਾਂ ਜੇ (SDL_strstr(font_ਨਾਂ[i], "tis620-2")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_TIS_WIN;
                } ਨਹੀਂਤਾਂ ਜੇ (SDL_strstr(font_ਨਾਂ[i], "iso8859-11")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_8859;
                } ਨਹੀਂਤਾਂ ਜੇ (SDL_strstr(font_ਨਾਂ[i], "iso10646-1")) {
                    thai_encoding = SDL_TOOLKIT_THAI_ENCODING_X11_UNICODE;
                }
                                                
                /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */
                ਜੇ (thai_encoding != SDL_TOOLKIT_THAI_ENCODING_X11_NONE) {
                    XFontStruct *font_struct;

                    /* We have to load the font again because the font_struct supplied by FontsOfFontSet does not have the per_char member set */
                    font_struct = X11_XLoadQueryFont(ਖਿੜਕੀ->display, font_ਨਾਂ[i]);
                    ਜੇ (font_struct) {
                        ਜੇ (font_struct->ਪ੍ਰਤੀ_char) {
                            ਪੂਰਨ glyphs_sz;
                            ਪੂਰਨ j;

                            glyphs_sz = (font_struct->max_char_or_byte2 - font_struct->min_char_or_byte2 + 1) * (font_struct->max_byte1 - font_struct->min_byte1 + 1);
                            ਲਈ (j = 0; j < glyphs_sz; j++) {
                                ਜੇ (font_struct->ਪ੍ਰਤੀ_char[j].lbearing < 0) {
                                    ਖਿੜਕੀ->thai_font = SDL_TOOLKIT_THAI_FONT_X11_ਵਿੱਥ;
                                }
                            }
                        }
                        X11_XFreeFont(ਖਿੜਕੀ->display, font_struct);
                    }
                }
                
                ਖਿੜਕੀ->thai_encoding = thai_encoding;
            } 
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        ਅੱਖਰ *font;

        ਲੱਦੋ_font_traditional:
        ਖਿੜਕੀ->utf8 = false;
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_ਮਾਪ * ਖਿੜਕੀ->iscale);
        ਖਿੜਕੀ->font_struct = X11_XLoadQueryFont(ਖਿੜਕੀ->display, font);
        SDL_free(font);
        ਜੇ (!ਖਿੜਕੀ->font_struct) {
            ਜੇ (ਖਿੜਕੀ->iscale > 0) {
                ਜੇ (ਖਿੜਕੀ->scale != 0) {
                    ਖਿੜਕੀ->iscale = (ਪੂਰਨ)SDL_ceilf(ਖਿੜਕੀ->scale);
                    ਖਿੜਕੀ->scale = 0;
                } ਨਹੀਂਤਾਂ {
                    ਖਿੜਕੀ->iscale--;
                }
                ਜਾਓ ਲੱਦੋ_font_traditional;
            } ਨਹੀਂਤਾਂ {
                ਖਿੜਕੀ->font_struct = X11_XLoadQueryFont(ਖਿੜਕੀ->display, g_ToolkitFontLatin1Fallback);
            }
        }
    }
}

ਸਥਿਰ ਖਾਲੀ X11Toolkit_SettingsNotify(ਅਚਲ ਅੱਖਰ *name, XSettingsAction action, XSettingsSetting *setting, ਖਾਲੀ *ਅੰਕੜੇ)
{
    SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ;
    ਪੂਰਨ i;

    ਖਿੜਕੀ = ਅੰਕੜੇ;

    ਜੇ (ਖਿੜਕੀ->xsettings_ਪਹਿਲਾ_ਸਮਾਂ) {
        ਵਾਪਸ;
    }

    ਜੇ (SDL_strcmp(name, SDL_XSETTINGS_GDK_ਖਿੜਕੀ_SCALING_ਗੁਣਕ) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_GDK_UNSCALED_DPI) == 0 ||
        SDL_strcmp(name, SDL_XSETTINGS_XFT_DPI) == 0) {
        bool dbe_already_ਤਿਆਰੀ = false;
        bool pixmap_already_ਤਿਆਰੀ = false;

        ਜੇ (ਖਿੜਕੀ->pixmap) {
            pixmap_already_ਤਿਆਰੀ = true;
        } ਨਹੀਂਤਾਂ {
            dbe_already_ਤਿਆਰੀ = true;
        }

        /* set scale vars */
        ਖਿੜਕੀ->scale = X11_GetGlobalContentScale(ਖਿੜਕੀ->display, ਖਿੜਕੀ->xsettings);
        ਖਿੜਕੀ->iscale = (ਪੂਰਨ)SDL_ceilf(ਖਿੜਕੀ->scale);
        ਜੇ (ਖਿੜਕੀ->scale < 1) {
            ਖਿੜਕੀ->scale = 1;
        }
        ਜੇ (SDL_roundf(ਖਿੜਕੀ->scale) == ਖਿੜਕੀ->scale) {
            ਖਿੜਕੀ->scale = 0;
        }

        /* setup fonts */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
        ਜੇ (ਖਿੜਕੀ->font_ਸੈੱਟ) {
            X11_XFree_Font_ਸੈੱਟ(ਖਿੜਕੀ->display, ਖਿੜਕੀ->font_ਸੈੱਟ);
        }
#ਜੇ_ਅੰਤ
        ਜੇ (ਖਿੜਕੀ->font_struct) {
            X11_XFreeFont(ਖਿੜਕੀ->display, ਖਿੜਕੀ->font_struct);
        }

        X11_Toolkit_Init_ਖਿੜਕੀ_Fonts(ਖਿੜਕੀ);

        /* set up window */
        ਜੇ (ਖਿੜਕੀ->scale != 0) {
            ਖਿੜਕੀ->ਖਿੜਕੀ_ਚੌੜਾਈ = SDL_lroundf((ਖਿੜਕੀ->ਖਿੜਕੀ_ਚੌੜਾਈ/ਖਿੜਕੀ->iscale) * ਖਿੜਕੀ->scale);
            ਖਿੜਕੀ->ਖਿੜਕੀ_ਉਚਾਈ = SDL_lroundf((ਖਿੜਕੀ->ਖਿੜਕੀ_ਉਚਾਈ/ਖਿੜਕੀ->iscale) * ਖਿੜਕੀ->scale);
            ਖਿੜਕੀ->pixmap_ਚੌੜਾਈ = ਖਿੜਕੀ->ਖਿੜਕੀ_ਚੌੜਾਈ;
            ਖਿੜਕੀ->pixmap_ਉਚਾਈ = ਖਿੜਕੀ->ਖਿੜਕੀ_ਉਚਾਈ;
            ਖਿੜਕੀ->pixmap = true;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->pixmap = false;
        }

        ਜੇ (ਖਿੜਕੀ->pixmap) {
            ਜੇ (!pixmap_already_ਤਿਆਰੀ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XDBE
                ਜੇ (SDL_X11_HAVE_XDBE && ਖਿੜਕੀ->xdbe) {
                    X11_Xdbe_Deallocate_ਪਿੱਠ_ਬਫਰ_Name(ਖਿੜਕੀ->display, ਖਿੜਕੀ->buf);
                }
#ਜੇ_ਅੰਤ
            }
            X11_XFreePixmap(ਖਿੜਕੀ->display, ਖਿੜਕੀ->drawable);
            X11_Toolkit_Init_ਖਿੜਕੀ_Pixmap(ਖਿੜਕੀ);
        } ਨਹੀਂਤਾਂ {
            ਜੇ (!dbe_already_ਤਿਆਰੀ) {
                X11_XFreePixmap(ਖਿੜਕੀ->display, ਖਿੜਕੀ->drawable);
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
                ਜੇ (ਖਿੜਕੀ->image) {
                    XDestroyImage(ਖਿੜਕੀ->image);
                    ਖਿੜਕੀ->image = ਨਿਰਾ;
                }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XDBE
                ਜੇ (SDL_X11_HAVE_XDBE && ਖਿੜਕੀ->xdbe) {
                    ਖਿੜਕੀ->buf = X11_Xdbe_Allocate_ਪਿੱਠ_ਬਫਰ_Name(ਖਿੜਕੀ->display, ਖਿੜਕੀ->ਖਿੜਕੀ, XdbeUndefined);
                    ਖਿੜਕੀ->drawable = ਖਿੜਕੀ->buf;
                }
#ਜੇ_ਅੰਤ
            }
        }

        /* notify controls */
        ਲਈ (i = 0; i < ਖਿੜਕੀ->controls_sz; i++) {
            ਖਿੜਕੀ->controls[i]->do_ਮਾਪ = true;

            ਜੇ (ਖਿੜਕੀ->controls[i]->func_on_scale_change) {
                ਖਿੜਕੀ->controls[i]->func_on_scale_change(ਖਿੜਕੀ->controls[i]);
            }

            ਜੇ (ਖਿੜਕੀ->controls[i]->func_calc_ਮਾਪ) {
                ਖਿੜਕੀ->controls[i]->func_calc_ਮਾਪ(ਖਿੜਕੀ->controls[i]);
            }

            ਖਿੜਕੀ->controls[i]->do_ਮਾਪ = false;
        }

        /* notify cb */
        ਜੇ (ਖਿੜਕੀ->cb_on_scale_change) {
            ਖਿੜਕੀ->cb_on_scale_change(ਖਿੜਕੀ, ਖਿੜਕੀ->cb_ਅੰਕੜੇ);
        }

        /* update ev scales */
        ਜੇ (!ਖਿੜਕੀ->pixmap) {
            ਖਿੜਕੀ->ev_scale = ਖਿੜਕੀ->ev_iscale = 1;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->ev_scale = ਖਿੜਕੀ->scale;
            ਖਿੜਕੀ->ev_iscale = ਖਿੜਕੀ->iscale;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ X11_Toolkit_Get_ਪਾਠ_ਚੌੜਾਈ_ਉਚਾਈ_For_Font(XFontStruct *font, ਅਚਲ ਅੱਖਰ *str, ਪੂਰਨ nbytes, ਪੂਰਨ *pwidth, ਪੂਰਨ *pheight, ਪੂਰਨ *ascent, ਪੂਰਨ *font_ਉਚਾਈ)
{
    XCharStruct ਪਾਠ_structure;
    ਪੂਰਨ font_direction, font_ascent, font_descent;
    
    X11_XTextExtents(font, str, nbytes, &font_direction, &font_ascent, &font_descent, &ਪਾਠ_structure);
    *pwidth = ਪਾਠ_structure.ਚੌੜਾਈ;
    *pheight = ਪਾਠ_structure.ascent + ਪਾਠ_structure.descent;
    *ascent = ਪਾਠ_structure.ascent;
    ਜੇ (font_ਉਚਾਈ) {
       *font_ਉਚਾਈ = font_ascent + font_descent;
    }
}

ਸਥਿਰ ਖਾਲੀ X11_Toolkit_Get_ਪਾਠ_ਚੌੜਾਈ_ਉਚਾਈ(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ, ਅਚਲ ਅੱਖਰ *str, ਪੂਰਨ nbytes, ਪੂਰਨ *pwidth, ਪੂਰਨ *pheight, ਪੂਰਨ *ascent, ਪੂਰਨ *descent, ਪੂਰਨ *font_ਉਚਾਈ)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    ਜੇ (ਅੰਕੜੇ->utf8) {
        XRectangle overall_ink, overall_logical;

        X11_Xutf8_ਪਾਠ_Extents(ਅੰਕੜੇ->font_ਸੈੱਟ, str, nbytes, &overall_ink, &overall_logical);
        *pwidth = overall_logical.ਚੌੜਾਈ;
        *pheight = overall_logical.ਉਚਾਈ;
        *ascent = -overall_logical.y;
        *descent = overall_logical.ਉਚਾਈ - *ascent;

        ਜੇ (font_ਉਚਾਈ) {
            XFont_ਸੈੱਟ_Extents *extents;

            extents = X11_XExtents_ਦਾ_Font_ਸੈੱਟ(ਅੰਕੜੇ->font_ਸੈੱਟ);
            *font_ਉਚਾਈ = extents->max_logical_extent.ਉਚਾਈ;
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        XCharStruct ਪਾਠ_structure;
        ਪੂਰਨ font_direction, font_ascent, font_descent;
        X11_XTextExtents(ਅੰਕੜੇ->font_struct, str, nbytes,
                         &font_direction, &font_ascent, &font_descent,
                         &ਪਾਠ_structure);
        *pwidth = ਪਾਠ_structure.ਚੌੜਾਈ;
        *pheight = ਪਾਠ_structure.ascent + ਪਾਠ_structure.descent;
        *ascent = ਪਾਠ_structure.ascent;
        *descent = ਪਾਠ_structure.descent;

        ਜੇ (font_ਉਚਾਈ) {
            *font_ਉਚਾਈ = font_ascent + font_descent;
        }
    }
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
SDL_List_ਗੰਢ *X11_Toolkit_Make_ਪਾਠ_Elements(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ, ਅੱਖਰ *txt, size_t sz, FriBidiParType *par)
#ਨਹੀਂਤਾਂ
SDL_List_ਗੰਢ *X11_Toolkit_Make_ਪਾਠ_Elements(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ, ਅੱਖਰ *txt, size_t sz)
#ਜੇ_ਅੰਤ
{
    SDL_List_ਗੰਢ *list;
    ਅੱਖਰ *str;
    ਅੱਖਰ *ਬਫਰ_2;
    Uint32 cp;
    bool thai;
    bool free_txt;
    
    free_txt = false;
    list = ਨਿਰਾ;
    thai = 0;
    str = txt;
    ਬਫਰ_2 = SDL_malloc(1);
    ਬਫਰ_2[0] = 0;
    
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
    ਜੇ (par) {
        *par = FRIBIDI_PAR_LTR;
    }
    ਜੇ (ਅੰਕੜੇ->fribidi) {
        ਅੱਖਰ *fstr;
                
        fstr = SDL_FriBidi_Process(ਅੰਕੜੇ->fribidi, str, sz, ਅੰਕੜੇ->do_shaping, par);
        ਜੇ (fstr) {
            txt = fstr;
            str = fstr;
            sz = SDL_strlen(str);
            free_txt = true;
        } 
    }
#ਜੇ_ਅੰਤ        

    ਜਦੋਂ (1) {
        ਅੱਖਰ *new;
        ਅੱਖਰ utf8[5];
        size_t csz;
        bool cond;

        SDL_zeroa(utf8);
        cp = SDL_ਕਦਮ_UTF8((ਅਚਲ ਅੱਖਰ **)&str, &sz);
        cond = (0xe00 <= cp && cp <= 0xe7f) ? true : false;
        ਜੇ (cp == 0 || cond == (thai ? false : true)) {
            SDL_Toolkit_ਪਾਠ_Element_X11 *element;
            
            element = SDL_malloc(ਆਕਾਰ(SDL_Toolkit_ਪਾਠ_Element_X11));
            ਜੇ (thai) {
                element->type = SDL_TOOLKIT_ਪਾਠ_TYPE_X11_THAI;
            } ਨਹੀਂਤਾਂ {
                element->type = SDL_TOOLKIT_ਪਾਠ_TYPE_X11_GENERIC;
            }
            element->str = SDL_strdup(ਬਫਰ_2);
            element->sz = SDL_strlen(ਬਫਰ_2);
            element->str_free = SDL_free;
            
            SDL_List_ਜੋੜੋ(&list, element);
            
            SDL_free(ਬਫਰ_2);
            ਬਫਰ_2 = SDL_malloc(1);
            ਬਫਰ_2[0] = 0;
            thai = thai ? false : true;
        }

        ਜੇ (!cp) {
            ਰੋਕੋ;
        }
        
        SDL_UCS4_ਮੰਜ਼ਿਲ_UTF8(cp, utf8);
        csz = SDL_strlen(ਬਫਰ_2) + SDL_strlen(utf8) + 1;
        new = SDL_malloc(csz);
        SDL_strlcpy(new, ਬਫਰ_2, csz);
        SDL_strlcat(new, utf8, csz);
        SDL_free(ਬਫਰ_2);
        ਬਫਰ_2 = new;
    }

    SDL_free(ਬਫਰ_2);
    ਜੇ (free_txt) {
        SDL_free(txt);
    }
    ਵਾਪਸ list;
}

ਖਾਲੀ X11_Toolkit_Shape_ਪਾਠ_Elements(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ, SDL_List_ਗੰਢ *list)
{
    SDL_List_ਗੰਢ *cursor;
    SDL_Toolkit_ਪਾਠ_Element_X11 *prev;
    ਪੂਰਨ ਆਰਜ਼ੀ;
    
    /* Shape and calculate bounding box */
    cursor = list;
    ਜਦੋਂ (cursor) {
        SDL_Toolkit_ਪਾਠ_Element_X11 *element;
        
        element = cursor->ਇੰਦਰਾਜ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBTHAI_H
        element->thai_overlays = ਨਿਰਾ;
#ਜੇ_ਅੰਤ
        ਜੇ (element->type == SDL_TOOLKIT_ਪਾਠ_TYPE_X11_THAI) {
            ਜੇ (ਅੰਕੜੇ->thai_font == SDL_TOOLKIT_THAI_FONT_X11_ਵਿੱਥ) {
                X11_Toolkit_Get_ਪਾਠ_ਚੌੜਾਈ_ਉਚਾਈ(ਅੰਕੜੇ, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &ਆਰਜ਼ੀ, ਨਿਰਾ);
            } ਨਹੀਂਤਾਂ {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBTHAI_H
                ਜੇ (ਅੰਕੜੇ->th) {
                    ਬਣਤਰ thcell_t *cells;
                    ਅੱਖਰ *tis_str;
                    ਅੱਖਰ *ਅਧਾਰ_tis_str;
                    size_t cells_sz;
                    size_t ਅਧਾਰ_tis_str_sz;
                    size_t tis_str_sz;
                                                    
                    tis_str = SDL_iconv_string("TIS-620", "UTF-8", element->str, element->sz);
                    cells_sz = tis_str_sz = SDL_strlen(tis_str);
                    
                    cells = SDL_calloc(cells_sz, ਆਕਾਰ(ਬਣਤਰ thcell_t));
                    ਅੰਕੜੇ->th->make_cells((ਅਚਲ thchar_t *)tis_str, tis_str_sz, cells, &cells_sz, 0);

                    ਅਧਾਰ_tis_str_sz = cells_sz;
                    ਅਧਾਰ_tis_str = SDL_malloc(ਅਧਾਰ_tis_str_sz + 1);
                    ਲਈ (ਆਰਜ਼ੀ = 0; ਆਰਜ਼ੀ < cells_sz; ਆਰਜ਼ੀ++) {
                        ਅਧਾਰ_tis_str[ਆਰਜ਼ੀ] = cells[ਆਰਜ਼ੀ].ਅਧਾਰ;
                        
                        ਜੇ (cells[ਆਰਜ਼ੀ].hilo) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            ਅੱਖਰ *pre;
                            ਪੂਰਨ temp2;
                            
                            overlay = SDL_malloc(ਆਕਾਰ(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", ਅਧਾਰ_tis_str, ਆਰਜ਼ੀ);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ਅਚਲ ਅੱਖਰ *)&cells[ਆਰਜ਼ੀ].hilo, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->ਸਿਖਰ = false;
                            X11_Toolkit_Get_ਪਾਠ_ਚੌੜਾਈ_ਉਚਾਈ(ਅੰਕੜੇ, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ਨਿਰਾ);
                            X11_Toolkit_Get_ਪਾਠ_ਚੌੜਾਈ_ਉਚਾਈ(ਅੰਕੜੇ, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ਨਿਰਾ);
                            SDL_List_ਜੋੜੋ(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                        
                        ਜੇ (cells[ਆਰਜ਼ੀ].ਸਿਖਰ) {
                            SDL_ToolkitThaiOverlayX11 *overlay;
                            ਅੱਖਰ *pre;
                            ਪੂਰਨ temp2;
                            
                            overlay = SDL_malloc(ਆਕਾਰ(SDL_ToolkitThaiOverlayX11));
                            pre = SDL_iconv_string("UTF-8", "TIS-620", ਅਧਾਰ_tis_str, ਆਰਜ਼ੀ);
                            overlay->str = SDL_iconv_string("UTF-8", "TIS-620", (ਅਚਲ ਅੱਖਰ *)&cells[ਆਰਜ਼ੀ].ਸਿਖਰ, 1);
                            overlay->sz = SDL_strlen(overlay->str);
                            overlay->ਸਿਖਰ = true;
                            X11_Toolkit_Get_ਪਾਠ_ਚੌੜਾਈ_ਉਚਾਈ(ਅੰਕੜੇ, pre, SDL_strlen(pre), &overlay->rect.x, &temp2, &temp2, &temp2, ਨਿਰਾ);
                            X11_Toolkit_Get_ਪਾਠ_ਚੌੜਾਈ_ਉਚਾਈ(ਅੰਕੜੇ, overlay->str, overlay->sz, &overlay->rect.w, &overlay->rect.h, &overlay->rect.y, &temp2, ਨਿਰਾ);
                            SDL_List_ਜੋੜੋ(&element->thai_overlays, overlay);
                            SDL_free(pre);
                        }
                    }
                    ਅਧਾਰ_tis_str[ਅਧਾਰ_tis_str_sz] = '\0';
                    
                    element->str_free(element->str);
                    element->str = SDL_iconv_string("UTF-8", "TIS-620", ਅਧਾਰ_tis_str, ਅਧਾਰ_tis_str_sz);
                    element->sz = SDL_strlen(element->str);
                    X11_Toolkit_Get_ਪਾਠ_ਚੌੜਾਈ_ਉਚਾਈ(ਅੰਕੜੇ, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &ਆਰਜ਼ੀ, &element->font_h);

                    SDL_free(tis_str);
                    SDL_free(cells);                
                    SDL_free(ਅਧਾਰ_tis_str);
                }
#ਨਹੀਂਤਾਂ
                X11_Toolkit_Get_ਪਾਠ_ਚੌੜਾਈ_ਉਚਾਈ(ਅੰਕੜੇ, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &ਆਰਜ਼ੀ, &element->font_h);
#ਜੇ_ਅੰਤ            
            }
        } ਨਹੀਂਤਾਂ {
            X11_Toolkit_Get_ਪਾਠ_ਚੌੜਾਈ_ਉਚਾਈ(ਅੰਕੜੇ, element->str, element->sz, &element->rect.w, &element->rect.h, &element->rect.y, &ਆਰਜ਼ੀ, &element->font_h);
        }
        
        cursor = cursor->ਅਗਲਾ;
    }
    
    /* Add offsets */
    prev = ਨਿਰਾ;
    cursor = list;
    ਜਦੋਂ (cursor) {
        SDL_Toolkit_ਪਾਠ_Element_X11 *element;
        
        element = cursor->ਇੰਦਰਾਜ;        
        ਜੇ (prev) {
            element->rect.x = prev->rect.x + prev->rect.w;
        } ਨਹੀਂਤਾਂ {
            element->rect.x = 0;
        }
        
        prev = element;
        cursor = cursor->ਅਗਲਾ;
    }
}


ਖਾਲੀ X11_Toolkit_Draw_ਪਾਠ_Elements(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ, SDL_List_ਗੰਢ *list, ਪੂਰਨ x, ਪੂਰਨ y)
{
    SDL_List_ਗੰਢ *cursor;
    
    cursor = list;
    
    ਜਦੋਂ (cursor) {
        SDL_Toolkit_ਪਾਠ_Element_X11 *element;
        
        element = cursor->ਇੰਦਰਾਜ;
        ਜੇ (element->type == SDL_TOOLKIT_ਪਾਠ_TYPE_X11_THAI) {
            ਜੇ (ਅੰਕੜੇ->thai_font == SDL_TOOLKIT_THAI_FONT_X11_ਵਿੱਥ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
                ਜੇ (ਅੰਕੜੇ->utf8) {
                    X11_Xutf8DrawString(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->font_ਸੈੱਟ, ਅੰਕੜੇ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
                {
                    X11_XDrawString(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }
            } ਨਹੀਂਤਾਂ {    
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBTHAI_H
                SDL_List_ਗੰਢ *overlay_cursor;
                    
                /* Draw the base string */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
                ਜੇ (ਅੰਕੜੇ->utf8) {
                    X11_Xutf8DrawString(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->font_ਸੈੱਟ, ਅੰਕੜੇ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
                {
                    X11_XDrawString(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
                }                        
                
                /* Draw overlays */
                overlay_cursor = element->thai_overlays;
                ਜਦੋਂ (overlay_cursor) {
                    SDL_ToolkitThaiOverlayX11 *overlay;
                    
                    overlay = overlay_cursor->ਇੰਦਰਾਜ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
                    ਜੇ (ਅੰਕੜੇ->utf8) {
                        X11_Xutf8DrawString(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->font_ਸੈੱਟ, ਅੰਕੜੇ->ctx, x + element->rect.x + overlay->rect.x, y + overlay->rect.y, overlay->str, overlay->sz);
                    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
                    {
                        X11_XDrawString(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->ctx, x + element->rect.x + overlay->rect.x, y + element->rect.y + overlay->rect.y, overlay->str, overlay->sz);
                    }                        
                            
                    overlay_cursor = overlay_cursor->ਅਗਲਾ;
                }
#ਜੇ_ਅੰਤ                
            }
        } ਨਹੀਂਤਾਂ {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
            ਜੇ (ਅੰਕੜੇ->utf8) {
                X11_Xutf8DrawString(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->font_ਸੈੱਟ, ਅੰਕੜੇ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
            {
                X11_XDrawString(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->ctx, x + element->rect.x, y + element->rect.y, element->str, element->sz);
            }
        }
        
        cursor = cursor->ਅਗਲਾ;
    }
}

ਪੂਰਨ X11_Toolkit_Get_ਪਾਠ_Elements_Rect(SDL_List_ਗੰਢ *list, SDL_Rect *ਬਾਹਰਲਾ)
{
    SDL_List_ਗੰਢ *cursor;
    ਪੂਰਨ ret;
    
    ret = 0;
    ਬਾਹਰਲਾ->x = ਬਾਹਰਲਾ->y = 0;
    ਬਾਹਰਲਾ->w = ਬਾਹਰਲਾ->h = 0;
    cursor = list;
    ਜਦੋਂ (cursor) {
        SDL_Toolkit_ਪਾਠ_Element_X11 *element;
        
        element = cursor->ਇੰਦਰਾਜ;
        
        ਬਾਹਰਲਾ->w += element->rect.w;
        ਬਾਹਰਲਾ->h = SDL_max(ਬਾਹਰਲਾ->h, element->rect.h);
        ret = SDL_max(ret, element->font_h);
        
        cursor = cursor->ਅਗਲਾ;
    }
    
    ਵਾਪਸ ret;
}

ਖਾਲੀ X11_Toolkit_Free_ਪਾਠ_Elements_List_Contents(SDL_List_ਗੰਢ *list)
{
    SDL_List_ਗੰਢ *cursor;
    
    cursor = list;
    ਜਦੋਂ (cursor) {
        SDL_Toolkit_ਪਾਠ_Element_X11 *element;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBTHAI_H
        SDL_List_ਗੰਢ *overlay_cursor;
#ਜੇ_ਅੰਤ

        element = cursor->ਇੰਦਰਾਜ;
        
        ਜੇ (element->str_free) {
            element->str_free(element->str);
        }
        
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBTHAI_H        
        overlay_cursor = element->thai_overlays;
        ਜਦੋਂ (overlay_cursor) {
            SDL_ToolkitThaiOverlayX11 *overlay;
                    
            overlay = overlay_cursor->ਇੰਦਰਾਜ;
            SDL_free(overlay->str);
            SDL_free(overlay);
            overlay_cursor = overlay_cursor->ਅਗਲਾ;
        }
        SDL_ListClear(&element->thai_overlays);
#ਜੇ_ਅੰਤ
        
        SDL_free(element);
        
        cursor = cursor->ਅਗਲਾ;
    }
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X11_Toolkit_Free_ਪਾਠ_Elements(x) X11_Toolkit_Free_ਪਾਠ_Elements_List_Contents(x); SDL_ListClear(&x)
 
ਸਥਿਰ bool X11Toolkit_ShouldFlipUI(ਖਾਲੀ) 
{
    SDL_Locale **current_locales;
    ਸਥਿਰ ਅਚਲ SDL_Locale rtl_locales[] = {
        { "ar", ਨਿਰਾ, },
        { "fa", "AF", },
        { "fa", "IR", },
        { "he", ਨਿਰਾ, },
        { "iw", ਨਿਰਾ, },
        { "yi", ਨਿਰਾ, },
        { "ur", ਨਿਰਾ, },
        { "ug", ਨਿਰਾ, },
        { "kd", ਨਿਰਾ, },
        { "pk", "PK", },
        { "ps", ਨਿਰਾ, }
    }; 
    ਪੂਰਨ current_locales_sz;
    ਪੂਰਨ i;

    current_locales = SDL_GetPreferredLocales(&current_locales_sz);
    ਜੇ (current_locales_sz <= 0) {
        ਵਾਪਸ false;        
    }
    ਲਈ (i = 0; i < SDL_arraysize(rtl_locales); ++i) {
        ਜੇ (SDL_startswith(current_locales[0]->language, rtl_locales[i].language)) {
            ਜੇ (!rtl_locales[i].country) {
                ਵਾਪਸ true;
            } ਨਹੀਂਤਾਂ {
                ਵਾਪਸ SDL_startswith(current_locales[0]->country, rtl_locales[i].country);
            }
        }
    }
    
    ਵਾਪਸ false;
}

SDL_Toolkit_ਖਿੜਕੀ_X11 *X11_Toolkit_Create_ਖਿੜਕੀ_Struct(SDL_ਖਿੜਕੀ *ਮਾਪਾ, SDL_Toolkit_ਖਿੜਕੀ_X11 *tkparent, SDL_Toolkit_ਖਿੜਕੀ_ਬਹੁਲਕ_X11 ਬਹੁਲਕ, ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Color *colorhints, bool create_new_display)
{
    SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ;
    ਪੂਰਨ i;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    SDL_SystemTheme theme;
#ਜੇ_ਅੰਤ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ErrorFreeRetNull(x, y) SDL_ਸੈੱਟ_Error(x); SDL_free(y); ਵਾਪਸ ਨਿਰਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ErrorCloseFreeRetNull(x, y, z) X11_XCloseDisplay(z->display); SDL_ਸੈੱਟ_Error(x, y); SDL_free(z); ਵਾਪਸ ਨਿਰਾ

    ਜੇ (!SDL_X11_ਲੱਦੋ_Symbols()) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    // This code could get called from multiple threads maybe?
    X11_XInit_ਧਾਗੇ();

    ਖਿੜਕੀ = (SDL_Toolkit_ਖਿੜਕੀ_X11 *)SDL_malloc(ਆਕਾਰ(SDL_Toolkit_ਖਿੜਕੀ_X11));
    ਜੇ (!ਖਿੜਕੀ) {
        SDL_ਸੈੱਟ_Error("Unable to allocate toolkit window structure");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਖਿੜਕੀ->ਬਹੁਲਕ = ਬਹੁਲਕ;
    ਖਿੜਕੀ->tk_ਮਾਪਾ = tkparent;

#ਜੇ SDL_ਸੈੱਟ_LOCALE
    ਜੇ (ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_DIALOG) {
        ਖਿੜਕੀ->origlocale = setlocale(LC_ALL, ਨਿਰਾ);
        ਜੇ (ਖਿੜਕੀ->origlocale) {
            ਖਿੜਕੀ->origlocale = SDL_strdup(ਖਿੜਕੀ->origlocale);
            ਜੇ (!ਖਿੜਕੀ->origlocale) {
                SDL_free(ਖਿੜਕੀ);
                ਵਾਪਸ ਨਿਰਾ;
            }
            (ਖਾਲੀ)setlocale(LC_ALL, "");
        }
    }
#ਜੇ_ਅੰਤ

    ਖਿੜਕੀ->ਮਾਪਾ_device = ਨਿਰਾ;
    ਜੇ (create_new_display) {
        ਖਿੜਕੀ->display = X11_XOpenDisplay(ਨਿਰਾ);
        ਖਿੜਕੀ->display_close = true;
        ਜੇ (!ਖਿੜਕੀ->display) {
            ErrorFreeRetNull("Couldn't open X11 display", ਖਿੜਕੀ);
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (ਮਾਪਾ) {
            ਖਿੜਕੀ->ਮਾਪਾ_device = SDL_GetVideoDevice();
            ਖਿੜਕੀ->display = ਖਿੜਕੀ->ਮਾਪਾ_device->ਅੰਦਰੂਨੀ->display;
            ਖਿੜਕੀ->display_close = false;
        } ਨਹੀਂਤਾਂ ਜੇ (tkparent) {
            ਖਿੜਕੀ->display = tkparent->display;
            ਖਿੜਕੀ->display_close = false;
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->display = X11_XOpenDisplay(ਨਿਰਾ);
            ਖਿੜਕੀ->display_close = true;
            ਜੇ (!ਖਿੜਕੀ->display) {
                ErrorFreeRetNull("Couldn't open X11 display", ਖਿੜਕੀ);
            }
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
    ਪੂਰਨ xrandr_event_ਅਧਾਰ, xrandr_error_ਅਧਾਰ;
    ਖਿੜਕੀ->xrandr = X11_XRRQueryExtension(ਖਿੜਕੀ->display, &xrandr_event_ਅਧਾਰ, &xrandr_error_ਅਧਾਰ);
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
    ਖਿੜਕੀ->shm_pixmap = False;
    ਖਿੜਕੀ->shm = X11_XShmQueryExtension(ਖਿੜਕੀ->display) ? SDL_X11_HAVE_SHM : false;
    ਜੇ (ਖਿੜਕੀ->shm) {
        ਪੂਰਨ major;
        ਪੂਰਨ minor;

        X11_XShm_Query_ਸੰਸਕਰਣ(ਖਿੜਕੀ->display, &major, &minor, &ਖਿੜਕੀ->shm_pixmap);
        ਜੇ (ਖਿੜਕੀ->shm_pixmap) {
            ਜੇ (X11_XShmPixmapFormat(ਖਿੜਕੀ->display) != ZPixmap) {
                ਖਿੜਕੀ->shm_pixmap = False;
            }
        }
    }
#ਜੇ_ਅੰਤ

    /* Scale/Xsettings */
    ਖਿੜਕੀ->pixmap = false;
    ਖਿੜਕੀ->xsettings_ਪਹਿਲਾ_ਸਮਾਂ = true;
    ਖਿੜਕੀ->xsettings = xsettings_client_new(ਖਿੜਕੀ->display, DefaultScreen(ਖਿੜਕੀ->display), X11Toolkit_SettingsNotify, ਨਿਰਾ, ਖਿੜਕੀ);
    ਖਿੜਕੀ->xsettings_ਪਹਿਲਾ_ਸਮਾਂ = false;
    ਖਿੜਕੀ->scale = X11_GetGlobalContentScale(ਖਿੜਕੀ->display, ਖਿੜਕੀ->xsettings);
    ਜੇ (ਖਿੜਕੀ->scale < 1) {
        ਖਿੜਕੀ->scale = 1;
    }
    ਖਿੜਕੀ->iscale = (ਪੂਰਨ)SDL_ceilf(ਖਿੜਕੀ->scale);
    ਜੇ (SDL_roundf(ਖਿੜਕੀ->scale) == ਖਿੜਕੀ->scale) {
        ਖਿੜਕੀ->scale = 0;
    }

    /* Fonts */
    X11_Toolkit_Init_ਖਿੜਕੀ_Fonts(ਖਿੜਕੀ);

    /* Color hints */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
    theme = SDL_SYSTEM_THEME_LIGHT;
    ਜੇ (SDL_SystemTheme_Init()) {
        theme = SDL_SystemTheme_Get();
    }
#ਜੇ_ਅੰਤ

    ਜੇ (!colorhints) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_USE_LIBDBUS
        ਚੋਣ (theme) {
            ਹਾਲਤ SDL_SYSTEM_THEME_DARK:
                colorhints = g_default_colors_dark;
                ਰੋਕੋ;
#ਜੇ 0
            ਹਾਲਤ SDL_SYSTEM_THEME_LIGHT_ਉੱਚਾ_CONTRAST:
                colorhints = g_default_colors_light_ਉੱਚਾ_contrast;
                ਰੋਕੋ;
            ਹਾਲਤ SDL_SYSTEM_THEME_DARK_ਉੱਚਾ_CONTRAST:
                colorhints = g_default_colors_dark_ਉੱਚਾ_contrast;
                ਰੋਕੋ;
#ਜੇ_ਅੰਤ
            ਮੂਲ:
                colorhints = g_default_colors;
        }
#ਨਹੀਂਤਾਂ
        colorhints = g_default_colors;
#ਜੇ_ਅੰਤ
    }
    ਖਿੜਕੀ->color_hints = colorhints;

    /* Convert colors to 16 bpc XColor format */
    ਲਈ (i = 0; i < SDL_MESSAGEBOX_COLOR_ਗਿਣਤੀ; i++) {
        ਖਿੜਕੀ->xcolor[i].flags = DoRed|DoGreen|DoBlue;
        ਖਿੜਕੀ->xcolor[i].red = colorhints[i].r * 257;
        ਖਿੜਕੀ->xcolor[i].green = colorhints[i].g * 257;
        ਖਿੜਕੀ->xcolor[i].blue = colorhints[i].b * 257;
    }

    /* Generate bevel and pressed colors */
    ਖਿੜਕੀ->xcolor_bevel_l1.flags = DoRed|DoGreen|DoBlue;
    ਖਿੜਕੀ->xcolor_bevel_l1.red = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 12500, 0, 65535);
    ਖਿੜਕੀ->xcolor_bevel_l1.green = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 12500, 0, 65535);
    ਖਿੜਕੀ->xcolor_bevel_l1.blue = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 12500, 0, 65535);

    ਖਿੜਕੀ->xcolor_bevel_l2.flags = DoRed|DoGreen|DoBlue;
    ਖਿੜਕੀ->xcolor_bevel_l2.red = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red + 32500, 0, 65535);
    ਖਿੜਕੀ->xcolor_bevel_l2.green = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green + 32500, 0, 65535);
    ਖਿੜਕੀ->xcolor_bevel_l2.blue = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue + 32500, 0, 65535);

    ਖਿੜਕੀ->xcolor_bevel_d.flags = DoRed|DoGreen|DoBlue;
    ਖਿੜਕੀ->xcolor_bevel_d.red = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].red - 22500, 0, 65535);
    ਖਿੜਕੀ->xcolor_bevel_d.green = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].green - 22500, 0, 65535);
    ਖਿੜਕੀ->xcolor_bevel_d.blue = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].blue - 22500, 0, 65535);

    ਖਿੜਕੀ->xcolor_pressed.flags = DoRed|DoGreen|DoBlue;
    ਖਿੜਕੀ->xcolor_pressed.red = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].red - 12500, 0, 65535);
    ਖਿੜਕੀ->xcolor_pressed.green = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].green - 12500, 0, 65535);
    ਖਿੜਕੀ->xcolor_pressed.blue = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].blue - 12500, 0, 65535);

    ਖਿੜਕੀ->xcolor_disabled_ਪਾਠ.flags = DoRed|DoGreen|DoBlue;
    ਖਿੜਕੀ->xcolor_disabled_ਪਾਠ.red = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_ਪਾਠ].red + 19500, 0, 65535);
    ਖਿੜਕੀ->xcolor_disabled_ਪਾਠ.green = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_ਪਾਠ].green + 19500, 0, 65535);
    ਖਿੜਕੀ->xcolor_disabled_ਪਾਠ.blue = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_ਪਾਠ].blue + 19500, 0, 65535);

    /* Screen */
    ਖਿੜਕੀ->ਮਾਪਾ = ਮਾਪਾ;
    ਜੇ (ਮਾਪਾ) {
        SDL_Display_ਅੰਕੜੇ *displaydata = SDL_Get_Display_Driver_ਅੰਕੜੇ_For_ਖਿੜਕੀ(ਮਾਪਾ);
        ਖਿੜਕੀ->screen = displaydata->screen;
    } ਨਹੀਂਤਾਂ {
        ਖਿੜਕੀ->screen = DefaultScreen(ਖਿੜਕੀ->display);
    }

    /* Visuals */
    ਜੇ (ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_ਬੱਚਾ) {
        ਖਿੜਕੀ->visual = ਮਾਪਾ->ਅੰਦਰੂਨੀ->visual;
        ਖਿੜਕੀ->cmap = ਮਾਪਾ->ਅੰਦਰੂਨੀ->colormap;
        X11_GetVisualInfoFromVisual(ਖਿੜਕੀ->display, ਖਿੜਕੀ->visual, &ਖਿੜਕੀ->vi);
        ਖਿੜਕੀ->ਡੂੰਘਾਈ_2 = ਖਿੜਕੀ->vi.ਡੂੰਘਾਈ_2;
    } ਨਹੀਂਤਾਂ {
        ਖਿੜਕੀ->visual = DefaultVisual(ਖਿੜਕੀ->display, ਖਿੜਕੀ->screen);
        ਖਿੜਕੀ->cmap = DefaultColormap(ਖਿੜਕੀ->display, ਖਿੜਕੀ->screen);
        ਖਿੜਕੀ->ਡੂੰਘਾਈ_2 = Default_ਡੂੰਘਾਈ(ਖਿੜਕੀ->display, ਖਿੜਕੀ->screen);
        X11_GetVisualInfoFromVisual(ਖਿੜਕੀ->display, ਖਿੜਕੀ->visual, &ਖਿੜਕੀ->vi);
    }

    /* Allocate colors */
    ਲਈ (i = 0; i < SDL_MESSAGEBOX_COLOR_ਗਿਣਤੀ; i++) {
        X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &ਖਿੜਕੀ->xcolor[i]);
    }
    X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &ਖਿੜਕੀ->xcolor_bevel_l1);
    X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &ਖਿੜਕੀ->xcolor_bevel_l2);
    X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &ਖਿੜਕੀ->xcolor_bevel_d);
    X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &ਖਿੜਕੀ->xcolor_pressed);
    X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &ਖਿੜਕੀ->xcolor_disabled_ਪਾਠ);

    /* Control list */
    ਖਿੜਕੀ->has_focus = false;
    ਖਿੜਕੀ->controls = ਨਿਰਾ;
    ਖਿੜਕੀ->controls_sz = 0;
    ਖਿੜਕੀ->dyn_controls_sz = 0;
    ਖਿੜਕੀ->fiddled_control = ਨਿਰਾ;
    ਖਿੜਕੀ->dyn_controls = ਨਿਰਾ;

    /* Menu windows */
    ਖਿੜਕੀ->popup_windows = ਨਿਰਾ;

    /* BIDI engine */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
    ਖਿੜਕੀ->fribidi = SDL_FriBidi_Create();
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBTHAI_H
    ਖਿੜਕੀ->th = SDL_LibThai_Create();
#ਜੇ_ਅੰਤ
    
    /* Interface direction */
    ਖਿੜਕੀ->flip_interface = X11Toolkit_ShouldFlipUI();
    
    ਵਾਪਸ ਖਿੜਕੀ;
}

ਸਥਿਰ ਖਾਲੀ X11_Toolkit_ਜੋੜੋ_Control_ਮੰਜ਼ਿਲ_ਖਿੜਕੀ(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ, SDL_ToolkitControlX11 *control) {
    /* Add to controls list */
    ਖਿੜਕੀ->controls_sz++;
    ਜੇ (ਖਿੜਕੀ->controls_sz == 1) {
        ਖਿੜਕੀ->controls = (ਬਣਤਰ SDL_ToolkitControlX11 **)SDL_malloc(ਆਕਾਰ(ਬਣਤਰ SDL_ToolkitControlX11 *));
    } ਨਹੀਂਤਾਂ {
        ਖਿੜਕੀ->controls = (ਬਣਤਰ SDL_ToolkitControlX11 **)SDL_realloc(ਖਿੜਕੀ->controls, ਆਕਾਰ(ਬਣਤਰ SDL_ToolkitControlX11 *) * ਖਿੜਕੀ->controls_sz);
    }
    ਖਿੜਕੀ->controls[ਖਿੜਕੀ->controls_sz - 1] = control;

    /* If dynamic, add it to the dynamic controls list too */
    ਜੇ (control->dynamic) {
        ਖਿੜਕੀ->dyn_controls_sz++;
        ਜੇ (ਖਿੜਕੀ->dyn_controls_sz == 1) {
            ਖਿੜਕੀ->dyn_controls = (ਬਣਤਰ SDL_ToolkitControlX11 **)SDL_malloc(ਆਕਾਰ(ਬਣਤਰ SDL_ToolkitControlX11 *));
        } ਨਹੀਂਤਾਂ {
            ਖਿੜਕੀ->dyn_controls = (ਬਣਤਰ SDL_ToolkitControlX11 **)SDL_realloc(ਖਿੜਕੀ->dyn_controls, ਆਕਾਰ(ਬਣਤਰ SDL_ToolkitControlX11 *) * ਖਿੜਕੀ->dyn_controls_sz);
        }
        ਖਿੜਕੀ->dyn_controls[ਖਿੜਕੀ->dyn_controls_sz - 1] = control;
    }

    /* If selected, set currently focused control to it */
    ਜੇ (control->selected) {
        ਖਿੜਕੀ->focused_control = control;
    }
}

bool X11_Toolkit_Create_ਖਿੜਕੀ_Res(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ, ਪੂਰਨ w, ਪੂਰਨ h, ਪੂਰਨ cx, ਪੂਰਨ cy, ਅੱਖਰ *title)
{
    ਪੂਰਨ x, y;
    XSizeHints *sizehints;
    XSet_ਖਿੜਕੀ_ਗੁਣ wnd_attr;
    Atom NET_WM_ਖਿੜਕੀ_TYPE, NET_WM_ਖਿੜਕੀ_TYPE_DIALOG, NET_WM_ਖਿੜਕੀ_TYPE_DROPDOWN_MENU, NET_WM_ਖਿੜਕੀ_TYPE_TOOLTIP;
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *windowdata = ਨਿਰਾ;
    Display *display = ਅੰਕੜੇ->display;
    XGCValues ctx_vals;
    ਖਿੜਕੀ_2 ਜੜ੍ਹ_win;
    ਖਿੜਕੀ_2 ਮਾਪਾ_win;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ gcflags = GCForeground | GCBackground;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ valuemask;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XRANDR_DISABLED_BY_DEFAULT
    ਅਚਲ bool use_xrandr_by_default = false;
#ਨਹੀਂਤਾਂ
    ਅਚਲ bool use_xrandr_by_default = true;
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

    ਜੇ (ਅੰਕੜੇ->scale == 0) {
        ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ = w;
        ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ = h;
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ = SDL_lroundf((w/ਅੰਕੜੇ->iscale) * ਅੰਕੜੇ->scale);
        ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ = SDL_lroundf((h/ਅੰਕੜੇ->iscale) * ਅੰਕੜੇ->scale);
        ਅੰਕੜੇ->pixmap_ਚੌੜਾਈ = w;
        ਅੰਕੜੇ->pixmap_ਉਚਾਈ = h;
        ਅੰਕੜੇ->pixmap = true;
    }

    ਜੇ (ਅੰਕੜੇ->ਮਾਪਾ) {
        windowdata = ਅੰਕੜੇ->ਮਾਪਾ->ਅੰਦਰੂਨੀ;
    }

    valuemask = CWEvent_ਨਕਾਬ | CWColormap;
    ਅੰਕੜੇ->event_ਨਕਾਬ = Exposure_ਨਕਾਬ |
                       Button_Press_ਨਕਾਬ | Button_Release_ਨਕਾਬ | ਕੁੰਜੀ_Press_ਨਕਾਬ | ਕੁੰਜੀ_Release_ਨਕਾਬ |
                       Structure_Notify_ਨਕਾਬ | Focus_Change_ਨਕਾਬ | ਸੂਚਕ_Motion_ਨਕਾਬ;
    wnd_attr.event_ਨਕਾਬ = ਅੰਕੜੇ->event_ਨਕਾਬ;
    wnd_attr.colormap = ਅੰਕੜੇ->cmap;
    ਜੇ (ਅੰਕੜੇ->ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_MENU || ਅੰਕੜੇ->ਬਹੁਲਕ== SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_TOOLTIP) {
        valuemask |= CWOverrideRedirect | CWSaveUnder;
        wnd_attr.save_under = True;
        wnd_attr.override_redirect = True;
    }
    ਜੜ੍ਹ_win = ਜੜ੍ਹ_ਖਿੜਕੀ(display, ਅੰਕੜੇ->screen);
    ਜੇ (ਅੰਕੜੇ->ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_ਬੱਚਾ) {
        ਮਾਪਾ_win = windowdata->xwindow;
    } ਨਹੀਂਤਾਂ {
        ਮਾਪਾ_win = ਜੜ੍ਹ_win;
    }

    ਅੰਕੜੇ->ਖਿੜਕੀ = X11_XCreate_ਖਿੜਕੀ(
        display, ਮਾਪਾ_win,
        0, 0,
        ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ, ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ,
        0, ਅੰਕੜੇ->ਡੂੰਘਾਈ_2, ਨਿਵੇਸ਼_Output, ਅੰਕੜੇ->visual,
        valuemask, &wnd_attr);
    ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ == None) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't create X window");
    }

    ਜੇ (windowdata && ਅੰਕੜੇ->ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_DIALOG) {
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
        X11_XChangeProperty(display, ਅੰਕੜੇ->ਖਿੜਕੀ, _NET_WM_STATE, XA_ATOM, 32,
                            Prop_ਬਹੁਲਕ_Replace, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)stateatoms, statecount);
    }

    ਜੇ (windowdata && ਅੰਕੜੇ->ਬਹੁਲਕ != SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_ਬੱਚਾ) {
        X11_XSetTransientForHint(display, ਅੰਕੜੇ->ਖਿੜਕੀ, windowdata->xwindow);
    }

    ਜੇ (ਅੰਕੜੇ->tk_ਮਾਪਾ) {
        X11_XSetTransientForHint(display, ਅੰਕੜੇ->ਖਿੜਕੀ, ਅੰਕੜੇ->tk_ਮਾਪਾ->ਖਿੜਕੀ);
    }

    SDL_X11_ਸੈੱਟ_ਖਿੜਕੀ_Title(display, ਅੰਕੜੇ->ਖਿੜਕੀ, title);

    // Let the window manager the type of the window
    ਜੇ (ਅੰਕੜੇ->ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_DIALOG) {
        NET_WM_ਖਿੜਕੀ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_ਖਿੜਕੀ_TYPE_DIALOG = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
        X11_XChangeProperty(display, ਅੰਕੜੇ->ਖਿੜਕੀ, NET_WM_ਖਿੜਕੀ_TYPE, XA_ATOM, 32,
                            Prop_ਬਹੁਲਕ_Replace,
                            (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)&NET_WM_ਖਿੜਕੀ_TYPE_DIALOG, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_MENU) {
        NET_WM_ਖਿੜਕੀ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_ਖਿੜਕੀ_TYPE_DROPDOWN_MENU = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU", False);
        X11_XChangeProperty(display, ਅੰਕੜੇ->ਖਿੜਕੀ, NET_WM_ਖਿੜਕੀ_TYPE, XA_ATOM, 32,
                            Prop_ਬਹੁਲਕ_Replace,
                            (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)&NET_WM_ਖਿੜਕੀ_TYPE_DROPDOWN_MENU, 1);
    } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕੜੇ->ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_TOOLTIP) {
        NET_WM_ਖਿੜਕੀ_TYPE = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE", False);
        NET_WM_ਖਿੜਕੀ_TYPE_TOOLTIP = X11_XInternAtom(display, "_NET_WM_WINDOW_TYPE_TOOLTIP", False);
        X11_XChangeProperty(display, ਅੰਕੜੇ->ਖਿੜਕੀ, NET_WM_ਖਿੜਕੀ_TYPE, XA_ATOM, 32,
                            Prop_ਬਹੁਲਕ_Replace,
                            (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)&NET_WM_ਖਿੜਕੀ_TYPE_TOOLTIP, 1);
    }

    // Allow the window to be deleted by the window manager
    ਅੰਕੜੇ->wm_delete_ਸੁਨੇਹਾ = X11_XInternAtom(display, "WM_DELETE_WINDOW", False);
    X11_XSetWMProtocols(display, ਅੰਕੜੇ->ਖਿੜਕੀ, &ਅੰਕੜੇ->wm_delete_ਸੁਨੇਹਾ, 1);
    ਅੰਕੜੇ->wm_protocols = X11_XInternAtom(display, "WM_PROTOCOLS", False);

    ਜੇ (ਅੰਕੜੇ->ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_MENU || ਅੰਕੜੇ->ਬਹੁਲਕ== SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_TOOLTIP) {
        x = cx;
        y = cy;
        ਜਾਓ MOVEWINDOW;
    }
    ਜੇ (windowdata) {
        XWindow_ਗੁਣ attrib;
        ਖਿੜਕੀ_2 dummy;

        X11_XGet_ਖਿੜਕੀ_ਗੁਣ(display, windowdata->xwindow, &attrib);
        x = attrib.x + (attrib.ਚੌੜਾਈ - ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ) / 2;
        y = attrib.y + (attrib.ਉਚਾਈ - ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ) / 3;
        X11_XTranslateCoordinates(display, windowdata->xwindow, ਜੜ੍ਹ_ਖਿੜਕੀ(display, ਅੰਕੜੇ->screen), x, y, &x, &y, &dummy);
    } ਨਹੀਂਤਾਂ {
        ਅਚਲ SDL_VideoDevice *dev = SDL_GetVideoDevice();
        ਜੇ (dev && dev->displays && dev->ਅੰਕ_displays > 0) {
            ਅਚਲ SDL_VideoDisplay *dpy = dev->displays[0];
            ਅਚਲ SDL_Display_ਅੰਕੜੇ *dpydata = dpy->ਅੰਦਰੂਨੀ;
            x = dpydata->x + ((dpy->current_ਬਹੁਲਕ->w - ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ) / 2);
            y = dpydata->y + ((dpy->current_ਬਹੁਲਕ->h - ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ) / 3);
        }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
        ਨਹੀਂਤਾਂ ਜੇ (SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, use_xrandr_by_default) && ਅੰਕੜੇ->xrandr) {
            XRRScreenResources *screen_res;
            XRRCrtcInfo *crtc_info;
            RROutput default_ਬਾਹਰਲਾ;

            screen_res = X11_XRRGetScreenResourcesCurrent(display, ਜੜ੍ਹ_win);
            ਜੇ (!screen_res) {
                ਜਾਓ NOXRANDR;
            }

            default_ਬਾਹਰਲਾ = X11_XRRGetOutputPrimary(display, ਜੜ੍ਹ_win);
            ਜੇ (default_ਬਾਹਰਲਾ != None) {
                XRROutputInfo *ਬਾਹਰਲਾ_info;

                ਬਾਹਰਲਾ_info = X11_XRRGetOutputInfo(display, screen_res, default_ਬਾਹਰਲਾ);
                ਜੇ (ਬਾਹਰਲਾ_info->connection != RR_Connected) {
                    X11_XRRFreeOutputInfo(ਬਾਹਰਲਾ_info);
                    ਜਾਓ FIRSTOUTPUTXRANDR;
                }

                ਜੇ (ਬਾਹਰਲਾ_info->crtc != None) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ਬਾਹਰਲਾ_info->crtc);
                } ਨਹੀਂਤਾਂ ਜੇ (ਬਾਹਰਲਾ_info->ncrtc > 0) {
                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ਬਾਹਰਲਾ_info->crtcs[0]);
                } ਨਹੀਂਤਾਂ {
                    crtc_info = ਨਿਰਾ;
                }
                
                ਜੇ (crtc_info) {
                    x = (crtc_info->ਚੌੜਾਈ - ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ) / 2;
                    y = (crtc_info->ਉਚਾਈ - ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ) / 3;
                    X11_XRRFreeOutputInfo(ਬਾਹਰਲਾ_info);
                    X11_XRRFreeCrtcInfo(crtc_info);
                    X11_XRRFreeScreenResources(screen_res);
                } ਨਹੀਂਤਾਂ {
                    X11_XRRFreeOutputInfo(ਬਾਹਰਲਾ_info);
                    ਜਾਓ NOXRANDR;
                }
            } ਨਹੀਂਤਾਂ {
                    FIRSTOUTPUTXRANDR:
                    ਜੇ (screen_res->noutput > 0) {
                        XRROutputInfo *ਬਾਹਰਲਾ_info;

                        ਬਾਹਰਲਾ_info = X11_XRRGetOutputInfo(display, screen_res, screen_res->outputs[0]);
                        ਜੇ (!ਬਾਹਰਲਾ_info) {
                            ਜਾਓ FIRSTCRTCXRANDR;
                        }

                        ਜੇ (ਬਾਹਰਲਾ_info->crtc != None) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ਬਾਹਰਲਾ_info->crtc);
                        } ਨਹੀਂਤਾਂ ਜੇ (ਬਾਹਰਲਾ_info->ncrtc > 0) {
                            crtc_info = X11_XRRGetCrtcInfo(display, screen_res, ਬਾਹਰਲਾ_info->crtcs[0]);
                        } ਨਹੀਂਤਾਂ {
                            crtc_info = ਨਿਰਾ;
                        }

                        ਜੇ (!crtc_info) {
                            X11_XRRFreeOutputInfo(ਬਾਹਰਲਾ_info);
                            ਜਾਓ FIRSTCRTCXRANDR;
                        }

                        x = (crtc_info->ਚੌੜਾਈ - ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ) / 2;
                        y = (crtc_info->ਉਚਾਈ - ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ) / 3;
                        X11_XRRFreeOutputInfo(ਬਾਹਰਲਾ_info);
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                        ਜਾਓ MOVEWINDOW;
                    }

                    FIRSTCRTCXRANDR:
                    ਜੇ (!screen_res->ncrtc) {
                        X11_XRRFreeScreenResources(screen_res);
                        ਜਾਓ NOXRANDR;
                    }

                    crtc_info = X11_XRRGetCrtcInfo(display, screen_res, screen_res->crtcs[0]);
                    ਜੇ (crtc_info) {
                        x = (crtc_info->ਚੌੜਾਈ - ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ) / 2;
                        y = (crtc_info->ਉਚਾਈ - ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ) / 3;
                        X11_XRRFreeCrtcInfo(crtc_info);
                        X11_XRRFreeScreenResources(screen_res);
                    } ਨਹੀਂਤਾਂ {
                        X11_XRRFreeScreenResources(screen_res);
                        ਜਾਓ NOXRANDR;
                    }
            }
        }
#ਜੇ_ਅੰਤ
        ਨਹੀਂਤਾਂ {
            // oh well. This will misposition on a multi-head setup. Init first next time.
            NOXRANDR:
            x = (Display_ਚੌੜਾਈ(display, ਅੰਕੜੇ->screen) - ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ) / 2;
            y = (Display_ਉਚਾਈ(display, ਅੰਕੜੇ->screen) - ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ) / 3;
        }
    }
    MOVEWINDOW:
    X11_XMove_ਖਿੜਕੀ(display, ਅੰਕੜੇ->ਖਿੜਕੀ, x, y);
    ਅੰਕੜੇ->ਖਿੜਕੀ_x = x;
    ਅੰਕੜੇ->ਖਿੜਕੀ_y = y;

    sizehints = X11_XAlloc_ਮਾਪ_Hints();
    ਜੇ (sizehints) {
        sizehints->flags = USPosition | USSize | PMax_ਮਾਪ | PMin_ਮਾਪ;
        sizehints->x = x;
        sizehints->y = y;
        sizehints->ਚੌੜਾਈ = ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ;
        sizehints->ਉਚਾਈ = ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ;

        sizehints->min_ਚੌੜਾਈ_2 = sizehints->max_ਚੌੜਾਈ_2 = ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ;
        sizehints->min_ਉਚਾਈ_2 = sizehints->max_ਉਚਾਈ_2 = ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ;

        X11_XSetWMNormalHints(display, ਅੰਕੜੇ->ਖਿੜਕੀ, sizehints);

        X11_XFree(sizehints);
    }

    X11_XMapRaised(display, ਅੰਕੜੇ->ਖਿੜਕੀ);

    ਅੰਕੜੇ->drawable = ਅੰਕੜੇ->ਖਿੜਕੀ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XDBE
    // Initialise a back buffer for double buffering
    ਜੇ (SDL_X11_HAVE_XDBE && !ਅੰਕੜੇ->pixmap) {
        ਪੂਰਨ xdbe_major, xdbe_minor;
        ਜੇ (X11_XdbeQueryExtension(display, &xdbe_major, &xdbe_minor) != 0) {
            ਅੰਕੜੇ->xdbe = true;
            ਅੰਕੜੇ->buf = X11_Xdbe_Allocate_ਪਿੱਠ_ਬਫਰ_Name(display, ਅੰਕੜੇ->ਖਿੜਕੀ, XdbeUndefined);
            ਅੰਕੜੇ->drawable = ਅੰਕੜੇ->buf;
        } ਨਹੀਂਤਾਂ {
            ਅੰਕੜੇ->xdbe = false;
        }
    }
#ਜੇ_ਅੰਤ

    X11_Toolkit_Init_ਖਿੜਕੀ_Pixmap(ਅੰਕੜੇ);

    SDL_zero(ctx_vals);
    ctx_vals.foreground = ਅੰਕੜੇ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ctx_vals.background = ਅੰਕੜੇ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel;
    ਜੇ (!ਅੰਕੜੇ->utf8) {
        gcflags |= GCFont;
        ctx_vals.font = ਅੰਕੜੇ->font_struct->fid;
    }
    ਅੰਕੜੇ->ctx = X11_XCreateGC(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, gcflags, &ctx_vals);
    ਜੇ (ਅੰਕੜੇ->ctx == None) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't create graphics context");
    }

    ਅੰਕੜੇ->close = false;
    ਅੰਕੜੇ->ਕੁੰਜੀ_control_esc = ਅੰਕੜੇ->ਕੁੰਜੀ_control_enter = ਨਿਰਾ;
    ਜੇ (!ਅੰਕੜੇ->pixmap) {
        ਅੰਕੜੇ->ev_scale = ਅੰਕੜੇ->ev_iscale = 1;
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->ev_scale = ਅੰਕੜੇ->scale;
        ਅੰਕੜੇ->ev_iscale = ਅੰਕੜੇ->iscale;
    }

#ਜੇ SDL_GRAB
    ਜੇ (ਅੰਕੜੇ->ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_MENU || ਅੰਕੜੇ->ਬਹੁਲਕ== SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_TOOLTIP) {
        X11_XGrab_ਸੂਚਕ(display, ਅੰਕੜੇ->ਖਿੜਕੀ, False, Button_Press_ਨਕਾਬ | Button_Release_ਨਕਾਬ | ਸੂਚਕ_Motion_ਨਕਾਬ, Grab_ਬਹੁਲਕ_Async, Grab_ਬਹੁਲਕ_Async, None, None, Current_ਸਮਾਂ);
        X11_XGrabKeyboard(display, ਅੰਕੜੇ->ਖਿੜਕੀ, False, Grab_ਬਹੁਲਕ_Async, Grab_ਬਹੁਲਕ_Async, Current_ਸਮਾਂ);
    }
#ਜੇ_ਅੰਤ

    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ X11_Toolkit_Draw_ਖਿੜਕੀ(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ) {
    SDL_Rect rect;
    ਪੂਰਨ i;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XDBE
    ਜੇ (SDL_X11_HAVE_XDBE && ਅੰਕੜੇ->xdbe && !ਅੰਕੜੇ->pixmap) {
        X11_XdbeBeginIdiom(ਅੰਕੜੇ->display);
    }
#ਜੇ_ਅੰਤ

    X11_XSetForeground(ਅੰਕੜੇ->display, ਅੰਕੜੇ->ctx, ਅੰਕੜੇ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].pixel);
    ਜੇ (ਅੰਕੜੇ->pixmap) {
        X11_XFillRectangle(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->ctx, 0, 0, ਅੰਕੜੇ->pixmap_ਚੌੜਾਈ, ਅੰਕੜੇ->pixmap_ਉਚਾਈ);
    } ਨਹੀਂਤਾਂ {
        X11_XFillRectangle(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->ctx, 0, 0, ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ, ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ);
    }

    ਲਈ (i = 0; i < ਅੰਕੜੇ->controls_sz; i++) {
        SDL_ToolkitControlX11 *control;

        control = ਅੰਕੜੇ->controls[i];
        ਜੇ (control) {
            ਜੇ (control->func_draw) {
                control->func_draw(control);
            }
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XDBE
    ਜੇ (SDL_X11_HAVE_XDBE && ਅੰਕੜੇ->xdbe && !ਅੰਕੜੇ->pixmap) {
        Xdbe_ਅਦਲਾ_ਬਦਲੀ_Info ਅਦਲਾ_ਬਦਲੀ_info;
        ਅਦਲਾ_ਬਦਲੀ_info.ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ = ਅੰਕੜੇ->ਖਿੜਕੀ;
        ਅਦਲਾ_ਬਦਲੀ_info.ਅਦਲਾ_ਬਦਲੀ_action = XdbeUndefined;
        X11_Xdbe_ਅਦਲਾ_ਬਦਲੀ_Buffers(ਅੰਕੜੇ->display, &ਅਦਲਾ_ਬਦਲੀ_info, 1);
        X11_Xdbe_ਸਿਰਾ_Idiom(ਅੰਕੜੇ->display);
    }
#ਜੇ_ਅੰਤ

    ਜੇ (ਅੰਕੜੇ->pixmap) {
        SDL_Surface *scale_surface;

        rect.x = rect.y = 0;
        rect.w = ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ;
        rect.h = ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
        ਜੇ (ਅੰਕੜੇ->shm) {
            ਜੇ (ਅੰਕੜੇ->shm_pixmap) {
                X11_XFlush(ਅੰਕੜੇ->display);
                X11_XSync(ਅੰਕੜੇ->display, false);
                scale_surface = SDL_CreateSurfaceFrom(ਅੰਕੜੇ->pixmap_ਚੌੜਾਈ, ਅੰਕੜੇ->pixmap_ਉਚਾਈ, X11_GetPixelFormatFromVisualInfo(ਅੰਕੜੇ->display, &ਅੰਕੜੇ->vi), ਅੰਕੜੇ->shm_info.shmaddr, ਅੰਕੜੇ->shm_ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਸਤਰ);
                SDL_BlitSurfaceScaled(scale_surface, ਨਿਰਾ, scale_surface, &rect, SDL_SCALEMODE_ਰੇਖਿਕ);
                SDL_DestroySurface(scale_surface);
                X11_XCopyArea(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->ਖਿੜਕੀ, ਅੰਕੜੇ->ctx, 0, 0, ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ, ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ, 0, 0);
            } ਨਹੀਂਤਾਂ {
                X11_XShmGetImage(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, ਅੰਕੜੇ->image, 0, 0, AllPlanes);
                scale_surface = SDL_CreateSurfaceFrom(ਅੰਕੜੇ->pixmap_ਚੌੜਾਈ, ਅੰਕੜੇ->pixmap_ਉਚਾਈ, X11_GetPixelFormatFromVisualInfo(ਅੰਕੜੇ->display, &ਅੰਕੜੇ->vi), ਅੰਕੜੇ->image->ਅੰਕੜੇ, ਅੰਕੜੇ->image->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਸਤਰ);
                SDL_BlitSurfaceScaled(scale_surface, ਨਿਰਾ, scale_surface, &rect, SDL_SCALEMODE_ਰੇਖਿਕ);
                X11_XShmPutImage(ਅੰਕੜੇ->display, ਅੰਕੜੇ->ਖਿੜਕੀ, ਅੰਕੜੇ->ctx, ਅੰਕੜੇ->image, 0, 0, 0, 0, ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ, ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ, False);
            }
        } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
        {
            XImage *image;

            image = X11_XGetImage(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable, 0, 0 , ਅੰਕੜੇ->pixmap_ਚੌੜਾਈ, ਅੰਕੜੇ->pixmap_ਉਚਾਈ, AllPlanes, ZPixmap);
            scale_surface = SDL_CreateSurfaceFrom(ਅੰਕੜੇ->pixmap_ਚੌੜਾਈ, ਅੰਕੜੇ->pixmap_ਉਚਾਈ, X11_GetPixelFormatFromVisualInfo(ਅੰਕੜੇ->display, &ਅੰਕੜੇ->vi), image->ਅੰਕੜੇ, image->ਬਾਈਟਾਂ_ਪ੍ਰਤੀ_ਸਤਰ);
            SDL_BlitSurfaceScaled(scale_surface, ਨਿਰਾ, scale_surface, &rect, SDL_SCALEMODE_ਰੇਖਿਕ);
            X11_XPutImage(ਅੰਕੜੇ->display, ਅੰਕੜੇ->ਖਿੜਕੀ, ਅੰਕੜੇ->ctx, image, 0, 0, 0, 0, ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ, ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ);

            XDestroyImage(image);
            SDL_DestroySurface(scale_surface);
        }
    }

    X11_XFlush(ਅੰਕੜੇ->display);
}

ਸਥਿਰ SDL_ToolkitControlX11 *X11Toolkit_GetControlMouseIsOn(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ, ਪੂਰਨ x, ਪੂਰਨ y)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < ਅੰਕੜੇ->controls_sz; i++) {
        SDL_Rect *rect = &ਅੰਕੜੇ->controls[i]->rect;
        ਜੇ ((x >= rect->x) &&
            (x <= (rect->x + rect->w)) &&
            (y >= rect->y) &&
            (y <= (rect->y + rect->h))) {
            ਵਾਪਸ ਅੰਕੜੇ->controls[i];
        }
    }

    ਵਾਪਸ ਨਿਰਾ;
}

// NOLINTNEXTLINE(readability-non-const-parameter): cannot make XPointer a const pointer due to typedef
ਸਥਿਰ Bool X11Toolkit_EventTest(Display *display, XEvent *event, XPointer arg)
{
    SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ = (SDL_Toolkit_ਖਿੜਕੀ_X11 *)arg;

    ਜੇ (event->xany.display != ਅੰਕੜੇ->display) {
        ਵਾਪਸ False;
    }

    ਜੇ (event->xany.ਖਿੜਕੀ == ਅੰਕੜੇ->ਖਿੜਕੀ) {
        ਵਾਪਸ True;
    }

    ਵਾਪਸ False;
}

ਖਾਲੀ X11_Toolkit_Process_ਖਿੜਕੀ_Events(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ, XEvent *e) {
    /* If X11_XFilterEvent returns True, then some input method has filtered the
        event, and the client should discard the event. */
    ਜੇ ((e->type != Expose) && X11_XFilterEvent(e, None)) {
        ਵਾਪਸ;
    }

    ਅੰਕੜੇ->draw = false;
    ਅੰਕੜੇ->e = e;

    ਚੋਣ (e->type) {
        ਹਾਲਤ Expose:
            ਅੰਕੜੇ->draw = true;
            ਰੋਕੋ;
        ਹਾਲਤ Client_ਸੁਨੇਹਾ:
            ਜੇ (e->xclient.ਸੁਨੇਹਾ_type == ਅੰਕੜੇ->wm_protocols &&
                e->xclient.format == 32 &&
                e->xclient.ਅੰਕੜੇ.l[0] == ਅੰਕੜੇ->wm_delete_ਸੁਨੇਹਾ) {
                ਅੰਕੜੇ->close = true;
            }
            ਰੋਕੋ;
        ਹਾਲਤ Focus_ਵਿੱਚ:
            ਅੰਕੜੇ->has_focus = true;
            ਰੋਕੋ;
        ਹਾਲਤ Focus_ਬਾਹਰਲਾ:
            ਅੰਕੜੇ->has_focus = false;
            ਜੇ (ਅੰਕੜੇ->fiddled_control) {
                ਅੰਕੜੇ->fiddled_control->selected = false;
            }
            ਅੰਕੜੇ->fiddled_control = ਨਿਰਾ;
            ਲਈ (ਅੰਕੜੇ->ev_i = 0; ਅੰਕੜੇ->ev_i < ਅੰਕੜੇ->controls_sz; ਅੰਕੜੇ->ev_i++) {
                ਅੰਕੜੇ->controls[ਅੰਕੜੇ->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_ਸਾਧਾਰਨ;
            }
            ਰੋਕੋ;
        ਹਾਲਤ MotionNotify:
            ਜੇ (ਅੰਕੜੇ->has_focus) {
                ਅੰਕੜੇ->ਪਿਛਲਾ_control = ਅੰਕੜੇ->fiddled_control;
                ਅੰਕੜੇ->fiddled_control = X11Toolkit_GetControlMouseIsOn(ਅੰਕੜੇ, SDL_lroundf((e->xbutton.x/ ਅੰਕੜੇ->ev_scale)* ਅੰਕੜੇ->ev_iscale), SDL_lroundf((e->xbutton.y/ ਅੰਕੜੇ->ev_scale)* ਅੰਕੜੇ->ev_iscale));
                ਜੇ (ਅੰਕੜੇ->ਪਿਛਲਾ_control) {
                    ਅੰਕੜੇ->ਪਿਛਲਾ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ਸਾਧਾਰਨ;
                    ਜੇ (ਅੰਕੜੇ->ਪਿਛਲਾ_control->func_on_state_change) {
                        ਅੰਕੜੇ->ਪਿਛਲਾ_control->func_on_state_change(ਅੰਕੜੇ->ਪਿਛਲਾ_control);
                    }
                    ਅੰਕੜੇ->draw = true;
                }
                ਜੇ (ਅੰਕੜੇ->fiddled_control) {
                    ਜੇ (ਅੰਕੜੇ->fiddled_control->dynamic) {
                        ਅੰਕੜੇ->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_HOVER;
                        ਜੇ (ਅੰਕੜੇ->fiddled_control->func_on_state_change) {
                            ਅੰਕੜੇ->fiddled_control->func_on_state_change(ਅੰਕੜੇ->fiddled_control);
                        }
                        ਅੰਕੜੇ->draw = true;
                    } ਨਹੀਂਤਾਂ {
                        ਅੰਕੜੇ->fiddled_control = ਨਿਰਾ;
                    }
                }
            }
            ਰੋਕੋ;
        ਹਾਲਤ ButtonPress:
            ਅੰਕੜੇ->ਪਿਛਲਾ_control = ਅੰਕੜੇ->fiddled_control;
            ਜੇ (ਅੰਕੜੇ->ਪਿਛਲਾ_control) {
                ਅੰਕੜੇ->ਪਿਛਲਾ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ਸਾਧਾਰਨ;
                ਜੇ (ਅੰਕੜੇ->ਪਿਛਲਾ_control->func_on_state_change) {
                    ਅੰਕੜੇ->ਪਿਛਲਾ_control->func_on_state_change(ਅੰਕੜੇ->ਪਿਛਲਾ_control);
                }
                ਅੰਕੜੇ->draw = true;
            }
            ਜੇ (e->xbutton.button == Button1) {
                ਅੰਕੜੇ->fiddled_control = X11Toolkit_GetControlMouseIsOn(ਅੰਕੜੇ, SDL_lroundf((e->xbutton.x/ ਅੰਕੜੇ->ev_scale)* ਅੰਕੜੇ->ev_iscale), SDL_lroundf((e->xbutton.y/ ਅੰਕੜੇ->ev_scale)* ਅੰਕੜੇ->ev_iscale));
                ਜੇ (ਅੰਕੜੇ->fiddled_control) {
                    ਅੰਕੜੇ->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD;
                    ਜੇ (ਅੰਕੜੇ->fiddled_control->func_on_state_change) {
                        ਅੰਕੜੇ->fiddled_control->func_on_state_change(ਅੰਕੜੇ->fiddled_control);
                    }
                    ਅੰਕੜੇ->draw = true;
                }
            }
            ਰੋਕੋ;
        ਹਾਲਤ ButtonRelease:
            ਜੇ (ਅੰਕੜੇ->ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_MENU || ਅੰਕੜੇ->ਬਹੁਲਕ== SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_TOOLTIP) {
                ਪੂਰਨ cx;
                ਪੂਰਨ cy;

                cx = e->xbutton.x;
                cy = e->xbutton.y;

                ਜੇ (cy < 0 || cx < 0) {
                    ਅੰਕੜੇ->close = true;
                }

                ਜੇ (cy > ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ || cx > ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ) {
                    ਅੰਕੜੇ->close = true;
                }
            }

            ਜੇ ((e->xbutton.button == Button1) && (ਅੰਕੜੇ->fiddled_control)) {
                SDL_ToolkitControlX11 *control;

                control = X11Toolkit_GetControlMouseIsOn(ਅੰਕੜੇ, SDL_lroundf((e->xbutton.x/ ਅੰਕੜੇ->ev_scale)* ਅੰਕੜੇ->ev_iscale), SDL_lroundf((e->xbutton.y/ ਅੰਕੜੇ->ev_scale)* ਅੰਕੜੇ->ev_iscale));
                ਜੇ (ਅੰਕੜੇ->fiddled_control == control) {
                    ਅੰਕੜੇ->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                    ਜੇ (ਅੰਕੜੇ->fiddled_control->func_on_state_change) {
                        ਅੰਕੜੇ->fiddled_control->func_on_state_change(ਅੰਕੜੇ->fiddled_control);
                    }
                    ਅੰਕੜੇ->fiddled_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ਸਾਧਾਰਨ;
                    ਅੰਕੜੇ->draw = true;
                }
            }
            ਰੋਕੋ;
        ਹਾਲਤ ਕੁੰਜੀ_Press:
            ਅੰਕੜੇ->ਆਖਰੀ_ਕੁੰਜੀ_pressed = X11_XLookupKeysym(&e->xkey, 0);

            ਜੇ (ਅੰਕੜੇ->ਆਖਰੀ_ਕੁੰਜੀ_pressed == XK_Escape) {
                ਲਈ (ਅੰਕੜੇ->ev_i = 0; ਅੰਕੜੇ->ev_i < ਅੰਕੜੇ->controls_sz; ਅੰਕੜੇ->ev_i++) {
                    ਜੇ(ਅੰਕੜੇ->controls[ਅੰਕੜੇ->ev_i]->is_default_esc) {
                        ਅੰਕੜੇ->controls[ਅੰਕੜੇ->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        ਅੰਕੜੇ->draw = true;
                        ਅੰਕੜੇ->ਕੁੰਜੀ_control_esc = ਅੰਕੜੇ->controls[ਅੰਕੜੇ->ev_i];
                    }
                }
            } ਨਹੀਂਤਾਂ ਜੇ ((ਅੰਕੜੇ->ਆਖਰੀ_ਕੁੰਜੀ_pressed == XK_Return) || (ਅੰਕੜੇ->ਆਖਰੀ_ਕੁੰਜੀ_pressed == XK_KP_Enter)) {
                ਲਈ (ਅੰਕੜੇ->ev_i = 0; ਅੰਕੜੇ->ev_i < ਅੰਕੜੇ->controls_sz; ਅੰਕੜੇ->ev_i++) {
                    ਜੇ(ਅੰਕੜੇ->controls[ਅੰਕੜੇ->ev_i]->selected) {
                        ਅੰਕੜੇ->controls[ਅੰਕੜੇ->ev_i]->state = SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED;
                        ਅੰਕੜੇ->draw = true;
                        ਅੰਕੜੇ->ਕੁੰਜੀ_control_enter = ਅੰਕੜੇ->controls[ਅੰਕੜੇ->ev_i];
                    }
                }
            }
            ਰੋਕੋ;
        ਹਾਲਤ ਕੁੰਜੀ_Release:
        {
            ਕੁੰਜੀ_Sym ਕੁੰਜੀ = X11_XLookupKeysym(&e->xkey, 0);

            // If this is a key release for something we didn't get the key down for, then bail.
            ਜੇ (ਕੁੰਜੀ != ਅੰਕੜੇ->ਆਖਰੀ_ਕੁੰਜੀ_pressed) {
                ਰੋਕੋ;
            }

            ਜੇ (ਕੁੰਜੀ == XK_Escape) {
                ਜੇ (ਅੰਕੜੇ->ਕੁੰਜੀ_control_esc) {
                    ਜੇ (ਅੰਕੜੇ->ਕੁੰਜੀ_control_esc->func_on_state_change) {
                        ਅੰਕੜੇ->ਕੁੰਜੀ_control_esc->func_on_state_change(ਅੰਕੜੇ->ਕੁੰਜੀ_control_esc);
                    }
                }
            } ਨਹੀਂਤਾਂ ਜੇ ((ਕੁੰਜੀ == XK_Return) || (ਕੁੰਜੀ == XK_KP_Enter)) {
                ਜੇ (ਅੰਕੜੇ->ਕੁੰਜੀ_control_enter) {
                    ਜੇ (ਅੰਕੜੇ->ਕੁੰਜੀ_control_enter->func_on_state_change) {
                        ਅੰਕੜੇ->ਕੁੰਜੀ_control_enter->func_on_state_change(ਅੰਕੜੇ->ਕੁੰਜੀ_control_enter);
                    }
                }
            } ਨਹੀਂਤਾਂ ਜੇ (ਕੁੰਜੀ == XK_Tab || ਕੁੰਜੀ == XK_ਖੱਬਾ || ਕੁੰਜੀ == XK_ਸੱਜਾ) {
                ਜੇ (ਅੰਕੜੇ->focused_control) {
                    ਅੰਕੜੇ->focused_control->selected = false;
                }
                ਅੰਕੜੇ->draw = true;
                ਲਈ (ਅੰਕੜੇ->ev_i = 0; ਅੰਕੜੇ->ev_i < ਅੰਕੜੇ->dyn_controls_sz; ਅੰਕੜੇ->ev_i++) {
                    ਜੇ (ਅੰਕੜੇ->dyn_controls[ਅੰਕੜੇ->ev_i] == ਅੰਕੜੇ->focused_control) {
                        ਪੂਰਨ ਅਗਲਾ_ਸੂਚਕਾਂਕ;

                        ਜੇ (ਕੁੰਜੀ == XK_ਖੱਬਾ) {
                            ਅਗਲਾ_ਸੂਚਕਾਂਕ = ਅੰਕੜੇ->ev_i - 1;
                        } ਨਹੀਂਤਾਂ {
                            ਅਗਲਾ_ਸੂਚਕਾਂਕ = ਅੰਕੜੇ->ev_i + 1;
                        }
                        ਜੇ ((ਅਗਲਾ_ਸੂਚਕਾਂਕ >= ਅੰਕੜੇ->dyn_controls_sz) || (ਅਗਲਾ_ਸੂਚਕਾਂਕ < 0)) {
                            ਜੇ (ਕੁੰਜੀ == XK_ਸੱਜਾ || ਕੁੰਜੀ == XK_ਖੱਬਾ) {
                                ਅਗਲਾ_ਸੂਚਕਾਂਕ = ਅੰਕੜੇ->ev_i;
                            } ਨਹੀਂਤਾਂ {
                                ਅਗਲਾ_ਸੂਚਕਾਂਕ = 0;
                            }
                        }
                        ਅੰਕੜੇ->focused_control = ਅੰਕੜੇ->dyn_controls[ਅਗਲਾ_ਸੂਚਕਾਂਕ];
                        ਅੰਕੜੇ->focused_control->selected = true;
                        ਰੋਕੋ;
                    }
                }
            }
            ਰੋਕੋ;
        }
    }

    ਜੇ (ਅੰਕੜੇ->draw) {
        X11_Toolkit_Draw_ਖਿੜਕੀ(ਅੰਕੜੇ);
    }
}

ਖਾਲੀ X11_Toolkit_Do_ਖਿੜਕੀ_Event_Loop(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ) {
   ਜਦੋਂ (!ਅੰਕੜੇ->close) {
        XEvent e;

        /* Process settings events */
        X11_XPeekEvent(ਅੰਕੜੇ->display, &e);
        ਜੇ (ਅੰਕੜੇ->xsettings) {
            xsettings_client_process_event(ਅੰਕੜੇ->xsettings, &e);
        }

        /* Do actual event loop */
        X11_XIfEvent(ਅੰਕੜੇ->display, &e, X11Toolkit_EventTest, (XPointer)ਅੰਕੜੇ);
        X11_Toolkit_Process_ਖਿੜਕੀ_Events(ਅੰਕੜੇ, &e);
    }
}


ਖਾਲੀ X11_Toolkit_Resize_ਖਿੜਕੀ(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ, ਪੂਰਨ w, ਪੂਰਨ h) {
    ਜੇ (!ਅੰਕੜੇ->pixmap) {
        ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ = w;
        ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ = h;
    } ਨਹੀਂਤਾਂ {
        ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ = SDL_lroundf((w/ਅੰਕੜੇ->iscale) * ਅੰਕੜੇ->scale);
        ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ = SDL_lroundf((h/ਅੰਕੜੇ->iscale) * ਅੰਕੜੇ->scale);
        ਅੰਕੜੇ->pixmap_ਚੌੜਾਈ = w;
        ਅੰਕੜੇ->pixmap_ਉਚਾਈ = h;
        X11_XFreePixmap(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable);
        X11_Toolkit_Init_ਖਿੜਕੀ_Pixmap(ਅੰਕੜੇ);
    }

    X11_XResize_ਖਿੜਕੀ(ਅੰਕੜੇ->display, ਅੰਕੜੇ->ਖਿੜਕੀ, ਅੰਕੜੇ->ਖਿੜਕੀ_ਚੌੜਾਈ, ਅੰਕੜੇ->ਖਿੜਕੀ_ਉਚਾਈ);
}

ਸਥਿਰ ਖਾਲੀ X11Toolkit_DestroyIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    X11_XFreeFont(control->ਖਿੜਕੀ->display, icon_control->icon_char_font);
    SDL_free(control);
}

ਸਥਿਰ ਖਾਲੀ X11Toolkit_DrawIconControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitIconControlX11 *icon_control;

    icon_control = (SDL_ToolkitIconControlX11 *)control;
    control->rect.w -= 2 * control->ਖਿੜਕੀ->iscale;
    control->rect.h -= 2 * control->ਖਿੜਕੀ->iscale;
    X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, icon_control->xcolor_bg_shadow.pixel);
    X11_XFillArc(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx, control->rect.x + (2 * control->ਖਿੜਕੀ->iscale), control->rect.y + (2* control->ਖਿੜਕੀ->iscale), control->rect.w, control->rect.h, 0, 360 * 64);

    ਚੋਣ (icon_control->flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
        ਹਾਲਤ SDL_MESSAGEBOX_ERROR:
                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, icon_control->xcolor_red_darker.pixel);
                X11_XFillArc(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, icon_control->xcolor_red.pixel);
                X11_XFillArc(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx, control->rect.x+(1* control->ਖਿੜਕੀ->iscale), control->rect.y+(1* control->ਖਿੜਕੀ->iscale), control->rect.w-(2* control->ਖਿੜਕੀ->iscale), control->rect.h-(2* control->ਖਿੜਕੀ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, icon_control->xcolor_white.pixel);
                ਰੋਕੋ;
        ਹਾਲਤ SDL_MESSAGEBOX_WARNING:
                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, icon_control->xcolor_black.pixel);
                X11_XFillArc(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, icon_control->xcolor_yellow.pixel);
                X11_XFillArc(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx, control->rect.x+(1* control->ਖਿੜਕੀ->iscale), control->rect.y+(1* control->ਖਿੜਕੀ->iscale), control->rect.w-(2* control->ਖਿੜਕੀ->iscale), control->rect.h-(2* control->ਖਿੜਕੀ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, icon_control->xcolor_black.pixel);
                ਰੋਕੋ;
        ਹਾਲਤ SDL_MESSAGEBOX_INFORMATION:
                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, icon_control->xcolor_white.pixel);
                X11_XFillArc(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx, control->rect.x, control->rect.y, control->rect.w, control->rect.h, 0, 360 * 64);
                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, icon_control->xcolor_blue.pixel);
                X11_XFillArc(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx, control->rect.x+(1* control->ਖਿੜਕੀ->iscale), control->rect.y+(1* control->ਖਿੜਕੀ->iscale), control->rect.w-(2* control->ਖਿੜਕੀ->iscale), control->rect.h-(2* control->ਖਿੜਕੀ->iscale), 0, 360 * 64);
                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, icon_control->xcolor_white.pixel);
                ਰੋਕੋ;
    }
    X11_XSetFont(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, icon_control->icon_char_font->fid);
    X11_XDrawString(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx, control->rect.x + icon_control->icon_char_x, control->rect.y + icon_control->icon_char_y, &icon_control->icon_char, 1);
    ਜੇ (!control->ਖਿੜਕੀ->utf8) {
        X11_XSetFont(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->font_struct->fid);
    }

    control->rect.w += 2 * control->ਖਿੜਕੀ->iscale;
    control->rect.h += 2 * control->ਖਿੜਕੀ->iscale;
}

ਸਥਿਰ ਖਾਲੀ X11Toolkit_CalculateIconControl(SDL_ToolkitControlX11 *ਅਧਾਰ_control) {
    SDL_ToolkitIconControlX11 *control;
    ਪੂਰਨ icon_char_w;
    ਪੂਰਨ icon_wh;

    control = (SDL_ToolkitIconControlX11 *)ਅਧਾਰ_control;
    X11_Toolkit_Get_ਪਾਠ_ਚੌੜਾਈ_ਉਚਾਈ_For_Font(control->icon_char_font, &control->icon_char, 1, &icon_char_w, &control->icon_char_h, &control->icon_char_a, ਨਿਰਾ);
    ਅਧਾਰ_control->rect.w = icon_char_w;
    ਅਧਾਰ_control->rect.h = control->icon_char_h;
    icon_wh = SDL_max(icon_char_w, control->icon_char_h) + SDL_TOOLKIT_X11_ELEMENT_PADDING * 2 * ਅਧਾਰ_control->ਖਿੜਕੀ->iscale;
    ਅਧਾਰ_control->rect.w = icon_wh;
    ਅਧਾਰ_control->rect.h = icon_wh;
    ਅਧਾਰ_control->rect.y = 0;
    ਅਧਾਰ_control->rect.x = 0;
    control->icon_char_y = control->icon_char_a + (ਅਧਾਰ_control->rect.h - control->icon_char_h)/2;
    control->icon_char_x = (ਅਧਾਰ_control->rect.w - icon_char_w)/2;
    ਅਧਾਰ_control->rect.w += 2 * ਅਧਾਰ_control->ਖਿੜਕੀ->iscale;
    ਅਧਾਰ_control->rect.h += 2 * ਅਧਾਰ_control->ਖਿੜਕੀ->iscale;
}

ਸਥਿਰ ਖਾਲੀ X11Toolkit_OnIconControlScaleChange(SDL_ToolkitControlX11 *ਅਧਾਰ_control) {
    SDL_ToolkitIconControlX11 *control;
    ਅੱਖਰ *font;

    control = (SDL_ToolkitIconControlX11 *)ਅਧਾਰ_control;
    X11_XFreeFont(ਅਧਾਰ_control->ਖਿੜਕੀ->display, control->icon_char_font);
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_ਮਾਪ * ਅਧਾਰ_control->ਖਿੜਕੀ->iscale);
    control->icon_char_font = X11_XLoadQueryFont(ਅਧਾਰ_control->ਖਿੜਕੀ->display, font);
    SDL_free(font);
    ਜੇ (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_ਮਾਪ * ਅਧਾਰ_control->ਖਿੜਕੀ->iscale);
        control->icon_char_font = X11_XLoadQueryFont(ਅਧਾਰ_control->ਖਿੜਕੀ->display, font);
        SDL_free(font);
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateIconControl(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ, SDL_ਸੁਨੇਹਾ_Box_Flags flags) {
    SDL_ToolkitIconControlX11 *control;
    SDL_ToolkitControlX11 *ਅਧਾਰ_control;
    ਅੱਖਰ *font;

    /* Create control struct */
    control = (SDL_ToolkitIconControlX11 *)SDL_malloc(ਆਕਾਰ(SDL_ToolkitIconControlX11));
    ਅਧਾਰ_control = (SDL_ToolkitControlX11 *)control;
    ਜੇ (!control) {
        SDL_ਸੈੱਟ_Error("Unable to allocate icon control structure");
        ਵਾਪਸ ਨਿਰਾ;
    }

    /* Fill out struct */
    ਅਧਾਰ_control->ਖਿੜਕੀ = ਖਿੜਕੀ;
    ਅਧਾਰ_control->func_draw = X11Toolkit_DrawIconControl;
    ਅਧਾਰ_control->func_free = X11Toolkit_DestroyIconControl;
    ਅਧਾਰ_control->func_on_state_change = ਨਿਰਾ;
    ਅਧਾਰ_control->func_calc_ਮਾਪ = X11Toolkit_CalculateIconControl;
    ਅਧਾਰ_control->func_on_scale_change = X11Toolkit_OnIconControlScaleChange;
    ਅਧਾਰ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ਸਾਧਾਰਨ;
    ਅਧਾਰ_control->selected = false;
    ਅਧਾਰ_control->dynamic = false;
    ਅਧਾਰ_control->is_default_enter = false;
    ਅਧਾਰ_control->is_default_esc = false;
    control->flags = flags;

    /* Load font */
    SDL_asprintf(&font, g_IconFont, G_ICONFONT_ਮਾਪ * ਖਿੜਕੀ->iscale);
    control->icon_char_font = X11_XLoadQueryFont(ਖਿੜਕੀ->display, font);
    SDL_free(font);
    ਜੇ (!control->icon_char_font) {
        SDL_asprintf(&font, g_ToolkitFontLatin1, G_TOOLKITFONT_ਮਾਪ * ਖਿੜਕੀ->iscale);
        control->icon_char_font = X11_XLoadQueryFont(ਖਿੜਕੀ->display, font);
        SDL_free(font);
        ਜੇ (!control->icon_char_font) {
            SDL_free(control);
            ਵਾਪਸ ਨਿਰਾ;
        }
    }

    /* Set colors */
    ਚੋਣ (flags & (SDL_MESSAGEBOX_ERROR | SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_INFORMATION)) {
    ਹਾਲਤ SDL_MESSAGEBOX_ERROR:
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
        X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &control->xcolor_white);
        X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &control->xcolor_red);
        X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &control->xcolor_red_darker);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_MESSAGEBOX_WARNING:
        control->icon_char = '!';
        control->xcolor_black.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_black.red = 0;
        control->xcolor_black.green = 0;
        control->xcolor_black.blue = 0;
        control->xcolor_yellow.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_yellow.red = 65535;
        control->xcolor_yellow.green = 65535;
        control->xcolor_yellow.blue = 0;
        X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &control->xcolor_black);
        X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &control->xcolor_yellow);
        ਰੋਕੋ;
    ਹਾਲਤ SDL_MESSAGEBOX_INFORMATION:
        control->icon_char = 'i';
        control->xcolor_white.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_white.red = 65535;
        control->xcolor_white.green = 65535;
        control->xcolor_white.blue = 65535;
        control->xcolor_blue.flags = DoRed|DoGreen|DoBlue;
        control->xcolor_blue.red = 0;
        control->xcolor_blue.green = 0;
        control->xcolor_blue.blue = 65535;
        X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &control->xcolor_white);
        X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &control->xcolor_blue);
        ਰੋਕੋ;
    ਮੂਲ:
        X11_XFreeFont(ਖਿੜਕੀ->display, control->icon_char_font);
        SDL_free(control);
        ਵਾਪਸ ਨਿਰਾ;
    }
    control->xcolor_bg_shadow.flags = DoRed|DoGreen|DoBlue;
    ਜੇ (ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red > 32896) {
        control->xcolor_bg_shadow.red = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 12500, 0, 65535);
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red == 0) {
        control->xcolor_bg_shadow.red = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red + 9000, 0, 65535);
    } ਨਹੀਂਤਾਂ {
        control->xcolor_bg_shadow.red = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].red - 3000, 0, 65535);
    }

    ਜੇ (ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green > 32896) {
        control->xcolor_bg_shadow.green = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 12500, 0, 65535);
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green == 0) {
        control->xcolor_bg_shadow.green = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green + 9000, 0, 65535);
    } ਨਹੀਂਤਾਂ {
        control->xcolor_bg_shadow.green = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].green - 3000, 0, 65535);
    }

    ਜੇ (ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue > 32896) {
        control->xcolor_bg_shadow.blue = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 12500, 0, 65535);
    } ਨਹੀਂਤਾਂ ਜੇ (ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue == 0) {
        control->xcolor_bg_shadow.blue = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue + 9000, 0, 65535);
    } ਨਹੀਂਤਾਂ {
        control->xcolor_bg_shadow.blue = SDL_clamp(ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BACKGROUND].blue - 3000, 0, 65535);
    }
    X11_XAllocColor(ਖਿੜਕੀ->display, ਖਿੜਕੀ->cmap, &control->xcolor_bg_shadow);

    /* Sizing and positioning */
    X11Toolkit_CalculateIconControl(ਅਧਾਰ_control);

    X11_Toolkit_ਜੋੜੋ_Control_ਮੰਜ਼ਿਲ_ਖਿੜਕੀ(ਖਿੜਕੀ, ਅਧਾਰ_control);
    ਵਾਪਸ ਅਧਾਰ_control;
}

bool X11_Toolkit_Notify_Control_ਦਾ_ਮਾਪ_Change(SDL_ToolkitControlX11 *control) {
    ਜੇ (control->func_calc_ਮਾਪ) {
        control->func_calc_ਮਾਪ(control);
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ false;
    }
}

ਸਥਿਰ ਖਾਲੀ X11Toolkit_CalculateButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    X11_Toolkit_Get_ਪਾਠ_Elements_Rect(button_control->ਪਾਠ, &button_control->ਪਾਠ_rect);
    ਜੇ (control->do_ਮਾਪ) {
        control->rect.w = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->ਖਿੜਕੀ->iscale + button_control->ਪਾਠ_rect.w;
        control->rect.h = SDL_TOOLKIT_X11_ELEMENT_PADDING_3 * 2 * control->ਖਿੜਕੀ->iscale + button_control->ਪਾਠ_rect.h;
    }
    button_control->ਪਾਠ_rect.x = (control->rect.w - button_control->ਪਾਠ_rect.w)/2;
    button_control->ਪਾਠ_rect.y = (control->rect.h - button_control->ਪਾਠ_rect.h)/2;
}


ਸਥਿਰ ਖਾਲੀ X11Toolkit_DrawButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_ਪਾਠ].pixel);
    /* Draw bevel */
    ਜੇ (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED || control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED_HELD) {
            X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor_bevel_d.pixel);
            X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

            X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor_bevel_l2.pixel);
            X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - (1* control->ਖਿੜਕੀ->iscale), control->rect.h - (1* control->ਖਿੜਕੀ->iscale));

            X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor_bevel_l1.pixel);
            X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x + 1 * control->ਖਿੜਕੀ->iscale, control->rect.y + 1 * control->ਖਿੜਕੀ->iscale,
                                   control->rect.w - 3 * control->ਖਿੜਕੀ->iscale, control->rect.h - 2 * control->ਖਿੜਕੀ->iscale);

            X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
            X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                               control->rect.x + 1 * control->ਖਿੜਕੀ->iscale, control->rect.y + 1 * control->ਖਿੜਕੀ->iscale,
                               control->rect.w - 3 * control->ਖਿੜਕੀ->iscale, control->rect.h - 3 * control->ਖਿੜਕੀ->iscale);

            X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor_pressed.pixel);
            X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                               control->rect.x + 2 * control->ਖਿੜਕੀ->iscale, control->rect.y + 2 * control->ਖਿੜਕੀ->iscale,
                               control->rect.w - 4 * control->ਖਿੜਕੀ->iscale, control->rect.h - 4 * control->ਖਿੜਕੀ->iscale);
        } ਨਹੀਂਤਾਂ {
            ਜੇ (control->selected) {
                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x + 1 * control->ਖਿੜਕੀ->iscale, control->rect.y + 1 * control->ਖਿੜਕੀ->iscale,
                                   control->rect.w - 3 * control->ਖਿੜਕੀ->iscale, control->rect.h - 3 * control->ਖਿੜਕੀ->iscale);

                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x + 2 * control->ਖਿੜਕੀ->iscale, control->rect.y + 2 * control->ਖਿੜਕੀ->iscale,
                                   control->rect.w - 4 * control->ਖਿੜਕੀ->iscale, control->rect.h - 4 * control->ਖਿੜਕੀ->iscale);

                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x + 2 * control->ਖਿੜਕੀ->iscale, control->rect.y + 2 * control->ਖਿੜਕੀ->iscale,
                                   control->rect.w - 5 * control->ਖਿੜਕੀ->iscale, control->rect.h - 5 * control->ਖਿੜਕੀ->iscale);

                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x + 3 * control->ਖਿੜਕੀ->iscale, control->rect.y + 3 * control->ਖਿੜਕੀ->iscale,
                                   control->rect.w - 6 * control->ਖਿੜਕੀ->iscale, control->rect.h - 6 * control->ਖਿੜਕੀ->iscale);
            } ਨਹੀਂਤਾਂ {
                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor_bevel_d.pixel);
                X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w, control->rect.h);

                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor_bevel_l2.pixel);
                X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x, control->rect.y,
                                   control->rect.w - 1 * control->ਖਿੜਕੀ->iscale, control->rect.h - 1 * control->ਖਿੜਕੀ->iscale);

                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER].pixel);
                X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x + 1 * control->ਖਿੜਕੀ->iscale, control->rect.y + 1 * control->ਖਿੜਕੀ->iscale,
                                   control->rect.w - 2 * control->ਖਿੜਕੀ->iscale, control->rect.h - 2 * control->ਖਿੜਕੀ->iscale);

                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor_bevel_l1.pixel);
                X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x + 1 * control->ਖਿੜਕੀ->iscale, control->rect.y + 1 * control->ਖਿੜਕੀ->iscale,
                                   control->rect.w - 3 * control->ਖਿੜਕੀ->iscale, control->rect.h - 3 * control->ਖਿੜਕੀ->iscale);

                X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, (control->state == SDL_TOOLKIT_CONTROL_STATE_X11_HOVER) ? control->ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED].pixel : control->ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND].pixel);
                X11_XFillRectangle(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->drawable, control->ਖਿੜਕੀ->ctx,
                                   control->rect.x + 2 * control->ਖਿੜਕੀ->iscale, control->rect.y + 2 * control->ਖਿੜਕੀ->iscale,
                                   control->rect.w - 4 * control->ਖਿੜਕੀ->iscale, control->rect.h - 4 * control->ਖਿੜਕੀ->iscale);
            }
        }

    X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_ਪਾਠ].pixel);
    X11_Toolkit_Draw_ਪਾਠ_Elements(control->ਖਿੜਕੀ, button_control->ਪਾਠ, control->rect.x + button_control->ਪਾਠ_rect.x, control->rect.y + button_control->ਪਾਠ_rect.y);
}

ਸਥਿਰ ਖਾਲੀ X11Toolkit_OnButtonControlStateChange(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    ਜੇ (button_control->cb && control->state == SDL_TOOLKIT_CONTROL_STATE_X11_PRESSED) {
        button_control->cb(control, button_control->cb_ਅੰਕੜੇ);
    }
}

ਸਥਿਰ ਖਾਲੀ X11Toolkit_DestroyButtonControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;

    X11_Toolkit_Free_ਪਾਠ_Elements(button_control->ਪਾਠ);
    
    SDL_free(control);
}

SDL_ToolkitControlX11 *X11Toolkit_CreateButtonControl(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ, ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ *ਅੰਕੜੇ) {
    SDL_ToolkitButtonControlX11 *control;
    SDL_ToolkitControlX11 *ਅਧਾਰ_control;

    control = (SDL_ToolkitButtonControlX11 *)SDL_malloc(ਆਕਾਰ(SDL_ToolkitButtonControlX11));
    ਅਧਾਰ_control = (SDL_ToolkitControlX11 *)control;
    ਜੇ (!control) {
        SDL_ਸੈੱਟ_Error("Unable to allocate button control structure");
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਅਧਾਰ_control->ਖਿੜਕੀ = ਖਿੜਕੀ;
    ਅਧਾਰ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ਸਾਧਾਰਨ;
    ਅਧਾਰ_control->func_calc_ਮਾਪ = X11Toolkit_CalculateButtonControl;
    ਅਧਾਰ_control->func_draw = X11Toolkit_DrawButtonControl;
    ਅਧਾਰ_control->func_on_state_change = X11Toolkit_OnButtonControlStateChange;
    ਅਧਾਰ_control->func_free = X11Toolkit_DestroyButtonControl;
    ਅਧਾਰ_control->func_on_scale_change = ਨਿਰਾ;
    ਅਧਾਰ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ਸਾਧਾਰਨ;
    ਅਧਾਰ_control->selected = false;
    ਅਧਾਰ_control->dynamic = true;
    ਅਧਾਰ_control->is_default_enter = false;
    ਅਧਾਰ_control->is_default_esc = false;
    ਜੇ (ਅੰਕੜੇ->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
        ਅਧਾਰ_control->is_default_esc = true;
    }
    ਜੇ (ਅੰਕੜੇ->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
        ਅਧਾਰ_control->is_default_enter = true;
        ਅਧਾਰ_control->selected = true;
    }
    control->cb = ਨਿਰਾ;
    control->ਅੰਕੜੇ = ਅੰਕੜੇ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
    control->ਪਾਠ = X11_Toolkit_Make_ਪਾਠ_Elements(ਅਧਾਰ_control->ਖਿੜਕੀ, (ਅੱਖਰ *)control->ਅੰਕੜੇ->ਪਾਠ, SDL_strlen(control->ਅੰਕੜੇ->ਪਾਠ), ਨਿਰਾ);
#ਨਹੀਂਤਾਂ 
    control->ਪਾਠ = X11_Toolkit_Make_ਪਾਠ_Elements(ਅਧਾਰ_control->ਖਿੜਕੀ, (ਅੱਖਰ *)control->ਅੰਕੜੇ->ਪਾਠ, SDL_strlen(control->ਅੰਕੜੇ->ਪਾਠ));
#ਜੇ_ਅੰਤ
    X11_Toolkit_Shape_ਪਾਠ_Elements(ਅਧਾਰ_control->ਖਿੜਕੀ, control->ਪਾਠ);
    
    ਅਧਾਰ_control->do_ਮਾਪ = true;
    X11Toolkit_CalculateButtonControl(ਅਧਾਰ_control);
    ਅਧਾਰ_control->do_ਮਾਪ = false;

    X11_Toolkit_ਜੋੜੋ_Control_ਮੰਜ਼ਿਲ_ਖਿੜਕੀ(ਖਿੜਕੀ, ਅਧਾਰ_control);
    ਵਾਪਸ ਅਧਾਰ_control;
}

ਖਾਲੀ X11_Toolkit_ਰਜਿਸਟਰ_Callback_For_Button_Control(SDL_ToolkitControlX11 *control, ਖਾਲੀ *ਅੰਕੜੇ, ਖਾਲੀ (*cb)(ਬਣਤਰ SDL_ToolkitControlX11 *, ਖਾਲੀ *)) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    button_control->cb_ਅੰਕੜੇ = ਅੰਕੜੇ;
    button_control->cb = cb;
}

ਅਚਲ SDL_ਸੁਨੇਹਾ_Box_Button_ਅੰਕੜੇ *X11_Toolkit_Get_Button_Control_ਅੰਕੜੇ(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitButtonControlX11 *button_control;

    button_control = (SDL_ToolkitButtonControlX11 *)control;
    ਵਾਪਸ button_control->ਅੰਕੜੇ;
}

ਖਾਲੀ X11_Toolkit_Destroy_ਖਿੜਕੀ(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ) {
    ਪੂਰਨ i;

    ਜੇ (!ਅੰਕੜੇ) {
        ਵਾਪਸ;
    }

#ਜੇ SDL_GRAB
    ਜੇ (ਅੰਕੜੇ->ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_MENU || ਅੰਕੜੇ->ਬਹੁਲਕ== SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_TOOLTIP) {
        X11_XUngrab_ਸੂਚਕ(ਅੰਕੜੇ->display, Current_ਸਮਾਂ);
        X11_XUngrabKeyboard(ਅੰਕੜੇ->display, Current_ਸਮਾਂ);
    }
#ਜੇ_ਅੰਤ

    ਲਈ (i = 0; i < ਅੰਕੜੇ->controls_sz; i++) {
        ਜੇ (ਅੰਕੜੇ->controls[i]->func_free) {
            ਅੰਕੜੇ->controls[i]->func_free(ਅੰਕੜੇ->controls[i]);
        }
    }
    SDL_free(ਅੰਕੜੇ->controls);
    SDL_free(ਅੰਕੜੇ->dyn_controls);

    ਜੇ (ਅੰਕੜੇ->popup_windows) {
        SDL_ListClear(&ਅੰਕੜੇ->popup_windows);
    }

    ਜੇ (ਅੰਕੜੇ->pixmap) {
        X11_XFreePixmap(ਅੰਕੜੇ->display, ਅੰਕੜੇ->drawable);
    }

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
    ਜੇ (ਅੰਕੜੇ->pixmap && ਅੰਕੜੇ->shm) {
        X11_XShmDetach(ਅੰਕੜੇ->display, &ਅੰਕੜੇ->shm_info);
        ਜੇ (!ਅੰਕੜੇ->shm_pixmap) {
            XDestroyImage(ਅੰਕੜੇ->image);
        }
        shmdt(ਅੰਕੜੇ->shm_info.shmaddr);
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X_HAVE_UTF8_STRING
    ਜੇ (ਅੰਕੜੇ->font_ਸੈੱਟ) {
        X11_XFree_Font_ਸੈੱਟ(ਅੰਕੜੇ->display, ਅੰਕੜੇ->font_ਸੈੱਟ);
        ਅੰਕੜੇ->font_ਸੈੱਟ = ਨਿਰਾ;
    }
#ਜੇ_ਅੰਤ

    ਜੇ (ਅੰਕੜੇ->font_struct) {
        X11_XFreeFont(ਅੰਕੜੇ->display, ਅੰਕੜੇ->font_struct);
        ਅੰਕੜੇ->font_struct = ਨਿਰਾ;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XDBE
    ਜੇ (SDL_X11_HAVE_XDBE && ਅੰਕੜੇ->xdbe && !ਅੰਕੜੇ->pixmap) {
        X11_Xdbe_Deallocate_ਪਿੱਠ_ਬਫਰ_Name(ਅੰਕੜੇ->display, ਅੰਕੜੇ->buf);
    }
#ਜੇ_ਅੰਤ

    ਜੇ (ਅੰਕੜੇ->xsettings) {
        xsettings_client_destroy(ਅੰਕੜੇ->xsettings);
    }

    X11_XFreeGC(ਅੰਕੜੇ->display, ਅੰਕੜੇ->ctx);

    ਜੇ (ਅੰਕੜੇ->display) {
        ਜੇ (ਅੰਕੜੇ->ਖਿੜਕੀ != None) {
            X11_XWithdraw_ਖਿੜਕੀ(ਅੰਕੜੇ->display, ਅੰਕੜੇ->ਖਿੜਕੀ, ਅੰਕੜੇ->screen);
            X11_XDestroy_ਖਿੜਕੀ(ਅੰਕੜੇ->display, ਅੰਕੜੇ->ਖਿੜਕੀ);
            ਅੰਕੜੇ->ਖਿੜਕੀ = None;
        }

        ਜੇ (ਅੰਕੜੇ->display_close) {
            X11_XCloseDisplay(ਅੰਕੜੇ->display);
        }
        ਅੰਕੜੇ->display = ਨਿਰਾ;
    }

#ਜੇ SDL_ਸੈੱਟ_LOCALE
    ਜੇ (ਅੰਕੜੇ->origlocale && (ਅੰਕੜੇ->ਬਹੁਲਕ == SDL_TOOLKIT_ਖਿੜਕੀ_ਬਹੁਲਕ_X11_DIALOG)) {
        (ਖਾਲੀ)setlocale(LC_ALL, ਅੰਕੜੇ->origlocale);
        SDL_free(ਅੰਕੜੇ->origlocale);
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
    SDL_FriBidi_Destroy(ਅੰਕੜੇ->fribidi);
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIBTHAI_H
    SDL_LibThai_Destroy(ਅੰਕੜੇ->th);
#ਜੇ_ਅੰਤ

    SDL_free(ਅੰਕੜੇ);
}

ਸਥਿਰ ਪੂਰਨ X11_Toolkit_ਗਿਣਤੀ_ਸਤਰਾਂ_ਦਾ_ਪਾਠ(ਅਚਲ ਅੱਖਰ *ਪਾਠ)
{
    ਪੂਰਨ ਨਤੀਜਾ = 0;
    ਜਦੋਂ (ਪਾਠ && *ਪਾਠ) {
        ਅਚਲ ਅੱਖਰ *lf = SDL_strchr(ਪਾਠ, '\n');
        ਨਤੀਜਾ++; // even without an endline, this counts as a line.
        ਪਾਠ = lf ? lf + 1 : ਨਿਰਾ;
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ ਖਾਲੀ X11Toolkit_DrawLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    ਪੂਰਨ i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    X11_XSetForeground(control->ਖਿੜਕੀ->display, control->ਖਿੜਕੀ->ctx, control->ਖਿੜਕੀ->xcolor[SDL_MESSAGEBOX_COLOR_ਪਾਠ].pixel);
    ਲਈ (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Draw_ਪਾਠ_Elements(control->ਖਿੜਕੀ, label_control->ਸਤਰਾਂ[i].ਪਾਠ, control->rect.x + label_control->ਸਤਰਾਂ[i].rect.x, control->rect.y + label_control->ਸਤਰਾਂ[i].rect.y);
    }
}

ਸਥਿਰ ਖਾਲੀ X11Toolkit_DestroyLabelControl(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;
    ਪੂਰਨ i;

    label_control = (SDL_ToolkitLabelControlX11 *)control;
    ਲਈ (i = 0; i < label_control->sz; i++) {
        X11_Toolkit_Free_ਪਾਠ_Elements(label_control->ਸਤਰਾਂ[i].ਪਾਠ);
    }
    SDL_free(label_control->ਸਤਰਾਂ);
    SDL_free(label_control);
}

ਸਥਿਰ ਖਾਲੀ X11Toolkit_CalculateLabelControl(SDL_ToolkitControlX11 *ਅਧਾਰ_control) {
    SDL_ToolkitLabelControlX11 *control;
    ਪੂਰਨ i;

    control = (SDL_ToolkitLabelControlX11 *)ਅਧਾਰ_control;
    
    ਜੇ (ਅਧਾਰ_control->do_ਮਾਪ) {
        ਅਧਾਰ_control->rect.w = 0;
        ਅਧਾਰ_control->rect.h = 0;
    }
    
    ਲਈ (i = 0; i < control->sz; i++) {
        ਪੂਰਨ font_h;
        
        font_h = X11_Toolkit_Get_ਪਾਠ_Elements_Rect(control->ਸਤਰਾਂ[i].ਪਾਠ, &control->ਸਤਰਾਂ[i].rect);
        
        ਜੇ (ਅਧਾਰ_control->do_ਮਾਪ) {
            ਅਧਾਰ_control->rect.w = SDL_max(ਅਧਾਰ_control->rect.w, control->ਸਤਰਾਂ[i].rect.w);
        }
        
        ਜੇ (i > 0) {
            control->ਸਤਰਾਂ[i].rect.y = font_h + control->ਸਤਰਾਂ[i - 1].rect.y;
        } ਨਹੀਂਤਾਂ {
            control->ਸਤਰਾਂ[i].rect.y = 0;
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
    ਜੇ (ਅਧਾਰ_control->ਖਿੜਕੀ->fribidi) {
        FriBidiParType ਪਹਿਲਾ_ndn_dir;
        ਪੂਰਨ ਆਖਰੀ_ndn;
    
        ਪਹਿਲਾ_ndn_dir = FRIBIDI_PAR_LTR;
        ਲਈ (i = 0; i < control->sz; i++) {
            ਜੇ (control->ਸਤਰਾਂ[i].par != FRIBIDI_PAR_ON) {
                ਪਹਿਲਾ_ndn_dir = control->ਸਤਰਾਂ[i].par;
            }
        }

        ਆਖਰੀ_ndn = -1;
        ਲਈ (i = 0; i < control->sz; i++) {
            ਚੋਣ (control->ਸਤਰਾਂ[i].par) {
                ਹਾਲਤ FRIBIDI_PAR_LTR:
                    control->ਸਤਰਾਂ[i].rect.x = 0;
                    ਆਖਰੀ_ndn = i;
                    ਰੋਕੋ;
                ਹਾਲਤ FRIBIDI_PAR_RTL:
                    control->ਸਤਰਾਂ[i].rect.x = ਅਧਾਰ_control->rect.w - control->ਸਤਰਾਂ[i].rect.w;
                    ਆਖਰੀ_ndn = i;
                    ਰੋਕੋ;
                ਮੂਲ:
                    ਜੇ (ਆਖਰੀ_ndn != -1) {
                        ਜੇ (control->ਸਤਰਾਂ[ਆਖਰੀ_ndn].par == FRIBIDI_PAR_RTL) {
                            control->ਸਤਰਾਂ[i].rect.x = ਅਧਾਰ_control->rect.w - control->ਸਤਰਾਂ[i].rect.w;
                        } ਨਹੀਂਤਾਂ {
                            control->ਸਤਰਾਂ[i].rect.x = 0;
                        }
                    } ਨਹੀਂਤਾਂ {
                        ਜੇ (ਪਹਿਲਾ_ndn_dir == FRIBIDI_PAR_RTL) {
                            control->ਸਤਰਾਂ[i].rect.x = ਅਧਾਰ_control->rect.w - control->ਸਤਰਾਂ[i].rect.w;
                        } ਨਹੀਂਤਾਂ {
                            control->ਸਤਰਾਂ[i].rect.x = 0;
                        }
                    }
            }
        }
    }
#ਜੇ_ਅੰਤ
    
    ਜੇ (ਅਧਾਰ_control->do_ਮਾਪ && control->sz) {
        ਅਧਾਰ_control->rect.h = control->ਸਤਰਾਂ[control->sz - 1].rect.y + control->ਸਤਰਾਂ[control->sz - 1].rect.h;
    }
}

SDL_ToolkitControlX11 *X11Toolkit_CreateLabelControl(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਖਿੜਕੀ, ਅੱਖਰ *utf8) {
    SDL_ToolkitLabelControlX11 *control;
    SDL_ToolkitControlX11 *ਅਧਾਰ_control;
    ਪੂਰਨ i;
    
    ਜੇ (!utf8) {
        ਵਾਪਸ ਨਿਰਾ;
    }
 
    ਜੇ (!SDL_strcmp(utf8, "")) {
        ਵਾਪਸ ਨਿਰਾ;
    }   
    control = (SDL_ToolkitLabelControlX11 *)SDL_malloc(ਆਕਾਰ(SDL_ToolkitLabelControlX11));
    ਅਧਾਰ_control = (SDL_ToolkitControlX11 *)control;
    ਜੇ (!control) {
        SDL_ਸੈੱਟ_Error("Unable to allocate label control structure");
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਅਧਾਰ_control->ਖਿੜਕੀ = ਖਿੜਕੀ;
    ਅਧਾਰ_control->func_draw = X11Toolkit_DrawLabelControl;
    ਅਧਾਰ_control->func_on_state_change = ਨਿਰਾ;
    ਅਧਾਰ_control->func_calc_ਮਾਪ = X11Toolkit_CalculateLabelControl;
    ਅਧਾਰ_control->func_free  = X11Toolkit_DestroyLabelControl;
    ਅਧਾਰ_control->func_on_scale_change = ਨਿਰਾ;
    ਅਧਾਰ_control->state = SDL_TOOLKIT_CONTROL_STATE_X11_ਸਾਧਾਰਨ;
    ਅਧਾਰ_control->selected = false;
    ਅਧਾਰ_control->dynamic = false;
    ਅਧਾਰ_control->rect.w = 0;
    ਅਧਾਰ_control->rect.h = 0;
    ਅਧਾਰ_control->is_default_enter = false;
    ਅਧਾਰ_control->is_default_esc = false;
    
    control->sz = X11_Toolkit_ਗਿਣਤੀ_ਸਤਰਾਂ_ਦਾ_ਪਾਠ(utf8);
    control->ਸਤਰਾਂ = SDL_calloc(control->sz, ਆਕਾਰ(SDL_Toolkit_Label_Control_ਸਤਰ_X11));
    ਲਈ (i = 0; i < control->sz; i++) {
        ਅਚਲ ਅੱਖਰ *lf = SDL_strchr(utf8, '\n');
        ਅਚਲ ਪੂਰਨ ਲੰਮਾਈ = lf ? (lf - utf8) : SDL_strlen(utf8);
        ਪੂਰਨ sz;
        
        sz = ਲੰਮਾਈ;
        ਜੇ (lf && (lf > utf8) && (lf[-1] == '\r')) {
            sz--;
        }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_FRIBIDI_H
        control->ਸਤਰਾਂ[i].ਪਾਠ = X11_Toolkit_Make_ਪਾਠ_Elements(ਅਧਾਰ_control->ਖਿੜਕੀ, (ਅੱਖਰ *)utf8, sz, &control->ਸਤਰਾਂ[i].par);
#ਨਹੀਂਤਾਂ 
        control->ਸਤਰਾਂ[i].ਪਾਠ = X11_Toolkit_Make_ਪਾਠ_Elements(ਅਧਾਰ_control->ਖਿੜਕੀ, (ਅੱਖਰ *)utf8, sz);
#ਜੇ_ਅੰਤ
        X11_Toolkit_Shape_ਪਾਠ_Elements(ਅਧਾਰ_control->ਖਿੜਕੀ, control->ਸਤਰਾਂ[i].ਪਾਠ);

        utf8 += ਲੰਮਾਈ + 1;
        ਜੇ (!lf) {
            ਰੋਕੋ;
        }
    }

    ਅਧਾਰ_control->do_ਮਾਪ = true;
    X11Toolkit_CalculateLabelControl(ਅਧਾਰ_control);
    ਅਧਾਰ_control->do_ਮਾਪ = false;
    X11_Toolkit_ਜੋੜੋ_Control_ਮੰਜ਼ਿਲ_ਖਿੜਕੀ(ਖਿੜਕੀ, ਅਧਾਰ_control);

    ਵਾਪਸ ਅਧਾਰ_control;
}

ਪੂਰਨ X11_Toolkit_Get_Label_Control_ਪਹਿਲਾ_ਸਤਰ_ਉਚਾਈ(SDL_ToolkitControlX11 *control) {
    SDL_ToolkitLabelControlX11 *label_control;

    label_control = (SDL_ToolkitLabelControlX11 *)control;

    ਵਾਪਸ label_control->ਸਤਰਾਂ[0].rect.h;
}

ਖਾਲੀ X11_Toolkit_Signal_ਖਿੜਕੀ_Close(SDL_Toolkit_ਖਿੜਕੀ_X11 *ਅੰਕੜੇ) {
    ਅੰਕੜੇ->close = true;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
