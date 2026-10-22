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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_pixels_c_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_pixels_c_h_

// Useful functions and variables from SDL_pixel.c

#ಅನ್ತರ್ಭಾವ "SDL_blit.h"

// The value, in nits, of scRGB 1.0
#ವ್ಯಾಖ್ಯಾನಿಸು SCRGB_NITS  80.0f

// The automatic SD/HD threshold for YUV colorspace
#ವ್ಯಾಖ್ಯಾನಿಸು YUV_SD_ಮಿತಿ 576


// Pixel format functions
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_Get8888_Alpha_ಮುಖವಾಡ_And_ಸರಿಸು(ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *fmt, Uint32 *ಮುಖವಾಡ, Uint32 *ಸರಿಸು);
ಬಾಹ್ಯ SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat pixel_format);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_QuitPixelFormatDetails(ಶೂನ್ಯ);

// Colorspace conversion functions
ಬಾಹ್ಯ ದಶಮಾಂಶ SDL_s_RGBto_ರೇಖೀಯ(ದಶಮಾಂಶ v);
ಬಾಹ್ಯ ದಶಮಾಂಶ SDL_s_RGBfrom_ರೇಖೀಯ(ದಶಮಾಂಶ v);
ಬಾಹ್ಯ ದಶಮಾಂಶ SDL_PQtoNits(ದಶಮಾಂಶ v);
ಬಾಹ್ಯ ದಶಮಾಂಶ SDL_PQfromNits(ದಶಮಾಂಶ v);
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *SDL_Get_YCb_CRto_RGBConversion_ಮಾತೃಕೆ(SDL_Colorspace colorspace, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel);
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *SDL_Get_Color_Primaries_Conversion_ಮಾತೃಕೆ(SDL_ColorPrimaries src, SDL_ColorPrimaries dst);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ConvertColorPrimaries(ದಶಮಾಂಶ *fR, ದಶಮಾಂಶ *fG, ದಶಮಾಂಶ *fB, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *ಮಾತೃಕೆ);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_ConvertColor709to2020(ದಶಮಾಂಶ *fR, ದಶಮಾಂಶ *fG, ದಶಮಾಂಶ *fB);

// Blit mapping functions
ಬಾಹ್ಯ bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_InvalidateMap(SDL_BlitMap *map);
ಬಾಹ್ಯ bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst);

// Miscellaneous functions
ಬಾಹ್ಯ bool SDL_IsSamePalette(ಸ್ಥಿರಾಂಕ SDL_Palette *src, ಸ್ಥಿರಾಂಕ SDL_Palette *dst);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_DitherPalette(SDL_Palette *palette);
ಬಾಹ್ಯ Uint8 SDL_LookupRGBAColor(SDL_Hash_ಕೋಷ್ಟಕ *palette_map, Uint32 pixelvalue, ಸ್ಥಿರಾಂಕ SDL_Palette *pal);
ಬಾಹ್ಯ ಶೂನ್ಯ SDL_DetectPalette(ಸ್ಥಿರಾಂಕ SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel);
ಬಾಹ್ಯ SDL_Surface *SDL_DuplicatePixels(ಪೂರ್ಣಾಂಕ ಅಗಲ, ಪೂರ್ಣಾಂಕ ಎತ್ತರ, SDL_PixelFormat format, SDL_Colorspace colorspace, ಶೂನ್ಯ *pixels, ಪೂರ್ಣಾಂಕ pitch);

#ಆದರೆ_ಅಂತ್ಯ // SDL_pixels_c_h_
