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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11

#समावेश "SDL_x11video.h"
#समावेश "SDL_x11settings.h"
#समावेश "edid.h"
#समावेश "../../events/SDL_displayevents_c.h"
#समावेश "../SDL_pixels_c.h"

// #define X11MODES_DEBUG

/* Timeout and revert mode switches if the timespan has elapsed without the window becoming fullscreen.
 * 5 seconds seems good from testing.
 */
#घोषणा MODE_SWITCH_TIMEOUT_NS SDL_NS_PER_SECOND * 5

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

भग्न X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    द्विगुन scale_factor = 0.0;

    // First use the forced scaling factor specified by the app/user
    स्थिर अक्षर *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_FACTOR);
    अगर (hint && *hint) {
        द्विगुन मूल्य = SDL_atof(hint);
        अगर (मूल्य >= 1.0f && मूल्य <= 10.0f) {
            scale_factor = मूल्य;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    अगर (scale_factor <= 0.0) {
        पूर्णांक status, real_format;
        Atom real_type;
        Atom res_mgr;
        अचिन्हित दीर्घ वस्तुएँ_read, वस्तुएँ_बायाँ;
        अक्षर *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        status = X11_XGetWindowProperty(display, मूल_Window(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &वस्तुएँ_read, &वस्तुएँ_बायाँ,
                                        (अचिन्हित अक्षर **)&resource_manager);

        अगर (status == Success && resource_manager) {
            owns_resource_manager = true;
        } अन्यथा {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        अगर (resource_manager) {
            XrmDatabase db;
            Xrm_मूल्य मूल्य;
            अक्षर *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            अगर (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &मूल्य)) {
                अगर (मूल्य.addr && type && SDL_strcmp(type, "String") == 0) {
                    पूर्णांक dpi = SDL_atoi(मूल्य.addr);
                    scale_factor  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            अगर (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    अगर (scale_factor <= 0.0) {
        scale_factor = X11_Get_Xsettings_Client_Int_कुंजी(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        अगर (scale_factor <= 0.0) {
            पूर्णांक dpi = X11_Get_Xsettings_Client_Int_कुंजी(client, "Xft/DPI", -1);
            अगर (dpi > 0) {
                scale_factor = (द्विगुन) dpi / 1024.0;
                scale_factor /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    अगर (scale_factor <= 0.0) {
        स्थिर अक्षर *scale_str = SDL_getenv("GDK_SCALE");
        अगर (scale_str) {
            scale_factor = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    अगर (scale_factor <= 0.0) {
        scale_factor = 1.0;
    }

    वापस (भग्न)scale_factor;
}

भग्न X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    वापस X11_GetGlobalContentScale(_this->internal->display, _this->internal->xsettings_तथ्य.xsettings);
}

अटल bool get_visualinfo(Display *display, पूर्णांक screen, XVisualInfo *vinfo)
{
    स्थिर अक्षर *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    पूर्णांक depth;

    // Look for an exact visual, if requested
    अगर (visual_id && *visual_id) {
        XVisualInfo *vi, ढाँचा;
        पूर्णांक nvis;

        SDL_zero(ढाँचा);
        ढाँचा.visualid = SDL_strtol(visual_id, शून्य, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &ढाँचा, &nvis);
        अगर (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            वापस true;
        }
    }

    depth = DefaultDepth(display, screen);
    अगर ((X11_UseDirectColorVisuals() &&
         X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
        वापस true;
    }
    वापस false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    पूर्णांक nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    अगर (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        वापस true;
    }
    वापस false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    अगर (vinfo->class == DirectColor || vinfo->class == TrueColor) {
        पूर्णांक bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_mask;
        Gmask = vinfo->visual->green_mask;
        Bmask = vinfo->visual->blue_mask;
        अगर (vinfo->depth == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } अन्यथा {
            Amask = 0;
        }

        bpp = vinfo->depth;
        अगर (bpp == 24) {
            पूर्णांक i, n;
            XPixmap_Format_मूल्यावली *p = X11_XListPixmapFormats(display, &n);
            अगर (p) {
                क्रम (i = 0; i < n; ++i) {
                    अगर (p[i].depth == 24) {
                        bpp = p[i].bits_per_pixel;
                        अवरोध;
                    }
                }
                X11_XFree(p);
            }
        }

        वापस SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    अगर (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        चयन (vinfo->depth) {
        हाल 8:
            वापस SDL_PIXELFORMAT_INDEX8;
        हाल 4:
            अगर (BitmapBitOrder(display) == LSBFirst) {
                वापस SDL_PIXELFORMAT_INDEX4LSB;
            } अन्यथा {
                वापस SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        हाल 1:
            अगर (BitmapBitOrder(display) == LSBFirst) {
                वापस SDL_PIXELFORMAT_INDEX1LSB;
            } अन्यथा {
                वापस SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    वापस SDL_PIXELFORMAT_UNKNOWN;
}

अटल SDL_DisplayID X11_AddGenericDisplay(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_Video_तथ्य *तथ्य = _this->internal;
    Display *dpy = तथ्य->display;
    स्थिर पूर्णांक default_screen = DefaultScreen(dpy);
    Screen *screen = ScreenOfDisplay(dpy, default_screen);
    पूर्णांक scanline_pad, n, i;
    SDL_Display_Mode_तथ्य *modedata;
    SDL_Display_तथ्य *displaydata;
    SDL_DisplayMode mode;
    XPixmap_Format_मूल्यावली *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    अगर (!get_visualinfo(dpy, default_screen, &vinfo)) {
        वापस SDL_SetError("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    अगर (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        वापस SDL_SetError("Palettized video modes are no longer supported");
    }

    SDL_zero(mode);
    mode.w = WidthOfScreen(screen);
    mode.h = HeightOfScreen(screen);
    mode.format = pixelformat;

    displaydata = (SDL_Display_तथ्य *)SDL_calloc(1, माप(*displaydata));
    अगर (!displaydata) {
        वापस false;
    }

    modedata = (SDL_Display_Mode_तथ्य *)SDL_calloc(1, माप(SDL_Display_Mode_तथ्य));
    अगर (!modedata) {
        SDL_free(displaydata);
        वापस false;
    }
    mode.internal = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    अगर (pixmapformats) {
        क्रम (i = 0; i < n; ++i) {
            अगर (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                अवरोध;
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
    वापस SDL_AddVideoDisplay(&display, send_event);
}

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR

अटल व्योम X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(शून्य);
    अगर (displays) {
        क्रम (पूर्णांक i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            स्थिर SDL_Display_तथ्य *displaydata = display->internal;
            अगर (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

अटल bool CheckXRandR(Display *display, पूर्णांक *major, पूर्णांक *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#अगर_घोषित XRANDR_DISABLED_BY_DEFAULT
    अगर (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#अगर_घोषित X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#पूर्ण_अगर
        वापस false;
    }
#अन्यथा
    अगर (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#अगर_घोषित X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#पूर्ण_अगर
        वापस false;
    }
#पूर्ण_अगर // XRANDR_DISABLED_BY_DEFAULT

    अगर (!SDL_X11_HAVE_XRANDR) {
#अगर_घोषित X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#पूर्ण_अगर
        वापस false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    अगर (!X11_XRRQueryVersion(display, major, minor)) {
#अगर_घोषित X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#पूर्ण_अगर
        *major = *minor = 0;
        वापस false;
    }
#अगर_घोषित X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#पूर्ण_अगर
    वापस true;
}

#घोषणा XRANDR_ROTATION_बायाँ  (1 << 1)
#घोषणा XRANDR_ROTATION_दायाँ (1 << 3)

अटल व्योम CalculateXRandRRefreshRate(स्थिर XRRModeInfo *info, पूर्णांक *numerator, पूर्णांक *denominator)
{
    अचिन्हित पूर्णांक v_योग_2 = info->v_योग_2;

    अगर (info->modeFlags & RR_DoubleScan) {
        // doublescan doubles the number of lines
        v_योग_2 *= 2;
    }

    अगर (info->modeFlags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        v_योग_2 /= 2;
    }

    अगर (info->h_योग_2 && v_योग_2) {
        *numerator = info->dotClock;
        *denominator = (info->h_योग_2 * v_योग_2);
    } अन्यथा {
        *numerator = 0;
        *denominator = 0;
    }
}

अटल bool SetXRandRModeInfo(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode modeID, SDL_DisplayMode *mode)
{
    पूर्णांक i;
    क्रम (i = 0; i < res->nmode; ++i) {
        स्थिर XRRModeInfo *info = &res->modes[i];
        अगर (info->id == modeID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtcTransformAttributes *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            अगर (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            अगर (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            अगर (rotation & (XRANDR_ROTATION_बायाँ | XRANDR_ROTATION_दायाँ)) {
                mode->w = (info->height * scale_w + 0xffff) >> 16;
                mode->h = (info->width * scale_h + 0xffff) >> 16;
            } अन्यथा {
                mode->w = (info->width * scale_w + 0xffff) >> 16;
                mode->h = (info->height * scale_h + 0xffff) >> 16;
            }
            CalculateXRandRRefreshRate(info, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
            mode->internal->xrandr_mode = modeID;
#अगर_घोषित X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (पूर्णांक)modeID,
                    mode->screen_w, mode->screen_h, mode->refresh_rate_numerator, mode->refresh_rate_denominator);
#पूर्ण_अगर
            वापस true;
        }
    }
    वापस false;
}

अटल bool Get_मूल_Window_Cardinal_Property(Display *dpy, पूर्णांक screen, स्थिर अक्षर *name, Uint32 *मूल्य)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    अगर (atom == None) {
        वापस false;
    }

    पूर्णांक real_format;
    Atom real_type;
    अचिन्हित दीर्घ वस्तुएँ_read = 0, वस्तुएँ_बायाँ = 0;
    अचिन्हित अक्षर *propdata = शून्य;
    पूर्णांक status;
    bool परिणाम = false;

    status = X11_XGetWindowProperty(dpy, मूल_Window(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &वस्तुएँ_read, &वस्तुएँ_बायाँ, &propdata);
    अगर (status == Success && propdata) {
        अगर (real_type == XA_CARDINAL && वस्तुएँ_read > 0) {
            चयन (real_format) {
            हाल 8:
                *मूल्य = propdata[0];
                अवरोध;
            हाल 16:
                *मूल्य = propdata[0] | (propdata[1] << 8);
                अवरोध;
            शेष:
                *मूल्य = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                अवरोध;
            }
            परिणाम = true;
        }
        X11_XFree(propdata);
    }
    वापस परिणाम;
}

अटल bool Get_मूल_Window_Bool_Property(Display *dpy, पूर्णांक screen, स्थिर अक्षर *name, bool *मूल्य)
{
    Uint32 v;
    अगर (Get_मूल_Window_Cardinal_Property(dpy, screen, name, &v)) {
        *मूल्य = (v != 0);
        वापस true;
    }
    वापस false;
}

अटल bool Get_मूल_Window_Float_Property(Display *dpy, पूर्णांक screen, स्थिर अक्षर *name, भग्न *मूल्य)
{
    Uint32 v;
    अगर (Get_मूल_Window_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(मूल्य, &v, माप(v));
        वापस true;
    }
    वापस false;
}

अटल bool IsSteamDeckOLEDDisplay(स्थिर MonitorInfo *info)
{
    अगर (SDL_strcmp(info->manufacturer_code, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        अगर (info->product_code == 0x3003 || info->product_code == 0x3004) {
            वापस true;
        }
    }
    वापस false;
}

अटल भग्न GetGamescopeSDRWhiteLevel(Display *dpy, पूर्णांक screen, स्थिर MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    अगर (!dpy) {
        वापस 0.0f;
    }

    भग्न SDR_white_level = 0.0f;
    bool external_display = false;
    अगर (Get_मूल_Window_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_मूल_Window_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } अन्यथा अगर (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (भग्न)info->max_luminance / 3.0f;
    } अन्यथा {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    वापस SDR_white_level;
}

अटल MonitorInfo *GetMonitorInfo(Display *dpy, पूर्णांक screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = शून्य;
    पूर्णांक real_format;
    Atom real_type;
    अचिन्हित दीर्घ वस्तुएँ_read = 0, वस्तुएँ_बायाँ = 0;
    अचिन्हित अक्षर *propdata = शून्य;
    पूर्णांक status;

    *gamescope = false;

    अगर (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_PATH = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        अगर (GAMESCOPE_DISPLAY_EDID_PATH != None) {
            status = X11_XGetWindowProperty(dpy, मूल_Window(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_PATH, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &वस्तुएँ_read, &वस्तुएँ_बायाँ, &propdata);
            अगर (status == Success && propdata) {
                माप_प्रकार आकार = 0;
                व्योम *तथ्य = SDL_LoadFile((अक्षर *)propdata, &आकार);
                अगर (तथ्य) {
                    info = decode_edid((uchar *)तथ्य, आकार);
                    अगर (info) {
                        *gamescope = true;
                    }
                    SDL_free(तथ्य);
                }
            }
            अगर (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    अगर (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        अगर (EDID != None) {
            पूर्णांक nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            क्रम (पूर्णांक i = 0; i < nprop; ++i) {
                अगर (props[i] == EDID) {
                    status = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &वस्तुएँ_read, &वस्तुएँ_बायाँ, &propdata);
                    अगर (status == Success && propdata) {
                        info = decode_edid(propdata, वस्तुएँ_read);
                    }
                    अगर (propdata) {
                        X11_XFree(propdata);
                    }
                    अवरोध;
                }
            }

            अगर (props) {
                X11_XFree(props);
            }
        }
    }

#अगर_घोषित X11MODES_DEBUG
    अगर (info) {
        dump_monitor_info(info);
    }
#पूर्ण_अगर
    वापस info;
}

अटल व्योम SetXRandRDisplayName(MonitorInfo *info, अक्षर *name, माप_प्रकार namelen, अचिन्हित दीर्घ widthmm, अचिन्हित दीर्घ heightmm)
{
    अगर (info) {
        SDL_strlcpy(name, info->dsc_product_name, namelen);
    }

    पूर्णांक inches = (पूर्णांक)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    अगर (*name && inches) {
        स्थिर माप_प्रकार len = SDL_strlen(name);
        (व्योम)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#अगर_घोषित X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#पूर्ण_अगर
}

अटल bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, पूर्णांक screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, अक्षर *display_name, माप_प्रकार display_name_आकार)
{
    XRROutputInfo *output_info;
    पूर्णांक display_x, display_y;
    अचिन्हित दीर्घ display_mm_width, display_mm_height;
    SDL_Display_तथ्य *displaydata;
    SDL_DisplayMode mode;
    SDL_Display_Mode_तथ्य *modedata;
    RRMode modeID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_मूल्यावली *pixmapformats;
    पूर्णांक scanline_pad;
    पूर्णांक i, n;

    अगर (!display || !display_name) {
        वापस false; // invalid parameters
    }

    अगर (!get_visualinfo(dpy, screen, &vinfo)) {
        वापस false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    अगर (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        वापस false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    अगर (pixmapformats) {
        क्रम (i = 0; i < n; i++) {
            अगर (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                अवरोध;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    अगर (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        वापस false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_आकार);
    display_mm_width = output_info->mm_width;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    अगर (!crtc) {
        वापस false; // oh well, ignore it.
    }

    SDL_zero(mode);
    modeID = crtc->mode;
    mode.w = crtc->width;
    mode.h = crtc->height;
    mode.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_Display_तथ्य *)SDL_calloc(1, माप(*displaydata));
    अगर (!displaydata) {
        वापस false;
    }

    modedata = (SDL_Display_Mode_तथ्य *)SDL_calloc(1, माप(SDL_Display_Mode_तथ्य));
    अगर (!modedata) {
        SDL_free(displaydata);
        वापस false;
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
    SDL_strlcpy(displaydata->connector_name, display_name, माप(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    SetXRandRModeInfo(dpy, res, output_crtc, modeID, &mode);
    SetXRandRDisplayName(info, display_name, display_name_आकार, display_mm_width, display_mm_height);

    SDL_zero(*display);
    अगर (*display_name) {
        display->name = display_name;
    }
    display->desktop_mode = mode;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->internal = displaydata;

    अगर (info) {
        भग्न SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        अगर (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } अन्यथा {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#अगर_घोषित X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#पूर्ण_अगर
        अगर (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (भग्न)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    वापस true;
}

अटल bool X11_AddXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, पूर्णांक screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    अक्षर display_name[128];

    अगर (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, माप(display_name))) {
        वापस true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    अगर (displayID == 0) {
        वापस false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    अगर (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    वापस true;
}


अटल bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, पूर्णांक screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    अक्षर display_name[128];

    अगर (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, माप(display_name))) {
        वापस false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_SetDesktopDisplayMode(existing_display, &display.desktop_mode);

    // update bounds
    अगर (existing_display->internal->x != display.internal->x ||
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

    वापस true;
}

अटल XRRScreenResources *X11_GetScreenResources(Display *dpy, पूर्णांक screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, मूल_Window(dpy, screen));
    अगर (!res || res->noutput == 0) {
        अगर (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, मूल_Window(dpy, screen));
    }
    वापस res;
}

व्योम X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    स्थिर पूर्णांक screencount = Screen_गिनती(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(शून्य);
    अगर (!displays) {
        वापस;
    }

    क्रम (पूर्णांक screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        अगर (!res) {
            जारी;
        }

        क्रम (पूर्णांक i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            स्थिर SDL_Display_तथ्य *displaydata = display->internal;
            अगर (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

अटल व्योम X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    स्थिर पूर्णांक screencount = Screen_गिनती(dpy);
    पूर्णांक अंक_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&अंक_displays);
    अगर (!displays) {
        वापस;
    }

    क्रम (पूर्णांक screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        अगर (!res) {
            जारी;
        }

        क्रम (पूर्णांक output = 0; output < res->noutput; output++) {
            क्रम (पूर्णांक i = 0; i < अंक_displays; ++i) {
                अगर (!displays[i]) {
                    // We already removed this display from the list
                    जारी;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                स्थिर SDL_Display_तथ्य *displaydata = display->internal;
                अगर (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    अवरोध;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    क्रम (पूर्णांक i = 0; i < अंक_displays; ++i) {
        अगर (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            स्थिर SDL_Display_तथ्य *displaydata = display->internal;
            अगर (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

अटल व्योम X11_HandleXRandROutputChange(SDL_VideoDevice *_this, स्थिर XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = शून्य;
    पूर्णांक i;

#अगर 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (अचिन्हित पूर्णांक) ev->output, (अचिन्हित पूर्णांक) ev->crtc, (अचिन्हित पूर्णांक) ev->mode, (अचिन्हित पूर्णांक) ev->rotation, (अचिन्हित पूर्णांक) ev->connection);
#पूर्ण_अगर

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(शून्य);
    अगर (displays) {
        क्रम (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            स्थिर SDL_Display_तथ्य *displaydata = thisdisplay->internal;
            अगर (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                अवरोध;
            }
        }
        SDL_free(displays);
    }

    अगर (ev->connection == RR_Disconnected) { // output is going away
        अगर (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            अगर (_this->अंक_displays == 1) {
                generic_display = X11_AddGenericDisplay(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            अगर (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } अन्यथा अगर (ev->connection == RR_Connected) { // output is coming online
        अगर (!display) {
            Display *dpy = ev->display;
            स्थिर पूर्णांक screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            अगर (res) {
                X11_AddXRandRDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

व्योम X11_HandleXRandREvent(SDL_VideoDevice *_this, स्थिर XEvent *xevent)
{
    SDL_Video_तथ्य *videodata = _this->internal;
    SDL_assert(xevent->type == (videodata->xrandr_event_base + RRNotify));

    चयन (((स्थिर XRRNotifyEvent *)xevent)->subtype) {
    हाल RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (स्थिर XRROutputChangeNotifyEvent *)xevent);
        अवरोध;
    शेष:
        अवरोध;
    }
}

अटल व्योम X11_SortOutputsByPriorityHint(SDL_VideoDevice *_this)
{
    स्थिर अक्षर *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    अगर (name_hint) {
        अक्षर *saveptr;
        अक्षर *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(माप(SDL_VideoDisplay *) * _this->अंक_displays);

        अगर (str && sorted_list) {
            पूर्णांक sorted_सूचकांक = 0;

            // Sort the requested displays to the front of the list.
            स्थिर अक्षर *token = SDL_strtok_r(str, ",", &saveptr);
            जबतक (token) {
                क्रम (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    अगर (d) {
                        SDL_Display_तथ्य *तथ्य = d->internal;
                        अगर (SDL_strcmp(token, तथ्य->connector_name) == 0) {
                            sorted_list[sorted_सूचकांक++] = d;
                            _this->displays[i] = शून्य;
                            अवरोध;
                        }
                    }
                }

                token = SDL_strtok_r(शून्य, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            क्रम (पूर्णांक i = 0; i < _this->अंक_displays; ++i) {
                अगर (_this->displays[i]) {
                    sorted_list[sorted_सूचकांक++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, माप(SDL_VideoDisplay *) * _this->अंक_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

अटल bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    Display *dpy = तथ्य->display;
    स्थिर पूर्णांक screencount = Screen_गिनती(dpy);
    स्थिर पूर्णांक default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, मूल_Window(dpy, default_screen));
    पूर्णांक xrandr_error_base = 0;
    पूर्णांक looking_for_primary;
    पूर्णांक output;
    पूर्णांक screen;

    अगर (!X11_XRRQueryExtension(dpy, &तथ्य->xrandr_event_base, &xrandr_error_base)) {
        वापस SDL_SetError("XRRQueryExtension failed");
    }

    क्रम (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        क्रम (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            अगर (looking_for_primary && (screen != default_screen)) {
                जारी;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            अगर (!res) {
                जारी;
            }

            क्रम (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                अगर ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    जारी;
                }
                अगर (!X11_AddXRandRDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    अवरोध;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_निवेश(dpy, मूल_Window(dpy, screen), RROutputChangeNotifyMask);
        }
    }

    अगर (_this->अंक_displays == 0) {
        वापस SDL_SetError("No available displays");
    }

    X11_SortOutputsByPriorityHint(_this);

    वापस true;
}
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
अटल bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    अगर (X11_AddGenericDisplay(_this, true) == 0) {
        वापस false;
    }
    वापस true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_Video_तथ्य *तथ्य = _this->internal;
        पूर्णांक xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        अगर (CheckXRandR(तथ्य->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            वापस true;
        }
    }
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    वापस X11_InitModes_StdXlib(_this);
}

bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display)
{
#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
    SDL_Display_तथ्य *तथ्य = sdl_display->internal;
    SDL_DisplayMode mode;

    /* Unfortunately X11 requires the window to be created with the correct
     * visual and depth ahead of time, but the SDL API allows you to create
     * a window before setting the fullscreen display mode.  This means that
     * we have to use the same format for all windows and all display modes.
     * (or support recreating the window with a new visual behind the scenes)
     */
    SDL_zero(mode);
    mode.format = sdl_display->desktop_mode.format;

    अगर (तथ्य->use_xrandr) {
        Display *display = _this->internal->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, मूल_Window(display, तथ्य->screen));
        अगर (res) {
            SDL_Display_Mode_तथ्य *modedata;
            XRROutputInfo *output_info;
            पूर्णांक i;

            output_info = X11_XRRGetOutputInfo(display, res, तथ्य->xrandr_output);
            अगर (output_info && output_info->connection != RR_Disconnected) {
                क्रम (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_Display_Mode_तथ्य *)SDL_calloc(1, माप(SDL_Display_Mode_तथ्य));
                    अगर (!modedata) {
                        जारी;
                    }
                    mode.internal = modedata;

                    अगर (!SetXRandRModeInfo(display, res, output_info->crtc, output_info->modes[i], &mode) ||
                        !SDL_AddFullscreenDisplayMode(sdl_display, &mode)) {
                        SDL_free(modedata);
                    }
                }
            }
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
        }
    }
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XRANDR
    वापस true;
}

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
अटल पूर्णांक (*Pre_XRRSet_Screen_आकार_Error_Handler)(Display *, XErrorEvent *) = शून्य;
अटल पूर्णांक SDL_XRRSet_Screen_आकार_Err_Handler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    अगर ((e->error_code == BadMatch) || (e->error_code == Bad_मूल्य)) {
        वापस 0;
    }

    वापस Pre_XRRSet_Screen_आकार_Error_Handler(d, e);
}
#पूर्ण_अगर

bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_Video_तथ्य *viddata = _this->internal;
    SDL_Display_तथ्य *तथ्य = sdl_display->internal;

    viddata->last_mode_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    अगर (!viddata->is_xwayland) {
        अगर (sdl_display->current_mode != mode) {
            तथ्य->mode_switch_deadline_ns = SDL_GetTicksNS() + MODE_SWITCH_TIMEOUT_NS;
        } अन्यथा {
            तथ्य->mode_switch_deadline_ns = 0;
        }
    }

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XRANDR
    अगर (तथ्य->use_xrandr) {
        Display *display = viddata->display;
        SDL_Display_Mode_तथ्य *modedata = mode->internal;
        पूर्णांक mm_width, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        Status status;

        res = X11_XRRGetScreenResources(display, मूल_Window(display, तथ्य->screen));
        अगर (!res) {
            वापस SDL_SetError("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, तथ्य->xrandr_output);
        अगर (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            वापस SDL_SetError("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        अगर (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            वापस SDL_SetError("Couldn't get XRandR crtc info");
        }

        अगर (crtc->mode == modedata->xrandr_mode) {
#अगर_घोषित X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->mode, crtc->width, crtc->height);
#पूर्ण_अगर
            status = Success;
            जाओ freeInfo;
        }

        X11_XGrabServer(display);
        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, शून्य, 0);
        अगर (status != Success) {
            जाओ ungrabServer;
        }

        mm_width = mode->w * DisplayWidthMM(display, तथ्य->screen) / DisplayWidth(display, तथ्य->screen);
        mm_height = mode->h * DisplayHeightMM(display, तथ्य->screen) / DisplayHeight(display, तथ्य->screen);

        /* !!! FIXME: this can get into a problem scenario when a window is
           bigger than a physical monitor in a configuration where one screen
           spans multiple physical monitors. A detailed reproduction case is
           discussed at https://github.com/libsdl-org/SDL/issues/4561 ...
           for now we cheat and just catch the X11 error and carry on, which
           is likely to cause subtle issues but is better than outright
           crashing */
        X11_XSync(display, False);
        Pre_XRRSet_Screen_आकार_Error_Handler = X11_XSetErrorHandler(SDL_XRRSet_Screen_आकार_Err_Handler);
        X11_XRRSet_Screen_आकार(display, मूल_Window(display, तथ्य->screen),
                             mode->w, mode->h, mm_width, mm_height);
        X11_XSync(display, False);
        X11_XSetErrorHandler(Pre_XRRSet_Screen_आकार_Error_Handler);

        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      crtc->x, crtc->y, modedata->xrandr_mode, crtc->rotation,
                                      &तथ्य->xrandr_output, 1);

    ungrabServer:
        X11_XUngrabServer(display);
    freeInfo:
        X11_XRRFreeCrtcInfo(crtc);
        X11_XRRFreeOutputInfo(output_info);
        X11_XRRFreeScreenResources(res);

        अगर (status != Success) {
            वापस SDL_SetError("X11_XRRSetCrtcConfig failed");
        }
    }
#अन्यथा
    (व्योम)तथ्य;
#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XRANDR

    वापस true;
}

व्योम X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Display_तथ्य *तथ्य = sdl_display->internal;

    rect->x = तथ्य->x;
    rect->y = तथ्य->y;
    rect->w = sdl_display->current_mode->w;
    rect->h = sdl_display->current_mode->h;
    वापस true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    Display *display = तथ्य->display;
    Atom _NET_WORKAREA;
    पूर्णांक real_format;
    Atom real_type;
    अचिन्हित दीर्घ वस्तुएँ_read = 0, वस्तुएँ_बायाँ = 0;
    अचिन्हित अक्षर *propdata = शून्य;
    bool परिणाम = false;

    अगर (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        वापस false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    पूर्णांक status = X11_XGetWindowProperty(display, Default_मूल_Window(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &वस्तुएँ_read,
                                    &वस्तुएँ_बायाँ, &propdata);
    अगर ((status == Success) && (वस्तुएँ_read >= 4)) {
        स्थिर दीर्घ *p = (दीर्घ *)propdata;
        स्थिर SDL_Rect usable = { (पूर्णांक)p[0], (पूर्णांक)p[1], (पूर्णांक)p[2], (पूर्णांक)p[3] };
        परिणाम = true;
        अगर (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    अगर (propdata) {
        X11_XFree(propdata);
    }

    वापस परिणाम;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11
