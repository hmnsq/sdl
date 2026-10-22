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

#నిర్వచితం_కాకపోతే SDL_dosmodes_h_
#నిర్వచించు SDL_dosmodes_h_

#అన్తర్భావ "SDL_internal.h"

బాహ్య bool DOSVESA_GetDisplayModes(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display);
బాహ్య bool DOSVESA_సమితి_Display_బహుళకం(SDL_VideoDevice *device, SDL_VideoDisplay *sdl_display, SDL_Display_బహుళకం *బహుళకం);
బాహ్య bool DOSVESA_SupportsVESA(శూన్య);
బాహ్య శూన్య DOSVESA_FreeVESAInfo(శూన్య);
బాహ్య Uint32 DOSVESA_Get_VESATotal_జ్ఞాపకం(శూన్య);
బాహ్య స్థిరరాశి అక్షరం *DOSVESA_GetGPUName(శూన్య);

// VGA DAC (Digital-to-Analog Converter) ports for palette programming
#నిర్వచించు VGA_DAC_PIXEL_ముసుగు  0x3C6 // pixel mask register (read/write, VGA-only)
#నిర్వచించు VGA_DAC_WRITE_సూచీ 0x3C8 // write index register (set starting color index)
#నిర్వచించు VGA_DAC_దత్తాంశం        0x3C9 // data register (write R, G, B in sequence)

// VGA Input Status Register 1 (for vblank detection)
#నిర్వచించు VGA_స్థితి_పోర్టు   0x3DA
#నిర్వచించు VGA_స్థితి_VBLANK 0x08 // bit 3: vertical retrace active

// VBE window attribute bits (WinAAttributes / WinBAttributes field)
#నిర్వచించు VBE_WINATTR_SUPPORTED 0x01 // bit 0: window is supported
#నిర్వచించు VBE_WINATTR_WRITABLE  0x04 // bit 2: window is writable

// Combination: a usable banked window must be both supported and writable
#నిర్వచించు VBE_WINATTR_USABLE (VBE_WINATTR_SUPPORTED | VBE_WINATTR_WRITABLE)

#అయితే_ముగింపు // SDL_dosmodes_h_
