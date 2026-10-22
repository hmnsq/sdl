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

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11framebuffer.h"
#ضمن "SDL_x11xsync.h"

#اگر_تعریف_نشده NO_SHARED_حافظه

// Shared memory error handler routine
ساكن صحيح shm_error;
ساكن صحيح (*X_handler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح shm_errhandler(Display *d, XErrorEvent *e)
{
    إذا (e->error_کد == BadAccess || e->error_کد == BadRequest) {
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

#پایان_اگر // !NO_SHARED_MEMORY

bool X11_Create_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره, SDL_PixelFormat *format,
                                فراغ **pixels, صحيح *pitch)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    صحيح w, h;

    SDL_Get_پنجره_اندازه_درون_Pixels(پنجره, &w, &h);

    // Free the old framebuffer surface
    X11_Destroy_پنجره_Framebuffer(_this, پنجره);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    داده->gc = X11_XCreateGC(display, داده->xwindow, GCGraphicsExposures, &gcv);
    إذا (!داده->gc) {
        أرجع SDL_مجموعه_Error("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    إذا (!X11_GetVisualInfoFromVisual(display, داده->visual, &vinfo)) {
        أرجع SDL_مجموعه_Error("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    إذا (*format == SDL_PIXELFORMAT_UNKNOWN) {
        أرجع SDL_مجموعه_Error("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#اگر_تعریف_نشده NO_SHARED_حافظه
    إذا (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &داده->shminfo;

        shminfo->shmid = shmget(IPC_خصوصی, (size_t)h * (*pitch), IPC_CREAT | 0777);
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
            داده->ximage = X11_XShmCreateImage(display, داده->visual,
                                               vinfo.عمق_2, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            إذا (!داده->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } وإلا {
                // Done!
                داده->ximage->byte_ترتیب = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                داده->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                أرجع true;
            }
        }
    }
#پایان_اگر // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    إذا (!*pixels) {
        أرجع false;
    }

    داده->ximage = X11_XCreateImage(display, داده->visual,
                                    vinfo.عمق_2, ZPixmap, 0, (حرف *)(*pixels),
                                    w, h, 32, 0);
    إذا (!داده->ximage) {
        SDL_free(*pixels);
        أرجع SDL_مجموعه_Error("Couldn't create XImage");
    }
    داده->ximage->byte_ترتیب = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    أرجع true;
}

bool X11_Update_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره, ثابت SDL_Rect *rects,
                                صحيح numrects)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display = داده->videodata->display;
    صحيح i;
    صحيح x, y, w, h;
    صحيح پنجره_w, پنجره_h;

    SDL_Get_پنجره_اندازه_درون_Pixels(پنجره, &پنجره_w, &پنجره_h);

#اگر_تعریف_نشده NO_SHARED_حافظه
    إذا (داده->use_mitshm) {
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
            إذا (x + w > پنجره_w) {
                w = پنجره_w - x;
            }
            إذا (y + h > پنجره_h) {
                h = پنجره_h - y;
            }

            X11_XShmPutImage(display, داده->xwindow, داده->gc, داده->ximage,
                             x, y, x, y, w, h, False);
        }
    } وإلا
#پایان_اگر // !NO_SHARED_MEMORY
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
            إذا (x + w > پنجره_w) {
                w = پنجره_w - x;
            }
            إذا (y + h > پنجره_h) {
                h = پنجره_h - y;
            }

            X11_XPutImage(display, داده->xwindow, داده->gc, داده->ximage,
                          x, y, x, y, w, h);
        }
    }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(داده->پنجره);
#پایان_اگر /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    أرجع true;
}

فراغ X11_Destroy_پنجره_Framebuffer(SDL_VideoDevice *_this, SDL_پنجره *پنجره)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    Display *display;

    إذا (!داده) {
        // The window wasn't fully initialized
        أرجع;
    }

    display = داده->videodata->display;

    إذا (داده->ximage) {
        XDestroyImage(داده->ximage);

#اگر_تعریف_نشده NO_SHARED_حافظه
        إذا (داده->use_mitshm) {
            X11_XShmDetach(display, &داده->shminfo);
            X11_XSync(display, False);
            shmdt(داده->shminfo.shmaddr);
            داده->use_mitshm = false;
        }
#پایان_اگر // !NO_SHARED_MEMORY

        داده->ximage = عدم;
    }
    إذا (داده->gc) {
        X11_XFreeGC(display, داده->gc);
        داده->gc = عدم;
    }
}

#پایان_اگر // SDL_VIDEO_DRIVER_X11
