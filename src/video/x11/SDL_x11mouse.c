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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश <X11/cursorfont.h>
#समावेश "SDL_x11video.h"
#समावेश "SDL_x11mouse.h"
#समावेश "SDL_x11xinput2.h"
#समावेश "SDL_x11xtest.h"
#समावेश "../SDL_video_c.h"
#समावेश "../../events/SDL_mouse_c.h"

काष्ठा SDL_Cursor_तथ्य
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
अटल Cursor x11_empty_cursor = None;
अटल bool x11_cursor_visible = true;

अटल SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_बायाँ + 1];

अटल Display *GetDisplay(व्योम)
{
    वापस SDL_GetVideoDevice()->internal->display;
}

अटल Cursor X11_CreateEmptyCursor(व्योम)
{
    अगर (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        अक्षर तथ्य[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(तथ्य);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreate_Bitmap_From_तथ्य(display, Default_मूल_Window(display),
                                           तथ्य, 1, 1);
        अगर (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    वापस x11_empty_cursor;
}

अटल व्योम X11_DestroyEmptyCursor(व्योम)
{
    अगर (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

अटल SDL_Cursor *X11_Create_Cursor_And_तथ्य(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, माप(*cursor));
    अगर (cursor) {
        SDL_Cursor_तथ्य *तथ्य = (SDL_Cursor_तथ्य *)SDL_calloc(1, माप(*तथ्य));
        अगर (!तथ्य) {
            SDL_free(cursor);
            वापस शून्य;
        }
        तथ्य->cursor = x11_cursor;
        cursor->internal = तथ्य;
    }
    वापस cursor;
}

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XCURSOR
अटल XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    अगर (!image) {
        SDL_OutOfMemory();
        वापस शून्य;
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

    वापस image;
}

अटल Cursor X11_CreateXCursorCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    अगर (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    वापस cursor;
}

अटल Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, पूर्णांक अंक_frames, पूर्णांक hot_x, पूर्णांक hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(अंक_frames);
    अगर (!images) {
        SDL_OutOfMemory();
        वापस None;
    }

    क्रम (पूर्णांक i = 0; i < अंक_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        अगर (!image) {
            जाओ cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    वापस cursor;
}
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XCURSOR

अटल Cursor X11_CreatePixmapCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *तथ्य_bits, *mask_bits;
    Pixmap तथ्य_pixmap, mask_pixmap;
    पूर्णांक x, y;
    अचिन्हित पूर्णांक rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    माप_प्रकार width_bytes = ((surface->w + 7) & ~((माप_प्रकार)7)) / 8;

    तथ्य_bits = SDL_calloc(1, surface->h * width_bytes);
    अगर (!तथ्य_bits) {
        वापस None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    अगर (!mask_bits) {
        SDL_free(तथ्य_bits);
        वापस None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    क्रम (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        क्रम (x = 0; x < surface->w; ++x) {
            पूर्णांक alpha = (*ptr >> 24) & 0xff;
            पूर्णांक red = (*ptr >> 16) & 0xff;
            पूर्णांक green = (*ptr >> 8) & 0xff;
            पूर्णांक blue = (*ptr >> 0) & 0xff;
            अगर (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                अगर ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    तथ्य_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
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

    अगर (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } अन्यथा {
        fg.red = fg.green = fg.blue = 0;
    }

    अगर (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } अन्यथा {
        bg.red = bg.green = bg.blue = 0;
    }

    तथ्य_pixmap = X11_XCreate_Bitmap_From_तथ्य(display, Default_मूल_Window(display),
                                            (अक्षर *)तथ्य_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreate_Bitmap_From_तथ्य(display, Default_मूल_Window(display),
                                            (अक्षर *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, तथ्य_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, तथ्य_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(तथ्य_bits);
    SDL_free(mask_bits);

    वापस cursor;
}

अटल SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    Cursor x11_cursor = None;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XCURSOR
    अगर (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#पूर्ण_अगर
    अगर (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    वापस X11_Create_Cursor_And_तथ्य(x11_cursor);
}

अटल SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, पूर्णांक अंक_frames, पूर्णांक hot_x, पूर्णांक hot_y)
{
    Cursor x11_cursor = None;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XCURSOR
    अगर (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, अंक_frames, hot_x, hot_y);
    }
#पूर्ण_अगर
    अगर (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    वापस X11_Create_Cursor_And_तथ्य(x11_cursor);
}

अटल अचिन्हित पूर्णांक GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    चयन (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        हाल SDL_SYSTEM_CURSOR_DEFAULT: वापस XC_बायाँ_ptr;
        हाल SDL_SYSTEM_CURSOR_TEXT: वापस XC_xterm;
        हाल SDL_SYSTEM_CURSOR_WAIT: वापस XC_watch;
        हाल SDL_SYSTEM_CURSOR_CROSSHAIR: वापस XC_tcross;
        हाल SDL_SYSTEM_CURSOR_PROGRESS: वापस XC_watch;
        हाल SDL_SYSTEM_CURSOR_NWSE_RESIZE: वापस XC_शीर्ष_बायाँ_corner;
        हाल SDL_SYSTEM_CURSOR_NESW_RESIZE: वापस XC_शीर्ष_दायाँ_corner;
        हाल SDL_SYSTEM_CURSOR_EW_RESIZE: वापस XC_sb_h_double_arrow;
        हाल SDL_SYSTEM_CURSOR_NS_RESIZE: वापस XC_sb_v_double_arrow;
        हाल SDL_SYSTEM_CURSOR_MOVE: वापस XC_fleur;
        हाल SDL_SYSTEM_CURSOR_NOT_ALLOWED: वापस XC_pirate;
        हाल SDL_SYSTEM_CURSOR_POINTER: वापस XC_hand2;
        हाल SDL_SYSTEM_CURSOR_NW_RESIZE: वापस XC_शीर्ष_बायाँ_corner;
        हाल SDL_SYSTEM_CURSOR_N_RESIZE: वापस XC_शीर्ष_side;
        हाल SDL_SYSTEM_CURSOR_NE_RESIZE: वापस XC_शीर्ष_दायाँ_corner;
        हाल SDL_SYSTEM_CURSOR_E_RESIZE: वापस XC_दायाँ_side;
        हाल SDL_SYSTEM_CURSOR_SE_RESIZE: वापस XC_bottom_दायाँ_corner;
        हाल SDL_SYSTEM_CURSOR_S_RESIZE: वापस XC_bottom_side;
        हाल SDL_SYSTEM_CURSOR_SW_RESIZE: वापस XC_bottom_बायाँ_corner;
        हाल SDL_SYSTEM_CURSOR_W_RESIZE: वापस XC_बायाँ_side;
        हाल SDL_SYSTEM_CURSOR_CONTEXT_MENU: वापस XC_hand2;
        हाल SDL_SYSTEM_CURSOR_HELP: वापस XC_question_arrow;
        हाल SDL_SYSTEM_CURSOR_CELL: वापस XC_cross;
        हाल SDL_SYSTEM_CURSOR_VERTICAL_TEXT: वापस XC_xterm;
        हाल SDL_SYSTEM_CURSOR_ALIAS: वापस XC_hand2;
        हाल SDL_SYSTEM_CURSOR_COPY: वापस XC_hand2;
        हाल SDL_SYSTEM_CURSOR_NO_DROP: वापस XC_pirate;
        हाल SDL_SYSTEM_CURSOR_GRAB: वापस XC_hand2;
        हाल SDL_SYSTEM_CURSOR_GRABBING: वापस XC_hand2;
        हाल SDL_SYSTEM_CURSOR_COL_RESIZE: वापस XC_sb_h_double_arrow;
        हाल SDL_SYSTEM_CURSOR_ROW_RESIZE: वापस XC_sb_v_double_arrow;
        हाल SDL_SYSTEM_CURSOR_ALL_SCROLL: वापस XC_fleur;
        हाल SDL_SYSTEM_CURSOR_ZOOM_IN: वापस XC_hand2;
        हाल SDL_SYSTEM_CURSOR_ZOOM_OUT: वापस XC_hand2;
        हाल SDL_SYSTEM_CURSOR_गिनती: अवरोध;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    वापस 0;
}

अटल SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = शून्य;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XCURSOR
    अगर (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, शून्य));
    }
#पूर्ण_अगर

    अगर (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    अगर (x11_cursor != None) {
        cursor = X11_Create_Cursor_And_तथ्य(x11_cursor);
    }

    वापस cursor;
}

अटल SDL_Cursor *X11_CreateDefaultCursor(व्योम)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    वापस X11_CreateSystemCursor(id);
}

अटल व्योम X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    अगर (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

अटल bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    अगर (cursor) {
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

        क्रम (window = video->windows; window; window = window->अग्र) {
            SDL_Window_तथ्य *तथ्य = window->internal;
            अगर (तथ्य) {
                अगर (x11_cursor != None) {
                    X11_XDefineCursor(display, तथ्य->xwindow, x11_cursor);
                } अन्यथा {
                    X11_XUndefineCursor(display, तथ्य->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    वापस true;
}

अटल व्योम X11_WarpMouseInternal(Window xwindow, भग्न x, भग्न y)
{
    SDL_Video_तथ्य *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    अगर (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    अगर (warp_hack) {
        X11_ShowCursor(शून्य);
    }
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2
    पूर्णांक deviceid = 0;
    अगर (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        अगर (Screen_गिनती(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    अगर (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } अन्यथा
#पूर्ण_अगर
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (पूर्णांक)x, (पूर्णांक)y);
    }

    अगर (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

अटल bool X11_WarpMouse(SDL_Window *window, भग्न x, भग्न y)
{
    SDL_Window_तथ्य *तथ्य = window->internal;

    अगर (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        वापस true;
    }

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    अगर (तथ्य->pointer_barrier_active == false) {
        X11_WarpMouseInternal(तथ्य->xwindow, x, y);
    }
#अन्यथा
    X11_WarpMouseInternal(तथ्य->xwindow, x, y);
#पूर्ण_अगर
    वापस true;
}

अटल bool X11_WarpMouseGlobal(भग्न x, भग्न y)
{
    अगर (X11_WarpMouseXTest(SDL_GetVideoDevice(), शून्य, x, y)) {
        वापस true;
    }

    X11_WarpMouseInternal(Default_मूल_Window(GetDisplay()), x, y);
    वापस true;
}

अटल bool X11_SetRelativeMouseMode(bool enabled)
{
    अगर (!X11_Xinput2IsInitialized()) {
        वापस SDL_Unsupported();
    }
    वापस true;
}

अटल bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    अगर (window) {
        SDL_Window_तथ्य *तथ्य = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        अगर (!तथ्य->xinput2_mouse_enabled || तथ्य->mouse_grabbed) {
            स्थिर अचिन्हित पूर्णांक mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (तथ्य->mouse_grabbed ? तथ्य->xwindow : None);
            स्थिर पूर्णांक rc = X11_XGrabPointer(display, तथ्य->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            अगर (rc != GrabSuccess) {
                वापस SDL_SetError("X server refused mouse capture");
            }

            अगर (तथ्य->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                तथ्य->videodata->global_mouse_changed = true;
            }
        }
    } अन्यथा अगर (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } अन्यथा {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    वापस true;
}

अटल SDL_MouseButtonFlags X11_GetGlobalMouseState(भग्न *x, भग्न *y)
{
    SDL_Video_तथ्य *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    पूर्णांक i;

    // !!! FIXME: should we XSync() here first?

    अगर (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    अगर (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(शून्य);
        अगर (displays) {
            क्रम (i = 0; displays[i]; ++i) {
                SDL_Display_तथ्य *तथ्य = SDL_Get_Display_Driver_तथ्य(displays[i]);
                अगर (तथ्य) {
                    Window मूल, child;
                    पूर्णांक rootx, rooty, winx, winy;
                    अचिन्हित पूर्णांक mask;
                    अगर (X11_XQueryPointer(display, मूल_Window(display, तथ्य->screen), &मूल, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes मूल_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(शून्य, शून्य) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, मूल, &मूल_attrs);
                        videodata->global_mouse_position.x = मूल_attrs.x + rootx;
                        videodata->global_mouse_position.y = मूल_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        अवरोध;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (भग्न)videodata->global_mouse_position.x;
    *y = (भग्न)videodata->global_mouse_position.y;
    वापस videodata->global_mouse_buttons;
}

व्योम X11_InitMouse(SDL_VideoDevice *_this)
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

    SDL_Hit_Test_परिणाम r = SDL_HITTEST_NORMAL;
    जबतक (r <= SDL_HITTEST_RESIZE_बायाँ) {
        चयन (r) {
        हाल SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); अवरोध;
        हाल SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); अवरोध;
        हाल SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); अवरोध;
        हाल SDL_HITTEST_RESIZE_शीर्ष: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); अवरोध;
        हाल SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); अवरोध;
        हाल SDL_HITTEST_RESIZE_दायाँ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); अवरोध;
        हाल SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); अवरोध;
        हाल SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); अवरोध;
        हाल SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); अवरोध;
        हाल SDL_HITTEST_RESIZE_बायाँ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); अवरोध;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

व्योम X11_QuitMouse(SDL_VideoDevice *_this)
{
    क्रम (पूर्णांक i = 0; i < SDL_arraysize(sys_cursors); i++) {
        अगर (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = शून्य;
        }
    }

    X11_DestroyEmptyCursor();
}

व्योम X11_SetHitTestCursor(SDL_Hit_Test_परिणाम rc)
{
    अगर (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } अन्यथा {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
