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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11

#ضمن <X11/cursorfont.h>
#ضمن "SDL_x11video.h"
#ضمن "SDL_x11mouse.h"
#ضمن "SDL_x11xinput2.h"
#ضمن "SDL_x11xtest.h"
#ضمن "../SDL_video_c.h"
#ضمن "../../events/SDL_mouse_c.h"

بنية SDL_Cursor_معلومات
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
ساكن Cursor x11_خالي_جايون_cursor = None;
ساكن bool x11_cursor_visible = true;

ساكن SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_کاٻو + 1];

ساكن Display *GetDisplay(فراغ)
{
    أرجع SDL_GetVideoDevice()->اندروني->display;
}

ساكن Cursor X11_Create_خالي_جايون_Cursor(فراغ)
{
    إذا (x11_خالي_جايون_cursor == None) {
        Display *display = GetDisplay();
        حرف معلومات[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(معلومات);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreate_Bitmap_From_معلومات(display, Default_پاڙ_دري(display),
                                           معلومات, 1, 1);
        إذا (pixmap) {
            x11_خالي_جايون_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    أرجع x11_خالي_جايون_cursor;
}

ساكن فراغ X11_Destroy_خالي_جايون_Cursor(فراغ)
{
    إذا (x11_خالي_جايون_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_خالي_جايون_cursor);
        x11_خالي_جايون_cursor = None;
    }
}

ساكن SDL_Cursor *X11_Create_Cursor_And_معلومات(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (cursor) {
        SDL_Cursor_معلومات *معلومات = (SDL_Cursor_معلومات *)SDL_calloc(1, حجم(*معلومات));
        إذا (!معلومات) {
            SDL_free(cursor);
            أرجع عدم;
        }
        معلومات->cursor = x11_cursor;
        cursor->اندروني = معلومات;
    }
    أرجع cursor;
}

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XCURSOR
ساكن XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, صحيح hot_x, صحيح hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    إذا (!image) {
        SDL_ٻاهريون_جو_يادگيري();
        أرجع عدم;
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

    أرجع image;
}

ساكن Cursor X11_CreateXCursorCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    إذا (image) {
        cursor = X11_Xcursor_Image_ڀريو_Cursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    أرجع cursor;
}

ساكن Cursor X11_CreateAnimatedXCursorCursor(SDL_Cursor_چوکٺو_Info *چوکٺا, صحيح انگ_چوکٺا, صحيح hot_x, صحيح hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(انگ_چوکٺا);
    إذا (!images) {
        SDL_ٻاهريون_جو_يادگيري();
        أرجع None;
    }

    لكل (صحيح i = 0; i < انگ_چوکٺا; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(چوکٺا[i].surface, hot_x, hot_y, چوکٺا[i].duration);
        إذا (!image) {
            اذهب cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_Xcursor_Images_ڀريو_Cursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    أرجع cursor;
}
#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11_XCURSOR

ساكن Cursor X11_CreatePixmapCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *معلومات_بٽ, *نقاب_بٽ;
    Pixmap معلومات_pixmap, نقاب_pixmap;
    صحيح x, y;
    بنانشان صحيح rfg, gfg, bfg, rbg, gbg, bbg, fg_بٽ, bg_بٽ;
    size_t ويڪر_بائيٽون = ((surface->w + 7) & ~((size_t)7)) / 8;

    معلومات_بٽ = SDL_calloc(1, surface->h * ويڪر_بائيٽون);
    إذا (!معلومات_بٽ) {
        أرجع None;
    }

    نقاب_بٽ = SDL_calloc(1, surface->h * ويڪر_بائيٽون);
    إذا (!نقاب_بٽ) {
        SDL_free(معلومات_بٽ);
        أرجع None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fg_بٽ = bg_بٽ = 0;
    لكل (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        لكل (x = 0; x < surface->w; ++x) {
            صحيح alpha = (*ptr >> 24) & 0xff;
            صحيح red = (*ptr >> 16) & 0xff;
            صحيح green = (*ptr >> 8) & 0xff;
            صحيح blue = (*ptr >> 0) & 0xff;
            إذا (alpha > 25) {
                نقاب_بٽ[y * ويڪر_بائيٽون + x / 8] |= (0x01 << (x % 8));

                إذا ((red + green + blue) > 0x40) {
                    fg_بٽ++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    معلومات_بٽ[y * ويڪر_بائيٽون + x / 8] |= (0x01 << (x % 8));
                } وإلا {
                    bg_بٽ++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    إذا (fg_بٽ) {
        fg.red = rfg * 257 / fg_بٽ;
        fg.green = gfg * 257 / fg_بٽ;
        fg.blue = bfg * 257 / fg_بٽ;
    } وإلا {
        fg.red = fg.green = fg.blue = 0;
    }

    إذا (bg_بٽ) {
        bg.red = rbg * 257 / bg_بٽ;
        bg.green = gbg * 257 / bg_بٽ;
        bg.blue = bbg * 257 / bg_بٽ;
    } وإلا {
        bg.red = bg.green = bg.blue = 0;
    }

    معلومات_pixmap = X11_XCreate_Bitmap_From_معلومات(display, Default_پاڙ_دري(display),
                                            (حرف *)معلومات_بٽ,
                                            surface->w, surface->h);
    نقاب_pixmap = X11_XCreate_Bitmap_From_معلومات(display, Default_پاڙ_دري(display),
                                            (حرف *)نقاب_بٽ,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, معلومات_pixmap, نقاب_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, معلومات_pixmap);
    X11_XFreePixmap(display, نقاب_pixmap);
    SDL_free(معلومات_بٽ);
    SDL_free(نقاب_بٽ);

    أرجع cursor;
}

ساكن SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    Cursor x11_cursor = None;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XCURSOR
    إذا (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#جيڪڏهن_پورو
    إذا (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    أرجع X11_Create_Cursor_And_معلومات(x11_cursor);
}

ساكن SDL_Cursor *X11_CreateAnimatedCursor(SDL_Cursor_چوکٺو_Info *چوکٺا, صحيح انگ_چوکٺا, صحيح hot_x, صحيح hot_y)
{
    Cursor x11_cursor = None;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XCURSOR
    إذا (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(چوکٺا, انگ_چوکٺا, hot_x, hot_y);
    }
#جيڪڏهن_پورو
    إذا (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(چوکٺا[0].surface, hot_x, hot_y);
    }

    أرجع X11_Create_Cursor_And_معلومات(x11_cursor);
}

ساكن بنانشان صحيح GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    بدل (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        حالة SDL_SYSTEM_CURSOR_DEFAULT: أرجع XC_کاٻو_ptr;
        حالة SDL_SYSTEM_CURSOR_متن: أرجع XC_xterm;
        حالة SDL_SYSTEM_CURSOR_WAIT: أرجع XC_watch;
        حالة SDL_SYSTEM_CURSOR_CROSSHAIR: أرجع XC_tcross;
        حالة SDL_SYSTEM_CURSOR_ترقي: أرجع XC_watch;
        حالة SDL_SYSTEM_CURSOR_NWSE_RESIZE: أرجع XC_چوٽي_کاٻو_ڪنڊ;
        حالة SDL_SYSTEM_CURSOR_NESW_RESIZE: أرجع XC_چوٽي_ساڄو_ڪنڊ;
        حالة SDL_SYSTEM_CURSOR_EW_RESIZE: أرجع XC_sb_h_double_arrow;
        حالة SDL_SYSTEM_CURSOR_NS_RESIZE: أرجع XC_sb_v_double_arrow;
        حالة SDL_SYSTEM_CURSOR_MOVE: أرجع XC_fleur;
        حالة SDL_SYSTEM_CURSOR_NOT_ALLOWED: أرجع XC_pirate;
        حالة SDL_SYSTEM_CURSOR_اشارو: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_NW_RESIZE: أرجع XC_چوٽي_کاٻو_ڪنڊ;
        حالة SDL_SYSTEM_CURSOR_N_RESIZE: أرجع XC_چوٽي_side;
        حالة SDL_SYSTEM_CURSOR_NE_RESIZE: أرجع XC_چوٽي_ساڄو_ڪنڊ;
        حالة SDL_SYSTEM_CURSOR_E_RESIZE: أرجع XC_ساڄو_side;
        حالة SDL_SYSTEM_CURSOR_SE_RESIZE: أرجع XC_bottom_ساڄو_ڪنڊ;
        حالة SDL_SYSTEM_CURSOR_S_RESIZE: أرجع XC_bottom_side;
        حالة SDL_SYSTEM_CURSOR_SW_RESIZE: أرجع XC_bottom_کاٻو_ڪنڊ;
        حالة SDL_SYSTEM_CURSOR_W_RESIZE: أرجع XC_کاٻو_side;
        حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_HELP: أرجع XC_question_arrow;
        حالة SDL_SYSTEM_CURSOR_CELL: أرجع XC_cross;
        حالة SDL_SYSTEM_CURSOR_VERTICAL_متن: أرجع XC_xterm;
        حالة SDL_SYSTEM_CURSOR_ALIAS: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_COPY: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_NO_DROP: أرجع XC_pirate;
        حالة SDL_SYSTEM_CURSOR_GRAB: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_GRABBING: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_کانو_RESIZE: أرجع XC_sb_h_double_arrow;
        حالة SDL_SYSTEM_CURSOR_صف_RESIZE: أرجع XC_sb_v_double_arrow;
        حالة SDL_SYSTEM_CURSOR_ALL_SCROLL: أرجع XC_fleur;
        حالة SDL_SYSTEM_CURSOR_ZOOM_اندريون: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_ZOOM_ٻاهريون: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_ڳڻپ: اكسر;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    أرجع 0;
}

ساكن SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = عدم;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XCURSOR
    إذا (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_Xcursor_Library_ڀريو_Cursor(dpy, SDL_GetCSSCursorName(id, عدم));
    }
#جيڪڏهن_پورو

    إذا (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    إذا (x11_cursor != None) {
        cursor = X11_Create_Cursor_And_معلومات(x11_cursor);
    }

    أرجع cursor;
}

ساكن SDL_Cursor *X11_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع X11_CreateSystemCursor(id);
}

ساكن فراغ X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->اندروني->cursor;

    إذا (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->اندروني);
    SDL_free(cursor);
}

ساكن bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    إذا (cursor) {
        x11_cursor = cursor->اندروني->cursor;
    } وإلا {
        x11_cursor = X11_Create_خالي_جايون_Cursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_دري *دري;

        x11_cursor_visible = !!cursor;

        لكل (دري = video->windows; دري; دري = دري->ايندڙ) {
            SDL_دري_معلومات *معلومات = دري->اندروني;
            إذا (معلومات) {
                إذا (x11_cursor != None) {
                    X11_XDefineCursor(display, معلومات->xwindow, x11_cursor);
                } وإلا {
                    X11_XUndefineCursor(display, معلومات->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    أرجع true;
}

ساكن فراغ X11_Warp_Mouse_اندروني(دري_2 xwindow, عائم x, عائم y)
{
    SDL_Video_معلومات *videodata = SDL_GetVideoDevice()->اندروني;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    إذا (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    إذا (warp_hack) {
        X11_ShowCursor(عدم);
    }
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XINPUT2
    صحيح deviceid = 0;
    إذا (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        إذا (Screen_ڳڻپ(display) == 1) {
            X11_XIGet_Client_اشارو(display, None, &deviceid);
        }
    }
    إذا (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarp_اشارو(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } وإلا
#جيڪڏهن_پورو
    {
        X11_XWarp_اشارو(display, None, xwindow, 0, 0, 0, 0, (صحيح)x, (صحيح)y);
    }

    إذا (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_بدليو = true;
}

ساكن bool X11_WarpMouse(SDL_دري *دري, عائم x, عائم y)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;

    إذا (X11_WarpMouseXTest(SDL_GetVideoDevice(), دري, x, y)) {
        أرجع true;
    }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    إذا (معلومات->اشارو_barrier_سرگرم == false) {
        X11_Warp_Mouse_اندروني(معلومات->xwindow, x, y);
    }
#وإلا
    X11_Warp_Mouse_اندروني(معلومات->xwindow, x, y);
#جيڪڏهن_پورو
    أرجع true;
}

ساكن bool X11_WarpMouseGlobal(عائم x, عائم y)
{
    إذا (X11_WarpMouseXTest(SDL_GetVideoDevice(), عدم, x, y)) {
        أرجع true;
    }

    X11_Warp_Mouse_اندروني(Default_پاڙ_دري(GetDisplay()), x, y);
    أرجع true;
}

ساكن bool X11_سيٽ_Relative_Mouse_گهڻائي(bool enabled)
{
    إذا (!X11_Xinput2IsInitialized()) {
        أرجع SDL_Unsupported();
    }
    أرجع true;
}

ساكن bool X11_CaptureMouse(SDL_دري *دري)
{
    Display *display = GetDisplay();
    SDL_دري *mouse_focus = SDL_GetMouseFocus();

    إذا (دري) {
        SDL_دري_معلومات *معلومات = دري->اندروني;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        إذا (!معلومات->xinput2_mouse_enabled || معلومات->mouse_grabbed) {
            ثابت بنانشان صحيح نقاب = Button_Press_نقاب | Button_Release_نقاب | اشارو_Motion_نقاب | Focus_Change_نقاب;
            دري_2 confined = (معلومات->mouse_grabbed ? معلومات->xwindow : None);
            ثابت صحيح rc = X11_XGrab_اشارو(display, معلومات->xwindow, False,
                                            نقاب, Grab_گهڻائي_Async, Grab_گهڻائي_Async,
                                            confined, None, Current_وقت);
            إذا (rc != GrabSuccess) {
                أرجع SDL_سيٽ_Error("X server refused mouse capture");
            }

            إذا (معلومات->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                معلومات->videodata->global_mouse_بدليو = true;
            }
        }
    } وإلا إذا (mouse_focus) {
        SDL_Update_دري_Grab(mouse_focus);
    } وإلا {
        X11_XUngrab_اشارو(display, Current_وقت);
    }

    X11_XSync(display, False);

    أرجع true;
}

ساكن SDL_MouseButtonFlags X11_GetGlobalMouseState(عائم *x, عائم *y)
{
    SDL_Video_معلومات *videodata = SDL_GetVideoDevice()->اندروني;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    صحيح i;

    // !!! FIXME: should we XSync() here first?

    إذا (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_بدليو = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    إذا (videodata->global_mouse_بدليو) {
        displays = SDL_GetDisplays(عدم);
        إذا (displays) {
            لكل (i = 0; displays[i]; ++i) {
                SDL_Display_معلومات *معلومات = SDL_Get_Display_Driver_معلومات(displays[i]);
                إذا (معلومات) {
                    دري_2 پاڙ, ٻار;
                    صحيح rootx, rooty, winx, winy;
                    بنانشان صحيح نقاب;
                    إذا (X11_XQuery_اشارو(display, پاڙ_دري(display, معلومات->screen), &پاڙ, &ٻار, &rootx, &rooty, &winx, &winy, &نقاب)) {
                        XWindow_خاصيتون پاڙ_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (نقاب & Button1_نقاب) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (نقاب & Button2_نقاب) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (نقاب & Button3_نقاب) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(عدم, عدم) & (SDL_BUTTON_X1_نقاب | SDL_BUTTON_X2_نقاب));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGet_دري_خاصيتون(display, پاڙ, &پاڙ_attrs);
                        videodata->global_mouse_position.x = پاڙ_attrs.x + rootx;
                        videodata->global_mouse_position.y = پاڙ_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_بدليو = false;
                        اكسر;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_بدليو); // The pointer wasn't on any X11 screen?!

    *x = (عائم)videodata->global_mouse_position.x;
    *y = (عائم)videodata->global_mouse_position.y;
    أرجع videodata->global_mouse_buttons;
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
    mouse->سيٽ_Relative_Mouse_گهڻائي = X11_سيٽ_Relative_Mouse_گهڻائي;
    mouse->CaptureMouse = X11_CaptureMouse;
    mouse->GetGlobalMouseState = X11_GetGlobalMouseState;

    SDL_ڪاميابي_Test_نتيجو r = SDL_HITTEST_عام;
    طالما (r <= SDL_HITTEST_RESIZE_کاٻو) {
        بدل (r) {
        حالة SDL_HITTEST_عام: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); اكسر;
        حالة SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); اكسر;
        حالة SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_چوٽي: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_ساڄو: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_کاٻو: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); اكسر;
        }
        r++;
    }

    SDL_سيٽ_Default_Cursor(X11_CreateDefaultCursor());
}

فراغ X11_QuitMouse(SDL_VideoDevice *_this)
{
    لكل (صحيح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        إذا (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = عدم;
        }
    }

    X11_Destroy_خالي_جايون_Cursor();
}

فراغ X11_سيٽ_ڪاميابي_Test_Cursor(SDL_ڪاميابي_Test_نتيجو rc)
{
    إذا (rc == SDL_HITTEST_عام || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } وإلا {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11
