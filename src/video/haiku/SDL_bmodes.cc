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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_HAIKU

#అన్తర్భావ <AppKit.h>
#అన్తర్భావ <InterfaceKit.h>
#అన్తర్భావ "SDL_bmodes.h"
#అన్తర్భావ "SDL_BWin.h"

#నిర్వచితమైతే SDL_VIDEO_OPENGL
#అన్తర్భావ "SDL_bopengl.h"
#అయితే_ముగింపు

#అన్తర్భావ "../../core/haiku/SDL_BApp.h"

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు


#నిర్వచించు WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#ఒకవేళ WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
నిర్మాణం SDL_Display_బహుళకం_దత్తాంశం {
    display_బహుళకం_2 *bmode;
};
#అయితే_ముగింపు

స్థిర SDL_INLINE SDL_BWin *గమ్యం_Be_Win(SDL_కిటికీ *కిటికీ)
{
    తిరిగి (SDL_BWin *)(కిటికీ->అంతర్గత);
}

స్థిర SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    తిరిగి SDL_Looper;
}

స్థిర SDL_INLINE display_బహుళకం_2 * వెలికితీయి_BMode(SDL_Display_బహుళకం *బహుళకం)
{
#ఒకవేళ WRAP_BMODE
    తిరిగి బహుళకం->అంతర్గత->bmode;
#లేకపోతే
    తిరిగి (display_బహుళకం_2 *)బహుళకం->అంతర్గత;
#అయితే_ముగింపు
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
స్థిర శూన్య get_refresh_రేటు(display_బహుళకం_2 &బహుళకం, పూర్ణాంకం *numerator, పూర్ణాంకం *denominator)
{
    *numerator = (బహుళకం.timing.pixel_clock * 1000);
    *denominator = (బహుళకం.timing.h_మొత్తం * బహుళకం.timing.v_మొత్తం);
}


#ఒకవేళ 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
శూన్య Spout_బహుళకం_దత్తాంశం(display_బహుళకం_2 *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_వెడల్పు, bmode->virtual_ఎత్తు);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_ప్రారంభం,
            bmode->v_display_ప్రారంభం);
    ఒకవేళ (bmode->flags) {
        SDL_Log("\tFlags:");
        ఒకవేళ (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        ఒకవేళ (bmode->flags & B_8_బిట్టు_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        ఒకవేళ (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        ఒకవేళ (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        ఒకవేళ (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        ఒకవేళ (bmode->flags & B_IO_FB_NA) {
            SDL_Log("\t\tB_IO_FB_NA");
        }
    }
    SDL_Log("\tTiming:");
    SDL_Log("\t\tpx clock: %i", bmode->timing.pixel_clock);
    SDL_Log("\t\th - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.h_display, bmode->timing.h_sync_ప్రారంభం,
        bmode->timing.h_sync_చివర, bmode->timing.h_మొత్తం);
    SDL_Log("\t\tv - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.v_display, bmode->timing.v_sync_ప్రారంభం,
        bmode->timing.v_sync_చివర, bmode->timing.v_మొత్తం);
    ఒకవేళ (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        ఒకవేళ (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        ఒకవేళ (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        ఒకవేళ (bmode->timing.flags & B_ధనాత్మక_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        ఒకవేళ (bmode->timing.flags & B_ధనాత్మక_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        ఒకవేళ (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#అయితే_ముగింపు



SDL_PixelFormat HAIKU_Color_Space_గమ్యం_SDLPx_Format(uint32 colorspace)
{
    ఎంపిక (colorspace) {
    స్థితి B_CMAP8:
        తిరిగి SDL_PIXELFORMAT_INDEX8;
        ఆపు;
    స్థితి B_RGB15:
    స్థితి B_RGBA15:
    స్థితి B_RGB15_BIG:
    స్థితి B_RGBA15_BIG:
        తిరిగి SDL_PIXELFORMAT_XRGB1555;
        ఆపు;
    స్థితి B_RGB16:
    స్థితి B_RGB16_BIG:
        తిరిగి SDL_PIXELFORMAT_RGB565;
        ఆపు;
    స్థితి B_RGB24:
    స్థితి B_RGB24_BIG:
        తిరిగి SDL_PIXELFORMAT_BGR24;
        ఆపు;
    స్థితి B_RGB32:
    స్థితి B_RGBA32:
    స్థితి B_RGB32_BIG:
    స్థితి B_RGBA32_BIG:
        తిరిగి SDL_PIXELFORMAT_XRGB8888;
        ఆపు;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_సమితి_Error("Invalid color space");
    తిరిగి SDL_PIXELFORMAT_UNKNOWN;
}

స్థిర శూన్య BDisplay_బహుళకం_గమ్యం_Sdl_Display_బహుళకం(display_బహుళకం_2 *bmode, SDL_Display_బహుళకం *బహుళకం)
{
    SDL_zerop(బహుళకం);
    బహుళకం->w = bmode->virtual_వెడల్పు;
    బహుళకం->h = bmode->virtual_ఎత్తు;
    get_refresh_రేటు(*bmode, &బహుళకం->refresh_రేటు_numerator, &బహుళకం->refresh_రేటు_denominator);

#ఒకవేళ WRAP_BMODE
    SDL_Display_బహుళకం_దత్తాంశం *దత్తాంశం = (SDL_Display_బహుళకం_దత్తాంశం *)SDL_calloc(1, పరిమాణం(SDL_Display_బహుళకం_దత్తాంశం));
    దత్తాంశం->bmode = bmode;

    బహుళకం->అంతర్గత = దత్తాంశం;
#లేకపోతే
    బహుళకం->అంతర్గత = bmode;
#అయితే_ముగింపు

    // Set the format
    బహుళకం->format = HAIKU_Color_Space_గమ్యం_SDLPx_Format(bmode->space);
}

// Later, there may be more than one monitor available
స్థిర శూన్య కూడు_Display(BScreen *screen)
{
    SDL_Display_బహుళకం బహుళకం;
    display_బహుళకం_2 bmode;
    screen->Get_బహుళకం(&bmode);

    BDisplay_బహుళకం_గమ్యం_Sdl_Display_బహుళకం(&bmode, &బహుళకం);

    SDL_కూడు_Basic_Video_Display(&బహుళకం);
}

/*
 * Functions called by SDL
 */

తార్కిక HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    కూడు_Display(&screen);
    తిరిగి నిజం;
}

శూన్య HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    తిరిగి;
}


తార్కిక HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.చట్రం_2();
    rect->x = (పూర్ణాంకం)rc.ఎడమ;
    rect->y = (పూర్ణాంకం)rc.శిఖరం;
    rect->w = (పూర్ణాంకం)rc.వెడల్పు_2() + 1;
    rect->h = (పూర్ణాంకం)rc.ఎత్తు_2() + 1;
    తిరిగి నిజం;
}

తార్కిక HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_Display_బహుళకం బహుళకం;
    display_బహుళకం_2 this_bmode;
    display_బహుళకం_2 *bmodes;
    uint32 లెక్క, i;
    తార్కిక retval = అబద్ధం;

    // Get graphics-hardware supported modes
    ఒకవేళ (bscreen.Get_బహుళకం_List(&bmodes, &లెక్క) == B_OK) {
        ఒకవేళ (bscreen.Get_బహుళకం(&this_bmode) == B_OK) {
            కొరకు (i = 0; i < లెక్క; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                ఒకవేళ (bmodes[i].space == this_bmode.space) {
                    BDisplay_బహుళకం_గమ్యం_Sdl_Display_బహుళకం(&bmodes[i], &బహుళకం);
                    SDL_కూడు_Fullscreen_Display_బహుళకం(display, &బహుళకం);
                }
            }
            retval = నిజం;
        }
        విడుదల(bmodes); // This should NOT be SDL_free()
    }

    తిరిగి retval;
}


తార్కిక HAIKU_సమితి_Display_బహుళకం(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_బహుళకం *బహుళకం)
{
    // Get the current screen
    BScreen bscreen;
    ఒకవేళ (!bscreen.IsValid()) {
        తిరిగి SDL_సమితి_Error("Invalid screen");
    }

    // Set the mode using the driver data
    display_బహుళకం_2 *bmode = వెలికితీయి_BMode(బహుళకం);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_బహుళకం_2 *bmode_list;
    bscreen.Get_బహుళకం_List(&bmode_list, &c);
    కొరకు (i = 0; i < c; ++i) {
        ఒకవేళ (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_వెడల్పు == bmode->virtual_వెడల్పు &&
            bmode_list[i].virtual_ఎత్తు == bmode->virtual_ఎత్తు ) {
                bmode = &bmode_list[i];
                ఆపు;
        }
    }

    ఒకవేళ (bscreen.సమితి_బహుళకం(bmode) != B_OK) {
        తిరిగి SDL_సమితి_Error("Bad video mode");
    }

    విడుదల(bmode_list); // This should NOT be SDL_free()

#నిర్వచితమైతే SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#అయితే_ముగింపు

    తిరిగి నిజం;
}

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_HAIKU
