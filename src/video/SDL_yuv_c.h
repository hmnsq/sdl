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

#جيڪڏهن_وصف_نه_ٿيل SDL_yuv_c_h_
#وصف_ڪريو SDL_yuv_c_h_

#ضمن "SDL_internal.h"

// YUV conversion functions

خارجي bool SDL_Convert_Pixels_YUV_منزل_RGB(صحيح ويڪر, صحيح اوچائي, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch);
خارجي bool SDL_Convert_Pixels_RGB_منزل_YUV(صحيح ويڪر, صحيح اوچائي, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch);
خارجي bool SDL_Convert_Pixels_YUV_منزل_YUV(صحيح ويڪر, صحيح اوچائي, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ثابت فراغ *src, صحيح src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, فراغ *dst, صحيح dst_pitch);


خارجي bool SDL_CalculateYUVSize(SDL_PixelFormat format, صحيح w, صحيح h, size_t *سائيز, size_t *pitch);

#جيڪڏهن_پورو // SDL_yuv_c_h_
