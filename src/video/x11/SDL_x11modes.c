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

#ifdef SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11settings.h"
#ಅನ್ತರ್ಭಾವ "edid.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_displayevents_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"

// #define X11MODES_DEBUG

/* Timeout and revert mode switches if the timespan has elapsed without the window becoming fullscreen.
 * 5 seconds seems good from testing.
 */
#define MODE_SWITCH_TIMEOUT_NS SDL_NS_PER_SECOND * 5

/* I'm becoming more and more convinced that the application should never
 * use XRandR, and it's the window manager's responsibility to track and
 * manage display modes for fullscreen windows.  Right now XRandR is completely
 * broken with respect to window manager behavior on every window manager that
 * I can find.  For example, on Unity 3D if you show a fullscreen window while
 * the resolution is changing (within ~250 ms) your window will retain the
 * fullscreen state hint but be decorated and windowed.
 *
 * However, many people swear by it, so let them swear at it. :)
 */
// #define XRANDR_DISABLED_BY_DEFAULT

ಭಿನ್ನ X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    ದ್ವಿಗುಣ scale_factor = 0.0;

    // First use the forced scaling factor specified by the app/user
    ಧ್ರುವ ವರ್ಣ *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_FACTOR);
    ಯದಿ (hint && *hint) {
        ದ್ವಿಗುಣ ಮೌಲ್ಯ = SDL_atof(hint);
        ಯದಿ (ಮೌಲ್ಯ >= 1.0f && ಮೌಲ್ಯ <= 10.0f) {
            scale_factor = ಮೌಲ್ಯ;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    ಯದಿ (scale_factor <= 0.0) {
        ಪೂರ್ಣಾಙ್ಕ status, real_format;
        Atom real_type;
        Atom res_mgr;
        unsigned long ವಸ್ತುಗಳು_read, ವಸ್ತುಗಳು_ಎಡ;
        ವರ್ಣ *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        status = X11_XGetWindowProperty(display, ಬೇರು_Window(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ,
                                        (unsigned ವರ್ಣ **)&resource_manager);

        ಯದಿ (status == Success && resource_manager) {
            owns_resource_manager = true;
        } ಅನ್ಯಥಾ {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        ಯದಿ (resource_manager) {
            XrmDatabase db;
            Xrm_ಮೌಲ್ಯ ಮೌಲ್ಯ;
            ವರ್ಣ *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            ಯದಿ (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &ಮೌಲ್ಯ)) {
                ಯದಿ (ಮೌಲ್ಯ.addr && type && SDL_strcmp(type, "String") == 0) {
                    ಪೂರ್ಣಾಙ್ಕ dpi = SDL_atoi(ಮೌಲ್ಯ.addr);
                    scale_factor  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            ಯದಿ (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    ಯದಿ (scale_factor <= 0.0) {
        scale_factor = X11_Get_Xsettings_Client_Int_ಕೀಲಿ(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        ಯದಿ (scale_factor <= 0.0) {
            ಪೂರ್ಣಾಙ್ಕ dpi = X11_Get_Xsettings_Client_Int_ಕೀಲಿ(client, "Xft/DPI", -1);
            ಯದಿ (dpi > 0) {
                scale_factor = (ದ್ವಿಗುಣ) dpi / 1024.0;
                scale_factor /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    ಯದಿ (scale_factor <= 0.0) {
        ಧ್ರುವ ವರ್ಣ *scale_str = SDL_getenv("GDK_SCALE");
        ಯದಿ (scale_str) {
            scale_factor = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    ಯದಿ (scale_factor <= 0.0) {
        scale_factor = 1.0;
    }

    ಪ್ರತ್ಯಾಗಮ (ಭಿನ್ನ)scale_factor;
}

ಭಿನ್ನ X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    ಪ್ರತ್ಯಾಗಮ X11_GetGlobalContentScale(_this->internal->display, _this->internal->xsettings_data.xsettings);
}

ಸ್ಥಿರ bool get_visualinfo(Display *display, ಪೂರ್ಣಾಙ್ಕ screen, XVisualInfo *vinfo)
{
    ಧ್ರುವ ವರ್ಣ *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    ಪೂರ್ಣಾಙ್ಕ depth;

    // Look for an exact visual, if requested
    ಯದಿ (visual_id && *visual_id) {
        XVisualInfo *vi, template;
        ಪೂರ್ಣಾಙ್ಕ nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(visual_id, ರಿಕ್ತ, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        ಯದಿ (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }

    depth = DefaultDepth(display, screen);
    ಯದಿ ((X11_UseDirectColorVisuals() &&
         X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    ಪೂರ್ಣಾಙ್ಕ nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    ಯದಿ (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    ಯದಿ (vinfo->class == DirectColor || vinfo->class == TrueColor) {
        ಪೂರ್ಣಾಙ್ಕ bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_mask;
        Gmask = vinfo->visual->green_mask;
        Bmask = vinfo->visual->blue_mask;
        ಯದಿ (vinfo->depth == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } ಅನ್ಯಥಾ {
            Amask = 0;
        }

        bpp = vinfo->depth;
        ಯದಿ (bpp == 24) {
            ಪೂರ್ಣಾಙ್ಕ i, n;
            XPixmap_Format_ಮೌಲ್ಯಗಳು *p = X11_XListPixmapFormats(display, &n);
            ಯದಿ (p) {
                ಪ್ರತಿ (i = 0; i < n; ++i) {
                    ಯದಿ (p[i].depth == 24) {
                        bpp = p[i].bits_per_pixel;
                        ಭಙ್ಗ;
                    }
                }
                X11_XFree(p);
            }
        }

        ಪ್ರತ್ಯಾಗಮ SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    ಯದಿ (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        ವಿಕಲ್ಪ (vinfo->depth) {
        ಪಕ್ಷ 8:
            ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_INDEX8;
        ಪಕ್ಷ 4:
            ಯದಿ (BitmapBitOrder(display) == LSBFirst) {
                ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_INDEX4LSB;
            } ಅನ್ಯಥಾ {
                ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        ಪಕ್ಷ 1:
            ಯದಿ (BitmapBitOrder(display) == LSBFirst) {
                ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_INDEX1LSB;
            } ಅನ್ಯಥಾ {
                ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_UNKNOWN;
}

ಸ್ಥಿರ SDL_DisplayID X11_AddGenericDisplay(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ default_screen = DefaultScreen(dpy);
    Screen *screen = ScreenOfDisplay(dpy, default_screen);
    ಪೂರ್ಣಾಙ್ಕ scanline_pad, n, i;
    SDL_DisplayModeData *modedata;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    XPixmap_Format_ಮೌಲ್ಯಗಳು *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    ಯದಿ (!get_visualinfo(dpy, default_screen, &vinfo)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ಯದಿ (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Palettized video modes are no longer supported");
    }

    SDL_zero(mode);
    mode.w = WidthOfScreen(screen);
    mode.h = HeightOfScreen(screen);
    mode.format = pixelformat;

    displaydata = (SDL_DisplayData *)SDL_calloc(1, ಪರಿಮಾಣ(*displaydata));
    ಯದಿ (!displaydata) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_DisplayModeData));
    ಯದಿ (!modedata) {
        SDL_free(displaydata);
        ಪ್ರತ್ಯಾಗಮ false;
    }
    mode.internal = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ಯದಿ (pixmapformats) {
        ಪ್ರತಿ (i = 0; i < n; ++i) {
            ಯದಿ (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ಭಙ್ಗ;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (ವರ್ಣ *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_mode = mode;
    display.internal = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    ಪ್ರತ್ಯಾಗಮ SDL_AddVideoDisplay(&display, send_event);
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR

ಸ್ಥಿರ ಶೂನ್ಯ X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(ರಿಕ್ತ);
    ಯದಿ (displays) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ಧ್ರುವ SDL_DisplayData *displaydata = display->internal;
            ಯದಿ (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

ಸ್ಥಿರ bool CheckXRandR(Display *display, ಪೂರ್ಣಾಙ್ಕ *major, ಪೂರ್ಣಾಙ್ಕ *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ifdef XRANDR_DISABLED_BY_DEFAULT
    ಯದಿ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#endif
        ಪ್ರತ್ಯಾಗಮ false;
    }
#ಅನ್ಯಥಾ
    ಯದಿ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#endif
        ಪ್ರತ್ಯಾಗಮ false;
    }
#endif // XRANDR_DISABLED_BY_DEFAULT

    ಯದಿ (!SDL_X11_HAVE_XRANDR) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#endif
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    ಯದಿ (!X11_XRRQueryVersion(display, major, minor)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#endif
        *major = *minor = 0;
        ಪ್ರತ್ಯಾಗಮ false;
    }
#ifdef X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#endif
    ಪ್ರತ್ಯಾಗಮ true;
}

#define XRANDR_ROTATION_ಎಡ  (1 << 1)
#define XRANDR_ROTATION_ಬಲ (1 << 3)

ಸ್ಥಿರ ಶೂನ್ಯ CalculateXRandRRefreshRate(ಧ್ರುವ XRRModeInfo *info, ಪೂರ್ಣಾಙ್ಕ *numerator, ಪೂರ್ಣಾಙ್ಕ *denominator)
{
    unsigned ಪೂರ್ಣಾಙ್ಕ vTotal = info->vTotal;

    ಯದಿ (info->modeFlags & RR_DoubleScan) {
        // doublescan doubles the number of lines
        vTotal *= 2;
    }

    ಯದಿ (info->modeFlags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        vTotal /= 2;
    }

    ಯದಿ (info->hTotal && vTotal) {
        *numerator = info->dotClock;
        *denominator = (info->hTotal * vTotal);
    } ಅನ್ಯಥಾ {
        *numerator = 0;
        *denominator = 0;
    }
}

ಸ್ಥಿರ bool SetXRandRModeInfo(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode modeID, SDL_DisplayMode *mode)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < res->nmode; ++i) {
        ಧ್ರುವ XRRModeInfo *info = &res->modes[i];
        ಯದಿ (info->id == modeID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtcTransformAttributes *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            ಯದಿ (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            ಯದಿ (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            ಯದಿ (rotation & (XRANDR_ROTATION_ಎಡ | XRANDR_ROTATION_ಬಲ)) {
                mode->w = (info->height * scale_w + 0xffff) >> 16;
                mode->h = (info->width * scale_h + 0xffff) >> 16;
            } ಅನ್ಯಥಾ {
                mode->w = (info->width * scale_w + 0xffff) >> 16;
                mode->h = (info->height * scale_h + 0xffff) >> 16;
            }
            CalculateXRandRRefreshRate(info, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
            mode->internal->xrandr_mode = modeID;
#ifdef X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (ಪೂರ್ಣಾಙ್ಕ)modeID,
                    mode->screen_w, mode->screen_h, mode->refresh_rate_numerator, mode->refresh_rate_denominator);
#endif
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ bool Get_ಬೇರು_Window_Cardinal_Property(Display *dpy, ಪೂರ್ಣಾಙ್ಕ screen, ಧ್ರುವ ವರ್ಣ *name, Uint32 *ಮೌಲ್ಯ)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    ಯದಿ (atom == None) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪೂರ್ಣಾಙ್ಕ real_format;
    Atom real_type;
    unsigned long ವಸ್ತುಗಳು_read = 0, ವಸ್ತುಗಳು_ಎಡ = 0;
    unsigned ವರ್ಣ *propdata = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ status;
    bool result = false;

    status = X11_XGetWindowProperty(dpy, ಬೇರು_Window(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
    ಯದಿ (status == Success && propdata) {
        ಯದಿ (real_type == XA_CARDINAL && ವಸ್ತುಗಳು_read > 0) {
            ವಿಕಲ್ಪ (real_format) {
            ಪಕ್ಷ 8:
                *ಮೌಲ್ಯ = propdata[0];
                ಭಙ್ಗ;
            ಪಕ್ಷ 16:
                *ಮೌಲ್ಯ = propdata[0] | (propdata[1] << 8);
                ಭಙ್ಗ;
            ಸ್ವಭಾವ:
                *ಮೌಲ್ಯ = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                ಭಙ್ಗ;
            }
            result = true;
        }
        X11_XFree(propdata);
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

ಸ್ಥಿರ bool Get_ಬೇರು_Window_Bool_Property(Display *dpy, ಪೂರ್ಣಾಙ್ಕ screen, ಧ್ರುವ ವರ್ಣ *name, bool *ಮೌಲ್ಯ)
{
    Uint32 v;
    ಯದಿ (Get_ಬೇರು_Window_Cardinal_Property(dpy, screen, name, &v)) {
        *ಮೌಲ್ಯ = (v != 0);
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ bool Get_ಬೇರು_Window_Float_Property(Display *dpy, ಪೂರ್ಣಾಙ್ಕ screen, ಧ್ರುವ ವರ್ಣ *name, ಭಿನ್ನ *ಮೌಲ್ಯ)
{
    Uint32 v;
    ಯದಿ (Get_ಬೇರು_Window_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(ಮೌಲ್ಯ, &v, ಪರಿಮಾಣ(v));
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ bool IsSteamDeckOLEDDisplay(ಧ್ರುವ MonitorInfo *info)
{
    ಯದಿ (SDL_strcmp(info->manufacturer_code, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        ಯದಿ (info->product_code == 0x3003 || info->product_code == 0x3004) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ ಭಿನ್ನ GetGamescopeSDRWhiteLevel(Display *dpy, ಪೂರ್ಣಾಙ್ಕ screen, ಧ್ರುವ MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    ಯದಿ (!dpy) {
        ಪ್ರತ್ಯಾಗಮ 0.0f;
    }

    ಭಿನ್ನ SDR_white_level = 0.0f;
    bool external_display = false;
    ಯದಿ (Get_ಬೇರು_Window_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_ಬೇರು_Window_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } ಅನ್ಯಥಾ ಯದಿ (IsSteamDeckOLEDDisplay(info)) {
        /* Gamescope drives the Steam Deck OLED panel with gamma 2.2, mapping PQ content relative
           to the panel's maximum brightness (1000 nits). When HDR content is shown, Steam raises
           the backlight and applies input gains so that HDR content is 3x the brightness of SDR
           content, which puts the SDR white level at 1/3 of the maximum brightness, regardless
           of the brightness setting.

           The backlight can go up to 1000/600 of its SDR maximum, so the headroom actually
           available for HDR content is 3.0 until the brightness slider reaches its HDR range,
           tapering down to 1.67 at maximum brightness, and gamescope clips HDR content above
           that.

           We report the full 3.0 from the panel's maximum brightness, since content rarely reaches
           the top of that range.

           These values depend on Steam's backlight policy, and should eventually come from gamescope.
        */
        SDR_white_level = (ಭಿನ್ನ)info->max_luminance / 3.0f;
    } ಅನ್ಯಥಾ {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    ಪ್ರತ್ಯಾಗಮ SDR_white_level;
}

ಸ್ಥಿರ MonitorInfo *GetMonitorInfo(Display *dpy, ಪೂರ್ಣಾಙ್ಕ screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ real_format;
    Atom real_type;
    unsigned long ವಸ್ತುಗಳು_read = 0, ವಸ್ತುಗಳು_ಎಡ = 0;
    unsigned ವರ್ಣ *propdata = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ status;

    *gamescope = false;

    ಯದಿ (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_PATH = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        ಯದಿ (GAMESCOPE_DISPLAY_EDID_PATH != None) {
            status = X11_XGetWindowProperty(dpy, ಬೇರು_Window(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_PATH, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
            ಯದಿ (status == Success && propdata) {
                size_t size = 0;
                ಶೂನ್ಯ *data = SDL_LoadFile((ವರ್ಣ *)propdata, &size);
                ಯದಿ (data) {
                    info = decode_edid((uchar *)data, size);
                    ಯದಿ (info) {
                        *gamescope = true;
                    }
                    SDL_free(data);
                }
            }
            ಯದಿ (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    ಯದಿ (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        ಯದಿ (EDID != None) {
            ಪೂರ್ಣಾಙ್ಕ nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nprop; ++i) {
                ಯದಿ (props[i] == EDID) {
                    status = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
                    ಯದಿ (status == Success && propdata) {
                        info = decode_edid(propdata, ವಸ್ತುಗಳು_read);
                    }
                    ಯದಿ (propdata) {
                        X11_XFree(propdata);
                    }
                    ಭಙ್ಗ;
                }
            }

            ಯದಿ (props) {
                X11_XFree(props);
            }
        }
    }

#ifdef X11MODES_DEBUG
    ಯದಿ (info) {
        dump_monitor_info(info);
    }
#endif
    ಪ್ರತ್ಯಾಗಮ info;
}

ಸ್ಥಿರ ಶೂನ್ಯ SetXRandRDisplayName(MonitorInfo *info, ವರ್ಣ *name, size_t namelen, unsigned long widthmm, unsigned long heightmm)
{
    ಯದಿ (info) {
        SDL_strlcpy(name, info->dsc_product_name, namelen);
    }

    ಪೂರ್ಣಾಙ್ಕ inches = (ಪೂರ್ಣಾಙ್ಕ)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    ಯದಿ (*name && inches) {
        ಧ್ರುವ size_t len = SDL_strlen(name);
        (ಶೂನ್ಯ)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ifdef X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#endif
}

ಸ್ಥಿರ bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, ಪೂರ್ಣಾಙ್ಕ screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, ವರ್ಣ *display_name, size_t display_name_size)
{
    XRROutputInfo *output_info;
    ಪೂರ್ಣಾಙ್ಕ display_x, display_y;
    unsigned long display_mm_width, display_mm_height;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    SDL_DisplayModeData *modedata;
    RRMode modeID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_ಮೌಲ್ಯಗಳು *pixmapformats;
    ಪೂರ್ಣಾಙ್ಕ scanline_pad;
    ಪೂರ್ಣಾಙ್ಕ i, n;

    ಯದಿ (!display || !display_name) {
        ಪ್ರತ್ಯಾಗಮ false; // invalid parameters
    }

    ಯದಿ (!get_visualinfo(dpy, screen, &vinfo)) {
        ಪ್ರತ್ಯಾಗಮ false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ಯದಿ (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        ಪ್ರತ್ಯಾಗಮ false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ಯದಿ (pixmapformats) {
        ಪ್ರತಿ (i = 0; i < n; i++) {
            ಯದಿ (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ಭಙ್ಗ;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    ಯದಿ (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        ಪ್ರತ್ಯಾಗಮ false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_size);
    display_mm_width = output_info->mm_width;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    ಯದಿ (!crtc) {
        ಪ್ರತ್ಯಾಗಮ false; // oh well, ignore it.
    }

    SDL_zero(mode);
    modeID = crtc->mode;
    mode.w = crtc->width;
    mode.h = crtc->height;
    mode.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_DisplayData *)SDL_calloc(1, ಪರಿಮಾಣ(*displaydata));
    ಯದಿ (!displaydata) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_DisplayModeData));
    ಯದಿ (!modedata) {
        SDL_free(displaydata);
        ಪ್ರತ್ಯಾಗಮ false;
    }

    modedata->xrandr_mode = modeID;
    mode.internal = modedata;

    displaydata->screen = screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;
    displaydata->scanline_pad = scanline_pad;
    displaydata->x = display_x;
    displaydata->y = display_y;
    displaydata->use_xrandr = true;
    displaydata->xrandr_output = outputid;
    SDL_strlcpy(displaydata->connector_name, display_name, ಪರಿಮಾಣ(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    SetXRandRModeInfo(dpy, res, output_crtc, modeID, &mode);
    SetXRandRDisplayName(info, display_name, display_name_size, display_mm_width, display_mm_height);

    SDL_zero(*display);
    ಯದಿ (*display_name) {
        display->name = display_name;
    }
    display->desktop_mode = mode;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->internal = displaydata;

    ಯದಿ (info) {
        ಭಿನ್ನ SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        ಯದಿ (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } ಅನ್ಯಥಾ {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ifdef X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#endif
        ಯದಿ (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (ಭಿನ್ನ)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool X11_AddXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, ಪೂರ್ಣಾಙ್ಕ screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    ವರ್ಣ display_name[128];

    ಯದಿ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, ಪರಿಮಾಣ(display_name))) {
        ಪ್ರತ್ಯಾಗಮ true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    ಯದಿ (displayID == 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    ಯದಿ (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}


ಸ್ಥಿರ bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, ಪೂರ್ಣಾಙ್ಕ screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    ವರ್ಣ display_name[128];

    ಯದಿ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, ಪರಿಮಾಣ(display_name))) {
        ಪ್ರತ್ಯಾಗಮ false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_SetDesktopDisplayMode(existing_display, &display.desktop_mode);

    // update bounds
    ಯದಿ (existing_display->internal->x != display.internal->x ||
        existing_display->internal->y != display.internal->y) {
        existing_display->internal->x = display.internal->x;
        existing_display->internal->y = display.internal->y;
        SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
    }

    // update scale
    SDL_SetDisplayContentScale(existing_display, display.content_scale);

    // update HDR properties
    SDL_SetDisplayHDRProperties(existing_display, &display.HDR);

    // SDL_DisplayData is updated piece-meal above, free our local copy of this data
    SDL_free(display.internal);

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ XRRScreenResources *X11_GetScreenResources(Display *dpy, ಪೂರ್ಣಾಙ್ಕ screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, ಬೇರು_Window(dpy, screen));
    ಯದಿ (!res || res->noutput == 0) {
        ಯದಿ (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, ಬೇರು_Window(dpy, screen));
    }
    ಪ್ರತ್ಯಾಗಮ res;
}

ಶೂನ್ಯ X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ screencount = Screen_ಎಣಿಕೆ(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(ರಿಕ್ತ);
    ಯದಿ (!displays) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ಯದಿ (!res) {
            ಅನುವರ್ತ;
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ಧ್ರುವ SDL_DisplayData *displaydata = display->internal;
            ಯದಿ (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ screencount = Screen_ಎಣಿಕೆ(dpy);
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&ಅಂಕೆ_displays);
    ಯದಿ (!displays) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ಯದಿ (!res) {
            ಅನುವರ್ತ;
        }

        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ output = 0; output < res->noutput; output++) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ_displays; ++i) {
                ಯದಿ (!displays[i]) {
                    // We already removed this display from the list
                    ಅನುವರ್ತ;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                ಧ್ರುವ SDL_DisplayData *displaydata = display->internal;
                ಯದಿ (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    ಭಙ್ಗ;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ_displays; ++i) {
        ಯದಿ (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ಧ್ರುವ SDL_DisplayData *displaydata = display->internal;
            ಯದಿ (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_HandleXRandROutputChange(SDL_VideoDevice *_this, ಧ್ರುವ XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ i;

#ಯದಿ 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (unsigned ಪೂರ್ಣಾಙ್ಕ) ev->output, (unsigned ಪೂರ್ಣಾಙ್ಕ) ev->crtc, (unsigned ಪೂರ್ಣಾಙ್ಕ) ev->mode, (unsigned ಪೂರ್ಣಾಙ್ಕ) ev->rotation, (unsigned ಪೂರ್ಣಾಙ್ಕ) ev->connection);
#endif

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(ರಿಕ್ತ);
    ಯದಿ (displays) {
        ಪ್ರತಿ (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            ಧ್ರುವ SDL_DisplayData *displaydata = thisdisplay->internal;
            ಯದಿ (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                ಭಙ್ಗ;
            }
        }
        SDL_free(displays);
    }

    ಯದಿ (ev->connection == RR_Disconnected) { // output is going away
        ಯದಿ (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            ಯದಿ (_this->ಅಂಕೆ_displays == 1) {
                generic_display = X11_AddGenericDisplay(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            ಯದಿ (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } ಅನ್ಯಥಾ ಯದಿ (ev->connection == RR_Connected) { // output is coming online
        ಯದಿ (!display) {
            Display *dpy = ev->display;
            ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ಯದಿ (res) {
                X11_AddXRandRDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

ಶೂನ್ಯ X11_HandleXRandREvent(SDL_VideoDevice *_this, ಧ್ರುವ XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_assert(xevent->type == (videodata->xrandr_event_base + RRNotify));

    ವಿಕಲ್ಪ (((ಧ್ರುವ XRRNotifyEvent *)xevent)->subtype) {
    ಪಕ್ಷ RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (ಧ್ರುವ XRROutputChangeNotifyEvent *)xevent);
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_SortOutputsByPriorityHint(SDL_VideoDevice *_this)
{
    ಧ್ರುವ ವರ್ಣ *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    ಯದಿ (name_hint) {
        ವರ್ಣ *saveptr;
        ವರ್ಣ *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(ಪರಿಮಾಣ(SDL_VideoDisplay *) * _this->ಅಂಕೆ_displays);

        ಯದಿ (str && sorted_list) {
            ಪೂರ್ಣಾಙ್ಕ sorted_index = 0;

            // Sort the requested displays to the front of the list.
            ಧ್ರುವ ವರ್ಣ *token = SDL_strtok_r(str, ",", &saveptr);
            ಯಾವತ್ (token) {
                ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    ಯದಿ (d) {
                        SDL_DisplayData *data = d->internal;
                        ಯದಿ (SDL_strcmp(token, data->connector_name) == 0) {
                            sorted_list[sorted_index++] = d;
                            _this->displays[i] = ರಿಕ್ತ;
                            ಭಙ್ಗ;
                        }
                    }
                }

                token = SDL_strtok_r(ರಿಕ್ತ, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
                ಯದಿ (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, ಪರಿಮಾಣ(SDL_VideoDisplay *) * _this->ಅಂಕೆ_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ಸ್ಥಿರ bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ screencount = Screen_ಎಣಿಕೆ(dpy);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, ಬೇರು_Window(dpy, default_screen));
    ಪೂರ್ಣಾಙ್ಕ xrandr_error_base = 0;
    ಪೂರ್ಣಾಙ್ಕ looking_for_primary;
    ಪೂರ್ಣಾಙ್ಕ output;
    ಪೂರ್ಣಾಙ್ಕ screen;

    ಯದಿ (!X11_XRRQueryExtension(dpy, &data->xrandr_event_base, &xrandr_error_base)) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("XRRQueryExtension failed");
    }

    ಪ್ರತಿ (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        ಪ್ರತಿ (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            ಯದಿ (looking_for_primary && (screen != default_screen)) {
                ಅನುವರ್ತ;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ಯದಿ (!res) {
                ಅನುವರ್ತ;
            }

            ಪ್ರತಿ (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                ಯದಿ ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    ಅನುವರ್ತ;
                }
                ಯದಿ (!X11_AddXRandRDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    ಭಙ್ಗ;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_ಒಳಹರಿವು(dpy, ಬೇರು_Window(dpy, screen), RROutputChangeNotifyMask);
        }
    }

    ಯದಿ (_this->ಅಂಕೆ_displays == 0) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("No available displays");
    }

    X11_SortOutputsByPriorityHint(_this);

    ಪ್ರತ್ಯಾಗಮ true;
}
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
ಸ್ಥಿರ bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    ಯದಿ (X11_AddGenericDisplay(_this, true) == 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_VideoData *data = _this->internal;
        ಪೂರ್ಣಾಙ್ಕ xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        ಯದಿ (CheckXRandR(data->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            ಪ್ರತ್ಯಾಗಮ true;
        }
    }
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    ಪ್ರತ್ಯಾಗಮ X11_InitModes_StdXlib(_this);
}

bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display)
{
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    SDL_DisplayData *data = sdl_display->internal;
    SDL_DisplayMode mode;

    /* Unfortunately X11 requires the window to be created with the correct
     * visual and depth ahead of time, but the SDL API allows you to create
     * a window before setting the fullscreen display mode.  This means that
     * we have to use the same format for all windows and all display modes.
     * (or support recreating the window with a new visual behind the scenes)
     */
    SDL_zero(mode);
    mode.format = sdl_display->desktop_mode.format;

    ಯದಿ (data->use_xrandr) {
        Display *display = _this->internal->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, ಬೇರು_Window(display, data->screen));
        ಯದಿ (res) {
            SDL_DisplayModeData *modedata;
            XRROutputInfo *output_info;
            ಪೂರ್ಣಾಙ್ಕ i;

            output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
            ಯದಿ (output_info && output_info->connection != RR_Disconnected) {
                ಪ್ರತಿ (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_DisplayModeData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_DisplayModeData));
                    ಯದಿ (!modedata) {
                        ಅನುವರ್ತ;
                    }
                    mode.internal = modedata;

                    ಯದಿ (!SetXRandRModeInfo(display, res, output_info->crtc, output_info->modes[i], &mode) ||
                        !SDL_AddFullscreenDisplayMode(sdl_display, &mode)) {
                        SDL_free(modedata);
                    }
                }
            }
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
        }
    }
#endif // SDL_VIDEO_DRIVER_X11_XRANDR
    ಪ್ರತ್ಯಾಗಮ true;
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ (*PreXRRSetScreenSizeErrorHandler)(Display *, XErrorEvent *) = ರಿಕ್ತ;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ SDL_XRRSetScreenSizeErrHandler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    ಯದಿ ((e->error_code == BadMatch) || (e->error_code == Bad_ಮೌಲ್ಯ)) {
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಪ್ರತ್ಯಾಗಮ PreXRRSetScreenSizeErrorHandler(d, e);
}
#endif

bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *data = sdl_display->internal;

    viddata->last_mode_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    ಯದಿ (!viddata->is_xwayland) {
        ಯದಿ (sdl_display->current_mode != mode) {
            data->mode_switch_deadline_ns = SDL_GetTicksNS() + MODE_SWITCH_TIMEOUT_NS;
        } ಅನ್ಯಥಾ {
            data->mode_switch_deadline_ns = 0;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    ಯದಿ (data->use_xrandr) {
        Display *display = viddata->display;
        SDL_DisplayModeData *modedata = mode->internal;
        ಪೂರ್ಣಾಙ್ಕ mm_width, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        Status status;

        res = X11_XRRGetScreenResources(display, ಬೇರು_Window(display, data->screen));
        ಯದಿ (!res) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
        ಯದಿ (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        ಯದಿ (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("Couldn't get XRandR crtc info");
        }

        ಯದಿ (crtc->mode == modedata->xrandr_mode) {
#ifdef X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->mode, crtc->width, crtc->height);
#endif
            status = Success;
            ಗಚ್ಛ freeInfo;
        }

        X11_XGrabServer(display);
        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, ರಿಕ್ತ, 0);
        ಯದಿ (status != Success) {
            ಗಚ್ಛ ungrabServer;
        }

        mm_width = mode->w * DisplayWidthMM(display, data->screen) / DisplayWidth(display, data->screen);
        mm_height = mode->h * DisplayHeightMM(display, data->screen) / DisplayHeight(display, data->screen);

        /* !!! FIXME: this can get into a problem scenario when a window is
           bigger than a physical monitor in a configuration where one screen
           spans multiple physical monitors. A detailed reproduction case is
           discussed at https://github.com/libsdl-org/SDL/issues/4561 ...
           for now we cheat and just catch the X11 error and carry on, which
           is likely to cause subtle issues but is better than outright
           crashing */
        X11_XSync(display, False);
        PreXRRSetScreenSizeErrorHandler = X11_XSetErrorHandler(SDL_XRRSetScreenSizeErrHandler);
        X11_XRRSetScreenSize(display, ಬೇರು_Window(display, data->screen),
                             mode->w, mode->h, mm_width, mm_height);
        X11_XSync(display, False);
        X11_XSetErrorHandler(PreXRRSetScreenSizeErrorHandler);

        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      crtc->x, crtc->y, modedata->xrandr_mode, crtc->rotation,
                                      &data->xrandr_output, 1);

    ungrabServer:
        X11_XUngrabServer(display);
    freeInfo:
        X11_XRRFreeCrtcInfo(crtc);
        X11_XRRFreeOutputInfo(output_info);
        X11_XRRFreeScreenResources(res);

        ಯದಿ (status != Success) {
            ಪ್ರತ್ಯಾಗಮ SDL_SetError("X11_XRRSetCrtcConfig failed");
        }
    }
#ಅನ್ಯಥಾ
    (ಶೂನ್ಯ)data;
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_DisplayData *data = sdl_display->internal;

    rect->x = data->x;
    rect->y = data->y;
    rect->w = sdl_display->current_mode->w;
    rect->h = sdl_display->current_mode->h;
    ಪ್ರತ್ಯಾಗಮ true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    Atom _NET_WORKAREA;
    ಪೂರ್ಣಾಙ್ಕ real_format;
    Atom real_type;
    unsigned long ವಸ್ತುಗಳು_read = 0, ವಸ್ತುಗಳು_ಎಡ = 0;
    unsigned ವರ್ಣ *propdata = ರಿಕ್ತ;
    bool result = false;

    ಯದಿ (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    ಪೂರ್ಣಾಙ್ಕ status = X11_XGetWindowProperty(display, Default_ಬೇರು_Window(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &ವಸ್ತುಗಳು_read,
                                    &ವಸ್ತುಗಳು_ಎಡ, &propdata);
    ಯದಿ ((status == Success) && (ವಸ್ತುಗಳು_read >= 4)) {
        ಧ್ರುವ long *p = (long *)propdata;
        ಧ್ರುವ SDL_Rect usable = { (ಪೂರ್ಣಾಙ್ಕ)p[0], (ಪೂರ್ಣಾಙ್ಕ)p[1], (ಪೂರ್ಣಾಙ್ಕ)p[2], (ಪೂರ್ಣಾಙ್ಕ)p[3] };
        result = true;
        ಯದಿ (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    ಯದಿ (propdata) {
        X11_XFree(propdata);
    }

    ಪ್ರತ್ಯಾಗಮ result;
}

#endif // SDL_VIDEO_DRIVER_X11
