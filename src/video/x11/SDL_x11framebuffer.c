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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ଅନ୍ତର୍ଭାଵ "SDL_x11video.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11framebuffer.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11xsync.h"

#ifndef NO_SHARED_MEMORY

// Shared memory error handler routine
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା shm_error;
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*X_handler)(Display *, XErrorEvent *) = ଖାଲି;
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା shm_errhandler(Display *d, XErrorEvent *e)
{
    ଯଦି (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        ଫେରନ୍ତୁ 0;
    }
    ଫେରନ୍ତୁ X_handler(d, e);
}

ସ୍ଥିର bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    ଫେରନ୍ତୁ X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                ଶୂନ୍ୟ **pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *pitch)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    data->gc = X11_XCreateGC(display, data->xwindow, GCGraphicsExposures, &gcv);
    ଯଦି (!data->gc) {
        ଫେରନ୍ତୁ SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    ଯଦି (!X11_GetVisualInfoFromVisual(display, data->visual, &vinfo)) {
        ଫେରନ୍ତୁ SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    ଯଦି (*format == SDL_PIXELFORMAT_UNKNOWN) {
        ଫେରନ୍ତୁ SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    ଯଦି (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &data->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (size_t)h * (*pitch), IPC_CREAT | 0777);
        ଯଦି (shminfo->shmid >= 0) {
            shminfo->shmaddr = (ଅକ୍ଷର *)shmat(shminfo->shmid, ଖାଲି, 0);
            shminfo->readOnly = False;
            ଯଦି (shminfo->shmaddr != (ଅକ୍ଷର *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                ଯଦି (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } ଅନ୍ୟଥା {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, ଖାଲି);
        } ଅନ୍ୟଥା {
            shm_error = True;
        }
        ଯଦି (!shm_error) {
            data->ximage = X11_XShmCreateImage(display, data->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            ଯଦି (!data->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } ଅନ୍ୟଥା {
                // Done!
                data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                data->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                ଫେରନ୍ତୁ true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    ଯଦି (!*pixels) {
        ଫେରନ୍ତୁ false;
    }

    data->ximage = X11_XCreateImage(display, data->visual,
                                    vinfo.depth, ZPixmap, 0, (ଅକ୍ଷର *)(*pixels),
                                    w, h, 32, 0);
    ଯଦି (!data->ximage) {
        SDL_free(*pixels);
        ଫେରନ୍ତୁ SDL_SetError("Couldn't create XImage");
    }
    data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    ଫେରନ୍ତୁ true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ଅଚଳ SDL_Rect *rects,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା numrects)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y, w, h;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା window_w, window_h;

    SDL_GetWindowSizeInPixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    ଯଦି (data->use_mitshm) {
        ପାଇଁ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ଯଦି (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                ଜାରି;
            }
            ଯଦି (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ଯଦି (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ଯଦି (x + w > window_w) {
                w = window_w - x;
            }
            ଯଦି (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                             x, y, x, y, w, h, False);
        }
    } ଅନ୍ୟଥା
#endif // !NO_SHARED_MEMORY
    {
        ପାଇଁ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ଯଦି (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                ଜାରି;
            }
            ଯଦି (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ଯଦି (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ଯଦି (x + w > window_w) {
                w = window_w - x;
            }
            ଯଦି (y + h > window_h) {
                h = window_h - y;
            }

            X11_XPutImage(display, data->xwindow, data->gc, data->ximage,
                          x, y, x, y, w, h);
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(data->window);
#endif /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    ଯଦି (!data) {
        // The window wasn't fully initialized
        ଫେରନ୍ତୁ;
    }

    display = data->videodata->display;

    ଯଦି (data->ximage) {
        XDestroyImage(data->ximage);

#ifndef NO_SHARED_MEMORY
        ଯଦି (data->use_mitshm) {
            X11_XShmDetach(display, &data->shminfo);
            X11_XSync(display, False);
            shmdt(data->shminfo.shmaddr);
            data->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        data->ximage = ଖାଲି;
    }
    ଯଦି (data->gc) {
        X11_XFreeGC(display, data->gc);
        data->gc = ଖାଲି;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
