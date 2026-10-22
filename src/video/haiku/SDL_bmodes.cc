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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_HAIKU

#અન્તર્ભાવ <AppKit.h>
#અન્તર્ભાવ <InterfaceKit.h>
#અન્તર્ભાવ "SDL_bmodes.h"
#અન્તર્ભાવ "SDL_BWin.h"

#ifdef SDL_VIDEO_OPENGL
#અન્તર્ભાવ "SDL_bopengl.h"
#endif

#અન્તર્ભાવ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
બાહ્ય "C" {
#endif


#define WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#જો WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
સંરચના SDL_DisplayModeData {
    display_mode *bmode;
};
#endif

સ્થિર SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    પાછા (SDL_BWin *)(window->internal);
}

સ્થિર SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    પાછા SDL_Looper;
}

સ્થિર SDL_INLINE display_mode * _ExtractBMode(SDL_DisplayMode *mode)
{
#જો WRAP_BMODE
    પાછા mode->internal->bmode;
#નહીંતર
    પાછા (display_mode *)mode->internal;
#endif
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
સ્થિર શૂન્ય get_refresh_rate(display_mode &mode, પૂર્ણાંક *numerator, પૂર્ણાંક *denominator)
{
    *numerator = (mode.timing.pixel_clock * 1000);
    *denominator = (mode.timing.h_total * mode.timing.v_total);
}


#જો 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
શૂન્ય _SpoutModeData(display_mode *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_width, bmode->virtual_height);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_start,
            bmode->v_display_start);
    જો (bmode->flags) {
        SDL_Log("\tFlags:");
        જો (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        જો (bmode->flags & B_8_BIT_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        જો (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        જો (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        જો (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        જો (bmode->flags & B_IO_FB_NA) {
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
    જો (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        જો (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        જો (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        જો (bmode->timing.flags & B_POSITIVE_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        જો (bmode->timing.flags & B_POSITIVE_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        જો (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#endif



SDL_PixelFormat HAIKU_ColorSpaceToSDLPxFormat(uint32 colorspace)
{
    પસંદગી (colorspace) {
    સ્થિતિ B_CMAP8:
        પાછા SDL_PIXELFORMAT_INDEX8;
        તોડો;
    સ્થિતિ B_RGB15:
    સ્થિતિ B_RGBA15:
    સ્થિતિ B_RGB15_BIG:
    સ્થિતિ B_RGBA15_BIG:
        પાછા SDL_PIXELFORMAT_XRGB1555;
        તોડો;
    સ્થિતિ B_RGB16:
    સ્થિતિ B_RGB16_BIG:
        પાછા SDL_PIXELFORMAT_RGB565;
        તોડો;
    સ્થિતિ B_RGB24:
    સ્થિતિ B_RGB24_BIG:
        પાછા SDL_PIXELFORMAT_BGR24;
        તોડો;
    સ્થિતિ B_RGB32:
    સ્થિતિ B_RGBA32:
    સ્થિતિ B_RGB32_BIG:
    સ્થિતિ B_RGBA32_BIG:
        પાછા SDL_PIXELFORMAT_XRGB8888;
        તોડો;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_SetError("Invalid color space");
    પાછા SDL_PIXELFORMAT_UNKNOWN;
}

સ્થિર શૂન્ય _BDisplayModeToSdlDisplayMode(display_mode *bmode, SDL_DisplayMode *mode)
{
    SDL_zerop(mode);
    mode->w = bmode->virtual_width;
    mode->h = bmode->virtual_height;
    get_refresh_rate(*bmode, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);

#જો WRAP_BMODE
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)SDL_calloc(1, કદ(SDL_DisplayModeData));
    data->bmode = bmode;

    mode->internal = data;
#નહીંતર
    mode->internal = bmode;
#endif

    // Set the format
    mode->format = HAIKU_ColorSpaceToSDLPxFormat(bmode->space);
}

// Later, there may be more than one monitor available
સ્થિર શૂન્ય _AddDisplay(BScreen *screen)
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

તાર્કિક HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    _AddDisplay(&screen);
    પાછા સાચું;
}

શૂન્ય HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    પાછા;
}


તાર્કિક HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.Frame();
    rect->x = (પૂર્ણાંક)rc.ડાબું;
    rect->y = (પૂર્ણાંક)rc.ટોચ;
    rect->w = (પૂર્ણાંક)rc.Width() + 1;
    rect->h = (પૂર્ણાંક)rc.Height() + 1;
    પાછા સાચું;
}

તાર્કિક HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_DisplayMode mode;
    display_mode this_bmode;
    display_mode *bmodes;
    uint32 ગણતરી, i;
    તાર્કિક retval = ખોટું;

    // Get graphics-hardware supported modes
    જો (bscreen.GetModeList(&bmodes, &ગણતરી) == B_OK) {
        જો (bscreen.GetMode(&this_bmode) == B_OK) {
            માટે (i = 0; i < ગણતરી; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                જો (bmodes[i].space == this_bmode.space) {
                    _BDisplayModeToSdlDisplayMode(&bmodes[i], &mode);
                    SDL_AddFullscreenDisplayMode(display, &mode);
                }
            }
            retval = સાચું;
        }
        મુક્ત(bmodes); // This should NOT be SDL_free()
    }

    પાછા retval;
}


તાર્કિક HAIKU_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    // Get the current screen
    BScreen bscreen;
    જો (!bscreen.IsValid()) {
        પાછા SDL_SetError("Invalid screen");
    }

    // Set the mode using the driver data
    display_mode *bmode = _ExtractBMode(mode);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_mode *bmode_list;
    bscreen.GetModeList(&bmode_list, &c);
    માટે (i = 0; i < c; ++i) {
        જો (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_width == bmode->virtual_width &&
            bmode_list[i].virtual_height == bmode->virtual_height ) {
                bmode = &bmode_list[i];
                તોડો;
        }
    }

    જો (bscreen.SetMode(bmode) != B_OK) {
        પાછા SDL_SetError("Bad video mode");
    }

    મુક્ત(bmode_list); // This should NOT be SDL_free()

#ifdef SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#endif

    પાછા સાચું;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
