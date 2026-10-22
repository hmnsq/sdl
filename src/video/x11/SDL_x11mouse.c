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

#ಅನ್ತರ್ಭಾವ <X11/cursorfont.h>
#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11mouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xinput2.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xtest.h"
#ಅನ್ತರ್ಭಾವ "../SDL_video_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

ರಚನೆ SDL_Cursor_ದತ್ತಾಂಶ
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
ಸ್ಥಿರ Cursor x11_ಖಾಲಿಗಳು_cursor = None;
ಸ್ಥಿರ bool x11_cursor_visible = true;

ಸ್ಥಿರ SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ಎಡ + 1];

ಸ್ಥಿರ Display *GetDisplay(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ SDL_GetVideoDevice()->ಆಂತರಿಕ->display;
}

ಸ್ಥಿರ Cursor X11_Create_ಖಾಲಿಗಳು_Cursor(ಶೂನ್ಯ)
{
    ಆದರೆ (x11_ಖಾಲಿಗಳು_cursor == None) {
        Display *display = GetDisplay();
        ಅಕ್ಷರ ದತ್ತಾಂಶ[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(ದತ್ತಾಂಶ);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreate_Bitmap_From_ದತ್ತಾಂಶ(display, Default_ಬೇರು_ಕಿಟಕಿ(display),
                                           ದತ್ತಾಂಶ, 1, 1);
        ಆದರೆ (pixmap) {
            x11_ಖಾಲಿಗಳು_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    ಹಿಂತಿರುಗಿ x11_ಖಾಲಿಗಳು_cursor;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Destroy_ಖಾಲಿಗಳು_Cursor(ಶೂನ್ಯ)
{
    ಆದರೆ (x11_ಖಾಲಿಗಳು_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_ಖಾಲಿಗಳು_cursor);
        x11_ಖಾಲಿಗಳು_cursor = None;
    }
}

ಸ್ಥಿರ SDL_Cursor *X11_Create_Cursor_And_ದತ್ತಾಂಶ(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ಗಾತ್ರ(*cursor));
    ಆದರೆ (cursor) {
        SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Cursor_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
        ಆದರೆ (!ದತ್ತಾಂಶ) {
            SDL_free(cursor);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        ದತ್ತಾಂಶ->cursor = x11_cursor;
        cursor->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    }
    ಹಿಂತಿರುಗಿ cursor;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XCURSOR
ಸ್ಥಿರ XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    ಆದರೆ (!image) {
        SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
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

    ಹಿಂತಿರುಗಿ image;
}

ಸ್ಥಿರ Cursor X11_CreateXCursorCursor(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    ಆದರೆ (image) {
        cursor = X11_Xcursor_Image_ತುಂಬು_Cursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ Cursor X11_CreateAnimatedXCursorCursor(SDL_Cursor_ಚೌಕಟ್ಟು_Info *ಚೌಕಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು);
    ಆದರೆ (!images) {
        SDL_ಹೊರಹೋಗು_ದ_ಸ್ಮರಣೆ();
        ಹಿಂತಿರುಗಿ None;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(ಚೌಕಟ್ಟುಗಳು[i].surface, hot_x, hot_y, ಚೌಕಟ್ಟುಗಳು[i].duration);
        ಆದರೆ (!image) {
            ಹೋಗು cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_Xcursor_Images_ತುಂಬು_Cursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    ಹಿಂತಿರುಗಿ cursor;
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XCURSOR

ಸ್ಥಿರ Cursor X11_CreatePixmapCursor(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *ದತ್ತಾಂಶ_ಬಿಟ್ಟುಗಳು, *ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು;
    Pixmap ದತ್ತಾಂಶ_pixmap, ಮುಖವಾಡ_pixmap;
    ಪೂರ್ಣಾಂಕ x, y;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ rfg, gfg, bfg, rbg, gbg, bbg, fg_ಬಿಟ್ಟುಗಳು, bg_ಬಿಟ್ಟುಗಳು;
    size_t ಅಗಲ_ಬೈಟುಗಳು = ((surface->w + 7) & ~((size_t)7)) / 8;

    ದತ್ತಾಂಶ_ಬಿಟ್ಟುಗಳು = SDL_calloc(1, surface->h * ಅಗಲ_ಬೈಟುಗಳು);
    ಆದರೆ (!ದತ್ತಾಂಶ_ಬಿಟ್ಟುಗಳು) {
        ಹಿಂತಿರುಗಿ None;
    }

    ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು = SDL_calloc(1, surface->h * ಅಗಲ_ಬೈಟುಗಳು);
    ಆದರೆ (!ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು) {
        SDL_free(ದತ್ತಾಂಶ_ಬಿಟ್ಟುಗಳು);
        ಹಿಂತಿರುಗಿ None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fg_ಬಿಟ್ಟುಗಳು = bg_ಬಿಟ್ಟುಗಳು = 0;
    ಗಾಗಿ (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        ಗಾಗಿ (x = 0; x < surface->w; ++x) {
            ಪೂರ್ಣಾಂಕ alpha = (*ptr >> 24) & 0xff;
            ಪೂರ್ಣಾಂಕ red = (*ptr >> 16) & 0xff;
            ಪೂರ್ಣಾಂಕ green = (*ptr >> 8) & 0xff;
            ಪೂರ್ಣಾಂಕ blue = (*ptr >> 0) & 0xff;
            ಆದರೆ (alpha > 25) {
                ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು[y * ಅಗಲ_ಬೈಟುಗಳು + x / 8] |= (0x01 << (x % 8));

                ಆದರೆ ((red + green + blue) > 0x40) {
                    fg_ಬಿಟ್ಟುಗಳು++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    ದತ್ತಾಂಶ_ಬಿಟ್ಟುಗಳು[y * ಅಗಲ_ಬೈಟುಗಳು + x / 8] |= (0x01 << (x % 8));
                } ಇಲ್ಲದಿದ್ದರೆ {
                    bg_ಬಿಟ್ಟುಗಳು++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    ಆದರೆ (fg_ಬಿಟ್ಟುಗಳು) {
        fg.red = rfg * 257 / fg_ಬಿಟ್ಟುಗಳು;
        fg.green = gfg * 257 / fg_ಬಿಟ್ಟುಗಳು;
        fg.blue = bfg * 257 / fg_ಬಿಟ್ಟುಗಳು;
    } ಇಲ್ಲದಿದ್ದರೆ {
        fg.red = fg.green = fg.blue = 0;
    }

    ಆದರೆ (bg_ಬಿಟ್ಟುಗಳು) {
        bg.red = rbg * 257 / bg_ಬಿಟ್ಟುಗಳು;
        bg.green = gbg * 257 / bg_ಬಿಟ್ಟುಗಳು;
        bg.blue = bbg * 257 / bg_ಬಿಟ್ಟುಗಳು;
    } ಇಲ್ಲದಿದ್ದರೆ {
        bg.red = bg.green = bg.blue = 0;
    }

    ದತ್ತಾಂಶ_pixmap = X11_XCreate_Bitmap_From_ದತ್ತಾಂಶ(display, Default_ಬೇರು_ಕಿಟಕಿ(display),
                                            (ಅಕ್ಷರ *)ದತ್ತಾಂಶ_ಬಿಟ್ಟುಗಳು,
                                            surface->w, surface->h);
    ಮುಖವಾಡ_pixmap = X11_XCreate_Bitmap_From_ದತ್ತಾಂಶ(display, Default_ಬೇರು_ಕಿಟಕಿ(display),
                                            (ಅಕ್ಷರ *)ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, ದತ್ತಾಂಶ_pixmap, ಮುಖವಾಡ_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, ದತ್ತಾಂಶ_pixmap);
    X11_XFreePixmap(display, ಮುಖವಾಡ_pixmap);
    SDL_free(ದತ್ತಾಂಶ_ಬಿಟ್ಟುಗಳು);
    SDL_free(ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು);

    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    Cursor x11_cursor = None;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XCURSOR
    ಆದರೆ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    ಹಿಂತಿರುಗಿ X11_Create_Cursor_And_ದತ್ತಾಂಶ(x11_cursor);
}

ಸ್ಥಿರ SDL_Cursor *X11_CreateAnimatedCursor(SDL_Cursor_ಚೌಕಟ್ಟು_Info *ಚೌಕಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    Cursor x11_cursor = None;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XCURSOR
    ಆದರೆ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(ಚೌಕಟ್ಟುಗಳು, ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು, hot_x, hot_y);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(ಚೌಕಟ್ಟುಗಳು[0].surface, hot_x, hot_y);
    }

    ಹಿಂತಿರುಗಿ X11_Create_Cursor_And_ದತ್ತಾಂಶ(x11_cursor);
}

ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    ಆಯ್ಕೆ (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_DEFAULT: ಹಿಂತಿರುಗಿ XC_ಎಡ_ptr;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಪಠ್ಯ: ಹಿಂತಿರುಗಿ XC_xterm;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_WAIT: ಹಿಂತಿರುಗಿ XC_watch;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CROSSHAIR: ಹಿಂತಿರುಗಿ XC_tcross;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಪ್ರಗತಿ: ಹಿಂತಿರುಗಿ XC_watch;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NWSE_RESIZE: ಹಿಂತಿರುಗಿ XC_ತುದಿ_ಎಡ_ಮೂಲೆ;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NESW_RESIZE: ಹಿಂತಿರುಗಿ XC_ತುದಿ_ಬಲ_ಮೂಲೆ;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_EW_RESIZE: ಹಿಂತಿರುಗಿ XC_sb_h_double_arrow;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NS_RESIZE: ಹಿಂತಿರುಗಿ XC_sb_v_double_arrow;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_MOVE: ಹಿಂತಿರುಗಿ XC_fleur;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NOT_ALLOWED: ಹಿಂತಿರುಗಿ XC_pirate;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಸೂಚಕ: ಹಿಂತಿರುಗಿ XC_hand2;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NW_RESIZE: ಹಿಂತಿರುಗಿ XC_ತುದಿ_ಎಡ_ಮೂಲೆ;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_N_RESIZE: ಹಿಂತಿರುಗಿ XC_ತುದಿ_side;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NE_RESIZE: ಹಿಂತಿರುಗಿ XC_ತುದಿ_ಬಲ_ಮೂಲೆ;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_E_RESIZE: ಹಿಂತಿರುಗಿ XC_ಬಲ_side;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_SE_RESIZE: ಹಿಂತಿರುಗಿ XC_bottom_ಬಲ_ಮೂಲೆ;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_S_RESIZE: ಹಿಂತಿರುಗಿ XC_bottom_side;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_SW_RESIZE: ಹಿಂತಿರುಗಿ XC_bottom_ಎಡ_ಮೂಲೆ;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_W_RESIZE: ಹಿಂತಿರುಗಿ XC_ಎಡ_side;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CONTEXT_MENU: ಹಿಂತಿರುಗಿ XC_hand2;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_HELP: ಹಿಂತಿರುಗಿ XC_question_arrow;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CELL: ಹಿಂತಿರುಗಿ XC_cross;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_VERTICAL_ಪಠ್ಯ: ಹಿಂತಿರುಗಿ XC_xterm;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ALIAS: ಹಿಂತಿರುಗಿ XC_hand2;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_COPY: ಹಿಂತಿರುಗಿ XC_hand2;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NO_DROP: ಹಿಂತಿರುಗಿ XC_pirate;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_GRAB: ಹಿಂತಿರುಗಿ XC_hand2;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_GRABBING: ಹಿಂತಿರುಗಿ XC_hand2;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಲಂಬಸಾಲು_RESIZE: ಹಿಂತಿರುಗಿ XC_sb_h_double_arrow;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಅಡ್ಡಸಾಲು_RESIZE: ಹಿಂತಿರುಗಿ XC_sb_v_double_arrow;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ALL_SCROLL: ಹಿಂತಿರುಗಿ XC_fleur;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ZOOM_ಒಳ: ಹಿಂತಿರುಗಿ XC_hand2;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ZOOM_ಹೊರಹೋಗು: ಹಿಂತಿರುಗಿ XC_hand2;
        ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಎಣಿಕೆ: ನಿಲ್ಲಿಸು;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = ಖಾಲಿ;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XCURSOR
    ಆದರೆ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_Xcursor_Library_ತುಂಬು_Cursor(dpy, SDL_GetCSSCursorName(id, ಖಾಲಿ));
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    ಆದರೆ (x11_cursor != None) {
        cursor = X11_Create_Cursor_And_ದತ್ತಾಂಶ(x11_cursor);
    }

    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ SDL_Cursor *X11_CreateDefaultCursor(ಶೂನ್ಯ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ಹಿಂತಿರುಗಿ X11_CreateSystemCursor(id);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->ಆಂತರಿಕ->cursor;

    ಆದರೆ (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->ಆಂತರಿಕ);
    SDL_free(cursor);
}

ಸ್ಥಿರ bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    ಆದರೆ (cursor) {
        x11_cursor = cursor->ಆಂತರಿಕ->cursor;
    } ಇಲ್ಲದಿದ್ದರೆ {
        x11_cursor = X11_Create_ಖಾಲಿಗಳು_Cursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_ಕಿಟಕಿ *ಕಿಟಕಿ;

        x11_cursor_visible = !!cursor;

        ಗಾಗಿ (ಕಿಟಕಿ = video->windows; ಕಿಟಕಿ; ಕಿಟಕಿ = ಕಿಟಕಿ->ಮುಂದಿನ) {
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
            ಆದರೆ (ದತ್ತಾಂಶ) {
                ಆದರೆ (x11_cursor != None) {
                    X11_XDefineCursor(display, ದತ್ತಾಂಶ->xwindow, x11_cursor);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    X11_XUndefineCursor(display, ದತ್ತಾಂಶ->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_Warp_Mouse_ಆಂತರಿಕ(ಕಿಟಕಿ_2 xwindow, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = SDL_GetVideoDevice()->ಆಂತರಿಕ;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    ಆದರೆ (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    ಆದರೆ (warp_hack) {
        X11_ShowCursor(ಖಾಲಿ);
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2
    ಪೂರ್ಣಾಂಕ deviceid = 0;
    ಆದರೆ (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        ಆದರೆ (Screen_ಎಣಿಕೆ(display) == 1) {
            X11_XIGet_Client_ಸೂಚಕ(display, None, &deviceid);
        }
    }
    ಆದರೆ (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarp_ಸೂಚಕ(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ
    {
        X11_XWarp_ಸೂಚಕ(display, None, xwindow, 0, 0, 0, 0, (ಪೂರ್ಣಾಂಕ)x, (ಪೂರ್ಣಾಂಕ)y);
    }

    ಆದರೆ (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_ಬದಲಾಯಿತು = true;
}

ಸ್ಥಿರ bool X11_WarpMouse(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

    ಆದರೆ (X11_WarpMouseXTest(SDL_GetVideoDevice(), ಕಿಟಕಿ, x, y)) {
        ಹಿಂತಿರುಗಿ true;
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    ಆದರೆ (ದತ್ತಾಂಶ->ಸೂಚಕ_barrier_ಸಕ್ರಿಯ == false) {
        X11_Warp_Mouse_ಆಂತರಿಕ(ದತ್ತಾಂಶ->xwindow, x, y);
    }
#ಇಲ್ಲದಿದ್ದರೆ
    X11_Warp_Mouse_ಆಂತರಿಕ(ದತ್ತಾಂಶ->xwindow, x, y);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool X11_WarpMouseGlobal(ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    ಆದರೆ (X11_WarpMouseXTest(SDL_GetVideoDevice(), ಖಾಲಿ, x, y)) {
        ಹಿಂತಿರುಗಿ true;
    }

    X11_Warp_Mouse_ಆಂತರಿಕ(Default_ಬೇರು_ಕಿಟಕಿ(GetDisplay()), x, y);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool X11_ಗಣ_Relative_Mouse_ಬಹುಲಕ(bool enabled)
{
    ಆದರೆ (!X11_Xinput2IsInitialized()) {
        ಹಿಂತಿರುಗಿ SDL_Unsupported();
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool X11_CaptureMouse(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    Display *display = GetDisplay();
    SDL_ಕಿಟಕಿ *mouse_focus = SDL_GetMouseFocus();

    ಆದರೆ (ಕಿಟಕಿ) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        ಆದರೆ (!ದತ್ತಾಂಶ->xinput2_mouse_enabled || ದತ್ತಾಂಶ->mouse_grabbed) {
            ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ = Button_Press_ಮುಖವಾಡ | Button_Release_ಮುಖವಾಡ | ಸೂಚಕ_Motion_ಮುಖವಾಡ | Focus_Change_ಮುಖವಾಡ;
            ಕಿಟಕಿ_2 confined = (ದತ್ತಾಂಶ->mouse_grabbed ? ದತ್ತಾಂಶ->xwindow : None);
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ rc = X11_XGrab_ಸೂಚಕ(display, ದತ್ತಾಂಶ->xwindow, False,
                                            ಮುಖವಾಡ, Grab_ಬಹುಲಕ_Async, Grab_ಬಹುಲಕ_Async,
                                            confined, None, Current_ಸಮಯ);
            ಆದರೆ (rc != GrabSuccess) {
                ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("X server refused mouse capture");
            }

            ಆದರೆ (ದತ್ತಾಂಶ->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                ದತ್ತಾಂಶ->videodata->global_mouse_ಬದಲಾಯಿತು = true;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (mouse_focus) {
        SDL_Update_ಕಿಟಕಿ_Grab(mouse_focus);
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_XUngrab_ಸೂಚಕ(display, Current_ಸಮಯ);
    }

    X11_XSync(display, False);

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ SDL_MouseButtonFlags X11_GetGlobalMouseState(ದಶಮಾಂಶ *x, ದಶಮಾಂಶ *y)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = SDL_GetVideoDevice()->ಆಂತರಿಕ;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    ಪೂರ್ಣಾಂಕ i;

    // !!! FIXME: should we XSync() here first?

    ಆದರೆ (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_ಬದಲಾಯಿತು = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    ಆದರೆ (videodata->global_mouse_ಬದಲಾಯಿತು) {
        displays = SDL_GetDisplays(ಖಾಲಿ);
        ಆದರೆ (displays) {
            ಗಾಗಿ (i = 0; displays[i]; ++i) {
                SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = SDL_Get_Display_Driver_ದತ್ತಾಂಶ(displays[i]);
                ಆದರೆ (ದತ್ತಾಂಶ) {
                    ಕಿಟಕಿ_2 ಬೇರು, ಮಗು;
                    ಪೂರ್ಣಾಂಕ rootx, rooty, winx, winy;
                    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ;
                    ಆದರೆ (X11_XQuery_ಸೂಚಕ(display, ಬೇರು_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->screen), &ಬೇರು, &ಮಗು, &rootx, &rooty, &winx, &winy, &ಮುಖವಾಡ)) {
                        XWindow_ಗುಣಲಕ್ಷಣಗಳು ಬೇರು_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (ಮುಖವಾಡ & Button1_ಮುಖವಾಡ) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (ಮುಖವಾಡ & Button2_ಮುಖವಾಡ) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (ಮುಖವಾಡ & Button3_ಮುಖವಾಡ) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(ಖಾಲಿ, ಖಾಲಿ) & (SDL_BUTTON_X1_ಮುಖವಾಡ | SDL_BUTTON_X2_ಮುಖವಾಡ));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGet_ಕಿಟಕಿ_ಗುಣಲಕ್ಷಣಗಳು(display, ಬೇರು, &ಬೇರು_attrs);
                        videodata->global_mouse_position.x = ಬೇರು_attrs.x + rootx;
                        videodata->global_mouse_position.y = ಬೇರು_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_ಬದಲಾಯಿತು = false;
                        ನಿಲ್ಲಿಸು;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_ಬದಲಾಯಿತು); // The pointer wasn't on any X11 screen?!

    *x = (ದಶಮಾಂಶ)videodata->global_mouse_position.x;
    *y = (ದಶಮಾಂಶ)videodata->global_mouse_position.y;
    ಹಿಂತಿರುಗಿ videodata->global_mouse_buttons;
}

ಶೂನ್ಯ X11_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = X11_CreateCursor;
    mouse->CreateAnimatedCursor = X11_CreateAnimatedCursor;
    mouse->CreateSystemCursor = X11_CreateSystemCursor;
    mouse->ShowCursor = X11_ShowCursor;
    mouse->FreeCursor = X11_FreeCursor;
    mouse->WarpMouse = X11_WarpMouse;
    mouse->WarpMouseGlobal = X11_WarpMouseGlobal;
    mouse->ಗಣ_Relative_Mouse_ಬಹುಲಕ = X11_ಗಣ_Relative_Mouse_ಬಹುಲಕ;
    mouse->CaptureMouse = X11_CaptureMouse;
    mouse->GetGlobalMouseState = X11_GetGlobalMouseState;

    SDL_ದೊರಕಿತು_Test_ಫಲಿತಾಂಶ r = SDL_HITTEST_ಸಾಮಾನ್ಯ;
    ಆಗ (r <= SDL_HITTEST_RESIZE_ಎಡ) {
        ಆಯ್ಕೆ (r) {
        ಸ್ಥಿತಿ SDL_HITTEST_ಸಾಮಾನ್ಯ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ತುದಿ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಬಲ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_HITTEST_RESIZE_ಎಡ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); ನಿಲ್ಲಿಸು;
        }
        r++;
    }

    SDL_ಗಣ_Default_Cursor(X11_CreateDefaultCursor());
}

ಶೂನ್ಯ X11_QuitMouse(SDL_VideoDevice *_this)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < SDL_arraysize(sys_cursors); i++) {
        ಆದರೆ (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = ಖಾಲಿ;
        }
    }

    X11_Destroy_ಖಾಲಿಗಳು_Cursor();
}

ಶೂನ್ಯ X11_ಗಣ_ದೊರಕಿತು_Test_Cursor(SDL_ದೊರಕಿತು_Test_ಫಲಿತಾಂಶ rc)
{
    ಆದರೆ (rc == SDL_HITTEST_ಸಾಮಾನ್ಯ || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } ಇಲ್ಲದಿದ್ದರೆ {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
