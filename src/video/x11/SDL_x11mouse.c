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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#അന്തര്ഭാവ <X11/cursorfont.h>
#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "SDL_x11mouse.h"
#അന്തര്ഭാവ "SDL_x11xinput2.h"
#അന്തര്ഭാവ "SDL_x11xtest.h"
#അന്തര്ഭാവ "../SDL_video_c.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"

ഘടന SDL_CursorData
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
സ്ഥിതം Cursor x11_empty_cursor = None;
സ്ഥിതം bool x11_cursor_visible = true;

സ്ഥിതം SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ഇടത് + 1];

സ്ഥിതം Display *GetDisplay(ശൂന്യം)
{
    തിരികെ SDL_GetVideoDevice()->internal->display;
}

സ്ഥിതം Cursor X11_CreateEmptyCursor(ശൂന്യം)
{
    എങ്കിൽ (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        അക്ഷരം data[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(data);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreateBitmapFromData(display, Default_വേര്_Window(display),
                                           data, 1, 1);
        എങ്കിൽ (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    തിരികെ x11_empty_cursor;
}

സ്ഥിതം ശൂന്യം X11_DestroyEmptyCursor(ശൂന്യം)
{
    എങ്കിൽ (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

സ്ഥിതം SDL_Cursor *X11_CreateCursorAndData(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, വലുപ്പം(*cursor));
    എങ്കിൽ (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, വലുപ്പം(*data));
        എങ്കിൽ (!data) {
            SDL_free(cursor);
            തിരികെ ശൂന്യ;
        }
        data->cursor = x11_cursor;
        cursor->internal = data;
    }
    തിരികെ cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
സ്ഥിതം XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    എങ്കിൽ (!image) {
        SDL_OutOfMemory();
        തിരികെ ശൂന്യ;
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

    തിരികെ image;
}

സ്ഥിതം Cursor X11_CreateXCursorCursor(SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    എങ്കിൽ (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    തിരികെ cursor;
}

സ്ഥിതം Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, പൂർണ്ണസംഖ്യ അക്കം_frames, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(അക്കം_frames);
    എങ്കിൽ (!images) {
        SDL_OutOfMemory();
        തിരികെ None;
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < അക്കം_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        എങ്കിൽ (!image) {
            പോകുക cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    തിരികെ cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

സ്ഥിതം Cursor X11_CreatePixmapCursor(SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *data_bits, *mask_bits;
    Pixmap data_pixmap, mask_pixmap;
    പൂർണ്ണസംഖ്യ x, y;
    unsigned പൂർണ്ണസംഖ്യ rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    size_t width_bytes = ((surface->w + 7) & ~((size_t)7)) / 8;

    data_bits = SDL_calloc(1, surface->h * width_bytes);
    എങ്കിൽ (!data_bits) {
        തിരികെ None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    എങ്കിൽ (!mask_bits) {
        SDL_free(data_bits);
        തിരികെ None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    വേണ്ടി (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        വേണ്ടി (x = 0; x < surface->w; ++x) {
            പൂർണ്ണസംഖ്യ alpha = (*ptr >> 24) & 0xff;
            പൂർണ്ണസംഖ്യ red = (*ptr >> 16) & 0xff;
            പൂർണ്ണസംഖ്യ green = (*ptr >> 8) & 0xff;
            പൂർണ്ണസംഖ്യ blue = (*ptr >> 0) & 0xff;
            എങ്കിൽ (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                എങ്കിൽ ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    data_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
                } അല്ലെങ്കിൽ {
                    bgBits++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    എങ്കിൽ (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } അല്ലെങ്കിൽ {
        fg.red = fg.green = fg.blue = 0;
    }

    എങ്കിൽ (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } അല്ലെങ്കിൽ {
        bg.red = bg.green = bg.blue = 0;
    }

    data_pixmap = X11_XCreateBitmapFromData(display, Default_വേര്_Window(display),
                                            (അക്ഷരം *)data_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreateBitmapFromData(display, Default_വേര്_Window(display),
                                            (അക്ഷരം *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, data_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, data_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(data_bits);
    SDL_free(mask_bits);

    തിരികെ cursor;
}

സ്ഥിതം SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    എങ്കിൽ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#endif
    എങ്കിൽ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    തിരികെ X11_CreateCursorAndData(x11_cursor);
}

സ്ഥിതം SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, പൂർണ്ണസംഖ്യ അക്കം_frames, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    എങ്കിൽ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, അക്കം_frames, hot_x, hot_y);
    }
#endif
    എങ്കിൽ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    തിരികെ X11_CreateCursorAndData(x11_cursor);
}

സ്ഥിതം unsigned പൂർണ്ണസംഖ്യ GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    തിരഞ്ഞെടുപ്പ് (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        അവസ്ഥ SDL_SYSTEM_CURSOR_DEFAULT: തിരികെ XC_ഇടത്_ptr;
        അവസ്ഥ SDL_SYSTEM_CURSOR_TEXT: തിരികെ XC_xterm;
        അവസ്ഥ SDL_SYSTEM_CURSOR_WAIT: തിരികെ XC_watch;
        അവസ്ഥ SDL_SYSTEM_CURSOR_CROSSHAIR: തിരികെ XC_tcross;
        അവസ്ഥ SDL_SYSTEM_CURSOR_PROGRESS: തിരികെ XC_watch;
        അവസ്ഥ SDL_SYSTEM_CURSOR_NWSE_RESIZE: തിരികെ XC_മുകൾ_ഇടത്_corner;
        അവസ്ഥ SDL_SYSTEM_CURSOR_NESW_RESIZE: തിരികെ XC_മുകൾ_വലത്_corner;
        അവസ്ഥ SDL_SYSTEM_CURSOR_EW_RESIZE: തിരികെ XC_sb_h_double_arrow;
        അവസ്ഥ SDL_SYSTEM_CURSOR_NS_RESIZE: തിരികെ XC_sb_v_double_arrow;
        അവസ്ഥ SDL_SYSTEM_CURSOR_MOVE: തിരികെ XC_fleur;
        അവസ്ഥ SDL_SYSTEM_CURSOR_NOT_ALLOWED: തിരികെ XC_pirate;
        അവസ്ഥ SDL_SYSTEM_CURSOR_POINTER: തിരികെ XC_hand2;
        അവസ്ഥ SDL_SYSTEM_CURSOR_NW_RESIZE: തിരികെ XC_മുകൾ_ഇടത്_corner;
        അവസ്ഥ SDL_SYSTEM_CURSOR_N_RESIZE: തിരികെ XC_മുകൾ_side;
        അവസ്ഥ SDL_SYSTEM_CURSOR_NE_RESIZE: തിരികെ XC_മുകൾ_വലത്_corner;
        അവസ്ഥ SDL_SYSTEM_CURSOR_E_RESIZE: തിരികെ XC_വലത്_side;
        അവസ്ഥ SDL_SYSTEM_CURSOR_SE_RESIZE: തിരികെ XC_bottom_വലത്_corner;
        അവസ്ഥ SDL_SYSTEM_CURSOR_S_RESIZE: തിരികെ XC_bottom_side;
        അവസ്ഥ SDL_SYSTEM_CURSOR_SW_RESIZE: തിരികെ XC_bottom_ഇടത്_corner;
        അവസ്ഥ SDL_SYSTEM_CURSOR_W_RESIZE: തിരികെ XC_ഇടത്_side;
        അവസ്ഥ SDL_SYSTEM_CURSOR_CONTEXT_MENU: തിരികെ XC_hand2;
        അവസ്ഥ SDL_SYSTEM_CURSOR_HELP: തിരികെ XC_question_arrow;
        അവസ്ഥ SDL_SYSTEM_CURSOR_CELL: തിരികെ XC_cross;
        അവസ്ഥ SDL_SYSTEM_CURSOR_VERTICAL_TEXT: തിരികെ XC_xterm;
        അവസ്ഥ SDL_SYSTEM_CURSOR_ALIAS: തിരികെ XC_hand2;
        അവസ്ഥ SDL_SYSTEM_CURSOR_COPY: തിരികെ XC_hand2;
        അവസ്ഥ SDL_SYSTEM_CURSOR_NO_DROP: തിരികെ XC_pirate;
        അവസ്ഥ SDL_SYSTEM_CURSOR_GRAB: തിരികെ XC_hand2;
        അവസ്ഥ SDL_SYSTEM_CURSOR_GRABBING: തിരികെ XC_hand2;
        അവസ്ഥ SDL_SYSTEM_CURSOR_COL_RESIZE: തിരികെ XC_sb_h_double_arrow;
        അവസ്ഥ SDL_SYSTEM_CURSOR_ROW_RESIZE: തിരികെ XC_sb_v_double_arrow;
        അവസ്ഥ SDL_SYSTEM_CURSOR_ALL_SCROLL: തിരികെ XC_fleur;
        അവസ്ഥ SDL_SYSTEM_CURSOR_ZOOM_IN: തിരികെ XC_hand2;
        അവസ്ഥ SDL_SYSTEM_CURSOR_ZOOM_OUT: തിരികെ XC_hand2;
        അവസ്ഥ SDL_SYSTEM_CURSOR_എണ്ണം: നിർത്തുക;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    തിരികെ 0;
}

സ്ഥിതം SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = ശൂന്യ;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    എങ്കിൽ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, ശൂന്യ));
    }
#endif

    എങ്കിൽ (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    എങ്കിൽ (x11_cursor != None) {
        cursor = X11_CreateCursorAndData(x11_cursor);
    }

    തിരികെ cursor;
}

സ്ഥിതം SDL_Cursor *X11_CreateDefaultCursor(ശൂന്യം)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    തിരികെ X11_CreateSystemCursor(id);
}

സ്ഥിതം ശൂന്യം X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    എങ്കിൽ (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

സ്ഥിതം bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    എങ്കിൽ (cursor) {
        x11_cursor = cursor->internal->cursor;
    } അല്ലെങ്കിൽ {
        x11_cursor = X11_CreateEmptyCursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_Window *window;

        x11_cursor_visible = !!cursor;

        വേണ്ടി (window = video->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            എങ്കിൽ (data) {
                എങ്കിൽ (x11_cursor != None) {
                    X11_XDefineCursor(display, data->xwindow, x11_cursor);
                } അല്ലെങ്കിൽ {
                    X11_XUndefineCursor(display, data->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    തിരികെ true;
}

സ്ഥിതം ശൂന്യം X11_WarpMouseInternal(Window xwindow, ദശാംശം x, ദശാംശം y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    എങ്കിൽ (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    എങ്കിൽ (warp_hack) {
        X11_ShowCursor(ശൂന്യ);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    പൂർണ്ണസംഖ്യ deviceid = 0;
    എങ്കിൽ (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        എങ്കിൽ (Screen_എണ്ണം(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    എങ്കിൽ (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } അല്ലെങ്കിൽ
#endif
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (പൂർണ്ണസംഖ്യ)x, (പൂർണ്ണസംഖ്യ)y);
    }

    എങ്കിൽ (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

സ്ഥിതം bool X11_WarpMouse(SDL_Window *window, ദശാംശം x, ദശാംശം y)
{
    SDL_WindowData *data = window->internal;

    എങ്കിൽ (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        തിരികെ true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    എങ്കിൽ (data->pointer_barrier_active == false) {
        X11_WarpMouseInternal(data->xwindow, x, y);
    }
#അല്ലെങ്കിൽ
    X11_WarpMouseInternal(data->xwindow, x, y);
#endif
    തിരികെ true;
}

സ്ഥിതം bool X11_WarpMouseGlobal(ദശാംശം x, ദശാംശം y)
{
    എങ്കിൽ (X11_WarpMouseXTest(SDL_GetVideoDevice(), ശൂന്യ, x, y)) {
        തിരികെ true;
    }

    X11_WarpMouseInternal(Default_വേര്_Window(GetDisplay()), x, y);
    തിരികെ true;
}

സ്ഥിതം bool X11_SetRelativeMouseMode(bool enabled)
{
    എങ്കിൽ (!X11_Xinput2IsInitialized()) {
        തിരികെ SDL_Unsupported();
    }
    തിരികെ true;
}

സ്ഥിതം bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    എങ്കിൽ (window) {
        SDL_WindowData *data = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        എങ്കിൽ (!data->xinput2_mouse_enabled || data->mouse_grabbed) {
            സ്ഥിരം unsigned പൂർണ്ണസംഖ്യ mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (data->mouse_grabbed ? data->xwindow : None);
            സ്ഥിരം പൂർണ്ണസംഖ്യ rc = X11_XGrabPointer(display, data->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            എങ്കിൽ (rc != GrabSuccess) {
                തിരികെ SDL_SetError("X server refused mouse capture");
            }

            എങ്കിൽ (data->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                data->videodata->global_mouse_changed = true;
            }
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } അല്ലെങ്കിൽ {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    തിരികെ true;
}

സ്ഥിതം SDL_MouseButtonFlags X11_GetGlobalMouseState(ദശാംശം *x, ദശാംശം *y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    പൂർണ്ണസംഖ്യ i;

    // !!! FIXME: should we XSync() here first?

    എങ്കിൽ (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    എങ്കിൽ (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(ശൂന്യ);
        എങ്കിൽ (displays) {
            വേണ്ടി (i = 0; displays[i]; ++i) {
                SDL_DisplayData *data = SDL_GetDisplayDriverData(displays[i]);
                എങ്കിൽ (data) {
                    Window വേര്, child;
                    പൂർണ്ണസംഖ്യ rootx, rooty, winx, winy;
                    unsigned പൂർണ്ണസംഖ്യ mask;
                    എങ്കിൽ (X11_XQueryPointer(display, വേര്_Window(display, data->screen), &വേര്, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes വേര്_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(ശൂന്യ, ശൂന്യ) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, വേര്, &വേര്_attrs);
                        videodata->global_mouse_position.x = വേര്_attrs.x + rootx;
                        videodata->global_mouse_position.y = വേര്_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        നിർത്തുക;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (ദശാംശം)videodata->global_mouse_position.x;
    *y = (ദശാംശം)videodata->global_mouse_position.y;
    തിരികെ videodata->global_mouse_buttons;
}

ശൂന്യം X11_InitMouse(SDL_VideoDevice *_this)
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
    ആകുമ്പോൾ (r <= SDL_HITTEST_RESIZE_ഇടത്) {
        തിരഞ്ഞെടുപ്പ് (r) {
        അവസ്ഥ SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_മുകൾ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_വലത്: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); നിർത്തുക;
        അവസ്ഥ SDL_HITTEST_RESIZE_ഇടത്: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); നിർത്തുക;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

ശൂന്യം X11_QuitMouse(SDL_VideoDevice *_this)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < SDL_arraysize(sys_cursors); i++) {
        എങ്കിൽ (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = ശൂന്യ;
        }
    }

    X11_DestroyEmptyCursor();
}

ശൂന്യം X11_SetHitTestCursor(SDL_HitTestResult rc)
{
    എങ്കിൽ (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } അല്ലെങ്കിൽ {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
