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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11framebuffer.h"
#अन्तर्भाव "SDL_x11xsync.h"

#ifndef NO_SHARED_MEMORY

// Shared memory error handler routine
स्थिर पूर्णाङ्क shm_error;
स्थिर पूर्णाङ्क (*X_handler)(Display *, XErrorEvent *) = रिक्त;
स्थिर पूर्णाङ्क shm_errhandler(Display *d, XErrorEvent *e)
{
    जइ (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        प्रत्यागम 0;
    }
    प्रत्यागम X_handler(d, e);
}

स्थिर bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    प्रत्यागम X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    पूर्णाङ्क w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    data->gc = X11_XCreateGC(display, data->xwindow, GCGraphicsExposures, &gcv);
    जइ (!data->gc) {
        प्रत्यागम SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    जइ (!X11_GetVisualInfoFromVisual(display, data->visual, &vinfo)) {
        प्रत्यागम SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    जइ (*format == SDL_PIXELFORMAT_UNKNOWN) {
        प्रत्यागम SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    जइ (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &data->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (size_t)h * (*pitch), IPC_CREAT | 0777);
        जइ (shminfo->shmid >= 0) {
            shminfo->shmaddr = (वर्ण *)shmat(shminfo->shmid, रिक्त, 0);
            shminfo->readOnly = False;
            जइ (shminfo->shmaddr != (वर्ण *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                जइ (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } अण्णहा {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, रिक्त);
        } अण्णहा {
            shm_error = True;
        }
        जइ (!shm_error) {
            data->ximage = X11_XShmCreateImage(display, data->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            जइ (!data->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } अण्णहा {
                // Done!
                data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                data->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                प्रत्यागम true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    जइ (!*pixels) {
        प्रत्यागम false;
    }

    data->ximage = X11_XCreateImage(display, data->visual,
                                    vinfo.depth, ZPixmap, 0, (वर्ण *)(*pixels),
                                    w, h, 32, 0);
    जइ (!data->ximage) {
        SDL_free(*pixels);
        प्रत्यागम SDL_SetError("Couldn't create XImage");
    }
    data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    प्रत्यागम true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, ध्रुव SDL_Rect *rects,
                                पूर्णाङ्क numrects)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    पूर्णाङ्क i;
    पूर्णाङ्क x, y, w, h;
    पूर्णाङ्क window_w, window_h;

    SDL_GetWindowSizeInPixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    जइ (data->use_mitshm) {
        प्रति (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            जइ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                अनुवर्त;
            }
            जइ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            जइ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            जइ (x + w > window_w) {
                w = window_w - x;
            }
            जइ (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                             x, y, x, y, w, h, False);
        }
    } अण्णहा
#endif // !NO_SHARED_MEMORY
    {
        प्रति (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            जइ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                अनुवर्त;
            }
            जइ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            जइ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            जइ (x + w > window_w) {
                w = window_w - x;
            }
            जइ (y + h > window_h) {
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

    प्रत्यागम true;
}

शून्य X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    जइ (!data) {
        // The window wasn't fully initialized
        प्रत्यागम;
    }

    display = data->videodata->display;

    जइ (data->ximage) {
        XDestroyImage(data->ximage);

#ifndef NO_SHARED_MEMORY
        जइ (data->use_mitshm) {
            X11_XShmDetach(display, &data->shminfo);
            X11_XSync(display, False);
            shmdt(data->shminfo.shmaddr);
            data->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        data->ximage = रिक्त;
    }
    जइ (data->gc) {
        X11_XFreeGC(display, data->gc);
        data->gc = रिक्त;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
