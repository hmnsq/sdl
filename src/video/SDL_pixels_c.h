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
#अन्तर्भाव "SDL_internal.h"

#ifndef SDL_pixels_c_h_
#define SDL_pixels_c_h_

// Useful functions and variables from SDL_pixel.c

#अन्तर्भाव "SDL_blit.h"

// The value, in nits, of scRGB 1.0
#define SCRGB_NITS  80.0f

// The automatic SD/HD threshold for YUV colorspace
#define YUV_SD_THRESHOLD 576


// Pixel format functions
बाह्य शून्य SDL_Get8888AlphaMaskAndShift(ध्रुव SDL_PixelFormatDetails *fmt, Uint32 *mask, Uint32 *shift);
बाह्य SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat pixel_format);
बाह्य शून्य SDL_QuitPixelFormatDetails(शून्य);

// Colorspace conversion functions
बाह्य भिन्न SDL_sRGBtoLinear(भिन्न v);
बाह्य भिन्न SDL_sRGBfromLinear(भिन्न v);
बाह्य भिन्न SDL_PQtoNits(भिन्न v);
बाह्य भिन्न SDL_PQfromNits(भिन्न v);
बाह्य ध्रुव भिन्न *SDL_GetYCbCRtoRGBConversionMatrix(SDL_Colorspace colorspace, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क bits_per_pixel);
बाह्य ध्रुव भिन्न *SDL_GetColorPrimariesConversionMatrix(SDL_ColorPrimaries src, SDL_ColorPrimaries dst);
बाह्य शून्य SDL_ConvertColorPrimaries(भिन्न *fR, भिन्न *fG, भिन्न *fB, ध्रुव भिन्न *matrix);
बाह्य शून्य SDL_ConvertColor709to2020(भिन्न *fR, भिन्न *fG, भिन्न *fB);

// Blit mapping functions
बाह्य bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst);
बाह्य शून्य SDL_InvalidateMap(SDL_BlitMap *map);
बाह्य bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst);

// Miscellaneous functions
बाह्य bool SDL_IsSamePalette(ध्रुव SDL_Palette *src, ध्रुव SDL_Palette *dst);
बाह्य शून्य SDL_DitherPalette(SDL_Palette *palette);
बाह्य Uint8 SDL_LookupRGBAColor(SDL_HashTable *palette_map, Uint32 pixelvalue, ध्रुव SDL_Palette *pal);
बाह्य शून्य SDL_DetectPalette(ध्रुव SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel);
बाह्य SDL_Surface *SDL_DuplicatePixels(पूर्णाङ्क width, पूर्णाङ्क height, SDL_PixelFormat format, SDL_Colorspace colorspace, शून्य *pixels, पूर्णाङ्क pitch);

#endif // SDL_pixels_c_h_
