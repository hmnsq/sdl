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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#અન્તર્ભાવ "SDL_x11video.h"
#અન્તર્ભાવ "SDL_x11framebuffer.h"
#અન્તર્ભાવ "SDL_x11xsync.h"

#ifndef NO_SHARED_MEMORY

// Shared memory error handler routine
સ્થિર પૂર્ણાંક shm_error;
સ્થિર પૂર્ણાંક (*X_handler)(Display *, XErrorEvent *) = ખાલી;
સ્થિર પૂર્ણાંક shm_errhandler(Display *d, XErrorEvent *e)
{
    જો (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        પાછા 0;
    }
    પાછા X_handler(d, e);
}

સ્થિર bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    પાછા X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                શૂન્ય **pixels, પૂર્ણાંક *pitch)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    પૂર્ણાંક w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    data->gc = X11_XCreateGC(display, data->xwindow, GCGraphicsExposures, &gcv);
    જો (!data->gc) {
        પાછા SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    જો (!X11_GetVisualInfoFromVisual(display, data->visual, &vinfo)) {
        પાછા SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    જો (*format == SDL_PIXELFORMAT_UNKNOWN) {
        પાછા SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    જો (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &data->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (size_t)h * (*pitch), IPC_CREAT | 0777);
        જો (shminfo->shmid >= 0) {
            shminfo->shmaddr = (અક્ષર *)shmat(shminfo->shmid, ખાલી, 0);
            shminfo->readOnly = False;
            જો (shminfo->shmaddr != (અક્ષર *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                જો (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } નહીંતર {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, ખાલી);
        } નહીંતર {
            shm_error = True;
        }
        જો (!shm_error) {
            data->ximage = X11_XShmCreateImage(display, data->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            જો (!data->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } નહીંતર {
                // Done!
                data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                data->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                પાછા true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    જો (!*pixels) {
        પાછા false;
    }

    data->ximage = X11_XCreateImage(display, data->visual,
                                    vinfo.depth, ZPixmap, 0, (અક્ષર *)(*pixels),
                                    w, h, 32, 0);
    જો (!data->ximage) {
        SDL_free(*pixels);
        પાછા SDL_SetError("Couldn't create XImage");
    }
    data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    પાછા true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, અચલ SDL_Rect *rects,
                                પૂર્ણાંક numrects)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    પૂર્ણાંક i;
    પૂર્ણાંક x, y, w, h;
    પૂર્ણાંક window_w, window_h;

    SDL_GetWindowSizeInPixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    જો (data->use_mitshm) {
        માટે (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            જો (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                ચાલુ;
            }
            જો (x < 0) {
                x += w;
                w += rects[i].x;
            }
            જો (y < 0) {
                y += h;
                h += rects[i].y;
            }
            જો (x + w > window_w) {
                w = window_w - x;
            }
            જો (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                             x, y, x, y, w, h, False);
        }
    } નહીંતર
#endif // !NO_SHARED_MEMORY
    {
        માટે (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            જો (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                ચાલુ;
            }
            જો (x < 0) {
                x += w;
                w += rects[i].x;
            }
            જો (y < 0) {
                y += h;
                h += rects[i].y;
            }
            જો (x + w > window_w) {
                w = window_w - x;
            }
            જો (y + h > window_h) {
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

    પાછા true;
}

શૂન્ય X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    જો (!data) {
        // The window wasn't fully initialized
        પાછા;
    }

    display = data->videodata->display;

    જો (data->ximage) {
        XDestroyImage(data->ximage);

#ifndef NO_SHARED_MEMORY
        જો (data->use_mitshm) {
            X11_XShmDetach(display, &data->shminfo);
            X11_XSync(display, False);
            shmdt(data->shminfo.shmaddr);
            data->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        data->ximage = ખાલી;
    }
    જો (data->gc) {
        X11_XFreeGC(display, data->gc);
        data->gc = ખાલી;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
