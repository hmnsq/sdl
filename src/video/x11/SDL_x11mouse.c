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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাব <X11/cursorfont.h>
#অন্তর্ভাব "SDL_x11video.h"
#অন্তর্ভাব "SDL_x11mouse.h"
#অন্তর্ভাব "SDL_x11xinput2.h"
#অন্তর্ভাব "SDL_x11xtest.h"
#অন্তর্ভাব "../SDL_video_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"

সংরচনা SDL_CursorData
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
স্থির Cursor x11_empty_cursor = None;
স্থির bool x11_cursor_visible = true;

স্থির SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_বাম + 1];

স্থির Display *GetDisplay(শূন্য)
{
    প্রত্যাগম SDL_GetVideoDevice()->internal->display;
}

স্থির Cursor X11_CreateEmptyCursor(শূন্য)
{
    যদি (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        বর্ণ data[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(data);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreateBitmapFromData(display, Default_মূল_Window(display),
                                           data, 1, 1);
        যদি (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    প্রত্যাগম x11_empty_cursor;
}

স্থির শূন্য X11_DestroyEmptyCursor(শূন্য)
{
    যদি (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

স্থির SDL_Cursor *X11_CreateCursorAndData(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, পরিমাণ(*cursor));
    যদি (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, পরিমাণ(*data));
        যদি (!data) {
            SDL_free(cursor);
            প্রত্যাগম রিক্ত;
        }
        data->cursor = x11_cursor;
        cursor->internal = data;
    }
    প্রত্যাগম cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
স্থির XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    যদি (!image) {
        SDL_OutOfMemory();
        প্রত্যাগম রিক্ত;
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

    প্রত্যাগম image;
}

স্থির Cursor X11_CreateXCursorCursor(SDL_Surface *surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    যদি (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    প্রত্যাগম cursor;
}

স্থির Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, পূর্ণাঙ্ক অঙ্ক_frames, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(অঙ্ক_frames);
    যদি (!images) {
        SDL_OutOfMemory();
        প্রত্যাগম None;
    }

    প্রতি (পূর্ণাঙ্ক i = 0; i < অঙ্ক_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        যদি (!image) {
            গচ্ছ cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    প্রত্যাগম cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

স্থির Cursor X11_CreatePixmapCursor(SDL_Surface *surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *data_bits, *mask_bits;
    Pixmap data_pixmap, mask_pixmap;
    পূর্ণাঙ্ক x, y;
    unsigned পূর্ণাঙ্ক rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    size_t width_bytes = ((surface->w + 7) & ~((size_t)7)) / 8;

    data_bits = SDL_calloc(1, surface->h * width_bytes);
    যদি (!data_bits) {
        প্রত্যাগম None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    যদি (!mask_bits) {
        SDL_free(data_bits);
        প্রত্যাগম None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    প্রতি (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        প্রতি (x = 0; x < surface->w; ++x) {
            পূর্ণাঙ্ক alpha = (*ptr >> 24) & 0xff;
            পূর্ণাঙ্ক red = (*ptr >> 16) & 0xff;
            পূর্ণাঙ্ক green = (*ptr >> 8) & 0xff;
            পূর্ণাঙ্ক blue = (*ptr >> 0) & 0xff;
            যদি (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                যদি ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    data_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
                } অন্যথা {
                    bgBits++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    যদি (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } অন্যথা {
        fg.red = fg.green = fg.blue = 0;
    }

    যদি (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } অন্যথা {
        bg.red = bg.green = bg.blue = 0;
    }

    data_pixmap = X11_XCreateBitmapFromData(display, Default_মূল_Window(display),
                                            (বর্ণ *)data_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreateBitmapFromData(display, Default_মূল_Window(display),
                                            (বর্ণ *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, data_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, data_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(data_bits);
    SDL_free(mask_bits);

    প্রত্যাগম cursor;
}

স্থির SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    যদি (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#endif
    যদি (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    প্রত্যাগম X11_CreateCursorAndData(x11_cursor);
}

স্থির SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, পূর্ণাঙ্ক অঙ্ক_frames, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    যদি (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, অঙ্ক_frames, hot_x, hot_y);
    }
#endif
    যদি (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    প্রত্যাগম X11_CreateCursorAndData(x11_cursor);
}

স্থির unsigned পূর্ণাঙ্ক GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    বিকল্প (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        পক্ষ SDL_SYSTEM_CURSOR_DEFAULT: প্রত্যাগম XC_বাম_ptr;
        পক্ষ SDL_SYSTEM_CURSOR_TEXT: প্রত্যাগম XC_xterm;
        পক্ষ SDL_SYSTEM_CURSOR_WAIT: প্রত্যাগম XC_watch;
        পক্ষ SDL_SYSTEM_CURSOR_CROSSHAIR: প্রত্যাগম XC_tcross;
        পক্ষ SDL_SYSTEM_CURSOR_PROGRESS: প্রত্যাগম XC_watch;
        পক্ষ SDL_SYSTEM_CURSOR_NWSE_RESIZE: প্রত্যাগম XC_শীর্ষ_বাম_corner;
        পক্ষ SDL_SYSTEM_CURSOR_NESW_RESIZE: প্রত্যাগম XC_শীর্ষ_ডান_corner;
        পক্ষ SDL_SYSTEM_CURSOR_EW_RESIZE: প্রত্যাগম XC_sb_h_double_arrow;
        পক্ষ SDL_SYSTEM_CURSOR_NS_RESIZE: প্রত্যাগম XC_sb_v_double_arrow;
        পক্ষ SDL_SYSTEM_CURSOR_MOVE: প্রত্যাগম XC_fleur;
        পক্ষ SDL_SYSTEM_CURSOR_NOT_ALLOWED: প্রত্যাগম XC_pirate;
        পক্ষ SDL_SYSTEM_CURSOR_POINTER: প্রত্যাগম XC_hand2;
        পক্ষ SDL_SYSTEM_CURSOR_NW_RESIZE: প্রত্যাগম XC_শীর্ষ_বাম_corner;
        পক্ষ SDL_SYSTEM_CURSOR_N_RESIZE: প্রত্যাগম XC_শীর্ষ_side;
        পক্ষ SDL_SYSTEM_CURSOR_NE_RESIZE: প্রত্যাগম XC_শীর্ষ_ডান_corner;
        পক্ষ SDL_SYSTEM_CURSOR_E_RESIZE: প্রত্যাগম XC_ডান_side;
        পক্ষ SDL_SYSTEM_CURSOR_SE_RESIZE: প্রত্যাগম XC_bottom_ডান_corner;
        পক্ষ SDL_SYSTEM_CURSOR_S_RESIZE: প্রত্যাগম XC_bottom_side;
        পক্ষ SDL_SYSTEM_CURSOR_SW_RESIZE: প্রত্যাগম XC_bottom_বাম_corner;
        পক্ষ SDL_SYSTEM_CURSOR_W_RESIZE: প্রত্যাগম XC_বাম_side;
        পক্ষ SDL_SYSTEM_CURSOR_CONTEXT_MENU: প্রত্যাগম XC_hand2;
        পক্ষ SDL_SYSTEM_CURSOR_HELP: প্রত্যাগম XC_question_arrow;
        পক্ষ SDL_SYSTEM_CURSOR_CELL: প্রত্যাগম XC_cross;
        পক্ষ SDL_SYSTEM_CURSOR_VERTICAL_TEXT: প্রত্যাগম XC_xterm;
        পক্ষ SDL_SYSTEM_CURSOR_ALIAS: প্রত্যাগম XC_hand2;
        পক্ষ SDL_SYSTEM_CURSOR_COPY: প্রত্যাগম XC_hand2;
        পক্ষ SDL_SYSTEM_CURSOR_NO_DROP: প্রত্যাগম XC_pirate;
        পক্ষ SDL_SYSTEM_CURSOR_GRAB: প্রত্যাগম XC_hand2;
        পক্ষ SDL_SYSTEM_CURSOR_GRABBING: প্রত্যাগম XC_hand2;
        পক্ষ SDL_SYSTEM_CURSOR_COL_RESIZE: প্রত্যাগম XC_sb_h_double_arrow;
        পক্ষ SDL_SYSTEM_CURSOR_ROW_RESIZE: প্রত্যাগম XC_sb_v_double_arrow;
        পক্ষ SDL_SYSTEM_CURSOR_ALL_SCROLL: প্রত্যাগম XC_fleur;
        পক্ষ SDL_SYSTEM_CURSOR_ZOOM_IN: প্রত্যাগম XC_hand2;
        পক্ষ SDL_SYSTEM_CURSOR_ZOOM_OUT: প্রত্যাগম XC_hand2;
        পক্ষ SDL_SYSTEM_CURSOR_গুনতি: ভঙ্গ;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    প্রত্যাগম 0;
}

স্থির SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = রিক্ত;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    যদি (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, রিক্ত));
    }
#endif

    যদি (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    যদি (x11_cursor != None) {
        cursor = X11_CreateCursorAndData(x11_cursor);
    }

    প্রত্যাগম cursor;
}

স্থির SDL_Cursor *X11_CreateDefaultCursor(শূন্য)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    প্রত্যাগম X11_CreateSystemCursor(id);
}

স্থির শূন্য X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    যদি (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

স্থির bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    যদি (cursor) {
        x11_cursor = cursor->internal->cursor;
    } অন্যথা {
        x11_cursor = X11_CreateEmptyCursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_Window *window;

        x11_cursor_visible = !!cursor;

        প্রতি (window = video->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            যদি (data) {
                যদি (x11_cursor != None) {
                    X11_XDefineCursor(display, data->xwindow, x11_cursor);
                } অন্যথা {
                    X11_XUndefineCursor(display, data->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    প্রত্যাগম true;
}

স্থির শূন্য X11_WarpMouseInternal(Window xwindow, ভিন্ন x, ভিন্ন y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    যদি (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    যদি (warp_hack) {
        X11_ShowCursor(রিক্ত);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    পূর্ণাঙ্ক deviceid = 0;
    যদি (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        যদি (Screen_গুনতি(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    যদি (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } অন্যথা
#endif
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (পূর্ণাঙ্ক)x, (পূর্ণাঙ্ক)y);
    }

    যদি (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

স্থির bool X11_WarpMouse(SDL_Window *window, ভিন্ন x, ভিন্ন y)
{
    SDL_WindowData *data = window->internal;

    যদি (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        প্রত্যাগম true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    যদি (data->pointer_barrier_active == false) {
        X11_WarpMouseInternal(data->xwindow, x, y);
    }
#অন্যথা
    X11_WarpMouseInternal(data->xwindow, x, y);
#endif
    প্রত্যাগম true;
}

স্থির bool X11_WarpMouseGlobal(ভিন্ন x, ভিন্ন y)
{
    যদি (X11_WarpMouseXTest(SDL_GetVideoDevice(), রিক্ত, x, y)) {
        প্রত্যাগম true;
    }

    X11_WarpMouseInternal(Default_মূল_Window(GetDisplay()), x, y);
    প্রত্যাগম true;
}

স্থির bool X11_SetRelativeMouseMode(bool enabled)
{
    যদি (!X11_Xinput2IsInitialized()) {
        প্রত্যাগম SDL_Unsupported();
    }
    প্রত্যাগম true;
}

স্থির bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    যদি (window) {
        SDL_WindowData *data = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        যদি (!data->xinput2_mouse_enabled || data->mouse_grabbed) {
            ধ্রুব unsigned পূর্ণাঙ্ক mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (data->mouse_grabbed ? data->xwindow : None);
            ধ্রুব পূর্ণাঙ্ক rc = X11_XGrabPointer(display, data->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            যদি (rc != GrabSuccess) {
                প্রত্যাগম SDL_SetError("X server refused mouse capture");
            }

            যদি (data->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                data->videodata->global_mouse_changed = true;
            }
        }
    } অন্যথা যদি (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } অন্যথা {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    প্রত্যাগম true;
}

স্থির SDL_MouseButtonFlags X11_GetGlobalMouseState(ভিন্ন *x, ভিন্ন *y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    পূর্ণাঙ্ক i;

    // !!! FIXME: should we XSync() here first?

    যদি (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    যদি (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(রিক্ত);
        যদি (displays) {
            প্রতি (i = 0; displays[i]; ++i) {
                SDL_DisplayData *data = SDL_GetDisplayDriverData(displays[i]);
                যদি (data) {
                    Window মূল, child;
                    পূর্ণাঙ্ক rootx, rooty, winx, winy;
                    unsigned পূর্ণাঙ্ক mask;
                    যদি (X11_XQueryPointer(display, মূল_Window(display, data->screen), &মূল, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes মূল_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(রিক্ত, রিক্ত) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, মূল, &মূল_attrs);
                        videodata->global_mouse_position.x = মূল_attrs.x + rootx;
                        videodata->global_mouse_position.y = মূল_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        ভঙ্গ;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (ভিন্ন)videodata->global_mouse_position.x;
    *y = (ভিন্ন)videodata->global_mouse_position.y;
    প্রত্যাগম videodata->global_mouse_buttons;
}

শূন্য X11_InitMouse(SDL_VideoDevice *_this)
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
    যাবত্ (r <= SDL_HITTEST_RESIZE_বাম) {
        বিকল্প (r) {
        পক্ষ SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ভঙ্গ;
        পক্ষ SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_শীর্ষ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_ডান: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); ভঙ্গ;
        পক্ষ SDL_HITTEST_RESIZE_বাম: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); ভঙ্গ;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

শূন্য X11_QuitMouse(SDL_VideoDevice *_this)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < SDL_arraysize(sys_cursors); i++) {
        যদি (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = রিক্ত;
        }
    }

    X11_DestroyEmptyCursor();
}

শূন্য X11_SetHitTestCursor(SDL_HitTestResult rc)
{
    যদি (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } অন্যথা {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
