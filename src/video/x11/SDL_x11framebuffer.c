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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11framebuffer.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xsync.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ

// Shared memory error handler routine
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ shm_error;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ (*X_handler)(Display *, XErrorEvent *) = ಖಾಲಿ;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ shm_errhandler(Display *d, XErrorEvent *e)
{
    ಆದರೆ (e->error_ಸಂಕೇತ == BadAccess || e->error_ಸಂಕೇತ == BadRequest) {
        shm_error = True;
        ಹಿಂತಿರುಗಿ 0;
    }
    ಹಿಂತಿರುಗಿ X_handler(d, e);
}

ಸ್ಥಿರ bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    ಹಿಂತಿರುಗಿ X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#ಆದರೆ_ಅಂತ್ಯ // !NO_SHARED_MEMORY

bool X11_Create_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_PixelFormat *format,
                                ಶೂನ್ಯ **pixels, ಪೂರ್ಣಾಂಕ *pitch)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    ಪೂರ್ಣಾಂಕ w, h;

    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &w, &h);

    // Free the old framebuffer surface
    X11_Destroy_ಕಿಟಕಿ_Framebuffer(_this, ಕಿಟಕಿ);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    ದತ್ತಾಂಶ->gc = X11_XCreateGC(display, ದತ್ತಾಂಶ->xwindow, GCGraphicsExposures, &gcv);
    ಆದರೆ (!ದತ್ತಾಂಶ->gc) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    ಆದರೆ (!X11_GetVisualInfoFromVisual(display, ದತ್ತಾಂಶ->visual, &vinfo)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    ಆದರೆ (*format == SDL_PIXELFORMAT_UNKNOWN) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
    ಆದರೆ (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &ದತ್ತಾಂಶ->shminfo;

        shminfo->shmid = shmget(IPC_ಖಾಸಗಿ, (size_t)h * (*pitch), IPC_CREAT | 0777);
        ಆದರೆ (shminfo->shmid >= 0) {
            shminfo->shmaddr = (ಅಕ್ಷರ *)shmat(shminfo->shmid, ಖಾಲಿ, 0);
            shminfo->readOnly = False;
            ಆದರೆ (shminfo->shmaddr != (ಅಕ್ಷರ *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                ಆದರೆ (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, ಖಾಲಿ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            shm_error = True;
        }
        ಆದರೆ (!shm_error) {
            ದತ್ತಾಂಶ->ximage = X11_XShmCreateImage(display, ದತ್ತಾಂಶ->visual,
                                               vinfo.ಆಳ_2, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            ಆದರೆ (!ದತ್ತಾಂಶ->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } ಇಲ್ಲದಿದ್ದರೆ {
                // Done!
                ದತ್ತಾಂಶ->ximage->byte_ಕ್ರಮ = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                ದತ್ತಾಂಶ->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                ಹಿಂತಿರುಗಿ true;
            }
        }
    }
#ಆದರೆ_ಅಂತ್ಯ // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    ಆದರೆ (!*pixels) {
        ಹಿಂತಿರುಗಿ false;
    }

    ದತ್ತಾಂಶ->ximage = X11_XCreateImage(display, ದತ್ತಾಂಶ->visual,
                                    vinfo.ಆಳ_2, ZPixmap, 0, (ಅಕ್ಷರ *)(*pixels),
                                    w, h, 32, 0);
    ಆದರೆ (!ದತ್ತಾಂಶ->ximage) {
        SDL_free(*pixels);
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't create XImage");
    }
    ದತ್ತಾಂಶ->ximage->byte_ಕ್ರಮ = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    ಹಿಂತಿರುಗಿ true;
}

bool X11_Update_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಸ್ಥಿರಾಂಕ SDL_Rect *rects,
                                ಪೂರ್ಣಾಂಕ numrects)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->videodata->display;
    ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ x, y, w, h;
    ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_w, ಕಿಟಕಿ_h;

    SDL_Get_ಕಿಟಕಿ_ಗಾತ್ರ_ಒಳ_Pixels(ಕಿಟಕಿ, &ಕಿಟಕಿ_w, &ಕಿಟಕಿ_h);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
    ಆದರೆ (ದತ್ತಾಂಶ->use_mitshm) {
        ಗಾಗಿ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ಆದರೆ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                ಮುಂದುವರಿ;
            }
            ಆದರೆ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ಆದರೆ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ಆದರೆ (x + w > ಕಿಟಕಿ_w) {
                w = ಕಿಟಕಿ_w - x;
            }
            ಆದರೆ (y + h > ಕಿಟಕಿ_h) {
                h = ಕಿಟಕಿ_h - y;
            }

            X11_XShmPutImage(display, ದತ್ತಾಂಶ->xwindow, ದತ್ತಾಂಶ->gc, ದತ್ತಾಂಶ->ximage,
                             x, y, x, y, w, h, False);
        }
    } ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ // !NO_SHARED_MEMORY
    {
        ಗಾಗಿ (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ಆದರೆ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                ಮುಂದುವರಿ;
            }
            ಆದರೆ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ಆದರೆ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ಆದರೆ (x + w > ಕಿಟಕಿ_w) {
                w = ಕಿಟಕಿ_w - x;
            }
            ಆದರೆ (y + h > ಕಿಟಕಿ_h) {
                h = ಕಿಟಕಿ_h - y;
            }

            X11_XPutImage(display, ದತ್ತಾಂಶ->xwindow, ದತ್ತಾಂಶ->gc, ದತ್ತಾಂಶ->ximage,
                          x, y, x, y, w, h);
        }
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(ದತ್ತಾಂಶ->ಕಿಟಕಿ);
#ಆದರೆ_ಅಂತ್ಯ /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_Destroy_ಕಿಟಕಿ_Framebuffer(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    Display *display;

    ಆದರೆ (!ದತ್ತಾಂಶ) {
        // The window wasn't fully initialized
        ಹಿಂತಿರುಗಿ;
    }

    display = ದತ್ತಾಂಶ->videodata->display;

    ಆದರೆ (ದತ್ತಾಂಶ->ximage) {
        XDestroyImage(ದತ್ತಾಂಶ->ximage);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SHARED_ಸ್ಮರಣೆ
        ಆದರೆ (ದತ್ತಾಂಶ->use_mitshm) {
            X11_XShmDetach(display, &ದತ್ತಾಂಶ->shminfo);
            X11_XSync(display, False);
            shmdt(ದತ್ತಾಂಶ->shminfo.shmaddr);
            ದತ್ತಾಂಶ->use_mitshm = false;
        }
#ಆದರೆ_ಅಂತ್ಯ // !NO_SHARED_MEMORY

        ದತ್ತಾಂಶ->ximage = ಖಾಲಿ;
    }
    ಆದರೆ (ದತ್ತಾಂಶ->gc) {
        X11_XFreeGC(display, ದತ್ತಾಂಶ->gc);
        ದತ್ತಾಂಶ->gc = ಖಾಲಿ;
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
