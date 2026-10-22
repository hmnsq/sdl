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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#અન્તર્ભાવ "SDL_x11video.h"
#અન્તર્ભાવ "SDL_x11settings.h"
#અન્તર્ભાવ "edid.h"
#અન્તર્ભાવ "../../events/SDL_displayevents_c.h"
#અન્તર્ભાવ "../SDL_pixels_c.h"

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

દશાંશ X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    દ્વિગુણ scale_factor = 0.0;

    // First use the forced scaling factor specified by the app/user
    અચલ અક્ષર *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_FACTOR);
    જો (hint && *hint) {
        દ્વિગુણ કિંમત = SDL_atof(hint);
        જો (કિંમત >= 1.0f && કિંમત <= 10.0f) {
            scale_factor = કિંમત;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    જો (scale_factor <= 0.0) {
        પૂર્ણાંક status, real_format;
        Atom real_type;
        Atom res_mgr;
        unsigned long વસ્તુઓ_read, વસ્તુઓ_ડાબું;
        અક્ષર *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        status = X11_XGetWindowProperty(display, મૂળ_Window(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &વસ્તુઓ_read, &વસ્તુઓ_ડાબું,
                                        (unsigned અક્ષર **)&resource_manager);

        જો (status == Success && resource_manager) {
            owns_resource_manager = true;
        } નહીંતર {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        જો (resource_manager) {
            XrmDatabase db;
            Xrm_કિંમત કિંમત;
            અક્ષર *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            જો (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &કિંમત)) {
                જો (કિંમત.addr && type && SDL_strcmp(type, "String") == 0) {
                    પૂર્ણાંક dpi = SDL_atoi(કિંમત.addr);
                    scale_factor  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            જો (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    જો (scale_factor <= 0.0) {
        scale_factor = X11_Get_Xsettings_Client_Int_ચાવી(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        જો (scale_factor <= 0.0) {
            પૂર્ણાંક dpi = X11_Get_Xsettings_Client_Int_ચાવી(client, "Xft/DPI", -1);
            જો (dpi > 0) {
                scale_factor = (દ્વિગુણ) dpi / 1024.0;
                scale_factor /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    જો (scale_factor <= 0.0) {
        અચલ અક્ષર *scale_str = SDL_getenv("GDK_SCALE");
        જો (scale_str) {
            scale_factor = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    જો (scale_factor <= 0.0) {
        scale_factor = 1.0;
    }

    પાછા (દશાંશ)scale_factor;
}

દશાંશ X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    પાછા X11_GetGlobalContentScale(_this->internal->display, _this->internal->xsettings_data.xsettings);
}

સ્થિર bool get_visualinfo(Display *display, પૂર્ણાંક screen, XVisualInfo *vinfo)
{
    અચલ અક્ષર *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    પૂર્ણાંક depth;

    // Look for an exact visual, if requested
    જો (visual_id && *visual_id) {
        XVisualInfo *vi, template;
        પૂર્ણાંક nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(visual_id, ખાલી, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        જો (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            પાછા true;
        }
    }

    depth = DefaultDepth(display, screen);
    જો ((X11_UseDirectColorVisuals() &&
         X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
        પાછા true;
    }
    પાછા false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    પૂર્ણાંક nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    જો (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        પાછા true;
    }
    પાછા false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    જો (vinfo->class == DirectColor || vinfo->class == TrueColor) {
        પૂર્ણાંક bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_mask;
        Gmask = vinfo->visual->green_mask;
        Bmask = vinfo->visual->blue_mask;
        જો (vinfo->depth == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } નહીંતર {
            Amask = 0;
        }

        bpp = vinfo->depth;
        જો (bpp == 24) {
            પૂર્ણાંક i, n;
            XPixmap_Format_કિંમતો *p = X11_XListPixmapFormats(display, &n);
            જો (p) {
                માટે (i = 0; i < n; ++i) {
                    જો (p[i].depth == 24) {
                        bpp = p[i].bits_per_pixel;
                        તોડો;
                    }
                }
                X11_XFree(p);
            }
        }

        પાછા SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    જો (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        પસંદગી (vinfo->depth) {
        સ્થિતિ 8:
            પાછા SDL_PIXELFORMAT_INDEX8;
        સ્થિતિ 4:
            જો (BitmapBitOrder(display) == LSBFirst) {
                પાછા SDL_PIXELFORMAT_INDEX4LSB;
            } નહીંતર {
                પાછા SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        સ્થિતિ 1:
            જો (BitmapBitOrder(display) == LSBFirst) {
                પાછા SDL_PIXELFORMAT_INDEX1LSB;
            } નહીંતર {
                પાછા SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    પાછા SDL_PIXELFORMAT_UNKNOWN;
}

સ્થિર SDL_DisplayID X11_AddGenericDisplay(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    અચલ પૂર્ણાંક default_screen = DefaultScreen(dpy);
    Screen *screen = ScreenOfDisplay(dpy, default_screen);
    પૂર્ણાંક scanline_pad, n, i;
    SDL_DisplayModeData *modedata;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    XPixmap_Format_કિંમતો *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    જો (!get_visualinfo(dpy, default_screen, &vinfo)) {
        પાછા SDL_SetError("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    જો (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        પાછા SDL_SetError("Palettized video modes are no longer supported");
    }

    SDL_zero(mode);
    mode.w = WidthOfScreen(screen);
    mode.h = HeightOfScreen(screen);
    mode.format = pixelformat;

    displaydata = (SDL_DisplayData *)SDL_calloc(1, કદ(*displaydata));
    જો (!displaydata) {
        પાછા false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, કદ(SDL_DisplayModeData));
    જો (!modedata) {
        SDL_free(displaydata);
        પાછા false;
    }
    mode.internal = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    જો (pixmapformats) {
        માટે (i = 0; i < n; ++i) {
            જો (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                તોડો;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (અક્ષર *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_mode = mode;
    display.internal = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    પાછા SDL_AddVideoDisplay(&display, send_event);
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR

સ્થિર શૂન્ય X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(ખાલી);
    જો (displays) {
        માટે (પૂર્ણાંક i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            અચલ SDL_DisplayData *displaydata = display->internal;
            જો (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

સ્થિર bool CheckXRandR(Display *display, પૂર્ણાંક *major, પૂર્ણાંક *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ifdef XRANDR_DISABLED_BY_DEFAULT
    જો (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#endif
        પાછા false;
    }
#નહીંતર
    જો (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#endif
        પાછા false;
    }
#endif // XRANDR_DISABLED_BY_DEFAULT

    જો (!SDL_X11_HAVE_XRANDR) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#endif
        પાછા false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    જો (!X11_XRRQueryVersion(display, major, minor)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#endif
        *major = *minor = 0;
        પાછા false;
    }
#ifdef X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#endif
    પાછા true;
}

#define XRANDR_ROTATION_ડાબું  (1 << 1)
#define XRANDR_ROTATION_જમણું (1 << 3)

સ્થિર શૂન્ય CalculateXRandRRefreshRate(અચલ XRRModeInfo *info, પૂર્ણાંક *numerator, પૂર્ણાંક *denominator)
{
    unsigned પૂર્ણાંક vTotal = info->vTotal;

    જો (info->modeFlags & RR_DoubleScan) {
        // doublescan doubles the number of lines
        vTotal *= 2;
    }

    જો (info->modeFlags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        vTotal /= 2;
    }

    જો (info->hTotal && vTotal) {
        *numerator = info->dotClock;
        *denominator = (info->hTotal * vTotal);
    } નહીંતર {
        *numerator = 0;
        *denominator = 0;
    }
}

સ્થિર bool SetXRandRModeInfo(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode modeID, SDL_DisplayMode *mode)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < res->nmode; ++i) {
        અચલ XRRModeInfo *info = &res->modes[i];
        જો (info->id == modeID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtcTransformAttributes *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            જો (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            જો (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            જો (rotation & (XRANDR_ROTATION_ડાબું | XRANDR_ROTATION_જમણું)) {
                mode->w = (info->height * scale_w + 0xffff) >> 16;
                mode->h = (info->width * scale_h + 0xffff) >> 16;
            } નહીંતર {
                mode->w = (info->width * scale_w + 0xffff) >> 16;
                mode->h = (info->height * scale_h + 0xffff) >> 16;
            }
            CalculateXRandRRefreshRate(info, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
            mode->internal->xrandr_mode = modeID;
#ifdef X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (પૂર્ણાંક)modeID,
                    mode->screen_w, mode->screen_h, mode->refresh_rate_numerator, mode->refresh_rate_denominator);
#endif
            પાછા true;
        }
    }
    પાછા false;
}

સ્થિર bool Get_મૂળ_Window_Cardinal_Property(Display *dpy, પૂર્ણાંક screen, અચલ અક્ષર *name, Uint32 *કિંમત)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    જો (atom == None) {
        પાછા false;
    }

    પૂર્ણાંક real_format;
    Atom real_type;
    unsigned long વસ્તુઓ_read = 0, વસ્તુઓ_ડાબું = 0;
    unsigned અક્ષર *propdata = ખાલી;
    પૂર્ણાંક status;
    bool result = false;

    status = X11_XGetWindowProperty(dpy, મૂળ_Window(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &વસ્તુઓ_read, &વસ્તુઓ_ડાબું, &propdata);
    જો (status == Success && propdata) {
        જો (real_type == XA_CARDINAL && વસ્તુઓ_read > 0) {
            પસંદગી (real_format) {
            સ્થિતિ 8:
                *કિંમત = propdata[0];
                તોડો;
            સ્થિતિ 16:
                *કિંમત = propdata[0] | (propdata[1] << 8);
                તોડો;
            મૂળભૂત:
                *કિંમત = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                તોડો;
            }
            result = true;
        }
        X11_XFree(propdata);
    }
    પાછા result;
}

સ્થિર bool Get_મૂળ_Window_Bool_Property(Display *dpy, પૂર્ણાંક screen, અચલ અક્ષર *name, bool *કિંમત)
{
    Uint32 v;
    જો (Get_મૂળ_Window_Cardinal_Property(dpy, screen, name, &v)) {
        *કિંમત = (v != 0);
        પાછા true;
    }
    પાછા false;
}

સ્થિર bool Get_મૂળ_Window_Float_Property(Display *dpy, પૂર્ણાંક screen, અચલ અક્ષર *name, દશાંશ *કિંમત)
{
    Uint32 v;
    જો (Get_મૂળ_Window_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(કિંમત, &v, કદ(v));
        પાછા true;
    }
    પાછા false;
}

સ્થિર bool IsSteamDeckOLEDDisplay(અચલ MonitorInfo *info)
{
    જો (SDL_strcmp(info->manufacturer_code, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        જો (info->product_code == 0x3003 || info->product_code == 0x3004) {
            પાછા true;
        }
    }
    પાછા false;
}

સ્થિર દશાંશ GetGamescopeSDRWhiteLevel(Display *dpy, પૂર્ણાંક screen, અચલ MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    જો (!dpy) {
        પાછા 0.0f;
    }

    દશાંશ SDR_white_level = 0.0f;
    bool external_display = false;
    જો (Get_મૂળ_Window_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_મૂળ_Window_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } નહીંતર જો (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (દશાંશ)info->max_luminance / 3.0f;
    } નહીંતર {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    પાછા SDR_white_level;
}

સ્થિર MonitorInfo *GetMonitorInfo(Display *dpy, પૂર્ણાંક screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = ખાલી;
    પૂર્ણાંક real_format;
    Atom real_type;
    unsigned long વસ્તુઓ_read = 0, વસ્તુઓ_ડાબું = 0;
    unsigned અક્ષર *propdata = ખાલી;
    પૂર્ણાંક status;

    *gamescope = false;

    જો (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_PATH = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        જો (GAMESCOPE_DISPLAY_EDID_PATH != None) {
            status = X11_XGetWindowProperty(dpy, મૂળ_Window(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_PATH, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &વસ્તુઓ_read, &વસ્તુઓ_ડાબું, &propdata);
            જો (status == Success && propdata) {
                size_t size = 0;
                શૂન્ય *data = SDL_LoadFile((અક્ષર *)propdata, &size);
                જો (data) {
                    info = decode_edid((uchar *)data, size);
                    જો (info) {
                        *gamescope = true;
                    }
                    SDL_free(data);
                }
            }
            જો (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    જો (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        જો (EDID != None) {
            પૂર્ણાંક nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            માટે (પૂર્ણાંક i = 0; i < nprop; ++i) {
                જો (props[i] == EDID) {
                    status = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &વસ્તુઓ_read, &વસ્તુઓ_ડાબું, &propdata);
                    જો (status == Success && propdata) {
                        info = decode_edid(propdata, વસ્તુઓ_read);
                    }
                    જો (propdata) {
                        X11_XFree(propdata);
                    }
                    તોડો;
                }
            }

            જો (props) {
                X11_XFree(props);
            }
        }
    }

#ifdef X11MODES_DEBUG
    જો (info) {
        dump_monitor_info(info);
    }
#endif
    પાછા info;
}

સ્થિર શૂન્ય SetXRandRDisplayName(MonitorInfo *info, અક્ષર *name, size_t namelen, unsigned long widthmm, unsigned long heightmm)
{
    જો (info) {
        SDL_strlcpy(name, info->dsc_product_name, namelen);
    }

    પૂર્ણાંક inches = (પૂર્ણાંક)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    જો (*name && inches) {
        અચલ size_t len = SDL_strlen(name);
        (શૂન્ય)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ifdef X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#endif
}

સ્થિર bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, પૂર્ણાંક screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, અક્ષર *display_name, size_t display_name_size)
{
    XRROutputInfo *output_info;
    પૂર્ણાંક display_x, display_y;
    unsigned long display_mm_width, display_mm_height;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    SDL_DisplayModeData *modedata;
    RRMode modeID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_કિંમતો *pixmapformats;
    પૂર્ણાંક scanline_pad;
    પૂર્ણાંક i, n;

    જો (!display || !display_name) {
        પાછા false; // invalid parameters
    }

    જો (!get_visualinfo(dpy, screen, &vinfo)) {
        પાછા false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    જો (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        પાછા false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    જો (pixmapformats) {
        માટે (i = 0; i < n; i++) {
            જો (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                તોડો;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    જો (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        પાછા false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_size);
    display_mm_width = output_info->mm_width;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    જો (!crtc) {
        પાછા false; // oh well, ignore it.
    }

    SDL_zero(mode);
    modeID = crtc->mode;
    mode.w = crtc->width;
    mode.h = crtc->height;
    mode.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_DisplayData *)SDL_calloc(1, કદ(*displaydata));
    જો (!displaydata) {
        પાછા false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, કદ(SDL_DisplayModeData));
    જો (!modedata) {
        SDL_free(displaydata);
        પાછા false;
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
    SDL_strlcpy(displaydata->connector_name, display_name, કદ(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    SetXRandRModeInfo(dpy, res, output_crtc, modeID, &mode);
    SetXRandRDisplayName(info, display_name, display_name_size, display_mm_width, display_mm_height);

    SDL_zero(*display);
    જો (*display_name) {
        display->name = display_name;
    }
    display->desktop_mode = mode;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->internal = displaydata;

    જો (info) {
        દશાંશ SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        જો (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } નહીંતર {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ifdef X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#endif
        જો (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (દશાંશ)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    પાછા true;
}

સ્થિર bool X11_AddXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, પૂર્ણાંક screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    અક્ષર display_name[128];

    જો (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, કદ(display_name))) {
        પાછા true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    જો (displayID == 0) {
        પાછા false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    જો (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    પાછા true;
}


સ્થિર bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, પૂર્ણાંક screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    અક્ષર display_name[128];

    જો (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, કદ(display_name))) {
        પાછા false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_SetDesktopDisplayMode(existing_display, &display.desktop_mode);

    // update bounds
    જો (existing_display->internal->x != display.internal->x ||
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

    પાછા true;
}

સ્થિર XRRScreenResources *X11_GetScreenResources(Display *dpy, પૂર્ણાંક screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, મૂળ_Window(dpy, screen));
    જો (!res || res->noutput == 0) {
        જો (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, મૂળ_Window(dpy, screen));
    }
    પાછા res;
}

શૂન્ય X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    અચલ પૂર્ણાંક screencount = Screen_ગણતરી(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(ખાલી);
    જો (!displays) {
        પાછા;
    }

    માટે (પૂર્ણાંક screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        જો (!res) {
            ચાલુ;
        }

        માટે (પૂર્ણાંક i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            અચલ SDL_DisplayData *displaydata = display->internal;
            જો (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

સ્થિર શૂન્ય X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    અચલ પૂર્ણાંક screencount = Screen_ગણતરી(dpy);
    પૂર્ણાંક અંક_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&અંક_displays);
    જો (!displays) {
        પાછા;
    }

    માટે (પૂર્ણાંક screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        જો (!res) {
            ચાલુ;
        }

        માટે (પૂર્ણાંક output = 0; output < res->noutput; output++) {
            માટે (પૂર્ણાંક i = 0; i < અંક_displays; ++i) {
                જો (!displays[i]) {
                    // We already removed this display from the list
                    ચાલુ;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                અચલ SDL_DisplayData *displaydata = display->internal;
                જો (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    તોડો;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    માટે (પૂર્ણાંક i = 0; i < અંક_displays; ++i) {
        જો (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            અચલ SDL_DisplayData *displaydata = display->internal;
            જો (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

સ્થિર શૂન્ય X11_HandleXRandROutputChange(SDL_VideoDevice *_this, અચલ XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = ખાલી;
    પૂર્ણાંક i;

#જો 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (unsigned પૂર્ણાંક) ev->output, (unsigned પૂર્ણાંક) ev->crtc, (unsigned પૂર્ણાંક) ev->mode, (unsigned પૂર્ણાંક) ev->rotation, (unsigned પૂર્ણાંક) ev->connection);
#endif

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(ખાલી);
    જો (displays) {
        માટે (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            અચલ SDL_DisplayData *displaydata = thisdisplay->internal;
            જો (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                તોડો;
            }
        }
        SDL_free(displays);
    }

    જો (ev->connection == RR_Disconnected) { // output is going away
        જો (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            જો (_this->અંક_displays == 1) {
                generic_display = X11_AddGenericDisplay(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            જો (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } નહીંતર જો (ev->connection == RR_Connected) { // output is coming online
        જો (!display) {
            Display *dpy = ev->display;
            અચલ પૂર્ણાંક screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            જો (res) {
                X11_AddXRandRDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

શૂન્ય X11_HandleXRandREvent(SDL_VideoDevice *_this, અચલ XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_assert(xevent->type == (videodata->xrandr_event_base + RRNotify));

    પસંદગી (((અચલ XRRNotifyEvent *)xevent)->subtype) {
    સ્થિતિ RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (અચલ XRROutputChangeNotifyEvent *)xevent);
        તોડો;
    મૂળભૂત:
        તોડો;
    }
}

સ્થિર શૂન્ય X11_SortOutputsByPriorityHint(SDL_VideoDevice *_this)
{
    અચલ અક્ષર *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    જો (name_hint) {
        અક્ષર *saveptr;
        અક્ષર *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(કદ(SDL_VideoDisplay *) * _this->અંક_displays);

        જો (str && sorted_list) {
            પૂર્ણાંક sorted_index = 0;

            // Sort the requested displays to the front of the list.
            અચલ અક્ષર *token = SDL_strtok_r(str, ",", &saveptr);
            જ્યારે (token) {
                માટે (પૂર્ણાંક i = 0; i < _this->અંક_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    જો (d) {
                        SDL_DisplayData *data = d->internal;
                        જો (SDL_strcmp(token, data->connector_name) == 0) {
                            sorted_list[sorted_index++] = d;
                            _this->displays[i] = ખાલી;
                            તોડો;
                        }
                    }
                }

                token = SDL_strtok_r(ખાલી, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            માટે (પૂર્ણાંક i = 0; i < _this->અંક_displays; ++i) {
                જો (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, કદ(SDL_VideoDisplay *) * _this->અંક_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

સ્થિર bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    અચલ પૂર્ણાંક screencount = Screen_ગણતરી(dpy);
    અચલ પૂર્ણાંક default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, મૂળ_Window(dpy, default_screen));
    પૂર્ણાંક xrandr_error_base = 0;
    પૂર્ણાંક looking_for_primary;
    પૂર્ણાંક output;
    પૂર્ણાંક screen;

    જો (!X11_XRRQueryExtension(dpy, &data->xrandr_event_base, &xrandr_error_base)) {
        પાછા SDL_SetError("XRRQueryExtension failed");
    }

    માટે (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        માટે (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            જો (looking_for_primary && (screen != default_screen)) {
                ચાલુ;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            જો (!res) {
                ચાલુ;
            }

            માટે (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                જો ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    ચાલુ;
                }
                જો (!X11_AddXRandRDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    તોડો;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_આગત(dpy, મૂળ_Window(dpy, screen), RROutputChangeNotifyMask);
        }
    }

    જો (_this->અંક_displays == 0) {
        પાછા SDL_SetError("No available displays");
    }

    X11_SortOutputsByPriorityHint(_this);

    પાછા true;
}
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
સ્થિર bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    જો (X11_AddGenericDisplay(_this, true) == 0) {
        પાછા false;
    }
    પાછા true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_VideoData *data = _this->internal;
        પૂર્ણાંક xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        જો (CheckXRandR(data->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            પાછા true;
        }
    }
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    પાછા X11_InitModes_StdXlib(_this);
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

    જો (data->use_xrandr) {
        Display *display = _this->internal->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, મૂળ_Window(display, data->screen));
        જો (res) {
            SDL_DisplayModeData *modedata;
            XRROutputInfo *output_info;
            પૂર્ણાંક i;

            output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
            જો (output_info && output_info->connection != RR_Disconnected) {
                માટે (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_DisplayModeData *)SDL_calloc(1, કદ(SDL_DisplayModeData));
                    જો (!modedata) {
                        ચાલુ;
                    }
                    mode.internal = modedata;

                    જો (!SetXRandRModeInfo(display, res, output_info->crtc, output_info->modes[i], &mode) ||
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
    પાછા true;
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
સ્થિર પૂર્ણાંક (*PreXRRSetScreenSizeErrorHandler)(Display *, XErrorEvent *) = ખાલી;
સ્થિર પૂર્ણાંક SDL_XRRSetScreenSizeErrHandler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    જો ((e->error_code == BadMatch) || (e->error_code == Bad_કિંમત)) {
        પાછા 0;
    }

    પાછા PreXRRSetScreenSizeErrorHandler(d, e);
}
#endif

bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *data = sdl_display->internal;

    viddata->last_mode_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    જો (!viddata->is_xwayland) {
        જો (sdl_display->current_mode != mode) {
            data->mode_switch_deadline_ns = SDL_GetTicksNS() + MODE_SWITCH_TIMEOUT_NS;
        } નહીંતર {
            data->mode_switch_deadline_ns = 0;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    જો (data->use_xrandr) {
        Display *display = viddata->display;
        SDL_DisplayModeData *modedata = mode->internal;
        પૂર્ણાંક mm_width, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        Status status;

        res = X11_XRRGetScreenResources(display, મૂળ_Window(display, data->screen));
        જો (!res) {
            પાછા SDL_SetError("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
        જો (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            પાછા SDL_SetError("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        જો (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            પાછા SDL_SetError("Couldn't get XRandR crtc info");
        }

        જો (crtc->mode == modedata->xrandr_mode) {
#ifdef X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->mode, crtc->width, crtc->height);
#endif
            status = Success;
            જાઓ freeInfo;
        }

        X11_XGrabServer(display);
        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, ખાલી, 0);
        જો (status != Success) {
            જાઓ ungrabServer;
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
        X11_XRRSetScreenSize(display, મૂળ_Window(display, data->screen),
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

        જો (status != Success) {
            પાછા SDL_SetError("X11_XRRSetCrtcConfig failed");
        }
    }
#નહીંતર
    (શૂન્ય)data;
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    પાછા true;
}

શૂન્ય X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_DisplayData *data = sdl_display->internal;

    rect->x = data->x;
    rect->y = data->y;
    rect->w = sdl_display->current_mode->w;
    rect->h = sdl_display->current_mode->h;
    પાછા true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    Atom _NET_WORKAREA;
    પૂર્ણાંક real_format;
    Atom real_type;
    unsigned long વસ્તુઓ_read = 0, વસ્તુઓ_ડાબું = 0;
    unsigned અક્ષર *propdata = ખાલી;
    bool result = false;

    જો (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        પાછા false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    પૂર્ણાંક status = X11_XGetWindowProperty(display, Default_મૂળ_Window(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &વસ્તુઓ_read,
                                    &વસ્તુઓ_ડાબું, &propdata);
    જો ((status == Success) && (વસ્તુઓ_read >= 4)) {
        અચલ long *p = (long *)propdata;
        અચલ SDL_Rect usable = { (પૂર્ણાંક)p[0], (પૂર્ણાંક)p[1], (પૂર્ણાંક)p[2], (પૂર્ણાંક)p[3] };
        result = true;
        જો (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    જો (propdata) {
        X11_XFree(propdata);
    }

    પાછા result;
}

#endif // SDL_VIDEO_DRIVER_X11
