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

#جيڪڏهن_وصف_نه_ٿيل SDL_dosmodes_h_
#وصف_ڪريو SDL_dosmodes_h_

#ضمن "SDL_internal.h"

خارجي bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display);
خارجي bool DOSVESA_سيٽ_Display_گهڻائي(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_گهڻائي *گهڻائي);
خارجي bool DOSVESA_SupportsVESA(فراغ);
خارجي فراغ DOSVESA_FreeVESAInfo(فراغ);
خارجي Uint32 DOSVESA_Get_VESATotal_يادگيري(فراغ);
خارجي ثابت حرف *DOSVESA_GetGPUName(فراغ);

// VGA DAC (Digital-to-Analog Converter) ports for palette programming
#وصف_ڪريو VGA_DAC_PIXEL_نقاب  0x3C6 // pixel mask register (read/write, VGA-only)
#وصف_ڪريو VGA_DAC_WRITE_اشاريو 0x3C8 // write index register (set starting color index)
#وصف_ڪريو VGA_DAC_معلومات        0x3C9 // data register (write R, G, B in sequence)

// VGA Input Status Register 1 (for vblank detection)
#وصف_ڪريو VGA_حالت_پورٽ   0x3DA
#وصف_ڪريو VGA_حالت_VBLANK 0x08 // bit 3: vertical retrace active

// VBE window attribute bits (WinAAttributes / WinBAttributes field)
#وصف_ڪريو VBE_WINATTR_SUPPORTED 0x01 // bit 0: window is supported
#وصف_ڪريو VBE_WINATTR_WRITABLE  0x04 // bit 2: window is writable

// Combination: a usable banked window must be both supported and writable
#وصف_ڪريو VBE_WINATTR_USABLE (VBE_WINATTR_SUPPORTED | VBE_WINATTR_WRITABLE)

#جيڪڏهن_پورو // SDL_dosmodes_h_
