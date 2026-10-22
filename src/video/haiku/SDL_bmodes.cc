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

#ifdef SDL_VIDEO_DRIVER_HAIKU

#अन्तर्भाव <AppKit.h>
#अन्तर्भाव <InterfaceKit.h>
#अन्तर्भाव "SDL_bmodes.h"
#अन्तर्भाव "SDL_BWin.h"

#ifdef SDL_VIDEO_OPENGL
#अन्तर्भाव "SDL_bopengl.h"
#endif

#अन्तर्भाव "../../core/haiku/SDL_BApp.h"

#ifdef __cplusplus
बाह्य "C" {
#endif


#define WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#यदि WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
संरचना SDL_DisplayModeData {
    display_mode *bmode;
};
#endif

स्थिर SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    फर्काऊ (SDL_BWin *)(window->internal);
}

स्थिर SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    फर्काऊ SDL_Looper;
}

स्थिर SDL_INLINE display_mode * _ExtractBMode(SDL_DisplayMode *mode)
{
#यदि WRAP_BMODE
    फर्काऊ mode->internal->bmode;
#अन्यथा
    फर्काऊ (display_mode *)mode->internal;
#endif
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
स्थिर शून्य get_refresh_rate(display_mode &mode, पूर्णाङ्क *numerator, पूर्णाङ्क *denominator)
{
    *numerator = (mode.timing.pixel_clock * 1000);
    *denominator = (mode.timing.h_total * mode.timing.v_total);
}


#यदि 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
शून्य _SpoutModeData(display_mode *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_width, bmode->virtual_height);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_start,
            bmode->v_display_start);
    यदि (bmode->flags) {
        SDL_Log("\tFlags:");
        यदि (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        यदि (bmode->flags & B_8_BIT_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        यदि (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        यदि (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        यदि (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        यदि (bmode->flags & B_IO_FB_NA) {
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
    यदि (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        यदि (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        यदि (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        यदि (bmode->timing.flags & B_POSITIVE_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        यदि (bmode->timing.flags & B_POSITIVE_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        यदि (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#endif



SDL_PixelFormat HAIKU_ColorSpaceToSDLPxFormat(uint32 colorspace)
{
    विकल्प (colorspace) {
    पक्ष B_CMAP8:
        फर्काऊ SDL_PIXELFORMAT_INDEX8;
        रोक;
    पक्ष B_RGB15:
    पक्ष B_RGBA15:
    पक्ष B_RGB15_BIG:
    पक्ष B_RGBA15_BIG:
        फर्काऊ SDL_PIXELFORMAT_XRGB1555;
        रोक;
    पक्ष B_RGB16:
    पक्ष B_RGB16_BIG:
        फर्काऊ SDL_PIXELFORMAT_RGB565;
        रोक;
    पक्ष B_RGB24:
    पक्ष B_RGB24_BIG:
        फर्काऊ SDL_PIXELFORMAT_BGR24;
        रोक;
    पक्ष B_RGB32:
    पक्ष B_RGBA32:
    पक्ष B_RGB32_BIG:
    पक्ष B_RGBA32_BIG:
        फर्काऊ SDL_PIXELFORMAT_XRGB8888;
        रोक;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_SetError("Invalid color space");
    फर्काऊ SDL_PIXELFORMAT_UNKNOWN;
}

स्थिर शून्य _BDisplayModeToSdlDisplayMode(display_mode *bmode, SDL_DisplayMode *mode)
{
    SDL_zerop(mode);
    mode->w = bmode->virtual_width;
    mode->h = bmode->virtual_height;
    get_refresh_rate(*bmode, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);

#यदि WRAP_BMODE
    SDL_DisplayModeData *data = (SDL_DisplayModeData *)SDL_calloc(1, परिमाण(SDL_DisplayModeData));
    data->bmode = bmode;

    mode->internal = data;
#अन्यथा
    mode->internal = bmode;
#endif

    // Set the format
    mode->format = HAIKU_ColorSpaceToSDLPxFormat(bmode->space);
}

// Later, there may be more than one monitor available
स्थिर शून्य _AddDisplay(BScreen *screen)
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

तार्किक HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    _AddDisplay(&screen);
    फर्काऊ सत्य;
}

शून्य HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    फर्काऊ;
}


तार्किक HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.Frame();
    rect->x = (पूर्णाङ्क)rc.बायाँ;
    rect->y = (पूर्णाङ्क)rc.शीर्ष;
    rect->w = (पूर्णाङ्क)rc.Width() + 1;
    rect->h = (पूर्णाङ्क)rc.Height() + 1;
    फर्काऊ सत्य;
}

तार्किक HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_DisplayMode mode;
    display_mode this_bmode;
    display_mode *bmodes;
    uint32 गन्ती, i;
    तार्किक retval = असत्य;

    // Get graphics-hardware supported modes
    यदि (bscreen.GetModeList(&bmodes, &गन्ती) == B_OK) {
        यदि (bscreen.GetMode(&this_bmode) == B_OK) {
            लागि (i = 0; i < गन्ती; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                यदि (bmodes[i].space == this_bmode.space) {
                    _BDisplayModeToSdlDisplayMode(&bmodes[i], &mode);
                    SDL_AddFullscreenDisplayMode(display, &mode);
                }
            }
            retval = सत्य;
        }
        मुक्त(bmodes); // This should NOT be SDL_free()
    }

    फर्काऊ retval;
}


तार्किक HAIKU_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    // Get the current screen
    BScreen bscreen;
    यदि (!bscreen.IsValid()) {
        फर्काऊ SDL_SetError("Invalid screen");
    }

    // Set the mode using the driver data
    display_mode *bmode = _ExtractBMode(mode);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_mode *bmode_list;
    bscreen.GetModeList(&bmode_list, &c);
    लागि (i = 0; i < c; ++i) {
        यदि (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_width == bmode->virtual_width &&
            bmode_list[i].virtual_height == bmode->virtual_height ) {
                bmode = &bmode_list[i];
                रोक;
        }
    }

    यदि (bscreen.SetMode(bmode) != B_OK) {
        फर्काऊ SDL_SetError("Bad video mode");
    }

    मुक्त(bmode_list); // This should NOT be SDL_free()

#ifdef SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#endif

    फर्काऊ सत्य;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU
