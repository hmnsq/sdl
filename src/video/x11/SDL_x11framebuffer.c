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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "SDL_x11framebuffer.h"
#അന്തര്ഭാവ "SDL_x11xsync.h"

#ifndef NO_SHARED_MEMORY

// Shared memory error handler routine
സ്ഥിതം പൂർണ്ണസംഖ്യ shm_error;
സ്ഥിതം പൂർണ്ണസംഖ്യ (*X_handler)(Display *, XErrorEvent *) = ശൂന്യ;
സ്ഥിതം പൂർണ്ണസംഖ്യ shm_errhandler(Display *d, XErrorEvent *e)
{
    എങ്കിൽ (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        തിരികെ 0;
    }
    തിരികെ X_handler(d, e);
}

സ്ഥിതം bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    തിരികെ X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#endif // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                ശൂന്യം **pixels, പൂർണ്ണസംഖ്യ *pitch)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    പൂർണ്ണസംഖ്യ w, h;

    SDL_GetWindowSizeInPixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    data->gc = X11_XCreateGC(display, data->xwindow, GCGraphicsExposures, &gcv);
    എങ്കിൽ (!data->gc) {
        തിരികെ SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    എങ്കിൽ (!X11_GetVisualInfoFromVisual(display, data->visual, &vinfo)) {
        തിരികെ SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    എങ്കിൽ (*format == SDL_PIXELFORMAT_UNKNOWN) {
        തിരികെ SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ifndef NO_SHARED_MEMORY
    എങ്കിൽ (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &data->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (size_t)h * (*pitch), IPC_CREAT | 0777);
        എങ്കിൽ (shminfo->shmid >= 0) {
            shminfo->shmaddr = (അക്ഷരം *)shmat(shminfo->shmid, ശൂന്യ, 0);
            shminfo->readOnly = False;
            എങ്കിൽ (shminfo->shmaddr != (അക്ഷരം *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                എങ്കിൽ (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } അല്ലെങ്കിൽ {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, ശൂന്യ);
        } അല്ലെങ്കിൽ {
            shm_error = True;
        }
        എങ്കിൽ (!shm_error) {
            data->ximage = X11_XShmCreateImage(display, data->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            എങ്കിൽ (!data->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } അല്ലെങ്കിൽ {
                // Done!
                data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                data->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                തിരികെ true;
            }
        }
    }
#endif // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    എങ്കിൽ (!*pixels) {
        തിരികെ false;
    }

    data->ximage = X11_XCreateImage(display, data->visual,
                                    vinfo.depth, ZPixmap, 0, (അക്ഷരം *)(*pixels),
                                    w, h, 32, 0);
    എങ്കിൽ (!data->ximage) {
        SDL_free(*pixels);
        തിരികെ SDL_SetError("Couldn't create XImage");
    }
    data->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    തിരികെ true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, സ്ഥിരം SDL_Rect *rects,
                                പൂർണ്ണസംഖ്യ numrects)
{
    SDL_WindowData *data = window->internal;
    Display *display = data->videodata->display;
    പൂർണ്ണസംഖ്യ i;
    പൂർണ്ണസംഖ്യ x, y, w, h;
    പൂർണ്ണസംഖ്യ window_w, window_h;

    SDL_GetWindowSizeInPixels(window, &window_w, &window_h);

#ifndef NO_SHARED_MEMORY
    എങ്കിൽ (data->use_mitshm) {
        വേണ്ടി (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            എങ്കിൽ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                തുടരുക;
            }
            എങ്കിൽ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            എങ്കിൽ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            എങ്കിൽ (x + w > window_w) {
                w = window_w - x;
            }
            എങ്കിൽ (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                             x, y, x, y, w, h, False);
        }
    } അല്ലെങ്കിൽ
#endif // !NO_SHARED_MEMORY
    {
        വേണ്ടി (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            എങ്കിൽ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                തുടരുക;
            }
            എങ്കിൽ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            എങ്കിൽ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            എങ്കിൽ (x + w > window_w) {
                w = window_w - x;
            }
            എങ്കിൽ (y + h > window_h) {
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

    തിരികെ true;
}

ശൂന്യം X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_WindowData *data = window->internal;
    Display *display;

    എങ്കിൽ (!data) {
        // The window wasn't fully initialized
        തിരികെ;
    }

    display = data->videodata->display;

    എങ്കിൽ (data->ximage) {
        XDestroyImage(data->ximage);

#ifndef NO_SHARED_MEMORY
        എങ്കിൽ (data->use_mitshm) {
            X11_XShmDetach(display, &data->shminfo);
            X11_XSync(display, False);
            shmdt(data->shminfo.shmaddr);
            data->use_mitshm = false;
        }
#endif // !NO_SHARED_MEMORY

        data->ximage = ശൂന്യ;
    }
    എങ്കിൽ (data->gc) {
        X11_XFreeGC(display, data->gc);
        data->gc = ശൂന്യ;
    }
}

#endif // SDL_VIDEO_DRIVER_X11
