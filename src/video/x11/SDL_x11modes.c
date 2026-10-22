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
#ضمن "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11settings.h"
#ضمن "edid.h"
#ضمن "../../events/SDL_displayevents_c.h"
#ضمن "../SDL_pixels_c.h"

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

عائم X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    مزدوج scale_factor = 0.0;

    // First use the forced scaling factor specified by the app/user
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_FACTOR);
    ܐܢ (hint && *hint) {
        مزدوج value = SDL_atof(hint);
        ܐܢ (value >= 1.0f && value <= 10.0f) {
            scale_factor = value;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    ܐܢ (scale_factor <= 0.0) {
        صحيح status, real_format;
        Atom real_type;
        Atom res_mgr;
        unsigned long items_read, items_left;
        حرف *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        status = X11_XGetWindowProperty(display, RootWindow(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &items_read, &items_left,
                                        (unsigned حرف **)&resource_manager);

        ܐܢ (status == Success && resource_manager) {
            owns_resource_manager = true;
        } ܐܚܪܢܐ {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        ܐܢ (resource_manager) {
            XrmDatabase db;
            XrmValue value;
            حرف *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            ܐܢ (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &value)) {
                ܐܢ (value.addr && type && SDL_strcmp(type, "String") == 0) {
                    صحيح dpi = SDL_atoi(value.addr);
                    scale_factor  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            ܐܢ (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    ܐܢ (scale_factor <= 0.0) {
        scale_factor = X11_GetXsettingsClientIntKey(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        ܐܢ (scale_factor <= 0.0) {
            صحيح dpi = X11_GetXsettingsClientIntKey(client, "Xft/DPI", -1);
            ܐܢ (dpi > 0) {
                scale_factor = (مزدوج) dpi / 1024.0;
                scale_factor /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    ܐܢ (scale_factor <= 0.0) {
        ثابت حرف *scale_str = SDL_getenv("GDK_SCALE");
        ܐܢ (scale_str) {
            scale_factor = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    ܐܢ (scale_factor <= 0.0) {
        scale_factor = 1.0;
    }

    ܦܢܐ (عائم)scale_factor;
}

عائم X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    ܦܢܐ X11_GetGlobalContentScale(_this->internal->display, _this->internal->xsettings_data.xsettings);
}

ساكن bool get_visualinfo(Display *display, صحيح screen, XVisualInfo *vinfo)
{
    ثابت حرف *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    صحيح depth;

    // Look for an exact visual, if requested
    ܐܢ (visual_id && *visual_id) {
        XVisualInfo *vi, template;
        صحيح nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(visual_id, عدم, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        ܐܢ (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            ܦܢܐ true;
        }
    }

    depth = DefaultDepth(display, screen);
    ܐܢ ((X11_UseDirectColorVisuals() &&
         X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
        ܦܢܐ true;
    }
    ܦܢܐ false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    صحيح nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    ܐܢ (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        ܦܢܐ true;
    }
    ܦܢܐ false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    ܐܢ (vinfo->class == DirectColor || vinfo->class == TrueColor) {
        صحيح bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_mask;
        Gmask = vinfo->visual->green_mask;
        Bmask = vinfo->visual->blue_mask;
        ܐܢ (vinfo->depth == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } ܐܚܪܢܐ {
            Amask = 0;
        }

        bpp = vinfo->depth;
        ܐܢ (bpp == 24) {
            صحيح i, n;
            XPixmapFormatValues *p = X11_XListPixmapFormats(display, &n);
            ܐܢ (p) {
                لكل (i = 0; i < n; ++i) {
                    ܐܢ (p[i].depth == 24) {
                        bpp = p[i].bits_per_pixel;
                        اكسر;
                    }
                }
                X11_XFree(p);
            }
        }

        ܦܢܐ SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    ܐܢ (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        بدل (vinfo->depth) {
        حالة 8:
            ܦܢܐ SDL_PIXELFORMAT_INDEX8;
        حالة 4:
            ܐܢ (BitmapBitOrder(display) == LSBFirst) {
                ܦܢܐ SDL_PIXELFORMAT_INDEX4LSB;
            } ܐܚܪܢܐ {
                ܦܢܐ SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        حالة 1:
            ܐܢ (BitmapBitOrder(display) == LSBFirst) {
                ܦܢܐ SDL_PIXELFORMAT_INDEX1LSB;
            } ܐܚܪܢܐ {
                ܦܢܐ SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    ܦܢܐ SDL_PIXELFORMAT_UNKNOWN;
}

ساكن SDL_DisplayID X11_AddGenericDisplay(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    ثابت صحيح default_screen = DefaultScreen(dpy);
    Screen *screen = ScreenOfDisplay(dpy, default_screen);
    صحيح scanline_pad, n, i;
    SDL_DisplayModeData *modedata;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    XPixmapFormatValues *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    ܐܢ (!get_visualinfo(dpy, default_screen, &vinfo)) {
        ܦܢܐ SDL_SetError("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ܐܢ (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        ܦܢܐ SDL_SetError("Palettized video modes are no longer supported");
    }

    SDL_zero(mode);
    mode.w = WidthOfScreen(screen);
    mode.h = HeightOfScreen(screen);
    mode.format = pixelformat;

    displaydata = (SDL_DisplayData *)SDL_calloc(1, حجم(*displaydata));
    ܐܢ (!displaydata) {
        ܦܢܐ false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, حجم(SDL_DisplayModeData));
    ܐܢ (!modedata) {
        SDL_free(displaydata);
        ܦܢܐ false;
    }
    mode.internal = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ܐܢ (pixmapformats) {
        لكل (i = 0; i < n; ++i) {
            ܐܢ (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                اكسر;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (حرف *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_mode = mode;
    display.internal = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    ܦܢܐ SDL_AddVideoDisplay(&display, send_event);
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR

ساكن فراغ X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(عدم);
    ܐܢ (displays) {
        لكل (صحيح i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ثابت SDL_DisplayData *displaydata = display->internal;
            ܐܢ (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

ساكن bool CheckXRandR(Display *display, صحيح *major, صحيح *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ifdef XRANDR_DISABLED_BY_DEFAULT
    ܐܢ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#endif
        ܦܢܐ false;
    }
#ܐܚܪܢܐ
    ܐܢ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#endif
        ܦܢܐ false;
    }
#endif // XRANDR_DISABLED_BY_DEFAULT

    ܐܢ (!SDL_X11_HAVE_XRANDR) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#endif
        ܦܢܐ false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    ܐܢ (!X11_XRRQueryVersion(display, major, minor)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#endif
        *major = *minor = 0;
        ܦܢܐ false;
    }
#ifdef X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#endif
    ܦܢܐ true;
}

#define XRANDR_ROTATION_LEFT  (1 << 1)
#define XRANDR_ROTATION_RIGHT (1 << 3)

ساكن فراغ CalculateXRandRRefreshRate(ثابت XRRModeInfo *info, صحيح *numerator, صحيح *denominator)
{
    unsigned صحيح vTotal = info->vTotal;

    ܐܢ (info->modeFlags & RR_DoubleScan) {
        // doublescan doubles the number of lines
        vTotal *= 2;
    }

    ܐܢ (info->modeFlags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        vTotal /= 2;
    }

    ܐܢ (info->hTotal && vTotal) {
        *numerator = info->dotClock;
        *denominator = (info->hTotal * vTotal);
    } ܐܚܪܢܐ {
        *numerator = 0;
        *denominator = 0;
    }
}

ساكن bool SetXRandRModeInfo(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode modeID, SDL_DisplayMode *mode)
{
    صحيح i;
    لكل (i = 0; i < res->nmode; ++i) {
        ثابت XRRModeInfo *info = &res->modes[i];
        ܐܢ (info->id == modeID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtcTransformAttributes *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            ܐܢ (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            ܐܢ (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            ܐܢ (rotation & (XRANDR_ROTATION_LEFT | XRANDR_ROTATION_RIGHT)) {
                mode->w = (info->height * scale_w + 0xffff) >> 16;
                mode->h = (info->width * scale_h + 0xffff) >> 16;
            } ܐܚܪܢܐ {
                mode->w = (info->width * scale_w + 0xffff) >> 16;
                mode->h = (info->height * scale_h + 0xffff) >> 16;
            }
            CalculateXRandRRefreshRate(info, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
            mode->internal->xrandr_mode = modeID;
#ifdef X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (صحيح)modeID,
                    mode->screen_w, mode->screen_h, mode->refresh_rate_numerator, mode->refresh_rate_denominator);
#endif
            ܦܢܐ true;
        }
    }
    ܦܢܐ false;
}

ساكن bool GetRootWindowCardinalProperty(Display *dpy, صحيح screen, ثابت حرف *name, Uint32 *value)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    ܐܢ (atom == None) {
        ܦܢܐ false;
    }

    صحيح real_format;
    Atom real_type;
    unsigned long items_read = 0, items_left = 0;
    unsigned حرف *propdata = عدم;
    صحيح status;
    bool result = false;

    status = X11_XGetWindowProperty(dpy, RootWindow(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &items_read, &items_left, &propdata);
    ܐܢ (status == Success && propdata) {
        ܐܢ (real_type == XA_CARDINAL && items_read > 0) {
            بدل (real_format) {
            حالة 8:
                *value = propdata[0];
                اكسر;
            حالة 16:
                *value = propdata[0] | (propdata[1] << 8);
                اكسر;
            افتراضي:
                *value = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                اكسر;
            }
            result = true;
        }
        X11_XFree(propdata);
    }
    ܦܢܐ result;
}

ساكن bool GetRootWindowBoolProperty(Display *dpy, صحيح screen, ثابت حرف *name, bool *value)
{
    Uint32 v;
    ܐܢ (GetRootWindowCardinalProperty(dpy, screen, name, &v)) {
        *value = (v != 0);
        ܦܢܐ true;
    }
    ܦܢܐ false;
}

ساكن bool GetRootWindowFloatProperty(Display *dpy, صحيح screen, ثابت حرف *name, عائم *value)
{
    Uint32 v;
    ܐܢ (GetRootWindowCardinalProperty(dpy, screen, name, &v)) {
        SDL_memcpy(value, &v, حجم(v));
        ܦܢܐ true;
    }
    ܦܢܐ false;
}

ساكن bool IsSteamDeckOLEDDisplay(ثابت MonitorInfo *info)
{
    ܐܢ (SDL_strcmp(info->manufacturer_code, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        ܐܢ (info->product_code == 0x3003 || info->product_code == 0x3004) {
            ܦܢܐ true;
        }
    }
    ܦܢܐ false;
}

ساكن عائم GetGamescopeSDRWhiteLevel(Display *dpy, صحيح screen, ثابت MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    ܐܢ (!dpy) {
        ܦܢܐ 0.0f;
    }

    عائم SDR_white_level = 0.0f;
    bool external_display = false;
    ܐܢ (GetRootWindowBoolProperty(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        GetRootWindowFloatProperty(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } ܐܚܪܢܐ ܐܢ (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (عائم)info->max_luminance / 3.0f;
    } ܐܚܪܢܐ {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    ܦܢܐ SDR_white_level;
}

ساكن MonitorInfo *GetMonitorInfo(Display *dpy, صحيح screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = عدم;
    صحيح real_format;
    Atom real_type;
    unsigned long items_read = 0, items_left = 0;
    unsigned حرف *propdata = عدم;
    صحيح status;

    *gamescope = false;

    ܐܢ (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_PATH = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        ܐܢ (GAMESCOPE_DISPLAY_EDID_PATH != None) {
            status = X11_XGetWindowProperty(dpy, RootWindow(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_PATH, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &items_read, &items_left, &propdata);
            ܐܢ (status == Success && propdata) {
                size_t size = 0;
                فراغ *data = SDL_LoadFile((حرف *)propdata, &size);
                ܐܢ (data) {
                    info = decode_edid((uchar *)data, size);
                    ܐܢ (info) {
                        *gamescope = true;
                    }
                    SDL_free(data);
                }
            }
            ܐܢ (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    ܐܢ (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        ܐܢ (EDID != None) {
            صحيح nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            لكل (صحيح i = 0; i < nprop; ++i) {
                ܐܢ (props[i] == EDID) {
                    status = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &items_read, &items_left, &propdata);
                    ܐܢ (status == Success && propdata) {
                        info = decode_edid(propdata, items_read);
                    }
                    ܐܢ (propdata) {
                        X11_XFree(propdata);
                    }
                    اكسر;
                }
            }

            ܐܢ (props) {
                X11_XFree(props);
            }
        }
    }

#ifdef X11MODES_DEBUG
    ܐܢ (info) {
        dump_monitor_info(info);
    }
#endif
    ܦܢܐ info;
}

ساكن فراغ SetXRandRDisplayName(MonitorInfo *info, حرف *name, size_t namelen, unsigned long widthmm, unsigned long heightmm)
{
    ܐܢ (info) {
        SDL_strlcpy(name, info->dsc_product_name, namelen);
    }

    صحيح inches = (صحيح)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    ܐܢ (*name && inches) {
        ثابت size_t len = SDL_strlen(name);
        (فراغ)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ifdef X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#endif
}

ساكن bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, صحيح screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, حرف *display_name, size_t display_name_size)
{
    XRROutputInfo *output_info;
    صحيح display_x, display_y;
    unsigned long display_mm_width, display_mm_height;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    SDL_DisplayModeData *modedata;
    RRMode modeID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmapFormatValues *pixmapformats;
    صحيح scanline_pad;
    صحيح i, n;

    ܐܢ (!display || !display_name) {
        ܦܢܐ false; // invalid parameters
    }

    ܐܢ (!get_visualinfo(dpy, screen, &vinfo)) {
        ܦܢܐ false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ܐܢ (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        ܦܢܐ false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ܐܢ (pixmapformats) {
        لكل (i = 0; i < n; i++) {
            ܐܢ (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                اكسر;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    ܐܢ (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        ܦܢܐ false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_size);
    display_mm_width = output_info->mm_width;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    ܐܢ (!crtc) {
        ܦܢܐ false; // oh well, ignore it.
    }

    SDL_zero(mode);
    modeID = crtc->mode;
    mode.w = crtc->width;
    mode.h = crtc->height;
    mode.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_DisplayData *)SDL_calloc(1, حجم(*displaydata));
    ܐܢ (!displaydata) {
        ܦܢܐ false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, حجم(SDL_DisplayModeData));
    ܐܢ (!modedata) {
        SDL_free(displaydata);
        ܦܢܐ false;
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
    SDL_strlcpy(displaydata->connector_name, display_name, حجم(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    SetXRandRModeInfo(dpy, res, output_crtc, modeID, &mode);
    SetXRandRDisplayName(info, display_name, display_name_size, display_mm_width, display_mm_height);

    SDL_zero(*display);
    ܐܢ (*display_name) {
        display->name = display_name;
    }
    display->desktop_mode = mode;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->internal = displaydata;

    ܐܢ (info) {
        عائم SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        ܐܢ (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } ܐܚܪܢܐ {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ifdef X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#endif
        ܐܢ (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (عائم)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    ܦܢܐ true;
}

ساكن bool X11_AddXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, صحيح screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    حرف display_name[128];

    ܐܢ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, حجم(display_name))) {
        ܦܢܐ true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    ܐܢ (displayID == 0) {
        ܦܢܐ false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    ܐܢ (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    ܦܢܐ true;
}


ساكن bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, صحيح screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    حرف display_name[128];

    ܐܢ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, حجم(display_name))) {
        ܦܢܐ false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_SetDesktopDisplayMode(existing_display, &display.desktop_mode);

    // update bounds
    ܐܢ (existing_display->internal->x != display.internal->x ||
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

    ܦܢܐ true;
}

ساكن XRRScreenResources *X11_GetScreenResources(Display *dpy, صحيح screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, RootWindow(dpy, screen));
    ܐܢ (!res || res->noutput == 0) {
        ܐܢ (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, RootWindow(dpy, screen));
    }
    ܦܢܐ res;
}

فراغ X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    ثابت صحيح screencount = ScreenCount(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(عدم);
    ܐܢ (!displays) {
        ܦܢܐ;
    }

    لكل (صحيح screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ܐܢ (!res) {
            استمر;
        }

        لكل (صحيح i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ثابت SDL_DisplayData *displaydata = display->internal;
            ܐܢ (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

ساكن فراغ X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    ثابت صحيح screencount = ScreenCount(dpy);
    صحيح num_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&num_displays);
    ܐܢ (!displays) {
        ܦܢܐ;
    }

    لكل (صحيح screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ܐܢ (!res) {
            استمر;
        }

        لكل (صحيح output = 0; output < res->noutput; output++) {
            لكل (صحيح i = 0; i < num_displays; ++i) {
                ܐܢ (!displays[i]) {
                    // We already removed this display from the list
                    استمر;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                ثابت SDL_DisplayData *displaydata = display->internal;
                ܐܢ (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    اكسر;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    لكل (صحيح i = 0; i < num_displays; ++i) {
        ܐܢ (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ثابت SDL_DisplayData *displaydata = display->internal;
            ܐܢ (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

ساكن فراغ X11_HandleXRandROutputChange(SDL_VideoDevice *_this, ثابت XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = عدم;
    صحيح i;

#ܐܢ 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (unsigned صحيح) ev->output, (unsigned صحيح) ev->crtc, (unsigned صحيح) ev->mode, (unsigned صحيح) ev->rotation, (unsigned صحيح) ev->connection);
#endif

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(عدم);
    ܐܢ (displays) {
        لكل (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            ثابت SDL_DisplayData *displaydata = thisdisplay->internal;
            ܐܢ (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                اكسر;
            }
        }
        SDL_free(displays);
    }

    ܐܢ (ev->connection == RR_Disconnected) { // output is going away
        ܐܢ (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            ܐܢ (_this->num_displays == 1) {
                generic_display = X11_AddGenericDisplay(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            ܐܢ (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } ܐܚܪܢܐ ܐܢ (ev->connection == RR_Connected) { // output is coming online
        ܐܢ (!display) {
            Display *dpy = ev->display;
            ثابت صحيح screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ܐܢ (res) {
                X11_AddXRandRDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

فراغ X11_HandleXRandREvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_assert(xevent->type == (videodata->xrandr_event_base + RRNotify));

    بدل (((ثابت XRRNotifyEvent *)xevent)->subtype) {
    حالة RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (ثابت XRROutputChangeNotifyEvent *)xevent);
        اكسر;
    افتراضي:
        اكسر;
    }
}

ساكن فراغ X11_SortOutputsByPriorityHint(SDL_VideoDevice *_this)
{
    ثابت حرف *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    ܐܢ (name_hint) {
        حرف *saveptr;
        حرف *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(حجم(SDL_VideoDisplay *) * _this->num_displays);

        ܐܢ (str && sorted_list) {
            صحيح sorted_index = 0;

            // Sort the requested displays to the front of the list.
            ثابت حرف *token = SDL_strtok_r(str, ",", &saveptr);
            ܟܡܐ (token) {
                لكل (صحيح i = 0; i < _this->num_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    ܐܢ (d) {
                        SDL_DisplayData *data = d->internal;
                        ܐܢ (SDL_strcmp(token, data->connector_name) == 0) {
                            sorted_list[sorted_index++] = d;
                            _this->displays[i] = عدم;
                            اكسر;
                        }
                    }
                }

                token = SDL_strtok_r(عدم, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            لكل (صحيح i = 0; i < _this->num_displays; ++i) {
                ܐܢ (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, حجم(SDL_VideoDisplay *) * _this->num_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ساكن bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    ثابت صحيح screencount = ScreenCount(dpy);
    ثابت صحيح default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, RootWindow(dpy, default_screen));
    صحيح xrandr_error_base = 0;
    صحيح looking_for_primary;
    صحيح output;
    صحيح screen;

    ܐܢ (!X11_XRRQueryExtension(dpy, &data->xrandr_event_base, &xrandr_error_base)) {
        ܦܢܐ SDL_SetError("XRRQueryExtension failed");
    }

    لكل (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        لكل (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            ܐܢ (looking_for_primary && (screen != default_screen)) {
                استمر;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ܐܢ (!res) {
                استمر;
            }

            لكل (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                ܐܢ ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    استمر;
                }
                ܐܢ (!X11_AddXRandRDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    اكسر;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelectInput(dpy, RootWindow(dpy, screen), RROutputChangeNotifyMask);
        }
    }

    ܐܢ (_this->num_displays == 0) {
        ܦܢܐ SDL_SetError("No available displays");
    }

    X11_SortOutputsByPriorityHint(_this);

    ܦܢܐ true;
}
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
ساكن bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    ܐܢ (X11_AddGenericDisplay(_this, true) == 0) {
        ܦܢܐ false;
    }
    ܦܢܐ true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_VideoData *data = _this->internal;
        صحيح xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        ܐܢ (CheckXRandR(data->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            ܦܢܐ true;
        }
    }
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    ܦܢܐ X11_InitModes_StdXlib(_this);
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

    ܐܢ (data->use_xrandr) {
        Display *display = _this->internal->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, RootWindow(display, data->screen));
        ܐܢ (res) {
            SDL_DisplayModeData *modedata;
            XRROutputInfo *output_info;
            صحيح i;

            output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
            ܐܢ (output_info && output_info->connection != RR_Disconnected) {
                لكل (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_DisplayModeData *)SDL_calloc(1, حجم(SDL_DisplayModeData));
                    ܐܢ (!modedata) {
                        استمر;
                    }
                    mode.internal = modedata;

                    ܐܢ (!SetXRandRModeInfo(display, res, output_info->crtc, output_info->modes[i], &mode) ||
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
    ܦܢܐ true;
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
ساكن صحيح (*PreXRRSetScreenSizeErrorHandler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح SDL_XRRSetScreenSizeErrHandler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    ܐܢ ((e->error_code == BadMatch) || (e->error_code == BadValue)) {
        ܦܢܐ 0;
    }

    ܦܢܐ PreXRRSetScreenSizeErrorHandler(d, e);
}
#endif

bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *data = sdl_display->internal;

    viddata->last_mode_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    ܐܢ (!viddata->is_xwayland) {
        ܐܢ (sdl_display->current_mode != mode) {
            data->mode_switch_deadline_ns = SDL_GetTicksNS() + MODE_SWITCH_TIMEOUT_NS;
        } ܐܚܪܢܐ {
            data->mode_switch_deadline_ns = 0;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    ܐܢ (data->use_xrandr) {
        Display *display = viddata->display;
        SDL_DisplayModeData *modedata = mode->internal;
        صحيح mm_width, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        Status status;

        res = X11_XRRGetScreenResources(display, RootWindow(display, data->screen));
        ܐܢ (!res) {
            ܦܢܐ SDL_SetError("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
        ܐܢ (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            ܦܢܐ SDL_SetError("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        ܐܢ (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            ܦܢܐ SDL_SetError("Couldn't get XRandR crtc info");
        }

        ܐܢ (crtc->mode == modedata->xrandr_mode) {
#ifdef X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->mode, crtc->width, crtc->height);
#endif
            status = Success;
            اذهب freeInfo;
        }

        X11_XGrabServer(display);
        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, عدم, 0);
        ܐܢ (status != Success) {
            اذهب ungrabServer;
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
        X11_XRRSetScreenSize(display, RootWindow(display, data->screen),
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

        ܐܢ (status != Success) {
            ܦܢܐ SDL_SetError("X11_XRRSetCrtcConfig failed");
        }
    }
#ܐܚܪܢܐ
    (فراغ)data;
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    ܦܢܐ true;
}

فراغ X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_DisplayData *data = sdl_display->internal;

    rect->x = data->x;
    rect->y = data->y;
    rect->w = sdl_display->current_mode->w;
    rect->h = sdl_display->current_mode->h;
    ܦܢܐ true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    Atom _NET_WORKAREA;
    صحيح real_format;
    Atom real_type;
    unsigned long items_read = 0, items_left = 0;
    unsigned حرف *propdata = عدم;
    bool result = false;

    ܐܢ (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        ܦܢܐ false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    صحيح status = X11_XGetWindowProperty(display, DefaultRootWindow(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &items_read,
                                    &items_left, &propdata);
    ܐܢ ((status == Success) && (items_read >= 4)) {
        ثابت long *p = (long *)propdata;
        ثابت SDL_Rect usable = { (صحيح)p[0], (صحيح)p[1], (صحيح)p[2], (صحيح)p[3] };
        result = true;
        ܐܢ (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    ܐܢ (propdata) {
        X11_XFree(propdata);
    }

    ܦܢܐ result;
}

#endif // SDL_VIDEO_DRIVER_X11
