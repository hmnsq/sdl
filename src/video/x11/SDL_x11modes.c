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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11settings.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "edid.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_displayevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_pixels_c.h"

// #define X11MODES_DEBUG

/* Timeout and revert mode switches if the timespan has elapsed without the window becoming fullscreen.
 * 5 seconds seems good from testing.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਬਹੁਲਕ_SWITCH_TIMEOUT_NS SDL_NS_ਪ੍ਰਤੀ_ਦੂਜਾ * 5

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

ਦਸ਼ਮਲਵ X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    ਦੁੱਗਣਾ scale_ਗੁਣਕ_2 = 0.0;

    // First use the forced scaling factor specified by the app/user
    ਅਚਲ ਅੱਖਰ *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_ਗੁਣਕ);
    ਜੇ (hint && *hint) {
        ਦੁੱਗਣਾ ਮੁੱਲ = SDL_atof(hint);
        ਜੇ (ਮੁੱਲ >= 1.0f && ਮੁੱਲ <= 10.0f) {
            scale_ਗੁਣਕ_2 = ਮੁੱਲ;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    ਜੇ (scale_ਗੁਣਕ_2 <= 0.0) {
        ਪੂਰਨ ਸਥਿਤੀ, real_format;
        Atom real_type;
        Atom res_mgr;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਚੀਜ਼ਾਂ_read, ਚੀਜ਼ਾਂ_ਖੱਬਾ;
        ਅੱਖਰ *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        ਸਥਿਤੀ = X11_XGet_ਖਿੜਕੀ_Property(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &ਚੀਜ਼ਾਂ_read, &ਚੀਜ਼ਾਂ_ਖੱਬਾ,
                                        (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ **)&resource_manager);

        ਜੇ (ਸਥਿਤੀ == Success && resource_manager) {
            owns_resource_manager = true;
        } ਨਹੀਂਤਾਂ {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        ਜੇ (resource_manager) {
            XrmDatabase db;
            Xrm_ਮੁੱਲ ਮੁੱਲ;
            ਅੱਖਰ *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            ਜੇ (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &ਮੁੱਲ)) {
                ਜੇ (ਮੁੱਲ.addr && type && SDL_strcmp(type, "String") == 0) {
                    ਪੂਰਨ dpi = SDL_atoi(ਮੁੱਲ.addr);
                    scale_ਗੁਣਕ_2  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            ਜੇ (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    ਜੇ (scale_ਗੁਣਕ_2 <= 0.0) {
        scale_ਗੁਣਕ_2 = X11_Get_Xsettings_Client_Int_ਕੁੰਜੀ(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        ਜੇ (scale_ਗੁਣਕ_2 <= 0.0) {
            ਪੂਰਨ dpi = X11_Get_Xsettings_Client_Int_ਕੁੰਜੀ(client, "Xft/DPI", -1);
            ਜੇ (dpi > 0) {
                scale_ਗੁਣਕ_2 = (ਦੁੱਗਣਾ) dpi / 1024.0;
                scale_ਗੁਣਕ_2 /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    ਜੇ (scale_ਗੁਣਕ_2 <= 0.0) {
        ਅਚਲ ਅੱਖਰ *scale_str = SDL_getenv("GDK_SCALE");
        ਜੇ (scale_str) {
            scale_ਗੁਣਕ_2 = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    ਜੇ (scale_ਗੁਣਕ_2 <= 0.0) {
        scale_ਗੁਣਕ_2 = 1.0;
    }

    ਵਾਪਸ (ਦਸ਼ਮਲਵ)scale_ਗੁਣਕ_2;
}

ਦਸ਼ਮਲਵ X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    ਵਾਪਸ X11_GetGlobalContentScale(_this->ਅੰਦਰੂਨੀ->display, _this->ਅੰਦਰੂਨੀ->xsettings_ਅੰਕੜੇ.xsettings);
}

ਸਥਿਰ bool get_visualinfo(Display *display, ਪੂਰਨ screen, XVisualInfo *vinfo)
{
    ਅਚਲ ਅੱਖਰ *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    ਪੂਰਨ ਡੂੰਘਾਈ_2;

    // Look for an exact visual, if requested
    ਜੇ (visual_id && *visual_id) {
        XVisualInfo *vi, ਸਾਂਚਾ;
        ਪੂਰਨ nvis;

        SDL_zero(ਸਾਂਚਾ);
        ਸਾਂਚਾ.visualid = SDL_strtol(visual_id, ਨਿਰਾ, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &ਸਾਂਚਾ, &nvis);
        ਜੇ (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            ਵਾਪਸ true;
        }
    }

    ਡੂੰਘਾਈ_2 = Default_ਡੂੰਘਾਈ(display, screen);
    ਜੇ ((X11_Use_ਸਿੱਧਾ_Color_Visuals() &&
         X11_XMatchVisualInfo(display, screen, ਡੂੰਘਾਈ_2, ਸਿੱਧਾ_Color, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, ਡੂੰਘਾਈ_2, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, ਡੂੰਘਾਈ_2, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, ਡੂੰਘਾਈ_2, StaticColor, vinfo)) {
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    ਪੂਰਨ nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    ਜੇ (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    ਜੇ (vinfo->class == ਸਿੱਧਾ_Color || vinfo->class == TrueColor) {
        ਪੂਰਨ bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_ਨਕਾਬ;
        Gmask = vinfo->visual->green_ਨਕਾਬ;
        Bmask = vinfo->visual->blue_ਨਕਾਬ;
        ਜੇ (vinfo->ਡੂੰਘਾਈ_2 == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } ਨਹੀਂਤਾਂ {
            Amask = 0;
        }

        bpp = vinfo->ਡੂੰਘਾਈ_2;
        ਜੇ (bpp == 24) {
            ਪੂਰਨ i, n;
            XPixmap_Format_ਮੁੱਲਾਂ *p = X11_XListPixmapFormats(display, &n);
            ਜੇ (p) {
                ਲਈ (i = 0; i < n; ++i) {
                    ਜੇ (p[i].ਡੂੰਘਾਈ_2 == 24) {
                        bpp = p[i].ਬਿੱਟ_ਪ੍ਰਤੀ_pixel;
                        ਰੋਕੋ;
                    }
                }
                X11_XFree(p);
            }
        }

        ਵਾਪਸ SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    ਜੇ (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        ਚੋਣ (vinfo->ਡੂੰਘਾਈ_2) {
        ਹਾਲਤ 8:
            ਵਾਪਸ SDL_PIXELFORMAT_INDEX8;
        ਹਾਲਤ 4:
            ਜੇ (Bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_ਕ੍ਰਮ(display) == LSBFirst) {
                ਵਾਪਸ SDL_PIXELFORMAT_INDEX4LSB;
            } ਨਹੀਂਤਾਂ {
                ਵਾਪਸ SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        ਹਾਲਤ 1:
            ਜੇ (Bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_ਕ੍ਰਮ(display) == LSBFirst) {
                ਵਾਪਸ SDL_PIXELFORMAT_INDEX1LSB;
            } ਨਹੀਂਤਾਂ {
                ਵਾਪਸ SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    ਵਾਪਸ SDL_PIXELFORMAT_UNKNOWN;
}

ਸਥਿਰ SDL_DisplayID X11_ਜੋੜੋ_Generic_Display(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    Display *dpy = ਅੰਕੜੇ->display;
    ਅਚਲ ਪੂਰਨ default_screen = DefaultScreen(dpy);
    Screen *screen = Screen_ਦਾ_Display(dpy, default_screen);
    ਪੂਰਨ scanline_pad, n, i;
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata;
    SDL_Display_ਅੰਕੜੇ *displaydata;
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    XPixmap_Format_ਮੁੱਲਾਂ *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    ਜੇ (!get_visualinfo(dpy, default_screen, &vinfo)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ਜੇ (SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(pixelformat)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Palettized video modes are no longer supported");
    }

    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ.w = ਚੌੜਾਈ_ਦਾ_Screen(screen);
    ਬਹੁਲਕ.h = ਉਚਾਈ_ਦਾ_Screen(screen);
    ਬਹੁਲਕ.format = pixelformat;

    displaydata = (SDL_Display_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*displaydata));
    ਜੇ (!displaydata) {
        ਵਾਪਸ false;
    }

    modedata = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ));
    ਜੇ (!modedata) {
        SDL_free(displaydata);
        ਵਾਪਸ false;
    }
    ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->ਡੂੰਘਾਈ_2 = vinfo.ਡੂੰਘਾਈ_2;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ਜੇ (pixmapformats) {
        ਲਈ (i = 0; i < n; ++i) {
            ਜੇ (pixmapformats[i].ਡੂੰਘਾਈ_2 == vinfo.ਡੂੰਘਾਈ_2) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ਰੋਕੋ;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (ਅੱਖਰ *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_ਬਹੁਲਕ = ਬਹੁਲਕ;
    display.ਅੰਦਰੂਨੀ = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    ਵਾਪਸ SDL_ਜੋੜੋ_Video_Display(&display, send_event);
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR

ਸਥਿਰ ਖਾਲੀ X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(ਨਿਰਾ);
    ਜੇ (displays) {
        ਲਈ (ਪੂਰਨ i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ਅਚਲ SDL_Display_ਅੰਕੜੇ *displaydata = display->ਅੰਦਰੂਨੀ;
            ਜੇ (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

ਸਥਿਰ bool CheckXRandR(Display *display, ਪੂਰਨ *major, ਪੂਰਨ *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ XRANDR_DISABLED_BY_DEFAULT
    ਜੇ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#ਜੇ_ਅੰਤ
        ਵਾਪਸ false;
    }
#ਨਹੀਂਤਾਂ
    ਜੇ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#ਜੇ_ਅੰਤ
        ਵਾਪਸ false;
    }
#ਜੇ_ਅੰਤ // XRANDR_DISABLED_BY_DEFAULT

    ਜੇ (!SDL_X11_HAVE_XRANDR) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#ਜੇ_ਅੰਤ
        ਵਾਪਸ false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    ਜੇ (!X11_XRRQuery_ਸੰਸਕਰਣ(display, major, minor)) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#ਜੇ_ਅੰਤ
        *major = *minor = 0;
        ਵਾਪਸ false;
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ true;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XRANDR_ROTATION_ਖੱਬਾ  (1 << 1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XRANDR_ROTATION_ਸੱਜਾ (1 << 3)

ਸਥਿਰ ਖਾਲੀ Calculate_XRand_RRefresh_ਦਰ(ਅਚਲ XRRModeInfo *info, ਪੂਰਨ *numerator, ਪੂਰਨ *denominator)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ v_ਕੁੱਲ_2 = info->v_ਕੁੱਲ_2;

    ਜੇ (info->ਬਹੁਲਕ_Flags & RR_Double_ਜਾਂਚ) {
        // doublescan doubles the number of lines
        v_ਕੁੱਲ_2 *= 2;
    }

    ਜੇ (info->ਬਹੁਲਕ_Flags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        v_ਕੁੱਲ_2 /= 2;
    }

    ਜੇ (info->h_ਕੁੱਲ_2 && v_ਕੁੱਲ_2) {
        *numerator = info->dotClock;
        *denominator = (info->h_ਕੁੱਲ_2 * v_ਕੁੱਲ_2);
    } ਨਹੀਂਤਾਂ {
        *numerator = 0;
        *denominator = 0;
    }
}

ਸਥਿਰ bool ਸੈੱਟ_XRand_RMode_Info(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode ਬਹੁਲਕ_ID, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < res->nmode; ++i) {
        ਅਚਲ XRRModeInfo *info = &res->modes[i];
        ਜੇ (info->id == ਬਹੁਲਕ_ID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtc_Transform_ਗੁਣ *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            ਜੇ (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            ਜੇ (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.ਮੈਟ੍ਰਿਕਸ[0][0];
                scale_h = attr->currentTransform.ਮੈਟ੍ਰਿਕਸ[1][1];
                X11_XFree(attr);
            }

            ਜੇ (rotation & (XRANDR_ROTATION_ਖੱਬਾ | XRANDR_ROTATION_ਸੱਜਾ)) {
                ਬਹੁਲਕ->w = (info->ਉਚਾਈ * scale_w + 0xffff) >> 16;
                ਬਹੁਲਕ->h = (info->ਚੌੜਾਈ * scale_h + 0xffff) >> 16;
            } ਨਹੀਂਤਾਂ {
                ਬਹੁਲਕ->w = (info->ਚੌੜਾਈ * scale_w + 0xffff) >> 16;
                ਬਹੁਲਕ->h = (info->ਉਚਾਈ * scale_h + 0xffff) >> 16;
            }
            Calculate_XRand_RRefresh_ਦਰ(info, &ਬਹੁਲਕ->refresh_ਦਰ_numerator, &ਬਹੁਲਕ->refresh_ਦਰ_denominator);
            ਬਹੁਲਕ->ਅੰਦਰੂਨੀ->xrandr_ਬਹੁਲਕ = ਬਹੁਲਕ_ID;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (ਪੂਰਨ)ਬਹੁਲਕ_ID,
                    ਬਹੁਲਕ->screen_w, ਬਹੁਲਕ->screen_h, ਬਹੁਲਕ->refresh_ਦਰ_numerator, ਬਹੁਲਕ->refresh_ਦਰ_denominator);
#ਜੇ_ਅੰਤ
            ਵਾਪਸ true;
        }
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ bool Get_ਜੜ੍ਹ_ਖਿੜਕੀ_Cardinal_Property(Display *dpy, ਪੂਰਨ screen, ਅਚਲ ਅੱਖਰ *name, Uint32 *ਮੁੱਲ)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    ਜੇ (atom == None) {
        ਵਾਪਸ false;
    }

    ਪੂਰਨ real_format;
    Atom real_type;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਚੀਜ਼ਾਂ_read = 0, ਚੀਜ਼ਾਂ_ਖੱਬਾ = 0;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *propdata = ਨਿਰਾ;
    ਪੂਰਨ ਸਥਿਤੀ;
    bool ਨਤੀਜਾ = false;

    ਸਥਿਤੀ = X11_XGet_ਖਿੜਕੀ_Property(dpy, ਜੜ੍ਹ_ਖਿੜਕੀ(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &ਚੀਜ਼ਾਂ_read, &ਚੀਜ਼ਾਂ_ਖੱਬਾ, &propdata);
    ਜੇ (ਸਥਿਤੀ == Success && propdata) {
        ਜੇ (real_type == XA_CARDINAL && ਚੀਜ਼ਾਂ_read > 0) {
            ਚੋਣ (real_format) {
            ਹਾਲਤ 8:
                *ਮੁੱਲ = propdata[0];
                ਰੋਕੋ;
            ਹਾਲਤ 16:
                *ਮੁੱਲ = propdata[0] | (propdata[1] << 8);
                ਰੋਕੋ;
            ਮੂਲ:
                *ਮੁੱਲ = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                ਰੋਕੋ;
            }
            ਨਤੀਜਾ = true;
        }
        X11_XFree(propdata);
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ bool Get_ਜੜ੍ਹ_ਖਿੜਕੀ_Bool_Property(Display *dpy, ਪੂਰਨ screen, ਅਚਲ ਅੱਖਰ *name, bool *ਮੁੱਲ)
{
    Uint32 v;
    ਜੇ (Get_ਜੜ੍ਹ_ਖਿੜਕੀ_Cardinal_Property(dpy, screen, name, &v)) {
        *ਮੁੱਲ = (v != 0);
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ bool Get_ਜੜ੍ਹ_ਖਿੜਕੀ_Float_Property(Display *dpy, ਪੂਰਨ screen, ਅਚਲ ਅੱਖਰ *name, ਦਸ਼ਮਲਵ *ਮੁੱਲ)
{
    Uint32 v;
    ਜੇ (Get_ਜੜ੍ਹ_ਖਿੜਕੀ_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(ਮੁੱਲ, &v, ਆਕਾਰ(v));
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ bool IsSteamDeckOLEDDisplay(ਅਚਲ MonitorInfo *info)
{
    ਜੇ (SDL_strcmp(info->manufacturer_ਕੋਡ, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        ਜੇ (info->ਗੁਣਨਫਲ_ਕੋਡ == 0x3003 || info->ਗੁਣਨਫਲ_ਕੋਡ == 0x3004) {
            ਵਾਪਸ true;
        }
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ ਦਸ਼ਮਲਵ GetGamescopeSDRWhiteLevel(Display *dpy, ਪੂਰਨ screen, ਅਚਲ MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    ਜੇ (!dpy) {
        ਵਾਪਸ 0.0f;
    }

    ਦਸ਼ਮਲਵ SDR_white_level = 0.0f;
    bool external_display = false;
    ਜੇ (Get_ਜੜ੍ਹ_ਖਿੜਕੀ_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_ਜੜ੍ਹ_ਖਿੜਕੀ_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } ਨਹੀਂਤਾਂ ਜੇ (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (ਦਸ਼ਮਲਵ)info->max_luminance / 3.0f;
    } ਨਹੀਂਤਾਂ {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    ਵਾਪਸ SDR_white_level;
}

ਸਥਿਰ MonitorInfo *GetMonitorInfo(Display *dpy, ਪੂਰਨ screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = ਨਿਰਾ;
    ਪੂਰਨ real_format;
    Atom real_type;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਚੀਜ਼ਾਂ_read = 0, ਚੀਜ਼ਾਂ_ਖੱਬਾ = 0;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *propdata = ਨਿਰਾ;
    ਪੂਰਨ ਸਥਿਤੀ;

    *gamescope = false;

    ਜੇ (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_ਰਸਤਾ = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        ਜੇ (GAMESCOPE_DISPLAY_EDID_ਰਸਤਾ != None) {
            ਸਥਿਤੀ = X11_XGet_ਖਿੜਕੀ_Property(dpy, ਜੜ੍ਹ_ਖਿੜਕੀ(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_ਰਸਤਾ, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &ਚੀਜ਼ਾਂ_read, &ਚੀਜ਼ਾਂ_ਖੱਬਾ, &propdata);
            ਜੇ (ਸਥਿਤੀ == Success && propdata) {
                size_t ਮਾਪ = 0;
                ਖਾਲੀ *ਅੰਕੜੇ = SDL_ਲੱਦੋ_File((ਅੱਖਰ *)propdata, &ਮਾਪ);
                ਜੇ (ਅੰਕੜੇ) {
                    info = decode_edid((uchar *)ਅੰਕੜੇ, ਮਾਪ);
                    ਜੇ (info) {
                        *gamescope = true;
                    }
                    SDL_free(ਅੰਕੜੇ);
                }
            }
            ਜੇ (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    ਜੇ (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        ਜੇ (EDID != None) {
            ਪੂਰਨ nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            ਲਈ (ਪੂਰਨ i = 0; i < nprop; ++i) {
                ਜੇ (props[i] == EDID) {
                    ਸਥਿਤੀ = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &ਚੀਜ਼ਾਂ_read, &ਚੀਜ਼ਾਂ_ਖੱਬਾ, &propdata);
                    ਜੇ (ਸਥਿਤੀ == Success && propdata) {
                        info = decode_edid(propdata, ਚੀਜ਼ਾਂ_read);
                    }
                    ਜੇ (propdata) {
                        X11_XFree(propdata);
                    }
                    ਰੋਕੋ;
                }
            }

            ਜੇ (props) {
                X11_XFree(props);
            }
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X11MODES_DEBUG
    ਜੇ (info) {
        dump_monitor_info(info);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ info;
}

ਸਥਿਰ ਖਾਲੀ ਸੈੱਟ_XRand_RDisplay_Name(MonitorInfo *info, ਅੱਖਰ *name, size_t namelen, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ widthmm, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ heightmm)
{
    ਜੇ (info) {
        SDL_strlcpy(name, info->dsc_ਗੁਣਨਫਲ_name, namelen);
    }

    ਪੂਰਨ inches = (ਪੂਰਨ)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    ਜੇ (*name && inches) {
        ਅਚਲ size_t len = SDL_strlen(name);
        (ਖਾਲੀ)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, ਪੂਰਨ screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, ਅੱਖਰ *display_name, size_t display_name_ਮਾਪ)
{
    XRROutputInfo *output_info;
    ਪੂਰਨ display_x, display_y;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ display_mm_ਚੌੜਾਈ, display_mm_ਉਚਾਈ;
    SDL_Display_ਅੰਕੜੇ *displaydata;
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata;
    RRMode ਬਹੁਲਕ_ID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_ਮੁੱਲਾਂ *pixmapformats;
    ਪੂਰਨ scanline_pad;
    ਪੂਰਨ i, n;

    ਜੇ (!display || !display_name) {
        ਵਾਪਸ false; // invalid parameters
    }

    ਜੇ (!get_visualinfo(dpy, screen, &vinfo)) {
        ਵਾਪਸ false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ਜੇ (SDL_ISPIXELFORMAT_ਸੂਚਕਾਂਕਿਤ(pixelformat)) {
        ਵਾਪਸ false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ਜੇ (pixmapformats) {
        ਲਈ (i = 0; i < n; i++) {
            ਜੇ (pixmapformats[i].ਡੂੰਘਾਈ_2 == vinfo.ਡੂੰਘਾਈ_2) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ਰੋਕੋ;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    ਜੇ (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        ਵਾਪਸ false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_ਮਾਪ);
    display_mm_ਚੌੜਾਈ = output_info->mm_ਚੌੜਾਈ;
    display_mm_ਉਚਾਈ = output_info->mm_ਉਚਾਈ;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    ਜੇ (!crtc) {
        ਵਾਪਸ false; // oh well, ignore it.
    }

    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ_ID = crtc->ਬਹੁਲਕ;
    ਬਹੁਲਕ.w = crtc->ਚੌੜਾਈ;
    ਬਹੁਲਕ.h = crtc->ਉਚਾਈ;
    ਬਹੁਲਕ.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_Display_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*displaydata));
    ਜੇ (!displaydata) {
        ਵਾਪਸ false;
    }

    modedata = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ));
    ਜੇ (!modedata) {
        SDL_free(displaydata);
        ਵਾਪਸ false;
    }

    modedata->xrandr_ਬਹੁਲਕ = ਬਹੁਲਕ_ID;
    ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = modedata;

    displaydata->screen = screen;
    displaydata->visual = vinfo.visual;
    displaydata->ਡੂੰਘਾਈ_2 = vinfo.ਡੂੰਘਾਈ_2;
    displaydata->scanline_pad = scanline_pad;
    displaydata->x = display_x;
    displaydata->y = display_y;
    displaydata->use_xrandr = true;
    displaydata->xrandr_output = outputid;
    SDL_strlcpy(displaydata->connector_name, display_name, ਆਕਾਰ(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    ਸੈੱਟ_XRand_RMode_Info(dpy, res, output_crtc, ਬਹੁਲਕ_ID, &ਬਹੁਲਕ);
    ਸੈੱਟ_XRand_RDisplay_Name(info, display_name, display_name_ਮਾਪ, display_mm_ਚੌੜਾਈ, display_mm_ਉਚਾਈ);

    SDL_zero(*display);
    ਜੇ (*display_name) {
        display->name = display_name;
    }
    display->desktop_ਬਹੁਲਕ = ਬਹੁਲਕ;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->ਅੰਦਰੂਨੀ = displaydata;

    ਜੇ (info) {
        ਦਸ਼ਮਲਵ SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        ਜੇ (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } ਨਹੀਂਤਾਂ {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#ਜੇ_ਅੰਤ
        ਜੇ (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (ਦਸ਼ਮਲਵ)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ bool X11_ਜੋੜੋ_XRand_RDisplay(SDL_VideoDevice *_this, Display *dpy, ਪੂਰਨ screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    ਅੱਖਰ display_name[128];

    ਜੇ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, ਆਕਾਰ(display_name))) {
        ਵਾਪਸ true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_ਜੋੜੋ_Video_Display(&display, false);
    ਜੇ (displayID == 0) {
        ਵਾਪਸ false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    ਜੇ (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    ਵਾਪਸ true;
}


ਸਥਿਰ bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, ਪੂਰਨ screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    ਅੱਖਰ display_name[128];

    ਜੇ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, ਆਕਾਰ(display_name))) {
        ਵਾਪਸ false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_ਸੈੱਟ_Desktop_Display_ਬਹੁਲਕ(existing_display, &display.desktop_ਬਹੁਲਕ);

    // update bounds
    ਜੇ (existing_display->ਅੰਦਰੂਨੀ->x != display.ਅੰਦਰੂਨੀ->x ||
        existing_display->ਅੰਦਰੂਨੀ->y != display.ਅੰਦਰੂਨੀ->y) {
        existing_display->ਅੰਦਰੂਨੀ->x = display.ਅੰਦਰੂਨੀ->x;
        existing_display->ਅੰਦਰੂਨੀ->y = display.ਅੰਦਰੂਨੀ->y;
        SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
    }

    // update scale
    SDL_ਸੈੱਟ_Display_Content_Scale(existing_display, display.content_scale);

    // update HDR properties
    SDL_ਸੈੱਟ_Display_HDRProperties(existing_display, &display.HDR);

    // SDL_DisplayData is updated piece-meal above, free our local copy of this data
    SDL_free(display.ਅੰਦਰੂਨੀ);

    ਵਾਪਸ true;
}

ਸਥਿਰ XRRScreenResources *X11_GetScreenResources(Display *dpy, ਪੂਰਨ screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, ਜੜ੍ਹ_ਖਿੜਕੀ(dpy, screen));
    ਜੇ (!res || res->noutput == 0) {
        ਜੇ (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, ਜੜ੍ਹ_ਖਿੜਕੀ(dpy, screen));
    }
    ਵਾਪਸ res;
}

ਖਾਲੀ X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    ਅਚਲ ਪੂਰਨ screencount = Screen_ਗਿਣਤੀ(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(ਨਿਰਾ);
    ਜੇ (!displays) {
        ਵਾਪਸ;
    }

    ਲਈ (ਪੂਰਨ screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ਜੇ (!res) {
            ਜਾਰੀ;
        }

        ਲਈ (ਪੂਰਨ i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ਅਚਲ SDL_Display_ਅੰਕੜੇ *displaydata = display->ਅੰਦਰੂਨੀ;
            ਜੇ (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

ਸਥਿਰ ਖਾਲੀ X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    ਅਚਲ ਪੂਰਨ screencount = Screen_ਗਿਣਤੀ(dpy);
    ਪੂਰਨ ਅੰਕ_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&ਅੰਕ_displays);
    ਜੇ (!displays) {
        ਵਾਪਸ;
    }

    ਲਈ (ਪੂਰਨ screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ਜੇ (!res) {
            ਜਾਰੀ;
        }

        ਲਈ (ਪੂਰਨ output = 0; output < res->noutput; output++) {
            ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ_displays; ++i) {
                ਜੇ (!displays[i]) {
                    // We already removed this display from the list
                    ਜਾਰੀ;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                ਅਚਲ SDL_Display_ਅੰਕੜੇ *displaydata = display->ਅੰਦਰੂਨੀ;
                ਜੇ (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    ਰੋਕੋ;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ_displays; ++i) {
        ਜੇ (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ਅਚਲ SDL_Display_ਅੰਕੜੇ *displaydata = display->ਅੰਦਰੂਨੀ;
            ਜੇ (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

ਸਥਿਰ ਖਾਲੀ X11_HandleXRandROutputChange(SDL_VideoDevice *_this, ਅਚਲ XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = ਨਿਰਾ;
    ਪੂਰਨ i;

#ਜੇ 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) ev->output, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) ev->crtc, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) ev->ਬਹੁਲਕ, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) ev->rotation, (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) ev->connection);
#ਜੇ_ਅੰਤ

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(ਨਿਰਾ);
    ਜੇ (displays) {
        ਲਈ (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            ਅਚਲ SDL_Display_ਅੰਕੜੇ *displaydata = thisdisplay->ਅੰਦਰੂਨੀ;
            ਜੇ (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                ਰੋਕੋ;
            }
        }
        SDL_free(displays);
    }

    ਜੇ (ev->connection == RR_Disconnected) { // output is going away
        ਜੇ (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            ਜੇ (_this->ਅੰਕ_displays == 1) {
                generic_display = X11_ਜੋੜੋ_Generic_Display(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            ਜੇ (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } ਨਹੀਂਤਾਂ ਜੇ (ev->connection == RR_Connected) { // output is coming online
        ਜੇ (!display) {
            Display *dpy = ev->display;
            ਅਚਲ ਪੂਰਨ screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ਜੇ (res) {
                X11_ਜੋੜੋ_XRand_RDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

ਖਾਲੀ X11_HandleXRandREvent(SDL_VideoDevice *_this, ਅਚਲ XEvent *xevent)
{
    SDL_Video_ਅੰਕੜੇ *videodata = _this->ਅੰਦਰੂਨੀ;
    SDL_assert(xevent->type == (videodata->xrandr_event_ਅਧਾਰ + RRNotify));

    ਚੋਣ (((ਅਚਲ XRRNotifyEvent *)xevent)->subtype) {
    ਹਾਲਤ RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (ਅਚਲ XRROutputChangeNotifyEvent *)xevent);
        ਰੋਕੋ;
    ਮੂਲ:
        ਰੋਕੋ;
    }
}

ਸਥਿਰ ਖਾਲੀ X11_ਛਾਂਟੋ_Outputs_By_ਤਰਜੀਹ_Hint(SDL_VideoDevice *_this)
{
    ਅਚਲ ਅੱਖਰ *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ਤਰਜੀਹ);

    ਜੇ (name_hint) {
        ਅੱਖਰ *saveptr;
        ਅੱਖਰ *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(ਆਕਾਰ(SDL_VideoDisplay *) * _this->ਅੰਕ_displays);

        ਜੇ (str && sorted_list) {
            ਪੂਰਨ sorted_ਸੂਚਕਾਂਕ = 0;

            // Sort the requested displays to the front of the list.
            ਅਚਲ ਅੱਖਰ *token = SDL_strtok_r(str, ",", &saveptr);
            ਜਦੋਂ (token) {
                ਲਈ (ਪੂਰਨ i = 0; i < _this->ਅੰਕ_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    ਜੇ (d) {
                        SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ = d->ਅੰਦਰੂਨੀ;
                        ਜੇ (SDL_strcmp(token, ਅੰਕੜੇ->connector_name) == 0) {
                            sorted_list[sorted_ਸੂਚਕਾਂਕ++] = d;
                            _this->displays[i] = ਨਿਰਾ;
                            ਰੋਕੋ;
                        }
                    }
                }

                token = SDL_strtok_r(ਨਿਰਾ, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            ਲਈ (ਪੂਰਨ i = 0; i < _this->ਅੰਕ_displays; ++i) {
                ਜੇ (_this->displays[i]) {
                    sorted_list[sorted_ਸੂਚਕਾਂਕ++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, ਆਕਾਰ(SDL_VideoDisplay *) * _this->ਅੰਕ_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ਸਥਿਰ bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    Display *dpy = ਅੰਕੜੇ->display;
    ਅਚਲ ਪੂਰਨ screencount = Screen_ਗਿਣਤੀ(dpy);
    ਅਚਲ ਪੂਰਨ default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, ਜੜ੍ਹ_ਖਿੜਕੀ(dpy, default_screen));
    ਪੂਰਨ xrandr_error_ਅਧਾਰ = 0;
    ਪੂਰਨ looking_for_primary;
    ਪੂਰਨ output;
    ਪੂਰਨ screen;

    ਜੇ (!X11_XRRQueryExtension(dpy, &ਅੰਕੜੇ->xrandr_event_ਅਧਾਰ, &xrandr_error_ਅਧਾਰ)) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("XRRQueryExtension failed");
    }

    ਲਈ (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        ਲਈ (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            ਜੇ (looking_for_primary && (screen != default_screen)) {
                ਜਾਰੀ;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ਜੇ (!res) {
                ਜਾਰੀ;
            }

            ਲਈ (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                ਜੇ ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    ਜਾਰੀ;
                }
                ਜੇ (!X11_ਜੋੜੋ_XRand_RDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    ਰੋਕੋ;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_ਨਿਵੇਸ਼(dpy, ਜੜ੍ਹ_ਖਿੜਕੀ(dpy, screen), RROutput_Change_Notify_ਨਕਾਬ);
        }
    }

    ਜੇ (_this->ਅੰਕ_displays == 0) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("No available displays");
    }

    X11_ਛਾਂਟੋ_Outputs_By_ਤਰਜੀਹ_Hint(_this);

    ਵਾਪਸ true;
}
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
ਸਥਿਰ bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    ਜੇ (X11_ਜੋੜੋ_Generic_Display(_this, true) == 0) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
        ਪੂਰਨ xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        ਜੇ (CheckXRandR(ਅੰਕੜੇ->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            ਵਾਪਸ true;
        }
    }
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    ਵਾਪਸ X11_InitModes_StdXlib(_this);
}

bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
    SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ = sdl_display->ਅੰਦਰੂਨੀ;
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;

    /* Unfortunately X11 requires the window to be created with the correct
     * visual and depth ahead of time, but the SDL API allows you to create
     * a window before setting the fullscreen display mode.  This means that
     * we have to use the same format for all windows and all display modes.
     * (or support recreating the window with a new visual behind the scenes)
     */
    SDL_zero(ਬਹੁਲਕ);
    ਬਹੁਲਕ.format = sdl_display->desktop_ਬਹੁਲਕ.format;

    ਜੇ (ਅੰਕੜੇ->use_xrandr) {
        Display *display = _this->ਅੰਦਰੂਨੀ->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, ਅੰਕੜੇ->screen));
        ਜੇ (res) {
            SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata;
            XRROutputInfo *output_info;
            ਪੂਰਨ i;

            output_info = X11_XRRGetOutputInfo(display, res, ਅੰਕੜੇ->xrandr_output);
            ਜੇ (output_info && output_info->connection != RR_Disconnected) {
                ਲਈ (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ));
                    ਜੇ (!modedata) {
                        ਜਾਰੀ;
                    }
                    ਬਹੁਲਕ.ਅੰਦਰੂਨੀ = modedata;

                    ਜੇ (!ਸੈੱਟ_XRand_RMode_Info(display, res, output_info->crtc, output_info->modes[i], &ਬਹੁਲਕ) ||
                        !SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(sdl_display, &ਬਹੁਲਕ)) {
                        SDL_free(modedata);
                    }
                }
            }
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
        }
    }
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XRANDR
    ਵਾਪਸ true;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
ਸਥਿਰ ਪੂਰਨ (*Pre_XRRSet_Screen_ਮਾਪ_Error_Handler)(Display *, XErrorEvent *) = ਨਿਰਾ;
ਸਥਿਰ ਪੂਰਨ SDL_XRRSet_Screen_ਮਾਪ_Err_Handler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    ਜੇ ((e->error_ਕੋਡ == Bad_ਮੇਲ) || (e->error_ਕੋਡ == Bad_ਮੁੱਲ)) {
        ਵਾਪਸ 0;
    }

    ਵਾਪਸ Pre_XRRSet_Screen_ਮਾਪ_Error_Handler(d, e);
}
#ਜੇ_ਅੰਤ

bool X11_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_Video_ਅੰਕੜੇ *viddata = _this->ਅੰਦਰੂਨੀ;
    SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ = sdl_display->ਅੰਦਰੂਨੀ;

    viddata->ਆਖਰੀ_ਬਹੁਲਕ_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_ਸਮਾਂ * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    ਜੇ (!viddata->is_xwayland) {
        ਜੇ (sdl_display->current_ਬਹੁਲਕ != ਬਹੁਲਕ) {
            ਅੰਕੜੇ->ਬਹੁਲਕ_switch_deadline_ns = SDL_GetTicksNS() + ਬਹੁਲਕ_SWITCH_TIMEOUT_NS;
        } ਨਹੀਂਤਾਂ {
            ਅੰਕੜੇ->ਬਹੁਲਕ_switch_deadline_ns = 0;
        }
    }

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XRANDR
    ਜੇ (ਅੰਕੜੇ->use_xrandr) {
        Display *display = viddata->display;
        SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *modedata = ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;
        ਪੂਰਨ mm_ਚੌੜਾਈ, mm_ਉਚਾਈ;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        ਸਥਿਤੀ_2 ਸਥਿਤੀ;

        res = X11_XRRGetScreenResources(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, ਅੰਕੜੇ->screen));
        ਜੇ (!res) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, ਅੰਕੜੇ->xrandr_output);
        ਜੇ (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        ਜੇ (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("Couldn't get XRandR crtc info");
        }

        ਜੇ (crtc->ਬਹੁਲਕ == modedata->xrandr_ਬਹੁਲਕ) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->ਬਹੁਲਕ, crtc->ਚੌੜਾਈ, crtc->ਉਚਾਈ);
#ਜੇ_ਅੰਤ
            ਸਥਿਤੀ = Success;
            ਜਾਓ freeInfo;
        }

        X11_XGrabServer(display);
        ਸਥਿਤੀ = X11_XRRSetCrtcConfig(display, res, output_info->crtc, Current_ਸਮਾਂ,
                                      0, 0, None, crtc->rotation, ਨਿਰਾ, 0);
        ਜੇ (ਸਥਿਤੀ != Success) {
            ਜਾਓ ungrabServer;
        }

        mm_ਚੌੜਾਈ = ਬਹੁਲਕ->w * Display_ਚੌੜਾਈ_MM(display, ਅੰਕੜੇ->screen) / Display_ਚੌੜਾਈ(display, ਅੰਕੜੇ->screen);
        mm_ਉਚਾਈ = ਬਹੁਲਕ->h * Display_ਉਚਾਈ_MM(display, ਅੰਕੜੇ->screen) / Display_ਉਚਾਈ(display, ਅੰਕੜੇ->screen);

        /* !!! FIXME: this can get into a problem scenario when a window is
           bigger than a physical monitor in a configuration where one screen
           spans multiple physical monitors. A detailed reproduction case is
           discussed at https://github.com/libsdl-org/SDL/issues/4561 ...
           for now we cheat and just catch the X11 error and carry on, which
           is likely to cause subtle issues but is better than outright
           crashing */
        X11_XSync(display, False);
        Pre_XRRSet_Screen_ਮਾਪ_Error_Handler = X11_XSetErrorHandler(SDL_XRRSet_Screen_ਮਾਪ_Err_Handler);
        X11_XRRSet_Screen_ਮਾਪ(display, ਜੜ੍ਹ_ਖਿੜਕੀ(display, ਅੰਕੜੇ->screen),
                             ਬਹੁਲਕ->w, ਬਹੁਲਕ->h, mm_ਚੌੜਾਈ, mm_ਉਚਾਈ);
        X11_XSync(display, False);
        X11_XSetErrorHandler(Pre_XRRSet_Screen_ਮਾਪ_Error_Handler);

        ਸਥਿਤੀ = X11_XRRSetCrtcConfig(display, res, output_info->crtc, Current_ਸਮਾਂ,
                                      crtc->x, crtc->y, modedata->xrandr_ਬਹੁਲਕ, crtc->rotation,
                                      &ਅੰਕੜੇ->xrandr_output, 1);

    ungrabServer:
        X11_XUngrabServer(display);
    freeInfo:
        X11_XRRFreeCrtcInfo(crtc);
        X11_XRRFreeOutputInfo(output_info);
        X11_XRRFreeScreenResources(res);

        ਜੇ (ਸਥਿਤੀ != Success) {
            ਵਾਪਸ SDL_ਸੈੱਟ_Error("X11_XRRSetCrtcConfig failed");
        }
    }
#ਨਹੀਂਤਾਂ
    (ਖਾਲੀ)ਅੰਕੜੇ;
#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XRANDR

    ਵਾਪਸ true;
}

ਖਾਲੀ X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Display_ਅੰਕੜੇ *ਅੰਕੜੇ = sdl_display->ਅੰਦਰੂਨੀ;

    rect->x = ਅੰਕੜੇ->x;
    rect->y = ਅੰਕੜੇ->y;
    rect->w = sdl_display->current_ਬਹੁਲਕ->w;
    rect->h = sdl_display->current_ਬਹੁਲਕ->h;
    ਵਾਪਸ true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    Display *display = ਅੰਕੜੇ->display;
    Atom _NET_WORKAREA;
    ਪੂਰਨ real_format;
    Atom real_type;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਚੀਜ਼ਾਂ_read = 0, ਚੀਜ਼ਾਂ_ਖੱਬਾ = 0;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *propdata = ਨਿਰਾ;
    bool ਨਤੀਜਾ = false;

    ਜੇ (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        ਵਾਪਸ false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    ਪੂਰਨ ਸਥਿਤੀ = X11_XGet_ਖਿੜਕੀ_Property(display, Default_ਜੜ੍ਹ_ਖਿੜਕੀ(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &ਚੀਜ਼ਾਂ_read,
                                    &ਚੀਜ਼ਾਂ_ਖੱਬਾ, &propdata);
    ਜੇ ((ਸਥਿਤੀ == Success) && (ਚੀਜ਼ਾਂ_read >= 4)) {
        ਅਚਲ ਲੰਮਾ *p = (ਲੰਮਾ *)propdata;
        ਅਚਲ SDL_Rect usable = { (ਪੂਰਨ)p[0], (ਪੂਰਨ)p[1], (ਪੂਰਨ)p[2], (ਪੂਰਨ)p[3] };
        ਨਤੀਜਾ = true;
        ਜੇ (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    ਜੇ (propdata) {
        X11_XFree(propdata);
    }

    ਵਾਪਸ ਨਤੀਜਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11
