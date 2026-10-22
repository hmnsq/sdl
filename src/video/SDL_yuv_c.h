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

#यदि_अपरिभाषितम् SDL_yuv_c_h_
#परिभाषय SDL_yuv_c_h_

#अन्तर्भाव "SDL_internal.h"

// YUV conversion functions

बाह्य bool SDL_Convert_Pixels_YUV_गन्तव्यम्_RGB(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णाङ्क dst_pitch);
बाह्य bool SDL_Convert_Pixels_RGB_गन्तव्यम्_YUV(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णाङ्क dst_pitch);
बाह्य bool SDL_Convert_Pixels_YUV_गन्तव्यम्_YUV(पूर्णाङ्क विस्तारः, पूर्णाङ्क height, SDL_PixelFormat src_format, SDL_Colorspace src_colorspace, SDL_PropertiesID src_properties, ध्रुव शून्य *src, पूर्णाङ्क src_pitch, SDL_PixelFormat dst_format, SDL_Colorspace dst_colorspace, SDL_PropertiesID dst_properties, शून्य *dst, पूर्णाङ्क dst_pitch);


बाह्य bool SDL_CalculateYUVSize(SDL_PixelFormat format, पूर्णाङ्क w, पूर्णाङ्क h, size_t *आकार, size_t *pitch);

#यदि_अन्तः // SDL_yuv_c_h_
