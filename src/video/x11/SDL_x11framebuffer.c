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

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11framebuffer.h"
#ضمن "SDL_x11xsync.h"

#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري

// Shared memory error handler routine
ساكن صحيح shm_error;
ساكن صحيح (*X_handler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح shm_errhandler(Display *d, XErrorEvent *e)
{
    إذا (e->error_ڪوڊ == BadAccess || e->error_ڪوڊ == BadRequest) {
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

#جيڪڏهن_پورو // !NO_SHARED_MEMORY

bool X11_Create_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, SDL_PixelFormat *format,
                                فراغ **pixels, صحيح *pitch)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    صحيح w, h;

    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &w, &h);

    // Free the old framebuffer surface
    X11_Destroy_دري_Framebuffer(_this, دري);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    معلومات->gc = X11_XCreateGC(display, معلومات->xwindow, GCGraphicsExposures, &gcv);
    إذا (!معلومات->gc) {
        أرجع SDL_سيٽ_Error("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    إذا (!X11_GetVisualInfoFromVisual(display, معلومات->visual, &vinfo)) {
        أرجع SDL_سيٽ_Error("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    إذا (*format == SDL_PIXELFORMAT_UNKNOWN) {
        أرجع SDL_سيٽ_Error("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري
    إذا (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &معلومات->shminfo;

        shminfo->shmid = shmget(IPC_ذاتي, (size_t)h * (*pitch), IPC_CREAT | 0777);
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
                                               vinfo.اونهائي_2, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            إذا (!معلومات->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } وإلا {
                // Done!
                معلومات->ximage->byte_ترتيب = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                معلومات->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                أرجع true;
            }
        }
    }
#جيڪڏهن_پورو // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    إذا (!*pixels) {
        أرجع false;
    }

    معلومات->ximage = X11_XCreateImage(display, معلومات->visual,
                                    vinfo.اونهائي_2, ZPixmap, 0, (حرف *)(*pixels),
                                    w, h, 32, 0);
    إذا (!معلومات->ximage) {
        SDL_free(*pixels);
        أرجع SDL_سيٽ_Error("Couldn't create XImage");
    }
    معلومات->ximage->byte_ترتيب = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    أرجع true;
}

bool X11_Update_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري, ثابت SDL_Rect *rects,
                                صحيح numrects)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display = معلومات->videodata->display;
    صحيح i;
    صحيح x, y, w, h;
    صحيح دري_w, دري_h;

    SDL_Get_دري_سائيز_اندريون_Pixels(دري, &دري_w, &دري_h);

#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري
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
            إذا (x + w > دري_w) {
                w = دري_w - x;
            }
            إذا (y + h > دري_h) {
                h = دري_h - y;
            }

            X11_XShmPutImage(display, معلومات->xwindow, معلومات->gc, معلومات->ximage,
                             x, y, x, y, w, h, False);
        }
    } وإلا
#جيڪڏهن_پورو // !NO_SHARED_MEMORY
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
            إذا (x + w > دري_w) {
                w = دري_w - x;
            }
            إذا (y + h > دري_h) {
                h = دري_h - y;
            }

            X11_XPutImage(display, معلومات->xwindow, معلومات->gc, معلومات->ximage,
                          x, y, x, y, w, h);
        }
    }

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(معلومات->دري);
#جيڪڏهن_پورو /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    أرجع true;
}

فراغ X11_Destroy_دري_Framebuffer(SDL_VideoDevice *_this, SDL_دري *دري)
{
    SDL_دري_معلومات *معلومات = دري->اندروني;
    Display *display;

    إذا (!معلومات) {
        // The window wasn't fully initialized
        أرجع;
    }

    display = معلومات->videodata->display;

    إذا (معلومات->ximage) {
        XDestroyImage(معلومات->ximage);

#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري
        إذا (معلومات->use_mitshm) {
            X11_XShmDetach(display, &معلومات->shminfo);
            X11_XSync(display, False);
            shmdt(معلومات->shminfo.shmaddr);
            معلومات->use_mitshm = false;
        }
#جيڪڏهن_پورو // !NO_SHARED_MEMORY

        معلومات->ximage = عدم;
    }
    إذا (معلومات->gc) {
        X11_XFreeGC(display, معلومات->gc);
        معلومات->gc = عدم;
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_X11
