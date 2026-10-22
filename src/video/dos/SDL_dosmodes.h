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

#अगर_अघोषित SDL_dosmodes_h_
#घोषणा SDL_dosmodes_h_

#समावेश "SDL_internal.h"

बाह्य bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display);
बाह्य bool DOSVESA_SetDisplayMode(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_DisplayMode *mode);
बाह्य bool DOSVESA_SupportsVESA(व्योम);
बाह्य व्योम DOSVESA_FreeVESAInfo(व्योम);
बाह्य Uint32 DOSVESA_GetVESATotalMemory(व्योम);
बाह्य स्थिर अक्षर *DOSVESA_GetGPUName(व्योम);

// VGA DAC (Digital-to-Analog Converter) ports for palette programming
#घोषणा VGA_DAC_PIXEL_MASK  0x3C6 // pixel mask register (read/write, VGA-only)
#घोषणा VGA_DAC_WRITE_सूचकांक 0x3C8 // write index register (set starting color index)
#घोषणा VGA_DAC_तथ्य        0x3C9 // data register (write R, G, B in sequence)

// VGA Input Status Register 1 (for vblank detection)
#घोषणा VGA_STATUS_PORT   0x3DA
#घोषणा VGA_STATUS_VBLANK 0x08 // bit 3: vertical retrace active

// VBE window attribute bits (WinAAttributes / WinBAttributes field)
#घोषणा VBE_WINATTR_SUPPORTED 0x01 // bit 0: window is supported
#घोषणा VBE_WINATTR_WRITABLE  0x04 // bit 2: window is writable

// Combination: a usable banked window must be both supported and writable
#घोषणा VBE_WINATTR_USABLE (VBE_WINATTR_SUPPORTED | VBE_WINATTR_WRITABLE)

#पूर्ण_अगर // SDL_dosmodes_h_
