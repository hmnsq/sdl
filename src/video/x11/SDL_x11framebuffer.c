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

#ifdef SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11framebuffer.h"
#ضمن "SDL_x11xsync.h"

#ifndef NO_SHARED_MEMORY

// Shared memory error handler routine
ساكن صحيح shm_error;
ساكن صحيح (*X_handler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح shm_errhandler(Display *d, XErrorEvent *e)
{
    إذا (e->error_code == BadAccess || e->error_code == BadRequest) {
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

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                فراغ **pixels, صحيح *pitch)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    صحيح w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    data->gc = X11_XCreateGC(display, data->xwindow, GCGraphicsExposures, &gcv);
    إذا (!data->gc) {
        أرجع SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    إذا (!X11_GetVisualInfoFromVisual(display, data->visual, &vinfo)) {
        أرجع SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    إذا (*format == SDL_PIXELFORMAT_UNKNOWN) {
        أرجع SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    إذا (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &data->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (size_t)h * (*pitch), IPC_CREAT | 0777);
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
            data->ximage = X11_XShmCreateImage(display, data->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            إذا (!data->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } وإلا {
                // Done!
                data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                data->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                أرجع true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    إذا (!*pixels) {
        أرجع false;
    }

    data->ximage = X11_XCreateImage(display, data->visual,
                                    vinfo.depth, ZPixmap, 0, (حرف *)(*pixels),
                                    w, h, 32, 0);
    إذا (!data->ximage) {
        SDL_free(*pixels);
        أرجع SDL_SetError("Couldn't create XImage");
    }
    data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    أرجع true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ثابت SDL_Rect *rects,
                                صحيح numrects)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    صحيح i;
    صحيح x, y, w, h;
    صحيح window_w, window_h;

    SDL_GetWindowSizeInPixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    إذا (data->use_mitshm) {
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
            إذا (x + w > window_w) {
                w = window_w - x;
            }
            إذا (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                             x, y, x, y, w, h, False);
        }
    } وإلا
#endif // !NO_SHARED_MEMORY
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
            إذا (x + w > window_w) {
                w = window_w - x;
            }
            إذا (y + h > window_h) {
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

    أرجع true;
}

فراغ X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    إذا (!data) {
        // The window wasn't fully initialized
        أرجع;
    }

    display = data->videodata->display;

    إذا (data->ximage) {
        XDestroyImage(data->ximage);

#ifndef NO_SHARED_MEMORY
        إذا (data->use_mitshm) {
            X11_XShmDetach(display, &data->shminfo);
            X11_XSync(display, False);
            shmdt(data->shminfo.shmaddr);
            data->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        data->ximage = عدم;
    }
    إذا (data->gc) {
        X11_XFreeGC(display, data->gc);
        data->gc = عدم;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
