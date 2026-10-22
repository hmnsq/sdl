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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_X11

#include "SDL_x11video.h"
#include "SDL_x11settings.h"
#include "edid.h"
#include "../../events/SDL_displayevents_c.h"
#include "../SDL_pixels_c.h"

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

float X11_GetGlobalContentScale(Display *display, XSettingsClient *client)
{
    double scale_factor = 0.0;

    // First use the forced scaling factor specified by the app/user
    const char *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_FACTOR);
    якщо (hint && *hint) {
        double value = SDL_atof(hint);
        якщо (value >= 1.0f && value <= 10.0f) {
            scale_factor = value;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    якщо (scale_factor <= 0.0) {
        ціле status, real_format;
        Atom real_type;
        Atom res_mgr;
        unsigned long items_read, items_left;
        char *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        status = X11_XGetWindowProperty(display, RootWindow(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &items_read, &items_left,
                                        (unsigned char **)&resource_manager);

        якщо (status == Success && resource_manager) {
            owns_resource_manager = true;
        } інакше {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        якщо (resource_manager) {
            XrmDatabase db;
            XrmValue value;
            char *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            якщо (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &value)) {
                якщо (value.addr && type && SDL_strcmp(type, "String") == 0) {
                    ціле dpi = SDL_atoi(value.addr);
                    scale_factor  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            якщо (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    якщо (scale_factor <= 0.0) {
        scale_factor = X11_GetXsettingsClientIntKey(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        якщо (scale_factor <= 0.0) {
            ціле dpi = X11_GetXsettingsClientIntKey(client, "Xft/DPI", -1);
            якщо (dpi > 0) {
                scale_factor = (double) dpi / 1024.0;
                scale_factor /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    якщо (scale_factor <= 0.0) {
        const char *scale_str = SDL_getenv("GDK_SCALE");
        якщо (scale_str) {
            scale_factor = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    якщо (scale_factor <= 0.0) {
        scale_factor = 1.0;
    }

    повернути (float)scale_factor;
}

float X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    повернути X11_GetGlobalContentScale(_this->internal->display, _this->internal->xsettings_data.xsettings);
}

static bool get_visualinfo(Display *display, ціле screen, XVisualInfo *vinfo)
{
    const char *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    ціле depth;

    // Look for an exact visual, if requested
    якщо (visual_id && *visual_id) {
        XVisualInfo *vi, template;
        ціле nvis;

        SDL_zero(template);
        template.visualid = SDL_strtol(visual_id, NULL, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &template, &nvis);
        якщо (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            повернути true;
        }
    }

    depth = DefaultDepth(display, screen);
    якщо ((X11_UseDirectColorVisuals() &&
         X11_XMatchVisualInfo(display, screen, depth, DirectColor, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, depth, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, depth, StaticColor, vinfo)) {
        повернути true;
    }
    повернути false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    ціле nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    якщо (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        повернути true;
    }
    повернути false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    якщо (vinfo->class == DirectColor || vinfo->class == TrueColor) {
        ціле bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_mask;
        Gmask = vinfo->visual->green_mask;
        Bmask = vinfo->visual->blue_mask;
        якщо (vinfo->depth == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } інакше {
            Amask = 0;
        }

        bpp = vinfo->depth;
        якщо (bpp == 24) {
            ціле i, n;
            XPixmapFormatValues *p = X11_XListPixmapFormats(display, &n);
            якщо (p) {
                для (i = 0; i < n; ++i) {
                    якщо (p[i].depth == 24) {
                        bpp = p[i].bits_per_pixel;
                        break;
                    }
                }
                X11_XFree(p);
            }
        }

        повернути SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    якщо (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        switch (vinfo->depth) {
        case 8:
            повернути SDL_PIXELFORMAT_INDEX8;
        case 4:
            якщо (BitmapBitOrder(display) == LSBFirst) {
                повернути SDL_PIXELFORMAT_INDEX4LSB;
            } інакше {
                повернути SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        case 1:
            якщо (BitmapBitOrder(display) == LSBFirst) {
                повернути SDL_PIXELFORMAT_INDEX1LSB;
            } інакше {
                повернути SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    повернути SDL_PIXELFORMAT_UNKNOWN;
}

static SDL_DisplayID X11_AddGenericDisplay(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    const ціле default_screen = DefaultScreen(dpy);
    Screen *screen = ScreenOfDisplay(dpy, default_screen);
    ціле scanline_pad, n, i;
    SDL_DisplayModeData *modedata;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    XPixmapFormatValues *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    якщо (!get_visualinfo(dpy, default_screen, &vinfo)) {
        повернути SDL_SetError("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    якщо (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        повернути SDL_SetError("Palettized video modes are no longer supported");
    }

    SDL_zero(mode);
    mode.w = WidthOfScreen(screen);
    mode.h = HeightOfScreen(screen);
    mode.format = pixelformat;

    displaydata = (SDL_DisplayData *)SDL_calloc(1, sizeof(*displaydata));
    якщо (!displaydata) {
        повернути false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, sizeof(SDL_DisplayModeData));
    якщо (!modedata) {
        SDL_free(displaydata);
        повернути false;
    }
    mode.internal = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->depth = vinfo.depth;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    якщо (pixmapformats) {
        для (i = 0; i < n; ++i) {
            якщо (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                break;
            }
        }
        X11_XFree(pixmapformats);
    }

    displaydata->scanline_pad = scanline_pad;
    displaydata->x = 0;
    displaydata->y = 0;
    displaydata->use_xrandr = false;

    SDL_zero(display);
    display.name = (char *)"Generic X11 Display"; /* this is just copied and thrown away, it's safe to cast to char* here. */
    display.desktop_mode = mode;
    display.internal = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    повернути SDL_AddVideoDisplay(&display, send_event);
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR

static void X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(NULL);
    якщо (displays) {
        для (ціле i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            const SDL_DisplayData *displaydata = display->internal;
            якщо (!displaydata->xrandr_output) {
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
        SDL_free(displays);
    }
}

static bool CheckXRandR(Display *display, ціле *major, ціле *minor)
{
    // Default the extension not available
    *major = *minor = 0;

    // Allow environment override
#ifdef XRANDR_DISABLED_BY_DEFAULT
    якщо (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#endif
        повернути false;
    }
#інакше
    якщо (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#endif
        повернути false;
    }
#endif // XRANDR_DISABLED_BY_DEFAULT

    якщо (!SDL_X11_HAVE_XRANDR) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#endif
        повернути false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    якщо (!X11_XRRQueryVersion(display, major, minor)) {
#ifdef X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#endif
        *major = *minor = 0;
        повернути false;
    }
#ifdef X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#endif
    повернути true;
}

#define XRANDR_ROTATION_LEFT  (1 << 1)
#define XRANDR_ROTATION_RIGHT (1 << 3)

static void CalculateXRandRRefreshRate(const XRRModeInfo *info, ціле *numerator, ціле *denominator)
{
    unsigned ціле vTotal = info->vTotal;

    якщо (info->modeFlags & RR_DoubleScan) {
        // doublescan doubles the number of lines
        vTotal *= 2;
    }

    якщо (info->modeFlags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        vTotal /= 2;
    }

    якщо (info->hTotal && vTotal) {
        *numerator = info->dotClock;
        *denominator = (info->hTotal * vTotal);
    } інакше {
        *numerator = 0;
        *denominator = 0;
    }
}

static bool SetXRandRModeInfo(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode modeID, SDL_DisplayMode *mode)
{
    ціле i;
    для (i = 0; i < res->nmode; ++i) {
        const XRRModeInfo *info = &res->modes[i];
        якщо (info->id == modeID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtcTransformAttributes *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            якщо (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            якщо (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            якщо (rotation & (XRANDR_ROTATION_LEFT | XRANDR_ROTATION_RIGHT)) {
                mode->w = (info->height * scale_w + 0xffff) >> 16;
                mode->h = (info->width * scale_h + 0xffff) >> 16;
            } інакше {
                mode->w = (info->width * scale_w + 0xffff) >> 16;
                mode->h = (info->height * scale_h + 0xffff) >> 16;
            }
            CalculateXRandRRefreshRate(info, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);
            mode->internal->xrandr_mode = modeID;
#ifdef X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (ціле)modeID,
                    mode->screen_w, mode->screen_h, mode->refresh_rate_numerator, mode->refresh_rate_denominator);
#endif
            повернути true;
        }
    }
    повернути false;
}

static bool GetRootWindowCardinalProperty(Display *dpy, ціле screen, const char *name, Uint32 *value)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    якщо (atom == None) {
        повернути false;
    }

    ціле real_format;
    Atom real_type;
    unsigned long items_read = 0, items_left = 0;
    unsigned char *propdata = NULL;
    ціле status;
    bool result = false;

    status = X11_XGetWindowProperty(dpy, RootWindow(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &items_read, &items_left, &propdata);
    якщо (status == Success && propdata) {
        якщо (real_type == XA_CARDINAL && items_read > 0) {
            switch (real_format) {
            case 8:
                *value = propdata[0];
                break;
            case 16:
                *value = propdata[0] | (propdata[1] << 8);
                break;
            default:
                *value = propdata[0] | (propdata[1] << 8) | (propdata[2] << 16) | (propdata[3] << 24);
                break;
            }
            result = true;
        }
        X11_XFree(propdata);
    }
    повернути result;
}

static bool GetRootWindowBoolProperty(Display *dpy, ціле screen, const char *name, bool *value)
{
    Uint32 v;
    якщо (GetRootWindowCardinalProperty(dpy, screen, name, &v)) {
        *value = (v != 0);
        повернути true;
    }
    повернути false;
}

static bool GetRootWindowFloatProperty(Display *dpy, ціле screen, const char *name, float *value)
{
    Uint32 v;
    якщо (GetRootWindowCardinalProperty(dpy, screen, name, &v)) {
        SDL_memcpy(value, &v, sizeof(v));
        повернути true;
    }
    повернути false;
}

static bool IsSteamDeckOLEDDisplay(const MonitorInfo *info)
{
    якщо (SDL_strcmp(info->manufacturer_code, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        якщо (info->product_code == 0x3003 || info->product_code == 0x3004) {
            повернути true;
        }
    }
    повернути false;
}

static float GetGamescopeSDRWhiteLevel(Display *dpy, ціле screen, const MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    якщо (!dpy) {
        повернути 0.0f;
    }

    float SDR_white_level = 0.0f;
    bool external_display = false;
    якщо (GetRootWindowBoolProperty(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        GetRootWindowFloatProperty(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } інакше якщо (IsSteamDeckOLEDDisplay(info)) {
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
        SDR_white_level = (float)info->max_luminance / 3.0f;
    } інакше {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    повернути SDR_white_level;
}

static MonitorInfo *GetMonitorInfo(Display *dpy, ціле screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = NULL;
    ціле real_format;
    Atom real_type;
    unsigned long items_read = 0, items_left = 0;
    unsigned char *propdata = NULL;
    ціле status;

    *gamescope = false;

    якщо (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_PATH = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        якщо (GAMESCOPE_DISPLAY_EDID_PATH != None) {
            status = X11_XGetWindowProperty(dpy, RootWindow(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_PATH, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &items_read, &items_left, &propdata);
            якщо (status == Success && propdata) {
                size_t size = 0;
                void *data = SDL_LoadFile((char *)propdata, &size);
                якщо (data) {
                    info = decode_edid((uchar *)data, size);
                    якщо (info) {
                        *gamescope = true;
                    }
                    SDL_free(data);
                }
            }
            якщо (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    якщо (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        якщо (EDID != None) {
            ціле nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            для (ціле i = 0; i < nprop; ++i) {
                якщо (props[i] == EDID) {
                    status = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &items_read, &items_left, &propdata);
                    якщо (status == Success && propdata) {
                        info = decode_edid(propdata, items_read);
                    }
                    якщо (propdata) {
                        X11_XFree(propdata);
                    }
                    break;
                }
            }

            якщо (props) {
                X11_XFree(props);
            }
        }
    }

#ifdef X11MODES_DEBUG
    якщо (info) {
        dump_monitor_info(info);
    }
#endif
    повернути info;
}

static void SetXRandRDisplayName(MonitorInfo *info, char *name, size_t namelen, unsigned long widthmm, unsigned long heightmm)
{
    якщо (info) {
        SDL_strlcpy(name, info->dsc_product_name, namelen);
    }

    ціле inches = (ціле)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    якщо (*name && inches) {
        const size_t len = SDL_strlen(name);
        (void)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#ifdef X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#endif
}

static bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, ціле screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, char *display_name, size_t display_name_size)
{
    XRROutputInfo *output_info;
    ціле display_x, display_y;
    unsigned long display_mm_width, display_mm_height;
    SDL_DisplayData *displaydata;
    SDL_DisplayMode mode;
    SDL_DisplayModeData *modedata;
    RRMode modeID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmapFormatValues *pixmapformats;
    ціле scanline_pad;
    ціле i, n;

    якщо (!display || !display_name) {
        повернути false; // invalid parameters
    }

    якщо (!get_visualinfo(dpy, screen, &vinfo)) {
        повернути false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    якщо (SDL_ISPIXELFORMAT_INDEXED(pixelformat)) {
        повернути false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    якщо (pixmapformats) {
        для (i = 0; i < n; i++) {
            якщо (pixmapformats[i].depth == vinfo.depth) {
                scanline_pad = pixmapformats[i].scanline_pad;
                break;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    якщо (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        повернути false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_size);
    display_mm_width = output_info->mm_width;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    якщо (!crtc) {
        повернути false; // oh well, ignore it.
    }

    SDL_zero(mode);
    modeID = crtc->mode;
    mode.w = crtc->width;
    mode.h = crtc->height;
    mode.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_DisplayData *)SDL_calloc(1, sizeof(*displaydata));
    якщо (!displaydata) {
        повернути false;
    }

    modedata = (SDL_DisplayModeData *)SDL_calloc(1, sizeof(SDL_DisplayModeData));
    якщо (!modedata) {
        SDL_free(displaydata);
        повернути false;
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
    SDL_strlcpy(displaydata->connector_name, display_name, sizeof(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    SetXRandRModeInfo(dpy, res, output_crtc, modeID, &mode);
    SetXRandRDisplayName(info, display_name, display_name_size, display_mm_width, display_mm_height);

    SDL_zero(*display);
    якщо (*display_name) {
        display->name = display_name;
    }
    display->desktop_mode = mode;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->internal = displaydata;

    якщо (info) {
        float SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        якщо (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } інакше {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#ifdef X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#endif
        якщо (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (float)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    повернути true;
}

static bool X11_AddXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, ціле screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    char display_name[128];

    якщо (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, sizeof(display_name))) {
        повернути true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_AddVideoDisplay(&display, false);
    якщо (displayID == 0) {
        повернути false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    якщо (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    повернути true;
}


static bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, ціле screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    char display_name[128];

    якщо (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, sizeof(display_name))) {
        повернути false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_SetDesktopDisplayMode(existing_display, &display.desktop_mode);

    // update bounds
    якщо (existing_display->internal->x != display.internal->x ||
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

    повернути true;
}

static XRRScreenResources *X11_GetScreenResources(Display *dpy, ціле screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, RootWindow(dpy, screen));
    якщо (!res || res->noutput == 0) {
        якщо (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, RootWindow(dpy, screen));
    }
    повернути res;
}

void X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    const ціле screencount = ScreenCount(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(NULL);
    якщо (!displays) {
        повернути;
    }

    для (ціле screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        якщо (!res) {
            continue;
        }

        для (ціле i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            const SDL_DisplayData *displaydata = display->internal;
            якщо (displaydata->xrandr_output && displaydata->screen == screen) {
                X11_UpdateXRandRDisplay(_this, dpy, screen, displaydata->xrandr_output, res, display);
            }
        }
        X11_XRRFreeScreenResources(res);
    }
    SDL_free(displays);
}

static void X11_CheckDisplaysRemoved(SDL_VideoDevice *_this, Display *dpy)
{
    const ціле screencount = ScreenCount(dpy);
    ціле num_displays = 0;

    SDL_DisplayID *displays = SDL_GetDisplays(&num_displays);
    якщо (!displays) {
        повернути;
    }

    для (ціле screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        якщо (!res) {
            continue;
        }

        для (ціле output = 0; output < res->noutput; output++) {
            для (ціле i = 0; i < num_displays; ++i) {
                якщо (!displays[i]) {
                    // We already removed this display from the list
                    continue;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                const SDL_DisplayData *displaydata = display->internal;
                якщо (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    break;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    для (ціле i = 0; i < num_displays; ++i) {
        якщо (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            const SDL_DisplayData *displaydata = display->internal;
            якщо (displaydata->xrandr_output) {
                // This display wasn't in the XRandR list
                SDL_DelVideoDisplay(displays[i], true);
            }
        }
    }
    SDL_free(displays);
}

static void X11_HandleXRandROutputChange(SDL_VideoDevice *_this, const XRROutputChangeNotifyEvent *ev)
{
    SDL_DisplayID *displays;
    SDL_VideoDisplay *display = NULL;
    ціле i;

#якщо 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (unsigned ціле) ev->output, (unsigned ціле) ev->crtc, (unsigned ціле) ev->mode, (unsigned ціле) ev->rotation, (unsigned ціле) ev->connection);
#endif

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(NULL);
    якщо (displays) {
        для (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            const SDL_DisplayData *displaydata = thisdisplay->internal;
            якщо (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                break;
            }
        }
        SDL_free(displays);
    }

    якщо (ev->connection == RR_Disconnected) { // output is going away
        якщо (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            якщо (_this->num_displays == 1) {
                generic_display = X11_AddGenericDisplay(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            якщо (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } інакше якщо (ev->connection == RR_Connected) { // output is coming online
        якщо (!display) {
            Display *dpy = ev->display;
            const ціле screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            якщо (res) {
                X11_AddXRandRDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

void X11_HandleXRandREvent(SDL_VideoDevice *_this, const XEvent *xevent)
{
    SDL_VideoData *videodata = _this->internal;
    SDL_assert(xevent->type == (videodata->xrandr_event_base + RRNotify));

    switch (((const XRRNotifyEvent *)xevent)->subtype) {
    case RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (const XRROutputChangeNotifyEvent *)xevent);
        break;
    default:
        break;
    }
}

static void X11_SortOutputsByPriorityHint(SDL_VideoDevice *_this)
{
    const char *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY);

    якщо (name_hint) {
        char *saveptr;
        char *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(sizeof(SDL_VideoDisplay *) * _this->num_displays);

        якщо (str && sorted_list) {
            ціле sorted_index = 0;

            // Sort the requested displays to the front of the list.
            const char *token = SDL_strtok_r(str, ",", &saveptr);
            поки (token) {
                для (ціле i = 0; i < _this->num_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    якщо (d) {
                        SDL_DisplayData *data = d->internal;
                        якщо (SDL_strcmp(token, data->connector_name) == 0) {
                            sorted_list[sorted_index++] = d;
                            _this->displays[i] = NULL;
                            break;
                        }
                    }
                }

                token = SDL_strtok_r(NULL, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            для (ціле i = 0; i < _this->num_displays; ++i) {
                якщо (_this->displays[i]) {
                    sorted_list[sorted_index++] = _this->displays[i];
                }
            }

            // Copy the sorted list back to the display list.
            SDL_memcpy(_this->displays, sorted_list, sizeof(SDL_VideoDisplay *) * _this->num_displays);
        }

        SDL_free(str);
        SDL_free(sorted_list);
    }
}

static bool X11_InitModes_XRandR(SDL_VideoDevice *_this)
{
    SDL_VideoData *data = _this->internal;
    Display *dpy = data->display;
    const ціле screencount = ScreenCount(dpy);
    const ціле default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, RootWindow(dpy, default_screen));
    ціле xrandr_error_base = 0;
    ціле looking_for_primary;
    ціле output;
    ціле screen;

    якщо (!X11_XRRQueryExtension(dpy, &data->xrandr_event_base, &xrandr_error_base)) {
        повернути SDL_SetError("XRRQueryExtension failed");
    }

    для (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        для (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            якщо (looking_for_primary && (screen != default_screen)) {
                continue;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            якщо (!res) {
                continue;
            }

            для (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                якщо ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    continue;
                }
                якщо (!X11_AddXRandRDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    break;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelectInput(dpy, RootWindow(dpy, screen), RROutputChangeNotifyMask);
        }
    }

    якщо (_this->num_displays == 0) {
        повернути SDL_SetError("No available displays");
    }

    X11_SortOutputsByPriorityHint(_this);

    повернути true;
}
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
static bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    якщо (X11_AddGenericDisplay(_this, true) == 0) {
        повернути false;
    }
    повернути true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_VideoData *data = _this->internal;
        ціле xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        якщо (CheckXRandR(data->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            повернути true;
        }
    }
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    повернути X11_InitModes_StdXlib(_this);
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

    якщо (data->use_xrandr) {
        Display *display = _this->internal->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, RootWindow(display, data->screen));
        якщо (res) {
            SDL_DisplayModeData *modedata;
            XRROutputInfo *output_info;
            ціле i;

            output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
            якщо (output_info && output_info->connection != RR_Disconnected) {
                для (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_DisplayModeData *)SDL_calloc(1, sizeof(SDL_DisplayModeData));
                    якщо (!modedata) {
                        continue;
                    }
                    mode.internal = modedata;

                    якщо (!SetXRandRModeInfo(display, res, output_info->crtc, output_info->modes[i], &mode) ||
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
    повернути true;
}

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
static ціле (*PreXRRSetScreenSizeErrorHandler)(Display *, XErrorEvent *) = NULL;
static ціле SDL_XRRSetScreenSizeErrHandler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    якщо ((e->error_code == BadMatch) || (e->error_code == BadValue)) {
        повернути 0;
    }

    повернути PreXRRSetScreenSizeErrorHandler(d, e);
}
#endif

bool X11_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode)
{
    SDL_VideoData *viddata = _this->internal;
    SDL_DisplayData *data = sdl_display->internal;

    viddata->last_mode_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    якщо (!viddata->is_xwayland) {
        якщо (sdl_display->current_mode != mode) {
            data->mode_switch_deadline_ns = SDL_GetTicksNS() + MODE_SWITCH_TIMEOUT_NS;
        } інакше {
            data->mode_switch_deadline_ns = 0;
        }
    }

#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
    якщо (data->use_xrandr) {
        Display *display = viddata->display;
        SDL_DisplayModeData *modedata = mode->internal;
        ціле mm_width, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        Status status;

        res = X11_XRRGetScreenResources(display, RootWindow(display, data->screen));
        якщо (!res) {
            повернути SDL_SetError("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, data->xrandr_output);
        якщо (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            повернути SDL_SetError("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        якщо (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            повернути SDL_SetError("Couldn't get XRandR crtc info");
        }

        якщо (crtc->mode == modedata->xrandr_mode) {
#ifdef X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->mode, crtc->width, crtc->height);
#endif
            status = Success;
            goto freeInfo;
        }

        X11_XGrabServer(display);
        status = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, NULL, 0);
        якщо (status != Success) {
            goto ungrabServer;
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
        X11_XRRSetScreenSize(display, RootWindow(display, data->screen),
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

        якщо (status != Success) {
            повернути SDL_SetError("X11_XRRSetCrtcConfig failed");
        }
    }
#інакше
    (void)data;
#endif // SDL_VIDEO_DRIVER_X11_XRANDR

    повернути true;
}

void X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_DisplayData *data = sdl_display->internal;

    rect->x = data->x;
    rect->y = data->y;
    rect->w = sdl_display->current_mode->w;
    rect->h = sdl_display->current_mode->h;
    повернути true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_VideoData *data = _this->internal;
    Display *display = data->display;
    Atom _NET_WORKAREA;
    ціле real_format;
    Atom real_type;
    unsigned long items_read = 0, items_left = 0;
    unsigned char *propdata = NULL;
    bool result = false;

    якщо (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        повернути false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    ціле status = X11_XGetWindowProperty(display, DefaultRootWindow(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &items_read,
                                    &items_left, &propdata);
    якщо ((status == Success) && (items_read >= 4)) {
        const long *p = (long *)propdata;
        const SDL_Rect usable = { (ціле)p[0], (ціле)p[1], (ціле)p[2], (ціле)p[3] };
        result = true;
        якщо (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    якщо (propdata) {
        X11_XFree(propdata);
    }

    повернути result;
}

#endif // SDL_VIDEO_DRIVER_X11
