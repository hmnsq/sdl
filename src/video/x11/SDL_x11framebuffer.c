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

#شامل "SDL_x11video.h"
#شامل "SDL_x11framebuffer.h"
#شامل "SDL_x11xsync.h"

#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ

// Shared memory error handler routine
ساکن صحیح shm_error;
ساکن صحیح (*X_handler)(Display *, XErrorEvent *) = تہی;
ساکن صحیح shm_errhandler(Display *d, XErrorEvent *e)
{
    اگر (e->error_رمز == BadAccess || e->error_رمز == BadRequest) {
        shm_error = True;
        واپس 0;
    }
    واپس X_handler(d, e);
}

ساکن bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    واپس X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#اگر_ختم // !NO_SHARED_MEMORY

bool X11_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format,
                                خالی **pixels, صحیح *pitch)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    صحیح w, h;

    SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &w, &h);

    // Free the old framebuffer surface
    X11_Destroy_کھڑکی_Framebuffer(_this, کھڑکی);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    ڈیٹا->gc = X11_XCreateGC(display, ڈیٹا->xwindow, GCGraphicsExposures, &gcv);
    اگر (!ڈیٹا->gc) {
        واپس SDL_سیٹ_Error("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    اگر (!X11_GetVisualInfoFromVisual(display, ڈیٹا->visual, &vinfo)) {
        واپس SDL_سیٹ_Error("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    اگر (*format == SDL_PIXELFORMAT_UNKNOWN) {
        واپس SDL_سیٹ_Error("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
    اگر (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &ڈیٹا->shminfo;

        shminfo->shmid = shmget(IPC_نجی, (size_t)h * (*pitch), IPC_CREAT | 0777);
        اگر (shminfo->shmid >= 0) {
            shminfo->shmaddr = (حرف *)shmat(shminfo->shmid, تہی, 0);
            shminfo->readOnly = False;
            اگر (shminfo->shmaddr != (حرف *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                اگر (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } ورنہ {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, تہی);
        } ورنہ {
            shm_error = True;
        }
        اگر (!shm_error) {
            ڈیٹا->ximage = X11_XShmCreateImage(display, ڈیٹا->visual,
                                               vinfo.گہرائی_2, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            اگر (!ڈیٹا->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } ورنہ {
                // Done!
                ڈیٹا->ximage->byte_ترتیب = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                ڈیٹا->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                واپس true;
            }
        }
    }
#اگر_ختم // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    اگر (!*pixels) {
        واپس false;
    }

    ڈیٹا->ximage = X11_XCreateImage(display, ڈیٹا->visual,
                                    vinfo.گہرائی_2, ZPixmap, 0, (حرف *)(*pixels),
                                    w, h, 32, 0);
    اگر (!ڈیٹا->ximage) {
        SDL_free(*pixels);
        واپس SDL_سیٹ_Error("Couldn't create XImage");
    }
    ڈیٹا->ximage->byte_ترتیب = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    واپس true;
}

bool X11_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects,
                                صحیح numrects)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display = ڈیٹا->videodata->display;
    صحیح i;
    صحیح x, y, w, h;
    صحیح کھڑکی_w, کھڑکی_h;

    SDL_Get_کھڑکی_سائز_اندر_Pixels(کھڑکی, &کھڑکی_w, &کھڑکی_h);

#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
    اگر (ڈیٹا->use_mitshm) {
        برائے (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            اگر (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                جاری;
            }
            اگر (x < 0) {
                x += w;
                w += rects[i].x;
            }
            اگر (y < 0) {
                y += h;
                h += rects[i].y;
            }
            اگر (x + w > کھڑکی_w) {
                w = کھڑکی_w - x;
            }
            اگر (y + h > کھڑکی_h) {
                h = کھڑکی_h - y;
            }

            X11_XShmPutImage(display, ڈیٹا->xwindow, ڈیٹا->gc, ڈیٹا->ximage,
                             x, y, x, y, w, h, False);
        }
    } ورنہ
#اگر_ختم // !NO_SHARED_MEMORY
    {
        برائے (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            اگر (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                جاری;
            }
            اگر (x < 0) {
                x += w;
                w += rects[i].x;
            }
            اگر (y < 0) {
                y += h;
                h += rects[i].y;
            }
            اگر (x + w > کھڑکی_w) {
                w = کھڑکی_w - x;
            }
            اگر (y + h > کھڑکی_h) {
                h = کھڑکی_h - y;
            }

            X11_XPutImage(display, ڈیٹا->xwindow, ڈیٹا->gc, ڈیٹا->ximage,
                          x, y, x, y, w, h);
        }
    }

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(ڈیٹا->کھڑکی);
#اگر_ختم /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    واپس true;
}

خالی X11_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
    Display *display;

    اگر (!ڈیٹا) {
        // The window wasn't fully initialized
        واپس;
    }

    display = ڈیٹا->videodata->display;

    اگر (ڈیٹا->ximage) {
        XDestroyImage(ڈیٹا->ximage);

#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
        اگر (ڈیٹا->use_mitshm) {
            X11_XShmDetach(display, &ڈیٹا->shminfo);
            X11_XSync(display, False);
            shmdt(ڈیٹا->shminfo.shmaddr);
            ڈیٹا->use_mitshm = false;
        }
#اگر_ختم // !NO_SHARED_MEMORY

        ڈیٹا->ximage = تہی;
    }
    اگر (ڈیٹا->gc) {
        X11_XFreeGC(display, ڈیٹا->gc);
        ڈیٹا->gc = تہی;
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11
