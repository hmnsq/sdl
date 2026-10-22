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

কাঠামো SDL_Cursor_তথ্য
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
স্থির Cursor x11_empty_cursor = None;
স্থির bool x11_cursor_visible = true;

স্থির SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_বাম + 1];

স্থির Display *GetDisplay(শূন্য)
{
    ফেরত SDL_GetVideoDevice()->internal->display;
}

স্থির Cursor X11_CreateEmptyCursor(শূন্য)
{
    যদি (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        অক্ষর তথ্য[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(তথ্য);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreate_Bitmap_From_তথ্য(display, Default_মূল_Window(display),
                                           তথ্য, 1, 1);
        যদি (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    ফেরত x11_empty_cursor;
}

স্থির শূন্য X11_DestroyEmptyCursor(শূন্য)
{
    যদি (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

স্থির SDL_Cursor *X11_Create_Cursor_And_তথ্য(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, আকার(*cursor));
    যদি (cursor) {
        SDL_Cursor_তথ্য *তথ্য = (SDL_Cursor_তথ্য *)SDL_calloc(1, আকার(*তথ্য));
        যদি (!তথ্য) {
            SDL_free(cursor);
            ফেরত ফাঁকা;
        }
        তথ্য->cursor = x11_cursor;
        cursor->internal = তথ্য;
    }
    ফেরত cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
স্থির XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    যদি (!image) {
        SDL_OutOfMemory();
        ফেরত ফাঁকা;
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

    ফেরত image;
}

স্থির Cursor X11_CreateXCursorCursor(SDL_Surface *surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    যদি (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    ফেরত cursor;
}

স্থির Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, পূর্ণসংখ্যা অঙ্ক_frames, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(অঙ্ক_frames);
    যদি (!images) {
        SDL_OutOfMemory();
        ফেরত None;
    }

    জন্য (পূর্ণসংখ্যা i = 0; i < অঙ্ক_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        যদি (!image) {
            যাও cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    ফেরত cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

স্থির Cursor X11_CreatePixmapCursor(SDL_Surface *surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *তথ্য_bits, *mask_bits;
    Pixmap তথ্য_pixmap, mask_pixmap;
    পূর্ণসংখ্যা x, y;
    unsigned পূর্ণসংখ্যা rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    size_t width_bytes = ((surface->w + 7) & ~((size_t)7)) / 8;

    তথ্য_bits = SDL_calloc(1, surface->h * width_bytes);
    যদি (!তথ্য_bits) {
        ফেরত None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    যদি (!mask_bits) {
        SDL_free(তথ্য_bits);
        ফেরত None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    জন্য (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        জন্য (x = 0; x < surface->w; ++x) {
            পূর্ণসংখ্যা alpha = (*ptr >> 24) & 0xff;
            পূর্ণসংখ্যা red = (*ptr >> 16) & 0xff;
            পূর্ণসংখ্যা green = (*ptr >> 8) & 0xff;
            পূর্ণসংখ্যা blue = (*ptr >> 0) & 0xff;
            যদি (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                যদি ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    তথ্য_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
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

    তথ্য_pixmap = X11_XCreate_Bitmap_From_তথ্য(display, Default_মূল_Window(display),
                                            (অক্ষর *)তথ্য_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreate_Bitmap_From_তথ্য(display, Default_মূল_Window(display),
                                            (অক্ষর *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, তথ্য_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, তথ্য_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(তথ্য_bits);
    SDL_free(mask_bits);

    ফেরত cursor;
}

স্থির SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
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
    ফেরত X11_Create_Cursor_And_তথ্য(x11_cursor);
}

স্থির SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, পূর্ণসংখ্যা অঙ্ক_frames, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
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

    ফেরত X11_Create_Cursor_And_তথ্য(x11_cursor);
}

স্থির unsigned পূর্ণসংখ্যা GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    নির্বাচন (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        ক্ষেত্র SDL_SYSTEM_CURSOR_DEFAULT: ফেরত XC_বাম_ptr;
        ক্ষেত্র SDL_SYSTEM_CURSOR_TEXT: ফেরত XC_xterm;
        ক্ষেত্র SDL_SYSTEM_CURSOR_WAIT: ফেরত XC_watch;
        ক্ষেত্র SDL_SYSTEM_CURSOR_CROSSHAIR: ফেরত XC_tcross;
        ক্ষেত্র SDL_SYSTEM_CURSOR_PROGRESS: ফেরত XC_watch;
        ক্ষেত্র SDL_SYSTEM_CURSOR_NWSE_RESIZE: ফেরত XC_শীর্ষ_বাম_corner;
        ক্ষেত্র SDL_SYSTEM_CURSOR_NESW_RESIZE: ফেরত XC_শীর্ষ_ডান_corner;
        ক্ষেত্র SDL_SYSTEM_CURSOR_EW_RESIZE: ফেরত XC_sb_h_double_arrow;
        ক্ষেত্র SDL_SYSTEM_CURSOR_NS_RESIZE: ফেরত XC_sb_v_double_arrow;
        ক্ষেত্র SDL_SYSTEM_CURSOR_MOVE: ফেরত XC_fleur;
        ক্ষেত্র SDL_SYSTEM_CURSOR_NOT_ALLOWED: ফেরত XC_pirate;
        ক্ষেত্র SDL_SYSTEM_CURSOR_POINTER: ফেরত XC_hand2;
        ক্ষেত্র SDL_SYSTEM_CURSOR_NW_RESIZE: ফেরত XC_শীর্ষ_বাম_corner;
        ক্ষেত্র SDL_SYSTEM_CURSOR_N_RESIZE: ফেরত XC_শীর্ষ_side;
        ক্ষেত্র SDL_SYSTEM_CURSOR_NE_RESIZE: ফেরত XC_শীর্ষ_ডান_corner;
        ক্ষেত্র SDL_SYSTEM_CURSOR_E_RESIZE: ফেরত XC_ডান_side;
        ক্ষেত্র SDL_SYSTEM_CURSOR_SE_RESIZE: ফেরত XC_bottom_ডান_corner;
        ক্ষেত্র SDL_SYSTEM_CURSOR_S_RESIZE: ফেরত XC_bottom_side;
        ক্ষেত্র SDL_SYSTEM_CURSOR_SW_RESIZE: ফেরত XC_bottom_বাম_corner;
        ক্ষেত্র SDL_SYSTEM_CURSOR_W_RESIZE: ফেরত XC_বাম_side;
        ক্ষেত্র SDL_SYSTEM_CURSOR_CONTEXT_MENU: ফেরত XC_hand2;
        ক্ষেত্র SDL_SYSTEM_CURSOR_HELP: ফেরত XC_question_arrow;
        ক্ষেত্র SDL_SYSTEM_CURSOR_CELL: ফেরত XC_cross;
        ক্ষেত্র SDL_SYSTEM_CURSOR_VERTICAL_TEXT: ফেরত XC_xterm;
        ক্ষেত্র SDL_SYSTEM_CURSOR_ALIAS: ফেরত XC_hand2;
        ক্ষেত্র SDL_SYSTEM_CURSOR_COPY: ফেরত XC_hand2;
        ক্ষেত্র SDL_SYSTEM_CURSOR_NO_DROP: ফেরত XC_pirate;
        ক্ষেত্র SDL_SYSTEM_CURSOR_GRAB: ফেরত XC_hand2;
        ক্ষেত্র SDL_SYSTEM_CURSOR_GRABBING: ফেরত XC_hand2;
        ক্ষেত্র SDL_SYSTEM_CURSOR_COL_RESIZE: ফেরত XC_sb_h_double_arrow;
        ক্ষেত্র SDL_SYSTEM_CURSOR_ROW_RESIZE: ফেরত XC_sb_v_double_arrow;
        ক্ষেত্র SDL_SYSTEM_CURSOR_ALL_SCROLL: ফেরত XC_fleur;
        ক্ষেত্র SDL_SYSTEM_CURSOR_ZOOM_IN: ফেরত XC_hand2;
        ক্ষেত্র SDL_SYSTEM_CURSOR_ZOOM_OUT: ফেরত XC_hand2;
        ক্ষেত্র SDL_SYSTEM_CURSOR_গুনতি: বিরতি;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    ফেরত 0;
}

স্থির SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = ফাঁকা;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    যদি (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, ফাঁকা));
    }
#endif

    যদি (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    যদি (x11_cursor != None) {
        cursor = X11_Create_Cursor_And_তথ্য(x11_cursor);
    }

    ফেরত cursor;
}

স্থির SDL_Cursor *X11_CreateDefaultCursor(শূন্য)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ফেরত X11_CreateSystemCursor(id);
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

        জন্য (window = video->windows; window; window = window->পরবর্তী) {
            SDL_Window_তথ্য *তথ্য = window->internal;
            যদি (তথ্য) {
                যদি (x11_cursor != None) {
                    X11_XDefineCursor(display, তথ্য->xwindow, x11_cursor);
                } অন্যথা {
                    X11_XUndefineCursor(display, তথ্য->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    ফেরত true;
}

স্থির শূন্য X11_WarpMouseInternal(Window xwindow, দশমিক x, দশমিক y)
{
    SDL_Video_তথ্য *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    যদি (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    যদি (warp_hack) {
        X11_ShowCursor(ফাঁকা);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    পূর্ণসংখ্যা deviceid = 0;
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
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (পূর্ণসংখ্যা)x, (পূর্ণসংখ্যা)y);
    }

    যদি (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

স্থির bool X11_WarpMouse(SDL_Window *window, দশমিক x, দশমিক y)
{
    SDL_Window_তথ্য *তথ্য = window->internal;

    যদি (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        ফেরত true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    যদি (তথ্য->pointer_barrier_active == false) {
        X11_WarpMouseInternal(তথ্য->xwindow, x, y);
    }
#অন্যথা
    X11_WarpMouseInternal(তথ্য->xwindow, x, y);
#endif
    ফেরত true;
}

স্থির bool X11_WarpMouseGlobal(দশমিক x, দশমিক y)
{
    যদি (X11_WarpMouseXTest(SDL_GetVideoDevice(), ফাঁকা, x, y)) {
        ফেরত true;
    }

    X11_WarpMouseInternal(Default_মূল_Window(GetDisplay()), x, y);
    ফেরত true;
}

স্থির bool X11_SetRelativeMouseMode(bool enabled)
{
    যদি (!X11_Xinput2IsInitialized()) {
        ফেরত SDL_Unsupported();
    }
    ফেরত true;
}

স্থির bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    যদি (window) {
        SDL_Window_তথ্য *তথ্য = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        যদি (!তথ্য->xinput2_mouse_enabled || তথ্য->mouse_grabbed) {
            ধ্রুবক unsigned পূর্ণসংখ্যা mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (তথ্য->mouse_grabbed ? তথ্য->xwindow : None);
            ধ্রুবক পূর্ণসংখ্যা rc = X11_XGrabPointer(display, তথ্য->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            যদি (rc != GrabSuccess) {
                ফেরত SDL_SetError("X server refused mouse capture");
            }

            যদি (তথ্য->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                তথ্য->videodata->global_mouse_changed = true;
            }
        }
    } অন্যথা যদি (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } অন্যথা {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    ফেরত true;
}

স্থির SDL_MouseButtonFlags X11_GetGlobalMouseState(দশমিক *x, দশমিক *y)
{
    SDL_Video_তথ্য *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    পূর্ণসংখ্যা i;

    // !!! FIXME: should we XSync() here first?

    যদি (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    যদি (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(ফাঁকা);
        যদি (displays) {
            জন্য (i = 0; displays[i]; ++i) {
                SDL_Display_তথ্য *তথ্য = SDL_Get_Display_Driver_তথ্য(displays[i]);
                যদি (তথ্য) {
                    Window মূল, child;
                    পূর্ণসংখ্যা rootx, rooty, winx, winy;
                    unsigned পূর্ণসংখ্যা mask;
                    যদি (X11_XQueryPointer(display, মূল_Window(display, তথ্য->screen), &মূল, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes মূল_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(ফাঁকা, ফাঁকা) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, মূল, &মূল_attrs);
                        videodata->global_mouse_position.x = মূল_attrs.x + rootx;
                        videodata->global_mouse_position.y = মূল_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        বিরতি;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (দশমিক)videodata->global_mouse_position.x;
    *y = (দশমিক)videodata->global_mouse_position.y;
    ফেরত videodata->global_mouse_buttons;
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

    SDL_Hit_Test_ফলাফল r = SDL_HITTEST_NORMAL;
    যখন (r <= SDL_HITTEST_RESIZE_বাম) {
        নির্বাচন (r) {
        ক্ষেত্র SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); বিরতি;
        ক্ষেত্র SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); বিরতি;
        ক্ষেত্র SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); বিরতি;
        ক্ষেত্র SDL_HITTEST_RESIZE_শীর্ষ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); বিরতি;
        ক্ষেত্র SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); বিরতি;
        ক্ষেত্র SDL_HITTEST_RESIZE_ডান: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); বিরতি;
        ক্ষেত্র SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); বিরতি;
        ক্ষেত্র SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); বিরতি;
        ক্ষেত্র SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); বিরতি;
        ক্ষেত্র SDL_HITTEST_RESIZE_বাম: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); বিরতি;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

শূন্য X11_QuitMouse(SDL_VideoDevice *_this)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < SDL_arraysize(sys_cursors); i++) {
        যদি (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = ফাঁকা;
        }
    }

    X11_DestroyEmptyCursor();
}

শূন্য X11_SetHitTestCursor(SDL_Hit_Test_ফলাফল rc)
{
    যদি (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } অন্যথা {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
