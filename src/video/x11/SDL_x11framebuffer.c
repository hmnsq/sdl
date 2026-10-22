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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11framebuffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xsync.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ

// Shared memory error handler routine
ਸਥਿਰ ਪੂਰਨ shm_error;
ਸਥਿਰ ਪੂਰਨ (*X_handler)(Display *, XErrorEvent *) = ਨਿਰਾ;
ਸਥਿਰ ਪੂਰਨ shm_errhandler(Display *d, XErrorEvent *e)
{
    ਜੇ (e->error_ਕੋਡ == BadAccess || e->error_ਕੋਡ == BadRequest) {
        shm_error = True;
        ਵਾਪਸ 0;
    }
    ਵਾਪਸ X_handler(d, e);
}

ਸਥਿਰ bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    ਵਾਪਸ X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#ਜੇ_ਅੰਤ // !NO_SHARED_MEMORY

bool X11_Create_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_PixelFormat *format,
                                ਖਾਲੀ **pixels, ਪੂਰਨ *pitch)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    ਪੂਰਨ w, h;

    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &w, &h);

    // Free the old framebuffer surface
    X11_Destroy_ਖਿੜਕੀ_Framebuffer(_this, ਖਿੜਕੀ);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    ਅੰਕੜੇ->gc = X11_XCreateGC(display, ਅੰਕੜੇ->xwindow, GCGraphicsExposures, &gcv);
    ਜੇ (!ਅੰਕੜੇ->gc) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    ਜੇ (!X11_GetVisualInfoFromVisual(display, ਅੰਕੜੇ->visual, &vinfo)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    ਜੇ (*format == SDL_PIXELFORMAT_UNKNOWN) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
    ਜੇ (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &ਅੰਕੜੇ->shminfo;

        shminfo->shmid = shmget(IPC_ਨਿੱਜੀ, (size_t)h * (*pitch), IPC_CREAT | 0777);
        ਜੇ (shminfo->shmid >= 0) {
            shminfo->shmaddr = (ਅੱਖਰ *)shmat(shminfo->shmid, ਨਿਰਾ, 0);
            shminfo->readOnly = False;
            ਜੇ (shminfo->shmaddr != (ਅੱਖਰ *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                ਜੇ (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } ਨਹੀਂਤਾਂ {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, ਨਿਰਾ);
        } ਨਹੀਂਤਾਂ {
            shm_error = True;
        }
        ਜੇ (!shm_error) {
            ਅੰਕੜੇ->ximage = X11_XShmCreateImage(display, ਅੰਕੜੇ->visual,
                                               vinfo.ਡੂੰਘਾਈ_2, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            ਜੇ (!ਅੰਕੜੇ->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } ਨਹੀਂਤਾਂ {
                // Done!
                ਅੰਕੜੇ->ximage->byte_ਕ੍ਰਮ = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                ਅੰਕੜੇ->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                ਵਾਪਸ true;
            }
        }
    }
#ਜੇ_ਅੰਤ // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    ਜੇ (!*pixels) {
        ਵਾਪਸ false;
    }

    ਅੰਕੜੇ->ximage = X11_XCreateImage(display, ਅੰਕੜੇ->visual,
                                    vinfo.ਡੂੰਘਾਈ_2, ZPixmap, 0, (ਅੱਖਰ *)(*pixels),
                                    w, h, 32, 0);
    ਜੇ (!ਅੰਕੜੇ->ximage) {
        SDL_free(*pixels);
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't create XImage");
    }
    ਅੰਕੜੇ->ximage->byte_ਕ੍ਰਮ = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    ਵਾਪਸ true;
}

bool X11_Update_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਅਚਲ SDL_Rect *rects,
                                ਪੂਰਨ numrects)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->videodata->display;
    ਪੂਰਨ i;
    ਪੂਰਨ x, y, w, h;
    ਪੂਰਨ ਖਿੜਕੀ_w, ਖਿੜਕੀ_h;

    SDL_Get_ਖਿੜਕੀ_ਮਾਪ_ਵਿੱਚ_Pixels(ਖਿੜਕੀ, &ਖਿੜਕੀ_w, &ਖਿੜਕੀ_h);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
    ਜੇ (ਅੰਕੜੇ->use_mitshm) {
        ਲਈ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ਜੇ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                ਜਾਰੀ;
            }
            ਜੇ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ਜੇ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ਜੇ (x + w > ਖਿੜਕੀ_w) {
                w = ਖਿੜਕੀ_w - x;
            }
            ਜੇ (y + h > ਖਿੜਕੀ_h) {
                h = ਖਿੜਕੀ_h - y;
            }

            X11_XShmPutImage(display, ਅੰਕੜੇ->xwindow, ਅੰਕੜੇ->gc, ਅੰਕੜੇ->ximage,
                             x, y, x, y, w, h, False);
        }
    } ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ // !NO_SHARED_MEMORY
    {
        ਲਈ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ਜੇ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                ਜਾਰੀ;
            }
            ਜੇ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ਜੇ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ਜੇ (x + w > ਖਿੜਕੀ_w) {
                w = ਖਿੜਕੀ_w - x;
            }
            ਜੇ (y + h > ਖਿੜਕੀ_h) {
                h = ਖਿੜਕੀ_h - y;
            }

            X11_XPutImage(display, ਅੰਕੜੇ->xwindow, ਅੰਕੜੇ->gc, ਅੰਕੜੇ->ximage,
                          x, y, x, y, w, h);
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(ਅੰਕੜੇ->ਖਿੜਕੀ);
#ਜੇ_ਅੰਤ /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    ਵਾਪਸ true;
}

ਖਾਲੀ X11_Destroy_ਖਿੜਕੀ_Framebuffer(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    Display *display;

    ਜੇ (!ਅੰਕੜੇ) {
        // The window wasn't fully initialized
        ਵਾਪਸ;
    }

    display = ਅੰਕੜੇ->videodata->display;

    ਜੇ (ਅੰਕੜੇ->ximage) {
        XDestroyImage(ਅੰਕੜੇ->ximage);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SHARED_ਸਮ੍ਰਿਤੀ
        ਜੇ (ਅੰਕੜੇ->use_mitshm) {
            X11_XShmDetach(display, &ਅੰਕੜੇ->shminfo);
            X11_XSync(display, False);
            shmdt(ਅੰਕੜੇ->shminfo.shmaddr);
            ਅੰਕੜੇ->use_mitshm = false;
        }
#ਜੇ_ਅੰਤ // !NO_SHARED_MEMORY

        ਅੰਕੜੇ->ximage = ਨਿਰਾ;
    }
    ਜੇ (ਅੰਕੜੇ->gc) {
        X11_XFreeGC(display, ਅੰਕੜੇ->gc);
        ਅੰਕੜੇ->gc = ਨਿਰਾ;
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
