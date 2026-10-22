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

#ifndef SDL_yuv_c_h_
#define SDL_yuv_c_h_

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

// YUV conversion functions

ಬಾಹ್ಯ bool SDL_ConvertPixels_YUV_to_RGB(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch);
ಬಾಹ್ಯ bool SDL_ConvertPixels_RGB_to_YUV(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch);
ಬಾಹ್ಯ bool SDL_ConvertPixels_YUV_to_YUV(ಪೂರ್ಣಾಙ್ಕ width, ಪೂರ್ಣಾಙ್ಕ height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ಧ್ರುವ ಶೂನ್ಯ *src, ಪೂರ್ಣಾಙ್ಕ src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ dst_pitch);


ಬಾಹ್ಯ bool SDL_CalculateYUVSize(SDL_PixelFormat format, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, size_t *size, size_t *pitch);

#endif // SDL_yuv_c_h_
