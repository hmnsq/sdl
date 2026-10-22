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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "SDL_x11settings.h"
#அந்தர்பாவ "edid.h"
#அந்தர்பாவ "../../events/SDL_displayevents_c.h"
#அந்தர்பாவ "../SDL_pixels_c.h"

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

தசம X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    இரட்டை scale_factor = 0.0;

    // First use the forced scaling factor specified by the app/user
    மாறிலி எழுத்து *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_FACTOR);
    எனில் (hint && *hint) {
        இரட்டை மதிப்பு = SDL_atof(hint);
        எனில் (மதிப்பு >= 1.0f && மதிப்பு <= 10.0f) {
            scale_factor = மதிப்பு;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    எனில் (scale_factor <= 0.0) {
        முழு status, real_format;
        Atom real_type;
        Atom res_mgr;
        unsigned long பொருட்கள்_read, பொருட்கள்_இடது;
        எழுத்து *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        status = X11_XGetWindowProperty(display, வேர்_Window(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &பொருட்கள்_read, &பொருட்கள்_இடது,
                                        (unsigned எழுத்து **)&resource_manager);

        எனில் (status == Success && resource_manager) {
            owns_resource_manager = true;
        } இல்லையெனில் {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        எனில் (resource_manager) {
            XrmDatabase db;
            Xrm_மதிப்பு மதிப்பு;
            எழுத்து *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            எனில் (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &மதிப்பு)) {
                எனில் (மதிப்பு.addr && type && SDL_strcmp(type, "String") == 0) {
                    முழு dpi = SDL_atoi(மதிப்பு.addr);
                    scale_factor  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            எனில் (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    எனில் (scale_factor <= 0.0) {
        scale_factor = X11_Get_Xsettings_Client_Int_சாவி(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        எனில் (scale_factor <= 0.0) {
            முழு dpi = X11_Get_Xsettings_Client_Int_சாவி(client, "Xft/DPI", -1);
            எனில் (dpi > 0) {
                scale_factor = (இரட்டை) dpi / 1024.0;
                scale_factor /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    எனில் (scale_factor <= 0.0) {
        மாறிலி எழுத்து *scale_str = SDL_getenv("GDK_SCALE");
        எனில் (scale_str) {
            scale_factor = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    எனில் (scale_factor <= 0.0) {
        scale_factor = 1.0;
    }

    திரும்பு (தசம)scale_factor;
}

தசம X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    திரும்பு X11_GetGlobalContentScale(_this->internal->display, _this->internal->xsettings_data.xsettings);
}

நிலையான bool get_visualinfo(Display *display, முழு screen, XVisualInfo *vinfo)
{
    மாறிலி எழுத்து *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    முழு depth;

    // Look for an exact visual, if requested
    எனில் (visual_id && *visual_id) {
        XVisualInfo *vi, template;
        முழு nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(visual_id, வெற்று, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        எனில் (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            திரும்பு true;
        }
    }

    depth = DefaultDepth(display, screen);
    எனில் ((X11_UseDirectColorVisuals() &&
         X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
        திரும்பு true;
    }
    திரும்பு false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    முழு nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    எனில் (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        திரும்பு true;
    }
    திரும்பு false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    எனில் (vinfo->class == DirectColor || vinfo->class == TrueColor) {
        முழு bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_mask;
        Gmask = vinfo->visual->green_mask;
        Bmask = vinfo->visual->blue_mask;
        எனில் (vinfo->depth == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } இல்லையெனில் {
            Amask = 0;
        }

        bpp = vinfo->depth;
        எனில் (bpp == 24) {
            முழு i, n;
            XPixmap_Format_மதிப்புகள் *p = X11_XListPixmapFormats(display, &n);
            எனில் (p) {
                க்கு (i = 0; i < n; ++i) {
                    எனில் (p[i].depth == 24) {
                        bpp = p[i].bits_per_pixel;
                        நிறுத்து;
                    }
                }
                X11_XFree(p);
            }
        }

        திரும்பு SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    எனில் (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        தேர்வு (vinfo->depth) {
        நிலை 8:
            திரும்பு SDL_PIXELFORMAT_INDEX8;
        நிலை 4:
            எனில் (BitmapBitOrder(display) == LSBFirst) {
                திரும்பு SDL_PIXELFORMAT_INDEX4LSB;
            } இல்லையெனில் {
                திரும்பு SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        நிலை 1:
            எனில் (BitmapBitOrder(display) == LSBFirst) {
                திரும்பு SDL_PIXELFORMAT_INDEX1LSB;
            } இல்லையெனில் {
                திரும்பு SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    திரும்பு SDL_PIXELFORMAT_UNKNOWN;
}

நிலையான SDL_DisplayID X11_AddGenericDisplay(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    மாறிலி முழு default_screen = DefaultScreen(dpy);
    Screen *screen = ScreenOfDisplay(dpy, default_screen);
    முழு scanline_pad, n, i;
    SDL_DisplayModeData *modedata;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    XPixmap_Format_மதிப்புகள் *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    எனில் (!get_visualinfo(dpy, default_screen, &vinfo)) {
        திரும்பு SDL_SetError("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    எனில் (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        திரும்பு SDL_SetError("Palettized video modes are no longer supported");
    }

    SDL_zero(mode);
    mode.w = WidthOfScreen(screen);
    mode.h = HeightOfScreen(screen);
    mode.format = pixelformat;

    displaydata = (SDL_DisplayData *)SDL_calloc(1, அளவு(*displaydata));
    எனில் (!displaydata) {
        திரும்பு false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, அளவு(SDL_DisplayModeData));
    எனில் (!modedata) {
        SDL_free(displaydata);
        திரும்பு false;
    }
    mode.internal = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    எனில் (pixmapformats) {
        க்கு (i = 0; i < n; ++i) {
            எனில் (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                நிறுத்து;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (எழுத்து *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_mode = mode;
    display.internal = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    திரும்பு SDL_AddVideoDisplay(&display, send_event);
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR

நிலையான வெறுமை X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(வெற்று);
    எனில் (displays) {
        க்கு (முழு i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            மாறிலி SDL_DisplayData *displaydata = display->internal;
            எனில் (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

நிலையான bool CheckXRandR(Display *display, முழு *major, முழு *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ifdef XRANDR_DISABLED_BY_DEFAULT
    எனில் (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#endif
        திரும்பு false;
    }
#இல்லையெனில்
    எனில் (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#endif
        திரும்பு false;
    }
#endif // XRANDR_DISABLED_BY_DEFAULT

    எனில் (!SDL_X11_HAVE_XRANDR) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#endif
        திரும்பு false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    எனில் (!X11_XRRQueryVersion(display, major, minor)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#endif
        *major = *minor = 0;
        திரும்பு false;
    }
#ifdef X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#endif
    திரும்பு true;
}

#define XRANDR_ROTATION_இடது  (1 << 1)
#define XRANDR_ROTATION_வலது (1 << 3)

நிலையான வெறுமை CalculateXRandRRefreshRate(மாறிலி XRRModeInfo *info, முழு *numerator, முழு *denominator)
{
    unsigned முழு vTotal = info->vTotal;

    எனில் (info->modeFlags & RR_DoubleScan) {
        // doublescan doubles the number of lines
        vTotal *= 2;
    }

    எனில் (info->modeFlags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        vTotal /= 2;
    }

    எனில் (info->hTotal && vTotal) {
        *numerator = info->dotClock;
        *denominator = (info->hTotal * vTotal);
    } இல்லையெனில் {
        *numerator = 0;
        *denominator = 0;
    }
}

நிலையான bool SetXRandRModeInfo(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode modeID, SDL_DisplayMode *mode)
{
    முழு i;
    க்கு (i = 0; i < res->nmode; ++i) {
        மாறிலி XRRModeInfo *info = &res->modes[i];
        எனில் (info->id == modeID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtcTransformAttributes *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            எனில் (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            எனில் (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            எனில் (rotation & (XRANDR_ROTATION_இடது | XRANDR_ROTATION_வலது)) {
                mode->w = (info->height * scale_w + 0xffff) >> 16;
                mode->h = (info->width * scale_h + 0xffff) >> 16;
            } இல்லையெனில் {
                mode->w = (info->width * scale_w + 0xffff) >> 16;
                mode->h = (info->height * scale_h + 0xffff) >> 16;
            }
            CalculateXRandRRefreshRate(info, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
            mode->internal->xrandr_mode = modeID;
#ifdef X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (முழு)modeID,
                    mode->screen_w, mode->screen_h, mode->refresh_rate_numerator, mode->refresh_rate_denominator);
#endif
            திரும்பு true;
        }
    }
    திரும்பு false;
}

நிலையான bool Get_வேர்_Window_Cardinal_Property(Display *dpy, முழு screen, மாறிலி எழுத்து *name, Uint32 *மதிப்பு)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    எனில் (atom == None) {
        திரும்பு false;
    }

    முழு real_format;
    Atom real_type;
    unsigned long பொருட்கள்_read = 0, பொருட்கள்_இடது = 0;
    unsigned எழுத்து *propdata = வெற்று;
    முழு status;
    bool result = false;

    status = X11_XGetWindowProperty(dpy, வேர்_Window(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &பொருட்கள்_read, &பொருட்கள்_இடது, &propdata);
    எனில் (status == Success && propdata) {
        எனில் (real_type == XA_CARDINAL && பொருட்கள்_read > 0) {
            தேர்வு (real_format) {
            நிலை 8:
                *மதிப்பு = propdata[0];
                நிறுத்து;
            நிலை 16:
                *மதிப்பு = propdata[0] | (propdata[1] << 8);
                நிறுத்து;
            இயல்பு:
                *மதிப்பு = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                நிறுத்து;
            }
            result = true;
        }
        X11_XFree(propdata);
    }
    திரும்பு result;
}

நிலையான bool Get_வேர்_Window_Bool_Property(Display *dpy, முழு screen, மாறிலி எழுத்து *name, bool *மதிப்பு)
{
    Uint32 v;
    எனில் (Get_வேர்_Window_Cardinal_Property(dpy, screen, name, &v)) {
        *மதிப்பு = (v != 0);
        திரும்பு true;
    }
    திரும்பு false;
}

நிலையான bool Get_வேர்_Window_Float_Property(Display *dpy, முழு screen, மாறிலி எழுத்து *name, தசம *மதிப்பு)
{
    Uint32 v;
    எனில் (Get_வேர்_Window_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(மதிப்பு, &v, அளவு(v));
        திரும்பு true;
    }
    திரும்பு false;
}

நிலையான bool IsSteamDeckOLEDDisplay(மாறிலி MonitorInfo *info)
{
    எனில் (SDL_strcmp(info->manufacturer_code, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        எனில் (info->product_code == 0x3003 || info->product_code == 0x3004) {
            திரும்பு true;
        }
    }
    திரும்பு false;
}

நிலையான தசம GetGamescopeSDRWhiteLevel(Display *dpy, முழு screen, மாறிலி MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    எனில் (!dpy) {
        திரும்பு 0.0f;
    }

    தசம SDR_white_level = 0.0f;
    bool external_display = false;
    எனில் (Get_வேர்_Window_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_வேர்_Window_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } இல்லையெனில் எனில் (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (தசம)info->max_luminance / 3.0f;
    } இல்லையெனில் {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    திரும்பு SDR_white_level;
}

நிலையான MonitorInfo *GetMonitorInfo(Display *dpy, முழு screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = வெற்று;
    முழு real_format;
    Atom real_type;
    unsigned long பொருட்கள்_read = 0, பொருட்கள்_இடது = 0;
    unsigned எழுத்து *propdata = வெற்று;
    முழு status;

    *gamescope = false;

    எனில் (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_PATH = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        எனில் (GAMESCOPE_DISPLAY_EDID_PATH != None) {
            status = X11_XGetWindowProperty(dpy, வேர்_Window(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_PATH, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &பொருட்கள்_read, &பொருட்கள்_இடது, &propdata);
            எனில் (status == Success && propdata) {
                size_t size = 0;
                வெறுமை *data = SDL_LoadFile((எழுத்து *)propdata, &size);
                எனில் (data) {
                    info = decode_edid((uchar *)data, size);
                    எனில் (info) {
                        *gamescope = true;
                    }
                    SDL_free(data);
                }
            }
            எனில் (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    எனில் (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        எனில் (EDID != None) {
            முழு nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            க்கு (முழு i = 0; i < nprop; ++i) {
                எனில் (props[i] == EDID) {
                    status = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &பொருட்கள்_read, &பொருட்கள்_இடது, &propdata);
                    எனில் (status == Success && propdata) {
                        info = decode_edid(propdata, பொருட்கள்_read);
                    }
                    எனில் (propdata) {
                        X11_XFree(propdata);
                    }
                    நிறுத்து;
                }
            }

            எனில் (props) {
                X11_XFree(props);
            }
        }
    }

#ifdef X11MODES_DEBUG
    எனில் (info) {
        dump_monitor_info(info);
    }
#endif
    திரும்பு info;
}

நிலையான வெறுமை SetXRandRDisplayName(MonitorInfo *info, எழுத்து *name, size_t namelen, unsigned long widthmm, unsigned long heightmm)
{
    எனில் (info) {
        SDL_strlcpy(name, info->dsc_product_name, namelen);
    }

    முழு inches = (முழு)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    எனில் (*name && inches) {
        மாறிலி size_t len = SDL_strlen(name);
        (வெறுமை)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ifdef X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#endif
}

நிலையான bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, முழு screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, எழுத்து *display_name, size_t display_name_size)
{
    XRROutputInfo *output_info;
    முழு display_x, display_y;
    unsigned long display_mm_width, display_mm_height;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    SDL_DisplayModeData *modedata;
    RRMode modeID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_மதிப்புகள் *pixmapformats;
    முழு scanline_pad;
    முழு i, n;

    எனில் (!display || !display_name) {
        திரும்பு false; // invalid parameters
    }

    எனில் (!get_visualinfo(dpy, screen, &vinfo)) {
        திரும்பு false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    எனில் (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        திரும்பு false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    எனில் (pixmapformats) {
        க்கு (i = 0; i < n; i++) {
            எனில் (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                நிறுத்து;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    எனில் (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        திரும்பு false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_size);
    display_mm_width = output_info->mm_width;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    எனில் (!crtc) {
        திரும்பு false; // oh well, ignore it.
    }

    SDL_zero(mode);
    modeID = crtc->mode;
    mode.w = crtc->width;
    mode.h = crtc->height;
    mode.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_DisplayData *)SDL_calloc(1, அளவு(*displaydata));
    எனில் (!displaydata) {
        திரும்பு false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, அளவு(SDL_DisplayModeData));
    எனில் (!modedata) {
        SDL_free(displaydata);
        திரும்பு false;
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
    SDL_strlcpy(displaydata->connector_name, display_name, அளவு(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    SetXRandRModeInfo(dpy, res, output_crtc, modeID, &mode);
    SetXRandRDisplayName(info, display_name, display_name_size, display_mm_width, display_mm_height);

    SDL_zero(*display);
    எனில் (*display_name) {
        display->name = display_name;
    }
    display->desktop_mode = mode;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->internal = displaydata;

    எனில் (info) {
        தசம SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        எனில் (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } இல்லையெனில் {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ifdef X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#endif
        எனில் (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (தசம)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    திரும்பு true;
}

நிலையான bool X11_AddXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, முழு screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    எழுத்து display_name[128];

    எனில் (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, அளவு(display_name))) {
        திரும்பு true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    எனில் (displayID == 0) {
        திரும்பு false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    எனில் (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    திரும்பு true;
}


நிலையான bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, முழு screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    எழுத்து display_name[128];

    எனில் (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, அளவு(display_name))) {
        திரும்பு false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_SetDesktopDisplayMode(existing_display, &display.desktop_mode);

    // update bounds
    எனில் (existing_display->internal->x != display.internal->x ||
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

    திரும்பு true;
}

நிலையான XRRScreenResources *X11_GetScreenResources(Display *dpy, முழு screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, வேர்_Window(dpy, screen));
    எனில் (!res || res->noutput == 0) {
        எனில் (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, வேர்_Window(dpy, screen));
    }
    திரும்பு res;
}

வெறுமை X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    மாறிலி முழு screencount = Screen_மொத்தம்(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(வெற்று);
    எனில் (!displays) {
        திரும்பு;
    }

    க்கு (முழு screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        எனில் (!res) {
            தொடர்;
        }

        க்கு (முழு i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            மாறிலி SDL_DisplayData *displaydata = display->internal;
            எனில் (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

நிலையான வெறுமை X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    மாறிலி முழு screencount = Screen_மொத்தம்(dpy);
    முழு இலக்கம்_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&இலக்கம்_displays);
    எனில் (!displays) {
        திரும்பு;
    }

    க்கு (முழு screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        எனில் (!res) {
            தொடர்;
        }

        க்கு (முழு output = 0; output < res->noutput; output++) {
            க்கு (முழு i = 0; i < இலக்கம்_displays; ++i) {
                எனில் (!displays[i]) {
                    // We already removed this display from the list
                    தொடர்;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                மாறிலி SDL_DisplayData *displaydata = display->internal;
                எனில் (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    நிறுத்து;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    க்கு (முழு i = 0; i < இலக்கம்_displays; ++i) {
        எனில் (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            மாறிலி SDL_DisplayData *displaydata = display->internal;
            எனில் (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

நிலையான வெறுமை X11_HandleXRandROutputChange(SDL_VideoDevice *_this, மாறிலி XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = வெற்று;
    முழு i;

#எனில் 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (unsigned முழு) ev->output, (unsigned முழு) ev->crtc, (unsigned முழு) ev->mode, (unsigned முழு) ev->rotation, (unsigned முழு) ev->connection);
#endif

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(வெற்று);
    எனில் (displays) {
        க்கு (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            மாறிலி SDL_DisplayData *displaydata = thisdisplay->internal;
            எனில் (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                நிறுத்து;
            }
        }
        SDL_free(displays);
    }

    எனில் (ev->connection == RR_Disconnected) { // output is going away
        எனில் (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            எனில் (_this->இலக்கம்_displays == 1) {
                generic_display = X11_AddGenericDisplay(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            எனில் (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } இல்லையெனில் எனில் (ev->connection == RR_Connected) { // output is coming online
        எனில் (!display) {
            Display *dpy = ev->display;
            மாறிலி முழு screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            எனில் (res) {
                X11_AddXRandRDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

வெறுமை X11_HandleXRandREvent(SDL_VideoDevice *_this, மாறிலி XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_assert(xevent->type == (videodata->xrandr_event_base + RRNotify));

    தேர்வு (((மாறிலி XRRNotifyEvent *)xevent)->subtype) {
    நிலை RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (மாறிலி XRROutputChangeNotifyEvent *)xevent);
        நிறுத்து;
    இயல்பு:
        நிறுத்து;
    }
}

நிலையான வெறுமை X11_SortOutputsByPriorityHint(SDL_VideoDevice *_this)
{
    மாறிலி எழுத்து *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    எனில் (name_hint) {
        எழுத்து *saveptr;
        எழுத்து *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(அளவு(SDL_VideoDisplay *) * _this->இலக்கம்_displays);

        எனில் (str && sorted_list) {
            முழு sorted_index = 0;

            // Sort the requested displays to the front of the list.
            மாறிலி எழுத்து *token = SDL_strtok_r(str, ",", &saveptr);
            போது (token) {
                க்கு (முழு i = 0; i < _this->இலக்கம்_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    எனில் (d) {
                        SDL_DisplayData *data = d->internal;
                        எனில் (SDL_strcmp(token, data->connector_name) == 0) {
                            sorted_list[sorted_index++] = d;
                            _this->displays[i] = வெற்று;
                            நிறுத்து;
                        }
                    }
                }

                token = SDL_strtok_r(வெற்று, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            க்கு (முழு i = 0; i < _this->இலக்கம்_displays; ++i) {
                எனில் (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, அளவு(SDL_VideoDisplay *) * _this->இலக்கம்_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

நிலையான bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    மாறிலி முழு screencount = Screen_மொத்தம்(dpy);
    மாறிலி முழு default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, வேர்_Window(dpy, default_screen));
    முழு xrandr_error_base = 0;
    முழு looking_for_primary;
    முழு output;
    முழு screen;

    எனில் (!X11_XRRQueryExtension(dpy, &data->xrandr_event_base, &xrandr_error_base)) {
        திரும்பு SDL_SetError("XRRQueryExtension failed");
    }

    க்கு (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        க்கு (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            எனில் (looking_for_primary && (screen != default_screen)) {
                தொடர்;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            எனில் (!res) {
                தொடர்;
            }

            க்கு (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                எனில் ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    தொடர்;
                }
                எனில் (!X11_AddXRandRDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    நிறுத்து;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_உள்ளீடு(dpy, வேர்_Window(dpy, screen), RROutputChangeNotifyMask);
        }
    }

    எனில் (_this->இலக்கம்_displays == 0) {
        திரும்பு SDL_SetError("No available displays");
    }

    X11_SortOutputsByPriorityHint(_this);

    திரும்பு true;
}
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
நிலையான bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    எனில் (X11_AddGenericDisplay(_this, true) == 0) {
        திரும்பு false;
    }
    திரும்பு true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_VideoData *data = _this->internal;
        முழு xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        எனில் (CheckXRandR(data->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            திரும்பு true;
        }
    }
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    திரும்பு X11_InitModes_StdXlib(_this);
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

    எனில் (data->use_xrandr) {
        Display *display = _this->internal->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, வேர்_Window(display, data->screen));
        எனில் (res) {
            SDL_DisplayModeData *modedata;
            XRROutputInfo *output_info;
            முழு i;

            output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
            எனில் (output_info && output_info->connection != RR_Disconnected) {
                க்கு (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_DisplayModeData *)SDL_calloc(1, அளவு(SDL_DisplayModeData));
                    எனில் (!modedata) {
                        தொடர்;
                    }
                    mode.internal = modedata;

                    எனில் (!SetXRandRModeInfo(display, res, output_info->crtc, output_info->modes[i], &mode) ||
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
    திரும்பு true;
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
நிலையான முழு (*PreXRRSetScreenSizeErrorHandler)(Display *, XErrorEvent *) = வெற்று;
நிலையான முழு SDL_XRRSetScreenSizeErrHandler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    எனில் ((e->error_code == BadMatch) || (e->error_code == Bad_மதிப்பு)) {
        திரும்பு 0;
    }

    திரும்பு PreXRRSetScreenSizeErrorHandler(d, e);
}
#endif

bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *data = sdl_display->internal;

    viddata->last_mode_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    எனில் (!viddata->is_xwayland) {
        எனில் (sdl_display->current_mode != mode) {
            data->mode_switch_deadline_ns = SDL_GetTicksNS() + MODE_SWITCH_TIMEOUT_NS;
        } இல்லையெனில் {
            data->mode_switch_deadline_ns = 0;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    எனில் (data->use_xrandr) {
        Display *display = viddata->display;
        SDL_DisplayModeData *modedata = mode->internal;
        முழு mm_width, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        Status status;

        res = X11_XRRGetScreenResources(display, வேர்_Window(display, data->screen));
        எனில் (!res) {
            திரும்பு SDL_SetError("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
        எனில் (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            திரும்பு SDL_SetError("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        எனில் (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            திரும்பு SDL_SetError("Couldn't get XRandR crtc info");
        }

        எனில் (crtc->mode == modedata->xrandr_mode) {
#ifdef X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->mode, crtc->width, crtc->height);
#endif
            status = Success;
            செல் freeInfo;
        }

        X11_XGrabServer(display);
        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, வெற்று, 0);
        எனில் (status != Success) {
            செல் ungrabServer;
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
        X11_XRRSetScreenSize(display, வேர்_Window(display, data->screen),
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

        எனில் (status != Success) {
            திரும்பு SDL_SetError("X11_XRRSetCrtcConfig failed");
        }
    }
#இல்லையெனில்
    (வெறுமை)data;
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    திரும்பு true;
}

வெறுமை X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_DisplayData *data = sdl_display->internal;

    rect->x = data->x;
    rect->y = data->y;
    rect->w = sdl_display->current_mode->w;
    rect->h = sdl_display->current_mode->h;
    திரும்பு true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    Atom _NET_WORKAREA;
    முழு real_format;
    Atom real_type;
    unsigned long பொருட்கள்_read = 0, பொருட்கள்_இடது = 0;
    unsigned எழுத்து *propdata = வெற்று;
    bool result = false;

    எனில் (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        திரும்பு false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    முழு status = X11_XGetWindowProperty(display, Default_வேர்_Window(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &பொருட்கள்_read,
                                    &பொருட்கள்_இடது, &propdata);
    எனில் ((status == Success) && (பொருட்கள்_read >= 4)) {
        மாறிலி long *p = (long *)propdata;
        மாறிலி SDL_Rect usable = { (முழு)p[0], (முழு)p[1], (முழு)p[2], (முழு)p[3] };
        result = true;
        எனில் (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    எனில் (propdata) {
        X11_XFree(propdata);
    }

    திரும்பு result;
}

#endif // SDL_VIDEO_DRIVER_X11
