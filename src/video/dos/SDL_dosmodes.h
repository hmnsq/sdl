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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_dosmodes_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_dosmodes_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

ਬਾਹਰੀ bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display);
ਬਾਹਰੀ bool DOSVESA_ਸੈੱਟ_Display_ਬਹੁਲਕ(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_ਬਹੁਲਕ *ਬਹੁਲਕ);
ਬਾਹਰੀ bool DOSVESA_SupportsVESA(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ DOSVESA_FreeVESAInfo(ਖਾਲੀ);
ਬਾਹਰੀ Uint32 DOSVESA_Get_VESATotal_ਸਮ੍ਰਿਤੀ(ਖਾਲੀ);
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *DOSVESA_GetGPUName(ਖਾਲੀ);

// VGA DAC (Digital-to-Analog Converter) ports for palette programming
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VGA_DAC_PIXEL_ਨਕਾਬ  0x3C6 // pixel mask register (read/write, VGA-only)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VGA_DAC_WRITE_ਸੂਚਕਾਂਕ 0x3C8 // write index register (set starting color index)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VGA_DAC_ਅੰਕੜੇ        0x3C9 // data register (write R, G, B in sequence)

// VGA Input Status Register 1 (for vblank detection)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VGA_ਸਥਿਤੀ_ਪੋਰਟ   0x3DA
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VGA_ਸਥਿਤੀ_VBLANK 0x08 // bit 3: vertical retrace active

// VBE window attribute bits (WinAAttributes / WinBAttributes field)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_WINATTR_SUPPORTED 0x01 // bit 0: window is supported
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_WINATTR_WRITABLE  0x04 // bit 2: window is writable

// Combination: a usable banked window must be both supported and writable
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VBE_WINATTR_USABLE (VBE_WINATTR_SUPPORTED | VBE_WINATTR_WRITABLE)

#ਜੇ_ਅੰਤ // SDL_dosmodes_h_
