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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_HAIKU

#समावेश <AppKit.h>
#समावेश <InterfaceKit.h>
#समावेश "SDL_bmodes.h"
#समावेश "SDL_BWin.h"

#अगर_घोषित SDL_VIDEO_OPENGL
#समावेश "SDL_bopengl.h"
#पूर्ण_अगर

#समावेश "../../core/haiku/SDL_BApp.h"

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर


#घोषणा WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#अगर WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
काष्ठा SDL_Display_Mode_तथ्य {
    display_mode *bmode;
};
#पूर्ण_अगर

अटल SDL_INLINE SDL_BWin *_ToBeWin(SDL_Window *window)
{
    वापस (SDL_BWin *)(window->internal);
}

अटल SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    वापस SDL_Looper;
}

अटल SDL_INLINE display_mode * _ExtractBMode(SDL_DisplayMode *mode)
{
#अगर WRAP_BMODE
    वापस mode->internal->bmode;
#अन्यथा
    वापस (display_mode *)mode->internal;
#पूर्ण_अगर
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
अटल व्योम get_refresh_rate(display_mode &mode, पूर्णांक *numerator, पूर्णांक *denominator)
{
    *numerator = (mode.timing.pixel_clock * 1000);
    *denominator = (mode.timing.h_योग * mode.timing.v_योग);
}


#अगर 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
व्योम Spout_Mode_तथ्य(display_mode *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_width, bmode->virtual_height);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_start,
            bmode->v_display_start);
    अगर (bmode->flags) {
        SDL_Log("\tFlags:");
        अगर (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        अगर (bmode->flags & B_8_BIT_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        अगर (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        अगर (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        अगर (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        अगर (bmode->flags & B_IO_FB_NA) {
            SDL_Log("\t\tB_IO_FB_NA");
        }
    }
    SDL_Log("\tTiming:");
    SDL_Log("\t\tpx clock: %i", bmode->timing.pixel_clock);
    SDL_Log("\t\th - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.h_display, bmode->timing.h_sync_start,
        bmode->timing.h_sync_end, bmode->timing.h_योग);
    SDL_Log("\t\tv - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.v_display, bmode->timing.v_sync_start,
        bmode->timing.v_sync_end, bmode->timing.v_योग);
    अगर (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        अगर (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        अगर (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        अगर (bmode->timing.flags & B_POSITIVE_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        अगर (bmode->timing.flags & B_POSITIVE_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        अगर (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#पूर्ण_अगर



SDL_PixelFormat HAIKU_ColorSpaceToSDLPxFormat(uint32 colorspace)
{
    चयन (colorspace) {
    हाल B_CMAP8:
        वापस SDL_PIXELFORMAT_INDEX8;
        अवरोध;
    हाल B_RGB15:
    हाल B_RGBA15:
    हाल B_RGB15_BIG:
    हाल B_RGBA15_BIG:
        वापस SDL_PIXELFORMAT_XRGB1555;
        अवरोध;
    हाल B_RGB16:
    हाल B_RGB16_BIG:
        वापस SDL_PIXELFORMAT_RGB565;
        अवरोध;
    हाल B_RGB24:
    हाल B_RGB24_BIG:
        वापस SDL_PIXELFORMAT_BGR24;
        अवरोध;
    हाल B_RGB32:
    हाल B_RGBA32:
    हाल B_RGB32_BIG:
    हाल B_RGBA32_BIG:
        वापस SDL_PIXELFORMAT_XRGB8888;
        अवरोध;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_SetError("Invalid color space");
    वापस SDL_PIXELFORMAT_UNKNOWN;
}

अटल व्योम _BDisplayModeToSdlDisplayMode(display_mode *bmode, SDL_DisplayMode *mode)
{
    SDL_zerop(mode);
    mode->w = bmode->virtual_width;
    mode->h = bmode->virtual_height;
    get_refresh_rate(*bmode, &mode->refresh_rate_numerator, &mode->refresh_rate_denominator);

#अगर WRAP_BMODE
    SDL_Display_Mode_तथ्य *तथ्य = (SDL_Display_Mode_तथ्य *)SDL_calloc(1, माप(SDL_Display_Mode_तथ्य));
    तथ्य->bmode = bmode;

    mode->internal = तथ्य;
#अन्यथा
    mode->internal = bmode;
#पूर्ण_अगर

    // Set the format
    mode->format = HAIKU_ColorSpaceToSDLPxFormat(bmode->space);
}

// Later, there may be more than one monitor available
अटल व्योम _AddDisplay(BScreen *screen)
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

bool HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    _AddDisplay(&screen);
    वापस true;
}

व्योम HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    वापस;
}


bool HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.Frame();
    rect->x = (पूर्णांक)rc.बाँए;
    rect->y = (पूर्णांक)rc.शीर्ष;
    rect->w = (पूर्णांक)rc.Width() + 1;
    rect->h = (पूर्णांक)rc.Height() + 1;
    वापस true;
}

bool HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_DisplayMode mode;
    display_mode this_bmode;
    display_mode *bmodes;
    uint32 गिनती, i;
    bool retval = false;

    // Get graphics-hardware supported modes
    अगर (bscreen.GetModeList(&bmodes, &गिनती) == B_OK) {
        अगर (bscreen.GetMode(&this_bmode) == B_OK) {
            क्रम (i = 0; i < गिनती; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                अगर (bmodes[i].space == this_bmode.space) {
                    _BDisplayModeToSdlDisplayMode(&bmodes[i], &mode);
                    SDL_AddFullscreenDisplayMode(display, &mode);
                }
            }
            retval = true;
        }
        मुक्त(bmodes); // This should NOT be SDL_free()
    }

    वापस retval;
}


bool HAIKU_SetDisplayMode(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
    // Get the current screen
    BScreen bscreen;
    अगर (!bscreen.IsValid()) {
        वापस SDL_SetError("Invalid screen");
    }

    // Set the mode using the driver data
    display_mode *bmode = _ExtractBMode(mode);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_mode *bmode_list;
    bscreen.GetModeList(&bmode_list, &c);
    क्रम (i = 0; i < c; ++i) {
        अगर (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_width == bmode->virtual_width &&
            bmode_list[i].virtual_height == bmode->virtual_height ) {
                bmode = &bmode_list[i];
                अवरोध;
        }
    }

    अगर (bscreen.SetMode(bmode) != B_OK) {
        वापस SDL_SetError("Bad video mode");
    }

    मुक्त(bmode_list); // This should NOT be SDL_free()

#अगर_घोषित SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#पूर्ण_अगर

    वापस true;
}

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर // SDL_VIDEO_DRIVER_HAIKU
