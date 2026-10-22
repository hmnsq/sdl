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

स्थिर SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_डावा + 1];

स्थिर Display *GetDisplay(शून्य)
{
    परत SDL_GetVideoDevice()->internal->display;
}

स्थिर Cursor X11_CreateEmptyCursor(शून्य)
{
    जर (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        अक्षर data[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(data);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreateBitmapFromData(display, Default_मूळ_Window(display),
                                           data, 1, 1);
        जर (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    परत x11_empty_cursor;
}

स्थिर शून्य X11_DestroyEmptyCursor(शून्य)
{
    जर (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

स्थिर SDL_Cursor *X11_CreateCursorAndData(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, आकार(*cursor));
    जर (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, आकार(*data));
        जर (!data) {
            SDL_free(cursor);
            परत रिक्त;
        }
        data->cursor = x11_cursor;
        cursor->internal = data;
    }
    परत cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
स्थिर XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    जर (!image) {
        SDL_OutOfMemory();
        परत रिक्त;
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

    परत image;
}

स्थिर Cursor X11_CreateXCursorCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    जर (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    परत cursor;
}

स्थिर Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, पूर्णांक अंक_frames, पूर्णांक hot_x, पूर्णांक hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(अंक_frames);
    जर (!images) {
        SDL_OutOfMemory();
        परत None;
    }

    साठी (पूर्णांक i = 0; i < अंक_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        जर (!image) {
            जा cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    परत cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

स्थिर Cursor X11_CreatePixmapCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *data_bits, *mask_bits;
    Pixmap data_pixmap, mask_pixmap;
    पूर्णांक x, y;
    अचिन्हित पूर्णांक rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    माप_प्रकार width_bytes = ((surface->w + 7) & ~((माप_प्रकार)7)) / 8;

    data_bits = SDL_calloc(1, surface->h * width_bytes);
    जर (!data_bits) {
        परत None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    जर (!mask_bits) {
        SDL_free(data_bits);
        परत None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    साठी (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        साठी (x = 0; x < surface->w; ++x) {
            पूर्णांक alpha = (*ptr >> 24) & 0xff;
            पूर्णांक red = (*ptr >> 16) & 0xff;
            पूर्णांक green = (*ptr >> 8) & 0xff;
            पूर्णांक blue = (*ptr >> 0) & 0xff;
            जर (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                जर ((red + green + blue) > 0x40) {
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

    जर (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } अन्यथा {
        fg.red = fg.green = fg.blue = 0;
    }

    जर (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } अन्यथा {
        bg.red = bg.green = bg.blue = 0;
    }

    data_pixmap = X11_XCreateBitmapFromData(display, Default_मूळ_Window(display),
                                            (अक्षर *)data_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreateBitmapFromData(display, Default_मूळ_Window(display),
                                            (अक्षर *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, data_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, data_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(data_bits);
    SDL_free(mask_bits);

    परत cursor;
}

स्थिर SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    जर (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#endif
    जर (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    परत X11_CreateCursorAndData(x11_cursor);
}

स्थिर SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, पूर्णांक अंक_frames, पूर्णांक hot_x, पूर्णांक hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    जर (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, अंक_frames, hot_x, hot_y);
    }
#endif
    जर (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    परत X11_CreateCursorAndData(x11_cursor);
}

स्थिर अचिन्हित पूर्णांक GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    निवड (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        स्थिती SDL_SYSTEM_CURSOR_DEFAULT: परत XC_डावा_ptr;
        स्थिती SDL_SYSTEM_CURSOR_TEXT: परत XC_xterm;
        स्थिती SDL_SYSTEM_CURSOR_WAIT: परत XC_watch;
        स्थिती SDL_SYSTEM_CURSOR_CROSSHAIR: परत XC_tcross;
        स्थिती SDL_SYSTEM_CURSOR_PROGRESS: परत XC_watch;
        स्थिती SDL_SYSTEM_CURSOR_NWSE_RESIZE: परत XC_शीर्ष_डावा_corner;
        स्थिती SDL_SYSTEM_CURSOR_NESW_RESIZE: परत XC_शीर्ष_उजवा_corner;
        स्थिती SDL_SYSTEM_CURSOR_EW_RESIZE: परत XC_sb_h_double_arrow;
        स्थिती SDL_SYSTEM_CURSOR_NS_RESIZE: परत XC_sb_v_double_arrow;
        स्थिती SDL_SYSTEM_CURSOR_MOVE: परत XC_fleur;
        स्थिती SDL_SYSTEM_CURSOR_NOT_ALLOWED: परत XC_pirate;
        स्थिती SDL_SYSTEM_CURSOR_POINTER: परत XC_hand2;
        स्थिती SDL_SYSTEM_CURSOR_NW_RESIZE: परत XC_शीर्ष_डावा_corner;
        स्थिती SDL_SYSTEM_CURSOR_N_RESIZE: परत XC_शीर्ष_side;
        स्थिती SDL_SYSTEM_CURSOR_NE_RESIZE: परत XC_शीर्ष_उजवा_corner;
        स्थिती SDL_SYSTEM_CURSOR_E_RESIZE: परत XC_उजवा_side;
        स्थिती SDL_SYSTEM_CURSOR_SE_RESIZE: परत XC_bottom_उजवा_corner;
        स्थिती SDL_SYSTEM_CURSOR_S_RESIZE: परत XC_bottom_side;
        स्थिती SDL_SYSTEM_CURSOR_SW_RESIZE: परत XC_bottom_डावा_corner;
        स्थिती SDL_SYSTEM_CURSOR_W_RESIZE: परत XC_डावा_side;
        स्थिती SDL_SYSTEM_CURSOR_CONTEXT_MENU: परत XC_hand2;
        स्थिती SDL_SYSTEM_CURSOR_HELP: परत XC_question_arrow;
        स्थिती SDL_SYSTEM_CURSOR_CELL: परत XC_cross;
        स्थिती SDL_SYSTEM_CURSOR_VERTICAL_TEXT: परत XC_xterm;
        स्थिती SDL_SYSTEM_CURSOR_ALIAS: परत XC_hand2;
        स्थिती SDL_SYSTEM_CURSOR_COPY: परत XC_hand2;
        स्थिती SDL_SYSTEM_CURSOR_NO_DROP: परत XC_pirate;
        स्थिती SDL_SYSTEM_CURSOR_GRAB: परत XC_hand2;
        स्थिती SDL_SYSTEM_CURSOR_GRABBING: परत XC_hand2;
        स्थिती SDL_SYSTEM_CURSOR_COL_RESIZE: परत XC_sb_h_double_arrow;
        स्थिती SDL_SYSTEM_CURSOR_ROW_RESIZE: परत XC_sb_v_double_arrow;
        स्थिती SDL_SYSTEM_CURSOR_ALL_SCROLL: परत XC_fleur;
        स्थिती SDL_SYSTEM_CURSOR_ZOOM_IN: परत XC_hand2;
        स्थिती SDL_SYSTEM_CURSOR_ZOOM_OUT: परत XC_hand2;
        स्थिती SDL_SYSTEM_CURSOR_मोजणी: थांबा;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    परत 0;
}

स्थिर SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = रिक्त;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    जर (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, रिक्त));
    }
#endif

    जर (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    जर (x11_cursor != None) {
        cursor = X11_CreateCursorAndData(x11_cursor);
    }

    परत cursor;
}

स्थिर SDL_Cursor *X11_CreateDefaultCursor(शून्य)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    परत X11_CreateSystemCursor(id);
}

स्थिर शून्य X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    जर (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

स्थिर bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    जर (cursor) {
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

        साठी (window = video->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            जर (data) {
                जर (x11_cursor != None) {
                    X11_XDefineCursor(display, data->xwindow, x11_cursor);
                } अन्यथा {
                    X11_XUndefineCursor(display, data->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    परत true;
}

स्थिर शून्य X11_WarpMouseInternal(Window xwindow, दशांश x, दशांश y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    जर (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    जर (warp_hack) {
        X11_ShowCursor(रिक्त);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    पूर्णांक deviceid = 0;
    जर (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        जर (Screen_मोजणी(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    जर (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } अन्यथा
#endif
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (पूर्णांक)x, (पूर्णांक)y);
    }

    जर (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

स्थिर bool X11_WarpMouse(SDL_Window *window, दशांश x, दशांश y)
{
    SDL_WindowData *data = window->internal;

    जर (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        परत true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    जर (data->pointer_barrier_active == false) {
        X11_WarpMouseInternal(data->xwindow, x, y);
    }
#अन्यथा
    X11_WarpMouseInternal(data->xwindow, x, y);
#endif
    परत true;
}

स्थिर bool X11_WarpMouseGlobal(दशांश x, दशांश y)
{
    जर (X11_WarpMouseXTest(SDL_GetVideoDevice(), रिक्त, x, y)) {
        परत true;
    }

    X11_WarpMouseInternal(Default_मूळ_Window(GetDisplay()), x, y);
    परत true;
}

स्थिर bool X11_SetRelativeMouseMode(bool enabled)
{
    जर (!X11_Xinput2IsInitialized()) {
        परत SDL_Unsupported();
    }
    परत true;
}

स्थिर bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    जर (window) {
        SDL_WindowData *data = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        जर (!data->xinput2_mouse_enabled || data->mouse_grabbed) {
            स्थिरांक अचिन्हित पूर्णांक mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (data->mouse_grabbed ? data->xwindow : None);
            स्थिरांक पूर्णांक rc = X11_XGrabPointer(display, data->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            जर (rc != GrabSuccess) {
                परत SDL_SetError("X server refused mouse capture");
            }

            जर (data->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                data->videodata->global_mouse_changed = true;
            }
        }
    } अन्यथा जर (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } अन्यथा {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    परत true;
}

स्थिर SDL_MouseButtonFlags X11_GetGlobalMouseState(दशांश *x, दशांश *y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    पूर्णांक i;

    // !!! FIXME: should we XSync() here first?

    जर (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    जर (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(रिक्त);
        जर (displays) {
            साठी (i = 0; displays[i]; ++i) {
                SDL_DisplayData *data = SDL_GetDisplayDriverData(displays[i]);
                जर (data) {
                    Window मूळ, child;
                    पूर्णांक rootx, rooty, winx, winy;
                    अचिन्हित पूर्णांक mask;
                    जर (X11_XQueryPointer(display, मूळ_Window(display, data->screen), &मूळ, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes मूळ_attrs;
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
                        X11_XGetWindowAttributes(display, मूळ, &मूळ_attrs);
                        videodata->global_mouse_position.x = मूळ_attrs.x + rootx;
                        videodata->global_mouse_position.y = मूळ_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        थांबा;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (दशांश)videodata->global_mouse_position.x;
    *y = (दशांश)videodata->global_mouse_position.y;
    परत videodata->global_mouse_buttons;
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
    पर्यंत (r <= SDL_HITTEST_RESIZE_डावा) {
        निवड (r) {
        स्थिती SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); थांबा;
        स्थिती SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); थांबा;
        स्थिती SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); थांबा;
        स्थिती SDL_HITTEST_RESIZE_शीर्ष: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); थांबा;
        स्थिती SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); थांबा;
        स्थिती SDL_HITTEST_RESIZE_उजवा: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); थांबा;
        स्थिती SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); थांबा;
        स्थिती SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); थांबा;
        स्थिती SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); थांबा;
        स्थिती SDL_HITTEST_RESIZE_डावा: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); थांबा;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

शून्य X11_QuitMouse(SDL_VideoDevice *_this)
{
    साठी (पूर्णांक i = 0; i < SDL_arraysize(sys_cursors); i++) {
        जर (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = रिक्त;
        }
    }

    X11_DestroyEmptyCursor();
}

शून्य X11_SetHitTestCursor(SDL_HitTestResult rc)
{
    जर (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } अन्यथा {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
