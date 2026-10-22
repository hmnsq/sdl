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

#اگر_تعریف_نشده SDL_dosvideo_h
#تعریف_کن SDL_dosvideo_h

#ضمن "../../core/dos/SDL_dos.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_internal.h"

بنية SDL_Display_نما_داده
{
    // we can add more fields to this, if we want them, later.
    Uint16 نما_id;
    Uint16 صفات;
    Uint16 pitch;
    Uint16 w;
    Uint16 h;
    Uint8 رقم_planes;
    Uint8 bpp;
    Uint8 حافظه_model;
    Uint8 رقم_image_صفحات;
    Uint8 red_ماسک_اندازه;
    Uint8 red_ماسک_pos;
    Uint8 green_ماسک_اندازه;
    Uint8 green_ماسک_pos;
    Uint8 blue_ماسک_اندازه;
    Uint8 blue_ماسک_pos;
    Uint32 physical_پایه_addr;

    // VBE 1.2 banked framebuffer fields (used when LFB is not available)
    bool has_lfb;           // true if linear framebuffer is available (VBE 2.0+)
    Uint16 win_granularity; // bank positioning granularity in KB
    Uint16 win_اندازه;        // window size in KB (typically 64)
    Uint16 win_a_segment;   // real-mode segment of window A (typically 0xA000)
    Uint32 win_func_ptr;    // real-mode far pointer to bank-switch function
    Uint8 win_a_صفات; // window A capabilities
};

بنية SDL_Video_داده
{
    __dpmi_meminfo mapping; // video memory mapping.
    SDL_Display_نما current_نما;
    DOS_وقفه_Hook keyboard_وقفه_hook;
    Uint32 palette_نسخه;       // tracks SDL_Palette::version to detect changes
    Uint16 original_vbe_نما;     // VBE mode number at startup
    فراغ *vbe_state_میانگیر;       // saved VBE state (from VBE 0x4F04)
    Uint32 vbe_state_میانگیر_اندازه; // size of the state buffer

    // Mouse sensitivity (mickeys per pixel), queried from INT 33h function 0x1B
    عائم mickeys_در_هر_hpixel; // horizontal mickeys per pixel (default: 8)
    عائم mickeys_در_هر_vpixel; // vertical mickeys per pixel (default: 16)

    // Page-flipping (double-buffering) state
    صحيح current_صفحه;         // 0 or 1: which page is currently displayed
    Uint32 صفحه_جابه_جایی[2];    // byte offset of each page within video memory
    bool صفحه_flip_موجود; // true if mode supports double-buffering
    bool banked_نما;         // true if current mode uses banked (not LFB) access
};

بنية SDL_Display_داده
{
    صحيح استفادهنشده; // for now
};

بنية SDL_پنجره_داده
{
    صحيح framebuffer_vsync;
};

#پایان_اگر // SDL_dosvideo_h
