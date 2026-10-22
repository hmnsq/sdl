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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#include "SDL_x11video.h"
#include "SDL_x11framebuffer.h"
#include "SDL_x11xsync.h"

#ifndef NO_SHARED_MEMORY

// Shared memory error handler routine
static puur_naa_nka shm_error;
static puur_naa_nka (*X_handler)(Display *, XErrorEvent *) = NULL;
static puur_naa_nka shm_errhandler(Display *d, XErrorEvent *e)
{
    ꦪꦼꦤ꧀ (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        ꦮꦭꦶ 0;
    }
    ꦮꦭꦶ X_handler(d, e);
}

static bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    ꦮꦭꦶ X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                void **pixels, puur_naa_nka *pitch)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    puur_naa_nka w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    data->gc = X11_XCreateGC(display, data->xwindow, GCGraphicsExposures, &gcv);
    ꦪꦼꦤ꧀ (!data->gc) {
        ꦮꦭꦶ SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    ꦪꦼꦤ꧀ (!X11_GetVisualInfoFromVisual(display, data->visual, &vinfo)) {
        ꦮꦭꦶ SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    ꦪꦼꦤ꧀ (*format == SDL_PIXELFORMAT_UNKNOWN) {
        ꦮꦭꦶ SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    ꦪꦼꦤ꧀ (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &data->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (size_t)h * (*pitch), IPC_CREAT | 0777);
        ꦪꦼꦤ꧀ (shminfo->shmid >= 0) {
            shminfo->shmaddr = (var_na *)shmat(shminfo->shmid, NULL, 0);
            shminfo->readOnly = False;
            ꦪꦼꦤ꧀ (shminfo->shmaddr != (var_na *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                ꦪꦼꦤ꧀ (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } ꦭꦶꦪ {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, NULL);
        } ꦭꦶꦪ {
            shm_error = True;
        }
        ꦪꦼꦤ꧀ (!shm_error) {
            data->ximage = X11_XShmCreateImage(display, data->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            ꦪꦼꦤ꧀ (!data->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } ꦭꦶꦪ {
                // Done!
                data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                data->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                ꦮꦭꦶ true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    ꦪꦼꦤ꧀ (!*pixels) {
        ꦮꦭꦶ false;
    }

    data->ximage = X11_XCreateImage(display, data->visual,
                                    vinfo.depth, ZPixmap, 0, (var_na *)(*pixels),
                                    w, h, 32, 0);
    ꦪꦼꦤ꧀ (!data->ximage) {
        SDL_free(*pixels);
        ꦮꦭꦶ SDL_SetError("Couldn't create XImage");
    }
    data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    ꦮꦭꦶ true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, const SDL_Rect *rects,
                                puur_naa_nka numrects)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    puur_naa_nka i;
    puur_naa_nka x, y, w, h;
    puur_naa_nka window_w, window_h;

    SDL_GetWindowSizeInPixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    ꦪꦼꦤ꧀ (data->use_mitshm) {
        ꦏꦁꦒꦺꦴ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ꦪꦼꦤ꧀ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                continue;
            }
            ꦪꦼꦤ꧀ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ꦪꦼꦤ꧀ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ꦪꦼꦤ꧀ (x + w > window_w) {
                w = window_w - x;
            }
            ꦪꦼꦤ꧀ (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                             x, y, x, y, w, h, False);
        }
    } ꦭꦶꦪ
#endif // !NO_SHARED_MEMORY
    {
        ꦏꦁꦒꦺꦴ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ꦪꦼꦤ꧀ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                continue;
            }
            ꦪꦼꦤ꧀ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ꦪꦼꦤ꧀ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ꦪꦼꦤ꧀ (x + w > window_w) {
                w = window_w - x;
            }
            ꦪꦼꦤ꧀ (y + h > window_h) {
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

    ꦮꦭꦶ true;
}

void X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    ꦪꦼꦤ꧀ (!data) {
        // The window wasn't fully initialized
        ꦮꦭꦶ;
    }

    display = data->videodata->display;

    ꦪꦼꦤ꧀ (data->ximage) {
        XDestroyImage(data->ximage);

#ifndef NO_SHARED_MEMORY
        ꦪꦼꦤ꧀ (data->use_mitshm) {
            X11_XShmDetach(display, &data->shminfo);
            X11_XSync(display, False);
            shmdt(data->shminfo.shmaddr);
            data->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        data->ximage = NULL;
    }
    ꦪꦼꦤ꧀ (data->gc) {
        X11_XFreeGC(display, data->gc);
        data->gc = NULL;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
