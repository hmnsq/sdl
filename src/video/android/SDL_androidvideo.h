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
#અન્તર્ભાવ "SDL_internal.h"

#ifndef SDL_androidvideo_h_
#define SDL_androidvideo_h_

#અન્તર્ભાવ "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
બાહ્ય શૂન્ય Android_SetScreenResolution(પૂર્ણાંક surfaceWidth, પૂર્ણાંક surfaceHeight, પૂર્ણાંક deviceWidth, પૂર્ણાંક deviceHeight, દશાંશ density, દશાંશ rate);
બાહ્ય શૂન્ય Android_SetScreenHDRHeadroom(દશાંશ headroom);
બાહ્ય શૂન્ય Android_SetFormat(પૂર્ણાંક format_wanted, પૂર્ણાંક format_got);
બાહ્ય શૂન્ય Android_SetOrientation(SDL_DisplayOrientation orientation);
બાહ્ય શૂન્ય Android_SendResize(SDL_Window *window);
બાહ્ય શૂન્ય Android_SetWindowSafeAreaInsets(પૂર્ણાંક ડાબું, પૂર્ણાંક જમણું, પૂર્ણાંક ટોચ, પૂર્ણાંક bottom);
બાહ્ય શૂન્ય Android_SetDarkMode(bool enabled);

// Private display data

સંરચના SDL_VideoData
{
    પૂર્ણાંક isPaused;
    પૂર્ણાંક isPausing;
};

બાહ્ય પૂર્ણાંક Android_SurfaceWidth;
બાહ્ય પૂર્ણાંક Android_SurfaceHeight;
બાહ્ય દશાંશ Android_ScreenDensity;
બાહ્ય પૂર્ણાંક Android_Safe_Inset_ડાબું;
બાહ્ય પૂર્ણાંક Android_Safe_Inset_જમણું;
બાહ્ય પૂર્ણાંક Android_Safe_Inset_ટોચ;
બાહ્ય પૂર્ણાંક Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
