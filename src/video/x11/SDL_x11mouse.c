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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

#ضمن <X11/cursorfont.h>
#ضمن "SDL_x11video.h"
#ضمن "SDL_x11mouse.h"
#ضمن "SDL_x11xinput2.h"
#ضمن "SDL_x11xtest.h"
#ضمن "../SDL_video_c.h"
#ضمن "../../events/SDL_mouse_c.h"

بنية SDL_Cursor_داده
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
ساكن Cursor x11_خالی_cursor = None;
ساكن bool x11_cursor_visible = true;

ساكن SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_چپ + 1];

ساكن Display *GetDisplay(فراغ)
{
    أرجع SDL_GetVideoDevice()->داخلی->display;
}

ساكن Cursor X11_Create_خالی_Cursor(فراغ)
{
    إذا (x11_خالی_cursor == None) {
        Display *display = GetDisplay();
        حرف داده[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(داده);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreate_Bitmap_From_داده(display, Default_ریشه_پنجره(display),
                                           داده, 1, 1);
        إذا (pixmap) {
            x11_خالی_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    أرجع x11_خالی_cursor;
}

ساكن فراغ X11_Destroy_خالی_Cursor(فراغ)
{
    إذا (x11_خالی_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_خالی_cursor);
        x11_خالی_cursor = None;
    }
}

ساكن SDL_Cursor *X11_Create_Cursor_And_داده(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (cursor) {
        SDL_Cursor_داده *داده = (SDL_Cursor_داده *)SDL_calloc(1, حجم(*داده));
        إذا (!داده) {
            SDL_free(cursor);
            أرجع عدم;
        }
        داده->cursor = x11_cursor;
        cursor->داخلی = داده;
    }
    أرجع cursor;
}

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XCURSOR
ساكن XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, صحيح hot_x, صحيح hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    إذا (!image) {
        SDL_بیرون_از_حافظه();
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
        cursor = X11_Xcursor_Image_بارگیری_Cursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    أرجع cursor;
}

ساكن Cursor X11_CreateAnimatedXCursorCursor(SDL_Cursor_قاب_Info *قابها, صحيح رقم_قابها, صحيح hot_x, صحيح hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(رقم_قابها);
    إذا (!images) {
        SDL_بیرون_از_حافظه();
        أرجع None;
    }

    لكل (صحيح i = 0; i < رقم_قابها; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(قابها[i].surface, hot_x, hot_y, قابها[i].duration);
        إذا (!image) {
            اذهب cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_Xcursor_Images_بارگیری_Cursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    أرجع cursor;
}
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XCURSOR

ساكن Cursor X11_CreatePixmapCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *داده_بیتها, *ماسک_بیتها;
    Pixmap داده_pixmap, ماسک_pixmap;
    صحيح x, y;
    بیعلامت صحيح rfg, gfg, bfg, rbg, gbg, bbg, fg_بیتها, bg_بیتها;
    size_t عرض_بایتها = ((surface->w + 7) & ~((size_t)7)) / 8;

    داده_بیتها = SDL_calloc(1, surface->h * عرض_بایتها);
    إذا (!داده_بیتها) {
        أرجع None;
    }

    ماسک_بیتها = SDL_calloc(1, surface->h * عرض_بایتها);
    إذا (!ماسک_بیتها) {
        SDL_free(داده_بیتها);
        أرجع None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fg_بیتها = bg_بیتها = 0;
    لكل (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        لكل (x = 0; x < surface->w; ++x) {
            صحيح alpha = (*ptr >> 24) & 0xff;
            صحيح red = (*ptr >> 16) & 0xff;
            صحيح green = (*ptr >> 8) & 0xff;
            صحيح blue = (*ptr >> 0) & 0xff;
            إذا (alpha > 25) {
                ماسک_بیتها[y * عرض_بایتها + x / 8] |= (0x01 << (x % 8));

                إذا ((red + green + blue) > 0x40) {
                    fg_بیتها++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    داده_بیتها[y * عرض_بایتها + x / 8] |= (0x01 << (x % 8));
                } وإلا {
                    bg_بیتها++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    إذا (fg_بیتها) {
        fg.red = rfg * 257 / fg_بیتها;
        fg.green = gfg * 257 / fg_بیتها;
        fg.blue = bfg * 257 / fg_بیتها;
    } وإلا {
        fg.red = fg.green = fg.blue = 0;
    }

    إذا (bg_بیتها) {
        bg.red = rbg * 257 / bg_بیتها;
        bg.green = gbg * 257 / bg_بیتها;
        bg.blue = bbg * 257 / bg_بیتها;
    } وإلا {
        bg.red = bg.green = bg.blue = 0;
    }

    داده_pixmap = X11_XCreate_Bitmap_From_داده(display, Default_ریشه_پنجره(display),
                                            (حرف *)داده_بیتها,
                                            surface->w, surface->h);
    ماسک_pixmap = X11_XCreate_Bitmap_From_داده(display, Default_ریشه_پنجره(display),
                                            (حرف *)ماسک_بیتها,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, داده_pixmap, ماسک_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, داده_pixmap);
    X11_XFreePixmap(display, ماسک_pixmap);
    SDL_free(داده_بیتها);
    SDL_free(ماسک_بیتها);

    أرجع cursor;
}

ساكن SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    Cursor x11_cursor = None;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XCURSOR
    إذا (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#پایان_اگر
    إذا (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    أرجع X11_Create_Cursor_And_داده(x11_cursor);
}

ساكن SDL_Cursor *X11_CreateAnimatedCursor(SDL_Cursor_قاب_Info *قابها, صحيح رقم_قابها, صحيح hot_x, صحيح hot_y)
{
    Cursor x11_cursor = None;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XCURSOR
    إذا (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(قابها, رقم_قابها, hot_x, hot_y);
    }
#پایان_اگر
    إذا (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(قابها[0].surface, hot_x, hot_y);
    }

    أرجع X11_Create_Cursor_And_داده(x11_cursor);
}

ساكن بیعلامت صحيح GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    بدل (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        حالة SDL_SYSTEM_CURSOR_DEFAULT: أرجع XC_چپ_ptr;
        حالة SDL_SYSTEM_CURSOR_متن: أرجع XC_xterm;
        حالة SDL_SYSTEM_CURSOR_WAIT: أرجع XC_watch;
        حالة SDL_SYSTEM_CURSOR_CROSSHAIR: أرجع XC_tcross;
        حالة SDL_SYSTEM_CURSOR_پیشرفت: أرجع XC_watch;
        حالة SDL_SYSTEM_CURSOR_NWSE_RESIZE: أرجع XC_بالاترین_چپ_گوشه;
        حالة SDL_SYSTEM_CURSOR_NESW_RESIZE: أرجع XC_بالاترین_راست_گوشه;
        حالة SDL_SYSTEM_CURSOR_EW_RESIZE: أرجع XC_sb_h_double_arrow;
        حالة SDL_SYSTEM_CURSOR_NS_RESIZE: أرجع XC_sb_v_double_arrow;
        حالة SDL_SYSTEM_CURSOR_MOVE: أرجع XC_fleur;
        حالة SDL_SYSTEM_CURSOR_NOT_ALLOWED: أرجع XC_pirate;
        حالة SDL_SYSTEM_CURSOR_اشاره_گر: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_NW_RESIZE: أرجع XC_بالاترین_چپ_گوشه;
        حالة SDL_SYSTEM_CURSOR_N_RESIZE: أرجع XC_بالاترین_side;
        حالة SDL_SYSTEM_CURSOR_NE_RESIZE: أرجع XC_بالاترین_راست_گوشه;
        حالة SDL_SYSTEM_CURSOR_E_RESIZE: أرجع XC_راست_side;
        حالة SDL_SYSTEM_CURSOR_SE_RESIZE: أرجع XC_bottom_راست_گوشه;
        حالة SDL_SYSTEM_CURSOR_S_RESIZE: أرجع XC_bottom_side;
        حالة SDL_SYSTEM_CURSOR_SW_RESIZE: أرجع XC_bottom_چپ_گوشه;
        حالة SDL_SYSTEM_CURSOR_W_RESIZE: أرجع XC_چپ_side;
        حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_HELP: أرجع XC_question_arrow;
        حالة SDL_SYSTEM_CURSOR_CELL: أرجع XC_cross;
        حالة SDL_SYSTEM_CURSOR_VERTICAL_متن: أرجع XC_xterm;
        حالة SDL_SYSTEM_CURSOR_ALIAS: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_COPY: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_NO_DROP: أرجع XC_pirate;
        حالة SDL_SYSTEM_CURSOR_GRAB: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_GRABBING: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_ستون_RESIZE: أرجع XC_sb_h_double_arrow;
        حالة SDL_SYSTEM_CURSOR_ردیف_RESIZE: أرجع XC_sb_v_double_arrow;
        حالة SDL_SYSTEM_CURSOR_ALL_SCROLL: أرجع XC_fleur;
        حالة SDL_SYSTEM_CURSOR_ZOOM_درون: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_ZOOM_بیرون: أرجع XC_hand2;
        حالة SDL_SYSTEM_CURSOR_شمار: اكسر;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    أرجع 0;
}

ساكن SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = عدم;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XCURSOR
    إذا (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_Xcursor_Library_بارگیری_Cursor(dpy, SDL_GetCSSCursorName(id, عدم));
    }
#پایان_اگر

    إذا (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    إذا (x11_cursor != None) {
        cursor = X11_Create_Cursor_And_داده(x11_cursor);
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
    Cursor x11_cursor = cursor->داخلی->cursor;

    إذا (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->داخلی);
    SDL_free(cursor);
}

ساكن bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    إذا (cursor) {
        x11_cursor = cursor->داخلی->cursor;
    } وإلا {
        x11_cursor = X11_Create_خالی_Cursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_پنجره *پنجره;

        x11_cursor_visible = !!cursor;

        لكل (پنجره = video->windows; پنجره; پنجره = پنجره->بعدی) {
            SDL_پنجره_داده *داده = پنجره->داخلی;
            إذا (داده) {
                إذا (x11_cursor != None) {
                    X11_XDefineCursor(display, داده->xwindow, x11_cursor);
                } وإلا {
                    X11_XUndefineCursor(display, داده->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    أرجع true;
}

ساكن فراغ X11_Warp_Mouse_داخلی(پنجره_2 xwindow, عائم x, عائم y)
{
    SDL_Video_داده *videodata = SDL_GetVideoDevice()->داخلی;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    إذا (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    إذا (warp_hack) {
        X11_ShowCursor(عدم);
    }
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XINPUT2
    صحيح deviceid = 0;
    إذا (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        إذا (Screen_شمار(display) == 1) {
            X11_XIGet_Client_اشاره_گر(display, None, &deviceid);
        }
    }
    إذا (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarp_اشاره_گر(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } وإلا
#پایان_اگر
    {
        X11_XWarp_اشاره_گر(display, None, xwindow, 0, 0, 0, 0, (صحيح)x, (صحيح)y);
    }

    إذا (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_تغییریافته = true;
}

ساكن bool X11_WarpMouse(SDL_پنجره *پنجره, عائم x, عائم y)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;

    إذا (X11_WarpMouseXTest(SDL_GetVideoDevice(), پنجره, x, y)) {
        أرجع true;
    }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    إذا (داده->اشاره_گر_barrier_فعال == false) {
        X11_Warp_Mouse_داخلی(داده->xwindow, x, y);
    }
#وإلا
    X11_Warp_Mouse_داخلی(داده->xwindow, x, y);
#پایان_اگر
    أرجع true;
}

ساكن bool X11_WarpMouseGlobal(عائم x, عائم y)
{
    إذا (X11_WarpMouseXTest(SDL_GetVideoDevice(), عدم, x, y)) {
        أرجع true;
    }

    X11_Warp_Mouse_داخلی(Default_ریشه_پنجره(GetDisplay()), x, y);
    أرجع true;
}

ساكن bool X11_مجموعه_Relative_Mouse_نما(bool enabled)
{
    إذا (!X11_Xinput2IsInitialized()) {
        أرجع SDL_Unsupported();
    }
    أرجع true;
}

ساكن bool X11_CaptureMouse(SDL_پنجره *پنجره)
{
    Display *display = GetDisplay();
    SDL_پنجره *mouse_focus = SDL_GetMouseFocus();

    إذا (پنجره) {
        SDL_پنجره_داده *داده = پنجره->داخلی;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        إذا (!داده->xinput2_mouse_enabled || داده->mouse_grabbed) {
            ثابت بیعلامت صحيح ماسک = Button_Press_ماسک | Button_Release_ماسک | اشاره_گر_Motion_ماسک | Focus_Change_ماسک;
            پنجره_2 confined = (داده->mouse_grabbed ? داده->xwindow : None);
            ثابت صحيح rc = X11_XGrab_اشاره_گر(display, داده->xwindow, False,
                                            ماسک, Grab_نما_Async, Grab_نما_Async,
                                            confined, None, Current_زمان);
            إذا (rc != GrabSuccess) {
                أرجع SDL_مجموعه_Error("X server refused mouse capture");
            }

            إذا (داده->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                داده->videodata->global_mouse_تغییریافته = true;
            }
        }
    } وإلا إذا (mouse_focus) {
        SDL_Update_پنجره_Grab(mouse_focus);
    } وإلا {
        X11_XUngrab_اشاره_گر(display, Current_زمان);
    }

    X11_XSync(display, False);

    أرجع true;
}

ساكن SDL_MouseButtonFlags X11_GetGlobalMouseState(عائم *x, عائم *y)
{
    SDL_Video_داده *videodata = SDL_GetVideoDevice()->داخلی;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    صحيح i;

    // !!! FIXME: should we XSync() here first?

    إذا (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_تغییریافته = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    إذا (videodata->global_mouse_تغییریافته) {
        displays = SDL_GetDisplays(عدم);
        إذا (displays) {
            لكل (i = 0; displays[i]; ++i) {
                SDL_Display_داده *داده = SDL_Get_Display_Driver_داده(displays[i]);
                إذا (داده) {
                    پنجره_2 ریشه, فرزند;
                    صحيح rootx, rooty, winx, winy;
                    بیعلامت صحيح ماسک;
                    إذا (X11_XQuery_اشاره_گر(display, ریشه_پنجره(display, داده->screen), &ریشه, &فرزند, &rootx, &rooty, &winx, &winy, &ماسک)) {
                        XWindow_صفات ریشه_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (ماسک & Button1_ماسک) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (ماسک & Button2_ماسک) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (ماسک & Button3_ماسک) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(عدم, عدم) & (SDL_BUTTON_X1_ماسک | SDL_BUTTON_X2_ماسک));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGet_پنجره_صفات(display, ریشه, &ریشه_attrs);
                        videodata->global_mouse_position.x = ریشه_attrs.x + rootx;
                        videodata->global_mouse_position.y = ریشه_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_تغییریافته = false;
                        اكسر;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_تغییریافته); // The pointer wasn't on any X11 screen?!

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
    mouse->مجموعه_Relative_Mouse_نما = X11_مجموعه_Relative_Mouse_نما;
    mouse->CaptureMouse = X11_CaptureMouse;
    mouse->GetGlobalMouseState = X11_GetGlobalMouseState;

    SDL_اصابت_Test_نتیجه r = SDL_HITTEST_نرمال;
    طالما (r <= SDL_HITTEST_RESIZE_چپ) {
        بدل (r) {
        حالة SDL_HITTEST_نرمال: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); اكسر;
        حالة SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); اكسر;
        حالة SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_بالاترین: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_راست: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); اكسر;
        حالة SDL_HITTEST_RESIZE_چپ: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); اكسر;
        }
        r++;
    }

    SDL_مجموعه_Default_Cursor(X11_CreateDefaultCursor());
}

فراغ X11_QuitMouse(SDL_VideoDevice *_this)
{
    لكل (صحيح i = 0; i < SDL_arraysize(sys_cursors); i++) {
        إذا (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = عدم;
        }
    }

    X11_Destroy_خالی_Cursor();
}

فراغ X11_مجموعه_اصابت_Test_Cursor(SDL_اصابت_Test_نتیجه rc)
{
    إذا (rc == SDL_HITTEST_نرمال || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } وإلا {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#پایان_اگر // SDL_VIDEO_DRIVER_X11
