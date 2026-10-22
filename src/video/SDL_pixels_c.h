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
#ضمن "SDL_internal.h"

#جے_بنا_تعریف SDL_pixels_c_h_
#تعریف_کرو SDL_pixels_c_h_

// Useful functions and variables from SDL_pixel.c

#ضمن "SDL_blit.h"

// The value, in nits, of scRGB 1.0
#تعریف_کرو SCRGB_NITS  80.0f

// The automatic SD/HD threshold for YUV colorspace
#تعریف_کرو YUV_SD_حد 576


// Pixel format functions
خارجي فراغ SDL_Get8888_Alpha_نقاب_And_کھسکاؤ(ثابت SDL_PixelFormatDetails *fmt, Uint32 *نقاب, Uint32 *کھسکاؤ);
خارجي SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat pixel_format);
خارجي فراغ SDL_QuitPixelFormatDetails(فراغ);

// Colorspace conversion functions
خارجي عائم SDL_s_RGBto_خطی(عائم v);
خارجي عائم SDL_s_RGBfrom_خطی(عائم v);
خارجي عائم SDL_PQtoNits(عائم v);
خارجي عائم SDL_PQfromNits(عائم v);
خارجي ثابت عائم *SDL_Get_YCb_CRto_RGBConversion_میٹرکس(SDL_Colorspace colorspace, صحيح w, صحيح h, صحيح بٹ_فی_pixel);
خارجي ثابت عائم *SDL_Get_Color_Primaries_Conversion_میٹرکس(SDL_ColorPrimaries src, SDL_ColorPrimaries dst);
خارجي فراغ SDL_ConvertColorPrimaries(عائم *fR, عائم *fG, عائم *fB, ثابت عائم *میٹرکس);
خارجي فراغ SDL_ConvertColor709to2020(عائم *fR, عائم *fG, عائم *fB);

// Blit mapping functions
خارجي bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst);
خارجي فراغ SDL_InvalidateMap(SDL_BlitMap *map);
خارجي bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst);

// Miscellaneous functions
خارجي bool SDL_IsSamePalette(ثابت SDL_Palette *src, ثابت SDL_Palette *dst);
خارجي فراغ SDL_DitherPalette(SDL_Palette *palette);
خارجي Uint8 SDL_LookupRGBAColor(SDL_Hash_جدول *palette_map, Uint32 pixelvalue, ثابت SDL_Palette *pal);
خارجي فراغ SDL_DetectPalette(ثابت SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel);
خارجي SDL_Surface *SDL_DuplicatePixels(صحيح چوڑائی, صحيح اچائی, SDL_PixelFormat format, SDL_Colorspace colorspace, فراغ *pixels, صحيح pitch);

#جے_انت // SDL_pixels_c_h_
