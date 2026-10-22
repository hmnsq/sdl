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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#ଅନ୍ତର୍ଭାଵ <AppKit.h>
#ଅନ୍ତର୍ଭାଵ <InterfaceKit.h>
#ଅନ୍ତର୍ଭାଵ "SDL_bmodes.h"
#ଅନ୍ତର୍ଭାଵ "SDL_BWin.h"

#ifdef SDL_VIDEO_OPENGL
#ଅନ୍ତର୍ଭାଵ "SDL_bopengl.h"
#endif

#ଅନ୍ତର୍ଭାଵ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif


#define WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#ଯଦି WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
ସଂରଚନା SDL_DisplayModeData {
    display_mode *bmode;
};
#endif

ସ୍ଥିର SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    ଫେରନ୍ତୁ (SDL_BWin *)(window->internal);
}

ସ୍ଥିର SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ଫେରନ୍ତୁ SDL_Looper;
}

ସ୍ଥିର SDL_INLINE display_mode * _ExtractBMode(SDL_DisplayMode *mode)
{
#ଯଦି WRAP_BMODE
    ଫେରନ୍ତୁ mode->internal->bmode;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ (display_mode *)mode->internal;
#endif
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
ସ୍ଥିର ଶୂନ୍ୟ get_refresh_rate(display_mode &mode, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *numerator, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *denominator)
{
    *numerator = (mode.timing.pixel_clock * 1000);
    *denominator = (mode.timing.h_total * mode.timing.v_total);
}


#ଯଦି 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
ଶୂନ୍ୟ _SpoutModeData(display_mode *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_width, bmode->virtual_height);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_start,
            bmode->v_display_start);
    ଯଦି (bmode->flags) {
        SDL_Log("\tFlags:");
        ଯଦି (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        ଯଦି (bmode->flags & B_8_BIT_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        ଯଦି (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        ଯଦି (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        ଯଦି (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        ଯଦି (bmode->flags & B_IO_FB_NA) {
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
    ଯଦି (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        ଯଦି (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        ଯଦି (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        ଯଦି (bmode->timing.flags & B_POSITIVE_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        ଯଦି (bmode->timing.flags & B_POSITIVE_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        ଯଦି (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#endif



SDL_PixelFormat HAIKU_ColorSpaceToSDLPxFormat(uint32 colorspace)
{
    ବାଛ (colorspace) {
    ସ୍ଥିତି B_CMAP8:
        ଫେରନ୍ତୁ SDL_PIXELFORMAT_INDEX8;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି B_RGB15:
    ସ୍ଥିତି B_RGBA15:
    ସ୍ଥିତି B_RGB15_BIG:
    ସ୍ଥିତି B_RGBA15_BIG:
        ଫେରନ୍ତୁ SDL_PIXELFORMAT_XRGB1555;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି B_RGB16:
    ସ୍ଥିତି B_RGB16_BIG:
        ଫେରନ୍ତୁ SDL_PIXELFORMAT_RGB565;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି B_RGB24:
    ସ୍ଥିତି B_RGB24_BIG:
        ଫେରନ୍ତୁ SDL_PIXELFORMAT_BGR24;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି B_RGB32:
    ସ୍ଥିତି B_RGBA32:
    ସ୍ଥିତି B_RGB32_BIG:
    ସ୍ଥିତି B_RGBA32_BIG:
        ଫେରନ୍ତୁ SDL_PIXELFORMAT_XRGB8888;
        ଭାଙ୍ଗ;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_SetError("Invalid color space");
    ଫେରନ୍ତୁ SDL_PIXELFORMAT_UNKNOWN;
}

ସ୍ଥିର ଶୂନ୍ୟ _BDisplayModeToSdlDisplayMode(display_mode *bmode, SDL_DisplayMode *mode)
{
    SDL_zerop(mode);
    mode->w = bmode->virtual_width;
    mode->h = bmode->virtual_height;
    get_refresh_rate(*bmode, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);

#ଯଦି WRAP_BMODE
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)SDL_calloc(1, ଆକାର(SDL_DisplayModeData));
    data->bmode = bmode;

    mode->internal = data;
#ଅନ୍ୟଥା
    mode->internal = bmode;
#endif

    // Set the format
    mode->format = HAIKU_ColorSpaceToSDLPxFormat(bmode->space);
}

// Later, there may be more than one monitor available
ସ୍ଥିର ଶୂନ୍ୟ _AddDisplay(BScreen *screen)
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

ତାର୍କିକ HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    _AddDisplay(&screen);
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ଶୂନ୍ୟ HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    ଫେରନ୍ତୁ;
}


ତାର୍କିକ HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.Frame();
    rect->x = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)rc.ବାମ;
    rect->y = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)rc.ଶୀର୍ଷ;
    rect->w = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)rc.Width() + 1;
    rect->h = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)rc.Height() + 1;
    ଫେରନ୍ତୁ ସତ୍ୟ;
}

ତାର୍କିକ HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_DisplayMode mode;
    display_mode this_bmode;
    display_mode *bmodes;
    uint32 ଗଣନା_2, i;
    ତାର୍କିକ retval = ମିଥ୍ୟା;

    // Get graphics-hardware supported modes
    ଯଦି (bscreen.GetModeList(&bmodes, &ଗଣନା_2) == B_OK) {
        ଯଦି (bscreen.GetMode(&this_bmode) == B_OK) {
            ପାଇଁ (i = 0; i < ଗଣନା_2; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                ଯଦି (bmodes[i].space == this_bmode.space) {
                    _BDisplayModeToSdlDisplayMode(&bmodes[i], &mode);
                    SDL_AddFullscreenDisplayMode(display, &mode);
                }
            }
            retval = ସତ୍ୟ;
        }
        ମୁକ୍ତ(bmodes); // This should NOT be SDL_free()
    }

    ଫେରନ୍ତୁ retval;
}


ତାର୍କିକ HAIKU_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    // Get the current screen
    BScreen bscreen;
    ଯଦି (!bscreen.IsValid()) {
        ଫେରନ୍ତୁ SDL_SetError("Invalid screen");
    }

    // Set the mode using the driver data
    display_mode *bmode = _ExtractBMode(mode);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_mode *bmode_list;
    bscreen.GetModeList(&bmode_list, &c);
    ପାଇଁ (i = 0; i < c; ++i) {
        ଯଦି (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_width == bmode->virtual_width &&
            bmode_list[i].virtual_height == bmode->virtual_height ) {
                bmode = &bmode_list[i];
                ଭାଙ୍ଗ;
        }
    }

    ଯଦି (bscreen.SetMode(bmode) != B_OK) {
        ଫେରନ୍ତୁ SDL_SetError("Bad video mode");
    }

    ମୁକ୍ତ(bmode_list); // This should NOT be SDL_free()

#ifdef SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#endif

    ଫେରନ୍ତୁ ସତ୍ୟ;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
