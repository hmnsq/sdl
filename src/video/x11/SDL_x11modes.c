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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11

#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11settings.h"
#అన్తర్భావ "edid.h"
#అన్తర్భావ "../../events/SDL_displayevents_c.h"
#అన్తర్భావ "../SDL_pixels_c.h"

// #define X11MODES_DEBUG

/* Timeout and revert mode switches if the timespan has elapsed without the window becoming fullscreen.
 * 5 seconds seems good from testing.
 */
#నిర్వచించు బహుళకం_SWITCH_TIMEOUT_NS SDL_NS_చొప్పున_రెండవ * 5

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

దశాంశం X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    ద్విగుణ scale_గుణకం_2 = 0.0;

    // First use the forced scaling factor specified by the app/user
    స్థిరరాశి అక్షరం *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_గుణకం);
    ఒకవేళ (hint && *hint) {
        ద్విగుణ విలువ = SDL_atof(hint);
        ఒకవేళ (విలువ >= 1.0f && విలువ <= 10.0f) {
            scale_గుణకం_2 = విలువ;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    ఒకవేళ (scale_గుణకం_2 <= 0.0) {
        పూర్ణాంకం స్థితి_2, real_format;
        Atom real_type;
        Atom res_mgr;
        గుర్తులేని దీర్ఘ వస్తువులు_read, వస్తువులు_ఎడమ;
        అక్షరం *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        స్థితి_2 = X11_XGet_కిటికీ_Property(display, మూలం_కిటికీ(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &వస్తువులు_read, &వస్తువులు_ఎడమ,
                                        (గుర్తులేని అక్షరం **)&resource_manager);

        ఒకవేళ (స్థితి_2 == Success && resource_manager) {
            owns_resource_manager = true;
        } లేకపోతే {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        ఒకవేళ (resource_manager) {
            XrmDatabase db;
            Xrm_విలువ విలువ;
            అక్షరం *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            ఒకవేళ (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &విలువ)) {
                ఒకవేళ (విలువ.addr && type && SDL_strcmp(type, "String") == 0) {
                    పూర్ణాంకం dpi = SDL_atoi(విలువ.addr);
                    scale_గుణకం_2  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            ఒకవేళ (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    ఒకవేళ (scale_గుణకం_2 <= 0.0) {
        scale_గుణకం_2 = X11_Get_Xsettings_Client_Int_కీలకం(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        ఒకవేళ (scale_గుణకం_2 <= 0.0) {
            పూర్ణాంకం dpi = X11_Get_Xsettings_Client_Int_కీలకం(client, "Xft/DPI", -1);
            ఒకవేళ (dpi > 0) {
                scale_గుణకం_2 = (ద్విగుణ) dpi / 1024.0;
                scale_గుణకం_2 /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    ఒకవేళ (scale_గుణకం_2 <= 0.0) {
        స్థిరరాశి అక్షరం *scale_str = SDL_getenv("GDK_SCALE");
        ఒకవేళ (scale_str) {
            scale_గుణకం_2 = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    ఒకవేళ (scale_గుణకం_2 <= 0.0) {
        scale_గుణకం_2 = 1.0;
    }

    తిరిగి (దశాంశం)scale_గుణకం_2;
}

దశాంశం X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    తిరిగి X11_GetGlobalContentScale(_this->అంతర్గత->display, _this->అంతర్గత->xsettings_దత్తాంశం.xsettings);
}

స్థిర bool get_visualinfo(Display *display, పూర్ణాంకం screen, XVisualInfo *vinfo)
{
    స్థిరరాశి అక్షరం *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    పూర్ణాంకం లోతు_2;

    // Look for an exact visual, if requested
    ఒకవేళ (visual_id && *visual_id) {
        XVisualInfo *vi, మూస;
        పూర్ణాంకం nvis;

        SDL_zero(మూస);
        మూస.visualid = SDL_strtol(visual_id, ఖాళీ, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &మూస, &nvis);
        ఒకవేళ (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            తిరిగి true;
        }
    }

    లోతు_2 = Default_లోతు(display, screen);
    ఒకవేళ ((X11_Use_ప్రత్యక్ష_Color_Visuals() &&
         X11_XMatchVisualInfo(display, screen, లోతు_2, ప్రత్యక్ష_Color, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, లోతు_2, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, లోతు_2, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, లోతు_2, StaticColor, vinfo)) {
        తిరిగి true;
    }
    తిరిగి false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    పూర్ణాంకం nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    ఒకవేళ (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        తిరిగి true;
    }
    తిరిగి false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    ఒకవేళ (vinfo->class == ప్రత్యక్ష_Color || vinfo->class == TrueColor) {
        పూర్ణాంకం bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_ముసుగు;
        Gmask = vinfo->visual->green_ముసుగు;
        Bmask = vinfo->visual->blue_ముసుగు;
        ఒకవేళ (vinfo->లోతు_2 == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } లేకపోతే {
            Amask = 0;
        }

        bpp = vinfo->లోతు_2;
        ఒకవేళ (bpp == 24) {
            పూర్ణాంకం i, n;
            XPixmap_Format_విలువలు *p = X11_XListPixmapFormats(display, &n);
            ఒకవేళ (p) {
                కొరకు (i = 0; i < n; ++i) {
                    ఒకవేళ (p[i].లోతు_2 == 24) {
                        bpp = p[i].బిట్లు_చొప్పున_pixel;
                        ఆపు;
                    }
                }
                X11_XFree(p);
            }
        }

        తిరిగి SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    ఒకవేళ (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        ఎంపిక (vinfo->లోతు_2) {
        స్థితి 8:
            తిరిగి SDL_PIXELFORMAT_INDEX8;
        స్థితి 4:
            ఒకవేళ (Bitmap_బిట్టు_క్రమం(display) == LSBFirst) {
                తిరిగి SDL_PIXELFORMAT_INDEX4LSB;
            } లేకపోతే {
                తిరిగి SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        స్థితి 1:
            ఒకవేళ (Bitmap_బిట్టు_క్రమం(display) == LSBFirst) {
                తిరిగి SDL_PIXELFORMAT_INDEX1LSB;
            } లేకపోతే {
                తిరిగి SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    తిరిగి SDL_PIXELFORMAT_UNKNOWN;
}

స్థిర SDL_DisplayID X11_కూడు_Generic_Display(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    Display *dpy = దత్తాంశం->display;
    స్థిరరాశి పూర్ణాంకం default_screen = DefaultScreen(dpy);
    Screen *screen = Screen_యొక్క_Display(dpy, default_screen);
    పూర్ణాంకం scanline_pad, n, i;
    SDL_Display_బహుళకం_దత్తాంశం *modedata;
    SDL_Display_దత్తాంశం *displaydata;
    SDL_Display_బహుళకం బహుళకం;
    XPixmap_Format_విలువలు *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    ఒకవేళ (!get_visualinfo(dpy, default_screen, &vinfo)) {
        తిరిగి SDL_సమితి_Error("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ఒకవేళ (SDL_ISPIXELFORMAT_సూచీకృత(pixelformat)) {
        తిరిగి SDL_సమితి_Error("Palettized video modes are no longer supported");
    }

    SDL_zero(బహుళకం);
    బహుళకం.w = వెడల్పు_యొక్క_Screen(screen);
    బహుళకం.h = ఎత్తు_యొక్క_Screen(screen);
    బహుళకం.format = pixelformat;

    displaydata = (SDL_Display_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*displaydata));
    ఒకవేళ (!displaydata) {
        తిరిగి false;
    }

    modedata = (SDL_Display_బహుళకం_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Display_బహుళకం_దత్తాంశం));
    ఒకవేళ (!modedata) {
        SDL_free(displaydata);
        తిరిగి false;
    }
    బహుళకం.అంతర్గత = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->లోతు_2 = vinfo.లోతు_2;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ఒకవేళ (pixmapformats) {
        కొరకు (i = 0; i < n; ++i) {
            ఒకవేళ (pixmapformats[i].లోతు_2 == vinfo.లోతు_2) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ఆపు;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (అక్షరం *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_బహుళకం = బహుళకం;
    display.అంతర్గత = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    తిరిగి SDL_కూడు_Video_Display(&display, send_event);
}

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR

స్థిర శూన్య X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(ఖాళీ);
    ఒకవేళ (displays) {
        కొరకు (పూర్ణాంకం i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            స్థిరరాశి SDL_Display_దత్తాంశం *displaydata = display->అంతర్గత;
            ఒకవేళ (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

స్థిర bool CheckXRandR(Display *display, పూర్ణాంకం *major, పూర్ణాంకం *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#నిర్వచితమైతే XRANDR_DISABLED_BY_DEFAULT
    ఒకవేళ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#నిర్వచితమైతే X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#అయితే_ముగింపు
        తిరిగి false;
    }
#లేకపోతే
    ఒకవేళ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#నిర్వచితమైతే X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#అయితే_ముగింపు
        తిరిగి false;
    }
#అయితే_ముగింపు // XRANDR_DISABLED_BY_DEFAULT

    ఒకవేళ (!SDL_X11_HAVE_XRANDR) {
#నిర్వచితమైతే X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#అయితే_ముగింపు
        తిరిగి false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    ఒకవేళ (!X11_XRRQuery_సంస్కరణ(display, major, minor)) {
#నిర్వచితమైతే X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#అయితే_ముగింపు
        *major = *minor = 0;
        తిరిగి false;
    }
#నిర్వచితమైతే X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#అయితే_ముగింపు
    తిరిగి true;
}

#నిర్వచించు XRANDR_ROTATION_ఎడమ  (1 << 1)
#నిర్వచించు XRANDR_ROTATION_కుడి (1 << 3)

స్థిర శూన్య Calculate_XRand_RRefresh_రేటు(స్థిరరాశి XRRModeInfo *info, పూర్ణాంకం *numerator, పూర్ణాంకం *denominator)
{
    గుర్తులేని పూర్ణాంకం v_మొత్తం_2 = info->v_మొత్తం_2;

    ఒకవేళ (info->బహుళకం_Flags & RR_Double_పరిశీలన) {
        // doublescan doubles the number of lines
        v_మొత్తం_2 *= 2;
    }

    ఒకవేళ (info->బహుళకం_Flags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        v_మొత్తం_2 /= 2;
    }

    ఒకవేళ (info->h_మొత్తం_2 && v_మొత్తం_2) {
        *numerator = info->dotClock;
        *denominator = (info->h_మొత్తం_2 * v_మొత్తం_2);
    } లేకపోతే {
        *numerator = 0;
        *denominator = 0;
    }
}

స్థిర bool సమితి_XRand_RMode_Info(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode బహుళకం_ID, SDL_Display_బహుళకం *బహుళకం)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < res->nmode; ++i) {
        స్థిరరాశి XRRModeInfo *info = &res->modes[i];
        ఒకవేళ (info->id == బహుళకం_ID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtc_Transform_లక్షణాలు *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            ఒకవేళ (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            ఒకవేళ (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.మాతృక[0][0];
                scale_h = attr->currentTransform.మాతృక[1][1];
                X11_XFree(attr);
            }

            ఒకవేళ (rotation & (XRANDR_ROTATION_ఎడమ | XRANDR_ROTATION_కుడి)) {
                బహుళకం->w = (info->ఎత్తు * scale_w + 0xffff) >> 16;
                బహుళకం->h = (info->వెడల్పు * scale_h + 0xffff) >> 16;
            } లేకపోతే {
                బహుళకం->w = (info->వెడల్పు * scale_w + 0xffff) >> 16;
                బహుళకం->h = (info->ఎత్తు * scale_h + 0xffff) >> 16;
            }
            Calculate_XRand_RRefresh_రేటు(info, &బహుళకం->refresh_రేటు_numerator, &బహుళకం->refresh_రేటు_denominator);
            బహుళకం->అంతర్గత->xrandr_బహుళకం = బహుళకం_ID;
#నిర్వచితమైతే X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (పూర్ణాంకం)బహుళకం_ID,
                    బహుళకం->screen_w, బహుళకం->screen_h, బహుళకం->refresh_రేటు_numerator, బహుళకం->refresh_రేటు_denominator);
#అయితే_ముగింపు
            తిరిగి true;
        }
    }
    తిరిగి false;
}

స్థిర bool Get_మూలం_కిటికీ_Cardinal_Property(Display *dpy, పూర్ణాంకం screen, స్థిరరాశి అక్షరం *name, Uint32 *విలువ)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    ఒకవేళ (atom == None) {
        తిరిగి false;
    }

    పూర్ణాంకం real_format;
    Atom real_type;
    గుర్తులేని దీర్ఘ వస్తువులు_read = 0, వస్తువులు_ఎడమ = 0;
    గుర్తులేని అక్షరం *propdata = ఖాళీ;
    పూర్ణాంకం స్థితి_2;
    bool ఫలితం = false;

    స్థితి_2 = X11_XGet_కిటికీ_Property(dpy, మూలం_కిటికీ(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &వస్తువులు_read, &వస్తువులు_ఎడమ, &propdata);
    ఒకవేళ (స్థితి_2 == Success && propdata) {
        ఒకవేళ (real_type == XA_CARDINAL && వస్తువులు_read > 0) {
            ఎంపిక (real_format) {
            స్థితి 8:
                *విలువ = propdata[0];
                ఆపు;
            స్థితి 16:
                *విలువ = propdata[0] | (propdata[1] << 8);
                ఆపు;
            అప్రమేయ:
                *విలువ = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                ఆపు;
            }
            ఫలితం = true;
        }
        X11_XFree(propdata);
    }
    తిరిగి ఫలితం;
}

స్థిర bool Get_మూలం_కిటికీ_Bool_Property(Display *dpy, పూర్ణాంకం screen, స్థిరరాశి అక్షరం *name, bool *విలువ)
{
    Uint32 v;
    ఒకవేళ (Get_మూలం_కిటికీ_Cardinal_Property(dpy, screen, name, &v)) {
        *విలువ = (v != 0);
        తిరిగి true;
    }
    తిరిగి false;
}

స్థిర bool Get_మూలం_కిటికీ_Float_Property(Display *dpy, పూర్ణాంకం screen, స్థిరరాశి అక్షరం *name, దశాంశం *విలువ)
{
    Uint32 v;
    ఒకవేళ (Get_మూలం_కిటికీ_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(విలువ, &v, పరిమాణం(v));
        తిరిగి true;
    }
    తిరిగి false;
}

స్థిర bool IsSteamDeckOLEDDisplay(స్థిరరాశి MonitorInfo *info)
{
    ఒకవేళ (SDL_strcmp(info->manufacturer_సంకేతం, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        ఒకవేళ (info->లబ్ధం_సంకేతం == 0x3003 || info->లబ్ధం_సంకేతం == 0x3004) {
            తిరిగి true;
        }
    }
    తిరిగి false;
}

స్థిర దశాంశం GetGamescopeSDRWhiteLevel(Display *dpy, పూర్ణాంకం screen, స్థిరరాశి MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    ఒకవేళ (!dpy) {
        తిరిగి 0.0f;
    }

    దశాంశం SDR_white_level = 0.0f;
    bool external_display = false;
    ఒకవేళ (Get_మూలం_కిటికీ_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_మూలం_కిటికీ_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } లేకపోతే ఒకవేళ (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (దశాంశం)info->max_luminance / 3.0f;
    } లేకపోతే {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    తిరిగి SDR_white_level;
}

స్థిర MonitorInfo *GetMonitorInfo(Display *dpy, పూర్ణాంకం screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = ఖాళీ;
    పూర్ణాంకం real_format;
    Atom real_type;
    గుర్తులేని దీర్ఘ వస్తువులు_read = 0, వస్తువులు_ఎడమ = 0;
    గుర్తులేని అక్షరం *propdata = ఖాళీ;
    పూర్ణాంకం స్థితి_2;

    *gamescope = false;

    ఒకవేళ (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_మార్గం = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        ఒకవేళ (GAMESCOPE_DISPLAY_EDID_మార్గం != None) {
            స్థితి_2 = X11_XGet_కిటికీ_Property(dpy, మూలం_కిటికీ(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_మార్గం, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &వస్తువులు_read, &వస్తువులు_ఎడమ, &propdata);
            ఒకవేళ (స్థితి_2 == Success && propdata) {
                size_t కొలత = 0;
                శూన్య *దత్తాంశం = SDL_ఎక్కించు_File((అక్షరం *)propdata, &కొలత);
                ఒకవేళ (దత్తాంశం) {
                    info = decode_edid((uchar *)దత్తాంశం, కొలత);
                    ఒకవేళ (info) {
                        *gamescope = true;
                    }
                    SDL_free(దత్తాంశం);
                }
            }
            ఒకవేళ (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    ఒకవేళ (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        ఒకవేళ (EDID != None) {
            పూర్ణాంకం nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            కొరకు (పూర్ణాంకం i = 0; i < nprop; ++i) {
                ఒకవేళ (props[i] == EDID) {
                    స్థితి_2 = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &వస్తువులు_read, &వస్తువులు_ఎడమ, &propdata);
                    ఒకవేళ (స్థితి_2 == Success && propdata) {
                        info = decode_edid(propdata, వస్తువులు_read);
                    }
                    ఒకవేళ (propdata) {
                        X11_XFree(propdata);
                    }
                    ఆపు;
                }
            }

            ఒకవేళ (props) {
                X11_XFree(props);
            }
        }
    }

#నిర్వచితమైతే X11MODES_DEBUG
    ఒకవేళ (info) {
        dump_monitor_info(info);
    }
#అయితే_ముగింపు
    తిరిగి info;
}

స్థిర శూన్య సమితి_XRand_RDisplay_Name(MonitorInfo *info, అక్షరం *name, size_t namelen, గుర్తులేని దీర్ఘ widthmm, గుర్తులేని దీర్ఘ heightmm)
{
    ఒకవేళ (info) {
        SDL_strlcpy(name, info->dsc_లబ్ధం_name, namelen);
    }

    పూర్ణాంకం inches = (పూర్ణాంకం)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    ఒకవేళ (*name && inches) {
        స్థిరరాశి size_t len = SDL_strlen(name);
        (శూన్య)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#నిర్వచితమైతే X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#అయితే_ముగింపు
}

స్థిర bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, పూర్ణాంకం screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, అక్షరం *display_name, size_t display_name_కొలత)
{
    XRROutputInfo *output_info;
    పూర్ణాంకం display_x, display_y;
    గుర్తులేని దీర్ఘ display_mm_వెడల్పు, display_mm_ఎత్తు;
    SDL_Display_దత్తాంశం *displaydata;
    SDL_Display_బహుళకం బహుళకం;
    SDL_Display_బహుళకం_దత్తాంశం *modedata;
    RRMode బహుళకం_ID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_విలువలు *pixmapformats;
    పూర్ణాంకం scanline_pad;
    పూర్ణాంకం i, n;

    ఒకవేళ (!display || !display_name) {
        తిరిగి false; // invalid parameters
    }

    ఒకవేళ (!get_visualinfo(dpy, screen, &vinfo)) {
        తిరిగి false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ఒకవేళ (SDL_ISPIXELFORMAT_సూచీకృత(pixelformat)) {
        తిరిగి false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ఒకవేళ (pixmapformats) {
        కొరకు (i = 0; i < n; i++) {
            ఒకవేళ (pixmapformats[i].లోతు_2 == vinfo.లోతు_2) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ఆపు;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    ఒకవేళ (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        తిరిగి false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_కొలత);
    display_mm_వెడల్పు = output_info->mm_వెడల్పు;
    display_mm_ఎత్తు = output_info->mm_ఎత్తు;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    ఒకవేళ (!crtc) {
        తిరిగి false; // oh well, ignore it.
    }

    SDL_zero(బహుళకం);
    బహుళకం_ID = crtc->బహుళకం;
    బహుళకం.w = crtc->వెడల్పు;
    బహుళకం.h = crtc->ఎత్తు;
    బహుళకం.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_Display_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*displaydata));
    ఒకవేళ (!displaydata) {
        తిరిగి false;
    }

    modedata = (SDL_Display_బహుళకం_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Display_బహుళకం_దత్తాంశం));
    ఒకవేళ (!modedata) {
        SDL_free(displaydata);
        తిరిగి false;
    }

    modedata->xrandr_బహుళకం = బహుళకం_ID;
    బహుళకం.అంతర్గత = modedata;

    displaydata->screen = screen;
    displaydata->visual = vinfo.visual;
    displaydata->లోతు_2 = vinfo.లోతు_2;
    displaydata->scanline_pad = scanline_pad;
    displaydata->x = display_x;
    displaydata->y = display_y;
    displaydata->use_xrandr = true;
    displaydata->xrandr_output = outputid;
    SDL_strlcpy(displaydata->connector_name, display_name, పరిమాణం(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    సమితి_XRand_RMode_Info(dpy, res, output_crtc, బహుళకం_ID, &బహుళకం);
    సమితి_XRand_RDisplay_Name(info, display_name, display_name_కొలత, display_mm_వెడల్పు, display_mm_ఎత్తు);

    SDL_zero(*display);
    ఒకవేళ (*display_name) {
        display->name = display_name;
    }
    display->desktop_బహుళకం = బహుళకం;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->అంతర్గత = displaydata;

    ఒకవేళ (info) {
        దశాంశం SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        ఒకవేళ (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } లేకపోతే {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#నిర్వచితమైతే X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#అయితే_ముగింపు
        ఒకవేళ (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (దశాంశం)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    తిరిగి true;
}

స్థిర bool X11_కూడు_XRand_RDisplay(SDL_VideoDevice *_this, Display *dpy, పూర్ణాంకం screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    అక్షరం display_name[128];

    ఒకవేళ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, పరిమాణం(display_name))) {
        తిరిగి true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_కూడు_Video_Display(&display, false);
    ఒకవేళ (displayID == 0) {
        తిరిగి false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    ఒకవేళ (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    తిరిగి true;
}


స్థిర bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, పూర్ణాంకం screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    అక్షరం display_name[128];

    ఒకవేళ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, పరిమాణం(display_name))) {
        తిరిగి false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_సమితి_Desktop_Display_బహుళకం(existing_display, &display.desktop_బహుళకం);

    // update bounds
    ఒకవేళ (existing_display->అంతర్గత->x != display.అంతర్గత->x ||
        existing_display->అంతర్గత->y != display.అంతర్గత->y) {
        existing_display->అంతర్గత->x = display.అంతర్గత->x;
        existing_display->అంతర్గత->y = display.అంతర్గత->y;
        SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
    }

    // update scale
    SDL_సమితి_Display_Content_Scale(existing_display, display.content_scale);

    // update HDR properties
    SDL_సమితి_Display_HDRProperties(existing_display, &display.HDR);

    // SDL_DisplayData is updated piece-meal above, free our local copy of this data
    SDL_free(display.అంతర్గత);

    తిరిగి true;
}

స్థిర XRRScreenResources *X11_GetScreenResources(Display *dpy, పూర్ణాంకం screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, మూలం_కిటికీ(dpy, screen));
    ఒకవేళ (!res || res->noutput == 0) {
        ఒకవేళ (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, మూలం_కిటికీ(dpy, screen));
    }
    తిరిగి res;
}

శూన్య X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    స్థిరరాశి పూర్ణాంకం screencount = Screen_లెక్క(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(ఖాళీ);
    ఒకవేళ (!displays) {
        తిరిగి;
    }

    కొరకు (పూర్ణాంకం screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ఒకవేళ (!res) {
            కొనసాగు;
        }

        కొరకు (పూర్ణాంకం i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            స్థిరరాశి SDL_Display_దత్తాంశం *displaydata = display->అంతర్గత;
            ఒకవేళ (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

స్థిర శూన్య X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    స్థిరరాశి పూర్ణాంకం screencount = Screen_లెక్క(dpy);
    పూర్ణాంకం అంకె_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&అంకె_displays);
    ఒకవేళ (!displays) {
        తిరిగి;
    }

    కొరకు (పూర్ణాంకం screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ఒకవేళ (!res) {
            కొనసాగు;
        }

        కొరకు (పూర్ణాంకం output = 0; output < res->noutput; output++) {
            కొరకు (పూర్ణాంకం i = 0; i < అంకె_displays; ++i) {
                ఒకవేళ (!displays[i]) {
                    // We already removed this display from the list
                    కొనసాగు;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                స్థిరరాశి SDL_Display_దత్తాంశం *displaydata = display->అంతర్గత;
                ఒకవేళ (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    ఆపు;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    కొరకు (పూర్ణాంకం i = 0; i < అంకె_displays; ++i) {
        ఒకవేళ (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            స్థిరరాశి SDL_Display_దత్తాంశం *displaydata = display->అంతర్గత;
            ఒకవేళ (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

స్థిర శూన్య X11_HandleXRandROutputChange(SDL_VideoDevice *_this, స్థిరరాశి XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = ఖాళీ;
    పూర్ణాంకం i;

#ఒకవేళ 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (గుర్తులేని పూర్ణాంకం) ev->output, (గుర్తులేని పూర్ణాంకం) ev->crtc, (గుర్తులేని పూర్ణాంకం) ev->బహుళకం, (గుర్తులేని పూర్ణాంకం) ev->rotation, (గుర్తులేని పూర్ణాంకం) ev->connection);
#అయితే_ముగింపు

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(ఖాళీ);
    ఒకవేళ (displays) {
        కొరకు (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            స్థిరరాశి SDL_Display_దత్తాంశం *displaydata = thisdisplay->అంతర్గత;
            ఒకవేళ (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                ఆపు;
            }
        }
        SDL_free(displays);
    }

    ఒకవేళ (ev->connection == RR_Disconnected) { // output is going away
        ఒకవేళ (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            ఒకవేళ (_this->అంకె_displays == 1) {
                generic_display = X11_కూడు_Generic_Display(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            ఒకవేళ (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } లేకపోతే ఒకవేళ (ev->connection == RR_Connected) { // output is coming online
        ఒకవేళ (!display) {
            Display *dpy = ev->display;
            స్థిరరాశి పూర్ణాంకం screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ఒకవేళ (res) {
                X11_కూడు_XRand_RDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

శూన్య X11_HandleXRandREvent(SDL_VideoDevice *_this, స్థిరరాశి XEvent *xevent)
{
    SDL_Video_దత్తాంశం *videodata = _this->అంతర్గత;
    SDL_assert(xevent->type == (videodata->xrandr_event_పునాది + RRNotify));

    ఎంపిక (((స్థిరరాశి XRRNotifyEvent *)xevent)->subtype) {
    స్థితి RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (స్థిరరాశి XRROutputChangeNotifyEvent *)xevent);
        ఆపు;
    అప్రమేయ:
        ఆపు;
    }
}

స్థిర శూన్య X11_క్రమీకరించు_Outputs_By_ప్రాధాన్యత_Hint(SDL_VideoDevice *_this)
{
    స్థిరరాశి అక్షరం *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ప్రాధాన్యత);

    ఒకవేళ (name_hint) {
        అక్షరం *saveptr;
        అక్షరం *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(పరిమాణం(SDL_VideoDisplay *) * _this->అంకె_displays);

        ఒకవేళ (str && sorted_list) {
            పూర్ణాంకం sorted_సూచీ = 0;

            // Sort the requested displays to the front of the list.
            స్థిరరాశి అక్షరం *token = SDL_strtok_r(str, ",", &saveptr);
            అయితే (token) {
                కొరకు (పూర్ణాంకం i = 0; i < _this->అంకె_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    ఒకవేళ (d) {
                        SDL_Display_దత్తాంశం *దత్తాంశం = d->అంతర్గత;
                        ఒకవేళ (SDL_strcmp(token, దత్తాంశం->connector_name) == 0) {
                            sorted_list[sorted_సూచీ++] = d;
                            _this->displays[i] = ఖాళీ;
                            ఆపు;
                        }
                    }
                }

                token = SDL_strtok_r(ఖాళీ, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            కొరకు (పూర్ణాంకం i = 0; i < _this->అంకె_displays; ++i) {
                ఒకవేళ (_this->displays[i]) {
                    sorted_list[sorted_సూచీ++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, పరిమాణం(SDL_VideoDisplay *) * _this->అంకె_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

స్థిర bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    Display *dpy = దత్తాంశం->display;
    స్థిరరాశి పూర్ణాంకం screencount = Screen_లెక్క(dpy);
    స్థిరరాశి పూర్ణాంకం default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, మూలం_కిటికీ(dpy, default_screen));
    పూర్ణాంకం xrandr_error_పునాది = 0;
    పూర్ణాంకం looking_for_primary;
    పూర్ణాంకం output;
    పూర్ణాంకం screen;

    ఒకవేళ (!X11_XRRQueryExtension(dpy, &దత్తాంశం->xrandr_event_పునాది, &xrandr_error_పునాది)) {
        తిరిగి SDL_సమితి_Error("XRRQueryExtension failed");
    }

    కొరకు (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        కొరకు (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            ఒకవేళ (looking_for_primary && (screen != default_screen)) {
                కొనసాగు;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ఒకవేళ (!res) {
                కొనసాగు;
            }

            కొరకు (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                ఒకవేళ ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    కొనసాగు;
                }
                ఒకవేళ (!X11_కూడు_XRand_RDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    ఆపు;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_ఆదానం(dpy, మూలం_కిటికీ(dpy, screen), RROutput_Change_Notify_ముసుగు);
        }
    }

    ఒకవేళ (_this->అంకె_displays == 0) {
        తిరిగి SDL_సమితి_Error("No available displays");
    }

    X11_క్రమీకరించు_Outputs_By_ప్రాధాన్యత_Hint(_this);

    తిరిగి true;
}
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
స్థిర bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    ఒకవేళ (X11_కూడు_Generic_Display(_this, true) == 0) {
        తిరిగి false;
    }
    తిరిగి true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
        పూర్ణాంకం xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        ఒకవేళ (CheckXRandR(దత్తాంశం->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            తిరిగి true;
        }
    }
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    తిరిగి X11_InitModes_StdXlib(_this);
}

bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display)
{
#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
    SDL_Display_దత్తాంశం *దత్తాంశం = sdl_display->అంతర్గత;
    SDL_Display_బహుళకం బహుళకం;

    /* Unfortunately X11 requires the window to be created with the correct
     * visual and depth ahead of time, but the SDL API allows you to create
     * a window before setting the fullscreen display mode.  This means that
     * we have to use the same format for all windows and all display modes.
     * (or support recreating the window with a new visual behind the scenes)
     */
    SDL_zero(బహుళకం);
    బహుళకం.format = sdl_display->desktop_బహుళకం.format;

    ఒకవేళ (దత్తాంశం->use_xrandr) {
        Display *display = _this->అంతర్గత->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, మూలం_కిటికీ(display, దత్తాంశం->screen));
        ఒకవేళ (res) {
            SDL_Display_బహుళకం_దత్తాంశం *modedata;
            XRROutputInfo *output_info;
            పూర్ణాంకం i;

            output_info = X11_XRRGetOutputInfo(display, res, దత్తాంశం->xrandr_output);
            ఒకవేళ (output_info && output_info->connection != RR_Disconnected) {
                కొరకు (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_Display_బహుళకం_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Display_బహుళకం_దత్తాంశం));
                    ఒకవేళ (!modedata) {
                        కొనసాగు;
                    }
                    బహుళకం.అంతర్గత = modedata;

                    ఒకవేళ (!సమితి_XRand_RMode_Info(display, res, output_info->crtc, output_info->modes[i], &బహుళకం) ||
                        !SDL_కూడు_Fullscreen_Display_బహుళకం(sdl_display, &బహుళకం)) {
                        SDL_free(modedata);
                    }
                }
            }
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
        }
    }
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XRANDR
    తిరిగి true;
}

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
స్థిర పూర్ణాంకం (*Pre_XRRSet_Screen_కొలత_Error_Handler)(Display *, XErrorEvent *) = ఖాళీ;
స్థిర పూర్ణాంకం SDL_XRRSet_Screen_కొలత_Err_Handler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    ఒకవేళ ((e->error_సంకేతం == Bad_సరిపోలిక) || (e->error_సంకేతం == Bad_విలువ)) {
        తిరిగి 0;
    }

    తిరిగి Pre_XRRSet_Screen_కొలత_Error_Handler(d, e);
}
#అయితే_ముగింపు

bool X11_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Display_బహుళకం *బహుళకం)
{
    SDL_Video_దత్తాంశం *viddata = _this->అంతర్గత;
    SDL_Display_దత్తాంశం *దత్తాంశం = sdl_display->అంతర్గత;

    viddata->చివరి_బహుళకం_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_సమయం * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    ఒకవేళ (!viddata->is_xwayland) {
        ఒకవేళ (sdl_display->current_బహుళకం != బహుళకం) {
            దత్తాంశం->బహుళకం_switch_deadline_ns = SDL_GetTicksNS() + బహుళకం_SWITCH_TIMEOUT_NS;
        } లేకపోతే {
            దత్తాంశం->బహుళకం_switch_deadline_ns = 0;
        }
    }

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XRANDR
    ఒకవేళ (దత్తాంశం->use_xrandr) {
        Display *display = viddata->display;
        SDL_Display_బహుళకం_దత్తాంశం *modedata = బహుళకం->అంతర్గత;
        పూర్ణాంకం mm_వెడల్పు, mm_ఎత్తు;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        స్థితి_3 స్థితి_2;

        res = X11_XRRGetScreenResources(display, మూలం_కిటికీ(display, దత్తాంశం->screen));
        ఒకవేళ (!res) {
            తిరిగి SDL_సమితి_Error("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, దత్తాంశం->xrandr_output);
        ఒకవేళ (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            తిరిగి SDL_సమితి_Error("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        ఒకవేళ (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            తిరిగి SDL_సమితి_Error("Couldn't get XRandR crtc info");
        }

        ఒకవేళ (crtc->బహుళకం == modedata->xrandr_బహుళకం) {
#నిర్వచితమైతే X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->బహుళకం, crtc->వెడల్పు, crtc->ఎత్తు);
#అయితే_ముగింపు
            స్థితి_2 = Success;
            వెళ్ళు freeInfo;
        }

        X11_XGrabServer(display);
        స్థితి_2 = X11_XRRSetCrtcConfig(display, res, output_info->crtc, Current_సమయం,
                                      0, 0, None, crtc->rotation, ఖాళీ, 0);
        ఒకవేళ (స్థితి_2 != Success) {
            వెళ్ళు ungrabServer;
        }

        mm_వెడల్పు = బహుళకం->w * Display_వెడల్పు_MM(display, దత్తాంశం->screen) / Display_వెడల్పు(display, దత్తాంశం->screen);
        mm_ఎత్తు = బహుళకం->h * Display_ఎత్తు_MM(display, దత్తాంశం->screen) / Display_ఎత్తు(display, దత్తాంశం->screen);

        /* !!! FIXME: this can get into a problem scenario when a window is
           bigger than a physical monitor in a configuration where one screen
           spans multiple physical monitors. A detailed reproduction case is
           discussed at https://github.com/libsdl-org/SDL/issues/4561 ...
           for now we cheat and just catch the X11 error and carry on, which
           is likely to cause subtle issues but is better than outright
           crashing */
        X11_XSync(display, False);
        Pre_XRRSet_Screen_కొలత_Error_Handler = X11_XSetErrorHandler(SDL_XRRSet_Screen_కొలత_Err_Handler);
        X11_XRRSet_Screen_కొలత(display, మూలం_కిటికీ(display, దత్తాంశం->screen),
                             బహుళకం->w, బహుళకం->h, mm_వెడల్పు, mm_ఎత్తు);
        X11_XSync(display, False);
        X11_XSetErrorHandler(Pre_XRRSet_Screen_కొలత_Error_Handler);

        స్థితి_2 = X11_XRRSetCrtcConfig(display, res, output_info->crtc, Current_సమయం,
                                      crtc->x, crtc->y, modedata->xrandr_బహుళకం, crtc->rotation,
                                      &దత్తాంశం->xrandr_output, 1);

    ungrabServer:
        X11_XUngrabServer(display);
    freeInfo:
        X11_XRRFreeCrtcInfo(crtc);
        X11_XRRFreeOutputInfo(output_info);
        X11_XRRFreeScreenResources(res);

        ఒకవేళ (స్థితి_2 != Success) {
            తిరిగి SDL_సమితి_Error("X11_XRRSetCrtcConfig failed");
        }
    }
#లేకపోతే
    (శూన్య)దత్తాంశం;
#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XRANDR

    తిరిగి true;
}

శూన్య X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Display_దత్తాంశం *దత్తాంశం = sdl_display->అంతర్గత;

    rect->x = దత్తాంశం->x;
    rect->y = దత్తాంశం->y;
    rect->w = sdl_display->current_బహుళకం->w;
    rect->h = sdl_display->current_బహుళకం->h;
    తిరిగి true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    Display *display = దత్తాంశం->display;
    Atom _NET_WORKAREA;
    పూర్ణాంకం real_format;
    Atom real_type;
    గుర్తులేని దీర్ఘ వస్తువులు_read = 0, వస్తువులు_ఎడమ = 0;
    గుర్తులేని అక్షరం *propdata = ఖాళీ;
    bool ఫలితం = false;

    ఒకవేళ (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        తిరిగి false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    పూర్ణాంకం స్థితి_2 = X11_XGet_కిటికీ_Property(display, Default_మూలం_కిటికీ(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &వస్తువులు_read,
                                    &వస్తువులు_ఎడమ, &propdata);
    ఒకవేళ ((స్థితి_2 == Success) && (వస్తువులు_read >= 4)) {
        స్థిరరాశి దీర్ఘ *p = (దీర్ఘ *)propdata;
        స్థిరరాశి SDL_Rect usable = { (పూర్ణాంకం)p[0], (పూర్ణాంకం)p[1], (పూర్ణాంకం)p[2], (పూర్ణాంకం)p[3] };
        ఫలితం = true;
        ఒకవేళ (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    ఒకవేళ (propdata) {
        X11_XFree(propdata);
    }

    తిరిగి ఫలితం;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11
