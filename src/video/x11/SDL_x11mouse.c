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

#ಅನ್ತರ್ಭಾವ <X11/cursorfont.h>
#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11mouse.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xinput2.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xtest.h"
#ಅನ್ತರ್ಭಾವ "../SDL_video_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

ಸಂರಚನಾ SDL_CursorData
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
ಸ್ಥಿರ Cursor x11_empty_cursor = None;
ಸ್ಥಿರ bool x11_cursor_visible = true;

ಸ್ಥಿರ SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ಎಡ + 1];

ಸ್ಥಿರ Display *GetDisplay(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ SDL_GetVideoDevice()->internal->display;
}

ಸ್ಥಿರ Cursor X11_CreateEmptyCursor(ಶೂನ್ಯ)
{
    ಯದಿ (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        ವರ್ಣ data[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(data);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreateBitmapFromData(display, Default_ಬೇರು_Window(display),
                                           data, 1, 1);
        ಯದಿ (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    ಪ್ರತ್ಯಾಗಮ x11_empty_cursor;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_DestroyEmptyCursor(ಶೂನ್ಯ)
{
    ಯದಿ (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

ಸ್ಥಿರ SDL_Cursor *X11_CreateCursorAndData(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ಪರಿಮಾಣ(*cursor));
    ಯದಿ (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, ಪರಿಮಾಣ(*data));
        ಯದಿ (!data) {
            SDL_free(cursor);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        data->cursor = x11_cursor;
        cursor->internal = data;
    }
    ಪ್ರತ್ಯಾಗಮ cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
ಸ್ಥಿರ XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    ಯದಿ (!image) {
        SDL_OutOfMemory();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
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

    ಪ್ರತ್ಯಾಗಮ image;
}

ಸ್ಥಿರ Cursor X11_CreateXCursorCursor(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    ಯದಿ (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    ಪ್ರತ್ಯಾಗಮ cursor;
}

ಸ್ಥಿರ Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_frames, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(ಅಂಕೆ_frames);
    ಯದಿ (!images) {
        SDL_OutOfMemory();
        ಪ್ರತ್ಯಾಗಮ None;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        ಯದಿ (!image) {
            ಗಚ್ಛ cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    ಪ್ರತ್ಯಾಗಮ cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

ಸ್ಥಿರ Cursor X11_CreatePixmapCursor(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *data_bits, *mask_bits;
    Pixmap data_pixmap, mask_pixmap;
    ಪೂರ್ಣಾಙ್ಕ x, y;
    unsigned ಪೂರ್ಣಾಙ್ಕ rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    size_t width_bytes = ((surface->w + 7) & ~((size_t)7)) / 8;

    data_bits = SDL_calloc(1, surface->h * width_bytes);
    ಯದಿ (!data_bits) {
        ಪ್ರತ್ಯಾಗಮ None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    ಯದಿ (!mask_bits) {
        SDL_free(data_bits);
        ಪ್ರತ್ಯಾಗಮ None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    ಪ್ರತಿ (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        ಪ್ರತಿ (x = 0; x < surface->w; ++x) {
            ಪೂರ್ಣಾಙ್ಕ alpha = (*ptr >> 24) & 0xff;
            ಪೂರ್ಣಾಙ್ಕ red = (*ptr >> 16) & 0xff;
            ಪೂರ್ಣಾಙ್ಕ green = (*ptr >> 8) & 0xff;
            ಪೂರ್ಣಾಙ್ಕ blue = (*ptr >> 0) & 0xff;
            ಯದಿ (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                ಯದಿ ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    data_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
                } ಅನ್ಯಥಾ {
                    bgBits++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    ಯದಿ (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } ಅನ್ಯಥಾ {
        fg.red = fg.green = fg.blue = 0;
    }

    ಯದಿ (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } ಅನ್ಯಥಾ {
        bg.red = bg.green = bg.blue = 0;
    }

    data_pixmap = X11_XCreateBitmapFromData(display, Default_ಬೇರು_Window(display),
                                            (ವರ್ಣ *)data_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreateBitmapFromData(display, Default_ಬೇರು_Window(display),
                                            (ವರ್ಣ *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, data_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, data_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(data_bits);
    SDL_free(mask_bits);

    ಪ್ರತ್ಯಾಗಮ cursor;
}

ಸ್ಥಿರ SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    ಯದಿ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#endif
    ಯದಿ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    ಪ್ರತ್ಯಾಗಮ X11_CreateCursorAndData(x11_cursor);
}

ಸ್ಥಿರ SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_frames, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    ಯದಿ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, ಅಂಕೆ_frames, hot_x, hot_y);
    }
#endif
    ಯದಿ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    ಪ್ರತ್ಯಾಗಮ X11_CreateCursorAndData(x11_cursor);
}

ಸ್ಥಿರ unsigned ಪೂರ್ಣಾಙ್ಕ GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    ವಿಕಲ್ಪ (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_DEFAULT: ಪ್ರತ್ಯಾಗಮ XC_ಎಡ_ptr;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_TEXT: ಪ್ರತ್ಯಾಗಮ XC_xterm;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_WAIT: ಪ್ರತ್ಯಾಗಮ XC_watch;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_CROSSHAIR: ಪ್ರತ್ಯಾಗಮ XC_tcross;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_PROGRESS: ಪ್ರತ್ಯಾಗಮ XC_watch;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_NWSE_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_ತುದಿ_ಎಡ_corner;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_NESW_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_ತುದಿ_ಬಲ_corner;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_EW_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_sb_h_double_arrow;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_NS_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_sb_v_double_arrow;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_MOVE: ಪ್ರತ್ಯಾಗಮ XC_fleur;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_NOT_ALLOWED: ಪ್ರತ್ಯಾಗಮ XC_pirate;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_POINTER: ಪ್ರತ್ಯಾಗಮ XC_hand2;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_NW_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_ತುದಿ_ಎಡ_corner;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_N_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_ತುದಿ_side;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_NE_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_ತುದಿ_ಬಲ_corner;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_E_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_ಬಲ_side;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_SE_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_bottom_ಬಲ_corner;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_S_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_bottom_side;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_SW_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_bottom_ಎಡ_corner;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_W_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_ಎಡ_side;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_CONTEXT_MENU: ಪ್ರತ್ಯಾಗಮ XC_hand2;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_HELP: ಪ್ರತ್ಯಾಗಮ XC_question_arrow;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_CELL: ಪ್ರತ್ಯಾಗಮ XC_cross;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_VERTICAL_TEXT: ಪ್ರತ್ಯಾಗಮ XC_xterm;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_ALIAS: ಪ್ರತ್ಯಾಗಮ XC_hand2;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_COPY: ಪ್ರತ್ಯಾಗಮ XC_hand2;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_NO_DROP: ಪ್ರತ್ಯಾಗಮ XC_pirate;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_GRAB: ಪ್ರತ್ಯಾಗಮ XC_hand2;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_GRABBING: ಪ್ರತ್ಯಾಗಮ XC_hand2;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_COL_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_sb_h_double_arrow;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_ROW_RESIZE: ಪ್ರತ್ಯಾಗಮ XC_sb_v_double_arrow;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_ALL_SCROLL: ಪ್ರತ್ಯಾಗಮ XC_fleur;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_ZOOM_IN: ಪ್ರತ್ಯಾಗಮ XC_hand2;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_ZOOM_OUT: ಪ್ರತ್ಯಾಗಮ XC_hand2;
        ಪಕ್ಷ SDL_SYSTEM_CURSOR_ಎಣಿಕೆ: ಭಙ್ಗ;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = ರಿಕ್ತ;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    ಯದಿ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, ರಿಕ್ತ));
    }
#endif

    ಯದಿ (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    ಯದಿ (x11_cursor != None) {
        cursor = X11_CreateCursorAndData(x11_cursor);
    }

    ಪ್ರತ್ಯಾಗಮ cursor;
}

ಸ್ಥಿರ SDL_Cursor *X11_CreateDefaultCursor(ಶೂನ್ಯ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ಪ್ರತ್ಯಾಗಮ X11_CreateSystemCursor(id);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    ಯದಿ (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ಸ್ಥಿರ bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    ಯದಿ (cursor) {
        x11_cursor = cursor->internal->cursor;
    } ಅನ್ಯಥಾ {
        x11_cursor = X11_CreateEmptyCursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_Window *window;

        x11_cursor_visible = !!cursor;

        ಪ್ರತಿ (window = video->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            ಯದಿ (data) {
                ಯದಿ (x11_cursor != None) {
                    X11_XDefineCursor(display, data->xwindow, x11_cursor);
                } ಅನ್ಯಥಾ {
                    X11_XUndefineCursor(display, data->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_WarpMouseInternal(Window xwindow, ಭಿನ್ನ x, ಭಿನ್ನ y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    ಯದಿ (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    ಯದಿ (warp_hack) {
        X11_ShowCursor(ರಿಕ್ತ);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ಪೂರ್ಣಾಙ್ಕ deviceid = 0;
    ಯದಿ (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        ಯದಿ (Screen_ಎಣಿಕೆ(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    ಯದಿ (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } ಅನ್ಯಥಾ
#endif
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (ಪೂರ್ಣಾಙ್ಕ)x, (ಪೂರ್ಣಾಙ್ಕ)y);
    }

    ಯದಿ (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

ಸ್ಥಿರ bool X11_WarpMouse(SDL_Window *window, ಭಿನ್ನ x, ಭಿನ್ನ y)
{
    SDL_WindowData *data = window->internal;

    ಯದಿ (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    ಯದಿ (data->pointer_barrier_active == false) {
        X11_WarpMouseInternal(data->xwindow, x, y);
    }
#ಅನ್ಯಥಾ
    X11_WarpMouseInternal(data->xwindow, x, y);
#endif
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool X11_WarpMouseGlobal(ಭಿನ್ನ x, ಭಿನ್ನ y)
{
    ಯದಿ (X11_WarpMouseXTest(SDL_GetVideoDevice(), ರಿಕ್ತ, x, y)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    X11_WarpMouseInternal(Default_ಬೇರು_Window(GetDisplay()), x, y);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool X11_SetRelativeMouseMode(bool enabled)
{
    ಯದಿ (!X11_Xinput2IsInitialized()) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    ಯದಿ (window) {
        SDL_WindowData *data = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        ಯದಿ (!data->xinput2_mouse_enabled || data->mouse_grabbed) {
            ಧ್ರುವ unsigned ಪೂರ್ಣಾಙ್ಕ mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (data->mouse_grabbed ? data->xwindow : None);
            ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ rc = X11_XGrabPointer(display, data->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            ಯದಿ (rc != GrabSuccess) {
                ಪ್ರತ್ಯಾಗಮ SDL_SetError("X server refused mouse capture");
            }

            ಯದಿ (data->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                data->videodata->global_mouse_changed = true;
            }
        }
    } ಅನ್ಯಥಾ ಯದಿ (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } ಅನ್ಯಥಾ {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ SDL_MouseButtonFlags X11_GetGlobalMouseState(ಭಿನ್ನ *x, ಭಿನ್ನ *y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    ಪೂರ್ಣಾಙ್ಕ i;

    // !!! FIXME: should we XSync() here first?

    ಯದಿ (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    ಯದಿ (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(ರಿಕ್ತ);
        ಯದಿ (displays) {
            ಪ್ರತಿ (i = 0; displays[i]; ++i) {
                SDL_DisplayData *data = SDL_GetDisplayDriverData(displays[i]);
                ಯದಿ (data) {
                    Window ಬೇರು, child;
                    ಪೂರ್ಣಾಙ್ಕ rootx, rooty, winx, winy;
                    unsigned ಪೂರ್ಣಾಙ್ಕ mask;
                    ಯದಿ (X11_XQueryPointer(display, ಬೇರು_Window(display, data->screen), &ಬೇರು, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes ಬೇರು_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(ರಿಕ್ತ, ರಿಕ್ತ) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, ಬೇರು, &ಬೇರು_attrs);
                        videodata->global_mouse_position.x = ಬೇರು_attrs.x + rootx;
                        videodata->global_mouse_position.y = ಬೇರು_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        ಭಙ್ಗ;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (ಭಿನ್ನ)videodata->global_mouse_position.x;
    *y = (ಭಿನ್ನ)videodata->global_mouse_position.y;
    ಪ್ರತ್ಯಾಗಮ videodata->global_mouse_buttons;
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
    mouse->SetRelativeMouseMode = X11_SetRelativeMouseMode;
    mouse->CaptureMouse = X11_CaptureMouse;
    mouse->GetGlobalMouseState = X11_GetGlobalMouseState;

    SDL_HitTestResult r = SDL_HITTEST_NORMAL;
    ಯಾವತ್ (r <= SDL_HITTEST_RESIZE_ಎಡ) {
        ವಿಕಲ್ಪ (r) {
        ಪಕ್ಷ SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ತುದಿ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ಬಲ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); ಭಙ್ಗ;
        ಪಕ್ಷ SDL_HITTEST_RESIZE_ಎಡ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); ಭಙ್ಗ;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

ಶೂನ್ಯ X11_QuitMouse(SDL_VideoDevice *_this)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < SDL_arraysize(sys_cursors); i++) {
        ಯದಿ (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = ರಿಕ್ತ;
        }
    }

    X11_DestroyEmptyCursor();
}

ಶೂನ್ಯ X11_SetHitTestCursor(SDL_HitTestResult rc)
{
    ಯದಿ (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } ಅನ್ಯಥಾ {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
