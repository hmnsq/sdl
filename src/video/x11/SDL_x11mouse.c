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
#شامل "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#شامل <X11/cursorfont.h>
#شامل "SDL_x11video.h"
#شامل "SDL_x11mouse.h"
#شامل "SDL_x11xinput2.h"
#شامل "SDL_x11xtest.h"
#شامل "../SDL_video_c.h"
#شامل "../../events/SDL_mouse_c.h"

ساختار SDL_CursorData
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
ایستا Cursor x11_empty_cursor = None;
ایستا bool x11_cursor_visible = true;

ایستا SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_چپ + 1];

ایستا Display *GetDisplay(تهی)
{
    بازگشت SDL_GetVideoDevice()->internal->display;
}

ایستا Cursor X11_CreateEmptyCursor(تهی)
{
    اگر (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        نویسه data[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(data);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreateBitmapFromData(display, Default_ریشه_Window(display),
                                           data, 1, 1);
        اگر (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    بازگشت x11_empty_cursor;
}

ایستا تهی X11_DestroyEmptyCursor(تهی)
{
    اگر (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

ایستا SDL_Cursor *X11_CreateCursorAndData(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, اندازه(*cursor));
    اگر (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, اندازه(*data));
        اگر (!data) {
            SDL_free(cursor);
            بازگشت پوچ;
        }
        data->cursor = x11_cursor;
        cursor->internal = data;
    }
    بازگشت cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
ایستا XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, صحیح hot_x, صحیح hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    اگر (!image) {
        SDL_OutOfMemory();
        بازگشت پوچ;
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

    بازگشت image;
}

ایستا Cursor X11_CreateXCursorCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    اگر (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    بازگشت cursor;
}

ایستا Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, صحیح رقم_frames, صحیح hot_x, صحیح hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(رقم_frames);
    اگر (!images) {
        SDL_OutOfMemory();
        بازگشت None;
    }

    برای (صحیح i = 0; i < رقم_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        اگر (!image) {
            برو cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    بازگشت cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

ایستا Cursor X11_CreatePixmapCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *data_bits, *mask_bits;
    Pixmap data_pixmap, mask_pixmap;
    صحیح x, y;
    unsigned صحیح rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    size_t width_bytes = ((surface->w + 7) & ~((size_t)7)) / 8;

    data_bits = SDL_calloc(1, surface->h * width_bytes);
    اگر (!data_bits) {
        بازگشت None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    اگر (!mask_bits) {
        SDL_free(data_bits);
        بازگشت None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    برای (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        برای (x = 0; x < surface->w; ++x) {
            صحیح alpha = (*ptr >> 24) & 0xff;
            صحیح red = (*ptr >> 16) & 0xff;
            صحیح green = (*ptr >> 8) & 0xff;
            صحیح blue = (*ptr >> 0) & 0xff;
            اگر (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                اگر ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    data_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
                } وگرنه {
                    bgBits++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    اگر (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } وگرنه {
        fg.red = fg.green = fg.blue = 0;
    }

    اگر (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } وگرنه {
        bg.red = bg.green = bg.blue = 0;
    }

    data_pixmap = X11_XCreateBitmapFromData(display, Default_ریشه_Window(display),
                                            (نویسه *)data_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreateBitmapFromData(display, Default_ریشه_Window(display),
                                            (نویسه *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, data_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, data_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(data_bits);
    SDL_free(mask_bits);

    بازگشت cursor;
}

ایستا SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    اگر (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#endif
    اگر (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    بازگشت X11_CreateCursorAndData(x11_cursor);
}

ایستا SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, صحیح رقم_frames, صحیح hot_x, صحیح hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    اگر (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, رقم_frames, hot_x, hot_y);
    }
#endif
    اگر (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    بازگشت X11_CreateCursorAndData(x11_cursor);
}

ایستا unsigned صحیح GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    انتخاب (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        حالت SDL_SYSTEM_CURSOR_DEFAULT: بازگشت XC_چپ_ptr;
        حالت SDL_SYSTEM_CURSOR_TEXT: بازگشت XC_xterm;
        حالت SDL_SYSTEM_CURSOR_WAIT: بازگشت XC_watch;
        حالت SDL_SYSTEM_CURSOR_CROSSHAIR: بازگشت XC_tcross;
        حالت SDL_SYSTEM_CURSOR_PROGRESS: بازگشت XC_watch;
        حالت SDL_SYSTEM_CURSOR_NWSE_RESIZE: بازگشت XC_بالاترین_چپ_corner;
        حالت SDL_SYSTEM_CURSOR_NESW_RESIZE: بازگشت XC_بالاترین_راست_corner;
        حالت SDL_SYSTEM_CURSOR_EW_RESIZE: بازگشت XC_sb_h_double_arrow;
        حالت SDL_SYSTEM_CURSOR_NS_RESIZE: بازگشت XC_sb_v_double_arrow;
        حالت SDL_SYSTEM_CURSOR_MOVE: بازگشت XC_fleur;
        حالت SDL_SYSTEM_CURSOR_NOT_ALLOWED: بازگشت XC_pirate;
        حالت SDL_SYSTEM_CURSOR_POINTER: بازگشت XC_hand2;
        حالت SDL_SYSTEM_CURSOR_NW_RESIZE: بازگشت XC_بالاترین_چپ_corner;
        حالت SDL_SYSTEM_CURSOR_N_RESIZE: بازگشت XC_بالاترین_side;
        حالت SDL_SYSTEM_CURSOR_NE_RESIZE: بازگشت XC_بالاترین_راست_corner;
        حالت SDL_SYSTEM_CURSOR_E_RESIZE: بازگشت XC_راست_side;
        حالت SDL_SYSTEM_CURSOR_SE_RESIZE: بازگشت XC_bottom_راست_corner;
        حالت SDL_SYSTEM_CURSOR_S_RESIZE: بازگشت XC_bottom_side;
        حالت SDL_SYSTEM_CURSOR_SW_RESIZE: بازگشت XC_bottom_چپ_corner;
        حالت SDL_SYSTEM_CURSOR_W_RESIZE: بازگشت XC_چپ_side;
        حالت SDL_SYSTEM_CURSOR_CONTEXT_MENU: بازگشت XC_hand2;
        حالت SDL_SYSTEM_CURSOR_HELP: بازگشت XC_question_arrow;
        حالت SDL_SYSTEM_CURSOR_CELL: بازگشت XC_cross;
        حالت SDL_SYSTEM_CURSOR_VERTICAL_TEXT: بازگشت XC_xterm;
        حالت SDL_SYSTEM_CURSOR_ALIAS: بازگشت XC_hand2;
        حالت SDL_SYSTEM_CURSOR_COPY: بازگشت XC_hand2;
        حالت SDL_SYSTEM_CURSOR_NO_DROP: بازگشت XC_pirate;
        حالت SDL_SYSTEM_CURSOR_GRAB: بازگشت XC_hand2;
        حالت SDL_SYSTEM_CURSOR_GRABBING: بازگشت XC_hand2;
        حالت SDL_SYSTEM_CURSOR_COL_RESIZE: بازگشت XC_sb_h_double_arrow;
        حالت SDL_SYSTEM_CURSOR_ROW_RESIZE: بازگشت XC_sb_v_double_arrow;
        حالت SDL_SYSTEM_CURSOR_ALL_SCROLL: بازگشت XC_fleur;
        حالت SDL_SYSTEM_CURSOR_ZOOM_IN: بازگشت XC_hand2;
        حالت SDL_SYSTEM_CURSOR_ZOOM_OUT: بازگشت XC_hand2;
        حالت SDL_SYSTEM_CURSOR_شمار: بشکن;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    بازگشت 0;
}

ایستا SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = پوچ;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    اگر (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, پوچ));
    }
#endif

    اگر (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    اگر (x11_cursor != None) {
        cursor = X11_CreateCursorAndData(x11_cursor);
    }

    بازگشت cursor;
}

ایستا SDL_Cursor *X11_CreateDefaultCursor(تهی)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    بازگشت X11_CreateSystemCursor(id);
}

ایستا تهی X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    اگر (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ایستا bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    اگر (cursor) {
        x11_cursor = cursor->internal->cursor;
    } وگرنه {
        x11_cursor = X11_CreateEmptyCursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_Window *window;

        x11_cursor_visible = !!cursor;

        برای (window = video->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            اگر (data) {
                اگر (x11_cursor != None) {
                    X11_XDefineCursor(display, data->xwindow, x11_cursor);
                } وگرنه {
                    X11_XUndefineCursor(display, data->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    بازگشت true;
}

ایستا تهی X11_WarpMouseInternal(Window xwindow, اعشاری x, اعشاری y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    اگر (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    اگر (warp_hack) {
        X11_ShowCursor(پوچ);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    صحیح deviceid = 0;
    اگر (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        اگر (Screen_شمار(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    اگر (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } وگرنه
#endif
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (صحیح)x, (صحیح)y);
    }

    اگر (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

ایستا bool X11_WarpMouse(SDL_Window *window, اعشاری x, اعشاری y)
{
    SDL_WindowData *data = window->internal;

    اگر (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        بازگشت true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    اگر (data->pointer_barrier_active == false) {
        X11_WarpMouseInternal(data->xwindow, x, y);
    }
#وگرنه
    X11_WarpMouseInternal(data->xwindow, x, y);
#endif
    بازگشت true;
}

ایستا bool X11_WarpMouseGlobal(اعشاری x, اعشاری y)
{
    اگر (X11_WarpMouseXTest(SDL_GetVideoDevice(), پوچ, x, y)) {
        بازگشت true;
    }

    X11_WarpMouseInternal(Default_ریشه_Window(GetDisplay()), x, y);
    بازگشت true;
}

ایستا bool X11_SetRelativeMouseMode(bool enabled)
{
    اگر (!X11_Xinput2IsInitialized()) {
        بازگشت SDL_Unsupported();
    }
    بازگشت true;
}

ایستا bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    اگر (window) {
        SDL_WindowData *data = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        اگر (!data->xinput2_mouse_enabled || data->mouse_grabbed) {
            ثابت unsigned صحیح mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (data->mouse_grabbed ? data->xwindow : None);
            ثابت صحیح rc = X11_XGrabPointer(display, data->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            اگر (rc != GrabSuccess) {
                بازگشت SDL_SetError("X server refused mouse capture");
            }

            اگر (data->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                data->videodata->global_mouse_changed = true;
            }
        }
    } وگرنه اگر (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } وگرنه {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    بازگشت true;
}

ایستا SDL_MouseButtonFlags X11_GetGlobalMouseState(اعشاری *x, اعشاری *y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    صحیح i;

    // !!! FIXME: should we XSync() here first?

    اگر (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    اگر (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(پوچ);
        اگر (displays) {
            برای (i = 0; displays[i]; ++i) {
                SDL_DisplayData *data = SDL_GetDisplayDriverData(displays[i]);
                اگر (data) {
                    Window ریشه, child;
                    صحیح rootx, rooty, winx, winy;
                    unsigned صحیح mask;
                    اگر (X11_XQueryPointer(display, ریشه_Window(display, data->screen), &ریشه, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes ریشه_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(پوچ, پوچ) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, ریشه, &ریشه_attrs);
                        videodata->global_mouse_position.x = ریشه_attrs.x + rootx;
                        videodata->global_mouse_position.y = ریشه_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        بشکن;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (اعشاری)videodata->global_mouse_position.x;
    *y = (اعشاری)videodata->global_mouse_position.y;
    بازگشت videodata->global_mouse_buttons;
}

تهی X11_InitMouse(SDL_VideoDevice *_this)
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
    وقتی (r <= SDL_HITTEST_RESIZE_چپ) {
        انتخاب (r) {
        حالت SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); بشکن;
        حالت SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); بشکن;
        حالت SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); بشکن;
        حالت SDL_HITTEST_RESIZE_بالاترین: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); بشکن;
        حالت SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); بشکن;
        حالت SDL_HITTEST_RESIZE_راست: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); بشکن;
        حالت SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); بشکن;
        حالت SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); بشکن;
        حالت SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); بشکن;
        حالت SDL_HITTEST_RESIZE_چپ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); بشکن;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

تهی X11_QuitMouse(SDL_VideoDevice *_this)
{
    برای (صحیح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        اگر (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = پوچ;
        }
    }

    X11_DestroyEmptyCursor();
}

تهی X11_SetHitTestCursor(SDL_HitTestResult rc)
{
    اگر (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } وگرنه {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
