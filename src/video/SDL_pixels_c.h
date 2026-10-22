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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_pixels_c_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_pixels_c_h_

// Useful functions and variables from SDL_pixel.c

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_blit.h"

// The value, in nits, of scRGB 1.0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SCRGB_NITS  80.0f

// The automatic SD/HD threshold for YUV colorspace
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YUV_SD_ਹੱਦ 576


// Pixel format functions
ਬਾਹਰੀ ਖਾਲੀ SDL_Get8888_Alpha_ਨਕਾਬ_And_ਖਿਸਕਾਓ(ਅਚਲ SDL_PixelFormatDetails *fmt, Uint32 *ਨਕਾਬ, Uint32 *ਖਿਸਕਾਓ);
ਬਾਹਰੀ SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat pixel_format);
ਬਾਹਰੀ ਖਾਲੀ SDL_QuitPixelFormatDetails(ਖਾਲੀ);

// Colorspace conversion functions
ਬਾਹਰੀ ਦਸ਼ਮਲਵ SDL_s_RGBto_ਰੇਖਿਕ(ਦਸ਼ਮਲਵ v);
ਬਾਹਰੀ ਦਸ਼ਮਲਵ SDL_s_RGBfrom_ਰੇਖਿਕ(ਦਸ਼ਮਲਵ v);
ਬਾਹਰੀ ਦਸ਼ਮਲਵ SDL_PQtoNits(ਦਸ਼ਮਲਵ v);
ਬਾਹਰੀ ਦਸ਼ਮਲਵ SDL_PQfromNits(ਦਸ਼ਮਲਵ v);
ਬਾਹਰੀ ਅਚਲ ਦਸ਼ਮਲਵ *SDL_Get_YCb_CRto_RGBConversion_ਮੈਟ੍ਰਿਕਸ(SDL_Colorspace colorspace, ਪੂਰਨ w, ਪੂਰਨ h, ਪੂਰਨ ਬਿੱਟ_ਪ੍ਰਤੀ_pixel);
ਬਾਹਰੀ ਅਚਲ ਦਸ਼ਮਲਵ *SDL_Get_Color_Primaries_Conversion_ਮੈਟ੍ਰਿਕਸ(SDL_ColorPrimaries src, SDL_ColorPrimaries dst);
ਬਾਹਰੀ ਖਾਲੀ SDL_ConvertColorPrimaries(ਦਸ਼ਮਲਵ *fR, ਦਸ਼ਮਲਵ *fG, ਦਸ਼ਮਲਵ *fB, ਅਚਲ ਦਸ਼ਮਲਵ *ਮੈਟ੍ਰਿਕਸ);
ਬਾਹਰੀ ਖਾਲੀ SDL_ConvertColor709to2020(ਦਸ਼ਮਲਵ *fR, ਦਸ਼ਮਲਵ *fG, ਦਸ਼ਮਲਵ *fB);

// Blit mapping functions
ਬਾਹਰੀ bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst);
ਬਾਹਰੀ ਖਾਲੀ SDL_InvalidateMap(SDL_BlitMap *map);
ਬਾਹਰੀ bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst);

// Miscellaneous functions
ਬਾਹਰੀ bool SDL_IsSamePalette(ਅਚਲ SDL_Palette *src, ਅਚਲ SDL_Palette *dst);
ਬਾਹਰੀ ਖਾਲੀ SDL_DitherPalette(SDL_Palette *palette);
ਬਾਹਰੀ Uint8 SDL_LookupRGBAColor(SDL_Hash_ਸਾਰਣੀ *palette_map, Uint32 pixelvalue, ਅਚਲ SDL_Palette *pal);
ਬਾਹਰੀ ਖਾਲੀ SDL_DetectPalette(ਅਚਲ SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel);
ਬਾਹਰੀ SDL_Surface *SDL_DuplicatePixels(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, SDL_PixelFormat format, SDL_Colorspace colorspace, ਖਾਲੀ *pixels, ਪੂਰਨ pitch);

#ਜੇ_ਅੰਤ // SDL_pixels_c_h_
