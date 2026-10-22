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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव <X11/cursorfont.h>
#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11mouse.h"
#अन्तर्भाव "SDL_x11xinput2.h"
#अन्तर्भाव "SDL_x11xtest.h"
#अन्तर्भाव "../SDL_video_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"

संरचना SDL_CursorData
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
स्थिर Cursor x11_empty_cursor = None;
स्थिर bool x11_cursor_visible = true;

स्थिर SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_बायाँ + 1];

स्थिर Display *GetDisplay(शून्य)
{
    प्रत्यागम SDL_GetVideoDevice()->internal->display;
}

स्थिर Cursor X11_CreateEmptyCursor(शून्य)
{
    यदि (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        वर्ण data[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(data);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreateBitmapFromData(display, Default_मूल_Window(display),
                                           data, 1, 1);
        यदि (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    प्रत्यागम x11_empty_cursor;
}

स्थिर शून्य X11_DestroyEmptyCursor(शून्य)
{
    यदि (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

स्थिर SDL_Cursor *X11_CreateCursorAndData(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, परिमाण(*cursor));
    यदि (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, परिमाण(*data));
        यदि (!data) {
            SDL_free(cursor);
            प्रत्यागम रिक्त;
        }
        data->cursor = x11_cursor;
        cursor->internal = data;
    }
    प्रत्यागम cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
स्थिर XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    यदि (!image) {
        SDL_OutOfMemory();
        प्रत्यागम रिक्त;
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

    प्रत्यागम image;
}

स्थिर Cursor X11_CreateXCursorCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    यदि (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    प्रत्यागम cursor;
}

स्थिर Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, पूर्णाङ्क अंक_frames, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(अंक_frames);
    यदि (!images) {
        SDL_OutOfMemory();
        प्रत्यागम None;
    }

    प्रति (पूर्णाङ्क i = 0; i < अंक_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        यदि (!image) {
            गच्छ cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    प्रत्यागम cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

स्थिर Cursor X11_CreatePixmapCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *data_bits, *mask_bits;
    Pixmap data_pixmap, mask_pixmap;
    पूर्णाङ्क x, y;
    unsigned पूर्णाङ्क rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    size_t width_bytes = ((surface->w + 7) & ~((size_t)7)) / 8;

    data_bits = SDL_calloc(1, surface->h * width_bytes);
    यदि (!data_bits) {
        प्रत्यागम None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    यदि (!mask_bits) {
        SDL_free(data_bits);
        प्रत्यागम None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    प्रति (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        प्रति (x = 0; x < surface->w; ++x) {
            पूर्णाङ्क alpha = (*ptr >> 24) & 0xff;
            पूर्णाङ्क red = (*ptr >> 16) & 0xff;
            पूर्णाङ्क green = (*ptr >> 8) & 0xff;
            पूर्णाङ्क blue = (*ptr >> 0) & 0xff;
            यदि (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                यदि ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    data_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
                } अन्यथा {
                    bgBits++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    यदि (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } अन्यथा {
        fg.red = fg.green = fg.blue = 0;
    }

    यदि (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } अन्यथा {
        bg.red = bg.green = bg.blue = 0;
    }

    data_pixmap = X11_XCreateBitmapFromData(display, Default_मूल_Window(display),
                                            (वर्ण *)data_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreateBitmapFromData(display, Default_मूल_Window(display),
                                            (वर्ण *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, data_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, data_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(data_bits);
    SDL_free(mask_bits);

    प्रत्यागम cursor;
}

स्थिर SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    यदि (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#endif
    यदि (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    प्रत्यागम X11_CreateCursorAndData(x11_cursor);
}

स्थिर SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, पूर्णाङ्क अंक_frames, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    यदि (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, अंक_frames, hot_x, hot_y);
    }
#endif
    यदि (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    प्रत्यागम X11_CreateCursorAndData(x11_cursor);
}

स्थिर unsigned पूर्णाङ्क GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    विकल्प (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        पक्ष SDL_SYSTEM_CURSOR_DEFAULT: प्रत्यागम XC_बायाँ_ptr;
        पक्ष SDL_SYSTEM_CURSOR_TEXT: प्रत्यागम XC_xterm;
        पक्ष SDL_SYSTEM_CURSOR_WAIT: प्रत्यागम XC_watch;
        पक्ष SDL_SYSTEM_CURSOR_CROSSHAIR: प्रत्यागम XC_tcross;
        पक्ष SDL_SYSTEM_CURSOR_PROGRESS: प्रत्यागम XC_watch;
        पक्ष SDL_SYSTEM_CURSOR_NWSE_RESIZE: प्रत्यागम XC_शीर्ष_बायाँ_corner;
        पक्ष SDL_SYSTEM_CURSOR_NESW_RESIZE: प्रत्यागम XC_शीर्ष_दायाँ_corner;
        पक्ष SDL_SYSTEM_CURSOR_EW_RESIZE: प्रत्यागम XC_sb_h_double_arrow;
        पक्ष SDL_SYSTEM_CURSOR_NS_RESIZE: प्रत्यागम XC_sb_v_double_arrow;
        पक्ष SDL_SYSTEM_CURSOR_MOVE: प्रत्यागम XC_fleur;
        पक्ष SDL_SYSTEM_CURSOR_NOT_ALLOWED: प्रत्यागम XC_pirate;
        पक्ष SDL_SYSTEM_CURSOR_POINTER: प्रत्यागम XC_hand2;
        पक्ष SDL_SYSTEM_CURSOR_NW_RESIZE: प्रत्यागम XC_शीर्ष_बायाँ_corner;
        पक्ष SDL_SYSTEM_CURSOR_N_RESIZE: प्रत्यागम XC_शीर्ष_side;
        पक्ष SDL_SYSTEM_CURSOR_NE_RESIZE: प्रत्यागम XC_शीर्ष_दायाँ_corner;
        पक्ष SDL_SYSTEM_CURSOR_E_RESIZE: प्रत्यागम XC_दायाँ_side;
        पक्ष SDL_SYSTEM_CURSOR_SE_RESIZE: प्रत्यागम XC_bottom_दायाँ_corner;
        पक्ष SDL_SYSTEM_CURSOR_S_RESIZE: प्रत्यागम XC_bottom_side;
        पक्ष SDL_SYSTEM_CURSOR_SW_RESIZE: प्रत्यागम XC_bottom_बायाँ_corner;
        पक्ष SDL_SYSTEM_CURSOR_W_RESIZE: प्रत्यागम XC_बायाँ_side;
        पक्ष SDL_SYSTEM_CURSOR_CONTEXT_MENU: प्रत्यागम XC_hand2;
        पक्ष SDL_SYSTEM_CURSOR_HELP: प्रत्यागम XC_question_arrow;
        पक्ष SDL_SYSTEM_CURSOR_CELL: प्रत्यागम XC_cross;
        पक्ष SDL_SYSTEM_CURSOR_VERTICAL_TEXT: प्रत्यागम XC_xterm;
        पक्ष SDL_SYSTEM_CURSOR_ALIAS: प्रत्यागम XC_hand2;
        पक्ष SDL_SYSTEM_CURSOR_COPY: प्रत्यागम XC_hand2;
        पक्ष SDL_SYSTEM_CURSOR_NO_DROP: प्रत्यागम XC_pirate;
        पक्ष SDL_SYSTEM_CURSOR_GRAB: प्रत्यागम XC_hand2;
        पक्ष SDL_SYSTEM_CURSOR_GRABBING: प्रत्यागम XC_hand2;
        पक्ष SDL_SYSTEM_CURSOR_COL_RESIZE: प्रत्यागम XC_sb_h_double_arrow;
        पक्ष SDL_SYSTEM_CURSOR_ROW_RESIZE: प्रत्यागम XC_sb_v_double_arrow;
        पक्ष SDL_SYSTEM_CURSOR_ALL_SCROLL: प्रत्यागम XC_fleur;
        पक्ष SDL_SYSTEM_CURSOR_ZOOM_IN: प्रत्यागम XC_hand2;
        पक्ष SDL_SYSTEM_CURSOR_ZOOM_OUT: प्रत्यागम XC_hand2;
        पक्ष SDL_SYSTEM_CURSOR_गिनती: भङ्ग;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    प्रत्यागम 0;
}

स्थिर SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = रिक्त;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    यदि (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, रिक्त));
    }
#endif

    यदि (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    यदि (x11_cursor != None) {
        cursor = X11_CreateCursorAndData(x11_cursor);
    }

    प्रत्यागम cursor;
}

स्थिर SDL_Cursor *X11_CreateDefaultCursor(शून्य)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    प्रत्यागम X11_CreateSystemCursor(id);
}

स्थिर शून्य X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    यदि (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

स्थिर bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    यदि (cursor) {
        x11_cursor = cursor->internal->cursor;
    } अन्यथा {
        x11_cursor = X11_CreateEmptyCursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_Window *window;

        x11_cursor_visible = !!cursor;

        प्रति (window = video->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            यदि (data) {
                यदि (x11_cursor != None) {
                    X11_XDefineCursor(display, data->xwindow, x11_cursor);
                } अन्यथा {
                    X11_XUndefineCursor(display, data->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    प्रत्यागम true;
}

स्थिर शून्य X11_WarpMouseInternal(Window xwindow, भिन्न x, भिन्न y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    यदि (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    यदि (warp_hack) {
        X11_ShowCursor(रिक्त);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    पूर्णाङ्क deviceid = 0;
    यदि (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        यदि (Screen_गिनती(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    यदि (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } अन्यथा
#endif
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (पूर्णाङ्क)x, (पूर्णाङ्क)y);
    }

    यदि (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

स्थिर bool X11_WarpMouse(SDL_Window *window, भिन्न x, भिन्न y)
{
    SDL_WindowData *data = window->internal;

    यदि (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        प्रत्यागम true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    यदि (data->pointer_barrier_active == false) {
        X11_WarpMouseInternal(data->xwindow, x, y);
    }
#अन्यथा
    X11_WarpMouseInternal(data->xwindow, x, y);
#endif
    प्रत्यागम true;
}

स्थिर bool X11_WarpMouseGlobal(भिन्न x, भिन्न y)
{
    यदि (X11_WarpMouseXTest(SDL_GetVideoDevice(), रिक्त, x, y)) {
        प्रत्यागम true;
    }

    X11_WarpMouseInternal(Default_मूल_Window(GetDisplay()), x, y);
    प्रत्यागम true;
}

स्थिर bool X11_SetRelativeMouseMode(bool enabled)
{
    यदि (!X11_Xinput2IsInitialized()) {
        प्रत्यागम SDL_Unsupported();
    }
    प्रत्यागम true;
}

स्थिर bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    यदि (window) {
        SDL_WindowData *data = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        यदि (!data->xinput2_mouse_enabled || data->mouse_grabbed) {
            ध्रुव unsigned पूर्णाङ्क mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (data->mouse_grabbed ? data->xwindow : None);
            ध्रुव पूर्णाङ्क rc = X11_XGrabPointer(display, data->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            यदि (rc != GrabSuccess) {
                प्रत्यागम SDL_SetError("X server refused mouse capture");
            }

            यदि (data->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                data->videodata->global_mouse_changed = true;
            }
        }
    } अन्यथा यदि (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } अन्यथा {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    प्रत्यागम true;
}

स्थिर SDL_MouseButtonFlags X11_GetGlobalMouseState(भिन्न *x, भिन्न *y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    पूर्णाङ्क i;

    // !!! FIXME: should we XSync() here first?

    यदि (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    यदि (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(रिक्त);
        यदि (displays) {
            प्रति (i = 0; displays[i]; ++i) {
                SDL_DisplayData *data = SDL_GetDisplayDriverData(displays[i]);
                यदि (data) {
                    Window मूल, child;
                    पूर्णाङ्क rootx, rooty, winx, winy;
                    unsigned पूर्णाङ्क mask;
                    यदि (X11_XQueryPointer(display, मूल_Window(display, data->screen), &मूल, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes मूल_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(रिक्त, रिक्त) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, मूल, &मूल_attrs);
                        videodata->global_mouse_position.x = मूल_attrs.x + rootx;
                        videodata->global_mouse_position.y = मूल_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        भङ्ग;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (भिन्न)videodata->global_mouse_position.x;
    *y = (भिन्न)videodata->global_mouse_position.y;
    प्रत्यागम videodata->global_mouse_buttons;
}

शून्य X11_InitMouse(SDL_VideoDevice *_this)
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
    यावत् (r <= SDL_HITTEST_RESIZE_बायाँ) {
        विकल्प (r) {
        पक्ष SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); भङ्ग;
        पक्ष SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_शीर्ष: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_दायाँ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_बायाँ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); भङ्ग;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

शून्य X11_QuitMouse(SDL_VideoDevice *_this)
{
    प्रति (पूर्णाङ्क i = 0; i < SDL_arraysize(sys_cursors); i++) {
        यदि (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = रिक्त;
        }
    }

    X11_DestroyEmptyCursor();
}

शून्य X11_SetHitTestCursor(SDL_HitTestResult rc)
{
    यदि (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } अन्यथा {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
