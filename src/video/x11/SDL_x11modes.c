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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "SDL_x11settings.h"
#അന്തര്ഭാവ "edid.h"
#അന്തര്ഭാവ "../../events/SDL_displayevents_c.h"
#അന്തര്ഭാവ "../SDL_pixels_c.h"

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

ദശാംശം X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    ഇരട്ട scale_factor = 0.0;

    // First use the forced scaling factor specified by the app/user
    സ്ഥിരം അക്ഷരം *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_FACTOR);
    എങ്കിൽ (hint && *hint) {
        ഇരട്ട മൂല്യം = SDL_atof(hint);
        എങ്കിൽ (മൂല്യം >= 1.0f && മൂല്യം <= 10.0f) {
            scale_factor = മൂല്യം;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    എങ്കിൽ (scale_factor <= 0.0) {
        പൂർണ്ണസംഖ്യ status, real_format;
        Atom real_type;
        Atom res_mgr;
        unsigned long ഇനങ്ങൾ_read, ഇനങ്ങൾ_ഇടത്;
        അക്ഷരം *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        status = X11_XGetWindowProperty(display, വേര്_Window(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &ഇനങ്ങൾ_read, &ഇനങ്ങൾ_ഇടത്,
                                        (unsigned അക്ഷരം **)&resource_manager);

        എങ്കിൽ (status == Success && resource_manager) {
            owns_resource_manager = true;
        } അല്ലെങ്കിൽ {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        എങ്കിൽ (resource_manager) {
            XrmDatabase db;
            Xrm_മൂല്യം മൂല്യം;
            അക്ഷരം *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            എങ്കിൽ (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &മൂല്യം)) {
                എങ്കിൽ (മൂല്യം.addr && type && SDL_strcmp(type, "String") == 0) {
                    പൂർണ്ണസംഖ്യ dpi = SDL_atoi(മൂല്യം.addr);
                    scale_factor  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            എങ്കിൽ (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    എങ്കിൽ (scale_factor <= 0.0) {
        scale_factor = X11_Get_Xsettings_Client_Int_താക്കോൽ(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        എങ്കിൽ (scale_factor <= 0.0) {
            പൂർണ്ണസംഖ്യ dpi = X11_Get_Xsettings_Client_Int_താക്കോൽ(client, "Xft/DPI", -1);
            എങ്കിൽ (dpi > 0) {
                scale_factor = (ഇരട്ട) dpi / 1024.0;
                scale_factor /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    എങ്കിൽ (scale_factor <= 0.0) {
        സ്ഥിരം അക്ഷരം *scale_str = SDL_getenv("GDK_SCALE");
        എങ്കിൽ (scale_str) {
            scale_factor = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    എങ്കിൽ (scale_factor <= 0.0) {
        scale_factor = 1.0;
    }

    തിരികെ (ദശാംശം)scale_factor;
}

ദശാംശം X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    തിരികെ X11_GetGlobalContentScale(_this->internal->display, _this->internal->xsettings_data.xsettings);
}

സ്ഥിതം bool get_visualinfo(Display *display, പൂർണ്ണസംഖ്യ screen, XVisualInfo *vinfo)
{
    സ്ഥിരം അക്ഷരം *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    പൂർണ്ണസംഖ്യ depth;

    // Look for an exact visual, if requested
    എങ്കിൽ (visual_id && *visual_id) {
        XVisualInfo *vi, template;
        പൂർണ്ണസംഖ്യ nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(visual_id, ശൂന്യ, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        എങ്കിൽ (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            തിരികെ true;
        }
    }

    depth = DefaultDepth(display, screen);
    എങ്കിൽ ((X11_UseDirectColorVisuals() &&
         X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
        തിരികെ true;
    }
    തിരികെ false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    പൂർണ്ണസംഖ്യ nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    എങ്കിൽ (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        തിരികെ true;
    }
    തിരികെ false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    എങ്കിൽ (vinfo->class == DirectColor || vinfo->class == TrueColor) {
        പൂർണ്ണസംഖ്യ bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_mask;
        Gmask = vinfo->visual->green_mask;
        Bmask = vinfo->visual->blue_mask;
        എങ്കിൽ (vinfo->depth == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } അല്ലെങ്കിൽ {
            Amask = 0;
        }

        bpp = vinfo->depth;
        എങ്കിൽ (bpp == 24) {
            പൂർണ്ണസംഖ്യ i, n;
            XPixmap_Format_മൂല്യങ്ങൾ *p = X11_XListPixmapFormats(display, &n);
            എങ്കിൽ (p) {
                വേണ്ടി (i = 0; i < n; ++i) {
                    എങ്കിൽ (p[i].depth == 24) {
                        bpp = p[i].bits_per_pixel;
                        നിർത്തുക;
                    }
                }
                X11_XFree(p);
            }
        }

        തിരികെ SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    എങ്കിൽ (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        തിരഞ്ഞെടുപ്പ് (vinfo->depth) {
        അവസ്ഥ 8:
            തിരികെ SDL_PIXELFORMAT_INDEX8;
        അവസ്ഥ 4:
            എങ്കിൽ (BitmapBitOrder(display) == LSBFirst) {
                തിരികെ SDL_PIXELFORMAT_INDEX4LSB;
            } അല്ലെങ്കിൽ {
                തിരികെ SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        അവസ്ഥ 1:
            എങ്കിൽ (BitmapBitOrder(display) == LSBFirst) {
                തിരികെ SDL_PIXELFORMAT_INDEX1LSB;
            } അല്ലെങ്കിൽ {
                തിരികെ SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    തിരികെ SDL_PIXELFORMAT_UNKNOWN;
}

സ്ഥിതം SDL_DisplayID X11_AddGenericDisplay(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    സ്ഥിരം പൂർണ്ണസംഖ്യ default_screen = DefaultScreen(dpy);
    Screen *screen = ScreenOfDisplay(dpy, default_screen);
    പൂർണ്ണസംഖ്യ scanline_pad, n, i;
    SDL_DisplayModeData *modedata;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    XPixmap_Format_മൂല്യങ്ങൾ *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    എങ്കിൽ (!get_visualinfo(dpy, default_screen, &vinfo)) {
        തിരികെ SDL_SetError("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    എങ്കിൽ (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        തിരികെ SDL_SetError("Palettized video modes are no longer supported");
    }

    SDL_zero(mode);
    mode.w = WidthOfScreen(screen);
    mode.h = HeightOfScreen(screen);
    mode.format = pixelformat;

    displaydata = (SDL_DisplayData *)SDL_calloc(1, വലുപ്പം(*displaydata));
    എങ്കിൽ (!displaydata) {
        തിരികെ false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, വലുപ്പം(SDL_DisplayModeData));
    എങ്കിൽ (!modedata) {
        SDL_free(displaydata);
        തിരികെ false;
    }
    mode.internal = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    എങ്കിൽ (pixmapformats) {
        വേണ്ടി (i = 0; i < n; ++i) {
            എങ്കിൽ (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                നിർത്തുക;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (അക്ഷരം *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_mode = mode;
    display.internal = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    തിരികെ SDL_AddVideoDisplay(&display, send_event);
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR

സ്ഥിതം ശൂന്യം X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(ശൂന്യ);
    എങ്കിൽ (displays) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            സ്ഥിരം SDL_DisplayData *displaydata = display->internal;
            എങ്കിൽ (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

സ്ഥിതം bool CheckXRandR(Display *display, പൂർണ്ണസംഖ്യ *major, പൂർണ്ണസംഖ്യ *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ifdef XRANDR_DISABLED_BY_DEFAULT
    എങ്കിൽ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#endif
        തിരികെ false;
    }
#അല്ലെങ്കിൽ
    എങ്കിൽ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#endif
        തിരികെ false;
    }
#endif // XRANDR_DISABLED_BY_DEFAULT

    എങ്കിൽ (!SDL_X11_HAVE_XRANDR) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#endif
        തിരികെ false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    എങ്കിൽ (!X11_XRRQueryVersion(display, major, minor)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#endif
        *major = *minor = 0;
        തിരികെ false;
    }
#ifdef X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#endif
    തിരികെ true;
}

#define XRANDR_ROTATION_ഇടത്  (1 << 1)
#define XRANDR_ROTATION_വലത് (1 << 3)

സ്ഥിതം ശൂന്യം CalculateXRandRRefreshRate(സ്ഥിരം XRRModeInfo *info, പൂർണ്ണസംഖ്യ *numerator, പൂർണ്ണസംഖ്യ *denominator)
{
    unsigned പൂർണ്ണസംഖ്യ vTotal = info->vTotal;

    എങ്കിൽ (info->modeFlags & RR_DoubleScan) {
        // doublescan doubles the number of lines
        vTotal *= 2;
    }

    എങ്കിൽ (info->modeFlags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        vTotal /= 2;
    }

    എങ്കിൽ (info->hTotal && vTotal) {
        *numerator = info->dotClock;
        *denominator = (info->hTotal * vTotal);
    } അല്ലെങ്കിൽ {
        *numerator = 0;
        *denominator = 0;
    }
}

സ്ഥിതം bool SetXRandRModeInfo(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode modeID, SDL_DisplayMode *mode)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < res->nmode; ++i) {
        സ്ഥിരം XRRModeInfo *info = &res->modes[i];
        എങ്കിൽ (info->id == modeID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtcTransformAttributes *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            എങ്കിൽ (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            എങ്കിൽ (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            എങ്കിൽ (rotation & (XRANDR_ROTATION_ഇടത് | XRANDR_ROTATION_വലത്)) {
                mode->w = (info->height * scale_w + 0xffff) >> 16;
                mode->h = (info->width * scale_h + 0xffff) >> 16;
            } അല്ലെങ്കിൽ {
                mode->w = (info->width * scale_w + 0xffff) >> 16;
                mode->h = (info->height * scale_h + 0xffff) >> 16;
            }
            CalculateXRandRRefreshRate(info, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
            mode->internal->xrandr_mode = modeID;
#ifdef X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (പൂർണ്ണസംഖ്യ)modeID,
                    mode->screen_w, mode->screen_h, mode->refresh_rate_numerator, mode->refresh_rate_denominator);
#endif
            തിരികെ true;
        }
    }
    തിരികെ false;
}

സ്ഥിതം bool Get_വേര്_Window_Cardinal_Property(Display *dpy, പൂർണ്ണസംഖ്യ screen, സ്ഥിരം അക്ഷരം *name, Uint32 *മൂല്യം)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    എങ്കിൽ (atom == None) {
        തിരികെ false;
    }

    പൂർണ്ണസംഖ്യ real_format;
    Atom real_type;
    unsigned long ഇനങ്ങൾ_read = 0, ഇനങ്ങൾ_ഇടത് = 0;
    unsigned അക്ഷരം *propdata = ശൂന്യ;
    പൂർണ്ണസംഖ്യ status;
    bool result = false;

    status = X11_XGetWindowProperty(dpy, വേര്_Window(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &ഇനങ്ങൾ_read, &ഇനങ്ങൾ_ഇടത്, &propdata);
    എങ്കിൽ (status == Success && propdata) {
        എങ്കിൽ (real_type == XA_CARDINAL && ഇനങ്ങൾ_read > 0) {
            തിരഞ്ഞെടുപ്പ് (real_format) {
            അവസ്ഥ 8:
                *മൂല്യം = propdata[0];
                നിർത്തുക;
            അവസ്ഥ 16:
                *മൂല്യം = propdata[0] | (propdata[1] << 8);
                നിർത്തുക;
            സ്ഥിരസ്ഥിതി:
                *മൂല്യം = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                നിർത്തുക;
            }
            result = true;
        }
        X11_XFree(propdata);
    }
    തിരികെ result;
}

സ്ഥിതം bool Get_വേര്_Window_Bool_Property(Display *dpy, പൂർണ്ണസംഖ്യ screen, സ്ഥിരം അക്ഷരം *name, bool *മൂല്യം)
{
    Uint32 v;
    എങ്കിൽ (Get_വേര്_Window_Cardinal_Property(dpy, screen, name, &v)) {
        *മൂല്യം = (v != 0);
        തിരികെ true;
    }
    തിരികെ false;
}

സ്ഥിതം bool Get_വേര്_Window_Float_Property(Display *dpy, പൂർണ്ണസംഖ്യ screen, സ്ഥിരം അക്ഷരം *name, ദശാംശം *മൂല്യം)
{
    Uint32 v;
    എങ്കിൽ (Get_വേര്_Window_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(മൂല്യം, &v, വലുപ്പം(v));
        തിരികെ true;
    }
    തിരികെ false;
}

സ്ഥിതം bool IsSteamDeckOLEDDisplay(സ്ഥിരം MonitorInfo *info)
{
    എങ്കിൽ (SDL_strcmp(info->manufacturer_code, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        എങ്കിൽ (info->product_code == 0x3003 || info->product_code == 0x3004) {
            തിരികെ true;
        }
    }
    തിരികെ false;
}

സ്ഥിതം ദശാംശം GetGamescopeSDRWhiteLevel(Display *dpy, പൂർണ്ണസംഖ്യ screen, സ്ഥിരം MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    എങ്കിൽ (!dpy) {
        തിരികെ 0.0f;
    }

    ദശാംശം SDR_white_level = 0.0f;
    bool external_display = false;
    എങ്കിൽ (Get_വേര്_Window_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_വേര്_Window_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } അല്ലെങ്കിൽ എങ്കിൽ (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (ദശാംശം)info->max_luminance / 3.0f;
    } അല്ലെങ്കിൽ {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    തിരികെ SDR_white_level;
}

സ്ഥിതം MonitorInfo *GetMonitorInfo(Display *dpy, പൂർണ്ണസംഖ്യ screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = ശൂന്യ;
    പൂർണ്ണസംഖ്യ real_format;
    Atom real_type;
    unsigned long ഇനങ്ങൾ_read = 0, ഇനങ്ങൾ_ഇടത് = 0;
    unsigned അക്ഷരം *propdata = ശൂന്യ;
    പൂർണ്ണസംഖ്യ status;

    *gamescope = false;

    എങ്കിൽ (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_PATH = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        എങ്കിൽ (GAMESCOPE_DISPLAY_EDID_PATH != None) {
            status = X11_XGetWindowProperty(dpy, വേര്_Window(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_PATH, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &ഇനങ്ങൾ_read, &ഇനങ്ങൾ_ഇടത്, &propdata);
            എങ്കിൽ (status == Success && propdata) {
                size_t size = 0;
                ശൂന്യം *data = SDL_LoadFile((അക്ഷരം *)propdata, &size);
                എങ്കിൽ (data) {
                    info = decode_edid((uchar *)data, size);
                    എങ്കിൽ (info) {
                        *gamescope = true;
                    }
                    SDL_free(data);
                }
            }
            എങ്കിൽ (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    എങ്കിൽ (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        എങ്കിൽ (EDID != None) {
            പൂർണ്ണസംഖ്യ nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < nprop; ++i) {
                എങ്കിൽ (props[i] == EDID) {
                    status = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &ഇനങ്ങൾ_read, &ഇനങ്ങൾ_ഇടത്, &propdata);
                    എങ്കിൽ (status == Success && propdata) {
                        info = decode_edid(propdata, ഇനങ്ങൾ_read);
                    }
                    എങ്കിൽ (propdata) {
                        X11_XFree(propdata);
                    }
                    നിർത്തുക;
                }
            }

            എങ്കിൽ (props) {
                X11_XFree(props);
            }
        }
    }

#ifdef X11MODES_DEBUG
    എങ്കിൽ (info) {
        dump_monitor_info(info);
    }
#endif
    തിരികെ info;
}

സ്ഥിതം ശൂന്യം SetXRandRDisplayName(MonitorInfo *info, അക്ഷരം *name, size_t namelen, unsigned long widthmm, unsigned long heightmm)
{
    എങ്കിൽ (info) {
        SDL_strlcpy(name, info->dsc_product_name, namelen);
    }

    പൂർണ്ണസംഖ്യ inches = (പൂർണ്ണസംഖ്യ)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    എങ്കിൽ (*name && inches) {
        സ്ഥിരം size_t len = SDL_strlen(name);
        (ശൂന്യം)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ifdef X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#endif
}

സ്ഥിതം bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, പൂർണ്ണസംഖ്യ screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, അക്ഷരം *display_name, size_t display_name_size)
{
    XRROutputInfo *output_info;
    പൂർണ്ണസംഖ്യ display_x, display_y;
    unsigned long display_mm_width, display_mm_height;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    SDL_DisplayModeData *modedata;
    RRMode modeID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_മൂല്യങ്ങൾ *pixmapformats;
    പൂർണ്ണസംഖ്യ scanline_pad;
    പൂർണ്ണസംഖ്യ i, n;

    എങ്കിൽ (!display || !display_name) {
        തിരികെ false; // invalid parameters
    }

    എങ്കിൽ (!get_visualinfo(dpy, screen, &vinfo)) {
        തിരികെ false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    എങ്കിൽ (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        തിരികെ false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    എങ്കിൽ (pixmapformats) {
        വേണ്ടി (i = 0; i < n; i++) {
            എങ്കിൽ (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                നിർത്തുക;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    എങ്കിൽ (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        തിരികെ false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_size);
    display_mm_width = output_info->mm_width;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    എങ്കിൽ (!crtc) {
        തിരികെ false; // oh well, ignore it.
    }

    SDL_zero(mode);
    modeID = crtc->mode;
    mode.w = crtc->width;
    mode.h = crtc->height;
    mode.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_DisplayData *)SDL_calloc(1, വലുപ്പം(*displaydata));
    എങ്കിൽ (!displaydata) {
        തിരികെ false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, വലുപ്പം(SDL_DisplayModeData));
    എങ്കിൽ (!modedata) {
        SDL_free(displaydata);
        തിരികെ false;
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
    SDL_strlcpy(displaydata->connector_name, display_name, വലുപ്പം(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    SetXRandRModeInfo(dpy, res, output_crtc, modeID, &mode);
    SetXRandRDisplayName(info, display_name, display_name_size, display_mm_width, display_mm_height);

    SDL_zero(*display);
    എങ്കിൽ (*display_name) {
        display->name = display_name;
    }
    display->desktop_mode = mode;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->internal = displaydata;

    എങ്കിൽ (info) {
        ദശാംശം SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        എങ്കിൽ (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } അല്ലെങ്കിൽ {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ifdef X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#endif
        എങ്കിൽ (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (ദശാംശം)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    തിരികെ true;
}

സ്ഥിതം bool X11_AddXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, പൂർണ്ണസംഖ്യ screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    അക്ഷരം display_name[128];

    എങ്കിൽ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, വലുപ്പം(display_name))) {
        തിരികെ true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    എങ്കിൽ (displayID == 0) {
        തിരികെ false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    എങ്കിൽ (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    തിരികെ true;
}


സ്ഥിതം bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, പൂർണ്ണസംഖ്യ screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    അക്ഷരം display_name[128];

    എങ്കിൽ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, വലുപ്പം(display_name))) {
        തിരികെ false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_SetDesktopDisplayMode(existing_display, &display.desktop_mode);

    // update bounds
    എങ്കിൽ (existing_display->internal->x != display.internal->x ||
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

    തിരികെ true;
}

സ്ഥിതം XRRScreenResources *X11_GetScreenResources(Display *dpy, പൂർണ്ണസംഖ്യ screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, വേര്_Window(dpy, screen));
    എങ്കിൽ (!res || res->noutput == 0) {
        എങ്കിൽ (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, വേര്_Window(dpy, screen));
    }
    തിരികെ res;
}

ശൂന്യം X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    സ്ഥിരം പൂർണ്ണസംഖ്യ screencount = Screen_എണ്ണം(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(ശൂന്യ);
    എങ്കിൽ (!displays) {
        തിരികെ;
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        എങ്കിൽ (!res) {
            തുടരുക;
        }

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            സ്ഥിരം SDL_DisplayData *displaydata = display->internal;
            എങ്കിൽ (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

സ്ഥിതം ശൂന്യം X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    സ്ഥിരം പൂർണ്ണസംഖ്യ screencount = Screen_എണ്ണം(dpy);
    പൂർണ്ണസംഖ്യ അക്കം_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&അക്കം_displays);
    എങ്കിൽ (!displays) {
        തിരികെ;
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        എങ്കിൽ (!res) {
            തുടരുക;
        }

        വേണ്ടി (പൂർണ്ണസംഖ്യ output = 0; output < res->noutput; output++) {
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < അക്കം_displays; ++i) {
                എങ്കിൽ (!displays[i]) {
                    // We already removed this display from the list
                    തുടരുക;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                സ്ഥിരം SDL_DisplayData *displaydata = display->internal;
                എങ്കിൽ (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    നിർത്തുക;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < അക്കം_displays; ++i) {
        എങ്കിൽ (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            സ്ഥിരം SDL_DisplayData *displaydata = display->internal;
            എങ്കിൽ (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

സ്ഥിതം ശൂന്യം X11_HandleXRandROutputChange(SDL_VideoDevice *_this, സ്ഥിരം XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = ശൂന്യ;
    പൂർണ്ണസംഖ്യ i;

#എങ്കിൽ 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (unsigned പൂർണ്ണസംഖ്യ) ev->output, (unsigned പൂർണ്ണസംഖ്യ) ev->crtc, (unsigned പൂർണ്ണസംഖ്യ) ev->mode, (unsigned പൂർണ്ണസംഖ്യ) ev->rotation, (unsigned പൂർണ്ണസംഖ്യ) ev->connection);
#endif

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(ശൂന്യ);
    എങ്കിൽ (displays) {
        വേണ്ടി (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            സ്ഥിരം SDL_DisplayData *displaydata = thisdisplay->internal;
            എങ്കിൽ (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                നിർത്തുക;
            }
        }
        SDL_free(displays);
    }

    എങ്കിൽ (ev->connection == RR_Disconnected) { // output is going away
        എങ്കിൽ (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            എങ്കിൽ (_this->അക്കം_displays == 1) {
                generic_display = X11_AddGenericDisplay(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            എങ്കിൽ (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } അല്ലെങ്കിൽ എങ്കിൽ (ev->connection == RR_Connected) { // output is coming online
        എങ്കിൽ (!display) {
            Display *dpy = ev->display;
            സ്ഥിരം പൂർണ്ണസംഖ്യ screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            എങ്കിൽ (res) {
                X11_AddXRandRDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

ശൂന്യം X11_HandleXRandREvent(SDL_VideoDevice *_this, സ്ഥിരം XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_assert(xevent->type == (videodata->xrandr_event_base + RRNotify));

    തിരഞ്ഞെടുപ്പ് (((സ്ഥിരം XRRNotifyEvent *)xevent)->subtype) {
    അവസ്ഥ RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (സ്ഥിരം XRROutputChangeNotifyEvent *)xevent);
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }
}

സ്ഥിതം ശൂന്യം X11_SortOutputsByPriorityHint(SDL_VideoDevice *_this)
{
    സ്ഥിരം അക്ഷരം *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    എങ്കിൽ (name_hint) {
        അക്ഷരം *saveptr;
        അക്ഷരം *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(വലുപ്പം(SDL_VideoDisplay *) * _this->അക്കം_displays);

        എങ്കിൽ (str && sorted_list) {
            പൂർണ്ണസംഖ്യ sorted_index = 0;

            // Sort the requested displays to the front of the list.
            സ്ഥിരം അക്ഷരം *token = SDL_strtok_r(str, ",", &saveptr);
            ആകുമ്പോൾ (token) {
                വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < _this->അക്കം_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    എങ്കിൽ (d) {
                        SDL_DisplayData *data = d->internal;
                        എങ്കിൽ (SDL_strcmp(token, data->connector_name) == 0) {
                            sorted_list[sorted_index++] = d;
                            _this->displays[i] = ശൂന്യ;
                            നിർത്തുക;
                        }
                    }
                }

                token = SDL_strtok_r(ശൂന്യ, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < _this->അക്കം_displays; ++i) {
                എങ്കിൽ (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, വലുപ്പം(SDL_VideoDisplay *) * _this->അക്കം_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

സ്ഥിതം bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    സ്ഥിരം പൂർണ്ണസംഖ്യ screencount = Screen_എണ്ണം(dpy);
    സ്ഥിരം പൂർണ്ണസംഖ്യ default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, വേര്_Window(dpy, default_screen));
    പൂർണ്ണസംഖ്യ xrandr_error_base = 0;
    പൂർണ്ണസംഖ്യ looking_for_primary;
    പൂർണ്ണസംഖ്യ output;
    പൂർണ്ണസംഖ്യ screen;

    എങ്കിൽ (!X11_XRRQueryExtension(dpy, &data->xrandr_event_base, &xrandr_error_base)) {
        തിരികെ SDL_SetError("XRRQueryExtension failed");
    }

    വേണ്ടി (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        വേണ്ടി (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            എങ്കിൽ (looking_for_primary && (screen != default_screen)) {
                തുടരുക;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            എങ്കിൽ (!res) {
                തുടരുക;
            }

            വേണ്ടി (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                എങ്കിൽ ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    തുടരുക;
                }
                എങ്കിൽ (!X11_AddXRandRDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    നിർത്തുക;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_നിവേശം(dpy, വേര്_Window(dpy, screen), RROutputChangeNotifyMask);
        }
    }

    എങ്കിൽ (_this->അക്കം_displays == 0) {
        തിരികെ SDL_SetError("No available displays");
    }

    X11_SortOutputsByPriorityHint(_this);

    തിരികെ true;
}
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
സ്ഥിതം bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    എങ്കിൽ (X11_AddGenericDisplay(_this, true) == 0) {
        തിരികെ false;
    }
    തിരികെ true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_VideoData *data = _this->internal;
        പൂർണ്ണസംഖ്യ xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        എങ്കിൽ (CheckXRandR(data->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            തിരികെ true;
        }
    }
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    തിരികെ X11_InitModes_StdXlib(_this);
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

    എങ്കിൽ (data->use_xrandr) {
        Display *display = _this->internal->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, വേര്_Window(display, data->screen));
        എങ്കിൽ (res) {
            SDL_DisplayModeData *modedata;
            XRROutputInfo *output_info;
            പൂർണ്ണസംഖ്യ i;

            output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
            എങ്കിൽ (output_info && output_info->connection != RR_Disconnected) {
                വേണ്ടി (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_DisplayModeData *)SDL_calloc(1, വലുപ്പം(SDL_DisplayModeData));
                    എങ്കിൽ (!modedata) {
                        തുടരുക;
                    }
                    mode.internal = modedata;

                    എങ്കിൽ (!SetXRandRModeInfo(display, res, output_info->crtc, output_info->modes[i], &mode) ||
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
    തിരികെ true;
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
സ്ഥിതം പൂർണ്ണസംഖ്യ (*PreXRRSetScreenSizeErrorHandler)(Display *, XErrorEvent *) = ശൂന്യ;
സ്ഥിതം പൂർണ്ണസംഖ്യ SDL_XRRSetScreenSizeErrHandler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    എങ്കിൽ ((e->error_code == BadMatch) || (e->error_code == Bad_മൂല്യം)) {
        തിരികെ 0;
    }

    തിരികെ PreXRRSetScreenSizeErrorHandler(d, e);
}
#endif

bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *data = sdl_display->internal;

    viddata->last_mode_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    എങ്കിൽ (!viddata->is_xwayland) {
        എങ്കിൽ (sdl_display->current_mode != mode) {
            data->mode_switch_deadline_ns = SDL_GetTicksNS() + MODE_SWITCH_TIMEOUT_NS;
        } അല്ലെങ്കിൽ {
            data->mode_switch_deadline_ns = 0;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    എങ്കിൽ (data->use_xrandr) {
        Display *display = viddata->display;
        SDL_DisplayModeData *modedata = mode->internal;
        പൂർണ്ണസംഖ്യ mm_width, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        Status status;

        res = X11_XRRGetScreenResources(display, വേര്_Window(display, data->screen));
        എങ്കിൽ (!res) {
            തിരികെ SDL_SetError("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
        എങ്കിൽ (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            തിരികെ SDL_SetError("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        എങ്കിൽ (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            തിരികെ SDL_SetError("Couldn't get XRandR crtc info");
        }

        എങ്കിൽ (crtc->mode == modedata->xrandr_mode) {
#ifdef X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->mode, crtc->width, crtc->height);
#endif
            status = Success;
            പോകുക freeInfo;
        }

        X11_XGrabServer(display);
        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, ശൂന്യ, 0);
        എങ്കിൽ (status != Success) {
            പോകുക ungrabServer;
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
        X11_XRRSetScreenSize(display, വേര്_Window(display, data->screen),
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

        എങ്കിൽ (status != Success) {
            തിരികെ SDL_SetError("X11_XRRSetCrtcConfig failed");
        }
    }
#അല്ലെങ്കിൽ
    (ശൂന്യം)data;
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    തിരികെ true;
}

ശൂന്യം X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_DisplayData *data = sdl_display->internal;

    rect->x = data->x;
    rect->y = data->y;
    rect->w = sdl_display->current_mode->w;
    rect->h = sdl_display->current_mode->h;
    തിരികെ true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    Atom _NET_WORKAREA;
    പൂർണ്ണസംഖ്യ real_format;
    Atom real_type;
    unsigned long ഇനങ്ങൾ_read = 0, ഇനങ്ങൾ_ഇടത് = 0;
    unsigned അക്ഷരം *propdata = ശൂന്യ;
    bool result = false;

    എങ്കിൽ (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        തിരികെ false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    പൂർണ്ണസംഖ്യ status = X11_XGetWindowProperty(display, Default_വേര്_Window(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &ഇനങ്ങൾ_read,
                                    &ഇനങ്ങൾ_ഇടത്, &propdata);
    എങ്കിൽ ((status == Success) && (ഇനങ്ങൾ_read >= 4)) {
        സ്ഥിരം long *p = (long *)propdata;
        സ്ഥിരം SDL_Rect usable = { (പൂർണ്ണസംഖ്യ)p[0], (പൂർണ്ണസംഖ്യ)p[1], (പൂർണ്ണസംഖ്യ)p[2], (പൂർണ്ണസംഖ്യ)p[3] };
        result = true;
        എങ്കിൽ (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    എങ്കിൽ (propdata) {
        X11_XFree(propdata);
    }

    തിരികെ result;
}

#endif // SDL_VIDEO_DRIVER_X11
