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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ <X11/cursorfont.h>
#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11mouse.h"
#అన్తర్భావ "SDL_x11xinput2.h"
#అన్తర్భావ "SDL_x11xtest.h"
#అన్తర్భావ "../SDL_video_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"

నిర్మాణం SDL_Cursor_దత్తాంశం
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
స్థిర Cursor x11_ఖాళీలు_cursor = None;
స్థిర bool x11_cursor_visible = true;

స్థిర SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_ఎడమ + 1];

స్థిర Display *GetDisplay(శూన్య)
{
    తిరిగి SDL_GetVideoDevice()->అంతర్గత->display;
}

స్థిర Cursor X11_Create_ఖాళీలు_Cursor(శూన్య)
{
    ఒకవేళ (x11_ఖాళీలు_cursor == None) {
        Display *display = GetDisplay();
        అక్షరం దత్తాంశం[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(దత్తాంశం);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreate_Bitmap_From_దత్తాంశం(display, Default_మూలం_కిటికీ(display),
                                           దత్తాంశం, 1, 1);
        ఒకవేళ (pixmap) {
            x11_ఖాళీలు_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    తిరిగి x11_ఖాళీలు_cursor;
}

స్థిర శూన్య X11_Destroy_ఖాళీలు_Cursor(శూన్య)
{
    ఒకవేళ (x11_ఖాళీలు_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_ఖాళీలు_cursor);
        x11_ఖాళీలు_cursor = None;
    }
}

స్థిర SDL_Cursor *X11_Create_Cursor_And_దత్తాంశం(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, పరిమాణం(*cursor));
    ఒకవేళ (cursor) {
        SDL_Cursor_దత్తాంశం *దత్తాంశం = (SDL_Cursor_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం));
        ఒకవేళ (!దత్తాంశం) {
            SDL_free(cursor);
            తిరిగి ఖాళీ;
        }
        దత్తాంశం->cursor = x11_cursor;
        cursor->అంతర్గత = దత్తాంశం;
    }
    తిరిగి cursor;
}

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XCURSOR
స్థిర XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    ఒకవేళ (!image) {
        SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
        తిరిగి ఖాళీ;
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

    తిరిగి image;
}

స్థిర Cursor X11_CreateXCursorCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    ఒకవేళ (image) {
        cursor = X11_Xcursor_Image_ఎక్కించు_Cursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    తిరిగి cursor;
}

స్థిర Cursor X11_CreateAnimatedXCursorCursor(SDL_Cursor_చట్రం_Info *చట్రాలు, పూర్ణాంకం అంకె_చట్రాలు, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(అంకె_చట్రాలు);
    ఒకవేళ (!images) {
        SDL_బహిర్గతం_యొక్క_జ్ఞాపకం();
        తిరిగి None;
    }

    కొరకు (పూర్ణాంకం i = 0; i < అంకె_చట్రాలు; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(చట్రాలు[i].surface, hot_x, hot_y, చట్రాలు[i].duration);
        ఒకవేళ (!image) {
            వెళ్ళు cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_Xcursor_Images_ఎక్కించు_Cursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    తిరిగి cursor;
}
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XCURSOR

స్థిర Cursor X11_CreatePixmapCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *దత్తాంశం_బిట్లు, *ముసుగు_బిట్లు;
    Pixmap దత్తాంశం_pixmap, ముసుగు_pixmap;
    పూర్ణాంకం x, y;
    గుర్తులేని పూర్ణాంకం rfg, gfg, bfg, rbg, gbg, bbg, fg_బిట్లు, bg_బిట్లు;
    size_t వెడల్పు_బైట్లు = ((surface->w + 7) & ~((size_t)7)) / 8;

    దత్తాంశం_బిట్లు = SDL_calloc(1, surface->h * వెడల్పు_బైట్లు);
    ఒకవేళ (!దత్తాంశం_బిట్లు) {
        తిరిగి None;
    }

    ముసుగు_బిట్లు = SDL_calloc(1, surface->h * వెడల్పు_బైట్లు);
    ఒకవేళ (!ముసుగు_బిట్లు) {
        SDL_free(దత్తాంశం_బిట్లు);
        తిరిగి None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fg_బిట్లు = bg_బిట్లు = 0;
    కొరకు (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        కొరకు (x = 0; x < surface->w; ++x) {
            పూర్ణాంకం alpha = (*ptr >> 24) & 0xff;
            పూర్ణాంకం red = (*ptr >> 16) & 0xff;
            పూర్ణాంకం green = (*ptr >> 8) & 0xff;
            పూర్ణాంకం blue = (*ptr >> 0) & 0xff;
            ఒకవేళ (alpha > 25) {
                ముసుగు_బిట్లు[y * వెడల్పు_బైట్లు + x / 8] |= (0x01 << (x % 8));

                ఒకవేళ ((red + green + blue) > 0x40) {
                    fg_బిట్లు++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    దత్తాంశం_బిట్లు[y * వెడల్పు_బైట్లు + x / 8] |= (0x01 << (x % 8));
                } లేకపోతే {
                    bg_బిట్లు++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    ఒకవేళ (fg_బిట్లు) {
        fg.red = rfg * 257 / fg_బిట్లు;
        fg.green = gfg * 257 / fg_బిట్లు;
        fg.blue = bfg * 257 / fg_బిట్లు;
    } లేకపోతే {
        fg.red = fg.green = fg.blue = 0;
    }

    ఒకవేళ (bg_బిట్లు) {
        bg.red = rbg * 257 / bg_బిట్లు;
        bg.green = gbg * 257 / bg_బిట్లు;
        bg.blue = bbg * 257 / bg_బిట్లు;
    } లేకపోతే {
        bg.red = bg.green = bg.blue = 0;
    }

    దత్తాంశం_pixmap = X11_XCreate_Bitmap_From_దత్తాంశం(display, Default_మూలం_కిటికీ(display),
                                            (అక్షరం *)దత్తాంశం_బిట్లు,
                                            surface->w, surface->h);
    ముసుగు_pixmap = X11_XCreate_Bitmap_From_దత్తాంశం(display, Default_మూలం_కిటికీ(display),
                                            (అక్షరం *)ముసుగు_బిట్లు,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, దత్తాంశం_pixmap, ముసుగు_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, దత్తాంశం_pixmap);
    X11_XFreePixmap(display, ముసుగు_pixmap);
    SDL_free(దత్తాంశం_బిట్లు);
    SDL_free(ముసుగు_బిట్లు);

    తిరిగి cursor;
}

స్థిర SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    Cursor x11_cursor = None;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XCURSOR
    ఒకవేళ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#అయితే_ముగింపు
    ఒకవేళ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    తిరిగి X11_Create_Cursor_And_దత్తాంశం(x11_cursor);
}

స్థిర SDL_Cursor *X11_CreateAnimatedCursor(SDL_Cursor_చట్రం_Info *చట్రాలు, పూర్ణాంకం అంకె_చట్రాలు, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    Cursor x11_cursor = None;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XCURSOR
    ఒకవేళ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(చట్రాలు, అంకె_చట్రాలు, hot_x, hot_y);
    }
#అయితే_ముగింపు
    ఒకవేళ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(చట్రాలు[0].surface, hot_x, hot_y);
    }

    తిరిగి X11_Create_Cursor_And_దత్తాంశం(x11_cursor);
}

స్థిర గుర్తులేని పూర్ణాంకం GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    ఎంపిక (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        స్థితి SDL_SYSTEM_CURSOR_DEFAULT: తిరిగి XC_ఎడమ_ptr;
        స్థితి SDL_SYSTEM_CURSOR_పాఠ్యం: తిరిగి XC_xterm;
        స్థితి SDL_SYSTEM_CURSOR_WAIT: తిరిగి XC_watch;
        స్థితి SDL_SYSTEM_CURSOR_CROSSHAIR: తిరిగి XC_tcross;
        స్థితి SDL_SYSTEM_CURSOR_పురోగతి: తిరిగి XC_watch;
        స్థితి SDL_SYSTEM_CURSOR_NWSE_RESIZE: తిరిగి XC_శిఖరం_ఎడమ_మూల;
        స్థితి SDL_SYSTEM_CURSOR_NESW_RESIZE: తిరిగి XC_శిఖరం_కుడి_మూల;
        స్థితి SDL_SYSTEM_CURSOR_EW_RESIZE: తిరిగి XC_sb_h_double_arrow;
        స్థితి SDL_SYSTEM_CURSOR_NS_RESIZE: తిరిగి XC_sb_v_double_arrow;
        స్థితి SDL_SYSTEM_CURSOR_MOVE: తిరిగి XC_fleur;
        స్థితి SDL_SYSTEM_CURSOR_NOT_ALLOWED: తిరిగి XC_pirate;
        స్థితి SDL_SYSTEM_CURSOR_సూచిక: తిరిగి XC_hand2;
        స్థితి SDL_SYSTEM_CURSOR_NW_RESIZE: తిరిగి XC_శిఖరం_ఎడమ_మూల;
        స్థితి SDL_SYSTEM_CURSOR_N_RESIZE: తిరిగి XC_శిఖరం_side;
        స్థితి SDL_SYSTEM_CURSOR_NE_RESIZE: తిరిగి XC_శిఖరం_కుడి_మూల;
        స్థితి SDL_SYSTEM_CURSOR_E_RESIZE: తిరిగి XC_కుడి_side;
        స్థితి SDL_SYSTEM_CURSOR_SE_RESIZE: తిరిగి XC_bottom_కుడి_మూల;
        స్థితి SDL_SYSTEM_CURSOR_S_RESIZE: తిరిగి XC_bottom_side;
        స్థితి SDL_SYSTEM_CURSOR_SW_RESIZE: తిరిగి XC_bottom_ఎడమ_మూల;
        స్థితి SDL_SYSTEM_CURSOR_W_RESIZE: తిరిగి XC_ఎడమ_side;
        స్థితి SDL_SYSTEM_CURSOR_CONTEXT_MENU: తిరిగి XC_hand2;
        స్థితి SDL_SYSTEM_CURSOR_HELP: తిరిగి XC_question_arrow;
        స్థితి SDL_SYSTEM_CURSOR_CELL: తిరిగి XC_cross;
        స్థితి SDL_SYSTEM_CURSOR_VERTICAL_పాఠ్యం: తిరిగి XC_xterm;
        స్థితి SDL_SYSTEM_CURSOR_ALIAS: తిరిగి XC_hand2;
        స్థితి SDL_SYSTEM_CURSOR_COPY: తిరిగి XC_hand2;
        స్థితి SDL_SYSTEM_CURSOR_NO_DROP: తిరిగి XC_pirate;
        స్థితి SDL_SYSTEM_CURSOR_GRAB: తిరిగి XC_hand2;
        స్థితి SDL_SYSTEM_CURSOR_GRABBING: తిరిగి XC_hand2;
        స్థితి SDL_SYSTEM_CURSOR_నిలువు_RESIZE: తిరిగి XC_sb_h_double_arrow;
        స్థితి SDL_SYSTEM_CURSOR_అడ్డువరుస_RESIZE: తిరిగి XC_sb_v_double_arrow;
        స్థితి SDL_SYSTEM_CURSOR_ALL_SCROLL: తిరిగి XC_fleur;
        స్థితి SDL_SYSTEM_CURSOR_ZOOM_లోపల: తిరిగి XC_hand2;
        స్థితి SDL_SYSTEM_CURSOR_ZOOM_బహిర్గతం: తిరిగి XC_hand2;
        స్థితి SDL_SYSTEM_CURSOR_లెక్క: ఆపు;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    తిరిగి 0;
}

స్థిర SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = ఖాళీ;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XCURSOR
    ఒకవేళ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_Xcursor_Library_ఎక్కించు_Cursor(dpy, SDL_GetCSSCursorName(id, ఖాళీ));
    }
#అయితే_ముగింపు

    ఒకవేళ (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    ఒకవేళ (x11_cursor != None) {
        cursor = X11_Create_Cursor_And_దత్తాంశం(x11_cursor);
    }

    తిరిగి cursor;
}

స్థిర SDL_Cursor *X11_CreateDefaultCursor(శూన్య)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    తిరిగి X11_CreateSystemCursor(id);
}

స్థిర శూన్య X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->అంతర్గత->cursor;

    ఒకవేళ (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->అంతర్గత);
    SDL_free(cursor);
}

స్థిర bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    ఒకవేళ (cursor) {
        x11_cursor = cursor->అంతర్గత->cursor;
    } లేకపోతే {
        x11_cursor = X11_Create_ఖాళీలు_Cursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_కిటికీ *కిటికీ;

        x11_cursor_visible = !!cursor;

        కొరకు (కిటికీ = video->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
            SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
            ఒకవేళ (దత్తాంశం) {
                ఒకవేళ (x11_cursor != None) {
                    X11_XDefineCursor(display, దత్తాంశం->xwindow, x11_cursor);
                } లేకపోతే {
                    X11_XUndefineCursor(display, దత్తాంశం->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    తిరిగి true;
}

స్థిర శూన్య X11_Warp_Mouse_అంతర్గత(కిటికీ_2 xwindow, దశాంశం x, దశాంశం y)
{
    SDL_Video_దత్తాంశం *videodata = SDL_GetVideoDevice()->అంతర్గత;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    ఒకవేళ (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    ఒకవేళ (warp_hack) {
        X11_ShowCursor(ఖాళీ);
    }
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2
    పూర్ణాంకం deviceid = 0;
    ఒకవేళ (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        ఒకవేళ (Screen_లెక్క(display) == 1) {
            X11_XIGet_Client_సూచిక(display, None, &deviceid);
        }
    }
    ఒకవేళ (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarp_సూచిక(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } లేకపోతే
#అయితే_ముగింపు
    {
        X11_XWarp_సూచిక(display, None, xwindow, 0, 0, 0, 0, (పూర్ణాంకం)x, (పూర్ణాంకం)y);
    }

    ఒకవేళ (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_మారింది = true;
}

స్థిర bool X11_WarpMouse(SDL_కిటికీ *కిటికీ, దశాంశం x, దశాంశం y)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

    ఒకవేళ (X11_WarpMouseXTest(SDL_GetVideoDevice(), కిటికీ, x, y)) {
        తిరిగి true;
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    ఒకవేళ (దత్తాంశం->సూచిక_barrier_చురుకైన == false) {
        X11_Warp_Mouse_అంతర్గత(దత్తాంశం->xwindow, x, y);
    }
#లేకపోతే
    X11_Warp_Mouse_అంతర్గత(దత్తాంశం->xwindow, x, y);
#అయితే_ముగింపు
    తిరిగి true;
}

స్థిర bool X11_WarpMouseGlobal(దశాంశం x, దశాంశం y)
{
    ఒకవేళ (X11_WarpMouseXTest(SDL_GetVideoDevice(), ఖాళీ, x, y)) {
        తిరిగి true;
    }

    X11_Warp_Mouse_అంతర్గత(Default_మూలం_కిటికీ(GetDisplay()), x, y);
    తిరిగి true;
}

స్థిర bool X11_సమితి_Relative_Mouse_బహుళకం(bool enabled)
{
    ఒకవేళ (!X11_Xinput2IsInitialized()) {
        తిరిగి SDL_Unsupported();
    }
    తిరిగి true;
}

స్థిర bool X11_CaptureMouse(SDL_కిటికీ *కిటికీ)
{
    Display *display = GetDisplay();
    SDL_కిటికీ *mouse_focus = SDL_GetMouseFocus();

    ఒకవేళ (కిటికీ) {
        SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        ఒకవేళ (!దత్తాంశం->xinput2_mouse_enabled || దత్తాంశం->mouse_grabbed) {
            స్థిరరాశి గుర్తులేని పూర్ణాంకం ముసుగు = Button_Press_ముసుగు | Button_Release_ముసుగు | సూచిక_Motion_ముసుగు | Focus_Change_ముసుగు;
            కిటికీ_2 confined = (దత్తాంశం->mouse_grabbed ? దత్తాంశం->xwindow : None);
            స్థిరరాశి పూర్ణాంకం rc = X11_XGrab_సూచిక(display, దత్తాంశం->xwindow, False,
                                            ముసుగు, Grab_బహుళకం_Async, Grab_బహుళకం_Async,
                                            confined, None, Current_సమయం);
            ఒకవేళ (rc != GrabSuccess) {
                తిరిగి SDL_సమితి_Error("X server refused mouse capture");
            }

            ఒకవేళ (దత్తాంశం->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                దత్తాంశం->videodata->global_mouse_మారింది = true;
            }
        }
    } లేకపోతే ఒకవేళ (mouse_focus) {
        SDL_Update_కిటికీ_Grab(mouse_focus);
    } లేకపోతే {
        X11_XUngrab_సూచిక(display, Current_సమయం);
    }

    X11_XSync(display, False);

    తిరిగి true;
}

స్థిర SDL_MouseButtonFlags X11_GetGlobalMouseState(దశాంశం *x, దశాంశం *y)
{
    SDL_Video_దత్తాంశం *videodata = SDL_GetVideoDevice()->అంతర్గత;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    పూర్ణాంకం i;

    // !!! FIXME: should we XSync() here first?

    ఒకవేళ (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_మారింది = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    ఒకవేళ (videodata->global_mouse_మారింది) {
        displays = SDL_GetDisplays(ఖాళీ);
        ఒకవేళ (displays) {
            కొరకు (i = 0; displays[i]; ++i) {
                SDL_Display_దత్తాంశం *దత్తాంశం = SDL_Get_Display_Driver_దత్తాంశం(displays[i]);
                ఒకవేళ (దత్తాంశం) {
                    కిటికీ_2 మూలం, బిడ్డ;
                    పూర్ణాంకం rootx, rooty, winx, winy;
                    గుర్తులేని పూర్ణాంకం ముసుగు;
                    ఒకవేళ (X11_XQuery_సూచిక(display, మూలం_కిటికీ(display, దత్తాంశం->screen), &మూలం, &బిడ్డ, &rootx, &rooty, &winx, &winy, &ముసుగు)) {
                        XWindow_లక్షణాలు మూలం_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (ముసుగు & Button1_ముసుగు) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (ముసుగు & Button2_ముసుగు) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (ముసుగు & Button3_ముసుగు) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(ఖాళీ, ఖాళీ) & (SDL_BUTTON_X1_ముసుగు | SDL_BUTTON_X2_ముసుగు));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGet_కిటికీ_లక్షణాలు(display, మూలం, &మూలం_attrs);
                        videodata->global_mouse_position.x = మూలం_attrs.x + rootx;
                        videodata->global_mouse_position.y = మూలం_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_మారింది = false;
                        ఆపు;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_మారింది); // The pointer wasn't on any X11 screen?!

    *x = (దశాంశం)videodata->global_mouse_position.x;
    *y = (దశాంశం)videodata->global_mouse_position.y;
    తిరిగి videodata->global_mouse_buttons;
}

శూన్య X11_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = X11_CreateCursor;
    mouse->CreateAnimatedCursor = X11_CreateAnimatedCursor;
    mouse->CreateSystemCursor = X11_CreateSystemCursor;
    mouse->ShowCursor = X11_ShowCursor;
    mouse->FreeCursor = X11_FreeCursor;
    mouse->WarpMouse = X11_WarpMouse;
    mouse->WarpMouseGlobal = X11_WarpMouseGlobal;
    mouse->సమితి_Relative_Mouse_బహుళకం = X11_సమితి_Relative_Mouse_బహుళకం;
    mouse->CaptureMouse = X11_CaptureMouse;
    mouse->GetGlobalMouseState = X11_GetGlobalMouseState;

    SDL_తగిలింది_Test_ఫలితం r = SDL_HITTEST_సాధారణ;
    అయితే (r <= SDL_HITTEST_RESIZE_ఎడమ) {
        ఎంపిక (r) {
        స్థితి SDL_HITTEST_సాధారణ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ఆపు;
        స్థితి SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); ఆపు;
        స్థితి SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); ఆపు;
        స్థితి SDL_HITTEST_RESIZE_శిఖరం: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); ఆపు;
        స్థితి SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); ఆపు;
        స్థితి SDL_HITTEST_RESIZE_కుడి: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); ఆపు;
        స్థితి SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); ఆపు;
        స్థితి SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); ఆపు;
        స్థితి SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); ఆపు;
        స్థితి SDL_HITTEST_RESIZE_ఎడమ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); ఆపు;
        }
        r++;
    }

    SDL_సమితి_Default_Cursor(X11_CreateDefaultCursor());
}

శూన్య X11_QuitMouse(SDL_VideoDevice *_this)
{
    కొరకు (పూర్ణాంకం i = 0; i < SDL_arraysize(sys_cursors); i++) {
        ఒకవేళ (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = ఖాళీ;
        }
    }

    X11_Destroy_ఖాళీలు_Cursor();
}

శూన్య X11_సమితి_తగిలింది_Test_Cursor(SDL_తగిలింది_Test_ఫలితం rc)
{
    ఒకవేళ (rc == SDL_HITTEST_సాధారణ || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } లేకపోతే {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
