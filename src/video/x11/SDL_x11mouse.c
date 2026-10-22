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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#அந்தர்பாவ <X11/cursorfont.h>
#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "SDL_x11mouse.h"
#அந்தர்பாவ "SDL_x11xinput2.h"
#அந்தர்பாவ "SDL_x11xtest.h"
#அந்தர்பாவ "../SDL_video_c.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"

கட்டமைப்பு SDL_CursorData
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
நிலையான Cursor x11_empty_cursor = None;
நிலையான bool x11_cursor_visible = true;

நிலையான SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_இடது + 1];

நிலையான Display *GetDisplay(வெறுமை)
{
    திரும்பு SDL_GetVideoDevice()->internal->display;
}

நிலையான Cursor X11_CreateEmptyCursor(வெறுமை)
{
    எனில் (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        எழுத்து data[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(data);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreateBitmapFromData(display, Default_வேர்_Window(display),
                                           data, 1, 1);
        எனில் (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    திரும்பு x11_empty_cursor;
}

நிலையான வெறுமை X11_DestroyEmptyCursor(வெறுமை)
{
    எனில் (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

நிலையான SDL_Cursor *X11_CreateCursorAndData(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, அளவு(*cursor));
    எனில் (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, அளவு(*data));
        எனில் (!data) {
            SDL_free(cursor);
            திரும்பு வெற்று;
        }
        data->cursor = x11_cursor;
        cursor->internal = data;
    }
    திரும்பு cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
நிலையான XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, முழு hot_x, முழு hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    எனில் (!image) {
        SDL_OutOfMemory();
        திரும்பு வெற்று;
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

    திரும்பு image;
}

நிலையான Cursor X11_CreateXCursorCursor(SDL_Surface *surface, முழு hot_x, முழு hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    எனில் (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    திரும்பு cursor;
}

நிலையான Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, முழு இலக்கம்_frames, முழு hot_x, முழு hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(இலக்கம்_frames);
    எனில் (!images) {
        SDL_OutOfMemory();
        திரும்பு None;
    }

    க்கு (முழு i = 0; i < இலக்கம்_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        எனில் (!image) {
            செல் cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    திரும்பு cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

நிலையான Cursor X11_CreatePixmapCursor(SDL_Surface *surface, முழு hot_x, முழு hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *data_bits, *mask_bits;
    Pixmap data_pixmap, mask_pixmap;
    முழு x, y;
    unsigned முழு rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    size_t width_bytes = ((surface->w + 7) & ~((size_t)7)) / 8;

    data_bits = SDL_calloc(1, surface->h * width_bytes);
    எனில் (!data_bits) {
        திரும்பு None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    எனில் (!mask_bits) {
        SDL_free(data_bits);
        திரும்பு None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    க்கு (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        க்கு (x = 0; x < surface->w; ++x) {
            முழு alpha = (*ptr >> 24) & 0xff;
            முழு red = (*ptr >> 16) & 0xff;
            முழு green = (*ptr >> 8) & 0xff;
            முழு blue = (*ptr >> 0) & 0xff;
            எனில் (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                எனில் ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    data_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
                } இல்லையெனில் {
                    bgBits++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    எனில் (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } இல்லையெனில் {
        fg.red = fg.green = fg.blue = 0;
    }

    எனில் (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } இல்லையெனில் {
        bg.red = bg.green = bg.blue = 0;
    }

    data_pixmap = X11_XCreateBitmapFromData(display, Default_வேர்_Window(display),
                                            (எழுத்து *)data_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreateBitmapFromData(display, Default_வேர்_Window(display),
                                            (எழுத்து *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, data_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, data_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(data_bits);
    SDL_free(mask_bits);

    திரும்பு cursor;
}

நிலையான SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, முழு hot_x, முழு hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    எனில் (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#endif
    எனில் (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    திரும்பு X11_CreateCursorAndData(x11_cursor);
}

நிலையான SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, முழு இலக்கம்_frames, முழு hot_x, முழு hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    எனில் (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, இலக்கம்_frames, hot_x, hot_y);
    }
#endif
    எனில் (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    திரும்பு X11_CreateCursorAndData(x11_cursor);
}

நிலையான unsigned முழு GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    தேர்வு (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        நிலை SDL_SYSTEM_CURSOR_DEFAULT: திரும்பு XC_இடது_ptr;
        நிலை SDL_SYSTEM_CURSOR_TEXT: திரும்பு XC_xterm;
        நிலை SDL_SYSTEM_CURSOR_WAIT: திரும்பு XC_watch;
        நிலை SDL_SYSTEM_CURSOR_CROSSHAIR: திரும்பு XC_tcross;
        நிலை SDL_SYSTEM_CURSOR_PROGRESS: திரும்பு XC_watch;
        நிலை SDL_SYSTEM_CURSOR_NWSE_RESIZE: திரும்பு XC_உச்சி_இடது_corner;
        நிலை SDL_SYSTEM_CURSOR_NESW_RESIZE: திரும்பு XC_உச்சி_வலது_corner;
        நிலை SDL_SYSTEM_CURSOR_EW_RESIZE: திரும்பு XC_sb_h_double_arrow;
        நிலை SDL_SYSTEM_CURSOR_NS_RESIZE: திரும்பு XC_sb_v_double_arrow;
        நிலை SDL_SYSTEM_CURSOR_MOVE: திரும்பு XC_fleur;
        நிலை SDL_SYSTEM_CURSOR_NOT_ALLOWED: திரும்பு XC_pirate;
        நிலை SDL_SYSTEM_CURSOR_POINTER: திரும்பு XC_hand2;
        நிலை SDL_SYSTEM_CURSOR_NW_RESIZE: திரும்பு XC_உச்சி_இடது_corner;
        நிலை SDL_SYSTEM_CURSOR_N_RESIZE: திரும்பு XC_உச்சி_side;
        நிலை SDL_SYSTEM_CURSOR_NE_RESIZE: திரும்பு XC_உச்சி_வலது_corner;
        நிலை SDL_SYSTEM_CURSOR_E_RESIZE: திரும்பு XC_வலது_side;
        நிலை SDL_SYSTEM_CURSOR_SE_RESIZE: திரும்பு XC_bottom_வலது_corner;
        நிலை SDL_SYSTEM_CURSOR_S_RESIZE: திரும்பு XC_bottom_side;
        நிலை SDL_SYSTEM_CURSOR_SW_RESIZE: திரும்பு XC_bottom_இடது_corner;
        நிலை SDL_SYSTEM_CURSOR_W_RESIZE: திரும்பு XC_இடது_side;
        நிலை SDL_SYSTEM_CURSOR_CONTEXT_MENU: திரும்பு XC_hand2;
        நிலை SDL_SYSTEM_CURSOR_HELP: திரும்பு XC_question_arrow;
        நிலை SDL_SYSTEM_CURSOR_CELL: திரும்பு XC_cross;
        நிலை SDL_SYSTEM_CURSOR_VERTICAL_TEXT: திரும்பு XC_xterm;
        நிலை SDL_SYSTEM_CURSOR_ALIAS: திரும்பு XC_hand2;
        நிலை SDL_SYSTEM_CURSOR_COPY: திரும்பு XC_hand2;
        நிலை SDL_SYSTEM_CURSOR_NO_DROP: திரும்பு XC_pirate;
        நிலை SDL_SYSTEM_CURSOR_GRAB: திரும்பு XC_hand2;
        நிலை SDL_SYSTEM_CURSOR_GRABBING: திரும்பு XC_hand2;
        நிலை SDL_SYSTEM_CURSOR_COL_RESIZE: திரும்பு XC_sb_h_double_arrow;
        நிலை SDL_SYSTEM_CURSOR_ROW_RESIZE: திரும்பு XC_sb_v_double_arrow;
        நிலை SDL_SYSTEM_CURSOR_ALL_SCROLL: திரும்பு XC_fleur;
        நிலை SDL_SYSTEM_CURSOR_ZOOM_IN: திரும்பு XC_hand2;
        நிலை SDL_SYSTEM_CURSOR_ZOOM_OUT: திரும்பு XC_hand2;
        நிலை SDL_SYSTEM_CURSOR_மொத்தம்: நிறுத்து;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    திரும்பு 0;
}

நிலையான SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = வெற்று;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    எனில் (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, வெற்று));
    }
#endif

    எனில் (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    எனில் (x11_cursor != None) {
        cursor = X11_CreateCursorAndData(x11_cursor);
    }

    திரும்பு cursor;
}

நிலையான SDL_Cursor *X11_CreateDefaultCursor(வெறுமை)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    திரும்பு X11_CreateSystemCursor(id);
}

நிலையான வெறுமை X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    எனில் (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

நிலையான bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    எனில் (cursor) {
        x11_cursor = cursor->internal->cursor;
    } இல்லையெனில் {
        x11_cursor = X11_CreateEmptyCursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_Window *window;

        x11_cursor_visible = !!cursor;

        க்கு (window = video->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            எனில் (data) {
                எனில் (x11_cursor != None) {
                    X11_XDefineCursor(display, data->xwindow, x11_cursor);
                } இல்லையெனில் {
                    X11_XUndefineCursor(display, data->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    திரும்பு true;
}

நிலையான வெறுமை X11_WarpMouseInternal(Window xwindow, தசம x, தசம y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    எனில் (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    எனில் (warp_hack) {
        X11_ShowCursor(வெற்று);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    முழு deviceid = 0;
    எனில் (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        எனில் (Screen_மொத்தம்(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    எனில் (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } இல்லையெனில்
#endif
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (முழு)x, (முழு)y);
    }

    எனில் (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

நிலையான bool X11_WarpMouse(SDL_Window *window, தசம x, தசம y)
{
    SDL_WindowData *data = window->internal;

    எனில் (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        திரும்பு true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    எனில் (data->pointer_barrier_active == false) {
        X11_WarpMouseInternal(data->xwindow, x, y);
    }
#இல்லையெனில்
    X11_WarpMouseInternal(data->xwindow, x, y);
#endif
    திரும்பு true;
}

நிலையான bool X11_WarpMouseGlobal(தசம x, தசம y)
{
    எனில் (X11_WarpMouseXTest(SDL_GetVideoDevice(), வெற்று, x, y)) {
        திரும்பு true;
    }

    X11_WarpMouseInternal(Default_வேர்_Window(GetDisplay()), x, y);
    திரும்பு true;
}

நிலையான bool X11_SetRelativeMouseMode(bool enabled)
{
    எனில் (!X11_Xinput2IsInitialized()) {
        திரும்பு SDL_Unsupported();
    }
    திரும்பு true;
}

நிலையான bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    எனில் (window) {
        SDL_WindowData *data = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        எனில் (!data->xinput2_mouse_enabled || data->mouse_grabbed) {
            மாறிலி unsigned முழு mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (data->mouse_grabbed ? data->xwindow : None);
            மாறிலி முழு rc = X11_XGrabPointer(display, data->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            எனில் (rc != GrabSuccess) {
                திரும்பு SDL_SetError("X server refused mouse capture");
            }

            எனில் (data->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                data->videodata->global_mouse_changed = true;
            }
        }
    } இல்லையெனில் எனில் (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } இல்லையெனில் {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    திரும்பு true;
}

நிலையான SDL_MouseButtonFlags X11_GetGlobalMouseState(தசம *x, தசம *y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    முழு i;

    // !!! FIXME: should we XSync() here first?

    எனில் (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    எனில் (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(வெற்று);
        எனில் (displays) {
            க்கு (i = 0; displays[i]; ++i) {
                SDL_DisplayData *data = SDL_GetDisplayDriverData(displays[i]);
                எனில் (data) {
                    Window வேர், child;
                    முழு rootx, rooty, winx, winy;
                    unsigned முழு mask;
                    எனில் (X11_XQueryPointer(display, வேர்_Window(display, data->screen), &வேர், &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes வேர்_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(வெற்று, வெற்று) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, வேர், &வேர்_attrs);
                        videodata->global_mouse_position.x = வேர்_attrs.x + rootx;
                        videodata->global_mouse_position.y = வேர்_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        நிறுத்து;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (தசம)videodata->global_mouse_position.x;
    *y = (தசம)videodata->global_mouse_position.y;
    திரும்பு videodata->global_mouse_buttons;
}

வெறுமை X11_InitMouse(SDL_VideoDevice *_this)
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
    போது (r <= SDL_HITTEST_RESIZE_இடது) {
        தேர்வு (r) {
        நிலை SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); நிறுத்து;
        நிலை SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_உச்சி: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_வலது: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); நிறுத்து;
        நிலை SDL_HITTEST_RESIZE_இடது: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); நிறுத்து;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

வெறுமை X11_QuitMouse(SDL_VideoDevice *_this)
{
    க்கு (முழு i = 0; i < SDL_arraysize(sys_cursors); i++) {
        எனில் (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = வெற்று;
        }
    }

    X11_DestroyEmptyCursor();
}

வெறுமை X11_SetHitTestCursor(SDL_HitTestResult rc)
{
    எனில் (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } இல்லையெனில் {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
