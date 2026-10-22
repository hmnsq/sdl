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

भिन्न X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    द्विगुण scale_factor = 0.0;

    // First use the forced scaling factor specified by the app/user
    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_FACTOR);
    सचे (hint && *hint) {
        द्विगुण मानम् = SDL_atof(hint);
        सचे (मानम् >= 1.0f && मानम् <= 10.0f) {
            scale_factor = मानम्;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    सचे (scale_factor <= 0.0) {
        पूर्णाङ्क status, real_format;
        Atom real_type;
        Atom res_mgr;
        unsigned long वस्तूनि_read, वस्तूनि_वामः;
        वर्ण *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        status = X11_XGetWindowProperty(display, मूलम्_Window(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &वस्तूनि_read, &वस्तूनि_वामः,
                                        (unsigned वर्ण **)&resource_manager);

        सचे (status == Success && resource_manager) {
            owns_resource_manager = true;
        } अञ्ञथा {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        सचे (resource_manager) {
            XrmDatabase db;
            Xrm_मानम् मानम्;
            वर्ण *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            सचे (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &मानम्)) {
                सचे (मानम्.addr && type && SDL_strcmp(type, "String") == 0) {
                    पूर्णाङ्क dpi = SDL_atoi(मानम्.addr);
                    scale_factor  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            सचे (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    सचे (scale_factor <= 0.0) {
        scale_factor = X11_Get_Xsettings_Client_Int_कुञ्चिका(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        सचे (scale_factor <= 0.0) {
            पूर्णाङ्क dpi = X11_Get_Xsettings_Client_Int_कुञ्चिका(client, "Xft/DPI", -1);
            सचे (dpi > 0) {
                scale_factor = (द्विगुण) dpi / 1024.0;
                scale_factor /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    सचे (scale_factor <= 0.0) {
        ध्रुव वर्ण *scale_str = SDL_getenv("GDK_SCALE");
        सचे (scale_str) {
            scale_factor = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    सचे (scale_factor <= 0.0) {
        scale_factor = 1.0;
    }

    पटिनिवत्त (भिन्न)scale_factor;
}

भिन्न X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    पटिनिवत्त X11_GetGlobalContentScale(_this->internal->display, _this->internal->xsettings_data.xsettings);
}

स्थिर bool get_visualinfo(Display *display, पूर्णाङ्क screen, XVisualInfo *vinfo)
{
    ध्रुव वर्ण *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    पूर्णाङ्क depth;

    // Look for an exact visual, if requested
    सचे (visual_id && *visual_id) {
        XVisualInfo *vi, template;
        पूर्णाङ्क nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(visual_id, रिक्त, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        सचे (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            पटिनिवत्त true;
        }
    }

    depth = DefaultDepth(display, screen);
    सचे ((X11_UseDirectColorVisuals() &&
         X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
        पटिनिवत्त true;
    }
    पटिनिवत्त false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    पूर्णाङ्क nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    सचे (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        पटिनिवत्त true;
    }
    पटिनिवत्त false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    सचे (vinfo->class == DirectColor || vinfo->class == TrueColor) {
        पूर्णाङ्क bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_mask;
        Gmask = vinfo->visual->green_mask;
        Bmask = vinfo->visual->blue_mask;
        सचे (vinfo->depth == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } अञ्ञथा {
            Amask = 0;
        }

        bpp = vinfo->depth;
        सचे (bpp == 24) {
            पूर्णाङ्क i, n;
            XPixmap_Format_मानानि *p = X11_XListPixmapFormats(display, &n);
            सचे (p) {
                अत्थाय (i = 0; i < n; ++i) {
                    सचे (p[i].depth == 24) {
                        bpp = p[i].bits_per_pixel;
                        भङ्ग;
                    }
                }
                X11_XFree(p);
            }
        }

        पटिनिवत्त SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    सचे (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        विकल्प (vinfo->depth) {
        पक्ष 8:
            पटिनिवत्त SDL_PIXELFORMAT_INDEX8;
        पक्ष 4:
            सचे (BitmapBitOrder(display) == LSBFirst) {
                पटिनिवत्त SDL_PIXELFORMAT_INDEX4LSB;
            } अञ्ञथा {
                पटिनिवत्त SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        पक्ष 1:
            सचे (BitmapBitOrder(display) == LSBFirst) {
                पटिनिवत्त SDL_PIXELFORMAT_INDEX1LSB;
            } अञ्ञथा {
                पटिनिवत्त SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    पटिनिवत्त SDL_PIXELFORMAT_UNKNOWN;
}

स्थिर SDL_DisplayID X11_AddGenericDisplay(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    ध्रुव पूर्णाङ्क default_screen = DefaultScreen(dpy);
    Screen *screen = ScreenOfDisplay(dpy, default_screen);
    पूर्णाङ्क scanline_pad, n, i;
    SDL_DisplayModeData *modedata;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    XPixmap_Format_मानानि *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    सचे (!get_visualinfo(dpy, default_screen, &vinfo)) {
        पटिनिवत्त SDL_SetError("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    सचे (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        पटिनिवत्त SDL_SetError("Palettized video modes are no longer supported");
    }

    SDL_zero(mode);
    mode.w = WidthOfScreen(screen);
    mode.h = HeightOfScreen(screen);
    mode.format = pixelformat;

    displaydata = (SDL_DisplayData *)SDL_calloc(1, परिमाण(*displaydata));
    सचे (!displaydata) {
        पटिनिवत्त false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, परिमाण(SDL_DisplayModeData));
    सचे (!modedata) {
        SDL_free(displaydata);
        पटिनिवत्त false;
    }
    mode.internal = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    सचे (pixmapformats) {
        अत्थाय (i = 0; i < n; ++i) {
            सचे (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                भङ्ग;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (वर्ण *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_mode = mode;
    display.internal = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    पटिनिवत्त SDL_AddVideoDisplay(&display, send_event);
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR

स्थिर शून्य X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
    सचे (displays) {
        अत्थाय (पूर्णाङ्क i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ध्रुव SDL_DisplayData *displaydata = display->internal;
            सचे (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

स्थिर bool CheckXRandR(Display *display, पूर्णाङ्क *major, पूर्णाङ्क *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ifdef XRANDR_DISABLED_BY_DEFAULT
    सचे (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#endif
        पटिनिवत्त false;
    }
#अञ्ञथा
    सचे (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#endif
        पटिनिवत्त false;
    }
#endif // XRANDR_DISABLED_BY_DEFAULT

    सचे (!SDL_X11_HAVE_XRANDR) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#endif
        पटिनिवत्त false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    सचे (!X11_XRRQueryVersion(display, major, minor)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#endif
        *major = *minor = 0;
        पटिनिवत्त false;
    }
#ifdef X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#endif
    पटिनिवत्त true;
}

#define XRANDR_ROTATION_वामः  (1 << 1)
#define XRANDR_ROTATION_दक्षिणः (1 << 3)

स्थिर शून्य CalculateXRandRRefreshRate(ध्रुव XRRModeInfo *info, पूर्णाङ्क *numerator, पूर्णाङ्क *denominator)
{
    unsigned पूर्णाङ्क vTotal = info->vTotal;

    सचे (info->modeFlags & RR_DoubleScan) {
        // doublescan doubles the number of lines
        vTotal *= 2;
    }

    सचे (info->modeFlags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        vTotal /= 2;
    }

    सचे (info->hTotal && vTotal) {
        *numerator = info->dotClock;
        *denominator = (info->hTotal * vTotal);
    } अञ्ञथा {
        *numerator = 0;
        *denominator = 0;
    }
}

स्थिर bool SetXRandRModeInfo(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode modeID, SDL_DisplayMode *mode)
{
    पूर्णाङ्क i;
    अत्थाय (i = 0; i < res->nmode; ++i) {
        ध्रुव XRRModeInfo *info = &res->modes[i];
        सचे (info->id == modeID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtcTransformAttributes *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            सचे (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            सचे (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            सचे (rotation & (XRANDR_ROTATION_वामः | XRANDR_ROTATION_दक्षिणः)) {
                mode->w = (info->height * scale_w + 0xffff) >> 16;
                mode->h = (info->width * scale_h + 0xffff) >> 16;
            } अञ्ञथा {
                mode->w = (info->width * scale_w + 0xffff) >> 16;
                mode->h = (info->height * scale_h + 0xffff) >> 16;
            }
            CalculateXRandRRefreshRate(info, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
            mode->internal->xrandr_mode = modeID;
#ifdef X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (पूर्णाङ्क)modeID,
                    mode->screen_w, mode->screen_h, mode->refresh_rate_numerator, mode->refresh_rate_denominator);
#endif
            पटिनिवत्त true;
        }
    }
    पटिनिवत्त false;
}

स्थिर bool Get_मूलम्_Window_Cardinal_Property(Display *dpy, पूर्णाङ्क screen, ध्रुव वर्ण *name, Uint32 *मानम्)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    सचे (atom == None) {
        पटिनिवत्त false;
    }

    पूर्णाङ्क real_format;
    Atom real_type;
    unsigned long वस्तूनि_read = 0, वस्तूनि_वामः = 0;
    unsigned वर्ण *propdata = रिक्त;
    पूर्णाङ्क status;
    bool result = false;

    status = X11_XGetWindowProperty(dpy, मूलम्_Window(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
    सचे (status == Success && propdata) {
        सचे (real_type == XA_CARDINAL && वस्तूनि_read > 0) {
            विकल्प (real_format) {
            पक्ष 8:
                *मानम् = propdata[0];
                भङ्ग;
            पक्ष 16:
                *मानम् = propdata[0] | (propdata[1] << 8);
                भङ्ग;
            स्वभाव:
                *मानम् = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                भङ्ग;
            }
            result = true;
        }
        X11_XFree(propdata);
    }
    पटिनिवत्त result;
}

स्थिर bool Get_मूलम्_Window_Bool_Property(Display *dpy, पूर्णाङ्क screen, ध्रुव वर्ण *name, bool *मानम्)
{
    Uint32 v;
    सचे (Get_मूलम्_Window_Cardinal_Property(dpy, screen, name, &v)) {
        *मानम् = (v != 0);
        पटिनिवत्त true;
    }
    पटिनिवत्त false;
}

स्थिर bool Get_मूलम्_Window_Float_Property(Display *dpy, पूर्णाङ्क screen, ध्रुव वर्ण *name, भिन्न *मानम्)
{
    Uint32 v;
    सचे (Get_मूलम्_Window_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(मानम्, &v, परिमाण(v));
        पटिनिवत्त true;
    }
    पटिनिवत्त false;
}

स्थिर bool IsSteamDeckOLEDDisplay(ध्रुव MonitorInfo *info)
{
    सचे (SDL_strcmp(info->manufacturer_code, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        सचे (info->product_code == 0x3003 || info->product_code == 0x3004) {
            पटिनिवत्त true;
        }
    }
    पटिनिवत्त false;
}

स्थिर भिन्न GetGamescopeSDRWhiteLevel(Display *dpy, पूर्णाङ्क screen, ध्रुव MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    सचे (!dpy) {
        पटिनिवत्त 0.0f;
    }

    भिन्न SDR_white_level = 0.0f;
    bool external_display = false;
    सचे (Get_मूलम्_Window_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_मूलम्_Window_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } अञ्ञथा सचे (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (भिन्न)info->max_luminance / 3.0f;
    } अञ्ञथा {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    पटिनिवत्त SDR_white_level;
}

स्थिर MonitorInfo *GetMonitorInfo(Display *dpy, पूर्णाङ्क screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = रिक्त;
    पूर्णाङ्क real_format;
    Atom real_type;
    unsigned long वस्तूनि_read = 0, वस्तूनि_वामः = 0;
    unsigned वर्ण *propdata = रिक्त;
    पूर्णाङ्क status;

    *gamescope = false;

    सचे (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_PATH = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        सचे (GAMESCOPE_DISPLAY_EDID_PATH != None) {
            status = X11_XGetWindowProperty(dpy, मूलम्_Window(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_PATH, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
            सचे (status == Success && propdata) {
                size_t size = 0;
                शून्य *data = SDL_LoadFile((वर्ण *)propdata, &size);
                सचे (data) {
                    info = decode_edid((uchar *)data, size);
                    सचे (info) {
                        *gamescope = true;
                    }
                    SDL_free(data);
                }
            }
            सचे (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    सचे (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        सचे (EDID != None) {
            पूर्णाङ्क nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            अत्थाय (पूर्णाङ्क i = 0; i < nprop; ++i) {
                सचे (props[i] == EDID) {
                    status = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
                    सचे (status == Success && propdata) {
                        info = decode_edid(propdata, वस्तूनि_read);
                    }
                    सचे (propdata) {
                        X11_XFree(propdata);
                    }
                    भङ्ग;
                }
            }

            सचे (props) {
                X11_XFree(props);
            }
        }
    }

#ifdef X11MODES_DEBUG
    सचे (info) {
        dump_monitor_info(info);
    }
#endif
    पटिनिवत्त info;
}

स्थिर शून्य SetXRandRDisplayName(MonitorInfo *info, वर्ण *name, size_t namelen, unsigned long widthmm, unsigned long heightmm)
{
    सचे (info) {
        SDL_strlcpy(name, info->dsc_product_name, namelen);
    }

    पूर्णाङ्क inches = (पूर्णाङ्क)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    सचे (*name && inches) {
        ध्रुव size_t len = SDL_strlen(name);
        (शून्य)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ifdef X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#endif
}

स्थिर bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, पूर्णाङ्क screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, वर्ण *display_name, size_t display_name_size)
{
    XRROutputInfo *output_info;
    पूर्णाङ्क display_x, display_y;
    unsigned long display_mm_width, display_mm_height;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    SDL_DisplayModeData *modedata;
    RRMode modeID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_मानानि *pixmapformats;
    पूर्णाङ्क scanline_pad;
    पूर्णाङ्क i, n;

    सचे (!display || !display_name) {
        पटिनिवत्त false; // invalid parameters
    }

    सचे (!get_visualinfo(dpy, screen, &vinfo)) {
        पटिनिवत्त false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    सचे (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        पटिनिवत्त false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    सचे (pixmapformats) {
        अत्थाय (i = 0; i < n; i++) {
            सचे (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                भङ्ग;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    सचे (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        पटिनिवत्त false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_size);
    display_mm_width = output_info->mm_width;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    सचे (!crtc) {
        पटिनिवत्त false; // oh well, ignore it.
    }

    SDL_zero(mode);
    modeID = crtc->mode;
    mode.w = crtc->width;
    mode.h = crtc->height;
    mode.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_DisplayData *)SDL_calloc(1, परिमाण(*displaydata));
    सचे (!displaydata) {
        पटिनिवत्त false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, परिमाण(SDL_DisplayModeData));
    सचे (!modedata) {
        SDL_free(displaydata);
        पटिनिवत्त false;
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
    SDL_strlcpy(displaydata->connector_name, display_name, परिमाण(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    SetXRandRModeInfo(dpy, res, output_crtc, modeID, &mode);
    SetXRandRDisplayName(info, display_name, display_name_size, display_mm_width, display_mm_height);

    SDL_zero(*display);
    सचे (*display_name) {
        display->name = display_name;
    }
    display->desktop_mode = mode;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->internal = displaydata;

    सचे (info) {
        भिन्न SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        सचे (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } अञ्ञथा {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ifdef X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#endif
        सचे (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (भिन्न)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    पटिनिवत्त true;
}

स्थिर bool X11_AddXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, पूर्णाङ्क screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    वर्ण display_name[128];

    सचे (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, परिमाण(display_name))) {
        पटिनिवत्त true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    सचे (displayID == 0) {
        पटिनिवत्त false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    सचे (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    पटिनिवत्त true;
}


स्थिर bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, पूर्णाङ्क screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    वर्ण display_name[128];

    सचे (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, परिमाण(display_name))) {
        पटिनिवत्त false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_SetDesktopDisplayMode(existing_display, &display.desktop_mode);

    // update bounds
    सचे (existing_display->internal->x != display.internal->x ||
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

    पटिनिवत्त true;
}

स्थिर XRRScreenResources *X11_GetScreenResources(Display *dpy, पूर्णाङ्क screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, मूलम्_Window(dpy, screen));
    सचे (!res || res->noutput == 0) {
        सचे (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, मूलम्_Window(dpy, screen));
    }
    पटिनिवत्त res;
}

शून्य X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    ध्रुव पूर्णाङ्क screencount = Screen_गणनम्(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
    सचे (!displays) {
        पटिनिवत्त;
    }

    अत्थाय (पूर्णाङ्क screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        सचे (!res) {
            अनुवर्त;
        }

        अत्थाय (पूर्णाङ्क i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ध्रुव SDL_DisplayData *displaydata = display->internal;
            सचे (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

स्थिर शून्य X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    ध्रुव पूर्णाङ्क screencount = Screen_गणनम्(dpy);
    पूर्णाङ्क अङ्कः_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&अङ्कः_displays);
    सचे (!displays) {
        पटिनिवत्त;
    }

    अत्थाय (पूर्णाङ्क screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        सचे (!res) {
            अनुवर्त;
        }

        अत्थाय (पूर्णाङ्क output = 0; output < res->noutput; output++) {
            अत्थाय (पूर्णाङ्क i = 0; i < अङ्कः_displays; ++i) {
                सचे (!displays[i]) {
                    // We already removed this display from the list
                    अनुवर्त;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                ध्रुव SDL_DisplayData *displaydata = display->internal;
                सचे (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    भङ्ग;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    अत्थाय (पूर्णाङ्क i = 0; i < अङ्कः_displays; ++i) {
        सचे (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ध्रुव SDL_DisplayData *displaydata = display->internal;
            सचे (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

स्थिर शून्य X11_HandleXRandROutputChange(SDL_VideoDevice *_this, ध्रुव XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = रिक्त;
    पूर्णाङ्क i;

#सचे 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (unsigned पूर्णाङ्क) ev->output, (unsigned पूर्णाङ्क) ev->crtc, (unsigned पूर्णाङ्क) ev->mode, (unsigned पूर्णाङ्क) ev->rotation, (unsigned पूर्णाङ्क) ev->connection);
#endif

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(रिक्त);
    सचे (displays) {
        अत्थाय (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            ध्रुव SDL_DisplayData *displaydata = thisdisplay->internal;
            सचे (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                भङ्ग;
            }
        }
        SDL_free(displays);
    }

    सचे (ev->connection == RR_Disconnected) { // output is going away
        सचे (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            सचे (_this->अङ्कः_displays == 1) {
                generic_display = X11_AddGenericDisplay(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            सचे (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } अञ्ञथा सचे (ev->connection == RR_Connected) { // output is coming online
        सचे (!display) {
            Display *dpy = ev->display;
            ध्रुव पूर्णाङ्क screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            सचे (res) {
                X11_AddXRandRDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

शून्य X11_HandleXRandREvent(SDL_VideoDevice *_this, ध्रुव XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_assert(xevent->type == (videodata->xrandr_event_base + RRNotify));

    विकल्प (((ध्रुव XRRNotifyEvent *)xevent)->subtype) {
    पक्ष RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (ध्रुव XRROutputChangeNotifyEvent *)xevent);
        भङ्ग;
    स्वभाव:
        भङ्ग;
    }
}

स्थिर शून्य X11_SortOutputsByPriorityHint(SDL_VideoDevice *_this)
{
    ध्रुव वर्ण *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    सचे (name_hint) {
        वर्ण *saveptr;
        वर्ण *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(परिमाण(SDL_VideoDisplay *) * _this->अङ्कः_displays);

        सचे (str && sorted_list) {
            पूर्णाङ्क sorted_index = 0;

            // Sort the requested displays to the front of the list.
            ध्रुव वर्ण *token = SDL_strtok_r(str, ",", &saveptr);
            याव (token) {
                अत्थाय (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    सचे (d) {
                        SDL_DisplayData *data = d->internal;
                        सचे (SDL_strcmp(token, data->connector_name) == 0) {
                            sorted_list[sorted_index++] = d;
                            _this->displays[i] = रिक्त;
                            भङ्ग;
                        }
                    }
                }

                token = SDL_strtok_r(रिक्त, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            अत्थाय (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
                सचे (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, परिमाण(SDL_VideoDisplay *) * _this->अङ्कः_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

स्थिर bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    ध्रुव पूर्णाङ्क screencount = Screen_गणनम्(dpy);
    ध्रुव पूर्णाङ्क default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, मूलम्_Window(dpy, default_screen));
    पूर्णाङ्क xrandr_error_base = 0;
    पूर्णाङ्क looking_for_primary;
    पूर्णाङ्क output;
    पूर्णाङ्क screen;

    सचे (!X11_XRRQueryExtension(dpy, &data->xrandr_event_base, &xrandr_error_base)) {
        पटिनिवत्त SDL_SetError("XRRQueryExtension failed");
    }

    अत्थाय (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        अत्थाय (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            सचे (looking_for_primary && (screen != default_screen)) {
                अनुवर्त;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            सचे (!res) {
                अनुवर्त;
            }

            अत्थाय (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                सचे ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    अनुवर्त;
                }
                सचे (!X11_AddXRandRDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    भङ्ग;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_निवेशः(dpy, मूलम्_Window(dpy, screen), RROutputChangeNotifyMask);
        }
    }

    सचे (_this->अङ्कः_displays == 0) {
        पटिनिवत्त SDL_SetError("No available displays");
    }

    X11_SortOutputsByPriorityHint(_this);

    पटिनिवत्त true;
}
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
स्थिर bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    सचे (X11_AddGenericDisplay(_this, true) == 0) {
        पटिनिवत्त false;
    }
    पटिनिवत्त true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_VideoData *data = _this->internal;
        पूर्णाङ्क xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        सचे (CheckXRandR(data->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            पटिनिवत्त true;
        }
    }
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    पटिनिवत्त X11_InitModes_StdXlib(_this);
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

    सचे (data->use_xrandr) {
        Display *display = _this->internal->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, मूलम्_Window(display, data->screen));
        सचे (res) {
            SDL_DisplayModeData *modedata;
            XRROutputInfo *output_info;
            पूर्णाङ्क i;

            output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
            सचे (output_info && output_info->connection != RR_Disconnected) {
                अत्थाय (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_DisplayModeData *)SDL_calloc(1, परिमाण(SDL_DisplayModeData));
                    सचे (!modedata) {
                        अनुवर्त;
                    }
                    mode.internal = modedata;

                    सचे (!SetXRandRModeInfo(display, res, output_info->crtc, output_info->modes[i], &mode) ||
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
    पटिनिवत्त true;
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
स्थिर पूर्णाङ्क (*PreXRRSetScreenSizeErrorHandler)(Display *, XErrorEvent *) = रिक्त;
स्थिर पूर्णाङ्क SDL_XRRSetScreenSizeErrHandler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    सचे ((e->error_code == BadMatch) || (e->error_code == Bad_मानम्)) {
        पटिनिवत्त 0;
    }

    पटिनिवत्त PreXRRSetScreenSizeErrorHandler(d, e);
}
#endif

bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *data = sdl_display->internal;

    viddata->last_mode_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    सचे (!viddata->is_xwayland) {
        सचे (sdl_display->current_mode != mode) {
            data->mode_switch_deadline_ns = SDL_GetTicksNS() + MODE_SWITCH_TIMEOUT_NS;
        } अञ्ञथा {
            data->mode_switch_deadline_ns = 0;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    सचे (data->use_xrandr) {
        Display *display = viddata->display;
        SDL_DisplayModeData *modedata = mode->internal;
        पूर्णाङ्क mm_width, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        Status status;

        res = X11_XRRGetScreenResources(display, मूलम्_Window(display, data->screen));
        सचे (!res) {
            पटिनिवत्त SDL_SetError("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
        सचे (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            पटिनिवत्त SDL_SetError("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        सचे (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            पटिनिवत्त SDL_SetError("Couldn't get XRandR crtc info");
        }

        सचे (crtc->mode == modedata->xrandr_mode) {
#ifdef X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->mode, crtc->width, crtc->height);
#endif
            status = Success;
            गच्छ freeInfo;
        }

        X11_XGrabServer(display);
        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, रिक्त, 0);
        सचे (status != Success) {
            गच्छ ungrabServer;
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
        X11_XRRSetScreenSize(display, मूलम्_Window(display, data->screen),
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

        सचे (status != Success) {
            पटिनिवत्त SDL_SetError("X11_XRRSetCrtcConfig failed");
        }
    }
#अञ्ञथा
    (शून्य)data;
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    पटिनिवत्त true;
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
    पटिनिवत्त true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    Atom _NET_WORKAREA;
    पूर्णाङ्क real_format;
    Atom real_type;
    unsigned long वस्तूनि_read = 0, वस्तूनि_वामः = 0;
    unsigned वर्ण *propdata = रिक्त;
    bool result = false;

    सचे (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        पटिनिवत्त false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    पूर्णाङ्क status = X11_XGetWindowProperty(display, Default_मूलम्_Window(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &वस्तूनि_read,
                                    &वस्तूनि_वामः, &propdata);
    सचे ((status == Success) && (वस्तूनि_read >= 4)) {
        ध्रुव long *p = (long *)propdata;
        ध्रुव SDL_Rect usable = { (पूर्णाङ्क)p[0], (पूर्णाङ्क)p[1], (पूर्णाङ्क)p[2], (पूर्णाङ्क)p[3] };
        result = true;
        सचे (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    सचे (propdata) {
        X11_XFree(propdata);
    }

    पटिनिवत्त result;
}

#endif // SDL_VIDEO_DRIVER_X11
