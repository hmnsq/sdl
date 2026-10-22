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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11settings.h"
#अन्तर्भाव "edid.h"
#अन्तर्भाव "../../events/SDL_displayevents_c.h"
#अन्तर्भाव "../SDL_pixels_c.h"

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

दशांश X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    द्विगुण scale_factor = 0.0;

    // First use the forced scaling factor specified by the app/user
    स्थिरांक अक्षर *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_FACTOR);
    जर (hint && *hint) {
        द्विगुण मूल्य = SDL_atof(hint);
        जर (मूल्य >= 1.0f && मूल्य <= 10.0f) {
            scale_factor = मूल्य;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    जर (scale_factor <= 0.0) {
        पूर्णांक status, real_format;
        Atom real_type;
        Atom res_mgr;
        अचिन्हित दीर्घ वस्तुसंच_read, वस्तुसंच_डावा;
        अक्षर *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        status = X11_XGetWindowProperty(display, मूळ_Window(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &वस्तुसंच_read, &वस्तुसंच_डावा,
                                        (अचिन्हित अक्षर **)&resource_manager);

        जर (status == Success && resource_manager) {
            owns_resource_manager = true;
        } अन्यथा {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        जर (resource_manager) {
            XrmDatabase db;
            Xrm_मूल्य मूल्य;
            अक्षर *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            जर (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &मूल्य)) {
                जर (मूल्य.addr && type && SDL_strcmp(type, "String") == 0) {
                    पूर्णांक dpi = SDL_atoi(मूल्य.addr);
                    scale_factor  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            जर (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    जर (scale_factor <= 0.0) {
        scale_factor = X11_Get_Xsettings_Client_Int_किल्ली(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        जर (scale_factor <= 0.0) {
            पूर्णांक dpi = X11_Get_Xsettings_Client_Int_किल्ली(client, "Xft/DPI", -1);
            जर (dpi > 0) {
                scale_factor = (द्विगुण) dpi / 1024.0;
                scale_factor /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    जर (scale_factor <= 0.0) {
        स्थिरांक अक्षर *scale_str = SDL_getenv("GDK_SCALE");
        जर (scale_str) {
            scale_factor = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    जर (scale_factor <= 0.0) {
        scale_factor = 1.0;
    }

    परत (दशांश)scale_factor;
}

दशांश X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    परत X11_GetGlobalContentScale(_this->internal->display, _this->internal->xsettings_data.xsettings);
}

स्थिर bool get_visualinfo(Display *display, पूर्णांक screen, XVisualInfo *vinfo)
{
    स्थिरांक अक्षर *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    पूर्णांक depth;

    // Look for an exact visual, if requested
    जर (visual_id && *visual_id) {
        XVisualInfo *vi, ढाँचा;
        पूर्णांक nvis;

        SDL_zero(ढाँचा);
        ढाँचा.visualid = SDL_strtol(visual_id, रिक्त, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &ढाँचा, &nvis);
        जर (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            परत true;
        }
    }

    depth = DefaultDepth(display, screen);
    जर ((X11_UseDirectColorVisuals() &&
         X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
        परत true;
    }
    परत false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    पूर्णांक nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    जर (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        परत true;
    }
    परत false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    जर (vinfo->class == DirectColor || vinfo->class == TrueColor) {
        पूर्णांक bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_mask;
        Gmask = vinfo->visual->green_mask;
        Bmask = vinfo->visual->blue_mask;
        जर (vinfo->depth == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } अन्यथा {
            Amask = 0;
        }

        bpp = vinfo->depth;
        जर (bpp == 24) {
            पूर्णांक i, n;
            XPixmap_Format_मूल्ये *p = X11_XListPixmapFormats(display, &n);
            जर (p) {
                साठी (i = 0; i < n; ++i) {
                    जर (p[i].depth == 24) {
                        bpp = p[i].bits_per_pixel;
                        थांबा;
                    }
                }
                X11_XFree(p);
            }
        }

        परत SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    जर (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        निवड (vinfo->depth) {
        स्थिती 8:
            परत SDL_PIXELFORMAT_INDEX8;
        स्थिती 4:
            जर (BitmapBitOrder(display) == LSBFirst) {
                परत SDL_PIXELFORMAT_INDEX4LSB;
            } अन्यथा {
                परत SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        स्थिती 1:
            जर (BitmapBitOrder(display) == LSBFirst) {
                परत SDL_PIXELFORMAT_INDEX1LSB;
            } अन्यथा {
                परत SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    परत SDL_PIXELFORMAT_UNKNOWN;
}

स्थिर SDL_DisplayID X11_AddGenericDisplay(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    स्थिरांक पूर्णांक default_screen = DefaultScreen(dpy);
    Screen *screen = ScreenOfDisplay(dpy, default_screen);
    पूर्णांक scanline_pad, n, i;
    SDL_DisplayModeData *modedata;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    XPixmap_Format_मूल्ये *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    जर (!get_visualinfo(dpy, default_screen, &vinfo)) {
        परत SDL_SetError("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    जर (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        परत SDL_SetError("Palettized video modes are no longer supported");
    }

    SDL_zero(mode);
    mode.w = WidthOfScreen(screen);
    mode.h = HeightOfScreen(screen);
    mode.format = pixelformat;

    displaydata = (SDL_DisplayData *)SDL_calloc(1, आकार(*displaydata));
    जर (!displaydata) {
        परत false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, आकार(SDL_DisplayModeData));
    जर (!modedata) {
        SDL_free(displaydata);
        परत false;
    }
    mode.internal = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    जर (pixmapformats) {
        साठी (i = 0; i < n; ++i) {
            जर (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                थांबा;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (अक्षर *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_mode = mode;
    display.internal = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    परत SDL_AddVideoDisplay(&display, send_event);
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR

स्थिर शून्य X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
    जर (displays) {
        साठी (पूर्णांक i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            स्थिरांक SDL_DisplayData *displaydata = display->internal;
            जर (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

स्थिर bool CheckXRandR(Display *display, पूर्णांक *major, पूर्णांक *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ifdef XRANDR_DISABLED_BY_DEFAULT
    जर (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#endif
        परत false;
    }
#अन्यथा
    जर (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#endif
        परत false;
    }
#endif // XRANDR_DISABLED_BY_DEFAULT

    जर (!SDL_X11_HAVE_XRANDR) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#endif
        परत false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    जर (!X11_XRRQueryVersion(display, major, minor)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#endif
        *major = *minor = 0;
        परत false;
    }
#ifdef X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#endif
    परत true;
}

#define XRANDR_ROTATION_डावा  (1 << 1)
#define XRANDR_ROTATION_उजवा (1 << 3)

स्थिर शून्य CalculateXRandRRefreshRate(स्थिरांक XRRModeInfo *info, पूर्णांक *numerator, पूर्णांक *denominator)
{
    अचिन्हित पूर्णांक vTotal = info->vTotal;

    जर (info->modeFlags & RR_DoubleScan) {
        // doublescan doubles the number of lines
        vTotal *= 2;
    }

    जर (info->modeFlags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        vTotal /= 2;
    }

    जर (info->hTotal && vTotal) {
        *numerator = info->dotClock;
        *denominator = (info->hTotal * vTotal);
    } अन्यथा {
        *numerator = 0;
        *denominator = 0;
    }
}

स्थिर bool SetXRandRModeInfo(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode modeID, SDL_DisplayMode *mode)
{
    पूर्णांक i;
    साठी (i = 0; i < res->nmode; ++i) {
        स्थिरांक XRRModeInfo *info = &res->modes[i];
        जर (info->id == modeID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtcTransformAttributes *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            जर (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            जर (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            जर (rotation & (XRANDR_ROTATION_डावा | XRANDR_ROTATION_उजवा)) {
                mode->w = (info->height * scale_w + 0xffff) >> 16;
                mode->h = (info->width * scale_h + 0xffff) >> 16;
            } अन्यथा {
                mode->w = (info->width * scale_w + 0xffff) >> 16;
                mode->h = (info->height * scale_h + 0xffff) >> 16;
            }
            CalculateXRandRRefreshRate(info, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
            mode->internal->xrandr_mode = modeID;
#ifdef X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (पूर्णांक)modeID,
                    mode->screen_w, mode->screen_h, mode->refresh_rate_numerator, mode->refresh_rate_denominator);
#endif
            परत true;
        }
    }
    परत false;
}

स्थिर bool Get_मूळ_Window_Cardinal_Property(Display *dpy, पूर्णांक screen, स्थिरांक अक्षर *name, Uint32 *मूल्य)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    जर (atom == None) {
        परत false;
    }

    पूर्णांक real_format;
    Atom real_type;
    अचिन्हित दीर्घ वस्तुसंच_read = 0, वस्तुसंच_डावा = 0;
    अचिन्हित अक्षर *propdata = रिक्त;
    पूर्णांक status;
    bool result = false;

    status = X11_XGetWindowProperty(dpy, मूळ_Window(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &वस्तुसंच_read, &वस्तुसंच_डावा, &propdata);
    जर (status == Success && propdata) {
        जर (real_type == XA_CARDINAL && वस्तुसंच_read > 0) {
            निवड (real_format) {
            स्थिती 8:
                *मूल्य = propdata[0];
                थांबा;
            स्थिती 16:
                *मूल्य = propdata[0] | (propdata[1] << 8);
                थांबा;
            पूर्वनिर्धारित:
                *मूल्य = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                थांबा;
            }
            result = true;
        }
        X11_XFree(propdata);
    }
    परत result;
}

स्थिर bool Get_मूळ_Window_Bool_Property(Display *dpy, पूर्णांक screen, स्थिरांक अक्षर *name, bool *मूल्य)
{
    Uint32 v;
    जर (Get_मूळ_Window_Cardinal_Property(dpy, screen, name, &v)) {
        *मूल्य = (v != 0);
        परत true;
    }
    परत false;
}

स्थिर bool Get_मूळ_Window_Float_Property(Display *dpy, पूर्णांक screen, स्थिरांक अक्षर *name, दशांश *मूल्य)
{
    Uint32 v;
    जर (Get_मूळ_Window_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(मूल्य, &v, आकार(v));
        परत true;
    }
    परत false;
}

स्थिर bool IsSteamDeckOLEDDisplay(स्थिरांक MonitorInfo *info)
{
    जर (SDL_strcmp(info->manufacturer_code, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        जर (info->product_code == 0x3003 || info->product_code == 0x3004) {
            परत true;
        }
    }
    परत false;
}

स्थिर दशांश GetGamescopeSDRWhiteLevel(Display *dpy, पूर्णांक screen, स्थिरांक MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    जर (!dpy) {
        परत 0.0f;
    }

    दशांश SDR_white_level = 0.0f;
    bool external_display = false;
    जर (Get_मूळ_Window_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_मूळ_Window_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } अन्यथा जर (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (दशांश)info->max_luminance / 3.0f;
    } अन्यथा {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    परत SDR_white_level;
}

स्थिर MonitorInfo *GetMonitorInfo(Display *dpy, पूर्णांक screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = रिक्त;
    पूर्णांक real_format;
    Atom real_type;
    अचिन्हित दीर्घ वस्तुसंच_read = 0, वस्तुसंच_डावा = 0;
    अचिन्हित अक्षर *propdata = रिक्त;
    पूर्णांक status;

    *gamescope = false;

    जर (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_PATH = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        जर (GAMESCOPE_DISPLAY_EDID_PATH != None) {
            status = X11_XGetWindowProperty(dpy, मूळ_Window(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_PATH, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &वस्तुसंच_read, &वस्तुसंच_डावा, &propdata);
            जर (status == Success && propdata) {
                माप_प्रकार size = 0;
                शून्य *data = SDL_LoadFile((अक्षर *)propdata, &size);
                जर (data) {
                    info = decode_edid((uchar *)data, size);
                    जर (info) {
                        *gamescope = true;
                    }
                    SDL_free(data);
                }
            }
            जर (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    जर (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        जर (EDID != None) {
            पूर्णांक nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            साठी (पूर्णांक i = 0; i < nprop; ++i) {
                जर (props[i] == EDID) {
                    status = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &वस्तुसंच_read, &वस्तुसंच_डावा, &propdata);
                    जर (status == Success && propdata) {
                        info = decode_edid(propdata, वस्तुसंच_read);
                    }
                    जर (propdata) {
                        X11_XFree(propdata);
                    }
                    थांबा;
                }
            }

            जर (props) {
                X11_XFree(props);
            }
        }
    }

#ifdef X11MODES_DEBUG
    जर (info) {
        dump_monitor_info(info);
    }
#endif
    परत info;
}

स्थिर शून्य SetXRandRDisplayName(MonitorInfo *info, अक्षर *name, माप_प्रकार namelen, अचिन्हित दीर्घ widthmm, अचिन्हित दीर्घ heightmm)
{
    जर (info) {
        SDL_strlcpy(name, info->dsc_product_name, namelen);
    }

    पूर्णांक inches = (पूर्णांक)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    जर (*name && inches) {
        स्थिरांक माप_प्रकार len = SDL_strlen(name);
        (शून्य)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ifdef X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#endif
}

स्थिर bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, पूर्णांक screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, अक्षर *display_name, माप_प्रकार display_name_size)
{
    XRROutputInfo *output_info;
    पूर्णांक display_x, display_y;
    अचिन्हित दीर्घ display_mm_width, display_mm_height;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    SDL_DisplayModeData *modedata;
    RRMode modeID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_मूल्ये *pixmapformats;
    पूर्णांक scanline_pad;
    पूर्णांक i, n;

    जर (!display || !display_name) {
        परत false; // invalid parameters
    }

    जर (!get_visualinfo(dpy, screen, &vinfo)) {
        परत false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    जर (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        परत false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    जर (pixmapformats) {
        साठी (i = 0; i < n; i++) {
            जर (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                थांबा;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    जर (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        परत false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_size);
    display_mm_width = output_info->mm_width;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    जर (!crtc) {
        परत false; // oh well, ignore it.
    }

    SDL_zero(mode);
    modeID = crtc->mode;
    mode.w = crtc->width;
    mode.h = crtc->height;
    mode.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_DisplayData *)SDL_calloc(1, आकार(*displaydata));
    जर (!displaydata) {
        परत false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, आकार(SDL_DisplayModeData));
    जर (!modedata) {
        SDL_free(displaydata);
        परत false;
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
    SDL_strlcpy(displaydata->connector_name, display_name, आकार(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    SetXRandRModeInfo(dpy, res, output_crtc, modeID, &mode);
    SetXRandRDisplayName(info, display_name, display_name_size, display_mm_width, display_mm_height);

    SDL_zero(*display);
    जर (*display_name) {
        display->name = display_name;
    }
    display->desktop_mode = mode;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->internal = displaydata;

    जर (info) {
        दशांश SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        जर (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } अन्यथा {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ifdef X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#endif
        जर (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (दशांश)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    परत true;
}

स्थिर bool X11_AddXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, पूर्णांक screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    अक्षर display_name[128];

    जर (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, आकार(display_name))) {
        परत true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    जर (displayID == 0) {
        परत false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    जर (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    परत true;
}


स्थिर bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, पूर्णांक screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    अक्षर display_name[128];

    जर (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, आकार(display_name))) {
        परत false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_SetDesktopDisplayMode(existing_display, &display.desktop_mode);

    // update bounds
    जर (existing_display->internal->x != display.internal->x ||
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

    परत true;
}

स्थिर XRRScreenResources *X11_GetScreenResources(Display *dpy, पूर्णांक screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, मूळ_Window(dpy, screen));
    जर (!res || res->noutput == 0) {
        जर (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, मूळ_Window(dpy, screen));
    }
    परत res;
}

शून्य X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    स्थिरांक पूर्णांक screencount = Screen_मोजणी(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
    जर (!displays) {
        परत;
    }

    साठी (पूर्णांक screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        जर (!res) {
            सुरूठेवा;
        }

        साठी (पूर्णांक i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            स्थिरांक SDL_DisplayData *displaydata = display->internal;
            जर (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

स्थिर शून्य X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    स्थिरांक पूर्णांक screencount = Screen_मोजणी(dpy);
    पूर्णांक अंक_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&अंक_displays);
    जर (!displays) {
        परत;
    }

    साठी (पूर्णांक screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        जर (!res) {
            सुरूठेवा;
        }

        साठी (पूर्णांक output = 0; output < res->noutput; output++) {
            साठी (पूर्णांक i = 0; i < अंक_displays; ++i) {
                जर (!displays[i]) {
                    // We already removed this display from the list
                    सुरूठेवा;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                स्थिरांक SDL_DisplayData *displaydata = display->internal;
                जर (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    थांबा;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    साठी (पूर्णांक i = 0; i < अंक_displays; ++i) {
        जर (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            स्थिरांक SDL_DisplayData *displaydata = display->internal;
            जर (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

स्थिर शून्य X11_HandleXRandROutputChange(SDL_VideoDevice *_this, स्थिरांक XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = रिक्त;
    पूर्णांक i;

#जर 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (अचिन्हित पूर्णांक) ev->output, (अचिन्हित पूर्णांक) ev->crtc, (अचिन्हित पूर्णांक) ev->mode, (अचिन्हित पूर्णांक) ev->rotation, (अचिन्हित पूर्णांक) ev->connection);
#endif

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(रिक्त);
    जर (displays) {
        साठी (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            स्थिरांक SDL_DisplayData *displaydata = thisdisplay->internal;
            जर (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                थांबा;
            }
        }
        SDL_free(displays);
    }

    जर (ev->connection == RR_Disconnected) { // output is going away
        जर (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            जर (_this->अंक_displays == 1) {
                generic_display = X11_AddGenericDisplay(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            जर (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } अन्यथा जर (ev->connection == RR_Connected) { // output is coming online
        जर (!display) {
            Display *dpy = ev->display;
            स्थिरांक पूर्णांक screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            जर (res) {
                X11_AddXRandRDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

शून्य X11_HandleXRandREvent(SDL_VideoDevice *_this, स्थिरांक XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_assert(xevent->type == (videodata->xrandr_event_base + RRNotify));

    निवड (((स्थिरांक XRRNotifyEvent *)xevent)->subtype) {
    स्थिती RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (स्थिरांक XRROutputChangeNotifyEvent *)xevent);
        थांबा;
    पूर्वनिर्धारित:
        थांबा;
    }
}

स्थिर शून्य X11_SortOutputsByPriorityHint(SDL_VideoDevice *_this)
{
    स्थिरांक अक्षर *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    जर (name_hint) {
        अक्षर *saveptr;
        अक्षर *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(आकार(SDL_VideoDisplay *) * _this->अंक_displays);

        जर (str && sorted_list) {
            पूर्णांक sorted_index = 0;

            // Sort the requested displays to the front of the list.
            स्थिरांक अक्षर *token = SDL_strtok_r(str, ",", &saveptr);
            पर्यंत (token) {
                साठी (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    जर (d) {
                        SDL_DisplayData *data = d->internal;
                        जर (SDL_strcmp(token, data->connector_name) == 0) {
                            sorted_list[sorted_index++] = d;
                            _this->displays[i] = रिक्त;
                            थांबा;
                        }
                    }
                }

                token = SDL_strtok_r(रिक्त, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            साठी (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
                जर (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, आकार(SDL_VideoDisplay *) * _this->अंक_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

स्थिर bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    स्थिरांक पूर्णांक screencount = Screen_मोजणी(dpy);
    स्थिरांक पूर्णांक default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, मूळ_Window(dpy, default_screen));
    पूर्णांक xrandr_error_base = 0;
    पूर्णांक looking_for_primary;
    पूर्णांक output;
    पूर्णांक screen;

    जर (!X11_XRRQueryExtension(dpy, &data->xrandr_event_base, &xrandr_error_base)) {
        परत SDL_SetError("XRRQueryExtension failed");
    }

    साठी (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        साठी (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            जर (looking_for_primary && (screen != default_screen)) {
                सुरूठेवा;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            जर (!res) {
                सुरूठेवा;
            }

            साठी (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                जर ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    सुरूठेवा;
                }
                जर (!X11_AddXRandRDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    थांबा;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_आदान(dpy, मूळ_Window(dpy, screen), RROutputChangeNotifyMask);
        }
    }

    जर (_this->अंक_displays == 0) {
        परत SDL_SetError("No available displays");
    }

    X11_SortOutputsByPriorityHint(_this);

    परत true;
}
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
स्थिर bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    जर (X11_AddGenericDisplay(_this, true) == 0) {
        परत false;
    }
    परत true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_VideoData *data = _this->internal;
        पूर्णांक xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        जर (CheckXRandR(data->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            परत true;
        }
    }
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    परत X11_InitModes_StdXlib(_this);
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

    जर (data->use_xrandr) {
        Display *display = _this->internal->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, मूळ_Window(display, data->screen));
        जर (res) {
            SDL_DisplayModeData *modedata;
            XRROutputInfo *output_info;
            पूर्णांक i;

            output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
            जर (output_info && output_info->connection != RR_Disconnected) {
                साठी (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_DisplayModeData *)SDL_calloc(1, आकार(SDL_DisplayModeData));
                    जर (!modedata) {
                        सुरूठेवा;
                    }
                    mode.internal = modedata;

                    जर (!SetXRandRModeInfo(display, res, output_info->crtc, output_info->modes[i], &mode) ||
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
    परत true;
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
स्थिर पूर्णांक (*PreXRRSetScreenSizeErrorHandler)(Display *, XErrorEvent *) = रिक्त;
स्थिर पूर्णांक SDL_XRRSetScreenSizeErrHandler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    जर ((e->error_code == BadMatch) || (e->error_code == Bad_मूल्य)) {
        परत 0;
    }

    परत PreXRRSetScreenSizeErrorHandler(d, e);
}
#endif

bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *data = sdl_display->internal;

    viddata->last_mode_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    जर (!viddata->is_xwayland) {
        जर (sdl_display->current_mode != mode) {
            data->mode_switch_deadline_ns = SDL_GetTicksNS() + MODE_SWITCH_TIMEOUT_NS;
        } अन्यथा {
            data->mode_switch_deadline_ns = 0;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    जर (data->use_xrandr) {
        Display *display = viddata->display;
        SDL_DisplayModeData *modedata = mode->internal;
        पूर्णांक mm_width, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        Status status;

        res = X11_XRRGetScreenResources(display, मूळ_Window(display, data->screen));
        जर (!res) {
            परत SDL_SetError("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
        जर (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            परत SDL_SetError("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        जर (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            परत SDL_SetError("Couldn't get XRandR crtc info");
        }

        जर (crtc->mode == modedata->xrandr_mode) {
#ifdef X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->mode, crtc->width, crtc->height);
#endif
            status = Success;
            जा freeInfo;
        }

        X11_XGrabServer(display);
        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, रिक्त, 0);
        जर (status != Success) {
            जा ungrabServer;
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
        X11_XRRSetScreenSize(display, मूळ_Window(display, data->screen),
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

        जर (status != Success) {
            परत SDL_SetError("X11_XRRSetCrtcConfig failed");
        }
    }
#अन्यथा
    (शून्य)data;
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    परत true;
}

शून्य X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_DisplayData *data = sdl_display->internal;

    rect->x = data->x;
    rect->y = data->y;
    rect->w = sdl_display->current_mode->w;
    rect->h = sdl_display->current_mode->h;
    परत true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    Atom _NET_WORKAREA;
    पूर्णांक real_format;
    Atom real_type;
    अचिन्हित दीर्घ वस्तुसंच_read = 0, वस्तुसंच_डावा = 0;
    अचिन्हित अक्षर *propdata = रिक्त;
    bool result = false;

    जर (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        परत false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    पूर्णांक status = X11_XGetWindowProperty(display, Default_मूळ_Window(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &वस्तुसंच_read,
                                    &वस्तुसंच_डावा, &propdata);
    जर ((status == Success) && (वस्तुसंच_read >= 4)) {
        स्थिरांक दीर्घ *p = (दीर्घ *)propdata;
        स्थिरांक SDL_Rect usable = { (पूर्णांक)p[0], (पूर्णांक)p[1], (पूर्णांक)p[2], (पूर्णांक)p[3] };
        result = true;
        जर (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    जर (propdata) {
        X11_XFree(propdata);
    }

    परत result;
}

#endif // SDL_VIDEO_DRIVER_X11
