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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_pixels_c_h_
#define SDL_pixels_c_h_

// Useful functions and variables from SDL_pixel.c

#ಅನ್ತರ್ಭಾವ "SDL_blit.h"

// The value, in nits, of scRGB 1.0
#define SCRGB_NITS  80.0f

// The automatic SD/HD threshold for YUV colorspace
#define YUV_SD_THRESHOLD 576


// Pixel format functions
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Get8888AlphaMaskAndShift(ಧ್ರುವ SDL_PixelFormatDetails *fmt, Uint32 *mask, Uint32 *shift);
ಬಾಹ್ಯ SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat pixel_format);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_QuitPixelFormatDetails(ಶೂನ್ಯ);

// Colorspace conversion functions
ಬಾಹ್ಯ ಭಿನ್ನ SDL_sRGBtoLinear(ಭಿನ್ನ v);
ಬಾಹ್ಯ ಭಿನ್ನ SDL_sRGBfromLinear(ಭಿನ್ನ v);
ಬಾಹ್ಯ ಭಿನ್ನ SDL_PQtoNits(ಭಿನ್ನ v);
ಬಾಹ್ಯ ಭಿನ್ನ SDL_PQfromNits(ಭಿನ್ನ v);
ಬಾಹ್ಯ ಧ್ರುವ ಭಿನ್ನ *SDL_GetYCbCRtoRGBConversionMatrix(SDL_Colorspace colorspace, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, ಪೂರ್ಣಾಙ್ಕ bits_per_pixel);
ಬಾಹ್ಯ ಧ್ರುವ ಭಿನ್ನ *SDL_GetColorPrimariesConversionMatrix(SDL_ColorPrimaries src, SDL_ColorPrimaries dst);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ConvertColorPrimaries(ಭಿನ್ನ *fR, ಭಿನ್ನ *fG, ಭಿನ್ನ *fB, ಧ್ರುವ ಭಿನ್ನ *matrix);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ConvertColor709to2020(ಭಿನ್ನ *fR, ಭಿನ್ನ *fG, ಭಿನ್ನ *fB);

// Blit mapping functions
ಬಾಹ್ಯ bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_InvalidateMap(SDL_BlitMap *map);
ಬಾಹ್ಯ bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst);

// Miscellaneous functions
ಬಾಹ್ಯ bool SDL_IsSamePalette(ಧ್ರುವ SDL_Palette *src, ಧ್ರುವ SDL_Palette *dst);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_DitherPalette(SDL_Palette *palette);
ಬಾಹ್ಯ Uint8 SDL_LookupRGBAColor(SDL_HashTable *palette_map, Uint32 pixelvalue, ಧ್ರುವ SDL_Palette *pal);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_DetectPalette(ಧ್ರುವ SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel);
ಬಾಹ್ಯ SDL_Surface *SDL_DuplicatePixels(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat format, SDL_Colorspace colorspace, ಶೂನ್ಯ *pixels, ಪೂರ್ಣಾಙ್ಕ pitch);

#endif // SDL_pixels_c_h_
