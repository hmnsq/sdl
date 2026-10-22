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
static ຈຳນວນເຕັມ shm_error;
static ຈຳນວນເຕັມ (*X_handler)(Display *, XErrorEvent *) = NULL;
static ຈຳນວນເຕັມ shm_errhandler(Display *d, XErrorEvent *e)
{
    ຖ້າ (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        ສົ່ງຄືນ 0;
    }
    ສົ່ງຄືນ X_handler(d, e);
}

static bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    ສົ່ງຄືນ X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                void **pixels, ຈຳນວນເຕັມ *pitch)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    ຈຳນວນເຕັມ w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    data->gc = X11_XCreateGC(display, data->xwindow, GCGraphicsExposures, &gcv);
    ຖ້າ (!data->gc) {
        ສົ່ງຄືນ SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    ຖ້າ (!X11_GetVisualInfoFromVisual(display, data->visual, &vinfo)) {
        ສົ່ງຄືນ SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    ຖ້າ (*format == SDL_PIXELFORMAT_UNKNOWN) {
        ສົ່ງຄືນ SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    ຖ້າ (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &data->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (size_t)h * (*pitch), IPC_CREAT | 0777);
        ຖ້າ (shminfo->shmid >= 0) {
            shminfo->shmaddr = (var_na *)shmat(shminfo->shmid, NULL, 0);
            shminfo->readOnly = False;
            ຖ້າ (shminfo->shmaddr != (var_na *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                ຖ້າ (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } ບໍ່ດັ່ງນັ້ນ {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, NULL);
        } ບໍ່ດັ່ງນັ້ນ {
            shm_error = True;
        }
        ຖ້າ (!shm_error) {
            data->ximage = X11_XShmCreateImage(display, data->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            ຖ້າ (!data->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } ບໍ່ດັ່ງນັ້ນ {
                // Done!
                data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                data->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                ສົ່ງຄືນ true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    ຖ້າ (!*pixels) {
        ສົ່ງຄືນ false;
    }

    data->ximage = X11_XCreateImage(display, data->visual,
                                    vinfo.depth, ZPixmap, 0, (var_na *)(*pixels),
                                    w, h, 32, 0);
    ຖ້າ (!data->ximage) {
        SDL_free(*pixels);
        ສົ່ງຄືນ SDL_SetError("Couldn't create XImage");
    }
    data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    ສົ່ງຄືນ true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, const SDL_Rect *rects,
                                ຈຳນວນເຕັມ numrects)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    ຈຳນວນເຕັມ i;
    ຈຳນວນເຕັມ x, y, w, h;
    ຈຳນວນເຕັມ window_w, window_h;

    SDL_GetWindowSizeInPixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    ຖ້າ (data->use_mitshm) {
        ສຳລັບ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ຖ້າ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                continue;
            }
            ຖ້າ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ຖ້າ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ຖ້າ (x + w > window_w) {
                w = window_w - x;
            }
            ຖ້າ (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                             x, y, x, y, w, h, False);
        }
    } ບໍ່ດັ່ງນັ້ນ
#endif // !NO_SHARED_MEMORY
    {
        ສຳລັບ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ຖ້າ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                continue;
            }
            ຖ້າ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ຖ້າ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ຖ້າ (x + w > window_w) {
                w = window_w - x;
            }
            ຖ້າ (y + h > window_h) {
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

    ສົ່ງຄືນ true;
}

void X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    ຖ້າ (!data) {
        // The window wasn't fully initialized
        ສົ່ງຄືນ;
    }

    display = data->videodata->display;

    ຖ້າ (data->ximage) {
        XDestroyImage(data->ximage);

#ifndef NO_SHARED_MEMORY
        ຖ້າ (data->use_mitshm) {
            X11_XShmDetach(display, &data->shminfo);
            X11_XSync(display, False);
            shmdt(data->shminfo.shmaddr);
            data->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        data->ximage = NULL;
    }
    ຖ້າ (data->gc) {
        X11_XFreeGC(display, data->gc);
        data->gc = NULL;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
