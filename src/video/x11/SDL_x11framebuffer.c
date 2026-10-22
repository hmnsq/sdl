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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "SDL_x11framebuffer.h"
#அந்தர்பாவ "SDL_x11xsync.h"

#ifndef NO_SHARED_MEMORY

// Shared memory error handler routine
நிலையான முழு shm_error;
நிலையான முழு (*X_handler)(Display *, XErrorEvent *) = வெற்று;
நிலையான முழு shm_errhandler(Display *d, XErrorEvent *e)
{
    எனில் (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        திரும்பு 0;
    }
    திரும்பு X_handler(d, e);
}

நிலையான bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    திரும்பு X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                வெறுமை **pixels, முழு *pitch)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    முழு w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    data->gc = X11_XCreateGC(display, data->xwindow, GCGraphicsExposures, &gcv);
    எனில் (!data->gc) {
        திரும்பு SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    எனில் (!X11_GetVisualInfoFromVisual(display, data->visual, &vinfo)) {
        திரும்பு SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    எனில் (*format == SDL_PIXELFORMAT_UNKNOWN) {
        திரும்பு SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    எனில் (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &data->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (size_t)h * (*pitch), IPC_CREAT | 0777);
        எனில் (shminfo->shmid >= 0) {
            shminfo->shmaddr = (எழுத்து *)shmat(shminfo->shmid, வெற்று, 0);
            shminfo->readOnly = False;
            எனில் (shminfo->shmaddr != (எழுத்து *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                எனில் (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } இல்லையெனில் {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, வெற்று);
        } இல்லையெனில் {
            shm_error = True;
        }
        எனில் (!shm_error) {
            data->ximage = X11_XShmCreateImage(display, data->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            எனில் (!data->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } இல்லையெனில் {
                // Done!
                data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                data->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                திரும்பு true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    எனில் (!*pixels) {
        திரும்பு false;
    }

    data->ximage = X11_XCreateImage(display, data->visual,
                                    vinfo.depth, ZPixmap, 0, (எழுத்து *)(*pixels),
                                    w, h, 32, 0);
    எனில் (!data->ximage) {
        SDL_free(*pixels);
        திரும்பு SDL_SetError("Couldn't create XImage");
    }
    data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    திரும்பு true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, மாறிலி SDL_Rect *rects,
                                முழு numrects)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    முழு i;
    முழு x, y, w, h;
    முழு window_w, window_h;

    SDL_GetWindowSizeInPixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    எனில் (data->use_mitshm) {
        க்கு (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            எனில் (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                தொடர்;
            }
            எனில் (x < 0) {
                x += w;
                w += rects[i].x;
            }
            எனில் (y < 0) {
                y += h;
                h += rects[i].y;
            }
            எனில் (x + w > window_w) {
                w = window_w - x;
            }
            எனில் (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                             x, y, x, y, w, h, False);
        }
    } இல்லையெனில்
#endif // !NO_SHARED_MEMORY
    {
        க்கு (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            எனில் (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                தொடர்;
            }
            எனில் (x < 0) {
                x += w;
                w += rects[i].x;
            }
            எனில் (y < 0) {
                y += h;
                h += rects[i].y;
            }
            எனில் (x + w > window_w) {
                w = window_w - x;
            }
            எனில் (y + h > window_h) {
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

    திரும்பு true;
}

வெறுமை X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    எனில் (!data) {
        // The window wasn't fully initialized
        திரும்பு;
    }

    display = data->videodata->display;

    எனில் (data->ximage) {
        XDestroyImage(data->ximage);

#ifndef NO_SHARED_MEMORY
        எனில் (data->use_mitshm) {
            X11_XShmDetach(display, &data->shminfo);
            X11_XSync(display, False);
            shmdt(data->shminfo.shmaddr);
            data->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        data->ximage = வெற்று;
    }
    எனில் (data->gc) {
        X11_XFreeGC(display, data->gc);
        data->gc = வெற்று;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
