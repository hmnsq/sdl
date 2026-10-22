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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11framebuffer.h"
#ضمن "SDL_x11xsync.h"

#جے_بنا_تعریف NO_SHARED_حافظہ

// Shared memory error handler routine
ساكن صحيح shm_error;
ساكن صحيح (*X_handler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح shm_errhandler(Display *d, XErrorEvent *e)
{
    إذا (e->error_کوڈ == BadAccess || e->error_کوڈ == BadRequest) {
        shm_error = True;
        أرجع 0;
    }
    أرجع X_handler(d, e);
}

ساكن bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    أرجع X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#جے_انت // !NO_SHARED_MEMORY

bool X11_Create_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, SDL_PixelFormat *format,
                                فراغ **pixels, صحيح *pitch)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    صحيح w, h;

    SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &w, &h);

    // Free the old framebuffer surface
    X11_Destroy_کھڑکی_Framebuffer(_this, کھڑکی);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    انکڑے->gc = X11_XCreateGC(display, انکڑے->xwindow, GCGraphicsExposures, &gcv);
    إذا (!انکڑے->gc) {
        أرجع SDL_سیٹ_Error("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    إذا (!X11_GetVisualInfoFromVisual(display, انکڑے->visual, &vinfo)) {
        أرجع SDL_سیٹ_Error("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    إذا (*format == SDL_PIXELFORMAT_UNKNOWN) {
        أرجع SDL_سیٹ_Error("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#جے_بنا_تعریف NO_SHARED_حافظہ
    إذا (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &انکڑے->shminfo;

        shminfo->shmid = shmget(IPC_نجی, (size_t)h * (*pitch), IPC_CREAT | 0777);
        إذا (shminfo->shmid >= 0) {
            shminfo->shmaddr = (حرف *)shmat(shminfo->shmid, عدم, 0);
            shminfo->readOnly = False;
            إذا (shminfo->shmaddr != (حرف *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                إذا (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } وإلا {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, عدم);
        } وإلا {
            shm_error = True;
        }
        إذا (!shm_error) {
            انکڑے->ximage = X11_XShmCreateImage(display, انکڑے->visual,
                                               vinfo.ڈونگھائی_2, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            إذا (!انکڑے->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } وإلا {
                // Done!
                انکڑے->ximage->byte_ترتیب = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                انکڑے->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                أرجع true;
            }
        }
    }
#جے_انت // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    إذا (!*pixels) {
        أرجع false;
    }

    انکڑے->ximage = X11_XCreateImage(display, انکڑے->visual,
                                    vinfo.ڈونگھائی_2, ZPixmap, 0, (حرف *)(*pixels),
                                    w, h, 32, 0);
    إذا (!انکڑے->ximage) {
        SDL_free(*pixels);
        أرجع SDL_سیٹ_Error("Couldn't create XImage");
    }
    انکڑے->ximage->byte_ترتیب = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    أرجع true;
}

bool X11_Update_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, ثابت SDL_Rect *rects,
                                صحيح numrects)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display = انکڑے->videodata->display;
    صحيح i;
    صحيح x, y, w, h;
    صحيح کھڑکی_w, کھڑکی_h;

    SDL_Get_کھڑکی_ناپ_وچ_Pixels(کھڑکی, &کھڑکی_w, &کھڑکی_h);

#جے_بنا_تعریف NO_SHARED_حافظہ
    إذا (انکڑے->use_mitshm) {
        لكل (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            إذا (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                استمر;
            }
            إذا (x < 0) {
                x += w;
                w += rects[i].x;
            }
            إذا (y < 0) {
                y += h;
                h += rects[i].y;
            }
            إذا (x + w > کھڑکی_w) {
                w = کھڑکی_w - x;
            }
            إذا (y + h > کھڑکی_h) {
                h = کھڑکی_h - y;
            }

            X11_XShmPutImage(display, انکڑے->xwindow, انکڑے->gc, انکڑے->ximage,
                             x, y, x, y, w, h, False);
        }
    } وإلا
#جے_انت // !NO_SHARED_MEMORY
    {
        لكل (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            إذا (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                استمر;
            }
            إذا (x < 0) {
                x += w;
                w += rects[i].x;
            }
            إذا (y < 0) {
                y += h;
                h += rects[i].y;
            }
            إذا (x + w > کھڑکی_w) {
                w = کھڑکی_w - x;
            }
            إذا (y + h > کھڑکی_h) {
                h = کھڑکی_h - y;
            }

            X11_XPutImage(display, انکڑے->xwindow, انکڑے->gc, انکڑے->ximage,
                          x, y, x, y, w, h);
        }
    }

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(انکڑے->کھڑکی);
#جے_انت /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    أرجع true;
}

فراغ X11_Destroy_کھڑکی_Framebuffer(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    Display *display;

    إذا (!انکڑے) {
        // The window wasn't fully initialized
        أرجع;
    }

    display = انکڑے->videodata->display;

    إذا (انکڑے->ximage) {
        XDestroyImage(انکڑے->ximage);

#جے_بنا_تعریف NO_SHARED_حافظہ
        إذا (انکڑے->use_mitshm) {
            X11_XShmDetach(display, &انکڑے->shminfo);
            X11_XSync(display, False);
            shmdt(انکڑے->shminfo.shmaddr);
            انکڑے->use_mitshm = false;
        }
#جے_انت // !NO_SHARED_MEMORY

        انکڑے->ximage = عدم;
    }
    إذا (انکڑے->gc) {
        X11_XFreeGC(display, انکڑے->gc);
        انکڑے->gc = عدم;
    }
}

#جے_انت // SDL_VIDEO_DRIVER_X11
