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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश "SDL_x11video.h"
#समावेश "SDL_x11framebuffer.h"
#समावेश "SDL_x11xsync.h"

#अगर_अघोषित NO_SHARED_MEMORY

// Shared memory error handler routine
अटल पूर्णांक shm_error;
अटल पूर्णांक (*X_handler)(Display *, XErrorEvent *) = शून्य;
अटल पूर्णांक shm_errhandler(Display *d, XErrorEvent *e)
{
    अगर (e->error_code == BadAccess || e->error_code == BadRequest) {
        shm_error = True;
        वापस 0;
    }
    वापस X_handler(d, e);
}

अटल bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    वापस X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#पूर्ण_अगर // !NO_SHARED_MEMORY

bool X11_CreateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, SDL_PixelFormat *format,
                                व्योम **pixels, पूर्णांक *pitch)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    पूर्णांक w, h;

    SDL_Get_Window_आकार_In_Pixels(window, &w, &h);

    // Free the old framebuffer surface
    X11_DestroyWindowFramebuffer(_this, window);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    तथ्य->gc = X11_XCreateGC(display, तथ्य->xwindow, GCGraphicsExposures, &gcv);
    अगर (!तथ्य->gc) {
        वापस SDL_SetError("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    अगर (!X11_GetVisualInfoFromVisual(display, तथ्य->visual, &vinfo)) {
        वापस SDL_SetError("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    अगर (*format == SDL_PIXELFORMAT_UNKNOWN) {
        वापस SDL_SetError("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#अगर_अघोषित NO_SHARED_MEMORY
    अगर (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &तथ्य->shminfo;

        shminfo->shmid = shmget(IPC_PRIVATE, (माप_प्रकार)h * (*pitch), IPC_CREAT | 0777);
        अगर (shminfo->shmid >= 0) {
            shminfo->shmaddr = (अक्षर *)shmat(shminfo->shmid, शून्य, 0);
            shminfo->readOnly = False;
            अगर (shminfo->shmaddr != (अक्षर *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                अगर (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } अन्यथा {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, शून्य);
        } अन्यथा {
            shm_error = True;
        }
        अगर (!shm_error) {
            तथ्य->ximage = X11_XShmCreateImage(display, तथ्य->visual,
                                               vinfo.depth, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            अगर (!तथ्य->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } अन्यथा {
                // Done!
                तथ्य->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                तथ्य->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                वापस true;
            }
        }
    }
#पूर्ण_अगर // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((माप_प्रकार)h * (*pitch));
    अगर (!*pixels) {
        वापस false;
    }

    तथ्य->ximage = X11_XCreateImage(display, तथ्य->visual,
                                    vinfo.depth, ZPixmap, 0, (अक्षर *)(*pixels),
                                    w, h, 32, 0);
    अगर (!तथ्य->ximage) {
        SDL_free(*pixels);
        वापस SDL_SetError("Couldn't create XImage");
    }
    तथ्य->ximage->byte_order = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    वापस true;
}

bool X11_UpdateWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window, स्थिर SDL_Rect *rects,
                                पूर्णांक numrects)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display = तथ्य->videodata->display;
    पूर्णांक i;
    पूर्णांक x, y, w, h;
    पूर्णांक window_w, window_h;

    SDL_Get_Window_आकार_In_Pixels(window, &window_w, &window_h);

#अगर_अघोषित NO_SHARED_MEMORY
    अगर (तथ्य->use_mitshm) {
        क्रम (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            अगर (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                जारी;
            }
            अगर (x < 0) {
                x += w;
                w += rects[i].x;
            }
            अगर (y < 0) {
                y += h;
                h += rects[i].y;
            }
            अगर (x + w > window_w) {
                w = window_w - x;
            }
            अगर (y + h > window_h) {
                h = window_h - y;
            }

            X11_XShmPutImage(display, तथ्य->xwindow, तथ्य->gc, तथ्य->ximage,
                             x, y, x, y, w, h, False);
        }
    } अन्यथा
#पूर्ण_अगर // !NO_SHARED_MEMORY
    {
        क्रम (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            अगर (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                जारी;
            }
            अगर (x < 0) {
                x += w;
                w += rects[i].x;
            }
            अगर (y < 0) {
                y += h;
                h += rects[i].y;
            }
            अगर (x + w > window_w) {
                w = window_w - x;
            }
            अगर (y + h > window_h) {
                h = window_h - y;
            }

            X11_XPutImage(display, तथ्य->xwindow, तथ्य->gc, तथ्य->ximage,
                          x, y, x, y, w, h);
        }
    }

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(तथ्य->window);
#पूर्ण_अगर /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    वापस true;
}

व्योम X11_DestroyWindowFramebuffer(SDL_VideoDevice *_this, SDL_Window *window)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    Display *display;

    अगर (!तथ्य) {
        // The window wasn't fully initialized
        वापस;
    }

    display = तथ्य->videodata->display;

    अगर (तथ्य->ximage) {
        XDestroyImage(तथ्य->ximage);

#अगर_अघोषित NO_SHARED_MEMORY
        अगर (तथ्य->use_mitshm) {
            X11_XShmDetach(display, &तथ्य->shminfo);
            X11_XSync(display, False);
            shmdt(तथ्य->shminfo.shmaddr);
            तथ्य->use_mitshm = false;
        }
#पूर्ण_अगर // !NO_SHARED_MEMORY

        तथ्य->ximage = शून्य;
    }
    अगर (तथ्य->gc) {
        X11_XFreeGC(display, तथ्य->gc);
        तथ्य->gc = शून्य;
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
