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

#यदि_अपरिभाषितम् SDL_androidvideo_h_
#परिभाषय SDL_androidvideo_h_

#अन्तर्भाव "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
बाह्य शून्य Android_समुच्चयः_Screen_Resolution(पूर्णाङ्क surface_विस्तारः, पूर्णाङ्क surfaceHeight, पूर्णाङ्क device_विस्तारः, पूर्णाङ्क deviceHeight, भिन्न density, भिन्न दरः);
बाह्य शून्य Android_समुच्चयः_Screen_HDRHeadroom(भिन्न headroom);
बाह्य शून्य Android_समुच्चयः_Format(पूर्णाङ्क format_wanted, पूर्णाङ्क format_got);
बाह्य शून्य Android_समुच्चयः_Orientation(SDL_DisplayOrientation orientation);
बाह्य शून्य Android_SendResize(SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य Android_समुच्चयः_गवाक्षः_Safe_Area_Insets(पूर्णाङ्क वामः, पूर्णाङ्क दक्षिणः, पूर्णाङ्क शिखरम्, पूर्णाङ्क bottom);
बाह्य शून्य Android_समुच्चयः_Dark_बहुलकम्(bool enabled);

// Private display data

संरचना SDL_Video_दत्त
{
    पूर्णाङ्क isPaused;
    पूर्णाङ्क isPausing;
};

बाह्य पूर्णाङ्क Android_Surface_विस्तारः;
बाह्य पूर्णाङ्क Android_SurfaceHeight;
बाह्य भिन्न Android_ScreenDensity;
बाह्य पूर्णाङ्क Android_Safe_Inset_वामः;
बाह्य पूर्णाङ्क Android_Safe_Inset_दक्षिणः;
बाह्य पूर्णाङ्क Android_Safe_Inset_शिखरम्;
बाह्य पूर्णाङ्क Android_SafeInsetBottom;

#यदि_अन्तः // SDL_androidvideo_h_
