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

#ਅਨ੍ਤਰ੍ਭਾਵ <X11/cursorfont.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11mouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xinput2.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xtest.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_video_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"

ਬਣਤਰ SDL_Cursor_ਅੰਕੜੇ
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
ਸਥਿਰ Cursor x11_ਖਾਲੀ_ਥਾਵਾਂ_cursor = None;
ਸਥਿਰ bool x11_cursor_visible = true;

ਸਥਿਰ SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ਖੱਬਾ + 1];

ਸਥਿਰ Display *GetDisplay(ਖਾਲੀ)
{
    ਵਾਪਸ SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ->display;
}

ਸਥਿਰ Cursor X11_Create_ਖਾਲੀ_ਥਾਵਾਂ_Cursor(ਖਾਲੀ)
{
    ਜੇ (x11_ਖਾਲੀ_ਥਾਵਾਂ_cursor == None) {
        Display *display = GetDisplay();
        ਅੱਖਰ ਅੰਕੜੇ[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(ਅੰਕੜੇ);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreate_Bitmap_From_ਅੰਕੜੇ(display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display),
                                           ਅੰਕੜੇ, 1, 1);
        ਜੇ (pixmap) {
            x11_ਖਾਲੀ_ਥਾਵਾਂ_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    ਵਾਪਸ x11_ਖਾਲੀ_ਥਾਵਾਂ_cursor;
}

ਸਥਿਰ ਖਾਲੀ X11_Destroy_ਖਾਲੀ_ਥਾਵਾਂ_Cursor(ਖਾਲੀ)
{
    ਜੇ (x11_ਖਾਲੀ_ਥਾਵਾਂ_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_ਖਾਲੀ_ਥਾਵਾਂ_cursor);
        x11_ਖਾਲੀ_ਥਾਵਾਂ_cursor = None;
    }
}

ਸਥਿਰ SDL_Cursor *X11_Create_Cursor_And_ਅੰਕੜੇ(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ਆਕਾਰ(*cursor));
    ਜੇ (cursor) {
        SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Cursor_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
        ਜੇ (!ਅੰਕੜੇ) {
            SDL_free(cursor);
            ਵਾਪਸ ਨਿਰਾ;
        }
        ਅੰਕੜੇ->cursor = x11_cursor;
        cursor->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    }
    ਵਾਪਸ cursor;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XCURSOR
ਸਥਿਰ XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    ਜੇ (!image) {
        SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
        ਵਾਪਸ ਨਿਰਾ;
    }
    image->xhot = hot_x;
    image->yhot = hot_y;
    image->delay = delay;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);
    SDL_PremultiplyAlpha(surface->w, surface->h,
                         surface->format, surface->pixels, surface->pitch,
                         SDL_PIXELFORMAT_ARGB8888, image->pixels,
                         surface->w * 4, false);

    ਵਾਪਸ image;
}

ਸਥਿਰ Cursor X11_CreateXCursorCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    ਜੇ (image) {
        cursor = X11_Xcursor_Image_ਲੱਦੋ_Cursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    ਵਾਪਸ cursor;
}

ਸਥਿਰ Cursor X11_CreateAnimatedXCursorCursor(SDL_Cursor_ਚੌਖਟਾ_Info *ਚੌਖਟੇ, ਪੂਰਨ ਅੰਕ_ਚੌਖਟੇ, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(ਅੰਕ_ਚੌਖਟੇ);
    ਜੇ (!images) {
        SDL_ਬਾਹਰਲਾ_ਦਾ_ਸਮ੍ਰਿਤੀ();
        ਵਾਪਸ None;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ_ਚੌਖਟੇ; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(ਚੌਖਟੇ[i].surface, hot_x, hot_y, ਚੌਖਟੇ[i].duration);
        ਜੇ (!image) {
            ਜਾਓ cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_Xcursor_Images_ਲੱਦੋ_Cursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    ਵਾਪਸ cursor;
}
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XCURSOR

ਸਥਿਰ Cursor X11_CreatePixmapCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *ਅੰਕੜੇ_ਬਿੱਟ, *ਨਕਾਬ_ਬਿੱਟ;
    Pixmap ਅੰਕੜੇ_pixmap, ਨਕਾਬ_pixmap;
    ਪੂਰਨ x, y;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ rfg, gfg, bfg, rbg, gbg, bbg, fg_ਬਿੱਟ, bg_ਬਿੱਟ;
    size_t ਚੌੜਾਈ_ਬਾਈਟਾਂ = ((surface->w + 7) & ~((size_t)7)) / 8;

    ਅੰਕੜੇ_ਬਿੱਟ = SDL_calloc(1, surface->h * ਚੌੜਾਈ_ਬਾਈਟਾਂ);
    ਜੇ (!ਅੰਕੜੇ_ਬਿੱਟ) {
        ਵਾਪਸ None;
    }

    ਨਕਾਬ_ਬਿੱਟ = SDL_calloc(1, surface->h * ਚੌੜਾਈ_ਬਾਈਟਾਂ);
    ਜੇ (!ਨਕਾਬ_ਬਿੱਟ) {
        SDL_free(ਅੰਕੜੇ_ਬਿੱਟ);
        ਵਾਪਸ None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fg_ਬਿੱਟ = bg_ਬਿੱਟ = 0;
    ਲਈ (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        ਲਈ (x = 0; x < surface->w; ++x) {
            ਪੂਰਨ alpha = (*ptr >> 24) & 0xff;
            ਪੂਰਨ red = (*ptr >> 16) & 0xff;
            ਪੂਰਨ green = (*ptr >> 8) & 0xff;
            ਪੂਰਨ blue = (*ptr >> 0) & 0xff;
            ਜੇ (alpha > 25) {
                ਨਕਾਬ_ਬਿੱਟ[y * ਚੌੜਾਈ_ਬਾਈਟਾਂ + x / 8] |= (0x01 << (x % 8));

                ਜੇ ((red + green + blue) > 0x40) {
                    fg_ਬਿੱਟ++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    ਅੰਕੜੇ_ਬਿੱਟ[y * ਚੌੜਾਈ_ਬਾਈਟਾਂ + x / 8] |= (0x01 << (x % 8));
                } ਨਹੀਂਤਾਂ {
                    bg_ਬਿੱਟ++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    ਜੇ (fg_ਬਿੱਟ) {
        fg.red = rfg * 257 / fg_ਬਿੱਟ;
        fg.green = gfg * 257 / fg_ਬਿੱਟ;
        fg.blue = bfg * 257 / fg_ਬਿੱਟ;
    } ਨਹੀਂਤਾਂ {
        fg.red = fg.green = fg.blue = 0;
    }

    ਜੇ (bg_ਬਿੱਟ) {
        bg.red = rbg * 257 / bg_ਬਿੱਟ;
        bg.green = gbg * 257 / bg_ਬਿੱਟ;
        bg.blue = bbg * 257 / bg_ਬਿੱਟ;
    } ਨਹੀਂਤਾਂ {
        bg.red = bg.green = bg.blue = 0;
    }

    ਅੰਕੜੇ_pixmap = X11_XCreate_Bitmap_From_ਅੰਕੜੇ(display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display),
                                            (ਅੱਖਰ *)ਅੰਕੜੇ_ਬਿੱਟ,
                                            surface->w, surface->h);
    ਨਕਾਬ_pixmap = X11_XCreate_Bitmap_From_ਅੰਕੜੇ(display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display),
                                            (ਅੱਖਰ *)ਨਕਾਬ_ਬਿੱਟ,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, ਅੰਕੜੇ_pixmap, ਨਕਾਬ_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, ਅੰਕੜੇ_pixmap);
    X11_XFreePixmap(display, ਨਕਾਬ_pixmap);
    SDL_free(ਅੰਕੜੇ_ਬਿੱਟ);
    SDL_free(ਨਕਾਬ_ਬਿੱਟ);

    ਵਾਪਸ cursor;
}

ਸਥਿਰ SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    Cursor x11_cursor = None;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XCURSOR
    ਜੇ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#ਜੇ_ਅੰਤ
    ਜੇ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    ਵਾਪਸ X11_Create_Cursor_And_ਅੰਕੜੇ(x11_cursor);
}

ਸਥਿਰ SDL_Cursor *X11_CreateAnimatedCursor(SDL_Cursor_ਚੌਖਟਾ_Info *ਚੌਖਟੇ, ਪੂਰਨ ਅੰਕ_ਚੌਖਟੇ, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    Cursor x11_cursor = None;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XCURSOR
    ਜੇ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(ਚੌਖਟੇ, ਅੰਕ_ਚੌਖਟੇ, hot_x, hot_y);
    }
#ਜੇ_ਅੰਤ
    ਜੇ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(ਚੌਖਟੇ[0].surface, hot_x, hot_y);
    }

    ਵਾਪਸ X11_Create_Cursor_And_ਅੰਕੜੇ(x11_cursor);
}

ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    ਚੋਣ (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        ਹਾਲਤ SDL_SYSTEM_CURSOR_DEFAULT: ਵਾਪਸ XC_ਖੱਬਾ_ptr;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_ਪਾਠ: ਵਾਪਸ XC_xterm;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_WAIT: ਵਾਪਸ XC_watch;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_CROSSHAIR: ਵਾਪਸ XC_tcross;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_ਤਰੱਕੀ: ਵਾਪਸ XC_watch;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_NWSE_RESIZE: ਵਾਪਸ XC_ਸਿਖਰ_ਖੱਬਾ_ਕੋਨਾ;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_NESW_RESIZE: ਵਾਪਸ XC_ਸਿਖਰ_ਸੱਜਾ_ਕੋਨਾ;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_EW_RESIZE: ਵਾਪਸ XC_sb_h_double_arrow;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_NS_RESIZE: ਵਾਪਸ XC_sb_v_double_arrow;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_MOVE: ਵਾਪਸ XC_fleur;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_NOT_ALLOWED: ਵਾਪਸ XC_pirate;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_ਸੂਚਕ: ਵਾਪਸ XC_hand2;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_NW_RESIZE: ਵਾਪਸ XC_ਸਿਖਰ_ਖੱਬਾ_ਕੋਨਾ;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_N_RESIZE: ਵਾਪਸ XC_ਸਿਖਰ_side;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_NE_RESIZE: ਵਾਪਸ XC_ਸਿਖਰ_ਸੱਜਾ_ਕੋਨਾ;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_E_RESIZE: ਵਾਪਸ XC_ਸੱਜਾ_side;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_SE_RESIZE: ਵਾਪਸ XC_bottom_ਸੱਜਾ_ਕੋਨਾ;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_S_RESIZE: ਵਾਪਸ XC_bottom_side;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_SW_RESIZE: ਵਾਪਸ XC_bottom_ਖੱਬਾ_ਕੋਨਾ;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_W_RESIZE: ਵਾਪਸ XC_ਖੱਬਾ_side;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_CONTEXT_MENU: ਵਾਪਸ XC_hand2;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_HELP: ਵਾਪਸ XC_question_arrow;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_CELL: ਵਾਪਸ XC_cross;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_VERTICAL_ਪਾਠ: ਵਾਪਸ XC_xterm;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_ALIAS: ਵਾਪਸ XC_hand2;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_COPY: ਵਾਪਸ XC_hand2;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_NO_DROP: ਵਾਪਸ XC_pirate;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_GRAB: ਵਾਪਸ XC_hand2;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_GRABBING: ਵਾਪਸ XC_hand2;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_ਖਾਨਾ_RESIZE: ਵਾਪਸ XC_sb_h_double_arrow;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_ਪੰਕਤੀ_RESIZE: ਵਾਪਸ XC_sb_v_double_arrow;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_ALL_SCROLL: ਵਾਪਸ XC_fleur;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_ZOOM_ਵਿੱਚ: ਵਾਪਸ XC_hand2;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_ZOOM_ਬਾਹਰਲਾ: ਵਾਪਸ XC_hand2;
        ਹਾਲਤ SDL_SYSTEM_CURSOR_ਗਿਣਤੀ: ਰੋਕੋ;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    ਵਾਪਸ 0;
}

ਸਥਿਰ SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = ਨਿਰਾ;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XCURSOR
    ਜੇ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_Xcursor_Library_ਲੱਦੋ_Cursor(dpy, SDL_GetCSSCursorName(id, ਨਿਰਾ));
    }
#ਜੇ_ਅੰਤ

    ਜੇ (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    ਜੇ (x11_cursor != None) {
        cursor = X11_Create_Cursor_And_ਅੰਕੜੇ(x11_cursor);
    }

    ਵਾਪਸ cursor;
}

ਸਥਿਰ SDL_Cursor *X11_CreateDefaultCursor(ਖਾਲੀ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ਵਾਪਸ X11_CreateSystemCursor(id);
}

ਸਥਿਰ ਖਾਲੀ X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->ਅੰਦਰੂਨੀ->cursor;

    ਜੇ (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->ਅੰਦਰੂਨੀ);
    SDL_free(cursor);
}

ਸਥਿਰ bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    ਜੇ (cursor) {
        x11_cursor = cursor->ਅੰਦਰੂਨੀ->cursor;
    } ਨਹੀਂਤਾਂ {
        x11_cursor = X11_Create_ਖਾਲੀ_ਥਾਵਾਂ_Cursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;

        x11_cursor_visible = !!cursor;

        ਲਈ (ਖਿੜਕੀ = video->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
            ਜੇ (ਅੰਕੜੇ) {
                ਜੇ (x11_cursor != None) {
                    X11_XDefineCursor(display, ਅੰਕੜੇ->xwindow, x11_cursor);
                } ਨਹੀਂਤਾਂ {
                    X11_XUndefineCursor(display, ਅੰਕੜੇ->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ ਖਾਲੀ X11_Warp_Mouse_ਅੰਦਰੂਨੀ(ਖਿੜਕੀ_2 xwindow, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    SDL_Video_ਅੰਕੜੇ *videodata = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    ਜੇ (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    ਜੇ (warp_hack) {
        X11_ShowCursor(ਨਿਰਾ);
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2
    ਪੂਰਨ deviceid = 0;
    ਜੇ (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        ਜੇ (Screen_ਗਿਣਤੀ(display) == 1) {
            X11_XIGet_Client_ਸੂਚਕ(display, None, &deviceid);
        }
    }
    ਜੇ (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarp_ਸੂਚਕ(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ
    {
        X11_XWarp_ਸੂਚਕ(display, None, xwindow, 0, 0, 0, 0, (ਪੂਰਨ)x, (ਪੂਰਨ)y);
    }

    ਜੇ (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_ਬਦਲਿਆ = true;
}

ਸਥਿਰ bool X11_WarpMouse(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

    ਜੇ (X11_WarpMouseXTest(SDL_GetVideoDevice(), ਖਿੜਕੀ, x, y)) {
        ਵਾਪਸ true;
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    ਜੇ (ਅੰਕੜੇ->ਸੂਚਕ_barrier_ਸਰਗਰਮ == false) {
        X11_Warp_Mouse_ਅੰਦਰੂਨੀ(ਅੰਕੜੇ->xwindow, x, y);
    }
#ਨਹੀਂਤਾਂ
    X11_Warp_Mouse_ਅੰਦਰੂਨੀ(ਅੰਕੜੇ->xwindow, x, y);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ true;
}

ਸਥਿਰ bool X11_WarpMouseGlobal(ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    ਜੇ (X11_WarpMouseXTest(SDL_GetVideoDevice(), ਨਿਰਾ, x, y)) {
        ਵਾਪਸ true;
    }

    X11_Warp_Mouse_ਅੰਦਰੂਨੀ(Default_ਜੜ੍ਹ_ਖਿੜਕੀ(GetDisplay()), x, y);
    ਵਾਪਸ true;
}

ਸਥਿਰ bool X11_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ(bool enabled)
{
    ਜੇ (!X11_Xinput2IsInitialized()) {
        ਵਾਪਸ SDL_Unsupported();
    }
    ਵਾਪਸ true;
}

ਸਥਿਰ bool X11_CaptureMouse(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    Display *display = GetDisplay();
    SDL_ਖਿੜਕੀ *mouse_focus = SDL_GetMouseFocus();

    ਜੇ (ਖਿੜਕੀ) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        ਜੇ (!ਅੰਕੜੇ->xinput2_mouse_enabled || ਅੰਕੜੇ->mouse_grabbed) {
            ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਨਕਾਬ = Button_Press_ਨਕਾਬ | Button_Release_ਨਕਾਬ | ਸੂਚਕ_Motion_ਨਕਾਬ | Focus_Change_ਨਕਾਬ;
            ਖਿੜਕੀ_2 confined = (ਅੰਕੜੇ->mouse_grabbed ? ਅੰਕੜੇ->xwindow : None);
            ਅਚਲ ਪੂਰਨ rc = X11_XGrab_ਸੂਚਕ(display, ਅੰਕੜੇ->xwindow, False,
                                            ਨਕਾਬ, Grab_ਬਹੁਲਕ_Async, Grab_ਬਹੁਲਕ_Async,
                                            confined, None, Current_ਸਮਾਂ);
            ਜੇ (rc != GrabSuccess) {
                ਵਾਪਸ SDL_ਸੈੱਟ_Error("X server refused mouse capture");
            }

            ਜੇ (ਅੰਕੜੇ->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                ਅੰਕੜੇ->videodata->global_mouse_ਬਦਲਿਆ = true;
            }
        }
    } ਨਹੀਂਤਾਂ ਜੇ (mouse_focus) {
        SDL_Update_ਖਿੜਕੀ_Grab(mouse_focus);
    } ਨਹੀਂਤਾਂ {
        X11_XUngrab_ਸੂਚਕ(display, Current_ਸਮਾਂ);
    }

    X11_XSync(display, False);

    ਵਾਪਸ true;
}

ਸਥਿਰ SDL_MouseButtonFlags X11_GetGlobalMouseState(ਦਸ਼ਮਲਵ *x, ਦਸ਼ਮਲਵ *y)
{
    SDL_Video_ਅੰਕੜੇ *videodata = SDL_GetVideoDevice()->ਅੰਦਰੂਨੀ;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    ਪੂਰਨ i;

    // !!! FIXME: should we XSync() here first?

    ਜੇ (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_ਬਦਲਿਆ = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    ਜੇ (videodata->global_mouse_ਬਦਲਿਆ) {
        displays = SDL_GetDisplays(ਨਿਰਾ);
        ਜੇ (displays) {
            ਲਈ (i = 0; displays[i]; ++i) {
                SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ = SDL_Get_Display_Driver_ਅੰਕੜੇ(displays[i]);
                ਜੇ (ਅੰਕੜੇ) {
                    ਖਿੜਕੀ_2 ਜੜ੍ਹ, ਬੱਚਾ;
                    ਪੂਰਨ rootx, rooty, winx, winy;
                    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਨਕਾਬ;
                    ਜੇ (X11_XQuery_ਸੂਚਕ(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, ਅੰਕੜੇ->screen), &ਜੜ੍ਹ, &ਬੱਚਾ, &rootx, &rooty, &winx, &winy, &ਨਕਾਬ)) {
                        XWindow_ਗੁਣ ਜੜ੍ਹ_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (ਨਕਾਬ & Button1_ਨਕਾਬ) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (ਨਕਾਬ & Button2_ਨਕਾਬ) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (ਨਕਾਬ & Button3_ਨਕਾਬ) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(ਨਿਰਾ, ਨਿਰਾ) & (SDL_BUTTON_X1_ਨਕਾਬ | SDL_BUTTON_X2_ਨਕਾਬ));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGet_ਖਿੜਕੀ_ਗੁਣ(display, ਜੜ੍ਹ, &ਜੜ੍ਹ_attrs);
                        videodata->global_mouse_position.x = ਜੜ੍ਹ_attrs.x + rootx;
                        videodata->global_mouse_position.y = ਜੜ੍ਹ_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_ਬਦਲਿਆ = false;
                        ਰੋਕੋ;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_ਬਦਲਿਆ); // The pointer wasn't on any X11 screen?!

    *x = (ਦਸ਼ਮਲਵ)videodata->global_mouse_position.x;
    *y = (ਦਸ਼ਮਲਵ)videodata->global_mouse_position.y;
    ਵਾਪਸ videodata->global_mouse_buttons;
}

ਖਾਲੀ X11_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = X11_CreateCursor;
    mouse->CreateAnimatedCursor = X11_CreateAnimatedCursor;
    mouse->CreateSystemCursor = X11_CreateSystemCursor;
    mouse->ShowCursor = X11_ShowCursor;
    mouse->FreeCursor = X11_FreeCursor;
    mouse->WarpMouse = X11_WarpMouse;
    mouse->WarpMouseGlobal = X11_WarpMouseGlobal;
    mouse->ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ = X11_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ;
    mouse->CaptureMouse = X11_CaptureMouse;
    mouse->GetGlobalMouseState = X11_GetGlobalMouseState;

    SDL_ਪ੍ਰਾਪਤੀ_Test_ਨਤੀਜਾ r = SDL_HITTEST_ਸਾਧਾਰਨ;
    ਜਦੋਂ (r <= SDL_HITTEST_RESIZE_ਖੱਬਾ) {
        ਚੋਣ (r) {
        ਹਾਲਤ SDL_HITTEST_ਸਾਧਾਰਨ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਸਿਖਰ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਸੱਜਾ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); ਰੋਕੋ;
        ਹਾਲਤ SDL_HITTEST_RESIZE_ਖੱਬਾ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); ਰੋਕੋ;
        }
        r++;
    }

    SDL_ਸੈੱਟ_Default_Cursor(X11_CreateDefaultCursor());
}

ਖਾਲੀ X11_QuitMouse(SDL_VideoDevice *_this)
{
    ਲਈ (ਪੂਰਨ i = 0; i < SDL_arraysize(sys_cursors); i++) {
        ਜੇ (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = ਨਿਰਾ;
        }
    }

    X11_Destroy_ਖਾਲੀ_ਥਾਵਾਂ_Cursor();
}

ਖਾਲੀ X11_ਸੈੱਟ_ਪ੍ਰਾਪਤੀ_Test_Cursor(SDL_ਪ੍ਰਾਪਤੀ_Test_ਨਤੀਜਾ rc)
{
    ਜੇ (rc == SDL_HITTEST_ਸਾਧਾਰਨ || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } ਨਹੀਂਤਾਂ {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
