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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ଅନ୍ତର୍ଭାଵ <X11/cursorfont.h>
#ଅନ୍ତର୍ଭାଵ "SDL_x11video.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11mouse.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11xinput2.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11xtest.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_video_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"

ସଂରଚନା SDL_CursorData
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
ସ୍ଥିର Cursor x11_empty_cursor = None;
ସ୍ଥିର bool x11_cursor_visible = true;

ସ୍ଥିର SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ବାମ + 1];

ସ୍ଥିର Display *GetDisplay(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ SDL_GetVideoDevice()->internal->display;
}

ସ୍ଥିର Cursor X11_CreateEmptyCursor(ଶୂନ୍ୟ)
{
    ଯଦି (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        ଅକ୍ଷର data[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(data);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreateBitmapFromData(display, Default_ମୂଳ_Window(display),
                                           data, 1, 1);
        ଯଦି (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    ଫେରନ୍ତୁ x11_empty_cursor;
}

ସ୍ଥିର ଶୂନ୍ୟ X11_DestroyEmptyCursor(ଶୂନ୍ୟ)
{
    ଯଦି (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

ସ୍ଥିର SDL_Cursor *X11_CreateCursorAndData(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ଆକାର(*cursor));
    ଯଦି (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, ଆକାର(*data));
        ଯଦି (!data) {
            SDL_free(cursor);
            ଫେରନ୍ତୁ ଖାଲି;
        }
        data->cursor = x11_cursor;
        cursor->internal = data;
    }
    ଫେରନ୍ତୁ cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
ସ୍ଥିର XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    ଯଦି (!image) {
        SDL_OutOfMemory();
        ଫେରନ୍ତୁ ଖାଲି;
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

    ଫେରନ୍ତୁ image;
}

ସ୍ଥିର Cursor X11_CreateXCursorCursor(SDL_Surface *surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    ଯଦି (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    ଫେରନ୍ତୁ cursor;
}

ସ୍ଥିର Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_frames, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(ଅଙ୍କ_frames);
    ଯଦି (!images) {
        SDL_OutOfMemory();
        ଫେରନ୍ତୁ None;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        ଯଦି (!image) {
            ଯାଅ cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    ଫେରନ୍ତୁ cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

ସ୍ଥିର Cursor X11_CreatePixmapCursor(SDL_Surface *surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *data_bits, *mask_bits;
    Pixmap data_pixmap, mask_pixmap;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    size_t width_bytes = ((surface->w + 7) & ~((size_t)7)) / 8;

    data_bits = SDL_calloc(1, surface->h * width_bytes);
    ଯଦି (!data_bits) {
        ଫେରନ୍ତୁ None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    ଯଦି (!mask_bits) {
        SDL_free(data_bits);
        ଫେରନ୍ତୁ None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    ପାଇଁ (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        ପାଇଁ (x = 0; x < surface->w; ++x) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା alpha = (*ptr >> 24) & 0xff;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା red = (*ptr >> 16) & 0xff;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା green = (*ptr >> 8) & 0xff;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା blue = (*ptr >> 0) & 0xff;
            ଯଦି (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                ଯଦି ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    data_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
                } ଅନ୍ୟଥା {
                    bgBits++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    ଯଦି (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } ଅନ୍ୟଥା {
        fg.red = fg.green = fg.blue = 0;
    }

    ଯଦି (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } ଅନ୍ୟଥା {
        bg.red = bg.green = bg.blue = 0;
    }

    data_pixmap = X11_XCreateBitmapFromData(display, Default_ମୂଳ_Window(display),
                                            (ଅକ୍ଷର *)data_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreateBitmapFromData(display, Default_ମୂଳ_Window(display),
                                            (ଅକ୍ଷର *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, data_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, data_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(data_bits);
    SDL_free(mask_bits);

    ଫେରନ୍ତୁ cursor;
}

ସ୍ଥିର SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    ଯଦି (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#endif
    ଯଦି (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    ଫେରନ୍ତୁ X11_CreateCursorAndData(x11_cursor);
}

ସ୍ଥିର SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_frames, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    ଯଦି (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, ଅଙ୍କ_frames, hot_x, hot_y);
    }
#endif
    ଯଦି (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    ଫେରନ୍ତୁ X11_CreateCursorAndData(x11_cursor);
}

ସ୍ଥିର unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    ବାଛ (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_DEFAULT: ଫେରନ୍ତୁ XC_ବାମ_ptr;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_TEXT: ଫେରନ୍ତୁ XC_xterm;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_WAIT: ଫେରନ୍ତୁ XC_watch;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_CROSSHAIR: ଫେରନ୍ତୁ XC_tcross;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_PROGRESS: ଫେରନ୍ତୁ XC_watch;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_NWSE_RESIZE: ଫେରନ୍ତୁ XC_ଶୀର୍ଷ_ବାମ_corner;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_NESW_RESIZE: ଫେରନ୍ତୁ XC_ଶୀର୍ଷ_ଡାହାଣ_corner;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_EW_RESIZE: ଫେରନ୍ତୁ XC_sb_h_double_arrow;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_NS_RESIZE: ଫେରନ୍ତୁ XC_sb_v_double_arrow;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_MOVE: ଫେରନ୍ତୁ XC_fleur;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_NOT_ALLOWED: ଫେରନ୍ତୁ XC_pirate;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_POINTER: ଫେରନ୍ତୁ XC_hand2;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_NW_RESIZE: ଫେରନ୍ତୁ XC_ଶୀର୍ଷ_ବାମ_corner;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_N_RESIZE: ଫେରନ୍ତୁ XC_ଶୀର୍ଷ_side;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_NE_RESIZE: ଫେରନ୍ତୁ XC_ଶୀର୍ଷ_ଡାହାଣ_corner;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_E_RESIZE: ଫେରନ୍ତୁ XC_ଡାହାଣ_side;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_SE_RESIZE: ଫେରନ୍ତୁ XC_bottom_ଡାହାଣ_corner;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_S_RESIZE: ଫେରନ୍ତୁ XC_bottom_side;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_SW_RESIZE: ଫେରନ୍ତୁ XC_bottom_ବାମ_corner;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_W_RESIZE: ଫେରନ୍ତୁ XC_ବାମ_side;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_CONTEXT_MENU: ଫେରନ୍ତୁ XC_hand2;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_HELP: ଫେରନ୍ତୁ XC_question_arrow;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_CELL: ଫେରନ୍ତୁ XC_cross;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_VERTICAL_TEXT: ଫେରନ୍ତୁ XC_xterm;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_ALIAS: ଫେରନ୍ତୁ XC_hand2;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_COPY: ଫେରନ୍ତୁ XC_hand2;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_NO_DROP: ଫେରନ୍ତୁ XC_pirate;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_GRAB: ଫେରନ୍ତୁ XC_hand2;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_GRABBING: ଫେରନ୍ତୁ XC_hand2;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_COL_RESIZE: ଫେରନ୍ତୁ XC_sb_h_double_arrow;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_ROW_RESIZE: ଫେରନ୍ତୁ XC_sb_v_double_arrow;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_ALL_SCROLL: ଫେରନ୍ତୁ XC_fleur;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_ZOOM_IN: ଫେରନ୍ତୁ XC_hand2;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_ZOOM_OUT: ଫେରନ୍ତୁ XC_hand2;
        ସ୍ଥିତି SDL_SYSTEM_CURSOR_ଗଣନା: ଭାଙ୍ଗ;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = ଖାଲି;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    ଯଦି (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, ଖାଲି));
    }
#endif

    ଯଦି (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    ଯଦି (x11_cursor != None) {
        cursor = X11_CreateCursorAndData(x11_cursor);
    }

    ଫେରନ୍ତୁ cursor;
}

ସ୍ଥିର SDL_Cursor *X11_CreateDefaultCursor(ଶୂନ୍ୟ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ଫେରନ୍ତୁ X11_CreateSystemCursor(id);
}

ସ୍ଥିର ଶୂନ୍ୟ X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    ଯଦି (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ସ୍ଥିର bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    ଯଦି (cursor) {
        x11_cursor = cursor->internal->cursor;
    } ଅନ୍ୟଥା {
        x11_cursor = X11_CreateEmptyCursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_Window *window;

        x11_cursor_visible = !!cursor;

        ପାଇଁ (window = video->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            ଯଦି (data) {
                ଯଦି (x11_cursor != None) {
                    X11_XDefineCursor(display, data->xwindow, x11_cursor);
                } ଅନ୍ୟଥା {
                    X11_XUndefineCursor(display, data->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର ଶୂନ୍ୟ X11_WarpMouseInternal(Window xwindow, ଦଶମିକ x, ଦଶମିକ y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    ଯଦି (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    ଯଦି (warp_hack) {
        X11_ShowCursor(ଖାଲି);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid = 0;
    ଯଦି (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        ଯଦି (Screen_ଗଣନା(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    ଯଦି (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } ଅନ୍ୟଥା
#endif
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)x, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)y);
    }

    ଯଦି (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

ସ୍ଥିର bool X11_WarpMouse(SDL_Window *window, ଦଶମିକ x, ଦଶମିକ y)
{
    SDL_WindowData *data = window->internal;

    ଯଦି (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        ଫେରନ୍ତୁ true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    ଯଦି (data->pointer_barrier_active == false) {
        X11_WarpMouseInternal(data->xwindow, x, y);
    }
#ଅନ୍ୟଥା
    X11_WarpMouseInternal(data->xwindow, x, y);
#endif
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool X11_WarpMouseGlobal(ଦଶମିକ x, ଦଶମିକ y)
{
    ଯଦି (X11_WarpMouseXTest(SDL_GetVideoDevice(), ଖାଲି, x, y)) {
        ଫେରନ୍ତୁ true;
    }

    X11_WarpMouseInternal(Default_ମୂଳ_Window(GetDisplay()), x, y);
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool X11_SetRelativeMouseMode(bool enabled)
{
    ଯଦି (!X11_Xinput2IsInitialized()) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    ଯଦି (window) {
        SDL_WindowData *data = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        ଯଦି (!data->xinput2_mouse_enabled || data->mouse_grabbed) {
            ଅଚଳ unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (data->mouse_grabbed ? data->xwindow : None);
            ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା rc = X11_XGrabPointer(display, data->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            ଯଦି (rc != GrabSuccess) {
                ଫେରନ୍ତୁ SDL_SetError("X server refused mouse capture");
            }

            ଯଦି (data->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                data->videodata->global_mouse_changed = true;
            }
        }
    } ଅନ୍ୟଥା ଯଦି (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } ଅନ୍ୟଥା {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର SDL_MouseButtonFlags X11_GetGlobalMouseState(ଦଶମିକ *x, ଦଶମିକ *y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    // !!! FIXME: should we XSync() here first?

    ଯଦି (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    ଯଦି (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(ଖାଲି);
        ଯଦି (displays) {
            ପାଇଁ (i = 0; displays[i]; ++i) {
                SDL_DisplayData *data = SDL_GetDisplayDriverData(displays[i]);
                ଯଦି (data) {
                    Window ମୂଳ, child;
                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rootx, rooty, winx, winy;
                    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask;
                    ଯଦି (X11_XQueryPointer(display, ମୂଳ_Window(display, data->screen), &ମୂଳ, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes ମୂଳ_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(ଖାଲି, ଖାଲି) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, ମୂଳ, &ମୂଳ_attrs);
                        videodata->global_mouse_position.x = ମୂଳ_attrs.x + rootx;
                        videodata->global_mouse_position.y = ମୂଳ_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        ଭାଙ୍ଗ;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (ଦଶମିକ)videodata->global_mouse_position.x;
    *y = (ଦଶମିକ)videodata->global_mouse_position.y;
    ଫେରନ୍ତୁ videodata->global_mouse_buttons;
}

ଶୂନ୍ୟ X11_InitMouse(SDL_VideoDevice *_this)
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
    ଯେତେବେଳେ (r <= SDL_HITTEST_RESIZE_ବାମ) {
        ବାଛ (r) {
        ସ୍ଥିତି SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_ଶୀର୍ଷ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_ଡାହାଣ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_HITTEST_RESIZE_ବାମ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); ଭାଙ୍ଗ;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

ଶୂନ୍ୟ X11_QuitMouse(SDL_VideoDevice *_this)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < SDL_arraysize(sys_cursors); i++) {
        ଯଦି (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = ଖାଲି;
        }
    }

    X11_DestroyEmptyCursor();
}

ଶୂନ୍ୟ X11_SetHitTestCursor(SDL_HitTestResult rc)
{
    ଯଦି (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } ଅନ୍ୟଥା {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
