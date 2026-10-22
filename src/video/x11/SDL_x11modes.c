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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#অন্তর্ভাৱ "SDL_x11video.h"
#অন্তর্ভাৱ "SDL_x11settings.h"
#অন্তর্ভাৱ "edid.h"
#অন্তর্ভাৱ "../../events/SDL_displayevents_c.h"
#অন্তর্ভাৱ "../SDL_pixels_c.h"

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

ভিন্ন X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    দ্ৱিগুণ scale_factor = 0.0;

    // First use the forced scaling factor specified by the app/user
    ধ্রুৱ ৱর্ণ *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_FACTOR);
    যদি (hint && *hint) {
        দ্ৱিগুণ মান = SDL_atof(hint);
        যদি (মান >= 1.0f && মান <= 10.0f) {
            scale_factor = মান;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    যদি (scale_factor <= 0.0) {
        পূর্ণাঙ্ক status, real_format;
        Atom real_type;
        Atom res_mgr;
        unsigned long বস্তুসমূহ_read, বস্তুসমূহ_বাম;
        ৱর্ণ *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        status = X11_XGetWindowProperty(display, মূল_Window(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &বস্তুসমূহ_read, &বস্তুসমূহ_বাম,
                                        (unsigned ৱর্ণ **)&resource_manager);

        যদি (status == Success && resource_manager) {
            owns_resource_manager = true;
        } অন্যথা {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        যদি (resource_manager) {
            XrmDatabase db;
            Xrm_মান মান;
            ৱর্ণ *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            যদি (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &মান)) {
                যদি (মান.addr && type && SDL_strcmp(type, "String") == 0) {
                    পূর্ণাঙ্ক dpi = SDL_atoi(মান.addr);
                    scale_factor  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            যদি (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    যদি (scale_factor <= 0.0) {
        scale_factor = X11_Get_Xsettings_Client_Int_চাবি(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        যদি (scale_factor <= 0.0) {
            পূর্ণাঙ্ক dpi = X11_Get_Xsettings_Client_Int_চাবি(client, "Xft/DPI", -1);
            যদি (dpi > 0) {
                scale_factor = (দ্ৱিগুণ) dpi / 1024.0;
                scale_factor /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    যদি (scale_factor <= 0.0) {
        ধ্রুৱ ৱর্ণ *scale_str = SDL_getenv("GDK_SCALE");
        যদি (scale_str) {
            scale_factor = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    যদি (scale_factor <= 0.0) {
        scale_factor = 1.0;
    }

    ঘূৰাই (ভিন্ন)scale_factor;
}

ভিন্ন X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    ঘূৰাই X11_GetGlobalContentScale(_this->internal->display, _this->internal->xsettings_data.xsettings);
}

স্থির bool get_visualinfo(Display *display, পূর্ণাঙ্ক screen, XVisualInfo *vinfo)
{
    ধ্রুৱ ৱর্ণ *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    পূর্ণাঙ্ক depth;

    // Look for an exact visual, if requested
    যদি (visual_id && *visual_id) {
        XVisualInfo *vi, template;
        পূর্ণাঙ্ক nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(visual_id, রিক্ত, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        যদি (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            ঘূৰাই true;
        }
    }

    depth = DefaultDepth(display, screen);
    যদি ((X11_UseDirectColorVisuals() &&
         X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
        ঘূৰাই true;
    }
    ঘূৰাই false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    পূর্ণাঙ্ক nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    যদি (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        ঘূৰাই true;
    }
    ঘূৰাই false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    যদি (vinfo->class == DirectColor || vinfo->class == TrueColor) {
        পূর্ণাঙ্ক bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_mask;
        Gmask = vinfo->visual->green_mask;
        Bmask = vinfo->visual->blue_mask;
        যদি (vinfo->depth == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } অন্যথা {
            Amask = 0;
        }

        bpp = vinfo->depth;
        যদি (bpp == 24) {
            পূর্ণাঙ্ক i, n;
            XPixmap_Format_মানসমূহ *p = X11_XListPixmapFormats(display, &n);
            যদি (p) {
                বাবে (i = 0; i < n; ++i) {
                    যদি (p[i].depth == 24) {
                        bpp = p[i].bits_per_pixel;
                        ভঙ্গ;
                    }
                }
                X11_XFree(p);
            }
        }

        ঘূৰাই SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    যদি (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        ৱিকল্প (vinfo->depth) {
        পক্ষ 8:
            ঘূৰাই SDL_PIXELFORMAT_INDEX8;
        পক্ষ 4:
            যদি (BitmapBitOrder(display) == LSBFirst) {
                ঘূৰাই SDL_PIXELFORMAT_INDEX4LSB;
            } অন্যথা {
                ঘূৰাই SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        পক্ষ 1:
            যদি (BitmapBitOrder(display) == LSBFirst) {
                ঘূৰাই SDL_PIXELFORMAT_INDEX1LSB;
            } অন্যথা {
                ঘূৰাই SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    ঘূৰাই SDL_PIXELFORMAT_UNKNOWN;
}

স্থির SDL_DisplayID X11_AddGenericDisplay(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    ধ্রুৱ পূর্ণাঙ্ক default_screen = DefaultScreen(dpy);
    Screen *screen = ScreenOfDisplay(dpy, default_screen);
    পূর্ণাঙ্ক scanline_pad, n, i;
    SDL_DisplayModeData *modedata;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    XPixmap_Format_মানসমূহ *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    যদি (!get_visualinfo(dpy, default_screen, &vinfo)) {
        ঘূৰাই SDL_SetError("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    যদি (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        ঘূৰাই SDL_SetError("Palettized video modes are no longer supported");
    }

    SDL_zero(mode);
    mode.w = WidthOfScreen(screen);
    mode.h = HeightOfScreen(screen);
    mode.format = pixelformat;

    displaydata = (SDL_DisplayData *)SDL_calloc(1, পরিমাণ(*displaydata));
    যদি (!displaydata) {
        ঘূৰাই false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, পরিমাণ(SDL_DisplayModeData));
    যদি (!modedata) {
        SDL_free(displaydata);
        ঘূৰাই false;
    }
    mode.internal = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    যদি (pixmapformats) {
        বাবে (i = 0; i < n; ++i) {
            যদি (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ভঙ্গ;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (ৱর্ণ *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_mode = mode;
    display.internal = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    ঘূৰাই SDL_AddVideoDisplay(&display, send_event);
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR

স্থির শূন্য X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(রিক্ত);
    যদি (displays) {
        বাবে (পূর্ণাঙ্ক i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ধ্রুৱ SDL_DisplayData *displaydata = display->internal;
            যদি (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

স্থির bool CheckXRandR(Display *display, পূর্ণাঙ্ক *major, পূর্ণাঙ্ক *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ifdef XRANDR_DISABLED_BY_DEFAULT
    যদি (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#endif
        ঘূৰাই false;
    }
#অন্যথা
    যদি (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#endif
        ঘূৰাই false;
    }
#endif // XRANDR_DISABLED_BY_DEFAULT

    যদি (!SDL_X11_HAVE_XRANDR) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#endif
        ঘূৰাই false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    যদি (!X11_XRRQueryVersion(display, major, minor)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#endif
        *major = *minor = 0;
        ঘূৰাই false;
    }
#ifdef X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#endif
    ঘূৰাই true;
}

#define XRANDR_ROTATION_বাম  (1 << 1)
#define XRANDR_ROTATION_ডান (1 << 3)

স্থির শূন্য CalculateXRandRRefreshRate(ধ্রুৱ XRRModeInfo *info, পূর্ণাঙ্ক *numerator, পূর্ণাঙ্ক *denominator)
{
    unsigned পূর্ণাঙ্ক vTotal = info->vTotal;

    যদি (info->modeFlags & RR_DoubleScan) {
        // doublescan doubles the number of lines
        vTotal *= 2;
    }

    যদি (info->modeFlags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        vTotal /= 2;
    }

    যদি (info->hTotal && vTotal) {
        *numerator = info->dotClock;
        *denominator = (info->hTotal * vTotal);
    } অন্যথা {
        *numerator = 0;
        *denominator = 0;
    }
}

স্থির bool SetXRandRModeInfo(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode modeID, SDL_DisplayMode *mode)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < res->nmode; ++i) {
        ধ্রুৱ XRRModeInfo *info = &res->modes[i];
        যদি (info->id == modeID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtcTransformAttributes *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            যদি (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            যদি (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            যদি (rotation & (XRANDR_ROTATION_বাম | XRANDR_ROTATION_ডান)) {
                mode->w = (info->height * scale_w + 0xffff) >> 16;
                mode->h = (info->width * scale_h + 0xffff) >> 16;
            } অন্যথা {
                mode->w = (info->width * scale_w + 0xffff) >> 16;
                mode->h = (info->height * scale_h + 0xffff) >> 16;
            }
            CalculateXRandRRefreshRate(info, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
            mode->internal->xrandr_mode = modeID;
#ifdef X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (পূর্ণাঙ্ক)modeID,
                    mode->screen_w, mode->screen_h, mode->refresh_rate_numerator, mode->refresh_rate_denominator);
#endif
            ঘূৰাই true;
        }
    }
    ঘূৰাই false;
}

স্থির bool Get_মূল_Window_Cardinal_Property(Display *dpy, পূর্ণাঙ্ক screen, ধ্রুৱ ৱর্ণ *name, Uint32 *মান)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    যদি (atom == None) {
        ঘূৰাই false;
    }

    পূর্ণাঙ্ক real_format;
    Atom real_type;
    unsigned long বস্তুসমূহ_read = 0, বস্তুসমূহ_বাম = 0;
    unsigned ৱর্ণ *propdata = রিক্ত;
    পূর্ণাঙ্ক status;
    bool result = false;

    status = X11_XGetWindowProperty(dpy, মূল_Window(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &বস্তুসমূহ_read, &বস্তুসমূহ_বাম, &propdata);
    যদি (status == Success && propdata) {
        যদি (real_type == XA_CARDINAL && বস্তুসমূহ_read > 0) {
            ৱিকল্প (real_format) {
            পক্ষ 8:
                *মান = propdata[0];
                ভঙ্গ;
            পক্ষ 16:
                *মান = propdata[0] | (propdata[1] << 8);
                ভঙ্গ;
            স্ৱভাৱ:
                *মান = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                ভঙ্গ;
            }
            result = true;
        }
        X11_XFree(propdata);
    }
    ঘূৰাই result;
}

স্থির bool Get_মূল_Window_Bool_Property(Display *dpy, পূর্ণাঙ্ক screen, ধ্রুৱ ৱর্ণ *name, bool *মান)
{
    Uint32 v;
    যদি (Get_মূল_Window_Cardinal_Property(dpy, screen, name, &v)) {
        *মান = (v != 0);
        ঘূৰাই true;
    }
    ঘূৰাই false;
}

স্থির bool Get_মূল_Window_Float_Property(Display *dpy, পূর্ণাঙ্ক screen, ধ্রুৱ ৱর্ণ *name, ভিন্ন *মান)
{
    Uint32 v;
    যদি (Get_মূল_Window_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(মান, &v, পরিমাণ(v));
        ঘূৰাই true;
    }
    ঘূৰাই false;
}

স্থির bool IsSteamDeckOLEDDisplay(ধ্রুৱ MonitorInfo *info)
{
    যদি (SDL_strcmp(info->manufacturer_code, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        যদি (info->product_code == 0x3003 || info->product_code == 0x3004) {
            ঘূৰাই true;
        }
    }
    ঘূৰাই false;
}

স্থির ভিন্ন GetGamescopeSDRWhiteLevel(Display *dpy, পূর্ণাঙ্ক screen, ধ্রুৱ MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    যদি (!dpy) {
        ঘূৰাই 0.0f;
    }

    ভিন্ন SDR_white_level = 0.0f;
    bool external_display = false;
    যদি (Get_মূল_Window_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_মূল_Window_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } অন্যথা যদি (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (ভিন্ন)info->max_luminance / 3.0f;
    } অন্যথা {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    ঘূৰাই SDR_white_level;
}

স্থির MonitorInfo *GetMonitorInfo(Display *dpy, পূর্ণাঙ্ক screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = রিক্ত;
    পূর্ণাঙ্ক real_format;
    Atom real_type;
    unsigned long বস্তুসমূহ_read = 0, বস্তুসমূহ_বাম = 0;
    unsigned ৱর্ণ *propdata = রিক্ত;
    পূর্ণাঙ্ক status;

    *gamescope = false;

    যদি (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_PATH = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        যদি (GAMESCOPE_DISPLAY_EDID_PATH != None) {
            status = X11_XGetWindowProperty(dpy, মূল_Window(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_PATH, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &বস্তুসমূহ_read, &বস্তুসমূহ_বাম, &propdata);
            যদি (status == Success && propdata) {
                size_t size = 0;
                শূন্য *data = SDL_LoadFile((ৱর্ণ *)propdata, &size);
                যদি (data) {
                    info = decode_edid((uchar *)data, size);
                    যদি (info) {
                        *gamescope = true;
                    }
                    SDL_free(data);
                }
            }
            যদি (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    যদি (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        যদি (EDID != None) {
            পূর্ণাঙ্ক nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            বাবে (পূর্ণাঙ্ক i = 0; i < nprop; ++i) {
                যদি (props[i] == EDID) {
                    status = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &বস্তুসমূহ_read, &বস্তুসমূহ_বাম, &propdata);
                    যদি (status == Success && propdata) {
                        info = decode_edid(propdata, বস্তুসমূহ_read);
                    }
                    যদি (propdata) {
                        X11_XFree(propdata);
                    }
                    ভঙ্গ;
                }
            }

            যদি (props) {
                X11_XFree(props);
            }
        }
    }

#ifdef X11MODES_DEBUG
    যদি (info) {
        dump_monitor_info(info);
    }
#endif
    ঘূৰাই info;
}

স্থির শূন্য SetXRandRDisplayName(MonitorInfo *info, ৱর্ণ *name, size_t namelen, unsigned long widthmm, unsigned long heightmm)
{
    যদি (info) {
        SDL_strlcpy(name, info->dsc_product_name, namelen);
    }

    পূর্ণাঙ্ক inches = (পূর্ণাঙ্ক)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    যদি (*name && inches) {
        ধ্রুৱ size_t len = SDL_strlen(name);
        (শূন্য)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ifdef X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#endif
}

স্থির bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, পূর্ণাঙ্ক screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, ৱর্ণ *display_name, size_t display_name_size)
{
    XRROutputInfo *output_info;
    পূর্ণাঙ্ক display_x, display_y;
    unsigned long display_mm_width, display_mm_height;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    SDL_DisplayModeData *modedata;
    RRMode modeID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_মানসমূহ *pixmapformats;
    পূর্ণাঙ্ক scanline_pad;
    পূর্ণাঙ্ক i, n;

    যদি (!display || !display_name) {
        ঘূৰাই false; // invalid parameters
    }

    যদি (!get_visualinfo(dpy, screen, &vinfo)) {
        ঘূৰাই false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    যদি (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        ঘূৰাই false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    যদি (pixmapformats) {
        বাবে (i = 0; i < n; i++) {
            যদি (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ভঙ্গ;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    যদি (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        ঘূৰাই false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_size);
    display_mm_width = output_info->mm_width;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    যদি (!crtc) {
        ঘূৰাই false; // oh well, ignore it.
    }

    SDL_zero(mode);
    modeID = crtc->mode;
    mode.w = crtc->width;
    mode.h = crtc->height;
    mode.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_DisplayData *)SDL_calloc(1, পরিমাণ(*displaydata));
    যদি (!displaydata) {
        ঘূৰাই false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, পরিমাণ(SDL_DisplayModeData));
    যদি (!modedata) {
        SDL_free(displaydata);
        ঘূৰাই false;
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
    SDL_strlcpy(displaydata->connector_name, display_name, পরিমাণ(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    SetXRandRModeInfo(dpy, res, output_crtc, modeID, &mode);
    SetXRandRDisplayName(info, display_name, display_name_size, display_mm_width, display_mm_height);

    SDL_zero(*display);
    যদি (*display_name) {
        display->name = display_name;
    }
    display->desktop_mode = mode;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->internal = displaydata;

    যদি (info) {
        ভিন্ন SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        যদি (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } অন্যথা {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ifdef X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#endif
        যদি (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (ভিন্ন)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    ঘূৰাই true;
}

স্থির bool X11_AddXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, পূর্ণাঙ্ক screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    ৱর্ণ display_name[128];

    যদি (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, পরিমাণ(display_name))) {
        ঘূৰাই true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    যদি (displayID == 0) {
        ঘূৰাই false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    যদি (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    ঘূৰাই true;
}


স্থির bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, পূর্ণাঙ্ক screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    ৱর্ণ display_name[128];

    যদি (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, পরিমাণ(display_name))) {
        ঘূৰাই false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_SetDesktopDisplayMode(existing_display, &display.desktop_mode);

    // update bounds
    যদি (existing_display->internal->x != display.internal->x ||
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

    ঘূৰাই true;
}

স্থির XRRScreenResources *X11_GetScreenResources(Display *dpy, পূর্ণাঙ্ক screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, মূল_Window(dpy, screen));
    যদি (!res || res->noutput == 0) {
        যদি (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, মূল_Window(dpy, screen));
    }
    ঘূৰাই res;
}

শূন্য X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    ধ্রুৱ পূর্ণাঙ্ক screencount = Screen_গুনতি(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(রিক্ত);
    যদি (!displays) {
        ঘূৰাই;
    }

    বাবে (পূর্ণাঙ্ক screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        যদি (!res) {
            অনুৱর্ত;
        }

        বাবে (পূর্ণাঙ্ক i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ধ্রুৱ SDL_DisplayData *displaydata = display->internal;
            যদি (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

স্থির শূন্য X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    ধ্রুৱ পূর্ণাঙ্ক screencount = Screen_গুনতি(dpy);
    পূর্ণাঙ্ক অঙ্ক_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&অঙ্ক_displays);
    যদি (!displays) {
        ঘূৰাই;
    }

    বাবে (পূর্ণাঙ্ক screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        যদি (!res) {
            অনুৱর্ত;
        }

        বাবে (পূর্ণাঙ্ক output = 0; output < res->noutput; output++) {
            বাবে (পূর্ণাঙ্ক i = 0; i < অঙ্ক_displays; ++i) {
                যদি (!displays[i]) {
                    // We already removed this display from the list
                    অনুৱর্ত;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                ধ্রুৱ SDL_DisplayData *displaydata = display->internal;
                যদি (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    ভঙ্গ;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    বাবে (পূর্ণাঙ্ক i = 0; i < অঙ্ক_displays; ++i) {
        যদি (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ধ্রুৱ SDL_DisplayData *displaydata = display->internal;
            যদি (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

স্থির শূন্য X11_HandleXRandROutputChange(SDL_VideoDevice *_this, ধ্রুৱ XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = রিক্ত;
    পূর্ণাঙ্ক i;

#যদি 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (unsigned পূর্ণাঙ্ক) ev->output, (unsigned পূর্ণাঙ্ক) ev->crtc, (unsigned পূর্ণাঙ্ক) ev->mode, (unsigned পূর্ণাঙ্ক) ev->rotation, (unsigned পূর্ণাঙ্ক) ev->connection);
#endif

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(রিক্ত);
    যদি (displays) {
        বাবে (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            ধ্রুৱ SDL_DisplayData *displaydata = thisdisplay->internal;
            যদি (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                ভঙ্গ;
            }
        }
        SDL_free(displays);
    }

    যদি (ev->connection == RR_Disconnected) { // output is going away
        যদি (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            যদি (_this->অঙ্ক_displays == 1) {
                generic_display = X11_AddGenericDisplay(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            যদি (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } অন্যথা যদি (ev->connection == RR_Connected) { // output is coming online
        যদি (!display) {
            Display *dpy = ev->display;
            ধ্রুৱ পূর্ণাঙ্ক screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            যদি (res) {
                X11_AddXRandRDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

শূন্য X11_HandleXRandREvent(SDL_VideoDevice *_this, ধ্রুৱ XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_assert(xevent->type == (videodata->xrandr_event_base + RRNotify));

    ৱিকল্প (((ধ্রুৱ XRRNotifyEvent *)xevent)->subtype) {
    পক্ষ RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (ধ্রুৱ XRROutputChangeNotifyEvent *)xevent);
        ভঙ্গ;
    স্ৱভাৱ:
        ভঙ্গ;
    }
}

স্থির শূন্য X11_SortOutputsByPriorityHint(SDL_VideoDevice *_this)
{
    ধ্রুৱ ৱর্ণ *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    যদি (name_hint) {
        ৱর্ণ *saveptr;
        ৱর্ণ *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(পরিমাণ(SDL_VideoDisplay *) * _this->অঙ্ক_displays);

        যদি (str && sorted_list) {
            পূর্ণাঙ্ক sorted_index = 0;

            // Sort the requested displays to the front of the list.
            ধ্রুৱ ৱর্ণ *token = SDL_strtok_r(str, ",", &saveptr);
            যেতিয়ালৈ (token) {
                বাবে (পূর্ণাঙ্ক i = 0; i < _this->অঙ্ক_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    যদি (d) {
                        SDL_DisplayData *data = d->internal;
                        যদি (SDL_strcmp(token, data->connector_name) == 0) {
                            sorted_list[sorted_index++] = d;
                            _this->displays[i] = রিক্ত;
                            ভঙ্গ;
                        }
                    }
                }

                token = SDL_strtok_r(রিক্ত, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            বাবে (পূর্ণাঙ্ক i = 0; i < _this->অঙ্ক_displays; ++i) {
                যদি (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, পরিমাণ(SDL_VideoDisplay *) * _this->অঙ্ক_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

স্থির bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    ধ্রুৱ পূর্ণাঙ্ক screencount = Screen_গুনতি(dpy);
    ধ্রুৱ পূর্ণাঙ্ক default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, মূল_Window(dpy, default_screen));
    পূর্ণাঙ্ক xrandr_error_base = 0;
    পূর্ণাঙ্ক looking_for_primary;
    পূর্ণাঙ্ক output;
    পূর্ণাঙ্ক screen;

    যদি (!X11_XRRQueryExtension(dpy, &data->xrandr_event_base, &xrandr_error_base)) {
        ঘূৰাই SDL_SetError("XRRQueryExtension failed");
    }

    বাবে (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        বাবে (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            যদি (looking_for_primary && (screen != default_screen)) {
                অনুৱর্ত;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            যদি (!res) {
                অনুৱর্ত;
            }

            বাবে (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                যদি ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    অনুৱর্ত;
                }
                যদি (!X11_AddXRandRDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    ভঙ্গ;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_প্ৰবেশ(dpy, মূল_Window(dpy, screen), RROutputChangeNotifyMask);
        }
    }

    যদি (_this->অঙ্ক_displays == 0) {
        ঘূৰাই SDL_SetError("No available displays");
    }

    X11_SortOutputsByPriorityHint(_this);

    ঘূৰাই true;
}
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
স্থির bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    যদি (X11_AddGenericDisplay(_this, true) == 0) {
        ঘূৰাই false;
    }
    ঘূৰাই true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_VideoData *data = _this->internal;
        পূর্ণাঙ্ক xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        যদি (CheckXRandR(data->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            ঘূৰাই true;
        }
    }
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    ঘূৰাই X11_InitModes_StdXlib(_this);
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

    যদি (data->use_xrandr) {
        Display *display = _this->internal->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, মূল_Window(display, data->screen));
        যদি (res) {
            SDL_DisplayModeData *modedata;
            XRROutputInfo *output_info;
            পূর্ণাঙ্ক i;

            output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
            যদি (output_info && output_info->connection != RR_Disconnected) {
                বাবে (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_DisplayModeData *)SDL_calloc(1, পরিমাণ(SDL_DisplayModeData));
                    যদি (!modedata) {
                        অনুৱর্ত;
                    }
                    mode.internal = modedata;

                    যদি (!SetXRandRModeInfo(display, res, output_info->crtc, output_info->modes[i], &mode) ||
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
    ঘূৰাই true;
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
স্থির পূর্ণাঙ্ক (*PreXRRSetScreenSizeErrorHandler)(Display *, XErrorEvent *) = রিক্ত;
স্থির পূর্ণাঙ্ক SDL_XRRSetScreenSizeErrHandler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    যদি ((e->error_code == BadMatch) || (e->error_code == Bad_মান)) {
        ঘূৰাই 0;
    }

    ঘূৰাই PreXRRSetScreenSizeErrorHandler(d, e);
}
#endif

bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *data = sdl_display->internal;

    viddata->last_mode_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    যদি (!viddata->is_xwayland) {
        যদি (sdl_display->current_mode != mode) {
            data->mode_switch_deadline_ns = SDL_GetTicksNS() + MODE_SWITCH_TIMEOUT_NS;
        } অন্যথা {
            data->mode_switch_deadline_ns = 0;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    যদি (data->use_xrandr) {
        Display *display = viddata->display;
        SDL_DisplayModeData *modedata = mode->internal;
        পূর্ণাঙ্ক mm_width, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        Status status;

        res = X11_XRRGetScreenResources(display, মূল_Window(display, data->screen));
        যদি (!res) {
            ঘূৰাই SDL_SetError("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
        যদি (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            ঘূৰাই SDL_SetError("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        যদি (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            ঘূৰাই SDL_SetError("Couldn't get XRandR crtc info");
        }

        যদি (crtc->mode == modedata->xrandr_mode) {
#ifdef X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->mode, crtc->width, crtc->height);
#endif
            status = Success;
            গচ্ছ freeInfo;
        }

        X11_XGrabServer(display);
        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, রিক্ত, 0);
        যদি (status != Success) {
            গচ্ছ ungrabServer;
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
        X11_XRRSetScreenSize(display, মূল_Window(display, data->screen),
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

        যদি (status != Success) {
            ঘূৰাই SDL_SetError("X11_XRRSetCrtcConfig failed");
        }
    }
#অন্যথা
    (শূন্য)data;
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    ঘূৰাই true;
}

শূন্য X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_DisplayData *data = sdl_display->internal;

    rect->x = data->x;
    rect->y = data->y;
    rect->w = sdl_display->current_mode->w;
    rect->h = sdl_display->current_mode->h;
    ঘূৰাই true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    Atom _NET_WORKAREA;
    পূর্ণাঙ্ক real_format;
    Atom real_type;
    unsigned long বস্তুসমূহ_read = 0, বস্তুসমূহ_বাম = 0;
    unsigned ৱর্ণ *propdata = রিক্ত;
    bool result = false;

    যদি (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        ঘূৰাই false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    পূর্ণাঙ্ক status = X11_XGetWindowProperty(display, Default_মূল_Window(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &বস্তুসমূহ_read,
                                    &বস্তুসমূহ_বাম, &propdata);
    যদি ((status == Success) && (বস্তুসমূহ_read >= 4)) {
        ধ্রুৱ long *p = (long *)propdata;
        ধ্রুৱ SDL_Rect usable = { (পূর্ণাঙ্ক)p[0], (পূর্ণাঙ্ক)p[1], (পূর্ণাঙ্ক)p[2], (পূর্ণাঙ্ক)p[3] };
        result = true;
        যদি (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    যদি (propdata) {
        X11_XFree(propdata);
    }

    ঘূৰাই result;
}

#endif // SDL_VIDEO_DRIVER_X11
