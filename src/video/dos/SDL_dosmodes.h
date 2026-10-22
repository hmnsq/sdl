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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_dosmodes_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_dosmodes_h_

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

ಬಾಹ್ಯ bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display);
ಬಾಹ್ಯ bool DOSVESA_ಗಣ_Display_ಬಹುಲಕ(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_ಬಹುಲಕ *ಬಹುಲಕ);
ಬಾಹ್ಯ bool DOSVESA_SupportsVESA(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ DOSVESA_FreeVESAInfo(ಶೂನ್ಯ);
ಬಾಹ್ಯ Uint32 DOSVESA_Get_VESATotal_ಸ್ಮರಣೆ(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *DOSVESA_GetGPUName(ಶೂನ್ಯ);

// VGA DAC (Digital-to-Analog Converter) ports for palette programming
#ವ್ಯಾಖ್ಯಾನಿಸು VGA_DAC_PIXEL_ಮುಖವಾಡ  0x3C6 // pixel mask register (read/write, VGA-only)
#ವ್ಯಾಖ್ಯಾನಿಸು VGA_DAC_WRITE_ಸೂಚ್ಯಂಕ 0x3C8 // write index register (set starting color index)
#ವ್ಯಾಖ್ಯಾನಿಸು VGA_DAC_ದತ್ತಾಂಶ        0x3C9 // data register (write R, G, B in sequence)

// VGA Input Status Register 1 (for vblank detection)
#ವ್ಯಾಖ್ಯಾನಿಸು VGA_ಸ್ಥಿತಿ_ಪೋರ್ಟ್   0x3DA
#ವ್ಯಾಖ್ಯಾನಿಸು VGA_ಸ್ಥಿತಿ_VBLANK 0x08 // bit 3: vertical retrace active

// VBE window attribute bits (WinAAttributes / WinBAttributes field)
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_WINATTR_SUPPORTED 0x01 // bit 0: window is supported
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_WINATTR_WRITABLE  0x04 // bit 2: window is writable

// Combination: a usable banked window must be both supported and writable
#ವ್ಯಾಖ್ಯಾನಿಸು VBE_WINATTR_USABLE (VBE_WINATTR_SUPPORTED | VBE_WINATTR_WRITABLE)

#ಆದರೆ_ಅಂತ್ಯ // SDL_dosmodes_h_
