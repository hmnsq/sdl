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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

#अन्तर्भाव <X11/cursorfont.h>
#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11mouse.h"
#अन्तर्भाव "SDL_x11xinput2.h"
#अन्तर्भाव "SDL_x11xtest.h"
#अन्तर्भाव "../SDL_video_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"

संरचना SDL_Cursor_दत्त
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
स्थिर Cursor x11_रिक्तानि_cursor = None;
स्थिर bool x11_cursor_visible = true;

स्थिर SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_वामः + 1];

स्थिर Display *GetDisplay(शून्य)
{
    प्रत्यागम SDL_GetVideoDevice()->आन्तरिकम्->display;
}

स्थिर Cursor X11_Create_रिक्तानि_Cursor(शून्य)
{
    यदि (x11_रिक्तानि_cursor == None) {
        Display *display = GetDisplay();
        वर्ण दत्त[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(दत्त);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreate_Bitmap_From_दत्त(display, Default_मूलम्_गवाक्षः(display),
                                           दत्त, 1, 1);
        यदि (pixmap) {
            x11_रिक्तानि_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    प्रत्यागम x11_रिक्तानि_cursor;
}

स्थिर शून्य X11_Destroy_रिक्तानि_Cursor(शून्य)
{
    यदि (x11_रिक्तानि_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_रिक्तानि_cursor);
        x11_रिक्तानि_cursor = None;
    }
}

स्थिर SDL_Cursor *X11_Create_Cursor_And_दत्त(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, परिमाण(*cursor));
    यदि (cursor) {
        SDL_Cursor_दत्त *दत्त = (SDL_Cursor_दत्त *)SDL_calloc(1, परिमाण(*दत्त));
        यदि (!दत्त) {
            SDL_free(cursor);
            प्रत्यागम रिक्त;
        }
        दत्त->cursor = x11_cursor;
        cursor->आन्तरिकम् = दत्त;
    }
    प्रत्यागम cursor;
}

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XCURSOR
स्थिर XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    यदि (!image) {
        SDL_बहिर्गमनम्_सम्बन्धि_स्मृतिः();
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
        cursor = X11_Xcursor_Image_आरोपय_Cursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    प्रत्यागम cursor;
}

स्थिर Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *चौकटाः, पूर्णाङ्क अङ्कः_चौकटाः, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(अङ्कः_चौकटाः);
    यदि (!images) {
        SDL_बहिर्गमनम्_सम्बन्धि_स्मृतिः();
        प्रत्यागम None;
    }

    प्रति (पूर्णाङ्क i = 0; i < अङ्कः_चौकटाः; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(चौकटाः[i].surface, hot_x, hot_y, चौकटाः[i].duration);
        यदि (!image) {
            गच्छ cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_Xcursor_Images_आरोपय_Cursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    प्रत्यागम cursor;
}
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XCURSOR

स्थिर Cursor X11_CreatePixmapCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *दत्त_द्वयङ्काः, *आवरणम्_द्वयङ्काः;
    Pixmap दत्त_pixmap, आवरणम्_pixmap;
    पूर्णाङ्क x, y;
    अचिह्नित पूर्णाङ्क rfg, gfg, bfg, rbg, gbg, bbg, fg_द्वयङ्काः, bg_द्वयङ्काः;
    size_t विस्तारः_अष्टकानि = ((surface->w + 7) & ~((size_t)7)) / 8;

    दत्त_द्वयङ्काः = SDL_calloc(1, surface->h * विस्तारः_अष्टकानि);
    यदि (!दत्त_द्वयङ्काः) {
        प्रत्यागम None;
    }

    आवरणम्_द्वयङ्काः = SDL_calloc(1, surface->h * विस्तारः_अष्टकानि);
    यदि (!आवरणम्_द्वयङ्काः) {
        SDL_free(दत्त_द्वयङ्काः);
        प्रत्यागम None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fg_द्वयङ्काः = bg_द्वयङ्काः = 0;
    प्रति (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        प्रति (x = 0; x < surface->w; ++x) {
            पूर्णाङ्क alpha = (*ptr >> 24) & 0xff;
            पूर्णाङ्क red = (*ptr >> 16) & 0xff;
            पूर्णाङ्क green = (*ptr >> 8) & 0xff;
            पूर्णाङ्क blue = (*ptr >> 0) & 0xff;
            यदि (alpha > 25) {
                आवरणम्_द्वयङ्काः[y * विस्तारः_अष्टकानि + x / 8] |= (0x01 << (x % 8));

                यदि ((red + green + blue) > 0x40) {
                    fg_द्वयङ्काः++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    दत्त_द्वयङ्काः[y * विस्तारः_अष्टकानि + x / 8] |= (0x01 << (x % 8));
                } अन्यथा {
                    bg_द्वयङ्काः++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    यदि (fg_द्वयङ्काः) {
        fg.red = rfg * 257 / fg_द्वयङ्काः;
        fg.green = gfg * 257 / fg_द्वयङ्काः;
        fg.blue = bfg * 257 / fg_द्वयङ्काः;
    } अन्यथा {
        fg.red = fg.green = fg.blue = 0;
    }

    यदि (bg_द्वयङ्काः) {
        bg.red = rbg * 257 / bg_द्वयङ्काः;
        bg.green = gbg * 257 / bg_द्वयङ्काः;
        bg.blue = bbg * 257 / bg_द्वयङ्काः;
    } अन्यथा {
        bg.red = bg.green = bg.blue = 0;
    }

    दत्त_pixmap = X11_XCreate_Bitmap_From_दत्त(display, Default_मूलम्_गवाक्षः(display),
                                            (वर्ण *)दत्त_द्वयङ्काः,
                                            surface->w, surface->h);
    आवरणम्_pixmap = X11_XCreate_Bitmap_From_दत्त(display, Default_मूलम्_गवाक्षः(display),
                                            (वर्ण *)आवरणम्_द्वयङ्काः,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, दत्त_pixmap, आवरणम्_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, दत्त_pixmap);
    X11_XFreePixmap(display, आवरणम्_pixmap);
    SDL_free(दत्त_द्वयङ्काः);
    SDL_free(आवरणम्_द्वयङ्काः);

    प्रत्यागम cursor;
}

स्थिर SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    Cursor x11_cursor = None;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XCURSOR
    यदि (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#यदि_अन्तः
    यदि (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    प्रत्यागम X11_Create_Cursor_And_दत्त(x11_cursor);
}

स्थिर SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *चौकटाः, पूर्णाङ्क अङ्कः_चौकटाः, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    Cursor x11_cursor = None;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XCURSOR
    यदि (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(चौकटाः, अङ्कः_चौकटाः, hot_x, hot_y);
    }
#यदि_अन्तः
    यदि (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(चौकटाः[0].surface, hot_x, hot_y);
    }

    प्रत्यागम X11_Create_Cursor_And_दत्त(x11_cursor);
}

स्थिर अचिह्नित पूर्णाङ्क GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    विकल्प (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        पक्ष SDL_SYSTEM_CURSOR_DEFAULT: प्रत्यागम XC_वामः_ptr;
        पक्ष SDL_SYSTEM_CURSOR_TEXT: प्रत्यागम XC_xterm;
        पक्ष SDL_SYSTEM_CURSOR_WAIT: प्रत्यागम XC_watch;
        पक्ष SDL_SYSTEM_CURSOR_CROSSHAIR: प्रत्यागम XC_tcross;
        पक्ष SDL_SYSTEM_CURSOR_प्रगतिः: प्रत्यागम XC_watch;
        पक्ष SDL_SYSTEM_CURSOR_NWSE_RESIZE: प्रत्यागम XC_शिखरम्_वामः_corner;
        पक्ष SDL_SYSTEM_CURSOR_NESW_RESIZE: प्रत्यागम XC_शिखरम्_दक्षिणः_corner;
        पक्ष SDL_SYSTEM_CURSOR_EW_RESIZE: प्रत्यागम XC_sb_h_double_arrow;
        पक्ष SDL_SYSTEM_CURSOR_NS_RESIZE: प्रत्यागम XC_sb_v_double_arrow;
        पक्ष SDL_SYSTEM_CURSOR_MOVE: प्रत्यागम XC_fleur;
        पक्ष SDL_SYSTEM_CURSOR_NOT_ALLOWED: प्रत्यागम XC_pirate;
        पक्ष SDL_SYSTEM_CURSOR_POINTER: प्रत्यागम XC_hand2;
        पक्ष SDL_SYSTEM_CURSOR_NW_RESIZE: प्रत्यागम XC_शिखरम्_वामः_corner;
        पक्ष SDL_SYSTEM_CURSOR_N_RESIZE: प्रत्यागम XC_शिखरम्_side;
        पक्ष SDL_SYSTEM_CURSOR_NE_RESIZE: प्रत्यागम XC_शिखरम्_दक्षिणः_corner;
        पक्ष SDL_SYSTEM_CURSOR_E_RESIZE: प्रत्यागम XC_दक्षिणः_side;
        पक्ष SDL_SYSTEM_CURSOR_SE_RESIZE: प्रत्यागम XC_bottom_दक्षिणः_corner;
        पक्ष SDL_SYSTEM_CURSOR_S_RESIZE: प्रत्यागम XC_bottom_side;
        पक्ष SDL_SYSTEM_CURSOR_SW_RESIZE: प्रत्यागम XC_bottom_वामः_corner;
        पक्ष SDL_SYSTEM_CURSOR_W_RESIZE: प्रत्यागम XC_वामः_side;
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
        पक्ष SDL_SYSTEM_CURSOR_ZOOM_अन्तर्: प्रत्यागम XC_hand2;
        पक्ष SDL_SYSTEM_CURSOR_ZOOM_बहिर्गमनम्: प्रत्यागम XC_hand2;
        पक्ष SDL_SYSTEM_CURSOR_गणनम्: भङ्ग;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    प्रत्यागम 0;
}

स्थिर SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = रिक्त;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XCURSOR
    यदि (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_Xcursor_Library_आरोपय_Cursor(dpy, SDL_GetCSSCursorName(id, रिक्त));
    }
#यदि_अन्तः

    यदि (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    यदि (x11_cursor != None) {
        cursor = X11_Create_Cursor_And_दत्त(x11_cursor);
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
    Cursor x11_cursor = cursor->आन्तरिकम्->cursor;

    यदि (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->आन्तरिकम्);
    SDL_free(cursor);
}

स्थिर bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    यदि (cursor) {
        x11_cursor = cursor->आन्तरिकम्->cursor;
    } अन्यथा {
        x11_cursor = X11_Create_रिक्तानि_Cursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_गवाक्षः *गवाक्षः;

        x11_cursor_visible = !!cursor;

        प्रति (गवाक्षः = video->windows; गवाक्षः; गवाक्षः = गवाक्षः->अग्र) {
            SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
            यदि (दत्त) {
                यदि (x11_cursor != None) {
                    X11_XDefineCursor(display, दत्त->xwindow, x11_cursor);
                } अन्यथा {
                    X11_XUndefineCursor(display, दत्त->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    प्रत्यागम true;
}

स्थिर शून्य X11_Warp_Mouse_आन्तरिकम्(गवाक्षः_2 xwindow, भिन्न x, भिन्न y)
{
    SDL_Video_दत्त *videodata = SDL_GetVideoDevice()->आन्तरिकम्;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    यदि (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    यदि (warp_hack) {
        X11_ShowCursor(रिक्त);
    }
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2
    पूर्णाङ्क deviceid = 0;
    यदि (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        यदि (Screen_गणनम्(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    यदि (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } अन्यथा
#यदि_अन्तः
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (पूर्णाङ्क)x, (पूर्णाङ्क)y);
    }

    यदि (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_परिवर्तितम् = true;
}

स्थिर bool X11_WarpMouse(SDL_गवाक्षः *गवाक्षः, भिन्न x, भिन्न y)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

    यदि (X11_WarpMouseXTest(SDL_GetVideoDevice(), गवाक्षः, x, y)) {
        प्रत्यागम true;
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    यदि (दत्त->pointer_barrier_सक्रिय == false) {
        X11_Warp_Mouse_आन्तरिकम्(दत्त->xwindow, x, y);
    }
#अन्यथा
    X11_Warp_Mouse_आन्तरिकम्(दत्त->xwindow, x, y);
#यदि_अन्तः
    प्रत्यागम true;
}

स्थिर bool X11_WarpMouseGlobal(भिन्न x, भिन्न y)
{
    यदि (X11_WarpMouseXTest(SDL_GetVideoDevice(), रिक्त, x, y)) {
        प्रत्यागम true;
    }

    X11_Warp_Mouse_आन्तरिकम्(Default_मूलम्_गवाक्षः(GetDisplay()), x, y);
    प्रत्यागम true;
}

स्थिर bool X11_समुच्चयः_Relative_Mouse_बहुलकम्(bool enabled)
{
    यदि (!X11_Xinput2IsInitialized()) {
        प्रत्यागम SDL_Unsupported();
    }
    प्रत्यागम true;
}

स्थिर bool X11_CaptureMouse(SDL_गवाक्षः *गवाक्षः)
{
    Display *display = GetDisplay();
    SDL_गवाक्षः *mouse_focus = SDL_GetMouseFocus();

    यदि (गवाक्षः) {
        SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        यदि (!दत्त->xinput2_mouse_enabled || दत्त->mouse_grabbed) {
            ध्रुव अचिह्नित पूर्णाङ्क आवरणम् = Button_Press_आवरणम् | Button_Release_आवरणम् | Pointer_Motion_आवरणम् | Focus_Change_आवरणम्;
            गवाक्षः_2 confined = (दत्त->mouse_grabbed ? दत्त->xwindow : None);
            ध्रुव पूर्णाङ्क rc = X11_XGrabPointer(display, दत्त->xwindow, False,
                                            आवरणम्, Grab_बहुलकम्_Async, Grab_बहुलकम्_Async,
                                            confined, None, CurrentTime);
            यदि (rc != GrabSuccess) {
                प्रत्यागम SDL_समुच्चयः_Error("X server refused mouse capture");
            }

            यदि (दत्त->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                दत्त->videodata->global_mouse_परिवर्तितम् = true;
            }
        }
    } अन्यथा यदि (mouse_focus) {
        SDL_Update_गवाक्षः_Grab(mouse_focus);
    } अन्यथा {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    प्रत्यागम true;
}

स्थिर SDL_MouseButtonFlags X11_GetGlobalMouseState(भिन्न *x, भिन्न *y)
{
    SDL_Video_दत्त *videodata = SDL_GetVideoDevice()->आन्तरिकम्;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    पूर्णाङ्क i;

    // !!! FIXME: should we XSync() here first?

    यदि (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_परिवर्तितम् = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    यदि (videodata->global_mouse_परिवर्तितम्) {
        displays = SDL_GetDisplays(रिक्त);
        यदि (displays) {
            प्रति (i = 0; displays[i]; ++i) {
                SDL_Display_दत्त *दत्त = SDL_Get_Display_Driver_दत्त(displays[i]);
                यदि (दत्त) {
                    गवाक्षः_2 मूलम्, child;
                    पूर्णाङ्क rootx, rooty, winx, winy;
                    अचिह्नित पूर्णाङ्क आवरणम्;
                    यदि (X11_XQueryPointer(display, मूलम्_गवाक्षः(display, दत्त->screen), &मूलम्, &child, &rootx, &rooty, &winx, &winy, &आवरणम्)) {
                        XWindow_गुणाः मूलम्_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (आवरणम् & Button1_आवरणम्) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (आवरणम् & Button2_आवरणम्) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (आवरणम् & Button3_आवरणम्) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(रिक्त, रिक्त) & (SDL_BUTTON_X1_आवरणम् | SDL_BUTTON_X2_आवरणम्));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGet_गवाक्षः_गुणाः(display, मूलम्, &मूलम्_attrs);
                        videodata->global_mouse_position.x = मूलम्_attrs.x + rootx;
                        videodata->global_mouse_position.y = मूलम्_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_परिवर्तितम् = false;
                        भङ्ग;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_परिवर्तितम्); // The pointer wasn't on any X11 screen?!

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
    mouse->समुच्चयः_Relative_Mouse_बहुलकम् = X11_समुच्चयः_Relative_Mouse_बहुलकम्;
    mouse->CaptureMouse = X11_CaptureMouse;
    mouse->GetGlobalMouseState = X11_GetGlobalMouseState;

    SDL_लब्धम्_Test_परिणाम r = SDL_HITTEST_प्रसामान्यम्;
    यावत् (r <= SDL_HITTEST_RESIZE_वामः) {
        विकल्प (r) {
        पक्ष SDL_HITTEST_प्रसामान्यम्: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); भङ्ग;
        पक्ष SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_शिखरम्: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_दक्षिणः: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); भङ्ग;
        पक्ष SDL_HITTEST_RESIZE_वामः: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); भङ्ग;
        }
        r++;
    }

    SDL_समुच्चयः_Default_Cursor(X11_CreateDefaultCursor());
}

शून्य X11_QuitMouse(SDL_VideoDevice *_this)
{
    प्रति (पूर्णाङ्क i = 0; i < SDL_arraysize(sys_cursors); i++) {
        यदि (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = रिक्त;
        }
    }

    X11_Destroy_रिक्तानि_Cursor();
}

शून्य X11_समुच्चयः_लब्धम्_Test_Cursor(SDL_लब्धम्_Test_परिणाम rc)
{
    यदि (rc == SDL_HITTEST_प्रसामान्यम् || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } अन्यथा {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
