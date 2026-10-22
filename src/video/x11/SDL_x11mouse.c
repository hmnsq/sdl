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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ضمن <X11/cursorfont.h>
#ضمن "SDL_x11video.h"
#ضمن "SDL_x11mouse.h"
#ضمن "SDL_x11xinput2.h"
#ضمن "SDL_x11xtest.h"
#ضمن "../SDL_video_c.h"
#ضمن "../../events/SDL_mouse_c.h"

بنية SDL_CursorData
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
ساكن Cursor x11_empty_cursor = None;
ساكن bool x11_cursor_visible = true;

ساكن SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_LEFT + 1];

ساكن Display *GetDisplay(فراغ)
{
    ܦܢܐ SDL_GetVideoDevice()->internal->display;
}

ساكن Cursor X11_CreateEmptyCursor(فراغ)
{
    ܐܢ (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        حرف data[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(data);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreateBitmapFromData(display, DefaultRootWindow(display),
                                           data, 1, 1);
        ܐܢ (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    ܦܢܐ x11_empty_cursor;
}

ساكن فراغ X11_DestroyEmptyCursor(فراغ)
{
    ܐܢ (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

ساكن SDL_Cursor *X11_CreateCursorAndData(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    ܐܢ (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, حجم(*data));
        ܐܢ (!data) {
            SDL_free(cursor);
            ܦܢܐ عدم;
        }
        data->cursor = x11_cursor;
        cursor->internal = data;
    }
    ܦܢܐ cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
ساكن XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, صحيح hot_x, صحيح hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    ܐܢ (!image) {
        SDL_OutOfMemory();
        ܦܢܐ عدم;
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

    ܦܢܐ image;
}

ساكن Cursor X11_CreateXCursorCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    ܐܢ (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    ܦܢܐ cursor;
}

ساكن Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, صحيح num_frames, صحيح hot_x, صحيح hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(num_frames);
    ܐܢ (!images) {
        SDL_OutOfMemory();
        ܦܢܐ None;
    }

    لكل (صحيح i = 0; i < num_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        ܐܢ (!image) {
            اذهب cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    ܦܢܐ cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

ساكن Cursor X11_CreatePixmapCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *data_bits, *mask_bits;
    Pixmap data_pixmap, mask_pixmap;
    صحيح x, y;
    unsigned صحيح rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    size_t width_bytes = ((surface->w + 7) & ~((size_t)7)) / 8;

    data_bits = SDL_calloc(1, surface->h * width_bytes);
    ܐܢ (!data_bits) {
        ܦܢܐ None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    ܐܢ (!mask_bits) {
        SDL_free(data_bits);
        ܦܢܐ None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    لكل (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        لكل (x = 0; x < surface->w; ++x) {
            صحيح alpha = (*ptr >> 24) & 0xff;
            صحيح red = (*ptr >> 16) & 0xff;
            صحيح green = (*ptr >> 8) & 0xff;
            صحيح blue = (*ptr >> 0) & 0xff;
            ܐܢ (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                ܐܢ ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    data_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
                } ܐܚܪܢܐ {
                    bgBits++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    ܐܢ (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } ܐܚܪܢܐ {
        fg.red = fg.green = fg.blue = 0;
    }

    ܐܢ (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } ܐܚܪܢܐ {
        bg.red = bg.green = bg.blue = 0;
    }

    data_pixmap = X11_XCreateBitmapFromData(display, DefaultRootWindow(display),
                                            (حرف *)data_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreateBitmapFromData(display, DefaultRootWindow(display),
                                            (حرف *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, data_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, data_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(data_bits);
    SDL_free(mask_bits);

    ܦܢܐ cursor;
}

ساكن SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    ܐܢ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#endif
    ܐܢ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    ܦܢܐ X11_CreateCursorAndData(x11_cursor);
}

ساكن SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, صحيح num_frames, صحيح hot_x, صحيح hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    ܐܢ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, num_frames, hot_x, hot_y);
    }
#endif
    ܐܢ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    ܦܢܐ X11_CreateCursorAndData(x11_cursor);
}

ساكن unsigned صحيح GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    بدل (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        حالة SDL_SYSTEM_CURSOR_DEFAULT: ܦܢܐ XC_left_ptr;
        حالة SDL_SYSTEM_CURSOR_TEXT: ܦܢܐ XC_xterm;
        حالة SDL_SYSTEM_CURSOR_WAIT: ܦܢܐ XC_watch;
        حالة SDL_SYSTEM_CURSOR_CROSSHAIR: ܦܢܐ XC_tcross;
        حالة SDL_SYSTEM_CURSOR_PROGRESS: ܦܢܐ XC_watch;
        حالة SDL_SYSTEM_CURSOR_NWSE_RESIZE: ܦܢܐ XC_top_left_corner;
        حالة SDL_SYSTEM_CURSOR_NESW_RESIZE: ܦܢܐ XC_top_right_corner;
        حالة SDL_SYSTEM_CURSOR_EW_RESIZE: ܦܢܐ XC_sb_h_double_arrow;
        حالة SDL_SYSTEM_CURSOR_NS_RESIZE: ܦܢܐ XC_sb_v_double_arrow;
        حالة SDL_SYSTEM_CURSOR_MOVE: ܦܢܐ XC_fleur;
        حالة SDL_SYSTEM_CURSOR_NOT_ALLOWED: ܦܢܐ XC_pirate;
        حالة SDL_SYSTEM_CURSOR_POINTER: ܦܢܐ XC_hand2;
        حالة SDL_SYSTEM_CURSOR_NW_RESIZE: ܦܢܐ XC_top_left_corner;
        حالة SDL_SYSTEM_CURSOR_N_RESIZE: ܦܢܐ XC_top_side;
        حالة SDL_SYSTEM_CURSOR_NE_RESIZE: ܦܢܐ XC_top_right_corner;
        حالة SDL_SYSTEM_CURSOR_E_RESIZE: ܦܢܐ XC_right_side;
        حالة SDL_SYSTEM_CURSOR_SE_RESIZE: ܦܢܐ XC_bottom_right_corner;
        حالة SDL_SYSTEM_CURSOR_S_RESIZE: ܦܢܐ XC_bottom_side;
        حالة SDL_SYSTEM_CURSOR_SW_RESIZE: ܦܢܐ XC_bottom_left_corner;
        حالة SDL_SYSTEM_CURSOR_W_RESIZE: ܦܢܐ XC_left_side;
        حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU: ܦܢܐ XC_hand2;
        حالة SDL_SYSTEM_CURSOR_HELP: ܦܢܐ XC_question_arrow;
        حالة SDL_SYSTEM_CURSOR_CELL: ܦܢܐ XC_cross;
        حالة SDL_SYSTEM_CURSOR_VERTICAL_TEXT: ܦܢܐ XC_xterm;
        حالة SDL_SYSTEM_CURSOR_ALIAS: ܦܢܐ XC_hand2;
        حالة SDL_SYSTEM_CURSOR_COPY: ܦܢܐ XC_hand2;
        حالة SDL_SYSTEM_CURSOR_NO_DROP: ܦܢܐ XC_pirate;
        حالة SDL_SYSTEM_CURSOR_GRAB: ܦܢܐ XC_hand2;
        حالة SDL_SYSTEM_CURSOR_GRABBING: ܦܢܐ XC_hand2;
        حالة SDL_SYSTEM_CURSOR_COL_RESIZE: ܦܢܐ XC_sb_h_double_arrow;
        حالة SDL_SYSTEM_CURSOR_ROW_RESIZE: ܦܢܐ XC_sb_v_double_arrow;
        حالة SDL_SYSTEM_CURSOR_ALL_SCROLL: ܦܢܐ XC_fleur;
        حالة SDL_SYSTEM_CURSOR_ZOOM_IN: ܦܢܐ XC_hand2;
        حالة SDL_SYSTEM_CURSOR_ZOOM_OUT: ܦܢܐ XC_hand2;
        حالة SDL_SYSTEM_CURSOR_COUNT: اكسر;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    ܦܢܐ 0;
}

ساكن SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = عدم;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    ܐܢ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, عدم));
    }
#endif

    ܐܢ (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    ܐܢ (x11_cursor != None) {
        cursor = X11_CreateCursorAndData(x11_cursor);
    }

    ܦܢܐ cursor;
}

ساكن SDL_Cursor *X11_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ܦܢܐ X11_CreateSystemCursor(id);
}

ساكن فراغ X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    ܐܢ (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ساكن bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    ܐܢ (cursor) {
        x11_cursor = cursor->internal->cursor;
    } ܐܚܪܢܐ {
        x11_cursor = X11_CreateEmptyCursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_Window *window;

        x11_cursor_visible = !!cursor;

        لكل (window = video->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            ܐܢ (data) {
                ܐܢ (x11_cursor != None) {
                    X11_XDefineCursor(display, data->xwindow, x11_cursor);
                } ܐܚܪܢܐ {
                    X11_XUndefineCursor(display, data->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    ܦܢܐ true;
}

ساكن فراغ X11_WarpMouseInternal(Window xwindow, عائم x, عائم y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    ܐܢ (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    ܐܢ (warp_hack) {
        X11_ShowCursor(عدم);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    صحيح deviceid = 0;
    ܐܢ (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        ܐܢ (ScreenCount(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    ܐܢ (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } ܐܚܪܢܐ
#endif
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (صحيح)x, (صحيح)y);
    }

    ܐܢ (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

ساكن bool X11_WarpMouse(SDL_Window *window, عائم x, عائم y)
{
    SDL_WindowData *data = window->internal;

    ܐܢ (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        ܦܢܐ true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    ܐܢ (data->pointer_barrier_active == false) {
        X11_WarpMouseInternal(data->xwindow, x, y);
    }
#ܐܚܪܢܐ
    X11_WarpMouseInternal(data->xwindow, x, y);
#endif
    ܦܢܐ true;
}

ساكن bool X11_WarpMouseGlobal(عائم x, عائم y)
{
    ܐܢ (X11_WarpMouseXTest(SDL_GetVideoDevice(), عدم, x, y)) {
        ܦܢܐ true;
    }

    X11_WarpMouseInternal(DefaultRootWindow(GetDisplay()), x, y);
    ܦܢܐ true;
}

ساكن bool X11_SetRelativeMouseMode(bool enabled)
{
    ܐܢ (!X11_Xinput2IsInitialized()) {
        ܦܢܐ SDL_Unsupported();
    }
    ܦܢܐ true;
}

ساكن bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    ܐܢ (window) {
        SDL_WindowData *data = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        ܐܢ (!data->xinput2_mouse_enabled || data->mouse_grabbed) {
            ثابت unsigned صحيح mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (data->mouse_grabbed ? data->xwindow : None);
            ثابت صحيح rc = X11_XGrabPointer(display, data->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            ܐܢ (rc != GrabSuccess) {
                ܦܢܐ SDL_SetError("X server refused mouse capture");
            }

            ܐܢ (data->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                data->videodata->global_mouse_changed = true;
            }
        }
    } ܐܚܪܢܐ ܐܢ (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } ܐܚܪܢܐ {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    ܦܢܐ true;
}

ساكن SDL_MouseButtonFlags X11_GetGlobalMouseState(عائم *x, عائم *y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    صحيح i;

    // !!! FIXME: should we XSync() here first?

    ܐܢ (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    ܐܢ (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(عدم);
        ܐܢ (displays) {
            لكل (i = 0; displays[i]; ++i) {
                SDL_DisplayData *data = SDL_GetDisplayDriverData(displays[i]);
                ܐܢ (data) {
                    Window root, child;
                    صحيح rootx, rooty, winx, winy;
                    unsigned صحيح mask;
                    ܐܢ (X11_XQueryPointer(display, RootWindow(display, data->screen), &root, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes root_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(عدم, عدم) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, root, &root_attrs);
                        videodata->global_mouse_position.x = root_attrs.x + rootx;
                        videodata->global_mouse_position.y = root_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        اكسر;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (عائم)videodata->global_mouse_position.x;
    *y = (عائم)videodata->global_mouse_position.y;
    ܦܢܐ videodata->global_mouse_buttons;
}

فراغ X11_InitMouse(SDL_VideoDevice *_this)
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
    ܟܡܐ (r <= SDL_HITTEST_RESIZE_LEFT) {
        بدل (r) {
        حالة SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); اكسر;
        حالة SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); اكسر;
        حالة SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_TOP: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_RIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_LEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); اكسر;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

فراغ X11_QuitMouse(SDL_VideoDevice *_this)
{
    لكل (صحيح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        ܐܢ (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = عدم;
        }
    }

    X11_DestroyEmptyCursor();
}

فراغ X11_SetHitTestCursor(SDL_HitTestResult rc)
{
    ܐܢ (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } ܐܚܪܢܐ {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
