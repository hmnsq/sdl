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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_HAIKU

#ਅਨ੍ਤਰ੍ਭਾਵ <AppKit.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <InterfaceKit.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bmodes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_BWin.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_bopengl.h"
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/haiku/SDL_BApp.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary

#ਜੇ WRAP_BMODE
/* This wrapper is here so that the internal can be freed without freeing
   the display_mode structure */
ਬਣਤਰ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ {
    display_ਬਹੁਲਕ_2 *bmode;
};
#ਜੇ_ਅੰਤ

ਸਥਿਰ SDL_INLINE SDL_BWin *ਮੰਜ਼ਿਲ_Be_Win(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਵਾਪਸ (SDL_BWin *)(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
}

ਸਥਿਰ SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    ਵਾਪਸ SDL_Looper;
}

ਸਥਿਰ SDL_INLINE display_ਬਹੁਲਕ_2 * ਕੱਢੋ_BMode(SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
#ਜੇ WRAP_BMODE
    ਵਾਪਸ ਬਹੁਲਕ->ਅੰਦਰੂਨੀ->bmode;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ (display_ਬਹੁਲਕ_2 *)ਬਹੁਲਕ->ਅੰਦਰੂਨੀ;
#ਜੇ_ਅੰਤ
}

// Copied from haiku/trunk/src/preferences/screen/ScreenMode.cpp
ਸਥਿਰ ਖਾਲੀ get_refresh_ਦਰ(display_ਬਹੁਲਕ_2 &ਬਹੁਲਕ, ਪੂਰਨ *numerator, ਪੂਰਨ *denominator)
{
    *numerator = (ਬਹੁਲਕ.timing.pixel_clock * 1000);
    *denominator = (ਬਹੁਲਕ.timing.h_ਕੁੱਲ * ਬਹੁਲਕ.timing.v_ਕੁੱਲ);
}


#ਜੇ 0
/* TODO:
 * This is a useful debugging tool.  Uncomment and insert into code as needed.
 */
ਖਾਲੀ Spout_ਬਹੁਲਕ_ਅੰਕੜੇ(display_ਬਹੁਲਕ_2 *bmode)
{
    SDL_Log("BMode:");
    SDL_Log("\tw,h = (%i,%i)", bmode->virtual_ਚੌੜਾਈ, bmode->virtual_ਉਚਾਈ);
    SDL_Log("\th,v = (%i,%i)", bmode->h_display_ਸ਼ੁਰੂ,
            bmode->v_display_ਸ਼ੁਰੂ);
    ਜੇ (bmode->flags) {
        SDL_Log("\tFlags:");
        ਜੇ (bmode->flags & B_SCROLL) {
            SDL_Log("\t\tB_SCROLL");
        }
        ਜੇ (bmode->flags & B_8_ਦੋਆਧਾਰੀ_ਅੰਕ_DAC) {
            SDL_Log("\t\tB_8_BIT_DAC");
        }
        ਜੇ (bmode->flags & B_HARDWARE_CURSOR) {
            SDL_Log("\t\tB_HARDWARE_CURSOR");
        }
        ਜੇ (bmode->flags & B_PARALLEL_ACCESS) {
            SDL_Log("\t\tB_PARALLEL_ACCESS");
        }
        ਜੇ (bmode->flags & B_DPMS) {
            SDL_Log("\t\tB_DPMS");
        }
        ਜੇ (bmode->flags & B_IO_FB_NA) {
            SDL_Log("\t\tB_IO_FB_NA");
        }
    }
    SDL_Log("\tTiming:");
    SDL_Log("\t\tpx clock: %i", bmode->timing.pixel_clock);
    SDL_Log("\t\th - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.h_display, bmode->timing.h_sync_ਸ਼ੁਰੂ,
        bmode->timing.h_sync_ਸਿਰਾ, bmode->timing.h_ਕੁੱਲ);
    SDL_Log("\t\tv - display: %i sync start: %i sync end: %i total: %i",
        bmode->timing.v_display, bmode->timing.v_sync_ਸ਼ੁਰੂ,
        bmode->timing.v_sync_ਸਿਰਾ, bmode->timing.v_ਕੁੱਲ);
    ਜੇ (bmode->timing.flags) {
        SDL_Log("\t\tFlags:");
        ਜੇ (bmode->timing.flags & B_BLANK_PEDESTAL) {
            SDL_Log("\t\t\tB_BLANK_PEDESTAL");
        }
        ਜੇ (bmode->timing.flags & B_TIMING_INTERLACED) {
            SDL_Log("\t\t\tB_TIMING_INTERLACED");
        }
        ਜੇ (bmode->timing.flags & B_ਸਕਾਰਾਤਮਕ_HSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_HSYNC");
        }
        ਜੇ (bmode->timing.flags & B_ਸਕਾਰਾਤਮਕ_VSYNC) {
            SDL_Log("\t\t\tB_POSITIVE_VSYNC");
        }
        ਜੇ (bmode->timing.flags & B_SYNC_ON_GREEN) {
            SDL_Log("\t\t\tB_SYNC_ON_GREEN");
        }
    }
}
#ਜੇ_ਅੰਤ



SDL_PixelFormat HAIKU_Color_Space_ਮੰਜ਼ਿਲ_SDLPx_Format(uint32 colorspace)
{
    ਚੋਣ (colorspace) {
    ਹਾਲਤ B_CMAP8:
        ਵਾਪਸ SDL_PIXELFORMAT_INDEX8;
        ਰੋਕੋ;
    ਹਾਲਤ B_RGB15:
    ਹਾਲਤ B_RGBA15:
    ਹਾਲਤ B_RGB15_BIG:
    ਹਾਲਤ B_RGBA15_BIG:
        ਵਾਪਸ SDL_PIXELFORMAT_XRGB1555;
        ਰੋਕੋ;
    ਹਾਲਤ B_RGB16:
    ਹਾਲਤ B_RGB16_BIG:
        ਵਾਪਸ SDL_PIXELFORMAT_RGB565;
        ਰੋਕੋ;
    ਹਾਲਤ B_RGB24:
    ਹਾਲਤ B_RGB24_BIG:
        ਵਾਪਸ SDL_PIXELFORMAT_BGR24;
        ਰੋਕੋ;
    ਹਾਲਤ B_RGB32:
    ਹਾਲਤ B_RGBA32:
    ਹਾਲਤ B_RGB32_BIG:
    ਹਾਲਤ B_RGBA32_BIG:
        ਵਾਪਸ SDL_PIXELFORMAT_XRGB8888;
        ਰੋਕੋ;
    }

    // May never get here, but safer and needed to shut up compiler
    SDL_ਸੈੱਟ_Error("Invalid color space");
    ਵਾਪਸ SDL_PIXELFORMAT_UNKNOWN;
}

ਸਥਿਰ ਖਾਲੀ BDisplay_ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_Sdl_Display_ਬਹੁਲਕ(display_ਬਹੁਲਕ_2 *bmode, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    SDL_zerop(ਬਹੁਲਕ);
    ਬਹੁਲਕ->w = bmode->virtual_ਚੌੜਾਈ;
    ਬਹੁਲਕ->h = bmode->virtual_ਉਚਾਈ;
    get_refresh_ਦਰ(*bmode, &ਬਹੁਲਕ->refresh_ਦਰ_numerator, &ਬਹੁਲਕ->refresh_ਦਰ_denominator);

#ਜੇ WRAP_BMODE
    SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ));
    ਅੰਕੜੇ->bmode = bmode;

    ਬਹੁਲਕ->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
#ਨਹੀਂਤਾਂ
    ਬਹੁਲਕ->ਅੰਦਰੂਨੀ = bmode;
#ਜੇ_ਅੰਤ

    // Set the format
    ਬਹੁਲਕ->format = HAIKU_Color_Space_ਮੰਜ਼ਿਲ_SDLPx_Format(bmode->space);
}

// Later, there may be more than one monitor available
ਸਥਿਰ ਖਾਲੀ ਜੋੜੋ_Display(BScreen *screen)
{
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    display_ਬਹੁਲਕ_2 bmode;
    screen->Get_ਬਹੁਲਕ(&bmode);

    BDisplay_ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_Sdl_Display_ਬਹੁਲਕ(&bmode, &ਬਹੁਲਕ);

    SDL_ਜੋੜੋ_Basic_Video_Display(&ਬਹੁਲਕ);
}

/*
 * Functions called by SDL
 */

ਤਾਰਕਿਕ HAIKU_InitModes(SDL_VideoDevice *_this)
{
    BScreen screen;

    /* TODO: When Haiku supports multiple display screens, call
       _AddDisplayScreen() for each of them. */
    ਜੋੜੋ_Display(&screen);
    ਵਾਪਸ ਸੱਚ;
}

ਖਾਲੀ HAIKU_QuitModes(SDL_VideoDevice *_this)
{
    ਵਾਪਸ;
}


ਤਾਰਕਿਕ HAIKU_GetDisplayBounds(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Rect *rect)
{
    BScreen bscreen;
    BRect rc = bscreen.ਚੌਖਟਾ_2();
    rect->x = (ਪੂਰਨ)rc.ਖੱਬੇ;
    rect->y = (ਪੂਰਨ)rc.ਸਿਖਰ;
    rect->w = (ਪੂਰਨ)rc.ਚੌੜਾਈ_2() + 1;
    rect->h = (ਪੂਰਨ)rc.ਉਚਾਈ_2() + 1;
    ਵਾਪਸ ਸੱਚ;
}

ਤਾਰਕਿਕ HAIKU_GetDisplayModes(SDL_VideoDevice *_this, SDL_VideoDisplay *display)
{
    // Get the current screen
    BScreen bscreen;

    // Iterate through all of the modes
    SDL_Display_ਬਹੁਲਕ ਬਹੁਲਕ;
    display_ਬਹੁਲਕ_2 this_bmode;
    display_ਬਹੁਲਕ_2 *bmodes;
    uint32 ਗਿਣਤੀ_2, i;
    ਤਾਰਕਿਕ retval = ਝੂਠ;

    // Get graphics-hardware supported modes
    ਜੇ (bscreen.Get_ਬਹੁਲਕ_List(&bmodes, &ਗਿਣਤੀ_2) == B_OK) {
        ਜੇ (bscreen.Get_ਬਹੁਲਕ(&this_bmode) == B_OK) {
            ਲਈ (i = 0; i < ਗਿਣਤੀ_2; ++i) {
                // FIXME: Apparently there are errors with colorspace changes
                ਜੇ (bmodes[i].space == this_bmode.space) {
                    BDisplay_ਬਹੁਲਕ_ਮੰਜ਼ਿਲ_Sdl_Display_ਬਹੁਲਕ(&bmodes[i], &ਬਹੁਲਕ);
                    SDL_ਜੋੜੋ_Fullscreen_Display_ਬਹੁਲਕ(display, &ਬਹੁਲਕ);
                }
            }
            retval = ਸੱਚ;
        }
        ਮੁਕਤ(bmodes); // This should NOT be SDL_free()
    }

    ਵਾਪਸ retval;
}


ਤਾਰਕਿਕ HAIKU_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *_this, SDL_VideoDisplay *display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ)
{
    // Get the current screen
    BScreen bscreen;
    ਜੇ (!bscreen.IsValid()) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Invalid screen");
    }

    // Set the mode using the driver data
    display_ਬਹੁਲਕ_2 *bmode = ਕੱਢੋ_BMode(ਬਹੁਲਕ);


    // FIXME: Is the first option always going to be the right one?
    uint32 c = 0, i;
    display_ਬਹੁਲਕ_2 *bmode_list;
    bscreen.Get_ਬਹੁਲਕ_List(&bmode_list, &c);
    ਲਈ (i = 0; i < c; ++i) {
        ਜੇ (    bmode_list[i].space == bmode->space &&
            bmode_list[i].virtual_ਚੌੜਾਈ == bmode->virtual_ਚੌੜਾਈ &&
            bmode_list[i].virtual_ਉਚਾਈ == bmode->virtual_ਉਚਾਈ ) {
                bmode = &bmode_list[i];
                ਰੋਕੋ;
        }
    }

    ਜੇ (bscreen.ਸੈੱਟ_ਬਹੁਲਕ(bmode) != B_OK) {
        ਵਾਪਸ SDL_ਸੈੱਟ_Error("Bad video mode");
    }

    ਮੁਕਤ(bmode_list); // This should NOT be SDL_free()

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL
    /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't
       help */
//    HAIKU_GL_RebootContexts(_this);
#ਜੇ_ਅੰਤ

    ਵਾਪਸ ਸੱਚ;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_HAIKU
