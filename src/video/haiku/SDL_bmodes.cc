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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_HAIKU

#ಅನ್ತರ್ಭಾವ <AppKit.h>
#ಅನ್ತರ್ಭಾವ <InterfaceKit.h>
#ಅನ್ತರ್ಭಾವ "SDL_bmodes.h"
#ಅನ್ತರ್ಭಾವ "SDL_BWin.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
#ಅನ್ತರ್ಭಾವ "SDL_bopengl.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "../../core/haiku/SDL_BApp.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ


#ವ್ಯಾಖ್ಯಾನಿಸು WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#ಆದರೆ WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
ರಚನೆ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ {
    display_ಬಹುಲಕ_2 *bmode;
};
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ SDL_INLINE SDL_BWin *ಗಮ್ಯ_Be_Win(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಹಿಂತಿರುಗಿ (SDL_BWin *)(ಕಿಟಕಿ->ಆಂತರಿಕ);
}

ಸ್ಥಿರ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ಹಿಂತಿರುಗಿ SDL_Looper;
}

ಸ್ಥಿರ SDL_INLINE display_ಬಹುಲಕ_2 * ಹೊರತೆಗೆ_BMode(SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
#ಆದರೆ WRAP_BMODE
    ಹಿಂತಿರುಗಿ ಬಹುಲಕ->ಆಂತರಿಕ->bmode;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ (display_ಬಹುಲಕ_2 *)ಬಹುಲಕ->ಆಂತರಿಕ;
#ಆದರೆ_ಅಂತ್ಯ
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
ಸ್ಥಿರ ಶೂನ್ಯ get_refresh_ದರ(display_ಬಹುಲಕ_2 &ಬಹುಲಕ, ಪೂರ್ಣಾಂಕ *numerator, ಪೂರ್ಣಾಂಕ *denominator)
{
    *numerator = (ಬಹುಲಕ.timing.pixel_clock * 1000);
    *denominator = (ಬಹುಲಕ.timing.h_ಒಟ್ಟು * ಬಹುಲಕ.timing.v_ಒಟ್ಟು);
}


#ಆದರೆ 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
ಶೂನ್ಯ Spout_ಬಹುಲಕ_ದತ್ತಾಂಶ(display_ಬಹುಲಕ_2 *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_ಅಗಲ, bmode->virtual_ಎತ್ತರ);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_ಆರಂಭ,
            bmode->v_display_ಆರಂಭ);
    ಆದರೆ (bmode->flags) {
        SDL_Log("\tFlags:");
        ಆದರೆ (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        ಆದರೆ (bmode->flags & B_8_ಬಿಟ್_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        ಆದರೆ (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        ಆದರೆ (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        ಆದರೆ (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        ಆದರೆ (bmode->flags & B_IO_FB_NA) {
            SDL_Log("\t\tB_IO_FB_NA");
        }
    }
    SDL_Log("\tTiming:");
    SDL_Log("\t\tpx clock: %i", bmode->timing.pixel_clock);
    SDL_Log("\t\th - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.h_display, bmode->timing.h_sync_ಆರಂಭ,
        bmode->timing.h_sync_ಕೊನೆ, bmode->timing.h_ಒಟ್ಟು);
    SDL_Log("\t\tv - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.v_display, bmode->timing.v_sync_ಆರಂಭ,
        bmode->timing.v_sync_ಕೊನೆ, bmode->timing.v_ಒಟ್ಟು);
    ಆದರೆ (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        ಆದರೆ (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        ಆದರೆ (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        ಆದರೆ (bmode->timing.flags & B_ಧನಾತ್ಮಕ_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        ಆದರೆ (bmode->timing.flags & B_ಧನಾತ್ಮಕ_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        ಆದರೆ (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#ಆದರೆ_ಅಂತ್ಯ



SDL_PixelFormat HAIKU_Color_Space_ಗಮ್ಯ_SDLPx_Format(uint32 colorspace)
{
    ಆಯ್ಕೆ (colorspace) {
    ಸ್ಥಿತಿ B_CMAP8:
        ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_INDEX8;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ B_RGB15:
    ಸ್ಥಿತಿ B_RGBA15:
    ಸ್ಥಿತಿ B_RGB15_BIG:
    ಸ್ಥಿತಿ B_RGBA15_BIG:
        ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XRGB1555;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ B_RGB16:
    ಸ್ಥಿತಿ B_RGB16_BIG:
        ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_RGB565;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ B_RGB24:
    ಸ್ಥಿತಿ B_RGB24_BIG:
        ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_BGR24;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ B_RGB32:
    ಸ್ಥಿತಿ B_RGBA32:
    ಸ್ಥಿತಿ B_RGB32_BIG:
    ಸ್ಥಿತಿ B_RGBA32_BIG:
        ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XRGB8888;
        ನಿಲ್ಲಿಸು;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_ಗಣ_Error("Invalid color space");
    ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_UNKNOWN;
}

ಸ್ಥಿರ ಶೂನ್ಯ BDisplay_ಬಹುಲಕ_ಗಮ್ಯ_Sdl_Display_ಬಹುಲಕ(display_ಬಹುಲಕ_2 *bmode, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    SDL_zerop(ಬಹುಲಕ);
    ಬಹುಲಕ->w = bmode->virtual_ಅಗಲ;
    ಬಹುಲಕ->h = bmode->virtual_ಎತ್ತರ;
    get_refresh_ದರ(*bmode, &ಬಹುಲಕ->refresh_ದರ_numerator, &ಬಹುಲಕ->refresh_ದರ_denominator);

#ಆದರೆ WRAP_BMODE
    SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ));
    ದತ್ತಾಂಶ->bmode = bmode;

    ಬಹುಲಕ->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
#ಇಲ್ಲದಿದ್ದರೆ
    ಬಹುಲಕ->ಆಂತರಿಕ = bmode;
#ಆದರೆ_ಅಂತ್ಯ

    // Set the format
    ಬಹುಲಕ->format = HAIKU_Color_Space_ಗಮ್ಯ_SDLPx_Format(bmode->space);
}

// Later, there may be more than one monitor available
ಸ್ಥಿರ ಶೂನ್ಯ ಕೂಡಿಸು_Display(BScreen *screen)
{
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    display_ಬಹುಲಕ_2 bmode;
    screen->Get_ಬಹುಲಕ(&bmode);

    BDisplay_ಬಹುಲಕ_ಗಮ್ಯ_Sdl_Display_ಬಹುಲಕ(&bmode, &ಬಹುಲಕ);

    SDL_ಕೂಡಿಸು_Basic_Video_Display(&ಬಹುಲಕ);
}

/*
 * Functions called by SDL
 */

ತಾರ್ಕಿಕ HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    ಕೂಡಿಸು_Display(&screen);
    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ಶೂನ್ಯ HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    ಹಿಂತಿರುಗಿ;
}


ತಾರ್ಕಿಕ HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.ಚೌಕಟ್ಟು_2();
    rect->x = (ಪೂರ್ಣಾಂಕ)rc.ಎಡ;
    rect->y = (ಪೂರ್ಣಾಂಕ)rc.ತುದಿ;
    rect->w = (ಪೂರ್ಣಾಂಕ)rc.ಅಗಲ_2() + 1;
    rect->h = (ಪೂರ್ಣಾಂಕ)rc.ಎತ್ತರ_2() + 1;
    ಹಿಂತಿರುಗಿ ನಿಜ;
}

ತಾರ್ಕಿಕ HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_Display_ಬಹುಲಕ ಬಹುಲಕ;
    display_ಬಹುಲಕ_2 this_bmode;
    display_ಬಹುಲಕ_2 *bmodes;
    uint32 ಎಣಿಕೆ_2, i;
    ತಾರ್ಕಿಕ retval = ಸುಳ್ಳು;

    // Get graphics-hardware supported modes
    ಆದರೆ (bscreen.Get_ಬಹುಲಕ_List(&bmodes, &ಎಣಿಕೆ_2) == B_OK) {
        ಆದರೆ (bscreen.Get_ಬಹುಲಕ(&this_bmode) == B_OK) {
            ಗಾಗಿ (i = 0; i < ಎಣಿಕೆ_2; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                ಆದರೆ (bmodes[i].space == this_bmode.space) {
                    BDisplay_ಬಹುಲಕ_ಗಮ್ಯ_Sdl_Display_ಬಹುಲಕ(&bmodes[i], &ಬಹುಲಕ);
                    SDL_ಕೂಡಿಸು_Fullscreen_Display_ಬಹುಲಕ(display, &ಬಹುಲಕ);
                }
            }
            retval = ನಿಜ;
        }
        ಬಿಡುಗಡೆ(bmodes); // This should NOT be SDL_free()
    }

    ಹಿಂತಿರುಗಿ retval;
}


ತಾರ್ಕಿಕ HAIKU_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ)
{
    // Get the current screen
    BScreen bscreen;
    ಆದರೆ (!bscreen.IsValid()) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Invalid screen");
    }

    // Set the mode using the driver data
    display_ಬಹುಲಕ_2 *bmode = ಹೊರತೆಗೆ_BMode(ಬಹುಲಕ);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_ಬಹುಲಕ_2 *bmode_list;
    bscreen.Get_ಬಹುಲಕ_List(&bmode_list, &c);
    ಗಾಗಿ (i = 0; i < c; ++i) {
        ಆದರೆ (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_ಅಗಲ == bmode->virtual_ಅಗಲ &&
            bmode_list[i].virtual_ಎತ್ತರ == bmode->virtual_ಎತ್ತರ ) {
                bmode = &bmode_list[i];
                ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (bscreen.ಗಣ_ಬಹುಲಕ(bmode) != B_OK) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Bad video mode");
    }

    ಬಿಡುಗಡೆ(bmode_list); // This should NOT be SDL_free()

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ ನಿಜ;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_HAIKU
