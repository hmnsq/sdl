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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11

#ضمن "SDL_x11video.h"
#ضمن "SDL_x11settings.h"
#ضمن "edid.h"
#ضمن "../../events/SDL_displayevents_c.h"
#ضمن "../SDL_pixels_c.h"

// #define X11MODES_DEBUG

/* Timeout and revert mode switches if the timespan has elapsed without the window becoming fullscreen.
 * 5 seconds seems good from testing.
 */
#تعریف_کن نما_SWITCH_TIMEOUT_NS SDL_NS_در_هر_دومی * 5

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
    مزدوج scale_ضریب_2 = 0.0;

    // First use the forced scaling factor specified by the app/user
    ثابت حرف *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_ضریب);
    إذا (hint && *hint) {
        مزدوج مقدار = SDL_atof(hint);
        إذا (مقدار >= 1.0f && مقدار <= 10.0f) {
            scale_ضریب_2 = مقدار;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    إذا (scale_ضریب_2 <= 0.0) {
        صحيح وضعیت, real_format;
        Atom real_type;
        Atom res_mgr;
        بیعلامت دراز اقلام_read, اقلام_چپ;
        حرف *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        وضعیت = X11_XGet_پنجره_Property(display, ریشه_پنجره(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &اقلام_read, &اقلام_چپ,
                                        (بیعلامت حرف **)&resource_manager);

        إذا (وضعیت == Success && resource_manager) {
            owns_resource_manager = true;
        } وإلا {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        إذا (resource_manager) {
            XrmDatabase db;
            Xrm_مقدار مقدار;
            حرف *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            إذا (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &مقدار)) {
                إذا (مقدار.addr && type && SDL_strcmp(type, "String") == 0) {
                    صحيح dpi = SDL_atoi(مقدار.addr);
                    scale_ضریب_2  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            إذا (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    إذا (scale_ضریب_2 <= 0.0) {
        scale_ضریب_2 = X11_Get_Xsettings_Client_Int_کلید(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        إذا (scale_ضریب_2 <= 0.0) {
            صحيح dpi = X11_Get_Xsettings_Client_Int_کلید(client, "Xft/DPI", -1);
            إذا (dpi > 0) {
                scale_ضریب_2 = (مزدوج) dpi / 1024.0;
                scale_ضریب_2 /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    إذا (scale_ضریب_2 <= 0.0) {
        ثابت حرف *scale_str = SDL_getenv("GDK_SCALE");
        إذا (scale_str) {
            scale_ضریب_2 = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    إذا (scale_ضریب_2 <= 0.0) {
        scale_ضریب_2 = 1.0;
    }

    أرجع (عائم)scale_ضریب_2;
}

عائم X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    أرجع X11_GetGlobalContentScale(_this->داخلی->display, _this->داخلی->xsettings_داده.xsettings);
}

ساكن bool get_visualinfo(Display *display, صحيح screen, XVisualInfo *vinfo)
{
    ثابت حرف *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    صحيح عمق_2;

    // Look for an exact visual, if requested
    إذا (visual_id && *visual_id) {
        XVisualInfo *vi, قالب;
        صحيح nvis;

        SDL_zero(قالب);
        قالب.visualid = SDL_strtol(visual_id, عدم, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &قالب, &nvis);
        إذا (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            أرجع true;
        }
    }

    عمق_2 = Default_عمق(display, screen);
    إذا ((X11_Use_مستقیم_Color_Visuals() &&
         X11_XMatchVisualInfo(display, screen, عمق_2, مستقیم_Color, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, عمق_2, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, عمق_2, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, عمق_2, StaticColor, vinfo)) {
        أرجع true;
    }
    أرجع false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    صحيح nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    إذا (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        أرجع true;
    }
    أرجع false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    إذا (vinfo->class == مستقیم_Color || vinfo->class == TrueColor) {
        صحيح bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_ماسک;
        Gmask = vinfo->visual->green_ماسک;
        Bmask = vinfo->visual->blue_ماسک;
        إذا (vinfo->عمق_2 == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } وإلا {
            Amask = 0;
        }

        bpp = vinfo->عمق_2;
        إذا (bpp == 24) {
            صحيح i, n;
            XPixmap_Format_مقادیر *p = X11_XListPixmapFormats(display, &n);
            إذا (p) {
                لكل (i = 0; i < n; ++i) {
                    إذا (p[i].عمق_2 == 24) {
                        bpp = p[i].بیتها_در_هر_pixel;
                        اكسر;
                    }
                }
                X11_XFree(p);
            }
        }

        أرجع SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    إذا (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        بدل (vinfo->عمق_2) {
        حالة 8:
            أرجع SDL_PIXELFORMAT_INDEX8;
        حالة 4:
            إذا (Bitmap_بیت_ترتیب(display) == LSBFirst) {
                أرجع SDL_PIXELFORMAT_INDEX4LSB;
            } وإلا {
                أرجع SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        حالة 1:
            إذا (Bitmap_بیت_ترتیب(display) == LSBFirst) {
                أرجع SDL_PIXELFORMAT_INDEX1LSB;
            } وإلا {
                أرجع SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    أرجع SDL_PIXELFORMAT_UNKNOWN;
}

ساكن SDL_DisplayID X11_جمع_کن_Generic_Display(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_Video_داده *داده = _this->داخلی;
    Display *dpy = داده->display;
    ثابت صحيح default_screen = DefaultScreen(dpy);
    Screen *screen = Screen_از_Display(dpy, default_screen);
    صحيح scanline_pad, n, i;
    SDL_Display_نما_داده *modedata;
    SDL_Display_داده *displaydata;
    SDL_Display_نما نما;
    XPixmap_Format_مقادیر *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    إذا (!get_visualinfo(dpy, default_screen, &vinfo)) {
        أرجع SDL_مجموعه_Error("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    إذا (SDL_ISPIXELFORMAT_نمایهای(pixelformat)) {
        أرجع SDL_مجموعه_Error("Palettized video modes are no longer supported");
    }

    SDL_zero(نما);
    نما.w = عرض_از_Screen(screen);
    نما.h = ارتفاع_از_Screen(screen);
    نما.format = pixelformat;

    displaydata = (SDL_Display_داده *)SDL_calloc(1, حجم(*displaydata));
    إذا (!displaydata) {
        أرجع false;
    }

    modedata = (SDL_Display_نما_داده *)SDL_calloc(1, حجم(SDL_Display_نما_داده));
    إذا (!modedata) {
        SDL_free(displaydata);
        أرجع false;
    }
    نما.داخلی = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->عمق_2 = vinfo.عمق_2;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    إذا (pixmapformats) {
        لكل (i = 0; i < n; ++i) {
            إذا (pixmapformats[i].عمق_2 == vinfo.عمق_2) {
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
    display.desktop_نما = نما;
    display.داخلی = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    أرجع SDL_جمع_کن_Video_Display(&display, send_event);
}

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR

ساكن فراغ X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(عدم);
    إذا (displays) {
        لكل (صحيح i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ثابت SDL_Display_داده *displaydata = display->داخلی;
            إذا (!displaydata->xrandr_output) {
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
#اگر_تعریف_شده XRANDR_DISABLED_BY_DEFAULT
    إذا (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#اگر_تعریف_شده X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#پایان_اگر
        أرجع false;
    }
#وإلا
    إذا (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#اگر_تعریف_شده X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#پایان_اگر
        أرجع false;
    }
#پایان_اگر // XRANDR_DISABLED_BY_DEFAULT

    إذا (!SDL_X11_HAVE_XRANDR) {
#اگر_تعریف_شده X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#پایان_اگر
        أرجع false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    إذا (!X11_XRRQuery_نسخه(display, major, minor)) {
#اگر_تعریف_شده X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#پایان_اگر
        *major = *minor = 0;
        أرجع false;
    }
#اگر_تعریف_شده X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#پایان_اگر
    أرجع true;
}

#تعریف_کن XRANDR_ROTATION_چپ  (1 << 1)
#تعریف_کن XRANDR_ROTATION_راست (1 << 3)

ساكن فراغ Calculate_XRand_RRefresh_نرخ(ثابت XRRModeInfo *info, صحيح *numerator, صحيح *denominator)
{
    بیعلامت صحيح v_مجموع_2 = info->v_مجموع_2;

    إذا (info->نما_Flags & RR_Double_پیمایش) {
        // doublescan doubles the number of lines
        v_مجموع_2 *= 2;
    }

    إذا (info->نما_Flags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        v_مجموع_2 /= 2;
    }

    إذا (info->h_مجموع_2 && v_مجموع_2) {
        *numerator = info->dotClock;
        *denominator = (info->h_مجموع_2 * v_مجموع_2);
    } وإلا {
        *numerator = 0;
        *denominator = 0;
    }
}

ساكن bool مجموعه_XRand_RMode_Info(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode نما_ID, SDL_Display_نما *نما)
{
    صحيح i;
    لكل (i = 0; i < res->nmode; ++i) {
        ثابت XRRModeInfo *info = &res->modes[i];
        إذا (info->id == نما_ID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtc_Transform_صفات *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            إذا (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            إذا (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.ماتریس[0][0];
                scale_h = attr->currentTransform.ماتریس[1][1];
                X11_XFree(attr);
            }

            إذا (rotation & (XRANDR_ROTATION_چپ | XRANDR_ROTATION_راست)) {
                نما->w = (info->ارتفاع * scale_w + 0xffff) >> 16;
                نما->h = (info->عرض * scale_h + 0xffff) >> 16;
            } وإلا {
                نما->w = (info->عرض * scale_w + 0xffff) >> 16;
                نما->h = (info->ارتفاع * scale_h + 0xffff) >> 16;
            }
            Calculate_XRand_RRefresh_نرخ(info, &نما->refresh_نرخ_numerator, &نما->refresh_نرخ_denominator);
            نما->داخلی->xrandr_نما = نما_ID;
#اگر_تعریف_شده X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (صحيح)نما_ID,
                    نما->screen_w, نما->screen_h, نما->refresh_نرخ_numerator, نما->refresh_نرخ_denominator);
#پایان_اگر
            أرجع true;
        }
    }
    أرجع false;
}

ساكن bool Get_ریشه_پنجره_Cardinal_Property(Display *dpy, صحيح screen, ثابت حرف *name, Uint32 *مقدار)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    إذا (atom == None) {
        أرجع false;
    }

    صحيح real_format;
    Atom real_type;
    بیعلامت دراز اقلام_read = 0, اقلام_چپ = 0;
    بیعلامت حرف *propdata = عدم;
    صحيح وضعیت;
    bool نتیجه = false;

    وضعیت = X11_XGet_پنجره_Property(dpy, ریشه_پنجره(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &اقلام_read, &اقلام_چپ, &propdata);
    إذا (وضعیت == Success && propdata) {
        إذا (real_type == XA_CARDINAL && اقلام_read > 0) {
            بدل (real_format) {
            حالة 8:
                *مقدار = propdata[0];
                اكسر;
            حالة 16:
                *مقدار = propdata[0] | (propdata[1] << 8);
                اكسر;
            افتراضي:
                *مقدار = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                اكسر;
            }
            نتیجه = true;
        }
        X11_XFree(propdata);
    }
    أرجع نتیجه;
}

ساكن bool Get_ریشه_پنجره_Bool_Property(Display *dpy, صحيح screen, ثابت حرف *name, bool *مقدار)
{
    Uint32 v;
    إذا (Get_ریشه_پنجره_Cardinal_Property(dpy, screen, name, &v)) {
        *مقدار = (v != 0);
        أرجع true;
    }
    أرجع false;
}

ساكن bool Get_ریشه_پنجره_Float_Property(Display *dpy, صحيح screen, ثابت حرف *name, عائم *مقدار)
{
    Uint32 v;
    إذا (Get_ریشه_پنجره_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(مقدار, &v, حجم(v));
        أرجع true;
    }
    أرجع false;
}

ساكن bool IsSteamDeckOLEDDisplay(ثابت MonitorInfo *info)
{
    إذا (SDL_strcmp(info->manufacturer_کد, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        إذا (info->حاصلضرب_کد == 0x3003 || info->حاصلضرب_کد == 0x3004) {
            أرجع true;
        }
    }
    أرجع false;
}

ساكن عائم GetGamescopeSDRWhiteLevel(Display *dpy, صحيح screen, ثابت MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    إذا (!dpy) {
        أرجع 0.0f;
    }

    عائم SDR_white_level = 0.0f;
    bool external_display = false;
    إذا (Get_ریشه_پنجره_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_ریشه_پنجره_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } وإلا إذا (IsSteamDeckOLEDDisplay(info)) {
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
    } وإلا {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    أرجع SDR_white_level;
}

ساكن MonitorInfo *GetMonitorInfo(Display *dpy, صحيح screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = عدم;
    صحيح real_format;
    Atom real_type;
    بیعلامت دراز اقلام_read = 0, اقلام_چپ = 0;
    بیعلامت حرف *propdata = عدم;
    صحيح وضعیت;

    *gamescope = false;

    إذا (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_مسیر = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        إذا (GAMESCOPE_DISPLAY_EDID_مسیر != None) {
            وضعیت = X11_XGet_پنجره_Property(dpy, ریشه_پنجره(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_مسیر, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &اقلام_read, &اقلام_چپ, &propdata);
            إذا (وضعیت == Success && propdata) {
                size_t اندازه = 0;
                فراغ *داده = SDL_بارگیری_File((حرف *)propdata, &اندازه);
                إذا (داده) {
                    info = decode_edid((uchar *)داده, اندازه);
                    إذا (info) {
                        *gamescope = true;
                    }
                    SDL_free(داده);
                }
            }
            إذا (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    إذا (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        إذا (EDID != None) {
            صحيح nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            لكل (صحيح i = 0; i < nprop; ++i) {
                إذا (props[i] == EDID) {
                    وضعیت = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &اقلام_read, &اقلام_چپ, &propdata);
                    إذا (وضعیت == Success && propdata) {
                        info = decode_edid(propdata, اقلام_read);
                    }
                    إذا (propdata) {
                        X11_XFree(propdata);
                    }
                    اكسر;
                }
            }

            إذا (props) {
                X11_XFree(props);
            }
        }
    }

#اگر_تعریف_شده X11MODES_DEBUG
    إذا (info) {
        dump_monitor_info(info);
    }
#پایان_اگر
    أرجع info;
}

ساكن فراغ مجموعه_XRand_RDisplay_Name(MonitorInfo *info, حرف *name, size_t namelen, بیعلامت دراز widthmm, بیعلامت دراز heightmm)
{
    إذا (info) {
        SDL_strlcpy(name, info->dsc_حاصلضرب_name, namelen);
    }

    صحيح inches = (صحيح)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    إذا (*name && inches) {
        ثابت size_t len = SDL_strlen(name);
        (فراغ)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#اگر_تعریف_شده X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#پایان_اگر
}

ساكن bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, صحيح screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, حرف *display_name, size_t display_name_اندازه)
{
    XRROutputInfo *output_info;
    صحيح display_x, display_y;
    بیعلامت دراز display_mm_عرض, display_mm_ارتفاع;
    SDL_Display_داده *displaydata;
    SDL_Display_نما نما;
    SDL_Display_نما_داده *modedata;
    RRMode نما_ID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_مقادیر *pixmapformats;
    صحيح scanline_pad;
    صحيح i, n;

    إذا (!display || !display_name) {
        أرجع false; // invalid parameters
    }

    إذا (!get_visualinfo(dpy, screen, &vinfo)) {
        أرجع false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    إذا (SDL_ISPIXELFORMAT_نمایهای(pixelformat)) {
        أرجع false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    إذا (pixmapformats) {
        لكل (i = 0; i < n; i++) {
            إذا (pixmapformats[i].عمق_2 == vinfo.عمق_2) {
                scanline_pad = pixmapformats[i].scanline_pad;
                اكسر;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    إذا (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        أرجع false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_اندازه);
    display_mm_عرض = output_info->mm_عرض;
    display_mm_ارتفاع = output_info->mm_ارتفاع;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    إذا (!crtc) {
        أرجع false; // oh well, ignore it.
    }

    SDL_zero(نما);
    نما_ID = crtc->نما;
    نما.w = crtc->عرض;
    نما.h = crtc->ارتفاع;
    نما.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_Display_داده *)SDL_calloc(1, حجم(*displaydata));
    إذا (!displaydata) {
        أرجع false;
    }

    modedata = (SDL_Display_نما_داده *)SDL_calloc(1, حجم(SDL_Display_نما_داده));
    إذا (!modedata) {
        SDL_free(displaydata);
        أرجع false;
    }

    modedata->xrandr_نما = نما_ID;
    نما.داخلی = modedata;

    displaydata->screen = screen;
    displaydata->visual = vinfo.visual;
    displaydata->عمق_2 = vinfo.عمق_2;
    displaydata->scanline_pad = scanline_pad;
    displaydata->x = display_x;
    displaydata->y = display_y;
    displaydata->use_xrandr = true;
    displaydata->xrandr_output = outputid;
    SDL_strlcpy(displaydata->connector_name, display_name, حجم(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    مجموعه_XRand_RMode_Info(dpy, res, output_crtc, نما_ID, &نما);
    مجموعه_XRand_RDisplay_Name(info, display_name, display_name_اندازه, display_mm_عرض, display_mm_ارتفاع);

    SDL_zero(*display);
    إذا (*display_name) {
        display->name = display_name;
    }
    display->desktop_نما = نما;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->داخلی = displaydata;

    إذا (info) {
        عائم SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        إذا (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } وإلا {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#اگر_تعریف_شده X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#پایان_اگر
        إذا (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (عائم)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    أرجع true;
}

ساكن bool X11_جمع_کن_XRand_RDisplay(SDL_VideoDevice *_this, Display *dpy, صحيح screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    حرف display_name[128];

    إذا (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, حجم(display_name))) {
        أرجع true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_جمع_کن_Video_Display(&display, false);
    إذا (displayID == 0) {
        أرجع false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    إذا (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    أرجع true;
}


ساكن bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, صحيح screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    حرف display_name[128];

    إذا (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, حجم(display_name))) {
        أرجع false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_مجموعه_Desktop_Display_نما(existing_display, &display.desktop_نما);

    // update bounds
    إذا (existing_display->داخلی->x != display.داخلی->x ||
        existing_display->داخلی->y != display.داخلی->y) {
        existing_display->داخلی->x = display.داخلی->x;
        existing_display->داخلی->y = display.داخلی->y;
        SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
    }

    // update scale
    SDL_مجموعه_Display_Content_Scale(existing_display, display.content_scale);

    // update HDR properties
    SDL_مجموعه_Display_HDRProperties(existing_display, &display.HDR);

    // SDL_DisplayData is updated piece-meal above, free our local copy of this data
    SDL_free(display.داخلی);

    أرجع true;
}

ساكن XRRScreenResources *X11_GetScreenResources(Display *dpy, صحيح screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, ریشه_پنجره(dpy, screen));
    إذا (!res || res->noutput == 0) {
        إذا (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, ریشه_پنجره(dpy, screen));
    }
    أرجع res;
}

فراغ X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    ثابت صحيح screencount = Screen_شمار(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(عدم);
    إذا (!displays) {
        أرجع;
    }

    لكل (صحيح screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        إذا (!res) {
            استمر;
        }

        لكل (صحيح i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ثابت SDL_Display_داده *displaydata = display->داخلی;
            إذا (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

ساكن فراغ X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    ثابت صحيح screencount = Screen_شمار(dpy);
    صحيح رقم_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&رقم_displays);
    إذا (!displays) {
        أرجع;
    }

    لكل (صحيح screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        إذا (!res) {
            استمر;
        }

        لكل (صحيح output = 0; output < res->noutput; output++) {
            لكل (صحيح i = 0; i < رقم_displays; ++i) {
                إذا (!displays[i]) {
                    // We already removed this display from the list
                    استمر;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                ثابت SDL_Display_داده *displaydata = display->داخلی;
                إذا (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    اكسر;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    لكل (صحيح i = 0; i < رقم_displays; ++i) {
        إذا (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ثابت SDL_Display_داده *displaydata = display->داخلی;
            إذا (displaydata->xrandr_output) {
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

#إذا 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (بیعلامت صحيح) ev->output, (بیعلامت صحيح) ev->crtc, (بیعلامت صحيح) ev->نما, (بیعلامت صحيح) ev->rotation, (بیعلامت صحيح) ev->connection);
#پایان_اگر

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(عدم);
    إذا (displays) {
        لكل (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            ثابت SDL_Display_داده *displaydata = thisdisplay->داخلی;
            إذا (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                اكسر;
            }
        }
        SDL_free(displays);
    }

    إذا (ev->connection == RR_Disconnected) { // output is going away
        إذا (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            إذا (_this->رقم_displays == 1) {
                generic_display = X11_جمع_کن_Generic_Display(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            إذا (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } وإلا إذا (ev->connection == RR_Connected) { // output is coming online
        إذا (!display) {
            Display *dpy = ev->display;
            ثابت صحيح screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            إذا (res) {
                X11_جمع_کن_XRand_RDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

فراغ X11_HandleXRandREvent(SDL_VideoDevice *_this, ثابت XEvent *xevent)
{
    SDL_Video_داده *videodata = _this->داخلی;
    SDL_assert(xevent->type == (videodata->xrandr_event_پایه + RRNotify));

    بدل (((ثابت XRRNotifyEvent *)xevent)->subtype) {
    حالة RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (ثابت XRROutputChangeNotifyEvent *)xevent);
        اكسر;
    افتراضي:
        اكسر;
    }
}

ساكن فراغ X11_مرتب_سازی_Outputs_By_اولویت_Hint(SDL_VideoDevice *_this)
{
    ثابت حرف *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_اولویت);

    إذا (name_hint) {
        حرف *saveptr;
        حرف *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(حجم(SDL_VideoDisplay *) * _this->رقم_displays);

        إذا (str && sorted_list) {
            صحيح sorted_شاخص = 0;

            // Sort the requested displays to the front of the list.
            ثابت حرف *token = SDL_strtok_r(str, ",", &saveptr);
            طالما (token) {
                لكل (صحيح i = 0; i < _this->رقم_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    إذا (d) {
                        SDL_Display_داده *داده = d->داخلی;
                        إذا (SDL_strcmp(token, داده->connector_name) == 0) {
                            sorted_list[sorted_شاخص++] = d;
                            _this->displays[i] = عدم;
                            اكسر;
                        }
                    }
                }

                token = SDL_strtok_r(عدم, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            لكل (صحيح i = 0; i < _this->رقم_displays; ++i) {
                إذا (_this->displays[i]) {
                    sorted_list[sorted_شاخص++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, حجم(SDL_VideoDisplay *) * _this->رقم_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ساكن bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_Video_داده *داده = _this->داخلی;
    Display *dpy = داده->display;
    ثابت صحيح screencount = Screen_شمار(dpy);
    ثابت صحيح default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, ریشه_پنجره(dpy, default_screen));
    صحيح xrandr_error_پایه = 0;
    صحيح looking_for_primary;
    صحيح output;
    صحيح screen;

    إذا (!X11_XRRQueryExtension(dpy, &داده->xrandr_event_پایه, &xrandr_error_پایه)) {
        أرجع SDL_مجموعه_Error("XRRQueryExtension failed");
    }

    لكل (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        لكل (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            إذا (looking_for_primary && (screen != default_screen)) {
                استمر;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            إذا (!res) {
                استمر;
            }

            لكل (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                إذا ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    استمر;
                }
                إذا (!X11_جمع_کن_XRand_RDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    اكسر;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_درون_داد(dpy, ریشه_پنجره(dpy, screen), RROutput_Change_Notify_ماسک);
        }
    }

    إذا (_this->رقم_displays == 0) {
        أرجع SDL_مجموعه_Error("No available displays");
    }

    X11_مرتب_سازی_Outputs_By_اولویت_Hint(_this);

    أرجع true;
}
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
ساكن bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    إذا (X11_جمع_کن_Generic_Display(_this, true) == 0) {
        أرجع false;
    }
    أرجع true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_Video_داده *داده = _this->داخلی;
        صحيح xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        إذا (CheckXRandR(داده->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            أرجع true;
        }
    }
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    أرجع X11_InitModes_StdXlib(_this);
}

bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display)
{
#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
    SDL_Display_داده *داده = sdl_display->داخلی;
    SDL_Display_نما نما;

    /* Unfortunately X11 requires the window to be created with the correct
     * visual and depth ahead of time, but the SDL API allows you to create
     * a window before setting the fullscreen display mode.  This means that
     * we have to use the same format for all windows and all display modes.
     * (or support recreating the window with a new visual behind the scenes)
     */
    SDL_zero(نما);
    نما.format = sdl_display->desktop_نما.format;

    إذا (داده->use_xrandr) {
        Display *display = _this->داخلی->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, ریشه_پنجره(display, داده->screen));
        إذا (res) {
            SDL_Display_نما_داده *modedata;
            XRROutputInfo *output_info;
            صحيح i;

            output_info = X11_XRRGetOutputInfo(display, res, داده->xrandr_output);
            إذا (output_info && output_info->connection != RR_Disconnected) {
                لكل (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_Display_نما_داده *)SDL_calloc(1, حجم(SDL_Display_نما_داده));
                    إذا (!modedata) {
                        استمر;
                    }
                    نما.داخلی = modedata;

                    إذا (!مجموعه_XRand_RMode_Info(display, res, output_info->crtc, output_info->modes[i], &نما) ||
                        !SDL_جمع_کن_Fullscreen_Display_نما(sdl_display, &نما)) {
                        SDL_free(modedata);
                    }
                }
            }
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
        }
    }
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XRANDR
    أرجع true;
}

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
ساكن صحيح (*Pre_XRRSet_Screen_اندازه_Error_Handler)(Display *, XErrorEvent *) = عدم;
ساكن صحيح SDL_XRRSet_Screen_اندازه_Err_Handler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    إذا ((e->error_کد == Bad_تطابق) || (e->error_کد == Bad_مقدار)) {
        أرجع 0;
    }

    أرجع Pre_XRRSet_Screen_اندازه_Error_Handler(d, e);
}
#پایان_اگر

bool X11_مجموعه_Display_نما(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Display_نما *نما)
{
    SDL_Video_داده *viddata = _this->داخلی;
    SDL_Display_داده *داده = sdl_display->داخلی;

    viddata->آخرین_نما_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_زمان * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    إذا (!viddata->is_xwayland) {
        إذا (sdl_display->current_نما != نما) {
            داده->نما_switch_deadline_ns = SDL_GetTicksNS() + نما_SWITCH_TIMEOUT_NS;
        } وإلا {
            داده->نما_switch_deadline_ns = 0;
        }
    }

#اگر_تعریف_شده SDL_VIDEO_DRIVER_X11_XRANDR
    إذا (داده->use_xrandr) {
        Display *display = viddata->display;
        SDL_Display_نما_داده *modedata = نما->داخلی;
        صحيح mm_عرض, mm_ارتفاع;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        وضعیت_2 وضعیت;

        res = X11_XRRGetScreenResources(display, ریشه_پنجره(display, داده->screen));
        إذا (!res) {
            أرجع SDL_مجموعه_Error("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, داده->xrandr_output);
        إذا (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            أرجع SDL_مجموعه_Error("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        إذا (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            أرجع SDL_مجموعه_Error("Couldn't get XRandR crtc info");
        }

        إذا (crtc->نما == modedata->xrandr_نما) {
#اگر_تعریف_شده X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->نما, crtc->عرض, crtc->ارتفاع);
#پایان_اگر
            وضعیت = Success;
            اذهب freeInfo;
        }

        X11_XGrabServer(display);
        وضعیت = X11_XRRSetCrtcConfig(display, res, output_info->crtc, Current_زمان,
                                      0, 0, None, crtc->rotation, عدم, 0);
        إذا (وضعیت != Success) {
            اذهب ungrabServer;
        }

        mm_عرض = نما->w * Display_عرض_MM(display, داده->screen) / Display_عرض(display, داده->screen);
        mm_ارتفاع = نما->h * Display_ارتفاع_MM(display, داده->screen) / Display_ارتفاع(display, داده->screen);

        /* !!! FIXME: this can get into a problem scenario when a window is
           bigger than a physical monitor in a configuration where one screen
           spans multiple physical monitors. A detailed reproduction case is
           discussed at https://github.com/libsdl-org/SDL/issues/4561 ...
           for now we cheat and just catch the X11 error and carry on, which
           is likely to cause subtle issues but is better than outright
           crashing */
        X11_XSync(display, False);
        Pre_XRRSet_Screen_اندازه_Error_Handler = X11_XSetErrorHandler(SDL_XRRSet_Screen_اندازه_Err_Handler);
        X11_XRRSet_Screen_اندازه(display, ریشه_پنجره(display, داده->screen),
                             نما->w, نما->h, mm_عرض, mm_ارتفاع);
        X11_XSync(display, False);
        X11_XSetErrorHandler(Pre_XRRSet_Screen_اندازه_Error_Handler);

        وضعیت = X11_XRRSetCrtcConfig(display, res, output_info->crtc, Current_زمان,
                                      crtc->x, crtc->y, modedata->xrandr_نما, crtc->rotation,
                                      &داده->xrandr_output, 1);

    ungrabServer:
        X11_XUngrabServer(display);
    freeInfo:
        X11_XRRFreeCrtcInfo(crtc);
        X11_XRRFreeOutputInfo(output_info);
        X11_XRRFreeScreenResources(res);

        إذا (وضعیت != Success) {
            أرجع SDL_مجموعه_Error("X11_XRRSetCrtcConfig failed");
        }
    }
#وإلا
    (فراغ)داده;
#پایان_اگر // SDL_VIDEO_DRIVER_X11_XRANDR

    أرجع true;
}

فراغ X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Display_داده *داده = sdl_display->داخلی;

    rect->x = داده->x;
    rect->y = داده->y;
    rect->w = sdl_display->current_نما->w;
    rect->h = sdl_display->current_نما->h;
    أرجع true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Video_داده *داده = _this->داخلی;
    Display *display = داده->display;
    Atom _NET_WORKAREA;
    صحيح real_format;
    Atom real_type;
    بیعلامت دراز اقلام_read = 0, اقلام_چپ = 0;
    بیعلامت حرف *propdata = عدم;
    bool نتیجه = false;

    إذا (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        أرجع false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    صحيح وضعیت = X11_XGet_پنجره_Property(display, Default_ریشه_پنجره(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &اقلام_read,
                                    &اقلام_چپ, &propdata);
    إذا ((وضعیت == Success) && (اقلام_read >= 4)) {
        ثابت دراز *p = (دراز *)propdata;
        ثابت SDL_Rect usable = { (صحيح)p[0], (صحيح)p[1], (صحيح)p[2], (صحيح)p[3] };
        نتیجه = true;
        إذا (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    إذا (propdata) {
        X11_XFree(propdata);
    }

    أرجع نتیجه;
}

#پایان_اگر // SDL_VIDEO_DRIVER_X11
