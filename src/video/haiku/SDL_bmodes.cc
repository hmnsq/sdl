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

#که_تعریف_شوی SDL_VIDEO_DRIVER_HAIKU

#ضمن <AppKit.h>
#ضمن <InterfaceKit.h>
#ضمن "SDL_bmodes.h"
#ضمن "SDL_BWin.h"

#که_تعریف_شوی SDL_VIDEO_OPENGL
#ضمن "SDL_bopengl.h"
#د_که_پای

#ضمن "../../core/haiku/SDL_BApp.h"

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای


#تعریف_کړه WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#إذا WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
بنية SDL_Display_ډېرپېښ_معلومات {
    display_ډېرپېښ_2 *bmode;
};
#د_که_پای

ساكن SDL_INLINE SDL_BWin *منزل_Be_Win(SDL_کړکۍ *کړکۍ)
{
    أرجع (SDL_BWin *)(کړکۍ->دننی);
}

ساكن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    أرجع SDL_Looper;
}

ساكن SDL_INLINE display_ډېرپېښ_2 * ایستل_BMode(SDL_Display_ډېرپېښ *ډېرپېښ)
{
#إذا WRAP_BMODE
    أرجع ډېرپېښ->دننی->bmode;
#وإلا
    أرجع (display_ډېرپېښ_2 *)ډېرپېښ->دننی;
#د_که_پای
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
ساكن فراغ get_refresh_شرح(display_ډېرپېښ_2 &ډېرپېښ, صحيح *numerator, صحيح *denominator)
{
    *numerator = (ډېرپېښ.timing.pixel_clock * 1000);
    *denominator = (ډېرپېښ.timing.h_ټول * ډېرپېښ.timing.v_ټول);
}


#إذا 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
فراغ Spout_ډېرپېښ_معلومات(display_ډېرپېښ_2 *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_پلنوالی, bmode->virtual_لوړوالی);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_پیل,
            bmode->v_display_پیل);
    إذا (bmode->flags) {
        SDL_Log("\tFlags:");
        إذا (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        إذا (bmode->flags & B_8_بټ_DAC) {
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
        bmode->timing.h_display, bmode->timing.h_sync_پیل,
        bmode->timing.h_sync_پای_ټکی, bmode->timing.h_ټول);
    SDL_Log("\t\tv - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.v_display, bmode->timing.v_sync_پیل,
        bmode->timing.v_sync_پای_ټکی, bmode->timing.v_ټول);
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
#د_که_پای



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
    SDL_سېټ_Error("Invalid color space");
    أرجع SDL_PIXELFORMAT_UNKNOWN;
}

ساكن فراغ BDisplay_ډېرپېښ_منزل_Sdl_Display_ډېرپېښ(display_ډېرپېښ_2 *bmode, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    SDL_zerop(ډېرپېښ);
    ډېرپېښ->w = bmode->virtual_پلنوالی;
    ډېرپېښ->h = bmode->virtual_لوړوالی;
    get_refresh_شرح(*bmode, &ډېرپېښ->refresh_شرح_numerator, &ډېرپېښ->refresh_شرح_denominator);

#إذا WRAP_BMODE
    SDL_Display_ډېرپېښ_معلومات *معلومات = (SDL_Display_ډېرپېښ_معلومات *)SDL_calloc(1, حجم(SDL_Display_ډېرپېښ_معلومات));
    معلومات->bmode = bmode;

    ډېرپېښ->دننی = معلومات;
#وإلا
    ډېرپېښ->دننی = bmode;
#د_که_پای

    // Set the format
    ډېرپېښ->format = HAIKU_Color_Space_منزل_SDLPx_Format(bmode->space);
}

// Later, there may be more than one monitor available
ساكن فراغ جمع_کړه_Display(BScreen *screen)
{
    SDL_Display_ډېرپېښ ډېرپېښ;
    display_ډېرپېښ_2 bmode;
    screen->Get_ډېرپېښ(&bmode);

    BDisplay_ډېرپېښ_منزل_Sdl_Display_ډېرپېښ(&bmode, &ډېرپېښ);

    SDL_جمع_کړه_Basic_Video_Display(&ډېرپېښ);
}

/*
 * Functions called by SDL
 */

منطقي HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    جمع_کړه_Display(&screen);
    أرجع ریښتیا;
}

فراغ HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    أرجع;
}


منطقي HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.چوکاټ_2();
    rect->x = (صحيح)rc.کیڼ;
    rect->y = (صحيح)rc.سر;
    rect->w = (صحيح)rc.پلنوالی_2() + 1;
    rect->h = (صحيح)rc.لوړوالی_2() + 1;
    أرجع ریښتیا;
}

منطقي HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_Display_ډېرپېښ ډېرپېښ;
    display_ډېرپېښ_2 this_bmode;
    display_ډېرپېښ_2 *bmodes;
    uint32 شمېر, i;
    منطقي retval = خطأ;

    // Get graphics-hardware supported modes
    إذا (bscreen.Get_ډېرپېښ_List(&bmodes, &شمېر) == B_OK) {
        إذا (bscreen.Get_ډېرپېښ(&this_bmode) == B_OK) {
            لكل (i = 0; i < شمېر; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                إذا (bmodes[i].space == this_bmode.space) {
                    BDisplay_ډېرپېښ_منزل_Sdl_Display_ډېرپېښ(&bmodes[i], &ډېرپېښ);
                    SDL_جمع_کړه_Fullscreen_Display_ډېرپېښ(display, &ډېرپېښ);
                }
            }
            retval = ریښتیا;
        }
        حرر(bmodes); // This should NOT be SDL_free()
    }

    أرجع retval;
}


منطقي HAIKU_سېټ_Display_ډېرپېښ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ډېرپېښ *ډېرپېښ)
{
    // Get the current screen
    BScreen bscreen;
    إذا (!bscreen.IsValid()) {
        أرجع SDL_سېټ_Error("Invalid screen");
    }

    // Set the mode using the driver data
    display_ډېرپېښ_2 *bmode = ایستل_BMode(ډېرپېښ);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_ډېرپېښ_2 *bmode_list;
    bscreen.Get_ډېرپېښ_List(&bmode_list, &c);
    لكل (i = 0; i < c; ++i) {
        إذا (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_پلنوالی == bmode->virtual_پلنوالی &&
            bmode_list[i].virtual_لوړوالی == bmode->virtual_لوړوالی ) {
                bmode = &bmode_list[i];
                اكسر;
        }
    }

    إذا (bscreen.سېټ_ډېرپېښ(bmode) != B_OK) {
        أرجع SDL_سېټ_Error("Bad video mode");
    }

    حرر(bmode_list); // This should NOT be SDL_free()

#که_تعریف_شوی SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#د_که_پای

    أرجع ریښتیا;
}

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای // SDL_VIDEO_DRIVER_HAIKU
