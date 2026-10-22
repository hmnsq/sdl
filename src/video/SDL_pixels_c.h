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
#شامل "SDL_internal.h"

#ifndef SDL_pixels_c_h_
#define SDL_pixels_c_h_

// Useful functions and variables from SDL_pixel.c

#شامل "SDL_blit.h"

// The value, in nits, of scRGB 1.0
#define SCRGB_NITS  80.0f

// The automatic SD/HD threshold for YUV colorspace
#define YUV_SD_THRESHOLD 576


// Pixel format functions
بیرونی تهی SDL_Get8888AlphaMaskAndShift(ثابت SDL_PixelFormatDetails *fmt, Uint32 *mask, Uint32 *shift);
بیرونی SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat pixel_format);
بیرونی تهی SDL_QuitPixelFormatDetails(تهی);

// Colorspace conversion functions
بیرونی اعشاری SDL_sRGBtoLinear(اعشاری v);
بیرونی اعشاری SDL_sRGBfromLinear(اعشاری v);
بیرونی اعشاری SDL_PQtoNits(اعشاری v);
بیرونی اعشاری SDL_PQfromNits(اعشاری v);
بیرونی ثابت اعشاری *SDL_GetYCbCRtoRGBConversionMatrix(SDL_Colorspace colorspace, صحیح w, صحیح h, صحیح bits_per_pixel);
بیرونی ثابت اعشاری *SDL_GetColorPrimariesConversionMatrix(SDL_ColorPrimaries src, SDL_ColorPrimaries dst);
بیرونی تهی SDL_ConvertColorPrimaries(اعشاری *fR, اعشاری *fG, اعشاری *fB, ثابت اعشاری *matrix);
بیرونی تهی SDL_ConvertColor709to2020(اعشاری *fR, اعشاری *fG, اعشاری *fB);

// Blit mapping functions
بیرونی bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst);
بیرونی تهی SDL_InvalidateMap(SDL_BlitMap *map);
بیرونی bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst);

// Miscellaneous functions
بیرونی bool SDL_IsSamePalette(ثابت SDL_Palette *src, ثابت SDL_Palette *dst);
بیرونی تهی SDL_DitherPalette(SDL_Palette *palette);
بیرونی Uint8 SDL_LookupRGBAColor(SDL_HashTable *palette_map, Uint32 pixelvalue, ثابت SDL_Palette *pal);
بیرونی تهی SDL_DetectPalette(ثابت SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel);
بیرونی SDL_Surface *SDL_DuplicatePixels(صحیح width, صحیح height, SDL_PixelFormat format, SDL_Colorspace colorspace, تهی *pixels, صحیح pitch);

#endif // SDL_pixels_c_h_
