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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11framebuffer.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xsync.h"

#ifndef NO_SHARED_MEMORY

// Shared memory error handler routine
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ shm_error;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ (*X_handler)(Display *, XErrorEvent *) = ರಿಕ್ತ;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ shm_errhandler(Display *d, XErrorEvent *e)
{
    ಯದಿ (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    ಪ್ರತ್ಯಾಗಮ X_handler(d, e);
}

ಸ್ಥಿರ bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    ಪ್ರತ್ಯಾಗಮ X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಙ್ಕ *pitch)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    ಪೂರ್ಣಾಙ್ಕ w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    data->gc = X11_XCreateGC(display, data->xwindow, GCGraphicsExposures, &gcv);
    ಯದಿ (!data->gc) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    ಯದಿ (!X11_GetVisualInfoFromVisual(display, data->visual, &vinfo)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    ಯದಿ (*format == SDL_PIXELFORMAT_UNKNOWN) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    ಯದಿ (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &data->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (size_t)h * (*pitch), IPC_CREAT | 0777);
        ಯದಿ (shminfo->shmid >= 0) {
            shminfo->shmaddr = (ವರ್ಣ *)shmat(shminfo->shmid, ರಿಕ್ತ, 0);
            shminfo->readOnly = False;
            ಯದಿ (shminfo->shmaddr != (ವರ್ಣ *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                ಯದಿ (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } ಅನ್ಯಥಾ {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, ರಿಕ್ತ);
        } ಅನ್ಯಥಾ {
            shm_error = True;
        }
        ಯದಿ (!shm_error) {
            data->ximage = X11_XShmCreateImage(display, data->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            ಯದಿ (!data->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } ಅನ್ಯಥಾ {
                // Done!
                data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                data->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                ಪ್ರತ್ಯಾಗಮ true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    ಯದಿ (!*pixels) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    data->ximage = X11_XCreateImage(display, data->visual,
                                    vinfo.depth, ZPixmap, 0, (ವರ್ಣ *)(*pixels),
                                    w, h, 32, 0);
    ಯದಿ (!data->ximage) {
        SDL_free(*pixels);
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't create XImage");
    }
    data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    ಪ್ರತ್ಯಾಗಮ true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ಧ್ರುವ SDL_Rect *rects,
                                ಪೂರ್ಣಾಙ್ಕ numrects)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪೂರ್ಣಾಙ್ಕ x, y, w, h;
    ಪೂರ್ಣಾಙ್ಕ window_w, window_h;

    SDL_GetWindowSizeInPixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    ಯದಿ (data->use_mitshm) {
        ಪ್ರತಿ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ಯದಿ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                ಅನುವರ್ತ;
            }
            ಯದಿ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ಯದಿ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ಯದಿ (x + w > window_w) {
                w = window_w - x;
            }
            ಯದಿ (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                             x, y, x, y, w, h, False);
        }
    } ಅನ್ಯಥಾ
#endif // !NO_SHARED_MEMORY
    {
        ಪ್ರತಿ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ಯದಿ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                ಅನುವರ್ತ;
            }
            ಯದಿ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ಯದಿ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ಯದಿ (x + w > window_w) {
                w = window_w - x;
            }
            ಯದಿ (y + h > window_h) {
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

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    ಯದಿ (!data) {
        // The window wasn't fully initialized
        ಪ್ರತ್ಯಾಗಮ;
    }

    display = data->videodata->display;

    ಯದಿ (data->ximage) {
        XDestroyImage(data->ximage);

#ifndef NO_SHARED_MEMORY
        ಯದಿ (data->use_mitshm) {
            X11_XShmDetach(display, &data->shminfo);
            X11_XSync(display, False);
            shmdt(data->shminfo.shmaddr);
            data->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        data->ximage = ರಿಕ್ತ;
    }
    ಯದಿ (data->gc) {
        X11_XFreeGC(display, data->gc);
        data->gc = ರಿಕ್ತ;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
