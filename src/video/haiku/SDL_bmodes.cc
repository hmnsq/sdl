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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#অন্তর্ভাব <AppKit.h>
#অন্তর্ভাব <InterfaceKit.h>
#অন্তর্ভাব "SDL_bmodes.h"
#অন্তর্ভাব "SDL_BWin.h"

#ifdef SDL_VIDEO_OPENGL
#অন্তর্ভাব "SDL_bopengl.h"
#endif

#অন্তর্ভাব "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
বাহ্য "C" {
#endif


#define WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#যদি WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
সংরচনা SDL_DisplayModeData {
    display_mode *bmode;
};
#endif

স্থির SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    প্রত্যাগম (SDL_BWin *)(window->internal);
}

স্থির SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    প্রত্যাগম SDL_Looper;
}

স্থির SDL_INLINE display_mode * _ExtractBMode(SDL_DisplayMode *mode)
{
#যদি WRAP_BMODE
    প্রত্যাগম mode->internal->bmode;
#অন্যথা
    প্রত্যাগম (display_mode *)mode->internal;
#endif
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
স্থির শূন্য get_refresh_rate(display_mode &mode, পূর্ণাঙ্ক *numerator, পূর্ণাঙ্ক *denominator)
{
    *numerator = (mode.timing.pixel_clock * 1000);
    *denominator = (mode.timing.h_total * mode.timing.v_total);
}


#যদি 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
শূন্য _SpoutModeData(display_mode *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_width, bmode->virtual_height);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_start,
            bmode->v_display_start);
    যদি (bmode->flags) {
        SDL_Log("\tFlags:");
        যদি (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        যদি (bmode->flags & B_8_BIT_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        যদি (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        যদি (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        যদি (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        যদি (bmode->flags & B_IO_FB_NA) {
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
    যদি (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        যদি (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        যদি (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        যদি (bmode->timing.flags & B_POSITIVE_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        যদি (bmode->timing.flags & B_POSITIVE_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        যদি (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#endif



SDL_PixelFormat HAIKU_ColorSpaceToSDLPxFormat(uint32 colorspace)
{
    বিকল্প (colorspace) {
    পক্ষ B_CMAP8:
        প্রত্যাগম SDL_PIXELFORMAT_INDEX8;
        ভঙ্গ;
    পক্ষ B_RGB15:
    পক্ষ B_RGBA15:
    পক্ষ B_RGB15_BIG:
    পক্ষ B_RGBA15_BIG:
        প্রত্যাগম SDL_PIXELFORMAT_XRGB1555;
        ভঙ্গ;
    পক্ষ B_RGB16:
    পক্ষ B_RGB16_BIG:
        প্রত্যাগম SDL_PIXELFORMAT_RGB565;
        ভঙ্গ;
    পক্ষ B_RGB24:
    পক্ষ B_RGB24_BIG:
        প্রত্যাগম SDL_PIXELFORMAT_BGR24;
        ভঙ্গ;
    পক্ষ B_RGB32:
    পক্ষ B_RGBA32:
    পক্ষ B_RGB32_BIG:
    পক্ষ B_RGBA32_BIG:
        প্রত্যাগম SDL_PIXELFORMAT_XRGB8888;
        ভঙ্গ;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_SetError("Invalid color space");
    প্রত্যাগম SDL_PIXELFORMAT_UNKNOWN;
}

স্থির শূন্য _BDisplayModeToSdlDisplayMode(display_mode *bmode, SDL_DisplayMode *mode)
{
    SDL_zerop(mode);
    mode->w = bmode->virtual_width;
    mode->h = bmode->virtual_height;
    get_refresh_rate(*bmode, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);

#যদি WRAP_BMODE
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)SDL_calloc(1, পরিমাণ(SDL_DisplayModeData));
    data->bmode = bmode;

    mode->internal = data;
#অন্যথা
    mode->internal = bmode;
#endif

    // Set the format
    mode->format = HAIKU_ColorSpaceToSDLPxFormat(bmode->space);
}

// Later, there may be more than one monitor available
স্থির শূন্য _AddDisplay(BScreen *screen)
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

তার্কিক HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    _AddDisplay(&screen);
    প্রত্যাগম সত্য;
}

শূন্য HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    প্রত্যাগম;
}


তার্কিক HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.Frame();
    rect->x = (পূর্ণাঙ্ক)rc.বাম;
    rect->y = (পূর্ণাঙ্ক)rc.শীর্ষ;
    rect->w = (পূর্ণাঙ্ক)rc.Width() + 1;
    rect->h = (পূর্ণাঙ্ক)rc.Height() + 1;
    প্রত্যাগম সত্য;
}

তার্কিক HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_DisplayMode mode;
    display_mode this_bmode;
    display_mode *bmodes;
    uint32 গুনতি, i;
    তার্কিক retval = অসত্য;

    // Get graphics-hardware supported modes
    যদি (bscreen.GetModeList(&bmodes, &গুনতি) == B_OK) {
        যদি (bscreen.GetMode(&this_bmode) == B_OK) {
            প্রতি (i = 0; i < গুনতি; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                যদি (bmodes[i].space == this_bmode.space) {
                    _BDisplayModeToSdlDisplayMode(&bmodes[i], &mode);
                    SDL_AddFullscreenDisplayMode(display, &mode);
                }
            }
            retval = সত্য;
        }
        মুক্ত(bmodes); // This should NOT be SDL_free()
    }

    প্রত্যাগম retval;
}


তার্কিক HAIKU_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    // Get the current screen
    BScreen bscreen;
    যদি (!bscreen.IsValid()) {
        প্রত্যাগম SDL_SetError("Invalid screen");
    }

    // Set the mode using the driver data
    display_mode *bmode = _ExtractBMode(mode);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_mode *bmode_list;
    bscreen.GetModeList(&bmode_list, &c);
    প্রতি (i = 0; i < c; ++i) {
        যদি (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_width == bmode->virtual_width &&
            bmode_list[i].virtual_height == bmode->virtual_height ) {
                bmode = &bmode_list[i];
                ভঙ্গ;
        }
    }

    যদি (bscreen.SetMode(bmode) != B_OK) {
        প্রত্যাগম SDL_SetError("Bad video mode");
    }

    মুক্ত(bmode_list); // This should NOT be SDL_free()

#ifdef SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#endif

    প্রত্যাগম সত্য;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
