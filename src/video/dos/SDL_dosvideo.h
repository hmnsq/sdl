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

#اگر_غیر_تعریف_شدہ SDL_dosvideo_h
#تعریف_کرو SDL_dosvideo_h

#شامل "../../core/dos/SDL_dos.h"
#شامل "../SDL_sysvideo.h"
#شامل "SDL_internal.h"

ساخت SDL_Display_منوال_ڈیٹا
{
    // we can add more fields to this, if we want them, later.
    Uint16 منوال_id;
    Uint16 اوصاف;
    Uint16 pitch;
    Uint16 w;
    Uint16 h;
    Uint8 عدد_planes;
    Uint8 bpp;
    Uint8 حافظہ_model;
    Uint8 عدد_image_صفحات;
    Uint8 red_نقاب_سائز;
    Uint8 red_نقاب_pos;
    Uint8 green_نقاب_سائز;
    Uint8 green_نقاب_pos;
    Uint8 blue_نقاب_سائز;
    Uint8 blue_نقاب_pos;
    Uint32 physical_بنیاد_addr;

    // VBE 1.2 banked framebuffer fields (used when LFB is not available)
    bool has_lfb;           // true if linear framebuffer is available (VBE 2.0+)
    Uint16 win_granularity; // bank positioning granularity in KB
    Uint16 win_سائز;        // window size in KB (typically 64)
    Uint16 win_a_segment;   // real-mode segment of window A (typically 0xA000)
    Uint32 win_func_ptr;    // real-mode far pointer to bank-switch function
    Uint8 win_a_اوصاف; // window A capabilities
};

ساخت SDL_Video_ڈیٹا
{
    __dpmi_meminfo mapping; // video memory mapping.
    SDL_Display_منوال current_منوال;
    DOS_مداخلت_Hook keyboard_مداخلت_hook;
    Uint32 palette_نسخہ;       // tracks SDL_Palette::version to detect changes
    Uint16 original_vbe_منوال;     // VBE mode number at startup
    خالی *vbe_state_بفر;       // saved VBE state (from VBE 0x4F04)
    Uint32 vbe_state_بفر_سائز; // size of the state buffer

    // Mouse sensitivity (mickeys per pixel), queried from INT 33h function 0x1B
    اعشاری mickeys_فی_hpixel; // horizontal mickeys per pixel (default: 8)
    اعشاری mickeys_فی_vpixel; // vertical mickeys per pixel (default: 16)

    // Page-flipping (double-buffering) state
    صحیح current_صفحہ;         // 0 or 1: which page is currently displayed
    Uint32 صفحہ_انحراف[2];    // byte offset of each page within video memory
    bool صفحہ_flip_دستیاب; // true if mode supports double-buffering
    bool banked_منوال;         // true if current mode uses banked (not LFB) access
};

ساخت SDL_Display_ڈیٹا
{
    صحیح غیر_مستعمل; // for now
};

ساخت SDL_کھڑکی_ڈیٹا
{
    صحیح framebuffer_vsync;
};

#اگر_ختم // SDL_dosvideo_h
