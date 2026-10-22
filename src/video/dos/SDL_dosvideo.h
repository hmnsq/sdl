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

#నిర్వచితం_కాకపోతే SDL_dosvideo_h
#నిర్వచించు SDL_dosvideo_h

#అన్తర్భావ "../../core/dos/SDL_dos.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "SDL_internal.h"

నిర్మాణం SDL_Display_బహుళకం_దత్తాంశం
{
    // we can add more fields to this, if we want them, later.
    Uint16 బహుళకం_id;
    Uint16 లక్షణాలు;
    Uint16 pitch;
    Uint16 w;
    Uint16 h;
    Uint8 అంకె_planes;
    Uint8 bpp;
    Uint8 జ్ఞాపకం_model;
    Uint8 అంకె_image_పుటలు;
    Uint8 red_ముసుగు_కొలత;
    Uint8 red_ముసుగు_pos;
    Uint8 green_ముసుగు_కొలత;
    Uint8 green_ముసుగు_pos;
    Uint8 blue_ముసుగు_కొలత;
    Uint8 blue_ముసుగు_pos;
    Uint32 physical_పునాది_addr;

    // VBE 1.2 banked framebuffer fields (used when LFB is not available)
    bool has_lfb;           // true if linear framebuffer is available (VBE 2.0+)
    Uint16 win_granularity; // bank positioning granularity in KB
    Uint16 win_కొలత;        // window size in KB (typically 64)
    Uint16 win_a_segment;   // real-mode segment of window A (typically 0xA000)
    Uint32 win_func_ptr;    // real-mode far pointer to bank-switch function
    Uint8 win_a_లక్షణాలు; // window A capabilities
};

నిర్మాణం SDL_Video_దత్తాంశం
{
    __dpmi_meminfo mapping; // video memory mapping.
    SDL_Display_బహుళకం current_బహుళకం;
    DOS_అంతరాయం_Hook keyboard_అంతరాయం_hook;
    Uint32 palette_సంస్కరణ;       // tracks SDL_Palette::version to detect changes
    Uint16 original_vbe_బహుళకం;     // VBE mode number at startup
    శూన్య *vbe_state_బఫరు;       // saved VBE state (from VBE 0x4F04)
    Uint32 vbe_state_బఫరు_కొలత; // size of the state buffer

    // Mouse sensitivity (mickeys per pixel), queried from INT 33h function 0x1B
    దశాంశం mickeys_చొప్పున_hpixel; // horizontal mickeys per pixel (default: 8)
    దశాంశం mickeys_చొప్పున_vpixel; // vertical mickeys per pixel (default: 16)

    // Page-flipping (double-buffering) state
    పూర్ణాంకం current_పుట;         // 0 or 1: which page is currently displayed
    Uint32 పుట_స్థానభ్రంశం[2];    // byte offset of each page within video memory
    bool పుట_flip_అందుబాటు; // true if mode supports double-buffering
    bool banked_బహుళకం;         // true if current mode uses banked (not LFB) access
};

నిర్మాణం SDL_Display_దత్తాంశం
{
    పూర్ణాంకం వాడని; // for now
};

నిర్మాణం SDL_కిటికీ_దత్తాంశం
{
    పూర్ణాంకం framebuffer_vsync;
};

#అయితే_ముగింపు // SDL_dosvideo_h
