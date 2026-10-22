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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#அந்தர்பாவ <AppKit.h>
#அந்தர்பாவ <InterfaceKit.h>
#அந்தர்பாவ "SDL_bmodes.h"
#அந்தர்பாவ "SDL_BWin.h"

#ifdef SDL_VIDEO_OPENGL
#அந்தர்பாவ "SDL_bopengl.h"
#endif

#அந்தர்பாவ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
வெளி "C" {
#endif


#define WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#எனில் WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
கட்டமைப்பு SDL_DisplayModeData {
    display_mode *bmode;
};
#endif

நிலையான SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    திரும்பு (SDL_BWin *)(window->internal);
}

நிலையான SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    திரும்பு SDL_Looper;
}

நிலையான SDL_INLINE display_mode * _ExtractBMode(SDL_DisplayMode *mode)
{
#எனில் WRAP_BMODE
    திரும்பு mode->internal->bmode;
#இல்லையெனில்
    திரும்பு (display_mode *)mode->internal;
#endif
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
நிலையான வெறுமை get_refresh_rate(display_mode &mode, முழு *numerator, முழு *denominator)
{
    *numerator = (mode.timing.pixel_clock * 1000);
    *denominator = (mode.timing.h_total * mode.timing.v_total);
}


#எனில் 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
வெறுமை _SpoutModeData(display_mode *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_width, bmode->virtual_height);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_start,
            bmode->v_display_start);
    எனில் (bmode->flags) {
        SDL_Log("\tFlags:");
        எனில் (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        எனில் (bmode->flags & B_8_BIT_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        எனில் (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        எனில் (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        எனில் (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        எனில் (bmode->flags & B_IO_FB_NA) {
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
    எனில் (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        எனில் (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        எனில் (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        எனில் (bmode->timing.flags & B_POSITIVE_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        எனில் (bmode->timing.flags & B_POSITIVE_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        எனில் (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#endif



SDL_PixelFormat HAIKU_ColorSpaceToSDLPxFormat(uint32 colorspace)
{
    தேர்வு (colorspace) {
    நிலை B_CMAP8:
        திரும்பு SDL_PIXELFORMAT_INDEX8;
        நிறுத்து;
    நிலை B_RGB15:
    நிலை B_RGBA15:
    நிலை B_RGB15_BIG:
    நிலை B_RGBA15_BIG:
        திரும்பு SDL_PIXELFORMAT_XRGB1555;
        நிறுத்து;
    நிலை B_RGB16:
    நிலை B_RGB16_BIG:
        திரும்பு SDL_PIXELFORMAT_RGB565;
        நிறுத்து;
    நிலை B_RGB24:
    நிலை B_RGB24_BIG:
        திரும்பு SDL_PIXELFORMAT_BGR24;
        நிறுத்து;
    நிலை B_RGB32:
    நிலை B_RGBA32:
    நிலை B_RGB32_BIG:
    நிலை B_RGBA32_BIG:
        திரும்பு SDL_PIXELFORMAT_XRGB8888;
        நிறுத்து;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_SetError("Invalid color space");
    திரும்பு SDL_PIXELFORMAT_UNKNOWN;
}

நிலையான வெறுமை _BDisplayModeToSdlDisplayMode(display_mode *bmode, SDL_DisplayMode *mode)
{
    SDL_zerop(mode);
    mode->w = bmode->virtual_width;
    mode->h = bmode->virtual_height;
    get_refresh_rate(*bmode, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);

#எனில் WRAP_BMODE
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)SDL_calloc(1, அளவு(SDL_DisplayModeData));
    data->bmode = bmode;

    mode->internal = data;
#இல்லையெனில்
    mode->internal = bmode;
#endif

    // Set the format
    mode->format = HAIKU_ColorSpaceToSDLPxFormat(bmode->space);
}

// Later, there may be more than one monitor available
நிலையான வெறுமை _AddDisplay(BScreen *screen)
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

தருக்க HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    _AddDisplay(&screen);
    திரும்பு உண்மை;
}

வெறுமை HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    திரும்பு;
}


தருக்க HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.Frame();
    rect->x = (முழு)rc.இடது;
    rect->y = (முழு)rc.உச்சி;
    rect->w = (முழு)rc.Width() + 1;
    rect->h = (முழு)rc.Height() + 1;
    திரும்பு உண்மை;
}

தருக்க HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_DisplayMode mode;
    display_mode this_bmode;
    display_mode *bmodes;
    uint32 மொத்தம், i;
    தருக்க retval = பொய்;

    // Get graphics-hardware supported modes
    எனில் (bscreen.GetModeList(&bmodes, &மொத்தம்) == B_OK) {
        எனில் (bscreen.GetMode(&this_bmode) == B_OK) {
            க்கு (i = 0; i < மொத்தம்; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                எனில் (bmodes[i].space == this_bmode.space) {
                    _BDisplayModeToSdlDisplayMode(&bmodes[i], &mode);
                    SDL_AddFullscreenDisplayMode(display, &mode);
                }
            }
            retval = உண்மை;
        }
        விடுவி(bmodes); // This should NOT be SDL_free()
    }

    திரும்பு retval;
}


தருக்க HAIKU_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    // Get the current screen
    BScreen bscreen;
    எனில் (!bscreen.IsValid()) {
        திரும்பு SDL_SetError("Invalid screen");
    }

    // Set the mode using the driver data
    display_mode *bmode = _ExtractBMode(mode);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_mode *bmode_list;
    bscreen.GetModeList(&bmode_list, &c);
    க்கு (i = 0; i < c; ++i) {
        எனில் (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_width == bmode->virtual_width &&
            bmode_list[i].virtual_height == bmode->virtual_height ) {
                bmode = &bmode_list[i];
                நிறுத்து;
        }
    }

    எனில் (bscreen.SetMode(bmode) != B_OK) {
        திரும்பு SDL_SetError("Bad video mode");
    }

    விடுவி(bmode_list); // This should NOT be SDL_free()

#ifdef SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#endif

    திரும்பு உண்மை;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
