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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_pixels_c_h_
#నిర్వచించు SDL_pixels_c_h_

// Useful functions and variables from SDL_pixel.c

#అన్తర్భావ "SDL_blit.h"

// The value, in nits, of scRGB 1.0
#నిర్వచించు SCRGB_NITS  80.0f

// The automatic SD/HD threshold for YUV colorspace
#నిర్వచించు YUV_SD_పరిమితి 576


// Pixel format functions
బాహ్య శూన్య SDL_Get8888_Alpha_ముసుగు_And_జరుపు(స్థిరరాశి SDL_PixelFormatDetails *fmt, Uint32 *ముసుగు, Uint32 *జరుపు);
బాహ్య SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat pixel_format);
బాహ్య శూన్య SDL_QuitPixelFormatDetails(శూన్య);

// Colorspace conversion functions
బాహ్య దశాంశం SDL_s_RGBto_రేఖీయ(దశాంశం v);
బాహ్య దశాంశం SDL_s_RGBfrom_రేఖీయ(దశాంశం v);
బాహ్య దశాంశం SDL_PQtoNits(దశాంశం v);
బాహ్య దశాంశం SDL_PQfromNits(దశాంశం v);
బాహ్య స్థిరరాశి దశాంశం *SDL_Get_YCb_CRto_RGBConversion_మాతృక(SDL_Colorspace colorspace, పూర్ణాంకం w, పూర్ణాంకం h, పూర్ణాంకం బిట్లు_చొప్పున_pixel);
బాహ్య స్థిరరాశి దశాంశం *SDL_Get_Color_Primaries_Conversion_మాతృక(SDL_ColorPrimaries src, SDL_ColorPrimaries dst);
బాహ్య శూన్య SDL_ConvertColorPrimaries(దశాంశం *fR, దశాంశం *fG, దశాంశం *fB, స్థిరరాశి దశాంశం *మాతృక);
బాహ్య శూన్య SDL_ConvertColor709to2020(దశాంశం *fR, దశాంశం *fG, దశాంశం *fB);

// Blit mapping functions
బాహ్య bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst);
బాహ్య శూన్య SDL_InvalidateMap(SDL_BlitMap *map);
బాహ్య bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst);

// Miscellaneous functions
బాహ్య bool SDL_IsSamePalette(స్థిరరాశి SDL_Palette *src, స్థిరరాశి SDL_Palette *dst);
బాహ్య శూన్య SDL_DitherPalette(SDL_Palette *palette);
బాహ్య Uint8 SDL_LookupRGBAColor(SDL_Hash_పట్టిక *palette_map, Uint32 pixelvalue, స్థిరరాశి SDL_Palette *pal);
బాహ్య శూన్య SDL_DetectPalette(స్థిరరాశి SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel);
బాహ్య SDL_Surface *SDL_DuplicatePixels(పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, SDL_PixelFormat format, SDL_Colorspace colorspace, శూన్య *pixels, పూర్ణాంకం pitch);

#అయితే_ముగింపు // SDL_pixels_c_h_
