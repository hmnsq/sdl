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
#ضمن "SDL_internal.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_HAIKU

#ضمن <AppKit.h>
#ضمن <InterfaceKit.h>
#ضمن "SDL_bmodes.h"
#ضمن "SDL_BWin.h"

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
#ضمن "SDL_bopengl.h"
#جيڪڏهن_پورو

#ضمن "../../core/haiku/SDL_BApp.h"

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو


#وصف_ڪريو WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#إذا WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
بنية SDL_Display_گهڻائي_معلومات {
    display_گهڻائي_2 *bmode;
};
#جيڪڏهن_پورو

ساكن SDL_INLINE SDL_BWin *منزل_Be_Win(SDL_دري *دري)
{
    أرجع (SDL_BWin *)(دري->اندروني);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    أرجع SDL_Looper;
}

ساكن SDL_INLINE display_گهڻائي_2 * ڪڍو_BMode(SDL_Display_گهڻائي *گهڻائي)
{
#إذا WRAP_BMODE
    أرجع گهڻائي->اندروني->bmode;
#وإلا
    أرجع (display_گهڻائي_2 *)گهڻائي->اندروني;
#جيڪڏهن_پورو
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
ساكن فراغ get_refresh_شرح(display_گهڻائي_2 &گهڻائي, صحيح *numerator, صحيح *denominator)
{
    *numerator = (گهڻائي.timing.pixel_clock * 1000);
    *denominator = (گهڻائي.timing.h_ڪل * گهڻائي.timing.v_ڪل);
}


#إذا 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
فراغ Spout_گهڻائي_معلومات(display_گهڻائي_2 *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_ويڪر, bmode->virtual_اوچائي);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_شروعات,
            bmode->v_display_شروعات);
    إذا (bmode->flags) {
        SDL_Log("\tFlags:");
        إذا (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        إذا (bmode->flags & B_8_ٻٽو_انگ_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        إذا (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        إذا (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        إذا (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        إذا (bmode->flags & B_IO_FB_NA) {
            SDL_Log("\t\tB_IO_FB_NA");
        }
    }
    SDL_Log("\tTiming:");
    SDL_Log("\t\tpx clock: %i", bmode->timing.pixel_clock);
    SDL_Log("\t\th - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.h_display, bmode->timing.h_sync_شروعات,
        bmode->timing.h_sync_پڇاڙي, bmode->timing.h_ڪل);
    SDL_Log("\t\tv - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.v_display, bmode->timing.v_sync_شروعات,
        bmode->timing.v_sync_پڇاڙي, bmode->timing.v_ڪل);
    إذا (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        إذا (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        إذا (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        إذا (bmode->timing.flags & B_مثبت_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        إذا (bmode->timing.flags & B_مثبت_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        إذا (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#جيڪڏهن_پورو



SDL_PixelFormat HAIKU_Color_Space_منزل_SDLPx_Format(uint32 colorspace)
{
    بدل (colorspace) {
    حالة B_CMAP8:
        أرجع SDL_PIXELFORMAT_INDEX8;
        اكسر;
    حالة B_RGB15:
    حالة B_RGBA15:
    حالة B_RGB15_BIG:
    حالة B_RGBA15_BIG:
        أرجع SDL_PIXELFORMAT_XRGB1555;
        اكسر;
    حالة B_RGB16:
    حالة B_RGB16_BIG:
        أرجع SDL_PIXELFORMAT_RGB565;
        اكسر;
    حالة B_RGB24:
    حالة B_RGB24_BIG:
        أرجع SDL_PIXELFORMAT_BGR24;
        اكسر;
    حالة B_RGB32:
    حالة B_RGBA32:
    حالة B_RGB32_BIG:
    حالة B_RGBA32_BIG:
        أرجع SDL_PIXELFORMAT_XRGB8888;
        اكسر;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_سيٽ_Error("Invalid color space");
    أرجع SDL_PIXELFORMAT_UNKNOWN;
}

ساكن فراغ BDisplay_گهڻائي_منزل_Sdl_Display_گهڻائي(display_گهڻائي_2 *bmode, SDL_Display_گهڻائي *گهڻائي)
{
    SDL_zerop(گهڻائي);
    گهڻائي->w = bmode->virtual_ويڪر;
    گهڻائي->h = bmode->virtual_اوچائي;
    get_refresh_شرح(*bmode, &گهڻائي->refresh_شرح_numerator, &گهڻائي->refresh_شرح_denominator);

#إذا WRAP_BMODE
    SDL_Display_گهڻائي_معلومات *معلومات = (SDL_Display_گهڻائي_معلومات *)SDL_calloc(1, حجم(SDL_Display_گهڻائي_معلومات));
    معلومات->bmode = bmode;

    گهڻائي->اندروني = معلومات;
#وإلا
    گهڻائي->اندروني = bmode;
#جيڪڏهن_پورو

    // Set the format
    گهڻائي->format = HAIKU_Color_Space_منزل_SDLPx_Format(bmode->space);
}

// Later, there may be more than one monitor available
ساكن فراغ جوڙيو_Display(BScreen *screen)
{
    SDL_Display_گهڻائي گهڻائي;
    display_گهڻائي_2 bmode;
    screen->Get_گهڻائي(&bmode);

    BDisplay_گهڻائي_منزل_Sdl_Display_گهڻائي(&bmode, &گهڻائي);

    SDL_جوڙيو_Basic_Video_Display(&گهڻائي);
}

/*
 * Functions called by SDL
 */

منطقي HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    جوڙيو_Display(&screen);
    أرجع سچ;
}

فراغ HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    أرجع;
}


منطقي HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.چوکٺو_2();
    rect->x = (صحيح)rc.کاٻي;
    rect->y = (صحيح)rc.چوٽي;
    rect->w = (صحيح)rc.ويڪر_2() + 1;
    rect->h = (صحيح)rc.اوچائي_2() + 1;
    أرجع سچ;
}

منطقي HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_Display_گهڻائي گهڻائي;
    display_گهڻائي_2 this_bmode;
    display_گهڻائي_2 *bmodes;
    uint32 ڳڻپ, i;
    منطقي retval = خطأ;

    // Get graphics-hardware supported modes
    إذا (bscreen.Get_گهڻائي_List(&bmodes, &ڳڻپ) == B_OK) {
        إذا (bscreen.Get_گهڻائي(&this_bmode) == B_OK) {
            لكل (i = 0; i < ڳڻپ; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                إذا (bmodes[i].space == this_bmode.space) {
                    BDisplay_گهڻائي_منزل_Sdl_Display_گهڻائي(&bmodes[i], &گهڻائي);
                    SDL_جوڙيو_Fullscreen_Display_گهڻائي(display, &گهڻائي);
                }
            }
            retval = سچ;
        }
        حرر(bmodes); // This should NOT be SDL_free()
    }

    أرجع retval;
}


منطقي HAIKU_سيٽ_Display_گهڻائي(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_گهڻائي *گهڻائي)
{
    // Get the current screen
    BScreen bscreen;
    إذا (!bscreen.IsValid()) {
        أرجع SDL_سيٽ_Error("Invalid screen");
    }

    // Set the mode using the driver data
    display_گهڻائي_2 *bmode = ڪڍو_BMode(گهڻائي);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_گهڻائي_2 *bmode_list;
    bscreen.Get_گهڻائي_List(&bmode_list, &c);
    لكل (i = 0; i < c; ++i) {
        إذا (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_ويڪر == bmode->virtual_ويڪر &&
            bmode_list[i].virtual_اوچائي == bmode->virtual_اوچائي ) {
                bmode = &bmode_list[i];
                اكسر;
        }
    }

    إذا (bscreen.سيٽ_گهڻائي(bmode) != B_OK) {
        أرجع SDL_سيٽ_Error("Bad video mode");
    }

    حرر(bmode_list); // This should NOT be SDL_free()

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#جيڪڏهن_پورو

    أرجع سچ;
}

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_HAIKU
