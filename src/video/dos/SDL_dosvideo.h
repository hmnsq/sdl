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

#यदि_अपरिभाषितम् SDL_dosvideo_h
#परिभाषय SDL_dosvideo_h

#अन्तर्भाव "../../core/dos/SDL_dos.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "SDL_internal.h"

संरचना SDL_Display_बहुलकम्_दत्त
{
    // we can add more fields to this, if we want them, later.
    Uint16 बहुलकम्_id;
    Uint16 गुणाः;
    Uint16 pitch;
    Uint16 w;
    Uint16 h;
    Uint8 अङ्कः_planes;
    Uint8 bpp;
    Uint8 स्मृतिः_model;
    Uint8 अङ्कः_image_पृष्ठानि;
    Uint8 red_आवरणम्_आकार;
    Uint8 red_आवरणम्_pos;
    Uint8 green_आवरणम्_आकार;
    Uint8 green_आवरणम्_pos;
    Uint8 blue_आवरणम्_आकार;
    Uint8 blue_आवरणम्_pos;
    Uint32 physical_आधारः_addr;

    // VBE 1.2 banked framebuffer fields (used when LFB is not available)
    bool has_lfb;           // true if linear framebuffer is available (VBE 2.0+)
    Uint16 win_granularity; // bank positioning granularity in KB
    Uint16 win_आकार;        // window size in KB (typically 64)
    Uint16 win_a_segment;   // real-mode segment of window A (typically 0xA000)
    Uint32 win_func_ptr;    // real-mode far pointer to bank-switch function
    Uint8 win_a_गुणाः; // window A capabilities
};

संरचना SDL_Video_दत्त
{
    __dpmi_meminfo mapping; // video memory mapping.
    SDL_Display_बहुलकम् current_बहुलकम्;
    DOS_व्यवधानम्_Hook keyboard_व्यवधानम्_hook;
    Uint32 palette_संस्करणम्;       // tracks SDL_Palette::version to detect changes
    Uint16 original_vbe_बहुलकम्;     // VBE mode number at startup
    शून्य *vbe_state_बफर;       // saved VBE state (from VBE 0x4F04)
    Uint32 vbe_state_बफर_आकार; // size of the state buffer

    // Mouse sensitivity (mickeys per pixel), queried from INT 33h function 0x1B
    भिन्न mickeys_प्रत्येकम्_hpixel; // horizontal mickeys per pixel (default: 8)
    भिन्न mickeys_प्रत्येकम्_vpixel; // vertical mickeys per pixel (default: 16)

    // Page-flipping (double-buffering) state
    पूर्णाङ्क current_page;         // 0 or 1: which page is currently displayed
    Uint32 page_विस्थापनम्[2];    // byte offset of each page within video memory
    bool page_flip_उपलब्धम्; // true if mode supports double-buffering
    bool banked_बहुलकम्;         // true if current mode uses banked (not LFB) access
};

संरचना SDL_Display_दत्त
{
    पूर्णाङ्क अप्रयुक्तम्; // for now
};

संरचना SDL_गवाक्षः_दत्त
{
    पूर्णाङ्क framebuffer_vsync;
};

#यदि_अन्तः // SDL_dosvideo_h
