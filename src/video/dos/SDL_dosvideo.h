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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_dosvideo_h
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_dosvideo_h

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/dos/SDL_dos.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

ਬਣਤਰ SDL_Display_ਬਹੁਲਕ_ਅੰਕੜੇ
{
    // we can add more fields to this, if we want them, later.
    Uint16 ਬਹੁਲਕ_id;
    Uint16 ਗੁਣ;
    Uint16 pitch;
    Uint16 w;
    Uint16 h;
    Uint8 ਅੰਕ_planes;
    Uint8 bpp;
    Uint8 ਸਮ੍ਰਿਤੀ_model;
    Uint8 ਅੰਕ_image_ਪੰਨੇ;
    Uint8 red_ਨਕਾਬ_ਮਾਪ;
    Uint8 red_ਨਕਾਬ_pos;
    Uint8 green_ਨਕਾਬ_ਮਾਪ;
    Uint8 green_ਨਕਾਬ_pos;
    Uint8 blue_ਨਕਾਬ_ਮਾਪ;
    Uint8 blue_ਨਕਾਬ_pos;
    Uint32 physical_ਅਧਾਰ_addr;

    // VBE 1.2 banked framebuffer fields (used when LFB is not available)
    bool has_lfb;           // true if linear framebuffer is available (VBE 2.0+)
    Uint16 win_granularity; // bank positioning granularity in KB
    Uint16 win_ਮਾਪ;        // window size in KB (typically 64)
    Uint16 win_a_segment;   // real-mode segment of window A (typically 0xA000)
    Uint32 win_func_ptr;    // real-mode far pointer to bank-switch function
    Uint8 win_a_ਗੁਣ; // window A capabilities
};

ਬਣਤਰ SDL_Video_ਅੰਕੜੇ
{
    __dpmi_meminfo mapping; // video memory mapping.
    SDL_Display_ਬਹੁਲਕ current_ਬਹੁਲਕ;
    DOS_ਰੁਕਾਵਟ_Hook keyboard_ਰੁਕਾਵਟ_hook;
    Uint32 palette_ਸੰਸਕਰਣ;       // tracks SDL_Palette::version to detect changes
    Uint16 original_vbe_ਬਹੁਲਕ;     // VBE mode number at startup
    ਖਾਲੀ *vbe_state_ਬਫਰ;       // saved VBE state (from VBE 0x4F04)
    Uint32 vbe_state_ਬਫਰ_ਮਾਪ; // size of the state buffer

    // Mouse sensitivity (mickeys per pixel), queried from INT 33h function 0x1B
    ਦਸ਼ਮਲਵ mickeys_ਪ੍ਰਤੀ_hpixel; // horizontal mickeys per pixel (default: 8)
    ਦਸ਼ਮਲਵ mickeys_ਪ੍ਰਤੀ_vpixel; // vertical mickeys per pixel (default: 16)

    // Page-flipping (double-buffering) state
    ਪੂਰਨ current_ਪੰਨਾ;         // 0 or 1: which page is currently displayed
    Uint32 ਪੰਨਾ_ਵਿੱਥ[2];    // byte offset of each page within video memory
    bool ਪੰਨਾ_flip_ਉਪਲਬਧ; // true if mode supports double-buffering
    bool banked_ਬਹੁਲਕ;         // true if current mode uses banked (not LFB) access
};

ਬਣਤਰ SDL_Display_ਅੰਕੜੇ
{
    ਪੂਰਨ ਅਣਵਰਤਿਆ; // for now
};

ਬਣਤਰ SDL_ਖਿੜਕੀ_ਅੰਕੜੇ
{
    ਪੂਰਨ framebuffer_vsync;
};

#ਜੇ_ਅੰਤ // SDL_dosvideo_h
