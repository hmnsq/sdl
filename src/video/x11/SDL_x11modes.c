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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ଅନ୍ତର୍ଭାଵ "SDL_x11video.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11settings.h"
#ଅନ୍ତର୍ଭାଵ "edid.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_displayevents_c.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_pixels_c.h"

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

ଦଶମିକ X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    ଦ୍ୱିଗୁଣ scale_factor = 0.0;

    // First use the forced scaling factor specified by the app/user
    ଅଚଳ ଅକ୍ଷର *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_FACTOR);
    ଯଦି (hint && *hint) {
        ଦ୍ୱିଗୁଣ ମୂଲ୍ୟ = SDL_atof(hint);
        ଯଦି (ମୂଲ୍ୟ >= 1.0f && ମୂଲ୍ୟ <= 10.0f) {
            scale_factor = ମୂଲ୍ୟ;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    ଯଦି (scale_factor <= 0.0) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା status, real_format;
        Atom real_type;
        Atom res_mgr;
        unsigned long ବସ୍ତୁଗୁଡ଼ିକ_read, ବସ୍ତୁଗୁଡ଼ିକ_ବାମ;
        ଅକ୍ଷର *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        status = X11_XGetWindowProperty(display, ମୂଳ_Window(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &ବସ୍ତୁଗୁଡ଼ିକ_read, &ବସ୍ତୁଗୁଡ଼ିକ_ବାମ,
                                        (unsigned ଅକ୍ଷର **)&resource_manager);

        ଯଦି (status == Success && resource_manager) {
            owns_resource_manager = true;
        } ଅନ୍ୟଥା {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        ଯଦି (resource_manager) {
            XrmDatabase db;
            Xrm_ମୂଲ୍ୟ ମୂଲ୍ୟ;
            ଅକ୍ଷର *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            ଯଦି (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &ମୂଲ୍ୟ)) {
                ଯଦି (ମୂଲ୍ୟ.addr && type && SDL_strcmp(type, "String") == 0) {
                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dpi = SDL_atoi(ମୂଲ୍ୟ.addr);
                    scale_factor  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            ଯଦି (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    ଯଦି (scale_factor <= 0.0) {
        scale_factor = X11_Get_Xsettings_Client_Int_ଚାବି(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        ଯଦି (scale_factor <= 0.0) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା dpi = X11_Get_Xsettings_Client_Int_ଚାବି(client, "Xft/DPI", -1);
            ଯଦି (dpi > 0) {
                scale_factor = (ଦ୍ୱିଗୁଣ) dpi / 1024.0;
                scale_factor /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    ଯଦି (scale_factor <= 0.0) {
        ଅଚଳ ଅକ୍ଷର *scale_str = SDL_getenv("GDK_SCALE");
        ଯଦି (scale_str) {
            scale_factor = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    ଯଦି (scale_factor <= 0.0) {
        scale_factor = 1.0;
    }

    ଫେରନ୍ତୁ (ଦଶମିକ)scale_factor;
}

ଦଶମିକ X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ X11_GetGlobalContentScale(_this->internal->display, _this->internal->xsettings_data.xsettings);
}

ସ୍ଥିର bool get_visualinfo(Display *display, ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen, XVisualInfo *vinfo)
{
    ଅଚଳ ଅକ୍ଷର *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth;

    // Look for an exact visual, if requested
    ଯଦି (visual_id && *visual_id) {
        XVisualInfo *vi, template;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(visual_id, ଖାଲି, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        ଯଦି (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            ଫେରନ୍ତୁ true;
        }
    }

    depth = DefaultDepth(display, screen);
    ଯଦି ((X11_UseDirectColorVisuals() &&
         X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    ଯଦି (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    ଯଦି (vinfo->class == DirectColor || vinfo->class == TrueColor) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_mask;
        Gmask = vinfo->visual->green_mask;
        Bmask = vinfo->visual->blue_mask;
        ଯଦି (vinfo->depth == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } ଅନ୍ୟଥା {
            Amask = 0;
        }

        bpp = vinfo->depth;
        ଯଦି (bpp == 24) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, n;
            XPixmap_Format_ମୂଲ୍ୟଗୁଡ଼ିକ *p = X11_XListPixmapFormats(display, &n);
            ଯଦି (p) {
                ପାଇଁ (i = 0; i < n; ++i) {
                    ଯଦି (p[i].depth == 24) {
                        bpp = p[i].bits_per_pixel;
                        ଭାଙ୍ଗ;
                    }
                }
                X11_XFree(p);
            }
        }

        ଫେରନ୍ତୁ SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    ଯଦି (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        ବାଛ (vinfo->depth) {
        ସ୍ଥିତି 8:
            ଫେରନ୍ତୁ SDL_PIXELFORMAT_INDEX8;
        ସ୍ଥିତି 4:
            ଯଦି (BitmapBitOrder(display) == LSBFirst) {
                ଫେରନ୍ତୁ SDL_PIXELFORMAT_INDEX4LSB;
            } ଅନ୍ୟଥା {
                ଫେରନ୍ତୁ SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        ସ୍ଥିତି 1:
            ଯଦି (BitmapBitOrder(display) == LSBFirst) {
                ଫେରନ୍ତୁ SDL_PIXELFORMAT_INDEX1LSB;
            } ଅନ୍ୟଥା {
                ଫେରନ୍ତୁ SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    ଫେରନ୍ତୁ SDL_PIXELFORMAT_UNKNOWN;
}

ସ୍ଥିର SDL_DisplayID X11_AddGenericDisplay(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା default_screen = DefaultScreen(dpy);
    Screen *screen = ScreenOfDisplay(dpy, default_screen);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା scanline_pad, n, i;
    SDL_DisplayModeData *modedata;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    XPixmap_Format_ମୂଲ୍ୟଗୁଡ଼ିକ *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    ଯଦି (!get_visualinfo(dpy, default_screen, &vinfo)) {
        ଫେରନ୍ତୁ SDL_SetError("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ଯଦି (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        ଫେରନ୍ତୁ SDL_SetError("Palettized video modes are no longer supported");
    }

    SDL_zero(mode);
    mode.w = WidthOfScreen(screen);
    mode.h = HeightOfScreen(screen);
    mode.format = pixelformat;

    displaydata = (SDL_DisplayData *)SDL_calloc(1, ଆକାର(*displaydata));
    ଯଦି (!displaydata) {
        ଫେରନ୍ତୁ false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, ଆକାର(SDL_DisplayModeData));
    ଯଦି (!modedata) {
        SDL_free(displaydata);
        ଫେରନ୍ତୁ false;
    }
    mode.internal = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ଯଦି (pixmapformats) {
        ପାଇଁ (i = 0; i < n; ++i) {
            ଯଦି (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ଭାଙ୍ଗ;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (ଅକ୍ଷର *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_mode = mode;
    display.internal = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    ଫେରନ୍ତୁ SDL_AddVideoDisplay(&display, send_event);
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR

ସ୍ଥିର ଶୂନ୍ୟ X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(ଖାଲି);
    ଯଦି (displays) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ଅଚଳ SDL_DisplayData *displaydata = display->internal;
            ଯଦି (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

ସ୍ଥିର bool CheckXRandR(Display *display, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *major, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ifdef XRANDR_DISABLED_BY_DEFAULT
    ଯଦି (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#endif
        ଫେରନ୍ତୁ false;
    }
#ଅନ୍ୟଥା
    ଯଦି (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#endif
        ଫେରନ୍ତୁ false;
    }
#endif // XRANDR_DISABLED_BY_DEFAULT

    ଯଦି (!SDL_X11_HAVE_XRANDR) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#endif
        ଫେରନ୍ତୁ false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    ଯଦି (!X11_XRRQueryVersion(display, major, minor)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#endif
        *major = *minor = 0;
        ଫେରନ୍ତୁ false;
    }
#ifdef X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#endif
    ଫେରନ୍ତୁ true;
}

#define XRANDR_ROTATION_ବାମ  (1 << 1)
#define XRANDR_ROTATION_ଡାହାଣ (1 << 3)

ସ୍ଥିର ଶୂନ୍ୟ CalculateXRandRRefreshRate(ଅଚଳ XRRModeInfo *info, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *numerator, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *denominator)
{
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା vTotal = info->vTotal;

    ଯଦି (info->modeFlags & RR_DoubleScan) {
        // doublescan doubles the number of lines
        vTotal *= 2;
    }

    ଯଦି (info->modeFlags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        vTotal /= 2;
    }

    ଯଦି (info->hTotal && vTotal) {
        *numerator = info->dotClock;
        *denominator = (info->hTotal * vTotal);
    } ଅନ୍ୟଥା {
        *numerator = 0;
        *denominator = 0;
    }
}

ସ୍ଥିର bool SetXRandRModeInfo(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode modeID, SDL_DisplayMode *mode)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < res->nmode; ++i) {
        ଅଚଳ XRRModeInfo *info = &res->modes[i];
        ଯଦି (info->id == modeID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtcTransformAttributes *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            ଯଦି (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            ଯଦି (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            ଯଦି (rotation & (XRANDR_ROTATION_ବାମ | XRANDR_ROTATION_ଡାହାଣ)) {
                mode->w = (info->height * scale_w + 0xffff) >> 16;
                mode->h = (info->width * scale_h + 0xffff) >> 16;
            } ଅନ୍ୟଥା {
                mode->w = (info->width * scale_w + 0xffff) >> 16;
                mode->h = (info->height * scale_h + 0xffff) >> 16;
            }
            CalculateXRandRRefreshRate(info, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
            mode->internal->xrandr_mode = modeID;
#ifdef X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)modeID,
                    mode->screen_w, mode->screen_h, mode->refresh_rate_numerator, mode->refresh_rate_denominator);
#endif
            ଫେରନ୍ତୁ true;
        }
    }
    ଫେରନ୍ତୁ false;
}

ସ୍ଥିର bool Get_ମୂଳ_Window_Cardinal_Property(Display *dpy, ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen, ଅଚଳ ଅକ୍ଷର *name, Uint32 *ମୂଲ୍ୟ)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    ଯଦି (atom == None) {
        ଫେରନ୍ତୁ false;
    }

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା real_format;
    Atom real_type;
    unsigned long ବସ୍ତୁଗୁଡ଼ିକ_read = 0, ବସ୍ତୁଗୁଡ଼ିକ_ବାମ = 0;
    unsigned ଅକ୍ଷର *propdata = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା status;
    bool result = false;

    status = X11_XGetWindowProperty(dpy, ମୂଳ_Window(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &ବସ୍ତୁଗୁଡ଼ିକ_read, &ବସ୍ତୁଗୁଡ଼ିକ_ବାମ, &propdata);
    ଯଦି (status == Success && propdata) {
        ଯଦି (real_type == XA_CARDINAL && ବସ୍ତୁଗୁଡ଼ିକ_read > 0) {
            ବାଛ (real_format) {
            ସ୍ଥିତି 8:
                *ମୂଲ୍ୟ = propdata[0];
                ଭାଙ୍ଗ;
            ସ୍ଥିତି 16:
                *ମୂଲ୍ୟ = propdata[0] | (propdata[1] << 8);
                ଭାଙ୍ଗ;
            ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                *ମୂଲ୍ୟ = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                ଭାଙ୍ଗ;
            }
            result = true;
        }
        X11_XFree(propdata);
    }
    ଫେରନ୍ତୁ result;
}

ସ୍ଥିର bool Get_ମୂଳ_Window_Bool_Property(Display *dpy, ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen, ଅଚଳ ଅକ୍ଷର *name, bool *ମୂଲ୍ୟ)
{
    Uint32 v;
    ଯଦି (Get_ମୂଳ_Window_Cardinal_Property(dpy, screen, name, &v)) {
        *ମୂଲ୍ୟ = (v != 0);
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}

ସ୍ଥିର bool Get_ମୂଳ_Window_Float_Property(Display *dpy, ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen, ଅଚଳ ଅକ୍ଷର *name, ଦଶମିକ *ମୂଲ୍ୟ)
{
    Uint32 v;
    ଯଦି (Get_ମୂଳ_Window_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(ମୂଲ୍ୟ, &v, ଆକାର(v));
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}

ସ୍ଥିର bool IsSteamDeckOLEDDisplay(ଅଚଳ MonitorInfo *info)
{
    ଯଦି (SDL_strcmp(info->manufacturer_code, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        ଯଦି (info->product_code == 0x3003 || info->product_code == 0x3004) {
            ଫେରନ୍ତୁ true;
        }
    }
    ଫେରନ୍ତୁ false;
}

ସ୍ଥିର ଦଶମିକ GetGamescopeSDRWhiteLevel(Display *dpy, ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen, ଅଚଳ MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    ଯଦି (!dpy) {
        ଫେରନ୍ତୁ 0.0f;
    }

    ଦଶମିକ SDR_white_level = 0.0f;
    bool external_display = false;
    ଯଦି (Get_ମୂଳ_Window_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_ମୂଳ_Window_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } ଅନ୍ୟଥା ଯଦି (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (ଦଶମିକ)info->max_luminance / 3.0f;
    } ଅନ୍ୟଥା {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    ଫେରନ୍ତୁ SDR_white_level;
}

ସ୍ଥିର MonitorInfo *GetMonitorInfo(Display *dpy, ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା real_format;
    Atom real_type;
    unsigned long ବସ୍ତୁଗୁଡ଼ିକ_read = 0, ବସ୍ତୁଗୁଡ଼ିକ_ବାମ = 0;
    unsigned ଅକ୍ଷର *propdata = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା status;

    *gamescope = false;

    ଯଦି (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_PATH = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        ଯଦି (GAMESCOPE_DISPLAY_EDID_PATH != None) {
            status = X11_XGetWindowProperty(dpy, ମୂଳ_Window(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_PATH, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &ବସ୍ତୁଗୁଡ଼ିକ_read, &ବସ୍ତୁଗୁଡ଼ିକ_ବାମ, &propdata);
            ଯଦି (status == Success && propdata) {
                size_t size = 0;
                ଶୂନ୍ୟ *data = SDL_LoadFile((ଅକ୍ଷର *)propdata, &size);
                ଯଦି (data) {
                    info = decode_edid((uchar *)data, size);
                    ଯଦି (info) {
                        *gamescope = true;
                    }
                    SDL_free(data);
                }
            }
            ଯଦି (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    ଯଦି (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        ଯଦି (EDID != None) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nprop; ++i) {
                ଯଦି (props[i] == EDID) {
                    status = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &ବସ୍ତୁଗୁଡ଼ିକ_read, &ବସ୍ତୁଗୁଡ଼ିକ_ବାମ, &propdata);
                    ଯଦି (status == Success && propdata) {
                        info = decode_edid(propdata, ବସ୍ତୁଗୁଡ଼ିକ_read);
                    }
                    ଯଦି (propdata) {
                        X11_XFree(propdata);
                    }
                    ଭାଙ୍ଗ;
                }
            }

            ଯଦି (props) {
                X11_XFree(props);
            }
        }
    }

#ifdef X11MODES_DEBUG
    ଯଦି (info) {
        dump_monitor_info(info);
    }
#endif
    ଫେରନ୍ତୁ info;
}

ସ୍ଥିର ଶୂନ୍ୟ SetXRandRDisplayName(MonitorInfo *info, ଅକ୍ଷର *name, size_t namelen, unsigned long widthmm, unsigned long heightmm)
{
    ଯଦି (info) {
        SDL_strlcpy(name, info->dsc_product_name, namelen);
    }

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା inches = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    ଯଦି (*name && inches) {
        ଅଚଳ size_t len = SDL_strlen(name);
        (ଶୂନ୍ୟ)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ifdef X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#endif
}

ସ୍ଥିର bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, ଅକ୍ଷର *display_name, size_t display_name_size)
{
    XRROutputInfo *output_info;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା display_x, display_y;
    unsigned long display_mm_width, display_mm_height;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    SDL_DisplayModeData *modedata;
    RRMode modeID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_ମୂଲ୍ୟଗୁଡ଼ିକ *pixmapformats;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା scanline_pad;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, n;

    ଯଦି (!display || !display_name) {
        ଫେରନ୍ତୁ false; // invalid parameters
    }

    ଯଦି (!get_visualinfo(dpy, screen, &vinfo)) {
        ଫେରନ୍ତୁ false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ଯଦି (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        ଫେରନ୍ତୁ false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ଯଦି (pixmapformats) {
        ପାଇଁ (i = 0; i < n; i++) {
            ଯଦି (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ଭାଙ୍ଗ;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    ଯଦି (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        ଫେରନ୍ତୁ false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_size);
    display_mm_width = output_info->mm_width;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    ଯଦି (!crtc) {
        ଫେରନ୍ତୁ false; // oh well, ignore it.
    }

    SDL_zero(mode);
    modeID = crtc->mode;
    mode.w = crtc->width;
    mode.h = crtc->height;
    mode.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_DisplayData *)SDL_calloc(1, ଆକାର(*displaydata));
    ଯଦି (!displaydata) {
        ଫେରନ୍ତୁ false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, ଆକାର(SDL_DisplayModeData));
    ଯଦି (!modedata) {
        SDL_free(displaydata);
        ଫେରନ୍ତୁ false;
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
    SDL_strlcpy(displaydata->connector_name, display_name, ଆକାର(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    SetXRandRModeInfo(dpy, res, output_crtc, modeID, &mode);
    SetXRandRDisplayName(info, display_name, display_name_size, display_mm_width, display_mm_height);

    SDL_zero(*display);
    ଯଦି (*display_name) {
        display->name = display_name;
    }
    display->desktop_mode = mode;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->internal = displaydata;

    ଯଦି (info) {
        ଦଶମିକ SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        ଯଦି (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } ଅନ୍ୟଥା {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ifdef X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#endif
        ଯଦି (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (ଦଶମିକ)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool X11_AddXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    ଅକ୍ଷର display_name[128];

    ଯଦି (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, ଆକାର(display_name))) {
        ଫେରନ୍ତୁ true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    ଯଦି (displayID == 0) {
        ଫେରନ୍ତୁ false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    ଯଦି (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    ଫେରନ୍ତୁ true;
}


ସ୍ଥିର bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    ଅକ୍ଷର display_name[128];

    ଯଦି (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, ଆକାର(display_name))) {
        ଫେରନ୍ତୁ false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_SetDesktopDisplayMode(existing_display, &display.desktop_mode);

    // update bounds
    ଯଦି (existing_display->internal->x != display.internal->x ||
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

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର XRRScreenResources *X11_GetScreenResources(Display *dpy, ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, ମୂଳ_Window(dpy, screen));
    ଯଦି (!res || res->noutput == 0) {
        ଯଦି (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, ମୂଳ_Window(dpy, screen));
    }
    ଫେରନ୍ତୁ res;
}

ଶୂନ୍ୟ X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା screencount = Screen_ଗଣନା(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(ଖାଲି);
    ଯଦି (!displays) {
        ଫେରନ୍ତୁ;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ଯଦି (!res) {
            ଜାରି;
        }

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ଅଚଳ SDL_DisplayData *displaydata = display->internal;
            ଯଦି (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

ସ୍ଥିର ଶୂନ୍ୟ X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା screencount = Screen_ଗଣନା(dpy);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&ଅଙ୍କ_displays);
    ଯଦି (!displays) {
        ଫେରନ୍ତୁ;
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ଯଦି (!res) {
            ଜାରି;
        }

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା output = 0; output < res->noutput; output++) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ_displays; ++i) {
                ଯଦି (!displays[i]) {
                    // We already removed this display from the list
                    ଜାରି;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                ଅଚଳ SDL_DisplayData *displaydata = display->internal;
                ଯଦି (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    ଭାଙ୍ଗ;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ_displays; ++i) {
        ଯଦି (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ଅଚଳ SDL_DisplayData *displaydata = display->internal;
            ଯଦି (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

ସ୍ଥିର ଶୂନ୍ୟ X11_HandleXRandROutputChange(SDL_VideoDevice *_this, ଅଚଳ XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

#ଯଦି 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) ev->output, (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) ev->crtc, (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) ev->mode, (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) ev->rotation, (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) ev->connection);
#endif

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(ଖାଲି);
    ଯଦି (displays) {
        ପାଇଁ (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            ଅଚଳ SDL_DisplayData *displaydata = thisdisplay->internal;
            ଯଦି (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                ଭାଙ୍ଗ;
            }
        }
        SDL_free(displays);
    }

    ଯଦି (ev->connection == RR_Disconnected) { // output is going away
        ଯଦି (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            ଯଦି (_this->ଅଙ୍କ_displays == 1) {
                generic_display = X11_AddGenericDisplay(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            ଯଦି (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } ଅନ୍ୟଥା ଯଦି (ev->connection == RR_Connected) { // output is coming online
        ଯଦି (!display) {
            Display *dpy = ev->display;
            ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ଯଦି (res) {
                X11_AddXRandRDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

ଶୂନ୍ୟ X11_HandleXRandREvent(SDL_VideoDevice *_this, ଅଚଳ XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_assert(xevent->type == (videodata->xrandr_event_base + RRNotify));

    ବାଛ (((ଅଚଳ XRRNotifyEvent *)xevent)->subtype) {
    ସ୍ଥିତି RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (ଅଚଳ XRROutputChangeNotifyEvent *)xevent);
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ X11_SortOutputsByPriorityHint(SDL_VideoDevice *_this)
{
    ଅଚଳ ଅକ୍ଷର *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    ଯଦି (name_hint) {
        ଅକ୍ଷର *saveptr;
        ଅକ୍ଷର *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(ଆକାର(SDL_VideoDisplay *) * _this->ଅଙ୍କ_displays);

        ଯଦି (str && sorted_list) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା sorted_index = 0;

            // Sort the requested displays to the front of the list.
            ଅଚଳ ଅକ୍ଷର *token = SDL_strtok_r(str, ",", &saveptr);
            ଯେତେବେଳେ (token) {
                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    ଯଦି (d) {
                        SDL_DisplayData *data = d->internal;
                        ଯଦି (SDL_strcmp(token, data->connector_name) == 0) {
                            sorted_list[sorted_index++] = d;
                            _this->displays[i] = ଖାଲି;
                            ଭାଙ୍ଗ;
                        }
                    }
                }

                token = SDL_strtok_r(ଖାଲି, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < _this->ଅଙ୍କ_displays; ++i) {
                ଯଦି (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, ଆକାର(SDL_VideoDisplay *) * _this->ଅଙ୍କ_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ସ୍ଥିର bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା screencount = Screen_ଗଣନା(dpy);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, ମୂଳ_Window(dpy, default_screen));
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା xrandr_error_base = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା looking_for_primary;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା output;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା screen;

    ଯଦି (!X11_XRRQueryExtension(dpy, &data->xrandr_event_base, &xrandr_error_base)) {
        ଫେରନ୍ତୁ SDL_SetError("XRRQueryExtension failed");
    }

    ପାଇଁ (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        ପାଇଁ (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            ଯଦି (looking_for_primary && (screen != default_screen)) {
                ଜାରି;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ଯଦି (!res) {
                ଜାରି;
            }

            ପାଇଁ (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                ଯଦି ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    ଜାରି;
                }
                ଯଦି (!X11_AddXRandRDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    ଭାଙ୍ଗ;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_ନିବେଶ(dpy, ମୂଳ_Window(dpy, screen), RROutputChangeNotifyMask);
        }
    }

    ଯଦି (_this->ଅଙ୍କ_displays == 0) {
        ଫେରନ୍ତୁ SDL_SetError("No available displays");
    }

    X11_SortOutputsByPriorityHint(_this);

    ଫେରନ୍ତୁ true;
}
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
ସ୍ଥିର bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    ଯଦି (X11_AddGenericDisplay(_this, true) == 0) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_VideoData *data = _this->internal;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        ଯଦି (CheckXRandR(data->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            ଫେରନ୍ତୁ true;
        }
    }
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    ଫେରନ୍ତୁ X11_InitModes_StdXlib(_this);
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

    ଯଦି (data->use_xrandr) {
        Display *display = _this->internal->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, ମୂଳ_Window(display, data->screen));
        ଯଦି (res) {
            SDL_DisplayModeData *modedata;
            XRROutputInfo *output_info;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

            output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
            ଯଦି (output_info && output_info->connection != RR_Disconnected) {
                ପାଇଁ (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_DisplayModeData *)SDL_calloc(1, ଆକାର(SDL_DisplayModeData));
                    ଯଦି (!modedata) {
                        ଜାରି;
                    }
                    mode.internal = modedata;

                    ଯଦି (!SetXRandRModeInfo(display, res, output_info->crtc, output_info->modes[i], &mode) ||
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
    ଫେରନ୍ତୁ true;
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*PreXRRSetScreenSizeErrorHandler)(Display *, XErrorEvent *) = ଖାଲି;
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDL_XRRSetScreenSizeErrHandler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    ଯଦି ((e->error_code == BadMatch) || (e->error_code == Bad_ମୂଲ୍ୟ)) {
        ଫେରନ୍ତୁ 0;
    }

    ଫେରନ୍ତୁ PreXRRSetScreenSizeErrorHandler(d, e);
}
#endif

bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *data = sdl_display->internal;

    viddata->last_mode_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    ଯଦି (!viddata->is_xwayland) {
        ଯଦି (sdl_display->current_mode != mode) {
            data->mode_switch_deadline_ns = SDL_GetTicksNS() + MODE_SWITCH_TIMEOUT_NS;
        } ଅନ୍ୟଥା {
            data->mode_switch_deadline_ns = 0;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    ଯଦି (data->use_xrandr) {
        Display *display = viddata->display;
        SDL_DisplayModeData *modedata = mode->internal;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା mm_width, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        Status status;

        res = X11_XRRGetScreenResources(display, ମୂଳ_Window(display, data->screen));
        ଯଦି (!res) {
            ଫେରନ୍ତୁ SDL_SetError("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
        ଯଦି (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            ଫେରନ୍ତୁ SDL_SetError("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        ଯଦି (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            ଫେରନ୍ତୁ SDL_SetError("Couldn't get XRandR crtc info");
        }

        ଯଦି (crtc->mode == modedata->xrandr_mode) {
#ifdef X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->mode, crtc->width, crtc->height);
#endif
            status = Success;
            ଯାଅ freeInfo;
        }

        X11_XGrabServer(display);
        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, ଖାଲି, 0);
        ଯଦି (status != Success) {
            ଯାଅ ungrabServer;
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
        X11_XRRSetScreenSize(display, ମୂଳ_Window(display, data->screen),
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

        ଯଦି (status != Success) {
            ଫେରନ୍ତୁ SDL_SetError("X11_XRRSetCrtcConfig failed");
        }
    }
#ଅନ୍ୟଥା
    (ଶୂନ୍ୟ)data;
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_DisplayData *data = sdl_display->internal;

    rect->x = data->x;
    rect->y = data->y;
    rect->w = sdl_display->current_mode->w;
    rect->h = sdl_display->current_mode->h;
    ଫେରନ୍ତୁ true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    Atom _NET_WORKAREA;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା real_format;
    Atom real_type;
    unsigned long ବସ୍ତୁଗୁଡ଼ିକ_read = 0, ବସ୍ତୁଗୁଡ଼ିକ_ବାମ = 0;
    unsigned ଅକ୍ଷର *propdata = ଖାଲି;
    bool result = false;

    ଯଦି (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        ଫେରନ୍ତୁ false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା status = X11_XGetWindowProperty(display, Default_ମୂଳ_Window(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &ବସ୍ତୁଗୁଡ଼ିକ_read,
                                    &ବସ୍ତୁଗୁଡ଼ିକ_ବାମ, &propdata);
    ଯଦି ((status == Success) && (ବସ୍ତୁଗୁଡ଼ିକ_read >= 4)) {
        ଅଚଳ long *p = (long *)propdata;
        ଅଚଳ SDL_Rect usable = { (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)p[0], (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)p[1], (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)p[2], (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)p[3] };
        result = true;
        ଯଦି (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    ଯଦି (propdata) {
        X11_XFree(propdata);
    }

    ଫେରନ୍ତୁ result;
}

#endif // SDL_VIDEO_DRIVER_X11
