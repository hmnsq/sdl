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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11framebuffer.h"
#అన్తర్భావ "SDL_x11xsync.h"

#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం

// Shared memory error handler routine
స్థిర పూర్ణాంకం shm_error;
స్థిర పూర్ణాంకం (*X_handler)(Display *, XErrorEvent *) = ఖాళీ;
స్థిర పూర్ణాంకం shm_errhandler(Display *d, XErrorEvent *e)
{
    ఒకవేళ (e->error_సంకేతం == BadAccess || e->error_సంకేతం == BadRequest) {
        shm_error = True;
        తిరిగి 0;
    }
    తిరిగి X_handler(d, e);
}

స్థిర bool have_mitshm(Display *dpy)
{
    // Only use shared memory on local X servers
    తిరిగి X11_XShmQueryExtension(dpy) ? SDL_X11_HAVE_SHM : false;
}

#అయితే_ముగింపు // !NO_SHARED_MEMORY

bool X11_Create_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PixelFormat *format,
                                శూన్య **pixels, పూర్ణాంకం *pitch)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    XGCValues gcv;
    XVisualInfo vinfo;
    పూర్ణాంకం w, h;

    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &w, &h);

    // Free the old framebuffer surface
    X11_Destroy_కిటికీ_Framebuffer(_this, కిటికీ);

    // Create the graphics context for drawing
    gcv.graphics_exposures = False;
    దత్తాంశం->gc = X11_XCreateGC(display, దత్తాంశం->xwindow, GCGraphicsExposures, &gcv);
    ఒకవేళ (!దత్తాంశం->gc) {
        తిరిగి SDL_సమితి_Error("Couldn't create graphics context");
    }

    // Find out the pixel format and depth
    ఒకవేళ (!X11_GetVisualInfoFromVisual(display, దత్తాంశం->visual, &vinfo)) {
        తిరిగి SDL_సమితి_Error("Couldn't get window visual information");
    }

    *format = X11_GetPixelFormatFromVisualInfo(display, &vinfo);
    ఒకవేళ (*format == SDL_PIXELFORMAT_UNKNOWN) {
        తిరిగి SDL_సమితి_Error("Unknown window pixel format");
    }

    // Calculate pitch
    *pitch = (((w * SDL_BYTESPERPIXEL(*format)) + 3) & ~3);

    // Create the actual image
#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
    ఒకవేళ (have_mitshm(display)) {
        XShmSegmentInfo *shminfo = &దత్తాంశం->shminfo;

        shminfo->shmid = shmget(IPC_వ్యక్తిగత, (size_t)h * (*pitch), IPC_CREAT | 0777);
        ఒకవేళ (shminfo->shmid >= 0) {
            shminfo->shmaddr = (అక్షరం *)shmat(shminfo->shmid, ఖాళీ, 0);
            shminfo->readOnly = False;
            ఒకవేళ (shminfo->shmaddr != (అక్షరం *)-1) {
                shm_error = False;
                X_handler = X11_XSetErrorHandler(shm_errhandler);
                X11_XShmAttach(display, shminfo);
                X11_XSync(display, False);
                X11_XSetErrorHandler(X_handler);
                ఒకవేళ (shm_error) {
                    shmdt(shminfo->shmaddr);
                }
            } లేకపోతే {
                shm_error = True;
            }
            shmctl(shminfo->shmid, IPC_RMID, ఖాళీ);
        } లేకపోతే {
            shm_error = True;
        }
        ఒకవేళ (!shm_error) {
            దత్తాంశం->ximage = X11_XShmCreateImage(display, దత్తాంశం->visual,
                                               vinfo.లోతు_2, ZPixmap,
                                               shminfo->shmaddr, shminfo,
                                               w, h);
            ఒకవేళ (!దత్తాంశం->ximage) {
                X11_XShmDetach(display, shminfo);
                X11_XSync(display, False);
                shmdt(shminfo->shmaddr);
            } లేకపోతే {
                // Done!
                దత్తాంశం->ximage->byte_క్రమం = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
                దత్తాంశం->use_mitshm = true;
                *pixels = shminfo->shmaddr;
                తిరిగి true;
            }
        }
    }
#అయితే_ముగింపు // not NO_SHARED_MEMORY

    *pixels = SDL_malloc((size_t)h * (*pitch));
    ఒకవేళ (!*pixels) {
        తిరిగి false;
    }

    దత్తాంశం->ximage = X11_XCreateImage(display, దత్తాంశం->visual,
                                    vinfo.లోతు_2, ZPixmap, 0, (అక్షరం *)(*pixels),
                                    w, h, 32, 0);
    ఒకవేళ (!దత్తాంశం->ximage) {
        SDL_free(*pixels);
        తిరిగి SDL_సమితి_Error("Couldn't create XImage");
    }
    దత్తాంశం->ximage->byte_క్రమం = (SDL_BYTEORDER == SDL_BIG_ENDIAN) ? MSBFirst : LSBFirst;
    తిరిగి true;
}

bool X11_Update_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, స్థిరరాశి SDL_Rect *rects,
                                పూర్ణాంకం numrects)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display = దత్తాంశం->videodata->display;
    పూర్ణాంకం i;
    పూర్ణాంకం x, y, w, h;
    పూర్ణాంకం కిటికీ_w, కిటికీ_h;

    SDL_Get_కిటికీ_కొలత_లోపల_Pixels(కిటికీ, &కిటికీ_w, &కిటికీ_h);

#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
    ఒకవేళ (దత్తాంశం->use_mitshm) {
        కొరకు (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ఒకవేళ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                కొనసాగు;
            }
            ఒకవేళ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ఒకవేళ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ఒకవేళ (x + w > కిటికీ_w) {
                w = కిటికీ_w - x;
            }
            ఒకవేళ (y + h > కిటికీ_h) {
                h = కిటికీ_h - y;
            }

            X11_XShmPutImage(display, దత్తాంశం->xwindow, దత్తాంశం->gc, దత్తాంశం->ximage,
                             x, y, x, y, w, h, False);
        }
    } లేకపోతే
#అయితే_ముగింపు // !NO_SHARED_MEMORY
    {
        కొరకు (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            ఒకవేళ (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                // Clipped?
                కొనసాగు;
            }
            ఒకవేళ (x < 0) {
                x += w;
                w += rects[i].x;
            }
            ఒకవేళ (y < 0) {
                y += h;
                h += rects[i].y;
            }
            ఒకవేళ (x + w > కిటికీ_w) {
                w = కిటికీ_w - x;
            }
            ఒకవేళ (y + h > కిటికీ_h) {
                h = కిటికీ_h - y;
            }

            X11_XPutImage(display, దత్తాంశం->xwindow, దత్తాంశం->gc, దత్తాంశం->ximage,
                          x, y, x, y, w, h);
        }
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XSYNC
    X11_HandlePresent(దత్తాంశం->కిటికీ);
#అయితే_ముగింపు /* SDL_VIDEO_DRIVER_X11_XSYNC */

    X11_XSync(display, False);

    తిరిగి true;
}

శూన్య X11_Destroy_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    Display *display;

    ఒకవేళ (!దత్తాంశం) {
        // The window wasn't fully initialized
        తిరిగి;
    }

    display = దత్తాంశం->videodata->display;

    ఒకవేళ (దత్తాంశం->ximage) {
        XDestroyImage(దత్తాంశం->ximage);

#నిర్వచితం_కాకపోతే NO_SHARED_జ్ఞాపకం
        ఒకవేళ (దత్తాంశం->use_mitshm) {
            X11_XShmDetach(display, &దత్తాంశం->shminfo);
            X11_XSync(display, False);
            shmdt(దత్తాంశం->shminfo.shmaddr);
            దత్తాంశం->use_mitshm = false;
        }
#అయితే_ముగింపు // !NO_SHARED_MEMORY

        దత్తాంశం->ximage = ఖాళీ;
    }
    ఒకవేళ (దత్తాంశం->gc) {
        X11_XFreeGC(display, దత్తాంశం->gc);
        దత్తాంశం->gc = ఖాళీ;
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
