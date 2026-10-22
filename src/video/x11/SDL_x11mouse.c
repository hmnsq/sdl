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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#شامل <X11/cursorfont.h>
#شامل "SDL_x11video.h"
#شامل "SDL_x11mouse.h"
#شامل "SDL_x11xinput2.h"
#شامل "SDL_x11xtest.h"
#شامل "../SDL_video_c.h"
#شامل "../../events/SDL_mouse_c.h"

ساخت SDL_Cursor_ڈیٹا
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
ساکن Cursor x11_خالی_خانے_cursor = None;
ساکن bool x11_cursor_visible = true;

ساکن SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_بایاں + 1];

ساکن Display *GetDisplay(خالی)
{
    واپس SDL_GetVideoDevice()->اندرونی_2->display;
}

ساکن Cursor X11_Create_خالی_خانے_Cursor(خالی)
{
    اگر (x11_خالی_خانے_cursor == None) {
        Display *display = GetDisplay();
        حرف ڈیٹا[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(ڈیٹا);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreate_Bitmap_From_ڈیٹا(display, Default_جڑ_کھڑکی(display),
                                           ڈیٹا, 1, 1);
        اگر (pixmap) {
            x11_خالی_خانے_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    واپس x11_خالی_خانے_cursor;
}

ساکن خالی X11_Destroy_خالی_خانے_Cursor(خالی)
{
    اگر (x11_خالی_خانے_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_خالی_خانے_cursor);
        x11_خالی_خانے_cursor = None;
    }
}

ساکن SDL_Cursor *X11_Create_Cursor_And_ڈیٹا(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    اگر (cursor) {
        SDL_Cursor_ڈیٹا *ڈیٹا = (SDL_Cursor_ڈیٹا *)SDL_calloc(1, حجم(*ڈیٹا));
        اگر (!ڈیٹا) {
            SDL_free(cursor);
            واپس تہی;
        }
        ڈیٹا->cursor = x11_cursor;
        cursor->اندرونی_2 = ڈیٹا;
    }
    واپس cursor;
}

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XCURSOR
ساکن XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, صحیح hot_x, صحیح hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    اگر (!image) {
        SDL_برآمد_کا_حافظہ();
        واپس تہی;
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

    واپس image;
}

ساکن Cursor X11_CreateXCursorCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    اگر (image) {
        cursor = X11_Xcursor_Image_بھرو_Cursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    واپس cursor;
}

ساکن Cursor X11_CreateAnimatedXCursorCursor(SDL_Cursor_چوکھٹا_Info *چوکھٹے, صحیح عدد_چوکھٹے, صحیح hot_x, صحیح hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(عدد_چوکھٹے);
    اگر (!images) {
        SDL_برآمد_کا_حافظہ();
        واپس None;
    }

    برائے (صحیح i = 0; i < عدد_چوکھٹے; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(چوکھٹے[i].surface, hot_x, hot_y, چوکھٹے[i].duration);
        اگر (!image) {
            جاؤ cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_Xcursor_Images_بھرو_Cursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    واپس cursor;
}
#اگر_ختم // SDL_VIDEO_DRIVER_X11_XCURSOR

ساکن Cursor X11_CreatePixmapCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *ڈیٹا_بٹ, *نقاب_بٹ;
    Pixmap ڈیٹا_pixmap, نقاب_pixmap;
    صحیح x, y;
    غیرعلامتی صحیح rfg, gfg, bfg, rbg, gbg, bbg, fg_بٹ, bg_بٹ;
    size_t چوڑائی_بائٹیں = ((surface->w + 7) & ~((size_t)7)) / 8;

    ڈیٹا_بٹ = SDL_calloc(1, surface->h * چوڑائی_بائٹیں);
    اگر (!ڈیٹا_بٹ) {
        واپس None;
    }

    نقاب_بٹ = SDL_calloc(1, surface->h * چوڑائی_بائٹیں);
    اگر (!نقاب_بٹ) {
        SDL_free(ڈیٹا_بٹ);
        واپس None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fg_بٹ = bg_بٹ = 0;
    برائے (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        برائے (x = 0; x < surface->w; ++x) {
            صحیح alpha = (*ptr >> 24) & 0xff;
            صحیح red = (*ptr >> 16) & 0xff;
            صحیح green = (*ptr >> 8) & 0xff;
            صحیح blue = (*ptr >> 0) & 0xff;
            اگر (alpha > 25) {
                نقاب_بٹ[y * چوڑائی_بائٹیں + x / 8] |= (0x01 << (x % 8));

                اگر ((red + green + blue) > 0x40) {
                    fg_بٹ++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    ڈیٹا_بٹ[y * چوڑائی_بائٹیں + x / 8] |= (0x01 << (x % 8));
                } ورنہ {
                    bg_بٹ++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    اگر (fg_بٹ) {
        fg.red = rfg * 257 / fg_بٹ;
        fg.green = gfg * 257 / fg_بٹ;
        fg.blue = bfg * 257 / fg_بٹ;
    } ورنہ {
        fg.red = fg.green = fg.blue = 0;
    }

    اگر (bg_بٹ) {
        bg.red = rbg * 257 / bg_بٹ;
        bg.green = gbg * 257 / bg_بٹ;
        bg.blue = bbg * 257 / bg_بٹ;
    } ورنہ {
        bg.red = bg.green = bg.blue = 0;
    }

    ڈیٹا_pixmap = X11_XCreate_Bitmap_From_ڈیٹا(display, Default_جڑ_کھڑکی(display),
                                            (حرف *)ڈیٹا_بٹ,
                                            surface->w, surface->h);
    نقاب_pixmap = X11_XCreate_Bitmap_From_ڈیٹا(display, Default_جڑ_کھڑکی(display),
                                            (حرف *)نقاب_بٹ,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, ڈیٹا_pixmap, نقاب_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, ڈیٹا_pixmap);
    X11_XFreePixmap(display, نقاب_pixmap);
    SDL_free(ڈیٹا_بٹ);
    SDL_free(نقاب_بٹ);

    واپس cursor;
}

ساکن SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    Cursor x11_cursor = None;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XCURSOR
    اگر (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#اگر_ختم
    اگر (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    واپس X11_Create_Cursor_And_ڈیٹا(x11_cursor);
}

ساکن SDL_Cursor *X11_CreateAnimatedCursor(SDL_Cursor_چوکھٹا_Info *چوکھٹے, صحیح عدد_چوکھٹے, صحیح hot_x, صحیح hot_y)
{
    Cursor x11_cursor = None;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XCURSOR
    اگر (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(چوکھٹے, عدد_چوکھٹے, hot_x, hot_y);
    }
#اگر_ختم
    اگر (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(چوکھٹے[0].surface, hot_x, hot_y);
    }

    واپس X11_Create_Cursor_And_ڈیٹا(x11_cursor);
}

ساکن غیرعلامتی صحیح GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    انتخاب (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        حالت SDL_SYSTEM_CURSOR_DEFAULT: واپس XC_بایاں_ptr;
        حالت SDL_SYSTEM_CURSOR_متن: واپس XC_xterm;
        حالت SDL_SYSTEM_CURSOR_WAIT: واپس XC_watch;
        حالت SDL_SYSTEM_CURSOR_CROSSHAIR: واپس XC_tcross;
        حالت SDL_SYSTEM_CURSOR_پیش_رفت: واپس XC_watch;
        حالت SDL_SYSTEM_CURSOR_NWSE_RESIZE: واپس XC_چوٹی_بایاں_کونا;
        حالت SDL_SYSTEM_CURSOR_NESW_RESIZE: واپس XC_چوٹی_دایاں_کونا;
        حالت SDL_SYSTEM_CURSOR_EW_RESIZE: واپس XC_sb_h_double_arrow;
        حالت SDL_SYSTEM_CURSOR_NS_RESIZE: واپس XC_sb_v_double_arrow;
        حالت SDL_SYSTEM_CURSOR_MOVE: واپس XC_fleur;
        حالت SDL_SYSTEM_CURSOR_NOT_ALLOWED: واپس XC_pirate;
        حالت SDL_SYSTEM_CURSOR_اشارہ_گر: واپس XC_hand2;
        حالت SDL_SYSTEM_CURSOR_NW_RESIZE: واپس XC_چوٹی_بایاں_کونا;
        حالت SDL_SYSTEM_CURSOR_N_RESIZE: واپس XC_چوٹی_side;
        حالت SDL_SYSTEM_CURSOR_NE_RESIZE: واپس XC_چوٹی_دایاں_کونا;
        حالت SDL_SYSTEM_CURSOR_E_RESIZE: واپس XC_دایاں_side;
        حالت SDL_SYSTEM_CURSOR_SE_RESIZE: واپس XC_bottom_دایاں_کونا;
        حالت SDL_SYSTEM_CURSOR_S_RESIZE: واپس XC_bottom_side;
        حالت SDL_SYSTEM_CURSOR_SW_RESIZE: واپس XC_bottom_بایاں_کونا;
        حالت SDL_SYSTEM_CURSOR_W_RESIZE: واپس XC_بایاں_side;
        حالت SDL_SYSTEM_CURSOR_CONTEXT_MENU: واپس XC_hand2;
        حالت SDL_SYSTEM_CURSOR_HELP: واپس XC_question_arrow;
        حالت SDL_SYSTEM_CURSOR_CELL: واپس XC_cross;
        حالت SDL_SYSTEM_CURSOR_VERTICAL_متن: واپس XC_xterm;
        حالت SDL_SYSTEM_CURSOR_ALIAS: واپس XC_hand2;
        حالت SDL_SYSTEM_CURSOR_COPY: واپس XC_hand2;
        حالت SDL_SYSTEM_CURSOR_NO_DROP: واپس XC_pirate;
        حالت SDL_SYSTEM_CURSOR_GRAB: واپس XC_hand2;
        حالت SDL_SYSTEM_CURSOR_GRABBING: واپس XC_hand2;
        حالت SDL_SYSTEM_CURSOR_ستون_RESIZE: واپس XC_sb_h_double_arrow;
        حالت SDL_SYSTEM_CURSOR_صف_RESIZE: واپس XC_sb_v_double_arrow;
        حالت SDL_SYSTEM_CURSOR_ALL_SCROLL: واپس XC_fleur;
        حالت SDL_SYSTEM_CURSOR_ZOOM_اندر: واپس XC_hand2;
        حالت SDL_SYSTEM_CURSOR_ZOOM_برآمد: واپس XC_hand2;
        حالت SDL_SYSTEM_CURSOR_گنتی: توڑو;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    واپس 0;
}

ساکن SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = تہی;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XCURSOR
    اگر (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_Xcursor_Library_بھرو_Cursor(dpy, SDL_GetCSSCursorName(id, تہی));
    }
#اگر_ختم

    اگر (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    اگر (x11_cursor != None) {
        cursor = X11_Create_Cursor_And_ڈیٹا(x11_cursor);
    }

    واپس cursor;
}

ساکن SDL_Cursor *X11_CreateDefaultCursor(خالی)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    واپس X11_CreateSystemCursor(id);
}

ساکن خالی X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->اندرونی_2->cursor;

    اگر (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->اندرونی_2);
    SDL_free(cursor);
}

ساکن bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    اگر (cursor) {
        x11_cursor = cursor->اندرونی_2->cursor;
    } ورنہ {
        x11_cursor = X11_Create_خالی_خانے_Cursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_کھڑکی *کھڑکی;

        x11_cursor_visible = !!cursor;

        برائے (کھڑکی = video->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
            اگر (ڈیٹا) {
                اگر (x11_cursor != None) {
                    X11_XDefineCursor(display, ڈیٹا->xwindow, x11_cursor);
                } ورنہ {
                    X11_XUndefineCursor(display, ڈیٹا->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    واپس true;
}

ساکن خالی X11_Warp_Mouse_اندرونی(کھڑکی_2 xwindow, اعشاری x, اعشاری y)
{
    SDL_Video_ڈیٹا *videodata = SDL_GetVideoDevice()->اندرونی_2;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    اگر (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    اگر (warp_hack) {
        X11_ShowCursor(تہی);
    }
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
    صحیح deviceid = 0;
    اگر (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        اگر (Screen_گنتی(display) == 1) {
            X11_XIGet_Client_اشارہ_گر(display, None, &deviceid);
        }
    }
    اگر (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarp_اشارہ_گر(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } ورنہ
#اگر_ختم
    {
        X11_XWarp_اشارہ_گر(display, None, xwindow, 0, 0, 0, 0, (صحیح)x, (صحیح)y);
    }

    اگر (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_بدلا = true;
}

ساکن bool X11_WarpMouse(SDL_کھڑکی *کھڑکی, اعشاری x, اعشاری y)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

    اگر (X11_WarpMouseXTest(SDL_GetVideoDevice(), کھڑکی, x, y)) {
        واپس true;
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    اگر (ڈیٹا->اشارہ_گر_barrier_فعال == false) {
        X11_Warp_Mouse_اندرونی(ڈیٹا->xwindow, x, y);
    }
#ورنہ
    X11_Warp_Mouse_اندرونی(ڈیٹا->xwindow, x, y);
#اگر_ختم
    واپس true;
}

ساکن bool X11_WarpMouseGlobal(اعشاری x, اعشاری y)
{
    اگر (X11_WarpMouseXTest(SDL_GetVideoDevice(), تہی, x, y)) {
        واپس true;
    }

    X11_Warp_Mouse_اندرونی(Default_جڑ_کھڑکی(GetDisplay()), x, y);
    واپس true;
}

ساکن bool X11_سیٹ_Relative_Mouse_منوال(bool enabled)
{
    اگر (!X11_Xinput2IsInitialized()) {
        واپس SDL_Unsupported();
    }
    واپس true;
}

ساکن bool X11_CaptureMouse(SDL_کھڑکی *کھڑکی)
{
    Display *display = GetDisplay();
    SDL_کھڑکی *mouse_focus = SDL_GetMouseFocus();

    اگر (کھڑکی) {
        SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        اگر (!ڈیٹا->xinput2_mouse_enabled || ڈیٹا->mouse_grabbed) {
            ثابت غیرعلامتی صحیح نقاب = Button_Press_نقاب | Button_Release_نقاب | اشارہ_گر_Motion_نقاب | Focus_Change_نقاب;
            کھڑکی_2 confined = (ڈیٹا->mouse_grabbed ? ڈیٹا->xwindow : None);
            ثابت صحیح rc = X11_XGrab_اشارہ_گر(display, ڈیٹا->xwindow, False,
                                            نقاب, Grab_منوال_Async, Grab_منوال_Async,
                                            confined, None, Current_وقت);
            اگر (rc != GrabSuccess) {
                واپس SDL_سیٹ_Error("X server refused mouse capture");
            }

            اگر (ڈیٹا->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                ڈیٹا->videodata->global_mouse_بدلا = true;
            }
        }
    } ورنہ اگر (mouse_focus) {
        SDL_Update_کھڑکی_Grab(mouse_focus);
    } ورنہ {
        X11_XUngrab_اشارہ_گر(display, Current_وقت);
    }

    X11_XSync(display, False);

    واپس true;
}

ساکن SDL_MouseButtonFlags X11_GetGlobalMouseState(اعشاری *x, اعشاری *y)
{
    SDL_Video_ڈیٹا *videodata = SDL_GetVideoDevice()->اندرونی_2;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    صحیح i;

    // !!! FIXME: should we XSync() here first?

    اگر (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_بدلا = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    اگر (videodata->global_mouse_بدلا) {
        displays = SDL_GetDisplays(تہی);
        اگر (displays) {
            برائے (i = 0; displays[i]; ++i) {
                SDL_Display_ڈیٹا *ڈیٹا = SDL_Get_Display_Driver_ڈیٹا(displays[i]);
                اگر (ڈیٹا) {
                    کھڑکی_2 جڑ, بچہ;
                    صحیح rootx, rooty, winx, winy;
                    غیرعلامتی صحیح نقاب;
                    اگر (X11_XQuery_اشارہ_گر(display, جڑ_کھڑکی(display, ڈیٹا->screen), &جڑ, &بچہ, &rootx, &rooty, &winx, &winy, &نقاب)) {
                        XWindow_اوصاف جڑ_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (نقاب & Button1_نقاب) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (نقاب & Button2_نقاب) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (نقاب & Button3_نقاب) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(تہی, تہی) & (SDL_BUTTON_X1_نقاب | SDL_BUTTON_X2_نقاب));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGet_کھڑکی_اوصاف(display, جڑ, &جڑ_attrs);
                        videodata->global_mouse_position.x = جڑ_attrs.x + rootx;
                        videodata->global_mouse_position.y = جڑ_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_بدلا = false;
                        توڑو;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_بدلا); // The pointer wasn't on any X11 screen?!

    *x = (اعشاری)videodata->global_mouse_position.x;
    *y = (اعشاری)videodata->global_mouse_position.y;
    واپس videodata->global_mouse_buttons;
}

خالی X11_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = X11_CreateCursor;
    mouse->CreateAnimatedCursor = X11_CreateAnimatedCursor;
    mouse->CreateSystemCursor = X11_CreateSystemCursor;
    mouse->ShowCursor = X11_ShowCursor;
    mouse->FreeCursor = X11_FreeCursor;
    mouse->WarpMouse = X11_WarpMouse;
    mouse->WarpMouseGlobal = X11_WarpMouseGlobal;
    mouse->سیٹ_Relative_Mouse_منوال = X11_سیٹ_Relative_Mouse_منوال;
    mouse->CaptureMouse = X11_CaptureMouse;
    mouse->GetGlobalMouseState = X11_GetGlobalMouseState;

    SDL_کامیابی_Test_نتیجہ r = SDL_HITTEST_معمول;
    جب (r <= SDL_HITTEST_RESIZE_بایاں) {
        انتخاب (r) {
        حالت SDL_HITTEST_معمول: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); توڑو;
        حالت SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); توڑو;
        حالت SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); توڑو;
        حالت SDL_HITTEST_RESIZE_چوٹی: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); توڑو;
        حالت SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); توڑو;
        حالت SDL_HITTEST_RESIZE_دایاں: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); توڑو;
        حالت SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); توڑو;
        حالت SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); توڑو;
        حالت SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); توڑو;
        حالت SDL_HITTEST_RESIZE_بایاں: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); توڑو;
        }
        r++;
    }

    SDL_سیٹ_Default_Cursor(X11_CreateDefaultCursor());
}

خالی X11_QuitMouse(SDL_VideoDevice *_this)
{
    برائے (صحیح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        اگر (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = تہی;
        }
    }

    X11_Destroy_خالی_خانے_Cursor();
}

خالی X11_سیٹ_کامیابی_Test_Cursor(SDL_کامیابی_Test_نتیجہ rc)
{
    اگر (rc == SDL_HITTEST_معمول || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } ورنہ {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
