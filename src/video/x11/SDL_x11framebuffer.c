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
स्थिर पूर्णांक shm_error;
स्थिर पूर्णांक (*X_handler)(Display *, XErrorEvent *) = रिक्त;
स्थिर पूर्णांक shm_errhandler(Display *d, XErrorEvent *e)
{
    जर (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        परत 0;
    }
    परत X_handler(d, e);
}

स्थिर bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    परत X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                शून्य **pixels, पूर्णांक *pitch)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    पूर्णांक w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    data->gc = X11_XCreateGC(display, data->xwindow, GCGraphicsExposures, &gcv);
    जर (!data->gc) {
        परत SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    जर (!X11_GetVisualInfoFromVisual(display, data->visual, &vinfo)) {
        परत SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    जर (*format == SDL_PIXELFORMAT_UNKNOWN) {
        परत SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    जर (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &data->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (माप_प्रकार)h * (*pitch), IPC_CREAT | 0777);
        जर (shminfo->shmid >= 0) {
            shminfo->shmaddr = (अक्षर *)shmat(shminfo->shmid, रिक्त, 0);
            shminfo->readOnly = False;
            जर (shminfo->shmaddr != (अक्षर *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                जर (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } अन्यथा {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, रिक्त);
        } अन्यथा {
            shm_error = True;
        }
        जर (!shm_error) {
            data->ximage = X11_XShmCreateImage(display, data->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            जर (!data->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } अन्यथा {
                // Done!
                data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                data->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                परत true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((माप_प्रकार)h * (*pitch));
    जर (!*pixels) {
        परत false;
    }

    data->ximage = X11_XCreateImage(display, data->visual,
                                    vinfo.depth, ZPixmap, 0, (अक्षर *)(*pixels),
                                    w, h, 32, 0);
    जर (!data->ximage) {
        SDL_free(*pixels);
        परत SDL_SetError("Couldn't create XImage");
    }
    data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    परत true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, स्थिरांक SDL_Rect *rects,
                                पूर्णांक numrects)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    पूर्णांक i;
    पूर्णांक x, y, w, h;
    पूर्णांक window_w, window_h;

    SDL_GetWindowSizeInPixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    जर (data->use_mitshm) {
        साठी (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            जर (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                सुरूठेवा;
            }
            जर (x < 0) {
                x += w;
                w += rects[i].x;
            }
            जर (y < 0) {
                y += h;
                h += rects[i].y;
            }
            जर (x + w > window_w) {
                w = window_w - x;
            }
            जर (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                             x, y, x, y, w, h, False);
        }
    } अन्यथा
#endif // !NO_SHARED_MEMORY
    {
        साठी (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            जर (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                सुरूठेवा;
            }
            जर (x < 0) {
                x += w;
                w += rects[i].x;
            }
            जर (y < 0) {
                y += h;
                h += rects[i].y;
            }
            जर (x + w > window_w) {
                w = window_w - x;
            }
            जर (y + h > window_h) {
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

    परत true;
}

शून्य X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    जर (!data) {
        // The window wasn't fully initialized
        परत;
    }

    display = data->videodata->display;

    जर (data->ximage) {
        XDestroyImage(data->ximage);

#ifndef NO_SHARED_MEMORY
        जर (data->use_mitshm) {
            X11_XShmDetach(display, &data->shminfo);
            X11_XSync(display, False);
            shmdt(data->shminfo.shmaddr);
            data->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        data->ximage = रिक्त;
    }
    जर (data->gc) {
        X11_XFreeGC(display, data->gc);
        data->gc = रिक्त;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
