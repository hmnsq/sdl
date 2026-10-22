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

#اگر_غیر_تعریف_شدہ SDL_pixels_c_h_
#تعریف_کرو SDL_pixels_c_h_

// Useful functions and variables from SDL_pixel.c

#شامل "SDL_blit.h"

// The value, in nits, of scRGB 1.0
#تعریف_کرو SCRGB_NITS  80.0f

// The automatic SD/HD threshold for YUV colorspace
#تعریف_کرو YUV_SD_حد 576


// Pixel format functions
خارجی خالی SDL_Get8888_Alpha_نقاب_And_سرکاؤ(ثابت SDL_PixelFormatDetails *fmt, Uint32 *نقاب, Uint32 *سرکاؤ);
خارجی SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat pixel_format);
خارجی خالی SDL_QuitPixelFormatDetails(خالی);

// Colorspace conversion functions
خارجی اعشاری SDL_s_RGBto_خطی(اعشاری v);
خارجی اعشاری SDL_s_RGBfrom_خطی(اعشاری v);
خارجی اعشاری SDL_PQtoNits(اعشاری v);
خارجی اعشاری SDL_PQfromNits(اعشاری v);
خارجی ثابت اعشاری *SDL_Get_YCb_CRto_RGBConversion_میٹرکس(SDL_Colorspace colorspace, صحیح w, صحیح h, صحیح بٹ_فی_pixel);
خارجی ثابت اعشاری *SDL_Get_Color_Primaries_Conversion_میٹرکس(SDL_ColorPrimaries src, SDL_ColorPrimaries dst);
خارجی خالی SDL_ConvertColorPrimaries(اعشاری *fR, اعشاری *fG, اعشاری *fB, ثابت اعشاری *میٹرکس);
خارجی خالی SDL_ConvertColor709to2020(اعشاری *fR, اعشاری *fG, اعشاری *fB);

// Blit mapping functions
خارجی bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst);
خارجی خالی SDL_InvalidateMap(SDL_BlitMap *map);
خارجی bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst);

// Miscellaneous functions
خارجی bool SDL_IsSamePalette(ثابت SDL_Palette *src, ثابت SDL_Palette *dst);
خارجی خالی SDL_DitherPalette(SDL_Palette *palette);
خارجی Uint8 SDL_LookupRGBAColor(SDL_Hash_جدول *palette_map, Uint32 pixelvalue, ثابت SDL_Palette *pal);
خارجی خالی SDL_DetectPalette(ثابت SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel);
خارجی SDL_Surface *SDL_DuplicatePixels(صحیح چوڑائی, صحیح اونچائی, SDL_PixelFormat format, SDL_Colorspace colorspace, خالی *pixels, صحیح pitch);

#اگر_ختم // SDL_pixels_c_h_
