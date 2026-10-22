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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_pixels_c_h_
#define SDL_pixels_c_h_

// Useful functions and variables from SDL_pixel.c

#ଅନ୍ତର୍ଭାଵ "SDL_blit.h"

// The value, in nits, of scRGB 1.0
#define SCRGB_NITS  80.0f

// The automatic SD/HD threshold for YUV colorspace
#define YUV_SD_THRESHOLD 576


// Pixel format functions
ବାହ୍ୟ ଶୂନ୍ୟ SDL_Get8888AlphaMaskAndShift(ଅଚଳ SDL_PixelFormatDetails *fmt, Uint32 *mask, Uint32 *shift);
ବାହ୍ୟ SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat pixel_format);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_QuitPixelFormatDetails(ଶୂନ୍ୟ);

// Colorspace conversion functions
ବାହ୍ୟ ଦଶମିକ SDL_sRGBtoLinear(ଦଶମିକ v);
ବାହ୍ୟ ଦଶମିକ SDL_sRGBfromLinear(ଦଶମିକ v);
ବାହ୍ୟ ଦଶମିକ SDL_PQtoNits(ଦଶମିକ v);
ବାହ୍ୟ ଦଶମିକ SDL_PQfromNits(ଦଶମିକ v);
ବାହ୍ୟ ଅଚଳ ଦଶମିକ *SDL_GetYCbCRtoRGBConversionMatrix(SDL_Colorspace colorspace, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, ପୂର୍ଣ୍ଣସଂଖ୍ୟା bits_per_pixel);
ବାହ୍ୟ ଅଚଳ ଦଶମିକ *SDL_GetColorPrimariesConversionMatrix(SDL_ColorPrimaries src, SDL_ColorPrimaries dst);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_ConvertColorPrimaries(ଦଶମିକ *fR, ଦଶମିକ *fG, ଦଶମିକ *fB, ଅଚଳ ଦଶମିକ *matrix);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_ConvertColor709to2020(ଦଶମିକ *fR, ଦଶମିକ *fG, ଦଶମିକ *fB);

// Blit mapping functions
ବାହ୍ୟ bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_InvalidateMap(SDL_BlitMap *map);
ବାହ୍ୟ bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst);

// Miscellaneous functions
ବାହ୍ୟ bool SDL_IsSamePalette(ଅଚଳ SDL_Palette *src, ଅଚଳ SDL_Palette *dst);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_DitherPalette(SDL_Palette *palette);
ବାହ୍ୟ Uint8 SDL_LookupRGBAColor(SDL_HashTable *palette_map, Uint32 pixelvalue, ଅଚଳ SDL_Palette *pal);
ବାହ୍ୟ ଶୂନ୍ୟ SDL_DetectPalette(ଅଚଳ SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel);
ବାହ୍ୟ SDL_Surface *SDL_DuplicatePixels(ପୂର୍ଣ୍ଣସଂଖ୍ୟା width, ପୂର୍ଣ୍ଣସଂଖ୍ୟା height, SDL_PixelFormat format, SDL_Colorspace colorspace, ଶୂନ୍ୟ *pixels, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch);

#endif // SDL_pixels_c_h_
