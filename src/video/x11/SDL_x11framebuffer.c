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

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11framebuffer.h"
#ضمن "SDL_x11xsync.h"

#که_نه_تعریف_شوی NO_SHARED_حافظه

// Shared memory error handler routine
ساكن صحيح shm_error;
ساكن صحيح (*X_handler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح shm_errhandler(Display *d, XErrorEvent *e)
{
    إذا (e->error_کوډ == BadAccess || e->error_کوډ == BadRequest) {
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

#د_که_پای // !NO_SHARED_MEMORY

bool X11_Create_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, SDL_PixelFormat *format,
                                فراغ **pixels, صحيح *pitch)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    صحيح w, h;

    SDL_Get_کړکۍ_اندازه_دننه_Pixels(کړکۍ, &w, &h);

    // Free the old framebuffer surface
    X11_Destroy_کړکۍ_Framebuffer(_this, کړکۍ);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    معلومات->gc = X11_XCreateGC(display, معلومات->xwindow, GCGraphicsExposures, &gcv);
    إذا (!معلومات->gc) {
        أرجع SDL_سېټ_Error("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    إذا (!X11_GetVisualInfoFromVisual(display, معلومات->visual, &vinfo)) {
        أرجع SDL_سېټ_Error("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    إذا (*format == SDL_PIXELFORMAT_UNKNOWN) {
        أرجع SDL_سېټ_Error("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#که_نه_تعریف_شوی NO_SHARED_حافظه
    إذا (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &معلومات->shminfo;

        shminfo->shmid = shmget(IPC_شخصي, (size_t)h * (*pitch), IPC_CREAT | 0777);
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
            معلومات->ximage = X11_XShmCreateImage(display, معلومات->visual,
                                               vinfo.ژوروالی_2, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            إذا (!معلومات->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } وإلا {
                // Done!
                معلومات->ximage->byte_ترتیب = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                معلومات->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                أرجع true;
            }
        }
    }
#د_که_پای // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    إذا (!*pixels) {
        أرجع false;
    }

    معلومات->ximage = X11_XCreateImage(display, معلومات->visual,
                                    vinfo.ژوروالی_2, ZPixmap, 0, (حرف *)(*pixels),
                                    w, h, 32, 0);
    إذا (!معلومات->ximage) {
        SDL_free(*pixels);
        أرجع SDL_سېټ_Error("Couldn't create XImage");
    }
    معلومات->ximage->byte_ترتیب = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    أرجع true;
}

bool X11_Update_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ, ثابت SDL_Rect *rects,
                                صحيح numrects)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display = معلومات->videodata->display;
    صحيح i;
    صحيح x, y, w, h;
    صحيح کړکۍ_w, کړکۍ_h;

    SDL_Get_کړکۍ_اندازه_دننه_Pixels(کړکۍ, &کړکۍ_w, &کړکۍ_h);

#که_نه_تعریف_شوی NO_SHARED_حافظه
    إذا (معلومات->use_mitshm) {
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
            إذا (x + w > کړکۍ_w) {
                w = کړکۍ_w - x;
            }
            إذا (y + h > کړکۍ_h) {
                h = کړکۍ_h - y;
            }

            X11_XShmPutImage(display, معلومات->xwindow, معلومات->gc, معلومات->ximage,
                             x, y, x, y, w, h, False);
        }
    } وإلا
#د_که_پای // !NO_SHARED_MEMORY
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
            إذا (x + w > کړکۍ_w) {
                w = کړکۍ_w - x;
            }
            إذا (y + h > کړکۍ_h) {
                h = کړکۍ_h - y;
            }

            X11_XPutImage(display, معلومات->xwindow, معلومات->gc, معلومات->ximage,
                          x, y, x, y, w, h);
        }
    }

#که_تعریف_شوی SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(معلومات->کړکۍ);
#د_که_پای /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    أرجع true;
}

فراغ X11_Destroy_کړکۍ_Framebuffer(SDL_VideoDevice *_this, SDL_کړکۍ *کړکۍ)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    Display *display;

    إذا (!معلومات) {
        // The window wasn't fully initialized
        أرجع;
    }

    display = معلومات->videodata->display;

    إذا (معلومات->ximage) {
        XDestroyImage(معلومات->ximage);

#که_نه_تعریف_شوی NO_SHARED_حافظه
        إذا (معلومات->use_mitshm) {
            X11_XShmDetach(display, &معلومات->shminfo);
            X11_XSync(display, False);
            shmdt(معلومات->shminfo.shmaddr);
            معلومات->use_mitshm = false;
        }
#د_که_پای // !NO_SHARED_MEMORY

        معلومات->ximage = عدم;
    }
    إذا (معلومات->gc) {
        X11_XFreeGC(display, معلومات->gc);
        معلومات->gc = عدم;
    }
}

#د_که_پای // SDL_VIDEO_DRIVER_X11
