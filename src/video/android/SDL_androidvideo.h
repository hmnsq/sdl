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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_androidvideo_h_
#घोषणा SDL_androidvideo_h_

#समावेश "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
बाह्य व्योम Android_SetScreenResolution(पूर्णांक surfaceWidth, पूर्णांक surfaceHeight, पूर्णांक deviceWidth, पूर्णांक deviceHeight, भग्न density, भग्न rate);
बाह्य व्योम Android_SetScreenHDRHeadroom(भग्न headroom);
बाह्य व्योम Android_SetFormat(पूर्णांक format_wanted, पूर्णांक format_got);
बाह्य व्योम Android_SetOrientation(SDL_DisplayOrientation orientation);
बाह्य व्योम Android_SendResize(SDL_Window *window);
बाह्य व्योम Android_SetWindowSafeAreaInsets(पूर्णांक बायाँ, पूर्णांक दायाँ, पूर्णांक शीर्ष, पूर्णांक bottom);
बाह्य व्योम Android_SetDarkMode(bool enabled);

// Private display data

काष्ठा SDL_Video_तथ्य
{
    पूर्णांक isPaused;
    पूर्णांक isPausing;
};

बाह्य पूर्णांक Android_SurfaceWidth;
बाह्य पूर्णांक Android_SurfaceHeight;
बाह्य भग्न Android_ScreenDensity;
बाह्य पूर्णांक Android_Safe_Inset_बायाँ;
बाह्य पूर्णांक Android_Safe_Inset_दायाँ;
बाह्य पूर्णांक Android_Safe_Inset_शीर्ष;
बाह्य पूर्णांक Android_SafeInsetBottom;

#पूर्ण_अगर // SDL_androidvideo_h_
