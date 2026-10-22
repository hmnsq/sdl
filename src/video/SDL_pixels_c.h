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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_pixels_c_h_
#define SDL_pixels_c_h_

// Useful functions and variables from SDL_pixel.c

#અન્તર્ભાવ "SDL_blit.h"

// The value, in nits, of scRGB 1.0
#define SCRGB_NITS  80.0f

// The automatic SD/HD threshold for YUV colorspace
#define YUV_SD_THRESHOLD 576


// Pixel format functions
બાહ્ય શૂન્ય SDL_Get8888AlphaMaskAndShift(અચલ SDL_PixelFormatDetails *fmt, Uint32 *mask, Uint32 *shift);
બાહ્ય SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat pixel_format);
બાહ્ય શૂન્ય SDL_QuitPixelFormatDetails(શૂન્ય);

// Colorspace conversion functions
બાહ્ય દશાંશ SDL_sRGBtoLinear(દશાંશ v);
બાહ્ય દશાંશ SDL_sRGBfromLinear(દશાંશ v);
બાહ્ય દશાંશ SDL_PQtoNits(દશાંશ v);
બાહ્ય દશાંશ SDL_PQfromNits(દશાંશ v);
બાહ્ય અચલ દશાંશ *SDL_GetYCbCRtoRGBConversionMatrix(SDL_Colorspace colorspace, પૂર્ણાંક w, પૂર્ણાંક h, પૂર્ણાંક bits_per_pixel);
બાહ્ય અચલ દશાંશ *SDL_GetColorPrimariesConversionMatrix(SDL_ColorPrimaries src, SDL_ColorPrimaries dst);
બાહ્ય શૂન્ય SDL_ConvertColorPrimaries(દશાંશ *fR, દશાંશ *fG, દશાંશ *fB, અચલ દશાંશ *matrix);
બાહ્ય શૂન્ય SDL_ConvertColor709to2020(દશાંશ *fR, દશાંશ *fG, દશાંશ *fB);

// Blit mapping functions
બાહ્ય bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst);
બાહ્ય શૂન્ય SDL_InvalidateMap(SDL_BlitMap *map);
બાહ્ય bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst);

// Miscellaneous functions
બાહ્ય bool SDL_IsSamePalette(અચલ SDL_Palette *src, અચલ SDL_Palette *dst);
બાહ્ય શૂન્ય SDL_DitherPalette(SDL_Palette *palette);
બાહ્ય Uint8 SDL_LookupRGBAColor(SDL_HashTable *palette_map, Uint32 pixelvalue, અચલ SDL_Palette *pal);
બાહ્ય શૂન્ય SDL_DetectPalette(અચલ SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel);
બાહ્ય SDL_Surface *SDL_DuplicatePixels(પૂર્ણાંક width, પૂર્ણાંક height, SDL_PixelFormat format, SDL_Colorspace colorspace, શૂન્ય *pixels, પૂર્ણાંક pitch);

#endif // SDL_pixels_c_h_
