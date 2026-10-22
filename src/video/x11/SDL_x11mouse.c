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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#અન્તર્ભાવ <X11/cursorfont.h>
#અન્તર્ભાવ "SDL_x11video.h"
#અન્તર્ભાવ "SDL_x11mouse.h"
#અન્તર્ભાવ "SDL_x11xinput2.h"
#અન્તર્ભાવ "SDL_x11xtest.h"
#અન્તર્ભાવ "../SDL_video_c.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"

સંરચના SDL_CursorData
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
સ્થિર Cursor x11_empty_cursor = None;
સ્થિર bool x11_cursor_visible = true;

સ્થિર SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ડાબું + 1];

સ્થિર Display *GetDisplay(શૂન્ય)
{
    પાછા SDL_GetVideoDevice()->internal->display;
}

સ્થિર Cursor X11_CreateEmptyCursor(શૂન્ય)
{
    જો (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        અક્ષર data[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(data);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreateBitmapFromData(display, Default_મૂળ_Window(display),
                                           data, 1, 1);
        જો (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    પાછા x11_empty_cursor;
}

સ્થિર શૂન્ય X11_DestroyEmptyCursor(શૂન્ય)
{
    જો (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

સ્થિર SDL_Cursor *X11_CreateCursorAndData(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, કદ(*cursor));
    જો (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, કદ(*data));
        જો (!data) {
            SDL_free(cursor);
            પાછા ખાલી;
        }
        data->cursor = x11_cursor;
        cursor->internal = data;
    }
    પાછા cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
સ્થિર XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    જો (!image) {
        SDL_OutOfMemory();
        પાછા ખાલી;
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

    પાછા image;
}

સ્થિર Cursor X11_CreateXCursorCursor(SDL_Surface *surface, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    જો (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    પાછા cursor;
}

સ્થિર Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, પૂર્ણાંક અંક_frames, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(અંક_frames);
    જો (!images) {
        SDL_OutOfMemory();
        પાછા None;
    }

    માટે (પૂર્ણાંક i = 0; i < અંક_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        જો (!image) {
            જાઓ cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    પાછા cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

સ્થિર Cursor X11_CreatePixmapCursor(SDL_Surface *surface, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *data_bits, *mask_bits;
    Pixmap data_pixmap, mask_pixmap;
    પૂર્ણાંક x, y;
    unsigned પૂર્ણાંક rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    size_t width_bytes = ((surface->w + 7) & ~((size_t)7)) / 8;

    data_bits = SDL_calloc(1, surface->h * width_bytes);
    જો (!data_bits) {
        પાછા None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    જો (!mask_bits) {
        SDL_free(data_bits);
        પાછા None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    માટે (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        માટે (x = 0; x < surface->w; ++x) {
            પૂર્ણાંક alpha = (*ptr >> 24) & 0xff;
            પૂર્ણાંક red = (*ptr >> 16) & 0xff;
            પૂર્ણાંક green = (*ptr >> 8) & 0xff;
            પૂર્ણાંક blue = (*ptr >> 0) & 0xff;
            જો (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                જો ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    data_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
                } નહીંતર {
                    bgBits++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    જો (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } નહીંતર {
        fg.red = fg.green = fg.blue = 0;
    }

    જો (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } નહીંતર {
        bg.red = bg.green = bg.blue = 0;
    }

    data_pixmap = X11_XCreateBitmapFromData(display, Default_મૂળ_Window(display),
                                            (અક્ષર *)data_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreateBitmapFromData(display, Default_મૂળ_Window(display),
                                            (અક્ષર *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, data_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, data_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(data_bits);
    SDL_free(mask_bits);

    પાછા cursor;
}

સ્થિર SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    જો (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#endif
    જો (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    પાછા X11_CreateCursorAndData(x11_cursor);
}

સ્થિર SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, પૂર્ણાંક અંક_frames, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    જો (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, અંક_frames, hot_x, hot_y);
    }
#endif
    જો (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    પાછા X11_CreateCursorAndData(x11_cursor);
}

સ્થિર unsigned પૂર્ણાંક GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    પસંદગી (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        સ્થિતિ SDL_SYSTEM_CURSOR_DEFAULT: પાછા XC_ડાબું_ptr;
        સ્થિતિ SDL_SYSTEM_CURSOR_TEXT: પાછા XC_xterm;
        સ્થિતિ SDL_SYSTEM_CURSOR_WAIT: પાછા XC_watch;
        સ્થિતિ SDL_SYSTEM_CURSOR_CROSSHAIR: પાછા XC_tcross;
        સ્થિતિ SDL_SYSTEM_CURSOR_PROGRESS: પાછા XC_watch;
        સ્થિતિ SDL_SYSTEM_CURSOR_NWSE_RESIZE: પાછા XC_ટોચ_ડાબું_corner;
        સ્થિતિ SDL_SYSTEM_CURSOR_NESW_RESIZE: પાછા XC_ટોચ_જમણું_corner;
        સ્થિતિ SDL_SYSTEM_CURSOR_EW_RESIZE: પાછા XC_sb_h_double_arrow;
        સ્થિતિ SDL_SYSTEM_CURSOR_NS_RESIZE: પાછા XC_sb_v_double_arrow;
        સ્થિતિ SDL_SYSTEM_CURSOR_MOVE: પાછા XC_fleur;
        સ્થિતિ SDL_SYSTEM_CURSOR_NOT_ALLOWED: પાછા XC_pirate;
        સ્થિતિ SDL_SYSTEM_CURSOR_POINTER: પાછા XC_hand2;
        સ્થિતિ SDL_SYSTEM_CURSOR_NW_RESIZE: પાછા XC_ટોચ_ડાબું_corner;
        સ્થિતિ SDL_SYSTEM_CURSOR_N_RESIZE: પાછા XC_ટોચ_side;
        સ્થિતિ SDL_SYSTEM_CURSOR_NE_RESIZE: પાછા XC_ટોચ_જમણું_corner;
        સ્થિતિ SDL_SYSTEM_CURSOR_E_RESIZE: પાછા XC_જમણું_side;
        સ્થિતિ SDL_SYSTEM_CURSOR_SE_RESIZE: પાછા XC_bottom_જમણું_corner;
        સ્થિતિ SDL_SYSTEM_CURSOR_S_RESIZE: પાછા XC_bottom_side;
        સ્થિતિ SDL_SYSTEM_CURSOR_SW_RESIZE: પાછા XC_bottom_ડાબું_corner;
        સ્થિતિ SDL_SYSTEM_CURSOR_W_RESIZE: પાછા XC_ડાબું_side;
        સ્થિતિ SDL_SYSTEM_CURSOR_CONTEXT_MENU: પાછા XC_hand2;
        સ્થિતિ SDL_SYSTEM_CURSOR_HELP: પાછા XC_question_arrow;
        સ્થિતિ SDL_SYSTEM_CURSOR_CELL: પાછા XC_cross;
        સ્થિતિ SDL_SYSTEM_CURSOR_VERTICAL_TEXT: પાછા XC_xterm;
        સ્થિતિ SDL_SYSTEM_CURSOR_ALIAS: પાછા XC_hand2;
        સ્થિતિ SDL_SYSTEM_CURSOR_COPY: પાછા XC_hand2;
        સ્થિતિ SDL_SYSTEM_CURSOR_NO_DROP: પાછા XC_pirate;
        સ્થિતિ SDL_SYSTEM_CURSOR_GRAB: પાછા XC_hand2;
        સ્થિતિ SDL_SYSTEM_CURSOR_GRABBING: પાછા XC_hand2;
        સ્થિતિ SDL_SYSTEM_CURSOR_COL_RESIZE: પાછા XC_sb_h_double_arrow;
        સ્થિતિ SDL_SYSTEM_CURSOR_ROW_RESIZE: પાછા XC_sb_v_double_arrow;
        સ્થિતિ SDL_SYSTEM_CURSOR_ALL_SCROLL: પાછા XC_fleur;
        સ્થિતિ SDL_SYSTEM_CURSOR_ZOOM_IN: પાછા XC_hand2;
        સ્થિતિ SDL_SYSTEM_CURSOR_ZOOM_OUT: પાછા XC_hand2;
        સ્થિતિ SDL_SYSTEM_CURSOR_ગણતરી: તોડો;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    પાછા 0;
}

સ્થિર SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = ખાલી;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    જો (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, ખાલી));
    }
#endif

    જો (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    જો (x11_cursor != None) {
        cursor = X11_CreateCursorAndData(x11_cursor);
    }

    પાછા cursor;
}

સ્થિર SDL_Cursor *X11_CreateDefaultCursor(શૂન્ય)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    પાછા X11_CreateSystemCursor(id);
}

સ્થિર શૂન્ય X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    જો (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

સ્થિર bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    જો (cursor) {
        x11_cursor = cursor->internal->cursor;
    } નહીંતર {
        x11_cursor = X11_CreateEmptyCursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_Window *window;

        x11_cursor_visible = !!cursor;

        માટે (window = video->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            જો (data) {
                જો (x11_cursor != None) {
                    X11_XDefineCursor(display, data->xwindow, x11_cursor);
                } નહીંતર {
                    X11_XUndefineCursor(display, data->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    પાછા true;
}

સ્થિર શૂન્ય X11_WarpMouseInternal(Window xwindow, દશાંશ x, દશાંશ y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    જો (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    જો (warp_hack) {
        X11_ShowCursor(ખાલી);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    પૂર્ણાંક deviceid = 0;
    જો (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        જો (Screen_ગણતરી(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    જો (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } નહીંતર
#endif
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (પૂર્ણાંક)x, (પૂર્ણાંક)y);
    }

    જો (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

સ્થિર bool X11_WarpMouse(SDL_Window *window, દશાંશ x, દશાંશ y)
{
    SDL_WindowData *data = window->internal;

    જો (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        પાછા true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    જો (data->pointer_barrier_active == false) {
        X11_WarpMouseInternal(data->xwindow, x, y);
    }
#નહીંતર
    X11_WarpMouseInternal(data->xwindow, x, y);
#endif
    પાછા true;
}

સ્થિર bool X11_WarpMouseGlobal(દશાંશ x, દશાંશ y)
{
    જો (X11_WarpMouseXTest(SDL_GetVideoDevice(), ખાલી, x, y)) {
        પાછા true;
    }

    X11_WarpMouseInternal(Default_મૂળ_Window(GetDisplay()), x, y);
    પાછા true;
}

સ્થિર bool X11_SetRelativeMouseMode(bool enabled)
{
    જો (!X11_Xinput2IsInitialized()) {
        પાછા SDL_Unsupported();
    }
    પાછા true;
}

સ્થિર bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    જો (window) {
        SDL_WindowData *data = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        જો (!data->xinput2_mouse_enabled || data->mouse_grabbed) {
            અચલ unsigned પૂર્ણાંક mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (data->mouse_grabbed ? data->xwindow : None);
            અચલ પૂર્ણાંક rc = X11_XGrabPointer(display, data->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            જો (rc != GrabSuccess) {
                પાછા SDL_SetError("X server refused mouse capture");
            }

            જો (data->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                data->videodata->global_mouse_changed = true;
            }
        }
    } નહીંતર જો (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } નહીંતર {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    પાછા true;
}

સ્થિર SDL_MouseButtonFlags X11_GetGlobalMouseState(દશાંશ *x, દશાંશ *y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    પૂર્ણાંક i;

    // !!! FIXME: should we XSync() here first?

    જો (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    જો (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(ખાલી);
        જો (displays) {
            માટે (i = 0; displays[i]; ++i) {
                SDL_DisplayData *data = SDL_GetDisplayDriverData(displays[i]);
                જો (data) {
                    Window મૂળ, child;
                    પૂર્ણાંક rootx, rooty, winx, winy;
                    unsigned પૂર્ણાંક mask;
                    જો (X11_XQueryPointer(display, મૂળ_Window(display, data->screen), &મૂળ, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes મૂળ_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(ખાલી, ખાલી) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, મૂળ, &મૂળ_attrs);
                        videodata->global_mouse_position.x = મૂળ_attrs.x + rootx;
                        videodata->global_mouse_position.y = મૂળ_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        તોડો;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (દશાંશ)videodata->global_mouse_position.x;
    *y = (દશાંશ)videodata->global_mouse_position.y;
    પાછા videodata->global_mouse_buttons;
}

શૂન્ય X11_InitMouse(SDL_VideoDevice *_this)
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
    જ્યારે (r <= SDL_HITTEST_RESIZE_ડાબું) {
        પસંદગી (r) {
        સ્થિતિ SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); તોડો;
        સ્થિતિ SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_ટોચ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_જમણું: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); તોડો;
        સ્થિતિ SDL_HITTEST_RESIZE_ડાબું: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); તોડો;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

શૂન્ય X11_QuitMouse(SDL_VideoDevice *_this)
{
    માટે (પૂર્ણાંક i = 0; i < SDL_arraysize(sys_cursors); i++) {
        જો (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = ખાલી;
        }
    }

    X11_DestroyEmptyCursor();
}

શૂન્ય X11_SetHitTestCursor(SDL_HitTestResult rc)
{
    જો (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } નહીંતર {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
