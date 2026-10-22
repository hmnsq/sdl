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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_HAIKU

#شامل <AppKit.h>
#شامل <InterfaceKit.h>
#شامل "SDL_bmodes.h"
#شامل "SDL_BWin.h"

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
#شامل "SDL_bopengl.h"
#اگر_ختم

#شامل "../../core/haiku/SDL_BApp.h"

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم


#تعریف_کرو WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#اگر WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
ساخت SDL_Display_منوال_ڈیٹا {
    display_منوال_2 *bmode;
};
#اگر_ختم

ساکن SDL_INLINE SDL_BWin *مقصد_Be_Win(SDL_کھڑکی *کھڑکی)
{
    واپس (SDL_BWin *)(کھڑکی->اندرونی_2);
}

ساکن SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    واپس SDL_Looper;
}

ساکن SDL_INLINE display_منوال_2 * نکالو_BMode(SDL_Display_منوال *منوال)
{
#اگر WRAP_BMODE
    واپس منوال->اندرونی_2->bmode;
#ورنہ
    واپس (display_منوال_2 *)منوال->اندرونی_2;
#اگر_ختم
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
ساکن خالی get_refresh_شرح(display_منوال_2 &منوال, صحیح *numerator, صحیح *denominator)
{
    *numerator = (منوال.timing.pixel_clock * 1000);
    *denominator = (منوال.timing.h_کل * منوال.timing.v_کل);
}


#اگر 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
خالی Spout_منوال_ڈیٹا(display_منوال_2 *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_چوڑائی, bmode->virtual_اونچائی);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_آغاز,
            bmode->v_display_آغاز);
    اگر (bmode->flags) {
        SDL_Log("\tFlags:");
        اگر (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        اگر (bmode->flags & B_8_ثنائی_ہندسہ_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        اگر (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        اگر (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        اگر (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        اگر (bmode->flags & B_IO_FB_NA) {
            SDL_Log("\t\tB_IO_FB_NA");
        }
    }
    SDL_Log("\tTiming:");
    SDL_Log("\t\tpx clock: %i", bmode->timing.pixel_clock);
    SDL_Log("\t\th - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.h_display, bmode->timing.h_sync_آغاز,
        bmode->timing.h_sync_انتہا, bmode->timing.h_کل);
    SDL_Log("\t\tv - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.v_display, bmode->timing.v_sync_آغاز,
        bmode->timing.v_sync_انتہا, bmode->timing.v_کل);
    اگر (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        اگر (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        اگر (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        اگر (bmode->timing.flags & B_مثبت_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        اگر (bmode->timing.flags & B_مثبت_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        اگر (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#اگر_ختم



SDL_PixelFormat HAIKU_Color_Space_مقصد_SDLPx_Format(uint32 colorspace)
{
    انتخاب (colorspace) {
    حالت B_CMAP8:
        واپس SDL_PIXELFORMAT_INDEX8;
        توڑو;
    حالت B_RGB15:
    حالت B_RGBA15:
    حالت B_RGB15_BIG:
    حالت B_RGBA15_BIG:
        واپس SDL_PIXELFORMAT_XRGB1555;
        توڑو;
    حالت B_RGB16:
    حالت B_RGB16_BIG:
        واپس SDL_PIXELFORMAT_RGB565;
        توڑو;
    حالت B_RGB24:
    حالت B_RGB24_BIG:
        واپس SDL_PIXELFORMAT_BGR24;
        توڑو;
    حالت B_RGB32:
    حالت B_RGBA32:
    حالت B_RGB32_BIG:
    حالت B_RGBA32_BIG:
        واپس SDL_PIXELFORMAT_XRGB8888;
        توڑو;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_سیٹ_Error("Invalid color space");
    واپس SDL_PIXELFORMAT_UNKNOWN;
}

ساکن خالی BDisplay_منوال_مقصد_Sdl_Display_منوال(display_منوال_2 *bmode, SDL_Display_منوال *منوال)
{
    SDL_zerop(منوال);
    منوال->w = bmode->virtual_چوڑائی;
    منوال->h = bmode->virtual_اونچائی;
    get_refresh_شرح(*bmode, &منوال->refresh_شرح_numerator, &منوال->refresh_شرح_denominator);

#اگر WRAP_BMODE
    SDL_Display_منوال_ڈیٹا *ڈیٹا = (SDL_Display_منوال_ڈیٹا *)SDL_calloc(1, حجم(SDL_Display_منوال_ڈیٹا));
    ڈیٹا->bmode = bmode;

    منوال->اندرونی_2 = ڈیٹا;
#ورنہ
    منوال->اندرونی_2 = bmode;
#اگر_ختم

    // Set the format
    منوال->format = HAIKU_Color_Space_مقصد_SDLPx_Format(bmode->space);
}

// Later, there may be more than one monitor available
ساکن خالی جوڑو_Display(BScreen *screen)
{
    SDL_Display_منوال منوال;
    display_منوال_2 bmode;
    screen->Get_منوال(&bmode);

    BDisplay_منوال_مقصد_Sdl_Display_منوال(&bmode, &منوال);

    SDL_جوڑو_Basic_Video_Display(&منوال);
}

/*
 * Functions called by SDL
 */

منطقی HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    جوڑو_Display(&screen);
    واپس سچ;
}

خالی HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    واپس;
}


منطقی HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.چوکھٹا_2();
    rect->x = (صحیح)rc.بائیں;
    rect->y = (صحیح)rc.چوٹی;
    rect->w = (صحیح)rc.چوڑائی_2() + 1;
    rect->h = (صحیح)rc.اونچائی_2() + 1;
    واپس سچ;
}

منطقی HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_Display_منوال منوال;
    display_منوال_2 this_bmode;
    display_منوال_2 *bmodes;
    uint32 گنتی, i;
    منطقی retval = جھوٹ;

    // Get graphics-hardware supported modes
    اگر (bscreen.Get_منوال_List(&bmodes, &گنتی) == B_OK) {
        اگر (bscreen.Get_منوال(&this_bmode) == B_OK) {
            برائے (i = 0; i < گنتی; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                اگر (bmodes[i].space == this_bmode.space) {
                    BDisplay_منوال_مقصد_Sdl_Display_منوال(&bmodes[i], &منوال);
                    SDL_جوڑو_Fullscreen_Display_منوال(display, &منوال);
                }
            }
            retval = سچ;
        }
        آزاد(bmodes); // This should NOT be SDL_free()
    }

    واپس retval;
}


منطقی HAIKU_سیٹ_Display_منوال(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_منوال *منوال)
{
    // Get the current screen
    BScreen bscreen;
    اگر (!bscreen.IsValid()) {
        واپس SDL_سیٹ_Error("Invalid screen");
    }

    // Set the mode using the driver data
    display_منوال_2 *bmode = نکالو_BMode(منوال);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_منوال_2 *bmode_list;
    bscreen.Get_منوال_List(&bmode_list, &c);
    برائے (i = 0; i < c; ++i) {
        اگر (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_چوڑائی == bmode->virtual_چوڑائی &&
            bmode_list[i].virtual_اونچائی == bmode->virtual_اونچائی ) {
                bmode = &bmode_list[i];
                توڑو;
        }
    }

    اگر (bscreen.سیٹ_منوال(bmode) != B_OK) {
        واپس SDL_سیٹ_Error("Bad video mode");
    }

    آزاد(bmode_list); // This should NOT be SDL_free()

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#اگر_ختم

    واپس سچ;
}

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم // SDL_VIDEO_DRIVER_HAIKU
