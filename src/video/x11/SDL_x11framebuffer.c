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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাব "SDL_x11video.h"
#অন্তর্ভাব "SDL_x11framebuffer.h"
#অন্তর্ভাব "SDL_x11xsync.h"

#ifndef NO_SHARED_MEMORY

// Shared memory error handler routine
স্থির পূর্ণসংখ্যা shm_error;
স্থির পূর্ণসংখ্যা (*X_handler)(Display *, XErrorEvent *) = ফাঁকা;
স্থির পূর্ণসংখ্যা shm_errhandler(Display *d, XErrorEvent *e)
{
    যদি (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        ফেরত 0;
    }
    ফেরত X_handler(d, e);
}

স্থির bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    ফেরত X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                শূন্য **pixels, পূর্ণসংখ্যা *pitch)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    পূর্ণসংখ্যা w, h;

    SDL_Get_Window_আকার_In_Pixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    তথ্য->gc = X11_XCreateGC(display, তথ্য->xwindow, GCGraphicsExposures, &gcv);
    যদি (!তথ্য->gc) {
        ফেরত SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    যদি (!X11_GetVisualInfoFromVisual(display, তথ্য->visual, &vinfo)) {
        ফেরত SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    যদি (*format == SDL_PIXELFORMAT_UNKNOWN) {
        ফেরত SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    যদি (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &তথ্য->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (size_t)h * (*pitch), IPC_CREAT | 0777);
        যদি (shminfo->shmid >= 0) {
            shminfo->shmaddr = (অক্ষর *)shmat(shminfo->shmid, ফাঁকা, 0);
            shminfo->readOnly = False;
            যদি (shminfo->shmaddr != (অক্ষর *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                যদি (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } অন্যথা {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, ফাঁকা);
        } অন্যথা {
            shm_error = True;
        }
        যদি (!shm_error) {
            তথ্য->ximage = X11_XShmCreateImage(display, তথ্য->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            যদি (!তথ্য->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } অন্যথা {
                // Done!
                তথ্য->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                তথ্য->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                ফেরত true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    যদি (!*pixels) {
        ফেরত false;
    }

    তথ্য->ximage = X11_XCreateImage(display, তথ্য->visual,
                                    vinfo.depth, ZPixmap, 0, (অক্ষর *)(*pixels),
                                    w, h, 32, 0);
    যদি (!তথ্য->ximage) {
        SDL_free(*pixels);
        ফেরত SDL_SetError("Couldn't create XImage");
    }
    তথ্য->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    ফেরত true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ধ্রুবক SDL_Rect *rects,
                                পূর্ণসংখ্যা numrects)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display = তথ্য->videodata->display;
    পূর্ণসংখ্যা i;
    পূর্ণসংখ্যা x, y, w, h;
    পূর্ণসংখ্যা window_w, window_h;

    SDL_Get_Window_আকার_In_Pixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    যদি (তথ্য->use_mitshm) {
        জন্য (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            যদি (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                চালু;
            }
            যদি (x < 0) {
                x += w;
                w += rects[i].x;
            }
            যদি (y < 0) {
                y += h;
                h += rects[i].y;
            }
            যদি (x + w > window_w) {
                w = window_w - x;
            }
            যদি (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, তথ্য->xwindow, তথ্য->gc, তথ্য->ximage,
                             x, y, x, y, w, h, False);
        }
    } অন্যথা
#endif // !NO_SHARED_MEMORY
    {
        জন্য (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            যদি (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                চালু;
            }
            যদি (x < 0) {
                x += w;
                w += rects[i].x;
            }
            যদি (y < 0) {
                y += h;
                h += rects[i].y;
            }
            যদি (x + w > window_w) {
                w = window_w - x;
            }
            যদি (y + h > window_h) {
                h = window_h - y;
            }

            X11_XPutImage(display, তথ্য->xwindow, তথ্য->gc, তথ্য->ximage,
                          x, y, x, y, w, h);
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(তথ্য->window);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    ফেরত true;
}

শূন্য X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    Display *display;

    যদি (!তথ্য) {
        // The window wasn't fully initialized
        ফেরত;
    }

    display = তথ্য->videodata->display;

    যদি (তথ্য->ximage) {
        XDestroyImage(তথ্য->ximage);

#ifndef NO_SHARED_MEMORY
        যদি (তথ্য->use_mitshm) {
            X11_XShmDetach(display, &তথ্য->shminfo);
            X11_XSync(display, False);
            shmdt(তথ্য->shminfo.shmaddr);
            তথ্য->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        তথ্য->ximage = ফাঁকা;
    }
    যদি (তথ্য->gc) {
        X11_XFreeGC(display, তথ্য->gc);
        তথ্য->gc = ফাঁকা;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
