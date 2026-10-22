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
#অন্তর্ভাব "SDL_internal.h"

#ifndef SDL_pixels_c_h_
#define SDL_pixels_c_h_

// Useful functions and variables from SDL_pixel.c

#অন্তর্ভাব "SDL_blit.h"

// The value, in nits, of scRGB 1.0
#define SCRGB_NITS  80.0f

// The automatic SD/HD threshold for YUV colorspace
#define YUV_SD_THRESHOLD 576


// Pixel format functions
বাহ্য শূন্য SDL_Get8888AlphaMaskAndShift(ধ্রুব SDL_PixelFormatDetails *fmt, Uint32 *mask, Uint32 *shift);
বাহ্য SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat pixel_format);
বাহ্য শূন্য SDL_QuitPixelFormatDetails(শূন্য);

// Colorspace conversion functions
বাহ্য ভিন্ন SDL_sRGBtoLinear(ভিন্ন v);
বাহ্য ভিন্ন SDL_sRGBfromLinear(ভিন্ন v);
বাহ্য ভিন্ন SDL_PQtoNits(ভিন্ন v);
বাহ্য ভিন্ন SDL_PQfromNits(ভিন্ন v);
বাহ্য ধ্রুব ভিন্ন *SDL_GetYCbCRtoRGBConversionMatrix(SDL_Colorspace colorspace, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h, পূর্ণাঙ্ক bits_per_pixel);
বাহ্য ধ্রুব ভিন্ন *SDL_GetColorPrimariesConversionMatrix(SDL_ColorPrimaries src, SDL_ColorPrimaries dst);
বাহ্য শূন্য SDL_ConvertColorPrimaries(ভিন্ন *fR, ভিন্ন *fG, ভিন্ন *fB, ধ্রুব ভিন্ন *matrix);
বাহ্য শূন্য SDL_ConvertColor709to2020(ভিন্ন *fR, ভিন্ন *fG, ভিন্ন *fB);

// Blit mapping functions
বাহ্য bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst);
বাহ্য শূন্য SDL_InvalidateMap(SDL_BlitMap *map);
বাহ্য bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst);

// Miscellaneous functions
বাহ্য bool SDL_IsSamePalette(ধ্রুব SDL_Palette *src, ধ্রুব SDL_Palette *dst);
বাহ্য শূন্য SDL_DitherPalette(SDL_Palette *palette);
বাহ্য Uint8 SDL_LookupRGBAColor(SDL_HashTable *palette_map, Uint32 pixelvalue, ধ্রুব SDL_Palette *pal);
বাহ্য শূন্য SDL_DetectPalette(ধ্রুব SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel);
বাহ্য SDL_Surface *SDL_DuplicatePixels(পূর্ণাঙ্ক width, পূর্ণাঙ্ক height, SDL_PixelFormat format, SDL_Colorspace colorspace, শূন্য *pixels, পূর্ণাঙ্ক pitch);

#endif // SDL_pixels_c_h_
