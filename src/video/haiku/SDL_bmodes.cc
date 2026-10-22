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

#ifdef SDL_VIDEO_DRIVER_HAIKU

#ضمن <AppKit.h>
#ضمن <InterfaceKit.h>
#ضمن "SDL_bmodes.h"
#ضمن "SDL_BWin.h"

#ifdef SDL_VIDEO_OPENGL
#ضمن "SDL_bopengl.h"
#endif

#ضمن "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
خارجي "C" {
#endif


#define WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#إذا WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
بنية SDL_DisplayModeData {
    display_mode *bmode;
};
#endif

ساكن SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    إرجاع (SDL_BWin *)(window->internal);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    إرجاع SDL_Looper;
}

ساكن SDL_INLINE display_mode * _ExtractBMode(SDL_DisplayMode *mode)
{
#إذا WRAP_BMODE
    إرجاع mode->internal->bmode;
#وإلا
    إرجاع (display_mode *)mode->internal;
#endif
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
ساكن فراغ get_refresh_rate(display_mode &mode, صحيح *numerator, صحيح *denominator)
{
    *numerator = (mode.timing.pixel_clock * 1000);
    *denominator = (mode.timing.h_total * mode.timing.v_total);
}


#إذا 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
فراغ _SpoutModeData(display_mode *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_width, bmode->virtual_height);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_start,
            bmode->v_display_start);
    إذا (bmode->flags) {
        SDL_Log("\tFlags:");
        إذا (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        إذا (bmode->flags & B_8_BIT_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        إذا (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        إذا (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        إذا (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        إذا (bmode->flags & B_IO_FB_NA) {
            SDL_Log("\t\tB_IO_FB_NA");
        }
    }
    SDL_Log("\tTiming:");
    SDL_Log("\t\tpx clock: %i", bmode->timing.pixel_clock);
    SDL_Log("\t\th - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.h_display, bmode->timing.h_sync_start,
        bmode->timing.h_sync_end, bmode->timing.h_total);
    SDL_Log("\t\tv - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.v_display, bmode->timing.v_sync_start,
        bmode->timing.v_sync_end, bmode->timing.v_total);
    إذا (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        إذا (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        إذا (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        إذا (bmode->timing.flags & B_POSITIVE_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        إذا (bmode->timing.flags & B_POSITIVE_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        إذا (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#endif



SDL_PixelFormat HAIKU_ColorSpaceToSDLPxFormat(uint32 colorspace)
{
    بدل (colorspace) {
    حالة B_CMAP8:
        إرجاع SDL_PIXELFORMAT_INDEX8;
        اكسر;
    حالة B_RGB15:
    حالة B_RGBA15:
    حالة B_RGB15_BIG:
    حالة B_RGBA15_BIG:
        إرجاع SDL_PIXELFORMAT_XRGB1555;
        اكسر;
    حالة B_RGB16:
    حالة B_RGB16_BIG:
        إرجاع SDL_PIXELFORMAT_RGB565;
        اكسر;
    حالة B_RGB24:
    حالة B_RGB24_BIG:
        إرجاع SDL_PIXELFORMAT_BGR24;
        اكسر;
    حالة B_RGB32:
    حالة B_RGBA32:
    حالة B_RGB32_BIG:
    حالة B_RGBA32_BIG:
        إرجاع SDL_PIXELFORMAT_XRGB8888;
        اكسر;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_SetError("Invalid color space");
    إرجاع SDL_PIXELFORMAT_UNKNOWN;
}

ساكن فراغ _BDisplayModeToSdlDisplayMode(display_mode *bmode, SDL_DisplayMode *mode)
{
    SDL_zerop(mode);
    mode->w = bmode->virtual_width;
    mode->h = bmode->virtual_height;
    get_refresh_rate(*bmode, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);

#إذا WRAP_BMODE
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)SDL_calloc(1, حجم(SDL_DisplayModeData));
    data->bmode = bmode;

    mode->internal = data;
#وإلا
    mode->internal = bmode;
#endif

    // Set the format
    mode->format = HAIKU_ColorSpaceToSDLPxFormat(bmode->space);
}

// Later, there may be more than one monitor available
ساكن فراغ _AddDisplay(BScreen *screen)
{
    SDL_DisplayMode mode;
    display_mode bmode;
    screen->GetMode(&bmode);

    _BDisplayModeToSdlDisplayMode(&bmode, &mode);

    SDL_AddBasicVideoDisplay(&mode);
}

/*
 * Functions called by SDL
 */

منطقي HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    _AddDisplay(&screen);
    إرجاع true;
}

فراغ HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    إرجاع;
}


منطقي HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.Frame();
    rect->x = (صحيح)rc.يسار;
    rect->y = (صحيح)rc.قمة;
    rect->w = (صحيح)rc.Width() + 1;
    rect->h = (صحيح)rc.Height() + 1;
    إرجاع true;
}

منطقي HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_DisplayMode mode;
    display_mode this_bmode;
    display_mode *bmodes;
    uint32 تعداد_2, i;
    منطقي retval = خطأ;

    // Get graphics-hardware supported modes
    إذا (bscreen.GetModeList(&bmodes, &تعداد_2) == B_OK) {
        إذا (bscreen.GetMode(&this_bmode) == B_OK) {
            لكل (i = 0; i < تعداد_2; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                إذا (bmodes[i].space == this_bmode.space) {
                    _BDisplayModeToSdlDisplayMode(&bmodes[i], &mode);
                    SDL_AddFullscreenDisplayMode(display, &mode);
                }
            }
            retval = true;
        }
        حرر(bmodes); // This should NOT be SDL_free()
    }

    إرجاع retval;
}


منطقي HAIKU_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    // Get the current screen
    BScreen bscreen;
    إذا (!bscreen.IsValid()) {
        إرجاع SDL_SetError("Invalid screen");
    }

    // Set the mode using the driver data
    display_mode *bmode = _ExtractBMode(mode);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_mode *bmode_list;
    bscreen.GetModeList(&bmode_list, &c);
    لكل (i = 0; i < c; ++i) {
        إذا (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_width == bmode->virtual_width &&
            bmode_list[i].virtual_height == bmode->virtual_height ) {
                bmode = &bmode_list[i];
                اكسر;
        }
    }

    إذا (bscreen.SetMode(bmode) != B_OK) {
        إرجاع SDL_SetError("Bad video mode");
    }

    حرر(bmode_list); // This should NOT be SDL_free()

#ifdef SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#endif

    إرجاع true;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
