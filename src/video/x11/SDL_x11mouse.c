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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#include <X11/cursorfont.h>
#include "SDL_x11video.h"
#include "SDL_x11mouse.h"
#include "SDL_x11xinput2.h"
#include "SDL_x11xtest.h"
#include "../SDL_video_c.h"
#include "../../events/SDL_mouse_c.h"

sa_nracanaa SDL_CursorData
{
    Cursor cursor;
};

// FIXME: Find a better place to put this...
static Cursor x11_empty_cursor = None;
static bool x11_cursor_visible = true;

static SDL_Cursor *sys_cursors[SDL_HITTEST_RESIZE_LEFT + 1];

static Display *GetDisplay(void)
{
    ပြန်ပေး SDL_GetVideoDevice()->internal->display;
}

static Cursor X11_CreateEmptyCursor(void)
{
    အကယ်၍ (x11_empty_cursor == None) {
        Display *display = GetDisplay();
        var_na data[1];
        XColor color;
        Pixmap pixmap;

        SDL_zeroa(data);
        color.red = color.green = color.blue = 0;
        pixmap = X11_XCreateBitmapFromData(display, DefaultRootWindow(display),
                                           data, 1, 1);
        အကယ်၍ (pixmap) {
            x11_empty_cursor = X11_XCreatePixmapCursor(display, pixmap, pixmap,
                                                       &color, &color, 0, 0);
            X11_XFreePixmap(display, pixmap);
        }
    }
    ပြန်ပေး x11_empty_cursor;
}

static void X11_DestroyEmptyCursor(void)
{
    အကယ်၍ (x11_empty_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_empty_cursor);
        x11_empty_cursor = None;
    }
}

static SDL_Cursor *X11_CreateCursorAndData(Cursor x11_cursor)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, parimaa_na(*cursor));
    အကယ်၍ (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, parimaa_na(*data));
        အကယ်၍ (!data) {
            SDL_free(cursor);
            ပြန်ပေး NULL;
        }
        data->cursor = x11_cursor;
        cursor->internal = data;
    }
    ပြန်ပေး cursor;
}

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
static XcursorImage *X11_CreateXCursorImage(SDL_Surface *surface, ကိန်းပြည့် hot_x, ကိန်းပြည့် hot_y, Uint32 delay)
{
    XcursorImage *image = X11_XcursorImageCreate(surface->w, surface->h);
    အကယ်၍ (!image) {
        SDL_OutOfMemory();
        ပြန်ပေး NULL;
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

    ပြန်ပေး image;
}

static Cursor X11_CreateXCursorCursor(SDL_Surface *surface, ကိန်းပြည့် hot_x, ကိန်းပြည့် hot_y)
{
    Cursor cursor = None;
    XcursorImage *image = X11_CreateXCursorImage(surface, hot_x, hot_y, 0);

    အကယ်၍ (image) {
        cursor = X11_XcursorImageLoadCursor(GetDisplay(), image);
        X11_XcursorImageDestroy(image);
    }

    ပြန်ပေး cursor;
}

static Cursor X11_CreateAnimatedXCursorCursor(SDL_CursorFrameInfo *frames, ကိန်းပြည့် num_frames, ကိန်းပြည့် hot_x, ကိန်းပြည့် hot_y)
{
    Cursor cursor = None;
    XcursorImages *images;

    images = X11_XcursorImagesCreate(num_frames);
    အကယ်၍ (!images) {
        SDL_OutOfMemory();
        ပြန်ပေး None;
    }

    အတွက် (ကိန်းပြည့် i = 0; i < num_frames; ++i) {
        XcursorImage *image = X11_CreateXCursorImage(frames[i].surface, hot_x, hot_y, frames[i].duration);
        အကယ်၍ (!image) {
            goto cleanup;
        }

        images->images[i] = image;
        images->nimage++;
    }

    cursor = X11_XcursorImagesLoadCursor(GetDisplay(), images);

cleanup:
    X11_XcursorImagesDestroy(images);
    ပြန်ပေး cursor;
}
#endif // SDL_VIDEO_DRIVER_X11_XCURSOR

static Cursor X11_CreatePixmapCursor(SDL_Surface *surface, ကိန်းပြည့် hot_x, ကိန်းပြည့် hot_y)
{
    Display *display = GetDisplay();
    XColor fg, bg;
    Cursor cursor = None;
    Uint32 *ptr;
    Uint8 *data_bits, *mask_bits;
    Pixmap data_pixmap, mask_pixmap;
    ကိန်းပြည့် x, y;
    unsigned ကိန်းပြည့် rfg, gfg, bfg, rbg, gbg, bbg, fgBits, bgBits;
    size_t width_bytes = ((surface->w + 7) & ~((size_t)7)) / 8;

    data_bits = SDL_calloc(1, surface->h * width_bytes);
    အကယ်၍ (!data_bits) {
        ပြန်ပေး None;
    }

    mask_bits = SDL_calloc(1, surface->h * width_bytes);
    အကယ်၍ (!mask_bits) {
        SDL_free(data_bits);
        ပြန်ပေး None;
    }

    // Code below assumes ARGB pixel format
    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);

    rfg = gfg = bfg = rbg = gbg = bbg = fgBits = bgBits = 0;
    အတွက် (y = 0; y < surface->h; ++y) {
        ptr = (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch);
        အတွက် (x = 0; x < surface->w; ++x) {
            ကိန်းပြည့် alpha = (*ptr >> 24) & 0xff;
            ကိန်းပြည့် red = (*ptr >> 16) & 0xff;
            ကိန်းပြည့် green = (*ptr >> 8) & 0xff;
            ကိန်းပြည့် blue = (*ptr >> 0) & 0xff;
            အကယ်၍ (alpha > 25) {
                mask_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));

                အကယ်၍ ((red + green + blue) > 0x40) {
                    fgBits++;
                    rfg += red;
                    gfg += green;
                    bfg += blue;
                    data_bits[y * width_bytes + x / 8] |= (0x01 << (x % 8));
                } မဟုတ်ပါက {
                    bgBits++;
                    rbg += red;
                    gbg += green;
                    bbg += blue;
                }
            }
            ++ptr;
        }
    }

    အကယ်၍ (fgBits) {
        fg.red = rfg * 257 / fgBits;
        fg.green = gfg * 257 / fgBits;
        fg.blue = bfg * 257 / fgBits;
    } မဟုတ်ပါက {
        fg.red = fg.green = fg.blue = 0;
    }

    အကယ်၍ (bgBits) {
        bg.red = rbg * 257 / bgBits;
        bg.green = gbg * 257 / bgBits;
        bg.blue = bbg * 257 / bgBits;
    } မဟုတ်ပါက {
        bg.red = bg.green = bg.blue = 0;
    }

    data_pixmap = X11_XCreateBitmapFromData(display, DefaultRootWindow(display),
                                            (var_na *)data_bits,
                                            surface->w, surface->h);
    mask_pixmap = X11_XCreateBitmapFromData(display, DefaultRootWindow(display),
                                            (var_na *)mask_bits,
                                            surface->w, surface->h);
    cursor = X11_XCreatePixmapCursor(display, data_pixmap, mask_pixmap,
                                     &fg, &bg, hot_x, hot_y);
    X11_XFreePixmap(display, data_pixmap);
    X11_XFreePixmap(display, mask_pixmap);
    SDL_free(data_bits);
    SDL_free(mask_bits);

    ပြန်ပေး cursor;
}

static SDL_Cursor *X11_CreateCursor(SDL_Surface *surface, ကိန်းပြည့် hot_x, ကိန်းပြည့် hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    အကယ်၍ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateXCursorCursor(surface, hot_x, hot_y);
    }
#endif
    အကယ်၍ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(surface, hot_x, hot_y);
    }
    ပြန်ပေး X11_CreateCursorAndData(x11_cursor);
}

static SDL_Cursor *X11_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, ကိန်းပြည့် num_frames, ကိန်းပြည့် hot_x, ကိန်းပြည့် hot_y)
{
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    အကယ်၍ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_CreateAnimatedXCursorCursor(frames, num_frames, hot_x, hot_y);
    }
#endif
    အကယ်၍ (x11_cursor == None) {
        x11_cursor = X11_CreatePixmapCursor(frames[0].surface, hot_x, hot_y);
    }

    ပြန်ပေး X11_CreateCursorAndData(x11_cursor);
}

static unsigned ကိန်းပြည့် GetLegacySystemCursorShape(SDL_SystemCursor id)
{
    switch (id) {
        // X Font Cursors reference:
        // http://tronche.com/gui/x/xlib/appendix/b/
        pak_sa SDL_SYSTEM_CURSOR_DEFAULT: ပြန်ပေး XC_left_ptr;
        pak_sa SDL_SYSTEM_CURSOR_TEXT: ပြန်ပေး XC_xterm;
        pak_sa SDL_SYSTEM_CURSOR_WAIT: ပြန်ပေး XC_watch;
        pak_sa SDL_SYSTEM_CURSOR_CROSSHAIR: ပြန်ပေး XC_tcross;
        pak_sa SDL_SYSTEM_CURSOR_PROGRESS: ပြန်ပေး XC_watch;
        pak_sa SDL_SYSTEM_CURSOR_NWSE_RESIZE: ပြန်ပေး XC_top_left_corner;
        pak_sa SDL_SYSTEM_CURSOR_NESW_RESIZE: ပြန်ပေး XC_top_right_corner;
        pak_sa SDL_SYSTEM_CURSOR_EW_RESIZE: ပြန်ပေး XC_sb_h_double_arrow;
        pak_sa SDL_SYSTEM_CURSOR_NS_RESIZE: ပြန်ပေး XC_sb_v_double_arrow;
        pak_sa SDL_SYSTEM_CURSOR_MOVE: ပြန်ပေး XC_fleur;
        pak_sa SDL_SYSTEM_CURSOR_NOT_ALLOWED: ပြန်ပေး XC_pirate;
        pak_sa SDL_SYSTEM_CURSOR_POINTER: ပြန်ပေး XC_hand2;
        pak_sa SDL_SYSTEM_CURSOR_NW_RESIZE: ပြန်ပေး XC_top_left_corner;
        pak_sa SDL_SYSTEM_CURSOR_N_RESIZE: ပြန်ပေး XC_top_side;
        pak_sa SDL_SYSTEM_CURSOR_NE_RESIZE: ပြန်ပေး XC_top_right_corner;
        pak_sa SDL_SYSTEM_CURSOR_E_RESIZE: ပြန်ပေး XC_right_side;
        pak_sa SDL_SYSTEM_CURSOR_SE_RESIZE: ပြန်ပေး XC_bottom_right_corner;
        pak_sa SDL_SYSTEM_CURSOR_S_RESIZE: ပြန်ပေး XC_bottom_side;
        pak_sa SDL_SYSTEM_CURSOR_SW_RESIZE: ပြန်ပေး XC_bottom_left_corner;
        pak_sa SDL_SYSTEM_CURSOR_W_RESIZE: ပြန်ပေး XC_left_side;
        pak_sa SDL_SYSTEM_CURSOR_CONTEXT_MENU: ပြန်ပေး XC_hand2;
        pak_sa SDL_SYSTEM_CURSOR_HELP: ပြန်ပေး XC_question_arrow;
        pak_sa SDL_SYSTEM_CURSOR_CELL: ပြန်ပေး XC_cross;
        pak_sa SDL_SYSTEM_CURSOR_VERTICAL_TEXT: ပြန်ပေး XC_xterm;
        pak_sa SDL_SYSTEM_CURSOR_ALIAS: ပြန်ပေး XC_hand2;
        pak_sa SDL_SYSTEM_CURSOR_COPY: ပြန်ပေး XC_hand2;
        pak_sa SDL_SYSTEM_CURSOR_NO_DROP: ပြန်ပေး XC_pirate;
        pak_sa SDL_SYSTEM_CURSOR_GRAB: ပြန်ပေး XC_hand2;
        pak_sa SDL_SYSTEM_CURSOR_GRABBING: ပြန်ပေး XC_hand2;
        pak_sa SDL_SYSTEM_CURSOR_COL_RESIZE: ပြန်ပေး XC_sb_h_double_arrow;
        pak_sa SDL_SYSTEM_CURSOR_ROW_RESIZE: ပြန်ပေး XC_sb_v_double_arrow;
        pak_sa SDL_SYSTEM_CURSOR_ALL_SCROLL: ပြန်ပေး XC_fleur;
        pak_sa SDL_SYSTEM_CURSOR_ZOOM_IN: ပြန်ပေး XC_hand2;
        pak_sa SDL_SYSTEM_CURSOR_ZOOM_OUT: ပြန်ပေး XC_hand2;
        pak_sa SDL_SYSTEM_CURSOR_COUNT: bha_nga;  // so the compiler might notice if an enum value is missing here.
    }

    SDL_assert(0);
    ပြန်ပေး 0;
}

static SDL_Cursor *X11_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = NULL;
    Display *dpy = GetDisplay();
    Cursor x11_cursor = None;

#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
    အကယ်၍ (SDL_X11_HAVE_XCURSOR) {
        x11_cursor = X11_XcursorLibraryLoadCursor(dpy, SDL_GetCSSCursorName(id, NULL));
    }
#endif

    အကယ်၍ (x11_cursor == None) {
        x11_cursor = X11_XCreateFontCursor(dpy, GetLegacySystemCursorShape(id));
    }

    အကယ်၍ (x11_cursor != None) {
        cursor = X11_CreateCursorAndData(x11_cursor);
    }

    ပြန်ပေး cursor;
}

static SDL_Cursor *X11_CreateDefaultCursor(void)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ပြန်ပေး X11_CreateSystemCursor(id);
}

static void X11_FreeCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = cursor->internal->cursor;

    အကယ်၍ (x11_cursor != None) {
        X11_XFreeCursor(GetDisplay(), x11_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

static bool X11_ShowCursor(SDL_Cursor *cursor)
{
    Cursor x11_cursor = 0;

    အကယ်၍ (cursor) {
        x11_cursor = cursor->internal->cursor;
    } မဟုတ်ပါက {
        x11_cursor = X11_CreateEmptyCursor();
    }

    // FIXME: Is there a better way than this?
    {
        SDL_VideoDevice *video = SDL_GetVideoDevice();
        Display *display = GetDisplay();
        SDL_Window *window;

        x11_cursor_visible = !!cursor;

        အတွက် (window = video->windows; window; window = window->next) {
            SDL_WindowData *data = window->internal;
            အကယ်၍ (data) {
                အကယ်၍ (x11_cursor != None) {
                    X11_XDefineCursor(display, data->xwindow, x11_cursor);
                } မဟုတ်ပါက {
                    X11_XUndefineCursor(display, data->xwindow);
                }
            }
        }
        X11_XFlush(display);
    }
    ပြန်ပေး true;
}

static void X11_WarpMouseInternal(Window xwindow, float x, float y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    Display *display = videodata->display;
    bool warp_hack = false;

    // XWayland will only warp the cursor if it is hidden, so this workaround is required.
    အကယ်၍ (videodata->is_xwayland && x11_cursor_visible) {
        warp_hack = true;
    }

    အကယ်၍ (warp_hack) {
        X11_ShowCursor(NULL);
    }
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
    ကိန်းပြည့် deviceid = 0;
    အကယ်၍ (X11_Xinput2IsInitialized()) {
        /* It seems XIWarpPointer() doesn't work correctly on multi-head setups:
         * https://developer.blender.org/rB165caafb99c6846e53d11c4e966990aaffc06cea
         */
        အကယ်၍ (ScreenCount(display) == 1) {
            X11_XIGetClientPointer(display, None, &deviceid);
        }
    }
    အကယ်၍ (deviceid != 0) {
        SDL_assert(SDL_X11_HAVE_XINPUT2);
        X11_XIWarpPointer(display, deviceid, None, xwindow, 0.0, 0.0, 0, 0, x, y);
    } မဟုတ်ပါက
#endif
    {
        X11_XWarpPointer(display, None, xwindow, 0, 0, 0, 0, (ကိန်းပြည့်)x, (ကိန်းပြည့်)y);
    }

    အကယ်၍ (warp_hack) {
        X11_ShowCursor(SDL_GetCursor());
    }
    X11_XSync(display, False);
    videodata->global_mouse_changed = true;
}

static bool X11_WarpMouse(SDL_Window *window, float x, float y)
{
    SDL_WindowData *data = window->internal;

    အကယ်၍ (X11_WarpMouseXTest(SDL_GetVideoDevice(), window, x, y)) {
        ပြန်ပေး true;
    }

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
    // If we have no barrier, we need to warp
    အကယ်၍ (data->pointer_barrier_active == false) {
        X11_WarpMouseInternal(data->xwindow, x, y);
    }
#မဟုတ်ပါက
    X11_WarpMouseInternal(data->xwindow, x, y);
#endif
    ပြန်ပေး true;
}

static bool X11_WarpMouseGlobal(float x, float y)
{
    အကယ်၍ (X11_WarpMouseXTest(SDL_GetVideoDevice(), NULL, x, y)) {
        ပြန်ပေး true;
    }

    X11_WarpMouseInternal(DefaultRootWindow(GetDisplay()), x, y);
    ပြန်ပေး true;
}

static bool X11_SetRelativeMouseMode(bool enabled)
{
    အကယ်၍ (!X11_Xinput2IsInitialized()) {
        ပြန်ပေး SDL_Unsupported();
    }
    ပြန်ပေး true;
}

static bool X11_CaptureMouse(SDL_Window *window)
{
    Display *display = GetDisplay();
    SDL_Window *mouse_focus = SDL_GetMouseFocus();

    အကယ်၍ (window) {
        SDL_WindowData *data = window->internal;

        /* If XInput2 is handling the pointer input, non-confinement grabs will always fail with 'AlreadyGrabbed',
         * since the pointer is being grabbed by XInput2.
         */
        အကယ်၍ (!data->xinput2_mouse_enabled || data->mouse_grabbed) {
            const unsigned ကိန်းပြည့် mask = ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask;
            Window confined = (data->mouse_grabbed ? data->xwindow : None);
            const ကိန်းပြည့် rc = X11_XGrabPointer(display, data->xwindow, False,
                                            mask, GrabModeAsync, GrabModeAsync,
                                            confined, None, CurrentTime);
            အကယ်၍ (rc != GrabSuccess) {
                ပြန်ပေး SDL_SetError("X server refused mouse capture");
            }

            အကယ်၍ (data->mouse_grabbed) {
                // XGrabPointer can warp the cursor when confining, so update the coordinates.
                data->videodata->global_mouse_changed = true;
            }
        }
    } မဟုတ်ပါက အကယ်၍ (mouse_focus) {
        SDL_UpdateWindowGrab(mouse_focus);
    } မဟုတ်ပါက {
        X11_XUngrabPointer(display, CurrentTime);
    }

    X11_XSync(display, False);

    ပြန်ပေး true;
}

static SDL_MouseButtonFlags X11_GetGlobalMouseState(float *x, float *y)
{
    SDL_VideoData *videodata = SDL_GetVideoDevice()->internal;
    SDL_DisplayID *displays;
    Display *display = GetDisplay();
    ကိန်းပြည့် i;

    // !!! FIXME: should we XSync() here first?

    အကယ်၍ (!X11_Xinput2IsInitialized()) {
        videodata->global_mouse_changed = true;
    }

    // check if we have this cached since XInput last saw the mouse move.
    // !!! FIXME: can we just calculate this from XInput's events?
    အကယ်၍ (videodata->global_mouse_changed) {
        displays = SDL_GetDisplays(NULL);
        အကယ်၍ (displays) {
            အတွက် (i = 0; displays[i]; ++i) {
                SDL_DisplayData *data = SDL_GetDisplayDriverData(displays[i]);
                အကယ်၍ (data) {
                    Window root, child;
                    ကိန်းပြည့် rootx, rooty, winx, winy;
                    unsigned ကိန်းပြည့် mask;
                    အကယ်၍ (X11_XQueryPointer(display, RootWindow(display, data->screen), &root, &child, &rootx, &rooty, &winx, &winy, &mask)) {
                        XWindowAttributes root_attrs;
                        SDL_MouseButtonFlags buttons = 0;
                        buttons |= (mask & Button1Mask) ? SDL_BUTTON_LMASK : 0;
                        buttons |= (mask & Button2Mask) ? SDL_BUTTON_MMASK : 0;
                        buttons |= (mask & Button3Mask) ? SDL_BUTTON_RMASK : 0;
                        // Use the SDL state for the extended buttons - it's better than nothing
                        buttons |= (SDL_GetMouseState(NULL, NULL) & (SDL_BUTTON_X1MASK | SDL_BUTTON_X2MASK));
                        /* SDL_DisplayData->x,y point to screen origin, and adding them to mouse coordinates relative to root window doesn't do the right thing
                         * (observed on dual monitor setup with primary display being the rightmost one - mouse was offset to the right).
                         *
                         * Adding root position to root-relative coordinates seems to be a better way to get absolute position. */
                        X11_XGetWindowAttributes(display, root, &root_attrs);
                        videodata->global_mouse_position.x = root_attrs.x + rootx;
                        videodata->global_mouse_position.y = root_attrs.y + rooty;
                        videodata->global_mouse_buttons = buttons;
                        videodata->global_mouse_changed = false;
                        bha_nga;
                    }
                }
            }
            SDL_free(displays);
        }
    }

    SDL_assert(!videodata->global_mouse_changed); // The pointer wasn't on any X11 screen?!

    *x = (float)videodata->global_mouse_position.x;
    *y = (float)videodata->global_mouse_position.y;
    ပြန်ပေး videodata->global_mouse_buttons;
}

void X11_InitMouse(SDL_VideoDevice *_this)
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
    နေစဉ် (r <= SDL_HITTEST_RESIZE_LEFT) {
        switch (r) {
        pak_sa SDL_HITTEST_NORMAL: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); bha_nga;
        pak_sa SDL_HITTEST_DRAGGABLE: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT); bha_nga;
        pak_sa SDL_HITTEST_RESIZE_TOPLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NW_RESIZE); bha_nga;
        pak_sa SDL_HITTEST_RESIZE_TOP: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_N_RESIZE); bha_nga;
        pak_sa SDL_HITTEST_RESIZE_TOPRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_NE_RESIZE); bha_nga;
        pak_sa SDL_HITTEST_RESIZE_RIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_E_RESIZE); bha_nga;
        pak_sa SDL_HITTEST_RESIZE_BOTTOMRIGHT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SE_RESIZE); bha_nga;
        pak_sa SDL_HITTEST_RESIZE_BOTTOM: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_S_RESIZE); bha_nga;
        pak_sa SDL_HITTEST_RESIZE_BOTTOMLEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_SW_RESIZE); bha_nga;
        pak_sa SDL_HITTEST_RESIZE_LEFT: sys_cursors[r] = X11_CreateSystemCursor(SDL_SYSTEM_CURSOR_W_RESIZE); bha_nga;
        }
        r++;
    }

    SDL_SetDefaultCursor(X11_CreateDefaultCursor());
}

void X11_QuitMouse(SDL_VideoDevice *_this)
{
    အတွက် (ကိန်းပြည့် i = 0; i < SDL_arraysize(sys_cursors); i++) {
        အကယ်၍ (sys_cursors[i]) {
            X11_FreeCursor(sys_cursors[i]);
            sys_cursors[i] = NULL;
        }
    }

    X11_DestroyEmptyCursor();
}

void X11_SetHitTestCursor(SDL_HitTestResult rc)
{
    အကယ်၍ (rc == SDL_HITTEST_NORMAL || rc == SDL_HITTEST_DRAGGABLE) {
        SDL_RedrawCursor();
    } မဟုတ်ပါက {
        X11_ShowCursor(sys_cursors[rc]);
    }
}

#endif // SDL_VIDEO_DRIVER_X11
