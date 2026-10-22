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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_dosvideo_h
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_dosvideo_h

#ಅನ್ತರ್ಭಾವ "../../core/dos/SDL_dos.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

ರಚನೆ SDL_Display_ಬಹುಲಕ_ದತ್ತಾಂಶ
{
    // we can add more fields to this, if we want them, later.
    Uint16 ಬಹುಲಕ_id;
    Uint16 ಗುಣಲಕ್ಷಣಗಳು;
    Uint16 pitch;
    Uint16 w;
    Uint16 h;
    Uint8 ಅಂಕೆ_planes;
    Uint8 bpp;
    Uint8 ಸ್ಮರಣೆ_model;
    Uint8 ಅಂಕೆ_image_ಪುಟಗಳು;
    Uint8 red_ಮುಖವಾಡ_ಗಾತ್ರ;
    Uint8 red_ಮುಖವಾಡ_pos;
    Uint8 green_ಮುಖವಾಡ_ಗಾತ್ರ;
    Uint8 green_ಮುಖವಾಡ_pos;
    Uint8 blue_ಮುಖವಾಡ_ಗಾತ್ರ;
    Uint8 blue_ಮುಖವಾಡ_pos;
    Uint32 physical_ತಳ_addr;

    // VBE 1.2 banked framebuffer fields (used when LFB is not available)
    bool has_lfb;           // true if linear framebuffer is available (VBE 2.0+)
    Uint16 win_granularity; // bank positioning granularity in KB
    Uint16 win_ಗಾತ್ರ;        // window size in KB (typically 64)
    Uint16 win_a_segment;   // real-mode segment of window A (typically 0xA000)
    Uint32 win_func_ptr;    // real-mode far pointer to bank-switch function
    Uint8 win_a_ಗುಣಲಕ್ಷಣಗಳು; // window A capabilities
};

ರಚನೆ SDL_Video_ದತ್ತಾಂಶ
{
    __dpmi_meminfo mapping; // video memory mapping.
    SDL_Display_ಬಹುಲಕ current_ಬಹುಲಕ;
    DOS_ಅಡಚಣೆ_Hook keyboard_ಅಡಚಣೆ_hook;
    Uint32 palette_ಆವೃತ್ತಿ;       // tracks SDL_Palette::version to detect changes
    Uint16 original_vbe_ಬಹುಲಕ;     // VBE mode number at startup
    ಶೂನ್ಯ *vbe_state_ಬಫರ್;       // saved VBE state (from VBE 0x4F04)
    Uint32 vbe_state_ಬಫರ್_ಗಾತ್ರ; // size of the state buffer

    // Mouse sensitivity (mickeys per pixel), queried from INT 33h function 0x1B
    ದಶಮಾಂಶ mickeys_ಪ್ರತಿ_hpixel; // horizontal mickeys per pixel (default: 8)
    ದಶಮಾಂಶ mickeys_ಪ್ರತಿ_vpixel; // vertical mickeys per pixel (default: 16)

    // Page-flipping (double-buffering) state
    ಪೂರ್ಣಾಂಕ current_ಪುಟ;         // 0 or 1: which page is currently displayed
    Uint32 ಪುಟ_ಸ್ಥಾನಾಂತರ[2];    // byte offset of each page within video memory
    bool ಪುಟ_flip_ಲಭ್ಯ; // true if mode supports double-buffering
    bool banked_ಬಹುಲಕ;         // true if current mode uses banked (not LFB) access
};

ರಚನೆ SDL_Display_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ ಬಳಸದ; // for now
};

ರಚನೆ SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ
{
    ಪೂರ್ಣಾಂಕ framebuffer_vsync;
};

#ಆದರೆ_ಅಂತ್ಯ // SDL_dosvideo_h
