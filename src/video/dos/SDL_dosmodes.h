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

#اگر_تعریف_نشده SDL_dosmodes_h_
#تعریف_کن SDL_dosmodes_h_

#ضمن "SDL_internal.h"

خارجي bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display);
خارجي bool DOSVESA_مجموعه_Display_نما(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_نما *نما);
خارجي bool DOSVESA_SupportsVESA(فراغ);
خارجي فراغ DOSVESA_FreeVESAInfo(فراغ);
خارجي Uint32 DOSVESA_Get_VESATotal_حافظه(فراغ);
خارجي ثابت حرف *DOSVESA_GetGPUName(فراغ);

// VGA DAC (Digital-to-Analog Converter) ports for palette programming
#تعریف_کن VGA_DAC_PIXEL_ماسک  0x3C6 // pixel mask register (read/write, VGA-only)
#تعریف_کن VGA_DAC_WRITE_شاخص 0x3C8 // write index register (set starting color index)
#تعریف_کن VGA_DAC_داده        0x3C9 // data register (write R, G, B in sequence)

// VGA Input Status Register 1 (for vblank detection)
#تعریف_کن VGA_وضعیت_پورت   0x3DA
#تعریف_کن VGA_وضعیت_VBLANK 0x08 // bit 3: vertical retrace active

// VBE window attribute bits (WinAAttributes / WinBAttributes field)
#تعریف_کن VBE_WINATTR_SUPPORTED 0x01 // bit 0: window is supported
#تعریف_کن VBE_WINATTR_WRITABLE  0x04 // bit 2: window is writable

// Combination: a usable banked window must be both supported and writable
#تعریف_کن VBE_WINATTR_USABLE (VBE_WINATTR_SUPPORTED | VBE_WINATTR_WRITABLE)

#پایان_اگر // SDL_dosmodes_h_
