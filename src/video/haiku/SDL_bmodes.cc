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

#ifdef SDL_VIDEO_DRIVER_HAIKU

#ಅನ್ತರ್ಭಾವ <AppKit.h>
#ಅನ್ತರ್ಭಾವ <InterfaceKit.h>
#ಅನ್ತರ್ಭಾವ "SDL_bmodes.h"
#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"

#ifdef SDL_VIDEO_OPENGL
#ಅನ್ತರ್ಭಾವ "SDL_bopengl.h"
#endif

#ಅನ್ತರ್ಭಾವ "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
ಬಾಹ್ಯ "C" {
#endif


#define WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#ಯದಿ WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
ಸಂರಚನಾ SDL_DisplayModeData {
    display_mode *bmode;
};
#endif

ಸ್ಥಿರ SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    ಪ್ರತ್ಯಾಗಮ (SDL_BWin *)(window->internal);
}

ಸ್ಥಿರ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ಪ್ರತ್ಯಾಗಮ SDL_Looper;
}

ಸ್ಥಿರ SDL_INLINE display_mode * _ExtractBMode(SDL_DisplayMode *mode)
{
#ಯದಿ WRAP_BMODE
    ಪ್ರತ್ಯಾಗಮ mode->internal->bmode;
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ (display_mode *)mode->internal;
#endif
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
ಸ್ಥಿರ ಶೂನ್ಯ get_refresh_rate(display_mode &mode, ಪೂರ್ಣಾಙ್ಕ *numerator, ಪೂರ್ಣಾಙ್ಕ *denominator)
{
    *numerator = (mode.timing.pixel_clock * 1000);
    *denominator = (mode.timing.h_total * mode.timing.v_total);
}


#ಯದಿ 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
ಶೂನ್ಯ _SpoutModeData(display_mode *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_width, bmode->virtual_height);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_start,
            bmode->v_display_start);
    ಯದಿ (bmode->flags) {
        SDL_Log("\tFlags:");
        ಯದಿ (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        ಯದಿ (bmode->flags & B_8_BIT_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        ಯದಿ (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        ಯದಿ (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        ಯದಿ (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        ಯದಿ (bmode->flags & B_IO_FB_NA) {
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
    ಯದಿ (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        ಯದಿ (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        ಯದಿ (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        ಯದಿ (bmode->timing.flags & B_POSITIVE_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        ಯದಿ (bmode->timing.flags & B_POSITIVE_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        ಯದಿ (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#endif



SDL_PixelFormat HAIKU_ColorSpaceToSDLPxFormat(uint32 colorspace)
{
    ವಿಕಲ್ಪ (colorspace) {
    ಪಕ್ಷ B_CMAP8:
        ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_INDEX8;
        ಭಙ್ಗ;
    ಪಕ್ಷ B_RGB15:
    ಪಕ್ಷ B_RGBA15:
    ಪಕ್ಷ B_RGB15_BIG:
    ಪಕ್ಷ B_RGBA15_BIG:
        ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_XRGB1555;
        ಭಙ್ಗ;
    ಪಕ್ಷ B_RGB16:
    ಪಕ್ಷ B_RGB16_BIG:
        ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_RGB565;
        ಭಙ್ಗ;
    ಪಕ್ಷ B_RGB24:
    ಪಕ್ಷ B_RGB24_BIG:
        ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_BGR24;
        ಭಙ್ಗ;
    ಪಕ್ಷ B_RGB32:
    ಪಕ್ಷ B_RGBA32:
    ಪಕ್ಷ B_RGB32_BIG:
    ಪಕ್ಷ B_RGBA32_BIG:
        ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_XRGB8888;
        ಭಙ್ಗ;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_SetError("Invalid color space");
    ಪ್ರತ್ಯಾಗಮ SDL_PIXELFORMAT_UNKNOWN;
}

ಸ್ಥಿರ ಶೂನ್ಯ _BDisplayModeToSdlDisplayMode(display_mode *bmode, SDL_DisplayMode *mode)
{
    SDL_zerop(mode);
    mode->w = bmode->virtual_width;
    mode->h = bmode->virtual_height;
    get_refresh_rate(*bmode, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);

#ಯದಿ WRAP_BMODE
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)SDL_calloc(1, ಪರಿಮಾಣ(SDL_DisplayModeData));
    data->bmode = bmode;

    mode->internal = data;
#ಅನ್ಯಥಾ
    mode->internal = bmode;
#endif

    // Set the format
    mode->format = HAIKU_ColorSpaceToSDLPxFormat(bmode->space);
}

// Later, there may be more than one monitor available
ಸ್ಥಿರ ಶೂನ್ಯ _AddDisplay(BScreen *screen)
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

ತಾರ್ಕಿಕ HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    _AddDisplay(&screen);
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಶೂನ್ಯ HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    ಪ್ರತ್ಯಾಗಮ;
}


ತಾರ್ಕಿಕ HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.Frame();
    rect->x = (ಪೂರ್ಣಾಙ್ಕ)rc.ಎಡ;
    rect->y = (ಪೂರ್ಣಾಙ್ಕ)rc.ತುದಿ;
    rect->w = (ಪೂರ್ಣಾಙ್ಕ)rc.Width() + 1;
    rect->h = (ಪೂರ್ಣಾಙ್ಕ)rc.Height() + 1;
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ತಾರ್ಕಿಕ HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_DisplayMode mode;
    display_mode this_bmode;
    display_mode *bmodes;
    uint32 ಎಣಿಕೆ, i;
    ತಾರ್ಕಿಕ retval = ಅಸತ್ಯ;

    // Get graphics-hardware supported modes
    ಯದಿ (bscreen.GetModeList(&bmodes, &ಎಣಿಕೆ) == B_OK) {
        ಯದಿ (bscreen.GetMode(&this_bmode) == B_OK) {
            ಪ್ರತಿ (i = 0; i < ಎಣಿಕೆ; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                ಯದಿ (bmodes[i].space == this_bmode.space) {
                    _BDisplayModeToSdlDisplayMode(&bmodes[i], &mode);
                    SDL_AddFullscreenDisplayMode(display, &mode);
                }
            }
            retval = ಸತ್ಯ;
        }
        ಮುಕ್ತ(bmodes); // This should NOT be SDL_free()
    }

    ಪ್ರತ್ಯಾಗಮ retval;
}


ತಾರ್ಕಿಕ HAIKU_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    // Get the current screen
    BScreen bscreen;
    ಯದಿ (!bscreen.IsValid()) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Invalid screen");
    }

    // Set the mode using the driver data
    display_mode *bmode = _ExtractBMode(mode);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_mode *bmode_list;
    bscreen.GetModeList(&bmode_list, &c);
    ಪ್ರತಿ (i = 0; i < c; ++i) {
        ಯದಿ (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_width == bmode->virtual_width &&
            bmode_list[i].virtual_height == bmode->virtual_height ) {
                bmode = &bmode_list[i];
                ಭಙ್ಗ;
        }
    }

    ಯದಿ (bscreen.SetMode(bmode) != B_OK) {
        ಪ್ರತ್ಯಾಗಮ SDL_SetError("Bad video mode");
    }

    ಮುಕ್ತ(bmode_list); // This should NOT be SDL_free()

#ifdef SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#endif

    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
