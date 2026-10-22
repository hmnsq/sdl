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
static จำนวนเต็ม shm_error;
static จำนวนเต็ม (*X_handler)(Display *, XErrorEvent *) = NULL;
static จำนวนเต็ม shm_errhandler(Display *d, XErrorEvent *e)
{
    ถ้า (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        คืน 0;
    }
    คืน X_handler(d, e);
}

static bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    คืน X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                void **pixels, จำนวนเต็ม *pitch)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    จำนวนเต็ม w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    data->gc = X11_XCreateGC(display, data->xwindow, GCGraphicsExposures, &gcv);
    ถ้า (!data->gc) {
        คืน SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    ถ้า (!X11_GetVisualInfoFromVisual(display, data->visual, &vinfo)) {
        คืน SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    ถ้า (*format == SDL_PIXELFORMAT_UNKNOWN) {
        คืน SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    ถ้า (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &data->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (size_t)h * (*pitch), IPC_CREAT | 0777);
        ถ้า (shminfo->shmid >= 0) {
            shminfo->shmaddr = (var_na *)shmat(shminfo->shmid, NULL, 0);
            shminfo->readOnly = False;
            ถ้า (shminfo->shmaddr != (var_na *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                ถ้า (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } มิฉะนั้น {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, NULL);
        } มิฉะนั้น {
            shm_error = True;
        }
        ถ้า (!shm_error) {
            data->ximage = X11_XShmCreateImage(display, data->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            ถ้า (!data->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } มิฉะนั้น {
                // Done!
                data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                data->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                คืน true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    ถ้า (!*pixels) {
        คืน false;
    }

    data->ximage = X11_XCreateImage(display, data->visual,
                                    vinfo.depth, ZPixmap, 0, (var_na *)(*pixels),
                                    w, h, 32, 0);
    ถ้า (!data->ximage) {
        SDL_free(*pixels);
        คืน SDL_SetError("Couldn't create XImage");
    }
    data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    คืน true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, const SDL_Rect *rects,
                                จำนวนเต็ม numrects)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    จำนวนเต็ม i;
    จำนวนเต็ม x, y, w, h;
    จำนวนเต็ม window_w, window_h;

    SDL_GetWindowSizeInPixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    ถ้า (data->use_mitshm) {
        สำหรับ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ถ้า (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                continue;
            }
            ถ้า (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ถ้า (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ถ้า (x + w > window_w) {
                w = window_w - x;
            }
            ถ้า (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                             x, y, x, y, w, h, False);
        }
    } มิฉะนั้น
#endif // !NO_SHARED_MEMORY
    {
        สำหรับ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ถ้า (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                continue;
            }
            ถ้า (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ถ้า (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ถ้า (x + w > window_w) {
                w = window_w - x;
            }
            ถ้า (y + h > window_h) {
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

    คืน true;
}

void X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    ถ้า (!data) {
        // The window wasn't fully initialized
        คืน;
    }

    display = data->videodata->display;

    ถ้า (data->ximage) {
        XDestroyImage(data->ximage);

#ifndef NO_SHARED_MEMORY
        ถ้า (data->use_mitshm) {
            X11_XShmDetach(display, &data->shminfo);
            X11_XSync(display, False);
            shmdt(data->shminfo.shmaddr);
            data->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        data->ximage = NULL;
    }
    ถ้า (data->gc) {
        X11_XFreeGC(display, data->gc);
        data->gc = NULL;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
