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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_HAIKU

#अन्तर्भाव <AppKit.h>
#अन्तर्भाव <InterfaceKit.h>
#अन्तर्भाव "SDL_bmodes.h"
#अन्तर्भाव "SDL_BWin.h"

#यदि_परिभाषितम् SDL_VIDEO_OPENGL
#अन्तर्भाव "SDL_bopengl.h"
#यदि_अन्तः

#अन्तर्भाव "../../core/haiku/SDL_BApp.h"

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः


#परिभाषय WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#यदि WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
संरचना SDL_Display_बहुलकम्_दत्त {
    display_बहुलकम्_2 *bmode;
};
#यदि_अन्तः

स्थिर SDL_INLINE SDL_BWin *गन्तव्यम्_Be_Win(SDL_गवाक्षः *गवाक्षः)
{
    प्रत्यागम (SDL_BWin *)(गवाक्षः->आन्तरिकम्);
}

स्थिर SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    प्रत्यागम SDL_Looper;
}

स्थिर SDL_INLINE display_बहुलकम्_2 * _ExtractBMode(SDL_Display_बहुलकम् *बहुलकम्)
{
#यदि WRAP_BMODE
    प्रत्यागम बहुलकम्->आन्तरिकम्->bmode;
#अन्यथा
    प्रत्यागम (display_बहुलकम्_2 *)बहुलकम्->आन्तरिकम्;
#यदि_अन्तः
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
स्थिर शून्य get_refresh_दरः(display_बहुलकम्_2 &बहुलकम्, पूर्णाङ्क *numerator, पूर्णाङ्क *denominator)
{
    *numerator = (बहुलकम्.timing.pixel_clock * 1000);
    *denominator = (बहुलकम्.timing.h_योग * बहुलकम्.timing.v_योग);
}


#यदि 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
शून्य Spout_बहुलकम्_दत्त(display_बहुलकम्_2 *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_विस्तारः, bmode->virtual_height);
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
        bmode->timing.h_sync_अन्तः, bmode->timing.h_योग);
    SDL_Log("\t\tv - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.v_display, bmode->timing.v_sync_start,
        bmode->timing.v_sync_अन्तः, bmode->timing.v_योग);
    यदि (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        यदि (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        यदि (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        यदि (bmode->timing.flags & B_धनात्मकम्_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        यदि (bmode->timing.flags & B_धनात्मकम्_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        यदि (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#यदि_अन्तः



SDL_PixelFormat HAIKU_Color_Space_गन्तव्यम्_SDLPx_Format(uint32 colorspace)
{
    विकल्प (colorspace) {
    पक्ष B_CMAP8:
        प्रत्यागम SDL_PIXELFORMAT_INDEX8;
        भङ्ग;
    पक्ष B_RGB15:
    पक्ष B_RGBA15:
    पक्ष B_RGB15_BIG:
    पक्ष B_RGBA15_BIG:
        प्रत्यागम SDL_PIXELFORMAT_XRGB1555;
        भङ्ग;
    पक्ष B_RGB16:
    पक्ष B_RGB16_BIG:
        प्रत्यागम SDL_PIXELFORMAT_RGB565;
        भङ्ग;
    पक्ष B_RGB24:
    पक्ष B_RGB24_BIG:
        प्रत्यागम SDL_PIXELFORMAT_BGR24;
        भङ्ग;
    पक्ष B_RGB32:
    पक्ष B_RGBA32:
    पक्ष B_RGB32_BIG:
    पक्ष B_RGBA32_BIG:
        प्रत्यागम SDL_PIXELFORMAT_XRGB8888;
        भङ्ग;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_समुच्चयः_Error("Invalid color space");
    प्रत्यागम SDL_PIXELFORMAT_UNKNOWN;
}

स्थिर शून्य BDisplay_बहुलकम्_गन्तव्यम्_Sdl_Display_बहुलकम्(display_बहुलकम्_2 *bmode, SDL_Display_बहुलकम् *बहुलकम्)
{
    SDL_zerop(बहुलकम्);
    बहुलकम्->w = bmode->virtual_विस्तारः;
    बहुलकम्->h = bmode->virtual_height;
    get_refresh_दरः(*bmode, &बहुलकम्->refresh_दरः_numerator, &बहुलकम्->refresh_दरः_denominator);

#यदि WRAP_BMODE
    SDL_Display_बहुलकम्_दत्त *दत्त = (SDL_Display_बहुलकम्_दत्त *)SDL_calloc(1, परिमाण(SDL_Display_बहुलकम्_दत्त));
    दत्त->bmode = bmode;

    बहुलकम्->आन्तरिकम् = दत्त;
#अन्यथा
    बहुलकम्->आन्तरिकम् = bmode;
#यदि_अन्तः

    // Set the format
    बहुलकम्->format = HAIKU_Color_Space_गन्तव्यम्_SDLPx_Format(bmode->space);
}

// Later, there may be more than one monitor available
स्थिर शून्य सङ्कलय_Display(BScreen *screen)
{
    SDL_Display_बहुलकम् बहुलकम्;
    display_बहुलकम्_2 bmode;
    screen->Get_बहुलकम्(&bmode);

    BDisplay_बहुलकम्_गन्तव्यम्_Sdl_Display_बहुलकम्(&bmode, &बहुलकम्);

    SDL_सङ्कलय_Basic_Video_Display(&बहुलकम्);
}

/*
 * Functions called by SDL
 */

तार्किक HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    सङ्कलय_Display(&screen);
    प्रत्यागम सत्य;
}

शून्य HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    प्रत्यागम;
}


तार्किक HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.Frame();
    rect->x = (पूर्णाङ्क)rc.वामतः;
    rect->y = (पूर्णाङ्क)rc.शिखरम्;
    rect->w = (पूर्णाङ्क)rc.विस्तारः_2() + 1;
    rect->h = (पूर्णाङ्क)rc.Height() + 1;
    प्रत्यागम सत्य;
}

तार्किक HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_Display_बहुलकम् बहुलकम्;
    display_बहुलकम्_2 this_bmode;
    display_बहुलकम्_2 *bmodes;
    uint32 गणनम्, i;
    तार्किक retval = असत्य;

    // Get graphics-hardware supported modes
    यदि (bscreen.Get_बहुलकम्_List(&bmodes, &गणनम्) == B_OK) {
        यदि (bscreen.Get_बहुलकम्(&this_bmode) == B_OK) {
            प्रति (i = 0; i < गणनम्; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                यदि (bmodes[i].space == this_bmode.space) {
                    BDisplay_बहुलकम्_गन्तव्यम्_Sdl_Display_बहुलकम्(&bmodes[i], &बहुलकम्);
                    SDL_सङ्कलय_Fullscreen_Display_बहुलकम्(display, &बहुलकम्);
                }
            }
            retval = सत्य;
        }
        मुक्त(bmodes); // This should NOT be SDL_free()
    }

    प्रत्यागम retval;
}


तार्किक HAIKU_समुच्चयः_Display_बहुलकम्(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_बहुलकम् *बहुलकम्)
{
    // Get the current screen
    BScreen bscreen;
    यदि (!bscreen.IsValid()) {
        प्रत्यागम SDL_समुच्चयः_Error("Invalid screen");
    }

    // Set the mode using the driver data
    display_बहुलकम्_2 *bmode = _ExtractBMode(बहुलकम्);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_बहुलकम्_2 *bmode_list;
    bscreen.Get_बहुलकम्_List(&bmode_list, &c);
    प्रति (i = 0; i < c; ++i) {
        यदि (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_विस्तारः == bmode->virtual_विस्तारः &&
            bmode_list[i].virtual_height == bmode->virtual_height ) {
                bmode = &bmode_list[i];
                भङ्ग;
        }
    }

    यदि (bscreen.समुच्चयः_बहुलकम्(bmode) != B_OK) {
        प्रत्यागम SDL_समुच्चयः_Error("Bad video mode");
    }

    मुक्त(bmode_list); // This should NOT be SDL_free()

#यदि_परिभाषितम् SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#यदि_अन्तः

    प्रत्यागम सत्य;
}

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः // SDL_VIDEO_DRIVER_HAIKU
