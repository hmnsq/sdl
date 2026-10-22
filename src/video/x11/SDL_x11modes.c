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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11

#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11settings.h"
#ಅನ್ತರ್ಭಾವ "edid.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_displayevents_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_pixels_c.h"

// #define X11MODES_DEBUG

/* Timeout and revert mode switches if the timespan has elapsed without the window becoming fullscreen.
 * 5 seconds seems good from testing.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಬಹುಲಕ_SWITCH_TIMEOUT_NS SDL_NS_ಪ್ರತಿ_ಎರಡನೇ * 5

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

ದಶಮಾಂಶ X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    ದ್ವಿಗುಣ scale_ಗುಣಕ_2 = 0.0;

    // First use the forced scaling factor specified by the app/user
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_ಗುಣಕ);
    ಆದರೆ (hint && *hint) {
        ದ್ವಿಗುಣ ಮೌಲ್ಯ = SDL_atof(hint);
        ಆದರೆ (ಮೌಲ್ಯ >= 1.0f && ಮೌಲ್ಯ <= 10.0f) {
            scale_ಗುಣಕ_2 = ಮೌಲ್ಯ;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    ಆದರೆ (scale_ಗುಣಕ_2 <= 0.0) {
        ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2, real_format;
        Atom real_type;
        Atom res_mgr;
        ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ವಸ್ತುಗಳು_read, ವಸ್ತುಗಳು_ಎಡ;
        ಅಕ್ಷರ *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        ಸ್ಥಿತಿ_2 = X11_XGet_ಕಿಟಕಿ_Property(display, ಬೇರು_ಕಿಟಕಿ(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ,
                                        (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ **)&resource_manager);

        ಆದರೆ (ಸ್ಥಿತಿ_2 == Success && resource_manager) {
            owns_resource_manager = true;
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        ಆದರೆ (resource_manager) {
            XrmDatabase db;
            Xrm_ಮೌಲ್ಯ ಮೌಲ್ಯ;
            ಅಕ್ಷರ *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            ಆದರೆ (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &ಮೌಲ್ಯ)) {
                ಆದರೆ (ಮೌಲ್ಯ.addr && type && SDL_strcmp(type, "String") == 0) {
                    ಪೂರ್ಣಾಂಕ dpi = SDL_atoi(ಮೌಲ್ಯ.addr);
                    scale_ಗುಣಕ_2  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            ಆದರೆ (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    ಆದರೆ (scale_ಗುಣಕ_2 <= 0.0) {
        scale_ಗುಣಕ_2 = X11_Get_Xsettings_Client_Int_ಕೀಲಿ(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        ಆದರೆ (scale_ಗುಣಕ_2 <= 0.0) {
            ಪೂರ್ಣಾಂಕ dpi = X11_Get_Xsettings_Client_Int_ಕೀಲಿ(client, "Xft/DPI", -1);
            ಆದರೆ (dpi > 0) {
                scale_ಗುಣಕ_2 = (ದ್ವಿಗುಣ) dpi / 1024.0;
                scale_ಗುಣಕ_2 /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    ಆದರೆ (scale_ಗುಣಕ_2 <= 0.0) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *scale_str = SDL_getenv("GDK_SCALE");
        ಆದರೆ (scale_str) {
            scale_ಗುಣಕ_2 = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    ಆದರೆ (scale_ಗುಣಕ_2 <= 0.0) {
        scale_ಗುಣಕ_2 = 1.0;
    }

    ಹಿಂತಿರುಗಿ (ದಶಮಾಂಶ)scale_ಗುಣಕ_2;
}

ದಶಮಾಂಶ X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ X11_GetGlobalContentScale(_this->ಆಂತರಿಕ->display, _this->ಆಂತರಿಕ->xsettings_ದತ್ತಾಂಶ.xsettings);
}

ಸ್ಥಿರ bool get_visualinfo(Display *display, ಪೂರ್ಣಾಂಕ screen, XVisualInfo *vinfo)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    ಪೂರ್ಣಾಂಕ ಆಳ_2;

    // Look for an exact visual, if requested
    ಆದರೆ (visual_id && *visual_id) {
        XVisualInfo *vi, ಮಾದರಿ;
        ಪೂರ್ಣಾಂಕ nvis;

        SDL_zero(ಮಾದರಿ);
        ಮಾದರಿ.visualid = SDL_strtol(visual_id, ಖಾಲಿ, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &ಮಾದರಿ, &nvis);
        ಆದರೆ (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            ಹಿಂತಿರುಗಿ true;
        }
    }

    ಆಳ_2 = Default_ಆಳ(display, screen);
    ಆದರೆ ((X11_Use_ನೇರ_Color_Visuals() &&
         X11_XMatchVisualInfo(display, screen, ಆಳ_2, ನೇರ_Color, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, ಆಳ_2, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, ಆಳ_2, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, ಆಳ_2, StaticColor, vinfo)) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    ಪೂರ್ಣಾಂಕ nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    ಆದರೆ (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    ಆದರೆ (vinfo->class == ನೇರ_Color || vinfo->class == TrueColor) {
        ಪೂರ್ಣಾಂಕ bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_ಮುಖವಾಡ;
        Gmask = vinfo->visual->green_ಮುಖವಾಡ;
        Bmask = vinfo->visual->blue_ಮುಖವಾಡ;
        ಆದರೆ (vinfo->ಆಳ_2 == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } ಇಲ್ಲದಿದ್ದರೆ {
            Amask = 0;
        }

        bpp = vinfo->ಆಳ_2;
        ಆದರೆ (bpp == 24) {
            ಪೂರ್ಣಾಂಕ i, n;
            XPixmap_Format_ಮೌಲ್ಯಗಳು *p = X11_XListPixmapFormats(display, &n);
            ಆದರೆ (p) {
                ಗಾಗಿ (i = 0; i < n; ++i) {
                    ಆದರೆ (p[i].ಆಳ_2 == 24) {
                        bpp = p[i].ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel;
                        ನಿಲ್ಲಿಸು;
                    }
                }
                X11_XFree(p);
            }
        }

        ಹಿಂತಿರುಗಿ SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    ಆದರೆ (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        ಆಯ್ಕೆ (vinfo->ಆಳ_2) {
        ಸ್ಥಿತಿ 8:
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_INDEX8;
        ಸ್ಥಿತಿ 4:
            ಆದರೆ (Bitmap_ಬಿಟ್_ಕ್ರಮ(display) == LSBFirst) {
                ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_INDEX4LSB;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        ಸ್ಥಿತಿ 1:
            ಆದರೆ (Bitmap_ಬಿಟ್_ಕ್ರಮ(display) == LSBFirst) {
                ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_INDEX1LSB;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_UNKNOWN;
}

ಸ್ಥಿರ SDL_DisplayID X11_ಕೂಡಿಸು_Generic_Display(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    Display *dpy = ದತ್ತಾಂಶ->display;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ default_screen = DefaultScreen(dpy);
    Screen *screen = Screen_ದ_Display(dpy, default_screen);
    ಪೂರ್ಣಾಂಕ scanline_pad, n, i;
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata;
    SDL_Display_ದತ್ತಾಂಶ *displaydata;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    XPixmap_Format_ಮೌಲ್ಯಗಳು *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    ಆದರೆ (!get_visualinfo(dpy, default_screen, &vinfo)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(pixelformat)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Palettized video modes are no longer supported");
    }

    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.w = ಅಗಲ_ದ_Screen(screen);
    ಬಹುಲಕ.h = ಎತ್ತರ_ದ_Screen(screen);
    ಬಹುಲಕ.format = pixelformat;

    displaydata = (SDL_Display_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*displaydata));
    ಆದರೆ (!displaydata) {
        ಹಿಂತಿರುಗಿ false;
    }

    modedata = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ));
    ಆದರೆ (!modedata) {
        SDL_free(displaydata);
        ಹಿಂತಿರುಗಿ false;
    }
    ಬಹುಲಕ.ಆಂತರಿಕ = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->ಆಳ_2 = vinfo.ಆಳ_2;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ಆದರೆ (pixmapformats) {
        ಗಾಗಿ (i = 0; i < n; ++i) {
            ಆದರೆ (pixmapformats[i].ಆಳ_2 == vinfo.ಆಳ_2) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ನಿಲ್ಲಿಸು;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (ಅಕ್ಷರ *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_ಬಹುಲಕ = ಬಹುಲಕ;
    display.ಆಂತರಿಕ = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    ಹಿಂತಿರುಗಿ SDL_ಕೂಡಿಸು_Video_Display(&display, send_event);
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR

ಸ್ಥಿರ ಶೂನ್ಯ X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(ಖಾಲಿ);
    ಆದರೆ (displays) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ಸ್ಥಿರಾಂಕ SDL_Display_ದತ್ತಾಂಶ *displaydata = display->ಆಂತರಿಕ;
            ಆದರೆ (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

ಸ್ಥಿರ bool CheckXRandR(Display *display, ಪೂರ್ಣಾಂಕ *major, ಪೂರ್ಣಾಂಕ *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XRANDR_DISABLED_BY_DEFAULT
    ಆದರೆ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ false;
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಆದರೆ (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ false;
    }
#ಆದರೆ_ಅಂತ್ಯ // XRANDR_DISABLED_BY_DEFAULT

    ಆದರೆ (!SDL_X11_HAVE_XRANDR) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    ಆದರೆ (!X11_XRRQuery_ಆವೃತ್ತಿ(display, major, minor)) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#ಆದರೆ_ಅಂತ್ಯ
        *major = *minor = 0;
        ಹಿಂತಿರುಗಿ false;
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿಸು XRANDR_ROTATION_ಎಡ  (1 << 1)
#ವ್ಯಾಖ್ಯಾನಿಸು XRANDR_ROTATION_ಬಲ (1 << 3)

ಸ್ಥಿರ ಶೂನ್ಯ Calculate_XRand_RRefresh_ದರ(ಸ್ಥಿರಾಂಕ XRRModeInfo *info, ಪೂರ್ಣಾಂಕ *numerator, ಪೂರ್ಣಾಂಕ *denominator)
{
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ v_ಒಟ್ಟು_2 = info->v_ಒಟ್ಟು_2;

    ಆದರೆ (info->ಬಹುಲಕ_Flags & RR_Double_ಪರಿಶೀಲನೆ) {
        // doublescan doubles the number of lines
        v_ಒಟ್ಟು_2 *= 2;
    }

    ಆದರೆ (info->ಬಹುಲಕ_Flags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        v_ಒಟ್ಟು_2 /= 2;
    }

    ಆದರೆ (info->h_ಒಟ್ಟು_2 && v_ಒಟ್ಟು_2) {
        *numerator = info->dotClock;
        *denominator = (info->h_ಒಟ್ಟು_2 * v_ಒಟ್ಟು_2);
    } ಇಲ್ಲದಿದ್ದರೆ {
        *numerator = 0;
        *denominator = 0;
    }
}

ಸ್ಥಿರ bool ಗಣ_XRand_RMode_Info(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode ಬಹುಲಕ_ID, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < res->nmode; ++i) {
        ಸ್ಥಿರಾಂಕ XRRModeInfo *info = &res->modes[i];
        ಆದರೆ (info->id == ಬಹುಲಕ_ID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtc_Transform_ಗುಣಲಕ್ಷಣಗಳು *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            ಆದರೆ (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            ಆದರೆ (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.ಮಾತೃಕೆ[0][0];
                scale_h = attr->currentTransform.ಮಾತೃಕೆ[1][1];
                X11_XFree(attr);
            }

            ಆದರೆ (rotation & (XRANDR_ROTATION_ಎಡ | XRANDR_ROTATION_ಬಲ)) {
                ಬಹುಲಕ->w = (info->ಎತ್ತರ * scale_w + 0xffff) >> 16;
                ಬಹುಲಕ->h = (info->ಅಗಲ * scale_h + 0xffff) >> 16;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಬಹುಲಕ->w = (info->ಅಗಲ * scale_w + 0xffff) >> 16;
                ಬಹುಲಕ->h = (info->ಎತ್ತರ * scale_h + 0xffff) >> 16;
            }
            Calculate_XRand_RRefresh_ದರ(info, &ಬಹುಲಕ->refresh_ದರ_numerator, &ಬಹುಲಕ->refresh_ದರ_denominator);
            ಬಹುಲಕ->ಆಂತರಿಕ->xrandr_ಬಹುಲಕ = ಬಹುಲಕ_ID;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (ಪೂರ್ಣಾಂಕ)ಬಹುಲಕ_ID,
                    ಬಹುಲಕ->screen_w, ಬಹುಲಕ->screen_h, ಬಹುಲಕ->refresh_ದರ_numerator, ಬಹುಲಕ->refresh_ದರ_denominator);
#ಆದರೆ_ಅಂತ್ಯ
            ಹಿಂತಿರುಗಿ true;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ bool Get_ಬೇರು_ಕಿಟಕಿ_Cardinal_Property(Display *dpy, ಪೂರ್ಣಾಂಕ screen, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, Uint32 *ಮೌಲ್ಯ)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    ಆದರೆ (atom == None) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಪೂರ್ಣಾಂಕ real_format;
    Atom real_type;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ವಸ್ತುಗಳು_read = 0, ವಸ್ತುಗಳು_ಎಡ = 0;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *propdata = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2;
    bool ಫಲಿತಾಂಶ = false;

    ಸ್ಥಿತಿ_2 = X11_XGet_ಕಿಟಕಿ_Property(dpy, ಬೇರು_ಕಿಟಕಿ(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
    ಆದರೆ (ಸ್ಥಿತಿ_2 == Success && propdata) {
        ಆದರೆ (real_type == XA_CARDINAL && ವಸ್ತುಗಳು_read > 0) {
            ಆಯ್ಕೆ (real_format) {
            ಸ್ಥಿತಿ 8:
                *ಮೌಲ್ಯ = propdata[0];
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ 16:
                *ಮೌಲ್ಯ = propdata[0] | (propdata[1] << 8);
                ನಿಲ್ಲಿಸು;
            ಪೂರ್ವನಿಯೋಜಿತ:
                *ಮೌಲ್ಯ = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                ನಿಲ್ಲಿಸು;
            }
            ಫಲಿತಾಂಶ = true;
        }
        X11_XFree(propdata);
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ bool Get_ಬೇರು_ಕಿಟಕಿ_Bool_Property(Display *dpy, ಪೂರ್ಣಾಂಕ screen, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, bool *ಮೌಲ್ಯ)
{
    Uint32 v;
    ಆದರೆ (Get_ಬೇರು_ಕಿಟಕಿ_Cardinal_Property(dpy, screen, name, &v)) {
        *ಮೌಲ್ಯ = (v != 0);
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ bool Get_ಬೇರು_ಕಿಟಕಿ_Float_Property(Display *dpy, ಪೂರ್ಣಾಂಕ screen, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ದಶಮಾಂಶ *ಮೌಲ್ಯ)
{
    Uint32 v;
    ಆದರೆ (Get_ಬೇರು_ಕಿಟಕಿ_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(ಮೌಲ್ಯ, &v, ಗಾತ್ರ(v));
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ bool IsSteamDeckOLEDDisplay(ಸ್ಥಿರಾಂಕ MonitorInfo *info)
{
    ಆದರೆ (SDL_strcmp(info->manufacturer_ಸಂಕೇತ, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        ಆದರೆ (info->ಗುಣಲಬ್ಧ_ಸಂಕೇತ == 0x3003 || info->ಗುಣಲಬ್ಧ_ಸಂಕೇತ == 0x3004) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ ದಶಮಾಂಶ GetGamescopeSDRWhiteLevel(Display *dpy, ಪೂರ್ಣಾಂಕ screen, ಸ್ಥಿರಾಂಕ MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    ಆದರೆ (!dpy) {
        ಹಿಂತಿರುಗಿ 0.0f;
    }

    ದಶಮಾಂಶ SDR_white_level = 0.0f;
    bool external_display = false;
    ಆದರೆ (Get_ಬೇರು_ಕಿಟಕಿ_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_ಬೇರು_ಕಿಟಕಿ_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (ದಶಮಾಂಶ)info->max_luminance / 3.0f;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    ಹಿಂತಿರುಗಿ SDR_white_level;
}

ಸ್ಥಿರ MonitorInfo *GetMonitorInfo(Display *dpy, ಪೂರ್ಣಾಂಕ screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ real_format;
    Atom real_type;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ವಸ್ತುಗಳು_read = 0, ವಸ್ತುಗಳು_ಎಡ = 0;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *propdata = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2;

    *gamescope = false;

    ಆದರೆ (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_ಮಾರ್ಗ = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        ಆದರೆ (GAMESCOPE_DISPLAY_EDID_ಮಾರ್ಗ != None) {
            ಸ್ಥಿತಿ_2 = X11_XGet_ಕಿಟಕಿ_Property(dpy, ಬೇರು_ಕಿಟಕಿ(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_ಮಾರ್ಗ, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
            ಆದರೆ (ಸ್ಥಿತಿ_2 == Success && propdata) {
                size_t ಗಾತ್ರ_2 = 0;
                ಶೂನ್ಯ *ದತ್ತಾಂಶ = SDL_ತುಂಬು_File((ಅಕ್ಷರ *)propdata, &ಗಾತ್ರ_2);
                ಆದರೆ (ದತ್ತಾಂಶ) {
                    info = decode_edid((uchar *)ದತ್ತಾಂಶ, ಗಾತ್ರ_2);
                    ಆದರೆ (info) {
                        *gamescope = true;
                    }
                    SDL_free(ದತ್ತಾಂಶ);
                }
            }
            ಆದರೆ (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    ಆದರೆ (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        ಆದರೆ (EDID != None) {
            ಪೂರ್ಣಾಂಕ nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nprop; ++i) {
                ಆದರೆ (props[i] == EDID) {
                    ಸ್ಥಿತಿ_2 = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &ವಸ್ತುಗಳು_read, &ವಸ್ತುಗಳು_ಎಡ, &propdata);
                    ಆದರೆ (ಸ್ಥಿತಿ_2 == Success && propdata) {
                        info = decode_edid(propdata, ವಸ್ತುಗಳು_read);
                    }
                    ಆದರೆ (propdata) {
                        X11_XFree(propdata);
                    }
                    ನಿಲ್ಲಿಸು;
                }
            }

            ಆದರೆ (props) {
                X11_XFree(props);
            }
        }
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X11MODES_DEBUG
    ಆದರೆ (info) {
        dump_monitor_info(info);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ info;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಗಣ_XRand_RDisplay_Name(MonitorInfo *info, ಅಕ್ಷರ *name, size_t namelen, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ widthmm, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ heightmm)
{
    ಆದರೆ (info) {
        SDL_strlcpy(name, info->dsc_ಗುಣಲಬ್ಧ_name, namelen);
    }

    ಪೂರ್ಣಾಂಕ inches = (ಪೂರ್ಣಾಂಕ)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    ಆದರೆ (*name && inches) {
        ಸ್ಥಿರಾಂಕ size_t len = SDL_strlen(name);
        (ಶೂನ್ಯ)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, ಪೂರ್ಣಾಂಕ screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, ಅಕ್ಷರ *display_name, size_t display_name_ಗಾತ್ರ)
{
    XRROutputInfo *output_info;
    ಪೂರ್ಣಾಂಕ display_x, display_y;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ display_mm_ಅಗಲ, display_mm_ಎತ್ತರ;
    SDL_Display_ದತ್ತಾಂಶ *displaydata;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata;
    RRMode ಬಹುಲಕ_ID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_ಮೌಲ್ಯಗಳು *pixmapformats;
    ಪೂರ್ಣಾಂಕ scanline_pad;
    ಪೂರ್ಣಾಂಕ i, n;

    ಆದರೆ (!display || !display_name) {
        ಹಿಂತಿರುಗಿ false; // invalid parameters
    }

    ಆದರೆ (!get_visualinfo(dpy, screen, &vinfo)) {
        ಹಿಂತಿರುಗಿ false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(pixelformat)) {
        ಹಿಂತಿರುಗಿ false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    ಆದರೆ (pixmapformats) {
        ಗಾಗಿ (i = 0; i < n; i++) {
            ಆದರೆ (pixmapformats[i].ಆಳ_2 == vinfo.ಆಳ_2) {
                scanline_pad = pixmapformats[i].scanline_pad;
                ನಿಲ್ಲಿಸು;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    ಆದರೆ (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        ಹಿಂತಿರುಗಿ false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_ಗಾತ್ರ);
    display_mm_ಅಗಲ = output_info->mm_ಅಗಲ;
    display_mm_ಎತ್ತರ = output_info->mm_ಎತ್ತರ;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    ಆದರೆ (!crtc) {
        ಹಿಂತಿರುಗಿ false; // oh well, ignore it.
    }

    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ_ID = crtc->ಬಹುಲಕ;
    ಬಹುಲಕ.w = crtc->ಅಗಲ;
    ಬಹುಲಕ.h = crtc->ಎತ್ತರ;
    ಬಹುಲಕ.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_Display_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*displaydata));
    ಆದರೆ (!displaydata) {
        ಹಿಂತಿರುಗಿ false;
    }

    modedata = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ));
    ಆದರೆ (!modedata) {
        SDL_free(displaydata);
        ಹಿಂತಿರುಗಿ false;
    }

    modedata->xrandr_ಬಹುಲಕ = ಬಹುಲಕ_ID;
    ಬಹುಲಕ.ಆಂತರಿಕ = modedata;

    displaydata->screen = screen;
    displaydata->visual = vinfo.visual;
    displaydata->ಆಳ_2 = vinfo.ಆಳ_2;
    displaydata->scanline_pad = scanline_pad;
    displaydata->x = display_x;
    displaydata->y = display_y;
    displaydata->use_xrandr = true;
    displaydata->xrandr_output = outputid;
    SDL_strlcpy(displaydata->connector_name, display_name, ಗಾತ್ರ(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    ಗಣ_XRand_RMode_Info(dpy, res, output_crtc, ಬಹುಲಕ_ID, &ಬಹುಲಕ);
    ಗಣ_XRand_RDisplay_Name(info, display_name, display_name_ಗಾತ್ರ, display_mm_ಅಗಲ, display_mm_ಎತ್ತರ);

    SDL_zero(*display);
    ಆದರೆ (*display_name) {
        display->name = display_name;
    }
    display->desktop_ಬಹುಲಕ = ಬಹುಲಕ;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->ಆಂತರಿಕ = displaydata;

    ಆದರೆ (info) {
        ದಶಮಾಂಶ SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        ಆದರೆ (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (ದಶಮಾಂಶ)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool X11_ಕೂಡಿಸು_XRand_RDisplay(SDL_VideoDevice *_this, Display *dpy, ಪೂರ್ಣಾಂಕ screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    ಅಕ್ಷರ display_name[128];

    ಆದರೆ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, ಗಾತ್ರ(display_name))) {
        ಹಿಂತಿರುಗಿ true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_ಕೂಡಿಸು_Video_Display(&display, false);
    ಆದರೆ (displayID == 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    ಆದರೆ (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    ಹಿಂತಿರುಗಿ true;
}


ಸ್ಥಿರ bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, ಪೂರ್ಣಾಂಕ screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    ಅಕ್ಷರ display_name[128];

    ಆದರೆ (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, ಗಾತ್ರ(display_name))) {
        ಹಿಂತಿರುಗಿ false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_ಗಣ_Desktop_Display_ಬಹುಲಕ(existing_display, &display.desktop_ಬಹುಲಕ);

    // update bounds
    ಆದರೆ (existing_display->ಆಂತರಿಕ->x != display.ಆಂತರಿಕ->x ||
        existing_display->ಆಂತರಿಕ->y != display.ಆಂತರಿಕ->y) {
        existing_display->ಆಂತರಿಕ->x = display.ಆಂತರಿಕ->x;
        existing_display->ಆಂತರಿಕ->y = display.ಆಂತರಿಕ->y;
        SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
    }

    // update scale
    SDL_ಗಣ_Display_Content_Scale(existing_display, display.content_scale);

    // update HDR properties
    SDL_ಗಣ_Display_HDRProperties(existing_display, &display.HDR);

    // SDL_DisplayData is updated piece-meal above, free our local copy of this data
    SDL_free(display.ಆಂತರಿಕ);

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ XRRScreenResources *X11_GetScreenResources(Display *dpy, ಪೂರ್ಣಾಂಕ screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, ಬೇರು_ಕಿಟಕಿ(dpy, screen));
    ಆದರೆ (!res || res->noutput == 0) {
        ಆದರೆ (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, ಬೇರು_ಕಿಟಕಿ(dpy, screen));
    }
    ಹಿಂತಿರುಗಿ res;
}

ಶೂನ್ಯ X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ screencount = Screen_ಎಣಿಕೆ(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(ಖಾಲಿ);
    ಆದರೆ (!displays) {
        ಹಿಂತಿರುಗಿ;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ಆದರೆ (!res) {
            ಮುಂದುವರಿ;
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ಸ್ಥಿರಾಂಕ SDL_Display_ದತ್ತಾಂಶ *displaydata = display->ಆಂತರಿಕ;
            ಆದರೆ (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ screencount = Screen_ಎಣಿಕೆ(dpy);
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&ಅಂಕೆ_displays);
    ಆದರೆ (!displays) {
        ಹಿಂತಿರುಗಿ;
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        ಆದರೆ (!res) {
            ಮುಂದುವರಿ;
        }

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ output = 0; output < res->noutput; output++) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ_displays; ++i) {
                ಆದರೆ (!displays[i]) {
                    // We already removed this display from the list
                    ಮುಂದುವರಿ;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                ಸ್ಥಿರಾಂಕ SDL_Display_ದತ್ತಾಂಶ *displaydata = display->ಆಂತರಿಕ;
                ಆದರೆ (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ_displays; ++i) {
        ಆದರೆ (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ಸ್ಥಿರಾಂಕ SDL_Display_ದತ್ತಾಂಶ *displaydata = display->ಆಂತರಿಕ;
            ಆದರೆ (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_HandleXRandROutputChange(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ i;

#ಆದರೆ 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) ev->output, (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) ev->crtc, (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) ev->ಬಹುಲಕ, (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) ev->rotation, (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) ev->connection);
#ಆದರೆ_ಅಂತ್ಯ

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(ಖಾಲಿ);
    ಆದರೆ (displays) {
        ಗಾಗಿ (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            ಸ್ಥಿರಾಂಕ SDL_Display_ದತ್ತಾಂಶ *displaydata = thisdisplay->ಆಂತರಿಕ;
            ಆದರೆ (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                ನಿಲ್ಲಿಸು;
            }
        }
        SDL_free(displays);
    }

    ಆದರೆ (ev->connection == RR_Disconnected) { // output is going away
        ಆದರೆ (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            ಆದರೆ (_this->ಅಂಕೆ_displays == 1) {
                generic_display = X11_ಕೂಡಿಸು_Generic_Display(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            ಆದರೆ (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ev->connection == RR_Connected) { // output is coming online
        ಆದರೆ (!display) {
            Display *dpy = ev->display;
            ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ಆದರೆ (res) {
                X11_ಕೂಡಿಸು_XRand_RDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

ಶೂನ್ಯ X11_HandleXRandREvent(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ XEvent *xevent)
{
    SDL_Video_ದತ್ತಾಂಶ *videodata = _this->ಆಂತರಿಕ;
    SDL_assert(xevent->type == (videodata->xrandr_event_ತಳ + RRNotify));

    ಆಯ್ಕೆ (((ಸ್ಥಿರಾಂಕ XRRNotifyEvent *)xevent)->subtype) {
    ಸ್ಥಿತಿ RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (ಸ್ಥಿರಾಂಕ XRROutputChangeNotifyEvent *)xevent);
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_ವಿಂಗಡಿಸು_Outputs_By_ಆದ್ಯತೆ_Hint(SDL_VideoDevice *_this)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_ಆದ್ಯತೆ);

    ಆದರೆ (name_hint) {
        ಅಕ್ಷರ *saveptr;
        ಅಕ್ಷರ *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(ಗಾತ್ರ(SDL_VideoDisplay *) * _this->ಅಂಕೆ_displays);

        ಆದರೆ (str && sorted_list) {
            ಪೂರ್ಣಾಂಕ sorted_ಸೂಚ್ಯಂಕ = 0;

            // Sort the requested displays to the front of the list.
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *token = SDL_strtok_r(str, ",", &saveptr);
            ಆಗ (token) {
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    ಆದರೆ (d) {
                        SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = d->ಆಂತರಿಕ;
                        ಆದರೆ (SDL_strcmp(token, ದತ್ತಾಂಶ->connector_name) == 0) {
                            sorted_list[sorted_ಸೂಚ್ಯಂಕ++] = d;
                            _this->displays[i] = ಖಾಲಿ;
                            ನಿಲ್ಲಿಸು;
                        }
                    }
                }

                token = SDL_strtok_r(ಖಾಲಿ, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < _this->ಅಂಕೆ_displays; ++i) {
                ಆದರೆ (_this->displays[i]) {
                    sorted_list[sorted_ಸೂಚ್ಯಂಕ++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, ಗಾತ್ರ(SDL_VideoDisplay *) * _this->ಅಂಕೆ_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

ಸ್ಥಿರ bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    Display *dpy = ದತ್ತಾಂಶ->display;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ screencount = Screen_ಎಣಿಕೆ(dpy);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, ಬೇರು_ಕಿಟಕಿ(dpy, default_screen));
    ಪೂರ್ಣಾಂಕ xrandr_error_ತಳ = 0;
    ಪೂರ್ಣಾಂಕ looking_for_primary;
    ಪೂರ್ಣಾಂಕ output;
    ಪೂರ್ಣಾಂಕ screen;

    ಆದರೆ (!X11_XRRQueryExtension(dpy, &ದತ್ತಾಂಶ->xrandr_event_ತಳ, &xrandr_error_ತಳ)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("XRRQueryExtension failed");
    }

    ಗಾಗಿ (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        ಗಾಗಿ (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            ಆದರೆ (looking_for_primary && (screen != default_screen)) {
                ಮುಂದುವರಿ;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            ಆದರೆ (!res) {
                ಮುಂದುವರಿ;
            }

            ಗಾಗಿ (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                ಆದರೆ ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    ಮುಂದುವರಿ;
                }
                ಆದರೆ (!X11_ಕೂಡಿಸು_XRand_RDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    ನಿಲ್ಲಿಸು;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_ಒಳಹರಿವು(dpy, ಬೇರು_ಕಿಟಕಿ(dpy, screen), RROutput_Change_Notify_ಮುಖವಾಡ);
        }
    }

    ಆದರೆ (_this->ಅಂಕೆ_displays == 0) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("No available displays");
    }

    X11_ವಿಂಗಡಿಸು_Outputs_By_ಆದ್ಯತೆ_Hint(_this);

    ಹಿಂತಿರುಗಿ true;
}
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
ಸ್ಥಿರ bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    ಆದರೆ (X11_ಕೂಡಿಸು_Generic_Display(_this, true) == 0) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
        ಪೂರ್ಣಾಂಕ xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        ಆದರೆ (CheckXRandR(ದತ್ತಾಂಶ->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    ಹಿಂತಿರುಗಿ X11_InitModes_StdXlib(_this);
}

bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
    SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = sdl_display->ಆಂತರಿಕ;
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;

    /* Unfortunately X11 requires the window to be created with the correct
     * visual and depth ahead of time, but the SDL API allows you to create
     * a window before setting the fullscreen display mode.  This means that
     * we have to use the same format for all windows and all display modes.
     * (or support recreating the window with a new visual behind the scenes)
     */
    SDL_zero(ಬಹುಲಕ);
    ಬಹುಲಕ.format = sdl_display->desktop_ಬಹುಲಕ.format;

    ಆದರೆ (ದತ್ತಾಂಶ->use_xrandr) {
        Display *display = _this->ಆಂತರಿಕ->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, ಬೇರು_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->screen));
        ಆದರೆ (res) {
            SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata;
            XRROutputInfo *output_info;
            ಪೂರ್ಣಾಂಕ i;

            output_info = X11_XRRGetOutputInfo(display, res, ದತ್ತಾಂಶ->xrandr_output);
            ಆದರೆ (output_info && output_info->connection != RR_Disconnected) {
                ಗಾಗಿ (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ));
                    ಆದರೆ (!modedata) {
                        ಮುಂದುವರಿ;
                    }
                    ಬಹುಲಕ.ಆಂತರಿಕ = modedata;

                    ಆದರೆ (!ಗಣ_XRand_RMode_Info(display, res, output_info->crtc, output_info->modes[i], &ಬಹುಲಕ) ||
                        !SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(sdl_display, &ಬಹುಲಕ)) {
                        SDL_free(modedata);
                    }
                }
            }
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
        }
    }
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XRANDR
    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ (*Pre_XRRSet_Screen_ಗಾತ್ರ_Error_Handler)(Display *, XErrorEvent *) = ಖಾಲಿ;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ SDL_XRRSet_Screen_ಗಾತ್ರ_Err_Handler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    ಆದರೆ ((e->error_ಸಂಕೇತ == Bad_ಹೊಂದಿಕೆ) || (e->error_ಸಂಕೇತ == Bad_ಮೌಲ್ಯ)) {
        ಹಿಂತಿರುಗಿ 0;
    }

    ಹಿಂತಿರುಗಿ Pre_XRRSet_Screen_ಗಾತ್ರ_Error_Handler(d, e);
}
#ಆದರೆ_ಅಂತ್ಯ

bool X11_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_Video_ದತ್ತಾಂಶ *viddata = _this->ಆಂತರಿಕ;
    SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = sdl_display->ಆಂತರಿಕ;

    viddata->ಕೊನೆಯ_ಬಹುಲಕ_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_ಸಮಯ * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    ಆದರೆ (!viddata->is_xwayland) {
        ಆದರೆ (sdl_display->current_ಬಹುಲಕ != ಬಹುಲಕ) {
            ದತ್ತಾಂಶ->ಬಹುಲಕ_switch_deadline_ns = SDL_GetTicksNS() + ಬಹುಲಕ_SWITCH_TIMEOUT_NS;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ದತ್ತಾಂಶ->ಬಹುಲಕ_switch_deadline_ns = 0;
        }
    }

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XRANDR
    ಆದರೆ (ದತ್ತಾಂಶ->use_xrandr) {
        Display *display = viddata->display;
        SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *modedata = ಬಹುಲಕ->ಆಂತರಿಕ;
        ಪೂರ್ಣಾಂಕ mm_ಅಗಲ, mm_ಎತ್ತರ;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        ಸ್ಥಿತಿ_3 ಸ್ಥಿತಿ_2;

        res = X11_XRRGetScreenResources(display, ಬೇರು_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->screen));
        ಆದರೆ (!res) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, ದತ್ತಾಂಶ->xrandr_output);
        ಆದರೆ (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        ಆದರೆ (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Couldn't get XRandR crtc info");
        }

        ಆದರೆ (crtc->ಬಹುಲಕ == modedata->xrandr_ಬಹುಲಕ) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->ಬಹುಲಕ, crtc->ಅಗಲ, crtc->ಎತ್ತರ);
#ಆದರೆ_ಅಂತ್ಯ
            ಸ್ಥಿತಿ_2 = Success;
            ಹೋಗು freeInfo;
        }

        X11_XGrabServer(display);
        ಸ್ಥಿತಿ_2 = X11_XRRSetCrtcConfig(display, res, output_info->crtc, Current_ಸಮಯ,
                                      0, 0, None, crtc->rotation, ಖಾಲಿ, 0);
        ಆದರೆ (ಸ್ಥಿತಿ_2 != Success) {
            ಹೋಗು ungrabServer;
        }

        mm_ಅಗಲ = ಬಹುಲಕ->w * Display_ಅಗಲ_MM(display, ದತ್ತಾಂಶ->screen) / Display_ಅಗಲ(display, ದತ್ತಾಂಶ->screen);
        mm_ಎತ್ತರ = ಬಹುಲಕ->h * Display_ಎತ್ತರ_MM(display, ದತ್ತಾಂಶ->screen) / Display_ಎತ್ತರ(display, ದತ್ತಾಂಶ->screen);

        /* !!! FIXME: this can get into a problem scenario when a window is
           bigger than a physical monitor in a configuration where one screen
           spans multiple physical monitors. A detailed reproduction case is
           discussed at https://github.com/libsdl-org/SDL/issues/4561 ...
           for now we cheat and just catch the X11 error and carry on, which
           is likely to cause subtle issues but is better than outright
           crashing */
        X11_XSync(display, False);
        Pre_XRRSet_Screen_ಗಾತ್ರ_Error_Handler = X11_XSetErrorHandler(SDL_XRRSet_Screen_ಗಾತ್ರ_Err_Handler);
        X11_XRRSet_Screen_ಗಾತ್ರ(display, ಬೇರು_ಕಿಟಕಿ(display, ದತ್ತಾಂಶ->screen),
                             ಬಹುಲಕ->w, ಬಹುಲಕ->h, mm_ಅಗಲ, mm_ಎತ್ತರ);
        X11_XSync(display, False);
        X11_XSetErrorHandler(Pre_XRRSet_Screen_ಗಾತ್ರ_Error_Handler);

        ಸ್ಥಿತಿ_2 = X11_XRRSetCrtcConfig(display, res, output_info->crtc, Current_ಸಮಯ,
                                      crtc->x, crtc->y, modedata->xrandr_ಬಹುಲಕ, crtc->rotation,
                                      &ದತ್ತಾಂಶ->xrandr_output, 1);

    ungrabServer:
        X11_XUngrabServer(display);
    freeInfo:
        X11_XRRFreeCrtcInfo(crtc);
        X11_XRRFreeOutputInfo(output_info);
        X11_XRRFreeScreenResources(res);

        ಆದರೆ (ಸ್ಥಿತಿ_2 != Success) {
            ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("X11_XRRSetCrtcConfig failed");
        }
    }
#ಇಲ್ಲದಿದ್ದರೆ
    (ಶೂನ್ಯ)ದತ್ತಾಂಶ;
#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XRANDR

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = sdl_display->ಆಂತರಿಕ;

    rect->x = ದತ್ತಾಂಶ->x;
    rect->y = ದತ್ತಾಂಶ->y;
    rect->w = sdl_display->current_ಬಹುಲಕ->w;
    rect->h = sdl_display->current_ಬಹುಲಕ->h;
    ಹಿಂತಿರುಗಿ true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    Display *display = ದತ್ತಾಂಶ->display;
    Atom _NET_WORKAREA;
    ಪೂರ್ಣಾಂಕ real_format;
    Atom real_type;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ವಸ್ತುಗಳು_read = 0, ವಸ್ತುಗಳು_ಎಡ = 0;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *propdata = ಖಾಲಿ;
    bool ಫಲಿತಾಂಶ = false;

    ಆದರೆ (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        ಹಿಂತಿರುಗಿ false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2 = X11_XGet_ಕಿಟಕಿ_Property(display, Default_ಬೇರು_ಕಿಟಕಿ(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &ವಸ್ತುಗಳು_read,
                                    &ವಸ್ತುಗಳು_ಎಡ, &propdata);
    ಆದರೆ ((ಸ್ಥಿತಿ_2 == Success) && (ವಸ್ತುಗಳು_read >= 4)) {
        ಸ್ಥಿರಾಂಕ ದೀರ್ಘ *p = (ದೀರ್ಘ *)propdata;
        ಸ್ಥಿರಾಂಕ SDL_Rect usable = { (ಪೂರ್ಣಾಂಕ)p[0], (ಪೂರ್ಣಾಂಕ)p[1], (ಪೂರ್ಣಾಂಕ)p[2], (ಪೂರ್ಣಾಂಕ)p[3] };
        ಫಲಿತಾಂಶ = true;
        ಆದರೆ (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    ಆದರೆ (propdata) {
        X11_XFree(propdata);
    }

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11
