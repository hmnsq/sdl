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
#അന്തര്ഭാവ "SDL_internal.h"

#ifndef SDL_androidvideo_h_
#define SDL_androidvideo_h_

#അന്തര്ഭാവ "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
ബാഹ്യ ശൂന്യം Android_SetScreenResolution(പൂർണ്ണസംഖ്യ surfaceWidth, പൂർണ്ണസംഖ്യ surfaceHeight, പൂർണ്ണസംഖ്യ deviceWidth, പൂർണ്ണസംഖ്യ deviceHeight, ദശാംശം density, ദശാംശം rate);
ബാഹ്യ ശൂന്യം Android_SetScreenHDRHeadroom(ദശാംശം headroom);
ബാഹ്യ ശൂന്യം Android_SetFormat(പൂർണ്ണസംഖ്യ format_wanted, പൂർണ്ണസംഖ്യ format_got);
ബാഹ്യ ശൂന്യം Android_SetOrientation(SDL_DisplayOrientation orientation);
ബാഹ്യ ശൂന്യം Android_SendResize(SDL_Window *window);
ബാഹ്യ ശൂന്യം Android_SetWindowSafeAreaInsets(പൂർണ്ണസംഖ്യ ഇടത്, പൂർണ്ണസംഖ്യ വലത്, പൂർണ്ണസംഖ്യ മുകൾ, പൂർണ്ണസംഖ്യ bottom);
ബാഹ്യ ശൂന്യം Android_SetDarkMode(bool enabled);

// Private display data

ഘടന SDL_VideoData
{
    പൂർണ്ണസംഖ്യ isPaused;
    പൂർണ്ണസംഖ്യ isPausing;
};

ബാഹ്യ പൂർണ്ണസംഖ്യ Android_SurfaceWidth;
ബാഹ്യ പൂർണ്ണസംഖ്യ Android_SurfaceHeight;
ബാഹ്യ ദശാംശം Android_ScreenDensity;
ബാഹ്യ പൂർണ്ണസംഖ്യ Android_Safe_Inset_ഇടത്;
ബാഹ്യ പൂർണ്ണസംഖ്യ Android_Safe_Inset_വലത്;
ബാഹ്യ പൂർണ്ണസംഖ്യ Android_Safe_Inset_മുകൾ;
ബാഹ്യ പൂർണ്ണസംഖ്യ Android_SafeInsetBottom;

#endif // SDL_androidvideo_h_
