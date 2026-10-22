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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11

#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11settings.h"
#अन्तर्भाव "edid.h"
#अन्तर्भाव "../../events/SDL_displayevents_c.h"
#अन्तर्भाव "../SDL_pixels_c.h"

// #define X11MODES_DEBUG

/* Timeout and revert mode switches if the timespan has elapsed without the window becoming fullscreen.
 * 5 seconds seems good from testing.
 */
#परिभाषय बहुलकम्_SWITCH_TIMEOUT_NS SDL_NS_प्रत्येकम्_SECOND * 5

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
    द्विगुण scale_गुणकः_2 = 0.0;

    // First use the forced scaling factor specified by the app/user
    ध्रुव वर्ण *hint = SDL_GetHint(SDL_HINT_VIDEO_X11_SCALING_गुणकः);
    यदि (hint && *hint) {
        द्विगुण मानम् = SDL_atof(hint);
        यदि (मानम् >= 1.0f && मानम् <= 10.0f) {
            scale_गुणकः_2 = मानम्;
        }
    }

    // If that failed, try "Xft.dpi" from the XResourcesDatabase...
    // We attempt to read this directly to get the live value, XResourceManagerString
    // is cached per display connection.
    यदि (scale_गुणकः_2 <= 0.0) {
        पूर्णाङ्क स्थितिः, real_format;
        Atom real_type;
        Atom res_mgr;
        अचिह्नित दीर्घ वस्तूनि_read, वस्तूनि_वामः;
        वर्ण *resource_manager;
        bool owns_resource_manager = false;

        X11_XrmInitialize();
        res_mgr = X11_XInternAtom(display, "RESOURCE_MANAGER", False);
        स्थितिः = X11_XGet_गवाक्षः_Property(display, मूलम्_गवाक्षः(display, DefaultScreen(display)),
                                        res_mgr, 0L, 8192L, False, XA_STRING,
                                        &real_type, &real_format, &वस्तूनि_read, &वस्तूनि_वामः,
                                        (अचिह्नित वर्ण **)&resource_manager);

        यदि (स्थितिः == Success && resource_manager) {
            owns_resource_manager = true;
        } अन्यथा {
            // Fall back to XResourceManagerString. This will not be updated if the
            // dpi value is later changed but should allow getting the initial value.
            resource_manager = X11_XResourceManagerString(display);
        }

        यदि (resource_manager) {
            XrmDatabase db;
            Xrm_मानम् मानम्;
            वर्ण *type;

            db = X11_XrmGetStringDatabase(resource_manager);

            // Get the value of Xft.dpi from the Database
            यदि (X11_XrmGetResource(db, "Xft.dpi", "String", &type, &मानम्)) {
                यदि (मानम्.addr && type && SDL_strcmp(type, "String") == 0) {
                    पूर्णाङ्क dpi = SDL_atoi(मानम्.addr);
                    scale_गुणकः_2  = dpi / 96.0;
                }
            }
            X11_XrmDestroyDatabase(db);

            यदि (owns_resource_manager) {
                X11_XFree(resource_manager);
            }
        }
    }

    // If that failed, try the XSETTINGS keys...
    यदि (scale_गुणकः_2 <= 0.0) {
        scale_गुणकः_2 = X11_Get_Xsettings_Client_Int_कुञ्चिका(client, "Gdk/WindowScalingFactor", -1);

        // The Xft/DPI key is stored in increments of 1024th
        यदि (scale_गुणकः_2 <= 0.0) {
            पूर्णाङ्क dpi = X11_Get_Xsettings_Client_Int_कुञ्चिका(client, "Xft/DPI", -1);
            यदि (dpi > 0) {
                scale_गुणकः_2 = (द्विगुण) dpi / 1024.0;
                scale_गुणकः_2 /= 96.0;
            }
        }
    }

    // If that failed, try the GDK_SCALE envvar...
    यदि (scale_गुणकः_2 <= 0.0) {
        ध्रुव वर्ण *scale_str = SDL_getenv("GDK_SCALE");
        यदि (scale_str) {
            scale_गुणकः_2 = SDL_atoi(scale_str);
        }
    }

    // Nothing or a bad value, just fall back to 1.0
    यदि (scale_गुणकः_2 <= 0.0) {
        scale_गुणकः_2 = 1.0;
    }

    प्रत्यागम (भिन्न)scale_गुणकः_2;
}

भिन्न X11_GetGlobalContentScaleForDevice(SDL_VideoDevice *_this)
{
    प्रत्यागम X11_GetGlobalContentScale(_this->आन्तरिकम्->display, _this->आन्तरिकम्->xsettings_दत्त.xsettings);
}

स्थिर bool get_visualinfo(Display *display, पूर्णाङ्क screen, XVisualInfo *vinfo)
{
    ध्रुव वर्ण *visual_id = SDL_GetHint(SDL_HINT_VIDEO_X11_VISUALID);
    पूर्णाङ्क गभीरता_2;

    // Look for an exact visual, if requested
    यदि (visual_id && *visual_id) {
        XVisualInfo *vi, प्रतिरूपम्;
        पूर्णाङ्क nvis;

        SDL_zero(प्रतिरूपम्);
        प्रतिरूपम्.visualid = SDL_strtol(visual_id, रिक्त, 0);
        vi = X11_XGetVisualInfo(display, VisualIDMask, &प्रतिरूपम्, &nvis);
        यदि (vi) {
            *vinfo = *vi;
            X11_XFree(vi);
            प्रत्यागम true;
        }
    }

    गभीरता_2 = Default_गभीरता(display, screen);
    यदि ((X11_Use_प्रत्यक्षम्_Color_Visuals() &&
         X11_XMatchVisualInfo(display, screen, गभीरता_2, प्रत्यक्षम्_Color, vinfo)) ||
        X11_XMatchVisualInfo(display, screen, गभीरता_2, TrueColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, गभीरता_2, PseudoColor, vinfo) ||
        X11_XMatchVisualInfo(display, screen, गभीरता_2, StaticColor, vinfo)) {
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

bool X11_GetVisualInfoFromVisual(Display *display, Visual *visual, XVisualInfo *vinfo)
{
    XVisualInfo *vi;
    पूर्णाङ्क nvis;

    vinfo->visualid = X11_XVisualIDFromVisual(visual);
    vi = X11_XGetVisualInfo(display, VisualIDMask, vinfo, &nvis);
    यदि (vi) {
        *vinfo = *vi;
        X11_XFree(vi);
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

SDL_PixelFormat X11_GetPixelFormatFromVisualInfo(Display *display, XVisualInfo *vinfo)
{
    यदि (vinfo->class == प्रत्यक्षम्_Color || vinfo->class == TrueColor) {
        पूर्णाङ्क bpp;
        Uint32 Rmask, Gmask, Bmask, Amask;

        Rmask = vinfo->visual->red_आवरणम्;
        Gmask = vinfo->visual->green_आवरणम्;
        Bmask = vinfo->visual->blue_आवरणम्;
        यदि (vinfo->गभीरता_2 == 32) {
            Amask = (0xFFFFFFFF & ~(Rmask | Gmask | Bmask));
        } अन्यथा {
            Amask = 0;
        }

        bpp = vinfo->गभीरता_2;
        यदि (bpp == 24) {
            पूर्णाङ्क i, n;
            XPixmap_Format_मानानि *p = X11_XListPixmapFormats(display, &n);
            यदि (p) {
                प्रति (i = 0; i < n; ++i) {
                    यदि (p[i].गभीरता_2 == 24) {
                        bpp = p[i].द्वयङ्काः_प्रत्येकम्_pixel;
                        भङ्ग;
                    }
                }
                X11_XFree(p);
            }
        }

        प्रत्यागम SDL_GetPixelFormatForMasks(bpp, Rmask, Gmask, Bmask, Amask);
    }

    यदि (vinfo->class == PseudoColor || vinfo->class == StaticColor) {
        विकल्प (vinfo->गभीरता_2) {
        पक्ष 8:
            प्रत्यागम SDL_PIXELFORMAT_INDEX8;
        पक्ष 4:
            यदि (Bitmap_Bit_क्रमः(display) == LSBFirst) {
                प्रत्यागम SDL_PIXELFORMAT_INDEX4LSB;
            } अन्यथा {
                प्रत्यागम SDL_PIXELFORMAT_INDEX4MSB;
            }
            // break; -Wunreachable-code-break
        पक्ष 1:
            यदि (Bitmap_Bit_क्रमः(display) == LSBFirst) {
                प्रत्यागम SDL_PIXELFORMAT_INDEX1LSB;
            } अन्यथा {
                प्रत्यागम SDL_PIXELFORMAT_INDEX1MSB;
            }
            // break; -Wunreachable-code-break
        }
    }

    प्रत्यागम SDL_PIXELFORMAT_UNKNOWN;
}

स्थिर SDL_DisplayID X11_सङ्कलय_Generic_Display(SDL_VideoDevice *_this, bool send_event)
{
    // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function.
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    Display *dpy = दत्त->display;
    ध्रुव पूर्णाङ्क default_screen = DefaultScreen(dpy);
    Screen *screen = Screen_सम्बन्धि_Display(dpy, default_screen);
    पूर्णाङ्क scanline_pad, n, i;
    SDL_Display_बहुलकम्_दत्त *modedata;
    SDL_Display_दत्त *displaydata;
    SDL_Display_बहुलकम् बहुलकम्;
    XPixmap_Format_मानानि *pixmapformats;
    Uint32 pixelformat;
    XVisualInfo vinfo;
    SDL_VideoDisplay display;

    // note that generally even if you have a multiple physical monitors, ScreenCount(dpy) still only reports ONE screen.

    यदि (!get_visualinfo(dpy, default_screen, &vinfo)) {
        प्रत्यागम SDL_समुच्चयः_Error("Failed to find an X11 visual for the primary display");
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    यदि (SDL_ISPIXELFORMAT_अनुक्रमितम्(pixelformat)) {
        प्रत्यागम SDL_समुच्चयः_Error("Palettized video modes are no longer supported");
    }

    SDL_zero(बहुलकम्);
    बहुलकम्.w = विस्तारः_सम्बन्धि_Screen(screen);
    बहुलकम्.h = Height_सम्बन्धि_Screen(screen);
    बहुलकम्.format = pixelformat;

    displaydata = (SDL_Display_दत्त *)SDL_calloc(1, परिमाण(*displaydata));
    यदि (!displaydata) {
        प्रत्यागम false;
    }

    modedata = (SDL_Display_बहुलकम्_दत्त *)SDL_calloc(1, परिमाण(SDL_Display_बहुलकम्_दत्त));
    यदि (!modedata) {
        SDL_free(displaydata);
        प्रत्यागम false;
    }
    बहुलकम्.आन्तरिकम् = modedata;

    displaydata->screen = default_screen;
    displaydata->visual = vinfo.visual;
    displaydata->गभीरता_2 = vinfo.गभीरता_2;

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    यदि (pixmapformats) {
        प्रति (i = 0; i < n; ++i) {
            यदि (pixmapformats[i].गभीरता_2 == vinfo.गभीरता_2) {
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
    display.desktop_बहुलकम् = बहुलकम्;
    display.आन्तरिकम् = displaydata;
    display.content_scale = X11_GetGlobalContentScaleForDevice(_this);
    प्रत्यागम SDL_सङ्कलय_Video_Display(&display, send_event);
}

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR

स्थिर शून्य X11_RemoveGenericDisplay(SDL_VideoDevice *_this)
{
    SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
    यदि (displays) {
        प्रति (पूर्णाङ्क i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ध्रुव SDL_Display_दत्त *displaydata = display->आन्तरिकम्;
            यदि (!displaydata->xrandr_output) {
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
#यदि_परिभाषितम् XRANDR_DISABLED_BY_DEFAULT
    यदि (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, false)) {
#यदि_परिभाषितम् X11MODES_DEBUG
        SDL_Log("XRandR disabled by default due to window manager issues\n");
#यदि_अन्तः
        प्रत्यागम false;
    }
#अन्यथा
    यदि (!SDL_GetHintBoolean(SDL_HINT_VIDEO_X11_XRANDR, true)) {
#यदि_परिभाषितम् X11MODES_DEBUG
        SDL_Log("XRandR disabled due to hint\n");
#यदि_अन्तः
        प्रत्यागम false;
    }
#यदि_अन्तः // XRANDR_DISABLED_BY_DEFAULT

    यदि (!SDL_X11_HAVE_XRANDR) {
#यदि_परिभाषितम् X11MODES_DEBUG
        SDL_Log("XRandR support not available\n");
#यदि_अन्तः
        प्रत्यागम false;
    }

    // Query the extension version
    *major = 1;
    *minor = 3; // we want 1.3
    यदि (!X11_XRRQuery_संस्करणम्(display, major, minor)) {
#यदि_परिभाषितम् X11MODES_DEBUG
        SDL_Log("XRandR not active on the display\n");
#यदि_अन्तः
        *major = *minor = 0;
        प्रत्यागम false;
    }
#यदि_परिभाषितम् X11MODES_DEBUG
    SDL_Log("XRandR available at version %d.%d!\n", *major, *minor);
#यदि_अन्तः
    प्रत्यागम true;
}

#परिभाषय XRANDR_ROTATION_वामः  (1 << 1)
#परिभाषय XRANDR_ROTATION_दक्षिणः (1 << 3)

स्थिर शून्य Calculate_XRand_RRefresh_दरः(ध्रुव XRRModeInfo *info, पूर्णाङ्क *numerator, पूर्णाङ्क *denominator)
{
    अचिह्नित पूर्णाङ्क v_योग_2 = info->v_योग_2;

    यदि (info->बहुलकम्_Flags & RR_Double_अवलोकनम्) {
        // doublescan doubles the number of lines
        v_योग_2 *= 2;
    }

    यदि (info->बहुलकम्_Flags & RR_Interlace) {
        // interlace splits the frame into two fields
        // the field rate is what is typically reported by monitors
        v_योग_2 /= 2;
    }

    यदि (info->h_योग_2 && v_योग_2) {
        *numerator = info->dotClock;
        *denominator = (info->h_योग_2 * v_योग_2);
    } अन्यथा {
        *numerator = 0;
        *denominator = 0;
    }
}

स्थिर bool समुच्चयः_XRand_RMode_Info(Display *display, XRRScreenResources *res, RRCrtc crtc,
                                  RRMode बहुलकम्_ID, SDL_Display_बहुलकम् *बहुलकम्)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < res->nmode; ++i) {
        ध्रुव XRRModeInfo *info = &res->modes[i];
        यदि (info->id == बहुलकम्_ID) {
            XRRCrtcInfo *crtcinfo;
            Rotation rotation = 0;
            XFixed scale_w = 0x10000, scale_h = 0x10000;
            XRRCrtc_Transform_गुणाः *attr;

            crtcinfo = X11_XRRGetCrtcInfo(display, res, crtc);
            यदि (crtcinfo) {
                rotation = crtcinfo->rotation;
                X11_XRRFreeCrtcInfo(crtcinfo);
            }
            यदि (X11_XRRGetCrtcTransform(display, crtc, &attr) && attr) {
                scale_w = attr->currentTransform.matrix[0][0];
                scale_h = attr->currentTransform.matrix[1][1];
                X11_XFree(attr);
            }

            यदि (rotation & (XRANDR_ROTATION_वामः | XRANDR_ROTATION_दक्षिणः)) {
                बहुलकम्->w = (info->height * scale_w + 0xffff) >> 16;
                बहुलकम्->h = (info->विस्तारः * scale_h + 0xffff) >> 16;
            } अन्यथा {
                बहुलकम्->w = (info->विस्तारः * scale_w + 0xffff) >> 16;
                बहुलकम्->h = (info->height * scale_h + 0xffff) >> 16;
            }
            Calculate_XRand_RRefresh_दरः(info, &बहुलकम्->refresh_दरः_numerator, &बहुलकम्->refresh_दरः_denominator);
            बहुलकम्->आन्तरिकम्->xrandr_बहुलकम् = बहुलकम्_ID;
#यदि_परिभाषितम् X11MODES_DEBUG
            SDL_Log("XRandR mode %d: %dx%d@%d/%dHz\n", (पूर्णाङ्क)बहुलकम्_ID,
                    बहुलकम्->screen_w, बहुलकम्->screen_h, बहुलकम्->refresh_दरः_numerator, बहुलकम्->refresh_दरः_denominator);
#यदि_अन्तः
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

स्थिर bool Get_मूलम्_गवाक्षः_Cardinal_Property(Display *dpy, पूर्णाङ्क screen, ध्रुव वर्ण *name, Uint32 *मानम्)
{
    Atom atom = X11_XInternAtom(dpy, name, False);
    यदि (atom == None) {
        प्रत्यागम false;
    }

    पूर्णाङ्क real_format;
    Atom real_type;
    अचिह्नित दीर्घ वस्तूनि_read = 0, वस्तूनि_वामः = 0;
    अचिह्नित वर्ण *propdata = रिक्त;
    पूर्णाङ्क स्थितिः;
    bool परिणाम = false;

    स्थितिः = X11_XGet_गवाक्षः_Property(dpy, मूलम्_गवाक्षः(dpy, screen),
                                    atom, 0L, 1024L, False, AnyPropertyType,
                                    &real_type, &real_format, &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
    यदि (स्थितिः == Success && propdata) {
        यदि (real_type == XA_CARDINAL && वस्तूनि_read > 0) {
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
            परिणाम = true;
        }
        X11_XFree(propdata);
    }
    प्रत्यागम परिणाम;
}

स्थिर bool Get_मूलम्_गवाक्षः_Bool_Property(Display *dpy, पूर्णाङ्क screen, ध्रुव वर्ण *name, bool *मानम्)
{
    Uint32 v;
    यदि (Get_मूलम्_गवाक्षः_Cardinal_Property(dpy, screen, name, &v)) {
        *मानम् = (v != 0);
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

स्थिर bool Get_मूलम्_गवाक्षः_Float_Property(Display *dpy, पूर्णाङ्क screen, ध्रुव वर्ण *name, भिन्न *मानम्)
{
    Uint32 v;
    यदि (Get_मूलम्_गवाक्षः_Cardinal_Property(dpy, screen, name, &v)) {
        SDL_memcpy(मानम्, &v, परिमाण(v));
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

स्थिर bool IsSteamDeckOLEDDisplay(ध्रुव MonitorInfo *info)
{
    यदि (SDL_strcmp(info->manufacturer_संहिता, "VLV") == 0) {
        // These are the Samsung and BOE panels used in the Steam Deck OLED
        यदि (info->गुणनफलम्_संहिता == 0x3003 || info->गुणनफलम्_संहिता == 0x3004) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

स्थिर भिन्न GetGamescopeSDRWhiteLevel(Display *dpy, पूर्णाङ्क screen, ध्रुव MonitorInfo *info)
{
    // These properties are currently only available on X display :0
    // If this changes, please remove the XCloseDisplay() call below.
    dpy = X11_XOpenDisplay(":0");
    screen = 0;
    यदि (!dpy) {
        प्रत्यागम 0.0f;
    }

    भिन्न SDR_white_level = 0.0f;
    bool external_display = false;
    यदि (Get_मूलम्_गवाक्षः_Bool_Property(dpy, screen, "GAMESCOPE_DISPLAY_IS_EXTERNAL", &external_display) &&
        external_display) {
        // Gamescope outputs PQ to external displays, with SDR content at this brightness
        Get_मूलम्_गवाक्षः_Float_Property(dpy, screen, "GAMESCOPE_SDR_ON_HDR_CONTENT_BRIGHTNESS", &SDR_white_level);
    } अन्यथा यदि (IsSteamDeckOLEDDisplay(info)) {
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
    } अन्यथा {
        // We don't know the SDR white level for other internal displays
        SDR_white_level = 0.0f;
    }

    // Closing the display opened above
    X11_XCloseDisplay(dpy);

    प्रत्यागम SDR_white_level;
}

स्थिर MonitorInfo *GetMonitorInfo(Display *dpy, पूर्णाङ्क screen, RROutput output, bool *gamescope)
{
    MonitorInfo *info = रिक्त;
    पूर्णाङ्क real_format;
    Atom real_type;
    अचिह्नित दीर्घ वस्तूनि_read = 0, वस्तूनि_वामः = 0;
    अचिह्नित वर्ण *propdata = रिक्त;
    पूर्णाङ्क स्थितिः;

    *gamescope = false;

    यदि (!info) {
        Atom GAMESCOPE_DISPLAY_EDID_मार्गः = X11_XInternAtom(dpy, "GAMESCOPE_DISPLAY_EDID_PATH", False);
        यदि (GAMESCOPE_DISPLAY_EDID_मार्गः != None) {
            स्थितिः = X11_XGet_गवाक्षः_Property(dpy, मूलम्_गवाक्षः(dpy, screen),
                                            GAMESCOPE_DISPLAY_EDID_मार्गः, 0L, 1024L, False, AnyPropertyType,
                                            &real_type, &real_format, &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
            यदि (स्थितिः == Success && propdata) {
                size_t आकार = 0;
                शून्य *दत्त = SDL_आरोपय_File((वर्ण *)propdata, &आकार);
                यदि (दत्त) {
                    info = decode_edid((uchar *)दत्त, आकार);
                    यदि (info) {
                        *gamescope = true;
                    }
                    SDL_free(दत्त);
                }
            }
            यदि (propdata) {
                X11_XFree(propdata);
            }
        }
    }

    यदि (!info) {
        Atom EDID = X11_XInternAtom(dpy, "EDID", False);
        यदि (EDID != None) {
            पूर्णाङ्क nprop = 0;
            Atom *props = X11_XRRListOutputProperties(dpy, output, &nprop);
            प्रति (पूर्णाङ्क i = 0; i < nprop; ++i) {
                यदि (props[i] == EDID) {
                    स्थितिः = X11_XRRGetOutputProperty(dpy, output, props[i], 0L, 128L, False,
                                                       False, AnyPropertyType, &real_type,
                                                       &real_format, &वस्तूनि_read, &वस्तूनि_वामः, &propdata);
                    यदि (स्थितिः == Success && propdata) {
                        info = decode_edid(propdata, वस्तूनि_read);
                    }
                    यदि (propdata) {
                        X11_XFree(propdata);
                    }
                    भङ्ग;
                }
            }

            यदि (props) {
                X11_XFree(props);
            }
        }
    }

#यदि_परिभाषितम् X11MODES_DEBUG
    यदि (info) {
        dump_monitor_info(info);
    }
#यदि_अन्तः
    प्रत्यागम info;
}

स्थिर शून्य समुच्चयः_XRand_RDisplay_Name(MonitorInfo *info, वर्ण *name, size_t namelen, अचिह्नित दीर्घ widthmm, अचिह्नित दीर्घ heightmm)
{
    यदि (info) {
        SDL_strlcpy(name, info->dsc_गुणनफलम्_name, namelen);
    }

    पूर्णाङ्क inches = (पूर्णाङ्क)((SDL_sqrtf(widthmm * widthmm + heightmm * heightmm) / 25.4f) + 0.5f);
    यदि (*name && inches) {
        ध्रुव size_t len = SDL_strlen(name);
        (शून्य)SDL_snprintf(&name[len], namelen - len, " %d\"", inches);
    }

#यदि_परिभाषितम् X11MODES_DEBUG
    SDL_Log("Display name: %s\n", name);
#यदि_अन्तः
}

स्थिर bool X11_FillXRandRDisplayInfo(SDL_VideoDevice *_this, Display *dpy, पूर्णाङ्क screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *display, वर्ण *display_name, size_t display_name_आकार)
{
    XRROutputInfo *output_info;
    पूर्णाङ्क display_x, display_y;
    अचिह्नित दीर्घ display_mm_विस्तारः, display_mm_height;
    SDL_Display_दत्त *displaydata;
    SDL_Display_बहुलकम् बहुलकम्;
    SDL_Display_बहुलकम्_दत्त *modedata;
    RRMode बहुलकम्_ID;
    RRCrtc output_crtc;
    XRRCrtcInfo *crtc;
    XVisualInfo vinfo;
    Uint32 pixelformat;
    XPixmap_Format_मानानि *pixmapformats;
    पूर्णाङ्क scanline_pad;
    पूर्णाङ्क i, n;

    यदि (!display || !display_name) {
        प्रत्यागम false; // invalid parameters
    }

    यदि (!get_visualinfo(dpy, screen, &vinfo)) {
        प्रत्यागम false; // uh, skip this screen?
    }

    pixelformat = X11_GetPixelFormatFromVisualInfo(dpy, &vinfo);
    यदि (SDL_ISPIXELFORMAT_अनुक्रमितम्(pixelformat)) {
        प्रत्यागम false; // Palettized video modes are no longer supported, ignore this one.
    }

    scanline_pad = SDL_BYTESPERPIXEL(pixelformat) * 8;
    pixmapformats = X11_XListPixmapFormats(dpy, &n);
    यदि (pixmapformats) {
        प्रति (i = 0; i < n; i++) {
            यदि (pixmapformats[i].गभीरता_2 == vinfo.गभीरता_2) {
                scanline_pad = pixmapformats[i].scanline_pad;
                भङ्ग;
            }
        }
        X11_XFree(pixmapformats);
    }

    output_info = X11_XRRGetOutputInfo(dpy, res, outputid);
    यदि (!output_info || !output_info->crtc || output_info->connection == RR_Disconnected) {
        X11_XRRFreeOutputInfo(output_info);
        प्रत्यागम false; // ignore this one.
    }

    SDL_strlcpy(display_name, output_info->name, display_name_आकार);
    display_mm_विस्तारः = output_info->mm_विस्तारः;
    display_mm_height = output_info->mm_height;
    output_crtc = output_info->crtc;
    X11_XRRFreeOutputInfo(output_info);

    crtc = X11_XRRGetCrtcInfo(dpy, res, output_crtc);
    यदि (!crtc) {
        प्रत्यागम false; // oh well, ignore it.
    }

    SDL_zero(बहुलकम्);
    बहुलकम्_ID = crtc->बहुलकम्;
    बहुलकम्.w = crtc->विस्तारः;
    बहुलकम्.h = crtc->height;
    बहुलकम्.format = pixelformat;

    display_x = crtc->x;
    display_y = crtc->y;

    X11_XRRFreeCrtcInfo(crtc);

    displaydata = (SDL_Display_दत्त *)SDL_calloc(1, परिमाण(*displaydata));
    यदि (!displaydata) {
        प्रत्यागम false;
    }

    modedata = (SDL_Display_बहुलकम्_दत्त *)SDL_calloc(1, परिमाण(SDL_Display_बहुलकम्_दत्त));
    यदि (!modedata) {
        SDL_free(displaydata);
        प्रत्यागम false;
    }

    modedata->xrandr_बहुलकम् = बहुलकम्_ID;
    बहुलकम्.आन्तरिकम् = modedata;

    displaydata->screen = screen;
    displaydata->visual = vinfo.visual;
    displaydata->गभीरता_2 = vinfo.गभीरता_2;
    displaydata->scanline_pad = scanline_pad;
    displaydata->x = display_x;
    displaydata->y = display_y;
    displaydata->use_xrandr = true;
    displaydata->xrandr_output = outputid;
    SDL_strlcpy(displaydata->connector_name, display_name, परिमाण(displaydata->connector_name));

    bool gamescope = false;
    MonitorInfo *info = GetMonitorInfo(dpy, screen, outputid, &gamescope);

    समुच्चयः_XRand_RMode_Info(dpy, res, output_crtc, बहुलकम्_ID, &बहुलकम्);
    समुच्चयः_XRand_RDisplay_Name(info, display_name, display_name_आकार, display_mm_विस्तारः, display_mm_height);

    SDL_zero(*display);
    यदि (*display_name) {
        display->name = display_name;
    }
    display->desktop_बहुलकम् = बहुलकम्;
    display->content_scale = X11_GetGlobalContentScaleForDevice(_this);
    display->आन्तरिकम् = displaydata;

    यदि (info) {
        भिन्न SDR_white_level;

        // Note that the gamescope values aren't updated if the display settings change while we're running
        यदि (gamescope) {
            SDR_white_level = GetGamescopeSDRWhiteLevel(dpy, screen, info);
        } अन्यथा {
            // Support for HDR on X11 seems spotty, let's disable this for now
            SDR_white_level = 0.0f;
        }

#यदि_परिभाषितम् X11MODES_DEBUG
        SDL_Log("HDR values: %f / %f", SDR_white_level, info->max_luminance);
#यदि_अन्तः
        यदि (SDR_white_level > 0.0f && info->max_luminance > SDR_white_level) {
            display->HDR.HDR_headroom = (भिन्न)info->max_luminance / SDR_white_level;
            display->HDR.SDR_white_level = SDR_white_level / SCRGB_NITS;
        }

        SDL_free(info);
    }

    प्रत्यागम true;
}

स्थिर bool X11_सङ्कलय_XRand_RDisplay(SDL_VideoDevice *_this, Display *dpy, पूर्णाङ्क screen, RROutput outputid, XRRScreenResources *res, bool send_event)
{
    SDL_VideoDisplay display;
    वर्ण display_name[128];

    यदि (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, परिमाण(display_name))) {
        प्रत्यागम true; // failed to query data, skip this display
    }

    SDL_DisplayID displayID = SDL_सङ्कलय_Video_Display(&display, false);
    यदि (displayID == 0) {
        प्रत्यागम false;
    }

    // We added an XRandR display, remove the generic display, if any
    X11_RemoveGenericDisplay(_this);

    यदि (send_event) {
        SDL_SendDisplayEvent(SDL_GetVideoDisplay(displayID), SDL_EVENT_DISPLAY_ADDED, 0, 0);
    }
    प्रत्यागम true;
}


स्थिर bool X11_UpdateXRandRDisplay(SDL_VideoDevice *_this, Display *dpy, पूर्णाङ्क screen, RROutput outputid, XRRScreenResources *res, SDL_VideoDisplay *existing_display)
{
    SDL_VideoDisplay display;
    वर्ण display_name[128];

    यदि (!X11_FillXRandRDisplayInfo(_this, dpy, screen, outputid, res, &display, display_name, परिमाण(display_name))) {
        प्रत्यागम false; // failed to query current display state
    }

    // update mode - this call takes ownership of display.desktop_mode.internal
    SDL_समुच्चयः_Desktop_Display_बहुलकम्(existing_display, &display.desktop_बहुलकम्);

    // update bounds
    यदि (existing_display->आन्तरिकम्->x != display.आन्तरिकम्->x ||
        existing_display->आन्तरिकम्->y != display.आन्तरिकम्->y) {
        existing_display->आन्तरिकम्->x = display.आन्तरिकम्->x;
        existing_display->आन्तरिकम्->y = display.आन्तरिकम्->y;
        SDL_SendDisplayEvent(existing_display, SDL_EVENT_DISPLAY_MOVED, 0, 0);
    }

    // update scale
    SDL_समुच्चयः_Display_Content_Scale(existing_display, display.content_scale);

    // update HDR properties
    SDL_समुच्चयः_Display_HDRProperties(existing_display, &display.HDR);

    // SDL_DisplayData is updated piece-meal above, free our local copy of this data
    SDL_free(display.आन्तरिकम्);

    प्रत्यागम true;
}

स्थिर XRRScreenResources *X11_GetScreenResources(Display *dpy, पूर्णाङ्क screen)
{
    XRRScreenResources *res = X11_XRRGetScreenResourcesCurrent(dpy, मूलम्_गवाक्षः(dpy, screen));
    यदि (!res || res->noutput == 0) {
        यदि (res) {
            X11_XRRFreeScreenResources(res);
        }
        res = X11_XRRGetScreenResources(dpy, मूलम्_गवाक्षः(dpy, screen));
    }
    प्रत्यागम res;
}

शून्य X11_CheckDisplaysMoved(SDL_VideoDevice *_this, Display *dpy)
{
    ध्रुव पूर्णाङ्क screencount = Screen_गणनम्(dpy);

    SDL_DisplayID *displays = SDL_GetDisplays(रिक्त);
    यदि (!displays) {
        प्रत्यागम;
    }

    प्रति (पूर्णाङ्क screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        यदि (!res) {
            अनुवर्त;
        }

        प्रति (पूर्णाङ्क i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ध्रुव SDL_Display_दत्त *displaydata = display->आन्तरिकम्;
            यदि (displaydata->xrandr_output && displaydata->screen == screen) {
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
    यदि (!displays) {
        प्रत्यागम;
    }

    प्रति (पूर्णाङ्क screen = 0; screen < screencount; ++screen) {
        XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
        यदि (!res) {
            अनुवर्त;
        }

        प्रति (पूर्णाङ्क output = 0; output < res->noutput; output++) {
            प्रति (पूर्णाङ्क i = 0; i < अङ्कः_displays; ++i) {
                यदि (!displays[i]) {
                    // We already removed this display from the list
                    अनुवर्त;
                }

                SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
                ध्रुव SDL_Display_दत्त *displaydata = display->आन्तरिकम्;
                यदि (displaydata->xrandr_output == res->outputs[output]) {
                    // This display is active, remove it from the list
                    displays[i] = 0;
                    भङ्ग;
                }
            }
        }
        X11_XRRFreeScreenResources(res);
    }

    प्रति (पूर्णाङ्क i = 0; i < अङ्कः_displays; ++i) {
        यदि (displays[i]) {
            SDL_VideoDisplay *display = SDL_GetVideoDisplay(displays[i]);
            ध्रुव SDL_Display_दत्त *displaydata = display->आन्तरिकम्;
            यदि (displaydata->xrandr_output) {
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

#यदि 0
    SDL_Log("XRROutputChangeNotifyEvent! [output=%u, crtc=%u, mode=%u, rotation=%u, connection=%u]\n", (अचिह्नित पूर्णाङ्क) ev->output, (अचिह्नित पूर्णाङ्क) ev->crtc, (अचिह्नित पूर्णाङ्क) ev->बहुलकम्, (अचिह्नित पूर्णाङ्क) ev->rotation, (अचिह्नित पूर्णाङ्क) ev->connection);
#यदि_अन्तः

    // XWayland doesn't always send output disconnected events
    X11_CheckDisplaysRemoved(_this, ev->display);

    displays = SDL_GetDisplays(रिक्त);
    यदि (displays) {
        प्रति (i = 0; displays[i]; ++i) {
            SDL_VideoDisplay *thisdisplay = SDL_GetVideoDisplay(displays[i]);
            ध्रुव SDL_Display_दत्त *displaydata = thisdisplay->आन्तरिकम्;
            यदि (displaydata->xrandr_output == ev->output) {
                display = thisdisplay;
                भङ्ग;
            }
        }
        SDL_free(displays);
    }

    यदि (ev->connection == RR_Disconnected) { // output is going away
        यदि (display) {
            // Add the generic display if we're about to remove the last XRandR display
            SDL_DisplayID generic_display = 0;
            यदि (_this->अङ्कः_displays == 1) {
                generic_display = X11_सङ्कलय_Generic_Display(_this, false);
            }

            SDL_DelVideoDisplay(display->id, true);

            यदि (generic_display) {
                SDL_SendDisplayEvent(SDL_GetVideoDisplay(generic_display), SDL_EVENT_DISPLAY_ADDED, 0, 0);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);

    } अन्यथा यदि (ev->connection == RR_Connected) { // output is coming online
        यदि (!display) {
            Display *dpy = ev->display;
            ध्रुव पूर्णाङ्क screen = DefaultScreen(dpy);
            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            यदि (res) {
                X11_सङ्कलय_XRand_RDisplay(_this, dpy, screen, ev->output, res, true);
                X11_XRRFreeScreenResources(res);
            }
        }
        X11_CheckDisplaysMoved(_this, ev->display);
    }
}

शून्य X11_HandleXRandREvent(SDL_VideoDevice *_this, ध्रुव XEvent *xevent)
{
    SDL_Video_दत्त *videodata = _this->आन्तरिकम्;
    SDL_assert(xevent->type == (videodata->xrandr_event_आधारः + RRNotify));

    विकल्प (((ध्रुव XRRNotifyEvent *)xevent)->subtype) {
    पक्ष RRNotify_OutputChange:
        X11_HandleXRandROutputChange(_this, (ध्रुव XRROutputChangeNotifyEvent *)xevent);
        भङ्ग;
    स्वभाव:
        भङ्ग;
    }
}

स्थिर शून्य X11_क्रमय_Outputs_By_प्राथमिकता_Hint(SDL_VideoDevice *_this)
{
    ध्रुव वर्ण *name_hint = SDL_GetHint(SDL_HINT_VIDEO_DISPLAY_प्राथमिकता);

    यदि (name_hint) {
        वर्ण *saveptr;
        वर्ण *str = SDL_strdup(name_hint);
        SDL_VideoDisplay **sorted_list = SDL_malloc(परिमाण(SDL_VideoDisplay *) * _this->अङ्कः_displays);

        यदि (str && sorted_list) {
            पूर्णाङ्क sorted_सूचकांक = 0;

            // Sort the requested displays to the front of the list.
            ध्रुव वर्ण *token = SDL_strtok_r(str, ",", &saveptr);
            यावत् (token) {
                प्रति (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
                    SDL_VideoDisplay *d = _this->displays[i];
                    यदि (d) {
                        SDL_Display_दत्त *दत्त = d->आन्तरिकम्;
                        यदि (SDL_strcmp(token, दत्त->connector_name) == 0) {
                            sorted_list[sorted_सूचकांक++] = d;
                            _this->displays[i] = रिक्त;
                            भङ्ग;
                        }
                    }
                }

                token = SDL_strtok_r(रिक्त, ",", &saveptr);
            }

            // Append the remaining displays to the end of the list.
            प्रति (पूर्णाङ्क i = 0; i < _this->अङ्कः_displays; ++i) {
                यदि (_this->displays[i]) {
                    sorted_list[sorted_सूचकांक++] = _this->displays[i];
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
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    Display *dpy = दत्त->display;
    ध्रुव पूर्णाङ्क screencount = Screen_गणनम्(dpy);
    ध्रुव पूर्णाङ्क default_screen = DefaultScreen(dpy);
    RROutput primary = X11_XRRGetOutputPrimary(dpy, मूलम्_गवाक्षः(dpy, default_screen));
    पूर्णाङ्क xrandr_error_आधारः = 0;
    पूर्णाङ्क looking_for_primary;
    पूर्णाङ्क output;
    पूर्णाङ्क screen;

    यदि (!X11_XRRQueryExtension(dpy, &दत्त->xrandr_event_आधारः, &xrandr_error_आधारः)) {
        प्रत्यागम SDL_समुच्चयः_Error("XRRQueryExtension failed");
    }

    प्रति (looking_for_primary = 1; looking_for_primary >= 0; looking_for_primary--) {
        प्रति (screen = 0; screen < screencount; screen++) {

            // we want the primary output first, and then skipped later.
            यदि (looking_for_primary && (screen != default_screen)) {
                अनुवर्त;
            }

            XRRScreenResources *res = X11_GetScreenResources(dpy, screen);
            यदि (!res) {
                अनुवर्त;
            }

            प्रति (output = 0; output < res->noutput; output++) {
                // The primary output _should_ always be sorted first, but just in case...
                यदि ((looking_for_primary && (res->outputs[output] != primary)) ||
                    (!looking_for_primary && (screen == default_screen) && (res->outputs[output] == primary))) {
                    अनुवर्त;
                }
                यदि (!X11_सङ्कलय_XRand_RDisplay(_this, dpy, screen, res->outputs[output], res, false)) {
                    भङ्ग;
                }
            }

            X11_XRRFreeScreenResources(res);

            // This will generate events for displays that come and go at runtime.
            X11_XRRSelect_निवेशः(dpy, मूलम्_गवाक्षः(dpy, screen), RROutput_Change_Notify_आवरणम्);
        }
    }

    यदि (_this->अङ्कः_displays == 0) {
        प्रत्यागम SDL_समुच्चयः_Error("No available displays");
    }

    X11_क्रमय_Outputs_By_प्राथमिकता_Hint(_this);

    प्रत्यागम true;
}
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XRANDR

/* This is used if there's no better functionality--like XRandR--to use.
   It won't attempt to supply different display modes at all, but it can
   enumerate the current displays and their current sizes. */
स्थिर bool X11_InitModes_StdXlib(SDL_VideoDevice *_this)
{
    यदि (X11_सङ्कलय_Generic_Display(_this, true) == 0) {
        प्रत्यागम false;
    }
    प्रत्यागम true;
}

bool X11_InitModes(SDL_VideoDevice *_this)
{
    /* XRandR is the One True Modern Way to do this on X11. If this
       fails, we just won't report any display modes except the current
       desktop size. */
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
    {
        SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
        पूर्णाङ्क xrandr_major, xrandr_minor;
        // require at least XRandR v1.3
        यदि (CheckXRandR(दत्त->display, &xrandr_major, &xrandr_minor) &&
            (xrandr_major >= 2 || (xrandr_major == 1 && xrandr_minor >= 3)) &&
            X11_InitModes_XRandR(_this)) {
            प्रत्यागम true;
        }
    }
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XRANDR

    // still here? Just set up an extremely basic display.
    प्रत्यागम X11_InitModes_StdXlib(_this);
}

bool X11_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display)
{
#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
    SDL_Display_दत्त *दत्त = sdl_display->आन्तरिकम्;
    SDL_Display_बहुलकम् बहुलकम्;

    /* Unfortunately X11 requires the window to be created with the correct
     * visual and depth ahead of time, but the SDL API allows you to create
     * a window before setting the fullscreen display mode.  This means that
     * we have to use the same format for all windows and all display modes.
     * (or support recreating the window with a new visual behind the scenes)
     */
    SDL_zero(बहुलकम्);
    बहुलकम्.format = sdl_display->desktop_बहुलकम्.format;

    यदि (दत्त->use_xrandr) {
        Display *display = _this->आन्तरिकम्->display;
        XRRScreenResources *res;

        res = X11_XRRGetScreenResources(display, मूलम्_गवाक्षः(display, दत्त->screen));
        यदि (res) {
            SDL_Display_बहुलकम्_दत्त *modedata;
            XRROutputInfo *output_info;
            पूर्णाङ्क i;

            output_info = X11_XRRGetOutputInfo(display, res, दत्त->xrandr_output);
            यदि (output_info && output_info->connection != RR_Disconnected) {
                प्रति (i = 0; i < output_info->nmode; ++i) {
                    modedata = (SDL_Display_बहुलकम्_दत्त *)SDL_calloc(1, परिमाण(SDL_Display_बहुलकम्_दत्त));
                    यदि (!modedata) {
                        अनुवर्त;
                    }
                    बहुलकम्.आन्तरिकम् = modedata;

                    यदि (!समुच्चयः_XRand_RMode_Info(display, res, output_info->crtc, output_info->modes[i], &बहुलकम्) ||
                        !SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(sdl_display, &बहुलकम्)) {
                        SDL_free(modedata);
                    }
                }
            }
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
        }
    }
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XRANDR
    प्रत्यागम true;
}

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
// This catches an error from XRRSetScreenSize, as a workaround for now.
// !!! FIXME: remove this later when we have a better solution.
स्थिर पूर्णाङ्क (*Pre_XRRSet_Screen_आकार_Error_Handler)(Display *, XErrorEvent *) = रिक्त;
स्थिर पूर्णाङ्क SDL_XRRSet_Screen_आकार_Err_Handler(Display *d, XErrorEvent *e)
{
    // BadMatch: https://github.com/libsdl-org/SDL/issues/4561
    // BadValue: https://github.com/libsdl-org/SDL/issues/4840
    यदि ((e->error_संहिता == Bad_मेलनम्) || (e->error_संहिता == Bad_मानम्)) {
        प्रत्यागम 0;
    }

    प्रत्यागम Pre_XRRSet_Screen_आकार_Error_Handler(d, e);
}
#यदि_अन्तः

bool X11_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_Video_दत्त *viddata = _this->आन्तरिकम्;
    SDL_Display_दत्त *दत्त = sdl_display->आन्तरिकम्;

    viddata->चरमः_बहुलकम्_change_deadline = SDL_GetTicks() + (PENDING_FOCUS_TIME * 2);

    // XWayland mode switches are emulated with viewports and thus instantaneous.
    यदि (!viddata->is_xwayland) {
        यदि (sdl_display->current_बहुलकम् != बहुलकम्) {
            दत्त->बहुलकम्_switch_deadline_ns = SDL_GetTicksNS() + बहुलकम्_SWITCH_TIMEOUT_NS;
        } अन्यथा {
            दत्त->बहुलकम्_switch_deadline_ns = 0;
        }
    }

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XRANDR
    यदि (दत्त->use_xrandr) {
        Display *display = viddata->display;
        SDL_Display_बहुलकम्_दत्त *modedata = बहुलकम्->आन्तरिकम्;
        पूर्णाङ्क mm_विस्तारः, mm_height;
        XRRScreenResources *res;
        XRROutputInfo *output_info;
        XRRCrtcInfo *crtc;
        स्थितिः_2 स्थितिः;

        res = X11_XRRGetScreenResources(display, मूलम्_गवाक्षः(display, दत्त->screen));
        यदि (!res) {
            प्रत्यागम SDL_समुच्चयः_Error("Couldn't get XRandR screen resources");
        }

        output_info = X11_XRRGetOutputInfo(display, res, दत्त->xrandr_output);
        यदि (!output_info || output_info->connection == RR_Disconnected) {
            X11_XRRFreeScreenResources(res);
            प्रत्यागम SDL_समुच्चयः_Error("Couldn't get XRandR output info");
        }

        crtc = X11_XRRGetCrtcInfo(display, res, output_info->crtc);
        यदि (!crtc) {
            X11_XRRFreeOutputInfo(output_info);
            X11_XRRFreeScreenResources(res);
            प्रत्यागम SDL_समुच्चयः_Error("Couldn't get XRandR crtc info");
        }

        यदि (crtc->बहुलकम् == modedata->xrandr_बहुलकम्) {
#यदि_परिभाषितम् X11MODES_DEBUG
            SDL_Log("already in desired mode 0x%lx (%ux%u), nothing to do\n",
                    crtc->बहुलकम्, crtc->विस्तारः, crtc->height);
#यदि_अन्तः
            स्थितिः = Success;
            गच्छ freeInfo;
        }

        X11_XGrabServer(display);
        स्थितिः = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      0, 0, None, crtc->rotation, रिक्त, 0);
        यदि (स्थितिः != Success) {
            गच्छ ungrabServer;
        }

        mm_विस्तारः = बहुलकम्->w * Display_विस्तारः_MM(display, दत्त->screen) / Display_विस्तारः(display, दत्त->screen);
        mm_height = बहुलकम्->h * DisplayHeightMM(display, दत्त->screen) / DisplayHeight(display, दत्त->screen);

        /* !!! FIXME: this can get into a problem scenario when a window is
           bigger than a physical monitor in a configuration where one screen
           spans multiple physical monitors. A detailed reproduction case is
           discussed at https://github.com/libsdl-org/SDL/issues/4561 ...
           for now we cheat and just catch the X11 error and carry on, which
           is likely to cause subtle issues but is better than outright
           crashing */
        X11_XSync(display, False);
        Pre_XRRSet_Screen_आकार_Error_Handler = X11_XSetErrorHandler(SDL_XRRSet_Screen_आकार_Err_Handler);
        X11_XRRSet_Screen_आकार(display, मूलम्_गवाक्षः(display, दत्त->screen),
                             बहुलकम्->w, बहुलकम्->h, mm_विस्तारः, mm_height);
        X11_XSync(display, False);
        X11_XSetErrorHandler(Pre_XRRSet_Screen_आकार_Error_Handler);

        स्थितिः = X11_XRRSetCrtcConfig(display, res, output_info->crtc, CurrentTime,
                                      crtc->x, crtc->y, modedata->xrandr_बहुलकम्, crtc->rotation,
                                      &दत्त->xrandr_output, 1);

    ungrabServer:
        X11_XUngrabServer(display);
    freeInfo:
        X11_XRRFreeCrtcInfo(crtc);
        X11_XRRFreeOutputInfo(output_info);
        X11_XRRFreeScreenResources(res);

        यदि (स्थितिः != Success) {
            प्रत्यागम SDL_समुच्चयः_Error("X11_XRRSetCrtcConfig failed");
        }
    }
#अन्यथा
    (शून्य)दत्त;
#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XRANDR

    प्रत्यागम true;
}

शून्य X11_QuitModes(SDL_VideoDevice *_this)
{
}

bool X11_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Display_दत्त *दत्त = sdl_display->आन्तरिकम्;

    rect->x = दत्त->x;
    rect->y = दत्त->y;
    rect->w = sdl_display->current_बहुलकम्->w;
    rect->h = sdl_display->current_बहुलकम्->h;
    प्रत्यागम true;
}

bool X11_GetDisplayUsableBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *sdl_display, SDL_Rect *rect)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    Display *display = दत्त->display;
    Atom _NET_WORKAREA;
    पूर्णाङ्क real_format;
    Atom real_type;
    अचिह्नित दीर्घ वस्तूनि_read = 0, वस्तूनि_वामः = 0;
    अचिह्नित वर्ण *propdata = रिक्त;
    bool परिणाम = false;

    यदि (!X11_GetDisplayBounds(_this, sdl_display, rect)) {
        प्रत्यागम false;
    }

    _NET_WORKAREA = X11_XInternAtom(display, "_NET_WORKAREA", False);
    पूर्णाङ्क स्थितिः = X11_XGet_गवाक्षः_Property(display, Default_मूलम्_गवाक्षः(display),
                                    _NET_WORKAREA, 0L, 4L, False, XA_CARDINAL,
                                    &real_type, &real_format, &वस्तूनि_read,
                                    &वस्तूनि_वामः, &propdata);
    यदि ((स्थितिः == Success) && (वस्तूनि_read >= 4)) {
        ध्रुव दीर्घ *p = (दीर्घ *)propdata;
        ध्रुव SDL_Rect usable = { (पूर्णाङ्क)p[0], (पूर्णाङ्क)p[1], (पूर्णाङ्क)p[2], (पूर्णाङ्क)p[3] };
        परिणाम = true;
        यदि (!SDL_GetRectIntersection(rect, &usable, rect)) {
            SDL_zerop(rect);
        }
    }

    यदि (propdata) {
        X11_XFree(propdata);
    }

    प्रत्यागम परिणाम;
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11
