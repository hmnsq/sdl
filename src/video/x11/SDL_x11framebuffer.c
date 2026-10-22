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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11framebuffer.h"
#अन्तर्भाव "SDL_x11xsync.h"

#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः

// Shared memory error handler routine
स्थिर पूर्णाङ्क shm_error;
स्थिर पूर्णाङ्क (*X_handler)(Display *, XErrorEvent *) = रिक्त;
स्थिर पूर्णाङ्क shm_errhandler(Display *d, XErrorEvent *e)
{
    यदि (e->error_संहिता == BadAccess || e->error_संहिता == BadRequest) {
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

#यदि_अन्तः // !NO_SHARED_MEMORY

bool X11_Create_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PixelFormat *format,
                                शून्य **pixels, पूर्णाङ्क *pitch)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    पूर्णाङ्क w, h;

    SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &w, &h);

    // Free the old framebuffer surface
    X11_Destroy_गवाक्षः_Framebuffer(_this, गवाक्षः);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    दत्त->gc = X11_XCreateGC(display, दत्त->xwindow, GCGraphicsExposures, &gcv);
    यदि (!दत्त->gc) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    यदि (!X11_GetVisualInfoFromVisual(display, दत्त->visual, &vinfo)) {
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    यदि (*format == SDL_PIXELFORMAT_UNKNOWN) {
        प्रत्यागम SDL_समुच्चयः_Error("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
    यदि (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &दत्त->shminfo;

        shminfo->shmid = shmget(IPC_वैयक्तिकम्, (size_t)h * (*pitch), IPC_CREAT | 0777);
        यदि (shminfo->shmid >= 0) {
            shminfo->shmaddr = (वर्ण *)shmat(shminfo->shmid, रिक्त, 0);
            shminfo->readOnly = False;
            यदि (shminfo->shmaddr != (वर्ण *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                यदि (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } अन्यथा {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, रिक्त);
        } अन्यथा {
            shm_error = True;
        }
        यदि (!shm_error) {
            दत्त->ximage = X11_XShmCreateImage(display, दत्त->visual,
                                               vinfo.गभीरता_2, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            यदि (!दत्त->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } अन्यथा {
                // Done!
                दत्त->ximage->byte_क्रमः = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                दत्त->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                प्रत्यागम true;
            }
        }
    }
#यदि_अन्तः // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    यदि (!*pixels) {
        प्रत्यागम false;
    }

    दत्त->ximage = X11_XCreateImage(display, दत्त->visual,
                                    vinfo.गभीरता_2, ZPixmap, 0, (वर्ण *)(*pixels),
                                    w, h, 32, 0);
    यदि (!दत्त->ximage) {
        SDL_free(*pixels);
        प्रत्यागम SDL_समुच्चयः_Error("Couldn't create XImage");
    }
    दत्त->ximage->byte_क्रमः = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    प्रत्यागम true;
}

bool X11_Update_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, ध्रुव SDL_Rect *rects,
                                पूर्णाङ्क numrects)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display = दत्त->videodata->display;
    पूर्णाङ्क i;
    पूर्णाङ्क x, y, w, h;
    पूर्णाङ्क गवाक्षः_w, गवाक्षः_h;

    SDL_Get_गवाक्षः_आकार_अन्तर्_Pixels(गवाक्षः, &गवाक्षः_w, &गवाक्षः_h);

#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
    यदि (दत्त->use_mitshm) {
        प्रति (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            यदि (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                अनुवर्त;
            }
            यदि (x < 0) {
                x += w;
                w += rects[i].x;
            }
            यदि (y < 0) {
                y += h;
                h += rects[i].y;
            }
            यदि (x + w > गवाक्षः_w) {
                w = गवाक्षः_w - x;
            }
            यदि (y + h > गवाक्षः_h) {
                h = गवाक्षः_h - y;
            }

            X11_XShmPutImage(display, दत्त->xwindow, दत्त->gc, दत्त->ximage,
                             x, y, x, y, w, h, False);
        }
    } अन्यथा
#यदि_अन्तः // !NO_SHARED_MEMORY
    {
        प्रति (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            यदि (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                अनुवर्त;
            }
            यदि (x < 0) {
                x += w;
                w += rects[i].x;
            }
            यदि (y < 0) {
                y += h;
                h += rects[i].y;
            }
            यदि (x + w > गवाक्षः_w) {
                w = गवाक्षः_w - x;
            }
            यदि (y + h > गवाक्षः_h) {
                h = गवाक्षः_h - y;
            }

            X11_XPutImage(display, दत्त->xwindow, दत्त->gc, दत्त->ximage,
                          x, y, x, y, w, h);
        }
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(दत्त->गवाक्षः);
#यदि_अन्तः /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    प्रत्यागम true;
}

शून्य X11_Destroy_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    Display *display;

    यदि (!दत्त) {
        // The window wasn't fully initialized
        प्रत्यागम;
    }

    display = दत्त->videodata->display;

    यदि (दत्त->ximage) {
        XDestroyImage(दत्त->ximage);

#यदि_अपरिभाषितम् NO_SHARED_स्मृतिः
        यदि (दत्त->use_mitshm) {
            X11_XShmDetach(display, &दत्त->shminfo);
            X11_XSync(display, False);
            shmdt(दत्त->shminfo.shmaddr);
            दत्त->use_mitshm = false;
        }
#यदि_अन्तः // !NO_SHARED_MEMORY

        दत्त->ximage = रिक्त;
    }
    यदि (दत्त->gc) {
        X11_XFreeGC(display, दत्त->gc);
        दत्त->gc = रिक्त;
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
